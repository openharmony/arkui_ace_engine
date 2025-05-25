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

#include "include/utils/SkParsePath.h"
#include "modifier/rs_property.h"
#include "render_service_base/include/property/rs_properties_def.h"
#include "render_service_base/include/render/rs_mask.h"
#include "render_service_client/core/modifier/rs_property_modifier.h"
#include "render_service_client/core/pipeline/rs_node_map.h"
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/transaction/rs_interfaces.h"
#include "render_service_client/core/ui/rs_canvas_drawing_node.h"
#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_effect_node.h"
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "rosen_render_context.h"

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/animation/native_curve_helper.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/overlay/accessibility_focus_paint_node_pattern.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/render/adapter/background_modifier.h"
#include "core/components_ng/render/adapter/border_image_modifier.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/render/adapter/debug_boundary_modifier.h"
#include "core/components_ng/render/adapter/focus_state_modifier.h"
#include "core/components_ng/render/adapter/gradient_style_modifier.h"
#include "core/components_ng/render/adapter/mouse_select_modifier.h"
#include "core/components_ng/render/adapter/overlay_modifier.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/components_ng/render/adapter/transition_modifier.h"
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "render_service_client/core/pipeline/rs_render_thread.h"
#endif
#include "core/components_ng/render/adapter/drawing_decoration_painter.h"
#include "core/components_ng/render/adapter/drawing_image.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/border_image_painter.h"
#include "core/components_ng/render/debug_boundary_painter.h"
#include "core/components_ng/render/image_painter.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/draw/modifier.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

using namespace OHOS::Rosen;
namespace {
RefPtr<PixelMap> g_pixelMap {};
std::mutex g_mutex;
std::condition_variable thumbnailGet;
constexpr std::chrono::duration<int, std::milli> PIXELMAP_TIMEOUT_DURATION(1000);
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
constexpr int32_t PARTICLE_DEFAULT_COLOR = 0xFFFFFFFF;
constexpr float PARTICLE_DEFAULT_OPACITY = 1.0f;
constexpr float PARTICLE_DEFAULT_SCALE = 1.0f;
constexpr float PARTICLE_DEFAULT_SPEED = 0.0f;
constexpr float PARTICLE_DEFAULT_ANGLE = 0.0f;
constexpr float PARTICLE_DEFAULT_SPIN = 0.0f;
constexpr int64_t PARTICLE_DEFAULT_LIFETIME = 1000;
constexpr int32_t PARTICLE_DEFAULT_EMITTER_RATE = 5;
constexpr uint32_t DRAW_REGION_CONTENT_MODIFIER_INDEX = 0;
constexpr uint32_t DRAW_REGION_OVERLAY_MODIFIER_INDEX = 1;
constexpr uint32_t DRAW_REGION_FOCUS_MODIFIER_INDEX = 2;
constexpr uint32_t DRAW_REGION_ACCESSIBILITY_FOCUS_MODIFIER_INDEX = 3;
constexpr uint32_t DRAW_REGION_OVERLAY_TEXT_MODIFIER_INDEX = 4;
constexpr uint32_t DRAW_REGION_DEBUG_BOUNDARY_MODIFIER_INDEX = 5;
constexpr uint32_t DRAW_REGION_FOREGROUND_MODIFIER_INDEX = 6;
constexpr uint32_t DRAW_REGION_TRANSITION_MODIFIER_INDEX = 7;
constexpr int32_t RIGHT_ANGLE = 90;
constexpr int32_t STRAIGHT_ANGLE = 180;
constexpr int32_t REFLEX_ANGLE = 270;
constexpr int32_t FULL_ROTATION = 360;
constexpr int32_t ACCESSIBILITY_FOCUS_WITHOUT_EVENT = -2100001;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
const Color DEFAULT_MASK_COLOR = Color::FromARGB(0, 0, 0, 0);
constexpr Dimension DASH_GEP_WIDTH = -1.0_px;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_3 = 3;
constexpr float FLOAT_ZERO = 0.0f;
constexpr uint16_t NO_FORCE_ROUND = static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START) |
                                    static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP) |
                                    static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END) |
                                    static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);

static void DrawNodeChangeCallback(std::shared_ptr<RSNode> rsNode, bool isPositionZ)
{
    if (!SystemProperties::GetContainerDeleteFlag()) {
        return;
    }
    CHECK_NULL_VOID(rsNode);
    auto uiNode = ElementRegister::GetInstance()->GetUINodeById(rsNode->GetFrameNodeId());
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
    CHECK_NULL_VOID(frameNode);
    if (isPositionZ) {
        frameNode->SetPositionZ(true);
        auto pipeline = uiNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddPositionZNode(rsNode->GetFrameNodeId());
        return;
    }

    if (frameNode->GetRenderContext()) {
        frameNode->GetRenderContext()->AddNodeToRsTree();
    }
}

bool SetDrawNodeChangeCallback()
{
    Rosen::RSNode::SetDrawNodeChangeCallback(DrawNodeChangeCallback);
    return true;
}

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

ColorMode GetResourceColorMode(PipelineContext* pipeline)
{
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, ColorMode::LIGHT);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, ColorMode::LIGHT);
    auto resourceAdapter = themeConstants->GetResourceAdapter();
    CHECK_NULL_RETURN(resourceAdapter, ColorMode::LIGHT);
    return resourceAdapter->GetResourceColorMode();
}

std::shared_ptr<Rosen::RSFilter> CreateRSMaterialFilter(
    const BlurStyleOption& blurStyleOption, PipelineContext* pipeline, const SysOptions& sysOptions)
{
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        LOGW("cannot find theme of blurStyle, create blurStyle failed");
        return nullptr;
    }
    ThemeColorMode colorMode = blurStyleOption.colorMode;
    if (blurStyleOption.colorMode == ThemeColorMode::SYSTEM) {
        colorMode = GetResourceColorMode(pipeline) == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    }
    auto blurParam = blurStyleTheme->GetBlurParameter(blurStyleOption.blurStyle, colorMode);
    CHECK_NULL_RETURN(blurParam, nullptr);
    auto ratio = blurStyleOption.scale;
    auto maskColor = blurParam->maskColor.BlendOpacity(ratio);
    auto radiusPx = blurParam->radius * pipeline->GetDipScale();
    auto radiusBlur = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx) * ratio;
    auto saturation = (blurParam->saturation - 1) * ratio + 1.0;
    auto brightness = (blurParam->brightness - 1) * ratio + 1.0;
    return Rosen::RSFilter::CreateMaterialFilter(radiusBlur, saturation, brightness, maskColor.GetValue(),
        static_cast<Rosen::BLUR_COLOR_MODE>(blurStyleOption.adaptiveColor), sysOptions.disableSystemAdaptation);
}

RSPen GetRsPen(uint32_t strokeColor, float strokeWidth)
{
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(strokeColor);

    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(strokeWidth);

    return pen;
}

RSBrush GetRsBrush(uint32_t fillColor)
{
    RSColor color;
    color.SetColorQuad(fillColor);
    RSBrush brush(color);

    return brush;
}

template<typename ModifierName, typename T>
T GetAnimatablePropertyStagingValue(std::shared_ptr<ModifierName>& modifier, const T& defaultValue = {})
{
    CHECK_NULL_RETURN(modifier, defaultValue);
    auto property = std::static_pointer_cast<Rosen::RSAnimatableProperty<T>>(modifier->GetProperty());
    CHECK_NULL_RETURN(property, defaultValue);
    return property->GetStagingValue();
}

template<typename ModifierName, typename T>
void CancelModifierAnimation(std::shared_ptr<ModifierName>& modifier)
{
    // request cancel all the animations on rs modifier.
    CHECK_NULL_VOID(modifier);
    auto property = std::static_pointer_cast<Rosen::RSAnimatableProperty<T>>(modifier->GetProperty());
    CHECK_NULL_VOID(property);
    property->RequestCancelAnimation();
}
} // namespace

bool RosenRenderContext::initDrawNodeChangeCallback_ = SetDrawNodeChangeCallback();

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
    DetachModifiers();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveExtraCustomProperty("RS_NODE");
}

void RosenRenderContext::DetachModifiers()
{
    CHECK_NULL_VOID(rsNode_ && rsNode_->GetType() == Rosen::RSUINodeType::SURFACE_NODE);
    if (transitionEffect_) {
        transitionEffect_->Detach(this);
    }
    std::shared_ptr<Rosen::RSModifier> modifiers[] = { translateXYUserModifier_, translateZUserModifier_,
        scaleXYUserModifier_, rotationXUserModifier_, rotationYUserModifier_, rotationZUserModifier_,
        cameraDistanceUserModifier_, baseTranslateInXY_, baseRotateInZ_, alphaUserModifier_ };
    for (auto& modifier : modifiers) {
        if (modifier) {
            rsNode_->RemoveModifier(modifier);
        }
    }
    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    if (pipeline) {
        pipeline->RequestFrame();
    }
}

void RosenRenderContext::StartRecording()
{
    CHECK_NULL_VOID(rsNode_);
    auto rsCanvasNode = rsNode_->ReinterpretCastTo<Rosen::RSCanvasNode>();
    CHECK_NULL_VOID(rsCanvasNode);
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
    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->RestoreEnabled();
    }
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
    if (!recursive && host && host->GetOrCreateEventHub<EventHub>()) {
        host->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(false);
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
    auto changed = true;
    if (pivotProperty_) {
        changed = pivotProperty_->Get().x_ != xPivot || pivotProperty_->Get().y_ != yPivot;
        pivotProperty_->Set({ xPivot, yPivot });
    } else {
        pivotProperty_ = std::make_shared<Rosen::RSProperty<Rosen::Vector2f>>(Rosen::Vector2f(xPivot, yPivot));
        auto modifier = std::make_shared<Rosen::RSPivotModifier>(pivotProperty_);
        rsNode_->AddModifier(modifier);
    }
    rsNode_->SetPivotZ(zPivot);
    NotifyHostTransformUpdated(changed);
}

void RosenRenderContext::SetTransitionPivot(const SizeF& frameSize, bool transitionIn)
{
    auto& transitionEffect = transitionIn ? propTransitionAppearing_ : propTransitionDisappearing_;
    CHECK_NULL_VOID(transitionEffect);
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

void RosenRenderContext::SetSurfaceChangedCallBack(const std::function<void(float, float, float, float)>& callback)
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    if (rsNode_) {
        RSRenderThread::Instance().AddSurfaceChangedCallBack(rsNode_->GetId(), callback);
    }
#endif
}

void RosenRenderContext::RemoveSurfaceChangedCallBack()
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    if (rsNode_) {
        RSRenderThread::Instance().RemoveSurfaceChangedCallBack(rsNode_->GetId());
    }
#endif
}

void RosenRenderContext::AddFrameNodeInfoToRsNode()
{
    if (rsNode_) {
        rsNode_->SetInstanceId(Container::CurrentId());
        auto frameNodePtr = GetHost();
        CHECK_NULL_VOID(frameNodePtr);
        rsNode_->SetFrameNodeInfo(frameNodePtr->GetId(), frameNodePtr->GetTag());
    }
}

void RosenRenderContext::SetHostNode(const WeakPtr<FrameNode>& host)
{
    RenderContext::SetHostNode(host);
    AddFrameNodeInfoToRsNode();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddExtraCustomProperty("RS_NODE", rsNode_.get());
}

std::shared_ptr<Rosen::RSUIContext> RosenRenderContext::GetRSUIContext()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto window = pipeline->GetWindow();
    CHECK_NULL_RETURN(window, nullptr);
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_RETURN(rsUIDirector, nullptr);
    return rsUIDirector->GetRSUIContext();
}

void RosenRenderContext::InitContext(bool isRoot, const std::optional<ContextParam>& param, bool isLayoutNode)
{
    if (isLayoutNode) {
        return;
    }
    InitContext(isRoot, param);
}

void RosenRenderContext::InitContext(bool isRoot, const std::optional<ContextParam>& param)
{
    // skip if node already created
    CHECK_NULL_VOID(!rsNode_);
    auto rsContext = GetRSUIContext();
    auto isTextureExportNode = ViewStackProcessor::GetInstance()->IsExportTexture();
    if (isRoot) {
        rsNode_ = Rosen::RSRootNode::Create(false, isTextureExportNode, rsContext);
        if (SystemProperties::GetMultiInstanceEnabled() && rsNode_) {
            rsNode_->SetSkipCheckInMultiInstance(true);
        }
        AddFrameNodeInfoToRsNode();
        return;
    } else if (!param.has_value()) {
        rsNode_ = Rosen::RSCanvasNode::Create(false, isTextureExportNode, rsContext);
        if (SystemProperties::GetMultiInstanceEnabled() && rsNode_) {
            rsNode_->SetSkipCheckInMultiInstance(true);
        }
        AddFrameNodeInfoToRsNode();
        return;
    }
    patternType_ = param->patternType;
    // create proper RSNode base on input
    switch (param->type) {
        case ContextType::CANVAS:
            rsNode_ = Rosen::RSCanvasNode::Create(false, isTextureExportNode, rsContext);
            break;
        case ContextType::ROOT:
            rsNode_ = Rosen::RSRootNode::Create(false, isTextureExportNode, rsContext);
            break;
        case ContextType::SURFACE: {
            Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = param->surfaceName.value_or(""),
                .isTextureExportNode = isTextureExportNode };
            rsNode_ = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false, rsContext);
            break;
        }
        case ContextType::HARDWARE_SURFACE: {
            rsNode_ = CreateHardwareSurface(param, isTextureExportNode, rsContext);
            break;
        }
#ifdef RENDER_EXTRACT_SUPPORTED
        case ContextType::HARDWARE_TEXTURE: {
            rsNode_ = CreateHardwareTexture(param, isTextureExportNode);
            break;
        }
#endif
        case ContextType::EFFECT:
            rsNode_ = Rosen::RSEffectNode::Create(false, isTextureExportNode, rsContext);
            break;
        case ContextType::INCREMENTAL_CANVAS: {
#ifdef ACE_ENABLE_HYBRID_RENDER
            if (RSSystemProperties::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::CANVAS)) {
                rsNode_ = Rosen::RSCanvasNode::Create(false, isTextureExportNode, rsContext);
                rsNode_->SetHybridRenderCanvas(true);
            } else {
                rsNode_ = Rosen::RSCanvasDrawingNode::Create(false, isTextureExportNode, rsContext);
            }
#else
            rsNode_ = Rosen::RSCanvasDrawingNode::Create(false, isTextureExportNode, rsContext);
#endif
            break;
        }
        case ContextType::EXTERNAL:
            break;
        default:
            break;
    }
    if (SystemProperties::GetMultiInstanceEnabled() && rsNode_) {
        rsNode_->SetSkipCheckInMultiInstance(true);
    }
    AddFrameNodeInfoToRsNode();
}

std::shared_ptr<Rosen::RSNode> RosenRenderContext::CreateHardwareSurface(const std::optional<ContextParam>& param,
    bool isTextureExportNode, std::shared_ptr<Rosen::RSUIContext>& rsUIContext)
{
    Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = param->surfaceName.value_or(""),
        .isTextureExportNode = isTextureExportNode, .isSync = true };
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode;
    if (rsUIContext) {
        surfaceNode = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false, rsUIContext);
    } else {
        surfaceNode = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
    }
    if (surfaceNode) {
        if (param->patternType == PatternType::VIDEO) {
            surfaceNode->SetHardwareEnabled(true, SelfDrawingNodeType::VIDEO);
        } else if (param->patternType == PatternType::XCOM) {
            surfaceNode->SetHardwareEnabled(true, SelfDrawingNodeType::XCOM);
        } else {
            surfaceNode->SetHardwareEnabled(true, SelfDrawingNodeType::DEFAULT);
        }
        surfaceNode->SetApiCompatibleVersion(Container::GetCurrentApiTargetVersion());
    }
    return surfaceNode;
}

#ifdef RENDER_EXTRACT_SUPPORTED
std::shared_ptr<Rosen::RSNode> RosenRenderContext::CreateHardwareTexture(
    const std::optional<ContextParam>& param, bool isTextureExportNode)
{
    Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = param->surfaceName.value_or(""),
        .isTextureExportNode = isTextureExportNode };
    auto surfaceNode = Rosen::RSSurfaceNode::Create(surfaceNodeConfig, RSSurfaceNodeType::SURFACE_TEXTURE_NODE, false);
    return surfaceNode;
}
#endif

void RosenRenderContext::SetSandBox(const std::optional<OffsetF>& parentPosition, bool force)
{
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (parentPosition.has_value()) {
        if (!force) {
            sandBoxCount_++;
        }
        Rosen::Vector2f value = { parentPosition.value().GetX(), parentPosition.value().GetY() };
        TAG_LOGI(AceLogTag::ACE_GEOMETRY_TRANSITION, "node[%{public}s] Set SandBox",
            std::to_string(rsNode_->GetId()).c_str());
        rsNode_->SetSandBox(value);
    } else {
        if (!force) {
            sandBoxCount_--;
            if (sandBoxCount_ > 0) {
                return;
            }
        }
        TAG_LOGI(AceLogTag::ACE_GEOMETRY_TRANSITION, "node[%{public}s] Remove SandBox",
            std::to_string(rsNode_->GetId()).c_str());
        sandBoxCount_ = 0;
        rsNode_->SetSandBox(std::nullopt);
    }
}

void RosenRenderContext::SetFrameWithoutAnimation(const RectF& paintRect)
{
    CHECK_NULL_VOID(rsNode_ && paintRect.IsValid());
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::ExecuteWithoutAnimation([rosenRenderContext = Claim(this), &paintRect]() {
            rosenRenderContext->SyncGeometryFrame(paintRect);
        }, rsUIContext);
}

void RosenRenderContext::SyncGeometryProperties(GeometryNode* /*geometryNode*/, bool /* isRound */, uint8_t /* flag */)
{
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isNeedAnimate_) {
        SyncGeometryProperties(paintRect_);
    } else {
        auto rsUIContext = rsNode_->GetRSUIContext();
        RSNode::ExecuteWithoutAnimation([rosenRenderContext = Claim(this)]() {
                rosenRenderContext->SyncGeometryProperties(rosenRenderContext->paintRect_);
            }, rsUIContext);
    }
    host->OnPixelRoundFinish(paintRect_.GetSize());
}

void RosenRenderContext::SyncGeometryFrame(const RectF& paintRect)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBounds(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    if (rsTextureExport_) {
        rsTextureExport_->UpdateBufferInfo(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    }
    if (handleChildBounds_) {
        SetChildBounds(paintRect);
    }
    if (useContentRectForRSFrame_) {
        SetContentRectToFrame(paintRect);
    } else {
        rsNode_->SetFrame(paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
    }
    if (frameOffset_.has_value()) {
        rsNode_->SetFrame(paintRect.GetX() + frameOffset_->GetX(), paintRect.GetY() + frameOffset_->GetY(),
            paintRect.Width(), paintRect.Height());
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnSyncGeometryFrameFinish(paintRect);
}

void RosenRenderContext::SetChildBounds(const RectF& paintRect) const
{
    CHECK_NULL_VOID(rsNode_);
    auto child = rsNode_->GetChildByIndex(0);
    if (child) {
        child->SetBounds(0.0f, 0.0f, paintRect.Width(), paintRect.Height());
    }
}

void RosenRenderContext::SyncGeometryProperties(const RectF& paintRect)
{
    CHECK_NULL_VOID(rsNode_);
    if (isDisappearing_ && !paintRect.IsValid()) {
        return;
    }
    if (SystemProperties::GetSyncDebugTraceEnabled()) {
        auto host = GetHost();
        ACE_LAYOUT_SCOPED_TRACE("SyncGeometryProperties [%s][self:%d] set bounds %s", host->GetTag().c_str(),
            host->GetId(), paintRect.ToString().c_str());
    }
    if (extraOffset_.has_value()) {
        SyncGeometryFrame(paintRect + extraOffset_.value());
    } else {
        SyncGeometryFrame(paintRect);
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

    SyncPartialRsProperties();
    SyncAdditionalGeometryProperties(paintRect);
}

void RosenRenderContext::SyncAdditionalGeometryProperties(const RectF& paintRect)
{
    if (propPointLight_ && propPointLight_->HasLightPosition()) {
        // if lightPosition unit is percent, it is related with frameSize
        OnLightPositionUpdate(propPointLight_->GetLightPositionValue());
    }

    if (bgLoadingCtx_ && bgImage_) {
        PaintBackground();
    }

    auto sourceFromImage = GetBorderSourceFromImage().value_or(false);
    if (sourceFromImage && bdImageLoadingCtx_ && bdImage_) {
        PaintBorderImage();
    } else if (!sourceFromImage && GetBorderImageGradient()) {
        PaintBorderImageGradient();
    }

    if (propGradient_) {
        PaintGradient(paintRect.GetSize());
    }

    if (propClip_) {
        PaintClip(paintRect.GetSize());
    }

    if (HasProgressMask() && GetProgressMaskValue()) {
        PaintProgressMask();
    }

    if (propGraphics_) {
        PaintGraphics();
    }

    if (propOverlay_) {
        PaintOverlayText();
    }

    if (SystemProperties::GetDebugBoundaryEnabled()) {
        PaintDebugBoundary(true);
    }

    if (propParticleOptionArray_.has_value()) {
        if (!measureTriggered_ || particleAnimationPlaying_) {
            measureTriggered_ = true;
            OnParticleOptionArrayUpdate(propParticleOptionArray_.value());
        }
    }
    OnEmitterPropertyUpdate();
}

void RosenRenderContext::PaintDebugBoundary(bool flag)
{
    if (!flag && !debugBoundaryModifier_) {
        return;
    }
    if (!NeedDebugBoundary()) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    auto paintTask = [contentSize = geometryNode->GetFrameSize(), frameSize = geometryNode->GetMarginFrameSize(),
                         offset = geometryNode->GetMarginFrameOffset(), frameOffset = geometryNode->GetFrameOffset(),
                         flag](RSCanvas& rsCanvas) mutable {
        if (!flag) {
            return;
        }
        DebugBoundaryPainter painter(contentSize, frameSize);
        painter.SetFrameOffset(frameOffset);
        painter.DrawDebugBoundaries(rsCanvas, offset);
    };

    if (!debugBoundaryModifier_ && rsNode_->IsInstanceOf<Rosen::RSCanvasNode>()) {
        debugBoundaryModifier_ = std::make_shared<DebugBoundaryModifier>();
        debugBoundaryModifier_->SetPaintTask(std::move(paintTask));
        debugBoundaryModifier_->SetNoNeedUICaptured(true);
        auto rect = GetPaintRectWithoutTransform();
        auto marginOffset = geometryNode->GetMarginFrameOffset();
        std::shared_ptr<Rosen::RectF> drawRect =
            std::make_shared<Rosen::RectF>(marginOffset.GetX() - rect.GetX(), marginOffset.GetY() - rect.GetY(),
                geometryNode->GetMarginFrameSize().Width(), geometryNode->GetMarginFrameSize().Height());
        UpdateDrawRegion(DRAW_REGION_DEBUG_BOUNDARY_MODIFIER_INDEX, drawRect);
        rsNode_->AddModifier(debugBoundaryModifier_);
        // SetCustomData(AttachProperty to rs modifier) must be called after AddModifier.
        debugBoundaryModifier_->SetCustomData(flag);
    } else if (debugBoundaryModifier_) {
        debugBoundaryModifier_->SetPaintTask(std::move(paintTask));
        auto rect = GetPaintRectWithoutTransform();
        auto marginOffset = geometryNode->GetMarginFrameOffset();
        std::shared_ptr<Rosen::RectF> drawRect =
            std::make_shared<Rosen::RectF>(marginOffset.GetX() - rect.GetX(), marginOffset.GetY() - rect.GetY(),
                geometryNode->GetMarginFrameSize().Width(), geometryNode->GetMarginFrameSize().Height());
        UpdateDrawRegion(DRAW_REGION_DEBUG_BOUNDARY_MODIFIER_INDEX, drawRect);
        debugBoundaryModifier_->SetCustomData(flag);
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
    if (SystemProperties::ConfigChangePerform()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern();
        pattern->OnForegroundColorUpdate();
    }
}

void RosenRenderContext::OnForegroundEffectUpdate(float radius)
{
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    CalcDimension value;
    value.SetValue(static_cast<double>(radius));
    float radiusPx = context->NormalizeToPx(value);
    float foreRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
    rsNode_->SetForegroundEffectRadius(foreRadius);
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
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_IMAGE, "backgroundImageDataReady src = %{private}s", sourceInfo.ToString().c_str());
        }
        auto rosenRenderContext = weak.Upgrade();
        CHECK_NULL_VOID(rosenRenderContext);
        auto imageSourceInfo = rosenRenderContext->GetBackgroundImage().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            return;
        }
        rosenRenderContext->bgLoadingCtx_->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
    return task;
}

LoadSuccessNotifyTask RosenRenderContext::CreateBgImageLoadSuccessCallback()
{
    auto task = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(
                AceLogTag::ACE_IMAGE, "backgroundImageLoadSuccess src = %{private}s", sourceInfo.ToString().c_str());
        }
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto imageSourceInfo = ctx->GetBackgroundImage().value_or(ImageSourceInfo(""));
        if (imageSourceInfo != sourceInfo) {
            return;
        }
        ctx->bgImage_ = ctx->bgLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(ctx->bgImage_);
        if (ctx->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            ctx->PaintBackground();
            ctx->RequestNextFrame();
        }
    };
    return task;
}

void RosenRenderContext::PaintBackground()
{
    CHECK_NULL_VOID(rsNode_);
    if (InstanceOf<PixelMapImage>(bgImage_)) {
        PaintPixmapBgImage();
    } else if (InstanceOf<DrawingImage>(bgImage_)) {
        PaintRSBgImage();
    } else {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            rsNode_->SetBgImage(nullptr);
        }
        return;
    }
    auto srcSize = bgLoadingCtx_->GetImageSize();
    SizeF renderSize = ImagePainter::CalculateBgImageSize(paintRect_.GetSize(), srcSize, GetBackgroundImageSize());
    OffsetF positionOffset =
        ImagePainter::CalculateBgImagePosition(paintRect_.GetSize(), renderSize, GetBackgroundImagePosition());
    auto slice = GetBackgroundImageResizableSliceValue(ImageResizableSlice());
    Rosen::Vector4f rect(slice.left.ConvertToPxWithSize(srcSize.Width()),
        slice.top.ConvertToPxWithSize(srcSize.Height()),
        srcSize.Width() - (slice.left + slice.right).ConvertToPxWithSize(srcSize.Width()),
        srcSize.Height() - (slice.top + slice.bottom).ConvertToPxWithSize(srcSize.Height()));
    rsNode_->SetBgImageWidth(renderSize.Width());
    rsNode_->SetBgImageHeight(renderSize.Height());
    rsNode_->SetBgImagePositionX(positionOffset.GetX());
    rsNode_->SetBgImagePositionY(positionOffset.GetY());
    rsNode_->SetBgImageInnerRect(rect);
}

void RosenRenderContext::OnBackgroundImageUpdate(const ImageSourceInfo& src)
{
    CHECK_NULL_VOID(rsNode_);
    if (src.GetSrc().empty() && src.GetPixmap() == nullptr) {
        bgImage_ = nullptr;
        bgLoadingCtx_ = nullptr;
        auto frameNode = GetHost();
        if (frameNode) {
            frameNode->SetColorModeUpdateCallback(nullptr);
        }
        PaintBackground();
        return;
    }
    if (!bgLoadingCtx_ || src != bgLoadingCtx_->GetSourceInfo()) {
        auto frameNode = GetHost();
        auto callback = [src, weak = WeakClaim(this)] {
            auto renderContext = weak.Upgrade();
            CHECK_NULL_VOID(renderContext);
            renderContext->OnBackgroundImageUpdate(src);
        };
        frameNode->SetColorModeUpdateCallback(std::move(callback));
    }
    LoadNotifier bgLoadNotifier(CreateBgImageDataReadyCallback(), CreateBgImageLoadSuccessCallback(), nullptr);
    auto syncMode = GetBackgroundImageSyncMode().value_or(false);
    bgLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(src, std::move(bgLoadNotifier), syncMode);
    CHECK_NULL_VOID(bgLoadingCtx_);
    bgLoadingCtx_->LoadImageData();
}

void RosenRenderContext::OnBackgroundImageRepeatUpdate(const ImageRepeat& /*imageRepeat*/)
{
    CHECK_NULL_VOID(rsNode_);
    PaintBackground();
}

void RosenRenderContext::OnBackgroundImageSyncModeUpdate(bool /*syncMode*/)
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

void RosenRenderContext::OnBackgroundImageResizableSliceUpdate(const ImageResizableSlice& /*ImageResizableSlice*/)
{
    CHECK_NULL_VOID(rsNode_);
    PaintBackground();
}

bool RosenRenderContext::HasValidBgImageResizable()
{
    CHECK_NULL_RETURN(bgLoadingCtx_, false);
    auto srcSize = bgLoadingCtx_->GetImageSize();
    auto slice = GetBackgroundImageResizableSliceValue(ImageResizableSlice());
    auto left = slice.left.ConvertToPxWithSize(srcSize.Width());
    auto right = slice.right.ConvertToPxWithSize(srcSize.Width());
    auto top = slice.top.ConvertToPxWithSize(srcSize.Width());
    auto bottom = slice.bottom.ConvertToPxWithSize(srcSize.Width());
    return srcSize.Width() > left + right && srcSize.Height() > top + bottom && right > 0 && bottom > 0;
}

void RosenRenderContext::SetBackBlurFilter()
{
    CHECK_NULL_VOID(rsNode_);
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    const auto& background = GetBackground();
    CHECK_NULL_VOID(background);
    const auto& blurStyleOption = background->propBlurStyleOption;
    auto sysOptions = background->propSysOptions.value_or(SysOptions());
    std::shared_ptr<Rosen::RSFilter> backFilter;
    if (!blurStyleOption.has_value()) {
        const auto& radius = background->propBlurRadius;
        if (radius.has_value() && radius->IsValid()) {
            float radiusPx = context->NormalizeToPx(radius.value());
            float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
            backFilter =
                Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius, sysOptions.disableSystemAdaptation);
        }
    } else {
        backFilter = CreateRSMaterialFilter(blurStyleOption.value(), context, sysOptions);
    }
    rsNode_->SetBackgroundFilter(backFilter);
}

void RosenRenderContext::UpdateWindowFocusState(bool isFocused)
{
    if (GetBackBlurStyle().has_value() &&
        GetBackBlurStyle()->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        auto blurStyle = GetBackBlurStyle().value();
        blurStyle.isWindowFocused = isFocused;
        UpdateBackBlurStyle(blurStyle);
    }
    if (GetBackgroundEffect().has_value() &&
        GetBackgroundEffect()->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        auto effect = GetBackgroundEffect().value();
        effect.isWindowFocused = isFocused;
        UpdateBackgroundEffect(effect);
    }
}

void RosenRenderContext::UpdateWindowActiveState(bool isActive)
{
    auto useEffect = GetUseEffect().value_or(false);
    auto effectType = GetUseEffectType().value_or(EffectType::DEFAULT);
    if (effectType == EffectType::WINDOW_EFFECT) {
        OnUseEffectUpdate(useEffect);
    }
}

void RosenRenderContext::SetFrontBlurFilter()
{
    CHECK_NULL_VOID(rsNode_);
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    const auto& foreground = GetForeground();
    CHECK_NULL_VOID(foreground);
    const auto& blurStyleOption = foreground->propBlurStyleOption;
    auto sysOptions = foreground->propSysOptionsForBlur.value_or(SysOptions());
    std::shared_ptr<Rosen::RSFilter> frontFilter;
    if (!blurStyleOption.has_value()) {
        const auto& radius = foreground->propBlurRadius;
        if (radius.has_value() && radius->IsValid()) {
            float radiusPx = context->NormalizeToPx(radius.value());
            float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
            frontFilter =
                Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius, sysOptions.disableSystemAdaptation);
        }
    } else {
        frontFilter = CreateRSMaterialFilter(blurStyleOption.value(), context, sysOptions);
    }

    rsNode_->SetFilter(frontFilter);
}

