#include "zf_common_headfile.h"

uint8 gpio_status;
int main(void) {
  clock_init(SYSTEM_CLOCK_600M); // 不可删除
  debug_init();                  // 调试端口初始化

  // 此处编写用户代码 例如外设初始化代码等

  // 初始化GPIO B9 为输出 默认输出低电平
  gpio_init(B9, GPO, 0, GPO_PUSH_PULL);

  // 初始化GPIO D0 D1 为输入引脚
  gpio_init(C4, GPI, 0, GPI_PULL_UP);
  gpio_init(D1, GPI, 0, GPI_PULL_UP);

  // 此处编写用户代码 例如外设初始化代码等

  while (1) {
    gpio_set_level(B9, 1); // 设置引脚电平为高电平
    system_delay_ms(100);
    gpio_set_level(B9, 0); // 设置引脚电平为低电平
    system_delay_ms(100);
    gpio_toggle_level(B9); // 翻转引脚电平
    system_delay_ms(100);

    gpio_status = gpio_get_level(C4); // 获取引脚电平
    system_delay_ms(100);
  }
}
