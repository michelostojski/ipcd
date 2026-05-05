typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
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



undefined1 __bss_start__;
undefined4 DAT_00030034;
dword DWORD_0001fe10;
undefined __register_frame_info;
undefined DAT_0003164c;
undefined LAB_00014020;
undefined LAB_000151ec;
undefined ak_mem_free;
undefined FUN_00013cec;
undefined FUN_0001561c;
int DAT_0003168c;
short DAT_0003167a;
int DAT_0003167c;
int DAT_00031680;
undefined2 DAT_00031684;
int DAT_00031668;
short DAT_00031686;
undefined DAT_00031664;
undefined _SD_Echo_GetFarVolumeParam;
undefined _SD_Echo_GetFarNrParam;
undefined _SD_Echo_GetFarEqParam;
undefined _SD_Echo_GetNrParam;
undefined _SD_Echo_GetNearEqParam;
undefined _SD_Echo_GetNearVolumeParam;
int DAT_00031618;
undefined4 DAT_00031668;
undefined2 DAT_00031678;
undefined4 DAT_00031674;
undefined4 DAT_0003168c;
WAVE-Sound WAVE_0001eb0c;
undefined DAT_0001eb20;
string s_/tmp/_00031418;
undefined DAT_0003166c;
undefined DAT_00031688;
undefined ak_get_localdate;
undefined1[5088] dump_wav_list;
undefined FUN_000140a8;
undefined DAT_0003161c;
undefined _SD_Echo_SetNearEqParam;
undefined _SD_Echo_SetNrParam;
undefined _SD_Echo_SetFarNrParam;
undefined _SD_Echo_SetFarEqParam;
undefined _SD_Echo_SetNearVolumeParam;
undefined4 DAT_00031624;
undefined _SD_Echo_SetFarVolumeParam;
undefined _SD_Echo_FillAdcStream;
int DAT_00031690;
undefined _SD_Echo_FillFarStream;
undefined4 DAT_0003167c;
undefined _SD_Echo_SetNearJitterBufParam;
uint DAT_00031618;
int DAT_00031628;
undefined4 DAT_0003162c;
undefined4 DAT_00031644;
undefined4 DAT_00031628;
undefined LAB_0001ab44;
undefined FUN_0001aaec;
undefined _SD_Filter_SetAslcMileStones;
undefined _SD_Filter_Open;
undefined _SD_ASLC_login;
undefined free;

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



// WARNING: Removing unreachable block (ram,0x000138d4)
// WARNING: Removing unreachable block (ram,0x000138ec)
// WARNING: Removing unreachable block (ram,0x000138f4)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  int iVar1;
  
  iVar1 = 0x30000;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_00030034);
    entry();
    if (*(int *)(iVar1 + 0x20) != 0) {
      __deregister_frame_info(&DWORD_0001fe10);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00013938)
// WARNING: Removing unreachable block (ram,0x00013950)
// WARNING: Removing unreachable block (ram,0x00013958)
// WARNING: Removing unreachable block (ram,0x00013a40)
// WARNING: Removing unreachable block (ram,0x00013a54)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_0001fe10,&DAT_0003164c,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



undefined4 FUN_00013a7c(undefined4 param_1,undefined2 *param_2,undefined *param_3)

{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  ushort *puVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  undefined1 *puVar12;
  undefined4 *puVar13;
  undefined1 auStack_ac [4];
  undefined2 local_a8;
  undefined4 local_a4;
  undefined4 local_a0 [10];
  undefined2 local_78 [10];
  undefined2 local_64 [10];
  byte local_50 [10];
  char local_46 [10];
  undefined1 local_3c;
  undefined1 local_38;
  undefined4 local_34;
  undefined1 local_30;
  
  memset(auStack_ac,0,0x84);
  iVar5 = (*(code *)param_3)(param_1,auStack_ac);
  if (iVar5 == 1) {
    *(undefined1 *)(param_2 + 0x3e) = 1;
    param_2[0x3d] = (undefined2)local_34;
    puVar8 = &local_a4;
    puVar6 = auStack_ac;
    *(undefined1 *)(param_2 + 0x3c) = local_30;
    *(undefined1 *)(param_2 + 0x36) = local_3c;
    *(undefined4 *)(param_2 + 0x3a) = local_34;
    puVar11 = param_2 + 0x17;
    puVar10 = param_2 + 0x21;
    puVar9 = param_2 + 0x2b;
    puVar12 = (undefined1 *)((int)param_2 + 0x7d);
    iVar5 = 10;
    *(undefined1 *)(param_2 + 0x38) = local_38;
    *param_2 = local_a8;
    puVar13 = (undefined4 *)(param_2 + 2);
    *puVar13 = local_a4;
    puVar7 = puVar6;
    do {
      cVar1 = puVar6[0x66];
      uVar3 = *(undefined2 *)(puVar7 + 0x34);
      uVar4 = *(undefined2 *)(puVar7 + 0x48);
      bVar2 = puVar6[0x5c];
      puVar8 = puVar8 + 1;
      puVar7 = puVar7 + 2;
      puVar13 = puVar13 + 1;
      *puVar13 = *puVar8;
      puVar11 = puVar11 + 1;
      *puVar11 = uVar3;
      puVar10 = puVar10 + 1;
      *puVar10 = uVar4;
      puVar9 = puVar9 + 1;
      *puVar9 = (ushort)bVar2;
      if (cVar1 == '\0') {
        *puVar12 = 1;
      }
      else {
        *puVar12 = 0;
      }
      iVar5 = iVar5 + -1;
      puVar6 = puVar6 + 1;
      puVar12 = puVar12 + 1;
    } while (iVar5 != 0);
    return 0;
  }
  *(undefined1 *)(param_2 + 0x3e) = 0;
  ak_print(0x19,5,"[%s:%d] eq not open\n ","get_eq_param",0x5ac);
  return 0x1900000d;
}



undefined4 FUN_00013bb8(undefined4 param_1,undefined2 *param_2,undefined *param_3)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  undefined2 *puVar12;
  undefined4 *puVar13;
  undefined4 local_ac;
  undefined2 local_a8;
  undefined4 local_a4;
  undefined4 local_a0 [10];
  undefined2 local_78 [10];
  undefined2 local_64 [10];
  undefined1 local_50 [10];
  undefined1 local_46 [22];
  undefined1 local_30;
  undefined2 local_2e;
  undefined1 local_2c;
  undefined2 local_2a;
  
  memset(&local_ac,0,0x84);
  local_a8 = *param_2;
  puVar13 = (undefined4 *)(param_2 + 2);
  local_a4 = *puVar13;
  puVar7 = &local_ac;
  puVar12 = param_2 + 0x17;
  puVar11 = param_2 + 0x21;
  puVar10 = param_2 + 0x2b;
  pcVar6 = (char *)(param_2 + 0x3e);
  iVar9 = 10;
  puVar4 = &local_a4;
  local_2e = 28000;
  local_30 = 0;
  local_ac = 7;
  puVar8 = puVar7;
  do {
    puVar13 = puVar13 + 1;
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
    puVar4 = puVar4 + 1;
    *puVar4 = *puVar13;
    puVar12 = puVar12 + 1;
    puVar11 = puVar11 + 1;
    uVar2 = *puVar11;
    puVar10 = puVar10 + 1;
    uVar3 = *puVar10;
    iVar9 = iVar9 + -1;
    *(undefined2 *)(puVar7 + 0xd) = *puVar12;
    *(undefined2 *)(puVar7 + 0x12) = uVar2;
    *(bool *)((int)puVar8 + 0x66) = cVar1 == '\0';
    *(char *)(puVar8 + 0x17) = (char)uVar3;
    puVar7 = (undefined4 *)((int)puVar7 + 2);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (iVar9 != 0);
  local_2a = 0x80;
  local_2c = 4;
  iVar9 = (*(code *)param_3)(param_1,1,&local_ac);
  if (iVar9 == 1) {
    uVar5 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNearEqParam failed\n ","eq_enable",0x60d);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}



void * FUN_00013cec(size_t param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  void *__s;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x19,param_1,"vqe_alloc",uVar1,param_4);
  if (__s != (void *)0x0) {
    memset(__s,0,param_1);
  }
  return __s;
}



int FUN_00013d44(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *local_74;
  undefined4 local_70;
  code *local_6c;
  code *local_68;
  undefined1 *local_64;
  undefined1 *local_54;
  code *local_50;
  int local_4c;
  undefined1 local_48;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  int local_38;
  undefined4 local_34;
  undefined2 local_30;
  undefined2 local_2e;
  undefined4 local_2c;
  
  memset(&local_74,0,0x4c);
  local_44 = *param_2;
  local_4c = param_1 + 0x38;
  local_40 = (undefined2)param_2[2];
  local_74 = "AudioFilter Version V1.15.16";
  local_6c = FUN_00013cec;
  local_68 = ak_mem_free;
  local_64 = &LAB_00014020;
  local_54 = &LAB_000151ec;
  local_50 = FUN_0001561c;
  local_70 = 0;
  local_3e = 0x10;
  if ((param_3 < 8000) || (local_38 = param_3, local_44 != 16000 && local_44 != 8000)) {
    local_38 = local_44;
  }
  local_30 = 0;
  local_2e = 0x5000;
  local_2c = 0xaa;
  if (local_44 < 16000) {
    local_34 = 0x2000;
  }
  else if (local_44 < 32000) {
    local_34 = 0x4000;
  }
  else {
    local_34 = 0x8000;
  }
  local_48 = (undefined1)param_4;
  iVar1 = _SD_Echo_Open(&local_74);
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] open echo lib error\n","open_echo_lib",0x7d9);
  }
  else {
    if (param_4 == 0) {
      pcVar2 = "near jitterBufLen ";
    }
    else {
      pcVar2 = "far jitterBufLen ";
    }
    ak_set_debug_num_info(0x19,1,pcVar2,local_34);
    ak_set_debug_num_info(0x19,1,"sample rate ",*param_2);
    ak_set_debug_num_info(0x19,1,"hwSampleRate ",local_38);
    ak_set_debug_num_info(0x19,1,"channel num ",param_2[2]);
    ak_set_debug_num_info(0x19,1,"sample bits ",param_2[1]);
    ak_set_debug_num_info(0x19,1,"syncedInputs ",local_30);
    ak_set_debug_num_info(0x19,1,"syncBufLen ",local_2e);
    ak_set_debug_num_info(0x19,1,"syncCompensate ",local_2c);
  }
  return iVar1;
}



void FUN_00013f68(int param_1)

{
  char cVar1;
  
  if (*(FILE **)(param_1 + 8) == (FILE *)0x0) {
    return;
  }
  DAT_0003168c = *(int *)(param_1 + 0xc);
  DAT_0003167c = *(int *)(param_1 + 0x14);
  cVar1 = *(char *)(param_1 + 0x10);
  DAT_00031680 = (int)cVar1 * DAT_0003167c * 2;
  DAT_0003167a = (short)cVar1;
  DAT_00031684 = (undefined2)((int)cVar1 << 1);
  DAT_00031668 = DAT_0003168c + 0x24;
  DAT_00031686 = (short)*(char *)(param_1 + 0x11);
  fseek(*(FILE **)(param_1 + 8),0,0);
  fwrite(&DAT_00031664,1,0x2c,*(FILE **)(param_1 + 8));
  fclose(*(FILE **)(param_1 + 8));
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}



// WARNING: Removing unreachable block (ram,0x00014220)
// WARNING: Removing unreachable block (ram,0x0001430c)
// WARNING: Removing unreachable block (ram,0x00014264)
// WARNING: Removing unreachable block (ram,0x000142a0)

undefined4 FUN_000140a8(undefined4 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = ak_thread_get_tid();
  ak_print(0x19,4,"[%s:%d] thread id: %ld\n","loopback_thread",0x4b3,uVar1);
  ak_thread_set_name("mpp_loopback");
  iVar3 = param_1[0x32];
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
LAB_00014120:
  iVar3 = param_1[4];
  do {
    if (iVar3 == 0) {
LAB_000141ac:
      uVar1 = ak_thread_get_tid();
      ak_print(0x19,4,"[%s:%d] ### thread id: %ld exit ###\n\n","loopback_thread",0x4e1,uVar1);
      ak_thread_exit();
      return 0;
    }
    if ((param_1[1] == 0) || (param_1[2] == 0)) break;
    iVar3 = param_1[7];
    if (iVar3 == 0) {
      uVar1 = ak_get_os_timestamp();
      iVar3 = ak_mem_alloc_(0x19,uVar4,"loopback_thread",uVar1);
      param_1[7] = iVar3;
      if (iVar3 == 0) {
        ak_print(0x19,2,"[%s:%d] malloc loopback_buf failed\n","loopback_thread",0x4c3);
        goto LAB_000141ac;
      }
      param_1[8] = uVar4;
      uVar2 = uVar4;
    }
    else {
      uVar2 = param_1[8];
      if ((uint)param_1[8] < uVar4) {
        ak_mem_free(iVar3);
        uVar1 = ak_get_os_timestamp();
        iVar3 = ak_mem_alloc_(0x19,uVar4,"loopback_thread",uVar1);
        param_1[7] = iVar3;
        if (iVar3 == 0) {
          ak_print(0x19,2,"[%s:%d] relloc loopback_buf failed\n","loopback_thread",0x4cc);
          goto LAB_000141ac;
        }
        param_1[8] = uVar4;
        uVar2 = uVar4;
      }
    }
    osal_loopback_read(param_1[5],iVar3,uVar2);
    ak_print(0x19,5,"[%s:%d] get loopback data failed\n","loopback_thread",0x4d5);
    ak_sleep_ms(10);
    iVar3 = param_1[4];
  } while( true );
  ak_print(0x19,2,"[%s:%d] aec_enable=%d, ai_open=%d, ao_open =%d\n","loopback_thread",0x4bb,
           param_1[1],param_1[2],param_1[3]);
  ak_sleep_ms(10);
  goto LAB_00014120;
}



undefined4 FUN_00014430(short *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  if (param_1 == (short *)0x0) {
    ak_print(0x19,1,"[%s:%d] nr_attr is NULL\n","check_nr_param",0x36d);
    return 0x101;
  }
  uVar1 = *(uint *)(param_1 + 4);
  if (uVar1 < 2) {
    uVar2 = 0;
    if (uVar1 != 0) {
      if ((ushort)(*param_1 + 0x3cU) < 0x3c) {
        uVar2 = 0;
      }
      else {
        ak_print(0x19,1,"[%s:%d] noise_suppress_db must in [-60,0)\n","check_nr_param",0x377);
        uVar2 = 0x101;
      }
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] enable =%d, nr_enable must be 0 or 1\n","check_nr_param",0x372,uVar1);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 FUN_00014514(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] agc_attr is NULL\n","check_agc_param",0x380);
    return 0x101;
  }
  if ((uint)param_1[4] < 2) {
    uVar1 = 0;
    if (param_1[4] != 0) {
      if (*param_1 - 1U < 0x7fff) {
        if ((ushort)((short)param_1[1] - 2U) < 7) {
          if (*(ushort *)((int)param_1 + 6) < 0x401) {
            if (*(ushort *)(param_1 + 2) < 0x65) {
              uVar1 = 0;
            }
            else {
              ak_print(0x19,1,"[%s:%d] near_sensitivity must in 1~100\n","check_agc_param",0x39c);
              uVar1 = 0x101;
            }
          }
          else {
            ak_print(0x19,1,"[%s:%d] agc_min_gain must in 0~1024\n","check_agc_param",0x395);
            uVar1 = 0x101;
          }
        }
        else {
          ak_print(0x19,1,"[%s:%d] agc_max_gain must in 2~8\n","check_agc_param",0x391);
          uVar1 = 0x101;
        }
      }
      else {
        ak_print(0x19,1,"[%s:%d] agc_level must in 1~32767\n","check_agc_param",0x38d);
        uVar1 = 0x101;
      }
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] agc_enable must be 0 or 1\n","check_agc_param",0x385);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 FUN_000146ac(uint *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] aec_attr is NULL\n","check_aec_param",0x3a7);
    return 0x101;
  }
  if (param_1[4] < 2) {
    uVar1 = 0;
    if (param_1[4] != 0) {
      if (*(ushort *)((int)param_1 + 6) < 0x401) {
        if ((ushort)param_1[1] < 0x401) {
          if (*param_1 < 0x8000) {
            uVar1 = 0;
          }
          else {
            ak_print(0x19,1,"[%s:%d] audio_out_threshold must in 0~32767\n","check_aec_param",0x3bd)
            ;
            uVar1 = 0x101;
          }
        }
        else {
          ak_print(0x19,1,"[%s:%d] audio_out_digi_gain must in 0~1024\n","check_aec_param",0x3b9);
          uVar1 = 0x101;
        }
      }
      else {
        ak_print(0x19,1,"[%s:%d] audio_in_digi_gain must in 0~1024\n","check_aec_param",0x3b5);
        uVar1 = 0x101;
      }
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] aec_enable must be 0 or 1\n","check_aec_param",0x3ac);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 FUN_000147f8(short *param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int *piVar3;
  short *psVar4;
  int iVar5;
  byte *pbVar6;
  
  if (param_1 == (short *)0x0) {
    ak_print(0x19,1,"[%s:%d] eq_attr is NULL\n","check_eq_param",0x3c6);
    return 0x101;
  }
  if (*(byte *)(param_1 + 0x3e) < 2) {
    if (*(byte *)(param_1 + 0x3e) == 0) {
      uVar2 = 0;
    }
    else if (*(uint *)(param_1 + 2) < 0xb) {
      if ((ushort)(*param_1 + 0x3000U) < 0x6001) {
        pbVar6 = (byte *)(param_1 + 0x3e);
        psVar4 = param_1 + 0x2c;
        piVar3 = (int *)(param_1 + 4);
        iVar5 = 0;
        do {
          pbVar6 = pbVar6 + 1;
          bVar1 = *pbVar6;
          if (1 < bVar1) {
            ak_print(0x19,1,"[%s:%d] band_enable must be 0 or 1, now band_enable[%d]=%d\n",
                     "check_eq_param",0x3df,iVar5,bVar1);
            return 0x101;
          }
          iVar5 = iVar5 + 1;
          if (bVar1 != 0) {
            if (0x6816 < *piVar3 - 0x14U) {
              ak_print(0x19,1,"[%s:%d] bandfreqs must in 20~26666\n","check_eq_param",0x3e6);
              return 0x101;
            }
            if (psVar4[-0x14] == 0) {
              if (1 < (ushort)(*psVar4 - 1U)) {
                ak_print(0x19,1,"[%s:%d] bandgains must not be 0\n","check_eq_param",0x3ea);
                return 0x101;
              }
            }
            else if (4 < (ushort)(*psVar4 - 1U)) {
              ak_print(0x19,1,"[%s:%d] band_types must in 1~5\n","check_eq_param",0x3f6);
              return 0x101;
            }
          }
          psVar4 = psVar4 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar5 != 10);
        uVar2 = 0;
      }
      else {
        ak_print(0x19,1,"[%s:%d] pre_gain must in -12288~12288, pre_gain =%d, error\n",
                 "check_eq_param",0x3d8,(int)*param_1);
        uVar2 = 0x101;
      }
    }
    else {
      ak_print(0x19,1,"[%s:%d] bands must in 0~10, bands =%lu, error\n","check_eq_param",0x3d3,
               *(uint *)(param_1 + 2));
      uVar2 = 0x101;
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] eq_enable must be 0 or 1\n","check_eq_param",0x3cb);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 FUN_00014a64(uint *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] aslc_enable is enable, but aslc_attr is NULL\n","check_aslc_param",
             0x400);
    return 0x101;
  }
  if (0x6e < param_1[1] + 0x5a) {
    ak_print(0x19,1,"[%s:%d] aslc_db =%ld, aslc_db must be -90~20\n","check_aslc_param",0x405,
             param_1[1]);
    return 0x101;
  }
  if (*param_1 < 0x8001) {
    uVar1 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] limit =%ld, limit must be 0~32768\n","check_aslc_param",0x409,*param_1)
    ;
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 FUN_00014b38(undefined4 param_1,ushort param_2,undefined *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  uint local_14;
  
  local_14 = (uint)param_2;
  local_18 = 1;
  iVar1 = (*(code *)param_3)(param_1,1,&local_18);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","nr_enable",0x634);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 FUN_00014bb0(undefined4 param_1,undefined *param_2,undefined *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar1 = (*(code *)param_2)(param_1,&local_18);
  if (iVar1 != 1) {
    ak_print(0x19,5,"[%s:%d] nr not open \n ","nr_disable",0x63f);
  }
  local_18 = 0;
  iVar1 = (*(code *)param_3)(param_1,1,&local_18);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","nr_disable",0x644);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 FUN_00014c6c(undefined4 param_1,undefined *param_2,undefined *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_94 [132];
  
  memset(auStack_94,0,0x84);
  iVar1 = (*(code *)param_2)(param_1,auStack_94);
  if (iVar1 == 1) {
    iVar1 = (*(code *)param_3)(param_1,0,auStack_94);
    if (iVar1 == 1) {
      uVar2 = 0;
    }
    else {
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNearEqParam failed\n ","eq_disable",0x626);
      uVar2 = 0xffffffff;
    }
  }
  else {
    ak_print(0x19,5,"[%s:%d] eq not open\n ","eq_disable",0x621);
    uVar2 = 0;
  }
  return uVar2;
}



undefined4 FUN_00014d38(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  int local_c;
  
  local_c = param_3 << 10;
  local_10 = param_2;
  iVar1 = (*(code *)param_4)(param_1,1,&local_10);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","aslc_enable",0x671);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



void FUN_00014da8(undefined4 param_1,undefined2 *param_2,undefined4 *param_3,undefined *param_4)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar1 = (*(code *)param_4)(param_1,&local_18);
  if (iVar1 != 1) {
    ak_print(0x19,3,"[%s:%d] nr not open\n ","get_nr_param",0x564);
  }
  *param_3 = local_18;
  *param_2 = (undefined2)local_14;
  return;
}



