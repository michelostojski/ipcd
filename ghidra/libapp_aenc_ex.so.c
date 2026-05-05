typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned short    word;
typedef pointer pointer __((offset(0x8)));

typedef pointer pointer __((offset(0x18)));

typedef pointer pointer __((offset(0x10)));

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

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;



undefined1 completed.8508;
pointer __DT_PLTGOT;
dword __FRAME_END__;
undefined4 __dso_handle;
undefined __register_frame_info;
undefined1[24] object.8513;
undefined1 CSWTCH.35;
undefined1 app_audio_chn_glock;
undefined4 app_audio_chn_g;
undefined4 error_count.7519;
undefined app_audio_ai_stream_th;
int *DAT_00024074;
undefined ak_print;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



void * app_audio_gen_obj(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
  pvVar1 = app_audio_gen_obj(param_1,param_2,param_3);
  return pvVar1;
}



int app_audio_ai_stream_behavior
              (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = app_audio_ai_stream_behavior(param_1,param_2,param_3,param_4);
  return iVar1;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



undefined4 app_audio_check_bind_chn_relation(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_check_bind_chn_relation(param_1,param_2);
  return uVar1;
}



int app_audio_ai_stream_do_aenc(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = app_audio_ai_stream_do_aenc(param_1,param_2);
  return iVar1;
}



undefined4 app_audio_free_obj(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_free_obj(param_1);
  return uVar1;
}



undefined4 app_audio_free_gobj(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_free_gobj(param_1);
  return uVar1;
}



void * app_audio_gen_gobj(void *param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
  pvVar1 = app_audio_gen_gobj(param_1,param_2,param_3);
  return pvVar1;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



undefined4 app_audio_check_src_range(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_check_src_range(param_1);
  return uVar1;
}



int * app_audio_find_dst_chn_all(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_audio_find_dst_chn_all(param_1);
  return piVar1;
}



int * app_audio_find_src_gchn(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_audio_find_src_gchn(param_1);
  return piVar1;
}



undefined4 app_audio_bind_chn(int *param_1,int *param_2,void *param_3)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_bind_chn(param_1,param_2,param_3);
  return uVar1;
}



int * app_audio_find_dst_chn(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = app_audio_find_dst_chn(param_1,param_2);
  return piVar1;
}



undefined4 app_audio_unbind_chn(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = app_audio_unbind_chn(param_1,param_2);
  return uVar1;
}



void __register_frame_info(void)

{
  __register_frame_info();
  return;
}



// WARNING: Removing unreachable block (ram,0x0001114c)
// WARNING: Removing unreachable block (ram,0x00011164)
// WARNING: Removing unreachable block (ram,0x0001116c)

void processEntry deregister_tm_clones(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x000111b0)
// WARNING: Removing unreachable block (ram,0x000111c8)
// WARNING: Removing unreachable block (ram,0x000111d0)

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
    if (ppuVar1[0x16] != (undefined *)0x0) {
      __deregister_frame_info(&__FRAME_END__);
    }
    completed_8508 = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x000112b8)
// WARNING: Removing unreachable block (ram,0x000112cc)

void frame_dummy(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&__FRAME_END__,object_8513,param_3,__register_frame_info,param_1,param_2);
  register_tm_clones();
  return;
}



undefined4 app_audio_switch_mid(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 5U < 0xc) {
    uVar1 = *(undefined4 *)(&CSWTCH_35 + (param_1 - 5U) * 4);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



int * app_audio_find_src_gchn(int *param_1)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (*param_1 - 5U < 0xc) {
    iVar3 = *(int *)(&CSWTCH_35 + (*param_1 - 5U) * 4);
  }
  else {
    iVar3 = -1;
  }
  puVar2 = &app_audio_chn_glock + iVar3 * 0x18;
  ak_thread_mutex_lock(puVar2);
  puVar1 = (undefined4 *)(&app_audio_chn_g)[iVar3 * 2];
  if (&app_audio_chn_g + iVar3 * 2 != puVar1) {
    do {
      if ((puVar1[-0xf] == *param_1) && (puVar1[-0xe] == param_1[1])) {
        ak_thread_mutex_unlock(puVar2);
        return puVar1 + -0xf;
      }
      puVar1 = (undefined4 *)*puVar1;
    } while (&app_audio_chn_g + iVar3 * 2 != puVar1);
  }
  ak_thread_mutex_unlock(puVar2);
  return (int *)0x0;
}



