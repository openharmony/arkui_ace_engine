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

#include "core/components_ng/render/adapter/flutter_render_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
FlutterRenderContext::~FlutterRenderContext()
{
    StopRecordingIfNeeded();
}

void FlutterRenderContext::StartRecording()
{
    CHECK_NULL_VOID(flutterNode_);
    if (IsRecording()) {
        return;
    }
    recorder_ = std::make_unique<SkPictureRecorder>();
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by recorder_
    recordingCanvas_ = { recorder_->beginRecording(SkRect::MakeXYWH(
                             0, 0, flutterNode_->FrameRect().Width(), flutterNode_->FrameRect().Height())),
        [](SkCanvas*) {} };
    LOGD("StartRecording %{public}s", flutterNode_->FrameRect().ToString().c_str());
}

void FlutterRenderContext::StartPictureRecording(float x, float y, float width, float height)
{
    recorder_ = std::make_unique<SkPictureRecorder>();
    // use dummy deleter avoid delete the SkCanvas by shared_ptr, its owned by recorder_
    recordingCanvas_ = { recorder_->beginRecording(SkRect::MakeXYWH(x, y, width, height)), [](SkCanvas*) {} };
}

void FlutterRenderContext::StopRecordingIfNeeded()
{
    if (IsRecording()) {
        sk_sp<SkPicture> picture = recorder_->finishRecordingAsPicture();
        if (flutterNode_) {
            flutterNode_->AddPicture(picture);
        }
        recorder_.reset();
        recordingCanvas_.reset();
    }
}

void FlutterRenderContext::InitContext(bool isRoot, const std::optional<ContextParam>& param)
{
    LOGD("InitContext root:%d", isRoot);
    flutterNode_ = std::make_shared<FlutterNode>(isRoot);
}

void FlutterRenderContext::SyncGeometryProperties(GeometryNode* geometryNode)
{
    const auto& frameRect = geometryNode->GetFrameRect();
    LOGD("SyncGeometryProperties frameRect:%s", frameRect.ToString().c_str());
    CHECK_NULL_VOID(flutterNode_);
    flutterNode_->SetFrameRect(frameRect);
}

void FlutterRenderContext::OnBackgroundColorUpdate(const Color& value)
{
    LOGD("UpdateBgColor color:%s", value.ColorToString().c_str());
    CHECK_NULL_VOID(flutterNode_);
    flutterNode_->SetBgColor(value);
    RequestNextFrame();
}

void FlutterRenderContext::FlushContentDrawFunction(CanvasDrawFunction&& contentDraw)
{
    RSCanvas canvas(&recordingCanvas_);
    if (contentDraw) {
        contentDraw(canvas);
    }
}

void FlutterRenderContext::FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw)
{
    RSCanvas canvas(&recordingCanvas_);
    if (foregroundDraw) {
        foregroundDraw(canvas);
    }
}

void FlutterRenderContext::FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) {}

RefPtr<Canvas> FlutterRenderContext::GetCanvas()
{
    return nullptr;
}

sk_sp<SkPicture> FlutterRenderContext::FinishRecordingAsPicture()
{
    CHECK_NULL_RETURN(recorder_, nullptr);
    return recorder_->finishRecordingAsPicture();
}

void FlutterRenderContext::Restore()
{
    const auto& canvas = GetCanvas();
    if (canvas != nullptr) {
        canvas->Restore();
    }
}

void FlutterRenderContext::RebuildFrame(FrameNode* node, const std::list<RefPtr<FrameNode>>& children)
{
    LOGD("RebuildFrame");
    CHECK_NULL_VOID(flutterNode_);
    flutterNode_->ClearChildren();
    for (const auto& child : children) {
        auto flutterRenderContext = DynamicCast<FlutterRenderContext>(child->GetRenderContext());
        if (!flutterRenderContext) {
            continue;
        }
        auto flutterNode = flutterRenderContext->GetNode();
        flutterNode_->AddChild(flutterNode);
    }
}

RectF FlutterRenderContext::GetPaintRectWithTransform()
{
    RectF rect;
    CHECK_NULL_RETURN(flutterNode_, rect);
    // TODO: support transform
    rect = GetPaintRectWithoutTransform();
    return rect;
}

RectF FlutterRenderContext::GetPaintRectWithoutTransform()
{
    RectF rect;
    CHECK_NULL_RETURN(flutterNode_, rect);
    return flutterNode_->FrameRect();
}

} // namespace OHOS::Ace::NG
