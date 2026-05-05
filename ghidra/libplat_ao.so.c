typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef void _IO_lock_t;

typedef struct _IO_marker _IO_marker, *P_IO_marker;

typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

typedef long __off_t;

typedef longlong __quad_t;

typedef __quad_t __off64_t;

typedef ulong size_t;

struct _IO_FILE {
    int _flags;
    char *_IO_read_ptr;
    char *_IO_read_end;
    char *_IO_read_base;
    char *_IO_write_base;
    char *_IO_write_ptr;
    char *_IO_write_end;
    char *_IO_buf_base;
    char *_IO_buf_end;
    char *_IO_save_base;
    char *_IO_backup_base;
    char *_IO_save_end;
    struct _IO_marker *_markers;
    struct _IO_FILE *_chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    ushort _cur_column;
    char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t *_lock;
    __off64_t _offset;
    void *__pad1;
    void *__pad2;
    void *__pad3;
    void *__pad4;
    size_t __pad5;
    int _mode;
    char _unused2[40];
};

struct _IO_marker {
    struct _IO_marker *_next;
    struct _IO_FILE *_sbuf;
    int _pos;
};

typedef struct _IO_FILE FILE;

typedef struct stat stat, *Pstat;

typedef ulonglong __u_quad_t;

typedef __u_quad_t __dev_t;

typedef ulong __ino_t;

typedef uint __mode_t;

typedef uint __nlink_t;

typedef uint __uid_t;

typedef uint __gid_t;

typedef long __blksize_t;

typedef long __blkcnt_t;

typedef struct timespec timespec, *Ptimespec;

typedef long __time_t;

struct timespec {
    __time_t tv_sec;
    long tv_nsec;
};

struct stat {
    __dev_t st_dev;
    ushort __pad1;
    __ino_t st_ino;
    __mode_t st_mode;
    __nlink_t st_nlink;
    __uid_t st_uid;
    __gid_t st_gid;
    __dev_t st_rdev;
    ushort __pad2;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    ulong __unused4;
    ulong __unused5;
};

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

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

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
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

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

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



undefined4 DAT_00027030;
dword DWORD_00016e20;
pointer __DT_PLTGOT;
undefined1 __bss_start__;
undefined __register_frame_info;
undefined DAT_0002704c;
undefined FUN_00012a30;
undefined4 DAT_00027044;
undefined DAT_00027034;
undefined ak_vqe_inner_close;

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



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



// WARNING: Removing unreachable block (ram,0x00011fc8)
// WARNING: Removing unreachable block (ram,0x00011fe0)
// WARNING: Removing unreachable block (ram,0x00011fe8)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_00027030);
    entry();
    if (ppuVar1[7] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_00016e20);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x0001202c)
// WARNING: Removing unreachable block (ram,0x00012044)
// WARNING: Removing unreachable block (ram,0x0001204c)
// WARNING: Removing unreachable block (ram,0x00012134)
// WARNING: Removing unreachable block (ram,0x00012148)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_00016e20,&DAT_0002704c,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



undefined4 FUN_00012170(int param_1,char *param_2,char *param_3)

{
  size_t sVar1;
  FILE *pFVar2;
  undefined4 uVar3;
  char *param0;
  char acStack_644 [524];
  char acStack_438 [524];
  char acStack_22c [524];
  
  sVar1 = strlen(param_2);
  if (0xfe < sVar1 - 1) {
    ak_print(6,1,"[%s:%d] file_path length = %d ,0< path_size < %d \n","ao_open_dbg_file",0x7c,sVar1
             ,0x100);
    return 0x101;
  }
  sVar1 = strlen(param_3);
  if (sVar1 - 1 < 0xff) {
    param0 = acStack_438;
    memset(acStack_644,0,0x20a);
    memset(param0,0,0x20a);
    memset(acStack_22c,0,0x20a);
    sprintf(acStack_644,"%s%s%s",param_2,param_3,"_input.pcm");
    ak_print(6,3,"[%s:%d] input_full_name =%s\n","ao_open_dbg_file",0x94,acStack_644);
    sprintf(param0,"%s%s%s",param_2,param_3,"_output_ch.pcm");
    ak_print(6,3,"[%s:%d] output_full_name =%s\n","ao_open_dbg_file",0x97,param0);
    sprintf(acStack_22c,"%s%s%s",param_2,param_3,"_vqe.pcm");
    ak_print(6,3,"[%s:%d] vqe_full_name =%s\n","ao_open_dbg_file",0x9a,acStack_22c);
    pFVar2 = fopen(acStack_644,"w+");
    *(FILE **)(param_1 + 0xc) = pFVar2;
    if (pFVar2 == (FILE *)0x0) {
      uVar3 = 0xa2;
      param0 = acStack_644;
    }
    else {
      pFVar2 = fopen(param0,"w+");
      *(FILE **)(param_1 + 0x18) = pFVar2;
      if (pFVar2 == (FILE *)0x0) {
        uVar3 = 0xaa;
      }
      else {
        pFVar2 = fopen(acStack_22c,"w+");
        *(FILE **)(param_1 + 0x24) = pFVar2;
        if (pFVar2 != (FILE *)0x0) {
          return 0;
        }
        param0 = acStack_22c;
        uVar3 = 0xb2;
      }
    }
    ak_print(6,1,"[%s:%d] open %s error\n","ao_open_dbg_file",uVar3,param0);
    if (*(FILE **)(param_1 + 0xc) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0xc));
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
    if (*(FILE **)(param_1 + 0x18) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x18));
      *(undefined4 *)(param_1 + 0x18) = 0;
      *(undefined4 *)(param_1 + 0x1c) = 0;
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
    if (*(FILE **)(param_1 + 0x24) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x24));
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x28) = 0;
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
  }
  else {
    ak_print(6,1,"[%s:%d] file_name length = %d ,0< name_size < %d\n","ao_open_dbg_file",0x83,sVar1,
             0x100);
  }
  return 0x101;
}



undefined4 FUN_00012484(void)

{
  ak_print(6,1,"[%s:%d] handle_id not support\n","get_dev_handle",0xe8);
  return 0;
}



void FUN_000124c4(undefined4 *param_1,void *param_2,size_t param_3)

