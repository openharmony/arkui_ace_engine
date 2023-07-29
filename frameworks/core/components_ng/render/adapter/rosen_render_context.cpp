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

#include <algorithm>
#include <memory>

#include "common/rs_vector2.h"
#include "include/utils/SkParsePath.h"
#include "modifier/rs_property.h"
#include "render_service_base/include/property/rs_properties_def.h"
#include "render_service_client/core/modifier/rs_property_modifier.h"
#include "render_service_client/core/pipeline/rs_node_map.h"
#include "render_service_client/core/transaction/rs_interfaces.h"
#include "render_service_client/core/ui/rs_canvas_drawing_node.h"
#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_effect_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/common/rosen/rosen_convert_helper.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/background_modifier.h"
#include "core/components_ng/render/adapter/border_image_modifier.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/render/adapter/debug_boundary_modifier.h"
#include "core/components_ng/render/adapter/focus_state_modifier.h"
#include "core/components_ng/render/adapter/gradient_style_modifier.h"
#include "core/components_ng/render/adapter/graphic_modifier.h"
#include "core/components_ng/render/adapter/moon_progress_modifier.h"
#include "core/components_ng/render/adapter/mouse_select_modifier.h"
#include "core/components_ng/render/adapter/overlay_modifier.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"
#include "core/components_ng/render/adapter/rosen_transition_effect.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/skia_decoration_painter.h"
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/render/adapter/rosen/drawing_decoration_painter.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#endif
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/border_image_painter.h"
#include "core/components_ng/render/debug_boundary_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace OHOS::Rosen;
namespace {
RefPtr<PixelMap> g_pixelMap {};
std::mutex g_mutex;
std::condition_variable thumbnailGet;
constexpr float ANIMATION_CURVE_VELOCITY_LIGHT_OR_MIDDLE = 10.0f;
constexpr float ANIMATION_CURVE_VELOCITY_HEAVY = 0.0f;
constexpr float ANIMATION_CURVE_MASS = 1.0f;
constexpr float ANIMATION_CURVE_STIFFNESS_LIGHT = 410.0f;
constexpr float ANIMATION_CURVE_STIFFNESS_MIDDLE = 350.0f;
constexpr float ANIMATION_CURVE_STIFFNESS_HEAVY = 240.0f;
constexpr float ANIMATION_CURVE_DAMPING_LIGHT = 38.0f;
constexpr float ANIMATION_CURVE_DAMPING_MIDDLE = 35.0f;
constexpr float ANIMATION_CURVE_DAMPING_HEAVY = 28.0f;
constexpr float DEFAULT_SCALE_LIGHT = 0.9f;
constexpr float DEFAULT_SCALE_MIDDLE_OR_HEAVY = 0.95f;
constexpr int32_t DEFAULT_OPTION_DURATION = 100;
constexpr int32_t PLATFORM_VERSION_TEN = 10;
Rosen::Gravity GetRosenGravity(RenderFit renderFit)
{
    static const LinearEnumMapNode<RenderFit, Rosen::Gravity> gravityMap[] = {
        { RenderFit::CENTER, Rosen::Gravity::CENTER },
        { RenderFit::TOP, Rosen::Gravity::TOP },
        { RenderFit::BOTTOM, Rosen::Gravity::BOTTOM },
        { RenderFit::LEFT, Rosen::Gravity::LEFT },
        { RenderFit::RIGHT, Rosen::Gravity::RIGHT },
        { RenderFit::TOP_LEFT, Rosen::Gravity::TOP_LEFT },
        { RenderFit::TOP_RIGHT, Rosen::Gravity::TOP_RIGHT },
        { RenderFit::BOTTOM_LEFT, Rosen::Gravity::BOTTOM_LEFT },
        { RenderFit::BOTTOM_RIGHT, Rosen::Gravity::BOTTOM_RIGHT },
        { RenderFit::RESIZE_FILL, Rosen::Gravity::RESIZE },
        { RenderFit::RESIZE_CONTAIN, Rosen::Gravity::RESIZE_ASPECT },
        { RenderFit::RESIZE_CONTAIN_TOP_LEFT, Rosen::Gravity::RESIZE_ASPECT_TOP_LEFT },
        { RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT, Rosen::Gravity::RESIZE_ASPECT_BOTTOM_RIGHT },
        { RenderFit::RESIZE_COVER, Rosen::Gravity::RESIZE_ASPECT_FILL },
        { RenderFit::RESIZE_COVER_TOP_LEFT, Rosen::Gravity::RESIZE_ASPECT_FILL_TOP_LEFT },
        { RenderFit::RESIZE_COVER_BOTTOM_RIGHT, Rosen::Gravity::RESIZE_ASPECT_FILL_BOTTOM_RIGHT },
    };
    int64_t idx = BinarySearchFindIndex(gravityMap, ArraySize(gravityMap), renderFit);
    return idx != -1 ? gravityMap[idx].value : Rosen::Gravity::DEFAULT;
}
} // namespace

float RosenRenderContext::ConvertDimensionToScaleBySize(const Dimension& dimension, float size)
{
    if (dimension.Unit() == DimensionUnit::PERCENT) {
        return static_cast<float>(dimension.Value());
    }
    return size > 0.0f ? static_cast<float>(dimension.ConvertToPx() / size) : 0.5f;
}

RosenRenderContext::~RosenRenderContext()
{
    StopRecordingIfNeeded();
}

void RosenRenderContext::StartRecording()
{
    CHECK_NULL_VOID(rsNode_);
    auto rsCanvasNode = rsNode_->ReinterpretCastTo<Rosen::RSCanvasNode>();
    CHECK_NULL_VOID_NOLOG(rsCanvasNode);
    rsCanvasNode->BeginRecording(ceil(rsCanvasNode->GetPaintWidth()), ceil(rsCanvasNode->GetPaintHeight()));
}

void RosenRenderContext::StopRecordingIfNeeded()
{
    auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
    if (rsCanvasNode) {
        rsCanvasNode->FinishRecording();
    }
}

void RosenRenderContext::OnNodeAppear(bool recursive)
{
    isDisappearing_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // restore eventHub state when node appears.
    host->GetEventHub<EventHub>()->RestoreEnabled();
    if (recursive && !propTransitionAppearing_ && !transitionEffect_) {
        // recursive and has no transition, no need to handle transition.
        return;
    }

    isBreakingPoint_ = !recursive;
    if (isSynced_) {
        // has set size before, trigger transition directly.
        auto rect = GetPaintRectWithoutTransform();
        NotifyTransitionInner(rect.GetSize(), true);
        return;
    }
    // pending transition in animation, will start on first layout
    firstTransitionIn_ = true;
}

void RosenRenderContext::OnNodeDisappear(bool recursive)
{
    isDisappearing_ = true;
    bool noneOrDefaultTransition = !propTransitionDisappearing_ && (!transitionEffect_ || hasDefaultTransition_);
    if (recursive && noneOrDefaultTransition) {
        // recursive, and has no transition or has default transition, no need to trigger transition.
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    if (!recursive && host && host->GetEventHub<EventHub>()) {
        host->GetEventHub<EventHub>()->SetEnabledInternal(false);
    }
    auto rect = GetPaintRectWithoutTransform();
    // only start default transition on the break point of render node tree.
    isBreakingPoint_ = !recursive;
    NotifyTransitionInner(rect.GetSize(), false);
}

void RosenRenderContext::SetPivot(float xPivot, float yPivot, float zPivot)
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
    rsNode_->SetPivotZ(zPivot);
}

void RosenRenderContext::SetTransitionPivot(const SizeF& frameSize, bool transitionIn)
{
    auto& transitionEffect = transitionIn ? propTransitionAppearing_ : propTransitionDisappearing_;
    CHECK_NULL_VOID_NOLOG(transitionEffect);
    float xPivot = 0.0f;
    float yPivot = 0.0f;
    float zPivot = 0.0f;
    if (transitionEffect->HasRotate()) {
        xPivot = ConvertDimensionToScaleBySize(transitionEffect->GetRotateValue().centerX, frameSize.Width());
        yPivot = ConvertDimensionToScaleBySize(transitionEffect->GetRotateValue().centerY, frameSize.Height());
        zPivot = static_cast<float>(transitionEffect->GetRotateValue().centerZ.ConvertToVp());
    } else if (transitionEffect->HasScale()) {
        xPivot = ConvertDimensionToScaleBySize(transitionEffect->GetScaleValue().centerX, frameSize.Width());
        yPivot = ConvertDimensionToScaleBySize(transitionEffect->GetScaleValue().centerY, frameSize.Height());
    } else {
        return;
    }
    SetPivot(xPivot, yPivot, zPivot);
}

