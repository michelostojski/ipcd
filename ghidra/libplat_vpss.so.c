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
undefined4 DAT_00035090;
dword DWORD_00024b54;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_0003516c;
undefined4 DAT_0003518c;
undefined DAT_000351e0;
undefined DAT_00035094;
uint DAT_00035218;
undefined DAT_0003524c;
undefined DAT_00035258;
uint DAT_00035220;
undefined4 DAT_0003521c;
undefined4 DAT_00035224;
undefined DAT_000351d8;
int DAT_00035260;
int DAT_00035254;
undefined4 DAT_00035184;
undefined4 DAT_00035188;
undefined4 DAT_000351c8;
undefined4 DAT_000351cc;
int DAT_000351d0;
int DAT_000351d4;
int DAT_00035188;
int DAT_00035184;
int DAT_000351c8;
undefined DAT_00022b78;
int DAT_00035250;
undefined ak_debug_info;
undefined4 DAT_00035264;
undefined4 DAT_00035260;
uint DAT_00035274;
uint DAT_00035264;
uint DAT_00035278;
uint DAT_00035284;
int DAT_00035288;
uint DAT_0003528c;
int DAT_00035290;
uint DAT_00035268;
uint DAT_00035270;
uint DAT_0003527c;
uint DAT_00035280;
undefined DAT_0003529c;
undefined DAT_00035320;
int DAT_00035298;
int DAT_00035294;
undefined4 DAT_00035298;
undefined4 DAT_00035294;
undefined DAT_000353d4;
undefined AK_ISP_set_wdr_attr;
undefined AK_ISP_get_wdr_attr;
undefined DAT_0003543c;
undefined DAT_0003a22c;
undefined DAT_0003a228;
undefined DAT_0003a248;
undefined AK_ISP_set_sharp_attr;
undefined DAT_000353bc;
undefined DAT_000353c0;
undefined DAT_000353d8;
undefined DAT_00035414;
undefined DAT_0003541c;
int DAT_00035134;
undefined DAT_000353a8;
undefined DAT_000353ac;
undefined DAT_000353b0;
undefined DAT_000353b4;
undefined DAT_000353b8;
undefined4 DAT_00035134;
undefined DAT_0003f9ac;
undefined DAT_0003a218;
undefined DAT_0003a21c;
undefined DAT_0003a220;
undefined DAT_0003a224;
undefined DAT_0003f9e4;
undefined DAT_0003fa08;
undefined DAT_0003fa0c;
undefined DAT_0003fbc4;
undefined DAT_0003fbcc;
undefined AK_ISP_get_effect_attr;
undefined DAT_0003fbce;
undefined DAT_0003fbd0;
undefined DAT_00039394;
undefined AK_ISP_set_effect_attr;
undefined AK_ISP_set_ae_attr;
undefined DAT_0003f9dc;
undefined DAT_00024414;
undefined DAT_000353c8;
undefined DAT_000353cc;
undefined DAT_000353d0;
undefined DAT_000353a4;
undefined DAT_000353c4;
undefined1[48] Isp_Struct_len;
undefined DAT_00035418;
undefined DAT_00035420;
undefined DAT_00035424;
undefined DAT_0003fbe0;
undefined DAT_0003fbe4;
undefined vi_dev_load_sensor_conf;
undefined DAT_000249fc;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



int isp_get_sensor_fps(int param_1)

{
  int iVar1;
  
  iVar1 = isp_get_sensor_fps(param_1);
  return iVar1;
}



undefined4 isp_module_check_cfg(int param_1,uint *param_2)

{
  undefined4 uVar1;
  
  uVar1 = isp_module_check_cfg(param_1,param_2);
  return uVar1;
}



undefined4 calc_cur_lumi(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = calc_cur_lumi(param_1);
  return uVar1;
}



undefined4 isp_set_effect(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = isp_set_effect(param_1,param_2,param_3);
  return uVar1;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



uint isp_get_attr(int param_1,uint param_2,void *param_3,undefined4 *param_4)

{
  uint uVar1;
  
  uVar1 = isp_get_attr(param_1,param_2,param_3,param_4);
  return uVar1;
}



undefined4 night_status_change(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = night_status_change(param_1);
  return uVar1;
}



undefined4 save_soft_ir_info(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = save_soft_ir_info(param_1);
  return uVar1;
}



void isp_cfg_file_clear_path(int param_1)

{
  isp_cfg_file_clear_path(param_1);
  return;
}



undefined4 ak_vpss_get_ae_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_get_ae_attr(param_1,param_2);
  return uVar1;
}



undefined4
ak_vpss_get_rgb_dis(uint param_1,uint param_2,int param_3,uint param_4,int param_5,uint *param_6)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_get_rgb_dis(param_1,param_2,param_3,param_4,param_5,param_6);
  return uVar1;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



undefined4 ak_vpss_get_ev(uint param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_get_ev(param_1,param_2);
  return uVar1;
}



undefined4 ak_vpss_wait_exp_stable(uint param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_wait_exp_stable(param_1,param_2,param_3);
  return uVar1;
}



undefined4 ak_vpss_get_ae_run_info(int param_1,void *param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_get_ae_run_info(param_1,param_2);
  return uVar1;
}



undefined4 isp_open(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = isp_open(param_1);
  return uVar1;
}



undefined4 isp_set_sensor_fps(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = isp_set_sensor_fps(param_1,param_2);
  return uVar1;
}



undefined1 isp_cfg_file_get_style_id(void)

{
  undefined1 uVar1;
  
  uVar1 = isp_cfg_file_get_style_id();
  return uVar1;
}



uint isp_set_attr(int param_1,uint param_2,void *param_3,size_t param_4)

{
  uint uVar1;
  
  uVar1 = isp_set_attr(param_1,param_2,param_3,param_4);
  return uVar1;
}



undefined4 ak_vpss_get_awb_stat_info(int param_1,void *param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_get_awb_stat_info(param_1,param_2);
  return uVar1;
}



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



undefined4 isp_close(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = isp_close(param_1);
  return uVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int raise(int __sig)

{
  int iVar1;
  
  iVar1 = raise(__sig);
  return iVar1;
}



undefined4 ak_vpss_check_ae_stable(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_vpss_check_ae_stable(param_1,param_2);
  return uVar1;
}



// WARNING: Removing unreachable block (ram,0x00015748)
// WARNING: Removing unreachable block (ram,0x00015760)
// WARNING: Removing unreachable block (ram,0x00015768)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_00035090);
    entry();
    if (ppuVar1[0x1f] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_00024b54);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x000157ac)
// WARNING: Removing unreachable block (ram,0x000157c4)
// WARNING: Removing unreachable block (ram,0x000157cc)
// WARNING: Removing unreachable block (ram,0x000158b4)
// WARNING: Removing unreachable block (ram,0x000158c8)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_00024b54,&DAT_0003516c,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



undefined4 FUN_000158f0(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint *puVar4;
  char *pcVar5;
  uint *puVar6;
  undefined4 uVar7;
  int local_1b0;
  uint local_1ac [5];
  undefined1 auStack_198 [116];
  int iStack_124;
  int local_120 [19];
  undefined1 auStack_d4 [116];
  int iStack_60;
  int local_5c [19];
  
  local_1b0 = 0;
  iVar1 = isp_get_statinfo(param_1,0x1b,(int)auStack_198,&local_1b0);
  if (iVar1 == 0) {
    iVar1 = isp_get_statinfo(param_1,0x1b,(int)auStack_d4,&local_1b0);
    if (iVar1 == 0) {
      puVar6 = local_1ac;
      piVar3 = &iStack_124;
      piVar2 = &iStack_60;
      puVar4 = puVar6;
      do {
        piVar3 = piVar3 + 1;
        piVar2 = piVar2 + 1;
        *puVar4 = (uint)(*piVar2 + *piVar3) >> 1;
        puVar4 = puVar4 + 1;
      } while (piVar3 != local_120 + 4);
      ak_print(10,4,"[%s:%d] \n----[0]%ld--[1]%ld--[2]%ld--[3]%ld--[4]%ld-----\n",
               "night_mode_cmp_awb",0x1b3,local_1ac[0],local_1ac[1],local_1ac[2],local_1ac[3],
               local_1ac[4]);
      puVar4 = &DAT_0003518c;
      iVar1 = 1;
      if (local_1ac[0] <= DAT_0003518c) {
        do {
          if (iVar1 == 5) {
            pcVar5 = "night";
            uVar7 = 0;
            goto LAB_00015a00;
          }
          puVar6 = puVar6 + 1;
          puVar4 = puVar4 + 1;
          iVar1 = iVar1 + 1;
        } while (*puVar6 <= *puVar4);
      }
      uVar7 = 1;
      pcVar5 = "day";
LAB_00015a00:
      ak_print(10,4,"[%s:%d] awb_day_night=%s\n","night_mode_cmp_awb",0x1c2,pcVar5,local_1ac[1],
               local_1ac[2],local_1ac[3],local_1ac[4]);
      return uVar7;
    }
    uVar7 = 0x1a8;
  }
  else {
    uVar7 = 0x1a3;
  }
  ak_print(10,1,"[%s:%d] get awb info failed \n","night_mode_cmp_awb",uVar7);
  return 0xffffffff;
}



undefined4 FUN_00015a84(int param_1)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  int *piVar4;
  char *pcVar5;
  uint *puVar6;
  undefined4 uVar7;
  uint local_1cc;
  uint local_1c8 [5];
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [116];
  int iStack_12c;
  int local_128 [9];
  int aiStack_104 [10];
  undefined1 auStack_dc [116];
  int iStack_68;
  int local_64 [19];
  
  local_1cc = 0;
  iVar1 = isp_get_statinfo(param_1,0x1b,(int)auStack_1a0,(int *)&local_1cc);
  if (iVar1 == 0) {
    iVar1 = isp_get_statinfo(param_1,0x1b,(int)auStack_dc,(int *)&local_1cc);
    if (iVar1 == 0) {
      puVar3 = &local_1cc;
      piVar4 = &iStack_12c;
      piVar2 = &iStack_68;
      do {
        piVar4 = piVar4 + 1;
        piVar2 = piVar2 + 1;
        puVar3 = puVar3 + 1;
        *puVar3 = (uint)(*piVar2 + *piVar4) >> 1;
      } while (piVar4 != aiStack_104);
      ak_print(10,4,
               "[%s:%d] \n----[0]%ld--[1]%ld--[2]%ld--[3]%ld--[4]%ld--[5]%ld--[6]%ld--[7]%ld--[8]%ld--[9]%ld-----\n"
               ,"day_mode_cmp_awb",0x182,local_1c8[0],local_1c8[1],local_1c8[2],local_1c8[3],
               local_1c8[4],local_1b4,local_1b0,uStack_1ac,uStack_1a8,uStack_1a4);
      puVar6 = (uint *)0x3519c;
      puVar3 = local_1c8;
      iVar1 = 10;
      do {
        puVar6 = puVar6 + 1;
        if (*puVar6 < local_1c8[0]) {
          uVar7 = 1;
          pcVar5 = "day";
LAB_00015ba0:
          ak_print(10,4,"[%s:%d] awb_day_night=%s\n","day_mode_cmp_awb",0x191,pcVar5,local_1c8[1],
                   local_1c8[2],local_1c8[3],local_1c8[4],local_1b4,local_1b0,uStack_1ac,uStack_1a8,
                   uStack_1a4);
          return uVar7;
        }
        iVar1 = iVar1 + -1;
        if (iVar1 == 0) {
          pcVar5 = "night";
          uVar7 = 0;
          goto LAB_00015ba0;
        }
        puVar3 = puVar3 + 1;
        local_1c8[0] = *puVar3;
      } while( true );
    }
    uVar7 = 0x175;
  }
  else {
    uVar7 = 0x170;
  }
  ak_print(10,1,"[%s:%d]  get awb info failed \n","day_mode_cmp_awb",uVar7);
  return 0xffffffff;
}



