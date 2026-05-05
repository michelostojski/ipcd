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
typedef pointer pointer __((offset(0x8)));

typedef pointer pointer __((offset(0x18)));

typedef pointer pointer __((offset(0x10)));

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

typedef struct timeval timeval, *Ptimeval;

typedef long __suseconds_t;

struct timeval {
    __time_t tv_sec;
    __suseconds_t tv_usec;
};

typedef struct _IO_FILE FILE;

typedef long __fd_mask;

typedef struct fd_set fd_set, *Pfd_set;

struct fd_set {
    __fd_mask fds_bits[32];
};

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

struct evp_pkey_ctx_st {
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



char DAT_0002c0c0;
pointer __DT_PLTGOT;
undefined4 DAT_0002c054;
dword DWORD_0001b030;
undefined __register_frame_info;
undefined DAT_0002c0c4;
undefined4 DAT_0002c05c;
undefined4 DAT_0002c064;
int *DAT_0002c068;
undefined DAT_000197c8;
int DAT_0002c058;
int *DAT_0002c060;
undefined vi_dev_close_td_chn;
undefined4 g_stop_flag;
undefined DAT_0002c0e8;
undefined DAT_0002c0ec;
undefined4 DAT_0002c06c;
undefined *PTR_s_/dev/video-0-2_0001a414;
undefined fcntl;
undefined4 DAT_0002c07c;
undefined DAT_0002c118;
undefined open;
undefined DAT_0001a428;
undefined8 g_sensor_fd;
int DAT_0002c07c;
int DAT_0002c080;
undefined4 DAT_0002c1a8;
undefined DAT_0002c1ac;
undefined4 DAT_0002c1b4;
undefined4 DAT_0002c1b8;
undefined ak_mem_free;
undefined4 DAT_0002c1e4;
undefined DAT_0002c1ec;
undefined ioctl;
undefined ak_mem_dma_vaddr2paddr;
undefined *td_v4l2_frame_list;
undefined DAT_0002c240;
undefined DAT_0002c250;
undefined DAT_0002c254;
undefined DAT_0002c280;
undefined DAT_0002c288;
undefined DAT_0002c360;
char *DAT_0002c23c;
undefined4 DAT_0002c23c;
undefined v4l2_frame_list;
uint DAT_0002c080;
uint DAT_0002c07c;
int DAT_0002c380;
int DAT_0002c37c;
int DAT_0002c378;
undefined *PTR_td_v4l2_frame_list_0002c090;
undefined DAT_0002c0a0;
undefined4 DAT_0002c1e8;
undefined DAT_0002c284;
undefined DAT_0002c368;
undefined DAT_0002c384;
undefined isp_3D_NR_create;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



undefined4 * vi_find_device(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = vi_find_device(param_1);
  return puVar1;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



undefined4 vi_dev_release_frame(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = vi_dev_release_frame(param_1,param_2,param_3);
  return uVar1;
}



int isp_sensor_ioctl(int param_1,ulong param_2,int param_3)

{
  int iVar1;
  
  iVar1 = isp_sensor_ioctl(param_1,param_2,param_3);
  return iVar1;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



void * vi_register_channel(undefined4 param_1)

{
  void *pvVar1;
  
  pvVar1 = vi_register_channel(param_1);
  return pvVar1;
}



undefined4
vi_dev_td_chn_capture_on(int param_1,int param_2,uint param_3,undefined4 param_4,uint param_5)

{
  undefined4 uVar1;
  
  uVar1 = vi_dev_td_chn_capture_on(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}



int vi_set_third_chn_attr(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = vi_set_third_chn_attr(param_1,param_2);
  return iVar1;
}



undefined4 vi_dev_td_chn_capture_off(undefined4 param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = vi_dev_td_chn_capture_off(param_1,param_2,param_3,param_4);
  return uVar1;
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



// WARNING: Removing unreachable block (ram,0x000124ac)
// WARNING: Removing unreachable block (ram,0x000124c4)
// WARNING: Removing unreachable block (ram,0x000124cc)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (DAT_0002c0c0 == '\0') {
    __cxa_finalize(DAT_0002c054);
    entry();
    if (ppuVar1[0x10] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_0001b030);
    }
    DAT_0002c0c0 = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00012510)
// WARNING: Removing unreachable block (ram,0x00012528)
// WARNING: Removing unreachable block (ram,0x00012530)
// WARNING: Removing unreachable block (ram,0x00012618)
// WARNING: Removing unreachable block (ram,0x0001262c)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_0001b030,&DAT_0002c0c4,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



undefined4 FUN_00012654(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  bool bVar8;
  bool bVar9;
  undefined1 auStack_618 [1540];
  
  if (param_1 == (undefined4 *)0x0 || param_2 == 0) {
    return 0xffffffff;
  }
  iVar1 = *(int *)(param_2 + 0x18);
  iVar4 = *(int *)(param_2 + 0x1c);
  iVar6 = *(int *)(param_2 + 0x10);
  if ((iVar1 == 0 && iVar4 == 0) || (iVar6 == 0)) {
    ak_print(7,2,"[%s:%d] entry: %p ts=%llu main_len=%u seq=%lu\n","vi_to_channel",0x693,param_2,
             iVar1,iVar4,iVar6,*(undefined4 *)(param_2 + 0x20));
    iVar6 = *(int *)(param_2 + 0x10);
    iVar1 = *(int *)(param_2 + 0x18);
    iVar4 = *(int *)(param_2 + 0x1c);
  }
  uVar7 = *(undefined4 *)(param_2 + 0xc);
  uVar2 = *(undefined4 *)(param_2 + 0x20);
  uVar5 = *(undefined4 *)(param_2 + 0x34);
  param_1[1] = iVar6;
  param_1[2] = iVar1;
  param_1[3] = iVar4;
  *param_1 = uVar7;
  param_1[4] = uVar2;
  param_1[6] = uVar5;
  param_1[8] = 0;
  pvVar3 = memset(auStack_618,0,0x600);
  bVar9 = SBORROW4(param_3,0x10);
  iVar1 = param_3 + -0x10;
  bVar8 = param_3 != 0x10;
  if (bVar8) {
    bVar9 = SBORROW4(param_3,1);
    iVar1 = param_3 + -1;
  }
  if ((bVar8 && param_3 != 1) && iVar1 < 0 == bVar9) {
    pvVar3 = (void *)0x1;
  }
  if ((!bVar8 || param_3 == 1) || iVar1 < 0 != bVar9) {
    pvVar3 = (void *)0x0;
  }
  iVar1 = ak_vpss_md_get_stat(pvVar3,auStack_618);
  if (iVar1 == 0) {
    uVar2 = ak_get_os_timestamp();
    pvVar3 = (void *)ak_mem_alloc_(7,0x600,"vi_to_channel",uVar2);
    param_1[8] = pvVar3;
    if (pvVar3 != (void *)0x0) {
      memcpy(pvVar3,auStack_618,0x600);
      return 0;
    }
  }
  return 0;
}



undefined4 FUN_000127c0(int param_1,void *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  memcpy((void *)(param_1 + 8),param_2,0x14);
  iVar1 = vi_dev_set_chn_res(*(int *)(param_1 + 4),*(undefined4 *)((int)param_2 + 8),
                             *(undefined4 *)((int)param_2 + 0xc),param_3);
  if (iVar1 == 0) {
    ak_print(7,4,"[%s:%d] set vi channel[%d] res w[%d] h[%d]\n","vi_set_channel_attr",0x322,
             *(undefined4 *)(param_1 + 4),*(undefined4 *)((int)param_2 + 8),
             *(undefined4 *)((int)param_2 + 0xc));
    if (*(int *)(param_1 + 4) - 0x10U < 2) {
      uVar2 = 0;
    }
    else {
      uVar2 = vi_dev_set_chn_enable();
    }
  }
  else {
    ak_print(7,1,"[%s:%d] Failed to set vi channel[%d] res w[%d] h[%d]\n","vi_set_channel_attr",
             0x325,*(undefined4 *)(param_1 + 4),*(undefined4 *)((int)param_2 + 8),
             *(undefined4 *)((int)param_2 + 0xc));
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



int FUN_000128b8(int param_1,undefined4 *param_2,uint param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  pcVar1 = (char *)*param_2;
  if (((uint)pcVar1 & 1) == 0) {
    iVar3 = *(int *)(param_1 + 0x30);
    iVar2 = *(int *)(param_1 + 0x34);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x3c);
    iVar2 = *(int *)(param_1 + 0x40);
  }
  iVar3 = iVar3 * iVar2;
  if (pcVar1 + -0x10 < (char *)0x2) {
    iVar3 = (*(int *)(param_1 + 0x40) / 2) * (*(int *)(param_1 + 0x3c) / 2);
  }
  iVar3 = vi_dev_capture_on(*(int *)(param_1 + 4),pcVar1,1,(iVar3 * 3) / 2 + 0x680,param_3);
  if (iVar3 == 0) {
    ak_print(7,3,"[%s:%d] vi channel [%d] is started!\n","vi_set_capture_on",0x495,*param_2);
    return 0;
  }
  ak_print(7,1,"[%s:%d] vi channel [%d] capture on failed!\n","vi_set_capture_on",0x498,*param_2);
  return iVar3;
}



undefined4 FUN_000129c4(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  ak_print(7,5,"[%s:%d] enter...\n","vi_set_capture_off",0x4a5);
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = vi_dev_capture_off(*param_1,param_2[1],3,param_2[6]);
    ak_print(7,3,"[%s:%d] channel [%d] capture off, ret [%d], pchn->status[%d]\n",
             "vi_set_capture_off",0x4b6,param_2[1],uVar1,*param_2);
    ak_print(7,5,"[%s:%d] leave..., ret=%d\n","vi_set_capture_off",0x4b8,uVar1);
  }
  return uVar1;
}



char * ak_vi_get_version(void)

{
  return "libplat_vi V3.0.02";
}



undefined4 * vi_find_device(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((undefined4 **)DAT_0002c05c != &DAT_0002c05c) {
    iVar1 = DAT_0002c05c[-0x10];
    puVar2 = DAT_0002c05c;
    while( true ) {
      if (param_1 == iVar1) {
        ak_print(7,5,"[%s:%d] old device\n","vi_find_device",0xae);
        return puVar2 + -0x11;
      }
      puVar2 = (undefined4 *)(puVar2 + -0x11)[0x11];
      if ((undefined4 **)puVar2 == &DAT_0002c05c) break;
      iVar1 = puVar2[-0x10];
    }
  }
  return (undefined4 *)0x0;
}



undefined4 * vi_find_channel(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
    iVar1 = DAT_0002c064[-6];
    puVar2 = DAT_0002c064;
    while( true ) {
      if (iVar1 == param_1) {
        return puVar2 + -7;
      }
      puVar2 = (undefined4 *)(puVar2 + -7)[7];
      if ((undefined4 **)puVar2 == &DAT_0002c064) break;
      iVar1 = puVar2[-6];
    }
  }
  return (undefined4 *)0x0;
}



void * vi_register_channel(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  void *__s;
  
  uVar2 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(7,0x38,"vi_register_channel",uVar2);
  if (__s == (void *)0x0) {
    ak_print(7,1,&DAT_000197c8,"vi_register_channel",0xd2);
  }
  else {
    memset(__s,0,0x38);
    *(undefined4 *)((int)__s + 4) = param_1;
    *(int **)((int)__s + 0x20) = DAT_0002c068;
    *(undefined4 **)((int)__s + 0x1c) = &DAT_0002c064;
    piVar1 = (int *)((int)__s + 0x1c);
    *DAT_0002c068 = (int)__s + 0x1c;
    DAT_0002c068 = piVar1;
    *(undefined4 *)((int)__s + 0x24) = 0;
    *(undefined4 *)((int)__s + 0x28) = 0;
    *(undefined4 *)((int)__s + 0x2c) = 0;
    *(int *)((int)__s + 0x30) = (int)__s + 0x30;
    *(int *)((int)__s + 0x34) = (int)__s + 0x30;
  }
  return __s;
}



undefined4 ak_vi_open(uint param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  void *__s;
  int iVar4;
  void *pvVar5;
  uint uVar6;
  void *pvVar7;
  char acStack_58 [64];
  
  if (param_1 < 2) {
    uVar6 = param_1;
    ak_print(7,3,"[%s:%d] register device, device id:[%d]\n","ak_vi_open",0x184,param_1);
    puVar3 = vi_find_device(param_1);
    if (puVar3 != (undefined4 *)0x0) {
      ak_print(7,4,"old device\n");
LAB_00012ce4:
      isp_fps_main(param_1);
      memset(acStack_58,0,0x40);
      memset(acStack_58,0,0x40);
      snprintf(acStack_58,0x40,"vi_version=%s","libplat_vi V3.0.02");
      ak_debug_info(7,1,acStack_58);
      memset(acStack_58,0,0x40);
      snprintf(acStack_58,0x40,"vi%d=opened",param_1);
      ak_debug_info(7,1,acStack_58);
      return 0;
    }
    ak_print(7,4,"new device\n");
    uVar2 = ak_get_os_timestamp();
    __s = (void *)ak_mem_alloc_(7,0x4c,"vi_register_device",uVar2);
    if (__s == (void *)0x0) {
      ak_print(7,1,"[%s:%d] No memory\n","vi_register_device",0x108);
    }
    else {
      memset(__s,0,0x4c);
      uVar2 = 0x10d;
      pvVar7 = __s;
      ak_print(7,4,"[%s:%d] new dev=%p\n","vi_register_device",0x10d,__s);
      iVar4 = isp_open(param_1);
      if (iVar4 == 0) {
        iVar4 = vi_dev_open(param_1);
        if (iVar4 != -1) {
          if (param_1 == 1) {
            pvVar5 = (void *)0x11;
          }
          else {
            pvVar5 = (void *)0x10;
          }
          iVar4 = vi_dev_open_td_chn((int)pvVar5);
          if (iVar4 != 0) {
            uVar2 = 300;
            ak_print(7,1,"[%s:%d] Open channel [%d] device failed!\n","vi_register_device",300,
                     pvVar5);
            pvVar7 = pvVar5;
          }
          DAT_0002c058 = DAT_0002c058 + 1;
          *(uint *)((int)__s + 4) = param_1;
          *(int **)((int)__s + 0x48) = DAT_0002c060;
          *(undefined4 **)((int)__s + 0x44) = &DAT_0002c05c;
          piVar1 = (int *)((int)__s + 0x44);
          *DAT_0002c060 = (int)__s + 0x44;
          DAT_0002c060 = piVar1;
          ak_print(7,4,"register vi device ok, dev_count=%d\n",DAT_0002c058,uVar2,pvVar7);
          goto LAB_00012ce4;
        }
        isp_close(param_1);
        ak_mem_free(__s);
        ak_print(7,1,"[%s:%d] dev id[%d] open failed!\n","vi_register_device",0x11f,param_1);
        uVar6 = param_1;
      }
      else {
        ak_mem_free(__s);
        ak_print(7,1,"[%s:%d] isp open device %d failed\n","vi_register_device",0x114,param_1);
        uVar6 = param_1;
      }
    }
    ak_print(7,1,"[%s:%d] register video device failed!\n","ak_vi_open",0x188,uVar6);
    uVar2 = 0x7000007;
  }
  else {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_open",0x180,param_1);
    uVar2 = 0x7000000;
  }
  return uVar2;
}



undefined4 ak_vi_close(uint param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 extraout_r1;
  int *piVar3;
  undefined4 extraout_r2;
  undefined4 **ppuVar4;
  undefined4 *puVar5;
  undefined4 **ppuVar6;
  undefined4 **ppuVar7;
  undefined4 *puVar8;
  
  ak_print(7,3,"[%s:%d] enter close vi\n","ak_vi_close",0x1a8);
  if (1 < param_1) {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_close",0x1ae,param_1);
    return 0x7000000;
  }
  piVar1 = vi_find_device(param_1);
  if (piVar1 == (int *)0x0) {
    ak_print(7,1,"[%s:%d] Can\'t find the video device according to the dev id[%d]\n","ak_vi_close",
             0x1f1,param_1);
    return 0x7000001;
  }
  if (*piVar1 != 0) {
    ak_print(7,1,"[%s:%d] the device [%d] is not disabled yet!\n","ak_vi_close",0x1ba,param_1);
    return 0x7000006;
  }
  iVar2 = piVar1[1];
  if (iVar2 != 0) {
    if (iVar2 != 1) goto LAB_00013044;
    if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
      ppuVar7 = (undefined4 **)(DAT_0002c064 + -7);
      ppuVar6 = ppuVar7;
      if (DAT_0002c064[-6] != 2) {
        do {
          ppuVar4 = (undefined4 **)ppuVar6[7];
          ppuVar6 = ppuVar4 + -7;
          if (ppuVar4 == &DAT_0002c064) {
            ppuVar6 = (undefined4 **)0x0;
            break;
          }
        } while (ppuVar4[-6] != (undefined4 *)0x2);
        if (DAT_0002c064[-6] == 3) goto LAB_00013190;
      }
      do {
        ppuVar4 = (undefined4 **)ppuVar7[7];
        ppuVar7 = ppuVar4 + -7;
        if (ppuVar4 == &DAT_0002c064) goto LAB_00013228;
      } while (ppuVar4[-6] != (undefined4 *)0x3);
      goto LAB_00013190;
    }
    goto LAB_0001344c;
  }
  if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
    ppuVar7 = (undefined4 **)(DAT_0002c064 + -7);
    ppuVar6 = ppuVar7;
    if (DAT_0002c064[-6] != 0) {
      do {
        ppuVar4 = (undefined4 **)ppuVar6[7];
        ppuVar6 = ppuVar4 + -7;
        if (ppuVar4 == &DAT_0002c064) {
          ppuVar6 = (undefined4 **)0x0;
          break;
        }
      } while (ppuVar4[-6] != (undefined4 *)0x0);
      if (DAT_0002c064[-6] == 1) goto LAB_00013190;
    }
    do {
      ppuVar4 = (undefined4 **)ppuVar7[7];
      ppuVar7 = ppuVar4 + -7;
      if (ppuVar4 == &DAT_0002c064) goto LAB_00013228;
    } while (ppuVar4[-6] != (undefined4 *)0x1);
LAB_00013190:
    if (ppuVar6 == (undefined4 **)0x0) {
      if (ppuVar7 == (undefined4 **)0x0) goto LAB_00013044;
      puVar5 = *ppuVar7;
      if (puVar5 != (undefined4 *)0x0) {
LAB_000132d4:
        ak_print(7,1,"[%s:%d] Device sub channel[%d] is not disable, status [%d]!\n","ak_vi_close",
                 0x1d4,ppuVar7[1],puVar5);
        return 0x700000c;
      }
    }
    else {
      puVar5 = *ppuVar6;
      if (puVar5 != (undefined4 *)0x0) {
LAB_0001326c:
        ak_print(7,1,"[%s:%d] Device main channel[%d] is not disable, status [%d]!\n","ak_vi_close",
                 0x1cf,ppuVar6[1],puVar5);
        return 0x700000c;
      }
      if (ppuVar7 == (undefined4 **)0x0) goto LAB_0001323c;
      puVar5 = *ppuVar7;
      if (puVar5 != (undefined4 *)0x0) goto LAB_000132d4;
      puVar5 = ppuVar6[8];
      puVar8 = ppuVar6[7];
      puVar8[1] = puVar5;
      *puVar5 = puVar8;
      ppuVar6[7] = ppuVar6 + 7;
      ppuVar6[8] = ppuVar6 + 7;
      ak_mem_free(ppuVar6);
    }
    puVar8 = ppuVar7[8];
    puVar5 = ppuVar7[7];
    puVar5[1] = puVar8;
    *puVar8 = puVar5;
    ppuVar7[7] = ppuVar7 + 7;
    ppuVar7[8] = ppuVar7 + 7;
    ak_mem_free(ppuVar7);
    iVar2 = piVar1[1];
    goto LAB_00013044;
  }
LAB_00013304:
  if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00013340:
    iVar2 = 0;
    goto LAB_00013058;
  }
  puVar5 = (undefined4 *)DAT_0002c064[-6];
  ppuVar6 = (undefined4 **)DAT_0002c064;
  while (ppuVar6 = ppuVar6 + -7, puVar5 != (undefined4 *)0x10) {
    ppuVar6 = (undefined4 **)ppuVar6[7];
    if (ppuVar6 == &DAT_0002c064) goto LAB_00013340;
    puVar5 = ppuVar6[-6];
  }
