/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDERING_CONTEXT_2D_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDERING_CONTEXT_2D_CONTENT_MODIFIER_H

#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/canvas/custom_paint_util.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class RenderContext;
class CanvasModifier : public ContentModifier {
    DECLARE_ACE_TYPE(CanvasModifier, ContentModifier);

public:
    CanvasModifier();
    ~CanvasModifier() override = default;
    void onDraw(DrawingContext& drawingContext) override;
    std::string GetDumpInfo();
    void GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& array);

    void SetRenderContext(const WeakPtr<RenderContext>& renderContext);

    void SetNeedResetSurface()
    {
        needResetSurface_ = true;
    }

    void MarkModifierDirty()
    {
        CHECK_NULL_VOID(needRender_);
        needRender_->Set(!needRender_->Get());
    }

    void UpdateCanvas(std::shared_ptr<RSRecordingCanvas> rsRecordingCanvas)
    {
        rsRecordingCanvas_ = rsRecordingCanvas;
    }

private:
    void ResetSurface();
    bool needResetSurface_ = false;
    WeakPtr<RenderContext> renderContext_;
    RefPtr<PropertyBool> needRender_;
    std::shared_ptr<RSRecordingCanvas> rsRecordingCanvas_;
    SizeT<int32_t> recordingCanvasDrawSize_ = { 0.0f, 0.0f };
    SizeT<int32_t> drawCmdSize_ = { 0.0f, 0.0f };
    std::vector<CanvasModifierDump> dumpInfos_;
    ACE_DISALLOW_COPY_AND_MOVE(CanvasModifier);
};
} // namespace OHOS::Ace::NG

#endif