bool RosenRenderContext::UpdateBlurBackgroundColor(const std::optional<BlurStyleOption>& bgBlurStyle)
{
    if (!bgBlurStyle.has_value()) {
        return false;
    }
    bool blurEnable =
        bgBlurStyle->policy == BlurStyleActivePolicy::ALWAYS_ACTIVE ||
        (bgBlurStyle->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE && bgBlurStyle->isWindowFocused);
    if (bgBlurStyle->isValidColor) {
        if (blurEnable) {
            rsNode_->SetBackgroundColor(GetBackgroundColor().value_or(Color::TRANSPARENT).GetValue());
        } else {
            rsNode_->SetBackgroundColor(bgBlurStyle->inactiveColor.GetValue());
        }
    }
    return blurEnable;
}

bool RosenRenderContext::UpdateBlurBackgroundColor(const std::optional<EffectOption>& efffectOption)
{
    bool blurEnable =
        efffectOption->policy == BlurStyleActivePolicy::ALWAYS_ACTIVE ||
        (efffectOption->policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE && efffectOption->isWindowFocused);
    if (efffectOption->isValidColor) {
        if (blurEnable) {
            rsNode_->SetBackgroundColor(GetBackgroundColor().value_or(Color::TRANSPARENT).GetValue());
        } else {
            rsNode_->SetBackgroundColor(efffectOption->inactiveColor.GetValue());
        }
    }
    return blurEnable;
}

void RosenRenderContext::UpdateBlurStyleForColorMode(
    const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [weak = AceType::WeakClaim(this), bgBlurStyle, sysOptions](
                            const RefPtr<ResourceObject>& resObj) {
        auto render = weak.Upgrade();
        CHECK_NULL_VOID(render);
        CHECK_NULL_VOID(render->rsNode_);
        const auto& groupProperty = render->GetOrCreateBackground();
        if (groupProperty->CheckBlurStyleOption(bgBlurStyle) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
            // Same with previous value.
            // If colorMode is following system and has valid blurStyle, still needs updating
            if (bgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
                return;
            }
            if (bgBlurStyle->blurOption.grayscale.size() > 1) {
                Rosen::Vector2f grayScale(bgBlurStyle->blurOption.grayscale[0], bgBlurStyle->blurOption.grayscale[1]);
                render->rsNode_->SetGreyCoef(grayScale);
            }
        } else {
            groupProperty->propBlurStyleOption = bgBlurStyle;
            groupProperty->propSysOptions = sysOptions;
        }
        if (!render->UpdateBlurBackgroundColor(bgBlurStyle)) {
            render->rsNode_->SetBackgroundFilter(nullptr);
            return;
        }
        render->SetBackBlurFilter();
    };
    updateFunc(resObj);
    pattern->AddResObj("backgroundBlurStyle.blurStyle", resObj, std::move(updateFunc));
}

void RosenRenderContext::UpdateBackBlurStyle(
    const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurStyleOption(bgBlurStyle) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (bgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
        if (bgBlurStyle->blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(bgBlurStyle->blurOption.grayscale[0], bgBlurStyle->blurOption.grayscale[1]);
            rsNode_->SetGreyCoef(grayScale);
        }
    } else {
        groupProperty->propBlurStyleOption = bgBlurStyle;
        groupProperty->propSysOptions = sysOptions;
    }
    if (SystemProperties::ConfigChangePerform()) {
        UpdateBlurStyleForColorMode(bgBlurStyle, sysOptions);
    }
    if (!UpdateBlurBackgroundColor(bgBlurStyle)) {
        rsNode_->SetBackgroundFilter(nullptr);
        return;
    }
    SetBackBlurFilter();
}

void RosenRenderContext::UpdateBackgroundEffect(
    const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckEffectOption(effectOption) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        return;
    }
    groupProperty->propEffectOption = effectOption;
    groupProperty->propSysOptions = sysOptions;
    if (!effectOption.has_value()) {
        return;
    }
    if (!UpdateBlurBackgroundColor(effectOption)) {
        rsNode_->SetBackgroundFilter(nullptr);
        return;
    }
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float radiusPx = context->NormalizeToPx(effectOption->radius);
    float backblurRadius = DrawingDecorationPainter::ConvertRadiusToSigma(radiusPx);
    auto fastAverage = Rosen::BLUR_COLOR_MODE::DEFAULT;
    if (effectOption->adaptiveColor == AdaptiveColor::AVERAGE) {
        fastAverage = Rosen::BLUR_COLOR_MODE::FASTAVERAGE;
    }
    std::shared_ptr<Rosen::RSFilter> backFilter =
        Rosen::RSFilter::CreateMaterialFilter(backblurRadius, static_cast<float>(effectOption->saturation),
            static_cast<float>(effectOption->brightness), effectOption->color.GetValue(),
            static_cast<Rosen::BLUR_COLOR_MODE>(fastAverage), sysOptions.disableSystemAdaptation);
    rsNode_->SetBackgroundFilter(backFilter);
    if (effectOption->blurOption.grayscale.size() > 1) {
        Rosen::Vector2f grayScale(effectOption->blurOption.grayscale[0], effectOption->blurOption.grayscale[1]);
        rsNode_->SetGreyCoef(grayScale);
    }
}

void RosenRenderContext::UpdateFrontBlurStyle(
    const std::optional<BlurStyleOption>& fgBlurStyle, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurStyleOption(fgBlurStyle) && groupProperty->CheckSysOptionsForBlurSame(sysOptions)) {
        // Same with previous value.
        // If colorMode is following system and has valid blurStyle, still needs updating
        if (fgBlurStyle->colorMode != ThemeColorMode::SYSTEM) {
            return;
        }
        if (fgBlurStyle->blurOption.grayscale.size() > 1) {
            Rosen::Vector2f grayScale(fgBlurStyle->blurOption.grayscale[0], fgBlurStyle->blurOption.grayscale[1]);
            rsNode_->SetGreyCoef(grayScale);
        }
    } else {
        groupProperty->propBlurStyleOption = fgBlurStyle;
        groupProperty->propSysOptionsForBlur = sysOptions;
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
        rsNode_->SetPixelStretch({ 0, 0, 0, 0 });
    } else {
        pixStretchVector.SetValues(static_cast<float>(option.left.ConvertToPx()),
            static_cast<float>(option.top.ConvertToPx()), static_cast<float>(option.right.ConvertToPx()),
            static_cast<float>(option.bottom.ConvertToPx()));
        rsNode_->SetPixelStretch(pixStretchVector);
        rsNode_->SetPixelStretchPercent({ 0, 0, 0, 0 });
    }
    RequestNextFrame();
}

void RosenRenderContext::OnLightUpEffectUpdate(double radio)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetLightUpEffectDegree(static_cast<float>(radio));
    RequestNextFrame();
}

void RosenRenderContext::OnParticleOptionArrayUpdate(const std::list<ParticleOption>& optionList)
{
    CHECK_NULL_VOID(rsNode_);
    RectF rect = GetPaintRectWithoutTransform();
    if (rect.IsEmpty()) {
        return;
    }
    if (NeedPreloadImage(optionList, rect)) {
        return;
    }
    auto pattern = GetHost()->GetPattern();
    auto particlePattern = AceType::DynamicCast<ParticlePattern>(pattern);
    if (particlePattern->HaveUnVisibleParent()) {
        return;
    }
    particleAnimationPlaying_ = true;
    std::vector<OHOS::Rosen::ParticleParams> particleParams;
    for (auto& item : optionList) {
        particleParams.emplace_back(ConvertParticleOptionToParams(item, rect));
    }
    auto finishCallback = [weak = WeakClaim(this)]() {
        auto renderContext = weak.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->particleAnimationPlaying_ = false;
    };
    rsNode_->SetParticleParams(particleParams, finishCallback);
    RequestNextFrame();
}

void RosenRenderContext::OnEmitterPropertyUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto particlePattern = AceType::DynamicCast<ParticlePattern>(pattern);
    CHECK_NULL_VOID(particlePattern);
    auto property = particlePattern->GetEmitterProperty();
    if (property.empty()) {
        return;
    }
    for (const auto& prop : property) {
        if (!prop.annulusRegion.has_value()) {
            continue;
        }
        const auto& annulusRegion = prop.annulusRegion.value();
        if (annulusRegion.center_.first.Unit() == DimensionUnit::PERCENT ||
            annulusRegion.center_.second.Unit() == DimensionUnit::PERCENT) {
            particlePattern->updateEmitterPosition(property);
            return;
        }
    }
}

void RosenRenderContext::OnClickEffectLevelUpdate(const ClickEffectInfo& info)
{
    if (HasClickEffectLevel()) {
        InitEventClickEffect();
    }
}

void RosenRenderContext::UpdateVisualEffect(const OHOS::Rosen::VisualEffect* visualEffect)
{
    CHECK_NULL_VOID(visualEffect);
    rsNode_->SetVisualEffect(visualEffect);
}

void RosenRenderContext::UpdateBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter)
{
    CHECK_NULL_VOID(backgroundFilter);
    rsNode_->SetUIBackgroundFilter(backgroundFilter);
}

void RosenRenderContext::UpdateForegroundFilter(const OHOS::Rosen::Filter* foregroundFilter)
{
    CHECK_NULL_VOID(foregroundFilter);
    rsNode_->SetUIForegroundFilter(foregroundFilter);
}

void RosenRenderContext::UpdateCompositingFilter(const OHOS::Rosen::Filter* compositingFilter)
{
    CHECK_NULL_VOID(compositingFilter);
    rsNode_->SetUICompositingFilter(compositingFilter);
}

bool RosenRenderContext::NeedPreloadImage(const std::list<ParticleOption>& optionList, RectF& rect)
{
    bool flag = false;
    std::vector<OHOS::Rosen::ParticleParams> particleParams;
    for (auto& item : optionList) {
        auto emitterOption = item.GetEmitterOption();
        auto particle = emitterOption.GetParticle();
        auto particleType = particle.GetParticleType();
        auto particleConfig = particle.GetConfig();
        if (particleType == ParticleType::IMAGE) {
            auto imageParameter = particleConfig.GetImageParticleParameter();
            auto imageSize = imageParameter.GetSize();
            auto imageWidth = Dimension(ConvertDimensionToPx(imageSize.first, rect.Width()), DimensionUnit::PX);
            auto imageHeight = Dimension(ConvertDimensionToPx(imageSize.second, rect.Height()), DimensionUnit::PX);
            auto canvasImageIter = particleImageMap_.find(imageParameter.GetImageSource());
            bool imageHasData = true;
            if (canvasImageIter->second) {
                imageHasData = canvasImageIter->second->HasData();
            }
            if (canvasImageIter == particleImageMap_.end() || !imageHasData) {
                LoadParticleImage(imageParameter.GetImageSource(), imageWidth, imageHeight);
                flag = true;
            }
        }
    }
    return flag;
}

Rosen::ParticleParams RosenRenderContext::ConvertParticleOptionToParams(
    const ParticleOption& particleOption, const RectF& rect)
{
    auto emitterOption = particleOption.GetEmitterOption();
    auto colorOptionOpt = particleOption.GetParticleColorOption();
    auto opacityOptionOpt = particleOption.GetParticleOpacityOption();
    auto scaleOptionOpt = particleOption.GetParticleScaleOption();
    auto velocityOptionOpt = particleOption.GetParticleVelocityOption();
    auto accelerationOpt = particleOption.GetParticleAccelerationOption();
    auto spinOptionOpt = particleOption.GetParticleSpinOption();
    auto rsEmitterConfig = ConvertParticleEmitterOption(emitterOption, rect);
    std::optional<OHOS::Rosen::ParticleColorParaType> rsColorOpt;
    std::optional<OHOS::Rosen::ParticleParaType<float>> rsSpinOpt;
    std::optional<OHOS::Rosen::ParticleVelocity> rsVelocityOpt;
    std::optional<OHOS::Rosen::ParticleParaType<float>> rsOpacityOpt;
    std::optional<OHOS::Rosen::ParticleParaType<float>> rsScaleOpt;
    std::optional<OHOS::Rosen::ParticleAcceleration> rsAccelerationOpt;
    if (colorOptionOpt.has_value()) {
        rsColorOpt = ConvertParticleColorOption(colorOptionOpt.value());
    } else {
        rsColorOpt = ConvertParticleDefaultColorOption(std::nullopt);
    }
    if (opacityOptionOpt.has_value()) {
        rsOpacityOpt = ConvertParticleFloatOption(opacityOptionOpt.value());
    } else {
        OHOS::Rosen::Range<float> rsInitRange(PARTICLE_DEFAULT_OPACITY, PARTICLE_DEFAULT_OPACITY);
        rsOpacityOpt = ConvertParticleDefaultFloatOption(rsInitRange);
    }
    if (scaleOptionOpt.has_value()) {
        rsScaleOpt = ConvertParticleFloatOption(scaleOptionOpt.value());
    } else {
        OHOS::Rosen::Range<float> rsInitRange(PARTICLE_DEFAULT_SCALE, PARTICLE_DEFAULT_SCALE);
        rsScaleOpt = ConvertParticleDefaultFloatOption(rsInitRange);
    }
    if (velocityOptionOpt.has_value()) {
        rsVelocityOpt = ConvertParticleVelocityOption(velocityOptionOpt.value());
    } else {
        rsVelocityOpt = ConvertParticleDefaultVelocityOption();
    }
    if (accelerationOpt.has_value()) {
        rsAccelerationOpt = ConvertParticleAccelerationOption(accelerationOpt.value());
    } else {
        rsAccelerationOpt = ConvertParticleDefaultAccelerationOption();
    }
    if (spinOptionOpt.has_value()) {
        rsSpinOpt = ConvertParticleFloatOption(spinOptionOpt.value());
    } else {
        OHOS::Rosen::Range<float> rsInitRange(PARTICLE_DEFAULT_SPIN, PARTICLE_DEFAULT_SPIN);
        rsSpinOpt = ConvertParticleDefaultFloatOption(rsInitRange);
    }
    return OHOS::Rosen::ParticleParams(rsEmitterConfig, rsVelocityOpt.value(), rsAccelerationOpt.value(),
        rsColorOpt.value(), rsOpacityOpt.value(), rsScaleOpt.value(), rsSpinOpt.value());
}

Rosen::EmitterConfig RosenRenderContext::ConvertParticleEmitterOption(
    const EmitterOption& emitterOption, const RectF& rect)
{
    auto emitterRateOpt = emitterOption.GetEmitterRate();
    auto pointOpt = emitterOption.GetPosition();
    auto sizeOpt = emitterOption.GetSize();
    auto shapeOpt = emitterOption.GetShape();
    auto particle = emitterOption.GetParticle();
    auto particleType = particle.GetParticleType();
    auto particleConfig = particle.GetConfig();
    auto particleCount = particle.GetCount();
    auto lifeTimeOpt = particle.GetLifeTime();
    auto lifeTimeRangeOpt = particle.GetLifeTimeRange();
    std::optional<int64_t> lifeTimeMin = 0;
    std::optional<int64_t> lifeTimeMax = lifeTimeOpt.value() + lifeTimeRangeOpt.value();
    if (lifeTimeOpt.value() == -1) {
        // when lifeTime == -1 particle life cycle is infinite
        lifeTimeMin = -1;
        lifeTimeMax = -1;
    } else if (lifeTimeOpt.value() - lifeTimeRangeOpt.value() > 0) {
        lifeTimeMin = lifeTimeOpt.value() - lifeTimeRangeOpt.value();
    }
    auto rsPoint = pointOpt.has_value()
                       ? OHOS::Rosen::Vector2f(ConvertDimensionToPx(pointOpt.value().first, rect.Width()),
                             ConvertDimensionToPx(pointOpt.value().second, rect.Height()))
                       : OHOS::Rosen::Vector2f(0.0f, 0.0f);
    auto rsSize = sizeOpt.has_value() ? OHOS::Rosen::Vector2f(ConvertDimensionToPx(sizeOpt.value().first, rect.Width()),
                                            ConvertDimensionToPx(sizeOpt.value().second, rect.Height()))
                                      : OHOS::Rosen::Vector2f(rect.Width(), rect.Height());
    auto shapeInt = static_cast<int32_t>(shapeOpt.value_or(ParticleEmitterShape::RECTANGLE));
    auto lifeTimeRange = OHOS::Rosen::Range<int64_t>(
        lifeTimeMin.value_or(PARTICLE_DEFAULT_LIFETIME), lifeTimeMax.value_or(PARTICLE_DEFAULT_LIFETIME));

    // The default value for the centerXY axis is 50 percent,
    // for the innerRadius or outerRadius is 0,
    // for the startAngle is 0, for the endAngle is 360.
    std::shared_ptr<Rosen::AnnulusRegion> rsAnnulusRegion = std::make_shared<Rosen::AnnulusRegion>(
        OHOS::Rosen::Vector2f(DEFAULT_CENTER_VALUE.ConvertToPxWithSize(rect.Width()),
        DEFAULT_CENTER_VALUE.ConvertToPxWithSize(rect.Height())),
        DEFAULT_RADIUS_VALUE, DEFAULT_RADIUS_VALUE, DEFAULT_START_ANGLE_VALUE, DEFAULT_END_ANGLE_VALUE);
    auto annulusRegionOpt = emitterOption.GetAnnulusRegion();
    if (annulusRegionOpt.has_value() && shapeInt == static_cast<int32_t>(ParticleEmitterShape::ANNULUS)) {
        auto annulusRegion = annulusRegionOpt.value();
        auto center = annulusRegion.center_;
        auto rsCenter = OHOS::Rosen::Vector2f(center.first.ConvertToPxWithSize(rect.Width()),
            center.second.ConvertToPxWithSize(rect.Height()));
        auto innerRadius = annulusRegion.innerRadius_;
        auto rsInnerRadius =
            (LessOrEqual(innerRadius.ConvertToPx(), 0.0) || innerRadius.Unit() == DimensionUnit::PERCENT)
            ? 0.0
            : innerRadius.ConvertToPx();
        auto outerRadius = annulusRegion.outerRadius_;
        auto rsOuterRadius =
            (LessOrEqual(outerRadius.ConvertToPx(), 0.0) || outerRadius.Unit() == DimensionUnit::PERCENT)
            ? 0.0
            : outerRadius.ConvertToPx();
        rsAnnulusRegion = std::make_shared<Rosen::AnnulusRegion>(rsCenter, rsInnerRadius,
            rsOuterRadius, annulusRegion.startAngle_, annulusRegion.endAngle_);
    }
    if (particleType == ParticleType::IMAGE) {
        auto imageParameter = particleConfig.GetImageParticleParameter();
        auto imageSource = imageParameter.GetImageSource();
        auto imageSize = imageParameter.GetSize();
        auto imageWidth = Dimension(ConvertDimensionToPx(imageSize.first, rect.Width()), DimensionUnit::PX);
        auto imageHeight = Dimension(ConvertDimensionToPx(imageSize.second, rect.Height()), DimensionUnit::PX);
        auto rsImagePtr = std::make_shared<Rosen::RSImage>();
        if (particleImageMap_.find(imageSource) != particleImageMap_.end()) {
            SetRsParticleImage(rsImagePtr, imageSource);
        }
        rsImagePtr->SetImageFit(static_cast<int32_t>(imageParameter.GetImageFit().value_or(ImageFit::COVER)));
        OHOS::Rosen::Vector2f rsImageSize(imageWidth.ConvertToPx(), imageHeight.ConvertToPx());
        auto emitterConfig =  OHOS::Rosen::EmitterConfig(emitterRateOpt.value_or(PARTICLE_DEFAULT_EMITTER_RATE),
            static_cast<OHOS::Rosen::ShapeType>(shapeInt), rsPoint, rsSize, particleCount, lifeTimeRange,
            OHOS::Rosen::ParticleType::IMAGES, 0.0f, rsImagePtr, rsImageSize);
        emitterConfig.SetConfigShape(rsAnnulusRegion);
        return emitterConfig;
    } else {
        auto pointParameter = particleConfig.GetPointParticleParameter();
        auto radius = pointParameter.GetRadius();
        auto emitterConfig =  OHOS::Rosen::EmitterConfig(emitterRateOpt.value_or(PARTICLE_DEFAULT_EMITTER_RATE),
            static_cast<OHOS::Rosen::ShapeType>(shapeInt), rsPoint, rsSize, particleCount, lifeTimeRange,
            OHOS::Rosen::ParticleType::POINTS, radius, std::make_shared<OHOS::Rosen::RSImage>(),
            OHOS::Rosen::Vector2f());
        emitterConfig.SetConfigShape(rsAnnulusRegion);
        return emitterConfig;
    }
}

void RosenRenderContext::SetRsParticleImage(std::shared_ptr<Rosen::RSImage>& rsImagePtr, std::string& imageSource)
{
    auto it = particleImageMap_.find(imageSource);
    if (it == particleImageMap_.end()) {
        return;
    }
    auto image = it->second;
    CHECK_NULL_VOID(image);

    if (InstanceOf<PixelMapImage>(image)) {
        auto pixmap = image->GetPixelMap();
        CHECK_NULL_VOID(pixmap);
        auto pixMapPtr = pixmap->GetPixelMapSharedPtr();
        rsImagePtr->SetPixelMap(pixMapPtr);
        if (pixMapPtr) {
            rsImagePtr->SetSrcRect(Rosen::RectF(0, 0, pixMapPtr->GetWidth(), pixMapPtr->GetHeight()));
        }
    } else if (InstanceOf<DrawingImage>(image)) {
        auto drawingImage = DynamicCast<DrawingImage>(image);
        CHECK_NULL_VOID(drawingImage);
        auto compressData = drawingImage->GetCompressData();
        if (compressData) {
            rsImagePtr->SetCompressData(compressData, drawingImage->GetUniqueID(), drawingImage->GetCompressWidth(),
                drawingImage->GetCompressHeight());
            rsImagePtr->SetSrcRect(
                Rosen::RectF(0, 0, drawingImage->GetCompressWidth(), drawingImage->GetCompressHeight()));
        } else {
            rsImagePtr->SetImage(drawingImage->GetImage());
            if (drawingImage->GetImage()) {
                rsImagePtr->SetSrcRect(
                    Rosen::RectF(0, 0, drawingImage->GetImage()->GetWidth(), drawingImage->GetImage()->GetHeight()));
            }
        }
        if (!HasValidBgImageResizable()) {
            rsImagePtr->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
        }
    }
}

void RosenRenderContext::LoadParticleImage(const std::string& src, Dimension& width, Dimension& height)
{
    if (particleImageContextMap_.find(src) != particleImageContextMap_.end()) {
        return;
    }
    ImageSourceInfo imageSourceInfo(src, width, height);
    imageSourceInfo.SetNeedCache(false);
    auto preLoadCallback = [weak = WeakClaim(this), imageSrc = src](const ImageSourceInfo& sourceInfo) {
        auto renderContent = weak.Upgrade();
        CHECK_NULL_VOID(renderContent);
        auto& imageContext = renderContent->particleImageContextMap_[imageSrc];
        CHECK_NULL_VOID(imageContext);
        imageContext->MakeCanvasImage(SizeF(), true, ImageFit::NONE);
    };
    auto loadingSuccessCallback = [weak = WeakClaim(this), imageSrc = src](const ImageSourceInfo& sourceInfo) {
        auto renderContent = weak.Upgrade();
        CHECK_NULL_VOID(renderContent);
        auto& imageContext = renderContent->particleImageContextMap_[imageSrc];
        CHECK_NULL_VOID(imageContext);
        auto imagePtr = imageContext->MoveCanvasImage();
        renderContent->OnParticleImageLoaded(imageSrc, imagePtr);
    };
    auto loadingErrorCallback = [weak = WeakClaim(this), imageSrc = src](const ImageSourceInfo& sourceInfo,
                                    const std::string& errorMsg, const ImageErrorInfo& /* errorInfo */) {
        auto renderContent = weak.Upgrade();
        CHECK_NULL_VOID(renderContent);
        renderContent->OnParticleImageLoaded(imageSrc, nullptr);
    };
    LoadNotifier loadNotifier(preLoadCallback, loadingSuccessCallback, loadingErrorCallback);
    auto particleImageLoadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(imageSourceInfo, std::move(loadNotifier));
    imageSourceInfo.SetSrc(src, Color(0x00000000));
    particleImageLoadingCtx->LoadImageData();
    particleImageContextMap_.try_emplace(src, particleImageLoadingCtx);
}

void RosenRenderContext::OnParticleImageLoaded(const std::string& src, RefPtr<CanvasImage> canvasImage)
{
    particleImageMap_.try_emplace(src, canvasImage);
    if (particleImageContextMap_.find(src) != particleImageContextMap_.end()) {
        particleImageContextMap_.erase(src);
    }
    if (particleImageContextMap_.empty() && propParticleOptionArray_.has_value()) {
        OnParticleOptionArrayUpdate(propParticleOptionArray_.value());
    }
}

float RosenRenderContext::ConvertDimensionToPx(Dimension& src, float size)
{
    if (src.Unit() == DimensionUnit::PERCENT) {
        return src.ConvertToPxWithSize(size);
    }
    return src.ConvertToPx();
}

Rosen::ParticleVelocity RosenRenderContext::ConvertParticleVelocityOption(const VelocityProperty& velocity)
{
    auto rsSpeedRange = OHOS::Rosen::Range<float>(velocity.GetSpeedRange().first, velocity.GetSpeedRange().second);
    auto rsAngleRange = OHOS::Rosen::Range<float>(velocity.GetAngleRange().first, velocity.GetAngleRange().second);
    return OHOS::Rosen::ParticleVelocity(rsSpeedRange, rsAngleRange);
}

Rosen::ParticleVelocity RosenRenderContext::ConvertParticleDefaultVelocityOption()
{
    auto rsSpeedRange = OHOS::Rosen::Range<float>(PARTICLE_DEFAULT_SPEED, PARTICLE_DEFAULT_SPEED);
    auto rsAngleRange = OHOS::Rosen::Range<float>(PARTICLE_DEFAULT_ANGLE, PARTICLE_DEFAULT_ANGLE);
    return OHOS::Rosen::ParticleVelocity(rsSpeedRange, rsAngleRange);
}

Rosen::ParticleAcceleration RosenRenderContext::ConvertParticleAccelerationOption(
    const AccelerationProperty& acceleration)
{
    auto speedOpt = acceleration.GetSpeed();
    auto angleOpt = acceleration.GetAngle();
    std::optional<OHOS::Rosen::ParticleParaType<float>> rsSpeedOpt;
    std::optional<OHOS::Rosen::ParticleParaType<float>> rsAngleOpt;
    OHOS::Rosen::Range<float> rsInitSpeedRange(PARTICLE_DEFAULT_SPEED, PARTICLE_DEFAULT_SPEED);
    if (speedOpt.has_value()) {
        rsSpeedOpt = ConvertParticleFloatOption(speedOpt.value());
    } else {
        rsSpeedOpt = ConvertParticleDefaultFloatOption(rsInitSpeedRange);
    }
    OHOS::Rosen::Range<float> rsInitAngleRange(PARTICLE_DEFAULT_ANGLE, PARTICLE_DEFAULT_ANGLE);
    if (angleOpt.has_value()) {
        rsAngleOpt = ConvertParticleFloatOption(angleOpt.value());
    } else {
        rsAngleOpt = ConvertParticleDefaultFloatOption(rsInitAngleRange);
    }
    return OHOS::Rosen::ParticleAcceleration(rsSpeedOpt.value(), rsAngleOpt.value());
}

Rosen::ParticleAcceleration RosenRenderContext::ConvertParticleDefaultAccelerationOption()
{
    OHOS::Rosen::Range<float> rsInitRange(PARTICLE_DEFAULT_SPEED, PARTICLE_DEFAULT_SPEED);
    return OHOS::Rosen::ParticleAcceleration(
        ConvertParticleDefaultFloatOption(rsInitRange), ConvertParticleDefaultFloatOption(rsInitRange));
}

Rosen::ParticleColorParaType RosenRenderContext::ConvertParticleColorOption(
    const ParticleColorPropertyOption& colorOption)
{
    auto initRange = colorOption.GetRange();
    auto colorDist = colorOption.GetDistribution();
    auto updaterOpt = colorOption.GetUpdater();
    OHOS::Rosen::Range<OHOS::Rosen::RSColor> rsInitRange(
        OHOS::Rosen::RSColor(initRange.first.GetRed(), initRange.first.GetGreen(), initRange.first.GetBlue(),
            initRange.first.GetAlpha()),
        OHOS::Rosen::RSColor(initRange.second.GetRed(), initRange.second.GetGreen(), initRange.second.GetBlue(),
            initRange.second.GetAlpha()));
    auto colorDistInt = static_cast<int32_t>(colorDist.value_or(DistributionType::UNIFORM));
    if (updaterOpt.has_value()) {
        auto updater = updaterOpt.value();
        auto updateType = updater.GetUpdateType();
        auto config = updater.GetConfig();
        if (updateType == UpdaterType::RANDOM) {
            auto randomConfig = config.GetRandomConfig();
            auto redRandom = randomConfig.GetRedRandom();
            auto greenRandom = randomConfig.GetGreenRandom();
            auto blueRandom = randomConfig.GetBlueRandom();
            auto alphaRandom = randomConfig.GetAlphaRandom();
            OHOS::Rosen::Range<float> rsRedRandom(redRandom.first, redRandom.second);
            OHOS::Rosen::Range<float> rsGreenRandom(greenRandom.first, greenRandom.second);
            OHOS::Rosen::Range<float> rsBlueRandom(blueRandom.first, blueRandom.second);
            OHOS::Rosen::Range<float> rsAlphaRandom(alphaRandom.first, alphaRandom.second);
            std::vector<OHOS::Rosen::Change<OHOS::Rosen::RSColor>> invalidCurve;
            return OHOS::Rosen::ParticleColorParaType(rsInitRange,
                static_cast<OHOS::Rosen::DistributionType>(colorDistInt), OHOS::Rosen::ParticleUpdator::RANDOM,
                rsRedRandom, rsGreenRandom, rsBlueRandom, rsAlphaRandom, invalidCurve);
        } else if (updateType == UpdaterType::CURVE) {
            auto& curveConfig = config.GetAnimationArray();
            std::vector<OHOS::Rosen::Change<OHOS::Rosen::RSColor>> valChangeOverLife;
            for (const auto& colorAnimationConfig : curveConfig) {
                auto fromColor = colorAnimationConfig.GetFrom();
                auto toColor = colorAnimationConfig.GetTo();
                auto startMills = colorAnimationConfig.GetStartMills();
                auto endMills = colorAnimationConfig.GetEndMills();
                auto curve = colorAnimationConfig.GetCurve();
                auto rsCurve = NativeCurveHelper::ToNativeCurve(curve);
                valChangeOverLife.emplace_back(OHOS::Rosen::Change<OHOS::Rosen::RSColor>(
                    OHOS::Rosen::RSColor(
                        fromColor.GetRed(), fromColor.GetGreen(), fromColor.GetBlue(), fromColor.GetAlpha()),
                    OHOS::Rosen::RSColor(toColor.GetRed(), toColor.GetGreen(), toColor.GetBlue(), toColor.GetAlpha()),
                    startMills, endMills, rsCurve));
            }
            return OHOS::Rosen::ParticleColorParaType(rsInitRange,
                static_cast<OHOS::Rosen::DistributionType>(colorDistInt), ParticleUpdator::CURVE,
                OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(),
                OHOS::Rosen::Range<float>(), valChangeOverLife);
        }
    }
    return ConvertParticleDefaultColorOption(rsInitRange);
}

