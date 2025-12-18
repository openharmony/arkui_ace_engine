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

#include "core/components_ng/pattern/canvas/canvas_render_context_immediate.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"

namespace OHOS::Ace::NG {
void CanvasRenderContextImmediate::PushTask(std::function<void(CanvasPaintMethod&)>&& task)
{
    CHECK_NULL_VOID(paintMethod_);
    if (!isVisible_) {
        paintMethod_->ClearRecordingCanvas();
        return;
    }
    task(*paintMethod_);
    needRender_ = true;
}

bool CanvasRenderContextImmediate::NeedRender() const
{
    return needRender_;
}

void CanvasRenderContextImmediate::FlushTask()
{
    needRender_ = false;
}

TransformParam CanvasRenderContextImmediate::GetTransform() const
{
    CHECK_NULL_RETURN(paintMethod_, {});
    return paintMethod_->GetTransformInner(); // wait for recordingCanvas storing in CanvasRenderContext
}

LineDashParam CanvasRenderContextImmediate::GetLineDash() const
{
    CHECK_NULL_RETURN(paintMethod_, {});
    return paintMethod_->GetLineDashInner(); // wait for recordingCanvas storing in CanvasRenderContext
}
} // namespace OHOS::Ace::NG
