/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_FLUTTER_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_FLUTTER_RENDER_CONTEXT_H

#include <memory>

#include "include/core/SkCanvas.h"
#include "include/core/SkPictureRecorder.h"
#include "include/core/SkRefCnt.h"

#include "core/components_ng/render/adapter/flutter_node.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class FlutterRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(FlutterRenderContext, NG::RenderContext)
public:
    FlutterRenderContext() = default;
    ~FlutterRenderContext() override;

    void InitContext(bool isRoot, const std::optional<ContextParam>& param) override;

    void SyncGeometryProperties(GeometryNode* geometryNode) override;

    void RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) override;

    RefPtr<Canvas> GetCanvas() override;
    void Restore() override;

    void StartRecording() override;

    void StopRecordingIfNeeded() override;

    bool IsRecording()
    {
        return !!recordingCanvas_;
    }

    void StartPictureRecording(float x, float y, float width, float height);
    sk_sp<SkPicture> FinishRecordingAsPicture();

    void SetDrawContentAtLast(bool useDrawContentLastOrder) override {}

    void SetClipToFrame(bool useClip) override {}

    void FlushContentDrawFunction(CanvasDrawFunction&& contentDraw) override;

    void FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw) override;

    void FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) override;

    RectF GetPaintRectWithTransform() override;

    RectF GetPaintRectWithoutTransform() override;

    const std::shared_ptr<FlutterNode>& GetNode()
    {
        return flutterNode_;
    }

protected:
    void OnBackgroundColorUpdate(const Color& value) override;

private:
    std::unique_ptr<SkPictureRecorder> recorder_;
    std::shared_ptr<FlutterNode> flutterNode_;
    std::shared_ptr<SkCanvas> recordingCanvas_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_FLUTTER_RENDER_CONTEXT_H
