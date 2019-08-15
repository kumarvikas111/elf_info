#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "findabi.h"

extern elf_library_list * info_elf_data;
extern int dbg_print;
Elf64_Ehdr elf_header;
char ret_buf[MAX] = {0};
int check_elf(Elf64_Ehdr *e_header){
	if ( ! strncmp((char *) e_header->e_ident,"\177ELF",4)) {
		return 1;
	}
	return 0;	
}


char * elf_info_update(void *buf){
	if (NULL == buf) {
		return NULL;
	}
	memset(ret_buf,0,MAX);
//	 ret_buf = {0};
	if (check_elf((Elf64_Ehdr *)buf) == 0){
		return NULL;
	}
	Elf64_Ehdr * e_header = (Elf64_Ehdr *) buf;

	switch( e_header->e_machine){

		case  EM_NONE:  //		 0	/* No machine */
			strcpy(ret_buf,"no_machine");
			break;
		case  EM_M32:   //		 1	/* AT&T WE 32100 */
			strcpy(ret_buf,"at&t");
			break;
		case  EM_SPARC: //	 2	/* SUN SPARC */
			strcpy(ret_buf,"sun_sparc");
			break;
		case  EM_386:	//	 3	/* Intel 80386 */
			strcpy(ret_buf,"x86");
			break;
		case  EM_68K:	//		 4""	/* Motorola m68k family */
			strcpy(ret_buf,"moto_m86k");
			break;
		case  EM_88K:	//		 5	/* Motorola m88k family */
			strcpy(ret_buf,"moto_m88k");
			break;
		case  EM_IAMCU: //	 6	/* Intel MCU */
			strcpy(ret_buf,"intel_mcu");
			break;
		case  EM_860:	//	 7	/* Intel 80860 */
			strcpy(ret_buf,"intel_x86");
			break;
		case  EM_MIPS:	//	 8	/* MIPS R3000 big-endian */
			strcpy(ret_buf,"mips");
			break;
		case  EM_S370:	//	 9	/* IBM System/370 */
			strcpy(ret_buf,"ibm");
			break;
		case  EM_MIPS_RS3_LE:	//10	/* MIPS R3000 little-endian */
			strcpy(ret_buf,"mips");
			break;
		case  EM_PARISC:	//15	/* HPPA */
			strcpy(ret_buf,"hp");
			break;
		case  EM_VPP500:	//17	/* Fujitsu VPP500 */
			strcpy(ret_buf,"fujitsu_vpp500");
			break;
		case  EM_SPARC32PLUS:	//18	/* Sun's "v8plus" */
			strcpy(ret_buf,"v8plus");
			break;
		case  EM_960:	//	19	/* Intel 80960 */
			strcpy(ret_buf,"x86");
			break;
		case  EM_PPC:	//	20	/* PowerPC */
			strcpy(ret_buf,"ppc");
			break;
		case  EM_PPC64:	//21	/* PowerPC 64-bit */
			strcpy(ret_buf,"ppc_x64");
			break;
		case  EM_S390:	//	22	/* IBM S390 */
			strcpy(ret_buf,"ibm_s390");
			break;
		case  EM_SPU:	//	23	/* IBM SPU/SPC */
			strcpy(ret_buf,"ibm_spu");
			break;
		case  EM_V800:	//	36	/* NEC V800 series */
			strcpy(ret_buf,"nec_v800");
			break;
		case  EM_FR20:	//	37	/* Fujitsu FR20 */
			strcpy(ret_buf,"fujitusu");
			break;
		case  EM_RH32:	//	38	/* TRW RH-32 */
			strcpy(ret_buf,"trw_rh32");
			break;
		case  EM_RCE:	//	39	/* Motorola RCE */
			strcpy(ret_buf,"moto_rce");
			break;
		case  EM_ARM:	//	40	/* ARM */
			strcpy(ret_buf,"arm");
			break;
		case  EM_FAKE_ALPHA:	//41	/* Digital Alpha */
			strcpy(ret_buf,"digital_alpha");
			break;
		case  EM_SH:	//	42	/* Hitachi SH */
			strcpy(ret_buf,"Hitachi_sh");
			break;
		case  EM_SPARCV9:	//43	/* SPARC v9 64-bit */
			strcpy(ret_buf,"sparc-v9");
			break;
		case  EM_TRICORE:	//44	/* Siemens Tricore */
			strcpy(ret_buf,"siemens_tricore");
			break;
		case  EM_ARC:	//	45	/* Argonaut RISC Core */
			strcpy(ret_buf,"RISC_CORE");
			break;
		case  EM_H8_300:	//46	/* Hitachi H8/300 */
			strcpy(ret_buf,"Hitachi_H8_300");
			break;
		case  EM_H8_300H:	//47	/* Hitachi H8/300H */
			strcpy(ret_buf,"Hitachi_H8_300H");
			break;
		case  EM_H8S:	//	48	/* Hitachi H8S */
			strcpy(ret_buf,"Hitachi_H8S");
			break;
		case  EM_H8_500:	//49	/* Hitachi H8/500 */
			strcpy(ret_buf,"Hitachi_H8_500");
			break;
		case  EM_IA_64:	//50	/* Intel Merced */
			strcpy(ret_buf,"x86_64");
			break;
		case  EM_MIPS_X:	//51	/* Stanford MIPS-X */
			strcpy(ret_buf,"mips-x");
			break;
		case  EM_COLDFIRE:	//52	/* Motorola Coldfire */
			strcpy(ret_buf,"moto_coldfire");
			break;
		case  EM_68HC12:	//53	/* Motorola M68HC12 */
			strcpy(ret_buf,"moto_m68hc12");
			break;
		case  EM_MMA:	//	54	/* Fujitsu MMA Multimedia Accelerator */
			strcpy(ret_buf,"fujitsu_mma");
			break;
		case  EM_PCP:	//	55	/* Siemens PCP */
			strcpy(ret_buf,"siemens_pcp");
			break;
		case  EM_NCPU:	//	56	/* Sony nCPU embeeded RISC */
			strcpy(ret_buf,"sony_ncpu");
			break;
		case  EM_NDR1:	//	57	/* Denso NDR1 microprocessor */
			strcpy(ret_buf,"denso_up");
			break;
		case  EM_STARCORE:	//58	/* Motorola Start*Core processor */
			strcpy(ret_buf,"moto");
			break;
		case  EM_ME16:	//	59	/* Toyota ME16 processor */
			strcpy(ret_buf,"toyota_up");
			break;
		case  EM_ST100:	//60	/* STMicroelectronic ST100 processor */
			strcpy(ret_buf,"stm_100");
			break;
		case  EM_TINYJ:	//61	/* Advanced Logic Corp. Tinyj emb.fam */
			strcpy(ret_buf,"adv_tinyj");
			break;
		case  EM_X86_64:	//62	/* AMD x86-64 architecture */
			strcpy(ret_buf,"x86_64");
			break;
		case  EM_PDSP:	//	63	/* Sony DSP Processor */
			strcpy(ret_buf,"sony_dsp");
			break;
		case  EM_PDP10:	//64	/* Digital PDP-10 */
		case  EM_PDP11:	//65	/* Digital PDP-11 */
			strcpy(ret_buf,"digital_pdp");
			break;
		case  EM_FX66:	//	66	/* Siemens FX66 microcontroller */
			strcpy(ret_buf,"simens_fx66");
			break;
		case  EM_ST19:	//	74	/* STMicroelectronics ST19 8 bit mc */
		case  EM_ST9PLUS:	//67	/* STMicroelectronics ST9+ 8/16 mc */
		case  EM_ST7:	//	68	/* STmicroelectronics ST7 8 bit mc */
			strcpy(ret_buf,"stm_uc");
			break;
		case  EM_68HC16:	//69	/* Motorola MC68HC16 microcontroller */
		case  EM_68HC11:	//70	/* Motorola MC68HC11 microcontroller */
		case  EM_68HC08:	//71	/* Motorola MC68HC08 microcontroller */
		case  EM_68HC05:	//72	/* Motorola MC68HC05 microcontroller */
			strcpy(ret_buf,"moto_uC");
			break;
		case  EM_SVX:	//	73	/* Silicon Graphics SVx */
			strcpy(ret_buf,"silicon_GSVx");
			break;
		case  EM_VAX:	//	75	/* Digital VAX */
			strcpy(ret_buf,"digital_vax");
			break;
		case  EM_CRIS:	//	76	/* Axis Communications 32-bit emb.proc */
			strcpy(ret_buf,"CRIS");
			break;
		case  EM_JAVELIN:	//77	/* Infineon Technologies 32-bit emb.proc */
			strcpy(ret_buf,"JAVELIN");
			break;
		case  EM_FIREPATH:	//78	/* Element 14 64-bit DSP Processor */
			strcpy(ret_buf,"FIREPATH");
			break;
		case  EM_ZSP:	//	79	/* LSI Logic 16-bit DSP Processor */
			strcpy(ret_buf,"ZSP");
			break;
		case  EM_MMIX:	//	80	/* Donald Knuth's educational 64-bit proc */
			strcpy(ret_buf,"MMIX");
			break;
		case  EM_HUANY:	//81	/* Harvard University machine-independent object files */
			strcpy(ret_buf,"HUANY");
			break;
		case  EM_PRISM:	//82	/* SiTera Prism */
			strcpy(ret_buf,"PRISM");
			break;
		case  EM_AVR:	//	83	/* Atmel AVR 8-bit microcontroller */
			strcpy(ret_buf,"avr");
			break;
		case  EM_FR30:	//	84	/* Fujitsu FR30 */
			strcpy(ret_buf,"FR30");
			break;
		case  EM_D10V:	//	85	/* Mitsubishi D10V */
		case  EM_D30V:	//	86	/* Mitsubishi D30V */
		case  EM_M32R:	//	88	/* Mitsubishi M32R */
			strcpy(ret_buf,"mistubishi_uP");
			break;
		case  EM_V850:	//	87	/* NEC v850 */
			strcpy(ret_buf,"V850");
			break;
		case  EM_MN10300:	//89	/* Matsushita MN10300 */
		case  EM_MN10200:	//90	/* Matsushita MN10200 */
			strcpy(ret_buf,"MN10200/300");
			break;
		case  EM_PJ:	//	91	/* picoJava */
			strcpy(ret_buf,"PJ");
			break;
		case  EM_OPENRISC:	//92	/* OpenRISC 32-bit embedded processor */
			strcpy(ret_buf,"OPENRISC");
			break;
		case  EM_ARC_COMPACT:	//93	/* ARC International ARCompact */
			strcpy(ret_buf,"ARC_COMPACT");
			break;
		case  EM_XTENSA:	//94	/* Tensilica Xtensa Architecture */
			strcpy(ret_buf,"XTENSA");
			break;
		case  EM_VIDEOCORE:	//95	/* Alphamosaic VideoCore */
			strcpy(ret_buf,"VIDEOCORE");
			break;
		case  EM_TMM_GPP:	//96	/* Thompson Multimedia General Purpose Proc */
			strcpy(ret_buf,"TMM_GPP");
			break;

		case  EM_NS32K:	//97	/* National Semi. 32000 */
			strcpy(ret_buf,"NS32K");
			break;
		case  EM_TPC:	//	98	/* Tenor Network TPC */
			strcpy(ret_buf,"TPC");
			break;
		case  EM_SNP1K:	//99	/* Trebia SNP 1000 */
			strcpy(ret_buf,"SNP1K");
			break;
		case  EM_ST200:	//100	/* STMicroelectronics ST200 */
			strcpy(ret_buf,"ST200");
			break;
		case  EM_IP2K:	//	101	/* Ubicom IP2xxx */
			strcpy(ret_buf,"IP2K");
			break;
		case  EM_MAX:	//	102	/* MAX processor */
			strcpy(ret_buf,"MAX");
			break;
		case  EM_CR:	//	103	/* National Semi. CompactRISC */
			strcpy(ret_buf,"CR");
			break;
		case  EM_F2MC16:	//104	/* Fujitsu F2MC16 */
			strcpy(ret_buf,"F2MC18");
			break;
		case  EM_MSP430:	//105	/* Texas Instruments msp430 */
			strcpy(ret_buf,"MSP430");
			break;
		case  EM_BLACKFIN:	//106	/* Analog Devices Blackfin DSP */
			strcpy(ret_buf,"BLACKFIN");
			break;
		case  EM_SE_C33:	//107	/* Seiko Epson S1C33 family */
			strcpy(ret_buf,"SE_C33");
			break;
		case  EM_SEP:	//	108	/* Sharp embedded microprocessor */
			strcpy(ret_buf,"SEP");
			break;
		case  EM_ARCA:	//	109	/* Arca RISC */
			strcpy(ret_buf,"ARCA");
			break;
		case  EM_UNICORE:	//110	/* PKU-Unity & MPRC Peking Uni. mc series */
			strcpy(ret_buf,"UNICORE");
			break;
		case  EM_EXCESS:	//111	/* eXcess configurable cpu */
			strcpy(ret_buf,"EXCESS");
			break;
		case  EM_DXP:	//	112	/* Icera Semi. Deep Execution Processor */
			strcpy(ret_buf,"DXP");
			break;
		case  EM_ALTERA_NIOS2:// 113	/* Altera Nios II */
			strcpy(ret_buf,"ALTERA_NIOS2");
			break;
		case  EM_CRX:	//	114	/* National Semi. CompactRISC CRX */
			strcpy(ret_buf,"CRX");
			break;
		case  EM_XGATE:	//115	/* Motorola XGATE */
			strcpy(ret_buf,"MOTO_XGATE");
			break;
		case  EM_C166:	//	116	/* Infineon C16x/XC16x */
			strcpy(ret_buf,"C166");
			break;
		case  EM_M16C:	//	117	/* Renesas M16C */
			strcpy(ret_buf,"M16C");
			break;
		case  EM_DSPIC30F:	//118	/* Microchip Technology dsPIC30F */
			strcpy(ret_buf,"DSPIC30F");
			break;
		case  EM_CE:	//	119	/* Freescale Communication Engine RISC */
			strcpy(ret_buf,"CE");
			break;
		case  EM_M32C:	//	120	/* Renesas M32C */
			strcpy(ret_buf,"M32C");
			break;
		case  EM_TSK3000:	//131	/* Altium TSK3000 */
			strcpy(ret_buf,"TSK3000");
			break;
		case  EM_RS08:	//	132	/* Freescale RS08 */
			strcpy(ret_buf,"RS08");
			break;
		case  EM_SHARC:	//133	/* Analog Devices SHARC family */
			strcpy(ret_buf,"SHARC");
			break;
		case  EM_ECOG2:	//134	/* Cyan Technology eCOG2 */
			strcpy(ret_buf,"ECOG2");
			break;
		case  EM_SCORE7:	//135	/* Sunplus S+core7 RISC */
			strcpy(ret_buf,"SCORE7");
			break;
		case  EM_DSP24:	//136	/* New Japan Radio (NJR) 24-bit DSP */
			strcpy(ret_buf,"DSP24");
			break;
		case  EM_VIDEOCORE3:	//137	/* Broadcom VideoCore III */
			strcpy(ret_buf,"VIDEOCORE3");
			break;
		case  EM_LATTICEMICO32: //138	/* RISC for Lattice FPGA */
			strcpy(ret_buf,"LATTICEMICO32");
			break;
		case  EM_SE_C17:	//139	/* Seiko Epson C17 */
			strcpy(ret_buf,"SE_C17");
			break;
		case  EM_TI_C6000:	//140	/* Texas Instruments TMS320C6000 DSP */
			strcpy(ret_buf,"TI_C6000");
			break;
		case  EM_TI_C2000:	//141	/* Texas Instruments TMS320C2000 DSP */
			strcpy(ret_buf,"TI_C2000");
			break;
		case  EM_TI_C5500:	//142	/* Texas Instruments TMS320C55x DSP */
			strcpy(ret_buf,"TI_C5500");
			break;
		case  EM_TI_ARP32:	//143	/* Texas Instruments App. Specific RISC */
			strcpy(ret_buf,"TI_ARP32");
			break;
		case  EM_TI_PRU:	//144	/* Texas Instruments Prog. Realtime Unit */
			strcpy(ret_buf,"TI_PRU");
			break;
		case  EM_MMDSP_PLUS:	//160	/* STMicroelectronics 64bit VLIW DSP */
			strcpy(ret_buf,"MMDSP_PLUS");
			break;
		case  EM_CYPRESS_M8C:	//161	/* Cypress M8C */
			strcpy(ret_buf,"Cypress_M8C");
			break;
		case  EM_R32C:	//	162	/* Renesas R32C */
			strcpy(ret_buf,"R32C");
			break;
		case  EM_TRIMEDIA:	//163	/* NXP Semi. TriMedia */
			strcpy(ret_buf,"TriMedia");
			break;
		case  EM_QDSP6:	//164	/* QUALCOMM DSP6 */
			strcpy(ret_buf,"QDSP6");
			break;
		case  EM_8051:	//	165	/* Intel 8051 and variants 
			strcpy(ret_buf,"intel-8051");
			break;
		case  EM_STXP7X:	//166	/* STMicroelectronics STxP7x */
			strcpy(ret_buf,"STM STxP7x");
			break;
		case  EM_NDS32:	//167	/* Andes Tech. compact code emb. RISC */
			strcpy(ret_buf,"NDS32");
			break;
		case  EM_ECOG1X:	//168	/* Cyan Technology eCOG1X */
			strcpy(ret_buf,"eCOG1X");
			break;
		case  EM_MAXQ30:	//169	/* Dallas Semi. MAXQ30 mc */
			strcpy(ret_buf,"MAXQ30");
			break;
		case  EM_XIMO16:	//170	/* New Japan Radio (NJR) 16-bit DSP */
			strcpy(ret_buf,"XIM016");
			break;
		case  EM_MANIK:	//171	/* M2000 Reconfigurable RISC */
			strcpy(ret_buf,"MANIK");
			break;
		case  EM_CRAYNV2:	//172	/* Cray NV2 vector architecture */
			strcpy(ret_buf,"CRAYNV2");
			break;
		case  EM_RX:	//	173	/* Renesas RX */
			strcpy(ret_buf,"Renesas_RX");
			break;
		case  EM_METAG:	//174	/* Imagination Tech. META */
			strcpy(ret_buf,"METAG");
			break;
		case  EM_MCST_ELBRUS:	//175	/* MCST Elbrus */
			strcpy(ret_buf,"MCST Elbrus");
			break;
		case  EM_ECOG16:	//176	/* Cyan Technology eCOG16 */
			strcpy(ret_buf,"Cyan Technology eCOG16");
			break;
		case  EM_CR16:	//	177	/* National Semi. CompactRISC CR16 */
			strcpy(ret_buf,"CompactRISC CR16");
			break;
		case  EM_ETPU:	//	178	/* Freescale Extended Time Processing Unit */
			strcpy(ret_buf,"ETPU");
			break;
		case  EM_SLE9X:	//179	/* Infineon Tech. SLE9X */
			strcpy(ret_buf,"SLE9X");
			break;
		case  EM_L10M:	//	180	/* Intel L10M */
			strcpy(ret_buf,"Intel L10M");
			break;
		case  EM_K10M:	//	181	/* Intel K10M */
			strcpy(ret_buf,"Intel K10M");
			break;
		case  EM_AARCH64:	//183	/* ARM AARCH64 */
			strcpy(ret_buf,"arm_arch64");
			break;
		case  EM_AVR32:	//185	/* Amtel 32-bit microprocessor */
			strcpy(ret_buf,"Atmel-32-uP");
			break;
		case  EM_STM8:	//	186	/* STMicroelectronics STM8 */
			strcpy(ret_buf,"ATMEL-8");
			break;
		case  EM_TILE64:	//187	/* Tileta TILE64 */
			strcpy(ret_buf,"Tileta TILE64");
			break;
		case  EM_TILEPRO:	//188	/* Tilera TILEPro */
			strcpy(ret_buf,"Tilera TILEPro");
			break;
		case  EM_MICROBLAZE:	//189	/* Xilinx MicroBlaze */
			strcpy(ret_buf,"XilinX-MicroBlaze");
			break;
		case  EM_CUDA:	//	190	/* NVIDIA CUDA */
			strcpy(ret_buf,"NVIDIA CUDA");
			break;
		case  EM_TILEGX:	//191	/* Tilera TILE-Gx */
			strcpy(ret_buf,"TILEGX");
			break;
		case  EM_CLOUDSHIELD:	//192	/* CloudShield */
			strcpy(ret_buf,"CloudShield");
			break;
		case  EM_COREA_1ST:	//193	/* KIPO-KAIST Core-A 1st gen. */
			strcpy(ret_buf,"COREA_1ST");
			break;
		case  EM_COREA_2ND:	//194	/* KIPO-KAIST Core-A 2nd gen. */
			strcpy(ret_buf,"COREA_2ND");
			break;
		case  EM_ARC_COMPACT2:	//195	/* Synopsys ARCompact V2 */
			strcpy(ret_buf,"ARCompact V2");
			break;
		case  EM_OPEN8:	//196	/* Open8 RISC */
			strcpy(ret_buf,"Open8 RISC");
			break;
		case  EM_RL78:	//	197	/* Renesas RL78 */
			strcpy(ret_buf,"Renesas RL78");
			break;
		case  EM_VIDEOCORE5:	//198	/* Broadcom VideoCore V */
			strcpy(ret_buf,"Broadcom VideoCore V");
			break;
		case  EM_78KOR:	//199	/* Renesas 78KOR */
			strcpy(ret_buf,"Renesas 78KOR");
			break;
		case  EM_56800EX:	//200	/* Freescale 56800EX DSC */
			strcpy(ret_buf,"56800EX DSC");
			break;
		case  EM_BA1:	//	201	/* Beyond BA1 */
			strcpy(ret_buf,"Beyond BA1");
			break;
		case  EM_BA2:	//	202	/* Beyond BA2 */
			strcpy(ret_buf,"Beyond BA2");
			break;
		case  EM_XCORE:	//203	/* XMOS xCORE */
			strcpy(ret_buf,"XMOS xCORE");
			break;
		case  EM_MCHP_PIC:	//204	/* Microchip 8-bit PIC(r) */
			strcpy(ret_buf,"PIC-8");
			break;
		case  EM_KM32:	//	210	/* KM211 KM32 */
			strcpy(ret_buf,"KM211 KM32");
			break;
		case  EM_KMX32:	//211	/* KM211 KMX32 */
			strcpy(ret_buf,"KM211 KMX32");
			break;
		case  EM_EMX16:	//212	/* KM211 KMX16 */
			strcpy(ret_buf,"KM211 KMX16");
			break;
		case  EM_EMX8:	//	213	/* KM211 KMX8 */
			strcpy(ret_buf,"KM211 KMX8");
			break;
		case  EM_KVARC:	//214	/* KM211 KVARC */
			strcpy(ret_buf,"KM211_KVARC");
			break;
		case  EM_CDP:	//	215	/* Paneve CDP */
			strcpy(ret_buf,"Paneve_CDP");
			break;
		case  EM_COGE:	//	216	/* Cognitive Smart Memory Processor */
			strcpy(ret_buf,"CPGE");
			break;
		case  EM_COOL:	//	217	/* Bluechip CoolEngine */
			strcpy(ret_buf,"COOL");
			break;
		case  EM_NORC:	//	218	/* Nanoradio Optimized RISC */
			strcpy(ret_buf,"NORC");

			break;
		case  EM_CSR_KALIMBA:	//219	/* CSR Kalimba */
			strcpy(ret_buf,"CSR_Kalimba");
			break;
		case  EM_Z80:	//	220	/* Zilog Z80 */
			strcpy(ret_buf,"Zilog_Z80");
			break;
		case  EM_VISIUM:	//221	/* Controls and Data Services VISIUMcore */
			strcpy(ret_buf,"VISIUMcore");
			break;
		case  EM_FT32:	//	222	/* FTDI Chip FT32 */
			strcpy(ret_buf,"FTDI_FT32");
			break;
		case  EM_MOXIE:	//223	/* Moxie processor */
			strcpy(ret_buf,"MOXIE");
			break;
		case  EM_AMDGPU:	//224	/* AMD GPU */
			strcpy(ret_buf,"AMD-GPU");
			break;
		case  EM_RISCV:	//243	/* RISC-V */
			strcpy(ret_buf,"RISC-V");
			break;
		case  EM_BPF:	//	247	/* Linux BPF -- in-kernel virtual machine */
			strcpy(ret_buf,"virtual-machine");
			break;
		default:
			strcpy(ret_buf,"invailid uP/uC.");
			break;
	}
	return ret_buf;
}


