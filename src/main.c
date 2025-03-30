#include "main.h"
#include "uart_dma.h"

QueueHandle_t hBuzzerQueue;
TimerHandle_t xUartResetTimer;

TaskHandle_t hUartSend;
// TaskHandle_t hUartRecv;
extern __attribute__((
    section("NonCacheable.init"))) uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH];

// volatile uint16_t xBatteryAdc;
volatile uint32_t xTime;
volatile float count_dis;
volatile float exp_dis;
volatile uint8_t CarStart = 0; // 发车标志
// EventGroupHandle_t Events;
// 速度和编码器五次平均
volatile float speedAverage[AVERAGECOUNT];
volatile int16_t encoderPulses[AVERAGECOUNT];

UartRecvFrame uartRecv;
UartTranFrame uartTran;
SPEED_PID pid;

#ifdef DEBUG
volatile char xPrintStr[64];
#endif // DEBUG
float sp_sum = 0;
int32_t en_sum = 0;
void PIDCalculate() {
  sp_sum = 0;
  en_sum = 0;
  xTime++;

  // 左移一位，再读取
  for (int i = AVERAGECOUNT - 1; i > 0; --i) {
    speedAverage[i] = speedAverage[i - 1];
    encoderPulses[i] = encoderPulses[i - 1];
  }
  // 极性反转，前进为正
  encoderPulses[0] = -encoder_get_count(ENCODER_CH);
  encoder_clear_count(ENCODER_CH);

  speedAverage[0] =
      (float)(encoderPulses[0]) / (float)(ENCODER_OM * PIT_PERIOD_S);

  for (int i = 0; i < AVERAGECOUNT; ++i) {
    sp_sum += speedAverage[i];
    en_sum += encoderPulses[i];
  }
  pid.encoder_num = en_sum / AVERAGECOUNT;
  pid.speed = sp_sum / AVERAGECOUNT;
  pid.error = pid.exp_speed * PIT_PERIOD_S * ENCODER_OM - pid.encoder_num;

  static float P_out = 0;
  static float I_out = 0;

  P_out += pid.kp * (pid.error - pid.last_error);
  I_out += pid.ki * pid.error;

  if (I_out > MOTOR_PWM_MAX)
    I_out = MOTOR_PWM_MAX;
  else if (I_out < MOTOR_PWM_MIN)
    I_out = MOTOR_PWM_MIN;

  pid.output = (long)(P_out + I_out);
  if (pid.output > MOTOR_PWM_MAX)
    pid.output = MOTOR_PWM_MAX;
  else if (pid.output < MOTOR_PWM_MIN)
    pid.output = MOTOR_PWM_MIN;

  pid.last_error = pid.error;
  // 距离积分
  if (exp_dis != 0.0) {
    count_dis += pid.speed * PIT_PERIOD_S;
    if (count_dis > exp_dis) {
      uartTran.dis_achieved = 1;
    } else {
      uartTran.dis_achieved = 0;
    }
  }

  if (CarStart) {
    if (pid.output >= 0) {
      gpio_set_level(MOTOR_DIR, MOTOR_FORWARD);
      pwm_set_duty(MOTOR_PWM, pid.output);
    } else {
      gpio_set_level(MOTOR_DIR, MOTOR_BACKWARD);
      pwm_set_duty(MOTOR_PWM, -(pid.output));
    }
  }
}

static void tMisc(void *pv) {
  for (;;) {
    uint8_t keys = 0;
    keys |= gpio_get_level(BUTTON1) << 1;
    keys |= gpio_get_level(BUTTON2) << 2;
    keys |= gpio_get_level(BUTTON3) << 3;
    keys |= gpio_get_level(BUTTON4) << 4;
    uartTran.keys = keys;

    // gpio_toggle_level(LED_PIN);
    // xBatteryAdc = adc_convert(BAT_ADC);
    // if (xBatteryAdc <= BATTERYTHRESH) {
    //   enum Buzzer action = BUZZER_WARNNING;
    //   xQueueSendToBack(hBuzzerQueue, &action, 100);
    // }
    vTaskDelay(500 / portTICK_PERIOD_MS);

#ifdef DEBUG
    // int16_t enc = -encoder_get_count(ENCODER_CH);
    // encoder_clear_count(ENCODER_CH);

    snprintf(xPrintStr, 16, "espeed %d \r\n", (int)(pid.exp_speed * 100));
    uart_write_buffer(DEBUG_UART, xPrintStr, 20);
#endif // DEBUG
  }
}

