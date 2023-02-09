/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <utility>

#include "core/image/image_source_info.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
namespace {
constexpr uint32_t FILE_SUFFIX_LEN = 4;
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
    return false;
}

bool ImageSourceInfo::IsValidBase64Head(const std::string& uri, const std::string& pattern)
{
    return true;
}

bool ImageSourceInfo::IsUriOfDataAbilityEncoded(const std::string& uri, const std::string& pattern)
{
    return true;
}

SrcType ImageSourceInfo::ResolveURIType(const std::string& uri)
{
    return SrcType::FILE;
}

ImageSourceInfo::ImageSourceInfo(std::string imageSrc, Dimension width, Dimension height,
    InternalResource::ResourceId resourceId, const RefPtr<PixelMap>& pixmap)
    : src_(std::move(imageSrc)), sourceWidth_(width), sourceHeight_(height), resourceId_(resourceId), pixmap_(pixmap),
      isSvg_(IsSVGSource(src_, resourceId_)), isPng_(IsPngSource(src_, resourceId_)), srcType_(ResolveSrcType())
{}

SrcType ImageSourceInfo::ResolveSrcType() const
{
    return SrcType::FILE;
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
    if (sourceWidth_ != info.sourceWidth_ || sourceHeight_ != info.sourceHeight_) {
        return false;
    }
    return ((!pixmap_ && !info.pixmap_) || (pixmap_ && info.pixmap_ && pixmap_ == info.pixmap_)) && src_ == info.src_ &&
           resourceId_ == info.resourceId_;
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
}

InternalResource::ResourceId ImageSourceInfo::GetResourceId() const
{
    return resourceId_;
}

void ImageSourceInfo::SetPixMap(const RefPtr<PixelMap>& pixmap, std::optional<Color> fillColor) {}

bool ImageSourceInfo::IsInternalResource() const
{
    return src_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID && !pixmap_;
}

bool ImageSourceInfo::IsValid() const
{
    return true;
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
    return true;
}

SrcType ImageSourceInfo::GetSrcType() const
{
    return srcType_;
}

std::string ImageSourceInfo::ToString() const
{
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

void ImageSourceInfo::Reset() {}

const std::optional<Color>& ImageSourceInfo::GetFillColor() const
{
    return fillColor_;
}

const RefPtr<PixelMap>& ImageSourceInfo::GetPixmap() const
{
    return pixmap_;
}

std::string ImageSourceInfo::GetKey() const
{
    return std::string("");
}

bool ImageSourceInfo::IsSupportCache() const
{
    return false;
}
} // namespace OHOS::Ace