undefined4 isp_open(int param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  char acStack_58 [64];
  
  if (param_1 < 2) {
    if (*(int *)(&DAT_000351e0 + param_1 * 4) == 1) {
      ak_print(10,4,"[%s:%d] dev:%d already opened!\n","isp_open",0x57,param_1);
      return 0;
    }
    iVar1 = isp_dev_open(param_1);
    if (iVar1 == 0) {
      ak_thread_mutex_init(param_1 * 0x18 + 0x351e8,0);
      *(undefined4 *)(&DAT_000351e0 + param_1 * 4) = 1;
      memset(acStack_58,0,0x40);
      memset(acStack_58,0,0x40);
      pcVar2 = ak_vpss_get_version();
      snprintf(acStack_58,0x40,"vpss_version=%s",pcVar2);
      ak_debug_info(10,1,acStack_58);
      memset(acStack_58,0,0x40);
      pcVar2 = (char *)AK_ISP_get_version();
      snprintf(acStack_58,0x40,"ispsdk_version=%s",pcVar2);
      ak_debug_info(10,1,acStack_58);
      uVar3 = 0;
    }
    else {
      ak_print(10,1,"[%s:%d] isp_dev_open dev %d failed!\n","isp_open",0x5e,param_1);
      uVar3 = 0xffffffff;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_open",0x51,param_1);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



undefined4 isp_close(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    if (*(int *)(&DAT_000351e0 + param_1 * 4) == 0) {
      ak_print(10,1,"[%s:%d] dev:%d is not opened!\n","isp_close",0x85,param_1);
      uVar1 = 0xffffffff;
    }
    else {
      isp_dev_close(param_1);
      ak_thread_mutex_destroy(param_1 * 0x18 + 0x351e8);
      isp_module_deinit(param_1);
      uVar1 = 0;
      *(undefined4 *)(&DAT_000351e0 + param_1 * 4) = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_close",0x7f,param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 isp_match_sensor_cfgfile(int param_1,char *param_2)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  size_t local_5c;
  char acStack_58 [64];
  
  local_5c = 0x32000;
  if (param_1 < 2) {
    if (param_2 == (char *)0x0) {
      ak_print(10,1,"[%s:%d] invalid argument\n","isp_match_sensor_cfgfile",0xa8);
      uVar3 = 0x100;
    }
    else {
      iVar1 = isp_open(param_1);
      if (iVar1 != 0) {
        ak_print(10,1,"[%s:%d] isp_open dev %d failed!\n","isp_match_sensor_cfgfile",0xaf,param_1);
        return 0x107;
      }
      uVar3 = ak_get_os_timestamp();
      pvVar2 = (void *)ak_mem_alloc_(10,0x32000,"isp_match_sensor_cfgfile",uVar3);
      if (pvVar2 == (void *)0x0) {
        isp_close(param_1);
        ak_print(10,1,"[%s:%d] calloc failed, size: %d\n","isp_match_sensor_cfgfile",0xb7,0x32000);
        uVar3 = 0x102;
      }
      else {
        isp_cfg_file_set_path(param_1,param_2);
        iVar1 = isp_cfg_file_load(param_1,0,pvVar2,&local_5c);
        if (iVar1 == 0) {
          iVar1 = isp_module_init(param_1,(int)pvVar2,local_5c);
          if (iVar1 == 0) {
            ak_mem_free(pvVar2);
            memset(acStack_58,0,0x40);
            memset(acStack_58,0,0x40);
            snprintf(acStack_58,0x40,"mode=%s",&DAT_00035094);
            ak_debug_info(10,1,acStack_58);
            uVar3 = 0;
          }
          else {
            isp_close(param_1);
            ak_mem_free(pvVar2);
            uVar3 = 0x108;
          }
        }
        else {
          isp_close(param_1);
          ak_mem_free(pvVar2);
          uVar3 = 0x10f;
        }
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_match_sensor_cfgfile",0xa2,param_1);
    uVar3 = 0x101;
  }
  return uVar3;
}



undefined4 isp_switch(int param_1,uint param_2)

{
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  char *param3;
  char *pcVar5;
  size_t local_64;
  char acStack_60 [64];
  
  local_64 = 0x32000;
  if (param_1 < 2) {
    if (4 < param_2) {
      ak_print(10,1,"[%s:%d] mode err:%d\n","isp_switch",0xfa,param_2);
      return 0x101;
    }
    uVar1 = ak_get_os_timestamp();
    pvVar2 = (void *)ak_mem_alloc_(10,0x32000,"isp_switch",uVar1);
    if (pvVar2 == (void *)0x0) {
      uVar1 = 0x102;
      ak_print(10,1,"[%s:%d] calloc cfg_data failed\n","isp_switch",0x102);
    }
    else {
      param3 = &DAT_00035094 + param_2 * 0x20;
      pcVar5 = param3;
      ak_print(10,4,"[%s:%d] switching isp mode -> %s\n","isp_switch",0x106,param3);
      iVar4 = param_1 * 0x18 + 0x351e8;
      ak_thread_mutex_lock(iVar4);
      iVar3 = isp_cfg_file_load(param_1,param_2,pvVar2,&local_64);
      if (iVar3 < 0) {
        ak_print(10,1,"[%s:%d] file load failed\n","isp_switch",0x10c,pcVar5);
        uVar1 = 0x10f;
      }
      else {
        iVar3 = isp_switch_mode(param_1,(int)pvVar2,local_64);
        if (iVar3 == 0) {
          DAT_00035218 = param_2;
          memset(acStack_60,0,0x40);
          memset(acStack_60,0,0x40);
          snprintf(acStack_60,0x40,"mode=%s",param3);
          ak_debug_info(10,1,acStack_60);
          uVar1 = 0;
        }
        else {
          ak_print(10,1,"[%s:%d] switch failed, ret: %d\n","isp_switch",0x114,0xffffffff);
          uVar1 = 0x10f;
        }
      }
      ak_thread_mutex_unlock(iVar4);
      ak_mem_free(pvVar2);
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_switch",0xf4,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 calc_cur_lumi(int param_1)

{
  int iVar1;
  undefined4 extraout_r0;
  uint uVar2;
  uint local_3c [10];
  
  local_3c[0] = 0;
  local_3c[1] = 0;
  local_3c[2] = 0;
  local_3c[3] = 0;
  local_3c[4] = 0;
  local_3c[5] = 0;
  local_3c[6] = 0;
  local_3c[7] = 0;
  local_3c[8] = 0;
  iVar1 = AK_ISP_get_ae_run_info(param_1,local_3c);
  if (iVar1 == 0) {
    uVar2 = local_3c[0] & 0xff;
    if (uVar2 == 0) {
      uVar2 = 0x28;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] get lum avg error\n","calc_cur_lumi",0x200);
    uVar2 = 0x28;
  }
  iVar1 = isp_get_cur_lum_factor(param_1);
  FUN_00021268(iVar1 * 0x28,uVar2);
  ak_print(10,5,"[%s:%d] cur_lum =%d, lum_avg = %d, res_lum=%d\n","calc_cur_lumi",0x20b,iVar1,uVar2,
           extraout_r0);
  return extraout_r0;
}



undefined4 save_soft_ir_info(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int local_fc;
  uint local_f8 [9];
  undefined1 auStack_d4 [116];
  undefined4 uStack_60;
  undefined4 local_5c [19];
  
  local_f8[0] = 0;
  local_f8[1] = 0;
  local_f8[2] = 0;
  local_f8[3] = 0;
  local_f8[4] = 0;
  local_f8[5] = 0;
  local_f8[6] = 0;
  local_f8[7] = 0;
  local_f8[8] = 0;
  iVar1 = AK_ISP_get_ae_run_info(param_1,local_f8);
  if (iVar1 == 0) {
    DAT_00035220 = local_f8[0] & 0xff;
    DAT_0003521c = isp_get_cur_lum_factor(param_1);
    DAT_00035224 = calc_cur_lumi(param_1);
    local_fc = iVar1;
    iVar1 = isp_get_statinfo(param_1,0x1b,(int)auStack_d4,&local_fc);
    if (iVar1 == 0) {
      puVar2 = &uStack_60;
      puVar3 = &DAT_00035224;
      do {
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
        *puVar3 = *puVar2;
      } while (puVar3 != (undefined4 *)&DAT_0003524c);
      ak_get_ostime(&DAT_00035258);
      uVar4 = 0;
    }
    else {
      ak_print(10,1,"[%s:%d]  get awb info failed \n","save_soft_ir_info",0x228);
      uVar4 = 0xffffffff;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] get lum avg error\n","save_soft_ir_info",0x21a);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}



undefined4 night_status_change(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int extraout_r0;
  int extraout_r0_00;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  bool bVar8;
  bool bVar9;
  int local_118;
  int local_114 [10];
  undefined1 auStack_ec [116];
  int iStack_78;
  int local_74 [9];
  int aiStack_50 [11];
  
  iVar2 = calc_cur_lumi(param_1);
  local_118 = 0;
  iVar3 = isp_get_statinfo(param_1,0x1b,(int)auStack_ec,&local_118);
  uVar1 = DAT_00035224;
  if (iVar3 == 0) {
    piVar6 = &local_118;
    piVar5 = &iStack_78;
    piVar7 = piVar6;
    do {
      piVar5 = piVar5 + 1;
      piVar7 = piVar7 + 1;
      *piVar7 = *piVar5;
    } while (piVar5 != aiStack_50);
    uVar4 = 0;
    if (DAT_00035224 != 0) {
      iVar2 = abs(iVar2 - DAT_00035224);
      FUN_00021268(iVar2 * 100,uVar1);
      if (0x1d < extraout_r0) {
        return 1;
      }
      piVar7 = (int *)&DAT_00035224;
      do {
        piVar7 = piVar7 + 1;
        iVar2 = *piVar7;
        piVar6 = piVar6 + 1;
        iVar3 = abs(*piVar6 - iVar2);
        FUN_00021268(iVar3 * 100,iVar2 + 1);
        bVar9 = SBORROW4(extraout_r0_00,0x1d);
        iVar2 = extraout_r0_00 + -0x1d;
        bVar8 = extraout_r0_00 == 0x1d;
        if (0x1d < extraout_r0_00) {
          bVar9 = SBORROW4(iVar3,10000);
          iVar2 = iVar3 + -10000;
          bVar8 = iVar3 == 10000;
        }
        if (!bVar8 && iVar2 < 0 == bVar9) {
          return 1;
        }
        uVar4 = 0;
      } while (piVar7 != (int *)&DAT_0003524c);
    }
  }
  else {
    ak_print(10,1,"[%s:%d]  get awb info failed \n","night_status_change",0x248);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}



undefined4 ak_vpss_get_ae_run_info(int param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_1 < 2) {
    if (param_2 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] ae_run_info is null\n","ak_vpss_get_ae_run_info",0x274);
      uVar1 = 0x100;
    }
    else {
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      local_28 = 0;
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      iVar2 = AK_ISP_get_ae_run_info(param_1,&local_34);
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get ae_run_info failed.\n","ak_vpss_get_ae_run_info",0x27d);
        return 0x109;
      }
      memcpy(param_2,&local_34,0x24);
      uVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_ae_run_info",0x26e,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_ae_init_info(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = param_2[1];
  local_c = param_2[3];
  local_18 = *param_2;
  local_10 = param_2[2];
  iVar1 = AK_ISP_set_ae_init_info(param_1,&local_18);
  uVar2 = 0;
  if (iVar1 != 0) {
    ak_print(10,1,"[%s:%d] set ae_init_info failed.\n","ak_vpss_set_ae_init_info",0x298);
    uVar2 = 0x109;
  }
  return uVar2;
}



undefined4 ak_vpss_get_sensor_ae_info(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  iVar1 = AK_ISP_get_sensor_ae_info(param_1,&local_18);
  if (iVar1 == 0) {
    *param_2 = local_18;
    param_2[1] = uStack_14;
    param_2[2] = uStack_10;
    param_2[3] = uStack_c;
    return 0;
  }
  ak_print(10,1,"[%s:%d] get sensor ae info failed.\n","ak_vpss_get_sensor_ae_info",0x2ac);
  return 0x109;
}



undefined4 ak_vpss_get_ae_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] ae_attr is NULL\n","ak_vpss_get_ae_attr",0x2c6);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_ae_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_ae_attr failed.\n","ak_vpss_get_ae_attr",0x2cd);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_ae_attr",0x2c0,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_ae_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] ae_attr is NULL\n","ak_vpss_set_ae_attr",0x2e4);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_ae_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_ae_attr failed.\n","ak_vpss_set_ae_attr",0x2ec);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_ae_attr",0x2de,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_ae_convergence_rate(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_100 [156];
  undefined4 local_64;
  
  if (param_1 < 2) {
    memset(auStack_100,0,0xf0);
    iVar2 = AK_ISP_get_ae_attr(param_1,auStack_100);
    if (iVar2 != 0) {
      ak_print(10,1,"[%s:%d] get ae fail\n","ak_vpss_set_ae_convergence_rate",0x306);
      return 0x109;
    }
    local_64 = param_2;
    iVar2 = AK_ISP_set_ae_attr(param_1,auStack_100);
    uVar1 = 0;
    if (iVar2 != 0) {
      ak_print(10,1,"[%s:%d] set ae fail\n","ak_vpss_set_ae_convergence_rate",0x30f);
      uVar1 = 0x109;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_ae_convergence_rate",0x2fd,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_ae_convergence_rate(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_100 [156];
  undefined4 local_64;
  
  if (param_1 < 2) {
    if (param_2 != (undefined4 *)0x0) {
      memset(auStack_100,0,0xf0);
      iVar2 = AK_ISP_get_ae_attr(param_1,auStack_100);
      if (iVar2 == 0) {
        *param_2 = local_64;
        return 0;
      }
      ak_print(10,1,"[%s:%d] get ae fail\n","ak_vpss_get_ae_convergence_rate",0x32f);
      return 0x109;
    }
    ak_print(10,1,"[%s:%d] value is NULL\n","ak_vpss_get_ae_convergence_rate",0x326);
    uVar1 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_ae_convergence_rate",800,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_check_ae_stable(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  uint local_12c;
  uint local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  undefined1 auStack_118 [36];
  int local_f4;
  int local_80;
  
  if (param_1 < 2) {
    if (param_2 != (undefined4 *)0x0) {
      memset(auStack_118,0,0xf0);
      local_13c = AK_ISP_get_ae_attr(param_1,auStack_118);
      if (local_13c == 0) {
        local_138 = local_13c;
        local_134 = local_13c;
        local_130 = local_13c;
        local_12c = local_13c;
        local_128 = local_13c;
        local_124 = local_13c;
        local_120 = local_13c;
        local_11c = local_13c;
        iVar1 = AK_ISP_get_ae_run_info(param_1,&local_13c);
        if (iVar1 != 0) {
          ak_print(10,1,"[%s:%d] get ae run info fail\n","ak_vpss_check_ae_stable",0x359);
          return 0x109;
        }
        uVar4 = local_13c >> 0x10 & 0xff;
        iVar1 = uVar4 + local_f4;
        if (local_80 == 0) {
          local_80 = 6;
        }
        uVar4 = uVar4 - local_f4;
        iVar6 = local_80 + iVar1;
        if (0xff < iVar1) {
          iVar1 = 0x100;
        }
        uVar5 = uVar4 & ~((int)uVar4 >> 0x1f);
        uVar4 = uVar4 - local_80 & ~((int)(uVar4 - local_80) >> 0x1f);
        if (0xff < iVar6) {
          iVar6 = 0x100;
        }
        iVar7 = iVar6;
        uVar8 = uVar4;
        ak_print(10,4,"[%s:%d] high_lock : %d low_lock :%d high_hold :%d low_hold :%d\n",
                 "ak_vpss_check_ae_stable",0x373,iVar1,uVar5,iVar6,uVar4);
        uVar3 = local_13c >> 8 & 0xff;
        if ((int)uVar3 < (int)uVar5 || iVar1 < (int)uVar3) {
          if ((*(int *)(&DAT_000351d8 + param_1 * 4) != 1) ||
             (((int)uVar3 <= iVar1 || iVar6 <= (int)uVar3 &&
              ((int)uVar5 <= (int)uVar3 || (int)uVar3 <= (int)uVar4)))) {
            *param_2 = 0;
            *(undefined4 *)(&DAT_000351d8 + param_1 * 4) = 0;
            ak_print(10,4,"[%s:%d] stable: %d  ae_lock :%d\n","ak_vpss_check_ae_stable",0x389,0,0,
                     iVar7,uVar8);
            return 0;
          }
          *param_2 = 1;
          ak_print(10,4,"[%s:%d] ae_lock_ stat stable: %d  ae_lock :%d\n","ak_vpss_check_ae_stable",
                   899,1,1,iVar7,uVar8);
          uVar2 = 0;
        }
        else {
          *param_2 = 1;
          *(undefined4 *)(&DAT_000351d8 + param_1 * 4) = 1;
          ak_print(10,4,"[%s:%d] stable: %d  ae_lock :%d\n","ak_vpss_check_ae_stable",0x37a,1,1,
                   iVar7,uVar8);
          uVar2 = 0;
        }
      }
      else {
        ak_print(10,1,"[%s:%d] get ae attr fail\n","ak_vpss_check_ae_stable",0x351);
        uVar2 = 0x109;
      }
      return uVar2;
    }
    ak_print(10,1,"[%s:%d] stable is NULL\n","ak_vpss_check_ae_stable");
    uVar2 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_check_ae_stable");
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 ak_vpss_get_me_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] me_attr is NULL\n","ak_vpss_get_me_attr",0x39f);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_me_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_me_attr failed.\n","ak_vpss_get_me_attr",0x3a6);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_me_attr",0x399,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_me_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] me_attr is NULL\n","ak_vpss_set_me_attr",0x3bd);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_me_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_me_attr failed.\n","ak_vpss_set_me_attr",0x3c4);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_me_attr",0x3b7,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_ae_suspend(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    iVar2 = Ak_ISP_Set_Ae_Suspend();
    uVar1 = 0;
    if (iVar2 != 0) {
      ak_print(10,1,"[%s:%d] Ak_ISP_Set_Ae_Suspend failed.\n","ak_vpss_set_ae_suspend",0x3dc);
      uVar1 = 0x109;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_ae_suspend",0x3d5,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_awb_stat_info(int param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_d4 [200];
  
  if (param_1 < 2) {
    if (param_2 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] awb_stat_info is null\n","ak_vpss_get_awb_stat_info",0x3f3);
      uVar1 = 0x100;
    }
    else {
      memset(auStack_d4,0,0xc4);
      iVar2 = Ak_ISP_get_awb_stat_info(param_1,auStack_d4);
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get awb_stat_info failed.\n","ak_vpss_get_awb_stat_info",0x3fc);
        return 0x109;
      }
      memcpy(param_2,auStack_d4,0xc4);
      uVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_awb_stat_info",0x3ed,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_cur_lumi(int param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == (int *)0x0) {
      ak_print(10,1,"[%s:%d] lumi is null\n","ak_vpss_get_cur_lumi",0x418);
      uVar1 = 0x100;
    }
    else {
      iVar2 = isp_get_cur_lum_factor(param_1);
      if (iVar2 < 0) {
        ak_print(10,1,"[%s:%d] get lumi failed.\n","ak_vpss_get_cur_lumi",0x420);
        uVar1 = 0x109;
      }
      else {
        uVar1 = 0;
        *param_2 = iVar2;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_cur_lumi",0x412,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_auto_day_night_param(int param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (param_1 < 2) {
    if (param_2 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] param is null!\n","ak_vpss_set_auto_day_night_param",0x439);
      uVar1 = 0x100;
    }
    else {
      if (DAT_00035260 != 0) {
        ak_print(10,1,
                 "[%s:%d] using ak_vpss_set_soft_ps_param function ,not support this function!\n",
                 "ak_vpss_set_auto_day_night_param",0x43f);
        return 0x104;
      }
      if (DAT_00035254 == 0) {
        memcpy(&DAT_00035184,param_2,0x54);
        DAT_000351cc = 0;
        uVar1 = DAT_000351c8;
        ak_print(10,4,"[%s:%d] (switch day_night) D_to_N=%d ,N_to_D=%d,lock_time=%d\n",
                 "set_auto_day_night_param",0x158,DAT_00035184,DAT_00035188,DAT_000351c8);
        puVar4 = &DAT_00035188;
        iVar3 = 0;
        do {
          puVar4 = puVar4 + 1;
          iVar2 = iVar3 + 1;
          ak_print(10,4,"[%s:%d] %d--%d\n","set_auto_day_night_param",0x15b,iVar3,*puVar4,uVar1);
          iVar3 = iVar2;
        } while (iVar2 != 5);
        puVar4 = (undefined4 *)0x3519c;
        iVar3 = 0;
        do {
          puVar4 = puVar4 + 1;
          iVar2 = iVar3 + 1;
          ak_print(10,4,"[%s:%d] %d--%d\n","set_auto_day_night_param",0x15e,iVar3,*puVar4,uVar1);
          iVar3 = iVar2;
        } while (iVar2 != 10);
        DAT_00035254 = 1;
        uVar1 = 0;
      }
      else {
        ak_print(10,2,"[%s:%d] auto_day_night param have set already\n",
                 "ak_vpss_set_auto_day_night_param",0x445);
        uVar1 = 0x105;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_auto_day_night_param",0x433,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_auto_day_night_level(int param_1,uint param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint local_38;
  int local_34;
  undefined1 auStack_30 [12];
  
  iVar3 = DAT_00035188;
  iVar6 = DAT_00035184;
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_auto_day_night_level",0x459,param_1);
    return 0x101;
  }
  if (param_3 == (uint *)0x0) {
    ak_print(10,1,"[%s:%d] new_level is null!\n","ak_vpss_get_auto_day_night_level",0x45f);
    return 0x100;
  }
  if (DAT_00035254 == 0) {
    ak_print(10,1,"[%s:%d] not init,set ak_vpss_set_auto_day_night_param first\n",
             "ak_vpss_get_auto_day_night_level",0x466);
    return 0x100;
  }
  if (1 < param_2) {
    ak_print(10,1,"[%s:%d] wrong input parameter\n","ak_vpss_get_auto_day_night_level",0x46c);
    return 0x101;
  }
  if (DAT_000351d0 == 0) {
    DAT_000351d0 = 500;
  }
  iVar2 = 0;
  if (DAT_000351d4 == 0) {
    DAT_000351d4 = 500;
  }
  iVar4 = 0;
  ak_sleep_ms(500);
  iVar5 = 0;
  do {
    iVar1 = isp_get_cur_lum_factor(param_1);
    if (iVar6 < iVar1) {
      iVar4 = iVar4 + 1;
    }
    else if (iVar1 < iVar3) {
      iVar5 = iVar5 + 1;
    }
    else {
      iVar2 = iVar2 + 1;
    }
    iVar1 = iVar5;
    if (iVar5 < 3) {
      iVar1 = iVar4;
    }
    iVar8 = iVar2 + iVar5 + iVar4;
    if (2 < iVar2 || 2 < iVar1) {
      iVar2 = 0;
      if (iVar8 == 3) break;
      ak_print(10,2,"[%s:%d] not stable\n","wait_move_stable",0x1e9);
      iVar4 = iVar2;
      iVar5 = iVar2;
    }
    ak_sleep_ms(500);
  } while( true );
  ak_print(10,5,"[%s:%d] lock time=%d, lock=%d\n","ak_vpss_get_auto_day_night_level",0x485,
           DAT_000351c8,DAT_00035250);
  if (param_2 == 0) {
    if (DAT_00035250 == 1) {
      ak_print(10,5,"[%s:%d] 1----lock= 0\n","ak_vpss_get_auto_day_night_level",0x48b);
      DAT_00035250 = 0;
    }
  }
  else if (DAT_00035250 == 1) {
    ak_get_ostime(auStack_30);
    iVar6 = ak_diff_ms_time(auStack_30,&DAT_00035258);
    if ((DAT_000351c8 < iVar6) || (iVar3 = night_status_change(param_1), iVar3 == 1)) {
      ak_print(10,5,"[%s:%d] 2----lock= 0, diff_time=%ld\n","ak_vpss_get_auto_day_night_level",0x497
               ,iVar6);
      DAT_00035250 = 0;
    }
    local_34 = 0;
    uVar7 = 1;
    iVar6 = local_34;
    goto LAB_000178dc;
  }
  iVar6 = 0;
  iVar3 = 3;
  local_34 = 0;
  local_38 = param_2;
  do {
    iVar2 = calc_cur_lumi(param_1);
    if (param_2 == 0) {
      ak_print(10,5,"[%s:%d]  pre lum=%s--cur_lum=%d\n","ak_vpss_get_auto_day_night_level",0x4a1,
               &DAT_00022b78,iVar2);
      if ((DAT_00035184 < iVar2) && (iVar2 = FUN_00015a84(param_1), iVar2 == 0)) {
        iVar6 = iVar6 + 1;
        local_38 = 1;
      }
      ak_sleep_ms(DAT_000351d0);
    }
    else {
      ak_print(10,5,"[%s:%d]  pre lum=%s--cur_lum=%d\n","ak_vpss_get_auto_day_night_level",0x4a1,
               "night",iVar2);
      if ((iVar2 < DAT_00035188) && (iVar2 = FUN_000158f0(param_1), iVar2 == 1)) {
        local_34 = local_34 + 1;
        local_38 = 0;
      }
      ak_sleep_ms(DAT_000351d4);
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar7 = param_2;
  if ((1 < local_34 - 1U) && (1 < iVar6 - 1U)) {
    if (((local_38 ^ 1) & param_2) == 0) {
      uVar7 = local_38;
      if (local_38 == 0 && param_2 == 0) {
        memset(&DAT_00035258,0,8);
        ak_print(10,5,"[%s:%d] 4----lock= 0\n","ak_vpss_get_auto_day_night_level",0x4d8);
        DAT_00035250 = 2;
        uVar7 = 0;
      }
    }
    else {
      ak_get_ostime(auStack_30);
      iVar3 = ak_diff_ms_time(auStack_30,&DAT_00035258);
      save_soft_ir_info(param_1);
      if (iVar3 < 15000) {
        DAT_00035250 = 1;
        uVar7 = 1;
      }
      else {
        ak_print(10,5,"[%s:%d] 3----lock= 0\n","ak_vpss_get_auto_day_night_level",0x4d1);
        DAT_00035250 = 0;
        uVar7 = 0;
      }
    }
  }
LAB_000178dc:
  *param_3 = uVar7;
  ak_print(10,5,"[%s:%d] (switch day_night) end check-daycount=%d,nightcount=%d \n\n",
           "ak_vpss_get_auto_day_night_level",0x4e1,local_34,iVar6);
  return 0;
}



undefined4 ak_vpss_set_force_anti_flicker_flag(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    iVar2 = isp_set_force_anti_flicker_flag(param_1,param_2,-1);
    uVar1 = 0;
    if (iVar2 != 0) {
      ak_print(10,1,"[%s:%d] set force_flag failed.\n","ak_vpss_set_force_anti_flicker_flag",0x4f6);
      uVar1 = 0x109;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_force_anti_flicker_flag",0x4f0,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_force_anti_flicker_flag(int param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_c;
  
  if (param_1 < 2) {
    if (param_2 == (uint *)0x0) {
      ak_print(10,1,"[%s:%d] force_flag is null\n","ak_vpss_get_force_anti_flicker_flag",0x50d);
      uVar1 = 0x100;
    }
    else {
      local_c = 0;
      iVar2 = isp_get_force_anti_flicker_flag(param_1,param_2,&local_c);
      if (iVar2 < 0) {
        ak_print(10,1,"[%s:%d] get force_flag failed.\n","ak_vpss_get_force_anti_flicker_flag",0x518
                );
        uVar1 = 0x109;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_force_anti_flicker_flag",0x507,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_force_anti_flicker_flag_ex(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_3 < 1) {
      ak_print(10,1,"[%s:%d] sub_antiflicker_value:%d error!\n",
               "ak_vpss_set_force_anti_flicker_flag_ex",0x531,param_3);
      return 0x101;
    }
    iVar2 = isp_set_force_anti_flicker_flag(param_1,param_2,param_3);
    uVar1 = 0;
    if (iVar2 != 0) {
      ak_print(10,1,"[%s:%d] set force_flag failed.\n","ak_vpss_set_force_anti_flicker_flag_ex",
               0x537);
      uVar1 = 0x109;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_force_anti_flicker_flag_ex",0x52b,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_force_anti_flicker_flag_ex(int param_1,uint *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == (uint *)0x0) {
      ak_print(10,1,"[%s:%d] force_flag is null\n","ak_vpss_get_force_anti_flicker_flag_ex",0x54f);
      uVar1 = 0x100;
    }
    else {
      iVar2 = isp_get_force_anti_flicker_flag(param_1,param_2,param_3);
      if (iVar2 < 0) {
        ak_print(10,1,"[%s:%d] get force_flag failed.\n","ak_vpss_get_force_anti_flicker_flag_ex",
                 0x559);
        uVar1 = 0x109;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_force_anti_flicker_flag_ex",0x549,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_open_wdr(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  undefined *puVar7;
  size_t sStack_64;
  char acStack_60 [64];
  
  if (param_1 < 2) {
    if (1 < DAT_00035218) {
      uVar4 = (uint)(DAT_00035218 != 2);
      sStack_64 = 0x32000;
      if (param_1 < 2) {
        if (4 < uVar4) {
          ak_print(10,1,"[%s:%d] mode err:%d\n","isp_switch",0xfa,uVar4);
          return 0x101;
        }
        uVar3 = ak_get_os_timestamp();
        pvVar1 = (void *)ak_mem_alloc_(10,0x32000,"isp_switch",uVar3);
        if (pvVar1 == (void *)0x0) {
          uVar3 = 0x102;
          ak_print(10,1,"[%s:%d] calloc cfg_data failed\n","isp_switch",0x102);
        }
        else {
          puVar6 = &DAT_00035094 + uVar4 * 0x20;
          puVar7 = puVar6;
          ak_print(10,4,"[%s:%d] switching isp mode -> %s\n","isp_switch",0x106,puVar6);
          iVar5 = param_1 * 0x18 + 0x351e8;
          ak_thread_mutex_lock(iVar5);
          iVar2 = isp_cfg_file_load(param_1,uVar4,pvVar1,&sStack_64);
          if (iVar2 < 0) {
            ak_print(10,1,"[%s:%d] file load failed\n","isp_switch",0x10c,puVar7);
            uVar3 = 0x10f;
          }
          else {
            iVar2 = isp_switch_mode(param_1,(int)pvVar1,sStack_64);
            if (iVar2 == 0) {
              DAT_00035218 = uVar4;
              memset(acStack_60,0,0x40);
              memset(acStack_60,0,0x40);
              snprintf(acStack_60,0x40,"mode=%s",puVar6);
              ak_debug_info(10,1,acStack_60,ak_debug_info);
              uVar3 = 0;
            }
            else {
              ak_print(10,1,"[%s:%d] switch failed, ret: %d\n","isp_switch",0x114,0xffffffff);
              uVar3 = 0x10f;
            }
          }
          ak_thread_mutex_unlock(iVar5);
          ak_mem_free(pvVar1);
        }
      }
      else {
        ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_switch",0xf4,param_1);
        uVar3 = 0x101;
      }
      return uVar3;
    }
    ak_print(10,4,"[%s:%d] wdr is already opened!\n","ak_vpss_open_wdr");
    uVar3 = 0;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_open_wdr");
    uVar3 = 0x101;
  }
  return uVar3;
}



undefined4 ak_vpss_close_wdr(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  undefined *puVar7;
  size_t sStack_64;
  char acStack_60 [64];
  
  if (param_1 < 2) {
    if (1 < DAT_00035218 - 2) {
      if (DAT_00035218 == 0) {
        uVar4 = 2;
      }
      else {
        uVar4 = 3;
      }
      sStack_64 = 0x32000;
      if (param_1 < 2) {
        if (4 < uVar4) {
          ak_print(10,1,"[%s:%d] mode err:%d\n","isp_switch",0xfa,uVar4);
          return 0x101;
        }
        uVar3 = ak_get_os_timestamp();
        pvVar1 = (void *)ak_mem_alloc_(10,0x32000,"isp_switch",uVar3);
        if (pvVar1 == (void *)0x0) {
          uVar3 = 0x102;
          ak_print(10,1,"[%s:%d] calloc cfg_data failed\n","isp_switch",0x102);
        }
        else {
          puVar6 = &DAT_00035094 + uVar4 * 0x20;
          puVar7 = puVar6;
          ak_print(10,4,"[%s:%d] switching isp mode -> %s\n","isp_switch",0x106,puVar6);
          iVar5 = param_1 * 0x18 + 0x351e8;
          ak_thread_mutex_lock(iVar5);
          iVar2 = isp_cfg_file_load(param_1,uVar4,pvVar1,&sStack_64);
          if (iVar2 < 0) {
            ak_print(10,1,"[%s:%d] file load failed\n","isp_switch",0x10c,puVar7);
            uVar3 = 0x10f;
          }
          else {
            iVar2 = isp_switch_mode(param_1,(int)pvVar1,sStack_64);
            if (iVar2 == 0) {
              DAT_00035218 = uVar4;
              memset(acStack_60,0,0x40);
              memset(acStack_60,0,0x40);
              snprintf(acStack_60,0x40,"mode=%s",puVar6);
              ak_debug_info(10,1,acStack_60,ak_debug_info);
              uVar3 = 0;
            }
            else {
              ak_print(10,1,"[%s:%d] switch failed, ret: %d\n","isp_switch",0x114,0xffffffff);
              uVar3 = 0x10f;
            }
          }
          ak_thread_mutex_unlock(iVar5);
          ak_mem_free(pvVar1);
        }
      }
      else {
        ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_switch",0xf4,param_1);
        uVar3 = 0x101;
      }
      return uVar3;
    }
    ak_print(10,4,"[%s:%d] wdr is already closed!\n","ak_vpss_close_wdr");
    uVar3 = 0;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_close_wdr");
    uVar3 = 0x101;
  }
  return uVar3;
}



undefined4 ak_vpss_get_wdr_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] p_wdr is null\n","ak_vpss_get_wdr_attr",0x5b8);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_wdr_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get wdr attr failed.\n","ak_vpss_get_wdr_attr",0x5c0);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_wdr_attr",0x5b2,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_weight_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] weight_attr is NULL\n","ak_vpss_get_weight_attr",0x5d7);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_weight_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_weight_attr failed.\n","ak_vpss_get_weight_attr",0x5de);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_weight_attr",0x5d1,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_weight_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] weight_attr is NULL\n","ak_vpss_set_weight_attr",0x5f5);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_weight_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_weight_attr failed.\n","ak_vpss_set_weight_attr",0x5fc);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_weight_attr",0x5ef,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4
ak_vpss_get_rgb_average(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  undefined4 extraout_r0_01;
  undefined4 uVar2;
  undefined1 auStack_dc [36];
  uint local_b8;
  uint local_90;
  uint local_68;
  uint local_40;
  
  if (param_1 < 2) {
    if (param_2 == (undefined4 *)0x0 ||
        (param_4 == (undefined4 *)0x0 || param_3 == (undefined4 *)0x0)) {
      ak_print(10,1,"[%s:%d] param is NULL\n","ak_vpss_get_rgb_average",0x616);
      return 0x100;
    }
    memset(auStack_dc,0,0xc4);
    iVar1 = Ak_ISP_get_awb_stat_info(param_1,auStack_dc);
    if (iVar1 == 0) {
      if (local_40 == 0) {
        *param_2 = 0;
        *param_3 = 0;
        *param_4 = 0;
        uVar2 = 0;
      }
      else {
        FUN_000211a0(local_b8,local_40);
        *param_2 = extraout_r0;
        FUN_000211a0(local_90,local_40);
        *param_3 = extraout_r0_00;
        FUN_000211a0(local_68,local_40);
        *param_4 = extraout_r0_01;
        uVar2 = 0;
      }
    }
    else {
      ak_print(10,1,"[%s:%d] Ak_ISP_get_awb_stat_info failed.\n","ak_vpss_get_rgb_average",0x61f);
      uVar2 = 0x109;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_rgb_average",0x610,param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 ak_vpss_get_wb_type(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] wb_type is NULL\n","ak_vpss_get_wb_type",0x643);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_wb_type();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_wb_type failed.\n","ak_vpss_get_wb_type",0x64a);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_wb_type",0x63d,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_wb_type(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] wb_type is NULL\n","ak_vpss_set_wb_type",0x661);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_wb_type();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_wb_type failed.\n","ak_vpss_set_wb_type",0x668);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_wb_type",0x65b,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_3d_nr_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] 3d_nr_attr is NULL\n","ak_vpss_get_3d_nr_attr",0x67f);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_3d_nr_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_3d_nr_attr failed.\n","ak_vpss_get_3d_nr_attr",0x686);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_3d_nr_attr",0x679,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_3d_nr_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] 3d_nr_attr is NULL\n","ak_vpss_set_3d_nr_attr",0x69d);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_3d_nr_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_3d_nr_attr failed.\n","ak_vpss_set_3d_nr_attr",0x6a4);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_3d_nr_attr",0x697,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_mwb_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] mwb_attr is NULL\n","ak_vpss_get_mwb_attr",0x6bb);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_mwb_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_mwb_attr failed.\n","ak_vpss_get_mwb_attr",0x6c2);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_mwb_attr",0x6b5,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_mwb_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] mwb_attr is NULL\n","ak_vpss_set_mwb_attr",0x6d9);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_mwb_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_mwb_attr failed.\n","ak_vpss_set_mwb_attr",0x6e1);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_mwb_attr",0x6d3,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_awb_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] awb_attr is NULL\n","ak_vpss_get_awb_attr",0x6f8);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_awb_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_awb_attr failed.\n","ak_vpss_get_awb_attr",0x6ff);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_awb_attr",0x6f2,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_awb_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] awb_attr is NULL\n","ak_vpss_set_awb_attr",0x716);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_awb_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_awb_attr failed.\n","ak_vpss_set_awb_attr",0x71d);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_awb_attr",0x710,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_exp_type(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] exp_type is NULL\n","ak_vpss_get_exp_type",0x734);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_exp_type();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_exp_type failed.\n","ak_vpss_get_exp_type",0x73b);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_exp_type",0x72e,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_awb_stable(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] exp_type is NULL\n","ak_vpss_get_awb_stable",0x752);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_awb_stable();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_exp_type failed.\n","ak_vpss_get_awb_stable",0x758);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_awb_stable",0x74c,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_exp_type(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] exp_type is NULL\n","ak_vpss_set_exp_type",0x771);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_exp_type();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_exp_type failed.\n","ak_vpss_set_exp_type",0x778);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_exp_type",0x76b,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_sensor_reg(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] ae_run_info is NULL\n","ak_vpss_get_sensor_reg",0x78f);
      uVar1 = 0x100;
    }
    else {
      iVar2 = Ak_ISP_Sensor_Get_Reg();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] Ak_ISP_Sensor_Get_Reg failed.\n","ak_vpss_get_sensor_reg",0x796);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_sensor_reg",0x789,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_lsc_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] lsc is NULL\n","ak_vpss_get_lsc_attr",0x7ad);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_lsc_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_lsc_attr failed.\n","ak_vpss_get_lsc_attr",0x7b4);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_lsc_attr",0x7a7,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_set_lsc_attr(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_lsc_attr",0x7c5,param_1);
    return 0x101;
  }
  if (param_2 == 0) {
    ak_print(10,1,"[%s:%d] lsc is NULL\n","ak_vpss_set_lsc_attr",0x7cb);
    uVar2 = 0x100;
  }
  else {
    iVar1 = AK_ISP_set_lsc_attr();
    uVar2 = 0;
    if (iVar1 != 0) {
      ak_print(10,1,"[%s:%d] AK_ISP_set_lsc_attr failed.\n","ak_vpss_set_lsc_attr",0x7d2);
      return 0x109;
    }
  }
  return uVar2;
}



// WARNING: Type propagation algorithm not settling

