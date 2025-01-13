/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/resource_adapter_impl_v2.h"

#include <dirent.h>

#include "drawable_descriptor.h"
#include "resource_adapter_impl_v2.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/resource_convertor.h"
#include "base/utils/utils.h"
#include "core/components/theme/theme_attributes.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace {
namespace {
constexpr uint32_t OHOS_THEME_ID = 125829872; // ohos_theme
const Color ERROR_VALUE_COLOR = Color(0xff000000);

void CheckThemeId(int32_t& themeId)
{
    if (themeId >= 0) {
        return;
    }
    themeId = OHOS_THEME_ID;
}

const char* PATTERN_MAP[] = {
    THEME_PATTERN_BUTTON,
    THEME_PATTERN_CAMERA,
    THEME_PATTERN_LIST_ITEM,
    THEME_PATTERN_ARC_LIST,
    THEME_PATTERN_ARC_LIST_ITEM,
    THEME_PATTERN_PICKER,
    THEME_PATTERN_PROGRESS,
    THEME_PATTERN_SELECT,
    THEME_PATTERN_STEPPER,
    THEME_PATTERN_TEXT,
    THEME_PATTERN_TEXTFIELD,
    THEME_PATTERN_TEXT_OVERLAY,
    THEME_PATTERN_CONTAINER_MODAL
};

// PRELOAD_LIST contain themes that should be preloaded asynchronously
const char* PRELOAD_LIST[] = {
    THEME_BLUR_STYLE_COMMON,
    THEME_PATTERN_ICON,
    THEME_PATTERN_SHADOW
};

constexpr char RESOURCE_TOKEN_PATTERN[] = "\\[.+?\\]\\.(\\S+?\\.\\S+)";

bool IsDirExist(const std::string& path)
{
    char realPath[PATH_MAX] = { 0x00 };
    CHECK_NULL_RETURN(realpath(path.c_str(), realPath), false);
    DIR* dir = opendir(realPath);
    CHECK_NULL_RETURN(dir, false);
    closedir(dir);
    return true;
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
};
} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::CreateV2()
{
    return AceType::MakeRefPtr<ResourceAdapterImplV2>();
}

