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

#define NETWORK_FILE "/etc/network/interfaces"
#define IMAGE_FILE   "/etc/ambaipcam/IPC_Q313/config/UIImage.cfg"
#define IMAGE_FIFO   "/dev/Fifo_WTE"
#define ENCODE_FILE   "/etc/ambaipcam/IPC_Q313/config/Encode.cfg"
#define NTP_TIME    "/etc/ambaipcam/IPC_Q313/config/NTPaddr.txt"
#define CFG_UIENCODER "/etc/ambaipcam/IPC_Q313/config/UIEncoder.cfg"

/********************************* Defines ************************************/

#define		NONE_OPTION		T("<NONE>")
#define		MSG_START		T("<body><h2>")
#define		MSG_END			T("</h2></body>")
#define	WTA_IMAGE_QULITY_SET					0x01	//Í¼Ïñ
#define WTA_ENCODE_SET                0x03  //±àÂëÉèÖÃ

#define	WTA_IMGQU_HUA_SET						0x01	//É«¶È
#define	WTA_IMGQU_BRIGHT_SET					0x02	//ÁÁ¶È
#define	WTA_IMGQU_CONTRAST_SET				0x03	//¶Ô±È¶È
#define	WTA_IMGQU_SATURATION_SET				0x04	//±¥ºÍ¶È
#define	WTA_IMGQU_SHARP_SET					0x05	//Èñ¶È
#define	WTA_IMGQU_MCTF_FILTER_SET				0x06	//½µÔë
#define	WTA_IMGQU_FACTORY_SET					0x07	//»Ö¸´Ä¬ÈÏÉèÖÃ

#define	WTA_AE_METER_MODE_SET					0x08	//ÆØ¹âÄ£Ê½
#define	WTA_AE_EV_SET							0x09	//ÆØ¹â²¹³¥
#define	WTA_AE_SHUTTER_RANG_SET				0x0A	//¿ìÃÅ·¶Î§
#define	WTA_BACKLIGHT_SET						0x0B	//±³¹â²¹³¥
#define	WTA_ANTIFLICKER_SET						0x0C	//ÆµÉÁ

//---------------------±àÂë²ÎÊýÉèÖÃ-----------------
#define	WTA_ENCODER										0x04
//Ö¸Áî¸¨Öú²ÎÊý£¨Cmd_Para[0]£©
#define	WTA_ENCODER_BASEPARA					0x01	//»ù±¾²ÎÊýÉèÖÃ
#define	WTA_ENCODER_FRAMERATE					0x02	//Ö¡ÂÊ
#define	WTA_ENCODER_GOPFRAME					0x03	//IÖ¡¼ä¸ô
#define	WTA_ENCODER_BITRATE						0x04	//ÂëÁ÷¿ØÖÆ
//---------------------------------------------
#define	CAP_JPEG_TYPE									0x00
#define	CAP_RAW_TYPE									0x01
#define	MAX_SIZE_CAP_PACKEG           1024
//---------------------------------------------
#define	CMD_ACK_NOCOMMAND							0x01
#define	CMD_ACK_COMMANDOK							0x02
//-------------------------------------------------
#define	CMD_FIFO_OTE_ENCODECONF				0x01
#define	STREAM_ENABLE									0x01
#define	STREAM_DISABLE								0
//-------------------------------------------------
#define	SIZE_ACK_OVER									0
#define	SIZE_ACK_COMMANDHD						16
#define	VER_CUS_CONFGCOMD							1
#define	MAX_SIZE_CONFBUF							512
#define	MAX_SIZE_FIFO_ONVIF_ENCODE		16
#define	MAX_SIZE_FIFO_WEB_ENCODE		16

#define CPENCODE        20  //Òª¿¼µÄÂëÁ÷¸öÊý
#define	CPCOUNT					12	//Òª¿¼µÄ¸öÊý
FILE *imagefp;
FILE *encodefp;

typedef struct ui_exposure_set_s{
	int enable_ae;					//onvif 0-manual, 1-auto
	int exposure_mode;			//onvif window £¨AE_SPOT_METERING = 0,	AE_CENTER_METERING,  ÆØ¹âÄ£Ê½
													//AE_AVERAGE_METERING,	AE_CUSTOM_METERING,	AE_METERING_TYPE_NUMBER,
	int exposure_level;			//EV 0¡«8£¨-3¡«4£©              ÆØ¹â²¹³¢
	int	anti_flicker_mode;	//ANTI_FLICKER_50HZ			= 0,	ANTI_FLICKER_60HZ			= 1,
	
	int slow_shutter_enable;//0-disable, 1-enable     µç×Ó¿ìÃÅ ÂýËÙ
	
	int	shutter_time_min; 	//onvif 1~8000         µç×Ó¿ìÃÅ ×î¿ì
	int	shutter_time_max; 	//onvif 1~8000          µç×Ó¿ìÃÅ ×îÂýì
	int	shutter_time_fixed;	//onvif 1~8000
	
	int	sensor_gain_min;		//onvif   ISO_100	 = 0,	//0db
																	//ISO_150 = 3,
																	//ISO_200 = 6,	//6db
																	//ISO_300 = 9,
																	//ISO_400 = 12,	//12db
																	//ISO_600 = 15,
																	//ISO_800 = 18,	//18db
																	//ISO_1600 = 24,	//24db
																	//ISO_3200 = 30,	//30db
																	//ISO_6400 = 36,	//36db
																	//ISO_12800 = 42,	//42db
																	//ISO_25600 = 48,	//48db
																	//ISO_51200 = 54,	//54db
																	//ISO_102400 = 60,//60db
	int	sensor_gain_max;		//onvif Í¬ÉÏ
	int	sensor_gain_fixed;	//onvif Í¬ÉÏ
	
	int enable_autoiris;		//onvif 0-AURO_DCIRIS, 1-manual
	int iris_min;						//onvif
	int iris_max;						//onvif
	int iris;								//onvif 0dB-full_open, 1-5
}ui_exposure_set_t;

typedef struct ui_focus_set_s{
	int enable_af;					//onvif 0-manual, 1-auto
	int near_limit;					//onvif 
	int far_limit;					//onvif 
	int near;								//onvif 
	int far;								//onvif 
}ui_focus_set_t;

typedef struct ui_ircut_set_s{
	int enable_autoircut;		//onvif 0-manual, 1-auto
	int near_limit;					//onvif 
	int far_limit;					//onvif 
	int near;								//onvif 
	int far;								//onvif 
}ui_ircut_set_t;

typedef struct ui_whitebalance_set_s{
	int enable_awb;					//onvif  0-auto, 1-manual
	int Rgain;							//onvif 
	int Bgain;							//onvif  
}ui_whitebalance_set_t;

typedef struct ui_image_set_s{
	int backlight;					//onvif 0-disable, 1-enable  ±³¹â
	int color_style;				//0~3  IMG_COLOR_TV = 0,	IMG_COLOR_PC,	IMG_COLOR_STILL,	IMG_COLOR_CUSTOM,	IMG_COLOR_NUMBER,
	int color_hue;					//0~31 (-15 - +15)     É«¶È
	int brightness;					//onvif 0~255 (-255 - +255)   ÁÁ¶È
	int contrast;						//onvif 0~255 (unit = 64 £¬128 is X2 valid rang:0¡«256)  ¶Ô±È¶È
	int saturation;					//onvif 0~255 (unit = 64£¬128 is X2 valid rang:0¡«256)   ±¥ºÍ¶È
	int sharpness;					//onvif 0~255 (unit = 128£¬256 is X2 valid rang:0¡«256)   ÇåÎú¶È
	int mctf_strength;			//unit = 32,64 is X2  valid rang:0 - 512   ½µÔë 
	
	ui_exposure_set_t exposure_set;                   //ÆØ¹âÉèÖÃ
	ui_focus_set_t focus_set;
	
	int ir_cut;						//onvif 0-auto, 1-on,	2-off
	
	ui_whitebalance_set_t whitebalance_set;
	
	int WDR;						//onvif 0-on,	1-off
}ui_image_set_t;

typedef struct wta_fifocmd_s
{
	unsigned char Cmdhead;		//0x0A
	unsigned char Cmd_ver;		//0x01
	unsigned char Cmd_ID;
	unsigned char Cmd_Para[12];
	unsigned char Cmd_check;	//0x00
}	wta_fifocmd_t;


typedef struct wta_fifoEncode_s
{
	unsigned char Cmdhead;		//0x0A
	unsigned char Cmd_ver;		//0x01
	unsigned char Cmd_ID;
	unsigned char Cmd_Para[20];
	unsigned char Cmd_check;	//0x00
}	wta_fifoEncode_t;


ui_image_set_t simg_t;


typedef struct encode_s
{
	char type[50];             //±àÂëÀàÐÍ
	int definition;            //ÇåÎú¶È
	int frame_rate;            //Ö¡ÂÊ
	int frame_rate_time;       //Ö¡¼ä¸ô
	int code_rate_contral;     //ÂëÂÊ¿ØÖÆ
	int code_rate;             //ÂëÂÊ
	int rotate;                //Ðý×ª·½Ïò
	int quality;               //ÖÊÁ¿
	int text_judge;            //
}encode_t;

