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

#include "core/common/resource/resource_wrapper.h"

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

ResourceWrapper::ResourceWrapper(RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter)
    : themeConstants_(themeConstants), resourceAdapter_(resourceAdapter)
{
    if (!themeConstants_ && !resourceAdapter_) {
        TAG_LOGW(AceLogTag::ACE_RESOURCE, "ThemeConstants and ResourceAdapter are both nullptr.");
    }
}

ResourceWrapper::ResourceWrapper(
    RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter, ColorMode colorMode)
    : themeConstants_(themeConstants), resourceAdapter_(resourceAdapter), localColorMode_(colorMode)
{
    if (resourceAdapter && colorMode != ColorMode::COLOR_MODE_UNDEFINED) {
        resourceAdapter->UpdateColorMode(colorMode);
    }
}

ResourceWrapper::~ResourceWrapper()
{
    if (localColorMode_ != ColorMode::COLOR_MODE_UNDEFINED) {
        resourceAdapter_->UpdateColorMode(Container::CurrentColorMode());
    }
}

Color ResourceWrapper::GetColor(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, Color());
        return resourceAdapter_->GetColor(key);
    }
    CHECK_NULL_RETURN(themeConstants_, Color());
    return themeConstants_->GetColor(key);
}

Color ResourceWrapper::GetColorByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, Color());
        return resourceAdapter_->GetColorByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, Color());
    return themeConstants_->GetColorByName(resName);
}

Dimension ResourceWrapper::GetDimension(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, Dimension());
        return resourceAdapter_->GetDimension(key);
    }
    CHECK_NULL_RETURN(themeConstants_, Dimension());
    return themeConstants_->GetDimension(key);
}

Dimension ResourceWrapper::GetDimensionByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, Dimension());
        return resourceAdapter_->GetDimensionByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, Dimension());
    return themeConstants_->GetDimensionByName(resName);
}

int32_t ResourceWrapper::GetInt(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0);
        return resourceAdapter_->GetInt(key);
    }
    CHECK_NULL_RETURN(themeConstants_, 0);
    return themeConstants_->GetInt(key);
}

int32_t ResourceWrapper::GetIntByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0);
        return resourceAdapter_->GetIntByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, 0);
    return themeConstants_->GetIntByName(resName);
}

double ResourceWrapper::GetDouble(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0.0f);
        return resourceAdapter_->GetDouble(key);
    }
    CHECK_NULL_RETURN(themeConstants_, 0.0f);
    return themeConstants_->GetDouble(key);
}

double ResourceWrapper::GetDoubleByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0.0f);
        return resourceAdapter_->GetDoubleByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, 0.0f);
    return themeConstants_->GetDoubleByName(resName);
}

std::string ResourceWrapper::GetString(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetString(key);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetString(key);
}

std::string ResourceWrapper::GetStringByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetStringByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetStringByName(resName);
}

std::string ResourceWrapper::GetPluralString(uint32_t key, int count) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetPluralString(key, count);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetPluralString(key, count);
}

std::string ResourceWrapper::GetPluralStringByName(const std::string& resName, int count) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetPluralStringByName(resName, count);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetPluralStringByName(resName, count);
}

bool ResourceWrapper::GetBoolean(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetBoolean(key);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetBoolean(key);
}

bool ResourceWrapper::GetBooleanByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetBooleanByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetBooleanByName(resName);
}

std::vector<uint32_t> ResourceWrapper::GetIntArray(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, std::vector<uint32_t>());
        return resourceAdapter_->GetIntArray(key);
    }
    CHECK_NULL_RETURN(themeConstants_, std::vector<uint32_t>());
    return themeConstants_->GetIntArray(key);
}

std::vector<uint32_t> ResourceWrapper::GetIntArrayByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, std::vector<uint32_t>());
        return resourceAdapter_->GetIntArrayByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, std::vector<uint32_t>());
    return themeConstants_->GetIntArrayByName(resName);
}

std::shared_ptr<Media::PixelMap> ResourceWrapper::GetPixelMap(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, nullptr);
        return resourceAdapter_->GetPixelMap(key);
    }
    CHECK_NULL_RETURN(themeConstants_, nullptr);
    return themeConstants_->GetPixelMap(key);
}

