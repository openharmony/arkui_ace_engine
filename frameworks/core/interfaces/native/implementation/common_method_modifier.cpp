/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <variant>
#include "arkoala_api_generated.h"

#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/accessibility/static/accessibility_static_utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"
#include "core/interfaces/native/implementation/base_gesture_event_peer.h"
#include "core/interfaces/native/implementation/color_metrics_peer.h"
#include "core/interfaces/native/implementation/dismiss_popup_action_peer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/focus_axis_event_peer.h"
#include "core/interfaces/native/implementation/gesture_recognizer_peer_impl.h"
#include "core/interfaces/native/implementation/long_press_gesture_event_peer.h"
#include "core/interfaces/native/implementation/long_press_recognizer_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_event_peer.h"
#include "core/interfaces/native/implementation/pan_recognizer_peer.h"
#include "core/interfaces/native/implementation/pinch_gesture_event_peer.h"
#include "core/interfaces/native/implementation/pinch_recognizer_peer.h"
#include "core/interfaces/native/implementation/progress_mask_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_event_peer.h"
#include "core/interfaces/native/implementation/rotation_recognizer_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_event_peer.h"
#include "core/interfaces/native/implementation/swipe_recognizer_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_event_peer.h"
#include "core/interfaces/native/implementation/tap_recognizer_peer.h"
#include "core/interfaces/native/implementation/text_field_modifier.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "frameworks/core/interfaces/native/implementation/bind_sheet_utils.h"
#include "base/log/log_wrapper.h"

#include "dismiss_popup_action_peer.h"

using namespace OHOS::Ace::NG::Converter;

namespace {
constexpr double PERCENT_100 = 100.0;
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr double BRIGHTNESS_MAX = 1.0;
constexpr double CONTRAST_MAX = 1.0;
constexpr double SATURATE_MAX = 1.0;
constexpr double LIGHTUPEFFECT_MAX = 1.0;
constexpr double BRIGHTNESS_MIN = 0.0;
constexpr double CONTRAST_MIN = 0.0;
constexpr double SATURATE_MIN = 0.0;
constexpr double LIGHTUPEFFECT_MIN = 0.0;
constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int NUM_3 = 3;
constexpr int NUM_5 = 5;
constexpr float DEFAULT_SCALE_LIGHT = 0.9f;
constexpr float DEFAULT_SCALE_MIDDLE_OR_HEAVY = 0.95f;
constexpr float MIN_ANGEL = 0.0f;
constexpr float MAX_ANGEL = 360.0f;
const uint32_t FOCUS_PRIORITY_AUTO = 0;
const uint32_t FOCUS_PRIORITY_PRIOR = 2000;
const uint32_t FOCUS_PRIORITY_PREVIOUS = 3000;
}

namespace OHOS::Ace::NG {
namespace {
Ark_GestureRecognizer CreateArkGestureRecognizer(const RefPtr<NGGestureRecognizer>& recognizer)
{
    Ark_GestureRecognizer peer = nullptr;
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(recognizer);
    if (tapRecognizer) {
        peer = Converter::ArkValue<Ark_TapRecognizer>(tapRecognizer);
        return peer;
    }
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(recognizer);
    if (longPressRecognizer) {
        peer = Converter::ArkValue<Ark_LongPressRecognizer>(longPressRecognizer);
        return peer;
    }
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(recognizer);
    if (panRecognizer) {
        peer = Converter::ArkValue<Ark_PanRecognizer>(panRecognizer);
        return peer;
    }
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(recognizer);
    if (pinchRecognizer) {
        peer = Converter::ArkValue<Ark_PinchRecognizer>(pinchRecognizer);
        return peer;
    }
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(recognizer);
    if (swipeRecognizer) {
        peer = Converter::ArkValue<Ark_SwipeRecognizer>(swipeRecognizer);
        return peer;
    }
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(recognizer);
    if (rotationRecognizer) {
        peer = Converter::ArkValue<Ark_RotationRecognizer>(rotationRecognizer);
        return peer;
    }
    peer = Converter::ArkValue<Ark_GestureRecognizer>(recognizer);
    return peer;
}
template<typename Container>
Array_GestureRecognizer CreateArkGestureRecognizerArray(const Container& recognizers)
{
    Array_GestureRecognizer result = {nullptr, 0};
    if (!Converter::FC) {
        return result;
    }
    result.length = static_cast<Ark_Int32>(recognizers.size());
    if (result.length <= 0) {
        return result;
    }
    result.array = static_cast<Ark_GestureRecognizer*>(
        Converter::FC->Allocate(result.length * sizeof(Ark_GestureRecognizer)));
    if (result.array == nullptr) {
        result.length = 0;
        return result;
    }
    size_t i = 0;
    for (const auto& recognizer : recognizers) {
        result.array[i++] = CreateArkGestureRecognizer(recognizer);
    }
    return result;
}
std::optional<bool> ProcessBindableIsShow(FrameNode* frameNode,
                                          const Opt_Union_Boolean_Bindable *value,
                                          std::function<void(const std::string&)>& outEvent)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result, &outEvent](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
            outEvent = nullptr;
        },
        [&result, frameNode, &outEvent](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            outEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::string& param) {
                PipelineContext::SetCallBackNode(weakNode);
                bool isShow = (param == "true");
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
            };
        },
        [] {});
    return result;
}
Ark_BaseGestureEvent CreateArkBaseGestureEvent(const std::shared_ptr<BaseGestureEvent>& info, GestureTypeName typeName)
{
    BaseGestureEventPeer* peer = nullptr;
    switch (typeName) {
        case OHOS::Ace::GestureTypeName::TAP_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<TapGestureEventPeer, TapGestureEvent>(info);
            break;
        }
        case OHOS::Ace::GestureTypeName::LONG_PRESS_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<LongPressGestureEventPeer, LongPressGestureEvent>(info);
            break;
        }
        case OHOS::Ace::GestureTypeName::PAN_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<PanGestureEventPeer, PanGestureEvent>(info);
            break;
        }
        case OHOS::Ace::GestureTypeName::PINCH_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<PinchGestureEventPeer, PinchGestureEvent>(info);
            break;
        }
        case OHOS::Ace::GestureTypeName::ROTATION_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<RotationGestureEventPeer, RotationGestureEvent>(info);
            break;
        }
        case OHOS::Ace::GestureTypeName::SWIPE_GESTURE: {
            peer = GeneratedModifier::CreateGestureEventPeer<SwipeGestureEventPeer, SwipeGestureEvent>(info);
            break;
        }
        default:
            peer = GeneratedModifier::CreateGestureEventPeer<GeneratedModifier::BaseGestureEventPeerImpl,
                BaseGestureEvent>(info);
            break;
    }
    CHECK_NULL_RETURN(peer, nullptr);
    peer->SetRecognizerType(typeName);
    return peer;
}
} // namespace

struct EdgesParamOptions {
    EdgesParam value;
    bool isLocalized;
};

struct BiasOpt {
    std::optional<float> first;
    std::optional<float> second;
};

struct RotateOpt {
    std::optional<DimensionOffset> center;
    std::vector<std::optional<float>> vec5f;
};

struct RotateAngleOpt {
    std::optional<DimensionOffset> center;
    std::vector<std::optional<float>> vec4f;
};

struct TranslateOpt {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
    std::optional<Dimension> z;
};

struct GeometryTransitionOptions {
    std::optional<bool> follow;
    std::optional<TransitionHierarchyStrategy> hierarchyStrategy;
};

struct SetFocusData {
    std::optional<std::string> forward;
    std::optional<std::string> backward;
    std::optional<std::string> up;
    std::optional<std::string> down;
    std::optional<std::string> left;
    std::optional<std::string> right;
};

using PositionWithLocalization = std::pair<std::optional<OffsetT<Dimension>>, bool>;

using OffsetOrEdgesParam = std::variant<
    std::monostate,
    std::optional<OffsetT<Dimension>>,
    std::optional<EdgesParamOptions>
>;

auto g_isPopupCreated = [](FrameNode* frameNode) -> bool {
    auto targetId = frameNode->GetId();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, false);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto popupInfo = overlayManager->GetPopupInfo(targetId);
    if (popupInfo.popupId == -1 || !popupInfo.popupNode) {
        return false;
    }
    return true;
};

auto g_popupCommonParam = [](const auto& src, RefPtr<PopupParam>& popupParam) {
    CHECK_NULL_VOID(popupParam);
    popupParam->SetEnableHoverMode(OptConvert<bool>(src.enableHoverMode).value_or(popupParam->EnableHoverMode()));
    popupParam->SetFollowTransformOfTarget(OptConvert<bool>(src.followTransformOfTarget)
        .value_or(popupParam->IsFollowTransformOfTarget()));
    Converter::VisitUnion(src.mask,
        [&popupParam](const Ark_Boolean& mask) {
            popupParam->SetBlockEvent(Convert<bool>(mask));
        },
        [&popupParam](const Ark_PopupMaskType& mask) {
            auto popupMaskColor = OptConvert<Color>(mask.color);
            if (popupMaskColor.has_value()) {
                popupParam->SetMaskColor(popupMaskColor.value());
            }
        },
        []() {});
    auto arkOnStateChange = GetOpt(src.onStateChange);
    if (arkOnStateChange.has_value()) {
        auto onStateChangeCallback = [arkCallback = CallbackHelper(*arkOnStateChange)](
            const std::string& param) {
            auto json = JsonUtil::ParseJsonString(param);
            json->Put("isVisible", param.c_str());
            Ark_PopupStateChangeParam event;
            event.isVisible = Converter::ArkValue<Ark_Boolean>(json->GetBool("isVisible", false));
            arkCallback.Invoke(event);
        };
        popupParam->SetOnStateChange(std::move(onStateChangeCallback));
    }
    auto offsetVal = OptConvert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(src.offset);
    if (offsetVal.has_value()) {
        Offset popupOffset;
        popupOffset.SetX(offsetVal.value().first->ConvertToPx());
        popupOffset.SetY(offsetVal.value().second->ConvertToPx());
        popupParam->SetTargetOffset(popupOffset);
    }
    auto popupBackgroundColor = Converter::OptConvert<Color>(src.popupColor);
    if (popupBackgroundColor.has_value()) {
        popupParam->SetBackgroundColor(popupBackgroundColor.value());
    }
    auto autoCancel = Converter::OptConvert<bool>(src.autoCancel);
    if (autoCancel.has_value()) {
        popupParam->SetHasAction(!autoCancel.value());
    }
    auto keyboardAvoidMode = Converter::OptConvert<PopupKeyboardAvoidMode>(src.keyboardAvoidMode);
    if (keyboardAvoidMode.has_value()) {
        popupParam->SetKeyBoardAvoidMode(keyboardAvoidMode.value());
    }
};

auto g_getPopupDefaultShadow = []() -> ShadowStyle {
    auto shadowStyle = ShadowStyle::OuterDefaultMD;
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, shadowStyle);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, shadowStyle);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, shadowStyle);
    return popupTheme->GetPopupShadowStyle();
};

auto g_getShadowFromTheme = [](ShadowStyle shadowStyle, Shadow& shadow) -> bool {
    auto colorMode = Container::CurrentColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
};

auto g_setPopupDefaultBlurStyle = [](RefPtr<PopupParam>& popupParam) {
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    auto blurStyle = static_cast<BlurStyle>(popupTheme->GetPopupBackgroundBlurStyle());
    popupParam->SetBlurStyle(blurStyle);
};

auto g_popupCommonParamWithValidator = [](const auto& src, RefPtr<PopupParam>& popupParam) {
    CHECK_NULL_VOID(popupParam);
    auto widthOpt = Converter::OptConvert<CalcDimension>(src.width);
    Validator::ValidateNonNegative(widthOpt);
    if (widthOpt.has_value()) {
        popupParam->SetChildWidth(widthOpt.value());
    }
    auto arrowWidthOpt = Converter::OptConvert<CalcDimension>(src.arrowWidth);
    Validator::ValidatePositive(arrowWidthOpt);
    Validator::ValidateNonPercent(arrowWidthOpt);
    if (arrowWidthOpt.has_value()) {
        popupParam->SetArrowWidth(arrowWidthOpt.value());
    }
    auto arrowHeightOpt = Converter::OptConvert<CalcDimension>(src.arrowHeight);
    Validator::ValidatePositive(arrowHeightOpt);
    Validator::ValidateNonPercent(arrowHeightOpt);
    if (arrowHeightOpt.has_value()) {
        popupParam->SetArrowHeight(arrowHeightOpt.value());
    }
    auto radiusOpt = Converter::OptConvert<CalcDimension>(src.radius);
    Validator::ValidateNonNegative(radiusOpt);
    if (radiusOpt.has_value()) {
        popupParam->SetRadius(radiusOpt.value());
    }
    auto shadowOpt = Converter::OptConvert<Shadow>(src.shadow);
    if (shadowOpt.has_value()) {
        popupParam->SetShadow(shadowOpt.value());
    } else {
        auto defaultPopupShadowStyle = g_getPopupDefaultShadow();
        Shadow shadow;
        g_getShadowFromTheme(defaultPopupShadowStyle, shadow);
        popupParam->SetShadow(shadow);
    }
    auto popupBackgroundBlurStyleOpt = Converter::OptConvert<BlurStyle>(src.backgroundBlurStyle);
    if (popupBackgroundBlurStyleOpt.has_value()) {
        popupParam->SetBlurStyle(popupBackgroundBlurStyleOpt.value());
    } else {
        g_setPopupDefaultBlurStyle(popupParam);
    }
    auto targetSpaceOpt = Converter::OptConvert<CalcDimension>(src.targetSpace);
    if (targetSpaceOpt.has_value()) {
        popupParam->SetTargetSpace(targetSpaceOpt.value());
    }
    bool showInSubBoolean = OptConvert<bool>(src.showInSubWindow).value_or(popupParam->IsShowInSubWindow());
#if defined(PREVIEW)
    showInSubBoolean = false;
#endif
    popupParam->SetShowInSubWindow(showInSubBoolean);
    popupParam->SetEnableArrow(OptConvert<bool>(src.enableArrow).value_or(popupParam->EnableArrow()));
    auto popupTransitionEffectsOpt = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(src.transition);
    if (popupTransitionEffectsOpt.has_value()) {
        popupParam->SetHasTransition(true);
        popupParam->SetTransitionEffects(popupTransitionEffectsOpt.value());
    }
};