{
  int iVar1;
  
  fwrite(param_2,1,param_3,(FILE *)*param_1);
  iVar1 = param_1[2];
  param_1[2] = param_3 + iVar1;
  if (param_3 + iVar1 < (uint)param_1[1]) {
    return;
  }
  if ((FILE *)*param_1 == (FILE *)0x0) {
    return;
  }
  fclose((FILE *)*param_1);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}



// WARNING: Removing unreachable block (ram,0x00012570)
// WARNING: Removing unreachable block (ram,0x00012588)

undefined4 FUN_0001252c(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = osal_ao_get_source(*param_1);
  if (iVar1 != 0) {
    ak_print(6,1,"[%s:%d] osal_ao_get_source error\n","ao_set_mute",0x24b);
    return 0x600000d;
  }
  return 0;
}



undefined4 FUN_00012600(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_14 [2];
  
  local_14[0] = 0;
  iVar1 = osal_ao_get_source(*param_1,local_14);
  if (iVar1 != 0) {
    ak_print(6,1,"[%s:%d] osal_ao_get_source error\n","ao_set_gain",0x4e);
    return 0x600000d;
  }
  if ((local_14[0] != 4) && (iVar1 = osal_ao_set_source(*param_1,4), iVar1 != 0)) {
    ak_print(6,1,"[%s:%d] osal_ao_set_source error\n","ao_set_gain",0x53);
    return 0x600000d;
  }
  iVar1 = osal_ao_set_gain(*param_1,param_2 + -1);
  uVar2 = 0;
  if (iVar1 != 0) {
    ak_print(6,1,"[%s:%d] osal_ao_set_gain error\n","ao_set_gain",0x58);
    uVar2 = 0x600000d;
  }
  return uVar2;
}



undefined4 FUN_00012718(undefined4 *param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  memcpy(param_1 + 0x3b,param_2,0x10);
  local_30 = param_1[0x3b];
  local_28 = param_1[0x3c];
  local_2c = param_1[0x3d];
  local_24 = local_30;
  if (local_30 < 16000) {
    local_24 = 0x400;
  }
  local_34 = 0;
  local_1c = 0;
  if (15999 < local_30) {
    if (local_24 < 32000) {
      local_24 = 0x800;
    }
    else if (local_24 < 0xbb81) {
      local_24 = 0x1000;
    }
    else {
      local_24 = 0x2000;
    }
  }
  local_20 = 8;
  ak_set_debug_num_info(6,1,"ao_period_bytes");
  ak_set_debug_num_info(6,1,"ao_periods",local_20);
  iVar1 = osal_ao_set_param(*param_1,&local_34);
  if (iVar1 == 0) {
    iVar1 = osal_ao_start_playing(*param_1);
    if (iVar1 != 0) {
      ak_print(6,1,"[%s:%d] osal_ao_start_playing failed\n","set_param_and_play_stat",0x17e);
      return 0x600000d;
    }
    memset(param_1 + 0x13,0,0xa0);
    *(undefined2 *)(param_1 + 0x13) = 0xffd8;
    param_1[0x14] = 0xc;
    param_1[0x3a] = 0xc;
    param_1[0x39] = 0;
    param_1[0x38] = 0x8000;
    local_34 = iVar1;
    iVar1 = osal_ao_get_dac_actual_rate(*param_1,&local_34);
    if (iVar1 != 0) {
      ak_print(6,2,"[%s:%d] error, osal_ao_get_dac_actual_rate failed.\n","set_param_and_play_stat",
               0x187);
    }
    ak_set_debug_num_info(6,1,"ao_hw_sample",local_34);
    iVar1 = ak_vqe_inner_open(0,0,param_1 + 0x3b,0,param_1 + 0x13,local_34);
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x12) = 0;
      *(undefined1 *)(param_1 + 0xc) = 1;
      iVar1 = ak_thread_create(param_1 + 0xd,FUN_00012a30,param_1,0x19000,0x32);
      if (iVar1 == 0) {
        ak_print(6,5,"[%s:%d] create capture pcm thread OK\n","play_start_running",0x16f);
        uVar2 = 0;
      }
      else {
        ak_print(6,1,"create capture_pcm_thread FAILED, ret=%d\n",0x6000013);
        uVar2 = 0x6000013;
      }
      ak_set_debug_num_info(6,1,"ao_sample_rate",param_1[0x3b]);
      ak_set_debug_num_info(6,1,"ao_channel_num",param_1[0x3d]);
    }
    else {
      uVar2 = 0x6000012;
    }
  }
  else {
    ak_print(6,1,"[%s:%d] dac_set_param error\n","set_param_and_play_stat",0x179);
    uVar2 = 0x600000d;
  }
  return uVar2;
}



undefined4 FUN_00012a30(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  undefined4 uVar6;
  size_t local_30;
  size_t local_2c [2];
  
  uVar2 = ak_thread_get_tid();
  ak_print(6,4,"[%s:%d] thread id: %ld\n","play_pcm_thread",0x11c,uVar2);
  ak_thread_set_name("mpp_ao");
  iVar5 = param_1[0x3b];
  local_30 = 0;
  local_2c[0] = 0;
  if (iVar5 < 16000) {
    uVar6 = 0x200;
  }
  else if (iVar5 < 32000) {
    uVar6 = 0x400;
  }
  else if (iVar5 < 0xbb81) {
    uVar6 = 0x800;
  }
  else {
    uVar6 = 0x1000;
  }
  uVar3 = ak_get_os_timestamp();
  pvVar4 = (void *)ak_mem_alloc_(6,uVar6,"play_pcm_thread",uVar3);
  if (pvVar4 == (void *)0x0) {
    ak_print(6,1,"[%s:%d] calloc dac aslc buffer failed\n","play_pcm_thread",0x126,uVar2);
    return 0;
  }
LAB_00012adc:
  do {
    cVar1 = *(char *)(param_1 + 0xc);
joined_r0x00012ae4:
    if (cVar1 == '\0') {
      ak_mem_free(pvVar4);
      uVar2 = ak_thread_get_tid();
      ak_print(6,4,"[%s:%d] ### thread id: %ld exit ###\n\n","play_pcm_thread",0x158,uVar2);
      ak_thread_exit();
      return 0;
    }
    ak_print(6,5,"[%s:%d] sleep...\n","play_pcm_thread",299);
    ak_thread_sem_wait(param_1 + 0xe);
    ak_print(6,5,"[%s:%d] wakup...\n","play_pcm_thread",0x12d);
    local_2c[0] = 0x200;
    while (*(char *)(param_1 + 0x12) == '\0') {
      while( true ) {
        if (local_2c[0] == 0) goto LAB_00012adc;
        iVar5 = ak_vqe_inner_get_dac(0,pvVar4,uVar6,local_2c);
        if (iVar5 != 0) {
          ak_print(6,1,"[%s:%d] ak_vqe_inner_get_dac failed\n","play_pcm_thread",0x135);
        }
        if (local_2c[0] == 0) goto LAB_00012adc;
        if (param_1[9] != 0) {
          FUN_000124c4(param_1 + 9,pvVar4,local_2c[0]);
        }
        iVar5 = osal_ao_write_data(*param_1,pvVar4,local_2c[0],&local_30);
        if (iVar5 != 0) break;
        if (param_1[6] != 0) {
          FUN_000124c4(param_1 + 6,pvVar4,local_30);
        }
        param_1[2] = param_1[2] + 1;
        if (*(char *)(param_1 + 0x12) != '\0') {
          cVar1 = *(char *)(param_1 + 0xc);
          goto joined_r0x00012ae4;
        }
      }
      ak_print(6,5,"[%s:%d] write error\n","play_pcm_thread",0x148);
      ak_sleep_ms(10);
    }
  } while( true );
}



