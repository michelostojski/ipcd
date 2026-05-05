typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    word;
typedef ulong size_t;

typedef struct Elf32_Phdr Elf32_Phdr, *PElf32_Phdr;

typedef enum Elf_ProgramHeaderType_ARM {
    PT_NULL=0,
    PT_LOAD=1,
    PT_DYNAMIC=2,
    PT_INTERP=3,
    PT_NOTE=4,
    PT_SHLIB=5,
    PT_PHDR=6,
    PT_TLS=7,
    PT_GNU_EH_FRAME=1685382480,
    PT_GNU_STACK=1685382481,
    PT_GNU_RELRO=1685382482,
    PT_ARM_EXIDX=1879048192
} Elf_ProgramHeaderType_ARM;

struct Elf32_Phdr {
    enum Elf_ProgramHeaderType_ARM p_type;
    dword p_offset;
    dword p_vaddr;
    dword p_paddr;
    dword p_filesz;
    dword p_memsz;
    dword p_flags;
    dword p_align;
};

typedef enum Elf32_DynTag_ARM {
    DT_NULL=0,
    DT_NEEDED=1,
    DT_PLTRELSZ=2,
    DT_PLTGOT=3,
    DT_HASH=4,
    DT_STRTAB=5,
    DT_SYMTAB=6,
    DT_RELA=7,
    DT_RELASZ=8,
    DT_RELAENT=9,
    DT_STRSZ=10,
    DT_SYMENT=11,
    DT_INIT=12,
    DT_FINI=13,
    DT_SONAME=14,
    DT_RPATH=15,
    DT_SYMBOLIC=16,
    DT_REL=17,
    DT_RELSZ=18,
    DT_RELENT=19,
    DT_PLTREL=20,
    DT_DEBUG=21,
    DT_TEXTREL=22,
    DT_JMPREL=23,
    DT_BIND_NOW=24,
    DT_INIT_ARRAY=25,
    DT_FINI_ARRAY=26,
    DT_INIT_ARRAYSZ=27,
    DT_FINI_ARRAYSZ=28,
    DT_RUNPATH=29,
    DT_FLAGS=30,
    DT_PREINIT_ARRAY=32,
    DT_PREINIT_ARRAYSZ=33,
    DT_RELRSZ=35,
    DT_RELR=36,
    DT_RELRENT=37,
    DT_ANDROID_REL=1610612751,
    DT_ANDROID_RELSZ=1610612752,
    DT_ANDROID_RELA=1610612753,
    DT_ANDROID_RELASZ=1610612754,
    DT_ANDROID_RELR=1879040000,
    DT_ANDROID_RELRSZ=1879040001,
    DT_ANDROID_RELRENT=1879040003,
    DT_GNU_PRELINKED=1879047669,
    DT_GNU_CONFLICTSZ=1879047670,
    DT_GNU_LIBLISTSZ=1879047671,
    DT_CHECKSUM=1879047672,
    DT_PLTPADSZ=1879047673,
    DT_MOVEENT=1879047674,
    DT_MOVESZ=1879047675,
    DT_FEATURE_1=1879047676,
    DT_POSFLAG_1=1879047677,
    DT_SYMINSZ=1879047678,
    DT_SYMINENT=1879047679,
    DT_GNU_XHASH=1879047924,
    DT_GNU_HASH=1879047925,
    DT_TLSDESC_PLT=1879047926,
    DT_TLSDESC_GOT=1879047927,
    DT_GNU_CONFLICT=1879047928,
    DT_GNU_LIBLIST=1879047929,
    DT_CONFIG=1879047930,
    DT_DEPAUDIT=1879047931,
    DT_AUDIT=1879047932,
    DT_PLTPAD=1879047933,
    DT_MOVETAB=1879047934,
    DT_SYMINFO=1879047935,
    DT_VERSYM=1879048176,
    DT_RELACOUNT=1879048185,
    DT_RELCOUNT=1879048186,
    DT_FLAGS_1=1879048187,
    DT_VERDEF=1879048188,
    DT_VERDEFNUM=1879048189,
    DT_VERNEED=1879048190,
    DT_VERNEEDNUM=1879048191,
    DT_AUXILIARY=2147483645,
    DT_FILTER=2147483647
} Elf32_DynTag_ARM;

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

