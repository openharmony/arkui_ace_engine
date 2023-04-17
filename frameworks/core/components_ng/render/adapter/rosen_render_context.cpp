/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>
#include <string>

#include "include/utils/SkParsePath.h"
#include "render_service_client/core/modifier/rs_property_modifier.h"
#include "render_service_client/core/pipeline/rs_node_map.h"
#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/common/container.h"
#include "core/common/rosen/rosen_convert_helper.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/border_image_modifier.h"
#include "core/components_ng/render/adapter/debug_boundary_modifier.h"
#include "core/components_ng/render/adapter/focus_state_modifier.h"
#include "core/components_ng/render/adapter/graphics_modifier.h"
#include "core/components_ng/render/adapter/mouse_select_modifier.h"
#include "core/components_ng/render/adapter/overlay_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/adapter/skia_canvas_image.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/border_image_painter.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/debug_boundary_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
float ConvertDimensionToScaleBySize(const Dimension& dimension, float size)
{
    if (dimension.Unit() == DimensionUnit::PERCENT) {
        return static_cast<float>(dimension.Value());
    }
    const float defaultPivot = 0.5f;
    return size > 0.0f ? static_cast<float>(dimension.ConvertToPx() / size) : defaultPivot;
}
} // namespace

RosenRenderContext::~RosenRenderContext()
{
    StopRecordingIfNeeded();
}

void RosenRenderContext::StartRecording()
{
    CHECK_NULL_VOID(rsNode_);
    auto rsCanvasNode = rsNode_->ReinterpretCastTo<Rosen::RSCanvasNode>();
    CHECK_NULL_VOID_NOLOG(rsCanvasNode);
    rosenCanvas_ = Canvas::Create(
        rsCanvasNode->BeginRecording(ceil(rsCanvasNode->GetPaintWidth()), ceil(rsCanvasNode->GetPaintHeight())));
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

void RosenRenderContext::OnNodeAppear()
{
    // because when call this function, the size of frameNode is not calculated. We need frameNode size
    // to calculate the pivot, so just mark need to perform appearing transition.
    CHECK_NULL_VOID_NOLOG(propTransitionAppearing_);
    firstTransitionIn_ = true;
}

void RosenRenderContext::OnNodeDisappear()
{
    CHECK_NULL_VOID_NOLOG(propTransitionDisappearing_);
    CHECK_NULL_VOID(rsNode_);
    auto rect = GetPaintRectWithoutTransform();
    NotifyTransitionInner(rect.GetSize(), false);
}

void RosenRenderContext::SetPivot(float xPivot, float yPivot)
{
    // change pivot without animation
    CHECK_NULL_VOID(rsNode_);
    if (pivotProperty_) {
        pivotProperty_->Set({ xPivot, yPivot });
    } else {
        pivotProperty_ = std::make_shared<Rosen::RSProperty<Rosen::Vector2f>>(Rosen::Vector2f(xPivot, yPivot));
        auto modifier = std::make_shared<Rosen::RSPivotModifier>(pivotProperty_);
        rsNode_->AddModifier(modifier);
    }
}

void RosenRenderContext::SetTransitionPivot(const SizeF& frameSize, bool transitionIn)
{
    auto& transitionEffect = transitionIn ? propTransitionAppearing_ : propTransitionDisappearing_;
    CHECK_NULL_VOID_NOLOG(transitionEffect);
    float xPivot = 0.0f;
    float yPivot = 0.0f;
    if (transitionEffect->HasRotate()) {
        xPivot = ConvertDimensionToScaleBySize(transitionEffect->GetRotateValue().centerX, frameSize.Width());
        yPivot = ConvertDimensionToScaleBySize(transitionEffect->GetRotateValue().centerY, frameSize.Height());
    } else if (transitionEffect->HasScale()) {
        xPivot = ConvertDimensionToScaleBySize(transitionEffect->GetScaleValue().centerX, frameSize.Width());
        yPivot = ConvertDimensionToScaleBySize(transitionEffect->GetScaleValue().centerY, frameSize.Height());
    } else {
        return;
    }
    SetPivot(xPivot, yPivot);
}

void RosenRenderContext::InitContext(bool isRoot, const std::optional<std::string>& surfaceName, bool useExternalNode)
{
    // skip if useExternalNode is true or node already created
    CHECK_NULL_VOID_NOLOG(!useExternalNode);
    CHECK_NULL_VOID_NOLOG(!rsNode_);

    // create proper RSNode base on input
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

void RosenRenderContext::SyncGeometryProperties(GeometryNode* /*geometryNode*/)
{
    CHECK_NULL_VOID(rsNode_);
    auto paintRect = AdjustPaintRect();
    SyncGeometryProperties(paintRect);
}

void RosenRenderContext::SyncGeometryProperties(const RectF& paintRect)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBounds(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    rsNode_->SetFrame(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    SetPivot(0.5f, 0.5f); // default pivot is center

    if (firstTransitionIn_) {
        // need to perform transitionIn early so not influence the following SetPivot
        NotifyTransitionInner(paintRect.GetSize(), true);
        firstTransitionIn_ = false;
    }

    if (propTransform_ && propTransform_->HasTransformCenter()) {
        auto vec = propTransform_->GetTransformCenterValue();
        float xPivot = ConvertDimensionToScaleBySize(vec.GetX(), paintRect.Width());
        float yPivot = ConvertDimensionToScaleBySize(vec.GetY(), paintRect.Height());
        SetPivot(xPivot, yPivot);
    }

    if (propTransform_ && propTransform_->HasTransformTranslate()) {
        // if translate unit is percent, it is related with frameSize
        OnTransformTranslateUpdate(propTransform_->GetTransformTranslateValue());
    }

    if (bgLoadingCtx_ && bgImage_) {
        PaintBackground();
    }

    if (bdImageLoadingCtx_ && bdImage_) {
        PaintBorderImage();
    }

    if (GetBorderImageGradient()) {
        PaintBorderImageGradient();
    }

    if (propGradient_) {
        PaintGradient(paintRect.GetSize());
    }

    if (propClip_) {
        PaintClip(paintRect.GetSize());
    }

    if (propGraphics_) {
        PaintGraphics();
    }

    if (propOverlay_) {
        PaintOverlayText();
    }

    if (NeedDebugBoundary() && SystemProperties::GetDebugBoundaryEnabled()) {
        PaintDebugBoundary();
    }
}

void RosenRenderContext::PaintDebugBoundary()
{
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    auto paintTask = [contentSize = geometryNode->GetFrameSize(), frameSize = geometryNode->GetMarginFrameSize(),
                         offset = geometryNode->GetMarginFrameOffset(),
                         frameOffset = geometryNode->GetFrameOffset()](RSCanvas& rsCanvas) mutable {
        DebugBoundaryPainter painter(contentSize, frameSize);
        painter.SetFrameOffset(frameOffset);
        painter.DrawDebugBoundaries(rsCanvas, offset);
    };

    if (!debugBoundaryModifier_ && rsNode_->IsInstanceOf<Rosen::RSCanvasNode>()) {
        debugBoundaryModifier_ = std::make_shared<DebugBoundaryModifier>();
        debugBoundaryModifier_->SetPaintTask(std::move(paintTask));
        rsNode_->AddModifier(debugBoundaryModifier_);
    }
    if (debugBoundaryModifier_) {
        debugBoundaryModifier_->SetCustomData(true);
    }
}

void RosenRenderContext::OnBackgroundColorUpdate(const Color& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBackgroundColor(value.GetValue());
    RequestNextFrame();
}

DataReadyNotifyTask RosenRenderContext::CreateBgImageDataReadyCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        auto imageSourceInfo = rosenRenderContext->GetBackgroundImage().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        LOGD("bgImage data ready %{public}s", sourceInfo.ToString().c_str());
        rosenRenderContext->bgLoadingCtx_->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
    return task;
}

LoadSuccessNotifyTask RosenRenderContext::CreateBgImageLoadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto imageSourceInfo = ctx->GetBackgroundImage().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        ctx->bgImage_ = ctx->bgLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(ctx->bgImage_);
        LOGI("bgImage load success %{public}s", sourceInfo.ToString().c_str());
        if (ctx->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            ctx->PaintBackground();
            ctx->RequestNextFrame();
        }
    };
    return task;
}

