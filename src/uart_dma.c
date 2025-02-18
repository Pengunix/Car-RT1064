#include "uart_dma.h"

// 收发缓冲区
__attribute__((
    section("NonCacheable.init"))) uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};

/*句柄定义*/
lpuart_edma_handle_t g_lpuartEdmaHandle; // 串口DMA传输句柄
edma_handle_t g_lpuartTxEdmaHandle;      // 串口DMA发送句柄
edma_handle_t g_lpuartRxEdmaHandle;      // 串口DMA接收句柄

Lpuart_DMA_Type DMAU6;

/* 初始化串口所使用的DMA-----------------------------------------------------------------------------------------------------------------*/
void LPUART_DMA_Init(_Bool LPUART_DMA_Mode) {
  if (LPUART_DMA_Mode == 1) {
    lpuart_config_t LpuartConfig;

    // 串口的引脚基础配置初始化
    LPUART_GPIO_Init(LPUART6_TX_GPIO, LPUART6_TX_GPIO_PIN, LPUART6_RX_GPIO,
                     LPUART6_RX_GPIO_PIN, LPUART6_TX_IOMUXC, LPUART6_RX_IOMUXC);

    /* 获取LPUART默认配置 */
    LPUART_GetDefaultConfig(&LpuartConfig);

    /* 在默认配置基础上继续配置参数 */
    LpuartConfig.baudRate_Bps = 115200;
    LpuartConfig.enableTx = true;
    LpuartConfig.enableRx = true;
    LpuartConfig.rxIdleConfig = kLPUART_IdleCharacter2;
    LpuartConfig.rxIdleType = kLPUART_IdleTypeStopBit;
    LPUART_Init(DEMO_LPUART, &LpuartConfig, DEMO_LPUART_CLK_FREQ);

    edma_config_t config;
    /*初始化DMAMUX */
    DMAMUX_Init(LPUART_DMAMUX_BASEADDR);
    /* 为LPUART设置DMA传输通道 */
    DMAMUX_SetSource(LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL,
                     LPUART_TX_DMA_REQUEST);
    DMAMUX_SetSource(LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL,
                     LPUART_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL);
    DMAMUX_EnableChannel(LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL);

    /* 初始化DMA */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(LPUART_DMA_BASEADDR, &config);

    /* 创建eDMA传输句柄 */
    EDMA_CreateHandle(&g_lpuartTxEdmaHandle, LPUART_DMA_BASEADDR,
                      LPUART_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_lpuartRxEdmaHandle, LPUART_DMA_BASEADDR,
                      LPUART_RX_DMA_CHANNEL);

    /* 创建 LPUART DMA 句柄 */
    LPUART_TransferCreateHandleEDMA(DEMO_LPUART, &g_lpuartEdmaHandle, NULL,
                                    NULL, &g_lpuartTxEdmaHandle,
                                    &g_lpuartRxEdmaHandle);

    /* 打开串口中断 */
    /* 清除可能残留的标志位，并使能空闲中断 */
    LPUART_ClearStatusFlags(DEMO_LPUART, kLPUART_IdleLineFlag);
    LPUART_EnableInterrupts(DEMO_LPUART, kLPUART_IdleLineInterruptEnable);
    EnableIRQ(LPUART6_IRQn);
    NVIC_SetPriority(LPUART6_IRQn, 6);

    /* 启动传输 */
    DMAU6.Rx_Buf.data = g_rxBuffer;
    DMAU6.Rx_Buf.dataSize = ECHO_BUFFER_LENGTH;
    LPUART_ReceiveEDMA(DEMO_LPUART, &g_lpuartEdmaHandle, &DMAU6.Rx_Buf);
  }
}

