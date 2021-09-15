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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/resource/internal_resource.h"

namespace OHOS::Ace {

class ImageSourceInfo {
public:
    static bool IsSVGSource(const std::string& imageSrc, InternalResource::ResourceId resourceId);
    ImageSourceInfo() = default;
    explicit ImageSourceInfo(
        const std::string& imageSrc,
        Dimension width = Dimension(-1),
        Dimension height = Dimension(-1),
        InternalResource::ResourceId resourceId = InternalResource::ResourceId::NO_ID)
        : src_(imageSrc),
          sourceWidth_(width),
          sourceHeight_(height),
          resourceId_(resourceId),
          isSvg_(IsSVGSource(src_, resourceId_))
    {}
    ~ImageSourceInfo() = default;

    bool operator==(const ImageSourceInfo& info) const
    {
        return src_ == info.src_ &&
               resourceId_ == info.resourceId_ &&
               sourceWidth_ == info.sourceWidth_ &&
               sourceHeight_ == info.sourceHeight_;
    }

    bool operator!=(const ImageSourceInfo& info) const
    {
        return src_ != info.src_ ||
               resourceId_ != info.resourceId_ ||
               sourceWidth_ != info.sourceWidth_ ||
               sourceHeight_ != info.sourceHeight_;
    }

    void SetSrc(const std::string& src)
    {
        src_ = src;
        resourceId_ = InternalResource::ResourceId::NO_ID;
        isSvg_ = IsSVGSource(src_, resourceId_);
    }

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetResourceId(InternalResource::ResourceId id)
    {
        resourceId_ = id;
        src_.clear();
        isSvg_ = IsSVGSource(src_, resourceId_);
    }

    InternalResource::ResourceId GetResourceId() const
    {
        return resourceId_;
    }

    bool IsInternalResource() const
    {
        return src_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID;
    }

    bool IsValid() const
    {
        return (src_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID) ||
               (!src_.empty() && resourceId_ == InternalResource::ResourceId::NO_ID);
    }

    bool IsSvg() const
    {
        return isSvg_;
    }

    std::string ToString() const
    {
        if (!src_.empty()) {
            return src_ + std::string("w") + std::to_string(sourceWidth_.Value()) +
                std::string("h") + std::to_string(sourceHeight_.Value());
        } else if (resourceId_ != InternalResource::ResourceId::NO_ID) {
            return std::string("internal resource id: ") + std::to_string(static_cast<int32_t>(resourceId_));
        } else {
            return std::string("empty source");
        }
    }

    void SetDimension(Dimension width, Dimension Height)
    {
        sourceWidth_ = width;
        sourceHeight_ = Height;
    }

    bool IsSourceDimensionValid() const
    {
        return sourceWidth_.IsValid() && sourceHeight_.IsValid();
    }

    Size GetSourceSize() const
    {
        return Size(sourceWidth_.Value(), sourceHeight_.Value());
    }

    void Reset()
    {
        src_.clear();
        sourceWidth_ = Dimension(-1);
        sourceHeight_ = Dimension(-1);
        resourceId_ = InternalResource::ResourceId::NO_ID;
        isSvg_ = false;
    }

private:
    std::string src_;
    Dimension sourceWidth_ = Dimension(-1);
    Dimension sourceHeight_ = Dimension(-1);
    InternalResource::ResourceId resourceId_ = InternalResource::ResourceId::NO_ID;
    bool isSvg_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_ACE_IMAGE_SOURCE_INFO_H