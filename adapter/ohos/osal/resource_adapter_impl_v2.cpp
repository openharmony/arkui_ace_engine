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
#include <queue>
#include <unordered_set>

#include "drawable_descriptor.h"
#include "resource_adapter_impl_v2.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/resource_convertor.h"
#include "core/common/resource/resource_manager.h"
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

const std::unordered_set<std::string> PATTERN_NOT_SYNC_LOAD_SET = { THEME_PATTERN_CHECKBOX, THEME_PATTERN_DATA_PANEL,
    THEME_PATTERN_RADIO, THEME_PATTERN_SWIPER, THEME_PATTERN_SWITCH, THEME_PATTERN_TOOLBAR, THEME_PATTERN_TOGGLE,
    THEME_PATTERN_TOAST, THEME_PATTERN_DIALOG, THEME_PATTERN_DRAG_BAR, THEME_PATTERN_CLOSE_ICON,
    THEME_PATTERN_SEMI_MODAL, THEME_PATTERN_BADGE, THEME_PATTERN_CALENDAR, THEME_PATTERN_CARD, THEME_PATTERN_CLOCK,
    THEME_PATTERN_COUNTER, THEME_PATTERN_DIVIDER, THEME_PATTERN_FOCUS_ANIMATION, THEME_PATTERN_GRID,
    THEME_PATTERN_HYPERLINK, THEME_PATTERN_ICON, THEME_PATTERN_IMAGE, THEME_PATTERN_LIST, THEME_PATTERN_MARQUEE,
    THEME_PATTERN_NAVIGATION_BAR, THEME_PATTERN_PIECE, THEME_PATTERN_POPUP, THEME_PATTERN_QRCODE, THEME_PATTERN_RATING,
    THEME_PATTERN_REFRESH, THEME_PATTERN_SCROLL_BAR, THEME_PATTERN_SEARCH, THEME_PATTERN_TAB, THEME_PATTERN_SLIDER,
    THEME_PATTERN_RICH_EDITOR, THEME_PATTERN_VIDEO, THEME_PATTERN_INDEXER, THEME_PATTERN_APP_BAR,
    THEME_PATTERN_ADVANCED_PATTERN, THEME_PATTERN_SECURITY_COMPONENT, THEME_PATTERN_FORM, THEME_PATTERN_SIDE_BAR,
    THEME_PATTERN_PATTERN_LOCK, THEME_PATTERN_GAUGE, THEME_PATTERN_SHEET, THEME_PATTERN_AGING_ADAPATION_DIALOG,
    THEME_PATTERN_LINEAR_INDICATOR, THEME_BLUR_STYLE_COMMON, THEME_PATTERN_SHADOW, THEME_PATTERN_SCROLLABLE,
    THEME_PATTERN_APP };

const std::unordered_set<std::string> PATTERN_SYNC_LOAD_SET = { THEME_PATTERN_BUTTON, THEME_PATTERN_CAMERA,
    THEME_PATTERN_LIST_ITEM, THEME_PATTERN_ARC_LIST, THEME_PATTERN_ARC_LIST_ITEM, THEME_PATTERN_PICKER,
    THEME_PATTERN_PROGRESS, THEME_PATTERN_SELECT, THEME_PATTERN_STEPPER, THEME_PATTERN_TEXT, THEME_PATTERN_TEXTFIELD,
    THEME_PATTERN_TEXT_OVERLAY, THEME_PATTERN_CONTAINER_MODAL };

const std::string PATTERN_ASYNC_LOAD_LIST[] = { THEME_BLUR_STYLE_COMMON, THEME_PATTERN_ICON, THEME_PATTERN_SHADOW };
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
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager, int32_t instanceId)
{
    sysResourceManager_ = resourceManager;
    std::shared_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    resourceManager->GetResConfig(*resConfig);
    resConfig_ = resConfig;
    appHasDarkRes_ = resConfig->GetAppDarkRes();
    auto container = Platform::AceContainer::GetContainer(instanceId);
    if (container) {
        std::string hapPath = container->GetHapPath();
        std::string resPath = container->GetPackagePathStr();
        packagePathStr_ = (hapPath.empty() || IsDirExist(resPath)) ? resPath : std::string();
    }
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
        TAG_LOGI(AceLogTag::ACE_RESOURCE, "ResourceAdapter UpdateResConfig with colorMode %{public}s",
            (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK ? "dark" : "light"));
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
        TAG_LOGI(AceLogTag::ACE_RESOURCE, "ResourceAdapter Init with colorMode %{public}s",
            (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK ? "dark" : "light"));
    }
    sysResourceManager_ = newResMgr;
    packagePathStr_ = (hapPath.empty() || IsDirExist(resPath)) ? resPath : std::string();
    resConfig_ = resConfig;
    appHasDarkRes_ = resourceInfo.GetResourceConfiguration().GetAppHasDarkRes();
}

