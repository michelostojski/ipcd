typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned long long    qword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef pointer pointer __((offset(0x8)));

typedef pointer pointer __((offset(0x10)));

typedef ulong size_t;

typedef uint sizetype;

typedef ulonglong UDItype;

typedef uint USItype;

typedef longlong DItype;

typedef qword complex float;

typedef undefined complex double[16];

typedef int SItype;

typedef union DWunion DWunion, *PDWunion;

typedef struct DWstruct DWstruct, *PDWstruct;

struct DWstruct {
    SItype low;
    SItype high;
};

union DWunion {
    struct DWstruct s;
    DItype ll;
};

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

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

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



undefined4 __dso_handle;
dword __FRAME_END__;
pointer __DT_PLTGOT;
undefined1 completed.8508;
undefined1[24] object.8513;
undefined __register_frame_info;
undefined1[32] CSWTCH.39;
undefined1 app_video_chn_glock;
undefined4 app_video_chn_g;
undefined4 error_count.7425;
undefined app_video_vi_stream_th;
int *DAT_00024078;
undefined4 dbg_init_flag;
undefined ak_print;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



int app_video_bind_chn(int *param_1,int *param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = app_video_bind_chn(param_1,param_2,param_3);
  return iVar1;
}



int * app_video_find_src_gchn(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_video_find_src_gchn(param_1);
  return piVar1;
}



undefined4 app_video_unbind_chn(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = app_video_unbind_chn(param_1,param_2);
  return uVar1;
}



int * app_video_find_dst_chn(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = app_video_find_dst_chn(param_1,param_2);
  return piVar1;
}



int app_video_vi_stream_behavior
              (undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = app_video_vi_stream_behavior(param_1,param_2,param_3,param_4);
  return iVar1;
}