encode_t encode_set[4];




typedef struct ui_Stream_cfg_s {
	unsigned char stream_id;                     //ÂëÁ÷±àºÅ
	unsigned char stream_enable;                 //ÂëÁ÷ÊÇ·ñ´ò¿ª
	unsigned char encode_type;                   //±àÂëÀàÐÍ
	unsigned char video_size_mode;               //ÇåÎú¶È 
	int image_width;                              
	int image_hight;
	unsigned char ePTZ_enable;
	int area_offset_x;
	int area_offset_y;
	int FrameRate;                               //Ö¡ÂÊ
	unsigned char revolve_mode;                  //Ðý×ª·½Ïò
	unsigned char biterate_control_mode;         //ÂëÂÊ¿ØÖÆ
	unsigned char GOP_frame;                     //IÖ¡¼ä¸ô
	int cbr_avg_bitrate;                         //CBRÆ½¾ùÂëÂÊ
	int vbr_min_bitrate;                         //VBR×îÐ¡ÂëÂÊ
	int vbr_max_bitrate;                         //VBR×î´óÂëÂÊ
	unsigned char mjpeg_quality;                 //ÖÊÁ¿
}ui_Stream_cfg_t;

typedef struct ui_AnalogVideo_cfg_s {
	unsigned char output_enable;                 //¼¸¸öÂëÁ÷       
	unsigned char output_type;                   //Ä£ÄâÊÓÆµÊä³ö£¬ÊÇ·ñ´ò¿ª
	unsigned char TV_system;                     //ÖÆÊ½
	unsigned char aspect_rate;                   //±ÈÀý
}ui_AnalogVideo_cfg_t;

typedef struct ui_Encoder_cfg_s {
	ui_Stream_cfg_t stream_cfg[4];
	ui_AnalogVideo_cfg_t AnalogVideo_cfg;
}ui_Encoder_cfg_t;

ui_Encoder_cfg_t ui_Encoder;
ui_Encoder_cfg_t my_ui_Encoder_cfg;


const char *FIFO_Web_Encode = "/dev/Fifo_WTE";

/**************************** Forward Declarations ****************************/

static int aspGenerateMakeDispAddr(int eid, webs_t wp, int argc, char_t **argv);
static int aspGenerateMakeDispMask(int eid, webs_t wp, int argc, char_t **argv);
static int aspGenerateMakeDispGate(int eid, webs_t wp, int argc, char_t **argv);


static void formTimeSet(webs_t wp, char_t *path, char_t *query);              //Ê±¼äÉèÖÃ
static void formSysTime(webs_t wp, char_t *path, char_t *query);              //ÏµÍ³Ê±¼äÏÔÊ¾
static void formNetworkSet(webs_t wp, char_t *path, char_t *query);
static void formEncodeSet(webs_t wp, char_t *path, char_t *query);            //±àÂëÉèÖÃ
static void formMinEncodeSet(webs_t wp, char_t *path, char_t *query);            //±àÂëµ¥¸öÒ³ÃæÉèÖÃ
static void formTimeSync(webs_t wp, char_t *path, char_t *query);
static void formImageSet(webs_t wp, char_t *path, char_t *query);
static void formImgDefault(webs_t wp, char_t *path, char_t *query);
static void	websMsgStart(webs_t wp);
static void	websMsgEnd(webs_t wp);


/*********************************** Code *************************************/
/*
 *	Set up the User Management form handlers
 */

void formaspDefineLWT(void)
{
	websAspDefine(T("MakeDispAddr"),aspGenerateMakeDispAddr);			
	websAspDefine(T("MakeDispMask"),aspGenerateMakeDispMask);
	websAspDefine(T("MakeDispGate"),aspGenerateMakeDispGate);
	
	websFormDefine(T("SysTime"), formSysTime);
  websFormDefine(T("FTimeSet"), formTimeSet);
	websFormDefine(T("NetworkSet"), formNetworkSet);
	websFormDefine(T("EncodeSet"), formEncodeSet);
	websFormDefine(T("MinEncodeSet"), formMinEncodeSet);
	websFormDefine(T("ImageSet"), formImageSet);
	websFormDefine(T("ImgDefault"), formImgDefault);
	

}


int setfifoimage( unsigned char Fifo_ID,unsigned char imgID,int imgvalue)
{
	
	wta_fifocmd_t imagefifo;
	imagefifo.Cmdhead=0x01;
	imagefifo.Cmd_ver=0x01;
	imagefifo.Cmd_ID=Fifo_ID;	
	imagefifo.Cmd_Para[0]=imgID;
	imagefifo.Cmd_Para[1]=imgvalue;
	imagefifo.Cmd_check=0x00;
	int real_wnum = 0;
	int fifo_fd = open(IMAGE_FIFO,O_WRONLY,0);
	printf("fifo: %d\n", fifo_fd);
	if(fifo_fd)
  	{
    	 real_wnum = write(fifo_fd,&imagefifo,sizeof(wta_fifocmd_t));
    	 if(real_wnum==-1)
        	 printf("write to fifo error; try later real_wnum=%d\n",real_wnum);
    	 else 
        	 printf("real write num is %d\n",real_wnum);
        	 printf("Cmd_Para[0]:%d\n",imagefifo.Cmd_Para[0]);
        	 printf("Cmd_Para[1]:%d\n",imagefifo.Cmd_Para[1]);

       close(fifo_fd);
  	}       
	
}


int encodefifoSet( unsigned char Fifo_ID,unsigned char imgID,char *imagevalue, int nValLen)   //ÂëÁ÷¿ØÖÆ
{
	
	wta_fifoEncode_t encodefifo;
	encodefifo.Cmdhead=0x01;
	encodefifo.Cmd_ver=0x01;
	encodefifo.Cmd_ID=Fifo_ID;	
	encodefifo.Cmd_Para[0]=imgID;
	memcpy(encodefifo.Cmd_Para + 1, imagevalue, nValLen);
	encodefifo.Cmd_check=0x00;
	int real_wnum = 0;
	int fifo_fd = open(IMAGE_FIFO,O_WRONLY,0);
	printf("fifo: %d\n", fifo_fd);
	if(fifo_fd)
  	{
    	 real_wnum = write(fifo_fd,&encodefifo,sizeof(wta_fifoEncode_t));
    	 if(real_wnum==-1)
        	 printf("write to fifo error; try later real_wnum=%d\n",real_wnum);
    	 else 
        	 printf("real write num is %d\n",real_wnum);
        	 printf("Cmd_Para[0]:%d\n",encodefifo.Cmd_Para[0]);
       close(fifo_fd);
  	}       
	
}


int shutterfifo( unsigned char Fifo_ID,unsigned char imgID,char *imagevalue, int nValLen)    //¿ìÃÅ
{
	
	wta_fifocmd_t imagefifo;
	imagefifo.Cmdhead=0x01;
	imagefifo.Cmd_ver=0x01;
	imagefifo.Cmd_ID=Fifo_ID;	
	imagefifo.Cmd_Para[0]=imgID;
	memcpy(imagefifo.Cmd_Para + 1, imagevalue, nValLen);
	imagefifo.Cmd_check=0x00;
	int real_wnum = 0;
	int fifo_fd = open(IMAGE_FIFO,O_WRONLY,0);
	printf("fifo: %d\n", fifo_fd);
	if(fifo_fd)
  	{
    	 real_wnum = write(fifo_fd,&imagefifo,sizeof(wta_fifocmd_t));
    	 if(real_wnum==-1)
        	 printf("write to fifo error; try later real_wnum=%d\n",real_wnum);
    	 else 
        	 printf("real write num is %d\n",real_wnum);
        	 printf("Cmd_Para[0]:%d\n",imagefifo.Cmd_Para[0]);
       close(fifo_fd);
  	}       
	
}


int defaultFifo()
{
	
	wta_fifocmd_t imagefifo;
	imagefifo.Cmdhead=0x01;
	imagefifo.Cmd_ver=0x01;
	imagefifo.Cmd_ID=WTA_IMAGE_QULITY_SET;	
	imagefifo.Cmd_Para[0]=WTA_IMGQU_FACTORY_SET;
	imagefifo.Cmd_check=0x00;
	int real_wnum = 0;
	int fifo_fd = open(IMAGE_FIFO,O_WRONLY,0);
	printf("fifo: %d\n", fifo_fd);
	if(fifo_fd)
  	{
    	 real_wnum = write(fifo_fd,&imagefifo,sizeof(wta_fifocmd_t));
    	 if(real_wnum==-1)
        	 printf("write to fifo error; try later real_wnum=%d\n",real_wnum);
    	 else 
        	 printf("real write num is %d\n",real_wnum);
        	 printf("Cmd_Para[0]:%d\n",imagefifo.Cmd_Para[0]);
       close(fifo_fd);
  	}       
	
}


void readimage()                                                 //´Ó¶þ½øÖÆÀï¶Á
{
	memset(&simg_t,0,sizeof(ui_image_set_t));
  if((imagefp=fopen(IMAGE_FILE,"rb"))==NULL)
	{
		printf("can not open file \n");
		return;
	}
	else
	{	
		fread(&simg_t,sizeof(ui_image_set_t),1,imagefp);
	}
}

