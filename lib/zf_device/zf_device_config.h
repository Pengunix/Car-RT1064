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
* 鏂囦欢鍚嶇О          zf_device_config
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

#ifndef _zf_device_config_h_
#define _zf_device_config_h_

extern const unsigned char imu660ra_config_file[8192];
extern const unsigned char dl1b_config_file[135];

unsigned char   mt9v03x_set_config_sccb         (void *soft_iic_obj, short int buff[10][2]);
unsigned char   mt9v03x_set_exposure_time_sccb  (unsigned short int light);
unsigned char   mt9v03x_set_reg_sccb            (unsigned char addr, unsigned short int data);

unsigned char   scc8660_set_config_sccb         (void *soft_iic_obj, short int buff[11][2]);
unsigned char   scc8660_set_brightness_sccb     (unsigned short int brightness);
unsigned char   scc8660_set_manual_wb_sccb      (unsigned short int manual_wb);
unsigned char   scc8660_set_reg_sccb            (unsigned char reg, unsigned short int data);

#endif