auto g_bindMenuOptionsParamCallbacks = [](
    const auto& menuOptions, MenuParam& menuParam, WeakPtr<FrameNode> weakNode) {
    auto onAppearValue = OptConvert<Callback_Void>(menuOptions.onAppear);
    if (onAppearValue) {
        auto onAppear = [arkCallback = CallbackHelper(onAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        menuParam.onAppear = std::move(onAppear);
    }
    auto onDisappearValue = OptConvert<Callback_Void>(menuOptions.onDisappear);
    if (onDisappearValue) {
        auto onDisappear = [arkCallback = CallbackHelper(onDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    auto aboutToAppearValue = OptConvert<Callback_Void>(menuOptions.aboutToAppear);
    if (aboutToAppearValue) {
        auto aboutToAppear = [arkCallback = CallbackHelper(aboutToAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        menuParam.aboutToAppear = std::move(aboutToAppear);
    }
    auto aboutToDisAppearValue = OptConvert<Callback_Void>(menuOptions.aboutToDisappear);
    if (aboutToDisAppearValue) {
        auto aboutToDisappear = [arkCallback = CallbackHelper(aboutToDisAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        menuParam.aboutToDisappear = std::move(aboutToDisappear);
    }
};

auto g_parseLayoutRegionMargin = [](const auto& menuOptions, MenuParam& menuParam) {
    auto layoutRegionMargin = OptConvert<PaddingProperty>(menuOptions.layoutRegionMargin);
    if (layoutRegionMargin->left.has_value() && !layoutRegionMargin->left.value().IsValid()) {
        layoutRegionMargin->left = std::nullopt;
    }
    if (layoutRegionMargin->right.has_value() && !layoutRegionMargin->right.value().IsValid()) {
        layoutRegionMargin->right = std::nullopt;
    }
    if (layoutRegionMargin->top.has_value() && !layoutRegionMargin->top.value().IsValid()) {
        layoutRegionMargin->top = std::nullopt;
    }
    if (layoutRegionMargin->bottom.has_value() && !layoutRegionMargin->bottom.value().IsValid()) {
        layoutRegionMargin->bottom = std::nullopt;
    }
    layoutRegionMargin->start = layoutRegionMargin->left;
    layoutRegionMargin->end = layoutRegionMargin->right;
    menuParam.layoutRegionMargin = layoutRegionMargin;
};

auto g_bindMenuOptionsParam = [](
    const auto& menuOptions, MenuParam& menuParam, WeakPtr<FrameNode> weakNode) {
    auto offsetVal =
        OptConvert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(menuOptions.offset);
    if (offsetVal) {
        menuParam.positionOffset.SetX(offsetVal.value().first->ConvertToPx());
        menuParam.positionOffset.SetY(offsetVal.value().second->ConvertToPx());
    }
    menuParam.placement = OptConvert<Placement>(menuOptions.placement);
    menuParam.enableHoverMode = OptConvert<bool>(menuOptions.enableHoverMode);
    menuParam.backgroundColor = OptConvert<Color>(menuOptions.backgroundColor);
    auto backgroundBlurStyle = OptConvert<BlurStyle>(menuOptions.backgroundBlurStyle);
    menuParam.backgroundBlurStyle = backgroundBlurStyle ?
        std::optional<int32_t>(static_cast<int32_t>(backgroundBlurStyle.value())) : std::nullopt;
    g_bindMenuOptionsParamCallbacks(menuOptions, menuParam, weakNode);
    auto transitionOpt = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(menuOptions.transition);
    menuParam.transition = transitionOpt.value_or(menuParam.transition);
    menuParam.hasTransitionEffect = transitionOpt.has_value();
    menuParam.enableArrow = OptConvert<bool>(menuOptions.enableArrow);
    menuParam.arrowOffset = OptConvert<CalcDimension>(menuOptions.arrowOffset);
    menuParam.placement = OptConvert<Placement>(menuOptions.placement);
    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
    if (!menuParam.placement.has_value() && (menuParam.type == NG::MenuType::MENU ||
        (menuParam.type == NG::MenuType::CONTEXT_MENU &&
        menuParam.contextMenuRegisterType == NG::ContextMenuRegisterType::CUSTOM_TYPE))) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
    auto borderRadius = OptConvert<BorderRadiusProperty>(menuOptions.borderRadius);
    if (borderRadius.has_value() && (borderRadius.value().radiusTopLeft.has_value()
        || borderRadius.value().radiusTopRight.has_value()
        || borderRadius.value().radiusBottomLeft.has_value()
        || borderRadius.value().radiusBottomRight.has_value())) {
        menuParam.borderRadius = borderRadius;
    }
    menuParam.previewBorderRadius = OptConvert<BorderRadiusProperty>(menuOptions.previewBorderRadius);
    g_parseLayoutRegionMargin(menuOptions, menuParam);
    menuParam.hapticFeedbackMode =
        OptConvert<HapticFeedbackMode>(menuOptions.hapticFeedbackMode).value_or(menuParam.hapticFeedbackMode);
    menuParam.outlineColor = OptConvert<BorderColorProperty>(menuOptions.outlineColor);
    menuParam.outlineWidth = OptConvert<BorderWidthProperty>(menuOptions.outlineWidth);
    menuParam.effectOption = OptConvert<EffectOption>(menuOptions.backgroundEffect);
    menuParam.blurStyleOption = OptConvert<BlurStyleOption>(menuOptions.backgroundBlurStyleOptions);
};

auto g_bindContextMenuParams = [](MenuParam& menuParam, const std::optional<Ark_ContextMenuOptions>& menuOption,
    Ark_NativePointer node, FrameNode* frameNode) {
    CHECK_NULL_VOID(menuOption);
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    auto weakNode = AceType::WeakClaim(frameNode);
    g_bindMenuOptionsParam(menuOption.value(), menuParam, weakNode);
    auto optParam = Converter::OptConvert<NG::MenuParam>(menuOption->previewAnimationOptions);
    if (optParam) {
        menuParam.previewAnimationOptions = optParam->previewAnimationOptions;
        if (menuParam.previewMode != MenuPreviewMode::CUSTOM ||
            optParam->hasPreviewTransitionEffect || optParam->hasTransitionEffect ||
            menuParam.contextMenuRegisterType == NG::ContextMenuRegisterType::CUSTOM_TYPE) {
            return;
        }
        menuParam.hasPreviewTransitionEffect = optParam->hasPreviewTransitionEffect;
        menuParam.previewTransition = optParam->previewTransition;
        menuParam.hoverImageAnimationOptions = optParam->hoverImageAnimationOptions;
        menuParam.isShowHoverImage = optParam->isShowHoverImage;
    }
};

Dimension ClampAngleDimension(const std::optional<Dimension>& angle, float minAngle, float maxAngle)
{
    if (!angle) {
        return CalcDimension(0.0f, DimensionUnit::PX);
    }

    float value = angle.value().Value();
    if (LessOrEqual(value, minAngle)) {
        value = minAngle;
    } else if (GreatOrEqual(value, maxAngle)) {
        value = maxAngle;
    }
    return CalcDimension(value, DimensionUnit::PX);
}

void FixBorderWidthDimension(std::optional<Dimension>& dim, bool nonPercent, bool nonNegative, bool resetZero)
{
    bool hasValue = dim.has_value();
    if (nonPercent) {
        Validator::ValidateNonPercent(dim);
    }
    if (nonNegative) {
        Validator::ValidateNonNegative(dim);
    }
    if (resetZero && hasValue) {
        dim = dim.value_or(Dimension(0));
    }
}

void FixBorderWidthProperty(BorderWidthProperty& prop, bool nonPercent, bool nonNegative, bool resetZero)
{
    FixBorderWidthDimension(prop.leftDimen, nonPercent, nonNegative, resetZero);
    FixBorderWidthDimension(prop.topDimen, nonPercent, nonNegative, resetZero);
    FixBorderWidthDimension(prop.rightDimen, nonPercent, nonNegative, resetZero);
    FixBorderWidthDimension(prop.bottomDimen, nonPercent, nonNegative, resetZero);
}

namespace GeneratedModifier {
namespace CommonMethodModifier {
void SetBackgroundEffect1Impl(
    Ark_NativePointer node, const Opt_BackgroundEffectOptions* options, const Opt_SystemAdaptiveOptions* sysOptions);
} // namespace CommonMethodModifier
}

namespace Validator {
void ValidateNonNegative(std::optional<InvertVariant>& value)
{
    if (!value.has_value()) {
        return;
    }
    auto& invertVariant = value.value();
    if (auto optionPtr = std::get_if<InvertOption>(&invertVariant)) {
        const InvertOption& option = *optionPtr;
        if (Negative(option.low_) || Negative(option.high_) ||
            Negative(option.threshold_) || Negative(option.thresholdRange_)) {
            value.reset();
            return;
        }
    }
    if (auto floatPtr = std::get_if<float>(&invertVariant)) {
        if (Negative(*floatPtr)) {
            value.reset();
        }
    }
}
void ValidateByRange(std::optional<InvertVariant>& value, const float& left, const float& right)
{
    if (!value.has_value()) {
        return;
    }
    auto& invertVariant = value.value();
    if (auto optionPtr = std::get_if<InvertOption>(&invertVariant)) {
        optionPtr->low_ = std::clamp(optionPtr->low_, left, right);
        optionPtr->high_ = std::clamp(optionPtr->high_, left, right);
        optionPtr->threshold_ = std::clamp(optionPtr->threshold_, left, right);
        optionPtr->thresholdRange_ = std::clamp(optionPtr->thresholdRange_, left, right);
    }
    if (auto floatPtr = std::get_if<float>(&invertVariant)) {
        *floatPtr = std::clamp(*floatPtr, left, right);
    }
}
} // namespace Validator

namespace Converter {
template<>
ChainWeightPair Convert(const Ark_ChainWeightOptions& src)
{
    return ChainWeightPair(
        Converter::OptConvert<float>(src.horizontal),
        Converter::OptConvert<float>(src.vertical));
}

template<>
SetFocusData Convert(const Ark_FocusMovement& src)
{
    return {
        .forward = OptConvert<std::string>(src.forward),
        .backward = OptConvert<std::string>(src.backward),
        .up = OptConvert<std::string>(src.up),
        .down = OptConvert<std::string>(src.down),
        .left = OptConvert<std::string>(src.left),
        .right = OptConvert<std::string>(src.right)
    };
}

template<>
MenuPreviewAnimationOptions Convert(const Ark_AnimationNumberRange& options)
{
    auto scaleFrom = Convert<float>(options.value0);
    auto scaleTo = Convert<float>(options.value1);
    return {
        .scaleFrom = LessOrEqual(scaleFrom, 0.0) ? -1.0f : scaleFrom,
        .scaleTo = LessOrEqual(scaleTo, 0.0) ? -1.0f : scaleTo
    };
}

template<>
NG::MenuParam Convert(const Ark_ContextMenuAnimationOptions& options)
{
    NG::MenuParam menuParam;
    auto scale = OptConvert<MenuPreviewAnimationOptions>(options.scale);
    if (scale) {
        menuParam.previewAnimationOptions = *scale;
    }
    menuParam.hasPreviewTransitionEffect = false;
    auto previewTransition = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(options.transition);
    if (previewTransition && *previewTransition) {
        menuParam.hasPreviewTransitionEffect = true;
        menuParam.previewTransition = *previewTransition;
    }
    auto hoverScale = OptConvert<MenuPreviewAnimationOptions>(options.hoverScale);
    menuParam.isShowHoverImage = false;
    if (hoverScale) {
        menuParam.hoverImageAnimationOptions = *hoverScale;
        menuParam.isShowHoverImage = true;
    }
    return menuParam;
}

template<>
void AssignCast(std::optional<BackgroundImageSizeType>& dst, const Ark_ImageSize& src)
{
    switch (src) {
        case ARK_IMAGE_SIZE_AUTO: dst = BackgroundImageSizeType::AUTO; break;
        case ARK_IMAGE_SIZE_COVER: dst = BackgroundImageSizeType::COVER; break;
        case ARK_IMAGE_SIZE_CONTAIN: dst = BackgroundImageSizeType::CONTAIN; break;
        case ARK_IMAGE_SIZE_FILL: dst = BackgroundImageSizeType::FILL; break;
        default: LOGE("Unexpected enum value in Ark_ImageSize: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<std::pair<double, double>>& dst, const Ark_Alignment& src)
{
    switch (src) {
        case ARK_ALIGNMENT_TOP_START: dst = { 0.0, 0.0 }; break;
        case ARK_ALIGNMENT_TOP: dst = { HALF_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_TOP_END: dst = { FULL_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_START: dst = { 0.0, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_CENTER: dst = { HALF_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_END: dst = { FULL_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_START: dst = { 0.0, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM: dst = { HALF_DIMENSION, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_END: dst = { FULL_DIMENSION, FULL_DIMENSION }; break;
        default: LOGE("Unexpected enum value in Ark_Alignment: %{public}d", src);
    }
}

template<>
MotionPathOption Convert(const Ark_MotionPathOptions& src)
{
    MotionPathOption p;
    p.SetPath(Converter::Convert<std::string>(src.path));
    if (auto opt = Converter::OptConvert<float>(src.from); opt) {
        p.SetBegin(*opt);
    }
    if (auto opt = Converter::OptConvert<float>(src.to); opt) {
        p.SetEnd(*opt);
    }
    if (auto opt = Converter::OptConvert<bool>(src.rotatable); opt) {
        p.SetRotate(*opt);
    }
    return p;
}

template<>
OHOS::Ace::SharedTransitionOption Convert(const Ark_sharedTransitionOptions& src)
{
    OHOS::Ace::SharedTransitionOption o;
    constexpr int32_t defaultDuration = 1000;
    o.duration = defaultDuration;
    if (auto opt = Converter::OptConvert<RefPtr<Curve>>(src.curve); opt) {
        o.curve = *opt;
    }
    if (!o.curve) {
        o.curve = Curves::LINEAR;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.duration); opt) {
        o.duration = *opt;
        if (o.duration < 0) {
            o.duration = defaultDuration;
        }
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.delay); opt) {
        o.delay = *opt;
        if (o.delay < 0) {
            o.delay = 0;
        }
    }
    if (auto opt = Converter::OptConvert<MotionPathOption>(src.motionPath); opt) {
        o.motionPathOption = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.zIndex); opt) {
        o.zIndex = *opt;
    }
    if (auto opt = Converter::OptConvert<SharedTransitionEffectType>(src.type); opt) {
        o.type = *opt;
    }
    return o;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Position& src)
{
    OffsetT<Dimension> offset;
    std::optional<Dimension> x = Converter::OptConvert<Dimension>(src.x);
    if (x) {
        offset.SetX(x.value());
    }
    std::optional<Dimension> y = Converter::OptConvert<Dimension>(src.y);
    if (y) {
        offset.SetY(y.value());
    }
    return offset;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Edges& src)
{
    EdgesParamOptions edgesParamOptions;
    edgesParamOptions.value = Converter::Convert<EdgesParam>(src);
    edgesParamOptions.isLocalized = false;
    return edgesParamOptions;
}

template<>
OffsetOrEdgesParam Convert(const Ark_LocalizedEdges& src)
{
    return EdgesParamOptions {
        .value = EdgesParam {
            .top = OptConvert<Dimension>(src.top),
            .left = OptConvert<Dimension>(src.start),
            .bottom = OptConvert<Dimension>(src.bottom),
            .right = OptConvert<Dimension>(src.end),
            .start = OptConvert<Dimension>(src.start),
            .end = OptConvert<Dimension>(src.end),
        },
        .isLocalized = true
    };
}

template<>
Gradient Convert(const Ark_RadialGradientOptions& src)
{
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);

    // center
    auto centerX = Converter::OptConvert<Dimension>(src.center.value0);
    if (centerX) {
        gradient.GetRadialGradient()->radialCenterX = IsPercent(*centerX) ? *centerX * PERCENT_100 : *centerX;
    }

    auto centerY = Converter::OptConvert<Dimension>(src.center.value1);
    if (centerY) {
        gradient.GetRadialGradient()->radialCenterY = IsPercent(*centerY) ? *centerY * PERCENT_100 : *centerY;
    }

    // radius
    std::optional<Dimension> radiusOpt = Converter::OptConvert<Dimension>(src.radius);
    if (radiusOpt) {
        // radius should be positive [0, +∞)
        Dimension radius = radiusOpt.value().IsNonPositive() ? Dimension(0, DimensionUnit::VP) : radiusOpt.value();
        gradient.GetRadialGradient()->radialVerticalSize = radius;
        gradient.GetRadialGradient()->radialHorizontalSize = radius;
    }

    // repeating
    std::optional<bool> repeating = Converter::OptConvert<bool>(src.repeating);
    if (repeating) {
        gradient.SetRepeat(repeating.value());
    }

    // color stops
    std::vector<GradientColor> colorStops = Converter::Convert<std::vector<GradientColor>>(src.colors);
    for (GradientColor gradientColor : colorStops) {
        gradient.AddColor(gradientColor);
    }

    return gradient;
}

template<>
BackgroundImageSize Convert(const Ark_SizeOptions& src)
{
    BackgroundImageSize imageSize;
    CalcDimension width;
    CalcDimension height;
    auto widthOpt = Converter::OptConvert<Dimension>(src.width);
    if (widthOpt) {
        width = widthOpt.value();
    }
    auto heightOpt = Converter::OptConvert<Dimension>(src.height);
    if (heightOpt) {
        height = heightOpt.value();
    }
    double valueWidth = width.ConvertToPx();
    double valueHeight = height.ConvertToPx();
    BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
    BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
    if (width.Unit() == DimensionUnit::PERCENT) {
        typeWidth = BackgroundImageSizeType::PERCENT;
        valueWidth = width.Value() * FULL_IMG_SIZE;
    }
    if (height.Unit() == DimensionUnit::PERCENT) {
        typeHeight = BackgroundImageSizeType::PERCENT;
        valueHeight = height.Value() * FULL_IMG_SIZE;
    }
    imageSize.SetSizeTypeX(typeWidth);
    imageSize.SetSizeValueX(valueWidth);
    imageSize.SetSizeTypeY(typeHeight);
    imageSize.SetSizeValueY(valueHeight);
    return imageSize;
}

template<>
BackgroundImageSize Convert(const Ark_ImageSize& src)
{
    auto sizeType = OptConvert<BackgroundImageSizeType>(src).value_or(BackgroundImageSizeType::AUTO);
    BackgroundImageSize imageSize;
    imageSize.SetSizeTypeX(sizeType);
    imageSize.SetSizeTypeY(sizeType);
    return imageSize;
}

template<>
TranslateOpt Convert(const Ark_TranslateOptions& src)
{
    TranslateOpt translateOptions;
    translateOptions.x = OptConvert<Dimension>(src.x);
    translateOptions.y = OptConvert<Dimension>(src.y);
    translateOptions.z = OptConvert<Dimension>(src.z);
    return translateOptions;
}

template<>
std::vector<DimensionRect> Convert(const Ark_Rectangle &src)
{
    return { Convert<DimensionRect>(src) };
}

using PixelRoundPolicyOneRule = bool; // let rule 'Ceil' is false, rool 'FLoor' is true

template<>
void AssignCast(std::optional<PixelRoundPolicyOneRule>& dst, const Ark_PixelRoundCalcPolicy& src)
{
    if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_CEIL) {
        dst = false;
    }
    if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_FLOOR) {
        dst = true;
    }
}

template<>
uint16_t Convert(const Ark_PixelRoundPolicy& src)
{
    uint16_t dst = 0;
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.start); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_START : PixelRoundPolicy::FORCE_CEIL_START;
        dst |= static_cast<uint16_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.end); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_END : PixelRoundPolicy::FORCE_CEIL_END;
        dst |= static_cast<uint16_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.top); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_TOP : PixelRoundPolicy::FORCE_CEIL_TOP;
        dst |= static_cast<uint16_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.bottom); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_BOTTOM : PixelRoundPolicy::FORCE_CEIL_BOTTOM;
        dst |= static_cast<uint16_t>(policy);
    }
    return dst;
}

template<>
float Convert(const Ark_ForegroundEffectOptions& src)
{
    return Convert<float>(src.radius);
}

template<>
BorderRadiusProperty Convert(const Ark_OutlineRadiuses& src)
{
    BorderRadiusProperty dst;
    dst.radiusTopLeft = OptConvert<Dimension>(src.topLeft);
    dst.radiusTopRight = OptConvert<Dimension>(src.topRight);
    dst.radiusBottomLeft = OptConvert<Dimension>(src.bottomLeft);
    dst.radiusBottomRight = OptConvert<Dimension>(src.bottomRight);
    dst.multiValued = true;
    return dst;
}

template<>
void AssignCast(std::optional<BorderStyle>& dst, const Ark_OutlineStyle& src)
{
    switch (src) {
        case ARK_OUTLINE_STYLE_DOTTED: dst = BorderStyle::DOTTED; break;
        case ARK_OUTLINE_STYLE_DASHED: dst = BorderStyle::DASHED; break;
        case ARK_OUTLINE_STYLE_SOLID: dst = BorderStyle::SOLID; break;
        default: LOGE("Unexpected enum value in Ark_OutlineStyle: %{public}d", src);
    }
}

template<>
BorderStyleProperty Convert(const Ark_OutlineStyle& src)
{
    BorderStyleProperty dst;
    if (auto styleOpt = OptConvert<BorderStyle>(src); styleOpt) {
        dst.SetBorderStyle(*styleOpt);
    }
    return dst;
}

template<>
BorderStyleProperty Convert(const Ark_EdgeOutlineStyles& src)
{
    BorderStyleProperty dst;
    dst.styleLeft = OptConvert<BorderStyle>(src.left);
    dst.styleRight = OptConvert<BorderStyle>(src.right);
    dst.styleTop = OptConvert<BorderStyle>(src.top);
    dst.styleBottom = OptConvert<BorderStyle>(src.bottom);
    dst.multiValued = true;
    return dst;
}
template<>
InvertVariant Convert(const Ark_Number& value)
{
    float fDst = Converter::Convert<float>(value);
    return std::variant<float, InvertOption>(fDst);
}
template<>
InvertVariant Convert(const Ark_InvertOptions& value)
{
    InvertOption invertOption = {
        .low_ = Converter::Convert<float>(value.low),
        .high_ = Converter::Convert<float>(value.high),
        .threshold_ = Converter::Convert<float>(value.threshold),
        .thresholdRange_ = Converter::Convert<float>(value.thresholdRange)};
    return std::variant<float, InvertOption>(invertOption);
}
template<>
float Convert(const Ark_InvertOptions& value)
{
    auto low = Converter::Convert<float>(value.low);
    auto high = Converter::Convert<float>(value.high);
    auto threshold = Converter::Convert<float>(value.threshold);
    auto thresholdRange = Converter::Convert<float>(value.thresholdRange);
    if (NearEqual(low, high) && NearEqual(low, threshold) && NearEqual(low, thresholdRange)) {
        return low;
    }
    float invalidValue = -1.0;
    return invalidValue;
}
template<>
void AssignCast(std::optional<float>& dst, const Ark_InvertOptions& src)
{
    auto low = Converter::Convert<float>(src.low);
    auto high = Converter::Convert<float>(src.high);
    auto threshold = Converter::Convert<float>(src.threshold);
    auto thresholdRange = Converter::Convert<float>(src.thresholdRange);
    if (NearEqual(low, high) && NearEqual(low, threshold) && NearEqual(low, thresholdRange)) {
        dst = low;
        return;
    }
    dst.reset();
}
template<>
void AssignCast(std::optional<PixStretchEffectOption>& dst, const Ark_PixelStretchEffectOptions& src)
{
    auto invalidValue = 0.0_vp;
    auto top = OptConvert<Dimension>(src.top);
    auto bottom = OptConvert<Dimension>(src.bottom);
    auto left = OptConvert<Dimension>(src.left);
    auto right = OptConvert<Dimension>(src.right);
    if (!top.has_value() && !bottom.has_value() && !left.has_value() && !right.has_value()) {
        dst = std::nullopt;
        return;
    }
    dst = {.left = left.value_or(invalidValue), .top = top.value_or(invalidValue),
        .right = right.value_or(invalidValue), .bottom = bottom.value_or(invalidValue)};
}

template<>
PositionWithLocalization Convert(const Ark_Position& src)
{
    auto x = Converter::OptConvert<Dimension>(src.x);
    auto y = Converter::OptConvert<Dimension>(src.y);
    if (!x && !y) {
        return PositionWithLocalization {std::nullopt, false};
    }
    auto offsetOpt = std::make_optional<OffsetT<Dimension>>();
    if (x) {
        offsetOpt->SetX(*x);
    }
    if (y) {
        offsetOpt->SetY(*y);
    }
    return PositionWithLocalization {offsetOpt, false};
}

template<>
PositionWithLocalization Convert(const Ark_LocalizedPosition& src)
{
    auto start = Converter::OptConvert<Dimension>(src.start);
    auto top = Converter::OptConvert<Dimension>(src.top);
    auto offsetOpt = std::make_optional<OffsetT<Dimension>>();
    if (start.has_value()) {
        offsetOpt->SetX(start.value());
    }
    if (top.has_value()) {
        offsetOpt->SetY(top.value());
    }
    return PositionWithLocalization {offsetOpt, true};
}

template<>
ButtonProperties Convert(const Ark_PopupButton& src)
{
    ButtonProperties properties;
    properties.value = Converter::Convert<std::string>(src.value);
    auto clickCallback = [callback = CallbackHelper(src.action)](GestureEvent& info) {
        callback.Invoke();
    };
    properties.action = AceType::MakeRefPtr<NG::ClickEvent>(clickCallback);
    properties.showButton = true;
    return properties;
}

template<>
void AssignCast(std::optional<HorizontalAlign>& dst, const Ark_HorizontalAlign& src)
{
    switch (src) {
        case ARK_HORIZONTAL_ALIGN_START: dst = HorizontalAlign::START; break;
        case ARK_HORIZONTAL_ALIGN_END: dst = HorizontalAlign::END; break;
        case ARK_HORIZONTAL_ALIGN_CENTER: dst = HorizontalAlign::CENTER; break;
        default: LOGE("Unexpected enum value in Ark_HorizontalAlign: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<VerticalAlign>& dst, const Ark_VerticalAlign& src)
{
    switch (src) {
        case ARK_VERTICAL_ALIGN_TOP: dst = VerticalAlign::TOP; break;
        case ARK_VERTICAL_ALIGN_BOTTOM: dst = VerticalAlign::BOTTOM; break;
        case ARK_VERTICAL_ALIGN_CENTER: dst = VerticalAlign::CENTER; break;
        default: LOGE("Unexpected enum value in Ark_VerticalAlign: %{public}d", src);
    }
}

template<>
AlignRule Convert(const Ark_LocalizedHorizontalAlignParam& src)
{
    AlignRule rule;
    rule.anchor = Convert<std::string>(src.anchor);
    auto align = OptConvert<HorizontalAlign>(src.align);
    if (align.has_value()) {
        rule.horizontal = align.value();
    }
    return rule;
}

template<>
AlignRule Convert(const Ark_LocalizedVerticalAlignParam& src)
{
    AlignRule rule;
    rule.anchor = Convert<std::string>(src.anchor);
    auto align = OptConvert<VerticalAlign>(src.align);
    if (align.has_value()) {
        rule.vertical = align.value();
    }
    return rule;
}

template<>
std::map<AlignDirection, AlignRule> Convert(const Ark_AlignRuleOption& src)
{
    LOGE("Ark_AlignRuleOption is stubbed");
    std::map<AlignDirection, AlignRule> rulesMap;
#ifdef WRONG_GEN
    auto rule = OptConvert<AlignRule>(src.left);
    if (rule.has_value()) {
        rulesMap[AlignDirection::LEFT] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.right);
    if (rule.has_value()) {
        rulesMap[AlignDirection::RIGHT] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.middle);
    if (rule.has_value()) {
        rulesMap[AlignDirection::MIDDLE] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.top);
    if (rule.has_value()) {
        rulesMap[AlignDirection::TOP] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.bottom);
    if (rule.has_value()) {
        rulesMap[AlignDirection::BOTTOM] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.center);
    if (rule.has_value()) {
        rulesMap[AlignDirection::CENTER] = rule.value();
    }
#endif
    return rulesMap;
}

template<>
std::map<AlignDirection, AlignRule> Convert(const Ark_LocalizedAlignRuleOptions& src)
{
    std::map<AlignDirection, AlignRule> rulesMap;
    auto rule = OptConvert<AlignRule>(src.start);
    if (rule.has_value()) {
        rulesMap[AlignDirection::LEFT] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.end);
    if (rule.has_value()) {
        rulesMap[AlignDirection::RIGHT] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.middle);
    if (rule.has_value()) {
        rulesMap[AlignDirection::MIDDLE] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.top);
    if (rule.has_value()) {
        rulesMap[AlignDirection::TOP] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.bottom);
    if (rule.has_value()) {
        rulesMap[AlignDirection::BOTTOM] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.center);
    if (rule.has_value()) {
        rulesMap[AlignDirection::CENTER] = rule.value();
    }
    return rulesMap;
}

template<>
BiasOpt Convert(const Ark_Bias& src)
{
    BiasOpt bias;
    bias.first = OptConvert<float>(src.horizontal);
    bias.second = OptConvert<float>(src.vertical);
    return bias;
}

template<>
void AssignCast(std::optional<uint32_t>& dst, const Ark_FocusPriority& src)
{
    switch (src) {
        case ARK_FOCUS_PRIORITY_AUTO: dst = FOCUS_PRIORITY_AUTO; break;
        case ARK_FOCUS_PRIORITY_PRIOR: dst = FOCUS_PRIORITY_PRIOR; break;
        case ARK_FOCUS_PRIORITY_PREVIOUS: dst = FOCUS_PRIORITY_PREVIOUS; break;
        default: LOGE("Unexpected enum value in Ark_FocusPriority: %{public}d", src);
    }
}

template<>
OHOS::Ace::Color Convert(const Ark_ColorMetrics& src)
{
    uint8_t red = static_cast<uint8_t>(Converter::Convert<uint32_t>(src.red_));
    uint8_t green = static_cast<uint8_t>(Converter::Convert<uint32_t>(src.green_));
    uint8_t blue = static_cast<uint8_t>(Converter::Convert<uint32_t>(src.blue_));
    uint8_t alpha = static_cast<uint8_t>(Converter::Convert<uint32_t>(src.alpha_));
    return Color::FromARGB(alpha, red, green, blue);
}

template<>
FocusBoxStyle Convert(const Ark_FocusBoxStyle& src)
{
    FocusBoxStyle style;
    style.strokeWidth = Converter::OptConvert<Dimension>(src.strokeWidth);
    style.strokeColor = Converter::OptConvert<Color>(src.strokeColor);
    style.margin = Converter::OptConvert<Dimension>(src.margin);
    return style;
}

template<>
MotionBlurOption Convert(const Ark_MotionBlurOptions& src)
{
    MotionBlurOption options;
    const float minValue = 0.0;
    const float maxValue = 1.0;
    options.radius = Convert<float>(src.radius);
    if (LessNotEqual(options.radius, minValue)) {
        options.radius = minValue;
    }
    options.anchor.x = Convert<float>(src.anchor.x);
    if (LessNotEqual(options.anchor.x, minValue)) {
        options.anchor.x = minValue;
    }
    if (GreatNotEqual(options.anchor.x, maxValue)) {
        options.anchor.x = maxValue;
    }
    options.anchor.y = Convert<float>(src.anchor.y);
    if (LessNotEqual(options.anchor.y, minValue)) {
        options.anchor.y = minValue;
    }
    if (GreatNotEqual(options.anchor.y, maxValue)) {
        options.anchor.y = maxValue;
    }
    return options;
}

template<>
RotateOpt Convert(const Ark_RotateOptions& src)
{
    RotateOpt options;
    options.vec5f.emplace_back(OptConvert<float>(src.x));
    options.vec5f.emplace_back(OptConvert<float>(src.y));
    options.vec5f.emplace_back(OptConvert<float>(src.z));
    options.vec5f.emplace_back(OptConvert<float>(src.angle));
    options.vec5f.emplace_back(OptConvert<float>(src.perspective));

    auto centerX =  OptConvert<Dimension>(src.centerX);
    auto centerY =  OptConvert<Dimension>(src.centerY);
    auto center = DimensionOffset(Dimension(0.5f, DimensionUnit::PERCENT), Dimension(0.5f, DimensionUnit::PERCENT));
    center.SetZ(Dimension(0.5f, DimensionUnit::PERCENT));
    if (centerX.has_value()) {
        center.SetX(centerX.value());
    }
    if (centerY.has_value()) {
        center.SetY(centerY.value());
    }
    auto centerZ =  OptConvert<Dimension>(src.centerZ);
    if (centerZ.has_value()) {
        center.SetZ(centerZ.value());
    }
    options.center = center;
    return options;
}

template<>
RotateAngleOpt Convert(const Ark_RotateAngleOptions& src)
{
    RotateAngleOpt options;
    options.vec4f.emplace_back(OptConvert<float>(src.angleX));
    options.vec4f.emplace_back(OptConvert<float>(src.angleY));
    options.vec4f.emplace_back(OptConvert<float>(src.angleZ));
    options.vec4f.emplace_back(OptConvert<float>(src.perspective));

    auto centerX =  OptConvert<Dimension>(src.centerX);
    auto centerY =  OptConvert<Dimension>(src.centerY);
    auto center = DimensionOffset(Dimension(0.5f, DimensionUnit::PERCENT), Dimension(0.5f, DimensionUnit::PERCENT));
    center.SetZ(Dimension(0.5f, DimensionUnit::PERCENT));
    if (centerX.has_value()) {
        center.SetX(centerX.value());
    }
    if (centerY.has_value()) {
        center.SetY(centerY.value());
    }
    auto centerZ =  OptConvert<Dimension>(src.centerZ);
    if (centerZ.has_value()) {
        center.SetZ(centerZ.value());
    }
    options.center = center;
    return options;
}

template<>
void AssignCast(std::optional<TransitionType>& dst, const Ark_TransitionType& src)
{
    switch (src) {
        case ARK_TRANSITION_TYPE_ALL: dst = TransitionType::ALL; break;
        case ARK_TRANSITION_TYPE_INSERT: dst = TransitionType::APPEARING; break;
        case ARK_TRANSITION_TYPE_DELETE: dst = TransitionType::DISAPPEARING; break;
        default: LOGE("Unexpected enum value in Opt_TransitionType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<FocusDrawLevel>& dst, const Ark_FocusDrawLevel& src)
{
    switch (src) {
        case ARK_FOCUS_DRAW_LEVEL_SELF: dst = FocusDrawLevel::SELF; break;
        case ARK_FOCUS_DRAW_LEVEL_TOP: dst = FocusDrawLevel::TOP; break;
        default: LOGE("Unexpected enum value in Ark_FocusDrawLevel: %{public}d", src);
    }
}

template<>
ScaleOptions Convert(const Ark_ScaleOptions& src)
{
    ScaleOptions scaleOptions(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto coord = OptConvert<float>(src.x);
    if (coord.has_value()) {
        scaleOptions.xScale = coord.value();
    }
    coord = OptConvert<float>(src.y);
    if (coord.has_value()) {
        scaleOptions.yScale = coord.value();
    }
    coord = OptConvert<float>(src.z);
    if (coord.has_value()) {
        scaleOptions.zScale = coord.value();
    }

    auto center = OptConvert<Dimension>(src.centerX);
    if (center.has_value()) {
        scaleOptions.centerX = center.value();
    }
    center = OptConvert<Dimension>(src.centerY);
    if (center.has_value()) {
        scaleOptions.centerY = center.value();
    }
    return scaleOptions;
}

RotateAngleOptions Convert(const Ark_RotateAngleOptions& src)
{
    RotateAngleOptions rotateOptions(0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct, 0.5_pct);
    // The value of centerZ is 50%, which is equivalent to 0 when finally set to the RS because not support percent.
    auto coordX = OptConvert<float>(src.angleX);
    auto coordY = OptConvert<float>(src.angleY);
    auto coordZ = OptConvert<float>(src.angleZ);
    if (!coordX && !coordY && !coordZ) {
        rotateOptions.angleZ = 1.0f;
    } else {
        if (coordX.has_value()) {
            rotateOptions.angleX = coordX.value();
        }
        if (coordY.has_value()) {
            rotateOptions.angleY = coordY.value();
        }
        if (coordZ.has_value()) {
            rotateOptions.angleZ = coordZ.value();
        }
    }
    auto perspective = OptConvert<float>(src.perspective);
    if (perspective.has_value()) {
        rotateOptions.perspective = perspective.value();
    }
    auto center = OptConvert<Dimension>(src.centerX);
    if (center.has_value()) {
        rotateOptions.centerX = center.value();
    }
    center = OptConvert<Dimension>(src.centerY);
    if (center.has_value()) {
        rotateOptions.centerY = center.value();
    }
    center = OptConvert<Dimension>(src.centerZ);
    if (center.has_value()) {
        rotateOptions.centerZ = center.value();
    }
    return rotateOptions;
}

template<>
RotateOptions Convert(const Ark_RotateOptions& src)
{
    RotateOptions rotateOptions(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct, 0.5_pct);
    // The value of centerZ is 50%, which is equivalent to 0 when finally set to the RS because not support percent.
    auto coordX = OptConvert<float>(src.x);
    auto coordY = OptConvert<float>(src.y);
    auto coordZ = OptConvert<float>(src.z);
    if (!coordX && !coordY && !coordZ) {
        rotateOptions.zDirection = 1.0f;
    } else {
        if (coordX.has_value()) {
            rotateOptions.xDirection = coordX.value();
        }
        if (coordY.has_value()) {
            rotateOptions.yDirection = coordY.value();
        }
        if (coordZ.has_value()) {
            rotateOptions.zDirection = coordZ.value();
        }
    }
    auto angle = OptConvert<float>(src.angle);
    if (angle.has_value()) {
        rotateOptions.angle = angle.value();
    }
    auto perspective = OptConvert<float>(src.perspective);
    if (perspective.has_value()) {
        rotateOptions.perspective = perspective.value();
    }
    auto center = OptConvert<Dimension>(src.centerX);
    if (center.has_value()) {
        rotateOptions.centerX = center.value();
    }
    center = OptConvert<Dimension>(src.centerY);
    if (center.has_value()) {
        rotateOptions.centerY = center.value();
    }
    center = OptConvert<Dimension>(src.centerZ);
    if (center.has_value()) {
        rotateOptions.centerZ = center.value();
    }
    return rotateOptions;
}

template<>
GradientDirection Convert(const Ark_GradientDirection& value)
{
    auto optVal = OptConvert<GradientDirection>(value);
    return optVal.has_value() ? optVal.value() : GradientDirection::NONE;
}
template<>
std::pair<float, float> Convert(const Ark_FractionStop& value)
{
    return std::make_pair(Convert<float>(value.value0), Convert<float>(value.value1));
}
template<>
NG::LinearGradientBlurPara Convert(const Ark_LinearGradientBlurOptions& value)
{
    auto blurRadius = Dimension(0);
    std::pair<float, float> pair;
    std::vector<std::pair<float, float>> fractionStops;
    auto fractionStopsVec = Convert<std::vector<Ark_FractionStop>>(value.fractionStops);
    for (auto& arkPair : fractionStopsVec) {
        pair = Convert<std::pair<float, float>>(arkPair);
        fractionStops.push_back(pair);
    }
    auto direction = Convert<GradientDirection>(value.direction);
    return NG::LinearGradientBlurPara(blurRadius, fractionStops, direction);
}
template<>
ClickEffectLevel Convert(const Ark_ClickEffectLevel& src)
{
    switch (src) {
        case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_LIGHT:
            return ClickEffectLevel::LIGHT;
        case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_MIDDLE:
            return ClickEffectLevel::MIDDLE;
        case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_HEAVY:
            return ClickEffectLevel::HEAVY;
        default:
            return ClickEffectLevel::UNDEFINED;
    }
}
template<>
void AssignCast(std::optional<ClickEffectLevel>& dst, const Ark_ClickEffectLevel& src)
{
    auto arkVal = Convert<ClickEffectLevel>(src);
    dst = arkVal == ClickEffectLevel::UNDEFINED ? std::nullopt :
        std::optional<ClickEffectLevel>(arkVal);
}
template<>
void AssignCast(std::optional<DragDropInfo>& dst, const Ark_String& src)
{
    auto vDst = DragDropInfo();
    vDst.extraInfo = Convert<std::string>(src);
    dst = vDst;
}

template<>
void AssignCast(std::optional<OHOS::Ace::ObscuredReasons>& dst, const Ark_ObscuredReasons& src)
{
    switch (src) {
        case ARK_OBSCURED_REASONS_PLACEHOLDER: dst = ObscuredReasons::PLACEHOLDER; break;
        default: LOGE("Unexpected enum value in Ark_ObscuredReasons: %{public}d", src);
    }
}

template<>
    void AssignCast(std::optional<uint32_t>& dst, const Ark_SafeAreaType& src)
{
    switch (src) {
        case ARK_SAFE_AREA_TYPE_SYSTEM: dst = SAFE_AREA_TYPE_SYSTEM; break;
        case ARK_SAFE_AREA_TYPE_CUTOUT: dst = SAFE_AREA_TYPE_CUTOUT; break;
        case ARK_SAFE_AREA_TYPE_KEYBOARD: dst = SAFE_AREA_TYPE_KEYBOARD; break;
        default: LOGE("Unexpected enum value in Ark_SafeAreaType: %{public}d", src);
    }
}

template<>
    void AssignCast(std::optional<uint32_t>& dst, const Ark_SafeAreaEdge& src)
{
    switch (src) {
        case ARK_SAFE_AREA_EDGE_TOP: dst = SAFE_AREA_EDGE_TOP; break;
        case ARK_SAFE_AREA_EDGE_BOTTOM: dst = SAFE_AREA_EDGE_BOTTOM; break;
        case ARK_SAFE_AREA_EDGE_START: dst = SAFE_AREA_EDGE_START; break;
        case ARK_SAFE_AREA_EDGE_END: dst = SAFE_AREA_EDGE_END; break;
        default: LOGE("Unexpected enum value in Ark_SafeAreaEdge: %{public}d", src);
    }
}

template<>
    void AssignCast(std::optional<RenderFit>& dst, const Ark_RenderFit& src)
{
    switch (src) {
        case ARK_RENDER_FIT_CENTER: dst = RenderFit::CENTER; break;
        case ARK_RENDER_FIT_TOP: dst = RenderFit::TOP; break;
        case ARK_RENDER_FIT_BOTTOM: dst = RenderFit::BOTTOM; break;
        case ARK_RENDER_FIT_LEFT: dst = RenderFit::LEFT; break;
        case ARK_RENDER_FIT_RIGHT: dst = RenderFit::RIGHT; break;
        case ARK_RENDER_FIT_TOP_LEFT: dst = RenderFit::TOP_LEFT; break;
        case ARK_RENDER_FIT_TOP_RIGHT: dst = RenderFit::TOP_RIGHT; break;
        case ARK_RENDER_FIT_BOTTOM_LEFT: dst = RenderFit::BOTTOM_LEFT; break;
        case ARK_RENDER_FIT_BOTTOM_RIGHT: dst = RenderFit::BOTTOM_RIGHT; break;
        case ARK_RENDER_FIT_RESIZE_FILL: dst = RenderFit::RESIZE_FILL; break;
        case ARK_RENDER_FIT_RESIZE_CONTAIN: dst = RenderFit::RESIZE_CONTAIN; break;
        case ARK_RENDER_FIT_RESIZE_CONTAIN_TOP_LEFT: dst = RenderFit::RESIZE_CONTAIN_TOP_LEFT; break;
        case ARK_RENDER_FIT_RESIZE_CONTAIN_BOTTOM_RIGHT: dst = RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT; break;
        case ARK_RENDER_FIT_RESIZE_COVER: dst = RenderFit::RESIZE_COVER; break;
        case ARK_RENDER_FIT_RESIZE_COVER_TOP_LEFT: dst = RenderFit::RESIZE_COVER_TOP_LEFT; break;
        case ARK_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT: dst = RenderFit::RESIZE_COVER_BOTTOM_RIGHT; break;
        default: LOGE("Unexpected enum value in Ark_RenderFit: %{public}d", src);
    }
}
template<>
TransitionHierarchyStrategy Convert(const Ark_TransitionHierarchyStrategy& src)
{
    if (src == ARK_TRANSITION_HIERARCHY_STRATEGY_ADAPTIVE) {
        return TransitionHierarchyStrategy::ADAPTIVE;
    }
    return TransitionHierarchyStrategy::NONE;
}
template<>
GeometryTransitionOptions Convert(const Ark_GeometryTransitionOptions& src)
{
    GeometryTransitionOptions dst;
    dst.follow = OptConvert<bool>(src.follow);
    dst.hierarchyStrategy = OptConvert<TransitionHierarchyStrategy>(src.hierarchyStrategy);
    return dst;
}

template<>
void AssignCast(std::optional<PopupKeyboardAvoidMode> &dst, const Ark_KeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_KEYBOARD_AVOID_MODE_DEFAULT: dst = PopupKeyboardAvoidMode::DEFAULT; break;
        case ARK_KEYBOARD_AVOID_MODE_NONE: dst = PopupKeyboardAvoidMode::NONE; break;
        default: LOGE("Unexpected enum value in Ark_KeyboardAvoidMode: %{public}d", src);
    }
}

template<>
RefPtr<PopupParam> Convert(const Ark_TipsOptions& src)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    auto appearingTimeOpt = Converter::OptConvert<int>(src.appearingTime);
    if (appearingTimeOpt.has_value() && appearingTimeOpt.value() >= 0) {
        popupParam->SetAppearingTime(appearingTimeOpt.value());
    }
    auto disappearingTimeOpt = Converter::OptConvert<int>(src.disappearingTime);
    if (disappearingTimeOpt.has_value() && disappearingTimeOpt.value() >= 0) {
        popupParam->SetDisappearingTime(disappearingTimeOpt.value());
    }
    auto appearingTimeWithContinuousOperationOpt =
        Converter::OptConvert<int>(src.appearingTimeWithContinuousOperation);
    if (appearingTimeWithContinuousOperationOpt.has_value() &&
        appearingTimeWithContinuousOperationOpt.value() >= 0) {
        popupParam->SetAppearingTimeWithContinuousOperation(appearingTimeWithContinuousOperationOpt.value());
    }
    auto disappearingTimeWithContinuousOperationOpt =
        Converter::OptConvert<int>(src.disappearingTimeWithContinuousOperation);
    if (disappearingTimeWithContinuousOperationOpt.has_value() &&
        disappearingTimeWithContinuousOperationOpt.value() >= 0) {
        popupParam->SetDisappearingTimeWithContinuousOperation(disappearingTimeWithContinuousOperationOpt.value());
    }
    auto enableArrowOpt = Converter::OptConvert<bool>(src.enableArrow);
    if (enableArrowOpt.has_value()) {
        popupParam->SetEnableArrow(enableArrowOpt.value());
        if (enableArrowOpt.value()) {
            auto arrowPointPositionOpt = Converter::OptConvert<Dimension>(src.arrowPointPosition);
            if (arrowPointPositionOpt.has_value()) {
                popupParam->SetArrowOffset(arrowPointPositionOpt.value());
            }
            auto arrowWidthOpt = Converter::OptConvert<CalcDimension>(src.arrowWidth);
            Validator::ValidatePositive(arrowWidthOpt);
            Validator::ValidateNonPercent(arrowWidthOpt);
            if (arrowWidthOpt.has_value()) {
                popupParam->SetArrowWidth(arrowWidthOpt.value());
            }
            auto arrowHeightOpt = Converter::OptConvert<CalcDimension>(src.arrowHeight);
            Validator::ValidatePositive(arrowHeightOpt);
            Validator::ValidateNonPercent(arrowHeightOpt);
            if (arrowHeightOpt.has_value()) {
                popupParam->SetArrowHeight(arrowHeightOpt.value());
            }
        }
    }
    return popupParam;
}

template<>
RefPtr<PopupParam> Convert(const Ark_PopupOptions& src)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetMessage(Converter::Convert<std::string>(src.message));
    auto messageOptions = Converter::OptConvert<Ark_PopupMessageOptions>(src.messageOptions);
    if (messageOptions.has_value()) {
        auto textColorOpt = Converter::OptConvert<Color>(messageOptions.value().textColor);
        if (textColorOpt.has_value()) {
            popupParam->SetTextColor(textColorOpt.value());
        }
        auto font = Converter::OptConvert<Ark_Font>(messageOptions.value().font);
        if (font.has_value()) {
            auto fontSizeOpt = Converter::OptConvert<CalcDimension>(font.value().size);
            if (fontSizeOpt.has_value()) {
                popupParam->SetFontSize(fontSizeOpt.value());
            }
            auto fontWeightOpt = Converter::OptConvert<FontWeight>(font.value().weight);
            if (fontWeightOpt.has_value()) {
                popupParam->SetFontWeight(fontWeightOpt.value());
            }
            auto fontStyleOpt = Converter::OptConvert<OHOS::Ace::FontStyle>(font.value().style);
            if (fontStyleOpt.has_value()) {
                popupParam->SetFontStyle(fontStyleOpt.value());
            }
        }
    }
    auto primaryButton = OptConvert<ButtonProperties>(src.primaryButton);
    if (primaryButton.has_value()) {
        popupParam->SetPrimaryButtonProperties(primaryButton.value());
    }
    auto secondaryButton = OptConvert<ButtonProperties>(src.secondaryButton);
    if (secondaryButton.has_value()) {
        popupParam->SetSecondaryButtonProperties(secondaryButton.value());
    }
    auto offsetOpt = Converter::OptConvert<Dimension>(src.arrowOffset);
    auto pointPositionOpt = Converter::OptConvert<Dimension>(src.arrowPointPosition);
    if (pointPositionOpt.has_value()) {
        popupParam->SetArrowOffset(pointPositionOpt.value());
    } else if (offsetOpt.has_value()) {
        popupParam->SetArrowOffset(offsetOpt.value());
    }
    popupParam->SetPlacement(OptConvert<Placement>(src.placement).value_or(Placement::BOTTOM));
    g_popupCommonParam(src, popupParam);
    g_popupCommonParamWithValidator(src, popupParam);
    return popupParam;
}
template<>
RefPtr<PopupParam> Convert(const Ark_CustomPopupOptions& src)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetFocusable(OptConvert<bool>(src.focusable).value_or(popupParam->GetFocusable()));
    popupParam->SetUseCustomComponent(true);
    auto offsetOpt = Converter::OptConvert<Dimension>(src.arrowOffset);
    auto pointPositionOpt = Converter::OptConvert<Dimension>(src.arrowPointPosition);
    if (pointPositionOpt.has_value()) {
        popupParam->SetArrowOffset(pointPositionOpt.value());
    } else if (offsetOpt.has_value()) {
        popupParam->SetArrowOffset(offsetOpt.value());
    }
    popupParam->SetPlacement(OptConvert<Placement>(src.placement).value_or(Placement::BOTTOM));
    g_popupCommonParam(src, popupParam);
    g_popupCommonParamWithValidator(src, popupParam);
    return popupParam;
}
template<>
void AssignCast(std::optional<Alignment>& dst, const Ark_BackgroundOptions& src)
{
    auto optAlign = Converter::OptConvert<Ark_Alignment>(src.align);
    if (!optAlign.has_value()) {
        dst = std::nullopt;
        return;
    }
    switch (optAlign.value()) {
        case ARK_ALIGNMENT_TOP_START: dst = Alignment::TOP_LEFT; break;
        case ARK_ALIGNMENT_TOP: dst = Alignment::TOP_CENTER; break;
        case ARK_ALIGNMENT_TOP_END: dst = Alignment::TOP_RIGHT; break;
        case ARK_ALIGNMENT_START: dst = Alignment::CENTER_LEFT; break;
        case ARK_ALIGNMENT_CENTER: dst = Alignment::CENTER; break;
        case ARK_ALIGNMENT_END: dst = Alignment::CENTER_RIGHT; break;
        case ARK_ALIGNMENT_BOTTOM_START: dst = Alignment::BOTTOM_LEFT; break;
        case ARK_ALIGNMENT_BOTTOM: dst = Alignment::BOTTOM_CENTER; break;
        case ARK_ALIGNMENT_BOTTOM_END: dst = Alignment::BOTTOM_RIGHT; break;
        default:
            dst = std::nullopt;
    }
}

template<>
void AssignCast(std::optional<TouchTestStrategy>& dst, const Ark_TouchTestStrategy& src)
{
    switch (src) {
        case ARK_TOUCH_TEST_STRATEGY_DEFAULT: dst = TouchTestStrategy::DEFAULT; break;
        case ARK_TOUCH_TEST_STRATEGY_FORWARD_COMPETITION: dst = TouchTestStrategy::FORWARD_COMPETITION; break;
        case ARK_TOUCH_TEST_STRATEGY_FORWARD: dst = TouchTestStrategy::FORWARD; break;
        default: LOGE("Unexpected enum value in Ark_TouchTestStrategy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<NG::TouchResult> &dst, const Ark_TouchResult& src)
{
    if (auto strategy = OptConvert<TouchTestStrategy>(src.strategy); strategy) {
        dst = { .strategy = *strategy };
        if (auto id = OptConvert<std::string>(src.id); id) {
            dst->id = *id;
        }
    } else {
        dst.reset();
    }
}

template<>
RefPtr<NG::NGGestureRecognizer> Convert(const Ark_GestureRecognizer &src)
{
    if (src) {
        return src->GetRecognizer().Upgrade();
    }
    return nullptr;
}

void AssignArkValue(Ark_TouchTestInfo& dst, const OHOS::Ace::NG::TouchTestInfo& src)
{
    dst.windowX = ArkValue<Ark_Number>(src.windowPoint.GetX());
    dst.windowY = ArkValue<Ark_Number>(src.windowPoint.GetY());
    dst.parentX = ArkValue<Ark_Number>(src.currentCmpPoint.GetX());
    dst.parentY = ArkValue<Ark_Number>(src.currentCmpPoint.GetY());
    dst.x = ArkValue<Ark_Number>(src.subCmpPoint.GetX());
    dst.y = ArkValue<Ark_Number>(src.subCmpPoint.GetY());
    dst.rect = ArkValue<Ark_RectResult>(src.subRect);
    dst.id = ArkValue<Ark_String>(src.id);
}
void AssignArkValue(Ark_GestureRecognizer &dst, const RefPtr<NG::NGGestureRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<GestureRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_TapRecognizer &dst, const RefPtr<NG::ClickRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<TapRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_LongPressRecognizer &dst, const RefPtr<NG::LongPressRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<LongPressRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_PanRecognizer &dst, const RefPtr<NG::PanRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<PanRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_PinchRecognizer &dst, const RefPtr<NG::PinchRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<PinchRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_SwipeRecognizer &dst, const RefPtr<NG::SwipeRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<SwipeRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_RotationRecognizer &dst, const RefPtr<NG::RotationRecognizer>& src)
{
    dst = PeerUtils::CreatePeer<RotationRecognizerPeer>();
    if (dst) {
        dst->IncRefCount();
        dst->Update(src);
    }
}
void AssignArkValue(Ark_GestureInfo &dst, const GestureInfo &src)
{
    auto tagOpt = src.GetTag();
    if (tagOpt.has_value()) {
        dst.tag.tag = InteropTag::INTEROP_TAG_STRING;
        dst.tag.value = Converter::ArkValue<Ark_String>(tagOpt.value(), Converter::FC);
    } else {
        dst.tag.tag = InteropTag::INTEROP_TAG_UNDEFINED;
    }
    dst.type = ArkValue<Ark_GestureControl_GestureType>(src.GetType());
    dst.isSystemGesture = ArkValue<Ark_Boolean>(src.IsSystemGesture());
}

template<>
void AssignCast(std::optional<GestureJudgeResult> &dst, const Ark_GestureJudgeResult& src)
{
    switch (src) {
        case ARK_GESTURE_JUDGE_RESULT_CONTINUE: dst = GestureJudgeResult::CONTINUE; break;
        case ARK_GESTURE_JUDGE_RESULT_REJECT: dst = GestureJudgeResult::REJECT; break;
        default: LOGE("Unexpected enum value in Ark_GestureJudgeResult: %{public}d", src);
    }
}

void AssignArkValue(Ark_FingerInfo& dst, const FingerInfo& src)
{
    dst.id = ArkValue<Ark_Number>(src.fingerId_);
    dst.globalX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.globalLocation_.GetX()));
    dst.globalY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.globalLocation_.GetY()));
    dst.localX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.localLocation_.GetX()));
    dst.localY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.localLocation_.GetY()));
    dst.displayX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.screenLocation_.GetX()));
    dst.displayY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(src.screenLocation_.GetY()));
    dst.hand = ArkValue<Opt_InteractionHand>(static_cast<Ark_InteractionHand>(src.operatingHand_));
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
void AssignArkValue(Ark_PreDragStatus& dst, const PreDragStatus& src)
{
    switch (src) {
        case PreDragStatus::ACTION_DETECTING_STATUS: dst = ARK_PRE_DRAG_STATUS_ACTION_DETECTING_STATUS; break;
        case PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION:
            dst = ARK_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG_ACTION;
            break;
        case PreDragStatus::PREVIEW_LIFT_STARTED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_STARTED; break;
        case PreDragStatus::PREVIEW_LIFT_FINISHED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_FINISHED; break;
        case PreDragStatus::PREVIEW_LANDING_STARTED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_STARTED; break;
        case PreDragStatus::PREVIEW_LANDING_FINISHED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_FINISHED; break;
        case PreDragStatus::ACTION_CANCELED_BEFORE_DRAG: dst = ARK_PRE_DRAG_STATUS_ACTION_CANCELED_BEFORE_DRAG; break;
        case PreDragStatus::PREPARING_FOR_DRAG_DETECTION:
            dst = ARK_PRE_DRAG_STATUS_PREPARING_FOR_DRAG_DETECTION;
            break;
        default:
            dst = static_cast<Ark_PreDragStatus>(-1);
            LOGE("Unexpected enum value in PreDragStatus: %{public}d", src);
            break;
    }
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;
constexpr float LAYOUT_HEIGHT_DEFAULT_VALUE = 0.0;

namespace CommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}
void SetWidthInternal(FrameNode *frameNode, std::optional<CalcDimension> value)
{
    Validator::ValidateNonNegative(value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (!value) {
            // Implement Reset value
            return;
        }
        CounterModelNG::SetWidth(frameNode, *value);
    } else {
        if (!value) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
            return;
        }
        ViewAbstractModelStatic::SetWidth(frameNode, *value);
    }
}
void SetWidthImpl(Ark_NativePointer node,
                  const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetWidthImpl(node, value);
        return;
    }
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_Length& src) {
            auto result = Converter::OptConvert<CalcDimension>(src);
            SetWidthInternal(frameNode, result);
        },
        [frameNode](const Ark_LayoutPolicy& src) {
            LOGE("WidthImpl: Ark_LayoutPolicy processint is not implemented yet!");
        },
        [frameNode]() {
            SetWidthInternal(frameNode, std::nullopt);
        });
}
void SetHeightInternal(FrameNode *frameNode, std::optional<CalcDimension> value)
{
    Validator::ValidateNonNegative(value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (!value) {
            // Implement Reset value
            return;
        }
        CounterModelNG::SetHeight(frameNode, *value);
    } else {
        if (!value) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstractModelStatic::SetHeight(frameNode, *value);
    }
}
void SetHeightImpl(Ark_NativePointer node,
                   const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetHeightImpl(node, value);
        return;
    }
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_Length& src) {
            auto result = Converter::OptConvert<CalcDimension>(src);
            SetHeightInternal(frameNode, result);
        },
        [frameNode](const Ark_LayoutPolicy& src) {
            LOGE("HeightImpl: Ark_LayoutPolicy processint is not implemented yet!");
        },
        [frameNode]() {
            SetHeightInternal(frameNode, std::nullopt);
        });
}
void SetDrawModifierImpl(Ark_NativePointer node,
                         const Opt_DrawModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!frameNode->IsSupportDrawModifier()) {
        return;
    }
    auto convValue = Converter::OptConvertPtr<Ark_DrawModifier>(value);
    if (!convValue) {
        return;
    }
    auto peer = convValue.value();
    CHECK_NULL_VOID(peer);
    if (!peer->drawModifier) {
        peer->drawModifier = AceType::MakeRefPtr<DrawModifier>();
    }
    peer->frameNode = AceType::WeakClaim(frameNode);
    ViewAbstractModelStatic::SetDrawModifier(frameNode, peer->drawModifier);
}
void SetResponseRegionImpl(Ark_NativePointer node,
                           const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (auto convArray = Converter::OptConvertPtr<std::vector<DimensionRect>>(value); convArray) {
        ViewAbstract::SetResponseRegion(frameNode, *convArray);
    } else {
        ViewAbstract::SetResponseRegion(frameNode, { DimensionRect() });
    }
}
void SetMouseResponseRegionImpl(Ark_NativePointer node,
                                const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (auto convArray = Converter::OptConvertPtr<std::vector<DimensionRect>>(value); convArray) {
        ViewAbstract::SetMouseResponseRegion(frameNode, *convArray);
    } else {
        ViewAbstract::SetMouseResponseRegion(frameNode, {});
    }
}
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto width = optValue ? Converter::OptConvert<CalcDimension>(optValue->width) : std::nullopt;
    auto height = optValue ? Converter::OptConvert<CalcDimension>(optValue->height) : std::nullopt;
    SetWidthInternal(frameNode, width);
    SetHeightInternal(frameNode, height);
}
void SetConstraintSizeImpl(Ark_NativePointer node,
                           const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::ResetMinSize(frameNode, true);
        ViewAbstract::ResetMaxSize(frameNode, true);
        ViewAbstract::ResetMinSize(frameNode, false);
        ViewAbstract::ResetMaxSize(frameNode, false);
        return;
    }
    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    auto minWidth = Converter::OptConvert<CalcDimension>(optValue->minWidth);
    if (minWidth) {
        ViewAbstractModelStatic::SetMinWidth(frameNode, minWidth.value());
    } else if (version10OrLarger) {
        ViewAbstract::ResetMinSize(frameNode, true);
    }
    auto minHeight = Converter::OptConvert<CalcDimension>(optValue->minHeight);
    if (minHeight) {
        ViewAbstractModelStatic::SetMinHeight(frameNode, minHeight.value());
    } else if (version10OrLarger) {
        ViewAbstract::ResetMinSize(frameNode, false);
    }
    auto maxWidth = Converter::OptConvert<CalcDimension>(optValue->maxWidth);
    if (maxWidth) {
        ViewAbstractModelStatic::SetMaxWidth(frameNode, maxWidth.value());
    } else if (version10OrLarger) {
        ViewAbstract::ResetMaxSize(frameNode, true);
    }
    auto maxHeight = Converter::OptConvert<CalcDimension>(optValue->maxHeight);
    if (maxHeight) {
        ViewAbstractModelStatic::SetMaxHeight(frameNode, maxHeight.value());
    } else if (version10OrLarger) {
        ViewAbstract::ResetMaxSize(frameNode, false);
    }
}
void SetHitTestBehaviorImpl(Ark_NativePointer node,
                            const Opt_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<NG::HitTestMode>(value);
    if (!convValue) {
        // Implement Reset value
        ViewAbstract::SetHitTestMode(frameNode, HitTestMode::HTMDEFAULT);
        return;
    }
    ViewAbstract::SetHitTestMode(frameNode, *convValue);
}
void SetOnChildTouchTestImpl(Ark_NativePointer node,
                             const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelStatic::SetOnTouchTestFunc(frameNode, nullptr);
        return;
    }
    auto onTouchTestFunc = [callback = CallbackHelper(*optValue)](
        const std::vector<NG::TouchTestInfo>& touchInfo
    ) -> NG::TouchResult {
        std::vector<NG::TouchTestInfo> touchInfoUpd = touchInfo;
        for (auto &item: touchInfoUpd) {
            item.windowPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.windowPoint.GetX()));
            item.windowPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.windowPoint.GetY()));
            item.currentCmpPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.currentCmpPoint.GetX()));
            item.currentCmpPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.currentCmpPoint.GetY()));
            item.subCmpPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.subCmpPoint.GetX()));
            item.subCmpPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.subCmpPoint.GetY()));
            item.subRect.SetLeft(PipelineBase::Px2VpWithCurrentDensity(item.subRect.GetX()));
            item.subRect.SetTop(PipelineBase::Px2VpWithCurrentDensity(item.subRect.GetY()));
            item.subRect.SetWidth(PipelineBase::Px2VpWithCurrentDensity(item.subRect.Width()));
            item.subRect.SetHeight(PipelineBase::Px2VpWithCurrentDensity(item.subRect.Height()));
        }

        auto arkTouchInfo = Converter::ArkValue<Array_TouchTestInfo>(touchInfoUpd, Converter::FC);
        auto resultOpt =
            callback.InvokeWithOptConvertResult<NG::TouchResult, Ark_TouchResult, Callback_TouchResult_Void>(
                arkTouchInfo
        );
        static const NG::TouchResult defaultRes{ NG::TouchTestStrategy::DEFAULT, "" };
        return resultOpt.value_or(defaultRes);
    };
    ViewAbstractModelStatic::SetOnTouchTestFunc(frameNode, std::move(onTouchTestFunc));
}
void SetLayoutWeightImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto weight = Converter::OptConvertPtr<float>(value);
    ViewAbstractModelStatic::SetLayoutWeight(frameNode, weight.value_or(LAYOUT_HEIGHT_DEFAULT_VALUE));
}
void SetChainWeightImpl(Ark_NativePointer node,
                        const Opt_ChainWeightOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto chainWeight = Converter::OptConvertPtr<ChainWeightPair>(value).value_or(ChainWeightPair{});
    ViewAbstractModelStatic::SetChainWeight(frameNode, chainWeight);
}
void SetPaddingImpl(Ark_NativePointer node,
                    const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetPaddingImpl(node, value);
    } else {
        ViewAbstractModelStatic::SetPadding(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
    }
}
void SetSafeAreaPaddingImpl(Ark_NativePointer node,
                            const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_Padding& value) {
            auto convValue = Converter::Convert<PaddingProperty>(value);
            // ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
        },
        [frameNode](const Ark_LocalizedPadding& value) {
             LOGE("ARKOALA: CommonMethod::SafeAreaPaddingImpl: Ark_LocalizedPadding is not supported.\n");
            auto convValue = Converter::Convert<PaddingProperty>(value);
             // ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
        },
        [frameNode](const Ark_LengthMetrics& value) {
            auto convValue = Converter::Convert<CalcLength>(value);
             // ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
        },
        []() {}
    );
}
void SetMarginImpl(Ark_NativePointer node,
                   const Opt_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetMarginImpl(node, value);
    } else {
        ViewAbstractModelStatic::SetMargin(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
    }
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_ColorMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto colorValue = Converter::OptConvertPtr<Color>(value);
    if (!colorValue) {
        ViewAbstractModelStatic::SetBackgroundColor(frameNode, Color::TRANSPARENT);
    }
    if (frameNode->GetTag() == V2::SELECT_ETS_TAG) {
        SelectModelStatic::SetBackgroundColor(frameNode, colorValue);
    } else if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBackgroundColorImpl(node, value);
    } else {
        ViewAbstractModelStatic::SetBackgroundColor(frameNode, colorValue);
    }
}
void SetPixelRoundImpl(Ark_NativePointer node,
                       const Opt_PixelRoundPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<uint16_t>(value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    ViewAbstractModelStatic::SetPixelRound(frameNode, *convValue);
}
void SetBackgroundImageSizeImpl(Ark_NativePointer node,
                                const Opt_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<BackgroundImageSize>(value);
    if (!convValue) {
        BackgroundImageSize imageSize;
        imageSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
        imageSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        ViewAbstract::SetBackgroundImageSize(frameNode, imageSize);
        return;
    }
    ViewAbstract::SetBackgroundImageSize(frameNode, *convValue);
}
void SetBackgroundImagePositionImpl(Ark_NativePointer node, const Opt_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImagePosition bgImgPosition;
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    bool isReset = false;
    Converter::VisitUnionPtr(value,
        [&valueX,&valueY,&typeX,&typeY](const Ark_Position& src) {
            auto position =
                Converter::Convert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(src);
            CalcDimension x;
            CalcDimension y;
            if (position.first) {
                x = position.first.value();
            }
            if (position.second) {
                y = position.second.value();
            }
            valueX = x.ConvertToPx();
            valueY = y.ConvertToPx();
            if (x.Unit() == DimensionUnit::PERCENT) {
                valueX = x.Value();
                typeX = DimensionUnit::PERCENT;
            }
            if (y.Unit() == DimensionUnit::PERCENT) {
                valueY = y.Value();
                typeY = DimensionUnit::PERCENT;
            }
        },
        [&valueX,&valueY,&typeX,&typeY,&bgImgPosition](const Ark_Alignment& src) {
            auto alignment = Converter::OptConvert<std::pair<double, double>>(src);
            if (alignment) {
                bgImgPosition.SetIsAlign(true);
                typeX = DimensionUnit::PERCENT;
                typeY = DimensionUnit::PERCENT;
                valueX = alignment.value().first;
                valueY = alignment.value().second;
            }
        },
        [&isReset] {
            isReset = true;
        });
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, isReset);
}
void SetBackgroundEffect0Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* value)
{
    SetBackgroundEffect1Impl(node, value, nullptr);
}
void SetBackgroundImageResizableImpl(Ark_NativePointer node,
                                     const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    ImageResizableSlice convValue {};
    convValue = Converter::OptConvert<ImageResizableSlice>(optValue->slice).value_or(convValue);
    // lattice .. This parameter does not take effect for the backgroundImageResizable API.
    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, convValue);
}
void SetForegroundEffectImpl(Ark_NativePointer node,
                             const Opt_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    const float defaultValue = 0.0;
    if (!convValue) {
        ViewAbstractModelStatic::SetForegroundEffect(frameNode, defaultValue);
        return;
    }
    Validator::ValidateNonNegative(convValue);
    ViewAbstractModelStatic::SetForegroundEffect(frameNode, convValue);
}
void SetVisualEffectImpl(Ark_NativePointer node,
                         const Opt_uiEffect_VisualEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto ptrOpt = Converter::OptConvertPtr<OHOS::Rosen::VisualEffect*>(value);
    if (!ptrOpt || !(ptrOpt.value())) {
        ViewAbstractModelStatic::SetVisualEffect(frameNode, nullptr);
        return;
    }
    ViewAbstractModelStatic::SetVisualEffect(frameNode, ptrOpt.value());
}
void SetBackgroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto ptrOpt = Converter::OptConvertPtr<OHOS::Rosen::Filter*>(value);
    if (!ptrOpt || !(ptrOpt.value())) {
        ViewAbstractModelStatic::SetBackgroundFilter(frameNode, nullptr);
        return;
    }
    ViewAbstractModelStatic::SetBackgroundFilter(frameNode, ptrOpt.value());
}
void SetForegroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto ptrOpt = Converter::OptConvertPtr<OHOS::Rosen::Filter*>(value);
    if (!ptrOpt || !(ptrOpt.value())) {
        ViewAbstractModelStatic::SetForegroundFilter(frameNode, nullptr);
        return;
    }
    ViewAbstractModelStatic::SetForegroundFilter(frameNode, ptrOpt.value());
}
void SetCompositingFilterImpl(Ark_NativePointer node,
                              const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto ptrOpt = Converter::OptConvertPtr<OHOS::Rosen::Filter*>(value);
    if (!ptrOpt || !(ptrOpt.value())) {
        ViewAbstractModelStatic::SetCompositingFilter(frameNode, nullptr);
        return;
    }
    ViewAbstractModelStatic::SetCompositingFilter(frameNode, ptrOpt.value());
}
void SetOpacityImpl(Ark_NativePointer node,
                    const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    ViewAbstractModelStatic::SetOpacity(frameNode, result);
}
void SetBorderImpl(Ark_NativePointer node,
                   const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBorderImpl(node, value);
        return;
    }
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
        ViewAbstract::SetBorderWidth(frameNode, BorderWidthProperty {});
        ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
        ViewAbstract::SetBorderRadius(frameNode, BorderRadiusProperty {});
        ViewAbstract::SetDashGap(frameNode, Dimension(-1));
        ViewAbstract::SetDashWidth(frameNode, Dimension(-1));
        return;
    }
    auto style = Converter::OptConvert<BorderStyleProperty>(optValue->style);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    } else {
        ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
    }
    auto width = Converter::OptConvert<BorderWidthProperty>(optValue->width);
    if (width) {
        FixBorderWidthProperty(width.value(), true, true, true);
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    } else {
        //Maybe reset BorderWidth after 1.1 fixed.
    }
    auto color = Converter::OptConvert<BorderColorProperty>(optValue->color);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    } else {
        ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
    }
    auto radius = Converter::OptConvert<BorderRadiusProperty>(optValue->radius);
    if (radius) {
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radius.value());
    } else {
        //BorderRadius should be reset, but 1.1 also not reset when undefined.
    }
    auto dashGap = Converter::OptConvert<BorderWidthProperty>(optValue->dashGap);
    if (dashGap) {
        FixBorderWidthProperty(dashGap.value(), true, false, true);
        ViewAbstractModelStatic::SetDashGap(frameNode, dashGap.value());
    } else {
        //Maybe reset DashGap after 1.1 fixed.
    }
    auto dashWidth = Converter::OptConvert<BorderWidthProperty>(optValue->dashWidth);
    if (dashWidth) {
        FixBorderWidthProperty(dashWidth.value(), true, false, true);
        ViewAbstractModelStatic::SetDashWidth(frameNode, dashWidth.value());
    } else {
        //Maybe reset DashWidth after 1.1 fixed.
    }
}
void SetBorderStyleImpl(Ark_NativePointer node,
                        const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBorderStyleImpl(node, value);
        return;
    }
    auto style = Converter::OptConvertPtr<BorderStyleProperty>(value);
    if (!style) {
        ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
        return;
    }
    ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
}
void SetBorderWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBorderWidthImpl(node, value);
        return;
    }
    auto width = Converter::OptConvertPtr<BorderWidthProperty>(value);
    if (width) {
        FixBorderWidthProperty(width.value(), true, true, true);
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    } else {
        ViewAbstract::SetBorderWidth(frameNode, BorderWidthProperty {});
    }
}
void SetBorderColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBorderColorImpl(node, value);
        return;
    }
    auto color = Converter::OptConvertPtr<BorderColorProperty>(value);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    } else {
        ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
    }
}
void SetBorderRadiusImpl(Ark_NativePointer node,
                         const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG || frameNode->GetTag() == V2::TEXTAREA_ETS_TAG) {
        TextFieldModifier::SetBorderRadiusImpl(node, value);
        return;
    }
    auto radiuses = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    if (radiuses) {
        if (frameNode->GetTag() == V2::BUTTON_ETS_TAG) {
            ButtonModelNG::SetBorderRadius(frameNode, radiuses.value().radiusTopLeft, radiuses.value().radiusTopRight,
                radiuses.value().radiusBottomLeft, radiuses.value().radiusBottomRight);
        }
        if (frameNode->GetTag() == V2::IMAGE_ETS_TAG) {
            ImageModelNG::SetBorderRadius(frameNode, radiuses.value().radiusTopLeft, radiuses.value().radiusTopRight,
                radiuses.value().radiusBottomLeft, radiuses.value().radiusBottomRight);
        }
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
        return;
    }
    ViewAbstract::SetBorderRadius(frameNode, Dimension(0));
}
void SetBorderImageImpl(Ark_NativePointer node,
                        const Opt_BorderImageOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    auto optValue = Converter::GetOptPtr(value);
    uint8_t bitSet = 0;
    Converter::VisitUnion(optValue->source,
        [frameNode, &bitSet](const Ark_LinearGradientOptions& src) {
            Gradient gradient = Converter::Convert<Gradient>(src);
            ViewAbstract::SetBorderImageGradient(frameNode, gradient);
            bitSet |= BorderImage::GRADIENT_BIT;
        },
        [&borderImage, &bitSet](const auto& src) {
            auto info = Converter::OptConvert<ImageSourceInfo>(src);
            if (info) {
                bitSet |= BorderImage::SOURCE_BIT;
                borderImage->SetSrc(info.value().GetSrc());
            }
        },
        [frameNode]() {
            ViewAbstract::SetBorderImageGradient(frameNode, Gradient());
            ViewAbstractModelStatic::SetBorderImageSource(frameNode, "", "", "");
        });
    auto repeat = Converter::OptConvert<BorderImageRepeat>(optValue->repeat);
    if (repeat) {
        bitSet |= BorderImage::REPEAT_BIT;
        borderImage->SetRepeatMode(repeat.value());
    }
    auto fill = Converter::OptConvert<bool>(optValue->fill);
    if (fill) {
        borderImage->SetNeedFillCenter(fill.value());
    }
    Converter::WithOptional(optValue->outset, [&borderImage, &bitSet](const auto& src) {
        switch (src.selector) {
            case CASE_0: {
                auto outset = Converter::OptConvert<Dimension>(src.value0);
                if (outset) {
                    borderImage->SetEdgeOutset(BorderImageDirection::LEFT, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::TOP, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, outset.value());
                    bitSet |= BorderImage::OUTSET_BIT;
                }
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(src.value1.left);
                auto top = Converter::OptConvert<Dimension>(src.value1.top);
                auto right = Converter::OptConvert<Dimension>(src.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(src.value1.bottom);
                if (left) {
                    borderImage->SetEdgeOutset(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeOutset(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, bottom.value());
                }
                bitSet |= BorderImage::OUTSET_BIT;
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    src.selector);
                return;
        }
    });
    if (optValue->slice.tag == INTEROP_TAG_UNDEFINED) {
        Dimension dimension;
        borderImage->SetEdgeSlice(BorderImageDirection::LEFT, dimension);
        borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, dimension);
        borderImage->SetEdgeSlice(BorderImageDirection::TOP, dimension);
        borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, dimension);
        bitSet |= BorderImage::SLICE_BIT;
    }
    Converter::WithOptional(optValue->slice, [&borderImage, &bitSet](const auto& src) {
        switch (src.selector) {
            case CASE_0: {
                auto slice = Converter::OptConvert<Dimension>(src.value0);
                if (slice) {
                    borderImage->SetEdgeSlice(BorderImageDirection::LEFT, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::TOP, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, slice.value());
                }
                bitSet |= BorderImage::SLICE_BIT;
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(src.value1.left);
                auto top = Converter::OptConvert<Dimension>(src.value1.top);
                auto right = Converter::OptConvert<Dimension>(src.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(src.value1.bottom);
                if (left) {
                    borderImage->SetEdgeSlice(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeSlice(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, bottom.value());
                }
                bitSet |= BorderImage::SLICE_BIT;
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    src.selector);
                return;
        }
    });
    Converter::WithOptional(optValue->width, [&borderImage, &bitSet](const auto& src) {
        switch (src.selector) {
            case CASE_0: {
                auto width = Converter::OptConvert<Dimension>(src.value0);
                if (width) {
                    borderImage->SetEdgeWidth(BorderImageDirection::LEFT, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::TOP, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, width.value());
                }
                bitSet |= BorderImage::WIDTH_BIT;
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(src.value1.left);
                auto top = Converter::OptConvert<Dimension>(src.value1.top);
                auto right = Converter::OptConvert<Dimension>(src.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(src.value1.bottom);
                if (left) {
                    borderImage->SetEdgeWidth(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeWidth(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, bottom.value());
                }
                bitSet |= BorderImage::WIDTH_BIT;
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    src.selector);
                return;
        }
    });
    ViewAbstractModelStatic::SetBorderImage(frameNode, borderImage, bitSet);
}
void SetOutlineImpl(Ark_NativePointer node,
                    const Opt_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        BorderWidthProperty width;
        width.SetBorderWidth(Dimension(0.0f, DimensionUnit::VP));
        BorderRadiusProperty radius;
        radius.SetRadius(Dimension(0.0f, DimensionUnit::VP));
        BorderColorProperty color;
        color.SetColor(Color::BLACK);
        BorderStyleProperty style;
        style.SetBorderStyle(BorderStyle::SOLID);
        ViewAbstractModelStatic::SetOuterBorderWidth(frameNode, width);
        ViewAbstractModelStatic::SetOuterBorderRadius(frameNode, radius);
        ViewAbstractModelStatic::SetOuterBorderColor(frameNode, color);
        ViewAbstractModelStatic::SetOuterBorderStyle(frameNode, style);
        return;
    }
    auto borderWidthOpt = Converter::OptConvert<BorderWidthProperty>(optValue->width);
    ViewAbstractModelStatic::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));

    auto borderRadiusOpt = Converter::OptConvert<BorderRadiusProperty>(optValue->radius);
    ViewAbstractModelStatic::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));

    auto borderColorsOpt = Converter::OptConvert<BorderColorProperty>(optValue->color);
    ViewAbstractModelStatic::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));

    auto borderStylesOpt = Converter::OptConvert<BorderStyleProperty>(optValue->style);
    ViewAbstractModelStatic::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void SetOutlineStyleImpl(Ark_NativePointer node,
                         const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderStylesOpt = Converter::OptConvertPtr<BorderStyleProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void SetOutlineWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderWidthOpt = Converter::OptConvertPtr<BorderWidthProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));
}
void SetOutlineColorImpl(Ark_NativePointer node,
                         const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderColorsOpt = Converter::OptConvertPtr<BorderColorProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));
}
void SetOutlineRadiusImpl(Ark_NativePointer node,
                          const Opt_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderRadiusOpt = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));
}
void SetForegroundColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_ResourceColor& resourceColor) {
            auto colorOpt = Converter::OptConvert<Color>(resourceColor);
            ViewAbstractModelStatic::SetForegroundColor(frameNode, colorOpt);
        },
        [frameNode](const Ark_ColoringStrategy& colorStrategy) {
            auto colorStrategyOpt = Converter::OptConvert<ForegroundColorStrategy>(colorStrategy);
            ViewAbstractModelStatic::SetForegroundColorStrategy(frameNode, colorStrategyOpt);
        },
        []() {}
    );
}
void SetOnClick0Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        if (frameNode->GetTag() == V2::TEXT_ETS_TAG) {
            TextModelNG::ClearOnClick(frameNode);
        }  else {
            ViewAbstract::DisableOnClick(frameNode);
        }
        return;
    }
    auto onClick = [callback = CallbackHelper(*optValue)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    if (frameNode->GetTag() == V2::TEXT_ETS_TAG) {
        TextModelNG::SetOnClick(frameNode, std::move(onClick));
    }  else {
        ViewAbstract::SetOnClick(frameNode, std::move(onClick));
    }
}
void SetOnHoverImpl(Ark_NativePointer node,
                    const Opt_Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnHover(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onHover = [arkCallback = CallbackHelper(*optValue), node = weakNode](bool isHover, HoverInfo& hoverInfo) {
        PipelineContext::SetCallBackNode(node);
        Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
        const auto event = Converter::ArkHoverEventSync(hoverInfo);
        arkCallback.InvokeSync(arkIsHover, event.ArkValue());
    };
    ViewAbstract::SetOnHover(frameNode, std::move(onHover));
}
void SetOnHoverMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetOnAccessibilityHoverImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelStatic::DisableOnAccessibilityHover(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAccessibilityHover = [arkCallback = CallbackHelper(*optValue), node = weakNode](
        bool isHover, AccessibilityHoverInfo& hoverInfo) {
        PipelineContext::SetCallBackNode(node);
        Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
        auto event = Converter::ArkAccessibilityHoverEventSync(hoverInfo);
        arkCallback.InvokeSync(arkIsHover, event.ArkValue());
    };
    ViewAbstractModelStatic::SetOnAccessibilityHover(frameNode, std::move(onAccessibilityHover));
}
void SetHoverEffectImpl(Ark_NativePointer node,
                        const Opt_HoverEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto hoverEffect = Converter::OptConvertPtr<OHOS::Ace::HoverEffectType>(value);
    // Implement Reset value
    if (hoverEffect) {
        ViewAbstract::SetHoverEffect(frameNode, hoverEffect.value());
    } else {
        ViewAbstract::SetHoverEffect(frameNode, HoverEffectType::AUTO);
    }
}
void SetOnMouseImpl(Ark_NativePointer node,
                    const Opt_Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnMouse(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onMouse = [arkCallback = CallbackHelper(*optValue), node = weakNode](MouseInfo& mouseInfo) {
        PipelineContext::SetCallBackNode(node);
        const auto event = Converter::ArkMouseEventSync(mouseInfo);
        arkCallback.InvokeSync(event.ArkValue());
    };
    ViewAbstract::SetOnMouse(frameNode, std::move(onMouse));
}
void SetOnTouchImpl(Ark_NativePointer node,
                    const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnTouch(frameNode);
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](TouchEventInfo& info) {
        const auto event = Converter::ArkTouchEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void SetOnKeyEventImpl(Ark_NativePointer node,
                       const Opt_Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnKeyEvent(frameNode);
        return;
    } else {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
            PipelineContext::SetCallBackNode(node);
            const auto event = Converter::ArkKeyEventSync(info);
            arkCallback.InvokeSync(event.ArkValue());
            return false;
        };
        ViewAbstract::SetOnKeyEvent(frameNode, std::move(onKeyEvent));
    }
#ifdef WRONG_GEN
    // this code for Opt_Callback_KeyEvent_Boolean* value
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnKeyEvent(frameNode);
    } else {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
            PipelineContext::SetCallBackNode(node);
            const auto event = Converter::ArkKeyEventSync(info);
            auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
            return Converter::Convert<bool>(arkResult);
        };
        ViewAbstract::SetOnKeyEvent(frameNode, std::move(onKeyEvent));
    }