undefined4 FUN_00014e1c(undefined4 param_1,undefined4 *param_2,int *param_3,undefined *param_4)

{
  int iVar1;
  undefined4 local_18;
  int local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar1 = (*(code *)param_4)(param_1,&local_18);
  if (iVar1 != 1) {
    ak_print(0x19,5,"[%s:%d] aslc not open\n ","get_aslc_param",0x5ce);
    *param_3 = 0;
    return 0x19000001;
  }
  if (local_14 < 0) {
    local_14 = local_14 + 0x3ff;
  }
  *param_3 = local_14 >> 10;
  *param_2 = local_18;
  return 0;
}



void FUN_00014eb8(int param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_1c;
  int local_18 [3];
  
  if (param_2 == 0) {
    return;
  }
  uVar4 = *(uint *)(param_3 + 0x14);
  uVar1 = *(undefined2 *)(param_3 + 4);
  uVar2 = *(undefined2 *)(param_3 + 6);
  *(undefined2 *)(param_1 + 0x28) = *(undefined2 *)(param_3 + 0xc);
  *(undefined2 *)(param_1 + 0x2a) = uVar1;
  *(undefined2 *)(param_1 + 0x2c) = uVar2;
  *(undefined4 *)(param_1 + 0x24) = 1;
  if (0x8000 < uVar4) {
    ak_print(0x19,1,"[%s:%d] audio_farBreakdownThresh must in 0 ~ 32768,if not use default 0 \n ",
             "save_aec_param_to_user",0x4ee);
    uVar4 = 0;
    *(undefined4 *)(param_3 + 0x14) = 0;
  }
  *(uint *)(param_1 + 0x34) = uVar4;
  *(undefined4 *)(param_1 + 4) = 1;
  if (*(int *)(param_1 + 0xc) != 0) {
    local_1c = 0;
    local_18[0] = 0;
    local_18[1] = 0;
    iVar3 = FUN_00014e1c(*(undefined4 *)(param_1 + 0xc4),&local_1c,local_18,
                         &_SD_Echo_GetFarVolumeParam);
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x30) = local_1c;
      return;
    }
  }
  *(undefined4 *)(param_1 + 0x30) = 0x8000;
  return;
}



undefined4 FUN_00014f9c(undefined4 param_1)

{
  ak_print(0x19,1,"[%s:%d] user not support %d \n","get_vqe_user_handle",0x34b,param_1);
  return 0;
}



undefined4 FUN_00014fe4(uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_1 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] vad_attr is NULL\n","check_vad_param",0x46b);
    return 0x101;
  }
  if (param_1[2] < 2) {
    if (0x8000 < *param_1) {
      ak_print(0x19,1,"[%s:%d] vad_thresh must in [0-32768] \n","check_vad_param",0x473);
      return 0x101;
    }
    if (param_1[1] < 5) {
      uVar2 = param_1[3];
      uVar1 = 0;
      if (uVar2 - 4 < 0x7ffc || 0x8003 < uVar2) {
        ak_print(0x19,1,"[%s:%d] vad_type = 0x%x must in [0,3]\n","check_vad_param",0x47c,uVar2);
        uVar1 = 0x101;
      }
    }
    else {
      ak_print(0x19,1,"[%s:%d] vad_level must little then MAX_SDET_SENSITIVITY(5) (0-4)\n",
               "check_vad_param",0x477);
      uVar1 = 0x101;
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] enable =%d, vad_enable must be 0 or 1\n","check_vad_param",0x46f,
             param_1[2]);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 FUN_0001515c(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    ak_print(0x19,1,"[%s:%d] hs_attr is NULL\n","check_hs_param",0x35f);
    return 0x101;
  }
  if (*(uint *)(param_1 + 4) < 2) {
    uVar1 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] enable =%d, nr_enable must be 0 or 1\n","check_hs_param",0x364,
             *(uint *)(param_1 + 4));
    uVar1 = 0x101;
  }
  return uVar1;
}



void FUN_00015274(undefined4 param_1)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  FUN_00014da8(param_1,(undefined2 *)&local_14,&local_c,&_SD_Echo_GetFarNrParam);
  ak_set_debug_str_info(0x19,1,"\nAO nr---","-------");
  ak_set_debug_num_info(0x19,1,"AO nr enable ",local_c);
  ak_set_debug_num_info(0x19,1,"AO noise Suppress db ",(int)(short)local_14);
  return;
}



void FUN_00015304(undefined4 param_1)

{
  short local_90 [2];
  undefined4 local_8c;
  undefined1 local_14;
  
  memset(local_90,0,0x88);
  FUN_00013a7c(param_1,local_90,&_SD_Echo_GetFarEqParam);
  ak_set_debug_str_info(0x19,1,"\nAO eq--","-------");
  ak_set_debug_num_info(0x19,1,"AO eq enable ",local_14);
  ak_set_debug_num_info(0x19,1,"AO eq bands num ",local_8c);
  ak_set_debug_num_info(0x19,1,"AO eq pre gain ",(int)local_90[0]);
  return;
}



void FUN_000153b8(undefined4 param_1)

{
  undefined4 local_14;
  int local_10 [2];
  
  local_14 = 0;
  local_10[0] = 0;
  local_10[1] = 0;
  FUN_00014e1c(param_1,&local_14,local_10,&_SD_Echo_GetFarVolumeParam);
  ak_set_debug_str_info(0x19,1,"\nAO aslc---","-------");
  ak_set_debug_num_info(0x19,1,"AO limit ",local_14);
  ak_set_debug_num_info(0x19,1,"AO volume ",local_10[0]);
  return;
}



void FUN_00015448(undefined4 param_1)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  FUN_00014da8(param_1,(undefined2 *)&local_14,&local_c,&_SD_Echo_GetNrParam);
  ak_set_debug_str_info(0x19,1,"\nAI nr---","-------");
  ak_set_debug_num_info(0x19,1,"AI nr enable ",local_c);
  ak_set_debug_num_info(0x19,1,"AI noise Suppress db ",(int)(short)local_14);
  return;
}



void FUN_000154d8(undefined4 param_1)

{
  short local_90 [2];
  undefined4 local_8c;
  undefined1 local_14;
  
  memset(local_90,0,0x88);
  FUN_00013a7c(param_1,local_90,&_SD_Echo_GetNearEqParam);
  ak_set_debug_str_info(0x19,1,"\nAI eq---","-------");
  ak_set_debug_num_info(0x19,1,"AI eq enable ",local_14);
  ak_set_debug_num_info(0x19,1,"AI eq bands num ",local_8c);
  ak_set_debug_num_info(0x19,1,"AI eq pre gain",(int)local_90[0]);
  return;
}



void FUN_0001558c(undefined4 param_1)

{
  undefined4 local_14;
  int local_10 [2];
  
  local_14 = 0;
  local_10[0] = 0;
  local_10[1] = 0;
  FUN_00014e1c(param_1,&local_14,local_10,&_SD_Echo_GetNearVolumeParam);
  ak_set_debug_str_info(0x19,1,"\nAI aslc---","-------");
  ak_set_debug_num_info(0x19,1,"AI limit ",local_14);
  ak_set_debug_num_info(0x19,1,"AI volume ",local_10[0]);
  return;
}



void FUN_0001561c(uint param_1,size_t param_2,void *param_3,char *param_4,int *param_5)

{
  char cVar1;
  size_t sVar2;
  size_t sVar3;
  int iVar4;
  char *__dest;
  int iVar5;
  FILE *pFVar6;
  int iVar7;
  char *__s;
  int iVar8;
  int local_2a8;
  int local_2a4;
  int local_2a0;
  int local_29c;
  int local_298;
  int local_294;
  char acStack_28c [616];
  
  if ((*param_5 != 0) && ((param_1 & 0x1000000) != 0)) {
    iVar8 = 0;
    iVar7 = 0;
    do {
      if (param_1 == *(uint *)(dump_wav_list + iVar8)) {
        iVar8 = iVar7 * 0x27c;
        pFVar6 = *(FILE **)(dump_wav_list + iVar8 + 8);
        if (pFVar6 == (FILE *)0x0) {
          ak_get_localdate(&local_2a8,param_2,param_3,ak_get_localdate);
          sVar2 = strlen(s__tmp__00031418);
          sVar3 = strlen("/tmp/");
          if ((sVar2 == sVar3) && (iVar4 = strcmp(s__tmp__00031418,"/tmp/"), iVar4 == 0)) {
            sprintf(acStack_28c,"/tmp/%d-%d-%d-%d-%d-%d_%03x_%s.wav",local_2a8,local_2a4,local_2a0,
                    local_29c,local_298,local_294,*(uint *)(dump_wav_list + iVar8) & 0xfff,
                    *(char **)(dump_wav_list + iVar8 + 4));
          }
          else {
            FUN_00013f68((int)(dump_wav_list + iVar8));
            sprintf(acStack_28c,"%s%d-%d-%d-%d-%d-%d_%03x_%s.wav",s__tmp__00031418,local_2a8,
                    local_2a4,local_2a0,local_29c,local_298,local_294,
                    *(uint *)(dump_wav_list + iVar7 * 0x27c) & 0xfff,
                    *(char **)(dump_wav_list + iVar7 * 0x27c + 4));
          }
          pFVar6 = fopen(acStack_28c,"wb");
          iVar4 = iVar7 * 0x27c;
          *(FILE **)(dump_wav_list + iVar4 + 8) = pFVar6;
          if (pFVar6 == (FILE *)0x0) {
            ak_print(0x19,1,"[%s:%d] open %s failed\n","open_dump_item_file",0x2b9,acStack_28c);
            pFVar6 = *(FILE **)(dump_wav_list + iVar4 + 8);
          }
          else {
            memcpy(dump_wav_list + iVar4 + 0x18,acStack_28c,0x264);
            *(undefined4 *)(dump_wav_list + iVar4 + 0xc) = 0;
            memcpy(dump_wav_list + iVar4 + 0x10,param_4,8);
            memcpy(&DAT_00031664,&WAVE_0001eb0c,4);
            DAT_00031668 = 0x24;
            memcpy(&DAT_0003166c,"WAVEfmt ",8);
            DAT_0003167c = *(int *)(param_4 + 4);
            DAT_00031678 = 1;
            DAT_00031674 = 0x10;
            cVar1 = *param_4;
            DAT_00031680 = (int)cVar1 * DAT_0003167c * 2;
            DAT_00031684 = (undefined2)((int)cVar1 << 1);
            DAT_0003167a = (short)cVar1;
            DAT_00031686 = (short)param_4[1];
            memcpy(&DAT_00031688,&DAT_0001eb20,4);
            DAT_0003168c = 0;
            fwrite(&DAT_00031664,1,0x2c,*(FILE **)(dump_wav_list + iVar4 + 8));
            pFVar6 = *(FILE **)(dump_wav_list + iVar4 + 8);
          }
          if (pFVar6 == (FILE *)0x0) {
            return;
          }
        }
        sVar2 = fwrite(param_3,1,param_2,pFVar6);
        if ((int)sVar2 < (int)param_2) {
          ak_print(0x19,1,
                   "[%s:%d] dump fwrite error, item:%s, sdata:%ld, swrite:%d, fd=%p, data=%p\n",
                   "write_dump_item_file",0x2d7,*(undefined4 *)(dump_wav_list + iVar7 * 0x27c + 4),
                   param_2,sVar2,*(undefined4 *)(dump_wav_list + iVar7 * 0x27c + 8),param_3);
        }
        iVar5 = *(int *)(dump_wav_list + iVar7 * 0x27c + 0xc);
        *(size_t *)(dump_wav_list + iVar7 * 0x27c + 0xc) = param_2 + iVar5;
        iVar4 = DAT_00031618;
        if (param_1 == 0x1000030) {
          iVar4 = DAT_00031618 << 1;
        }
        if (*(int *)(dump_wav_list + iVar7 * 0x27c + 8) == 0 || (int)(param_2 + iVar5 >> 10) < iVar4
           ) {
          return;
        }
        __s = dump_wav_list + iVar7 * 0x27c + 0x18;
        FUN_00013f68((int)(dump_wav_list + iVar8));
        sVar2 = strlen(__s);
        if ((sVar2 < 0x264) && (sVar3 = strlen("_dump.wav"), sVar3 < 0x264 - sVar2)) {
          memset(acStack_28c,0,0x264);
          sVar2 = strlen(__s);
          memcpy(acStack_28c,__s,sVar2);
          __dest = strstr(acStack_28c,".wav");
          sVar2 = strlen("_dump.wav");
          memcpy(__dest,"_dump.wav",sVar2);
          rename(__s,acStack_28c);
          return;
        }
        ak_print(0x19,1,"[%s:%d] file_name is too long\n","dump_debug_file",0x309);
        return;
      }
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 0x27c;
    } while (iVar7 != 8);
  }
  return;
}



undefined4 FUN_00015b24(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  iVar1 = _SD_Echo_GetAecParam(param_1,&local_24);
  if (iVar1 == 1) {
    *(undefined4 *)(param_2 + 0x10) = local_24;
    *(undefined2 *)(param_2 + 6) = (undefined2)local_1c;
    *(undefined2 *)(param_2 + 4) = local_20._2_2_;
    *(undefined2 *)(param_2 + 0xc) = (undefined2)local_20;
    *(undefined4 *)(param_2 + 0x14) = local_14;
    ak_set_debug_num_info(0x19,1,"AO limit ",local_18);
    ak_set_debug_num_info(0x19,1,"farBreakdownThresh",local_14);
    uVar2 = 0;
  }
  else {
    ak_print(0x19,5,"[%s:%d] aec not open\n ","get_aec_param",0x58f);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



void FUN_00015c08(undefined4 param_1)

{
  int iVar1;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  uint local_64;
  undefined4 local_60;
  undefined4 local_5c;
  char acStack_58 [68];
  
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  iVar1 = FUN_00015b24(param_1,(int)&local_70);
  if (iVar1 != 0) {
    return;
  }
  ak_set_debug_str_info(0x19,1,"\naec--","-------");
  ak_set_debug_num_info(0x19,1,"aec enable ",local_60);
  ak_set_debug_num_info(0x19,1,"tail ",local_64 & 0xffff);
  memset(acStack_58,0,0x40);
  memset(acStack_58,0,0x40);
  iVar1 = (short)local_6c * 100;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x3ff;
  }
  snprintf(acStack_58,0x40,"audio out digi gain = %d %%",iVar1 >> 10);
  ak_debug_info(0x19,1,acStack_58);
  memset(acStack_58,0,0x40);
  iVar1 = local_6c._2_2_ * 100;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x3ff;
  }
  snprintf(acStack_58,0x40,"audio in digi gain = %d %%\n",iVar1 >> 10);
  ak_debug_info(0x19,1,acStack_58);
  return;
}



void FUN_00015d78(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  if (param_1[4] != 0) {
    param_1[4] = 0;
    ak_thread_join(param_1[6]);
    if (param_1[5] != 0) {
      osal_loopback_close();
      param_1[5] = 0xffffffff;
    }
    if (param_1[7] != 0) {
      ak_mem_free();
      param_1[7] = 0;
      param_1[8] = 0;
    }
  }
  puVar2 = param_1 + 0x23;
  iVar1 = ak_thread_mutex_lock(puVar2);
  if (iVar1 == 0) {
    local_24 = iVar1;
    local_20 = iVar1;
    local_1c = iVar1;
    local_18 = iVar1;
    local_14 = iVar1;
    memcpy(&local_24,param_1 + 9,0x14);
    local_24 = iVar1;
    iVar1 = _SD_Echo_SetAecParam(*param_1,1,&local_24);
    if (iVar1 != 1) {
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAecParam failed\n ","aec_stop",0x738);
      ak_thread_mutex_unlock(puVar2);
      return;
    }
    ak_thread_mutex_unlock(puVar2);
    FUN_00015c08(*param_1);
  }
  else {
    ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","aec_stop",0x72e,iVar1);
  }
  return;
}



undefined4 FUN_00015ef0(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = _SD_Echo_Close(), iVar1 == 1)) {
    return 0;
  }
  ak_print(0x19,1,"[%s:%d] _SD_Echo_Close error\n","close_echo_lib",0x7f6);
  return 0x19000007;
}



undefined4 FUN_00015f60(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  iVar1 = _SD_Echo_GetVadParam(param_1,&local_14);
  if (iVar1 != 1) {
    ak_print(0x19,5,"[%s:%d] nr not open \n ","vad_disable",0x6a8);
  }
  local_14 = 0;
  iVar1 = _SD_Echo_SetVadParam(param_1,1,&local_14);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetVadParam failed\n ","vad_disable",0x6ad);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 FUN_00016028(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_c = param_2[1];
  local_14 = param_2[3];
  local_10 = *param_2;
  iVar1 = _SD_Echo_SetVadParam(param_1,1,&local_14);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] _SD_Echo_SetVadParam failed\n ","vad_enable",0x69d);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 FUN_000160ac(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined2 local_20;
  undefined2 local_1e;
  uint local_1c;
  
  local_24 = *param_2;
  local_20 = *(undefined2 *)(param_2 + 1);
  local_1e = *(undefined2 *)((int)param_2 + 6);
  local_28 = 1;
  local_1c = (uint)*(ushort *)(param_2 + 2);
  iVar1 = _SD_Echo_SetAgcParam(param_1,1,&local_28);
  if (iVar1 == 1) {
    uVar2 = 0;
  }
  else {
    ak_print(0x19,1,"[%s:%d] set agc failed\n ","agc_enable",0x655);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



void FUN_00016144(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  iVar1 = _SD_Echo_GetVadParam(param_1,&local_14);
  if (iVar1 == 1) {
    param_2[3] = local_14;
    param_2[2] = (uint)(local_14 != 0);
    *param_2 = local_10;
    param_2[1] = local_c;
    return;
  }
  ak_print(0x19,3,"[%s:%d] vad not open\n ","get_vad_param",0x5e5);
  return;
}



void FUN_000161d8(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  iVar1 = _SD_Echo_GetAgcParam(param_1,&local_18);
  if (iVar1 == 1) {
    param_2[4] = local_18;
    *param_2 = local_14;
    *(undefined2 *)(param_2 + 1) = (undefined2)local_10;
    *(undefined2 *)((int)param_2 + 6) = local_10._2_2_;
    *(undefined2 *)(param_2 + 2) = (undefined2)local_c;
    return;
  }
  ak_print(0x19,3,"[%s:%d] agc not open\n ","get_agc_param",0x578);
  return;
}



void FUN_00016278(undefined4 param_1)

{
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  FUN_000161d8(param_1,&local_1c);
  ak_set_debug_str_info(0x19,1,"\nagc---","-------");
  ak_set_debug_num_info(0x19,1,"agc enable ",local_c);
  ak_set_debug_num_info(0x19,1,"agc level ",local_1c);
  ak_set_debug_num_info(0x19,1,"agc max gain ",(int)(short)local_18);
  ak_set_debug_num_info(0x19,1,"agc min gain ",(int)local_18._2_2_);
  ak_set_debug_num_info(0x19,1,"near sensitivity ",(int)(short)local_14);
  return;
}



undefined4 FUN_0001634c(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  
  puVar2 = param_1 + 0x23;
  param_1[9] = param_1[1];
  iVar1 = ak_thread_mutex_lock(puVar2);
  if (iVar1 == 0) {
    iVar1 = _SD_Echo_SetAecParam(*param_1,1,param_1 + 9);
    if (iVar1 != 1) {
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAecParam failed\n ","aec_start",0x71e);
      ak_thread_mutex_unlock(puVar2);
      return 0x19000007;
    }
    ak_thread_mutex_unlock(puVar2);
    if (param_1[4] == 0) {
      if ((param_1[1] == 0) || (param_1[2] == 0)) {
        ak_print(0x19,3,"[%s:%d] aec_enable =%d, user->ai_open=%d\n ","loopback_start",0x518,
                 param_1[1],param_1[2]);
        uVar3 = 0;
      }
      else {
        local_34 = osal_loopback_open(param_1[0x35],param_1 + 5);
        if (local_34 == 0) {
          local_30 = param_1[0x32];
          local_20 = 8;
          local_28 = 0x10;
          if (local_30 < 16000) {
            local_24 = 0x400;
          }
          else if (local_30 < 32000) {
            local_24 = 0x800;
          }
          else if (local_30 < 0xbb81) {
            local_24 = 0x1000;
          }
          else {
            local_24 = 0x2000;
          }
          local_2c = iVar1;
          local_1c = local_34;
          iVar1 = osal_loopback_set_param(param_1[5],&local_34);
          if (iVar1 == 0) {
            ak_print(0x19,4,"[%s:%d] aec enable, osal_loopback_open ok\n ","loopback_start",0x525);
            param_1[4] = 1;
            iVar1 = ak_thread_create(param_1 + 6,FUN_000140a8,param_1,0x19000,0x32);
            if (iVar1 == 0) {
              ak_print(0x19,3,"[%s:%d] create capture pcm thread OK\n","loopback_start",0x52e);
              uVar3 = 0;
            }
            else {
              ak_print(0x19,1,"create capture_pcm_thread FAILED, ret=%d\n",0x19000008);
              uVar3 = 0x19000008;
            }
          }
          else {
            ak_print(0x19,1,"[%s:%d] osal_loopback_set_param failed\n ","loopback_set_param",0x50b);
            ak_print(0x19,1,"[%s:%d] osal_loopback_open failed\n ","loopback_start",0x521);
            uVar3 = 0x19000009;
          }
        }
        else {
          ak_print(0x19,1,"[%s:%d] osal_loopback_open failed\n ","loopback_start",0x51c);
          uVar3 = 0x19000009;
        }
      }
    }
    else {
      ak_print(0x19,2,"[%s:%d] loopback start already\n ","loopback_start",0x514);
      uVar3 = 0;
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","aec_start",0x719,iVar1);
    uVar3 = 0x105;
  }
  return uVar3;
}



int ak_vqe_inner_open(int param_1,int *param_2,int *param_3,ushort *param_4,ushort *param_5,
                     int param_6)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int *__s;
  int *piVar5;
  bool bVar6;
  bool bVar7;
  
  ak_print(0x19,4,"[%s:%d] ak_vqe_inner_open entry...ai_vqe = %p, ao_vqe = %p\n","ak_vqe_inner_open"
           ,0x80b,param_4,param_5);
  uVar1 = _SD_GetAudioFilterVersionInfo();
  ak_set_debug_str_info(0x19,1,"--",uVar1);
  pcVar2 = ak_vqe_get_version();
  ak_set_debug_str_info(0x19,1,"vqe version",pcVar2);
  bVar6 = param_4 != (ushort *)0x0;
  if (bVar6 && param_2 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] ai_attr=NULL  ai_vqe!=NULL is error\n","check_echo_param",0x439);
    goto LAB_00016760;
  }
  bVar7 = param_5 != (ushort *)0x0;
  if (bVar7 && param_3 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] ao_attr=NULL  ao_vqe!=NULL is error\n","check_echo_param",0x43d);
    goto LAB_00016760;
  }
  if (param_2 == (int *)0x0 && param_3 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] ai_attr=NULL ao_attr=NULL is error\n","check_echo_param",0x441);
    goto LAB_00016760;
  }
  if (((bVar6) &&
      ((((iVar3 = FUN_00014430((short *)param_4), iVar3 != 0 ||
         (iVar3 = FUN_00014514((int *)(param_4 + 6)), iVar3 != 0)) ||
        (iVar3 = FUN_000146ac((uint *)(param_4 + 0x10)), iVar3 != 0)) ||
       ((iVar3 = FUN_000147f8((short *)(param_4 + 0x1c)), iVar3 != 0 ||
        (iVar3 = FUN_00014a64((uint *)(param_4 + 0x60)), iVar3 != 0)))))) ||
     ((bVar7 && (((iVar3 = FUN_00014430((short *)param_5), iVar3 != 0 ||
                  (iVar3 = FUN_000147f8((short *)(param_5 + 6)), iVar3 != 0)) ||
                 (iVar3 = FUN_00014a64((uint *)(param_5 + 0x4a)), iVar3 != 0))))))
  goto LAB_00016760;
  if (param_2 != (int *)0x0) {
    iVar3 = *param_2;
    if ((((iVar3 == 8000 || iVar3 == 12000) || (iVar3 == 0x2b11 || iVar3 == 16000)) ||
        (iVar3 == 0x5622 || iVar3 == 24000)) ||
       ((iVar3 == 32000 || iVar3 == 0xac44 || (iVar3 == 48000 || iVar3 == 96000)))) {
      if (param_2[1] == 0x10) {
        if (param_2[2] - 1U < 2) goto LAB_000168f0;
        uVar1 = 0x455;
LAB_00016978:
        ak_print(0x19,1,"[%s:%d] channel invalid \n","check_echo_param",uVar1);
        goto LAB_00016760;
      }
      uVar1 = 0x451;
LAB_000168d4:
      ak_print(0x19,1,"[%s:%d] sample bit invalid \n","check_echo_param",uVar1);
      goto LAB_00016760;
    }
    uVar1 = 0x44d;
LAB_000171a4:
    ak_print(0x19,1,"[%s:%d] sample rate invalid \n","check_echo_param",uVar1);
LAB_00016760:
    ak_print(0x19,1,"[%s:%d] check_echo_param error\n","ak_vqe_inner_open",0x810);
    return 0x101;
  }