undefined4 app_audio_check_bind_chn_relation(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *param_1;
  iVar1 = *param_2;
  if (iVar2 == 0xf) {
    uVar3 = 0x1f000002;
    if (iVar1 == 0x10) {
      uVar3 = 0;
    }
    return uVar3;
  }
  if ((iVar2 != 0x10) && (iVar2 != 5)) {
    return 0x1f000000;
  }
  uVar3 = 0x1f000002;
  if (iVar1 == 0xf || iVar1 == 6) {
    uVar3 = 0;
  }
  return uVar3;
}



undefined4 app_audio_check_src_range(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((*param_1 - 5U < 0xc) && (*(uint *)(&CSWTCH_35 + (*param_1 - 5U) * 4) < 4)) {
    piVar1 = app_audio_find_src_gchn(param_1);
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    uVar2 = 0x1f000006;
    if (piVar1[4] < piVar1[3]) {
      uVar2 = 0;
    }
    return uVar2;
  }
  return 0x1f000000;
}



int * app_audio_find_dst_chn(int param_1,int *param_2)

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



int * app_audio_find_dst_chn_by_src_dst(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  
  if (0xb < *param_1 - 5U) {
    return (int *)0x0;
  }
  uVar3 = *(uint *)(&CSWTCH_35 + (*param_1 - 5U) * 4);
  if (uVar3 < 4) {
    puVar5 = &app_audio_chn_glock + uVar3 * 0x18;
    ak_thread_mutex_lock(puVar5);
    for (puVar2 = (undefined4 *)(&app_audio_chn_g)[uVar3 * 2];
        &app_audio_chn_g + uVar3 * 2 != puVar2; puVar2 = (undefined4 *)*puVar2) {
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



int * app_audio_find_dst_chn_all(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int local_38 [5];
  
  memset(local_38,0,0x10);
  if (*param_1 - 5U < 0xc) {
    switch(*(undefined4 *)(&CSWTCH_35 + (*param_1 - 5U) * 4)) {
    case 0:
      local_38[3] = 1;
      local_38[1] = 1;
      break;
    case 1:
      local_38[0] = 1;
      local_38[2] = 1;
      break;
    case 2:
      local_38[1] = 1;
      local_38[3] = 1;
      break;
    case 3:
      local_38[0] = 1;
      local_38[2] = 1;
      break;
    default:
      goto switchD_000116ac_default;
    }
    puVar4 = &app_audio_chn_glock;
    iVar3 = 0;
    iVar1 = local_38[0];
    while( true ) {
      if (iVar1 != 0) {
        ak_thread_mutex_lock(puVar4);
        puVar6 = (undefined4 *)(&app_audio_chn_g)[iVar3 * 2];
        if (puVar6 != &app_audio_chn_g + iVar3 * 2) {
          for (; &app_audio_chn_g + iVar3 * 2 != puVar6; puVar6 = (undefined4 *)*puVar6) {
            puVar5 = puVar6 + -10;
            ak_thread_mutex_lock(puVar5);
            puVar2 = (undefined4 *)puVar6[2];
            if (puVar6 + 2 != puVar2) {
              do {
                if ((*param_1 == puVar2[-0x13]) && (puVar2[-0x12] == param_1[1])) {
                  ak_thread_mutex_unlock(puVar5);
                  ak_thread_mutex_unlock(puVar4);
                  return puVar2 + -0x13;
                }
                puVar2 = (undefined4 *)*puVar2;
              } while (puVar6 + 2 != puVar2);
            }
            ak_thread_mutex_unlock(puVar5);
          }
        }
        ak_thread_mutex_unlock(puVar4);
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0x18;
      if (iVar3 == 4) break;
      iVar1 = local_38[iVar3];
    }
  }
switchD_000116ac_default:
  return (int *)0x0;
}



undefined4 app_audio_free_obj(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    ak_print(0x1f,1,"[%s:%d] the gobj is NULL!\n","app_audio_free_obj",0x17c);
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



void * app_audio_gen_obj(void *param_1,void *param_2,size_t param_3)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x1f,0x58,"app_audio_gen_obj",uVar1);
  if (__s == (void *)0x0) {
    ak_print(0x1f,1,"[%s:%d] Mem alloc for obj failed!\n","app_audio_gen_obj",0x198);
  }
  else {
    memset(__s,0,0x58);
    uVar1 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0x1f,param_3,"app_audio_gen_obj",uVar1);
    *(int *)((int)__s + 0x2c) = iVar2;
    if (iVar2 == 0) {
      ak_print(0x1f,1,"[%s:%d] Mem alloc for obj->param failed!\n","app_audio_gen_obj",0x1a2);
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



undefined4 app_audio_free_gobj(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    ak_print(0x1f,1,"[%s:%d] the gobj is NULL!\n","app_audio_free_gobj",0x1c0);
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



void * app_audio_gen_gobj(void *param_1,void *param_2,size_t param_3)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0x1f,0x4c,"app_audio_gen_gobj",uVar1);
  if (__s == (void *)0x0) {
    ak_print(0x1f,1,"[%s:%d] Mem alloc for gobj failed!\n","app_audio_gen_gobj",0x1de);
  }
  else {
    memset(__s,0,0x4c);
    uVar1 = ak_get_os_timestamp();
    iVar2 = ak_mem_alloc_(0x1f,param_3,"app_audio_gen_gobj",uVar1);
    *(int *)((int)__s + 0x38) = iVar2;
    if (iVar2 == 0) {
      ak_print(0x1f,1,"[%s:%d] Mem alloc for gobj->sparam failed!\n","app_audio_gen_gobj",0x1e8);
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



int app_audio_ai_stream_do_aenc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  void *__s;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  
  uVar4 = *(undefined4 *)(param_2 + 4);
  uVar1 = ak_get_os_timestamp();
  __s = (void *)ak_mem_alloc_(0xf,0x20,"app_audio_ai_stream_do_aenc",uVar1);
  if (__s == (void *)0x0) {
    ak_print(0x1f,1,"[%s:%d] Alloc stream buffer failed!\n","app_audio_ai_stream_do_aenc",0x20e);
    return 0x102;
  }
  memset(__s,0,0x20);
  iVar2 = ak_aenc_send_frame(uVar4,param_1,0);
  if (iVar2 == 0) {
    ak_thread_mutex_lock(param_2 + 0x10);
    piVar3 = *(int **)(param_2 + 0x48);
    *(int *)(param_2 + 0x30) = *(int *)(param_2 + 0x30) + 1;
    *(int *)(param_2 + 0x40) = *(int *)(param_2 + 0x40) + 1;
    *(int *)(param_2 + 0x48) = (int)__s + 0x18;
    *(int **)((int)__s + 0x1c) = piVar3;
    *(int *)((int)__s + 0x18) = param_2 + 0x44;
    *piVar3 = (int)__s + 0x18;
    ak_thread_mutex_unlock(param_2 + 0x10);
    return 0;
  }
  ak_print(0xfe,1,"[%s:%d] send frame error\n","app_audio_ai_stream_do_aenc",0x217);
  return iVar2;
}



int app_audio_ai_stream_behavior
              (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
    *(undefined4 *)(param_2 + 0x30) = 0;
    *(undefined4 *)(param_2 + 0x34) = 0;
  }
  iVar4 = param_2 + 0x44;
  if (iVar4 == *(int *)(param_2 + 0x44)) {
    iVar5 = 0;
  }
  else {
    piVar3 = (int *)(*(int *)(param_2 + 0x44) + -0x4c);
    iVar5 = 0;
    do {
      while (((piVar3[10] == 1 && (*piVar3 - 5U < 0xc)) &&
             (*(int *)(&CSWTCH_35 + (*piVar3 - 5U) * 4) == 1))) {
        iVar5 = app_audio_ai_stream_do_aenc(param_1,(int)piVar3);
        piVar1 = piVar3 + 0x13;
        piVar3 = (int *)(*piVar1 + -0x4c);
        if (iVar4 == *piVar1) goto LAB_00011e38;
      }
      piVar1 = piVar3 + 0x13;
      piVar3 = (int *)(*piVar1 + -0x4c);
    } while (iVar4 != *piVar1);
  }
LAB_00011e38:
  ak_thread_mutex_unlock(param_2 + 0x14);
  return iVar5;
}



undefined4 app_audio_ai_stream_th(int param_1)

{
  int iVar1;
  undefined4 extraout_r2;
  int param3;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  char local_40 [36];
  
  param3 = *(int *)(param_1 + 4);
  local_40[0] = '\0';
  local_40[1] = '\0';
  local_40[2] = '\0';
  local_40[3] = '\0';
  local_40[4] = '\0';
  local_40[5] = '\0';
  local_40[6] = '\0';
  local_40[7] = '\0';
  local_40[8] = '\0';
  local_40[9] = '\0';
  local_40[10] = '\0';
  local_40[0xb] = '\0';
  local_40[0xc] = '\0';
  local_40[0xd] = '\0';
  local_40[0xe] = '\0';
  local_40[0xf] = '\0';
  local_40[0x10] = '\0';
  local_40[0x11] = '\0';
  local_40[0x12] = '\0';
  local_40[0x13] = '\0';
  local_40[0x14] = '\0';
  local_40[0x15] = '\0';
  local_40[0x16] = '\0';
  local_40[0x17] = '\0';
  local_40[0x18] = '\0';
  local_40[0x19] = '\0';
  local_40[0x1a] = '\0';
  local_40[0x1b] = '\0';
  local_40[0x1c] = '\0';
  local_40[0x1d] = '\0';
  local_40[0x1e] = '\0';
  local_40[0x1f] = '\0';
  snprintf(local_40,0x20,"ai_stream_%d",param3);
  ak_thread_set_name(local_40);
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  while( true ) {
    if (*(int *)(param_1 + 8) == 0) break;
    memset(&local_58,0,0x18);
    iVar1 = ak_ai_get_frame(param3,&local_58,0);
    if (iVar1 == 0) {
      error_count_7519 = 0;
      app_audio_ai_stream_behavior(&local_58,param_1,extraout_r2,0);
      ak_ai_release_frame(param3,&local_58);
    }
    else if (0x32 < error_count_7519) {
      ak_print(0x1f,4,"[%s:%d] get frame failed!\n","app_audio_ai_stream_th",0x27d);
      error_count_7519 = 0;
    }
  }
  return 0;
}



undefined4 app_audio_unbind_ai_aenc(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  
  piVar3 = app_audio_find_src_gchn(param_1);
  if (piVar3 == (int *)0x0) {
    ak_print(0x1f,1,"[%s:%d] the Src Chn is not binded!\n","app_audio_unbind_ai_aenc",0x293);
    return 0x1f000005;
  }
  piVar4 = app_audio_find_dst_chn((int)piVar3,param_2);
  if (piVar4 == (int *)0x0) {
    ak_print(0x1f,1,"[%s:%d] the Dest Chn is not binded!\n","app_audio_unbind_ai_aenc",0x29c);
    return 0x1f000004;
  }
  ak_thread_mutex_lock(piVar3 + 5);
  iVar8 = piVar3[4];
  iVar6 = piVar4[0x13];
  piVar7 = (int *)piVar4[0x14];
  *(int **)(iVar6 + 4) = piVar7;
  *piVar7 = iVar6;
  piVar4[0x13] = 0x100100;
  piVar4[0x14] = 0x200200;
  piVar3[4] = iVar8 + -1;
  ak_thread_mutex_unlock(piVar3 + 5);
  ak_thread_mutex_lock(piVar4 + 4);
  piVar10 = piVar4 + 0x11;
  piVar7 = (int *)*piVar10;
  if (piVar10 != piVar7) {
    piVar9 = (int *)*piVar7;
    piVar2 = (int *)*piVar7;
    do {
      piVar1 = piVar2;
      iVar6 = piVar4[0x10];
      puVar5 = (undefined4 *)piVar7[1];
      piVar9[1] = (int)puVar5;
      *puVar5 = piVar9;
      *piVar7 = 0x100100;
      piVar7[1] = 0x200200;
      piVar4[0x10] = iVar6 + -1;
      ak_mem_free(piVar7 + -6);
      piVar9 = (int *)*piVar1;
      piVar2 = piVar9;
      piVar7 = piVar1;
    } while (piVar1 != piVar10);
  }
  ak_thread_mutex_unlock(piVar4 + 4);
  app_audio_free_obj((int)piVar4);
  if (piVar3[4] == 0) {
    piVar3[2] = 0;
    ak_thread_join(piVar3[0xb]);
    if (*piVar3 - 5U < 0xc) {
      iVar6 = *(int *)(&CSWTCH_35 + (*piVar3 - 5U) * 4);
    }
    else {
      iVar6 = -1;
    }
    ak_thread_mutex_lock(&app_audio_chn_glock + iVar6 * 0x18);
    piVar4 = (int *)piVar3[0x10];
    iVar8 = piVar3[0xf];
    *(int **)(iVar8 + 4) = piVar4;
    *piVar4 = iVar8;
    piVar3[0xf] = 0x100100;
    piVar3[0x10] = 0x200200;
    ak_thread_mutex_unlock(&app_audio_chn_glock + iVar6 * 0x18);
    app_audio_free_gobj((int)piVar3);
    return 0;
  }
  return 0;
}



undefined4 app_audio_bind_ai_aenc(int *param_1,void *param_2,void *param_3)

{
  void *pvVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 local_1c;
  
  local_1c = 1;
  pvVar1 = app_audio_gen_obj(param_2,&local_1c,0x10);
  if (pvVar1 == (void *)0x0) {
    ak_print(0x1f,1,"[%s:%d] Generate dst obj failed!\n","app_audio_bind_ai_aenc",0x2e2);
    return 0x1f000009;
  }
  memcpy((void *)((int)pvVar1 + 8),param_3,8);
  piVar2 = app_audio_find_src_gchn(param_1);
  if (piVar2 == (int *)0x0) {
    piVar2 = app_audio_gen_gobj(param_1,&local_1c,4);
    if (piVar2 == (int *)0x0) {
      ak_print(0x1f,1,"[%s:%d] Generate group obj failed!\n","app_audio_bind_ai_aenc",0x2f1);
      app_audio_free_obj((int)pvVar1);
      return 0x1f000008;
    }
    piVar2[3] = 8;
    ak_thread_mutex_lock(&app_audio_chn_glock);
    piVar2[0xf] = (int)&app_audio_chn_g;
    piVar2[0x10] = (int)DAT_00024074;
    piVar3 = piVar2 + 0xf;
    *DAT_00024074 = (int)(piVar2 + 0xf);
    DAT_00024074 = piVar3;
    ak_thread_mutex_unlock(&app_audio_chn_glock);
  }
  ak_thread_mutex_lock(piVar2 + 5);
  iVar4 = piVar2[4];
  iVar5 = piVar2[2];
  piVar3 = (int *)piVar2[0x12];
  piVar2[0x12] = (int)pvVar1 + 0x4c;
  *(int **)((int)pvVar1 + 0x50) = piVar3;
  *(int **)((int)pvVar1 + 0x4c) = piVar2 + 0x11;
  *piVar3 = (int)pvVar1 + 0x4c;
  piVar2[4] = iVar4 + 1;
  if (iVar5 == 0) {
    piVar2[2] = 1;
    ak_thread_create(piVar2 + 0xb,app_audio_ai_stream_th,piVar2,0x19000,0xb);
  }
  ak_thread_mutex_unlock(piVar2 + 5);
  return 0;
}



undefined4 app_audio_unbind_chn(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int *piVar12;
  
  if (0xb < *param_1 - 5U) {
    return 0x1f000000;
  }
  uVar11 = *(uint *)(&CSWTCH_35 + (*param_1 - 5U) * 4);
  if (0xb < *param_2 - 5U) {
    if (uVar11 < 3) {
      uVar6 = 0;
    }
    else {
      uVar6 = 0x1f000000;
    }
    return uVar6;
  }
  if (uVar11 == 0) {
    if (*(int *)(&CSWTCH_35 + (*param_2 - 5U) * 4) == 1) {
      piVar3 = app_audio_find_src_gchn(param_1);
      if (piVar3 == (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] the Src Chn is not binded!\n","app_audio_unbind_ai_aenc",0x293);
        return 0x1f000005;
      }
      piVar4 = app_audio_find_dst_chn((int)piVar3,param_2);
      if (piVar4 != (int *)0x0) {
        ak_thread_mutex_lock(piVar3 + 5);
        iVar9 = piVar3[4];
        iVar7 = piVar4[0x13];
        piVar8 = (int *)piVar4[0x14];
        *(int **)(iVar7 + 4) = piVar8;
        *piVar8 = iVar7;
        piVar4[0x13] = 0x100100;
        piVar4[0x14] = 0x200200;
        piVar3[4] = iVar9 + -1;
        ak_thread_mutex_unlock(piVar3 + 5);
        ak_thread_mutex_lock(piVar4 + 4);
        piVar12 = piVar4 + 0x11;
        piVar8 = (int *)*piVar12;
        if (piVar12 != piVar8) {
          piVar10 = (int *)*piVar8;
          piVar2 = (int *)*piVar8;
          do {
            piVar1 = piVar2;
            iVar7 = piVar4[0x10];
            puVar5 = (undefined4 *)piVar8[1];
            piVar10[1] = (int)puVar5;
            *puVar5 = piVar10;
            *piVar8 = 0x100100;
            piVar8[1] = 0x200200;
            piVar4[0x10] = iVar7 + -1;
            ak_mem_free(piVar8 + -6);
            piVar10 = (int *)*piVar1;
            piVar2 = piVar10;
            piVar8 = piVar1;
          } while (piVar1 != piVar12);
        }
        ak_thread_mutex_unlock(piVar4 + 4);
        app_audio_free_obj((int)piVar4);
        if (piVar3[4] != 0) {
          return 0;
        }
        piVar3[2] = 0;
        ak_thread_join(piVar3[0xb]);
        if (*piVar3 - 5U < 0xc) {
          iVar7 = *(int *)(&CSWTCH_35 + (*piVar3 - 5U) * 4);
        }
        else {
          iVar7 = -1;
        }
        ak_thread_mutex_lock(&app_audio_chn_glock + iVar7 * 0x18);
        piVar4 = (int *)piVar3[0x10];
        iVar9 = piVar3[0xf];
        *(int **)(iVar9 + 4) = piVar4;
        *piVar4 = iVar9;
        piVar3[0xf] = 0x100100;
        piVar3[0x10] = 0x200200;
        ak_thread_mutex_unlock(&app_audio_chn_glock + iVar7 * 0x18);
        app_audio_free_gobj((int)piVar3);
        return 0;
      }
      ak_print(0x1f,1,"[%s:%d] the Dest Chn is not binded!\n","app_audio_unbind_ai_aenc",0x29c);
      return 0x1f000004;
    }
  }
  else {
    if ((int)uVar11 < 0) {
      return 0x1f000000;
    }
    if (2 < (int)uVar11) {
      return 0x1f000000;
    }
  }
  return 0;
}



undefined4 app_audio_bind_chn(int *param_1,int *param_2,void *param_3)

{
  void *pvVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 uStack_1c;
  
  if (0xb < *param_1 - 5U) {
    return 0x1f000000;
  }
  uVar6 = *(uint *)(&CSWTCH_35 + (*param_1 - 5U) * 4);
  if (0xb < *param_2 - 5U) {
    if (uVar6 < 3) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0x1f000000;
    }
    return uVar3;
  }
  if (uVar6 != 0) {
    if ((-1 < (int)uVar6) && ((int)uVar6 < 3)) {
      return 0;
    }
    return 0x1f000000;
  }
  if (*(int *)(&CSWTCH_35 + (*param_2 - 5U) * 4) != 1) {
    return 0;
  }
  uStack_1c = 1;
  pvVar1 = app_audio_gen_obj(param_2,&uStack_1c,0x10);
  if (pvVar1 != (void *)0x0) {
    memcpy((void *)((int)pvVar1 + 8),param_3,8);
    piVar2 = app_audio_find_src_gchn(param_1);
    if (piVar2 == (int *)0x0) {
      piVar2 = app_audio_gen_gobj(param_1,&uStack_1c,4);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] Generate group obj failed!\n","app_audio_bind_ai_aenc",0x2f1);
        app_audio_free_obj((int)pvVar1);
        return 0x1f000008;
      }
      piVar2[3] = 8;
      ak_thread_mutex_lock(&app_audio_chn_glock);
      piVar2[0xf] = (int)&app_audio_chn_g;
      piVar2[0x10] = (int)DAT_00024074;
      piVar4 = piVar2 + 0xf;
      *DAT_00024074 = (int)(piVar2 + 0xf);
      DAT_00024074 = piVar4;
      ak_thread_mutex_unlock(&app_audio_chn_glock);
    }
    ak_thread_mutex_lock(piVar2 + 5);
    iVar5 = piVar2[4];
    iVar7 = piVar2[2];
    piVar4 = (int *)piVar2[0x12];
    piVar2[0x12] = (int)pvVar1 + 0x4c;
    *(int **)((int)pvVar1 + 0x50) = piVar4;
    *(int **)((int)pvVar1 + 0x4c) = piVar2 + 0x11;
    *piVar4 = (int)pvVar1 + 0x4c;
    piVar2[4] = iVar5 + 1;
    if (iVar7 == 0) {
      piVar2[2] = 1;
      ak_thread_create(piVar2 + 0xb,app_audio_ai_stream_th,piVar2,0x19000,0xb);
    }
    ak_thread_mutex_unlock(piVar2 + 5);
    return 0;
  }
  ak_print(0x1f,1,"[%s:%d] Generate dst obj failed!\n","app_audio_bind_ai_aenc",0x2e2);
  return 0x1f000009;
}



undefined4 ak_app_audio_set_dst_chn_active(int *param_1,uint param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_1 != (int *)0x0) {
    if (param_2 < 2) {
      piVar2 = app_audio_find_dst_chn_all(param_1);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_audio_set_dst_chn_active",
                 0x38e);
        uVar1 = 0x1f000004;
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
      ak_print(0x1f,1,"[%s:%d] The enable status  is invalid!\n","ak_app_audio_set_dst_chn_active",
               0x385);
      uVar1 = 0x101;
    }
    return uVar1;
  }
  ak_print(0x1f,1,"[%s:%d] The input param is NULL!\n","ak_app_audio_set_dst_chn_active",0x37f);
  return 0x101;
}



