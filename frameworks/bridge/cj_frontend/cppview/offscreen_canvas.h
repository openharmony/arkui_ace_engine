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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_OFFSCREEN_CAVANS_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_OFFSCREEN_CAVANS_H

#include <cstdint>

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "bridge/cj_frontend/cppview/offscreen_rendering_context.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeOffscreenCanvas : public OHOS::FFI::FFIData {
public:
    NativeOffscreenCanvas(double height, double width, int32_t unit);
    ~NativeOffscreenCanvas() override;

    int64_t GetContext(int32_t contextType, bool option, double width, double height);
    int64_t TransferToImageBitmap();
    void NativeSetHeihgt(double height);
    void NativeSetWidth(double width);
    double NativeGetHeihgt();
    double NativeGetWidth();

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

    bool IsGetContext() const
    {
        return isGetContext_;
    }

    void SetDetachStatus(bool isDetached)
    {
        isDetached_ = isDetached;
    }

    bool IsDetached() const
    {
        return isDetached_;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    void SetOffscreenPattern(const RefPtr<NG::OffscreenCanvasPattern>& offscreenPattern)
    {
        offscreenCanvasPattern_ = offscreenPattern;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity()
    {
        double density = PipelineBase::GetCurrentDensity();
        return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
    }

    enum class ContextType {
        CONTEXT_2D = 0,
    };

    void SetOffscreenCanvasContext(const sptr<CJOffscreenRenderingContext> offscreenCanvasContext)
    {
        offscreenCanvasContext_ = offscreenCanvasContext;
    }

private:
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
    double width_ = 0.0f;
    double height_ = 0.0f;
    RefPtr<NG::OffscreenCanvasPattern> offscreenCanvasPattern_;
    sptr<CJOffscreenRenderingContext> offscreenCanvasContext_;
    bool isGetContext_ = false;
    bool isDetached_ = false;
    ContextType contextType_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATH_H
