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

#include <cmath>
#include <cstdint>
#include <memory>

#include "render_service_client/core/pipeline/rs_node_map.h"
#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/graphics_modifier.h"
#include "core/components_ng/render/adapter/overlay_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/adapter/skia_canvas_image.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"
#include "core/components_ng/render/border_image_painter.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {

RosenRenderContext::~RosenRenderContext()
{
    StopRecordingIfNeeded();
}

void RosenRenderContext::StartRecording()
{
    CHECK_NULL_VOID(rsNode_);
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

void RosenRenderContext::InitContext(bool isRoot, const std::optional<std::string>& surfaceName, bool useExternalNode)
{
    // skip if useExternalNode is true or node already created
    if (useExternalNode || rsNode_ != nullptr) {
        return;
    }

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
    rsNode_->SetPivot(0.5f, 0.5f); // default pivot is center

    if (propTransform_ && propTransform_->HasTransformCenter()) {
        auto vec = propTransform_->GetTransformCenterValue();
        if (vec.GetX().Unit() == DimensionUnit::PERCENT) {
            rsNode_->SetPivot(vec.GetX().Value(), vec.GetY().Value());
        } else {
            rsNode_->SetPivot(
                vec.GetX().ConvertToPx() / paintRect.Width(), vec.GetY().ConvertToPx() / paintRect.Height());
        }
    }

    if (bgLoadingCtx_ && bgLoadingCtx_->GetCanvasImage()) {
        PaintBackground();
    }

    if (bdImageLoadingCtx_ && bdImageLoadingCtx_->GetCanvasImage()) {
        PaintBorderImage();
    }

    if (GetBorderImageGradient()) {
        PaintBorderImageGradient();
    }

    if (propGradient_) {
        SizeF frameSize(paintRect.Width(), paintRect.Height());
        PaintGradient(frameSize);
    }

    if (propClip_) {
        SizeF frameSize(paintRect.Width(), paintRect.Height());
        PaintClip(frameSize);
    }

    if (propGraphics_) {
        PaintGraphics();
    }

    if (propOverlay_) {
        PaintOverlayText();
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
        rosenRenderContext->bgLoadingCtx_->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
    return task;
}

LoadSuccessNotifyTask RosenRenderContext::CreateBgImageLoadSuccessCallback()
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
        if (rosenRenderContext->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            rosenRenderContext->PaintBackground();
        }
    };
    return task;
}

void RosenRenderContext::PaintBackground()
{
    if (GetBackground() == nullptr || GetBackground()->GetBackgroundImage() == std::nullopt) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(bgLoadingCtx_);
    auto skiaCanvasImage = DynamicCast<SkiaCanvasImage>(bgLoadingCtx_->GetCanvasImage());
    CHECK_NULL_VOID(skiaCanvasImage);
    auto skImage = skiaCanvasImage->GetCanvasImage();
    CHECK_NULL_VOID(skImage);
    auto rosenImage = std::make_shared<Rosen::RSImage>();
    rosenImage->SetImage(skImage);
    rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NOREPEAT)));
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

