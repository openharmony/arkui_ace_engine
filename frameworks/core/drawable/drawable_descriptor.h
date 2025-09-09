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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
enum class DrawableType {
    BASE = 0,
    LAYERED = 1,
    ANIMATED = 2,
    PIXELMAP = 3,
};

struct MediaData {
    std::unique_ptr<uint8_t[]> data;
    size_t len = 0;
};

struct DrawableDescriptorLoadResult {
    int32_t imageWidth_ = 0;
    int32_t imageHeight_ = 0;
    int32_t errorCode = 0;
};

class ACE_FORCE_EXPORT DrawableDescriptor : public AceType {
    DECLARE_ACE_TYPE(DrawableDescriptor, AceType);

public:
    using UpdateCallback = std::function<void(const RefPtr<PixelMap>& pixelMap)>;
    using LoadCallback = std::function<void(DrawableDescriptorLoadResult result)>;

    struct ImageSize {
        int32_t width = 0;
        int32_t height = 0;
    };

    DrawableDescriptor() = default;
    virtual ~DrawableDescriptor() = default;

    virtual RefPtr<PixelMap> GetPixelMap()
    {
        return nullptr;
    }

    virtual DrawableType GetDrawableType() const
    {
        return DrawableType::BASE;
    }

    virtual int32_t GetOriginalWidth()
    {
        return -1;
    }

    virtual int32_t GetOriginalHeight()
    {
        return -1;
    }

    virtual DrawableDescriptorLoadResult LoadSync()
    {
        return {};
    }

    virtual void LoadAsync(const LoadCallback&& callback) {}

    virtual void RegisterUpdateCallback(int32_t nodeId, const UpdateCallback&& callback) {}

    virtual void UnRegisterUpdateCallback(int32_t nodeId) {}

protected:
    ImageSize imageSize_;

private:
    virtual void CreatePixelMap() {}
};
}; // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H