LAB_000168f0:
  if (param_3 != (int *)0x0) {
    iVar3 = *param_3;
    if (((iVar3 != 8000 && iVar3 != 12000) && (iVar3 != 0x2b11 && iVar3 != 16000)) &&
       ((iVar3 != 0x5622 && iVar3 != 24000 &&
        ((iVar3 != 32000 && iVar3 != 0xac44 && (iVar3 != 48000 && iVar3 != 96000)))))) {
      uVar1 = 0x45a;
      goto LAB_000171a4;
    }
    if (param_3[1] != 0x10) {
      uVar1 = 0x45e;
      goto LAB_000168d4;
    }
    if (1 < param_3[2] - 1U) {
      uVar1 = 0x462;
      goto LAB_00016978;
    }
  }
  iVar3 = param_1 * 4;
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (*(int *)(&DAT_0003161c + iVar3) == 0) {
    uVar1 = ak_get_os_timestamp();
    __s = (int *)ak_mem_alloc_(0x19,0xd8,"ak_vqe_inner_open",uVar1);
    if (__s == (int *)0x0) {
      ak_print(0x19,1,"[%s:%d] malloc vqe_info error!\n","ak_vqe_inner_open",0x81b);
      iVar4 = 0x102;
      goto LAB_00016a30;
    }
    memset(__s,0,0xd8);
    __s[0xe] = 0;
    ak_thread_rwlock_init(__s + 0x10,0);
    ak_thread_mutex_init(__s + 0x23,0);
    ak_thread_mutex_init(__s + 0x29,0);
  }
  else {
    ak_print(0x19,5,"[%s:%d] already open\n","ak_vqe_inner_open",0x828);
    __s = *(int **)(&DAT_0003161c + iVar3);
  }
  if ((bVar7) && (__s[0x31] == 0)) {
    __s[0x35] = param_3[3];
    iVar4 = FUN_00013d44((int)__s,param_3,param_6,1);
    __s[0x31] = iVar4;
    if (iVar4 != 0) {
      memcpy(__s + 0x32,param_3,0xc);
      iVar4 = ak_thread_mutex_lock(__s + 0x29);
      if (iVar4 == 0) {
        if (*(int *)(param_5 + 4) == 0) {
          iVar4 = FUN_00014bb0(__s[0x31],&_SD_Echo_GetFarNrParam,&_SD_Echo_SetFarNrParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] ao nr disable failed\n ","set_ao_vqe",0x796);
          }
        }
        else {
          iVar4 = FUN_00014b38(__s[0x31],*param_5,&_SD_Echo_SetFarNrParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] ao nr enable failed\n ","set_ao_vqe",0x792);
          }
        }
        if ((char)param_5[0x44] == '\0') {
          iVar4 = FUN_00014c6c(__s[0x31],&_SD_Echo_GetFarEqParam,&_SD_Echo_SetFarEqParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] eq_enable failed\n","set_ao_vqe",0x7a0);
          }
        }
        else {
          iVar4 = FUN_00013bb8(__s[0x31],param_5 + 6,&_SD_Echo_SetFarEqParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] eq_enable failed\n","set_ao_vqe",0x79c);
          }
        }
        iVar4 = FUN_00014d38(__s[0x31],*(undefined4 *)(param_5 + 0x4a),*(int *)(param_5 + 0x4c),
                             &_SD_Echo_SetFarVolumeParam);
        if (iVar4 != 0) {
          ak_print(0x19,1,"[%s:%d] aslc_enable failed\n","set_ao_vqe",0x7a5);
        }
        ak_thread_mutex_unlock(__s + 0x29);
        FUN_00015274(__s[0x31]);
        FUN_00015304(__s[0x31]);
        FUN_000153b8(__s[0x31]);
        iVar4 = *param_3;
        __s[3] = 1;
        if (iVar4 < 16000) {
          iVar4 = 0x2000;
        }
        else if (iVar4 < 32000) {
          iVar4 = 0x4000;
        }
        else {
          iVar4 = 0x8000;
        }
        __s[0x2f] = iVar4;
        goto LAB_000169f4;
      }
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","set_ao_vqe",0x78c,iVar4);
      ak_print(0x19,1,"[%s:%d] set_ao_vqe error!\n","ak_vqe_inner_open",0x834);
      iVar4 = 0x19000007;
LAB_00016b14:
      ak_thread_mutex_destroy(__s + 0x23);
      ak_thread_mutex_destroy(__s + 0x29);
      ak_thread_rwlock_destroy(__s + 0x10);
      if (bVar6) goto LAB_00016b3c;
      FUN_00015ef0(__s[0x31]);
      goto LAB_00016b44;
    }
  }
  else {
LAB_000169f4:
    if ((bVar6) && (*__s == 0)) {
      iVar4 = FUN_00013d44((int)__s,param_2,param_6,0);
      *__s = iVar4;
      if (iVar4 == 0) goto LAB_00016a20;
      piVar5 = __s + 0x23;
      memcpy(__s + 0x20,param_2,0xc);
      iVar4 = ak_thread_mutex_lock(piVar5);
      if (iVar4 == 0) {
        if (*(int *)(param_4 + 4) == 0) {
          iVar4 = FUN_00014bb0(*__s,&_SD_Echo_GetNrParam,&_SD_Echo_SetNrParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","set_ai_vqe",0x74f);
          }
          ak_print(0x19,5,"[%s:%d] ai nr close success\n","set_ai_vqe",0x751);
        }
        else {
          iVar4 = FUN_00014b38(*__s,*param_4,&_SD_Echo_SetNrParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","set_ai_vqe",0x74a);
          }
          ak_print(0x19,5,"[%s:%d] ai nr open success\n","set_ai_vqe",0x74c);
        }
        if ((*(int *)(param_4 + 0xe) != 0) &&
           (iVar4 = FUN_000160ac(*__s,(undefined4 *)(param_4 + 6)), iVar4 != 0)) {
          ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAgcParam failed\n ","set_ai_vqe",0x756);
        }
        if ((char)param_4[0x5a] == '\0') {
          iVar4 = FUN_00014c6c(*__s,&_SD_Echo_GetNearEqParam,&_SD_Echo_SetNearEqParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] eq_enable failed\n","set_ai_vqe",0x760);
          }
        }
        else {
          iVar4 = FUN_00013bb8(*__s,param_4 + 0x1c,&_SD_Echo_SetNearEqParam);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] eq_enable failed\n","set_ai_vqe",0x75c);
          }
        }
        iVar4 = FUN_00014d38(*__s,*(undefined4 *)(param_4 + 0x60),*(int *)(param_4 + 0x62),
                             &_SD_Echo_SetNearVolumeParam);
        if (iVar4 != 0) {
          ak_print(0x19,1,"[%s:%d] aslc_enable failed\n","set_ai_vqe",0x765);
        }
        ak_print(0x19,5,"[%s:%d] ai aslc set attribute success\n","set_ai_vqe",0x767);
        if (*(int *)(param_4 + 0x18) != 0) {
          FUN_00014eb8((int)__s,*(int *)(param_4 + 0x18),(int)(param_4 + 0x10));
          ak_print(0x19,4,"[%s:%d] aec need to open\n ","set_ai_vqe",0x76c);
        }
        if (*(int *)(param_4 + 0x6a) == 0) {
          iVar4 = FUN_00015f60(*__s);
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetVadParam failed\n ","set_ai_vqe",0x776);
          }
          ak_print(0x19,5,"[%s:%d] ai vad close success\n","set_ai_vqe",0x778);
        }
        else {
          iVar4 = FUN_00016028(*__s,(undefined4 *)(param_4 + 0x66));
          if (iVar4 != 0) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetVadParam failed\n ","set_ai_vqe",0x771);
          }
          ak_print(0x19,5,"[%s:%d] ai vad open success @@@@@\n","set_ai_vqe",0x773);
        }
        ak_thread_mutex_unlock(piVar5);
        FUN_00015448(*__s);
        FUN_00016278(*__s);
        FUN_000154d8(*__s);
        FUN_0001558c(*__s);
        ak_print(0x19,5,"[%s:%d] set_ai_vqe end\n","set_ai_vqe",0x782);
        iVar4 = *param_2;
        __s[2] = 1;
        if (iVar4 < 16000) {
          iVar4 = 0x2000;
        }
        else if (iVar4 < 32000) {
          iVar4 = 0x4000;
        }
        else {
          iVar4 = 0x8000;
        }
        __s[0x30] = iVar4;
        goto LAB_00016a08;
      }
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","set_ai_vqe",0x744,iVar4);
      ak_print(0x19,1,"[%s:%d] set_ai_vqe error!\n","ak_vqe_inner_open",0x844);
      ak_thread_mutex_destroy(piVar5);
      ak_thread_mutex_destroy(__s + 0x29);
      ak_thread_rwlock_destroy(__s + 0x10);
      iVar4 = 0x19000007;
LAB_00016b3c:
      FUN_00015ef0(*__s);
LAB_00016b44:
      ak_mem_free(__s);
      *(undefined4 *)(&DAT_0003161c + iVar3) = 0;
      goto LAB_00016a30;
    }
LAB_00016a08:
    if ((__s[3] != 0) && (__s[2] != 0)) {
      iVar4 = FUN_0001634c(__s);
      FUN_00015c08(*__s);
      if (iVar4 != 0) goto LAB_00016b14;
    }
  }
LAB_00016a20:
  iVar4 = 0;
  *(int **)(&DAT_0003161c + iVar3) = __s;
LAB_00016a30:
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,3,"[%s:%d] ak_vqe_inner_open exit...\n","ak_vqe_inner_open",0x864);
  return iVar4;
}



int ak_vqe_inner_set_ai_nr(uint param_1,ushort *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00014430((short *)param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_nr",0x879);
    iVar1 = 0x19000004;
    goto LAB_00017424;
  }
  iVar1 = ak_thread_mutex_lock(puVar2 + 0x23);
  if (iVar1 != 0) {
    ak_print(6,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_nr",0x880,iVar1);
    goto LAB_00017424;
  }
  if (*(int *)(param_2 + 4) == 0) {
    iVar3 = FUN_00014bb0(*puVar2,&_SD_Echo_GetNrParam,&_SD_Echo_SetNrParam);
    if (iVar3 != 0) {
      uVar4 = 0x88a;
      goto LAB_00017464;
    }
  }
  else {
    iVar3 = FUN_00014b38(*puVar2,*param_2,&_SD_Echo_SetNrParam);
    if (iVar3 != 0) {
      uVar4 = 0x886;
LAB_00017464:
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetNrParam failed\n ","ak_vqe_inner_set_ai_nr",uVar4);
    }
  }
  ak_thread_mutex_unlock(puVar2 + 0x23);
  FUN_00015448(*puVar2);
LAB_00017424:
  ak_thread_rwlock_unlock(DAT_00031624);
  return iVar1;
}



undefined4 ak_vqe_inner_get_ai_nr(uint param_1,undefined2 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined2 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_nr",0x8a8);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00014da8(*puVar1,param_2,(undefined4 *)(param_2 + 4),&_SD_Echo_GetNrParam);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_nr",0x8b0);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] nr_attr is NULL\n","ak_vqe_inner_get_ai_nr",0x8a0);
  return 0x100;
}



int ak_vqe_inner_set_ai_agc(uint param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ai_agc",0x8be);
  iVar1 = FUN_00014514(param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_agc",0x8c8);
    iVar1 = 0x19000004;
    goto LAB_000176f8;
  }
  iVar1 = ak_thread_mutex_lock(puVar2 + 0x23);
  if (iVar1 != 0) {
    ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_agc",0x8cf,iVar1);
    goto LAB_000176f8;
  }
  if (param_2[4] == 0) {
    uVar4 = *puVar2;
    local_30 = iVar1;
    local_2c = iVar1;
    local_28 = iVar1;
    local_24 = iVar1;
    iVar3 = _SD_Echo_GetAgcParam(uVar4,&local_30);
    if (iVar3 != 1) {
      ak_print(0x19,5,"[%s:%d] agc not open\n ","agc_disable",0x65f);
    }
    local_30 = 0;
    iVar3 = _SD_Echo_SetAgcParam(uVar4,1,&local_30);
    if (iVar3 != 1) {
      ak_print(0x19,1,"[%s:%d] set agc failed\n ","agc_disable",0x664);
      uVar4 = 0x8d9;
      goto LAB_000177c4;
    }
  }
  else {
    iVar3 = FUN_000160ac(*puVar2,param_2);
    if (iVar3 != 0) {
      uVar4 = 0x8d5;
LAB_000177c4:
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAgcParam failed\n ","ak_vqe_inner_set_ai_agc",uVar4);
    }
  }
  ak_thread_mutex_unlock(puVar2 + 0x23);
  FUN_00016278(*puVar2);
LAB_000176f8:
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ai_agc",0x8e2);
  return iVar1;
}



undefined4 ak_vqe_inner_get_ai_agc(uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_agc",0x8f8);
      uVar2 = 0x19000004;
    }
    else {
      FUN_000161d8(*puVar1,param_2);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_agc",0x900);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] nr_attr is NULL\n","ak_vqe_inner_get_ai_agc",0x8f0);
  return 0x100;
}



undefined4 ak_vqe_inner_set_ai_aec(uint param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_000146ac(param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar2 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar2 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_aec",0x916);
      uVar3 = 0x19000004;
    }
    else {
      if (param_2[4] == 0) {
        puVar2[1] = 0;
        FUN_00015d78(puVar2);
      }
      else {
        FUN_00014eb8((int)puVar2,param_2[4],(int)param_2);
        ak_print(0x19,4,"[%s:%d] aec need to open\n ","ak_vqe_inner_set_ai_aec",0x91d);
      }
      if ((((puVar2[3] == 0) || (puVar2[2] == 0)) || (puVar2[1] == 0)) ||
         (iVar1 = FUN_0001634c(puVar2), iVar1 == 0)) {
        FUN_00015c08(*puVar2);
        uVar3 = 0;
      }
      else {
        ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAecParam failed\n ","ak_vqe_inner_set_ai_aec",0x925);
        uVar3 = 0xffffffff;
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ai_aec",0x92f);
    return uVar3;
  }
  return 0x101;
}



undefined4 ak_vqe_inner_get_ai_aec(uint param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_get_ai_aec",0x93c);
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_aec",0x947);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00015b24(*puVar1,param_2);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_aec",0x94f);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] aec_attr is NULL\n","ak_vqe_inner_get_ai_aec",0x93f);
  return 0x100;
}



int ak_vqe_inner_set_ai_aslc(uint param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ai_aslc",0x95c);
  if (param_2 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] aslc_attr is NULL\n","ak_vqe_inner_set_ai_aslc",0x95f);
    return 0x100;
  }
  iVar1 = FUN_00014a64(param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar2 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar2 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_aslc",0x96b);
      iVar1 = 0x19000004;
    }
    else {
      iVar1 = ak_thread_mutex_lock(puVar2 + 0x23);
      if (iVar1 == 0) {
        iVar3 = FUN_00014d38(*puVar2,*param_2,param_2[1],&_SD_Echo_SetNearVolumeParam);
        if (iVar3 != 0) {
          ak_print(0x19,1,"[%s:%d] aslc_enable failed\n","ak_vqe_inner_set_ai_aslc",0x977);
        }
        ak_thread_mutex_unlock(puVar2 + 0x23);
        FUN_0001558c(*puVar2);
      }
      else {
        ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_aslc",0x972,iVar1);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ai_aslc",0x97f);
    return iVar1;
  }
  return 0x101;
}



undefined4 ak_vqe_inner_get_ai_aslc(uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_get_ai_aslc",0x98d);
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_aslc",0x998);
      uVar2 = 0x19000004;
    }
    else {
      uVar2 = FUN_00014e1c(*puVar1,param_2,param_2 + 1,&_SD_Echo_GetNearVolumeParam);
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_aslc",0x9a0);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_get_ai_aslc",0x990);
  return 0x100;
}



int ak_vqe_inner_set_ai_eq(uint param_1,short *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ai_eq",0x9ad);
  iVar1 = FUN_000147f8(param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_eq",0x9b6);
    iVar1 = 0x19000004;
    goto LAB_00018074;
  }
  iVar1 = ak_thread_mutex_lock(puVar2 + 0x23);
  if (iVar1 != 0) {
    ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_eq",0x9bd,iVar1);
    goto LAB_00018074;
  }
  if ((char)param_2[0x3e] == '\0') {
    iVar3 = FUN_00014c6c(*puVar2,&_SD_Echo_GetNearEqParam,&_SD_Echo_SetNearEqParam);
    if (iVar3 != 0) {
      uVar4 = 0x9c7;
      goto LAB_000180d0;
    }
  }
  else {
    iVar3 = FUN_00013bb8(*puVar2,param_2,&_SD_Echo_SetNearEqParam);
    if (iVar3 != 0) {
      uVar4 = 0x9c3;
LAB_000180d0:
      ak_print(0x19,1,"[%s:%d] eq_enable failed\n","ak_vqe_inner_set_ai_eq",uVar4);
    }
  }
  ak_thread_mutex_unlock(puVar2 + 0x23);
  FUN_000154d8(*puVar2);
LAB_00018074:
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ai_eq",0x9d0);
  return iVar1;
}



undefined4 ak_vqe_inner_get_ai_eq(uint param_1,undefined2 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  ak_print(0x19,4,"[%s:%d] entry...\n","ak_vqe_inner_get_ai_eq",0x9dd);
  if (param_2 != (undefined2 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_eq",0x9e8);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00013a7c(*puVar1,param_2,&_SD_Echo_GetNearEqParam);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_eq",0x9f0);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_get_ai_eq",0x9e0);
  return 0x100;
}



int ak_vqe_inner_set_ai_vad(uint param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  if (param_2 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_set_ai_vad",0x9fe);
    return 0x100;
  }
  ak_print(0x19,3,"[%s:%d] ak_vqe_inner_set_ai_nr \n","ak_vqe_inner_set_ai_vad",0xa01);
  iVar1 = FUN_00014fe4(param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_vad",0xa0a);
    iVar1 = 0x19000004;
    goto LAB_00018408;
  }
  iVar1 = ak_thread_mutex_lock(puVar2 + 0x23);
  if (iVar1 != 0) {
    ak_print(6,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_vad",0xa11,iVar1);
    goto LAB_00018408;
  }
  if (param_2[2] == 0) {
    iVar3 = FUN_00015f60(*puVar2);
    if (iVar3 != 0) {
      uVar4 = 0xa1b;
LAB_00018444:
      ak_print(0x19,1,"[%s:%d] _SD_Echo_SetVadParam failed\n ","ak_vqe_inner_set_ai_vad",uVar4);
    }
  }
  else {
    iVar3 = FUN_00016028(*puVar2,param_2);
    if (iVar3 != 0) {
      uVar4 = 0xa17;
      goto LAB_00018444;
    }
  }
  ak_thread_mutex_unlock(puVar2 + 0x23);
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  FUN_00016144(*puVar2,&local_30);
  ak_set_debug_str_info(0x19,1,"\nAI vad---","-------");
  ak_set_debug_num_info(0x19,1,"AI vad thresh",local_30);
  ak_set_debug_num_info(0x19,1,"AI vad level",local_2c);
LAB_00018408:
  ak_thread_rwlock_unlock(DAT_00031624);
  return iVar1;
}



undefined4 ak_vqe_inner_get_ai_vad(uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_vad",0xa39);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00016144(*puVar1,param_2);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_vad",0xa41);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] nr_attr is NULL\n","ak_vqe_inner_get_ai_vad",0xa31);
  return 0x100;
}



