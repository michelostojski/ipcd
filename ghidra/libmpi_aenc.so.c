typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
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

typedef void *__gnuc_va_list;

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



undefined1 __bss_start__;
undefined4 DAT_00026034;
dword DWORD_00015364;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_00026054;
undefined FUN_00011d1c;
undefined LAB_00011d5c;
undefined aenc_decoder_alloc;
undefined ak_mem_free;
undefined4 DAT_00026038;
undefined4 DAT_0002603c;
char *DAT_0002604c;
undefined ak_thread_mutex_lock;
undefined ak_mem_rb_write;
int DAT_0002604c;

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



// WARNING: Unknown calling convention -- yet parameter storage is locked

int raise(int __sig)

{
  int iVar1;
  
  iVar1 = raise(__sig);
  return iVar1;
}



// WARNING: Removing unreachable block (ram,0x000116f4)
// WARNING: Removing unreachable block (ram,0x0001170c)
// WARNING: Removing unreachable block (ram,0x00011714)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_00026034);
    entry();
    if (ppuVar1[8] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_00015364);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00011758)
// WARNING: Removing unreachable block (ram,0x00011770)
// WARNING: Removing unreachable block (ram,0x00011778)
// WARNING: Removing unreachable block (ram,0x00011860)
// WARNING: Removing unreachable block (ram,0x00011874)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_00015364,&DAT_00026054,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



void * aenc_decoder_alloc(size_t param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  void *__s;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0xf,param_1,"aenc_decoder_alloc",uVar1,param_4);
  if (__s != (void *)0x0) {
    memset(__s,0,param_1);
  }
  return __s;
}



int * FUN_000118f4(int param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  int *__s;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x28);
  if (iVar2 == 3) {
    uVar3 = (*(uint *)(param_1 + 0x20) >> 3) *
            *(int *)(param_1 + 0x24) * *(int *)(param_1 + 0x1c) * 0x14;
    param_3 = uVar3 * 0x10624dd3;
    uVar3 = uVar3 / 1000;
  }
  else if (iVar2 == 4) {
    uVar3 = *(int *)(param_1 + 0x24) * 0x400 * (*(uint *)(param_1 + 0x20) >> 3);
  }
  else {
    uVar3 = param_2;
    if (iVar2 == 2) {
      param_3 = *(uint *)(param_1 + 0x1c);
      if (param_3 < 0x5dc1) {
        if (*(uint *)(param_1 + 0x24) < 2) {
          uVar3 = 0x480;
        }
        else {
          uVar3 = 0x900;
        }
      }
      else if (*(uint *)(param_1 + 0x24) < 2) {
        uVar3 = 0x900;
      }
      else {
        uVar3 = 0x1200;
      }
      goto LAB_00011924;
    }
  }
  if ((int)uVar3 < 1) {
    ak_print(0xf,1,"[%s:%d] calcuate frame length = 0\n","malloc_aenc_entry",0x1b9);
    return (int *)0x0;
  }
LAB_00011924:
  uVar1 = ak_get_os_timestamp(param_1,param_2,param_3);
  __s = (int *)ak_mem_alloc_(0xf,0x20,"malloc_aenc_entry",uVar1);
  if (__s != (int *)0x0) {
    memset(__s,0,0x20);
    uVar1 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0xf,uVar3,"malloc_aenc_entry",uVar1);
    *__s = iVar2;
    if (iVar2 == 0) {
      ak_print(0xf,1,"[%s:%d] calloc %d failed\n","malloc_aenc_entry",0x1c3,uVar3);
      ak_mem_free(__s);
      __s = (int *)0x0;
    }
    else {
      __s[1] = uVar3;
    }
    return __s;
  }
  ak_print(0xf,1,"[%s:%d] malloc struct aenc_entry failed\n","malloc_aenc_entry",0x1ca);
  return (int *)0x0;
}



undefined4 FUN_00011ad4(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_194 [36];
  char *local_170;
  undefined4 local_16c;
  code *local_168;
  code *local_164;
  undefined1 *local_160;
  code *local_15c;
  uint local_150;
  undefined2 local_14c;
  undefined2 local_14a;
  uint local_148;
  undefined4 local_144;
  undefined4 local_138;
  uint3 local_134;
  undefined1 uStack_131;
  undefined4 local_1c;
  
  memset(&local_170,0,0x158);
  if (param_1[3] - 1 < 0x15) {
    local_148 = *param_1;
    local_14c = (undefined2)param_1[2];
    local_168 = aenc_decoder_alloc;
    local_164 = ak_mem_free;
    local_160 = &LAB_00011d5c;
    local_15c = FUN_00011d1c;
    local_14a = 0x10;
    iVar1 = ak_get_chip_id();
    local_150 = param_1[3];
    local_170 = "AudioCodec Version V1.21.12";
    if (iVar1 == 0x20160101) {
      local_16c = 0xe;
    }
    else {
      local_16c = 0x10;
    }
    switch(local_150) {
    case 2:
      local_144 = 0;
      if (47999 < local_148) {
        local_144 = 0xc0;
      }
      local_1c = _SD_MP3_Encode_login(0);
      local_138 = 1;
      break;
    case 3:
      _local_134 = 7;
      local_1c = _SD_AMR_Encode_login(0);
      local_138 = 4;
      break;
    case 4:
      local_134 = (uint3)(ushort)local_134;
      local_1c = _SD_AAC_Encode_login(0);
      local_138 = 4;
      break;
    case 0x11:
    case 0x12:
      local_1c = _SD_G711_Encode_login(0);
    }
    ak_set_debug_num_info(0xf,1,"aenc_sample_rate",local_148);
    ak_set_debug_num_info(0xf,1,"aenc_channel_num",local_14c);
    memset(auStack_194,0,0x24);
    uVar2 = _SD_Encode_Open(&local_170,auStack_194);
  }
  else {
    ak_print(0xf,1,"[%s:%d] Unknow encode type!\n","init_encode_input",0x151);
    uVar2 = 0;
  }
  return uVar2;
}



undefined4 FUN_00011d1c(undefined4 param_1)