Rosen::ParticleColorParaType RosenRenderContext::ConvertParticleDefaultColorOption(
    std::optional<OHOS::Rosen::Range<OHOS::Rosen::RSColor>> rsInitRangeOpt)
{
    std::vector<OHOS::Rosen::Change<OHOS::Rosen::RSColor>> invalidCurve;
    if (rsInitRangeOpt.has_value()) {
        return OHOS::Rosen::ParticleColorParaType(rsInitRangeOpt.value(), OHOS::Rosen::DistributionType::UNIFORM,
            OHOS::Rosen::ParticleUpdator::NONE, OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(),
            OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(), invalidCurve);
    }
    return OHOS::Rosen::ParticleColorParaType(
        OHOS::Rosen::Range<OHOS::Rosen::RSColor>(
            OHOS::Rosen::RSColor(PARTICLE_DEFAULT_COLOR), OHOS::Rosen::RSColor(PARTICLE_DEFAULT_COLOR)),
        OHOS::Rosen::DistributionType::UNIFORM, OHOS::Rosen::ParticleUpdator::NONE, OHOS::Rosen::Range<float>(),
        OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(), OHOS::Rosen::Range<float>(), invalidCurve);
}

Rosen::ParticleParaType<float> RosenRenderContext::ConvertParticleFloatOption(
    const ParticleFloatPropertyOption& floatOption)
{
    auto initRange = floatOption.GetRange();
    OHOS::Rosen::Range<float> rsInitRange(initRange.first, initRange.second);
    auto updaterOpt = floatOption.GetUpdater();
    if (updaterOpt.has_value()) {
        auto updater = updaterOpt.value();
        auto updateType = updater.GetUpdaterType();
        auto& config = updater.GetConfig();
        if (updateType == UpdaterType::RANDOM) {
            auto& randomRangeConfig = config.GetRandomConfig();
            std::vector<OHOS::Rosen::Change<float>> invalidChangeInOverLifeArray;
            return OHOS::Rosen::ParticleParaType<float>(rsInitRange, OHOS::Rosen::ParticleUpdator::RANDOM,
                OHOS::Rosen::Range<float>(randomRangeConfig.first, randomRangeConfig.second),
                invalidChangeInOverLifeArray);
        } else if (updateType == UpdaterType::CURVE) {
            auto curveConfig = config.GetAnimations();
            std::vector<OHOS::Rosen::Change<float>> valChangeOverLife;
            for (auto& animationConfig : curveConfig) {
                auto from = animationConfig.GetFrom();
                auto to = animationConfig.GetTo();
                auto startMills = animationConfig.GetStartMills();
                auto endMills = animationConfig.GetEndMills();
                auto rsCurve = NativeCurveHelper::ToNativeCurve(animationConfig.GetCurve());
                valChangeOverLife.emplace_back(OHOS::Rosen::Change<float>(from, to, startMills, endMills, rsCurve));
            }
            OHOS::Rosen::Range<float> rsInvalidRange;
            return OHOS::Rosen::ParticleParaType<float>(
                rsInitRange, OHOS::Rosen::ParticleUpdator::CURVE, rsInvalidRange, valChangeOverLife);
        }
    }
    return ConvertParticleDefaultFloatOption(rsInitRange);
}

Rosen::ParticleParaType<float> RosenRenderContext::ConvertParticleDefaultFloatOption(
    OHOS::Rosen::Range<float>& rsInitRange)
{
    std::vector<OHOS::Rosen::Change<float>> invalidChangeInOverLifeArray;
    return OHOS::Rosen::ParticleParaType<float>(
        rsInitRange, OHOS::Rosen::ParticleUpdator::NONE, OHOS::Rosen::Range<float>(), invalidChangeInOverLifeArray);
}

void RosenRenderContext::OnOpacityUpdate(double opacity)
{
    CHECK_NULL_VOID(rsNode_);
    if (AnimationUtils::IsImplicitAnimationOpen() && alphaUserModifier_ && GetHost()) {
        auto preOpacity = GetAnimatablePropertyStagingValue<Rosen::RSAlphaModifier, float>(alphaUserModifier_);
        if (!NearEqual(preOpacity, opacity)) {
            auto host = GetHost();
            ACE_SCOPED_TRACE(
                "opacity from %f to %f, id:%d, tag:%s", preOpacity, opacity, host->GetId(), host->GetTag().c_str());
        }
    }
    SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaUserModifier_, opacity);
    RequestNextFrame();
}

void RosenRenderContext::OnDynamicRangeModeUpdate(DynamicRangeMode dynamicRangeMode)
{
    auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
    CHECK_NULL_VOID(rsCanvasNode);
    if (dynamicRangeMode < DynamicRangeMode::STANDARD && !isHdr_) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "Set HDRPresent True.");
        isHdr_ = true;
        rsCanvasNode->SetHDRPresent(true);
    } else if (isHdr_) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "Set HDRPresent False.");
        isHdr_ = false;
        rsCanvasNode->SetHDRPresent(false);
    }
}

void RosenRenderContext::SetAlphaOffscreen(bool isOffScreen)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetAlphaOffscreen(isOffScreen);
}

class DrawDragThumbnailCallback : public SurfaceCaptureCallback {
public:
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        if (pixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
            g_pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
#endif // PIXEL_MAP_SUPPORTED
        } else {
            g_pixelMap = nullptr;
            TAG_LOGE(AceLogTag::ACE_DRAG, "get thumbnail pixelMap failed!");
        }
        if (callback_ == nullptr) {
            std::unique_lock<std::mutex> lock(g_mutex);
            thumbnailGet.notify_all();
            return;
        }
        callback_(g_pixelMap);
    }

    std::function<void(const RefPtr<PixelMap>&)> callback_;
};

RefPtr<PixelMap> RosenRenderContext::GetThumbnailPixelMap(bool needScale, bool isOffline)
{
    CHECK_NULL_RETURN(rsNode_, nullptr);
    std::shared_ptr<DrawDragThumbnailCallback> drawDragThumbnailCallback =
        std::make_shared<DrawDragThumbnailCallback>();
    CHECK_NULL_RETURN(drawDragThumbnailCallback, nullptr);
    drawDragThumbnailCallback->callback_ = nullptr;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    if (needScale) {
        UpdateThumbnailPixelMapScale(scaleX, scaleY);
    }
    AddRsNodeForCapture();
    auto ret = RSInterfaces::GetInstance().TakeSurfaceCaptureForUI(rsNode_, drawDragThumbnailCallback, scaleX, scaleY,
        isOffline);
    if (!ret) {
        LOGE("TakeSurfaceCaptureForUI failed!");
        return nullptr;
    }
    std::unique_lock<std::mutex> lock(g_mutex);
    if (thumbnailGet.wait_for(lock, PIXELMAP_TIMEOUT_DURATION) == std::cv_status::timeout) {
        LOGE("get thumbnail pixelMap timeout!");
        return nullptr;
    }
    return g_pixelMap;
}

bool RosenRenderContext::CreateThumbnailPixelMapAsyncTask(
    bool needScale, std::function<void(const RefPtr<PixelMap>)>&& callback)
{
    CHECK_NULL_RETURN(rsNode_, false);
    std::shared_ptr<DrawDragThumbnailCallback> thumbnailCallback = std::make_shared<DrawDragThumbnailCallback>();
    CHECK_NULL_RETURN(thumbnailCallback, false);
    thumbnailCallback->callback_ = std::move(callback);
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    if (needScale) {
        UpdateThumbnailPixelMapScale(scaleX, scaleY);
    }
    AddRsNodeForCapture();
    return RSInterfaces::GetInstance().TakeSurfaceCaptureForUI(rsNode_, thumbnailCallback, scaleX, scaleY, true);
}

void RosenRenderContext::UpdateThumbnailPixelMapScale(float& scaleX, float& scaleY)
{
    CHECK_NULL_VOID(rsNode_);
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto parent = frameNode->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(parentRenderContext);
        auto parentScale = parentRenderContext->GetTransformScale();
        if (parentScale) {
            scale[0] *= parentScale.value().x;
            scale[1] *= parentScale.value().y;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    scaleX = scale[0];
    scaleY = scale[1];
}

bool RosenRenderContext::GetBitmap(RSBitmap& bitmap, std::shared_ptr<RSDrawCmdList> drawCmdList)
{
#ifdef ACE_ENABLE_HYBRID_RENDER
    if (RSSystemProperties::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::CANVAS)) {
        auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
        if (!rsCanvasNode || !rsCanvasNode->IsHybridRenderCanvas()) {
            return false;
        }
        return rsCanvasNode->GetBitmap(bitmap, drawCmdList);
    }
#endif
    auto rsCanvasDrawingNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasDrawingNode>(rsNode_);
    if (!rsCanvasDrawingNode) {
        return false;
    }
    return rsCanvasDrawingNode->GetBitmap(bitmap, drawCmdList);
}

bool RosenRenderContext::GetPixelMap(const std::shared_ptr<Media::PixelMap>& pixelMap,
    std::shared_ptr<RSDrawCmdList> drawCmdList, Rosen::Drawing::Rect* rect)
{
#ifdef ACE_ENABLE_HYBRID_RENDER
    if (RSSystemProperties::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::CANVAS)) {
        auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
        if (!rsCanvasNode || !rsCanvasNode->IsHybridRenderCanvas()) {
            return false;
        }
        return rsCanvasNode->GetPixelmap(pixelMap, drawCmdList, rect);
    }
#endif
    auto rsCanvasDrawingNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasDrawingNode>(rsNode_);
    if (!rsCanvasDrawingNode) {
        return false;
    }
    return rsCanvasDrawingNode->GetPixelmap(pixelMap, drawCmdList, rect);
}

template<typename ModifierName, typename T>
void RosenRenderContext::SetAnimatableProperty(std::shared_ptr<ModifierName>& modifier, const T& value)
{
    if (modifier) {
        auto property = std::static_pointer_cast<Rosen::RSAnimatableProperty<T>>(modifier->GetProperty());
        CHECK_NULL_VOID(property);
        property->Set(value);
    } else {
        auto property = std::make_shared<Rosen::RSAnimatableProperty<T>>(value);
        modifier = std::make_shared<ModifierName>(property);
        rsNode_->AddModifier(modifier);
    }
}

void RosenRenderContext::OnTransformScaleUpdate(const VectorF& scale)
{
    CHECK_NULL_VOID(rsNode_);
    auto curScale = rsNode_->GetStagingProperties().GetScale();
    hasScales_ = !NearEqual(curScale, Vector2f(1.0f, 1.0f)) && !NearEqual(scale, VectorF(1.0f, 1.0f));
    if (AnimationUtils::IsImplicitAnimationOpen() && scaleXYUserModifier_ && GetHost()) {
        auto preScale =
            GetAnimatablePropertyStagingValue<Rosen::RSScaleModifier, Rosen::Vector2f>(scaleXYUserModifier_);
        if (!(NearEqual(preScale[0], scale.x) && NearEqual(preScale[1], scale.y))) {
            auto host = GetHost();
            ACE_SCOPED_TRACE("scale from (%f, %f) to (%f, %f), id:%d, tag:%s", preScale[0], preScale[1], scale.x,
                scale.y, host->GetId(), host->GetTag().c_str());
        }
    }
    SetAnimatableProperty<Rosen::RSScaleModifier, Rosen::Vector2f>(scaleXYUserModifier_, { scale.x, scale.y });
    NotifyHostTransformUpdated();
    RequestNextFrame();
}

Vector3F RosenRenderContext::MarshallTranslate(const TranslateOptions& translate)
{
    float xValue = 0.0f;
    float yValue = 0.0f;
    if (translate.x.Unit() == DimensionUnit::PERCENT || translate.y.Unit() == DimensionUnit::PERCENT) {
        auto rect = GetPaintRectWithoutTransform();
        if (rect.IsEmpty()) {
            // size is not determined yet
            return Vector3F();
        }
        xValue = translate.x.ConvertToPxWithSize(rect.Width());
        yValue = translate.y.ConvertToPxWithSize(rect.Height());
    } else {
        xValue = translate.x.ConvertToPx();
        yValue = translate.y.ConvertToPx();
    }
    // translateZ doesn't support percentage
    float zValue = translate.z.ConvertToPx();
    return Vector3F(xValue, yValue, zValue);
}

void RosenRenderContext::OnTransformTranslateUpdate(const TranslateOptions& translate)
{
    CHECK_NULL_VOID(rsNode_);
    auto translateVec = MarshallTranslate(translate);
    auto changed = true;
    Rosen::Vector2f preTranslate;
    if (translateXYUserModifier_) {
        preTranslate =
            GetAnimatablePropertyStagingValue<Rosen::RSTranslateModifier, Rosen::Vector2f>(translateXYUserModifier_);
        changed = !NearEqual(preTranslate[0], translateVec.x) || !NearEqual(preTranslate[1], translateVec.y);
    }
    if (AnimationUtils::IsImplicitAnimationOpen() && translateXYUserModifier_ && GetHost()) {
        if (!(NearEqual(preTranslate[0], translateVec.x) && NearEqual(preTranslate[1], translateVec.y))) {
            auto host = GetHost();
            ACE_SCOPED_TRACE("translate from (%f, %f) to (%f, %f), id:%d, tag:%s", preTranslate[0], preTranslate[1],
                translateVec.x, translateVec.y, host->GetId(), host->GetTag().c_str());
        }
    }
    SetAnimatableProperty<Rosen::RSTranslateModifier, Rosen::Vector2f>(
        translateXYUserModifier_, { translateVec.x, translateVec.y });
    SetAnimatableProperty<Rosen::RSTranslateZModifier, float>(translateZUserModifier_, translateVec.z);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost());
    NotifyHostTransformUpdated(changed);
    RequestNextFrame();
}

void RosenRenderContext::OnTransformRotateUpdate(const Vector5F& rotate)
{
    CHECK_NULL_VOID(rsNode_);
    float norm = std::sqrt(std::pow(rotate.x, 2) + std::pow(rotate.y, 2) + std::pow(rotate.z, 2));
    if (NearZero(norm)) {
        norm = 1.0f;
    }
    SetAnimatableProperty<Rosen::RSRotationXModifier, float>(rotationXUserModifier_, -rotate.w * rotate.x / norm);
    SetAnimatableProperty<Rosen::RSRotationYModifier, float>(rotationYUserModifier_, -rotate.w * rotate.y / norm);
    SetAnimatableProperty<Rosen::RSRotationModifier, float>(rotationZUserModifier_, rotate.w * rotate.z / norm);
    SetAnimatableProperty<Rosen::RSCameraDistanceModifier, float>(cameraDistanceUserModifier_, rotate.v);
    NotifyHostTransformUpdated();
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
        NotifyHostTransformUpdated();
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
        Rosen::Vector4f perspectiveValue { transform.perspective[0], transform.perspective[1], 0.0f,
            1.0f };
        Rosen::Vector2f xyTranslateValue { transform.translate[0], transform.translate[1] };
        Rosen::Quaternion quaternion { static_cast<float>(transform.quaternion.GetX()),
            static_cast<float>(transform.quaternion.GetY()), static_cast<float>(transform.quaternion.GetZ()),
            static_cast<float>(transform.quaternion.GetW()) };
        Rosen::Vector2f xyScaleValue { transform.scale[0], transform.scale[1] };
        Rosen::Vector3f skewValue { transform.skew[0], transform.skew[1], 0.0f };

        AddOrChangePerspectiveModifier(rsNode_, transformMatrixModifier_->perspective,
            transformMatrixModifier_->perspectiveValue, perspectiveValue);
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, xyScaleValue);
        AddOrChangeSkewModifier(
            rsNode_, transformMatrixModifier_->skew, transformMatrixModifier_->skewValue, skewValue);
        AddOrChangeQuaternionModifier(
            rsNode_, transformMatrixModifier_->quaternion, transformMatrixModifier_->quaternionValue, quaternion);
    }
    NotifyHostTransformUpdated();
    RequestNextFrame();
}

void RosenRenderContext::OnTransform3DMatrixUpdate(const Matrix4& matrix)
{
    CHECK_NULL_VOID(rsNode_);
    if (!transformMatrixModifier_.has_value()) {
        transformMatrixModifier_ = TransformMatrixModifier();
    }
    DecomposedTransform transform;
    if (!TransformUtil::DecomposeTransform(transform, matrix)) {
        // fallback to basic matrix decompose
        Rosen::Vector2f xyTranslateValue { static_cast<float>(matrix.Get(INDEX_0, INDEX_3)),
            static_cast<float>(matrix.Get(INDEX_1, INDEX_3)) };
        Rosen::Vector2f scaleValue { FLOAT_ZERO, FLOAT_ZERO };
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, scaleValue);
    } else {
        Rosen::Vector4f perspectiveValue { transform.perspective[0], transform.perspective[1],
            transform.perspective[INDEX_2], transform.perspective[INDEX_3] };
        Rosen::Vector2f xyTranslateValue { transform.translate[0], transform.translate[1] };
        Rosen::Quaternion quaternion { static_cast<float>(transform.quaternion.GetX()),
            static_cast<float>(transform.quaternion.GetY()), static_cast<float>(transform.quaternion.GetZ()),
            static_cast<float>(transform.quaternion.GetW()) };
        Rosen::Vector2f xyScaleValue { transform.scale[0], transform.scale[1] };
        Rosen::Vector3f skewValue { transform.skew[0], transform.skew[1], transform.skew[INDEX_2] };

        AddOrChangePerspectiveModifier(rsNode_, transformMatrixModifier_->perspective,
            transformMatrixModifier_->perspectiveValue, perspectiveValue);
        AddOrChangeTranslateModifier(rsNode_, transformMatrixModifier_->translateXY,
            transformMatrixModifier_->translateXYValue, xyTranslateValue);
        AddOrChangeTranslateZModifier(rsNode_, transformMatrixModifier_->translateZ,
            transformMatrixModifier_->translateZValue, transform.translate[INDEX_2]);
        AddOrChangeScaleModifier(
            rsNode_, transformMatrixModifier_->scaleXY, transformMatrixModifier_->scaleXYValue, xyScaleValue);
        AddOrChangeScaleZModifier(
            rsNode_, transformMatrixModifier_->scaleZ, transformMatrixModifier_->scaleZValue, transform.scale[INDEX_2]);
        AddOrChangeSkewModifier(
            rsNode_, transformMatrixModifier_->skew, transformMatrixModifier_->skewValue, skewValue);
        AddOrChangeQuaternionModifier(
            rsNode_, transformMatrixModifier_->quaternion, transformMatrixModifier_->quaternionValue, quaternion);
    }
    NotifyHostTransformUpdated();
    RequestNextFrame();
}

RectF gRect;

double Degree2Radian(int32_t degree)
{
    const float pi = 3.14159265;
    degree = degree % FULL_ROTATION;
    if (degree < 0) {
        degree += FULL_ROTATION;
    }
    return degree * pi / STRAIGHT_ANGLE;
}

void SetCorner(double& x, double& y, double width, double height, int32_t degree)
{
    if (degree == RIGHT_ANGLE) {
        x = 0;
        y = height;
    } else if (degree == STRAIGHT_ANGLE) {
        x = width;
        y = height;
    } else if (degree == REFLEX_ANGLE) {
        x = width;
        y = 0;
    }
}

void SkewRect(float sx, float sy, RectF& rect)
{
    auto left = rect.Left();
    auto right = rect.Right();
    auto top = rect.Top();
    auto bottom = rect.Bottom();

    auto leftAfterSkew = sx > 0 ? left + sx * top : left + sx * bottom;
    auto rightAfterSkew = sx > 0 ? right + sx * bottom : right + sx * top;
    auto topAfterSkew = sy > 0 ? top + sy * left : top + sy * right;
    auto bottomAfterSkew = sy > 0 ? bottom + sy * right : bottom + sy * left;

    rect.SetLeft(leftAfterSkew);
    rect.SetWidth(rightAfterSkew - leftAfterSkew);
    rect.SetTop(topAfterSkew);
    rect.SetHeight(bottomAfterSkew - topAfterSkew);
}

void PerspectiveRect(float px, float py, RectF& rect)
{
    auto left = rect.Left();
    auto right = rect.Right();
    auto top = rect.Top();
    auto bottom = rect.Bottom();

    auto leftAfterSkew = Infinity<double>();
    auto rightAfterSkew = -Infinity<double>();
    auto topAfterSkew = Infinity<double>();
    auto bottomAfterSkew = -Infinity<double>();

    double xValues[] = { left, right };
    double yValues[] = { top, bottom };

    for (uint32_t i = 0; i < 2; i++) {
        for (uint32_t j = 0; j < 2; j++) {
            double perspectiveValue = px * xValues[i] + py * yValues[j] + 1;
            if (NearZero(perspectiveValue)) {
                return;
            }
            leftAfterSkew = std::min(leftAfterSkew, xValues[i] / perspectiveValue);
            rightAfterSkew = std::max(rightAfterSkew, xValues[i] / perspectiveValue);
            topAfterSkew = std::min(topAfterSkew, yValues[i] / perspectiveValue);
            bottomAfterSkew = std::max(bottomAfterSkew, yValues[i] / perspectiveValue);
        }
    }

    rect.SetLeft(leftAfterSkew);
    rect.SetWidth(rightAfterSkew - leftAfterSkew);
    rect.SetTop(topAfterSkew);
    rect.SetHeight(bottomAfterSkew - topAfterSkew);
}

void SkewPoint(float sx, float sy, PointF& point)
{
    auto x = point.GetX();
    auto y = point.GetY();

    point.SetX(x + y * sx);
    point.SetY(y + x * sy);
}

RectF RosenRenderContext::GetPaintRectWithTransform()
{
    RectF rect;

    CHECK_NULL_RETURN(rsNode_, rect);
    rect = GetPaintRectWithoutTransform();
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto perspective = rsNode_->GetStagingProperties().GetPersp();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto center = rsNode_->GetStagingProperties().GetPivot();
    auto degree = rsNode_->GetStagingProperties().GetRotation();
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
    // calculate skew
    SkewRect(skew[0], skew[1], rect);
    // calculate rotate
    degree = static_cast<int32_t>(degree) % FULL_ROTATION;
    auto radian = Degree2Radian(degree);
    if (degree != 0) {
        auto newRect = GetPaintRectWithoutTransform();
        double leftX = 0.0;
        double leftY = 0.0;
        degree = degree < 0 ? degree + FULL_ROTATION : degree;
        SetCorner(leftX, leftY, oldSize.Width(), oldSize.Height(), degree);
        double centerX = oldSize.Width() * center[0];
        double centerY = oldSize.Height() * center[1];
        auto tmp = leftX;
        leftX = (leftX - centerX) * cos(-1 * radian) + (leftY - centerY) * sin(-1 * radian);
        leftY = -1 * (tmp - centerX) * sin(-1 * radian) + (leftY - centerY) * cos(-1 * radian);
        leftX += newRect.GetOffset().GetX() + centerX;
        leftY += newRect.GetOffset().GetY() + centerY;
        auto offset = OffsetF(leftX + translate[0], leftY + translate[1]);
        rect.SetOffset(offset);
        if (degree == STRAIGHT_ANGLE) {
            newSize = SizeF(oldSize.Width() * scale[0], oldSize.Height() * scale[1]);
        } else {
            newSize = SizeF(oldSize.Height() * scale[1], oldSize.Width() * scale[0]);
        }
        rect.SetSize(newSize);

        // calculate perspective
        PerspectiveRect(perspective[0], perspective[1], rect);
    }
    gRect = rect;
    return rect;
}

std::pair<RectF, bool> RosenRenderContext::GetPaintRectWithTranslate()
{
    RectF rect;
    bool error = hasScales_;
    CHECK_NULL_RETURN(rsNode_, std::make_pair(rect, error));
    if (rsNode_->GetStagingProperties().GetRotation()) {
        return std::make_pair(RectF(0, 0, -1, -1), error);
    }
    rect = GetPaintRectWithoutTransform();
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    rect.SetOffset(rect.GetOffset() + OffsetF(translate[0], translate[1]));
    return std::make_pair(rect, error);
}

Matrix4 RosenRenderContext::GetRevertMatrix()
{
    CHECK_NULL_RETURN(rsNode_, {});
    auto center = rsNode_->GetStagingProperties().GetPivot();
    Matrix4 rotateMat;
    if (transformMatrixModifier_ && !transformMatrixModifier_->quaternionValue->GetStagingValue().IsIdentity()) {
        auto quaternionValue = transformMatrixModifier_->quaternionValue->GetStagingValue();
        // 2: parameter index, 3: parameter index
        rotateMat =
            Matrix4::QuaternionToMatrix(quaternionValue[0], quaternionValue[1], quaternionValue[2], quaternionValue[3]);
    } else {
        int32_t degree = rsNode_->GetStagingProperties().GetRotation();
        if (rsNode_->GetType() == RSUINodeType::DISPLAY_NODE && degree != 0) {
            degree = 0;
            return Matrix4();
        }
        rotateMat = Matrix4::CreateRotate(degree, 0, 0, 1);
    }

    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto perspective = rsNode_->GetStagingProperties().GetPersp();

    RectF rect = GetPaintRectWithoutTransform();
    auto centOffset = OffsetF(center[0] * rect.Width(), center[1] * rect.Height());
    auto centerPos = rect.GetOffset() + centOffset;

    auto perspectiveMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                          Matrix4::CreateFactorPerspective(perspective[0], perspective[1]) *
                          Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto translateMat = Matrix4::CreateTranslate(translate[0], translate[1], 0);
    auto rotationMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) * rotateMat *
                       Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto skewMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                   Matrix4::CreateFactorSkew(skew[0], skew[1]) *
                   Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto scaleMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                    Matrix4::CreateScale(scale[0], scale[1], 1) *
                    Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);

    return Matrix4::Invert(perspectiveMat * translateMat * rotationMat * skewMat * scaleMat);
}

Matrix4 RosenRenderContext::GetMatrix()
{
    CHECK_NULL_RETURN(rsNode_, {});
    auto center = rsNode_->GetStagingProperties().GetPivot();
    int32_t degree = rsNode_->GetStagingProperties().GetRotation();
    if (rsNode_->GetType() == RSUINodeType::DISPLAY_NODE && degree != 0) {
        degree = 0;
        return Matrix4();
    }

    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto scale = rsNode_->GetStagingProperties().GetScale();

    RectF rect = GetPaintRectWithoutTransform();
    auto centOffset = OffsetF(center[0] * rect.Width(), center[1] * rect.Height());
    auto centerPos = rect.GetOffset() + centOffset;

    auto translateMat = Matrix4::CreateTranslate(translate[0], translate[1], 0);
    auto rotationMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                       Matrix4::CreateRotate(degree, 0, 0, 1) *
                       Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto skewMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                   Matrix4::CreateFactorSkew(skew[0], skew[1]) *
                   Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto scaleMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                    Matrix4::CreateScale(scale[0], scale[1], 1) *
                    Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);

    return translateMat * rotationMat * skewMat * scaleMat;
}

// only for GetPositionToXXXWithTransform in FrameNode.
// contains rotate and perspective matrix set by tranform.
Matrix4 RosenRenderContext::GetMatrixWithTransformRotate()
{
    CHECK_NULL_RETURN(rsNode_, {});
    auto center = rsNode_->GetStagingProperties().GetPivot();

    Matrix4 rotateMat;
    if (transformMatrixModifier_ && !transformMatrixModifier_->quaternionValue->GetStagingValue().IsIdentity()) {
        auto quaternionValue = transformMatrixModifier_->quaternionValue->GetStagingValue();
        // 2: parameter index, 3: parameter index
        rotateMat =
            Matrix4::QuaternionToMatrix(quaternionValue[0], quaternionValue[1], quaternionValue[2], quaternionValue[3]);
    } else {
        int32_t degree = rsNode_->GetStagingProperties().GetRotation();
        if (rsNode_->GetType() == RSUINodeType::DISPLAY_NODE && degree != 0) {
            degree = 0;
            return Matrix4();
        }
        rotateMat = Matrix4::CreateRotate(degree, 0, 0, 1);
    }

    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto perspective = rsNode_->GetStagingProperties().GetPersp();

    RectF rect = GetPaintRectWithoutTransform();
    auto centOffset = OffsetF(center[0] * rect.Width(), center[1] * rect.Height());
    auto centerPos = rect.GetOffset() + centOffset;

    auto perspectiveMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                          Matrix4::CreateFactorPerspective(perspective[0], perspective[1]) *
                          Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto translateMat = Matrix4::CreateTranslate(translate[0], translate[1], 0);
    auto rotationMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) * rotateMat *
                       Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto skewMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                   Matrix4::CreateFactorSkew(skew[0], skew[1]) *
                   Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);
    auto scaleMat = Matrix4::CreateTranslate(centerPos.GetX(), centerPos.GetY(), 0) *
                    Matrix4::CreateScale(scale[0], scale[1], 1) *
                    Matrix4::CreateTranslate(-centerPos.GetX(), -centerPos.GetY(), 0);

    return perspectiveMat * translateMat * rotationMat * skewMat * scaleMat;
}

Matrix4 RosenRenderContext::GetLocalTransformMatrix()
{
    auto invertMat = GetRevertMatrix();
    RectF rect = GetPaintRectWithoutTransform();
    auto transformMat = Matrix4::CreateTranslate(-rect.GetOffset().GetX(), -rect.GetOffset().GetY(), 0) * invertMat;
    return transformMat;
}

void RosenRenderContext::GetPointWithRevert(PointF& point)
{
    auto invertMat = GetRevertMatrix();
    Point tmp(point.GetX(), point.GetY());
    auto invertPoint = invertMat * tmp;
    point.SetX(invertPoint.GetX());
    point.SetY(invertPoint.GetY());
}

void RosenRenderContext::GetPointTransform(PointF& point)
{
    auto transformMat = GetMatrix();
    Point tmp(point.GetX(), point.GetY());
    auto transformPoint = transformMat * tmp;
    point.SetX(transformPoint.GetX());
    point.SetY(transformPoint.GetY());
}

// only for GetPositionToXXXWithTransform in FrameNode
void RosenRenderContext::GetPointTransformRotate(PointF& point)
{
    auto transformMat = GetMatrixWithTransformRotate();
    Point tmp(point.GetX(), point.GetY());
    auto transformPoint = transformMat * tmp;
    point.SetX(transformPoint.GetX());
    point.SetY(transformPoint.GetY());
}

void RosenRenderContext::GetPointWithTransform(PointF& point)
{
    CHECK_NULL_VOID(rsNode_);
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    point = PointF(point.GetX() / scale[0], point.GetY() / scale[1]);
    SkewPoint(skew[0], skew[1], point);
    int32_t degree = rsNode_->GetStagingProperties().GetRotation();
    if (degree != 0 && rsNode_->GetType() == RSUINodeType::DISPLAY_NODE) {
        degree = 0;
    }
    degree = degree % FULL_ROTATION;
    if (degree != 0) {
        auto translate = rsNode_->GetStagingProperties().GetTranslate();
        auto perspective = rsNode_->GetStagingProperties().GetPersp();
        RectF rect = GetPaintRectWithoutTransform();
        auto center = rsNode_->GetStagingProperties().GetPivot();
        auto radian = Degree2Radian(degree);
        point = point + gRect.GetOffset();
        point = point - OffsetF(translate[0], translate[1]);
        auto centOffset = OffsetF(center[0] * gRect.Width(), center[1] * gRect.Height());
        auto centerPos = gRect.GetOffset() + centOffset - OffsetF(translate[0], translate[1]);
        auto centerX = centerPos.GetX();
        auto centerY = centerPos.GetY();

        double currentPointX = (point.GetX() - centerX) * cos(radian) + (point.GetY() - centerY) * sin(radian);
        double currentPointY = -1 * (point.GetX() - centerX) * sin(radian) + (point.GetY() - centerY) * cos(radian);
        currentPointX += centerX - rect.Left();
        currentPointY += centerY - rect.Top();

        double perspectiveValue = perspective[0] * currentPointX + perspective[1] * currentPointY + 1;
        if (NearZero(perspectiveValue)) {
            point.SetX(currentPointX);
            point.SetY(currentPointY);
            return;
        }

        point.SetX(currentPointX / perspectiveValue);
        point.SetY(currentPointY / perspectiveValue);
    }
}

