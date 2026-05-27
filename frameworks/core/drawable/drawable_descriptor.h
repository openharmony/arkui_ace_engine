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
#include "core/drawable/drawable_descriptor_info.h"

namespace OHOS::Ace {

extern const char DRAWABLE_DESCRIPTOR_NAME[];
extern const char LAYERED_DRAWABLE_DESCRIPTOR_NAME[];
extern const char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[];
extern const char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[];
extern const char PICTURE_DRAWABLE_DESCRIPTOR_NAME[];
enum class DrawableType {
    BASE = 0,
    LAYERED = 1,
    ANIMATED = 2,
    PIXELMAP = 3,
    PICTURE = 4,
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

    virtual void Invalidate() {}

    void SetDrawableDescriptorInfo(const RefPtr<DrawableDescriptorInfo>& info)
    {
        info_ = info;
    }

    void SetRawData(uint8_t* data, size_t len)
    {
        rawData_.data.reset(data);
        rawData_.len = len;
    }

protected:
    MediaData rawData_;
    RefPtr<DrawableDescriptorInfo> info_;
    ImageSize imageSize_;

private:
    virtual void CreatePixelMap() {}
};
};     // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H