void RosenRenderContext::PaintBackground()
{
    CHECK_NULL_VOID(GetBackground() && GetBackground()->GetBackgroundImage());
    auto image = DynamicCast<SkiaCanvasImage>(bgImage_);
    CHECK_NULL_VOID(rsNode_ && bgLoadingCtx_ && image);
    auto skImage = image->GetCanvasImage();

    auto rosenImage = std::make_shared<Rosen::RSImage>();
    rosenImage->SetImage(skImage);
    auto compressData = image->GetCompressData();
    rosenImage->SetCompressData(
        compressData, image->GetUniqueID(), image->GetCompressWidth(), image->GetCompressHeight());
    rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
    rsNode_->SetBgImage(rosenImage);

    SizeF renderSize = ImagePainter::CalculateBgImageSize(
        GetHost()->GetGeometryNode()->GetFrameSize(), bgLoadingCtx_->GetImageSize(), GetBackgroundImageSize());
    OffsetF positionOffset = ImagePainter::CalculateBgImagePosition(
        GetHost()->GetGeometryNode()->GetFrameSize(), renderSize, GetBackgroundImagePosition());
    rsNode_->SetBgImageWidth(renderSize.Width());
    rsNode_->SetBgImageHeight(renderSize.Height());
    rsNode_->SetBgImagePositionX(positionOffset.GetX());
    rsNode_->SetBgImagePositionY(positionOffset.GetY());
}

void RosenRenderContext::OnBackgroundImageUpdate(const ImageSourceInfo& imageSourceInfo)
{
    CHECK_NULL_VOID(rsNode_);
    if (imageSourceInfo.GetSrc().empty()) {
        return;
    }
    if (!bgLoadingCtx_ || imageSourceInfo != bgLoadingCtx_->GetSourceInfo()) {
        LoadNotifier bgLoadNotifier(CreateBgImageDataReadyCallback(), CreateBgImageLoadSuccessCallback(), nullptr);
        bgLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(imageSourceInfo, std::move(bgLoadNotifier));
        CHECK_NULL_VOID(bgLoadingCtx_);
        bgLoadingCtx_->LoadImageData();
    }
}

void RosenRenderContext::OnBackgroundImageRepeatUpdate(const ImageRepeat& /*imageRepeat*/)
{
    CHECK_NULL_VOID(rsNode_);
    PaintBackground();
}

void RosenRenderContext::OnBackgroundImageSizeUpdate(const BackgroundImageSize& /*bgImgSize*/)
{
    CHECK_NULL_VOID(rsNode_);
    PaintBackground();
}

void RosenRenderContext::OnBackgroundImagePositionUpdate(const BackgroundImagePosition& /*bgImgPosition*/)
{
    CHECK_NULL_VOID(rsNode_);
    PaintBackground();
}

void RosenRenderContext::SetBackBlurFilter()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    const auto& background = GetBackground();
    CHECK_NULL_VOID(background);
    const auto& blurStyle = background->propBlurStyleOption;
    std::shared_ptr<Rosen::RSFilter> backFilter;
    auto dipScale_ = context->GetDipScale();
    auto rosenBlurStyleValue =
        blurStyle.has_value() ? GetRosenBlurStyleValue(blurStyle.value()) : MATERIAL_BLUR_STYLE::NO_MATERIAL;
    if (rosenBlurStyleValue != MATERIAL_BLUR_STYLE::NO_MATERIAL) {
        backFilter = Rosen::RSFilter::CreateMaterialFilter(static_cast<int>(rosenBlurStyleValue),
            static_cast<float>(dipScale_), static_cast<Rosen::BLUR_COLOR_MODE>(blurStyle->adaptiveColor));
    } else {
        const auto& radius = background->propBlurRadius;
        if (radius.has_value() && radius->IsValid()) {
            float radiusPx = context->NormalizeToPx(radius.value());
            float backblurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
            backFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
        }
    }
    rsNode_->SetBackgroundFilter(backFilter);
}

void RosenRenderContext::UpdateBackBlurStyle(const BlurStyleOption& bgBlurStyle)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurStyleOption(bgBlurStyle)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (bgBlurStyle.blurStyle == BlurStyle::NO_MATERIAL || bgBlurStyle.colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
    } else {
        groupProperty->propBlurStyleOption = bgBlurStyle;
    }
    isBackBlurChanged_ = true;
}

void RosenRenderContext::OnOpacityUpdate(double opacity)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetAlpha(opacity);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformScaleUpdate(const VectorF& scale)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetScale(scale.x, scale.y);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformTranslateUpdate(const TranslateOptions& translate)
{
    CHECK_NULL_VOID(rsNode_);
    float xValue = 0.0f;
    float yValue = 0.0f;
    if (translate.x.Unit() == DimensionUnit::PERCENT || translate.y.Unit() == DimensionUnit::PERCENT) {
        auto rect = GetPaintRectWithoutTransform();
        if (!rect.IsValid()) {
            // size is not determined yet
            return;
        }
        xValue = translate.x.ConvertToPxWithSize(rect.Width());
        yValue = translate.y.ConvertToPxWithSize(rect.Height());
    } else {
        xValue = translate.x.ConvertToPx();
        yValue = translate.y.ConvertToPx();
    }
    rsNode_->SetTranslate(xValue, yValue, 0.0f);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformRotateUpdate(const Vector4F& rotate)
{
    CHECK_NULL_VOID(rsNode_);
    float norm = std::sqrt(std::pow(rotate.x, 2) + std::pow(rotate.y, 2) + std::pow(rotate.z, 2));
    if (NearZero(norm)) {
        LOGW("rotate vector is near zero, please check");
        norm = 1.0f;
    }
    // for rosen backend, the rotation angles in the x and y directions should be set to opposite angles
    rsNode_->SetRotation(-rotate.w * rotate.x / norm, -rotate.w * rotate.y / norm, rotate.w * rotate.z / norm);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformCenterUpdate(const DimensionOffset& center)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        float xPivot = ConvertDimensionToScaleBySize(center.GetX(), rect.Width());
        float yPivot = ConvertDimensionToScaleBySize(center.GetY(), rect.Height());
        SetPivot(xPivot, yPivot);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnTransformMatrixUpdate(const Matrix4& matrix)
{
    CHECK_NULL_VOID(rsNode_);
    if (!transformMatrixModifier_.has_value()) {
        transformMatrixModifier_ = TransformMatrixModifier();
    }
    DecomposedTransform transform;
    if (!TransformUtil::DecomposeTransform(transform, matrix)) {
        // fallback to basic matrix decompose
        Rosen::Vector2f xyTranslateValue { static_cast<float>(matrix.Get(0, 3)), static_cast<float>(matrix.Get(1, 3)) };
        Rosen::Vector2f scaleValue { 0.0f, 0.0f };
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, scaleValue);
    } else {
        Rosen::Vector2f xyTranslateValue { transform.translate[0], transform.translate[1] };
        Rosen::Quaternion quaternion { static_cast<float>(transform.quaternion.GetX()),
            static_cast<float>(transform.quaternion.GetY()), static_cast<float>(transform.quaternion.GetZ()),
            static_cast<float>(transform.quaternion.GetW()) };
        Rosen::Vector2f scaleValue { transform.scale[0], transform.scale[1] };
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, scaleValue);
        AddOrChangeQuaternionModifier(
            rsNode_, transformMatrixModifier_->quaternion, transformMatrixModifier_->quaternionValue, quaternion);
    }
    RequestNextFrame();
}

RectF RosenRenderContext::GetPaintRectWithTransform()
{
    RectF rect;
    CHECK_NULL_RETURN(rsNode_, rect);
    rect = GetPaintRectWithoutTransform();
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto center = rsNode_->GetStagingProperties().GetPivot();
    // calculate new pos.
    auto centOffset = OffsetF(center[0] * rect.Width(), center[1] * rect.Height());
    auto centerPos = rect.GetOffset() + centOffset;
    auto newPos = centerPos - OffsetF(centOffset.GetX() * scale[0], centOffset.GetY() * scale[1]);
    newPos = newPos + OffsetF(translate[0], translate[1]);
    rect.SetOffset(newPos);
    // calculate new size.
    auto oldSize = rect.GetSize();
    auto newSize = SizeF(oldSize.Width() * scale[0], oldSize.Height() * scale[1]);
    rect.SetSize(newSize);
    return rect;
}