{
  ak_print(0xf,5,"delay 0x%lx ticks",param_1);
  ak_sleep_ms(param_1);
  return 1;
}



undefined4 FUN_00011ddc(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x38) == -1) {
    uVar1 = 0;
  }
  else {
    iVar2 = ak_mem_rb_destroy();
    uVar1 = 0;
    if (iVar2 != 0) {
      ak_print(0xf,1,"[%s:%d] ak_rb_reset failed\n","destroy_buf",0x413);
      uVar1 = 0x1000000a;
    }
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    uVar1 = ak_mem_free(*(int *)(param_1 + 0x30));
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return uVar1;
}



void FUN_00011e7c(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  ak_thread_mutex_lock(param_1 + 4);
  piVar4 = *(int **)(param_1 + 0x40);
  piVar5 = (int *)*piVar4;
  while (piVar1 = piVar5, (int *)(param_1 + 0x40) != piVar4) {
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
  *(undefined4 *)(param_1 + 0x34) = 0;
  ak_thread_mutex_unlock(param_1 + 4);
  return;
}



void FUN_00011f54(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  if ((FILE *)*param_1 == (FILE *)0x0) {
    return;
  }
  fclose((FILE *)*param_1);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return;
}



undefined4 FUN_00011f94(int param_1,char *param_2,char *param_3)

{
  size_t sVar1;
  FILE *pFVar2;
  undefined4 uVar3;
  char *param0;
  char acStack_45c [12];
  char acStack_450 [532];
  char acStack_23c [536];
  
  sVar1 = strlen(param_2);
  if (0xfe < sVar1 - 1) {
    ak_print(0xf,1,"[%s:%d] file_path length = %d ,0< path_size < %d \n","open_aenc_save_file",0x101
             ,sVar1,0x100);
    return 0x101;
  }
  sVar1 = strlen(param_3);
  if (sVar1 - 1 < 0xff) {
    param0 = acStack_450;
    memset(param0,0,0x214);
    memset(acStack_23c,0,0x214);
    sprintf(param0,"%s%s%s",param_2,param_3,"_input.pcm");
    ak_print(0xf,3,"[%s:%d] input_full_name =%s\n","open_aenc_save_file",0x114,param0);
    memset(acStack_45c,0,10);
    switch(*(undefined4 *)(param_1 + 0x28)) {
    case 2:
      strncpy(acStack_45c,".mp3",5);
      break;
    case 3:
      strncpy(acStack_45c,".amr",5);
      break;
    case 4:
      strncpy(acStack_45c,".aac",5);
      break;
    case 6:
      strncpy(acStack_45c,".pcm",5);
      break;
    case 0x11:
      strncpy(acStack_45c,".g711a",7);
      break;
    case 0x12:
      strncpy(acStack_45c,".g711u",7);
    }
    sprintf(acStack_23c,"%s%s_output_%s",param_2,param_3,acStack_45c);
    ak_print(0xf,3,"[%s:%d] output_full_name =%s\n","open_aenc_save_file",0x11b,acStack_23c);
    pFVar2 = fopen(param0,"w+");
    *(FILE **)(param_1 + 0x58) = pFVar2;
    if (pFVar2 == (FILE *)0x0) {
      uVar3 = 0x121;
    }
    else {
      pFVar2 = fopen(acStack_23c,"w+");
      *(FILE **)(param_1 + 0x68) = pFVar2;
      if (pFVar2 != (FILE *)0x0) {
        return 0;
      }
      param0 = acStack_23c;
      uVar3 = 0x128;
    }
    ak_print(0xf,1,"[%s:%d] open %s error\n","open_aenc_save_file",uVar3,param0);
    FUN_00011f54((undefined4 *)(param_1 + 0x58));
    FUN_00011f54((undefined4 *)(param_1 + 0x68));
  }
  else {
    ak_print(0xf,1,"[%s:%d] file_name length = %d ,0< name_size < %d\n","open_aenc_save_file",0x108,
             sVar1,0x100);
  }
  return 0x101;
}



undefined4 FUN_000122d0(void)

{
  ak_print(0xf,1,"[%s:%d] handle_id invalid \n","get_aenc_user_handle",0x429);
  return 0;
}



undefined4 FUN_00012314(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 != (int *)0x0) {
    if ((*param_1 == 0) || (iVar1 = _SD_Encode_Close(), iVar1 != 0)) {
      uVar2 = 0;
    }
    else {
      ak_print(0xf,1,"[%s:%d] close SdCodec failed\n","frame_mode_destroy",0x3af);
      uVar2 = 0x10000001;
    }
    *param_1 = 0;
    FUN_00011e7c((int)param_1);
    ak_thread_mutex_destroy(param_1 + 1);
    return uVar2;
  }
  ak_print(0xf,1,"[%s:%d] encode handle is NULL\n","frame_mode_destroy",0x3a7);
  return 0x100;
}



void FUN_000123e0(undefined4 *param_1,uint param_2,int *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,int param_8)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  int local_24;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  piVar1 = FUN_000118f4((int)param_1,param_2,(uint)param_3);
  if (piVar1 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] malloc_aenc_entry error \n","encode_one_frame",0x203);
    return;
  }
  local_2c = *piVar1;
  local_24 = piVar1[1];
  uVar2 = *param_1;
  piVar1[4] = *param_3;
  local_28 = param_5;
  piVar1[2] = param_7;
  piVar1[3] = param_8;
  local_30 = param_4;
  iVar3 = _SD_Encode(uVar2,&local_30);
  iVar5 = param_1[0x12];
  piVar1[1] = iVar3;
  param_1[0x12] = iVar5 + 1;
  if (0 < iVar3) {
    ak_thread_mutex_lock(param_1 + 1);
    iVar3 = param_1[0xd];
    puVar4 = (undefined4 *)param_1[0x11];
    param_1[0x11] = piVar1 + 6;
    piVar1[7] = (int)puVar4;
    piVar1[6] = (int)(param_1 + 0x10);
    *puVar4 = piVar1 + 6;
    param_1[0xd] = iVar3 + 1;
    ak_thread_mutex_unlock(param_1 + 1);
    param_1[0x13] = param_1[0x13] + 1;
    return;
  }
  if (*piVar1 != 0) {
    ak_mem_free();
  }
  ak_mem_free(piVar1);
  return;
}



