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
#include <functional>
#include <memory>
#include <unordered_map>

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

enum class DrawableType {
    BASE = 0,
    LAYERED = 1,
    ANIMATED = 2,
    PIXELMAP = 3,
    VECTOR = 4,
};

class DRAWABLE_FORCE_EXPORT DrawableDescriptor {
public:
    using RedrawCallback = std::function<void()>;

    DrawableDescriptor() = default;

    virtual ~DrawableDescriptor()
    {
        ProcessDestructCallbacks();
    }

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

    void ProcessDestructCallbacks()
    {
        for (auto& [_, callback] : destructCallbacks_) {
            callback();
        }
    }

    void AddDestructCallback(void* key, const std::function<void()>& callback)
    {
        destructCallbacks_.emplace(key, callback);
    }

    void RemoveDestructCallback(void* key)
    {
        destructCallbacks_.erase(key);
    }

    SrcType GetSrcType() const
    {
        return src_.GetSrcType();
    }

protected:
    SourceInfo src_;
    std::shared_ptr<ImageData> data_;
    std::vector<RedrawCallback> redrawCallbacks_;

private:
    // holder notice to prevent pointer from hanging
    std::unordered_map<void*, std::function<void()>> destructCallbacks_;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H
