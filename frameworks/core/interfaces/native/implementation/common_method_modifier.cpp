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
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/color_metrics_peer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/focus_axis_event_peer.h"
#include "core/interfaces/native/implementation/gesture_group_interface_peer.h"
#include "core/interfaces/native/implementation/gesture_recognizer_peer_impl.h"
#include "core/interfaces/native/implementation/long_press_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/long_press_recognizer_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pan_recognizer_peer.h"
#include "core/interfaces/native/implementation/pinch_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pinch_recognizer_peer.h"
#include "core/interfaces/native/implementation/progress_mask_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/rotation_recognizer_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/swipe_recognizer_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/tap_recognizer_peer.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "frameworks/core/interfaces/native/implementation/bind_sheet_utils.h"
#include "base/log/log_wrapper.h"

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
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(recognizer);
    if (tapRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(Converter::ArkValue<Ark_TapRecognizer>(tapRecognizer));
    }
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(recognizer);
    if (longPressRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(
            Converter::ArkValue<Ark_LongPressRecognizer>(longPressRecognizer));
    }
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(recognizer);
    if (panRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(Converter::ArkValue<Ark_PanRecognizer>(panRecognizer));
    }
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(recognizer);
    if (pinchRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(Converter::ArkValue<Ark_PinchRecognizer>(pinchRecognizer));
    }
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(recognizer);
    if (swipeRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(Converter::ArkValue<Ark_SwipeRecognizer>(swipeRecognizer));
    }
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(recognizer);
    if (rotationRecognizer) {
        return reinterpret_cast<Ark_GestureRecognizer>(Converter::ArkValue<Ark_RotationRecognizer>(rotationRecognizer));
    }
    return Converter::ArkValue<Ark_GestureRecognizer>(recognizer);
}
}
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

struct TranslateOpt {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
    std::optional<Dimension> z;
};

