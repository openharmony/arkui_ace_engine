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

#include "core/common/ace_application_info.h"
#include "base/utils/system_properties.h"
#include "resource_manager.h"
#include "rstate.h"

namespace OHOS::Ace {
namespace {
constexpr double DPI_BASE = 160.0;
Global::Resource::DeviceType ConvertDeviceType(DeviceType type)
{
    // TODO: check device type WEARABLE / PC 
    switch (type) {
        case DeviceType::PHONE:
            return Global::Resource::DeviceType::DEVICE_PHONE;
        case DeviceType::TV:
            return Global::Resource::DeviceType::DEVICE_TV;
        case DeviceType::WATCH:
            return Global::Resource::DeviceType::DEVICE_WEARABLE; // CHECK
        case DeviceType::CAR:
            return Global::Resource::DeviceType::DEVICE_CAR;
        case DeviceType::TABLET:
            return Global::Resource::DeviceType::DEVICE_TABLET;
        default:
            return Global::Resource::DeviceType::DEVICE_NOT_SET;
    }
}

Global::Resource::Direction ConvertDirection(DeviceOrientation orientation)
{
    switch (orientation) {
        case DeviceOrientation::PORTRAIT:
            return Global::Resource::Direction::DIRECTION_VERTICAL;
        case DeviceOrientation::LANDSCAPE:
            return Global::Resource::Direction::DIRECTION_HORIZONTAL;
        default:
            return Global::Resource::Direction::DIRECTION_NOT_SET;
    }
}

Global::Resource::ScreenDensity ConvertDensity(double density)
{
    static const std::vector<std::pair<double, Global::Resource::ScreenDensity>> resolutions = {
        { 0.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_NOT_SET },
        { 120.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_SDPI },
        { 160.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_MDPI },
        { 240.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_LDPI },
        { 320.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_XLDPI },
        { 480.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_XXLDPI },
        { 640.0, Global::Resource::ScreenDensity::SCREEN_DENSITY_XXXLDPI },
    };
    double deviceDpi = density * DPI_BASE;
    auto resolution = Global::Resource::ScreenDensity::SCREEN_DENSITY_NOT_SET;
    for (const auto& [dpi, value] : resolutions) {
        resolution = value;
        if (LessOrEqual(deviceDpi, dpi)) {
            break;
        }
    }
    return resolution;
}

std::shared_ptr<Global::Resource::ResConfig> ConvertConfig(const ResourceConfiguration& config)
{
    std::shared_ptr<Global::Resource::ResConfig> newResCfg(Global::Resource::CreateResConfig());
    newResCfg->SetLocaleInfo(AceApplicationInfo::GetInstance().GetLanguage().c_str(), 
        AceApplicationInfo::GetInstance().GetScript().c_str(), AceApplicationInfo::GetInstance().GetCountryOrRegion().c_str());
    newResCfg->SetDeviceType(ConvertDeviceType(config.GetDeviceType()));
    newResCfg->SetDirection(ConvertDirection(config.GetOrientation()));
    newResCfg->SetScreenDensity(ConvertDensity(config.GetDensity()));
    return newResCfg;
}
} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::Create()
{
    auto deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::PHONE || deviceType == DeviceType::CAR) {
        return AceType::MakeRefPtr<ResourceAdapterImpl>();
    }
    return RefPtr<ResourceAdapter>();
}

void ResourceAdapterImpl::Init(const ResourceInfo& resourceInfo)
{
    std::string resPath = resourceInfo.GetPackagePath();
    auto resConfig = ConvertConfig(resourceInfo.GetResourceConfiguration());
    std::shared_ptr<Global::Resource::ResourceManager> newResMgr(Global::Resource::CreateResourceManager());
    std::string resIndxPath = resPath + "resources.index";
    auto resRet = newResMgr->AddResource(resIndxPath.c_str());
    auto configRet = newResMgr->UpdateResConfig(*resConfig);
    LOGI("AddResource result=%{public}d, UpdateResConfig result=%{public}d, ori=%{public}d, dpi=%{public}d, device=%{public}d",
        resRet, configRet, resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType());
    resourceManager_ = newResMgr;
    packagePathStr_ = resPath;
}

void ResourceAdapterImpl::UpdateConfig(const ResourceConfiguration& config)
{
    auto resConfig = ConvertConfig(config);
    LOGI("UpdateConfig ori=%{public}d, dpi=%{public}d, device=%{public}d",
        resConfig->GetDirection(), resConfig->GetScreenDensity(), resConfig->GetDeviceType());
    resourceManager_->UpdateResConfig(*resConfig);
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
    return "file:///" + packagePathStr_ + "resources/rawfile/" + fileName;
}

} // namespace OHOS::Ace
