#ifndef __PCI429_4_IOCTL_H__
#define __PCI429_4_IOCTL_H__


#define LNXioctl_PCI429_4_getSN			0xc0046b64  //_IOWR(pci429_IOC_MAGIC,100, unsigned int)

#define LNXioctl_PCI429_4_getPRM		0xc0046b65  //_IOWR(pci429_IOC_MAGIC,101, unsigned int)

#define LNXioctl_PCI429_4_getState		0xc0046b66  //_IOWR(pci429_IOC_MAGIC,102, unsigned int)
#define LNXioctl_PCI429_4_setFreq		0xc0046b67  //_IOWR(pci429_IOC_MAGIC,103, unsigned int)
#define LNXioctl_PCI429_4_setKCR		0xc0046b68  //_IOWR(pci429_IOC_MAGIC,104, unsigned int)

#define LNXioctl_PCI429_4_setKCI		0xc0046b69  //_IOWR(pci429_IOC_MAGIC,105, unsigned int)


#define LNXioctl_PCI429_4_writeKOP_0		0xc0046b6a  //_IOWR(pci429_IOC_MAGIC,106, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_1		0xc0046b6b  //_IOWR(pci429_IOC_MAGIC,107, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_2		0xc0046b6c  //_IOWR(pci429_IOC_MAGIC,108, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_3		0xc0046b6d  //_IOWR(pci429_IOC_MAGIC,109, unsigned int)


//
#define LNXioctl_PCI429_4_read_BKOP		0xc0046b6e   //IOWR(pci429_IOC_MAGIC,110, 0x4)


//
#define LNXioctl_PCI429_4_read_KPM		0xc0046b6f   //_IOWR(pci429_IOC_MAGIC,111, unsigned int)
#define LNXioctl_PCI429_4_read_KVM		0xc0046b70   //_IOWR(pci429_IOC_MAGIC,112, unsigned int)
#define LNXioctl_PCI429_4_read_KMP		0xc0046b71   //_IOWR(pci429_IOC_MAGIC,113, unsigned int)
#define LNXioctl_PCI429_4_read_KOMP		0xc0046b72   //_IOWR(pci429_IOC_MAGIC,114, unsigned int)

//
#define LNXioctl_PCI429_4_write_KPM_blAdr1		0xc0046b73   //_IOWR(pci429_IOC_MAGIC,115, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blAdr2		0xc0046b74   //_IOWR(pci429_IOC_MAGIC,116, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blDat1		0xc0046b75   //_IOWR(pci429_IOC_MAGIC,117, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blDat2		0xc0046b76   //_IOWR(pci429_IOC_MAGIC,118, unsigned int)
#define LNXioctl_PCI429_4_write_KVM_blAdr1		0xc0046b77   //_IOWR(pci429_IOC_MAGIC,119, unsigned int)
#define LNXioctl_PCI429_4_write_KVM_blAdr2		0xc0046b78   //_IOWR(pci429_IOC_MAGIC,120, unsigned int)
#define LNXioctl_PCI429_4_write_KMP_blAdr		0xc0046b79   //_IOWR(pci429_IOC_MAGIC,121, unsigned int)

//
#define LNXioctl_PCI429_4_read_KVM_blDat1		0xc0046b7a   //_IOWR(pci429_IOC_MAGIC,122, unsigned int)
#define LNXioctl_PCI429_4_read_KVM_blDat2		0xc0046b7b   //_IOWR(pci429_IOC_MAGIC,123, unsigned int)
// 
// 
    
#define LNXioctl_PCI429_4_writeBU_I		0xc0046b7c  //_IOWR(pci429_IOC_MAGIC,124, unsigned int)
//    
#define LNXioctl_PCI429_4_writeBU_O		0xc0046b7d  //_IOWR(pci429_IOC_MAGIC,125, unsigned int)

// 
//  
   
#define LNXioctl_PCI429_4_readBU_I		0xc0046b7e  //_IOWR(pci429_IOC_MAGIC,126, unsigned int)
//     
#define LNXioctl_PCI429_4_readBU_O		0xc0046b7f  //_IOWR(pci429_IOC_MAGIC,127, unsigned int)
// 
//    
#define LNXioctl_PCI429_4_readFL_I		0xc0046b80  //_IOWR(pci429_IOC_MAGIC,128, unsigned int)
//    
#define LNXioctl_PCI429_4_readFL_O		0xc0046b81  //_IOWR(pci429_IOC_MAGIC,129, unsigned int)

// 
//     
#define LNXioctl_PCI429_4_writeTab_I		0xc0046b82  //_IOWR(pci429_IOC_MAGIC,130, unsigned int)
//     
#define LNXioctl_PCI429_4_writeTab_O		0xc0046b83  //_IOWR(pci429_IOC_MAGIC,131, unsigned int)
// 

#define LNXioctl_PCI429_4_writeBKV		0xc0046b84  //_IOWR(pci429_IOC_MAGIC,132, unsigned int)

