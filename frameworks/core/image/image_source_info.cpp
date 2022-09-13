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

#include "core/image/image_source_info.h"
#include <regex>

#include "core/common/container.h"

namespace OHOS::Ace {

constexpr uint32_t FILE_SUFFIX_LEN = 4;
constexpr uint32_t APNG_FILE_SUFFIX_LEN = 5;
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
    if(!src.empty()){
        std::string head = src.size() > APNG_FILE_SUFFIX_LEN ? src.substr(src.size() - APNG_FILE_SUFFIX_LEN,
            APNG_FILE_SUFFIX_LEN) : src.size() == 4 ? src.substr(src.size() - FILE_SUFFIX_LEN, FILE_SUFFIX_LEN) : "";
        std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });

        return (head.size() > FILE_SUFFIX_LEN && head.substr(head.size() - FILE_SUFFIX_LEN) == ".png") ||
               (head.size() > APNG_FILE_SUFFIX_LEN && head.substr(head.size() - APNG_FILE_SUFFIX_LEN) == ".apng");
    }
    else if(resourceId < InternalResource::ResourceId::SVG_START)
        return true;
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
        return SrcType::FILE;
    } else if (head == "internal") {
        return SrcType::INTERNAL;
    } else if (head == "data") {
        static constexpr char BASE64_PATTERN[] = "^data:image/(jpeg|jpg|png|ico|gif|bmp|webp);base64$";
        if (IsValidBase64Head(uri, BASE64_PATTERN)) {
            return SrcType::BASE64;
        }
        return SrcType::UNSUPPORTED;
    } else if (head == "memory") {
        return SrcType::MEMORY;
    } else if (head == "resource") {
        return SrcType::RESOURCE;
    } else if (head == "dataability" || head == "datashare") {
        if (IsUriOfDataAbilityEncoded(uri, "^dataability://.*?/media/.*/thumbnail/.*$") ||
            IsUriOfDataAbilityEncoded(uri, "^datashare://.*?/media/.*/thumbnail/.*$")) {
            return SrcType::DATA_ABILITY_DECODED;
        }
        return SrcType::DATA_ABILITY;
    } else {
        return SrcType::UNSUPPORTED;
    }
}

ImageSourceInfo::ImageSourceInfo(
    const std::string& imageSrc,
    Dimension width,
    Dimension height,
    InternalResource::ResourceId resourceId,
    const RefPtr<PixelMap>& pixmap)
    : src_(imageSrc),
      sourceWidth_(width),
      sourceHeight_(height),
      resourceId_(resourceId),
      pixmap_(pixmap),
      isSvg_(IsSVGSource(src_, resourceId_)),
      isPng_(IsPngSource(src_, resourceId_)),
      srcType_(ResolveSrcType())
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
    cacheKey_ = std::to_string(std::hash<std::string> {}(src_)) +
                std::to_string(static_cast<int32_t>(resourceId_)) +
                std::to_string(Container::CurrentId());
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

void ImageSourceInfo::SetFillColor(const Color& color)
{
    fillColor_.emplace(color.GetValue());
}

} // namespace OHOS::Ace