void RosenRenderContext::GetPointWithTransform(PointF& point)
{
    // TODO: add rotation and center support
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    point = PointF(point.GetX() / scale[0], point.GetY() / scale[1]);
}

RectF RosenRenderContext::GetPaintRectWithoutTransform()
{
    RectF rect;
    CHECK_NULL_RETURN(rsNode_, rect);
    auto paintRectVector = rsNode_->GetStagingProperties().GetBounds();
    rect.SetRect(paintRectVector[0], paintRectVector[1], paintRectVector[2], paintRectVector[3]);
    return rect;
}

void RosenRenderContext::NotifyTransition(
    const AnimationOption& option, const TransitionOptions& transOptions, bool isTransitionIn)
{
    CHECK_NULL_VOID(rsNode_);
    auto effect = GetRSTransitionWithoutType(transOptions);
    AnimationUtils::Animate(
        option,
        [rsNode = rsNode_, isTransitionIn, effect]() {
            CHECK_NULL_VOID_NOLOG(rsNode);
            rsNode->NotifyTransition(effect, isTransitionIn);
        },
        option.GetOnFinishEvent());
}

void RosenRenderContext::NotifyTransitionInner(const SizeF& frameSize, bool isTransitionIn)
{
    auto& transOptions = isTransitionIn ? propTransitionAppearing_ : propTransitionDisappearing_;
    CHECK_NULL_VOID_NOLOG(transOptions);
    CHECK_NULL_VOID(rsNode_);
    SetTransitionPivot(frameSize, isTransitionIn);
    auto effect = GetRSTransitionWithoutType(*transOptions, frameSize);
    // notice that we have been in animateTo, so do not need to use Animation closure to notify transition.
    rsNode_->NotifyTransition(effect, isTransitionIn);
}

void RosenRenderContext::OpacityAnimation(const AnimationOption& option, double begin, double end)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetAlpha(begin);
    AnimationUtils::Animate(
        option,
        [rsNode = rsNode_, endAlpha = end]() {
            CHECK_NULL_VOID_NOLOG(rsNode);
            rsNode->SetAlpha(endAlpha);
        },
        option.GetOnFinishEvent());
}

void RosenRenderContext::ScaleAnimation(const AnimationOption& option, double begin, double end)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetScale(begin);
    AnimationUtils::Animate(
        option,
        [rsNode = rsNode_, endScale = end]() {
            CHECK_NULL_VOID_NOLOG(rsNode);
            rsNode->SetScale(endScale);
        },
        option.GetOnFinishEvent());
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

void RosenRenderContext::UpdateBorderWidthF(const BorderWidthPropertyF& value)
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

void RosenRenderContext::OnAccessibilityFocusUpdate(bool isAccessibilityFocus)
{
    auto uiNode = GetHost();
    CHECK_NULL_VOID(uiNode);
    if (isAccessibilityFocus) {
        PaintAccessibilityFocus();
    } else {
        ClearAccessibilityFocus();
    }
    uiNode->OnAccessibilityEvent(isAccessibilityFocus ? AccessibilityEventType::ACCESSIBILITY_FOCUSED
                                                      : AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED);
}

void RosenRenderContext::PaintAccessibilityFocus()
{
    CHECK_NULL_VOID(rsNode_);
    Dimension focusPaddingVp = Dimension(0.0, DimensionUnit::VP);
    constexpr uint32_t ACCESSIBILITY_FOCUS_COLOR = 0xbf39b500;
    constexpr double ACCESSIBILITY_FOCUS_WIDTH = 4.0;
    Color paintColor(ACCESSIBILITY_FOCUS_COLOR);
    Dimension paintWidth(ACCESSIBILITY_FOCUS_WIDTH, DimensionUnit::PX);
    const auto& bounds = rsNode_->GetStagingProperties().GetBounds();
    RoundRect frameRect;
    frameRect.SetRect(RectF(0.0, 0.0, bounds.z_, bounds.w_));
    PaintFocusState(frameRect, focusPaddingVp, paintColor, paintWidth, true);
}

void RosenRenderContext::ClearAccessibilityFocus()
{
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(accessibilityFocusStateModifier_);
    rsNode_->RemoveModifier(accessibilityFocusStateModifier_);
    RequestNextFrame();
}

void RosenRenderContext::BdImagePaintTask(RSCanvas& canvas)
{
    CHECK_NULL_VOID(GetBorderImage());
    auto paintRect = GetPaintRectWithoutTransform();
    if (NearZero(paintRect.Width()) || NearZero(paintRect.Height())) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProps = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    const auto& widthProp = layoutProps->GetBorderWidthProperty();

    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dipScale = pipeline->GetDipScale();

    CHECK_NULL_VOID(bdImage_);
    auto image = DynamicCast<SkiaCanvasImage>(bdImage_)->GetCanvasImage();
    CHECK_NULL_VOID(image);
    RSImage rsImage(&image);

    BorderImagePainter borderImagePainter(*GetBdImage(), widthProp, paintRect.GetSize(), rsImage, dipScale);
    borderImagePainter.PaintBorderImage(OffsetF(0.0, 0.0), canvas);
}

void RosenRenderContext::PaintBorderImage()
{
    CHECK_NULL_VOID(rsNode_);

    auto paintTask = [weak = WeakClaim(this)](RSCanvas& canvas) {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->BdImagePaintTask(canvas);
    };

    if (!borderImageModifier_) {
        borderImageModifier_ = std::make_shared<BorderImageModifier>();
        rsNode_->AddModifier(borderImageModifier_);
    }
    borderImageModifier_->SetPaintTask(std::move(paintTask));
    borderImageModifier_->Modify();
}

DataReadyNotifyTask RosenRenderContext::CreateBorderImageDataReadyCallback()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        auto imageSourceInfo = rosenRenderContext->GetBorderImageSource().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        LOGI("borderImage data ready %{public}s", sourceInfo.ToString().c_str());
        rosenRenderContext->bdImageLoadingCtx_->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
}

LoadSuccessNotifyTask RosenRenderContext::CreateBorderImageLoadSuccessCallback()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto imageSourceInfo = ctx->GetBorderImageSource().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        ctx->bdImage_ = ctx->bdImageLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(ctx->bdImage_);
        LOGI("borderImage load success %{public}s", sourceInfo.ToString().c_str());
        if (ctx->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            ctx->PaintBorderImage();
            ctx->RequestNextFrame();
        }
    };
}

void RosenRenderContext::OnBorderImageUpdate(const RefPtr<BorderImage>& /*borderImage*/)
{
    CHECK_NULL_VOID(rsNode_);
    if (bdImageLoadingCtx_ && bdImage_) {
        PaintBorderImage();
        RequestNextFrame();
    }
}

void RosenRenderContext::OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo)
{
    CHECK_NULL_VOID(rsNode_);
    if (!bdImageLoadingCtx_ || borderImageSourceInfo != bdImageLoadingCtx_->GetSourceInfo()) {
        LoadNotifier bgLoadNotifier(
            CreateBorderImageDataReadyCallback(), CreateBorderImageLoadSuccessCallback(), nullptr);
        bdImageLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(borderImageSourceInfo, std::move(bgLoadNotifier));
        CHECK_NULL_VOID(bdImageLoadingCtx_);
        bdImageLoadingCtx_->LoadImageData();
    }
}

void RosenRenderContext::OnHasBorderImageSliceUpdate(bool tag) {}
void RosenRenderContext::OnHasBorderImageWidthUpdate(bool tag) {}
void RosenRenderContext::OnHasBorderImageOutsetUpdate(bool tag) {}
void RosenRenderContext::OnHasBorderImageRepeatUpdate(bool tag) {}
void RosenRenderContext::OnBorderImageGradientUpdate(const Gradient& gradient)
{
    CHECK_NULL_VOID(rsNode_);
    if (!gradient.IsValid()) {
        LOGE("Gradient not valid");
        return;
    }
    if (GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
        PaintBorderImageGradient();
    }
    RequestNextFrame();
}

