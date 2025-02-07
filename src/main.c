#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// *************************** 例程硬件连接说明 ***************************
// 核心板正常供电即可 无需额外连接

// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，完成上电
//
// 2.使用万用表检测 PWM_CHx 对应的通道，会看到电压变化
//
// 2.使用示波器检测 PWM_CHx 对应的通道，会看到脉宽变化
//
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************
#define CHANNEL_NUMBER (4)

#define PWM_CH1 (PWM1_MODULE3_CHA_D0)
#define PWM_CH2 (PWM1_MODULE3_CHB_D1)
#define PWM_CH3 (PWM2_MODULE3_CHA_D2)
#define PWM_CH4 (PWM2_MODULE3_CHB_D3)

int16 duty = 0;
uint8 channel_index = 0;
pwm_channel_enum channel_list[CHANNEL_NUMBER] = {PWM_CH1, PWM_CH2, PWM_CH3,
                                                 PWM_CH4};

int main(void) {
  clock_init(SYSTEM_CLOCK_600M); // 初始化芯片时钟 工作频率为 600MHz
  debug_init();                  // 初始化默认 debug uart

  // 此处编写用户代码 例如外设初始化代码等
  pwm_init(PWM_CH1, 17000, 0); // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
  pwm_init(PWM_CH2, 17000, 0); // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
  pwm_init(PWM_CH3, 17000, 0); // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
  pwm_init(PWM_CH4, 17000, 0); // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
  gpio_init(B9, GPO, 0, GPO_PUSH_PULL);
  // 此处编写用户代码 例如外设初始化代码等

  while (1) {
    // 此处编写需要循环执行的代码
    for (channel_index = 0; channel_index < CHANNEL_NUMBER; channel_index++) {
      for (duty = 0; duty <= PWM_DUTY_MAX / 2; duty++) // 输出占空比递增到 50%
      {
        pwm_set_duty(channel_list[channel_index], duty); // 更新对应通道占空比
        system_delay_us(100);
      }
      gpio_set_level(B9, 1);
      for (duty = PWM_DUTY_MAX / 2; duty >= 0; duty--) // 输出占空比递减到 0%
      {
        pwm_set_duty(channel_list[channel_index], duty); // 更新对应通道占空比
        system_delay_us(100);
      }
      gpio_set_level(B9, 0);
      uart_write_byte(DEBUG_UART_INDEX, 0x36);
    }
    // 此处编写需要循环执行的代码
  }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
//
// 问题1：PWM_CHx 对应的通道长时间无信号、电压变化
//      查看程序是否正常烧录，是否下载报错，确认正常按下复位按键
//      四个通道同一时间只有一个通道输出，换个通道看看