void LPUART_GPIO_Init(GPIO_Type *base_tx, uint32_t pin_tx, GPIO_Type *base_rx,
                      uint32_t pin_rx, uint32 muxRegister, uint32 muxMode,
                      uint32 inputRegister, uint32 inputDaisy,
                      uint32 configRegister, uint32 muxRegister2,
                      uint32 muxMode2, uint32 inputRegister2,
                      uint32 inputDaisy2, uint32 configRegister2) {
  /* 定义gpio初始化配置结构体 */
  gpio_pin_config_t config = {0};

  /*GPIO配置*/
  config.direction = kGPIO_DigitalInput;  // 输入模式
  config.interruptMode = kGPIO_NoIntmode; // 不使用中断
  GPIO_PinInit(base_rx, pin_rx, &config);

  config.direction = kGPIO_DigitalOutput; // 输出模式
  config.outputLogic = 1; // 默认高电平，在输入模式下配置该选项无效
  GPIO_PinInit(base_tx, pin_tx, &config);

  IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy,
                   configRegister, 0U);
  IOMUXC_SetPinMux(muxRegister2, muxMode2, inputRegister2, inputDaisy2,
                   configRegister2, 0U);
  /* 配置说明 : */
  /* 转换速率: 转换速率慢
      驱动强度: R0/6
      带宽配置 : medium(100MHz)
      开漏配置: 关闭
      拉/保持器配置: 使能
      拉/保持器选择: 上下拉
      上拉/下拉选择: 22K欧姆上拉(选择了保持器此配置无效)
      滞回器配置: 禁止 */
  IOMUXC_SetPinConfig(
      LPUART6_TX_IOMUXC,
      IOMUXC_SW_PAD_CTL_PAD_SRE(0) |         /* Slow slew rate */
          IOMUXC_SW_PAD_CTL_PAD_DSE(0x6) |   /* Drive strength */
          IOMUXC_SW_PAD_CTL_PAD_SPEED(0x2) | /* Med speed (100Mhz) */
          IOMUXC_SW_PAD_CTL_PAD_ODE(0) |     /* Open drain disabled */
          IOMUXC_SW_PAD_CTL_PAD_PKE(1) |     /* Pull/keep disabled */
          IOMUXC_SW_PAD_CTL_PAD_PUE(1) |     /* Set to keep */
          IOMUXC_SW_PAD_CTL_PAD_PUS(3) |     /* Pull down 100kOhm */
          IOMUXC_SW_PAD_CTL_PAD_HYS(0)       /* Hysteresis disabled */
  );
  IOMUXC_SetPinConfig(
      LPUART6_RX_IOMUXC,
      IOMUXC_SW_PAD_CTL_PAD_SRE(0) |         /* Slow slew rate */
          IOMUXC_SW_PAD_CTL_PAD_DSE(0x6) |   /* Drive strength */
          IOMUXC_SW_PAD_CTL_PAD_SPEED(0x2) | /* Med speed (100Mhz) */
          IOMUXC_SW_PAD_CTL_PAD_ODE(0) |     /* Open drain disabled */
          IOMUXC_SW_PAD_CTL_PAD_PKE(1) |     /* Pull/keep disabled */
          IOMUXC_SW_PAD_CTL_PAD_PUE(1) |     /* Set to keep */
          IOMUXC_SW_PAD_CTL_PAD_PUS(3) |     /* Pull down 100kOhm */
          IOMUXC_SW_PAD_CTL_PAD_HYS(0)       /* Hysteresis disabled */
  );
}

extern QueueHandle_t uartQueue;
void UartCallbackDMA6(void) {
  /* 判断中断源 */
  if (LPUART_GetStatusFlags(DEMO_LPUART) & kLPUART_IdleLineFlag) {
    /* 清除空闲中断标志位 */
    LPUART_ClearStatusFlags(DEMO_LPUART, kLPUART_IdleLineFlag);
    /* 获取当前已接收字节数 */
    LPUART_TransferGetReceiveCountEDMA(DEMO_LPUART, &g_lpuartEdmaHandle,
                                       (uint32_t *)&DMAU6.RxData_Index);
    /* 关闭DMA传输 */
    LPUART_TransferAbortReceiveEDMA(DEMO_LPUART, &g_lpuartEdmaHandle);

    /*数据处理-------------------------------------------------------------------------------------------------------*/
    gpio_toggle_level(B9);
    BaseType_t yeildFromISR = pdFALSE;
    if (DMAU6.RxData_Index == 12) {
      xQueueSendToBackFromISR(uartQueue, DMAU6.Rx_Buf.rxData, &yeildFromISR);
    } else {
      memset(g_rxBuffer, 0, ECHO_BUFFER_LENGTH);
    }

    /* 重新开始DMA接收传输 */
    LPUART_ReceiveEDMA(DEMO_LPUART, &g_lpuartEdmaHandle, &DMAU6.Rx_Buf);
    portYIELD_FROM_ISR(yeildFromISR);
  }
}