LAB_000133c0:
  if (*ppuVar6 != (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d] Device third channel[%d] is not disable, status [%d]!\n","ak_vi_close",
             0x1e8,ppuVar6[1],*ppuVar6);
    return 0x700000c;
  }
  puVar5 = ppuVar6[8];
  puVar8 = ppuVar6[7];
  puVar8[1] = puVar5;
  *puVar5 = puVar8;
  ppuVar6[7] = ppuVar6 + 7;
  ppuVar6[8] = ppuVar6 + 7;
  ak_mem_free(ppuVar6);
  iVar2 = piVar1[1];
LAB_00013058:
  isp_close(iVar2);
  if (piVar1[1] == 1) {
    iVar2 = 0x11;
  }
  else {
    iVar2 = 0x10;
  }
  vi_dev_close_td_chn(iVar2,extraout_r1,extraout_r2,vi_dev_close_td_chn);
  vi_dev_close(piVar1[1]);
  if (piVar1[2] != 0) {
    ak_mem_dma_free();
    piVar1[2] = 0;
  }
  piVar3 = (int *)piVar1[0x12];
  iVar2 = piVar1[0x11];
  DAT_0002c058 = DAT_0002c058 + -1;
  *(int **)(iVar2 + 4) = piVar3;
  *piVar3 = iVar2;
  piVar1[0x11] = (int)(piVar1 + 0x11);
  piVar1[0x12] = (int)(piVar1 + 0x11);
  ak_mem_free(piVar1);
  ak_print(7,4,"[%s:%d] unregister done\n","vi_unregister_device",0x171);
  if (param_1 == 0) {
    ak_debug_info(7,1,"vi0=closed");
    ak_debug_info(7,1,"vi0_load_cfg=false");
  }
  else {
    ak_debug_info(7,1,"vi1=closed");
    ak_debug_info(7,1,"vi1_load_cfg=false");
  }
  return 0;
LAB_00013228:
  if (ppuVar6 != (undefined4 **)0x0) {
    puVar5 = *ppuVar6;
    if (puVar5 != (undefined4 *)0x0) goto LAB_0001326c;
LAB_0001323c:
    puVar5 = ppuVar6[8];
    puVar8 = ppuVar6[7];
    puVar8[1] = puVar5;
    *puVar5 = puVar8;
    ppuVar6[7] = ppuVar6 + 7;
    ppuVar6[8] = ppuVar6 + 7;
    ak_mem_free(ppuVar6);
    iVar2 = piVar1[1];
  }
LAB_00013044:
  if (iVar2 == 0) goto LAB_00013304;
  if (iVar2 != 1) goto LAB_00013058;
LAB_0001344c:
  if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
    iVar2 = 1;
    goto LAB_00013058;
  }
  puVar5 = (undefined4 *)DAT_0002c064[-6];
  ppuVar6 = (undefined4 **)DAT_0002c064;
  while (ppuVar6 = ppuVar6 + -7, puVar5 != (undefined4 *)0x11) {
    ppuVar6 = (undefined4 **)ppuVar6[7];
    if (ppuVar6 == &DAT_0002c064) {
      iVar2 = 1;
      goto LAB_00013058;
    }
    puVar5 = ppuVar6[-6];
  }
  goto LAB_000133c0;
}



undefined4 ak_vi_load_sensor_cfg(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char *pcVar3;
  
  if (param_1 < 2) {
    puVar2 = vi_find_device(param_1);
    if (puVar2 != (undefined4 *)0x0) {
      if (param_1 == 0) {
        pcVar3 = "vi0_load_cfg=true";
      }
      else {
        pcVar3 = "vi1_load_cfg=true";
      }
      ak_debug_info(7,1,pcVar3);
      uVar1 = isp_match_sensor_cfgfile(param_1,param_2);
      return uVar1;
    }
    ak_print(7,1,"[%s:%d] Can\'t find the video device according to the dev id[%d]\n",
             "ak_vi_load_sensor_cfg",0x21a,param_1);
    uVar1 = 0x7000001;
  }
  else {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_load_sensor_cfg",0x214,param_1);
    uVar1 = 0x7000000;
  }
  return uVar1;
}



undefined4 ak_vi_get_sensor_resolution(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    if (param_1 < 2) {
      puVar2 = vi_find_device(param_1);
      if (puVar2 == (undefined4 *)0x0) {
        ak_print(7,1,"[%s:%d] Can\'t find the video device according to the dev id[%d]\n",
                 "ak_vi_get_sensor_resolution",0x23e,param_1);
        uVar1 = 0x7000001;
      }
      else {
        uVar1 = vi_dev_get_sensor_crop(param_1,param_2,param_2 + 1);
      }
    }
    else {
      ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_get_sensor_resolution",0x238,param_1);
      uVar1 = 0x7000000;
    }
    return uVar1;
  }
  ak_print(7,1,"[%s:%d] Input res is NULL!\n","ak_vi_get_sensor_resolution",0x232);
  return 0x101;
}



undefined4 ak_vi_get_dev_attr(uint param_1,void *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_1 < 2) {
    if (param_2 != (void *)0x0) {
      puVar2 = DAT_0002c05c;
      if ((undefined4 **)DAT_0002c05c != &DAT_0002c05c) {
        do {
          if (param_1 == puVar2[-0x10]) {
            memcpy(param_2,puVar2 + -0xe,0x38);
            return 0;
          }
          puVar2 = (undefined4 *)*puVar2;
        } while ((undefined4 **)puVar2 != &DAT_0002c05c);
      }
      ak_print(7,1,"[%s:%d] Can\'t find the video device according to the dev id[%d]\n",
               "ak_vi_get_dev_attr",0x30e,param_1);
      return 0x7000001;
    }
    ak_print(7,1,"[%s:%d] dev_attr is NULL!\n","ak_vi_get_dev_attr",0x305);
    uVar1 = 0x101;
  }
  else {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_get_dev_attr",0x2ff,param_1);
    uVar1 = 0x7000000;
  }
  return uVar1;
}



undefined4 ak_vi_get_chn_attr(int param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if ((param_1 < 0) || (3 < param_1 && 1 < param_1 - 0x10U)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_get_chn_attr",0x33e,param_1);
    uVar1 = 0x7000004;
  }
  else {
    if (param_2 != (void *)0x0) {
      if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
        iVar2 = DAT_0002c064[-6];
        puVar3 = DAT_0002c064;
        while( true ) {
          if (param_1 == iVar2) {
            memcpy(param_2,puVar3 + -5,0x14);
            return 0;
          }
          puVar3 = (undefined4 *)*puVar3;
          if ((undefined4 **)puVar3 == &DAT_0002c064) break;
          iVar2 = puVar3[-6];
        }
      }
      ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_get_chn_attr",0x34c,param_1);
      return 0x700000a;
    }
    ak_print(7,1,"[%s:%d]  channel attribute argement is invalid!\n","ak_vi_get_chn_attr",0x344);
    uVar1 = 0x101;
  }
  return uVar1;
}



int vi_set_third_chn_attr(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *param3;
  char acStack_60 [68];
  
  if ((undefined4 *)0x1 < param_1 + -4) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","vi_set_third_chn_attr",0x363,param_1);
    return 0x7000004;
  }
  if (param_2 == (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d]  channel attribute argement is invalid!\n","vi_set_third_chn_attr",0x369);
    return 0x101;
  }
  param3 = (undefined4 *)*param_2;
  if (param3 != param_1) {
    ak_print(7,1,"[%s:%d] chn id [%d] is not match the chn id in attr[%d]\n","vi_set_third_chn_attr"
             ,0x370,param_1,param3);
    return 0x700000d;
  }
  if (param3 == (undefined4 *)0x10) {
    puVar1 = vi_find_device(0);
    if (puVar1 != (undefined4 *)0x0) {
      puVar9 = (undefined4 *)0x1;
      goto LAB_000139ec;
    }
  }
  else {
    puVar1 = vi_find_device(1);
    if (puVar1 != (undefined4 *)0x0) {
      puVar9 = (undefined4 *)0x3;
LAB_000139ec:
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00013a30:
        ak_print(7,1,"[%s:%d] Channel [%d] is master Channel[%d] is not resigter yet!\n",
                 "vi_set_third_chn_attr",0x38e,param3,puVar9);
        return 0x700000a;
      }
      puVar3 = DAT_0002c064 + -7;
      puVar2 = (undefined4 *)DAT_0002c064[-6];
      puVar5 = puVar3;
      for (puVar7 = puVar2; puVar7 != puVar9; puVar7 = (undefined4 *)puVar7[-6]) {
        puVar7 = (undefined4 *)puVar5[7];
        puVar5 = puVar7 + -7;
        if ((undefined4 **)puVar7 == &DAT_0002c064) goto LAB_00013a30;
      }
      if ((param_2[2] != (int)puVar5[4] / 2) || (param_2[3] != (int)puVar5[5] / 2)) {
        ak_print(7,1,
                 "[%s:%d] the channel resolution param w:[%d] h:[%d] is invalid, should be half of sub chn:[%d]h:[%d]!\n"
                 ,"vi_set_third_chn_attr",0x39a,param_2[2],param_2[3],puVar5[4],puVar5[5]);
        return 0x101;
      }
      if (2 < param_2[4] - 2) {
        ak_print(7,1,"[%s:%d] the channel frame depth [%d] is out of range [%d - %d]\n",
                 "vi_set_third_chn_attr",0x3a1,param_2[4],2,4);
        return 0x101;
      }
      do {
        if (param3 == puVar2) {
LAB_00013b8c:
          iVar4 = FUN_000127c0((int)puVar3,param_2,(uint)(puVar1[7] == 1));
          if (iVar4 == 0) {
            memset(acStack_60,0,0x40);
            memset(acStack_60,0,0x40);
            snprintf(acStack_60,0x40,"chn%d_id=%d",(int)param3,(int)param3);
            ak_debug_info(7,0,acStack_60);
            memset(acStack_60,0,0x40);
            snprintf(acStack_60,0x40,"chn%d_frame_rate=%d",(int)param3,param_2[1]);
            ak_debug_info(7,0,acStack_60);
            memset(acStack_60,0,0x40);
            snprintf(acStack_60,0x40,"chn%d_res=[%d*%d]",(int)param3,param_2[2],param_2[3]);
            ak_debug_info(7,0,acStack_60);
            memset(acStack_60,0,0x40);
            snprintf(acStack_60,0x40,"chn%d_frame_depth=%d",(int)param3,param_2[4]);
            ak_debug_info(7,0,acStack_60);
            return 0;
          }
          piVar8 = (int *)puVar3[8];
          iVar6 = puVar3[7];
          *(int **)(iVar6 + 4) = piVar8;
          *piVar8 = iVar6;
          puVar3[7] = puVar3 + 7;
          puVar3[8] = puVar3 + 7;
          ak_mem_free(puVar3);
          return iVar4;
        }
        puVar9 = (undefined4 *)puVar3[7];
        puVar3 = puVar9 + -7;
        if ((undefined4 **)puVar9 == &DAT_0002c064) {
          puVar3 = vi_register_channel(param3);
          if (puVar3 == (undefined4 *)0x0) {
            ak_print(7,1,"[%s:%d] register vi channel [%d] failed!\n","vi_set_third_chn_attr",0x3b0,
                     param3);
            return 0x7000008;
          }
          ak_print(7,4,"[%s:%d] success register vi channel[%d]\n","vi_set_third_chn_attr",0x3b4,
                   param3);
          goto LAB_00013b8c;
        }
        puVar2 = (undefined4 *)puVar9[-6];
      } while( true );
    }
  }
  ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","vi_set_third_chn_attr",
           0x382,param3);
  return 0x7000009;
}



int ak_vi_set_chn_attr(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *param3;
  uint uVar8;
  uint uVar9;
  char acStack_60 [68];
  
  if (param_1 + -4 < (undefined4 *)0x2) {
    iVar2 = vi_set_third_chn_attr(param_1,param_2);
    return iVar2;
  }
  if ((undefined4 *)0x3 < param_1) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_set_chn_attr",0x3f8,param_1);
    return 0x7000004;
  }
  if (param_2 == (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d]  channel attribute argement is invalid!\n","ak_vi_set_chn_attr",0x3fe);
    return 0x101;
  }
  param3 = (undefined4 *)*param_2;
  if (param3 != param_1) {
    ak_print(7,1,"[%s:%d] chn id [%d] is not match the chn id in attr[%d]\n","ak_vi_set_chn_attr",
             0x405,param_1,param3);
    return 0x700000d;
  }
  puVar1 = vi_find_device((uint)(1 < (int)param3));
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_set_chn_attr",
             0x417,param3);
    return 0x7000009;
  }
  uVar8 = param_2[2] + 0x1f & 0xffffffe0;
  uVar5 = param_2[3] + 7 & 0xfffffff8;
  if (((uint)param_1 & 1) == 0) {
    iVar2 = puVar1[0xc];
    iVar4 = puVar1[0xd];
  }
  else {
    iVar2 = puVar1[0xf];
    iVar4 = puVar1[0x10];
  }
  uVar9 = uVar5;
  if (0x11 < (int)uVar5) {
    uVar9 = uVar8;
  }
  if (iVar4 < (int)uVar5 || (iVar2 < (int)uVar8 || (int)uVar9 < 0x12)) {
    ak_print(7,1,
             "[%s:%d] the channel resolution param w:[%d] h:[%d] is invalid, larger than the max w:[%d]h:[%d]!\n"
             ,"ak_vi_set_chn_attr",0x425,param_2[2],param_2[3],iVar2,iVar4);
    return 0x101;
  }
  if (2 < param_2[4] - 2) {
    ak_print(7,1,"[%s:%d] the channel frame depth [%d] is out of range [%d - %d]\n",
             "ak_vi_set_chn_attr",0x42b,param_2[4],2,4);
    return 0x101;
  }
  uVar9 = param_2[1];
  param_2[2] = uVar8;
  param_2[3] = uVar5;
  if ((int)uVar9 < 0) {
LAB_00013f98:
    ak_print(7,1,"[%s:%d] the channel frame rate [%d] is inavlid! \n","ak_vi_set_chn_attr",0x435,
             uVar9);
    iVar2 = 0x101;
  }
  else {
    if (uVar9 != 0) {
      if ((uVar9 & 0xffff) == 0) goto LAB_00013f98;
      uVar5 = uVar9 >> 0x10;
      if (uVar5 == 0) {
        uVar5 = 1;
      }
      FUN_00018a48(uVar5 * 1000,uVar9 & 0xffff);
      ak_print(7,4,"[%s:%d] chn[%d] frame_rate[%d] frame_num[%d],frame_den[%d], interval[%d]\n",
               "ak_vi_set_chn_attr");
    }
    if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_0001408c:
      puVar3 = vi_register_channel(param3);
      if (puVar3 == (undefined4 *)0x0) {
        ak_print(7,1,"[%s:%d] register vi channel [%d] failed!\n","ak_vi_set_chn_attr",0x44a,param3)
        ;
        return 0x7000008;
      }
      ak_print(7,4,"[%s:%d] success register vi channel[%d]\n","ak_vi_set_chn_attr",0x44e,param3);
    }
    else {
      puVar6 = (undefined4 *)DAT_0002c064[-6];
      puVar7 = DAT_0002c064;
      while (puVar3 = puVar7 + -7, param3 != puVar6) {
        puVar7 = (undefined4 *)*puVar7;
        if ((undefined4 **)puVar7 == &DAT_0002c064) goto LAB_0001408c;
        puVar6 = (undefined4 *)puVar7[-6];
      }
    }
    iVar2 = FUN_000127c0((int)puVar3,param_2,(uint)(puVar1[7] == 1));
    if (iVar2 == 0) {
      memset(acStack_60,0,0x40);
      memset(acStack_60,0,0x40);
      snprintf(acStack_60,0x40,"chn%d_id=%d",(int)param3,(int)param3);
      ak_debug_info(7,0,acStack_60);
      memset(acStack_60,0,0x40);
      snprintf(acStack_60,0x40,"chn%d_frame_rate=%d",(int)param3,param_2[1]);
      ak_debug_info(7,0,acStack_60);
      memset(acStack_60,0,0x40);
      snprintf(acStack_60,0x40,"chn%d_res=[%d*%d]",(int)param3,param_2[2],param_2[3]);
      ak_debug_info(7,0,acStack_60);
      memset(acStack_60,0,0x40);
      snprintf(acStack_60,0x40,"chn%d_frame_depth=%d",(int)param3,param_2[4]);
      ak_debug_info(7,0,acStack_60);
    }
  }
  return iVar2;
}