// comparing to frameRect of geometryNode,
// paint rect has position, offset, markAnchor, pixelGridRound and safeArea properties
RectF RosenRenderContext::GetPaintRectWithoutTransform()
{
    return paintRect_;
}

RectF RosenRenderContext::GetPaintRectWithTransformWithoutDegree()
{
    RectF rect;
    CHECK_NULL_RETURN(rsNode_, rect);
    rect = GetPaintRectWithoutTransform();
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    auto skew = rsNode_->GetStagingProperties().GetSkew();
    auto perspective = rsNode_->GetStagingProperties().GetPersp();
    auto scale = rsNode_->GetStagingProperties().GetScale();
    auto center = rsNode_->GetStagingProperties().GetPivot();
    auto degree = 0;
    auto centOffset = OffsetF(center[0] * rect.Width(), center[1] * rect.Height());
    auto centerPos = rect.GetOffset() + centOffset;
    auto newPos = centerPos - OffsetF(centOffset.GetX() * scale[0], centOffset.GetY() * scale[1]);
    newPos = newPos + OffsetF(translate[0], translate[1]);
    rect.SetOffset(newPos);
    auto oldSize = rect.GetSize();
    auto newSize = SizeF(oldSize.Width() * scale[0], oldSize.Height() * scale[1]);
    rect.SetSize(newSize);
    SkewRect(skew[0], skew[1], rect);
    degree = static_cast<int32_t>(degree) % FULL_ROTATION;
    auto radian = Degree2Radian(degree);
    if (degree != 0) {
        auto newRect = GetPaintRectWithoutTransform();
        double leftX = 0;
        double leftY = oldSize.Height();
        degree = degree < 0 ? degree + FULL_ROTATION : degree;
        SetCorner(leftX, leftY, oldSize.Width(), oldSize.Height(), degree);
        double centerX = oldSize.Width() * center[0];
        double centerY = oldSize.Height() * center[1];
        auto tmp = leftX;
        leftX = (leftX - centerX) * cos(-1 * radian) + (leftY - centerY) * sin(-1 * radian);
        leftY = -1 * (tmp - centerX) * sin(-1 * radian) + (leftY - centerY) * cos(-1 * radian);
        leftX += newRect.GetOffset().GetX() + centerX;
        leftY += newRect.GetOffset().GetY() + centerY;
        auto offset = OffsetF(leftX + translate[0], leftY + translate[1]);
        rect.SetOffset(offset);
        if (degree == STRAIGHT_ANGLE) {
            newSize = SizeF(oldSize.Width() * scale[0], oldSize.Height() * scale[1]);
        } else {
            newSize = SizeF(oldSize.Height() * scale[1], oldSize.Width() * scale[0]);
        }
        rect.SetSize(newSize);
        PerspectiveRect(perspective[0], perspective[1], rect);
    }
    gRect = rect;
    return rect;
}

void RosenRenderContext::UpdateTranslateInXY(const OffsetF& offset)
{
    CHECK_NULL_VOID(rsNode_);
    auto xValue = offset.GetX();
    auto yValue = offset.GetY();
    bool changed = true;
    if (translateXY_) {
        auto propertyXY = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
        if (propertyXY) {
            auto translate = propertyXY->Get();
            changed = !NearEqual(translate[0], xValue) || !NearEqual(translate[1], yValue);
            propertyXY->Set({ xValue, yValue });
        }
    } else {
        auto propertyXY = std::make_shared<RSAnimatableProperty<Vector2f>>(Vector2f(xValue, yValue));
        translateXY_ = std::make_shared<Rosen::RSTranslateModifier>(propertyXY);
        rsNode_->AddModifier(translateXY_);
    }
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost());
    NotifyHostTransformUpdated(changed);
}

OffsetF RosenRenderContext::GetShowingTranslateProperty()
{
    OffsetF offset;
    CHECK_NULL_RETURN(translateXY_, offset);
    auto property = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
    CHECK_NULL_RETURN(property, offset);
    auto result = property->GetShowingValueAndCancelAnimation();
    if (!result) {
        return offset;
    }
    auto translate = property->Get();
    offset.SetX(translate[0]);
    offset.SetY(translate[1]);
    return offset;
}

void RosenRenderContext::CancelTranslateXYAnimation()
{
    CHECK_NULL_VOID(translateXY_);
    auto property = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
    CHECK_NULL_VOID(property);
    property->RequestCancelAnimation();
}

OffsetF RosenRenderContext::GetTranslateXYProperty()
{
    OffsetF offset;
    CHECK_NULL_RETURN(translateXY_, offset);
    auto property = std::static_pointer_cast<RSAnimatableProperty<Vector2f>>(translateXY_->GetProperty());
    CHECK_NULL_RETURN(property, offset);
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
        CHECK_NULL_VOID(effect);
        SetTransitionPivot(frameSize, isTransitionIn);
        // notice that we have been in animateTo, so do not need to use Animation closure to notify transition.
        rsNode_->NotifyTransition(effect, isTransitionIn);
        return;
    }
    // add default transition effect on the 'breaking point' of render tree, if no user-defined transition effect
    // and triggered in AnimateTo closure.
    // Note: this default transition effect will be removed after all transitions finished, implemented in
    // OnTransitionInFinish. and OnTransitionOutFinish.
    if (isBreakingPoint_ && !transitionEffect_ && AnimationUtils::IsImplicitAnimationOpen()) {
        hasDefaultTransition_ = true;
        transitionEffect_ = RosenTransitionEffect::CreateDefaultRosenTransitionEffect();
        auto rsUIContext = rsNode_->GetRSUIContext();
        RSNode::ExecuteWithoutAnimation([this, isTransitionIn]() {
                // transitionIn effects should be initialized as active if is transitionIn.
                transitionEffect_->Attach(Claim(this), isTransitionIn);
            }, rsUIContext);
    }
    NotifyTransition(isTransitionIn);
}

void RosenRenderContext::OpacityAnimation(const AnimationOption& option, double begin, double end)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaUserModifier_, begin);
    AnimationUtils::Animate(
        option,
        [this, end]() {
            SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaUserModifier_, end);
        },
        option.GetOnFinishEvent());
}

void RosenRenderContext::ScaleAnimation(const AnimationOption& option, double begin, double end)
{
    CHECK_NULL_VOID(rsNode_);
    SetScale(begin, begin);
    AnimationUtils::Animate(
        option, [this, end]() { SetScale(end, end); }, option.GetOnFinishEvent());
}

void RosenRenderContext::SetBorderRadius(const BorderRadiusProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    auto paintRect = AdjustPaintRect();
    if (isDisappearing_ && !paintRect.IsValid()) {
        return;
    }
    double width = paintRect.Width();
    Rosen::Vector4f cornerRadius;
    cornerRadius.SetValues(static_cast<float>(value.radiusTopLeft.value_or(Dimension()).ConvertToPxWithSize(width)),
        static_cast<float>(value.radiusTopRight.value_or(Dimension()).ConvertToPxWithSize(width)),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension()).ConvertToPxWithSize(width)),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension()).ConvertToPxWithSize(width)));
    rsNode_->SetCornerRadius(cornerRadius);
    RequestNextFrame();
}

void RosenRenderContext::OnBorderRadiusUpdate(const BorderRadiusProperty& value)
{
    CHECK_NULL_VOID(isSynced_);
    SetBorderRadius(value);
}

void RosenRenderContext::OnBorderColorUpdate(const BorderColorProperty& value)
{
    SetBorderColor(value);
}

void RosenRenderContext::SetBorderColor(const BorderColorProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBorderColor(value.leftColor.value_or(Color::BLACK).GetValue(),
        value.topColor.value_or(Color::BLACK).GetValue(), value.rightColor.value_or(Color::BLACK).GetValue(),
        value.bottomColor.value_or(Color::BLACK).GetValue());
    RequestNextFrame();
}

void RosenRenderContext::SetBorderWidth(const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerBorderWidth;
    cornerBorderWidth.SetValues(static_cast<float>((value.leftDimen.value()).ConvertToPx()),
        static_cast<float>((value.topDimen.value()).ConvertToPx()),
        static_cast<float>((value.rightDimen.value()).ConvertToPx()),
        static_cast<float>((value.bottomDimen.value()).ConvertToPx()));
    rsNode_->SetBorderWidth(cornerBorderWidth);
    borderWidth_ = cornerBorderWidth;
    RequestNextFrame();
}

void RosenRenderContext::UpdateBorderWidthF(const BorderWidthPropertyF& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerBorderWidth;
    cornerBorderWidth.SetValues(value.leftDimen.value_or(0), static_cast<float>(value.topDimen.value_or(0)),
        static_cast<float>(value.rightDimen.value_or(0)), static_cast<float>(value.bottomDimen.value_or(0)));
    rsNode_->SetBorderWidth(cornerBorderWidth);
    borderWidth_ = cornerBorderWidth;
    RequestNextFrame();
}

void RosenRenderContext::OnBorderStyleUpdate(const BorderStyleProperty& value)
{
    SetBorderStyle(value);
}

void RosenRenderContext::SetBorderStyle(const BorderStyleProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBorderStyle(static_cast<uint32_t>(value.styleLeft.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleTop.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleRight.value_or(BorderStyle::SOLID)),
        static_cast<uint32_t>(value.styleBottom.value_or(BorderStyle::SOLID)));
    RequestNextFrame();
}

void RosenRenderContext::OnDashGapUpdate(const BorderWidthProperty& value)
{
    SetDashGap(value);
}

void RosenRenderContext::SetDashGap(const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerDashGap;
    cornerDashGap.SetValues(static_cast<float>((value.leftDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.topDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.rightDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.bottomDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()));
    rsNode_->SetBorderDashGap(cornerDashGap);
    RequestNextFrame();
}

void RosenRenderContext::OnDashWidthUpdate(const BorderWidthProperty& value)
{
    SetDashWidth(value);
}

void RosenRenderContext::SetDashWidth(const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerDashWidth;
    cornerDashWidth.SetValues(static_cast<float>((value.leftDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.topDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.rightDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()),
        static_cast<float>((value.bottomDimen.value_or(DASH_GEP_WIDTH)).ConvertToPx()));
    rsNode_->SetBorderDashWidth(cornerDashWidth);
    RequestNextFrame();
}

void RosenRenderContext::OnOuterBorderRadiusUpdate(const BorderRadiusProperty& value)
{
    SetOuterBorderRadius(value);
}

void RosenRenderContext::SetOuterBorderRadius(const BorderRadiusProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    auto paintRect = AdjustPaintRect();
    if (isDisappearing_ && !paintRect.IsValid()) {
        return;
    }
    double radiusX = paintRect.Width();
    Rosen::Vector4f cornerRadius;
    cornerRadius.SetValues(
        static_cast<float>(value.radiusTopLeft.value_or(Dimension(0.0)).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusTopRight.value_or(Dimension(0.0)).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension(0.0)).ConvertToPxWithSize(radiusX)),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension(0.0)).ConvertToPxWithSize(radiusX)));
    rsNode_->SetOuterBorderRadius(cornerRadius);
    RequestNextFrame();
}

void RosenRenderContext::OnOuterBorderColorUpdate(const BorderColorProperty& value)
{
    SetOuterBorderColor(value);
}

void RosenRenderContext::SetOuterBorderColor(const BorderColorProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4<Rosen::RSColor> color(Rosen::RSColor::FromArgbInt(value.leftColor.value_or(Color::BLACK).GetValue()),
        Rosen::RSColor::FromArgbInt(value.topColor.value_or(Color::BLACK).GetValue()),
        Rosen::RSColor::FromArgbInt(value.rightColor.value_or(Color::BLACK).GetValue()),
        Rosen::RSColor::FromArgbInt(value.bottomColor.value_or(Color::BLACK).GetValue()));
    rsNode_->SetOuterBorderColor(color);
    RequestNextFrame();
}

void RosenRenderContext::OnOuterBorderWidthUpdate(const BorderWidthProperty& value)
{
    SetOuterBorderWidth(value);
}

void RosenRenderContext::SetOuterBorderWidth(const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4f cornerBorderWidth;
    cornerBorderWidth.SetValues(static_cast<float>((value.leftDimen.value_or(Dimension(0.0))).ConvertToPx()),
        static_cast<float>((value.topDimen.value_or(Dimension(0.0))).ConvertToPx()),
        static_cast<float>((value.rightDimen.value_or(Dimension(0.0))).ConvertToPx()),
        static_cast<float>((value.bottomDimen.value_or(Dimension(0.0))).ConvertToPx()));
    rsNode_->SetOuterBorderWidth(cornerBorderWidth);
    RequestNextFrame();
}

void RosenRenderContext::SetExtraOffset(const std::optional<OffsetF>& offset)
{
    extraOffset_ = offset;
}

void RosenRenderContext::OnOuterBorderStyleUpdate(const BorderStyleProperty& value)
{
    SetOuterBorderStyle(value);
}

void RosenRenderContext::SetOuterBorderStyle(const BorderStyleProperty& value)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector4<Rosen::BorderStyle> borderStyle(
        static_cast<Rosen::BorderStyle>(static_cast<uint32_t>(value.styleLeft.value_or(BorderStyle::SOLID))),
        static_cast<Rosen::BorderStyle>(static_cast<uint32_t>(value.styleTop.value_or(BorderStyle::SOLID))),
        static_cast<Rosen::BorderStyle>(static_cast<uint32_t>(value.styleRight.value_or(BorderStyle::SOLID))),
        static_cast<Rosen::BorderStyle>(static_cast<uint32_t>(value.styleBottom.value_or(BorderStyle::SOLID))));
    rsNode_->SetOuterBorderStyle(borderStyle);
    RequestNextFrame();
}

void RosenRenderContext::OnAccessibilityFocusUpdate(
    bool isAccessibilityFocus, const int64_t accessibilityIdForVirtualNode)
{
    auto uiNode = GetHost();
    CHECK_NULL_VOID(uiNode);
    UpdateAccessibilityFocus(isAccessibilityFocus);
    if (isAccessibilityFocus) {
        PaintAccessibilityFocus();
    } else {
        ClearAccessibilityFocus();
    }

    if (accessibilityIdForVirtualNode == ACCESSIBILITY_FOCUS_WITHOUT_EVENT) {
        return;
    }

    if (accessibilityIdForVirtualNode == INVALID_PARENT_ID) {
        uiNode->OnAccessibilityEvent(isAccessibilityFocus ? AccessibilityEventType::ACCESSIBILITY_FOCUSED
                                                          : AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED);
    } else {
        uiNode->OnAccessibilityEventForVirtualNode(isAccessibilityFocus
                                                       ? AccessibilityEventType::ACCESSIBILITY_FOCUSED
                                                       : AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED,
            accessibilityIdForVirtualNode);
    }
}

void RosenRenderContext::OnAccessibilityFocusRectUpdate(RectT<int32_t> accessibilityFocusRect)
{
    auto isAccessibilityFocus = GetAccessibilityFocus().value_or(false);
    if (isAccessibilityFocus) {
        PaintAccessibilityFocus();
    }
}

bool RosenRenderContext::GetStatusByEffectTypeAndWindow()
{
    auto pipeline = GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto isWindowActivated = pipeline->IsWindowActivated();
    auto effectType = GetUseEffectType().value_or(EffectType::DEFAULT);
    return effectType == EffectType::WINDOW_EFFECT && !isWindowActivated;
}

void RosenRenderContext::OnUseEffectUpdate(bool useEffect)
{
    CHECK_NULL_VOID(rsNode_);
    if (GetStatusByEffectTypeAndWindow()) {
        rsNode_->SetUseEffect(false);
    } else {
        rsNode_->SetUseEffect(useEffect);
    }
}

void RosenRenderContext::OnUseEffectTypeUpdate(EffectType effectType)
{
    CHECK_NULL_VOID(rsNode_);
    auto effectTypeParam = static_cast<Rosen::UseEffectType>(effectType);
    rsNode_->SetUseEffectType(effectTypeParam);
    auto useEffect = GetUseEffect().value_or(false);
    OnUseEffectUpdate(useEffect);
}

void RosenRenderContext::OnUseShadowBatchingUpdate(bool useShadowBatching)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetUseShadowBatching(useShadowBatching);
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
    constexpr float kAccessibilityMinSize = 1.0f;
    double lineWidth = ACCESSIBILITY_FOCUS_WIDTH * PipelineBase::GetCurrentDensity();
    Color paintColor(ACCESSIBILITY_FOCUS_COLOR);
    Dimension paintWidth(lineWidth, DimensionUnit::PX);
    const auto& bounds = rsNode_->GetStagingProperties().GetBounds();
    RoundRect frameRect;
    double noGreenBorderWidth = (bounds.w_ - (2 * lineWidth)) > 0 ? (bounds.w_ - (2 * lineWidth)) : 0;
    double noGreenBorderHeight = (bounds.z_ - (2 * lineWidth)) > 0 ? (bounds.z_ - (2 * lineWidth)) : 0;
    frameRect.SetRect(RectF(lineWidth, lineWidth, noGreenBorderHeight, noGreenBorderWidth));
    RectT<int32_t> localRect = GetAccessibilityFocusRect().value_or(RectT<int32_t>());
    if (localRect != RectT<int32_t>()) {
        RectT<int32_t> containerRect;
        containerRect.SetRect(0, 0, bounds.z_, bounds.w_);
        RectF globalRect = frameRect.GetRect();
        auto localRectWidth = localRect.Width() - 2 * lineWidth;
        auto localRectHeight = localRect.Height() - 2 * lineWidth;
        if (NonPositive(localRectWidth)) {
            localRectWidth = kAccessibilityMinSize;
        }
        if (NonPositive(localRectHeight)) {
            localRectHeight = kAccessibilityMinSize;
        }
        globalRect.SetRect(globalRect.GetX() + localRect.GetX(), globalRect.GetY() + localRect.GetY(),
            localRectWidth, localRectHeight);
        if (globalRect.IsEmpty()) {
            ClearAccessibilityFocus();
            return;
        }
        frameRect.SetRect(globalRect);
    }
    PaintFocusState(frameRect, focusPaddingVp, paintColor, paintWidth, { true, false });
}

void RosenRenderContext::UpdateAccessibilityRoundRect()
{
    CHECK_NULL_VOID(accessibilityFocusStateModifier_);
    const constexpr double accessibilityFocusWidth = 4.0;
    double lineWidth = accessibilityFocusWidth * PipelineBase::GetCurrentDensity();
    Dimension paintWidth(lineWidth, DimensionUnit::PX);
    Dimension focusPaddingVp = Dimension(0.0, DimensionUnit::VP);

    auto paintWidthPx = static_cast<float>(paintWidth.ConvertToPx());
    auto borderPaddingPx = static_cast<float>(focusPaddingVp.ConvertToPx());

    auto node = GetHost();
    CHECK_NULL_VOID(node);
    if (node->GetTag() == V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG) {
        auto paintNodePattern = AceType::DynamicCast<AccessibilityFocusPaintNodePattern>(node->GetPattern());
        CHECK_NULL_VOID(paintNodePattern);
        auto focusNode = paintNodePattern->GetFocusNode().Upgrade();
        CHECK_NULL_VOID(focusNode);
        auto pipeline = focusNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto rect = pipeline->GetRootRect();
        std::shared_ptr<Rosen::RectF> drawRect =
            std::make_shared<Rosen::RectF>(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
        UpdateDrawRegion(DRAW_REGION_ACCESSIBILITY_FOCUS_MODIFIER_INDEX, drawRect);
    }
    auto nodeWidth = node->GetGeometryNode()->GetFrameSize().Width();
    auto nodeHeight = node->GetGeometryNode()->GetFrameSize().Height();

    double noGreenBorderWidth = GreatOrEqual(nodeWidth - (2 * lineWidth), 0.0) ? (nodeWidth - (2 * lineWidth)) : 0;
    double noGreenBorderHeight = GreatOrEqual(nodeHeight - (2 * lineWidth), 0.0) ? (nodeHeight - (2 * lineWidth)) : 0;

    RoundRect frameRect;
    std::shared_ptr<FocusStateModifier> modifier;
    modifier = accessibilityFocusStateModifier_;
    frameRect.SetRect(RectF(lineWidth - borderPaddingPx - paintWidthPx / 2,
        lineWidth - borderPaddingPx - paintWidthPx / 2, noGreenBorderWidth + 2 * borderPaddingPx + paintWidthPx,
        noGreenBorderHeight + 2 * borderPaddingPx + paintWidthPx)); // 2: framenode to graphic specification
    modifier->SetRoundRect(frameRect, paintWidthPx);
}
void RosenRenderContext::ClearAccessibilityFocus()
{
    CHECK_NULL_VOID(rsNode_);
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

    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dipScale = pipeline->GetDipScale();
    auto lpxScale = pipeline->GetLogicScale();

    CHECK_NULL_VOID(bdImage_);
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
    CHECK_NULL_VOID(image);
    BorderImagePainter borderImagePainter(
        *GetBdImage(), widthProp, paintRect.GetSize(), *image, { dipScale, lpxScale });
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        auto rect = borderImagePainter.GetDrawRect(OffsetF(0.0, 0.0));
        std::shared_ptr<Rosen::RectF> drawRect =
            std::make_shared<Rosen::RectF>(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
        UpdateDrawRegion(DRAW_REGION_FOREGROUND_MODIFIER_INDEX, drawRect);
    }
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
            return;
        }
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
            return;
        }
        ctx->bdImage_ = ctx->bdImageLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(ctx->bdImage_);
        if (ctx->GetHost()->GetGeometryNode()->GetFrameSize().IsPositive()) {
            ctx->PaintBorderImage();
            ctx->RequestNextFrame();
        }
    };
}

void RosenRenderContext::OnBackgroundAlignUpdate(const Alignment& align)
{
    CHECK_NULL_VOID(rsNode_);
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto transitionModifier = GetOrCreateTransitionModifier();
    transitionModifier->SetHostNode(node);
    transitionModifier->SetAlign(align);
    auto backgroundModifier = GetOrCreateBackgroundModifier();
    backgroundModifier->SetHostNode(node);
    backgroundModifier->SetAlign(align);
    if (GetIsTransitionBackgroundValue(false)) {
        rsNode_->RemoveModifier(backgroundModifier_);
        rsNode_->AddModifier(transitionModifier);
        transitionModifier->Modify();
    } else {
        rsNode_->RemoveModifier(transitionModifier_);
        rsNode_->AddModifier(backgroundModifier);
        backgroundModifier->Modify();
    }
    RequestNextFrame();
}

void RosenRenderContext::OnBackgroundPixelMapUpdate(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(rsNode_);
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto transitionModifier = GetOrCreateTransitionModifier();
    transitionModifier->SetPixelMap(pixelMap);
    transitionModifier->SetHostNode(node);
    auto backgroundModifier = GetOrCreateBackgroundModifier();
    auto nodeWidth = node->GetGeometryNode()->GetFrameSize().Width();
    auto nodeHeight = node->GetGeometryNode()->GetFrameSize().Height();
    backgroundModifier_->SetInitialNodeSize(nodeWidth, nodeHeight);
    backgroundModifier->SetPixelMap(pixelMap);
    backgroundModifier->SetHostNode(node);
    if (GetIsTransitionBackgroundValue(false)) {
        rsNode_->RemoveModifier(backgroundModifier_);
        rsNode_->AddModifier(transitionModifier);
        transitionModifier->Modify();
    } else {
        rsNode_->RemoveModifier(transitionModifier_);
        rsNode_->AddModifier(backgroundModifier);
        backgroundModifier->Modify();
    }
    RequestNextFrame();
}

void RosenRenderContext::OnCustomBackgroundColorUpdate(const Color& color)
{
    CHECK_NULL_VOID(rsNode_);
    if (!GetIsTransitionBackgroundValue(false)) {
        return;
    }
    rsNode_->RemoveModifier(backgroundModifier_);
    auto transitionModifier = GetOrCreateTransitionModifier();
    rsNode_->AddModifier(transitionModifier);
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    transitionModifier->SetHostNode(node);
    transitionModifier->SetBackgroundColor(color);
    transitionModifier->Modify();
    RequestNextFrame();
}

void RosenRenderContext::OnIsBuilderBackgroundUpdate(bool isBuilderBackground)
{
    auto transitionModifier = GetOrCreateTransitionModifier();
    transitionModifier->SetIsBuilderBackground(isBuilderBackground);
}

void RosenRenderContext::CreateBackgroundPixelMap(const RefPtr<FrameNode>& customNode)
{
    NG::ComponentSnapshot::JsCallback callback = [weak = WeakPtr(GetHost()), containerId = Container::CurrentId()](
                                                     std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
                                                     std::function<void()> finishCallback) {
        CHECK_NULL_VOID(pixmap);
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ContainerScope scope(containerId);
        std::shared_ptr<Media::PixelMap> pmap = std::move(pixmap);
        auto pixelmap = PixelMap::CreatePixelMap(&pmap);
        auto task = [pixelmap, frameNode]() {
            auto context = frameNode->GetRenderContext();
            if (context) {
                context->UpdateBackgroundPixelMap(pixelmap);
                context->RequestNextFrame();
            }
        };
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUICreateBackgroundPixelMap");
    };
    auto firstCallback = callback;
    SnapshotParam firstParam;
    firstParam.delay = 0;
    firstParam.checkImageStatus = true;
    firstParam.options.waitUntilRenderFinished = true;
    NG::ComponentSnapshot::Create(customNode, std::move(firstCallback), false, firstParam, true);

    SnapshotParam param;
    NG::ComponentSnapshot::Create(customNode, std::move(callback), false, param, false);
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
    auto paintTask = [weak = WeakClaim(this), paintSize, borderImageProperty, &borderWidthProperty, gradient](
                         RSCanvas& rsCanvas) mutable {
        auto rsImage = DrawingDecorationPainter::CreateBorderImageGradient(gradient, paintSize);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        BorderImagePainter borderImagePainter(borderImageProperty, borderWidthProperty, paintSize, rsImage,
            { pipeline->GetDipScale(), pipeline->GetLogicScale() });
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
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!rect.GetSize().IsPositive()) {
            geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
            return rect;
        }
    } else {
        if (!rect.GetSize().IsPositive() && !frameNode->IsLayoutComplete()) {
            geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
            return rect;
        }
    }
    bool hasPosition = (HasPosition() || HasPositionEdges()) && IsUsingPosition(frameNode);
    bool hasOffset = HasOffset() || HasOffsetEdges();
    if (!HasAnchor() && !hasOffset && !hasPosition) {
        geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
        return rect;
    }
    auto percentReference = GetPercentReference(frameNode);
    auto widthPercentReference = percentReference.Width();
    auto heightPercentReference = percentReference.Height();
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
        geometryNode->SetFrameOffset(rect.GetOffset());
        geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
        return rect;
    }
    if (HasPositionEdges() && IsUsingPosition(frameNode)) {
        auto positionEdges = GetPositionEdgesValue(EdgesParam {});
        OffsetF rectOffset =
            GetRectOffsetWithPositionEdges(positionEdges, widthPercentReference, heightPercentReference);
        rect.SetLeft(rectOffset.GetX() - anchorX.value_or(0));
        rect.SetTop(rectOffset.GetY() - anchorY.value_or(0));
        geometryNode->SetFrameOffset(rect.GetOffset());
        geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
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
        geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
        return rect;
    }
    if (HasOffsetEdges()) {
        auto offsetEdges = GetOffsetEdgesValue(EdgesParam {});
        OffsetF rectOffset = GetRectOffsetWithOffsetEdges(offsetEdges, widthPercentReference, heightPercentReference);
        rect.SetLeft(rect.GetX() + rectOffset.GetX() - anchorX.value_or(0));
        rect.SetTop(rect.GetY() + rectOffset.GetY() - anchorY.value_or(0));
        geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
        return rect;
    }
    rect.SetLeft(rect.GetX() - anchorX.value_or(0));
    rect.SetTop(rect.GetY() - anchorY.value_or(0));
    geometryNode->SetPixelGridRoundOffset(rect.GetOffset());
    return rect;
}

float RosenRenderContext::RoundValueToPixelGrid(float value)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.75f)) {
        return (value - fractials + 1.0f);
    } else if (NearEqual(fractials, 0.0f) || !GreatOrEqual(fractials, 0.25f)) {
        return (value - fractials);
    } else {
        return (value - fractials + 0.5f);
    }
}

OffsetF RosenRenderContext::GetRectOffsetWithOffsetEdges(
    const EdgesParam& offsetEdges, float widthPercentReference, float heightPercentReference)
{
    OffsetF rectOffset;
    if (offsetEdges.top.has_value()) {
        rectOffset.SetY(
            ConvertToPx(offsetEdges.top.value(), ScaleProperty::CreateScaleProperty(), heightPercentReference)
                .value_or(0));
    }
    if (offsetEdges.left.has_value()) {
        rectOffset.SetX(
            ConvertToPx(offsetEdges.left.value(), ScaleProperty::CreateScaleProperty(), widthPercentReference)
                .value_or(0));
    }
    if (!offsetEdges.top.has_value() && offsetEdges.bottom.has_value()) {
        rectOffset.SetY(
            -ConvertToPx(offsetEdges.bottom.value(), ScaleProperty::CreateScaleProperty(), heightPercentReference)
                 .value_or(0));
    }
    if (!offsetEdges.left.has_value() && offsetEdges.right.has_value()) {
        rectOffset.SetX(
            -ConvertToPx(offsetEdges.right.value(), ScaleProperty::CreateScaleProperty(), widthPercentReference)
                 .value_or(0));
    }
    return rectOffset;
}

