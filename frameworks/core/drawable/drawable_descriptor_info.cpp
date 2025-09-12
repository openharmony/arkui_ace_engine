/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/drawable/drawable_descriptor_info.h"

#include <regex>

namespace OHOS::Ace {

DrawableDescriptorInfo::DrawableDescriptorInfo(const std::string& path)
{
    path_ = path;
    srcType_ = ParseStringType(path);
}

DrawableDescriptorInfo::DrawableDescriptorInfo(const RefPtr<ResourceObject>& resource)
{
    resource_ = resource;
    srcType_ = SrcType::RESOURCE;
}

DrawableDescriptorInfo::SrcType DrawableDescriptorInfo::ParseStringType(const std::string& src)
{
    if (src.empty()) {
        return DrawableDescriptorInfo::SrcType::UNDEFINED;
    }
    if (IsValidFileHead(src)) {
        return DrawableDescriptorInfo::SrcType::FILE;
    }
    if (IsValidBase64Head(src)) {
        return DrawableDescriptorInfo::SrcType::BASE64;
    }
    return DrawableDescriptorInfo::SrcType::UNDEFINED;
}

bool DrawableDescriptorInfo::IsValidBase64Head(const std::string& uri)
{
    static constexpr char BASE64_PATTERN[] =
        "^data:image/(jpeg|JPEG|jpg|JPG|png|PNG|ico|ICO|gif|GIF|bmp|BMP|webp|WEBP|heic|heif|HEIF"
        "|sut|astc);base64$";
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos) {
        return false;
    }
    std::string base64Head = uri.substr(0, iter);
    std::regex regular(BASE64_PATTERN);
    return std::regex_match(base64Head, regular);
}

bool DrawableDescriptorInfo::IsValidFileHead(const std::string& uri)
{
    std::regex fileRegex("^file://.");
    return std::regex_match(uri, fileRegex);
}
} // namespace OHOS::Ace