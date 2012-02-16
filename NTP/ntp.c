#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

#include <sys/timex.h>

#define NTP_SERVER    "192.168.1.169"
const char *hostname = "192.168.1.145";	//NTP服务器地址
#define NTP_PORT      123

#define JAN_1970      0x83aa7e80      /* 2208988800 1970 - 1900 in seconds */
#define GMT_CHINASH	0x7080		/*8*3600 = 28800*/

/* How to multiply by 4294.967296 quickly (and not quite exactly)
 * without using floating point or greater than 32-bit integers.
 * If you want to fix the last 12 microseconds of error, add in
 * (2911*(x))>>28)
 */
#define NTPFRAC(x) ( 4294*(x) + ( (1981*(x))>>11 ) )

/* The reverse of the above, needed if we want to set our microsecond
 * clock (via settimeofday) based on the incoming time in NTP format.
 * Basically exact.
 */
#define USEC(x) ( ( (x) >> 12 ) - 759 * ( ( ( (x) >> 10 ) + 32768 ) >> 16 ) )

/* Converts NTP delay and dispersion, apparently in seconds scaled
 * by 65536, to microseconds.  RFC1305 states this time is in seconds,
 * doesn't mention the scaling.
 * Should somehow be the same as 1000000 * x / 65536
 */
#define sec2u(x) ( (x) * 15.2587890625 )

typedef u_int32_t __u32;


/*------------------------全局变量定义------------------------------------*/
extern int TMtNTPfifofd,WBtNTPfifofd;
//-------------------------------------------------------------------------------
struct ntptime 
{
    unsigned int coarse;
    unsigned int fine;
};
//--------------------全局变量-----------------------------------------------------------
char incoming[1500];
struct timeval time_of_send;
//------------------------------------------------------------------------------

void stuff_net_addr(struct in_addr *p, char *hostname)
{
	struct hostent *ntpserver;
	ntpserver=gethostbyname(hostname);
	if (ntpserver == NULL) {
		herror(hostname);
		exit(1);
	}
	if (ntpserver->h_length != 4) {
		fprintf(stderr,"oops %d\n",ntpserver->h_length);
		exit(1);
	}
	memcpy(&(p->s_addr),ntpserver->h_addr_list[0],4);
}

int get_current_freq()
{
	/* OS dependent routine to get the current value of clock frequency.
	 */
	struct timex txc;
	txc.modes=0;
	if (__adjtimex(&txc) < 0) {
		perror("adjtimex"); exit(1);
	}
	return txc.freq;
}


double ntpdiff( struct ntptime *start, struct ntptime *stop)
{
	int a;
	unsigned int b;
	a = stop->coarse - start->coarse;
	if (stop->fine >= start->fine) {
		b = stop->fine - start->fine;
	} else {
		b = start->fine - stop->fine;
		b = ~b;
		a -= 1;
	}
	
	return a*1.e6 + b * (1.e6/4294967296.0);
}

void send_packet(int ntpsockfd)
{
	__u32 data[12];

	struct timeval now;
#define LI 0
#define VN 3
#define MODE 3
#define STRATUM 0
#define POLL 4 
#define PREC -6

	printf("Sending NTP packet...\n");
	if (sizeof(data) != 48) 
	{
		fprintf(stderr,"size error\n");
		return;
	}
	bzero(data,sizeof(data));
	data[0] = htonl (
		( LI << 30 ) | ( VN << 27 ) | ( MODE << 24 ) |
		( STRATUM << 16) | ( POLL << 8 ) | ( PREC & 0xff ) );
	data[1] = htonl(1<<16);  /* Root Delay (seconds) */
	data[2] = htonl(1<<16);  /* Root Dispersion (seconds) */
	gettimeofday(&now,NULL);
	data[10] = htonl(now.tv_sec + JAN_1970); /* Transmit Timestamp coarse */
	data[11] = htonl(NTPFRAC(now.tv_usec));  /* Transmit Timestamp fine   */
	send(ntpsockfd,data,48,0);
	time_of_send=now;
}