bool LocaleDiff(const std::shared_ptr<Global::Resource::ResConfig>& oldResConfig,
    const std::shared_ptr<Global::Resource::ResConfig>& newResConfig)
{
    auto oldLocaleInfo = oldResConfig->GetLocaleInfo();
    auto newLocaleInfo = newResConfig->GetLocaleInfo();
    if ((!oldLocaleInfo && newLocaleInfo) || (oldLocaleInfo && !newLocaleInfo)) {
        return true;
    }
    if (oldLocaleInfo && newLocaleInfo) {
        if (!StringUtils::CStringEqual(oldLocaleInfo->getLanguage(), newLocaleInfo->getLanguage()) ||
            !StringUtils::CStringEqual(oldLocaleInfo->getScript(), newLocaleInfo->getScript()) ||
            !StringUtils::CStringEqual(oldLocaleInfo->getCountry(), newLocaleInfo->getCountry())) {
            return true;
        }
    }
    auto oldPreferredLocaleInfo = oldResConfig->GetPreferredLocaleInfo();
    auto newPreferredLocaleInfo = newResConfig->GetPreferredLocaleInfo();
    if ((!oldPreferredLocaleInfo && newPreferredLocaleInfo) || (oldPreferredLocaleInfo && !newPreferredLocaleInfo)) {
        return true;
    }
    if (oldPreferredLocaleInfo && newPreferredLocaleInfo) {
        if (!StringUtils::CStringEqual(oldPreferredLocaleInfo->getLanguage(), newPreferredLocaleInfo->getLanguage()) ||
            !StringUtils::CStringEqual(oldPreferredLocaleInfo->getScript(), newPreferredLocaleInfo->getScript()) ||
            !StringUtils::CStringEqual(oldPreferredLocaleInfo->getCountry(), newPreferredLocaleInfo->getCountry())) {
            return true;
        }
    }
    return false;
}