int * app_video_find_dst_chn_all(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_video_find_dst_chn_all(param_1);
  return piVar1;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



undefined4 app_video_check_bind_chn_relation(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = app_video_check_bind_chn_relation(param_1,param_2);
  return uVar1;
}



void * app_video_gen_obj(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
  pvVar1 = app_video_gen_obj(param_1,param_2,param_3);
  return pvVar1;
}



undefined4 app_video_free_gobj(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_video_free_gobj(param_1);
  return uVar1;
}



undefined4 app_video_free_obj(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_video_free_obj(param_1);
  return uVar1;
}



undefined4 app_video_check_src_range(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_video_check_src_range(param_1);
  return uVar1;
}



int app_video_vi_stream_do_venc(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = app_video_vi_stream_do_venc(param_1,param_2);
  return iVar1;
}



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



void * app_video_gen_gobj(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
  pvVar1 = app_video_gen_gobj(param_1,param_2,param_3);
  return pvVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int raise(int __sig)

{
  int iVar1;
  
  iVar1 = raise(__sig);
  return iVar1;
}



// WARNING: Removing unreachable block (ram,0x000113e4)
// WARNING: Removing unreachable block (ram,0x000113fc)
// WARNING: Removing unreachable block (ram,0x00011404)

void processEntry deregister_tm_clones(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x00011448)
// WARNING: Removing unreachable block (ram,0x00011460)
// WARNING: Removing unreachable block (ram,0x00011468)

void register_tm_clones(void)

{
  return;
}



void __do_global_dtors_aux(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (completed_8508 == '\0') {
    __cxa_finalize(__dso_handle);
    deregister_tm_clones();
    if (ppuVar1[0x17] != (undefined *)0x0) {
      __deregister_frame_info(&__FRAME_END__);
    }
    completed_8508 = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00011550)
// WARNING: Removing unreachable block (ram,0x00011564)

void frame_dummy(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&__FRAME_END__,object_8513,param_3,__register_frame_info,param_1,param_2);
  register_tm_clones();
  return;
}



char * ak_app_video_get_version(void)

{
  return "libapp_video V1.0.07";
}



undefined4 app_video_switch_mid(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 7U < 8) {
    uVar1 = *(undefined4 *)(CSWTCH_39 + (param_1 - 7U) * 4);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



int * app_video_find_src_gchn(int *param_1)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (*param_1 - 7U < 8) {
    iVar3 = *(int *)(CSWTCH_39 + (*param_1 - 7U) * 4);
  }
  else {
    iVar3 = -1;
  }
  puVar2 = &app_video_chn_glock + iVar3 * 0x18;
  ak_thread_mutex_lock(puVar2);
  puVar1 = (undefined4 *)(&app_video_chn_g)[iVar3 * 2];
  if (&app_video_chn_g + iVar3 * 2 != puVar1) {
    do {
      if ((puVar1[-0xf] == *param_1) && (puVar1[-0xe] == param_1[1])) {
        ak_thread_mutex_unlock(puVar2);
        return puVar1 + -0xf;
      }
      puVar1 = (undefined4 *)*puVar1;
    } while (&app_video_chn_g + iVar3 * 2 != puVar1);
  }
  ak_thread_mutex_unlock(puVar2);
  return (int *)0x0;
}



undefined4 app_video_check_bind_chn_relation(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *param_1;
  iVar1 = *param_2;
  if (iVar2 == 0xd) {
    uVar3 = 0x1a000002;
    if (iVar1 == 0xe) {
      uVar3 = 0;
    }
    return uVar3;
  }
  if ((iVar2 != 0xe) && (iVar2 != 7)) {
    return 0x1a000000;
  }
  uVar3 = 0x1a000002;
  if (iVar1 == 0xd || iVar1 == 8) {
    uVar3 = 0;
  }
  return uVar3;
}



undefined4 app_video_check_src_range(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((*param_1 - 7U < 8) && (*(uint *)(CSWTCH_39 + (*param_1 - 7U) * 4) < 3)) {
    piVar1 = app_video_find_src_gchn(param_1);
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    uVar2 = 0x1a000006;
    if (piVar1[4] < piVar1[3]) {
      uVar2 = 0;
    }
    return uVar2;
  }
  return 0x1a000000;
}



int * app_video_find_dst_chn(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_1 + 0x14;
  ak_thread_mutex_lock(iVar2);
  piVar1 = *(int **)(param_1 + 0x44);
  if ((int *)(param_1 + 0x44) != piVar1) {
    do {
      if ((piVar1[-0x13] == *param_2) && (piVar1[-0x12] == param_2[1])) {
        ak_thread_mutex_unlock(iVar2);
        return piVar1 + -0x13;
      }
      piVar1 = (int *)*piVar1;
    } while ((int *)(param_1 + 0x44) != piVar1);
  }
  ak_thread_mutex_unlock(iVar2);
  return (int *)0x0;
}



int * app_video_find_dst_chn_by_src_dst(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  
  if (7 < *param_1 - 7U) {
    return (int *)0x0;
  }
  uVar3 = *(uint *)(CSWTCH_39 + (*param_1 - 7U) * 4);
  if (uVar3 < 3) {
    puVar5 = &app_video_chn_glock + uVar3 * 0x18;
    ak_thread_mutex_lock(puVar5);
    for (puVar2 = (undefined4 *)(&app_video_chn_g)[uVar3 * 2];
        &app_video_chn_g + uVar3 * 2 != puVar2; puVar2 = (undefined4 *)*puVar2) {
      if ((puVar2[-0xf] == *param_1) && (puVar2[-0xe] == param_1[1])) {
        puVar1 = puVar2 + -10;
        ak_thread_mutex_lock(puVar1);
        puVar4 = (undefined4 *)puVar2[2];
        if (puVar2 + 2 != puVar4) {
          do {
            if ((*param_2 == puVar4[-0x13]) && (puVar4[-0x12] == param_2[1])) {
              ak_thread_mutex_unlock(puVar1);
              ak_thread_mutex_unlock(puVar5);
              return puVar4 + -0x13;
            }
            puVar4 = (undefined4 *)*puVar4;
          } while (puVar2 + 2 != puVar4);
        }
        ak_thread_mutex_unlock(puVar1);
      }
    }
    ak_thread_mutex_unlock(puVar5);
  }
  return (int *)0x0;
}



int * app_video_find_dst_chn_all(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int local_34 [4];
  
  memset(local_34,0,0xc);
  if ((*param_1 - 7U < 8) && (iVar2 = *(int *)(CSWTCH_39 + (*param_1 - 7U) * 4), -1 < iVar2)) {
    if (iVar2 == 2) {
      local_34[1] = 1;
    }
    else if (iVar2 == 3) {
      local_34[0] = 1;
      local_34[2] = 1;
    }
    else {
      if (iVar2 != 1) {
        return (int *)0x0;
      }
      local_34[2] = iVar2;
      local_34[0] = 1;
    }
    puVar4 = &app_video_chn_glock;
    iVar2 = 0;
    iVar1 = local_34[0];
    while( true ) {
      if (iVar1 != 0) {
        ak_thread_mutex_lock(puVar4);
        puVar6 = (undefined4 *)(&app_video_chn_g)[iVar2 * 2];
        if (puVar6 != &app_video_chn_g + iVar2 * 2) {
          for (; &app_video_chn_g + iVar2 * 2 != puVar6; puVar6 = (undefined4 *)*puVar6) {
            puVar5 = puVar6 + -10;
            ak_thread_mutex_lock(puVar5);
            puVar3 = (undefined4 *)puVar6[2];
            if (puVar6 + 2 != puVar3) {
              do {
                if ((*param_1 == puVar3[-0x13]) && (puVar3[-0x12] == param_1[1])) {
                  ak_thread_mutex_unlock(puVar5);
                  ak_thread_mutex_unlock(puVar4);
                  return puVar3 + -0x13;
                }
                puVar3 = (undefined4 *)*puVar3;
              } while (puVar6 + 2 != puVar3);
            }
            ak_thread_mutex_unlock(puVar5);
          }
        }
        ak_thread_mutex_unlock(puVar4);
      }
      iVar2 = iVar2 + 1;
      puVar4 = puVar4 + 0x18;
      if (iVar2 == 3) break;
      iVar1 = local_34[iVar2];
    }
  }
  return (int *)0x0;
}



undefined4 app_video_free_obj(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    ak_print(0x1a,1,"[%s:%d] the gobj is NULL!\n","app_video_free_obj",0x185);
    uVar1 = 0xffffffff;
  }
  else {
    if (*(int *)(param_1 + 0x2c) != 0) {
      ak_mem_free();
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    ak_thread_mutex_destroy(param_1 + 0x10);
    ak_mem_free(param_1);
    uVar1 = 0;
  }
  return uVar1;
}



void * app_video_gen_obj(void *param_1,void *param_2,size_t param_3)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x1a,0x58,"app_video_gen_obj",uVar1);
  if (__s == (void *)0x0) {
    ak_print(0x1a,1,"[%s:%d] Mem alloc for obj failed!\n","app_video_gen_obj",0x1a1);
  }
  else {
    memset(__s,0,0x58);
    uVar1 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0x1a,param_3,"app_video_gen_obj",uVar1);
    *(int *)((int)__s + 0x2c) = iVar2;
    if (iVar2 == 0) {
      ak_print(0x1a,1,"[%s:%d] Mem alloc for obj->param failed!\n","app_video_gen_obj",0x1ab);
      ak_mem_free(__s);
      __s = (void *)0x0;
    }
    else {
      memcpy(__s,param_1,8);
      memcpy(*(void **)((int)__s + 0x2c),param_2,param_3);
      *(undefined4 *)((int)__s + 0x28) = 0;
      *(undefined4 *)((int)__s + 0x30) = 0;
      *(undefined4 *)((int)__s + 0x40) = 0;
      *(undefined4 *)((int)__s + 0x38) = 0;
      *(undefined4 *)((int)__s + 0x3c) = 0;
      *(int *)((int)__s + 0x44) = (int)__s + 0x44;
      *(int *)((int)__s + 0x48) = (int)__s + 0x44;
      *(int *)((int)__s + 0x4c) = (int)__s + 0x4c;
      *(int *)((int)__s + 0x50) = (int)__s + 0x4c;
      ak_thread_mutex_init((int)__s + 0x10);
    }
  }
  return __s;
}



undefined4 app_video_free_gobj(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    ak_print(0x1a,1,"[%s:%d] the gobj is NULL!\n","app_video_free_gobj",0x1c9);
    uVar1 = 0xffffffff;
  }
  else {
    if (*(int *)(param_1 + 0x38) != 0) {
      ak_mem_free();
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    ak_thread_mutex_destroy(param_1 + 0x14);
    ak_mem_free(param_1);
    uVar1 = 0;
  }
  return uVar1;
}



void * app_video_gen_gobj(void *param_1,void *param_2,size_t param_3)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x1a,0x4c,"app_video_gen_gobj",uVar1);
  if (__s == (void *)0x0) {
    ak_print(0x1a,1,"[%s:%d] Mem alloc for gobj failed!\n","app_video_gen_gobj",0x1e7);
  }
  else {
    memset(__s,0,0x4c);
    uVar1 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0x1a,param_3,"app_video_gen_gobj",uVar1);
    *(int *)((int)__s + 0x38) = iVar2;
    if (iVar2 == 0) {
      ak_print(0x1a,1,"[%s:%d] Mem alloc for gobj->sparam failed!\n","app_video_gen_gobj",0x1f1);
      ak_mem_free(__s);
      __s = (void *)0x0;
    }
    else {
      memcpy(__s,param_1,8);
      memcpy(*(void **)((int)__s + 0x38),param_2,param_3);
      *(int *)((int)__s + 0x44) = (int)__s + 0x44;
      *(int *)((int)__s + 0x48) = (int)__s + 0x44;
      *(undefined4 *)((int)__s + 0xc) = 0;
      *(undefined4 *)((int)__s + 0x10) = 0;
      *(undefined4 *)((int)__s + 0x30) = 0;
      *(undefined4 *)((int)__s + 0x34) = 0;
      *(int *)((int)__s + 0x3c) = (int)__s + 0x3c;
      *(int *)((int)__s + 0x40) = (int)__s + 0x3c;
      ak_thread_mutex_init((int)__s + 0x14);
    }
  }
  return __s;
}



