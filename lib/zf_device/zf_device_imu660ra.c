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
* 鏂囦欢鍚嶇О          zf_device_imu660ra
* 鍏�徃鍚嶇О          鎴愰兘閫愰�绉戞妧鏈夐檺鍏�徃
* 鐗堟湰淇℃伅          鏌ョ湅 libraries/doc 鏂囦欢澶瑰唴 version 鏂囦欢 鐗堟湰璇存槑
* 寮€鍙戠幆澧�          IAR 8.32.4 or MDK 5.33
* 閫傜敤骞冲彴          RT1064DVL6A
* 搴楅摵閾炬帴          https://seekfree.taobao.com/
*
* 淇�敼璁板綍
* 鏃ユ湡              浣滆€�                澶囨敞
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 鎺ョ嚎瀹氫箟锛�
*                   ------------------------------------
*                   妯″潡绠¤剼            鍗曠墖鏈虹�鑴�
*                   // 纭�欢 SPI 寮曡剼
*                   SCL/SPC           鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_SPC_PIN 瀹忓畾涔�
*                   SDA/DSI           鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_SDI_PIN 瀹忓畾涔�
*                   SA0/SDO           鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_SDO_PIN 瀹忓畾涔�
*                   CS                鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_CS_PIN 瀹忓畾涔�
*                   VCC               3.3V鐢垫簮
*                   GND               鐢垫簮鍦�
*                   鍏朵綑寮曡剼鎮�┖
*
*                   // 杞�欢 IIC 寮曡剼
*                   SCL/SPC           鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_SCL_PIN 瀹忓畾涔�
*                   SDA/DSI           鏌ョ湅 zf_device_imu660ra.h 涓� IMU660RA_SDA_PIN 瀹忓畾涔�
*                   VCC               3.3V鐢垫簮
*                   GND               鐢垫簮鍦�
*                   鍏朵綑寮曡剼鎮�┖
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_iic.h"
#include "zf_device_config.h"
#include "zf_device_imu660ra.h"

int16 imu660ra_gyro_x = 0, imu660ra_gyro_y = 0, imu660ra_gyro_z = 0;            // 涓夎酱闄€铻轰华鏁版嵁   gyro (闄€铻轰华)
int16 imu660ra_acc_x = 0, imu660ra_acc_y = 0, imu660ra_acc_z = 0;               // 涓夎酱鍔犻€熷害璁℃暟鎹� acc  (accelerometer 鍔犻€熷害璁�)
float imu660ra_transition_factor[2] = {4096, 16.4};

#if IMU660RA_USE_SOFT_IIC
static soft_iic_info_struct imu660ra_iic_struct;

#define imu660ra_write_register(reg, data)        (soft_iic_write_8bit_register (&imu660ra_iic_struct, (reg), (data)))
#define imu660ra_write_registers(reg, data, len)  (soft_iic_write_8bit_registers(&imu660ra_iic_struct, (reg), (data), (len)))
#define imu660ra_read_register(reg)               (soft_iic_read_8bit_register  (&imu660ra_iic_struct, (reg)))
#define imu660ra_read_registers(reg, data, len)   (soft_iic_read_8bit_registers (&imu660ra_iic_struct, (reg), (data), (len)))
#else
//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     IMU660RA 鍐欏瘎瀛樺櫒
// 鍙傛暟璇存槑     reg             瀵勫瓨鍣ㄥ湴鍧€
// 鍙傛暟璇存槑     data            鏁版嵁
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                   // 鍏抽棴楂樼骇鐪佺數妯″紡
// 澶囨敞淇℃伅     鍐呴儴璋冪敤
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_register (uint8 reg, uint8 data)
{
    IMU660RA_CS(0);
    spi_write_8bit_register(IMU660RA_SPI, reg | IMU660RA_SPI_W, data);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     IMU660RA 鍐欐暟鎹�
// 鍙傛暟璇存槑     reg             瀵勫瓨鍣ㄥ湴鍧€
// 鍙傛暟璇存槑     data            鏁版嵁
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));
// 澶囨敞淇℃伅     鍐呴儴璋冪敤
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_registers (uint8 reg, const uint8 *data, uint32 len)
{
    IMU660RA_CS(0);
    spi_write_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_W, data, len);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     IMU660RA 璇诲瘎瀛樺櫒
