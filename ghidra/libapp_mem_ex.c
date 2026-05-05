
undefined4 ak_app_mem_ex_dma_pool_activate(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int local_3c;
  int local_38 [5];
  
  iVar1 = g_vi_policy._36_4_ * g_vi_policy._32_4_;
  iVar8 = ((g_vi_policy._0_4_ * g_vi_policy._4_4_ * 3) / 2) * 5;
  iVar11 = iVar8 + 3;
  if (iVar8 < 0) {
    iVar8 = iVar11;
  }
  iVar2 = iVar1;
  if (0 < iVar1) {
    iVar2 = iVar1 * 3;
  }
  if (0 < iVar1) {
    iVar11 = iVar2 >> 1;
  }
  if (iVar1 < 1) {
    iVar11 = 0;
  }
  else {
    iVar11 = iVar11 + 0x800;
  }
  iVar8 = g_vi_policy._40_4_ * iVar11 +
          g_vi_policy._28_4_ * ((g_vi_policy._20_4_ * g_vi_policy._24_4_ * 3) / 2 + 0x800) +
          g_vi_policy._16_4_ * ((g_vi_policy._8_4_ * g_vi_policy._12_4_ * 3) / 2 + 0x800) +
          (iVar8 >> 2) + 0x40;
  iVar11 = ak_mem_dma_pool_create(7,iVar8);
  if (iVar11 == 0) {
    ak_print(0x1e,3,"[%s:%d] ak_mem_dma_pool_create vi size:%d OK!\n",
             "ak_app_mem_ex_dma_pool_activate",0xd8,iVar8);
    iVar11 = 0;
    iVar8 = 0;
    iVar1 = 0;
    local_38[0] = 0;
    local_38[1] = 0;
    local_38[2] = 0;
    local_38[3] = 0;
    while( true ) {
      iVar2 = iVar11 * 4;
      iVar12 = local_38[1];
      if (*(int *)(venc_str_max + iVar11 * 4) != 0) {
        piVar6 = (int *)(venc_str_max + iVar2);
        do {
          piVar6 = piVar6 + 1;
          iVar12 = iVar12 + *piVar6;
        } while (piVar6 != (int *)(venc_str_max + (*(int *)(venc_str_max + iVar11 * 4) + iVar11) * 4
                                  ));
        local_38[iVar8] = iVar12;
      }
      iVar4 = local_38[3];
      if (*(int *)(venc_jpg_max + iVar2) != 0) {
        piVar6 = (int *)(venc_jpg_max + iVar2);
        do {
          piVar6 = piVar6 + 1;
          iVar4 = iVar4 + *piVar6;
        } while (piVar6 != (int *)(venc_jpg_max + (*(int *)(venc_jpg_max + iVar2) + iVar11) * 4));
        local_38[iVar8 + 2] = iVar4;
      }
      iVar1 = iVar1 + iVar12 + iVar4;
      iVar11 = iVar11 + 0x15;
      if (iVar8 == 1) break;
      iVar8 = 1;
    }
    iVar11 = ak_mem_dma_pool_create(0xd,iVar1);
    if (iVar11 != 0) {
      ak_print(0x1e,1,"[%s:%d] ak_mem_dma_pool_create venc size:%d failed!\n",
               "ak_app_mem_ex_dma_pool_activate",0xf9,iVar1);
      return 0x103;
    }
    ak_print(0x1e,3,"[%s:%d] ak_mem_dma_pool_create venc size:%d OK!\n",
             "ak_app_mem_ex_dma_pool_activate",0xfd,iVar1);
    iVar11 = ak_mem_dma_pool_activate();
    if (iVar11 == 0) {
      iVar11 = 0;
      uVar10 = 0;
      local_3c = 0;
      do {
        if (*(int *)(venc_str_max + iVar11) != 0) {
          piVar6 = (int *)(venc_str_min + iVar11 + 4);
          piVar9 = (int *)(venc_str_max + iVar11);
          uVar7 = 0;
          do {
            while( true ) {
              piVar9 = piVar9 + 1;
              uVar7 = uVar7 + 1;
              if ((*piVar9 == 0) || (*piVar6 == 0)) break;
              uVar5 = ak_mem_dma_pool_create_reserved_obj(0xd);
              iVar8 = *piVar6;
              piVar6 = piVar6 + 1;
              uVar10 = uVar10 | uVar5;
              ak_print(0x1e,3,
                       "[%s:%d] ak_mem_dma_pool_create_reserved_obj venc_stream[%d] size:%lu, thresh old:%lu !\n"
                       ,"ak_app_mem_ex_dma_pool_activate",0x113,local_3c,*piVar9,iVar8);
              if (*(uint *)(venc_str_max + iVar11) <= uVar7) goto LAB_000110f4;
            }
            piVar6 = piVar6 + 1;
          } while (uVar7 < *(uint *)(venc_str_max + iVar11));
        }
LAB_000110f4:
        if (*(int *)(venc_jpg_max + iVar11) != 0) {
          piVar6 = (int *)(venc_jpg_min + iVar11 + 4);
          piVar9 = (int *)(venc_jpg_max + iVar11);
          uVar7 = 0;
          do {
            while( true ) {
              piVar9 = piVar9 + 1;
              uVar7 = uVar7 + 1;
              if ((*piVar9 == 0) || (*piVar6 == 0)) break;
              uVar5 = ak_mem_dma_pool_create_reserved_obj(0xd);
              iVar8 = *piVar6;
              piVar6 = piVar6 + 1;
              uVar10 = uVar10 | uVar5;
              ak_print(0x1e,3,
                       "[%s:%d] ak_mem_dma_pool_create_reserved_obj venc_jpeg[%d] size:%lu, threshol d:%lu !\n"
                       ,"ak_app_mem_ex_dma_pool_activate",0x11e,local_3c,*piVar9,iVar8);
              if (*(uint *)(venc_jpg_max + iVar11) <= uVar7) goto LAB_00011194;
            }
            piVar6 = piVar6 + 1;
          } while (uVar7 < *(uint *)(venc_jpg_max + iVar11));
        }
LAB_00011194:
        iVar11 = iVar11 + 0x54;
        local_3c = local_3c + 1;
      } while (iVar11 != 0xa8);
      uVar3 = 0x103;
      ak_app_mem_init_flag = 1;
      if (uVar10 == 0) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = 0x103;
      ak_print(0x1e,1,"[%s:%d] ak_mem_dma_pool_activate failed!\n","ak_app_mem_ex_dma_pool_activate"
               ,0x103);
    }
  }
  else {
    ak_print(0x1e,1,"[%s:%d] ak_mem_dma_pool_create vi size:%d failed!\n",
             "ak_app_mem_ex_dma_pool_activate",0xd4,iVar8);
    uVar3 = 0x103;
  }
  return uVar3;
}


