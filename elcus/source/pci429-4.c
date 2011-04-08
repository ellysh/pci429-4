
/*Драйвер PCI429-4 для LINUX
 * (c) ELCUS, 2005.
 *
 * Part of this code comes from the book "Linux Device Drivers"
 * by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.
*/


/*
ядро 2.6.3-7mdk

	параметры BIOS:
APIC запрещен

	сборка драйвера
make  -C /usr/src/linux-2.6.3 SUBDIRS=$PWD modules

	установка драйвера
./pci429Load

Замечание:если драйвер не работает с устройствами номер 1,2 и т.д. следует собрать его заново, определив параметр myDRV

*/


//#define myDRV

//#include <linux/config.h>
#ifdef CONFIG_SMP
# define __SMP__
#endif

#include <linux/version.h>
#include <linux/module.h>   /* Specifically, a module */
#include <linux/kernel.h>   /* We're doing kernel work */
#include <linux/signal.h>
#if ( LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19) )
#include <linux/config.h>   // for PCI, SMP configuration
#endif 
#include <linux/mm.h> 
#include <linux/delay.h> 
#include <linux/pci.h> 
#include <linux/fs.h> 
#include <linux/ioport.h> 
#include <asm/io.h> 
#include <asm/uaccess.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h> 
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <asm/ioctl.h>
#include <linux/kdev_t.h>
#include "pci429-4.h"
#include "tms.h"


#ifndef CONFIG_PCI
#  error "This driver needs PCI support to be available"
#endif


MODULE_LICENSE("GPL");
MODULE_AUTHOR("VERA KOURIANOVA");
MODULE_DESCRIPTION("PCI429_4 device driver");


/* The name for our device, as it will appear 
 * in /proc/devices */

#define PCI429_4_DEVICE_NAME    "pci429_4"
#define PCI429_4_MINOR           MISC_DYNAMIC_MINOR



#define DEVICE_NUMBER 8

typedef struct
{
 unsigned short int 	RA,
			      	RD,
			      	RID ,
			      	RM ,
			      	RV ,
			      	RDV ,
			      	RDP ,
			      	RD2 ,
			      	RCA ,
			      	RDV1 ,
			      	RDV2 ,
			      	r ,
			      	bSN ,
			      	PLX ,
				hSEM,
	       			sigN,
	       			busy;
 struct task_struct * pp;
 unsigned short int freq[ 32 ];
 unsigned int dummy_state;
}PCI429_4_Info,*pPCI429_4;

static PCI429_4_Info aPCI429_4_Info[DEVICE_NUMBER];



//static inline _syscall2(int,kill,unsigned short int, arg1,unsigned short int, arg2);
int errno;


 irqreturn_t irq_handler(int irq, 
                 void *dev_id, 
                 struct pt_regs *regs)
{ 
	PCI429_4_Info* dev = dev_id;

	if ((inw(dev->PLX)&5)==5)
	{	
		outw(0xd53,dev->PLX);
#if ( LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31) )
		send_sig(dev->sigN,dev->pp,0);
#endif
		 return IRQ_HANDLED; 	
	}
	return IRQ_NONE; 
}


					 
spinlock_t pci429_4_lock;

/* Module Declarations ***************************** */

/* The major device number for the device. This is 
 * global (well, static, which in this context is global
 * within this file) because it has to be accessible 
 * both for registration and for release. */

static int Major = 0;

static int pci429_ioctl (struct inode *inode, struct file *filp,
         unsigned int cmd, unsigned long arg)