void file_processing_abi( char *  path,const char * fname){

	dbg_printf(dbg_print,"path:%s name: %s \n",path,fname);
	if ( NULL == path || NULL == fname){
		return;
	}

	int fd,ret;
	char elf_buf[TOTAL_BYTE_READ] = {0};
	char path_buf[1024] = {0};

	memset(path_buf,0,1024);
	strcat(path_buf,path);
	strcat(path_buf,"/");
	strcat(path_buf,fname);
	dbg_printf(dbg_print,"%s\n",path);
	fd = open(path_buf,O_RDONLY);
	if (fd < 0){
		printf(" %s %d error\n",__FILE__,__LINE__);
		close(fd);
		exit(-1);
	}

	ret = read(fd,elf_buf,TOTAL_BYTE_READ);
	if (ret < 0){
		return;
	}

	if (check_elf((Elf64_Ehdr *) elf_buf) == 0){
		close(fd);
		return;
	}
	char * arch_type = NULL;

	arch_type = elf_info_update(elf_buf);
	if (arch_type){
		elf_library_list * data = (elf_library_list *) malloc(sizeof(elf_library_list));
		if (NULL == data) {
			printf("error:memory not available\n");
			exit(-1);
		}
		strcpy(data->library_name,path_buf);
		strcpy(data->library_arch_type,arch_type);

		dbg_printf(dbg_print,"%s %s",data->library_name,data->library_arch_type);
		add_to_list(data);
	}

	close(fd);
	return;
}
