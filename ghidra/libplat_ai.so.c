typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
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

typedef struct Elf32_Shdr Elf32_Shdr, *PElf32_Shdr;

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

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
};

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
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



undefined1 __bss_start__;
undefined4 DAT_0002c038;
dword DWORD_0001b360;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_0002c054;
undefined4 DAT_00017700;
undefined *PTR_s_resample_00019770;
undefined ak_vqe_inner_send_adc;
int DAT_0002c06c;
undefined4 DAT_0002c04c;
undefined DAT_0002c03c;
undefined FUN_00013e18;

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



int ak_ai_get_vad_status_ex(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = ak_ai_get_vad_status_ex(param_1,param_2);
  return iVar1;
}



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int raise(int __sig)

{
  int iVar1;
  
  iVar1 = raise(__sig);
  return iVar1;
}



// WARNING: Removing unreachable block (ram,0x00012cf4)
// WARNING: Removing unreachable block (ram,0x00012d0c)
// WARNING: Removing unreachable block (ram,0x00012d14)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_0002c038);
    entry();
    if (ppuVar1[9] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_0001b360);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00012d58)
// WARNING: Removing unreachable block (ram,0x00012d70)
// WARNING: Removing unreachable block (ram,0x00012d78)
// WARNING: Removing unreachable block (ram,0x00012e60)
// WARNING: Removing unreachable block (ram,0x00012e74)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_0001b360,&DAT_0002c054,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



undefined4 FUN_00012e9c(int *param_1)

{
  if (param_1 == (int *)0x0) {
    ak_print(5,1,"[%s:%d] pcm_frame is NULL!\n","check_release_frame_param",0x346);
    return 0x100;
  }
  if (*param_1 == 0) {
    ak_print(5,1,"[%s:%d] pcm_frame->data is NULL, can not be release \n",
             "check_release_frame_param",0x34a);
    return 0x101;
  }
  if (param_1[1] == 0) {
    ak_print(5,2,"[%s:%d] pcm_frame->len=%d, wrong length\n","check_release_frame_param",0x34e,0);
  }
  if (param_1[2] == 0 && param_1[3] == 0) {
    ak_print(5,2,"[%s:%d] pcm_frame->ts=%lld, wrong ts\n","check_release_frame_param",0x351);
  }
  if (param_1[4] == 0) {
    ak_print(5,2,"[%s:%d] pcm_frame->seq_no=%ld, wrong seq_no\n","check_release_frame_param",0x355,0
            );
    return 0;
  }
  return 0;
}



void FUN_00012fec(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  ak_thread_mutex_lock(param_1 + 0x158);
  piVar4 = *(int **)(param_1 + 0x148);
  piVar5 = (int *)*piVar4;
  while (piVar1 = piVar5, (int *)(param_1 + 0x148) != piVar4) {
    piVar5 = piVar4 + -6;
    if (piVar5 != (int *)0x0) {
      if (*piVar5 != 0) {
        ak_mem_free();
        *piVar5 = 0;
      }
      piVar3 = (int *)piVar4[1];
      iVar2 = *piVar4;
      *(int **)(iVar2 + 4) = piVar3;
      *piVar3 = iVar2;
      *piVar4 = 0x100100;
      piVar4[1] = 0x200200;
      ak_mem_free(piVar5);
    }
    piVar5 = (int *)*piVar1;
    piVar4 = piVar1;
  }
  *(undefined4 *)(param_1 + 0x150) = 0;
  ak_thread_mutex_unlock(param_1 + 0x158);
  return;
}



undefined4 FUN_000130c4(int param_1,char *param_2,char *param_3)

{
  size_t sVar1;
  FILE *pFVar2;
  undefined4 uVar3;
  char *param0;
  char acStack_438 [524];
  char acStack_22c [528];
  
  sVar1 = strlen(param_2);
  if (0xfe < sVar1 - 1) {
    ak_print(5,1,"[%s:%d] file_path length = %d ,0< path_size < %d \n","ai_open_dbg_file",0xdb,sVar1
             ,0x100);
    return 0x101;
  }
  sVar1 = strlen(param_3);
  if (sVar1 - 1 < 0xff) {
    param0 = acStack_438;
    memset(param0,0,0x20a);
    memset(acStack_22c,0,0x20a);
    sprintf(param0,"%s%s%s",param_2,param_3,"_input.pcm");
    ak_print(5,3,"[%s:%d] input_full_name =%s\n","ai_open_dbg_file",0xf1,param0);
    sprintf(acStack_22c,"%s%s%s",param_2,param_3,"_output.pcm");
    ak_print(5,3,"[%s:%d] output_full_name =%s\n","ai_open_dbg_file",0xf5,acStack_22c);
    pFVar2 = fopen(param0,"w+");
    *(FILE **)(param_1 + 0x30) = pFVar2;
    if (pFVar2 == (FILE *)0x0) {
      uVar3 = 0xfb;
    }
    else {
      pFVar2 = fopen(acStack_22c,"w+");
      *(FILE **)(param_1 + 0x3c) = pFVar2;
      if (pFVar2 != (FILE *)0x0) {
        return 0;
      }
      uVar3 = 0x102;
      param0 = acStack_22c;
    }
    ak_print(5,1,"[%s:%d] open %s error\n","ai_open_dbg_file",uVar3,param0);
    if (*(FILE **)(param_1 + 0x30) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0;
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    if (*(FILE **)(param_1 + 0x3c) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x3c));
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x44) = 0;
    }
  }
  else {
    ak_print(5,1,"[%s:%d] file_name length = %d ,0< name_size < %d\n","ai_open_dbg_file",0xe2,sVar1,
             0x100);
  }
  return 0x101;
}



undefined4 FUN_00013330(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_1 == (undefined4 *)0x0) {
    ak_print(5,1,"[%s:%d] open parameter is NULL!\n","check_ai_open_param",0x308);
    return 0x100;
  }
  if (param_1[1] == 0x10) {
    if (1 < param_1[2] - 1) {
      ak_print(5,1,"[%s:%d] channel number invalid \n","check_ai_open_param",0x312);
      return 0x101;
    }
    if (3 < (uint)param_1[3]) {
      ak_print(5,1,"[%s:%d] dev_id invalid \n","check_ai_open_param",0x317);
      return 0x101;
    }
    if (param_1[2] == 1 && param_1[3] != 0) {
      ak_print(5,1,"[%s:%d] only adc support mono \n","check_ai_open_param",0x321);
      uVar1 = 0x101;
    }
    else {
      puVar2 = (undefined4 *)*param_1;
      if (puVar2 == (undefined4 *)0x1f40 || puVar2 == (undefined4 *)0x2ee0) {
        uVar1 = 0;
      }
      else if (puVar2 == (undefined4 *)0x2b11 || puVar2 == (undefined4 *)0x3e80) {
        uVar1 = 0;
      }
      else if (puVar2 == (undefined4 *)0x5622 || puVar2 == (undefined4 *)0x5dc0) {
        uVar1 = 0;
      }
      else if (puVar2 == (undefined4 *)0x7d00 || puVar2 == (undefined4 *)0xac44) {
        uVar1 = 0;
      }
      else if (puVar2 == (undefined4 *)0xbb80 || puVar2 == &DAT_00017700) {
        uVar1 = 0;
      }
      else {
        ak_print(5,1,"[%s:%d] sample rate invalid \n","check_ai_open_param",0x326);
        uVar1 = 0x101;
      }
    }
  }
  else {
    ak_print(5,1,"[%s:%d] sample bit invalid \n","check_ai_open_param",0x30d);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 FUN_00013558(undefined4 param_1)

{
  ak_print(5,1,"[%s:%d] dev_id not support %d \n","get_ai_user_handle",0x39d,param_1);
  return 0;
}



undefined4 FUN_000135a0(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 != (int *)0x0) {
    uVar1 = 0;
    if (*param_1 != 0) {
      ak_print(5,1,"[%s:%d] pcm_frame->data must be NULL, now is %p \n","check_get_frame_param",
               0x33d,*param_1);
      uVar1 = 0x101;
    }
    return uVar1;
  }
  ak_print(5,1,"[%s:%d] pcm_frame is NULL!\n","check_get_frame_param",0x338);
  return 0x100;
}



undefined4 FUN_00013630(int param_1,int param_2,int *param_3)

{
  if (param_2 != 16000 && param_2 != 8000) {
    ak_print(5,1,"[%s:%d] %s no support %d sample rate\n","sample_and_channel_condition",0x90,
             (&PTR_s_resample_00019770)[param_1],param_2);
    return 0x101;
  }
  if (*param_3 == 0) {
    return 0;
  }
  ak_print(5,1,"[%s:%d] %s no support stereo\n","sample_and_channel_condition",0x94,
           (&PTR_s_resample_00019770)[param_1]);
  return 0x101;
}



void FUN_000136f0(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  ak_set_debug_num_info(5,1,"ai_sample_rate ",param_1,param_4);
  ak_set_debug_num_info(5,1,"ai_ch_num ",*param_2);
  return;
}



void FUN_00013734(undefined4 *param_1,void *param_2,size_t param_3)

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



undefined4 FUN_0001379c(int param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined4 uVar9;
  int iVar10;
  undefined8 uVar11;
  uint *local_48;
  uint local_44 [3];
  undefined2 auStack_38 [2];
  uint local_34;
  uint local_30;
  uint uStack_2c;
  
  uVar9 = *(undefined4 *)(param_1 + 0x1c);
  param_2[1] = 0;
  local_30 = 0;
  uStack_2c = 0;
  uVar3 = ak_get_os_timestamp();
  puVar4 = (undefined2 *)ak_mem_alloc_(5,uVar9,"get_frame_non_block",uVar3);
  *param_2 = puVar4;
  if (puVar4 == (undefined2 *)0x0) {
    local_48 = (uint *)0x368;
    ak_print(5,1,"[%s:%d] malloc pcm_frame->data fialed\n","get_frame_non_block");
    return 0x102;
  }
  local_34 = *(uint *)(param_1 + 0x13c);
  if ((local_34 == 0) && (*(int *)(param_1 + 0x138) == 2)) {
    uVar1 = *(int *)(param_1 + 0x1c) >> 1;
    iVar5 = -(uVar1 + 7 & 0xfffffff8);
    *(uint **)((int)&local_48 + iVar5) = &local_30;
    iVar10 = ak_vqe_inner_get_adc(0,(int)auStack_38 + iVar5,uVar1);
    uVar2 = local_34;
    if (iVar10 == 0) {
      if (local_34 - 1 < 0x2000) {
        if (local_34 < uVar1) {
          *(undefined4 *)((int)&local_48 + iVar5) = 0x280;
          *(uint *)((int)local_44 + iVar5) = uVar2;
          *(undefined4 *)((int)local_44 + iVar5 + 4) = *(undefined4 *)(param_1 + 0x1c);
          ak_print(5,2,"[%s:%d] read ring buffer len=%d, frame_size=%d not enough\n",
                   "get_mono_and_copyto_stereo");
        }
        iVar10 = local_34 * 2;
        iVar7 = iVar10 + 3;
        if (-1 < iVar10) {
          iVar7 = iVar10;
        }
        iVar7 = iVar7 >> 2;
        if (0 < iVar7) {
          puVar6 = (undefined2 *)((int)auStack_38 + iVar5 + iVar7 * 2);
          puVar8 = puVar4 + iVar7 * 2;
          do {
            puVar6 = puVar6 + -1;
            puVar8[-1] = *puVar6;
            puVar8 = puVar8 + -2;
            *puVar8 = *puVar6;
          } while (puVar8 != puVar4);
        }
        param_2[1] = iVar10;
LAB_0001385c:
        iVar10 = *(int *)(param_1 + 0x28) + 1;
        *(int *)(param_1 + 0x28) = iVar10;
        uVar11 = FUN_00019374(local_30,uStack_2c,1000,0);
        iVar5 = *(int *)(param_1 + 0x3c);
        param_2[4] = iVar10;
        *(undefined8 *)(param_2 + 2) = uVar11;
        if (iVar5 != 0) {
          FUN_00013734((undefined4 *)(param_1 + 0x3c),(void *)*param_2,param_2[1]);
        }
        return 0;
      }
      *(undefined4 *)((int)&local_48 + iVar5) = 0x27a;
      *(uint *)((int)local_44 + iVar5) = uVar2;
      ak_print(5,5,"[%s:%d] read from ring buffer return len=%d\n","get_mono_and_copyto_stereo");
    }
    else {
      *(undefined4 *)((int)&local_48 + iVar5) = 0x275;
      ak_print(5,1,"[%s:%d] osal_vqe_get_adc failed\n","get_mono_and_copyto_stereo");
    }
    ak_mem_free(*param_2);
    *param_2 = 0;
  }
  else {
    local_48 = &local_30;
    local_34 = 0;
    iVar5 = ak_vqe_inner_get_adc(0,puVar4,*(undefined4 *)(param_1 + 0x1c));
    if (iVar5 == 0) {
      if (local_34 - 1 < 0x2000) {
        if (local_34 < *(uint *)(param_1 + 0x1c)) {
          local_44[0] = local_34;
          local_48 = (uint *)0x25e;
          local_44[1] = *(uint *)(param_1 + 0x1c);
          ak_print(5,5,"[%s:%d] read from vqe len=%d, frame_size=%d not enough\n","get_pcm_from_vqe"
                  );
        }
        param_2[1] = local_34;
        goto LAB_0001385c;
      }
      local_48 = (uint *)0x258;
      local_44[0] = local_34;
      ak_print(5,5,"[%s:%d] read from vqe return len=%d\n","get_pcm_from_vqe");
    }
    else {
      local_48 = (uint *)0x253;
      ak_print(5,1,"[%s:%d] osal_vqe_get_adc failed\n","get_pcm_from_vqe");
    }
    ak_mem_free(*param_2);
    *param_2 = 0;
  }
  return 0x5000011;
}