{
unsigned short int i=0, adr, adrEnd, ind, ch, i1;
unsigned short int work=0;
unsigned short int pos=0;
switch(cmd) 
 {
 	case LNXioctl_PCI429_4_readFL_I:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif

		__get_user(adr, (unsigned short *)(arg));
		adr = RRP_i_ext + ((adr-1)&0xf)*0x80+6;  
		outw( adr,  aPCI429_4_Info[i].RA); 

		work=inw( aPCI429_4_Info[i].RD);
		__put_user ( work,(unsigned short *)(arg+2));

		if (work!=0)
		{
			outw( adr,  aPCI429_4_Info[i].RA); 
			outw( 0,  aPCI429_4_Info[i].RD); 
		}
		spin_unlock(&pci429_4_lock);
		break;
	}

	
	case LNXioctl_PCI429_4_readFL_O:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		adr = RRV_i_ext + ((adr-1)&0xf)*0x80+6;  
		outw( adr,  aPCI429_4_Info[i].RA); 

		work=inw( aPCI429_4_Info[i].RD);
		__put_user ( work,(unsigned short *)(arg+2));

		if (work!=0)
		{
			outw( adr,  aPCI429_4_Info[i].RA); 
			outw( 0,  aPCI429_4_Info[i].RD); 
		}
		spin_unlock(&pci429_4_lock);
		break;
	}


	case LNXioctl_PCI429_4_readPK:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		outw( adr,  aPCI429_4_Info[i].RA);

		i1 = inw( aPCI429_4_Info[i].RD2);
		work=inw( aPCI429_4_Info[i].RD2);
		__put_user ( i1,(unsigned short *)(arg+2));
		__put_user ( work,(unsigned short *)(arg+4));

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writePK:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = (*((&(inode->i_rdev))+2));
#else
		i = (inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		outw( adr,  aPCI429_4_Info[i].RA);

		__get_user(i1, (unsigned short *)(arg+2));
		__get_user(work, (unsigned short *)(arg+4));
		outw( i1,  aPCI429_4_Info[i].RD2);
		outw( work,  aPCI429_4_Info[i].RD2);

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_read_BKOP:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UKOP_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<5; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
//

	case LNXioctl_PCI429_4_read_KPM:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( CPM0_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<4; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_read_KVM:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( CBM0_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<4; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_read_KMP:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( CBP0_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<4; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_read_KOMP:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( CBOM_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<4; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_readBU_I:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif

		__get_user(adr, (unsigned short *)(arg));
		adr = RRP_i_ext + ((adr-1)&0xf)*0x80;  
		outw( adr,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<8; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_readBU_O:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif

		__get_user(adr, (unsigned short *)(arg));
		adr = RRV_i_ext + ((adr-1)&0xf)*0x80;  
		outw( adr,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<8; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
//

	case LNXioctl_PCI429_4_read_KVM_blDat1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BPK1_i_ext,  aPCI429_4_Info[i].RA);

		for(ind=0; ind<512; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_read_KVM_blDat2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BPK2_i_ext,  aPCI429_4_Info[i].RA);

		for(ind=0; ind<512; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeKOP_0:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UKOP_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeKOP_1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UKOP_i_ext+1,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);

		outw( UKOP_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeKOP_2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UKOP_i_ext+1,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);

		__get_user(work, (unsigned short *)(arg+4));
		outw( work,  aPCI429_4_Info[i].RD);

		outw( UKOP_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeKOP_3:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UKOP_i_ext+1,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);

		__get_user(work, (unsigned short *)(arg+4));
		outw( work,  aPCI429_4_Info[i].RD);

		__get_user(work, (unsigned short *)(arg+6));
		outw( work,  aPCI429_4_Info[i].RD);

		outw( UKOP_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);

		spin_unlock(&pci429_4_lock);
		break;
	}


	case LNXioctl_PCI429_4_writeBU_O:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		adr = RRV_i_ext + ((adr-1)&0xf)*0x80;  
		outw( adr,  aPCI429_4_Info[i].RA); 

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);			

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeBU_I:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		adr = RRP_i_ext + ((adr-1)&0xf)*0x80+2;  
		outw( adr,  aPCI429_4_Info[i].RA); 

		__get_user(work, (unsigned short *)(arg+4));
		outw( work,  aPCI429_4_Info[i].RD);		

		adr = adr-2;	
		outw( adr,  aPCI429_4_Info[i].RA); 

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);		

		spin_unlock(&pci429_4_lock);
		break;
	}


//

	case LNXioctl_PCI429_4_write_KPM_blAdr1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BAPMP1_i_ext,  aPCI429_4_Info[i].RA);

		ind=0;
		do	
		{
		__get_user(work, (unsigned short *)(arg+2*ind));
		outw( work,  aPCI429_4_Info[i].RD);		
		ind++;
		}while((ind<256) && ((work&0x8000)!=0));

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_write_KPM_blAdr2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BAPMP2_i_ext,  aPCI429_4_Info[i].RA);

		ind=0;
		do	
		{
		__get_user(work, (unsigned short *)(arg+2*ind));
		outw( work,  aPCI429_4_Info[i].RD);		
		ind++;
		}while((ind<256) && ((work&0x8000)!=0));

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_write_KPM_blDat1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BPMP1_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg));
		ch = ch*2;

		for (ind = 1; ind<=ch; ind++)	
		{
			__get_user(work, (unsigned short *)(arg+2*ind));
			outw( work,  aPCI429_4_Info[i].RD);		
		}


		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_write_KPM_blDat2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BPMP2_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg));
		ch = ch*2;

		for (ind = 1; ind<=ch; ind++)	
		{
			__get_user(work, (unsigned short *)(arg+2*ind));
			outw( work,  aPCI429_4_Info[i].RD);		
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_write_KVM_blAdr1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BAP1_i_ext,  aPCI429_4_Info[i].RA);

		ind=0;
		do	
		{
		__get_user(work, (unsigned short *)(arg+2*ind));
		outw( work,  aPCI429_4_Info[i].RD);		
		ind++;
		}while((ind<256) && ((work&0xC000)!=0));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_write_KVM_blAdr2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BAP2_i_ext,  aPCI429_4_Info[i].RA);

		ind=0;
		do	
		{
		__get_user(work, (unsigned short *)(arg+2*ind));
		outw( work,  aPCI429_4_Info[i].RD);		
		ind++;
		}while((ind<256) && ((work&0xC000)!=0));

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_write_KMP_blAdr:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( BAPP_i_ext,  aPCI429_4_Info[i].RA);

		ind=0;
		do	
		{
		__get_user(work, (unsigned short *)(arg+2*ind));
		outw( work,  aPCI429_4_Info[i].RD);		
		ind++;
		}while((ind<256) && (work!=0));

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_getSN:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__put_user (  aPCI429_4_Info[i].bSN,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_getState:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
//		if( aPCI429_4_Info[i].busy != 1 ) {
//			aPCI429_4_Info[i].dummy_state = !aPCI429_4_Info[i].dummy_state;
//			{
//				if( aPCI429_4_Info[i].dummy_state ) { work=0xbcc; }
//				else { work=0xbce; }
//				__put_user ( work,(unsigned short *)(arg+0*2));
//				__put_user ( 0x7310,(unsigned short *)(arg+1*2));
//				__put_user ( 0x0,(unsigned short *)(arg+2*2));
//				__put_user ( 0x0,(unsigned short *)(arg+3*2));
//			}
//			spin_unlock(&pci429_4_lock);
//			break;
//		}
		outw( CIA_i_ext,  aPCI429_4_Info[i].RA);

		for	 ( ind=0;ind<4; ind++)
		{
			work=inw( aPCI429_4_Info[i].RD);
			__put_user ( work,(unsigned short *)(arg+ind*2));
		}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_IntInit:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif

		__get_user( aPCI429_4_Info[i].hSEM,(int *)(arg));
//		if( aPCI429_4_Info[i].busy == 1 ) {
#if ( LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31) )
		 aPCI429_4_Info[i].pp = find_task_by_vpid(aPCI429_4_Info[i].hSEM);
#else
		 aPCI429_4_Info[i].pp = NULL;
#endif
		 aPCI429_4_Info[i].sigN=SIGUSR1;
		outw( 0xd53,  aPCI429_4_Info[i].PLX);
//		}
//		else {
//		    printk("pci429-4: intInit skipped\n" );
//		}

		spin_unlock(&pci429_4_lock);
		break;
	}
	
	case LNXioctl_PCI429_4_IntRst:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
