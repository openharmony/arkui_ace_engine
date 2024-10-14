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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t FILE_SUFFIX_LEN = 4;
constexpr uint32_t APNG_FILE_SUFFIX_LEN = 5;
constexpr uint32_t MAX_BASE64_LENGTH = 50; // prevent the Base64 image format from too long.

bool CheckSvgExtension(const std::string& src)
{
    if (src.size() <= FILE_SUFFIX_LEN) {
        return false;
    }
    auto srcSuffix = src.substr(src.size() - FILE_SUFFIX_LEN);
    StringUtils::TransformStrCase(srcSuffix, StringUtils::TEXT_CASE_LOWERCASE);
    return srcSuffix == ".svg";
}

} // namespace

bool ImageSourceInfo::IsSVGSource(const std::string& src, SrcType srcType, InternalResource::ResourceId resourceId)
{
    // 4 is the length of ".svg".
    if (CheckSvgExtension(src)) {
        return true;
    } else if (srcType == SrcType::NETWORK) {
        size_t queryPos = src.find('?');
        std::string cleanUrl = (queryPos != std::string::npos) ? src.substr(0, queryPos) : src;
        if (CheckSvgExtension(cleanUrl)) {
            return true;
        }
    }
    return (src.empty() && resourceId > InternalResource::ResourceId::SVG_START &&
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
        TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageSourceInfo: wrong base64 head format.");
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
        } else if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*astc.*$")) {
            return SrcType::ASTC;
        } else if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*")) {
            return SrcType::DATA_ABILITY;
        }
        return SrcType::FILE;
    } else if (head == "internal") {
        return SrcType::INTERNAL;
    } else if (head == "data") {
        static constexpr char BASE64_PATTERN[] =
            "^data:image/(jpeg|JPEG|jpg|JPG|png|PNG|ico|ICO|gif|GIF|bmp|BMP|webp|WEBP|heic|heif|HEIF"
            "|sut|astc);base64$";
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
      isPng_(IsPngSource(src_, resourceId_)), srcType_(ResolveSrcType())
{
    isSvg_ = IsSVGSource(src_, srcType_, resourceId_);
    // count how many source set.
    int32_t count = 0;
    if (!src_.empty()) {
        ++count;
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        ++count;
    }
    if (pixmap != nullptr) {
        pixmapBuffer_ = pixmap->GetPixels();
        ++count;
    }
    if (count > 1) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageSourceInfo: multi image source set, only one will be load.");
    }
    GenerateCacheKey();

    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        localColorMode_ = pipelineContext->GetLocalColorMode();
    }
}

ImageSourceInfo::ImageSourceInfo(const std::shared_ptr<std::string>& imageSrc, std::string bundleName,
    std::string moduleName, Dimension width, Dimension height, InternalResource::ResourceId resourceId,
    const RefPtr<PixelMap>& pixmap)
    : srcRef_(imageSrc), bundleName_(std::move(bundleName)), moduleName_(std::move(moduleName)), sourceWidth_(width),
      sourceHeight_(height), resourceId_(resourceId), pixmap_(pixmap), isPng_(IsPngSource(*srcRef_, resourceId_)),
      srcType_(ResolveSrcType())
{
    // count how many source set.
    int32_t count = 0;
    if (srcRef_ && !(*srcRef_).empty()) {
        isSvg_ = IsSVGSource((*srcRef_), srcType_, resourceId_);
        ++count;
    } else {
        isSvg_ = IsSVGSource("", srcType_, resourceId_);
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        ++count;
    }
    if (pixmap != nullptr) {
        pixmapBuffer_ = pixmap->GetPixels();
        ++count;
    }
    if (count > 1) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageSourceInfo: multi image source set, only one will be load.");
    }
    GenerateCacheKey();

    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        localColorMode_ = pipelineContext->GetLocalColorMode();
    }
}

SrcType ImageSourceInfo::ResolveSrcType() const
{
    if (pixmap_) {
        return SrcType::PIXMAP;
    }
    auto& src = GetSrc();
    if (!src.empty()) {
        return ResolveURIType(src);
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        return SrcType::RESOURCE_ID;
    }
    return SrcType::UNSUPPORTED;
}

