/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/utils/system_properties.h"

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unistd.h>

#include "parameter.h"
#include "parameters.h"

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "systemcapability.h"
#endif

namespace OHOS::Ace {
namespace {
constexpr char PROPERTY_DEVICE_TYPE[] = "const.product.devicetype";
constexpr char PROPERTY_DEVICE_TYPE_DEFAULT[] = "default";
constexpr char PROPERTY_DEVICE_TYPE_TV[] = "tv";
constexpr char PROPERTY_DEVICE_TYPE_TABLET[] = "tablet";
constexpr char PROPERTY_DEVICE_TYPE_TWOINONE[] = "2in1";
constexpr char PROPERTY_DEVICE_TYPE_WATCH[] = "watch";
constexpr char PROPERTY_DEVICE_TYPE_CAR[] = "car";
constexpr char ENABLE_DEBUG_BOUNDARY_KEY[] = "persist.ace.debug.boundary.enabled";
constexpr char ANIMATION_SCALE_KEY[] = "persist.sys.arkui.animationscale";
constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
constexpr float DEFAULT_ANIMATION_SCALE = 1.0f;
float animationScale_ = DEFAULT_ANIMATION_SCALE;
std::shared_mutex mutex_;
#ifdef ENABLE_ROSEN_BACKEND
constexpr char DISABLE_ROSEN_FILE_PATH[] = "/etc/disablerosen";
constexpr char DISABLE_WINDOW_ANIMATION_PATH[] = "/etc/disable_window_size_animation";
#endif

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}

bool IsDebugBoundaryEnabled()
{
    return system::GetParameter(ENABLE_DEBUG_BOUNDARY_KEY, "false") == "true";
}

bool IsTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.enabled", "0") == "1" ||
            system::GetParameter("debug.ace.trace.enabled", "0") == "1");
}

bool IsSvgTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.svg.enabled", "0") == "1");
}

bool IsHookModeEnabled()
{
#ifdef PREVIEW
    return false;
#endif
    const int bufferLen = 128;
    char paramOutBuf[bufferLen] = { 0 };
    constexpr char hook_mode[] = "startup:";
    int ret = GetParameter("persist.libc.hook_mode", "", paramOutBuf, bufferLen);
    if (ret <= 0 || strncmp(paramOutBuf, hook_mode, strlen(hook_mode)) != 0) {
        return false;
    }
    return true;
}

bool IsRosenBackendEnabled()
{
#ifdef PREVIEW
    return false;
#endif
#ifdef ENABLE_ROSEN_BACKEND
    if (system::GetParameter("persist.ace.rosen.backend.enabled", "0") == "1") {
        return true;
    }
    if (system::GetParameter("persist.ace.rosen.backend.enabled", "0") == "2") {
        return false;
    }
    if (access(DISABLE_ROSEN_FILE_PATH, F_OK) == 0) {
        return false;
    }
    return true;
#else
    return false;
#endif
}

bool IsWindowAnimationEnabled()
{
#ifdef PREVIEW
    return false;
#endif
#ifdef ENABLE_ROSEN_BACKEND
    if (access(DISABLE_WINDOW_ANIMATION_PATH, F_OK) == 0) {
        return false;
    }
    return true;
#else
    return false;
#endif
}

bool IsAccessibilityEnabled()
{
    return (system::GetParameter("persist.ace.testmode.enabled", "0") == "1" ||
            system::GetParameter("debug.ace.testmode.enabled", "0") == "1");
}

bool IsDebugEnabled()
{
    return (system::GetParameter("persist.ace.debug.enabled", "0") == "1");
}

bool IsGpuUploadEnabled()
{
    return (system::GetParameter("persist.ace.gpuupload.enabled", "0") == "1" ||
            system::GetParameter("debug.ace.gpuupload.enabled", "0") == "1");
}