//		 if( aPCI429_4_Info[i].busy == 1 ) {
		     aPCI429_4_Info[i].hSEM = 0;
		     aPCI429_4_Info[i].sigN = 0;
		     outw( 0xd12,  aPCI429_4_Info[i].PLX);
//		 }
//		 else {
//		     printk("pci429-4: intRst skipped\n" );
//		 }
		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_getPRM:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__put_user ( ( aPCI429_4_Info[i].PLX-0x4c),(unsigned short *)(arg));
		__put_user (  aPCI429_4_Info[i].RA,(unsigned short *)(arg+2));
		__put_user (  aPCI429_4_Info[i].r,(unsigned short *)(arg+4));

		spin_unlock(&pci429_4_lock);
		break;
	}


	case LNXioctl_PCI429_4_writeBKV:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));

		work = ((work-1)&0xf)*0x400 + bufO_i_ext;
		outw( work,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg+2));
		ch = ch*2;

		if( ch>0x400) ch = 0x400;

		for(ind = 0;ind<ch;ind++)
			{
			__get_user(work, (unsigned short *)(arg+4+ind*2));
			outw( work, aPCI429_4_Info[i].RD);
			
 //printk("<1>writeBKV = %x\n",work);
			}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeBKV2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));

		work = ((work-1)&0xf)*0x400 + bufO_i_ext+0x200;
		outw( work,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg+2));
		ch = ch*2;

		if( ch>0x200) ch = 0x200;

		for(ind = 0;ind<ch;ind++)
			{
			__get_user(work, (unsigned short *)(arg+4+ind*2));
			outw( work, aPCI429_4_Info[i].RD);
			
			}

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeBG:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		__get_user(ch, (unsigned short *)(arg+2));
		ch = ch*2;

		if (adr<0xC000)
		{
			__put_user ( 1,(unsigned short *)(arg));
			break;
		}
	
		if  (((unsigned short)(adr+ch))<adr) ch =(unsigned short)( 0x10000 - adr);
		ind = 0;

		while(ind<ch)
		{
			outw( adr, aPCI429_4_Info[i].RA);
			adrEnd = (adr&0xFC00)+0x400;

			i1 = 0;

			if ( adr>=0xfc00 )
			{
				while(ind<ch)
				{
					__get_user(work, (unsigned short *)(arg+4+ind*2));
					outw( work, aPCI429_4_Info[i].RD);
					ind++;
				}
			}
			else
			{
				while((ind<ch) && ((adr+i1)<adrEnd))
				{
					__get_user(work, (unsigned short *)(arg+4+ind*2));
					outw( work, aPCI429_4_Info[i].RD);
					ind++;
					i1++;
				}
			}
			adr = adrEnd;
		}
		__put_user ( 0,(unsigned short *)(arg));


		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeTab_I:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		work = ((work-1)&0xf)*0x400 + bufI_i_ext;
		outw( work,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg+2));

		ind = 0;
		while((ind<ch) && (ind<0x400))
		{
			__get_user(work, (unsigned short *)(arg+4+ind*2));
			outw( work,  aPCI429_4_Info[i].RD);
			ind++;
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_writeTab_O:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		work = ((work-1)&0xf)*0x400 + bufO_i_ext;
		outw( work,  aPCI429_4_Info[i].RA);

		__get_user(ch, (unsigned short *)(arg+2));

		ind = 0;
		while((ind<ch) && (ind<0x400))
		{
			__get_user(work, (unsigned short *)(arg+4+ind*2));
			outw( work,  aPCI429_4_Info[i].RD);
			ind++;
		}

		spin_unlock(&pci429_4_lock);
		break;
	}

	case  LNXioctl_PCI429_4_readRV:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		work=inw( aPCI429_4_Info[i].RV);
		__put_user ( work,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRV:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RV);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRCA:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RCA);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeDV1:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RDV1);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeDV2:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RDV2);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_readRA:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		work=inw( aPCI429_4_Info[i].RA);
		__put_user ( work,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRA:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RA);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_readRD:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		work=inw( aPCI429_4_Info[i].RD);
		__put_user ( work,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRD:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRM:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RM);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_readRDP:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		work=inw( aPCI429_4_Info[i].RDP);
		__put_user ( work,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_writeRDV:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RDV);

		spin_unlock(&pci429_4_lock);
		break;
	}
	case LNXioctl_PCI429_4_readRID:
	{

		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
//		if( aPCI429_4_Info[i].busy == 1 ) {
		    work=inw( aPCI429_4_Info[i].RID);  
		    __put_user ( work,(unsigned short *)(arg));
//		}
//		else {
//		    printk("pci429-4: readRID skipped\n" );
//		}

		spin_unlock(&pci429_4_lock);

		break;
	}

