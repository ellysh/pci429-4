#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include "pci429_4_ioctl.h"

	int  hARINC, IntNumber = 0;
	short unsigned int Data[0x8002], RID, numberSI, numberSO, nk, ap, modeKOP;

	struct sigaction action;
	struct itimerval timer;

	long int li,lo,ncikl=0,errors =0;
    
void hINT (int signo)
 	{
	int ii;

		IntNumber++;
		ioctl(hARINC,LNXioctl_PCI429_4_readRV ,&ii);
		if(ii&0x1000)
		{
			ii = 1;
			ioctl(hARINC,LNXioctl_PCI429_4_writeRV ,&ii);
		}
	}



void timerNonstop (int signo)

{
//читаем принятые параметры командой КВП
	ncikl++;
	for( nk=0;nk<numberSI;nk++)    	
		for( ap=0;ap<256;ap++)
		{ 

			Data[0] = 2;
			Data[1] = 0x4000+(nk)*0x400+ap*2;
			ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_1 ,&Data);

			int tim = 0;
			Data[0]=1;
			do
			{
				ioctl(hARINC,LNXioctl_PCI429_4_read_BKOP ,&Data);
				tim++;
			}while((Data[0]!=0)&&(tim<2000));
				
			lo = ((0x8000+(nk<<8)+(0xFF&(~ap)))<<16)|((nk<<12)+ap);
			li = ((Data[3])<<16)|(Data[2]);


			if  (li!=lo)
			{
				errors++;
			}
			 
		 }

  	printf(" \r");
 	printf("count=%5d  err_si=%3d IntNumber=%10d\r",ncikl,errors,IntNumber);

	switch (modeKOP)
	{
	case 0:
	{

		ioctl(hARINC,LNXioctl_PCI429_4_read_KPM ,&Data);
	
		if (Data[0]== 0)
		{
			ioctl(hARINC,LNXioctl_PCI429_4_read_BKOP ,&Data);

			if (Data[0]== 0)
			{
				Data[0] = 0x3c;		//
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_0 ,&Data);
				modeKOP = 1;
			}
		}
		break;
	}
	case 1:
	{

		ioctl(hARINC,LNXioctl_PCI429_4_read_KVM ,&Data);
	
		if (Data[0]== 0)
		{
			ioctl(hARINC,LNXioctl_PCI429_4_read_BKOP ,&Data);

			if (Data[0]== 0)
			{
				Data[0] = 0x8;		//
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_0 ,&Data);
				modeKOP = 2;
			}
		}
		break;
	}
	case 2:
	{

		ioctl(hARINC,LNXioctl_PCI429_4_read_KOMP ,&Data);
	
		if (Data[0]== 0)
		{
			ioctl(hARINC,LNXioctl_PCI429_4_read_BKOP ,&Data);

			if (Data[0]== 0)
			{
				Data[0] = 0x30;		//
				Data[1] = 0xc000;		//
				Data[2] = 512;		//
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_2 ,&Data);
				modeKOP = 0;
			}
		}
		break;
	}
	}
}





void timerErrorstop (int signo)

{
  if(errors==0)
    {
	ncikl++;
//читаем параметры в режиме защищенного обмена
	for( nk=0;nk<numberSI;nk++)    	
		for( ap=0;ap<256;ap++)
		{ 
			Data[0] = 0x4000+(nk)*0x400+ap*2;
			ioctl(hARINC,LNXioctl_PCI429_4_readPK ,&Data);

				
			lo = ((0x8000+(nk<<8)+(0xFF&(~ap)))<<16)|((nk<<12)+ap);
			li = ((Data[2])<<16)|(Data[1]);

			Data[0] = 0x4000+(nk)*0x400+ap*2;
			Data[1] = 0xaaaa;
			Data[2] = 0;
			ioctl(hARINC,LNXioctl_PCI429_4_writePK ,&Data);

			if  (li!=lo)
			{
				errors++;
 				printf("count=%5d  nk=%2d  ap=%2d   lo=%8x  li=%8x\n",ncikl,nk,ap,lo,li);
				nk = 20;
				break;
			}
			 
		 }
   	if(errors==0) 	printf("count=%5d  IntNumber =%10d\r",ncikl,IntNumber);
   }
	switch (modeKOP)
	{
	case 0:
	{

		Data[0] = 0x3010;		//
		ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);
	
		if (Data[1]== 0)
		{
			Data[0] = 0x2008;		//
			ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);

			if (Data[1]== 0)
			{
				Data[0] = 0x3c;		//йно
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_0 ,&Data);
			}
		}
		modeKOP = 1;
		break;
	}
	case 1:
	{

		Data[0] = 0x3014;		//
		ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);
	
		if (Data[1]== 0)
		{
			Data[0] = 0x2008;		//
			ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);

			if (Data[1]== 0)
			{
				Data[0] = 0x8;		//
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_0 ,&Data);
			}
		}
		modeKOP = 2;
		break;
	}
	case 2:
	{

		Data[0] = 0x301c;		//
		ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);
	
		if (Data[1]== 0)
		{
			Data[0] = 0x2008;		//
			ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);

			if (Data[1]== 0)
			{
				Data[0] = 0x30;		//
				Data[1] = 0xc000;		//
				Data[2] = 512;		//
				ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_2 ,&Data);
			}
		}
		modeKOP = 0;
		break;
	}
	}
   
}

