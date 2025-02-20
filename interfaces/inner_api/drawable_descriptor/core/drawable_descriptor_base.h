/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H

#include <cstdint>
#include <memory>

#include "base/drawing.h"
#include "base/image_data.h"
#include "base/log.h"
#include "base/marcos.h"
#include "base/paint.h"
#include "base/pixel_map.h"
#include "base/source_info.h"

namespace OHOS {
namespace Media {
class PixelMap;
}
} // namespace OHOS

namespace OHOS {
namespace Ace {
namespace Drawable {
struct DrawableInfo {
    int32_t originalWidth = 0;
    int32_t originalHeight = 0;
};

class DRAWABLE_FORCE_EXPORT DrawableDescriptor {
public:
    enum class DrawableType {
        BASE = 0,
        LAYERED = 1,
        ANIMATED = 2,
        PIXELMAP = 3,
        VECTOR = 4,
    };

    using RedrawCallback = std::function<void()>;

    DrawableDescriptor() = default;

    virtual ~DrawableDescriptor() = default;

    virtual std::shared_ptr<Media::PixelMap> GetPixelMap()
    {
        return nullptr;
    }

    virtual DrawableType GetDrawableType() const
    {
        return DrawableType::BASE;
    }

    virtual int32_t GetOriginalWidth() const
    {
        return 0;
    }

    virtual int32_t GetOriginalHeight() const
    {
        return 0;
    }

    virtual DrawableInfo FetchSync()
    {
        return { 0, 0 };
    }

    virtual void Validate() {}

    virtual void Draw(RSCanvas& canvas, PaintConfig config) {}

    virtual void Fetch() {}

    virtual void LoadImageData() {}

    virtual void Decode() {}

    virtual void RegisterRedrawCallback(RedrawCallback&& callback) {}

    virtual void SetPixelMap(const std::shared_ptr<Media::PixelMap>& pixelMap) {}
    
    void SetSourceInfo(const SourceInfo& sourceInfo)
    {
        src_ = sourceInfo;
    }

protected:
    SourceInfo src_;
    std::shared_ptr<ImageData> data_;
    std::vector<RedrawCallback> redrawCallbacks_;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H