// 鍙傛暟璇存槑     reg             瀵勫瓨鍣ㄥ湴鍧€
// 杩斿洖鍙傛暟     uint8           鏁版嵁
// 浣跨敤绀轰緥     imu660ra_read_register(IMU660RA_CHIP_ID);
// 澶囨敞淇℃伅     鍐呴儴璋冪敤
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu660ra_read_register (uint8 reg)
{
    uint8 data[2];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, data, 2);
    IMU660RA_CS(1);
    return data[1];
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     IMU660RA 璇绘暟鎹�
// 鍙傛暟璇存槑     reg             瀵勫瓨鍣ㄥ湴鍧€
// 鍙傛暟璇存槑     data            鏁版嵁缂撳啿鍖�
// 鍙傛暟璇存槑     len             鏁版嵁闀垮害
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
// 澶囨敞淇℃伅     鍐呴儴璋冪敤
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_read_registers (uint8 reg, uint8 *data, uint32 len)
{
    uint8 temp_data[8];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, temp_data, len + 1);
    IMU660RA_CS(1);
    for(int i = 0; i < len; i ++)
    {
        *(data ++) = temp_data[i + 1];
    }
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     IMU660RA 鑷��
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     uint8           1-鑷��澶辫触 0-鑷��鎴愬姛
// 浣跨敤绀轰緥     imu660ra_self_check();
// 澶囨敞淇℃伅     鍐呴儴璋冪敤
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu660ra_self_check (void)
{
    uint8 dat = 0, return_state = 0;
    uint16 timeout_count = 0;
    do
    {
        if(IMU660RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state =  1;
            break;
        }
        dat = imu660ra_read_register(IMU660RA_CHIP_ID);
        system_delay_ms(1);
    }while(0x24 != dat);                                                        // 璇诲彇璁惧�ID鏄�惁绛変簬0X24锛屽�鏋滀笉鏄�0X24鍒欒�涓烘病妫€娴嬪埌璁惧�
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     鑾峰彇 IMU660RA 鍔犻€熷害璁℃暟鎹�
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     imu660ra_get_acc();                                             // 鎵ц�璇ュ嚱鏁板悗锛岀洿鎺ユ煡鐪嬪�搴旂殑鍙橀噺鍗冲彲
// 澶囨敞淇℃伅     浣跨敤 SPI 鐨勯噰闆嗘椂闂翠负69us
//             浣跨敤 IIC 鐨勯噰闆嗘椂闂翠负126us        閲囬泦鍔犻€熷害璁＄殑鏃堕棿涓庨噰闆嗛檧铻轰华鐨勬椂闂翠竴鑷寸殑鍘熷洜鏄�兘鍙�槸璇诲彇瀵勫瓨鍣ㄦ暟鎹�
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_acc (void)
{
    uint8 dat[6];

    imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
    imu660ra_acc_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu660ra_acc_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu660ra_acc_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}
//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     鑾峰彇 IMU660RA 闄€铻轰华鏁版嵁
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     void
// 浣跨敤绀轰緥     imu660ra_get_gyro();                                            // 鎵ц�璇ュ嚱鏁板悗锛岀洿鎺ユ煡鐪嬪�搴旂殑鍙橀噺鍗冲彲
// 澶囨敞淇℃伅     浣跨敤 SPI 鐨勯噰闆嗘椂闂翠负69us
//             浣跨敤 IIC 鐨勯噰闆嗘椂闂翠负126us
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_gyro (void)
{
    uint8 dat[6];

    imu660ra_read_registers(IMU660RA_GYRO_ADDRESS, dat, 6);
    imu660ra_gyro_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu660ra_gyro_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu660ra_gyro_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}

//-------------------------------------------------------------------------------------------------------------------
// 鍑芥暟绠€浠�     鍒濆�鍖� IMU660RA
// 鍙傛暟璇存槑     void
// 杩斿洖鍙傛暟     uint8           1-鍒濆�鍖栧け璐� 0-鍒濆�鍖栨垚鍔�
// 浣跨敤绀轰緥     imu660ra_init();
// 澶囨敞淇℃伅
//-------------------------------------------------------------------------------------------------------------------
uint8 imu660ra_init (void)
{
    uint8 return_state = 0;
    system_delay_ms(20);                                                        // 绛夊緟璁惧�涓婄數鎴愬姛
#if IMU660RA_USE_IIC
#if IMU660RA_USE_SOFT_IIC
    soft_iic_init(&imu660ra_iic_struct, IMU660RA_DEV_ADDR, IMU660RA_SOFT_IIC_DELAY, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // 閰嶇疆 IMU660RA 鐨� IIC 绔�彛
#else
    iic_init(IMU660RA_IIC_INDEX, IMU660RA_DEV_ADDR, IMU660RA_IIC_SPEED, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // 閰嶇疆 IMU660RA 鐨� IIC 绔�彛
#endif
#else
    spi_init(IMU660RA_SPI, SPI_MODE0, IMU660RA_SPI_SPEED, IMU660RA_SPC_PIN, IMU660RA_SDI_PIN, IMU660RA_SDO_PIN, SPI_CS_NULL);   // 閰嶇疆 IMU660RA 鐨� SPI 绔�彛
    gpio_init(IMU660RA_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);                  // 閰嶇疆 IMU660RA 鐨凜S绔�彛
    imu660ra_read_register(IMU660RA_CHIP_ID);                                   // 璇诲彇涓€涓嬭�澶嘔D 灏嗚�澶囪�缃�负SPI妯″紡
#endif
    do{
        if(imu660ra_self_check())                                               // IMU660RA 鑷��
        {
            // 濡傛灉绋嬪簭鍦ㄨ緭鍑轰簡鏂�█淇℃伅 骞朵笖鎻愮ず鍑洪敊浣嶇疆鍦ㄨ繖閲�
            // 閭ｄ箞灏辨槸 IMU660RA 鑷��鍑洪敊骞惰秴鏃堕€€鍑轰簡
            // 妫€鏌ヤ竴涓嬫帴绾挎湁娌℃湁闂�� 濡傛灉娌￠棶棰樺彲鑳藉氨鏄�潖浜�
            zf_log(0, "imu660ra self check error.");
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                       // 鍏抽棴楂樼骇鐪佺數妯″紡
        system_delay_ms(1);
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x00);                      // 寮€濮嬪�妯″潡杩涜�鍒濆�鍖栭厤缃�
        imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));   // 杈撳嚭閰嶇疆鏂囦欢
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x01);                      // 鍒濆�鍖栭厤缃�粨鏉�
        system_delay_ms(20);
        if(1 != imu660ra_read_register(IMU660RA_INT_STA))                       // 妫€鏌ユ槸鍚﹂厤缃�畬鎴�
        {
            // 濡傛灉绋嬪簭鍦ㄨ緭鍑轰簡鏂�█淇℃伅 骞朵笖鎻愮ず鍑洪敊浣嶇疆鍦ㄨ繖閲�
            // 閭ｄ箞灏辨槸 IMU660RA 閰嶇疆鍒濆�鍖栨枃浠跺嚭閿欎簡
            // 妫€鏌ヤ竴涓嬫帴绾挎湁娌℃湁闂�� 濡傛灉娌￠棶棰樺彲鑳藉氨鏄�潖浜�
            zf_log(0, "imu660ra init error.");
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CTRL, 0x0E);                       // 寮€鍚�€ц兘妯″紡  浣胯兘闄€铻轰华銆佸姞閫熷害銆佹俯搴︿紶鎰熷櫒
        imu660ra_write_register(IMU660RA_ACC_CONF, 0xA7);                       // 鍔犻€熷害閲囬泦閰嶇疆 鎬ц兘妯″紡 姝ｅ父閲囬泦 50Hz  閲囨牱棰戠巼
        imu660ra_write_register(IMU660RA_GYR_CONF, 0xA9);                       // 闄€铻轰华閲囬泦閰嶇疆 鎬ц兘妯″紡 姝ｅ父閲囬泦 200Hz 閲囨牱棰戠巼

        // IMU660RA_ACC_SAMPLE 瀵勫瓨鍣�
        // 璁剧疆涓� 0x00 鍔犻€熷害璁￠噺绋嬩负 卤2  g   鑾峰彇鍒扮殑鍔犻€熷害璁℃暟鎹�櫎浠� 16384  鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� (g 浠ｈ〃閲嶅姏鍔犻€熷害 鐗╃悊瀛﹀悕璇� 涓€鑸�儏鍐典笅 g 鍙� 9.8 m/s^2 涓烘爣鍑嗗€�)
        // 璁剧疆涓� 0x01 鍔犻€熷害璁￠噺绋嬩负 卤4  g   鑾峰彇鍒扮殑鍔犻€熷害璁℃暟鎹�櫎浠� 8192   鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� (g 浠ｈ〃閲嶅姏鍔犻€熷害 鐗╃悊瀛﹀悕璇� 涓€鑸�儏鍐典笅 g 鍙� 9.8 m/s^2 涓烘爣鍑嗗€�)
        // 璁剧疆涓� 0x02 鍔犻€熷害璁￠噺绋嬩负 卤8  g   鑾峰彇鍒扮殑鍔犻€熷害璁℃暟鎹�櫎浠� 4096   鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� (g 浠ｈ〃閲嶅姏鍔犻€熷害 鐗╃悊瀛﹀悕璇� 涓€鑸�儏鍐典笅 g 鍙� 9.8 m/s^2 涓烘爣鍑嗗€�)
        // 璁剧疆涓� 0x03 鍔犻€熷害璁￠噺绋嬩负 卤16 g   鑾峰彇鍒扮殑鍔犻€熷害璁℃暟鎹�櫎浠� 2048   鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� (g 浠ｈ〃閲嶅姏鍔犻€熷害 鐗╃悊瀛﹀悕璇� 涓€鑸�儏鍐典笅 g 鍙� 9.8 m/s^2 涓烘爣鍑嗗€�)
        switch(IMU660RA_ACC_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU660RA_ACC_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_2G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x00);
                imu660ra_transition_factor[0] = 16384;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_4G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x01);
                imu660ra_transition_factor[0] = 8192;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_8G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x02);
                imu660ra_transition_factor[0] = 4096;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_16G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x03);
                imu660ra_transition_factor[0] = 2048;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        // IMU660RA_GYR_RANGE 瀵勫瓨鍣�
        // 璁剧疆涓� 0x04 闄€铻轰华閲忕▼涓� 卤125  dps    鑾峰彇鍒扮殑闄€铻轰华鏁版嵁闄や互 262.4   鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� 鍗曚綅涓� 掳/s
        // 璁剧疆涓� 0x03 闄€铻轰华閲忕▼涓� 卤250  dps    鑾峰彇鍒扮殑闄€铻轰华鏁版嵁闄や互 131.2   鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� 鍗曚綅涓� 掳/s
        // 璁剧疆涓� 0x02 闄€铻轰华閲忕▼涓� 卤500  dps    鑾峰彇鍒扮殑闄€铻轰华鏁版嵁闄や互 65.6    鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� 鍗曚綅涓� 掳/s
        // 璁剧疆涓� 0x01 闄€铻轰华閲忕▼涓� 卤1000 dps    鑾峰彇鍒扮殑闄€铻轰华鏁版嵁闄や互 32.8    鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� 鍗曚綅涓� 掳/s
        // 璁剧疆涓� 0x00 闄€铻轰华閲忕▼涓� 卤2000 dps    鑾峰彇鍒扮殑闄€铻轰华鏁版嵁闄や互 16.4    鍙�互杞�寲涓哄甫鐗╃悊鍗曚綅鐨勬暟鎹� 鍗曚綅涓� 掳/s
        switch(IMU660RA_GYRO_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU660RA_GYRO_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_125DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x04);
                imu660ra_transition_factor[1] = 262.4;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_250DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x03);
                imu660ra_transition_factor[1] = 131.2;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_500DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x02);
                imu660ra_transition_factor[1] = 65.6;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_1000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x01);
                imu660ra_transition_factor[1] = 32.8;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_2000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x00);
                imu660ra_transition_factor[1] = 16.4;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }
    }while(0);
    return return_state;
}