bool ResourceAdapterImplV2::NeedUpdateResConfig(const std::shared_ptr<Global::Resource::ResConfig>& oldResConfig,
    const std::shared_ptr<Global::Resource::ResConfig>& newResConfig)
{
    CHECK_NULL_RETURN(oldResConfig, true);

    return LocaleDiff(oldResConfig, newResConfig) || oldResConfig->GetDeviceType() != newResConfig->GetDeviceType() ||
           oldResConfig->GetDirection() != newResConfig->GetDirection() ||
           oldResConfig->GetScreenDensity() != newResConfig->GetScreenDensity() ||
           oldResConfig->GetColorMode() != newResConfig->GetColorMode() ||
           oldResConfig->GetInputDevice() != newResConfig->GetInputDevice();
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
using ResType = OHOS::Global::Resource::ResType;
using ResData = OHOS::Global::Resource::ResourceManager::ResData;
using ThemeResTuple = std::tuple<std::string, ResType, std::string>;
RefPtr<ThemeStyle> ResourceAdapterImplV2::GetTheme(int32_t themeId)
{
    CheckThemeId(themeId);
    auto theme = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    auto resourceManager = GetResourceManager();
    std::map<std::string, ResData> themeOutValue;
    if (resourceManager) {
        Global::Resource::RState getThemeRet = resourceManager->GetThemeDataById(themeId, themeOutValue);
        if (getThemeRet != Global::Resource::RState::SUCCESS) {
            LOGW("GetThemeDataById failed, error code=%{public}d, now load ohos_theme.", getThemeRet);
            getThemeRet = resourceManager->GetThemeDataById(OHOS_THEME_ID, themeOutValue);
            if (getThemeRet != Global::Resource::RState::SUCCESS) {
                LOGW("load ohos_theme failed, error code=%{public}d", getThemeRet);
                return nullptr;
            }
        }
    }
    std::queue<ThemeResTuple> themeQueue;
    for (auto eachTheme : themeOutValue) {
        std::string patternTag = eachTheme.first;         // e.g. advanced_pattern
        ResType patternType = eachTheme.second.resType;   // e.g. 22
        std::string patternData = eachTheme.second.value; // e.g. 125830098
        themeQueue.push(std::make_tuple(patternTag, patternType, patternData));
    }
    while (!themeQueue.empty()) {
        ThemeResTuple themeQueueFront = themeQueue.front();
        themeQueue.pop();
        std::string patternTag = std::get<0>(themeQueueFront);  // e.g. advanced_pattern
        ResType patternType = std::get<1>(themeQueueFront);     // e.g. 22
        std::string patternData = std::get<2>(themeQueueFront); // e.g. 125830098
        if (patternType == ResType::PATTERN) {
            patternNameMap_[patternTag] = StringUtils::StringToUintCheck(patternData);
        }
        if (patternType == ResType::PATTERN && PATTERN_SYNC_LOAD_SET.find(patternTag) != PATTERN_SYNC_LOAD_SET.end()) {
            // is theme pattern and sync load
            ResourceThemeStyle::RawAttrMap attrMap;
            std::map<std::string, ResData> patternOutValue;
            resourceManager->GetPatternDataById(StringUtils::StringToInt(patternData), patternOutValue);
            for (auto eachPattern : patternOutValue) {
                auto patternKey = eachPattern.first;
                auto patternValue = eachPattern.second.value;
                attrMap[patternKey] = patternValue;
            }
            if (attrMap.empty()) {
                continue;
            }
            theme->patternAttrs_[patternTag] = attrMap;
        } else if (patternType == ResType::PATTERN &&
                   PATTERN_NOT_SYNC_LOAD_SET.find(patternTag) == PATTERN_NOT_SYNC_LOAD_SET.end()) {
            // is nested pattern
            std::map<std::string, ResData> patternOutValue;
            resourceManager->GetPatternDataById(StringUtils::StringToInt(patternData), patternOutValue);
            for (auto eachPattern : patternOutValue) {
                auto sonPatternKey = eachPattern.first;           // e.g. advanced_pattern
                auto sonPatternType = eachPattern.second.resType; // e.g. 22
                auto sonPatternValue = eachPattern.second.value;  // e.g. 125830098
                themeQueue.push(std::make_tuple(sonPatternKey, sonPatternType, sonPatternValue));
            }
        } else if (patternType == ResType::COLOR || patternType == ResType::FLOAT || patternType == ResType::STRING ||
                   patternType == ResType::SYMBOL) {
            theme->rawAttrs_[patternTag] = patternData;
        } else if (patternType != ResType::PATTERN) {
            LOGW("GetTheme found unknown ResType:%{public}d", patternType);
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

    // post an asynchronous task to preload themes in PATTERN_ASYNC_LOAD_LIST
    auto task = [manager, resourceThemeStyle = WeakPtr<ResourceThemeStyle>(theme), weak = WeakClaim(this)]() -> void {
        auto themeStyle = resourceThemeStyle.Upgrade();
        CHECK_NULL_VOID(themeStyle);
        auto adapter = weak.Upgrade();
        CHECK_NULL_VOID(adapter);
        for (size_t i = 0; i < sizeof(PATTERN_ASYNC_LOAD_LIST) / sizeof(PATTERN_ASYNC_LOAD_LIST[0]); ++i) {
            std::string patternName = PATTERN_ASYNC_LOAD_LIST[i];
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
    auto manager = GetResourceManager();
    if (manager) {
        ResourceThemeStyle::RawAttrMap attrMap;
        uint32_t id = 0;
        Global::Resource::RState state;
        bool patternNameFound = true;
        if (!patternNameMap_.count(patternName)) {
            patternNameFound = false;
            constexpr char flag[] = "ohos_";
            std::string patternTag = std::string(flag) + patternName;
            state = manager->GetPatternByName(patternTag.c_str(), attrMap);
        } else {
            id = patternNameMap_[patternName];
            state = manager->GetPatternById(id, attrMap);
        }
        if (state != Global::Resource::SUCCESS) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern by name error, name=%{public}s", patternName.c_str());
            if (patternNameFound) {
                state = manager->GetPatternById(id, attrMap);
            } else {
                state = manager->GetPatternByName(patternName.c_str(), attrMap);
            }
            if (state != Global::Resource::SUCCESS) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern by name error, name=%{public}s", patternName.c_str());
                auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
                ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId() : -1,
                    patternName, "Pattern", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
            } else if (attrMap.empty()) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern %{public}s empty!", patternName.c_str());
            }
        } else if (attrMap.empty()) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get pattern %{public}s empty!", patternName.c_str());
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Color", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Color", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
            auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
            ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
                std::to_string(resId), "Dimension", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
                auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
                ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
                    std::to_string(resId), "Dimension", host ? host->GetTag().c_str() : "",
                    GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Dimension", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Dimension", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "String", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "String", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "PluralString", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "PluralString", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "StringArray", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "StringArray", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Double", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Double", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Int", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Int", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
                auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
                ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
                    std::to_string(resId), "IntArray", host ? host->GetTag().c_str() : "",
                    GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "IntArray", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Boolean", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Boolean", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "PixelMap", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "MediaPath", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
            auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
            ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
                resName, "MediaPath", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
            auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
            ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
                fileName, "RawFile", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            rawFile, "RawFile", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            rawFile, "RawFile", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "MediaData", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "MediaData", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "MediaData", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "MediaData", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            rawfileName, "RawFileDescription", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            rawfileName, "RawFileDescription", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
        return false;
    }
    return true;
}

bool ResourceAdapterImplV2::GetRawFD(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    OHOS::Global::Resource::ResourceManager::RawFileDescriptor descriptor;
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetRawFdNdkFromHap(rawfileName, descriptor);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get raw fd(no cache) error, rawFileName:%{public}s, error:%{public}u",
            rawfileName.c_str(), state);
        return false;
    }
    rawfileDescription.fd = descriptor.fd;
    rawfileDescription.offset = descriptor.offset;
    rawfileDescription.length = descriptor.length;
    return true;
}

