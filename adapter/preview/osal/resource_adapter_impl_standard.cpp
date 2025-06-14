/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "adapter/preview/osal/resource_adapter_impl_standard.h"

#include "adapter/preview/entrance/ace_container.h"
#include "adapter/ohos/osal/resource_theme_style.h"
#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/osal/resource_convertor.h"
#include "base/log/log.h"
#include "core/common/container.h"
#include "core/components/theme/theme_attributes.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/simulator/ability_simulator/include/ability_context.h"

namespace OHOS::Ace {

namespace {
#ifdef WINDOWS_PLATFORM
constexpr char DELIMITER[] = "\\";
#else
constexpr char DELIMITER[] = "/";
#endif

constexpr uint32_t OHOS_THEME_ID = 125829872; // ohos_theme

void CheckThemeId(int32_t& themeId)
{
    if (themeId >= 0) {
        return;
    }
    themeId = OHOS_THEME_ID;
}

const char* PATTERN_MAP[] = {
    THEME_PATTERN_BUTTON,
    THEME_PATTERN_CHECKBOX,
    THEME_PATTERN_DATA_PANEL,
    THEME_PATTERN_RADIO,
    THEME_PATTERN_SWIPER,
    THEME_PATTERN_SWITCH,
    THEME_PATTERN_TOOLBAR,
    THEME_PATTERN_TOGGLE,
    THEME_PATTERN_TOAST,
    THEME_PATTERN_DIALOG,
    THEME_PATTERN_DRAG_BAR,
    THEME_PATTERN_CLOSE_ICON,
    THEME_PATTERN_SEMI_MODAL,
    // append
    THEME_PATTERN_BADGE,
    THEME_PATTERN_CALENDAR,
    THEME_PATTERN_CAMERA,
    THEME_PATTERN_CARD,
    THEME_PATTERN_CLOCK,
    THEME_PATTERN_COUNTER,
    THEME_PATTERN_DIVIDER,
    THEME_PATTERN_FOCUS_ANIMATION,
    THEME_PATTERN_GRID,
    THEME_PATTERN_IMAGE,
    THEME_PATTERN_LIST,
    THEME_PATTERN_LIST_ITEM,
    THEME_PATTERN_ARC_LIST,
    THEME_PATTERN_ARC_LIST_ITEM,
    THEME_PATTERN_MARQUEE,
    THEME_PATTERN_NAVIGATION_BAR,
    THEME_PATTERN_PICKER,
    THEME_PATTERN_PIECE,
    THEME_PATTERN_POPUP,
    THEME_PATTERN_PROGRESS,
    THEME_PATTERN_QRCODE,
    THEME_PATTERN_RATING,
    THEME_PATTERN_REFRESH,
    THEME_PATTERN_SCROLL_BAR,
    THEME_PATTERN_SEARCH,
    THEME_PATTERN_SELECT,
    THEME_PATTERN_SLIDER,
    THEME_PATTERN_STEPPER,
    THEME_PATTERN_TAB,
    THEME_PATTERN_TEXT,
    THEME_PATTERN_TEXTFIELD,
    THEME_PATTERN_TEXT_OVERLAY,
    THEME_PATTERN_VIDEO,
    THEME_PATTERN_ICON,
    THEME_PATTERN_INDEXER,
    THEME_PATTERN_APP_BAR,
    THEME_PATTERN_SECURITY_COMPONENT,
    THEME_PATTERN_SIDE_BAR,
    THEME_PATTERN_PATTERN_LOCK,
    THEME_PATTERN_HYPERLINK,
    THEME_PATTERN_GAUGE,
    THEME_PATTERN_SHEET,
    THEME_BLUR_STYLE_COMMON,
    THEME_PATTERN_SHADOW,
    THEME_PATTERN_RICH_EDITOR,
    THEME_PATTERN_CONTAINER_MODAL,
    THEME_PATTERN_APP,
    THEME_PATTERN_LINEAR_INDICATOR
};
} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::Create()
{
    return AceType::MakeRefPtr<ResourceAdapterImpl>();
}

DimensionUnit ParseDimensionUnit(const std::string& unit)
{
    if (unit == "px") {
        return DimensionUnit::PX;
    } else if (unit == "fp") {
        return DimensionUnit::FP;
    } else if (unit == "lpx") {
        return DimensionUnit::LPX;
    } else if (unit == "%") {
        return DimensionUnit::PERCENT;
    } else {
        return DimensionUnit::VP;
    }
}

ResourceAdapterImpl::ResourceAdapterImpl(std::shared_ptr<Global::Resource::ResourceManager> resourceManager)
{
    resourceManager_ = resourceManager;
}

void ResourceAdapterImpl::Init(const ResourceInfo& resourceInfo)
{
    std::string appResPath = resourceInfo.GetPackagePath();
    std::string sysResPath = resourceInfo.GetSystemPackagePath();
    std::string hmsResPath = resourceInfo.GetHmsPackagePath();
    auto resConfig = ConvertConfigToGlobal(resourceInfo.GetResourceConfiguration());
    std::shared_ptr<Global::Resource::ResourceManager> newResMgr(Global::Resource::CreateResourceManager());

    std::string appResIndexPath = appResPath + DELIMITER + "resources.index";
    auto appResRet = newResMgr->AddResource(appResIndexPath.c_str());
    std::string sysResIndexPath = sysResPath + DELIMITER + "resources.index";
    auto sysResRet = newResMgr->AddResource(sysResIndexPath.c_str());
    if (!hmsResPath.empty()) {
        std::string hmsResIndexPath =
            hmsResPath + DELIMITER + "resources" + DELIMITER + "resources" + DELIMITER + "resources.index";
        newResMgr->AddResource(hmsResIndexPath.c_str());
    }

    if (resConfig != nullptr) {
        auto configRet = newResMgr->UpdateResConfig(*resConfig);
        LOGI("AddAppRes result=%{public}d, AddSysRes result=%{public}d,  UpdateResConfig result=%{public}d, "
             "ori=%{public}d, dpi=%{public}f, device=%{public}d",
            appResRet, sysResRet, configRet, resConfig->GetDirection(), resConfig->GetScreenDensity(),
            resConfig->GetDeviceType());
    }

    Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(newResMgr);
    resourceManager_ = newResMgr;
    packagePathStr_ = appResPath;
}

void ResourceAdapterImpl::SetAppHasDarkRes(bool hasDarkRes)
{
    appHasDarkRes_ = hasDarkRes;
}

RefPtr<ResourceAdapter> ResourceAdapter::CreateNewResourceAdapter(
    const std::string& bundleName, const std::string& moduleName, bool fromTheme)
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, nullptr);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, nullptr);
    
    RefPtr<ResourceAdapter> newResourceAdapter = nullptr;
    auto context = aceContainer->GetAbilityContextByModule(bundleName, moduleName);
    if (context) {
        auto resourceManager = context->GetResourceManager();
        auto resourceAdapterImpl = AceType::MakeRefPtr<ResourceAdapterImpl>(resourceManager);
        resourceAdapterImpl->SetAppHasDarkRes(aceContainer->GetResourceConfiguration().GetAppHasDarkRes());
        newResourceAdapter = resourceAdapterImpl;
    } else {
        newResourceAdapter = ResourceAdapter::Create();
        auto resourceInfo = aceContainer->GetResourceInfo();
        newResourceAdapter->Init(resourceInfo);
    }

    auto resConfig = aceContainer->GetResourceConfiguration();
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->GetLocalColorMode() != ColorMode::COLOR_MODE_UNDEFINED) {
        auto localColorMode = pipelineContext->GetLocalColorMode();
        resConfig.SetColorMode(localColorMode);
    }
    newResourceAdapter->UpdateConfig(resConfig);

    return newResourceAdapter;
}