RefPtr<ResourceAdapter> ResourceAdapter::CreateNewResourceAdapter(
    const std::string& bundleName, const std::string& moduleName)
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, nullptr);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, nullptr);
    
    RefPtr<ResourceAdapter> newResourceAdapter = nullptr;
    auto context = aceContainer->GetAbilityContextByModule(bundleName, moduleName);
    if (context) {
        auto resourceManager = context->GetResourceManager();
        auto resourceAdapterV2 = AceType::MakeRefPtr<ResourceAdapterImplV2>(resourceManager);
        resourceAdapterV2->SetAppHasDarkRes(aceContainer->GetResourceConfiguration().GetAppHasDarkRes());
        newResourceAdapter = resourceAdapterV2;
    } else {
        newResourceAdapter = ResourceAdapter::CreateV2();
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

ResourceAdapterImplV2::ResourceAdapterImplV2(std::shared_ptr<Global::Resource::ResourceManager> resourceManager)
{
    sysResourceManager_ = resourceManager;
}

ResourceAdapterImplV2::ResourceAdapterImplV2(
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager, const ResourceInfo& resourceInfo)
{
    std::string resPath = resourceInfo.GetPackagePath();
    std::string hapPath = resourceInfo.GetHapPath();
    std::string resIndexPath = hapPath.empty() ? (resPath + "resources.index") : hapPath;
    packagePathStr_ = (hapPath.empty() || IsDirExist(resPath)) ? resPath : std::string();

    auto resConfig = ConvertConfigToGlobal(resourceInfo.GetResourceConfiguration());
    sysResourceManager_ = resourceManager;
    if (resConfig != nullptr) {
        sysResourceManager_->UpdateResConfig(*resConfig);
    }
    resConfig_ = resConfig;
    appHasDarkRes_ = resourceInfo.GetResourceConfiguration().GetAppHasDarkRes();
}

void ResourceAdapterImplV2::Init(const ResourceInfo& resourceInfo)
{
    std::string resPath = resourceInfo.GetPackagePath();
    std::string hapPath = resourceInfo.GetHapPath();
    auto resConfig = ConvertConfigToGlobal(resourceInfo.GetResourceConfiguration());
    std::shared_ptr<Global::Resource::ResourceManager> newResMgr(Global::Resource::CreateResourceManager());
    std::string resIndexPath = hapPath.empty() ? (resPath + "resources.index") : hapPath;
    newResMgr->AddResource(resIndexPath.c_str());
    if (resConfig != nullptr) {
        newResMgr->UpdateResConfig(*resConfig);
    }
    sysResourceManager_ = newResMgr;
    packagePathStr_ = (hapPath.empty() || IsDirExist(resPath)) ? resPath : std::string();
    resConfig_ = resConfig;
    appHasDarkRes_ = resourceInfo.GetResourceConfiguration().GetAppHasDarkRes();
}

bool ResourceAdapterImplV2::NeedUpdateResConfig(const std::shared_ptr<Global::Resource::ResConfig>& oldResConfig,
    const std::shared_ptr<Global::Resource::ResConfig>& newResConfig)
{
    if (oldResConfig == nullptr) {
        return true;
    }
    auto oldLocaleInfo = oldResConfig->GetLocaleInfo();
    auto newLocaleInfo = newResConfig->GetLocaleInfo();
    bool isLocaleChange = false;
    if (newLocaleInfo == nullptr) {
        isLocaleChange = false;
    } else if (oldLocaleInfo == nullptr) {
        isLocaleChange = true;
    } else {
        isLocaleChange = std::string(oldLocaleInfo->getLanguage()) != std::string(newLocaleInfo->getLanguage()) ||
                         std::string(oldLocaleInfo->getScript()) != std::string(newLocaleInfo->getScript()) ||
                         std::string(oldLocaleInfo->getCountry()) != std::string(newLocaleInfo->getCountry());
    }

    return oldResConfig->GetDeviceType() != newResConfig->GetDeviceType() ||
           oldResConfig->GetDirection() != newResConfig->GetDirection() ||
           oldResConfig->GetScreenDensity() != newResConfig->GetScreenDensity() ||
           oldResConfig->GetColorMode() != newResConfig->GetColorMode() ||
           oldResConfig->GetInputDevice() != newResConfig->GetInputDevice() || isLocaleChange;
}

void ResourceAdapterImplV2::UpdateConfig(const ResourceConfiguration& config, bool themeFlag)
{
    std::lock_guard<std::mutex> lock(updateResConfigMutex_);
    auto resConfig = ConvertConfigToGlobal(config);
    auto needUpdateResConfig = NeedUpdateResConfig(resConfig_, resConfig) || themeFlag;
    if (sysResourceManager_ && resConfig != nullptr && needUpdateResConfig) {
        sysResourceManager_->UpdateResConfig(*resConfig, themeFlag);
    }
    resConfig_ = resConfig;
}

RefPtr<ThemeStyle> ResourceAdapterImplV2::GetTheme(int32_t themeId)
{
    CheckThemeId(themeId);
    auto theme = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    
    constexpr char flag[] = "ohos_"; // fit with resource/base/theme.json and pattern.json
    {
        auto manager = GetResourceManager();
        if (manager) {
            auto ret = manager->GetThemeById(themeId, theme->rawAttrs_);
            if (ret != Global::Resource::SUCCESS) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get theme by id error, id=%{public}d", themeId);
            }
            for (size_t i = 0; i < sizeof(PATTERN_MAP) / sizeof(PATTERN_MAP[0]); i++) {
                ResourceThemeStyle::RawAttrMap attrMap;
                std::string patternTag = PATTERN_MAP[i];
                std::string patternName = std::string(flag) + PATTERN_MAP[i];
                ret = manager->GetPatternByName(patternName.c_str(), attrMap);
                if (ret != Global::Resource::SUCCESS) {
                    TAG_LOGW(
                        AceLogTag::ACE_RESOURCE, "Get pattern by name error, name=%{public}s", patternName.c_str());
                }
                if (attrMap.empty()) {
                    continue;
                }
                theme->patternAttrs_[patternTag] = attrMap;
            }
        }
    }

    if (theme->patternAttrs_.empty() && theme->rawAttrs_.empty()) {
        return nullptr;
    }

    theme->ParseContent();
    theme->patternAttrs_.clear();

    PreloadTheme(themeId, theme);
    return theme;
}