//

	case LNXioctl_PCI429_4_readMem:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		__get_user(ch, (unsigned short *)(arg+2));

		if  (((unsigned short)(adr+ch))<adr) ch =(unsigned short)( 0x10000 - adr);
		ind = 0;
		
		while(ind<ch)
		{
			outw( adr, aPCI429_4_Info[i].RA);
			adrEnd = (adr&0xFC00)+0x400;

			i1 = 0;

			if ( adr>=0xfc00 )
			{
				while(ind<ch)
				{
					work=inw( aPCI429_4_Info[i].RD);
					__put_user ( work,(unsigned short *)(arg+4+ind*2));
					ind++;
				}
			}
			else
			{
				while((ind<ch) && ((adr+i1)<adrEnd))
				{
					work=inw( aPCI429_4_Info[i].RD);
					__put_user ( work,(unsigned short *)(arg+4+ind*2));
					ind++;
					i1++;
				}
			}
			adr = adrEnd;
		}
		__put_user ( 0,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
			break;
	}


	case LNXioctl_PCI429_4_writeMem:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(adr, (unsigned short *)(arg));
		__get_user(ch, (unsigned short *)(arg+2));

		if  (((unsigned short)(adr+ch))<adr) ch =(unsigned short)( 0x10000 - adr);

		ind = 0;

		while(ind<ch)
		{
			outw( adr, aPCI429_4_Info[i].RA);
			adrEnd = (adr&0xFC00)+0x400;

			i1 = 0;

			if ( adr>=0xfc00 )
			{
				while(ind<ch)
				{
					__get_user(work, (unsigned short *)(arg+4+ind*2));
					outw( work, aPCI429_4_Info[i].RD);
					ind++;
				}
			}
			else
			{
				while((ind<ch) && ((adr+i1)<adrEnd))
				{
					__get_user(work, (unsigned short *)(arg+4+ind*2));
					outw( work, aPCI429_4_Info[i].RD);
					ind++;
					i1++;
				}
			}
			adr = adrEnd;
		}
		__put_user ( 0,(unsigned short *)(arg));

		spin_unlock(&pci429_4_lock);
		break;
	}


	case LNXioctl_PCI429_4_readWord:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RA);

		work=inw( aPCI429_4_Info[i].RD);
		__put_user ( work,(unsigned short *)(arg+2));
	

		spin_unlock(&pci429_4_lock);
		break;
	}


	case LNXioctl_PCI429_4_writeWord:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg+2));
		outw( work,  aPCI429_4_Info[i].RD);


		spin_unlock(&pci429_4_lock);
		break;
	}

		
	case LNXioctl_PCI429_4_setFreq:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif

		{
		    unsigned short iotype, ch, freq;
		    
		    __get_user( work, (unsigned short *)(arg) );
		    __get_user( freq, (unsigned short *)(arg+2) );
		    iotype = work / 16;
		    ch     = work % 16;
		    printk("pci429-4: setFreq: ch=%d io=%d freq=%x\n", ch, iotype, freq );
		    aPCI429_4_Info[i].freq[ work-1 ] = freq;
		}
		printk("pci429-4: setFreqIn: " );
		for( ind = 0; ind < 16; ind++ ) printk("%d", aPCI429_4_Info[i].freq[ind] ); printk("\n" );
		printk("pci429-4: setFreqOut: " );
		for( ind = 16; ind < 32; ind++ ) printk("%d", aPCI429_4_Info[i].freq[ind] ); printk("\n" );

		adr = RRP_i_ext + 7;
		for(ind = 0; ind<16; ind++)
		{
			outw( adr,  aPCI429_4_Info[i].RA);
			//__get_user(work, (unsigned short *)(arg+ind*2));
			work = aPCI429_4_Info[i].freq[ ind ];
			outw( work,  aPCI429_4_Info[i].RD);
			adr = adr + 0x80;
		}

	
		adr = RRV_i_ext + 7;
		for(ind = 0; ind<16; ind++)
		{
			outw( adr,  aPCI429_4_Info[i].RA);
			//__get_user(work, (unsigned short *)(arg+ind*2+32));
			work = aPCI429_4_Info[i].freq[ 16+ind ];
			outw( work,  aPCI429_4_Info[i].RD);
			adr = adr + 0x80;
		}


		spin_unlock(&pci429_4_lock);
		break;
	}

	case LNXioctl_PCI429_4_setKCR:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UCMT_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);
			

		spin_unlock(&pci429_4_lock);
		break;
	}		
	
	case LNXioctl_PCI429_4_setKCI:
	{
		spin_lock(&pci429_4_lock);

#if defined myDRV
		i = MINOR(*((&(inode->i_rdev))+2));
#else
		i = MINOR(inode->i_rdev);
#endif
		outw( UNI_i_ext,  aPCI429_4_Info[i].RA);

		__get_user(work, (unsigned short *)(arg));
		outw( work,  aPCI429_4_Info[i].RD);
			

		spin_unlock(&pci429_4_lock);
		break;
	}

	////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
	// TODO Gurov begins:
   case PCI429_4_IOCTL_SEND:
    {
        spin_lock(&pci429_4_lock);

#if defined myDRV
        i = MINOR(*((&(inode->i_rdev))+2));
#else
        i = MINOR(inode->i_rdev);
#endif

        //piece of LNXioctl_PCI429_4_writeBKV:
        __get_user(work, (unsigned short *)(arg));

        adr = work; ///!!!
        work = ((work-1)&0xf)*0x400 + bufO_i_ext;
        outw( work,  aPCI429_4_Info[i].RA);

        __get_user(ch, (unsigned short *)(arg+2));
        pos = ch & 0x3ff; ///!!!
        ch = ch*2;

        if( ch>0x400) ch = 0x400;

        for(ind = 0;ind<ch;ind++)
            {
            __get_user(work, (unsigned short *)(arg+4+ind*2));
            outw( work, aPCI429_4_Info[i].RD);
            }

        //piece of LNXioctl_PCI429_4_writeBU_O:
//        __get_user(adr, (unsigned short *)(arg));
        adr = RRV_i_ext + ((adr-1)&0xf)*0x80;
        outw( adr,  aPCI429_4_Info[i].RA);

        outw( pos,  aPCI429_4_Info[i].RD);

        spin_unlock(&pci429_4_lock);
        break;
    }

    ////////////////////////////////////////////////////////////////////////////
	}
	return 0;  
}