void RosenRenderContext::InitContext(bool isRoot, const std::optional<ContextParam>& param)
{
    // skip if node already created
    CHECK_NULL_VOID_NOLOG(!rsNode_);
    if (isRoot) {
        rsNode_ = Rosen::RSRootNode::Create();
        return;
    } else if (!param.has_value()) {
        rsNode_ = Rosen::RSCanvasNode::Create();
        return;
    }

    // create proper RSNode base on input
    switch (param->type) {
        case ContextType::CANVAS:
            rsNode_ = Rosen::RSCanvasNode::Create();
            break;
        case ContextType::ROOT:
            rsNode_ = Rosen::RSRootNode::Create();
            break;
        case ContextType::SURFACE: {
            Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = param->surfaceName.value_or("") };
            rsNode_ = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
            break;
        }
        case ContextType::HARDWARE_SURFACE: {
            Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = param->surfaceName.value_or("") };
            auto surfaceNode = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
            if (surfaceNode) {
                surfaceNode->SetHardwareEnabled(true);
            }
            rsNode_ = surfaceNode;
            break;
        }
        case ContextType::EFFECT:
            rsNode_ = Rosen::RSEffectNode::Create();
            break;
        case ContextType::INCREMENTAL_CANVAS:
            rsNode_ = Rosen::RSCanvasDrawingNode::Create();
            break;
        case ContextType::EXTERNAL:
            break;
        default:
            LOGE("invalid context type");
            break;
    }
}

