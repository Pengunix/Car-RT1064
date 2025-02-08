#include "zf_common_headfile.h"

int main(void) {
  clock_init(SYSTEM_CLOCK_600M);
  debug_init();
  // 控制串口
  uart_init(UART_6, 115200, UART6_TX_B2, UART6_RX_B3);
  // 电机速度/方向
  pwm_init(PWM1_MODULE3_CHB_B11, 17000, 0);
  gpio_init(B10, GPO, 0, GPO_PUSH_PULL);
  // 舵机
  pwm_init(PWM4_MODULE1_CHA_B25, 50, 1500);
  // 编码器
  encoder_quad_init(QTIMER4_ENCODER1, QTIMER4_ENCODER1_CH1_C9,
                    QTIMER4_ENCODER1_CH2_C10);
  // 电池采样adc
  adc_init(ADC2_CH1_B28, ADC_8BIT);
  // 蜂鸣器
  gpio_init(B20, GPO, 0, GPO_PUSH_PULL);
}