int app_video_vi_stream_do_venc(undefined4 *param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *__s;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  bool bVar11;
  
  uVar10 = *(undefined4 *)(param_2 + 4);
  if (*(int *)(param_2 + 0xc) <= *(int *)(param_2 + 0x40)) {
    ak_print(0x1a,1,"[%s:%d] The frame list in the Chn reached the limitation of frame depth!\n",
             "app_video_vi_stream_do_venc",0x215);
    return 0x1a00000b;
  }
  uVar3 = *(uint *)(param_2 + 8);
  if ((int)uVar3 < 1) goto LAB_00011f94;
  uVar1 = uVar3 >> 0x10;
  if (uVar1 == 0) {
    uVar1 = 1;
  }
  uVar3 = __divsi3(uVar1 * 1000,uVar3 & 0xffff);
  uVar5 = param_1[2];
  iVar6 = param_1[3];
  uVar7 = *(uint *)(param_2 + 0x30);
  uVar8 = *(uint *)(param_2 + 0x38);
  iVar9 = *(int *)(param_2 + 0x3c);
  uVar1 = uVar5 - uVar8;
  if ((uVar7 == 0) ||
     (uVar1 = __aeabi_uldivmod(uVar1,iVar6 - (iVar9 + (uint)(uVar5 < uVar8)),uVar7,0),
     uVar7 == (uVar7 / 1000) * 1000)) {
    ak_print(0x1a,3,
             "[%s:%d] Chn[%d] cur frame ts[%llu], start_time[%llu], total_frame[%d], cur_int[%d], int[%d]!\n"
             ,"app_video_vi_stream_do_venc",0x226,uVar10,uVar5,iVar6,uVar8,iVar9,uVar7,uVar1,uVar3);
    if (*(int *)(param_2 + 0x38) == 0 && *(int *)(param_2 + 0x3c) == 0) goto LAB_000120b0;
  }
  else if (uVar8 == 0 && iVar9 == 0) {
LAB_000120b0:
    uVar2 = param_1[3];
    *(undefined4 *)(param_2 + 0x38) = param_1[2];
    *(undefined4 *)(param_2 + 0x3c) = uVar2;
    goto LAB_00011f94;
  }
  bVar11 = *(int *)(param_2 + 0x30) != 0;
  iVar6 = 0;
  if (bVar11) {
    iVar6 = uVar3 - uVar1;
  }
  if ((bVar11 && uVar3 != uVar1) && iVar6 < 0 == (bVar11 && SBORROW4(uVar3,uVar1))) {
    ak_print(0x1a,5,
             "[%s:%d] Venc frame rate if over the limitation,total_frame[%d], cur_int[%d], int[%d], should drop!\n"
             ,"app_video_vi_stream_do_venc",0x22c,*(int *)(param_2 + 0x30),uVar1,uVar3);
    return 0;
  }
LAB_00011f94:
  uVar2 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0xd,0x20,"app_video_vi_stream_do_venc",uVar2);
  if (__s == (void *)0x0) {
    ak_print(0x1a,1,"[%s:%d] Alloc stream buffer failed!\n","app_video_vi_stream_do_venc",0x238);
    return 0x102;
  }
  memset(__s,0,0x20);
  iVar6 = ak_venc_encode_frame(uVar10,*param_1,param_1[1],param_1[8],__s);
  if (iVar6 == 0) {
    if (*(int *)((int)__s + 4) != 0) {
      uVar10 = param_1[3];
      *(undefined4 *)((int)__s + 8) = param_1[2];
      *(undefined4 *)((int)__s + 0xc) = uVar10;
      ak_thread_mutex_lock(param_2 + 0x10);
      piVar4 = *(int **)(param_2 + 0x48);
      *(int *)(param_2 + 0x30) = *(int *)(param_2 + 0x30) + 1;
      *(int *)(param_2 + 0x40) = *(int *)(param_2 + 0x40) + 1;
      *(int *)(param_2 + 0x48) = (int)__s + 0x18;
      *(int **)((int)__s + 0x1c) = piVar4;
      *(int *)((int)__s + 0x18) = param_2 + 0x44;
      *piVar4 = (int)__s + 0x18;
      ak_thread_mutex_unlock(param_2 + 0x10);
      return 0;
    }
    ak_print(0x1a,1,"[%s:%d] Encoder output data len is 0!\n","app_video_vi_stream_do_venc",0x24b);
    ak_mem_free(__s);
    iVar6 = 0xd000006;
  }
  else {
    ak_print(0x1a,1,"[%s:%d] send to encode failed\n","app_video_vi_stream_do_venc",0x244);
    ak_mem_free(__s);
  }
  return iVar6;
}



int app_video_vi_stream_behavior
              (undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  code *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  ak_thread_mutex_lock(param_2 + 0x14);
  pcVar2 = *(code **)(param_2 + 0x30);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_2,param_1,*(undefined4 *)(param_2 + 0x34),pcVar2,param_4);
  }
  iVar4 = param_2 + 0x44;
  if (iVar4 == *(int *)(param_2 + 0x44)) {
    iVar5 = 0;
  }
  else {
    piVar3 = (int *)(*(int *)(param_2 + 0x44) + -0x4c);
    iVar5 = 0;
    do {
      while (((piVar3[10] == 1 && (*piVar3 - 7U < 8)) &&
             (*(int *)(CSWTCH_39 + (*piVar3 - 7U) * 4) == 1))) {
        iVar5 = app_video_vi_stream_do_venc(param_1,(int)piVar3);
        piVar1 = piVar3 + 0x13;
        piVar3 = (int *)(*piVar1 + -0x4c);
        if (iVar4 == *piVar1) goto LAB_000122c0;
      }
      piVar1 = piVar3 + 0x13;
      piVar3 = (int *)(*piVar1 + -0x4c);
    } while (iVar4 != *piVar1);
  }
LAB_000122c0:
  ak_thread_mutex_unlock(param_2 + 0x14);
  return iVar5;
}



undefined4 app_video_vi_stream_th(int param_1)

{
  undefined4 extraout_r2;
  int iVar1;
  int param3;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 auStack_50 [11];
  
  param3 = *(int *)(param_1 + 4);
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  snprintf((char *)&local_70,0x20,"vi_stream_%d",param3);
  ak_thread_set_name(&local_70);
  iVar1 = *(int *)(param_1 + 8);
  do {
    if (iVar1 == 0) {
      return 0;
    }
    while( true ) {
      memset(auStack_50,0,0x28);
      iVar1 = ak_vi_get_frame(param3,auStack_50);
      if (iVar1 != 0) break;
      error_count_7425 = 0;
      app_video_vi_stream_behavior(auStack_50,param_1,extraout_r2,0);
      ak_vi_release_frame(param3,auStack_50);
      if (*(int *)(param_1 + 8) == 0) {
        return 0;
      }
    }
    if (0x32 < error_count_7425) {
      ak_print(0x1a,4,"[%s:%d] get frame failed!\n","app_video_vi_stream_th",0x2b4);
      error_count_7425 = 0;
    }
    ak_sleep_ms(10);
    iVar1 = *(int *)(param_1 + 8);
  } while( true );
}