OffsetF RosenRenderContext::GetRectOffsetWithPositionEdges(
    const EdgesParam& positionEdges, float widthPercentReference, float heightPercentReference)
{
    float rectTop = 0.0f;
    float rectLeft = 0.0f;

    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, OffsetF {});
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, OffsetF {});
    auto& marginOri = layoutProperty->GetMarginProperty();
    std::unique_ptr<MarginProperty> margin(
        marginOri ? std::make_unique<MarginProperty>(*marginOri) : std::make_unique<MarginProperty>());

    auto parentNode = frameNode->GetAncestorNodeOfFrame(true);
    CHECK_NULL_RETURN(parentNode, OffsetF {});
    auto parentLayoutProperty = parentNode->GetLayoutProperty();
    CHECK_NULL_RETURN(parentLayoutProperty, OffsetF {});
    auto& parentPaddingOri = parentLayoutProperty->GetPaddingProperty();
    std::unique_ptr<PaddingProperty> parentPadding(
        parentPaddingOri ? std::make_unique<PaddingProperty>(*parentPaddingOri) : std::make_unique<PaddingProperty>());

    auto parenPercentRef = GetPercentReference(parentNode);
    float parentWidthRef = parenPercentRef.Width();
    float parentHeightRef = parenPercentRef.Height();

    SizeF selfSize = frameNode->GetGeometryNode()->GetFrameSize();
    float selfWidth = selfSize.Width();
    float selfHeight = selfSize.Height();
    SizeF parentSize = parentNode->GetGeometryNode()->GetFrameSize();
    float parentWidth = parentSize.Width();
    float parentHeight = parentSize.Height();

    if (positionEdges.top.has_value()) {
        rectTop = ConvertToPx(parentPadding->top.value_or(CalcLength(Dimension(0))).GetDimension(),
                      ScaleProperty::CreateScaleProperty(), parentHeightRef)
                      .value_or(0) +
                  ConvertToPx(margin->top.value_or(CalcLength(Dimension(0))).GetDimension(),
                      ScaleProperty::CreateScaleProperty(), heightPercentReference)
                      .value_or(0) +
                  ConvertToPx(positionEdges.top.value(), ScaleProperty::CreateScaleProperty(), heightPercentReference)
                      .value_or(0);
    }
    if (positionEdges.left.has_value()) {
        rectLeft = ConvertToPx(parentPadding->left.value_or(CalcLength(Dimension(0))).GetDimension(),
                       ScaleProperty::CreateScaleProperty(), parentWidthRef)
                       .value_or(0) +
                   ConvertToPx(margin->left.value_or(CalcLength(Dimension(0))).GetDimension(),
                       ScaleProperty::CreateScaleProperty(), widthPercentReference)
                       .value_or(0) +
                   ConvertToPx(positionEdges.left.value(), ScaleProperty::CreateScaleProperty(), widthPercentReference)
                       .value_or(0);
    }
    if (!positionEdges.top.has_value() && positionEdges.bottom.has_value()) {
        rectTop =
            parentHeight - selfHeight -
            ConvertToPx(parentPadding->bottom.value_or(CalcLength(Dimension(0))).GetDimension(),
                ScaleProperty::CreateScaleProperty(), parentHeightRef)
                .value_or(0) -
            ConvertToPx(margin->bottom.value_or(CalcLength(Dimension(0))).GetDimension(),
                ScaleProperty::CreateScaleProperty(), heightPercentReference)
                .value_or(0) -
            ConvertToPx(positionEdges.bottom.value(), ScaleProperty::CreateScaleProperty(), heightPercentReference)
                .value_or(0);
    }
    if (!positionEdges.left.has_value() && positionEdges.right.has_value()) {
        rectLeft = parentWidth - selfWidth -
                   ConvertToPx(parentPadding->right.value_or(CalcLength(Dimension(0))).GetDimension(),
                       ScaleProperty::CreateScaleProperty(), parentWidthRef)
                       .value_or(0) -
                   ConvertToPx(margin->right.value_or(CalcLength(Dimension(0))).GetDimension(),
                       ScaleProperty::CreateScaleProperty(), widthPercentReference)
                       .value_or(0) -
                   ConvertToPx(positionEdges.right.value(), ScaleProperty::CreateScaleProperty(), widthPercentReference)
                       .value_or(0);
    }
    return OffsetF(rectLeft, rectTop);
}

float RosenRenderContext::RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.75f)) {
            return (value - fractials + 1.0f);
        } else if (NearEqual(fractials, 0.0f) || !GreatOrEqual(fractials, 0.25f)) {
            return (value - fractials);
        } else {
            return (value - fractials + 0.5f);
        }
    }
    return value;
}

float RosenRenderContext::OnePixelValueRounding(float value)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.5f)) {
        return (value - fractials + 1.0f);
    } else {
        return (value - fractials);
    }
}

float RosenRenderContext::OnePixelValueRounding(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.5f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}

void RosenRenderContext::RoundToPixelGrid()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    float relativeLeft = geometryNode->GetPixelGridRoundOffset().GetX();
    float relativeTop = geometryNode->GetPixelGridRoundOffset().GetY();
    float nodeWidth = geometryNode->GetFrameSize().Width();
    float nodeHeight = geometryNode->GetFrameSize().Height();
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    // round node
    float nodeLeftI = RoundValueToPixelGrid(relativeLeft);
    float nodeTopI = RoundValueToPixelGrid(relativeTop);
    geometryNode->SetPixelGridRoundOffset(OffsetF(nodeLeftI, nodeTopI));
    float nodeWidthI = RoundValueToPixelGrid(absoluteRight) - nodeLeftI;
    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom) - nodeTopI;
    geometryNode->SetPixelGridRoundSize(SizeF(nodeWidthI, nodeHeightI));
    if (borderWidth_ != Rosen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f)) {
        // round inner
        float innerLeft = relativeLeft + borderWidth_[0];
        float innerRight = relativeLeft + nodeWidth - borderWidth_[2];
        float innerTop = relativeTop + borderWidth_[1];
        float innerBottom = relativeTop + nodeHeight - borderWidth_[3];
        float innerWidthI = RoundValueToPixelGrid(innerRight) - RoundValueToPixelGrid(innerLeft);
        float innerHeightI = RoundValueToPixelGrid(innerBottom) - RoundValueToPixelGrid(innerTop);
        // update border
        float borderLeftI = RoundValueToPixelGrid(borderWidth_[0]);
        float borderTopI = RoundValueToPixelGrid(borderWidth_[1]);
        float borderRightI = nodeWidthI - innerWidthI - borderLeftI;
        float borderBottomI = nodeHeightI - innerHeightI - borderTopI;
        BorderWidthPropertyF borderWidthPropertyF;
        borderWidthPropertyF.leftDimen = borderLeftI;
        borderWidthPropertyF.topDimen = borderTopI;
        borderWidthPropertyF.rightDimen = borderRightI;
        borderWidthPropertyF.bottomDimen = borderBottomI;
        UpdateBorderWidthF(borderWidthPropertyF);
    }
}

void RosenRenderContext::RoundToPixelGrid(bool isRound, uint16_t flag)
{
    CHECK_NULL_VOID(rsNode_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    float relativeLeft = geometryNode->GetPixelGridRoundOffset().GetX();
    float relativeTop = geometryNode->GetPixelGridRoundOffset().GetY();
    float nodeWidth = geometryNode->GetFrameSize().Width();
    float nodeHeight = geometryNode->GetFrameSize().Height();
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    bool ceilLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
    bool floorLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START);
    bool ceilTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
    bool floorTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
    bool ceilRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
    bool floorRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END);
    bool ceilBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    bool floorBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);
    // round node
    float nodeLeftI = RoundValueToPixelGrid(relativeLeft, isRound, ceilLeft, floorLeft);
    float nodeTopI = RoundValueToPixelGrid(relativeTop, isRound, ceilTop, floorTop);
    geometryNode->SetPixelGridRoundOffset(OffsetF(nodeLeftI, nodeTopI));
    float nodeWidthI = RoundValueToPixelGrid(absoluteRight, isRound, ceilRight, floorRight) - nodeLeftI;
    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom, isRound, ceilBottom, floorBottom) - nodeTopI;
    geometryNode->SetPixelGridRoundSize(SizeF(nodeWidthI, nodeHeightI));
    if (borderWidth_ != Rosen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f)) {
        // round inner
        float innerLeft = relativeLeft + borderWidth_[0];
        float innerRight = relativeLeft + nodeWidth - borderWidth_[2];
        float innerTop = relativeTop + borderWidth_[1];
        float innerBottom = relativeTop + nodeHeight - borderWidth_[3];
        float innerWidthI = RoundValueToPixelGrid(innerRight, isRound, ceilRight, floorRight) -
                            RoundValueToPixelGrid(innerLeft, isRound, ceilLeft, floorLeft);
        float innerHeightI = RoundValueToPixelGrid(innerBottom, isRound, ceilBottom, floorBottom) -
                             RoundValueToPixelGrid(innerTop, isRound, ceilTop, floorTop);
        // update border
        float borderLeftI = RoundValueToPixelGrid(borderWidth_[0], isRound, ceilLeft, floorLeft);
        float borderTopI = RoundValueToPixelGrid(borderWidth_[1], isRound, ceilTop, floorTop);
        float borderRightI = nodeWidthI - innerWidthI - borderLeftI;
        float borderBottomI = nodeHeightI - innerHeightI - borderTopI;
        BorderWidthPropertyF borderWidthPropertyF;
        borderWidthPropertyF.leftDimen = borderLeftI;
        borderWidthPropertyF.topDimen = borderTopI;
        borderWidthPropertyF.rightDimen = borderRightI;
        borderWidthPropertyF.bottomDimen = borderBottomI;
        UpdateBorderWidthF(borderWidthPropertyF);
    }
}

void RosenRenderContext::OnePixelRounding()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    float relativeLeft = geometryNode->GetPixelGridRoundOffset().GetX();
    float relativeTop = geometryNode->GetPixelGridRoundOffset().GetY();
    float nodeWidth = geometryNode->GetFrameSize().Width();
    float nodeHeight = geometryNode->GetFrameSize().Height();
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;

    float nodeLeftI = OnePixelValueRounding(relativeLeft);
    float nodeTopI = OnePixelValueRounding(relativeTop);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    geometryNode->SetPixelGridRoundOffset(OffsetF(nodeLeftI, nodeTopI));

    float nodeWidthI = OnePixelValueRounding(absoluteRight) - nodeLeftI;
    float nodeWidthTemp = OnePixelValueRounding(nodeWidth);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = OnePixelValueRounding(absoluteBottom) - nodeTopI;
    float nodeHeightTemp = OnePixelValueRounding(nodeHeight);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }
    geometryNode->SetPixelGridRoundSize(SizeF(nodeWidthI, nodeHeightI));
}

void RosenRenderContext::OnePixelRounding(uint16_t flag)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    float relativeLeft = geometryNode->GetPixelGridRoundOffset().GetX();
    float relativeTop = geometryNode->GetPixelGridRoundOffset().GetY();
    float nodeWidth = geometryNode->GetFrameSize().Width();
    float nodeHeight = geometryNode->GetFrameSize().Height();
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    bool ceilLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
    bool floorLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START);
    bool noRoundLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START);
    bool ceilTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
    bool floorTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
    bool noRoundTop = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP);
    bool ceilRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
    bool floorRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END);
    bool noRoundRight = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END);
    bool ceilBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    bool floorBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);
    bool noRoundBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);

    float nodeLeftI = OnePixelValueRounding(relativeLeft, !noRoundLeft, ceilLeft, floorLeft);
    float nodeTopI = OnePixelValueRounding(relativeTop, !noRoundTop, ceilTop, floorTop);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    geometryNode->SetPixelGridRoundOffset(OffsetF(nodeLeftI, nodeTopI));

    float nodeWidthI = OnePixelValueRounding(absoluteRight, !noRoundRight, ceilRight, floorRight) - nodeLeftI;
    float nodeWidthTemp = OnePixelValueRounding(nodeWidth, !noRoundRight, ceilRight, floorRight);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    bool enableForceFloorX = SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE && (floorLeft || floorRight);
    if (roundToPixelErrorX < -0.5f && !enableForceFloorX) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = OnePixelValueRounding(absoluteBottom, !noRoundBottom, ceilBottom, floorBottom) - nodeTopI;
    float nodeHeightTemp = OnePixelValueRounding(nodeHeight, !noRoundBottom, ceilBottom, floorBottom);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    bool enableForceFloorY = SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE && (floorTop || floorBottom);
    if (roundToPixelErrorY < -0.5f && !enableForceFloorY) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }
    geometryNode->SetPixelGridRoundSize(SizeF(nodeWidthI, nodeHeightI));
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
    auto frameNodeParent = frameNode->GetAncestorNodeOfFrame(true);
    CHECK_NULL_VOID(frameNodeParent);
    auto layoutProperty = frameNodeParent->GetLayoutProperty();
    if (layoutProperty && layoutProperty->GetPaddingProperty()) {
        parentPaddingLeft =
            layoutProperty->GetPaddingProperty()->left.value_or(CalcLength(Dimension(0))).GetDimension();
        parentPaddingTop = layoutProperty->GetPaddingProperty()->top.value_or(CalcLength(Dimension(0))).GetDimension();
    }
}

SizeF RosenRenderContext::GetPercentReference(const RefPtr<FrameNode>& frameNode)
{
    SizeF percentReference = SizeF(PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight());
    CHECK_NULL_RETURN(frameNode, percentReference);
    const auto& layoutConstraint = frameNode->GetGeometryNode()->GetParentLayoutConstraint();
    if (layoutConstraint.has_value()) {
        percentReference.SetWidth(layoutConstraint->percentReference.Width());
        percentReference.SetHeight(layoutConstraint->percentReference.Height());
    }
    return percentReference;
}

void RosenRenderContext::SetPositionToRSNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    auto rect = AdjustPaintRect();
    if (!rect.GetSize().IsPositive()) {
        return;
    }
    paintRect_ = rect;
    if (frameNode->ParentExpansive() && !frameNode->SelfExpansive()) {
        // Dynamically modify position, need consider parent expand
        frameNode->AdjustNotExpandNode();
        rect = paintRect_;
    }
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        auto preBounds = rsNode_->GetStagingProperties().GetBounds();
        if (!NearEqual(preBounds[0], rect.GetX()) || !NearEqual(preBounds[1], rect.GetY())) {
            ACE_SCOPED_TRACE("SetPosition, bounds from (%f, %f, %f, %f) to (%f, %f, %f, %f), id:%d, tag:%s",
                preBounds[0], preBounds[1], preBounds[2], preBounds[3], rect.GetX(), rect.GetY(), rect.Width(),
                rect.Height(), frameNode->GetId(), frameNode->GetTag().c_str());
        }
    }
    rsNode_->SetBounds(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    if (useContentRectForRSFrame_) {
        SetContentRectToFrame(rect);
    } else {
        rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    }
    if (frameOffset_.has_value()) {
        rsNode_->SetFrame(
            rect.GetX() + frameOffset_->GetX(), rect.GetY() + frameOffset_->GetY(), rect.Width(), rect.Height());
    }
    frameNode->OnSyncGeometryFrameFinish(rect);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost());
}

void RosenRenderContext::OnPositionUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnPositionEdgesUpdate(const EdgesParam& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnOffsetUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnOffsetEdgesUpdate(const EdgesParam& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnAnchorUpdate(const OffsetT<Dimension>& /*value*/)
{
    SetPositionToRSNode();
}

void RosenRenderContext::RecalculatePosition()
{
    SetPositionToRSNode();
}

void RosenRenderContext::OnZIndexUpdate(int32_t value)
{
    CHECK_NULL_VOID(rsNode_);
    // When zindex is combined with transform/rotate, zindex has the action of controlling camera height
    rsNode_->SetPositionZApplicableCamera3D(Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN));
    rsNode_->SetPositionZ(static_cast<float>(value));
    auto uiNode = GetHost();
    CHECK_NULL_VOID(uiNode);
    auto parent = uiNode->GetAncestorNodeOfFrame(true);
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
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

void RosenRenderContext::PaintFocusState(const RoundRect& paintRect, const Color& paintColor,
    const Dimension& paintWidth, bool isAccessibilityFocus, bool isFocusBoxGlow)
{
#ifndef IS_RELEASE_VERSION
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "PaintFocusState rect is (%{public}f, %{public}f, %{public}f, %{public}f). Color is %{public}s, PainWidth is "
        "%{public}s",
        paintRect.GetRect().Left(), paintRect.GetRect().Top(), paintRect.GetRect().Width(),
        paintRect.GetRect().Height(), paintColor.ColorToString().c_str(), paintWidth.ToString().c_str());
#endif
    CHECK_NULL_VOID(paintRect.GetRect().IsValid());
    CHECK_NULL_VOID(rsNode_);
    auto borderWidthPx = static_cast<float>(paintWidth.ConvertToPx());
    isFocusBoxGlow_ = isFocusBoxGlow;
    if (isAccessibilityFocus) {
        InitAccessibilityFocusModidifer(paintRect, paintColor, borderWidthPx);
        auto host = GetHost();
        if (host && host->GetTag() != V2::ACCESSIBILITY_FOCUS_PAINT_NODE_TAG) {
            UpdateDrawRegion(
                DRAW_REGION_ACCESSIBILITY_FOCUS_MODIFIER_INDEX, accessibilityFocusStateModifier_->GetOverlayRect());
        }
        rsNode_->AddModifier(accessibilityFocusStateModifier_);
        accessibilityFocusStateModifier_->AttachAnimationRectProperty();
        RequestNextFrame();
        return;
    }
    if (!isFocusBoxGlow_) {
        InitFocusStateModidifer(paintRect, paintColor, borderWidthPx);
        UpdateDrawRegion(DRAW_REGION_FOCUS_MODIFIER_INDEX, focusStateModifier_->GetOverlayRect());
        rsNode_->AddModifier(focusStateModifier_);
        focusStateModifier_->AttachAnimationRectProperty();
    } else {
        InitFocusAnimationModidifer(paintRect, paintColor, borderWidthPx);
        UpdateDrawRegion(DRAW_REGION_FOCUS_MODIFIER_INDEX, focusAnimationModifier_->GetOverlayRect());
        auto modifierAdapter =
            std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(focusAnimationModifier_));
        rsNode_->AddModifier(modifierAdapter);
        modifierAdapter->AttachProperties();
        focusAnimationModifier_->StartFocusAnimation();
    }
    RequestNextFrame();
}

void RosenRenderContext::InitAccessibilityFocusModidifer(
    const RoundRect& paintRect, const Color& paintColor, float borderWidthPx)
{
    auto frameNode = GetHost();
    if (!accessibilityFocusStateModifier_) {
        accessibilityFocusStateModifier_ = std::make_shared<FocusStateModifier>();
    }
    rsNode_->AddModifier(accessibilityFocusStateModifier_);
    accessibilityFocusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
    accessibilityFocusStateModifier_->SetPaintColor(paintColor);
    accessibilityFocusStateModifier_->SetFrameNode(frameNode);
    accessibilityFocusStateModifier_->SetNoNeedUICaptured(true);
}

void RosenRenderContext::InitFocusStateModidifer(
    const RoundRect& paintRect, const Color& paintColor, float borderWidthPx)
{
    auto frameNode = GetHost();
    if (!focusStateModifier_) {
        focusStateModifier_ = std::make_shared<FocusStateModifier>();
    }
    focusStateModifier_->SetRoundRect(paintRect, borderWidthPx);
    focusStateModifier_->SetPaintColor(paintColor);
    focusStateModifier_->SetFrameNode(frameNode);
}

void RosenRenderContext::InitFocusAnimationModidifer(
    const RoundRect& paintRect, const Color& paintColor, float borderWidthPx)
{
    auto frameNode = GetHost();
    if (!focusAnimationModifier_) {
        focusAnimationModifier_ = AceType::MakeRefPtr<FocusAnimationModifier>();
    }
    focusAnimationModifier_->SetRoundRect(paintRect, borderWidthPx);
    focusAnimationModifier_->SetPaintColor(paintColor);
    focusAnimationModifier_->SetFrameNode(frameNode);
}

void RosenRenderContext::PaintFocusState(const RoundRect& paintRect, const Dimension& focusPaddingVp,
    const Color& paintColor, const Dimension& paintWidth, const PaintFocusExtraInfo& paintFocusExtraInfo)
{
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

    PaintFocusState(focusPaintRect, paintColor, paintWidth, paintFocusExtraInfo.isAccessibilityFocus,
        paintFocusExtraInfo.isFocusBoxGlow);
}

void RosenRenderContext::PaintFocusState(
    const Dimension& focusPaddingVp, const Color& paintColor, const Dimension& paintWidth, bool isFocusBoxGlow)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& bounds = rsNode_->GetStagingProperties().GetBounds();
    const auto& radius = rsNode_->GetStagingProperties().GetCornerRadius();

    RoundRect frameRect;
    frameRect.SetRect(RectF(0, 0, bounds.z_, bounds.w_));
    frameRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radius.x_, radius.x_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radius.y_, radius.y_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radius.z_, radius.z_);
    frameRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radius.w_, radius.w_);

    PaintFocusState(frameRect, focusPaddingVp, paintColor, paintWidth, { false, isFocusBoxGlow });
}

void RosenRenderContext::ClearFocusState()
{
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Clear focus state.");
    CHECK_NULL_VOID(rsNode_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (!isFocusBoxGlow_) {
        CHECK_NULL_VOID(focusStateModifier_);
        UpdateDrawRegion(DRAW_REGION_FOCUS_MODIFIER_INDEX, focusStateModifier_->GetOverlayRect());
        rsNode_->RemoveModifier(focusStateModifier_);
        RequestNextFrame();
        return;
    }
    CHECK_NULL_VOID(focusAnimationModifier_);
    focusAnimationModifier_->StopFocusAnimation();
    UpdateDrawRegion(DRAW_REGION_FOCUS_MODIFIER_INDEX, focusAnimationModifier_->GetOverlayRect());
    auto modifierAdapter =
        std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(focusAnimationModifier_));
    rsNode_->RemoveModifier(modifierAdapter);
    RequestNextFrame();
}

void RosenRenderContext::FlushContentDrawFunction(CanvasDrawFunction&& contentDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(contentDraw);
    rsNode_->DrawOnNode(
        Rosen::RSModifierType::CONTENT_STYLE,
        [contentDraw = std::move(contentDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            contentDraw(*canvas);
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
        UpdateDrawRegion(DRAW_REGION_CONTENT_MODIFIER_INDEX, overlayRect);
    }
    rsNode_->SetIsCustomTextType(contentModifier->GetIsCustomFont());
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
}

void RosenRenderContext::FlushKitContentModifier(const RefPtr<Kit::Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);

    auto modifierAdapter = ConvertKitContentModifier(modifier);
    rsNode_->AddModifier(modifierAdapter);
    modifier->OnAttached();
}

void RosenRenderContext::FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(foregroundDraw);
    rsNode_->DrawOnNode(Rosen::RSModifierType::FOREGROUND_STYLE,
        [foregroundDraw = std::move(foregroundDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            foregroundDraw(*canvas);
        });
}

void RosenRenderContext::FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(overlayDraw);
    rsNode_->DrawOnNode(
        Rosen::RSModifierType::OVERLAY_STYLE,
        [overlayDraw = std::move(overlayDraw)](std::shared_ptr<RSCanvas> canvas) {
            CHECK_NULL_VOID(canvas);
            overlayDraw(*canvas);
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
    UpdateDrawRegion(DRAW_REGION_OVERLAY_MODIFIER_INDEX, overlayRect);
    rsNode_->AddModifier(modifierAdapter);
    modifierAdapter->AttachProperties();
}

void RosenRenderContext::FlushForegroundModifier(const RefPtr<Modifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<ForegroundModifierAdapter>(ConvertForegroundModifier(modifier));
    auto foregroundModifier = AceType::DynamicCast<ForegroundModifier>(modifier);
    CHECK_NULL_VOID(foregroundModifier);
    auto rect = foregroundModifier->GetBoundsRect();
    std::shared_ptr<Rosen::RectF> foregroundRect =
        std::make_shared<Rosen::RectF>(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
    UpdateDrawRegion(DRAW_REGION_OVERLAY_MODIFIER_INDEX, foregroundRect);
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

std::vector<std::shared_ptr<Rosen::RSNode>> RosenRenderContext::GetChildrenRSNodes(
    const std::list<RefPtr<FrameNode>>& frameChildren, std::unordered_map<Rosen::RSNode::SharedPtr, bool>& nodeMap)
{
    std::vector<std::shared_ptr<Rosen::RSNode>> rsNodes;
    for (const auto& child : frameChildren) {
        if (!child) {
            continue;
        }
        auto rosenRenderContext = DynamicCast<RosenRenderContext>(child->renderContext_);
        if (!rosenRenderContext) {
            continue;
        }
        auto rsnode = rosenRenderContext->GetRSNode();
        if (!rsnode) {
            continue;
        }
        auto result = nodeMap.try_emplace(rsnode, false);
        if (result.second) {
            rsNodes.emplace_back(rsnode);
        }
    }
    return rsNodes;
}

void RosenRenderContext::SetDrawNode()
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetDrawNode();
}

bool RosenRenderContext::AddNodeToRsTree()
{
    auto node = GetHost();
    if (!node || !node->GetIsDelete()) {
        return true;
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "AddNodeToRsTree node(%{public}d, %{public}s)", node->GetId(),
            node->GetTag().c_str());
    }

    std::list<RefPtr<FrameNode>> childNodes;
    // get not be deleted children of node
    GetLiveChildren(node, childNodes);

    auto rsNode = GetRsNodeByFrame(node);
    CHECK_NULL_RETURN(rsNode, false);

    size_t rsNodeIndex = rsNode->GetChildren().size();
    for (auto& child : childNodes) {
        auto childRsNode = GetRsNodeByFrame(child);
        rsNode->AddChild(childRsNode, rsNodeIndex);
        rsNodeIndex++;
    }
    node->SetDeleteRsNode(false);
    // rebuild parent node
    auto parentNode = node->GetParentFrameNode();
    CHECK_NULL_RETURN(parentNode, false);
    parentNode->MarkNeedSyncRenderTree();
    parentNode->RebuildRenderContextTree();
    return true;
}

std::shared_ptr<Rosen::RSNode> RosenRenderContext::GetRsNodeByFrame(const RefPtr<FrameNode>& frameNode)
{
    if (!frameNode) {
        return nullptr;
    }
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(frameNode->renderContext_);
    if (!rosenRenderContext) {
        return nullptr;
    }
    auto rsnode = rosenRenderContext->GetRSNode();
    return rsnode;
}

bool RosenRenderContext::CanNodeBeDeleted(const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    auto rsNode = GetRsNodeByFrame(node);
    CHECK_NULL_RETURN(rsNode, false);
    std::list <RefPtr<FrameNode>> childChildrenList;
    node->GenerateOneDepthVisibleFrameWithTransition(childChildrenList);
    if (rsNode->GetIsDrawn() || rsNode->GetType() != Rosen::RSUINodeType::CANVAS_NODE
        || childChildrenList.empty() || node->GetTag() == V2::PAGE_ETS_TAG
        || node->GetTag() == V2::STAGE_ETS_TAG) {
        return false;
    }
    return true;
}

void RosenRenderContext::GetLiveChildren(const RefPtr<FrameNode>& node, std::list<RefPtr<FrameNode>>& childNodes)
{
    CHECK_NULL_VOID(node);
    std::list<RefPtr<FrameNode>> childrenList;
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    node->GenerateOneDepthVisibleFrameWithTransition(childrenList);
    for (auto& child : childrenList) {
        if (!CanNodeBeDeleted(child)) {
            childNodes.emplace_back(child);
            if (pipeline && child->HasPositionZ()) {
                pipeline->AddPositionZNode(child->GetId());
            }
        } else {
            child->SetDeleteRsNode(true);
            GetLiveChildren(child, childNodes);
        }
    }
    auto accessibilityFocusPaintNode = node->GetFocusPaintNode();
    if (accessibilityFocusPaintNode) {
        childNodes.emplace_back(accessibilityFocusPaintNode);
        if (accessibilityFocusPaintNode->HasPositionZ()) {
            pipeline->AddPositionZNode(accessibilityFocusPaintNode->GetId());
        }
    }
    auto overlayNode = node->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto property = overlayNode->GetLayoutProperty();
    if (property && property->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE) {
        if (!CanNodeBeDeleted(overlayNode)) {
            childNodes.emplace_back(overlayNode);
            if (pipeline && overlayNode->HasPositionZ()) {
                pipeline->AddPositionZNode(overlayNode->GetId());
            }
        } else {
            overlayNode->SetDeleteRsNode(true);
            GetLiveChildren(overlayNode, childNodes);
        }
    }
}

void RosenRenderContext::AddRsNodeForCapture()
{
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    if (host && host->GetIsDelete()) {
        rsNode_->SetDrawNode();
        auto pipeline = host->GetContext();
        if (pipeline) {
            pipeline->FlushMessages();
        }
    }
}

void RosenRenderContext::ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children)
{
    if (!rsNode_ || !isNeedRebuildRSTree_) {
        return;
    }
    auto childNodesNew = children;
    if (SystemProperties::GetContainerDeleteFlag()) {
        auto frameNode = GetHost();
        if (frameNode->GetIsDelete()) {
            return;
        }
        childNodesNew.clear();
        GetLiveChildren(frameNode, childNodesNew);
    }
    // now rsNode's children, key is id of rsNode, value means whether the node exists in previous children of rsNode.
    std::unordered_map<Rosen::RSNode::SharedPtr, bool> childNodeMap;
    auto nowRSNodes = GetChildrenRSNodes(childNodesNew, childNodeMap);
    std::vector<Rosen::RSNode::SharedPtr> childNodes;
    for (auto child : rsNode_->GetChildren()) {
        if (child.lock()) {
            childNodes.emplace_back(child.lock());
        }
    }
    if (nowRSNodes == childNodes) {
        return;
    }
    if (nowRSNodes.empty()) {
        rsNode_->ClearChildren();
        return;
    }
    // save a copy of previous children because for loop will delete child
    auto preChildNodes = rsNode_->GetChildren();
    for (auto node : preChildNodes) {
        if (node.lock() == nullptr) {
            continue;
        }
        auto iter = childNodeMap.find(node.lock());
        if (iter == childNodeMap.end()) {
            rsNode_->RemoveChildByNodeSelf(node);
        } else {
            iter->second = true;
        }
    }
    for (size_t index = 0; index != nowRSNodes.size(); ++index) {
        auto node = rsNode_->GetChildByIndex(index);
        if (node != nowRSNodes[index]) {
            auto iter = childNodeMap.find(nowRSNodes[index]);
            if (iter == childNodeMap.end()) {
                continue;
            }
            if (iter->second) {
                rsNode_->MoveChild(nowRSNodes[index], index);
            } else {
                rsNode_->AddChild(nowRSNodes[index], index);
            }
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

    SetScale(scaleStart, scaleStart);
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::Animate(rsUIContext, protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [this, scaleEnd]() { SetScale(scaleEnd, scaleEnd); });
    isHoveredScale_ = isHovered;
}

void RosenRenderContext::AnimateHoverEffectBoard(bool isHovered)
{
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

    rsNode_->SetBackgroundColor(highlightStart.GetValue());
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(themeDuration);
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::Animate(rsUIContext, protocol, Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2f, 0.0f, 0.2f, 1.0f),
        [rsNode = rsNode_, highlightEnd]() {
            CHECK_NULL_VOID(rsNode);
            rsNode->SetBackgroundColor(highlightEnd.GetValue());
        });
    hoveredColor_ = hoverColorTo;
    isHoveredBoard_ = isHovered;
}

void RosenRenderContext::UpdateBackBlurRadius(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurRadiusChanged(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    SetBackBlurFilter();
}

void RosenRenderContext::UpdateMotionBlur(const MotionBlurOption& motionBlurOption)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateForeground();
    groupProperty->propMotionBlur = motionBlurOption;
    Rosen::Vector2f anchor(motionBlurOption.anchor.x, motionBlurOption.anchor.y);
    rsNode_->SetMotionBlurPara(motionBlurOption.radius, anchor);
}

void RosenRenderContext::UpdateBackBlur(
    const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateBackground();
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckSystemAdaptationSame(sysOptions)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    groupProperty->propSysOptions = sysOptions;
    SetBackBlurFilter();
    if (blurOption.grayscale.size() > 1) {
        Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[0]);
        rsNode_->SetGreyCoef(grayScale);
    }
}

void RosenRenderContext::UpdateNodeBackBlur(const Dimension& radius, const BlurOption& blurOption)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateBackground();
    groupProperty->propBackdropBlurOption = blurOption;
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckBlurOptionChanged(blurOption)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    SetBackBlurFilter();
    if (blurOption.grayscale.size() > 1) {
        Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[1]);
        rsNode_->SetGreyCoef(grayScale);
    }
}

void RosenRenderContext::UpdateFrontBlurRadius(const Dimension& radius)
{
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurRadiusChanged(radius)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    SetFrontBlurFilter();
}

