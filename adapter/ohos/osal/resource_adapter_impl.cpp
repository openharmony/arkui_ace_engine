/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/resource_adapter_impl.h"

#include <dirent.h>

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/resource_convertor.h"
#include "adapter/ohos/osal/resource_theme_style.h"
#include "base/utils/system_properties.h"
#include "core/components/theme/theme_attributes.h"

namespace OHOS::Ace {
namespace {

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
    THEME_PATTERN_SEMI_MODAL,
    // append
    THEME_PATTERN_BADGE,
    THEME_PATTERN_CALENDAR,
    THEME_PATTERN_CAMERA,
    THEME_PATTERN_CLOCK,
    THEME_PATTERN_COUNTER,
    THEME_PATTERN_DIVIDER,
    THEME_PATTERN_FOCUS_ANIMATION,
    THEME_PATTERN_GRID,
    THEME_PATTERN_IMAGE,
    THEME_PATTERN_LIST,
    THEME_PATTERN_LIST_ITEM,
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
    THEME_PATTERN_ICON
};

bool IsDirExist(const std::string& path)
{
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(path.c_str(), realPath) == nullptr) {
        return false;
    }
    DIR *dir = opendir(realPath);
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::Create()
{
    return AceType::MakeRefPtr<ResourceAdapterImpl>();
}

void ResourceAdapterImpl::Init(const ResourceInfo& resourceInfo)
{
    std::string resPath = resourceInfo.GetPackagePath();
    std::string hapPath = resourceInfo.GetHapPath();
    auto resConfig = ConvertConfigToGlobal(resourceInfo.GetResourceConfiguration());
    std::shared_ptr<Global::Resource::ResourceManager> newResMgr(Global::Resource::CreateResourceManager());
    std::string resIndexPath = hapPath.empty() ? (resPath + "resources.index") : hapPath;
    auto resRet = newResMgr->AddResource(resIndexPath.c_str());
    auto configRet = newResMgr->UpdateResConfig(*resConfig);
    LOGI("AddRes result=%{public}d, UpdateResConfig result=%{public}d, ori=%{public}d, dpi=%{public}d, "
         "device=%{public}d, colorMode=%{publid}d, inputDevice=%{public}d",
        resRet, configRet, resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType(),
        resConfig->GetColorMode(), resConfig->GetInputDevice());
    sysResourceManager_ = newResMgr;
    resourceManager_ = sysResourceManager_;
    packagePathStr_ = IsDirExist(resPath) ? resPath : std::string();
    resConfig_ = resConfig;
}

void ResourceAdapterImpl::UpdateConfig(const ResourceConfiguration& config)
{
    auto resConfig = ConvertConfigToGlobal(config);
    LOGI("UpdateConfig ori=%{public}d, dpi=%{public}d, device=%{public}d, "
        "colorMode=%{publid}d, inputDevice=%{public}d",
        resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType(),
        resConfig->GetColorMode(), resConfig->GetInputDevice());
    sysResourceManager_->UpdateResConfig(*resConfig);
    for (auto& resMgr : resourceManagers_) {
        resMgr.second->UpdateResConfig(*resConfig);
    }
    resConfig_ = resConfig;
}

RefPtr<ThemeStyle> ResourceAdapterImpl::GetTheme(int32_t themeId)
{
    CheckThemeId(themeId);
    auto theme = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    auto ret = resourceManager_->GetThemeById(themeId, theme->rawAttrs_);
    std::string OHFlag = "ohos_"; // fit with resource/base/theme.json and pattern.json
    for (size_t i = 0; i < sizeof(PATTERN_MAP) / sizeof(PATTERN_MAP[0]); i++) {
        ResourceThemeStyle::RawAttrMap attrMap;
        std::string patternTag = PATTERN_MAP[i];
        std::string patternName = OHFlag + PATTERN_MAP[i];
        ret = resourceManager_->GetPatternByName(patternName.c_str(), attrMap);
        LOGD("theme pattern[%{public}s, %{public}s], attr size=%{public}zu",
            patternTag.c_str(), patternName.c_str(), attrMap.size());
        if (attrMap.empty()) {
            continue;
        }
        theme->patternAttrs_[patternTag] = attrMap;
    }
    LOGI("theme themeId=%{public}d, ret=%{public}d, attr size=%{public}zu, pattern size=%{public}zu",
        themeId, ret, theme->rawAttrs_.size(), theme->patternAttrs_.size());
    if (theme->patternAttrs_.empty() && theme->rawAttrs_.empty()) {
        LOGW("theme resource get failed, use default theme config.");
        return nullptr;
    }

    theme->ParseContent();
    theme->patternAttrs_.clear();
    return theme;
}

Color ResourceAdapterImpl::GetColor(uint32_t resId)
{
    uint32_t result = 0;
    if (resourceManager_) {
        auto state = resourceManager_->GetColorById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetColor error, id=%{public}u", resId);
        }
    }
    return Color(result);
}

