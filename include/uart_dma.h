#include "board.h"
#include "fsl_common.h"
#include "fsl_dmamux.h"
#include "fsl_iomuxc.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#include "main.h"

typedef struct {
  lpuart_transfer_t Tx_Buf;
  lpuart_transfer_t Rx_Buf;
  uint32_t TxData_Index;
  uint32_t RxData_Index;
} Lpuart_DMA_Type;
extern Lpuart_DMA_Type DMAU6;

extern lpuart_edma_handle_t g_lpuartEdmaHandle; // 串口DMA传输句柄
extern edma_handle_t g_lpuartTxEdmaHandle;      // 串口DMA发送句柄
extern edma_handle_t g_lpuartRxEdmaHandle;      // 串口DMA接收句柄

// 定义本程序使用的串口
#define DEMO_LPUART LPUART6
#define DEMO_LPUART_CLK_FREQ BOARD_DebugConsoleSrcFreq() // UART时钟频率
#define LPUART_TX_DMA_CHANNEL 0U // UART发送使用的DMA通道号
#define LPUART_RX_DMA_CHANNEL 1U // UART接收使用的DMA通道号
#define LPUART_TX_DMA_REQUEST kDmaRequestMuxLPUART6Tx // 定义串口DMA发送请求源
#define LPUART_RX_DMA_REQUEST kDmaRequestMuxLPUART6Rx // 定义串口DMA接收请求源
#define LPUART_DMAMUX_BASEADDR DMAMUX // 定义所使用的DMA多路复用模块(DMAMUX)
#define LPUART_DMA_BASEADDR DMA0 // 定义使用的DMA
#define ECHO_BUFFER_LENGTH 255     // UART接收和发送数据缓冲区长度

#define LPUART6_RX_GPIO GPIO1
#define LPUART6_RX_GPIO_PIN (3U)
#define LPUART6_RX_IOMUXC IOMUXC_GPIO_AD_B0_03_LPUART6_RX

#define LPUART6_TX_GPIO GPIO1
#define LPUART6_TX_GPIO_PIN (2U)
#define LPUART6_TX_IOMUXC IOMUXC_GPIO_AD_B0_02_LPUART6_TX

void LPUART_DMA_Init(_Bool LPUART_DMA_Mode);

void LPUART_GPIO_Init(GPIO_Type *base_tx, uint32_t pin_tx, GPIO_Type *base_rx,
                      uint32_t pin_rx, uint32 muxRegister, uint32 muxMode,
                      uint32 inputRegister, uint32 inputDaisy,
                      uint32 configRegister, uint32 muxRegister2,
                      uint32 muxMode2, uint32 inputRegister2,
                      uint32 inputDaisy2, uint32 configRegister2);
void UartCallbackDMA6(void);