void ResourceAdapterImpl::UpdateConfig(const ResourceConfiguration& config, bool themeFlag)
{
    auto resConfig = ConvertConfigToGlobal(config);
    LOGI("UpdateConfig ori=%{public}d, dpi=%{public}f, device=%{public}d", resConfig->GetDirection(),
        resConfig->GetScreenDensity(), resConfig->GetDeviceType());
    if (resConfig != nullptr) {
        resourceManager_->UpdateResConfig(*resConfig);
    }
}

RefPtr<ThemeStyle> ResourceAdapterImpl::GetTheme(int32_t themeId)
{
    CheckThemeId(themeId);
    auto theme = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    constexpr char OHFlag[] = "ohos_"; // fit with resource/base/theme.json and pattern.json
    if (resourceManager_) {
        auto ret = resourceManager_->GetThemeById(themeId, theme->rawAttrs_);
        for (size_t i = 0; i < sizeof(PATTERN_MAP) / sizeof(PATTERN_MAP[0]); i++) {
            ResourceThemeStyle::RawAttrMap attrMap;
            std::string patternTag = PATTERN_MAP[i];
            std::string patternName = std::string(OHFlag) + PATTERN_MAP[i];
            ret = resourceManager_->GetPatternByName(patternName.c_str(), attrMap);
            if (attrMap.empty()) {
                continue;
            }
            theme->patternAttrs_[patternTag] = attrMap;
        }
        LOGI("themeId=%{public}d, ret=%{public}d, attr size=%{public}zu, pattern size=%{public}zu", themeId, ret,
            theme->rawAttrs_.size(), theme->patternAttrs_.size());
    }

    if (theme->patternAttrs_.empty() && theme->rawAttrs_.empty()) {
        LOGW("theme resource get failed, use default theme config.");
        return nullptr;
    }

    theme->ParseContent();
    theme->patternAttrs_.clear();
    return theme;
};