typedef enum Elf_SectionHeaderType_ARM {
    SHT_NULL=0,
    SHT_PROGBITS=1,
    SHT_SYMTAB=2,
    SHT_STRTAB=3,
    SHT_RELA=4,
    SHT_HASH=5,
    SHT_DYNAMIC=6,
    SHT_NOTE=7,
    SHT_NOBITS=8,
    SHT_REL=9,
    SHT_SHLIB=10,
    SHT_DYNSYM=11,
    SHT_INIT_ARRAY=14,
    SHT_FINI_ARRAY=15,
    SHT_PREINIT_ARRAY=16,
    SHT_GROUP=17,
    SHT_SYMTAB_SHNDX=18,
    SHT_ANDROID_REL=1610612737,
    SHT_ANDROID_RELA=1610612738,
    SHT_GNU_ATTRIBUTES=1879048181,
    SHT_GNU_HASH=1879048182,
    SHT_GNU_LIBLIST=1879048183,
    SHT_CHECKSUM=1879048184,
    SHT_SUNW_move=1879048186,
    SHT_SUNW_COMDAT=1879048187,
    SHT_SUNW_syminfo=1879048188,
    SHT_GNU_verdef=1879048189,
    SHT_GNU_verneed=1879048190,
    SHT_GNU_versym=1879048191,
    SHT_ARM_EXIDX=1879048193,
    SHT_ARM_PREEMPTMAP=1879048194,
    SHT_ARM_ATTRIBUTES=1879048195,
    SHT_ARM_DEBUGOVERLAY=1879048196,
    SHT_ARM_OVERLAYSECTION=1879048197
} Elf_SectionHeaderType_ARM;

typedef struct Elf32_Shdr Elf32_Shdr, *PElf32_Shdr;

struct Elf32_Shdr {
    dword sh_name;
    enum Elf_SectionHeaderType_ARM sh_type;
    dword sh_flags;
    dword sh_addr;
    dword sh_offset;
    dword sh_size;
    dword sh_link;
    dword sh_info;
    dword sh_addralign;
    dword sh_entsize;
};

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
};

typedef struct Elf32_Dyn_ARM Elf32_Dyn_ARM, *PElf32_Dyn_ARM;

struct Elf32_Dyn_ARM {
    enum Elf32_DynTag_ARM d_tag;
    dword d_val;
};

typedef struct Elf32_Ehdr Elf32_Ehdr, *PElf32_Ehdr;

struct Elf32_Ehdr {
    byte e_ident_magic_num;
    char e_ident_magic_str[3];
    byte e_ident_class;
    byte e_ident_data;
    byte e_ident_version;
    byte e_ident_osabi;
    byte e_ident_abiversion;
    byte e_ident_pad[7];
    word e_type;
    word e_machine;
    dword e_version;
    dword e_entry;
    dword e_phoff;
    dword e_shoff;
    dword e_flags;
    word e_ehsize;
    word e_phentsize;
    word e_phnum;
    word e_shentsize;
    word e_shnum;
    word e_shstrndx;
};

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;



undefined4 __bss_start__;
undefined4 DAT_00023034;
dword DWORD_00012524;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_00023044;
undefined ioctl;
undefined8 g_isp_fd;
undefined fcntl;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



int isp_sdk_ioctl(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = isp_sdk_ioctl(param_1,param_2,param_3);
  return iVar1;
}



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



// WARNING: Removing unreachable block (ram,0x000118f0)
// WARNING: Removing unreachable block (ram,0x00011908)
// WARNING: Removing unreachable block (ram,0x00011910)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if ((char)__bss_start__ == '\0') {
    __cxa_finalize(DAT_00023034);
    entry();
    if (ppuVar1[8] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_00012524);
    }
    __bss_start__._0_1_ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00011954)