undefined4 FUN_00013af4(undefined4 *param_1,int param_2)

{
  int iVar1;
  int local_14;
  
  local_14 = 2;
  iVar1 = osal_ai_get_source(*param_1,&local_14);
  if (iVar1 != 0) {
    ak_print(5,1,"[%s:%d] osal_ai_get_source failed\n","ai_set_source",0x21a);
    return 0x500000d;
  }
  if ((local_14 != param_2) && (iVar1 = osal_ai_set_source(*param_1,param_2), iVar1 != 0)) {
    ak_print(5,1,"[%s:%d] osal_ai_set_source failed\n","ai_set_source",0x220);
    return 0x500000d;
  }
  return 0;
}



undefined4 FUN_00013bd8(uint *param_1)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  uint *__file;
  stat sStack_70;
  
  if (param_1 == (uint *)0x0) {
    ak_print(5,1,"[%s:%d] save_file_info is NULL\n","ai_check_dbg_file_param",0xae);
    return 0x100;
  }
  if (*param_1 < 2) {
    if (0xb3 < param_1[0x81] - 1) {
      ak_print(5,1,"[%s:%d] save_second = %d, invalid, must in [1~180]\n","ai_check_dbg_file_param",
               0xb7,param_1[0x81]);
      return 0x101;
    }
    __file = param_1 + 1;
    memset(&sStack_70,0,0x58);
    iVar1 = stat((char *)__file,&sStack_70);
    if (iVar1 == 0) {
      if ((sStack_70.st_mode & 0xf000) == 0x4000) {
        iVar1 = access((char *)__file,2);
        if (iVar1 == 0) {
          sVar2 = strlen((char *)__file);
          if (sVar2 < 0x101) {
            sVar2 = strlen((char *)(param_1 + 0x41));
            uVar3 = 0;
            if (0x100 < sVar2) {
              ak_print(5,1,"[%s:%d] file_name = %s, invalid\n","ai_check_dbg_file_param",0xd0,
                       param_1 + 0x41);
              uVar3 = 0x101;
            }
          }
          else {
            ak_print(5,1,"[%s:%d] file_path = %s, invalid\n","ai_check_dbg_file_param",0xcb,__file);
            uVar3 = 0x101;
          }
        }
        else {
          ak_print(5,1,"[%s:%d] path can not write. path:%s\n","ai_check_dbg_file_param",0xc5,__file
                  );
          uVar3 = 0x101;
        }
      }
      else {
        ak_print(5,1,"[%s:%d] path is not dir. path:%s\n","ai_check_dbg_file_param",0xc1,__file);
        uVar3 = 0x101;
      }
    }
    else {
      ak_print(5,1,"[%s:%d] stat error. path:%s, error\n","ai_check_dbg_file_param",0xbd,__file);
      uVar3 = 0x101;
    }
  }
  else {
    ak_print(5,1,"[%s:%d] enable = %d, invalid\n","ai_check_dbg_file_param",0xb2,*param_1);
    uVar3 = 0x101;
  }
  return uVar3;
}



undefined4 FUN_00013e18(char *param_1)

{
  size_t sVar1;
  undefined4 uVar2;
  void *__src;
  int iVar3;
  undefined4 *__s;
  void *__dest;
  undefined4 *puVar4;
  size_t sVar5;
  int iVar6;
  char *pcVar7;
  size_t __n;
  size_t local_48;
  size_t local_44;
  int local_40;
  size_t sStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar2 = ak_thread_get_tid();
  ak_print(5,4,"[%s:%d] thread id: %ld\n","capture_pcm_thread",0x290,uVar2);
  ak_thread_set_name("mpp_ai");
  iVar6 = *(int *)(param_1 + 0x130);
  if (iVar6 < 16000) {
    iVar6 = 0x200;
  }
  else if (iVar6 < 32000) {
    iVar6 = 0x400;
  }
  else if (iVar6 < 0xbb81) {
    iVar6 = 0x800;
  }
  else {
    iVar6 = 0x1000;
  }
  if (*(int *)(param_1 + 0x13c) - 1U < 3) {
    iVar6 = iVar6 << 1;
  }
  ak_set_debug_num_info(5,1,"dev_buf_len",iVar6);
  uVar2 = ak_get_os_timestamp();
  __src = (void *)ak_mem_alloc_(5,iVar6,"capture_pcm_thread",uVar2);
  if (__src == (void *)0x0) {
    ak_print(5,1,"[%s:%d] calloc audio read buffer failed\n","capture_pcm_thread",0x29f);
    return 0;
  }
  local_48 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar3 = osal_ai_get_adc_actual_rate(*(undefined4 *)(param_1 + 4),&local_48);
  if (iVar3 != 0) {
    ak_print(5,2,"[%s:%d] error, osal_ai_get_adc_actual_rate failed.\n","capture_pcm_thread",0x2a6);
  }
  ak_set_debug_num_info(5,1,"ai_hw_sample",local_48);
  memcpy(&local_38,param_1 + 0x130,0x10);
  if (*(int *)(param_1 + 0x13c) == 0) {
    local_30 = 1;
  }
  sVar5 = local_48;
  iVar3 = ak_vqe_inner_open(0,&local_38,0,param_1 + 0x54,0,local_48);
  if (iVar3 != 0) {
    ak_print(5,1,"ak_vqe_inner_open FAILED\n");
  }
  ak_vqe_inner_set_ai_jitterbuf_upperBound(0,300);
  if (*(int *)(param_1 + 0x48) != 0) {
    ak_vqe_inner_enable_dump(0);
  }
LAB_00013f8c:
  do {
    if (*param_1 == '\0') {
LAB_00013ff0:
      uVar2 = ak_thread_get_tid();
      ak_print(5,4,"[%s:%d] ### thread id: %ld exit ###\n\n","capture_pcm_thread",0x2cf,uVar2);
      iVar6 = ak_vqe_inner_close(0,1,0);
      if (iVar6 != 0) {
        ak_print(5,1,"ak_vqe_inner_close FAILED\n");
      }
      ak_mem_free(__src);
      ak_thread_exit();
      return 0;
    }
    if ((*(int *)(param_1 + 0x50) != 0) || (*(int *)(param_1 + 0x154) != 0)) {
      local_44 = 0;
      iVar3 = osal_ai_read(*(undefined4 *)(param_1 + 4),__src,iVar6);
      if (iVar3 != 0) {
        ak_print(5,3,"[%s:%d] read ended\n","read_driver_data_send_to_vqe",0x1bf);
        goto LAB_00013ff0;
      }
      iVar3 = osal_ai_get_pcm_timer(*(undefined4 *)(param_1 + 4),&local_40);
      if (iVar3 != 0) {
        ak_print(5,1,"[%s:%d] osal_ai_get_pcm_timer error\n","read_driver_data_send_to_vqe",0x1c5);
        goto LAB_00013ff0;
      }
      *(int *)(param_1 + 0x140) = local_40;
      *(size_t *)(param_1 + 0x144) = sStack_3c;
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 1;
      if (*(int *)(param_1 + 0x30) != 0) {
        FUN_00013734((undefined4 *)(param_1 + 0x30),__src,local_44);
      }
      sVar1 = sStack_3c;
      iVar3 = local_40;
      __n = local_44;
      if (*(int *)(param_1 + 0x154) != 0) {
        pcVar7 = param_1 + 0x158;
        ak_thread_mutex_lock(pcVar7);
        if (*(uint *)(param_1 + 0x150) < 0x1f) {
          ak_thread_mutex_unlock(pcVar7);
          uVar2 = ak_get_os_timestamp();
          __s = (undefined4 *)ak_mem_alloc_(5,0x20,"src_frame_list_add_member",uVar2);
          if (__s == (undefined4 *)0x0) {
            ak_print(5,1,"[%s:%d] malloc struct aenc_entry failed\n","src_frame_list_add_member",
                     0x193);
          }
          else {
            memset(__s,0,0x20);
            uVar2 = ak_get_os_timestamp();
            __dest = (void *)ak_mem_alloc_(5,__n,"src_frame_list_add_member",uVar2);
            *__s = __dest;
            if (__dest == (void *)0x0) {
              ak_print(5,1,"[%s:%d] calloc %d failed\n","src_frame_list_add_member",0x182,__n);
              ak_mem_free(__s);
              sVar5 = __n;
            }
            else {
              memcpy(__dest,__src,__n);
              __s[1] = __n;
              __s[2] = iVar3;
              __s[3] = sVar1;
              __s[4] = __s[4] + 1;
              ak_thread_mutex_lock(pcVar7);
              iVar3 = *(int *)(param_1 + 0x150);
              puVar4 = *(undefined4 **)(param_1 + 0x14c);
              *(undefined4 **)(param_1 + 0x14c) = __s + 6;
              __s[7] = puVar4;
              __s[6] = param_1 + 0x148;
              *puVar4 = __s + 6;
              *(int *)(param_1 + 0x150) = iVar3 + 1;
              ak_thread_mutex_unlock(pcVar7);
            }
          }
        }
        else {
          ak_print(5,5,"[%s:%d] frame list is full\n","src_frame_list_add_member",0x176);
          ak_thread_mutex_unlock(pcVar7);
        }
      }
      if ((*(int *)(param_1 + 0x50) != 0) &&
         (sVar5 = sStack_3c,
         iVar3 = ak_vqe_inner_send_adc(0,__src,local_44,ak_vqe_inner_send_adc,local_40,sStack_3c),
         iVar3 != 0)) {
        if (DAT_0002c06c < 0x65) {
          DAT_0002c06c = DAT_0002c06c + 1;
        }
        else {
          ak_print(5,1,"[%s:%d] osal_vqe_send_adc failed\n","read_driver_data_send_to_vqe",0x1d9);
          ak_print(5,3,"[%s:%d] read_dev_count=%d\n","read_driver_data_send_to_vqe",0x1da,
                   *(undefined4 *)(param_1 + 0x24));
          ak_print(5,3,"[%s:%d] get_frame_count=%d\n","read_driver_data_send_to_vqe",0x1db,
                   *(undefined4 *)(param_1 + 0x28));
          sVar5 = *(size_t *)(param_1 + 0x2c);
          ak_print(5,3,"[%s:%d] release_frame_count=%d\n","read_driver_data_send_to_vqe",0x1dc,sVar5
                  );
          DAT_0002c06c = 1;
        }
      }
      if ((int)local_44 < 0) goto LAB_00013ff0;
      if (local_44 == 0) {
        ak_print(5,1,"[%s:%d] read_pcm_data get data len = 0\n","capture_pcm_thread",0x2c9,sVar5);
      }
      goto LAB_00013f8c;
    }
    local_40 = *(int *)(param_1 + 0x154);
    iVar3 = osal_ai_read(*(undefined4 *)(param_1 + 4),__src,iVar6);
    if (iVar3 != 0) {
      ak_print(5,1,"[%s:%d] read failed\n","capture_pcm_thread",0x2bd);
      goto LAB_00013ff0;
    }
    ak_print(5,5,"[%s:%d] user no ready to read .\n","capture_pcm_thread",0x2c0);
  } while( true );
}