undefined4 ak_vqe_inner_get_ai_vad_status(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ai_vad_status",0xa57);
      ak_thread_rwlock_unlock(DAT_00031624);
      uVar2 = 0x19000004;
    }
    else {
      ak_thread_rwlock_unlock(DAT_00031624);
      ak_thread_rwlock_rdlock(iVar1 + 0x40);
      uVar3 = *(undefined4 *)(iVar1 + 0x68);
      uVar4 = *(undefined4 *)(iVar1 + 0x6c);
      uVar2 = *(undefined4 *)(iVar1 + 0x74);
      *param_2 = *(undefined4 *)(iVar1 + 0x60);
      param_2[2] = uVar3;
      param_2[3] = uVar4;
      param_2[4] = uVar2;
      ak_thread_rwlock_unlock(iVar1 + 0x40);
      uVar2 = 0;
    }
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ai_vad_status",0xa65);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] vad_status is NULL\n","ak_vqe_inner_get_ai_vad_status",0xa4f);
  return 0x100;
}



int ak_vqe_inner_set_ao_nr(uint param_1,ushort *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ao_nr",0xa73);
  iVar1 = FUN_00014430((short *)param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ao_nr",0xa7d);
      iVar2 = 0x19000004;
    }
    else {
      iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
      if (iVar2 == 0) {
        if (*(int *)(param_2 + 4) == 0) {
          iVar3 = FUN_00014bb0(*(undefined4 *)(iVar1 + 0xc4),&_SD_Echo_GetFarNrParam,
                               &_SD_Echo_SetFarNrParam);
          if (iVar3 != 0) {
            ak_print(0x19,1,"[%s:%d] ao nr disable failed\n ","ak_vqe_inner_set_ao_nr",0xa8d);
          }
        }
        else {
          iVar3 = FUN_00014b38(*(undefined4 *)(iVar1 + 0xc4),*param_2,&_SD_Echo_SetFarNrParam);
          if (iVar3 != 0) {
            ak_print(0x19,1,"[%s:%d] ao nr enable failed\n ","ak_vqe_inner_set_ao_nr",0xa89);
          }
        }
        ak_thread_mutex_unlock(iVar1 + 0xa4);
        FUN_00015274(*(undefined4 *)(iVar1 + 0xc4));
      }
      else {
        ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ao_nr",0xa84,iVar2);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ao_nr",0xa95);
    return iVar2;
  }
  return 0x101;
}



undefined4 ak_vqe_inner_get_ao_nr(uint param_1,undefined2 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined2 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ao_nr",0xaab);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00014da8(*(undefined4 *)(iVar1 + 0xc4),param_2,(undefined4 *)(param_2 + 4),
                   &_SD_Echo_GetFarNrParam);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_get_ao_nr",0xab3);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_get_ao_nr",0xaa3);
  return 0x100;
}



int ak_vqe_inner_set_ao_eq(uint param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ao_eq",0xac0);
  iVar1 = FUN_000147f8(param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ao_eq",0xaca);
    iVar2 = 0x19000004;
    goto LAB_00018b60;
  }
  iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
  if (iVar2 != 0) {
    ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ao_eq",0xad1,iVar2);
    goto LAB_00018b60;
  }
  if ((char)param_2[0x3e] == '\0') {
    iVar3 = FUN_00014c6c(*(undefined4 *)(iVar1 + 0xc4),&_SD_Echo_GetFarEqParam,
                         &_SD_Echo_SetFarEqParam);
    if (iVar3 != 0) {
      uVar4 = 0xada;
      goto LAB_00018bbc;
    }
  }
  else {
    iVar3 = FUN_00013bb8(*(undefined4 *)(iVar1 + 0xc4),param_2,&_SD_Echo_SetFarEqParam);
    if (iVar3 != 0) {
      uVar4 = 0xad6;
LAB_00018bbc:
      ak_print(0x19,1,"[%s:%d] eq_enable failed\n","ak_vqe_inner_set_ao_eq",uVar4);
    }
  }
  ak_thread_mutex_unlock(iVar1 + 0xa4);
  FUN_00015304(*(undefined4 *)(iVar1 + 0xc4));
LAB_00018b60:
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ao_eq",0xae2);
  return iVar2;
}



undefined4 ak_vqe_inner_get_ao_eq(uint param_1,undefined2 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined2 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ao_eq",0xaf8);
      uVar2 = 0x19000004;
    }
    else {
      FUN_00013a7c(*(undefined4 *)(iVar1 + 0xc4),param_2,&_SD_Echo_GetFarEqParam);
      uVar2 = 0;
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ao_eq",0xb00);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] eq_attr is NULL\n","ak_vqe_inner_get_ao_eq",0xaf0);
  return 0x100;
}



int ak_vqe_inner_set_ao_aslc(uint param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (param_2 == (uint *)0x0) {
    ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_set_ao_aslc",0xb0e);
    return 0x100;
  }
  iVar1 = FUN_00014a64(param_2);
  if (iVar1 != 0) {
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    puVar2 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar2 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ao_aslc",0xb1a);
    iVar1 = 0x19000004;
  }
  else {
    iVar1 = ak_thread_mutex_lock(puVar2 + 0x29);
    if (iVar1 == 0) {
      iVar3 = FUN_00014d38(puVar2[0x31],*param_2,param_2[1],&_SD_Echo_SetFarVolumeParam);
      if (iVar3 != 0) {
        ak_print(0x19,1,"[%s:%d] aslc_enable failed\n","ak_vqe_inner_set_ao_aslc",0xb26);
      }
      ak_thread_mutex_unlock(puVar2 + 0x29);
      FUN_000153b8(puVar2[0x31]);
      if ((puVar2[2] != 0) && (puVar2[1] != 0)) {
        puVar2[0xc] = *param_2;
        iVar3 = FUN_0001634c(puVar2);
        if (iVar3 == 0) {
          FUN_00015c08(*puVar2);
        }
        else {
          ak_print(0x19,1,"[%s:%d] _SD_Echo_SetAecParam failed\n ","ak_vqe_inner_set_ao_aslc",0xb2f)
          ;
          iVar1 = 0x19000007;
        }
      }
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ao_aslc",0xb21,iVar1);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ao_aslc",0xb38);
  return iVar1;
}



undefined4 ak_vqe_inner_get_ao_aslc(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ao_aslc",0xb4e);
      uVar2 = 0x19000004;
    }
    else {
      uVar2 = FUN_00014e1c(*(undefined4 *)(iVar1 + 0xc4),param_2,param_2 + 1,
                           &_SD_Echo_GetFarVolumeParam);
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_ao_aslc",0xb56);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] aslc_attr is NULL\n","ak_vqe_inner_get_ao_aslc",0xb46);
  return 0x100;
}



int ak_vqe_inner_send_adc
              (uint param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
              undefined4 param_6)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_send_adc",0xb67);
  if (param_2 == 0) {
    ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_send_adc",0xb6a);
    return 0x100;
  }
  if (param_3 != 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      puVar1 = (undefined4 *)FUN_00014f9c(param_1);
    }
    if (puVar1 == (undefined4 *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_send_adc",0xb7c);
      iVar2 = 0x19000004;
    }
    else {
      iVar2 = ak_thread_mutex_lock(puVar1 + 0x23);
      if (iVar2 == 0) {
        iVar5 = 1;
        iVar3 = _SD_Echo_FillAdcStream
                          (*puVar1,param_2,param_3,_SD_Echo_FillAdcStream,param_5,param_6,1);
        ak_thread_mutex_unlock(puVar1 + 0x23);
        if (iVar3 != param_3) {
          if (DAT_00031690 < 0x65) {
            iVar5 = DAT_00031690 + 1;
          }
          else {
            uVar4 = _SD_Echo_GetResult(*puVar1,0,0,0,1);
            ak_print(0x19,2,"[%s:%d] _SD_Echo_FillAdcStream has %d %d byte data need to send\n",
                     "ak_vqe_inner_send_adc",0xb93,param_3 - iVar3,iVar3);
            ak_print(0x19,2,"[%s:%d] near jitterBuf remain %d , jitterBuf size %d \n",
                     "ak_vqe_inner_send_adc",0xb94,uVar4,puVar1[0x30]);
          }
          iVar2 = 0x1900000c;
          DAT_00031690 = iVar5;
        }
      }
      else {
        ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_send_adc",0xb83,iVar2);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_send_adc",0xba9);
    return iVar2;
  }
  ak_print(0x19,1,"[%s:%d] data_len is 0\n","ak_vqe_inner_send_adc",0xb6e);
  return 0x101;
}



int ak_vqe_inner_get_adc(uint param_1,int param_2,int param_3,int *param_4,undefined4 param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_get_adc",0xbba);
  if (param_3 != 0 && param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      piVar1 = *(int **)(&DAT_0003161c + param_1 * 4);
    }
    else {
      piVar1 = (int *)FUN_00014f9c(param_1);
    }
    if (piVar1 == (int *)0x0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_adc",0xbcb);
      iVar2 = 0x19000004;
    }
    else {
      iVar2 = ak_thread_mutex_lock(piVar1 + 0x23);
      if (iVar2 == 0) {
        iVar3 = *piVar1;
        if (iVar3 == 0) {
          ak_print(0x19,2,"[%s:%d] user->echo_near_handle is NULL \n","ak_vqe_inner_get_adc",0xbdb);
          iVar3 = *piVar1;
        }
        iVar3 = _SD_Echo_GetResult(iVar3,param_2,param_3,param_5,1);
        if (iVar3 == 0) {
          *param_4 = 0;
          ak_print(0x19,5,"[%s:%d] vqe get no data \n","ak_vqe_inner_get_adc",0xbe2);
          iVar2 = 0;
        }
        else if (iVar3 < 0) {
          *param_4 = 0;
          ak_print(0x19,2,"[%s:%d] vqe get result error \n","ak_vqe_inner_get_adc",0xbe5);
          iVar2 = 0x19000007;
        }
        else {
          *param_4 = iVar3;
        }
        ak_thread_mutex_unlock(piVar1 + 0x23);
      }
      else {
        ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_get_adc",0xbd2,iVar2);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_adc",0xbfc);
    return iVar2;
  }
  ak_print(0x19,1,"[%s:%d] len_out is %p, len_out =%d\n","ak_vqe_inner_get_adc",0xbbd,param_2,
           param_3);
  return 0x100;
}



int ak_vqe_inner_send_far_pcm(uint param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_send_far_pcm",0xc0b);
  if (param_3 == 0 || param_2 == 0) {
    ak_print(0x19,1,"[%s:%d] data_in is %p, len_in =%d\n","ak_vqe_inner_send_far_pcm",0xc0e,param_2,
             param_3);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_send_far_pcm",0xc21);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
    if (iVar2 == 0) {
      iVar3 = _SD_Echo_FillFarStream
                        (*(undefined4 *)(iVar1 + 0xc4),param_2,param_3,_SD_Echo_FillFarStream,0,0,1)
      ;
      *param_4 = iVar3;
      if (param_3 != iVar3) {
        ak_print(0x19,5,"[%s:%d] _SD_Echo_Process has %d byte data need to send\n",
                 "ak_vqe_inner_send_far_pcm",0xc32,param_3 - iVar3);
      }
      ak_thread_mutex_unlock(iVar1 + 0xa4);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_send_far_pcm",0xc28,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_send_far_pcm",0xc45);
  return iVar2;
}



int ak_vqe_inner_get_dac(uint param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_get_dac",0xc55);
  if (param_3 == 0 || param_2 == 0) {
    ak_print(0x19,1,"[%s:%d] data_out is %p, out_buf_len =%d\n","ak_vqe_inner_get_dac",0xc58,param_2
             ,param_3);
    return 0x100;
  }
  if (param_4 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] out_len is NULL\n","ak_vqe_inner_get_dac",0xc5c);
    return 0x100;
  }
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_dac",0xc6a);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
    if (iVar2 == 0) {
      local_30 = 0;
      uStack_2c = 0;
      iVar3 = _SD_Echo_GetDacStream(*(undefined4 *)(iVar1 + 0xc4),param_2,param_3,&local_30,0);
      if (iVar3 == 0) {
        *param_4 = 0;
        ak_print(0x19,5,"[%s:%d] vqe get no data \n","ak_vqe_inner_get_dac",0xc7d);
      }
      else if (iVar3 < 0) {
        *param_4 = 0;
        ak_print(0x19,2,"[%s:%d] vqe get DacStream error \n","ak_vqe_inner_get_dac",0xc80);
        iVar2 = 0x19000007;
      }
      else {
        *param_4 = iVar3;
      }
      ak_thread_mutex_unlock(iVar1 + 0xa4);
      ak_print(0x19,5,"[%s:%d] ******out_len=%d\n","ak_vqe_inner_get_dac",0xc88,*param_4);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_get_dac",0xc70,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_dac",0xc97);
  return iVar2;
}



undefined4 ak_vqe_inner_enable_dump(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  ak_thread_rwlock_wrlock(DAT_00031624);
  ak_print(0x19,3,"[%s:%d] entry...\n","ak_vqe_inner_enable_dump",0xca6);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] user is NULL!\n","ak_vqe_inner_enable_dump",0xcaa);
    uVar2 = 0x19000004;
  }
  else {
    uVar2 = 0;
    if (*(int *)(iVar1 + 0x38) != param_2) {
      DAT_0003167c = *(undefined4 *)(iVar1 + 0x80);
      *(int *)(iVar1 + 0x38) = param_2;
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,3,"[%s:%d] exit...\n","ak_vqe_inner_enable_dump",0xcbe);
  return uVar2;
}



undefined4 ak_vqe_inner_close(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_close",0xccc);
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (param_1 < 2) {
    piVar2 = *(int **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    piVar2 = (int *)FUN_00014f9c(param_1);
  }
  if (piVar2 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_close",0xcd3);
    uVar3 = 0x19000004;
    goto LAB_00019c28;
  }
  if (param_2 == 0 && param_3 == 0) {
LAB_00019bc4:
    uVar3 = 0;
  }
  else {
    if (piVar2[4] != 0) {
      FUN_00015d78(piVar2);
    }
    if (param_2 == 0) goto LAB_00019bc4;
    piVar2[2] = 0;
    uVar3 = FUN_00015ef0(*piVar2);
    *piVar2 = 0;
  }
  if (param_3 != 0) {
    piVar2[3] = 0;
    FUN_00015ef0(piVar2[0x31]);
    piVar2[0x31] = 0;
  }
  if (((piVar2[2] == 0) && (piVar2[3] == 0)) &&
     (iVar1 = param_1 * 4, *(int *)(&DAT_0003161c + iVar1) != 0)) {
    ak_thread_rwlock_destroy(piVar2 + 0x10);
    ak_thread_mutex_destroy(piVar2 + 0x23);
    ak_thread_mutex_destroy(piVar2 + 0x29);
    ak_mem_free(*(undefined4 *)(&DAT_0003161c + iVar1));
    *(undefined4 *)(&DAT_0003161c + iVar1) = 0;
  }
LAB_00019c28:
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_close",0xd01);
  return uVar3;
}



undefined4 ak_vqe_inner_set_lib_print_level(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x10000) != 0) {
    param_2 = param_2 & 0xfffeffff | 0x1c7;
  }
  _SD_Filter_SetDebugZones(param_2);
  return 0;
}



void ak_vqe_inner_get_atc_version(void)

{
  _SD_GetAudioFilterVersionInfo();
  return;
}



int ak_vqe_inner_set_ai_jitterbuf_upperBound(uint param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  
  ak_print(0x19,4,"[%s:%d] osal_vqe_get_dac entry...\n","ak_vqe_inner_set_ai_jitterbuf_upperBound",
           0xd2b);
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (param_1 < 2) {
    puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar1 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ai_jitterbuf_upperBound",0xd30);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(puVar1 + 0x23);
    if (iVar2 == 0) {
      local_3c = iVar2;
      local_38 = iVar2;
      local_34 = iVar2;
      local_30 = iVar2;
      uVar3 = FUN_0001cd70(puVar1[0x20] << 1);
      uVar4 = FUN_0001cd94(param_2);
      uVar3 = FUN_0001ce70((int)uVar3,(uint)(uVar3 >> 0x20),(uint)uVar4,(uint)(uVar4 >> 0x20));
      uVar3 = FUN_0001d0dc((int)uVar3,(uint)(uVar3 >> 0x20),0,0x408f4000);
      local_2c = FUN_0001d33c((uint)uVar3,(uint)(uVar3 >> 0x20));
      _SD_Echo_SetNearJitterBufParam(*puVar1,1,&local_3c,_SD_Echo_SetNearJitterBufParam);
      ak_thread_mutex_unlock(puVar1 + 0x23);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ai_jitterbuf_upperBound",
               0xd36,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_set_ai_jitterbuf_upperBound",0xd40);
  return iVar2;
}



int ak_vqe_inner_clean_ai_buf(uint param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  ak_print(0x19,4,"[%s:%d] osal_vqe_get_dac entry...\n","ak_vqe_inner_clean_ai_buf",0xd4d);
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (param_1 < 2) {
    puVar1 = *(undefined4 **)(&DAT_0003161c + param_1 * 4);
  }
  else {
    puVar1 = (undefined4 *)FUN_00014f9c(param_1);
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_clean_ai_buf",0xd52);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(puVar1 + 0x23);
    if (iVar2 == 0) {
      _SD_Echo_Reset(*puVar1);
      ak_thread_mutex_unlock(puVar1 + 0x23);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_clean_ai_buf",0xd58,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_clean_ai_buf",0xd61);
  return iVar2;
}



int ak_vqe_inner_clean_ao_buf(uint param_1)

{
  int iVar1;
  int iVar2;
  
  ak_print(0x19,4,"[%s:%d] osal_vqe_get_dac entry...\n","ak_vqe_inner_clean_ao_buf",0xd6e);
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_clean_ao_buf",0xd73);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
    if (iVar2 == 0) {
      _SD_Echo_Reset(*(undefined4 *)(iVar1 + 0xc4));
      ak_thread_mutex_unlock(iVar1 + 0xa4);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_clean_ao_buf",0xd79,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_clean_ao_buf",0xd82);
  return iVar2;
}



int ak_vqe_inner_get_buf_status(uint param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_get_buf_status",0xd91);
  ak_thread_rwlock_rdlock(DAT_00031624);
  if (param_1 < 2) {
    iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar1 = FUN_00014f9c(param_1);
  }
  if (iVar1 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_buf_status",0xd96);
    iVar2 = 0x19000004;
  }
  else {
    iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
    if (iVar2 == 0) {
      iVar3 = _SD_Echo_GetDacStream(*(undefined4 *)(iVar1 + 0xc4),0,0,0,0);
      *param_2 = iVar3;
      ak_thread_mutex_unlock(iVar1 + 0xa4);
      if (*param_2 < 0) {
        ak_print(0x19,1,"[%s:%d] get dac buffer remain failed, remain = %d \n",
                 "ak_vqe_inner_get_buf_status",0xda5,*param_2);
      }
      *param_3 = *(undefined4 *)(iVar1 + 0xbc);
    }
    else {
      ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_get_buf_status",0xd9d,iVar2);
    }
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_get_buf_status",0xdab);
  return iVar2;
}



int ak_vqe_inner_set_ao_hs(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  ak_print(0x19,5,"[%s:%d] entry...\n","ak_vqe_inner_set_ao_hs",0xdb8);
  iVar1 = FUN_0001515c(param_2);
  if (iVar1 == 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_ao_hs",0xdc2);
      iVar2 = 0x19000004;
    }
    else {
      iVar2 = ak_thread_mutex_lock(iVar1 + 0xa4);
      if (iVar2 == 0) {
        local_38 = iVar2;
        local_34 = iVar2;
        local_30 = iVar2;
        local_2c = iVar2;
        local_28 = iVar2;
        local_24 = iVar2;
        if (*(int *)(param_2 + 4) == 0) {
          uVar4 = *(undefined4 *)(iVar1 + 0xc4);
          local_3c = iVar2;
          iVar3 = _SD_Echo_GetFarHowlingSuppressParam(uVar4,&local_3c);
          if (iVar3 != 1) {
            ak_print(0x19,5,"[%s:%d] howlingSuppress not open \n ","hs_disable",0x688);
          }
          local_3c = 0;
          iVar3 = _SD_Echo_SetFarHowlingSuppressParam(uVar4,1,&local_3c);
          if (iVar3 != 1) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetFarHowlingSuppressParam failed\n ","hs_disable",
                     0x68d);
            ak_print(0x19,1,"[%s:%d] ao howling suppress failed\n ","ak_vqe_inner_set_ao_hs",0xdd3);
          }
        }
        else {
          local_3c = 1;
          iVar3 = _SD_Echo_SetFarHowlingSuppressParam(*(undefined4 *)(iVar1 + 0xc4),1);
          if (iVar3 != 1) {
            ak_print(0x19,1,"[%s:%d] _SD_Echo_SetFarHowlingSuppressParam failed\n ","hs_enable",
                     0x67e);
            ak_print(0x19,1,"[%s:%d] ao howling suppress enable failed\n ","ak_vqe_inner_set_ao_hs",
                     0xdcf);
          }
        }
        ak_thread_mutex_unlock(iVar1 + 0xa4);
        FUN_00015274(*(undefined4 *)(iVar1 + 0xc4));
      }
      else {
        ak_print(0x19,1,"[%s:%d] lock failed, ret=%d\n","ak_vqe_inner_set_ao_hs",0xdc9,iVar2);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,5,"[%s:%d] exit...\n","ak_vqe_inner_set_ao_hs",0xddb);
    return iVar2;
  }
  return 0x101;
}



undefined4 ak_vqe_inner_get_ao_hs(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_2 != 0) {
    ak_thread_rwlock_rdlock(DAT_00031624);
    if (param_1 < 2) {
      iVar1 = *(int *)(&DAT_0003161c + param_1 * 4);
    }
    else {
      iVar1 = FUN_00014f9c(param_1);
    }
    if (iVar1 == 0) {
      ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_get_ao_hs",0xdf1);
      uVar2 = 0x19000004;
    }
    else {
      uVar2 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      local_28 = 0;
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      iVar1 = _SD_Echo_GetFarHowlingSuppressParam(*(undefined4 *)(iVar1 + 0xc4),&local_34);
      if (iVar1 == 1) {
        *(undefined4 *)(param_2 + 4) = local_34;
      }
      else {
        ak_print(0x19,3,"[%s:%d] howling suppress not open\n ","get_hs_param",0x552);
      }
    }
    ak_thread_rwlock_unlock(DAT_00031624);
    ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_get_ao_hs",0xdf9);
    return uVar2;
  }
  ak_print(0x19,1,"[%s:%d] data is NULL\n","ak_vqe_inner_get_ao_hs",0xde9);
  return 0x100;
}



undefined4 ak_vqe_inner_set_dump_info(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  
  ak_thread_rwlock_wrlock(DAT_00031624);
  if (param_1 < 2) {
    iVar2 = *(int *)(&DAT_0003161c + param_1 * 4);
  }
  else {
    iVar2 = FUN_00014f9c(param_1);
  }
  if (iVar2 == 0) {
    ak_print(0x19,1,"[%s:%d] dev is NULL!\n","ak_vqe_inner_set_dump_info",0xe10);
    uVar5 = 0x19000004;
  }
  else if (param_2 == 0) {
    uVar5 = 0;
  }
  else {
    puVar4 = dump_wav_list;
    do {
      if (*(FILE **)(puVar4 + 8) != (FILE *)0x0) {
        cVar1 = puVar4[0x10];
        DAT_00031680 = (int)cVar1 * *(int *)(puVar4 + 0x14) * 2;
        DAT_0003167a = (short)cVar1;
        DAT_0003167c = *(undefined4 *)(puVar4 + 0x14);
        DAT_00031684 = (undefined2)((int)cVar1 << 1);
        DAT_0003168c = *(undefined4 *)(puVar4 + 0xc);
        DAT_00031668 = *(int *)(puVar4 + 0xc) + 0x24;
        DAT_00031686 = (short)(char)puVar4[0x11];
        fseek(*(FILE **)(puVar4 + 8),0,0);
        fwrite(&DAT_00031664,1,0x2c,*(FILE **)(puVar4 + 8));
        fclose(*(FILE **)(puVar4 + 8));
        puVar4[8] = '\0';
        puVar4[9] = '\0';
        puVar4[10] = '\0';
        puVar4[0xb] = '\0';
        puVar4[0xc] = '\0';
        puVar4[0xd] = '\0';
        puVar4[0xe] = '\0';
        puVar4[0xf] = '\0';
      }
      puVar4 = puVar4 + 0x27c;
    } while (puVar4 != s__tmp__00031418);
    memset(s__tmp__00031418,0,0x200);
    strncpy(s__tmp__00031418,(char *)(param_2 + 4),0x100);
    uVar5 = 0;
    uVar3 = (*(int *)(param_2 + 0x204) * 1000 *
            (*(uint *)(iVar2 + 0x84) >> 3) * *(int *)(iVar2 + 0x80) * *(int *)(iVar2 + 0x88)) / 1000
    ;
    if ((uVar3 & 1) != 0) {
      uVar3 = uVar3 + 1;
    }
    DAT_00031618 = uVar3 >> 10;
  }
  ak_thread_rwlock_unlock(DAT_00031624);
  ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_inner_set_dump_info",0xe1e);
  return uVar5;
}



undefined4 ak_vqe_inner_check_attr_params(undefined4 param_1,uint *param_2)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0:
    uVar1 = FUN_000147f8((short *)param_2);
    return uVar1;
  case 1:
    uVar1 = FUN_00014430((short *)param_2);
    return uVar1;
  case 2:
    uVar1 = FUN_00014514((int *)param_2);
    return uVar1;
  case 3:
    uVar1 = FUN_000146ac(param_2);
    return uVar1;
  case 4:
    uVar1 = FUN_00014a64(param_2);
    return uVar1;
  case 5:
    uVar1 = FUN_00014fe4(param_2);
    return uVar1;
  case 6:
    uVar1 = FUN_0001515c((int)param_2);
    return uVar1;
  default:
    ak_print(0x19,1,"[%s:%d] no support attribute params\n","ak_vqe_inner_check_attr_params",0xe46);
    return 0x101;
  }
}