undefined4 app_video_unbind_vi_venc(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  
  piVar3 = app_video_find_src_gchn(param_1);
  if (piVar3 == (int *)0x0) {
    ak_print(0x1a,1,"[%s:%d] the Src Chn is not binded!\n","app_video_unbind_vi_venc",0x2cc);
    return 0x1a000005;
  }
  piVar4 = app_video_find_dst_chn((int)piVar3,param_2);
  if (piVar4 == (int *)0x0) {
    ak_print(0x1a,1,"[%s:%d] the Dest Chn is not binded!\n","app_video_unbind_vi_venc",0x2d6);
    return 0x1a000004;
  }
  ak_thread_mutex_lock(piVar3 + 5);
  iVar5 = piVar4[0x13];
  piVar7 = (int *)piVar4[0x14];
  *(int **)(iVar5 + 4) = piVar7;
  *piVar7 = iVar5;
  piVar4[0x13] = 0x100100;
  piVar4[0x14] = 0x200200;
  ak_thread_mutex_unlock(piVar3 + 5);
  ak_thread_mutex_lock(piVar4 + 4);
  piVar10 = piVar4 + 0x11;
  piVar7 = (int *)*piVar10;
  if (piVar10 != piVar7) {
    piVar6 = (int *)*piVar7;
    piVar2 = (int *)*piVar7;
    do {
      piVar1 = piVar2;
      puVar8 = (undefined4 *)piVar7[1];
      iVar5 = piVar4[1];
      piVar6[1] = (int)puVar8;
      *puVar8 = piVar6;
      *piVar7 = 0x100100;
      piVar7[1] = 0x200200;
      ak_venc_release_stream(iVar5,piVar7 + -6);
      piVar4[0x10] = piVar4[0x10] + -1;
      ak_mem_free(piVar7 + -6);
      piVar6 = (int *)*piVar1;
      piVar2 = piVar6;
      piVar7 = piVar1;
    } while (piVar1 != piVar10);
  }
  ak_thread_mutex_unlock(piVar4 + 4);
  app_video_free_obj((int)piVar4);
  if (*piVar3 - 7U < 8) {
    iVar5 = *(int *)(CSWTCH_39 + (*piVar3 - 7U) * 4);
  }
  else {
    iVar5 = -1;
  }
  ak_thread_mutex_lock(&app_video_chn_glock + iVar5 * 0x18);
  iVar9 = piVar3[4];
  piVar3[4] = iVar9 + -1;
  if (iVar9 + -1 == 0) {
    piVar3[2] = 0;
    ak_thread_join(piVar3[0xb]);
    piVar4 = (int *)piVar3[0x10];
    iVar9 = piVar3[0xf];
    *(int **)(iVar9 + 4) = piVar4;
    *piVar4 = iVar9;
    piVar3[0xf] = 0x100100;
    piVar3[0x10] = 0x200200;
    app_video_free_gobj((int)piVar3);
  }
  ak_thread_mutex_unlock(&app_video_chn_glock + iVar5 * 0x18);
  return 0;
}



int app_video_bind_vi_venc(int *param_1,void *param_2,void *param_3)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined1 auStack_b0 [8];
  int local_a8;
  int local_a4;
  undefined1 auStack_9c [56];
  ushort local_64;
  ushort local_62;
  
  uVar5 = param_1[1];
  uVar6 = *(undefined4 *)((int)param_2 + 4);
  if (3 < uVar5) {
    ak_print(0x1a,1,"[%s:%d]  vi_chn is incorrect[%d]\n","app_video_bind_vi_venc",0x319,uVar5);
    return 0x7000004;
  }
  memset(auStack_9c,0,0x38);
  iVar1 = ak_vi_get_dev_attr(1 < (int)uVar5,auStack_9c);
  if (iVar1 == 0) {
    memset(auStack_b0,0,0x14);
    iVar1 = ak_vi_get_chn_attr(uVar5,auStack_b0);
    if (iVar1 != 0) {
      ak_print(0x1a,1,"[%s:%d] Vi get chn_id[%d] chn attr error[%d]\n","app_video_bind_vi_venc",
               0x334,uVar5,iVar1);
      return iVar1;
    }
    memset(&local_64,0,0x3c);
    iVar1 = ak_venc_get_attr(uVar6,&local_64);
    if (iVar1 == 0) {
      if (((int)(uint)local_64 < local_a8) || ((int)(uint)local_62 < local_a4)) {
        ak_print(0x1a,1,"[%s:%d] The vi res[%d]*[%d] is small then encoder res[%d]*[%d]!\n",
                 "app_video_bind_vi_venc",0x345,local_a8,local_a4,(uint)local_64,(uint)local_62);
        return 0x1a000007;
      }
      pvVar2 = app_video_gen_obj(param_2,&local_64,0x3c);
      if (pvVar2 == (void *)0x0) {
        ak_print(0x1a,1,"[%s:%d] Generate dst obj failed!\n","app_video_bind_vi_venc",0x34f);
        iVar1 = 0x1a000009;
      }
      else {
        memcpy((void *)((int)pvVar2 + 8),param_3,8);
        piVar3 = app_video_find_src_gchn(param_1);
        if (piVar3 == (int *)0x0) {
          piVar3 = app_video_gen_gobj(param_1,auStack_b0,0x14);
          if (piVar3 == (int *)0x0) {
            ak_print(0x1a,1,"[%s:%d] Generate group obj failed!\n","app_video_bind_vi_venc",0x35e);
            app_video_free_obj((int)pvVar2);
            return 0x1a000008;
          }
          piVar3[3] = 8;
          ak_thread_mutex_lock(&app_video_chn_glock);
          piVar3[0xf] = (int)&app_video_chn_g;
          piVar3[0x10] = (int)DAT_00024078;
          piVar4 = piVar3 + 0xf;
          *DAT_00024078 = (int)(piVar3 + 0xf);
          DAT_00024078 = piVar4;
          ak_thread_mutex_unlock(&app_video_chn_glock);
        }
        ak_thread_mutex_lock(piVar3 + 5);
        iVar1 = piVar3[4];
        iVar7 = piVar3[2];
        piVar4 = (int *)piVar3[0x12];
        piVar3[0x12] = (int)pvVar2 + 0x4c;
        *(int **)((int)pvVar2 + 0x50) = piVar4;
        *(int **)((int)pvVar2 + 0x4c) = piVar3 + 0x11;
        *piVar4 = (int)pvVar2 + 0x4c;
        piVar3[4] = iVar1 + 1;
        if (iVar7 == 0) {
          piVar3[2] = 1;
          ak_thread_create(piVar3 + 0xb,app_video_vi_stream_th,piVar3,0x19000,0x50);
        }
        ak_thread_mutex_unlock(piVar3 + 5);
        iVar1 = 0;
      }
    }
    else {
      ak_print(0x1a,1,"[%s:%d] Venc [%d] get attribute failed [%d]!\n","app_video_bind_vi_venc",
               0x33e,uVar6,iVar1);
    }
  }
  else {
    ak_print(0x1a,1,"[%s:%d] Vi get dev[%d] dev attr error[%d]\n","app_video_bind_vi_venc",0x32a,
             1 < (int)uVar5,iVar1);
  }
  return iVar1;
}