main ()
{unsigned int rj, ind1, sn, snI, i;
 char msg[16]={'/','d','e','v','/','p','c','i','4','2','9','_','4'};
 int TestType, TestTypeStub;
	
	printf("enter serial # :")	;
	scanf("%5d",&snI);
	msg[14]='\0';
      	while(getchar()!=0xa);

	ind1 = 0;
	msg[13]='\0'; //was: '0'
	do
	{
		hARINC=open(msg,0);
		msg[13]++;
		ind1++;
		if(hARINC!=-1)
		{
			ioctl(hARINC,LNXioctl_PCI429_4_getSN,&Data);
			sn = Data[0];
			if(sn == snI)
				ind1 = 9;
			else
				ind1 = 9;
//				close(hARINC);

 		}
	}while (ind1 < 8);

	if(hARINC==-1)
	{
		printf("open error \n")	;
		return;
	}

	printf("SN = %dh\n",sn);	

//чтение идентификатора платы
	ioctl(hARINC,LNXioctl_PCI429_4_readRID ,&Data);
	RID = Data[0];
	printf("RID = %xh\n",RID)	;

	switch (RID)
	{
		case 0x4030:
			numberSI = 16;
			numberSO = 16;
			break;

		case 0x4020:
			numberSI = 16;
			numberSO = 8;
			break;

		case 0x4010:
			numberSI = 8;
			numberSO = 8;
			break;

		default: break;

	}
//ресурсы модуля
	ioctl(hARINC,LNXioctl_PCI429_4_getPRM ,&Data);
	printf("PRM : %xh %xh %xh \n",Data[0],Data[1],Data[2]);

//чтение блока состояния модуля
	i = 0;
	do
	{
		ioctl(hARINC,LNXioctl_PCI429_4_getState ,&Data);
		i++;
	}while ((Data[0]!=0xbcc)&&(i<2000));

	if(Data[0]!=0xbcc)
	{
		printf("getState = %xh %xh %xh %xh %d\n",Data[0],Data[1],Data[2],Data[3],i);
		close(hARINC);
		return;

	}

//запись в регистр управления  модуля
	Data[0] = 0x6000;
	ioctl(hARINC,LNXioctl_PCI429_4_writeRM ,&Data);


	printf("Test Type [0-nonstop / 1-error stop]:")	;
	scanf("%1d",&TestType);
      	while(getchar()!=0xa);

	printf("          [0-internal / 1-with stub]:")	;
	scanf("%1d",&TestTypeStub);
      	while(getchar()!=0xa);

	if (TestTypeStub==0)
	{
		for(i = 0; i<numberSI; i++)
			Data[i] = 3;
		for(i = numberSI; i<16; i++)
			Data[i] = 0;
		for(i = 16; i<numberSO+16; i++)
			Data[i] = 3;
		for(i = numberSO+16; i<32; i++)
			Data[i] = 0;
		ioctl(hARINC,LNXioctl_PCI429_4_setFreq ,&Data);
	
		Data[0] = 0x89;
		ioctl(hARINC,LNXioctl_PCI429_4_setKCR ,&Data);
	}
	else
	{
		for(i = 0; i<numberSI; i++)
			Data[i] = 2;
		for(i = numberSI; i<16; i++)
			Data[i] = 0;
		for(i = 16; i<numberSO+16; i++)
			Data[i] = 2;
		for(i = numberSO+16; i<32; i++)
			Data[i] = 0;
		ioctl(hARINC,LNXioctl_PCI429_4_setFreq ,&Data);
	

		Data[0] = 0x80;
		ioctl(hARINC,LNXioctl_PCI429_4_setKCR ,&Data);
	}


// задание режимов выходных и входных каналов
	for(nk=1;nk<numberSO; nk++)
	{
		Data[0] = nk+1;
		Data[1] = 0x900;
		ioctl(hARINC,LNXioctl_PCI429_4_writeBU_O ,&Data);
	}
		Data[0] = 1;
		Data[1] = 0x900;
		ioctl(hARINC,LNXioctl_PCI429_4_writeBU_O ,&Data);

	for(nk=0;nk<numberSI; nk++)
	{
		Data[0] = nk+1;
		Data[1] = 0x1900;
		Data[2] = 0x10;
		ioctl(hARINC,LNXioctl_PCI429_4_writeBU_I ,&Data);
	}

//подготовка стартовых кодов ПК каналов выдачи
	Data[1] = 0x100;
	for(nk=0;nk<16; nk++)
	{
		for(ap=0; ap<0x100; ap++)
		{
			Data[2+ap*2] = (nk<<12)+ap;
			Data[3+ap*2] = 0x8000+(nk<<8)+(0xFF&(~ap));
		}
		Data[0] = nk+1;
		ioctl(hARINC,LNXioctl_PCI429_4_writeBKV ,&Data);
	}

// подготовка адресов 
//               - для команды КПМ
	for( ap=0;ap<256;ap++)
		Data[ap]=0xC000+ap*2;
	ioctl(hARINC,LNXioctl_PCI429_4_write_KPM_blAdr1 ,&Data);

//               - для команды КВМ
	ioctl(hARINC,LNXioctl_PCI429_4_write_KVM_blAdr1 ,&Data);

// подготовка данных для команды КПМ
	Data[0] = 256;
	for( ap=0;ap<256;ap++)
	{
		Data[1+ap*2]=0xC000+ap;			
		Data[2+ap*2]=0x8000+ap;			
	}
	ioctl(hARINC,LNXioctl_PCI429_4_write_KPM_blDat1 ,&Data);


  
 //сброс FIFO и инициализация обработчика прерывания
	Data[0] = 1;
	ioctl(hARINC,LNXioctl_PCI429_4_writeRV ,&Data);

   	memset(&action, 0, sizeof(action));

	action.sa_handler = &hINT;
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);

	Data[0] = (short unsigned int) getpid();
 	ioctl(hARINC,LNXioctl_PCI429_4_IntInit ,&Data);


