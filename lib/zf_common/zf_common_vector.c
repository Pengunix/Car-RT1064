#include "zf_common_vector.h"

void NMI_Handler(void) {
  while (1)
    ;
}
void HardFault_Handler(void) {
  // 硬件上访  可能是数组越界或者使用了未初始化的设备
  // 这里提示大家一个问题，经常有人说我的外设初始化了怎么就是要进HardFault呢
  // 很多是因为自己开了中断，然后在中断里面使用了外设，然后他的初始化顺序是先初始化中断然后再初始化外设
  // 那么问题就来了，中断初始化完成之后会部分中断直接进入中断函数或者满足调节也会进入中断函数，那么就会造成中断里面使用到的外设还没被初始化
  // 所以大家需要注意这个问题
  while (1)
    ;
}
void MemManage_Handler(void) {
  while (1)
    ;
}
void BusFault_Handler(void) {
  while (1)
    ;
}
void UsageFault_Handler(void) {
  while (1)
    ;
}
// void SVC_Handler(void)
// {
// 	while(1);
// }
void DebugMon_Handler(void) {
  while (1)
    ;
}
// void PendSV_Handler(void)
// {
// 	while(1);
// }

// void SysTick_Handler(void)
//{
//	while(1);
// }