Dimension ResourceAdapterImpl::GetDimension(uint32_t resId)
{
    float dimensionFloat = 0.0f;
    if (resourceManager_) {
        auto state = resourceManager_->GetFloatById(resId, dimensionFloat);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetDimension error, id=%{public}u", resId);
        }
    }
    return Dimension(static_cast<double>(dimensionFloat));
}

std::string ResourceAdapterImpl::GetString(uint32_t resId)
{
    std::string strResult = "";
    if (resourceManager_) {
        auto state = resourceManager_->GetStringById(resId, strResult);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetString error, id=%{public}u", resId);
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
            LOGE("GetPluralString error, id=%{public}u", resId);
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
            LOGE("GetStringArray error, id=%{public}u", resId);
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
            LOGE("GetDouble error, id=%{public}u", resId);
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
            LOGE("GetInt error, id=%{public}u", resId);
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
            LOGE("GetIntArray error, id=%{public}u", resId);
        }
    }
    std::vector<uint32_t> result;
    std::transform(intVectorResult.begin(), intVectorResult.end(), result.begin(),
        [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

bool ResourceAdapterImpl::GetBoolean(uint32_t resId) const
{
    bool result = false;
    if (resourceManager_) {
        auto state = resourceManager_->GetBooleanById(resId, result);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetBoolean error, id=%{public}u", resId);
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
            LOGE("GetMediaPath error, id=%{public}u", resId);
            return "";
        }
        return "file:///" + mediaPath;
    }
    return "";
}

std::string ResourceAdapterImpl::GetRawfile(const std::string& fileName)
{
    // as web component not support resource format: resource://RAWFILE/{fileName}, use old format
    if (!packagePathStr_.empty()) {
        return "file:///" + packagePathStr_ + "resources/rawfile/" + fileName;
    }
    return "resource://RAWFILE/" + fileName;
}

bool ResourceAdapterImpl::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (resourceManager_ == nullptr) {
        return false;
    }
    auto rawFileObj = std::make_unique<OHOS::Global::Resource::ResourceManager::RawFile>();
    auto state = resourceManager_->GetRawFileFromHap(rawFile, rawFileObj);
    if (state != Global::Resource::SUCCESS || !rawFileObj || !rawFileObj->buffer) {
        LOGE("GetRawFileFromHap error, raw filename:%{public}s, error:%{public}u", rawFile.c_str(), state);
        return false;
    }
    len = rawFileObj->length;
    dest.swap(rawFileObj->buffer);
    return true;
}

bool ResourceAdapterImpl::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]> &dest)
{
    if (resourceManager_ == nullptr) {
        return false;
    }
    auto state = resourceManager_->GetMediaDataById(resId, len, dest);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetMediaDataById error, id=%{public}u, error:%{public}u", resId, state);
        return false;
    }
    return true;
}

bool ResourceAdapterImpl::GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]> &dest)
{
    if (resourceManager_ == nullptr) {
        return false;
    }
    auto state = resourceManager_->GetMediaDataByName(resName.c_str(), len, dest);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetMediaDataByName error, res=%{public}s, error:%{public}u", resName.c_str(), state);
        return false;
    }
    return true;
}

void ResourceAdapterImpl::UpdateResourceManager(const std::string& bundleName, const std::string& moduleName)
{
    if (bundleName.empty() || moduleName.empty()) {
        resourceManager_ = sysResourceManager_;
        return;
    }

    auto resourceMgrIter = resourceManagers_.find({ bundleName, moduleName });
    if (resourceMgrIter != resourceManagers_.end()) {
        resourceManager_ = resourceMgrIter->second;
        return;
    } else {
        auto container = Container::Current();
        if (!container) {
            LOGW("container is null");
            return;
        }

        auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
        if (!aceContainer) {
            LOGW("container's type is not AceContainer.");
            return;
        }

        auto context = aceContainer->GetAbilityContextByModule(bundleName, moduleName);
        if (!context) {
            LOGW("get ability context failed");
            return;
        }
        resourceManagers_[{ bundleName, moduleName }] = context->GetResourceManager();
        resourceManager_ = context->GetResourceManager();
        resourceManager_->UpdateResConfig(*resConfig_);
    }
}

} // namespace OHOS::Ace