#define LNXioctl_PCI429_4_writeBKV2		0xc0046b85  //_IOWR(pci429_IOC_MAGIC,133, unsigned int)
#define LNXioctl_PCI429_4_writeBG		0xc0046b86  //_IOWR(pci429_IOC_MAGIC,134, unsigned int)

//  
#define LNXioctl_PCI429_4_readMem		0xc0046b87  //_IOWR(pci429_IOC_MAGIC,0135, unsigned int)
#define LNXioctl_PCI429_4_writeMem		0xc0046b88  //_IOWR(pci429_IOC_MAGIC,0x136, unsigned int)

#define LNXioctl_PCI429_4_readWord		0xc0046b89  //_IOWR(pci429_IOC_MAGIC,137, unsigned int)

#define LNXioctl_PCI429_4_writeWord		0xc0046b8A  //_IOWR(pci429_IOC_MAGIC,138, unsigned int)

  
#define LNXioctl_PCI429_4_readRA		0xc0046b8b   //_IOWR(pci429_IOC_MAGIC,139,unsigned int)
#define LNXioctl_PCI429_4_writeRA		0xc0046b8c   //_IOWR(pci429_IOC_MAGIC,140,unsigned int)
#define LNXioctl_PCI429_4_readRD		0xc0046b8d   //_IOWR(pci429_IOC_MAGIC,141,unsigned int)
#define LNXioctl_PCI429_4_writeRD		0xc0046b8e   //_IOWR(pci429_IOC_MAGIC,142,unsigned int)

#define LNXioctl_PCI429_4_readRID		0xc0046b8f   //_IOWR(pci429_IOC_MAGIC,143,unsigned int)
#define LNXioctl_PCI429_4_writeRM		0xc0046b90   //_IOWR(pci429_IOC_MAGIC,144,unsigned int)

#define LNXioctl_PCI429_4_readRDP		0xc0046b91   //_IOWR(pci429_IOC_MAGIC,145,unsigned int)
#define LNXioctl_PCI429_4_writeRDV		0xc0046b92   //_IOWR(pci429_IOC_MAGIC,146,unsigned int)
#define LNXioctl_PCI429_4_readRV		0xc0046b93//  _IOWR(pci429_IOC_MAGIC,147,unsigned int)
#define LNXioctl_PCI429_4_writeRV		0xc0046b94//  _IOWR(pci429_IOC_MAGIC,148,unsigned int)
#define LNXioctl_PCI429_4_writeRCA		0xc0046b95   //_IOWR(pci429_IOC_MAGIC,149,unsigned int)
#define LNXioctl_PCI429_4_writeDV1		0xc0046b96   //_IOWR(pci429_IOC_MAGIC,150,unsigned int)
#define LNXioctl_PCI429_4_writeDV2		0xc0046b97   //_IOWR(pci429_IOC_MAGIC,151,unsigned int)


#define LNXioctl_PCI429_4_IntInit		0xc0046b98  //_IOWR(pci429_IOC_MAGIC,152, unsigned int)
#define LNXioctl_PCI429_4_IntRst		0xc0046b99  //_IOWR(pci429_IOC_MAGIC,153, unsigned int)

#define LNXioctl_PCI429_4_readPK		0xc0046b9a  //_IOWR(pci429_IOC_MAGIC,154, unsigned int)
#define LNXioctl_PCI429_4_writePK		0xc0046b9b  //_IOWR(pci429_IOC_MAGIC,155, unsigned int)

#define PCI429_4_IOCTL_SEND             0xc0046b9c  //_IOWR(pci429_IOC_MAGIC,155, unsigned int)
#define PCI429_4_IOCTL_READ             0xc0046b9d  //_IOWR(pci429_IOC_MAGIC,155, unsigned int)

//

#define KVP(hDevice,Data,adr)	Data[0] =0x2;	\
			Data[1] = (unsigned short)adr;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data)

#define KPP(hDevice,Data,adr,prm)	Data[0] =0x3;	\
			Data[1] = (unsigned short)adr;\
			Data[2] = (unsigned short)(prm&0xffff);\
			Data[3] = (unsigned short)(((prm)>>16)&0xffff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_3,&Data )


#define KMP(hDevice,Data) Data[0] = 0x4;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KCB(hDevice,Data,msk)	Data[0] = 0x5;\
			Data[1] = (unsigned short)msk;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )

#define KCT(hDevice,Data) Data[0]=0x6;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
			
	
#define KPT(hDevice,Data,tmr)	Data[0] = 0x7; Data[1] = (unsigned short)tmr;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )


#define KVM0(hDevice,Data )	Data[0] = 0x8;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM1(hDevice,Data )	Data[0] = 0x9;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM2(hDevice,Data )	Data[0] = 0xA;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM3(hDevice,Data )	Data[0] = 0xB;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM4(hDevice,Data )	Data[0] = 0xC;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM5(hDevice,Data )	Data[0] = 0xD;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM6(hDevice,Data )	Data[0] = 0xE;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )
#define KVM7(hDevice,Data )	Data[0] = 0xF;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )


//безусловный спуск задания режима входному каналу

