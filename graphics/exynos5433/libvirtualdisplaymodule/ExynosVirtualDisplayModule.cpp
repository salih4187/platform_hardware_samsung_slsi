#include "ExynosVirtualDisplayModule.h"

ExynosVirtualDisplayModule::ExynosVirtualDisplayModule(struct exynos5_hwc_composer_device_1_t *pdev)
    : ExynosVirtualDisplay(pdev)
{
    mGLESFormat = HAL_PIXEL_FORMAT_RGBA_8888;
}

ExynosVirtualDisplayModule::~ExynosVirtualDisplayModule()
{
}

// TODO: Backport this from Prebuilt BSP

/*

ExynosVirtualDisplayModule::configureHandle
          (ExynosVirtualDisplayModule *this,private_handle_t *param_1,hwc_frect *param_2,
          hwc_rect *param_3,int param_4,int param_5,int param_6,s3c_fb_win_config *param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  int iVar9;

  iVar1 = *(int *)(param_3 + 0xc);
  iVar3 = *(int *)(param_3 + 4);
  iVar4 = *(int *)(param_3 + 8);
  iVar5 = *(int *)param_3;
  iVar2 = formatToBpp(*(int *)(param_1 + 0x28));
  iVar9 = *(int *)(param_1 + 0x34);
  fVar8 = *(float *)(param_2 + 4);
  fVar7 = *(float *)param_2;
  *(undefined4 *)param_7 = 2;
  *(undefined4 *)(param_7 + 4) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_7 + 0x20) = *(undefined4 *)param_3;
  uVar6 = *(undefined4 *)(param_3 + 4);
  *(int *)(param_7 + 0x28) = iVar4 - iVar5;
  *(int *)(param_7 + 0x2c) = iVar1 - iVar3;
  *(undefined4 *)(param_7 + 0x24) = uVar6;
  fVar7 = (fVar7 + (float)(longlong)iVar9 * fVar8) * (float)(longlong)iVar2 * 0.125;
  uVar6 = halFormatToS3CFormat(*(int *)(param_1 + 0x28));
  *(undefined4 *)(param_7 + 0x10) = uVar6;
  *(uint *)(param_7 + 8) = (uint)(0.0 < fVar7) * (int)fVar7;
  *(int *)(param_7 + 0xc) = (*(int *)(param_1 + 0x34) * iVar2) / 8;
  uVar6 = halBlendingToS3CBlending(param_4);
  *(undefined4 *)(param_7 + 0x14) = uVar6;
  *(int *)(param_7 + 0x18) = param_6;
  if ((param_5 != 0) && (param_5 < 0xff)) {
    *(int *)(param_7 + 0x1c) = param_5;
    return;
  }
  *(undefined4 *)(param_7 + 0x1c) = 0xff;
  return;
}

ExynosVirtualDisplayModule::isYuvLayer(ExynosVirtualDisplayModule *this,hwc_layer_1 *param_1)

{
  int iVar1;

  iVar1 = FUN_000131d8(*(undefined4 *)(param_1 + 0xc));
  if ((*(uint *)(iVar1 + 0x28) & 0xfffffffd) != 0x105) {
    return *(uint *)(iVar1 + 0x28) == 0x32315659;
  }
  return true;
}

ExynosVirtualDisplayModule::isLayerBetweenGLES
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1,uint param_2)

{
  hwc_display_contents_1 *phVar1;
  uint uVar2;
  uint uVar3;

  for (uVar3 = 0; uVar3 != param_2; uVar3 = uVar3 + 1) {
    if (*(int *)(param_1 + uVar3 * 100 + 0x14) == 0) {
      uVar3 = 1;
      goto LAB_00014988;
    }
  }
  uVar3 = 0;
LAB_00014988:
  phVar1 = param_1 + param_2 * 100;
  do {
    if (*(uint *)(param_1 + 0x10) <= param_2) {
      uVar2 = 0;
LAB_000149a8:
      return uVar3 & uVar2;
    }
    if (*(int *)(phVar1 + 0x14) == 0) {
      uVar2 = 1;
      goto LAB_000149a8;
    }
    param_2 = param_2 + 1;
    phVar1 = phVar1 + 100;
  } while( true );
}

int ExynosVirtualDisplayModule::isDeconExtWbSupported(hwc_layer_1 * __unused param_1,uint __unused param_2)

{
  uint uVar1;
  int in_r2;
  int iVar2;
  int iVar3;

  if ((*(uint *)(param_2 + 8) & 1) != 0) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    uVar1 = *(uint *)(iVar3 + 4) | 1;
    goto LAB_000140d6;
  }
  if (*(char *)(param_2 + 0x58) == '\0') {
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    uVar1 = *(uint *)(iVar3 + 4) | 2;
    goto LAB_00014224;
  }
  iVar3 = FUN_000131d8(*(undefined4 *)(param_2 + 0xc));
  if (iVar3 == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x1a8) != 0) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x80;
    return 0;
  }
  if (4 < *(int *)(iVar3 + 0x28) - 1U) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    uVar1 = *(uint *)(iVar3 + 4) | 0x40;
    goto LAB_00014224;
  }
  uVar1 = (uint)(*(float *)(param_2 + 0x20) - *(float *)(param_2 + 0x18));
  if ((uVar1 & 3) != 0) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    uVar1 = *(uint *)(iVar3 + 4) | 0x10;
    goto LAB_00014224;
  }
  if (((int)uVar1 < 0x20) ||
     (iVar3 = *(int *)(param_2 + 0x30) - *(int *)(param_2 + 0x28), iVar3 < 0x20)) {
LAB_00014228:
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
    uVar1 = *(uint *)(iVar3 + 4) | 0x10;
    goto LAB_000140d6;
  }
  iVar2 = *(int *)(param_1 + 300);
  if (iVar2 == 0) {
LAB_0001420e:
    iVar3 = isBlendingSupported(*(int *)(param_2 + 0x14));
    if (iVar3 == 0) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
      uVar1 = *(uint *)(iVar3 + 4) | 0x80;
LAB_00014224:
      *(uint *)(iVar3 + 4) = uVar1;
      return 0;
    }
    iVar2 = isOffscreen((hwc_layer_1 *)param_2,*(int *)(param_1 + 8),*(int *)(param_1 + 0xc));
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_2 + 0x10);
      return iVar3;
    }
    __android_log_print(5,"ExynosVirtualDisplayModule","\tlayer %u: off-screen");
  }
  else if (*(int *)(iVar2 + 0x10) == *(int *)(param_2 + 0x10)) {
    if (((double)(longlong)(int)(*(float *)(iVar2 + 0x20) - *(float *)(iVar2 + 0x18)) /
         (double)(longlong)(*(int *)(iVar2 + 0x30) - *(int *)(iVar2 + 0x28)) !=
         (double)(longlong)(int)uVar1 / (double)(longlong)iVar3) ||
       ((double)(longlong)(int)(*(float *)(iVar2 + 0x24) - *(float *)(iVar2 + 0x1c)) /
        (double)(longlong)(*(int *)(iVar2 + 0x34) - *(int *)(iVar2 + 0x2c)) !=
        (double)(longlong)(int)(*(float *)(param_2 + 0x24) - *(float *)(param_2 + 0x1c)) /
        (double)(longlong)(*(int *)(param_2 + 0x34) - *(int *)(param_2 + 0x2c)))) goto LAB_00014228;
    goto LAB_0001420e;
  }
  iVar3 = *(int *)(*(int *)(param_1 + 0x34) + in_r2 * 4);
  uVar1 = *(uint *)(iVar3 + 4) | 0x20;
LAB_000140d6:
  *(uint *)(iVar3 + 4) = uVar1;
  return 0;
}

ExynosVirtualDisplayModule::assignGscLayer
          (ExynosVirtualDisplayModule *this,hwc_layer_1 *param_1,int param_2,int param_3)

{
  *(undefined4 *)(this + param_3 * 8 + 0x178) = 1;
  ExynosMPP::setMode(*(int *)(this + 0x104));
  *(undefined4 *)(this + param_3 * 8 + 0x17c) = 2;
  return 1;
}

ExynosVirtualDisplayModule::determineSkipLayer
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  int iVar1;
  int iVar2;
  hwc_display_contents_1 *phVar3;
  uint uVar4;

  for (iVar2 = 0; iVar2 != *(int *)(param_1 + 0x10); iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + iVar2 * 100 + 0x1c) << 0x17 < 0) {
      this[0x59] = (ExynosVirtualDisplayModule)0x1;
      *(undefined4 *)(this + 0x128) = 0x10;
      break;
    }
  }
  iVar2 = *(int *)(param_1 + 0x10);
  phVar3 = param_1;
  for (iVar1 = 0; iVar1 != iVar2; iVar1 = iVar1 + 1) {
    if ((*(int *)(phVar3 + 0x14) != 3) && (this[0x59] != (ExynosVirtualDisplayModule)0x0)) {
      *(undefined4 *)(phVar3 + 0x14) = 1;
      *(undefined4 *)(phVar3 + 0x1c) = 0x80000000;
    }
    phVar3 = phVar3 + 100;
  }
  uVar4 = 0;
  this[0x34c] = this[0xfc];
  phVar3 = param_1;
  do {
    if (*(uint *)(param_1 + 0x10) <= uVar4) {
LAB_00014b54:
      if (0 < *(int *)(this + 0x128)) {
        *(int *)(this + 0x128) = *(int *)(this + 0x128) + -1;
        this[0x34c] = (ExynosVirtualDisplayModule)0x0;
      }
      if (this[0xfe] != (ExynosVirtualDisplayModule)0x0) {
        this[0x34c] = (ExynosVirtualDisplayModule)0x0;
        *(undefined4 *)(this + 0x128) = 0x10;
        this[0xfe] = (ExynosVirtualDisplayModule)0x0;
      }
      if (((this[0x34c] == (ExynosVirtualDisplayModule)0x0) || (0 < *(int *)(this + 0x128))) &&
         (this[0x59] == (ExynosVirtualDisplayModule)0x0)) {
        iVar1 = *(int *)(param_1 + 0x10);
        for (iVar2 = 0; iVar2 != iVar1; iVar2 = iVar2 + 1) {
          if ((((*(uint *)(param_1 + 0x1c) & 1) == 0) && (*(int *)(param_1 + 0x14) == 1)) &&
             (*(int *)(param_1 + 0x20) != 0)) {
            *(undefined4 *)(param_1 + 0x14) = 0;
          }
          param_1 = param_1 + 100;
        }
      }
      return;
    }
    if (*(int *)(phVar3 + 0x1c) << 0x1f < 0) {
      if (*(int *)(phVar3 + 0x20) == 0) {
        this[0x34c] = (ExynosVirtualDisplayModule)0x0;
        goto LAB_00014b54;
      }
      iVar2 = FUN_000131d8();
      getDrmMode(*(int *)(iVar2 + 0x1c));
    }
    uVar4 = uVar4 + 1;
    phVar3 = phVar3 + 100;
  } while( true );
}

ExynosVirtualDisplayModule::determineYuvOverlay(hwc_display_contents_1 *param_1)

{
  determineYuvOverlay(param_1);
  return;
}

ExynosVirtualDisplayModule::setSinkBufferUsage(ExynosVirtualDisplayModule *this)

{
  undefined4 uVar1;

  *(undefined4 *)(this + 0xac) = 0x800;
  if (this[0x5a] == (ExynosVirtualDisplayModule)0x0) {
    if (this[0x5b] == (ExynosVirtualDisplayModule)0x0) {
      return;
    }
    uVar1 = 0x2000800;
  }
  else {
    uVar1 = 0x1004800;
  }
  *(undefined4 *)(this + 0xac) = uVar1;
  return;
}

ExynosVirtualDisplayModule::determineSupportedOverlays
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  determineSupportedOverlays(this,param_1);
  return;
}

ExynosVirtualDisplayModule::assignWindows
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  assignWindows(this,param_1);
  return;
}

ExynosVirtualDisplayModule::calculateOverlapRect
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  calculateOverlapRect(this,param_1);
  return;
}

ExynosVirtualDisplayModule::postGscM2M
          (ExynosVirtualDisplayModule *this,hwc_layer_1 *param_1,hwc_frect *param_2,
          s3c_fb_win_config *param_3,int param_4,int param_5)

{
  postGscM2M(this,param_1,param_2,param_3,param_4,param_5);
  return;
}

ExynosVirtualDisplayModule::configureOverlay
          (ExynosVirtualDisplayModule *this,hwc_layer_1 *param_1,s3c_fb_win_config *param_2)

{
  configureOverlay(this,param_1,param_2);
  return;
}

ExynosVirtualDisplayModule::configureOverlay
          (ExynosVirtualDisplayModule *this,hwc_layer_1 *param_1,hwc_frect *param_2,
          s3c_fb_win_config *param_3)

{
  configureOverlay(this,param_1,param_2,param_3);
  return;
}

ExynosVirtualDisplayModule::handleStaticLayers
               (hwc_display_contents_1 *param_1,s3c_fb_win_config_data *param_2,int param_3)

{
  handleStaticLayers(param_1,param_2,param_3);
  return;
}

ExynosVirtualDisplayModule::cleanupGscs(ExynosVirtualDisplayModule *this)

{
  cleanupGscs(this);
  return;
}

ExynosVirtualDisplayModule::clearOutBuf
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  clearOutBuf(this,param_1);
  return;
}

ExynosVirtualDisplayModule::postFrame
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  postFrame(this,param_1);
  return;
}

ExynosVirtualDisplayModule::clearDisplay(ExynosVirtualDisplayModule *this)

{
  clearDisplay(this);
  return;
}

ExynosVirtualDisplayModule::processHwc
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  processHwc(this,param_1);
  return;
}

ExynosVirtualDisplayModule::processGles
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  processGles(this,param_1);
  return;
}

ExynosVirtualDisplayModule::processMixed
          (ExynosVirtualDisplayModule *this,hwc_display_contents_1 *param_1)

{
  processMixed(this,param_1);
  return;
}


int ExynosVirtualDisplayModule::openDeconExt(void)

{
  int in_r0;
  int iVar1;

  if (*(int *)(in_r0 + 4) < 0) {
    iVar1 = open("/dev/graphics/fb1",2);
    *(int *)(in_r0 + 4) = iVar1;
    if (iVar1 < 0) {
      __android_log_print(6,"ExynosVirtualDisplayModule",
                          "failed to open framebuffer for VirtualDisplay");
    }
    *(undefined4 *)(in_r0 + 0x128) = 0x10;
  }
  iVar1 = 0;
  *(undefined1 *)(in_r0 + 0x59) = 0;
  if (((*(int **)(in_r0 + 0x100))[4] == 0) &&
     (iVar1 = (**(code **)(**(int **)(in_r0 + 0x100) + 0x84))(), iVar1 < 0)) {
    __android_log_print(6,"ExynosVirtualDisplayModule",
                        "GSC WB for VirtualDisplay open failed, frame will be skipped");
    *(undefined1 *)(in_r0 + 0x59) = 1;
    *(undefined4 *)(in_r0 + 0x128) = 0x10;
  }
  return iVar1;
}

ExynosVirtualDisplayModule::closeDeconExt(ExynosVirtualDisplayModule *this)

{
  if (0 < *(int *)(this + 4)) {
    *(undefined4 *)
     (*(int *)(this + 0x100) + (*(int *)(*(int *)(this + 0x100) + 300) + 0x3e) * 4 + 4) = 0;
    *(undefined4 *)(*(int *)(this + 0x100) + *(int *)(*(int *)(this + 0x100) + 300) * 4 + 0x114) =
         0xffffffff;
    (**(code **)(**(int **)(this + 0x100) + 0x88))();
    (**(code **)(*(int *)this + 0x40))(this);
    (**(code **)(**(int **)(this + 0x100) + 0x94))();
    close(*(int *)(this + 4));
    *(undefined4 *)(this + 4) = 0xffffffff;
    this[0xfe] = (ExynosVirtualDisplayModule)0x1;

    (**(code **)(**(int **)(this + 0x104) + 0x28))();
    return;
  }
  return;
*/