char * ak_ao_get_version(void)

{
  return "libplat_ao V1.12.03";
}



undefined4 ak_ao_open(int *param_1,uint *param_2)

{
  undefined4 *__s;
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  
  pcVar4 = "libplat_ao V1.12.03";
  ak_print(6,4,"[%s:%d] ao version: %s\n","ak_ao_open",0x269,"libplat_ao V1.12.03");
  if (param_1 == (int *)0x0) {
    ak_print(6,1,"[%s:%d] open parameter is NULL!\n","check_open_param",0x1ca,pcVar4);
    return 0x100;
  }
  if (param_2 == (uint *)0x0) {
    ak_print(6,1,"[%s:%d] handle_id is NULL!\n","check_open_param",0x1cf,pcVar4);
    return 0x100;
  }
  if (param_1[1] == 0x10) {
    iVar1 = param_1[2];
    if (1 < iVar1 - 1U) {
      ak_print(6,1,"[%s:%d] channel_num not support now is %d \n","check_open_param",0x1db,iVar1);
      return 0x101;
    }
    uVar3 = param_1[3];
    if (3 < uVar3) {
      ak_print(6,1,"[%s:%d] dev_id is invalid \n","check_open_param",0x1e0,pcVar4);
      return 0x101;
    }
    if (uVar3 == 1 && iVar1 == 1) {
      ak_print(6,1,"[%s:%d] ao no support I2S0 mono \n","check_open_param",0x1e4,pcVar4);
    }
    else {
      iVar1 = *param_1;
      if ((((iVar1 == 8000 || iVar1 == 12000) || (iVar1 == 0x2b11 || iVar1 == 16000)) ||
          (iVar1 == 0x5622 || iVar1 == 24000)) ||
         ((iVar1 == 32000 || iVar1 == 0xac44 || (iVar1 == 48000 || iVar1 == 96000)))) {
        ak_thread_rwlock_wrlock(DAT_00027044);
        if (*(int *)(&DAT_00027034 + uVar3 * 4) == 0) {
          ak_set_debug_str_info(6,1,"ao_version","libplat_ao V1.12.03");
          uVar2 = ak_get_os_timestamp();
          __s = (undefined4 *)ak_mem_alloc_(6,0xfc,"init_dac_device",uVar2);
          if (__s == (undefined4 *)0x0) {
            ak_print(6,1,"[%s:%d] malloc ao_dev_info error!\n","init_dac_device",0x1a1);
          }
          else {
            memset(__s,0,0xfc);
            iVar1 = osal_ao_open(uVar3,__s);
            if (iVar1 == 0) {
              ak_thread_sem_init(__s + 0xe);
              iVar1 = FUN_00012718(__s,param_1);
              if ((iVar1 == 0) && (iVar1 = FUN_00012600(__s,4), iVar1 == 0)) {
                memset(__s + 3,0,0xc);
                memset(__s + 6,0,0xc);
                memset(__s + 9,0,0xc);
                *(undefined4 **)(&DAT_00027034 + uVar3 * 4) = __s;
                *param_2 = uVar3;
                uVar2 = 0;
                goto LAB_00012e98;
              }
              osal_ao_close(*__s);
              ak_mem_free(__s);
            }
            else {
              ak_print(6,1,"[%s:%d] dac dev open failed\n","init_dac_device",0x1a8);
              ak_mem_free(__s);
            }
          }
          uVar2 = 0x6000005;
        }
        else {
          ak_print(6,1,"[%s:%d] dev has open already!\n","ak_ao_open",0x275,pcVar4);
          uVar2 = 0x6000004;
        }
LAB_00012e98:
        ak_thread_rwlock_unlock(DAT_00027044);
        ak_print(6,3,"[%s:%d] leaved...\n","ak_ao_open",0x288);
        return uVar2;
      }
      ak_print(6,1,"[%s:%d] sample rate not support now is %d \n","check_open_param",0x1ea,iVar1);
    }
  }
  else {
    ak_print(6,1,"[%s:%d] sample bit only suppirt 16bit,now is %d \n","check_open_param",0x1d5,
             param_1[1]);
  }
  return 0x101;
}