static int pci429_open(struct inode *inode, struct file *filp)
{
  unsigned  int  i;
   int result;
//	 pPCI429_4 dev ;

	spin_lock(&pci429_4_lock);

#if defined myDRV
	i = MINOR(*((&(inode->i_rdev))+2));
#else
	i = MINOR(inode->i_rdev);
#endif

    aPCI429_4_Info[i].busy++;
    try_module_get(THIS_MODULE);
    if( aPCI429_4_Info[i].busy==1 ) {
#define SA_INTERRUPT 0
#define SA_SHIRQ     IRQF_SHARED
        result = request_irq(aPCI429_4_Info[i].r,irq_handler,SA_INTERRUPT|SA_SHIRQ, "pci429_4", &aPCI429_4_Info[i]);
    }
    spin_unlock(&pci429_4_lock);
    return( 0 );
}






static int pci429_release(struct inode *inode, struct file *filp)
{

  unsigned short int i;

	spin_lock(&pci429_4_lock);

#if defined myDRV
	i = MINOR(*((&(inode->i_rdev))+2));
#else
	i = MINOR(inode->i_rdev);
#endif

    aPCI429_4_Info[i].busy--;
    if( aPCI429_4_Info[i].busy == 0 ) {
        free_irq( aPCI429_4_Info[i].r,&aPCI429_4_Info[i]);
    }

    module_put(THIS_MODULE);
    spin_unlock(&pci429_4_lock);
    return 0;
}

