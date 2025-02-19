#pragma once
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"
#include "zf_common_headfile.h"
#define DEBUG_UART UART_1
#define DEBUG_UART_TX UART1_TX_B12
#define DEBUG_UART_RX UART1_RX_B13

#define MOTOR_PWM PWM1_MODULE3_CHA_B10
#define MOTOR_DIR B11

#define SERVO_PWM PWM4_MODULE2_CHA_C30

#define BAT_ADC ADC2_CH1_B28

#define BUZZER_PIN B29
#define LED_PIN B9

enum Buzzer {
  BUZZER_SLIENT = -1,
  BUZZER_OK = 0,   // 确认
  BUZZER_WARNNING, // 报警
  BUZZER_FINISH,   // 完成
  BUZZER_DING,     // 提示
  BUZZER_START,    // 开机
};

#define UART_FRAME_HEAD 0x34
#define UART_FRAME_TAIL 0x43
typedef union {
  uint8 data[12];
  uint8 head;
  int8 buzzer;
  uint16 servo;
  float speed;
  uint8 _reserved[2];
  uint8 xorCheck;
  uint8 tail;
} UartRecvFrame;

#define PWMSERVOMID 1500
#define BATTERYTHRESH 90