// WARNING: Removing unreachable block (ram,0x0001196c)
// WARNING: Removing unreachable block (ram,0x00011974)
// WARNING: Removing unreachable block (ram,0x00011a5c)
// WARNING: Removing unreachable block (ram,0x00011a70)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_00012524,&DAT_00023044,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



int isp_sdk_ioctl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  char *param3;
  int __errnum;
  undefined4 local_e4;
  int local_e0;
  int local_dc;
  
  if (param_2 != -0x7ffbb67c && param_3 == 0) {
    return 1;
  }
  if (-1 < *(int *)((int)&g_isp_fd + param_1 * 4)) {
    memset(&local_e4,0,0xcc);
    local_e4 = 1;
    local_e0 = param_2;
    local_dc = param_3;
    iVar1 = ioctl(*(int *)((int)&g_isp_fd + param_1 * 4),0xc0cc5616,&local_e4,ioctl);
    if (iVar1 != 0) {
      piVar2 = __errno_location();
      __errnum = *piVar2;
      param3 = strerror(__errnum);
      printf("cmd=0x%X, err:%d, estr:%s\n",param_2,__errnum,param3);
    }
    return iVar1;
  }
  return 2;
}



char * AK_ISP_get_version(void)

{
  return "libplat_isp_sdk V7.0.01";
}



undefined4 AK_ISP_sdk_init(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  char acStack_74 [100];
  
  printf("ispsdk_lib version:%s \n","libplat_isp_sdk V7.0.01");
  if (param_1 < 2) {
    memset(acStack_74,0,100);
    if (param_1 == 0) {
      pcVar4 = "/dev/isp-param-0";
    }
    else {
      pcVar4 = "/dev/isp-param-1";
    }
    sprintf(acStack_74,"%s",pcVar4);
    printf("open isp dev: %s\n",acStack_74);
    iVar1 = open(acStack_74,2);
    *(int *)((int)&g_isp_fd + param_1 * 4) = iVar1;
    if (iVar1 < 0) {
      piVar3 = __errno_location();
      iVar1 = *piVar3;
      pcVar4 = strerror(iVar1);
      printf("open %s fail, err:%d, estr:%s\n",acStack_74,iVar1,pcVar4);
      uVar2 = 0xffffffff;
    }
    else {
      fcntl(iVar1,2,1,fcntl);
      printf("--- %s g_isp_fd[%d]=%d ---\n","AK_ISP_sdk_init",param_1,
             *(int *)((int)&g_isp_fd + param_1 * 4));
      uVar2 = 0;
    }
  }
  else {
    printf("dev no:%d invalid\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 AK_ISP_sdk_exit(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int __fd;
  
  if (1 < param_1) {
    printf("dev no:%d invalid\n",param_1);
    return 0xffffffff;
  }
  printf("--- %s g_isp_fd[%d]=%d closed ---\n","AK_ISP_sdk_exit",param_1,
         *(int *)((int)&g_isp_fd + param_1 * 4));
  __fd = *(int *)((int)&g_isp_fd + param_1 * 4);
  if (__fd != -1) {
    close(__fd);
    *(undefined4 *)((int)&g_isp_fd + param_1 * 4) = 0xffffffff;
    return 0;
  }
  return 0;
}



void AK_ISP_set_raw_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044943,param_2);
  return;
}



void AK_ISP_get_raw_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6bc,param_2);
  return;
}



void AK_ISP_get_raw_hist_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6bb,param_2);
  return;
}



void AK_ISP_set_rgb_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044946,param_2);
  return;
}



void AK_ISP_get_rgb_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b9,param_2);
  return;
}



void AK_ISP_get_rgb_hist_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b8,param_2);
  return;
}



void AK_ISP_set_yuv_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044949,param_2);
  return;
}



void AK_ISP_get_yuv_hist_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b6,param_2);
  return;
}