undefined4 ak_app_audio_aenc_get_stream(int *param_1,void *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  if (param_2 != (void *)0x0 && param_1 != (int *)0x0) {
    if ((*param_1 == 0xf) && (-1 < param_1[1])) {
      piVar2 = app_audio_find_dst_chn_all(param_1);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_audio_aenc_get_stream",0x3b6
                );
        uVar1 = 0x1f000004;
      }
      else if (piVar2 + 0x11 == (int *)piVar2[0x11]) {
        ak_thread_mutex_unlock(piVar2 + 4);
        uVar1 = 0x1f00000a;
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
      ak_print(0x1f,1,"[%s:%d] The Chn param is invalid!\n","ak_app_audio_aenc_get_stream",0x3ad);
      uVar1 = 0x101;
    }
    return uVar1;
  }
  ak_print(0x1f,1,"[%s:%d] The input param is NULL!\n","ak_app_audio_aenc_get_stream",0x3a7);
  return 0x101;
}



int ak_app_audio_unbind_chn(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 == (int *)0x0 || param_1 == (int *)0x0) {
    ak_print(0x1f,1,"[%s:%d] The Input param is invalid!\n","ak_app_audio_unbind_chn",0x3de);
    return 0x101;
  }
  iVar1 = app_audio_check_bind_chn_relation(param_1,param_2);
  if (iVar1 == 0) {
    piVar2 = app_audio_find_src_gchn(param_1);
    if (piVar2 == (int *)0x0) {
      ak_print(0x1f,1,"[%s:%d] the Src Chn is not binded!\n","ak_app_audio_unbind_chn",0x3ee);
      iVar1 = 0x1f000005;
    }
    else {
      piVar2 = app_audio_find_dst_chn((int)piVar2,param_2);
      if (piVar2 == (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] the Dest Chn is not binded!\n","ak_app_audio_unbind_chn",0x3f7);
        iVar1 = 0x1f000004;
      }
      else {
        iVar1 = app_audio_unbind_chn(param_1,param_2);
        if (iVar1 != 0) {
          ak_print(0x1f,1,"[%s:%d] Chn unbind Error:[%x]!\n","ak_app_audio_unbind_chn",0x400,iVar1);
        }
      }
    }
  }
  else {
    ak_print(0x1f,1,"[%s:%d] the relation ship between Chns is incorrect!\n",
             "ak_app_audio_unbind_chn",0x3e6);
  }
  return iVar1;
}



