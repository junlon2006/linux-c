#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static u_int32_t __get_string_hashcode(const char *str) {
    u_int32_t code = 0;
    char c;
    if (NULL == str) {
        return 0;
    }
    while ((c = *str++) != '\0') {
        code *= 31;
        code += c;
    }
    return code;
}

enum {
    wakeup_ = 0,
    sleep_,
    volume_up_,
    volume_down_,
    net_connect_,
    net_connect_exit_,
    power_on_,
    power_off_,
    windspeed_auto_,
    windspeed_mute_,
    windspeed_lowest_,
    windspeed_low_,
    windspeed_middle_,
    windspeed_high_,
    windspeed_highest_,
    windspeed_inc_,
    windspeed_dec_,
    temp_set_16_,
    temp_set_17_,
    temp_set_18_,
    temp_set_19_,
    temp_set_20_,
    temp_set_21_,
    temp_set_22_,
    temp_set_23_,
    temp_set_24_,
    temp_set_25_,
    temp_set_26_,
    temp_set_27_,
    temp_set_28_,
    temp_set_29_,
    temp_set_30_,
    temp_set_31_,
    temp_set_32_,
    temp_dec_1_,
    temp_inc_1_,
    mode_cool_,
    mode_hot_,
    mode_wet_,
    mode_wind_,
    wind_swing_left_right_on_,
    wind_swing_left_right_off_,
    wind_swing_up_down_on_,
    wind_swing_up_down_off_,
    extras_screen_open_,
    extras_screen_close_,
    sleep_mode_open_,
    sleep_mode_close_,
    energy_saving_open_,
    energy_saving_close_,
    humidifying_open_,
    humidifying_close_,
    curtain_open_,
    curtain_close_,
    come_back_,
    go_out_,
    good_night_,
    tv_open_,
    tv_close_,
    light_on_,
    light_off_,
};