void writeimage()
{
	if((imagefp=fopen(IMAGE_FILE,"wb"))==NULL)
	{
		printf("write can not open file\n");
		return;
	}
	else
	{
	fwrite(&simg_t,sizeof(ui_image_set_t),1,imagefp);
	
  }
  fclose(imagefp);
}

/*
 *±£´æÓÃ»§±àÂëÅäÖÃÐÅÏ¢
 */
/*----------------------------------------------------------------------------------------*/
int SaveUIEncodeCFG()
{
	int UIEncodeCfgfd;
	unsigned char *dbUIEncodeCfg;
	int len_file = 0,len_fileData = 0,len_fileHand = 0;
	//----------------------------------------------------------------
	printf(	"Doing SaveUIEncodeCFG......\n");
	if ((UIEncodeCfgfd = open(CFG_UIENCODER,O_WRONLY|O_CREAT|O_APPEND|O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR)) < 0)
		printf(	"open UIEncodeCfgfd file fail!\n");
	
	len_fileData = sizeof(my_ui_Encoder_cfg);	
	len_fileHand = 2;
	len_file = len_fileHand+len_fileData;
	
	printf("size of stream[4]:%d\n",len_fileData);
	
	dbUIEncodeCfg = malloc(len_file);
	if(dbUIEncodeCfg == NULL)
	{
		printf("malloc dbUIEncodeCfg failed!\n");
		return -1;
	}
	
	memset(dbUIEncodeCfg,0,len_file);
	
	dbUIEncodeCfg[0] = len_fileData/256;
	dbUIEncodeCfg[1] = len_fileData%256;
	
	memcpy(dbUIEncodeCfg+len_fileHand,&my_ui_Encoder_cfg,len_fileData);
	
	if(write(UIEncodeCfgfd,dbUIEncodeCfg,len_file) < 0)
	{
		printf ("write UIEncodeCfgfd fail!\n");
		close(UIEncodeCfgfd);
		free(dbUIEncodeCfg);
		return -1;
	}
	printf("done write UIEncodeCfgfd!\n");
	close(UIEncodeCfgfd);
	free(dbUIEncodeCfg);
	
	return 1;
}

/*
 *ÌáÈ¡ÓÃ»§±àÂëÅäÖÃ
 */
/*----------------------------------------------------------------------------------------*/
int LoadUIEncodeCFG()
{
	
	int UIEncodeCfgfd;
	unsigned char filehead[2] = {0};
	unsigned char *dbUIEncodeCfg;
	int len_fileData = 0,len_fileHand = 0;
	//----------------------------------------------------------------
	
	if ((UIEncodeCfgfd = open(CFG_UIENCODER,O_RDONLY,S_IRUSR|S_IWUSR|S_IXUSR)) < 0)
		printf(	"open UIEncodeCfgfd file fail!\n");
	
	len_fileHand = 2;
	
	if(read(UIEncodeCfgfd,filehead,len_fileHand) < 0)
	{
		printf ("write UIEncodeCfgfd fail!\n");
		close(UIEncodeCfgfd);
		return -1;
	}
	
	len_fileData = filehead[0]*256 + filehead[1];
	printf("size of UIEncodeCfgfd data:%d\n",len_fileData);
	
	if(len_fileData!=sizeof(my_ui_Encoder_cfg))
	{
		close(UIEncodeCfgfd);
		return 1;
	}
	//len_file = len_fileData + len_fileHand;
	dbUIEncodeCfg = malloc(len_fileData);
	if(dbUIEncodeCfg == NULL)
	{
		printf("malloc dbUIEncodeCfg failed!\n");
		return -1;
	}
	
	if(read(UIEncodeCfgfd,dbUIEncodeCfg,len_fileData) < 0)
	{
		printf ("read UIEncodeCfgfd fail!\n");
		close(UIEncodeCfgfd);
		free(dbUIEncodeCfg);
		return -1;
	}
	
	memcpy(&my_ui_Encoder_cfg,dbUIEncodeCfg,len_fileData);
	
	close(UIEncodeCfgfd);
	free(dbUIEncodeCfg);

	return 1;
}


void readencode()                                                 //´Ó¶þ½øÖÆÀï¶Á
{
	memset(&my_ui_Encoder_cfg,0,sizeof(ui_Encoder_cfg_t));
  if((encodefp=fopen(ENCODE_FILE,"rb"))==NULL)
	{
		printf("can not open file \n");
		return;
	}
	else
	{	
		fread(&my_ui_Encoder_cfg,sizeof(ui_Encoder_cfg_t),1,encodefp);
	}
	fclose(encodefp);
}



void writeencode()
{
	if((encodefp=fopen(ENCODE_FILE,"wb"))==NULL)
	{
		printf("write can not open file\n");
		return;
	}
	else
	{
	fwrite(&my_ui_Encoder_cfg,sizeof(ui_Encoder_cfg_t),1,encodefp);
	
  }
  fclose(encodefp);
}



static char* getNetworkInfo(char *maches)
{
	FILE *fp = NULL;
	char szBuf[64];
	char *szNetwork=NULL;
	int i = 0;
	if((fp=fopen(NETWORK_FILE, "r"))==NULL)
	{
		printf( "Can 't   open   file!\n"); 
		return 0;
	}
	while(fgets(szBuf,128,fp)){
		if(strstr(szBuf,maches) != NULL){
			for(i =0;i < strlen(szBuf);i++){
				if(isdigit(*(szBuf+i))){
					szNetwork = (char*)malloc(strlen(szBuf));
					strcpy(szNetwork,szBuf+i);
					szNetwork[strlen(szNetwork)-1] = '\0';
					fclose(fp);
					return szNetwork;
				}
			}
		}else
			continue;
	}
	fclose(fp);
	return szNetwork;
}
static int aspGenerateMakeDispAddr(int eid, webs_t wp, int argc, char_t **argv)
{   
	char_t *szAddr;
	szAddr = getNetworkInfo("address");
	return websWrite(wp, T("%s"), szAddr);
}
static int aspGenerateMakeDispMask(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*szMask;
	szMask = getNetworkInfo("netmask");
	return websWrite(wp, T("%s"), szMask);
}
static int aspGenerateMakeDispGate(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*szGate;
	szGate = getNetworkInfo("gateway");
	return websWrite(wp, T("%s"), szGate);
}





static void formImgDefault(webs_t wp, char_t *path, char_t *query)
{
	char_t *pszOperate = NULL;
	pszOperate = websGetVar(wp, T("Operate"), T(""));
	
	if (0 == gstricmp(pszOperate, T("set")))
	{	
		readimage();
		
		simg_t.color_hue=gatoi(websGetVar(wp, T("Hue"), T("")));
		simg_t.brightness=gatoi(websGetVar(wp, T("Bright"), T("")));
		simg_t.sharpness=gatoi(websGetVar(wp, T("Sharp"), T("")));
		simg_t.mctf_strength=gatoi(websGetVar(wp, T("Denoise"), T("")));
		simg_t.contrast=gatoi(websGetVar(wp, T("Contrast"), T("")));
		simg_t.saturation=gatoi(websGetVar(wp, T("Saturation"), T("")));	
		
		simg_t.exposure_set.exposure_mode=gatoi(websGetVar(wp, T("exposure_mode"), T("")));
		simg_t.exposure_set.exposure_level=gatoi(websGetVar(wp, T("exposure_level"), T("")));
		simg_t.backlight=gatoi(websGetVar(wp, T("backlight"), T("")));
		simg_t.exposure_set.anti_flicker_mode=gatoi( websGetVar(wp, T("screen_blink"), T("")));
		simg_t.exposure_set.shutter_time_min=gatoi(websGetVar(wp, T("shutter_min"), T("")));
		simg_t.exposure_set.shutter_time_max=gatoi(websGetVar(wp, T("shutter_max"), T("")));
		simg_t.exposure_set.slow_shutter_enable=gatoi(websGetVar(wp, T("slow_shutter"), T("")));	
				
		defaultFifo();           //Ä¬ÈÏÉèÖÃFifo
		writeimage();            //Ð´
		
		websWrite(wp,T("0"));	
		websDone(wp, 200);
	}
}