undefined4 app_video_unbind_chn(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  
  if (7 < *param_1 - 7U) {
    return 0x1a000000;
  }
  uVar11 = *(uint *)(CSWTCH_39 + (*param_1 - 7U) * 4);
  if (7 < *param_2 - 7U) {
    if (uVar11 < 3) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0x1a000000;
    }
    return uVar5;
  }
  if (uVar11 == 0) {
    if (*(int *)(CSWTCH_39 + (*param_2 - 7U) * 4) == 1) {
      piVar3 = app_video_find_src_gchn(param_1);
      if (piVar3 == (int *)0x0) {
        ak_print(0x1a,1,"[%s:%d] the Src Chn is not binded!\n","app_video_unbind_vi_venc",0x2cc);
        return 0x1a000005;
      }
      piVar4 = app_video_find_dst_chn((int)piVar3,param_2);
      if (piVar4 != (int *)0x0) {
        ak_thread_mutex_lock(piVar3 + 5);
        iVar6 = piVar4[0x13];
        piVar8 = (int *)piVar4[0x14];
        *(int **)(iVar6 + 4) = piVar8;
        *piVar8 = iVar6;
        piVar4[0x13] = 0x100100;
        piVar4[0x14] = 0x200200;
        ak_thread_mutex_unlock(piVar3 + 5);
        ak_thread_mutex_lock(piVar4 + 4);
        piVar12 = piVar4 + 0x11;
        piVar8 = (int *)*piVar12;
        if (piVar12 != piVar8) {
          piVar7 = (int *)*piVar8;
          piVar2 = (int *)*piVar8;
          do {
            piVar1 = piVar2;
            puVar9 = (undefined4 *)piVar8[1];
            iVar6 = piVar4[1];
            piVar7[1] = (int)puVar9;
            *puVar9 = piVar7;
            *piVar8 = 0x100100;
            piVar8[1] = 0x200200;
            ak_venc_release_stream(iVar6,piVar8 + -6);
            piVar4[0x10] = piVar4[0x10] + -1;
            ak_mem_free(piVar8 + -6);
            piVar7 = (int *)*piVar1;
            piVar2 = piVar7;
            piVar8 = piVar1;
          } while (piVar1 != piVar12);
        }
        ak_thread_mutex_unlock(piVar4 + 4);
        app_video_free_obj((int)piVar4);
        if (*piVar3 - 7U < 8) {
          iVar6 = *(int *)(CSWTCH_39 + (*piVar3 - 7U) * 4);
        }
        else {
          iVar6 = -1;
        }
        ak_thread_mutex_lock(&app_video_chn_glock + iVar6 * 0x18);
        iVar10 = piVar3[4];
        piVar3[4] = iVar10 + -1;
        if (iVar10 + -1 == 0) {
          piVar3[2] = 0;
          ak_thread_join(piVar3[0xb]);
          piVar4 = (int *)piVar3[0x10];
          iVar10 = piVar3[0xf];
          *(int **)(iVar10 + 4) = piVar4;
          *piVar4 = iVar10;
          piVar3[0xf] = 0x100100;
          piVar3[0x10] = 0x200200;
          app_video_free_gobj((int)piVar3);
        }
        ak_thread_mutex_unlock(&app_video_chn_glock + iVar6 * 0x18);
        return 0;
      }
      ak_print(0x1a,1,"[%s:%d] the Dest Chn is not binded!\n","app_video_unbind_vi_venc",0x2d6);
      return 0x1a000004;
    }
  }
  else {
    if ((int)uVar11 < 0) {
      return 0x1a000000;
    }
    if (2 < (int)uVar11) {
      return 0x1a000000;
    }
  }
  return 0;
}



int app_video_bind_chn(int *param_1,int *param_2,void *param_3)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined1 auStack_b0 [8];
  int iStack_a8;
  int iStack_a4;
  undefined1 auStack_9c [56];
  ushort uStack_64;
  ushort uStack_62;
  
  if (7 < *param_1 - 7U) {
    return 0x1a000000;
  }
  uVar6 = *(uint *)(CSWTCH_39 + (*param_1 - 7U) * 4);
  if (*param_2 - 7U < 8) {
    if (uVar6 == 0) {
      if (*(int *)(CSWTCH_39 + (*param_2 - 7U) * 4) == 1) {
        uVar6 = param_1[1];
        iVar4 = param_2[1];
        if (3 < uVar6) {
          ak_print(0x1a,1,"[%s:%d]  vi_chn is incorrect[%d]\n","app_video_bind_vi_venc",0x319,uVar6)
          ;
          return 0x7000004;
        }
        memset(auStack_9c,0,0x38);
        iVar1 = ak_vi_get_dev_attr(1 < (int)uVar6,auStack_9c);
        if (iVar1 == 0) {
          memset(auStack_b0,0,0x14);
          iVar1 = ak_vi_get_chn_attr(uVar6,auStack_b0);
          if (iVar1 != 0) {
            ak_print(0x1a,1,"[%s:%d] Vi get chn_id[%d] chn attr error[%d]\n",
                     "app_video_bind_vi_venc",0x334,uVar6,iVar1);
            return iVar1;
          }
          memset(&uStack_64,0,0x3c);
          iVar1 = ak_venc_get_attr(iVar4,&uStack_64);
          if (iVar1 == 0) {
            if (((int)(uint)uStack_64 < iStack_a8) || ((int)(uint)uStack_62 < iStack_a4)) {
              ak_print(0x1a,1,"[%s:%d] The vi res[%d]*[%d] is small then encoder res[%d]*[%d]!\n",
                       "app_video_bind_vi_venc",0x345,iStack_a8,iStack_a4,(uint)uStack_64,
                       (uint)uStack_62);
              return 0x1a000007;
            }
            pvVar2 = app_video_gen_obj(param_2,&uStack_64,0x3c);
            if (pvVar2 == (void *)0x0) {
              ak_print(0x1a,1,"[%s:%d] Generate dst obj failed!\n","app_video_bind_vi_venc",0x34f);
              iVar1 = 0x1a000009;
            }
            else {
              memcpy((void *)((int)pvVar2 + 8),param_3,8);
              piVar3 = app_video_find_src_gchn(param_1);
              if (piVar3 == (int *)0x0) {
                piVar3 = app_video_gen_gobj(param_1,auStack_b0,0x14);
                if (piVar3 == (int *)0x0) {
                  ak_print(0x1a,1,"[%s:%d] Generate group obj failed!\n","app_video_bind_vi_venc",
                           0x35e);
                  app_video_free_obj((int)pvVar2);
                  return 0x1a000008;
                }
                piVar3[3] = 8;
                ak_thread_mutex_lock(&app_video_chn_glock);
                piVar3[0xf] = (int)&app_video_chn_g;
                piVar3[0x10] = (int)DAT_00024078;
                piVar5 = piVar3 + 0xf;
                *DAT_00024078 = (int)(piVar3 + 0xf);
                DAT_00024078 = piVar5;
                ak_thread_mutex_unlock(&app_video_chn_glock);
              }
              ak_thread_mutex_lock(piVar3 + 5);
              iVar4 = piVar3[4];
              iVar1 = piVar3[2];
              piVar5 = (int *)piVar3[0x12];
              piVar3[0x12] = (int)pvVar2 + 0x4c;
              *(int **)((int)pvVar2 + 0x50) = piVar5;
              *(int **)((int)pvVar2 + 0x4c) = piVar3 + 0x11;
              *piVar5 = (int)pvVar2 + 0x4c;
              piVar3[4] = iVar4 + 1;
              if (iVar1 == 0) {
                piVar3[2] = 1;
                ak_thread_create(piVar3 + 0xb,app_video_vi_stream_th,piVar3,0x19000,0x50);
              }
              ak_thread_mutex_unlock(piVar3 + 5);
              iVar1 = 0;
            }
          }
          else {
            ak_print(0x1a,1,"[%s:%d] Venc [%d] get attribute failed [%d]!\n",
                     "app_video_bind_vi_venc",0x33e,iVar4,iVar1);
          }
        }
        else {
          ak_print(0x1a,1,"[%s:%d] Vi get dev[%d] dev attr error[%d]\n","app_video_bind_vi_venc",
                   0x32a,1 < (int)uVar6,iVar1);
        }
        return iVar1;
      }
    }
    else if (((int)uVar6 < 0) || (2 < (int)uVar6)) {
      return 0x1a000000;
    }
    return 0;
  }
  if (uVar6 < 3) {
    iVar4 = 0;
  }
  else {
    iVar4 = 0x1a000000;
  }
  return iVar4;
}



