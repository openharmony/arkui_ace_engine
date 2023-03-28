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
#include "base/utils/utils.h"
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
    THEME_PATTERN_ICON,
    THEME_PATTERN_INDEXER,
    THEME_PATTERN_APP_BAR,
};

bool IsDirExist(const std::string& path)
{
    char realPath[PATH_MAX] = { 0x00 };
    CHECK_NULL_RETURN_NOLOG(realpath(path.c_str(), realPath), false);
    DIR* dir = opendir(realPath);
    CHECK_NULL_RETURN_NOLOG(dir, false);
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
    LOGI("AddRes result=%{public}d, UpdateResConfig result=%{public}d, ori=%{public}d, dpi=%{public}f, "
         "device=%{public}d, colorMode=%{publid}d, inputDevice=%{public}d",
        resRet, configRet, resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType(),
        resConfig->GetColorMode(), resConfig->GetInputDevice());
    sysResourceManager_ = newResMgr;
    {
        std::unique_lock<std::shared_mutex> lock(resourceMutex_);
        resourceManager_ = sysResourceManager_;
    }
    packagePathStr_ = (hapPath.empty() || IsDirExist(resPath)) ? resPath : std::string();
    resConfig_ = resConfig;
}

void ResourceAdapterImpl::Reload()
{
    std::string resIndexPath = packagePathStr_ + "resources.index";
    auto resRet = sysResourceManager_->AddResource(resIndexPath.c_str());
    auto configRet = sysResourceManager_->UpdateResConfig(*resConfig_);
    LOGI("UICast result=%{public}d, UpdateResConfig result=%{public}d", resRet, configRet);
}

void ResourceAdapterImpl::UpdateConfig(const ResourceConfiguration& config)
{
    auto resConfig = ConvertConfigToGlobal(config);
    LOGI("UpdateConfig ori=%{public}d, dpi=%{public}f, device=%{public}d, "
        "colorMode=%{publid}d, inputDevice=%{public}d",
        resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType(),
        resConfig->GetColorMode(), resConfig->GetInputDevice());
    if (sysResourceManager_) {
        sysResourceManager_->UpdateResConfig(*resConfig);
    }
    for (auto& resMgr : resourceManagers_) {
        resMgr.second->UpdateResConfig(*resConfig);
    }
    resConfig_ = resConfig;
}

RefPtr<ThemeStyle> ResourceAdapterImpl::GetTheme(int32_t themeId)
{
    CheckThemeId(themeId);
    auto theme = AceType::MakeRefPtr<ResourceThemeStyle>(AceType::Claim(this));
    constexpr char OHFlag[] = "ohos_"; // fit with resource/base/theme.json and pattern.json
    {
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        if (resourceManager_) {
            auto ret = resourceManager_->GetThemeById(themeId, theme->rawAttrs_);
            for (size_t i = 0; i < sizeof(PATTERN_MAP) / sizeof(PATTERN_MAP[0]); i++) {
                ResourceThemeStyle::RawAttrMap attrMap;
                std::string patternTag = PATTERN_MAP[i];
                std::string patternName = std::string(OHFlag) + PATTERN_MAP[i];
                ret = resourceManager_->GetPatternByName(patternName.c_str(), attrMap);
                LOGD("theme pattern[%{public}s, %{public}s], attr size=%{public}zu", patternTag.c_str(),
                    patternName.c_str(), attrMap.size());
                if (attrMap.empty()) {
                    continue;
                }
                theme->patternAttrs_[patternTag] = attrMap;
            }
            LOGI("themeId=%{public}d, ret=%{public}d, attr size=%{public}zu, pattern size=%{public}zu", themeId, ret,
                theme->rawAttrs_.size(), theme->patternAttrs_.size());
        }
    }

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
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, Color(result));
    auto state = resourceManager_->GetColorById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetColor error, id=%{public}u", resId);
    }
    return Color(result);
}

Color ResourceAdapterImpl::GetColorByName(const std::string& resName)
{
    uint32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, Color(result));
    auto state = resourceManager_->GetColorByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetColor error, resName=%{public}s", resName.c_str());
    }
    return Color(result);
}

Dimension ResourceAdapterImpl::GetDimension(uint32_t resId)
{
    if (Container::IsCurrentUseNewPipeline()) {
        float dimensionFloat = 0.0f;
        std::string unit;
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        if (resourceManager_) {
            auto state = resourceManager_->GetFloatById(resId, dimensionFloat, unit);
            if (state != Global::Resource::SUCCESS) {
                LOGE("NG: GetDimension error, id=%{public}u", resId);
            }
        }
        return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
    }

    float dimensionFloat = 0.0f;

    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, Dimension(static_cast<double>(dimensionFloat)));
    auto state = resourceManager_->GetFloatById(resId, dimensionFloat);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetDimension error, id=%{public}u", resId);
    }
    return Dimension(static_cast<double>(dimensionFloat));
}