void ImageSourceInfo::GenerateCacheKey()
{
    auto colorMode = GetColorModeToString();
    auto name = ToString(false) + AceApplicationInfo::GetInstance().GetAbilityName() + bundleName_ + moduleName_;
    cacheKey_ =
        std::to_string(std::hash<std::string> {}(name)) + std::to_string(static_cast<int32_t>(resourceId_)) + colorMode;
    if (srcType_ == SrcType::BASE64) {
        cacheKey_ += "SrcType:BASE64";
    }
}

const std::string ImageSourceInfo::GetColorModeToString()
{
    auto colorMode = SystemProperties::GetColorMode();
    switch (colorMode) {
        case ColorMode::LIGHT:
            return "LIGHT";
        case ColorMode::DARK:
            return "DARK";
        case ColorMode::COLOR_MODE_UNDEFINED:
            return "COLOR_MODE_UNDEFINED";
        default:
            return "LIGHT";
    }
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
    return ((!pixmap_ && !info.pixmap_) ||
               (pixmap_ && info.pixmap_ && pixmapBuffer_ == info.pixmap_->GetPixels())) &&
           GetSrc() == info.GetSrc() && resourceId_ == info.resourceId_;
}

bool ImageSourceInfo::operator!=(const ImageSourceInfo& info) const
{
    return !(operator==(info));
}

void ImageSourceInfo::SetSrc(const std::string& src, std::optional<Color> fillColor)
{
    srcRef_.reset(new std::string(src));
    srcType_ = ResolveURIType(src);
    resourceId_ = InternalResource::ResourceId::NO_ID;
    isSvg_ = IsSVGSource(src, srcType_, resourceId_);
    fillColor_ = fillColor;
    pixmap_ = nullptr;
    GenerateCacheKey();
}

const std::string& ImageSourceInfo::GetSrc() const
{
    if (srcRef_) {
        return *srcRef_;
    }
    return src_;
}

void ImageSourceInfo::SetResourceId(InternalResource::ResourceId id, std::optional<Color> fillColor)
{
    resourceId_ = id;
    srcType_ = SrcType::RESOURCE_ID;
    src_.clear();
    isSvg_ = IsSVGSource(src_, srcType_, resourceId_);
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
    srcRef_.reset();
    isSvg_ = IsSVGSource(src_, srcType_, resourceId_);
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
    return GetSrc().empty() && resourceId_ != InternalResource::ResourceId::NO_ID && !pixmap_;
}

bool ImageSourceInfo::IsValid() const
{
    auto& src = GetSrc();
    return (src.empty() && resourceId_ != InternalResource::ResourceId::NO_ID) ||
           (!src.empty() && resourceId_ == InternalResource::ResourceId::NO_ID) || pixmap_;
}

bool ImageSourceInfo::IsPng() const
{
    return isPng_;
}

bool ImageSourceInfo::IsSvg() const
{
    return isSvg_ && !IsPixmap();
}

bool ImageSourceInfo::IsPixmap() const
{
    return pixmap_ != nullptr || SrcType::DATA_ABILITY_DECODED == srcType_ || SrcType::ASTC == srcType_;
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

std::string ImageSourceInfo::ToString(bool isNeedTruncated) const
{
    auto& src = GetSrc();
    if (!src.empty()) {
        // Check if the src is a base64 image
        if (srcType_ == SrcType::BASE64 && isNeedTruncated) {
            // Return the first 50 characters of the base64 image string
            return src.substr(0, MAX_BASE64_LENGTH) + "...(truncated)";
        }
        return src;
    }
    if (resourceId_ != InternalResource::ResourceId::NO_ID) {
        return std::string("internal resource id: ") + std::to_string(static_cast<int32_t>(resourceId_));
    }
    if (pixmap_) {
        int32_t w = pixmap_->GetWidth();
        int32_t h = pixmap_->GetHeight();
        int32_t totalSize = pixmap_->GetByteCount();
        auto rowStride = pixmap_->GetRowStride();
        return std::string("pixmapID: ") + pixmap_->GetId() + std::string(" -> modifyID: ") + pixmap_->GetModifyId() +
               "details: _w" + std::to_string(w) + "_h" + std::to_string(h) + "_rowStride" + std::to_string(rowStride) +
               "_byteCount" + std::to_string(totalSize);
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
    srcRef_.reset();
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
    if (!needCache_) {
        return false;
    }
    return !GetSrc().empty() || resourceId_ != InternalResource::ResourceId::NO_ID;
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