static const char* g_nlu_content_str[] = {
  [wakeup_] = "{\"asr_recongize\":\"你好魔方\",\"text\":\"你好魔方\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ENTER_REGCON\",\"operands\":\"ATTR_ASR\"}]}},\"general\":{\"type\":\"T\",\"text\":\"你好请吩咐\",\"pcm\":\"2.pcm\",\"pcm_fail\":\"1.pcm\"}}",
  [sleep_] =  "{\"asr_recongize\":\"再见\",\"text\":\"再见\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ENTER_WAKEUP\",\"operands\":\"ATTR_ASR\"}]}},\"general\":{\"type\":\"T\",\"text\":\"拜拜\",\"pcm\":\"51.pcm\"}}",
  [volume_up_] = "{\"asr_recongize\":\"增大音量\",\"text\":\"增大音量\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_INCREASE\",\"operands\":\"ATTR_VOLUME\"}]}},\"general\":{\"type\":\"T\",\"text\":\"音量已增大\",\"text_fail\":\"已是最大音量\",\"pcm\":\"61.pcm\",\"pcm_fail\":\"62.pcm\"}}",
  [volume_down_] = "{\"asr_recongize\":\"减小音量\",\"text\":\"减小音量\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_DECREASE\",\"operands\":\"ATTR_VOLUME\"}]}},\"general\":{\"type\":\"T\",\"text\":\"音量已减小\",\"text_fail\":\"已是最小音量\",\"pcm\":\"61.pcm\",\"pcm_fail\":\"62.pcm\"}}",
  [net_connect_] = "{\"asr_recongize\":\"我要联网\",\"text\":\"我要联网\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_NETWORK\"}]}},\"general\":{\"type\":\"T\",\"text\":\"好的，请按照手机app指示进行联网操作\",\"pcm\":\"58.pcm\"}}",
  [net_connect_exit_] = "{\"asr_recongize\":\"退出配网\",\"text\":\"退出配网\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_CANCEL\",\"operands\":\"ATTR_NETWORK\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已退出配网模式\",\"pcm\":\"59.pcm\"}}",
  [power_on_] = "{\"asr_recongize\":\"打开空调\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_OPEN\",\"deviceType\":\"OBJ_AC\",\"deviceExpr\":\"空调\"}]}},\"general\":{\"type\":\"T\",\"text\":\"空调已开机\",\"pcm\":\"63.pcm\",\"pcm_cool\":\"3.pcm\",\"pcm_heat\":\"4.pcm\",\"pcm_dry\":\"5.pcm\",\"pcm_prefan\":\"6.pcm\",\"pcm_auto\":\"7.pcm\"}}",
  [power_off_] = "{\"asr_recongize\":\"关闭空调\",\"service\":\"cn.yunzhisheng.setting\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_CLOSE\",\"deviceType\":\"OBJ_AC\",\"deviceExpr\":\"空调\"}]}},\"general\":{\"type\":\"T\",\"text\":\"空调已关机\",\"pcm\":\"8.pcm\"}}",
  [windspeed_auto_] = "{\"asr_recongize\":\"自动风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_AUTO\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为自动风\",\"pcm\":\"42.pcm\"}}",
  [windspeed_mute_] = "{\"asr_recongize\":\"静音风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_MUTE\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为静音风\",\"pcm\":\"40.pcm\"}}",
  [windspeed_lowest_] = "{\"asr_recongize\":\"最小风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_MIN\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_MIN\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为最小风\",\"pcm\":\"41.pcm\"}}",
  [windspeed_low_] = "{\"asr_recongize\":\"低速风。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_LOW\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为低速风\",\"pcm\":\"36.pcm\"}}",
  [windspeed_middle_] = "{\"asr_recongize\":\"中速风。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_MEDIUM\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为中等风\",\"pcm\":\"35.pcm\"}}",
  [windspeed_high_] = "{\"asr_recongize\":\"高速风。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_HIGH\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为高速风\",\"pcm\":\"34.pcm\"}}",
  [windspeed_highest_] = "{\"asr_recongize\":\"最大风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_MAX\",\"operands\":\"ATTR_WIND_SPEED\",\"value\":\"WIND_SPEED_MAX\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为最大风\",\"pcm\":\"38.pcm\"}}",
  [windspeed_inc_] = "{\"asr_recongize\":\"增大风速。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_INCREASE\",\"operands\":\"ATTR_WIND_SPEED\"}]}},\"general\":{\"type\":\"T\",\"text\":\"风速已增大\",\"pcm\":\"37.pcm\"}}",
  [windspeed_dec_] = "{\"asr_recongize\":\"减小风速。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_DECREASE\",\"operands\":\"ATTR_WIND_SPEED\"}]}},\"general\":{\"type\":\"T\",\"text\":\"风速已减小\",\"pcm\":\"39.pcm\"}}",
  [temp_set_16_] = "{\"asr_recongize\":\"十六度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"16\",\"valueExpr\":\"16\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为16度\",\"pcm\":\"9.pcm\"}}",
  [temp_set_17_] = "{\"asr_recongize\":\"十七度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"17\",\"valueExpr\":\"17\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为17度\",\"pcm\":\"10.pcm\"}}",
  [temp_set_18_] = "{\"asr_recongize\":\"十八度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"18\",\"valueExpr\":\"18\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为18度\",\"pcm\":\"11.pcm\"}}",
  [temp_set_19_] = "{\"asr_recongize\":\"十九度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"19\",\"valueExpr\":\"19\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为19度\",\"pcm\":\"12.pcm\"}}",
  [temp_set_20_] = "{\"asr_recongize\":\"二十度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"20\",\"valueExpr\":\"20\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为20度\",\"pcm\":\"13.pcm\"}}",
  [temp_set_21_] = "{\"asr_recongize\":\"二十一度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"21\",\"valueExpr\":\"21\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为21度\",\"pcm\":\"14.pcm\"}}",
  [temp_set_22_] = "{\"asr_recongize\":\"二十二度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"22\",\"valueExpr\":\"22\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为22度\",\"pcm\":\"15.pcm\"}}",
  [temp_set_23_] = "{\"asr_recongize\":\"二十三度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"23\",\"valueExpr\":\"23\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为23度\",\"pcm\":\"16.pcm\"}}",
  [temp_set_24_] = "{\"asr_recongize\":\"二十四度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"24\",\"valueExpr\":\"24\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为24度\",\"pcm\":\"17.pcm\"}}",
  [temp_set_25_] = "{\"asr_recongize\":\"二十五度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"25\",\"valueExpr\":\"25\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为25度\",\"pcm\":\"18.pcm\"}}",
  [temp_set_26_] = "{\"asr_recongize\":\"二十六度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"26\",\"valueExpr\":\"26\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为26度\",\"pcm\":\"19.pcm\"}}",
  [temp_set_27_] = "{\"asr_recongize\":\"二十七度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"27\",\"valueExpr\":\"27\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为27度\",\"pcm\":\"20.pcm\"}}",
  [temp_set_28_] = "{\"asr_recongize\":\"二十八度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"28\",\"valueExpr\":\"28\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为28度\",\"pcm\":\"21.pcm\"}}",
  [temp_set_29_] = "{\"asr_recongize\":\"二十九度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"29\",\"valueExpr\":\"29\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为29度\",\"pcm\":\"22.pcm\"}}",
  [temp_set_30_] = "{\"asr_recongize\":\"三十度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"30\",\"valueExpr\":\"30\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为30度\",\"pcm\":\"23.pcm\"}}",
  [temp_set_31_] = "{\"asr_recongize\":\"三十一度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"31\",\"valueExpr\":\"31\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为31度\",\"pcm\":\"24.pcm\"}}",
  [temp_set_32_] = "{\"asr_recongize\":\"三十二度。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_TEMPERATURE\",\"value\":\"32\",\"valueExpr\":\"32\",\"datatype\":\"int\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为32度\",\"pcm\":\"25.pcm\"}}",
  [temp_dec_1_] = "{\"asr_recongize\":\"温度有点高。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_DECREASE\",\"operands\":\"ATTR_TEMPERATURE\",\"valueDelta\":\"VALUE_DELTA_SMALL\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已为您调低一度\",\"pcm\":\"27.pcm\"}}",
  [temp_inc_1_] = "{\"asr_recongize\":\"温度有点低。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_INCREASE\",\"operands\":\"ATTR_TEMPERATURE\",\"valueDelta\":\"VALUE_DELTA_SMALL\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已为您调高一度\",\"pcm\":\"26.pcm\"}}",
  [mode_cool_] = "{\"asr_recongize\":\"制冷模式。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"MODE_COOL\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为制冷模式\",\"pcm\":\"30.pcm\"}}",
  [mode_hot_] = "{\"asr_recongize\":\"制热模式。\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"MODE_HEAT\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为制热模式\",\"pcm\":\"33.pcm\"}}",
  [mode_wet_] = "{\"asr_recongize\":\"抽湿模式。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"MODE_WETTED\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为抽湿模式\",\"pcm\":\"31.pcm\"}}",
  [mode_wind_] = "{\"asr_recongize\":\"送风模式。\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"MODE_AIR_SUPPLY\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已设为送风模式\",\"pcm\":\"32.pcm\"}}",
  [wind_swing_left_right_on_] = "{\"asr_recongize\":\"打开左右摆风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_DIRECTION\",\"value\":\"WIND_SWING_LEFT_RIGHT\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开左右摆风\",\"pcm\":\"43.pcm\"}}",
  [wind_swing_left_right_off_] = "{\"asr_recongize\":\"关闭左右摆风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_UNSET\",\"operands\":\"ATTR_WIND_DIRECTION\",\"value\":\"WIND_SWING_LEFT_RIGHT\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭左右摆风\",\"pcm\":\"44.pcm\"}}",
  [wind_swing_up_down_on_] = "{\"asr_recongize\":\"打开上下摆风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_WIND_DIRECTION\",\"value\":\"WIND_SWING_UP_DOWN\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开上下摆风\",\"pcm\":\"45.pcm\"}}",
  [wind_swing_up_down_off_] = "{\"asr_recongize\":\"关闭上下摆风\",\"service\":\"cn.yunzhisheng.setting.air\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_UNSET\",\"operands\":\"ATTR_WIND_DIRECTION\",\"value\":\"WIND_SWING_UP_DOWN\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭上下摆风\",\"pcm\":\"46.pcm\"}}",
  [extras_screen_open_] = "{\"asr_recongize\":\"打开屏显\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"OPEN_SCREEN\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开屏显。\",\"pcm\":\"54.pcm\"}}",
  [extras_screen_close_] = "{\"asr_recongize\":\"关闭屏显\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"CLOSE_SCREEN\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭屏显。\",\"pcm\":\"55.pcm\"}}",
  [sleep_mode_open_] = "{\"asr_recongize\":\"打开睡眠\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"OPEN_SLEEP\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开睡眠模式。\",\"pcm\":\"49.pcm\"}}",
  [sleep_mode_close_] = "{\"asr_recongize\":\"关闭睡眠\",\"service\":\"cn.yunzhisheng.setting.thermostat\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_MODE\",\"value\":\"CLOSE_SLEEP\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭睡眠模式。\",\"pcm\":\"50.pcm\"}}",
  [energy_saving_open_] = "{\"asr_recongize\":\"打开节能\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"OPEN_ENERGY\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开节能。\",\"pcm\":\"56.pcm\"}}",
  [energy_saving_close_] = "{\"asr_recongize\":\"关闭节能\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"CLOSE_ENERGY\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭节能。\",\"pcm\":\"57.pcm\"}}",
  [humidifying_open_] = "{\"asr_recongize\":\"打开除湿\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"OPEN_HUMID\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已打开除湿。\",\"pcm\":\"52.pcm\"}}",
  [humidifying_close_] = "{\"asr_recongize\":\"关闭除湿\",\"service\":\"cn.yunzhisheng.setting.extras\",\"semantic\":{\"intent\":{\"operations\":[{\"operator\":\"ACT_SET\",\"operands\":\"ATTR_EXTRAS\",\"value\":\"CLOSE_HUMID\"}]}},\"general\":{\"type\":\"T\",\"text\":\"已关闭除湿。\",\"pcm\":\"53.pcm\"}}",
  
  /* unsupport now, just skip behind */
  [curtain_open_] = "{}",
  [curtain_close_] = "{}",
  [come_back_] = "{}",
  [go_out_] = "{}",
  [tv_open_] = "{}",
  [good_night_] = "{}",
  [tv_close_] = "{}",
  [light_on_] = "{}",
  [light_off_] = "{}",
};

