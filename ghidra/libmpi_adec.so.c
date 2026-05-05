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

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
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



undefined4 DAT_00026030;
undefined1 __bss_start__;
dword DWORD_0001596c;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_00026050;
undefined ak_mem_free;
undefined LAB_00011948;
undefined LAB_000119a8;
undefined FUN_00011950;
undefined4 DAT_00026034;
undefined4 DAT_00026038;
int DAT_00026048;
undefined ak_thread_rwlock_rdlock;
undefined ak_sleep_ms;
undefined ak_thread_rwlock_wrlock;

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



// WARNING: Removing unreachable block (ram,0x000117a0)
// WARNING: Removing unreachable block (ram,0x000117b8)
// WARNING: Removing unreachable block (ram,0x000117c0)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_00026030);
    entry();
    if (ppuVar1[7] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_0001596c);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00011804)
// WARNING: Removing unreachable block (ram,0x0001181c)
// WARNING: Removing unreachable block (ram,0x00011824)
// WARNING: Removing unreachable block (ram,0x0001190c)
// WARNING: Removing unreachable block (ram,0x00011920)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_0001596c,&DAT_00026050,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



void * FUN_00011950(size_t param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  void *__s;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x10,param_1,"adec_decoder_alloc",uVar1,param_4);
  if (__s != (void *)0x0) {
    memset(__s,0,param_1);
  }
  return __s;
}



undefined4 FUN_00011a28(int param_1,char *param_2,char *param_3)

{
  size_t sVar1;
  FILE *pFVar2;
  undefined4 uVar3;
  char *param0;
  char acStack_884 [12];
  char acStack_878 [532];
  char acStack_664 [532];
  char acStack_450 [532];
  char acStack_23c [536];
  
  sVar1 = strlen(param_2);
  if (0xfe < sVar1 - 1) {
    ak_print(0x10,1,"[%s:%d] file_path length = %d ,0< path_size < %d \n","open_adec_save_file",0xfc
             ,sVar1,0x100);
    return 0x101;
  }
  sVar1 = strlen(param_3);
  if (sVar1 - 1 < 0xff) {
    memset(acStack_878,0,0x214);
    memset(acStack_664,0,0x214);
    param0 = acStack_450;
    memset(param0,0,0x214);
    memset(acStack_23c,0,0x214);
    memset(acStack_884,0,10);
    switch(*(undefined4 *)(param_1 + 0x10)) {
    case 2:
      strncpy(acStack_884,".mp3",5);
      break;
    case 3:
      strncpy(acStack_884,".amr",5);
      break;
    case 4:
      strncpy(acStack_884,".aac",5);
      break;
    case 6:
      strncpy(acStack_884,".pcm",5);
      break;
    case 0x11:
      strncpy(acStack_884,".g711a",7);
      break;
    case 0x12:
      strncpy(acStack_884,".g711u",7);
    }
    sprintf(acStack_878,"%s%s_input_%s",param_2,param_3,acStack_884);
    ak_print(0x10,3,"[%s:%d] input_full_name =%s\n","open_adec_save_file",0x11d,acStack_878);
    sprintf(acStack_664,"%s%s%s",param_2,param_3,"_output.pcm");
    ak_print(0x10,3,"[%s:%d] output_full_name =%s\n","open_adec_save_file",0x121,acStack_664);
    sprintf(param0,"%s%s_in_dec_%s",param_2,param_3,acStack_884);
    ak_print(0x10,3,"[%s:%d] in_dec_full_name =%s\n","open_adec_save_file",0x125,param0);
    sprintf(acStack_23c,"%s%s%s",param_2,param_3,"_out_dec.pcm");
    ak_print(0x10,3,"[%s:%d] out_dec_full_name =%s\n","open_adec_save_file",0x129,acStack_23c);
    pFVar2 = fopen(acStack_878,"w+");
    *(FILE **)(param_1 + 0x60) = pFVar2;
    if (pFVar2 == (FILE *)0x0) {
      uVar3 = 0x12f;
      param0 = acStack_878;
    }
    else {
      pFVar2 = fopen(acStack_664,"w+");
      *(FILE **)(param_1 + 0x6c) = pFVar2;
      if (pFVar2 == (FILE *)0x0) {
        uVar3 = 0x137;
        param0 = acStack_664;
      }
      else {
        pFVar2 = fopen(param0,"w+");
        *(FILE **)(param_1 + 0x78) = pFVar2;
        if (pFVar2 == (FILE *)0x0) {
          uVar3 = 0x13f;
        }
        else {
          pFVar2 = fopen(acStack_23c,"w+");
          *(FILE **)(param_1 + 0x84) = pFVar2;
          if (pFVar2 != (FILE *)0x0) {
            return 0;
          }
          uVar3 = 0x146;
          param0 = acStack_23c;
        }
      }
    }
    ak_print(0x10,1,"[%s:%d] open %s error\n","open_adec_save_file",uVar3,param0);
    if (*(FILE **)(param_1 + 0x60) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x60));
      *(undefined4 *)(param_1 + 0x60) = 0;
      *(undefined4 *)(param_1 + 100) = 0;
      *(undefined4 *)(param_1 + 0x68) = 0;
    }
    if (*(FILE **)(param_1 + 0x6c) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x6c));
      *(undefined4 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
    }
    if (*(FILE **)(param_1 + 0x78) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x78));
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x7c) = 0;
      *(undefined4 *)(param_1 + 0x80) = 0;
    }
    if (*(FILE **)(param_1 + 0x84) != (FILE *)0x0) {
      fclose(*(FILE **)(param_1 + 0x84));
      *(undefined4 *)(param_1 + 0x84) = 0;
      *(undefined4 *)(param_1 + 0x88) = 0;
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
  }
  else {
    ak_print(0x10,1,"[%s:%d] file_name length = %d ,0< name_size < %d\n","open_adec_save_file",0x103
             ,sVar1,0x100);
  }
  return 0x101;
}



undefined4 FUN_00011f08(undefined4 param_1)

{
  ak_print(0x10,1,"[%s:%d] adec not suport handle_id: %d\n","get_adec_user_handle",0x326,param_1);
  return 0;
}