void setup_receive(int ntpsockfd, unsigned int interface, short port)
{
	struct sockaddr_in sa_rcvr;
	bzero((char *) &sa_rcvr, sizeof(sa_rcvr));
	sa_rcvr.sin_family=AF_INET;
	sa_rcvr.sin_addr.s_addr=htonl(interface);
	sa_rcvr.sin_port=htons(port);
	if(bind(ntpsockfd,(struct sockaddr *) &sa_rcvr,sizeof(sa_rcvr)) == -1) 
	{
		fprintf(stderr,"could not bind to udp port %d\n",port);
		perror("bind");
		//system("reboot");
	}
	listen(ntpsockfd,3);
}


void setup_transmit(int ntpsockfd, char *host, short port)
{
	struct sockaddr_in sa_dest;
	bzero((char *) &sa_dest, sizeof(sa_dest));
	sa_dest.sin_family=AF_INET;
	stuff_net_addr(&(sa_dest.sin_addr),host);
	sa_dest.sin_port=htons(port);
	if (connect(ntpsockfd,(struct sockaddr *)&sa_dest,sizeof(sa_dest))==-1)
	{
		printf("ntpclient connect failed!......\n");
		//exit(1);
	}
}

void rfc1305print(char *data, struct ntptime *arrival)
{
/* straight out of RFC-1305 Appendix A */
	int li, vn, mode, stratum, poll, prec;
	int delay, disp, refid;
	struct ntptime reftime, orgtime, rectime, xmttime;
	double etime,stime,skew1,skew2;
	int freq;
	struct timeval tv_set;
	//----------------------------------------------------------
	
#define Data(i) ntohl(((unsigned int *)data)[i])
	li      = Data(0) >> 30 & 0x03;
	vn      = Data(0) >> 27 & 0x07;
	mode    = Data(0) >> 24 & 0x07;
	stratum = Data(0) >> 16 & 0xff;
	poll    = Data(0) >>  8 & 0xff;
	prec    = Data(0)       & 0xff;
	if (prec & 0x80) prec|=0xffffff00;
	delay   = Data(1);
	disp    = Data(2);
	refid   = Data(3);
	reftime.coarse = Data(4);
	reftime.fine   = Data(5);
	orgtime.coarse = Data(6);
	orgtime.fine   = Data(7);
	rectime.coarse = Data(8);
	rectime.fine   = Data(9);
	xmttime.coarse = Data(10);
	xmttime.fine   = Data(11);
#undef Data

	//settime
	/* it would be even better to subtract half the slop */
	tv_set.tv_sec  = xmttime.coarse - JAN_1970 + GMT_CHINASH;
	/* divide xmttime.fine by 4294.967296 */
	tv_set.tv_usec = USEC(xmttime.fine);
	//debug Jack 2008-9-13 22:00
	printf("set_local_time......\n");
	if (settimeofday(&tv_set,NULL)<0) 
	{
		perror("settimeofday");
		//exit(1);
	}
	
	system("hwclock -w");
	
	printf("settimeofday OK!\n");
	

	
	etime=ntpdiff(&orgtime,arrival);
	stime=ntpdiff(&rectime,&xmttime);
	skew1=ntpdiff(&orgtime,&rectime);
	skew2=ntpdiff(&xmttime,arrival);
	freq=get_current_freq();
	
	//printf("%d %5d.%.3d  %8.1f %8.1f  %8.1f %8.1f %9d\n",
	//	arrival->coarse/86400+15020, 	//当前秒/一天的秒+
	//	arrival->coarse%86400,
	//	arrival->fine/4294967, etime, stime,
	//	(skew1-skew2)/2, sec2u(disp), freq);
	
	
}