undefined4 ak_app_video_set_dst_chn_active(int *param_1,uint param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_1 != (int *)0x0) {
    if (param_2 < 2) {
      piVar2 = app_video_find_dst_chn_all(param_1);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1a,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_video_set_dst_chn_active",
                 0x3fe);
        uVar1 = 0x1a000004;
      }
      else {
        ak_thread_mutex_lock(piVar2 + 4);
        piVar2[10] = param_2;
        if (param_2 == 1) {
          piVar2[0xc] = 0;
          piVar2[0xe] = 0;
          piVar2[0xf] = 0;
        }
        ak_thread_mutex_unlock(piVar2 + 4);
        uVar1 = 0;
      }
    }
    else {
      ak_print(0x1a,1,"[%s:%d] The enable status  is invalid!\n","ak_app_video_set_dst_chn_active",
               0x3f5);
      uVar1 = 0x101;
    }
    return uVar1;
  }
  ak_print(0x1a,1,"[%s:%d] The input param is NULL!\n","ak_app_video_set_dst_chn_active",0x3ef);
  return 0x101;
}



undefined4 ak_app_video_venc_get_stream(int *param_1,void *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  if (param_2 == (void *)0x0 || param_1 == (int *)0x0) {
    ak_print(0x1a,1,"[%s:%d] The input param is NULL!\n","ak_app_video_venc_get_stream",0x417);
    return 0x101;
  }
  if ((*param_1 == 0xd) && (-1 < param_1[1])) {
    piVar2 = app_video_find_dst_chn_all(param_1);
    if (piVar2 == (int *)0x0) {
      ak_print(0x1a,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_video_venc_get_stream",0x426);
      uVar1 = 0x1a000004;
    }
    else if (piVar2 + 0x11 == (int *)piVar2[0x11]) {
      uVar1 = 0x1a00000a;
    }
    else {
      ak_thread_mutex_lock(piVar2 + 4);
      piVar4 = (int *)piVar2[0x11];
      if (piVar2 + 0x11 != piVar4) {
        piVar3 = (int *)piVar4[1];
        iVar5 = *piVar4;
        *(int **)(iVar5 + 4) = piVar3;
        *piVar3 = iVar5;
        *piVar4 = 0x100100;
        piVar4[1] = 0x200200;
        memcpy(param_2,piVar4 + -6,0x18);
        piVar2[0x10] = piVar2[0x10] + -1;
        ak_mem_free(piVar4 + -6);
      }
      ak_thread_mutex_unlock(piVar2 + 4);
      uVar1 = 0;
    }
  }
  else {
    ak_print(0x1a,1,"[%s:%d] The Chn param is invalid!\n","ak_app_video_venc_get_stream",0x41d);
    uVar1 = 0x101;
  }
  return uVar1;
}



int ak_app_video_unbind_chn(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 == (int *)0x0 || param_1 == (int *)0x0) {
    ak_print(0x1a,1,"[%s:%d] The Input param is invalid!\n","ak_app_video_unbind_chn",0x44f);
    return 0x101;
  }
  iVar1 = app_video_check_bind_chn_relation(param_1,param_2);
  if (iVar1 == 0) {
    piVar2 = app_video_find_src_gchn(param_1);
    if (piVar2 == (int *)0x0) {
      ak_print(0x1a,1,"[%s:%d] the Src Chn is not binded!\n","ak_app_video_unbind_chn",0x45f);
      iVar1 = 0x1a000005;
    }
    else {
      piVar2 = app_video_find_dst_chn((int)piVar2,param_2);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1a,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_video_unbind_chn",0x468);
        iVar1 = 0x1a000004;
      }
      else if (piVar2[10] == 1) {
        ak_print(0x1a,1,"[%s:%d] The Dest Chn should be disabled before unbind chn!\n",
                 "ak_app_video_unbind_chn",0x46f);
        iVar1 = 0x1a00000c;
      }
      else {
        iVar1 = app_video_unbind_chn(param_1,param_2);
        if (iVar1 != 0) {
          ak_print(0x1a,1,"[%s:%d] Chn unbind Error:[%x]!\n","ak_app_video_unbind_chn",0x477,iVar1);
        }
      }
    }
  }
  else {
    ak_print(0x1a,1,"[%s:%d] the relation ship between Chns is incorrect!\n",
             "ak_app_video_unbind_chn",0x457);
  }
  return iVar1;
}



int ak_app_video_bind_chn(int *param_1,int *param_2,void *param_3)