void RosenRenderContext::PaintBorderImageGradient()
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(GetBorderImage());
    CHECK_NULL_VOID(GetBorderImageGradient());
    auto gradient = GetBorderImageGradient().value();
    if (!gradient.IsValid()) {
        LOGE("Gradient not valid");
        return;
    }
    auto paintSize = GetPaintRectWithoutTransform().GetSize();
    if (NearZero(paintSize.Width()) || NearZero(paintSize.Height())) {
        return;
    }
    auto layoutProperty = GetHost()->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto borderImageProperty = *GetBdImage();
    auto&& borderWidthProperty = layoutProperty->GetBorderWidthProperty();
    auto paintTask = [paintSize, borderImageProperty, &borderWidthProperty, gradient](RSCanvas& rsCanvas) mutable {
        auto rsImage = SkiaDecorationPainter::CreateBorderImageGradient(gradient, paintSize);
        BorderImagePainter borderImagePainter(borderImageProperty, borderWidthProperty, paintSize, rsImage,
            PipelineBase::GetCurrentContext()->GetDipScale());
        borderImagePainter.PaintBorderImage(OffsetF(0.0, 0.0), rsCanvas);
    };

    if (!borderImageModifier_) {
        borderImageModifier_ = std::make_shared<BorderImageModifier>();
        rsNode_->AddModifier(borderImageModifier_);
    }
    borderImageModifier_->SetPaintTask(std::move(paintTask));
    borderImageModifier_->Modify();
}

void RosenRenderContext::OnModifyDone()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    if (isBackBlurChanged_) {
        SetBackBlurFilter();
        isBackBlurChanged_ = false;
    }
    const auto& size = frameNode->GetGeometryNode()->GetFrameSize();
    if (!size.IsPositive()) {
        LOGD("first modify, make change in SyncGeometryProperties");
        return;
    }
    CHECK_NULL_VOID_NOLOG(isPositionChanged_);
    auto rect = AdjustPaintRect();
    if (!rect.GetSize().IsPositive()) {
        return;
    }
    rsNode_->SetBounds(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    isPositionChanged_ = false;
}

RectF RosenRenderContext::AdjustPaintRect()
{
    RectF rect;
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, rect);
    CHECK_NULL_RETURN(rsNode_, rect);
    const auto& geometryNode = frameNode->GetGeometryNode();
    if (rsNode_->GetType() == Rosen::RSUINodeType::SURFACE_NODE) {
        rect = geometryNode->GetContent() ? geometryNode->GetContent()->GetRect() : RectF();
        rect.SetOffset(geometryNode->GetFrameOffset() + geometryNode->GetContentOffset());
    } else {
        rect = geometryNode->GetFrameRect();
    }
    if (!rect.GetSize().IsPositive()) {
        LOGD("paint size is zero");
        return rect;
    }
    const auto& layoutConstraint = frameNode->GetGeometryNode()->GetParentLayoutConstraint();
    auto widthPercentReference = layoutConstraint.has_value() ? layoutConstraint->percentReference.Width()
                                                              : PipelineContext::GetCurrentRootWidth();
    auto heightPercentReference = layoutConstraint.has_value() ? layoutConstraint->percentReference.Height()
                                                               : PipelineContext::GetCurrentRootHeight();
    auto anchor = GetAnchorValue({});
    auto anchorWidthReference = rect.Width();
    auto anchorHeightReference = rect.Height();
    auto anchorX = ConvertToPx(anchor.GetX(), ScaleProperty::CreateScaleProperty(), anchorWidthReference);
    auto anchorY = ConvertToPx(anchor.GetY(), ScaleProperty::CreateScaleProperty(), anchorHeightReference);
    Dimension parentPaddingLeft;
    Dimension parentPaddingTop;
    // Position properties take precedence over offset locations.
    if (HasPosition()) {
        GetPaddingOfFirstFrameNodeParent(parentPaddingLeft, parentPaddingTop);
        auto position = GetPositionValue({}) + OffsetT<Dimension>(parentPaddingLeft, parentPaddingTop);
        auto posX = ConvertToPx(position.GetX(), ScaleProperty::CreateScaleProperty(), widthPercentReference);
        auto posY = ConvertToPx(position.GetY(), ScaleProperty::CreateScaleProperty(), heightPercentReference);
        rect.SetLeft(posX.value_or(0) - anchorX.value_or(0));
        rect.SetTop(posY.value_or(0) - anchorY.value_or(0));
        return rect;
    }
    if (HasOffset()) {
        GetPaddingOfFirstFrameNodeParent(parentPaddingLeft, parentPaddingTop);
        auto offset = GetOffsetValue({}) + OffsetT<Dimension>(parentPaddingLeft, parentPaddingTop);
        auto offsetX = ConvertToPx(offset.GetX(), ScaleProperty::CreateScaleProperty(), widthPercentReference);
        auto offsetY = ConvertToPx(offset.GetY(), ScaleProperty::CreateScaleProperty(), heightPercentReference);
        rect.SetLeft(rect.GetX() + offsetX.value_or(0) - anchorX.value_or(0));
        rect.SetTop(rect.GetY() + offsetY.value_or(0) - anchorY.value_or(0));
        return rect;
    }
    rect.SetLeft(rect.GetX() - anchorX.value_or(0));
    rect.SetTop(rect.GetY() - anchorY.value_or(0));
    return rect;
}

void RosenRenderContext::GetPaddingOfFirstFrameNodeParent(Dimension& parentPaddingLeft, Dimension& parentPaddingTop)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto frameNodeParent = frameNode->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(frameNodeParent);
    auto layoutProperty = frameNodeParent->GetLayoutProperty();
    if (layoutProperty && layoutProperty->GetPaddingProperty()) {
        parentPaddingLeft =
            layoutProperty->GetPaddingProperty()->left.value_or(CalcLength(Dimension(0))).GetDimension();
        parentPaddingTop = layoutProperty->GetPaddingProperty()->top.value_or(CalcLength(Dimension(0))).GetDimension();
    }
}

void RosenRenderContext::OnPositionUpdate(const OffsetT<Dimension>& /*value*/)
{
    isPositionChanged_ = true;
}

void RosenRenderContext::OnOffsetUpdate(const OffsetT<Dimension>& /*value*/)
{
    isPositionChanged_ = true;
}

void RosenRenderContext::OnAnchorUpdate(const OffsetT<Dimension>& /*value*/)
{
    isPositionChanged_ = true;
}

void RosenRenderContext::OnZIndexUpdate(int32_t value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetPositionZ(static_cast<float>(value));
}