Dimension ResourceAdapterImpl::GetDimensionByName(const std::string& resName)
{
    float dimensionFloat = 0.0f;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, Dimension());
    std::string unit;
    auto state = resourceManager_->GetFloatByName(actualResName.c_str(), dimensionFloat, unit);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetDimension error, resName=%{public}s", resName.c_str());
    }
    return Dimension(static_cast<double>(dimensionFloat), ParseDimensionUnit(unit));
}

std::string ResourceAdapterImpl::GetString(uint32_t resId)
{
    std::string strResult = "";
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResult);
    auto state = resourceManager_->GetStringById(resId, strResult);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetString error, id=%{public}u", resId);
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetStringByName(const std::string& resName)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResult);
    auto state = resourceManager_->GetStringByName(actualResName.c_str(), strResult);
    if (state != Global::Resource::SUCCESS) {
        LOGD("GetString error, resName=%{public}s", resName.c_str());
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetPluralString(uint32_t resId, int quantity)
{
    std::string strResult = "";
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResult);
    auto state = resourceManager_->GetPluralStringById(resId, quantity, strResult);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetPluralString error, id=%{public}u", resId);
    }
    return strResult;
}

std::string ResourceAdapterImpl::GetPluralStringByName(const std::string& resName, int quantity)
{
    std::string strResult = "";
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResult);
    auto state = resourceManager_->GetPluralStringByName(actualResName.c_str(), quantity, strResult);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetPluralString error, resName=%{public}s", resName.c_str());
    }
    return strResult;
}

std::vector<std::string> ResourceAdapterImpl::GetStringArray(uint32_t resId) const
{
    std::vector<std::string> strResults;
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResults);
    auto state = resourceManager_->GetStringArrayById(resId, strResults);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetStringArray error, id=%{public}u", resId);
    }
    return strResults;
}

std::vector<std::string> ResourceAdapterImpl::GetStringArrayByName(const std::string& resName) const
{
    std::vector<std::string> strResults;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, strResults);
    auto state = resourceManager_->GetStringArrayByName(actualResName.c_str(), strResults);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetStringArray error, resName=%{public}s", resName.c_str());
    }
    return strResults;
}

double ResourceAdapterImpl::GetDouble(uint32_t resId)
{
    float result = 0.0f;
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, static_cast<double>(result));
    auto state = resourceManager_->GetFloatById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetDouble error, id=%{public}u", resId);
    }
    return static_cast<double>(result);
}

double ResourceAdapterImpl::GetDoubleByName(const std::string& resName)
{
    float result = 0.0f;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, static_cast<double>(result));
    auto state = resourceManager_->GetFloatByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetDouble error, resName=%{public}s", resName.c_str());
    }
    return static_cast<double>(result);
}

int32_t ResourceAdapterImpl::GetInt(uint32_t resId)
{
    int32_t result = 0;
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, result);
    auto state = resourceManager_->GetIntegerById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetInt error, id=%{public}u", resId);
    }
    return result;
}

int32_t ResourceAdapterImpl::GetIntByName(const std::string& resName)
{
    int32_t result = 0;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, result);
    auto state = resourceManager_->GetIntegerByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetInt error, resName=%{public}s", resName.c_str());
    }
    return result;
}

std::vector<uint32_t> ResourceAdapterImpl::GetIntArray(uint32_t resId) const
{
    std::vector<int> intVectorResult;
    {
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        if (resourceManager_) {
            auto state = resourceManager_->GetIntArrayById(resId, intVectorResult);
            if (state != Global::Resource::SUCCESS) {
                LOGE("GetIntArray error, id=%{public}u", resId);
            }
        }
    }

    std::vector<uint32_t> result;
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

std::vector<uint32_t> ResourceAdapterImpl::GetIntArrayByName(const std::string& resName) const
{
    std::vector<int> intVectorResult;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, {});
    auto state = resourceManager_->GetIntArrayByName(actualResName.c_str(), intVectorResult);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetIntArray error, resName=%{public}s", resName.c_str());
    }

    std::vector<uint32_t> result;
    std::transform(
        intVectorResult.begin(), intVectorResult.end(), result.begin(), [](int x) { return static_cast<uint32_t>(x); });
    return result;
}

bool ResourceAdapterImpl::GetBoolean(uint32_t resId) const
{
    bool result = false;
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, result);
    auto state = resourceManager_->GetBooleanById(resId, result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetBoolean error, id=%{public}u", resId);
    }
    return result;
}

bool ResourceAdapterImpl::GetBooleanByName(const std::string& resName) const
{
    bool result = false;
    auto actualResName = GetActualResourceName(resName);
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, result);
    auto state = resourceManager_->GetBooleanByName(actualResName.c_str(), result);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetBoolean error, resName=%{public}s", resName.c_str());
    }
    return result;
}