#define KP_PFA_BKP(hDevice,Data ,nc,ch,m_ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = ((m_ch&1)<<15)|(ch&0x3ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )

#define KP_PFA_BKP2(hDevice,Data ,nc,ch,m_ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = ((m_ch&1)<<15)|(0x400)|(ch&0x1ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )

#define KP_PFR_BKP(hDevice,Data ,nc,ch,m_ch)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = ((m_ch&1)<<15)|(0x1000)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KP_PFR_BKP2(hDevice,Data ,nc,ch,m_ch)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = ((m_ch&1)<<15)|(0x1400)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KP_PFC_BKP(hDevice,Data ,nc,ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = (0x1800)|(ch&0x3ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )
#define KP_PFC_BKP2(hDevice,Data ,nc,ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = (0x1C00)|(ch&0x1ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )
#define KP_PA_BKP1(hDevice,Data ,nc,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = 0x2000;\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )
#define KP_PA_BKP2(hDevice,Data ,nc,ap,m_ap)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = 0x2400;\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )
#define KP_PG(hDevice,Data ,nc)	Data[0] =((nc-1)&0xF)+0x10;	\
			Data[1] = 0x3000;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )



//безусловный спуск задания выходному каналу
#define KV_VR_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VR_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0x400)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VC_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0x800)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VC_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0xC00)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VO_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0x1800)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VO_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0x1C00)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )
#define KV_VG(hDevice,Data ,nc,m)	Data[0] =((nc-1)&0xF)+0x20;	\
			Data[1] = ((m&1)<<15)|(0x2000);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_1,&Data )

//обнулить массив числа слов
#define KOM(hDevice,Data ,am,ch)	Data[0] =0x30;	\
			Data[1] = (unsigned short)am;\
			Data[2] = (unsigned short)ch;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )
#define KOMP(hDevice,Data ,am,ch)	Data[0] =0x31;	\
			Data[1] = (unsigned short)am;\
			Data[2] = (unsigned short)ch;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_2,&Data )

// передать массив параметров
#define KPM0(hDevice,Data )	Data[0] = 0x38;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM1(hDevice,Data )	Data[0] = 0x39;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM2(hDevice,Data )	Data[0] = 0x3A;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM3(hDevice,Data )	Data[0] = 0x3B;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM4(hDevice,Data )	Data[0] = 0x3C;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM5(hDevice,Data )	Data[0] = 0x3D;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM6(hDevice,Data )	Data[0] = 0x3E;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )

#define KPM7(hDevice,Data )	Data[0] = 0x3F;	\
			ioctl(hDevice,LNXioctl_PCI429_4_writeKOP_0,&Data )


//
#define PFA_BKP(hDevice,Data ,nc,ch,m_ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m_ch&1)<<15)|(ch&0x3ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PFA_BKP2(hDevice,Data ,nc,ch,m_ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m_ch&1)<<15)|(0x400)|(ch&0x1ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PFR_BKP(hDevice,Data ,nc,ch,m_ch)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m_ch&1)<<15)|(0x1000)|(ch&0x3ff);\
			Data[2] = 0;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PFR_BKP2(hDevice,Data ,nc,ch,m_ch)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m_ch&1)<<15)|(0x1400)|(ch&0x1ff);\
			Data[2] = 0;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PFC_BKP(hDevice,Data ,nc,ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = (0x1800)|(ch&0x3ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PFC_BKP2(hDevice,Data ,nc,ch,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = (0x1C00)|(ch&0x1ff);\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PA_BKP1(hDevice,Data ,nc,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = 0x2000;\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PA_BKP2(hDevice,Data ,nc,ap,m_ap)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = 0x2400;\
			Data[2] = (unsigned short)(((m_ap&1)<<13)|(ap&0xff));\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )
#define PG(hDevice,Data ,nc)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = 0x3000;\
			Data[2] = 0;\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_I,&Data )



//
#define VR_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VR_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0x400)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VC_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0x800)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VC_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0xC00)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VO_BKV(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0x1800)|(ch&0x3ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VO_BKV2(hDevice,Data ,nc,ch,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0x1C00)|(ch&0x1ff);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )
#define VG(hDevice,Data ,nc,m)	Data[0] =((nc-1)&0xF)+1;	\
			Data[1] = ((m&1)<<15)|(0x2000);\
			ioctl(hDevice,LNXioctl_PCI429_4_writeBU_O,&Data )

//Подготовка расписания канала, работающего в глобальном режиме.

//Выходные каналы.

#define TAB_VG_WORD(Data,ss,adr,km,nl)	Data[ss+2] =((km&0x1)<<14)+((nl&0x1)<<13)+(adr&0x1fff)


#define TAB_VG_PAUSE(Data, ss, ch_p)	Data[ss+2] =(ch_p&0x1FF)+0x8000

//Входные каналы.

#define TAB_PG_WORD(Data,ap,adr,m)	Data[ap+2] =((m&0x1)<<15)+0x2000+(adr&0x1fff)


#define TAB_PG_PAUSE(Data, ap)	Data[ap+2] =0


#endif //__PCI429_4_IOCTL_H__