void ResourceAdapterImplV2::PreloadTheme(int32_t themeId, RefPtr<ResourceThemeStyle> theme)
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto manager = GetResourceManager();
    CHECK_NULL_VOID(manager);
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    // post an asynchronous task to preload themes in PRELOAD_LIST
    auto task = [manager, resourceThemeStyle = WeakPtr<ResourceThemeStyle>(theme), weak = WeakClaim(this)]() -> void {
        auto themeStyle = resourceThemeStyle.Upgrade();
        CHECK_NULL_VOID(themeStyle);
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        for (size_t i = 0; i < sizeof(PRELOAD_LIST) / sizeof(PRELOAD_LIST[0]); ++i) {
            std::string patternName = PRELOAD_LIST[i];
            themeStyle->PushBackCheckThemeStyleVector(patternName);
            auto style = adapter->GetPatternByName(patternName);
            if (style) {
                ResValueWrapper value = { .type = ThemeConstantsType::PATTERN, .value = style };
                themeStyle->SetAttr(patternName, value);
            }
        }

        themeStyle->SetPromiseValue();
    };

    // isolation of loading card themes
    if (!container->IsFormRender()) {
        taskExecutor->PostTask(task, TaskExecutor::TaskType::BACKGROUND, "ArkUILoadTheme");
    }
}

RefPtr<TaskExecutor> ResourceAdapterImplV2::GetTaskExecutor()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetTaskExecutor();
}

RefPtr<ThemeStyle> ResourceAdapterImplV2::GetPatternByName(const std::string& patternName)
{
    auto patternStyle = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    patternStyle->SetName(patternName);
    constexpr char flag[] = "ohos_"; // fit with resource/base/theme.json and pattern.json
    auto manager = GetResourceManager();
    if (manager) {
        ResourceThemeStyle::RawAttrMap attrMap;
        std::string patternTag = std::string(flag) + patternName;
        auto state = manager->GetPatternByName(patternTag.c_str(), attrMap);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern by name error, name=%{public}s", patternTag.c_str());
            state = manager->GetPatternByName(patternName.c_str(), attrMap);
            if (state != Global::Resource::SUCCESS) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern by name error, name=%{public}s", patternName.c_str());
            } else if (attrMap.empty()) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern %{public}s empty!", patternName.c_str());
            }
        } else if (attrMap.empty()) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern %{public}s empty!", patternTag.c_str());
        }
        patternStyle->rawAttrs_ = attrMap;
        patternStyle->ParseContent();
    }
    return patternStyle;
}

Color ResourceAdapterImplV2::GetColor(uint32_t resId)
{
    uint32_t result = 0;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, Color(result));
    auto state = manager->GetColorById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get color by id error, id=%{public}u", resId);
        return ERROR_VALUE_COLOR;
    }
    return Color(result);
}

Color ResourceAdapterImplV2::GetColorByName(const std::string& resName)
{
    uint32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, Color(result));
    auto state = manager->GetColorByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get color by name error, name=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return Color(result);
}

Dimension ResourceAdapterImplV2::GetDimension(uint32_t resId)
{
    float dimensionFloat = 0.0f;
#ifdef NG_BUILD
    std::string unit;
    auto manager = GetResourceManager();
    if (manager) {
        auto state = manager->GetFloatById(resId, dimensionFloat, unit);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "NG Get dimension by id error, id=%{public}u, errorCode=%{public}d",
                resId, state);
        }
    }
    return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
#else
    if (Container::IsCurrentUseNewPipeline()) {
        std::string unit;
        auto manager = GetResourceManager();
        if (manager) {
            auto state = manager->GetFloatById(resId, dimensionFloat, unit);
            if (state != Global::Resource::SUCCESS) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "NG: Get dimension by id error, id=%{public}u, errorCode=%{public}d",
                    resId, state);
            }
        }
        return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
    }

    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, Dimension(static_cast<double>(dimensionFloat)));
    auto state = manager->GetFloatById(resId, dimensionFloat);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(
            AceLogTag::ACE_RESOURCE, "Get dimension by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return Dimension(static_cast<double>(dimensionFloat));
#endif
}