Color ResourceAdapterImpl::GetColor(uint32_t resId)
{
    uint32_t result = 0;
    if (resourceManager_) {
        auto state = resourceManager_->GetColorById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetColor error, id=%{public}u", resId);
        }
    }
    return Color(result);
}

Color ResourceAdapterImpl::GetColorByName(const std::string& resName)
{
    uint32_t result = 0;
    if (resourceManager_) {
        auto index = resName.find_last_of('.');
        auto actualResName = resName.substr(index + 1, resName.length() - index - 1);
        auto state = resourceManager_->GetColorByName(actualResName.c_str(), result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetColorByName error, name=%{public}s", resName.c_str());
        }
    }
    return Color(result);
}

Dimension ResourceAdapterImpl::GetDimension(uint32_t resId)
{
    float dimensionFloat = 0.0f;
    std::string unit = "";
    if (resourceManager_) {
        auto state = resourceManager_->GetFloatById(resId, dimensionFloat, unit);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetDimension error, id=%{public}u", resId);
        }
    }
    return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
}

Dimension ResourceAdapterImpl::GetDimensionByName(const std::string& resName)
{
    float dimensionFloat = 0.0f;
    std::string unit = "";
    if (resourceManager_) {
        auto index = resName.find_last_of('.');
        auto actualResName = resName.substr(index + 1, resName.length() - index - 1);
        auto state = resourceManager_->GetFloatByName(actualResName.c_str(), dimensionFloat, unit);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetDimensionByName error, name=%{public}s", resName.c_str());
        }
    }
    return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
}

std::string ResourceAdapterImpl::GetString(uint32_t resId)
{
    std::string strResult = "";
    if (resourceManager_) {
        auto state = resourceManager_->GetStringById(resId, strResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetString error, id=%{public}u", resId);
        }
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetStringByName(const std::string& resName)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetStringByName(actualResName.c_str(), strResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get string by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetPluralString(uint32_t resId, int quantity)
{
    std::string strResult = "";
    if (resourceManager_) {
        auto state = resourceManager_->GetPluralStringById(resId, quantity, strResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetPluralString error, id=%{public}u", resId);
        }
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetPluralStringByName(const std::string& resName, int quantity)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetPluralStringByName(actualResName.c_str(), quantity, strResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE,
                "Get plural string by name error, resName=%{public}s, errorCode=%{public}d", resName.c_str(), state);
        }
    }
    return strResult;
}

std::vector<std::string> ResourceAdapterImpl::GetStringArray(uint32_t resId) const
{
    std::vector<std::string> strResults;
    if (resourceManager_) {
        auto state = resourceManager_->GetStringArrayById(resId, strResults);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetStringArray error, id=%{public}u", resId);
        }
    }
    return strResults;
}

std::vector<std::string> ResourceAdapterImpl::GetStringArrayByName(const std::string& resName) const
{
    std::vector<std::string> strResults;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetStringArrayByName(actualResName.c_str(), strResults);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get stringArray by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }
    return strResults;
}

double ResourceAdapterImpl::GetDouble(uint32_t resId)
{
    float result = 0.0f;
    if (resourceManager_) {
        auto state = resourceManager_->GetFloatById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetDouble error, id=%{public}u", resId);
        }
    }
    return static_cast<double>(result);
}

double ResourceAdapterImpl::GetDoubleByName(const std::string& resName)
{
    float result = 0.0f;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetFloatByName(actualResName.c_str(), result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get double by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }
    return static_cast<double>(result);
}

int32_t ResourceAdapterImpl::GetInt(uint32_t resId)
{
    int32_t result = 0;
    if (resourceManager_) {
        auto state = resourceManager_->GetIntegerById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetInt error, id=%{public}u", resId);
        }
    }
    return result;
}

int32_t ResourceAdapterImpl::GetIntByName(const std::string& resName)
{
    int32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetIntegerByName(actualResName.c_str(), result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get int by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }
    return result;
}

