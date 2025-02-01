/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 鍗筹紙RT1064DVL6A 寮€婧愬簱锛夋槸涓€涓�熀浜庡畼鏂� SDK 鎺ュ彛鐨勭�涓夋柟寮€婧愬簱
* Copyright (c) 2022 SEEKFREE 閫愰�绉戞妧
* 
* 鏈�枃浠舵槸 RT1064DVL6A 寮€婧愬簱鐨勪竴閮ㄥ垎
* 
* RT1064DVL6A 寮€婧愬簱 鏄�厤璐硅蒋浠�
* 鎮ㄥ彲浠ユ牴鎹�嚜鐢辫蒋浠跺熀閲戜細鍙戝竷鐨� GPL锛圙NU General Public License锛屽嵆 GNU閫氱敤鍏�叡璁稿彲璇侊級鐨勬潯娆�
* 鍗� GPL 鐨勭�3鐗堬紙鍗� GPL3.0锛夋垨锛堟偍閫夋嫨鐨勶級浠讳綍鍚庢潵鐨勭増鏈�紝閲嶆柊鍙戝竷鍜�/鎴栦慨鏀瑰畠
* 
* 鏈�紑婧愬簱鐨勫彂甯冩槸甯屾湜瀹冭兘鍙戞尌浣滅敤锛屼絾骞舵湭瀵瑰叾浣滀换浣曠殑淇濊瘉
* 鐢氳嚦娌℃湁闅愬惈鐨勯€傞攢鎬ф垨閫傚悎鐗瑰畾鐢ㄩ€旂殑淇濊瘉
* 鏇村�缁嗚妭璇峰弬瑙� GPL
* 
* 鎮ㄥ簲璇ュ湪鏀跺埌鏈�紑婧愬簱鐨勫悓鏃舵敹鍒颁竴浠� GPL 鐨勫壇鏈�
* 濡傛灉娌℃湁锛岃�鍙傞槄<https://www.gnu.org/licenses/>
* 
* 棰濆�娉ㄦ槑锛�
* 鏈�紑婧愬簱浣跨敤 GPL3.0 寮€婧愯�鍙�瘉鍗忚� 浠ヤ笂璁稿彲鐢虫槑涓鸿瘧鏂囩増鏈�
* 璁稿彲鐢虫槑鑻辨枃鐗堝湪 libraries/doc 鏂囦欢澶逛笅鐨� GPL3_permission_statement.txt 鏂囦欢涓�
* 璁稿彲璇佸壇鏈�湪 libraries 鏂囦欢澶逛笅 鍗宠�鏂囦欢澶逛笅鐨� LICENSE 鏂囦欢
* 娆㈣繋鍚勪綅浣跨敤骞朵紶鎾�湰绋嬪簭 浣嗕慨鏀瑰唴瀹规椂蹇呴』淇濈暀閫愰�绉戞妧鐨勭増鏉冨０鏄庯紙鍗虫湰澹版槑锛�
* 
* 鏂囦欢鍚嶇О          zf_device_dl1a
* 鍏�徃鍚嶇О          鎴愰兘閫愰�绉戞妧鏈夐檺鍏�徃
* 鐗堟湰淇℃伅          鏌ョ湅 libraries/doc 鏂囦欢澶瑰唴 version 鏂囦欢 鐗堟湰璇存槑
* 寮€鍙戠幆澧�          IAR 8.32.4 or MDK 5.33
* 閫傜敤骞冲彴          RT1064DVL6A
* 搴楅摵閾炬帴          https://seekfree.taobao.com/
* 
* 淇�敼璁板綍
* 鏃ユ湡              浣滆€�                澶囨敞
* 2022-08-10        Teternal            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 鎺ョ嚎瀹氫箟锛�
*                   ------------------------------------
*                   妯″潡绠¤剼            鍗曠墖鏈虹�鑴�
*                   SCL                 鏌ョ湅 zf_device_dl1a.h 涓� DL1A_SCL_PIN  瀹忓畾涔�
*                   SDA                 鏌ョ湅 zf_device_dl1a.h 涓� DL1A_SDA_PIN  瀹忓畾涔�
*                   XS                  鏌ョ湅 zf_device_dl1a.h 涓� DL1A_XS_PIN  瀹忓畾涔�
*                   VCC                 5V 鐢垫簮
*                   GND                 鐢垫簮鍦�
*                   ------------------------------------
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _ZF_DEVICE_DL1A_H_
#define _ZF_DEVICE_DL1A_H_

#include "zf_common_typedef.h"

// 闇€瑕佹敞鎰忕殑鏄� DL1A 鏈€楂樻敮鎸� 400KHz 鐨� IIC 閫氫俊閫熺巼
// 闇€瑕佹敞鎰忕殑鏄� DL1A 鏈€楂樻敮鎸� 400KHz 鐨� IIC 閫氫俊閫熺巼
// 闇€瑕佹敞鎰忕殑鏄� DL1A 鏈€楂樻敮鎸� 400KHz 鐨� IIC 閫氫俊閫熺巼