void udp_handle(int ntpsockfd, char *data, int data_len, struct sockaddr *sa_source, int sa_len)
{
	struct timeval udp_arrival;
	struct ntptime udp_arrival_ntp;
	struct sockaddr_in *sa_in;
	
	gettimeofday(&udp_arrival,NULL);

	udp_arrival_ntp.coarse = udp_arrival.tv_sec + JAN_1970;
	udp_arrival_ntp.fine   = NTPFRAC(udp_arrival.tv_usec);

	
	sa_in=(struct sockaddr_in *)sa_source;
	printf("packet of length %d received\n",data_len);
	if (sa_source->sa_family==AF_INET) 
	{
		printf("Source: INET Port %d host %s\n",
			ntohs(sa_in->sin_port),inet_ntoa(sa_in->sin_addr));
	} else 
	{
		printf("Source: Address family %d\n",sa_source->sa_family);
	}
	
	rfc1305print(data,&udp_arrival_ntp);
}



void primary_loop(int usd, int num_probes, int interval)
{
	fd_set fds;
	struct sockaddr sa_xmit;
	int i, pack_len, sa_xmit_len, probes_sent;
	struct timeval to;
	
	//debug Jack 2008-9-13 22:00
	printf("primary_loop......\n");
	
	printf("Listening...\n");

	probes_sent=0;
	sa_xmit_len=sizeof(sa_xmit);
	to.tv_sec=0;
	to.tv_usec=0;
	for (;;) 
	{
		FD_ZERO(&fds);
		FD_SET(usd,&fds);
		i=select(usd+1,&fds,NULL,NULL,&to);  /* Wait on read or error */
		if(i>0)
		{
		if ((i!=1)||(!FD_ISSET(usd,&fds)))
		{
			if (i==EINTR) continue;
			if (i<0) 
				perror("select");
			if (to.tv_sec == 0) 
			{
				//if (probes_sent >= num_probes && num_probes != 0) 
				//	break;
				printf("when to.tv_sec == 0,selectret:%u\n",i);
				send_packet(usd);
				++probes_sent;
				to.tv_sec=interval;
				to.tv_usec=0;
			}	
			continue;
			printf("when to.tv_sec == 0,continue\n");
		}
		}
		
		printf("Ready to recvfrom......\n");
		pack_len=recvfrom(usd,incoming,sizeof(incoming),0,&sa_xmit,&sa_xmit_len);
		if (pack_len<0) 
		{
			perror("recvfrom");
		} 
		else if (pack_len>0 && pack_len<sizeof(incoming))
		{
			udp_handle(usd,incoming,pack_len,&sa_xmit,sa_xmit_len);
		} 
		else 
		{
			printf("Ooops.  pack_len=%d\n",pack_len);
			fflush(stdout);
		}
		//if (probes_sent >= num_probes && num_probes != 0)
		//	break;
	}
}
/*
 *
 */
/*-------------------------NTP服务器初始化-------------------*/

static int iniNTPServer(void)
{
	char buf[100],Raddress[100],NTPbugjudge[100];
	FILE *NTPfp;
	const char *cfg_NTPaddress  = "/etc/ambaipcam/IPC_Q313/config/NTPaddr.txt";		/*矩阵属性文件*/
	int i = 0, judge; 
	//------------------------------------------------------------
	 if((NTPfp=fopen(cfg_NTPaddress,"r"))==NULL)
    {
   	  printf("can not open file!\n");
    }

    while(fgets(buf,128,NTPfp))
    {
			if(strstr(buf,"address") != NULL)                 //读IP地址
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
			}else if(strstr(buf,"NTP") != NULL)            //找出文件里NTP的值   1开启  0关闭
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
   judge=atoi(NTPbugjudge);
   printf("NTPaddress=%s\n",Raddress);
   printf("NTPjudge=%s\n",NTPbugjudge);
   printf("hostname:%s len:%d \n",hostname,strlen(hostname)); 
   hostname = Raddress;
   //hostname[strlen(lastbuf)] = 0;
   //memset(hostname,0,sizeof(hostname));
   //printf("1111111111111111\n");
   //memcpy(&hostname,lastbuf,strlen(lastbuf));
   printf("hostname:%s len:%d \n",hostname,strlen(hostname)); 
   return judge;   
	
}