void ak_app_mem_ex_dma_pool_exit(void)

{
  ak_app_mem_init_flag = 0;
  ak_mem_dma_pool_exit();
  return;
}


undefined4 ak_app_mem_ex_dma_pool_set_venc_policy(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  uint local_84;
  undefined4 local_80;
  uint local_7c;
  uint local_78 [21];
  
  if (param_1 == (uint *)0x0) {
    ak_print(0x1e,1,"[%s:%d] policy is NULL!\n","ak_app_mem_ex_dma_pool_set_venc_policy",0x59);
    return 0x101;
  }
  if (*param_1 < 2) {
    uVar5 = param_1[3];
    if (2 < uVar5) {
      ak_print(0x1e,1,"[%s:%d] type %d error!\n","ak_app_mem_ex_dma_pool_set_venc_policy",0x65,uVar5
              );
      return 0x101;
    }
    if (ak_app_mem_init_flag != 1) {
      local_94 = 0;
      local_90 = 0;
      local_8c = 0;
      local_88 = 0;
      local_84 = 0;
      local_80 = 0;
      memset(&local_7c,0,0x54);
      if (uVar5 == 2) {
        local_94 = 0x2000001;
      }
      else if (uVar5 == 0) {
        local_94 = 0x100004d;
      }
      else {
        local_94 = 0x4000000;
      }
      local_84 = param_1[5];
      local_90 = 1;
      local_8c = CONCAT22((short)param_1[2],(short)param_1[1]);
      local_88 = CONCAT22((short)param_1[4],1);
      local_80 = CONCAT31(local_80._1_3_,(char)param_1[6]);
      AKV_Encoder_Get_Dma_Memory_Info(&local_94,&local_7c);
      uVar5 = param_1[3];
      if (uVar5 == 1) {
        uVar5 = *param_1;
        *(uint *)(venc_jpg_max + uVar5 * 0x54) = local_7c;
        *(uint *)(venc_jpg_min + uVar5 * 0x54) = local_7c;
        if (local_7c != 0) {
          puVar6 = &local_7c;
          uVar5 = 0;
          do {
            puVar6 = puVar6 + 1;
            ak_print(0x1e,6,"[%s:%d] JPEG[%d*%d] need DMA BUF[%d]size:[%lx]\n",
                     "ak_app_mem_ex_dma_pool_set_venc_policy",0x8b,param_1[1],param_1[2],uVar5,
                     *puVar6);
            uVar3 = *puVar6;
            iVar1 = (*param_1 * 0x15 + uVar5) * 4;
            if (*(uint *)(venc_jpg_max + iVar1 + 4) < uVar3) {
              *(uint *)(venc_jpg_max + iVar1 + 4) = uVar3;
            }
            uVar5 = uVar5 + 1;
            if ((uVar3 != 0) &&
               (uVar3 < *(uint *)(venc_jpg_min + iVar1 + 4) ||
                *(uint *)(venc_jpg_min + iVar1 + 4) == 0)) {
              *(uint *)(venc_jpg_min + iVar1 + 4) = uVar3;
            }
          } while (uVar5 < local_7c);
        }
      }
      else {
        uVar3 = *param_1;
        *(uint *)(venc_str_max + uVar3 * 0x54) = local_7c;
        *(uint *)(venc_str_min + uVar3 * 0x54) = local_7c;
        if (local_7c != 0) {
          puVar6 = &local_7c;
          uVar3 = 0;
          while( true ) {
            puVar4 = &DAT_0001139c;
            if (uVar5 != 0) {
              puVar4 = &DAT_000113a4;
            }
            puVar6 = puVar6 + 1;
            ak_print(0x1e,6,"[%s:%d] %s [%d*%d]need DMA BUF[%d]size:[%lx]\n",
                     "ak_app_mem_ex_dma_pool_set_venc_policy",0xa0,puVar4,param_1[1],param_1[2],
                     uVar3,*puVar6);
            uVar5 = *puVar6;
            iVar1 = (*param_1 * 0x15 + uVar3) * 4;
            if (*(uint *)(venc_str_max + iVar1 + 4) < uVar5) {
              *(uint *)(venc_str_max + iVar1 + 4) = uVar5;
            }
            uVar3 = uVar3 + 1;
            if ((uVar5 != 0) &&
               (uVar5 < *(uint *)(venc_str_min + iVar1 + 4) ||
                *(uint *)(venc_str_min + iVar1 + 4) == 0)) {
              *(uint *)(venc_str_min + iVar1 + 4) = uVar5;
            }
            if (local_7c <= uVar3) break;
            uVar5 = param_1[3];
          }
        }
      }
      return 0;
    }
    ak_print(0x1e,1,"[%s:%d] The policy should be set before app dma activate!\n",
             "ak_app_mem_ex_dma_pool_set_venc_policy",0x6c);
    uVar2 = 0x1e000000;
  }
  else {
    ak_print(0x1e,1,"[%s:%d] video_chn_id %d error!\n","ak_app_mem_ex_dma_pool_set_venc_policy",0x5f
             ,*param_1);
    uVar2 = 0x101;
  }
  return uVar2;
}