void RosenRenderContext::UpdateFrontBlur(
    const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(rsNode_);
    const auto& groupProperty = GetOrCreateForeground();
    if (groupProperty->CheckBlurRadiusChanged(radius) && groupProperty->CheckSysOptionsForBlurSame(sysOptions)) {
        // Same with previous value
        return;
    }
    groupProperty->propBlurRadius = radius;
    groupProperty->propSysOptionsForBlur = sysOptions;
    SetFrontBlurFilter();
    if (blurOption.grayscale.size() > 1) {
        Rosen::Vector2f grayScale(blurOption.grayscale[0], blurOption.grayscale[1]);
        rsNode_->SetGreyCoef(grayScale);
    }
}

Rosen::SHADOW_COLOR_STRATEGY RosenRenderContext::ToShadowColorStrategy(ShadowColorStrategy shadowColorStrategy)
{
    if (shadowColorStrategy == ShadowColorStrategy::NONE) {
        return Rosen::SHADOW_COLOR_STRATEGY::COLOR_STRATEGY_NONE;
    } else if (shadowColorStrategy == ShadowColorStrategy::AVERAGE) {
        return Rosen::SHADOW_COLOR_STRATEGY::COLOR_STRATEGY_AVERAGE;
    } else if (shadowColorStrategy == ShadowColorStrategy::PRIMARY) {
        return Rosen::SHADOW_COLOR_STRATEGY::COLOR_STRATEGY_MAIN;
    } else {
        return Rosen::SHADOW_COLOR_STRATEGY::COLOR_STRATEGY_NONE;
    }
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
    rsNode_->SetShadowIsFilled(shadow.GetIsFilled());
    rsNode_->SetShadowColorStrategy(ToShadowColorStrategy(shadow.GetShadowColorStrategy()));
    if (shadow.GetHardwareAcceleration()) {
        rsNode_->SetShadowElevation(shadow.GetElevation());
    } else {
        rsNode_->SetShadowRadius(DrawingDecorationPainter::ConvertRadiusToSigma(shadow.GetBlurRadius()));
    }
    RequestNextFrame();
}

void RosenRenderContext::OnBackBlendModeUpdate(BlendMode blendMode)
{
    CHECK_NULL_VOID(rsNode_);
    if (blendMode == BlendMode::BACK_COMPAT_SOURCE_IN) {
        rsNode_->SetBackgroundShader(nullptr);
        rsNode_->SetColorBlendMode(Rosen::RSColorBlendMode::NONE);
    } else {
        auto rsBlendMode = static_cast<Rosen::RSColorBlendMode>(blendMode);
        rsNode_->SetColorBlendMode(rsBlendMode);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnBackBlendApplyTypeUpdate(BlendApplyType blendApplyType)
{
    CHECK_NULL_VOID(rsNode_);
    if (blendApplyType == BlendApplyType::FAST) {
        rsNode_->SetColorBlendApplyType(Rosen::RSColorBlendApplyType::FAST);
    } else if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        rsNode_->SetColorBlendApplyType(Rosen::RSColorBlendApplyType::SAVE_LAYER_ALPHA);
    } else {
        rsNode_->SetColorBlendApplyType(Rosen::RSColorBlendApplyType::SAVE_LAYER);
    }
    RequestNextFrame();
}

void RosenRenderContext::UpdateBrightnessBlender(const OHOS::Rosen::BrightnessBlender* brightnessBlender)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(brightnessBlender);
    rsNode_->SetBlender(brightnessBlender);
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
    CHECK_NULL_VOID(rsNode_);
    if (!modifier) {
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
    CHECK_NULL_VOID(rsNode_);
    rsNode_->AddModifier(modifier);
}

void RosenRenderContext::RemoveModifier(const std::shared_ptr<Rosen::RSModifier>& modifier)
{
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(rsNode_);
    rsNode_->RemoveModifier(modifier);
}

// helper function to update one of the graphic effects
template<typename T, typename D>
void RosenRenderContext::UpdateGraphic(std::shared_ptr<T>& modifier, D data)
{
    CHECK_NULL_VOID(!RectIsNull());
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

void RosenRenderContext::OnFrontInvertUpdate(const InvertVariant& invert)
{
    CHECK_NULL_VOID(rsNode_);
    if (invert.index() == 0) {
        rsNode_->SetInvert(std::get<float>(invert));
    } else {
        InvertOption option = std::get<InvertOption>(invert);
        Rosen::Vector4f invertVector;
        invertVector.SetValues(option.low_, option.high_, option.threshold_, option.thresholdRange_);
        rsNode_->SetAiInvert(invertVector);
    }
    RequestNextFrame();
}

void RosenRenderContext::OnSystemBarEffectUpdate(bool systemBarEffect)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetSystemBarEffect();
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

void RosenRenderContext::OnMagnifierUpdate(const MagnifierParams& magnifierParams)
{
    CHECK_NULL_VOID(rsNode_);
    std::shared_ptr<Rosen::RSMagnifierParams> rsMagnifierParams(std::make_shared<Rosen::RSMagnifierParams>());
    rsMagnifierParams->factor_ = magnifierParams.factor_;
    rsMagnifierParams->width_ = magnifierParams.width_;
    rsMagnifierParams->height_ = magnifierParams.height_;
    rsMagnifierParams->borderWidth_ = magnifierParams.borderWidth_;
    rsMagnifierParams->cornerRadius_ = magnifierParams.cornerRadius_;
    rsMagnifierParams->offsetX_ = magnifierParams.offsetX_;
    rsMagnifierParams->offsetY_ = magnifierParams.offsetY_;
    rsMagnifierParams->shadowOffsetX_ = magnifierParams.shadowOffsetX_;
    rsMagnifierParams->shadowOffsetY_ = magnifierParams.shadowOffsetY_;
    rsMagnifierParams->shadowSize_ = magnifierParams.shadowSize_;
    rsMagnifierParams->shadowStrength_ = magnifierParams.shadowStrength_;
    rsMagnifierParams->gradientMaskColor1_ = magnifierParams.gradientMaskColor1_;
    rsMagnifierParams->gradientMaskColor2_ = magnifierParams.gradientMaskColor2_;
    rsMagnifierParams->outerContourColor1_ = magnifierParams.outerContourColor1_;
    rsMagnifierParams->outerContourColor2_ = magnifierParams.outerContourColor2_;
    rsNode_->SetMagnifierParams(rsMagnifierParams);
    RequestNextFrame();
}
void RosenRenderContext::OnDynamicDimDegreeUpdate(const float degree)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetDynamicDimDegree(degree);
    RequestNextFrame();
}

void RosenRenderContext::OnDynamicLightUpRateUpdate(const float rate)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetDynamicLightUpRate(rate);
    RequestNextFrame();
}

void RosenRenderContext::OnDynamicLightUpDegreeUpdate(const float degree)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetDynamicLightUpDegree(degree);
    RequestNextFrame();
}

void RosenRenderContext::OnBgDynamicBrightnessOptionUpdate(const std::optional<BrightnessOption>& brightnessOption)
{
    if (!brightnessOption.has_value()) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBgBrightnessParams({ brightnessOption->rate, brightnessOption->lightUpDegree,
        brightnessOption->cubicCoeff, brightnessOption->quadCoeff, brightnessOption->saturation,
        { brightnessOption->posRGB[0], brightnessOption->posRGB[1], brightnessOption->posRGB[2] },
        { brightnessOption->negRGB[0], brightnessOption->negRGB[1], brightnessOption->negRGB[2] } });
    rsNode_->SetBgBrightnessFract(brightnessOption->fraction);
    RequestNextFrame();
}

void RosenRenderContext::OnFgDynamicBrightnessOptionUpdate(const std::optional<BrightnessOption>& brightnessOption)
{
    if (!brightnessOption.has_value()) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFgBrightnessParams({ brightnessOption->rate, brightnessOption->lightUpDegree,
        brightnessOption->cubicCoeff, brightnessOption->quadCoeff, brightnessOption->saturation,
        { brightnessOption->posRGB[0], brightnessOption->posRGB[1], brightnessOption->posRGB[2] },
        { brightnessOption->negRGB[0], brightnessOption->negRGB[1], brightnessOption->negRGB[2] } });
    rsNode_->SetFgBrightnessFract(brightnessOption->fraction);
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
    NotifyHostTransformUpdated();
}

void RosenRenderContext::CleanTransition()
{
    propTransitionDisappearing_.reset();
    propTransitionDisappearing_.reset();
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

void RosenRenderContext::SetBackgroundShader(const std::shared_ptr<Rosen::RSShader>& shader)
{
    CHECK_NULL_VOID(rsNode_);
    // temporary code for back compat
    auto& graphicProps = GetOrCreateGraphics();
    if (graphicProps->GetBackBlendMode() == BlendMode::BACK_COMPAT_SOURCE_IN) {
        rsNode_->SetBackgroundShader(nullptr);
        return;
    }
    rsNode_->SetBackgroundShader(shader);
}

void RosenRenderContext::PaintGradient(const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto& gradientProperty = GetOrCreateGradient();
    Gradient gradient;
    if (gradientProperty->HasLastGradientType()) {
        switch (gradientProperty->GetLastGradientTypeValue()) {
            case GradientType::LINEAR:
                gradient = gradientProperty->GetLinearGradientValue();
                break;
            case GradientType::RADIAL:
                gradient = gradientProperty->GetRadialGradientValue();
                break;
            case GradientType::SWEEP:
                gradient = gradientProperty->GetSweepGradientValue();
                break;
            default:
                return;
        }
    } else {
        if (gradientProperty->HasLinearGradient()) {
            gradient = gradientProperty->GetLinearGradientValue();
        }
        if (gradientProperty->HasRadialGradient()) {
            gradient = gradientProperty->GetRadialGradientValue();
        }
        if (gradientProperty->HasSweepGradient()) {
            gradient = gradientProperty->GetSweepGradientValue();
        }
    }
    if (!gradientStyleModifier_) {
        gradientStyleModifier_ = std::make_shared<GradientStyleModifier>(WeakClaim(this));
        rsNode_->AddModifier(gradientStyleModifier_);
    }
    gradientStyleModifier_->SetGradient(gradient);
    gradientStyleModifier_->SetSizeF(frameSize);
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

void RosenRenderContext::PaintClipShape(const std::unique_ptr<ClipProperty>& clip, const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto basicShape = clip->GetClipShapeValue();
    auto rsPath = DrawingDecorationPainter::DrawingCreatePath(basicShape, frameSize);
    auto shapePath = Rosen::RSPath::CreateRSPath(rsPath);
    if (!clipBoundModifier_) {
        auto prop = std::make_shared<RSProperty<std::shared_ptr<Rosen::RSPath>>>(shapePath);
        clipBoundModifier_ = std::make_shared<Rosen::RSClipBoundsModifier>(prop);
        rsNode_->AddModifier(clipBoundModifier_);
    } else {
        auto property =
            std::static_pointer_cast<RSProperty<std::shared_ptr<Rosen::RSPath>>>(clipBoundModifier_->GetProperty());
        property->Set(shapePath);
    }
}

void RosenRenderContext::PaintClipMask(const std::unique_ptr<ClipProperty>& clip, const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto basicShape = clip->GetClipMaskValue();
    auto rsPath = DrawingDecorationPainter::DrawingCreatePath(basicShape, frameSize);

    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(basicShape->GetStrokeColor());
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(basicShape->GetStrokeWidth());

    auto maskPath =
        Rosen::RSMask::CreatePathMask(rsPath, pen, DrawingDecorationPainter::CreateMaskDrawingBrush(basicShape));
    if (!clipMaskModifier_) {
        auto prop = std::make_shared<RSProperty<std::shared_ptr<RSMask>>>(maskPath);
        clipMaskModifier_ = std::make_shared<Rosen::RSMaskModifier>(prop);
        rsNode_->AddModifier(clipMaskModifier_);
    } else {
        auto property = std::static_pointer_cast<RSProperty<std::shared_ptr<RSMask>>>(clipMaskModifier_->GetProperty());
        property->Set(maskPath);
    }
}

void RosenRenderContext::PaintClip(const SizeF& frameSize)
{
    CHECK_NULL_VOID(rsNode_);
    auto& clip = GetOrCreateClip();
    if (clip->HasClipShape()) {
        PaintClipShape(clip, frameSize);
    }

    if (clip->HasClipMask()) {
        PaintClipMask(clip, frameSize);
    }
}

void RosenRenderContext::PaintProgressMask()
{
    CHECK_NULL_VOID(rsNode_);
    if (!moonProgressModifier_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        moonProgressModifier_ = AceType::MakeRefPtr<MoonProgressModifier>(host);
        auto modifierAdapter =
            std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(moonProgressModifier_));
        rsNode_->AddModifier(modifierAdapter);
        modifierAdapter->AttachProperties();
    }
    auto progress = GetProgressMaskValue();
    moonProgressModifier_->SetMaskColor(LinearColor(progress->GetColor()));
    moonProgressModifier_->SetMaxValue(progress->GetMaxValue());
    if (progress->GetValue() > moonProgressModifier_->GetMaxValue()) {
        progress->SetValue(moonProgressModifier_->GetMaxValue());
    }
    moonProgressModifier_->SetValue(progress->GetValue());
    moonProgressModifier_->SetEnableBreathe(progress->GetEnableBreathe());
}

void RosenRenderContext::SetClipBoundsWithCommands(const std::string& commands)
{
    CHECK_NULL_VOID(rsNode_);
    RSRecordingPath rsPath;
    rsPath.BuildFromSVGString(commands);
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
}

void RosenRenderContext::ClipWithRect(const RectF& rectF)
{
    CHECK_NULL_VOID(rsNode_);
    RSRecordingPath rsPath;
    rsPath.AddRect({ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() });
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
}

void RosenRenderContext::ClipWithRoundRect(const RoundRect& roundRect)
{
    CHECK_NULL_VOID(rsNode_);
    RSRoundRect rsRoundRect;

    RSRect rsRect(roundRect.GetRect().Left(), roundRect.GetRect().Top(), roundRect.GetRect().Right(),
        roundRect.GetRect().Bottom());
    rsRoundRect.SetRect(rsRect);

    EdgeF edge = roundRect.GetCornerRadius(RoundRect::TOP_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::TOP_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, edge.x, edge.y);
    RSRecordingPath rsPath;
    rsPath.AddRoundRect(rsRoundRect);
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
}

void RosenRenderContext::ClipWithOval(const RectF& rectF)
{
    CHECK_NULL_VOID(rsNode_);
    RSRecordingPath rsPath;
    rsPath.AddOval({ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() });
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
}

void RosenRenderContext::ClipWithCircle(const Circle& circle)
{
    CHECK_NULL_VOID(rsNode_);
    RSRecordingPath rsPath;
    rsPath.AddCircle(circle.GetAxisX().Value(), circle.GetAxisY().Value(), circle.GetRadius().Value());
    rsNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
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

void RosenRenderContext::SetContentClip(const std::variant<RectF, RefPtr<ShapeRect>>& rect)
{
    CHECK_NULL_VOID(rsNode_);
    RectF rectF;
    Rosen::Vector4f clipRect;
    if (std::holds_alternative<RectF>(rect)) {
        rectF = std::get<RectF>(rect);
        clipRect =
            Rosen::Vector4f{ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() };
    } else {
        auto shape = std::get<RefPtr<ShapeRect>>(rect);
        CHECK_NULL_VOID(shape);
        using helper = DrawingDecorationPainter;

        const float x =
            helper::DrawingDimensionToPx(shape->GetOffset().GetX(), paintRect_.GetSize(), LengthMode::HORIZONTAL);
        const float y =
            helper::DrawingDimensionToPx(shape->GetOffset().GetY(), paintRect_.GetSize(), LengthMode::VERTICAL);
        const float width =
            helper::DrawingDimensionToPx(shape->GetWidth(), paintRect_.GetSize(), LengthMode::HORIZONTAL);
        const float height =
            helper::DrawingDimensionToPx(shape->GetHeight(), paintRect_.GetSize(), LengthMode::VERTICAL);
        rectF = RectF(x, y, width, height);
        clipRect = Rosen::Vector4f{ x, y, x + width, y + height };
    }
    if (!customClipToFrameModifier_) {
        auto prop = std::make_shared<RSAnimatableProperty<Rosen::Vector4f>>(clipRect);
        customClipToFrameModifier_ = std::make_shared<Rosen::RSCustomClipToFrameModifier>(prop);
        rsNode_->AddModifier(customClipToFrameModifier_);
    } else {
        auto property = std::static_pointer_cast<RSAnimatableProperty<Rosen::Vector4f>>(
            customClipToFrameModifier_->GetProperty());
        property->Set(clipRect);
    }
    if (!contentClip_ || rectF != *contentClip_) {
        contentClip_ = std::make_unique<RectF>(rectF);
        GetHost()->AddFrameNodeChangeInfoFlag(FRAME_NODE_CONTENT_CLIP_CHANGE);
    }
}

void RosenRenderContext::ResetContentClip()
{
    if (customClipToFrameModifier_) {
        rsNode_->RemoveModifier(customClipToFrameModifier_);
        customClipToFrameModifier_.reset();
    }
    if (contentClip_) {
        contentClip_.reset();
    }
}

void RosenRenderContext::RemoveClipWithRRect()
{
    std::weak_ptr<Rosen::RSNode> weakRsNode = rsNode_;
    AnimationUtils::ExecuteWithoutAnimation([weakRsNode]() {
        auto rsNode = weakRsNode.lock();
        CHECK_NULL_VOID(rsNode);
        rsNode->SetClipRRect(nullptr);
    });
    RequestNextFrame();
}

void RosenRenderContext::OnClipShapeUpdate(const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(rsNode_);
    if (basicShape) {
        if (!RectIsNull()) {
            RectF rect = GetPaintRectWithoutTransform();
            PaintClipShape(GetOrCreateClip(), rect.GetSize());
        }
    } else if (clipBoundModifier_) {
        rsNode_->RemoveModifier(clipBoundModifier_);
        clipBoundModifier_ = nullptr;
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

void RosenRenderContext::OnClipMaskUpdate(const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(rsNode_);
    if (basicShape) {
        if (!RectIsNull()) {
            RectF rect = GetPaintRectWithoutTransform();
            PaintClipMask(GetOrCreateClip(), rect.GetSize());
        }
    } else if (clipMaskModifier_) {
        rsNode_->RemoveModifier(clipMaskModifier_);
        clipMaskModifier_ = nullptr;
    }
    RequestNextFrame();
}

void RosenRenderContext::OnProgressMaskUpdate(const RefPtr<ProgressMaskProperty>& progress)
{
    CHECK_NULL_VOID(rsNode_);
    if (progress) {
        if (!RectIsNull()) {
            PaintProgressMask();
        }
        rsNode_->SetClipToBounds(true);
    } else if (moonProgressModifier_) {
        auto modifierAdapter =
            std::static_pointer_cast<OverlayModifierAdapter>(ConvertOverlayModifier(moonProgressModifier_));
        rsNode_->RemoveModifier(modifierAdapter);
        moonProgressModifier_ = nullptr;
    }
    RequestNextFrame();
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
            auto paragraphSize = modifier_->GetParagraphSize(paintRect.Width());
            overlayRect = std::make_shared<Rosen::RectF>(overlayOffset.GetX(), overlayOffset.GetY(),
                std::max(paragraphSize.Width(), paintRect.Width()),
                std::max(paragraphSize.Height(), paintRect.Height()));
            rsNode_->SetIsCustomTextType(modifier_->IsCustomFont());
            UpdateDrawRegion(DRAW_REGION_OVERLAY_TEXT_MODIFIER_INDEX, overlayRect);
        } else {
            modifier_ = std::make_shared<OverlayTextModifier>();
            rsNode_->AddModifier(modifier_);
            modifier_->SetCustomData(NG::OverlayTextData(overlayText));
            auto overlayOffset = modifier_->GetOverlayOffset();
            auto paragraphSize = modifier_->GetParagraphSize(paintRect.Width());
            overlayRect = std::make_shared<Rosen::RectF>(overlayOffset.GetX(), overlayOffset.GetY(),
                std::max(paragraphSize.Width(), paintRect.Width()),
                std::max(paragraphSize.Height(), paintRect.Height()));
            rsNode_->SetIsCustomTextType(modifier_->IsCustomFont());
            UpdateDrawRegion(DRAW_REGION_OVERLAY_TEXT_MODIFIER_INDEX, overlayRect);
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
    if (!motionPath.IsValid()) {
        rsNode_->SetMotionPathOption(nullptr);
        return;
    }
    auto motionOption = Rosen::RSMotionPathOption(motionPath.GetPath());
    motionOption.SetBeginFraction(motionPath.GetBegin());
    motionOption.SetEndFraction(motionPath.GetEnd());
    motionOption.SetRotationMode(
        motionPath.GetRotate() ? Rosen::RotationMode::ROTATE_AUTO : Rosen::RotationMode::ROTATE_NONE);
    motionOption.SetPathNeedAddOrigin(HasOffset());
    rsNode_->SetMotionPathOption(std::make_shared<Rosen::RSMotionPathOption>(motionOption));
    RequestNextFrame();
}

void RosenRenderContext::OnLightPositionUpdate(const TranslateOptions& translate)
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
    rsNode_->SetLightPosition(xValue, yValue, zValue);
    RequestNextFrame();
}

void RosenRenderContext::OnLightIntensityUpdate(const float lightIntensity)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetLightIntensity(lightIntensity);
    RequestNextFrame();
}

void RosenRenderContext::OnLightColorUpdate(const Color& lightColor)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetLightColor(lightColor.GetValue());
    RequestNextFrame();
}

void RosenRenderContext::OnLightIlluminatedUpdate(const uint32_t lightIlluminated)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetIlluminatedType(lightIlluminated);
    RequestNextFrame();
}

void RosenRenderContext::OnIlluminatedBorderWidthUpdate(const Dimension& illuminatedBorderWidth)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetIlluminatedBorderWidth(static_cast<float>(illuminatedBorderWidth.ConvertToPx()));
    RequestNextFrame();
}

void RosenRenderContext::OnBloomUpdate(const float bloomIntensity)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBloom(bloomIntensity);
    RequestNextFrame();
}

void RosenRenderContext::SetSharedTranslate(float xTranslate, float yTranslate)
{
    if (!sharedTransitionModifier_) {
        sharedTransitionModifier_ = std::make_unique<SharedTransitionModifier>();
    }
    AddOrChangeTranslateModifier(rsNode_, sharedTransitionModifier_->translateXY,
        sharedTransitionModifier_->translateXYValue, { xTranslate, yTranslate });
    NotifyHostTransformUpdated();
}

void RosenRenderContext::ResetSharedTranslate()
{
    CHECK_NULL_VOID(sharedTransitionModifier_);
    CHECK_NULL_VOID(sharedTransitionModifier_->translateXY);
    CHECK_NULL_VOID(rsNode_);
    rsNode_->RemoveModifier(sharedTransitionModifier_->translateXY);
    sharedTransitionModifier_->translateXYValue = nullptr;
    sharedTransitionModifier_->translateXY = nullptr;
    NotifyHostTransformUpdated();
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

void RosenRenderContext::ClearChildren()
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->ClearChildren();
}

void RosenRenderContext::SetBounds(float positionX, float positionY, float width, float height)
{
    CHECK_NULL_VOID(rsNode_);
    paintRect_ = RectF(positionX, positionY, width, height);
    rsNode_->SetBounds(positionX, positionY, width, height);
}

void RosenRenderContext::SetUsingContentRectForRenderFrame(bool value, bool adjustRSFrameByContentRect)
{
    useContentRectForRSFrame_ = value;
    adjustRSFrameByContentRect_ = adjustRSFrameByContentRect;
}

void RosenRenderContext::SetSecurityLayer(bool isSecure)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetSecurityLayer(isSecure);
}

void RosenRenderContext::SetHDRBrightness(float hdrBrightness)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetHDRBrightness(hdrBrightness);
}

void RosenRenderContext::SetImageHDRPresent(bool hdrPresent)
{
    auto rsCanvasDrawingNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
    CHECK_NULL_VOID(rsCanvasDrawingNode);
    rsCanvasDrawingNode->SetHDRPresent(hdrPresent);
}

void RosenRenderContext::SetImageHDRBrightness(float hdrBrightness)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetHDRBrightness(hdrBrightness);
}

void RosenRenderContext::SetTransparentLayer(bool isTransparentLayer)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetHardwareEnableHint(isTransparentLayer);
}

void RosenRenderContext::SetScreenId(uint64_t screenId)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetSourceVirtualDisplayId(screenId);
}

void RosenRenderContext::SetAlwaysSnapshot(bool enable)
{
    CHECK_NULL_VOID(rsNode_);
    if (rsNode_->GetType() != Rosen::RSUINodeType::EFFECT_NODE) {
        return;
    }
    rsNode_->SetAlwaysSnapshot(enable);
}

void RosenRenderContext::SetFrameGravity(OHOS::Rosen::Gravity gravity)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFrameGravity(gravity);
}

void RosenRenderContext::SetUIFirstSwitch(OHOS::Rosen::RSUIFirstSwitch uiFirstSwitch)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetUIFirstSwitch(uiFirstSwitch);
}

int32_t RosenRenderContext::CalcExpectedFrameRate(const std::string& scene, float speed)
{
    if (rsNode_ == nullptr) {
        return 0;
    }
    return rsNode_->CalcExpectedFrameRate(scene, speed);
}

bool RosenRenderContext::DoTextureExport(uint64_t surfaceId)
{
    CHECK_NULL_RETURN(rsNode_, false);
    rsNode_->RemoveFromTree();
    if (!rsTextureExport_) {
        rsTextureExport_ = std::make_shared<Rosen::RSTextureExport>(rsNode_, surfaceId);
    }
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    if (rsSurfaceNode) {
        rsSurfaceNode->SetTextureExport(true);
    }
    return rsTextureExport_->DoTextureExport();
}

bool RosenRenderContext::StopTextureExport()
{
    CHECK_NULL_RETURN(rsNode_, false);
    CHECK_NULL_RETURN(rsTextureExport_, false);
    rsTextureExport_->StopTextureExport();
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    if (rsSurfaceNode) {
        rsSurfaceNode->SetTextureExport(false);
    }
    return true;
}

void RosenRenderContext::SetSurfaceRotation(bool isLock)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    if (rsSurfaceNode) {
        rsSurfaceNode->SetForceHardwareAndFixRotation(isLock);
    }
}

void RosenRenderContext::SetRenderFit(RenderFit renderFit)
{
    CHECK_NULL_VOID(rsNode_);
    propRenderFit_ = renderFit;
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    if (rsSurfaceNode) {
        rsSurfaceNode->SetFrameGravity(GetRosenGravity(renderFit));
    }
}

void RosenRenderContext::ClearDrawCommands()
{
    StartRecording();
    StopRecordingIfNeeded();
}

void RosenRenderContext::RemoveContentModifier(const RefPtr<ContentModifier>& modifier)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(modifier);
    auto modifierAdapter = std::static_pointer_cast<ContentModifierAdapter>(ConvertContentModifier(modifier));
    CHECK_NULL_VOID(modifierAdapter);
    rsNode_->RemoveModifier(modifierAdapter);
}

void RosenRenderContext::SetRSNode(const std::shared_ptr<RSNode>& externalNode)
{
    // Update rsNode_ to externalNode.
    if (externalNode == rsNode_) {
        return;
    }
    rsNode_ = externalNode;
    AddFrameNodeInfoToRsNode();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddExtraCustomProperty("RS_NODE", rsNode_.get());

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
        return;
    }
    PaintMouseSelectRect(rect, fillColor, strokeColor);
    RequestNextFrame();
}

void RosenRenderContext::PaintMouseSelectRect(const RectF& rect, const Color& fillColor, const Color& strokeColor)
{
    CHECK_NULL_VOID(rsNode_);
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
        rsCanvas.DetachPen();
    };

    mouseSelectModifier_ = std::make_shared<MouseSelectModifier>();
    mouseSelectModifier_->SetPaintTask(std::move(paintTask));
    rsNode_->AddModifier(mouseSelectModifier_);
}

