/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_OFFSCREEN_RENDERING_CONTEXT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_OFFSCREEN_RENDERING_CONTEXT_H

#include <cstdint>
#include "render_image.h"

#include "bridge/cj_frontend/cppview/canvas_renderer.h"
#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT CJOffscreenRenderingContext : public NativeCanvasRenderer {
public:
    CJOffscreenRenderingContext(double width, double height, bool antialias, int32_t unit);
    CJOffscreenRenderingContext();
    ~CJOffscreenRenderingContext() override;

    int64_t CJTransferToImageBitmap();

    static void AddOffscreenCanvasPattern(const RefPtr<AceType>& pattern)
    {
        CHECK_NULL_VOID(pattern);
        std::lock_guard<std::mutex> lock(mutex_);
        offscreenPatternMap_[offscreenPatternCount_++] = pattern;
    }

    static RefPtr<AceType> GetOffscreenPattern(int32_t id)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return offscreenPatternMap_[id];
    }

    uint32_t GetId()
    {
        return id_;
    }

    void SetWidth(double width)
    {
        width_ = width;
    }

    double GetWidth() const
    {
        return width_;
    }

    void SetHeight(double height)
    {
        height_ = height;
    }

    double GetHeight() const
    {
        return height_;
    }

private:
    static std::mutex mutex_;

    uint32_t id_;
    double width_ = 0.0f;
    double height_ = 0.0f;

    static std::unordered_map<uint32_t, RefPtr<AceType>> offscreenPatternMap_;
    static uint32_t offscreenPatternCount_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_OFFSCREEN_RENDERING_CONTEXT_H