void ak_ai_print_filter_info(void)

{
  undefined4 uVar1;
  
  uVar1 = ak_vqe_inner_get_atc_version();
  ak_print(5,4,"[%s:%d] filter version: %s\n","ak_ai_print_filter_info",0x3ab,uVar1);
  return;
}



char * ak_ai_get_version(void)

{
  return "libplat_ai V1.14.00";
}



int ak_ai_open(undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *__s;
  int iVar3;
  undefined4 extraout_r0;
  uint uVar4;
  undefined4 uVar5;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  char *pcVar6;
  
  pcVar6 = "libplat_ai V1.14.00";
  ak_print(5,4,"[%s:%d] ai version: %s\n","ak_ai_open",0x3c2,"libplat_ai V1.14.00");
  if (param_2 == (int *)0x0) {
    ak_print(5,1,"[%s:%d] open parameter is NULL!\n","ak_ai_open",0x3c5,pcVar6);
    return 0x100;
  }
  iVar1 = FUN_00013330(param_1);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = param_1[3];
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (*(int *)(&DAT_0002c03c + iVar1 * 4) == 0) {
    ak_set_debug_str_info(5,1,"ai_version ","libplat_ai V1.14.00");
    uVar5 = param_1[3];
    uVar2 = ak_get_os_timestamp();
    __s = (void *)ak_mem_alloc_(5,0x170,"init_adc_dev",uVar2);
    if (__s == (void *)0x0) {
      ak_print(5,1,"[%s:%d] malloc ai_dev_info error!\n","init_adc_dev",0x1ea);
    }
    else {
      memset(__s,0,0x170);
      iVar3 = osal_ai_open(uVar5,(int)__s + 4);
      if (iVar3 == 0) {
        memcpy((void *)((int)__s + 0x130),param_1,0x10);
        iVar3 = *(int *)((int)__s + 0x130);
        if (iVar3 < 16000) {
          iVar3 = 0x200;
        }
        else if (iVar3 < 32000) {
          iVar3 = 0x400;
        }
        else if (iVar3 < 0xbb81) {
          iVar3 = 0x800;
        }
        else {
          iVar3 = 0x1000;
        }
        *(int *)((int)__s + 0x1c) = iVar3;
        if (*(int *)((int)__s + 0x138) == 2) {
          *(int *)((int)__s + 0x1c) = iVar3 << 1;
        }
        ak_set_debug_num_info(5,1,"frame_size");
        uVar4 = (*(uint *)((int)__s + 0x134) >> 3) *
                *(int *)((int)__s + 0x130) * *(int *)((int)__s + 0x138);
        if (uVar4 == 0) {
          uVar4 = 16000;
        }
        FUN_000192ac(*(int *)((int)__s + 0x1c) * 1000,uVar4);
        *(undefined4 *)((int)__s + 0x18) = extraout_r0;
        ak_set_debug_num_info(5,1,"frame_interval",extraout_r0);
        *(undefined4 *)((int)__s + 0x20) = 0;
        memset((void *)((int)__s + 0x54),0,0xdc);
        *(undefined4 *)((int)__s + 0x120) = 0xccc;
        *(undefined2 *)((int)__s + 0x54) = 0xffd8;
        *(undefined4 *)((int)__s + 0x58) = 0xc;
        *(undefined4 *)((int)__s + 0x11c) = 0xc;
        *(undefined4 *)((int)__s + 0x60) = 0x6000;
        *(undefined2 *)((int)__s + 100) = 4;
        *(undefined2 *)((int)__s + 0x68) = 0x28;
        *(undefined4 *)((int)__s + 0x6c) = 0x14;
        *(undefined2 *)((int)__s + 0x7a) = 0x400;
        *(undefined2 *)((int)__s + 0x78) = 0x400;
        *(undefined4 *)((int)__s + 300) = 2;
        *(undefined2 *)((int)__s + 0x80) = 0x200;
        *(undefined4 *)((int)__s + 0x7c) = 0x18;
        *(undefined4 *)((int)__s + 0x114) = 0x8000;
        *(undefined2 *)((int)__s + 0x66) = 0;
        *(undefined4 *)((int)__s + 0x74) = 0;
        *(undefined4 *)((int)__s + 0x118) = 0;
        *(undefined4 *)((int)__s + 0x128) = 0;
        *(undefined4 *)((int)__s + 0x124) = 0;
        memset((void *)((int)__s + 0x30),0,0xc);
        memset((void *)((int)__s + 0x3c),0,0xc);
        uVar2 = *param_1;
        *(undefined4 *)((int)__s + 0x4c) = 2;
        *param_2 = iVar1;
        *(void **)(&DAT_0002c03c + iVar1 * 4) = __s;
        FUN_000136f0(uVar2,param_1 + 2,extraout_r2,extraout_r3);
        iVar1 = 0;
        goto LAB_0001461c;
      }
      ak_print(5,1,"[%s:%d] dac dev open failed\n","init_adc_dev",0x1f1);
      ak_mem_free(__s);
    }
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = 0x500000c;
  }
LAB_0001461c:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaved...\n","ak_ai_open",0x3e6);
  return iVar1;
}



undefined4 ak_ai_get_handle_id(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (uint *)0x0) {
    ak_print(5,4,"ai_handle_id is NULL\n");
    return 0x100;
  }
  if (3 < param_1) {
    ak_print(5,1,"[%s:%d] dev_id invalid \n","ak_ai_get_handle_id",0x3f9);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (*(int *)(&DAT_0002c03c + param_1 * 4) == 0) {
    ak_print(5,1,"[%s:%d] no device id %d\n","ak_ai_get_handle_id",0x402,param_1);
    uVar1 = 0x101;
    *param_2 = 0xffffffff;
  }
  else {
    uVar1 = 0;
    *param_2 = param_1;
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar1;
}



undefined4 ak_ai_start_capture(uint param_1)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  
  ak_print(5,5,"[%s:%d] entering...\n","ak_ai_start_capture",0x413);
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (param_1 < 4) {
    puVar1 = *(undefined1 **)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    puVar1 = (undefined1 *)FUN_00013558(param_1);
  }
  if (puVar1 == (undefined1 *)0x0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_start_capture",0x419);
    uVar3 = 0x5000004;
    goto LAB_00014c08;
  }
  iVar2 = *(int *)(puVar1 + 0x20);
  if (iVar2 != 0) {
    ak_print(5,1,"[%s:%d] already running\n","ak_ai_start_capture",0x41e);
    uVar3 = 0;
    goto LAB_00014c08;
  }
  *(undefined4 *)(puVar1 + 0x50) = 0;
  *(undefined4 *)(puVar1 + 0x154) = 0;
  *puVar1 = 1;
  *(undefined1 **)(puVar1 + 0x148) = puVar1 + 0x148;
  *(undefined1 **)(puVar1 + 0x14c) = puVar1 + 0x148;
  *(undefined4 *)(puVar1 + 0x150) = 0;
  ak_thread_mutex_init(puVar1 + 0x158,0);
  local_30 = *(int *)(puVar1 + 0x130);
  local_28 = 0x10;
  if (*(int *)(puVar1 + 0x13c) == 0) {
    local_24 = local_30;
    if (local_30 < 16000) {
      local_24 = 0x200;
    }
    local_2c = 1;
    if (15999 < local_30) {
      if (local_24 < 32000) goto LAB_00014cb4;
      if (local_24 < 0xbb81) goto LAB_00014cd4;
LAB_00014bdc:
      local_24 = 0x1000;
    }
  }
  else {
    local_2c = *(undefined4 *)(puVar1 + 0x138);
    if (local_30 < 16000) {
LAB_00014cb4:
      local_24 = 0x400;
    }
    else if (local_30 < 32000) {
LAB_00014cd4:
      local_24 = 0x800;
    }
    else {
      if (local_30 < 0xbb81) goto LAB_00014bdc;
      local_24 = 0x2000;
    }
  }
  local_20 = 8;
  local_34 = iVar2;
  local_1c = iVar2;
  ak_set_debug_num_info(5,1,"ai_period_bytes");
  ak_set_debug_num_info(5,1,"ai_periods",local_20);
  iVar2 = osal_ai_set_param(*(undefined4 *)(puVar1 + 4),&local_34);
  if (iVar2 == 0) {
    iVar2 = osal_ai_reset_buf(*(undefined4 *)(puVar1 + 4));
    if (iVar2 == 0) {
      iVar2 = osal_ai_capture_resume(*(undefined4 *)(puVar1 + 4));
      if (iVar2 == 0) {
        uVar4 = 0x32;
        iVar2 = ak_thread_create(puVar1 + 8,FUN_00013e18,puVar1,0x19000,0x32);
        if (iVar2 == 0) {
          ak_print(5,5,"[%s:%d] create capture pcm thread OK\n","capture_start_running",0x2ff);
          *(undefined4 *)(puVar1 + 0x20) = 1;
          uVar3 = 0;
          goto LAB_00014c08;
        }
        ak_print(5,1,"create capture_pcm_thread FAILED, ret=%d\n",iVar2);
        uVar3 = 0x5000016;
      }
      else {
        uVar4 = 0x2f5;
        ak_print(5,1,"[%s:%d] osal_ai_capture_resume failed\n","capture_start_running",0x2f5);
        uVar3 = 0x500000d;
      }
    }
    else {
      uVar4 = 0x2f0;
      ak_print(5,1,"[%s:%d] osal_ai_reset_buf failed\n","capture_start_running",0x2f0);
      uVar3 = 0x500000d;
    }
  }
  else {
    ak_print(5,1,"[%s:%d] adc_dev_set_param failed\n","set_dev_param",0x130);
    uVar4 = 0x2eb;
    ak_print(5,1,"[%s:%d] adc_dev_set_param failed\n","capture_start_running",0x2eb);
    uVar3 = 0x500000d;
  }
  ak_print(5,1,"create capture_pcm_thread FAILED, ret=%d\n",uVar3,uVar4);
  *puVar1 = 0;
LAB_00014c08:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar3;
}



undefined4 ak_ai_stop_capture(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  
  ak_print(5,4,"[%s:%d] entering...\n","ak_ai_stop_capture",0x43a);
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (param_1 < 4) {
    puVar3 = *(undefined1 **)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    puVar3 = (undefined1 *)FUN_00013558(param_1);
  }
  if (puVar3 == (undefined1 *)0x0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_stop_capture",0x43f);
    uVar2 = 0x5000004;
  }
  else {
    *puVar3 = 0;
    uVar2 = 0;
    if (*(int *)(puVar3 + 0x20) != 0) {
      iVar1 = osal_ai_reset_buf(*(undefined4 *)(puVar3 + 4));
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        ak_print(5,1,"[%s:%d] osal_ai_capture_pause failed!\n","ak_ai_stop_capture",0x446);
        uVar2 = 0x500000d;
      }
      FUN_00012fec((int)puVar3);
      ak_thread_mutex_destroy(puVar3 + 0x158);
      *(undefined4 *)(puVar3 + 0x20) = 0;
      ak_print(5,4,"[%s:%d] join capture pcm thread...\n","ak_ai_stop_capture",1099);
      ak_thread_join(*(undefined4 *)(puVar3 + 8));
      ak_print(5,3,"[%s:%d] capture pcm thread join OK\n","ak_ai_stop_capture",0x44d);
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,4,"[%s:%d] leave...ret =%d\n","ak_ai_stop_capture",0x451,uVar2);
  return uVar2;
}



