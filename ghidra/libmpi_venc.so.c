typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef ulong size_t;

typedef long __fd_mask;

typedef struct fd_set fd_set, *Pfd_set;

struct fd_set {
    __fd_mask fds_bits[32];
};

typedef int __ssize_t;

typedef __ssize_t ssize_t;

typedef long __time_t;

typedef long __suseconds_t;

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

typedef void *__gnuc_va_list;

typedef struct timeval timeval, *Ptimeval;

struct timeval {
    __time_t tv_sec;
    __suseconds_t tv_usec;
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
undefined4 DAT_0002903c;
dword DWORD_00018494;
pointer __DT_PLTGOT;
undefined __register_frame_info;
undefined DAT_0002907c;
int DAT_00029074;
uint DAT_00029040;
undefined ak_thread_join;
undefined4 DAT_00029070;
int DAT_00029040;
undefined4 DAT_00029094;
int DAT_00029098;
int DAT_0002909c;
undefined FUN_00012808;
undefined ak_cb_thread_delete;
undefined ak_cb_mutex_unlock;
undefined ak_cb_mutex_lock;
undefined ak_cb_sem_wait;
undefined ak_cb_sem_destroy;
undefined ak_cb_irq_wait;
undefined ak_cb_atomic_increment;
undefined ak_cb_sem_post;
undefined ak_cb_dma_free;
undefined ak_cb_release_frame_buf;
undefined ak_mem_free;
undefined FUN_000127d0;
undefined ak_cb_thread_join;
undefined ak_cb_sem_init;
undefined4 DAT_00029048;
undefined4 DAT_00029044;
undefined ak_cb_atomic_decrement;
int DAT_0002906c;
undefined ak_cb_module_reset;
undefined ak_cb_mutex_destroy;
int DAT_00029094;
undefined ak_cb_thread_create;
undefined4 DAT_0002909c;
undefined4 DAT_00029098;
undefined LAB_00012794;
undefined LAB_000127b0;
undefined DAT_000127cc;
undefined LAB_00012944;
undefined ak_cb_module_clock;
undefined LAB_00012978;
undefined LAB_00012994;
undefined ak_cb_mutex_init;
undefined4 DAT_0002904c;
uint DAT_0002906c;

int _init(EVP_PKEY_CTX *ctx)

{
  return (int)ctx;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



void venc_info(ushort *param_1,undefined4 param_2)

{
  venc_info(param_1,param_2);
  return;
}



void __deregister_frame_info(void)

{
  __deregister_frame_info();
  return;
}



undefined4 ak_venc_get_attr(uint param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = ak_venc_get_attr(param_1,param_2);
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



// WARNING: Removing unreachable block (ram,0x000125ec)
// WARNING: Removing unreachable block (ram,0x00012604)
// WARNING: Removing unreachable block (ram,0x0001260c)

void processEntry entry(void)

{
  return;
}



void _FINI_0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &__DT_PLTGOT;
  if (__bss_start__ == '\0') {
    __cxa_finalize(DAT_0002903c);
    entry();
    if (ppuVar1[10] != (undefined *)0x0) {
      __deregister_frame_info(&DWORD_00018494);
    }
    __bss_start__ = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00012650)
// WARNING: Removing unreachable block (ram,0x00012668)
// WARNING: Removing unreachable block (ram,0x00012670)
// WARNING: Removing unreachable block (ram,0x00012758)
// WARNING: Removing unreachable block (ram,0x0001276c)

void _INIT_0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  __register_frame_info(&DWORD_00018494,&DAT_0002907c,param_3,__register_frame_info,param_1,param_2)
  ;
  return;
}



void FUN_000127d0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = ak_get_os_timestamp();
  ak_mem_alloc_(0xd,param_1,"venc_cb_alloc",uVar1);
  return;
}



void FUN_00012808(void)

{
  int iVar1;
  __suseconds_t *p_Var2;
  undefined4 local_ac;
  timeval local_a8;
  fd_set local_a0;
  
  ak_thread_set_name("mpp_venc_irq");
  while (DAT_00029074 != 0) {
    p_Var2 = &local_a8.tv_usec;
    do {
      p_Var2 = p_Var2 + 1;
      *p_Var2 = 0;
    } while (p_Var2 != local_a0.fds_bits + 0x1f);
    local_a0.fds_bits[DAT_00029040 >> 5] =
         local_a0.fds_bits[DAT_00029040 >> 5] | 1 << (DAT_00029040 & 0x1f);
    local_a8.tv_usec = 0;
    local_a8.tv_sec = 1;
    iVar1 = select(DAT_00029040 + 1,&local_a0,(fd_set *)0x0,(fd_set *)0x0,&local_a8);
    if (iVar1 == -1) {
      ak_print(0xd,1,"[%s:%d] select error","venc_wait_irq_handler_th",0xa5);
    }
    else if ((0 < iVar1) &&
            ((local_a0.fds_bits[DAT_00029040 >> 5] >> (DAT_00029040 & 0x1f) & 1U) != 0)) {
      local_ac = 0;
      read(DAT_00029040,&local_ac,4);
      AKV_Encoder_Interrupt_Handler();
    }
  }
  return;
}



undefined4 FUN_00012a14(ushort *param_1,undefined4 *param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  int extraout_r1;
  uint uVar14;
  uint uVar15;
  undefined4 uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  undefined2 local_38;
  
  uVar15 = *(uint *)(param_1 + 0x12);
  if (2 < uVar15) {
    ak_print(0xd,1,"[%s:%d] enc_out_type error %d\n","venc_check_and_format_param",0x1ff,uVar15);
    return 0xd000003;
  }
  uVar17 = *(uint *)(param_1 + 6);
  if (uVar15 == 0) {
    if (3 < uVar17) {
      ak_print(0xd,1,"[%s:%d] profile error, not h264 profile\n","venc_check_and_format_param",0x209
              );
      return 0xd000003;
    }
  }
  else if (uVar15 == 2) {
    if (2 < uVar17 - 4) {
      ak_print(0xd,1,"[%s:%d] profile error, not h265 profile\n","venc_check_and_format_param",0x213
              );
      return 0xd000003;
    }
  }
  else if (uVar17 != 7) {
    ak_print(0xd,1,"[%s:%d] profile error, not jpeg profile\n","venc_check_and_format_param",0x21c);
    return 0xd000003;
  }
  uVar18 = *(uint *)(param_1 + 8);
  if (3 < uVar18) {
    ak_print(0xd,1,"[%s:%d] br_mode error\n","venc_check_and_format_param",0x225);
    return 0xd000003;
  }
  uVar19 = *(uint *)(param_1 + 0x10);
  if (2 < uVar19) {
    ak_print(0xd,1,"[%s:%d] chroma_mode error\n","venc_check_and_format_param",0x22d);
    return 0xd000003;
  }
  uVar1 = *param_1;
  uVar20 = (uint)uVar1;
  if (uVar15 == 1) {
    uVar14 = 0x10;
    uVar21 = 8000;
  }
  else {
    uVar14 = 8;
    uVar21 = 0xa20;
  }
  if (uVar21 < uVar20 || uVar20 < uVar14) {
    ak_print(0xd,1,"[%s:%d] width error, must in [%d, %d].\n","venc_check_and_format_param",0x243,
             uVar14,uVar21);
    return 0xd000003;
  }
  FUN_00016ddc(uVar20,uVar14);
  if (extraout_r1 != 0) {
    ak_print(0xd,1,"[%s:%d] width error, must be divided by %d.\n","venc_check_and_format_param",
             0x24a,uVar14);
    return 0xd000003;
  }
  uVar2 = param_1[1];
  if (uVar21 < uVar2 || uVar2 < 8) {
    ak_print(0xd,1,"[%s:%d] height error, must in [%d, %d].\n","venc_check_and_format_param",0x251,8
             ,uVar21);
    return 0xd000003;
  }
  if ((uVar2 & 7) != 0) {
    ak_print(0xd,1,"[%s:%d] height error, must be divided by 8.\n","venc_check_and_format_param",600
            );
    return 0xd000003;
  }
  uVar3 = param_1[3];
  if (999 < (ushort)(uVar3 - 1)) {
    ak_print(0xd,1,"[%s:%d] goplen error, can\'t be 0 or larger than %d. cur gop: %d\n",
             "venc_check_and_format_param",0x25f,1000,uVar3);
    return 0xd000003;
  }
  uVar4 = param_1[2];
  if (uVar4 == 0) {
    ak_print(0xd,1,"[%s:%d] fps error, can\'t be 0. cur gop: %d\n","venc_check_and_format_param",
             0x266,0);
    return 0xd000003;
  }
  uVar5 = param_1[10];
  if (100 < uVar5) {
    ak_print(0xd,1,"[%s:%d] initqp error, can\'t larger than %d.\n","venc_check_and_format_param",
             0x26d,100);
    return 0xd000003;
  }
  uVar6 = param_1[4];
  uVar7 = param_1[5];
  if ((uVar6 == 0) || (uVar7 < uVar6)) {
    ak_print(0xd,1,"[%s:%d] birate error, can\'t set that bitrate value: target %d max %d.\n",
             "venc_check_and_format_param",0x274,uVar6,uVar7);
    return 0xd000003;
  }
  uVar8 = param_1[0xb];
  if (uVar15 == 1) {
    if (uVar8 == 0) {
      ak_print(0xd,1,"[%s:%d] jpeg minqp error, can\'t smaller than 1.minqp %d\n",
               "venc_check_and_format_param",0x27c,0);
      return 0xd000003;
    }
    uVar13 = param_1[0xc];
    if (100 < uVar13) {
      ak_print(0xd,1,"[%s:%d] jpeg maxqp error, can\'t larger than %d. maxqp [%d]\n",
               "venc_check_and_format_param",0x283,100,uVar13);
      return 0xd000003;
    }
    if (uVar13 < uVar8) goto LAB_00012f0c;
  }
  else {
    uVar13 = param_1[0xc];
    if (uVar13 < uVar8) {
LAB_00012f0c:
      ak_print(0xd,1,"[%s:%d] qp range error, minqp [%d] maxqp [%d].\n",
               "venc_check_and_format_param",0x28a,uVar8,uVar13);
      return 0xd000003;
    }
    if ((uVar15 & 0xfffffffd) == 0) {
      uVar9 = uVar8;
      if (uVar8 < 0x34) {
        uVar9 = uVar13;
      }
      if (0x33 < uVar9) {
        ak_print(0xd,1,
                 "[%s:%d] h264/h265 qp range error, can\'t larger than %d.And minqp %d maxqp %d\n",
                 "venc_check_and_format_param",0x295,0x33,uVar8,uVar13);
        return 0xd000003;
      }
      if (uVar5 < uVar8 || uVar13 < uVar5) {
        ak_print(0xd,1,"[%s:%d] initpq error, should be in the range of minqp-maxqp [%d - %d].\n",
                 "venc_check_and_format_param",0x29c,uVar8,uVar13);
        return 0xd000003;
      }
    }
  }
  uVar20 = *(uint *)(param_1 + 0xe);
  if (uVar20 < 4) {
    uVar9 = param_1[0x16];
    if ((ushort)(uVar9 - 10) < 0x29) {
      uVar14 = *(uint *)(param_1 + 0x18);
      if (uVar14 < 4) {
        uVar10 = param_1[0x1a];
        if (uVar10 < 0x3e9) {
          uVar11 = param_1[0x1b];
          if (uVar11 < 0x65) {
            uVar12 = param_1[0x1c];
            if (uVar12 < 0x301) {
              if (uVar15 == 0) {
                switch(uVar17) {
                case 0:
                  *param_2 = 0x100004d;
                  break;
                case 1:
                  *param_2 = 0x1000064;
                  break;
                case 2:
                  *param_2 = 0x1000042;
                  break;
                case 3:
                  *param_2 = 0x1000242;
                }
              }
              else if (uVar15 == 2) {
                if (uVar17 == 5) {
                  *param_2 = 0x2000003;
                }
                else if (uVar17 == 6) {
                  *param_2 = 0x2fa0004;
                }
                else if (uVar17 == 4) {
                  *param_2 = 0x2000001;
                }
              }
              else {
                *param_2 = 0x4000000;
              }
              if (uVar18 == 1) {
                param_2[1] = 2;
              }
              else {
                if ((uVar18 != 0) && (uVar18 < 4)) {
                  param_2[1] = 3;
                  ak_print(0xd,1,"[%s:%d] br_mode error NOT support\n","venc_check_and_format_param"
                           ,0x307);
                  return 0xd000003;
                }
                param_2[1] = 1;
              }
              uVar16 = *(undefined4 *)(param_1 + 0x14);
              *(ushort *)((int)param_2 + 0xe) = uVar2;
              *(ushort *)(param_2 + 4) = uVar6;
              param_2[0xb] = uVar16;
              *(ushort *)(param_2 + 5) = uVar4;
              *(ushort *)(param_2 + 7) = uVar3;
              param_2[2] = uVar19;
              *(ushort *)((int)param_2 + 0x16) = uVar5;
              local_38 = (undefined2)uVar20;
              *(ushort *)(param_2 + 3) = uVar1;
              *(undefined2 *)(param_2 + 10) = local_38;
              *(ushort *)((int)param_2 + 0x12) = uVar7;
              *(ushort *)(param_2 + 0xc) = uVar9;
              *(ushort *)(param_2 + 6) = uVar8;
              *(ushort *)(param_2 + 9) = uVar10;
              *(ushort *)((int)param_2 + 0x1a) = uVar13;
              *(short *)((int)param_2 + 0x22) = (short)uVar14;
              *(ushort *)((int)param_2 + 0x26) = uVar11;
              *(ushort *)((int)param_2 + 0x2a) = uVar12;
              *(undefined2 *)((int)param_2 + 0x1e) = 0;
              *(undefined2 *)(param_2 + 8) = 1;
              uVar16 = 0;
            }
            else {
              ak_print(0xd,1,"[%s:%d] smart_static_value error, must in [%d, %d].\n",
                       "venc_check_and_format_param",0x2c7,0,0x300);
              uVar16 = 0xd000003;
            }
          }
          else {
            ak_print(0xd,1,"[%s:%d] smart_quality error, must in [%d, %d].\n",
                     "venc_check_and_format_param",0x2c0,0,100);
            uVar16 = 0xd000003;
          }
        }
        else {
          ak_print(0xd,1,"[%s:%d] smart_goplen error, can\'t larger than %d.\n",
                   "venc_check_and_format_param",0x2b9,1000);
          uVar16 = 0xd000003;
        }
      }
      else {
        ak_print(0xd,1,"[%s:%d] smart_mode error, can\'t larger than %d.\n",
                 "venc_check_and_format_param",0x2b2,3);
        uVar16 = 0xd000003;
      }
    }
    else {
      ak_print(0xd,1,"[%s:%d] enc_level error, must in [%d, %d].\n","venc_check_and_format_param",
               0x2ab,10,0x32);
      uVar16 = 0xd000003;
    }
  }
  else {
    ak_print(0xd,1,"[%s:%d] jpeg_qlevel error, can\'t larger than %d.\n",
             "venc_check_and_format_param",0x2a4,3);
    uVar16 = 0xd000003;
  }
  return uVar16;
}



undefined4 FUN_000132d4(void)

{
  ak_print(0xd,1,"[%s:%d] handle_id invalid \n","venc_get_user_handle",0x1f0);
  return 0;
}



undefined4 FUN_00013314(undefined4 param_1,undefined4 param_2)

{
  if (DAT_00029074 != 0) {
    DAT_00029074 = 0;
    ak_thread_join(DAT_00029070,param_2,0,ak_thread_join);
    if (0 < DAT_00029040) {
      close(DAT_00029040);
      DAT_00029040 = -1;
    }
    return 0;
  }
  ak_print(0xd,4,"[%s:%d] the wait irq thread is already destroyed!\n",
           "venc_destroy_wait_irq_thread",0xfe);
  return 0;
}



void FUN_000133ac(void)

{
  if (((DAT_00029094 != 0) && (DAT_00029098 == 0x20020000)) && (DAT_0002909c == 0x10000)) {
    ak_print(0xd,4,"[%s:%d] unmapping, start: 0x%08x, len: 0x%08x\n","venc_cb_exit_reg",0x151,
             0x20020000,0x10000);
    osal_drv_uio_unmap_regs(DAT_00029094,0x10000);
    ak_print(0xd,4,"[%s:%d] uninit venc reg, va: 0x%08x, pa: 0x%08x, len: 0x%08x\n",
             "venc_cb_exit_reg",0x15a,DAT_00029094,DAT_00029098,DAT_0002909c);
    memset(&DAT_00029094,0,0xc);
  }
  return;
}



void print_venc_param(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ak_print(0xfe,4,"eProfile:[%x]\n",*param_1,param_4);
  ak_print(0xfe,4,"eRCMode:[%x]\n",param_1[1]);
  ak_print(0xfe,4,"eChromaMode:[%x]\n",param_1[2]);
  ak_print(0xfe,4,"FrameWidth:[%u]\n",*(undefined2 *)(param_1 + 3));
  ak_print(0xfe,4,"FrameHeight:[%u]\n",*(undefined2 *)((int)param_1 + 0xe));
  ak_print(0xfe,4,"TargetBitRate:[%u]\n",*(undefined2 *)(param_1 + 4));
  ak_print(0xfe,4,"MaxBitRate[%u]\n",*(undefined2 *)((int)param_1 + 0x12));
  ak_print(0xfe,4,"EncFrameRate[%u]\n",*(undefined2 *)(param_1 + 5));
  ak_print(0xfe,4,"InitialSliceQP[%u]\n",*(undefined2 *)((int)param_1 + 0x16));
  ak_print(0xfe,4,"MinQP->[%u]\n",*(undefined2 *)(param_1 + 6));
  ak_print(0xfe,4,"MaxQP->[%u]\n",*(undefined2 *)((int)param_1 + 0x1a));
  ak_print(0xfe,4,"GopLength[%u]\n",*(undefined2 *)(param_1 + 7));
  ak_print(0xfe,4,"GopNumB[%d]\n",*(undefined2 *)((int)param_1 + 0x1e));
  ak_print(0xfe,4,"NumSlices[%u]\n",*(undefined2 *)(param_1 + 8));
  ak_print(0xfe,4,"SmartMode[%d]\n",*(undefined2 *)((int)param_1 + 0x22));
  ak_print(0xfe,4,"SmartGopLength[%u]\n",*(undefined2 *)(param_1 + 9));
  ak_print(0xfe,4,"SmartQuality[%u]\n",*(undefined2 *)((int)param_1 + 0x26));
  ak_print(0xfe,4,"QuantTableLevel[%u]\n",*(undefined2 *)(param_1 + 10));
  ak_print(0xfe,4,"SmartStaticValue[%u]\n",*(undefined2 *)((int)param_1 + 0x2a));
  ak_print(0xfe,4,"MaxPictureSize[%lu]\n",param_1[0xb]);
  ak_print(0xfe,4,"EncLevel[%u]\n",*(undefined2 *)(param_1 + 0xc));
  return;
}



char * ak_venc_get_version(void)

{
  return "libmpi_venc V1.0.29-debug1";
}



void ak_venc_get_enc_lib_version(void)

{
  AKV_Encoder_GetVersionInfo();
  return;
}



void venc_info(ushort *param_1,int param_2)

{
  int iVar1;
  char acStack_98 [128];
  
  memset(acStack_98,0,0x80);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d=opened",param_2);
  ak_debug_info(0xd,1,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc_id=%d",param_2);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_width=%d",param_2,(uint)*param_1);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_height=%d",param_2,(uint)param_1[1]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_fps=%d",param_2,(uint)param_1[2]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_goplen=%d",param_2,(uint)param_1[3]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_target_kbps=%d",param_2,(uint)param_1[4]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_max_kbps=%d",param_2,(uint)param_1[5]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  iVar1 = *(int *)(param_1 + 0x12);
  if (iVar1 == 1) {
    snprintf(acStack_98,0x80,"venc%d_enc_type=JPEG",param_2);
  }
  else if (iVar1 == 0) {
    snprintf(acStack_98,0x80,"venc%d_enc_type=AVC(H264)",param_2);
  }
  else if (iVar1 == 2) {
    snprintf(acStack_98,0x80,"venc%d_enc_type=HEVC(H265)",param_2);
  }
  else {
    snprintf(acStack_98,0x80,"venc%d_enc_type=UNKNOWN",param_2);
  }
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  switch(*(undefined4 *)(param_1 + 6)) {
  case 0:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_MAIN",param_2);
    break;
  case 1:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_HIGH",param_2);
    break;
  case 2:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_BASE",param_2);
    break;
  case 3:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_C_BASE",param_2);
    break;
  case 4:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_HEVC_MAIN",param_2);
    break;
  case 5:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_HEVC_MAIN_STILL",param_2);
    break;
  case 6:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_HEVC_MAIN_INTRA",param_2);
    break;
  case 7:
    snprintf(acStack_98,0x80,"venc%d_profile=PROFILE_JPEG",param_2);
    break;
  default:
    snprintf(acStack_98,0x80,"venc%d_profile=UNKNOWN",param_2);
  }
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  switch(*(undefined4 *)(param_1 + 8)) {
  case 0:
    snprintf(acStack_98,0x80,"venc%d_br_mode=CBR",param_2);
    break;
  case 1:
    snprintf(acStack_98,0x80,"venc%d_br_mode=VBR",param_2);
    break;
  case 2:
    snprintf(acStack_98,0x80,"venc%d_br_mode=CONST_QP",param_2);
    break;
  case 3:
    snprintf(acStack_98,0x80,"venc%d_br_mode=LOW_LATENCY",param_2);
    break;
  default:
    snprintf(acStack_98,0x80,"venc%d_br_mode=UNKNOWN",param_2);
  }
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_initqp=%d",param_2,(uint)param_1[10]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_minqp=%d",param_2,(uint)param_1[0xb]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_maxqp=%d",param_2,(uint)param_1[0xc]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_jpeg_qlevel=%d",param_2,*(int *)(param_1 + 0xe));
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_chroma_mode=%d",param_2,*(int *)(param_1 + 0x10));
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_max_picture_size=%d",param_2,*(int *)(param_1 + 0x14));
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_enc_level=%d",param_2,(uint)param_1[0x16]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  switch(*(undefined4 *)(param_1 + 0x18)) {
  case 0:
    snprintf(acStack_98,0x80,"venc%d_smart_mode=SMART_DISABLE",param_2);
    break;
  case 1:
    snprintf(acStack_98,0x80,"venc%d_smart_mode=SMART_LTR",param_2);
    break;
  case 2:
    snprintf(acStack_98,0x80,"venc%d_smart_mode=SMART_CHANGING_GOPLEN",param_2);
    break;
  case 3:
    snprintf(acStack_98,0x80,"venc%d_smart_mode=SMART_SKIP_FRAME",param_2);
    break;
  default:
    snprintf(acStack_98,0x80,"venc%d_smart_mode=UNKNOWN",param_2);
  }
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_smart_goplen=%d",param_2,(uint)param_1[0x1a]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_smart_quality=%d",param_2,(uint)param_1[0x1b]);
  ak_debug_info(0xd,0,acStack_98);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"venc%d_smart_static_value=%d",param_2,(uint)param_1[0x1c]);
  ak_debug_info(0xd,0,acStack_98);
  return;
}