undefined4 ak_vi_enable_chn(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  char acStack_58 [64];
  
  if (((int)param_1 < 0) || (3 < (int)param_1 && (undefined4 *)0x1 < param_1 + -4)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_enable_chn",0x4cc,param_1);
    uVar1 = 0x7000004;
  }
  else {
    bVar4 = SBORROW4((int)param_1,0x10);
    puVar2 = param_1 + -4;
    if (param_1 != (undefined4 *)0x10) {
      bVar4 = SBORROW4((int)param_1,1);
      puVar2 = (undefined4 *)((int)param_1 + -1);
    }
    puVar2 = vi_find_device((uint)((param_1 != (undefined4 *)0x10 && param_1 != (undefined4 *)0x1)
                                  && (int)puVar2 < 0 == bVar4));
    if (puVar2 != (undefined4 *)0x0) {
      if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
        puVar3 = (undefined4 *)DAT_0002c064[-6];
        puVar2 = DAT_0002c064;
        while( true ) {
          puVar2 = puVar2 + -7;
          if (param_1 == puVar3) {
            ak_print(7,4,"[%s:%d] set channel [%d] capture on\n","ak_vi_enable_chn",0x4ea,param_1);
            puVar2[10] = 0;
            puVar2[0xb] = 0;
            puVar2[9] = 0;
            *puVar2 = 1;
            memset(acStack_58,0,0x40);
            memset(acStack_58,0,0x40);
            snprintf(acStack_58,0x40,"chn%d_status=enabled",(int)param_1);
            ak_debug_info(7,1,acStack_58);
            return 0;
          }
          puVar2 = (undefined4 *)puVar2[7];
          if ((undefined4 **)puVar2 == &DAT_0002c064) break;
          puVar3 = (undefined4 *)puVar2[-6];
        }
      }
      ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_enable_chn",0x4e6,param_1);
      return 0x700000a;
    }
    ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_enable_chn",0x4de
             ,param_1);
    uVar1 = 0x7000009;
  }
  return uVar1;
}



undefined4 ak_vi_disable_chn(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  char acStack_50 [64];
  
  if (((int)param_1 < 0) || (3 < (int)param_1 && (undefined4 *)0x1 < param_1 + -4)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_disable_chn",0x50a,param_1);
    uVar1 = 0x7000004;
  }
  else {
    bVar4 = SBORROW4((int)param_1,0x10);
    puVar2 = param_1 + -4;
    if (param_1 != (undefined4 *)0x10) {
      bVar4 = SBORROW4((int)param_1,1);
      puVar2 = (undefined4 *)((int)param_1 + -1);
    }
    puVar2 = vi_find_device((uint)((param_1 != (undefined4 *)0x10 && param_1 != (undefined4 *)0x1)
                                  && (int)puVar2 < 0 == bVar4));
    if (puVar2 != (undefined4 *)0x0) {
      if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
        puVar3 = (undefined4 *)DAT_0002c064[-6];
        puVar2 = DAT_0002c064;
        while( true ) {
          puVar2 = puVar2 + -7;
          if (param_1 == puVar3) {
            puVar2[10] = 0;
            puVar2[0xb] = 0;
            *puVar2 = 0;
            puVar2[9] = 0;
            memset(acStack_50,0,0x40);
            memset(acStack_50,0,0x40);
            snprintf(acStack_50,0x40,"chn%d_status=disabled",(int)param_1);
            ak_debug_info(7,1,acStack_50);
            return 0;
          }
          puVar2 = (undefined4 *)puVar2[7];
          if ((undefined4 **)puVar2 == &DAT_0002c064) break;
          puVar3 = (undefined4 *)puVar2[-6];
        }
      }
      ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_disable_chn",0x524,param_1);
      return 0x700000a;
    }
    ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_disable_chn",
             0x51c,param_1);
    uVar1 = 0x7000009;
  }
  return uVar1;
}



int ak_vi_enable_dev(uint param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (1 < param_1) {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_enable_dev",0x541,param_1);
    return 0x7000000;
  }
  piVar1 = vi_find_device(param_1);
  if (piVar1 == (int *)0x0) {
    ak_print(7,1,"[%s:%d] the device id [%d] is not open!\n","ak_vi_enable_dev",0x548,param_1);
    return 0x7000001;
  }
  if (*piVar1 == 1) {
    return 0;
  }
  iVar5 = param_1 * 2;
  iVar6 = iVar5;
  if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
    do {
      puVar4 = DAT_0002c064;
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) break;
      while (iVar6 != puVar4[-6]) {
        puVar4 = (undefined4 *)*puVar4;
        if ((undefined4 **)puVar4 == &DAT_0002c064) goto LAB_00014728;
      }
      iVar7 = FUN_000128b8((int)piVar1,puVar4 + -6,puVar4[-1]);
      if (iVar7 != 0) {
        ak_print(7,1,"[%s:%d] Channel [%d] start capture on failed!\n","ak_vi_enable_dev",0x55f,
                 puVar4[-6]);
        puVar4 = (undefined4 *)0x0;
        goto LAB_00014750;
      }
      if (iVar6 == iVar5 + 1) {
        puVar3 = DAT_0002c064;
        if (param_1 == 0) {
          if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
            puVar4 = DAT_0002c064 + -7;
            iVar6 = 0x10;
            goto LAB_00014820;
          }
          *piVar1 = 1;
          goto LAB_00014854;
        }
        if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
          puVar4 = DAT_0002c064;
        }
        puVar4 = puVar4 + -7;
        if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
          iVar6 = 0x11;
          goto LAB_00014820;
        }
        *piVar1 = 1;
        goto LAB_0001488c;
      }
      iVar6 = iVar6 + 1;
    } while ((undefined4 **)DAT_0002c064 != &DAT_0002c064);
  }
LAB_00014728:
  ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_enable_dev",0x558,iVar6);
  iVar7 = 0x700000a;
  puVar4 = (undefined4 *)0x0;
LAB_00014750:
  iVar6 = iVar5 + 2;
  do {
    if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_000147a0:
      ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_enable_dev",0x58a,iVar5);
    }
    else {
      iVar2 = DAT_0002c064[-6];
      puVar3 = DAT_0002c064;
      while (iVar5 != iVar2) {
        puVar3 = (undefined4 *)(puVar3 + -7)[7];
        if ((undefined4 **)puVar3 == &DAT_0002c064) goto LAB_000147a0;
        iVar2 = puVar3[-6];
      }
      FUN_000129c4(piVar1 + 1,puVar3 + -7);
    }
    iVar5 = iVar5 + 1;
    if (iVar5 == iVar6) {
      if (puVar4 == (undefined4 *)0x0) {
        return iVar7;
      }
      FUN_000129c4(piVar1 + 1,puVar4);
      return iVar7;
    }
  } while( true );
  while( true ) {
    puVar3 = (undefined4 *)puVar4[7];
    puVar4 = puVar3 + -7;
    if ((undefined4 **)puVar3 == &DAT_0002c064) break;
LAB_00014820:
    if (iVar6 == puVar3[-6]) {
      iVar7 = FUN_000128b8((int)piVar1,puVar4 + 1,puVar4[6]);
      if (iVar7 != 0) {
        ak_print(7,1,"[%s:%d] Channel [%d] start capture on failed!\n","ak_vi_enable_dev",0x571,
                 puVar4[1]);
        goto LAB_00014750;
      }
      break;
    }
  }
  *piVar1 = 1;
  if (param_1 == 0) {
LAB_00014854:
    ak_debug_info(7,1,"vi0=enabled");
  }
  else {
LAB_0001488c:
    ak_debug_info(7,1,"vi1=enabled");
  }
  return 0;
}



undefined4 ak_vi_disable_dev(uint param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  
  if (1 < param_1) {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_disable_dev",0x5a0,param_1);
    return 0x7000000;
  }
  piVar1 = vi_find_device(param_1);
  if (piVar1 == (int *)0x0) {
    ak_print(7,1,"[%s:%d] the device id [%d] is not open!\n","ak_vi_disable_dev",0x5a7,param_1);
    return 0x7000001;
  }
  if (*piVar1 == 0) {
    return 0;
  }
  iVar5 = param_1 * 2;
  iVar6 = iVar5 + 2;
  do {
    if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00014a50:
      ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_disable_dev",0x5b7,iVar5);
    }
    else {
      iVar3 = DAT_0002c064[-6];
      puVar4 = DAT_0002c064;
      while (puVar4 = puVar4 + -7, iVar5 != iVar3) {
        puVar4 = (undefined4 *)puVar4[7];
        if ((undefined4 **)puVar4 == &DAT_0002c064) goto LAB_00014a50;
        iVar3 = puVar4[-6];
      }
      *puVar4 = 0;
      puVar4[9] = 0;
      puVar4[10] = 0;
      puVar4[0xb] = 0;
      FUN_000129c4(piVar1 + 1,puVar4);
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != iVar6);
  puVar4 = DAT_0002c064;
  if (param_1 == 1) {
    if ((undefined4 **)DAT_0002c064 != &DAT_0002c064) {
      puVar2 = DAT_0002c064 + -7;
      iVar5 = 0x11;
      goto LAB_00014aa8;
    }
    *piVar1 = 0;
LAB_00014b30:
    ak_debug_info(7,1,"vi1=disabled");
  }
  else {
    if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
      *piVar1 = 0;
    }
    else {
      puVar2 = DAT_0002c064 + -7;
      iVar5 = 0x10;
LAB_00014aa8:
      do {
        if (iVar5 == puVar4[-6]) {
          *puVar2 = 0;
          puVar2[9] = 0;
          puVar2[10] = 0;
          puVar2[0xb] = 0;
          FUN_000129c4(piVar1 + 1,puVar2);
          *piVar1 = 0;
          goto joined_r0x00014adc;
        }
        puVar4 = (undefined4 *)puVar2[7];
        puVar2 = puVar4 + -7;
      } while ((undefined4 **)puVar4 != &DAT_0002c064);
      *piVar1 = 0;
joined_r0x00014adc:
      if (param_1 != 0) goto LAB_00014b30;
    }
    ak_debug_info(7,1,"vi0=disabled");
  }
  return 0;
}



undefined4 ak_vi_get_frame_ex(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  void *__s;
  int iVar6;
  undefined4 *puVar7;
  undefined4 **ppuVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  bool bVar13;
  ulonglong uVar14;
  int local_78;
  undefined4 *local_60;
  undefined4 *puStack_5c;
  undefined4 *local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (((int)param_1 < 0) || (3 < (int)param_1 && (undefined4 *)0x1 < param_1 + -4)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_get_frame_ex",0x6f2,param_1);
    uVar3 = 0x7000004;
  }
  else if (param_2 == (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d] frame is NULL!\n","ak_vi_get_frame_ex",0x6f8);
    uVar3 = 0x101;
  }
  else {
    bVar13 = SBORROW4((int)param_1,0x10);
    puVar7 = param_1 + -4;
    if (param_1 != (undefined4 *)0x10) {
      bVar13 = SBORROW4((int)param_1,1);
      puVar7 = (undefined4 *)((int)param_1 + -1);
    }
    piVar4 = vi_find_device((uint)((param_1 != (undefined4 *)0x10 && param_1 != (undefined4 *)0x1)
                                  && (int)puVar7 < 0 == bVar13));
    if (piVar4 == (int *)0x0) {
      ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_get_frame_ex",
               0x70a,param_1);
      uVar3 = 0x7000009;
    }
    else {
      if (*piVar4 != 1) {
        ak_print(7,1,"[%s:%d] vi device should be enable first!\n","ak_vi_get_frame_ex",0x710);
        return 0x7000005;
      }
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00014cd0:
        ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_get_frame_ex",0x719,param_1);
        uVar3 = 0x700000a;
      }
      else {
        puVar7 = (undefined4 *)DAT_0002c064[-6];
        ppuVar8 = (undefined4 **)DAT_0002c064;
        while (ppuVar8 = ppuVar8 + -7, param_1 != puVar7) {
          ppuVar8 = (undefined4 **)ppuVar8[7];
          if (ppuVar8 == &DAT_0002c064) goto LAB_00014cd0;
          puVar7 = ppuVar8[-6];
        }
        if (*ppuVar8 == (undefined4 *)0x1) {
          if (g_stop_flag == 0 || param_3 != 0) {
            local_78 = 3;
            local_50 = (undefined4 *)0x0;
            local_4c = 0;
            local_48 = (undefined4 *)0x0;
            local_44 = (undefined4 *)0x0;
            local_40 = 0;
            local_3c = 0;
            local_38 = 0;
            local_34 = 0;
            local_30 = 0;
            local_2c = 0;
            do {
              memset(&local_50,0,0x28);
              iVar5 = vi_dev_get_frame(piVar4[1],(int)ppuVar8[1],(int *)&local_50);
              if (iVar5 != 0) {
                ak_print(7,1,"[%s:%d] CHN [%d] vi_dev_get_frame failed!\n","vi_get_one_frame",0x60e,
                         ppuVar8[1]);
                break;
              }
              uVar3 = ak_get_os_timestamp();
              __s = (void *)ak_mem_alloc_(7,0x38,"vi_get_one_frame",uVar3);
              if (__s == (void *)0x0) {
                ak_print(7,1,"[%s:%d] calloc struct ak_frame failed\n","vi_get_one_frame",0x618);
                if (local_50 != (undefined4 *)0x0) {
                  vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],local_50);
                }
                break;
              }
              memset(__s,0,0x38);
              uVar3 = local_3c;
              puVar2 = local_44;
              puVar7 = local_48;
              puVar12 = ppuVar8[1];
              puVar9 = ppuVar8[5];
              puVar11 = ppuVar8[4];
              iVar5 = (int)puVar12 * 8;
              *(undefined4 *)((int)__s + 0xc) = local_40;
              *(undefined4 *)((int)__s + 0x24) = local_38;
              *(undefined4 *)((int)__s + 0x28) = local_34;
              iVar1 = ((int)puVar9 * (int)puVar11 * 3) / 2;
              *(undefined4 *)((int)__s + 0x20) = local_3c;
              *(int *)((int)__s + 0x10) = iVar1;
              *(undefined4 **)((int)__s + 8) = local_50;
              *(undefined4 *)((int)__s + 0x34) = local_30;
              *(undefined4 **)((int)__s + 0x18) = local_48;
              *(undefined4 **)((int)__s + 0x1c) = local_44;
              if (puVar12 + -4 < (undefined4 *)0x2) {
                iVar5 = (uint)(puVar12 == (undefined4 *)0x11) * 8;
                puVar9 = *(undefined4 **)(&DAT_0002c0e8 + iVar5);
                puVar11 = *(undefined4 **)(&DAT_0002c0ec + iVar5);
                if (puVar9 != (undefined4 *)0x0 || puVar11 != (undefined4 *)0x0) {
                  bVar13 = local_44 <= puVar11;
                  if (puVar11 == local_44) {
                    bVar13 = local_48 <= puVar9;
                  }
                  if (bVar13 && (puVar11 != local_44 || puVar9 != local_48)) {
                    uVar3 = 0x630;
                    goto LAB_000151dc;
                  }
                }
                if (ppuVar8[10] == (undefined4 *)0x0 && ppuVar8[0xb] == (undefined4 *)0x0) {
                  ppuVar8[10] = local_48;
                  ppuVar8[0xb] = local_44;
                }
                puVar9 = ppuVar8[9];
                *(undefined4 **)(&DAT_0002c0e8 + iVar5) = local_48;
                *(undefined4 **)(&DAT_0002c0ec + iVar5) = local_44;
                goto LAB_000150c0;
              }
              puVar9 = *(undefined4 **)(iVar5 + 0x2c0fc);
              bVar13 = puVar9 <= local_44;
              if (local_44 == puVar9) {
                bVar13 = *(undefined4 **)(iVar5 + 0x2c0f8) <= local_48;
              }
              if (!bVar13 &&
                  (*(undefined4 **)(iVar5 + 0x2c0f8) != (undefined4 *)0x0 ||
                  puVar9 != (undefined4 *)0x0)) {
                uVar3 = 0x646;
LAB_000151dc:
                ak_print(7,1,
                         "[%s:%d] CHN [%d] frame rollback, len[%d], pre_ts=%llu, entry->ts=%llu, diff=%llu\n"
                         ,"vi_get_one_frame",uVar3,puVar12,iVar1);
                vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],*(undefined4 **)((int)__s + 8));
                ak_mem_free(__s);
                break;
              }
              puVar9 = ppuVar8[3];
              uVar10 = (uint)puVar9 >> 0x10;
              if ((int)puVar9 < 1) {
                local_60 = ppuVar8[10];
                puStack_5c = ppuVar8[0xb];
                puVar9 = ppuVar8[9];
LAB_00015218:
                if (local_60 == (undefined4 *)0x0 && puStack_5c == (undefined4 *)0x0) {
                  ppuVar8[10] = puVar7;
                  ppuVar8[0xb] = puVar2;
                }
                *(undefined4 **)(iVar5 + 0x2c0f8) = puVar7;
                *(undefined4 **)(iVar5 + 0x2c0fc) = puVar2;
LAB_000150c0:
                ppuVar8[9] = (undefined4 *)((int)puVar9 + 1);
                ak_print(7,6,"[%s:%d] seq_no=%lu, ts=%llu\n","vi_data_to_frame",0x6cf,uVar3,puVar7,
                         puVar2);
                uVar3 = FUN_00012654(param_2,(int)__s,(int)puVar12);
                ak_mem_free(__s);
                return uVar3;
              }
              if (uVar10 == 0) {
                uVar10 = 1;
              }
              uVar14 = FUN_00018a48(uVar10 * 1000,(uint)puVar9 & 0xffff);
              local_60 = ppuVar8[10];
              puStack_5c = ppuVar8[0xb];
              puVar9 = ppuVar8[9];
              iVar6 = FUN_00018b44((int)puVar7 - (int)local_60,
                                   (int)puVar2 - ((int)puStack_5c + (uint)(puVar7 < local_60)),
                                   (int)puVar9 + 1,0);
              if ((int)uVar14 <= iVar6 ||
                  (puVar9 == (undefined4 *)0x0 ||
                  local_60 == (undefined4 *)0x0 && puStack_5c == (undefined4 *)0x0))
              goto LAB_00015218;
              ak_print(7,5,
                       "[%s:%d] chn[%d] frame advance, should drop, len[%d], pre_ts=%llu, pos->ts=%llu, start_time[%llu], frame_count[%d], cur_int=%d interval=%d\n"
                       ,"vi_get_one_frame",0x65d,puVar12,iVar1);
              vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],*(undefined4 **)((int)__s + 8));
              ak_mem_free(__s);
              local_78 = local_78 + -1;
            } while (local_78 != 0);
            ak_print(7,1,"[%s:%d] CHN [%d] get frame failed\n","ak_vi_get_frame_ex",0x776,param_1);
            uVar3 = 0xffffffff;
          }
          else {
            uVar3 = 0x700000b;
          }
        }
        else {
          ak_print(7,1,"[%s:%d] vi channel [%d] should be enable first!\n","ak_vi_get_frame_ex",
                   0x71f,param_1);
          uVar3 = 0x700000b;
        }
      }
    }
  }
  return uVar3;
}