std::string ResourceAdapterImpl::GetMediaPath(uint32_t resId)
{
    CHECK_NULL_RETURN_NOLOG(resourceManager_, "");
    std::string mediaPath = "";
    {
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        auto state = resourceManager_->GetMediaById(resId, mediaPath);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetMediaById error, id=%{public}u, errorCode=%{public}u", resId, state);
            return "";
        }
    }
    if (SystemProperties::GetUnZipHap()) {
        return "file:///" + mediaPath;
    }
    auto pos = mediaPath.find_last_of('.');
    if (pos == std::string::npos) {
        LOGE("GetMediaById error, return mediaPath[%{private}s] format error", mediaPath.c_str());
        return "";
    }
    return "resource:///" + std::to_string(resId) + mediaPath.substr(pos);
}

std::string ResourceAdapterImpl::GetMediaPathByName(const std::string& resName)
{
    std::string mediaPath = "";
    auto actualResName = GetActualResourceName(resName);
    {
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        CHECK_NULL_RETURN_NOLOG(resourceManager_, "");
        auto state = resourceManager_->GetMediaByName(actualResName.c_str(), mediaPath);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetMediaPathByName error, resName=%{public}s, errorCode=%{public}u", resName.c_str(), state);
            return "";
        }
    }
    if (SystemProperties::GetUnZipHap()) {
        return "file:///" + mediaPath;
    }
    auto pos = mediaPath.find_last_of('.');
    if (pos == std::string::npos) {
        LOGE("GetMediaById error, return mediaPath[%{private}s] format error", mediaPath.c_str());
        return "";
    }
    return "resource:///" + actualResName + mediaPath.substr(pos);
}

std::string ResourceAdapterImpl::GetRawfile(const std::string& fileName)
{
    // as web component not support resource format: resource://RAWFILE/{fileName}, use old format
    if (!packagePathStr_.empty()) {
        std::string outPath;
        std::shared_lock<std::shared_mutex> lock(resourceMutex_);
        CHECK_NULL_RETURN_NOLOG(resourceManager_, "");
        // Adapt to the input like: "file:///index.html?a=1", before the new solution comes.
        auto it = std::find_if(fileName.begin(), fileName.end(), [](char c) {
            return (c == '#') || (c == '?');
        });
        std::string params;
        std::string newFileName = fileName;
        if (it != fileName.end()) {
            newFileName = std::string(fileName.begin(), it);
            params = std::string(it, fileName.end());
        }
        auto state = resourceManager_->GetRawFilePathByName(newFileName, outPath);
        if (state != Global::Resource::SUCCESS) {
            LOGE("GetRawfile error, filename:%{public}s, error:%{public}u", fileName.c_str(), state);
            return "";
        }
        return "file:///" + outPath + params;
    }
    return "resource://RAWFILE/" + fileName;
}

bool ResourceAdapterImpl::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, false);
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

bool ResourceAdapterImpl::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, false);
    auto state = resourceManager_->GetMediaDataById(resId, len, dest);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetMediaDataById error, id=%{public}u, error:%{public}u", resId, state);
        return false;
    }
    return true;
}

bool ResourceAdapterImpl::GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    std::shared_lock<std::shared_mutex> lock(resourceMutex_);
    CHECK_NULL_RETURN_NOLOG(resourceManager_, false);
    auto state = resourceManager_->GetMediaDataByName(resName.c_str(), len, dest);
    if (state != Global::Resource::SUCCESS) {
        LOGE("GetMediaDataByName error, res=%{public}s, error:%{public}u", resName.c_str(), state);
        return false;
    }
    return true;
}

void ResourceAdapterImpl::UpdateResourceManager(const std::string& bundleName, const std::string& moduleName)
{
    std::unique_lock<std::shared_mutex> lcok(resourceMutex_);
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
        CHECK_NULL_VOID(container);
        auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
        CHECK_NULL_VOID(aceContainer);
        auto context = aceContainer->GetAbilityContextByModule(bundleName, moduleName);
        CHECK_NULL_VOID(context);
        resourceManagers_[{ bundleName, moduleName }] = context->GetResourceManager();
        resourceManager_ = context->GetResourceManager();
        if (resourceManager_) {
            resourceManager_->UpdateResConfig(*resConfig_);
        }
    }
}

std::string ResourceAdapterImpl::GetActualResourceName(const std::string& resName) const
{
    auto index = resName.find_last_of('.');
    if (index == std::string::npos) {
        LOGE("GetActualResourceName error, incorrect resName format.");
        return "";
    }
    return resName.substr(index + 1, resName.length() - index - 1);
}

} // namespace OHOS::Ace