void RosenRenderContext::SetSandBox(const std::optional<OffsetF>& parentPosition)
{
    CHECK_NULL_VOID(rsNode_);
    if (parentPosition.has_value()) {
        sandBoxCount_++;
        Rosen::Vector2f value = { parentPosition.value().GetX(), parentPosition.value().GetY() };
        rsNode_->SetSandBox(value);
    } else {
        sandBoxCount_--;
        if (sandBoxCount_ > 0) {
            return;
        }
        sandBoxCount_ = 0;
        rsNode_->SetSandBox(std::nullopt);
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
    if (isDisappearing_ && !paintRect.IsValid()) {
        return;
    }
    rsNode_->SetBounds(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    if (useContentRectForRSFrame_) {
        SetContentRectToFrame(paintRect);
    } else {
        rsNode_->SetFrame(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    }
    if (!isSynced_) {
        isSynced_ = true;
        auto borderRadius = GetBorderRadius();
        if (borderRadius.has_value()) {
            OnBorderRadiusUpdate(borderRadius.value());
        }
    }

    if (firstTransitionIn_) {
        // need to perform transitionIn early so not influence the following SetPivot
        NotifyTransitionInner(paintRect.GetSize(), true);
        firstTransitionIn_ = false;
    }

    if (propTransform_ && propTransform_->HasTransformCenter()) {
        auto vec = propTransform_->GetTransformCenterValue();
        float xPivot = ConvertDimensionToScaleBySize(vec.GetX(), paintRect.Width());
        float yPivot = ConvertDimensionToScaleBySize(vec.GetY(), paintRect.Height());
        if (vec.GetZ().has_value()) {
            float zPivot = static_cast<float>(vec.GetZ().value().ConvertToVp());
            SetPivot(xPivot, yPivot, zPivot);
        } else {
            SetPivot(xPivot, yPivot);
        }
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

void RosenRenderContext::OnForegroundColorUpdate(const Color& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetEnvForegroundColor(value.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::OnForegroundColorStrategyUpdate(const ForegroundColorStrategy& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::ForegroundColorStrategyType rsStrategy = Rosen::ForegroundColorStrategyType::INVALID;
    switch (value) {
        case ForegroundColorStrategy::INVERT:
            rsStrategy = Rosen::ForegroundColorStrategyType::INVERT_BACKGROUNDCOLOR;
            break;
        default:
            break;
    }
    rsNode_->SetEnvForegroundColorStrategy(rsStrategy);
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
    if (InstanceOf<PixelMapImage>(bgImage_)) {
        PaintPixmapBgImage();
#ifndef USE_ROSEN_DRAWING
    } else if (InstanceOf<SkiaImage>(bgImage_)) {
        PaintSkBgImage();
#else
    } else if (InstanceOf<DrawingImage>(bgImage_)) {
        PaintRSBgImage();
#endif
    } else {
        return;
    }

    SizeF renderSize = ImagePainter::CalculateBgImageSize(
        GetHost()->GetGeometryNode()->GetFrameSize(), bgLoadingCtx_->GetImageSize(), GetBackgroundImageSize());
    OffsetF positionOffset = ImagePainter::CalculateBgImagePosition(
        GetHost()->GetGeometryNode()->GetFrameSize(), renderSize, GetBackgroundImagePosition());
    rsNode_->SetBgImageWidth(renderSize.Width());
    rsNode_->SetBgImageHeight(renderSize.Height());
    rsNode_->SetBgImagePositionX(positionOffset.GetX());
    rsNode_->SetBgImagePositionY(positionOffset.GetY());
}

void RosenRenderContext::OnBackgroundImageUpdate(const ImageSourceInfo& src)
{
    CHECK_NULL_VOID(rsNode_);
    if (src.GetSrc().empty()) {
        return;
    }
    if (!bgLoadingCtx_ || src != bgLoadingCtx_->GetSourceInfo()) {
        LoadNotifier bgLoadNotifier(CreateBgImageDataReadyCallback(), CreateBgImageLoadSuccessCallback(), nullptr);
        bgLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(src, std::move(bgLoadNotifier));
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
    if (!blurStyle.has_value()) {
        const auto& radius = background->propBlurRadius;
        if (radius.has_value() && radius->IsValid()) {
            float radiusPx = context->NormalizeToPx(radius.value());
#ifndef USE_ROSEN_DRAWING
            float backblurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
#else
            float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
#endif
            backFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
        }
    } else if (GetRosenBlurStyleValue(blurStyle.value()) == MATERIAL_BLUR_STYLE::NO_MATERIAL) {
        backFilter = nullptr;
    } else {
        backFilter = Rosen::RSFilter::CreateMaterialFilter(static_cast<int>(GetRosenBlurStyleValue(blurStyle.value())),
            static_cast<float>(dipScale_), static_cast<Rosen::BLUR_COLOR_MODE>(blurStyle->adaptiveColor),
            static_cast<float>(blurStyle->scale));
    }
    rsNode_->SetBackgroundFilter(backFilter);
}

void RosenRenderContext::SetFrontBlurFilter()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    const auto& foreground = GetForeground();
    CHECK_NULL_VOID(foreground);
    const auto& blurStyle = foreground->propBlurStyleOption;
    std::shared_ptr<Rosen::RSFilter> frontFilter;
    auto dipScale_ = context->GetDipScale();
    if (!blurStyle.has_value()) {
        const auto& radius = foreground->propBlurRadius;
        if (radius.has_value() && radius->IsValid()) {
            float radiusPx = context->NormalizeToPx(radius.value());
#ifndef USE_ROSEN_DRAWING
            float backblurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
#else
            float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
#endif
            frontFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
        }
    } else if (GetRosenBlurStyleValue(blurStyle.value()) == MATERIAL_BLUR_STYLE::NO_MATERIAL) {
        frontFilter = nullptr;
    } else {
        frontFilter = Rosen::RSFilter::CreateMaterialFilter(static_cast<int>(GetRosenBlurStyleValue(blurStyle.value())),
            static_cast<float>(dipScale_), static_cast<Rosen::BLUR_COLOR_MODE>(blurStyle->adaptiveColor),
            static_cast<float>(blurStyle->scale));
    }

    rsNode_->SetFilter(frontFilter);
}

void RosenRenderContext::UpdateBackBlurStyle(const std::optional<BlurStyleOption>& bgBlurStyle)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurStyleOption(bgBlurStyle)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (bgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
    } else {
        groupProperty->propBlurStyleOption = bgBlurStyle;
    }
    SetBackBlurFilter();
}

void RosenRenderContext::UpdateBackgroundEffect(const std::optional<EffectOption>& effectOption)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckEffectOption(effectOption)) {
        return;
    }
    groupProperty->propEffectOption = effectOption;
    if (!effectOption.has_value()) {
        return;
    }
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float radiusPx = context->NormalizeToPx(effectOption->radius);
#ifndef USE_ROSEN_DRAWING
    float backblurRadius = SkiaDecorationPainter::ConvertRadiusToSigma(radiusPx);
#else
    float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
#endif
    std::shared_ptr<Rosen::RSFilter> backFilter = Rosen::RSFilter::CreateMaterialFilter(
        backblurRadius, static_cast<float>(effectOption->saturation),
        static_cast<float>(effectOption->brightness), effectOption->color.GetValue());
    rsNode_->SetBackgroundFilter(backFilter);
}

void RosenRenderContext::UpdateFrontBlurStyle(const std::optional<BlurStyleOption>& fgBlurStyle)
{
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurStyleOption(fgBlurStyle)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (fgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
    } else {
        groupProperty->propBlurStyleOption = fgBlurStyle;
    }
    SetFrontBlurFilter();
}

void RosenRenderContext::ResetBackBlurStyle()
{
    const auto& groupProperty = GetOrCreateBackground();
    groupProperty->propBlurStyleOption.reset();
    SetBackBlurFilter();
}

void RosenRenderContext::OnSphericalEffectUpdate(double radio)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetSpherizeDegree(static_cast<float>(radio));
    RequestNextFrame();
}

void RosenRenderContext::OnPixelStretchEffectUpdate(const PixStretchEffectOption& option)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f pixStretchVector;
    if (option.IsPercentOption()) {
        pixStretchVector.SetValues(static_cast<float>(option.left.Value()), static_cast<float>(option.top.Value()),
            static_cast<float>(option.right.Value()), static_cast<float>(option.bottom.Value()));
        rsNode_->SetPixelStretchPercent(pixStretchVector);
    } else {
        pixStretchVector.SetValues(static_cast<float>(option.left.ConvertToPx()),
            static_cast<float>(option.top.ConvertToPx()), static_cast<float>(option.right.ConvertToPx()),
            static_cast<float>(option.bottom.ConvertToPx()));
        rsNode_->SetPixelStretch(pixStretchVector);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnLightUpEffectUpdate(double radio)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetLightUpEffectDegree(static_cast<float>(radio));
    RequestNextFrame();
}

void RosenRenderContext::OnOpacityUpdate(double opacity)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetAlpha(opacity);
    RequestNextFrame();
}

class DrawDragThumbnailCallback : public SurfaceCaptureCallback {
public:
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        if (pixelMap == nullptr) {
            LOGE("%{public}s: failed to get pixelmap, return nullptr", __func__);
            thumbnailGet.notify_all();
            return;
        }
        std::unique_lock<std::mutex> lock(g_mutex);
#ifdef PIXEL_MAP_SUPPORTED
        g_pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
#endif // PIXEL_MAP_SUPPORTED
        thumbnailGet.notify_all();
        LOGI("Get pixelmap success");
    }
};

RefPtr<PixelMap> RosenRenderContext::GetThumbnailPixelMap()
{
    if (rsNode_ == nullptr) {
        LOGE("rsNode is nullptr");
        return nullptr;
    }
    std::shared_ptr<DrawDragThumbnailCallback> drawDragThumbnailCallback =
        std::make_shared<DrawDragThumbnailCallback>();
    auto ret = RSInterfaces::GetInstance().TakeSurfaceCaptureForUI(rsNode_, drawDragThumbnailCallback, 1, 1);
    if (!ret) {
        LOGE("GetThumbnailPixelMap false, return nullptr");
        return nullptr;
    }
    std::unique_lock<std::mutex> lock(g_mutex);
    thumbnailGet.wait(lock);
    return g_pixelMap;
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderContext::GetBitmap(SkBitmap& bitmap, std::shared_ptr<OHOS::Rosen::DrawCmdList> drawCmdList)
#else
bool RosenRenderContext::GetBitmap(RSBitmap& bitmap, std::shared_ptr<RSDrawCmdList> drawCmdList)
#endif
{
    auto rsCanvasDrawingNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasDrawingNode>(rsNode_);
    if (!rsCanvasDrawingNode) {
        return false;
    }
    return rsCanvasDrawingNode->GetBitmap(bitmap, drawCmdList);
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
        if (rect.IsEmpty()) {
            // size is not determined yet
            return;
        }
        xValue = translate.x.ConvertToPxWithSize(rect.Width());
        yValue = translate.y.ConvertToPxWithSize(rect.Height());
    } else {
        xValue = translate.x.ConvertToPx();
        yValue = translate.y.ConvertToPx();
    }
    // translateZ doesn't support percentage
    float zValue = translate.z.ConvertToPx();
    rsNode_->SetTranslate(xValue, yValue, zValue);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformRotateUpdate(const Vector5F& rotate)
{
    CHECK_NULL_VOID(rsNode_);
    float norm = std::sqrt(std::pow(rotate.x, 2) + std::pow(rotate.y, 2) + std::pow(rotate.z, 2));
    if (NearZero(norm)) {
        LOGW("rotate vector is near zero, please check");
        norm = 1.0f;
    }
    // for rosen backend, the rotation angles in the x and y directions should be set to opposite angles
    rsNode_->SetRotation(-rotate.w * rotate.x / norm, -rotate.w * rotate.y / norm, rotate.w * rotate.z / norm);
    // set camera distance
    rsNode_->SetCameraDistance(rotate.v);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformCenterUpdate(const DimensionOffset& center)
{
    RectF rect = GetPaintRectWithoutTransform();
    if (!RectIsNull()) {
        float xPivot = ConvertDimensionToScaleBySize(center.GetX(), rect.Width());
        float yPivot = ConvertDimensionToScaleBySize(center.GetY(), rect.Height());
        float zPivot = 0.0f;
        auto& z = center.GetZ();
        if (z.has_value()) {
            zPivot = static_cast<float>(z.value().ConvertToVp());
        }
        SetPivot(xPivot, yPivot, zPivot);
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

const int degree90 = 90;
const int degree180 = 180;
const int degree135 = 135;
const int degree45 = 45;

RectF RosenRenderContext::GetPaintRectWithTransform()
{
    RectF rect;

    const float pi = 3.14159265;
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
    // calculate rotate
    int degree = rsNode_->GetStagingProperties().GetRotation();

    if ((abs(degree) % degree180 > degree45) && (abs(degree) % degree180 < degree135)) {
        degree = degree90;
        OffsetF leftCornerRotate(0, 0);
        OffsetF leftCorner(-1 * oldSize.Width() * scale[0] / 2, -1 * oldSize.Height() * scale[1] / 2);
        leftCornerRotate.SetX(leftCorner.GetX() * cos(degree * pi / degree180) * -1 -
                              leftCorner.GetY() * sin(degree * pi / degree180) * -1);
        leftCornerRotate.SetY(leftCorner.GetX() * sin(degree * pi / degree180) * -1 +
                              leftCorner.GetY() * cos(degree * pi / degree180) * -1);
        OffsetF screenRotate(rect.GetX() + leftCornerRotate.GetX() - leftCorner.GetX(),
            rect.GetY() + oldSize.Height() * scale[1] - leftCornerRotate.GetY() + leftCorner.GetY());
        rect.SetOffset(screenRotate);
        if (abs(degree) % degree180 != 0) {
            newSize = SizeF(oldSize.Height() * scale[1], oldSize.Width() * scale[0]);
            rect.SetSize(newSize);
        }
    }
    return rect;
}

RectF RosenRenderContext::GetPaintRectWithTranslate()
{
    RectF rect;
    CHECK_NULL_RETURN(rsNode_, rect);
    rect = GetPaintRectWithoutTransform();
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    rect.SetOffset(rect.GetOffset() + OffsetF(translate[0], translate[1]));
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

void RosenRenderContext::UpdateTranslateInXY(const OffsetF& offset)
{
    CHECK_NULL_VOID(rsNode_);
    auto xValue = offset.GetX();
    auto yValue = offset.GetY();
    if (translateXY_) {
        auto propertyXY = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
        if (propertyXY) {
            propertyXY->Set({ xValue, yValue });
        } else {
            LOGE("fail to get translateXY property");
        }
    } else {
        auto propertyXY = std::make_shared<RSAnimatableProperty<Vector2f>>(Vector2f(xValue, yValue));
        translateXY_ = std::make_shared<Rosen::RSTranslateModifier>(propertyXY);
        rsNode_->AddModifier(translateXY_);
    }
}

OffsetF RosenRenderContext::GetShowingTranslateProperty()
{
    OffsetF offset;
    CHECK_NULL_RETURN(translateXY_, offset);
    auto property = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
    CHECK_NULL_RETURN(property, offset);
    auto result = property->GetShowingValueAndCancelAnimation();
    if (!result) {
        LOGW("fail to stop current property animation");
        return offset;
    }
    auto translate = property->Get();
    offset.SetX(translate[0]);
    offset.SetY(translate[1]);
    return offset;
}

void RosenRenderContext::NotifyTransitionInner(const SizeF& frameSize, bool isTransitionIn)
{
    CHECK_NULL_VOID(rsNode_);
    if (propTransitionAppearing_ || propTransitionDisappearing_) {
        // old transition
        auto& transOptions = isTransitionIn ? propTransitionAppearing_ : propTransitionDisappearing_;
        auto effect = GetRSTransitionWithoutType(transOptions, frameSize);
        CHECK_NULL_VOID_NOLOG(effect);
        SetTransitionPivot(frameSize, isTransitionIn);
        // notice that we have been in animateTo, so do not need to use Animation closure to notify transition.
        rsNode_->NotifyTransition(effect, isTransitionIn);
        return;
    }
    // add default transition effect on the 'breaking point' of render tree, if no user-defined transition effect
    // and triggered in AnimateTo closure.
    // Note: this default transition effect will be removed after all transitions finished, implemented in
    // OnTransitionInFinish. and OnTransitionOutFinish.
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (isBreakingPoint_ && !transitionEffect_ &&
        (pipeline->GetSyncAnimationOption().IsValid() ||
            ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().IsValid())) {
        hasDefaultTransition_ = true;
        transitionEffect_ = RosenTransitionEffect::CreateDefaultRosenTransitionEffect();
        RSNode::ExecuteWithoutAnimation([this, isTransitionIn]() {
            // transitionIn effects should be initialized as active if is transitionIn.
            transitionEffect_->Attach(Claim(this), isTransitionIn);
        });
    }
    NotifyTransition(isTransitionIn);
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
    if (!isSynced_) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto paintRect = AdjustPaintRect();
    if (isDisappearing_ && !paintRect.IsValid()) {
        return;
    }
    double radiusX = paintRect.Width();
    Rosen::Vector4f cornerRadius;
    // When the unit of radius is percent, the length and width of rect should be calculated at the same time,
    // but currently SetCornerRadius only supports Vector4f parameter passing.
    // Graphic should provide support .
    cornerRadius.SetValues(static_cast<float>(value.radiusTopLeft.value_or(Dimension()).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusTopRight.value_or(Dimension()).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension()).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension()).ConvertToPxWithSize(radiusX)));
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
    UpdateAccessibilityFocus(isAccessibilityFocus);
    if (isAccessibilityFocus) {
        PaintAccessibilityFocus();
    } else {
        ClearAccessibilityFocus();
    }
    uiNode->OnAccessibilityEvent(isAccessibilityFocus ? AccessibilityEventType::ACCESSIBILITY_FOCUSED
                                                      : AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED);
}

void RosenRenderContext::OnUseEffectUpdate(bool useEffect)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetUseEffect(useEffect);
}

void RosenRenderContext::OnFreezeUpdate(bool isFreezed)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFreeze(isFreezed);
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
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkImage> image;
    if (InstanceOf<SkiaImage>(bdImage_)) {
        image = DynamicCast<SkiaImage>(bdImage_)->GetImage();
    } else if (InstanceOf<PixelMapImage>(bdImage_)) {
        auto pixmap = DynamicCast<PixelMapImage>(bdImage_)->GetPixelMap();
        CHECK_NULL_VOID(pixmap);
        image = SkiaImage::MakeSkImageFromPixmap(pixmap);
    } else {
        return;
    }
#else
    std::shared_ptr<RSImage> image;
    if (InstanceOf<DrawingImage>(bdImage_)) {
        image = DynamicCast<DrawingImage>(bdImage_)->GetImage();
    } else if (InstanceOf<PixelMapImage>(bdImage_)) {
        auto pixmap = DynamicCast<PixelMapImage>(bdImage_)->GetPixelMap();
        CHECK_NULL_VOID(pixmap);
        image = DrawingImage::MakeRSImageFromPixmap(pixmap);
    } else {
        return;
    }
#endif
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

void RosenRenderContext::OnBackgroundAlignUpdate(const Alignment& align)
{
    CHECK_NULL_VOID(rsNode_);
    if (!backgroundModifier_) {
        backgroundModifier_ = std::make_shared<BackgroundModifier>();
        rsNode_->AddModifier(backgroundModifier_);
    }
    backgroundModifier_->SetAlign(align);
    backgroundModifier_->Modify();
    RequestNextFrame();
}

void RosenRenderContext::OnBackgroundPixelMapUpdate(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(rsNode_);
    if (!backgroundModifier_) {
        backgroundModifier_ = std::make_shared<BackgroundModifier>();
        rsNode_->AddModifier(backgroundModifier_);
    }
    auto node = GetHost();
    auto nodeWidth = node->GetGeometryNode()->GetFrameSize().Width();
    auto nodeHeight = node->GetGeometryNode()->GetFrameSize().Height();
    backgroundModifier_->SetInitialNodeSize(nodeWidth, nodeHeight);
    backgroundModifier_->SetPixelMap(pixelMap);
    backgroundModifier_->Modify();
    RequestNextFrame();
}

void RosenRenderContext::CreateBackgroundPixelMap(const RefPtr<FrameNode>& customNode)
{
    NG::ComponentSnapshot::JsCallback callback = [weak = WeakClaim(RawPtr(GetHost())),
                                                     containerId = Container::CurrentId()](
                                                     std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode) {
        CHECK_NULL_VOID(pixmap);
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ContainerScope scope(containerId);
        std::shared_ptr<Media::PixelMap> pmap = std::move(pixmap);
        auto pixelmap = PixelMap::CreatePixelMap(&pmap);
        auto task = [pixelmap, containerId = containerId, frameNode]() {
            auto context = frameNode->GetRenderContext();
            if (context) {
                context->UpdateBackgroundPixelMap(pixelmap);
                context->RequestNextFrame();
            }
        };
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    };
    NG::ComponentSnapshot::Create(customNode, std::move(callback));
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
    RequestNextFrame();
}

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
#ifndef USE_ROSEN_DRAWING
        auto rsImage = SkiaDecorationPainter::CreateBorderImageGradient(gradient, paintSize);
#else
        auto rsImage = DrawingDecorationPainter::CreateBorderImageGradient(gradient, paintSize);
#endif
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
    if (HasClickEffectLevel()) {
        InitEventClickEffect();
    }
}

RectF RosenRenderContext::GetPropertyOfPosition()
{
    return AdjustPaintRect();
}

RectF RosenRenderContext::AdjustPaintRect()
{
    RectF rect;
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, rect);
    CHECK_NULL_RETURN(rsNode_, rect);
    const auto& geometryNode = frameNode->GetGeometryNode();
    rect = geometryNode->GetFrameRect();
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
    Dimension resultX;
    Dimension resultY;
    Dimension parentPaddingLeft;
    Dimension parentPaddingTop;
    GetPaddingOfFirstFrameNodeParent(parentPaddingLeft, parentPaddingTop);
    // Position properties take precedence over offset locations.
    if (HasPosition() && IsUsingPosition(frameNode)) {
        CombineMarginAndPosition(
            resultX, resultY, parentPaddingLeft, parentPaddingTop, widthPercentReference, heightPercentReference);
        rect.SetLeft(resultX.ConvertToPx() - anchorX.value_or(0));
        rect.SetTop(resultY.ConvertToPx() - anchorY.value_or(0));
        return rect;
    }
    if (HasOffset()) {
        auto offset = GetOffsetValue({});
        if (PipelineBase::GetCurrentContext() &&
            PipelineBase::GetCurrentContext()->GetMinPlatformVersion() < PLATFORM_VERSION_TEN) {
            offset += OffsetT<Dimension>(parentPaddingLeft, parentPaddingTop);
        }
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

void RosenRenderContext::CombineMarginAndPosition(Dimension& resultX, Dimension& resultY,
    const Dimension& parentPaddingLeft, const Dimension& parentPaddingTop, float widthPercentReference,
    float heightPercentReference)
{
    Dimension selfMarginLeft;
    Dimension selfMarginTop;
    auto frameNode = GetHost();
    if (frameNode && frameNode->GetLayoutProperty() && frameNode->GetLayoutProperty()->GetMarginProperty()) {
        auto& margin = frameNode->GetLayoutProperty()->GetMarginProperty();
        if (margin->left.has_value()) {
            selfMarginLeft = margin->left.value().GetDimension();
        }
        if (margin->top.has_value()) {
            selfMarginTop = margin->top.value().GetDimension();
        }
    }
    // to distinguish cases ex. margin has percentage unit and padding has vp unit
    // final rect offset will be affected by parent padding, self margin and position property
    if (selfMarginLeft.Unit() != GetPositionValue({}).GetX().Unit() ||
        selfMarginLeft.Unit() != parentPaddingLeft.Unit() ||
        parentPaddingLeft.Unit() != GetPositionValue({}).GetX().Unit()) {
        resultX = Dimension(
            ConvertToPx(parentPaddingLeft, ScaleProperty::CreateScaleProperty(), widthPercentReference).value_or(0) +
                ConvertToPx(selfMarginLeft, ScaleProperty::CreateScaleProperty(), widthPercentReference).value_or(0) +
                ConvertToPx(GetPositionValue({}).GetX(), ScaleProperty::CreateScaleProperty(), widthPercentReference)
                    .value_or(0),
            DimensionUnit::PX);
    } else {
        resultX = selfMarginLeft + GetPositionValue({}).GetX() + parentPaddingLeft;
    }
    if (selfMarginTop.Unit() != GetPositionValue({}).GetY().Unit() || selfMarginTop.Unit() != parentPaddingTop.Unit() ||
        parentPaddingTop.Unit() != GetPositionValue({}).GetY().Unit()) {
        resultY = Dimension(
            ConvertToPx(parentPaddingTop, ScaleProperty::CreateScaleProperty(), heightPercentReference).value_or(0) +
                ConvertToPx(selfMarginTop, ScaleProperty::CreateScaleProperty(), heightPercentReference).value_or(0) +
                ConvertToPx(GetPositionValue({}).GetY(), ScaleProperty::CreateScaleProperty(), heightPercentReference)
                    .value_or(0),
            DimensionUnit::PX);
    } else {
        resultY = selfMarginTop + GetPositionValue({}).GetY() + parentPaddingTop;
    }
}

bool RosenRenderContext::IsUsingPosition(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    bool isUsingPosition = true;
    if (layoutProperty) {
        isUsingPosition = layoutProperty->IsUsingPosition();
    }
    return isUsingPosition;
}

void RosenRenderContext::GetPaddingOfFirstFrameNodeParent(Dimension& parentPaddingLeft, Dimension& parentPaddingTop)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto frameNodeParent = frameNode->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID_NOLOG(frameNodeParent);
    auto layoutProperty = frameNodeParent->GetLayoutProperty();
    if (layoutProperty && layoutProperty->GetPaddingProperty()) {
        parentPaddingLeft =
            layoutProperty->GetPaddingProperty()->left.value_or(CalcLength(Dimension(0))).GetDimension();
        parentPaddingTop = layoutProperty->GetPaddingProperty()->top.value_or(CalcLength(Dimension(0))).GetDimension();
    }
}
void RosenRenderContext::SetPositionToRSNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    const auto& size = frameNode->GetGeometryNode()->GetFrameSize();
    if (!size.IsPositive()) {
        LOGD("first modify, make change in SyncGeometryProperties");
        return;
    }
    auto rect = AdjustPaintRect();
    if (!rect.GetSize().IsPositive()) {
        return;
    }
    rsNode_->SetBounds(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    if (useContentRectForRSFrame_) {
        SetContentRectToFrame(rect);
    } else {
        rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    }
}

void RosenRenderContext::OnPositionUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnOffsetUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnAnchorUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
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
    CHECK_NULL_VOID_NOLOG(paintRect.GetRect().IsValid());
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
    std::shared_ptr<Rosen::RectF> overlayRect = std::make_shared<Rosen::RectF>(
        paintRect.GetRect().Left() - borderWidthPx / 2, paintRect.GetRect().Top() - borderWidthPx / 2,
        paintRect.GetRect().Width() + borderWidthPx, paintRect.GetRect().Height() + borderWidthPx);
    if (isAccessibilityFocus) {
        if (!accessibilityFocusStateModifier_) {
            accessibilityFocusStateModifier_ = std::make_shared<FocusStateModifier>();
        }
        accessibilityFocusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
        accessibilityFocusStateModifier_->SetPaintTask(std::move(paintTask));
        rsNode_->SetDrawRegion(overlayRect);
        rsNode_->AddModifier(accessibilityFocusStateModifier_);
    } else {
        if (!focusStateModifier_) {
            // TODO: Add property data
            focusStateModifier_ = std::make_shared<FocusStateModifier>();
        }
        focusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
        focusStateModifier_->SetPaintTask(std::move(paintTask));
        rsNode_->SetDrawRegion(overlayRect);
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

    EdgeF diffRadius = { borderPaddingPx + paintWidthPx / 2, borderPaddingPx + paintWidthPx / 2 };
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
    LOGD("ClearFocusState in.");
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID_NOLOG(focusStateModifier_);
    rsNode_->RemoveModifier(focusStateModifier_);
    RequestNextFrame();
}

void RosenRenderContext::FlushContentDrawFunction(CanvasDrawFunction&& contentDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(contentDraw);
    rsNode_->DrawOnNode(
#ifndef USE_ROSEN_DRAWING
        Rosen::RSModifierType::CONTENT_STYLE, [contentDraw = std::move(contentDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            contentDraw(rsCanvas);
#else
        Rosen::RSModifierType::CONTENT_STYLE,
        [contentDraw = std::move(contentDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            contentDraw(*canvas);
#endif
        });
}

void RosenRenderContext::FlushContentModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<ContentModifierAdapter>(ConvertContentModifier(modifier));
    auto contentModifier = AceType::DynamicCast<ContentModifier>(modifier);
    CHECK_NULL_VOID(contentModifier);
    auto rect = contentModifier->GetBoundsRect();
    if (rect.has_value()) {
        std::shared_ptr<Rosen::RectF> overlayRect =
            std::make_shared<Rosen::RectF>(rect->GetX(), rect->GetY(), rect->Width(), rect->Height());
        rsNode_->SetDrawRegion(overlayRect);
    }
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
}

void RosenRenderContext::FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(foregroundDraw);
    rsNode_->DrawOnNode(Rosen::RSModifierType::FOREGROUND_STYLE,
#ifndef USE_ROSEN_DRAWING
        [foregroundDraw = std::move(foregroundDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            foregroundDraw(rsCanvas);
#else
        [foregroundDraw = std::move(foregroundDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            foregroundDraw(*canvas);
#endif
        });
}

void RosenRenderContext::FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(overlayDraw);
    rsNode_->DrawOnNode(
#ifndef USE_ROSEN_DRAWING
        Rosen::RSModifierType::OVERLAY_STYLE, [overlayDraw = std::move(overlayDraw)](std::shared_ptr<SkCanvas> canvas) {
            RSCanvas rsCanvas(&canvas);
            overlayDraw(rsCanvas);
#else
        Rosen::RSModifierType::OVERLAY_STYLE,
        [overlayDraw = std::move(overlayDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            overlayDraw(*canvas);
#endif
        });
}

void RosenRenderContext::FlushOverlayModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(modifier));
    auto overlayModifier = AceType::DynamicCast<OverlayModifier>(modifier);
    CHECK_NULL_VOID(overlayModifier);
    auto rect = overlayModifier->GetBoundsRect();
    std::shared_ptr<Rosen::RectF> overlayRect =
        std::make_shared<Rosen::RectF>(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    rsNode_->SetDrawRegion(overlayRect);
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
}

const std::shared_ptr<Rosen::RSNode>& RosenRenderContext::GetRSNode()
{
    return rsNode_;
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
    SetBackBlurFilter();
}

void RosenRenderContext::UpdateFrontBlurRadius(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurRadius(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    SetFrontBlurFilter();
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
    rsNode_->SetShadowMask(shadow.GetShadowType() == ShadowType::BLUR);
    if (shadow.GetHardwareAcceleration()) {
        rsNode_->SetShadowElevation(shadow.GetElevation());
    } else {
#ifndef USE_ROSEN_DRAWING
        rsNode_->SetShadowRadius(SkiaDecorationPainter::ConvertRadiusToSigma(shadow.GetBlurRadius()));
#else
        rsNode_->SetShadowRadius(DrawingDecorationPainter::ConvertRadiusToSigma(shadow.GetBlurRadius()));
#endif
    }
    RequestNextFrame();
}

// called when frameNode size changes
void RosenRenderContext::PaintGraphics()
{
    CHECK_NULL_VOID(rsNode_);
    auto&& graphicProps = GetOrCreateGraphics();

    if (!graphics_) {
        graphics_ = std::make_unique<GraphicModifiers>();
    }
    if (graphicProps->HasFrontGrayScale()) {
        auto grayScale = graphicProps->GetFrontGrayScaleValue();
        OnFrontGrayScaleUpdate(grayScale);
    }

    if (graphicProps->HasFrontBrightness()) {
        auto brightness = graphicProps->GetFrontBrightnessValue();
        OnFrontBrightnessUpdate(brightness);
    }

    if (graphicProps->HasFrontContrast()) {
        auto contrast = graphicProps->GetFrontContrastValue();
        OnFrontContrastUpdate(contrast);
    }

    if (graphicProps->HasFrontSaturate()) {
        auto saturate = graphicProps->GetFrontSaturateValue();
        OnFrontSaturateUpdate(saturate);
    }

    if (graphicProps->HasFrontSepia()) {
        auto sepia = graphicProps->GetFrontSepiaValue();
        OnFrontSepiaUpdate(sepia);
    }

    if (graphicProps->HasFrontInvert()) {
        auto invert = graphicProps->GetFrontInvertValue();
        OnFrontInvertUpdate(invert);
    }

    if (graphicProps->HasFrontHueRotate()) {
        auto hueRotate = graphicProps->GetFrontHueRotateValue();
        OnFrontHueRotateUpdate(hueRotate);
    }

    if (graphicProps->HasFrontColorBlend()) {
        auto colorBlend = graphicProps->GetFrontColorBlendValue();
        OnFrontColorBlendUpdate(colorBlend);
    }
}

// helper function to check if frame react is valid
bool RosenRenderContext::RectIsNull()
{
    RectF rect = GetPaintRectWithoutTransform();
    return NearZero(rect.Width()) || NearZero(rect.Height());
}

template<typename T, typename D>
void RosenRenderContext::SetGraphicModifier(std::shared_ptr<T>& modifier, D data)
{
    if (!modifier) {
        LOGD("create new modifier");
        modifier = std::make_shared<T>();
        rsNode_->AddModifier(modifier);
    }
    modifier->SetCustomData(data);

    auto borderRadius = GetBorderRadius();
    if (borderRadius.has_value()) {
        Rosen::Vector4f rsRadius;
        ConvertRadius(*borderRadius, rsRadius);
        modifier->SetCornerRadius(rsRadius);
    }
}

void RosenRenderContext::AddModifier(const std::shared_ptr<Rosen::RSModifier>& modifier)
{
    CHECK_NULL_VOID(modifier);
    rsNode_->AddModifier(modifier);
}

void RosenRenderContext::RemoveModifier(const std::shared_ptr<Rosen::RSModifier>& modifier)
{
    CHECK_NULL_VOID(modifier);
    rsNode_->RemoveModifier(modifier);
}

// helper function to update one of the graphic effects
template<typename T, typename D>
void RosenRenderContext::UpdateGraphic(std::shared_ptr<T>& modifier, D data)
{
    CHECK_NULL_VOID_NOLOG(!RectIsNull());
    LOGD("updating graphic effect");
    SetGraphicModifier(modifier, data);
    RequestNextFrame();
}

void RosenRenderContext::OnFrontBrightnessUpdate(const Dimension& brightness)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBrightness(brightness.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontGrayScaleUpdate(const Dimension& grayScale)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetGrayScale(grayScale.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontContrastUpdate(const Dimension& contrast)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetContrast(contrast.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontSaturateUpdate(const Dimension& saturate)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetSaturate(saturate.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontSepiaUpdate(const Dimension& sepia)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetSepia(sepia.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontInvertUpdate(const Dimension& invert)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetInvert(invert.Value());
    RequestNextFrame();
}

void RosenRenderContext::OnFrontHueRotateUpdate(float hueRotate)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetHueRotate(hueRotate);
    RequestNextFrame();
}

void RosenRenderContext::OnFrontColorBlendUpdate(const Color& colorBlend)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetColorBlend(colorBlend.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::OnLinearGradientBlurUpdate(const NG::LinearGradientBlurPara& blurPara)
{
    float blurRadius = 0.0f;
    if (blurPara.blurRadius_.IsValid()) {
        float radiusPx = blurPara.blurRadius_.ConvertToPx();
        blurRadius = radiusPx;
    }

    CHECK_NULL_VOID(rsNode_);
    std::shared_ptr<Rosen::RSLinearGradientBlurPara> rsLinearGradientBlurPara(
        std::make_shared<Rosen::RSLinearGradientBlurPara>(
            blurRadius, blurPara.fractionStops_, static_cast<Rosen::GradientDirection>(blurPara.direction_)));

    rsNode_->SetLinearGradientBlurPara(rsLinearGradientBlurPara);
    RequestNextFrame();
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
    const std::unique_ptr<TransitionOptions>& options, const SizeF& frameSize)
{
    if (options == nullptr) {
        return nullptr;
    }
    std::shared_ptr<Rosen::RSTransitionEffect> effect = Rosen::RSTransitionEffect::Create();
    if (options->HasOpacity()) {
        effect = effect->Opacity(options->GetOpacityValue());
    }
    if (options->HasTranslate()) {
        const auto& translate = options->GetTranslateValue();
        effect = effect->Translate({ static_cast<float>(translate.x.ConvertToPxWithSize(frameSize.Width())),
            static_cast<float>(translate.y.ConvertToPxWithSize(frameSize.Height())),
            static_cast<float>(translate.z.ConvertToPx()) });
    }
    if (options->HasScale()) {
        const auto& scale = options->GetScaleValue();
        effect = effect->Scale({ scale.xScale, scale.yScale, scale.zScale });
    }
    if (options->HasRotate()) {
        const auto& rotate = options->GetRotateValue();
        effect = effect->Rotate({ rotate.xDirection, rotate.yDirection, rotate.zDirection, rotate.angle });
    }
    return effect;
}

void RosenRenderContext::PaintGradient(const SizeF& /*frameSize*/)
{
    CHECK_NULL_VOID(rsNode_);
    auto& gradientProperty = GetOrCreateGradient();
    Gradient gradient;
    if (gradientProperty->HasLinearGradient()) {
        gradient = gradientProperty->GetLinearGradientValue();
    }
    if (gradientProperty->HasRadialGradient()) {
        gradient = gradientProperty->GetRadialGradientValue();
    }
    if (gradientProperty->HasSweepGradient()) {
        gradient = gradientProperty->GetSweepGradientValue();
    }
    if (!gradientStyleModifier_) {
        gradientStyleModifier_ = std::make_shared<GradientStyleModifier>();
        rsNode_->AddModifier(gradientStyleModifier_);
    }
    auto borderRadius = GetBorderRadius();
    if (borderRadius.has_value()) {
        Rosen::Vector4f rsRadius;
        ConvertRadius(*borderRadius, rsRadius);
        gradientStyleModifier_->SetCornerRadius(rsRadius);
    }
    gradientStyleModifier_->SetGradient(gradient);
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
#ifndef USE_ROSEN_DRAWING
        auto skPath = SkiaDecorationPainter::SkiaCreateSkPath(basicShape, frameSize);
        rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
#else
        auto rsPath = DrawingDecorationPainter::DrawingCreatePath(basicShape, frameSize);
        rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
#endif
    }

    if (clip->HasClipMask()) {
        auto basicShape = clip->GetClipMaskValue();
#ifndef USE_ROSEN_DRAWING
        auto skPath = SkiaDecorationPainter::SkiaCreateSkPath(basicShape, frameSize);
        rsNode_->SetMask(Rosen::RSMask::CreatePathMask(skPath, SkiaDecorationPainter::CreateMaskSkPaint(basicShape)));
#else
        auto rsPath = DrawingDecorationPainter::DrawingCreatePath(basicShape, frameSize);
        rsNode_->SetMask(
            Rosen::RSMask::CreatePathMask(rsPath, DrawingDecorationPainter::CreateMaskDrawingBrush(basicShape)));
#endif
    }
}

void RosenRenderContext::PaintProgressMask()
{
    if (!moonProgressModifier_) {
        moonProgressModifier_ = std::make_shared<MoonProgressModifier>();
        rsNode_->AddModifier(moonProgressModifier_);
    }
    auto progress = GetProgressMaskValue();
    moonProgressModifier_->InitRatio();
    moonProgressModifier_->SetMaskColor(LinearColor(progress->GetColor()));
    moonProgressModifier_->SetMaxValue(progress->GetMaxValue());
    if (progress->GetValue() > moonProgressModifier_->GetMaxValue()) {
        progress->SetValue(moonProgressModifier_->GetMaxValue());
    }
    moonProgressModifier_->SetValue(progress->GetValue());
}

void RosenRenderContext::SetClipBoundsWithCommands(const std::string& commands)
{
    CHECK_NULL_VOID(rsNode_);
#ifndef USE_ROSEN_DRAWING
    SkPath skPath;
    SkParsePath::FromSVGString(commands.c_str(), &skPath);
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
#else
    RSRecordingPath rsPath;
    rsPath.BuildFromSVGString(commands);
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
#endif
}

void RosenRenderContext::ClipWithRect(const RectF& rectF)
{
    CHECK_NULL_VOID(rsNode_);
#ifndef USE_ROSEN_DRAWING
    SkPath skPath;
    skPath.addRect(rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height());
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(skPath));
#else
    RSRecordingPath rsPath;
    rsPath.AddRect({ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() });
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
#endif
}

void RosenRenderContext::ClipWithRRect(const RectF& rectF, const RadiusF& radiusF)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f rect;
    Rosen::Vector4f radius;
    rect.SetValues(rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height());
    radius.SetValues(radiusF.GetCorner(RoundRect::CornerPos::TOP_LEFT_POS).x,
        radiusF.GetCorner(RoundRect::CornerPos::TOP_RIGHT_POS).x,
        radiusF.GetCorner(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
        radiusF.GetCorner(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x);
    rsNode_->SetClipRRect(rect, radius);
    RequestNextFrame();
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

void RosenRenderContext::OnProgressMaskUpdate(const RefPtr<ProgressMaskProperty>&)
{
    PaintProgressMask();
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetClipToBounds(true);
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
#ifdef QUICK_PUSH_TRANSITION
        auto pipeline = PipelineBase::GetCurrentContext();
        if (pipeline) {
            const int32_t nanoToMilliSeconds = 1000000;
            const int32_t minTransitionDuration = pageTransitionDuration / 2;
            const int32_t frameDelayTime = 32;
            int32_t startDelayTime =
                static_cast<int32_t>(pipeline->GetTimeFromExternalTimer() - pipeline->GetLastTouchTime()) /
                nanoToMilliSeconds;
            startDelayTime = std::max(0, startDelayTime);
            int32_t delayedDuration = pageTransitionDuration > startDelayTime ? pageTransitionDuration - startDelayTime
                                                                              : pageTransitionDuration;
            delayedDuration = std::max(minTransitionDuration, delayedDuration - frameDelayTime);
            LOGI("Use quick push delayedDuration:%{public}d", delayedDuration);
            option.SetDuration(delayedDuration);
        }
#endif
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
        auto paintRect = GetPaintRectWithTransform();
        std::shared_ptr<Rosen::RectF> overlayRect;
        if (modifier_) {
            modifier_->SetCustomData(NG::OverlayTextData(overlayText));
            auto overlayOffset = modifier_->GetOverlayOffset();
            overlayRect = std::make_shared<Rosen::RectF>(paintRect.GetX(), paintRect.GetY(),
                paintRect.Width() + overlayOffset.GetX(), paintRect.Height() + overlayOffset.GetY());
            rsNode_->SetDrawRegion(overlayRect);
        } else {
            modifier_ = std::make_shared<OverlayTextModifier>();
            rsNode_->AddModifier(modifier_);
            modifier_->SetCustomData(NG::OverlayTextData(overlayText));
            auto overlayOffset = modifier_->GetOverlayOffset();
            overlayRect = std::make_shared<Rosen::RectF>(paintRect.GetX(), paintRect.GetY(),
                paintRect.Width() + overlayOffset.GetX(), paintRect.Height() + overlayOffset.GetY());
            rsNode_->SetDrawRegion(overlayRect);
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

void RosenRenderContext::RemoveChild(const RefPtr<RenderContext>& renderContext)
{
    CHECK_NULL_VOID(rsNode_);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    auto child = rosenRenderContext->GetRSNode();
    rsNode_->RemoveChild(child);
}

void RosenRenderContext::SetBounds(float positionX, float positionY, float width, float height)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBounds(positionX, positionY, width, height);
}

void RosenRenderContext::SetUsingContentRectForRenderFrame(bool value)
{
    useContentRectForRSFrame_ = value;
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

void RosenRenderContext::MarkContentChanged(bool isChanged)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkContentChanged(isChanged);
}

void RosenRenderContext::MarkDrivenRender(bool flag)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkDrivenRender(flag);
}

void RosenRenderContext::MarkDrivenRenderItemIndex(int32_t index)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkDrivenRenderItemIndex(index);
}

void RosenRenderContext::MarkDrivenRenderFramePaintState(bool flag)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkDrivenRenderFramePaintState(flag);
}

void RosenRenderContext::UpdateChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect)
{
    if (transitionEffect_) {
        // use effect to update rosenTransitionEffect activeValue
        if (RosenTransitionEffect::UpdateRosenTransitionEffect(transitionEffect_, effect)) {
            return;
        }
        LOGW("transition effect struct changed");
        transitionEffect_->Detach(Claim(this));
    }
    transitionEffect_ = RosenTransitionEffect::ConvertToRosenTransitionEffect(effect);
    hasDefaultTransition_ = false;
    CHECK_NULL_VOID(transitionEffect_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    bool isOnTheTree = frameNode->IsOnMainTree();
    // transition effects should be initialized without animation.
    RSNode::ExecuteWithoutAnimation([this, isOnTheTree, &frameNode]() {
        // transitionIn effects should be initialized as active if currently not on the tree.
        transitionEffect_->Attach(Claim(this), !isOnTheTree);
    });
}

void RosenRenderContext::NotifyTransition(bool isTransitionIn)
{
    CHECK_NULL_VOID_NOLOG(transitionEffect_);

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    LOGD("RosenTransitionEffect::NotifyTransition transition BEGIN, node %{public}d, isTransitionIn: %{public}d",
        frameNode->GetId(), isTransitionIn);

    RSNode::ExecuteWithoutAnimation([this, &frameNode, isTransitionIn]() {
        if (isTransitionIn && disappearingTransitionCount_ == 0) {
            // transitionIn, reset to state before attaching in case of node reappear
            transitionEffect_->Attach(Claim(this), true);
        }
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        SizeF rootSize(pipeline->GetRootWidth(), pipeline->GetRootHeight());
        auto parentOffset = frameNode->GetPaintRectOffset(true);
        auto rect = GetPaintRectWithoutTransform();
        // Do not consider the position after its own transform, as the transition modifier also affects the transform
        rect.SetOffset(parentOffset + rect.GetOffset());

        transitionEffect_->UpdateTransitionContext(Claim(this), rect, rootSize);
    });

    if (isTransitionIn) {
        // Isolate the animation callback function, to avoid changing the callback timing of current implicit animation.
        AnimationUtils::AnimateWithCurrentOptions(
            [this]() {
                transitionEffect_->Appear();
                ++appearingTransitionCount_;
            },
            [weakThis = WeakClaim(this), nodeId = frameNode->GetId(), id = Container::CurrentId()]() {
                auto context = weakThis.Upgrade();
                CHECK_NULL_VOID(context);
                ContainerScope scope(id);
                LOGD("RosenTransitionEffect::NotifyTransition transition END, node %{public}d, isTransitionIn: IN",
                    nodeId);
                context->OnTransitionInFinish();
            },
            false);
    } else {
        // Re-use current implicit animation timing params, only replace the finish callback function.
        // The finish callback function will perform all the necessary cleanup work.
        // Important Note on timing:
        // 1. If any transition animations are created, the finish callback function will only be called when ALL
        //    animations have finished. This is accomplished by sharing the same shared_ptr<AnimationFinishCallback>
        //    among all animations.
        // 2. If no transition animations are created, the finish callback function will be called IMMEDIATELY. This
        //    is accomplished by setting the last param (timing sensitive) to false, which avoids creating an empty
        //    'timer' animation.
        AnimationUtils::AnimateWithCurrentOptions(
            [this]() {
                transitionEffect_->Disappear();
                // update transition out count
                ++disappearingTransitionCount_;
            },
            [weakThis = WeakClaim(this), nodeId = frameNode->GetId(), id = Container::CurrentId()]() {
                auto context = weakThis.Upgrade();
                CHECK_NULL_VOID(context);
                ContainerScope scope(id);
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto taskExecutor = pipeline->GetTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                taskExecutor->PostTask(
                    [id, nodeId, context]() {
                        ContainerScope scope(id);
                        LOGD("RosenTransitionEffect::NotifyTransition transition END, node %{public}d, "
                             "isTransitionIn: OUT",
                            nodeId);
                        // update transition out count
                        context->OnTransitionOutFinish();
                    },
                    TaskExecutor::TaskType::UI);
            },
            false);
    }
}

void RosenRenderContext::RemoveDefaultTransition()
{
    if (hasDefaultTransition_ && transitionEffect_ && disappearingTransitionCount_ == 0 &&
        appearingTransitionCount_ == 0) {
        transitionEffect_->Detach(Claim(this));
        transitionEffect_ = nullptr;
        hasDefaultTransition_ = false;
    }
}

void RosenRenderContext::OnTransitionInFinish()
{
    --appearingTransitionCount_;
    // make sure we are the last transition out animation, if not, return.
    if (appearingTransitionCount_ > 0) {
        LOGD("RosenTransitionEffect: appearingTransitionCount_ is %{public}d, not the last transition out animation",
            appearingTransitionCount_);
        return;
    }
    if (appearingTransitionCount_ < 0) {
        LOGW("RosenTransitionEffect: appearingTransitionCount_ should not be less than 0");
        appearingTransitionCount_ = 0;
    }
    // when all transition in/out animations are finished, we should remove the default transition effect.
    RemoveDefaultTransition();
}

void RosenRenderContext::OnTransitionOutFinish()
{
    // update transition out count
    --disappearingTransitionCount_;
    // make sure we are the last transition out animation, if not, return.
    if (disappearingTransitionCount_ > 0) {
        LOGD("RosenTransitionEffect: disappearingTransitionCount_ is %{public}d, not the last transition out animation",
            disappearingTransitionCount_);
        return;
    }
    if (disappearingTransitionCount_ < 0) {
        LOGW("RosenTransitionEffect: disappearingTransitionCount_ should not be less than 0");
        disappearingTransitionCount_ = 0;
    }
    // when all transition in/out animations are finished, we should remove the default transition effect.
    RemoveDefaultTransition();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    if (!host->IsVisible()) {
        // trigger transition through visibility
        parent->MarkNeedSyncRenderTree();
        parent->RebuildRenderContextTree();
        return;
    }
    RefPtr<UINode> breakPointChild = host;
    RefPtr<UINode> breakPointParent = breakPointChild->GetParent();
    while (breakPointParent && !breakPointChild->IsDisappearing()) {
        // recursively looking up the node tree, until we reach the breaking point (IsDisappearing() == true).
        // Because when trigger transition, only the breakPoint will be marked as disappearing and
        // moved to disappearingChildren.
        breakPointChild = breakPointParent;
        breakPointParent = breakPointParent->GetParent();
    }
    // if can not find the breakPoint, means the node is not disappearing (reappear?), return.
    if (!breakPointParent) {
        LOGI("RosenTransitionEffect: node is not disappearing, skip, id: %{public}d", host->GetId());
        return;
    }
    if (breakPointChild->RemoveImmediately()) {
        LOGD("RosenTransitionEffect: transition out finish, node %{public}d, break point %{public}d, break point tag: "
             "%{public}s",
            host->GetId(), breakPointChild->GetId(), breakPointChild->GetTag().c_str());
        breakPointChild->OnRemoveFromParent(false);
        // remove breakPoint
        breakPointParent->RemoveDisappearingChild(breakPointChild);
        breakPointParent->MarkNeedSyncRenderTree();
        breakPointParent->RebuildRenderContextTree();
    } else {
        LOGD("RosenTransitionEffect: transition out finish, node %{public}d, node tag: %{public}s", host->GetId(),
            host->GetTag().c_str());
        // When host's transition is done, RemoveImmediately must return true, so this branch means
        // host is different from breakPointChild. It will be removed when breakPoint is removed.
    }
    if (isModalRootNode_ && breakPointParent->GetChildren().empty()) {
        auto grandParent = breakPointParent->GetParent();
        CHECK_NULL_VOID(grandParent);
        grandParent->RemoveChild(breakPointParent);
        grandParent->RebuildRenderContextTree();
    }
}

void RosenRenderContext::SetActualForegroundColor(const Color& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetForegroundColor(value.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> property)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(property);
    if (!property->GetModifyImpl()) {
        auto nodeModifierImpl = std::make_shared<RSNodeModifierImpl>();
        CHECK_NULL_VOID(nodeModifierImpl);
        property->SetModifyImpl(nodeModifierImpl);
        rsNode_->AddModifier(nodeModifierImpl);
        nodeModifierImpl->AddProperty(property->GetProperty());
    }
}

void RosenRenderContext::InitEventClickEffect()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto renderContext = weak.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->ClickEffectPlayAnimation(info.GetTouches().front().GetTouchType());
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void RosenRenderContext::ClickEffectPlayAnimation(const TouchType& touchType)
{
    if (touchType != TouchType::DOWN && touchType != TouchType::UP && touchType != TouchType::CANCEL) {
        return;
    }
    auto value = GetClickEffectLevelValue();
    auto level = value.level;
    auto scaleValue = value.scaleNumber;
    auto springCurve = UpdatePlayAnimationValue(level, scaleValue);

    AnimationOption option;
    option.SetCurve(springCurve);
    option.SetDuration(DEFAULT_OPTION_DURATION);

    if (touchType == TouchType::DOWN && level != ClickEffectLevel::UNDEFINED) {
        if (isTouchUpFinished_) {
            auto defaultScale = VectorF(1.0f, 1.0f);
            auto currentScale = GetTransformScaleValue(defaultScale);
            currentScale_ = currentScale;
            UpdateTransformScale(currentScale_);

            AnimationUtils::OpenImplicitAnimation(option, springCurve, nullptr);
            VectorF valueScale(scaleValue, scaleValue);
            UpdateTransformScale(valueScale);
            AnimationUtils::CloseImplicitAnimation();
        }
        isTouchUpFinished_ = false;
    }

    if ((touchType == TouchType::UP || touchType == TouchType::CANCEL) && level != ClickEffectLevel::UNDEFINED) {
        AnimationUtils::OpenImplicitAnimation(option, springCurve, nullptr);
        UpdateTransformScale(currentScale_);
        AnimationUtils::CloseImplicitAnimation();
        isTouchUpFinished_ = true;
    }
}

RefPtr<Curve> RosenRenderContext::UpdatePlayAnimationValue(const ClickEffectLevel& level, float& scaleValue)
{
    float velocity = 0.0f;
    float mass = 0.0f;
    float stiffness = 0.0f;
    float damping = 0.0f;
    if (level == ClickEffectLevel::LIGHT) {
        velocity = ANIMATION_CURVE_VELOCITY_LIGHT_OR_MIDDLE;
        mass = ANIMATION_CURVE_MASS;
        stiffness = ANIMATION_CURVE_STIFFNESS_LIGHT;
        damping = ANIMATION_CURVE_DAMPING_LIGHT;
        if (GreatOrEqual(scaleValue, 0.0) && LessOrEqual(scaleValue, 1.0)) {
            scaleValue = sqrt(scaleValue);
        } else {
            scaleValue = sqrt(DEFAULT_SCALE_LIGHT);
        }
    } else if (level == ClickEffectLevel::MIDDLE) {
        velocity = ANIMATION_CURVE_VELOCITY_LIGHT_OR_MIDDLE;
        mass = ANIMATION_CURVE_MASS;
        stiffness = ANIMATION_CURVE_STIFFNESS_MIDDLE;
        damping = ANIMATION_CURVE_DAMPING_MIDDLE;
        if (GreatOrEqual(scaleValue, 0.0) && LessOrEqual(scaleValue, 1.0)) {
            scaleValue = sqrt(scaleValue);
        } else {
            scaleValue = sqrt(DEFAULT_SCALE_MIDDLE_OR_HEAVY);
        }
    } else if (level == ClickEffectLevel::HEAVY) {
        velocity = ANIMATION_CURVE_VELOCITY_HEAVY;
        mass = ANIMATION_CURVE_MASS;
        stiffness = ANIMATION_CURVE_STIFFNESS_HEAVY;
        damping = ANIMATION_CURVE_DAMPING_HEAVY;
        if (GreatOrEqual(scaleValue, 0.0) && LessOrEqual(scaleValue, 1.0)) {
            scaleValue = sqrt(scaleValue);
        } else {
            scaleValue = sqrt(DEFAULT_SCALE_MIDDLE_OR_HEAVY);
        }
    }
    return AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
}

void RosenRenderContext::RegisterSharedTransition(const RefPtr<RenderContext>& other)
{
    auto otherContext = AceType::DynamicCast<RosenRenderContext>(other);
    if (!otherContext) {
        LOGE("RosenRenderContext::RegisterSharedTransition: other is not RosenRenderContext");
        return;
    }
    RSNode::RegisterTransitionPair(rsNode_->GetId(), otherContext->rsNode_->GetId());
}

void RosenRenderContext::UnregisterSharedTransition(const RefPtr<RenderContext>& other)
{
    auto otherContext = AceType::DynamicCast<RosenRenderContext>(other);
    if (!otherContext) {
        // the paired node is already destroyed, we don't need to unregister it, Rosen will handle it.
        return;
    }
    RSNode::UnregisterTransitionPair(rsNode_->GetId(), otherContext->rsNode_->GetId());
}

inline void RosenRenderContext::ConvertRadius(const BorderRadiusProperty& value, Rosen::Vector4f& cornerRadius)
{
    cornerRadius.SetValues(static_cast<float>(value.radiusTopLeft.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusTopRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension()).ConvertToPx()));
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderContext::PaintSkBgImage()
{
    auto image = DynamicCast<NG::SkiaImage>(bgImage_);
#else
void RosenRenderContext::PaintRSBgImage()
{
    auto image = DynamicCast<NG::DrawingImage>(bgImage_);
#endif
    CHECK_NULL_VOID(bgLoadingCtx_ && image);

    auto rosenImage = std::make_shared<Rosen::RSImage>();
    auto compressData = image->GetCompressData();
    if (compressData) {
        rosenImage->SetCompressData(
            compressData, image->GetUniqueID(), image->GetCompressWidth(), image->GetCompressHeight());
    } else {
        rosenImage->SetImage(image->GetImage());
    }
    rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
    rsNode_->SetBgImage(rosenImage);
}

void RosenRenderContext::PaintPixmapBgImage()
{
    auto image = DynamicCast<NG::PixelMapImage>(bgImage_);
    CHECK_NULL_VOID(bgLoadingCtx_ && image);
    auto pixmap = image->GetPixelMap();
    CHECK_NULL_VOID(pixmap);

    auto rosenImage = std::make_shared<Rosen::RSImage>();
    rosenImage->SetPixelMap(pixmap->GetPixelMapSharedPtr());
    rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
    rsNode_->SetBgImage(rosenImage);
}

void RosenRenderContext::OnRenderGroupUpdate(bool isRenderGroup)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkNodeGroup(isRenderGroup);
}

void RosenRenderContext::OnRenderFitUpdate(RenderFit renderFit)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFrameGravity(GetRosenGravity(renderFit));
}

void RosenRenderContext::SetContentRectToFrame(RectF rect)
{
    auto host = GetHost();
    auto&& padding = host->GetGeometryNode()->GetPadding();
    // minus padding to get contentRect
    if (padding) {
        rect.SetOffset(rect.GetOffset() + OffsetF { padding->left.value_or(0), padding->top.value_or(0) });
        auto size = rect.GetSize();
        MinusPaddingToSize(*padding, size);
        rect.SetSize(size);
    }
    rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
}

} // namespace OHOS::Ace::NG