void ak_aenc_print_codec_info(void)

{
  undefined4 uVar1;
  
  uVar1 = _SD_GetAudioCodecVersionInfo();
  ak_print(0xf,4,"[%s:%d] AudioCodec version: %s\n","ak_aenc_print_codec_info",0x435,uVar1);
  return;
}



char * ak_aenc_get_version(void)

{
  return "libmpi_aenc V1.2.02";
}



undefined4 ak_aenc_open(uint *param_1,int *param_2)

{
  uint uVar1;
  int *__s;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 uVar5;
  char *pcVar6;
  
  pcVar6 = "libmpi_aenc V1.2.02";
  ak_print(0xf,4,"[%s:%d] aenc version: %s\n","ak_aenc_open",1099,"libmpi_aenc V1.2.02");
  if (param_1 == (uint *)0x0) {
    ak_print(0xf,1,"[%s:%d] invalid audio encode param\n","check_aenc_open_param",0x2f0,pcVar6);
    return 0x100;
  }
  uVar1 = param_1[3];
  if (uVar1 == 3) {
    uVar3 = param_1[2];
    if (uVar3 == 2) {
      ak_print(0xf,1,"[%s:%d] amr encode not suppprt stereo\n","check_aenc_open_param",0x2f7,pcVar6)
      ;
      return 0x101;
    }
    if (*param_1 != 8000) {
      ak_print(0xf,1,"[%s:%d] amr encode sample rate != 8000, not support\n","check_aenc_open_param"
               ,0x2fd,pcVar6);
      return 0x101;
    }
  }
  else {
    if (uVar1 == 0x11) {
      if (param_1[2] == 2) {
        ak_print(0xf,1,"[%s:%d] g711a encode not suppprt stereo\n","check_aenc_open_param",0x304,
                 pcVar6);
        return 0x101;
      }
      uVar3 = *param_1;
      if (uVar3 != 8000 && uVar3 != 16000) {
        ak_print(0xf,1,"[%s:%d] 711a encode sample rate != 8000 or 16000, not support\n",
                 "check_aenc_open_param",0x30b,pcVar6);
        return 0x101;
      }
    }
    else if (uVar1 == 0x12) {
      if (param_1[2] == 2) {
        ak_print(0xf,1,"[%s:%d] g711u encode not suppprt stereo\n","check_aenc_open_param",0x312,
                 pcVar6);
        return 0x101;
      }
      uVar3 = *param_1;
      if (uVar3 != 8000 && uVar3 != 16000) {
        ak_print(0xf,1,"[%s:%d] 711u encode sample rate != 8000 or 16000, not support\n",
                 "check_aenc_open_param",0x319,pcVar6);
        return 0x101;
      }
    }
    else {
      uVar3 = *param_1;
    }
    if (((((uVar3 != 8000 && uVar3 != 12000) && (uVar3 != 0x2b11 && uVar3 != 16000)) &&
         (uVar3 != 0x5622 && uVar3 != 24000)) &&
        ((uVar3 != 32000 && uVar3 != 0xac44 && (uVar3 != 48000 && uVar3 != 96000)))) ||
       (48000 < uVar3)) {
      ak_print(0xf,1,"[%s:%d] sample rate not suppprt %d \n","check_aenc_open_param",800,uVar3);
      return 0x101;
    }
    uVar3 = param_1[2];
  }
  if (1 < uVar3 - 1) {
    ak_print(0xf,1,"[%s:%d] channel number not suppprt %d \n","check_aenc_open_param",0x326,uVar3);
    return 0x101;
  }
  if (param_1[1] != 0x10) {
    ak_print(0xf,1,"[%s:%d] sample bits not suppprt %d \n","check_aenc_open_param",0x32c,param_1[1])
    ;
    return 0x101;
  }
  if (0x15 < uVar1 - 1) {
    ak_print(0xf,1,"[%s:%d] not support type = %d\n","check_aenc_open_param",0x331,uVar1);
    return 0x10000003;
  }
  if (param_2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] handle_id is NULL\n","check_aenc_open_param",0x336,pcVar6);
    return 0x100;
  }
  ak_thread_rwlock_wrlock(DAT_00026038);
  if (3 < (int)DAT_0002604c) {
    pcVar6 = DAT_0002604c;
    ak_print(0xf,1,"[%s:%d] open count too many, now open count = %d\n","ak_aenc_open",0x457,
             DAT_0002604c);
    uVar5 = 0x10000002;
    goto LAB_000128ac;
  }
  uVar5 = ak_get_os_timestamp();
  __s = (int *)ak_mem_alloc_(0xf,0x78,"ak_aenc_open",uVar5);
  if (__s == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] mollco encode handle failed\n","ak_aenc_open",0x461,pcVar6);
    uVar5 = 0x102;
    goto LAB_000128ac;
  }
  memset(__s,0,0x78);
  memcpy(__s + 7,param_1,0x10);
  __s[0x10] = (int)(__s + 0x10);
  __s[0x11] = (int)(__s + 0x10);
  __s[0xd] = 0;
  ak_thread_mutex_init(__s + 1,0);
  if (__s[10] == 6) {
    *__s = 0;
LAB_00012980:
    if (2 < param_1[3] - 2) {
LAB_00012990:
      piVar4 = &DAT_00026038;
      iVar2 = 0;
      do {
        piVar4 = piVar4 + 1;
        if (*piVar4 == 0) {
          pcVar6 = DAT_0002604c + 1;
          (&DAT_0002603c)[iVar2] = __s;
          DAT_0002604c = pcVar6;
          ak_print(0xf,5,"[%s:%d] open count = %d\n","ak_aenc_open",0x47c,pcVar6);
          *param_2 = iVar2;
          break;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 != 4);
      ak_set_debug_str_info(0xf,1,"aenc_version","libmpi_aenc V1.2.02");
      uVar5 = _SD_GetAudioCodecVersionInfo();
      ak_set_debug_str_info(0xf,1,"AudioCodec version",uVar5);
      ak_set_debug_num_info(0xf,1,"user_count",DAT_0002604c);
      uVar5 = 0;
      goto LAB_000128ac;
    }
    iVar2 = __s[10];
    __s[0xf] = 0;
    __s[0xe] = 0;
    if (iVar2 == 4) {
      uVar1 = __s[9] * 0x400 * ((uint)__s[8] >> 3);
    }
    else if (iVar2 == 2) {
      if ((uint)__s[7] < 0x5dc1) {
        if ((uint)__s[9] < 2) {
          uVar1 = 0x480;
        }
        else {
LAB_00012c14:
          uVar1 = 0x900;
        }
      }
      else {
        if ((uint)__s[9] < 2) goto LAB_00012c14;
        uVar1 = 0x1200;
      }
    }
    else {
      if (iVar2 != 3) {
        ak_print(0xf,2,"[%s:%d] not aac/mp3/amr type, not need to init buffer\n","init_buf",0x3cd);
        goto LAB_00012990;
      }
      uVar1 = (((uint)__s[8] >> 3) * __s[7] * __s[9] * 0x14) / 1000;
    }
    uVar5 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0xf,uVar1,"init_buf",uVar5);
    __s[0xc] = iVar2;
    if (iVar2 == 0) {
      ak_print(0xf,1,"[%s:%d] calloc capture ring buffer failed\n","init_buf",0x3d3);
      uVar5 = 0x102;
    }
    else {
      if (__s[10] == 3) {
        uVar5 = ak_get_os_timestamp();
        iVar2 = 0x4000;
      }
      else {
        uVar5 = ak_get_os_timestamp();
        iVar2 = uVar1 << 3;
      }
      ak_mem_rb_init_(__s + 0xe,0xf,iVar2,"init_buf",uVar5);
      if (__s[0xe] == -1) {
        ak_print(0xf,1,"[%s:%d] calloc capture ring buffer failed\n","init_buf",0x3dd);
        ak_mem_free(__s[0xc]);
        uVar5 = 0x102;
      }
      else {
        iVar2 = ak_mem_rb_reset();
        if (iVar2 == 0) {
          __s[0xb] = uVar1;
          if (__s[10] == 3) {
            __s[0xf] = 0x4000;
          }
          else {
            __s[0xf] = uVar1 << 3;
          }
          goto LAB_00012990;
        }
        ak_print(0xf,1,"[%s:%d] ak_rb_reset failed\n","init_buf",0x3e2);
        ak_mem_free(__s[0xc]);
        __s[0xc] = 0;
        ak_mem_rb_destroy(__s[0xe]);
        __s[0xe] = -1;
        uVar5 = 0x1000000a;
      }
    }
  }
  else {
    iVar2 = FUN_00011ad4((uint *)(__s + 7));
    *__s = iVar2;
    if (iVar2 != 0) goto LAB_00012980;
    ak_print(0xf,1,"[%s:%d] open SdCodec failed\n","frame_mode_init",0x395);
    uVar5 = 0x10000000;
  }
  FUN_00012314(__s);
  FUN_00011ddc((int)__s);
  ak_mem_free(__s);