undefined4 ak_vpss_wait_exp_stable(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint extraout_r0;
  int extraout_r0_00;
  int iVar2;
  int extraout_r0_01;
  int extraout_r0_02;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint local_154;
  uint local_150;
  uint local_144;
  int local_140 [11];
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_108;
  uint local_104;
  uint local_100;
  uint local_fc;
  uint local_f8;
  
  local_144 = 0;
  local_140[1] = 0;
  local_140[2] = 0;
  local_140[3] = 0;
  local_140[4] = 0;
  local_140[5] = 0;
  local_140[6] = 0;
  local_140[7] = 0;
  local_140[8] = 0;
  local_140[9] = 0;
  memset(local_140 + 10,0,0xf0);
  local_140[0] = 0;
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] exp_stable_check_frame_num is error %u\n","ak_vpss_wait_exp_stable",
               0x7f0,0);
      return 0x100;
    }
    ak_vpss_get_sensor_fps(param_1,(int *)&local_144);
    FUN_00021268(1000,local_144);
    FUN_000211a0(param_3,extraout_r0);
    ak_vpss_check_ae_stable(param_1,local_140);
    iVar5 = extraout_r0_00 + 1;
    while ((local_140[0] == 0 && (iVar3 = iVar5 + -1, 0 < iVar5))) {
      iVar2 = ak_vpss_get_ae_run_info(param_1,local_140 + 1);
      if (iVar2 != 0) {
        uVar4 = 0x800;
LAB_000193ec:
        ak_print(10,1,"[%s:%d] can not get ae run info!\n","ak_vpss_wait_exp_stable",uVar4);
        return 0x109;
      }
      ak_vpss_check_ae_stable(param_1,local_140);
      if (local_140[0] != 0) {
        ak_print(10,5,"[%s:%d] is_stable!\n","ak_vpss_wait_exp_stable",0x808);
        return 0;
      }
      iVar2 = ak_vpss_get_ae_attr(param_1,(int)(local_140 + 10));
      if (iVar2 != 0) {
        uVar4 = 0x810;
LAB_00019410:
        ak_print(10,1,"[%s:%d] can not get ae attr!\n","ak_vpss_wait_exp_stable",uVar4);
        return 0x109;
      }
      uVar6 = local_140[5];
      uVar7 = local_140[10];
      uVar8 = local_f8;
      ak_print(10,6,"[%s:%d] 0 current_exp_time:%d, exp_time_max:%d, step:%d!\n",
               "ak_vpss_wait_exp_stable",0x815,local_140[5],local_140[10],local_f8);
      uVar1 = local_f8;
      iVar2 = local_140[5];
      if ((((local_114 < (uint)local_140[5]) &&
           (FUN_000211a0(local_140[10],local_f8), (uint)iVar2 < uVar1 * extraout_r0_01)) &&
          (local_fc < (uint)local_140[2])) &&
         ((((uint)local_140[2] < local_100 && (local_10c < (uint)local_140[3])) &&
          (((uint)local_140[3] < local_110 &&
           ((local_108 < (uint)local_140[4] && ((uint)local_140[4] < local_104)))))))) {
        ak_print(10,4,"[%s:%d] 0 exp is not stable!\n","ak_vpss_wait_exp_stable",0x820,uVar6,uVar7,
                 uVar8);
        ak_sleep_ms(extraout_r0);
        iVar5 = iVar3;
      }
      else {
        local_150 = 0;
        iVar5 = ~param_2 + iVar5;
        local_154 = 0;
        do {
          iVar2 = ak_vpss_get_ae_run_info(param_1,local_140 + 1);
          if (iVar2 != 0) {
            uVar4 = 0x832;
            goto LAB_000193ec;
          }
          iVar2 = ak_vpss_get_ae_attr(param_1,(int)(local_140 + 10));
          if (iVar2 != 0) {
            uVar4 = 0x83a;
            goto LAB_00019410;
          }
          uVar6 = local_140[5];
          uVar7 = local_140[10];
          uVar8 = local_f8;
          ak_print(10,6,"[%s:%d] 1 current_exp_time:%d, exp_time_max:%d, step:%d!\n",
                   "ak_vpss_wait_exp_stable",0x83f,local_140[5],local_140[10],local_f8);
          uVar1 = local_f8;
          FUN_000211a0(local_140[10],local_f8);
          if ((((local_140[5] == uVar1 * extraout_r0_02) && (local_140[2] == local_100)) &&
              (local_140[3] == local_110)) && (local_140[4] == local_104)) {
            local_154 = local_154 + 1;
            uVar6 = local_154;
            ak_print(10,5,"[%s:%d] cnt_max : %d!\n","ak_vpss_wait_exp_stable",0x847,local_154);
          }
          else if (((local_140[5] == local_114) && (local_140[2] == local_fc)) &&
                  ((local_140[3] == local_10c && (local_140[4] == local_108)))) {
            local_150 = local_150 + 1;
            uVar6 = local_150;
            ak_print(10,5,"[%s:%d] cnt_min : %d!\n","ak_vpss_wait_exp_stable",0x84f,local_150,uVar7,
                     uVar8);
          }
          iVar3 = iVar3 + -1;
          ak_sleep_ms(extraout_r0);
        } while (iVar3 != iVar5);
        if (local_154 == param_2 || local_150 == param_2) {
          ak_print(10,5,"[%s:%d] is_stable! cnt_max : %d, cnt_min : %d\n","ak_vpss_wait_exp_stable",
                   0x858,local_154,local_150,uVar8);
          return 0;
        }
        ak_print(10,4,"[%s:%d] 1 exp is not stable!\n","ak_vpss_wait_exp_stable",0x85d,uVar6,uVar7,
                 uVar8);
        ak_sleep_ms(extraout_r0);
      }
    }
    ak_print(10,4,"[%s:%d] is_stable!\n","ak_vpss_wait_exp_stable",0x863);
    uVar4 = 0;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_wait_exp_stable",0x7ea,param_1);
    uVar4 = 0x101;
  }
  return uVar4;
}



undefined4 ak_vpss_set_soft_ps_param(uint param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (DAT_00035254 == 0) {
    if (param_1 < 2) {
      if (param_2 == (int *)0x0) {
        ak_print(10,1,"[%s:%d] param is NULL\n","ak_vpss_set_soft_ps_param",0x914);
        uVar1 = 0x100;
      }
      else if (*param_2 == 0) {
        ak_print(10,1,"[%s:%d] day_to_night_lum is 0\n","ak_vpss_set_soft_ps_param",0x91a);
        uVar1 = 0x101;
      }
      else if (param_2[1] == 0) {
        ak_print(10,1,"[%s:%d] night_to_day_lum is 0\n","ak_vpss_set_soft_ps_param",0x920);
        uVar1 = 0x101;
      }
      else if (param_2[3] == 0) {
        ak_print(10,1,"[%s:%d] awb_night_dis_max is 0\n","ak_vpss_set_soft_ps_param",0x926);
        uVar1 = 0x101;
      }
      else if (param_2[4] == 0) {
        ak_print(10,1,"[%s:%d] day_check_frame_num is 0\n","ak_vpss_set_soft_ps_param",0x92c);
        uVar1 = 0x101;
      }
      else if (param_2[5] == 0) {
        ak_print(10,1,"[%s:%d] night_check_frame_num is 0\n","ak_vpss_set_soft_ps_param",0x932);
        uVar1 = 0x101;
      }
      else if (param_2[6] == 0) {
        ak_print(10,1,"[%s:%d] exp_stable_check_frame_num is 0\n","ak_vpss_set_soft_ps_param",0x938)
        ;
        uVar1 = 0x101;
      }
      else if (param_2[8] == 0) {
        ak_print(10,1,"[%s:%d] gain_r is 0\n","ak_vpss_set_soft_ps_param",0x93e);
        uVar1 = 0x101;
      }
      else if (param_2[10] == 0) {
        ak_print(10,1,"[%s:%d] gain_b is 0\n","ak_vpss_set_soft_ps_param",0x944);
        uVar1 = 0x101;
      }
      else {
        memcpy(&DAT_00035264,param_2,0x30);
        DAT_00035260 = 1;
        uVar1 = 0;
      }
    }
    else {
      ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_soft_ps_param",0x90e,param_1);
      uVar1 = 0x101;
    }
    return uVar1;
  }
  ak_print(10,1,
           "[%s:%d] using ak_vpss_set_auto_day_night_param function ,not support this function!\n",
           "ak_vpss_set_soft_ps_param",0x908);
  return 0x104;
}