static void formImageSet(webs_t wp, char_t *path, char_t *query)
{
	FILE *imgfp;
	FILE *fp;                                            //¶¨ÒåÒ»¸öÎÄ¼þÖ¸Õë        
	char_t *pszOperate = NULL;

	pszOperate = websGetVar(wp, T("Operate"), T(""));
	
	if (0 == gstricmp(pszOperate, T("get"))) {
		
		readimage();   //¶Á
		
		websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<Image>"));
		websWrite(wp, T("<Hue>%d</Hue>"),simg_t.color_hue);
		websWrite(wp, T("<Bright>%d</Bright>"),simg_t.brightness);
		websWrite(wp, T("<Sharp>%d</Sharp>"),simg_t.sharpness);
		websWrite(wp, T("<Denoise>%d</Denoise>"),simg_t.mctf_strength);
		websWrite(wp, T("<Contrast>%d</Contrast>"),simg_t.contrast);
		websWrite(wp, T("<Saturation>%d</Saturation>"),simg_t.saturation);
		websWrite(wp, T("<exposure_mode>%d</exposure_mode>"),simg_t.exposure_set.exposure_mode);
		websWrite(wp, T("<exposure_level>%d</exposure_level>"),simg_t.exposure_set.exposure_level);
		websWrite(wp, T("<backlight>%d</backlight>"),simg_t.backlight);
		websWrite(wp, T("<screen_blink>%d</screen_blink>"),simg_t.exposure_set.anti_flicker_mode);
		websWrite(wp, T("<shutter_min>%d</shutter_min>"),simg_t.exposure_set.shutter_time_min);
		websWrite(wp, T("<shutter_max>%d</shutter_max>"),simg_t.exposure_set.shutter_time_max);
		websWrite(wp, T("<slow_shutter>%d</slow_shutter>"),simg_t.exposure_set.slow_shutter_enable);
		
		
		
		websWrite(wp, T("</Image>"));
		websDone(wp, 200);
	}else if (0 == gstricmp(pszOperate, T("set"))) {
		
		char *pszTmp = NULL;	
		char shutterTmp[12]={0};
		int nTmp=0;	
		memset(&simg_t,0,sizeof(ui_image_set_t));
	
		readimage();
		
		pszTmp = websGetVar(wp, T("Hue"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{
			simg_t.color_hue=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_HUA_SET, simg_t.color_hue);
			printf("hue!!!!!!!!!!!!!!\n");
		}	
		
		pszTmp = websGetVar(wp, T("Bright"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.brightness=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_BRIGHT_SET, simg_t.brightness);
			printf("bright!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("Sharp"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.sharpness=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_SHARP_SET, simg_t.sharpness);
			printf("bright!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("Denoise"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.mctf_strength=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_MCTF_FILTER_SET, simg_t.mctf_strength);
			printf("mctf_strength!!!!!!!!!!!!!\n");
		}		
		
		pszTmp = websGetVar(wp, T("Contrast"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.contrast=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_CONTRAST_SET, simg_t.contrast);
			printf("contrast!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("Saturation"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.saturation=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_IMGQU_SATURATION_SET, simg_t.saturation);
			printf("saturation!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("exposure_mode"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.exposure_set.exposure_mode=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_AE_METER_MODE_SET, simg_t.exposure_set.exposure_mode);
			printf("exposure_mode!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("exposure_level"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.exposure_set.exposure_level=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_AE_EV_SET, simg_t.exposure_set.exposure_level);
			printf("exposure_level!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("backlight"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.backlight=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET, WTA_BACKLIGHT_SET, simg_t.backlight);
			printf("backlightl!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("screen_blink"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.exposure_set.anti_flicker_mode=gatoi(pszTmp);
			setfifoimage(WTA_IMAGE_QULITY_SET,WTA_ANTIFLICKER_SET, simg_t.exposure_set.anti_flicker_mode);
			printf("anti_flicker_mode!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("shutter_min"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.exposure_set.shutter_time_min=gatoi(pszTmp);
			nTmp = htonl(simg_t.exposure_set.shutter_time_min);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.shutter_time_max);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.slow_shutter_enable);
			memcpy(shutterTmp+8, &nTmp, 4);
			shutterfifo(WTA_IMAGE_QULITY_SET, WTA_AE_SHUTTER_RANG_SET, shutterTmp,CPCOUNT);
			printf("shutter_time_min!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("shutter_max"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{			
			simg_t.exposure_set.shutter_time_max=gatoi(pszTmp);
			nTmp = htonl(simg_t.exposure_set.shutter_time_min);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.shutter_time_max);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.slow_shutter_enable);
			memcpy(shutterTmp+8, &nTmp, 4);
			shutterfifo(WTA_IMAGE_QULITY_SET, WTA_AE_SHUTTER_RANG_SET, shutterTmp,CPCOUNT);
			printf("shutter_time_max!!!!!!!!!!!!!\n");
		}
		
		pszTmp = websGetVar(wp, T("slow_shutter"), T(""));
		if(0!=gstricmp(pszTmp, T("")))
		{				  
			simg_t.exposure_set.slow_shutter_enable=gatoi(pszTmp);			
			nTmp = htonl(simg_t.exposure_set.shutter_time_min);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.shutter_time_max);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(simg_t.exposure_set.slow_shutter_enable);
			memcpy(shutterTmp+8, &nTmp, 4);
			shutterfifo(WTA_IMAGE_QULITY_SET, WTA_AE_SHUTTER_RANG_SET, shutterTmp,CPCOUNT);
			printf("slow_shutter!!!!!!!!!!!!!");
		}

    writeimage();
    
		websWrite(wp,T("0"));	
		websDone(wp, 200);
	}
}



static void formTimeSet(webs_t wp, char_t *path, char_t *query)
{
	
	FILE *NTPfp;
	char_t *pszOperate = NULL;
  char_t *ClientTime=NULL;
  char_t *SystemTime=NULL;
  char_t *NTPradiotime=NULL;
  char_t *NTPaddress="192.168.1.1";
	pszOperate = websGetVar(wp, T("Operate"), T(""));

	// get osd para
 if(0 == gstricmp(pszOperate, T("get")))
  {
  	char buf[100],Raddress[100],NTPbugjudge[100];
    int i=0;
    if((NTPfp=fopen(NTP_TIME,"r"))==NULL)
    {
   	  printf("can not open file!\n");
    }

    while(fgets(buf,128,NTPfp))
    {
			if(strstr(buf,T("address")) != NULL)                 //¶ÁIPµØÖ·
			{
				for(i =0;i<strlen(buf);i++)
				{
				 if(isdigit(*(buf+i)))
					{
						strcpy(Raddress,buf+i);
						Raddress[strlen(Raddress)-1] = '\0';
						//printf("szIP:%s\n", szIP);
						break;
					}
				}	
			}else if(strstr(buf,T("NTP")) != NULL)            //ÕÒ³öÎÄ¼þÀïNTPµÄÖµ   1¿ªÆô  0¹Ø±Õ
			{
				for(i =0;i<strlen(buf);i++)
				{
				 if(isdigit(*(buf+i)))
					{
						strcpy(NTPbugjudge,buf+i);
						NTPbugjudge[strlen(NTPbugjudge)-1] = '\0';
						//printf("szIP:%s\n", szIP);
						break;
					}
				}	
			}else
			{	
			  continue;
		  }
    }
  	
  	printf("NTPaddress=%s\n",Raddress);
  	printf("NTPjudge=%s\n",NTPbugjudge);
  	websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<timeset>"));
		websWrite(wp, T("<NTPradiotime>%s</NTPradiotime>"),NTPbugjudge);
		websWrite(wp, T("<NTPaddress>%s</NTPaddress>"),Raddress);
		websWrite(wp, T("</timeset>"));
		websDone(wp, 200);
   
	}
	// set
	else if (0 == gstricmp(pszOperate, T("set"))) {
		
    char szNTP[50][255],ntpjudge[100];
    char addr[255],addrbuf[255];	
    int i,Lid=-1;	
		NTPaddress = websGetVar(wp, T("NTPaddress"), T(""));
    NTPradiotime=websGetVar(wp, T("NTPradiotime"), T(""));
		if('\0' == NTPradiotime) {
			return;
		}
		
		if (0 == gstricmp(NTPradiotime, T("")))              //Óë±¾µØÊ±¼äÍ¬²½
	 {                
		char_t *szDateTime;
		char fid[200];
		char systimeread[]="+%Y-%m-%d %H:%M:%S";              //date  ±ê×¼Óï¾ä
		char systimewrite[200];
		szDateTime = websGetVar(wp, T("ClientTime"),T(""));
		if(szDateTime == NULL)
			return;
    sprintf(systimewrite,"date \%s\"",systimeread);       //°´±ê×¼¸ñÊ½¶¨Òå
		sprintf(fid,"date --set \"%s\"",szDateTime);
		printf("%s\n",fid);
		system(fid);
		
		
		memset(szNTP,0,sizeof(szNTP));
		if((NTPfp=fopen(NTP_TIME,"r"))==NULL)
    {
    	printf("can not open file!\n");
    }
    while(fgets(addr,256,NTPfp))
    {
    	Lid++;
    	strcpy(ntpjudge,"0");
			memset(addrbuf,0,sizeof(addrbuf));
			if(strstr(addr,T("NTP"))!=NULL)                      //ÅÐ¶ÏNTPÊÇ·ñ´ò¿ª
			{
				snprintf(addrbuf,sizeof(addrbuf),"\ NTP=%s\n",ntpjudge);
				strcpy(szNTP[Lid],addrbuf);		
			}else
				strcpy(szNTP[Lid],addr);
    }
    
    
    fclose(NTPfp);
		if((NTPfp=fopen(NTP_TIME,"w"))==NULL)                //Ð´ÈëNTPaddr.txt
	    {
	    	printf("can not open file!\n");
	    	return;
	    }
			else
			{
				for(i=0;i<=Lid;i++)
				{
					fputs(szNTP[i],NTPfp);
				}
				fclose(NTPfp);
			}
			printf("ntpend=%s\n",szNTP[0]);
		
		}
		
	  else if (0 == gstricmp(NTPradiotime, T("1")))        //ÓëNTPÍ¬²½
		{
			memset(szNTP,0,sizeof(szNTP));
			strcpy(ntpjudge,"1");
			if((NTPfp=fopen(NTP_TIME,"r"))==NULL)
	    {
	    	printf("can not open file!\n");
	    }
			while(fgets(addr,256,NTPfp))
			{
				Lid++;
				memset(addrbuf,0,sizeof(addrbuf));
				if(strstr(addr,T("NTP"))!=NULL)                      //ÅÐ¶ÏNTPÊÇ·ñ´ò¿ª
				{
					snprintf(addrbuf,sizeof(addrbuf),"\ NTP=%s\n",ntpjudge);
					strcpy(szNTP[Lid],addrbuf);			
				}
				else if(strstr(addr,T("address"))!=NULL)          //ÅÐ¶ÏÎÄ¼þÖÐÄÄÒ»ÐÐÊÇaddress
				{	
					snprintf(addrbuf,sizeof(addrbuf),"\ address=%s\n",NTPaddress);
					strcpy(szNTP[Lid],addrbuf);
				}
				else
					strcpy(szNTP[Lid],addr);
			}
			fclose(NTPfp);
			
			
			if((NTPfp=fopen(NTP_TIME,"w"))==NULL)                //Ð´ÈëNTPaddr.txt
	    {
	    	printf("can not open file!\n");
	    	return;
	    }
			else
			{
				for(i=0;i<=Lid;i++)
				{
					fputs(szNTP[i],NTPfp);
				}
				fclose(NTPfp);
			}
			printf("ntpend=%s\n",szNTP[0]);
			printf("address=%s\n",szNTP[1]);
	    }
    
		websWrite(wp,T("0"));	
		websDone(wp, 200);
	}
	
}

static void formSysTime(webs_t wp, char_t*path, char_t *query)
{
  char_t *pszOperate = NULL;
  pszOperate = websGetVar(wp, T("Operate"), T(""));
  if (0 == gstricmp(pszOperate, T("get")))
  {
  	
		struct tm *tp;
		char linuxsystime[50];
		time_t t;
		t=time(NULL);
		tp=localtime(&t);
		sprintf(linuxsystime,"%d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d\n",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,tp->tm_hour,tp->tm_min,tp->tm_sec);
		websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<timeset>"));
		websWrite(wp, T("<SystemTime>%s</SystemTime>"),linuxsystime);
		//websWrite(wp, T("<NTPradiotime>%s</NTPradiotime>"),"0");
		//websWrite(wp, T("<NTPaddress>%s</NTPaddress>"),"192.168.1.12");
		websWrite(wp, T("</timeset>"));
		websDone(wp, 200);
	}
	
}

static void formNetworkSet(webs_t wp, char_t *path, char_t *query)
{
	char_t	*szAddr, *szMask, *szGate;
    szAddr = websGetVar(wp, T("Address"),T(""));
    szMask = websGetVar(wp, T("Submask"),T(""));
    szGate = websGetVar(wp, T("Gateway"),T(""));
 
	FILE* fp=NULL;
	int i,Lid = -1; 
	char szBuf[128];
	char szTemp[128]; 
	char szTmp[20][256];
    memset(szTmp,0,sizeof(szTmp));
    memset(szBuf,0,sizeof(szBuf));
 
	if((fp=fopen(NETWORK_FILE, "r+"))==NULL) 
	{ 
		printf( "setIP Can 't open file!\n"); 
		return;
	} 
	while(fgets(szBuf,256,fp)) 
	{
		Lid++;
	 	if('#' != *szBuf)
		{
			if(strstr(szBuf,T("address")) != NULL)
			{
				memset(szTemp,0,sizeof(szTemp));
				snprintf(szTemp, sizeof(szTemp), "\taddress %s\n",szAddr);
				strcpy(szTmp[Lid],szTemp);
			}else if(strstr(szBuf,T("netmask")) != NULL)
			{
				memset(szTemp,0,sizeof(szTemp));
				snprintf(szTemp, sizeof(szTemp), "\tnetmask %s\n",szMask);
				strcpy(szTmp[Lid],szTemp);
			}else if(strstr(szBuf,T("gateway")) != NULL)
			{
				memset(szTemp,0,sizeof(szTemp));
				snprintf(szTemp, sizeof(szTemp), "\tgateway %s\n",szGate);
				strcpy(szTmp[Lid],szTemp);
			}else
				strcpy(szTmp[Lid],szBuf);
		}else{
			strcpy(szTmp[Lid],szBuf);
		}
	}
	fclose(fp);
	if((fp=fopen(NETWORK_FILE, "w"))==NULL) 
	{ 
		printf( "writeIP Can 't open file!\n");
		websRedirect(wp, T("network.asp")); 
		return;
	}else{
 		for(i = 0;i <=Lid;i++) 
			fputs(szTmp[i],fp);
		fclose(fp);
	}
	websRedirect(wp, T("network.asp"));
	return;
}



static void formEncodeSet(webs_t wp, char_t *path, char_t *query)
{	
	
	
	char_t *pszOperate = NULL;
  
	
	pszOperate = websGetVar(wp, T("Operate"), T(""));
	
	printf("Encode: %s\n", pszOperate);
  
	//readencode();
	LoadUIEncodeCFG();

	
	if (0 == gstricmp(pszOperate, T("get"))) {
		  
			websWrite(wp, T("HTTP/1.0 200 OK\n"));
			websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
			websWrite(wp, T("Pragma: no-cache\n"));
			websWrite(wp, T("Cache-control: no-cache\n"));
			websWrite(wp, T("Content-Type: text/xml\n"));
			websWrite(wp, T("\n"));
			
			
			websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
			websWrite(wp, T("<Encode>"));
			websWrite(wp, T("<stream_number>%d</stream_number>"),my_ui_Encoder_cfg.stream_cfg[0].stream_id);
			websWrite(wp, T("<video_output>%d</video_output>"),my_ui_Encoder_cfg.AnalogVideo_cfg.output_type);
			websWrite(wp, T("<video_mode>%d</video_mode>"),my_ui_Encoder_cfg.AnalogVideo_cfg.TV_system);
			websWrite(wp, T("<proportion>%d</proportion>"),my_ui_Encoder_cfg.AnalogVideo_cfg.aspect_rate);
			
			

			//websWrite(wp, T("<encode_style1>%d</encode_style1>"),my_ui_Encoder_cfg.stream_cfg[0].stream_id );
			//websWrite(wp, T("<stream_number>%d</stream_number>"),my_ui_Encoder_cfg.stream_cfg[0].stream_enable );
			websWrite(wp, T("<encode_style1>%d</encode_style1>"),my_ui_Encoder_cfg.stream_cfg[0].encode_type );
			websWrite(wp, T("<PTZ1>%d</PTZ1>"),my_ui_Encoder_cfg.stream_cfg[0].ePTZ_enable );
			websWrite(wp, T("<rotate1>%d</rotate1>"),my_ui_Encoder_cfg.stream_cfg[0].revolve_mode );
			websWrite(wp, T("<definition1>%d</definition1>"),my_ui_Encoder_cfg.stream_cfg[0].video_size_mode );
			websWrite(wp, T("<frame_rate1>%d</frame_rate1>"),my_ui_Encoder_cfg.stream_cfg[0].FrameRate);
			websWrite(wp, T("<code_rate_contral>%d</code_rate_contral>"),my_ui_Encoder_cfg.stream_cfg[0].biterate_control_mode);
			websWrite(wp, T("<frame_rate_time1>%d</frame_rate_time1>"),my_ui_Encoder_cfg.stream_cfg[0].GOP_frame);
			websWrite(wp, T("<CBR_code_contral1>%d</CBR_code_contral1>"),my_ui_Encoder_cfg.stream_cfg[0].cbr_avg_bitrate);
			websWrite(wp, T("<VBR_min_contral1>%d</VBR_min_contral1>"),my_ui_Encoder_cfg.stream_cfg[0].vbr_min_bitrate);
			websWrite(wp, T("<VBR_max_contral1>%d</VBR_max_contral1>"),my_ui_Encoder_cfg.stream_cfg[0].vbr_max_bitrate );
			websWrite(wp, T("<encode_quality1>%d</encode_quality1>"),my_ui_Encoder_cfg.stream_cfg[0].mjpeg_quality );
			
			websWrite(wp, T("<encode_style2>%d</encode_style2>"),my_ui_Encoder_cfg.stream_cfg[1].encode_type );
			websWrite(wp, T("<PTZ2>%d</PTZ2>"),my_ui_Encoder_cfg.stream_cfg[1].ePTZ_enable );
			websWrite(wp, T("<rotate2>%d</rotate2>"),my_ui_Encoder_cfg.stream_cfg[1].revolve_mode );
			websWrite(wp, T("<definition2>%d</definition2>"),my_ui_Encoder_cfg.stream_cfg[1].video_size_mode );
			websWrite(wp, T("<frame_rate2>%d</frame_rate2>"),my_ui_Encoder_cfg.stream_cfg[1].FrameRate);
			websWrite(wp, T("<code_rate_contra2>%d</code_rate_contra2>"),my_ui_Encoder_cfg.stream_cfg[1].biterate_control_mode);
			websWrite(wp, T("<frame_rate_time2>%d</frame_rate_time2>"),my_ui_Encoder_cfg.stream_cfg[1].GOP_frame);
			websWrite(wp, T("<CBR_code_contral2>%d</CBR_code_contral2>"),my_ui_Encoder_cfg.stream_cfg[1].cbr_avg_bitrate);
			websWrite(wp, T("<VBR_min_contral2>%d</VBR_min_contral2>"),my_ui_Encoder_cfg.stream_cfg[1].vbr_min_bitrate);
			websWrite(wp, T("<VBR_max_contral2>%d</VBR_max_contral2>"),my_ui_Encoder_cfg.stream_cfg[1].vbr_max_bitrate );
			websWrite(wp, T("<encode_quality2>%d</encode_quality2>"),my_ui_Encoder_cfg.stream_cfg[1].mjpeg_quality );
			
			websWrite(wp, T("<encode_style3>%d</encode_style3>"),my_ui_Encoder_cfg.stream_cfg[2].encode_type );
			websWrite(wp, T("<PTZ3>%d</PTZ3>"),my_ui_Encoder_cfg.stream_cfg[2].ePTZ_enable );
			websWrite(wp, T("<rotate3>%d</rotate3>"),my_ui_Encoder_cfg.stream_cfg[2].revolve_mode );
			websWrite(wp, T("<definition3>%d</definition3>"),my_ui_Encoder_cfg.stream_cfg[2].video_size_mode );
			websWrite(wp, T("<frame_rate3>%d</frame_rate3>"),my_ui_Encoder_cfg.stream_cfg[2].FrameRate);
			websWrite(wp, T("<code_rate_contra3>%d</code_rate_contra3>"),my_ui_Encoder_cfg.stream_cfg[2].biterate_control_mode);
			websWrite(wp, T("<frame_rate_time3>%d</frame_rate_time3>"),my_ui_Encoder_cfg.stream_cfg[2].GOP_frame);
			websWrite(wp, T("<CBR_code_contral3>%d</CBR_code_contral3>"),my_ui_Encoder_cfg.stream_cfg[2].cbr_avg_bitrate);
			websWrite(wp, T("<VBR_min_contral3>%d</VBR_min_contral3>"),my_ui_Encoder_cfg.stream_cfg[2].vbr_min_bitrate);
			websWrite(wp, T("<VBR_max_contral3>%d</VBR_max_contral3>"),my_ui_Encoder_cfg.stream_cfg[2].vbr_max_bitrate );
			websWrite(wp, T("<encode_quality3>%d</encode_quality3>"),my_ui_Encoder_cfg.stream_cfg[2].mjpeg_quality );
			
			websWrite(wp, T("<encode_style4>%d</encode_style4>"),my_ui_Encoder_cfg.stream_cfg[3].encode_type );
			websWrite(wp, T("<PTZ4>%d</PTZ4>"),my_ui_Encoder_cfg.stream_cfg[3].ePTZ_enable );
			websWrite(wp, T("<rotate4>%d</rotate4>"),my_ui_Encoder_cfg.stream_cfg[3].revolve_mode );
			websWrite(wp, T("<definition4>%d</definition4>"),my_ui_Encoder_cfg.stream_cfg[3].video_size_mode );
			websWrite(wp, T("<frame_rate4>%d</frame_rate4>"),my_ui_Encoder_cfg.stream_cfg[3].FrameRate);
			websWrite(wp, T("<code_rate_contra4>%d</code_rate_contra4>"),my_ui_Encoder_cfg.stream_cfg[3].biterate_control_mode);
			websWrite(wp, T("<frame_rate_time4>%d</frame_rate_time4>"),my_ui_Encoder_cfg.stream_cfg[3].GOP_frame);
			websWrite(wp, T("<CBR_code_contral4>%d</CBR_code_contral4>"),my_ui_Encoder_cfg.stream_cfg[3].cbr_avg_bitrate);
			websWrite(wp, T("<VBR_min_contral4>%d</VBR_min_contral4>"),my_ui_Encoder_cfg.stream_cfg[3].vbr_min_bitrate);
			websWrite(wp, T("<VBR_max_contral4>%d</VBR_max_contral4>"),my_ui_Encoder_cfg.stream_cfg[3].vbr_max_bitrate );
			websWrite(wp, T("<encode_quality4>%d</encode_quality4>"),my_ui_Encoder_cfg.stream_cfg[3].mjpeg_quality );
			websWrite(wp, T("</Encode>"));
			websDone(wp, 200);
	}	
	else if (0 == gstricmp(pszOperate, T("set"))) {

   
    printf("set");
    my_ui_Encoder_cfg.AnalogVideo_cfg.output_enable=gatoi(websGetVar(wp, T("video_output"), T("")));
    my_ui_Encoder_cfg.AnalogVideo_cfg.output_type  =gatoi(websGetVar(wp, T("video_output"), T("")));
    my_ui_Encoder_cfg.AnalogVideo_cfg.TV_system    =gatoi(websGetVar(wp, T("video_mode"), T("")));
    my_ui_Encoder_cfg.AnalogVideo_cfg.aspect_rate  =gatoi(websGetVar(wp, T("proportion"), T("")));
    
    
    my_ui_Encoder_cfg.stream_cfg[0].stream_id            =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].ePTZ_enable          =gatoi(websGetVar(wp, T("PTZ1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].stream_enable        =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].encode_type          =gatoi(websGetVar(wp, T("encode_style1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].revolve_mode         =gatoi(websGetVar(wp, T("rotate1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].video_size_mode      =gatoi(websGetVar(wp, T("definition1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].FrameRate            =gatoi(websGetVar(wp, T("frame_rate1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contral"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral1"), T("")));
    my_ui_Encoder_cfg.stream_cfg[0].mjpeg_quality        =gatoi(websGetVar(wp, T("encode_quality1"), T("")));
    
    
    my_ui_Encoder_cfg.stream_cfg[1].stream_id            =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].ePTZ_enable          =gatoi(websGetVar(wp, T("PTZ2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].stream_enable        =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].encode_type          =gatoi(websGetVar(wp, T("encode_style2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].revolve_mode         =gatoi(websGetVar(wp, T("rotate2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].video_size_mode      =gatoi(websGetVar(wp, T("definition2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].FrameRate            =gatoi(websGetVar(wp, T("frame_rate2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral2"), T("")));
    my_ui_Encoder_cfg.stream_cfg[1].mjpeg_quality        =gatoi(websGetVar(wp, T("encode_quality2"), T("")));
    
   
    my_ui_Encoder_cfg.stream_cfg[2].stream_id            =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].ePTZ_enable          =gatoi(websGetVar(wp, T("PTZ3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].stream_enable        =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].encode_type          =gatoi(websGetVar(wp, T("encode_style3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].revolve_mode         =gatoi(websGetVar(wp, T("rotate3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].video_size_mode      =gatoi(websGetVar(wp, T("definition3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].FrameRate            =gatoi(websGetVar(wp, T("frame_rate3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral3"), T("")));
    my_ui_Encoder_cfg.stream_cfg[2].mjpeg_quality        =gatoi(websGetVar(wp, T("encode_quality3"), T("")));
    
    my_ui_Encoder_cfg.stream_cfg[3].stream_id            =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].ePTZ_enable          =gatoi(websGetVar(wp, T("PTZ4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].stream_enable        =gatoi(websGetVar(wp, T("stream_number"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].encode_type          =gatoi(websGetVar(wp, T("encode_style4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].revolve_mode         =gatoi(websGetVar(wp, T("rotate4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].video_size_mode      =gatoi(websGetVar(wp, T("definition4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].FrameRate            =gatoi(websGetVar(wp, T("frame_rate4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral4"), T("")));
    my_ui_Encoder_cfg.stream_cfg[3].mjpeg_quality        =gatoi(websGetVar(wp, T("encode_quality4"), T("")));

    if(my_ui_Encoder_cfg.stream_cfg[0].stream_id==0)
    {
    	my_ui_Encoder_cfg.stream_cfg[0].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[1].stream_enable=0;
    	my_ui_Encoder_cfg.stream_cfg[2].stream_enable=0;
    	my_ui_Encoder_cfg.stream_cfg[3].stream_enable=0;
    }
    if(my_ui_Encoder_cfg.stream_cfg[0].stream_id==1)
    {
    	my_ui_Encoder_cfg.stream_cfg[0].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[1].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[2].stream_enable=0;
    	my_ui_Encoder_cfg.stream_cfg[3].stream_enable=0;
    }
    if(my_ui_Encoder_cfg.stream_cfg[0].stream_id==2)
    {
    	my_ui_Encoder_cfg.stream_cfg[0].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[1].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[2].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[3].stream_enable=0;
    }
    if(my_ui_Encoder_cfg.stream_cfg[0].stream_id==3)
    {
    	my_ui_Encoder_cfg.stream_cfg[0].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[1].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[2].stream_enable=1;
    	my_ui_Encoder_cfg.stream_cfg[3].stream_enable=1;
    }
    printf("output_enable:%d\n",my_ui_Encoder_cfg.AnalogVideo_cfg.output_enable);
    printf("output_type:%d\n", my_ui_Encoder_cfg.AnalogVideo_cfg.output_type );
    printf("TV_system:%d\n",my_ui_Encoder_cfg.AnalogVideo_cfg.TV_system);
    printf("aspect_rate:%d\n",my_ui_Encoder_cfg.AnalogVideo_cfg.aspect_rate );
    
    
    printf("encode_style1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].stream_id  );
    printf("ePTZ_enable1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].ePTZ_enable );
    printf("stream_enable1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].stream_enable );
    printf("revolve_mode1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].encode_type );
    printf("FrameRate1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].FrameRate );
   
   
    printf("encode_style2:%d\n",my_ui_Encoder_cfg.stream_cfg[1].stream_id  );
    printf("ePTZ_enable2:%d\n",my_ui_Encoder_cfg.stream_cfg[1].ePTZ_enable );
    printf("stream_enable2:%d\n",my_ui_Encoder_cfg.stream_cfg[1].stream_enable );
    printf("FrameRate2:%d\n",my_ui_Encoder_cfg.stream_cfg[1].FrameRate );
    
    printf("encode_style3:%d\n",my_ui_Encoder_cfg.stream_cfg[2].stream_id  );
    printf("ePTZ_enable3:%d\n",my_ui_Encoder_cfg.stream_cfg[2].ePTZ_enable );
    printf("stream_enable3:%d\n",my_ui_Encoder_cfg.stream_cfg[2].stream_enable );
    printf("FrameRate3:%d\n",my_ui_Encoder_cfg.stream_cfg[2].FrameRate );
    
    printf("encode_style4:%d\n",my_ui_Encoder_cfg.stream_cfg[3].stream_id  );
    printf("ePTZ_enable4:%d\n",my_ui_Encoder_cfg.stream_cfg[3].ePTZ_enable );
    printf("stream_enable4:%d\n",my_ui_Encoder_cfg.stream_cfg[3].stream_enable );
    printf("FrameRate4:%d\n",my_ui_Encoder_cfg.stream_cfg[3].FrameRate );
		//writeencode();
		SaveUIEncodeCFG();
	 
		setfifoimage(WTA_ENCODER,WTA_ENCODER_BASEPARA,0);
		
		websWrite(wp,T("0"));	
		websDone(wp, 200);
	}
}


static void formMinEncodeSet(webs_t wp, char_t *path, char_t *query)
{		
	char_t *pszOperate = NULL; 
	pszOperate = websGetVar(wp, T("Operate"), T(""));
	printf("Encode: %s\n", pszOperate);
  
  LoadUIEncodeCFG();
  
	if (0 == gstricmp(pszOperate, T("get1")))
  {
  	printf("get1:\n");	
  	websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<MinEncode>"));
		websWrite(wp, T("<frame_rate_time>%d</frame_rate_time>"),my_ui_Encoder_cfg.stream_cfg[0].GOP_frame);
		websWrite(wp, T("<frame_rate>%d</frame_rate>"),my_ui_Encoder_cfg.stream_cfg[0].FrameRate);
		websWrite(wp, T("<code_rate_contra>%d</code_rate_contra>"), my_ui_Encoder_cfg.stream_cfg[0].biterate_control_mode);
		websWrite(wp, T("<CBR_code_contral>%d</CBR_code_contral>"), my_ui_Encoder_cfg.stream_cfg[0].cbr_avg_bitrate);
		websWrite(wp, T("<VBR_min_contral>%d</VBR_min_contral>"),my_ui_Encoder_cfg.stream_cfg[0].vbr_min_bitrate);
		websWrite(wp, T("<VBR_max_contral>%d</VBR_max_contral>"),my_ui_Encoder_cfg.stream_cfg[0].vbr_max_bitrate);
		websWrite(wp, T("<PTZX>%d</PTZX>"),my_ui_Encoder_cfg.stream_cfg[0].area_offset_x);
		websWrite(wp, T("<PTZY>%d</PTZY>"),my_ui_Encoder_cfg.stream_cfg[0].area_offset_y);
		websWrite(wp, T("</MinEncode>"));
		websDone(wp, 200);
  	
  }
  else if (0 == gstricmp(pszOperate, T("get2")))
  {
  	printf("get2:\n");	
  	websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<MinEncode>"));
		websWrite(wp, T("<frame_rate_time>%d</frame_rate_time>"),my_ui_Encoder_cfg.stream_cfg[1].GOP_frame);
		websWrite(wp, T("<frame_rate>%d</frame_rate>"),my_ui_Encoder_cfg.stream_cfg[1].FrameRate);
		websWrite(wp, T("<code_rate_contra>%d</code_rate_contra>"), my_ui_Encoder_cfg.stream_cfg[1].biterate_control_mode);
		websWrite(wp, T("<CBR_code_contral>%d</CBR_code_contral>"), my_ui_Encoder_cfg.stream_cfg[1].cbr_avg_bitrate);
		websWrite(wp, T("<VBR_min_contral>%d</VBR_min_contral>"),my_ui_Encoder_cfg.stream_cfg[1].vbr_min_bitrate);
		websWrite(wp, T("<VBR_max_contral>%d</VBR_max_contral>"),my_ui_Encoder_cfg.stream_cfg[1].vbr_max_bitrate);
		websWrite(wp, T("<PTZX>%d</PTZX>"),my_ui_Encoder_cfg.stream_cfg[1].area_offset_x);
		websWrite(wp, T("<PTZY>%d</PTZY>"),my_ui_Encoder_cfg.stream_cfg[1].area_offset_y);
		websWrite(wp, T("</MinEncode>"));
		websDone(wp, 200);
  	
  }
   else if (0 == gstricmp(pszOperate, T("get3")))
  {
  	printf("get2:\n");	
  	websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<MinEncode>"));
		websWrite(wp, T("<frame_rate_time>%d</frame_rate_time>"),my_ui_Encoder_cfg.stream_cfg[2].GOP_frame);
		websWrite(wp, T("<frame_rate>%d</frame_rate>"),my_ui_Encoder_cfg.stream_cfg[2].FrameRate);
		websWrite(wp, T("<code_rate_contra>%d</code_rate_contra>"), my_ui_Encoder_cfg.stream_cfg[2].biterate_control_mode);
		websWrite(wp, T("<CBR_code_contral>%d</CBR_code_contral>"), my_ui_Encoder_cfg.stream_cfg[2].cbr_avg_bitrate);
		websWrite(wp, T("<VBR_min_contral>%d</VBR_min_contral>"),my_ui_Encoder_cfg.stream_cfg[2].vbr_min_bitrate);
		websWrite(wp, T("<VBR_max_contral>%d</VBR_max_contral>"),my_ui_Encoder_cfg.stream_cfg[2].vbr_max_bitrate);
		websWrite(wp, T("<PTZX>%d</PTZX>"),my_ui_Encoder_cfg.stream_cfg[2].area_offset_x);
		websWrite(wp, T("<PTZY>%d</PTZY>"),my_ui_Encoder_cfg.stream_cfg[2].area_offset_y);
		websWrite(wp, T("</MinEncode>"));
		websDone(wp, 200);
  	
  }
   else if (0 == gstricmp(pszOperate, T("get4")))
  {
  	printf("get4:\n");	
  	websWrite(wp, T("HTTP/1.0 200 OK\n"));
		websWrite(wp, T("Server: %s\r\n"), WEBS_NAME);
		websWrite(wp, T("Pragma: no-cache\n"));
		websWrite(wp, T("Cache-control: no-cache\n"));
		websWrite(wp, T("Content-Type: text/xml\n"));
		websWrite(wp, T("\n"));
		
		websWrite(wp, T("<?xml version='1.0' encoding='UTF-8'?>"));
		websWrite(wp, T("<MinEncode>"));
		websWrite(wp, T("<frame_rate_time>%d</frame_rate_time>"),my_ui_Encoder_cfg.stream_cfg[3].GOP_frame);
		websWrite(wp, T("<frame_rate>%d</frame_rate>"),my_ui_Encoder_cfg.stream_cfg[3].FrameRate);
		websWrite(wp, T("<code_rate_contra>%d</code_rate_contra>"), my_ui_Encoder_cfg.stream_cfg[3].biterate_control_mode);
		websWrite(wp, T("<CBR_code_contral>%d</CBR_code_contral>"), my_ui_Encoder_cfg.stream_cfg[3].cbr_avg_bitrate);
		websWrite(wp, T("<VBR_min_contral>%d</VBR_min_contral>"),my_ui_Encoder_cfg.stream_cfg[3].vbr_min_bitrate);
		websWrite(wp, T("<VBR_max_contral>%d</VBR_max_contral>"),my_ui_Encoder_cfg.stream_cfg[3].vbr_max_bitrate);
		websWrite(wp, T("<PTZX>%d</PTZX>"),my_ui_Encoder_cfg.stream_cfg[3].area_offset_x);
		websWrite(wp, T("<PTZY>%d</PTZY>"),my_ui_Encoder_cfg.stream_cfg[3].area_offset_y);
		websWrite(wp, T("</MinEncode>"));
		websDone(wp, 200);
  	
  }
 
  else if (0 == gstricmp(pszOperate, T("set1")))                       //Ö¡ÂÊ
  {
  	char shutterTmp[12]={0};
		int nTmp=0;	
  	char_t *frame_ratejudge=NULL;	
  	frame_ratejudge=websGetVar(wp, T("text_judge"), T(""));
  	printf("judge:%s\n",frame_ratejudge);
    if (0 == gstricmp(frame_ratejudge, T("1")))
    {
  		 my_ui_Encoder_cfg.stream_cfg[0].FrameRate  =gatoi(websGetVar(wp, T("frame_rate"), T("")));
  	   printf("setframe_rate:%d\n",my_ui_Encoder_cfg.stream_cfg[0].FrameRate );
			 nTmp = htonl(0);
			 memcpy(shutterTmp, &nTmp, 4);
			 nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].FrameRate);
			 memcpy(shutterTmp+4, &nTmp, 4);	   
    }
    if (0 == gstricmp(frame_ratejudge, T("2")))
    {
  		 my_ui_Encoder_cfg.stream_cfg[1].FrameRate  =gatoi(websGetVar(wp, T("frame_rate"), T("")));
  	   nTmp = htonl(1);
			 memcpy(shutterTmp, &nTmp, 4);
			 nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].FrameRate);
			 memcpy(shutterTmp+4, &nTmp, 4);
    }
    if (0 == gstricmp(frame_ratejudge, T("3")))
    {
  		 my_ui_Encoder_cfg.stream_cfg[2].FrameRate  =gatoi(websGetVar(wp, T("frame_rate"), T("")));
  	   nTmp = htonl(2);
			 memcpy(shutterTmp, &nTmp, 4);
			 nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].FrameRate);
			 memcpy(shutterTmp+4, &nTmp, 4);
    }
    if (0 == gstricmp(frame_ratejudge, T("4")))
    {
  		 my_ui_Encoder_cfg.stream_cfg[3].FrameRate  =gatoi(websGetVar(wp, T("frame_rate"), T("")));
  	   nTmp = htonl(3);
			 memcpy(shutterTmp, &nTmp, 4);
			 nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].FrameRate);
			 memcpy(shutterTmp+4, &nTmp, 4);
    }	
  	SaveUIEncodeCFG();	
    shutterfifo(WTA_ENCODER, WTA_ENCODER_FRAMERATE, shutterTmp,CPCOUNT);
		websDone(wp, 200);
  }
 
  else if (0 == gstricmp(pszOperate, T("set2")))                 // IÖ¡¼ä¸ô
  {
  	char shutterTmp[12]={0};
		int nTmp=0;	
  	char_t *GOP_framejudge=NULL;	
  	GOP_framejudge=websGetVar(wp, T("text_judge"), T(""));
  	printf("judge:%s\n",GOP_framejudge);
  	if (0 == gstricmp(GOP_framejudge, T("1")))
  	{
  		my_ui_Encoder_cfg.stream_cfg[0].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		printf("frame_rate_time1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].GOP_frame);
  		nTmp = htonl(0);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].FrameRate);
			memcpy(shutterTmp+4, &nTmp, 4);
  	}
  	if (0 == gstricmp(GOP_framejudge, T("2")))
  	{
  		my_ui_Encoder_cfg.stream_cfg[1].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		nTmp = htonl(1);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].FrameRate);
			memcpy(shutterTmp+4, &nTmp, 4);
  	}
  	if (0 == gstricmp(GOP_framejudge, T("3")))
  	{
  		my_ui_Encoder_cfg.stream_cfg[2].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		nTmp = htonl(2);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].FrameRate);
			memcpy(shutterTmp+4, &nTmp, 4);
  	}
  	if (0 == gstricmp(GOP_framejudge, T("4")))
  	{
  		my_ui_Encoder_cfg.stream_cfg[3].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		nTmp = htonl(3);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].FrameRate);
			memcpy(shutterTmp+4, &nTmp, 4);
			
  	}
  	
  	SaveUIEncodeCFG();
  	shutterfifo(WTA_ENCODER, WTA_ENCODER_GOPFRAME, shutterTmp,CPCOUNT);
  	websDone(wp, 200);
  }	
  else if (0 == gstricmp(pszOperate, T("set")))             //ÂëÁ÷
  {
  	char shutterTmp[20]={0};
		int nTmp=0;	
  	char_t *minjudge=NULL;	
  	minjudge=websGetVar(wp, T("text_judge"), T(""));
  	printf("judge:%s\n",minjudge);
  		
  	if (0 == gstricmp(minjudge, T("1")))
  	{
  		printf("set1\n");
  		my_ui_Encoder_cfg.stream_cfg[0].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[0].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[0].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[0].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[0].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[0].area_offset_x      =gatoi(websGetVar(wp, T("PTZX"), T("")));
      my_ui_Encoder_cfg.stream_cfg[0].area_offset_y      =gatoi(websGetVar(wp, T("PTZY"), T("")));
  		printf("frame_rate_time1:%d\n",my_ui_Encoder_cfg.stream_cfg[0].GOP_frame);
  		nTmp = htonl(0);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].biterate_control_mode);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].cbr_avg_bitrate);
			memcpy(shutterTmp+8, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].vbr_min_bitrate);
			memcpy(shutterTmp+12, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[0].vbr_max_bitrate);
			memcpy(shutterTmp+16, &nTmp, 4);
  		
  		
  	}
  	if (0 == gstricmp(minjudge, T("2")))
  	{
  		printf("set2\n");
  		my_ui_Encoder_cfg.stream_cfg[1].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[1].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[1].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[1].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[1].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[1].area_offset_x      =gatoi(websGetVar(wp, T("PTZX"), T("")));
      my_ui_Encoder_cfg.stream_cfg[1].area_offset_y      =gatoi(websGetVar(wp, T("PTZY"), T("")));
  		printf("frame_rate_time1:%d\n",my_ui_Encoder_cfg.stream_cfg[1].GOP_frame);
  		nTmp = htonl(1);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].biterate_control_mode);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].cbr_avg_bitrate);
			memcpy(shutterTmp+8, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].vbr_min_bitrate);
			memcpy(shutterTmp+12, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[1].vbr_max_bitrate);
			memcpy(shutterTmp+16, &nTmp, 4);
  	}
    if (0 == gstricmp(minjudge, T("3")))
  	{
  		printf("set3\n");
  		my_ui_Encoder_cfg.stream_cfg[2].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[2].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[2].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[2].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[2].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[2].area_offset_x      =gatoi(websGetVar(wp, T("PTZX"), T("")));
      my_ui_Encoder_cfg.stream_cfg[2].area_offset_y      =gatoi(websGetVar(wp, T("PTZY"), T("")));
  		nTmp = htonl(2);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].biterate_control_mode);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].cbr_avg_bitrate);
			memcpy(shutterTmp+8, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].vbr_min_bitrate);
			memcpy(shutterTmp+12, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[2].vbr_max_bitrate);
			memcpy(shutterTmp+16, &nTmp, 4);
  	}
  	if (0 == gstricmp(minjudge, T("4")))
  	{
  		printf("set4\n");
  		my_ui_Encoder_cfg.stream_cfg[3].GOP_frame            =gatoi(websGetVar(wp, T("frame_rate_time"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[3].biterate_control_mode=gatoi(websGetVar(wp, T("code_rate_contra"), T("")));
  		my_ui_Encoder_cfg.stream_cfg[3].cbr_avg_bitrate      =gatoi(websGetVar(wp, T("CBR_code_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[3].vbr_min_bitrate      =gatoi(websGetVar(wp, T("VBR_min_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[3].vbr_max_bitrate      =gatoi(websGetVar(wp, T("VBR_max_contral"), T("")));
      my_ui_Encoder_cfg.stream_cfg[3].area_offset_x      =gatoi(websGetVar(wp, T("PTZX"), T("")));
      my_ui_Encoder_cfg.stream_cfg[3].area_offset_y      =gatoi(websGetVar(wp, T("PTZY"), T("")));
  		nTmp = htonl(3);
			memcpy(shutterTmp, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].biterate_control_mode);
			memcpy(shutterTmp+4, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].cbr_avg_bitrate);
			memcpy(shutterTmp+8, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].vbr_min_bitrate);
			memcpy(shutterTmp+12, &nTmp, 4);
			nTmp = htonl(my_ui_Encoder_cfg.stream_cfg[3].vbr_max_bitrate);
			memcpy(shutterTmp+16, &nTmp, 4);
			
  	}
  	
  	
  	SaveUIEncodeCFG();
  	
  	encodefifoSet(WTA_ENCODER, WTA_ENCODER_BITRATE, shutterTmp,CPENCODE);
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