void ak_vqe_inner_get_filter_info(void)

{
  _SD_GetAudioFilterVersionInfo();
  return;
}



void * FUN_0001aaec(size_t param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  void *__s;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x19,param_1,"filter_alloc",uVar1,param_4);
  if (__s != (void *)0x0) {
    memset(__s,0,param_1);
  }
  return __s;
}



int FUN_0001abc4(int *param_1)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] pcm_attr is NULL\n","check_audio_data_attr",0xff);
    return 0x100;
  }
  if (param_1[1] == 0x10) {
    if (1 < param_1[2] - 1U) {
      ak_print(0x19,1,"[%s:%d] channel_num not support now is %d \n","check_audio_data_attr",0x10b,
               param_1[2]);
      return 0x101;
    }
    iVar1 = *param_1;
    if (iVar1 == 8000 || iVar1 == 12000) {
      iVar1 = 0;
    }
    else if (iVar1 == 0x2b11 || iVar1 == 16000) {
      iVar1 = 0;
    }
    else if (iVar1 == 0x5622 || iVar1 == 24000) {
      iVar1 = 0;
    }
    else if (iVar1 == 32000 || iVar1 == 0xac44) {
      iVar1 = 0;
    }
    else {
      iVar1 = -(uint)(iVar1 != 96000 && iVar1 != 48000);
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] sample bit only suppirt 16bit,now is %d \n","check_audio_data_attr",
             0x104,param_1[1]);
    iVar1 = 0x101;
  }
  return iVar1;
}



undefined4 FUN_0001ad34(void)

{
  ak_print(0x19,1,"[%s:%d] effect_handle_id invalid\n","get_effect_user",0x197);
  return 0;
}



void FUN_0001ad78(int param_1)

{
  if ((&DAT_0003162c)[param_1] != 0) {
    ak_mem_free();
    DAT_00031628 = DAT_00031628 + -1;
    (&DAT_0003162c)[param_1] = 0;
    return;
  }
  ak_print(0x19,1,"[%s:%d] user is NULL\n","del_effect_user",0x1a5);
  return;
}



char * ak_vqe_get_version(void)

{
  return "libplat_vqe V1.4.04";
}



undefined4 ak_vqe_open(uint param_1,int *param_2)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  char acStack_60 [64];
  
  pcVar5 = "libplat_vqe V1.4.04";
  ak_print(0x19,4,"[%s:%d] vqe version: %s\n","ak_vqe_open",0x1bc,"libplat_vqe V1.4.04");
  if (param_2 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] effect_handle_id pointer is NULL\n","ak_vqe_open",0x1bf,pcVar5);
    return 0x100;
  }
  *param_2 = -1;
  if (2 < param_1) {
    ak_print(0x19,1,"[%s:%d] effect_type invalid\n","check_effect_type",0xf2,pcVar5);
    return 0x101;
  }
  piVar3 = &DAT_00031628;
  ak_thread_rwlock_wrlock(DAT_00031644);
  ak_print(0x19,4,"[%s:%d] entry...\n","ak_vqe_open",0x1c9,pcVar5);
  if (DAT_00031628 < 6) {
    uVar1 = ak_get_os_timestamp();
    __s = (void *)ak_mem_alloc_(0x19,0x20,"ak_vqe_open",uVar1);
    if (__s == (void *)0x0) {
      ak_print(0x19,1,"[%s:%d] malloc user error\n","ak_vqe_open",0x1d2);
      uVar1 = 0x102;
    }
    else {
      memset(__s,0,0x20);
      iVar2 = 0;
      *(uint *)((int)__s + 0x10) = param_1;
      do {
        piVar3 = piVar3 + 1;
        if (*piVar3 == 0) {
          iVar4 = iVar2 * 4;
          (&DAT_0003162c)[iVar2] = __s;
          goto LAB_0001aeec;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 != 6);
      iVar4 = 0x18;
LAB_0001aeec:
      DAT_00031628 = DAT_00031628 + 1;
      ak_print(0x19,3,"[%s:%d] effect_ctrl.user_count=%d\n","ak_vqe_open",0x1e4,DAT_00031628);
      uVar1 = *(undefined4 *)((int)&DAT_0003162c + iVar4);
      *param_2 = iVar2;
      ak_print(0x19,3,"[%s:%d] vqe_handle_id=%d--%p\n","ak_vqe_open",0x1e7,iVar2,uVar1);
      memset(acStack_60,0,0x40);
      memset(acStack_60,0,0x40);
      snprintf(acStack_60,0x40,"vqe_version=%s","libplat_vqe V1.4.04");
      ak_debug_info(0x19,1,acStack_60);
      uVar1 = 0;
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] usser too many\n","ak_vqe_open",0x1cc,pcVar5);
    uVar1 = 0x19000003;
  }
  ak_thread_rwlock_unlock(DAT_00031644);
  ak_print(0x19,4,"[%s:%d] ak_vqe_open exit \n","ak_vqe_open",500);
  return uVar1;
}



undefined4 ak_vqe_set_res_attr(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  char *local_e4;
  undefined4 local_e0;
  code *local_dc;
  code *local_d8;
  undefined1 *local_d4;
  undefined4 local_c4;
  int local_c0;
  undefined2 local_bc;
  undefined2 local_ba;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_2c;
  
  if (param_2 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] pcm_attr_in is NULL\n","check_resample_attr_param",0x119);
  }
  else if (param_3 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] pcm_attr_out is NULL\n","check_resample_attr_param",0x11e);
  }
  else {
    iVar1 = FUN_0001abc4(param_2);
    if (iVar1 == 0) {
      iVar1 = FUN_0001abc4(param_3);
      if (iVar1 == 0) {
        ak_thread_rwlock_rdlock(DAT_00031644);
        ak_print(0x19,4,"[%s:%d] entry...\n","ak_vqe_set_res_attr",0x209);
        if (param_1 < 6) {
          piVar3 = (int *)(&DAT_0003162c)[param_1];
        }
        else {
          piVar3 = (int *)FUN_0001ad34();
        }
        if (piVar3 == (int *)0x0) {
          ak_print(0x19,1,"[%s:%d] user is NULL\n","ak_vqe_set_res_attr",0x20d);
          uVar2 = 0x19000004;
        }
        else if (piVar3[4] == 0) {
          if (*piVar3 != 0) {
            iVar1 = _SD_Filter_Close();
            if (iVar1 != 1) {
              ak_print(0x19,1,"[%s:%d] vqe close error\n","ak_vqe_set_res_attr",0x21a);
              uVar2 = 0x19000002;
              goto LAB_0001b1dc;
            }
            *piVar3 = 0;
          }
          memset(&local_e4,0,0xbc);
          local_c0 = *param_2;
          local_a8 = *param_3;
          local_d8 = ak_mem_free;
          uVar2 = 0;
          local_dc = FUN_0001aaec;
          local_d4 = &LAB_0001ab44;
          local_ba = (undefined2)param_2[1];
          local_bc = (undefined2)param_2[2];
          local_e4 = "AudioFilter Version V1.15.16";
          local_c4 = 3;
          local_e0 = 0;
          local_ac = 0;
          local_b0 = 0;
          local_a4 = 1;
          local_2c = _SD_Resample_login(0);
          local_b4 = 0x14;
          iVar1 = _SD_Filter_Open(&local_e4);
          *piVar3 = iVar1;
          if (iVar1 == 0) {
            ak_print(0x19,1,"[%s:%d] filter lib error\n","ak_vqe_set_res_attr",0x239);
            FUN_0001ad78(param_1);
            uVar2 = 0x19000000;
          }
          else {
            piVar3[7] = *param_3;
            memcpy(piVar3 + 1,param_2,0xc);
          }
        }
        else {
          ak_print(0x19,1,"[%s:%d] vqe open type not same\n","ak_vqe_set_res_attr",0x213);
          uVar2 = 0x101;
        }
LAB_0001b1dc:
        ak_thread_rwlock_unlock(DAT_00031644);
        ak_print(0x19,4,"[%s:%d] exit...\n","ak_vqe_set_res_attr",0x247);
        return uVar2;
      }
      ak_print(0x19,1,"[%s:%d] pcm_attr_out param invalid\n","check_resample_attr_param",0x128);
    }
    else {
      ak_print(0x19,1,"[%s:%d] pcm_attr_in param invalid\n","check_resample_attr_param",0x123);
    }
  }
  return 0x101;
}



int ak_vqe_set_aslc_attr(uint param_1,int *param_2,int param_3)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int extraout_r0;
  uint extraout_r0_00;
  int extraout_r0_01;
  uint extraout_r0_02;
  uint extraout_r0_03;
  uint extraout_r0_04;
  undefined4 extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  undefined4 extraout_r1_02;
  uint extraout_r1_03;
  uint extraout_r1_04;
  undefined4 extraout_r1_05;
  uint extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  uint extraout_r1_10;
  undefined4 extraout_r1_11;
  undefined4 extraout_r1_12;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  undefined4 extraout_r2_05;
  undefined4 extraout_r2_06;
  undefined4 extraout_r2_07;
  undefined4 extraout_r2_08;
  undefined4 extraout_r2_09;
  undefined4 extraout_r2_10;
  undefined4 extraout_r2_11;
  undefined4 extraout_r2_12;
  undefined4 extraout_r2_13;
  undefined4 extraout_r2_14;
  undefined4 extraout_r2_15;
  undefined4 extraout_r2_16;
  uint extraout_r3;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint extraout_r3_02;
  int *piVar5;
  undefined4 uVar6;
  double __x;
  double extraout_d0;
  double __x_00;
  double extraout_d0_00;
  double dVar7;
  undefined4 extraout_s1;
  double extraout_d0_01;
  undefined4 extraout_s1_00;
  double extraout_d0_02;
  undefined4 extraout_s2;
  undefined4 extraout_s2_00;
  double __y;
  double __y_00;
  undefined4 extraout_s3;
  undefined4 extraout_s3_00;
  undefined8 uVar8;
  ulonglong uVar9;
  char **local_114;
  char *local_e4;
  undefined4 local_e0;
  code *local_dc;
  code *local_d8;
  undefined1 *local_d4;
  undefined4 local_d0;
  uint local_cc;
  uint local_c8;
  undefined4 local_c4;
  int local_c0;
  undefined4 local_bc;
  undefined4 local_b4;
  undefined1 local_b0;
  undefined2 local_ae;
  undefined2 local_ac;
  undefined2 local_aa;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_2c;
  
  iVar3 = FUN_0001abc4(param_2);
  if (iVar3 != 0) {
    ak_print(0x19,1,"[%s:%d] check_audio_data_attr error\n","ak_vqe_set_aslc_attr",0x259);
    return iVar3;
  }
  if (0x6e < param_3 + 0x5aU) {
    ak_print(0x19,1,"[%s:%d] check db error\n","ak_vqe_set_aslc_attr",0x25d);
    return 0x101;
  }
  ak_thread_rwlock_rdlock(DAT_00031644);
  if (param_1 < 6) {
    piVar5 = (int *)(&DAT_0003162c)[param_1];
  }
  else {
    piVar5 = (int *)FUN_0001ad34();
  }
  if (piVar5 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] user is NULL\n","ak_vqe_set_aslc_attr",0x264);
    iVar3 = 0x19000004;
    goto LAB_0001b508;
  }
  if (piVar5[4] != 1) {
    ak_print(0x19,1,"[%s:%d] vqe open type not same\n","ak_vqe_set_aslc_attr",0x26a);
    iVar3 = 0x101;
    goto LAB_0001b508;
  }
  iVar3 = *piVar5;
  if (iVar3 == 0) {
LAB_0001b5b8:
    memset(&local_e4,0,0xbc);
    local_c0 = *param_2;
    local_dc = FUN_0001aaec;
    local_d8 = ak_mem_free;
    local_d4 = &LAB_0001ab44;
    local_bc = CONCAT22((short)param_2[1],(short)param_2[2]);
    local_ae = 0x7fbc;
    local_ac = 20000;
    local_e4 = "AudioFilter Version V1.15.16";
    local_d0 = 0;
    local_e0 = 0;
    local_c4 = 0xb;
    local_aa = 2;
    local_b0 = 1;
    uVar8 = _SD_ASLC_login(0,2,_SD_ASLC_login);
    local_2c = (undefined4)uVar8;
    local_b4 = 0x18;
    iVar3 = _SD_Filter_Open(&local_e4,(int)((ulonglong)uVar8 >> 0x20),0x18,_SD_Filter_Open);
    *piVar5 = iVar3;
    if (iVar3 == 0) {
      ak_print(0x19,1,"[%s:%d] filter lib error\n","ak_vqe_set_aslc_attr",0x293);
      FUN_0001ad78(param_1);
      iVar3 = 0x19000000;
      goto LAB_0001b508;
    }
    memcpy(piVar5 + 1,param_2,0xc);
    iVar3 = *piVar5;
    if (iVar3 != 0) goto LAB_0001b69c;
    iVar3 = 0;
  }
  else {
    if ((piVar5[1] != *param_2) || (piVar5[3] != param_2[2])) {
      iVar3 = _SD_Filter_Close(iVar3);
      if (iVar3 != 1) {
        ak_print(0x19,1,"[%s:%d] vqe close error\n","ak_vqe_set_aslc_attr",0x272);
        iVar3 = 0x19000002;
        goto LAB_0001b508;
      }
      *piVar5 = 0;
      goto LAB_0001b5b8;
    }
LAB_0001b69c:
    local_114 = &local_e4;
    uVar4 = FUN_0001d5d4(param_3 - 0x28);
    uVar4 = FUN_0001d818(uVar4,0x41a00000,extraout_r2,extraout_r3);
    uVar9 = FUN_0001cdbc(uVar4,extraout_r1,extraout_r2_00,0x1cdbc);
    ak_print(0x19,5,"[%s:%d] first exponential[%d] = %f\n","da_get_stone2_y",0x73,param_3,uVar9);
    bVar1 = FUN_0001da24(uVar4,0);
    if (bVar1) {
      uVar4 = FUN_0001d680(uVar4,0x447a0000,extraout_r2_01,0x1d680);
      uVar4 = FUN_0001da74(uVar4);
      uVar4 = abs(uVar4);
      uVar4 = FUN_0001d5d4(uVar4);
      uVar4 = FUN_0001d818(uVar4,0x447a0000,extraout_r2_05,extraout_r3_01);
      uVar9 = FUN_0001cdbc(uVar4,extraout_r1_05,extraout_r2_06,0x1cdbc);
      uVar6 = ak_print(0x19,5,"[%s:%d] second exponential[%d] = %f\n","da_get_stone2_y",0x76,param_3
                       ,uVar9,uVar9);
      pow((double)CONCAT44(extraout_s1,uVar6),(double)CONCAT44(extraout_s3,extraout_s2));
      uVar4 = FUN_0001d390(extraout_r0_03,extraout_r1_06);
      cVar2 = FUN_0001da10(uVar4,0);
      if (cVar2 == '\0') {
        uVar4 = FUN_0001d818(0x3f800000,uVar4,extraout_r2_07,extraout_r3_02);
        uVar9 = FUN_0001cdbc(uVar4,extraout_r1_07,extraout_r2_08,0x1cdbc);
      }
      else {
        uVar4 = 0x3f800000;
        uVar9 = 0x3ff0000000000000;
      }
      ak_print(0x19,5,"[%s:%d] exponential_float[%d] = %f\n","da_get_stone2_y",0x7a,param_3,uVar9);
      uVar4 = FUN_0001d680(uVar4,0x47000000,extraout_r2_09,0x1d680);
      FUN_0001cdbc(uVar4,extraout_r1_08,extraout_r2_10,0x1cdbc);
      dVar7 = extraout_d0_01;
    }
    else {
      pow(__x,__y);
      FUN_0001ce70(extraout_r0,extraout_r1_00,0,0x40e00000);
      dVar7 = extraout_d0;
    }
    round(dVar7);
    local_cc = FUN_0001d2e0(extraout_r0_00,extraout_r1_01);
    ak_print(0x19,5,"[%s:%d] result2[%d] = %d\n","da_get_stone2_y",0x80,param_3,local_cc);
    uVar4 = FUN_0001d5d4(-param_3);
    uVar4 = FUN_0001d818(uVar4,0x41a00000,extraout_r2_02,extraout_r3_00);
    uVar9 = FUN_0001cdbc(uVar4,extraout_r1_02,extraout_r2_03,0x1cdbc);
    ak_print(0x19,5,"[%s:%d] first exponential[%d] = %f\n","da_get_stone3_x",0x92,param_3,uVar9);
    uVar6 = (undefined4)(uVar9 >> 0x20);
    bVar1 = FUN_0001da24(uVar4,0);
    if (bVar1) {
      uVar4 = FUN_0001d680(uVar4,0x447a0000,extraout_r2_04,0x1d680);
      uVar4 = FUN_0001da74(uVar4);
      uVar4 = abs(uVar4);
      uVar4 = FUN_0001d5d4(uVar4);
      uVar4 = FUN_0001d818(uVar4,0x447a0000,extraout_r2_11,0x1d818);
      uVar9 = FUN_0001cdbc(uVar4,extraout_r1_09,extraout_r2_12,0x1cdbc);
      uVar6 = ak_print(0x19,5,"[%s:%d] second exponential[%d] = %f\n","da_get_stone3_x",0x95,param_3
                       ,uVar9);
      pow((double)CONCAT44(extraout_s1_00,uVar6),(double)CONCAT44(extraout_s3_00,extraout_s2_00));
      uVar4 = FUN_0001d390(extraout_r0_04,extraout_r1_10);
      cVar2 = FUN_0001da10(uVar4,0);
      if (cVar2 == '\0') {
        uVar4 = FUN_0001d818(0x3f800000,uVar4,extraout_r2_13,0x1d818);
        uVar9 = FUN_0001cdbc(uVar4,extraout_r1_11,extraout_r2_14,0x1cdbc);
      }
      else {
        uVar4 = 0x3f800000;
        uVar9 = 0x3ff0000000000000;
      }
      ak_print(0x19,5,"[%s:%d] exponential_float[%d] = %f\n","da_get_stone3_x",0x99,param_3,uVar9);
      uVar6 = (undefined4)(uVar9 >> 0x20);
      uVar4 = FUN_0001d680(uVar4,0x47000000,extraout_r2_15,0x1d680);
      FUN_0001cdbc(uVar4,extraout_r1_12,extraout_r2_16,0x1cdbc);
      dVar7 = extraout_d0_02;
    }
    else {
      pow(__x_00,__y_00);
      FUN_0001ce70(extraout_r0_01,extraout_r1_03,0,0x40e00000);
      dVar7 = extraout_d0_00;
    }
    round(dVar7);
    uVar4 = FUN_0001d2e0(extraout_r0_02,extraout_r1_04);
    ak_print(0x19,5,"[%s:%d] result3[%d] = %d\n","da_get_stone3_x",0x9f,param_3,uVar4);
    uVar8 = CONCAT44(uVar6,uVar4);
    ak_print(0x19,5,"[%s:%d] stone2_y=%d, stone3_x=%d\n","set_da_aslc_param",0xb1,local_cc,uVar4);
    memset(local_114,0,0x60);
    local_e4 = (char *)0x5;
    local_90 = 6;
    local_d0 = 0x148;
    local_d8 = (code *)0x68;
    local_d4 = (undefined1 *)0x21;
    local_c4 = 0x8000;
    local_c0 = 0x8000;
    local_bc = 0x8000;
    local_8c = 3;
    local_88 = 300;
    local_c8 = uVar4;
    iVar3 = _SD_Filter_SetAslcMileStones(iVar3,local_114,_SD_Filter_SetAslcMileStones);
    if (iVar3 == 1) {
      ak_print(0x19,5,"[%s:%d] user->lib_handle=%p\n","ak_vqe_set_aslc_attr",0x2a4,*piVar5,uVar8);
      iVar3 = 0;
      goto LAB_0001b508;
    }
    iVar3 = *piVar5;
  }
  ak_print(0x19,1,"[%s:%d] aslc_set_param error, handle=%p\n","ak_vqe_set_aslc_attr",0x29d,iVar3);
  _SD_Filter_Close(*piVar5);
  FUN_0001ad78(param_1);
  iVar3 = 0x19000001;