{
  int iVar1;
  int *piVar2;
  char acStack_58 [68];
  
  if (dbg_init_flag == 0) {
    dbg_init_flag = 1;
    memset(acStack_58,0,0x40);
    snprintf(acStack_58,0x40,"version=%s","libapp_video V1.0.07");
    ak_debug_info(0x1a,1,acStack_58);
  }
  if (param_1 == (int *)0x0 || (param_3 == (void *)0x0 || param_2 == (int *)0x0)) {
    ak_print(0x1a,1,"[%s:%d] The Input param is invalid!\n","ak_app_video_bind_chn",0x493);
    iVar1 = 0x101;
  }
  else {
    iVar1 = app_video_check_bind_chn_relation(param_1,param_2);
    if (iVar1 != 0) {
      ak_print(0x1a,1,"[%s:%d] the relation ship between Chns is incorrect!\n",
               "ak_app_video_bind_chn",0x49b);
      return iVar1;
    }
    iVar1 = app_video_check_src_range(param_1);
    if (iVar1 == 0) {
      piVar2 = app_video_find_dst_chn_all(param_2);
      if (piVar2 != (int *)0x0) {
        ak_print(0x1a,1,"[%s:%d] the Dest Chn is already binded!\n","ak_app_video_bind_chn",0x4ac);
        return 0x1a000003;
      }
      iVar1 = app_video_bind_chn(param_1,param_2,param_3);
      if (iVar1 != 0) {
        ak_print(0x1a,1,"[%s:%d] Chn bind Error:[%x]!\n","ak_app_video_bind_chn",0x4b4,iVar1);
      }
    }
    else {
      ak_print(0x1a,1,"[%s:%d] the src chn is reach to the max bind range!\n",
               "ak_app_video_bind_chn",0x4a3);
    }
  }
  return iVar1;
}



