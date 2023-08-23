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

#include "core/image/image_source_info.h"

#include <regex>

#include "core/common/container.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t FILE_SUFFIX_LEN = 4;
constexpr uint32_t APNG_FILE_SUFFIX_LEN = 5;

} // namespace

bool ImageSourceInfo::IsSVGSource(const std::string& src, InternalResource::ResourceId resourceId)
{
    // 4 is the length of ".svg".
    return (src.size() > FILE_SUFFIX_LEN && src.substr(src.size() - FILE_SUFFIX_LEN) == ".svg") ||
           (src.empty() && resourceId > InternalResource::ResourceId::SVG_START &&
               resourceId < InternalResource::ResourceId::SVG_END);
}

bool ImageSourceInfo::IsPngSource(const std::string& src, InternalResource::ResourceId resourceId)
{
    // 4 is the length of ".png" or is .apng
    if (!src.empty()) {
        std::string head = src.size() > APNG_FILE_SUFFIX_LEN
                               ? src.substr(src.size() - APNG_FILE_SUFFIX_LEN, APNG_FILE_SUFFIX_LEN)
                           : src.size() == 4 ? src.substr(src.size() - FILE_SUFFIX_LEN, FILE_SUFFIX_LEN)
                                             : "";
        std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });

        return (head.size() > FILE_SUFFIX_LEN && head.substr(head.size() - FILE_SUFFIX_LEN) == ".png") ||
               (head.size() > APNG_FILE_SUFFIX_LEN && head.substr(head.size() - APNG_FILE_SUFFIX_LEN) == ".apng");
    } else if (resourceId < InternalResource::ResourceId::SVG_START) {
        return true;
    }
    return false;
}

bool ImageSourceInfo::IsValidBase64Head(const std::string& uri, const std::string& pattern)
{
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos) {
        LOGE("wrong base64 head format.");
        return false;
    }
    std::string base64Head = uri.substr(0, iter);
    std::regex regular(pattern);
    return std::regex_match(base64Head, regular);
}

bool ImageSourceInfo::IsUriOfDataAbilityEncoded(const std::string& uri, const std::string& pattern)
{
    std::regex regular(pattern);
    return std::regex_match(uri, regular);
}

SrcType ImageSourceInfo::ResolveURIType(const std::string& uri)
{
    if (uri.empty()) {
        return SrcType::UNSUPPORTED;
    }
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        return SrcType::ASSET;
    }
    std::string head = uri.substr(0, iter);
    std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });
    if (head == "http" || head == "https") {
        return SrcType::NETWORK;
    } else if (head == "file") {
        if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*thumbnail.*$")) {
            return SrcType::DATA_ABILITY_DECODED;
        } else if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*")) {
            return SrcType::DATA_ABILITY;
        }
        return SrcType::FILE;
    } else if (head == "internal") {
        return SrcType::INTERNAL;
    } else if (head == "data") {
        static constexpr char BASE64_PATTERN[] =
            "^data:image/(jpeg|JPEG|jpg|JPG|png|PNG|ico|ICO|gif|GIF|bmp|BMP|webp|WEBP);base64$";
        if (IsValidBase64Head(uri, BASE64_PATTERN)) {
            return SrcType::BASE64;
        }
        return SrcType::UNSUPPORTED;
    } else if (head == "memory") {
        return SrcType::MEMORY;
    } else if (head == "resource") {
        return SrcType::RESOURCE;
    } else if (head == "dataability" || head == "datashare") {
        if (IsUriOfDataAbilityEncoded(uri, "^dataability://.*?/media/.*thumbnail.*$") ||
            IsUriOfDataAbilityEncoded(uri, "^datashare://.*?/media/.*thumbnail.*$")) {
            return SrcType::DATA_ABILITY_DECODED;
        }
        return SrcType::DATA_ABILITY;
    } else {
        return SrcType::UNSUPPORTED;
    }
}

// add constructor method for decompressed hap
ImageSourceInfo::ImageSourceInfo(std::string imageSrc, std::string bundleName, std::string moduleName, Dimension width,
    Dimension height, InternalResource::ResourceId resourceId, const RefPtr<PixelMap>& pixmap)
    : src_(std::move(imageSrc)), bundleName_(std::move(bundleName)), moduleName_(std::move(moduleName)),
      sourceWidth_(width), sourceHeight_(height), resourceId_(resourceId), pixmap_(pixmap),
      isSvg_(IsSVGSource(src_, resourceId_)), isPng_(IsPngSource(src_, resourceId_)), srcType_(ResolveSrcType())
{
    // count how many source set.
    int32_t count = 0;
    if (!src_.empty()) {
        ++count;
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        ++count;
    }
    if (pixmap != nullptr) {
        ++count;
    }
    if (count > 1) {
        LOGW("multi image source set, only one will be load.");
    }
    GenerateCacheKey();
}

SrcType ImageSourceInfo::ResolveSrcType() const
{
    if (pixmap_) {
        return SrcType::PIXMAP;
    }
    if (!src_.empty()) {
        return ResolveURIType(src_);
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        return SrcType::RESOURCE_ID;
    }
    return SrcType::UNSUPPORTED;
}