undefined4 ak_app_mem_ex_dma_pool_set_vi_policy(void *param_1)

{
  if (param_1 == (void *)0x0) {
    ak_print(0x1e,1,"[%s:%d] policy is NULL!\n","ak_app_mem_ex_dma_pool_set_vi_policy",0x34);
    return 0x101;
  }
  if (*(int *)((int)param_1 + 0x10) < 2) {
    ak_print(0x1e,1,"[%s:%d] main_frame_depth %d is error! \n",
             "ak_app_mem_ex_dma_pool_set_vi_policy",0x3b,*(int *)((int)param_1 + 0x10));
    return 0x101;
  }
  if (*(int *)((int)param_1 + 0x1c) < 2) {
    ak_print(0x1e,1,"[%s:%d] sub_frame_depth %d is error! \n","ak_app_mem_ex_dma_pool_set_vi_policy"
             ,0x41,*(int *)((int)param_1 + 0x1c));
    return 0x101;
  }
  if (ak_app_mem_init_flag != 1) {
    memcpy(g_vi_policy,param_1,0x30);
    return 0;
  }
  ak_print(0x1e,1,"[%s:%d] The policy should be set before app dma activate!\n",
           "ak_app_mem_ex_dma_pool_set_vi_policy",0x48);
  return 0x1e000000;
}


char * ak_app_mem_ex_get_version(void)

{
  return "libapp_mem_ex V1.0.00";
}