undefined4 ak_vi_get_frame(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  void *__s;
  int iVar6;
  undefined4 *puVar7;
  undefined4 **ppuVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  bool bVar13;
  ulonglong uVar14;
  int iStack_78;
  undefined4 *puStack_60;
  undefined4 *puStack_5c;
  undefined4 *puStack_50;
  undefined4 uStack_4c;
  undefined4 *puStack_48;
  undefined4 *puStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  if ((param_1 < 0) || (3 < param_1 && 1 < param_1 - 0x10U)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_get_frame_ex",0x6f2,param_1);
    uVar3 = 0x7000004;
  }
  else if (param_2 == 0) {
    ak_print(7,1,"[%s:%d] frame is NULL!\n","ak_vi_get_frame_ex",0x6f8);
    uVar3 = 0x101;
  }
  else {
    bVar13 = SBORROW4(param_1,0x10);
    iVar5 = param_1 + -0x10;
    if (param_1 != 0x10) {
      bVar13 = SBORROW4(param_1,1);
      iVar5 = param_1 + -1;
    }
    piVar4 = vi_find_device((uint)((param_1 != 0x10 && param_1 != 1) && iVar5 < 0 == bVar13));
    if (piVar4 == (int *)0x0) {
      ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_get_frame_ex",
               0x70a,param_1);
      uVar3 = 0x7000009;
    }
    else {
      if (*piVar4 != 1) {
        ak_print(7,1,"[%s:%d] vi device should be enable first!\n","ak_vi_get_frame_ex",0x710);
        return 0x7000005;
      }
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00014cd0:
        ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_get_frame_ex",0x719,param_1);
        uVar3 = 0x700000a;
      }
      else {
        puVar7 = (undefined4 *)DAT_0002c064[-6];
        ppuVar8 = (undefined4 **)DAT_0002c064;
        while (ppuVar8 = ppuVar8 + -7, (undefined4 *)param_1 != puVar7) {
          ppuVar8 = (undefined4 **)ppuVar8[7];
          if (ppuVar8 == &DAT_0002c064) goto LAB_00014cd0;
          puVar7 = ppuVar8[-6];
        }
        if (*ppuVar8 == (undefined4 *)0x1) {
          if (g_stop_flag == 0) {
            iStack_78 = 3;
            puStack_50 = (undefined4 *)0x0;
            uStack_4c = 0;
            puStack_48 = (undefined4 *)0x0;
            puStack_44 = (undefined4 *)0x0;
            uStack_40 = 0;
            uStack_3c = 0;
            uStack_38 = 0;
            uStack_34 = 0;
            uStack_30 = 0;
            uStack_2c = 0;
            do {
              memset(&puStack_50,0,0x28);
              iVar5 = vi_dev_get_frame(piVar4[1],(int)ppuVar8[1],(int *)&puStack_50);
              if (iVar5 != 0) {
                ak_print(7,1,"[%s:%d] CHN [%d] vi_dev_get_frame failed!\n","vi_get_one_frame",0x60e,
                         ppuVar8[1]);
                break;
              }
              uVar3 = ak_get_os_timestamp();
              __s = (void *)ak_mem_alloc_(7,0x38,"vi_get_one_frame",uVar3);
              if (__s == (void *)0x0) {
                ak_print(7,1,"[%s:%d] calloc struct ak_frame failed\n","vi_get_one_frame",0x618);
                if (puStack_50 != (undefined4 *)0x0) {
                  vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],puStack_50);
                }
                break;
              }
              memset(__s,0,0x38);
              uVar3 = uStack_3c;
              puVar2 = puStack_44;
              puVar7 = puStack_48;
              puVar12 = ppuVar8[1];
              puVar9 = ppuVar8[5];
              puVar11 = ppuVar8[4];
              iVar5 = (int)puVar12 * 8;
              *(undefined4 *)((int)__s + 0xc) = uStack_40;
              *(undefined4 *)((int)__s + 0x24) = uStack_38;
              *(undefined4 *)((int)__s + 0x28) = uStack_34;
              iVar1 = ((int)puVar9 * (int)puVar11 * 3) / 2;
              *(undefined4 *)((int)__s + 0x20) = uStack_3c;
              *(int *)((int)__s + 0x10) = iVar1;
              *(undefined4 **)((int)__s + 8) = puStack_50;
              *(undefined4 *)((int)__s + 0x34) = uStack_30;
              *(undefined4 **)((int)__s + 0x18) = puStack_48;
              *(undefined4 **)((int)__s + 0x1c) = puStack_44;
              if (puVar12 + -4 < (undefined4 *)0x2) {
                iVar5 = (uint)(puVar12 == (undefined4 *)0x11) * 8;
                puVar9 = *(undefined4 **)(&DAT_0002c0e8 + iVar5);
                puVar11 = *(undefined4 **)(&DAT_0002c0ec + iVar5);
                if (puVar9 != (undefined4 *)0x0 || puVar11 != (undefined4 *)0x0) {
                  bVar13 = puStack_44 <= puVar11;
                  if (puVar11 == puStack_44) {
                    bVar13 = puStack_48 <= puVar9;
                  }
                  if (bVar13 && (puVar11 != puStack_44 || puVar9 != puStack_48)) {
                    uVar3 = 0x630;
                    goto LAB_000151dc;
                  }
                }
                if (ppuVar8[10] == (undefined4 *)0x0 && ppuVar8[0xb] == (undefined4 *)0x0) {
                  ppuVar8[10] = puStack_48;
                  ppuVar8[0xb] = puStack_44;
                }
                puVar9 = ppuVar8[9];
                *(undefined4 **)(&DAT_0002c0e8 + iVar5) = puStack_48;
                *(undefined4 **)(&DAT_0002c0ec + iVar5) = puStack_44;
                goto LAB_000150c0;
              }
              puVar9 = *(undefined4 **)(iVar5 + 0x2c0fc);
              bVar13 = puVar9 <= puStack_44;
              if (puStack_44 == puVar9) {
                bVar13 = *(undefined4 **)(iVar5 + 0x2c0f8) <= puStack_48;
              }
              if (!bVar13 &&
                  (*(undefined4 **)(iVar5 + 0x2c0f8) != (undefined4 *)0x0 ||
                  puVar9 != (undefined4 *)0x0)) {
                uVar3 = 0x646;
LAB_000151dc:
                ak_print(7,1,
                         "[%s:%d] CHN [%d] frame rollback, len[%d], pre_ts=%llu, entry->ts=%llu, diff=%llu\n"
                         ,"vi_get_one_frame",uVar3,puVar12,iVar1);
                vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],*(undefined4 **)((int)__s + 8));
                ak_mem_free(__s);
                break;
              }
              puVar9 = ppuVar8[3];
              uVar10 = (uint)puVar9 >> 0x10;
              if ((int)puVar9 < 1) {
                puStack_60 = ppuVar8[10];
                puStack_5c = ppuVar8[0xb];
                puVar9 = ppuVar8[9];
LAB_00015218:
                if (puStack_60 == (undefined4 *)0x0 && puStack_5c == (undefined4 *)0x0) {
                  ppuVar8[10] = puVar7;
                  ppuVar8[0xb] = puVar2;
                }
                *(undefined4 **)(iVar5 + 0x2c0f8) = puVar7;
                *(undefined4 **)(iVar5 + 0x2c0fc) = puVar2;
LAB_000150c0:
                ppuVar8[9] = (undefined4 *)((int)puVar9 + 1);
                ak_print(7,6,"[%s:%d] seq_no=%lu, ts=%llu\n","vi_data_to_frame",0x6cf,uVar3,puVar7,
                         puVar2);
                uVar3 = FUN_00012654((undefined4 *)param_2,(int)__s,(int)puVar12);
                ak_mem_free(__s);
                return uVar3;
              }
              if (uVar10 == 0) {
                uVar10 = 1;
              }
              uVar14 = FUN_00018a48(uVar10 * 1000,(uint)puVar9 & 0xffff);
              puStack_60 = ppuVar8[10];
              puStack_5c = ppuVar8[0xb];
              puVar9 = ppuVar8[9];
              iVar6 = FUN_00018b44((int)puVar7 - (int)puStack_60,
                                   (int)puVar2 - ((int)puStack_5c + (uint)(puVar7 < puStack_60)),
                                   (int)puVar9 + 1,0);
              if ((int)uVar14 <= iVar6 ||
                  (puVar9 == (undefined4 *)0x0 ||
                  puStack_60 == (undefined4 *)0x0 && puStack_5c == (undefined4 *)0x0))
              goto LAB_00015218;
              ak_print(7,5,
                       "[%s:%d] chn[%d] frame advance, should drop, len[%d], pre_ts=%llu, pos->ts=%llu, start_time[%llu], frame_count[%d], cur_int=%d interval=%d\n"
                       ,"vi_get_one_frame",0x65d,puVar12,iVar1);
              vi_dev_release_frame(piVar4[1],(int)ppuVar8[1],*(undefined4 **)((int)__s + 8));
              ak_mem_free(__s);
              iStack_78 = iStack_78 + -1;
            } while (iStack_78 != 0);
            ak_print(7,1,"[%s:%d] CHN [%d] get frame failed\n","ak_vi_get_frame_ex",0x776,param_1);
            uVar3 = 0xffffffff;
          }
          else {
            uVar3 = 0x700000b;
          }
        }
        else {
          ak_print(7,1,"[%s:%d] vi channel [%d] should be enable first!\n","ak_vi_get_frame_ex",
                   0x71f,param_1);
          uVar3 = 0x700000b;
        }
      }
    }
  }
  return uVar3;
}



undefined4 ak_vi_release_frame(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  bool bVar5;
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
  
  if ((param_1 < 0) || (3 < param_1 && 1 < param_1 - 0x10U)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_release_frame",0x78f,param_1);
    uVar1 = 0x7000004;
  }
  else if (param_2 == (undefined4 *)0x0) {
    ak_print(7,1,"[%s:%d] frame is NULL!\n","ak_vi_release_frame",0x795);
    uVar1 = 0x101;
  }
  else {
    bVar5 = SBORROW4(param_1,0x10);
    iVar3 = param_1 + -0x10;
    if (param_1 != 0x10) {
      bVar5 = SBORROW4(param_1,1);
      iVar3 = param_1 + -1;
    }
    piVar2 = vi_find_device((uint)((param_1 != 0x10 && param_1 != 1) && iVar3 < 0 == bVar5));
    if (piVar2 == (int *)0x0) {
      ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_release_frame",
               0x7a7,param_1);
      uVar1 = 0x7000009;
    }
    else {
      if (*piVar2 != 1) {
        ak_print(7,1,"[%s:%d] vi device should be enable first!\n","ak_vi_release_frame",0x7ad);
        return 0x7000005;
      }
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00015440:
        ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_release_frame",0x7b6,param_1);
        uVar1 = 0x700000a;
      }
      else {
        iVar3 = DAT_0002c064[-6];
        puVar4 = DAT_0002c064;
        while (param_1 != iVar3) {
          puVar4 = (undefined4 *)(puVar4 + -7)[7];
          if ((undefined4 **)puVar4 == &DAT_0002c064) goto LAB_00015440;
          iVar3 = puVar4[-6];
        }
        if (puVar4[-7] == 1) {
          local_28 = *param_2;
          local_18 = param_2[6];
          local_38 = 0;
          local_34 = 0;
          local_30 = 0;
          local_2c = 0;
          local_24 = 0;
          local_20 = 0;
          local_1c = 0;
          local_14 = 0;
          if (param_2[8] != 0) {
            ak_mem_free();
          }
          uVar1 = vi_dev_release_frame_by_ispframe(piVar2[1],param_1,(int)&local_38);
        }
        else {
          ak_print(7,1,"[%s:%d] vi channel [%d] should be enable first!\n","ak_vi_release_frame",
                   0x7bd,param_1);
          uVar1 = 0x700000b;
        }
      }
    }
  }
  return uVar1;
}



undefined4 ak_vi_change_chn_fps(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  bool bVar4;
  
  if ((param_1 < 0) || (3 < param_1 && 1 < param_1 - 0x10U)) {
    ak_print(7,1,"[%s:%d]  vi_chn is incorrect[%d]\n","ak_vi_change_chn_fps",0x7f1,param_1);
    uVar1 = 0x7000004;
  }
  else {
    bVar4 = SBORROW4(param_1,0x10);
    iVar3 = param_1 + -0x10;
    if (param_1 != 0x10) {
      bVar4 = SBORROW4(param_1,1);
      iVar3 = param_1 + -1;
    }
    puVar2 = vi_find_device((uint)((param_1 != 0x10 && param_1 != 1) && iVar3 < 0 == bVar4));
    if (puVar2 == (undefined4 *)0x0) {
      ak_print(7,1,"[%s:%d] Channel [%d] is master Device is not open yet!\n","ak_vi_change_chn_fps"
               ,0x803,param_1);
      uVar1 = 0x7000009;
    }
    else {
      if ((undefined4 **)DAT_0002c064 == &DAT_0002c064) {
LAB_00015660:
        ak_print(7,1,"[%s:%d] Channel [%d] is not existed!\n","ak_vi_change_chn_fps",0x80b,param_1);
        return 0x700000a;
      }
      iVar3 = DAT_0002c064[-6];
      puVar2 = DAT_0002c064;
      while (param_1 != iVar3) {
        puVar2 = (undefined4 *)*puVar2;
        if ((undefined4 **)puVar2 == &DAT_0002c064) goto LAB_00015660;
        iVar3 = puVar2[-6];
      }
      if (-1 < param_2) {
        puVar2[-4] = param_2;
        puVar2[2] = 0;
        puVar2[3] = 0;
        puVar2[4] = 0;
        return 0;
      }
      ak_print(7,1,"[%s:%d] frame rate param [%d] is invalid!\n","ak_vi_change_chn_fps",0x811,
               param_2);
      uVar1 = 0x101;
    }
  }
  return uVar1;
}



