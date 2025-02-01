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
* 鏂囦欢鍚嶇О          zf_device_dl1b
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
*                   SCL                 鏌ョ湅 zf_device_dl1b.h 涓� DL1B_SCL_PIN  瀹忓畾涔�
*                   SDA                 鏌ョ湅 zf_device_dl1b.h 涓� DL1B_SDA_PIN  瀹忓畾涔�
*                   XS                  鏌ョ湅 zf_device_dl1b.h 涓� DL1B_XS_PIN  瀹忓畾涔�
*                   VCC                 5V 鐢垫簮
*                   GND                 鐢垫簮鍦�
*                   ------------------------------------
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"

#include "zf_driver_delay.h"
#include "zf_driver_exti.h"
#include "zf_driver_soft_iic.h"

#include "zf_device_dl1b.h"
#include "zf_device_config.h"
#include "zf_device_type.h"

uint8 dl1b_init_flag = 0;
uint8 dl1b_finsh_flag = 0;
uint16 dl1b_distance_mm = 8192;

#if DL1B_USE_SOFT_IIC
static soft_iic_info_struct dl1b_iic_struct;

#define dl1b_transfer_8bit_array(tdata, tlen, rdata, rlen)      (soft_iic_transfer_8bit_array(&dl1b_iic_struct, (tdata), (tlen), (rdata), (rlen)))
#else
#define dl1b_transfer_8bit_array(tdata, tlen, rdata, rlen)      (iic_transfer_8bit_array(DL1B_IIC, DL1B_DEV_ADDR, (tdata), (tlen), (rdata), (rlen)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     杩斿洖浠ユ�绫充负鍗曚綅鐨勮寖鍥磋�鏁�
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     dl1b_get_distance();
// 澶囨敞淇℃伅     鍦ㄥ紑濮嬪崟娆″皠绋嬫祴閲忓悗涔熻皟鐢ㄦ�鍑芥暟
//-------------------------------------------------------------------------------------------------------------------
void dl1b_get_distance (void)
{
    if(dl1b_init_flag)
    {
        uint8 data_buffer[3];
        int16 dl1b_distance_temp = 0;

        data_buffer[0] = DL1B_GPIO__TIO_HV_STATUS >> 8;
        data_buffer[1] = DL1B_GPIO__TIO_HV_STATUS & 0xFF;
        dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);

        if(data_buffer[2])
        {

            data_buffer[0] = DL1B_SYSTEM__INTERRUPT_CLEAR >> 8;
            data_buffer[1] = DL1B_SYSTEM__INTERRUPT_CLEAR & 0xFF;
            data_buffer[2] = 0x01;
            dl1b_transfer_8bit_array(data_buffer, 3, data_buffer, 0);// clear Interrupt

            data_buffer[0] = DL1B_RESULT__RANGE_STATUS >> 8;
            data_buffer[1] = DL1B_RESULT__RANGE_STATUS & 0xFF;
            dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
            
            if(0x89 == data_buffer[2])
            {
                data_buffer[0] = DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 >> 8;
                data_buffer[1] = DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 & 0xFF;
                dl1b_transfer_8bit_array(data_buffer, 2, data_buffer, 2);
                dl1b_distance_temp = data_buffer[0];
                dl1b_distance_temp = (dl1b_distance_temp << 8) | data_buffer[1];
                
                if(dl1b_distance_temp > 4000 || dl1b_distance_temp < 0)
                {
                    dl1b_distance_mm = 8192;
                    dl1b_finsh_flag = 0;
                }
                else
                {
                    dl1b_distance_mm = dl1b_distance_temp;
                    dl1b_finsh_flag = 1;
                }
            }
            else
            {
                dl1b_distance_mm = 8192;
                dl1b_finsh_flag = 0;
            }
        }
        else
        {
            dl1b_distance_mm = 8192;
            dl1b_finsh_flag = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     DL1B INT 涓�柇鍝嶅簲澶勭悊鍑芥暟
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     dl1b_int_handler();
// 澶囨敞淇℃伅     鏈�嚱鏁伴渶瑕佸湪 DL1B_INT_PIN 瀵瑰簲鐨勫�閮ㄤ腑鏂��鐞嗗嚱鏁颁腑璋冪敤
//-------------------------------------------------------------------------------------------------------------------
void dl1b_int_handler (void)
{
#if DL1B_INT_ENABLE
    if(exti_flag_get(DL1B_INT_PIN))
    {
        exti_flag_clear(DL1B_INT_PIN);
        dl1b_get_distance();
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     鍒濆�鍖� DL1B
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     uint8           1-鍒濆�鍖栧け璐� 0-鍒濆�鍖栨垚鍔�
// 浣跨敤绀轰緥     dl1b_init();
// 澶囨敞淇℃伅
//-------------------------------------------------------------------------------------------------------------------
uint8 dl1b_init (void)
{
    uint8   return_state    = 0;
    uint8   data_buffer[2 + sizeof(dl1b_config_file)]; 
    uint16  time_out_count  = 0;

#if DL1B_USE_SOFT_IIC
    soft_iic_init(&dl1b_iic_struct, DL1B_DEV_ADDR, DL1B_SOFT_IIC_DELAY, DL1B_SCL_PIN, DL1B_SDA_PIN);
#else
    iic_init(DL1B_IIC, DL1B_DEV_ADDR, DL1B_IIC_SPEED, DL1B_SCL_PIN, DL1B_SDA_PIN);
#endif
    gpio_init(DL1B_XS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    do
    {
        system_delay_ms(50);
        gpio_low(DL1B_XS_PIN);
        system_delay_ms(10);
        gpio_high(DL1B_XS_PIN);
        system_delay_ms(50);

        data_buffer[0] = DL1B_FIRMWARE__SYSTEM_STATUS >> 8;
        data_buffer[1] = DL1B_FIRMWARE__SYSTEM_STATUS & 0xFF;
        dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
        return_state = (0x01 == (data_buffer[2] & 0x01)) ? (0) : (1);
        if(1 == return_state)
        {
            break;
        }

        data_buffer[0] = DL1B_I2C_SLAVE__DEVICE_ADDRESS >> 8;
        data_buffer[1] = DL1B_I2C_SLAVE__DEVICE_ADDRESS & 0xFF;
        memcpy(&data_buffer[2], (uint8 *)dl1b_config_file, sizeof(dl1b_config_file));
        dl1b_transfer_8bit_array(data_buffer, 2 + sizeof(dl1b_config_file), data_buffer, 0);

        while(1)
        {
            data_buffer[0] = DL1B_GPIO__TIO_HV_STATUS >> 8;
            data_buffer[1] = DL1B_GPIO__TIO_HV_STATUS & 0xFF;
            dl1b_transfer_8bit_array(data_buffer, 2, &data_buffer[2], 1);
            if(0x00 == (data_buffer[2] & 0x01))
            {
                time_out_count = 0;
                break;
            }
            if(DL1B_TIMEOUT_COUNT < time_out_count ++)
            {
                return_state = 1;
                break;
            }
            system_delay_ms(1);
        }

        dl1b_init_flag = 1;
    }while(0);

#if DL1B_INT_ENABLE
    set_tof_type(TOF_DL1B, dl1b_int_handler);
    exti_init(DL1B_INT_PIN, EXTI_TRIGGER_FALLING);
    dl1b_int_handler();
    dl1b_finsh_flag = 0;
#endif

    return return_state;
}