void RosenRenderContext::OnBackgroundBlurStyleUpdate(const BlurStyle& bgBlurStyle)
{
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto dipScale_ = context->GetDipScale();
    auto backFilter =
        Rosen::RSFilter::CreateMaterialFilter(static_cast<int>(bgBlurStyle), static_cast<float>(dipScale_));
    CHECK_NULL_VOID(backFilter);
    rsNode_->SetBackgroundFilter(backFilter);
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

void RosenRenderContext::OnTransformTranslateUpdate(const Vector3F& translate)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetTranslate(translate.x, translate.y, translate.z);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformRotateUpdate(const Vector4F& rotate)
{
    CHECK_NULL_VOID(rsNode_);
    float norm = std::sqrt(std::pow(rotate.x, 2) + std::pow(rotate.y, 2) + std::pow(rotate.z, 2));
    // pi = 4*atan(1)
    float angle = rotate.w / 2 * 4 * std::atan(1) / 180.0;
    float dx = rotate.x * std::sin(angle) / norm;
    float dy = rotate.y * std::sin(angle) / norm;
    float dz = rotate.z * std::sin(angle) / norm;
    float dw = std::cos(angle);
    rsNode_->SetRotation(Rosen::Quaternion(dx, dy, dz, dw));
    RequestNextFrame();
}

void RosenRenderContext::OnTransformCenterUpdate(const DimensionOffset& center) {}

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
        float zTranslateValue = static_cast<float>(matrix.Get(2, 3));
        Rosen::Vector2f scaleValue { 0.0f, 0.0f };
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeTranslateZModifier(
            rsNode_, transformMatrixModifier_->translateZ, transformMatrixModifier_->translateZValue, zTranslateValue);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, scaleValue);
    } else {
        Rosen::Vector2f xyTranslateValue { transform.translate[0], transform.translate[1] };
        float zTranslateValue = transform.translate[2];
        Rosen::Quaternion quaternion { static_cast<float>(transform.quaternion.GetX()),
            static_cast<float>(transform.quaternion.GetY()), static_cast<float>(transform.quaternion.GetZ()),
            static_cast<float>(transform.quaternion.GetW()) };
        Rosen::Vector2f scaleValue { transform.scale[0], transform.scale[1] };
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeTranslateZModifier(
            rsNode_, transformMatrixModifier_->translateZ, transformMatrixModifier_->translateZValue, zTranslateValue);
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
            if (rsNode) {
                rsNode->NotifyTransition(effect, isTransitionIn);
            }
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

void RosenRenderContext::PaintBorderImage()
{
    CHECK_NULL_VOID(rsNode_);
    auto paintBorderImageTask = [weak = WeakClaim(this)](std::shared_ptr<SkCanvas> canvas) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        CHECK_NULL_VOID(rosenRenderContext->GetBorderImage());
        CHECK_NULL_VOID(rosenRenderContext->bdImageLoadingCtx_);
        auto skiaCanvasImage = DynamicCast<SkiaCanvasImage>(rosenRenderContext->bdImageLoadingCtx_->GetCanvasImage());
        CHECK_NULL_VOID(skiaCanvasImage);
        auto skImage = skiaCanvasImage->GetCanvasImage();
        auto layoutProperty = rosenRenderContext->GetHost()->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto paintRect = rosenRenderContext->GetPaintRectWithoutTransform();
        if (NearZero(paintRect.Width()) || NearZero(paintRect.Height())) {
            return;
        }

        RSCanvas rsCanvas(&canvas);
        RSPen pen;
        pen.SetAntiAlias(true);
        rsCanvas.AttachPen(pen);
        rsCanvas.Save();

        BorderImagePainter borderImagePainter(rosenRenderContext->GetBdImage(),
            layoutProperty->GetBorderWidthProperty(), paintRect.GetSize(), rosenRenderContext->GetBorderImage().value(),
            skImage, NG::PipelineContext::GetCurrentContext()->GetDipScale());
        borderImagePainter.InitPainter();

        auto position = OffsetF(0.0, 0.0);
        if (layoutProperty->GetMarginProperty()) {
            auto margin = *layoutProperty->GetMarginProperty();
            auto scaleProperty = ScaleProperty::CreateScaleProperty();
            const auto& rect = rosenRenderContext->GetHost()->GetGeometryNode()->GetFrameRect();
            position += OffsetF(ConvertToPx(margin.left, scaleProperty, rect.Width()).value_or(0.0),
                ConvertToPx(margin.top, scaleProperty, rect.Height()).value_or(0.0));
        }
        borderImagePainter.PaintBorderImage(position, rsCanvas);
        rsCanvas.Restore();
    };

    rsNode_->DrawOnNode(Rosen::RSModifierType::FOREGROUND_STYLE, paintBorderImageTask);
}

DataReadyNotifyTask RosenRenderContext::CreateBorderImageDataReadyCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        auto imageSourceInfo = rosenRenderContext->GetBorderImageSource().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        rosenRenderContext->bdImageLoadingCtx_->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
    return task;
}

LoadSuccessNotifyTask RosenRenderContext::CreateBorderImageLoadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        auto imageSourceInfo = rosenRenderContext->GetBorderImageSource().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            LOGW("sourceInfo does not match, ignore current callback. current: %{public}s vs callback's: %{public}s",
                imageSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        if (rosenRenderContext->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            rosenRenderContext->PaintBorderImage();
        }
    };
    return task;
}

