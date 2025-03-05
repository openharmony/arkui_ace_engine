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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_SOURCE_INFO_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_SOURCE_INFO_H

#include <string>

#include "base/resource.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
enum class SrcType {
    UNSUPPORTED = -1,
    RESOURCE,
    PIXMAP,
};

class SourceInfo final {
public:
    SourceInfo() = default;
    ~SourceInfo() = default;

    explicit SourceInfo(const std::string& src) : src_(src), srcType_(ResolveSrcType(src)) {}

    explicit SourceInfo(const Resource& resource) : resource_(resource), srcType_(SrcType::RESOURCE) {}

    void SetSrc(const std::string& src)
    {
        src_ = src;
        srcType_ = ResolveSrcType(src);
    }

    void SetSrcType(const SrcType& srcType)
    {
        srcType_ = srcType;
    }

    SrcType GetSrcType() const
    {
        return srcType_;
    }

    std::string GetSrc() const
    {
        return src_;
    }

    void SetResource(const Resource& resource)
    {
        resource_ = resource;
    }

    Resource GetResource() const
    {
        return resource_;
    }

private:
    static SrcType ResolveSrcType(const std::string& src)
    {
        return SrcType::RESOURCE;
    }

    std::string src_;
    Resource resource_;
    SrcType srcType_ = SrcType::UNSUPPORTED;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_SOURCE_INFO_H
