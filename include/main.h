#pragma once
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"
#include "zf_common_headfile.h"

// 注意修改引脚
#define DEBUG_UART UART_1
#define DEBUG_UART_TX UART1_TX_B12
#define DEBUG_UART_RX UART1_RX_B13
#define MOTOR_PWM PWM1_MODULE3_CHA_B10
#define MOTOR_DIR B11
#define SERVO_PWM PWM4_MODULE2_CHA_C30
#define BAT_ADC ADC2_CH1_B28
#define BUZZER_PIN B29
#define LED_PIN B9
// 注意修改引脚
#define ENCODER_CH QTIMER4_ENCODER1
#define BUTTON1 C13
#define BUTTON2 C14
#define BUTTON3 C11
#define BUTTON4 C12

#define UART_FRAME_HEAD 0x34
#define UART_FRAME_TAIL 0x43
#define PWMSERVOMID 1500
#define BATTERYTHRESH 90
#define AVERAGECOUNT 5

#define ENCODER_OM 6773
#define PIT_PERIOD_S 0.001
#define PIT_PERIOD_MS 1

#define MOTOR_PWM_MAX 7000
#define MOTOR_PWM_MIN -7000

enum Buzzer {
  BUZZER_SLIENT = -1,
  BUZZER_OK = 0,   // 确认
  BUZZER_WARNNING, // 报警
  BUZZER_FINISH,   // 完成
  BUZZER_DING,     // 提示
  BUZZER_START,    // 开机
};

#define UART_RX_SIZE 12
typedef union {
  uint8 data[UART_RX_SIZE];
  struct {
    uint8 head;
    int8 buzzer;
    uint16 servo;
    float speed;
    uint8 _reserved;
    uint8 dis; // x100
    uint8 xorCheck;
    uint8 tail;
  };
} UartRecvFrame;

#define UART_TX_SIZE 24
typedef union {
  uint8 data[UART_TX_SIZE];
  struct {
    uint8 head;
    uint8 keys;
    uint8 dis_achieced;
    uint8 _reserved;
    float speed;
    float roll;
    float pitch;
    float yaw;
    uint8 _reserved1[2];
    uint8 xorCheck;
    uint8 tail;
  };
} UartTranFrame;

typedef struct {
  float kp;
  float ki;
  float error;
  float last_error;
  long output;
  float speed;
  float exp_speed;
  int32_t encoder_num;
} SPEED_PID;