undefined4 ak_vpss_get_ev(uint param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint local_12c;
  uint local_128;
  int local_124;
  uint local_120;
  int local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined1 auStack_108 [20];
  uint local_f4;
  uint local_f0;
  
  local_12c = 0;
  local_128 = 0;
  local_124 = 0;
  local_120 = 0;
  local_11c = 0;
  local_118 = 0;
  local_114 = 0;
  local_110 = 0;
  local_10c = 0;
  memset(auStack_108,0,0xf0);
  if (param_1 < 2) {
    if (param_2 == (int *)0x0) {
      ak_print(10,1,"[%s:%d] ev is NULL\n","ak_vpss_get_ev",0x9ac);
      uVar1 = 0x100;
    }
    else {
      iVar2 = ak_vpss_get_ae_run_info(param_1,&local_12c);
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] can not get ae run info!\n","ak_vpss_get_ev",0x9b7);
        return 0x109;
      }
      *param_2 = local_11c * ((int)(local_120 * ((int)(local_128 * local_124) >> 8)) >> 8);
      ak_vpss_get_ae_attr(param_1,(int)auStack_108);
      if ((local_120 < local_f4) || (local_128 < local_f0)) {
        iVar2 = *param_2;
      }
      else {
        uVar3 = local_12c >> 0x10 & 0xff;
        uVar4 = local_12c >> 8 & 0xff;
        iVar2 = abs(uVar4 - uVar3);
        ak_print(10,5,"[%s:%d] try fix env ,compensation_lumi = %d,target_lumi= %d !\n",
                 "ak_vpss_get_ev",0x9c7,uVar4,uVar3);
        iVar2 = *param_2 + (uint)(*param_2 * iVar2) / 100;
        *param_2 = iVar2;
      }
      ak_print(10,4,"[%s:%d] EV : %d!\n","ak_vpss_get_ev",0x9cb,iVar2);
      uVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_ev",0x9a6,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



int day_mode_check(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 extraout_r0;
  uint uVar2;
  uint uVar3;
  uint local_30;
  uint local_2c [2];
  
  uVar2 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (param_1 < 2) {
    if (param_2 == (undefined4 *)0x0) {
      ak_print(10,1,"[%s:%d] new_ir_level is NULL\n","day_mode_check",0x87e);
      iVar1 = 0x100;
    }
    else {
      ak_vpss_get_sensor_fps(param_1,(int *)local_2c);
      FUN_00021268(1000,local_2c[0]);
      if (DAT_00035274 != 0) {
        uVar3 = 0;
        do {
          iVar1 = ak_vpss_get_ev(param_1,(int *)&local_30);
          uVar2 = uVar2 + 1;
          if (iVar1 != 0) {
            ak_print(10,1,"[%s:%d] can not get ev!\n","day_mode_check",0x88c);
            return iVar1;
          }
          ak_print(10,5,"[%s:%d] EV : %d!\n","day_mode_check",0x890,local_30);
          if (DAT_00035264 < local_30) {
            uVar3 = uVar3 + 1;
            ak_print(10,5,"[%s:%d] night_cnt : %d!\n","day_mode_check",0x898,uVar3);
          }
          ak_sleep_ms(extraout_r0);
        } while (uVar2 < DAT_00035274);
        if (uVar3 != DAT_00035274) {
          *param_2 = 0;
          return 0;
        }
      }
      *param_2 = 1;
      iVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","day_mode_check",0x878,param_1);
    iVar1 = 0x101;
  }
  return iVar1;
}



undefined4
ak_vpss_get_rgb_dis(uint param_1,uint param_2,int param_3,uint param_4,int param_5,uint *param_6)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  uint local_108;
  uint uStack_104;
  uint local_100;
  uint uStack_fc;
  undefined8 local_f8;
  undefined1 auStack_ec [36];
  uint local_c8;
  uint local_a0;
  uint local_78;
  uint local_50;
  
  memset(auStack_ec,0,0xc4);
  if (param_1 < 2) {
    if (param_6 == (uint *)0x0) {
      ak_print(10,1,"[%s:%d] dis is NULL\n","ak_vpss_get_rgb_dis",0x9ea);
      uVar2 = 0x100;
    }
    else {
      if (param_2 == 0) {
        ak_print(10,1,"[%s:%d] gain_r is 0\n","ak_vpss_get_rgb_dis",0x9f0);
        return 0x101;
      }
      if (param_4 == 0) {
        ak_print(10,1,"[%s:%d] gain_b is 0\n","ak_vpss_get_rgb_dis",0x9f6);
        uVar2 = 0x101;
      }
      else {
        iVar3 = ak_vpss_get_awb_stat_info(param_1,auStack_ec);
        if (iVar3 == 0) {
          uVar6 = FUN_0002161c(local_50);
          uVar5 = (uint)(uVar6 >> 0x20);
          uVar4 = (uint)uVar6;
          uVar6 = FUN_0002161c(local_a0);
          uVar6 = FUN_00021988((int)uVar6,(uint)(uVar6 >> 0x20),uVar4,uVar5);
          uVar7 = FUN_0002161c(param_2);
          uVar8 = FUN_0002161c(local_c8);
          uVar8 = FUN_00021988((int)uVar8,(uint)(uVar8 >> 0x20),uVar4,uVar5);
          uVar7 = FUN_0002171c((int)uVar7,(uint)(uVar7 >> 0x20),(uint)uVar8,(uint)(uVar8 >> 0x20));
          uVar7 = FUN_0002171c((int)uVar7,(uint)(uVar7 >> 0x20),0,0x3f500000);
          if (param_3 < 0) {
            param_3 = param_3 + 0x3ff;
          }
          uVar8 = FUN_00021640(param_3 >> 10);
          uVar7 = FUN_00021370((uint)uVar7,(uint)(uVar7 >> 0x20),(uint)uVar8,(uint)(uVar8 >> 0x20));
          uVar8 = FUN_0002161c(param_4);
          uVar9 = FUN_0002161c(local_78);
          uVar9 = FUN_00021988((int)uVar9,(uint)(uVar9 >> 0x20),uVar4,uVar5);
          uVar8 = FUN_0002171c((int)uVar8,(uint)(uVar8 >> 0x20),(uint)uVar9,(uint)(uVar9 >> 0x20));
          uVar8 = FUN_0002171c((int)uVar8,(uint)(uVar8 >> 0x20),0,0x3f500000);
          if (param_5 < 0) {
            param_5 = param_5 + 0x3ff;
          }
          uVar9 = FUN_00021640(param_5 >> 10);
          uVar8 = FUN_00021370((uint)uVar8,(uint)(uVar8 >> 0x20),(uint)uVar9,(uint)(uVar9 >> 0x20));
          uVar5 = (uint)(uVar8 >> 0x20);
          uVar4 = (uint)uVar8;
          local_100 = (uint)uVar7;
          uStack_fc = (uint)(uVar7 >> 0x20);
          bVar1 = FUN_00021c90(local_100,uStack_fc,uVar4,uVar5);
          if (bVar1) {
            local_f8 = FUN_0002136c(local_100,uStack_fc,uVar4,uVar5);
          }
          else {
            local_f8 = FUN_0002136c(uVar4,uVar5,local_100,uStack_fc);
          }
          local_108 = (uint)uVar6;
          uStack_104 = (uint)(uVar6 >> 0x20);
          bVar1 = FUN_00021c7c(local_108,uStack_104,local_100,uStack_fc);
          if (bVar1) {
            uVar6 = FUN_0002136c(local_100,uStack_fc,local_108,uStack_104);
          }
          else {
            uVar6 = FUN_0002136c(local_108,uStack_104,local_100,uStack_fc);
          }
          bVar1 = FUN_00021c7c(local_108,uStack_104,uVar4,uVar5);
          if (bVar1) {
            uVar7 = FUN_0002136c(uVar4,uVar5,local_108,uStack_104);
          }
          else {
            uVar7 = FUN_0002136c(local_108,uStack_104,uVar4,uVar5);
          }
          uVar6 = FUN_00021370((uint)local_f8,local_f8._4_4_,(uint)uVar6,(uint)(uVar6 >> 0x20));
          uVar6 = FUN_00021370((uint)uVar6,(uint)(uVar6 >> 0x20),(uint)uVar7,(uint)(uVar7 >> 0x20));
          uVar6 = FUN_00021370((uint)uVar6,(uint)(uVar6 >> 0x20),0,0x3fe00000);
          uVar6 = FUN_0002171c((int)uVar6,(uint)(uVar6 >> 0x20),0,0x40590000);
          uVar4 = FUN_00021cb8((uint)uVar6,(uint)(uVar6 >> 0x20));
          *param_6 = uVar4;
          ak_print(10,4,"[%s:%d] dis : %d!\n","ak_vpss_get_rgb_dis",0xa30,uVar4);
          uVar2 = 0;
        }
        else {
          ak_print(10,1,"[%s:%d] can not get awb stat info!\n","ak_vpss_get_rgb_dis",0xa01);
          uVar2 = 0x109;
        }
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_rgb_dis",0x9e4,param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}



int night_mode_check(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 extraout_r0;
  uint uVar2;
  uint uVar3;
  uint local_34;
  uint local_30;
  uint local_2c [2];
  
  uVar2 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (param_1 < 2) {
    if (param_2 == (undefined4 *)0x0) {
      ak_print(10,1,"[%s:%d] new_ir_level is NULL\n","night_mode_check",0x8c2);
      iVar1 = 0x100;
    }
    else {
      ak_vpss_get_sensor_fps(param_1,(int *)&local_30);
      FUN_00021268(1000,local_30);
      if (DAT_00035278 != 0) {
        uVar3 = 0;
        do {
          iVar1 = ak_vpss_get_ev(param_1,(int *)&local_34);
          uVar2 = uVar2 + 1;
          if (iVar1 != 0) {
            ak_print(10,1,"[%s:%d] can not get ev!\n","night_mode_check",0x8d3);
            return iVar1;
          }
          iVar1 = ak_vpss_get_rgb_dis(param_1,DAT_00035284,DAT_00035288,DAT_0003528c,DAT_00035290,
                                      local_2c);
          if (iVar1 != 0) {
            ak_print(10,1,"[%s:%d] can not get rgb dis!\n","night_mode_check",0x8df);
            return iVar1;
          }
          ak_print(10,5,"[%s:%d] EV : %d, dis : %d!\n","night_mode_check",0x8e3,local_34,local_2c[0]
                  );
          if ((local_34 < DAT_00035268) && (DAT_00035270 < local_2c[0])) {
            uVar3 = uVar3 + 1;
            ak_print(10,5,"[%s:%d] day_cnt : %d!\n","night_mode_check",0x8eb,uVar3);
          }
          ak_sleep_ms(extraout_r0);
        } while (uVar2 < DAT_00035278);
        if (DAT_00035278 != uVar3) {
          *param_2 = 1;
          return 0;
        }
      }
      iVar1 = 0;
      *param_2 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","night_mode_check",0x8bc,param_1);
    iVar1 = 0x101;
  }
  return iVar1;
}



int ak_vpss_get_soft_ps_level(uint param_1,uint param_2,undefined4 *param_3)

{
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uStack_34;
  uint uStack_30;
  uint auStack_2c [3];
  undefined4 local_20;
  uint uStack_1c;
  
  if (param_1 < 2) {
    if (param_3 == (undefined4 *)0x0) {
      local_20 = 0x962;
      ak_print(10,1,"[%s:%d] new_level is null!\n","ak_vpss_get_soft_ps_level");
      iVar1 = 0x100;
    }
    else {
      if (DAT_00035260 == 0) {
        local_20 = 0x96c;
        ak_print(10,1,"[%s:%d] not init,set ak_vpss_set_soft_ps_param first! \n",
                 "ak_vpss_get_soft_ps_level");
        return 0x105;
      }
      if (1 < param_2) {
        local_20 = 0x972;
        ak_print(10,1,"[%s:%d] wrong input parameter\n","ak_vpss_get_soft_ps_level");
        return 0x101;
      }
      local_20 = 0x979;
      ak_print(10,5,"[%s:%d] wait_exp_stable!\n","ak_vpss_get_soft_ps_level");
      iVar1 = ak_vpss_wait_exp_stable(param_1,DAT_0003527c,DAT_00035280);
      local_20 = 0x97b;
      ak_print(10,5,"[%s:%d] wait_exp_stable is stable!\n","ak_vpss_get_soft_ps_level");
      if (iVar1 == 0) {
        if (param_2 != 0) {
          uVar2 = 0;
          uStack_34 = 0;
          uStack_30 = 0;
          auStack_2c[0] = 0;
          if (param_1 < 2) {
            if (param_3 == (undefined4 *)0x0) {
              ak_print(10,1,"[%s:%d] new_ir_level is NULL\n","night_mode_check",0x8c2);
              iVar1 = 0x100;
            }
            else {
              ak_vpss_get_sensor_fps(param_1,(int *)&uStack_30);
              FUN_00021268(1000,uStack_30);
              if (DAT_00035278 != 0) {
                uVar3 = 0;
                do {
                  iVar1 = ak_vpss_get_ev(param_1,(int *)&uStack_34);
                  uVar2 = uVar2 + 1;
                  if (iVar1 != 0) {
                    ak_print(10,1,"[%s:%d] can not get ev!\n","night_mode_check",0x8d3);
                    return iVar1;
                  }
                  iVar1 = ak_vpss_get_rgb_dis(param_1,DAT_00035284,DAT_00035288,DAT_0003528c,
                                              DAT_00035290,auStack_2c);
                  if (iVar1 != 0) {
                    ak_print(10,1,"[%s:%d] can not get rgb dis!\n","night_mode_check",0x8df);
                    return iVar1;
                  }
                  ak_print(10,5,"[%s:%d] EV : %d, dis : %d!\n","night_mode_check",0x8e3,uStack_34,
                           auStack_2c[0]);
                  if ((uStack_34 < DAT_00035268) && (DAT_00035270 < auStack_2c[0])) {
                    uVar3 = uVar3 + 1;
                    ak_print(10,5,"[%s:%d] day_cnt : %d!\n","night_mode_check",0x8eb,uVar3);
                  }
                  ak_sleep_ms(extraout_r0_00);
                } while (uVar2 < DAT_00035278);
                if (DAT_00035278 != uVar3) {
                  *param_3 = 1;
                  return 0;
                }
              }
              iVar1 = 0;
              *param_3 = 0;
            }
          }
          else {
            ak_print(10,1,"[%s:%d] dev:%d error!\n","night_mode_check",0x8bc,param_1);
            iVar1 = 0x101;
          }
          return iVar1;
        }
        uVar2 = 0;
        uStack_30 = 0;
        auStack_2c[0] = 0;
        if (param_1 < 2) {
          if (param_3 == (undefined4 *)0x0) {
            ak_print(10,1,"[%s:%d] new_ir_level is NULL\n","day_mode_check",0x87e);
            iVar1 = 0x100;
          }
          else {
            ak_vpss_get_sensor_fps(param_1,(int *)auStack_2c);
            FUN_00021268(1000,auStack_2c[0]);
            if (DAT_00035274 != 0) {
              uVar3 = 0;
              do {
                uStack_34 = ak_vpss_get_ev(param_1,(int *)&uStack_30);
                uVar2 = uVar2 + 1;
                if (uStack_34 != 0) {
                  ak_print(10,1,"[%s:%d] can not get ev!\n","day_mode_check",0x88c);
                  return uStack_34;
                }
                ak_print(10,5,"[%s:%d] EV : %d!\n","day_mode_check",0x890,uStack_30);
                if (DAT_00035264 < uStack_30) {
                  uVar3 = uVar3 + 1;
                  ak_print(10,5,"[%s:%d] night_cnt : %d!\n","day_mode_check",0x898,uVar3);
                }
                ak_sleep_ms(extraout_r0);
              } while (uVar2 < DAT_00035274);
              if (uVar3 != DAT_00035274) {
                *param_3 = 0;
                return 0;
              }
            }
            *param_3 = 1;
            iVar1 = 0;
          }
        }
        else {
          ak_print(10,1,"[%s:%d] dev:%d error!\n","day_mode_check",0x878,param_1);
          iVar1 = 0x101;
        }
        return iVar1;
      }
      local_20 = 0x97f;
      ak_print(10,1,"[%s:%d] exp stable error!\n","ak_vpss_get_soft_ps_level");
    }
  }
  else {
    local_20 = 0x95c;
    uStack_1c = param_1;
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_soft_ps_level");
    iVar1 = 0x101;
  }
  return iVar1;
}



char * ak_vpss_get_version(void)

{
  return "libplat_vpss V1.3.07-debug3";
}



void ak_vpss_get_ispsdk_version(void)

{
  AK_ISP_get_version();
  return;
}



undefined4 ak_vpss_osd_set_param(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_osd_set_param",0x42,param_1);
    return 0x101;
  }
  if (param_2 == (undefined4 *)0x0) {
    ak_print(10,1,"[%s:%d] param is null\n","ak_vpss_osd_set_param",0x48);
    return 0x100;
  }
  switch(*param_2) {
  case 1:
    *param_2 = 0x4005490a;
    break;
  case 2:
    if (DAT_00035294 == 0) {
      return 0;
    }
    memcpy(&DAT_0003529c,param_2,0x84);
    *param_2 = 0x4005490b;
    break;
  case 3:
    if (DAT_00035298 == 0) {
      return 0;
    }
    memcpy(&DAT_00035320,param_2,0x84);
    *param_2 = 0x4005490c;
    break;
  case 4:
    DAT_00035294 = 1;
    *param_2 = 0x4005490d;
    break;
  case 5:
    DAT_00035298 = 1;
    *param_2 = 0x4005490e;
  }
  iVar1 = Ak_ISP_Set_User_Params(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  return 0x109;
}



undefined4 ak_vpss_osd_get_param(int param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    if (param_2 == (int *)0x0) {
      ak_print(10,1,"[%s:%d] param is null\n","ak_vpss_osd_get_param",0x8f);
      uVar1 = 0x100;
    }
    else if (*param_2 == 2) {
      memcpy(param_2,&DAT_0003529c,0x84);
      uVar1 = 0;
    }
    else if (*param_2 == 3) {
      memcpy(param_2,&DAT_00035320,0x84);
      uVar1 = 0;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_osd_get_param",0x89,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_osd_close(int param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 != (int *)0x0) {
      iVar2 = *param_2;
      if (iVar2 == 2) {
        DAT_00035294 = 0;
        ak_print(10,3,"[%s:%d] disable main channel osd\n","ak_vpss_osd_close",0xba);
        *param_2 = 0x4005490b;
      }
      else if (iVar2 == 3) {
        DAT_00035298 = 0;
        ak_print(10,3,"[%s:%d] disable sub channel osd\n","ak_vpss_osd_close",0xbf);
        *param_2 = 0x4005490c;
      }
      else {
        ak_print(10,1,"[%s:%d] unknow osd channel, id: %d\n","ak_vpss_osd_close",0xc3,iVar2);
      }
      memset(param_2 + 1,0,0x80);
      iVar2 = Ak_ISP_Set_User_Params(param_1,param_2);
      uVar1 = 0x109;
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      return uVar1;
    }
    ak_print(10,1,"[%s:%d] param is null\n","ak_vpss_osd_close",0xb2);
    uVar1 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_osd_close",0xac,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_md_get_stat(int param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_61c;
  undefined1 auStack_618 [2];
  undefined1 auStack_616 [1546];
  
  if (param_1 < 2) {
    if (param_2 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] md is null\n","ak_vpss_md_get_stat",0xe3);
      uVar1 = 0x100;
    }
    else {
      local_61c = 0;
      memset(auStack_618,0,0x608);
      iVar2 = isp_get_statinfo(param_1,0x18,(int)auStack_618,&local_61c);
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get 3d nr stat info fail\n","ak_vpss_md_get_stat",0xed);
        return 0x109;
      }
      memcpy(param_2,auStack_616,0x600);
      uVar1 = 0;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_md_get_stat",0xdd,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_od_get(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_418;
  undefined4 local_414;
  undefined1 auStack_410 [1024];
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] od is null\n","ak_vpss_od_get",0x109);
      uVar1 = 0x100;
    }
    else {
      local_418 = 0;
      memset(&local_414,0,0x404);
      iVar2 = isp_get_statinfo(param_1,0x1a,param_2,&local_418);
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get af nr stat info fail\n","ak_vpss_od_get",0x115);
        return 0x109;
      }
      iVar2 = isp_get_statinfo(param_1,0x1e,(int)&local_414,&local_418);
      if (iVar2 == 0) {
        *(undefined4 *)(param_2 + 0x14) = local_414;
        memcpy((void *)(param_2 + 0x18),auStack_410,0x400);
        uVar1 = 0;
      }
      else {
        ak_print(10,1,"[%s:%d] get 3d nr stat info fail\n","ak_vpss_od_get",0x11e);
        uVar1 = 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_od_get",0x103,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_af_get_stat(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_c [2];
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] af_stat is null\n","ak_vpss_af_get_stat",0x13b);
      uVar1 = 0x100;
    }
    else {
      local_c[0] = 0;
      iVar2 = isp_get_statinfo(param_1,0x1a,param_2,local_c);
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get af stat info fail\n","ak_vpss_af_get_stat",0x144);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_af_get_stat",0x135,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_af_set_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] af_attr is null\n","ak_vpss_af_set_attr",0x15c);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_set_af_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_set_af_attr fail\n","ak_vpss_af_set_attr",0x164);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_af_set_attr",0x156,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_af_get_attr(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] af_attr is null\n","ak_vpss_af_get_attr",0x17c);
      uVar1 = 0x100;
    }
    else {
      iVar2 = AK_ISP_get_af_attr();
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] AK_ISP_get_af_attr fail\n","ak_vpss_af_get_attr",0x184);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_af_get_attr",0x176,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_effect_set(int param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  uint local_10;
  int local_c;
  
  if (param_1 < 2) {
    if (param_2 < 6) {
      if (100 < param_3 + 0x32) {
        ak_print(10,1,"[%s:%d] value range [-50, 50], cur value: %d\n","ak_vpss_effect_set",0x1a2,
                 param_3);
        return 0x101;
      }
      uVar1 = isp_set_effect(param_1,param_2,param_3);
    }
    else if (param_2 == 7) {
      if (param_3 == 0x3c || param_3 == 0x32) {
        uVar1 = isp_set_hz(param_1,param_3);
      }
      else {
        uVar1 = 0;
      }
    }
    else if (param_2 == 8) {
      uVar1 = 0;
      local_10 = 0;
      local_c = 0;
      if (param_3 < 4) {
        local_10 = param_3 & 1;
        local_c = (int)(param_3 & 2) >> 1;
        isp_set_flip_mirror(param_1,&local_10);
      }
      else {
        ak_print(10,1,"[%s:%d] value range [0, 3], cur value: %d\n","ak_vpss_effect_set",0x1bc,
                 param_3);
        uVar1 = 0x101;
      }
    }
    else if (param_2 == 6) {
      uVar1 = isp_cfg_file_set_style_id((char)param_3);
    }
    else {
      ak_print(10,1,"[%s:%d] error type: %d\n","ak_vpss_effect_set",0x1c7,param_2);
      uVar1 = 0x101;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_effect_set",0x19a,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_effect_get(int param_1,uint param_2,uint *param_3)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  uint local_18;
  int local_14;
  
  if (param_1 < 2) {
    if (param_3 == (uint *)0x0) {
      ak_print(10,1,"[%s:%d] value is null\n","ak_vpss_effect_get",0x1e0);
      uVar3 = 0x100;
    }
    else if (param_2 < 6) {
      uVar3 = isp_get_effect(param_1,param_2,param_3);
    }
    else if (param_2 == 7) {
      uVar2 = isp_get_hz();
      uVar3 = 0;
      *param_3 = uVar2;
    }
    else if (param_2 == 8) {
      uVar3 = 0;
      local_18 = 0;
      local_14 = 0;
      isp_get_flip_mirror(param_1,&local_18);
      *param_3 = local_18 | local_14 << 1;
    }
    else if (param_2 == 6) {
      bVar1 = isp_cfg_file_get_style_id();
      uVar3 = 0;
      *param_3 = (uint)bVar1;
    }
    else {
      ak_print(10,1,"[%s:%d] error type: %d\n","ak_vpss_effect_get",0x1fc,param_2);
      uVar3 = 0x101;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_effect_get",0x1da,param_1);
    uVar3 = 0x101;
  }
  return uVar3;
}



undefined4 ak_vpss_mask_set_area(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined2 extraout_r0;
  undefined2 extraout_r0_00;
  undefined2 extraout_r0_01;
  undefined2 extraout_r0_02;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  int iVar13;
  uint uVar14;
  undefined4 local_64;
  undefined4 local_60;
  uint local_5c;
  uint local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] area is null\n","ak_vpss_mask_set_area",0x218);
      uVar6 = 0x100;
    }
    else {
      local_64 = 0;
      local_60 = 0;
      local_5c = 0;
      local_58 = 0;
      local_54 = 0;
      ak_vi_get_chn_attr(0,&local_64);
      uVar4 = local_58;
      uVar2 = local_5c;
      ak_vi_get_chn_attr(1,&local_64);
      uVar5 = local_58;
      uVar3 = local_5c;
      pcVar7 = (char *)(param_2 + 8);
      iVar8 = 0;
      do {
        if (*pcVar7 != '\0') {
          uVar14 = (uint)*(ushort *)(pcVar7 + -8);
          if ((int)uVar2 <= (int)uVar14) {
            iVar13 = param_2 + iVar8 * 10;
            uVar9 = (uint)*(ushort *)(iVar13 + 2);
            uVar10 = (uint)*(ushort *)(iVar13 + 4);
            uVar11 = (uint)*(ushort *)(iVar13 + 6);
LAB_0001b36c:
            ak_print(10,1,
                     "[%s:%d] main_mask[%d] param error, start x:%d, end x:%d, start y:%d, end y:%d\n"
                     ,"ak_vpss_mask_set_area",0x234,iVar8,uVar14,uVar9,uVar10,uVar11);
            return 0x101;
          }
          uVar9 = (uint)*(ushort *)(pcVar7 + -6);
          if ((int)uVar2 <= (int)uVar9) {
            iVar13 = param_2 + iVar8 * 10;
            uVar10 = (uint)*(ushort *)(iVar13 + 4);
            uVar11 = (uint)*(ushort *)(iVar13 + 6);
            goto LAB_0001b36c;
          }
          uVar10 = (uint)*(ushort *)(pcVar7 + -4);
          if ((int)uVar4 <= (int)uVar10) {
            uVar11 = (uint)*(ushort *)(param_2 + iVar8 * 10 + 6);
            goto LAB_0001b36c;
          }
          uVar11 = (uint)*(ushort *)(pcVar7 + -2);
          if ((int)uVar4 <= (int)uVar11 || (uVar9 <= uVar14 || uVar11 <= uVar10)) goto LAB_0001b36c;
        }
        iVar8 = iVar8 + 1;
        pcVar7 = pcVar7 + 10;
      } while (iVar8 != 4);
      iVar8 = isp_set_main_mask_area(param_1,param_2);
      if (iVar8 == 0) {
        iVar8 = 0;
        local_50 = 0;
        local_4c = 0;
        local_48 = 0;
        local_44 = 0;
        local_40 = 0;
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
        local_30 = 0;
        local_2c = 0;
        iVar13 = param_2;
        puVar12 = &local_50;
        do {
          uVar1 = *(ushort *)(param_2 + iVar8);
          *(undefined1 *)(puVar12 + 2) = *(undefined1 *)(iVar13 + 8);
          FUN_00021268(uVar1 * uVar3,uVar2);
          uVar1 = *(ushort *)(iVar13 + 2);
          *(undefined2 *)((int)&local_50 + iVar8) = extraout_r0;
          iVar8 = iVar8 + 10;
          FUN_00021268(uVar1 * uVar3,uVar2);
          uVar1 = *(ushort *)(iVar13 + 4);
          *(undefined2 *)((int)puVar12 + 2) = extraout_r0_00;
          FUN_00021268(uVar1 * uVar5,uVar4);
          uVar1 = *(ushort *)(iVar13 + 6);
          *(undefined2 *)(puVar12 + 1) = extraout_r0_01;
          FUN_00021268(uVar1 * uVar5,uVar4);
          *(undefined2 *)((int)puVar12 + 6) = extraout_r0_02;
          iVar13 = iVar13 + 10;
          puVar12 = (undefined4 *)((int)puVar12 + 10);
        } while (iVar8 != 0x28);
        iVar8 = isp_set_sub_mask_area(param_1,(int)&local_50);
        uVar6 = 0;
        if (iVar8 != 0) {
          ak_print(10,1,"[%s:%d] set isp sub mask failed\n","ak_vpss_mask_set_area",0x24b);
          uVar6 = 0x109;
        }
      }
      else {
        ak_print(10,1,"[%s:%d] set isp main mask failed\n","ak_vpss_mask_set_area",0x23b);
        uVar6 = 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_mask_set_area",0x212,param_1);
    uVar6 = 0x101;
  }
  return uVar6;
}



undefined4 ak_vpss_mask_get_area(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      ak_print(10,1,"[%s:%d] area is null\n","ak_vpss_mask_get_area",0x264);
      uVar1 = 0x100;
    }
    else {
      iVar2 = isp_get_main_mask_area(param_1,param_2);
      uVar1 = 0;
      if (iVar2 != 0) {
        ak_print(10,1,"[%s:%d] get isp main mask failed\n","ak_vpss_mask_get_area",0x26a);
        return 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_mask_get_area",0x25e,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_mask_set_color(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_28;
  undefined1 local_24;
  
  if (param_1 < 2) {
    if (param_2 == (byte *)0x0) {
      ak_print(10,1,"[%s:%d] color is null\n","ak_vpss_mask_set_color",0x282);
      uVar4 = 0x100;
    }
    else {
      bVar1 = *param_2;
      if (3 < bVar1) {
        ak_print(10,1,"[%s:%d] color_type %d is error, must be [%d, %d]\n","ak_vpss_mask_set_color",
                 0x289,bVar1,0,3);
        return 0x101;
      }
      uVar8 = (uint)param_2[3];
      uVar9 = (uint)param_2[2];
      bVar2 = param_2[4];
      uVar10 = (uint)bVar2;
      local_24 = 0;
      local_28._0_2_ = CONCAT11(param_2[1],bVar1);
      local_28 = (uint)(ushort)local_28;
      ak_print(10,4,"[%s:%d] color rgb:[%d, %d, %d]\n","ak_vpss_mask_set_color",0x295,uVar9,uVar8,
               uVar10);
      uVar7 = (int)((short)(ushort)bVar2 * 0x75 + uVar8 * 0x259 + uVar9 * 0x132) >> 10;
      if (uVar7 == 0) {
        uVar3 = 0;
      }
      else {
        if (0xfe < uVar7) {
          uVar7 = 0xff;
        }
        uVar3 = (undefined1)uVar7;
      }
      iVar6 = (int)(uVar9 * -0xad + uVar8 * -0x153 + uVar10 * 0x200) >> 10;
      if (iVar6 == -0x80) {
        uVar5 = 0;
      }
      else if (iVar6 == 0x7f) {
        uVar5 = 0xff;
      }
      else {
        uVar5 = iVar6 - 0x80U & 0xff;
      }
      local_28 = CONCAT13((char)uVar5,CONCAT12(uVar3,(ushort)local_28));
      iVar6 = (int)(uVar10 * -0x53 + uVar8 * -0x1ad + uVar9 * 0x200) >> 10;
      if (iVar6 == -0x80) {
        uVar8 = 0;
      }
      else if (iVar6 == 0x7f) {
        uVar8 = 0xff;
      }
      else {
        uVar8 = iVar6 - 0x80U & 0xff;
      }
      local_24 = (undefined1)uVar8;
      ak_print(10,4,"[%s:%d] color yuv:[%d, %d, %d]\n","ak_vpss_mask_set_color",0x29b,uVar7,uVar5,
               uVar8);
      iVar6 = isp_set_mask_color(param_1,(int)&local_28);
      uVar4 = 0;
      if (iVar6 != 0) {
        ak_print(10,1,"[%s:%d] set mask color failed\n","ak_vpss_mask_set_color",0x29f);
        uVar4 = 0x109;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_mask_set_color",0x27c,param_1);
    uVar4 = 0x101;
  }
  return uVar4;
}



undefined4 ak_vpss_mask_get_color(int param_1,undefined1 *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  uint extraout_r0;
  int extraout_r0_00;
  uint extraout_r0_01;
  uint extraout_r0_02;
  int extraout_r0_03;
  uint extraout_r0_04;
  uint extraout_r0_05;
  uint extraout_r0_06;
  uint extraout_r0_07;
  uint extraout_r0_08;
  uint extraout_r0_09;
  uint uVar4;
  uint uVar5;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r1_02;
  uint extraout_r1_03;
  uint extraout_r1_04;
  uint extraout_r1_05;
  uint extraout_r1_06;
  uint extraout_r1_07;
  uint extraout_r1_08;
  uint extraout_r1_09;
  undefined1 uVar6;
  undefined4 local_30;
  byte local_2c;
  
  if (param_1 < 2) {
    if (param_2 != (undefined1 *)0x0) {
      local_30 = 0;
      local_2c = 0;
      iVar3 = isp_get_mask_color(param_1,(int)&local_30);
      if (iVar3 != 0) {
        ak_print(10,1,"[%s:%d] get mask color failed\n","ak_vpss_mask_get_color",0x2bf);
        return 0x109;
      }
      *param_2 = (undefined1)local_30;
      param_2[1] = local_30._1_1_;
      FUN_00021640((uint)(local_30 >> 0x10));
      uVar4 = local_30 >> 0x18;
      FUN_00021640(local_2c - 0x80);
      FUN_0002171c(extraout_r0_00,extraout_r1_00,0x66666666,0x3ff66666);
      FUN_00021370(extraout_r0,extraout_r1,extraout_r0_01,extraout_r1_01);
      bVar1 = FUN_00021ca4(extraout_r0_02,extraout_r1_02,0,0);
      uVar6 = 0;
      if (bVar1) {
        bVar1 = FUN_00021c68(extraout_r0_02,extraout_r1_02,0,0x406fe000);
        if (bVar1) {
          uVar5 = FUN_00021d14(extraout_r0_02,extraout_r1_02);
          uVar6 = (undefined1)uVar5;
        }
        else {
          uVar6 = 0xff;
        }
      }
      param_2[2] = uVar6;
      FUN_00021640(uVar4 - 0x80);
      FUN_0002171c(extraout_r0_03,extraout_r1_03,0x5c28f5c3,0x3fd5c28f);
      FUN_0002136c(extraout_r0,extraout_r1,extraout_r0_04,extraout_r1_04);
      FUN_0002171c(extraout_r0_00,extraout_r1_00,0xeb851eb8,0x3fe6b851);
      FUN_0002136c(extraout_r0_05,extraout_r1_05,extraout_r0_06,extraout_r1_06);
      bVar1 = FUN_00021ca4(extraout_r0_07,extraout_r1_07,0,0);
      uVar6 = 0;
      if (bVar1) {
        bVar1 = FUN_00021c68(extraout_r0_07,extraout_r1_07,0,0x406fe000);
        if (bVar1) {
          uVar4 = FUN_00021d14(extraout_r0_07,extraout_r1_07);
          uVar6 = (undefined1)uVar4;
        }
        else {
          uVar6 = 0xff;
        }
      }
      param_2[3] = uVar6;
      FUN_0002171c(extraout_r0_03,extraout_r1_03,0xa1cac083,0x3ffbb645);
      FUN_00021370(extraout_r0,extraout_r1,extraout_r0_08,extraout_r1_08);
      bVar1 = FUN_00021ca4(extraout_r0_09,extraout_r1_09,0,0);
      if (bVar1) {
        bVar1 = FUN_00021c68(extraout_r0_09,extraout_r1_09,0,0x406fe000);
        if (bVar1) {
          uVar4 = FUN_00021d14(extraout_r0_09,extraout_r1_09);
          uVar6 = (char)uVar4;
        }
        else {
          uVar6 = 0xff;
        }
      }
      else {
        uVar6 = 0;
      }
      param_2[4] = uVar6;
      return 0;
    }
    ak_print(10,1,"[%s:%d] color is null\n","ak_vpss_mask_get_color",0x2b7);
    uVar2 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_mask_get_color",0x2b1,param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 FUN_0001ba7c(int param_1,byte *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","check_fps_para",0x167,param_1);
    return 0xffffffff;
  }
  if (*(int *)(&DAT_000353d4 + param_1 * 0x38) == 3) {
    ak_print(10,4,"[%s:%d] hight light:\n\tframe_rate=%d, max_exp_time=%d, to mid_light_gain=%d\n",
             "check_fps_para",0x176,*param_2,*(undefined2 *)(param_2 + 4),param_2[2]);
    ak_print(10,4,"[%s:%d] low light:\n\tframe_rate=%d, max_exp_time=%d, to mid_light_gain=%d\n",
             "check_fps_para",0x17b,param_2[0xc],*(undefined2 *)(param_2 + 0x10),param_2[0xd]);
    uVar1 = (uint)*(ushort *)(param_2 + 10);
    uVar3 = (uint)param_2[7];
    uVar5 = (uint)param_2[8];
    ak_print(10,4,
             "[%s:%d] mid light:\n\tframe_rate=%d, max_exp_time=%d, to high_light_gain=%d, to low_light_gain=%d\n"
             ,"check_fps_para",0x181,param_2[6],uVar1,uVar3,uVar5);
    if (0x37 < *param_2 - 5) {
      ak_print(10,1,"[%s:%d] hight_light_frame_rate=%d failed\n","check_fps_para",0x187,
               (uint)*param_2,uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (*(ushort *)(param_2 + 4) < 100) {
      ak_print(10,1,"[%s:%d] hight_light_max_exp_time = %d failed\n","check_fps_para",399,
               *(ushort *)(param_2 + 4),uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (param_2[2] == 0) {
      ak_print(10,1,"[%s:%d] hight_light_to_mid_light_gain = %d failed\n","check_fps_para",0x196,0,
               uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (0x37 < param_2[0xc] - 5) {
      ak_print(10,1,"[%s:%d] low_light_frame_rate=%d failed\n","check_fps_para",0x19d,
               (uint)param_2[0xc],uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (*(ushort *)(param_2 + 0x10) < 100) {
      ak_print(10,1,"[%s:%d] low_light_max_exp_time = %d failed\n","check_fps_para",0x1a5,
               *(ushort *)(param_2 + 0x10),uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (0x37 < param_2[6] - 5) {
      ak_print(10,1,"[%s:%d] mid_light_frame_rate=%d failed\n","check_fps_para",0x1b4,
               (uint)param_2[6],uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (*(ushort *)(param_2 + 10) < 100) {
      ak_print(10,1,"[%s:%d] mid_light_max_exp_time = %d failed\n","check_fps_para",0x1bc,
               *(ushort *)(param_2 + 10),uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
    if (param_2[8] == 0) {
      ak_print(10,1,"[%s:%d] mid_light_to_low_light_gain = %d failed\n","check_fps_para",0x1ca,0,
               uVar1,uVar3,uVar5);
      return 0xffffffff;
    }
  }
  else {
    ak_print(10,4,"[%s:%d] hight light:\n\tframe_rate=%u max_exp_time=%u low_light_gain=%u\n",
             "check_fps_para",0x1d4,*(undefined4 *)param_2,*(undefined4 *)(param_2 + 4),
             *(undefined4 *)(param_2 + 8));
    uVar2 = *(undefined4 *)(param_2 + 0x10);
    uVar4 = *(undefined4 *)(param_2 + 0x14);
    ak_print(10,4,"[%s:%d] low light:\n\tframe_rate=%u max_exp_time=%u light_gain=%u\n",
             "check_fps_para",0x1d9,*(undefined4 *)(param_2 + 0xc),uVar2,uVar4);
    if (0x37 < *(int *)param_2 - 5U) {
      ak_print(10,1,"[%s:%d] hight_light_frame_rate=%u failed\n","check_fps_para",0x1df,
               *(int *)param_2,uVar2,uVar4);
      return 0xffffffff;
    }
    if (0xff9b < *(int *)(param_2 + 4) - 100U) {
      ak_print(10,1,"[%s:%d] hight_light_max_exp_time = %u failed\n","check_fps_para",0x1e7,
               *(int *)(param_2 + 4),uVar2,uVar4);
      return 0xffffffff;
    }
    if (0xfe < *(int *)(param_2 + 8) - 1U) {
      ak_print(10,1,"[%s:%d] hight_light_to_low_light_gain = %u failed\n","check_fps_para",0x1ef,
               *(int *)(param_2 + 8),uVar2,uVar4);
      return 0xffffffff;
    }
    if (0x37 < *(int *)(param_2 + 0xc) - 5U) {
      ak_print(10,1,"[%s:%d] low_light_frame_rate = %u failed\n","check_fps_para",0x1f7,
               *(int *)(param_2 + 0xc),uVar2,uVar4);
      return 0xffffffff;
    }
    if (0xff9b < *(int *)(param_2 + 0x10) - 100U) {
      ak_print(10,1,"[%s:%d] low_light_max_exp_time = %u failed\n","check_fps_para",0x1ff,
               *(int *)(param_2 + 0x10),uVar2,uVar4);
      return 0xffffffff;
    }
    if (0xfe < *(int *)(param_2 + 0x14) - 1U) {
      ak_print(10,1,"[%s:%d] low_light to hight_light_gain = %u failed\n","check_fps_para",0x207,
               *(int *)(param_2 + 0x14),uVar2,uVar4);
      return 0xffffffff;
    }
  }
  return 0;
}



void FUN_0001c170(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  void *__src;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  ushort *puVar13;
  ushort *puVar14;
  int iVar15;
  ulonglong uVar16;
  int local_2734;
  int *local_2730;
  ushort *local_2728;
  undefined1 auStack_2714 [18];
  ushort local_2702 [65];
  ushort local_2680 [65];
  ushort local_25fe [65];
  ushort local_257c [65];
  ushort local_24fa [65];
  ushort local_2478 [173];
  ushort local_231e [4477];
  
  uVar16 = FUN_00021640((param_2 + 0x32) * 0x400);
  uVar16 = FUN_00021988((int)uVar16,(uint)(uVar16 >> 0x20),0,0x40490000);
  uVar7 = FUN_00021cb8((uint)uVar16,(uint)(uVar16 >> 0x20));
  memset(auStack_2714,0,0x26ea);
  if (*(int *)(&DAT_0003543c + param_1 * 4) == 0) {
    __src = (void *)(param_1 * 0x26ea + 0x35444);
    AK_ISP_get_wdr_attr(param_1,__src,__src,AK_ISP_get_wdr_attr);
    *(undefined4 *)(&DAT_0003543c + param_1 * 4) = 1;
  }
  else {
    __src = (void *)(param_1 * 0x26ea + 0x35444);
  }
  memcpy(auStack_2714,__src,0x26ea);
  local_2730 = (int *)0x23a0c;
  local_2734 = 0;
  puVar9 = local_24fa;
  puVar10 = local_2478;
  puVar11 = local_257c;
  puVar12 = local_25fe;
  puVar13 = local_2680;
  puVar14 = local_2702;
  do {
    local_2730 = local_2730 + 1;
    iVar15 = *local_2730 * (0x400 - uVar7);
    uVar1 = (uVar7 * *puVar14 + iVar15) * 0x40;
    uVar6 = uVar1 >> 0x10;
    *puVar14 = (ushort)(uVar1 >> 0x10);
    uVar1 = (uVar7 * *puVar13 + iVar15) * 0x40;
    *puVar13 = (ushort)(uVar1 >> 0x10);
    uVar2 = (uVar7 * *puVar12 + iVar15) * 0x40;
    *puVar12 = (ushort)(uVar2 >> 0x10);
    uVar3 = (uVar7 * *puVar11 + iVar15) * 0x40;
    *puVar11 = (ushort)(uVar3 >> 0x10);
    uVar4 = (uVar7 * *puVar9 + iVar15) * 0x40;
    *puVar9 = (ushort)(uVar4 >> 0x10);
    iVar8 = uVar7 * *puVar10 + iVar15;
    if (0x3ff < uVar6) {
      iVar15 = -0xfc01;
    }
    uVar5 = iVar8 * 0x40;
    *puVar10 = (ushort)(uVar5 >> 0x10);
    if (0x3ff < uVar6) {
      *puVar14 = (ushort)iVar15;
    }
    if (0x3ff < uVar1 >> 0x10) {
      *puVar13 = 0x3ff;
    }
    if (0x3ff < uVar2 >> 0x10) {
      *puVar12 = 0x3ff;
    }
    if (0x3ff < uVar3 >> 0x10) {
      *puVar11 = 0x3ff;
    }
    if (0x3ff < uVar4 >> 0x10) {
      *puVar9 = 0x3ff;
    }
    if (0x3ff < uVar5 >> 0x10) {
      *puVar10 = 0x3ff;
    }
    local_2734 = local_2734 + 1;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
    puVar14 = puVar14 + 1;
  } while (local_2734 != 0x41);
  local_2728 = local_231e;
  do {
    local_2730 = (int *)0x23a0c;
    local_2734 = 0x41;
    puVar9 = local_2728 + 0x145;
    puVar10 = local_2728 + 0xc3;
    puVar11 = local_2728;
    puVar12 = local_2728 + 0x104;
    puVar13 = local_2728 + 0x82;
    puVar14 = local_2728 + 0x41;
    do {
      local_2730 = local_2730 + 1;
      iVar15 = *local_2730 * (0x400 - uVar7);
      uVar1 = (uVar7 * *puVar11 + iVar15) * 0x40;
      uVar6 = uVar1 >> 0x10;
      *puVar11 = (ushort)(uVar1 >> 0x10);
      uVar1 = (uVar7 * *puVar14 + iVar15) * 0x40;
      *puVar14 = (ushort)(uVar1 >> 0x10);
      uVar2 = (uVar7 * *puVar13 + iVar15) * 0x40;
      *puVar13 = (ushort)(uVar2 >> 0x10);
      uVar3 = (uVar7 * *puVar10 + iVar15) * 0x40;
      *puVar10 = (ushort)(uVar3 >> 0x10);
      uVar4 = (uVar7 * *puVar12 + iVar15) * 0x40;
      *puVar12 = (ushort)(uVar4 >> 0x10);
      iVar8 = uVar7 * *puVar9 + iVar15;
      if (0x3ff < uVar6) {
        iVar15 = -0xfc01;
      }
      uVar5 = iVar8 * 0x40;
      *puVar9 = (ushort)(uVar5 >> 0x10);
      if (0x3ff < uVar6) {
        *puVar11 = (ushort)iVar15;
      }
      if (0x3ff < uVar1 >> 0x10) {
        *puVar14 = 0x3ff;
      }
      if (0x3ff < uVar2 >> 0x10) {
        *puVar13 = 0x3ff;
      }
      if (0x3ff < uVar3 >> 0x10) {
        *puVar10 = 0x3ff;
      }
      if (0x3ff < uVar4 >> 0x10) {
        *puVar12 = 0x3ff;
      }
      if (0x3ff < uVar5 >> 0x10) {
        *puVar9 = 0x3ff;
      }
      local_2734 = local_2734 + -1;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
      puVar12 = puVar12 + 1;
      puVar13 = puVar13 + 1;
      puVar14 = puVar14 + 1;
    } while (local_2734 != 0);
    local_2728 = local_2728 + 0x1f2;
  } while (local_2728 != (ushort *)&stack0xffffffe6);
  *(int *)(&DAT_0003a22c + param_1 * 0x18) = param_2;
  AK_ISP_set_wdr_attr(param_1,auStack_2714,AK_ISP_set_wdr_attr);
  return;
}



void FUN_0001c544(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  void *__src;
  short *psVar7;
  ulonglong uVar8;
  undefined1 auStack_2bd0 [32];
  short local_2bb0 [256];
  short local_29b0 [303];
  short local_2752 [5017];
  
  memset(auStack_2bd0,0,0x2bae);
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","set_sharp",0x4c5,param_1);
    return;
  }
  if (*(int *)(&DAT_0003a248 + param_1 * 4) == 0) {
    __src = (void *)(param_1 * 0x2bae + 0x3a250);
    AK_ISP_get_sharp_attr(param_1,__src);
    *(undefined4 *)(&DAT_0003a248 + param_1 * 4) = 1;
  }
  else {
    __src = (void *)(param_1 * 0x2bae + 0x3a250);
  }
  uVar8 = FUN_00021640((param_2 + 0x32) * 0x400);
  uVar8 = FUN_00021988((int)uVar8,(uint)(uVar8 >> 0x20),0,0x40490000);
  uVar3 = FUN_00021cb8((uint)uVar8,(uint)(uVar8 >> 0x20));
  memcpy(auStack_2bd0,__src,0x2bae);
  psVar5 = local_2bb0;
  psVar6 = local_29b0;
  iVar4 = 0x100;
  do {
    iVar1 = uVar3 * (int)*psVar5 * 0x40;
    *psVar5 = (short)((uint)iVar1 >> 0x10);
    iVar1 = iVar1 >> 0x10;
    iVar2 = uVar3 * (int)*psVar6 * 0x40;
    *psVar6 = (short)((uint)iVar2 >> 0x10);
    if (iVar1 < 0x100) {
      if (iVar1 < -0x100) {
        *psVar5 = -0x100;
      }
    }
    else {
      *psVar5 = 0xff;
    }
    iVar2 = iVar2 >> 0x10;
    if (iVar2 < 0x100) {
      if (iVar2 < -0x100) {
        *psVar6 = -0x100;
      }
    }
    else {
      *psVar6 = 0xff;
    }
    iVar4 = iVar4 + -1;
    psVar5 = psVar5 + 1;
    psVar6 = psVar6 + 1;
  } while (iVar4 != 0);
  psVar5 = local_2752;
  do {
    psVar7 = psVar5 + 0x100;
    iVar4 = 0x100;
    psVar6 = psVar5;
    do {
      iVar1 = uVar3 * (int)*psVar6 * 0x40;
      *psVar6 = (short)((uint)iVar1 >> 0x10);
      iVar1 = iVar1 >> 0x10;
      iVar2 = uVar3 * (int)*psVar7 * 0x40;
      *psVar7 = (short)((uint)iVar2 >> 0x10);
      if (iVar1 < 0x100) {
        if (iVar1 < -0x100) {
          *psVar6 = -0x100;
        }
      }
      else {
        *psVar6 = 0xff;
      }
      iVar2 = iVar2 >> 0x10;
      if (iVar2 < 0x100) {
        if (iVar2 < -0x100) {
          *psVar7 = -0x100;
        }
      }
      else {
        *psVar7 = 0xff;
      }
      iVar4 = iVar4 + -1;
      psVar6 = psVar6 + 1;
      psVar7 = psVar7 + 1;
    } while (iVar4 != 0);
    psVar5 = psVar5 + 0x22f;
  } while (psVar5 != (short *)&stack0xfffffffc);
  *(int *)(&DAT_0003a228 + param_1 * 0x18) = param_2;
  AK_ISP_set_sharp_attr(param_1,auStack_2bd0,psVar6,AK_ISP_set_sharp_attr);
  return;
}



int FUN_0001c7b8(int param_1)

{
  int iVar1;
  int iVar2;
  int local_108;
  uint local_104;
  uint local_e8;
  
  if (1 < param_1) {
    iVar1 = ak_print(10,1,"[%s:%d] dev:%d error!\n","set_exptimemax_by_curfps");
    return iVar1;
  }
  iVar1 = param_1 * 0x38;
  if (*(int *)(&DAT_000353d8 + iVar1) == 0) {
    return param_1;
  }
  iVar2 = *(int *)(&DAT_000353a8 + iVar1);
  if (iVar2 == *(int *)(&DAT_000353b4 + iVar1)) {
    iVar1 = *(int *)(&DAT_000353c0 + iVar1);
  }
  else if (iVar2 == *(int *)(&DAT_000353ac + iVar1)) {
    iVar1 = *(int *)(&DAT_000353b8 + iVar1);
  }
  else {
    if (iVar2 != *(int *)(&DAT_000353b0 + iVar1)) {
      iVar1 = ak_print(10,1,"[%s:%d] fps:%d cannot find exp_time!\n","set_exptimemax_by_curfps");
      return iVar1;
    }
    iVar1 = *(int *)(&DAT_000353bc + iVar1);
  }
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","set_exptimemax",0x2c7,param_1);
    return -1;
  }
  iVar2 = AK_ISP_get_ae_attr(param_1,&local_108);
  if (iVar2 == 0) {
    local_108 = iVar1;
    if ((DAT_00035134 == 0x32) && (*(int *)(&DAT_000353a8 + param_1 * 0x38) == 0xf)) {
      iVar1 = 0;
      if (*(int *)(&DAT_00035414 + param_1 * 0x14) != 0) {
        iVar1 = vi_dev_get_exptime_for_fps(0xe);
        if (iVar1 == 0) {
          local_108 = 0;
        }
        iVar1 = *(int *)(&DAT_00035414 + param_1 * 0x14);
      }
    }
    else {
      iVar1 = *(int *)(&DAT_00035414 + param_1 * 0x14);
    }
    if ((*(int *)(&DAT_0003541c + param_1 * 0x14) != 1) || (iVar1 != 0)) {
      if (DAT_00035134 == 0x3c) {
        if (*(int *)(&DAT_000353a8 + param_1 * 0x38) - 0xcU < 2) {
          local_e8 = (uint)(local_108 * 0x7d) / 0x4b0;
        }
        else {
          local_e8 = (uint)(*(int *)(&DAT_000353a8 + param_1 * 0x38) * local_108) / 0x78;
        }
      }
      else {
        iVar2 = *(int *)(&DAT_000353a8 + param_1 * 0x38);
        if (iVar2 - 0xcU < 2) {
          local_e8 = (uint)(local_108 * 0x7d) / 1000;
        }
        else if ((iVar2 == 0xe) || ((iVar2 == 0xf && (iVar1 != 0)))) {
          local_e8 = (uint)(local_108 * 0x594) / 10000;
        }
        else {
          local_e8 = (uint)(local_108 * iVar2) / 100;
        }
      }
      if (iVar1 == 1) {
        local_104 = local_e8;
      }
    }
    iVar2 = AK_ISP_set_ae_attr(param_1,&local_108);
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = -1;
    }
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}



undefined4 FUN_0001c89c(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","get_aestat",0x147,param_1);
    return 0xffffffff;
  }
  iVar1 = AK_ISP_get_ae_run_info(param_1,auStack_2c);
  if (iVar1 == 0) {
    *param_2 = local_28;
    param_2[1] = local_24;
    param_2[2] = uStack_20;
    param_2[3] = uStack_1c;
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_module_check_cfg(int param_1,uint *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  ushort *puVar8;
  short local_2c;
  ushort local_2a [3];
  
  uVar5 = 0;
  local_2c = 0;
  local_2a[0] = 0;
  if ((param_1 == 0) || (*param_2 == 0)) {
    ak_print(10,1,"[%s:%d] cfgbuf is null or size is 0, size:%u!\n","isp_module_check_cfg",0x588,
             *param_2);
    uVar1 = 0xffffffff;
  }
  else {
    puVar8 = (ushort *)((int)&DAT_00035134 + 2);
    iVar7 = 0;
    sVar6 = 0;
    do {
      memcpy(&local_2c,(void *)(param_1 + uVar5),2);
      memcpy(local_2a,(void *)(param_1 + uVar5 + 2),2);
      sVar3 = sVar6 + 1;
      if (local_2c != sVar6) {
LAB_0001ca2c:
        ak_print(10,1,"[%s:%d] data err!\n","isp_module_check_cfg",0x595);
        return 0xffffffff;
      }
      uVar4 = (uint)local_2a[0];
      puVar8 = puVar8 + 1;
      uVar5 = uVar5 + uVar4;
      if (uVar4 != *puVar8) goto LAB_0001ca2c;
      uVar2 = *param_2;
      iVar7 = iVar7 + uVar4;
      if (uVar2 < uVar5) {
        uVar1 = 0x59e;
        goto LAB_0001ca60;
      }
      sVar6 = sVar3;
    } while (sVar3 != 0x18);
    memcpy(&local_2c,(void *)(param_1 + uVar5),2);
    if (local_2c == 0x1c) {
      memcpy(local_2a,(void *)(param_1 + uVar5 + 2),2);
      uVar2 = *param_2;
      if (uVar2 < local_2a[0] + 2 + uVar5 + 2) {
        uVar1 = 0x5b6;
LAB_0001ca60:
        ak_print(10,1,"[%s:%d] size err:%u!\n","isp_module_check_cfg",uVar1,uVar2);
        return 0xffffffff;
      }
      uVar1 = 0;
      *param_2 = local_2a[0] + 4 + iVar7;
    }
    else {
      ak_print(10,1,"[%s:%d] sensor id err!\n","isp_module_check_cfg",0x5a7);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}



undefined4 isp_dev_open(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    iVar1 = AK_ISP_sdk_init();
    uVar2 = 0;
    if (iVar1 != 0) {
      ak_print(10,1,"[%s:%d] AK_ISP_sdk_init dev %d failed!\n","isp_dev_open",0x5ce,param_1);
      uVar2 = 0xffffffff;
    }
    return uVar2;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_dev_open",0x5c8,param_1);
  return 0xffffffff;
}



undefined4 isp_dev_close(int param_1)

{
  if (param_1 < 2) {
    AK_ISP_sdk_exit();
    return 0;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_dev_close",0x5de,param_1);
  return 0xffffffff;
}



// WARNING: Removing unreachable block (ram,0x0001cca4)
// WARNING: Removing unreachable block (ram,0x0001ccac)
// WARNING: Removing unreachable block (ram,0x0001ccb0)
// WARNING: Removing unreachable block (ram,0x0001ccc8)
// WARNING: Removing unreachable block (ram,0x0001cccc)
// WARNING: Removing unreachable block (ram,0x0001ccd0)
// WARNING: Removing unreachable block (ram,0x0001ccd4)

int isp_3D_NR_create(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 < 2) {
    iVar2 = ((param_3 * param_2 * 3) / 2) * 5;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 3;
    }
    uVar1 = ak_get_os_timestamp();
    iVar3 = (iVar2 >> 2) + 0x40;
    iVar2 = ak_mem_dma_alloc_(7,iVar3,"isp_3D_NR_create",uVar1);
    if (iVar2 == 0) {
      ak_print(7,1,"[%s:%d] alloc [%d] bytes 3DNR DMA memory failed!\n","isp_3D_NR_create",0x666,
               iVar3);
    }
    else {
      ak_mem_dma_vaddr2paddr();
    }
    return 0;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_3D_NR_create",0x65d,param_1);
  return 0;
}



undefined4 isp_fps_main(int param_1)

{
  if (param_1 < 2) {
    ak_thread_mutex_init(&DAT_0003f9ac + param_1 * 0x18,0);
    return 0;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_fps_main",0x68b,param_1);
  return 0xffffffff;
}



undefined4 isp_module_deinit(int param_1)

{
  if (param_1 < 2) {
    ak_thread_mutex_destroy(&DAT_0003f9ac + param_1 * 0x18);
    return 0;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_module_deinit",0x6b4,param_1);
  return 0xffffffff;
}



uint isp_get_attr(int param_1,uint param_2,void *param_3,undefined4 *param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint local_10c;
  undefined1 auStack_108 [80];
  undefined1 auStack_b8 [164];
  
  local_10c = param_2;
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_attr",0x6d3,param_1);
    return 0xffffffff;
  }
  if (param_4 == (undefined4 *)0x0 || param_3 == (void *)0x0) {
    uVar7 = 0x6d8;
LAB_0001cf54:
    ak_print(10,1,"[%s:%d] param err\n","isp_get_attr",uVar7);
    uVar1 = 0xffffffff;
  }
  else {
    switch(param_2) {
    case 0:
      uVar1 = AK_ISP_get_blc_attr(param_1,(int)param_3 + 4);
      *param_4 = 0xba;
      break;
    case 1:
      uVar1 = AK_ISP_get_lsc_attr(param_1,(int)param_3 + 4);
      *param_4 = 0xcc;
      break;
    case 2:
      uVar1 = AK_ISP_get_raw_lut_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x36c;
      break;
    case 3:
      uVar2 = AK_ISP_get_nr1_attr(param_1,(int)param_3 + 4);
      uVar3 = AK_ISP_get_nr2_attr(param_1,(int)param_3 + 0x6fa);
      uVar1 = AK_ISP_get_uvnr_attr(param_1,(int)param_3 + 0x940);
      *param_4 = 0xae6;
      uVar1 = uVar3 | uVar2 | uVar1;
      break;
    case 4:
      uVar1 = AK_ISP_get_3d_nr_attr(param_1,(int)param_3 + 4);
      *param_4 = 0xe90;
      break;
    case 5:
      uVar1 = AK_ISP_get_gb_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x56;
      break;
    case 6:
      uVar1 = AK_ISP_get_demo_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x16;
      break;
    case 7:
      uVar1 = AK_ISP_get_rgb_gamma_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x36c;
      break;
    case 8:
      uVar1 = AK_ISP_get_ccm_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x88;
      break;
    case 9:
      uVar1 = AK_ISP_get_fcs_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x6a;
      break;
    case 10:
      uVar1 = AK_ISP_get_wdr_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x26ee;
      break;
    case 0xb:
      uVar2 = AK_ISP_get_sharp_attr(param_1,(int)param_3 + 4);
      uVar1 = AK_ISP_get_sharp_ex_attr(param_1,(int)param_3 + 0x2bb2);
      *param_4 = 0x2bc4;
      uVar1 = uVar1 | uVar2;
      break;
    case 0xc:
      uVar1 = AK_ISP_get_saturation_attr(param_1,(int)param_3 + 4);
      *param_4 = 0xce;
      break;
    case 0xd:
      uVar1 = AK_ISP_get_contrast_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x40;
      break;
    case 0xe:
      uVar1 = AK_ISP_get_rgb2yuv_attr(param_1,(int)param_3 + 4);
      *param_4 = 6;
      break;
    case 0xf:
      uVar1 = AK_ISP_get_effect_attr(param_1,(int)param_3 + 4);
      *param_4 = 0xe;
      break;
    case 0x10:
      uVar2 = AK_ISP_get_dpc_attr(param_1,(int)param_3 + 4);
      uVar1 = AK_ISP_get_sdpc_attr(param_1,(int)param_3 + 0x58);
      *param_4 = 0x105c;
      uVar1 = uVar1 | uVar2;
      break;
    case 0x11:
      uVar1 = AK_ISP_get_weight_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x104;
      break;
    case 0x12:
      uVar1 = AK_ISP_get_af_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x2e;
      break;
    case 0x13:
      uVar2 = AK_ISP_get_wb_type(param_1,(int)param_3 + 4);
      uVar3 = AK_ISP_get_mwb_attr(param_1,(int)param_3 + 6);
      uVar4 = AK_ISP_get_awb_attr(param_1,(int)param_3 + 0x12);
      uVar1 = AK_ISP_get_awb_ex_attr(param_1,(int)param_3 + 0xcc);
      *param_4 = 0x210;
      uVar1 = uVar3 | uVar2 | uVar4 | uVar1;
      break;
    case 0x14:
      uVar2 = AK_ISP_get_raw_hist_attr(param_1,(int)param_3 + 4);
      uVar3 = AK_ISP_get_rgb_hist_attr(param_1,(int)param_3 + 6);
      uVar4 = AK_ISP_get_yuv_hist_attr(param_1,(int)param_3 + 8);
      uVar5 = AK_ISP_get_exp_type(param_1,(int)param_3 + 10);
      uVar6 = AK_ISP_get_frame_rate(param_1,(int)param_3 + 0xc);
      uVar1 = AK_ISP_get_ae_attr(param_1,(int)param_3 + 0x24);
      *param_4 = 0x114;
      uVar1 = uVar3 | uVar2 | uVar4 | uVar5 | uVar6 | uVar1;
      break;
    case 0x15:
      uVar1 = AK_ISP_get_misc_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x26;
      break;
    case 0x16:
      uVar1 = AK_ISP_get_Y_gamma_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x132;
      break;
    case 0x17:
      uVar1 = AK_ISP_get_hue_attr(param_1,(int)param_3 + 4);
      *param_4 = 0x3e4;
      break;
    default:
      uVar7 = 0x7c3;
      goto LAB_0001cf54;
    case 0x1d:
      uVar1 = AK_ISP_get_frame_rate(param_1,param_3);
      *param_4 = 0x18;
      break;
    case 0x1f:
      memset(auStack_108,0,0xf0);
      uVar1 = AK_ISP_get_ae_attr(param_1,auStack_108);
      memcpy(param_3,auStack_b8,4);
      *param_4 = 4;
    }
    if (local_10c < 0x18) {
      memcpy(param_3,&local_10c,2);
      memcpy((void *)((int)param_3 + 2),param_4,2);
      return uVar1;
    }
  }
  return uVar1;
}



undefined4 isp_get_statinfo(int param_1,undefined4 param_2,int param_3,int *param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 < 2) {
    if (param_4 == (int *)0x0 || param_3 == 0) {
      ak_print(10,1,"[%s:%d] param err\n","isp_get_statinfo",0x8c5);
      uVar1 = 0xffffffff;
    }
    else {
      switch(param_2) {
      case 0x18:
        AK_ISP_get_3d_nr_stat_info(param_1,param_3);
        *param_4 = 0x608;
        return 0;
      case 0x19:
        AK_ISP_get_ae_run_info(param_1,param_3);
        *param_4 = 0x24;
        AK_ISP_get_raw_hist_stat_info(param_1,param_3 + 0x24);
        iVar2 = *param_4;
        *param_4 = iVar2 + 0x404;
        AK_ISP_get_rgb_hist_stat_info(param_1,param_3 + iVar2 + 0x404);
        iVar2 = *param_4;
        *param_4 = iVar2 + 0x404;
        AK_ISP_get_yuv_hist_stat_info(param_1,param_3 + iVar2 + 0x404);
        *param_4 = *param_4 + 0x404;
        return 0;
      case 0x1a:
        AK_ISP_get_af_stat_info(param_1,param_3);
        *param_4 = 0x14;
        return 0;
      case 0x1b:
        Ak_ISP_get_awb_stat_info(param_1,param_3);
        *param_4 = 0xc4;
        return 0;
      default:
        uVar1 = 0xffffffff;
        break;
      case 0x1e:
        AK_ISP_get_rgb_hist_stat_info(param_1,param_3);
        uVar1 = 0;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_statinfo",0x8bf,param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 isp_set_sensor_value(int param_1,undefined2 param_2,undefined2 param_3)

{
  undefined4 uVar1;
  undefined2 local_c;
  undefined2 local_a;
  
  if (param_1 < 2) {
    local_c = param_2;
    local_a = param_3;
    uVar1 = Ak_ISP_Sensor_Set_Reg(param_1,&local_c);
    return uVar1;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_sensor_value",0x8fd,param_1);
  return 0xffffffff;
}



undefined4 isp_get_sensor_value(int param_1,undefined2 param_2,undefined2 *param_3)

{
  undefined4 uVar1;
  undefined2 local_c;
  undefined2 local_a;
  
  if (param_1 < 2) {
    local_a = 0;
    local_c = param_2;
    uVar1 = Ak_ISP_Sensor_Get_Reg(param_1,&local_c);
    *param_3 = local_a;
    return uVar1;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_sensor_value",0x916,param_1);
  return 0xffffffff;
}



undefined4 isp_get_sensor_id(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    uVar1 = vi_dev_get_sensor_id();
    return uVar1;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_sensor_id",0x92f,param_1);
  return 0xffffffff;
}



undefined4 isp_get_effect(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    if (param_3 == (undefined4 *)0x0) {
      uVar1 = 0xffffffff;
    }
    else {
      switch(param_2) {
      case 0:
        *param_3 = *(undefined4 *)(&DAT_0003a218 + param_1 * 0x18);
        return 0;
      case 1:
        *param_3 = *(undefined4 *)(&DAT_0003a21c + param_1 * 0x18);
        return 0;
      case 2:
        *param_3 = *(undefined4 *)(&DAT_0003a220 + param_1 * 0x18);
        return 0;
      case 3:
        *param_3 = *(undefined4 *)(&DAT_0003a224 + param_1 * 0x18);
        return 0;
      case 4:
        *param_3 = *(undefined4 *)(&DAT_0003a228 + param_1 * 0x18);
        return 0;
      case 5:
        uVar1 = 0;
        *param_3 = *(undefined4 *)(&DAT_0003a22c + param_1 * 0x18);
        break;
      default:
        ak_print(10,1,"[%s:%d] error type: %d\n","isp_get_effect",0x9da,param_2);
        return 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_effect",0x9ba,param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 isp_set_effect(int param_1,undefined4 param_2,int param_3)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  int extraout_r2;
  short sVar8;
  uint uVar9;
  int *piVar10;
  bool bVar11;
  ulonglong uVar12;
  undefined4 local_110;
  undefined4 local_10c;
  undefined2 local_108;
  undefined4 local_ec;
  int local_e8;
  uint auStack_e4 [8];
  uint auStack_c4 [42];
  
  if (param_1 < 2) {
    if (param_3 + 0x32U < 0x65) {
      switch(param_2) {
      case 0:
        local_110 = 0;
        local_10c = 0;
        local_108 = 0;
        AK_ISP_get_effect_attr(param_1,&local_110,AK_ISP_get_effect_attr);
        iVar5 = (int)local_10c._2_2_ - *(int *)(&DAT_0003a218 + param_1 * 0x18);
        iVar4 = param_3 + iVar5;
        if (iVar4 < 0x100) {
          if (iVar4 < -0x100) {
            param_3 = -0x100 - iVar5;
            iVar4 = param_3 + iVar5;
          }
        }
        else {
          param_3 = 0xff - iVar5;
          iVar4 = param_3 + iVar5;
        }
        *(int *)(&DAT_0003a218 + param_1 * 0x18) = param_3;
        local_10c = CONCAT22((short)iVar4,(undefined2)local_10c);
        AK_ISP_set_effect_attr
                  (param_1,&local_110,&DAT_00039394 + param_1 * 0x18,AK_ISP_set_effect_attr);
        uVar3 = 0;
        break;
      case 1:
        if (*(int *)(&DAT_0003f9dc + param_1 * 4) == 0) {
          iVar5 = param_1 * 0x10;
          AK_ISP_get_ae_attr(param_1,&DAT_0003f9e4 + param_1 * 0xf0);
          *(undefined4 *)(&DAT_0003f9dc + param_1 * 4) = 1;
        }
        else {
          iVar5 = param_1 << 4;
        }
        memset(&local_110,0,0xf0);
        iVar4 = 0x1dc10;
        AK_ISP_get_ae_attr(param_1,&local_110);
        uVar9 = *(uint *)(&DAT_0003fa0c + (iVar5 - param_1) * 0x10);
        iVar5 = (iVar5 - param_1) * 0x10;
        iVar2 = *(int *)(&DAT_0003fa08 + iVar5);
        local_e8 = param_3 + uVar9;
        bVar11 = local_e8 < 0;
        if (bVar11) {
          local_e8 = 0;
          iVar4 = -uVar9;
        }
        if (!bVar11) {
          iVar4 = param_3;
        }
        *(int *)(&DAT_0003a21c + param_1 * 0x18) = iVar4;
        uVar12 = FUN_000211a0(local_e8 * iVar2,uVar9);
        local_ec = (undefined4)uVar12;
        piVar10 = (int *)(&DAT_0003fa0c + iVar5);
        puVar6 = auStack_e4;
        do {
          piVar10 = piVar10 + 1;
          puVar7 = puVar6 + 1;
          *puVar6 = param_3 + *piVar10 & ~(param_3 + *piVar10 >> 0x1f);
          puVar6 = puVar7;
        } while (puVar7 != auStack_c4);
        AK_ISP_set_ae_attr(param_1,&local_110,puVar7,AK_ISP_set_ae_attr);
        uVar3 = 0;
        break;
      case 2:
        local_110 = 0;
        local_10c = 0;
        local_108 = 0;
        if (*(int *)(&DAT_0003fbc4 + param_1 * 4) == 0) {
          AK_ISP_get_effect_attr(param_1,&DAT_0003fbcc + param_1 * 10);
          *(undefined4 *)(&DAT_0003fbc4 + param_1 * 4) = 1;
        }
        AK_ISP_get_effect_attr(param_1,&local_110);
        sVar1 = *(short *)(&DAT_0003fbd0 + param_1 * 10);
        iVar5 = (int)sVar1;
        if (param_3 < 0) {
          iVar4 = param_3;
          if (param_3 + iVar5 < 0) {
            iVar4 = -iVar5;
          }
        }
        else {
          iVar4 = param_3 * 3;
          if (0xff < iVar5 + param_3 * 3) {
            iVar4 = 0xff - iVar5;
          }
        }
        *(int *)(&DAT_0003a220 + param_1 * 0x18) = param_3;
        local_10c = CONCAT22(local_10c._2_2_,(short)iVar4 + sVar1);
        AK_ISP_set_effect_attr(param_1,&local_110);
        uVar3 = 0;
        break;
      case 3:
        iVar5 = *(int *)(&DAT_0003fbc4 + param_1 * 4);
        local_110 = 0;
        local_10c = 0;
        local_108 = 0;
        if (iVar5 == 0) {
          AK_ISP_get_effect_attr(param_1,&DAT_0003fbcc + param_1 * 10,0,AK_ISP_get_effect_attr);
          *(undefined4 *)(&DAT_0003fbc4 + param_1 * 4) = 1;
          iVar5 = extraout_r2;
        }
        iVar4 = param_1 * 10;
        if ((*(ushort *)(&DAT_0003fbcc + iVar4) & 1) == 0) {
          AK_ISP_get_effect_attr(param_1,&local_110,iVar5,AK_ISP_get_effect_attr);
          uVar9 = (uint)*(ushort *)(&DAT_0003fbcc + iVar4);
          sVar1 = *(short *)(&DAT_0003fbce + iVar4);
          iVar5 = (int)sVar1;
          if ((int)(param_3 + uVar9) < 0x100) {
            if ((int)(param_3 + uVar9) < 0) {
              param_3 = -uVar9;
            }
          }
          else {
            param_3 = 0xff - uVar9;
          }
          iVar4 = iVar5 + param_3 * -2;
          if (iVar4 < -0x80) {
            param_3 = (iVar5 + 0x80) / 2;
          }
          else if (0x7f < iVar4) {
            param_3 = (iVar5 + -0x7f) / 2;
          }
          sVar8 = (short)(uVar9 + param_3);
          if (((uVar9 + param_3) * 0x10000 & 0x10000) != 0) {
            sVar8 = sVar8 + -1;
          }
          *(int *)(&DAT_0003a224 + param_1 * 0x18) = param_3;
          local_110 = CONCAT22(sVar1 + (short)param_3 * -2,sVar8);
          AK_ISP_set_effect_attr(param_1,&local_110);
          uVar3 = 0;
        }
        else {
          ak_print(10,3,"[%s:%d] auto ygain selected, not support contrast set!\n","set_contrast",
                   0x485);
          uVar3 = 0;
        }
        break;
      case 4:
        FUN_0001c544(param_1,param_3);
        return 0;
      case 5:
        FUN_0001c170(param_1,param_3);
        uVar3 = 0;
        break;
      default:
        ak_print(10,1,"[%s:%d] error type: %d\n","isp_set_effect",0xa0d,param_2);
        return 0xffffffff;
      }
    }
    else {
      ak_print(10,1,"[%s:%d] value range [-50, 50], cur value: %d\n","isp_set_effect",0x9f3,param_3)
      ;
      uVar3 = 0xffffffff;
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_effect",0x9ed,param_1);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



undefined4 isp_get_hz(void)

{
  return DAT_00035134;
}



undefined4 isp_set_sensor_fps(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  local_c = param_2;
  if (param_1 < 2) {
    ak_print(10,3,"[%s:%d] set sensor fps: %d\n","isp_set_sensor_fps",0xa49,param_2);
    uVar1 = Ak_ISP_Set_Sensor_Fps(param_1,&local_c);
    return uVar1;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_sensor_fps",0xa45,param_1);
  return 0xffffffff;
}



int FUN_0001dec8(int param_1,int param_2)

{
  int iVar1;
  char acStack_50 [64];
  
  if (param_1 < 2) {
    if (param_2 == 0xf && DAT_00035134 == 0x32) {
      if (*(int *)(&DAT_00035414 + param_1 * 0x14) == 0) {
        param_2 = 0xf;
      }
      else {
        param_2 = 0xe;
      }
    }
    iVar1 = isp_set_sensor_fps(param_1,param_2);
    if (iVar1 != 0) {
      ak_print(10,3,"[%s:%d] set dev:%d fps:%d %s\n","set_fps",0xec,param_1,param_2,"failed");
      return iVar1;
    }
    ak_print(10,3,"[%s:%d] set dev:%d fps:%d %s\n","set_fps",0xec,param_1,param_2,&DAT_00024414);
    memset(acStack_50,0,0x40);
    memset(acStack_50,0,0x40);
    snprintf(acStack_50,0x40,"sensor_fps=%d",param_2);
    ak_debug_info(10,1,acStack_50);
    iVar1 = 0;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","set_fps",0xe0,param_1);
    iVar1 = -1;
  }
  return iVar1;
}



undefined4 FUN_0001e048(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_5c;
  uint local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  undefined4 local_2c;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_5c = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","init_fps_info",0x21f,param_1);
    return 0xffffffff;
  }
  ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
  uVar2 = isp_get_attr(param_1,0x1d,&local_58,&local_5c);
  if (uVar2 != 0) {
    ak_print(10,1,"[%s:%d] get attr failed\n","init_fps_info",0x226);
    uVar4 = 0xffffffff;
    goto LAB_0001e0ec;
  }
  iVar1 = param_1 * 0x38;
  memset(&DAT_000353a4 + iVar1,0,0x38);
  if ((local_58 & 0xffffff00) == 0) {
    *(undefined4 *)(&DAT_000353d4 + iVar1) = 2;
    iVar3 = FUN_0001ba7c(param_1,(byte *)&local_58);
    if (iVar3 == 0) {
      ak_print(10,4,"[%s:%d] hight light fps: %u\n","init_fps_info",600,local_58);
      iVar3 = FUN_0001dec8(param_1,local_58);
      if (iVar3 != 0) goto LAB_0001e23c;
      *(uint *)(&DAT_000353a8 + iVar1) = local_58;
      *(uint *)(&DAT_000353b4 + iVar1) = local_58;
      *(undefined4 *)(&DAT_000353ac + iVar1) = local_4c;
      *(undefined4 *)(&DAT_000353b8 + iVar1) = local_48;
      *(undefined4 *)(&DAT_000353c0 + iVar1) = local_54;
      *(undefined4 *)(&DAT_000353c4 + iVar1) = local_50;
      *(undefined4 *)(&DAT_000353c8 + iVar1) = local_44;
      *(undefined4 *)(&DAT_000353a4 + iVar1) = 1;
LAB_0001e2bc:
      uVar4 = 0;
      *(undefined4 *)(&DAT_000353d8 + param_1 * 0x38) = 1;
      goto LAB_0001e0ec;
    }
    uVar4 = 0x254;
LAB_0001e228:
    ak_print(10,1,"[%s:%d] failed\n","init_fps_info",uVar4);
  }
  else {
    *(undefined4 *)(&DAT_000353d4 + iVar1) = 3;
    memcpy(&local_40,&local_58,0x18);
    iVar3 = FUN_0001ba7c(param_1,(byte *)&local_40);
    if (iVar3 != 0) {
      uVar4 = 0x236;
      goto LAB_0001e228;
    }
    ak_print(10,4,"[%s:%d] hight light fps: %d\n","init_fps_info",0x23a,local_40 & 0xff);
    iVar3 = FUN_0001dec8(param_1,local_40 & 0xff);
    if (iVar3 == 0) {
      *(uint *)(&DAT_000353d0 + iVar1) = local_3c >> 0x18;
      *(uint *)(&DAT_000353a8 + iVar1) = local_40 & 0xff;
      *(uint *)(&DAT_000353b4 + iVar1) = local_40 & 0xff;
      *(uint *)(&DAT_000353b0 + iVar1) = local_3c >> 0x10 & 0xff;
      *(uint *)(&DAT_000353ac + iVar1) = local_34 & 0xff;
      *(uint *)(&DAT_000353b8 + iVar1) = local_30 & 0xffff;
      *(uint *)(&DAT_000353c0 + iVar1) = local_3c & 0xffff;
      *(uint *)(&DAT_000353bc + iVar1) = local_38 >> 0x10;
      *(uint *)(&DAT_000353c4 + iVar1) = local_40 >> 0x10 & 0xff;
      *(uint *)(&DAT_000353c8 + iVar1) = local_34 >> 8 & 0xff;
      *(uint *)(&DAT_000353cc + iVar1) = local_38 & 0xff;
      *(undefined4 *)(&DAT_000353a4 + iVar1) = 1;
      goto LAB_0001e2bc;
    }
  }
LAB_0001e23c:
  uVar4 = 0xffffffff;
LAB_0001e0ec:
  ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
  return uVar4;
}



uint isp_set_attr(int param_1,uint param_2,void *param_3,size_t param_4)

{
  ushort uVar1;
  int iVar2;
  void *__dest;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  
  if (param_1 < 2) {
    if (param_3 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] param err\n","isp_set_attr",0x7e5);
      uVar10 = 0xffffffff;
    }
    else if ((param_2 < 0x18) && (*(ushort *)(Isp_Struct_len + param_2 * 2) != param_4)) {
      ak_print(10,1,"[%s:%d] size err\n","isp_set_attr",0x7ec);
      uVar10 = 0xffffffff;
    }
    else {
      __dest = malloc(param_4);
      memcpy(__dest,param_3,param_4);
      switch(param_2) {
      case 0:
        uVar10 = AK_ISP_set_blc_attr(param_1,(int)__dest + 4);
        break;
      case 1:
        uVar10 = AK_ISP_set_lsc_attr(param_1,(int)__dest + 4);
        break;
      case 2:
        uVar10 = AK_ISP_set_raw_lut_attr(param_1,(int)__dest + 4);
        break;
      case 3:
        uVar3 = AK_ISP_set_nr1_attr(param_1,(int)__dest + 4);
        uVar4 = AK_ISP_set_nr2_attr(param_1,(int)__dest + 0x6fa);
        uVar10 = AK_ISP_set_uvnr_attr(param_1,(int)__dest + 0x940);
        uVar10 = uVar4 | uVar3 | uVar10;
        break;
      case 4:
        uVar10 = AK_ISP_set_3d_nr_attr(param_1,(int)__dest + 4);
        break;
      case 5:
        uVar10 = AK_ISP_set_gb_attr(param_1,(int)__dest + 4);
        break;
      case 6:
        uVar10 = AK_ISP_set_demo_attr(param_1,(int)__dest + 4);
        break;
      case 7:
        uVar10 = AK_ISP_set_rgb_gamma_attr(param_1,(int)__dest + 4);
        break;
      case 8:
        uVar10 = AK_ISP_set_ccm_attr(param_1,(int)__dest + 4);
        break;
      case 9:
        uVar10 = AK_ISP_set_fcs_attr(param_1,(int)__dest + 4);
        break;
      case 10:
        uVar10 = AK_ISP_set_wdr_attr(param_1,(int)__dest + 4);
        break;
      case 0xb:
        uVar3 = AK_ISP_set_sharp_attr(param_1,(int)__dest + 4);
        uVar10 = AK_ISP_set_sharp_ex_attr(param_1,(int)__dest + 0x2bb2);
        uVar10 = uVar10 | uVar3;
        break;
      case 0xc:
        uVar10 = AK_ISP_set_saturation_attr(param_1,(int)__dest + 4);
        break;
      case 0xd:
        uVar10 = AK_ISP_set_contrast_attr(param_1,(int)__dest + 4);
        break;
      case 0xe:
        uVar10 = AK_ISP_set_rgb2yuv_attr(param_1,(int)__dest + 4);
        break;
      case 0xf:
        uVar10 = AK_ISP_set_effect_attr(param_1,(int)__dest + 4);
        break;
      case 0x10:
        uVar3 = AK_ISP_set_dpc_attr(param_1,(int)__dest + 4);
        uVar10 = AK_ISP_set_sdpc_attr(param_1,(int)__dest + 0x58);
        uVar10 = uVar10 | uVar3;
        break;
      case 0x11:
        uVar10 = AK_ISP_set_weight_attr(param_1,(int)__dest + 4);
        break;
      case 0x12:
        uVar10 = AK_ISP_set_af_attr(param_1,(int)__dest + 4);
        break;
      case 0x13:
        uVar3 = AK_ISP_set_wb_type(param_1,(int)__dest + 4);
        uVar4 = AK_ISP_set_mwb_attr(param_1,(int)__dest + 6);
        uVar5 = AK_ISP_set_awb_attr(param_1,(int)__dest + 0x12);
        uVar10 = AK_ISP_set_awb_ex_attr(param_1,(int)__dest + 0xcc);
        uVar10 = uVar4 | uVar3 | uVar5 | uVar10;
        break;
      case 0x14:
        uVar3 = AK_ISP_set_raw_hist_attr(param_1,(int)__dest + 4);
        uVar4 = AK_ISP_set_rgb_hist_attr(param_1,(int)__dest + 6);
        uVar5 = AK_ISP_set_yuv_hist_attr(param_1,(int)__dest + 8);
        uVar6 = AK_ISP_set_exp_type(param_1,(int)__dest + 10);
        uVar7 = AK_ISP_set_frame_rate(param_1,(int)__dest + 0xc);
        uVar10 = AK_ISP_set_ae_attr(param_1,(int)__dest + 0x24);
        uVar9 = *(undefined4 *)((int)__dest + 0x6c);
        uVar8 = *(undefined4 *)((int)__dest + 0x44);
        iVar2 = param_1 * 0x14;
        *(undefined4 *)(&DAT_00035418 + iVar2) = *(undefined4 *)((int)__dest + 0x28);
        *(undefined4 *)(&DAT_0003541c + iVar2) = uVar8;
        *(undefined4 *)(&DAT_00035420 + iVar2) = uVar9;
        *(undefined4 *)(&DAT_00035424 + iVar2) = uVar9;
        uVar10 = uVar4 | uVar3 | uVar5 | uVar6 | uVar7 | uVar10;
        FUN_0001e048(param_1);
        break;
      case 0x15:
        uVar10 = AK_ISP_set_misc_attr(param_1,(int)__dest + 4);
        uVar1 = *(ushort *)((int)__dest + 0x1c);
        *(uint *)(&DAT_0003fbe0 + param_1 * 8) = (uint)*(ushort *)((int)__dest + 0x1a);
        *(uint *)(&DAT_0003fbe4 + param_1 * 8) = (uint)uVar1;
        break;
      case 0x16:
        uVar10 = AK_ISP_set_Y_gamma_attr(param_1,(int)__dest + 4);
        break;
      case 0x17:
        uVar10 = AK_ISP_set_hue_attr(param_1,(int)__dest + 4);
        break;
      default:
        ak_print(10,1,"[%s:%d] param err\n","isp_set_attr",0x8a7);
        uVar10 = 0xffffffff;
        break;
      case 0x1d:
        AK_ISP_set_frame_rate(param_1,__dest);
        uVar10 = 0xffffffff;
      }
      free(__dest);
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_attr",0x7df,param_1);
    uVar10 = 0xffffffff;
  }
  return uVar10;
}



int isp_module_init(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  ushort local_142;
  uint local_140;
  ushort local_13c [2];
  int local_138;
  undefined1 auStack_118 [244];
  
  uVar6 = 0;
  local_142 = 0;
  local_140 = param_3;
  uVar3 = ak_get_chip_id();
  ak_print(10,3,"[%s:%d] chipid:0x%lx !\n","isp_module_init",0x5f9,uVar3);
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_module_init",0x5fd,param_1);
    return -1;
  }
  iVar1 = param_1 * 4;
  memset(&DAT_00035414 + param_1 * 0x14,0,0x14);
  memset(&DAT_0003a218 + param_1 * 0x18,0,0x18);
  iVar4 = isp_module_check_cfg(param_2,&local_140);
  if (iVar4 < 0) {
    return iVar4;
  }
  iVar8 = 0;
  puVar7 = Isp_Struct_len;
  sVar5 = 1;
  do {
    uVar2 = uVar6 & 0xffff;
    if (uVar6 == 0xb) {
      memcpy((void *)(param_1 * 0x2bae + 0x3a250),(void *)(param_2 + iVar8 + 4),0x2bae);
      *(undefined4 *)(&DAT_0003a248 + iVar1) = 1;
LAB_0001ea64:
      isp_set_attr(param_1,uVar6,(void *)(param_2 + iVar8),(uint)*(ushort *)puVar7);
      iVar8 = iVar8 + (uint)*(ushort *)puVar7;
      if (sVar5 == 0x18) {
        memcpy(&local_142,(void *)(param_2 + iVar8 + 2),2);
        local_138 = param_2 + iVar8 + 4;
        local_13c[0] = local_142 >> 2;
        vi_dev_load_sensor_conf(param_1,local_13c,vi_dev_load_sensor_conf);
        ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
        FUN_0001c7b8(param_1);
        ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
        return iVar4;
      }
    }
    else {
      if (uVar2 == 10) {
        memcpy((void *)(param_1 * 0x26ea + 0x35444),(void *)(param_2 + iVar8 + 4),0x26ea);
        *(undefined4 *)(&DAT_0003543c + iVar1) = 1;
        goto LAB_0001ea64;
      }
      if (uVar2 == 0x14) {
        memcpy(local_13c,(void *)(param_2 + iVar8),0x114);
        memcpy(&DAT_0003f9e4 + param_1 * 0xf0,auStack_118,0xf0);
        *(undefined4 *)(&DAT_0003f9dc + iVar1) = 1;
      }
      else {
        if (uVar2 != 0xf) goto LAB_0001ea64;
        memcpy(&DAT_0003fbcc + param_1 * 10,(void *)(param_2 + iVar8 + 4),10);
        *(undefined4 *)(&DAT_0003fbc4 + iVar1) = 1;
      }
      isp_set_attr(param_1,uVar6,(void *)(param_2 + iVar8),(uint)*(ushort *)puVar7);
      iVar8 = iVar8 + (uint)*(ushort *)puVar7;
    }
    sVar5 = sVar5 + 1;
    uVar6 = uVar6 + 1;
    puVar7 = (undefined1 *)((int)puVar7 + 2);
  } while( true );
}



// WARNING: Type propagation algorithm not settling

int isp_switch_mode(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  undefined1 *puVar7;
  void *__src;
  uint local_14c [2];
  undefined4 local_144;
  undefined2 local_140;
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  undefined1 auStack_118 [244];
  
  uVar6 = 0;
  local_14c[1] = 0;
  local_144 = 0;
  local_140 = 0;
  local_14c[0] = param_3;
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_switch_mode",0x94a,param_1);
    return -1;
  }
  iVar5 = isp_module_check_cfg(param_2,local_14c);
  if (-1 < iVar5) {
    puVar7 = Isp_Struct_len;
    iVar5 = 0;
    bVar4 = false;
    do {
      uVar1 = uVar6 & 0xffff;
      if (uVar6 == 0xb) {
        memcpy((void *)(param_1 * 0x2bae + 0x3a250),(void *)(param_2 + iVar5 + 4),0x2bae);
        *(undefined4 *)(&DAT_0003a248 + param_1 * 4) = 1;
LAB_0001ed48:
        isp_set_attr(param_1,uVar6,(void *)(param_2 + iVar5),(uint)*(ushort *)puVar7);
LAB_0001ed5c:
        uVar2 = *(ushort *)(Isp_Struct_len + uVar6 * 2);
        bVar3 = bVar4;
      }
      else {
        if (uVar1 == 10) {
          memcpy((void *)(param_1 * 0x26ea + 0x35444),(void *)(param_2 + iVar5 + 4),0x26ea);
          *(undefined4 *)(&DAT_0003543c + param_1 * 4) = 1;
          goto LAB_0001ed48;
        }
        if (uVar1 == 0x14) {
          memcpy(&local_13c,(void *)(param_2 + iVar5),0x114);
          memcpy(&DAT_0003f9e4 + param_1 * 0xf0,auStack_118,0xf0);
          *(undefined4 *)(&DAT_0003f9dc + param_1 * 4) = 1;
          goto LAB_0001ed48;
        }
        if (uVar1 != 0xf) {
          if (uVar6 != 0x15) goto LAB_0001ed48;
          goto LAB_0001ed5c;
        }
        __src = (void *)(param_2 + iVar5 + 4);
        memcpy(&DAT_0003fbcc + param_1 * 10,__src,10);
        *(undefined4 *)(&DAT_0003fbc4 + param_1 * 4) = 1;
        memcpy(local_14c + 1,__src,10);
        bVar3 = true;
        uVar2 = Isp_Struct_len._30_2_;
        if ((short)local_144 == 0) goto LAB_0001ed48;
      }
      iVar5 = iVar5 + (uint)uVar2;
      uVar6 = uVar6 + 1;
      puVar7 = (undefined1 *)((int)puVar7 + 2);
      bVar4 = bVar3;
    } while (uVar6 != 0x18);
    if (bVar3) {
      AK_ISP_set_effect_attr(param_1,local_14c + 1);
    }
    memcpy(&local_13c,&DAT_0003a218 + param_1 * 0x18,0x18);
    memset(&DAT_0003a218 + param_1 * 0x18,0,0x18);
    isp_set_effect(param_1,0,local_13c);
    isp_set_effect(param_1,1,local_138);
    isp_set_effect(param_1,2,local_134);
    isp_set_effect(param_1,3,local_130);
    isp_set_effect(param_1,4,local_12c);
    FUN_0001e048(param_1);
    ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
    FUN_0001c7b8(param_1);
    ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
    iVar5 = 0;
  }
  return iVar5;
}



undefined4 isp_set_hz(int param_1,undefined4 param_2)

{
  if (param_1 < 2) {
    DAT_00035134 = param_2;
    ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
    FUN_0001dec8(param_1,*(int *)(&DAT_000353a8 + param_1 * 0x38));
    FUN_0001c7b8(param_1);
    ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
    return 0;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_hz",0xa2c,param_1);
  return 0xffffffff;
}



int isp_get_sensor_fps(int param_1)

{
  int iVar1;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_sensor_fps",0xa57,param_1);
    return -1;
  }
  iVar1 = Ak_ISP_Get_Sensor_Fps();
  if (iVar1 != 0) {
    return iVar1;
  }
  ak_print(10,1,"[%s:%d] Error, fps is 0, we use default 25\n","isp_get_sensor_fps",0xa5e);
  return 0x19;
}



undefined4 isp_get_work_scene(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    uVar1 = Ak_ISP_Get_Work_Scene();
    return uVar1;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_work_scene",0xa6f,param_1);
  return 0xffffffff;
}



undefined4 isp_set_flip_mirror(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    if (param_2 == (undefined4 *)0x0) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = param_2[1];
      *(undefined4 *)(&DAT_0003fbe0 + param_1 * 8) = *param_2;
      *(undefined4 *)(&DAT_0003fbe4 + param_1 * 8) = uVar1;
      uVar1 = Ak_ISP_Set_Flip_Mirror();
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_flip_mirror",0xa81,param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 isp_get_flip_mirror(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_flip_mirror",0xa99,param_1);
    return 0xffffffff;
  }
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0;
    uVar2 = *(undefined4 *)(&DAT_0003fbe4 + param_1 * 8);
    *param_2 = *(undefined4 *)(&DAT_0003fbe0 + param_1 * 8);
    param_2[1] = uVar2;
  }
  return uVar1;
}



undefined4 isp_set_main_mask_area(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_set_main_chan_mask_area();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_main_mask_area",0xab1,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_get_main_mask_area(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_get_main_chan_mask_area();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_main_mask_area",0xac9,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_set_sub_mask_area(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_set_sub_chan_mask_area();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_sub_mask_area",0xae1,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_get_sub_mask_area(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_get_sub_chan_mask_area();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_sub_mask_area",0xaf9,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_set_mask_color(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_set_mask_color();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_mask_color",0xb11,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_get_mask_color(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      iVar1 = AK_ISP_get_mask_color();
      uVar2 = 0;
      if (iVar1 != 0) {
        uVar2 = 0xffffffff;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_mask_color",0xb29,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined4 isp_get_force_anti_flicker_flag(int param_1,uint *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    if (param_2 == (uint *)0x0) {
      ak_print(10,1,"[%s:%d] force_flag is null!\n","isp_get_force_anti_flicker_flag",0xb40);
      uVar1 = 0xffffffff;
    }
    else if (param_3 == (undefined4 *)0x0) {
      ak_print(10,1,"[%s:%d] sub_antiflicker_value is null!\n","isp_get_force_anti_flicker_flag",
               0xb46);
      uVar1 = 0xffffffff;
    }
    else {
      *param_2 = (uint)(0 < *(int *)(&DAT_00035414 + param_1 * 0x14));
      uVar1 = 0;
      *param_3 = *(undefined4 *)(&DAT_00035424 + param_1 * 0x14);
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_force_anti_flicker_flag",0xb3a,param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 isp_set_force_anti_flicker_flag(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_110 [4];
  undefined4 local_10c;
  undefined4 local_f0;
  int local_c8;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_set_force_anti_flicker_flag",0xb5a,param_1);
    return 0xffffffff;
  }
  iVar1 = AK_ISP_get_ae_attr(param_1,auStack_110);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  if (param_3 == -1) {
    *(int *)(&DAT_00035424 + param_1 * 0x14) = local_c8;
    if (param_2 != 0) {
      uVar2 = 1;
      local_10c = local_f0;
      goto LAB_0001f6dc;
    }
  }
  else {
    if (param_2 != 0) {
      *(int *)(&DAT_00035424 + param_1 * 0x14) = param_3;
      uVar2 = 2;
      local_c8 = param_3;
      goto LAB_0001f6dc;
    }
    *(int *)(&DAT_00035424 + param_1 * 0x14) = param_3;
  }
  iVar1 = param_1 * 0x14;
  local_10c = *(undefined4 *)(&DAT_00035418 + iVar1);
  local_c8 = *(int *)(&DAT_00035420 + iVar1);
  uVar2 = 0;
  if (*(int *)(&DAT_0003541c + iVar1) == 1) {
    local_f0 = 1;
  }
LAB_0001f6dc:
  iVar1 = AK_ISP_set_ae_attr(param_1,auStack_110);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  ak_print(10,4,"[%s:%d] force_flag=%d\n","isp_set_force_anti_flicker_flag",0xb8e,param_2);
  *(undefined4 *)(&DAT_00035414 + param_1 * 0x14) = uVar2;
  ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
  FUN_0001dec8(param_1,*(int *)(&DAT_000353a8 + param_1 * 0x38));
  FUN_0001c7b8(param_1);
  ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
  return 0;
}



undefined4 isp_get_cur_lum_factor(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_get_cur_lum_factor",0xba4,param_1);
    return 0xffffffff;
  }
  iVar1 = param_1 * 0x38;
  if (*(int *)(&DAT_000353d8 + iVar1) != 1) {
    ak_print(10,1,"[%s:%d] init fps info failed\n","isp_get_cur_lum_factor",0xbaa);
    return 0xffffffff;
  }
  if (*(int *)(&DAT_000353c0 + iVar1) < 1) {
    ak_print(10,1,"[%s:%d] high_fps_exp_time error\n","isp_get_cur_lum_factor",0xbb0);
    return 0xffffffff;
  }
  iVar2 = FUN_0001c89c(param_1,&local_20);
  if (iVar2 != 0) {
    ak_print(10,1,"[%s:%d] get AE stat info failed\n","isp_get_cur_lum_factor",2999);
    return 0xffffffff;
  }
  iVar2 = *(int *)(&DAT_000353a8 + iVar1);
  if (iVar2 == *(int *)(&DAT_000353b4 + iVar1)) {
    uVar3 = *(uint *)(&DAT_000353c0 + iVar1);
  }
  else if (iVar2 == *(int *)(&DAT_000353ac + iVar1)) {
    uVar3 = *(uint *)(&DAT_000353b8 + iVar1);
  }
  else {
    if (iVar2 != *(int *)(&DAT_000353b0 + iVar1)) goto LAB_0001f8c8;
    uVar3 = *(uint *)(&DAT_000353bc + iVar1);
  }
  if (uVar3 != 0) {
    uVar4 = FUN_00021268((local_18 * (local_20 * local_1c >> 8) >> 8) * local_14,uVar3);
    return (int)uVar4;
  }
LAB_0001f8c8:
  ak_print(10,1,"[%s:%d] get fps_exp_time error\n","isp_get_cur_lum_factor",0xbd1);
  return 0xffffffff;
}



undefined4 ak_vpss_get_fps_ctrl_stat(int param_1,uint *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint extraout_r0;
  uint uVar4;
  int iVar5;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_fps_ctrl_stat",0xbeb,param_1);
    return 0x101;
  }
  if (param_3 == (int *)0x0 || param_2 == (uint *)0x0) {
    ak_print(10,1,"[%s:%d] param is null!\n","ak_vpss_get_fps_ctrl_stat",0xbf1);
    return 0x100;
  }
  uVar4 = 0;
  iVar1 = param_1 * 0x38;
  if (*(int *)(&DAT_000353d8 + iVar1) == 0) {
    ak_print(10,5,"[%s:%d] dev:%d fps cfg is not init!\n","ak_vpss_get_fps_ctrl_stat",0xbf7,param_1)
    ;
    return 0x105;
  }
  ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
  iVar3 = FUN_0001c89c(param_1,&local_38);
  if (iVar3 != 0) {
    iVar3 = *(int *)(&DAT_000353a8 + iVar1);
    goto LAB_0001fb30;
  }
  iVar2 = local_30 * (local_38 * local_34 >> 8) >> 0x10;
  if (*(int *)(&DAT_000353d4 + iVar1) == 3) {
    iVar5 = *(int *)(&DAT_000353a8 + iVar1);
    if (iVar5 == *(int *)(&DAT_000353b4 + iVar1)) {
      if ((uint)(*(int *)(&DAT_000353c4 + iVar1) * *(int *)(&DAT_000353c0 + iVar1)) <=
          (uint)(iVar2 * local_2c) &&
          iVar2 * local_2c - *(int *)(&DAT_000353c4 + iVar1) * *(int *)(&DAT_000353c0 + iVar1) != 0)
      {
LAB_0001fc68:
        uVar4 = 3;
        iVar3 = *(int *)(&DAT_000353b0 + param_1 * 0x38);
        goto LAB_0001fbcc;
      }
    }
    else if (iVar5 == *(int *)(&DAT_000353ac + iVar1)) {
      FUN_00021268(*(int *)(&DAT_000353bc + param_1 * 0x38) *
                   *(int *)(&DAT_000353cc + param_1 * 0x38) * 9,10);
      if ((uint)(local_2c * iVar2) < extraout_r0) goto LAB_0001fc68;
    }
    else {
      uVar4 = iVar2 * local_2c;
      if (uVar4 < (uint)((*(int *)(&DAT_000353c4 + iVar1) * *(int *)(&DAT_000353c0 + iVar1) * 9) /
                        10)) goto LAB_0001fc28;
      if ((uint)(*(int *)(&DAT_000353cc + param_1 * 0x38) * *(int *)(&DAT_000353bc + param_1 * 0x38)
                ) <= uVar4 &&
          uVar4 - *(int *)(&DAT_000353cc + param_1 * 0x38) *
                  *(int *)(&DAT_000353bc + param_1 * 0x38) != 0) goto LAB_0001fbbc;
    }
  }
  else {
    iVar3 = *(int *)(&DAT_000353ac + iVar1);
    iVar5 = *(int *)(&DAT_000353a8 + iVar1);
    if (iVar3 != *(int *)(&DAT_000353b4 + iVar1)) {
      if (*(int *)(&DAT_000353b4 + iVar1) == iVar5) {
        if (*(int *)(&DAT_000353c4 + iVar1) < iVar2) {
LAB_0001fbbc:
          iVar3 = *(int *)(&DAT_000353ac + param_1 * 0x38);
          uVar4 = 2;
          goto LAB_0001fbcc;
        }
      }
      else if (iVar3 == iVar5) {
        uVar4 = (uint)(iVar2 < *(int *)(&DAT_000353c8 + iVar1));
        if (uVar4 != 1) goto LAB_0001fb30;
LAB_0001fc28:
        iVar3 = *(int *)(&DAT_000353b4 + param_1 * 0x38);
        uVar4 = 1;
LAB_0001fbcc:
        if (*(int *)(&DAT_000353a8 + param_1 * 0x38) != iVar3) {
          ak_print(10,3,"[%s:%d] need change sensor fps, new_fps:%d, current gain:%d\n",
                   "ak_vpss_get_fps_ctrl_stat",0xc14,iVar3,iVar2);
        }
        goto LAB_0001fb30;
      }
    }
  }
  iVar3 = iVar5;
  uVar4 = 0;
LAB_0001fb30:
  *param_2 = uVar4;
  *param_3 = iVar3;
  ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
  return 0;
}



undefined4 ak_vpss_change_sensor_fps(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  
  iVar1 = param_1 * 0x38;
  iVar4 = *(int *)(&DAT_000353a8 + iVar1);
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_change_sensor_fps",0xc2e,param_1);
    return 0x101;
  }
  if (param_2 < 1) {
    ak_print(10,1,"[%s:%d] need_fps:%d error!\n","ak_vpss_change_sensor_fps",0xc34,param_2);
    return 0x101;
  }
  if (*(int *)(&DAT_000353d8 + iVar1) == 0) {
    ak_print(10,5,"[%s:%d] dev:%d fps cfg is not init!\n","ak_vpss_change_sensor_fps",0xc3a,param_1)
    ;
    return 0x105;
  }
  puVar3 = &DAT_0003f9ac + param_1 * 0x18;
  ak_thread_mutex_lock(puVar3);
  if (((*(int *)(&DAT_000353b4 + iVar1) != param_2) && (*(int *)(&DAT_000353ac + iVar1) != param_2))
     && (*(int *)(&DAT_000353b0 + iVar1) != param_2)) {
    ak_print(10,1,"[%s:%d] need_fps:%d cannot find in cfg!\n","ak_vpss_change_sensor_fps",0xc44,
             param_2);
    ak_thread_mutex_unlock(puVar3);
    return 0x101;
  }
  if (param_2 < iVar4) {
    iVar1 = FUN_0001dec8(param_1,param_2);
    if (iVar1 == 0) {
      *(int *)(&DAT_000353a8 + param_1 * 0x38) = param_2;
      FUN_0001c7b8(param_1);
LAB_0001fe88:
      ak_thread_mutex_unlock(puVar3);
      ak_sleep_ms(5000);
      return 0;
    }
    uVar2 = 0x109;
  }
  else if (iVar4 < param_2) {
    *(int *)(&DAT_000353a8 + param_1 * 0x38) = param_2;
    FUN_0001c7b8(param_1);
    iVar1 = FUN_0001dec8(param_1,param_2);
    if (iVar1 == 0) goto LAB_0001fe88;
    *(int *)(&DAT_000353a8 + param_1 * 0x38) = iVar4;
    uVar2 = 0x109;
    FUN_0001c7b8(param_1);
  }
  else {
    uVar2 = 0;
  }
  ak_thread_mutex_unlock(puVar3);
  return uVar2;
}



undefined4 ak_vpss_get_sensor_fps(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 < 2) {
    if (param_2 != (int *)0x0) {
      iVar1 = isp_get_sensor_fps(param_1);
      *param_2 = iVar1;
      return 0;
    }
    ak_print(10,1,"[%s:%d] fps is null!\n","ak_vpss_get_sensor_fps",0xc7f);
    uVar2 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_sensor_fps",0xc79,param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4 ak_vpss_set_fps_level(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  uint local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (param_1 < 2) {
    if (param_2 != (undefined4 *)0x0) {
      if (((param_2[3] == 0) || (param_2[4] == 0)) || (param_2[5] == 0)) {
        local_58 = *param_2;
        local_54 = param_2[1];
        local_50 = param_2[2];
        local_4c = param_2[6];
        local_48 = param_2[7];
        local_44 = param_2[8];
        isp_set_attr(param_1,0x1d,&local_58,0x18);
      }
      else {
        local_38 = param_2[4] << 0x10;
        local_38 = CONCAT31(local_38._1_3_,(char)param_2[5]);
        local_3c = (uint)CONCAT12((char)param_2[3],(short)param_2[1]);
        local_40 = (uint)(CONCAT12((char)param_2[2],(short)*param_2) & 0xff00ff);
        local_30 = param_2[7] & 0xffff;
        local_34 = (uint)CONCAT11((char)param_2[8],(char)param_2[6]);
        isp_set_attr(param_1,0x1d,&local_40,0x18);
      }
      iVar2 = FUN_0001e048(param_1);
      ak_thread_mutex_lock(&DAT_0003f9ac + param_1 * 0x18);
      FUN_0001c7b8(param_1);
      ak_thread_mutex_unlock(&DAT_0003f9ac + param_1 * 0x18);
      uVar1 = 0x109;
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      return uVar1;
    }
    ak_print(10,1,"[%s:%d] fps_level is null!\n","ak_vpss_set_fps_level",0xc9d);
    uVar1 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_set_fps_level",0xc97,param_1);
    uVar1 = 0x101;
  }
  return uVar1;
}



undefined4 ak_vpss_get_fps_level(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined *puVar9;
  
  if (param_1 < 2) {
    if (param_2 != (undefined4 *)0x0) {
      iVar1 = param_1 * 0x38;
      if (*(int *)(&DAT_000353d8 + iVar1) == 0) {
        ak_print(10,5,"[%s:%d] dev:%d fps cfg is not init!\n","ak_vpss_get_fps_level",0xce8,param_1)
        ;
        return 0x105;
      }
      iVar8 = *(int *)(&DAT_000353d4 + iVar1);
      uVar2 = *(undefined4 *)(&DAT_000353b8 + iVar1);
      uVar3 = *(undefined4 *)(&DAT_000353b4 + iVar1);
      uVar4 = *(undefined4 *)(&DAT_000353c0 + iVar1);
      uVar5 = *(undefined4 *)(&DAT_000353c4 + iVar1);
      uVar7 = *(undefined4 *)(&DAT_000353ac + iVar1);
      param_2[8] = *(undefined4 *)(&DAT_000353c8 + iVar1);
      puVar9 = &DAT_000353ac + iVar1;
      param_2[7] = uVar2;
      if (iVar8 != 2) {
        uVar2 = *(undefined4 *)(&DAT_000353b0 + iVar1);
        puVar9 = *(undefined **)(&DAT_000353bc + iVar1);
        uVar6 = *(undefined4 *)(&DAT_000353cc + iVar1);
      }
      else {
        uVar6 = 0;
        param_2[3] = 0;
        param_2[4] = 0;
      }
      param_2[5] = uVar6;
      *param_2 = uVar3;
      param_2[1] = uVar4;
      param_2[2] = uVar5;
      if (iVar8 != 2) {
        param_2[3] = uVar2;
        param_2[4] = puVar9;
      }
      param_2[6] = uVar7;
      ak_print(10,4,
               "[%s:%d] hight light:\n\tframe_rate=%d, max_exp_time=%d, to lower_light_gain=%d\n",
               "ak_vpss_get_fps_level",0xd05,uVar3,uVar4,uVar5);
      ak_print(10,4,
               "[%s:%d] low light:\n\tframe_rate=%d, max_exp_time=%d, to higher_light_gain=%d\n",
               "ak_vpss_get_fps_level",0xd0a,param_2[6],param_2[7],param_2[8]);
      ak_print(10,4,"[%s:%d] mid light:\n\tframe_rate=%d, max_exp_time=%d, to low_light_gain=%d\n",
               "ak_vpss_get_fps_level",0xd0f,param_2[3],param_2[4],param_2[5]);
      return 0;
    }
    ak_print(10,1,"[%s:%d] fps_level is null!\n","ak_vpss_get_fps_level",0xce2);
    uVar2 = 0x100;
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","ak_vpss_get_fps_level",0xcdc,param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}



undefined4
FUN_00020384(int param_1,uint param_2,int param_3,uint param_4,int param_5,int param_6,char param_7,
            int *param_8)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  uint local_258;
  int local_254 [10];
  undefined4 local_22c;
  int local_228;
  undefined1 auStack_224 [16];
  int local_214;
  ushort local_210;
  byte local_20e;
  byte local_20d;
  byte local_20c;
  byte local_20b;
  byte local_20a;
  byte local_209;
  char local_208;
  undefined1 auStack_1a8 [388];
  
  if (param_1 < 2) {
    if (param_3 != 0 && (param_8 != (int *)0x0 && param_2 < 6)) {
      memset(&local_228,0,0x200);
      iVar5 = 1;
      local_254[1] = 0xffffffff;
      local_254[2] = 0xffffffff;
      local_254[3] = 0xffffffff;
      local_254[4] = 0xffffffff;
      local_254[5] = 0xffffffff;
      iVar4 = 0;
      uVar6 = 0;
      local_254[0] = 0;
      local_254[6] = 0;
      local_254[7] = 0;
      local_254[8] = 0;
      local_254[9] = 0;
      local_22c = 0;
      piVar7 = local_254 + 5;
      do {
        memcpy(&local_228,(void *)(param_5 + iVar4),0x200);
        cVar1 = local_208;
        if (local_228 != 6) {
          ak_print(10,1,"[%s:%d] config file: %s is wrong version, main_version:%d\n","check_data",
                   0xf3,param_3,local_228);
          return 0xffffffff;
        }
        if (((((local_210 < 0x76c) || (0xb < local_20e - 1)) || (0x1e < local_20d - 1)) ||
            ((0x17 < local_20c || (0x3b < local_20b)))) || ((0x3b < local_20a || (4 < local_209))))
        {
          ak_print(10,1,"[%s:%d] file: %s head info err!\n","check_data",0xfc,param_3);
          return 0xffffffff;
        }
        if (local_208 != param_7 || local_214 != param_6) {
          ak_print(10,2,"[%s:%d] %s is not need file!\n","check_data",0x10a,param_3);
          ak_print(10,4,"[%s:%d] sensor_id:0x%x, 0x%x, style_id:%d, %d\n","check_data",0x10c,param_6
                   ,local_214,param_7,local_208);
          return 0xffffffff;
        }
        piVar8 = piVar7 + 1;
        iVar3 = *piVar8;
        iVar4 = iVar4 + 0x200;
        local_258 = param_4 - iVar4;
        *piVar8 = iVar3 + 0x200;
        iVar2 = isp_module_check_cfg(param_5 + iVar4,&local_258);
        if (iVar2 < 0) {
          ak_print(10,1,"[%s:%d] %s isp data err!\n","check_data",0x118,param_3);
          return 0xffffffff;
        }
        iVar4 = iVar4 + local_258;
        *piVar8 = iVar3 + 0x200 + local_258;
        uVar6 = uVar6 + local_258 + 0x200;
        if (iVar5 == 1) {
          local_254[local_209 + 1] = 0;
          if (param_4 <= uVar6) {
LAB_00020570:
            if (param_2 == 5) {
              *param_8 = 0;
            }
            else {
              if (local_254[param_2 + 1] == -1) {
                ak_print(10,1,"[%s:%d] %s no this subfile! mode : %d\n","check_data",0x134,param_3,
                         param_2);
                return 0xffffffff;
              }
              *param_8 = local_254[param_2 + 1] + 0x200;
            }
            if (iVar5 == 1) {
              ak_print(10,1,"[%s:%d] subfile %s is not enough, cnt: %u\n","check_data",0x13d,param_3
                       ,1);
              return 0xffffffff;
            }
            ak_print(10,3,"[isp.conf]version: %s, sensor id: 0x%x, style id: %d\n",auStack_224,
                     local_214,cVar1);
            piVar7 = local_254;
            iVar4 = 0;
            do {
              piVar7 = piVar7 + 1;
              memcpy(&local_228,(void *)(param_5 + *piVar7),0x200);
              ak_print(10,4,"isp subfile %d, modify time: %d-%d-%d %02d:%02d:%02d\n",iVar4,local_210
                       ,local_20e,local_20d,local_20c,local_20b,local_20a);
              iVar4 = iVar4 + 1;
              ak_print(10,4,&DAT_000249fc,auStack_1a8);
            } while (iVar4 != iVar5);
            return 0;
          }
        }
        else {
          local_254[local_209 + 1] = piVar7[-5] + *piVar7;
          if ((param_4 <= uVar6) || (iVar5 == 5)) goto LAB_00020570;
        }
        iVar5 = iVar5 + 1;
        piVar7 = piVar8;
      } while( true );
    }
    ak_print(10,1,"[%s:%d] invalid argument, path: %s, offset: %p, mode: %d\n","check_data",0xbe,
             param_3,param_8,param_2);
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","check_data",0xb7,param_1);
  }
  return 0xffffffff;
}



undefined4 FUN_0002087c(undefined4 param_1)

{
  int *piVar1;
  char *pcVar2;
  
  piVar1 = __errno_location();
  pcVar2 = strerror(*piVar1);
  ak_print(10,1,"[%s:%d] open %s failed, %s\n","open_file",0x8b,param_1,pcVar2);
  return 0;
}



void isp_cfg_file_set_path(int param_1,char *param_2)

{
  size_t __n;
  char *__dest;
  
  if (param_1 < 2) {
    if (param_2 != (char *)0x0) {
      __dest = (char *)(param_1 * 0x100 + 0x3fbf0);
      memset(__dest,0,0x100);
      __n = strlen(param_2);
      strncpy(__dest,param_2,__n);
    }
    return;
  }
  ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_cfg_file_set_path",0x206,param_1);
  return;
}



void isp_cfg_file_clear_path(int param_1)

{
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_cfg_file_clear_path",0x214,param_1);
    return;
  }
  memset((void *)(param_1 * 0x100 + 0x3fbf0),0,0x100);
  return;
}



undefined1 isp_cfg_file_get_style_id(void)

{
  FILE *__stream;
  undefined1 local_9;
  
  local_9 = 0;
  __stream = fopen("/etc/config/styleId","rb");
  if (__stream != (FILE *)0x0) {
    fread(&local_9,1,1,__stream);
    fclose(__stream);
  }
  return local_9;
}



undefined4 isp_cfg_file_set_style_id(undefined1 param_1)

{
  FILE *__s;
  undefined4 uVar1;
  undefined1 local_9;
  
  local_9 = param_1;
  __s = fopen("/etc/config/styleId","wb");
  if (__s == (FILE *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    fwrite(&local_9,1,1,__s);
    fclose(__s);
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 isp_cfg_file_load(int param_1,uint param_2,void *param_3,size_t *param_4)

{
  char cVar1;
  FILE *__stream;
  uint __n;
  void *__ptr;
  int iVar2;
  char *__filename;
  undefined4 uVar3;
  char *__dest;
  int local_30;
  int local_2c;
  
  local_30 = 0;
  if (1 < param_1) {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_cfg_file_load",0x24e,param_1);
    return 0xffffffff;
  }
  __filename = (char *)(param_1 * 0x100 + 0x3fbf0);
  __stream = fopen(__filename,"rb");
  if ((__stream == (FILE *)0x0) &&
     (__stream = (FILE *)FUN_0002087c(__filename), __stream == (FILE *)0x0)) {
    return 0xffffffff;
  }
  fseek(__stream,0,2);
  __n = ftell(__stream);
  if (__n < 0x201) {
    ak_print(10,1,"[%s:%d] file_size too small","isp_cfg_file_load",0x25d);
  }
  else {
    uVar3 = ak_get_os_timestamp();
    __ptr = (void *)ak_mem_alloc_(10,__n + 0x10,"isp_cfg_file_load",uVar3);
    if (__ptr != (void *)0x0) {
      rewind(__stream);
      fread(__ptr,1,__n,__stream);
      local_2c = 0;
      vi_dev_get_sensor_id(param_1);
      iVar2 = local_2c;
      cVar1 = isp_cfg_file_get_style_id();
      iVar2 = FUN_00020384(param_1,param_2,(int)__filename,__n,(int)__ptr,iVar2,cVar1,&local_30);
      if (iVar2 == 0) {
        __dest = (char *)(param_1 * 0x100 + 0x3fdf0);
        memset(__dest,0,0x100);
        strcpy(__dest,__filename);
        ak_print(10,4,"[%s:%d] check isp cfg: %s OK\n","check_file",0x19d,__dest);
        *param_4 = __n - local_30;
        memcpy(param_3,(void *)((int)__ptr + local_30),__n - local_30);
        uVar3 = 0;
      }
      else {
        ak_print(10,4,"[%s:%d] read sensor fail\n","check_file",0x193);
        if (param_2 == 0) {
          isp_cfg_file_clear_path(param_1);
        }
        uVar3 = 0xffffffff;
      }
      ak_mem_free(__ptr);
      goto LAB_00020b78;
    }
    ak_print(10,1,"[%s:%d] calloc failed, size: %d\n","isp_cfg_file_load",0x265,__n + 0x10);
  }
  uVar3 = 0xffffffff;
LAB_00020b78:
  fclose(__stream);
  return uVar3;
}



undefined4 isp_cfg_file_store(int param_1,void *param_2,size_t param_3)

{
  int iVar1;
  FILE *__stream;
  size_t sVar2;
  int *piVar3;
  char *pcVar4;
  char *__filename;
  undefined4 uVar5;
  
  if (param_1 < 2) {
    if (param_3 == 0 || param_2 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] param NULL!\n","isp_cfg_file_store",0x29d);
      uVar5 = 0xffffffff;
    }
    else {
      iVar1 = param_1 * 4;
      if (*(FILE **)(iVar1 + 0x3fff0) != (FILE *)0x0) {
        fclose(*(FILE **)(iVar1 + 0x3fff0));
      }
      __filename = (char *)(param_1 * 0x100 + 0x3fdf0);
      __stream = fopen(__filename,"w+b");
      *(FILE **)(iVar1 + 0x3fff0) = __stream;
      if (__stream == (FILE *)0x0) {
        piVar3 = __errno_location();
        uVar5 = 0xffffffff;
        pcVar4 = strerror(*piVar3);
        ak_print(10,1,"[%s:%d] open %s failed, %s\n","create_file",0x3d,__filename,pcVar4);
        ak_print(10,1,"%s isp_cfg_fp open failed!\n","isp_cfg_file_store");
      }
      else {
        fseek(__stream,0,0);
        sVar2 = fwrite(param_2,1,param_3,*(FILE **)(iVar1 + 0x3fff0));
        if (param_3 == sVar2) {
          uVar5 = 0;
        }
        else {
          ak_print(10,1,"%s isp_cfg_fp write failed!\n","write_data");
          uVar5 = 0xffffffff;
        }
      }
      if (*(FILE **)(iVar1 + 0x3fff0) != (FILE *)0x0) {
        fclose(*(FILE **)(iVar1 + 0x3fff0));
        *(undefined4 *)(iVar1 + 0x3fff0) = 0;
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_cfg_file_store",0x298,param_1);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}



undefined4 isp_cfg_file_get_headinfo(int param_1,int param_2,void *param_3)

{
  FILE *__stream;
  size_t sVar1;
  undefined4 uVar2;
  char *__filename;
  int iVar3;
  long __off;
  undefined1 auStack_220 [36];
  int local_1fc;
  
  memset(auStack_220,0,0x200);
  if (param_1 < 2) {
    if (param_3 == (void *)0x0) {
      ak_print(10,1,"[%s:%d] headinfo NULL!\n","isp_cfg_file_get_headinfo",0x2c2);
      uVar2 = 0xffffffff;
    }
    else {
      __filename = (char *)(param_1 * 0x100 + 0x3fdf0);
      __stream = fopen(__filename,"rb");
      if ((__stream == (FILE *)0x0) &&
         (__stream = (FILE *)FUN_0002087c(__filename), __stream == (FILE *)0x0)) {
        uVar2 = 0xffffffff;
      }
      else {
        if (param_2 == 0) {
          __off = 0;
        }
        else {
          iVar3 = 0;
          __off = 0;
          do {
            fseek(__stream,__off,0);
            sVar1 = fread(auStack_220,1,0x200,__stream);
            iVar3 = iVar3 + 1;
            if (sVar1 != 0x200) {
              uVar2 = 0x2ce;
              goto LAB_00021084;
            }
            __off = __off + local_1fc;
          } while (iVar3 != param_2);
        }
        fseek(__stream,__off,0);
        sVar1 = fread(param_3,1,0x200,__stream);
        if (sVar1 == 0x200) {
          uVar2 = 0;
        }
        else {
          uVar2 = 0x2d9;
LAB_00021084:
          ak_print(10,1,"[%s:%d] read failed!\n","isp_cfg_file_get_headinfo",uVar2);
          uVar2 = 0xffffffff;
        }
        fclose(__stream);
      }
    }
  }
  else {
    ak_print(10,1,"[%s:%d] dev:%d error!\n","isp_cfg_file_get_headinfo",0x2bd,param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



ulonglong FUN_000211a0(uint param_1,uint param_2)

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



ulonglong FUN_00021268(uint param_1,uint param_2)

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



ulonglong FUN_0002136c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  
  uVar9 = param_4 ^ 0x80000000;
  uVar12 = param_2 << 1;
  uVar5 = param_4 << 1;
  iVar11 = (int)uVar12 >> 0x15;
  iVar1 = (int)uVar5 >> 0x15;
  if ((((uVar12 == uVar5 && param_1 == param_3 || uVar12 == 0 && param_1 == 0) ||
       uVar5 == 0 && param_3 == 0) || iVar11 == -1) || iVar1 == -1) {
    if (iVar11 == -1 || iVar1 == -1) {
      uVar12 = param_3;
      uVar5 = uVar9;
      if (iVar11 == -1) {
        uVar12 = param_1;
        uVar5 = param_2;
      }
      if (iVar11 != -1 || iVar1 != -1) {
        param_3 = uVar12;
        uVar9 = uVar5;
      }
      bVar15 = (uVar5 & 0xfffff) == 0;
      bVar16 = uVar12 == 0 && bVar15;
      if (uVar12 == 0 && bVar15) {
        bVar16 = param_3 == 0 && (uVar9 & 0xfffff) == 0;
      }
      if (!bVar16 || uVar5 != uVar9) {
        uVar5 = uVar5 | 0x80000;
      }
      return CONCAT44(uVar5,uVar12);
    }
    if (uVar12 != uVar5 || param_1 != param_3) {
      if (uVar12 == 0 && param_1 == 0) {
        param_1 = param_3;
        param_2 = uVar9;
      }
      return CONCAT44(param_2,param_1);
    }
    if (param_2 != uVar9) {
      return 0;
    }
    if (uVar12 >> 0x15 == 0) {
      bVar2 = (byte)(param_1 >> 0x1f);
      uVar12 = param_2 * 2 + (uint)bVar2;
      if (CARRY4(param_2,param_2) || CARRY4(param_2 * 2,(uint)bVar2)) {
        uVar12 = uVar12 | 0x80000000;
      }
      return CONCAT44(uVar12,param_1 << 1);
    }
    if (uVar12 < 0xffc00000) {
      return CONCAT44(param_2 + 0x100000,param_1);
    }
    uVar5 = param_2 & 0x80000000;
LAB_000215e0:
    return (ulonglong)(uVar5 | 0x7ff00000) << 0x20;
  }
  uVar12 = uVar12 >> 0x15;
  uVar5 = uVar5 >> 0x15;
  uVar13 = uVar5 - uVar12;
  bVar15 = uVar13 != 0;
  if (uVar5 < uVar12) {
    uVar13 = -uVar13;
  }
  uVar6 = param_1;
  uVar10 = param_2;
  if (bVar15 && uVar12 <= uVar5) {
    uVar12 = uVar12 + uVar13;
    uVar6 = param_3;
    uVar10 = uVar9;
    param_3 = param_1;
    uVar9 = param_2;
  }
  if (0x36 < uVar13) {
    return CONCAT44(uVar10,uVar6);
  }
  uVar5 = uVar10 & 0xfffff | 0x100000;
  if ((uVar10 & 0x80000000) != 0) {
    bVar15 = uVar6 != 0;
    uVar6 = -uVar6;
    uVar5 = -(uVar5 + bVar15);
  }
  uVar10 = uVar9 & 0xfffff | 0x100000;
  if ((uVar9 & 0x80000000) != 0) {
    bVar15 = param_3 != 0;
    param_3 = -param_3;
    uVar10 = -(uVar10 + bVar15);
  }
  if (uVar12 == uVar13) {
    uVar10 = uVar10 ^ 0x100000;
    if (uVar12 == 0) {
      uVar5 = uVar5 ^ 0x100000;
      uVar12 = 1;
    }
    else {
      uVar13 = uVar13 - 1;
    }
  }
  uVar9 = -uVar13 + 0x20;
  if ((int)uVar13 < 0x21) {
    uVar14 = param_3 << (uVar9 & 0xff);
    uVar8 = param_3 >> (uVar13 & 0xff);
    uVar4 = uVar6 + uVar8;
    uVar7 = uVar10 << (uVar9 & 0xff);
    uVar9 = uVar4 + uVar7;
    uVar13 = uVar5 + CARRY4(uVar6,uVar8) + ((int)uVar10 >> (uVar13 & 0xff)) +
             (uint)CARRY4(uVar4,uVar7);
  }
  else {
    uVar14 = uVar10 << (-uVar13 + 0x40 & 0xff);
    if (param_3 != 0) {
      uVar14 = uVar14 | 2;
    }
    uVar13 = (int)uVar10 >> (uVar13 - 0x20 & 0xff);
    uVar9 = uVar6 + uVar13;
    uVar13 = uVar5 + ((int)uVar10 >> 0x1f) + (uint)CARRY4(uVar6,uVar13);
  }
  uVar5 = uVar13 & 0x80000000;
  uVar6 = uVar13;
  if ((int)uVar13 < 0) {
    bVar15 = uVar14 == 0;
    uVar14 = -uVar14;
    uVar6 = -uVar9;
    uVar9 = -(uVar9 + !bVar15);
    uVar6 = -(uVar13 + (bVar15 <= uVar6));
  }
  if (0xfffff < uVar6) {
    uVar10 = uVar12 - 1;
    if (0x1fffff < uVar6) {
      bVar2 = (byte)uVar6;
      uVar6 = uVar6 >> 1;
      bVar3 = (byte)uVar9;
      uVar9 = (uint)(bVar2 & 1) << 0x1f | uVar9 >> 1;
      uVar14 = (uint)(bVar3 & 1) << 0x1f | uVar14 >> 1;
      uVar10 = uVar12;
      if (0xffbfffff < uVar12 * 0x200000) goto LAB_000215e0;
    }
LAB_00021488:
    bVar15 = 0x7fffffff < uVar14;
    if (uVar14 == 0x80000000) {
      bVar15 = (bool)((byte)uVar9 & 1);
    }
    return CONCAT44(uVar6 + uVar10 * 0x100000 + (uint)CARRY4(uVar9,(uint)bVar15) | uVar5,
                    uVar9 + bVar15);
  }
  bVar2 = (byte)(uVar14 >> 0x1f);
  uVar14 = uVar14 << 1;
  uVar10 = uVar9 * 2;
  bVar15 = CARRY4(uVar9,uVar9);
  uVar9 = uVar9 * 2 + (uint)bVar2;
  uVar6 = uVar6 * 2 + (uint)(bVar15 || CARRY4(uVar10,(uint)bVar2));
  uVar10 = uVar12 - 2;
  if ((uVar6 & 0x100000) != 0) goto LAB_00021488;
  uVar12 = uVar9;
  uVar7 = uVar6;
  if (uVar6 == 0) {
    uVar12 = 0;
    uVar7 = uVar9;
  }
  iVar11 = LZCOUNT(uVar7);
  if (uVar6 == 0) {
    iVar11 = iVar11 + 0x20;
  }
  uVar4 = iVar11 - 0xb;
  bVar16 = SBORROW4(uVar4,0x20);
  uVar8 = iVar11 - 0x2b;
  bVar15 = uVar8 == 0;
  uVar9 = uVar8;
  uVar6 = uVar8;
  if ((int)uVar4 < 0x20) {
    bVar16 = SCARRY4(uVar8,0xc);
    uVar6 = iVar11 - 0x1f;
    bVar15 = uVar6 == 0;
    uVar9 = uVar4;
    if (!bVar15 && -0xd < (int)uVar8) {
      uVar12 = uVar7 << (uVar4 & 0xff);
      uVar7 = uVar7 >> (0xc - uVar6 & 0xff);
      goto LAB_00021508;
    }
  }
  if (bVar15 || (int)uVar6 < 0 != bVar16) {
    uVar14 = 0x20 - uVar9;
  }
  uVar7 = uVar7 << (uVar9 & 0xff);
  if (bVar15 || (int)uVar6 < 0 != bVar16) {
    uVar7 = uVar7 | uVar12 >> (uVar14 & 0xff);
    uVar12 = uVar12 << (uVar9 & 0xff);
  }
LAB_00021508:
  if ((int)uVar4 <= (int)uVar10) {
    return CONCAT44(uVar7 + (uVar10 - uVar4) * 0x100000 | uVar5,uVar12);
  }
  uVar9 = ~(uVar10 - uVar4);
  if ((int)uVar9 < 0x1f) {
    if (uVar9 - 0x13 != 0 && -0xd < (int)(uVar9 - 0x1f)) {
      uVar5 = 0xc - (uVar9 - 0x13);
      return CONCAT44(uVar13,uVar12 >> (0x20 - uVar5 & 0xff) | uVar7 << (uVar5 & 0xff)) &
             0x80000000ffffffff;
    }
    uVar9 = uVar9 + 1;
    return CONCAT44(uVar5 | uVar7 >> (uVar9 & 0xff),
                    uVar12 >> (uVar9 & 0xff) | uVar7 << (0x20 - uVar9 & 0xff));
  }
  return CONCAT44(uVar13,uVar7 >> (uVar9 - 0x1f & 0xff)) & 0x80000000ffffffff;
}



ulonglong FUN_00021370(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  
  uVar11 = param_2 << 1;
  uVar5 = param_4 << 1;
  iVar10 = (int)uVar11 >> 0x15;
  iVar1 = (int)uVar5 >> 0x15;
  if ((((uVar11 == uVar5 && param_1 == param_3 || uVar11 == 0 && param_1 == 0) ||
       uVar5 == 0 && param_3 == 0) || iVar10 == -1) || iVar1 == -1) {
    if (iVar10 == -1 || iVar1 == -1) {
      uVar11 = param_3;
      uVar5 = param_4;
      if (iVar10 == -1) {
        uVar11 = param_1;
        uVar5 = param_2;
      }
      if (iVar10 != -1 || iVar1 != -1) {
        param_3 = uVar11;
        param_4 = uVar5;
      }
      bVar15 = (uVar5 & 0xfffff) == 0;
      bVar16 = uVar11 == 0 && bVar15;
      if (uVar11 == 0 && bVar15) {
        bVar16 = param_3 == 0 && (param_4 & 0xfffff) == 0;
      }
      if (!bVar16 || uVar5 != param_4) {
        uVar5 = uVar5 | 0x80000;
      }
      return CONCAT44(uVar5,uVar11);
    }
    if (uVar11 != uVar5 || param_1 != param_3) {
      if (uVar11 == 0 && param_1 == 0) {
        param_1 = param_3;
        param_2 = param_4;
      }
      return CONCAT44(param_2,param_1);
    }
    if (param_2 != param_4) {
      return 0;
    }
    if (uVar11 >> 0x15 == 0) {
      bVar2 = (byte)(param_1 >> 0x1f);
      uVar11 = param_2 * 2 + (uint)bVar2;
      if (CARRY4(param_2,param_2) || CARRY4(param_2 * 2,(uint)bVar2)) {
        uVar11 = uVar11 | 0x80000000;
      }
      return CONCAT44(uVar11,param_1 << 1);
    }
    if (uVar11 < 0xffc00000) {
      return CONCAT44(param_2 + 0x100000,param_1);
    }
    uVar5 = param_2 & 0x80000000;
LAB_000215e0:
    return (ulonglong)(uVar5 | 0x7ff00000) << 0x20;
  }
  uVar11 = uVar11 >> 0x15;
  uVar5 = uVar5 >> 0x15;
  uVar12 = uVar5 - uVar11;
  bVar15 = uVar12 != 0;
  if (uVar5 < uVar11) {
    uVar12 = -uVar12;
  }
  uVar6 = param_1;
  uVar9 = param_2;
  if (bVar15 && uVar11 <= uVar5) {
    uVar11 = uVar11 + uVar12;
    uVar6 = param_3;
    uVar9 = param_4;
    param_3 = param_1;
    param_4 = param_2;
  }
  if (0x36 < uVar12) {
    return CONCAT44(uVar9,uVar6);
  }
  uVar5 = uVar9 & 0xfffff | 0x100000;
  if ((uVar9 & 0x80000000) != 0) {
    bVar15 = uVar6 != 0;
    uVar6 = -uVar6;
    uVar5 = -(uVar5 + bVar15);
  }
  uVar9 = param_4 & 0xfffff | 0x100000;
  if ((param_4 & 0x80000000) != 0) {
    bVar15 = param_3 != 0;
    param_3 = -param_3;
    uVar9 = -(uVar9 + bVar15);
  }
  if (uVar11 == uVar12) {
    uVar9 = uVar9 ^ 0x100000;
    if (uVar11 == 0) {
      uVar5 = uVar5 ^ 0x100000;
      uVar11 = 1;
    }
    else {
      uVar12 = uVar12 - 1;
    }
  }
  uVar14 = -uVar12 + 0x20;
  if ((int)uVar12 < 0x21) {
    uVar13 = param_3 << (uVar14 & 0xff);
    uVar8 = param_3 >> (uVar12 & 0xff);
    uVar4 = uVar6 + uVar8;
    uVar7 = uVar9 << (uVar14 & 0xff);
    uVar14 = uVar4 + uVar7;
    uVar12 = uVar5 + CARRY4(uVar6,uVar8) + ((int)uVar9 >> (uVar12 & 0xff)) +
             (uint)CARRY4(uVar4,uVar7);
  }
  else {
    uVar13 = uVar9 << (-uVar12 + 0x40 & 0xff);
    if (param_3 != 0) {
      uVar13 = uVar13 | 2;
    }
    uVar12 = (int)uVar9 >> (uVar12 - 0x20 & 0xff);
    uVar14 = uVar6 + uVar12;
    uVar12 = uVar5 + ((int)uVar9 >> 0x1f) + (uint)CARRY4(uVar6,uVar12);
  }
  uVar5 = uVar12 & 0x80000000;
  uVar6 = uVar12;
  if ((int)uVar12 < 0) {
    bVar15 = uVar13 == 0;
    uVar13 = -uVar13;
    uVar6 = -uVar14;
    uVar14 = -(uVar14 + !bVar15);
    uVar6 = -(uVar12 + (bVar15 <= uVar6));
  }
  if (0xfffff < uVar6) {
    uVar9 = uVar11 - 1;
    if (0x1fffff < uVar6) {
      bVar2 = (byte)uVar6;
      uVar6 = uVar6 >> 1;
      bVar3 = (byte)uVar14;
      uVar14 = (uint)(bVar2 & 1) << 0x1f | uVar14 >> 1;
      uVar13 = (uint)(bVar3 & 1) << 0x1f | uVar13 >> 1;
      uVar9 = uVar11;
      if (0xffbfffff < uVar11 * 0x200000) goto LAB_000215e0;
    }
LAB_00021488:
    bVar15 = 0x7fffffff < uVar13;
    if (uVar13 == 0x80000000) {
      bVar15 = (bool)((byte)uVar14 & 1);
    }
    return CONCAT44(uVar6 + uVar9 * 0x100000 + (uint)CARRY4(uVar14,(uint)bVar15) | uVar5,
                    uVar14 + bVar15);
  }
  bVar2 = (byte)(uVar13 >> 0x1f);
  uVar13 = uVar13 << 1;
  uVar9 = uVar14 * 2;
  bVar15 = CARRY4(uVar14,uVar14);
  uVar14 = uVar14 * 2 + (uint)bVar2;
  uVar6 = uVar6 * 2 + (uint)(bVar15 || CARRY4(uVar9,(uint)bVar2));
  uVar9 = uVar11 - 2;
  if ((uVar6 & 0x100000) != 0) goto LAB_00021488;
  uVar11 = uVar14;
  uVar7 = uVar6;
  if (uVar6 == 0) {
    uVar11 = 0;
    uVar7 = uVar14;
  }
  iVar10 = LZCOUNT(uVar7);
  if (uVar6 == 0) {
    iVar10 = iVar10 + 0x20;
  }
  uVar4 = iVar10 - 0xb;
  bVar16 = SBORROW4(uVar4,0x20);
  uVar8 = iVar10 - 0x2b;
  bVar15 = uVar8 == 0;
  uVar6 = uVar8;
  uVar14 = uVar8;
  if ((int)uVar4 < 0x20) {
    bVar16 = SCARRY4(uVar8,0xc);
    uVar14 = iVar10 - 0x1f;
    bVar15 = uVar14 == 0;
    uVar6 = uVar4;
    if (!bVar15 && -0xd < (int)uVar8) {
      uVar11 = uVar7 << (uVar4 & 0xff);
      uVar7 = uVar7 >> (0xc - uVar14 & 0xff);
      goto LAB_00021508;
    }
  }
  if (bVar15 || (int)uVar14 < 0 != bVar16) {
    uVar13 = 0x20 - uVar6;
  }
  uVar7 = uVar7 << (uVar6 & 0xff);
  if (bVar15 || (int)uVar14 < 0 != bVar16) {
    uVar7 = uVar7 | uVar11 >> (uVar13 & 0xff);
    uVar11 = uVar11 << (uVar6 & 0xff);
  }
LAB_00021508:
  if ((int)uVar4 <= (int)uVar9) {
    return CONCAT44(uVar7 + (uVar9 - uVar4) * 0x100000 | uVar5,uVar11);
  }
  uVar6 = ~(uVar9 - uVar4);
  if ((int)uVar6 < 0x1f) {
    if (uVar6 - 0x13 != 0 && -0xd < (int)(uVar6 - 0x1f)) {
      uVar5 = 0xc - (uVar6 - 0x13);
      return CONCAT44(uVar12,uVar11 >> (0x20 - uVar5 & 0xff) | uVar7 << (uVar5 & 0xff)) &
             0x80000000ffffffff;
    }
    uVar6 = uVar6 + 1;
    return CONCAT44(uVar5 | uVar7 >> (uVar6 & 0xff),
                    uVar11 >> (uVar6 & 0xff) | uVar7 << (0x20 - uVar6 & 0xff));
  }
  return CONCAT44(uVar12,uVar7 >> (uVar6 - 0x1f & 0xff)) & 0x80000000ffffffff;
}



ulonglong FUN_0002161c(uint param_1)

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
      goto LAB_00021508;
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
LAB_00021508:
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



ulonglong FUN_00021640(uint param_1)

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
      goto LAB_00021508;
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
LAB_00021508:
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



ulonglong FUN_0002171c(int param_1,uint param_2,uint param_3,uint param_4)

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
    uVar15 = FUN_000218fc(param_1,param_2,param_3,param_4);
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



ulonglong FUN_000218fc(int param_1,uint param_2,int param_3,uint param_4)

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



ulonglong FUN_00021988(int param_1,uint param_2,uint param_3,uint param_4)

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
    uVar16 = FUN_00021b1c(param_1,param_2,param_3,param_4);
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
        if ((uVar6 & 0x100000) != 0) goto LAB_00021ac8;
        uVar6 = uVar6 | uVar2;
        uVar2 = 0;
        uVar11 = 0x80000000;
      }
    }
    if ((uVar6 & 0x100000) == 0) {
      uVar6 = uVar6 | uVar2;
      uVar2 = 0;
    }
LAB_00021ac8:
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



ulonglong FUN_00021b1c(int param_1,uint param_2,int param_3,uint param_4)

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
LAB_00021964:
        return (ulonglong)((param_2 ^ param_4) & 0x80000000 | 0x7ff00000) << 0x20;
      }
    }
    else if (uVar2 == in_r12) {
      param_1 = param_3;
      uVar3 = param_4;
      if (param_3 == 0 && (param_4 & 0xfffff) == 0) {
LAB_00021918:
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
      if (param_1 != 0 || (param_2 & 0x7fffffff) != 0) goto LAB_00021964;
      if (param_3 != 0 || (param_4 & 0x7fffffff) != 0) goto LAB_00021918;
    }
  }
  return CONCAT44(uVar3,param_1) | 0x7ff8000000000000;
}



uint FUN_00021b9c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  bool bVar2;
  bool bVar3;
  
  if (((int)(param_2 << 1) >> 0x15 == -1 || (int)(param_4 << 1) >> 0x15 == -1) &&
     ((((int)(param_2 << 1) >> 0x15 == -1 && (param_1 != 0 || (param_2 & 0xfffff) != 0)) ||
      (((int)(param_4 << 1) >> 0x15 == -1 && (param_3 != 0 || (param_4 & 0xfffff) != 0)))))) {
    return 1;
  }
  bVar3 = (param_2 & 0x7fffffff) == 0;
  bVar2 = param_1 == 0 && bVar3;
  if (param_1 == 0 && bVar3) {
    bVar2 = param_3 == 0 && (param_4 & 0x7fffffff) == 0;
  }
  if (!bVar2) {
    bVar2 = param_2 == param_4;
  }
  if (!bVar2 || param_1 != param_3) {
    uVar1 = param_2 ^ param_4;
    bVar3 = uVar1 == 0;
    if (-1 < (int)uVar1) {
      bVar3 = param_2 == param_4;
    }
    bVar2 = -1 < (int)uVar1 && param_4 <= param_2;
    if (bVar3) {
      bVar2 = param_3 <= param_1;
    }
    uVar1 = (int)param_4 >> 0x1f;
    if (!bVar2) {
      uVar1 = ~uVar1;
    }
    return uVar1 | 1;
  }
  return 0;
}



void FUN_00021c24(uint param_1,uint param_2,uint param_3,uint param_4)

{
  FUN_00021c40(param_3,param_4,param_1,param_2);
  return;
}



uint FUN_00021c40(uint param_1,uint param_2,uint param_3,uint param_4)

{
  FUN_00021b9c(param_1,param_2,param_3,param_4);
  return param_1;
}



undefined1 FUN_00021c54(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 in_ZR;
  
  FUN_00021c40(param_1,param_2,param_3,param_4);
  return in_ZR;
}



bool FUN_00021c68(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 in_CY;
  
  FUN_00021c40(param_1,param_2,param_3,param_4);
  return !(bool)in_CY;
}



bool FUN_00021c7c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 in_ZR;
  undefined1 in_CY;
  
  FUN_00021c40(param_1,param_2,param_3,param_4);
  return !(bool)in_CY || (bool)in_ZR;
}



bool FUN_00021c90(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 in_ZR;
  undefined1 in_CY;
  
  FUN_00021c24(param_1,param_2,param_3,param_4);
  return !(bool)in_CY || (bool)in_ZR;
}



bool FUN_00021ca4(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined1 in_CY;
  
  FUN_00021c24(param_1,param_2,param_3,param_4);
  return !(bool)in_CY;
}



uint FUN_00021cb8(uint param_1,uint param_2)

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



uint FUN_00021d14(uint param_1,uint param_2)

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



void _fini(void)

{
  return;
}


