#include "main.h"
#include "uart_dma.h"

QueueHandle_t buzzerQueue;
QueueHandle_t uartQueue;

static void hello_task(void *pv) {
  for (;;) {
    gpio_set_level(B9, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(B9, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    enum Buzzer ac1 = BUZZER_START;
    xQueueGenericSend(buzzerQueue, &ac1, portMAX_DELAY, queueSEND_TO_BACK);
  }
}

static void tUartRecv(void *pv) {
  UartRecvFrame recv;
  for (;;) {
    if (pdPASS == xQueueReceive(uartQueue, &recv, portMAX_DELAY)) {
      uart_write_buffer(UART_1, recv.data, 12);
    }
  }
}

static void tBuzzer(void *pv) {
  enum Buzzer action;
  for (;;) {
    if (pdPASS == xQueueReceive(buzzerQueue, &action, portMAX_DELAY)) {
      switch (action) {
      case BUZZER_OK:
        // 短一声
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        break;
      case BUZZER_DING:
        // 长一声
        gpio_set_level(B29, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        break;
      case BUZZER_WARNNING:
        // 短三声
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        break;
      case BUZZER_FINISH:
        // 一长两短
        gpio_set_level(B29, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
      case BUZZER_START:
        // 两短一长
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(B29, 0);
      }
    }
  }
}

int main(void) {
  // DisableGlobalIRQ();
  clock_init(SYSTEM_CLOCK_600M);
  // 调试串口
  uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);
  // 控制串口
  LPUART_DMA_Init(1);
  // uart_init(UART_6, 115200, UART6_TX_B2, UART6_RX_B3);
  // 电机速度/方向
  pwm_init(PWM1_MODULE3_CHA_B10, 17000, 5000);
  gpio_init(B9, GPO, 0, GPO_PUSH_PULL);
  // 舵机
  pwm_init(PWM4_MODULE2_CHA_C30, 50, 1500);
  // 编码器
  encoder_quad_init(QTIMER4_ENCODER1, QTIMER4_ENCODER1_CH1_C9,
                    QTIMER4_ENCODER1_CH2_C10);
  // 电池采样adc
  adc_init(ADC2_CH1_B28, ADC_8BIT);
  // 蜂鸣器
  gpio_init(B29, GPO, 0, GPO_PUSH_PULL);
  // 核心板led
  gpio_init(B9, GPO, 1, GPO_PUSH_PULL);

  buzzerQueue = xQueueCreate(5, sizeof(enum Buzzer));
  uartQueue = xQueueCreate(5, sizeof(UartRecvFrame));

  BaseType_t ret;
  ret = xTaskCreate(hello_task, "Hello", configMINIMAL_STACK_SIZE + 100, NULL,
                    configMAX_PRIORITIES - 1, NULL);
  ret = xTaskCreate(tBuzzer, "BUZZER", 128, NULL, 4, NULL);
  ret = xTaskCreate(tUartRecv, "CTRL", 128, NULL, 4, NULL);
  if (ret != pdPASS) {
    while (1) {
      uart_write_string(UART_1, "[ERROR] Create Task Error\r\4");
    }
  }

  vTaskStartScheduler();
}