void AK_ISP_get_yuv_hist_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b5,param_2);
  return;
}



void AK_ISP_set_exp_type(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004494c,param_2);
  return;
}



void AK_ISP_get_exp_type(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b3,param_2);
  return;
}



void AK_ISP_set_ae_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044950,param_2);
  return;
}



void AK_ISP_get_ae_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6af,param_2);
  return;
}



void AK_ISP_set_me_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb67d,param_2);
  return;
}



void AK_ISP_get_me_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb67e,param_2);
  return;
}



void AK_ISP_get_ae_run_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6ae,param_2);
  return;
}



void AK_ISP_set_ae_init_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044980,param_2);
  return;
}



void AK_ISP_get_sensor_ae_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044981,param_2);
  return;
}



void AK_ISP_set_wb_type(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044953,param_2);
  return;
}



void AK_ISP_get_wb_type(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6ac,param_2);
  return;
}



void AK_ISP_set_mwb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044963,param_2);
  return;
}



void AK_ISP_get_mwb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb69c,param_2);
  return;
}



void AK_ISP_set_awb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044955,param_2);
  return;
}



void AK_ISP_get_awb_stable(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb67c,param_2);
  return;
}



void AK_ISP_get_awb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6aa,param_2);
  return;
}



void AK_ISP_set_awb_ex_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044973,param_2);
  return;
}



void AK_ISP_get_awb_ex_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb68c,param_2);
  return;
}



void Ak_ISP_get_awb_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6a7,param_2);
  return;
}



void AK_ISP_set_af_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044960,param_2);
  return;
}



void AK_ISP_get_af_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb69f,param_2);
  return;
}



void AK_ISP_get_af_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb69e,param_2);
  return;
}



void AK_ISP_set_weight_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004495e,param_2);
  return;
}



void AK_ISP_get_weight_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6a1,param_2);
  return;
}



void AK_ISP_set_blc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044902,param_2);
  return;
}



void AK_ISP_get_blc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6ff,param_2);
  return;
}



void AK_ISP_set_dpc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044910,param_2);
  return;
}



void AK_ISP_get_dpc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6f1,param_2);
  return;
}



undefined4 AK_ISP_set_sdpc_attr(void)

{
  return 0;
}



undefined4 AK_ISP_get_sdpc_attr(void)

{
  return 0;
}



void AK_ISP_set_lsc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044904,param_2);
  return;
}



void AK_ISP_get_lsc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6fd,param_2);
  return;
}



void AK_ISP_set_nr1_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004490c,param_2);
  return;
}



void AK_ISP_get_nr1_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6f5,param_2);
  return;
}



void AK_ISP_set_nr2_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004492b,param_2);
  return;
}



void AK_ISP_get_nr2_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6d4,param_2);
  return;
}



void AK_ISP_set_uvnr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004497d,param_2);
  return;
}



void AK_ISP_get_uvnr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb682,param_2);
  return;
}



void AK_ISP_set_3d_nr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004492f,param_2);
  return;
}



void AK_ISP_get_3d_nr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6d0,param_2);
  return;
}



void AK_ISP_set_3d_nr_ref_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044967,param_2);
  return;
}



void AK_ISP_get_3d_nr_ref_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb698,param_2);
  return;
}



void AK_ISP_get_3d_nr_stat_info(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb690,param_2);
  return;
}



void AK_ISP_set_gb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044906,param_2);
  return;
}



void AK_ISP_get_gb_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6fb,param_2);
  return;
}



void AK_ISP_set_demo_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004490e,param_2);
  return;
}



void AK_ISP_get_demo_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6f3,param_2);
  return;
}



void AK_ISP_set_rgb_gamma_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004491a,param_2);
  return;
}



void AK_ISP_get_rgb_gamma_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6e7,param_2);
  return;
}



void AK_ISP_set_raw_lut_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004490a,param_2);
  return;
}



void AK_ISP_get_raw_lut_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6f7,param_2);
  return;
}