undefined4 ak_vi_switch_mode(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_1 < 2) {
    puVar2 = vi_find_device(param_1);
    if (puVar2 != (undefined4 *)0x0) {
      uVar1 = isp_switch(param_1,param_2);
      return uVar1;
    }
    ak_print(7,1,"[%s:%d] the device id [%d] is not open!\n","ak_vi_switch_mode",0x831,param_1);
    uVar1 = 0x7000001;
  }
  else {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_switch_mode",0x82a,param_1);
    uVar1 = 0x7000000;
  }
  return uVar1;
}



void ak_vi_get_sensor_id(uint param_1,undefined4 *param_2)

{
  vi_dev_get_sensor_id(param_1,param_2);
  return;
}



void ak_vi_set_stop_flag(undefined4 param_1)

{
  g_stop_flag = param_1;
  return;
}



int FUN_00015814(int param_1,ulong param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_4;
  do {
    iVar2 = ioctl(param_1,param_2,param_3,param_4,iVar3);
    if (iVar2 != -1) {
      return iVar2;
    }
    piVar1 = __errno_location();
    param_4 = *piVar1;
  } while (param_4 == 4);
  return -1;
}



void FUN_0001586c(int *param_1)

{
  if (param_1 == (int *)0x0) {
    return;
  }
  if (*param_1 != 0) {
    ak_mem_free();
    *param_1 = 0;
  }
  ak_mem_free(param_1);
  return;
}



undefined4 vi_dev_get_sensor_crop(int param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c [3];
  undefined4 local_30;
  int local_2c;
  
  local_3c[0] = 1;
  iVar1 = FUN_00015814((&DAT_0002c06c)[param_1 * 2],0xc02c563a,local_3c,(int)local_3c);
  if ((iVar1 == 0) && (local_2c != 0)) {
    *param_2 = local_30;
    *param_3 = local_2c;
    uVar2 = 0;
  }
  else {
    local_2c = *param_3;
    uVar2 = 0xffffffff;
  }
  ak_print(7,4,"%s %d, ret:%d, w:%d, h:%d\n","vi_dev_get_sensor_crop",0x8d,uVar2,*param_2,local_2c);
  return uVar2;
}



undefined4 vi_dev_open_td_chn(int param_1)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  undefined4 uVar5;
  char *pcVar6;
  stat sStack_78;
  
  uVar1 = (uint)(param_1 == 0x11);
  ak_print(7,3,"[%s:%d] vi third chn device open CHN%d!\n","vi_dev_open_td_chn",0x99,param_1);
  pcVar6 = (&PTR_s__dev_video_0_2_0001a414)[uVar1];
  iVar2 = stat(pcVar6,&sStack_78);
  if (iVar2 == -1) {
    piVar4 = __errno_location();
    pcVar3 = strerror(*piVar4);
    ak_print(7,1,"[%s:%d] Cannot identify \'%s\': %s\n","vi_dev_open_td_chn",0xa1,pcVar6,pcVar3);
    uVar5 = 0xffffffff;
  }
  else if ((sStack_78.st_mode & 0xf000) == 0x2000) {
    iVar2 = open(pcVar6,0x802,0,open);
    (&DAT_0002c07c)[uVar1] = iVar2;
    if (iVar2 == -1) {
      piVar4 = __errno_location();
      pcVar3 = strerror(*piVar4);
      ak_print(7,1,"[%s:%d] Cannot open \'%s\': %s\n","vi_dev_open_td_chn",0xad,pcVar6,pcVar3);
      uVar5 = 0xffffffff;
    }
    else {
      iVar2 = fcntl(iVar2,2,1,fcntl);
      if (iVar2 == -1) {
        piVar4 = __errno_location();
        pcVar6 = strerror(*piVar4);
        ak_print(7,3,"[%s:%d] fcntl: %s\n","vi_dev_open_td_chn",0xb3,pcVar6);
        uVar5 = 0xffffffff;
      }
      else {
        ak_thread_mutex_init(&DAT_0002c118 + uVar1 * 0x18,0);
        uVar5 = 0;
      }
    }
  }
  else {
    ak_print(7,3,"[%s:%d] %s is no device\n","vi_dev_open_td_chn",0xa6,pcVar6);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}



void vi_dev_close_td_chn(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = (uint)(param_1 == 0x11);
  if ((&DAT_0002c07c)[uVar1] != -1) {
    close((&DAT_0002c07c)[uVar1]);
    (&DAT_0002c07c)[uVar1] = 0xffffffff;
  }
  ak_thread_mutex_destroy(&DAT_0002c118 + uVar1 * 0x18);
  return;
}



int vi_dev_open(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  stat sStack_e8;
  char acStack_8c [104];
  
  ak_print(7,3,"[%s:%d] vi device open DEV%d!\n","vi_dev_open",0xd7,param_1);
  memset(acStack_8c,0,100);
  if (param_1 == 0) {
    pcVar6 = "/dev/v4l-subdev0";
  }
  else {
    pcVar6 = "/dev/v4l-subdev1";
  }
  sprintf(acStack_8c,"%s",pcVar6);
  ak_print(7,3,"[%s:%d] open sensor dev: %s\n","vi_dev_open",0xe4,acStack_8c);
  iVar2 = ak_open(acStack_8c,2);
  iVar9 = param_1 * 4;
  *(int *)((int)&g_sensor_fd + iVar9) = iVar2;
  if (iVar2 < 0) {
    piVar5 = __errno_location();
    iVar9 = *piVar5;
    pcVar6 = strerror(iVar9);
    ak_print(7,1,"[%s:%d] open %s fail, err:%d, estr:%s\n","vi_dev_open",0xea,acStack_8c,iVar9,
             pcVar6);
    iVar2 = -1;
  }
  else {
    iVar11 = param_1;
    ak_print(7,3,"[%s:%d] --- %s g_sensor_fd[%d]=%d ---\n","vi_dev_open",0xee,"vi_dev_open",param_1,
             iVar2);
    bVar1 = false;
    piVar5 = &DAT_0002c06c + param_1 * 2;
    puVar10 = (undefined4 *)(&DAT_0001a428 + param_1 * 8);
    while( true ) {
      pcVar6 = (char *)*puVar10;
      iVar3 = stat(pcVar6,&sStack_e8);
      if (iVar3 == -1) break;
      if ((sStack_e8.st_mode & 0xf000) != 0x2000) {
        ak_print(7,3,"[%s:%d] %s is no device\n","vi_dev_open",0xfc,pcVar6,iVar11,iVar2);
        goto LAB_00015d94;
      }
      iVar3 = open(pcVar6,0x802,0,open);
      *piVar5 = iVar3;
      if (iVar3 == -1) {
        piVar5 = __errno_location();
        pcVar4 = strerror(*piVar5);
        uVar8 = 0x103;
        pcVar7 = "[%s:%d] Cannot open \'%s\': %s\n";
        goto LAB_00015d80;
      }
      iVar3 = fcntl(iVar3,2,1,fcntl);
      if (iVar3 == -1) {
        piVar5 = __errno_location();
        pcVar6 = strerror(*piVar5);
        ak_print(7,3,"[%s:%d] fcntl: %s\n","vi_dev_open",0x109,pcVar6);
        goto LAB_00015d94;
      }
      if (bVar1) {
        ak_thread_mutex_init(param_1 * 0x30 + 0x2c148,0);
        ak_thread_mutex_init((param_1 * 2 + 1) * 0x18 + 0x2c148,0);
        return 0;
      }
      bVar1 = true;
      piVar5 = piVar5 + 1;
      puVar10 = puVar10 + 1;
    }
    piVar5 = __errno_location();
    pcVar4 = strerror(*piVar5);
    pcVar7 = "[%s:%d] Cannot identify \'%s\': %s\n";
    uVar8 = 0xf7;
LAB_00015d80:
    ak_print(7,1,pcVar7,"vi_dev_open",uVar8,pcVar6,pcVar4);
LAB_00015d94:
    if ((&DAT_0002c06c)[param_1 * 2] != -1) {
      close((&DAT_0002c06c)[param_1 * 2]);
      (&DAT_0002c06c)[param_1 * 2] = 0xffffffff;
    }
    iVar2 = param_1 * 2 + 1;
    if ((&DAT_0002c06c)[iVar2] != -1) {
      close((&DAT_0002c06c)[iVar2]);
      (&DAT_0002c06c)[iVar2] = 0xffffffff;
    }
    ak_print(7,3,"[%s:%d] --- %s g_sensor_fd[%d]=%d closed ---\n","vi_dev_open",0x120,"vi_dev_open",
             param_1,*(undefined4 *)((int)&g_sensor_fd + iVar9));
    iVar2 = *(int *)((int)&g_sensor_fd + iVar9);
    if (iVar2 != -1) {
      close(iVar2);
      iVar2 = -1;
      *(undefined4 *)((int)&g_sensor_fd + iVar9) = 0xffffffff;
    }
  }
  return iVar2;
}



void vi_dev_close(int param_1)

{
  int iVar1;
  int iVar2;
  
  if ((&DAT_0002c06c)[param_1 * 2] != -1) {
    close((&DAT_0002c06c)[param_1 * 2]);
    (&DAT_0002c06c)[param_1 * 2] = 0xffffffff;
  }
  iVar2 = param_1 * 2 + 1;
  ak_thread_mutex_destroy(param_1 * 0x30 + 0x2c148);
  if ((&DAT_0002c06c)[iVar2] != -1) {
    close((&DAT_0002c06c)[iVar2]);
    (&DAT_0002c06c)[iVar2] = 0xffffffff;
  }
  iVar1 = param_1 * 4;
  ak_thread_mutex_destroy(iVar2 * 0x18 + 0x2c148);
  ak_print(7,3,"[%s:%d] --- %s g_sensor_fd[%d]=%d closed ---\n","vi_dev_close",0x13e,"vi_dev_close",
           param_1,*(undefined4 *)((int)&g_sensor_fd + iVar1));
  if (*(int *)((int)&g_sensor_fd + iVar1) != -1) {
    close(*(int *)((int)&g_sensor_fd + iVar1));
    *(undefined4 *)((int)&g_sensor_fd + iVar1) = 0xffffffff;
  }
  return;
}



undefined4
vi_dev_set_crop_attr(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int extraout_r3;
  int iVar4;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  undefined4 local_88 [21];
  uint local_34;
  
  iVar4 = (&DAT_0002c06c)[param_1 * 2];
  iVar1 = FUN_00015814(iVar4,0x80685600,local_88,param_4);
  if (iVar1 == -1) {
    piVar2 = __errno_location();
    if (*piVar2 == 0x16) {
      ak_print(7,4,"[%s:%d] %s is no V4L2 device\n","get_capture_cap",0x156,
               *(undefined4 *)(&DAT_0001a428 + param_1 * 4));
      iVar4 = (&DAT_0002c06c)[param_1 * 2];
    }
    else {
      pcVar3 = strerror(*piVar2);
      ak_print(7,4,"[%s:%d] VIDIOC_QUERYCAP, %s\n","get_capture_cap",0x159,pcVar3);
      iVar4 = (&DAT_0002c06c)[param_1 * 2];
    }
  }
  else if ((local_34 & 1) == 0) {
    ak_print(7,4,"[%s:%d] %s is no video capture device\n","get_capture_cap",0x161,
             *(undefined4 *)(&DAT_0001a428 + param_1 * 4));
    iVar4 = (&DAT_0002c06c)[param_1 * 2];
  }
  memset(local_88,0,0x2c);
  local_88[0] = 1;
  iVar1 = FUN_00015814(iVar4,0xc02c563a,local_88,extraout_r3);
  if (iVar1 != 0) {
    ak_print(7,1,"[%s:%d] GET CROP CAP failed!\n","vi_dev_set_crop_attr",0x194);
    return 0xffffffff;
  }
  local_9c = 1;
  local_8c = param_5;
  local_98 = param_2;
  local_94 = param_3;
  local_90 = param_4;
  iVar1 = FUN_00015814(iVar4,0x4014563c,&local_9c,param_5);
  if (iVar1 == -1) {
    ak_print(7,1,"[%s:%d] init CROP failed!\n","vi_dev_set_crop_attr",0x18b);
    return 0xffffffff;
  }
  ak_print(7,4,"init CROP succeedded! reset to CROP[%d, %d]\n",local_90,local_8c);
  return 0;
}



undefined4 vi_dev_set_chn_enable(void)

{
  return 0;
}



int vi_dev_set_chn_res(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int extraout_r3;
  undefined4 uVar4;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  
  iVar1 = DAT_0002c07c;
  if ((param_1 != 0x10) && (iVar1 = (&DAT_0002c06c)[param_1], param_1 == 0x11)) {
    iVar1 = DAT_0002c080;
  }
  ak_print(7,4,"[%s:%d] chn id is[%d], fd is:[%d]\n","vi_dev_set_chn_res",499,param_1,iVar1);
  if (iVar1 < 0) {
    iVar1 = -1;
  }
  else {
    uVar4 = 0x3032344d;
    if (param_4 != 1) {
      uVar4 = 0x56595559;
    }
    memset(&local_ec,0,0xcc);
    local_dc = 4;
    local_ec = 1;
    local_e8 = param_2;
    local_e4 = param_3;
    local_e0 = uVar4;
    ak_print(7,4,"[%s:%d] %s w:%d, h:%d\n","vi_dev_set_chn_res",0x214,"vi_dev_set_chn_res",param_2,
             param_3);
    iVar1 = FUN_00015814(iVar1,0xc0cc5605,&local_ec,extraout_r3);
    if (iVar1 == -1) {
      piVar2 = __errno_location();
      pcVar3 = strerror(*piVar2);
      ak_print(7,1,"[%s:%d] VIDIOC_S_FMT, %s\n","vi_dev_set_chn_res",0x219,pcVar3,param_2,param_3);
      return -1;
    }
  }
  return iVar1;
}



int vi_dev_get_chn_res(int param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_cc;
  
  iVar1 = DAT_0002c07c;
  if ((param_1 != 0x10) && (iVar1 = (&DAT_0002c06c)[param_1], param_1 == 0x11)) {
    iVar1 = DAT_0002c080;
  }
  if (iVar1 < 0) {
    iVar1 = -1;
  }
  else {
    memset(&local_dc,0,0xcc);
    local_dc = 1;
    local_cc = 4;
    iVar1 = FUN_00015814(iVar1,0xc0cc5604,&local_dc,4);
    if (iVar1 == -1) {
      piVar2 = __errno_location();
      pcVar3 = strerror(*piVar2);
      ak_print(7,1,"[%s:%d] VIDIOC_S_FMT, %s\n","vi_dev_get_chn_res",0x241,pcVar3);
    }
    *param_2 = local_d8;
    param_2[1] = local_d4;
  }
  return iVar1;
}