LAB_000128ac:
  ak_thread_rwlock_unlock(DAT_00026038);
  ak_print(0xf,5,"[%s:%d] exit....\n","ak_aenc_open",0x499,pcVar6);
  return uVar5;
}



undefined4 ak_aenc_get_params(uint param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (void *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00026038);
    if (param_1 < 4) {
      iVar1 = (&DAT_0002603c)[param_1];
    }
    else {
      iVar1 = FUN_000122d0();
    }
    if (iVar1 == 0) {
      ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_get_params",0x4b1);
      uVar2 = 0x10000005;
    }
    else {
      memcpy(param_2,(void *)(iVar1 + 0x1c),0x10);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00026038);
    return uVar2;
  }
  ak_print(0xf,1,"[%s:%d] param is NULL\n","ak_aenc_get_params",0x4a8);
  return 0x100;
}



undefined4 ak_aenc_set_attr(uint param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] aenc attr NULL\n","ak_aenc_set_attr",0x4c7);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00026038);
  if (param_1 < 4) {
    puVar1 = (undefined4 *)(&DAT_0002603c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000122d0();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_set_attr",0x4d0);
    uVar3 = 0x10000005;
    goto LAB_00012fd4;
  }
  if (*param_2 == 1) {
    iVar2 = _SD_Encode_SetFramHeadFlag(*puVar1,0);
    if (iVar2 != 1) {
      ak_print(0xf,1,"[%s:%d] _SD_Encode_SetFramHeadFlag set save head failed\n","ak_aenc_set_attr",
               0x4d8);
      uVar3 = 0x1000000d;
      goto LAB_00012fd4;
    }
  }
  else {
    if (*param_2 != 2) {
      ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_set_attr",0x4e3);
      uVar3 = 0x101;
      goto LAB_00012fd4;
    }
    iVar2 = _SD_Encode_SetFramHeadFlag(*puVar1,1);
    if (iVar2 != 1) {
      ak_print(0xf,1,"[%s:%d] _SD_Encode_SetFramHeadFlag set cut head failed\n","ak_aenc_set_attr",
               0x4de);
      uVar3 = 0x1000000d;
      goto LAB_00012fd4;
    }
  }
  uVar3 = 0;
LAB_00012fd4:
  ak_thread_rwlock_unlock(DAT_00026038);
  return uVar3;
}



