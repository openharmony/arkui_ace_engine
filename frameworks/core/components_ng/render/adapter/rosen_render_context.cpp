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

#include <cstdint>

#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RosenRenderContext::~RosenRenderContext()
{
    StopRecordingIfNeeded();
}

void RosenRenderContext::StartRecording()
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

void RosenRenderContext::InitContext(bool isRoot, const std::optional<std::string>& surfaceName)
{
    if (!rsNode_) {
        if (surfaceName.has_value()) {
            struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceName.value() };
            rsNode_ = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
        } else if (isRoot) {
            LOGI("create RSRootNode");
            rsNode_ = Rosen::RSRootNode::Create();
        } else {
            rsNode_ = Rosen::RSCanvasNode::Create();
        }
    }
    rsNode_->SetBounds(0, 0, 0, 0);
    rsNode_->SetFrame(0, 0, 0, 0);
    rsNode_->SetPivot(0.0F, 0.0F);
}

void RosenRenderContext::SyncGeometryProperties(GeometryNode* geometryNode)
{
    if (!rsNode_) {
        return;
    }
    const auto& frameRect = geometryNode->GetFrame().GetRect();
    if (rsNode_->GetType() == Rosen::RSUINodeType::SURFACE_NODE) {
        const auto& contentRect = geometryNode->GetContent()->GetRect();
        rsNode_->SetBounds(frameRect.GetX() + contentRect.GetX(), frameRect.GetY() + contentRect.GetY(),
            contentRect.Width(), contentRect.Height());
    } else {
        rsNode_->SetBounds(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
    }
    rsNode_->SetFrame(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
}

void RosenRenderContext::OnBackgroundColorUpdate(const Color& value)
{
    if (!rsNode_) {
        return;
    }
    rsNode_->SetBackgroundColor(value.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::OnBorderRadiusUpdate(const BorderRadiusProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerRadius;
    cornerRadius.SetValues(static_cast<float>(value.radiusTopLeft.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusTopRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension()).ConvertToPx()));
    rsNode_->SetCornerRadius(cornerRadius);
    RequestNextFrame();
}

void RosenRenderContext::OnBorderColorUpdate(const BorderColorProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBorderColor(value.leftColor.value_or(Color::BLACK).GetValue(),
        value.topColor.value_or(Color::BLACK).GetValue(), value.rightColor.value_or(Color::BLACK).GetValue(),
        value.bottomColor.value_or(Color::BLACK).GetValue());
    RequestNextFrame();
}

void RosenRenderContext::UpdateBorderWidth(const BorderWidthPropertyF& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerBorderWidth;
    cornerBorderWidth.SetValues(value.leftDimen.value_or(0), static_cast<float>(value.topDimen.value_or(0)),
        static_cast<float>(value.rightDimen.value_or(0)), static_cast<float>(value.bottomDimen.value_or(0)));
    rsNode_->SetBorderWidth(cornerBorderWidth);
    RequestNextFrame();
}

void RosenRenderContext::OnBorderStyleUpdate(const BorderStyleProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBorderStyle(static_cast<uint32_t>(value.styleLeft.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleTop.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleRight.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleBottom.value_or(BorderStyle::SOLID)));
    RequestNextFrame();
}

void RosenRenderContext::ResetBlendBgColor()
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBackgroundColor(GetBackgroundColor().value_or(Color::TRANSPARENT).GetValue());
    RequestNextFrame();
}

void RosenRenderContext::BlendBgColor(const Color& color)
{
    CHECK_NULL_VOID(rsNode_);
    auto blendColor = GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(color);
    rsNode_->SetBackgroundColor(blendColor.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::FlushContentDrawFunction(CanvasDrawFunction&& contentDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(contentDraw);
    rsNode_->DrawOnNode(
        Rosen::RSModifierType::CONTENT_STYLE, [contentDraw = std::move(contentDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            contentDraw(rsCanvas);
        });
}

void RosenRenderContext::FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(foregroundDraw);
    rsNode_->DrawOnNode(Rosen::RSModifierType::FOREGROUND_STYLE,
        [foregroundDraw = std::move(foregroundDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            foregroundDraw(rsCanvas);
        });
}

void RosenRenderContext::FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(overlayDraw);
    rsNode_->DrawOnNode(
        Rosen::RSModifierType::OVERLAY_STYLE, [overlayDraw = std::move(overlayDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            overlayDraw(rsCanvas);
        });
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

void RosenRenderContext::RebuildFrame(FrameNode* /*self*/, const std::list<RefPtr<FrameNode>>& children)
{
    ReCreateRsNodeTree(children);
}

void RosenRenderContext::ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->ClearChildren();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
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

void RosenRenderContext::AddFrameChildren(FrameNode* /*self*/, const std::list<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_VOID(rsNode_);
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
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

void RosenRenderContext::RemoveFrameChildren(FrameNode* /*self*/, const std::list<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_VOID(rsNode_);
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
        if (!rosenRenderContext) {
            continue;
        }
        auto rsnode = rosenRenderContext->GetRSNode();
        if (rsnode) {
            rsNode_->RemoveChild(rsnode);
        }
    }
}

void RosenRenderContext::MoveFrame(FrameNode* /*self*/, const RefPtr<FrameNode>& child, int32_t index)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(child);
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
    CHECK_NULL_VOID(rosenRenderContext);
    auto rsnode = rosenRenderContext->GetRSNode();
    if (rsnode) {
        rsNode_->MoveChild(rsnode, index);
    }
}

void RosenRenderContext::AnimateHoverEffectScale(bool isHovered)
{
    LOGD("AnimateHoverEffectScale: isHoverd = %{public}d", isHovered);
    if ((isHovered && isHoveredScale_) || (!isHovered && !isHoveredScale_)) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto appTheme = themeManager->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    float themeScaleStart = appTheme->GetHoverScaleStart();
    float themeScaleEnd = appTheme->GetHoverScaleEnd();
    int32_t themeDuration = appTheme->GetHoverDuration();
    float scaleBegin = isHovered ? themeScaleStart : themeScaleEnd;
    float scaleEnd = isHovered ? themeScaleEnd : themeScaleStart;

    rsNode_->SetScale(scaleBegin);
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    RSNode::Animate(
        protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [rsNode = rsNode_, scaleEnd]() {
            if (rsNode) {
                rsNode->SetScale(scaleEnd);
            }
        },
        []() {});
    isHoveredScale_ = isHovered;
}

void RosenRenderContext::AnimateHoverEffectBoard(bool isHovered)
{
    LOGD("AnimateHoverEffectBoard: isHoverd = %{public}d", isHovered);
    if ((isHovered && isHoveredBoard_) || (!isHovered && !isHoveredBoard_)) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto appTheme = themeManager->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    Color themeHighlightStart = appTheme->GetHoverHighlightStart();
    Color themeHighlightEnd = appTheme->GetHoverHighlightEnd();
    int32_t themeDuration = appTheme->GetHoverDuration();
    Color colorBegin = isHovered ? themeHighlightStart : themeHighlightEnd;
    Color colorEnd = isHovered ? themeHighlightEnd : themeHighlightStart;

    rsNode_->SetBackgroundColor(colorBegin.GetValue());
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    RSNode::Animate(
        protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [rsNode = rsNode_, colorEnd]() {
            if (rsNode) {
                rsNode->SetBackgroundColor(colorEnd.GetValue());
            }
        },
        []() {});
    isHoveredBoard_ = isHovered;
}

} // namespace OHOS::Ace::NG