undefined4 ak_ao_get_handle_id(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (uint *)0x0) {
    ak_print(6,4,"ao_handle_id is NULL\n");
    return 0x100;
  }
  if (3 < param_1) {
    ak_print(6,1,"[%s:%d] dev_id invalid \n","ak_ao_get_handle_id",0x29a);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (*(int *)(&DAT_00027034 + param_1 * 4) == 0) {
    ak_print(6,1,"[%s:%d] no device id %d\n","ak_ao_get_handle_id",0x2a3,param_1);
    uVar1 = 0x101;
    *param_2 = 0xffffffff;
  }
  else {
    uVar1 = 0;
    *param_2 = param_1;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar1;
}



undefined4 ak_ao_send_frame(uint param_1,void *param_2,uint param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int local_2c [2];
  
  ak_print(6,5,"[%s:%d] enter...\n","ak_ao_send_frame",0x2b8);
  if (param_2 == (void *)0x0) {
    ak_print(6,1,"[%s:%d] data buffer is NULL\n","check_send_frame_param",499);
    return 0x100;
  }
  if ((int)param_3 < 1) {
    ak_print(6,1,"[%s:%d] send_pcm_len =%d, error\n","check_send_frame_param",0x1f8,param_3);
    return 0x101;
  }
  if (0x6400 < (int)param_3) {
    ak_print(6,1,"[%s:%d] send_pcm_len =%d, must use len <= %d\n","check_send_frame_param",0x1fd,
             param_3,0x6400);
    return 0x6000009;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar5 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar5 = FUN_00012484();
  }
  if (iVar5 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_send_frame",0x2c7);
    uVar4 = 0x6000005;
    goto LAB_0001345c;
  }
  iVar1 = *(int *)(iVar5 + 0xf4);
  if (iVar1 == 2) {
    iVar2 = 0x2000;
  }
  else {
    iVar2 = 0x1000;
  }
  if (48000 < *(int *)(iVar5 + 0xec)) {
    iVar2 = 0x4000;
  }
  if (iVar2 < (int)param_3) {
    ak_print(6,1,"[%s:%d] send_pcm_len =%d, error, send_pcm_len must < %d\n","check_send_frame_len",
             0x20f,param_3,iVar2);
LAB_00013458:
    uVar4 = 0x101;
  }
  else {
    if (iVar1 == 1) {
      if ((param_3 & 1) != 0) {
        ak_print(6,1,
                 "[%s:%d] AUDIO_CHANNEL_MONO: play_pcm_len must be multiple of 2, send_pcm_len = %d\n"
                 ,"check_send_frame_len",0x213,param_3);
        goto LAB_00013458;
      }
    }
    else if ((iVar1 == 2) && ((param_3 & 3) != 0)) {
      ak_print(6,1,
               "[%s:%d] AUDIO_CHANNEL_STEREO: play_pcm_len must be multiple of 4, send_pcm_len = %d\n"
               ,"check_send_frame_len",0x217,param_3);
      goto LAB_00013458;
    }
    if (*(int *)(iVar5 + 0xc) != 0) {
      FUN_000124c4((undefined4 *)(iVar5 + 0xc),param_2,param_3);
    }
    if (*(char *)(iVar5 + 0x48) == '\x01') {
      *(int *)(iVar5 + 4) = *(int *)(iVar5 + 4) + 1;
      *(undefined1 *)(iVar5 + 0x48) = 0;
    }
    else {
      *(int *)(iVar5 + 4) = *(int *)(iVar5 + 4) + 1;
    }
    local_2c[0] = 0;
    cVar3 = '\0';
    iVar1 = 0;
    do {
      iVar2 = ak_vqe_inner_send_far_pcm(0,(int)param_2 + iVar1,param_3,local_2c);
      if (iVar2 != 0) {
        ak_print(6,1,"[%s:%d] ak_vqe_inner_send_far_pcm failed\n","send_data_to_vqe",0x101);
        goto LAB_00013520;
      }
      if (local_2c[0] != 0) {
        ak_thread_sem_post(iVar5 + 0x38);
        param_3 = param_3 - local_2c[0];
        iVar1 = iVar1 + local_2c[0];
        if (param_3 == 0) {
          if (cVar3 != -0x38) {
            uVar4 = 0;
            if (1 < iVar1 + 1U) goto LAB_000134c0;
            goto LAB_00013520;
          }
          break;
        }
      }
      cVar3 = cVar3 + '\x01';
      ak_sleep_ms(10);
    } while (cVar3 != -0x37);
    ak_print(6,1,"[%s:%d] loop timeout!\n","send_data_to_vqe",0x10e);
LAB_00013520:
    ak_print(6,1,"[%s:%d] send_data_to_vqe failed\n","ak_ao_send_frame",0x2da);
    uVar4 = 0xffffffff;
    iVar1 = 0;
LAB_000134c0:
    if (param_4 != (int *)0x0) {
      *param_4 = iVar1;
    }
  }
LAB_0001345c:
  ak_thread_rwlock_unlock(DAT_00027044);
  ak_print(6,5,"[%s:%d] exit...\n","ak_ao_send_frame",0x2e6);
  return uVar4;
}



undefined4 ak_ao_wait_play_finish(void)

{
  ak_print(6,1,"[%s:%d] this function is deprecated and no longer in use\n","ak_ao_wait_play_finish"
           ,0x2f2);
  return 0;
}



undefined4 ak_ao_clear_frame_buffer(void)

{
  ak_print(6,1,"[%s:%d] this function is deprecated and no longer in use\n",
           "ak_ao_clear_frame_buffer",0x2fe);
  return 0;
}



undefined4 ak_ao_set_gain(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if (param_2 < 7) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      puVar3 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
    }
    else {
      puVar3 = (undefined4 *)FUN_00012484();
    }
    if (puVar3 == (undefined4 *)0x0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_gain",0x315);
      uVar2 = 0x6000005;
    }
    else {
      ak_print(6,4,"[%s:%d] set gain %d\n","ak_ao_set_gain",0x31a,param_2);
      if (param_2 == 0) {
        iVar1 = FUN_0001252c(puVar3);
      }
      else {
        iVar1 = FUN_00012600(puVar3,param_2);
      }
      if (iVar1 == 0) {
        ak_set_debug_num_info(6,1,"ao_gain",param_2);
        uVar2 = 0;
      }
      else {
        uVar2 = 0x600000d;
      }
    }
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] invalid volume = %d, gain must in [0,6]\n","ak_ao_set_gain",0x30c,param_2);
  return 0x101;
}



undefined4 ak_ao_set_volume(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  
  if (param_2 + 0x5aU < 0x6f) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_volume",0x341);
      uVar2 = 0x6000005;
    }
    else {
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      iVar1 = ak_vqe_inner_get_ao_aslc(0,&local_1c);
      if (iVar1 != 0) {
        local_1c = 0x8000;
      }
      local_18 = param_2;
      uVar2 = ak_vqe_inner_set_ao_aslc(0,&local_1c);
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_set_volume",0x34f);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(5,1,"[%s:%d] db =%d, db must in [-90, 20]\n","ak_ao_set_volume",0x339,param_2);
  return 0x101;
}