void ExynosVirtualDisplayModule::init(hwc_display_contents_1_t __unused *virtual_contents)

{
  /*int iVar1;
  int in_r0;

  if (*(int *)(in_r0 + 4) < 0) {
    iVar1 = open("/dev/graphics/fb1",2);
    *(int *)(in_r0 + 4) = iVar1;
    if (iVar1 < 0) {
      __android_log_print(6,"ExynosVirtualDisplayModule",
                          "failed to open framebuffer for VirtualDisplay");
    }
    *(undefined4 *)(in_r0 + 0x128) = 0x10;
  }
  iVar1 = 0;
  *(undefined1 *)(in_r0 + 0x59) = 0;
  if (((*(int **)(in_r0 + 0x100))[4] == 0) &&
     (iVar1 = (**(code **)(**(int **)(in_r0 + 0x100) + 0x84))(), iVar1 < 0)) {
    __android_log_print(6,"ExynosVirtualDisplayModule",
                        "GSC WB for VirtualDisplay open failed, frame will be skipped");
    *(undefined1 *)(in_r0 + 0x59) = 1;
    *(undefined4 *)(in_r0 + 0x128) = 0x10;
  }
  return iVar1;
  */
}

/*
ExynosVirtualDisplayModule::deInit(ExynosVirtualDisplayModule *this)

{
  int *piVar1;
  int iVar2;

  piVar1 = *(int **)(this + 0x104);
  iVar2 = piVar1[0x4b];
  piVar1[iVar2 + 0x3f] = 0;
  piVar1[iVar2 + 0x45] = -1;
  (**(code **)(*piVar1 + 0x28))();
  ExynosG2DWrapper::TerminateSecureG2D();
  (**(code **)(*(int *)this + 0x3c))(this);
  *(undefined4 *)(this + 0xa4) = 1;
  closeDeconExt(this);
  return;
}

ExynosVirtualDisplayModule::setWFDOutputResolution(unsigned int width, unsigned int height,
        unsigned int disp_w, unsigned int disp_h)
{
    mDisplayWidth = disp_w;
    mWidth = width;
    mHeight = height;
    mXres = width;
    mDisplayHeight = disp_h;
    mYres = height;
}

*/

void ExynosVirtualDisplayModule::setPriContents(hwc_display_contents_1_t __unused *contents)
{
}

int32_t ExynosVirtualDisplayModule::getDisplayAttributes(const uint32_t attribute, uint32_t config __unused)
{
    switch(attribute) {
        case HWC_DISPLAY_COMPOSITION_TYPE:
            return mCompositionType;
        case HWC_DISPLAY_GLES_FORMAT:
            return mGLESFormat;
        case HWC_DISPLAY_SINK_BQ_FORMAT:
            return HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M;
        case HWC_DISPLAY_SINK_BQ_USAGE:
            return mSinkUsage;
        case HWC_DISPLAY_SINK_BQ_WIDTH:
            if (mDisplayWidth == 0)
                return mWidth;
            return mDisplayWidth;
        case HWC_DISPLAY_SINK_BQ_HEIGHT:
            if (mDisplayHeight == 0)
                return mHeight;
            return mDisplayHeight;
        default:
            ALOGE("unknown display attribute %u", attribute);
            return -EINVAL;
    }
    return 0;
}
