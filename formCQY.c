/*
 * umui.c -- User Management GoForm Processing
 *
 * Copyright (c) GoAhead Software Inc., 1995-2000. All Rights Reserved.
 *
 * See the file "license.txt" for usage and redistribution license requirements
 *
 *	$Id: umui.c,v 1.2 2002/10/24 14:44:50 bporter Exp $
 */

/******************************** Description *********************************/

/*
 *	This module provides GoForm functions for User management
 */

/********************************* Includes ***********************************/

#include	"wsIntrn.h"



/********************************* Defines ************************************/

#define		NONE_OPTION		T("<NONE>")
#define		MSG_START		T("<body><h2>")
#define		MSG_END			T("</h2></body>")
#define   IMAGE_FIFO  "/dev/Fifo_WTE"



/**************************** Forward Declarations ****************************/


static void formTimeSet(webs_t wp, char_t *path, char_t *query);                         // ±º‰…Ë÷√

/*********************************** Code *************************************/
/*
 *	Set up the User Management form handlers
 */



void formDefineMyForm(void)
{

	websFormDefine(T("FTimeSet"), formTimeSet);

	//printf("fsafjdl\n");
}

/******************************************************************************/
/*
 *  Message start and end convenience functions
 */
 

 
static void formTimeSet(webs_t wp, char_t *path, char_t *query)
{
	char_t *pszOperate = NULL;
  char_t *computeTimeSet = "2011-11-3 16:51:00";
  char_t *NTPaddress=NULL;
	pszOperate = websGetVar(wp, T("Operate"), T(""));

	// get osd para
	if (0 == gstricmp(pszOperate, T("get"))) {
		  
	   
			websWrite(wp, T("HTTP/1.0 200 OK\n"));
			websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
			websWrite(wp, T("Pragma: no-cache\n"));
			websWrite(wp, T("Cache-control: no-cache\n"));
			websWrite(wp, T("Content-Type: text/xml\n"));
			websWrite(wp, T("\n"));
			
			websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
			websWrite(wp, T("<TimeSet>"));
			websWrite(wp, T("<LinuxSysTime>%d</LinuxSysTime>"),computeTimeSet);
			websWrite(wp, T("</TimeSet>"));
			printf("return OK!\n");
			websDone(wp, 200);
	}
	// set osd
	else if (0 == gstricmp(pszOperate, T("set"))) {

		NTPaddress = websGetVar(wp, T("NTPaddress"), T(""));
		printf("%s\n",NTPaddress);
    
    FILE *NTPfp;
    char NTPbuf[100];
    if((NTPfp=fopen("/home/NTPaddr.txt","w"))==NULL)
    {
    	printf("can not open file!\n");
    }
    else
    {
    memset(NTPbuf,0,sizeof(NTPbuf));
    snprintf(NTPbuf,sizeof(NTPbuf),"\ address=%s\n",NTPaddress);
    fputs(NTPbuf,NTPfp);
    fclose(NTPfp);
    printf("%s\n",NTPbuf);
    }
		websWrite(wp,T("0"));	
		websDone(wp, 200);
	}
	
}
 










static void	websMsgStart(webs_t wp)
{
	websWrite(wp, MSG_START);
}

static void	websMsgEnd(webs_t wp)
{
	websWrite(wp, MSG_END);
}

/******************************************************************************/