LAB_0001b508:
  ak_thread_rwlock_unlock(DAT_00031644);
  return iVar3;
}



undefined4 ak_vqe_set_eq_attr(uint param_1,int *param_2,short *param_3)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short *psVar4;
  int *piVar5;
  char **ppcVar6;
  int iVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  int *piVar10;
  byte *pbVar11;
  short *psVar12;
  byte *pbVar13;
  undefined1 *puVar14;
  short *local_f8;
  int *local_f4;
  char *local_e4;
  undefined4 local_e0;
  code *local_dc;
  code *local_d8;
  undefined1 *local_d4;
  undefined4 local_d0;
  undefined4 local_c4;
  int local_c0;
  undefined2 local_bc;
  undefined2 local_ba;
  undefined4 local_b4;
  undefined4 local_b0;
  short local_ac;
  int local_a8;
  int local_a4 [10];
  undefined2 local_7c [10];
  undefined2 local_68 [9];
  undefined1 uStack_55;
  undefined1 local_54 [9];
  undefined1 uStack_4b;
  undefined1 local_4a [22];
  undefined1 local_34;
  short local_32;
  undefined4 local_2c;
  
  if (param_2 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] pcm_attr_in is NULL\n","check_eq_attr_param",0x136);
    return 0x100;
  }
  if (param_3 == (short *)0x0) {
    ak_print(0x19,1,"[%s:%d] eq_attr is NULL\n","check_eq_attr_param",0x13a);
    return 0x100;
  }
  iVar7 = *param_2;
  if ((((iVar7 == 8000 || iVar7 == 12000) || (iVar7 == 0x2b11 || iVar7 == 16000)) ||
      (iVar7 == 0x5622 || iVar7 == 24000)) ||
     ((iVar7 == 32000 || iVar7 == 0xac44 || (iVar7 == 48000 || iVar7 == 96000)))) {
    if (param_2[1] == 0x10) {
      if (1 < param_2[2] - 1U) {
        ak_print(0x19,1,"[%s:%d] channel number invalid \n","check_eq_attr_param",0x147);
        return 0x101;
      }
      if (*(byte *)(param_3 + 0x3e) < 2) {
        if (*(uint *)(param_3 + 2) < 0xb) {
          if ((ushort)(*param_3 + 0x3000U) < 0x6001) {
            pbVar11 = (byte *)(param_3 + 0x3e);
            psVar4 = param_3 + 0x2c;
            piVar5 = (int *)(param_3 + 4);
            iVar7 = 0;
            pbVar13 = pbVar11;
            do {
              pbVar13 = pbVar13 + 1;
              bVar1 = *pbVar13;
              if (1 < bVar1) {
                ak_print(0x19,1,"[%s:%d] band_enable must be 0 or 1, now band_enable[%d]=%d\n",
                         "check_eq_attr_param",0x162,iVar7,bVar1);
                return 0x101;
              }
              iVar7 = iVar7 + 1;
              if (bVar1 != 0) {
                if (0x6816 < *piVar5 - 0x14U) {
                  ak_print(0x19,1,"[%s:%d] bandfreqs must in 20~26666\n","check_eq_attr_param",0x169
                          );
                  return 0x101;
                }
                if (4 < (ushort)(*psVar4 - 1U)) {
                  ak_print(0x19,1,"[%s:%d] band_types must in 1~5\n","check_eq_attr_param",0x175);
                  return 0x101;
                }
              }
              psVar4 = psVar4 + 1;
              piVar5 = piVar5 + 1;
            } while (iVar7 != 10);
            ak_thread_rwlock_rdlock(DAT_00031644);
            if (param_1 < 6) {
              local_f4 = (int *)(&DAT_0003162c)[param_1];
            }
            else {
              local_f4 = (int *)FUN_0001ad34();
            }
            if (local_f4 == (int *)0x0) {
              ak_print(0x19,1,"[%s:%d] user is NULL\n","ak_vqe_set_eq_attr",0x2c0);
              uVar8 = 0x19000004;
            }
            else if (local_f4[4] == 2) {
              if (*local_f4 != 0) {
                iVar7 = _SD_Filter_Close();
                if (iVar7 != 1) {
                  ak_print(0x19,1,"[%s:%d] vqe close error\n","ak_vqe_set_eq_attr",0x2cd);
                  uVar8 = 0x19000002;
                  goto LAB_0001bf60;
                }
                *local_f4 = 0;
              }
              memset(&local_e4,0,0xbc);
              local_a8 = *(int *)(param_3 + 2);
              local_c0 = *param_2;
              local_ac = *param_3;
              local_dc = FUN_0001aaec;
              local_d8 = free;
              local_34 = (undefined1)param_3[0x3c];
              local_32 = param_3[0x3d];
              local_d4 = &LAB_0001ab44;
              local_ba = (undefined2)param_2[1];
              iVar7 = 0;
              local_bc = (undefined2)param_2[2];
              local_e4 = "AudioFilter Version V1.15.16";
              local_d0 = 0;
              local_e0 = 0;
              local_c4 = 1;
              local_b0 = 7;
              if (local_a8 != 0) {
                local_f8 = param_3 + 0x2b;
                piVar5 = (int *)(param_3 + 2);
                psVar12 = param_3 + 0x17;
                psVar4 = param_3 + 0x21;
                piVar10 = &local_a8;
                ppcVar6 = &local_e4;
                puVar9 = &uStack_55;
                puVar14 = &uStack_4b;
                do {
                  iVar7 = iVar7 + 1;
                  piVar5 = piVar5 + 1;
                  pbVar11 = pbVar11 + 1;
                  bVar1 = *pbVar11;
                  piVar10 = piVar10 + 1;
                  *piVar10 = *piVar5;
                  psVar12 = psVar12 + 1;
                  local_f8 = local_f8 + 1;
                  sVar2 = *local_f8;
                  psVar4 = psVar4 + 1;
                  sVar3 = *psVar4;
                  *(short *)(ppcVar6 + 0x1a) = *psVar12;
                  *(short *)(ppcVar6 + 0x1f) = sVar3;
                  puVar9 = puVar9 + 1;
                  *puVar9 = (char)sVar2;
                  ppcVar6 = (char **)((int)ppcVar6 + 2);
                  puVar14 = puVar14 + 1;
                  *puVar14 = bVar1 == 0;
                } while (iVar7 != local_a8);
              }
              local_2c = _SD_EQ_login(0);
              local_b4 = 0x84;
              iVar7 = _SD_Filter_Open(&local_e4);
              *local_f4 = iVar7;
              if (iVar7 == 0) {
                ak_print(0x19,1,"[%s:%d] filter lib error\n","ak_vqe_set_eq_attr",0x2f9);
                FUN_0001ad78(param_1);
                uVar8 = 0x19000000;
              }
              else {
                ak_print(0x19,5,"[%s:%d] user->lib_handle=%p\n","ak_vqe_set_eq_attr",0x2ff,iVar7);
                uVar8 = 0;
              }
            }
            else {
              ak_print(0x19,1,"[%s:%d] vqe open type not same\n","ak_vqe_set_eq_attr",0x2c6);
              uVar8 = 0x101;
            }
LAB_0001bf60:
            ak_thread_rwlock_unlock(DAT_00031644);
            return uVar8;
          }
          ak_print(0x19,1,"[%s:%d] pre_gain must in -12288~12288, pre_gain =%d, error\n",
                   "check_eq_attr_param",0x15b,(int)*param_3);
        }
        else {
          ak_print(0x19,1,"[%s:%d] bands must in 0~10, bands =%d, error\n","check_eq_attr_param",
                   0x151,*(uint *)(param_3 + 2));
        }
      }
      else {
        ak_print(0x19,1,"[%s:%d] eq_enable must be 0 or 1\n","check_eq_attr_param",0x14c);
      }
    }
    else {
      ak_print(0x19,1,"[%s:%d] sample bit invalid \n","check_eq_attr_param",0x143);
    }
  }
  else {
    ak_print(0x19,1,"[%s:%d] sample rate invalid \n","check_eq_attr_param",0x13f);
  }
  return 0x101;
}



undefined4 ak_vqe_process(uint param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  uint extraout_r0;
  int extraout_r1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  uint uVar6;
  int local_48;
  int local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar5 = DAT_00031644;
  if (param_2 == 0) {
    ak_print(0x19,1,"[%s:%d] inbuf is NULL\n","check_effect_control_param",0x180);
    return 0x101;
  }
  if (param_3 == 0) {
    ak_print(0x19,1,"[%s:%d] inlen is <= 0\n","check_effect_control_param",0x185);
    return 0x101;
  }
  if (param_5 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] ret_data_len is NULL\n","check_effect_control_param",0x18a);
    return 0x100;
  }
  *param_5 = 0;
  ak_thread_rwlock_wrlock(uVar5);
  if (param_1 < 6) {
    piVar4 = (int *)(&DAT_0003162c)[param_1];
  }
  else {
    piVar4 = (int *)FUN_0001ad34();
  }
  if (piVar4 == (int *)0x0) {
    ak_print(0x19,1,"[%s:%d] user is NULL\n","ak_vqe_process",0x322);
    uVar5 = 0x19000004;
    goto LAB_0001c400;
  }
  iVar1 = *piVar4;
  if (iVar1 == 0) {
    ak_print(0x19,1,
             "[%s:%d] please set ak_vqe_set_res_attr or ak_vqe_set_aslc_attr or ak_vqe_set_eq_attr first!\n"
             ,"ak_vqe_process",0x328);
    uVar5 = 0x19000001;
    goto LAB_0001c400;
  }
  iVar3 = *param_4;
  iVar2 = piVar4[5];
  if (iVar3 == 0) {
    if (iVar2 == 0) {
      iVar1 = param_3;
      if (piVar4[4] == 0) {
        uVar6 = piVar4[7];
        if (uVar6 != 0) {
          FUN_0001c8f4(uVar6 * param_3,piVar4[1]);
          FUN_0001ca98(uVar6 * param_3,uVar6);
          uVar6 = extraout_r0;
          if (extraout_r1 != 0) {
            uVar6 = extraout_r0 + 4;
          }
          if ((uVar6 & 1) != 0) {
            uVar6 = uVar6 + 1;
          }
          if ((uVar6 & 3) != 0) {
            uVar6 = uVar6 + 2;
          }
          iVar1 = uVar6 + 0x10;
          goto LAB_0001c560;
        }
        ak_print(0x19,1,"[%s:%d] out_sample_rate = 0\n","get_outbuf_size",0xd5);
        piVar4[6] = 0;
      }
      else {
LAB_0001c560:
        piVar4[6] = iVar1;
        if (iVar1 != 0) {
          uVar5 = ak_get_os_timestamp();
          iVar2 = ak_mem_alloc_(0x19,iVar1,"ak_vqe_process",uVar5);
          piVar4[5] = iVar2;
          if (iVar2 == 0) {
            ak_print(0x19,1,"[%s:%d] malloc user->outbuf failed\n","ak_vqe_process",0x33d);
            uVar5 = 0x100;
            goto LAB_0001c400;
          }
          iVar1 = *piVar4;
          goto LAB_0001c478;
        }
      }
      ak_print(0x19,1,"[%s:%d] outbuf_len = 0\n","ak_vqe_process",0x337);
      uVar5 = 0x19000006;
      goto LAB_0001c400;
    }
  }
  else if (iVar3 != iVar2) {
    ak_print(0x19,1,"[%s:%d] outbuf addr wrong, *outbuf=%p, user->outbuf=%p\n","ak_vqe_process",
             0x32f,iVar3,iVar2);
    uVar5 = 0x100;
    goto LAB_0001c400;
  }
LAB_0001c478:
  local_38 = piVar4[6];
  local_40 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_48 = param_2;
  local_44 = param_3;
  local_3c = iVar2;
  iVar1 = _SD_Filter_Control(iVar1,&local_48);
  if (iVar1 < 0) {
    ak_print(0x19,1,"[%s:%d] _SD_Filter_Control\n","ak_vqe_process",0x34c);
    uVar5 = 0x19000001;
  }
  else {
    if (iVar1 == 0) {
      ak_print(0x19,5,"_SD_Filter_Control output 0.\n");
    }
    else {
      *param_5 = iVar1;
    }
    uVar5 = 0;
    *param_4 = piVar4[5];
  }
LAB_0001c400:
  ak_thread_rwlock_unlock(DAT_00031644);
  return uVar5;
}



undefined4 ak_vqe_close(uint param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  if (param_1 < 6) {
    piVar2 = (int *)(&DAT_0003162c)[param_1];
  }
  else {
    piVar2 = (int *)FUN_0001ad34();
  }
  if (piVar2 != (int *)0x0) {
    ak_thread_rwlock_wrlock(DAT_00031644);
    if (DAT_00031628 < 1) {
      ak_print(0x19,1,"[%s:%d] no user\n","ak_vqe_close",0x36f);
      uVar3 = 0x19000005;
    }
    else {
      if ((*piVar2 == 0) || (iVar1 = _SD_Filter_Close(), iVar1 == 1)) {
        uVar3 = 0;
      }
      else {
        ak_print(0x19,1,"[%s:%d] _SD_Filter_Close failed\n","ak_vqe_close",0x375);
        uVar3 = 0x19000001;
      }
      if (piVar2[5] != 0) {
        ak_mem_free();
        piVar2[6] = 0;
      }
      FUN_0001ad78(param_1);
    }
    ak_thread_rwlock_unlock(DAT_00031644);
    ak_print(0x19,3,"[%s:%d] ak_vqe_close, now count =%d--%p\n","ak_vqe_close",899,DAT_00031628,
             (&DAT_0003162c)[param_1]);
    return uVar3;
  }
  ak_print(0x19,1,"[%s:%d] user is NULL\n","ak_vqe_close",0x367);
  return 0x19000004;
}



void ak_vqe_get_filter_info(void)

{
  _SD_GetAudioFilterVersionInfo();
  return;
}



ulonglong FUN_0001c8f4(uint param_1,uint param_2)

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