// WARNING: Removing unreachable block (ram,0x00013ac4)
// WARNING: Removing unreachable block (ram,0x00013af4)
// WARNING: Removing unreachable block (ram,0x00013ae0)

undefined4 ak_ao_get_gain(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_get_gain",0x35e);
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      puVar3 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
    }
    else {
      puVar3 = (undefined4 *)FUN_00012484();
    }
    if (puVar3 == (undefined4 *)0x0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_gain",0x369);
      uVar2 = 0x6000005;
    }
    else {
      iVar1 = osal_ao_get_source(*puVar3);
      if (iVar1 == 0) {
        uVar2 = 0;
        *param_2 = 0;
      }
      else {
        ak_print(6,1,"[%s:%d] osal_ao_get_source error\n","ak_ao_get_gain",0x370);
        uVar2 = 0x600000d;
      }
    }
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] gain is NULL\n","ak_ao_get_gain",0x360);
  return 0x100;
}



undefined4 ak_ao_get_volume(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_24 [4];
  undefined4 local_20;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_volume",0x39a);
      uVar2 = 0x6000005;
    }
    else {
      iVar1 = ak_vqe_inner_get_ao_aslc(0,auStack_24);
      if (iVar1 == 0) {
        *param_2 = local_20;
        uVar2 = 0;
      }
      else {
        uVar2 = 0;
        *param_2 = 0;
      }
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_get_volume",0x3a5);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_get_volume",0x390);
  return 0x100;
}



undefined4 ak_ao_set_speaker(uint param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (1 < param_2) {
    ak_print(6,1,"[%s:%d] enable must be 0 or 1\n","ak_ao_set_speaker",0x3b4);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    puVar1 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
  }
  else {
    puVar1 = (undefined4 *)FUN_00012484();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_speaker",0x3bd);
    uVar3 = 0x6000005;
    goto LAB_00013d20;
  }
  if (param_2 == 0) {
    iVar2 = FUN_0001252c(puVar1);
    if (iVar2 != 0) {
      uVar3 = 0x3ca;
      goto LAB_00013d50;
    }
  }
  else {
    iVar2 = osal_ao_set_source(*puVar1,4);
    if (iVar2 != 0) {
      uVar3 = 0x3c4;
LAB_00013d50:
      ak_print(6,1,"[%s:%d] osal_ao_set_source failed\n","ak_ao_set_speaker",uVar3);
      uVar3 = 0x600000d;
      goto LAB_00013d20;
    }
  }
  uVar3 = 0;
LAB_00013d20:
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar3;
}



undefined4 ak_ao_enable_eq(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_98 [124];
  char local_1c;
  
  if (param_2 < 2) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar3 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar3 = FUN_00012484();
    }
    if (iVar3 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_enable_eq",1000);
      uVar2 = 0x6000005;
    }
    else {
      memset(auStack_98,0,0x88);
      iVar1 = ak_vqe_inner_get_ao_eq(0,auStack_98);
      if ((iVar1 != 0) || (local_1c == '\0')) {
        memcpy(auStack_98,(void *)(iVar3 + 0x58),0x88);
      }
      local_1c = (char)param_2;
      uVar2 = ak_vqe_inner_set_ao_eq(0,auStack_98);
      ak_print(6,4,"[%s:%d] leave...\n","ak_ao_enable_eq",0x3f5);
    }
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] enable must be 0 or 1\n","ak_ao_enable_eq",0x3df);
  return 0x101;
}



undefined4 ak_ao_set_eq_attr(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_eq_attr",0x40f);
      uVar2 = 0x6000005;
    }
    else {
      uVar2 = ak_vqe_inner_set_ao_eq(0,param_2);
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_set_eq_attr",0x416);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_set_eq_attr",0x407);
  return 0x100;
}



undefined4 ak_ao_get_eq_attr(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_eq_attr",0x42d);
      uVar2 = 0x6000005;
    }
    else {
      uVar2 = ak_vqe_inner_get_ao_eq(0,param_2);
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_get_eq_attr",0x435);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_get_eq_attr",0x425);
  return 0x100;
}



undefined4 ak_ao_reset_sample_rate(void)

{
  ak_print(6,1,"[%s:%d] this function is deprecated and no longer in use\n",
           "ak_ao_reset_sample_rate",0x444);
  return 0;
}



undefined4 ak_ao_set_dev_buf_size(void)

{
  ak_print(6,1,"[%s:%d] this function is deprecated and no longer in use\n","ak_ao_set_dev_buf_size"
           ,0x451);
  return 0;
}



undefined4 ak_ao_get_dev_buf_size(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_get_dev_buf_size",0x45f);
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_dev_buf_size",0x46a);
      uVar3 = 0x6000005;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0xec);
      if (iVar1 < 16000) {
        uVar2 = 0x400;
      }
      else if (iVar1 < 32000) {
        uVar2 = 0x800;
      }
      else if (iVar1 < 0xbb81) {
        uVar2 = 0x1000;
      }
      else {
        uVar2 = 0x2000;
      }
      uVar3 = 0;
      *param_2 = uVar2;
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_get_dev_buf_size",0x472);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar3;
  }
  ak_print(6,1,"[%s:%d] dev_buf_size is NULL\n","ak_ao_get_dev_buf_size",0x462);
  return 0x100;
}



undefined4 ak_ao_print_runtime_status(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar1 = FUN_00012484();
  }
  if (iVar1 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_print_runtime_status",0x484);
    uVar2 = 0x6000005;
  }
  else {
    ak_print(6,3,"[%s:%d] send_frame_count=%d\n","ak_ao_print_runtime_status",0x489,
             *(undefined4 *)(iVar1 + 4));
    ak_print(6,3,"[%s:%d] write_to_driver_count=%d\n","ak_ao_print_runtime_status",0x48a,
             *(undefined4 *)(iVar1 + 8));
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar2;
}



