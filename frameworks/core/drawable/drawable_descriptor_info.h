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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_INFO_H

#include "base/image/pixel_map.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT DrawableDescriptorInfo : public AceType {
    DECLARE_ACE_TYPE(DrawableDescriptorInfo, AceType);

public:
    DrawableDescriptorInfo() = default;
    ~DrawableDescriptorInfo() = default;

    enum class SrcType {
        UNDEFINED = -1,
        RESOURCE = 0,
        BASE64 = 1,
        FILE = 2,
    };

    explicit DrawableDescriptorInfo(const std::string& path);
    explicit DrawableDescriptorInfo(const RefPtr<ResourceObject>& resource);

    SrcType GetSrcType() const
    {
        return srcType_;
    }

    std::string GetSrc()
    {
        return path_;
    }

    RefPtr<ResourceObject> GetResource()
    {
        return resource_;
    }

private:
    static DrawableDescriptorInfo::SrcType ParseStringType(const std::string& src);
    static bool IsValidBase64Head(const std::string& uri);
    static bool IsValidFileHead(const std::string& uri);

    std::string path_;
    SrcType srcType_ = SrcType::UNDEFINED;
    RefPtr<ResourceObject> resource_;
};
}; // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_INFO_H