#endif
}
void SetOnDigitalCrownImpl(Ark_NativePointer node,
                           const Opt_Callback_CrownEvent_Void* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    std::optional<Callback_CrownEvent_Void> optOnDigitalCrown = Converter::GetOpt(*value);
    if (optOnDigitalCrown) {
        auto onDigitalCrown = [callback = CallbackHelper(*optOnDigitalCrown), node = weakNode](CrownEventInfo& info) {
            PipelineContext::SetCallBackNode(node);
            auto stopPropagation = CallbackKeeper::DefineReverseCallback<Callback_Void>([&info]() {
                info.SetStopPropagation(true);
            });
            Ark_CrownEvent crownEvent {
                .timestamp = ArkValue<Ark_Number>(info.GetTimeStamp().time_since_epoch().count()),
                .angularVelocity = ArkValue<Ark_Number>(info.GetAngularVelocity()),
                .degree = ArkValue<Ark_Number>(info.GetDegree()),
                .action = ArkValue<Ark_CrownAction>(info.GetAction()),
                .stopPropagation = stopPropagation,
            };
            callback.Invoke(crownEvent);
        };
        ViewAbstract::SetOnCrownEvent(frameNode, std::move(onDigitalCrown));
    } else {
        ViewAbstract::DisableOnCrownEvent(frameNode);
    }
#endif
}
void SetOnKeyPreImeImpl(Ark_NativePointer node,
                        const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelNG::DisableOnKeyPreIme(frameNode);
        return;
    } else {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyPreImeEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info)
            -> bool {
            PipelineContext::SetCallBackNode(node);
            const auto event = Converter::ArkKeyEventSync(info);
            auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
            return Converter::Convert<bool>(arkResult);
        };
        ViewAbstractModelNG::SetOnKeyPreIme(frameNode, std::move(onKeyPreImeEvent));
    }
}
void SetOnKeyEventDispatchImpl(Ark_NativePointer node,
                               const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnKeyEventDispatch(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
        PipelineContext::SetCallBackNode(node);
        const auto event = Converter::ArkKeyEventSync(info);
        auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
        return Converter::Convert<bool>(arkResult);
    };
    ViewAbstract::SetOnKeyEventDispatch(frameNode, std::move(onKeyEvent));
}
void SetOnFocusAxisEventImpl(Ark_NativePointer node,
                             const Opt_Callback_FocusAxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnFocusAxisEvent(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onFocusAxis = [callback = CallbackHelper(*optValue), node = weakNode](NG::FocusAxisEventInfo& info) {
        PipelineContext::SetCallBackNode(node);
        const auto arkInfo = Converter::ArkFocusAxisEventSync(info);
        callback.InvokeSync(arkInfo.ArkValue());
    };
    ViewAbstract::SetOnFocusAxisEvent(frameNode, std::move(onFocusAxis));
}
void SetOnAxisEventImpl(Ark_NativePointer node,
                        const Opt_Callback_AxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnAxisEvent(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAxis = [callback = CallbackHelper(*optValue), node = weakNode](AxisInfo& info) {
        PipelineContext::SetCallBackNode(node);
        const auto arkInfo = Converter::ArkAxisEventSync(info);
        callback.InvokeSync(arkInfo.ArkValue());
    };
    ViewAbstract::SetOnAxisEvent(frameNode, std::move(onAxis));
}
void SetFocusableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    ViewAbstract::SetFocusable(frameNode, *convValue);
}
void SetNextFocusImpl(Ark_NativePointer node,
                      const Opt_FocusMovement* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto setFocusData = Converter::OptConvertPtr<SetFocusData>(value);
    ViewAbstract::ResetNextFocus(frameNode);
    if (!setFocusData) {
        return;
    }
    if (setFocusData->forward.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::TAB, setFocusData->forward.value());
    }
    if (setFocusData->backward.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::SHIFT_TAB, setFocusData->backward.value());
    }
    if (setFocusData->up.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::UP, setFocusData->up.value());
    }
    if (setFocusData->down.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::DOWN, setFocusData->down.value());
    }
    if (setFocusData->left.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::LEFT, setFocusData->left.value());
    }
    if (setFocusData->right.has_value()) {
        ViewAbstract::SetNextFocus(frameNode, FocusIntension::RIGHT, setFocusData->right.value());
    }
}
void SetTabStopImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ViewAbstract::SetTabStop(frameNode, convValue.value_or(false));
}
void SetOnFocusImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnFocus(frameNode);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void SetOnBlurImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnBlur(frameNode);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnBlur(frameNode, std::move(onEvent));
}
void SetTabIndexImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        int32_t index = 0;
        ViewAbstract::SetTabIndex(frameNode, index);
        return;
    }
    ViewAbstract::SetTabIndex(frameNode, *convValue);
}
void SetDefaultFocusImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetDefaultFocus(frameNode, false);
        return;
    }
    ViewAbstract::SetDefaultFocus(frameNode, *convValue);
}
void SetGroupDefaultFocusImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetGroupDefaultFocus(frameNode, false);
        return;
    }
    ViewAbstract::SetGroupDefaultFocus(frameNode, *convValue);
}
void SetFocusOnTouchImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetFocusOnTouch(frameNode, false);
        return;
    }
    ViewAbstract::SetFocusOnTouch(frameNode, *convValue);
}
void SetFocusBoxImpl(Ark_NativePointer node,
                     const Opt_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<NG::FocusBoxStyle>(value);
    ViewAbstractModelStatic::SetFocusBoxStyle(frameNode, convValue);
}
void SetAnimationImpl(Ark_NativePointer node,
                      const Opt_AnimateParam* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (frameNode->IsFirstBuilding()) {
    //     // the node sets attribute value for the first time. No animation is generated.
    //     return;
    // }

    // auto container = Container::CurrentSafely();
    // CHECK_NULL_VOID(container);
    // auto pipelineContextBase = container->GetPipelineContext();
    // CHECK_NULL_VOID(pipelineContextBase);
    // if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
    //     GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
    //     TAG_LOGW(
    //         AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
    //     return;
    // }

    // auto optOption = Converter::OptConvertPtr<AnimationOption>(value);
    // if (optOption) {
    //     auto option = *optOption;
    //     Validator::ValidateAnimationOption(option, pipelineContextBase->IsFormRender());

    //     if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
    //         option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
    //         option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
    //         TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
    //             static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
    //     }

    //     LOGI("ARKOALA CommonMethod::AnimationImpl: onFinish callback don`t supported yet");
    //     // we need to support onFinish callback and set it to options:

    //     if (SystemProperties::GetRosenBackendEnabled()) {
    //         option.SetAllowRunningAsynchronously(true);
    //     }
    //     ViewContextModelNG::openAnimationInternal(option);
    // } else {
    //     AnimationOption option = AnimationOption();
    //     ViewContextModelNG::closeAnimationInternal(option, true);
    // }
}
void SetTransition0Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    ViewAbstract::SetChainedTransition(frameNode, *convValue);
}
void SetMotionBlurImpl(Ark_NativePointer node,
                       const Opt_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<MotionBlurOption>(value);
    if (convValue) {
        ViewAbstract::SetMotionBlur(frameNode, *convValue);
    }
}
void SetBrightnessImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    if (!convValue.has_value()) {
        convValue = Dimension(BRIGHTNESS_MAX);
    } else {
        if (LessOrEqual(convValue.value().Value(), BRIGHTNESS_MIN)) {
            convValue.value().SetValue(BRIGHTNESS_MIN);
        }
    }
    Validator::ValidateNonNegative(convValue);
    ViewAbstractModelStatic::SetBrightness(frameNode, convValue);
}
void SetContrastImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    if (!convValue.has_value()) {
        convValue = Dimension(CONTRAST_MAX);
    } else {
        if (LessOrEqual(convValue.value().Value(), CONTRAST_MIN)) {
            convValue.value().SetValue(CONTRAST_MIN);
        }
    }
    Validator::ValidateNonNegative(convValue);
    ViewAbstractModelStatic::SetContrast(frameNode, convValue);
}
void SetGrayscaleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    if (!convValue.has_value()) {
        ViewAbstractModelStatic::SetGrayScale(frameNode, 0.0_vp);
        return;
    }
    Validator::ValidateNonNegative(convValue);
    ViewAbstractModelStatic::SetGrayScale(frameNode, convValue);
}
void SetColorBlendImpl(Ark_NativePointer node,
                       const Opt_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    if (!convValue.has_value()) {
        ViewAbstractModelStatic::SetColorBlend(frameNode, Color::TRANSPARENT);
        return;
    }
    ViewAbstractModelStatic::SetColorBlend(frameNode, convValue);
}
void SetSaturateImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    if (!convValue.has_value()) {
        convValue = Dimension(1.0);
    } else {
        if (LessOrEqual(convValue.value().Value(), 0.0f)) {
            convValue.value().SetValue(0);
        }
    }
    ViewAbstract::SetSaturate(frameNode, convValue.value());
}
void SetSepiaImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetSepia(frameNode, convValue.value_or(0._vp));
}
void SetInvertImpl(Ark_NativePointer node,
                   const Opt_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    constexpr float minValue = 0.0f;
    constexpr float maxValue = 1.0f;
    auto convValue = Converter::OptConvertPtr<InvertVariant>(value);
    Validator::ValidateByRange(convValue, minValue, maxValue);
    ViewAbstractModelStatic::SetInvert(frameNode, convValue);
}
void SetHueRotateImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto convValue = std::optional<float>();
    if (optValue.has_value()) {
        Converter::VisitUnion(optValue.value(),
            [&convValue](const Ark_Number& val) {
                convValue = Converter::Convert<float>(val);
            },
            [&convValue](const Ark_String& val) {
                std::string degreeStr = Converter::Convert<std::string>(val);
                convValue = static_cast<float>(StringUtils::StringToDegree(degreeStr));
            },
            []() {});
    }
    Validator::ValidateDegree(convValue);
    ViewAbstract::SetHueRotate(frameNode, convValue.value_or(0.0f));
}
void SetUseShadowBatchingImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstractModelStatic::SetUseShadowBatching(frameNode, false);
        return;
    }
    ViewAbstractModelStatic::SetUseShadowBatching(frameNode, convValue);
}
void SetUseEffect0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ViewAbstractModelStatic::SetUseEffect(frameNode, convValue, std::nullopt);
}
void SetRenderGroupImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetRenderGroup(frameNode, false);
        return;
    }
    ViewAbstract::SetRenderGroup(frameNode, *convValue);
}
void SetFreezeImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ViewAbstractModelStatic::SetFreeze(frameNode, convValue);
}
void SetTranslateImpl(Ark_NativePointer node,
                      const Opt_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TranslateOpt options = Converter::OptConvertPtr<TranslateOpt>(value).value_or(TranslateOpt{});

    CalcDimension x = options.x.value_or(CalcDimension(0.0));
    CalcDimension y = options.y.value_or(CalcDimension(0.0));
    CalcDimension z = options.z.value_or(CalcDimension(0.0));
    ViewAbstractModelStatic::SetTranslate(frameNode, TranslateOptions(x, y, z));
}
void SetScaleImpl(Ark_NativePointer node,
                  const Opt_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScaleOpt scaleOptions = Converter::OptConvertPtr<ScaleOpt>(value).value_or(ScaleOpt{});

    float scaleX = scaleOptions.x.value_or(1.0f);
    float scaleY = scaleOptions.y.value_or(1.0f);
    ViewAbstract::SetScale(frameNode, VectorF(scaleX, scaleY));

    CalcDimension centerX = scaleOptions.centerX.value_or(0.5_pct);
    CalcDimension centerY = scaleOptions.centerY.value_or(0.5_pct);
    ViewAbstractModelStatic::SetPivot(frameNode, DimensionOffset(centerX, centerY));
}
void SetRotateImpl(Ark_NativePointer node,
                   const Opt_Union_RotateOptions_RotateAngleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->value.selector == 0) {
        auto convValue = Converter::OptConvert<RotateOpt>(value->value.value0);
        if (!convValue) {
            std::vector<std::optional<float>> EMPTY_ROTATE_VECTOR(NUM_5, std::nullopt);
            ViewAbstractModelStatic::SetRotate(frameNode, EMPTY_ROTATE_VECTOR);
            return;
        }
        auto xValue = Converter::GetOptPtr(&(value->value.value0.centerX));
        if (xValue.has_value()) {
            Converter::VisitUnion(
                xValue.value(),
                [&convValue](const Ark_String& val) {
                    std::string degreeStr = Converter::Convert<std::string>(val);
                    auto dim = StringUtils::StringToCalcDimension(degreeStr);
                    convValue->center->SetX(dim);
                },
                [](const Ark_Number& val) {}, []() {});
        }
        auto yValue = Converter::GetOptPtr(&(value->value.value0.centerY));
        if (yValue.has_value()) {
            Converter::VisitUnion(
                yValue.value(),
                [&convValue](const Ark_String& val) {
                    std::string degreeStr = Converter::Convert<std::string>(val);
                    auto dim = StringUtils::StringToCalcDimension(degreeStr);
                    convValue->center->SetY(dim);
                },
                [](const Ark_Number& val) {}, []() {});
        }
        auto angleValue = value->value.value0.angle;
        Converter::VisitUnion(
            angleValue,
            [&convValue](const Ark_String& str) {
                std::string degreeStr = Converter::Convert<std::string>(str);
                float angle = static_cast<float>(StringUtils::StringToDegree(degreeStr));
                int32_t indA = 3;
                if (convValue->vec5f.size() > static_cast<size_t>(indA)) {
                    convValue->vec5f[indA] = angle;
                }
            },
            [](const Ark_Number& val) {}, []() {});
        ViewAbstractModelStatic::SetRotate(frameNode, convValue->vec5f);
        ViewAbstractModelStatic::SetPivot(frameNode, convValue->center);
    } else {
        auto convValue = Converter::OptConvert<RotateAngleOpt>(value->value.value1);
        auto xValue = Converter::GetOptPtr(&(value->value.value1.centerX));
        if (xValue.has_value()) {
            Converter::VisitUnion(
                xValue.value(),
                [&convValue](const Ark_String& val) {
                    std::string degreeStr = Converter::Convert<std::string>(val);
                    auto dim = StringUtils::StringToCalcDimension(degreeStr);
                    convValue->center->SetX(dim);
                },
                [](const Ark_Number& val) {}, []() {});
        }
        auto yValue = Converter::GetOptPtr(&(value->value.value1.centerY));
        if (yValue.has_value()) {
            Converter::VisitUnion(
                yValue.value(),
                [&convValue](const Ark_String& val) {
                    std::string degreeStr = Converter::Convert<std::string>(val);
                    auto dim = StringUtils::StringToCalcDimension(degreeStr);
                    convValue->center->SetY(dim);
                },
                [](const Ark_Number& val) {}, []() {});
        }
        ViewAbstractModelStatic::SetRotateAngle(frameNode, convValue->vec4f);
        ViewAbstractModelStatic::SetPivot(frameNode, convValue->center);
    }
}
void SetTransformImpl(Ark_NativePointer node, const Opt_matrix4_Matrix4Transit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto matrixOpt = OptConvertPtr<Matrix4>(value);
    if (!matrixOpt.has_value()) {
        ViewAbstract::SetTransformMatrix(frameNode, Matrix4::CreateIdentity());
        return;
    }
    ViewAbstract::SetTransformMatrix(frameNode, matrixOpt.value());
}
void SetTransform3DImpl(Ark_NativePointer node, const Opt_matrix4_Matrix4Transit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto matrixOpt = OptConvertPtr<Matrix4>(value);
    if (!matrixOpt.has_value()) {
        ViewAbstract::SetTransform3DMatrix(frameNode, Matrix4::CreateIdentity());
        return;
    }
    ViewAbstractModelStatic::SetTransform3DMatrix(frameNode, matrixOpt.value());
}
void SetOnAppearImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnAppear(frameNode);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void SetOnDisAppearImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnDisappear(frameNode);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void SetOnAttachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnAttach(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAttach = [arkCallback = CallbackHelper(*optValue), node = weakNode]() {
        PipelineContext::SetCallBackNode(node);
        arkCallback.InvokeSync();
    };
    ViewAbstract::SetOnAttach(frameNode, std::move(onAttach));
}
void SetOnDetachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnDetach(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onDetach = [arkCallback = CallbackHelper(*optValue), node = weakNode]() {
        PipelineContext::SetCallBackNode(node);
        arkCallback.InvokeSync();
    };
    ViewAbstract::SetOnDetach(frameNode, std::move(onDetach));
}
void SetOnAreaChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Area_Area_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnAreaChange(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](
        const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin) {
        ConvContext ctx;
        PipelineContext::SetCallBackNode(node);

        auto previousOffset = oldRect.GetOffset();
        Ark_Area previous;
        previous.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()), &ctx);
        previous.height = Converter::ArkValue<Ark_Length>(
            PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()), &ctx);
        previous.position.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX()), &ctx);
        previous.position.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY()), &ctx);
        previous.globalPosition.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX() + oldOrigin.GetX()), &ctx);
        previous.globalPosition.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY() + oldOrigin.GetY()), &ctx);

        auto currentOffset = rect.GetOffset();
        Ark_Area current;
        current.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Width()), &ctx);
        current.height = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Height()), &ctx);
        current.position.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX()), &ctx);
        current.position.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY()), &ctx);
        current.globalPosition.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX() + origin.GetX()), &ctx);
        current.globalPosition.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY() + origin.GetY()), &ctx);

        arkCallback.InvokeSync(previous, current);
    };

    auto areaChangeCallback = [areaChangeFunc = std::move(onEvent)](const RectF& oldRect,
                                  const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
            Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
            Offset(origin.GetX(), origin.GetY()));
    };
    ViewAbstract::SetOnAreaChanged(frameNode, std::move(areaChangeCallback));
}
void SetVisibilityImpl(Ark_NativePointer node,
                       const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<VisibleType>(value);
    if (!convValue.has_value()) {
        ViewAbstract::SetVisibility(frameNode, VisibleType::VISIBLE);
        return;
    }
    ViewAbstract::SetVisibility(frameNode, convValue.value());
}
void SetFlexGrowImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue || (convValue.has_value() && convValue.value() < 0.0f)) {
        convValue = 0.0f;
    }
    ViewAbstractModelStatic::SetFlexGrow(frameNode, *convValue);
}
void SetFlexShrinkImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (convValue.has_value() && convValue.value() < 0.0f) {
        convValue.reset();
    }
    if (!convValue) {
        ViewAbstractModelStatic::ResetFlexShrink(frameNode);
        return;
    }
    ViewAbstractModelStatic::SetFlexShrink(frameNode, *convValue);
}
void SetFlexBasisImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    if (!convValue) {
        convValue = Dimension(0, DimensionUnit::AUTO);
    }
    ViewAbstractModelStatic::SetFlexBasis(frameNode, convValue);
}
void SetAlignSelfImpl(Ark_NativePointer node,
                      const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto align = Converter::OptConvertPtr<OHOS::Ace::FlexAlign>(value);
    if (align) {
        ViewAbstractModelStatic::SetAlignSelf(frameNode, align.value());
    } else {
        ViewAbstractModelStatic::SetAlignSelf(frameNode, OHOS::Ace::FlexAlign::AUTO);
    }
}
void SetDisplayPriorityImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<int>(value);
    if (!result) {
        ViewAbstractModelStatic::SetDisplayIndex(frameNode, result.value_or(1));
        return;
    }
    ViewAbstractModelStatic::SetDisplayIndex(frameNode, result.value());
}
void SetZIndexImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<int>(value);
    if (result) {
        ViewAbstract::SetZIndex(frameNode, result.value());
    } else {
        ViewAbstract::SetZIndex(frameNode, 0);
    }
}
void SetDirectionImpl(Ark_NativePointer node,
                      const Opt_Direction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = Converter::OptConvertPtr<TextDirection>(value);
    if (!direction) {
        ViewAbstractModelStatic::SetLayoutDirection(frameNode, TextDirection::AUTO);
        return;
    }
    ViewAbstractModelStatic::SetLayoutDirection(frameNode, direction.value());
}
void SetAlignImpl(Ark_NativePointer node,
                  const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto alignment = Converter::OptConvertPtr<Alignment>(value);
    if (alignment) {
        // Implement Reset value
        ViewAbstractModelStatic::SetAlign(frameNode, alignment.value());
    }
}
void SetPositionImpl(Ark_NativePointer node,
                     const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelStatic::SetPosition(frameNode, OffsetT<Dimension>(Dimension(0), Dimension(0)));
        return;
    }
    switch (optValue->selector) {
        case CASE_0: {
            auto x = Converter::ConvertOrDefault(optValue->value0.x, Dimension());
            auto y = Converter::ConvertOrDefault(optValue->value0.y, Dimension());
            ViewAbstractModelStatic::SetPosition(frameNode, { x, y });
            break;
        }
        case CASE_1: {
            auto result = Converter::ConvertOrDefault(optValue->value1, EdgesParam());
            ViewAbstractModelStatic::SetPositionEdges(frameNode, result);
            break;
        }
        case CASE_2: {
            auto result = Converter::ConvertOrDefault(optValue->value2, EdgesParam());
            ViewAbstractModelStatic::SetPositionLocalizedEdges(frameNode, true);
            ViewAbstractModelStatic::SetPositionEdges(frameNode, result);
            break;
        }
        default:
            LOGE("ARKOALA:PositionImpl: Unexpected value->selector: %{public}d\n", optValue->selector);
            return;
    }
}
void SetMarkAnchorImpl(Ark_NativePointer node,
                       const Opt_Union_Position_LocalizedPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto anchorOpt = Converter::OptConvertPtr<PositionWithLocalization>(value);
    if (anchorOpt) {
        if (anchorOpt->second && anchorOpt->first.has_value()) {
            ViewAbstractModelStatic::SetMarkAnchorStart(frameNode, anchorOpt->first->GetX());
            ViewAbstractModelStatic::MarkAnchor(frameNode, anchorOpt->first);
            return;
        }
        ViewAbstractModelStatic::MarkAnchor(frameNode, anchorOpt->first);
    } else {
        ViewAbstractModelStatic::MarkAnchor(frameNode, std::nullopt);
    }
    ViewAbstractModelStatic::ResetMarkAnchorStart(frameNode);
}
void SetOffsetImpl(Ark_NativePointer node,
                   const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto varOpt = Converter::OptConvertPtr<OffsetOrEdgesParam>(value);
    CHECK_NULL_VOID(varOpt);
    if (auto offset = std::get_if<std::optional<OffsetT<Dimension>>>(&varOpt.value()); offset) {
        ViewAbstractModelStatic::SetOffset(frameNode, offset->value());
    } else if (auto edges = std::get_if<std::optional<EdgesParamOptions>>(&varOpt.value()); edges) {
        ViewAbstractModelStatic::SetOffsetEdges(frameNode, edges->value().value);
        ViewAbstractModelStatic::SetOffsetLocalizedEdges(frameNode, edges->value().isLocalized);
    } else {
        LOGE("ARKOALA CommonMethod::OffsetImpl: incorrect value");
    }
}
void SetEnabledImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetEnabled(frameNode, true);
        return;
    }
    ViewAbstract::SetEnabled(frameNode, *convValue);
}
void SetAlignRulesWithAlignRuleOptionTypedValueImpl(Ark_NativePointer node,
                                                    const Opt_AlignRuleOption* value)
{
    LOGE("Ark_AlignRuleOption is stubbed");
#ifdef WRONG_GEN
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convMapValue = Converter::OptConvertPtr<std::map<AlignDirection, AlignRule>>(value);
    ViewAbstractModelStatic::SetAlignRules(frameNode, convMapValue);
    auto optValue = Converter::GetOptPtr(value);
    auto convBiasValue = optValue ? Converter::OptConvert<BiasOpt>(optValue->bias) : std::nullopt;
    if (convBiasValue.has_value()) {
        ViewAbstractModelStatic::SetBias(frameNode, convBiasValue.value().first, convBiasValue.value().second);
    } else {
        ViewAbstractModelStatic::SetBias(frameNode, std::nullopt);
    }
#endif
}
void SetAlignRulesWithLocalizedAlignRuleOptionsTypedValueImpl(Ark_NativePointer node,
                                                              const Opt_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convMapValue = Converter::OptConvertPtr<std::map<AlignDirection, AlignRule>>(value);
    ViewAbstractModelStatic::SetAlignRules(frameNode, convMapValue);
    auto optValue = Converter::GetOptPtr(value);
    auto convBiasValue = optValue ? Converter::OptConvert<BiasOpt>(optValue->bias) : std::nullopt;
    if (convBiasValue.has_value()) {
        ViewAbstractModelStatic::SetBias(frameNode, convBiasValue.value().first, convBiasValue.value().second);
    } else {
        ViewAbstractModelStatic::SetBias(frameNode, std::nullopt);
    }
}
void SetAspectRatioImpl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<float>(value);
    if (result) {
        auto ratio = result.value();
        if (ratio <= 0.0) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                ViewAbstractModelStatic::ResetAspectRatio(frameNode);
                return;
            } else {
                ratio = 1.0;
            }
        }
        ViewAbstractModelStatic::SetAspectRatio(frameNode, ratio);
    }
}
void SetClickEffectImpl(Ark_NativePointer node,
                        const Opt_ClickEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ark_ClickEffect>(value);
    if (!convValue.has_value()) {
        ViewAbstractModelStatic::SetClickEffectLevel(frameNode, std::nullopt, std::nullopt);
        return;
    }
    const std::optional<ClickEffectLevel>& level = Converter::OptConvert<ClickEffectLevel>(convValue.value().level);
    auto scaleValue = Converter::OptConvert<float>(convValue.value().scale);
    if (!scaleValue) {
        scaleValue = (level == ClickEffectLevel::MIDDLE || level == ClickEffectLevel::HEAVY)
                         ? DEFAULT_SCALE_MIDDLE_OR_HEAVY
                         : DEFAULT_SCALE_LIGHT;
    }
    ViewAbstractModelStatic::SetClickEffectLevel(frameNode, level, scaleValue);
}
void SetOnDragStartImpl(Ark_NativePointer node,
                        const Opt_Type_CommonMethod_onDragStart* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::SetOnDragStart(frameNode, nullptr);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onDragStart = [callback = CallbackHelper(*optValue), weakNode]
        (const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) -> DragDropInfo {
        DragDropInfo result;
        CHECK_NULL_RETURN(info, result);
        auto arkDragInfo = Converter::ArkValue<Ark_DragEvent>(info);
        auto arkExtraParam = Converter::ArkValue<Opt_String>(extraParams);

        auto parseCustBuilder = [&result, weakNode](const CustomNodeBuilder& val) {
            if (auto fnode = weakNode.Upgrade(); fnode) {
                result.customNode = CallbackHelper(val).BuildSync(Referenced::RawPtr(fnode));
            }
        };
        auto parseDragI = [&result, weakNode](const Ark_DragItemInfo& value) {
            result.pixelMap = Converter::OptConvert<RefPtr<PixelMap>>(value.pixelMap).value_or(nullptr);
            result.extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string());
            auto fnode = weakNode.Upgrade();
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            if (builder && fnode) {
                result.customNode = CallbackHelper(builder.value()).BuildSync(Referenced::RawPtr(fnode));
            }
        };
        auto handler = [custB = std::move(parseCustBuilder), dragI = std::move(parseDragI)](const void *rawResultPtr) {
            auto arkResultPtr = reinterpret_cast<const Ark_Union_CustomBuilder_DragItemInfo*>(rawResultPtr);
            CHECK_NULL_VOID(arkResultPtr);
            Converter::VisitUnionPtr(arkResultPtr, custB, dragI, []() {});
        };

        PipelineContext::SetCallBackNode(weakNode);

        CallbackKeeper::InvokeWithResultHandler<Ark_Union_CustomBuilder_DragItemInfo,
            Callback_Union_CustomBuilder_DragItemInfo_Void>(handler, callback, arkDragInfo, arkExtraParam);
        return result;
    };
    ViewAbstract::SetOnDragStart(frameNode, std::move(onDragStart));
}
void SetOnDragEnterImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnDragEnter(frameNode);
        return;
    }
    auto onDragEnter = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                           const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDragEnter(frameNode, std::move(onDragEnter));
}
void SetOnDragMoveImpl(Ark_NativePointer node,
                       const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnDragMove(frameNode);
        return;
    }
    auto onDragMove = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                          const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDragMove(frameNode, std::move(onDragMove));
}
void SetOnDragLeaveImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnDragLeave(frameNode);
        return;
    }
    auto onDragLeave = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                           const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDragLeave(frameNode, std::move(onDragLeave));
}
void SetOnDrop0Impl(Ark_NativePointer node,
                    const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnDrop(frameNode);
        return;
    }
    auto onDrop = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                      const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDrop(frameNode, std::move(onDrop));
}
void SetOnDragEndImpl(Ark_NativePointer node,
                      const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::DisableOnDragEnd(frameNode);
        return;
    }
    auto onDragEnd = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        std::string extraParams = "";
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDragEnd(frameNode, std::move(onDragEnd));
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetDraggable(frameNode, false);
        return;
    }
    ViewAbstract::SetDraggable(frameNode, *convValue);
}
void SetDragPreview0Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_String& val) {
            ViewAbstract::SetDragPreview(frameNode,
                DragDropInfo { .inspectorId = Converter::Convert<std::string>(val) });
        },
        [node, frameNode](const CustomNodeBuilder& val) {
            CallbackHelper(val).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                ViewAbstract::SetDragPreview(frameNode, DragDropInfo { .customNode = uiNode });
                }, node);
        },
        [node, frameNode](const Ark_DragItemInfo& value) {
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            if (builder) {
                CallbackHelper(builder.value()).BuildAsync([frameNode](
                    const RefPtr<UINode>& uiNode) {
                    DragDropInfo info;
                    info.customNode = uiNode;
                    ViewAbstract::SetDragPreview(frameNode, info);
                    }, node);
            } else {
                ViewAbstract::SetDragPreview(frameNode, DragDropInfo {});
            }
        },
        [frameNode]() {
            ViewAbstract::SetDragPreview(frameNode, DragDropInfo {});
        });
}
void SetOnPreDragImpl(Ark_NativePointer node,
                      const Opt_Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnPreDrag(frameNode);
        return;
    }
    auto onPreDrag = [callback = CallbackHelper(*optValue)](const PreDragStatus info) {
        callback.Invoke(Converter::ArkValue<Ark_PreDragStatus>(info));
    };
    ViewAbstract::SetOnPreDrag(frameNode, onPreDrag);
}
void SetLinearGradientImpl(Ark_NativePointer node,
                           const Opt_LinearGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        Gradient defaultGradient;
        ViewAbstract::SetLinearGradient(frameNode, defaultGradient);
        return;
    }
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    auto repeat = Converter::OptConvert<bool>(optValue->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto linear = gradient.GetLinearGradient();
    linear->angle = Converter::OptConvert<Dimension>(optValue->angle);
    auto direction = Converter::OptConvert<GradientDirection>(optValue->direction);
    if (direction) {
        Converter::AssignLinearGradientDirection(linear, direction.value());
    }
    Converter::AssignGradientColors(&gradient, &optValue->colors);
    ViewAbstract::SetLinearGradient(frameNode, gradient);
}
void SetSweepGradientImpl(Ark_NativePointer node,
                          const Opt_SweepGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        Gradient defaultGradient;
        ViewAbstract::SetSweepGradient(frameNode, defaultGradient);
        return;
    }
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::SWEEP);
    auto repeat = Converter::OptConvert<bool>(optValue->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto sweep = gradient.GetSweepGradient();
    auto centerX = Converter::OptConvert<Dimension>(optValue->center.value0);
    auto centerY = Converter::OptConvert<Dimension>(optValue->center.value1);
    auto startAngle = Converter::OptConvert<Dimension>(optValue->start);
    auto endAngle = Converter::OptConvert<Dimension>(optValue->end);
    auto rotation = Converter::OptConvert<Dimension>(optValue->rotation);
    sweep->startAngle = ClampAngleDimension(Converter::OptConvert<Dimension>(optValue->start), MIN_ANGEL, MAX_ANGEL);
    sweep->endAngle = ClampAngleDimension(Converter::OptConvert<Dimension>(optValue->end), MIN_ANGEL, MAX_ANGEL);
    sweep->rotation = ClampAngleDimension(Converter::OptConvert<Dimension>(optValue->rotation), MIN_ANGEL, MAX_ANGEL);
    if (centerX) sweep->centerX = centerX.value();
    if (centerY) sweep->centerY = centerY.value();
    Converter::AssignGradientColors(&gradient, &optValue->colors);
    ViewAbstract::SetSweepGradient(frameNode, gradient);
}
void SetRadialGradientImpl(Ark_NativePointer node,
                           const Opt_RadialGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Gradient>(value);
    if (!convValue) {
        Gradient defaultGradient;
        ViewAbstract::SetRadialGradient(frameNode, defaultGradient);
        return;
    }
    ViewAbstract::SetRadialGradient(frameNode, *convValue);
}
void SetMotionPathImpl(Ark_NativePointer node,
                       const Opt_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<MotionPathOption>(value);
    if (convValue) {
        ViewAbstract::SetMotionPath(frameNode, *convValue);
    } else {
        ViewAbstract::SetMotionPath(frameNode, MotionPathOption());
    }
}
void SetShadowImpl(Ark_NativePointer node,
                   const Opt_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadow = Converter::OptConvertPtr<Shadow>(value);
    if (!shadow) {
        Shadow defaultShadow;
        ViewAbstract::SetBackShadow(frameNode, defaultShadow);
        return;
    }
    ViewAbstract::SetBackShadow(frameNode, shadow.value());
}
void SetClipImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetClipEdge(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void SetClipShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RefPtr<BasicShape>>(value);
    if (!convValue) {
        ViewAbstract::SetClipShape(frameNode, nullptr);
        return;
    }
    ViewAbstract::SetClipShape(frameNode, convValue.value());
}
void SetMaskImpl(Ark_NativePointer node,
                 const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto mask = Converter::OptConvertPtr<Ark_ProgressMask>(value);
    if (!mask) {
        ViewAbstract::SetProgressMask(frameNode, nullptr);
        return;
    }
    const auto& progressMask = mask.value()->GetProperty();
    ViewAbstract::SetProgressMask(frameNode, progressMask);
}
void SetMaskShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RefPtr<BasicShape>>(value);
    if (!convValue) {
        ViewAbstract::SetProgressMask(frameNode, nullptr);
        return;
    }
    ViewAbstract::SetMask(frameNode, convValue.value());
}
void SetKeyImpl(Ark_NativePointer node,
                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        std::string defaultStr = "";
        ViewAbstract::SetInspectorId(frameNode, defaultStr);
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, *convValue);
}
void SetIdImpl(Ark_NativePointer node,
               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto id = Converter::OptConvertPtr<std::string>(value);
    ViewAbstract::SetInspectorId(frameNode, *id);
}
void SetGeometryTransition0Impl(Ark_NativePointer node,
                                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto idOpt = Converter::OptConvertPtr<std::string>(value);
    if (!idOpt) {
        return; // undefined return, same with ArktsDyn
    }
    // follow flag
    bool followWithoutTransition { false };
    // hierarchy flag
    bool doRegisterSharedTransition { true };
    ViewAbstractModelStatic::SetGeometryTransition(
        frameNode, idOpt.value(), followWithoutTransition, doRegisterSharedTransition);
}
void SetRestoreIdImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        int32_t index = -1;
        ViewAbstract::SetRestoreId(frameNode, index);
        return;
    }
    ViewAbstract::SetRestoreId(frameNode, *convValue);
}
void SetSphericalEffectImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    const float minValue = 0.0;
    const float maxValue = 1.0;
    if (!convValue.has_value()) {
        convValue = minValue;
    } else {
        if (LessOrEqual(convValue.value(), minValue)) {
            convValue = minValue;
        }
    }
    Validator::ValidateByRange(convValue, minValue, maxValue);
    ViewAbstractModelStatic::SetSphericalEffect(frameNode, convValue);
}
void SetLightUpEffectImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue.has_value()) {
        convValue = LIGHTUPEFFECT_MAX;
    } else {
        if (LessOrEqual(convValue.value(), LIGHTUPEFFECT_MIN)) {
            convValue = LIGHTUPEFFECT_MIN;
        }
    }
    Validator::ValidateByRange(convValue, LIGHTUPEFFECT_MIN, LIGHTUPEFFECT_MAX);
    ViewAbstractModelStatic::SetLightUpEffect(frameNode, convValue);
}
void SetPixelStretchEffectImpl(Ark_NativePointer node,
                               const Opt_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<PixStretchEffectOption>(value);
    if (!convValue.has_value()) {
        PixStretchEffectOption option;
        option.ResetValue();
        ViewAbstractModelStatic::SetPixelStretchEffect(frameNode, option);
        return;
    }
    ViewAbstractModelStatic::SetPixelStretchEffect(frameNode, convValue);
}
void SetAccessibilityGroupWithValueImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    bool isGroupFlag = false;
    if (convValue) {
        isGroupFlag = *convValue;
    }
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, isGroupFlag);
}
void SetAccessibilityTextOfStringTypeImpl(Ark_NativePointer node,
                                          const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityText(frameNode, *convValue);
}
void SetAccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode, *convValue);
}
void SetAccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    bool isFocus = false;
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (convValue) {
        isFocus = *convValue;
    }
    ViewAbstractModelStatic::SetAccessibilityDefaultFocus(frameNode, isFocus);
}
void SetAccessibilityUseSamePageImpl(Ark_NativePointer node,
                                     const Opt_AccessibilitySamePageMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ark_AccessibilitySamePageMode>(value);
    if (!convValue) {
        ViewAbstractModelStatic::SetAccessibilityUseSamePage(frameNode, "");
        return;
    }
    auto pageMode = AccessibilityStaticUtils::GetPageModeType(convValue.value());
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(frameNode, pageMode);
}
void SetAccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    bool scrollTriggerable = false;
    bool resetValue = false;
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        resetValue = true;
    } else  {
        scrollTriggerable = *convValue;
    }
    ViewAbstractModelNG::SetAccessibilityScrollTriggerable(frameNode, scrollTriggerable, resetValue);
}
void SetAccessibilityTextOfResourceTypeImpl(Ark_NativePointer node,
                                            const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<std::string>(value);
    if (!optValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityText(frameNode, optValue.value());
}
void SetAccessibilityRoleImpl(Ark_NativePointer node,
                              const Opt_AccessibilityRoleType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    bool resetValue = false;
    std::string role;
    auto convValue = Converter::OptConvertPtr<Ark_AccessibilityRoleType>(value);
    if (!convValue) {
        ViewAbstractModelNG::SetAccessibilityRole(frameNode, role, true);
        return;
    }
    auto roleType = static_cast<AccessibilityRoleType>(convValue.value());
    role = AccessibilityStaticUtils::GetRoleByType(roleType);
    if (role.empty()) {
        resetValue = true;
    }
    ViewAbstractModelNG::SetAccessibilityRole(frameNode, role, resetValue);
}
void SetOnAccessibilityFocusImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityFocusCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelNG::ResetOnAccessibilityFocus(frameNode);
        return;
    }
    auto onFocus = [callback = CallbackHelper(*optValue)](bool isFocus) -> void {
        callback.Invoke(ArkValue<Ark_Boolean>(isFocus));
    };
    ViewAbstractModelNG::SetOnAccessibilityFocus(frameNode, std::move(onFocus));
}
void SetOnAccessibilityActionInterceptImpl(Ark_NativePointer node,
                                           const Opt_AccessibilityActionInterceptCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstractModelNG::SetOnAccessibilityActionIntercept(frameNode, nullptr);
        return;
    }
    auto accessibilityActionInterceptCallback = [callback = CallbackHelper(*optValue)](AccessibilityInterfaceAction action) -> AccessibilityActionInterceptResult {
        auto arkAccessibilityAction = Converter::ArkValue<Ark_AccessibilityAction>(action);
        auto resultOpt = callback.InvokeWithOptConvertResult<AccessibilityActionInterceptResult, Ark_AccessibilityActionInterceptResult, Callback_AccessibilityActionInterceptResult_Void>(arkAccessibilityAction);
        return resultOpt.value_or(AccessibilityActionInterceptResult::ACTION_CONTINUE);
    };
    ViewAbstractModelNG::SetOnAccessibilityActionIntercept(frameNode, std::move(accessibilityActionInterceptCallback));
}
void SetAccessibilityTextHintImpl(Ark_NativePointer node,
                                  const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelStatic::SetAccessibilityTextHint(frameNode, *convValue);
}
void SetAccessibilityDescriptionOfStringTypeImpl(Ark_NativePointer node,
                                                 const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, *convValue);
}
void SetAccessibilityDescriptionOfResourceTypeImpl(Ark_NativePointer node,
                                                   const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<std::string>(value);
    CHECK_EQUAL_VOID(optValue.has_value(), false);
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, optValue.value());
}
void SetAccessibilityLevelImpl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, *convValue);
}
void SetAccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                     const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // keep the same processing
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
        auto builder = [uiNode]() -> RefPtr<UINode> {
            return uiNode;
        };
        ViewAbstractModelStatic::SetAccessibilityVirtualNode(frameNode, std::move(builder));
    }, node);
}
void SetAccessibilityCheckedImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    bool checked = false;
    bool resetValue = false;
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        resetValue = true;
    } else {
        checked = *convValue;
    }
    ViewAbstractModelNG::SetAccessibilityChecked(frameNode, checked, resetValue);
}
void SetAccessibilitySelectedImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    bool selected = false;
    bool resetValue = false;
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        resetValue = true;
    } else {
        selected = *convValue;
    }
    ViewAbstractModelNG::SetAccessibilitySelected(frameNode, selected, resetValue);
}
void SetObscuredImpl(Ark_NativePointer node,
                     const Opt_Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::vector<std::optional<ObscuredReasons>>>(value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    auto vec = std::vector<ObscuredReasons>();
    for (auto reason : *convValue) {
        if (reason.has_value()) {
            vec.emplace_back(reason.value());
        }
    }
    ViewAbstract::SetObscured(frameNode, vec);
}
void SetReuseIdImpl(Ark_NativePointer node,
                    const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA CommonMethod::ReuseIdImpl: Method not implemented in ViewAbstract!");
}
void SetReuseImpl(Ark_NativePointer node,
                  const Opt_ReuseOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetRenderFitImpl(Ark_NativePointer node,
                      const Opt_RenderFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RenderFit>(value);
    if (!convValue) {
        ViewAbstractModelStatic::SetRenderFit(frameNode, RenderFit::TOP_LEFT);
        return;
    }
    ViewAbstractModelStatic::SetRenderFit(frameNode, convValue);
}
void SetBackgroundBrightnessImpl(Ark_NativePointer node,
                                 const Opt_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    const double rateValue = 0.0;
    const double lightUpDegreeValue = 0.0;
    if (!optValue) {
        ViewAbstract::SetDynamicLightUp(frameNode, rateValue, lightUpDegreeValue);
        return;
    }
    auto rate = Converter::Convert<float>(optValue->rate);
    auto lightUpDegree = Converter::Convert<float>(optValue->lightUpDegree);
    ViewAbstract::SetDynamicLightUp(frameNode, rate, lightUpDegree);
}
void SetOnGestureJudgeBeginImpl(Ark_NativePointer node,
                                const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::SetOnGestureJudgeBegin(frameNode, nullptr);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onGestureJudgefunc = [callback = CallbackHelper(*optValue), node = weakNode](
            const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& baseGestureInfo
        ) -> GestureJudgeResult {
        GestureJudgeResult defVal = GestureJudgeResult::CONTINUE;
        CHECK_NULL_RETURN(gestureInfo && baseGestureInfo, defVal);
        PipelineContext::SetCallBackNode(node);
        auto arkGestInfo = Converter::ArkValue<Ark_GestureInfo>(*gestureInfo);
        auto arkGestEvent = CreateArkBaseGestureEvent(baseGestureInfo, gestureInfo->GetRecognizerType());
        CHECK_NULL_RETURN(arkGestEvent, defVal);
        auto resultOpt = callback.InvokeWithOptConvertResult
            <GestureJudgeResult, Ark_GestureJudgeResult, Callback_GestureJudgeResult_Void>(arkGestInfo, arkGestEvent);
        return resultOpt.value_or(defVal);
    };
    ViewAbstract::SetOnGestureJudgeBegin(frameNode, std::move(onGestureJudgefunc));
}
void SetOnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
    const Opt_GestureRecognizerJudgeBeginCallback* callback,
    const Opt_Boolean *exposeInnerGesture);
void SetOnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                           const Opt_GestureRecognizerJudgeBeginCallback* value)
{
    auto exposeInnerGesture = Converter::ArkValue<Opt_Boolean>(false);
    SetOnGestureRecognizerJudgeBegin1Impl(node, value, &exposeInnerGesture);
}
void SetShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                                const Opt_ShouldBuiltInRecognizerParallelWithCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, nullptr);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto shouldBuiltInRecognizerParallelWithFunc = [callback = CallbackHelper(*optValue), node = weakNode](
        const RefPtr<NG::NGGestureRecognizer>& current, const std::vector<RefPtr<NG::NGGestureRecognizer>>& others
    ) -> RefPtr<NG::NGGestureRecognizer> {
        PipelineContext::SetCallBackNode(node);

        auto arkValCurrent = CreateArkGestureRecognizer(current);
        auto arkValOthers = CreateArkGestureRecognizerArray(others);
        auto resultOpt = callback.InvokeWithOptConvertResult<RefPtr<NG::NGGestureRecognizer>, Ark_GestureRecognizer,
            Callback_GestureRecognizer_Void>(arkValCurrent, arkValOthers);
        return resultOpt.value_or(nullptr);
    };
    ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, std::move(shouldBuiltInRecognizerParallelWithFunc));
}
void SetMonopolizeEventsImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ViewAbstract::SetMonopolizeEvents(frameNode, false);
        return;
    }
    ViewAbstract::SetMonopolizeEvents(frameNode, *convValue);
}
void SetOnTouchInterceptImpl(Ark_NativePointer node,
                             const Opt_Callback_TouchEvent_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::SetOnTouchIntercept(frameNode, nullptr);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onTouchIntercept = [arkCallback = CallbackHelper(*optValue), node = weakNode](
        TouchEventInfo& info) -> HitTestMode {
        const auto event = Converter::ArkTouchEventSync(info);
        auto resultOpt = arkCallback.InvokeWithOptConvertResult<
            HitTestMode, Ark_HitTestMode, Callback_HitTestMode_Void>(event.ArkValue());
        return resultOpt.value_or(HitTestMode::HTMDEFAULT);
    };
    ViewAbstract::SetOnTouchIntercept(frameNode, std::move(onTouchIntercept));
}
void SetOnSizeChangeImpl(Ark_NativePointer node,
                         const Opt_SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        ViewAbstract::SetOnSizeChanged(frameNode, nullptr);
        return;
    }
    auto onSizeChange = [callback = CallbackHelper(*optValue)](const RectF& oldRect, const RectF& newRect) {
        Ark_SizeOptions oldSize;
        oldSize.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
        oldSize.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
        Ark_SizeOptions newSize;
        newSize.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(newRect.Width()));
        newSize.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(newRect.Height()));
        callback.InvokeSync(oldSize, newSize);
    };
    ViewAbstract::SetOnSizeChanged(frameNode, std::move(onSizeChange));
}
void SetAccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                        const Opt_FocusDrawLevel* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    int32_t drawLevel = 0;
    auto convValue = Converter::OptConvertPtr<Ark_FocusDrawLevel>(value);
    if (convValue.has_value()) {
        drawLevel = AccessibilityStaticUtils::GetFocusDrawLevel(static_cast<int32_t>(convValue.value()));
        if (drawLevel == -1) {
            drawLevel = 0;
        }
    }
    ViewAbstractModelNG::SetAccessibilityFocusDrawLevel(frameNode, drawLevel);
}
void SetCustomPropertyImpl(Ark_NativePointer node,
                           const Ark_String* name,
                           const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("CommonMethodModifier::CustomPropertyImpl is not implemented");
}
void SetExpandSafeAreaImpl(Ark_NativePointer node,
                           const Opt_Array_SafeAreaType* types,
                           const Opt_Array_SafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convTypes = Converter::OptConvertPtr<std::vector<std::optional<uint32_t>>>(types);
    auto convEdges = Converter::OptConvertPtr<std::vector<std::optional<uint32_t>>>(edges);
    SafeAreaExpandOpts opts;
    uint32_t safeAreaType = SAFE_AREA_TYPE_NONE;
    if (convTypes.has_value()) {
        std::vector<std::optional<uint32_t>> vec = convTypes.value();
        for (size_t i = 0; i < vec.size(); ++i) {
            safeAreaType |= vec[i].value_or(0);
        }
        opts.type = safeAreaType;
    }
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    if (convEdges.has_value()) {
        std::vector<std::optional<uint32_t>> vec = convEdges.value();
        for (size_t i = 0; i < vec.size(); ++i) {
            safeAreaEdge |= vec[i].value_or(0);
        }
        opts.edges = safeAreaEdge;
    }
    ViewAbstractModelStatic::UpdateSafeAreaExpandOpts(frameNode, opts);
}
void SetBackgroundImpl(Ark_NativePointer node,
                       const Opt_CustomNodeBuilder* builder,
                       const Opt_BackgroundOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optAlign = Converter::OptConvertPtr<Alignment>(options);
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        // Implement Reset value
        return;
    }
    CallbackHelper(*optBuilder).BuildAsync([frameNode, optAlign](const RefPtr<UINode>& uiNode) {
            CHECK_NULL_VOID(uiNode);
            auto builder = [uiNode]() -> RefPtr<UINode> {
                return uiNode;
            };
            ViewAbstractModelStatic::BindBackground(frameNode, builder, optAlign);
        }, node);
}
void SetBackgroundImage0Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvertPtr<ImageSourceInfo>(src);
    ViewAbstractModelStatic::SetBackgroundImage(frameNode, sourceInfo);
}
void SetBackgroundImage1Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_BackgroundImageOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvertPtr<ImageSourceInfo>(src);
    ViewAbstractModelStatic::SetBackgroundImage(frameNode, sourceInfo);
    CHECK_NULL_VOID(options);

    auto syncLoad = static_cast<bool>(options->value.syncLoad.value);
    ViewAbstractModelStatic::SetBackgroundImageSyncMode(frameNode, syncLoad);

    auto imageRepeat = Converter::OptConvertPtr<ImageRepeat>(&options->value.repeat);
    if (imageRepeat.has_value()) {
        ViewAbstractModelStatic::SetBackgroundImageRepeat(frameNode, imageRepeat.value());
    }
}
void SetBackgroundImage2Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvertPtr<ImageSourceInfo>(src);
    ViewAbstractModelStatic::SetBackgroundImage(frameNode, sourceInfo);

    auto imageRepeat = Converter::OptConvertPtr<ImageRepeat>(repeat);
    ViewAbstractModelStatic::SetBackgroundImageRepeat(frameNode, imageRepeat);
}
void SetBackgroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_BackgroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (auto opt = Converter::OptConvertPtr<BlurStyleOption>(options); opt) {
        convValue = *opt;
    }
    if (auto optStyle = Converter::OptConvertPtr<BlurStyle>(style); optStyle) {
        convValue.blurStyle = *optStyle;
    }
    auto sysOptionsOpt = Converter::OptConvertPtr<SysOptions>(sysOptions);
    if (sysOptionsOpt) {
        ViewAbstract::SetBackgroundBlurStyle(frameNode, convValue, *sysOptionsOpt);
        return;
    }
    ViewAbstract::SetBackgroundBlurStyle(frameNode, convValue);
}
void SetBackgroundEffect1Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<EffectOption>(options);
    auto sysAdaptiveOptions = Converter::OptConvertPtr<SysOptions>(sysOptions);
    ViewAbstractModelStatic::SetBackgroundEffect(frameNode, convValue, sysAdaptiveOptions);
}
void SetForegroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_ForegroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (auto opt = Converter::OptConvertPtr<BlurStyleOption>(options); opt) {
        convValue = *opt;
    }
    if (auto optStyle = Converter::OptConvertPtr<BlurStyle>(style); optStyle) {
        convValue.blurStyle = *optStyle;
    }
    ViewAbstract::SetForegroundBlurStyle(frameNode, convValue);
}
void SetOnClick1Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* event,
                     const Opt_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optEvent = Converter::GetOptPtr(event);
    if (!optEvent) {
        ViewAbstract::DisableOnClick(frameNode);
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optEvent)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    auto convValue = Converter::OptConvertPtr<float>(distanceThreshold);
    double threshold = convValue.value_or(std::numeric_limits<double>::infinity());
    if (threshold != std::numeric_limits<double>::infinity() && threshold >= 0) {
        threshold = Dimension(threshold, DimensionUnit::VP).ConvertToPx();
    } else {
        threshold = std::numeric_limits<double>::infinity();
    }
    ViewAbstract::SetOnClick(frameNode, std::move(onEvent), threshold);
    ViewAbstract::SetOnClick(frameNode, std::move(onEvent), *convValue);
}
void SetFocusScopeIdImpl(Ark_NativePointer node,
                         const Opt_String* id,
                         const Opt_Boolean* isGroup,
                         const Opt_Boolean* arrowStepOut)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convIdValue = Converter::OptConvertPtr<std::string>(id);
    auto convIsGroupValue = Converter::OptConvertPtr<bool>(isGroup);
    auto convArrowStepOutValue = Converter::OptConvertPtr<bool>(arrowStepOut);
    ViewAbstractModelStatic::SetFocusScopeId(frameNode, convIdValue, convIsGroupValue, convArrowStepOutValue);
}
void SetFocusScopePriorityImpl(Ark_NativePointer node,
                               const Opt_String* scopeId,
                               const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convIdValue = Converter::OptConvertPtr<std::string>(scopeId);
    auto optPriority = Converter::OptConvertPtr<uint32_t>(priority);
    ViewAbstractModelStatic::SetFocusScopePriority(frameNode, convIdValue, optPriority);
}
void SetTransition1Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* effect,
                        const Opt_TransitionFinishCallback* onFinish)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(effect);
    std::function<void(bool)> finishCallback;
    auto arkOnFinish = Converter::OptConvertPtr<::TransitionFinishCallback>(onFinish);
    if (arkOnFinish) {
            finishCallback = [callback = CallbackHelper(*arkOnFinish)](bool transitionIn) {
                callback.Invoke(Converter::ArkValue<Ark_Boolean>(transitionIn));
            };
    }
    auto optValue = Converter::GetOptPtr(effect);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto effectPeer = *optValue;
    if (effectPeer && effectPeer->handler) {
        ViewAbstract::SetChainedTransition(frameNode, effectPeer->handler, std::move(finishCallback));
    } else {
        ViewAbstract::CleanTransition(frameNode);
    }
}
void SetBlurImpl(Ark_NativePointer node,
                 const Opt_Number* blurRadius,
                 const Opt_BlurOptions* options,
                 const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blurRadiusOpt = Converter::OptConvertPtr<float>(blurRadius);
    auto optionsOpt = Converter::OptConvertPtr<BlurOption>(options);
    auto sysOptionsOpt = Converter::OptConvertPtr<SysOptions>(sysOptions);
    ViewAbstractModelStatic::SetFrontBlur(frameNode, blurRadiusOpt, optionsOpt, sysOptionsOpt);
}
void SetLinearGradientBlurImpl(Ark_NativePointer node,
                               const Opt_Number* value,
                               const Opt_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvertPtr<Dimension>(value);
    auto convValue = Converter::OptConvertPtr<NG::LinearGradientBlurPara>(options);
    Validator::ValidateNonNegative(radius);
    NG::LinearGradientBlurPara para(
        Dimension(0.0f, DimensionUnit::VP), std::vector<std::pair<float, float>>(), GradientDirection::BOTTOM);
    if (convValue.has_value()) {
        para = convValue.value();
    }
    if (radius.has_value()) {
        para.blurRadius_ = radius.value();
    } else {
        para.blurRadius_ = Dimension(0.0, DimensionUnit::VP);
    }
    ViewAbstractModelStatic::SetLinearGradientBlur(frameNode, std::optional<NG::LinearGradientBlurPara>(para));
}
void SetSystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("The `ViewAbstract::SetSystemBarEffect(frameNode, enable)` function must take two parameters");
}
void SetUseEffect1Impl(Ark_NativePointer node,
                       const Opt_Boolean* useEffect,
                       const Opt_EffectType* effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetBackdropBlurImpl(Ark_NativePointer node,
                         const Opt_Number* radius,
                         const Opt_BlurOptions* options,
                         const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optRadius = Converter::OptConvertPtr<Dimension>(radius);
    auto optOption = Converter::OptConvertPtr<BlurOption>(options);
    auto sysOpts = Converter::OptConvertPtr<SysOptions>(sysOptions).value_or(SysOptions());
    ViewAbstractModelStatic::SetBackdropBlur(frameNode, optRadius, optOption, sysOpts);
}
void SetSharedTransitionImpl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto modelId = Converter::OptConvertPtr<std::string>(id);
    if (!modelId) {
        // Implement Reset value
        return;
    }
    std::shared_ptr<SharedTransitionOption> modelOptions;
    if (auto transOpt = Converter::OptConvertPtr<SharedTransitionOption>(options); transOpt) {
        modelOptions = std::make_shared<SharedTransitionOption>(*transOpt);
    }
    ViewAbstract::SetSharedTransition(frameNode, *modelId, modelOptions);
}
void SetChainModeImpl(Ark_NativePointer node,
                      const Opt_Axis* direction,
                      const Opt_ChainStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ChainInfo chainInfo = {
        .direction = Converter::OptConvertPtr<LineDirection>(direction),
        .style = Converter::OptConvertPtr<ChainStyle>(style)
    };
    ViewAbstractModelStatic::SetChainStyle(frameNode, chainInfo);
}
void SetOnDrop1Impl(Ark_NativePointer node,
                    const Opt_OnDragEventCallback* eventCallback,
                    const Opt_DropOptions* dropOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(eventCallback);
    if (!optValue) {
        ViewAbstract::SetOnDrop(frameNode, nullptr);
        return;
    }
    auto onDrop = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                      const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
    ViewAbstract::SetOnDrop(frameNode, std::move(onDrop));

    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto optValueDropOption = Converter::GetOptPtr(dropOptions);
    if (!optValueDropOption) {
        eventHub->SetDisableDataPrefetch(false);
        return;
    }
    auto disableDataPrefetch = Converter::OptConvert<bool>(optValueDropOption->disableDataPrefetch).value_or(false);
    eventHub->SetDisableDataPrefetch(disableDataPrefetch);
}
void SetDragPreview1Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                         const Opt_PreviewConfiguration* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(config);
    bool onlyForLifting = optValue ? Converter::OptConvert<bool>(optValue->onlyForLifting).value_or(false) : false;
    bool delayCreating = optValue ? Converter::OptConvert<bool>(optValue->delayCreating).value_or(false) : false;
    Converter::VisitUnionPtr(preview,
        [frameNode, onlyForLifting, delayCreating](const Ark_String& val) {
            ViewAbstract::SetDragPreview(frameNode,
                DragDropInfo { .inspectorId = Converter::Convert<std::string>(val),
                               .onlyForLifting = onlyForLifting, .delayCreating = delayCreating });
        },
        [node, frameNode, onlyForLifting, delayCreating](const CustomNodeBuilder& val) {
            CallbackHelper(val).BuildAsync([frameNode, onlyForLifting, delayCreating](const RefPtr<UINode>& uiNode) {
                ViewAbstract::SetDragPreview(frameNode, DragDropInfo { .customNode = uiNode,
                                                                       .onlyForLifting = onlyForLifting,
                                                                       .delayCreating = delayCreating  });
                }, node);
        },
        [node, frameNode, onlyForLifting, delayCreating](const Ark_DragItemInfo& value) {
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            DragDropInfo dragDropInfo {
                .pixelMap = Converter::OptConvert<RefPtr<PixelMap>>(value.pixelMap).value_or(nullptr),
                .extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string()),
                .onlyForLifting = onlyForLifting, .delayCreating = delayCreating };
            if (builder) {
                CallbackHelper(builder.value()).BuildAsync([frameNode, dragDropInfo = std::move(dragDropInfo)](
                    const RefPtr<UINode>& uiNode) {
                    DragDropInfo info;
                    info.customNode = uiNode;
                    info.onlyForLifting = dragDropInfo.onlyForLifting;
                    info.delayCreating = dragDropInfo.delayCreating;
                    info.pixelMap = dragDropInfo.pixelMap;
                    ViewAbstract::SetDragPreview(frameNode, info);
                    }, node);
            } else {
                ViewAbstract::SetDragPreview(frameNode, dragDropInfo);
            }
        },
        [frameNode]() {
            ViewAbstract::SetDragPreview(frameNode, DragDropInfo {});
        });
}
void SetOverlayImpl(Ark_NativePointer node,
                    const Opt_Union_String_CustomBuilder_ComponentContent* value,
                    const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    OverlayOptions overlay { .align = Alignment::TOP_LEFT};
    overlay = Converter::OptConvertPtr<OverlayOptions>(options).value_or(overlay);
    Converter::VisitUnionPtr(value, [frameNode, &overlay](const Ark_String& src) {
            overlay.content = Converter::Convert<std::string>(src);
            ViewAbstract::SetOverlay(frameNode, overlay);
        },
        [node, frameNode, overlay](const CustomNodeBuilder& builder) {
            CallbackHelper(builder).BuildAsync([overlay, frameNode](const RefPtr<UINode>& uiNode) {
                ViewAbstract::SetOverlayBuilder(frameNode, uiNode, overlay.align, overlay.x, overlay.y);
                }, node);
        },
        [](const Ark_ComponentContent& src) {
            LOGE("OverlayImpl() Ark_ComponentContent.ComponentContentStub not implemented");
        },
        [frameNode]() {
            ViewAbstractModelStatic::ResetOverlay(frameNode);
        });
}
void SetBlendModeImpl(Ark_NativePointer node,
                      const Opt_BlendMode* value,
                      const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blendMode = Converter::OptConvertPtr<BlendMode>(value);
    auto blendApplyType = Converter::OptConvertPtr<BlendApplyType>(type);
    ViewAbstractModelStatic::SetBlendMode(frameNode, blendMode);
    ViewAbstractModelStatic::SetBlendApplyType(frameNode, blendApplyType);
}
void SetAdvancedBlendModeImpl(Ark_NativePointer node,
                              const Ark_Union_BlendMode_Blender* effect,
                              const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(effect);
    BlendMode blendMode = BlendMode::NONE;
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    Converter::VisitUnionPtr(effect,
        [&blendMode, &blendApplyType, frameNode](const Ark_BlendMode& value) {
            blendMode = Converter::OptConvert<BlendMode>(value).value_or(blendMode);
            blendApplyType = BlendApplyType::OFFSCREEN;
            ViewAbstractModelStatic::SetBlendMode(frameNode, blendMode);
        },
        [](const Ark_uiEffect_BrightnessBlender& value) {
            LOGE("CommonMethodModifier::AdvancedBlendModeImpl Ark_uiEffect_BrightnessBlender is not supported yet.");
        },
        []() {}
    );
    std::optional<BlendApplyType> blendApplyTypeOpt = Converter::OptConvertPtr<BlendApplyType>(type);
    blendApplyType = blendApplyTypeOpt.value_or(blendApplyType);
    ViewAbstractModelStatic::SetBlendApplyType(frameNode, blendApplyType);
}
void SetGeometryTransition1Impl(Ark_NativePointer node,
                                const Opt_String* id,
                                const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto idOpt = Converter::OptConvertPtr<std::string>(id);
    if (!idOpt) {
        return; // undefined return, same with ArktsDyn
    }
    auto optOptions = Converter::OptConvertPtr<GeometryTransitionOptions>(options);
    // follow flag
    bool followWithoutTransition { false };
    // hierarchy flag
    bool doRegisterSharedTransition { true };
    if (optOptions.has_value()) {
        followWithoutTransition = optOptions->follow.value_or(false);
        if (optOptions->hierarchyStrategy &&
            optOptions->hierarchyStrategy.value() == TransitionHierarchyStrategy::NONE) {
            doRegisterSharedTransition = false;
        }
    }
    ViewAbstractModelStatic::SetGeometryTransition(
        frameNode, idOpt.value(), followWithoutTransition, doRegisterSharedTransition);
}
void SetBindTipsImpl(Ark_NativePointer node,
                     const Opt_TipsMessageType* message,
                     const Opt_TipsOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    RefPtr<SpanString> styledString;
    auto tipsOption = Converter::OptConvertPtr<Ark_TipsOptions>(options);
    if (tipsOption.has_value()) {
        popupParam = Converter::Convert<RefPtr<PopupParam>>(tipsOption.value());
    }
    popupParam->SetBlockEvent(false);
    popupParam->SetTipsFlag(true);
    popupParam->SetShowInSubWindow(true);
    popupParam->SetKeyBoardAvoidMode(PopupKeyboardAvoidMode::DEFAULT);
    Converter::VisitUnion(*message,
        [frameNode, popupParam, styledString] (const Ark_ResourceStr& value) {
            auto message = Converter::OptConvert<std::string>(value);
            if (message.has_value()) {
                popupParam->SetMessage(message.value());
            }
            ViewAbstractModelStatic::BindTips(frameNode, popupParam, styledString);
        },
        [] (const Ark_StyledString& value) {
            return;
        },
        [frameNode, popupParam, styledString] () {
            ViewAbstractModelStatic::BindTips(frameNode, popupParam, styledString);
            return;
        });
}
void SetBindPopupImpl(Ark_NativePointer node,
                      const Opt_Boolean* show,
                      const Opt_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optShow = Converter::OptConvertPtr<bool>(show);
    auto onWillDismissPopup = [](
        const Opt_Union_Boolean_Callback_DismissPopupAction_Void& param, RefPtr<PopupParam>& popupParam) {
        CHECK_NULL_VOID(popupParam);
        Converter::VisitUnion(param,
            [&popupParam](const Ark_Boolean& value) {
                popupParam->SetInteractiveDismiss(Converter::Convert<bool>(value));
                popupParam->SetOnWillDismiss(nullptr);
            },
            [&popupParam](const Callback_DismissPopupAction_Void& value) {
                auto callback = [arkCallback = CallbackHelper(value)](int32_t reason) {
                    auto parameter = PeerUtils::CreatePeer<DismissPopupActionPeer>();
                    parameter->reason = static_cast<BindSheetDismissReason>(reason);
                    arkCallback.InvokeSync(parameter);
                };
                popupParam->SetOnWillDismiss(std::move(callback));
                popupParam->SetInteractiveDismiss(true);
            },
            []() {});
    };
    Converter::VisitUnionPtr(popup,
        [frameNode, optShow, onWillDismissPopup](const Ark_PopupOptions& value) {
            auto popupParam = Converter::Convert<RefPtr<PopupParam>>(value);
            CHECK_NULL_VOID(popupParam);
            onWillDismissPopup(value.onWillDismiss, popupParam);
            popupParam->SetIsShow(optShow.value_or(false));
           ViewAbstractModelStatic::BindPopup(frameNode, popupParam, nullptr);
        },
        [frameNode, node, optShow, onWillDismissPopup](const Ark_CustomPopupOptions& value) {
            auto popupParam = Converter::Convert<RefPtr<PopupParam>>(value);
            CHECK_NULL_VOID(popupParam);
            onWillDismissPopup(value.onWillDismiss, popupParam);
            if (popupParam->IsShow() && !g_isPopupCreated(frameNode)) {
                popupParam->SetIsShow(optShow.value_or(false));
                CallbackHelper(value.builder).BuildAsync([frameNode, popupParam](const RefPtr<UINode>& uiNode) {
                    ViewAbstractModelStatic::BindPopup(frameNode, popupParam, uiNode);
                    }, node);
            } else {
                popupParam->SetIsShow(optShow.value_or(false));
                ViewAbstractModelStatic::BindPopup(frameNode, popupParam, nullptr);
            }
        },
        [frameNode, optShow]() {
            auto popupParam = AceType::MakeRefPtr<PopupParam>();
            popupParam->SetIsShow(optShow.value_or(false));
            ViewAbstractModelStatic::BindPopup(frameNode, popupParam, nullptr);
        });
}
void BindMenuBase(Ark_NativePointer node,
    const Opt_Boolean *isShow,
    const bool setShow,
    const Opt_Union_Array_MenuElement_CustomBuilder* content,
    const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuParam menuParam;
    menuParam.placement = Placement::BOTTOM_LEFT;
    menuParam.isShowInSubWindow = false;
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuParam.isShowInSubWindow = theme->GetExpandDisplay();
    menuParam.setShow = setShow;
    menuParam.isShow = Converter::OptConvertPtr<bool>(isShow).value_or(menuParam.isShow);
    auto menuOptions = Converter::OptConvertPtr<Ark_MenuOptions>(options);
    if (menuOptions) {
        menuParam.title = OptConvert<std::string>(menuOptions->title).value_or(menuParam.title);
        auto weakNode = AceType::WeakClaim(frameNode);
        g_bindMenuOptionsParam(menuOptions.value(), menuParam, weakNode);
        if (menuParam.isShowInSubWindow) {
            menuParam.isShowInSubWindow = OptConvert<bool>(menuOptions->showInSubWindow).value_or(true);
        }
    }
    Converter::VisitUnionPtr(content,
        [frameNode, menuParam](const Array_MenuElement& value) {
            auto optionsParam = Converter::Convert<std::vector<OptionParam>>(value);
            ViewAbstractModelStatic::BindMenu(frameNode, std::move(optionsParam), nullptr, menuParam);
        },
        [frameNode, node, menuParam](const CustomNodeBuilder& value) {
            auto builder = [callback = CallbackHelper(value), node]() {
                auto uiNode = callback.BuildSync(node);
                ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            ViewAbstractModelStatic::BindMenu(frameNode, {}, std::move(builder), menuParam);
        },
        []() {});
}
void SetBindMenu0Impl(Ark_NativePointer node,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    auto show = ArkValue<Opt_Boolean>(false);
    BindMenuBase(node, &show, false, content, options);
}
void SetBindMenu1Impl(Ark_NativePointer node,
                      const Opt_Boolean* isShow,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    BindMenuBase(node, isShow, true, content, options);
}
void ParseContextMenuParam(MenuParam& menuParam, const std::optional<Ark_ContextMenuOptions>& menuOption,
    const ResponseType type, Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    g_bindContextMenuParams(menuParam, menuOption, node, frameNode);
    if (type != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.isShowHoverImage = false;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
}
void BindContextMenuBase(Ark_NativePointer node,
    const Opt_CustomNodeBuilder* content,
    const Opt_ResponseType *responseType,
    const Opt_ContextMenuOptions* options,
    MenuParam& menuParam)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(content);
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    auto type = Converter::OptConvertPtr<ResponseType>(responseType).value_or(ResponseType::LONG_PRESS);
    std::function<void(MenuParam, std::function<void()> &&)> contentBuilder;
    if (!optValue) {
        contentBuilder = [node, frameNode, type](MenuParam menuParam, std::function<void()>&& previewBuildFunc) {
            ViewAbstractModelStatic::BindContextMenuStatic(
                AceType::Claim(frameNode), type, nullptr, menuParam, std::move(previewBuildFunc));
            ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(frameNode, menuParam);
        };
    } else {
        contentBuilder = [callback = CallbackHelper(*optValue), node, frameNode, type](
                             MenuParam menuParam, std::function<void()>&& previewBuildFunc) {
            callback.BuildAsync(
                [frameNode, type, menuParam, previewBuildFunc](const RefPtr<UINode>& uiNode) mutable {
                    auto builder = [frameNode, uiNode]() {
                        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                        ViewStackProcessor::GetInstance()->Push(uiNode);
                    };
                    ViewAbstractModelStatic::BindContextMenuStatic(
                        AceType::Claim(frameNode), type, std::move(builder), menuParam, std::move(previewBuildFunc));
                    ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(frameNode, menuParam);
                },
                node);
        };
    }
    menuParam.previewMode = MenuPreviewMode::NONE;
    auto menuOption = Converter::GetOptPtr(options);
    Converter::VisitUnion(menuOption->preview,
        [&menuParam, menuOption, type, node, contentBuilder](const Ark_MenuPreviewMode& value) {
            auto mode = Converter::OptConvert<MenuPreviewMode>(value);
            if (mode && mode.value() == MenuPreviewMode::IMAGE) {
                menuParam.previewMode = MenuPreviewMode::IMAGE;
            }
            ParseContextMenuParam(menuParam, menuOption, type, node);
            std::function<void()> previewBuildFunc = nullptr;
            contentBuilder(menuParam, std::move(previewBuildFunc));
        },
        [&menuParam, menuOption, type, node, &contentBuilder](const CustomNodeBuilder& value) {
            auto frameNode = reinterpret_cast<FrameNode *>(node);
            CHECK_NULL_VOID(frameNode);
            menuParam.previewMode = MenuPreviewMode::CUSTOM;
            ParseContextMenuParam(menuParam, menuOption, type, node);
            CallbackHelper(value).BuildAsync([frameNode, menuParam, contentBuilder](const RefPtr<UINode>& uiNode) {
                auto previewBuildFunc = [frameNode, uiNode]() {
                    PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
                contentBuilder(menuParam, std::move(previewBuildFunc));
                }, node);
        },
        [&menuParam, contentBuilder]() {
            std::function<void()> previewBuildFunc = nullptr;
            contentBuilder(menuParam, std::move(previewBuildFunc));
        });
}
void SetBindContextMenu0Impl(Ark_NativePointer node,
                             const Opt_CustomNodeBuilder* content,
                             const Opt_ResponseType* responseType,
                             const Opt_ContextMenuOptions* options)
{
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::NORMAL_TYPE;
    menuParam.isShow = false;
    BindContextMenuBase(node, content, responseType, options, menuParam);
}
void SetBindContextMenu1Impl(Ark_NativePointer node,
                             const Opt_Boolean* isShown,
                             const Opt_CustomNodeBuilder* content,
                             const Opt_ContextMenuOptions* options)
{
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = Converter::OptConvertPtr<bool>(isShown).value_or(menuParam.isShow);
    auto type = Converter::ArkValue<Opt_ResponseType>(ARK_RESPONSE_TYPE_LONG_PRESS);
    BindContextMenuBase(node, content, &type, options, menuParam);
}
void SetBindContentCover0Impl(Ark_NativePointer node,
                              const Opt_Union_Boolean_Bindable* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(builder);
    std::function<void(const std::string&)> changeEvent;
    auto isShowValue = ProcessBindableIsShow(frameNode, isShow, changeEvent);
    ModalStyle modalStyle;
    modalStyle.modalTransition = (Converter::OptConvertPtr<ModalTransition>(type))
        .value_or(ModalTransition::DEFAULT);
    auto optBuilder = Converter::GetOptPtr(builder);
    if (isShowValue && *isShowValue && optBuilder) {
        CallbackHelper(*optBuilder).BuildAsync([frameNode, modalStyle](
            const RefPtr<UINode>& uiNode) mutable {
            auto weakNode = AceType::WeakClaim(frameNode);
            PipelineContext::SetCallBackNode(weakNode);
            auto buildFunc = [uiNode]() -> RefPtr<UINode> {
                return uiNode;
            };
            ContentCoverParam contentCoverParam;
            ViewAbstractModelStatic::BindContentCover(frameNode, true, nullptr, std::move(buildFunc), modalStyle,
                nullptr, nullptr, nullptr, nullptr, contentCoverParam);
            }, node);
    } else {
        ContentCoverParam contentCoverParam;
        std::function<RefPtr<UINode>()> buildFunc = nullptr;
        ViewAbstractModelStatic::BindContentCover(frameNode, false, nullptr, std::move(buildFunc), modalStyle, nullptr,
            nullptr, nullptr, nullptr, contentCoverParam);
    }
}
void SetBindContentCover1Impl(Ark_NativePointer node,
                              const Opt_Union_Boolean_Bindable* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ContentCoverOptions* options)
{
    CHECK_NULL_VOID(builder);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<void(const std::string&)> changeEvent;
    auto isShowValue = ProcessBindableIsShow(frameNode, isShow, changeEvent);
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::DEFAULT;
    std::function<void()> onShowCallback;
    std::function<void()> onDismissCallback;
    std::function<void()> onWillShowCallback;
    std::function<void()> onWillDismissCallback;
    std::function<void(const int32_t&)> onWillDismissFunc;
    ContentCoverParam contentCoverParam;
    auto weakNode = AceType::WeakClaim(frameNode);
    auto coverOption = Converter::OptConvertPtr<Ark_ContentCoverOptions>(options);
    if (coverOption) {
        BindSheetUtil::ParseContentCoverCallbacks(weakNode, coverOption.value(), onShowCallback,
            onDismissCallback, onWillShowCallback, onWillDismissCallback, onWillDismissFunc);
        modalStyle.modalTransition = Converter::OptConvert<ModalTransition>(coverOption->modalTransition)
            .value_or(ModalTransition::DEFAULT);
        modalStyle.backgroundColor = Converter::OptConvert<Color>(coverOption->backgroundColor);
        contentCoverParam.transitionEffect = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(coverOption->transition)
            .value_or(contentCoverParam.transitionEffect);
        contentCoverParam.enableSafeArea = Converter::OptConvert<bool>(coverOption->enableSafeArea).value_or(false);
    }
    contentCoverParam.onWillDismiss = std::move(onWillDismissFunc);

    auto optBuilder = Converter::GetOptPtr(builder);
    if (isShowValue && *isShowValue && optBuilder) {
        CallbackHelper(*optBuilder).BuildAsync([weakNode, frameNode, modalStyle, contentCoverParam,
            changeEvent = std::move(changeEvent),
            onShowCallback = std::move(onShowCallback),
            onDismissCallback = std::move(onDismissCallback),
            onWillShowCallback = std::move(onWillShowCallback),
            onWillDismissCallback = std::move(onWillDismissCallback)
        ](const RefPtr<UINode>& uiNode) mutable {
            PipelineContext::SetCallBackNode(weakNode);
            auto buildFunc = [uiNode]() -> RefPtr<UINode> {
                return uiNode;
            };
            ViewAbstractModelStatic::BindContentCover(frameNode, true, std::move(changeEvent), std::move(buildFunc),
                modalStyle, std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
                std::move(onWillDismissCallback), contentCoverParam);
            }, node);
    } else {
        ViewAbstractModelStatic::BindContentCover(frameNode, false, std::move(changeEvent), nullptr,
            modalStyle, std::move(onShowCallback), std::move(onDismissCallback),
            std::move(onWillShowCallback), std::move(onWillDismissCallback), contentCoverParam);
    }
}
void SetBindSheetImpl(Ark_NativePointer node,
                      const Opt_Union_Boolean_Bindable* isShow,
                      const Opt_CustomNodeBuilder* builder,
                      const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(builder);
    std::function<void(const std::string&)> changeEvent;
    auto isShowValue = ProcessBindableIsShow(frameNode, isShow, changeEvent);
    if (!isShowValue) {
        // Implement Reset value
        return;
    }
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    sheetStyle.showInPage = false;
    sheetStyle.enableFloatingDragBar = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto sheetOptions = Converter::OptConvertPtr<Ark_SheetOptions>(options);
    if (sheetOptions) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, sheetOptions.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, sheetOptions.value());
        Converter::VisitUnion(sheetOptions->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = OptConvert<std::string>(value.subtitle.value);
            },
            [&sheetStyle, frameNode, node, &cbs](const CustomNodeBuilder& value) {
                sheetStyle.isTitleBuilder = true;
                cbs.titleBuilder = [callback = CallbackHelper(value), node]() {
                    auto uiNode = callback.BuildSync(node);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            }, []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, sheetOptions.value());
    }
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        // Implement Reset value
        return;
    }
    CallbackHelper(*optBuilder).BuildAsync([frameNode, isShowValue, sheetStyle, changeEvent = std::move(changeEvent),
        cb = std::move(cbs)](
        const RefPtr<UINode>& uiNode) mutable {
        auto buildFunc = [frameNode, uiNode]() {
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        ViewAbstractModelStatic::BindSheet(frameNode, *isShowValue, std::move(changeEvent), std::move(buildFunc),
            std::move(cb.titleBuilder), sheetStyle, std::move(cb.onAppear), std::move(cb.onDisappear),
            std::move(cb.shouldDismiss), std::move(cb.onWillDismiss), std::move(cb.onWillAppear),
            std::move(cb.onWillDisappear), std::move(cb.onHeightDidChange), std::move(cb.onDetentsDidChange),
            std::move(cb.onWidthDidChange), std::move(cb.onTypeDidChange), std::move(cb.sheetSpringBack));
        }, node);
}
void SetOnVisibleAreaChangeImpl(Ark_NativePointer node,
                                const Opt_Array_Number* ratios,
                                const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    auto rawRatioVec = Converter::OptConvertPtr<std::vector<double>>(ratios);
    if (!rawRatioVec) {
        std::vector<double> ratioList;
        ViewAbstract::SetOnVisibleChange(frameNode, nullptr, ratioList);
        return;
    }
    size_t size = rawRatioVec->size();
    std::vector<double> ratioVec;
    for (size_t i = 0; i < size; i++) {
        double ratio = (*rawRatioVec)[i];
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }
    auto optEvent = Converter::GetOptPtr(event);
    if (!optEvent) {
        ViewAbstract::SetOnVisibleChange(frameNode, nullptr, ratioVec);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onVisibleAreaChange =
        [arkCallback = CallbackHelper(*optEvent), node = weakNode](bool visible, double ratio) {
            Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
            Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
            PipelineContext::SetCallBackNode(node);
            arkCallback.InvokeSync(isExpanding, currentRatio);
        };
    ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioVec);
}
void SetOnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                           const Opt_VisibleAreaEventOptions* options,
                                           const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    CHECK_NULL_VOID(event);
    auto rawRatioVec = Converter::OptConvert<std::vector<float>>(options->value.ratios);
    if (!rawRatioVec.has_value()) {
        return;
    }
    std::vector<float> floatArray = rawRatioVec.value();
    size_t size = floatArray.size();
    std::vector<double> ratioVec;
    for (size_t i = 0; i < size; i++) {
        double ratio = static_cast<double>(floatArray[i]);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }
    auto expectedUpdateInterval =
        Converter::OptConvert<int32_t>(options->value.expectedUpdateInterval).value_or(DEFAULT_DURATION);
    if (expectedUpdateInterval < 0) {
        expectedUpdateInterval = DEFAULT_DURATION;
    }
    std::function<void(bool, double)> onVisibleAreaChange = nullptr;
    auto optEvent = Converter::GetOptPtr(event);
    if (!optEvent) {
        ViewAbstract::SetOnVisibleAreaApproximateChange(
            frameNode, nullptr, ratioVec, expectedUpdateInterval);
        return;
    }
    ViewAbstract::SetOnVisibleAreaApproximateChange(
        frameNode, std::move(onVisibleAreaChange), ratioVec, expectedUpdateInterval);
}
void SetKeyboardShortcutImpl(Ark_NativePointer node,
                             const Opt_Union_String_FunctionKey* value,
                             const Opt_Array_ModifierKey* keys,
                             const Opt_Callback_Void* action)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value || !keys) {
        ViewAbstractModelStatic::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
        return;
    }
    auto strValue = Converter::OptConvertPtr<std::string>(value);
    if (value->value.selector == 0 && (!strValue.has_value() || strValue.value().size() != 1)) {
        ViewAbstractModelStatic::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
        return;
    }
    auto keysOptVect = Converter::OptConvertPtr<std::vector<std::optional<ModifierKey>>>(keys);
    if (!keysOptVect) {
        ViewAbstractModelStatic::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
        return;
    }
    std::vector<ModifierKey> keysVect;
    for (auto item : *keysOptVect) {
        if (item.has_value()) {
            keysVect.emplace_back(item.value());
        }
    }
    auto actionOpt = Converter::OptConvertPtr<Callback_Void>(action);
    if (actionOpt) {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyboardShortcutAction = [arkCallback = CallbackHelper(actionOpt.value()), node = weakNode]() {
            PipelineContext::SetCallBackNode(node);
            arkCallback.InvokeSync();
        };
        ViewAbstractModelStatic::SetKeyboardShortcut(
            frameNode, strValue.value(), keysVect, std::move(onKeyboardShortcutAction));
        return;
    }
    ViewAbstractModelStatic::SetKeyboardShortcut(frameNode, strValue.value(), keysVect, nullptr);
}
void SetAccessibilityGroupWithConfigImpl(Ark_NativePointer node,
                                         const Opt_Boolean* isGroup,
                                         const Opt_AccessibilityOptions* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isGroupValue = Converter::OptConvertPtr<bool>(isGroup);
    bool isGroupFlag = false;
    if (isGroupValue) {
        isGroupFlag = *isGroupValue;
    }
    auto optValue = Converter::GetOptPtr(config);
    auto accessibilityPreferred = optValue ?
        Converter::OptConvert<bool>(optValue->accessibilityPreferred) : std::nullopt;
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, isGroupFlag);
    ViewAbstractModelNG::SetAccessibilityTextPreferred(frameNode, accessibilityPreferred.value_or(false));
}
void SetOnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                           const Opt_GestureRecognizerJudgeBeginCallback* callback_,
                                           const Opt_Boolean* exposeInnerGesture)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(callback_);
    if (!optValue) {
        ViewAbstractModelStatic::SetOnGestureRecognizerJudgeBegin(frameNode, nullptr, false);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onGestureRecognizerJudgefunc = [callback = CallbackHelper(*optValue), node = weakNode](
            const std::shared_ptr<BaseGestureEvent>& info,
            const RefPtr<NG::NGGestureRecognizer>& current,
            const std::list<RefPtr<NG::NGGestureRecognizer>>& others
        ) -> GestureJudgeResult {
        GestureJudgeResult defVal = GestureJudgeResult::CONTINUE;
        CHECK_NULL_RETURN(info && current, defVal);
        PipelineContext::SetCallBackNode(node);
        auto gestureInfo = current->GetGestureInfo();
        CHECK_NULL_RETURN(gestureInfo, defVal);
        auto arkGestEvent = CreateArkBaseGestureEvent(info, gestureInfo->GetRecognizerType());
        CHECK_NULL_RETURN(arkGestEvent, defVal);
        auto arkValCurrent = CreateArkGestureRecognizer(current);
        auto arkValOthers = CreateArkGestureRecognizerArray(others);
        auto resultOpt = callback.InvokeWithOptConvertResult<GestureJudgeResult, Ark_GestureJudgeResult,
            Callback_GestureJudgeResult_Void>(arkGestEvent, arkValCurrent, arkValOthers);
        return resultOpt.value_or(defVal);
    };
    auto convValue = Converter::OptConvertPtr<bool>(exposeInnerGesture);
    if (!convValue) {
        ViewAbstractModelStatic::SetOnGestureRecognizerJudgeBegin(
            frameNode, std::move(onGestureRecognizerJudgefunc), false);
        return;
    }
    ViewAbstractModelStatic::SetOnGestureRecognizerJudgeBegin(frameNode,
        std::move(onGestureRecognizerJudgefunc), *convValue);
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::ConstructImpl,
        CommonMethodModifier::SetWidthImpl,
        CommonMethodModifier::SetHeightImpl,
        CommonMethodModifier::SetResponseRegionImpl,
        CommonMethodModifier::SetMouseResponseRegionImpl,
        CommonMethodModifier::SetSizeImpl,
        CommonMethodModifier::SetConstraintSizeImpl,
        CommonMethodModifier::SetHitTestBehaviorImpl,
        CommonMethodModifier::SetOnChildTouchTestImpl,
        CommonMethodModifier::SetLayoutWeightImpl,
        CommonMethodModifier::SetChainWeightImpl,
        CommonMethodModifier::SetPaddingImpl,
        CommonMethodModifier::SetSafeAreaPaddingImpl,
        CommonMethodModifier::SetMarginImpl,
        CommonMethodModifier::SetBackgroundColorImpl,
        CommonMethodModifier::SetPixelRoundImpl,
        CommonMethodModifier::SetBackgroundImageSizeImpl,
        CommonMethodModifier::SetBackgroundImagePositionImpl,
        CommonMethodModifier::SetBackgroundEffect0Impl,
        CommonMethodModifier::SetBackgroundImageResizableImpl,
        CommonMethodModifier::SetForegroundEffectImpl,
        CommonMethodModifier::SetVisualEffectImpl,
        CommonMethodModifier::SetBackgroundFilterImpl,
        CommonMethodModifier::SetForegroundFilterImpl,
        CommonMethodModifier::SetCompositingFilterImpl,
        CommonMethodModifier::SetOpacityImpl,
        CommonMethodModifier::SetBorderImpl,
        CommonMethodModifier::SetBorderStyleImpl,
        CommonMethodModifier::SetBorderWidthImpl,
        CommonMethodModifier::SetBorderColorImpl,
        CommonMethodModifier::SetBorderRadiusImpl,
        CommonMethodModifier::SetBorderImageImpl,
        CommonMethodModifier::SetOutlineImpl,
        CommonMethodModifier::SetOutlineStyleImpl,
        CommonMethodModifier::SetOutlineWidthImpl,
        CommonMethodModifier::SetOutlineColorImpl,
        CommonMethodModifier::SetOutlineRadiusImpl,
        CommonMethodModifier::SetForegroundColorImpl,
        CommonMethodModifier::SetOnClick0Impl,
        CommonMethodModifier::SetOnHoverImpl,
        CommonMethodModifier::SetOnHoverMoveImpl,
        CommonMethodModifier::SetOnAccessibilityHoverImpl,
        CommonMethodModifier::SetHoverEffectImpl,
        CommonMethodModifier::SetOnMouseImpl,
        CommonMethodModifier::SetOnTouchImpl,
        CommonMethodModifier::SetOnKeyEventImpl,
        CommonMethodModifier::SetOnDigitalCrownImpl,
        CommonMethodModifier::SetOnKeyPreImeImpl,
        CommonMethodModifier::SetOnKeyEventDispatchImpl,
        CommonMethodModifier::SetOnFocusAxisEventImpl,
        CommonMethodModifier::SetOnAxisEventImpl,
        CommonMethodModifier::SetFocusableImpl,
        CommonMethodModifier::SetNextFocusImpl,
        CommonMethodModifier::SetTabStopImpl,
        CommonMethodModifier::SetOnFocusImpl,
        CommonMethodModifier::SetOnBlurImpl,
        CommonMethodModifier::SetTabIndexImpl,
        CommonMethodModifier::SetDefaultFocusImpl,
        CommonMethodModifier::SetGroupDefaultFocusImpl,
        CommonMethodModifier::SetFocusOnTouchImpl,
        CommonMethodModifier::SetFocusBoxImpl,
        CommonMethodModifier::SetAnimationImpl,
        CommonMethodModifier::SetTransition0Impl,
        CommonMethodModifier::SetMotionBlurImpl,
        CommonMethodModifier::SetBrightnessImpl,
        CommonMethodModifier::SetContrastImpl,
        CommonMethodModifier::SetGrayscaleImpl,
        CommonMethodModifier::SetColorBlendImpl,
        CommonMethodModifier::SetSaturateImpl,
        CommonMethodModifier::SetSepiaImpl,
        CommonMethodModifier::SetInvertImpl,
        CommonMethodModifier::SetHueRotateImpl,
        CommonMethodModifier::SetUseShadowBatchingImpl,
        CommonMethodModifier::SetUseEffect0Impl,
        CommonMethodModifier::SetRenderGroupImpl,
        CommonMethodModifier::SetFreezeImpl,
        CommonMethodModifier::SetTranslateImpl,
        CommonMethodModifier::SetScaleImpl,
        CommonMethodModifier::SetRotateImpl,
        CommonMethodModifier::SetTransformImpl,
        CommonMethodModifier::SetTransform3DImpl,
        CommonMethodModifier::SetOnAppearImpl,
        CommonMethodModifier::SetOnDisAppearImpl,
        CommonMethodModifier::SetOnAttachImpl,
        CommonMethodModifier::SetOnDetachImpl,
        CommonMethodModifier::SetOnAreaChangeImpl,
        CommonMethodModifier::SetVisibilityImpl,
        CommonMethodModifier::SetFlexGrowImpl,
        CommonMethodModifier::SetFlexShrinkImpl,
        CommonMethodModifier::SetFlexBasisImpl,
        CommonMethodModifier::SetAlignSelfImpl,
        CommonMethodModifier::SetDisplayPriorityImpl,
        CommonMethodModifier::SetZIndexImpl,
        CommonMethodModifier::SetDirectionImpl,
        CommonMethodModifier::SetAlignImpl,
        CommonMethodModifier::SetPositionImpl,
        CommonMethodModifier::SetMarkAnchorImpl,
        CommonMethodModifier::SetOffsetImpl,
        CommonMethodModifier::SetEnabledImpl,
        CommonMethodModifier::SetAlignRulesWithAlignRuleOptionTypedValueImpl,
        CommonMethodModifier::SetAlignRulesWithLocalizedAlignRuleOptionsTypedValueImpl,
        CommonMethodModifier::SetAspectRatioImpl,
        CommonMethodModifier::SetClickEffectImpl,
        CommonMethodModifier::SetOnDragStartImpl,
        CommonMethodModifier::SetOnDragEnterImpl,
        CommonMethodModifier::SetOnDragMoveImpl,
        CommonMethodModifier::SetOnDragLeaveImpl,
        CommonMethodModifier::SetOnDrop0Impl,
        CommonMethodModifier::SetOnDragEndImpl,
        CommonMethodModifier::SetDraggableImpl,
        CommonMethodModifier::SetDragPreview0Impl,
        CommonMethodModifier::SetOnPreDragImpl,
        CommonMethodModifier::SetLinearGradientImpl,
        CommonMethodModifier::SetSweepGradientImpl,
        CommonMethodModifier::SetRadialGradientImpl,
        CommonMethodModifier::SetMotionPathImpl,
        CommonMethodModifier::SetShadowImpl,
        CommonMethodModifier::SetClipImpl,
        CommonMethodModifier::SetClipShapeImpl,
        CommonMethodModifier::SetMaskImpl,
        CommonMethodModifier::SetMaskShapeImpl,
        CommonMethodModifier::SetKeyImpl,
        CommonMethodModifier::SetIdImpl,
        CommonMethodModifier::SetGeometryTransition0Impl,
        CommonMethodModifier::SetRestoreIdImpl,
        CommonMethodModifier::SetSphericalEffectImpl,
        CommonMethodModifier::SetLightUpEffectImpl,
        CommonMethodModifier::SetPixelStretchEffectImpl,
        CommonMethodModifier::SetAccessibilityGroupWithValueImpl,
        CommonMethodModifier::SetAccessibilityTextOfStringTypeImpl,
        CommonMethodModifier::SetAccessibilityNextFocusIdImpl,
        CommonMethodModifier::SetAccessibilityDefaultFocusImpl,
        CommonMethodModifier::SetAccessibilityUseSamePageImpl,
        CommonMethodModifier::SetAccessibilityScrollTriggerableImpl,
        CommonMethodModifier::SetAccessibilityTextOfResourceTypeImpl,
        CommonMethodModifier::SetAccessibilityRoleImpl,
        CommonMethodModifier::SetOnAccessibilityFocusImpl,
        CommonMethodModifier::SetOnAccessibilityActionInterceptImpl,
        CommonMethodModifier::SetAccessibilityTextHintImpl,
        CommonMethodModifier::SetAccessibilityDescriptionOfStringTypeImpl,
        CommonMethodModifier::SetAccessibilityDescriptionOfResourceTypeImpl,
        CommonMethodModifier::SetAccessibilityLevelImpl,
        CommonMethodModifier::SetAccessibilityVirtualNodeImpl,
        CommonMethodModifier::SetAccessibilityCheckedImpl,
        CommonMethodModifier::SetAccessibilitySelectedImpl,
        CommonMethodModifier::SetObscuredImpl,
        CommonMethodModifier::SetReuseIdImpl,
        CommonMethodModifier::SetReuseImpl,
        CommonMethodModifier::SetRenderFitImpl,
        CommonMethodModifier::SetBackgroundBrightnessImpl,
        CommonMethodModifier::SetOnGestureJudgeBeginImpl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::SetShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::SetMonopolizeEventsImpl,
        CommonMethodModifier::SetOnTouchInterceptImpl,
        CommonMethodModifier::SetOnSizeChangeImpl,
        CommonMethodModifier::SetAccessibilityFocusDrawLevelImpl,
        CommonMethodModifier::SetExpandSafeAreaImpl,
        CommonMethodModifier::SetBackgroundImpl,
        CommonMethodModifier::SetBackgroundImage0Impl,
        CommonMethodModifier::SetBackgroundImage1Impl,
        CommonMethodModifier::SetBackgroundImage2Impl,
        CommonMethodModifier::SetBackgroundBlurStyleImpl,
        CommonMethodModifier::SetBackgroundEffect1Impl,
        CommonMethodModifier::SetForegroundBlurStyleImpl,
        CommonMethodModifier::SetOnClick1Impl,
        CommonMethodModifier::SetFocusScopeIdImpl,
        CommonMethodModifier::SetFocusScopePriorityImpl,
        CommonMethodModifier::SetTransition1Impl,
        CommonMethodModifier::SetBlurImpl,
        CommonMethodModifier::SetLinearGradientBlurImpl,
        CommonMethodModifier::SetSystemBarEffectImpl,
        CommonMethodModifier::SetUseEffect1Impl,
        CommonMethodModifier::SetBackdropBlurImpl,
        CommonMethodModifier::SetSharedTransitionImpl,
        CommonMethodModifier::SetChainModeImpl,
        CommonMethodModifier::SetOnDrop1Impl,
        CommonMethodModifier::SetDragPreview1Impl,
        CommonMethodModifier::SetOverlayImpl,
        CommonMethodModifier::SetBlendModeImpl,
        CommonMethodModifier::SetAdvancedBlendModeImpl,
        CommonMethodModifier::SetGeometryTransition1Impl,
        CommonMethodModifier::SetBindTipsImpl,
        CommonMethodModifier::SetBindPopupImpl,
        CommonMethodModifier::SetBindMenu0Impl,
        CommonMethodModifier::SetBindMenu1Impl,
        CommonMethodModifier::SetBindContextMenu0Impl,
        CommonMethodModifier::SetBindContextMenu1Impl,
        CommonMethodModifier::SetBindContentCover0Impl,
        CommonMethodModifier::SetBindContentCover1Impl,
        CommonMethodModifier::SetBindSheetImpl,
        CommonMethodModifier::SetOnVisibleAreaChangeImpl,
        CommonMethodModifier::SetOnVisibleAreaApproximateChangeImpl,
        CommonMethodModifier::SetKeyboardShortcutImpl,
        CommonMethodModifier::SetAccessibilityGroupWithConfigImpl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin1Impl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