undefined4 ak_aenc_send_frame(uint param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *extraout_r2;
  char *pcVar7;
  int iVar8;
  undefined4 *puVar9;
  char *extraout_r2_00;
  char *extraout_r2_01;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  int *piVar13;
  uint uVar14;
  int iVar15;
  bool bVar16;
  ulonglong uVar17;
  ulonglong uVar18;
  uint in_stack_ffffffac;
  uint local_30;
  int local_2c [2];
  
  if (param_2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] frame or stream NULL\n","check_aenc_send_frame_param",0x346);
    return 0x100;
  }
  if (*param_2 == 0) {
    ak_print(0xf,1,"[%s:%d] frame->data is NULL\n","check_aenc_send_frame_param",0x34b);
    return 0x100;
  }
  if (param_2[1] == 0) {
    ak_print(0xf,1,"[%s:%d] frame->len is 0\n","check_aenc_send_frame_param",0x350);
    return 0x101;
  }
  if (1 < param_3) {
    ak_print(0xf,1,"[%s:%d] block must be 0 or 1\n","check_aenc_send_frame_param",0x355);
    return 0x101;
  }
  ak_print(0xf,5,"[%s:%d] entry....\n","ak_aenc_send_frame",0x4fd);
  ak_thread_rwlock_rdlock(DAT_00026038);
  if (param_1 < 4) {
    piVar13 = (int *)(&DAT_0002603c)[param_1];
    pcVar7 = extraout_r2;
  }
  else {
    piVar13 = (int *)FUN_000122d0();
    pcVar7 = extraout_r2_00;
  }
  if (piVar13 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_send_frame",0x502);
    uVar12 = 0x10000005;
    goto LAB_000132e8;
  }
  if ((FILE *)piVar13[0x16] != (FILE *)0x0) {
    if (piVar13[0x18] == 0 && piVar13[0x19] == 0) {
      iVar4 = param_2[3];
      piVar13[0x18] = param_2[2];
      piVar13[0x19] = iVar4;
    }
    fwrite((void *)*param_2,1,param_2[1],(FILE *)piVar13[0x16]);
    uVar14 = piVar13[0x17] >> 0x1f;
    pcVar7 = (char *)(param_2[2] - piVar13[0x18]);
    uVar10 = param_2[3] - (piVar13[0x19] + (uint)((uint)param_2[2] < (uint)piVar13[0x18]));
    bVar16 = uVar14 <= uVar10;
    if (uVar10 == uVar14) {
      bVar16 = (char *)piVar13[0x17] <= pcVar7;
    }
    if (bVar16) {
      FUN_00011f54(piVar13 + 0x16);
      pcVar7 = extraout_r2_01;
    }
  }
  if (param_3 != 0) {
    iVar4 = 0x47;
    do {
      uVar14 = piVar13[0xd];
      pcVar7 = "[%s:%d] user->list_stream_cnt = %d\n";
      if (uVar14 < 0x33) goto LAB_00013230;
      ak_print(0xf,4,"[%s:%d] user->list_stream_cnt = %d\n","ak_aenc_send_frame",0x517);
      ak_sleep_ms(0x1e);
      iVar4 = iVar4 + -1;
      in_stack_ffffffac = uVar14;
    } while (iVar4 != 0);
    uVar12 = 0x10000007;
    goto LAB_000132e8;
  }
  if (0x32 < (uint)piVar13[0xd]) {
    ak_print(0xf,1,"[%s:%d] list count too many, count=%d, please get stream\n","ak_aenc_send_frame"
             ,0x522,piVar13[0xd]);
    uVar12 = 0x10000007;
    goto LAB_000132e8;
  }
LAB_00013230:
  uVar14 = piVar13[10];
  if (uVar14 < 2) {
LAB_0001355c:
    if (*piVar13 != 0) {
      FUN_000123e0(piVar13,param_2[1],param_2 + 4,*param_2,param_2[1],in_stack_ffffffac,param_2[2],
                   param_2[3]);
    }
  }
  else if (uVar14 < 5) {
    if (*piVar13 != 0) {
      local_2c[0] = 0;
      local_30 = 0;
      uVar14 = param_2[2];
      uVar10 = param_2[3];
      iVar4 = ak_mem_rb_get_data_size(piVar13[0xe],local_2c);
      if (iVar4 == 0) {
        uVar6 = ((uint)piVar13[8] >> 3) * piVar13[9] * piVar13[7];
        if (uVar6 == 0) {
          uVar6 = 16000;
        }
        uVar17 = FUN_000144d0(local_2c[0] * 1000,uVar6);
        uVar3 = (uint)uVar17;
        uVar1 = (int)uVar3 >> 0x1f;
        bVar16 = uVar1 <= uVar10;
        if (uVar10 == uVar1) {
          bVar16 = uVar3 <= uVar14;
        }
        if (bVar16) {
          uVar6 = uVar14 - uVar3;
          iVar4 = uVar10 - (uVar1 + (uVar14 < uVar3));
        }
        else {
          ak_print(0xf,1,"[%s:%d] interval > frame_ts , interval=%d, frame_ts =%lld\n",
                   "get_stream_ts",0x26b,uVar3,uVar14,uVar10);
          uVar6 = 0;
          iVar4 = 0;
          in_stack_ffffffac = uVar3;
        }
      }
      else {
        ak_print(0xf,1,"[%s:%d] ak_mem_rb_write error\n","get_stream_ts",0x263);
        uVar6 = 0;
        iVar4 = 0;
      }
      iVar5 = ak_mem_rb_write(piVar13[0xe],*param_2,param_2[1],ak_mem_rb_write);
      if (iVar5 != 0) {
        ak_print(0xf,1,"[%s:%d] ak_mem_rb_write error\n","aenc_encode_frame",0x28b);
      }
      ak_mem_rb_get_data_size(piVar13[0xe],&local_30);
      uVar10 = piVar13[0xb];
      uVar17 = FUN_00014408(local_30,uVar10);
      iVar5 = 0;
      local_2c[0] = 0;
      uVar14 = ((uint)piVar13[8] >> 3) * piVar13[9] * piVar13[7];
      if (uVar14 == 0) {
        uVar14 = 16000;
      }
      uVar18 = FUN_000144d0(uVar10 * 1000,uVar14);
      uVar14 = (uint)uVar18;
      if (0 < (int)uVar17) {
        while( true ) {
          ak_mem_rb_read(piVar13[0xe],0,piVar13[0xc],uVar10,local_2c);
          bVar16 = CARRY4(uVar14,uVar6);
          iVar5 = iVar5 + 1;
          FUN_000123e0(piVar13,param_2[1],param_2 + 4,piVar13[0xc],piVar13[0xb],in_stack_ffffffac,
                       uVar6,iVar4);
          if ((int)uVar17 == iVar5) break;
          uVar10 = piVar13[0xb];
          uVar6 = uVar14 + uVar6;
          iVar4 = ((int)uVar14 >> 0x1f) + iVar4 + (uint)bVar16;
        }
      }
    }
  }
  else {
    if (uVar14 != 6) goto LAB_0001355c;
    piVar2 = FUN_000118f4((int)piVar13,param_2[1],(uint)pcVar7);
    if (piVar2 == (int *)0x0) {
      ak_print(0xf,1,"[%s:%d] malloc_aenc_entry error \n","pcm_copy_frame",0x22e);
    }
    else {
      memcpy((void *)*piVar2,(void *)*param_2,param_2[1]);
      iVar5 = piVar13[0x12];
      iVar8 = param_2[2];
      iVar11 = param_2[3];
      iVar15 = param_2[4];
      iVar4 = param_2[1];
      piVar2[2] = iVar8;
      piVar2[3] = iVar11;
      piVar2[4] = iVar15;
      piVar2[1] = iVar4;
      piVar13[0x12] = iVar5 + 1;
      ak_thread_mutex_lock(piVar13 + 1,iVar5 + 1,iVar8,ak_thread_mutex_lock);
      iVar4 = piVar13[0xd];
      puVar9 = (undefined4 *)piVar13[0x11];
      piVar13[0x11] = (int)(piVar2 + 6);
      piVar2[7] = (int)puVar9;
      piVar2[6] = (int)(piVar13 + 0x10);
      *puVar9 = piVar2 + 6;
      piVar13[0xd] = iVar4 + 1;
      ak_thread_mutex_unlock(piVar13 + 1);
      piVar13[0x13] = piVar13[0x13] + 1;
    }
  }
  uVar12 = 0;