void RosenRenderContext::ResetBlendBgColor()
{
    CHECK_NULL_VOID(rsNode_);
    blendColor_ = Color::TRANSPARENT;
    auto blendColor =
        GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColor_).BlendColor(hoveredColor_);
    rsNode_->SetBackgroundColor(blendColor.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::BlendBgColor(const Color& color)
{
    CHECK_NULL_VOID(rsNode_);
    blendColor_ = color;
    auto blendColor =
        GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColor_).BlendColor(hoveredColor_);
    rsNode_->SetBackgroundColor(blendColor.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::ResetBlendBorderColor()
{
    CHECK_NULL_VOID(rsNode_);
    auto leftColor = (Color::TRANSPARENT).GetValue();
    auto topColor = (Color::TRANSPARENT).GetValue();
    auto rightColor = (Color::TRANSPARENT).GetValue();
    auto bottomColor = (Color::TRANSPARENT).GetValue();
    if (GetBorderColor().has_value()) {
        leftColor = GetBorderColor()->leftColor.value_or(Color::TRANSPARENT).GetValue();
        topColor = GetBorderColor()->topColor.value_or(Color::TRANSPARENT).GetValue();
        rightColor = GetBorderColor()->rightColor.value_or(Color::TRANSPARENT).GetValue();
        bottomColor = GetBorderColor()->bottomColor.value_or(Color::TRANSPARENT).GetValue();
    }
    rsNode_->SetBorderColor(leftColor, topColor, rightColor, bottomColor);
    RequestNextFrame();
}

void RosenRenderContext::BlendBorderColor(const Color& color)
{
    CHECK_NULL_VOID(rsNode_);
    auto leftColor = color.GetValue();
    auto topColor = color.GetValue();
    auto rightColor = color.GetValue();
    auto bottomColor = color.GetValue();
    if (GetBorderColor().has_value()) {
        leftColor = (GetBorderColor()->leftColor.value_or(Color::TRANSPARENT).BlendColor(color)).GetValue();
        topColor = (GetBorderColor()->topColor.value_or(Color::TRANSPARENT).BlendColor(color)).GetValue();
        rightColor = (GetBorderColor()->rightColor.value_or(Color::TRANSPARENT).BlendColor(color)).GetValue();
        bottomColor = (GetBorderColor()->bottomColor.value_or(Color::TRANSPARENT).BlendColor(color)).GetValue();
    }
    rsNode_->SetBorderColor(leftColor, topColor, rightColor, bottomColor);
    RequestNextFrame();
}

void RosenRenderContext::PaintFocusState(
    const RoundRect& paintRect, const Color& paintColor, const Dimension& paintWidth, bool isAccessibilityFocus)
{
    LOGD("PaintFocusState rect is (%{public}f, %{public}f, %{public}f, %{public}f). Color is %{public}s, PainWidth is "
         "%{public}s",
        paintRect.GetRect().Left(), paintRect.GetRect().Top(), paintRect.GetRect().Width(),
        paintRect.GetRect().Height(), paintColor.ColorToString().c_str(), paintWidth.ToString().c_str());
    CHECK_NULL_VOID(rsNode_);

    auto borderWidthPx = static_cast<float>(paintWidth.ConvertToPx());

    auto paintTask = [paintColor, borderWidthPx](const RSRoundRect& rrect, RSCanvas& rsCanvas) mutable {
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetColor(ToRSColor(paintColor));
        pen.SetWidth(borderWidthPx);
        rsCanvas.AttachPen(pen);
        rsCanvas.DrawRoundRect(rrect);
    };

    if (isAccessibilityFocus) {
        if (!accessibilityFocusStateModifier_) {
            accessibilityFocusStateModifier_ = std::make_shared<FocusStateModifier>();
        }
        accessibilityFocusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
        accessibilityFocusStateModifier_->SetPaintTask(std::move(paintTask));
        rsNode_->AddModifier(accessibilityFocusStateModifier_);
    } else {
        if (!focusStateModifier_) {
            // TODO: Add property data
            focusStateModifier_ = std::make_shared<FocusStateModifier>();
        }
        focusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
        focusStateModifier_->SetPaintTask(std::move(paintTask));
        rsNode_->AddModifier(focusStateModifier_);
    }
    RequestNextFrame();
}

void RosenRenderContext::PaintFocusState(const RoundRect& paintRect, const Dimension& focusPaddingVp,
    const Color& paintColor, const Dimension& paintWidth, bool isAccessibilityFocus)
{
    LOGD("PaintFocusState rect is (%{public}f, %{public}f, %{public}f, %{public}f). focusPadding is %{public}s, Color "
         "is %{public}s, PainWidth is %{public}s",
        paintRect.GetRect().Left(), paintRect.GetRect().Top(), paintRect.GetRect().Width(),
        paintRect.GetRect().Height(), focusPaddingVp.ToString().c_str(), paintColor.ColorToString().c_str(),
        paintWidth.ToString().c_str());

    auto paintWidthPx = static_cast<float>(paintWidth.ConvertToPx());
    auto borderPaddingPx = static_cast<float>(focusPaddingVp.ConvertToPx());
    auto focusPaintRectLeft = paintRect.GetRect().Left() - borderPaddingPx - paintWidthPx / 2;
    auto focusPaintRectTop = paintRect.GetRect().Top() - borderPaddingPx - paintWidthPx / 2;
    auto focusPaintRectWidth = paintRect.GetRect().Width() + 2 * borderPaddingPx + paintWidthPx;
    auto focusPaintRectHeight = paintRect.GetRect().Height() + 2 * borderPaddingPx + paintWidthPx;

    EdgeF diffRadius = { borderPaddingPx + paintWidthPx, borderPaddingPx + paintWidthPx };
    auto focusPaintCornerTopLeft = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS) + diffRadius;
    auto focusPaintCornerTopRight = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS) + diffRadius;
    auto focusPaintCornerBottomLeft = paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS) + diffRadius;
    auto focusPaintCornerBottomRight = paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS) + diffRadius;

    RoundRect focusPaintRect;
    focusPaintRect.SetRect(RectF(focusPaintRectLeft, focusPaintRectTop, focusPaintRectWidth, focusPaintRectHeight));
    focusPaintRect.SetCornerRadius(
        RoundRect::CornerPos::TOP_LEFT_POS, focusPaintCornerTopLeft.x, focusPaintCornerTopLeft.y);
    focusPaintRect.SetCornerRadius(
        RoundRect::CornerPos::TOP_RIGHT_POS, focusPaintCornerTopRight.x, focusPaintCornerTopRight.y);
    focusPaintRect.SetCornerRadius(
        RoundRect::CornerPos::BOTTOM_LEFT_POS, focusPaintCornerBottomLeft.x, focusPaintCornerBottomLeft.y);
    focusPaintRect.SetCornerRadius(
        RoundRect::CornerPos::BOTTOM_RIGHT_POS, focusPaintCornerBottomRight.x, focusPaintCornerBottomRight.y);

    PaintFocusState(focusPaintRect, paintColor, paintWidth, isAccessibilityFocus);
}

void RosenRenderContext::PaintFocusState(
    const Dimension& focusPaddingVp, const Color& paintColor, const Dimension& paintWidth)
{
    const auto& bounds = rsNode_->GetStagingProperties().GetBounds();
    const auto& radius = rsNode_->GetStagingProperties().GetCornerRadius();

    RoundRect frameRect;
    frameRect.SetRect(RectF(0, 0, bounds.z_, bounds.w_));
    frameRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radius.x_, radius.x_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radius.y_, radius.y_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radius.z_, radius.z_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radius.w_, radius.w_);

    PaintFocusState(frameRect, focusPaddingVp, paintColor, paintWidth);
}

void RosenRenderContext::ClearFocusState()
{
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(focusStateModifier_);
    rsNode_->RemoveModifier(focusStateModifier_);
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

void RosenRenderContext::FlushContentModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<ContentModifierAdapter>(ConvertContentModifier(modifier));
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
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

void RosenRenderContext::FlushOverlayModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(modifier));
    auto rect = AceType::DynamicCast<OverlayModifier>(modifier)->GetBoundsRect();
    std::shared_ptr<Rosen::RectI> overlayRect =
        std::make_shared<Rosen::RectI>(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    modifierAdapter->SetOverlayBounds(overlayRect);
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
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
    CHECK_NULL_RETURN_NOLOG(recorder_, nullptr);
    return recorder_->finishRecordingAsPicture();
}

void RosenRenderContext::Restore()
{
    const auto& canvas = GetCanvas();
    CHECK_NULL_VOID(canvas);
    canvas->Restore();
}

void RosenRenderContext::RebuildFrame(FrameNode* /*self*/, const std::list<RefPtr<FrameNode>>& children)
{
    ReCreateRsNodeTree(children);
    RequestNextFrame();
}

std::list<std::shared_ptr<Rosen::RSNode>> RosenRenderContext::GetChildrenRSNodes(
    const std::list<RefPtr<FrameNode>>& frameChildren)
{
    std::list<std::shared_ptr<Rosen::RSNode>> rsNodes;
    for (const auto& child : frameChildren) {
        if (!child) {
            continue;
        }
        auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
        if (!rosenRenderContext) {
            continue;
        }
        auto rsnode = rosenRenderContext->GetRSNode();
        if (rsnode) {
            rsNodes.emplace_back(rsnode);
        }
    }
    return rsNodes;
}

void RosenRenderContext::ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_VOID(rsNode_);
    auto nowRSNodes = GetChildrenRSNodes(children);
    std::vector<OHOS::Rosen::NodeId> childNodeIds;
    for (auto& child : nowRSNodes) {
        childNodeIds.emplace_back(child->GetId());
    }
    if (childNodeIds == rsNode_->GetChildren()) {
        return;
    }
    rsNode_->ClearChildren();
    for (const auto& rsnode : nowRSNodes) {
        rsNode_->AddChild(rsnode, -1);
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
        auto rsNode = rosenRenderContext->GetRSNode();
        if (rsNode) {
            rsNode_->AddChild(rsNode, -1);
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
        auto rsNode = rosenRenderContext->GetRSNode();
        if (rsNode) {
            rsNode_->RemoveChild(rsNode);
        }
    }
}