#define DL1A_USE_SOFT_IIC           (1)                                         // 榛樿�浣跨敤杞�欢 IIC 鏂瑰紡椹卞姩 寤鸿�浣跨敤杞�欢 IIC 鏂瑰紡
#if DL1A_USE_SOFT_IIC                                                           // 杩欎袱娈� 棰滆壊姝ｅ父鐨勬墠鏄��纭�殑 棰滆壊鐏扮殑灏辨槸娌℃湁鐢ㄧ殑
//====================================================杞�欢 IIC 椹卞姩====================================================
#define DL1A_SOFT_IIC_DELAY         (100 )                                      // 杞�欢 IIC 鐨勬椂閽熷欢鏃跺懆鏈� 鏁板€艰秺灏� IIC 閫氫俊閫熺巼瓒婂揩
#define DL1A_SCL_PIN                (B9 )                                       // 杞�欢 IIC SCL 寮曡剼 杩炴帴 DL1A 鐨� SCL 寮曡剼
#define DL1A_SDA_PIN                (B10 )                                      // 杞�欢 IIC SDA 寮曡剼 杩炴帴 DL1A 鐨� SDA 寮曡剼
//====================================================杞�欢 IIC 椹卞姩====================================================
#else
//====================================================纭�欢 IIC 椹卞姩====================================================
#define DL1A_IIC_SPEED              (400000     )                               // 纭�欢 IIC 閫氫俊閫熺巼 鏈€楂� 400KHz 涓嶅缓璁�綆浜� 40KHz
#define DL1A_IIC                    (IIC_1      )                               // 纭�欢 IIC SCL 寮曡剼 杩炴帴 DL1A 鐨� SCL 寮曡剼
#define DL1A_SCL_PIN                (IIC1_SCL_B8)                               // 纭�欢 IIC SCL 寮曡剼 杩炴帴 DL1A 鐨� SCL 寮曡剼
#define DL1A_SDA_PIN                (IIC1_SDA_B9)                               // 纭�欢 IIC SDA 寮曡剼 杩炴帴 DL1A 鐨� SDA 寮曡剼
//====================================================纭�欢 IIC 椹卞姩====================================================
#endif

#define DL1A_XS_PIN                 (D4)

#define DL1A_INT_ENABLE             ( 1 )                                       // 鏄�惁鍚�敤 INT 寮曡剼 鍚�敤鍒欎細鑷�姩鏇存柊鏁版嵁
#if DL1A_INT_ENABLE
#define DL1A_INT_PIN                ( C20 )
#endif

#define DL1A_TIMEOUT_COUNT          (0x00FF)                                    // DL1A 瓒呮椂璁℃暟

//================================================瀹氫箟 DL1A 鍐呴儴鍦板潃================================================
#define DL1A_DEV_ADDR                                       ( 0x52 >> 1 )       // 0b0101001

#define DL1A_SYSRANGE_START                                 ( 0x00 )

#define DL1A_SYSTEM_SEQUENCE_CONFIG                         ( 0x01 )
#define DL1A_SYSTEM_INTERMEASUREMENT_PERIOD                 ( 0x04 )
#define DL1A_SYSTEM_RANGE_CONFIG                            ( 0x09 )
#define DL1A_SYSTEM_INTERRUPT_GPIO_CONFIG                   ( 0x0A )
#define DL1A_SYSTEM_INTERRUPT_CLEAR                         ( 0x0B )
#define DL1A_SYSTEM_THRESH_HIGH                             ( 0x0C )
#define DL1A_SYSTEM_THRESH_LOW                              ( 0x0E )
#define DL1A_SYSTEM_HISTOGRAM_BIN                           ( 0x81 )

#define DL1A_RESULT_INTERRUPT_STATUS                        ( 0x13 )
#define DL1A_RESULT_RANGE_STATUS                            ( 0x14 )
#define DL1A_RESULT_PEAK_SIGNAL_RATE_REF                    ( 0xB6 )
#define DL1A_RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN          ( 0xBC )
#define DL1A_RESULT_CORE_RANGING_TOTAL_EVENTS_RTN           ( 0xC0 )
#define DL1A_RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF          ( 0xD0 )
#define DL1A_RESULT_CORE_RANGING_TOTAL_EVENTS_REF           ( 0xD4 )

#define DL1A_PRE_RANGE_CONFIG_MIN_SNR                       ( 0x27 )
#define DL1A_PRE_RANGE_CONFIG_VCSEL_PERIOD                  ( 0x50 )
#define DL1A_PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI             ( 0x51 )
#define DL1A_PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO             ( 0x52 )
#define DL1A_PRE_RANGE_CONFIG_VALID_PHASE_LOW               ( 0x56 )
#define DL1A_PRE_RANGE_CONFIG_VALID_PHASE_HIGH              ( 0x57 )
#define DL1A_PRE_RANGE_CONFIG_SIGMA_THRESH_HI               ( 0x61 )
#define DL1A_PRE_RANGE_CONFIG_SIGMA_THRESH_LO               ( 0x62 )
#define DL1A_PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT             ( 0x64 )