void OnAnimationScaleChanged(const char* key, const char* value, void* context)
{
    CHECK_NULL_VOID(key);
    if (strcmp(key, ANIMATION_SCALE_KEY) != 0) {
        LOGE("AnimationScale key not matched. key: %{public}s", key);
        return;
    }
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (value == nullptr) {
        LOGW("AnimationScale changes with null value, use default. key: %{public}s", key);
        animationScale_ = DEFAULT_ANIMATION_SCALE;
        return;
    }
    auto animationScale = std::atof(value);
    if (animationScale < 0.0f) {
        LOGE("AnimationScale changes with invalid value: %{public}s. ignore", value);
        return;
    }
    LOGI("AnimationScale: %{public}f -> %{public}f", animationScale_, animationScale);
    animationScale_ = animationScale;
}

uint32_t GetSysDumpFrameCount()
{
    return system::GetUintParameter<uint32_t>("persist.ace.framedumpcount", 10);
}

bool GetAstcEnabled()
{
    return system::GetParameter("persist.astc.enable", "true") == "true";
}

int32_t GetAstcMaxErrorProp()
{
    return system::GetIntParameter<int>("persist.astc.max", 50000);
}

int32_t GetAstcPsnrProp()
{
    return system::GetIntParameter<int>("persist.astc.psnr", 0);
}

bool IsUseMemoryMonitor()
{
    return (system::GetParameter("persist.ace.memorymonitor.enabled", "0") == "1");
}

bool IsExtSurfaceEnabled()
{
#ifdef EXT_SURFACE_ENABLE
    return true;
#else
    return false;
#endif
}
} // namespace

bool SystemProperties::traceEnabled_ = IsTraceEnabled();
bool SystemProperties::svgTraceEnable_ = IsSvgTraceEnabled();
bool SystemProperties::accessibilityEnabled_ = IsAccessibilityEnabled();
bool SystemProperties::isRound_ = false;
bool SystemProperties::isDeviceAccess_ = false;
int32_t SystemProperties::deviceWidth_ = 0;
int32_t SystemProperties::deviceHeight_ = 0;
int32_t SystemProperties::devicePhysicalWidth_ = 0;
int32_t SystemProperties::devicePhysicalHeight_ = 0;
ACE_WEAK_SYM double SystemProperties::resolution_ = 1.0;
ACE_WEAK_SYM DeviceType SystemProperties::deviceType_ { DeviceType::UNKNOWN };
ACE_WEAK_SYM DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
std::string SystemProperties::brand_ = INVALID_PARAM;
std::string SystemProperties::manufacturer_ = INVALID_PARAM;
std::string SystemProperties::model_ = INVALID_PARAM;
std::string SystemProperties::product_ = INVALID_PARAM;
std::string SystemProperties::apiVersion_ = INVALID_PARAM;
std::string SystemProperties::releaseType_ = INVALID_PARAM;
std::string SystemProperties::paramDeviceType_ = INVALID_PARAM;
int32_t SystemProperties::mcc_ = MCC_UNDEFINED;
int32_t SystemProperties::mnc_ = MNC_UNDEFINED;
ACE_WEAK_SYM ColorMode SystemProperties::colorMode_ { ColorMode::LIGHT };
ScreenShape SystemProperties::screenShape_ { ScreenShape::NOT_ROUND };
LongScreenType SystemProperties::LongScreen_ { LongScreenType::NOT_LONG };
bool SystemProperties::unZipHap_ = true;
ACE_WEAK_SYM bool SystemProperties::rosenBackendEnabled_ = IsRosenBackendEnabled();
ACE_WEAK_SYM bool SystemProperties::isHookModeEnabled_ = IsHookModeEnabled();
bool SystemProperties::debugBoundaryEnabled_ = IsDebugBoundaryEnabled();
ACE_WEAK_SYM bool SystemProperties::windowAnimationEnabled_ = IsWindowAnimationEnabled();
bool SystemProperties::debugEnabled_ = IsDebugEnabled();
bool SystemProperties::gpuUploadEnabled_ = IsGpuUploadEnabled();
bool SystemProperties::astcEnabled_ = GetAstcEnabled();
int32_t SystemProperties::astcMax_ = GetAstcMaxErrorProp();
int32_t SystemProperties::astcPsnr_ = GetAstcPsnrProp();
ACE_WEAK_SYM bool SystemProperties::extSurfaceEnabled_ = IsExtSurfaceEnabled();
ACE_WEAK_SYM uint32_t SystemProperties::dumpFrameCount_ = GetSysDumpFrameCount();
bool SystemProperties::resourceDecoupling_ = GetResourceDecoupling();

