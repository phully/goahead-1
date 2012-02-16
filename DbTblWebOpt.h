/*
###############################################################
# FileName      	: DbTblWebOpt.h
# Version           : 3.0
# Create			:
# Function Describe : DbTblWebOpt.c 头文件
# Modified 			: 
###############################################################
*/

#ifndef _DBTBLWEBOPT_H_ 
#define _DBTBLWEBOPT_H_


/*Web 初始化表数据显示*/
extern int aspSysStatusDisplay(int eid, webs_t wp, int argc, char_t **argv);


/****************************************************************************************/


// 设置和获取OSD参数
extern void FormOSD(webs_t wp,char_t *path,char_t *query);
// 设置和获取OSD参数
extern void FormPrivacy(webs_t wp,char_t *path,char_t *query);
// 系统操作
extern void FormSystem(webs_t wp,char_t *path,char_t *query);
// 固件上传
extern void upldForm(webs_t wp, char_t * path, char_t * query);

#endif