uint FUN_0001c9c4(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool in_NG;
  bool bVar6;
  
  uVar5 = param_1 ^ param_2;
  uVar2 = param_2;
  if (in_NG) {
    uVar2 = -param_2;
  }
  if (uVar2 - 1 == 0) {
    if ((int)param_2 < 0) {
      param_1 = -param_1;
    }
    return param_1;
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
    return param_1;
  }
  if ((uVar2 & uVar2 - 1) == 0) {
    uVar4 = uVar4 >> (0x1fU - LZCOUNT(uVar2) & 0xff);
    if ((int)uVar5 < 0) {
      uVar4 = -uVar4;
    }
    return uVar4;
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
  return uVar1;
}



void FUN_0001ca98(uint param_1,uint param_2)

{
  if (param_2 != 0) {
    FUN_0001c9c4(param_1,param_2);
    return;
  }
  raise(8);
  return;
}



ulonglong FUN_0001cd70(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint in_r12;
  bool bVar7;
  bool bVar8;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  iVar4 = LZCOUNT(param_1);
  uVar5 = iVar4 + 0x15;
  bVar8 = SBORROW4(uVar5,0x20);
  uVar2 = iVar4 - 0xb;
  bVar7 = uVar2 == 0;
  uVar6 = uVar2;
  uVar3 = uVar2;
  if (uVar5 < 0x20) {
    bVar8 = SCARRY4(uVar2,0xc);
    uVar3 = iVar4 + 1;
    bVar7 = uVar3 == 0;
    uVar6 = uVar5;
    if (!bVar7 && -0xd < (int)uVar2) {
      uVar1 = param_1 << uVar5;
      uVar2 = param_1 >> (0xc - uVar3 & 0xff);
      goto LAB_0001cc5c;
    }
  }
  if (bVar7 || (int)uVar3 < 0 != bVar8) {
    in_r12 = 0x20 - uVar6;
  }
  uVar2 = param_1 << (uVar6 & 0xff);
  if (bVar7 || (int)uVar3 < 0 != bVar8) {
    uVar2 = uVar2 | 0U >> (in_r12 & 0xff);
    uVar1 = 0 << (uVar6 & 0xff);
  }
LAB_0001cc5c:
  if (uVar5 < 0x433) {
    return CONCAT44(uVar2 + (0x432 - uVar5) * 0x100000,uVar1);
  }
  uVar6 = ~(0x432 - uVar5);
  if (0x1e < (int)uVar6) {
    return (ulonglong)(uVar2 >> (uVar6 - 0x1f & 0xff));
  }
  if (uVar6 - 0x13 == 0 || (int)(uVar6 - 0x1f) < -0xc) {
    uVar6 = uVar6 + 1;
    return CONCAT44(uVar2 >> (uVar6 & 0xff),uVar1 >> (uVar6 & 0xff) | uVar2 << (0x20 - uVar6 & 0xff)
                   );
  }
  uVar6 = 0xc - (uVar6 - 0x13);
  return (ulonglong)(uVar1 >> (0x20 - uVar6 & 0xff) | uVar2 << (uVar6 & 0xff));
}



ulonglong FUN_0001cd94(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint in_r12;
  bool bVar9;
  bool bVar10;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar8 = param_1 & 0x80000000;
  uVar2 = param_1;
  if ((int)uVar8 < 0) {
    uVar2 = -param_1;
  }
  uVar1 = 0;
  iVar5 = LZCOUNT(uVar2);
  uVar6 = iVar5 + 0x15;
  bVar10 = SBORROW4(uVar6,0x20);
  uVar3 = iVar5 - 0xb;
  bVar9 = uVar3 == 0;
  uVar7 = uVar3;
  uVar4 = uVar3;
  if (uVar6 < 0x20) {
    bVar10 = SCARRY4(uVar3,0xc);
    uVar4 = iVar5 + 1;
    bVar9 = uVar4 == 0;
    uVar7 = uVar6;
    if (!bVar9 && -0xd < (int)uVar3) {
      uVar1 = uVar2 << uVar6;
      uVar2 = uVar2 >> (0xc - uVar4 & 0xff);
      goto LAB_0001cc5c;
    }
  }
  if (bVar9 || (int)uVar4 < 0 != bVar10) {
    in_r12 = 0x20 - uVar7;
  }
  uVar2 = uVar2 << (uVar7 & 0xff);
  if (bVar9 || (int)uVar4 < 0 != bVar10) {
    uVar2 = uVar2 | 0U >> (in_r12 & 0xff);
    uVar1 = 0 << (uVar7 & 0xff);
  }
LAB_0001cc5c:
  if (uVar6 < 0x433) {
    return CONCAT44(uVar2 + (0x432 - uVar6) * 0x100000 | uVar8,uVar1);
  }
  uVar7 = ~(0x432 - uVar6);
  if (0x1e < (int)uVar7) {
    return CONCAT44(param_1,uVar2 >> (uVar7 - 0x1f & 0xff)) & 0x80000000ffffffff;
  }
  if (uVar7 - 0x13 == 0 || (int)(uVar7 - 0x1f) < -0xc) {
    uVar7 = uVar7 + 1;
    return CONCAT44(uVar8 | uVar2 >> (uVar7 & 0xff),
                    uVar1 >> (uVar7 & 0xff) | uVar2 << (0x20 - uVar7 & 0xff));
  }
  uVar8 = 0xc - (uVar7 - 0x13);
  return CONCAT44(param_1,uVar1 >> (0x20 - uVar8 & 0xff) | uVar2 << (uVar8 & 0xff)) &
         0x80000000ffffffff;
}



ulonglong FUN_0001cdbc(uint param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint in_r12;
  bool bVar10;
  bool bVar11;
  
  uVar3 = param_1 << 1;
  bVar10 = uVar3 == 0;
  uVar1 = param_1 & 0x80000000;
  uVar6 = (uint)((int)uVar3 >> 3) >> 1;
  uVar2 = uVar1 | uVar6;
  uVar9 = param_1 << 0x1d;
  if (!bVar10) {
    param_4 = uVar3 & 0xff000000;
    bVar10 = param_4 == 0;
  }
  if (!bVar10) {
    bVar10 = param_4 == 0xff000000;
  }
  if (!bVar10) {
    return CONCAT44(uVar2,uVar9) ^ 0x3800000000000000;
  }
  if (uVar3 == 0 || param_4 == 0xff000000) {
    return CONCAT44(uVar2,uVar9);
  }
  uVar3 = uVar9;
  uVar4 = uVar6;
  if (uVar6 == 0) {
    uVar3 = 0;
    uVar4 = uVar9;
  }
  iVar7 = LZCOUNT(uVar4);
  if (uVar6 == 0) {
    iVar7 = iVar7 + 0x20;
  }
  uVar8 = iVar7 - 0xb;
  bVar11 = SBORROW4(uVar8,0x20);
  uVar5 = iVar7 - 0x2b;
  bVar10 = uVar5 == 0;
  uVar9 = uVar5;
  uVar6 = uVar5;
  if ((int)uVar8 < 0x20) {
    bVar11 = SCARRY4(uVar5,0xc);
    uVar6 = iVar7 - 0x1f;
    bVar10 = uVar6 == 0;
    uVar9 = uVar8;
    if (!bVar10 && -0xd < (int)uVar5) {
      uVar3 = uVar4 << (uVar8 & 0xff);
      uVar4 = uVar4 >> (0xc - uVar6 & 0xff);
      goto LAB_0001cc5c;
    }
  }
  if (bVar10 || (int)uVar6 < 0 != bVar11) {
    in_r12 = 0x20 - uVar9;
  }
  uVar4 = uVar4 << (uVar9 & 0xff);
  if (bVar10 || (int)uVar6 < 0 != bVar11) {
    uVar4 = uVar4 | uVar3 >> (in_r12 & 0xff);
    uVar3 = uVar3 << (uVar9 & 0xff);
  }
LAB_0001cc5c:
  if ((int)uVar8 < 0x381) {
    return CONCAT44(uVar4 + (0x380 - uVar8) * 0x100000 | uVar1,uVar3);
  }
  uVar9 = ~(0x380 - uVar8);
  if ((int)uVar9 < 0x1f) {
    if (uVar9 - 0x13 != 0 && -0xd < (int)(uVar9 - 0x1f)) {
      uVar9 = 0xc - (uVar9 - 0x13);
      return CONCAT44(uVar2,uVar3 >> (0x20 - uVar9 & 0xff) | uVar4 << (uVar9 & 0xff)) &
             0x80000000ffffffff;
    }
    uVar9 = uVar9 + 1;
    return CONCAT44(uVar1 | uVar4 >> (uVar9 & 0xff),
                    uVar3 >> (uVar9 & 0xff) | uVar4 << (0x20 - uVar9 & 0xff));
  }
  return CONCAT44(uVar2,uVar4 >> (uVar9 - 0x1f & 0xff)) & 0x80000000ffffffff;
}



ulonglong FUN_0001ce70(int param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  ulonglong uVar2;
  byte bVar3;
  uint uVar4;
  uint extraout_r2;
  uint extraout_r3;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint unaff_r5;
  uint uVar10;
  uint uVar11;
  uint extraout_r12;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  ulonglong uVar15;
  
  uVar15 = CONCAT44(param_2,param_1);
  uVar11 = 0x7ff;
  uVar7 = param_2 >> 0x14 & 0x7ff;
  bVar12 = uVar7 == 0;
  if (!bVar12) {
    unaff_r5 = param_4 >> 0x14 & 0x7ff;
    bVar12 = unaff_r5 == 0;
  }
  if (!bVar12) {
    bVar12 = uVar7 == 0x7ff;
  }
  if (!bVar12) {
    bVar12 = unaff_r5 == 0x7ff;
  }
  if (bVar12) {
    uVar15 = FUN_0001d050(param_1,param_2,param_3,param_4);
    param_3 = extraout_r2;
    param_4 = extraout_r3;
    uVar11 = extraout_r12;
  }
  uVar4 = (uint)(uVar15 >> 0x20);
  iVar8 = uVar7 + unaff_r5;
  uVar10 = uVar4 ^ param_4;
  uVar4 = uVar4 & ~(uVar11 << 0x15);
  uVar5 = param_4 & ~(uVar11 << 0x15);
  uVar7 = uVar4 | 0x100000;
  uVar6 = uVar5 | 0x100000;
  if ((uint)uVar15 == 0 && (uVar4 & 0xfffff) == 0 || param_3 == 0 && (uVar5 & 0xfffff) == 0) {
    uVar5 = (uint)uVar15 | param_3;
    uVar6 = (uVar10 & 0x80000000 | uVar7) ^ uVar6;
    uVar7 = uVar11 >> 1;
    bVar14 = SBORROW4(iVar8,uVar7);
    uVar9 = iVar8 - uVar7;
    bVar12 = uVar9 == 0;
    uVar4 = uVar9;
    if (!bVar12 && (int)uVar7 <= iVar8) {
      bVar14 = SBORROW4(uVar11,uVar9);
      uVar4 = uVar11 - uVar9;
      bVar12 = uVar11 == uVar9;
    }
    if (!bVar12 && (int)uVar4 < 0 == bVar14) {
      return CONCAT44(uVar6 | uVar9 * 0x100000,uVar5);
    }
    uVar6 = uVar6 | 0x100000;
    uVar11 = 0;
    bVar14 = SBORROW4(uVar9,1);
    uVar9 = uVar9 - 1;
    bVar12 = uVar9 == 0;
    uVar7 = uVar9;
  }
  else {
    uVar2 = (ulonglong)param_3 * (uVar15 & 0xffffffff);
    uVar15 = (ulonglong)uVar6 * (uVar15 & 0xffffffff) +
             (ulonglong)param_3 * (ulonglong)uVar7 + (uVar2 >> 0x20);
    uVar4 = (uint)uVar15;
    lVar1 = (ulonglong)uVar6 * (ulonglong)uVar7 + (uVar15 >> 0x20);
    uVar11 = (uint)lVar1;
    uVar7 = (uint)((ulonglong)lVar1 >> 0x20);
    if ((int)uVar2 != 0) {
      uVar4 = uVar4 | 1;
    }
    uVar9 = (iVar8 + -0xff) - ((uVar7 < 0x200) + 0x300);
    if (uVar7 < 0x200) {
      bVar3 = (byte)(uVar4 >> 0x1f);
      uVar4 = uVar4 << 1;
      lVar1 = CONCAT44(uVar7 * 2 + (uint)(CARRY4(uVar11,uVar11) || CARRY4(uVar11 * 2,(uint)bVar3)),
                       uVar11 * 2 + (uint)bVar3);
    }
    uVar6 = uVar10 & 0x80000000 | (int)((ulonglong)lVar1 >> 0x20) << 0xb | (uint)lVar1 >> 0x15;
    uVar5 = (uint)lVar1 << 0xb | uVar4 >> 0x15;
    uVar11 = uVar4 * 0x800;
    bVar13 = 0xfc < uVar9;
    bVar14 = SBORROW4(uVar9,0xfd);
    uVar10 = uVar9 - 0xfd;
    bVar12 = uVar10 == 0;
    uVar7 = uVar10;
    if (bVar13 && !bVar12) {
      bVar13 = 0x6ff < uVar10;
      bVar14 = SBORROW4(uVar10,0x700);
      uVar7 = uVar9 - 0x7fd;
      bVar12 = uVar10 == 0x700;
    }
    if (!bVar13 || bVar12) {
      bVar12 = 0x7fffffff < uVar11;
      if (uVar11 == 0x80000000) {
        bVar12 = (bool)((byte)(uVar4 >> 0x15) & 1);
      }
      return CONCAT44(uVar6 + uVar9 * 0x100000 + (uint)CARRY4(uVar5,(uint)bVar12),uVar5 + bVar12);
    }
  }
  if (!bVar12 && (int)uVar7 < 0 == bVar14) {
    return (ulonglong)(uVar6 & 0x80000000 | 0x7ff00000) << 0x20;
  }
  if (-0x36 < (int)uVar9) {
    uVar7 = -uVar9;
    uVar4 = uVar7 - 0x20;
    if (0x1f < (int)uVar7) {
      uVar10 = uVar5 >> (uVar4 & 0xff) | uVar6 << (0x20 - uVar4 & 0xff);
      uVar7 = (uVar6 >> (uVar4 & 0xff) & ~((uVar6 & 0x80000000) >> (uVar4 & 0xff))) -
              ((int)uVar10 >> 0x1f);
      if ((uVar11 == 0 && uVar5 << (0x20 - uVar4 & 0xff) == 0) && (uVar10 & 0x7fffffff) == 0) {
        uVar7 = uVar7 & ~(uVar10 >> 0x1f);
      }
      return CONCAT44(uVar6,uVar7) & 0x80000000ffffffff;
    }
    if (uVar7 - 0x14 != 0 && -0xd < (int)uVar4) {
      uVar4 = 0xc - (uVar7 - 0x14);
      uVar7 = uVar5 << (uVar4 & 0xff);
      uVar4 = uVar5 >> (0x20 - uVar4 & 0xff) | uVar6 << (uVar4 & 0xff);
      uVar5 = uVar4 + -((int)uVar7 >> 0x1f);
      if (uVar11 == 0 && (uVar7 & 0x7fffffff) == 0) {
        uVar5 = uVar5 & ~(uVar7 >> 0x1f);
      }
      return CONCAT44((uVar6 & 0x80000000) + (uint)CARRY4(uVar4,-((int)uVar7 >> 0x1f)),uVar5);
    }
    uVar4 = uVar5 << (uVar9 + 0x20 & 0xff);
    uVar5 = uVar5 >> (uVar7 & 0xff) | uVar6 << (uVar9 + 0x20 & 0xff);
    uVar10 = uVar5 + -((int)uVar4 >> 0x1f);
    if (uVar11 == 0 && (uVar4 & 0x7fffffff) == 0) {
      uVar10 = uVar10 & ~(uVar4 >> 0x1f);
    }
    return CONCAT44((uVar6 & 0x80000000) + ((uVar6 & 0x7fffffff) >> (uVar7 & 0xff)) +
                    (uint)CARRY4(uVar5,-((int)uVar4 >> 0x1f)),uVar10);
  }
  return (ulonglong)(uVar6 & 0x80000000) << 0x20;
}



ulonglong FUN_0001d050(int param_1,uint param_2,int param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint unaff_r4;
  uint uVar4;
  uint uVar5;
  uint in_r12;
  
  uVar4 = in_r12 & param_4 >> 0x14;
  if (unaff_r4 != in_r12 && uVar4 != in_r12) {
    if (param_1 == 0 && (param_2 & 0x7fffffff) == 0 || param_3 == 0 && (param_4 & 0x7fffffff) == 0)
    {
      return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
    }
    if (unaff_r4 == 0) {
      uVar5 = param_2 & 0x80000000;
      do {
        iVar2 = param_1 >> 0x1f;
        param_1 = param_1 << 1;
        param_2 = param_2 * 2 - iVar2;
      } while ((param_2 & 0x100000) == 0);
      param_2 = param_2 | uVar5;
      if (uVar4 != 0) {
        return CONCAT44(param_2,param_1);
      }
    }
    do {
      iVar2 = param_3 >> 0x1f;
      param_3 = param_3 << 1;
      param_4 = param_4 * 2 - iVar2;
    } while ((param_4 & 0x100000) == 0);
    return CONCAT44(param_2,param_1);
  }
  bVar1 = (param_2 & 0x7fffffff) != 0;
  uVar5 = param_4;
  iVar2 = param_3;
  if (param_1 != 0 || bVar1) {
    uVar5 = param_2;
    iVar2 = param_1;
  }
  uVar3 = uVar5;
  if ((((param_1 != 0 || bVar1) && (param_3 != 0 || (param_4 & 0x7fffffff) != 0)) &&
      ((unaff_r4 != in_r12 || (iVar2 == 0 && (uVar5 & 0xfffff) == 0)))) &&
     ((uVar4 != in_r12 ||
      (iVar2 = param_3, uVar3 = param_4, param_3 == 0 && (param_4 & 0xfffff) == 0)))) {
    return (ulonglong)((uVar5 ^ param_4) & 0x80000000 | 0x7ff00000) << 0x20;
  }
  return CONCAT44(uVar3,iVar2) | 0x7ff8000000000000;
}



ulonglong FUN_0001d0dc(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint extraout_r2;
  uint uVar3;
  uint extraout_r3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint unaff_r5;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint extraout_r12;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  ulonglong uVar16;
  
  uVar16 = CONCAT44(param_2,param_1);
  uVar11 = 0x7ff;
  uVar6 = param_2 >> 0x14 & 0x7ff;
  bVar13 = uVar6 == 0;
  if (!bVar13) {
    unaff_r5 = param_4 >> 0x14 & 0x7ff;
    bVar13 = unaff_r5 == 0;
  }
  if (!bVar13) {
    bVar13 = uVar6 == 0x7ff;
  }
  if (!bVar13) {
    bVar13 = unaff_r5 == 0x7ff;
  }
  if (bVar13) {
    uVar16 = FUN_0001d270(param_1,param_2,param_3,param_4);
    param_3 = extraout_r2;
    param_4 = extraout_r3;
    uVar11 = extraout_r12;
  }
  uVar8 = (uint)(uVar16 >> 0x20);
  uVar2 = (uint)uVar16;
  iVar7 = uVar6 - unaff_r5;
  if (param_3 == 0 && (param_4 & 0xfffff) == 0) {
    uVar6 = (uVar8 ^ param_4) & 0x80000000 | uVar8 & 0xfffff;
    bVar14 = SCARRY4(iVar7,uVar11 >> 1);
    uVar8 = iVar7 + (uVar11 >> 1);
    bVar13 = (int)uVar8 < 0;
    bVar15 = uVar8 == 0;
    if (!bVar15 && bVar13 == bVar14) {
      bVar14 = SBORROW4(uVar11,uVar8);
      bVar13 = (int)(uVar11 - uVar8) < 0;
      bVar15 = uVar11 == uVar8;
    }
    if (!bVar15 && bVar13 == bVar14) {
      return CONCAT44(uVar6 | uVar8 * 0x100000,uVar2);
    }
    uVar6 = uVar6 | 0x100000;
    uVar4 = 0;
    bVar15 = SBORROW4(uVar8,1);
    uVar8 = uVar8 - 1;
    bVar13 = uVar8 == 0;
    uVar11 = uVar8;
  }
  else {
    uVar4 = (param_4 << 0xc) >> 4 | 0x10000000 | param_3 >> 0x18;
    uVar11 = param_3 << 8;
    uVar9 = (uVar8 << 0xc) >> 4 | 0x10000000 | uVar2 >> 0x18;
    uVar2 = uVar2 * 0x100;
    uVar6 = (uVar8 ^ param_4) & 0x80000000;
    bVar13 = uVar4 <= uVar9;
    if (uVar9 == uVar4) {
      bVar13 = uVar11 <= uVar2;
    }
    iVar7 = iVar7 + (uint)bVar13;
    uVar8 = iVar7 + 0x3fd;
    if (!bVar13) {
      uVar4 = uVar4 >> 1;
      uVar11 = (uint)((byte)(param_3 >> 0x18) & 1) << 0x1f | uVar11 >> 1;
    }
    uVar10 = uVar2 - uVar11;
    uVar9 = uVar9 - (uVar4 + (uVar2 < uVar11));
    uVar5 = uVar4 >> 1;
    uVar3 = (uint)((byte)uVar4 & 1) << 0x1f | uVar11 >> 1;
    uVar2 = 0x100000;
    uVar11 = 0x80000;
    while( true ) {
      bVar13 = uVar3 <= uVar10;
      if (uVar5 < uVar9 || uVar9 - uVar5 < (uint)bVar13) {
        uVar10 = uVar10 - uVar3;
        uVar2 = uVar2 | uVar11;
        uVar9 = uVar9 - (uVar5 + !bVar13);
      }
      uVar4 = uVar5 >> 1;
      uVar3 = (uint)((byte)uVar5 & 1) << 0x1f | uVar3 >> 1;
      bVar13 = uVar3 <= uVar10;
      if (uVar4 < uVar9 || uVar9 - uVar4 < (uint)bVar13) {
        uVar10 = uVar10 - uVar3;
        uVar2 = uVar2 | uVar11 >> 1;
        uVar9 = uVar9 - (uVar4 + !bVar13);
      }
      uVar12 = uVar5 >> 2;
      uVar1 = (uint)((byte)uVar4 & 1) << 0x1f | uVar3 >> 1;
      bVar13 = uVar1 <= uVar10;
      if (uVar12 < uVar9 || uVar9 - uVar12 < (uint)bVar13) {
        uVar10 = uVar10 - uVar1;
        uVar2 = uVar2 | uVar11 >> 2;
        uVar9 = uVar9 - (uVar12 + !bVar13);
      }
      uVar5 = uVar5 >> 3;
      uVar3 = (uint)((byte)uVar12 & 1) << 0x1f | uVar1 >> 1;
      bVar13 = uVar3 <= uVar10;
      if (uVar5 < uVar9 || uVar9 - uVar5 < (uint)bVar13) {
        uVar10 = uVar10 - uVar3;
        uVar2 = uVar2 | uVar11 >> 3;
        uVar9 = uVar9 - (uVar5 + !bVar13);
      }
      uVar4 = uVar9 | uVar10;
      if (uVar4 == 0) break;
      uVar9 = uVar9 << 4 | uVar10 >> 0x1c;
      uVar10 = uVar10 << 4;
      uVar5 = uVar5 << 3 | uVar3 >> 0x1d;
      uVar3 = (uVar1 >> 1) << 3;
      uVar11 = uVar11 >> 4;
      if (uVar11 == 0) {
        if ((uVar6 & 0x100000) != 0) goto LAB_0001d21c;
        uVar6 = uVar6 | uVar2;
        uVar2 = 0;
        uVar11 = 0x80000000;
      }
    }
    if ((uVar6 & 0x100000) == 0) {
      uVar6 = uVar6 | uVar2;
      uVar2 = 0;
    }
LAB_0001d21c:
    bVar14 = 0xfc < uVar8;
    bVar15 = SBORROW4(uVar8,0xfd);
    uVar12 = iVar7 + 0x300;
    bVar13 = uVar12 == 0;
    uVar11 = uVar12;
    if (bVar14 && !bVar13) {
      bVar14 = 0x6ff < uVar12;
      bVar15 = SBORROW4(uVar12,0x700);
      uVar11 = iVar7 - 0x400;
      bVar13 = uVar12 == 0x700;
    }
    if (!bVar14 || bVar13) {
      bVar13 = uVar5 <= uVar9;
      if (uVar9 == uVar5) {
        bVar13 = uVar3 <= uVar10;
      }
      if (uVar9 == uVar5 && uVar10 == uVar3) {
        bVar13 = (bool)((byte)uVar2 & 1);
      }
      return CONCAT44(uVar6 + uVar8 * 0x100000 + (uint)CARRY4(uVar2,(uint)bVar13),uVar2 + bVar13);
    }
  }
  if (!bVar13 && (int)uVar11 < 0 == bVar15) {
    return (ulonglong)(uVar6 & 0x80000000 | 0x7ff00000) << 0x20;
  }
  if ((int)uVar8 < -0x35) {
    return (ulonglong)(uVar6 & 0x80000000) << 0x20;
  }
  uVar11 = -uVar8;
  uVar9 = uVar11 - 0x20;
  if (0x1f < (int)uVar11) {
    uVar8 = uVar2 >> (uVar9 & 0xff) | uVar6 << (0x20 - uVar9 & 0xff);
    uVar11 = (uVar6 >> (uVar9 & 0xff) & ~((uVar6 & 0x80000000) >> (uVar9 & 0xff))) -
             ((int)uVar8 >> 0x1f);
    if ((uVar4 == 0 && uVar2 << (0x20 - uVar9 & 0xff) == 0) && (uVar8 & 0x7fffffff) == 0) {
      uVar11 = uVar11 & ~(uVar8 >> 0x1f);
    }
    return CONCAT44(uVar6,uVar11) & 0x80000000ffffffff;
  }
  if (uVar11 - 0x14 != 0 && -0xd < (int)uVar9) {
    uVar8 = 0xc - (uVar11 - 0x14);
    uVar11 = uVar2 << (uVar8 & 0xff);
    uVar2 = uVar2 >> (0x20 - uVar8 & 0xff) | uVar6 << (uVar8 & 0xff);
    uVar8 = uVar2 + -((int)uVar11 >> 0x1f);
    if (uVar4 == 0 && (uVar11 & 0x7fffffff) == 0) {
      uVar8 = uVar8 & ~(uVar11 >> 0x1f);
    }
    return CONCAT44((uVar6 & 0x80000000) + (uint)CARRY4(uVar2,-((int)uVar11 >> 0x1f)),uVar8);
  }
  uVar9 = uVar2 << (uVar8 + 0x20 & 0xff);
  uVar2 = uVar2 >> (uVar11 & 0xff) | uVar6 << (uVar8 + 0x20 & 0xff);
  uVar8 = uVar2 + -((int)uVar9 >> 0x1f);
  if (uVar4 == 0 && (uVar9 & 0x7fffffff) == 0) {
    uVar8 = uVar8 & ~(uVar9 >> 0x1f);
  }
  return CONCAT44((uVar6 & 0x80000000) + ((uVar6 & 0x7fffffff) >> (uVar11 & 0xff)) +
                  (uint)CARRY4(uVar2,-((int)uVar9 >> 0x1f)),uVar8);
}



ulonglong FUN_0001d270(int param_1,uint param_2,int param_3,uint param_4)

{
  int iVar1;
  uint unaff_r4;
  uint uVar2;
  uint uVar3;
  uint in_r12;
  
  uVar2 = in_r12 & param_4 >> 0x14;
  uVar3 = param_2;
  if (unaff_r4 != in_r12 || uVar2 != in_r12) {
    if (unaff_r4 == in_r12) {
      if ((param_1 == 0 && (param_2 & 0xfffff) == 0) &&
         (param_1 = param_3, uVar3 = param_4, uVar2 != in_r12)) {
LAB_0001d0b8:
        return (ulonglong)((param_2 ^ param_4) & 0x80000000 | 0x7ff00000) << 0x20;
      }
    }
    else if (uVar2 == in_r12) {
      param_1 = param_3;
      uVar3 = param_4;
      if (param_3 == 0 && (param_4 & 0xfffff) == 0) {
LAB_0001d06c:
        return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
      }
    }
    else {
      if ((param_1 != 0 || (param_2 & 0x7fffffff) != 0) &&
          (param_3 != 0 || (param_4 & 0x7fffffff) != 0)) {
        if (unaff_r4 == 0) {
          uVar3 = param_2 & 0x80000000;
          do {
            iVar1 = param_1 >> 0x1f;
            param_1 = param_1 << 1;
            param_2 = param_2 * 2 - iVar1;
          } while ((param_2 & 0x100000) == 0);
          param_2 = param_2 | uVar3;
          if (uVar2 != 0) {
            return CONCAT44(param_2,param_1);
          }
        }
        do {
          iVar1 = param_3 >> 0x1f;
          param_3 = param_3 << 1;
          param_4 = param_4 * 2 - iVar1;
        } while ((param_4 & 0x100000) == 0);
        return CONCAT44(param_2,param_1);
      }
      if (param_1 != 0 || (param_2 & 0x7fffffff) != 0) goto LAB_0001d0b8;
      if (param_3 != 0 || (param_4 & 0x7fffffff) != 0) goto LAB_0001d06c;
    }
  }
  return CONCAT44(uVar3,param_1) | 0x7ff8000000000000;
}



uint FUN_0001d2e0(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_2 * 2 + 0x200000;
  if (param_2 * 2 < 0xffe00000) {
    if (-1 < iVar2) {
      return 0;
    }
    uVar1 = iVar2 >> 0x15;
    uVar3 = -uVar1 - 0x3e1;
    if (uVar1 < 0xfffffc20 && uVar3 != 0) {
      uVar1 = (param_2 << 0xb | 0x80000000 | param_1 >> 0x15) >> (uVar3 & 0xff);
      if ((param_2 & 0x80000000) != 0) {
        uVar1 = -uVar1;
      }
      return uVar1;
    }
  }
  else if (param_1 != 0 || (param_2 & 0xfffff) != 0) {
    return 0;
  }
  uVar1 = param_2 & 0x80000000;
  if (uVar1 == 0) {
    uVar1 = 0x7fffffff;
  }
  return uVar1;
}



uint FUN_0001d33c(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if (SUB41(param_2 >> 0x1f,0)) {
    return 0;
  }
  iVar1 = param_2 * 2 + 0x200000;
  if (param_2 * 2 < 0xffe00000) {
    if (-1 < iVar1) {
      return 0;
    }
    uVar2 = -(iVar1 >> 0x15) - 0x3e1;
    if (-1 < (int)uVar2) {
      return (param_2 << 0xb | 0x80000000 | param_1 >> 0x15) >> (uVar2 & 0xff);
    }
  }
  else if (param_1 != 0 || (param_2 & 0xfffff) != 0) {
    return 0;
  }
  return 0xffffffff;
}



uint FUN_0001d390(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint in_r12;
  bool bVar4;
  bool bVar5;
  
  uVar2 = param_2 * 2;
  bVar5 = uVar2 < 0x70000000;
  uVar3 = uVar2 + 0x90000000;
  uVar1 = uVar3;
  if (!bVar5) {
    in_r12 = uVar2 + 0x8fe00000;
    uVar1 = in_r12;
  }
  bVar4 = uVar1 == 0;
  if (!bVar5 && uVar3 >= 0x200000) {
    bVar4 = in_r12 == 0x1fc00000;
  }
  if (((bVar5 || uVar3 < 0x200000) || 0x1fc00000 < in_r12) || bVar4) {
    if ((param_2 & 0x40000000) != 0) {
      if (((int)uVar2 >> 0x15 == -1) && (param_1 != 0 || (param_2 & 0xfffff) != 0)) {
        return 0x7fc00000;
      }
      return param_2 & 0x80000000 | 0x7f800000;
    }
    if ((int)uVar3 < -0x2e00000) {
      return param_2 & 0x80000000;
    }
    uVar3 = 0x18 - (uVar2 + 0x92e00000 >> 0x15);
    uVar2 = param_1 >> (uVar3 & 0xff);
    if (param_1 << (0x20 - uVar3 & 0xff) != 0) {
      uVar2 = uVar2 | 1;
    }
    uVar1 = param_2 & 0x1fffff | 0x100000;
    param_1 = uVar2 | uVar1 << (0x20 - uVar3 & 0xff);
    uVar3 = (uVar1 >> (uVar3 & 0xff)) << 1;
  }
  uVar2 = (param_2 & 0x80000000 | param_1 >> 0x1d) + uVar3 * 4 + (uint)(0x7fffffff < param_1 * 8);
  if (param_1 * 8 == 0x80000000) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}



uint FUN_0001d5d4(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = param_1 & 0x80000000;
  if ((int)uVar3 < 0) {
    param_1 = -param_1;
  }
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = LZCOUNT(param_1);
  uVar2 = uVar1 - 8;
  iVar4 = ((uVar3 | 0x4b000000) - 0x800000) + uVar2 * -0x800000;
  if (7 < uVar1) {
    uVar3 = 0 << (uVar2 & 0xff);
    uVar1 = iVar4 + (param_1 << (uVar2 & 0xff)) + (0U >> (0x20 - uVar2 & 0xff)) +
            (uint)(0x7fffffff < uVar3);
    if (uVar3 == 0x80000000) {
      uVar1 = uVar1 & 0xfffffffe;
    }
    return uVar1;
  }
  uVar3 = param_1 << uVar1 + 0x18;
  uVar1 = (iVar4 + (param_1 >> (0x20 - (uVar1 + 0x18) & 0xff))) - ((int)uVar3 >> 0x1f);
  if ((uVar3 & 0x7fffffff) == 0) {
    uVar1 = uVar1 & ~(uVar3 >> 0x1f);
  }
  return uVar1;
}



uint FUN_0001d680(uint param_1,uint param_2,undefined4 param_3,uint param_4)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  bool bVar11;
  
  uVar3 = param_1 >> 0x17 & 0xff;
  bVar10 = uVar3 == 0;
  if (!bVar10) {
    param_4 = param_2 >> 0x17 & 0xff;
    bVar10 = param_4 == 0;
  }
  if (!bVar10) {
    bVar10 = uVar3 == 0xff;
  }
  if (!bVar10) {
    bVar10 = param_4 == 0xff;
  }
  if (bVar10) {
    param_4 = param_2 >> 0x17 & 0xff;
    if (uVar3 == 0xff || param_4 == 0xff) {
      uVar9 = param_2;
      if (param_1 != 0 && param_1 != 0x80000000) {
        uVar9 = param_1;
      }
      uVar5 = uVar9;
      if (((((param_1 == 0 || param_1 == 0x80000000) || param_2 == 0) || param_2 == 0x80000000) ||
          ((uVar3 == 0xff && ((uVar9 & 0x7fffff) != 0)))) ||
         ((param_4 == 0xff && (uVar5 = param_2, (param_2 & 0x7fffff) != 0)))) {
        return uVar5 | 0x7fc00000;
      }
      uVar9 = uVar9 ^ param_2;
      goto LAB_0001d7fc;
    }
    if ((param_1 & 0x7fffffff) == 0 || (param_2 & 0x7fffffff) == 0) {
      return (param_1 ^ param_2) & 0x80000000;
    }
    bVar10 = uVar3 == 0;
    uVar9 = param_1 & 0x80000000;
    while( true ) {
      if (bVar10) {
        param_1 = param_1 << 1;
        bVar10 = (param_1 & 0x800000) == 0;
      }
      if (!bVar10) break;
      uVar3 = uVar3 - 1;
    }
    param_1 = param_1 | uVar9;
    bVar10 = param_4 == 0;
    uVar9 = param_2 & 0x80000000;
    while( true ) {
      if (bVar10) {
        param_2 = param_2 << 1;
        bVar10 = (param_2 & 0x800000) == 0;
      }
      if (!bVar10) break;
      param_4 = param_4 - 1;
    }
    param_2 = param_2 | uVar9;
  }
  iVar4 = uVar3 + param_4;
  uVar9 = param_1 ^ param_2;
  uVar3 = param_1 << 9;
  bVar10 = uVar3 == 0;
  if (!bVar10) {
    param_2 = param_2 << 9;
    bVar10 = param_2 == 0;
  }
  if (bVar10) {
    if (uVar3 == 0) {
      param_2 = param_2 << 9;
    }
    uVar9 = uVar9 & 0x80000000 | param_1 & 0x7fffff | param_2 >> 9;
    bVar11 = SBORROW4(iVar4,0x7f);
    iVar6 = iVar4 + -0x7f;
    bVar10 = iVar6 == 0;
    iVar7 = iVar6;
    if (!bVar10 && 0x7e < iVar4) {
      bVar11 = SBORROW4(0xff,iVar6);
      iVar7 = -iVar6 + 0xff;
      bVar10 = -iVar6 == -0xff;
    }
    if (!bVar10 && iVar7 < 0 == bVar11) {
      return uVar9 | iVar6 * 0x800000;
    }
    uVar9 = uVar9 | 0x800000;
    uVar8 = 0;
    bVar11 = SBORROW4(iVar6,1);
    uVar5 = iVar4 - 0x80;
    bVar10 = uVar5 == 0;
    uVar3 = uVar5;
  }
  else {
    lVar2 = (ulonglong)(param_2 >> 5 | 0x8000000) * (ulonglong)(uVar3 >> 5 | 0x8000000);
    bVar10 = (uint)((ulonglong)lVar2 >> 0x20) < 0x800000;
    if (bVar10) {
      lVar2 = lVar2 * 2;
    }
    uVar8 = (uint)lVar2;
    uVar9 = uVar9 & 0x80000000 | (uint)((ulonglong)lVar2 >> 0x20);
    uVar5 = iVar4 - (bVar10 + 0x7f);
    bVar11 = SBORROW4(uVar5,0xfd);
    bVar10 = uVar5 == 0xfd;
    uVar3 = uVar5 - 0xfd;
    if (uVar5 < 0xfe) {
      uVar3 = uVar9 + uVar5 * 0x800000 + (uint)(0x7fffffff < uVar8);
      if (uVar8 == 0x80000000) {
        uVar3 = uVar3 & 0xfffffffe;
      }
      return uVar3;
    }
  }
  if (bVar10 || (int)uVar3 < 0 != bVar11) {
    if (-0x19 < (int)uVar5) {
      uVar1 = (uVar9 << 1) >> (-uVar5 & 0xff);
      uVar3 = uVar9 << (uVar5 + 0x20 & 0xff);
      uVar9 = (uVar9 & 0x80000000 | uVar1 >> 1) + (uint)((byte)uVar1 & 1);
      if (uVar8 == 0 && (uVar3 & 0x7fffffff) == 0) {
        uVar9 = uVar9 & ~(uVar3 >> 0x1f);
      }
      return uVar9;
    }
    return uVar9 & 0x80000000;
  }
LAB_0001d7fc:
  return uVar9 & 0x80000000 | 0x7f800000;
}