Dimension ResourceAdapterImplV2::GetDimensionByName(const std::string& resName)
{
    float dimensionFloat = 0.0f;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, Dimension());
    std::string unit;
    auto state = manager->GetFloatByName(actualResName.c_str(), dimensionFloat, unit);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get dimension by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
}

std::string ResourceAdapterImplV2::GetString(uint32_t resId)
{
    std::string strResult = "";
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResult);
    auto state = manager->GetStringById(resId, strResult);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get string by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return strResult;
}

std::string ResourceAdapterImplV2::GetStringByName(const std::string& resName)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResult);
    auto state = manager->GetStringByName(actualResName.c_str(), strResult);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get string by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return strResult;
}

std::string ResourceAdapterImplV2::GetPluralString(uint32_t resId, int quantity)
{
    std::string strResult = "";
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResult);
    auto state = manager->GetPluralStringById(resId, quantity, strResult);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get plural string by id error, id=%{public}u, errorCode=%{public}d", resId,
            state);
    }
    return strResult;
}

std::string ResourceAdapterImplV2::GetPluralStringByName(const std::string& resName, int quantity)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResult);
    auto state = manager->GetPluralStringByName(actualResName.c_str(), quantity, strResult);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get plural string by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return strResult;
}

std::vector<std::string> ResourceAdapterImplV2::GetStringArray(uint32_t resId) const
{
    std::vector<std::string> strResults;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResults);
    auto state = manager->GetStringArrayById(resId, strResults);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(
            AceLogTag::ACE_RESOURCE, "Get stringArray by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return strResults;
}

std::vector<std::string> ResourceAdapterImplV2::GetStringArrayByName(const std::string& resName) const
{
    std::vector<std::string> strResults;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, strResults);
    auto state = manager->GetStringArrayByName(actualResName.c_str(), strResults);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get stringArray by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return strResults;
}

double ResourceAdapterImplV2::GetDouble(uint32_t resId)
{
    float result = 0.0f;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, static_cast<double>(result));
    auto state = manager->GetFloatById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get double by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return static_cast<double>(result);
}

double ResourceAdapterImplV2::GetDoubleByName(const std::string& resName)
{
    float result = 0.0f;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, static_cast<double>(result));
    auto state = manager->GetFloatByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get double by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return static_cast<double>(result);
}

int32_t ResourceAdapterImplV2::GetInt(uint32_t resId)
{
    int32_t result = 0;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, result);
    auto state = manager->GetIntegerById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get int by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return result;
}

int32_t ResourceAdapterImplV2::GetIntByName(const std::string& resName)
{
    int32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, result);
    auto state = manager->GetIntegerByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get int by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return result;
}

std::vector<uint32_t> ResourceAdapterImplV2::GetIntArray(uint32_t resId) const
{
    std::vector<int> intVectorResult;
    {
        auto manager = GetResourceManager();
        if (manager) {
            auto state = manager->GetIntArrayById(resId, intVectorResult);
            if (state != Global::Resource::SUCCESS) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get intArray by id error, id=%{public}u, errorCode=%{public}d",
                    resId, state);
            }
        }
    }

    std::vector<uint32_t> result(intVectorResult.size());
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

std::vector<uint32_t> ResourceAdapterImplV2::GetIntArrayByName(const std::string& resName) const
{
    std::vector<int> intVectorResult;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, {});
    auto state = manager->GetIntArrayByName(actualResName.c_str(), intVectorResult);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get intArray by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }

    std::vector<uint32_t> result(intVectorResult.size());
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

bool ResourceAdapterImplV2::GetBoolean(uint32_t resId) const
{
    bool result = false;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, result);
    auto state = manager->GetBooleanById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get boolean by id error, id=%{public}u, errorCode=%{public}d", resId, state);
    }
    return result;
}

bool ResourceAdapterImplV2::GetBooleanByName(const std::string& resName) const
{
    bool result = false;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, result);
    auto state = manager->GetBooleanByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get boolean by name error, resName=%{public}s, errorCode=%{public}d",
            resName.c_str(), state);
    }
    return result;
}