std::vector<uint32_t> ResourceAdapterImpl::GetIntArray(uint32_t resId) const
{
    std::vector<int> intVectorResult;
    if (resourceManager_) {
        auto state = resourceManager_->GetIntArrayById(resId, intVectorResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetIntArray error, id=%{public}u", resId);
        }
    }
    std::vector<uint32_t> result(intVectorResult.size());
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

std::vector<uint32_t> ResourceAdapterImpl::GetIntArrayByName(const std::string& resName) const
{
    std::vector<int> intVectorResult;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetIntArrayByName(actualResName.c_str(), intVectorResult);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get intArray by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }

    std::vector<uint32_t> result(intVectorResult.size());
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

bool ResourceAdapterImpl::GetBoolean(uint32_t resId) const
{
    bool result = false;
    if (resourceManager_) {
        auto state = resourceManager_->GetBooleanById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetBoolean error, id=%{public}u", resId);
        }
    }
    return result;
}

bool ResourceAdapterImpl::GetBooleanByName(const std::string& resName) const
{
    bool result = false;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetBooleanByName(actualResName.c_str(), result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get boolean by name error, resName=%{public}s, errorCode=%{public}d",
                resName.c_str(), state);
        }
    }
    return result;
}

std::string ResourceAdapterImpl::GetMediaPath(uint32_t resId)
{
    std::string mediaPath = "";
    if (resourceManager_) {
        auto state = resourceManager_->GetMediaById(resId, mediaPath);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetMediaPath error, id=%{public}u", resId);
            return "";
        }
        // The Media file directory starts with file// on the PC Preview
        return "file://" + mediaPath;
    }
    return "";
}

std::string ResourceAdapterImpl::GetMediaPathByName(const std::string& resName)
{
    std::string mediaPath = "";
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetMediaByName(actualResName.c_str(), mediaPath);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "GetMediaPathByName error, resName=%{public}s, errorCode=%{public}u",
                resName.c_str(), state);
            return "";
        }
        // The Media file directory starts with file// on the PC Preview
        return "file://" + mediaPath;
    }
    return "";
}

std::string ResourceAdapterImpl::GetRawfile(const std::string& fileName)
{
    // The rawfile file directory starts with file// on the PC Preview
    return "file://" + packagePathStr_ + "/resources/rawfile/" + fileName;
}

bool ResourceAdapterImpl::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    return false;
}

bool ResourceAdapterImpl::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    return false;
}

bool ResourceAdapterImpl::GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    return false;
}

void ResourceAdapterImpl::UpdateResourceManager(const std::string& bundleName, const std::string& moduleName)
{
    return;
}

std::string ResourceAdapterImpl::GetActualResourceName(const std::string& resName)
{
    auto index = resName.find_last_of('.');
    if (index == std::string::npos) {
        LOGE("GetActualResourceName error, incorrect resName format.");
        return {};
    }
    return resName.substr(index + 1, resName.length() - index - 1);
}

uint32_t ResourceAdapterImpl::GetSymbolById(uint32_t resId) const
{
    uint32_t result = 0;
    if (resourceManager_) {
        resourceManager_->GetSymbolById(resId, result);
    }
    return result;
}

uint32_t ResourceAdapterImpl::GetSymbolByName(const char* resName) const
{
    uint32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    if (resourceManager_) {
        auto state = resourceManager_->GetSymbolByName(actualResName.c_str(), result);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get symbol by name error, name=%{public}s, errorCode=%{public}d",
                resName, state);
        }
    }
    return result;
}

ColorMode ResourceAdapterImpl::GetResourceColorMode() const
{
    CHECK_NULL_RETURN(resourceManager_, ColorMode::LIGHT);
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    resourceManager_->GetResConfig(*resConfig);
    return resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK ? ColorMode::DARK : ColorMode::LIGHT;
}

RefPtr<ResourceAdapter> ResourceAdapterImpl::GetOverrideResourceAdapter(
    const ResourceConfiguration& config, const ConfigurationChange& configurationChange)
{
    std::shared_ptr<Global::Resource::ResConfig> overrideResConfig(Global::Resource::CreateResConfig());
    resourceManager_->GetOverrideResConfig(*overrideResConfig);
    if (configurationChange.colorModeUpdate) {
        overrideResConfig->SetColorMode(ConvertColorModeToGlobal(config.GetColorMode()));
    }
    if (configurationChange.directionUpdate) {
        overrideResConfig->SetDirection(ConvertDirectionToGlobal(config.GetOrientation()));
    }
    if (configurationChange.dpiUpdate) {
        overrideResConfig->SetScreenDensity(config.GetDensity());
    }
    auto overrideResMgr = resourceManager_->GetOverrideResourceManager(overrideResConfig);
    return AceType::MakeRefPtr<ResourceAdapterImpl>(overrideResMgr);
}
} // namespace OHOS::Ace