uint8_t xorCheck(uint8_t *data, uint16_t size, uint8_t xorByte) {
  uint8_t result = 0;
  for (uint8_t i = 0; i < size; ++i) {
    result ^= *(data + i);
  }
  result ^= xorByte;
  return result;
}

// TODO: 陀螺仪数据
static void tUartSend(void *pv) {
  uartTran.head = 0x34;
  uartTran.tail = 0x43;
  for (;;) {
    uartTran.speed = pid.speed;
    for (int i = 0; i < UART_TX_SIZE; ++i) {
      xorCheck(uartTran.data, UART_TX_SIZE, 0);
      uart_write_byte(UART_6, uartTran.data[i]);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void uartResetTimerCallback() {
  pid.exp_speed = 0;
  // TODO: 使用了OC电路，输出反相，改为与门换回来即可
  pwm_set_duty(SERVO_PWM, PWM_DUTY_MAX - PWMSERVOMID);
}

static void tBuzzer(void *pv) {
  enum Buzzer action;
  for (;;) {
    if (pdPASS == xQueueReceive(hBuzzerQueue, &action, portMAX_DELAY)) {
      switch (action) {
      case BUZZER_OK:
        // 短一声
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        break;
      case BUZZER_DING:
        // 长一声
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        break;
      case BUZZER_WARNNING:
        // 短三声
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        break;
      case BUZZER_FINISH:
        // 一长两短
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        break;
      case BUZZER_START:
        // 两短一长
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(BUZZER_PIN, 0);
        break;
      default:
        break;
      }
    }
  }
}

int main(void) {
  clock_init(SYSTEM_CLOCK_600M);
  // 调试串口
  uart_init(DEBUG_UART, 115200, DEBUG_UART_TX, DEBUG_UART_RX);
  // 控制串口 UART_6 B2 B3
  LPUART_DMA_Init(1);
  gpio_set_level(LED_PIN, 0);
  // uart_init(UART_6, 115200, UART6_TX_B2, UART6_RX_B3);
  // 电机速度
  pwm_init(MOTOR_PWM, 17000, 0);
  // 舵机
  pwm_init(SERVO_PWM, 100, PWMSERVOMID);
  // 编码器
  encoder_quad_init(ENCODER_CH, QTIMER4_ENCODER1_CH1_C9,
                    QTIMER4_ENCODER1_CH2_C10);
  // 电池采样adc
  // adc_init(BAT_ADC, ADC_8BIT);
  // PID定时器中断
  // TODO: 速度PID参数调整
  pid.kp = 300.0;
  pid.ki = 30.0;
  pit_ms_init(PIT_CH0, PIT_PERIOD_MS);
  // 电机方向
  gpio_init(MOTOR_DIR, GPO, 1, GPO_PUSH_PULL);
  // 蜂鸣器
  gpio_init(BUZZER_PIN, GPO, 0, GPO_PUSH_PULL);
  // 按钮
  gpio_init(BUTTON1, GPI, 0, GPI_PULL_DOWN);
  gpio_init(BUTTON2, GPI, 0, GPI_PULL_DOWN);
  gpio_init(BUTTON3, GPI, 0, GPI_PULL_DOWN);
  gpio_init(BUTTON4, GPI, 0, GPI_PULL_DOWN);
  // 核心板led
  gpio_init(LED_PIN, GPO, 0, GPO_PUSH_PULL);

  hBuzzerQueue = xQueueCreate(4, sizeof(enum Buzzer));

  if (hBuzzerQueue == NULL) {
#ifdef DEBUG
    uart_write_string(UART_1, "Queue Creation failed!\r\n");
    system_delay_ms(100);
#endif // DEBUG
  }

  xUartResetTimer = xTimerCreate("Uart Reset", pdMS_TO_TICKS(500), pdTRUE, NULL,
                                 uartResetTimerCallback);
  if (xUartResetTimer != NULL) {
    xTimerStart(xUartResetTimer, 0);
  }

  BaseType_t ret;
  ret = xTaskCreate(tMisc, "MISC", 256, NULL, 1, NULL);
  ret = xTaskCreate(tBuzzer, "BUZZER", 128, NULL, 1, NULL);
  // ret = xTaskCreate(tUartRecv, "CTRL RX", 128, NULL, 4, &hUartRecv);
  ret = xTaskCreate(tUartSend, "CTRL TX", 128, NULL, 1, &hUartSend);
  if (ret != pdPASS) {
    while (1) {
#ifdef DEBUG
      uart_write_string(UART_1, "Task Creation Error!\r\n");
      system_delay_ms(100);
#endif // DEBUG
    }
  }
  vTaskStartScheduler();
  for(;;) {}
}