#pragma once
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"
#include "zf_common_headfile.h"

enum Buzzer {
  BUZZER_OK = 0,   // 确认
  BUZZER_WARNNING, // 报警
  BUZZER_FINISH,   // 完成
  BUZZER_DING,     // 提示
  BUZZER_START,    // 开机
};

typedef union {
  uint8 data[12];
  uint8 head;
  uint8 buzzer;
  uint16 servo;
  float speed;
  uint8 _reserved[2];
  uint8 xorCheck;
  uint8 tail;
} UartRecvFrame;