int ak_app_audio_bind_chn(int *param_1,int *param_2,void *param_3)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 == (int *)0x0 || (param_3 == (void *)0x0 || param_2 == (int *)0x0)) {
    ak_print(0x1f,1,"[%s:%d] The Input param is invalid!\n","ak_app_audio_bind_chn",0x413);
    iVar1 = 0x101;
  }
  else {
    iVar1 = app_audio_check_bind_chn_relation(param_1,param_2);
    if (iVar1 != 0) {
      ak_print(0x1f,1,"[%s:%d] the relation ship between Chns is incorrect!\n",
               "ak_app_audio_bind_chn",0x41b);
      return iVar1;
    }
    iVar1 = app_audio_check_src_range(param_1);
    if (iVar1 == 0) {
      piVar2 = app_audio_find_dst_chn_all(param_2);
      if (piVar2 != (int *)0x0) {
        ak_print(0x1f,1,"[%s:%d] the Dest Chn is already binded!\n","ak_app_audio_bind_chn",0x42c);
        return 0x1f000003;
      }
      iVar1 = app_audio_bind_chn(param_1,param_2,param_3);
      if (iVar1 != 0) {
        ak_print(0x1f,1,"[%s:%d] Chn bind Error:[%x]!\n","ak_app_audio_bind_chn",0x434,iVar1);
      }
    }
    else {
      ak_print(0x1f,1,"[%s:%d] the src chn is reach to the max bind range!\n",
               "ak_app_audio_bind_chn",0x423);
    }
  }
  return iVar1;
}



undefined4 ak_app_audio_set_chn_attr(int *param_1,void *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_2 == (void *)0x0 || param_1 == (int *)0x0) {
    ak_print(0x1f,1,"[%s:%d] The Input param is invalid!\n","ak_app_audio_set_chn_attr",0x440);
    uVar1 = 0x101;
  }
  else {
    piVar2 = app_audio_find_dst_chn_all(param_1);
    if (piVar2 != (int *)0x0) {
      memcpy(piVar2 + 2,param_2,8);
      return 0;
    }
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



undefined4 ak_app_audio_set_cb(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  
  piVar1 = app_audio_find_src_gchn(param_1);
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



undefined4 ak_app_audio_unset_cb(int *param_1)

{
  int *piVar1;
  
  piVar1 = app_audio_find_src_gchn(param_1);
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



void _fini(void)

{
  return;
}