int main(int argc, char *argv[])
{
	short udp_local_port = 123;
	
	//struct mx_ethip NTPServerIP;
	struct in_addr NTP_inaddr;
	int nNetTimeout=1000;//1秒
	
	fd_set readset;
	//int field[4] = {0};
	int selret;
	int maxfd;
	struct timeval timeout;
	
	
	int ntpsockfd=0;
	int readlen=0;
	//int i;
	//int reconnecttype = 0;
	struct sockaddr sa_xmit;
	int pack_len, sa_xmit_len;
	
	unsigned char rbuf_ttnf[7]= {0};
	//unsigned char rbuf_wtnf[7]= {0};
	
	//int TimeOutBit = 0;
	//-----------------------------------------------------------------
	/*
	NTPServerIP = iniNTPServer();
					
	NTP_inaddr.s_addr = ((NTPServerIP.mx_eth_IP4*256 + NTPServerIP.mx_eth_IP3)*256 +
			 NTPServerIP.mx_eth_IP2)*256 + NTPServerIP.mx_eth_IP1;
					
	hostname = inet_ntoa(NTP_inaddr);
	*/
	if(iniNTPServer()==0)
	{
	  exit(0);
  }
	
	sa_xmit_len=sizeof(sa_xmit);
	timeout.tv_sec=1;
	timeout.tv_usec=0;
	
	if ((ntpsockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
	{
		printf("ntpsock creat failed!\n");
		system("reboot");
	}
	
	
	//发送时限
	setsockopt(ntpsockfd,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));
	//接收时限
	setsockopt(ntpsockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));


	//监听udp_local_port端口
	setup_receive(ntpsockfd, INADDR_ANY, udp_local_port);

	//连接 NTP SERVER 端口
	setup_transmit(ntpsockfd, hostname, NTP_PORT);
	//
	send_packet(ntpsockfd);
	while(1)
	{
		
		FD_ZERO(&readset);
				
 		FD_SET(ntpsockfd, &readset);
 		//FD_SET(TMtNTPfifofd, &readset);
 		
 		maxfd = ntpsockfd;
 		/*
 		if(ntpsockfd>TMtNTPfifofd)
 		{
 			maxfd = ntpsockfd;
 		}
 		else
 		{
 			maxfd = TMtNTPfifofd;
 		}		
 		*/
						
		selret = select(maxfd+1, &readset, NULL, NULL, &timeout);
				
		if (selret<0)
		{
			//printf("dealcom function select ERROR!\n");
		}
/*---------------------------------------------------------------------------------------------------*/	
		if (selret>0)
		{
			if(FD_ISSET(ntpsockfd, &readset))
			{
				
				pack_len=recvfrom(ntpsockfd,incoming,sizeof(incoming),0,&sa_xmit,&sa_xmit_len);
				if (pack_len<0) 
				{
					perror("recvfrom");
				} 
				else if (pack_len>0 && pack_len<sizeof(incoming))
				{
					udp_handle(ntpsockfd,incoming,pack_len,&sa_xmit,sa_xmit_len);
				} 
				else 
				{
					printf("Ooops.  pack_len=%d\n",pack_len);
					fflush(stdout);
				}
				
				
			}
			//-----------------------------------------------------------------------
			/*if(FD_ISSET(TMtNTPfifofd, &readset))
			{
				readlen=read(TMtNTPfifofd, &rbuf_ttnf, 7);
				if (readlen<0)
				{
					printf("time FIFO read fail!\n");
				}
				else
				{
					send_packet(ntpsockfd);
				}
				
			}
			
			*/
		}
		
/*-------------------------------------------------------------------------*/
		if (selret==0)
		{
			/* //FOR TEST
			if(TimeOutBit == 0)
			{
				printf("NTP Time Out !\n");
				TimeOutBit = 1;
			}
			*/
						
		}

	}//while
	
	close(ntpsockfd);
	return 0;
}