/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/pipeline/base/flutter_render_context.h"

#include "core/pipeline/base/render_node.h"
#include "core/pipeline/layers/offset_layer.h"

namespace OHOS::Ace {
namespace {

inline bool ShouldPaint(const RefPtr<RenderNode>& node)
{
    return node != nullptr && node->GetVisible() && !node->GetHidden();
}

} // namespace

using namespace Flutter;

FlutterRenderContext::~FlutterRenderContext()
{
    StopRecordingIfNeeded();
}

void FlutterRenderContext::Repaint(const RefPtr<RenderNode>& node)
{
    if (!ShouldPaint(node) || !node->NeedRender() || !node->GetRenderLayer()) {
        LOGD("Node is not need to paint");
        return;
    }
    InitContext(node->GetRenderLayer(), node->GetRectWithShadow());
    node->RenderWithContext(*this, Offset::Zero());
    StopRecordingIfNeeded();
}

void FlutterRenderContext::PaintChild(const RefPtr<RenderNode>& child, const Offset& offset)
{
    if (!ShouldPaint(child)) {
        LOGD("Node is not need to paint");
        return;
    }

    Rect rect = child->GetTransitionPaintRect() + offset;
    if (!child->IsPaintOutOfParent() && !estimatedRect_.IsIntersectWith(rect)) {
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        child->ClearAccessibilityRect();
#endif
        return;
    }

    if (child->GetRenderLayer()) {
        StopRecordingIfNeeded();
        std::string name = AceType::TypeName(child);
        if (name != "FlutterRenderForm") {
            if (child->NeedRender()) {
                FlutterRenderContext context;
                context.Repaint(child);
            } else {
                // No need to repaint, notify to update AccessibilityNode info.
                child->NotifyPaintFinish();
            }
        }
        // add child layer to parent layer
        OffsetLayer* layer = CastLayerAs<OffsetLayer>(child->GetRenderLayer());
        if (!layer) {
            LOGE("layer is null");
            return;
        }
        Offset pos = rect.GetOffset();
        if (name != "FlutterRenderForm") {
            layer->SetOffset(pos.GetX(), pos.GetY());
        } else {
            auto renderPost = child->GetGlobalOffset();
            auto context = child->GetContext().Upgrade();
            if (context) {
                auto density = context->GetDensity();
                auto parent = child->GetParent();
                if (!NearZero(density)) {
                    if (parent.Upgrade() && parent.Upgrade()->GetRenderLayer()) {
                        layer->SetOffset(renderPost.GetX() / density - renderPost.GetX(),
                            renderPost.GetY() / density - renderPost.GetY());
                    } else {
                        layer->SetOffset(pos.GetX() / density, pos.GetY() / density);
                    }
                }
            }
        }
        containerLayer_->AddChildren(AceType::Claim(layer));
    } else {
        child->RenderWithContext(*this, rect.GetOffset());
    }
}

void FlutterRenderContext::StartRecording()
{
    currentLayer_ = AceType::MakeRefPtr<PictureLayer>();
    recorder_ = flutter::PictureRecorder::Create();
    canvas_ = flutter::Canvas::Create(
        recorder_.get(), estimatedRect_.Left(), estimatedRect_.Top(), estimatedRect_.Right(), estimatedRect_.Bottom());
    containerLayer_->AddChildren(currentLayer_);
}

void FlutterRenderContext::StopRecordingIfNeeded()
{
    if (!IsRecording()) {
        return;
    }

    currentLayer_->SetPicture(recorder_->endRecording());
    currentLayer_ = nullptr;
    recorder_ = nullptr;
    canvas_ = nullptr;
}

bool FlutterRenderContext::IsIntersectWith(const RefPtr<RenderNode>& child, Offset& offset)
{
    if (!ShouldPaint(child)) {
        LOGD("Node is not need to paint");
        return false;
    }

    Rect rect = child->GetTransitionPaintRect() + offset;
    if (!estimatedRect_.IsIntersectWith(rect)) {
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        child->ClearAccessibilityRect();
#endif
        return false;
    }

    offset = rect.GetOffset();
    return true;
}

void FlutterRenderContext::ClipHoleBegin(const Rect& holeRect)
{
    auto canvas = GetCanvas();
    if (!canvas) {
        return;
    }
    LOGI("Hole: PrePaint save clip.");
    canvas->save();
    if (holeRect.IsValid()) {
        canvas->clipRect(holeRect.Left(), holeRect.Top(), holeRect.Right(), holeRect.Bottom(), SkClipOp::kDifference);
    }
}

void FlutterRenderContext::ClipHoleEnd()
{
    LOGI("Hole: PostPaint restore clip");
    auto canvas = GetCanvas();
    if (!canvas) {
        return;
    }
    canvas->restore();
}

void FlutterRenderContext::InitContext(RenderLayer layer, const Rect& rect)
{
    LOGD("InitContext with width %{public}lf height %{public}lf", rect.Width(), rect.Height());
    estimatedRect_ = rect;
    containerLayer_ = CastLayerAs<ContainerLayer>(layer);
    containerLayer_->RemoveChildren();
}

flutter::Canvas* FlutterRenderContext::GetCanvas()
{
    if (!IsRecording()) {
        StartRecording();
    }
    return canvas_.get();
}

} // namespace OHOS::Ace