bool SystemProperties::IsSyscapExist(const char* cap)
{
#ifdef OHOS_STANDARD_SYSTEM
    return HasSystemCapability(cap);
#else
    return false;
#endif
}

void SystemProperties::InitDeviceType(DeviceType)
{
    // Do nothing, no need to store type here, use system property at 'GetDeviceType' instead.
}

int SystemProperties::GetArkProperties()
{
    return system::GetIntParameter<int>("persist.ark.properties", -1);
}

std::string SystemProperties::GetArkBundleName()
{
    return system::GetParameter("persist.ark.arkbundlename", "");
}

size_t SystemProperties::GetGcThreadNum()
{
    size_t defaultGcThreadNums = 7;
    return system::GetUintParameter<size_t>("persist.ark.gcthreads", defaultGcThreadNums);
}

size_t SystemProperties::GetLongPauseTime()
{
    size_t defaultLongPauseTime = 40; // 40ms
    return system::GetUintParameter<size_t>("persist.ark.longpausetime", defaultLongPauseTime);
}

bool SystemProperties::GetAsmInterpreterEnabled()
{
    return system::GetParameter("persist.ark.asminterpreter", "true") == "true";
}

std::string SystemProperties::GetAsmOpcodeDisableRange()
{
    return system::GetParameter("persist.ark.asmopcodedisablerange", "");
}

bool SystemProperties::IsScoringEnabled(const std::string& name)
{
    if (name.empty()) {
        return false;
    }
    std::string filePath = "/etc/" + name;
    if (access(filePath.c_str(), F_OK) == 0) {
        return true;
    }
    std::string prop = system::GetParameter("persist.ace.trace.scoringtool", "");
    return prop == name;
}

ACE_WEAK_SYM DeviceType SystemProperties::GetDeviceType()
{
    InitDeviceTypeBySystemProperty();
    return deviceType_;
}

void SystemProperties::InitDeviceTypeBySystemProperty()
{
    if (deviceType_ != DeviceType::UNKNOWN) {
        return;
    }

    auto deviceProp = system::GetParameter(PROPERTY_DEVICE_TYPE, PROPERTY_DEVICE_TYPE_DEFAULT);
    // Properties: "default", "tv", "tablet", "watch", "car"
    LOGD("GetDeviceType, deviceProp=%{private}s.", deviceProp.c_str());
    if (deviceProp == PROPERTY_DEVICE_TYPE_TV) {
        deviceType_ = DeviceType::TV;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_CAR) {
        deviceType_ = DeviceType::CAR;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WATCH) {
        deviceType_ = DeviceType::WATCH;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TABLET) {
        deviceType_ = DeviceType::TABLET;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TWOINONE) {
        deviceType_ = DeviceType::TWO_IN_ONE;
    } else {
        deviceType_ = DeviceType::PHONE;
    }
}