undefined4 venc_check_akvenc_version(void)

{
  AKV_Encoder_GetVersionInfo();
  return 0;
}



// WARNING: Type propagation algorithm not settling

undefined4 ak_venc_open(ushort *param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined8 uVar9;
  int local_c8 [14];
  code *local_90;
  code *local_8c;
  code *local_88;
  code *local_84;
  code *local_80;
  code *local_7c;
  code *local_78;
  code *local_74;
  undefined *local_70;
  undefined *local_6c;
  undefined *local_68;
  undefined *local_64;
  undefined *local_60;
  undefined *local_5c;
  undefined *local_58;
  undefined *local_54;
  undefined *local_50;
  undefined *local_4c;
  undefined *local_48;
  undefined *local_44;
  undefined *local_40;
  undefined *local_3c;
  undefined *local_38;
  undefined *local_34;
  undefined *local_30;
  undefined1 *local_2c;
  
  AKV_Encoder_GetVersionInfo();
  local_c8[1] = 0;
  local_c8[2] = 0;
  local_c8[3] = 0;
  local_c8[4] = 0;
  local_c8[5] = 0;
  local_c8[6] = 0;
  local_c8[7] = 0;
  local_c8[8] = 0;
  local_c8[9] = 0;
  local_c8[10] = 0;
  local_c8[0xb] = 0;
  local_c8[0xc] = 0;
  local_c8[0xd] = 0;
  if ((param_1 == (ushort *)0x0) || (iVar1 = FUN_00012a14(param_1,local_c8 + 1), iVar1 != 0)) {
    ak_print(0xd,1,"[%s:%d] param is invalid\n","ak_venc_open",0x4c3);
    return 0xd000003;
  }
  if (param_2 == (int *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle_id is NULL\n","ak_venc_open",0x4ca);
    return 0xd000003;
  }
  ak_thread_rwlock_wrlock(DAT_00029048);
  if (DAT_00029044 == (code *)0x0) {
    if (DAT_00029074 == 1) {
      ak_print(0xd,4,"[%s:%d] the wait irq thread is already created!\n",
               "venc_create_wait_irq_thread",0xc1);
LAB_00014068:
      memset(&local_90,0,0x68);
      local_90 = (code *)&LAB_00012994;
      local_8c = FUN_000127d0;
      local_84 = (code *)&LAB_00012794;
      local_80 = (code *)&LAB_000127b0;
      local_7c = (code *)&LAB_00012978;
      local_78 = (code *)&ak_cb_dma_free;
      local_74 = (code *)&DAT_000127cc;
      local_70 = &ak_cb_release_frame_buf;
      local_6c = &ak_cb_module_clock;
      local_68 = &ak_cb_module_reset;
      local_64 = &ak_cb_mutex_init;
      local_60 = &ak_cb_mutex_destroy;
      local_5c = &ak_cb_mutex_lock;
      local_58 = &ak_cb_mutex_unlock;
      local_54 = &ak_cb_sem_init;
      local_50 = &ak_cb_sem_destroy;
      local_4c = &ak_cb_sem_wait;
      local_48 = &ak_cb_sem_post;
      local_44 = &ak_cb_thread_create;
      local_88 = ak_mem_free;
      local_40 = &ak_cb_thread_join;
      local_3c = &ak_cb_thread_delete;
      local_38 = &ak_cb_irq_wait;
      local_34 = &ak_cb_atomic_increment;
      local_30 = &ak_cb_atomic_decrement;
      local_2c = &LAB_00012944;
      if (DAT_00029094 == 0) {
        osal_drv_uio_init();
        ak_print(0xd,4,"[%s:%d] mapping, start: 0x%08x, len: 0x%08x\n","venc_cb_init_reg",0x12f,
                 0x20020000,0x10000);
        DAT_00029094 = osal_drv_uio_map_regs(0x20020000,0x10000);
        if (DAT_00029094 == 0) {
          ak_print(0xd,1,"[%s:%d] map failed\n","venc_cb_init_reg",0x137);
        }
        else {
          DAT_0002909c = 0x10000;
          DAT_00029098 = 0x20020000;
          ak_print(0xd,4,"[%s:%d] init venc reg, va: 0x%08x, pa: 0x%08x, len: 0x%08x\n",
                   "venc_cb_init_reg",0x143,DAT_00029094,0x20020000,0x10000);
        }
      }
      uVar9 = AKV_Encoder_Init(&local_90);
      if ((int)uVar9 != 0) {
        DAT_00029044 = (code *)0x1;
        memset(&local_90,0,0x40);
        memset(&local_90,0,0x40);
        snprintf((char *)&local_90,0x40,"venc_version=%s","libmpi_venc V1.0.29-debug1");
        ak_debug_info(0xd,1,&local_90);
        memset(&local_90,0,0x40);
        pcVar5 = (char *)AKV_Encoder_GetVersionInfo();
        snprintf((char *)&local_90,0x40,"akv_enc_version=%s",pcVar5);
        ak_debug_info(0xd,1,&local_90);
        goto LAB_00013efc;
      }
      FUN_00013314(0,(int)((ulonglong)uVar9 >> 0x20));
      FUN_000133ac();
      pcVar5 = "[%s:%d] venc_encoder_init failed!\n";
      uVar2 = 0x4e0;
    }
    else {
      DAT_00029074 = 1;
      local_c8[0] = -1;
      local_90 = DAT_00029044;
      local_8c = DAT_00029044;
      local_88 = DAT_00029044;
      local_84 = DAT_00029044;
      local_80 = DAT_00029044;
      local_7c = DAT_00029044;
      local_78 = DAT_00029044;
      local_74 = DAT_00029044;
      osal_drv_uio_find_node("video-encoder",local_c8);
      if (local_c8[0] == -1) {
        piVar6 = __errno_location();
        pcVar5 = strerror(*piVar6);
        ak_print(0xe,1,"[%s:%d] encoder uio not found: %s\n","venc_create_wait_irq_thread",0xcf,
                 pcVar5);
      }
      else {
        memset(&local_90,0,0x20);
        sprintf((char *)&local_90,"/dev/uio%d",local_c8[0]);
        DAT_00029040 = ak_open(&local_90,2);
        if (DAT_00029040 < 0) {
          DAT_00029074 = 0;
          piVar6 = __errno_location();
          pcVar5 = strerror(*piVar6);
          ak_print(0xd,1,"[%s:%d] %s open failed: %s\n","venc_create_wait_irq_thread",0xdb,&local_90
                   ,pcVar5);
        }
        else {
          iVar1 = ak_thread_create(&DAT_00029070,FUN_00012808,0,0x32000,0x5a);
          if (iVar1 == 0) goto LAB_00014068;
          DAT_00029074 = 0;
          ak_print(0xd,1,"[%s:%d] create wait decode irq thread failed!\n",
                   "venc_create_wait_irq_thread",0xee);
        }
      }
      uVar2 = 0x4d6;
      pcVar5 = "[%s:%d] venc_create_wait_irq_thread failed!\n";
    }
    ak_print(0xd,1,pcVar5,"ak_venc_open",uVar2);
    ak_thread_rwlock_unlock(DAT_00029048);
    uVar2 = 0xd000000;
  }
  else {
LAB_00013efc:
    if (DAT_0002906c < 8) {
      uVar2 = ak_get_os_timestamp();
      iVar1 = ak_mem_alloc_(0xd,0xa8,"ak_venc_open",uVar2);
      if (iVar1 == 0) {
        ak_print(0xd,1,"[%s:%d] malloc user failed\n","ak_venc_open",0x506);
        ak_thread_rwlock_unlock(DAT_00029048);
        uVar2 = 0x102;
      }
      else {
        memcpy((void *)(iVar1 + 4),param_1,0x3c);
        iVar8 = 0;
        piVar6 = &DAT_00029048;
        do {
          piVar6 = piVar6 + 1;
          if (*piVar6 == 0) {
            iVar4 = iVar8 + 2;
            DAT_0002906c = DAT_0002906c + 1;
            (&DAT_00029044)[iVar4] = (code *)iVar1;
            ak_print(0xd,3,"[%s:%d] open count = %d\n","ak_venc_open",0x516,DAT_0002906c);
            iVar1 = (int)(&DAT_00029044)[iVar4];
            *param_2 = iVar8;
            ak_thread_mutex_init(iVar1 + 0x40,0);
            uVar2 = 0x80000;
            ak_thread_mutex_lock((int)(&DAT_00029044)[iVar4] + 0x40);
            iVar1 = (uint)*param_1 * (uint)param_1[1];
            iVar8 = (int)(&DAT_00029044)[iVar4];
            *(undefined4 *)(iVar8 + 0x5c) = 0x80000;
            if (iVar1 < 0xe1000) {
              uVar2 = 0x40000;
              *(undefined4 *)(iVar8 + 0x5c) = 0x40000;
            }
            else if (iVar1 - 0x1fa401U < 0x2b5c00) {
              uVar2 = 0x100000;
              *(undefined4 *)(iVar8 + 0x5c) = 0x100000;
            }
            else if (0x4b0000 < iVar1) {
              uVar2 = 0x200000;
              *(undefined4 *)(iVar8 + 0x5c) = 0x200000;
            }
            uVar3 = ak_get_os_timestamp();
            uVar2 = ak_mem_alloc_(0xd,uVar2,"ak_venc_open",uVar3);
            iVar1 = (int)(&DAT_00029044)[iVar4];
            *(undefined4 *)(iVar8 + 0x58) = uVar2;
            if (*(int *)(iVar1 + 0x58) == 0) {
              ak_print(0xd,1,"[%s:%d] malloc encbuf failed\n","ak_venc_open",0x53b);
              uVar2 = 0x102;
            }
            else {
              memcpy((void *)(iVar1 + 4),param_1,0x3c);
              uVar2 = 0;
              local_90 = (code *)0x0;
              local_8c = (code *)0x0;
              local_88 = (code *)0x0;
              local_84 = (code *)0x0;
              local_80 = (code *)0x0;
              local_7c = (code *)0x0;
              local_78 = (code *)0x0;
              local_74 = (code *)0x0;
              local_70 = (undefined *)0x0;
              local_6c = (undefined *)0x0;
              local_68 = (undefined *)0x0;
              local_64 = (undefined *)0x0;
              local_60 = (undefined *)0x0;
              local_5c = (undefined *)0x0;
              ak_print(0xd,3,"[%s:%d] we don\'t use config for encode\n","ak_venc_open",0x545);
              memcpy(&local_8c,local_c8 + 1,0x34);
              puVar7 = (undefined4 *)(&DAT_00029044)[iVar4];
              uVar3 = AKV_Encoder_Open(&local_90);
              piVar6 = (int *)(&DAT_00029044)[iVar4];
              *puVar7 = uVar3;
              if (*piVar6 != 0) {
                ak_print(0xd,3,"[%s:%d] Video encoder open success\n","ak_venc_open",0x554);
                ak_print(0xd,4,
                         "[%s:%d] \n\tparams: w=%d, h=%d, qpmin=%d, qpmax=%d,bps=%d, gop=%u, fps=%u, profile=%d\n"
                         ,"ak_venc_open",0x55e,(uint)local_80 & 0xffff,(uint)local_80 >> 0x10,
                         (uint)local_74 & 0xffff,(uint)local_74 >> 0x10,(uint)local_7c & 0xffff,
                         (uint)local_70 & 0xffff,(uint)local_78 & 0xffff,local_8c);
                ak_thread_mutex_unlock((int)(&DAT_00029044)[iVar4] + 0x40);
                venc_info(param_1,*param_2);
                goto LAB_00014608;
              }
              ak_print(0xd,1,"[%s:%d] AKV_Encoder_Open failed!\n","ak_venc_open",0x54e);
              uVar2 = 0xd000001;
            }
            iVar1 = (int)(&DAT_00029044)[iVar4];
            if (iVar1 != 0) {
              if (*(int *)(iVar1 + 0x58) != 0) {
                ak_mem_free();
                iVar1 = (int)(&DAT_00029044)[iVar4];
                *(undefined4 *)(iVar1 + 0x58) = 0;
              }
              ak_thread_mutex_unlock(iVar1 + 0x40);
              ak_thread_mutex_destroy((int)(&DAT_00029044)[iVar4] + 0x40);
              ak_mem_free((&DAT_00029044)[iVar4]);
              DAT_0002906c = DAT_0002906c + -1;
              (&DAT_00029044)[iVar4] = (code *)0x0;
              *param_2 = -1;
            }
            if (DAT_0002906c == 0) {
              uVar9 = AKV_Encoder_Destroy();
              FUN_00013314((int)uVar9,(int)((ulonglong)uVar9 >> 0x20));
              FUN_000133ac();
              DAT_00029044 = (code *)0x0;
            }
LAB_00014608:
            ak_thread_rwlock_unlock(DAT_00029048);
            ak_print(0xd,4,"[%s:%d] exit....\n","ak_venc_open",0x58a);
            return uVar2;
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 != 8);
        ak_print(0xd,1,"[%s:%d] open count too many, open count = %d\n","ak_venc_open",0x522,
                 DAT_0002906c);
        ak_thread_rwlock_unlock(DAT_00029048);
        ak_mem_free(iVar1);
        uVar2 = 0xd000002;
      }
    }
    else {
      ak_print(0xd,1,"[%s:%d] open count too many, now open count = %d\n","ak_venc_open",0x4fa,
               DAT_0002906c);
      ak_thread_rwlock_unlock(DAT_00029048);
      uVar2 = 0xd000002;
    }
  }
  return uVar2;
}



// WARNING: Type propagation algorithm not settling

undefined4
ak_venc_encode_frame(uint param_1,int param_2,undefined4 param_3,int param_4,int *param_5)

{
  size_t sVar1;
  undefined2 extraout_r0;
  undefined2 extraout_r0_00;
  int iVar2;
  void *__dest;
  uint uVar3;
  int extraout_r0_01;
  uint uVar4;
  undefined2 uVar5;
  uint uVar6;
  undefined4 uVar7;
  ushort uVar8;
  undefined4 *puVar9;
  undefined1 auStack_70 [8];
  int local_68 [4];
  int *local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  void *local_40;
  undefined4 local_3c;
  size_t local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_5 == (int *)0x0 || param_2 == 0) {
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar9 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar9 = (undefined4 *)FUN_000132d4();
  }
  if (puVar9 == (undefined4 *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_encode_frame",0x5a8,
             param_1);
    uVar7 = 0xd000004;
  }
  else {
    local_68[1] = 0;
    local_68[2] = 0;
    local_68[3] = 0;
    local_68[0] = param_2;
    iVar2 = ak_mem_dma_vaddr2paddr(param_2,local_68 + 1);
    if (iVar2 == 0) {
      local_54 = 0;
      local_50 = 0;
      if (param_4 != 0) {
        if ((uint)*(ushort *)((int)puVar9 + 6) % 0x18 == 0) {
          uVar5 = 0x18;
        }
        else {
          uVar5 = 0x10;
        }
        local_54 = CONCAT22(uVar5,0x20);
        local_50 = param_4;
      }
      local_40 = (void *)puVar9[0x16];
      local_3c = puVar9[0x17];
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      local_68[2] = param_3;
      local_68[3] = iVar2;
      local_58 = local_68;
      local_4c = iVar2;
      local_48 = iVar2;
      local_44 = iVar2;
      ak_thread_mutex_lock(puVar9 + 0x10);
      AKV_Encoder_Process(*puVar9,&local_58,&local_40);
      ak_thread_mutex_unlock(puVar9 + 0x10);
      sVar1 = local_38;
      if (local_38 == 0) {
        param_5[1] = 0;
        uVar7 = 0xd000006;
      }
      else {
        uVar7 = ak_get_os_timestamp();
        __dest = (void *)ak_mem_alloc_(0xd,sVar1,"ak_venc_encode_frame",uVar7);
        *param_5 = (int)__dest;
        if (__dest != (void *)0x0) {
          memcpy(__dest,local_40,local_38);
          if (local_34 == 2) {
            param_5[5] = 1;
          }
          else if (local_34 == 3) {
            param_5[5] = 2;
          }
          else if (local_34 == 1) {
            param_5[5] = 0;
          }
          param_5[1] = local_38;
          ak_get_ostime(auStack_70);
          uVar3 = ak_diff_ms_time(auStack_70,puVar9 + 0x1b);
          if (param_5[5] == 1) {
            if (0 < (int)uVar3) goto LAB_00014c14;
LAB_00014c54:
            uVar8 = *(ushort *)((int)puVar9 + 10);
          }
          else {
            uVar8 = *(ushort *)((int)puVar9 + 10);
            FUN_00016d00((uint)uVar8 * 1000,(uint)*(undefined2 *)(puVar9 + 2));
            if (extraout_r0_01 < (int)uVar3) {
LAB_00014c14:
              FUN_00016d00(puVar9[0x18] * 1000,uVar3);
              *(undefined2 *)(puVar9 + 0x1d) = extraout_r0;
              FUN_00016d00(puVar9[0x19] * 1000,uVar3);
              puVar9[0x18] = 0;
              puVar9[0x19] = 0;
              *(undefined2 *)(puVar9 + 0x1e) = extraout_r0_00;
              ak_get_ostime(puVar9 + 0x1b);
              goto LAB_00014c54;
            }
          }
          uVar4 = param_5[1];
          uVar6 = puVar9[0x1a];
          uVar3 = uVar6;
          if (uVar6 < uVar4) {
            uVar3 = uVar4;
          }
          puVar9[0x19] = puVar9[0x19] + uVar4;
          puVar9[0x18] = puVar9[0x18] + 1;
          if (uVar6 < uVar4) {
            puVar9[0x1a] = uVar3;
          }
          *(short *)((int)puVar9 + 0x7a) = (short)uVar3;
          *(ushort *)((int)puVar9 + 0x76) = uVar8;
          uVar7 = 0;
          goto LAB_00014b14;
        }
        ak_print(0xd,1,"[%s:%d] mem alloc %lubytes fail\n","ak_venc_encode_frame",0x5f1,local_38);
        uVar7 = 0x102;
        param_5[1] = 0;
      }
    }
    else {
      ak_print(0xd,1,"[%s:%d] handle id : %d, can\'t get the dma address\n","ak_venc_encode_frame",
               0x5b3,param_1);
      uVar7 = 0x102;
    }
  }
  if (*param_5 != 0) {
    ak_mem_free();
    *param_5 = 0;
  }
LAB_00014b14:
  ak_thread_rwlock_unlock(DAT_00029048);
  return uVar7;
}



undefined4 ak_venc_release_stream(undefined4 param_1,int *param_2)

{
  if (param_2 != (int *)0x0) {
    if (*param_2 != 0) {
      ak_mem_free();
      *param_2 = 0;
    }
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] invalid stream\n","ak_venc_release_stream",0x635);
  return 0xd000003;
}



undefined4 ak_venc_close(uint param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  bool bVar5;
  undefined8 uVar6;
  char acStack_60 [68];
  
  ak_print(0xd,4,"[%s:%d] enter...\n","ak_venc_close",0x64c);
  ak_thread_rwlock_wrlock(DAT_00029048);
  if (param_1 < 8) {
    piVar1 = (int *)(&DAT_0002904c)[param_1];
  }
  else {
    piVar1 = (int *)FUN_000132d4();
  }
  if (piVar1 == (int *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_close",0x653,param_1);
    uVar2 = 0xd000004;
  }
  else {
    piVar3 = piVar1 + 0x10;
    ak_thread_mutex_lock(piVar3);
    if (*piVar1 != 0) {
      AKV_Encoder_Close();
      *piVar1 = 0;
      ak_print(0xd,4,"[%s:%d] Video Stream Encoder Close OK\n","ak_venc_close",0x65e);
    }
    if (piVar1[0x16] != 0) {
      ak_mem_free();
    }
    ak_thread_mutex_unlock(piVar3);
    ak_thread_mutex_destroy(piVar3);
    uVar4 = DAT_0002906c - 1;
    DAT_0002906c = uVar4;
    ak_print(0xd,4,"[%s:%d] user_count=%d\n","ak_venc_close",0x668,uVar4);
    ak_mem_free(piVar1);
    bVar5 = DAT_0002906c == 0;
    (&DAT_00029044)[param_1 + 2] = 0;
    if (bVar5) {
      uVar6 = AKV_Encoder_Destroy();
      FUN_00013314((int)uVar6,(int)((ulonglong)uVar6 >> 0x20));
      FUN_000133ac();
      DAT_00029044 = 0;
    }
    memset(acStack_60,0,0x40);
    memset(acStack_60,0,0x40);
    snprintf(acStack_60,0x40,"venc%d=closed",param_1);
    ak_debug_info(0xd,1,acStack_60);
    uVar2 = 0;
    param_1 = uVar4;
  }
  ak_thread_rwlock_unlock(DAT_00029048);
  ak_print(0xd,5,"[%s:%d] leave...\n","ak_venc_close",0x683,param_1);
  return uVar2;
}



undefined4 ak_venc_get_attr(uint param_1,undefined2 *param_2)

{
  undefined4 *puVar1;
  uint local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
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
  local_28 = 0;
  local_24 = 0;
  if (param_2 == (undefined2 *)0x0) {
    ak_print(0xd,1,"[%s:%d] param is NULL\n","ak_venc_get_attr",0x6d0);
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_get_attr",0x6da,param_1);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0xd000004;
  }
  ak_thread_mutex_lock(puVar1 + 0x10);
  AKV_Encoder_Get_Parameters(*puVar1,&local_54);
  ak_thread_mutex_unlock(puVar1 + 0x10);
  ak_thread_rwlock_unlock(DAT_00029048);
  *param_2 = (undefined2)local_48;
  param_2[1] = local_48._2_2_;
  param_2[2] = (undefined2)local_40;
  param_2[3] = (undefined2)local_38;
  param_2[4] = (undefined2)local_44;
  param_2[5] = local_44._2_2_;
  if (local_54 == 0x1000242) {
    *(undefined4 *)(param_2 + 6) = 3;
    *(undefined4 *)(param_2 + 0x12) = 0;
  }
  else if (local_54 < 0x1000243) {
    if (local_54 == 0x100004d) {
      *(undefined4 *)(param_2 + 6) = 0;
      *(undefined4 *)(param_2 + 0x12) = 0;
    }
    else if (local_54 == 0x1000064) {
      *(undefined4 *)(param_2 + 6) = 1;
      *(undefined4 *)(param_2 + 0x12) = 0;
    }
    else if (local_54 == 0x1000042) {
      *(undefined4 *)(param_2 + 6) = 2;
      *(undefined4 *)(param_2 + 0x12) = 0;
    }
  }
  else if (local_54 == 0x2000003) {
    *(undefined4 *)(param_2 + 6) = 5;
    *(undefined4 *)(param_2 + 0x12) = 2;
  }
  else if (local_54 < 0x2000004) {
    if (local_54 == 0x2000001) {
      *(undefined4 *)(param_2 + 6) = 4;
      *(undefined4 *)(param_2 + 0x12) = 2;
    }
  }
  else if (local_54 == 0x2fa0004) {
    *(undefined4 *)(param_2 + 6) = 6;
    *(undefined4 *)(param_2 + 0x12) = 2;
  }
  else if (local_54 == 0x4000000) {
    *(undefined4 *)(param_2 + 6) = 7;
    *(undefined4 *)(param_2 + 0x12) = 1;
  }
  switch(local_50) {
  case 0:
    *(undefined4 *)(param_2 + 8) = 2;
    break;
  case 1:
    *(undefined4 *)(param_2 + 8) = 0;
    break;
  case 2:
    *(undefined4 *)(param_2 + 8) = 1;
    break;
  case 3:
    *(undefined4 *)(param_2 + 8) = 3;
  }
  *(uint *)(param_2 + 0x18) = local_34 >> 0x10;
  param_2[10] = local_40._2_2_;
  param_2[0xb] = (undefined2)local_3c;
  param_2[0xc] = local_3c._2_2_;
  *(uint *)(param_2 + 0xe) = local_2c & 0xffff;
  *(undefined4 *)(param_2 + 0x10) = local_4c;
  *(undefined4 *)(param_2 + 0x14) = local_28;
  param_2[0x16] = (undefined2)local_24;
  param_2[0x1a] = (undefined2)local_30;
  param_2[0x1b] = local_30._2_2_;
  param_2[0x1c] = local_2c._2_2_;
  return 0;
}



undefined4 ak_venc_set_attr(uint param_1,ushort *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_5c [3];
  int local_50;
  int local_38;
  
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  memset(local_5c,0,0x3c);
  if (param_2 == (ushort *)0x0) {
    ak_print(0xd,1,"[%s:%d] param is NULL\n","ak_venc_set_attr",0x696);
    return 0xd000003;
  }
  iVar1 = ak_venc_get_attr(param_1,(undefined2 *)local_5c);
  if (iVar1 == 0) {
    if (*(int *)(param_2 + 0x12) == local_38) {
      if (*(int *)param_2 == local_5c[0]) {
        if (*(int *)(param_2 + 6) == local_50) {
          iVar1 = FUN_00012a14(param_2,&local_90);
          if (iVar1 == 0) {
            ak_thread_rwlock_rdlock(DAT_00029048);
            if (param_1 < 8) {
              puVar2 = (undefined4 *)(&DAT_0002904c)[param_1];
            }
            else {
              puVar2 = (undefined4 *)FUN_000132d4();
            }
            if (puVar2 == (undefined4 *)0x0) {
              ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_attr",0x6ac,
                       param_1);
              ak_thread_rwlock_unlock(DAT_00029048);
              return 0xd000004;
            }
            ak_thread_mutex_lock(puVar2 + 0x10);
            AKV_Encoder_Set_Parameters(*puVar2,&local_90);
            memcpy(puVar2 + 1,param_2,0x3c);
            ak_thread_mutex_unlock(puVar2 + 0x10);
            ak_thread_rwlock_unlock(DAT_00029048);
            venc_info(param_2,param_1);
            return 0;
          }
        }
        else {
          ak_print(0xd,1,"[%s:%d] profile cannot be set dynamically.\n",
                   "venc_compare_and_format_param",0x346);
        }
      }
      else {
        ak_print(0xd,1,"[%s:%d] width and height cannot be set dynamically.\n",
                 "venc_compare_and_format_param",0x33f);
      }
    }
    else {
      ak_print(0xd,1,"[%s:%d] enc_out_type cannot be set dynamically.\n",
               "venc_compare_and_format_param",0x337);
    }
    ak_print(0xd,1,"[%s:%d] param is invalid\n","ak_venc_set_attr",0x6a3);
  }
  return 0xd000003;
}



undefined4 ak_venc_request_idr(uint param_1)

{
  undefined4 *puVar1;
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_Set_EncIFrame(*puVar1);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_request_idr",0x6f8,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_get_stat(uint param_1,void *param_2)

{
  int iVar1;
  
  if (param_2 == (void *)0x0) {
    ak_print(0xd,1,"[%s:%d] stat is NULL\n","ak_venc_get_stat",0x713);
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    iVar1 = (&DAT_0002904c)[param_1];
  }
  else {
    iVar1 = FUN_000132d4();
  }
  if (iVar1 != 0) {
    memcpy(param_2,(void *)(iVar1 + 0x74),8);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_get_stat",0x71c,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_qp(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  bool bVar4;
  bool bVar5;
  char acStack_58 [64];
  
  bVar5 = SBORROW4(param_2,param_3);
  iVar1 = param_2 - param_3;
  bVar4 = param_2 == param_3;
  if ((int)param_2 <= (int)param_3) {
    bVar5 = SBORROW4(param_2,0x33);
    iVar1 = param_2 - 0x33;
    bVar4 = param_2 == 0x33;
  }
  if ((int)param_3 < 0x34 && (bVar4 || iVar1 < 0 != bVar5)) {
    ak_thread_rwlock_rdlock(DAT_00029048);
    if (param_1 < 8) {
      puVar3 = (undefined4 *)(&DAT_0002904c)[param_1];
    }
    else {
      puVar3 = (undefined4 *)FUN_000132d4();
    }
    if (puVar3 == (undefined4 *)0x0) {
      ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_qp",0x740,param_1);
      ak_thread_rwlock_unlock(DAT_00029048);
      uVar2 = 0xd000004;
    }
    else {
      AKV_Encoder_Apply_Quality(*puVar3,param_2 & 0xff,param_3 & 0xff);
      ak_thread_rwlock_unlock(DAT_00029048);
      memset(acStack_58,0,0x40);
      snprintf(acStack_58,0x40,"venc%d_minqp=%d",param_1,param_2);
      ak_debug_info(0xd,0,acStack_58);
      memset(acStack_58,0,0x40);
      snprintf(acStack_58,0x40,"venc%d_maxqp=%d",param_1,param_3);
      ak_debug_info(0xd,0,acStack_58);
      uVar2 = 0;
    }
  }
  else {
    ak_print(0xd,1,"[%s:%d] invalid value\n","ak_venc_set_qp",0x737);
    uVar2 = 0xd000003;
  }
  return uVar2;
}



undefined4 ak_venc_reset_qp(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  char acStack_58 [64];
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    AKV_Encoder_Disable_Apply_Quality(*puVar1);
    ak_thread_rwlock_unlock(DAT_00029048);
    memset(acStack_58,0,0x40);
    snprintf(acStack_58,0x40,"venc%d_minqp=%d",param_1,(uint)*(ushort *)((int)puVar1 + 0x1a));
    ak_debug_info(0xd,0,acStack_58);
    memset(acStack_58,0,0x40);
    snprintf(acStack_58,0x40,"venc%d_maxqp=%d",param_1,(uint)*(ushort *)(puVar1 + 7));
    ak_debug_info(0xd,0,acStack_58);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_reset_qp",0x767,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_stream_buff(uint param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  char acStack_50 [64];
  
  if (param_2 < 1) {
    ak_print(0xd,1,"[%s:%d] size error:%d\n","ak_venc_set_stream_buff",0x78c,param_2);
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    AKV_Encoder_Set_StreamBufferSize(*puVar1,param_2);
    ak_thread_rwlock_unlock(DAT_00029048);
    memset(acStack_50,0,0x40);
    snprintf(acStack_50,0x40,"venc%d_stream_buff_size=%d",param_1,param_2);
    ak_debug_info(0xd,0,acStack_50);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_stream_buff",0x795,
           param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_iframe_param(uint param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  char acStack_68 [68];
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    AKV_Encoder_Set_IFrameSize_AdjustmentParameters
              (*puVar1,param_2 & 0xffff,param_3 & 0xffff,param_4,param_5);
    ak_thread_rwlock_unlock(DAT_00029048);
    memset(acStack_68,0,0x40);
    snprintf(acStack_68,0x40,"venc%d_IFrame_minqp=%d",param_1,param_2);
    ak_debug_info(0xd,0,acStack_68);
    memset(acStack_68,0,0x40);
    snprintf(acStack_68,0x40,"venc%d_IFrame_maxQP=%d",param_1,param_3);
    ak_debug_info(0xd,0,acStack_68);
    memset(acStack_68,0,0x40);
    snprintf(acStack_68,0x40,"venc%d_IFrame_minframeSize=%d",param_1,param_4);
    ak_debug_info(0xd,0,acStack_68);
    memset(acStack_68,0,0x40);
    snprintf(acStack_68,0x40,"venc%d_IFrame_maxframeSize=%d",param_1,param_5);
    ak_debug_info(0xd,0,acStack_68);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_iframe_param",0x7ba,
           param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_get_iframe_param(uint param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_3 == 0 || param_2 == 0) || (param_5 == 0 || param_4 == 0)) {
    ak_print(0xd,1,"[%s:%d] invalid param\n","ak_venc_get_iframe_param",0x7e3);
    uVar1 = 0x101;
  }
  else {
    ak_thread_rwlock_rdlock(DAT_00029048);
    if (param_1 < 8) {
      puVar2 = (undefined4 *)(&DAT_0002904c)[param_1];
    }
    else {
      puVar2 = (undefined4 *)FUN_000132d4();
    }
    if (puVar2 == (undefined4 *)0x0) {
      ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_get_iframe_param",0x7ed,
               param_1);
      ak_thread_rwlock_unlock(DAT_00029048);
      uVar1 = 0xd000004;
    }
    else {
      AKV_Encoder_Get_IFrameSize_AdjustmentParameters(*puVar2,param_2,param_3,param_4,param_5);
      ak_thread_rwlock_unlock(DAT_00029048);
      uVar1 = 0;
    }
  }
  return uVar1;
}



undefined4
ak_venc_set_ROI_Mdinfo
          (uint param_1,undefined2 param_2,short param_3,short param_4,undefined2 param_5,
          undefined2 param_6)

{
  undefined4 *puVar1;
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_Set_ROI_Mdinfo(*puVar1,param_2,(int)param_3,(int)param_4,param_5,param_6);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_ROI_Mdinfo",0x804,
           param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_jpeg_slice(uint param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_3 == 0 || param_2 == 0) {
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 == (undefined4 *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_jpeg_slice",0x82c,
             param_1);
    uVar2 = 0xd000004;
  }
  else {
    puVar1[0x20] = puVar1[0x16];
    puVar1[0x21] = puVar1[0x17];
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_Set_Jpeg_MergeStream(*puVar1,puVar1 + 0x20,param_2 & 0xffff,param_3 & 0xffff);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    uVar2 = 0;
  }
  ak_thread_rwlock_unlock(DAT_00029048);
  return uVar2;
}



// WARNING: Type propagation algorithm not settling

undefined4
ak_venc_jpeg_slice_encode
          (uint param_1,int param_2,undefined4 param_3,undefined2 param_4,undefined2 param_5,
          int *param_6)

{
  int iVar1;
  void *__dest;
  undefined4 uVar2;
  undefined4 *puVar3;
  int local_50 [4];
  int *local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  if (param_6 == (int *)0x0 || param_2 == 0) {
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar3 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar3 = (undefined4 *)FUN_000132d4();
  }
  if (puVar3 == (undefined4 *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_jpeg_slice_encode",0x858,
             param_1);
    uVar2 = 0xd000004;
  }
  else {
    local_50[1] = 0;
    local_50[2] = 0;
    local_50[3] = 0;
    local_50[0] = param_2;
    iVar1 = ak_mem_dma_vaddr2paddr(param_2,local_50 + 1);
    if (iVar1 == 0) {
      local_50[2] = param_3;
      local_50[3] = iVar1;
      local_40 = local_50;
      local_3c = iVar1;
      local_38 = iVar1;
      local_34 = iVar1;
      local_30 = iVar1;
      local_2c = iVar1;
      ak_thread_mutex_lock(puVar3 + 0x10);
      AKV_Encoder_Process_Jpeg_MergeStream(*puVar3,&local_40,param_4,param_5);
      ak_thread_mutex_unlock(puVar3 + 0x10);
      iVar1 = puVar3[0x22];
      if (iVar1 == 0) {
        param_6[1] = 0;
      }
      else {
        uVar2 = ak_get_os_timestamp();
        __dest = (void *)ak_mem_alloc_(0xd,iVar1,"ak_venc_jpeg_slice_encode",uVar2);
        *param_6 = (int)__dest;
        if (__dest == (void *)0x0) {
          ak_print(0xd,1,"[%s:%d] mem alloc %lubytes fail\n","ak_venc_jpeg_slice_encode",0x882,
                   puVar3[0x22]);
          uVar2 = 0x102;
          param_6[1] = 0;
          goto LAB_000162a4;
        }
        memcpy(__dest,(void *)puVar3[0x20],puVar3[0x22]);
        param_6[1] = puVar3[0x22];
      }
      uVar2 = 0;
      goto LAB_000162c0;
    }
    ak_print(0xd,1,"[%s:%d] handle id : %d, can\'t get the dma address\n",
             "ak_venc_jpeg_slice_encode",0x863,param_1);
    uVar2 = 0x102;
  }
LAB_000162a4:
  if (*param_6 != 0) {
    ak_mem_free();
    *param_6 = 0;
  }
LAB_000162c0:
  ak_thread_rwlock_unlock(DAT_00029048);
  return uVar2;
}



undefined4 ak_venc_change_CUblocksize(uint param_1,undefined2 param_2)

{
  undefined4 *puVar1;
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_Change_CUBlockSize(*puVar1,param_2);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_change_CUblocksize",0x8a7,
           param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_strictlylimit_frameSize(uint param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (param_2 < 0) {
    ak_print(0xd,1,"[%s:%d] not support the size value %d\n","ak_venc_strictlylimit_frameSize",0x8c2
             ,param_2);
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_StrictlyLimit_FrameSize(*puVar1,param_2);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_strictlylimit_frameSize",
           0x8cc,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_rc_cb(uint param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  
  if (param_2 == 0) {
    ak_print(0xd,3,"[%s:%d] handle id : %d, rc callback function is NULL\n","ak_venc_set_rc_cb",
             0x8ed,param_1);
  }
  if (param_3 == 0) {
    ak_print(0xd,3,"[%s:%d] handle id : %d, rc user handle is NULL\n","ak_venc_set_rc_cb",0x8f1,
             param_1);
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_Set_RC_Callback(*puVar1,param_2,param_3);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_rc_cb",0x8fa,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_unset_rc_cb(uint param_1)

{
  undefined4 *puVar1;
  
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar1 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar1 = (undefined4 *)FUN_000132d4();
  }
  if (puVar1 != (undefined4 *)0x0) {
    ak_thread_mutex_lock(puVar1 + 0x10);
    AKV_Encoder_UnSet_RC_Callback(*puVar1);
    ak_thread_mutex_unlock(puVar1 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_unset_rc_cb",0x917,param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



undefined4 ak_venc_set_skipmode(uint param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (1 < param_2) {
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    puVar2 = (undefined4 *)(&DAT_0002904c)[param_1];
  }
  else {
    puVar2 = (undefined4 *)FUN_000132d4();
  }
  if (puVar2 == (undefined4 *)0x0) {
    ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_skipmode",0x938,
             param_1);
    ak_thread_rwlock_unlock(DAT_00029048);
    uVar1 = 0xd000004;
  }
  else {
    ak_thread_mutex_lock(puVar2 + 0x10);
    AKV_SET_SKIPMODE(*puVar2,param_2);
    ak_thread_mutex_unlock(puVar2 + 0x10);
    ak_thread_rwlock_unlock(DAT_00029048);
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 ak_venc_set_spec_param(uint param_1,void *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_2 == (void *)0x0) {
    return 0xd000003;
  }
  if ((*(uint *)((int)param_2 + 8) & 0xfffffffb) == 1) {
    if (*(byte *)((int)param_2 + 2) < 2) {
      if (*(byte *)((int)param_2 + 4) < 2) {
        if (*(byte *)((int)param_2 + 5) < 2) {
          if (*(byte *)((int)param_2 + 3) < 8) {
            ak_thread_rwlock_rdlock(DAT_00029048);
            if (param_1 < 8) {
              puVar2 = (undefined4 *)(&DAT_0002904c)[param_1];
            }
            else {
              puVar2 = (undefined4 *)FUN_000132d4();
            }
            if (puVar2 == (undefined4 *)0x0) {
              ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_set_spec_param",
                       0x97e,param_1);
              ak_thread_rwlock_unlock(DAT_00029048);
              uVar1 = 0xd000004;
            }
            else {
              ak_thread_mutex_lock(puVar2 + 0x10);
              AKV_Encoder_Set_SpecialParameters(*puVar2,param_2);
              memcpy(puVar2 + 0x26,param_2,0xc);
              ak_thread_mutex_unlock(puVar2 + 0x10);
              ak_thread_rwlock_unlock(DAT_00029048);
              uVar1 = 0;
            }
          }
          else {
            ak_print(0xd,1,"[%s:%d] video_format %d error\n","ak_venc_set_spec_param",0x975,
                     *(byte *)((int)param_2 + 3));
            uVar1 = 0xd000003;
          }
        }
        else {
          ak_print(0xd,1,"[%s:%d] colour_description_present_flag %d error\n",
                   "ak_venc_set_spec_param",0x96d,*(byte *)((int)param_2 + 5));
          uVar1 = 0xd000003;
        }
      }
      else {
        ak_print(0xd,1,"[%s:%d] video_full_range_flag %d error\n","ak_venc_set_spec_param",0x966,
                 *(byte *)((int)param_2 + 4));
        uVar1 = 0xd000003;
      }
    }
    else {
      ak_print(0xd,1,"[%s:%d] video_signal_type_present_flag %d error\n","ak_venc_set_spec_param",
               0x95f,*(byte *)((int)param_2 + 2));
      uVar1 = 0xd000003;
    }
    return uVar1;
  }
  ak_print(0xd,1,"[%s:%d] eColourDescription %d error\n","ak_venc_set_spec_param",0x957,
           *(uint *)((int)param_2 + 8));
  return 0xd000003;
}



undefined4 ak_venc_get_spec_param(uint param_1,void *param_2)

{
  int iVar1;
  
  if (param_2 == (void *)0x0) {
    return 0xd000003;
  }
  ak_thread_rwlock_rdlock(DAT_00029048);
  if (param_1 < 8) {
    iVar1 = (&DAT_0002904c)[param_1];
  }
  else {
    iVar1 = FUN_000132d4();
  }
  if (iVar1 != 0) {
    ak_thread_mutex_lock(iVar1 + 0x40);
    memcpy(param_2,(void *)(iVar1 + 0x98),0xc);
    ak_thread_mutex_unlock(iVar1 + 0x40);
    ak_thread_rwlock_unlock(DAT_00029048);
    return 0;
  }
  ak_print(0xd,1,"[%s:%d] handle id : %d, venc user is NULL\n","ak_venc_get_spec_param",0x9a0,
           param_1);
  ak_thread_rwlock_unlock(DAT_00029048);
  return 0xd000004;
}



ulonglong FUN_00016d00(uint param_1,uint param_2)

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



uint FUN_00016d08(uint param_1,uint param_2)

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



void FUN_00016ddc(uint param_1,uint param_2)

{
  if (param_2 != 0) {
    FUN_00016d08(param_1,param_2);
    return;
  }
  raise(8);
  return;
}



void _fini(void)

{
  return;
}