void AK_ISP_set_ccm_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044912,param_2);
  return;
}



void AK_ISP_get_ccm_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6ef,param_2);
  return;
}



void AK_ISP_set_sharp_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044925,param_2);
  return;
}



void AK_ISP_get_sharp_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6da,param_2);
  return;
}



void AK_ISP_set_sharp_ex_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044927,param_2);
  return;
}



void AK_ISP_get_sharp_ex_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6d8,param_2);
  return;
}



void AK_ISP_set_fcs_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044936,param_2);
  return;
}



void AK_ISP_get_fcs_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6cb,param_2);
  return;
}



void AK_ISP_set_wdr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004491b,param_2);
  return;
}



void AK_ISP_get_wdr_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6e4,param_2);
  return;
}



void AK_ISP_set_contrast_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044939,param_2);
  return;
}



void AK_ISP_get_contrast_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6c6,param_2);
  return;
}



void AK_ISP_set_saturation_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004493b,param_2);
  return;
}



void AK_ISP_get_saturation_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6c4,param_2);
  return;
}



void AK_ISP_set_rgb2yuv_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004493f,param_2);
  return;
}



void AK_ISP_get_rgb2yuv_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6c0,param_2);
  return;
}



void AK_ISP_set_effect_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044941,param_2);
  return;
}



void AK_ISP_get_effect_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6be,param_2);
  return;
}



void AK_ISP_set_main_chan_mask_area(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004495a,param_2);
  return;
}



void AK_ISP_get_main_chan_mask_area(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6a5,param_2);
  return;
}



void AK_ISP_set_sub_chan_mask_area(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044965,param_2);
  return;
}



void AK_ISP_get_sub_chan_mask_area(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb69a,param_2);
  return;
}



void AK_ISP_set_mask_color(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004495c,param_2);
  return;
}



void AK_ISP_get_mask_color(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6a3,param_2);
  return;
}



void Ak_ISP_Sensor_Set_Reg(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004496b,param_2);
  return;
}



void Ak_ISP_Sensor_Get_Reg(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb694,param_2);
  return;
}



void Ak_ISP_Set_User_Params(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004496d,param_2);
  return;
}



void AK_ISP_set_misc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004496e,param_2);
  return;
}



void AK_ISP_get_misc_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb691,param_2);
  return;
}



void AK_ISP_set_Y_gamma_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044975,param_2);
  return;
}



void AK_ISP_get_Y_gamma_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb68a,param_2);
  return;
}



void AK_ISP_set_hue_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044977,param_2);
  return;
}



void AK_ISP_get_hue_attr(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb688,param_2);
  return;
}



void AK_ISP_set_frame_rate(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004494e,param_2);
  return;
}



void AK_ISP_get_frame_rate(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb6b1,param_2);
  return;
}



void AK_ISP_set_isp_capturing(int param_1,undefined4 param_2)

{
  undefined4 local_c [2];
  
  local_c[0] = param_2;
  isp_sdk_ioctl(param_1,0x40044972,(int)local_c);
  return;
}



void Ak_ISP_Set_Flip_Mirror(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x40044979,param_2);
  return;
}



void Ak_ISP_Set_Sensor_Fps(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,0x4004497a,param_2);
  return;
}



undefined4 Ak_ISP_Get_Sensor_Fps(int param_1)

{
  undefined4 local_c [2];
  
  local_c[0] = 0;
  isp_sdk_ioctl(param_1,-0x7ffbb685,(int)local_c);
  return local_c[0];
}



undefined4 Ak_ISP_Get_Work_Scene(int param_1)

{
  undefined4 local_c [2];
  
  local_c[0] = 0;
  isp_sdk_ioctl(param_1,-0x7ffbb684,(int)local_c);
  return local_c[0];
}



void Ak_ISP_Set_Ae_Suspend(int param_1,int param_2)

{
  isp_sdk_ioctl(param_1,-0x7ffbb67c,param_2);
  return;
}



void _fini(void)

{
  return;
}