struct GridSizeOpt {
    std::optional<int32_t> span;
    std::optional<int32_t> offset;
    GridSizeType type;
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
using BackgroundImagePositionType = std::variant<
    Ark_Position,
    Ark_Alignment
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

auto g_onWillDismissPopup = [](
    const Opt_Union_Boolean_Callback_DismissPopupAction_Void& param, RefPtr<PopupParam>& popupParam) {
    CHECK_NULL_VOID(popupParam);
    Converter::VisitUnion(param,
        [&popupParam](const Ark_Boolean& value) {
            popupParam->SetInteractiveDismiss(Converter::Convert<bool>(value));
            popupParam->SetOnWillDismiss(nullptr);
        },
        [&popupParam](const Callback_DismissPopupAction_Void& value) {
            auto callback = [arkCallback = CallbackHelper(value)](int32_t reason) {
                Ark_DismissPopupAction parameter;
                auto reasonOpt = Converter::ArkValue<Opt_DismissReason>(
                    static_cast<BindSheetDismissReason>(reason));
                parameter.reason = Converter::OptConvert<Ark_DismissReason>(reasonOpt)
                    .value_or(ARK_DISMISS_REASON_CLOSE_BUTTON);
                const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstract::DismissPopup));
                parameter.dismiss = keeper.ArkValue();
                arkCallback.InvokeSync(parameter);
            };
            popupParam->SetOnWillDismiss(std::move(callback));
            popupParam->SetInteractiveDismiss(true);
        },
        []() {});
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
    auto arkOnStateChange = OptConvert<PopupStateChangeCallback>(src.onStateChange);
    if (arkOnStateChange.has_value()) {
        auto onStateChangeCallback = [arkCallback = CallbackHelper(arkOnStateChange.value())](
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
    Validator::ValidateNonNegative(arrowWidthOpt);
    Validator::ValidateNonPercent(arrowWidthOpt);
    if (arrowWidthOpt.has_value()) {
        popupParam->SetArrowWidth(arrowWidthOpt.value());
    }
    auto arrowHeightOpt = Converter::OptConvert<CalcDimension>(src.arrowHeight);
    Validator::ValidateNonNegative(arrowHeightOpt);
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

auto g_bindMenuOptionsParam = [](
    const auto& menuOptions, MenuParam& menuParam, WeakPtr<FrameNode> weakNode) {
    auto offsetVal =
        OptConvert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(menuOptions.offset);
    if (offsetVal) {
        menuParam.positionOffset.SetX(offsetVal.value().first->ConvertToPx());
        menuParam.positionOffset.SetY(offsetVal.value().second->ConvertToPx());
    }
    menuParam.placement = OptConvert<Placement>(menuOptions.placement);
    menuParam.enableHoverMode = OptConvert<bool>(menuOptions.enableHoverMode).value_or(menuParam.enableHoverMode);
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
    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
    menuParam.borderRadius = OptConvert<BorderRadiusProperty>(menuOptions.borderRadius);
    menuParam.previewBorderRadius = OptConvert<BorderRadiusProperty>(menuOptions.previewBorderRadius);
    menuParam.layoutRegionMargin = OptConvert<PaddingProperty>(menuOptions.layoutRegionMargin);
    menuParam.hapticFeedbackMode =
        OptConvert<HapticFeedbackMode>(menuOptions.hapticFeedbackMode).value_or(menuParam.hapticFeedbackMode);
    menuParam.outlineColor = OptConvert<BorderColorProperty>(menuOptions.outlineColor);
    menuParam.outlineWidth = OptConvert<BorderWidthProperty>(menuOptions.outlineWidth);
};

auto g_bindContextMenuParams = [](MenuParam& menuParam, const std::optional<Ark_ContextMenuOptions>& menuOption,
    Ark_NativePointer node, FrameNode* frameNode) {
    CHECK_NULL_VOID(menuOption);
    menuParam.placement = Placement::BOTTOM_LEFT;
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

namespace GeneratedModifier {
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor();
const GENERATED_ArkUITapRecognizerAccessor* GetTapRecognizerAccessor();
const GENERATED_ArkUILongPressRecognizerAccessor* GetLongPressRecognizerAccessor();
const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor();
const GENERATED_ArkUIPinchRecognizerAccessor* GetPinchRecognizerAccessor();
const GENERATED_ArkUISwipeRecognizerAccessor* GetSwipeRecognizerAccessor();
const GENERATED_ArkUIRotationRecognizerAccessor* GetRotationRecognizerAccessor();

namespace CommonMethodModifier {
void BackgroundEffect1Impl(
    Ark_NativePointer node, const Opt_BackgroundEffectOptions* options, const Opt_SystemAdaptiveOptions* sysOptions);
void ForegroundBlurStyle1Impl(Ark_NativePointer node, const Opt_BlurStyle* style,
    const Opt_ForegroundBlurStyleOptions* options, const Opt_SystemAdaptiveOptions* sysOptions);
void Blur1Impl(Ark_NativePointer node,
    const Opt_Number* blurRadius,
    const Opt_BlurOptions* options,
    const Opt_SystemAdaptiveOptions* sysOptions);
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
        const InvertOption& option = *optionPtr;
        if (LessNotEqual(option.low_, left) || LessNotEqual(option.high_, left) ||
            LessNotEqual(option.threshold_, left) || LessNotEqual(option.thresholdRange_, left) ||
            GreatNotEqual(option.low_, right) || GreatNotEqual(option.high_, right) ||
            GreatNotEqual(option.threshold_, right) || GreatNotEqual(option.thresholdRange_, right)) {
            value.reset();
            return;
        }
    }
    if (auto floatPtr = std::get_if<float>(&invertVariant)) {
        if (LessNotEqual(*floatPtr, left) || GreatNotEqual(*floatPtr, right)) {
            value.reset();
        }
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
MenuPreviewAnimationOptions Convert(const Ark_AnimationRange_Number& options)
{
    return {
        .scaleFrom = Convert<float>(options.value0),
        .scaleTo = Convert<float>(options.value1)
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
    OHOS::Ace::SharedTransitionOption o = { .duration = INT_MIN };
    if (auto opt = Converter::OptConvert<RefPtr<Curve>>(src.curve); opt) {
        o.curve = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.duration); opt) {
        o.duration = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.delay); opt) {
        o.delay = *opt;
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
    auto centerX = Converter::Convert<Dimension>(src.center.value0);
    if (centerX.Unit() == DimensionUnit::PERCENT) {
        centerX = centerX * PERCENT_100;
    }
    gradient.GetRadialGradient()->radialCenterX = centerX;

    auto centerY = Converter::Convert<Dimension>(src.center.value1);
    if (centerY.Unit() == DimensionUnit::PERCENT) {
        centerY = centerY * PERCENT_100;
    }
    gradient.GetRadialGradient()->radialCenterY = centerY;

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
        valueWidth = width.Value();
    }
    if (height.Unit() == DimensionUnit::PERCENT) {
        typeHeight = BackgroundImageSizeType::PERCENT;
        valueHeight = height.Value();
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
std::pair<std::optional<Dimension>, std::optional<Dimension>> Convert(const Ark_Position& src)
{
    auto x = OptConvert<Dimension>(src.x);
    auto y = OptConvert<Dimension>(src.y);
    return {x, y};
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
BlurStyleOption Convert(const Ark_ForegroundBlurStyleOptions& src)
{
    BlurStyleOption dst;
    dst.colorMode = OptConvert<ThemeColorMode>(src.colorMode).value_or(dst.colorMode);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    if (auto scaleOpt = OptConvert<float>(src.scale); scaleOpt) {
        dst.scale = static_cast<double>(*scaleOpt);
    }
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    return dst;
}

template<>
OverlayOptions Convert(const Ark_OverlayOptions& src)
{
    OverlayOptions dst;
    auto align = Converter::OptConvert<Alignment>(src.align);
    if (align) {
        dst.align = align.value();
    }
    auto x = Converter::OptConvert<Dimension>(src.offset.value.x);
    if (x) {
        dst.x = x.value();
    }
    auto y = Converter::OptConvert<Dimension>(src.offset.value.y);
    if (y) {
        dst.y = y.value();
    }
    return dst;
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
AlignRule Convert(const Ark_HorizontalAlignOptions& src)
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
AlignRule Convert(const Ark_VerticalAlignOptions& src)
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
    std::map<AlignDirection, AlignRule> rulesMap;
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
    return rulesMap;
}

template<>
std::map<AlignDirection, AlignRule> Convert(const Ark_LocalizedAlignRuleOptions& src)
{
    std::map<AlignDirection, AlignRule> rulesMap;
    auto rule = OptConvert<AlignRule>(src.start);
    if (rule.has_value()) {
        rulesMap[AlignDirection::START] = rule.value();
    }
    rule = OptConvert<AlignRule>(src.end);
    if (rule.has_value()) {
        rulesMap[AlignDirection::END] = rule.value();
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
    if (src) {
        return Color(src->colorValue.value);
    }
    return Color();
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
    Validator::ValidateNonPercent(centerX);
    Validator::ValidateNonPercent(centerY);
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
ScaleOptions Convert(const Ark_ScaleOptions& src)
{
    ScaleOptions scaleOptions;
    auto coord = OptConvert<float>(src.x);
    scaleOptions.xScale = coord.value_or(0.0);
    coord = OptConvert<float>(src.y);
    scaleOptions.yScale = coord.value_or(0.0);
    coord = OptConvert<float>(src.z);
    scaleOptions.zScale = coord.value_or(0.0);

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

template<>
RotateOptions Convert(const Ark_RotateOptions& src)
{
    RotateOptions rotateOptions;
    auto coord = OptConvert<float>(src.x);
    if (coord.has_value()) {
        rotateOptions.xDirection = coord.value();
    }
    coord = OptConvert<float>(src.y);
    if (coord.has_value()) {
        rotateOptions.yDirection = coord.value();
    }
    coord = OptConvert<float>(src.z);
    if (coord.has_value()) {
        rotateOptions.zDirection = coord.value();
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
TransitionOptions Convert(const Ark_TransitionOptions& src)
{
    TransitionOptions options;
    auto type = OptConvert<TransitionType>(src.type);
    if (type.has_value()) {
        options.Type = type.value();
    }
    auto opacity = OptConvert<float>(src.opacity);
    if (opacity.has_value()) {
        options.UpdateOpacity(opacity.value());
    }
    auto translateOpt = Converter::OptConvert<TranslateOptions>(src.translate);
    if (translateOpt.has_value()) {
        options.UpdateTranslate(translateOpt.value());
    }
    auto scaleOpt = Converter::OptConvert<ScaleOptions>(src.scale);
    if (scaleOpt.has_value()) {
        options.UpdateScale(scaleOpt.value());
    }
    auto rotateOpt = Converter::OptConvert<RotateOptions>(src.rotate);
    if (rotateOpt.has_value()) {
        options.UpdateRotate(rotateOpt.value());
    }
    return options;
}

template<>
GridSizeOpt Convert(const Ark_Number& src)
{
    GridSizeOpt options;
    options.span = OptConvert<int32_t>(src);
    Validator::ValidateNonNegative(options.span);
    options.offset = 0;
    return options;
}

template<>
GridSizeOpt Convert(const Ark_Literal_Number_offset_span& src)
{
    GridSizeOpt options;
    options.span = OptConvert<int32_t>(src.span);
    Validator::ValidateNonNegative(options.span);
    options.offset = OptConvert<int32_t>(src.offset);
    return options;
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
    for (auto arkPair : fractionStopsVec) {
        pair = Convert<std::pair<float, float>>(arkPair);
        fractionStops.push_back(pair);
    }
    auto direction = Convert<GradientDirection>(value.direction);
    return NG::LinearGradientBlurPara(blurRadius, fractionStops, direction);
}
template<>
void AssignCast(std::optional<Matrix4>& dst, const Ark_Object& src)
{
    LOGE("This converter is created for testing purposes only. Custom objects are not supported.");
#ifdef WRONG_GEN
    double* row1 = (double*)src.pointers[0];
    double* row2 = (double*)src.pointers[1];
    double* row3 = (double*)src.pointers[2];
    double* row4 = (double*)src.pointers[3];
    if (!row1 || !row2 || !row3 || !row4) {
        dst = std::nullopt;
        return;
    }
    if (strcmp(src.kind, "Matrix4") != 0) {
        dst = std::nullopt;
        return;
    }
    double m11 = row1[0], m12 = row1[1], m13 = row1[2], m14 = row1[3],
        m21 = row2[0], m22 = row2[1], m23 = row2[2], m24 = row2[3],
        m31 = row3[0], m32 = row3[1], m33 = row3[2], m34 = row3[3],
        m41 = row4[0], m42 = row4[1], m43 = row4[2], m44 = row4[3];
    dst = Matrix4(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
#endif
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
RefPtr<PopupParam> Convert(const Ark_TipsOptions& src)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    auto appearingTimeOpt = Converter::OptConvert<int>(src.appearingTime);
    if (appearingTimeOpt.has_value()) {
        popupParam->SetAppearingTime(appearingTimeOpt.value());
    }
    auto disappearingTimeOpt = Converter::OptConvert<int>(src.disappearingTime);
    if (disappearingTimeOpt.has_value()) {
        popupParam->SetDisappearingTime(disappearingTimeOpt.value());
    }
    auto appearingTimeWithContinuousOperationOpt =
        Converter::OptConvert<int>(src.appearingTimeWithContinuousOperation);
    if (appearingTimeWithContinuousOperationOpt.has_value()) {
        popupParam->SetAppearingTimeWithContinuousOperation(appearingTimeWithContinuousOperationOpt.value());
    }
    auto disappearingTimeWithContinuousOperationOpt =
        Converter::OptConvert<int>(src.disappearingTimeWithContinuousOperation);
    if (disappearingTimeWithContinuousOperationOpt.has_value()) {
        popupParam->SetAppearingTime(disappearingTimeWithContinuousOperationOpt.value());
    }
    auto enableArrowOpt = Converter::OptConvert<bool>(src.enableArrow);
    if (enableArrowOpt.has_value()) {
        popupParam->SetEnableArrow(enableArrowOpt.value());
    }
    if (enableArrowOpt.value()) {
        auto arrowPointPositionOpt = Converter::OptConvert<Dimension>(src.arrowPointPosition);
        if (arrowPointPositionOpt.has_value()) {
            popupParam->SetArrowOffset(arrowPointPositionOpt.value());
        }
        auto arrowWidthOpt = Converter::OptConvert<CalcDimension>(src.arrowWidth);
        Validator::ValidateNonNegative(arrowWidthOpt);
        Validator::ValidateNonPercent(arrowWidthOpt);
        if (arrowWidthOpt.has_value()) {
            popupParam->SetArrowWidth(arrowWidthOpt.value());
        }
        auto arrowHeightOpt = Converter::OptConvert<CalcDimension>(src.arrowHeight);
        Validator::ValidateNonNegative(arrowHeightOpt);
        Validator::ValidateNonPercent(arrowHeightOpt);
        if (arrowHeightOpt.has_value()) {
            popupParam->SetArrowHeight(arrowHeightOpt.value());
        }
    }
    popupParam->SetBlockEvent(false);
    popupParam->SetTipsFlag(true);
    popupParam->SetShowInSubWindow(true);
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
void AssignCast(std::optional<Alignment>& dst, const Ark_Literal_Alignment_align& src)
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
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_GestureRecognizer &dst, const RefPtr<NG::NGGestureRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetGestureRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_TapRecognizer &dst, const RefPtr<NG::ClickRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetTapRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_LongPressRecognizer &dst, const RefPtr<NG::LongPressRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetLongPressRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_PanRecognizer &dst, const RefPtr<NG::PanRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetPanRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_PinchRecognizer &dst, const RefPtr<NG::PinchRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetPinchRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_SwipeRecognizer &dst, const RefPtr<NG::SwipeRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetSwipeRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
        dst->Update(src);
    }
}
// this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
void AssignArkValue(Ark_RotationRecognizer &dst, const RefPtr<NG::RotationRecognizer>& src)
{
    auto accessor = GeneratedModifier::GetRotationRecognizerAccessor();
    CHECK_NULL_VOID(accessor);
    dst = accessor->ctor();
    if (dst) {
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
    dst.hand.tag = InteropTag::INTEROP_TAG_OBJECT;
    dst.hand.value = static_cast<Ark_InteractionHand>(src.operatingHand_);
}

template<>
template<>
ArkArrayHolder<Array_FingerInfo>::ArkArrayHolder(const std::list<FingerInfo>& data)
{
    std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const FingerInfo& src) {
        return OHOS::Ace::NG::Converter::ArkValue<Ark_FingerInfo>(src);
    });
}

template<>
template<>
ArkArrayHolder<Array_GestureRecognizer>::ArkArrayHolder(const std::list<RefPtr<NG::NGGestureRecognizer>>& data)
{
    std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const RefPtr<NG::NGGestureRecognizer>& src) {
        return OHOS::Ace::NG::CreateArkGestureRecognizer(src);
    });
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
namespace CommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void SetWidthImpl(Ark_NativePointer node,
                  const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetWidth(frameNode, convValue);
}
void SetHeightImpl(Ark_NativePointer node,
                   const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHeight(frameNode, convValue);
}
void SetDrawModifierImpl(Ark_NativePointer node,
                         const Opt_DrawModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDrawModifier(frameNode, convValue);
}
void SetResponseRegionImpl(Ark_NativePointer node,
                           const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetResponseRegion(frameNode, convValue);
}
void SetMouseResponseRegionImpl(Ark_NativePointer node,
                                const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMouseResponseRegion(frameNode, convValue);
}
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSize(frameNode, convValue);
}
void SetConstraintSizeImpl(Ark_NativePointer node,
                           const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetConstraintSize(frameNode, convValue);
}
void SetHitTestBehaviorImpl(Ark_NativePointer node,
                            const Opt_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHitTestBehavior(frameNode, convValue);
}
void SetOnChildTouchTestImpl(Ark_NativePointer node,
                             const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnChildTouchTest(frameNode, convValue);
}
void SetLayoutWeightImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLayoutWeight(frameNode, convValue);
}
void SetChainWeightImpl(Ark_NativePointer node,
                        const Opt_ChainWeightOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetChainWeight(frameNode, convValue);
}
void SetPaddingImpl(Ark_NativePointer node,
                    const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPadding(frameNode, convValue);
}
void SetSafeAreaPaddingImpl(Ark_NativePointer node,
                            const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSafeAreaPadding(frameNode, convValue);
}
void SetMarginImpl(Ark_NativePointer node,
                   const Opt_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMargin(frameNode, convValue);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundColor(frameNode, convValue);
}
void SetPixelRoundImpl(Ark_NativePointer node,
                       const Opt_PixelRoundPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPixelRound(frameNode, convValue);
}
void SetBackgroundImageSizeImpl(Ark_NativePointer node,
                                const Opt_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImageSize(frameNode, convValue);
}
void SetBackgroundImagePositionImpl(Ark_NativePointer node,
                                    const Opt_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImagePosition(frameNode, convValue);
}
void SetBackgroundEffect0Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundEffect0(frameNode, convValue);
}
void SetBackgroundImageResizableImpl(Ark_NativePointer node,
                                     const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImageResizable(frameNode, convValue);
}
void SetForegroundEffectImpl(Ark_NativePointer node,
                             const Opt_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundEffect(frameNode, convValue);
}
void SetVisualEffectImpl(Ark_NativePointer node,
                         const Opt_uiEffect_VisualEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetVisualEffect(frameNode, convValue);
}
void SetBackgroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundFilter(frameNode, convValue);
}
void SetForegroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundFilter(frameNode, convValue);
}
void SetCompositingFilterImpl(Ark_NativePointer node,
                              const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetCompositingFilter(frameNode, convValue);
}
void SetOpacityImpl(Ark_NativePointer node,
                    const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    ViewAbstractModelStatic::SetOpacity(frameNode, result);
}
void Opacity1Impl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    Opacity0Impl(node, value);
}
void SetBorderImpl(Ark_NativePointer node,
                   const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorder(frameNode, convValue);
}
void SetBorderStyleImpl(Ark_NativePointer node,
                        const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderStyle(frameNode, convValue);
}
void SetBorderWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderWidth(frameNode, convValue);
}
void SetBorderColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderColor(frameNode, convValue);
}
void SetBorderRadiusImpl(Ark_NativePointer node,
                         const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiuses = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    if (radiuses) {
        // TODO: Reset value
        if (frameNode->GetTag() == V2::BUTTON_ETS_TAG) {
            ButtonModelNG::SetBorderRadius(frameNode, radiuses.value().radiusTopLeft, radiuses.value().radiusTopRight,
                radiuses.value().radiusBottomLeft, radiuses.value().radiusBottomRight);
        }
        if (frameNode->GetTag() == V2::IMAGE_ETS_TAG) {
            ImageModelNG::SetBorderRadius(frameNode, radiuses.value().radiusTopLeft, radiuses.value().radiusTopRight,
                radiuses.value().radiusBottomLeft, radiuses.value().radiusBottomRight);
        }
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
    }
}
void SetBorderImageImpl(Ark_NativePointer node,
                        const Opt_BorderImageOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    uint8_t bitSet = 0;
    Converter::VisitUnion(optValue->source,
        [frameNode, &bitSet](const Ark_LinearGradient_common& src) {
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
        []() {});
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
void Outline0Impl(Ark_NativePointer node,
                  const Opt_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void Outline1Impl(Ark_NativePointer node,
                  const Opt_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutline(frameNode, convValue);
}
void SetOutlineStyleImpl(Ark_NativePointer node,
                         const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineStyle(frameNode, convValue);
}
void SetOutlineWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineWidth(frameNode, convValue);
}
void SetOutlineColorImpl(Ark_NativePointer node,
                         const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineColor(frameNode, convValue);
}
void SetOutlineRadiusImpl(Ark_NativePointer node,
                          const Opt_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineRadius(frameNode, convValue);
}
void SetForegroundColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundColor(frameNode, convValue);
}
void SetOnClick0Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnClick0(frameNode, convValue);
}
void SetOnHoverImpl(Ark_NativePointer node,
                    const Opt_Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnHover(frameNode, convValue);
}
void SetOnHoverMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnHoverMove(frameNode, convValue);
}
void SetOnAccessibilityHoverImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAccessibilityHover(frameNode, convValue);
}
void SetHoverEffectImpl(Ark_NativePointer node,
                        const Opt_HoverEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHoverEffect(frameNode, convValue);
}
void SetOnMouseImpl(Ark_NativePointer node,
                    const Opt_Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnMouse(frameNode, convValue);
}
void SetOnTouchImpl(Ark_NativePointer node,
                    const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnTouch(frameNode, convValue);
}
void SetOnKeyEventImpl(Ark_NativePointer node,
                       const Opt_Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyEvent(frameNode, convValue);
}
void SetOnDigitalCrownImpl(Ark_NativePointer node,
                           const Opt_Callback_CrownEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDigitalCrown(frameNode, convValue);
}
void SetOnKeyPreImeImpl(Ark_NativePointer node,
                        const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyPreIme(frameNode, convValue);
}
void SetOnKeyEventDispatchImpl(Ark_NativePointer node,
                               const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyEventDispatch(frameNode, convValue);
}
void SetOnFocusAxisEventImpl(Ark_NativePointer node,
                             const Opt_Callback_FocusAxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnFocusAxisEvent(frameNode, convValue);
}
void SetOnAxisEventImpl(Ark_NativePointer node,
                        const Opt_Callback_AxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAxisEvent(frameNode, convValue);
}
void SetFocusableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusable(frameNode, convValue);
}
void SetNextFocusImpl(Ark_NativePointer node,
                      const Opt_FocusMovement* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetNextFocus(frameNode, convValue);
}
void SetTabStopImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTabStop(frameNode, convValue);
}
void SetOnFocusImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnFocus(frameNode, convValue);
}
void SetOnBlurImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnBlur(frameNode, convValue);
}
void SetTabIndexImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTabIndex(frameNode, convValue);
}
void SetDefaultFocusImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDefaultFocus(frameNode, convValue);
}
void SetGroupDefaultFocusImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGroupDefaultFocus(frameNode, convValue);
}
void SetFocusOnTouchImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusOnTouch(frameNode, convValue);
}
void SetFocusBoxImpl(Ark_NativePointer node,
                     const Opt_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusBox(frameNode, convValue);
}
void SetAnimationImpl(Ark_NativePointer node,
                      const Opt_AnimateParam* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAnimation(frameNode, convValue);
}
void SetTransition0Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTransition0(frameNode, convValue);
}
void SetMotionBlurImpl(Ark_NativePointer node,
                       const Opt_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMotionBlur(frameNode, convValue);
}
void SetBrightnessImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBrightness(frameNode, convValue);
}
void SetContrastImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetContrast(frameNode, convValue);
}
void SetGrayscaleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGrayscale(frameNode, convValue);
}
void SetColorBlendImpl(Ark_NativePointer node,
                       const Opt_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetColorBlend(frameNode, convValue);
}
void SetSaturateImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSaturate(frameNode, convValue);
}
void SetSepiaImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSepia(frameNode, convValue);
}
void SetInvertImpl(Ark_NativePointer node,
                   const Opt_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetInvert(frameNode, convValue);
}
void SetHueRotateImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHueRotate(frameNode, convValue);
}
void SetUseShadowBatchingImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetUseShadowBatching(frameNode, convValue);
}
void SetUseEffect0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetUseEffect0(frameNode, convValue);
}
void SetRenderGroupImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRenderGroup(frameNode, convValue);
}
void SetFreezeImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFreeze(frameNode, convValue);
}
void SetTranslateImpl(Ark_NativePointer node,
                      const Opt_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTranslate(frameNode, convValue);
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
void Scale1Impl(Ark_NativePointer node,
                const Opt_ScaleOptions* value)
{
    Scale0Impl(node, value);
}
void GridSpanImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetGrid(frameNode, convValue, std::nullopt, GridSizeType::UNDEFINED);
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetGrid(frameNode, std::nullopt, convValue, GridSizeType::UNDEFINED);
}
void SetRotateImpl(Ark_NativePointer node,
                   const Opt_RotateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RotateOpt>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    auto xValue = Converter::GetOptPtr(&(value->value.centerX));
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
    auto yValue = Converter::GetOptPtr(&(value->value.centerY));
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
    auto angleValue = value->value.angle;
    Converter::VisitUnion(
        angleValue,
        [&convValue](const Ark_String& str) {
            std::string degreeStr = Converter::Convert<std::string>(str);
            float angle = static_cast<float>(StringUtils::StringToDegree(degreeStr));
            int32_t indA = 3;
            if (convValue->vec5f.size() > indA) {
                convValue->vec5f[indA] = angle;
            }
        },
        [](const Ark_Number& val) {}, []() {});
    ViewAbstractModelStatic::SetRotate(frameNode, convValue->vec5f);
    ViewAbstractModelStatic::SetPivot(frameNode, convValue->center);
}
void Rotate1Impl(Ark_NativePointer node,
                 const Opt_RotateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvertPtr<RotateOpt>(value);
    if (convValue.has_value()) {
        ViewAbstractModelStatic::SetPivot(frameNode, convValue->center);
        ViewAbstractModelStatic::SetRotate(frameNode, convValue->vec5f);
    }
}
void Transform0Impl(Ark_NativePointer node,
                    const Opt_TransformationMatrix* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRotate(frameNode, convValue);
}
void SetTransformImpl(Ark_NativePointer node,
                      const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTransform(frameNode, convValue);
}
void SetOnAppearImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAppear(frameNode, convValue);
}
void SetOnDisAppearImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDisAppear(frameNode, convValue);
}
void SetOnAttachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAttach(frameNode, convValue);
}
void SetOnDetachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDetach(frameNode, convValue);
}
void SetOnAreaChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Area_Area_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAreaChange(frameNode, convValue);
}
void SetVisibilityImpl(Ark_NativePointer node,
                       const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetVisibility(frameNode, convValue);
}
void SetFlexGrowImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexGrow(frameNode, convValue);
}
void SetFlexShrinkImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexShrink(frameNode, convValue);
}
void SetFlexBasisImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexBasis(frameNode, convValue);
}
void SetAlignSelfImpl(Ark_NativePointer node,
                      const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignSelf(frameNode, convValue);
}
void SetDisplayPriorityImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDisplayPriority(frameNode, convValue);
}
void SetZIndexImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetZIndex(frameNode, convValue);
}
void SetDirectionImpl(Ark_NativePointer node,
                      const Opt_Direction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDirection(frameNode, convValue);
}
void SetAlignImpl(Ark_NativePointer node,
                  const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlign(frameNode, convValue);
}
void SetPositionImpl(Ark_NativePointer node,
                     const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPosition(frameNode, convValue);
}
void SetMarkAnchorImpl(Ark_NativePointer node,
                       const Opt_Union_Position_LocalizedPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMarkAnchor(frameNode, convValue);
}
void SetOffsetImpl(Ark_NativePointer node,
                   const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOffset(frameNode, convValue);
}
void SetEnabledImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetEnabled(frameNode, convValue);
}
void SetAlignRules0Impl(Ark_NativePointer node,
                        const Opt_AlignRuleOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignRules0(frameNode, convValue);
}
void SetAlignRules1Impl(Ark_NativePointer node,
                        const Opt_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignRules1(frameNode, convValue);
}
void SetAspectRatioImpl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAspectRatio(frameNode, convValue);
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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragStart(frameNode, convValue);
}
void SetOnDragEnterImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragEnter(frameNode, convValue);
}
void SetOnDragMoveImpl(Ark_NativePointer node,
                       const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragMove(frameNode, convValue);
}
void SetOnDragLeaveImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragLeave(frameNode, convValue);
}
void SetOnDrop0Impl(Ark_NativePointer node,
                    const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDrop0(frameNode, convValue);
}
void SetOnDragEndImpl(Ark_NativePointer node,
                      const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragEnd(frameNode, convValue);
}
void SetAllowDropImpl(Ark_NativePointer node,
                      const Opt_Array_uniformTypeDescriptor_UniformDataType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(eventCallback);
    if (!optValue) {
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
void OnDragEndImpl(Ark_NativePointer node,
                   const Opt_Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void AllowDropImpl(Ark_NativePointer node,
                   const Opt_Array_UniformDataType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto allowDrop = value ? Converter::OptConvert<std::set<std::string>>(*value) : std::nullopt;
    ViewAbstractModelStatic::SetAllowDrop(frameNode, allowDrop);
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDraggable(frameNode, convValue);
}
void SetDragPreview0Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDragPreview0(frameNode, convValue);
}
void SetOnPreDragImpl(Ark_NativePointer node,
                      const Opt_Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnPreDrag(frameNode, convValue);
}
void SetLinearGradientImpl(Ark_NativePointer node,
                           const Opt_LinearGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLinearGradient(frameNode, convValue);
}
void SetSweepGradientImpl(Ark_NativePointer node,
                          const Opt_SweepGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSweepGradient(frameNode, convValue);
}
void SetRadialGradientImpl(Ark_NativePointer node,
                           const Opt_RadialGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRadialGradient(frameNode, convValue);
}
void SetMotionPathImpl(Ark_NativePointer node,
                       const Opt_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMotionPath(frameNode, convValue);
}
void SetShadowImpl(Ark_NativePointer node,
                   const Opt_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetShadow(frameNode, convValue);
}
void SetClipImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetClip(frameNode, convValue);
}
void SetClipShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetClipShape(frameNode, convValue);
}
void SetMaskImpl(Ark_NativePointer node,
                 const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMask(frameNode, convValue);
}
void SetMaskShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMaskShape(frameNode, convValue);
}
void SetKeyImpl(Ark_NativePointer node,
                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetKey(frameNode, convValue);
}
void SetIdImpl(Ark_NativePointer node,
               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetId(frameNode, convValue);
}
void SetGeometryTransition0Impl(Ark_NativePointer node,
                                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGeometryTransition0(frameNode, convValue);
}
void SetStateStylesImpl(Ark_NativePointer node,
                        const Opt_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetStateStyles(frameNode, convValue);
}
void SetRestoreIdImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRestoreId(frameNode, convValue);
}
void SetSphericalEffectImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSphericalEffect(frameNode, convValue);
}
void SetLightUpEffectImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLightUpEffect(frameNode, convValue);
}
void SetPixelStretchEffectImpl(Ark_NativePointer node,
                               const Opt_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPixelStretchEffect(frameNode, convValue);
}
void SetAccessibilityGroup0Impl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityGroup0(frameNode, convValue);
}
void SetAccessibilityText0Impl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityText0(frameNode, convValue);
}
void SetAccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityNextFocusId(frameNode, convValue);
}
void SetAccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDefaultFocus(frameNode, convValue);
}
void SetAccessibilityUseSamePageImpl(Ark_NativePointer node,
                                     const Opt_AccessibilitySamePageMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityUseSamePage(frameNode, convValue);
}
void SetAccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityScrollTriggerable(frameNode, convValue);
}
void SetAccessibilityText1Impl(Ark_NativePointer node,
                               const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityText1(frameNode, convValue);
}
void SetAccessibilityRoleImpl(Ark_NativePointer node,
                              const Opt_AccessibilityRoleType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityRole(frameNode, convValue);
}
void SetOnAccessibilityFocusImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityFocusCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAccessibilityFocus(frameNode, convValue);
}
void SetAccessibilityTextHintImpl(Ark_NativePointer node,
                                  const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityTextHint(frameNode, convValue);
}
void SetAccessibilityDescription0Impl(Ark_NativePointer node,
                                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDescription0(frameNode, convValue);
}
void SetAccessibilityDescription1Impl(Ark_NativePointer node,
                                      const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDescription1(frameNode, convValue);
}
void SetAccessibilityLevelImpl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityLevel(frameNode, convValue);
}
void SetAccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                     const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityVirtualNode(frameNode, convValue);
}
void SetAccessibilityCheckedImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityChecked(frameNode, convValue);
}
void SetAccessibilitySelectedImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilitySelected(frameNode, convValue);
}
void SetObscuredImpl(Ark_NativePointer node,
                     const Opt_Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetObscured(frameNode, convValue);
}
void SetReuseIdImpl(Ark_NativePointer node,
                    const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetReuseId(frameNode, convValue);
}
void SetReuseImpl(Ark_NativePointer node,
                  const Opt_ReuseOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetReuse(frameNode, convValue);
}
void SetRenderFitImpl(Ark_NativePointer node,
                      const Opt_RenderFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRenderFit(frameNode, convValue);
}
void SetGestureModifierImpl(Ark_NativePointer node,
                            const Opt_GestureModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGestureModifier(frameNode, convValue);
}
void SetBackgroundBrightnessImpl(Ark_NativePointer node,
                                 const Opt_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundBrightness(frameNode, convValue);
}
void SetOnGestureJudgeBeginImpl(Ark_NativePointer node,
                                const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnGestureJudgeBegin(frameNode, convValue);
}
void SetOnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                           const Opt_GestureRecognizerJudgeBeginCallback* value)
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

        auto arkGestEvent = Converter::ArkValue<Ark_BaseGestureEvent>(info);
        auto arkValCurrent = CreateArkGestureRecognizer(current);
        Converter::ArkArrayHolder<Array_GestureRecognizer> holderOthers(others);
        auto arkValOthers = holderOthers.ArkValue();
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

        auto arkValCurrent = Converter::ArkValue<Ark_GestureRecognizer>(current);
        Converter::ArkArrayHolder<Array_GestureRecognizer> holderOthers(others);
        auto arkValOthers = holderOthers.ArkValue();
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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMonopolizeEvents(frameNode, convValue);
}
void SetOnTouchInterceptImpl(Ark_NativePointer node,
                             const Opt_Callback_TouchEvent_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnTouchIntercept(frameNode, convValue);
}
void SetOnSizeChangeImpl(Ark_NativePointer node,
                         const Opt_SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSizeChange = [callback = CallbackHelper(*optValue)](const RectF& oldRect, const RectF& newRect) {
        Ark_SizeOptions oldSize;
        oldSize.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
        oldSize.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
        Ark_SizeOptions newSize;
        newSize.width = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(newRect.Width()));
        newSize.height = Converter::ArkValue<Opt_Length>(PipelineBase::Px2VpWithCurrentDensity(newRect.Height()));
        callback.Invoke(oldSize, newSize);
    };
    ViewAbstract::SetOnSizeChanged(frameNode, std::move(onSizeChange));
}
void SetAccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                        const Opt_FocusDrawLevel* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityFocusDrawLevel(frameNode, convValue);
}
void SetCustomPropertyImpl(Ark_NativePointer node,
                           const Opt_String* name,
                           const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(name);
    //auto convValue = Converter::OptConvert<type>(name); // for enums
    //CommonMethodModelNG::SetSetCustomProperty(frameNode, convValue);
}
void SetExpandSafeAreaImpl(Ark_NativePointer node,
                           const Opt_Array_SafeAreaType* types,
                           const Opt_Array_SafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //CommonMethodModelNG::SetSetExpandSafeArea(frameNode, convValue);
}
void SetBackgroundImpl(Ark_NativePointer node,
                       const Opt_CustomNodeBuilder* builder,
                       const Opt_BackgroundOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(builder);
    //auto convValue = Converter::OptConvert<type>(builder); // for enums
    //CommonMethodModelNG::SetSetBackground(frameNode, convValue);
}
void SetBackgroundImage0Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //CommonMethodModelNG::SetSetBackgroundImage0(frameNode, convValue);
}
void SetBackgroundImage1Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_BackgroundImageOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //CommonMethodModelNG::SetSetBackgroundImage1(frameNode, convValue);
}
void SetBackgroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_BackgroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(style);
    //auto convValue = Converter::OptConvert<type>(style); // for enums
    //CommonMethodModelNG::SetSetBackgroundBlurStyle(frameNode, convValue);
}
void SetBackgroundEffect1Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(options);
    //auto convValue = Converter::OptConvert<type>(options); // for enums
    //CommonMethodModelNG::SetSetBackgroundEffect1(frameNode, convValue);
}
void SetForegroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_ForegroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(style);
    //auto convValue = Converter::OptConvert<type>(style); // for enums
    //CommonMethodModelNG::SetSetForegroundBlurStyle(frameNode, convValue);
}
void SetOnClick1Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* event,
                     const Opt_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(event);
    //auto convValue = Converter::OptConvert<type>(event); // for enums
    //CommonMethodModelNG::SetSetOnClick1(frameNode, convValue);
}
void SetFocusScopeIdImpl(Ark_NativePointer node,
                         const Opt_String* id,
                         const Opt_Boolean* isGroup,
                         const Opt_Boolean* arrowStepOut)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetFocusScopeId(frameNode, convValue);
}
void SetFocusScopePriorityImpl(Ark_NativePointer node,
                               const Opt_String* scopeId,
                               const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(scopeId);
    //auto convValue = Converter::OptConvert<type>(scopeId); // for enums
    //CommonMethodModelNG::SetSetFocusScopePriority(frameNode, convValue);
}
void SetTransition1Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* effect,
                        const Opt_TransitionFinishCallback* onFinish)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetSetTransition1(frameNode, convValue);
}
void SetGestureImpl(Ark_NativePointer node,
                    const Opt_GestureType* gesture,
                    const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetGesture(frameNode, convValue);
}
void SetPriorityGestureImpl(Ark_NativePointer node,
                            const Opt_GestureType* gesture,
                            const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetPriorityGesture(frameNode, convValue);
}
void SetParallelGestureImpl(Ark_NativePointer node,
                            const Opt_GestureType* gesture,
                            const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetParallelGesture(frameNode, convValue);
}
void SetBlurImpl(Ark_NativePointer node,
                 const Opt_Number* blurRadius,
                 const Opt_BlurOptions* options,
                 const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(blurRadius);
    //auto convValue = Converter::OptConvert<type>(blurRadius); // for enums
    //CommonMethodModelNG::SetSetBlur(frameNode, convValue);
}
void SetLinearGradientBlurImpl(Ark_NativePointer node,
                               const Opt_Number* value,
                               const Opt_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetLinearGradientBlur(frameNode, convValue);
}
void SetSystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //CommonMethodModelNG::SetSetSystemBarEffect(frameNode, convValue);
}
void SetUseEffect1Impl(Ark_NativePointer node,
                       const Opt_Boolean* useEffect,
                       const Opt_EffectType* effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(useEffect);
    //auto convValue = Converter::OptConvert<type>(useEffect); // for enums
    //CommonMethodModelNG::SetSetUseEffect1(frameNode, convValue);
}
void SetBackdropBlurImpl(Ark_NativePointer node,
                         const Opt_Number* radius,
                         const Opt_BlurOptions* options,
                         const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(radius);
    //auto convValue = Converter::OptConvert<type>(radius); // for enums
    //CommonMethodModelNG::SetSetBackdropBlur(frameNode, convValue);
}
void SetSharedTransitionImpl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetSharedTransition(frameNode, convValue);
}
void SetChainModeImpl(Ark_NativePointer node,
                      const Opt_Axis* direction,
                      const Opt_ChainStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //CommonMethodModelNG::SetSetChainMode(frameNode, convValue);
}
void SetOnDrop1Impl(Ark_NativePointer node,
                    const Opt_OnDragEventCallback* eventCallback,
                    const Opt_DropOptions* dropOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(eventCallback);
    //auto convValue = Converter::OptConvert<type>(eventCallback); // for enums
    //CommonMethodModelNG::SetSetOnDrop1(frameNode, convValue);
}
void SetDragPreview1Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                         const Opt_PreviewConfiguration* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(preview);
    //auto convValue = Converter::OptConvert<type>(preview); // for enums
    //CommonMethodModelNG::SetSetDragPreview1(frameNode, convValue);
}
void SetDragPreviewOptionsImpl(Ark_NativePointer node,
                               const Opt_DragPreviewOptions* value,
                               const Opt_DragInteractionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto previewOption = Converter::OptConvertPtr<DragPreviewOption>(value);
    if (!previewOption) {
        // TODO: Reset value
        return;
    }
    auto optionsOpt = Converter::OptConvertPtr<Ark_DragInteractionOptions>(options);
    if (optionsOpt) {
        auto defaultAnimationBeforeLifting = Converter::OptConvert<Ark_Boolean>(
            optionsOpt.value().defaultAnimationBeforeLifting);
        if (defaultAnimationBeforeLifting) {
            previewOption->defaultAnimationBeforeLifting = defaultAnimationBeforeLifting.value();
        }
        auto isMultiSelectionEnabled = Converter::OptConvert<Ark_Boolean>(
            optionsOpt.value().isMultiSelectionEnabled);
        if (isMultiSelectionEnabled) {
            previewOption->isMultiSelectionEnabled = isMultiSelectionEnabled.value();
        }
        auto enableEdgeAutoScroll = Converter::OptConvert<Ark_Boolean>(
            optionsOpt.value().enableEdgeAutoScroll);
        if (enableEdgeAutoScroll) {
            previewOption->enableEdgeAutoScroll = enableEdgeAutoScroll.value();
        }
        auto enableHapticFeedback = Converter::OptConvert<Ark_Boolean>(
            optionsOpt.value().enableHapticFeedback);
        if (enableHapticFeedback) {
            previewOption->enableHapticFeedback = enableHapticFeedback.value();
        }
        auto isLiftingDisabled = Converter::OptConvert<Ark_Boolean>(
            optionsOpt.value().isLiftingDisabled);
        if (isLiftingDisabled) {
            previewOption->isLiftingDisabled = isLiftingDisabled.value();
        }
    }
    LOGE("CommonMethodModifier::DragPreviewOptionsImpl Ark_ImageModifier is not supported yet.");
    ViewAbstract::SetDragPreviewOptions(frameNode, *previewOption);
}
void SetOverlayImpl(Ark_NativePointer node,
                    const Opt_Union_String_CustomBuilder_ComponentContent* value,
                    const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetOverlay(frameNode, convValue);
}
void SetBlendModeImpl(Ark_NativePointer node,
                      const Opt_BlendMode* value,
                      const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetBlendMode(frameNode, convValue);
}
void SetAdvancedBlendModeImpl(Ark_NativePointer node,
                              const Opt_Union_BlendMode_Blender* effect,
                              const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetSetAdvancedBlendMode(frameNode, convValue);
}
void SetGeometryTransition1Impl(Ark_NativePointer node,
                                const Opt_String* id,
                                const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetGeometryTransition1(frameNode, convValue);
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
        [] () {
            return;
        });
}
void SetBindPopupImpl(Ark_NativePointer node,
                      const Opt_Boolean* show,
                      const Opt_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(show);
    //auto convValue = Converter::OptConvert<type>(show); // for enums
    //CommonMethodModelNG::SetSetBindPopup(frameNode, convValue);
}
void SetBindMenu0Impl(Ark_NativePointer node,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetSetBindMenu0(frameNode, convValue);
}
void SetBindMenu1Impl(Ark_NativePointer node,
                      const Opt_Boolean* isShow,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(content);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto type = Converter::OptConvertPtr<ResponseType>(responseType).value_or(ResponseType::LONG_PRESS);
    auto contentBuilder = [callback = CallbackHelper(*optValue), node, frameNode, type](
                              MenuParam menuParam, std::function<void()>&& previewBuildFunc) {
        auto builder = [node, frameNode, callback]() {
            auto uiNode = callback.BuildSync(node);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        ViewAbstractModelStatic::BindContextMenuStatic(
            AceType::Claim(frameNode), type, std::move(builder), menuParam, std::move(previewBuildFunc));
        ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(frameNode, menuParam);
    };
    menuParam.previewMode = MenuPreviewMode::NONE;
    auto menuOption = Converter::GetOptPtr(options);
    g_bindContextMenuParams(menuParam, menuOption, node, frameNode);
    if (type != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.isShowHoverImage = false;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    Converter::VisitUnion(menuOption->preview,
        [&menuParam, menuOption, contentBuilder](const Ark_MenuPreviewMode& value) {
            auto mode = Converter::OptConvert<MenuPreviewMode>(value);
            if (mode && mode.value() == MenuPreviewMode::IMAGE) {
                menuParam.previewMode = MenuPreviewMode::IMAGE;
            }
            std::function<void()> previewBuildFunc = nullptr;
            contentBuilder(menuParam, std::move(previewBuildFunc));
        },
        [&menuParam, menuOption, node, frameNode, &contentBuilder](const CustomNodeBuilder& value) {
            menuParam.previewMode = MenuPreviewMode::CUSTOM;
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
void BindContextMenu0Impl(Ark_NativePointer node,
                          const Opt_CustomNodeBuilder* content,
                          const Opt_ResponseType* responseType,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetSetBindContextMenu0(frameNode, convValue);
}
void SetBindContextMenu1Impl(Ark_NativePointer node,
                             const Opt_Boolean* isShown,
                             const Opt_CustomNodeBuilder* content,
                             const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShown);
    //auto convValue = Converter::OptConvert<type>(isShown); // for enums
    //CommonMethodModelNG::SetSetBindContextMenu1(frameNode, convValue);
}
void SetBindContentCover0Impl(Ark_NativePointer node,
                              const Opt_Boolean* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindContentCover0(frameNode, convValue);
}
void SetBindContentCover1Impl(Ark_NativePointer node,
                              const Opt_Boolean* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ContentCoverOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindContentCover1(frameNode, convValue);
}
void SetBindSheetImpl(Ark_NativePointer node,
                      const Opt_Boolean* isShow,
                      const Opt_CustomNodeBuilder* builder,
                      const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindSheet(frameNode, convValue);
}
void SetOnVisibleAreaChangeImpl(Ark_NativePointer node,
                                const Opt_Array_Number* ratios,
                                const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(ratios);
    //auto convValue = Converter::OptConvert<type>(ratios); // for enums
    //CommonMethodModelNG::SetSetOnVisibleAreaChange(frameNode, convValue);
}
void SetOnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                           const Opt_VisibleAreaEventOptions* options,
                                           const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(options);
    //auto convValue = Converter::OptConvert<type>(options); // for enums
    //CommonMethodModelNG::SetSetOnVisibleAreaApproximateChange(frameNode, convValue);
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
        // TODO: Reset value
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
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::ConstructImpl,
        CommonMethodModifier::SetWidthImpl,
        CommonMethodModifier::SetHeightImpl,
        CommonMethodModifier::SetDrawModifierImpl,
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
        CommonMethodModifier::SetAlignRules0Impl,
        CommonMethodModifier::SetAlignRules1Impl,
        CommonMethodModifier::SetAspectRatioImpl,
        CommonMethodModifier::SetClickEffectImpl,
        CommonMethodModifier::SetOnDragStartImpl,
        CommonMethodModifier::SetOnDragEnterImpl,
        CommonMethodModifier::SetOnDragMoveImpl,
        CommonMethodModifier::SetOnDragLeaveImpl,
        CommonMethodModifier::SetOnDrop0Impl,
        CommonMethodModifier::SetOnDragEndImpl,
        CommonMethodModifier::SetAllowDropImpl,
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
        CommonMethodModifier::SetStateStylesImpl,
        CommonMethodModifier::SetRestoreIdImpl,
        CommonMethodModifier::SetSphericalEffectImpl,
        CommonMethodModifier::SetLightUpEffectImpl,
        CommonMethodModifier::SetPixelStretchEffectImpl,
        CommonMethodModifier::SetAccessibilityGroup0Impl,
        CommonMethodModifier::SetAccessibilityText0Impl,
        CommonMethodModifier::SetAccessibilityNextFocusIdImpl,
        CommonMethodModifier::SetAccessibilityDefaultFocusImpl,
        CommonMethodModifier::SetAccessibilityUseSamePageImpl,
        CommonMethodModifier::SetAccessibilityScrollTriggerableImpl,
        CommonMethodModifier::SetAccessibilityText1Impl,
        CommonMethodModifier::SetAccessibilityRoleImpl,
        CommonMethodModifier::SetOnAccessibilityFocusImpl,
        CommonMethodModifier::SetAccessibilityTextHintImpl,
        CommonMethodModifier::SetAccessibilityDescription0Impl,
        CommonMethodModifier::SetAccessibilityDescription1Impl,
        CommonMethodModifier::SetAccessibilityLevelImpl,
        CommonMethodModifier::SetAccessibilityVirtualNodeImpl,
        CommonMethodModifier::SetAccessibilityCheckedImpl,
        CommonMethodModifier::SetAccessibilitySelectedImpl,
        CommonMethodModifier::SetObscuredImpl,
        CommonMethodModifier::SetReuseIdImpl,
        CommonMethodModifier::SetReuseImpl,
        CommonMethodModifier::SetRenderFitImpl,
        CommonMethodModifier::SetGestureModifierImpl,
        CommonMethodModifier::SetBackgroundBrightnessImpl,
        CommonMethodModifier::SetOnGestureJudgeBeginImpl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::SetShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::SetMonopolizeEventsImpl,
        CommonMethodModifier::SetOnTouchInterceptImpl,
        CommonMethodModifier::SetOnSizeChangeImpl,
        CommonMethodModifier::SetAccessibilityFocusDrawLevelImpl,
        CommonMethodModifier::SetCustomPropertyImpl,
        CommonMethodModifier::SetExpandSafeAreaImpl,
        CommonMethodModifier::SetBackgroundImpl,
        CommonMethodModifier::SetBackgroundImage0Impl,
        CommonMethodModifier::SetBackgroundImage1Impl,
        CommonMethodModifier::SetBackgroundBlurStyleImpl,
        CommonMethodModifier::SetBackgroundEffect1Impl,
        CommonMethodModifier::SetForegroundBlurStyleImpl,
        CommonMethodModifier::SetOnClick1Impl,
        CommonMethodModifier::SetFocusScopeIdImpl,
        CommonMethodModifier::SetFocusScopePriorityImpl,
        CommonMethodModifier::SetTransition1Impl,
        CommonMethodModifier::SetGestureImpl,
        CommonMethodModifier::SetPriorityGestureImpl,
        CommonMethodModifier::SetParallelGestureImpl,
        CommonMethodModifier::SetBlurImpl,
        CommonMethodModifier::SetLinearGradientBlurImpl,
        CommonMethodModifier::SetSystemBarEffectImpl,
        CommonMethodModifier::SetUseEffect1Impl,
        CommonMethodModifier::SetBackdropBlurImpl,
        CommonMethodModifier::SetSharedTransitionImpl,
        CommonMethodModifier::SetChainModeImpl,
        CommonMethodModifier::SetOnDrop1Impl,
        CommonMethodModifier::SetDragPreview1Impl,
        CommonMethodModifier::SetDragPreviewOptionsImpl,
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
        CommonMethodModifier::SetAccessibilityGroup1Impl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin1Impl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