std::vector<std::string> ResourceWrapper::GetStringArray(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, std::vector<std::string>());
        return resourceAdapter_->GetStringArray(key);
    }
    CHECK_NULL_RETURN(themeConstants_, std::vector<std::string>());
    return themeConstants_->GetStringArray(key);
}

std::vector<std::string> ResourceWrapper::GetStringArrayByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, std::vector<std::string>());
        return resourceAdapter_->GetStringArrayByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, std::vector<std::string>());
    return themeConstants_->GetStringArrayByName(resName);
}

std::string ResourceWrapper::GetMediaPath(uint32_t key) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetMediaPath(key);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetMediaPath(key);
}

std::string ResourceWrapper::GetMediaPathByName(const std::string& resName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetMediaPathByName(resName);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetMediaPathByName(resName);
}

std::string ResourceWrapper::GetRawfile(const std::string& fileName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, "");
        return resourceAdapter_->GetRawfile(fileName);
    }
    CHECK_NULL_RETURN(themeConstants_, "");
    return themeConstants_->GetRawfile(fileName);
}

bool ResourceWrapper::GetRawFileDescription(
    const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetRawFileDescription(rawfileName, rawfileDescription);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetRawFileDescription(rawfileName, rawfileDescription);
}

bool ResourceWrapper::CloseRawFileDescription(const std::string& rawfileName) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->CloseRawFileDescription(rawfileName);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->CloseRawFileDescription(rawfileName);
}

bool ResourceWrapper::GetRawFD(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetRawFD(rawfileName, rawfileDescription);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetRawFD(rawfileName, rawfileDescription);
}

bool ResourceWrapper::GetMediaById(const int32_t& resId, std::string& mediaPath) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetMediaById(resId, mediaPath);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetMediaById(resId, mediaPath);
}

template<class T>
bool ResourceWrapper::GetMediaResource(T& resId, std::ostream& dest) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetResource(resId, dest);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetMediaResource<T>(resId, dest);
}

template<class T>
bool ResourceWrapper::GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetMediaData(resId, len, dest);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetMediaData<T>(resId, len, dest);
}

template<class T>
bool ResourceWrapper::GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetMediaData(resId, len, dest, bundleName, moduleName);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetMediaData<T>(resId, len, dest, bundleName, moduleName);
}

bool ResourceWrapper::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetRawFileData(rawFile, len, dest);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetRawFileData(rawFile, len, dest);
}

bool ResourceWrapper::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
}

bool ResourceWrapper::GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, false);
        return resourceAdapter_->GetIdByName(resName, resType, resId);
    }
    CHECK_NULL_RETURN(themeConstants_, false);
    return themeConstants_->GetResourceIdByName(resName, resType, resId);
}

uint32_t ResourceWrapper::GetSymbolByName(const char* name) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0);
        return resourceAdapter_->GetSymbolByName(name);
    }
    CHECK_NULL_RETURN(themeConstants_, 0);
    return themeConstants_->GetSymbolByName(name);
}

uint32_t ResourceWrapper::GetSymbolById(uint32_t resId) const
{
    if (SystemProperties::GetResourceDecoupling()) {
        CHECK_NULL_RETURN(resourceAdapter_, 0);
        return resourceAdapter_->GetSymbolById(resId);
    }
    CHECK_NULL_RETURN(themeConstants_, 0);
    return themeConstants_->GetSymbolById(resId);
}

void ResourceWrapper::UpdateColorMode(ColorMode colorMode)
{
    CHECK_NULL_VOID(resourceAdapter_);
    resourceAdapter_->UpdateColorMode(colorMode);
}

const RefPtr<ResourceAdapter>& ResourceWrapper::GetResourceAdapter() const
{
    return resourceAdapter_;
}

template bool ResourceWrapper::GetMediaResource(uint32_t&, std::ostream&) const;
template bool ResourceWrapper::GetMediaResource(std::string&, std::ostream&) const;
template bool ResourceWrapper::GetMediaData(uint32_t&, size_t&, std::unique_ptr<uint8_t[]>&);
template bool ResourceWrapper::GetMediaData(std::string&, size_t&, std::unique_ptr<uint8_t[]>&);
template bool ResourceWrapper::GetMediaData(
    uint32_t&, size_t&, std::unique_ptr<uint8_t[]>&, const std::string&, const std::string&);
template bool ResourceWrapper::GetMediaData(
    std::string&, size_t&, std::unique_ptr<uint8_t[]>&, const std::string&, const std::string&);

} // namespace OHOS::Ace