undefined4 ak_app_video_set_chn_attr(int *param_1,void *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_2 == (void *)0x0 || param_1 == (int *)0x0) {
    ak_print(0x1a,1,"[%s:%d] The Input param is invalid!\n","ak_app_video_set_chn_attr",0x4c0);
    uVar1 = 0x101;
  }
  else {
    piVar2 = app_video_find_dst_chn_all(param_1);
    if (piVar2 != (int *)0x0) {
      memcpy(piVar2 + 2,param_2,8);
      return 0;
    }
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 ak_app_video_set_cb(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  
  piVar1 = app_video_find_src_gchn(param_1);
  if (piVar1 != (int *)0x0) {
    ak_thread_mutex_lock(piVar1 + 5);
    piVar1[0xc] = param_2;
    piVar1[0xd] = param_3;
    ak_thread_mutex_unlock(piVar1 + 5);
    return 0;
  }
  ak_print(0xfe,1,"cant find the source chn",ak_print,param_4);
  return 0xffffffff;
}



undefined4 ak_app_video_unset_cb(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_video_find_src_gchn(param_1);
  if (piVar1 != (int *)0x0) {
    ak_thread_mutex_lock(piVar1 + 5);
    piVar1[0xc] = 0;
    piVar1[0xd] = 0;
    ak_thread_mutex_unlock(piVar1 + 5);
    return 0;
  }
  ak_print(0xfe,1,"cant find the source chn");
  return 0xffffffff;
}



uint __divsi3(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  if (param_2 == 0) {
    uVar2 = __aeabi_idiv0();
    return uVar2;
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



uint _divsi3_skip_div0_test(uint param_1,uint param_2)

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



void __aeabi_idivmod(uint param_1,uint param_2)

{
  if (param_2 != 0) {
    _divsi3_skip_div0_test(param_1,param_2);
    return;
  }
  __aeabi_idiv0();
  return;
}



undefined4 __aeabi_uldivmod(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  ulonglong uVar2;
  ulonglong local_8;
  
  if (param_4 != 0 || param_3 != 0) {
    uVar2 = __gnu_uldivmod_helper(CONCAT44(param_2,param_1),CONCAT44(param_4,param_3),&local_8);
    return (int)uVar2;
  }
  uVar1 = __aeabi_idiv0();
  return uVar1;
}



void __aeabi_idiv0(void)

{
  raise(8);
  return;
}



longlong __gnu_ldivmod_helper(longlong a,longlong b,longlong *remainder)

{
  uint uVar1;
  DItype DVar2;
  
                    // Unresolved local var: longlong quotient@[DW_OP_reg0(r0); DW_OP_piece: 4;
                    // DW_OP_reg1(r1); DW_OP_piece: 4]
  DVar2 = __divdi3(a,b);
  uVar1 = (uint)(DVar2 * b);
  *(uint *)remainder = (uint)a - uVar1;
  *(uint *)((int)remainder + 4) =
       (int)((ulonglong)a >> 0x20) -
       ((int)((ulonglong)(DVar2 * b) >> 0x20) + (uint)((uint)a < uVar1));
  return DVar2;
}



ulonglong __gnu_uldivmod_helper(ulonglong a,ulonglong b,ulonglong *remainder)

{
  uint uVar1;
  UDItype UVar2;
  
                    // Unresolved local var: ulonglong quotient@[DW_OP_reg0(r0); DW_OP_piece: 4;
                    // DW_OP_reg1(r1); DW_OP_piece: 4]
  UVar2 = __udivdi3(a,b);
  uVar1 = (uint)(UVar2 * b);
  *(uint *)remainder = (uint)a - uVar1;
  *(uint *)((int)remainder + 4) =
       (int)(a >> 0x20) - ((int)(UVar2 * b >> 0x20) + (uint)((uint)a < uVar1));
  return UVar2;
}



DItype __divdi3(DItype u,DItype v)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  undefined8 uVar15;
  longlong lVar16;
  
                    // Unresolved local var: SItype c@[???]
                    // Unresolved local var: DWunion uu@[???]
                    // Unresolved local var: DWunion vv@[???]
                    // Unresolved local var: DItype w@[???]
  if (u < 0) {
    u = CONCAT44(-((int)((ulonglong)u >> 0x20) + (uint)((int)u != 0)),-(int)u);
    uVar11 = 0xffffffff;
  }
  else {
    uVar11 = 0;
  }
  uVar7 = (uint)((ulonglong)u >> 0x20);
  uVar10 = (uint)u;
  if (v < 0) {
    uVar11 = ~uVar11;
    v = CONCAT44(-((int)((ulonglong)v >> 0x20) + (uint)((int)v != 0)),-(int)v);
  }
  uVar2 = (uint)((ulonglong)v >> 0x20);
  uVar1 = (uint)v;
                    // Unresolved local var: UDItype q@[???]
                    // Unresolved local var: UDItype r@[???]
                    // Unresolved local var: UDItype y@[???]
                    // Unresolved local var: USItype lz1@[???]
                    // Unresolved local var: USItype lz2@[???]
                    // Unresolved local var: USItype i@[???]
                    // Unresolved local var: USItype k@[???]
  bVar14 = uVar7 <= uVar2;
  bVar12 = uVar2 == uVar7;
  if (bVar12) {
    bVar14 = uVar10 <= uVar1;
  }
  bVar13 = uVar1 != uVar10;
  if (bVar14 && (!bVar12 || bVar13)) {
    uVar1 = 0;
  }
  if (bVar14 && (!bVar12 || bVar13)) {
    uVar2 = 0;
  }
  lVar16 = CONCAT44(uVar2,uVar1);
  if (!bVar14 || v == u) {
    if (uVar2 == 0) {
      iVar8 = LZCOUNT(uVar1) + 0x20;
    }
    else {
      iVar8 = LZCOUNT(uVar2);
    }
    if (uVar7 == 0) {
      iVar3 = LZCOUNT(uVar10) + 0x20;
    }
    else {
      iVar3 = LZCOUNT(uVar7);
    }
    uVar9 = iVar8 - iVar3;
    uVar15 = __aeabi_llsl(uVar1,uVar2,uVar9);
    uVar1 = (uint)((ulonglong)uVar15 >> 0x20);
    uVar2 = (uint)uVar15;
    bVar14 = uVar1 <= uVar7;
    if (uVar7 == uVar1) {
      bVar14 = uVar2 <= uVar10;
    }
    if (bVar14) {
      u = CONCAT44(uVar7 - (uVar1 + (uVar10 < uVar2)),uVar10 - uVar2);
      lVar16 = __aeabi_llsl(1,0,uVar9);
    }
    else {
      lVar16 = 0;
    }
    if (uVar9 != 0) {
      uVar1 = uVar1 >> 1;
      uVar7 = (uint)((byte)((ulonglong)uVar15 >> 0x20) & 1) << 0x1f | uVar2 >> 1;
      uVar10 = uVar9;
      do {
        uVar6 = (uint)((ulonglong)u >> 0x20);
        uVar2 = (uint)u;
        bVar14 = uVar1 <= uVar6;
        if (uVar6 == uVar1) {
          bVar14 = uVar7 <= uVar2;
        }
        if (bVar14) {
          uVar4 = uVar2 - uVar7;
          uVar5 = uVar4 * 2 + 1;
          uVar2 = (uVar6 - (uVar1 + (uVar2 < uVar7))) * 2 + (uint)CARRY4(uVar4,uVar4) +
                  (uint)(0xfffffffe < uVar4 * 2);
        }
        else {
          uVar5 = uVar2 * 2;
          uVar2 = uVar6 * 2 + (uint)CARRY4(uVar2,uVar2);
        }
        u = CONCAT44(uVar2,uVar5);
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      uVar7 = (uint)(lVar16 + u);
      uVar15 = __lshrdi3(uVar5,uVar2,uVar9);
      uVar15 = __aeabi_llsl((uint)uVar15,(int)((ulonglong)uVar15 >> 0x20),uVar9);
      lVar16 = CONCAT44((int)((ulonglong)(lVar16 + u) >> 0x20) -
                        ((int)((ulonglong)uVar15 >> 0x20) + (uint)(uVar7 < (uint)uVar15)),
                        uVar7 - (uint)uVar15);
    }
  }
  if (uVar11 == 0) {
    return lVar16;
  }
  return CONCAT44(-((int)((ulonglong)lVar16 >> 0x20) + (uint)((int)lVar16 != 0)),-(int)lVar16);
}



UDItype __udivdi3(UDItype n,UDItype d)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  undefined8 uVar12;
  UDItype UVar13;
  
  uVar6 = (uint)(d >> 0x20);
  uVar2 = (uint)d;
  uVar9 = (uint)(n >> 0x20);
  uVar10 = (uint)n;
                    // Unresolved local var: UDItype q@[???]
                    // Unresolved local var: UDItype r@[???]
                    // Unresolved local var: UDItype y@[???]
                    // Unresolved local var: USItype lz1@[???]
                    // Unresolved local var: USItype lz2@[???]
                    // Unresolved local var: USItype i@[???]
                    // Unresolved local var: USItype k@[???]
  bVar11 = uVar9 <= uVar6;
  if (uVar6 == uVar9) {
    bVar11 = uVar10 <= uVar2;
  }
  if (bVar11 && n != d) {
    return 0;
  }
  if (uVar6 == 0) {
    iVar7 = LZCOUNT(uVar2) + 0x20;
  }
  else {
    iVar7 = LZCOUNT(uVar6);
  }
  if (uVar9 == 0) {
    iVar1 = LZCOUNT(uVar10) + 0x20;
  }
  else {
    iVar1 = LZCOUNT(uVar9);
  }
  uVar8 = iVar7 - iVar1;
  uVar12 = __aeabi_llsl(uVar2,uVar6,uVar8);
  uVar2 = (uint)((ulonglong)uVar12 >> 0x20);
  uVar6 = (uint)uVar12;
  bVar11 = uVar2 <= uVar9;
  if (uVar9 == uVar2) {
    bVar11 = uVar6 <= uVar10;
  }
  if (bVar11) {
    n = CONCAT44(uVar9 - (uVar2 + (uVar10 < uVar6)),uVar10 - uVar6);
    UVar13 = __aeabi_llsl(1,0,uVar8);
  }
  else {
    UVar13 = 0;
  }
  if (uVar8 == 0) {
    return UVar13;
  }
  uVar2 = uVar2 >> 1;
  uVar10 = (uint)((byte)((ulonglong)uVar12 >> 0x20) & 1) << 0x1f | uVar6 >> 1;
  uVar9 = uVar8;
  do {
    uVar5 = (uint)(n >> 0x20);
    uVar6 = (uint)n;
    bVar11 = uVar2 <= uVar5;
    if (uVar5 == uVar2) {
      bVar11 = uVar10 <= uVar6;
    }
    if (bVar11) {
      uVar3 = uVar6 - uVar10;
      uVar4 = uVar3 * 2 + 1;
      uVar6 = (uVar5 - (uVar2 + (uVar6 < uVar10))) * 2 + (uint)CARRY4(uVar3,uVar3) +
              (uint)(0xfffffffe < uVar3 * 2);
    }
    else {
      uVar4 = uVar6 * 2;
      uVar6 = uVar5 * 2 + (uint)CARRY4(uVar6,uVar6);
    }
    n = CONCAT44(uVar6,uVar4);
    uVar9 = uVar9 - 1;
  } while (uVar9 != 0);
  uVar10 = (uint)(UVar13 + n);
  uVar12 = __lshrdi3(uVar4,uVar6,uVar8);
  uVar12 = __aeabi_llsl((uint)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar8);
  return CONCAT44((int)(UVar13 + n >> 0x20) -
                  ((int)((ulonglong)uVar12 >> 0x20) + (uint)(uVar10 < (uint)uVar12)),
                  uVar10 - (uint)uVar12);
}



undefined8 __lshrdi3(uint param_1,uint param_2,uint param_3)

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



undefined8 __aeabi_llsl(uint param_1,int param_2,uint param_3)

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