/* This structure will hold the functions to be 
 * called when a process does something to the device 
 * we created.*/

static const struct file_operations pci429_4_fops = {
 .owner   =     THIS_MODULE,
 .ioctl   =   	pci429_ioctl,
 .open    = 	pci429_open,
 .release = 	pci429_release
};

static struct miscdevice pci429_4_dev = {
        .minor	 =  PCI429_4_MINOR,
        .name    =  PCI429_4_DEVICE_NAME,
        .fops    =  &pci429_4_fops
};

unsigned short ptr, SN[6];

static int __init  pci429_4_initialization(void)

{
   unsigned long int  ch1,sss;
   unsigned short  m, number = 0, temp, i;
   struct pci_dev *dev = NULL;

//   return( -ENODEV );
    memset( aPCI429_4_Info, 0x0, sizeof( aPCI429_4_Info ) );

 /* Register the character device (atleast try) */
#if 1
  Major = register_chrdev(0, 
                          PCI429_4_DEVICE_NAME,
                          &pci429_4_fops);
 //                         &pci429_fops);
#else
   Major = misc_register( &pci429_4_dev );
#endif
   if (Major < 0)
   {
    printk ("<1>%s device pci429_4 failed with %d\n",
	    "Sorry, registering the character",
	    Major);
    return Major;
   }
  
    printk ("<1>%s The major pci429 device number is %d.\n",
          "Registeration is a success.",
          Major);

          
          
    dev = pci_get_device(0x10b5,0x9030, dev);
   

 while (dev)
	{
		pci_read_config_word(dev, 0x2c, &ptr);

	    	if (ptr==0xe1c5) 
	    	{
			pci_read_config_word(dev, 0x2e, &ptr);
 
	    		if (ptr==0x0202) 
	    		{
				pci_read_config_word(dev, 0x14, &temp);
				temp = (temp & 0xfffe) + 0x4c;
				 aPCI429_4_Info[number].PLX =  temp;
 //printk("<1>Hello,  0x18 = %xh\n",temp);
// printk("<1>Hello, PLX = %xh\n", aPCI429_4_Info[number].PLX);

				pci_read_config_word(dev, 0x18, &temp);
				temp &=0xfffe;
//printk("<1>Hello,  temp = %xh\n",temp);
				 aPCI429_4_Info[number].RA  =  temp;
				 aPCI429_4_Info[number].RD  =  temp+0x2;
				 aPCI429_4_Info[number].RID =  temp+0x4;
				 aPCI429_4_Info[number].RM  =  temp+0x4;
				aPCI429_4_Info[number].RV  =  temp+0x6;
				aPCI429_4_Info[number].RDV =  temp+0x8;
				aPCI429_4_Info[number].RDP =  temp+0x8;
				aPCI429_4_Info[number].RD2 =  temp+0xA;
				aPCI429_4_Info[number].RCA =  temp+0xC;
				aPCI429_4_Info[number].RDV1 = temp+0xC;
				aPCI429_4_Info[number].RDV2 = temp+0xE;

				pci_read_config_word(dev, 0x3c, &temp);
				temp &=0xff;
				aPCI429_4_Info[number].r=(unsigned short) temp;
 //printk("<1>Hello,  0x3c = %xh\n",r[number]);
				ptr=0;
				pci_write_config_word(dev, 0x4e, 0xcc);
	
				m=0; ch1=0;
	
				while(!(m&0x8000))
				{
					pci_read_config_word(dev, 0x4e, 					(u16*)&m);
					ch1++;
					if(ch1==0xfff)
					{
						ch1=0;
						pci_write_config_word(dev, 							0x4e, 0xcc);
					}
				};
	
 //printk("<1>Hello, m = %xh\n",m);
 //printk("<1>Hello, ch1 = %xh\n",ch1);
 
 
		
				pci_read_config_dword(dev, 0x50,(u32 *) 				&sss);

 //printk("<1>Hello, ptr = %d\n",sss);
				SN[0]=(sss>>16)&0xff;
				SN[1]=(sss>>24)&0xff;


				pci_write_config_word(dev, 0x4e, 0xd0);
				m=0; ch1=0;
	
				while(!(m&0x8000))
				{
					pci_read_config_word(dev, 0x4e, 					(u16*)&m);
					ch1++;
					if(ch1==0xfff)
					{
						ch1=0;
						pci_write_config_word(dev, 							0x4e, 0xd0);
					}
				};
	
				pci_read_config_dword(dev, 0x50, (u32 *)				&sss);
 //printk("<1>Hello, config = %d\n",sss);

     				SN[2]=sss&0xff;
				SN[3]=(sss>>8)&0xff;
     				SN[4]=(sss>>16)&0xff;
				aPCI429_4_Info[number].bSN =(SN[0]-0x30)*10000+(SN[1]-				0x30)*1000+(SN[2]-0x30)*100+(SN[3]-0x30)*10+(SN[4]-0x30);

//printk("<1>bSN[0] = %d\n",bSN[number]);
				number++;

			}
		}
 	    dev = pci_get_device(0x10b5,0x9030, dev);
 
	}
	for (i=0; i<DEVICE_NUMBER; i++)
		 aPCI429_4_Info[i].busy= 0;

	spin_lock_init(&pci429_4_lock);
    
    return 0; 
}

static void __exit pci429_4_cleanup(void) 
{
 int ret;
// int  i;

  /* Unregister the device */
  /*ret = */
  
#if 1
    unregister_chrdev(Major, PCI429_4_DEVICE_NAME);
#else
    misc_deregister( &pci429_4_dev );
#endif

 
  /* If there's an error, report it */ 
/*  if (ret < 0)
    printk("Error in unregister_chrdev: %d\n", ret);
    else
    {
 }*/

}
module_init(pci429_4_initialization);
module_exit(pci429_4_cleanup);