void RosenRenderContext::OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) {}

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
}

void RosenRenderContext::PaintBorderImageGradient()
{
    CHECK_NULL_VOID(rsNode_);
    auto PaintBorderImageGradientTask = [weak = WeakClaim(this)](std::shared_ptr<SkCanvas> canvas) {
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        CHECK_NULL_VOID(rosenRenderContext->GetBorderImageGradient());
        auto gradient = rosenRenderContext->GetBorderImageGradient().value();
        if (!gradient.IsValid()) {
            LOGE("Gradient not valid");
            return;
        }
        // TODO: PaintBorderImageGradient
    };

    rsNode_->DrawOnNode(Rosen::RSModifierType::FOREGROUND_STYLE, PaintBorderImageGradientTask);
}

void RosenRenderContext::OnModifyDone()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    const auto& size = frameNode->GetGeometryNode()->GetFrameSize();
    if (!size.IsPositive()) {
        LOGD("first modify, make change in SyncGeometryProperties");
        return;
    }
    if (!isPositionChanged_) {
        return;
    }
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
    // Position properties take precedence over offset locations.
    if (HasPosition()) {
        auto position = GetPositionValue({});
        auto posX = ConvertToPx(position.GetX(), ScaleProperty::CreateScaleProperty(), widthPercentReference);
        auto posY = ConvertToPx(position.GetY(), ScaleProperty::CreateScaleProperty(), heightPercentReference);
        rect.SetLeft(posX.value_or(0) - anchorX.value_or(0));
        rect.SetTop(posY.value_or(0) - anchorY.value_or(0));
        return rect;
    }
    if (HasOffset()) {
        auto offset = GetOffsetValue({});
        auto offsetX = ConvertToPx(offset.GetX(), ScaleProperty::CreateScaleProperty(), widthPercentReference);
        auto offsetY = ConvertToPx(offset.GetY(), ScaleProperty::CreateScaleProperty(), heightPercentReference);
        rect.SetLeft(rect.GetX() + offsetX.value_or(0));
        rect.SetTop(rect.GetY() + offsetY.value_or(0));
        return rect;
    }
    rect.SetLeft(rect.GetX() + anchorX.value_or(0));
    rect.SetTop(rect.GetY() + anchorY.value_or(0));
    return rect;
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

void RosenRenderContext::FlushModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<ContentModifierAdapter>(ConvertModifier(modifier));
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

bool RosenRenderContext::GetRSNodeTreeDiff(const std::list<std::shared_ptr<Rosen::RSNode>>& nowRSNodes,
    std::list<std::shared_ptr<Rosen::RSNode>>& toRemoveRSNodes,
    std::list<std::pair<std::shared_ptr<Rosen::RSNode>, int>>& toAddRSNodesAndIndex)
{
    CHECK_NULL_RETURN(rsNode_, false);
    auto preRSNodesID = rsNode_->GetChildren();
    std::unordered_set<std::shared_ptr<Rosen::RSNode>> nowRSNodesSet;
    std::unordered_set<std::shared_ptr<Rosen::RSNode>> preRSNodesSet;
    // get previous rsnode children set and now rsnode children set
    for (const auto& node : nowRSNodes) {
        nowRSNodesSet.insert(node);
    }
    for (const auto& id : preRSNodesID) {
        auto preNode = Rosen::RSNodeMap::Instance().GetNode<Rosen::RSNode>(id);
        preRSNodesSet.insert(preNode);
    }
    // get the difference
    for (const auto& node : preRSNodesSet) {
        if (nowRSNodesSet.find(node) == nowRSNodesSet.end()) {
            toRemoveRSNodes.emplace_back(node);
        }
    }
    int cntIndex = 0;
    for (const auto& node : nowRSNodes) {
        if (preRSNodesSet.find(node) == preRSNodesSet.end()) {
            toAddRSNodesAndIndex.emplace_back(node, cntIndex);
        }
        cntIndex++;
    }
    return !toRemoveRSNodes.empty() || !toAddRSNodesAndIndex.empty();
}