typedef struct {
    u_int32_t key_word_hash_code;  /* 存放识别词汇对应的hashcode */
    u_int8_t  nlu_content_str_index; /* 存放nlu映射表中的索引，实现多个识别词汇可对应同一个nlu，暂支持256条，如果不够换short */
    char      *hash_collision_orginal_str /* 类似Java equal，当hash碰撞时，直接比较字符串，没有碰撞设置为NULL */;
} uni_nlu_content_mapping_t;

static const uni_nlu_content_mapping_t g_nlu_content_mapping[] = {
    {10874671 /*你好魔方*/, wakeup_, NULL},
    {3455339387 /*开机*/, power_on_, NULL},
    {547903228 /*打开空调*/, power_on_, NULL},
    {3406065073 /*关机*/, power_off_, NULL},
    {3901797551 /*关闭空调*/, power_off_, NULL},
    {1064005821 /*十六度*/, temp_set_16_, NULL},
    {1081225019 /*十七度*/, temp_set_17_, NULL},
    {1063946239 /*十八度*/, temp_set_18_, NULL},
    {1082923106 /*十九度*/, temp_set_19_, NULL},
    {872229998 /*二十度*/, temp_set_20_, NULL},
    {20093160 /*二十一度*/, temp_set_21_, NULL},
    {22297694 /*二十二度*/, temp_set_22_, NULL},
    {20361279 /*二十三度*/, temp_set_23_, NULL},
    {22744559 /*二十四度*/, temp_set_24_, NULL},
    {22536022 /*二十五度*/, temp_set_25_, NULL},
    {2963335 /*二十六度*/, temp_set_26_, NULL},
    {20182533 /*二十七度*/, temp_set_27_, NULL},
    {2903753 /*二十八度*/, temp_set_28_, NULL},
    {21880620 /*二十九度*/, temp_set_29_, NULL},
    {3314032877 /*三十度*/, temp_set_30_, NULL},
    {4203536393 /*三十一度*/, temp_set_31_, NULL},
    {4205740927 /*三十二度*/, temp_set_32_, NULL},
    {2207943570 /*降低温度*/, temp_dec_1_, NULL},
    {282293386 /*太热了*/, temp_dec_1_, NULL},
    {1368820308 /*调低温度*/, temp_dec_1_, NULL},
    {1491223089 /*升高温度*/, temp_inc_1_, NULL},
    {228103557 /*太冷了*/, temp_inc_1_, NULL},
    {4195737141 /*调高温度*/, temp_inc_1_, NULL},
    {102066620 /*自动风*/, windspeed_auto_, NULL},
    {208278716 /*静音风*/, windspeed_mute_, NULL},
    {3075187002 /*最小风*/, windspeed_lowest_, NULL},
    {3684108737 /*低速风*/, windspeed_low_, NULL},
    {3715921948 /*低风挡*/, windspeed_low_, NULL},
    {1007834693 /*中速风*/, windspeed_middle_, NULL},
    {1039647904 /*中风挡*/, windspeed_middle_, NULL},
    {2216058274 /*高速风*/, windspeed_high_, NULL},
    {2247871485 /*高风挡*/, windspeed_high_, NULL},
    {423899681 /*强力风*/, windspeed_high_, NULL},
    {3064819734 /*最大风*/, windspeed_highest_, NULL},
    {618440035 /*提高风速*/, windspeed_inc_, NULL},
    {1787696865 /*加大风速*/, windspeed_inc_, NULL},
    {1542981611 /*减小风速*/, windspeed_dec_, NULL},
    {2273634764 /*降低风速*/, windspeed_dec_, NULL},
    {1548051164 /*制冷模式*/, mode_cool_, NULL},
    {1009543607 /*制热模式*/, mode_hot_, NULL},
    {1738937999 /*加热模式*/, mode_hot_, NULL},
    {509877361 /*除湿模式*/, mode_wet_, NULL},
    {3096598218 /*通风模式*/, mode_wind_, NULL},
    {3714468547 /*送风模式*/, mode_wind_, NULL},
    {1068266126 /*左右摆风*/, wind_swing_left_right_on_, NULL},
    {1061980225 /*左右扫风*/, wind_swing_left_right_on_, NULL},
    {70831463 /*打开左右摆风*/, wind_swing_left_right_on_, NULL},
    {64545562 /*打开左右扫风*/, wind_swing_left_right_on_, NULL},
    {2342139977 /*开启左右摆风*/, wind_swing_left_right_on_, NULL},
    {2335854076 /*开启左右扫风*/, wind_swing_left_right_on_, NULL},
    {3735214298 /*关闭左右摆风*/, wind_swing_left_right_off_, NULL},
    {3728928397 /*关闭左右扫风*/, wind_swing_left_right_off_, NULL},
    {1941716777 /*停止左右摆风*/, wind_swing_left_right_off_, NULL},
    {1935430876 /*停止左右扫风*/, wind_swing_left_right_off_, NULL},
    {3752435482 /*上下摆风*/, wind_swing_up_down_on_, NULL},
    {2755000819 /*打开上下摆风*/, wind_swing_up_down_on_, NULL},
    {731342037 /*开启上下摆风*/, wind_swing_up_down_on_, NULL},
    {489275109 /*打开扫风*/, wind_swing_up_down_on_, NULL},
    {495561010 /*打开摆风*/, wind_swing_up_down_on_, NULL},
    {2124416358 /*关闭上下摆风*/, wind_swing_up_down_off_, NULL},
    {330918837 /*停止上下摆风*/, wind_swing_up_down_off_, NULL},
    {3843169432 /*关闭扫风*/, wind_swing_up_down_off_, NULL},
    {3849455333 /*关闭摆风*/, wind_swing_up_down_off_, NULL},
    {2314081396 /*停止摆风*/, wind_swing_up_down_off_, NULL},
    {536074649 /*打开睡眠*/, sleep_mode_open_, NULL},
    {1623869664 /*开始睡眠*/, sleep_mode_open_, NULL},
    {3889968972 /*关闭睡眠*/, sleep_mode_close_, NULL},
    {2354595035 /*停止睡眠*/, sleep_mode_close_, NULL},
    {546233595 /*打开节能*/, energy_saving_open_, NULL},
    {3900127918 /*关闭节能*/, energy_saving_close_, NULL},
    {496749474 /*打开屏显*/, extras_screen_open_, NULL},
    {3850643797 /*关闭屏显*/, extras_screen_close_, NULL},
    {615848419 /*提高音量*/, volume_up_, NULL},
    {1907004795 /*音量增大*/, volume_up_, NULL},
    {2000972603 /*增大音量*/, volume_up_, NULL},
    {1540389995 /*减小音量*/, volume_down_, NULL},
    {2271043148 /*降低音量*/, volume_down_, NULL},
    {1881623211 /*音量减小*/, volume_down_, NULL},
    {3935581027 /*关闭语音*/, sleep_, NULL},
    {712568611 /*语音关闭*/, sleep_, NULL},
    {377224549 /*关掉语音*/, sleep_, NULL},
    {402639023 /*去休息吧*/, sleep_, NULL},
    {3514443630 /*退下*/, sleep_, NULL},
    {3405858742 /*再见*/, sleep_, NULL},
    {3414437100 /*取消*/, sleep_, NULL},
    {3537025218 /*闭嘴*/, sleep_, NULL},
    {3910506702 /*别烦了*/, sleep_, NULL},
    {461239626 /*打开加湿*/, humidifying_open_, NULL},
    {2004464044 /*开启加湿*/, humidifying_open_, NULL},
    {2279760012 /*停止加湿*/, humidifying_close_, NULL},
    {804492948 /*帮我联网*/, net_connect_, NULL},
    {1445242841 /*退出配网*/, net_connect_exit_, NULL},
    {547781450 /*打开窗帘*/, curtain_open_, NULL},
    {563332352 /*打开纱帘*/, curtain_open_, NULL},
    {3901675773 /*关闭窗帘*/, curtain_close_, NULL},
    {3917226675 /*关闭纱帘*/, curtain_close_, NULL},
    {2292503518 /*回家模式*/, come_back_, NULL},
    {1874681499 /*我回来了*/, come_back_, NULL},
    {416685895 /*我出去了*/, go_out_, NULL},
    {4071210650 /*我出去了*/, go_out_, NULL},
    {3710858845 /*我要睡觉了*/, good_night_, NULL},
    {2675673318 /*我想睡觉*/, good_night_, NULL},
    {3986191929 /*睡眠模式*/, good_night_, NULL},
    {528360056 /*打开电视*/, tv_open_, NULL},
    {847824046 /*我想看电视*/, tv_open_, NULL},
    {1503287826 /*关电视*/, tv_close_, NULL},
    {3882254379 /*关闭电视*/, tv_close_, NULL},
    {3455339500 /*开灯*/, light_on_, NULL},
    {846245084 /*打开床头灯*/, light_on_, NULL},
    {3406065186 /*关灯*/, light_off_, NULL},
    {1563076265 /*关闭灯*/, light_off_, NULL},
    {2887814729 /*关闭床头灯*/, light_off_, NULL},
};