int ak_ai_get_frame(uint param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_000135a0(param_2);
  if (iVar1 != 0) {
    return iVar1;
  }
  ak_print(5,5,"[%s:%d] entry....\n","ak_ai_get_frame",0x465);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_frame",0x469);
    iVar2 = 0x5000004;
  }
  else {
    *(undefined4 *)(iVar1 + 0x50) = 1;
    if (*(int *)(iVar1 + 0x20) == 0) {
      ak_print(5,1,"[%s:%d] capture not start,please call ak_ai_start_capture first \n",
               "ak_ai_get_frame",0x46e);
      iVar2 = 0x5000007;
    }
    else if (param_3 == 0) {
      iVar2 = FUN_0001379c(iVar1,param_2);
    }
    else {
      iVar3 = 0x20;
      do {
        iVar2 = FUN_0001379c(iVar1,param_2);
        if (iVar2 != 0x5000011) break;
        ak_sleep_ms(10);
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaving....\n","ak_ai_get_frame",0x47b);
  return iVar2;
}



int ak_ai_release_frame(uint param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  ak_print(5,5,"[%s:%d] entrying... \n","ak_ai_release_frame",0x48a);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  iVar1 = FUN_00012e9c(param_2);
  if (iVar1 == 0) {
    if (*param_2 == 0) {
      ak_print(5,1,"[%s:%d] frame is NULL can\'t be released\n","ak_ai_release_frame",0x495);
    }
    else {
      ak_mem_free();
    }
    iVar2 = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    *param_2 = 0;
    param_2[1] = 0;
    param_2[4] = 0;
    if (3 < param_1) {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_release_frame",0x4a0);
      iVar1 = 0x5000004;
    }
    else {
      *(int *)(iVar2 + 0x2c) = *(int *)(iVar2 + 0x2c) + 1;
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaving... \n","ak_ai_release_frame",0x4a5);
  return iVar1;
}



undefined4 ak_ai_set_dev_buf_size(void)

{
  ak_print(5,1,"[%s:%d] this function is deprecated and no longer in use\n","ak_ai_set_dev_buf_size"
           ,0x4b2);
  return 0;
}



undefined4 ak_ai_get_dev_buf_size(uint param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  ak_print(5,4,"[%s:%d] enter...\n","ak_ai_get_dev_buf_size",0x4c0);
  if (param_2 != (int *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_dev_buf_size",0x4ca);
      uVar3 = 0x5000004;
    }
    else {
      iVar2 = *(int *)(iVar1 + 0x130);
      if (iVar2 < 16000) {
        iVar2 = 0x200;
      }
      else if (iVar2 < 32000) {
        iVar2 = 0x400;
      }
      else if (iVar2 < 0xbb81) {
        iVar2 = 0x800;
      }
      else {
        iVar2 = 0x1000;
      }
      *param_2 = iVar2;
      if (*(int *)(iVar1 + 0x13c) - 1U < 3) {
        *param_2 = iVar2 << 1;
      }
      uVar3 = 0;
    }
    ak_print(5,4,"[%s:%d] leave...\n","ak_ai_get_dev_buf_size",0x4d4);
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return uVar3;
  }
  ak_print(5,1,"[%s:%d] dev_buf_size is NULL\n","ak_ai_get_dev_buf_size",0x4c3);
  return 0x100;
}



undefined4 ak_ai_set_frame_length(uint param_1,uint param_2)

{
  undefined4 extraout_r0;
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  
  if ((param_2 & 1) != 0) {
    ak_print(5,1,"[%s:%d] not support frame interval =%d\n","ak_ai_set_frame_length",0x4e3,param_2);
    return 0x101;
  }
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar5 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar5 = FUN_00013558(param_1);
  }
  if (iVar5 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_frame_length",0x4ea);
    uVar4 = 0x5000004;
    goto LAB_000155cc;
  }
  uVar3 = *(uint *)(iVar5 + 0x130);
  if ((int)uVar3 < 16000) {
    iVar2 = 0x200;
  }
  else if ((int)uVar3 < 32000) {
    iVar2 = 0x400;
  }
  else if ((int)uVar3 < 0xbb81) {
    iVar2 = 0x800;
  }
  else {
    iVar2 = 0x1000;
  }
  iVar1 = *(int *)(iVar5 + 0x138);
  if (iVar1 == 2) {
    if (iVar2 * 2 <= (int)param_2) {
LAB_00015514:
      if (uVar3 < 0xbb81) {
        if ((int)param_2 < 0x2001) goto LAB_00015528;
        uVar4 = 0x503;
      }
      else if ((int)param_2 < 0x4001) {
LAB_00015528:
        if ((iVar1 != 2 || *(int *)(iVar5 + 0x13c) != 0) || ((param_2 & 3) == 0)) goto LAB_00015538;
        uVar4 = 0x50e;
      }
      else {
        uVar4 = 0x508;
      }
      ak_print(5,1,"[%s:%d] STEREO not support frame length =%d\n","ak_ai_set_frame_length",uVar4,
               param_2);
      uVar4 = 0x101;
      goto LAB_000155cc;
    }
  }
  else if (iVar2 <= (int)param_2) {
    if (iVar1 != 1) goto LAB_00015514;
    if (uVar3 < 0xbb81) {
      if (0x1000 < (int)param_2) {
        uVar4 = 0x4f8;
LAB_0001561c:
        ak_print(5,1,"[%s:%d] MONO not support frame length =%d\n","ak_ai_set_frame_length",uVar4,
                 param_2);
        uVar4 = 0x101;
        goto LAB_000155cc;
      }
    }
    else if (0x2000 < (int)param_2) {
      uVar4 = 0x4fd;
      goto LAB_0001561c;
    }
LAB_00015538:
    if (*(uint *)(iVar5 + 0x1c) == param_2) {
      ak_print(5,2,"[%s:%d] set frame length is the same, length =%d\n","ak_ai_set_frame_length",
               0x514,param_2);
      uVar4 = 0;
    }
    else if (*(int *)(iVar5 + 0x20) == 0) {
      uVar3 = iVar1 * uVar3 * (*(uint *)(iVar5 + 0x134) >> 3);
      if (uVar3 == 0) {
        uVar3 = 16000;
      }
      *(uint *)(iVar5 + 0x1c) = param_2;
      FUN_000192ac(param_2 * 1000,uVar3);
      *(undefined4 *)(iVar5 + 0x18) = extraout_r0;
      ak_print(5,4,"[%s:%d] frame_length = %d\n","ak_ai_set_frame_length",0x524,param_2);
      ak_set_debug_num_info(5,1,"frame_size",*(undefined4 *)(iVar5 + 0x1c));
      ak_set_debug_num_info(5,1,"frame_interval",*(undefined4 *)(iVar5 + 0x18));
      uVar4 = 0;
    }
    else {
      ak_print(5,1,"[%s:%d] capture has already start, can not set frame interval\n",
               "ak_ai_set_frame_length",0x51b);
      uVar4 = 0x5000006;
    }
    goto LAB_000155cc;
  }
  ak_print(5,1,"[%s:%d] not support frame length =%d\n","ak_ai_set_frame_length",0x4f1,param_2);
  uVar4 = 0x101;
LAB_000155cc:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar4;
}



undefined4 ak_ai_get_frame_length(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == (undefined4 *)0x0) {
    ak_print(5,1,"[%s:%d] frame_length is NULL!\n","ak_ai_get_frame_length",0x538);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_frame_length",0x53e);
    uVar2 = 0x5000004;
  }
  else {
    uVar2 = 0;
    *param_2 = *(undefined4 *)(iVar1 + 0x1c);
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



undefined4 ak_ai_clear_frame_buffer(void)

{
  ak_print(5,1,"[%s:%d] this function is deprecated and no longer in use\n",
           "ak_ai_clear_frame_buffer",0x551);
  return 0;
}



undefined4 ak_ai_set_max_frame_num(void)

{
  ak_print(5,1,"[%s:%d] this function is deprecated and no longer in use\n",
           "ak_ai_set_max_frame_num",0x55e);
  return 0;
}



undefined4 ak_ai_get_max_frame_num(void)

{
  ak_print(5,1,"[%s:%d] this function is deprecated and no longer in use\n",
           "ak_ai_get_max_frame_num",0x56b);
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00015b9c)
// WARNING: Removing unreachable block (ram,0x00015bb4)

int ak_ai_set_gain(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (8 < param_2) {
    ak_print(5,1,"[%s:%d] invalid volume = %d, gain must in [0,8]\n","ak_ai_set_gain",0x579,param_2)
    ;
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar2 = FUN_00013558(param_1);
  }
  if (iVar2 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_gain",0x580);
    iVar1 = 0x5000004;
    goto LAB_00015a48;
  }
  if (*(int *)(iVar2 + 0x13c) == 1) {
    ak_print(5,1,"[%s:%d] set gain not support PDM\n","ak_ai_set_gain",0x583);
    iVar1 = 0x101;
    goto LAB_00015a48;
  }
  uVar3 = param_2;
  ak_print(5,4,"[%s:%d] set gain %d\n","ak_ai_set_gain",0x588,param_2);
  if (param_2 == 0) {
    iVar2 = osal_ai_get_source(*(undefined4 *)(iVar2 + 4));
    if (iVar2 == 0) {
LAB_00015a88:
      ak_set_debug_num_info(5,1,"ai_gain",param_2);
      iVar1 = 0;
      goto LAB_00015a48;
    }
    ak_print(5,1,"[%s:%d] osal_ai_get_source failed\n","ai_set_mute",0x22c,uVar3);
  }
  else {
    iVar1 = FUN_00013af4((undefined4 *)(iVar2 + 4),*(int *)(iVar2 + 0x4c));
    if (iVar1 != 0) {
      ak_print(5,1,"[%s:%d] ai_set_source failed\n","ak_ai_set_gain",0x592,uVar3);
      goto LAB_00015a48;
    }
    iVar1 = osal_ai_get_gain(*(undefined4 *)(iVar2 + 4));
    if (iVar1 == 0) {
      if ((param_2 == 1) || (iVar2 = osal_ai_set_gain(*(undefined4 *)(iVar2 + 4)), iVar2 == 0))
      goto LAB_00015a88;
      ak_print(5,1,"[%s:%d] osal_ai_set_gain failed\n","ai_set_gain",0x240,uVar3);
    }
    else {
      ak_print(5,1,"[%s:%d] osal_ai_get_gain failed\n","ai_set_gain",0x23c,uVar3);
    }
    ak_print(5,1,"[%s:%d] ai_set_gain failed\n","ak_ai_set_gain",0x598);
  }
  iVar1 = 0x500000d;
LAB_00015a48:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



undefined4 ak_ai_set_volume(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  
  if (0x6e < param_2 + 0x5aU) {
    ak_print(5,1,"[%s:%d] db =%d, db must in [-90, 20]\n","ak_ai_set_volume",0x5ad,param_2);
    return 0x101;
  }
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_volume",0x5b4);
    uVar2 = 0x5000004;
    goto LAB_00015ce8;
  }
  if (*(int *)(iVar3 + 0x20) != 0) {
    iVar4 = param_2;
    ak_print(5,3,"[%s:%d] db =%d\n","ak_ai_set_volume",0x5b7,param_2);
    iVar1 = ak_vqe_inner_get_ai_aslc(0,&local_24);
    if (iVar1 != 0) {
      ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_aslc FAILED\n","ak_ai_set_volume",0x5b9,iVar4);
      uVar2 = 0x5000017;
      goto LAB_00015ce8;
    }
    local_20 = param_2;
    iVar1 = ak_vqe_inner_set_ai_aslc(0,&local_24);
    if (iVar1 != 0) {
      ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_aslc FAILED\n","ak_ai_set_volume",0x5c0,iVar4);
      uVar2 = 0x5000017;
      goto LAB_00015ce8;
    }
  }
  uVar2 = 0;
  *(int *)(iVar3 + 0x118) = param_2;
LAB_00015ce8:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x00015f30)
// WARNING: Removing unreachable block (ram,0x00015f88)
// WARNING: Removing unreachable block (ram,0x00015f4c)

undefined4 ak_ai_get_gain(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_gain",0x5dd);
      uVar1 = 0x5000004;
    }
    else if (*(int *)(iVar2 + 0x13c) == 1) {
      ak_print(5,1,"[%s:%d] get gain not support PDM\n","ak_ai_get_gain",0x5e0);
      uVar1 = 0x101;
    }
    else {
      iVar2 = osal_ai_get_source(*(undefined4 *)(iVar2 + 4));
      if (iVar2 == 0) {
        uVar1 = 0;
        *param_2 = 0;
      }
      else {
        ak_print(5,1,"[%s:%d] osal_ai_get_source failed\n","ak_ai_get_gain",0x5e7);
        uVar1 = 0x5000005;
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return uVar1;
  }
  ak_print(5,1,"[%s:%d] gain is NULL\n","ak_ai_get_gain",0x5d6);
  return 0x100;
}



undefined4 ak_ai_get_volume(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_2 != (undefined4 *)0x0) {
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_volume",0x610);
      uVar2 = 0x5000004;
    }
    else {
      if (*(int *)(iVar1 + 0x20) == 0) {
        *param_2 = *(undefined4 *)(iVar1 + 0x118);
      }
      else {
        iVar1 = ak_vqe_inner_get_ai_aslc(0,&local_1c);
        uVar2 = local_18;
        if (iVar1 != 0) {
          uVar2 = 0;
        }
        *param_2 = uVar2;
      }
      ak_print(5,3,"[%s:%d] ak_ai_set_vqe_attr success\n","ak_ai_get_volume",0x61b);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return uVar2;
  }
  ak_print(5,1,"[%s:%d] db is NULL\n","ak_ai_get_volume",0x609);
  return 0x100;
}



int ak_ai_enable_nr(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_24;
  int local_20;
  uint local_1c;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_enable_nr",0x62c);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_enable_nr",0x633);
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(3,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) != 0) {
        local_24 = iVar1;
        local_20 = iVar1;
        local_1c = iVar1;
        memcpy(&local_24,(void *)(iVar3 + 0x54),0xc);
        local_1c = param_2;
        iVar2 = ak_vqe_inner_set_ai_nr(0,&local_24);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_nr FAILED\n","ak_ai_enable_nr",0x63f);
          iVar1 = 0x5000017;
          goto LAB_000161d8;
        }
      }
      *(uint *)(iVar3 + 0x5c) = param_2;
    }
  }