std::shared_ptr<Media::PixelMap> ResourceAdapterImplV2::GetPixelMap(uint32_t resId)
{
    auto manager = GetResourceManager();

    CHECK_NULL_RETURN(manager, nullptr);
    Napi::DrawableDescriptor::DrawableType drawableType;
    Global::Resource::RState state;
    auto drawableDescriptor =
        Napi::DrawableDescriptorFactory::Create(resId, sysResourceManager_, state, drawableType, 0);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Failed to Create drawableDescriptor by %{public}d, errorCode=%{public}d",
            resId, state);
        return nullptr;
    }
    CHECK_NULL_RETURN(drawableDescriptor, nullptr);
    return drawableDescriptor->GetPixelMap();
}

std::string ResourceAdapterImplV2::GetMediaPath(uint32_t resId)
{
    std::string mediaPath = "";
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, "");
    auto state = manager->GetMediaById(resId, mediaPath);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media by id error, id=%{public}u, errorCode=%{public}u", resId, state);
        return "";
    }
    if (SystemProperties::GetUnZipHap()) {
        return "file:///" + mediaPath;
    }
    auto pos = mediaPath.find_last_of('.');
    if (pos == std::string::npos) {
        return "";
    }
    return "resource:///" + std::to_string(resId) + mediaPath.substr(pos);
}

std::string ResourceAdapterImplV2::GetMediaPathByName(const std::string& resName)
{
    std::string mediaPath = "";
    auto actualResName = GetActualResourceName(resName);
    {
        auto manager = GetResourceManager();
        CHECK_NULL_RETURN(manager, "");
        auto state = manager->GetMediaByName(actualResName.c_str(), mediaPath);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media path by name error, resName=%{public}s, errorCode=%{public}u",
                resName.c_str(), state);
            return "";
        }
    }
    if (SystemProperties::GetUnZipHap()) {
        return "file:///" + mediaPath;
    }
    auto pos = mediaPath.find_last_of('.');
    if (pos == std::string::npos) {
        return "";
    }
    return "resource:///" + actualResName + mediaPath.substr(pos);
}

std::string ResourceAdapterImplV2::GetRawfile(const std::string& fileName)
{
    // as web component not support resource format: resource://RAWFILE/{fileName}, use old format
    if (!packagePathStr_.empty()) {
        std::string outPath;
        auto manager = GetResourceManager();
        CHECK_NULL_RETURN(manager, "");
        // Adapt to the input like: "file:///index.html?a=1", before the new solution comes.
        auto it = std::find_if(fileName.begin(), fileName.end(), [](char c) { return (c == '#') || (c == '?'); });
        std::string params;
        std::string newFileName = fileName;
        if (it != fileName.end()) {
            newFileName = std::string(fileName.begin(), it);
            params = std::string(it, fileName.end());
        }
        auto state = manager->GetRawFilePathByName(newFileName, outPath);
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get rawFile error, filename:%{public}s, error:%{public}u",
                fileName.c_str(), state);
            return "";
        }
        return "file:///" + outPath + params;
    }
    std::regex regex(RESOURCE_TOKEN_PATTERN);
    std::smatch results;
    std::string newFIleName = fileName;
    if (std::regex_match(fileName, results, regex)) {
        newFIleName = results[1];
    }
    return "resource://RAWFILE/" + newFIleName;
}

bool ResourceAdapterImplV2::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetRawFileFromHap(rawFile, len, dest);
    if (state != Global::Resource::SUCCESS || !dest) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get rawFile from hap error, raw filename:%{public}s, error:%{public}u",
            rawFile.c_str(), state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetRawFileFromHap(rawFile, len, dest);
    if (state != Global::Resource::SUCCESS || !dest) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE,
            "Get rawFile from hap error, raw filename:%{public}s, bundleName:%{public}s, moduleName:%{public}s, "
            "error:%{public}u",
            rawFile.c_str(), bundleName.c_str(), moduleName.c_str(), state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaDataById(resId, len, dest);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media data by id error, id:%{public}u, error:%{public}u", resId, state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaDataById(resId, len, dest);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE,
            "Get media data by id error, id:%{public}u, bundleName:%{public}s, moduleName:%{public}s, error:%{public}u",
            resId, bundleName.c_str(), moduleName.c_str(), state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaDataByName(resName.c_str(), len, dest);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media data by name error, resName:%{public}s, error:%{public}u",
            resName.c_str(), state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaDataByName(resName.c_str(), len, dest);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE,
            "Get media data by name error, resName:%{public}s, bundleName:%{public}s, moduleName:%{public}s, "
            "error:%{public}u",
            resName.c_str(), bundleName.c_str(), moduleName.c_str(), state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetRawFileDescription(
    const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    OHOS::Global::Resource::ResourceManager::RawFileDescriptor descriptor;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetRawFileDescriptorFromHap(rawfileName, descriptor);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get raw file description error, rawFileName:%{public}s, error:%{public}u",
            rawfileName.c_str(), state);
        return false;
    }
    rawfileDescription.fd = descriptor.fd;
    rawfileDescription.offset = descriptor.offset;
    rawfileDescription.length = descriptor.length;
    return true;
}

