﻿#ifndef CONST_DEFINE_H
#define CONST_DEFINE_H

#define ActionState_UNDO 150
#define ActionState_DONE 151

#define NOAction 100
#define ActionAControl 101
#define ActionBControl 103
#define ActionCControl 104
#define ActionDControl 105

#define ActionAControl_TEXT "加料"
#define ActionBControl_TEXT "倒包"
#define ActionCControl_TEXT "捞渣"
#define ActionDControl_TEXT "搅拌"

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

#define State_NO_Warning_TEXT  "未报警"
#define State_Warning_TEXT  "报警"

#define PrePath QString("/root/file/")

#endif // CONST_DEFINE_H