LAB_000161d8:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



int ak_ai_enable_agc(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  uint local_1c;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_enable_agc",0x655);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_enable_agc",0x65c);
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(4,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x5c) == 0) {
        ak_print(5,1,"[%s:%d] nr no open, can not open agc!\n","ak_ai_enable_agc",0x663);
        iVar1 = 0x5000001;
      }
      else {
        if (*(int *)(iVar3 + 0x20) != 0) {
          local_2c = iVar1;
          local_28 = iVar1;
          local_24 = iVar1;
          local_20 = iVar1;
          local_1c = iVar1;
          memcpy(&local_2c,(void *)(iVar3 + 0x60),0x14);
          local_1c = param_2;
          iVar2 = ak_vqe_inner_set_ai_agc(0,&local_2c);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_agc FAILED\n","ak_ai_enable_agc",0x66d);
            iVar1 = 0x5000017;
            goto LAB_00016368;
          }
        }
        *(uint *)(iVar3 + 0x70) = param_2;
      }
    }
  }
LAB_00016368:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



int ak_ai_enable_aec(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  uint local_20;
  int local_1c;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_enable_aec",0x683);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_enable_aec",0x68a);
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(5,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) != 0) {
        local_30 = iVar1;
        local_2c = iVar1;
        local_28 = iVar1;
        local_24 = iVar1;
        local_20 = iVar1;
        local_1c = iVar1;
        memcpy(&local_30,(void *)(iVar3 + 0x74),0x18);
        local_20 = param_2;
        iVar2 = ak_vqe_inner_set_ai_aec(0,&local_30);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_aec FAILED\n","ak_ai_enable_aec",0x696);
          iVar1 = 0x5000017;
          goto LAB_00016528;
        }
      }
      *(uint *)(iVar3 + 0x84) = param_2;
    }
  }
LAB_00016528:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



undefined4 ak_ai_enable_eq(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_a0 [124];
  undefined1 local_24;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_enable_eq",0x6ac);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_enable_eq",0x6b3);
    uVar2 = 0x5000004;
  }
  else {
    if (*(int *)(iVar3 + 0x20) != 0) {
      memset(auStack_a0,0,0x88);
      memcpy(auStack_a0,(void *)(iVar3 + 0x8c),0x88);
      local_24 = (char)param_2;
      iVar1 = ak_vqe_inner_set_ai_eq(0,auStack_a0);
      if (iVar1 != 0) {
        ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_eq FAILED\n","ak_ai_enable_eq",0x6ba);
        uVar2 = 0x5000017;
        goto LAB_000166a8;
      }
    }
    uVar2 = 0;
    *(char *)(iVar3 + 0x108) = (char)param_2;
  }
LAB_000166a8:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



int ak_ai_enable_vad(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_28;
  int local_24;
  uint local_20;
  int local_1c;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_enable_vad",0x6d1);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_enable_vad",0x6d8);
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(6,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) != 0) {
        local_28 = iVar1;
        local_24 = iVar1;
        local_20 = iVar1;
        local_1c = iVar1;
        memcpy(&local_28,(void *)(iVar3 + 0x120),0x10);
        local_20 = param_2;
        iVar2 = ak_vqe_inner_set_ai_vad(0,&local_28);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_vad FAILED\n","ak_ai_enable_vad",0x6e4);
          iVar1 = 0x5000017;
          goto LAB_0001683c;
        }
      }
      *(uint *)(iVar3 + 0x128) = param_2;
    }
  }
LAB_0001683c:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



int ak_ai_set_nr_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] nr_attr is NULL\n","ak_ai_set_nr_attr",0x6fb);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_nr_attr",0x702);
    iVar2 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(3,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    iVar2 = iVar1;
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) == 0) {
        iVar2 = ak_vqe_inner_check_attr_params(1,param_2);
        if (iVar2 != 0) goto LAB_00016984;
      }
      else {
        iVar2 = ak_vqe_inner_set_ai_nr(0,param_2);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_nr FAILED\n","ak_ai_set_nr_attr",0x70b);
          iVar2 = 0x5000017;
          goto LAB_00016984;
        }
      }
      memcpy((void *)(iVar3 + 0x54),param_2,0xc);
      ak_print(5,5,"[%s:%d] ak_ai_set_vqe_attr success\n","ak_ai_set_nr_attr",0x716);
      iVar2 = iVar1;
    }
  }
LAB_00016984:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar2;
}



int ak_ai_get_nr_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != (void *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_nr_attr",0x72f);
      iVar1 = 0x5000004;
    }
    else {
      iVar1 = FUN_00013630(3,*(int *)(iVar2 + 0x130),(int *)(iVar2 + 0x13c));
      if (iVar1 == 0) {
        if (*(int *)(iVar2 + 0x20) == 0) {
          memcpy(param_2,(void *)(iVar2 + 0x54),0xc);
        }
        else {
          iVar2 = ak_vqe_inner_get_ai_nr(0,param_2);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_nr FAILED\n","ak_ai_get_nr_attr",0x738);
            iVar1 = 0x5000017;
          }
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  ak_print(5,1,"[%s:%d] nr_attr is NULL\n","ak_ai_get_nr_attr",0x727);
  return 0x101;
}



int ak_ai_set_agc_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] agc_attr is NULL\n","ak_ai_set_agc_attr",0x750);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_agc_attr",0x757);
    iVar2 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(4,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    iVar2 = iVar1;
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) == 0) {
        iVar2 = ak_vqe_inner_check_attr_params(2,param_2);
        if (iVar2 != 0) goto LAB_00016cac;
      }
      else {
        iVar2 = ak_vqe_inner_set_ai_agc(0,param_2);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_agc FAILED\n","ak_ai_set_agc_attr",0x760);
          iVar2 = 0x5000017;
          goto LAB_00016cac;
        }
      }
      memcpy((void *)(iVar3 + 0x60),param_2,0x14);
      ak_print(5,5,"[%s:%d] ak_ai_set_vqe_attr success\n","ak_ai_set_agc_attr",0x76b);
      iVar2 = iVar1;
    }
  }
LAB_00016cac:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar2;
}



int ak_ai_get_agc_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != (void *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_agc_attr",0x784);
      iVar1 = 0x5000004;
    }
    else {
      iVar1 = FUN_00013630(4,*(int *)(iVar2 + 0x130),(int *)(iVar2 + 0x13c));
      if (iVar1 == 0) {
        if (*(int *)(iVar2 + 0x5c) == 0) {
          ak_print(5,1,"[%s:%d] nr no open, can not open agc!\n","ak_ai_get_agc_attr",0x78c);
          iVar1 = 0x5000001;
        }
        else if (*(int *)(iVar2 + 0x20) == 0) {
          memcpy(param_2,(void *)(iVar2 + 0x60),0x14);
        }
        else {
          iVar2 = ak_vqe_inner_get_ai_agc(0,param_2);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_agc FAILED\n","ak_ai_get_agc_attr",0x793);
            iVar1 = 0x5000017;
          }
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  ak_print(5,1,"[%s:%d] agc_attr is NULL\n","ak_ai_get_agc_attr",0x77c);
  return 0x100;
}



int ak_ai_set_aec_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] aec_attr is NULL\n","ak_ai_set_aec_attr",0x7aa);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_aec_attr",0x7b1);
    iVar2 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(5,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    iVar2 = iVar1;
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) == 0) {
        iVar2 = ak_vqe_inner_check_attr_params(3,param_2);
        if (iVar2 != 0) goto LAB_00017008;
      }
      else {
        iVar2 = ak_vqe_inner_set_ai_aec(0,param_2);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_aec FAILED\n","ak_ai_set_aec_attr",0x7ba);
          iVar2 = 0x5000017;
          goto LAB_00017008;
        }
      }
      memcpy((void *)(iVar3 + 0x74),param_2,0x18);
      iVar2 = iVar1;
    }
  }
LAB_00017008:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar2;
}



int ak_ai_get_aec_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != (void *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_aec_attr",0x7dd);
      iVar1 = 0x5000004;
    }
    else {
      iVar1 = FUN_00013630(5,*(int *)(iVar2 + 0x130),(int *)(iVar2 + 0x13c));
      if (iVar1 == 0) {
        if (*(int *)(iVar2 + 0x20) == 0) {
          memcpy(param_2,(void *)(iVar2 + 0x74),0x18);
        }
        else {
          iVar2 = ak_vqe_inner_get_ai_aec(0,param_2);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_aec FAILED\n","ak_ai_get_aec_attr",0x7e6);
            iVar1 = 0x5000017;
          }
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  ak_print(5,1,"[%s:%d] aec_attr is NULL\n","ak_ai_get_aec_attr",0x7d5);
  return 0x100;
}



int ak_ai_set_eq_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] eq_attr is NULL\n","ak_ai_set_eq_attr",0x7fd);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar2 = FUN_00013558(param_1);
  }
  if (iVar2 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_eq_attr",0x804);
    iVar1 = 0x5000004;
  }
  else {
    if (*(int *)(iVar2 + 0x20) == 0) {
      iVar1 = ak_vqe_inner_check_attr_params(0,param_2);
      if (iVar1 != 0) goto LAB_00017348;
    }
    else {
      iVar1 = ak_vqe_inner_set_ai_eq(0,param_2);
      if (iVar1 != 0) {
        ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_eq FAILED\n","ak_ai_set_eq_attr",0x808);
        iVar1 = 0x5000017;
        goto LAB_00017348;
      }
    }
    memcpy((void *)(iVar2 + 0x8c),param_2,0x88);
    ak_print(5,3,"[%s:%d] ak_ai_set_vqe_attr success\n","ak_ai_set_eq_attr",0x813);
    iVar1 = 0;
  }