void RosenRenderContext::DumpInfo()
{
    if (rsNode_) {
        DumpLog::GetInstance().AddDesc("------------start print rsNode");
        DumpLog::GetInstance().AddDesc(rsNode_->DumpNode(0));
        auto center = rsNode_->GetStagingProperties().GetPivot();
        if (!NearEqual(center[0], 0.5) || !NearEqual(center[1], 0.5)) {
            DumpLog::GetInstance().AddDesc(std::string("Center: x:")
                                               .append(std::to_string(center[0]))
                                               .append(" y:")
                                               .append(std::to_string(center[1])));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetPivotZ())) {
            DumpLog::GetInstance().AddDesc(
                std::string("PivotZ:").append(std::to_string(rsNode_->GetStagingProperties().GetPivotZ())));
        }
        std::string res = "";
        if (!NearZero(rsNode_->GetStagingProperties().GetRotation())) {
            res.append(" Rotation:").append(std::to_string(rsNode_->GetStagingProperties().GetRotation()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetRotationX())) {
            res.append(" RotationX:").append(std::to_string(rsNode_->GetStagingProperties().GetRotationX()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetRotationY())) {
            res.append(" RotationY:").append(std::to_string(rsNode_->GetStagingProperties().GetRotationY()));
        }
        if (!res.empty()) {
            DumpLog::GetInstance().AddDesc(res);
            res.clear();
        }
        const auto& groupProperty = GetOrCreateBackground();
        if (groupProperty->propEffectOption.has_value()) {
            auto backgroundEffect = groupProperty->propEffectOption->ToJsonValue()->ToString();
            DumpLog::GetInstance().AddDesc(std::string("backgroundEffect:").append(backgroundEffect));
        }
        if (groupProperty->propSysOptions.has_value()) {
            DumpLog::GetInstance().AddDesc(
                std::string("backDisable:")
                    .append(std::to_string(groupProperty->propSysOptions->disableSystemAdaptation)));
        }
        const auto& foregroundProperty = GetOrCreateForeground();
        if (foregroundProperty->propSysOptionsForBlur.has_value()) {
            DumpLog::GetInstance().AddDesc(
                std::string("blurDisable:")
                    .append(std::to_string(foregroundProperty->propSysOptionsForBlur->disableSystemAdaptation)));
        }
        auto&& graphicProps = GetOrCreateGraphics();
        if (graphicProps->propFgDynamicBrightnessOption.has_value()) {
            auto fgDynamicBrightness = graphicProps->propFgDynamicBrightnessOption->GetJsonObject();
            DumpLog::GetInstance().AddDesc(
                std::string("foregroundBrightness:").append(fgDynamicBrightness->ToString().c_str()));
        }
        if (graphicProps->propBgDynamicBrightnessOption.has_value()) {
            auto bgDynamicBrightness = graphicProps->propBgDynamicBrightnessOption->GetJsonObject();
            DumpLog::GetInstance().AddDesc(
                std::string("backgroundBrightnessInternal:").append(bgDynamicBrightness->ToString().c_str()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetCameraDistance())) {
            DumpLog::GetInstance().AddDesc(
                std::string("CameraDistance:")
                    .append(std::to_string(rsNode_->GetStagingProperties().GetCameraDistance())));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetTranslateZ())) {
            DumpLog::GetInstance().AddDesc(
                std::string("TranslateZ:").append(std::to_string(rsNode_->GetStagingProperties().GetTranslateZ())));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetBgImageWidth())) {
            res.append(" BgImageWidth:").append(std::to_string(rsNode_->GetStagingProperties().GetBgImageWidth()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetBgImageHeight())) {
            res.append(" BgImageHeight:").append(std::to_string(rsNode_->GetStagingProperties().GetBgImageHeight()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetBgImagePositionX())) {
            res.append(" BgImagePositionX")
                .append(std::to_string(rsNode_->GetStagingProperties().GetBgImagePositionX()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetBgImagePositionY())) {
            res.append(" BgImagePositionY")
                .append(std::to_string(rsNode_->GetStagingProperties().GetBgImagePositionY()));
        }
        if (!res.empty()) {
            DumpLog::GetInstance().AddDesc(res);
            res.clear();
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetShadowOffsetX())) {
            res.append(" ShadowOffsetX:").append(std::to_string(rsNode_->GetStagingProperties().GetShadowOffsetX()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetShadowOffsetY())) {
            res.append(" ShadowOffsetY:").append(std::to_string(rsNode_->GetStagingProperties().GetShadowOffsetY()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetShadowAlpha())) {
            res.append(" ShadowAlpha:").append(std::to_string(rsNode_->GetStagingProperties().GetShadowAlpha()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetShadowElevation())) {
            res.append(" ShadowElevation:")
                .append(std::to_string(rsNode_->GetStagingProperties().GetShadowElevation()));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetShadowRadius())) {
            res.append(" ShadowRadius:").append(std::to_string(rsNode_->GetStagingProperties().GetShadowRadius()));
        }
        if (!res.empty()) {
            DumpLog::GetInstance().AddDesc(res);
            res.clear();
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetSpherizeDegree())) {
            DumpLog::GetInstance().AddDesc(
                std::string("SpherizeDegree:")
                    .append(std::to_string(rsNode_->GetStagingProperties().GetSpherizeDegree())));
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetLightUpEffectDegree())) {
            DumpLog::GetInstance().AddDesc(
                std::string("LightUpEffectDegree:")
                    .append(std::to_string(rsNode_->GetStagingProperties().GetLightUpEffectDegree())));
        }
        if (!NearEqual(rsNode_->GetStagingProperties().GetAlpha(), 1)) {
            DumpLog::GetInstance().AddDesc(
                std::string("Alpha:").append(std::to_string(rsNode_->GetStagingProperties().GetAlpha())));
        }
        auto translate = rsNode_->GetStagingProperties().GetTranslate();
        if (!(NearZero(translate[0]) && NearZero(translate[1]))) {
            DumpLog::GetInstance().AddDesc(
                std::string("translate(x,y): ")
                    .append(std::to_string(translate[0]).append(",").append(std::to_string(translate[1]))));
        }
        auto scale = rsNode_->GetStagingProperties().GetScale();
        if (!(NearEqual(scale[0], 1) && NearEqual(scale[1], 1))) {
            DumpLog::GetInstance().AddDesc(
                std::string("scale(x,y): ")
                    .append(std::to_string(scale[0]).append(",").append(std::to_string(scale[1]))));
        }
        auto rect = GetPaintRectWithoutTransform();
        if (HasTransformTranslate()) {
            auto translateArk = GetTransformTranslate().value();
            auto arkTranslateX = translateArk.x.ConvertToPxWithSize(rect.Width());
            auto arkTranslateY = translateArk.y.ConvertToPxWithSize(rect.Height());
            if (!NearEqual(arkTranslateX, translate[0])) {
                DumpLog::GetInstance().AddDesc(
                    std::string("TranlateX has difference,arkui:").append(std::to_string(arkTranslateX)));
            }
            if (!NearEqual(arkTranslateY, translate[1])) {
                DumpLog::GetInstance().AddDesc(
                    std::string("TranlateY has difference,arkui:").append(std::to_string(arkTranslateY)));
            }
        }
        if (HasTransformScale()) {
            auto arkTransformScale = GetTransformScale().value();
            if (!NearEqual(arkTransformScale.x, scale[0])) {
                DumpLog::GetInstance().AddDesc(
                    std::string("scaleX has difference,arkui:").append(std::to_string(arkTransformScale.x)));
            }
            if (!NearEqual(arkTransformScale.y, scale[1])) {
                DumpLog::GetInstance().AddDesc(
                    std::string("scaleY has difference,arkui:").append(std::to_string(arkTransformScale.y)));
            }
        }
        if (HasOpacity()) {
            auto arkAlpha = GetOpacity();
            if (!NearEqual(arkAlpha.value(), rsNode_->GetStagingProperties().GetAlpha())) {
                DumpLog::GetInstance().AddDesc(
                    std::string("Alpha has difference,arkui:").append(std::to_string(arkAlpha.value())));
            }
        }
        if (HasPosition()) {
            auto position = GetPosition();
            DumpLog::GetInstance().AddDesc(std::string("PositionX :")
                                               .append(position->GetX().ToString().c_str())
                                               .append(std::string(",PositionY :"))
                                               .append(position->GetY().ToString().c_str()));
        }
        if (HasOffset()) {
            auto offset = GetOffset();
            DumpLog::GetInstance().AddDesc(std::string("OffsetX :")
                                               .append(offset->GetX().ToString().c_str())
                                               .append(std::string(",OffsetY :"))
                                               .append(offset->GetY().ToString().c_str()));
        }
        if (HasPositionEdges()) {
            auto positionEdges = GetPositionEdges();
            DumpLog::GetInstance().AddDesc(std::string("positionEdges :").append(positionEdges->ToString().c_str()));
        }
        if (HasOffsetEdges()) {
            auto offsetEdges = GetOffsetEdges();
            DumpLog::GetInstance().AddDesc(std::string("offsetEdges :").append(offsetEdges->ToString().c_str()));
        }
        if (HasAnchor()) {
            auto anchor = GetAnchor();
            DumpLog::GetInstance().AddDesc(std::string("anchorX :")
                                               .append(anchor->GetX().ToString().c_str())
                                               .append(std::string(",anchorY :"))
                                               .append(anchor->GetY().ToString().c_str()));
        }

        auto rsBlendMode = static_cast<int16_t>(rsNode_->GetStagingProperties().GetColorBlendMode());
        if (GetBackBlendMode().has_value() || rsBlendMode) {
            DumpLog::GetInstance().AddDesc(
                std::string("blendMode:") + std::to_string(rsBlendMode));
            auto blendMode = static_cast<int16_t>(GetBackBlendMode().value_or(BlendMode::NONE));
            if (rsBlendMode != blendMode) {
                DumpLog::GetInstance().AddDesc(
                    std::string("blendMode has difference,arkui:") + std::to_string(blendMode));
            }
        }
        
        auto rsBlendApplyType = static_cast<int16_t>(rsNode_->GetStagingProperties().GetColorBlendApplyType());
        if (GetBackBlendApplyType().has_value() || rsBlendApplyType) {
            DumpLog::GetInstance().AddDesc(
                std::string("blendApplyType:") + std::to_string(rsBlendApplyType));
            auto blendApplyType = static_cast<int16_t>(GetBackBlendApplyType().value_or(BlendApplyType::FAST));
            if (rsBlendApplyType != blendApplyType) {
                DumpLog::GetInstance().AddDesc(
                    std::string("blendApplyType has difference,arkui:") + std::to_string(blendApplyType));
            }
        }
    }
    if (disappearingTransitionCount_) {
        DumpLog::GetInstance().AddDesc(
            std::string("transitionCnt:").append(std::to_string(disappearingTransitionCount_))
        );
    }
}

void RosenRenderContext::DumpAdvanceInfo()
{
    if (GetBackgroundAlign().has_value()) {
        DumpLog::GetInstance().AddDesc("BackgroundAlign:" + GetBackgroundAlign().value().ToString());
    }
    if (GetBackgroundImage().has_value()) {
        DumpLog::GetInstance().AddDesc("BackgroundImage:" + GetBackgroundImage().value().ToString());
    }
    if (GetSphericalEffect().has_value()) {
        DumpLog::GetInstance().AddDesc("SphericalEffect:" + std::to_string(GetSphericalEffect().value()));
    }
    if (GetPixelStretchEffect().has_value()) {
        DumpLog::GetInstance().AddDesc("PixelStretchEffect:" + GetPixelStretchEffect().value().ToString());
    }
    if (GetLightUpEffect().has_value()) {
        DumpLog::GetInstance().AddDesc("LightUpEffect:" + std::to_string(GetLightUpEffect().value()));
    }
    if (GetBorderColor().has_value()) {
        DumpLog::GetInstance().AddDesc("BorderColor:" + GetBorderColor().value().ToString());
    }
    if (GetBorderWidth().has_value()) {
        DumpLog::GetInstance().AddDesc("BorderWidth:" + GetBorderWidth().value().ToString());
    }
    if (GetOuterBorderRadius().has_value()) {
        DumpLog::GetInstance().AddDesc("OuterBorderRadius:" + GetOuterBorderRadius().value().ToString());
    }
    if (GetOuterBorderColor().has_value()) {
        DumpLog::GetInstance().AddDesc("OuterBorderColor:" + GetOuterBorderColor().value().ToString());
    }
    if (GetOuterBorderWidth().has_value()) {
        DumpLog::GetInstance().AddDesc("OuterBorderWidth:" + GetOuterBorderWidth().value().ToString());
    }
    if (GetDynamicLightUpRate().has_value()) {
        DumpLog::GetInstance().AddDesc("DynamicLightUpRate:" + std::to_string(GetDynamicLightUpRate().value()));
    }
    if (GetDynamicLightUpDegree().has_value()) {
        DumpLog::GetInstance().AddDesc("DynamicLightUpDegree:" + std::to_string(GetDynamicLightUpDegree().value()));
    }
    if (GetBackBlendMode().has_value()) {
        DumpLog::GetInstance().AddDesc("BlendMode:" + std::to_string(static_cast<int>(GetBackBlendMode().value())));
    }
    if (GetLinearGradient().has_value()) {
        DumpLog::GetInstance().AddDesc("LinearGradient:" + GetLinearGradient().value().ToString());
    }
    if (GetSweepGradient().has_value()) {
        DumpLog::GetInstance().AddDesc("SweepGradient:" + GetSweepGradient().value().ToString());
    }
    if (GetRadialGradient().has_value()) {
        DumpLog::GetInstance().AddDesc("RadialGradient:" + GetRadialGradient().value().ToString());
    }
    if (GetFrontBrightness().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontBrightness:" + GetFrontBrightness().value().ToString());
    }
    if (GetFrontGrayScale().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontGrayScale:" + GetFrontGrayScale().value().ToString());
    }
    if (GetFrontContrast().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontContrast:" + GetFrontContrast().value().ToString());
    }
    if (GetFrontSaturate().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontSaturate:" + GetFrontSaturate().value().ToString());
    }
    if (GetFrontSepia().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontSepia:" + GetFrontSepia().value().ToString());
    }
    if (GetFrontHueRotate().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontHueRotate:" + std::to_string(GetFrontHueRotate().value()));
    }
    if (GetFrontColorBlend().has_value()) {
        DumpLog::GetInstance().AddDesc("FrontColorBlend:" + GetFrontColorBlend().value().ColorToString());
    }
    if (GetBorderImageSource().has_value()) {
        DumpLog::GetInstance().AddDesc("BorderImageSource:" + GetBorderImageSource().value().ToString());
    }
    if (GetBorderImageGradient().has_value()) {
        DumpLog::GetInstance().AddDesc("BorderImageGradient:" + GetBorderImageGradient().value().ToString());
    }
    if (GetForegroundColor().has_value()) {
        DumpLog::GetInstance().AddDesc("ForegroundColor:" + GetForegroundColor().value().ColorToString());
    }
    if (GetLightIntensity().has_value()) {
        DumpLog::GetInstance().AddDesc("LightIntensity:" + std::to_string(GetLightIntensity().value()));
    }
    if (GetLightIlluminated().has_value()) {
        DumpLog::GetInstance().AddDesc("LightIlluminated:" + std::to_string(GetLightIlluminated().value()));
    }
    if (GetIlluminatedBorderWidth().has_value()) {
        DumpLog::GetInstance().AddDesc("IlluminatedBorderWidth:" + GetIlluminatedBorderWidth().value().ToString());
    }
    if (GetBloom().has_value()) {
        DumpLog::GetInstance().AddDesc("Bloom:" + std::to_string(GetBloom().value()));
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
        transitionEffect_->Detach(this);
    }
    transitionEffect_ = RosenTransitionEffect::ConvertToRosenTransitionEffect(effect);
    hasDefaultTransition_ = false;
    CHECK_NULL_VOID(transitionEffect_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    bool isOnTheTree = frameNode->IsOnMainTree();
    CHECK_NULL_VOID(rsNode_);
    auto rsUIContext = rsNode_->GetRSUIContext();
    // transition effects should be initialized without animation.
    RSNode::ExecuteWithoutAnimation([this, isOnTheTree]() {
        // transitionIn effects should be initialized as active if currently not on the tree.
        transitionEffect_->Attach(Claim(this), !isOnTheTree);
        }, rsUIContext);
}

void RosenRenderContext::NotifyTransition(bool isTransitionIn)
{
    CHECK_NULL_VOID(transitionEffect_);

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rsNode_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::ExecuteWithoutAnimation([this, &frameNode, isTransitionIn, &pipeline]() {
            if (isTransitionIn && disappearingTransitionCount_ == 0 && appearingTransitionCount_ == 0) {
                // transitionIn, reset to state before attaching in case of node reappear
                transitionEffect_->Attach(Claim(this), true);
            }

            SizeF rootSize(pipeline->GetRootWidth(), pipeline->GetRootHeight());
            auto parentOffset = frameNode->GetPaintRectOffset(true);
            auto rect = GetPaintRectWithoutTransform();
            // Do not consider the position after its own transform,
            // as the transition modifier also affects the transform
            rect.SetOffset(parentOffset + rect.GetOffset());

            transitionEffect_->UpdateTransitionContext(Claim(this), rect, rootSize);
        }, rsUIContext);

    if (isTransitionIn) {
        // Isolate the animation callback function, to avoid changing the callback timing of current implicit animation.
        AnimationUtils::AnimateWithCurrentOptions(
            [this]() {
                transitionEffect_->Appear();
                ++appearingTransitionCount_;
            },
            [weakThis = WeakClaim(this)]() {
                auto context = weakThis.Upgrade();
                CHECK_NULL_VOID(context);
                context->OnTransitionInFinish();
            },
            false, pipeline);
    } else {
        if (!transitionEffect_->HasDisappearTransition()) {
            if (frameNode->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
                auto frameParent = frameNode->GetAncestorNodeOfFrame(false);
                CHECK_NULL_VOID(frameParent);
                // for window surfaceNode, remove surfaceNode explicitly
                frameParent->GetRenderContext()->RemoveChild(Claim(this));
            }
            if (transitionUserCallback_ && !disappearingTransitionCount_) {
                PostTransitionUserOutCallback();
            }
            return;
        }
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
                // update transition out count
                context->OnTransitionOutFinish();
            },
            false, pipeline);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->NotifyTransformInfoChanged();
    host->OnNodeTransitionInfoUpdate();
}

void RosenRenderContext::RemoveDefaultTransition()
{
    if (hasDefaultTransition_ && transitionEffect_ && disappearingTransitionCount_ == 0 &&
        appearingTransitionCount_ == 0) {
        transitionEffect_->Detach(this);
        transitionEffect_ = nullptr;
        hasDefaultTransition_ = false;
    }
}

void RosenRenderContext::OnTransitionInFinish()
{
    --appearingTransitionCount_;
    // make sure we are the last transition out animation, if not, return.
    if (appearingTransitionCount_ > 0) {
        return;
    }
    if (appearingTransitionCount_ < 0) {
        appearingTransitionCount_ = 0;
    }
    // when all transition in/out animations are finished, we should remove the default transition effect.
    RemoveDefaultTransition();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireTransitionUserCallback(true);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    if (host->IsVisible()) {
        // trigger transition through visibility
        if (transitionInCallback_) {
            transitionInCallback_();
        }
    }
}

void RosenRenderContext::OnTransitionOutFinish()
{
    // update transition out count
    --disappearingTransitionCount_;
    // make sure we are the last transition out animation, if not, return.
    if (disappearingTransitionCount_ > 0) {
        return;
    }
    if (disappearingTransitionCount_ < 0) {
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
        if (host->IsOnMainTree()) {
            if (transitionOutCallback_) {
                transitionOutCallback_();
            }
            parent->MarkNeedSyncRenderTree();
            parent->RebuildRenderContextTree();
            FireTransitionUserCallback(false);
            return;
        }
        parent->MarkNeedSyncRenderTree();
        parent->RebuildRenderContextTree();
    }
    RefPtr<UINode> breakPointChild = host;
    RefPtr<UINode> breakPointParent = breakPointChild->GetParent();
    UINode::GetBestBreakPoint(breakPointChild, breakPointParent);
    // if can not find the breakPoint, means the node is not disappearing (reappear? or the node of subtree), return.
    if (!breakPointParent) {
        FireTransitionUserCallback(false);
        return;
    }
    if (breakPointChild->RemoveImmediately()) {
        breakPointChild->OnRemoveFromParent(false);
        // remove breakPoint
        breakPointParent->RemoveDisappearingChild(breakPointChild);
        breakPointParent->MarkNeedSyncRenderTree();
        breakPointParent->RebuildRenderContextTree();
    }
    if (isModalRootNode_ && breakPointParent->GetChildren().empty()) {
        auto grandParent = breakPointParent->GetParent();
        CHECK_NULL_VOID(grandParent);
        grandParent->RemoveChild(breakPointParent);
        grandParent->RebuildRenderContextTree();
    }
    FireTransitionUserCallback(false);
}

void RosenRenderContext::FireTransitionUserCallback(bool isTransitionIn)
{
    if (transitionUserCallback_) {
        auto callback = transitionUserCallback_;
        callback(isTransitionIn);
    }
}

void RosenRenderContext::PostTransitionUserOutCallback()
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    // post the callback to let it run on isolate environment
    taskExecutor->PostTask(
        [callback = transitionUserCallback_]() {
            if (callback) {
                callback(false);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUITransitionOutFinishCallback", PriorityType::HIGH);
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

void RosenRenderContext::DetachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyBase>& property)
{
    CHECK_NULL_VOID(rsNode_);
    CHECK_NULL_VOID(property);
    std::shared_ptr<RSNodeModifierImpl> modifier =
        std::static_pointer_cast<RSNodeModifierImpl>(property->GetModifyImpl());
    RemoveModifier(modifier);
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

void RosenRenderContext::RegisterSharedTransition(const RefPtr<RenderContext>& other, const bool isInSameWindow)
{
    auto otherContext = AceType::DynamicCast<RosenRenderContext>(other);
    if (!otherContext) {
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::RegisterTransitionPair(rsUIContext, rsNode_->GetId(), otherContext->rsNode_->GetId(), isInSameWindow);
}

void RosenRenderContext::UnregisterSharedTransition(const RefPtr<RenderContext>& other)
{
    auto otherContext = AceType::DynamicCast<RosenRenderContext>(other);
    if (!otherContext) {
        // the paired node is already destroyed, we don't need to unregister it, Rosen will handle it.
        return;
    }
    CHECK_NULL_VOID(rsNode_);
    auto rsUIContext = rsNode_->GetRSUIContext();
    RSNode::UnregisterTransitionPair(rsUIContext, rsNode_->GetId(), otherContext->rsNode_->GetId());
}

inline void RosenRenderContext::ConvertRadius(const BorderRadiusProperty& value, Rosen::Vector4f& cornerRadius)
{
    cornerRadius.SetValues(static_cast<float>(value.radiusTopLeft.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusTopRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomRight.value_or(Dimension()).ConvertToPx()),
        static_cast<float>(value.radiusBottomLeft.value_or(Dimension()).ConvertToPx()));
}

void RosenRenderContext::PaintRSBgImage()
{
    auto image = DynamicCast<NG::DrawingImage>(bgImage_);
    CHECK_NULL_VOID(bgLoadingCtx_ && image);
    CHECK_NULL_VOID(rsNode_);
    auto rosenImage = std::make_shared<Rosen::RSImage>();
    auto compressData = image->GetCompressData();
    if (compressData) {
        rosenImage->SetCompressData(
            compressData, image->GetUniqueID(), image->GetCompressWidth(), image->GetCompressHeight());
    } else {
        rosenImage->SetImage(image->GetImage());
    }
    if (!HasValidBgImageResizable()) {
        rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
    }
    rsNode_->SetBgImage(rosenImage);
}

void RosenRenderContext::PaintPixmapBgImage()
{
    CHECK_NULL_VOID(rsNode_);
    auto image = DynamicCast<NG::PixelMapImage>(bgImage_);
    CHECK_NULL_VOID(bgLoadingCtx_ && image);
    auto pixmap = image->GetPixelMap();
    CHECK_NULL_VOID(pixmap);

    auto rosenImage = std::make_shared<Rosen::RSImage>();
    rosenImage->SetPixelMap(pixmap->GetPixelMapSharedPtr());
    if (!HasValidBgImageResizable()) {
        rosenImage->SetImageRepeat(static_cast<int>(GetBackgroundImageRepeat().value_or(ImageRepeat::NO_REPEAT)));
    }
    rsNode_->SetBgImage(rosenImage);
}

void RosenRenderContext::OnRenderGroupUpdate(bool isRenderGroup)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkNodeGroup(isRenderGroup);
}

void RosenRenderContext::UpdateRenderGroup(bool isRenderGroup, bool isForced, bool includeProperty)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkNodeGroup(isRenderGroup, isForced, includeProperty);
}

void RosenRenderContext::OnNodeNameUpdate(const std::string& id)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetNodeName(id);
}

void RosenRenderContext::OnSuggestedRenderGroupUpdate(bool isRenderGroup)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkNodeGroup(isRenderGroup, false);
}

void RosenRenderContext::OnRenderFitUpdate(RenderFit renderFit)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFrameGravity(GetRosenGravity(renderFit));
}

void RosenRenderContext::SetContentRectToFrame(RectF rect)
{
    CHECK_NULL_VOID(rsNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (adjustRSFrameByContentRect_) {
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto contentRect = geometryNode->GetContentRect();
        rect.SetOffset(rect.GetOffset() + contentRect.GetOffset());
        rect.SetSize(contentRect.GetSize());
    } else {
        auto&& padding = host->GetGeometryNode()->GetPadding();
        // minus padding to get contentRect
        if (padding) {
            rect.SetOffset(rect.GetOffset() + OffsetF { padding->left.value_or(0), padding->top.value_or(0) });
            auto size = rect.GetSize();
            MinusPaddingToSize(*padding, size);
            rect.SetSize(size);
        }
    }
    rsNode_->SetFrame(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
}

void RosenRenderContext::MarkNewFrameAvailable(void* nativeWindow)
{
    CHECK_NULL_VOID(rsNode_);
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
#if defined(ANDROID_PLATFORM)
    rsSurfaceNode->MarkUiFrameAvailable(true);
#endif
#if defined(IOS_PLATFORM)
#if defined(PLATFORM_VIEW_SUPPORTED)
    if (patternType_ == PatternType::PLATFORM_VIEW) {
        RSSurfaceExtConfig config = {
            .type = RSSurfaceExtType::SURFACE_PLATFORM_TEXTURE,
            .additionalData = nativeWindow,
        };
        rsSurfaceNode->SetSurfaceTexture(config);
        rsSurfaceNode->MarkUiFrameAvailable(true);
        return;
    }
#endif
    RSSurfaceExtConfig config = {
        .type = RSSurfaceExtType::SURFACE_TEXTURE,
        .additionalData = nativeWindow,
    };
    rsSurfaceNode->SetSurfaceTexture(config);
#endif
}

void RosenRenderContext::AddAttachCallBack(const std::function<void(int64_t, bool)>& attachCallback)
{
    CHECK_NULL_VOID(rsNode_);
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetSurfaceTextureAttachCallBack(attachCallback);
#endif
}

void RosenRenderContext::AddUpdateCallBack(const std::function<void(std::vector<float>&)>& updateCallback)
{
    CHECK_NULL_VOID(rsNode_);
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetSurfaceTextureUpdateCallBack(updateCallback);
#endif
}

void RosenRenderContext::AddInitTypeCallBack(const std::function<void(int32_t&)>& initTypeCallback)
{
    CHECK_NULL_VOID(rsNode_);
#if defined(IOS_PLATFORM)
    auto rsSurfaceNode = rsNode_->ReinterpretCastTo<Rosen::RSSurfaceNode>();
    CHECK_NULL_VOID(rsSurfaceNode);
    rsSurfaceNode->SetSurfaceTextureInitTypeCallBack(initTypeCallback);
#endif
}

bool RosenRenderContext::IsUniRenderEnabled()
{
    return Rosen::RSSystemProperties::GetUniRenderEnabled();
}

void RosenRenderContext::SetRotation(float rotationX, float rotationY, float rotationZ)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSRotationXModifier, float>(rotationXUserModifier_, rotationX);
    SetAnimatableProperty<Rosen::RSRotationYModifier, float>(rotationYUserModifier_, rotationY);
    SetAnimatableProperty<Rosen::RSRotationModifier, float>(rotationZUserModifier_, rotationZ);
    NotifyHostTransformUpdated();
}

void RosenRenderContext::SetShadowColor(uint32_t color)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetShadowColor(color);
}

void RosenRenderContext::SetShadowOffset(float offsetX, float offsetY)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetShadowOffset(offsetX, offsetY);
}

void RosenRenderContext::SetShadowAlpha(float alpha)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetShadowAlpha(alpha);
}

void RosenRenderContext::SetShadowElevation(float elevation)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetShadowElevation(elevation);
}

void RosenRenderContext::SetShadowRadius(float radius)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetShadowRadius(radius);
}

void RosenRenderContext::SetRenderFrameOffset(const OffsetF& offset)
{
    frameOffset_ = offset;
}

void RosenRenderContext::SetScale(float scaleX, float scaleY)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSScaleModifier, Rosen::Vector2f>(scaleXYUserModifier_, { scaleX, scaleY });
    NotifyHostTransformUpdated();
}

void RosenRenderContext::SetBackgroundColor(uint32_t colorValue)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetBackgroundColor(colorValue);
}

void RosenRenderContext::SetRenderPivot(float pivotX, float pivotY)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetPivot(pivotX, pivotY);
    NotifyHostTransformUpdated();
}

void RosenRenderContext::SetFrame(float positionX, float positionY, float width, float height)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->SetFrame(positionX, positionY, width, height);
}

void RosenRenderContext::SetOpacity(float opacity)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaUserModifier_, opacity);
}

void RosenRenderContext::SetOpacityMultiplier(float opacity)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaModifier_, opacity);
}

void RosenRenderContext::SetTranslate(float translateX, float translateY, float translateZ)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSTranslateModifier, Rosen::Vector2f>(
        translateXYUserModifier_, { translateX, translateY });
    SetAnimatableProperty<Rosen::RSTranslateZModifier, float>(translateZUserModifier_, translateZ);
    NotifyHostTransformUpdated();
}

void RosenRenderContext::SetTransitionInCallback(std::function<void()>&& callback)
{
    transitionInCallback_ = std::move(callback);
}

void RosenRenderContext::SetTransitionOutCallback(std::function<void()>&& callback)
{
    transitionOutCallback_ = std::move(callback);
}

void RosenRenderContext::SetTransitionUserCallback(TransitionFinishCallback&& callback)
{
    transitionUserCallback_ = std::move(callback);
}

OffsetF RosenRenderContext::GetBaseTransalteInXY() const
{
    OffsetF offset{ 0.0f, 0.0f };
    CHECK_NULL_RETURN(baseTranslateInXY_, offset);
    auto property = std::static_pointer_cast<RSAnimatableProperty<Rosen::Vector2f>>(baseTranslateInXY_->GetProperty());
    CHECK_NULL_RETURN(property, offset);
    auto vec2 = property->Get();
    offset = OffsetF{ vec2[0], vec2[1] };
    return offset;
}

void RosenRenderContext::SetBaseTranslateInXY(const OffsetF& offset)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSTranslateModifier, Rosen::Vector2f>(
        baseTranslateInXY_, { offset.GetX(), offset.GetY() });
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost());
    NotifyHostTransformUpdated();
}

float RosenRenderContext::GetBaseRotateInZ() const
{
    float rotate = 0.0f;
    CHECK_NULL_RETURN(baseRotateInZ_, rotate);
    auto property = std::static_pointer_cast<RSAnimatableProperty<float>>(baseRotateInZ_->GetProperty());
    CHECK_NULL_RETURN(property, rotate);
    rotate = property->Get();
    return rotate;
}

void RosenRenderContext::SetBaseRotateInZ(float degree)
{
    CHECK_NULL_VOID(rsNode_);
    SetAnimatableProperty<Rosen::RSRotationModifier, float>(baseRotateInZ_, degree);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost());
    NotifyHostTransformUpdated();
}

void RosenRenderContext::SetRectMask(const RectF& rect, const ShapeMaskProperty& property)
{
    CHECK_NULL_VOID(rsNode_);
    RSPath path;
    path.AddRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());

    RSBrush brush = GetRsBrush(property.fillColor);
    RSPen pen = GetRsPen(property.strokeColor, property.strokeWidth);

    std::shared_ptr<RSMask> mask = RSMask::CreatePathMask(path, pen, brush);
    rsNode_->SetMask(mask);
}

void RosenRenderContext::SetCircleMask(const Circle& circle, const ShapeMaskProperty& property)
{
    CHECK_NULL_VOID(rsNode_);
    RSPath path;
    path.AddCircle(circle.GetAxisX().Value(), circle.GetAxisY().Value(), circle.GetRadius().Value());

    RSBrush brush = GetRsBrush(property.fillColor);
    RSPen pen = GetRsPen(property.strokeColor, property.strokeWidth);

    std::shared_ptr<RSMask> mask = RSMask::CreatePathMask(path, pen, brush);
    rsNode_->SetMask(mask);
}

void RosenRenderContext::SetRoundRectMask(const RoundRect& roundRect, const ShapeMaskProperty& property)
{
    CHECK_NULL_VOID(rsNode_);
    RSRoundRect rsRoundRect;

    RSRect rsRect(roundRect.GetRect().Left(), roundRect.GetRect().Top(), roundRect.GetRect().Right(),
        roundRect.GetRect().Bottom());
    rsRoundRect.SetRect(rsRect);

    EdgeF edge = roundRect.GetCornerRadius(RoundRect::TOP_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::TOP_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, edge.x, edge.y);

    RSPath path;
    path.AddRoundRect(rsRoundRect);

    RSBrush brush = GetRsBrush(property.fillColor);
    RSPen pen = GetRsPen(property.strokeColor, property.strokeWidth);

    std::shared_ptr<RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNode_->SetMask(mask);
}

void RosenRenderContext::SetOvalMask(const RectF& rect, const ShapeMaskProperty& property)
{
    CHECK_NULL_VOID(rsNode_);
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    RSPath path;
    path.AddOval(rsRect);

    RSBrush brush = GetRsBrush(property.fillColor);
    RSPen pen = GetRsPen(property.strokeColor, property.strokeWidth);

    std::shared_ptr<RSMask> mask = RSMask::CreatePathMask(path, pen, brush);
    rsNode_->SetMask(mask);
}

void RosenRenderContext::SetCommandPathMask(const std::string& commands, const ShapeMaskProperty& property)
{
    CHECK_NULL_VOID(rsNode_);
    RSPath path;
    path.BuildFromSVGString(commands);

    RSBrush brush = GetRsBrush(property.fillColor);
    RSPen pen = GetRsPen(property.strokeColor, property.strokeWidth);

    std::shared_ptr<RSMask> mask = RSMask::CreatePathMask(path, pen, brush);
    rsNode_->SetMask(mask);
}

void RosenRenderContext::SetMarkNodeGroup(bool isNodeGroup)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkNodeGroup(isNodeGroup);
}

int32_t RosenRenderContext::GetRotateDegree()
{
    CHECK_NULL_RETURN(rsNode_, 0);
    return static_cast<int32_t>(rsNode_->GetStagingProperties().GetRotation());
}