int FUN_00011f50(int *param_1)

{
  int iVar1;
  
  if (*param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = ak_mem_free(*param_1);
    if (iVar1 != 0) {
      ak_print(0x10,1,"[%s:%d] ak_mem_free failed\n","dec_destroy_buffer",0x29c);
    }
    *param_1 = 0;
  }
  return iVar1;
}



undefined4 FUN_00011fc8(undefined4 *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *local_88;
  undefined4 local_84;
  code *local_80;
  code *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined4 local_68;
  undefined4 local_64;
  undefined2 local_60;
  undefined2 local_5e;
  undefined4 local_54;
  undefined4 local_3c;
  undefined2 local_38;
  undefined2 local_36;
  undefined4 local_24;
  
  memset(&local_88,0,0x68);
  iVar2 = param_2[0x2d];
  if (0x14 < param_1[3] - 1) {
    ak_print(0x10,1,"[%s:%d] unsupport audio decode type\n","set_decoder_input",0x179);
    goto LAB_000120e0;
  }
  local_64 = *param_1;
  local_5e = (undefined2)param_1[1];
  local_54 = 0x5000;
  local_7c = ak_mem_free;
  local_80 = FUN_00011950;
  local_78 = &LAB_000119a8;
  local_74 = &LAB_00011948;
  local_60 = (undefined2)param_1[2];
  iVar1 = ak_get_chip_id();
  local_88 = "AudioCodec Version V1.21.12";
  if (iVar1 == 0x20160101) {
    local_84 = 0xe;
  }
  else {
    local_84 = 0x10;
  }
  local_68 = param_1[3];
  switch(local_68) {
  case 2:
    ak_print(0x10,3,"[%s:%d] decode type=%d: MP3\n","set_decoder_input",0x198,2);
    local_24 = _SD_MP3_login(0);
    break;
  case 3:
    ak_print(0x10,3,"[%s:%d] decode type=%d: AMR\n","set_decoder_input",0x19e,3);
    local_64 = 8000;
    local_60 = 1;
    local_24 = _SD_AMR_login(0);
    break;
  case 4:
    ak_print(0x10,3,"[%s:%d] decode type=%d: AAC\n","set_decoder_input",0x1a7,4);
    local_38 = 0;
    local_36 = (short)iVar2;
    local_24 = _SD_AAC_login(0);
    local_3c = 0x14;
    break;
  default:
    ak_print(0x10,3,"[%s:%d] decode type=%d\n","set_decoder_input",0x1c7,local_68);
    break;
  case 6:
    ak_print(0x10,3,"[%s:%d] decode type=%d: PCM\n","set_decoder_input",0x1b1,6);
    local_24 = _SD_PCM_login(0);
    break;
  case 0xe:
    ak_print(0x10,3,"[%s:%d] decode type=%d: DRA\n","set_decoder_input",0x1c3,0xe);
    break;
  case 0x11:
    uVar3 = 0x1b7;
    uVar5 = 0x11;
    pcVar4 = "[%s:%d] decode type=%d: PCM_ALAW\n";
    goto LAB_00012150;
  case 0x12:
    uVar3 = 0x1bd;
    uVar5 = 0x12;
    pcVar4 = "[%s:%d] decode type=%d: PCM_ULAW\n";
LAB_00012150:
    ak_print(0x10,3,pcVar4,"set_decoder_input",uVar3,uVar5);
    local_24 = _SD_G711_login(0);
  }
  ak_print(0x10,3,"[%s:%d] sample_rate=%d, channel_num=%d, sample_bits=%d\n","set_decoder_input",
           0x1cd,*param_1,param_1[2],param_1[1]);
LAB_000120e0:
  memset(param_2 + 7,0,0x1c);
  iVar2 = _SD_Decode_Open(&local_88,param_2 + 7);
  *param_2 = iVar2;
  if (iVar2 == 0) {
    ak_print(0x10,1,"[%s:%d] _SD_Decode_Open failed\n","decode_lib_open",0x1de);
    uVar3 = 0xffffffff;
  }
  else {
    _SD_SetBufferMode(iVar2,0);
    _SD_SetInbufMinLen(*param_2,0x80);
    uVar3 = 0;
  }
  return uVar3;
}



undefined4 FUN_000123c8(int *param_1)