LAB_00017348:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



undefined4 ak_ai_get_eq_attr(uint param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] eq_attr is NULL\n","ak_ai_get_eq_attr",0x824);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_eq_attr",0x82b);
    uVar2 = 0x5000004;
  }
  else if (*(int *)(iVar1 + 0x20) == 0) {
    memcpy(param_2,(void *)(iVar1 + 0x8c),0x88);
    uVar2 = 0;
  }
  else {
    iVar1 = ak_vqe_inner_get_ai_eq(0,param_2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_eq FAILED\n","ak_ai_get_eq_attr",0x82f);
      uVar2 = 0x5000017;
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



undefined4 ak_ai_set_source(uint param_1,uint param_2)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  if (1 < param_2) {
    ak_print(5,1,"[%s:%d] source not support %d\n","check_source_param",0x32f,param_2);
    return 0x101;
  }
  if (param_2 == 1) {
    iVar5 = 4;
  }
  else {
    iVar5 = 2;
  }
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar4 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar4 = FUN_00013558(param_1);
  }
  if (iVar4 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_source",0x851);
    uVar3 = 0x5000004;
  }
  else if (*(int *)(iVar4 + 0x13c) == 0) {
    iVar1 = FUN_00013af4((undefined4 *)(iVar4 + 4),iVar5);
    if (iVar1 == 0) {
      *(int *)(iVar4 + 0x4c) = iVar5;
      uVar3 = 0;
    }
    else {
      pcVar2 = "mic";
      if (iVar5 != 2) {
        pcVar2 = "linein";
      }
      ak_print(5,1,"[%s:%d] set source %s failed\n","ak_ai_set_source",0x85c,pcVar2);
      uVar3 = 0x500000d;
    }
  }
  else {
    ak_print(5,1,"[%s:%d] set source only used in ADC\n","ak_ai_set_source",0x854);
    uVar3 = 0x101;
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x000177a0)

undefined4 ak_ai_get_source(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_source",0x876);
      uVar2 = 0x5000004;
    }
    else if (*(int *)(iVar1 + 0x13c) == 0) {
      iVar1 = osal_ai_get_source(*(undefined4 *)(iVar1 + 4));
      if (iVar1 == 0) {
        uVar2 = 0;
        *param_2 = 0;
      }
      else {
        ak_print(5,1,"[%s:%d] dac_dev_get_source failed\n","ak_ai_get_source",0x880);
        uVar2 = 0x500000d;
      }
    }
    else {
      ak_print(5,1,"[%s:%d] get source only used in ADC\n","ak_ai_get_source",0x879);
      uVar2 = 0x101;
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return uVar2;
  }
  ak_print(5,1,"[%s:%d] src is NULL\n","ak_ai_get_source",0x86f);
  return 0x100;
}



int ak_ai_set_vad_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] vad_attr is NULL\n","ak_ai_set_vad_attr",0x899);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar3 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar3 = FUN_00013558(param_1);
  }
  if (iVar3 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_vad_attr",0x8a0);
    iVar2 = 0x5000004;
  }
  else {
    iVar1 = FUN_00013630(6,*(int *)(iVar3 + 0x130),(int *)(iVar3 + 0x13c));
    iVar2 = iVar1;
    if (iVar1 == 0) {
      if (*(int *)(iVar3 + 0x20) == 0) {
        iVar2 = ak_vqe_inner_check_attr_params(5,param_2);
        if (iVar2 != 0) goto LAB_0001790c;
      }
      else {
        iVar2 = ak_vqe_inner_set_ai_vad(0,param_2);
        if (iVar2 != 0) {
          ak_print(5,1,"[%s:%d] ak_vqe_inner_set_ai_vad FAILED\n","ak_ai_set_vad_attr",0x8a9);
          iVar2 = 0x5000017;
          goto LAB_0001790c;
        }
      }
      memcpy((void *)(iVar3 + 0x120),param_2,0x10);
      ak_print(5,4,"[%s:%d] ak_ai_set_vad_attr success\n","ak_ai_set_vad_attr",0x8b4);
      iVar2 = iVar1;
    }
  }
LAB_0001790c:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar2;
}



int ak_ai_get_vad_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != (void *)0x0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_vad_attr",0x8cd);
      iVar1 = 0x5000004;
    }
    else {
      iVar1 = FUN_00013630(6,*(int *)(iVar2 + 0x130),(int *)(iVar2 + 0x13c));
      if (iVar1 == 0) {
        if (*(int *)(iVar2 + 0x20) == 0) {
          memcpy(param_2,(void *)(iVar2 + 0x120),0x10);
        }
        else {
          iVar2 = ak_vqe_inner_get_ai_vad(0,param_2);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_vad FAILED\n","ak_ai_get_vad_attr",0x8d6);
            iVar1 = 0x5000017;
          }
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  ak_print(5,1,"[%s:%d] vad_attr is NULL\n","ak_ai_get_vad_attr",0x8c5);
  return 0x100;
}



undefined4 ak_ai_print_runtime_status(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_print_runtime_status",0x8fe);
    uVar2 = 0x5000004;
  }
  else {
    ak_print(5,3,"[%s:%d] read_dev_count=%d\n","ak_ai_print_runtime_status",0x900,
             *(undefined4 *)(iVar1 + 0x24));
    ak_print(5,3,"[%s:%d] get_frame_count=%d\n","ak_ai_print_runtime_status",0x901,
             *(undefined4 *)(iVar1 + 0x28));
    ak_print(5,3,"[%s:%d] release_frame_count=%d\n","ak_ai_print_runtime_status",0x902,
             *(undefined4 *)(iVar1 + 0x2c));
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



undefined4 ak_ai_save_aec_dump_file(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 < 2) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_save_aec_dump_file",0x91c);
      uVar2 = 0x5000004;
    }
    else if (*(int *)(iVar1 + 0x20) == 0) {
      *(uint *)(iVar1 + 0x48) = param_2;
      uVar2 = 0;
    }
    else {
      uVar2 = ak_vqe_inner_enable_dump(0);
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return uVar2;
  }
  ak_print(5,1,"[%s:%d] enable must be 0 or 1\n","ak_ai_save_aec_dump_file",0x915);
  return 0x101;
}



