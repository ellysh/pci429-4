#ifndef __PCI429_4_H__
#define __PCI429_4_H__

#include <linux/ioctl.h>

#define pci429_IOC_MAGIC 'k'
//
#define LNXioctl_PCI429_4_getSN			_IOWR(pci429_IOC_MAGIC,100, unsigned int)
#define LNXioctl_PCI429_4_getPRM		_IOWR(pci429_IOC_MAGIC,101, unsigned int)
#define LNXioctl_PCI429_4_getState		_IOWR(pci429_IOC_MAGIC,102, unsigned int)

// 
#define LNXioctl_PCI429_4_setFreq		_IOWR(pci429_IOC_MAGIC,103, unsigned int)
#define LNXioctl_PCI429_4_setKCR		_IOWR(pci429_IOC_MAGIC,104, unsigned int)
#define LNXioctl_PCI429_4_setKCI		_IOWR(pci429_IOC_MAGIC,105, unsigned int)

// 
#define LNXioctl_PCI429_4_writeKOP_0		_IOWR(pci429_IOC_MAGIC,106, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_1		_IOWR(pci429_IOC_MAGIC,107, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_2		_IOWR(pci429_IOC_MAGIC,108, unsigned int)
#define LNXioctl_PCI429_4_writeKOP_3		_IOWR(pci429_IOC_MAGIC,109, unsigned int)


//
#define LNXioctl_PCI429_4_read_BKOP		_IOWR(pci429_IOC_MAGIC,110, unsigned int)


//
#define LNXioctl_PCI429_4_read_KPM		_IOWR(pci429_IOC_MAGIC,111, unsigned int)
#define LNXioctl_PCI429_4_read_KVM		_IOWR(pci429_IOC_MAGIC,112, unsigned int)
#define LNXioctl_PCI429_4_read_KMP		_IOWR(pci429_IOC_MAGIC,113, unsigned int)
#define LNXioctl_PCI429_4_read_KOMP		_IOWR(pci429_IOC_MAGIC,114, unsigned int)

//
#define LNXioctl_PCI429_4_write_KPM_blAdr1		_IOWR(pci429_IOC_MAGIC,115, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blAdr2		_IOWR(pci429_IOC_MAGIC,116, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blDat1		_IOWR(pci429_IOC_MAGIC,117, unsigned int)
#define LNXioctl_PCI429_4_write_KPM_blDat2		_IOWR(pci429_IOC_MAGIC,118, unsigned int)
#define LNXioctl_PCI429_4_write_KVM_blAdr1		_IOWR(pci429_IOC_MAGIC,119, unsigned int)
#define LNXioctl_PCI429_4_write_KVM_blAdr2		_IOWR(pci429_IOC_MAGIC,120, unsigned int)
#define LNXioctl_PCI429_4_write_KMP_blAdr		_IOWR(pci429_IOC_MAGIC,121, unsigned int)

//
#define LNXioctl_PCI429_4_read_KVM_blDat1		_IOWR(pci429_IOC_MAGIC,122, unsigned int)
#define LNXioctl_PCI429_4_read_KVM_blDat2		_IOWR(pci429_IOC_MAGIC,123, unsigned int)
// 
//     
#define LNXioctl_PCI429_4_writeBU_I		_IOWR(pci429_IOC_MAGIC,124, unsigned int)
//    
#define LNXioctl_PCI429_4_writeBU_O		_IOWR(pci429_IOC_MAGIC,125, unsigned int)

// 
//     
#define LNXioctl_PCI429_4_readBU_I		_IOWR(pci429_IOC_MAGIC,126, unsigned int)
//     
#define LNXioctl_PCI429_4_readBU_O		_IOWR(pci429_IOC_MAGIC,127, unsigned int)

// 
//    
#define LNXioctl_PCI429_4_readFL_I		_IOWR(pci429_IOC_MAGIC,128, unsigned int)
//    
#define LNXioctl_PCI429_4_readFL_O		_IOWR(pci429_IOC_MAGIC,129, unsigned int)

// 
//     
#define LNXioctl_PCI429_4_writeTab_I		_IOWR(pci429_IOC_MAGIC,130, unsigned int)
//     
#define LNXioctl_PCI429_4_writeTab_O		_IOWR(pci429_IOC_MAGIC,131, unsigned int)

// 
#define LNXioctl_PCI429_4_writeBKV		_IOWR(pci429_IOC_MAGIC,132, unsigned int)
#define LNXioctl_PCI429_4_writeBKV2		_IOWR(pci429_IOC_MAGIC,133, unsigned int)
#define LNXioctl_PCI429_4_writeBG		_IOWR(pci429_IOC_MAGIC,134, unsigned int)

//  
#define LNXioctl_PCI429_4_readMem		_IOWR(pci429_IOC_MAGIC,135, unsigned int)
#define LNXioctl_PCI429_4_writeMem		_IOWR(pci429_IOC_MAGIC,136, unsigned int)
#define LNXioctl_PCI429_4_readWord		_IOWR(pci429_IOC_MAGIC,137, unsigned int)
#define LNXioctl_PCI429_4_writeWord	_IOWR(pci429_IOC_MAGIC,138, unsigned int)

//  
#define LNXioctl_PCI429_4_readRA		_IOWR(pci429_IOC_MAGIC,139,unsigned int)
#define LNXioctl_PCI429_4_writeRA		_IOWR(pci429_IOC_MAGIC,140,unsigned int)
#define LNXioctl_PCI429_4_readRD		_IOWR(pci429_IOC_MAGIC,141,unsigned int)
#define LNXioctl_PCI429_4_writeRD		_IOWR(pci429_IOC_MAGIC,142,unsigned int)
#define LNXioctl_PCI429_4_readRID		_IOWR(pci429_IOC_MAGIC,143,unsigned int)
#define LNXioctl_PCI429_4_writeRM		_IOWR(pci429_IOC_MAGIC,144,unsigned int)
#define LNXioctl_PCI429_4_readRDP		_IOWR(pci429_IOC_MAGIC,145,unsigned int)
#define LNXioctl_PCI429_4_writeRDV		_IOWR(pci429_IOC_MAGIC,146,unsigned int)
#define LNXioctl_PCI429_4_readRV		_IOWR(pci429_IOC_MAGIC,147,unsigned int)
#define LNXioctl_PCI429_4_writeRV		_IOWR(pci429_IOC_MAGIC,148,unsigned int)
#define LNXioctl_PCI429_4_writeRCA		_IOWR(pci429_IOC_MAGIC,149,unsigned int)
#define LNXioctl_PCI429_4_writeDV1		_IOWR(pci429_IOC_MAGIC,150,unsigned int)
#define LNXioctl_PCI429_4_writeDV2		_IOWR(pci429_IOC_MAGIC,151,unsigned int)


#define LNXioctl_PCI429_4_IntInit		_IOWR(pci429_IOC_MAGIC,152, unsigned int)
#define LNXioctl_PCI429_4_IntRst		_IOWR(pci429_IOC_MAGIC,153, unsigned int)

#define LNXioctl_PCI429_4_readPK		_IOWR(pci429_IOC_MAGIC,154, unsigned int)
#define LNXioctl_PCI429_4_writePK		_IOWR(pci429_IOC_MAGIC,155, unsigned int)

#define PCI429_4_IOCTL_SEND             _IOWR(pci429_IOC_MAGIC,156, unsigned int)
#define PCI429_4_IOCTL_READ             _IOWR(pci429_IOC_MAGIC,157, unsigned int)


#endif //__PCI429_4_H__