undefined4 ak_ao_close(uint param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_close",0x49a);
  ak_thread_rwlock_wrlock(DAT_00027044);
  if (param_1 < 4) {
    puVar2 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00012484();
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_close",0x4a1);
    uVar3 = 0x6000005;
  }
  else {
    if (*(char *)(puVar2 + 0xc) != '\0') {
      *(undefined1 *)(puVar2 + 0xc) = 0;
      ak_thread_sem_post(puVar2 + 0xe);
      ak_print(6,4,"[%s:%d] join play pcm thread...\n","ak_ao_close",0x4a9);
      ak_thread_join(puVar2[0xd]);
      ak_print(6,3,"[%s:%d] play pcm thread join OK\n","ak_ao_close",0x4ab);
    }
    iVar1 = ak_vqe_inner_close(0,0,1,ak_vqe_inner_close);
    if (iVar1 != 0) {
      ak_print(6,1,"[%s:%d] osal_vqe_close failed\n","ak_ao_close",0x4af);
    }
    iVar1 = osal_ao_close(*puVar2);
    if (iVar1 == 0) {
      uVar3 = 0;
    }
    else {
      ak_print(6,1,"[%s:%d] dac_dev_close failed!\n","ak_ao_close",0x4b4);
      uVar3 = 0x600000d;
    }
    ak_thread_sem_destroy(puVar2 + 0xe);
    if ((FILE *)puVar2[3] != (FILE *)0x0) {
      fclose((FILE *)puVar2[3]);
      puVar2[3] = 0;
      puVar2[4] = 0;
      puVar2[5] = 0;
    }
    if ((FILE *)puVar2[6] != (FILE *)0x0) {
      fclose((FILE *)puVar2[6]);
      puVar2[6] = 0;
      puVar2[7] = 0;
      puVar2[8] = 0;
    }
    if ((FILE *)puVar2[9] != (FILE *)0x0) {
      fclose((FILE *)puVar2[9]);
      puVar2[9] = 0;
      puVar2[10] = 0;
      puVar2[0xb] = 0;
    }
    ak_mem_free(puVar2);
    *(undefined4 *)(&DAT_00027034 + param_1 * 4) = 0;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  ak_print(6,4,"[%s:%d] leave\n","ak_ao_close",0x4c3);
  return uVar3;
}



int ak_ao_save_file(uint param_1,uint *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *__file;
  uint *__s;
  stat sStack_78;
  
  if (param_2 == (uint *)0x0) {
    ak_print(6,1,"[%s:%d] save_file_info is NULL\n","check_save_file_param",0x220);
    return 0x100;
  }
  if (*param_2 < 2) {
    if (0xb3 < param_2[0x81] - 1) {
      ak_print(6,1,"[%s:%d] save_second = %d, invalid, must in [1~180]\n","check_save_file_param",
               0x229,param_2[0x81]);
      return 0x101;
    }
    __file = param_2 + 1;
    memset(&sStack_78,0,0x58);
    iVar1 = stat((char *)__file,&sStack_78);
    if (iVar1 == 0) {
      if ((sStack_78.st_mode & 0xf000) == 0x4000) {
        iVar1 = access((char *)__file,2);
        if (iVar1 == 0) {
          sVar2 = strlen((char *)__file);
          if (sVar2 < 0x101) {
            __s = param_2 + 0x41;
            sVar2 = strlen((char *)__s);
            if (sVar2 < 0x101) {
              ak_thread_rwlock_rdlock(DAT_00027044);
              if (param_1 < 4) {
                iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
              }
              else {
                iVar1 = FUN_00012484();
              }
              if (iVar1 == 0) {
                ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_save_file",0x4d9);
                iVar3 = 0x6000005;
              }
              else {
                iVar3 = 0;
                if (*param_2 != 0) {
                  iVar3 = FUN_00012170(iVar1,(char *)__file,(char *)__s);
                  if (iVar3 == 0) {
                    uVar4 = ((*(uint *)(iVar1 + 0xf0) >> 3) *
                            param_2[0x81] * *(int *)(iVar1 + 0xec) * *(int *)(iVar1 + 0xf4)) / 1000;
                    if ((uVar4 & 1) != 0) {
                      uVar4 = uVar4 + 1;
                    }
                    iVar5 = uVar4 * 1000;
                    *(int *)(iVar1 + 0x10) = iVar5;
                    *(int *)(iVar1 + 0x1c) = iVar5;
                    *(int *)(iVar1 + 0x28) = iVar5;
                    *(undefined4 *)(iVar1 + 0x20) = 0;
                    *(undefined4 *)(iVar1 + 0x14) = 0;
                    *(undefined4 *)(iVar1 + 0x2c) = 0;
                  }
                  else {
                    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_save_file",0x4e1);
                  }
                }
              }
              ak_thread_rwlock_unlock(DAT_00027044);
              return iVar3;
            }
            ak_print(5,1,"[%s:%d] file_name = %s, invalid\n","check_save_file_param",0x241,__s);
          }
          else {
            ak_print(5,1,"[%s:%d] file_path = %s, invalid\n","check_save_file_param",0x23c,__file);
          }
        }
        else {
          ak_print(6,1,"[%s:%d] path can not write. path:%s\n","check_save_file_param",0x236,__file)
          ;
        }
      }
      else {
        ak_print(6,1,"[%s:%d] path is not dir. path:%s\n","check_save_file_param",0x232,__file);
      }
    }
    else {
      ak_print(6,1,"[%s:%d] stat error. path:%s, error\n","check_save_file_param",0x22e,__file);
    }
  }
  else {
    ak_print(6,1,"[%s:%d] enable = %d, invalid\n","check_save_file_param",0x224,*param_2);
  }
  return 0x101;
}



undefined4 ak_ao_set_aslc_attr(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_aslc_attr",0x507);
      uVar2 = 0x6000005;
    }
    else {
      uVar2 = ak_vqe_inner_set_ao_aslc(0,param_2);
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_set_aslc_attr",0x50f);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_set_aslc_attr",0x4ff);
  return 0x100;
}



undefined4 ak_ao_get_aslc_attr(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_aslc_attr",0x526);
      uVar2 = 0x6000005;
    }
    else {
      uVar2 = ak_vqe_inner_get_ao_aslc(0,param_2);
    }
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_get_aslc_attr",0x52e);
    ak_thread_rwlock_unlock(DAT_00027044);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_get_aslc_attr",0x51e);
  return 0x100;
}