void RosenRenderContext::ResetSurface(int width, int height)
{
#ifdef ACE_ENABLE_HYBRID_RENDER
    if (RSSystemProperties::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::CANVAS)) {
        auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
        CHECK_NULL_VOID(rsCanvasNode);
        if (rsCanvasNode->IsHybridRenderCanvas()) {
            rsCanvasNode->ResetSurface(width, height);
        }
        return;
    }
#endif
    auto rsCanvasDrawingNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasDrawingNode>(rsNode_);
    CHECK_NULL_VOID(rsCanvasDrawingNode);
    rsCanvasDrawingNode->ResetSurface(width, height);
}

void RosenRenderContext::SavePaintRect(bool isRound, uint16_t flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    AdjustPaintRect();
    if (!SystemProperties::GetPixelRoundEnabled()) {
        // isRound is the switch of pixelRound of lower version
        isRound = false;
        // flag is the switch of pixelRound of upper version
        flag = NO_FORCE_ROUND;
    }
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        OnePixelRounding(flag);
    } else {
        if (isRound && flag == 0) {
            RoundToPixelGrid(); // call RoundToPixelGrid without param to improve performance
        } else {
            RoundToPixelGrid(isRound, flag);
        }
    }
    paintRect_ = RectF(geometryNode->GetPixelGridRoundOffset(), geometryNode->GetPixelGridRoundSize());
    if (SystemProperties::GetSyncDebugTraceEnabled()) {
        ACE_LAYOUT_SCOPED_TRACE("SavePaintRect[%s][self:%d] rs SavePaintRect %s", host->GetTag().c_str(), host->GetId(),
            paintRect_.ToString().c_str());
    }
}

void RosenRenderContext::UpdatePaintRect(const RectF& paintRect)
{
    auto host = GetHost();
    if (host && SystemProperties::GetSyncDebugTraceEnabled()) {
        ACE_LAYOUT_SCOPED_TRACE("UpdatePaintRect[%s][self:%d] from %s to %s", host->GetTag().c_str(), host->GetId(),
            paintRect_.ToString().c_str(), paintRect.ToString().c_str());
    }
    paintRect_ = paintRect;
}

void RosenRenderContext::SyncPartialRsProperties()
{
    if (propTransform_ && propTransform_->HasTransformCenter()) {
        auto vec = propTransform_->GetTransformCenterValue();
        float xPivot = ConvertDimensionToScaleBySize(vec.GetX(), paintRect_.Width());
        float yPivot = ConvertDimensionToScaleBySize(vec.GetY(), paintRect_.Height());
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
}

void RosenRenderContext::UpdateDrawRegion(uint32_t index, const std::shared_ptr<Rosen::RectF>& rect)
{
    if (drawRegionRects_[index] && rect && *drawRegionRects_[index] == *rect) {
        return;
    } else if (!drawRegionRects_[index] && !rect) {
        return;
    }
    // the drawRegion of this index has changed
    drawRegionRects_[index] = rect;
    std::shared_ptr<Rosen::RectF> result;
    for (size_t index = 0; index < DRAW_REGION_RECT_COUNT; ++index) {
        if (drawRegionRects_[index]) {
            if (result) {
                *result = result->JoinRect(*drawRegionRects_[index]);
            } else {
                result = std::make_shared<Rosen::RectF>(*drawRegionRects_[index]);
            }
        }
    }
    if (!result) {
        return;
    }
    rsNode_->SetDrawRegion(result);
}

void RosenRenderContext::NotifyHostTransformUpdated(bool changed)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->NotifyTransformInfoChanged();
    host->OnNodeTransformInfoUpdate(changed);
    host->UpdateAccessibilityNodeRect();
}

void RosenRenderContext::SuggestOpIncNode(bool isOpincNode, bool isNeedCalculate)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkSuggestOpincNode(isOpincNode, isNeedCalculate);
}

void RosenRenderContext::OnAttractionEffectUpdate(const AttractionEffect& effect)
{
    CHECK_NULL_VOID(rsNode_);
    Rosen::Vector2f destinationPoint(effect.destinationX.ConvertToPx(), effect.destinationY.ConvertToPx());
    rsNode_->SetAttractionEffect(effect.fraction, destinationPoint);
    RequestNextFrame();
}

void RosenRenderContext::UpdateOcclusionCullingStatus(bool enable)
{
    CHECK_NULL_VOID(rsNode_);
    const auto keyOcclusionNodeId = rsNode_->GetId();
    LOGD("RosenRenderContext::UpdateOcclusionCullingStatus enable %{public}d, "
        "keyOcclusionId %{public}" PRIu64, enable, keyOcclusionNodeId);
    ACE_SCOPED_TRACE("RosenRenderContext::UpdateOcclusionCullingStatus"
        "enable %d, keyOcclusionId %" PRIu64, enable, keyOcclusionNodeId);
    rsNode_->UpdateOcclusionCullingStatus(enable, keyOcclusionNodeId);
}

PipelineContext* RosenRenderContext::GetPipelineContext() const
{
    auto host = GetHost();
    if (host) {
        return host->GetContextWithCheck();
    }
    return PipelineContext::GetCurrentContextPtrSafelyWithCheck();
}

void RosenRenderContext::UpdateWindowBlur()
{
    auto pipeline = GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->IsFormRender()) {
        return;
    }
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        LOGW("cannot find theme of blurStyle, create blurStyle failed");
        return;
    }
    ThemeColorMode colorMode =
        GetResourceColorMode(pipeline) == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    auto blurParam = blurStyleTheme->GetBlurParameter(BlurStyle::COMPONENT_ULTRA_THICK_WINDOW, colorMode);
    if (NearZero(blurParam->radius)) {
        return;
    }
    auto maskColor = LinearColor(blurParam->maskColor.GetValue());
    auto rgbaColor = (static_cast<uint32_t>(std::clamp<uint16_t>(maskColor.GetAlpha(), 0, UINT8_MAX))) |
                     (static_cast<uint32_t>((std::clamp<uint16_t>(maskColor.GetBlue(), 0, UINT8_MAX)) << 8)) |
                     (static_cast<uint32_t>((std::clamp<uint16_t>(maskColor.GetGreen(), 0, UINT8_MAX)) << 16)) |
                     (static_cast<uint32_t>((std::clamp<uint16_t>(maskColor.GetRed(), 0, UINT8_MAX)) << 24));
    if (!windowBlurModifier_.has_value()) {
        windowBlurModifier_ = WindowBlurModifier();
    }
    auto window = reinterpret_cast<RosenWindow*>(pipeline->GetWindow());
    CHECK_NULL_VOID(window);
    auto rsWindow = window->GetRSWindow();
    CHECK_NULL_VOID(rsWindow);
    auto surfaceNode = rsWindow->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto rsUIContext = rsNode_->GetRSUIContext();
    auto rsNodeTmp = rsUIContext ? rsUIContext->GetNodeMap().GetNode(
        surfaceNode->GetId()) : Rosen::RSNodeMap::Instance().GetNode(surfaceNode->GetId());
    AnimationOption option;
    const int32_t duration = 400;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), nullptr);
    WindowBlurModifier::AddOrChangeRadiusModifier(rsNodeTmp, windowBlurModifier_->radius,
        windowBlurModifier_->radiusValue, blurParam->radius);
    WindowBlurModifier::AddOrChangeSaturationModifier(
        rsNodeTmp, windowBlurModifier_->saturation, windowBlurModifier_->saturationValue, blurParam->saturation);
    WindowBlurModifier::AddOrChangeMaskColorModifier(rsNodeTmp, windowBlurModifier_->maskColor,
        windowBlurModifier_->maskColorValue, Rosen::RSColor(rgbaColor));
    WindowBlurModifier::AddOrChangeBrightnessModifier(
        rsNodeTmp, windowBlurModifier_->brightness, windowBlurModifier_->brightnessValue, blurParam->brightness);
    AnimationUtils::CloseImplicitAnimation();
}

void RosenRenderContext::MarkUiFirstNode(bool isUiFirstNode)
{
    CHECK_NULL_VOID(rsNode_);
    rsNode_->MarkUifirstNode(isUiFirstNode);
}

void RosenRenderContext::BuildShadowInfo(std::unique_ptr<JsonValue>& json)
{
    if (!NearZero(rsNode_->GetStagingProperties().GetShadowOffsetY())) {
        json->Put("ShadowOffsetY", rsNode_->GetStagingProperties().GetShadowOffsetY());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetShadowAlpha())) {
        json->Put("ShadowAlpha", rsNode_->GetStagingProperties().GetShadowAlpha());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetShadowElevation())) {
        json->Put("ShadowElevation", rsNode_->GetStagingProperties().GetShadowElevation());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetShadowRadius())) {
        json->Put("ShadowRadius", rsNode_->GetStagingProperties().GetShadowRadius());
    }
}

void RosenRenderContext::BuildStagingInfo(std::unique_ptr<JsonValue>& json)
{
    if (!NearZero(rsNode_->GetStagingProperties().GetPivotZ())) {
        json->Put("PivotZ", rsNode_->GetStagingProperties().GetPivotZ());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetRotation())) {
        json->Put("Rotation", rsNode_->GetStagingProperties().GetRotation());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetRotationX())) {
        json->Put("RotationX", rsNode_->GetStagingProperties().GetRotationX());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetRotationY())) {
        json->Put("RotationY", rsNode_->GetStagingProperties().GetRotationY());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetCameraDistance())) {
        json->Put("CameraDistance", rsNode_->GetStagingProperties().GetCameraDistance());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetTranslateZ())) {
        json->Put("TranslateZ", rsNode_->GetStagingProperties().GetTranslateZ());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetBgImageWidth())) {
        json->Put("BgImageWidth", rsNode_->GetStagingProperties().GetBgImageWidth());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetBgImageHeight())) {
        json->Put("BgImageHeight", rsNode_->GetStagingProperties().GetBgImageHeight());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetBgImagePositionX())) {
        json->Put("BgImagePositionX", rsNode_->GetStagingProperties().GetBgImagePositionX());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetBgImagePositionY())) {
        json->Put("BgImagePositionY", rsNode_->GetStagingProperties().GetBgImagePositionY());
    }
    BuildShadowInfo(json);
    if (!NearZero(rsNode_->GetStagingProperties().GetSpherizeDegree())) {
        json->Put("SpherizeDegree", rsNode_->GetStagingProperties().GetSpherizeDegree());
    }
    if (!NearZero(rsNode_->GetStagingProperties().GetLightUpEffectDegree())) {
        json->Put("LightUpEffectDegree", rsNode_->GetStagingProperties().GetLightUpEffectDegree());
    }
    if (!NearEqual(rsNode_->GetStagingProperties().GetAlpha(), 1)) {
        json->Put("Alpha", rsNode_->GetStagingProperties().GetAlpha());
    }
}

void RosenRenderContext::BuildPositionInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("rsNode", rsNode_->DumpNode(0).c_str());
    auto center = rsNode_->GetStagingProperties().GetPivot();
    if (!NearEqual(center[0], 0.5) || !NearEqual(center[1], 0.5)) {
        auto child = JsonUtil::Create(true);
        child->Put("x", center[0]);
        child->Put("y", center[1]);
        json->Put("Center", child);
    }
    BuildStagingInfo(json);
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    if (!(NearZero(translate[0]) && NearZero(translate[1]))) {
        auto child = JsonUtil::Create(true);
        child->Put("x", translate[0]);
        child->Put("y", translate[1]);
        json->Put("translate", child);
    }
    auto scale = rsNode_->GetStagingProperties().GetScale();
    if (!(NearEqual(scale[0], 1) && NearEqual(scale[1], 1))) {
        auto child = JsonUtil::Create(true);
        child->Put("x", scale[0]);
        child->Put("y", scale[1]);
        json->Put("scale", child);
    }
    auto rect = GetPaintRectWithoutTransform();
    if (HasTransformTranslate()) {
        auto translateArk = GetTransformTranslate().value();
        auto arkTranslateX = translateArk.x.ConvertToPxWithSize(rect.Width());
        auto arkTranslateY = translateArk.y.ConvertToPxWithSize(rect.Height());
        if (!NearEqual(arkTranslateX, translate[0])) {
            json->Put("TranlateX has difference,arkui", std::to_string(arkTranslateX).c_str());
        }
        if (!NearEqual(arkTranslateY, translate[1])) {
            json->Put("TranlateY has difference,arkui", std::to_string(arkTranslateY).c_str());
        }
    }
    if (HasTransformScale()) {
        auto arkTransformScale = GetTransformScale().value();
        if (!NearEqual(arkTransformScale.x, scale[0])) {
            json->Put("scaleX has difference,arkui", std::to_string(arkTransformScale.x).c_str());
        }
        if (!NearEqual(arkTransformScale.y, scale[1])) {
            json->Put("scaleY has difference,arkui", std::to_string(arkTransformScale.y).c_str());
        }
    }
}

void RosenRenderContext::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    if (rsNode_) {
        auto children = JsonUtil::Create(true);
        BuildPositionInfo(children);
        if (HasOpacity()) {
            auto arkAlpha = GetOpacity();
            if (!NearEqual(arkAlpha.value(), rsNode_->GetStagingProperties().GetAlpha())) {
                children->Put("Alpha has difference,arkui", std::to_string(arkAlpha.value()).c_str());
            }
        }
        if (HasPosition()) {
            auto position = GetPosition();
            children->Put("PositionX", position->GetX().ToString().c_str());
            children->Put("PositionY", position->GetY().ToString().c_str());
        }
        if (HasOffset()) {
            auto offset = GetOffset();
            children->Put("OffsetX", offset->GetX().ToString().c_str());
            children->Put("OffsetY", offset->GetY().ToString().c_str());
        }
        if (HasPositionEdges()) {
            auto positionEdges = GetPositionEdges();
            children->Put("positionEdges", positionEdges->ToString().c_str());
        }
        if (HasOffsetEdges()) {
            auto offsetEdges = GetOffsetEdges();
            children->Put("offsetEdges", offsetEdges->ToString().c_str());
        }
        if (HasAnchor()) {
            auto anchor = GetAnchor();
            children->Put("anchorX", anchor->GetX().ToString().c_str());
            children->Put("anchorY", anchor->GetY().ToString().c_str());
        }
        json->Put("rsNode", children);
    }
}

void RosenRenderContext::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    if (GetBackgroundAlign().has_value()) {
        json->Put("BackgroundAlign", GetBackgroundAlign().value().ToString().c_str());
    }
    if (GetBackgroundImage().has_value()) {
        json->Put("BackgroundImage", GetBackgroundImage().value().ToString().c_str());
    }
    if (GetSphericalEffect().has_value()) {
        json->Put("SphericalEffect", std::to_string(GetSphericalEffect().value()).c_str());
    }
    if (GetPixelStretchEffect().has_value()) {
        json->Put("PixelStretchEffect", GetPixelStretchEffect().value().ToString().c_str());
    }
    if (GetLightUpEffect().has_value()) {
        json->Put("LightUpEffect", std::to_string(GetLightUpEffect().value()).c_str());
    }
    if (GetBorderColor().has_value()) {
        json->Put("BorderColor", GetBorderColor().value().ToString().c_str());
    }
    if (GetBorderWidth().has_value()) {
        json->Put("BorderWidth", GetBorderWidth().value().ToString().c_str());
    }
    if (GetOuterBorderRadius().has_value()) {
        json->Put("OuterBorderRadius", GetOuterBorderRadius().value().ToString().c_str());
    }
    if (GetOuterBorderColor().has_value()) {
        json->Put("OuterBorderColor", GetOuterBorderColor().value().ToString().c_str());
    }
    if (GetOuterBorderWidth().has_value()) {
        json->Put("OuterBorderWidth", GetOuterBorderWidth().value().ToString().c_str());
    }
    if (GetDynamicLightUpRate().has_value()) {
        json->Put("DynamicLightUpRate", std::to_string(GetDynamicLightUpRate().value()).c_str());
    }
    if (GetDynamicLightUpDegree().has_value()) {
        json->Put("DynamicLightUpDegree", std::to_string(GetDynamicLightUpDegree().value()).c_str());
    }
    if (GetBackBlendMode().has_value()) {
        json->Put("BlendMode", static_cast<int>(GetBackBlendMode().value()));
    }
    if (GetLinearGradient().has_value()) {
        json->Put("LinearGradient", GetLinearGradient().value().ToString().c_str());
    }
    if (GetSweepGradient().has_value()) {
        json->Put("SweepGradient", GetSweepGradient().value().ToString().c_str());
    }
    SetAdvanceInfo(json);
}

void RosenRenderContext::SetAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    if (GetRadialGradient().has_value()) {
        json->Put("RadialGradient", GetRadialGradient().value().ToString().c_str());
    }
    if (GetFrontBrightness().has_value()) {
        json->Put("FrontBrightness", GetFrontBrightness().value().ToString().c_str());
    }
    if (GetFrontGrayScale().has_value()) {
        json->Put("FrontGrayScale", GetFrontGrayScale().value().ToString().c_str());
    }
    if (GetFrontContrast().has_value()) {
        json->Put("FrontContrast", GetFrontContrast().value().ToString().c_str());
    }
    if (GetFrontSaturate().has_value()) {
        json->Put("FrontSaturate", GetFrontSaturate().value().ToString().c_str());
    }
    if (GetFrontSepia().has_value()) {
        json->Put("FrontSepia", GetFrontSepia().value().ToString().c_str());
    }
    if (GetFrontHueRotate().has_value()) {
        json->Put("FrontHueRotate", std::to_string(GetFrontHueRotate().value()).c_str());
    }
    if (GetFrontColorBlend().has_value()) {
        json->Put("FrontColorBlend", GetFrontColorBlend().value().ColorToString().c_str());
    }
    if (GetBorderImageSource().has_value()) {
        json->Put("BorderImageSource", GetBorderImageSource().value().ToString().c_str());
    }
    if (GetBorderImageGradient().has_value()) {
        json->Put("BorderImageGradient", GetBorderImageGradient().value().ToString().c_str());
    }
    if (GetForegroundColor().has_value()) {
        json->Put("ForegroundColor", GetForegroundColor().value().ColorToString().c_str());
    }
    if (GetLightIntensity().has_value()) {
        json->Put("LightIntensity", std::to_string(GetLightIntensity().value()).c_str());
    }
    if (GetLightIlluminated().has_value()) {
        json->Put("LightIlluminated", std::to_string(GetLightIlluminated().value()).c_str());
    }
    if (GetIlluminatedBorderWidth().has_value()) {
        json->Put("IlluminatedBorderWidth", GetIlluminatedBorderWidth().value().ToString().c_str());
    }
    if (GetBloom().has_value()) {
        json->Put("Bloom", std::to_string(GetBloom().value()).c_str());
    }
}

void RosenRenderContext::DumpSimplifyInfo(std::unique_ptr<JsonValue>& json)
{
    if (rsNode_) {
        DumpSimplifyStagingProperties(json);
        if (!NearZero(rsNode_->GetStagingProperties().GetPivotZ())) {
            json->Put("PivotZ", std::to_string(rsNode_->GetStagingProperties().GetPivotZ()).c_str());
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetRotation())) {
            json->Put("Rotation", std::to_string(rsNode_->GetStagingProperties().GetRotation()).c_str());
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetRotationX())) {
            json->Put("RotationX", std::to_string(rsNode_->GetStagingProperties().GetRotationX()).c_str());
        }
        if (!NearZero(rsNode_->GetStagingProperties().GetRotationY())) {
            json->Put("RotationY", std::to_string(rsNode_->GetStagingProperties().GetRotationY()).c_str());
        }
        if (!NearEqual(rsNode_->GetStagingProperties().GetAlpha(), 1)) {
            json->Put("Alpha", std::to_string(rsNode_->GetStagingProperties().GetAlpha()).c_str());
        }
        if (HasPosition()) {
            auto position = GetPosition();
            json->Put("Position",
                position->GetX().ToString().append(",").append(position->GetY().ToString()).c_str());
        }
        if (HasOffset()) {
            auto offset = GetOffset();
            json->Put("Offset", offset->GetX().ToString().append(",").append(offset->GetY().ToString()).c_str());
        }
        if (HasPositionEdges()) {
            auto positionEdges = GetPositionEdges();
            json->Put("PositionEdges", positionEdges->ToString().c_str());
        }
        if (HasOffsetEdges()) {
            auto offsetEdges = GetOffsetEdges();
            json->Put("OffsetEdges", offsetEdges->ToString().c_str());
        }
        if (HasAnchor()) {
            auto anchor = GetAnchor();
            json->Put("Anchor", anchor->GetX().ToString().append(",").append(anchor->GetY().ToString()).c_str());
        }
    }
}

void RosenRenderContext::DumpSimplifyStagingProperties(std::unique_ptr<JsonValue>& json)
{
    auto center = rsNode_->GetStagingProperties().GetPivot();
    if (!NearEqual(center[0], 0.5) || !NearEqual(center[1], 0.5)) {
        json->Put("Center", std::to_string(center[0]).append(",").append(std::to_string(center[1])).c_str());
    }
    auto translate = rsNode_->GetStagingProperties().GetTranslate();
    if (!(NearZero(translate[0]) && NearZero(translate[1]))) {
        json->Put("Translate",
            std::to_string(translate[0]).append(",").append(std::to_string(translate[1])).c_str());
    }
    auto scale = rsNode_->GetStagingProperties().GetScale();
    if (!(NearEqual(scale[0], 1) && NearEqual(scale[1], 1))) {
        json->Put("Scale", std::to_string(scale[0]).append(",").append(std::to_string(scale[1])).c_str());
    }
    if (HasTransformScale()) {
        auto arkTransformScale = GetTransformScale().value();
        if (!NearEqual(arkTransformScale.x, scale[0])) {
            json->Put("TransformScaleX", std::to_string(arkTransformScale.x).c_str());
        }
        if (!NearEqual(arkTransformScale.y, scale[1])) {
            json->Put("TransformScaleY", std::to_string(arkTransformScale.y).c_str());
        }
    }
    auto rect = GetPaintRectWithoutTransform();
    if (HasTransformTranslate()) {
        auto translateArk = GetTransformTranslate().value();
        auto arkTranslateX = translateArk.x.ConvertToPxWithSize(rect.Width());
        auto arkTranslateY = translateArk.y.ConvertToPxWithSize(rect.Height());
        if (!NearEqual(arkTranslateX, translate[0])) {
            json->Put("TransformTranslateX", std::to_string(arkTranslateX).c_str());
        }
        if (!NearEqual(arkTranslateY, translate[1])) {
            json->Put("TransformTranslateY", std::to_string(arkTranslateY).c_str());
        }
    }
    if (HasOpacity()) {
        auto arkAlpha = GetOpacity();
        if (!NearEqual(arkAlpha.value(), rsNode_->GetStagingProperties().GetAlpha())) {
            json->Put("TransformAlpha", std::to_string(arkAlpha.value()).c_str());
        }
    }
}

void RosenRenderContext::FreezeCanvasNode(bool freezeFlag)
{
    if (canvasNode_) {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "FreezeCanvasNode. %{public}d", freezeFlag);
        canvasNode_->SetFreeze(freezeFlag);
    }
}

void RosenRenderContext::RemoveCanvasNode()
{
    if (reDraggingFlag_) {
        reDraggingFlag_ = false;
        return;
    }
    if (canvasNode_) {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "RemoveCanvasNode.");
        canvasNode_->RemoveFromTree();
        canvasNode_ = nullptr;
    }
}

void RosenRenderContext::CheckAnimationParametersValid(int32_t& animationParam)
{
    const int32_t maxTime = 2000;
    const int32_t defaultTime = 100;
    if (animationParam <= 0 || animationParam > maxTime) {
        animationParam = defaultTime;
    }
}

bool RosenRenderContext::SetCanvasNodeOpacityAnimation(int32_t duration, int32_t delay, bool isDragEnd)
{
    static bool animationFlag = false;
    if (animationFlag) {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "animationFlag is true.");
        return false;
    }
    if (!canvasNode_) {
        return true;
    }

    FreezeCanvasNode(true);
    canvasNode_->SetAlpha(1.0f);
    Rosen::RSTransaction::FlushImplicitTransaction();

    CheckAnimationParametersValid(duration);
    CheckAnimationParametersValid(delay);
    AnimationOption option;
    option.SetDuration(duration);
    option.SetDelay(delay);
    option.SetCurve(Curves::EASE_OUT);
    AnimationUtils::Animate(option,
        [this]() {
            if (canvasNode_) {
                animationFlag = true;
                canvasNode_->SetAlpha(0.0f);
            }
        },
        [this, isDragEnd]() {
            if (canvasNode_) {
                canvasNode_->SetAlpha(1.0f);
            }
            FreezeCanvasNode(false);
            if (isDragEnd) {
                RemoveCanvasNode();
            }
            if (callbackAnimateEnd_) {
                callbackAnimateEnd_();
            }
            Rosen::RSTransaction::FlushImplicitTransaction();
            animationFlag = false;
            if (callbackCachedAnimateAction_) {
                callbackCachedAnimateAction_();
            }
        });
    return true;
}

void RosenRenderContext::LinkCanvasNodeToRootNode(const RefPtr<FrameNode>& rootNode)
{
    if (canvasNode_ && rootNode) {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "SetLinkedRootNodeId");
        auto renderContext = rootNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        canvasNode_->SetLinkedRootNodeId(renderContext->GetNodeId());
        Rosen::RSTransaction::FlushImplicitTransaction();
    }
}

void RosenRenderContext::CreateCanvasNode()
{
    if (!canvasNode_) {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "Create RSCanvasNode.");
        canvasNode_ = Rosen::RSCanvasNode::Create();
        Rosen::RSTransaction::FlushImplicitTransaction();
    }
}

std::shared_ptr<Rosen::RSCanvasNode> RosenRenderContext::GetCanvasNode() const
{
    return canvasNode_;
}

void RosenRenderContext::SetIsWideColorGamut(bool isWideColorGamut)
{
    auto rsCanvasNode = Rosen::RSNode::ReinterpretCast<Rosen::RSCanvasNode>(rsNode_);
    CHECK_NULL_VOID(rsCanvasNode);
    if (isWideColorGamut_ != isWideColorGamut) {
        isWideColorGamut_ = isWideColorGamut;
        rsCanvasNode->SetIsWideColorGamut(isWideColorGamut_);
        return;
    }
}

void RosenRenderContext::SetAnimationPropertyValue(AnimationPropertyType property, const std::vector<float>& value)
{
    CHECK_NULL_VOID(rsNode_);
    switch (property) {
        case AnimationPropertyType::ROTATION: {
            if (value.size() == 3) {
                // rotationX and rotationY are opposite between arkui and rs.
                SetAnimatableProperty<Rosen::RSRotationXModifier, float>(rotationXUserModifier_, -value[0]);
                SetAnimatableProperty<Rosen::RSRotationYModifier, float>(rotationYUserModifier_, -value[1]);
                SetAnimatableProperty<Rosen::RSRotationModifier, float>(rotationZUserModifier_, value[2]);
                NotifyHostTransformUpdated();
            }
            break;
        }
        case AnimationPropertyType::TRANSLATION: {
            if (value.size() == 2) {
                SetAnimatableProperty<Rosen::RSTranslateModifier, Rosen::Vector2f>(
                    translateXYUserModifier_, { value[0], value[1] });
                NotifyHostTransformUpdated();
            }
            break;
        }
        case AnimationPropertyType::SCALE: {
            if (value.size() == 2) {
                SetAnimatableProperty<Rosen::RSScaleModifier, Rosen::Vector2f>(
                    scaleXYUserModifier_, { value[0], value[1] });
                NotifyHostTransformUpdated();
            }
            break;
        }
        case AnimationPropertyType::OPACITY: {
            if (value.size() == 1) {
                SetAnimatableProperty<Rosen::RSAlphaModifier, float>(alphaUserModifier_, value[0]);
            }
            break;
        }
        default: {
            break;
        }
    }
}

void RosenRenderContext::CancelPropertyAnimation(AnimationPropertyType property)
{
    CHECK_NULL_VOID(rsNode_);
    switch (property) {
        case AnimationPropertyType::ROTATION: {
            CancelModifierAnimation<Rosen::RSRotationXModifier, float>(rotationXUserModifier_);
            CancelModifierAnimation<Rosen::RSRotationYModifier, float>(rotationYUserModifier_);
            CancelModifierAnimation<Rosen::RSRotationModifier, float>(rotationZUserModifier_);
            NotifyHostTransformUpdated();
            break;
        }
        case AnimationPropertyType::TRANSLATION: {
            CancelModifierAnimation<Rosen::RSTranslateModifier, Rosen::Vector2f>(translateXYUserModifier_);
            NotifyHostTransformUpdated();
            break;
        }
        case AnimationPropertyType::SCALE: {
            CancelModifierAnimation<Rosen::RSScaleModifier, Rosen::Vector2f>(scaleXYUserModifier_);
            NotifyHostTransformUpdated();
            break;
        }
        case AnimationPropertyType::OPACITY: {
            CancelModifierAnimation<Rosen::RSAlphaModifier, float>(alphaUserModifier_);
            break;
        }
        default: {
            break;
        }
    }
}

std::vector<float> RosenRenderContext::GetRenderNodePropertyValue(AnimationPropertyType property)
{
    std::vector<float> result;
    CHECK_NULL_RETURN(rsNode_, result);
    switch (property) {
        case AnimationPropertyType::ROTATION: {
            auto angleX =
                GetAnimatablePropertyStagingValue<Rosen::RSRotationXModifier, float>(rotationXUserModifier_, 0.0f);
            auto angleY =
                GetAnimatablePropertyStagingValue<Rosen::RSRotationYModifier, float>(rotationYUserModifier_, 0.0f);
            auto angleZ =
                GetAnimatablePropertyStagingValue<Rosen::RSRotationModifier, float>(rotationZUserModifier_, 0.0f);
            // reverse angleX and angleY, because the angle direction is inconsistent with the RS.
            result = { -angleX, -angleY, angleZ };
            break;
        }
        case AnimationPropertyType::TRANSLATION: {
            auto value = GetAnimatablePropertyStagingValue<Rosen::RSTranslateModifier, Rosen::Vector2f>(
                translateXYUserModifier_);
            result = { value[0], value[1] };
            break;
        }
        case AnimationPropertyType::SCALE: {
            auto value = GetAnimatablePropertyStagingValue<Rosen::RSScaleModifier, Rosen::Vector2f>(
                scaleXYUserModifier_, { 1.0f, 1.0f });
            result = { value[0], value[1] };
            break;
        }
        case AnimationPropertyType::OPACITY: {
            auto opacity = GetAnimatablePropertyStagingValue<Rosen::RSAlphaModifier, float>(alphaUserModifier_, 1.0f);
            result = { opacity };
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

std::shared_ptr<TransitionModifier> RosenRenderContext::GetOrCreateTransitionModifier()
{
    if (transitionModifier_) {
        return transitionModifier_;
    }

    transitionModifier_ = std::make_shared<TransitionModifier>();
    std::function<void(const std::shared_ptr<Rosen::RectF>& rect)> func =
        [weak = WeakClaim(this)](const std::shared_ptr<Rosen::RectF>& rect) {
            auto renderContext = weak.Upgrade();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateDrawRegion(DRAW_REGION_TRANSITION_MODIFIER_INDEX, rect);
        };

    transitionModifier_->SetDrawRegionUpdateFunc(func);
    return transitionModifier_;
}

std::shared_ptr<BackgroundModifier> RosenRenderContext::GetOrCreateBackgroundModifier()
{
    if (backgroundModifier_) {
        return backgroundModifier_;
    }
    backgroundModifier_ = std::make_shared<BackgroundModifier>();
    return backgroundModifier_;
}
} // namespace OHOS::Ace::NG