void RosenRenderContext::MoveFrame(FrameNode* /*self*/, const RefPtr<FrameNode>& child, int32_t index)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(child);
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
    CHECK_NULL_VOID(rosenRenderContext);
    auto rsNode = rosenRenderContext->GetRSNode();
    // no need to check nullptr since MoveChild will take care of it
    rsNode_->MoveChild(rsNode, index);
}

void RosenRenderContext::AnimateHoverEffectScale(bool isHovered)
{
    LOGD("HoverEffect.Scale: isHovered = %{public}d", isHovered);
    if ((isHovered && isHoveredScale_) || (!isHovered && !isHoveredScale_)) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appTheme = pipeline->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);

    float hoverScaleFrom = isHovered ? appTheme->GetHoverScaleStart() : appTheme->GetHoverScaleEnd();
    float hoverColorTo = isHovered ? appTheme->GetHoverScaleEnd() : appTheme->GetHoverScaleStart();
    float scaleStart = hoverScaleFrom;
    float scaleEnd = hoverColorTo;
    int32_t themeDuration = appTheme->GetHoverDuration();

    LOGD("HoverEffect.Scale: scale from %{public}f to %{public}f", scaleStart, scaleEnd);
    rsNode_->SetScale(scaleStart);
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    RSNode::Animate(protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [rsNode = rsNode_, scaleEnd]() {
            if (rsNode) {
                rsNode->SetScale(scaleEnd);
            }
        });
    isHoveredScale_ = isHovered;
}

void RosenRenderContext::AnimateHoverEffectBoard(bool isHovered)
{
    LOGD("HoverEffect.Highlight: isHovered = %{public}d", isHovered);
    if ((isHovered && isHoveredBoard_) || (!isHovered && !isHoveredBoard_)) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appTheme = pipeline->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);

    Color hoverColorFrom = isHovered ? appTheme->GetHoverHighlightStart() : appTheme->GetHoverHighlightEnd();
    Color hoverColorTo = isHovered ? appTheme->GetHoverHighlightEnd() : appTheme->GetHoverHighlightStart();
    Color highlightStart =
        GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColor_).BlendColor(hoverColorFrom);
    Color highlightEnd =
        GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColor_).BlendColor(hoverColorTo);
    int32_t themeDuration = appTheme->GetHoverDuration();

    LOGD("HoverEffect.Highlight: background color from %{public}x to %{public}x", highlightStart.GetValue(),
        highlightEnd.GetValue());
    rsNode_->SetBackgroundColor(highlightStart.GetValue());
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    RSNode::Animate(protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [rsNode = rsNode_, highlightEnd]() {
            CHECK_NULL_VOID_NOLOG(rsNode);
            rsNode->SetBackgroundColor(highlightEnd.GetValue());
        });
    hoveredColor_ = hoverColorTo;
    isHoveredBoard_ = isHovered;
}

void RosenRenderContext::UpdateBackBlurRadius(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurRadius(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    isBackBlurChanged_ = true;
}

void RosenRenderContext::OnFrontBlurRadiusUpdate(const Dimension& radius)
{
    std::shared_ptr<Rosen::RSFilter> frontFilter = nullptr;
    if (radius.IsValid()) {
        float radiusPx = radius.ConvertToPx();
        float frontBlurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
        frontFilter = Rosen::RSFilter::CreateBlurFilter(frontBlurRadius, frontBlurRadius);
    }
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFilter(frontFilter);
    RequestNextFrame();
}

void RosenRenderContext::OnBackShadowUpdate(const Shadow& shadow)
{
    CHECK_NULL_VOID(rsNode_);
    if (!shadow.IsValid()) {
        if (shadow.GetHardwareAcceleration()) {
            rsNode_->SetShadowElevation(0.0);
        } else {
            rsNode_->SetShadowRadius(0.0);
        }
        RequestNextFrame();
        return;
    }
    rsNode_->SetShadowColor(shadow.GetColor().GetValue());
    rsNode_->SetShadowOffsetX(shadow.GetOffset().GetX());
    rsNode_->SetShadowOffsetY(shadow.GetOffset().GetY());
    if (shadow.GetHardwareAcceleration()) {
        rsNode_->SetShadowElevation(shadow.GetElevation());
    } else {
        rsNode_->SetShadowRadius(SkiaDecorationPainter::ConvertRadiusToSigma(shadow.GetBlurRadius()));
    }
    RequestNextFrame();
}

// called when frameNode size changes
void RosenRenderContext::PaintGraphics()
{
    CHECK_NULL_VOID(rsNode_);
    auto&& graphicProps = GetOrCreateGraphics();
    if (graphicProps->HasFrontGrayScale()) {
        auto grayScale = graphicProps->GetFrontGrayScaleValue();
        SetModifier(grayScaleModifier_, grayScale.Value());
    }

    if (graphicProps->HasFrontBrightness()) {
        auto brightness = graphicProps->GetFrontBrightnessValue();
        SetModifier(brightnessModifier_, brightness.Value());
    }

    if (graphicProps->HasFrontContrast()) {
        auto contrast = graphicProps->GetFrontContrastValue();
        SetModifier(contrastModifier_, contrast.Value());
    }

    if (graphicProps->HasFrontSaturate()) {
        auto saturate = graphicProps->GetFrontSaturateValue();
        SetModifier(saturateModifier_, saturate.Value());
    }

    if (graphicProps->HasFrontSepia()) {
        auto sepia = graphicProps->GetFrontSepiaValue();
        SetModifier(sepiaModifier_, sepia.Value());
    }

    if (graphicProps->HasFrontInvert()) {
        auto invert = graphicProps->GetFrontInvertValue();
        SetModifier(invertModifier_, invert.Value());
    }

    if (graphicProps->HasFrontHueRotate()) {
        auto hueRotate = graphicProps->GetFrontHueRotateValue();
        SetModifier(hueRotateModifier_, hueRotate);
    }

    if (graphicProps->HasFrontColorBlend()) {
        auto colorBlend = graphicProps->GetFrontColorBlendValue();
        SetModifier(colorBlendModifier_, ColorBlend(colorBlend));
    }
}

// helper function to check if frame react is valid
bool RosenRenderContext::RectIsNull()
{
    RectF rect = GetPaintRectWithoutTransform();
    return NearZero(rect.Width()) || NearZero(rect.Height());
}

template<typename T, typename D>
void RosenRenderContext::SetModifier(std::shared_ptr<T>& modifier, D data)
{
    if (!modifier) {
        LOGD("create new modifier");
        modifier = std::make_shared<T>();
        rsNode_->AddModifier(modifier);
    }
    modifier->SetCustomData(data);
}

// helper function to update one of the graphic effects
template<typename T, typename D>
void RosenRenderContext::UpdateGraphic(std::shared_ptr<T>& modifier, D data)
{
    CHECK_NULL_VOID_NOLOG(!RectIsNull());
    LOGD("updating graphic effect");
    SetModifier(modifier, data);
    RequestNextFrame();
}

void RosenRenderContext::OnFrontBrightnessUpdate(const Dimension& brightness)
{
    UpdateGraphic(brightnessModifier_, brightness.Value());
}

void RosenRenderContext::OnFrontGrayScaleUpdate(const Dimension& grayScale)
{
    UpdateGraphic(grayScaleModifier_, grayScale.Value());
}

void RosenRenderContext::OnFrontContrastUpdate(const Dimension& contrast)
{
    UpdateGraphic(contrastModifier_, contrast.Value());
}

void RosenRenderContext::OnFrontSaturateUpdate(const Dimension& saturate)
{
    UpdateGraphic(saturateModifier_, saturate.Value());
}

void RosenRenderContext::OnFrontSepiaUpdate(const Dimension& sepia)
{
    UpdateGraphic(sepiaModifier_, sepia.Value());
}

void RosenRenderContext::OnFrontInvertUpdate(const Dimension& invert)
{
    UpdateGraphic(invertModifier_, invert.Value());
}

void RosenRenderContext::OnFrontHueRotateUpdate(float hueRotate)
{
    UpdateGraphic(hueRotateModifier_, hueRotate);
}

void RosenRenderContext::OnFrontColorBlendUpdate(const Color& colorBlend)
{
    UpdateGraphic(colorBlendModifier_, ColorBlend(colorBlend));
}

void RosenRenderContext::UpdateTransition(const TransitionOptions& options)
{
    CHECK_NULL_VOID(rsNode_);
    if (options.Type == TransitionType::ALL || options.Type == TransitionType::APPEARING) {
        if (!propTransitionAppearing_) {
            propTransitionAppearing_ = std::make_unique<TransitionOptions>(options);
        } else {
            *propTransitionAppearing_ = options;
        }
        propTransitionAppearing_->Type = TransitionType::APPEARING;
    }
    if (options.Type == TransitionType::ALL || options.Type == TransitionType::DISAPPEARING) {
        if (!propTransitionDisappearing_) {
            propTransitionDisappearing_ = std::make_unique<TransitionOptions>(options);
        } else {
            *propTransitionDisappearing_ = options;
        }
        propTransitionDisappearing_->Type = TransitionType::DISAPPEARING;
    }
}

std::shared_ptr<Rosen::RSTransitionEffect> RosenRenderContext::GetRSTransitionWithoutType(
    const TransitionOptions& options, const SizeF& frameSize)
{
    std::shared_ptr<Rosen::RSTransitionEffect> effect = Rosen::RSTransitionEffect::Create();
    if (options.HasOpacity()) {
        effect = effect->Opacity(options.GetOpacityValue());
    }
    if (options.HasTranslate()) {
        const auto& translate = options.GetTranslateValue();
        effect = effect->Translate({ static_cast<float>(translate.x.ConvertToPxWithSize(frameSize.Width())),
            static_cast<float>(translate.y.ConvertToPxWithSize(frameSize.Height())),
            static_cast<float>(translate.z.ConvertToPx()) });
    }
    if (options.HasScale()) {
        const auto& scale = options.GetScaleValue();
        effect = effect->Scale({ scale.xScale, scale.yScale, scale.zScale });
    }
    if (options.HasRotate()) {
        const auto& rotate = options.GetRotateValue();
        effect = effect->Rotate({ rotate.xDirection, rotate.yDirection, rotate.zDirection, rotate.angle });
    }
    return effect;
}

void RosenRenderContext::PaintGradient(const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto& gradientProperty = GetOrCreateGradient();
    if (gradientProperty->HasLinearGradient()) {
        auto gradient = gradientProperty->GetLinearGradientValue();
        auto shader = SkiaDecorationPainter::CreateGradientShader(gradient, frameSize);
        rsNode_->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
    }
    if (gradientProperty->HasRadialGradient()) {
        auto gradient = gradientProperty->GetRadialGradientValue();
        auto shader = SkiaDecorationPainter::CreateGradientShader(gradient, frameSize);
        rsNode_->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
    }
    if (gradientProperty->HasSweepGradient()) {
        auto gradient = gradientProperty->GetSweepGradientValue();
        auto shader = SkiaDecorationPainter::CreateGradientShader(gradient, frameSize);
        rsNode_->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
    }
}

void RosenRenderContext::OnLinearGradientUpdate(const NG::Gradient& gradient)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        PaintGradient(rect.GetSize());
    }
    RequestNextFrame();
}