void RosenRenderContext::ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_VOID(rsNode_);
    auto nowRSNodes = GetChildrenRSNodes(children);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto option = pipeline->GetExplicitAnimationOption();
    // if no explicit animation, cannot animate
    if (!option.GetCurve()) {
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
        return;
    }
    // do transition animate
    std::list<std::shared_ptr<Rosen::RSNode>> toRemoveRSNodes;
    std::list<std::pair<std::shared_ptr<Rosen::RSNode>, int>> toAddRSNodesAndIndex;
    bool diffRes = GetRSNodeTreeDiff(nowRSNodes, toRemoveRSNodes, toAddRSNodesAndIndex);
    if (!diffRes) {
        return;
    }
    AnimationUtils::Animate(
        option, [rsParentNode = rsNode_, &removing = toRemoveRSNodes, &adding = toAddRSNodesAndIndex]() {
            for (auto& node : removing) {
                rsParentNode->RemoveChild(node);
            }
            for (auto& [node, index] : adding) {
                rsParentNode->AddChild(node, index);
            }
        });
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
    auto pipeline = PipelineContext::GetCurrentContext();
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
    auto pipeline = PipelineContext::GetCurrentContext();
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
            if (rsNode) {
                rsNode->SetBackgroundColor(highlightEnd.GetValue());
            }
        });
    hoveredColor_ = hoverColorTo;
    isHoveredBoard_ = isHovered;
}

void RosenRenderContext::UpdateBackBlurRadius(const Dimension& radius)
{
    auto& backDecoration = GetOrCreateBackDecoration();
    if (backDecoration->CheckBlurRadius(radius)) {
        return;
    }
    backDecoration->UpdateBlurRadius(radius);

    auto pipelineBase = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineBase);
    std::shared_ptr<Rosen::RSFilter> backFilter = nullptr;
    if (backDecoration->HasBlurStyle() && backDecoration->GetBlurStyleValue() != BlurStyle::NoMaterial) {
        backFilter = Rosen::RSFilter::CreateMaterialFilter(
            static_cast<int>(backDecoration->GetBlurStyleValue()), pipelineBase->GetDipScale());
    } else if (radius.IsValid()) {
        float radiusPx = pipelineBase->NormalizeToPx(radius);
        float backblurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
        backFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
    }
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBackgroundFilter(backFilter);
    RequestNextFrame();
}

void RosenRenderContext::UpdateFrontBlurRadius(const Dimension& radius)
{
    auto& frontDecoration = GetOrCreateFrontDecoration();
    if (frontDecoration->CheckBlurRadius(radius)) {
        return;
    }
    frontDecoration->UpdateBlurRadius(radius);

    auto pipelineBase = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineBase);
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

void RosenRenderContext::UpdateBackShadow(const Shadow& shadow)
{
    const auto& backDecoration = GetOrCreateBackDecoration();
    if (backDecoration->CheckBackShadow(shadow)) {
        return;
    }
    backDecoration->UpdateBackShadow(shadow);
    CHECK_NULL_VOID(rsNode_);
    if (!shadow.GetHardwareAcceleration()) {
        rsNode_->SetShadowRadius(SkiaDecorationPainter::ConvertRadiusToSigma(shadow.GetBlurRadius()));
    } else {
        rsNode_->SetShadowElevation(shadow.GetElevation());
    }
    rsNode_->SetShadowColor(shadow.GetColor().GetValue());
    rsNode_->SetShadowOffsetX(shadow.GetOffset().GetX());
    rsNode_->SetShadowOffsetY(shadow.GetOffset().GetY());
    rsNode_->SetShadowElevation(shadow.GetElevation());
    RequestNextFrame();
}