undefined4 ak_ai_close(uint param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  
  ak_print(5,5,"[%s:%d] enter\n","ak_ai_close",0x92f);
  ak_thread_rwlock_wrlock(DAT_0002c04c);
  if (param_1 < 4) {
    puVar2 = *(undefined1 **)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    puVar2 = (undefined1 *)FUN_00013558(param_1);
  }
  if (puVar2 == (undefined1 *)0x0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_close",0x934);
    uVar3 = 0x5000004;
  }
  else {
    *puVar2 = 0;
    if (*(int *)(puVar2 + 0x20) == 0) {
      uVar3 = 0;
    }
    else {
      iVar1 = osal_ai_reset_buf(*(undefined4 *)(puVar2 + 4));
      *(undefined4 *)(puVar2 + 0x20) = 0;
      uVar3 = 0x500000d;
      if (iVar1 == 0) {
        uVar3 = 0;
      }
      ak_print(5,4,"[%s:%d] join capture pcm thread...\n","ak_ai_close",0x93e);
      ak_thread_join(*(undefined4 *)(puVar2 + 8));
      ak_print(5,3,"[%s:%d] capture pcm thread join OK\n","ak_ai_close",0x940);
    }
    iVar1 = osal_ai_close(*(undefined4 *)(puVar2 + 4));
    if (iVar1 != 0) {
      ak_print(5,1,"[%s:%d] dac_dev_close failed!\n","ak_ai_close",0x945);
      uVar3 = 0x500000d;
    }
    if (*(FILE **)(puVar2 + 0x30) != (FILE *)0x0) {
      fclose(*(FILE **)(puVar2 + 0x30));
      *(undefined4 *)(puVar2 + 0x30) = 0;
      *(undefined4 *)(puVar2 + 0x34) = 0;
      *(undefined4 *)(puVar2 + 0x38) = 0;
    }
    if (*(FILE **)(puVar2 + 0x3c) != (FILE *)0x0) {
      fclose(*(FILE **)(puVar2 + 0x3c));
      *(undefined4 *)(puVar2 + 0x3c) = 0;
      *(undefined4 *)(puVar2 + 0x40) = 0;
      *(undefined4 *)(puVar2 + 0x44) = 0;
    }
    ak_mem_free(puVar2);
    *(undefined4 *)(&DAT_0002c03c + param_1 * 4) = 0;
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leave...\n","ak_ai_close",0x951);
  return uVar3;
}



int ak_ai_save_file(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_00013bd8(param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_wrlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_save_file",0x965);
      iVar2 = 0x5000004;
    }
    else {
      iVar2 = 0;
      if (*param_2 != 0) {
        iVar2 = FUN_000130c4(iVar1,(char *)(param_2 + 1),(char *)(param_2 + 0x41));
        if (iVar2 == 0) {
          uVar3 = ((*(uint *)(iVar1 + 0x134) >> 3) *
                  param_2[0x81] * *(int *)(iVar1 + 0x130) * *(int *)(iVar1 + 0x138)) / 1000;
          if ((uVar3 & 1) != 0) {
            uVar3 = uVar3 + 1;
          }
          *(uint *)(iVar1 + 0x34) = uVar3 * 1000;
          *(uint *)(iVar1 + 0x40) = uVar3 * 1000;
          *(undefined4 *)(iVar1 + 0x44) = 0;
          *(undefined4 *)(iVar1 + 0x38) = 0;
        }
        else {
          ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_save_file",0x96a);
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar2;
  }
  return iVar1;
}



int ak_ai_set_aslc_attr(uint param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] eq_attr is NULL\n","ak_ai_set_aslc_attr",0x984);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar2 = FUN_00013558(param_1);
  }
  if (iVar2 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_aslc_attr",0x98b);
    iVar1 = 0x5000004;
  }
  else {
    if (*(int *)(iVar2 + 0x20) == 0) {
      iVar1 = ak_vqe_inner_check_attr_params(4,param_2);
      if (iVar1 != 0) goto LAB_0001823c;
    }
    else {
      iVar1 = ak_vqe_inner_set_ai_aslc(0,param_2);
      if (iVar1 != 0) {
        ak_print(5,1,"ak_vqe_inner_set_ai_aslc FAILED\n");
        iVar1 = 0x5000017;
        goto LAB_0001823c;
      }
    }
    memcpy((void *)(iVar2 + 0x114),param_2,0xc);
    ak_print(5,3,"[%s:%d] ak_ai_set_aslc_attr success\n","ak_ai_set_aslc_attr",0x99a);
    iVar1 = 0;
  }
LAB_0001823c:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar1;
}



undefined4 ak_ai_get_aslc_attr(uint param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == (void *)0x0) {
    ak_print(5,1,"[%s:%d] eq_attr is NULL\n","ak_ai_get_aslc_attr",0x9ab);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_aslc_attr",0x9b2);
    uVar2 = 0x5000004;
  }
  else if (*(int *)(iVar1 + 0x20) == 0) {
    memcpy(param_2,(void *)(iVar1 + 0x114),0xc);
    uVar2 = 0;
  }
  else {
    iVar1 = ak_vqe_inner_get_ai_aslc(0,param_2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      ak_print(5,3,"[%s:%d] aslc not open\n","ak_ai_get_aslc_attr",0x9b6);
      uVar2 = 0x5000017;
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



undefined4 ak_ai_set_lib_print_level(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_print(5,4,"[%s:%d] enter\n","ak_ai_set_lib_print_level",0x9cc);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_lib_print_level",0x9d1);
    uVar2 = 0x5000004;
  }
  else {
    uVar2 = ak_vqe_inner_set_lib_print_level(0,param_2);
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar2;
}



undefined4 ak_ai_get_params(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_2 == (undefined4 *)0x0) {
    ak_print(5,1,"[%s:%d] invalid param\n","ak_ai_get_params",0x9e5);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_params",0x9ec);
    uVar4 = 0x5000004;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x134);
    uVar3 = *(undefined4 *)(iVar1 + 0x138);
    uVar4 = 0;
    *param_2 = *(undefined4 *)(iVar1 + 0x130);
    param_2[1] = uVar2;
    param_2[2] = uVar3;
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return uVar4;
}



int ak_ai_reset_params(uint param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r0;
  int iVar4;
  undefined4 extraout_r2;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 extraout_r2_00;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  
  puVar6 = param_3;
  if ((int)param_3 < 1) {
    puVar6 = param_2;
  }
  if (puVar6 == (undefined4 *)0x0) {
    ak_print(5,1,"[%s:%d] param = NULL && 0 >= frame_length\n","ak_ai_reset_params",0xa05);
    return 0x101;
  }
  if (param_2 != (undefined4 *)0x0) {
    iVar2 = FUN_00013330(param_2);
    if (iVar2 != 0) {
      return iVar2;
    }
    uVar7 = param_2[3];
    if (uVar7 != param_1) {
      ak_print(5,1,
               "[%s:%d] error ai_handle_id should equal param->dev_id:            ai_handle_id = %d, param->dev_id = %d\n"
               ,"ak_ai_reset_params",0xa11,param_1,uVar7);
      return 0x101;
    }
    if (uVar7 - 2 < 2) {
      ak_print(5,1,
               "[%s:%d] ak_ai_reset_params() not support i2s,            please call ak_ai_stop_capture(), ak_ai_close(), and call ak_ai_open(), reset the params !\n"
               ,"ak_ai_reset_params",0xa18);
      return 0x101;
    }
  }
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    uVar5 = extraout_r2;
  }
  else {
    iVar2 = FUN_00013558(param_1);
    uVar5 = extraout_r2_00;
  }
  if (iVar2 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_reset_params",0xa1f);
    iVar9 = 0x5000004;
  }
  else if (*(int *)(iVar2 + 0x20) == 0) {
    if (param_2 != (undefined4 *)0x0) {
      *(undefined4 *)(iVar2 + 0x130) = *param_2;
      uVar8 = param_2[2];
      uVar3 = *param_2;
      *(undefined4 *)(iVar2 + 0x138) = uVar8;
      FUN_000136f0(uVar3,param_2 + 2,uVar5,uVar8);
      ak_print(5,3,"[%s:%d] params reset to rate=%d, channel=%d\n","ak_ai_reset_params",0xa2c,
               *(undefined4 *)(iVar2 + 0x130),*(undefined4 *)(iVar2 + 0x138));
    }
    iVar9 = *(int *)(iVar2 + 0x130);
    if (iVar9 < 16000) {
      puVar6 = (undefined4 *)0x200;
    }
    else if (iVar9 < 32000) {
      puVar6 = (undefined4 *)0x400;
    }
    else if (iVar9 < 0xbb81) {
      puVar6 = (undefined4 *)0x800;
    }
    else {
      puVar6 = (undefined4 *)0x1000;
    }
    iVar4 = *(int *)(iVar2 + 0x138);
    if (iVar4 == 2) {
      puVar6 = (undefined4 *)((int)puVar6 << 1);
    }
    if (param_3 != (undefined4 *)0x0) {
      bVar11 = SBORROW4((int)param_3,0x2000);
      puVar1 = param_3 + -0x800;
      bVar10 = param_3 == (undefined4 *)0x2000;
      if ((int)param_3 < 0x2001) {
        bVar11 = SBORROW4((int)puVar6,(int)param_3);
        puVar1 = (undefined4 *)((int)puVar6 - (int)param_3);
        bVar10 = puVar6 == param_3;
      }
      if ((!bVar10 && (int)puVar1 < 0 == bVar11) || (((uint)param_3 & 1) != 0)) {
        ak_print(5,1,"[%s:%d] not support frame length =%d\n","ak_ai_reset_params",0xa35,param_3);
        iVar9 = 0x101;
        goto LAB_00018878;
      }
      if (iVar4 == 1) {
        if (0x1000 < (int)param_3) {
          ak_print(5,1,"[%s:%d] MONO not support frame length =%d\n","ak_ai_reset_params",0xa38,
                   param_3);
          iVar9 = 0x101;
          goto LAB_00018878;
        }
      }
      else if ((iVar4 == 2) && (((uint)param_3 & 3) != 0)) {
        ak_print(5,1,"[%s:%d] STEREO not support frame length =%d\n","ak_ai_reset_params",0xa3b,
                 param_3);
        iVar9 = 0x101;
        goto LAB_00018878;
      }
      if (param_3 != *(undefined4 **)(iVar2 + 0x1c)) {
        uVar7 = (*(uint *)(iVar2 + 0x134) >> 3) * iVar4 * iVar9;
        if (uVar7 == 0) {
          uVar7 = 16000;
        }
        *(undefined4 **)(iVar2 + 0x1c) = param_3;
        FUN_000192ac((int)param_3 * 1000,uVar7);
        iVar9 = 0;
        *(undefined4 *)(iVar2 + 0x18) = extraout_r0;
        ak_set_debug_num_info(5,1,"frame_size",param_3);
        ak_set_debug_num_info(5,1,"frame_interval",*(undefined4 *)(iVar2 + 0x18));
        ak_print(5,3,"[%s:%d] frame_length reset to %d\n","ak_ai_reset_params",0xa44,param_3);
        goto LAB_00018878;
      }
    }
    iVar9 = 0;
  }
  else {
    ak_print(5,1,"[%s:%d] capture start has begin, please use ak_ai_stop_capture first\n",
             "ak_ai_reset_params",0xa22);
    iVar9 = 0x5000006;
  }
LAB_00018878:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  return iVar9;
}



int ak_ai_set_aec_dump_file_info(uint param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00013bd8(param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00013558(param_1);
    }
    if (iVar1 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_set_aec_dump_file_info",0xa5e);
      iVar1 = 0x5000004;
    }
    else {
      if (*(int *)(iVar1 + 0x20) == 0) {
        uVar2 = *param_2;
        *(uint *)(iVar1 + 0x48) = uVar2;
      }
      else {
        ak_vqe_inner_set_dump_info(0,param_2);
        uVar2 = *param_2;
      }
      iVar1 = ak_vqe_inner_enable_dump(0,uVar2);
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  return iVar1;
}



int ak_ai_get_vad_status_ex(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_0002c04c);
    if (param_1 < 4) {
      iVar2 = *(int *)(&DAT_0002c03c + param_1 * 4);
    }
    else {
      iVar2 = FUN_00013558(param_1);
    }
    if (iVar2 == 0) {
      ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_vad_status_ex",0xa7e);
      iVar1 = 0x5000004;
    }
    else {
      iVar1 = FUN_00013630(6,*(int *)(iVar2 + 0x130),(int *)(iVar2 + 0x13c));
      if (iVar1 == 0) {
        if (*(int *)(iVar2 + 0x20) == 0) {
          ak_print(5,1,"[%s:%d] capture no start\n","ak_ai_get_vad_status_ex",0xa8c);
          iVar1 = 0x5000007;
        }
        else {
          iVar2 = ak_vqe_inner_get_ai_vad_status(0,param_2);
          if (iVar2 != 0) {
            ak_print(5,1,"[%s:%d] ak_vqe_inner_get_ai_vad_status FAILED\n","ak_ai_get_vad_status_ex"
                     ,0xa87);
            iVar1 = 0x5000017;
          }
        }
      }
    }
    ak_thread_rwlock_unlock(DAT_0002c04c);
    return iVar1;
  }
  ak_print(5,1,"[%s:%d] vad_status is NULL\n","ak_ai_get_vad_status_ex",0xa76);
  return 0x100;
}



void ak_ai_get_vad_status(uint param_1,undefined4 *param_2)

{
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  ak_ai_get_vad_status_ex(param_1,(int)&local_38);
  *param_2 = local_38;
  param_2[2] = local_30;
  param_2[3] = local_2c;
  return;
}



int ak_ai_get_source_frame(uint param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar1 = FUN_000135a0(param_2);
  if (iVar1 != 0) {
    return iVar1;
  }
  ak_print(5,5,"[%s:%d] entry....\n","ak_ai_get_source_frame",0xaa6);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_get_source_frame",0xaaa);
    iVar8 = 0x5000004;
  }
  else {
    *(undefined4 *)(iVar1 + 0x154) = 1;
    if (*(int *)(iVar1 + 0x20) == 0) {
      ak_print(5,1,"[%s:%d] capture not start,please call ak_ai_start_capture first \n",
               "ak_ai_get_source_frame",0xaaf);
      iVar8 = 0x5000007;
    }
    else {
      iVar8 = 0;
      if (param_3 == 0) {
        ak_thread_mutex_lock(iVar1 + 0x158);
        piVar6 = *(int **)(iVar1 + 0x148);
        if ((piVar6 == (int *)(iVar1 + 0x148)) || (piVar6 == (int *)0x18)) {
          iVar8 = 0x5000011;
        }
        else {
          iVar5 = piVar6[-5];
          uVar2 = piVar6[-4];
          uVar3 = piVar6[-3];
          *param_2 = piVar6[-6];
          param_2[1] = iVar5;
          uVar9 = FUN_00019374(uVar2,uVar3,1000,0);
          param_2[4] = piVar6[-2];
          *(undefined8 *)(param_2 + 2) = uVar9;
        }
        ak_thread_mutex_unlock(iVar1 + 0x158);
      }
      else {
        iVar7 = iVar1 + 0x158;
        iVar5 = 0x20;
        while( true ) {
          ak_thread_mutex_lock(iVar7);
          iVar4 = *(int *)(iVar1 + 0x148);
          if ((iVar1 + 0x148 != iVar4) && ((int *)(iVar4 + -0x18) != (int *)0x0)) {
            iVar1 = *(int *)(iVar4 + -0x14);
            *param_2 = *(int *)(iVar4 + -0x18);
            param_2[1] = iVar1;
            uVar9 = FUN_00019374(*(uint *)(iVar4 + -0x10),*(uint *)(iVar4 + -0xc),1000,0);
            param_2[4] = *(int *)(iVar4 + -8);
            *(undefined8 *)(param_2 + 2) = uVar9;
            ak_thread_mutex_unlock(iVar7);
            goto LAB_00018e70;
          }
          iVar5 = iVar5 + -1;
          if (iVar5 == 0) break;
          ak_thread_mutex_unlock(iVar7);
          ak_sleep_ms(10);
        }
        ak_print(5,1,"[%s:%d] get no data \n","ak_ai_get_source_frame",0xac6);
        ak_thread_mutex_unlock(iVar7);
        iVar8 = 0x5000011;
      }
    }
  }
LAB_00018e70:
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaving....\n","ak_ai_get_source_frame",0xadb);
  return iVar8;
}