void RosenRenderContext::OnRadialGradientUpdate(const NG::Gradient& gradient)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        PaintGradient(rect.GetSize());
    }
    RequestNextFrame();
}

void RosenRenderContext::OnSweepGradientUpdate(const NG::Gradient& gradient)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        PaintGradient(rect.GetSize());
    }
    RequestNextFrame();
}

void RosenRenderContext::PaintClip(const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto& clip = GetOrCreateClip();
    if (clip->HasClipShape()) {
        auto basicShape = clip->GetClipShapeValue();
        auto skPath = SkiaDecorationPainter::SkiaCreateSkPath(basicShape, frameSize);
        if (skPath.isEmpty()) {
            return;
        }
        rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
    }

    if (clip->HasClipMask()) {
        auto basicShape = clip->GetClipMaskValue();
        auto skPath = SkiaDecorationPainter::SkiaCreateSkPath(basicShape, frameSize);
        rsNode_->SetMask(Rosen::RSMask::CreatePathMask(skPath, SkiaDecorationPainter::CreateMaskSkPaint(basicShape)));
    }
}

void RosenRenderContext::SetClipBoundsWithCommands(const std::string& commands)
{
    CHECK_NULL_VOID(rsNode_);
    SkPath skPath;
    SkParsePath::FromSVGString(commands.c_str(), &skPath);
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
}

void RosenRenderContext::ClipWithRect(const RectF& rectF)
{
    CHECK_NULL_VOID(rsNode_);
    SkPath skPath;
    skPath.addRect(rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height());
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
}

void RosenRenderContext::OnClipShapeUpdate(const RefPtr<BasicShape>& /*basicShape*/)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        PaintClip(SizeF(rect.Width(), rect.Height()));
    }
    RequestNextFrame();
}

void RosenRenderContext::OnClipEdgeUpdate(bool isClip)
{
    CHECK_NULL_VOID(rsNode_);
    if (isClip) {
        rsNode_->SetClipToBounds(true);
    } else {
        // In the internal implementation, some nodes call SetClipToBounds(true), some call SetClipToFrame(true).
        // If the developer set clip to false, we should disable all internal clips
        // so that the child component can go beyond the parent component
        rsNode_->SetClipToBounds(false);
        rsNode_->SetClipToFrame(false);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnClipMaskUpdate(const RefPtr<BasicShape>& /*basicShape*/)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        PaintClip(SizeF(rect.Width(), rect.Height()));
    }
    RequestNextFrame();
}

RefPtr<PageTransitionEffect> RosenRenderContext::GetDefaultPageTransition(PageTransitionType type)
{
    auto resultEffect = AceType::MakeRefPtr<PageTransitionEffect>(type, PageTransitionOption());
    resultEffect->SetScaleEffect(ScaleOptions(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct));
    TranslateOptions translate;
    auto rect = GetPaintRectWithoutTransform();
    switch (type) {
        case PageTransitionType::ENTER_PUSH:
        case PageTransitionType::EXIT_POP:
            translate.x = Dimension(rect.Width());
            break;
        case PageTransitionType::ENTER_POP:
        case PageTransitionType::EXIT_PUSH:
            translate.x = Dimension(-rect.Width());
            break;
        default:
            LOGI("unexpected transition type");
            break;
    }
    resultEffect->SetTranslateEffect(translate);
    resultEffect->SetOpacityEffect(1);
    return resultEffect;
}

RefPtr<PageTransitionEffect> RosenRenderContext::GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition)
{
    auto resultEffect = AceType::MakeRefPtr<PageTransitionEffect>(
        transition->GetPageTransitionType(), transition->GetPageTransitionOption());
    resultEffect->SetScaleEffect(
        transition->GetScaleEffect().value_or(ScaleOptions(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct)));
    TranslateOptions translate;
    // slide and translate, only one can be effective
    if (transition->GetSlideEffect().has_value()) {
        auto rect = GetPaintRectWithoutTransform();
        switch (transition->GetSlideEffect().value()) {
            case SlideEffect::LEFT:
                translate.x = Dimension(-rect.Width());
                break;
            case SlideEffect::RIGHT:
                translate.x = Dimension(rect.Width());
                break;
            case SlideEffect::BOTTOM:
                translate.y = Dimension(rect.Height());
                break;
            case SlideEffect::TOP:
                translate.y = Dimension(-rect.Height());
                break;
            default:
                LOGW("unexpected slide effect");
                break;
        }
    } else if (transition->GetTranslateEffect().has_value()) {
        auto rect = GetPaintRectWithoutTransform();
        const auto& translateOptions = transition->GetTranslateEffect();
        translate.x = Dimension(translateOptions->x.ConvertToPxWithSize(rect.Width()));
        translate.y = Dimension(translateOptions->y.ConvertToPxWithSize(rect.Height()));
        translate.z = Dimension(translateOptions->z.ConvertToPx());
    }
    resultEffect->SetTranslateEffect(translate);
    resultEffect->SetOpacityEffect(transition->GetOpacityEffect().value_or(1));
    return resultEffect;
}