void ImageSourceInfo::GenerateCacheKey()
{
    auto name = ToString() + AceApplicationInfo::GetInstance().GetAbilityName() + bundleName_ + moduleName_;
    cacheKey_ = std::to_string(std::hash<std::string> {}(name)) + std::to_string(static_cast<int32_t>(resourceId_));
}

void ImageSourceInfo::SetFillColor(const Color& color)
{
    fillColor_.emplace(color.GetValue());
}

bool ImageSourceInfo::operator==(const ImageSourceInfo& info) const
{
    // only svg uses fillColor
    if (isSvg_ && fillColor_ != info.fillColor_) {
        return false;
    }
    return ((!pixmap_ && !info.pixmap_) || (pixmap_ && info.pixmap_ && pixmap_ == info.pixmap_)) &&
           src_ == info.src_ && resourceId_ == info.resourceId_;
}

bool ImageSourceInfo::operator!=(const ImageSourceInfo& info) const
{
    return !(operator==(info));
}

void ImageSourceInfo::SetSrc(const std::string& src, std::optional<Color> fillColor)
{
    src_ = src;
    srcType_ = ResolveURIType(src_);
    resourceId_ = InternalResource::ResourceId::NO_ID;
    isSvg_ = IsSVGSource(src_, resourceId_);
    fillColor_ = fillColor;
    pixmap_ = nullptr;
    GenerateCacheKey();
}

const std::string& ImageSourceInfo::GetSrc() const
{
    return src_;
}

void ImageSourceInfo::SetResourceId(InternalResource::ResourceId id, std::optional<Color> fillColor)
{
    resourceId_ = id;
    srcType_ = SrcType::RESOURCE_ID;
    src_.clear();
    isSvg_ = IsSVGSource(src_, resourceId_);
    fillColor_ = fillColor;
    pixmap_ = nullptr;
    GenerateCacheKey();
}

InternalResource::ResourceId ImageSourceInfo::GetResourceId() const
{
    return resourceId_;
}

void ImageSourceInfo::SetPixMap(const RefPtr<PixelMap>& pixmap, std::optional<Color> fillColor)
{
    resourceId_ = InternalResource::ResourceId::NO_ID;
    srcType_ = SrcType::PIXMAP;
    src_.clear();
    isSvg_ = IsSVGSource(src_, resourceId_);
    fillColor_ = fillColor;
    pixmap_ = pixmap;
}

void ImageSourceInfo::SetBundleName(const std::string& bundleName)
{
    bundleName_ = bundleName;
}

void ImageSourceInfo::SetModuleName(const std::string& moduleName)
{
    moduleName_ = moduleName;
}

bool ImageSourceInfo::IsInternalResource() const
{
    return src_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID && !pixmap_;
}

bool ImageSourceInfo::IsValid() const
{
    return (src_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID) ||
           (!src_.empty() && resourceId_ == InternalResource::ResourceId::NO_ID) || pixmap_;
}

bool ImageSourceInfo::IsPng() const
{
    return isPng_;
}

bool ImageSourceInfo::IsSvg() const
{
    return isSvg_;
}

bool ImageSourceInfo::IsPixmap() const
{
    return pixmap_ != nullptr || SrcType::DATA_ABILITY_DECODED == srcType_;
}

const std::string& ImageSourceInfo::GetBundleName() const
{
    return bundleName_;
}

const std::string& ImageSourceInfo::GetModuleName() const
{
    return moduleName_;
}

SrcType ImageSourceInfo::GetSrcType() const
{
    return srcType_;
}

std::string ImageSourceInfo::ToString() const
{
    if (!src_.empty()) {
        return src_;
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        return std::string("internal resource id: ") + std::to_string(static_cast<int32_t>(resourceId_));
    }
    if (pixmap_) {
        return std::string("pixmapID: ") + pixmap_->GetId() + std::string(" -> modifyID: ") + pixmap_->GetModifyId();
    }
    return std::string("empty source");
}

void ImageSourceInfo::SetDimension(Dimension width, Dimension Height)
{
    sourceWidth_ = width;
    sourceHeight_ = Height;
}

bool ImageSourceInfo::IsSourceDimensionValid() const
{
    return sourceWidth_.IsValid() && sourceHeight_.IsValid();
}

Size ImageSourceInfo::GetSourceSize() const
{
    return Size(sourceWidth_.Value(), sourceHeight_.Value());
}

void ImageSourceInfo::Reset()
{
    src_.clear();
    sourceWidth_ = Dimension(-1);
    sourceHeight_ = Dimension(-1);
    resourceId_ = InternalResource::ResourceId::NO_ID;
    isSvg_ = false;
    fillColor_.reset();
    pixmap_ = nullptr;
    cacheKey_.clear();
}

const std::optional<Color>& ImageSourceInfo::GetFillColor() const
{
    return fillColor_;
}

const RefPtr<PixelMap>& ImageSourceInfo::GetPixmap() const
{
    return pixmap_;
}

bool ImageSourceInfo::SupportObjCache() const
{
    if (IsPixmap()) {
        return false;
    }
    return !src_.empty() || resourceId_ != InternalResource::ResourceId::NO_ID;
}

std::string ImageSourceInfo::GetKey() const
{
    // only svg sets fillColor
    if (isSvg_ && fillColor_.has_value()) {
        return cacheKey_ + fillColor_.value().ColorToString();
    }
    return cacheKey_;
}

} // namespace OHOS::Ace