undefined4 ak_ao_set_nr_attr(uint param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_set_nr_attr",0x53d);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar2 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar2 = FUN_00012484();
  }
  if (iVar2 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_set_nr_attr",0x545);
    uVar1 = 0x6000005;
  }
  else {
    iVar3 = *(int *)(iVar2 + 0xec);
    if (iVar3 == 16000 || iVar3 == 8000) {
      if (*(int *)(iVar2 + 0xf4) == 2) {
        ak_print(6,1,"[%s:%d] set nr attr only support mono\n","ak_ao_set_nr_attr",0x550);
        uVar1 = 0x101;
      }
      else {
        uVar1 = ak_vqe_inner_set_ao_nr(0,param_2);
      }
    }
    else {
      ak_print(6,1,"[%s:%d] nr no support %d sample rate\n","ak_ao_set_nr_attr",0x54b,iVar3);
      uVar1 = 0x101;
    }
  }
  ak_print(6,4,"[%s:%d] leave...\n","ak_ao_set_nr_attr",0x558);
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar1;
}



undefined4 ak_ao_get_nr_attr(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_2 == 0) {
    ak_print(6,1,"[%s:%d] eq_attr is NULL\n","ak_ao_get_nr_attr",0x567);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar1 = FUN_00012484();
  }
  if (iVar1 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_nr_attr",0x56f);
    uVar3 = 0x6000005;
  }
  else {
    iVar2 = *(int *)(iVar1 + 0xec);
    if (iVar2 == 16000 || iVar2 == 8000) {
      if (*(int *)(iVar1 + 0xf8) == 0) {
        uVar3 = ak_vqe_inner_get_ao_nr(0,param_2);
      }
      else {
        ak_print(6,1,"[%s:%d] get nr attr only support dac device\n","ak_ao_get_nr_attr",0x57b);
        uVar3 = 0x101;
      }
    }
    else {
      ak_print(6,1,"[%s:%d] nr no support %d sample rate\n","ak_ao_get_nr_attr",0x575,iVar2);
      uVar3 = 0x101;
    }
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar3;
}



void ak_ao_get_filter_info(void)

{
  ak_vqe_inner_get_atc_version();
  return;
}



undefined4 ak_ao_enable_nr(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_24;
  int local_20;
  uint local_1c;
  
  if (param_2 < 2) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_enable_nr",0x5a4);
      uVar3 = 0x6000005;
    }
    else {
      iVar2 = *(int *)(iVar1 + 0xec);
      if (iVar2 == 16000 || iVar2 == 8000) {
        iVar2 = *(int *)(iVar1 + 0xf8);
        if (iVar2 == 0) {
          local_24 = iVar2;
          local_20 = iVar2;
          local_1c = iVar2;
          memcpy(&local_24,(void *)(iVar1 + 0x4c),0xc);
          local_1c = param_2;
          uVar3 = ak_vqe_inner_set_ao_nr(0,&local_24);
        }
        else {
          ak_print(6,1,"[%s:%d] set nr only support dac device\n","ak_ao_enable_nr",0x5b1);
          uVar3 = 0x101;
        }
      }
      else {
        ak_print(6,1,"[%s:%d] nr no support %d sample rate\n","ak_ao_enable_nr",0x5ab,iVar2);
        uVar3 = 0x101;
      }
    }
    ak_thread_rwlock_unlock(DAT_00027044);
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_enable_nr",0x5bd);
    return uVar3;
  }
  ak_print(6,1,"[%s:%d] enable must be 0 or 1\n","ak_ao_enable_nr",0x59b);
  return 0x101;
}



undefined4 ak_ao_cancel(uint param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_cancel",0x5c9);
  ak_thread_rwlock_wrlock(DAT_00027044);
  if (param_1 < 4) {
    puVar1 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
  }
  else {
    puVar1 = (undefined4 *)FUN_00012484();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_cancel",0x5d0);
    uVar2 = 0x6000005;
  }
  else if (*(char *)(puVar1 + 0xc) == '\0') {
    uVar2 = 0;
  }
  else {
    *(undefined1 *)(puVar1 + 0x12) = 1;
    ak_vqe_inner_clean_ao_buf(0);
    osal_ao_clear_dma_buffer(*puVar1);
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  ak_print(6,4,"[%s:%d] leave\n","ak_ao_cancel",0x5dd);
  return uVar2;
}



undefined4 ak_ao_get_buf_status(uint param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int local_24;
  int local_20;
  int local_1c;
  
  ak_print(6,5,"[%s:%d] enter...\n","ak_ao_get_buf_status",0x5ea);
  if (param_2 == (int *)0x0) {
    ak_print(6,1,"[%s:%d] buf_status is NULL\n","ak_ao_get_buf_status",0x5ec);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    puVar2 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00012484();
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_buf_status",0x5f5);
    uVar3 = 0x6000005;
  }
  else {
    local_24 = -1;
    local_20 = -1;
    iVar1 = osal_ao_get_buf_status(*puVar2,&local_24);
    if ((iVar1 == 0) && (local_24 != -1)) {
      local_1c = -1;
      iVar1 = ak_vqe_inner_get_buf_status(0,&local_20,&local_1c);
      if ((iVar1 == 0) && (local_20 != -1)) {
        ak_print(6,5,"[%s:%d] atcbuf_remain=%d, devbuf_remain=%d\n","ak_ao_get_buf_status",0x609,
                 local_20,local_24);
        iVar1 = puVar2[0x3b];
        param_2[1] = local_24 + local_20;
        if (iVar1 < 16000) {
          iVar1 = 0x1000;
        }
        else if (iVar1 < 32000) {
          iVar1 = 0x2000;
        }
        else if (iVar1 < 0xbb81) {
          iVar1 = 0x4000;
        }
        else {
          iVar1 = 0x8000;
        }
        *param_2 = local_1c + iVar1;
        ak_print(6,5,"[%s:%d] devbuf_total=%d, atcbuf_total=%d\n","ak_ao_get_buf_status",0x60f,iVar1
                 ,local_1c);
        uVar3 = 0;
        goto LAB_0001542c;
      }
      uVar3 = 0x605;
    }
    else {
      uVar3 = 0x5fe;
    }
    ak_print(6,1,"[%s:%d] osal_ao_get_buf_status failed\n","ak_ao_get_buf_status",uVar3);
    uVar3 = 0x600000d;
  }
LAB_0001542c:
  ak_thread_rwlock_unlock(DAT_00027044);
  ak_print(6,5,"[%s:%d] leave\n","ak_ao_get_buf_status",0x613);
  return uVar3;
}



undefined4 ak_ao_enable_hs(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_18 [4];
  uint local_14;
  
  if (param_2 < 2) {
    ak_thread_rwlock_rdlock(DAT_00027044);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
    }
    else {
      iVar1 = FUN_00012484();
    }
    if (iVar1 == 0) {
      ak_print(6,1,"[%s:%d] ao dev is NULL!\n","ak_ao_enable_hs",0x62a);
      uVar2 = 0x6000005;
    }
    else {
      ak_vqe_inner_get_ao_hs(0,auStack_18);
      local_14 = param_2;
      uVar2 = ak_vqe_inner_set_ao_hs(0,auStack_18);
    }
    ak_thread_rwlock_unlock(DAT_00027044);
    ak_print(6,4,"[%s:%d] leave...\n","ak_ao_enable_hs",0x635);
    return uVar2;
  }
  ak_print(6,1,"[%s:%d] enable must be 0 or 1\n","ak_ao_enable_hs",0x621);
  return 0x101;
}



