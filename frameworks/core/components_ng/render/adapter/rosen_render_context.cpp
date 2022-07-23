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

#include "core/components_ng/render/adapter/rosen_render_context.h"

#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_root_node.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/render/canvas.h"

namespace OHOS::Ace::NG {
RosenRenderContext::~RosenRenderContext()
{
    StopRecordingIfNeeded();
}

void RosenRenderContext::StartRecording(float x, float y, float width, float height)
{
    if (rsNode_ == nullptr) {
        return;
    }
    auto rsCanvasNode = rsNode_->ReinterpretCastTo<Rosen::RSCanvasNode>();
    if (rsCanvasNode) {
        rosenCanvas_ = Canvas::Create(
            rsCanvasNode->BeginRecording(ceil(rsCanvasNode->GetPaintWidth()), ceil(rsCanvasNode->GetPaintHeight())));
    }
}

void RosenRenderContext::StartPictureRecording(float x, float y, float width, float height)
{
    recorder_ = new SkPictureRecorder();
    recordingCanvas_ = Canvas::Create(recorder_->beginRecording(SkRect::MakeXYWH(x, y, width, height)));
}

void RosenRenderContext::StopRecordingIfNeeded()
{
    auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
    if (rosenCanvas_ && rsCanvasNode) {
        rsCanvasNode->FinishRecording();
        rosenCanvas_ = nullptr;
    }

    if (IsRecording()) {
        delete recorder_;
        recorder_ = nullptr;
        recordingCanvas_.Reset();
    }
}

void RosenRenderContext::InitContext(bool isRoot)
{
    if (!rsNode_) {
        if (isRoot) {
            LOGE("create RSRootNode");
            rsNode_ = Rosen::RSRootNode::Create();
        } else {
            rsNode_ = Rosen::RSCanvasNode::Create();
        }
    }
    rsNode_->SetFrame(0, 0, 0, 0);
    rsNode_->SetPivot(0.0F, 0.0F);
}

void RosenRenderContext::SyncGeometryProperties(GeometryNode* geometryNode)
{
    if (!rsNode_) {
        return;
    }
    const auto& frameRect = geometryNode->GetFrame().GetRect();
    rsNode_->SetFrame(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
}

void RosenRenderContext::UpdateBgColor(const Color& value)
{
    if (!rsNode_) {
        return;
    }
    rsNode_->SetBackgroundColor(value.GetValue());
    RequestNextFrame();
}

RefPtr<Canvas> RosenRenderContext::GetCanvas()
{
    // if picture recording, return recording canvas
    return recordingCanvas_ ? recordingCanvas_ : rosenCanvas_;
}

const std::shared_ptr<Rosen::RSNode>& RosenRenderContext::GetRSNode()
{
    return rsNode_;
}

sk_sp<SkPicture> RosenRenderContext::FinishRecordingAsPicture()
{
    if (!recorder_) {
        return nullptr;
    }
    return recorder_->finishRecordingAsPicture();
}

void RosenRenderContext::Restore()
{
    const auto& canvas = GetCanvas();
    if (canvas != nullptr) {
        canvas->Restore();
    }
}

void RosenRenderContext::RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children)
{
    ReCreateRsNodeTree(children);
}

void RosenRenderContext::ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children)
{
    rsNode_->ClearChildren();
    for (const auto& child : children) {
        ACE_DCHECK(child);
        auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
        if (!rosenRenderContext) {
            continue;
        }
        auto rsnode = rosenRenderContext->GetRSNode();
        if (rsnode) {
            rsNode_->AddChild(rsnode, -1);
        }
    }
}
} // namespace OHOS::Ace::NG