LAB_000132e8:
  ak_thread_rwlock_unlock(DAT_00026038);
  ak_print(0xf,5,"[%s:%d] exit....\n","ak_aenc_send_frame",0x52d);
  return uVar12;
}



undefined4 ak_aenc_get_stream(uint param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  void *__dest;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int iVar12;
  undefined4 uVar13;
  bool bVar14;
  
  ak_print(0xf,5,"[%s:%d] entry.....\n","ak_aenc_get_stream",0x53b);
  if (param_2 == (undefined4 *)0x0) {
    ak_print(0xf,1,"[%s:%d] param is NULL\n","ak_aenc_get_stream",0x53d);
    return 0x100;
  }
  if (1 < param_3) {
    ak_print(0xf,1,"[%s:%d] block must be 0 or 1\n","ak_aenc_get_stream",0x541);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00026038);
  if (param_1 < 4) {
    iVar8 = (&DAT_0002603c)[param_1];
  }
  else {
    iVar8 = FUN_000122d0();
  }
  if (iVar8 == 0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_get_stream",0x54a);
    uVar3 = 0x10000005;
    goto LAB_000138dc;
  }
  iVar12 = iVar8 + 0x40;
  if (param_3 == 0) {
    if (iVar12 == *(int *)(iVar8 + 0x40)) {
      ak_print(0xf,5,"[%s:%d] stream_list is empty\n","check_stream_list_empty",700);
      goto LAB_0001395c;
    }
  }
  else if (iVar12 == *(int *)(iVar8 + 0x40)) {
    iVar9 = 0x32;
    do {
      ak_print(0xf,5,"[%s:%d] aenc list empty\n","check_stream_list_empty",0x2af);
      ak_sleep_ms(10);
      if (iVar12 != *(int *)(iVar8 + 0x40)) goto LAB_000137b4;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    ak_print(0xf,3,"[%s:%d] stream_list is empty\n","check_stream_list_empty",0x2b7);
LAB_0001395c:
    param_2[1] = 0;
    param_2[4] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    uVar3 = 0x1000000b;
    goto LAB_000138dc;
  }
LAB_000137b4:
  ak_print(0xf,5,"[%s:%d]  list_head=%p\n","ak_aenc_get_stream",0x557,iVar12);
  iVar9 = iVar8 + 4;
  ak_print(0xf,5,"[%s:%d] entry....\n","ak_aenc_get_stream",0x55b);
  ak_thread_mutex_lock(iVar9);
  piVar10 = (int *)**(int **)(iVar8 + 0x40);
  piVar2 = *(int **)(iVar8 + 0x40);
  while (piVar7 = piVar10, (int *)iVar12 != piVar2) {
    piVar10 = piVar2 + -6;
    if (((piVar10 != (int *)0x0) && (*piVar10 != 0)) && (piVar2[-5] != 0)) {
      uVar4 = piVar2[-4];
      uVar6 = piVar2[-3];
      uVar3 = piVar2[-2];
      param_2[1] = piVar2[-5];
      uVar13 = piVar2[-5];
      param_2[2] = uVar4;
      param_2[3] = uVar6;
      param_2[4] = uVar3;
      uVar3 = ak_get_os_timestamp();
      __dest = (void *)ak_mem_alloc_(0xf,uVar13,"ak_aenc_get_stream",uVar3);
      *param_2 = __dest;
      if (__dest == (void *)0x0) {
        ak_print(0xf,1,"[%s:%d] calloc %d failed\n","ak_aenc_get_stream",0x565,piVar2[-5]);
        ak_thread_mutex_unlock(iVar9);
        ak_print(0xf,1,"[%s:%d] exit....\n","ak_aenc_get_stream",0x568);
        uVar3 = 0x102;
        goto LAB_000138dc;
      }
      memcpy(__dest,(void *)*piVar10,piVar2[-5]);
      piVar7 = (int *)piVar2[1];
      iVar5 = *piVar2;
      iVar12 = *piVar10;
      *(int **)(iVar5 + 4) = piVar7;
      *piVar7 = iVar5;
      *piVar2 = (int)piVar2;
      piVar2[1] = (int)piVar2;
      ak_mem_free(iVar12);
      *piVar10 = 0;
      ak_mem_free(piVar10);
      if (*(int *)(iVar8 + 0x34) != 0) {
        *(int *)(iVar8 + 0x34) = *(int *)(iVar8 + 0x34) + -1;
      }
      break;
    }
    piVar10 = (int *)*piVar7;
    piVar2 = piVar7;
  }
  if (*(FILE **)(iVar8 + 0x68) != (FILE *)0x0) {
    if (*(int *)(iVar8 + 0x70) == 0 && *(int *)(iVar8 + 0x74) == 0) {
      uVar3 = param_2[3];
      *(undefined4 *)(iVar8 + 0x70) = param_2[2];
      *(undefined4 *)(iVar8 + 0x74) = uVar3;
    }
    fwrite((void *)*param_2,1,param_2[1],*(FILE **)(iVar8 + 0x68));
    uVar1 = (int)*(uint *)(iVar8 + 0x6c) >> 0x1f;
    uVar11 = param_2[3] -
             (*(int *)(iVar8 + 0x74) + (uint)((uint)param_2[2] < *(uint *)(iVar8 + 0x70)));
    bVar14 = uVar1 <= uVar11;
    if (uVar11 == uVar1) {
      bVar14 = *(uint *)(iVar8 + 0x6c) <= param_2[2] - *(uint *)(iVar8 + 0x70);
    }
    if (bVar14) {
      FUN_00011f54((undefined4 *)(iVar8 + 0x68));
    }
  }
  ak_thread_mutex_unlock(iVar9);
  ak_print(0xf,5,"[%s:%d] exit....\n","ak_aenc_get_stream",0x589);
  uVar3 = 0;
  *(int *)(iVar8 + 0x50) = *(int *)(iVar8 + 0x50) + 1;
LAB_000138dc:
  ak_thread_rwlock_unlock(DAT_00026038);
  ak_print(0xf,5,"[%s:%d] exit.....\n","ak_aenc_get_stream",0x590);
  return uVar3;
}



undefined4 ak_aenc_release_stream(undefined4 param_1,int *param_2)

{
  if (param_2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] param is NULL\n","ak_aenc_release_stream",0x59d);
    return 0x100;
  }
  if (*param_2 != 0) {
    ak_mem_free();
    *param_2 = 0;
    param_2[1] = 0;
    param_2[4] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    return 0;
  }
  ak_print(0xf,1,"[%s:%d] stream->data is NULL\n","ak_aenc_release_stream",0x5a2);
  return 0x100;
}