undefined4 ak_ao_get_hs_attr(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    ak_print(6,1,"[%s:%d] hs_attr is NULL\n","ak_ao_get_hs_attr",0x643);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar1 = FUN_00012484();
  }
  if (iVar1 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_hs_attr",0x64b);
    uVar2 = 0x6000005;
  }
  else {
    iVar1 = *(int *)(iVar1 + 0xec);
    if (iVar1 == 16000 || iVar1 == 8000) {
      uVar2 = ak_vqe_inner_get_ao_hs(0,param_2);
    }
    else {
      ak_print(6,1,"[%s:%d] howling suppress no support %d sample rate\n","ak_ao_get_hs_attr",0x651,
               iVar1);
      uVar2 = 0x101;
    }
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar2;
}



undefined4 ak_ao_reset_params(uint param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_reset_params",0x666);
  if (param_2 == (int *)0x0) {
    ak_print(6,2,"[%s:%d] param is NULL, use default setting \n","ak_ao_reset_params",0x668);
    uVar1 = 0;
  }
  else {
    iVar2 = *param_2;
    if ((((iVar2 == 8000 || iVar2 == 12000) || (iVar2 == 0x2b11 || iVar2 == 16000)) ||
        (iVar2 == 0x5622 || iVar2 == 24000)) ||
       ((iVar2 == 32000 || iVar2 == 0xac44 || (iVar2 == 48000 || iVar2 == 96000)))) {
      iVar2 = param_2[2];
      if (iVar2 - 1U < 2) {
        ak_thread_rwlock_wrlock(DAT_00027044);
        if (param_1 < 4) {
          puVar3 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
        }
        else {
          puVar3 = (undefined4 *)FUN_00012484();
        }
        if (puVar3 == (undefined4 *)0x0) {
          ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_reset_params",0x67a);
          uVar1 = 0x6000005;
        }
        else if ((puVar3[0x3b] == *param_2) && (puVar3[0x3d] == param_2[2])) {
          ak_print(6,1,"[%s:%d] set sample rate and channel number is the same !\n",
                   "ak_ao_reset_params",0x681);
          uVar1 = 0x6000008;
        }
        else {
          if (*(char *)(puVar3 + 0xc) != '\0') {
            *(undefined1 *)(puVar3 + 0xc) = 0;
            ak_thread_sem_post(puVar3 + 0xe);
            ak_print(6,4,"[%s:%d] join play pcm thread...\n","ak_ao_reset_params",0x689);
            ak_thread_join(puVar3[0xd]);
            ak_print(6,3,"[%s:%d] play pcm thread join OK\n","ak_ao_reset_params",0x68b);
          }
          iVar2 = ak_vqe_inner_close(0,0,1);
          if (iVar2 != 0) {
            ak_print(6,1,"[%s:%d] osal_vqe_close failed\n","ak_ao_reset_params",0x68f);
          }
          iVar2 = osal_ao_clear_dma_buffer(*puVar3);
          if (iVar2 == 0) {
            uVar1 = FUN_00012718(puVar3,param_2);
          }
          else {
            uVar1 = 0x600000d;
          }
        }
        ak_thread_rwlock_unlock(DAT_00027044);
        return uVar1;
      }
      uVar1 = 0x671;
    }
    else {
      uVar1 = 0x66d;
    }
    ak_print(6,1,"[%s:%d] sample rate not support now is %d \n","ak_ao_reset_params",uVar1,iVar2);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_ao_restart(uint param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  ak_print(6,4,"[%s:%d] enter...\n","ak_ao_restart",0x6a9);
  ak_thread_rwlock_wrlock(DAT_00027044);
  if (param_1 < 4) {
    puVar1 = *(undefined4 **)(&DAT_00027034 + param_1 * 4);
  }
  else {
    puVar1 = (undefined4 *)FUN_00012484();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_restart",0x6b0);
    uVar3 = 0x6000005;
  }
  else if ((*(char *)(puVar1 + 0xc) == '\0') || (*(char *)(puVar1 + 0x12) != '\0')) {
    *(undefined1 *)(puVar1 + 0x12) = 0;
    iVar2 = osal_ao_start_playing(*puVar1);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      ak_print(6,1,"[%s:%d] osal_ao_start_playing failed\n","ak_ao_restart",0x6be);
      uVar3 = 0x600000d;
    }
  }
  else {
    ak_print(6,1,"[%s:%d] ao now is playing, please use ak_ao_cancel then restart\n","ak_ao_restart"
             ,0x6b6);
    uVar3 = 0x6000007;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  ak_print(6,4,"[%s:%d] leave\n","ak_ao_restart",0x6c5);
  return uVar3;
}



undefined4 ak_ao_get_params(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_2 == (undefined4 *)0x0) {
    ak_print(6,1,"[%s:%d] invalid param\n","ak_ao_get_params",0x6d4);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00027044);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_00027034 + param_1 * 4);
  }
  else {
    iVar1 = FUN_00012484();
  }
  if (iVar1 == 0) {
    ak_print(6,1,"[%s:%d] dev is NULL!\n","ak_ao_get_params",0x6dd);
    uVar4 = 0x6000005;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0xf0);
    uVar3 = *(undefined4 *)(iVar1 + 0xf4);
    uVar4 = 0;
    *param_2 = *(undefined4 *)(iVar1 + 0xec);
    param_2[1] = uVar2;
    param_2[2] = uVar3;
  }
  ak_thread_rwlock_unlock(DAT_00027044);
  return uVar4;
}



void _fini(void)

{
  return;
}