{
  undefined4 uVar1;
  
  if (*param_1 == 0) {
    ak_print(0x10,1,"[%s:%d] user->lib_handle is NULL\n","decode_lib_close",0x1f5);
    uVar1 = 0xffffffff;
  }
  else {
    _SD_Buffer_Clear();
    _SD_Decode_Close(*param_1);
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 FUN_00012440(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = _SD_Buffer_GetFreeLen();
    return uVar1;
  }
  ak_print(0x10,1,"[%s:%d] user->lib_handle is NULL\n","decode_lib_get_free_size",0x167);
  return 0;
}



char * ak_adec_get_version(void)

{
  return "libmpi_adec V1.3.08";
}



undefined4 ak_adec_open(uint *param_1,int *param_2)

{
  undefined4 uVar1;
  int *__s;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  
  pcVar6 = "libmpi_adec V1.3.08";
  ak_print(0x10,4,"[%s:%d] adec version: %s\n","ak_adec_open",0x36d,"libmpi_adec V1.3.08");
  if (param_1 == (uint *)0x0) {
    ak_print(0x10,1,"[%s:%d] invalid audio decode param\n","check_adec_open_param",0x2d6,pcVar6);
    return 0x100;
  }
  uVar2 = param_1[3];
  if (uVar2 == 3) {
    uVar3 = param_1[2];
    if (uVar3 == 2) {
      ak_print(0x10,1,"[%s:%d] amr decode not suppprt stereo\n","check_adec_open_param",0x2dd,pcVar6
              );
      return 0x101;
    }
    if (*param_1 != 8000) {
      ak_print(0x10,1,"[%s:%d] amr decode sample rate > 8000, not support\n","check_adec_open_param"
               ,0x2e3,pcVar6);
      return 0x101;
    }
  }
  else {
    if (uVar2 == 0x11) {
      if (param_1[2] == 2) {
        ak_print(0x10,1,"[%s:%d] g711a decode not suppprt stereo\n","check_adec_open_param",0x2ea,
                 pcVar6);
        return 0x101;
      }
      uVar3 = *param_1;
      if (uVar3 != 8000 && uVar3 != 16000) {
        ak_print(0x10,1,"[%s:%d] g711a decode sample rate != 8000 or 16000, not support\n",
                 "check_adec_open_param",0x2f1,pcVar6);
        return 0x101;
      }
    }
    else if (uVar2 == 0x12) {
      if (param_1[2] == 2) {
        ak_print(0x10,1,"[%s:%d] g711u decode not suppprt stereo\n","check_adec_open_param",0x2f8,
                 pcVar6);
        return 0x101;
      }
      uVar3 = *param_1;
      if (uVar3 != 8000 && uVar3 != 16000) {
        ak_print(0x10,1,"[%s:%d] g711u decode sample rate != 8000 or 16000, not support\n",
                 "check_adec_open_param",0x2ff,pcVar6);
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
      ak_print(0x10,1,"[%s:%d] sample rate not suppprt %d \n","check_adec_open_param",0x306,uVar3);
      return 0x101;
    }
    uVar3 = param_1[2];
  }
  if (1 < uVar3 - 1) {
    ak_print(0x10,1,"[%s:%d] channel number not suppprt %d \n","check_adec_open_param",0x30c,uVar3);
    return 0x101;
  }
  if (param_1[1] != 0x10) {
    ak_print(0x10,1,"[%s:%d] sample bits not suppprt %d \n","check_adec_open_param",0x312,param_1[1]
            );
    return 0x101;
  }
  if (0x15 < uVar2 - 1) {
    ak_print(0x10,1,"[%s:%d] decode type not suppprt %d \n","check_adec_open_param",0x318,uVar2);
    return 0x101;
  }
  if (param_2 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] handle_id is NULL\n","check_adec_open_param",0x31d,pcVar6);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00026034);
  if (3 < DAT_00026048) {
    ak_print(0x10,1,"[%s:%d] adec open too many, user_count=%d\n","ak_adec_open",0x377,DAT_00026048)
    ;
    ak_thread_rwlock_unlock(DAT_00026034);
    return 0x10000002;
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  uVar1 = ak_get_os_timestamp();
  __s = (int *)ak_mem_alloc_(0x10,0xb8,"ak_adec_open",uVar1);
  if (__s == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] calloc failed\n","ak_adec_open",0x37f);
    return 0x102;
  }
  memset(__s,0,0xb8);
  memcpy(__s + 1,param_1,0x10);
  uVar2 = *param_1;
  iVar4 = 0x200;
  __s[6] = 0x200;
  if (15999 < (int)uVar2) {
    if ((int)uVar2 < 32000) {
      iVar4 = 0x400;
    }
    else if ((int)uVar2 < 0xbb81) {
      iVar4 = 0x800;
    }
    else {
      iVar4 = 0x1000;
    }
  }
  uVar2 = param_1[2];
  __s[0x13] = iVar4;
  if (uVar2 == 2) {
    __s[0x13] = iVar4 << 1;
  }
  ak_set_debug_num_info(0x10,1,"user->output_pcm_len");
  iVar4 = FUN_00011fc8(param_1,__s);
  if (iVar4 == 0) {
    iVar4 = __s[0x13];
    __s[0x25] = iVar4 << 1;
    uVar1 = ak_get_os_timestamp();
    iVar4 = ak_mem_alloc_(0x10,iVar4 << 1,"dec_init_buffer",uVar1);
    __s[0x24] = iVar4;
    if (iVar4 != 0) {
      __s[0x26] = 0;
      ak_thread_mutex_init(__s + 0x27,0);
      ak_set_debug_str_info(0x10,1,"adec_version","libmpi_adec V1.3.08");
      uVar1 = _SD_GetAudioCodecVersionInfo();
      ak_set_debug_str_info(0x10,1,"AudioCodec version",uVar1);
      ak_set_debug_num_info(0x10,1,"user_count",DAT_00026048);
      ak_set_debug_num_info(0x10,1,"adec_m_ulSize",__s[0xc]);
      ak_set_debug_num_info(0x10,1,"adec_m_ulDecDataSize",__s[0xd]);
      piVar5 = &DAT_00026034;
      ak_thread_rwlock_wrlock(DAT_00026034);
      iVar4 = 0;
      do {
        piVar5 = piVar5 + 1;
        if (*piVar5 == 0) {
          DAT_00026048 = DAT_00026048 + 1;
          (&DAT_00026038)[iVar4] = __s;
          *param_2 = iVar4;
          break;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      ak_thread_rwlock_unlock(DAT_00026034);
      uVar1 = 0;
      goto LAB_000128e8;
    }
    ak_print(0x10,1,"[%s:%d] calloc audio decode out buffer failed\n","dec_init_buffer",0x28d);
    uVar1 = 0x102;
  }
  else {
    ak_print(0x10,1,"[%s:%d] open decode lib failed\n","ak_adec_open",0x38f);
    uVar1 = 0x10000000;
  }
  FUN_000123c8(__s);
  FUN_00011f50(__s + 0x24);
  ak_mem_free(__s);
LAB_000128e8:
  ak_print(0x10,5,"[%s:%d] exit...\n","ak_adec_open",0x3b7);
  return uVar1;
}



undefined4 ak_adec_get_params(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00026034);
    if (param_1 < 4) {
      iVar1 = (&DAT_00026038)[param_1];
    }
    else {
      iVar1 = FUN_00011f08(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_get_params",0x3cf);
      uVar5 = 0x10000004;
    }
    else {
      uVar2 = *(undefined4 *)(iVar1 + 8);
      uVar3 = *(undefined4 *)(iVar1 + 0xc);
      uVar4 = *(undefined4 *)(iVar1 + 0x10);
      uVar5 = 0;
      *param_2 = *(undefined4 *)(iVar1 + 4);
      param_2[1] = uVar2;
      param_2[2] = uVar3;
      param_2[3] = uVar4;
    }
    ak_thread_rwlock_unlock(DAT_00026034);
    return uVar5;
  }
  ak_print(0x10,1,"[%s:%d] param is NULL\n","ak_adec_get_params",0x3c6);
  return 0x100;
}



undefined4 ak_adec_set_output_pcm_len(uint param_1,uint param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_r3;
  int iVar5;
  
  ak_thread_rwlock_rdlock(DAT_00026034);
  if (param_1 < 4) {
    iVar5 = (&DAT_00026038)[param_1];
  }
  else {
    iVar5 = FUN_00011f08(param_1);
  }
  if (iVar5 == 0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_set_output_pcm_len",0x3ee);
    uVar1 = 0x10000004;
    goto LAB_00012e04;
  }
  if (*(uint *)(iVar5 + 0x4c) == param_2) {
    ak_print(0x10,1,"[%s:%d] out_pcm_len is set the same\n","ak_adec_set_output_pcm_len",0x3f4);
    goto LAB_00012d74;
  }
  iVar3 = *(int *)(iVar5 + 4);
  if (iVar3 < 16000) {
    uVar4 = 0x200;
  }
  else if (iVar3 < 32000) {
    uVar4 = 0x400;
  }
  else if (iVar3 < 0xbb81) {
    uVar4 = 0x800;
  }
  else {
    uVar4 = 0x1000;
  }
  if (*(int *)(iVar5 + 0xc) == 2) {
    uVar4 = uVar4 << 1;
    if (param_2 < uVar4) goto LAB_00012ddc;
    if (param_2 < 0x2001) goto LAB_00012d04;
    uVar1 = 0x40a;
    uVar4 = 0x2000;
LAB_00012e98:
    pcVar2 = "[%s:%d] out_pcm_len must <= %d\n";
  }
  else {
    if (uVar4 <= param_2) {
      if ((*(int *)(iVar5 + 0xc) != 1) || (param_2 < 0x1001)) {
LAB_00012d04:
        ak_thread_rwlock_unlock(DAT_00026034);
        ak_thread_rwlock_wrlock(DAT_00026034);
        *(uint *)(iVar5 + 0x4c) = param_2;
        if (*(int *)(iVar5 + 0x90) != 0) {
          ak_mem_free();
          param_2 = *(uint *)(iVar5 + 0x4c);
        }
        *(uint *)(iVar5 + 0x94) = param_2 << 1;
        uVar1 = ak_get_os_timestamp();
        iVar3 = ak_mem_alloc_(0x10,param_2 << 1,"dec_relloc_buffer",uVar1);
        uVar1 = extraout_r3;
        if (iVar3 != 0) {
          uVar1 = 0;
        }
        *(int *)(iVar5 + 0x90) = iVar3;
        if (iVar3 != 0) {
          *(undefined4 *)(iVar5 + 0x98) = uVar1;
LAB_00012d74:
          ak_thread_rwlock_unlock(DAT_00026034);
          ak_set_debug_num_info(0x10,1,"user->output_pcm_len",*(undefined4 *)(iVar5 + 0x4c));
          return 0;
        }
        ak_print(0x10,1,"[%s:%d] calloc audio decode out buffer failed\n","dec_relloc_buffer",0x2ab)
        ;
        uVar1 = 0x102;
        goto LAB_00012e04;
      }
      uVar1 = 0x404;
      uVar4 = 0x1000;
      goto LAB_00012e98;
    }
LAB_00012ddc:
    uVar1 = 0x3fe;
    pcVar2 = "[%s:%d] out_pcm_len must >= %d\n";
  }
  ak_print(0x10,1,pcVar2,"ak_adec_set_output_pcm_len",uVar1,uVar4);
  uVar1 = 0x101;
LAB_00012e04:
  ak_thread_rwlock_unlock(DAT_00026034);
  return uVar1;
}



undefined4 ak_adec_send_stream(uint param_1,void *param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  if (param_2 == (void *)0x0) {
    ak_print(0x10,1,"[%s:%d] stream is NULL\n","check_adec_send_stream_param",0x2b7);
    return 0x100;
  }
  if (param_3 == 0) {
    ak_print(0x10,1,"[%s:%d] stream->len is %d, invalid\n","check_adec_send_stream_param",699,0);
    return 0x101;
  }
  if (1 < param_4) {
    ak_print(0x10,1,"[%s:%d] block is %d, invalid\n","check_adec_send_stream_param",0x2bf,param_3);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00026034,param_2,param_3,ak_thread_rwlock_rdlock);
  if (param_1 < 4) {
    puVar4 = (undefined4 *)(&DAT_00026038)[param_1];
  }
  else {
    puVar4 = (undefined4 *)FUN_00011f08(param_1);
  }
  if (puVar4 == (undefined4 *)0x0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_send_stream",0x433);
    uVar3 = 0x10000004;
  }
  else {
    if (puVar4[3] == 1) {
      if (0x1000 < param_3) {
        ak_print(0x10,1,"[%s:%d] MONO, out_pcm_len must <= %d\n","ak_adec_send_stream",0x439,0x1000)
        ;
        uVar3 = 0x101;
        goto LAB_000130f8;
      }
    }
    else if (puVar4[3] == 2 && 0x2000 < param_3) {
      ak_print(0x10,1,"[%s:%d] STEREO, out_pcm_len must <= %d\n","ak_adec_send_stream",0x43f,0x2000)
      ;
      uVar3 = 0x101;
      goto LAB_000130f8;
    }
    if (*(char *)(puVar4 + 5) == '\x01') {
      _SD_SetBufferMode(*puVar4,0);
      *(undefined1 *)(puVar4 + 5) = 0;
    }
    if ((FILE *)puVar4[0x18] != (FILE *)0x0) {
      fwrite(param_2,1,param_3,(FILE *)puVar4[0x18]);
      puVar4[0x1a] = puVar4[0x1a] + param_3;
    }
    if (param_4 == 0) {
      iVar1 = _SD_Buffer_Fill(*puVar4,param_2,param_3,1);
      ak_print(0x10,5,"[%s:%d] send_len=%d\n","send_stream_non_block_mode",0x27e,iVar1);
      if (iVar1 < 1) {
        uVar3 = 0x10000009;
      }
      else {
        puVar4[0x14] = puVar4[0x14] + 1;
        uVar3 = 0;
      }
    }
    else {
      iVar1 = _SD_Buffer_Fill(*puVar4,param_2,param_3,1);
      if (iVar1 == 0) {
        ak_sleep_ms(10);
        iVar1 = _SD_Buffer_Fill(*puVar4,param_2,param_3,1);
        iVar2 = 799;
        do {
          if (iVar1 != 0) goto LAB_000130e0;
          ak_sleep_ms(10);
          iVar1 = _SD_Buffer_Fill(*puVar4,param_2,param_3,1);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        ak_print(0x10,1,"[%s:%d] block mode, no space\n","send_stream_block_mode",0x26e);
        uVar3 = 0x10000009;
      }
      else {
LAB_000130e0:
        if (iVar1 < 0) {
          uVar3 = 0x10000007;
        }
        else {
          uVar3 = 0;
          puVar4[0x14] = puVar4[0x14] + 1;
        }
      }
    }
  }
LAB_000130f8:
  ak_thread_rwlock_unlock(DAT_00026034);
  return uVar3;
}



undefined4 ak_adec_get_frame(uint param_1,int *param_2,int param_3)

{
  size_t sVar1;
  size_t __n;
  int iVar2;
  size_t sVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  
  if (param_2 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] frame is NULL\n","check_adec_get_frame_param",0x2c8);
    return 0x100;
  }
  if (*param_2 != 0) {
    ak_print(0x10,1,"[%s:%d] frame->data must be NULL, malloc by sdk\n","check_adec_get_frame_param"
             ,0x2cd);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00026034,param_2,&DAT_00026034,ak_thread_rwlock_rdlock);
  if (param_1 < 4) {
    piVar5 = (int *)(&DAT_00026038)[param_1];
  }
  else {
    piVar5 = (int *)FUN_00011f08(param_1);
  }
  if (piVar5 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_get_frame",0x46c);
    uVar6 = 0x10000004;
  }
  else {
    if ((char)piVar5[5] != '\x01') {
      iVar7 = 0;
LAB_00013378:
      iVar4 = piVar5[0x25];
      iVar2 = piVar5[0x26];
      if (iVar4 <= iVar2) goto LAB_00013454;
      do {
        iVar4 = iVar4 - iVar2;
        if (iVar4 == 0) goto LAB_00013478;
        if (iVar4 < 0x200) {
          ak_print(0x10,1,
                   "[%s:%d] Ring buffer unexpected almost full maybe no enough space ! have you call ak_adec_release_frame ? rb_write_size=%d w=%d\n"
                   ,"get_frame_from_decoder",0x223,iVar4,iVar2);
          __n = 0;
          sVar1 = piVar5[0x26];
        }
        else {
          if (piVar5[0x13] <= iVar4) {
            iVar4 = piVar5[0x13];
          }
          piVar5[0xc] = iVar4;
          piVar5[0xb] = piVar5[0x24] + iVar2;
          __n = _SD_Decode(*piVar5,piVar5 + 7);
          if ((int)__n < 1) {
            sVar3 = __n;
            sVar1 = piVar5[0x26];
            if (__n != 0) {
LAB_00013504:
              if (sVar3 == 0) {
LAB_000134b4:
                param_2[1] = 0;
                *param_2 = 0;
                uVar6 = 0x10000008;
              }
              else if (sVar3 == 0xfffffff7) {
                ak_print(0x10,5,"[%s:%d] stream terminated remain=%d\n","get_decode_frame_data",
                         0x354,piVar5[0x26]);
                uVar6 = FUN_00012440(*piVar5);
                ak_print(0x10,5,"[%s:%d] terminated called, decode free size=%d\n",
                         "get_decode_frame_data",0x356,uVar6);
                iVar7 = piVar5[0x26];
                if (piVar5[0x13] <= piVar5[0x26]) {
                  iVar7 = piVar5[0x13];
                }
                param_2[1] = iVar7;
                if (iVar7 == 0) {
                  uVar6 = 0x10000008;
                  *param_2 = 0;
                }
                else {
                  iVar4 = piVar5[0x16];
                  iVar7 = piVar5[0x24];
                  param_2[4] = param_2[4] + 1;
                  *param_2 = iVar7;
                  uVar6 = 0;
                  piVar5[0x16] = iVar4 + 1;
                }
                *(undefined1 *)(piVar5 + 5) = 1;
              }
              else {
                ak_print(0x10,1,"[%s:%d] ERROR_ADEC_ATC_LIB_ERROR \n","get_decode_frame_data",0x35d)
                ;
                uVar6 = 0x10000006;
                param_2[1] = 0;
                *param_2 = 0;
              }
              goto LAB_000135b0;
            }
          }
          else {
            iVar4 = piVar5[0x26];
            piVar5[0x15] = piVar5[0x15] + 1;
            piVar5[0x26] = __n + iVar4;
            sVar1 = __n + iVar4;
            if ((FILE *)piVar5[0x21] != (FILE *)0x0) {
              fwrite((void *)piVar5[0xb],1,__n,(FILE *)piVar5[0x21]);
              piVar5[0x23] = piVar5[0x23] + __n;
              sVar1 = piVar5[0x26];
            }
          }
        }
        while( true ) {
          sVar3 = sVar1;
          iVar4 = piVar5[0x13];
          if (iVar4 <= (int)sVar3) {
            if ((int)sVar3 < 1) goto LAB_00013504;
            if (piVar5[0x26] <= iVar4) {
              iVar4 = piVar5[0x26];
            }
            param_2[1] = iVar4;
            if (iVar4 == 0) {
              *param_2 = 0;
              uVar6 = 0x10000008;
            }
            else {
              iVar4 = piVar5[0x16];
              iVar7 = piVar5[0x24];
              param_2[4] = param_2[4] + 1;
              *param_2 = iVar7;
              uVar6 = 0;
              piVar5[0x16] = iVar4 + 1;
            }
            goto LAB_000135b0;
          }
          if (param_3 == 0) {
            if (__n == 0) goto LAB_000134b4;
            goto LAB_00013378;
          }
          if (200 < iVar7) {
            ak_print(0x10,1,"[%s:%d] retry_num=%d\n","get_frame_loop",0x24b,iVar7);
            goto LAB_000134b4;
          }
          if (__n != 0) goto LAB_00013378;
          ak_sleep_ms(10,iVar4,0,ak_sleep_ms);
          iVar4 = piVar5[0x25];
          iVar2 = piVar5[0x26];
          iVar7 = iVar7 + 1;
          if (iVar2 < iVar4) break;
LAB_00013454:
          ak_print(0x10,1,"[%s:%d] Ring buffer get write size full ! rb_write_size=%d, w=%d\n",
                   "get_rb_write_size",0x215,0,iVar2);
LAB_00013478:
          ak_print(0x10,1,
                   "[%s:%d] Ring buffer unexpected full ! have you call ak_adec_release_frame ? rb_write_size=%d, rb_w_offset=%d\n"
                   ,"get_frame_from_decoder",0x220,0,piVar5[0x26]);
          __n = 0;
          sVar1 = piVar5[0x26];
        }
      } while( true );
    }
    ak_print(0x10,5,"[%s:%d] adec_status = AK_ADEC_STATU_END \n","ak_adec_get_frame",0x471);
    uVar6 = 0x1000000b;
  }
LAB_000135b0:
  ak_thread_rwlock_unlock(DAT_00026034);
  ak_print(0x10,5,"[%s:%d] exit... \n","ak_adec_get_frame",0x47f);
  return uVar6;
}



undefined4 ak_adec_release_frame(uint param_1,int *param_2,undefined4 param_3)

{
  size_t sVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  size_t __n;
  void *__ptr;
  
  if (param_2 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] frame is NULL\n","ak_adec_release_frame",0x48c);
    return 0x100;
  }
  if (*param_2 == 0) {
    ak_print(0x10,1,"[%s:%d] frame->data is NULL\n","ak_adec_release_frame",0x491);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00026034,param_2,param_3,ak_thread_rwlock_rdlock);
  __ptr = (void *)*param_2;
  __n = param_2[1];
  if (__ptr != (void *)0x0) {
    *param_2 = 0;
  }
  param_2[1] = 0;
  param_2[4] = 0;
  if (param_1 < 4) {
    iVar3 = (&DAT_00026038)[param_1];
  }
  else {
    iVar3 = FUN_00011f08(param_1);
  }
  if (iVar3 == 0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_release_frame",0x4a2);
    uVar4 = 0x10000004;
  }
  else {
    if (*(FILE **)(iVar3 + 0x6c) != (FILE *)0x0) {
      fwrite(__ptr,1,__n,*(FILE **)(iVar3 + 0x6c));
      uVar2 = __n + *(int *)(iVar3 + 0x74);
      *(uint *)(iVar3 + 0x74) = uVar2;
      if (*(uint *)(iVar3 + 0x70) <= uVar2) {
        if (*(FILE **)(iVar3 + 0x6c) != (FILE *)0x0) {
          fclose(*(FILE **)(iVar3 + 0x6c));
          *(undefined4 *)(iVar3 + 0x6c) = 0;
          *(undefined4 *)(iVar3 + 0x70) = 0;
          *(undefined4 *)(iVar3 + 0x74) = 0;
        }
        if (*(FILE **)(iVar3 + 0x60) != (FILE *)0x0) {
          fclose(*(FILE **)(iVar3 + 0x60));
          *(undefined4 *)(iVar3 + 0x60) = 0;
          *(undefined4 *)(iVar3 + 100) = 0;
          *(undefined4 *)(iVar3 + 0x68) = 0;
        }
        if (*(FILE **)(iVar3 + 0x78) != (FILE *)0x0) {
          fclose(*(FILE **)(iVar3 + 0x78));
          *(undefined4 *)(iVar3 + 0x78) = 0;
          *(undefined4 *)(iVar3 + 0x7c) = 0;
          *(undefined4 *)(iVar3 + 0x80) = 0;
        }
        if (*(FILE **)(iVar3 + 0x84) != (FILE *)0x0) {
          fclose(*(FILE **)(iVar3 + 0x84));
          *(undefined4 *)(iVar3 + 0x84) = 0;
          *(undefined4 *)(iVar3 + 0x88) = 0;
          *(undefined4 *)(iVar3 + 0x8c) = 0;
        }
      }
    }
    ak_thread_mutex_lock(iVar3 + 0x9c);
    sVar1 = *(size_t *)(iVar3 + 0x98);
    if ((int)__n < (int)sVar1) {
      memcpy(*(void **)(iVar3 + 0x90),(void *)((int)*(void **)(iVar3 + 0x90) + __n),sVar1 - __n);
      *(size_t *)(iVar3 + 0x98) = sVar1 - __n;
    }
    else if (__n == sVar1) {
      *(undefined4 *)(iVar3 + 0x98) = 0;
    }
    ak_thread_mutex_unlock(iVar3 + 0x9c);
    uVar4 = 0;
    *(int *)(iVar3 + 0x5c) = *(int *)(iVar3 + 0x5c) + 1;
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  ak_print(0x10,5,"[%s:%d] exit... \n","ak_adec_release_frame",0x4be);
  return uVar4;
}



undefined4 ak_adec_send_stream_end(uint param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  ak_thread_rwlock_rdlock(DAT_00026034);
  if (param_1 < 4) {
    piVar2 = (int *)(&DAT_00026038)[param_1];
  }
  else {
    piVar2 = (int *)FUN_00011f08(param_1);
  }
  if (piVar2 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_send_stream_end",0x4cf);
    uVar3 = 0x10000004;
  }
  else if (piVar2[0x14] == 0) {
    ak_print(0x10,1,"[%s:%d] adec send stream no start\n","ak_adec_send_stream_end",0x4d4);
    uVar3 = 0x1000000c;
  }
  else {
    uVar3 = FUN_00012440(*piVar2);
    ak_print(0x10,3,"[%s:%d] called, decode free size=%d\n","ak_adec_send_stream_end",0x4da,uVar3);
    iVar1 = _SD_SetBufferMode(*piVar2,1);
    if (iVar1 == 1) {
      uVar3 = 0;
    }
    else {
      ak_print(0x10,1,"[%s:%d] _SD_SetBufferMode failed\n","ak_adec_send_stream_end",0x4de,uVar3);
      uVar3 = 0x10000006;
    }
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  return uVar3;
}



undefined4 ak_adec_clear_decode_buf(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  
  ak_thread_rwlock_wrlock(DAT_00026034);
  if (param_1 < 4) {
    piVar3 = (int *)(&DAT_00026038)[param_1];
  }
  else {
    piVar3 = (int *)FUN_00011f08(param_1);
  }
  if (piVar3 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_clear_decode_buf",0x4f7);
    uVar2 = 0x10000004;
  }
  else if (*piVar3 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = _SD_Get_Input_Buf_Info(*piVar3,1);
    iVar4 = iVar1;
    ak_print(0x10,3,"[%s:%d] remain = %d\n","ak_adec_clear_decode_buf",0x4fe,iVar1);
    if ((iVar1 < 1) || (iVar1 = _SD_Buffer_Clear(*piVar3), iVar1 == 1)) {
      uVar2 = 0;
    }
    else {
      ak_print(0x10,1,"[%s:%d] _SD_Buffer_Clear failed\n","ak_adec_clear_decode_buf",0x502,iVar4);
      uVar2 = 0x10000006;
    }
    iVar1 = _SD_Decode_Seek(*piVar3,0);
    if (iVar1 != 1) {
      ak_print(0x10,1,"[%s:%d] _SD_Buffer_Seek failed","ak_adec_clear_decode_buf",0x508,iVar4);
      uVar2 = 0x10000006;
    }
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  return uVar2;
}



undefined4 ak_adec_print_runtime_status(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_thread_rwlock_rdlock(DAT_00026034);
  if (param_1 < 4) {
    iVar1 = (&DAT_00026038)[param_1];
  }
  else {
    iVar1 = FUN_00011f08(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_print_runtime_status",0x51d);
    uVar2 = 0x10000004;
  }
  else {
    ak_print(0x10,3,"[%s:%d] send_stream_count=%d\n","ak_adec_print_runtime_status",0x522,
             *(undefined4 *)(iVar1 + 0x50));
    ak_print(0x10,3,"[%s:%d] decode_count=%d\n","ak_adec_print_runtime_status",0x523,
             *(undefined4 *)(iVar1 + 0x54));
    ak_print(0x10,3,"[%s:%d] get_frame_count=%d\n","ak_adec_print_runtime_status",0x524,
             *(undefined4 *)(iVar1 + 0x58));
    ak_print(0x10,3,"[%s:%d] release_frame_count=%d\n\n","ak_adec_print_runtime_status",0x525,
             *(undefined4 *)(iVar1 + 0x5c));
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  return uVar2;
}



int ak_adec_close(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  
  ak_thread_rwlock_wrlock(DAT_00026034,param_2,param_3,ak_thread_rwlock_wrlock);
  ak_print(0x10,3,"[%s:%d] entry\n","ak_adec_close",0x535);
  if (param_1 < 4) {
    piVar2 = (int *)(&DAT_00026038)[param_1];
  }
  else {
    piVar2 = (int *)FUN_00011f08(param_1);
  }
  if (piVar2 == (int *)0x0) {
    ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_close",0x538);
    iVar1 = 0x10000004;
  }
  else {
    if (*piVar2 != 0) {
      _SD_Buffer_Clear();
      _SD_Decode_Close(*piVar2);
      *piVar2 = 0;
    }
    iVar1 = FUN_00011f50(piVar2 + 0x24);
    ak_thread_mutex_destroy(piVar2 + 0x27);
    if ((FILE *)piVar2[0x18] != (FILE *)0x0) {
      fclose((FILE *)piVar2[0x18]);
      piVar2[0x18] = 0;
      piVar2[0x19] = 0;
      piVar2[0x1a] = 0;
    }
    if ((FILE *)piVar2[0x1b] != (FILE *)0x0) {
      fclose((FILE *)piVar2[0x1b]);
      piVar2[0x1b] = 0;
      piVar2[0x1c] = 0;
      piVar2[0x1d] = 0;
    }
    if ((FILE *)piVar2[0x1e] != (FILE *)0x0) {
      fclose((FILE *)piVar2[0x1e]);
      piVar2[0x1e] = 0;
      piVar2[0x1f] = 0;
      piVar2[0x20] = 0;
    }
    if ((FILE *)piVar2[0x21] != (FILE *)0x0) {
      fclose((FILE *)piVar2[0x21]);
      piVar2[0x21] = 0;
      piVar2[0x22] = 0;
      piVar2[0x23] = 0;
    }
    ak_mem_free(piVar2);
    DAT_00026048 = DAT_00026048 + -1;
    (&DAT_00026038)[param_1] = 0;
    ak_print(0x10,3,"[%s:%d] dec_ctrl.user_count=%d\n","ak_adec_close",0x54f,DAT_00026048);
  }
  ak_thread_rwlock_unlock(DAT_00026034);
  return iVar1;
}



int ak_adec_save_file(uint param_1,uint *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *__file;
  uint *__s;
  stat sStack_78;
  
  ak_print(0x10,4,"[%s:%d] enter\n","ak_adec_save_file",0x55f);
  if (param_2 == (uint *)0x0) {
    ak_print(0x10,1,"[%s:%d] save_file_info is NULL\n","check_save_file_param",0x92);
    return 0x100;
  }
  if (*param_2 < 2) {
    if (0xb3 < param_2[0x81] - 1) {
      ak_print(0x10,1,"[%s:%d] save_second = %d, invalid, must in [1~180]\n","check_save_file_param"
               ,0x9b,param_2[0x81]);
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
              ak_thread_rwlock_wrlock(DAT_00026034);
              if (param_1 < 4) {
                iVar1 = (&DAT_00026038)[param_1];
              }
              else {
                iVar1 = FUN_00011f08(param_1);
              }
              if (iVar1 == 0) {
                ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_save_file",0x569);
                iVar3 = 0x10000004;
              }
              else {
                iVar3 = 0;
                if (*param_2 != 0) {
                  iVar3 = FUN_00011a28(iVar1,(char *)__file,(char *)__s);
                  if (iVar3 == 0) {
                    uVar4 = ((*(uint *)(iVar1 + 8) >> 3) *
                            *(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 4) * param_2[0x81]) / 1000;
                    if ((uVar4 & 1) != 0) {
                      uVar4 = uVar4 + 1;
                    }
                    iVar5 = uVar4 * 1000;
                    *(int *)(iVar1 + 100) = iVar5;
                    *(int *)(iVar1 + 0x70) = iVar5;
                    *(int *)(iVar1 + 0x7c) = iVar5;
                    *(int *)(iVar1 + 0x88) = iVar5;
                    *(undefined4 *)(iVar1 + 0x74) = 0;
                    *(undefined4 *)(iVar1 + 0x68) = 0;
                    *(undefined4 *)(iVar1 + 0x80) = 0;
                    *(undefined4 *)(iVar1 + 0x8c) = 0;
                  }
                  else {
                    ak_print(0x10,1,"[%s:%d] dev is NULL!\n","ak_adec_save_file",0x571);
                  }
                }
              }
              ak_thread_rwlock_unlock(DAT_00026034);
              ak_print(0x10,4,"[%s:%d] leave...\n","ak_adec_save_file",0x583);
              return iVar3;
            }
            ak_print(0x10,1,"[%s:%d] file_name = %s, invalid\n","check_save_file_param",0xb4,__s);
          }
          else {
            ak_print(0x10,1,"[%s:%d] file_path = %s, invalid\n","check_save_file_param",0xaf,__file)
            ;
          }
        }
        else {
          ak_print(0x10,1,"[%s:%d] path can not write. path:%s\n","check_save_file_param",0xa9,
                   __file);
        }
      }
      else {
        ak_print(0x10,1,"[%s:%d] path is not dir. path:%s\n","check_save_file_param",0xa5,__file);
      }
    }
    else {
      ak_print(0x10,1,"[%s:%d] stat error. path:%s, error\n","check_save_file_param",0xa1,__file);
    }
  }
  else {
    ak_print(0x10,1,"[%s:%d] enable = %d, invalid\n","check_save_file_param",0x96,*param_2);
  }
  return 0x101;
}



void ak_adec_get_codec_info(void)

{
  _SD_GetAudioCodecVersionInfo();
  return;
}



undefined4 ak_adec_get_buf_status(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  if (param_2 != (undefined4 *)0x0) {
    memset(param_2,0,8);
    ak_thread_rwlock_rdlock(DAT_00026034);
    if (param_1 < 4) {
      puVar2 = (undefined4 *)(&DAT_00026038)[param_1];
    }
    else {
      puVar2 = (undefined4 *)FUN_00011f08(param_1);
    }
    if (puVar2 == (undefined4 *)0x0) {
      ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_get_buf_status",0x5a5);
      uVar3 = 0x10000004;
    }
    else {
      iVar1 = _SD_Get_Input_Buf_Info(*puVar2,1);
      if (iVar1 < 0) {
        ak_print(0x10,1,"[%s:%d] _SD_Get_Input_Buf_Info failed\n","ak_adec_get_buf_status",0x5ac);
        uVar3 = 0x10000006;
      }
      else {
        if (*(char *)(puVar2 + 5) == '\x01') {
          iVar1 = 0;
        }
        ak_print(0x10,5,"[%s:%d] decode_buf_len=%ld, decode_remain=%ld, adec_status=%d\n",
                 "ak_adec_get_buf_status",0x5b4,0x5000,iVar1,*(char *)(puVar2 + 5));
        uVar3 = 0;
        param_2[1] = iVar1;
        *param_2 = 0x5000;
      }
    }
    ak_thread_rwlock_unlock(DAT_00026034);
    return uVar3;
  }
  ak_print(0x10,5,"[%s:%d] buf_status is NULL\n","ak_adec_get_buf_status",0x59b);
  return 0x100;
}



undefined4 ak_adec_set_aac_dec_param(uint param_1,ushort *param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  if (param_2 == (ushort *)0x0) {
    ak_print(0x10,1,"[%s:%d] dec_param is NULL\n","ak_adec_set_aac_dec_param",0x5c7);
    return 0x100;
  }
  if (*param_2 < 4) {
    ak_thread_rwlock_wrlock(DAT_00026034);
    if (param_1 < 4) {
      piVar2 = (int *)(&DAT_00026038)[param_1];
    }
    else {
      piVar2 = (int *)FUN_00011f08(param_1);
    }
    if (piVar2 == (int *)0x0) {
      ak_print(0x10,1,"[%s:%d] adec user is NULL\n","ak_adec_set_aac_dec_param",0x5d4);
      uVar3 = 0x10000004;
    }
    else if (piVar2[0x14] < 1) {
      *(ushort *)(piVar2 + 0x2d) = *param_2;
      FUN_000123c8(piVar2);
      iVar1 = FUN_00011fc8(piVar2 + 1,piVar2);
      if (iVar1 == 0) {
        uVar3 = 0;
      }
      else {
        ak_print(0x10,1,"[%s:%d] open decode lib failed\n","ak_adec_set_aac_dec_param",0x5e2);
        uVar3 = 0x10000000;
      }
    }
    else {
      ak_print(0x10,1,"[%s:%d] send stream begin, can not set aac_dec_param\n",
               "ak_adec_set_aac_dec_param",0x5da);
      uVar3 = 0x10000004;
    }
    ak_thread_rwlock_unlock(DAT_00026034);
    return uVar3;
  }
  ak_print(0x10,1,"[%s:%d] dec_param->stream_format must in 0~3\n","ak_adec_set_aac_dec_param",0x5cb
          );
  return 0x101;
}



void _fini(void)

{
  return;
}


