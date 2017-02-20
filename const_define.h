#ifndef CONST_DEFINE_H
#define CONST_DEFINE_H

#define COM1 "/dev/ttyS1"
#define COM2 "/dev/ttyS3"
#define COM5 "/dev/ttyS0"
#define COM6 "/dev/ttyS2"

#define ActionState_UNDO 150
#define ActionState_DONE 151

#define NOAction 100
#define ActionAControl 101
#define ActionBControl 103
#define ActionCControl 104
#define ActionDControl 105

#define MAX_POWER_VALUE 100
#define MIN_POWER_VALUE 0

#define EMERGENCY_STOP "紧急停机"
#define STATE_STANDBY "待机"
#define STATE_FAULT          "设备故障"
#define STATE_LOW_EFFICIENCY "热效率低"

#define MSG_AUTO_STATE_FAULT          "设备故障,无法执行操作"
#define MSG_AUTO_STATE_LOW_EFFICIENCY "热效率低,无法执行操作"

#define ActionAControl_TEXT "加料"
#define ActionBControl_TEXT "倒包"
#define ActionCControl_TEXT "捞渣"
#define ActionDControl_TEXT "搅拌"

#define UPLOAD_FILE_STATE_PROCESSING "正在上传"
#define UPLOAD_FILE_STATE_SUCCESS "上传成功"
#define UPLOAD_FILE_STATE_FAIL "上传失败"

#define File_Saved_TEXT "文件已保存"

#define TIME_START_TEXT "计时"
#define Start_TEXT "开始"
#define End_TEXT "停止"

#define Start_Record_TEXT "开始记录"
#define End_Record__TEXT "停止记录"

#define Step_TEXT "阶段"

#define Warning_Timer_TEXT "计时器报警!"
#define Warning_NO_FILENAME_TEXT "请输入工艺文件名称!"
#define Warning_NO_TIME_TEXT "请先输入定时时间!"

#define State_UNLOCK_TEXT  "未锁定"
#define State_LOCK_TEXT  "锁定"
#define State_LOCK_DISABLE_TEXT  "关闭"


#define State_NO_Warning_TEXT  "未报警"
#define State_Warning_TEXT  "报警"

#define PrePath QString("/root/program/file/")
#define UDISK_PATH_PREFIX "/media/root/"
#define UPDATE_TEMP_PATH "/root/program/temp/UpdateFile"

#define NET_PIC_PATH ":/new/png/wifi.png"
#define NETOFF_PIC_PATH ":/new/png/wifi_off.png"

#define UDISK_UNPLUGIN "未插入u盘"
#define NO_UPDATE_FILE_DETECT "未检测到更新文件"

#define UPDATE_PROCESSING "正在更新"
#define UPDATE_END "更新完成，请重启机器"

#define EMPTY_FILE "文件内容为空"

#define REBOOT_CHECK "确定重启?"
#endif // CONST_DEFINE_H