undefined4 vi_dev_get_raw_data(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_d4;
  undefined4 local_d0;
  
  DAT_0002c1a8 = 0;
  memset(&local_d4,0,0xcc);
  local_d0 = 0x102;
  local_d4 = 1;
  iVar1 = FUN_00015814((&DAT_0002c06c)[param_1],0xc0cc5616,&local_d4,0x102);
  uVar2 = 0;
  if (iVar1 != 0) {
    ak_print(7,1,"[%s:%d] VIDIOC_S_PARM fail!!! ret = %d\n","vi_dev_get_raw_data",0x4e4,iVar1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 vi_dev_get_raw_flag(void)

{
  return DAT_0002c1a8;
}



undefined4
vi_dev_td_chn_capture_on(int param_1,int param_2,uint param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  void *__s;
  int iVar6;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 uVar7;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  int extraout_r2;
  uint extraout_r3;
  uint extraout_r3_00;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 local_84;
  uint local_80 [17];
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  
  ak_print(7,5,"[%s:%d] enter...\n","vi_dev_td_chn_capture_on",0x4fe);
  ak_print(7,5,"[%s:%d] enter...\n","vi_dev_td_chn_capture_on",0x504);
  uVar9 = (uint)(param_2 == 0x11);
  iVar1 = uVar9 * 4;
  iVar11 = (&DAT_0002c07c)[uVar9];
  uVar8 = 0;
  local_80[0] = param_5;
  local_80[3] = 0;
  local_80[4] = 0;
  local_80[1] = 1;
  local_80[2] = 2;
  iVar2 = FUN_00015814(iVar11,0xc0145608,local_80,2);
  if (iVar2 == -1) {
    ak_print(7,1,"[%s:%d] REQBUFS failed!\n","vi_dev_td_chn_capture_on",0x510);
    piVar4 = __errno_location();
    uVar12 = 0xffffffff;
    if (*piVar4 == 0x16) {
      ak_print(7,1,"[%s:%d] %s does not support user pointer i/o\n","vi_dev_td_chn_capture_on",0x512
               ,*(undefined4 *)(&DAT_0001a428 + param_1 * 4));
    }
    else {
      pcVar5 = strerror(*piVar4);
      ak_print(7,1,"[%s:%d] VIDIOC_REQBUFS, %s\n","vi_dev_td_chn_capture_on",0x514,pcVar5);
    }
  }
  else {
    iVar2 = iVar1;
    if (param_3 == 1) {
      uVar12 = ak_get_os_timestamp();
      __s = (void *)ak_mem_alloc_(7,param_5 << 3,"vi_dev_td_chn_capture_on",uVar12);
      *(void **)(&DAT_0002c1ac + iVar1) = __s;
      if (__s == (void *)0x0) {
        ak_print(7,4,"[%s:%d] Out of memory\n","vi_dev_td_chn_capture_on",0x51e);
        return 0xffffffff;
      }
      memset(__s,0,param_5 << 3);
      param_3 = extraout_r3_00;
      if (0 < (int)param_5) {
        do {
          (&DAT_0002c1b8)[uVar9 * 0x11] = 1;
          (&DAT_0002c1e4)[uVar9 * 0x11] = 2;
          (&DAT_0002c1b4)[uVar9 * 0x11] = uVar8;
          iVar6 = ioctl(iVar11,0xc0445609,&DAT_0002c1b4 + uVar9 * 0x11,ioctl);
          iVar3 = uVar8 * 8;
          if (iVar6 == -1) {
            ak_print(7,1,"[%s:%d] query buffer error\n","vi_dev_td_chn_capture_on",0x52d);
            uVar12 = extraout_r1_02;
            goto LAB_00016868;
          }
          iVar10 = *(int *)(&DAT_0002c1ac + iVar1);
          uVar7 = *(undefined4 *)(&DAT_0002c1ec + uVar9 * 0x44);
          *(undefined4 *)(iVar10 + iVar3 + 4) = uVar7;
          uVar12 = ak_get_os_timestamp();
          uVar12 = ak_mem_dma_alloc_(7,uVar7,"vi_dev_td_chn_capture_on",uVar12);
          iVar6 = *(int *)(&DAT_0002c1ac + iVar1);
          *(undefined4 *)(iVar10 + uVar8 * 8) = uVar12;
          iVar10 = *(int *)(iVar6 + uVar8 * 8);
          if (iVar10 == 0) {
            ak_print(7,1,"[%s:%d] V4L2 DMA buffer [%d] bytes alloc error\n",
                     "vi_dev_td_chn_capture_on",0x535,*(undefined4 *)(iVar6 + iVar3 + 4));
            uVar12 = extraout_r1_03;
            goto LAB_00016868;
          }
          local_80[5] = 0;
          ak_mem_dma_vaddr2paddr(iVar10,local_80 + 5,ak_mem_dma_vaddr2paddr);
          ak_print(7,4,"[%s:%d] channel[%d] alloc n_buffers:%d, paddr:%lu, vaddr:%p, length:%u\n",
                   "vi_dev_td_chn_capture_on",0x53c,param_2,uVar8,local_80[5],
                   *(undefined4 *)(*(int *)(&DAT_0002c1ac + iVar1) + uVar8 * 8),
                   *(undefined4 *)(*(int *)(&DAT_0002c1ac + iVar1) + iVar3 + 4));
          uVar8 = uVar8 + 1;
          param_3 = param_5;
        } while (uVar8 != param_5);
      }
    }
    if (param_5 != 0) {
      uVar9 = 0;
      do {
        ak_print(7,6,"[%s:%d] %s %d,i:%d\n","vi_dev_td_chn_capture_on",0x543,
                 "vi_dev_td_chn_capture_on",0x543,uVar9);
        memset(local_80 + 5,0,0x44);
        local_38 = *(undefined4 *)(*(int *)(&DAT_0002c1ac + iVar1) + uVar9 * 8);
        local_3c = 2;
        local_80[6] = 1;
        local_34 = *(int *)(*(int *)(&DAT_0002c1ac + iVar1) + uVar9 * 8 + 4);
        local_80[5] = uVar9;
        iVar3 = FUN_00015814(iVar11,0xc044560f,local_80 + 5,local_34);
        if (iVar3 == -1) {
          piVar4 = __errno_location();
          pcVar5 = strerror(*piVar4);
          ak_print(7,1,"[%s:%d] VIDIOC_QBUF, %s, i: %d\n","vi_dev_td_chn_capture_on",0x54c,pcVar5,
                   uVar9);
          uVar12 = extraout_r1;
          goto LAB_00016778;
        }
        uVar9 = uVar9 + 1;
        param_3 = extraout_r3;
      } while (param_5 != uVar9);
    }
    local_84 = 1;
    iVar11 = FUN_00015814(iVar11,0x40045612,&local_84,param_3);
    if (iVar11 == -1) {
      piVar4 = __errno_location();
      pcVar5 = strerror(*piVar4);
      ak_print(7,1,"[%s:%d] STREAMON failed, %s\n","vi_dev_td_chn_capture_on",0x555,pcVar5);
      uVar12 = extraout_r1_01;
LAB_00016868:
      if (param_5 == 0) {
        iVar11 = *(int *)(&DAT_0002c1ac + iVar1);
      }
      else {
LAB_00016778:
        iVar11 = *(int *)(&DAT_0002c1ac + iVar1);
        uVar9 = 0;
        do {
          if (iVar11 != 0) {
            iVar2 = *(int *)(iVar11 + uVar9 * 8);
            if (iVar2 != 0) {
              ak_mem_dma_free();
              iVar11 = *(int *)(&DAT_0002c1ac + iVar1);
              *(undefined4 *)(iVar11 + uVar9 * 8) = 0;
              *(undefined4 *)(iVar11 + uVar9 * 8 + 4) = 0;
              uVar12 = extraout_r1_00;
              iVar2 = extraout_r2;
            }
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < param_5);
      }
      if (iVar11 == 0) {
        uVar12 = 0xffffffff;
      }
      else {
        ak_mem_free(iVar11,uVar12,iVar2,ak_mem_free);
        uVar12 = 0xffffffff;
        *(undefined4 *)(&DAT_0002c1ac + iVar1) = 0;
      }
    }
    else {
      uVar12 = 0;
    }
  }
  return uVar12;
}



undefined4 vi_dev_td_chn_capture_off(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  undefined **ppuVar3;
  undefined **ppuVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined **ppuVar7;
  undefined **ppuVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 local_2c [2];
  
  uVar2 = (uint)(param_2 == 0x11);
  iVar1 = uVar2 * 4;
  local_2c[0] = 1;
  iVar5 = FUN_00015814((&DAT_0002c07c)[uVar2],0x40045613,local_2c,param_4);
  if (iVar5 == -1) {
    ak_print(7,4,"STREAMOFF failed\n");
    uVar9 = 0xffffffff;
  }
  else {
    ak_print(7,4,"[%s:%d] STREAMOFF succeedded\n","vi_dev_td_chn_capture_off",0x58a);
    if (param_3 == 3) {
      iVar5 = *(int *)(&DAT_0002c1ac + iVar1);
      if (iVar5 != 0) {
        if (0 < param_4) {
          iVar10 = 0;
          do {
            if (*(int *)(iVar5 + iVar10 * 8) != 0) {
              ak_mem_dma_free();
              iVar5 = *(int *)(&DAT_0002c1ac + iVar1);
              *(undefined4 *)(iVar5 + iVar10 * 8) = 0;
            }
            iVar10 = iVar10 + 1;
          } while (iVar10 != param_4);
        }
        ak_mem_free(iVar5);
        *(undefined4 *)(&DAT_0002c1ac + iVar1) = 0;
      }
      ak_thread_mutex_lock(&DAT_0002c118 + uVar2 * 0x18);
      ppuVar7 = (undefined **)(&td_v4l2_frame_list)[uVar2 * 2];
      if (&td_v4l2_frame_list + uVar2 * 2 != ppuVar7) {
        ppuVar8 = (undefined **)*ppuVar7;
        ppuVar4 = (undefined **)*ppuVar7;
        do {
          ppuVar3 = ppuVar4;
          puVar6 = (undefined4 *)ppuVar7[1];
          ppuVar8[1] = (undefined *)puVar6;
          *puVar6 = ppuVar8;
          *ppuVar7 = (undefined *)0x100100;
          ppuVar7[1] = (undefined *)0x200200;
          FUN_0001586c((int *)(ppuVar7 + -1));
          ppuVar8 = (undefined **)*ppuVar3;
          ppuVar4 = ppuVar8;
          ppuVar7 = ppuVar3;
        } while (ppuVar3 != &td_v4l2_frame_list + uVar2 * 2);
      }
      ak_thread_mutex_unlock(&DAT_0002c118 + uVar2 * 0x18);
      return 0;
    }
    uVar9 = 0;
  }
  return uVar9;
}



undefined4 vi_dev_capture_on(int param_1,char *param_2,uint param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  void *__s;
  int iVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 local_70;
  uint local_6c [12];
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  
  pcVar7 = DAT_0002c23c;
  ak_print(7,5,"[%s:%d] enter..., camera_lost_frame=%d\n","vi_dev_capture_on",0x5b9,DAT_0002c23c);
  if (param_2 + -0x10 < (char *)0x2) {
    uVar3 = vi_dev_td_chn_capture_on(param_1,(int)param_2,param_3,param_4,param_5);
    return uVar3;
  }
  ak_print(7,5,"[%s:%d] enter...\n","set_buffer_size",0x454,pcVar7);
  uVar10 = 0;
  iVar9 = (&DAT_0002c06c)[(int)param_2];
  local_6c[0] = param_5;
  local_6c[3] = 0;
  local_6c[4] = 0;
  local_6c[1] = 1;
  local_6c[2] = 2;
  iVar2 = FUN_00015814(iVar9,0xc0145608,local_6c,2);
  if (iVar2 == -1) {
    ak_print(7,1,"[%s:%d] REQBUFS failed!\n","set_buffer_size",0x45f,pcVar7);
    piVar6 = __errno_location();
    if (*piVar6 == 0x16) {
      pcVar7 = *(char **)(&DAT_0001a428 + param_1 * 4);
      ak_print(7,1,"[%s:%d] %s does not support user pointer i/o\n","set_buffer_size",0x461,pcVar7);
    }
    else {
      pcVar7 = strerror(*piVar6);
      ak_print(7,1,"[%s:%d] VIDIOC_REQBUFS, %s\n","set_buffer_size",0x463,pcVar7);
    }
  }
  else {
    if (param_3 == 1) {
      uVar3 = ak_get_os_timestamp();
      __s = (void *)ak_mem_alloc_(7,param_5 << 3,"malloc_capture_buffers",uVar3);
      iVar2 = (int)param_2 * 4;
      *(void **)(&DAT_0002c240 + iVar2) = __s;
      if (__s != (void *)0x0) {
        memset(__s,0,param_5 << 3);
        if (0 < (int)param_5) {
          iVar5 = (int)param_2 * 0x44;
          do {
            *(undefined4 *)(&DAT_0002c254 + iVar5) = 1;
            *(undefined4 *)(&DAT_0002c280 + iVar5) = 2;
            *(uint *)(&DAT_0002c250 + iVar5) = uVar10;
            iVar4 = ioctl(iVar9,0xc0445609,&DAT_0002c250 + iVar5,ioctl);
            iVar1 = uVar10 * 8;
            if (iVar4 == -1) {
              ak_print(7,1,"[%s:%d] query buffer error\n","malloc_capture_buffers",0x41d,pcVar7);
LAB_000170f4:
              iVar9 = *(int *)(&DAT_0002c240 + iVar2);
              uVar10 = 0;
              do {
                if ((iVar9 != 0) && (*(int *)(iVar9 + uVar10 * 8) != 0)) {
                  ak_mem_dma_free();
                  iVar9 = *(int *)(&DAT_0002c240 + iVar2);
                  *(undefined4 *)(iVar9 + uVar10 * 8) = 0;
                  *(undefined4 *)(iVar9 + uVar10 * 8 + 4) = 0;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 != param_5);
              if (iVar9 != 0) {
                ak_mem_free(iVar9);
                *(undefined4 *)(&DAT_0002c240 + iVar2) = 0;
              }
              goto LAB_00016e78;
            }
            iVar11 = *(int *)(&DAT_0002c240 + iVar2);
            uVar8 = *(undefined4 *)(&DAT_0002c288 + iVar5);
            *(undefined4 *)(iVar11 + iVar1 + 4) = uVar8;
            uVar3 = ak_get_os_timestamp();
            uVar3 = ak_mem_dma_alloc_(7,uVar8,"malloc_capture_buffers",uVar3);
            iVar4 = *(int *)(&DAT_0002c240 + iVar2);
            *(undefined4 *)(iVar11 + uVar10 * 8) = uVar3;
            iVar11 = *(int *)(iVar4 + uVar10 * 8);
            if (iVar11 == 0) {
              pcVar7 = *(char **)(iVar4 + iVar1 + 4);
              ak_print(7,1,"[%s:%d] V4L2 DMA buffer [%d] bytes alloc error\n",
                       "malloc_capture_buffers",0x425,pcVar7);
              goto LAB_000170f4;
            }
            local_70 = 0;
            ak_mem_dma_vaddr2paddr(iVar11,&local_70,ak_mem_dma_vaddr2paddr);
            pcVar7 = param_2;
            ak_print(7,4,"[%s:%d] channel[%d] alloc n_buffers:%d, paddr:%lu, vaddr:%p, length:%u\n",
                     "malloc_capture_buffers",0x42c,param_2,uVar10,local_70,
                     *(undefined4 *)(*(int *)(&DAT_0002c240 + iVar2) + uVar10 * 8),
                     *(undefined4 *)(*(int *)(&DAT_0002c240 + iVar2) + iVar1 + 4));
            uVar10 = uVar10 + 1;
          } while (uVar10 != param_5);
        }
        ak_print(7,5,"[%s:%d] leave...\n","set_buffer_size",0x46c,pcVar7);
        iVar9 = (&DAT_0002c06c)[(int)param_2];
        if (param_5 != 0) {
          uVar10 = 0;
          do {
            ak_print(7,6,"[%s:%d] %s %d,i:%d\n","set_v4l2_qbuf",0x482,"set_v4l2_qbuf",0x482,uVar10);
            memset(local_6c,0,0x44);
            local_38 = *(undefined4 *)(*(int *)(&DAT_0002c240 + iVar2) + uVar10 * 8);
            local_3c = 2;
            local_6c[1] = 1;
            local_34 = *(int *)(*(int *)(&DAT_0002c240 + iVar2) + uVar10 * 8 + 4);
            local_6c[0] = uVar10;
            iVar5 = FUN_00015814(iVar9,0xc044560f,local_6c,local_34);
            if (iVar5 == -1) {
              piVar6 = __errno_location();
              pcVar7 = strerror(*piVar6);
              ak_print(7,1,"[%s:%d] VIDIOC_QBUF, %s, i: %d\n","set_v4l2_qbuf",0x48f,pcVar7,uVar10);
              goto LAB_00016eb0;
            }
            uVar10 = uVar10 + 1;
          } while (param_5 != uVar10);
          iVar9 = (&DAT_0002c06c)[(int)param_2];
        }
        local_6c[0] = 1;
        iVar2 = FUN_00015814(iVar9,0x40045612,local_6c,0x2c06c);
        if (iVar2 == -1) {
          piVar6 = __errno_location();
          pcVar7 = strerror(*piVar6);
          ak_print(7,1,"[%s:%d] STREAMON failed, %s\n","vi_dev_capture_on",0x5cd,pcVar7);
          return 0xffffffff;
        }
        ak_get_ostime(&DAT_0002c360);
        ak_print(7,5,"[%s:%d] leave...\n","vi_dev_capture_on",0x5ee);
        return 0;
      }
      ak_print(7,4,"[%s:%d] Out of memory\n","malloc_capture_buffers",0x40f);
    }
LAB_00016e78:
    ak_print(7,5,"[%s:%d] leave...\n","set_buffer_size",0x46c,pcVar7);
  }
  ak_print(7,1,"[%s:%d] set buffer size failed!\n","set_data_buffer",0x4a9,pcVar7);
LAB_00016eb0:
  ak_print(7,1,"[%s:%d] set_data_buffer failed!\n","vi_dev_capture_on",0x5c6,pcVar7);
  return 0xffffffff;
}



undefined4 vi_dev_capture_off(undefined4 param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 local_2c [2];
  
  if (param_2 - 0x10U < 2) {
    uVar7 = vi_dev_td_chn_capture_off(param_1,param_2,param_3,param_4);
    return uVar7;
  }
  local_2c[0] = 1;
  iVar2 = FUN_00015814((&DAT_0002c06c)[param_2],0x40045613,local_2c,1);
  if (iVar2 == -1) {
    ak_print(7,4,"STREAMOFF failed\n");
    uVar7 = 0xffffffff;
  }
  else {
    ak_print(7,4,"[%s:%d] STREAMOFF succeedded\n","vi_dev_capture_off",0x613);
    DAT_0002c23c = 4;
    if (param_3 == 3) {
      iVar2 = param_2 * 4;
      iVar3 = *(int *)(&DAT_0002c240 + iVar2);
      if (iVar3 != 0) {
        if (0 < param_4) {
          iVar8 = 0;
          do {
            if (*(int *)(iVar3 + iVar8 * 8) != 0) {
              ak_mem_dma_free();
              iVar3 = *(int *)(&DAT_0002c240 + iVar2);
              *(undefined4 *)(iVar3 + iVar8 * 8) = 0;
            }
            iVar8 = iVar8 + 1;
          } while (iVar8 != param_4);
        }
        ak_mem_free(iVar3);
        *(undefined4 *)(&DAT_0002c240 + iVar2) = 0;
      }
      iVar2 = param_2 * 0x18 + 0x2c148;
      ak_thread_mutex_lock(iVar2);
      puVar5 = *(undefined4 **)(&v4l2_frame_list + param_2 * 8);
      if ((undefined4 *)(&v4l2_frame_list + param_2 * 8) != puVar5) {
        puVar6 = (undefined4 *)*puVar5;
        puVar4 = (undefined4 *)*puVar5;
        do {
          puVar1 = puVar4;
          puVar4 = (undefined4 *)puVar5[1];
          puVar6[1] = puVar4;
          *puVar4 = puVar6;
          *puVar5 = 0x100100;
          puVar5[1] = 0x200200;
          FUN_0001586c(puVar5 + -1);
          puVar6 = (undefined4 *)*puVar1;
          puVar4 = puVar6;
          puVar5 = puVar1;
        } while (puVar1 != (undefined4 *)(&v4l2_frame_list + param_2 * 8));
      }
      ak_thread_mutex_unlock(iVar2);
      return 0;
    }
    uVar7 = 0;
  }
  return uVar7;
}



undefined4 vi_dev_release_frame_by_ispframe(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined **ppuVar2;
  int iVar3;
  char *pcVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  int *piVar8;
  uint uVar9;
  undefined **ppuVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  undefined **ppuVar16;
  
  iVar14 = (&DAT_0002c06c)[param_2];
  if (param_2 - 0x10U < 2) {
    uVar7 = (uint)(param_2 == 0x11);
    iVar14 = (&DAT_0002c07c)[uVar7];
    ak_thread_mutex_lock(&DAT_0002c118 + uVar7 * 0x18);
    ppuVar10 = (undefined **)(&td_v4l2_frame_list)[uVar7 * 2];
    uVar15 = 0xffffffff;
    if (&td_v4l2_frame_list + uVar7 * 2 != ppuVar10) {
      uVar15 = 0xffffffff;
      ppuVar16 = (undefined **)*ppuVar10;
      do {
        ppuVar2 = ppuVar16;
        ppuVar16 = ppuVar10 + -1;
        puVar6 = (undefined4 *)*ppuVar16;
        if ((*(int *)(param_3 + 0x10) == puVar6[0xd]) && (puVar6[0xb] == *(int *)(param_3 + 0x20)))
        {
          ak_print(7,6,"[%s:%d] CHN [%d] release, i = %d\n","vi_dev_release_frame_by_ispframe",0x654
                   ,param_2,*puVar6);
          puVar6 = (undefined4 *)*ppuVar16;
          uVar9 = puVar6[0xe];
          if ((0xa00000 < uVar9) || (uVar9 != *(uint *)(*(int *)(&DAT_0002c1ac + uVar7 * 4) + 4))) {
            ak_print(7,5,"[%s:%d] CHN [%d] release frame[%d].length[%u],buffers[%d][0].length[%u]\n"
                     ,"vi_dev_release_frame_by_ispframe",0x659,param_2,*puVar6,uVar9,param_2,
                     *(uint *)(*(int *)(&DAT_0002c1ac + uVar7 * 4) + 4));
            puVar6 = (undefined4 *)*ppuVar16;
            uVar9 = *(uint *)(*(int *)(&DAT_0002c1ac + uVar7 * 4) + 4);
            puVar6[0xe] = uVar9;
          }
          iVar13 = FUN_00015814(iVar14,0xc044560f,puVar6,uVar9);
          if (iVar13 == -1) {
            piVar11 = __errno_location();
            pcVar4 = strerror(*piVar11);
            ak_print(7,1,"[%s:%d] CHN [%d] VIDIOC_QBUF, %s\n","vi_dev_release_frame_by_ispframe",
                     0x65f,param_2,pcVar4);
            ak_print(7,1,"[%s:%d] CHN [%d] release frame[%d].length[%d]\n",
                     "vi_dev_release_frame_by_ispframe",0x660,param_2,*(undefined4 *)*ppuVar16,
                     *(undefined4 *)((int)*ppuVar16 + 0x38));
          }
          puVar5 = *ppuVar10;
          puVar6 = (undefined4 *)ppuVar10[1];
          *(undefined4 **)(puVar5 + 4) = puVar6;
          *puVar6 = puVar5;
          *ppuVar10 = (undefined *)0x100100;
          ppuVar10[1] = (undefined *)0x200200;
          FUN_0001586c((int *)ppuVar16);
          uVar15 = 0;
        }
        ppuVar16 = (undefined **)*ppuVar2;
        ppuVar10 = ppuVar2;
      } while (&td_v4l2_frame_list + uVar7 * 2 != ppuVar2);
    }
    ak_thread_mutex_unlock(&DAT_0002c118 + uVar7 * 0x18);
    return uVar15;
  }
  iVar13 = param_2 * 0x18 + 0x2c148;
  ak_thread_mutex_lock(iVar13);
  piVar11 = *(int **)(&v4l2_frame_list + param_2 * 8);
  if ((int *)(&v4l2_frame_list + param_2 * 8) == piVar11) {
    uVar15 = 0xffffffff;
  }
  else {
    uVar15 = 0xffffffff;
    piVar12 = (int *)*piVar11;
    do {
      piVar1 = piVar12;
      piVar12 = piVar11 + -1;
      puVar6 = (undefined4 *)*piVar12;
      if ((*(int *)(param_3 + 0x10) == puVar6[0xd]) && (puVar6[0xb] == *(int *)(param_3 + 0x20))) {
        ak_print(7,6,"[%s:%d] CHN [%d] release, i = %d\n","vi_dev_release_frame_by_ispframe",0x671,
                 param_2,*puVar6);
        puVar6 = (undefined4 *)*piVar12;
        uVar7 = puVar6[0xe];
        if ((0xa00000 < uVar7) || (uVar7 != *(uint *)(*(int *)(&DAT_0002c240 + param_2 * 4) + 4))) {
          ak_print(7,5,"[%s:%d] CHN [%d] release frame[%d].length[%u],buffers[%d][0].length[%u]\n",
                   "vi_dev_release_frame_by_ispframe",0x675,param_2,*puVar6,uVar7,param_2,
                   *(uint *)(*(int *)(&DAT_0002c240 + param_2 * 4) + 4));
          puVar6 = (undefined4 *)*piVar12;
          uVar7 = *(uint *)(*(int *)(&DAT_0002c240 + param_2 * 4) + 4);
          puVar6[0xe] = uVar7;
        }
        iVar3 = FUN_00015814(iVar14,0xc044560f,puVar6,uVar7);
        if (iVar3 == -1) {
          piVar8 = __errno_location();
          pcVar4 = strerror(*piVar8);
          ak_print(7,1,"[%s:%d] CHN [%d] VIDIOC_QBUF, %s\n","vi_dev_release_frame_by_ispframe",0x67b
                   ,param_2,pcVar4);
          ak_print(7,1,"[%s:%d] CHN [%d] release frame[%d].length[%d]\n",
                   "vi_dev_release_frame_by_ispframe",0x67c,param_2,*(undefined4 *)*piVar12,
                   ((undefined4 *)*piVar12)[0xe]);
        }
        iVar3 = *piVar11;
        piVar8 = (int *)piVar11[1];
        *(int **)(iVar3 + 4) = piVar8;
        *piVar8 = iVar3;
        *piVar11 = 0x100100;
        piVar11[1] = 0x200200;
        FUN_0001586c(piVar12);
        uVar15 = 0;
      }
      piVar12 = (int *)*piVar1;
      piVar11 = piVar1;
    } while ((int *)(&v4l2_frame_list + param_2 * 8) != piVar1);
  }
  ak_thread_mutex_unlock(iVar13);
  return uVar15;
}



undefined4 vi_dev_release_frame(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined **ppuVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  int extraout_r3;
  int extraout_r3_00;
  int *piVar8;
  int *piVar9;
  undefined **ppuVar10;
  undefined4 uVar11;
  undefined *puVar12;
  int iVar13;
  
  iVar13 = (&DAT_0002c06c)[param_2];
  iVar3 = DAT_0002c07c;
  if ((param_2 == 0x10) || (iVar3 = DAT_0002c080, param_2 == 0x11)) {
    if (param_2 == 0x11) {
      iVar13 = 0x18;
    }
    else {
      iVar13 = 0;
    }
    puVar12 = &DAT_0002c118 + iVar13;
    ak_thread_mutex_lock(puVar12);
    ppuVar10 = (undefined **)(&td_v4l2_frame_list)[(uint)(param_2 == 0x11) * 2];
    uVar11 = 0xffffffff;
    if (&td_v4l2_frame_list + (uint)(param_2 == 0x11) * 2 != ppuVar10) {
      puVar7 = (undefined4 *)ppuVar10[-1];
      ppuVar2 = ppuVar10 + -1;
      ppuVar10 = (undefined **)*ppuVar10;
      while( true ) {
        if (param_3 == puVar7) {
          ak_print(7,6,"[%s:%d] CHN [%d] release, i = %d\n","release_data_buf",0x370,param_2,
                   *param_3);
          iVar13 = FUN_00015814(iVar3,0xc044560f,*ppuVar2,extraout_r3);
          uVar11 = 0;
          if (iVar13 == -1) {
            piVar5 = __errno_location();
            pcVar4 = strerror(*piVar5);
            ak_print(7,1,"[%s:%d] CHN [%d] VIDIOC_QBUF, %s\n","release_data_buf",0x372,param_2,
                     pcVar4);
          }
          puVar6 = ppuVar2[1];
          puVar7 = (undefined4 *)ppuVar2[2];
          *(undefined4 **)(puVar6 + 4) = puVar7;
          *puVar7 = puVar6;
          ppuVar2[1] = (undefined *)0x100100;
          ppuVar2[2] = (undefined *)0x200200;
          FUN_0001586c((int *)ppuVar2);
        }
        if (&td_v4l2_frame_list + (uint)(param_2 == 0x11) * 2 == ppuVar10) break;
        puVar7 = (undefined4 *)ppuVar10[-1];
        ppuVar2 = ppuVar10 + -1;
        ppuVar10 = (undefined **)*ppuVar10;
      }
    }
  }
  else {
    puVar12 = (undefined *)(param_2 * 0x18 + 0x2c148);
    ak_thread_mutex_lock(puVar12);
    uVar11 = 0xffffffff;
    piVar9 = (int *)**(int **)(&v4l2_frame_list + param_2 * 8);
    piVar5 = *(int **)(&v4l2_frame_list + param_2 * 8);
    while (piVar1 = piVar9, (int *)(&v4l2_frame_list + param_2 * 8) != piVar5) {
      piVar9 = piVar5 + -1;
      if (param_3 == (undefined4 *)*piVar9) {
        ak_print(7,6,"[%s:%d] CHN [%d] release, i = %d\n","release_data_buf",0x381,param_2,*param_3)
        ;
        iVar3 = FUN_00015814(iVar13,0xc044560f,*piVar9,extraout_r3_00);
        uVar11 = 0;
        if (iVar3 == -1) {
          piVar8 = __errno_location();
          pcVar4 = strerror(*piVar8);
          ak_print(7,1,"[%s:%d] CHN [%d] VIDIOC_QBUF, %s\n","release_data_buf",899,param_2,pcVar4);
        }
        iVar3 = *piVar5;
        piVar8 = (int *)piVar5[1];
        *(int **)(iVar3 + 4) = piVar8;
        *piVar8 = iVar3;
        *piVar5 = 0x100100;
        piVar5[1] = 0x200200;
        FUN_0001586c(piVar9);
      }
      piVar9 = (int *)*piVar1;
      piVar5 = piVar1;
    }
  }
  ak_thread_mutex_unlock(puVar12);
  return uVar11;
}



undefined4 vi_dev_get_frame(undefined4 param_1,int param_2,int *param_3)

{
  code *pcVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  void *__s;
  FILE *__s_00;
  size_t sVar7;
  undefined4 *puVar8;
  __suseconds_t *p_Var9;
  undefined4 uVar10;
  undefined **ppuVar11;
  size_t sVar12;
  size_t __n;
  uint uVar13;
  undefined *puVar14;
  int iVar15;
  int local_c0;
  timeval local_b0;
  fd_set local_a8;
  
  if (param_3 == (int *)0x0) {
    ak_print(7,1,"[%s:%d] pointer = NULL !\n","vi_dev_get_frame",0x6aa);
    return 0xffffffff;
  }
  uVar13 = (&DAT_0002c06c)[param_2];
  if (param_2 == 0x10) {
    local_c0 = 0;
    uVar13 = DAT_0002c07c;
  }
  else if (param_2 == 0x11) {
    local_c0 = 1;
    uVar13 = DAT_0002c080;
  }
  else {
    local_c0 = -1;
  }
  p_Var9 = &local_b0.tv_usec;
  local_b0.tv_usec = 0;
  local_b0.tv_sec = 2;
  do {
    p_Var9 = p_Var9 + 1;
    *p_Var9 = 0;
  } while (p_Var9 != local_a8.fds_bits + 0x1f);
  local_a8.fds_bits[uVar13 >> 5] = local_a8.fds_bits[uVar13 >> 5] | 1 << (uVar13 & 0x1f);
  iVar3 = select(uVar13 + 1,&local_a8,(fd_set *)0x0,(fd_set *)0x0,&local_b0);
  if (iVar3 == -1) {
    ak_print(7,1,"[%s:%d] CHN [%d] select error\n","get_v4l2_ptr",0x3b5,param_2);
    goto LAB_00017ed8;
  }
  if (iVar3 == 0) {
    ak_print(7,1,"[%s:%d] CHN [%d] select timeout!\n","get_v4l2_ptr",0x3b9,param_2);
    goto LAB_00017ed8;
  }
  if (param_2 - 0x10U < 2) {
    if (param_2 == 0x11) {
      iVar3 = 0x44;
    }
    else {
      iVar3 = 0;
    }
    memset((void *)((int)&DAT_0002c1b4 + iVar3),0,0x44);
    *(undefined4 *)((int)&DAT_0002c1b8 + iVar3) = 1;
    *(undefined4 *)((int)&DAT_0002c1e4 + iVar3) = 2;
    *(undefined4 *)((int)&DAT_0002c1e8 + iVar3) = 0;
    iVar4 = FUN_00015814(uVar13,0xc0445611,(void *)((int)&DAT_0002c1b4 + iVar3),2);
    if (iVar4 != -1) {
      ak_print(7,6,"[%s:%d] %s %d, td_v4l2_buf[%d].index:%d\n","read_frame",0x2dc,"read_frame",0x2dc
               ,param_2,*(undefined4 *)((int)&DAT_0002c1b4 + iVar3));
      *(undefined4 *)((int)&DAT_0002c1e8 + iVar3) =
           *(undefined4 *)
            (*(int *)(&DAT_0002c1ac + (uint)(param_2 == 0x11) * 4) +
            *(int *)((int)&DAT_0002c1b4 + iVar3) * 8);
      goto LAB_00018110;
    }
    piVar5 = __errno_location();
    iVar3 = *piVar5;
    if (iVar3 == 5) {
      ak_print(7,1,"[%s:%d] CHN [%d] %s %d\n","read_frame",0x2d4,param_2,"read_frame",0x2d4);
      iVar3 = *piVar5;
    }
    else if (iVar3 == 0xb) {
      uVar10 = 0x2ce;
      goto LAB_00018510;
    }
    pcVar6 = strerror(iVar3);
    uVar10 = 0x2d7;
LAB_0001808c:
    ak_print(7,1,"[%s:%d] CHN [%d] VIDIOC_DQBUF, %s\n","read_frame",uVar10,param_2,pcVar6);
  }
  else {
    iVar3 = param_2 * 0x44;
    memset(&DAT_0002c250 + iVar3,0,0x44);
    *(undefined4 *)(&DAT_0002c254 + iVar3) = 1;
    *(undefined4 *)(&DAT_0002c280 + iVar3) = 2;
    *(undefined4 *)(&DAT_0002c284 + iVar3) = 0;
    iVar4 = FUN_00015814(uVar13,0xc0445611,&DAT_0002c250 + iVar3,2);
    if (iVar4 != -1) {
      ak_print(7,6,"[%s:%d] %s %d, v4l2_buf[%d].index:%d\n","read_frame",0x2f9,"read_frame",0x2f9,
               param_2,*(undefined4 *)(&DAT_0002c250 + iVar3));
      *(undefined4 *)(&DAT_0002c284 + iVar3) =
           *(undefined4 *)
            (*(int *)(&DAT_0002c240 + param_2 * 4) + *(int *)(&DAT_0002c250 + iVar3) * 8);
LAB_00018110:
      uVar10 = ak_get_os_timestamp();
      piVar5 = (int *)ak_mem_alloc_(7,0x10,"alloc_frame_buf",uVar10);
      if (piVar5 == (int *)0x0) {
        ak_print(7,2,"[%s:%d] calloc failed\n","alloc_frame_buf",0x327);
      }
      else {
        memset(piVar5,0,0x10);
        uVar10 = ak_get_os_timestamp();
        __s = (void *)ak_mem_alloc_(7,0x44,"alloc_frame_buf",uVar10);
        *piVar5 = (int)__s;
        if (__s == (void *)0x0) {
          ak_mem_free(piVar5);
                    // WARNING: Does not return
          pcVar1 = (code *)software_udf(0,0x18644);
          (*pcVar1)();
        }
        memset(__s,0,0x44);
        if (local_c0 == -1) {
          memcpy((void *)*piVar5,&DAT_0002c250 + param_2 * 0x44,0x44);
          puVar14 = (undefined *)(param_2 * 0x18 + 0x2c148);
          piVar5[3] = 1;
          ak_thread_mutex_lock(puVar14);
          iVar3 = param_2 * 8;
          ppuVar11 = (undefined **)(&v4l2_frame_list + iVar3);
          puVar8 = *(undefined4 **)(&DAT_0002c0a0 + iVar3);
          *(int **)(&DAT_0002c0a0 + iVar3) = piVar5 + 1;
        }
        else {
          memcpy((void *)*piVar5,&DAT_0002c1b4 + local_c0 * 0x11,0x44);
          puVar14 = &DAT_0002c118 + local_c0 * 0x18;
          piVar5[3] = 1;
          ak_thread_mutex_lock(puVar14);
          ppuVar11 = &td_v4l2_frame_list + local_c0 * 2;
          puVar8 = (undefined4 *)(&PTR_td_v4l2_frame_list_0002c090)[local_c0 * 2];
          (&PTR_td_v4l2_frame_list_0002c090)[local_c0 * 2] = (undefined *)(piVar5 + 1);
        }
        piVar5[1] = (int)ppuVar11;
        piVar5[2] = (int)puVar8;
        *puVar8 = piVar5 + 1;
        ak_thread_mutex_unlock(puVar14);
        iVar3 = *piVar5;
        if (iVar3 != 0) {
          if (param_2 < 0x10) {
            iVar4 = *(int *)(&DAT_0002c368 + param_2 * 4) + 1;
            *(int *)(&DAT_0002c368 + param_2 * 4) = iVar4;
          }
          else if (param_2 == 0x10) {
            iVar4 = DAT_0002c378 + 1;
            DAT_0002c378 = iVar4;
          }
          else if (param_2 == 0x11) {
            iVar4 = DAT_0002c37c + 1;
            DAT_0002c37c = iVar4;
          }
          else {
            iVar4 = 0;
          }
          uVar13 = *(uint *)(iVar3 + 0x18);
          *param_3 = iVar3;
          param_3[4] = *(int *)(iVar3 + 0x34);
          lVar2 = FUN_00018b44(uVar13,(int)uVar13 >> 0x1f,1000,0);
          iVar15 = *(int *)(iVar3 + 0x14);
          param_3[8] = *(int *)(iVar3 + 0x2c);
          param_3[5] = iVar4;
          *(longlong *)(param_3 + 2) = (longlong)iVar15 * 1000 + lVar2;
          ak_get_ostime(param_3 + 6);
          if (DAT_0002c380 != 0) {
            ak_get_ostime(&DAT_0002c384);
            uVar10 = ak_diff_ms_time(&DAT_0002c384,&DAT_0002c360);
            ak_print(7,3,"[%s:%d] capture on --> real get frame time=%ld\n","vi_dev_get_frame",0x6f0
                     ,uVar10);
            ak_print(7,3,"[%s:%d] seq_no=%ld, frame->ts=%llu, drop_isp_frame=%d\n",
                     "vi_dev_get_frame",0x6f2,param_3[5],param_3[2],param_3[3],DAT_0002c380);
            DAT_0002c380 = DAT_0002c380 + -1;
            vi_dev_release_frame(param_1,param_2,(undefined4 *)*param_3);
            return 0xffffffff;
          }
          if ((*(int *)(iVar3 + 0x10) == 1) &&
             (local_a8.fds_bits[0] = DAT_0002c380, local_a8.fds_bits[1] = DAT_0002c380,
             local_a8.fds_bits[2] = DAT_0002c380, local_a8.fds_bits[3] = DAT_0002c380,
             local_a8.fds_bits[4] = DAT_0002c380, local_a8.fds_bits[5] = DAT_0002c380,
             local_a8.fds_bits[6] = DAT_0002c380, memcpy(&local_a8,(void *)param_3[4],0x1c),
             local_a8.fds_bits[0] == 0x52415744)) {
            ak_print(7,3,"[%s:%d] get a raw frame, headsize:%d,format:%d,bitsw:%d,size:%d,w:%d,h:%d"
                     ,"vi_dev_get_frame",0x704,local_a8.fds_bits[1],local_a8.fds_bits[2],
                     local_a8.fds_bits[4],local_a8.fds_bits[3],local_a8.fds_bits[5],
                     local_a8.fds_bits[6]);
            sVar12 = local_a8.fds_bits[1] + local_a8.fds_bits[3];
            iVar3 = param_3[4];
            __s_00 = fopen("/tmp/frame.raw","w+b");
            __n = sVar12;
            if (__s_00 == (FILE *)0x0) {
              ak_print(7,1,"raw file create failed.\n");
            }
            else {
              do {
                sVar7 = fwrite((void *)(iVar3 + (sVar12 - __n)),1,__n,__s_00);
                __n = __n - sVar7;
              } while (0 < (int)__n);
              fclose(__s_00);
              DAT_0002c1a8 = 1;
            }
          }
          else {
            iVar3 = param_3[2];
            iVar4 = param_3[3];
            if (iVar3 != 0 || iVar4 != 0) {
              ak_print(7,6,"[%s:%d] seq_no=%ld, frame->ts=%llu, success get frame!\n",
                       "vi_dev_get_frame",0x712,param_3[5],iVar3,iVar4);
              return 0;
            }
            ak_print(7,3,"[%s:%d] seq_no=%ld, frame->ts=%llu, we had dropped it!\n",
                     "vi_dev_get_frame",0x717,param_3[5],iVar3,iVar4);
          }
          vi_dev_release_frame(param_1,param_2,(undefined4 *)*param_3);
          return 0xffffffff;
        }
      }
      goto LAB_00017ed8;
    }
    piVar5 = __errno_location();
    iVar3 = *piVar5;
    if (iVar3 == 5) {
      ak_print(7,1,"[%s:%d] CHN [%d] %s %d\n","read_frame",0x2f1,param_2,"read_frame",0x2f1);
      iVar3 = *piVar5;
LAB_00017f9c:
      pcVar6 = strerror(iVar3);
      uVar10 = 0x2f4;
      goto LAB_0001808c;
    }
    if (iVar3 != 0xb) goto LAB_00017f9c;
    uVar10 = 0x2eb;
LAB_00018510:
    ak_print(7,1,"[%s:%d] CHN [%d] interrupt\n","read_frame",uVar10,param_2);
  }
  ak_print(7,3,"[%s:%d] CHN [%d] read frame failed\n","get_v4l2_ptr",0x3c2,param_2);
LAB_00017ed8:
  ak_print(7,1,"[%s:%d] get frame fail\n","vi_dev_get_frame",0x6be);
  return 0xffffffff;
}



int isp_sensor_ioctl(int param_1,ulong param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int __errnum;
  
  if (param_3 == 0) {
    return 0x100;
  }
  iVar1 = *(int *)((int)&g_sensor_fd + param_1 * 4);
  if (iVar1 < 0) {
    return 0x105;
  }
  iVar1 = ioctl(iVar1,param_2,param_3,ioctl);
  if (iVar1 != 0) {
    piVar2 = __errno_location();
    __errnum = *piVar2;
    pcVar3 = strerror(__errnum);
    ak_print(7,1,"[%s:%d] cmd=0x%X, err:%d, estr:%s\n","isp_sensor_ioctl",0x72e,param_2,__errnum,
             pcVar3);
  }
  return iVar1;
}



int vi_dev_get_sensor_id(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  int __errnum;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_1 < 2) {
    if (param_2 == (undefined4 *)0x0) {
      ak_print(7,1,"[%s:%d] id is null!\n","vi_dev_get_sensor_id",0x740);
      iVar2 = -1;
    }
    else {
      memset(&local_20,0,8);
      local_20 = 0x910001;
      iVar2 = ioctl(*(int *)((int)&g_sensor_fd + param_1 * 4),0xc008561b,&local_20,ioctl);
      if (iVar2 != 0) {
        piVar3 = __errno_location();
        uVar1 = local_20;
        __errnum = *piVar3;
        pcVar4 = strerror(__errnum);
        ak_print(7,1,"[%s:%d] %s: VIDIOC_G_CTRL id=0x%X, err:%d, estr:%s\n","vi_dev_get_sensor_id",
                 0x74b,"SENSOR",uVar1,__errnum,pcVar4);
      }
      *param_2 = local_1c;
    }
  }
  else {
    ak_print(7,1,"[%s:%d] dev:%d invalid\n","vi_dev_get_sensor_id",0x73a,param_1);
    iVar2 = -1;
  }
  return iVar2;
}



void vi_dev_load_sensor_conf(int param_1,int param_2)

{
  isp_sensor_ioctl(param_1,0x40085301,param_2);
  return;
}



undefined4 vi_dev_get_exptime_for_fps(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_14 = 0;
  local_18 = param_1;
  iVar1 = isp_sensor_ioctl(0,0xc0085300,(int)&local_18);
  if (iVar1 == 0) {
    ak_print(7,3,"[%s:%d] exptime:%d\n","vi_dev_get_exptime_for_fps",0x767,local_14);
    *param_2 = local_14;
    uVar2 = 0;
  }
  else {
    ak_print(7,1,"[%s:%d] AK_SENSOR_GET_MAX_EXP_FOR_FPS fail!!! ret = %d\n",
             "vi_dev_get_exptime_for_fps",0x763,iVar1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



ulonglong FUN_00018a48(uint param_1,uint param_2)

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



void FUN_00018b44(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint local_8;
  
  if (param_4 != 0 || param_3 != 0) {
    FUN_00018bcc(param_1,param_2,param_3,param_4,(int *)&local_8);
    return;
  }
  if (param_2 != 0 || param_1 != 0) {
    param_2 = 0xffffffff;
  }
  local_8 = param_2;
  raise(8);
  return;
}



void FUN_00018b90(uint param_1,uint param_2,uint param_3,uint param_4,int *param_5)

{
  uint uVar1;
  longlong lVar2;
  
  lVar2 = FUN_00018c08(param_1,param_2,param_3,param_4);
  lVar2 = lVar2 * CONCAT44(param_4,param_3);
  uVar1 = (uint)lVar2;
  *param_5 = param_1 - uVar1;
  param_5[1] = param_2 - ((int)((ulonglong)lVar2 >> 0x20) + (uint)(param_1 < uVar1));
  return;
}



void FUN_00018bcc(uint param_1,uint param_2,uint param_3,uint param_4,int *param_5)

{
  uint uVar1;
  longlong lVar2;
  
  lVar2 = FUN_00018d64(param_1,param_2,param_3,param_4);
  lVar2 = lVar2 * CONCAT44(param_4,param_3);
  uVar1 = (uint)lVar2;
  *param_5 = param_1 - uVar1;
  param_5[1] = param_2 - ((int)((ulonglong)lVar2 >> 0x20) + (uint)(param_1 < uVar1));
  return;
}



longlong FUN_00018c08(uint param_1,uint param_2,uint param_3,uint param_4)

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
    uVar12 = FUN_00018e84(param_3,param_4,uVar6);
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
      lVar13 = FUN_00018e84(1,0,uVar6);
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
      uVar12 = FUN_00018e68(param_1,param_2,uVar6);
      uVar12 = FUN_00018e84((uint)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar6);
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



longlong FUN_00018d64(uint param_1,uint param_2,uint param_3,uint param_4)

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
  uVar9 = FUN_00018e84(param_3,param_4,uVar5);
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
    lVar10 = FUN_00018e84(1,0,uVar5);
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
  uVar9 = FUN_00018e68(param_1,param_2,uVar5);
  uVar9 = FUN_00018e84((uint)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar5);
  return CONCAT44((int)((ulonglong)lVar10 >> 0x20) -
                  ((int)((ulonglong)uVar9 >> 0x20) + (uint)(uVar7 < (uint)uVar9)),
                  uVar7 - (uint)uVar9);
}



undefined8 FUN_00018e68(uint param_1,uint param_2,uint param_3)

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



undefined8 FUN_00018e84(uint param_1,int param_2,uint param_3)

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



int ak_vi_set_dev_attr(uint param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint param3;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined1 auStack_78 [8];
  uint local_70;
  uint local_6c;
  char acStack_68 [68];
  
  if (param_1 < 2) {
    if (param_2 == (uint *)0x0) {
      ak_print(7,1,"[%s:%d] dev_attr is NULL!\n","ak_vi_set_dev_attr",0x295);
      iVar1 = 0x101;
    }
    else {
      param3 = *param_2;
      if (param3 != param_1) {
        ak_print(7,1,"[%s:%d] dev id [%d] is not match the dev id in attr[%d]\n",
                 "ak_vi_set_dev_attr",0x29b,param_1,param3);
        return 0x7000002;
      }
      puVar2 = vi_find_device(param_1);
      if (puVar2 == (undefined4 *)0x0) {
        ak_print(7,1,"[%s:%d] Can\'t find the video device according to the dev id[%d]\n",
                 "ak_vi_set_dev_attr",0x2a4,param3);
        iVar1 = 0x7000001;
      }
      else {
        uVar5 = param_2[9];
        uVar6 = param_2[10];
        uVar4 = uVar6 - 0x12;
        if (uVar4 < 0xa0f) {
          uVar4 = uVar5 - 0x12;
        }
        uVar7 = param_2[0xc];
        uVar8 = param_2[0xd];
        if (uVar4 < 0xa0f) {
          uVar4 = uVar8 - 0x12;
          if (uVar4 < 0x4ef) {
            uVar4 = uVar7 - 0x12;
          }
          if (uVar4 < 0x4ef) {
            memcpy(auStack_78,param_2 + 5,0x10);
            uVar5 = uVar5 + 0x1f & 0xffffffe0;
            uVar6 = uVar6 + 7 & 0xfffffff8;
            uVar4 = uVar7 + 0x1f & 0xffffffe0;
            uVar7 = uVar8 + 7 & 0xfffffff8;
            if (((int)local_70 < 1) || ((int)local_6c < 1)) {
              ak_print(7,1,"[%s:%d] crop argument error, w: %d, h: %d\n",
                       "vi_check_dev_resolution_align",0x25e,local_70,local_6c);
            }
            else if (uVar6 == 0 || uVar5 == 0) {
              ak_print(7,1,"[%s:%d] main chn argument error, w: %d, h: %d\n",
                       "vi_check_dev_resolution_align",0x265,uVar5,uVar6);
              local_70 = uVar5;
              local_6c = uVar6;
            }
            else {
              if (uVar7 != 0 && uVar4 != 0) {
                if (((int)local_70 < (int)uVar4) || ((int)local_6c < (int)uVar7)) {
                  ak_print(7,1,
                           "[%s:%d] the sub_max_width(32 align)/height(8 align):[%d][%d] should not larger then crop resolution[%d][%d]\n"
                           ,"ak_vi_set_dev_attr",0x2c2,uVar4,uVar7,local_70,local_6c);
                  return 0x7000003;
                }
                iVar1 = puVar2[2];
                param_2[7] = local_70;
                param_2[8] = local_6c;
                param_2[9] = uVar5;
                param_2[10] = uVar6;
                param_2[0xc] = uVar4;
                param_2[0xd] = uVar7;
                if (iVar1 == 0) {
                  uVar3 = isp_3D_NR_create(param3,local_70,local_6c,isp_3D_NR_create);
                  puVar2[2] = uVar3;
                }
                memcpy(puVar2 + 3,param_2,0x38);
                iVar1 = vi_dev_set_crop_attr(puVar2[1],param_2[5],param_2[6],param_2[7],param_2[8]);
                if (iVar1 != 0) {
                  return iVar1;
                }
                memset(acStack_68,0,0x40);
                memset(acStack_68,0,0x40);
                snprintf(acStack_68,0x40,"vi%d_id=%d",param3,param3);
                ak_debug_info(7,0,acStack_68);
                memset(acStack_68,0,0x40);
                snprintf(acStack_68,0x40,"vi%d_crop=[%d,%d,%d,%d]",param3,param_2[5],param_2[6],
                         param_2[7],param_2[8]);
                ak_debug_info(7,0,acStack_68);
                memset(acStack_68,0,0x40);
                snprintf(acStack_68,0x40,"vi%d_max_res=[%d*%d]",param3,param_2[9],param_2[10]);
                ak_debug_info(7,0,acStack_68);
                memset(acStack_68,0,0x40);
                snprintf(acStack_68,0x40,"vi%d_frame_rate=%d",param3,param_2[0xb]);
                ak_debug_info(7,0,acStack_68);
                memset(acStack_68,0,0x40);
                snprintf(acStack_68,0x40,"vi%d_sub_max_res=[%d*%d]",param3,param_2[0xc],param_2[0xd]
                        );
                ak_debug_info(7,0,acStack_68);
                return 0;
              }
              ak_print(7,1,"[%s:%d] sub chn argument error, w: %d, h: %d\n",
                       "vi_check_dev_resolution_align",0x26c,uVar5,uVar6);
              local_70 = uVar5;
              local_6c = uVar6;
            }
            ak_print(7,1,"[%s:%d] check device resolution attribute argument failed!\n",
                     "ak_vi_set_dev_attr",700,local_70,local_6c);
            return 0x7000003;
          }
        }
        ak_print(7,1,"[%s:%d] the res is out the range main[%d*%d]sub[%d*%d], min[%d*%d]!\n",
                 "ak_vi_set_dev_attr",0x2b4,0xa20,0xa20,0x500,0x500,0x12,0x12);
        iVar1 = 0x101;
      }
    }
  }
  else {
    ak_print(7,1,"[%s:%d] Unsupport Dev id:[%d]\n","ak_vi_set_dev_attr",0x28f,param_1);
    iVar1 = 0x7000000;
  }
  return iVar1;
}



void _fini(void)

{
  return;
}


