#include "main.h"
#include "uart_dma.h"

QueueHandle_t buzzerQueue;
QueueHandle_t uartQueue;

TimerHandle_t xUartResetTimer;

volatile uint16_t xBatteryAdc;
volatile char xPrintStr[64];
volatile UartRecvFrame uartRecv;
volatile float targetSpeed;

static void tMisc(void *pv) {
  for (;;) {
    gpio_toggle_level(LED_PIN);
    xBatteryAdc = adc_convert(BAT_ADC);
    if (xBatteryAdc <= BATTERYTHRESH) {
      enum Buzzer action = BUZZER_WARNNING;
      xQueueSendToBack(buzzerQueue, &action, 100);
    }

#ifdef DEBUG
    snprintf(xPrintStr, 24, "targetSpeed: %d \r\n", (int)(targetSpeed * 10));
    uart_write_buffer(DEBUG_UART, xPrintStr, 20);
#endif // DEBUG
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static uint8_t xorCheck(uint8_t *data, uint16_t size) {
  uint8_t result = 0;
  for (uint8_t i = 0; i < size; ++i) {
    result ^= *(data + i);
  }
  return result;
}

static void tUartRecv(void *pv) {
  uint8_t recv[12];
  for (;;) {
    if (pdPASS == xQueueReceive(uartQueue, &recv, portMAX_DELAY)) {
      // uart_write_buffer(UART_6, recv, 12);
      if (recv[0] == UART_FRAME_HEAD && recv[11] == UART_FRAME_TAIL) {
        if (recv[10] == xorCheck(recv, 12)) {
          memcpy(uartRecv.data, recv, 12);
          // 设置速度
          targetSpeed = uartRecv.speed;
          // 设置舵机
          pwm_set_duty(SERVO_PWM, uartRecv.servo);
          // 蜂鸣器
          if (uartRecv.buzzer != BUZZER_SLIENT) {
            xQueueSendToBack(buzzerQueue, &uartRecv.buzzer, pdMS_TO_TICKS(1));
          }
          xTimerReset(xUartResetTimer, 0);
        } else {
#ifdef DEBUG
          uart_write_string(DEBUG_UART, "XOR sum ERROR!\r\n");
#endif // DEBUG
        }
      } else {
#ifdef DEBUG
        uart_write_string(DEBUG_UART, "Uart Frame Recv Error!\r\n");
#endif // DEBUG
      }
    }
  }
}

static void uartResetTimerCallback() {
  pwm_set_duty(MOTOR_PWM, 0);
  pwm_set_duty(SERVO_PWM, PWMSERVOMID);
}

static void tBuzzer(void *pv) {
  enum Buzzer action;
  for (;;) {
    if (pdPASS == xQueueReceive(buzzerQueue, &action, portMAX_DELAY)) {
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
      }
    }
  }
}

int main(void) {
  // DisableGlobalIRQ();
  clock_init(SYSTEM_CLOCK_600M);
  // 调试串口
  uart_init(DEBUG_UART, 115200, DEBUG_UART_TX, DEBUG_UART_RX);
  // 控制串口 UART_6 B2 B3
  LPUART_DMA_Init(1);
  // uart_init(UART_6, 115200, UART6_TX_B2, UART6_RX_B3);
  // 电机速度/方向
  pwm_init(MOTOR_PWM, 17000, 1000);
  gpio_init(MOTOR_DIR, GPO, 0, GPO_PUSH_PULL);
  // 舵机
  pwm_init(SERVO_PWM, 50, PWMSERVOMID);
  pwm_init(PWM2_MODULE3_CHA_B0, 50, 1500);
  // 编码器
  encoder_quad_init(QTIMER4_ENCODER1, QTIMER4_ENCODER1_CH1_C9,
                    QTIMER4_ENCODER1_CH2_C10);
  // 电池采样adc
  adc_init(BAT_ADC, ADC_8BIT);
  // 蜂鸣器
  gpio_init(BUZZER_PIN, GPO, 0, GPO_PUSH_PULL);
  // 核心板led
  gpio_init(LED_PIN, GPO, 1, GPO_PUSH_PULL);

  buzzerQueue = xQueueCreate(4, sizeof(enum Buzzer));
  uartQueue = xQueueCreate(8, sizeof(UartRecvFrame));

  if (buzzerQueue == NULL || uartQueue == NULL) {
#ifdef DEBUG
    uart_write_string(UART_1, "Queue Creation failed!\r\n");
    system_delay_ms(100);
#endif // DEBUG
  }

  xUartResetTimer = xTimerCreate("Uart Reset", pdMS_TO_TICKS(500), pdTRUE, NULL,
                                 uartResetTimerCallback);
  if (xUartResetTimer != NULL) {
    // xTimerStart(xUartResetTimer, 0);
  }

  BaseType_t ret;
  ret = xTaskCreate(tMisc, "MISC", 256, NULL, 1, NULL);
  ret = xTaskCreate(tBuzzer, "BUZZER", 128, NULL, 4, NULL);
  ret = xTaskCreate(tUartRecv, "CTRLUART", 128, NULL, 4, NULL);
  if (ret != pdPASS) {
    while (1) {
#ifdef DEBUG
      uart_write_string(UART_1, "Task Creation Error!\r\n");
      system_delay_ms(100);
#endif // DEBUG
    }
  }
  vTaskStartScheduler();
}