bool ResourceAdapterImplV2::GetMediaById(const int32_t& resId, std::string& mediaPath) const
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto state = manager->GetMediaById(resId, mediaPath);
    if (state != Global::Resource::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get media by id error, resId:%{public}d, error:%{public}u", resId, state);
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            std::to_string(resId), "Media", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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
        auto host = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
        ResourceManager::GetInstance().AddResourceLoadError(ResourceErrorInfo(host ? host->GetId(): -1,
            resName, "Symbol", host ? host->GetTag().c_str() : "", GetCurrentTimestamp(), state));
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

bool ResourceAdapterImplV2::ExistDarkResById(const std::string& resourceId)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto resId = StringUtils::StringToUintCheck(resourceId, UINT32_MAX);
    if (resId == UINT32_MAX) {
        return false;
    }
    auto colorMode = GetResourceColorMode();
    bool colorChanged = false;
    if (colorMode == ColorMode::LIGHT) {
        UpdateColorMode(ColorMode::DARK);
        colorChanged = true;
    }
    auto appResCfg = Global::Resource::CreateResConfig();
    auto state = manager->GetResConfigById(resId, *appResCfg);
    if (colorChanged) {
        UpdateColorMode(ColorMode::LIGHT);
    }
    return (state == Global::Resource::SUCCESS) &&
        (appResCfg->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK);
}

bool ResourceAdapterImplV2::ExistDarkResByName(const std::string& resourceName, const std::string& resourceType)
{
    auto manager = GetResourceManager();
    CHECK_NULL_RETURN(manager, false);
    auto resType = StringUtils::StringToUintCheck(resourceType, UINT32_MAX);
    if (resType < OHOS::Global::Resource::ResType::VALUES ||
        resType > OHOS::Global::Resource::ResType::MAX_RES_TYPE) {
        return false;
    }
    auto type = static_cast<OHOS::Global::Resource::ResType>(resType);
    auto colorMode = GetResourceColorMode();
    bool colorChanged = false;
    if (colorMode == ColorMode::LIGHT) {
        UpdateColorMode(ColorMode::DARK);
        colorChanged = true;
    }
    auto appResCfg = Global::Resource::CreateResConfig();
    auto state = manager->GetResConfigByName(resourceName, type, *appResCfg);
    if (colorChanged) {
        UpdateColorMode(ColorMode::LIGHT);
    }
    return (state == Global::Resource::SUCCESS) &&
        (appResCfg->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK);
}
} // namespace OHOS::Ace