//переход в режим "Работа"
	Data[0] = 0x7310;
	ioctl(hARINC,LNXioctl_PCI429_4_setKCI ,&Data);

//чтение блока состояния модуля
	i = 0;
	do
	{
		ioctl(hARINC,LNXioctl_PCI429_4_getState ,&Data);
		i++;
	}while ((Data[0]!=0xbce)&&(i<1000));

	if((Data[0]!=0xbce)||(Data[1]!=0x7310)||(Data[3]!=0))
	{
		printf("getState = %xh %xh %xh %xh %d\n",Data[0],Data[1],Data[2],Data[3],i);
		ioctl(hARINC,LNXioctl_PCI429_4_readRID ,&Data);
		ioctl(hARINC,LNXioctl_PCI429_4_IntRst ,&Data);
		close(hARINC);
		return;

	}

//для 1-го выходного канала ожидаем установку задания обращением непосредственно к памяти
	i = 0;
	do
	{
	Data[0] = 0x1840;
		ioctl(hARINC,LNXioctl_PCI429_4_readWord ,&Data);
		i++;
	}while ((Data[1]!=0x0)&&(i<1000));

	if(Data[1]!=0)
	{
		printf("0x1840 = %xh  %d\n",Data[1],i);
		ioctl(hARINC,LNXioctl_PCI429_4_readRID ,&Data);
		ioctl(hARINC,LNXioctl_PCI429_4_IntRst ,&Data);
		close(hARINC);
		return;

	}

//для 1-го входного канала ожидаем установку задания чтением блока управления канала
	i = 0;
	do
	{
	Data[0] = 1;
		ioctl(hARINC,LNXioctl_PCI429_4_readBU_I ,&Data);
		i++;
	}while ((Data[0]!=0x0)&&(i<1000));

	if(Data[0]!=0)
	{
		printf("readBU_I = %xh %xh %xh %xh %d\n",Data[0],Data[1],Data[2],Data[3],i);
		ioctl(hARINC,LNXioctl_PCI429_4_readRID ,&Data);
		ioctl(hARINC,LNXioctl_PCI429_4_IntRst ,&Data);
		close(hARINC);
		return;

	}


	printf("Press ENTER for quit \n")	;


   	timer.it_value.tv_sec = 0;
    	timer.it_value.tv_usec = 800000;
    	timer.it_interval.tv_sec = 0;
    	timer.it_interval.tv_usec = 800000;
 


	Data[0] = 0x3c;
	ioctl(hARINC,LNXioctl_PCI429_4_writeKOP_0 ,&Data);
	modeKOP = 1;

	if(TestType==0)
	{
		action.sa_handler = &timerNonstop;
		action.sa_flags = 0;
		sigaction(SIGALRM, &action, NULL);
        
		setitimer(ITIMER_REAL, &timer, NULL);
	}
	else
	{
		action.sa_handler = &timerErrorstop;
		action.sa_flags = 0;
		sigaction(SIGALRM, &action, NULL);

		setitimer(ITIMER_REAL, &timer, NULL);
	}

      	while(getchar()!=0xa);
      							
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;      
	setitimer(ITIMER_REAL, &timer, NULL);




//чтение идентификатора платы
	ioctl(hARINC,LNXioctl_PCI429_4_readRID ,&Data);
	ioctl(hARINC,LNXioctl_PCI429_4_IntRst ,&Data);
	close(hARINC);
}
/*
[home]# gcc tpsPCI429-4.c
[home]# ./a.out
*/