void RosenRenderContext::PaintGraphics()
{
    CHECK_NULL_VOID(rsNode_);
    auto& graphicsProperty = GetOrCreateGraphics();
    if (graphicsProperty->HasFrontColorBlend()) {
        auto colorBlend = graphicsProperty->GetFrontColorBlendValue();
        auto modifier = std::make_shared<ColorBlendModifier>();
        modifier->SetCustomData(NG::ColorBlend(colorBlend));
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontGrayScale()) {
        auto grayScale = graphicsProperty->GetFrontGrayScaleValue();
        auto modifier = std::make_shared<GrayScaleModifier>();
        modifier->SetCustomData(grayScale.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontBrightness()) {
        auto brightness = graphicsProperty->GetFrontBrightnessValue();
        auto modifier = std::make_shared<BrightnessModifier>();
        modifier->SetCustomData(brightness.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontContrast()) {
        auto contrast = graphicsProperty->GetFrontContrastValue();
        auto modifier = std::make_shared<ContrastModifier>();
        modifier->SetCustomData(contrast.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontSaturate()) {
        auto saturate = graphicsProperty->GetFrontSaturateValue();
        auto modifier = std::make_shared<SaturateModifier>();
        modifier->SetCustomData(saturate.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontSepia()) {
        auto sepia = graphicsProperty->GetFrontSepiaValue();
        auto modifier = std::make_shared<SepiaModifier>();
        modifier->SetCustomData(sepia.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontInvert()) {
        auto invert = graphicsProperty->GetFrontInvertValue();
        auto modifier = std::make_shared<InvertModifier>();
        modifier->SetCustomData(invert.Value());
        rsNode_->AddModifier(modifier);
    }

    if (graphicsProperty->HasFrontHueRotate()) {
        auto hueRotate = graphicsProperty->GetFrontHueRotateValue();
        auto modifier = std::make_shared<HueRotateModifier>();
        modifier->SetCustomData(hueRotate);
        rsNode_->AddModifier(modifier);
    }
}

void RosenRenderContext::OnPaintGraphics()
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!NearZero(rect.Width()) && !NearZero(rect.Height())) {
        PaintGraphics();
    }
    RequestNextFrame();
}

void RosenRenderContext::OnFrontBrightnessUpdate(const Dimension& /*brightness*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontGrayScaleUpdate(const Dimension& /*grayScale*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontContrastUpdate(const Dimension& /*contrast*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontSaturateUpdate(const Dimension& /*saturate*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontSepiaUpdate(const Dimension& /*sepia*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontInvertUpdate(const Dimension& /*invert*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontHueRotateUpdate(float /*hueRotate*/)
{
    OnPaintGraphics();
}

void RosenRenderContext::OnFrontColorBlendUpdate(const Color& /*colorBlend*/)
{
    OnPaintGraphics();
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
        transitionAppearingEffect_ = GetRSTransitionWithoutType(*propTransitionAppearing_);
    }
    if (options.Type == TransitionType::ALL || options.Type == TransitionType::DISAPPEARING) {
        if (!propTransitionDisappearing_) {
            propTransitionDisappearing_ = std::make_unique<TransitionOptions>(options);
        } else {
            *propTransitionDisappearing_ = options;
        }
        propTransitionDisappearing_->Type = TransitionType::DISAPPEARING;
        transitionDisappearingEffect_ = GetRSTransitionWithoutType(*propTransitionDisappearing_);
    }
    rsNode_->SetTransitionEffect(Rosen::RSTransitionEffect::Asymmetric(
        HasAppearingTransition() ? transitionAppearingEffect_ : Rosen::RSTransitionEffect::Create(),
        HasDisappearingTransition() ? transitionDisappearingEffect_ : Rosen::RSTransitionEffect::Create()));
}

std::shared_ptr<Rosen::RSTransitionEffect> RosenRenderContext::GetRSTransitionWithoutType(
    const TransitionOptions& options)
{
    std::shared_ptr<Rosen::RSTransitionEffect> effect = Rosen::RSTransitionEffect::Create();
    if (options.HasOpacity()) {
        effect = effect->Opacity(options.GetOpacityValue());
    }
    if (options.HasTranslate()) {
        const auto& translate = options.GetTranslateValue();
        effect = effect->Translate({ translate.x.ConvertToPx(), translate.y.ConvertToPx(), translate.z.ConvertToPx() });
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
    auto& gradientProperty = GetOrCreateGradient();
    if (!gradientProperty || !gradientProperty->UpdateLinearGradient(gradient)) {
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    SizeF frameSize = frameNode->GetGeometryNode()->GetFrameSize();
    if (!NearZero(frameSize.Width()) && !NearZero(frameSize.Height())) {
        PaintGradient(frameSize);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnRadialGradientUpdate(const NG::Gradient& gradient)
{
    auto& gradientProperty = GetOrCreateGradient();
    if (!gradientProperty || !gradientProperty->UpdateRadialGradient(gradient)) {
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    SizeF frameSize = frameNode->GetGeometryNode()->GetFrameSize();
    if (!NearZero(frameSize.Width()) && !NearZero(frameSize.Height())) {
        PaintGradient(frameSize);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnSweepGradientUpdate(const NG::Gradient& gradient)
{
    auto& gradientProperty = GetOrCreateGradient();
    if (!gradientProperty || !gradientProperty->UpdateSweepGradient(gradient)) {
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    SizeF frameSize = frameNode->GetGeometryNode()->GetFrameSize();
    if (!NearZero(frameSize.Width()) && !NearZero(frameSize.Height())) {
        PaintGradient(frameSize);
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
    if (!NearZero(rect.Width()) && !NearZero(rect.Height())) {
        PaintClip(SizeF(rect.Width(), rect.Height()));
    }
    RequestNextFrame();
}

void RosenRenderContext::OnClipEdgeUpdate(bool isClip)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetClipToBounds(isClip);
    RequestNextFrame();
}

void RosenRenderContext::OnClipMaskUpdate(const RefPtr<BasicShape>& /*basicShape*/)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!NearZero(rect.Width()) && !NearZero(rect.Height())) {
        PaintClip(SizeF(rect.Width(), rect.Height()));
    }
    RequestNextFrame();
}

bool RosenRenderContext::TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish) const
{
    CHECK_NULL_RETURN(rsNode_, false);
    const int32_t PAGE_TRANSITION_DURATION = 300;
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(PAGE_TRANSITION_DURATION);
    auto pipelineBase = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineBase, false);
    const double width = pipelineBase->GetRootWidth();
    std::shared_ptr<Rosen::RSTransitionEffect> effect = Rosen::RSTransitionEffect::Create();
    bool transitionIn = true;
    switch (type) {
        case PageTransitionType::ENTER_PUSH:
            effect->Translate({ width, 0, 0 });
            transitionIn = true;
            break;
        case PageTransitionType::ENTER_POP:
            effect->Translate({ -width, 0, 0 });
            transitionIn = true;
            break;
        case PageTransitionType::EXIT_PUSH:
            effect->Translate({ -width, 0, 0 });
            transitionIn = false;
            break;
        case PageTransitionType::EXIT_POP:
            effect->Translate({ width, 0, 0 });
            transitionIn = false;
            break;
        default:
            LOGI("unexpected transition type");
            return false;
    }
    AnimationUtils::Animate(
        option, [rsNode = rsNode_, effect, transitionIn]() { rsNode->NotifyTransition(effect, transitionIn); },
        onFinish);
    return true;
}

void RosenRenderContext::PaintOverlayText()
{
    CHECK_NULL_VOID(rsNode_);
    auto& overlay = GetOrCreateOverlay();
    if (overlay->HasOverlayText()) {
        auto overlayText = overlay->GetOverlayTextValue();
        auto modifier = std::make_shared<OverlayTextModifier>();
        modifier->SetCustomData(NG::OverlayTextData(overlayText));
        rsNode_->AddModifier(modifier);
        // TODO: PaintOverlayText
    }
}

void RosenRenderContext::OnOverlayTextUpdate(const OverlayOptions& overlay)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!NearZero(rect.Width()) && !NearZero(rect.Height())) {
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
    motionOption.SetPathNeedAddOrigin(true);
    rsNode_->SetMotionPathOption(std::make_shared<Rosen::RSMotionPathOption>(motionOption));
    RequestNextFrame();
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

    // after update, tell parent to update RSNode hierarchy.
    auto uiNode = GetHost();
    CHECK_NULL_VOID(uiNode);
    auto parentUINode = uiNode->GetParent();
    CHECK_NULL_VOID(parentUINode);
    parentUINode->MarkNeedSyncRenderTree();
    parentUINode->RebuildRenderContextTree();
}
} // namespace OHOS::Ace::NG