int ak_ai_release_source_frame(uint param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  ak_print(5,5,"[%s:%d] entrying... \n","ak_ai_release_source_frame",0xaea);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar5 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar5 = FUN_00013558(param_1);
  }
  if (iVar5 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_release_source_frame",0xaec);
    iVar1 = 0x5000004;
  }
  else {
    iVar1 = FUN_00012e9c(param_2);
    if (iVar1 == 0) {
      ak_print(5,5,"[%s:%d] entry....\n","src_frame_list_del_member",0x19d);
      ak_thread_mutex_lock(iVar5 + 0x158);
      piVar3 = *(int **)(iVar5 + 0x148);
      piVar4 = (int *)*piVar3;
      while (piVar2 = piVar4, piVar3 != (int *)(iVar5 + 0x148)) {
        piVar4 = piVar3 + -6;
        if (((piVar4 != (int *)0x0) && (*param_2 == *piVar4)) && (param_2[1] == piVar3[-5])) {
          piVar2 = (int *)piVar3[1];
          iVar6 = *piVar3;
          *(int **)(iVar6 + 4) = piVar2;
          *piVar2 = iVar6;
          *piVar3 = (int)piVar3;
          piVar3[1] = (int)piVar3;
          ak_mem_free();
          *piVar4 = 0;
          ak_mem_free(piVar4);
          if (*(int *)(iVar5 + 0x150) != 0) {
            *(int *)(iVar5 + 0x150) = *(int *)(iVar5 + 0x150) + -1;
          }
          break;
        }
        piVar4 = (int *)*piVar2;
        piVar3 = piVar2;
      }
      ak_thread_mutex_unlock(iVar5 + 0x158);
      *param_2 = 0;
      param_2[1] = 0;
      param_2[4] = 0;
      param_2[2] = 0;
      param_2[3] = 0;
    }
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaving... \n","ak_ai_release_source_frame",0xafb);
  return iVar1;
}



undefined4 ak_ai_reset_source_frame_list(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_print(5,5,"[%s:%d] entrying... \n","ak_ai_reset_source_frame_list",0xb09);
  ak_thread_rwlock_rdlock(DAT_0002c04c);
  if (param_1 < 4) {
    iVar1 = *(int *)(&DAT_0002c03c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00013558(param_1);
  }
  if (iVar1 == 0) {
    ak_print(5,1,"[%s:%d] dev is NULL!\n","ak_ai_reset_source_frame_list",0xb0b);
    uVar2 = 0x5000004;
  }
  else {
    uVar2 = 0;
    *(undefined4 *)(iVar1 + 0x154) = 0;
    FUN_00012fec(iVar1);
  }
  ak_thread_rwlock_unlock(DAT_0002c04c);
  ak_print(5,5,"[%s:%d] leaving... \n","ak_ai_reset_source_frame_list",0xb13);
  return uVar2;
}



ulonglong FUN_000192ac(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  if (param_2 - 1 == 0) {
    return CONCAT44(param_2,param_1);
  }
  if (param_2 == 0) {
    uVar1 = raise(8);
    return (ulonglong)uVar1;
  }
  if (param_1 <= param_2) {
    return CONCAT44(param_2,(uint)(param_1 == param_2));
  }
  if ((param_2 & param_2 - 1) == 0) {
    return CONCAT44(param_2,param_1 >> (0x1fU - LZCOUNT(param_2) & 0xff));
  }
  uVar2 = param_2 << (LZCOUNT(param_2) - LZCOUNT(param_1) & 0xffU);
  uVar1 = 1 << (LZCOUNT(param_2) - LZCOUNT(param_1) & 0xffU);
  uVar3 = 0;
  while( true ) {
    if (uVar2 <= param_1) {
      param_1 = param_1 - uVar2;
      uVar3 = uVar3 | uVar1;
    }
    if (uVar2 >> 1 <= param_1) {
      param_1 = param_1 - (uVar2 >> 1);
      uVar3 = uVar3 | uVar1 >> 1;
    }
    if (uVar2 >> 2 <= param_1) {
      param_1 = param_1 - (uVar2 >> 2);
      uVar3 = uVar3 | uVar1 >> 2;
    }
    if (uVar2 >> 3 <= param_1) {
      param_1 = param_1 - (uVar2 >> 3);
      uVar3 = uVar3 | uVar1 >> 3;
    }
    bVar4 = param_1 == 0;
    if (!bVar4) {
      uVar1 = uVar1 >> 4;
      bVar4 = uVar1 == 0;
    }
    if (bVar4) break;
    uVar2 = uVar2 >> 4;
  }
  return CONCAT44(uVar2,uVar3);
}



void FUN_00019374(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint local_8;
  
  if (param_4 != 0 || param_3 != 0) {
    FUN_000193fc(param_1,param_2,param_3,param_4,(int *)&local_8);
    return;
  }
  if (param_2 != 0 || param_1 != 0) {
    param_2 = 0xffffffff;
  }
  local_8 = param_2;
  raise(8);
  return;
}



void FUN_000193c0(uint param_1,uint param_2,uint param_3,uint param_4,int *param_5)

{
  uint uVar1;
  longlong lVar2;
  
  lVar2 = FUN_00019438(param_1,param_2,param_3,param_4);
  lVar2 = lVar2 * CONCAT44(param_4,param_3);
  uVar1 = (uint)lVar2;
  *param_5 = param_1 - uVar1;
  param_5[1] = param_2 - ((int)((ulonglong)lVar2 >> 0x20) + (uint)(param_1 < uVar1));
  return;
}



void FUN_000193fc(uint param_1,uint param_2,uint param_3,uint param_4,int *param_5)

{
  uint uVar1;
  longlong lVar2;
  
  lVar2 = FUN_00019594(param_1,param_2,param_3,param_4);
  lVar2 = lVar2 * CONCAT44(param_4,param_3);
  uVar1 = (uint)lVar2;
  *param_5 = param_1 - uVar1;
  param_5[1] = param_2 - ((int)((ulonglong)lVar2 >> 0x20) + (uint)(param_1 < uVar1));
  return;
}



longlong FUN_00019438(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  undefined8 uVar12;
  longlong lVar13;
  
  if ((int)param_2 < 0) {
    bVar11 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(param_2 + bVar11);
    uVar8 = 0xffffffff;
  }
  else {
    uVar8 = 0;
  }
  if ((int)param_4 < 0) {
    bVar11 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(param_4 + bVar11);
    uVar8 = ~uVar8;
  }
  bVar11 = param_2 <= param_4;
  bVar9 = param_4 != param_2;
  if (!bVar9) {
    bVar11 = param_1 <= param_3;
  }
  bVar10 = param_3 != param_1;
  if (bVar11 && (bVar9 || bVar10)) {
    param_3 = 0;
    param_4 = 0;
  }
  lVar13 = CONCAT44(param_4,param_3);
  if (!bVar11 || !bVar9 && !bVar10) {
    if (param_4 == 0) {
      iVar5 = LZCOUNT(param_3) + 0x20;
    }
    else {
      iVar5 = LZCOUNT(param_4);
    }
    if (param_2 == 0) {
      iVar2 = LZCOUNT(param_1) + 0x20;
    }
    else {
      iVar2 = LZCOUNT(param_2);
    }
    uVar6 = iVar5 - iVar2;
    uVar12 = FUN_000196b4(param_3,param_4,uVar6);
    uVar4 = (uint)((ulonglong)uVar12 >> 0x20);
    uVar1 = (uint)uVar12;
    bVar11 = uVar4 <= param_2;
    if (param_2 == uVar4) {
      bVar11 = uVar1 <= param_1;
    }
    if (bVar11) {
      bVar11 = param_1 < uVar1;
      param_1 = param_1 - uVar1;
      param_2 = param_2 - (uVar4 + bVar11);
      lVar13 = FUN_000196b4(1,0,uVar6);
    }
    else {
      lVar13 = 0;
    }
    if (uVar6 != 0) {
      uVar4 = uVar4 >> 1;
      uVar1 = (uint)((byte)((ulonglong)uVar12 >> 0x20) & 1) << 0x1f | uVar1 >> 1;
      uVar7 = uVar6;
      do {
        bVar11 = uVar4 <= param_2;
        if (param_2 == uVar4) {
          bVar11 = uVar1 <= param_1;
        }
        if (bVar11) {
          bVar11 = param_1 < uVar1;
          uVar3 = param_1 - uVar1;
          param_1 = uVar3 * 2 + 1;
          param_2 = (param_2 - (uVar4 + bVar11)) * 2 + (uint)CARRY4(uVar3,uVar3) +
                    (uint)(0xfffffffe < uVar3 * 2);
        }
        else {
          bVar11 = CARRY4(param_1,param_1);
          param_1 = param_1 * 2;
          param_2 = param_2 * 2 + (uint)bVar11;
        }
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
      lVar13 = lVar13 + CONCAT44(param_2,param_1);
      uVar4 = (uint)lVar13;
      uVar12 = FUN_00019698(param_1,param_2,uVar6);
      uVar12 = FUN_000196b4((uint)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar6);
      lVar13 = CONCAT44((int)((ulonglong)lVar13 >> 0x20) -
                        ((int)((ulonglong)uVar12 >> 0x20) + (uint)(uVar4 < (uint)uVar12)),
                        uVar4 - (uint)uVar12);
    }
  }
  if (uVar8 == 0) {
    return lVar13;
  }
  return CONCAT44(-((int)((ulonglong)lVar13 >> 0x20) + (uint)((int)lVar13 != 0)),-(int)lVar13);
}



longlong FUN_00019594(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  undefined8 uVar9;
  longlong lVar10;
  
  bVar8 = param_2 <= param_4;
  if (param_4 == param_2) {
    bVar8 = param_1 <= param_3;
  }
  if (bVar8 && (param_4 != param_2 || param_3 != param_1)) {
    return 0;
  }
  if (param_4 == 0) {
    iVar4 = LZCOUNT(param_3) + 0x20;
  }
  else {
    iVar4 = LZCOUNT(param_4);
  }
  if (param_2 == 0) {
    iVar2 = LZCOUNT(param_1) + 0x20;
  }
  else {
    iVar2 = LZCOUNT(param_2);
  }
  uVar5 = iVar4 - iVar2;
  uVar9 = FUN_000196b4(param_3,param_4,uVar5);
  uVar7 = (uint)((ulonglong)uVar9 >> 0x20);
  uVar1 = (uint)uVar9;
  bVar8 = uVar7 <= param_2;
  if (param_2 == uVar7) {
    bVar8 = uVar1 <= param_1;
  }
  if (bVar8) {
    bVar8 = param_1 < uVar1;
    param_1 = param_1 - uVar1;
    param_2 = param_2 - (uVar7 + bVar8);
    lVar10 = FUN_000196b4(1,0,uVar5);
  }
  else {
    lVar10 = 0;
  }
  if (uVar5 == 0) {
    return lVar10;
  }
  uVar7 = uVar7 >> 1;
  uVar1 = (uint)((byte)((ulonglong)uVar9 >> 0x20) & 1) << 0x1f | uVar1 >> 1;
  uVar6 = uVar5;
  do {
    bVar8 = uVar7 <= param_2;
    if (param_2 == uVar7) {
      bVar8 = uVar1 <= param_1;
    }
    if (bVar8) {
      bVar8 = param_1 < uVar1;
      uVar3 = param_1 - uVar1;
      param_1 = uVar3 * 2 + 1;
      param_2 = (param_2 - (uVar7 + bVar8)) * 2 + (uint)CARRY4(uVar3,uVar3) +
                (uint)(0xfffffffe < uVar3 * 2);
    }
    else {
      bVar8 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      param_2 = param_2 * 2 + (uint)bVar8;
    }
    uVar6 = uVar6 - 1;
  } while (uVar6 != 0);
  lVar10 = lVar10 + CONCAT44(param_2,param_1);
  uVar7 = (uint)lVar10;
  uVar9 = FUN_00019698(param_1,param_2,uVar5);
  uVar9 = FUN_000196b4((uint)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar5);
  return CONCAT44((int)((ulonglong)lVar10 >> 0x20) -
                  ((int)((ulonglong)uVar9 >> 0x20) + (uint)(uVar7 < (uint)uVar9)),
                  uVar7 - (uint)uVar9);
}



undefined8 FUN_00019698(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  if ((int)(param_3 - 0x20) < 0) {
    uVar1 = param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = param_2 >> (param_3 - 0x20 & 0xff);
  }
  return CONCAT44(param_2 >> (param_3 & 0xff),uVar1);
}



undefined8 FUN_000196b4(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  if ((int)(param_3 - 0x20) < 0) {
    uVar1 = param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = param_1 << (param_3 - 0x20 & 0xff);
  }
  return CONCAT44(uVar1,param_1 << (param_3 & 0xff));
}



void _fini(void)

{
  return;
}