undefined4 ak_aenc_clear_encode_buf(uint param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  ak_thread_rwlock_wrlock(DAT_00026038);
  if (param_1 < 4) {
    piVar2 = (int *)(&DAT_0002603c)[param_1];
  }
  else {
    piVar2 = (int *)FUN_000122d0();
  }
  if (piVar2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_clear_encode_buf",0x5bc);
    uVar3 = 0x10000005;
  }
  else {
    iVar1 = ak_mem_rb_reset(piVar2[0xe]);
    if (iVar1 == 0) {
      uVar3 = 0;
    }
    else {
      ak_print(0xf,1,"[%s:%d] ak_rb_reset failed\n","clear_buf",0x3fd);
      uVar3 = 0x1000000a;
    }
    if ((void *)piVar2[0xc] != (void *)0x0) {
      memset((void *)piVar2[0xc],0,piVar2[0xb]);
    }
    FUN_00011e7c((int)piVar2);
    if (*piVar2 != 0) {
      _SD_Encode_Reset();
    }
  }
  ak_thread_rwlock_unlock(DAT_00026038);
  ak_print(0xf,5,"[%s:%d] exit.....\n","ak_aenc_clear_encode_buf",0x5ca);
  return uVar3;
}



undefined4 ak_aenc_print_runtime_status(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_thread_rwlock_rdlock(DAT_00026038);
  if (param_1 < 4) {
    iVar1 = (&DAT_0002603c)[param_1];
  }
  else {
    iVar1 = FUN_000122d0();
  }
  if (iVar1 == 0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_print_runtime_status",0x5dc);
    uVar2 = 0x10000005;
  }
  else {
    ak_print(0xf,3,"[%s:%d] \nencode_count=%d\n","ak_aenc_print_runtime_status",0x5e0,
             *(undefined4 *)(iVar1 + 0x48));
    ak_print(0xf,3,"[%s:%d] genera_list_count=%d\n","ak_aenc_print_runtime_status",0x5e1,
             *(undefined4 *)(iVar1 + 0x4c));
    ak_print(0xf,3,"[%s:%d] get_streamc_count=%d\n\n","ak_aenc_print_runtime_status",0x5e2,
             *(undefined4 *)(iVar1 + 0x50));
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_00026038);
  return uVar2;
}



undefined4 ak_aenc_close(uint param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  ak_print(0xf,4,"[%s:%d] enter...\n","ak_aenc_close",0x5f3);
  ak_thread_rwlock_wrlock(DAT_00026038);
  if (param_1 < 4) {
    piVar2 = (int *)(&DAT_0002603c)[param_1];
  }
  else {
    piVar2 = (int *)FUN_000122d0();
  }
  if (piVar2 == (int *)0x0) {
    ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_close",0x5f9);
    uVar1 = 0x10000005;
  }
  else {
    ak_print(0xf,4,"[%s:%d] type=%d\n","ak_aenc_close",0x5fe,piVar2[10]);
    uVar1 = FUN_00012314(piVar2);
    if (piVar2[10] - 2U < 3) {
      uVar1 = FUN_00011ddc((int)piVar2);
    }
    DAT_0002604c = DAT_0002604c + -1;
    ak_print(0xf,4,"[%s:%d] user_count=%d\n","ak_aenc_close",0x609,DAT_0002604c);
    FUN_00011f54(piVar2 + 0x16);
    FUN_00011f54(piVar2 + 0x1a);
    ak_mem_free(piVar2);
    (&DAT_0002603c)[param_1] = 0;
  }
  ak_thread_rwlock_unlock(DAT_00026038);
  ak_print(0xf,5,"[%s:%d] leave...\n","ak_aenc_close",0x614);
  return uVar1;
}