bool RosenRenderContext::TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish)
{
    bool transitionIn = true;
    if (type == PageTransitionType::ENTER_PUSH || type == PageTransitionType::ENTER_POP) {
        transitionIn = true;
    } else if (type == PageTransitionType::EXIT_PUSH || type == PageTransitionType::EXIT_POP) {
        transitionIn = false;
    } else {
        LOGW("unexpected transition type");
        return false;
    }
    CHECK_NULL_RETURN(rsNode_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto transition = pattern->FindPageTransitionEffect(type);
    RefPtr<PageTransitionEffect> effect;
    AnimationOption option;
    if (transition) {
        effect = GetPageTransitionEffect(transition);
        option.SetCurve(transition->GetCurve());
        option.SetDuration(transition->GetDuration());
        option.SetDelay(transition->GetDelay());
    } else {
        effect = GetDefaultPageTransition(type);
        const int32_t pageTransitionDuration = 300;
        option.SetCurve(Curves::LINEAR);
        option.SetDuration(pageTransitionDuration);
    }
    const auto& scaleOptions = effect->GetScaleEffect();
    const auto& translateOptions = effect->GetTranslateEffect();
    UpdateTransformCenter(DimensionOffset(scaleOptions->centerX, scaleOptions->centerY));

    if (transitionIn) {
        UpdateTransformScale(VectorF(scaleOptions->xScale, scaleOptions->yScale));
        UpdateTransformTranslate(translateOptions.value());
        UpdateOpacity(effect->GetOpacityEffect().value());
        AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), onFinish);
        UpdateTransformScale(VectorF(1.0f, 1.0f));
        UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
        UpdateOpacity(1.0);
        AnimationUtils::CloseImplicitAnimation();
        return true;
    }
    UpdateTransformScale(VectorF(1.0f, 1.0f));
    UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    UpdateOpacity(1.0);
    AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), onFinish);
    UpdateTransformScale(VectorF(scaleOptions->xScale, scaleOptions->yScale));
    UpdateTransformTranslate(translateOptions.value());
    UpdateOpacity(effect->GetOpacityEffect().value());
    AnimationUtils::CloseImplicitAnimation();
    return true;
}

void RosenRenderContext::PaintOverlayText()
{
    CHECK_NULL_VOID(rsNode_);
    auto& overlay = GetOrCreateOverlay();
    if (overlay->HasOverlayText()) {
        auto overlayText = overlay->GetOverlayTextValue();
        if (modifier_) {
            modifier_->SetCustomData(NG::OverlayTextData(overlayText));
        } else {
            modifier_ = std::make_shared<OverlayTextModifier>();
            rsNode_->AddModifier(modifier_);
            modifier_->SetCustomData(NG::OverlayTextData(overlayText));
        }
    }
}

void RosenRenderContext::OnOverlayTextUpdate(const OverlayOptions& overlay)
{
    if (!RectIsNull()) {
        PaintOverlayText();
    }
    RequestNextFrame();
}

void RosenRenderContext::OnMotionPathUpdate(const MotionPathOption& motionPath)
{
    CHECK_NULL_VOID(rsNode_);
    auto motionOption = Rosen::RSMotionPathOption(motionPath.GetPath());
    motionOption.SetBeginFraction(motionPath.GetBegin());
    motionOption.SetEndFraction(motionPath.GetEnd());
    motionOption.SetRotationMode(
        motionPath.GetRotate() ? Rosen::RotationMode::ROTATE_AUTO : Rosen::RotationMode::ROTATE_NONE);
    motionOption.SetPathNeedAddOrigin(HasOffset());
    rsNode_->SetMotionPathOption(std::make_shared<Rosen::RSMotionPathOption>(motionOption));
    RequestNextFrame();
}

void RosenRenderContext::SetSharedTranslate(float xTranslate, float yTranslate)
{
    if (!sharedTransitionModifier_) {
        sharedTransitionModifier_ = std::make_unique<SharedTransitionModifier>();
    }
    AddOrChangeTranslateModifier(rsNode_, sharedTransitionModifier_->translateXY,
        sharedTransitionModifier_->translateXYValue, { xTranslate, yTranslate });
}

void RosenRenderContext::ResetSharedTranslate()
{
    CHECK_NULL_VOID_NOLOG(sharedTransitionModifier_);
    CHECK_NULL_VOID_NOLOG(sharedTransitionModifier_->translateXY);
    CHECK_NULL_VOID_NOLOG(rsNode_);
    rsNode_->RemoveModifier(sharedTransitionModifier_->translateXY);
    sharedTransitionModifier_->translateXYValue = nullptr;
    sharedTransitionModifier_->translateXY = nullptr;
}

void RosenRenderContext::ResetPageTransitionEffect()
{
    UpdateTransformScale(VectorF(1.0f, 1.0f));
    UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    UpdateOpacity(1.0);
}

void RosenRenderContext::AddChild(const RefPtr<RenderContext>& renderContext, int index)
{
    CHECK_NULL_VOID(rsNode_);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    auto child = rosenRenderContext->GetRSNode();
    rsNode_->AddChild(child, index);
}

void RosenRenderContext::SetBounds(float positionX, float positionY, float width, float height)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBounds(positionX, positionY, width, height);
}

void RosenRenderContext::ClearDrawCommands()
{
    StartRecording();
    StopRecordingIfNeeded();
}

void RosenRenderContext::SetRSNode(const std::shared_ptr<RSNode>& externalNode)
{
    // Update rsNode_ to externalNode.
    if (externalNode == rsNode_) {
        return;
    }
    rsNode_ = externalNode;

    // TODO: need move property to new rs node.
    ResetTransform();
    ResetTransformMatrix();

    // after update, tell parent to update RSNode hierarchy.
    auto uiNode = GetHost();
    CHECK_NULL_VOID(uiNode);
    auto parentUINode = uiNode->GetParent();
    CHECK_NULL_VOID(parentUINode);
    parentUINode->MarkNeedSyncRenderTree();
    parentUINode->RebuildRenderContextTree();
}

void RosenRenderContext::OnMouseSelectUpdate(bool isSelected, const Color& fillColor, const Color& strokeColor)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    RectF rect = RectF();
    if (isSelected) {
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        rect = geometryNode->GetFrameRect();
        rect.SetOffset(OffsetF());
    }

    UpdateMouseSelectWithRect(rect, fillColor, strokeColor);
}

void RosenRenderContext::UpdateMouseSelectWithRect(const RectF& rect, const Color& fillColor, const Color& strokeColor)
{
    if (!rect.IsValid()) {
        LOGE("UpdateMouseSelectWithRect: selected rect not valid");
        return;
    }
    PaintMouseSelectRect(rect, fillColor, strokeColor);
    RequestNextFrame();
}

void RosenRenderContext::PaintMouseSelectRect(const RectF& rect, const Color& fillColor, const Color& strokeColor)
{
    if (mouseSelectModifier_) {
        mouseSelectModifier_->SetSelectRect(rect);
        return;
    }

    auto paintTask = [&fillColor, &strokeColor](const RectF& rect, RSCanvas& rsCanvas) mutable {
        RSBrush brush;
        brush.SetColor(ToRSColor(fillColor));
        rsCanvas.AttachBrush(brush);
        rsCanvas.DrawRect(ToRSRect(rect));
        rsCanvas.DetachBrush();
        RSPen pen;
        pen.SetColor(ToRSColor(strokeColor));
        rsCanvas.AttachPen(pen);
        rsCanvas.DrawRect(ToRSRect(rect));
    };

    mouseSelectModifier_ = std::make_shared<MouseSelectModifier>();
    mouseSelectModifier_->SetPaintTask(std::move(paintTask));
    rsNode_->AddModifier(mouseSelectModifier_);
}

void RosenRenderContext::DumpInfo() const
{
    if (rsNode_) {
        DumpLog::GetInstance().AddDesc(rsNode_->DumpNode(0));
    }
}

} // namespace OHOS::Ace::NG