bool ResourceAdapterImplV2::CloseRawFileDescription(const std::string &rawfileName) const
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->CloseRawFileDescriptor(rawfileName);
    if (state != Global::Resource::SUCCESS) {
        LOGE("Close RawFile Description error, error:%{public}u", state);
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetMediaById(const int32_t& resId, std::string& mediaPath) const
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaById(resId, mediaPath);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media by id error, resId:%{public}d, error:%{public}u", resId, state);
        return false;
    }
    return true;
}

std::string ResourceAdapterImplV2::GetActualResourceName(const std::string& resName) const
{
    auto index = resName.find_last_of('.');
    if (index == std::string::npos) {
        return {};
    }
    return resName.substr(index + 1, resName.length() - index - 1);
}

uint32_t ResourceAdapterImplV2::GetResourceLimitKeys() const
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, 0);
    return manager->GetResourceLimitKeys();
}

uint32_t ResourceAdapterImplV2::GetSymbolByName(const char* resName) const
{
    uint32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, -1);
    auto state = manager->GetSymbolByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get symbol by name error, name=%{public}s, errorCode=%{public}d",
            resName, state);
    }
    return result;
}

uint32_t ResourceAdapterImplV2::GetSymbolById(uint32_t resId) const
{
    uint32_t result = 0;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, -1);
    manager->GetSymbolById(resId, result);
    return result;
}

void ResourceAdapterImplV2::UpdateColorMode(ColorMode colorMode)
{
    RefPtr<Container> container = Container::Current();
    CHECK_NULL_VOID(container);
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_VOID(aceContainer);

    auto resConfig = aceContainer->GetResourceConfiguration();
    resConfig.SetColorMode(colorMode);
    UpdateConfig(resConfig, false);
}

ColorMode ResourceAdapterImplV2::GetResourceColorMode() const
{
    CHECK_NULL_RETURN(resConfig_, ColorMode::LIGHT);
    if (resConfig_->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK && !resConfig_->GetAppColorMode() &&
        !appHasDarkRes_) {
        return ColorMode::LIGHT;
    }
    return resConfig_->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK ? ColorMode::DARK : ColorMode::LIGHT;
}

void ResourceAdapterImplV2::SetAppHasDarkRes(bool hasDarkRes)
{
    appHasDarkRes_ = hasDarkRes;
}

RefPtr<ResourceAdapter> ResourceAdapterImplV2::GetOverrideResourceAdapter(
    const ResourceConfiguration& config, const ConfigurationChange& configurationChange)
{
    CHECK_NULL_RETURN(sysResourceManager_, nullptr);
    std::shared_ptr<Global::Resource::ResConfig> overrideResConfig(Global::Resource::CreateResConfig());
    sysResourceManager_->GetOverrideResConfig(*overrideResConfig);
    if (configurationChange.colorModeUpdate) {
        overrideResConfig->SetColorMode(ConvertColorModeToGlobal(config.GetColorMode()));
    }
    if (configurationChange.directionUpdate) {
        overrideResConfig->SetDirection(ConvertDirectionToGlobal(config.GetOrientation()));
    }
    if (configurationChange.dpiUpdate) {
        overrideResConfig->SetScreenDensity(config.GetDensity());
    }
    auto overrideResMgr = sysResourceManager_->GetOverrideResourceManager(overrideResConfig);
    return AceType::MakeRefPtr<ResourceAdapterImplV2>(overrideResMgr);
}
} // namespace OHOS::Ace