int ak_aenc_save_file(uint param_1,uint *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  uint *__file;
  uint *__s;
  stat sStack_78;
  
  ak_print(0xf,4,"[%s:%d] enter\n","ak_aenc_save_file",0x622);
  if (param_2 == (uint *)0x0) {
    ak_print(0xf,1,"[%s:%d] save_file_info is NULL\n","check_save_file_param",0xb9);
    return 0x100;
  }
  if (*param_2 < 2) {
    if (0xb3 < param_2[0x81] - 1) {
      ak_print(0xf,1,"[%s:%d] save_second = %d, invalid, must in [1~180]\n","check_save_file_param",
               0xc2,param_2[0x81]);
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
              ak_thread_rwlock_rdlock(DAT_00026038);
              if (param_1 < 4) {
                iVar1 = (&DAT_0002603c)[param_1];
              }
              else {
                iVar1 = FUN_000122d0();
              }
              if (iVar1 == 0) {
                ak_print(0xf,1,"[%s:%d] aenc user is NULL\n","ak_aenc_save_file",0x62c);
                iVar3 = 0x10000005;
              }
              else {
                iVar3 = 0;
                if (*param_2 != 0) {
                  iVar3 = FUN_00011f94(iVar1,(char *)__file,(char *)__s);
                  if (iVar3 == 0) {
                    uVar4 = param_2[0x81];
                    *(uint *)(iVar1 + 0x5c) = uVar4 * 1000;
                    *(uint *)(iVar1 + 0x6c) = uVar4 * 1000;
                    *(undefined4 *)(iVar1 + 0x60) = 0;
                    *(undefined4 *)(iVar1 + 100) = 0;
                    *(undefined4 *)(iVar1 + 0x70) = 0;
                    *(undefined4 *)(iVar1 + 0x74) = 0;
                  }
                  else {
                    ak_print(0xf,1,"[%s:%d] dev is NULL!\n","ak_aenc_save_file",0x634);
                  }
                }
              }
              ak_thread_rwlock_unlock(DAT_00026038);
              ak_print(0xf,4,"[%s:%d] leave...\n","ak_aenc_save_file",0x640);
              return iVar3;
            }
            ak_print(5,1,"[%s:%d] file_name = %s, invalid\n","check_save_file_param",0xdb,__s);
          }
          else {
            ak_print(5,1,"[%s:%d] file_path = %s, invalid\n","check_save_file_param",0xd6,__file);
          }
        }
        else {
          ak_print(6,1,"[%s:%d] path can not write. path:%s\n","check_save_file_param",0xd0,__file);
        }
      }
      else {
        ak_print(6,1,"[%s:%d] path is not dir. path:%s\n","check_save_file_param",0xcc,__file);
      }
    }
    else {
      ak_print(6,1,"[%s:%d] stat error. path:%s, error\n","check_save_file_param",200,__file);
    }
  }
  else {
    ak_print(0xf,1,"[%s:%d] enable = %d, invalid\n","check_save_file_param",0xbd,*param_2);
  }
  return 0x101;
}



void ak_aenc_get_codec_info(void)

{
  _SD_GetAudioCodecVersionInfo();
  return;
}



ulonglong FUN_00014408(uint param_1,uint param_2)

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



ulonglong FUN_000144d0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  if (param_2 == 0) {
    uVar2 = raise(8);
    return (ulonglong)uVar2;
  }
  uVar5 = param_1 ^ param_2;
  uVar2 = param_2;
  if ((int)param_2 < 0) {
    uVar2 = -param_2;
  }
  if (uVar2 - 1 == 0) {
    if ((int)param_2 < 0) {
      param_1 = -param_1;
    }
    return CONCAT44(uVar2,param_1);
  }
  uVar4 = param_1;
  if ((int)param_1 < 0) {
    uVar4 = -param_1;
  }
  if (uVar4 <= uVar2) {
    if (uVar4 < uVar2) {
      param_1 = 0;
    }
    if (uVar4 == uVar2) {
      param_1 = (int)uVar5 >> 0x1f | 1;
    }
    return CONCAT44(uVar2,param_1);
  }
  if ((uVar2 & uVar2 - 1) == 0) {
    uVar4 = uVar4 >> (0x1fU - LZCOUNT(uVar2) & 0xff);
    if ((int)uVar5 < 0) {
      uVar4 = -uVar4;
    }
    return CONCAT44(uVar2,uVar4);
  }
  uVar3 = uVar2 << (LZCOUNT(uVar2) - LZCOUNT(uVar4) & 0xffU);
  uVar2 = 1 << (LZCOUNT(uVar2) - LZCOUNT(uVar4) & 0xffU);
  uVar1 = 0;
  while( true ) {
    if (uVar3 <= uVar4) {
      uVar4 = uVar4 - uVar3;
      uVar1 = uVar1 | uVar2;
    }
    if (uVar3 >> 1 <= uVar4) {
      uVar4 = uVar4 - (uVar3 >> 1);
      uVar1 = uVar1 | uVar2 >> 1;
    }
    if (uVar3 >> 2 <= uVar4) {
      uVar4 = uVar4 - (uVar3 >> 2);
      uVar1 = uVar1 | uVar2 >> 2;
    }
    if (uVar3 >> 3 <= uVar4) {
      uVar4 = uVar4 - (uVar3 >> 3);
      uVar1 = uVar1 | uVar2 >> 3;
    }
    bVar6 = uVar4 == 0;
    if (!bVar6) {
      uVar2 = uVar2 >> 4;
      bVar6 = uVar2 == 0;
    }
    if (bVar6) break;
    uVar3 = uVar3 >> 4;
  }
  if ((int)uVar5 < 0) {
    uVar1 = -uVar1;
  }
  return CONCAT44(uVar3,uVar1);
}



void _fini(void)

{
  return;
}