static const char* __get_nlu_by_key_word(const char *key_word) {
    u_int32_t hashCode = __get_string_hashcode(key_word);
    int hashTableSize = sizeof(g_nlu_content_mapping) / sizeof(g_nlu_content_mapping[0]);
    int i;

    for (i = 0; i < hashTableSize; i++) {
        /* find same hashcode as keyword's */
        if (hashCode == g_nlu_content_mapping[i].key_word_hash_code) {
            /* return immediately when no hash collision */
            if (NULL == g_nlu_content_mapping[i].hash_collision_orginal_str) {
                return g_nlu_content_str[g_nlu_content_mapping[i].nlu_content_str_index];
            }
             /* return when key_word equals hash_collision_orginal_str */
            if (0 == strcmp(key_word, g_nlu_content_mapping[i].hash_collision_orginal_str)) {
                return g_nlu_content_str[g_nlu_content_mapping[i].nlu_content_str_index];
            }
        }
    }
    return NULL;
}

static void __lasr_result_parse(char* asr_result, float *score, char *key_word) {
    int i = 0;
    int index;
    /* asr result string format: "%d <s> %s </s> \n%f\n" */
    char *p = asr_result + 9; //9 meams the offset of keyword, the length of "%d <s> "
    char c;
    while ((c = *p++) != '<') {
        if (c != ' ') {
            key_word[i++] = c;
        }
    }
    key_word[i] = '\0';
    while (*p++ != '\n');
    *score = strtof(p, NULL);
}

static const char* __get_key_word_by_asr_result(char* asr_result, float *score, char *key_word_buf) {
    if (NULL == asr_result || NULL == score) {
        return NULL;
    }
    __lasr_result_parse(asr_result, score, key_word_buf);
    return __get_nlu_by_key_word(key_word_buf);
}

int main(int argc, char *argv[]) {
    char key_word[64] = {0,};
    float score = -100;
    
    printf("%s\n", __get_key_word_by_asr_result("4239 <s> 你好 魔方 </s> \n8.91\n", &score, key_word));
    printf("keyword=%s\n", key_word);
    printf("score=%f\n", score);
    printf("code=%u\n", __get_string_hashcode("你好魔方"));

    return 0;
}