#define DL1A_FINAL_RANGE_CONFIG_VALID_PHASE_LOW             ( 0x47 )
#define DL1A_FINAL_RANGE_CONFIG_VALID_PHASE_HIGH            ( 0x48 )
#define DL1A_FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT    ( 0x44 )
#define DL1A_FINAL_RANGE_CONFIG_MIN_SNR                     ( 0x67 )
#define DL1A_FINAL_RANGE_CONFIG_VCSEL_PERIOD                ( 0x70 )
#define DL1A_FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI           ( 0x71 )
#define DL1A_FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO           ( 0x72 )

#define DL1A_GLOBAL_CONFIG_VCSEL_WIDTH                      ( 0x32 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_0               ( 0xB0 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_1               ( 0xB1 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_2               ( 0xB2 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_3               ( 0xB3 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_4               ( 0xB4 )
#define DL1A_GLOBAL_CONFIG_SPAD_ENABLES_REF_5               ( 0xB5 )
#define DL1A_GLOBAL_CONFIG_REF_EN_START_SELECT              ( 0xB6 )

#define DL1A_ALGO_PART_TO_PART_RANGE_OFFSET_MM              ( 0x28 )
#define DL1A_ALGO_PHASECAL_LIM                              ( 0x30 )
#define DL1A_ALGO_PHASECAL_CONFIG_TIMEOUT                   ( 0x30 )

#define DL1A_HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT          ( 0x33 )
#define DL1A_HISTOGRAM_CONFIG_READOUT_CTRL                  ( 0x55 )

#define DL1A_DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD            ( 0x4E )
#define DL1A_DYNAMIC_SPAD_REF_EN_START_OFFSET               ( 0x4F )

#define DL1A_MSRC_CONFIG_TIMEOUT_MACROP                     ( 0x46 )
#define DL1A_MSRC_CONFIG                                    ( 0x60 )

#define DL1A_IDENTIFICATION_MODEL_ID                        ( 0xC0 )
#define DL1A_IDENTIFICATION_REVISION_ID                     ( 0xC2 )

#define DL1A_CROSSTALK_COMPENSATION_PEAK_RATE_MCPS          ( 0x20 )

#define DL1A_POWER_MANAGEMENT_GO1_POWER_FORCE               ( 0x80 )

#define DL1A_GPIO_HV_MUX_ACTIVE_HIGH                        ( 0x84 )

#define DL1A_I2C_SLAVE_DEVICE_ADDRESS                       ( 0x8A )

#define DL1A_SOFT_RESET_GO2_SOFT_RESET_N                    ( 0xBF )

#define DL1A_OSC_CALIBRATE_VAL                              ( 0xF8 )

#define DL1A_IO_VOLTAGE_CONFIG                              ( 0x89 )            // IO 鐢靛帇璁剧疆瀵勫瓨鍣ㄥ湴鍧€ 榛樿� 1V8 浣跨敤淇�敼涓� 2V8

//================================================瀹氫箟 DL1A 鍐呴儴鍦板潃================================================

#define DL1A_MIN_TIMING_BUDGET                              ( 20000 )

#define DL1A_GET_START_OVERHEAD                             ( 1910 )
#define DL1A_SET_START_OVERHEAD                             ( 1320 )
#define DL1A_END_OVERHEAD                                   ( 960  )
#define DL1A_TCC_OVERHEAD                                   ( 590  )
#define DL1A_DSS_OVERHEAD                                   ( 690  )
#define DL1A_MSRC_OVERHEAD                                  ( 660  )
#define DL1A_PRERANGE_OVERHEAD                              ( 660  )
#define DL1A_FINALlRANGE_OVERHEAD                           ( 550  )

typedef enum
{
    DL1A_VCSEL_PERIOD_PER_RANGE,
    DL1A_VCSEL_PERIOD_FINAL_RANGE,
}dl1a_vcsel_period_type_enum;

typedef struct
{
    uint8 tcc;
    uint8 msrc;
    uint8 dss;
    uint8 pre_range;
    uint8 final_range;
}dl1a_sequence_enables_step_struct;

typedef struct
{
    uint16 pre_range_vcsel_period_pclks;
    uint16 final_range_vcsel_period_pclks;

    uint16 msrc_dss_tcc_mclks;
    uint16 pre_range_mclks;
    uint16 final_range_mclks;
    uint32 msrc_dss_tcc_us;
    uint32 pre_range_us;
    uint32 final_range_us;
}dl1a_sequence_timeout_step_struct;

extern uint8 dl1a_finsh_flag;
extern uint16 dl1a_distance_mm;

void   dl1a_get_distance (void);

void   dl1a_int_handler  (void);
uint8  dl1a_init         (void);

#endif