void SystemProperties::InitDeviceInfo(
    int32_t deviceWidth, int32_t deviceHeight, int32_t orientation, double resolution, bool isRound)
{
    // SetDeviceOrientation should be earlier than deviceWidth/deviceHeight init.
    SetDeviceOrientation(orientation);

    isRound_ = isRound;
    resolution_ = resolution;
    deviceWidth_ = deviceWidth;
    deviceHeight_ = deviceHeight;
    brand_ = ::GetBrand();
    manufacturer_ = ::GetManufacture();
    model_ = ::GetProductModel();
    product_ = ::GetMarketName();
    apiVersion_ = std::to_string(::GetSdkApiVersion());
    releaseType_ = ::GetOsReleaseType();
    paramDeviceType_ = ::GetDeviceType();

    debugEnabled_ = IsDebugEnabled();
    traceEnabled_ = IsTraceEnabled();
    svgTraceEnable_ = IsSvgTraceEnabled();
    accessibilityEnabled_ = IsAccessibilityEnabled();
    rosenBackendEnabled_ = IsRosenBackendEnabled();
    isHookModeEnabled_ = IsHookModeEnabled();
    debugBoundaryEnabled_ = system::GetParameter(ENABLE_DEBUG_BOUNDARY_KEY, "false") == "true";
    animationScale_ = std::atof(system::GetParameter(ANIMATION_SCALE_KEY, "1").c_str());
    WatchParameter(ANIMATION_SCALE_KEY, OnAnimationScaleChanged, nullptr);
    resourceDecoupling_ = GetResourceDecoupling();

    if (isRound_) {
        screenShape_ = ScreenShape::ROUND;
    } else {
        screenShape_ = ScreenShape::NOT_ROUND;
    }

    InitDeviceTypeBySystemProperty();
}

void SystemProperties::SetDeviceOrientation(int32_t orientation)
{
    if (orientation == ORIENTATION_PORTRAIT && orientation_ != DeviceOrientation::PORTRAIT) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::PORTRAIT;
    } else if (orientation == ORIENTATION_LANDSCAPE && orientation_ != DeviceOrientation::LANDSCAPE) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::LANDSCAPE;
    }
}

ACE_WEAK_SYM float SystemProperties::GetFontWeightScale()
{
    // Default value of font weight scale is 1.0.
    std::string prop =
        "persist.sys.font_wght_scale_for_user" + std::to_string(AceApplicationInfo::GetInstance().GetUserId());
    return std::stof(system::GetParameter(prop, "1.0"));
}

void SystemProperties::InitMccMnc(int32_t mcc, int32_t mnc)
{
    mcc_ = mcc;
    mnc_ = mnc;
}

ACE_WEAK_SYM bool SystemProperties::GetDebugEnabled()
{
    return debugEnabled_;
}

std::string SystemProperties::GetLanguage()
{
    return system::GetParameter("const.global.language", INVALID_PARAM);
}

std::string SystemProperties::GetRegion()
{
    return system::GetParameter("const.global.region", INVALID_PARAM);
}

std::string SystemProperties::GetNewPipePkg()
{
    return system::GetParameter("persist.ace.newpipe.pkgname", "");
}

ACE_WEAK_SYM float SystemProperties::GetAnimationScale()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return animationScale_;
}

std::string SystemProperties::GetPartialUpdatePkg()
{
    return system::GetParameter("persist.ace.partial.pkgname", "");
}

int32_t SystemProperties::GetSvgMode()
{
#ifdef NG_BUILD
    // disable ace svg before updated to new pipeline
    return system::GetIntParameter<int>("persist.ace.svg.mode", 0);
#else
    return system::GetIntParameter<int>("persist.ace.svg.mode", 1);
#endif
}

bool SystemProperties::GetAllowWindowOpenMethodEnabled()
{
    return system::GetBoolParameter("persist.web.allowWindowOpenMethod.enabled", false);
}

bool SystemProperties::GetImageFrameworkEnabled()
{
    return system::GetBoolParameter("persist.ace.image.framework.enabled", true);
}

ACE_WEAK_SYM bool SystemProperties::GetIsUseMemoryMonitor()
{
    static bool isUseMemoryMonitor = IsUseMemoryMonitor();
    return isUseMemoryMonitor;
}

bool SystemProperties::IsFormAnimationLimited()
{
    return system::GetBoolParameter("persist.sys.arkui.formAnimationLimit", true);
}

bool SystemProperties::GetResourceDecoupling()
{
    return system::GetBoolParameter("resource.decoupling", true);
}
} // namespace OHOS::Ace