uint FUN_0001d818(uint param_1,uint param_2,undefined4 param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  
  uVar2 = param_1 >> 0x17 & 0xff;
  bVar9 = uVar2 == 0;
  if (!bVar9) {
    param_4 = param_2 >> 0x17 & 0xff;
    bVar9 = param_4 == 0;
  }
  if (!bVar9) {
    bVar9 = uVar2 == 0xff;
  }
  if (!bVar9) {
    bVar9 = param_4 == 0xff;
  }
  if (bVar9) {
    param_4 = param_2 >> 0x17 & 0xff;
    uVar6 = param_1;
    if (uVar2 == 0xff) {
      if (((param_1 & 0x7fffff) != 0) || (uVar6 = param_2, param_4 == 0xff)) {
LAB_0001d80c:
        return uVar6 | 0x7fc00000;
      }
    }
    else {
      if (param_4 == 0xff) {
        uVar6 = param_2;
        if ((param_2 & 0x7fffff) == 0) {
LAB_0001d7b0:
          return (param_1 ^ param_2) & 0x80000000;
        }
        goto LAB_0001d80c;
      }
      if ((param_1 & 0x7fffffff) != 0 && (param_2 & 0x7fffffff) != 0) {
        bVar9 = uVar2 == 0;
        uVar6 = param_1 & 0x80000000;
        while( true ) {
          if (bVar9) {
            param_1 = param_1 << 1;
            bVar9 = (param_1 & 0x800000) == 0;
          }
          if (!bVar9) break;
          uVar2 = uVar2 - 1;
        }
        param_1 = param_1 | uVar6;
        bVar9 = param_4 == 0;
        uVar6 = param_2 & 0x80000000;
        while( true ) {
          if (bVar9) {
            param_2 = param_2 << 1;
            bVar9 = (param_2 & 0x800000) == 0;
          }
          if (!bVar9) break;
          param_4 = param_4 - 1;
        }
        param_2 = param_2 | uVar6;
        goto LAB_0001d830;
      }
      if ((param_1 & 0x7fffffff) == 0) {
        if ((param_2 & 0x7fffffff) != 0) goto LAB_0001d7b0;
        goto LAB_0001d80c;
      }
    }
    uVar2 = param_1 ^ param_2;
  }
  else {
LAB_0001d830:
    iVar3 = uVar2 - param_4;
    if (param_2 << 9 == 0) {
      uVar2 = (param_1 ^ param_2) & 0x80000000 | param_1 & 0x7fffff;
      bVar10 = SCARRY4(iVar3,0x7f);
      iVar5 = iVar3 + 0x7f;
      bVar9 = iVar5 == 0;
      iVar7 = iVar5;
      if (!bVar9 && -0x80 < iVar3) {
        bVar10 = SBORROW4(0xff,iVar5);
        iVar7 = -iVar5 + 0xff;
        bVar9 = -iVar5 == -0xff;
      }
      if (!bVar9 && iVar7 < 0 == bVar10) {
        return uVar2 | iVar5 * 0x800000;
      }
      uVar2 = uVar2 | 0x800000;
      uVar6 = 0;
      bVar10 = SBORROW4(iVar5,1);
      uVar4 = iVar3 + 0x7e;
      bVar9 = uVar4 == 0;
      uVar8 = uVar4;
    }
    else {
      uVar1 = (param_2 << 9) >> 4 | 0x10000000;
      uVar6 = (param_1 << 9) >> 4 | 0x10000000;
      uVar2 = (param_1 ^ param_2) & 0x80000000;
      bVar9 = uVar1 <= uVar6;
      if (!bVar9) {
        uVar6 = uVar6 << 1;
      }
      uVar4 = iVar3 + 0x7d + (uint)bVar9;
      uVar8 = 0x800000;
      do {
        if (uVar1 <= uVar6) {
          uVar6 = uVar6 - uVar1;
          uVar2 = uVar2 | uVar8;
        }
        if (uVar1 >> 1 <= uVar6) {
          uVar6 = uVar6 - (uVar1 >> 1);
          uVar2 = uVar2 | uVar8 >> 1;
        }
        if (uVar1 >> 2 <= uVar6) {
          uVar6 = uVar6 - (uVar1 >> 2);
          uVar2 = uVar2 | uVar8 >> 2;
        }
        if (uVar1 >> 3 <= uVar6) {
          uVar6 = uVar6 - (uVar1 >> 3);
          uVar2 = uVar2 | uVar8 >> 3;
        }
        uVar6 = uVar6 * 0x10;
        bVar9 = uVar6 == 0;
        if (!bVar9) {
          uVar8 = uVar8 >> 4;
          bVar9 = uVar8 == 0;
        }
      } while (!bVar9);
      bVar10 = SBORROW4(uVar4,0xfd);
      bVar9 = uVar4 == 0xfd;
      uVar8 = uVar4 - 0xfd;
      if (uVar4 < 0xfe) {
        uVar2 = uVar2 + uVar4 * 0x800000 + (uint)(uVar1 <= uVar6);
        if (uVar6 == uVar1) {
          uVar2 = uVar2 & 0xfffffffe;
        }
        return uVar2;
      }
    }
    if (bVar9 || (int)uVar8 < 0 != bVar10) {
      if (-0x19 < (int)uVar4) {
        uVar1 = (uVar2 << 1) >> (-uVar4 & 0xff);
        uVar8 = uVar2 << (uVar4 + 0x20 & 0xff);
        uVar2 = (uVar2 & 0x80000000 | uVar1 >> 1) + (uint)((byte)uVar1 & 1);
        if (uVar6 == 0 && (uVar8 & 0x7fffffff) == 0) {
          uVar2 = uVar2 & ~(uVar8 >> 0x1f);
        }
        return uVar2;
      }
      return uVar2 & 0x80000000;
    }
  }
  return uVar2 & 0x80000000 | 0x7f800000;
}



uint FUN_0001d988(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  
  uVar1 = param_1 * 2;
  uVar2 = param_2 * 2;
  if (((int)uVar1 >> 0x18 == -1 || (int)uVar2 >> 0x18 == -1) &&
     ((((int)uVar1 >> 0x18 == -1 && ((param_1 & 0x7fffff) != 0)) ||
      (((int)uVar2 >> 0x18 == -1 && ((param_2 & 0x7fffff) != 0)))))) {
    return 1;
  }
  bVar4 = (param_2 & 0x7fffffff) == 0;
  bVar5 = uVar1 == 0 && bVar4;
  uVar3 = 0;
  if (uVar1 != 0 || !bVar4) {
    uVar3 = param_1 ^ param_2;
    bVar5 = uVar3 == 0;
  }
  bVar4 = -1 < (int)uVar3;
  if (bVar4) {
    param_1 = uVar1 + param_2 * -2;
    bVar5 = param_1 == 0;
  }
  if ((bVar4 && uVar1 >= uVar2) && !bVar5) {
    param_1 = (int)param_2 >> 0x1f;
  }
  if (!bVar4 || uVar1 < uVar2) {
    param_1 = ~((int)param_2 >> 0x1f);
  }
  if (!bVar5) {
    param_1 = param_1 | 1;
  }
  return param_1;
}



undefined8 FUN_0001d9ec(uint param_1,uint param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0001d9fc(param_2,param_1);
  return uVar1;
}



undefined8 FUN_0001d9fc(uint param_1,uint param_2)

{
  FUN_0001d988(param_1,param_2);
  return CONCAT44(param_2,param_1);
}



undefined1 FUN_0001da10(uint param_1,uint param_2)

{
  undefined1 in_ZR;
  
  FUN_0001d9fc(param_1,param_2);
  return in_ZR;
}



bool FUN_0001da24(uint param_1,uint param_2)

{
  undefined1 in_CY;
  
  FUN_0001d9fc(param_1,param_2);
  return !(bool)in_CY;
}



bool FUN_0001da38(uint param_1,uint param_2)

{
  undefined1 in_ZR;
  undefined1 in_CY;
  
  FUN_0001d9fc(param_1,param_2);
  return !(bool)in_CY || (bool)in_ZR;
}



bool FUN_0001da4c(uint param_1,uint param_2)

{
  undefined1 in_ZR;
  undefined1 in_CY;
  
  FUN_0001d9ec(param_1,param_2);
  return !(bool)in_CY || (bool)in_ZR;
}



bool FUN_0001da60(uint param_1,uint param_2)

{
  undefined1 in_CY;
  
  FUN_0001d9ec(param_1,param_2);
  return !(bool)in_CY;
}



uint FUN_0001da74(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 << 1 < 0x7f000000) {
    return 0;
  }
  uVar1 = (param_1 << 1) >> 0x18;
  uVar2 = 0x9e - uVar1;
  if (uVar1 < 0x9f && uVar2 != 0) {
    uVar1 = (param_1 << 8 | 0x80000000) >> (uVar2 & 0xff);
    if ((param_1 & 0x80000000) != 0) {
      uVar1 = -uVar1;
    }
    return uVar1;
  }
  if ((uVar2 == 0xffffff9f) && ((param_1 & 0x7fffff) != 0)) {
    return 0;
  }
  uVar1 = param_1 & 0x80000000;
  if (uVar1 == 0) {
    uVar1 = 0x7fffffff;
  }
  return uVar1;
}



void _fini(void)

{
  return;
}


