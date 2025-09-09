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

#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
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
#include "core/interfaces/native/implementation/pan_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pinch_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/progress_mask_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
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

struct SheetCallbacks {
    std::function<void()> onAppear;
    std::function<void()> onDisappear;
    std::function<void()> onWillAppear;
    std::function<void()> onWillDisappear;
    std::function<void()> shouldDismiss;
    std::function<void(const int32_t)> onWillDismiss;
    std::function<void(const float)> onHeightDidChange;
    std::function<void(const float)> onDetentsDidChange;
    std::function<void(const float)> onWidthDidChange;
    std::function<void(const float)> onTypeDidChange;
    std::function<void()> titleBuilder;
    std::function<void()> sheetSpringBack;
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
    }
    auto popupBackgroundBlurStyleOpt = Converter::OptConvert<BlurStyle>(src.backgroundBlurStyle);
    if (popupBackgroundBlurStyleOpt.has_value()) {
        popupParam->SetBlurStyle(popupBackgroundBlurStyleOpt.value());
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

auto g_contentCoverCallbacks = [](WeakPtr<FrameNode> weakNode, const Ark_ContentCoverOptions& options,
    std::function<void()>& onShowCallback, std::function<void()>& onDismissCallback,
    std::function<void()>& onWillShowCallback, std::function<void()>& onWillDismissCallback,
    std::function<void(const int32_t& info)>& onWillDismissFunc) {
    auto onAppearValue = OptConvert<Callback_Void>(options.onAppear);
    if (onAppearValue) {
        onShowCallback = [arkCallback = CallbackHelper(onAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
    }
    auto onDisappearValue = OptConvert<Callback_Void>(options.onDisappear);
    if (onDisappearValue) {
        onDismissCallback = [arkCallback = CallbackHelper(onDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
    }
    auto onWillAppearValue = OptConvert<Callback_Void>(options.onWillAppear);
    if (onWillAppearValue) {
        onWillShowCallback = [arkCallback = CallbackHelper(onWillAppearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
    }
    auto onWillDisappearValue = OptConvert<Callback_Void>(options.onWillDisappear);
    if (onWillDisappearValue) {
        onWillDismissCallback = [arkCallback = CallbackHelper(onWillDisappearValue.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
    }
    auto onWillDismissValue = OptConvert<Callback_DismissContentCoverAction_Void>(options.onWillDismiss);
    if (onWillDismissValue) {
        onWillDismissFunc = [arkCallback = CallbackHelper(onWillDismissValue.value()), weakNode](int32_t reason) {
        };
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
    // menuParam.enableHoverMode = OptConvert<bool>(menuOptions.enableHoverMode).value_or(menuParam.enableHoverMode);
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
    menuParam.layoutRegionMargin = OptConvert<PaddingProperty>(menuOptions.layoutRegionMargin);
};

auto g_bindContextMenuParams = [](MenuParam& menuParam, const std::optional<Ark_ContextMenuOptions>& menuOption,
    Ark_NativePointer node, FrameNode* frameNode) {
    CHECK_NULL_VOID(menuOption);
    menuParam.placement = Placement::BOTTOM_LEFT;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    auto weakNode = AceType::WeakClaim(frameNode);
    // g_bindMenuOptionsParam(menuOption.value(), menuParam, weakNode);
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
}

auto g_bindSheetCallbacks1 = [](SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions) {
    auto onAppear = Converter::OptConvert<Callback_Void>(sheetOptions.onAppear);
    if (onAppear) {
        callbacks.onAppear = [arkCallback = CallbackHelper(onAppear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto onDisappear = Converter::OptConvert<Callback_Void>(sheetOptions.onDisappear);
    if (onDisappear) {
        callbacks.onDisappear = [arkCallback = CallbackHelper(onDisappear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto onWillAppear = Converter::OptConvert<Callback_Void>(sheetOptions.onWillAppear);
    if (onWillAppear) {
        callbacks.onWillAppear = [arkCallback = CallbackHelper(onWillAppear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto onWillDisappear = Converter::OptConvert<Callback_Void>(sheetOptions.onWillDisappear);
    if (onWillDisappear) {
        callbacks.onWillDisappear = [arkCallback = CallbackHelper(onWillDisappear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto shouldDismiss = Converter::OptConvert<Callback_SheetDismiss_Void>(sheetOptions.shouldDismiss);
    if (shouldDismiss) {
        callbacks.shouldDismiss = [arkCallback = CallbackHelper(shouldDismiss.value())]() {
        };
    }
    auto onTypeDidChange = Converter::OptConvert<Callback_SheetType_Void>(sheetOptions.onTypeDidChange);
    if (onTypeDidChange) {
        callbacks.onTypeDidChange = [arkCallback = CallbackHelper(onTypeDidChange.value())](int32_t value) {
            arkCallback.Invoke(Converter::ArkValue<Ark_SheetType>(static_cast<SheetType>(value)));
        };
    }
};

auto g_bindSheetCallbacks2 = [](SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions) {
    auto onWillDismiss = Converter::OptConvert<Callback_DismissSheetAction_Void>(sheetOptions.onWillDismiss);
    if (onWillDismiss) {
        callbacks.onWillDismiss = [arkCallback = CallbackHelper(onWillDismiss.value())](const int32_t reason) {
        };
    }
    auto onWillSpringBackWhenDismiss = Converter::OptConvert<Callback_SpringBackAction_Void>(
        sheetOptions.onWillSpringBackWhenDismiss);
    if (onWillSpringBackWhenDismiss) {
        callbacks.sheetSpringBack = [arkCallback = CallbackHelper(onWillSpringBackWhenDismiss.value())]() {
        };
    }
    auto onHeightDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onHeightDidChange);
    if (onHeightDidChange) {
        callbacks.onHeightDidChange = [arkCallback = CallbackHelper(onHeightDidChange.value())](int32_t value) {
            arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
        };
    }
    auto onWidthDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onWidthDidChange);
    if (onWidthDidChange) {
        callbacks.onWidthDidChange = [arkCallback = CallbackHelper(onWidthDidChange.value())](int32_t value) {
            arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
        };
    }
    auto onDetentsDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onDetentsDidChange);
    if (onDetentsDidChange) {
        callbacks.onDetentsDidChange = [arkCallback = CallbackHelper(onDetentsDidChange.value())](
            int32_t value) {
            arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
        };
    }
};

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
BorderWidthProperty Convert(const Ark_EdgeOutlineWidths& src)
{
    BorderWidthProperty dst;
    dst.leftDimen = OptConvert<Dimension>(src.left);
    Validator::ValidateNonNegative(dst.leftDimen);
    dst.topDimen = OptConvert<Dimension>(src.top);
    Validator::ValidateNonNegative(dst.topDimen);
    dst.rightDimen = OptConvert<Dimension>(src.right);
    Validator::ValidateNonNegative(dst.rightDimen);
    dst.bottomDimen = OptConvert<Dimension>(src.bottom);
    Validator::ValidateNonNegative(dst.bottomDimen);
    dst.multiValued = true;
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
AlignRule Convert(const Ark_HorizontalAlignParam& src)
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
AlignRule Convert(const Ark_VerticalAlignParam& src)
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
void AssignArkValue(Ark_GestureInfo &dst, const GestureInfo &src)
{
    auto tagOpt = src.GetTag();
    dst.tag = ArkValue<Opt_String>(tagOpt);
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
    dst.globalX = ArkValue<Ark_Number>(src.globalLocation_.GetX());
    dst.globalY = ArkValue<Ark_Number>(src.globalLocation_.GetY());
    dst.localX = ArkValue<Ark_Number>(src.localLocation_.GetX());
    dst.localY = ArkValue<Ark_Number>(src.localLocation_.GetY());
    dst.displayX = ArkValue<Ark_Number>(src.screenLocation_.GetX());
    dst.displayY = ArkValue<Ark_Number>(src.screenLocation_.GetY());
}

template<>
template<>
ArkArrayHolder<Array_FingerInfo>::ArkArrayHolder(const std::list<FingerInfo>& data)
{
    std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const FingerInfo& src) {
        return OHOS::Ace::NG::Converter::ArkValue<Ark_FingerInfo>(src);
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
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;

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
void Width0Impl(Ark_NativePointer node,
                const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<CalcDimension>(value);
    Validator::ValidateNonNegative(result);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (!result) {
            // TODO: Reset value
            return;
        }
        CounterModelNG::SetWidth(frameNode, *result);
    } else {
        if (!result) {
            return;
        }
        ViewAbstractModelStatic::SetWidth(frameNode, *result);
    }
}
void Width1Impl(Ark_NativePointer node,
                const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Height0Impl(Ark_NativePointer node,
                 const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<CalcDimension>(value);
    Validator::ValidateNonNegative(result);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (!result) {
            // TODO: Reset value
            return;
        }
        CounterModelNG::SetHeight(frameNode, *result);
    } else {
        if (!result) {
            return;
        }
        ViewAbstractModelStatic::SetHeight(frameNode, *result);
    }
}
void Height1Impl(Ark_NativePointer node,
                 const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DrawModifierImpl(Ark_NativePointer node,
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
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (auto convArray = Converter::OptConvertPtr<std::vector<DimensionRect>>(value); convArray) {
    } else {
    }
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (auto convArray = Converter::OptConvertPtr<std::vector<DimensionRect>>(value); convArray) {
    } else {
    }
}
void SizeImpl(Ark_NativePointer node,
              const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    Width0Impl(node, &optValue->width);
    Height0Impl(node, &optValue->height);
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto minWidth = Converter::OptConvert<CalcDimension>(optValue->minWidth);
    if (minWidth) {
        ViewAbstractModelStatic::SetMinWidth(frameNode, minWidth.value());
    }
    auto minHeight = Converter::OptConvert<CalcDimension>(optValue->minHeight);
    if (minHeight) {
        ViewAbstractModelStatic::SetMinHeight(frameNode, minHeight.value());
    }
    auto maxWidth = Converter::OptConvert<CalcDimension>(optValue->maxWidth);
    if (maxWidth) {
        ViewAbstractModelStatic::SetMaxWidth(frameNode, maxWidth.value());
    }
    auto maxHeight = Converter::OptConvert<CalcDimension>(optValue->maxHeight);
    if (maxHeight) {
        ViewAbstractModelStatic::SetMaxHeight(frameNode, maxHeight.value());
    }
}
void TouchableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         const Opt_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<NG::HitTestMode>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void OnChildTouchTestImpl(Ark_NativePointer node,
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

        Converter::ArkArrayHolder<Array_TouchTestInfo> holder(touchInfoUpd);
        auto resultOpt =
            callback.InvokeWithOptConvertResult<NG::TouchResult, Ark_TouchResult, Callback_TouchResult_Void>(
                holder.ArkValue()
        );
        static const NG::TouchResult defaultRes{ NG::TouchTestStrategy::DEFAULT, "" };
        return resultOpt.value_or(defaultRes);
    };
    ViewAbstractModelStatic::SetOnTouchTestFunc(frameNode, std::move(onTouchTestFunc));
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto weight = Converter::OptConvertPtr<float>(value);
    if (weight) {
        ViewAbstractModelStatic::SetLayoutWeight(frameNode, weight.value());
    }
}
void ChainWeightImpl(Ark_NativePointer node,
                     const Opt_ChainWeightOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto chainWeight = Converter::OptConvertPtr<ChainWeightPair>(value).value_or(ChainWeightPair{});
    ViewAbstractModelStatic::SetChainWeight(frameNode, chainWeight);
}
void PaddingImpl(Ark_NativePointer node,
                 const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetPadding(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
}
void SafeAreaPaddingImpl(Ark_NativePointer node,
                         const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_Padding& value) {
            auto convValue = Converter::Convert<PaddingProperty>(value);
        },
        [frameNode](const Ark_LocalizedPadding& value) {
             LOGE("ARKOALA: CommonMethod::SafeAreaPaddingImpl: Ark_LocalizedPadding is not supported.\n");
            auto convValue = Converter::Convert<PaddingProperty>(value);
        },
        [frameNode](const Ark_LengthMetrics& value) {
            auto convValue = Converter::Convert<CalcLength>(value);
        },
        []() {}
    );
}
void MarginImpl(Ark_NativePointer node,
                const Opt_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetMargin(frameNode, Converter::OptConvertPtr<PaddingProperty>(value));
}
void BackgroundColor0Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void BackgroundColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Opt_PixelRoundPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<uint16_t>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ViewAbstractModelStatic::SetPixelRound(frameNode, *convValue);
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Opt_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Opt_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto varValue = Converter::OptConvertPtr<BackgroundImagePositionType>(value);
    BackgroundImagePosition bgImgPosition;
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    if (varValue) {
        if (auto arkPosition = std::get_if<Ark_Position>(&varValue.value()); arkPosition) {
            auto position =
                Converter::Convert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(*arkPosition);
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
        } else if (auto arkAlign = std::get_if<Ark_Alignment>(&varValue.value()); arkAlign) {
            auto alignment = Converter::OptConvertPtr<std::pair<double, double>>(arkAlign);
            if (alignment) {
                bgImgPosition.SetIsAlign(true);
                typeX = DimensionUnit::PERCENT;
                typeY = DimensionUnit::PERCENT;
                valueX = alignment.value().first;
                valueY = alignment.value().second;
            }
        }
    }
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
}
void BackgroundEffect0Impl(Ark_NativePointer node,
                           const Opt_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<EffectOption>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void BackgroundEffect1Impl(Ark_NativePointer node,
                           const Opt_BackgroundEffectOptions* options,
                           const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    ImageResizableSlice convValue {};
    convValue = Converter::OptConvert<ImageResizableSlice>(optValue->slice).value_or(convValue);
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Opt_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    ViewAbstractModelStatic::SetForegroundEffect(frameNode, convValue);
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Opt_VisualEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Opt_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Opt_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Opt_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Opacity0Impl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<float>(value);
    if (result) {
        // TODO: Reset value
    }
}
void Opacity1Impl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BorderImpl(Ark_NativePointer node,
                const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto style = Converter::OptConvert<BorderStyleProperty>(optValue->style);
    if (style) {
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
    auto width = Converter::OptConvert<BorderWidthProperty>(optValue->width);
    if (width) {
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
    auto color = Converter::OptConvert<BorderColorProperty>(optValue->color);
    if (color) {
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
    auto radius = Converter::OptConvert<BorderRadiusProperty>(optValue->radius);
    if (radius) {
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radius.value());
    }
    auto dashGap = Converter::OptConvert<BorderWidthProperty>(optValue->dashGap);
    if (dashGap) {
        ViewAbstractModelStatic::SetDashGap(frameNode, dashGap.value());
    }
    auto dashWidth = Converter::OptConvert<BorderWidthProperty>(optValue->dashWidth);
    if (dashWidth) {
        ViewAbstractModelStatic::SetDashWidth(frameNode, dashWidth.value());
    }
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<BorderStyleProperty>(value);
    if (style) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetBorderStyle(frameNode, style.value());
    }
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvertPtr<BorderWidthProperty>(value);
    if (width) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetBorderWidth(frameNode, width.value());
    }
}
void BorderColorImpl(Ark_NativePointer node,
                     const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<BorderColorProperty>(value);
    if (color) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetBorderColor(frameNode, color.value());
    }
}
void BorderRadiusImpl(Ark_NativePointer node,
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
        ViewAbstractModelStatic::SetBorderRadius(frameNode, radiuses.value());
    }
}
void BorderImageImpl(Ark_NativePointer node,
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
}
void OutlineStyle0Impl(Ark_NativePointer node,
                       const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderStylesOpt = Converter::OptConvertPtr<BorderStyleProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void OutlineStyle1Impl(Ark_NativePointer node,
                       const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OutlineWidth0Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderWidthOpt = Converter::OptConvertPtr<BorderWidthProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));
}
void OutlineWidth1Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OutlineColor0Impl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderColorsOpt = Converter::OptConvertPtr<BorderColorProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));
}
void OutlineColor1Impl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OutlineRadius0Impl(Ark_NativePointer node,
                        const Opt_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderRadiusOpt = Converter::OptConvertPtr<BorderRadiusProperty>(value);
    ViewAbstractModelStatic::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));
}
void OutlineRadius1Impl(Ark_NativePointer node,
                        const Opt_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ForegroundColor0Impl(Ark_NativePointer node,
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
void ForegroundColor1Impl(Ark_NativePointer node,
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
void OnClick0Impl(Ark_NativePointer node,
                  const Opt_Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnClick(frameNode);
        return;
    }
    auto onClick = [callback = CallbackHelper(*optValue)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    ViewAbstract::SetOnClick(frameNode, std::move(onClick));
}
void OnClick1Impl(Ark_NativePointer node,
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

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(static_cast<UINode *>(node), std::move(onEvent));
    } else {
        if (!convValue) {
            ViewAbstract::DisableOnClick(frameNode);
            return;
        }
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent), *convValue);
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 const Opt_Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void OnHoverMoveImpl(Ark_NativePointer node,
                     const Opt_Callback_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              const Opt_AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ViewAbstract::DisableOnAccessibilityHover(frameNode);
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
    ViewAbstract::SetOnAccessibilityHover(frameNode, std::move(onAccessibilityHover));
}
void HoverEffectImpl(Ark_NativePointer node,
                     const Opt_HoverEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto hoverEffect = Converter::OptConvertPtr<OHOS::Ace::HoverEffectType>(value);
    // TODO: Reset value
    if (hoverEffect) {
    }
}
void OnMouseImpl(Ark_NativePointer node,
                 const Opt_Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void OnTouchImpl(Ark_NativePointer node,
                 const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](TouchEventInfo& info) {
        const auto event = Converter::ArkTouchEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEvent0Impl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    } else {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
            PipelineContext::SetCallBackNode(node);
            const auto event = Converter::ArkKeyEventSync(info);
            arkCallback.InvokeSync(event.ArkValue());
            return false;
        };
    }
}
void OnKeyEvent1Impl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    } else {
        auto weakNode = AceType::WeakClaim(frameNode);
        auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
            PipelineContext::SetCallBackNode(node);
            const auto event = Converter::ArkKeyEventSync(info);
            auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
            return Converter::Convert<bool>(arkResult);
        };
    }
}
void OnDigitalCrownImpl(Ark_NativePointer node,
                        const Opt_Callback_CrownEvent_Void* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode*>(node);
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
                .timestamp = ArkValue<Ark_Int64>(info.GetTimeStamp().time_since_epoch().count()),
                .angularVelocity = ArkValue<Ark_Number>(info.GetAngularVelocity()),
                .degree = ArkValue<Ark_Number>(info.GetDegree()),
                .action = ArkValue<Ark_CrownAction>(info.GetAction()),
                .stopPropagation = stopPropagation,
            };
            callback.Invoke(crownEvent);
        };
    } else {
    }
#endif
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
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
    }
}
void OnKeyEventDispatchImpl(Ark_NativePointer node,
                            const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onKeyEvent = [arkCallback = CallbackHelper(*optValue), node = weakNode](KeyEventInfo& info) -> bool {
        PipelineContext::SetCallBackNode(node);
        const auto event = Converter::ArkKeyEventSync(info);
        auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
        return Converter::Convert<bool>(arkResult);
    };
}
void OnFocusAxisEventImpl(Ark_NativePointer node,
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
void OnAxisEventImpl(Ark_NativePointer node,
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
void FocusableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void NextFocusImpl(Ark_NativePointer node,
                   const Opt_FocusMovement* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto arkFocusMovement = Converter::OptConvertPtr<Ark_FocusMovement>(value);
    if (!arkFocusMovement) {
        return;
    }
    auto forward = Converter::OptConvert<std::string>(arkFocusMovement->forward);
    if (forward.has_value()) {
    }

    auto backward = Converter::OptConvert<std::string>(arkFocusMovement->backward);
    if (backward.has_value()) {
    }

    auto up = Converter::OptConvert<std::string>(arkFocusMovement->up);
    if (up.has_value()) {
    }

    auto down = Converter::OptConvert<std::string>(arkFocusMovement->down);
    if (down.has_value()) {
    }

    auto left = Converter::OptConvert<std::string>(arkFocusMovement->left);
    if (left.has_value()) {
    }

    auto right = Converter::OptConvert<std::string>(arkFocusMovement->right);
    if (right.has_value()) {
    }
}
void TabStopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void OnFocusImpl(Ark_NativePointer node,
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
void OnBlurImpl(Ark_NativePointer node,
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
void TabIndexImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void DefaultFocusImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Opt_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<NG::FocusBoxStyle>(value);
    ViewAbstractModelStatic::SetFocusBoxStyle(frameNode, convValue);
}
void AnimationImpl(Ark_NativePointer node,
                   const Opt_AnimateParam* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->IsFirstBuilding()) {
        // the node sets attribute value for the first time. No animation is generated.
        return;
    }

    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }

    auto optOption = Converter::OptConvertPtr<AnimationOption>(value);
    if (optOption) {
        auto option = *optOption;
        Validator::ValidateAnimationOption(option, pipelineContextBase->IsFormRender());

        if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
            option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
            option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
            TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
                static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
        }

        LOGI("ARKOALA CommonMethod::AnimationImpl: onFinish callback don`t supported yet");
        // we need to support onFinish callback and set it to options:

        if (SystemProperties::GetRosenBackendEnabled()) {
            option.SetAllowRunningAsynchronously(true);
        }
        // ViewContextModelNG::openAnimationInternal(option);
    } else {
        // AnimationOption option = AnimationOption();
        // ViewContextModelNG::closeAnimationInternal(option, true);
    }
}
void Transition0Impl(Ark_NativePointer node,
                     const Opt_Union_TransitionOptions_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_TransitionOptions& value) {
            auto convValue = Converter::Convert<TransitionOptions>(value);
        },
        [frameNode](const Ark_TransitionEffect& value) {
            auto convValue = Converter::Convert<RefPtr<NG::ChainedTransitionEffect>>(value);
        },
        []() {}
    );
}
void Transition1Impl(Ark_NativePointer node,
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
        // TODO: Reset value
        return;
    }
    auto effectPeer = *optValue;
    if (effectPeer && effectPeer->handler) {
    } else {
    }
}
void MotionBlur0Impl(Ark_NativePointer node,
                     const Opt_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<MotionBlurOption>(value);
}
void MotionBlur1Impl(Ark_NativePointer node,
                     const Opt_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvertPtr<MotionBlurOption>(value);
}
void Brightness0Impl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
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
void Brightness1Impl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}
void Contrast0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
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
void Contrast1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Grayscale0Impl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
}
void Grayscale1Impl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ColorBlend0Impl(Ark_NativePointer node,
                     const Opt_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
}
void ColorBlend1Impl(Ark_NativePointer node,
                     const Opt_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Saturate0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    if (!convValue.has_value()) {
        convValue = Dimension(1.0);
    } else {
        if (LessOrEqual(convValue.value().Value(), 0.0f)) {
            convValue.value().SetValue(0);
        }
    }
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetSaturate(frameNode, convValue.value());
}
void Saturate1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Sepia0Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
}
void Sepia1Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Invert0Impl(Ark_NativePointer node,
                 const Opt_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    const float minValue = 0.0;
    const float maxValue = 100.0;
    auto convValue = Converter::OptConvertPtr<InvertVariant>(value);
    Validator::ValidateByRange(convValue, minValue, maxValue);
}
void Invert1Impl(Ark_NativePointer node,
                 const Opt_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void HueRotate0Impl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
}
void HueRotate1Impl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void UseShadowBatching0Impl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
}
void UseShadowBatching1Impl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void UseEffect0Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
}
void UseEffect1Impl(Ark_NativePointer node,
                    const Opt_Boolean* useEffect,
                    const Opt_EffectType* effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void UseEffect2Impl(Ark_NativePointer node,
                    const Opt_Boolean* useEffect,
                    const Opt_EffectType* effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void RenderGroup0Impl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void RenderGroup1Impl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Freeze0Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
}
void Freeze1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Translate0Impl(Ark_NativePointer node,
                    const Opt_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TranslateOpt options = Converter::OptConvertPtr<TranslateOpt>(value).value_or(TranslateOpt{});

    CalcDimension x = options.x.value_or(CalcDimension(0.0));
    CalcDimension y = options.y.value_or(CalcDimension(0.0));
    CalcDimension z = options.z.value_or(CalcDimension(0.0));
}
void Translate1Impl(Ark_NativePointer node,
                    const Opt_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Scale0Impl(Ark_NativePointer node,
                const Opt_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScaleOpt scaleOptions = Converter::OptConvertPtr<ScaleOpt>(value).value_or(ScaleOpt{});

    float scaleX = scaleOptions.x.value_or(1.0f);
    float scaleY = scaleOptions.y.value_or(1.0f);

    CalcDimension centerX = scaleOptions.centerX.value_or(0.5_pct);
    CalcDimension centerY = scaleOptions.centerY.value_or(0.5_pct);
    ViewAbstractModelStatic::SetPivot(frameNode, DimensionOffset(centerX, centerY));
}
void Scale1Impl(Ark_NativePointer node,
                const Opt_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void GridSpanImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(convValue);
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(convValue);
}
void Rotate0Impl(Ark_NativePointer node,
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
            uint32_t indA = 3;
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
}
void Transform1Impl(Ark_NativePointer node,
                    const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Matrix4>(value);
    ViewAbstractModelStatic::SetTransformMatrix(frameNode, convValue);
}
void OnAppearImpl(Ark_NativePointer node,
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
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
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
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
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
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnAttach(frameNode, std::move(onAttach));
}
void OnDetachImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
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
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnDetach(frameNode, std::move(onDetach));
}
void OnAreaChangeImpl(Ark_NativePointer node,
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
        PipelineContext::SetCallBackNode(node);

        auto previousOffset = oldRect.GetOffset();
        Ark_Area previous;
        previous.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
        previous.height = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
        previous.position.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX()));
        previous.position.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY()));
        previous.globalPosition.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX() + oldOrigin.GetX()));
        previous.globalPosition.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY() + oldOrigin.GetY()));

        auto currentOffset = rect.GetOffset();
        Ark_Area current;
        current.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Width()));
        current.height = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Height()));
        current.position.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX()));
        current.position.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY()));
        current.globalPosition.x = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX() + origin.GetX()));
        current.globalPosition.y = Converter::ArkValue<Opt_Length>(
            PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY() + origin.GetY()));

        arkCallback.Invoke(previous, current);
    };

    auto areaChangeCallback = [areaChangeFunc = std::move(onEvent)](const RectF& oldRect,
                                  const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
            Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
            Offset(origin.GetX(), origin.GetY()));
    };
    ViewAbstract::SetOnAreaChanged(frameNode, std::move(areaChangeCallback));
}
void VisibilityImpl(Ark_NativePointer node,
                    const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<VisibleType>(value);
    if (!convValue.has_value()) {
        // TODO: Reset value
        return;
    }
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ViewAbstractModelStatic::SetFlexGrow(frameNode, *convValue);
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ViewAbstractModelStatic::SetFlexShrink(frameNode, *convValue);
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    ViewAbstractModelStatic::SetFlexBasis(frameNode, convValue);
}
void AlignSelfImpl(Ark_NativePointer node,
                   const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto align = Converter::OptConvertPtr<OHOS::Ace::FlexAlign>(value);
    if (align) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetAlignSelf(frameNode, align.value());
    }
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvertPtr<int>(value);
    if (result) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetDisplayIndex(frameNode, result.value());
    }
}
void ZIndexImpl(Ark_NativePointer node,
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
void DirectionImpl(Ark_NativePointer node,
                   const Opt_Direction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = Converter::OptConvertPtr<TextDirection>(value);
    if (direction) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetLayoutDirection(frameNode, direction.value());
    }
}
void AlignImpl(Ark_NativePointer node,
               const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto alignment = Converter::OptConvertPtr<Alignment>(value);
    if (alignment) {
        // TODO: Reset value
        ViewAbstractModelStatic::SetAlign(frameNode, alignment.value());
    }
}
void PositionImpl(Ark_NativePointer node,
                  const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void MarkAnchorImpl(Ark_NativePointer node,
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

void OffsetImpl(Ark_NativePointer node,
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
void EnabledImpl(Ark_NativePointer node,
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
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Opt_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto gridSizeOpt = Converter::OptConvert<GridSizeOpt>(optValue->xs);
    if (gridSizeOpt.has_value()) {
    }
    gridSizeOpt = Converter::OptConvert<GridSizeOpt>(optValue->sm);
    if (gridSizeOpt.has_value()) {
    }
    gridSizeOpt = Converter::OptConvert<GridSizeOpt>(optValue->md);
    if (gridSizeOpt.has_value()) {
    }
    gridSizeOpt= Converter::OptConvert<GridSizeOpt>(optValue->lg);
    if (gridSizeOpt.has_value()) {
    }
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Opt_AlignRuleOption* value)
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
void AlignRules1Impl(Ark_NativePointer node,
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
void AspectRatioImpl(Ark_NativePointer node,
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
void ClickEffect0Impl(Ark_NativePointer node,
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
void ClickEffect1Impl(Ark_NativePointer node,
                      const Opt_ClickEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnDragStartImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
        auto parseDragI = [&result](const Ark_DragItemInfo& value) {
            result.pixelMap = Converter::OptConvert<RefPtr<PixelMap>>(value.pixelMap).value_or(nullptr);
            result.extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string());
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
}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDragEnter = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                           const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Opt_Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDragMove = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                          const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDragLeave = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                           const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
}
void OnDrop0Impl(Ark_NativePointer node,
                 const Opt_Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDrop = [callback = CallbackHelper(*optValue)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
                                                      const std::string& extraParams) {
        CHECK_NULL_VOID(dragEvent);
        Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
        callback.InvokeSync(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    };
}
void OnDrop1Impl(Ark_NativePointer node,
                 const Opt_OnDragEventCallback* eventCallback,
                 const Opt_DropOptions* dropOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
}
void AllowDropImpl(Ark_NativePointer node,
                   const Opt_Array_UniformDataType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto allowDrop = Converter::OptConvertPtr<std::set<std::string>>(value);
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void DragPreview0Impl(Ark_NativePointer node,
                      const Opt_Union_CustomBuilder_DragItemInfo_String* value)
{
}
void DragPreview1Impl(Ark_NativePointer node,
                      const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                      const Opt_PreviewConfiguration* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnPreDragImpl(Ark_NativePointer node,
                   const Opt_Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onPreDrag = [callback = CallbackHelper(*optValue)](const PreDragStatus info) {
        callback.Invoke(Converter::ArkValue<Ark_PreDragStatus>(info));
    };
}
void LinearGradient0Impl(Ark_NativePointer node,
                         const Opt_LinearGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
}
void LinearGradient1Impl(Ark_NativePointer node,
                         const Opt_LinearGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SweepGradient0Impl(Ark_NativePointer node,
                        const Opt_SweepGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
}
void SweepGradient1Impl(Ark_NativePointer node,
                        const Opt_SweepGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void RadialGradient0Impl(Ark_NativePointer node,
                         const Opt_RadialGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Gradient>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void RadialGradient1Impl(Ark_NativePointer node,
                         const Opt_RadialGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MotionPathImpl(Ark_NativePointer node,
                    const Opt_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<MotionPathOption>(value);
}
void Shadow0Impl(Ark_NativePointer node,
                 const Opt_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadow = Converter::OptConvertPtr<Shadow>(value);
    if (shadow) {
        // TODO: Reset value
    }
}
void Shadow1Impl(Ark_NativePointer node,
                 const Opt_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Clip0Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetClipEdge(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void Clip1Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Clip2Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ClipShape0Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RefPtr<BasicShape>>(value);
    if (convValue.has_value() && convValue.value()) {
        // TODO: Reset value
    }
}
void ClipShape1Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Mask0Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto mask = Converter::OptConvertPtr<Ark_ProgressMask>(value);
    if (!mask) return;
    const auto& progressMask = mask.value()->GetProperty();
}
void Mask1Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Mask2Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MaskShape0Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RefPtr<BasicShape>>(value);
    if (convValue.has_value() && convValue.value()) {
        // TODO: Reset value
    }
}
void MaskShape1Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void KeyImpl(Ark_NativePointer node,
             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
}
void IdImpl(Ark_NativePointer node,
            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto id = Converter::OptConvertPtr<std::string>(value);
    if ((!id) || id->empty()) {
        // TODO: Reset value
        return;
    }
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto id = Converter::OptConvertPtr<std::string>(value).value_or("");
    bool followWithoutTransition {false};
    bool doRegisterSharedTransition {false};
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_EQUAL_VOID(id && options, false);
    auto idValue = Converter::OptConvertPtr<std::string>(id).value_or("");
    auto optOptions = Converter::OptConvertPtr<GeometryTransitionOptions>(options);
    auto followWithoutTransition {false};
    auto hierarchyStrategy = TransitionHierarchyStrategy::NONE;
    auto doRegisterSharedTransition {false};
    if (optOptions.has_value()) {
        followWithoutTransition = optOptions.value().follow.value_or(false);
        hierarchyStrategy = optOptions.value().hierarchyStrategy.value_or(TransitionHierarchyStrategy::NONE);
        doRegisterSharedTransition = hierarchyStrategy == TransitionHierarchyStrategy::ADAPTIVE;
    }
}
void StateStylesImpl(Ark_NativePointer node,
                     const Opt_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("Ark_StateStyles contains a CustomObject's which is not supported");
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void SphericalEffect0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    const float minValue = 0.0;
    const float maxValue = 1.0;
    Validator::ValidateByRange(convValue, minValue, maxValue);
}
void SphericalEffect1Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void LightUpEffect0Impl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
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
void LightUpEffect1Impl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void PixelStretchEffect0Impl(Ark_NativePointer node,
                             const Opt_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<PixStretchEffectOption>(value);
}
void PixelStretchEffect1Impl(Ark_NativePointer node,
                             const Opt_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void AccessibilityGroup0Impl(Ark_NativePointer node,
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
void AccessibilityGroup1Impl(Ark_NativePointer node,
                             const Opt_Boolean* isGroup,
                             const Opt_AccessibilityOptions* accessibilityOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isGroupValue = Converter::OptConvertPtr<bool>(isGroup);
    bool isGroupFlag = false;
    if (isGroupValue) {
        isGroupFlag = *isGroupValue;
    }
    auto optValue = Converter::GetOptPtr(accessibilityOptions);
    auto accessibilityPreferred = optValue ?
        Converter::OptConvert<bool>(optValue->accessibilityPreferred) : std::nullopt;
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, isGroupFlag);
    ViewAbstractModelNG::SetAccessibilityTextPreferred(frameNode, accessibilityPreferred.value_or(false));
}
void AccessibilityText0Impl(Ark_NativePointer node,
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
void AccessibilityText1Impl(Ark_NativePointer node,
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
void AccessibilityNextFocusIdImpl(Ark_NativePointer node,
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
void AccessibilityDefaultFocusImpl(Ark_NativePointer node,
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
    ViewAbstractModelNG::SetAccessibilityDefaultFocus(frameNode, isFocus);
}
void AccessibilityUseSamePageImpl(Ark_NativePointer node,
                                  const Opt_AccessibilitySamePageMode* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::OptConvertPtr<Ark_AccessibilitySamePageMode>(value);
    // if (!convValue) {
    //     return;
    // }
    // auto pageMode = AccessibilityUtils::GetPageModeType(convValue.value());
}
void AccessibilityScrollTriggerableImpl(Ark_NativePointer node,
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
void AccessibilityRoleImpl(Ark_NativePointer node,
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
    if (role.empty()) {
        resetValue = true;
    }
    ViewAbstractModelNG::SetAccessibilityRole(frameNode, role, resetValue);
}
void OnAccessibilityFocusImpl(Ark_NativePointer node,
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
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstractModelNG::SetAccessibilityTextHint(frameNode, *convValue);
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
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
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<std::string>(value);
    CHECK_EQUAL_VOID(optValue.has_value(), false);
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, optValue.value());
}
void AccessibilityLevelImpl(Ark_NativePointer node,
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
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
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
void AccessibilityCheckedImpl(Ark_NativePointer node,
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
void AccessibilitySelectedImpl(Ark_NativePointer node,
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
void ObscuredImpl(Ark_NativePointer node,
                  const Opt_Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::vector<std::optional<ObscuredReasons>>>(value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    auto vec = std::vector<ObscuredReasons>();
    for (auto reason : *convValue) {
        if (reason.has_value()) {
            vec.emplace_back(reason.value());
        }
    }
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA CommonMethod::ReuseIdImpl: Method not implemented in ViewAbstract!");
}
void ReuseImpl(Ark_NativePointer node,
               const Opt_ReuseOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void RenderFit0Impl(Ark_NativePointer node,
                    const Opt_RenderFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RenderFit>(value);
    ViewAbstractModelStatic::SetRenderFit(frameNode, convValue);
}
void RenderFit1Impl(Ark_NativePointer node,
                    const Opt_RenderFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<RenderFit>(value);
    ViewAbstractModelStatic::SetRenderFit(frameNode, convValue);
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Opt_GestureModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BackgroundBrightness0Impl(Ark_NativePointer node,
                               const Opt_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto rate = Converter::Convert<float>(optValue->rate);
    auto lightUpDegree = Converter::Convert<float>(optValue->lightUpDegree);
}
void BackgroundBrightness1Impl(Ark_NativePointer node,
                               const Opt_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
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
        auto arkGestEvent = Converter::ArkValue<Ark_BaseGestureEvent>(baseGestureInfo);
        auto resultOpt = callback.InvokeWithOptConvertResult
            <GestureJudgeResult, Ark_GestureJudgeResult, Callback_GestureJudgeResult_Void>(arkGestInfo, arkGestEvent);
        return resultOpt.value_or(defVal);
    };
    ViewAbstract::SetOnGestureJudgeBegin(frameNode, std::move(onGestureJudgefunc));
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const Opt_GestureRecognizerJudgeBeginCallback* callback,
                                        const Opt_Boolean *exposeInnerGesture);
void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                        const Opt_GestureRecognizerJudgeBeginCallback* value)
{
    auto exposeInnerGesture = Converter::ArkValue<Opt_Boolean>(false);
    OnGestureRecognizerJudgeBegin1Impl(node, value, &exposeInnerGesture);
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
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

        auto arkGestEvent = Converter::ArkValue<Ark_BaseGestureEvent>(info);
        auto arkValCurrent = Converter::ArkValue<Ark_GestureRecognizer>(current);
        Converter::ArkArrayHolder<Array_GestureRecognizer> holderOthers(others);
        auto arkValOthers = holderOthers.ArkValue();
        auto resultOpt = callback.InvokeWithOptConvertResult<GestureJudgeResult, Ark_GestureJudgeResult,
            Callback_GestureJudgeResult_Void>(arkGestEvent, arkValCurrent, arkValOthers);
        if (auto accessor = GetGestureRecognizerAccessor(); accessor) {
            accessor->destroyPeer(arkValCurrent);
            holderOthers.Release([accessor](Ark_GestureRecognizer& item) {
                accessor->destroyPeer(item);
            });
        }
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
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
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
        if (auto accessor = GetGestureRecognizerAccessor(); accessor) {
            accessor->destroyPeer(arkValCurrent);
            holderOthers.Release([accessor](Ark_GestureRecognizer& item) {
                accessor->destroyPeer(item);
            });
        }
        return resultOpt.value_or(nullptr);
    };
    ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, std::move(shouldBuiltInRecognizerParallelWithFunc));
}
void MonopolizeEventsImpl(Ark_NativePointer node,
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
void OnTouchInterceptImpl(Ark_NativePointer node,
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
void OnSizeChangeImpl(Ark_NativePointer node,
                      const Opt_SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSizeChange = [callback = CallbackHelper(*optValue)](const RectF &oldRect, const RectF &newRect) {
        Ark_SizeOptions oldSize;
        oldSize.width = Converter::ArkValue<Opt_Length>(oldRect.Width());
        oldSize.height = Converter::ArkValue<Opt_Length>(oldRect.Height());
        Ark_SizeOptions newSize;
        newSize.width = Converter::ArkValue<Opt_Length>(newRect.Width());
        newSize.height = Converter::ArkValue<Opt_Length>(newRect.Height());
        callback.Invoke(oldSize, newSize);
    };
}
void AccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                     const Opt_FocusDrawLevel* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    int32_t drawLevel = 0;
    auto convValue = Converter::OptConvertPtr<Ark_FocusDrawLevel>(value);
    if (convValue.has_value()) {
        if (drawLevel == -1) {
            drawLevel = 0;
        }
    }
    ViewAbstractModelNG::SetAccessibilityFocusDrawLevel(frameNode, drawLevel);
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Opt_String* name,
                        const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("CommonMethodModifier::CustomPropertyImpl is not implemented");
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
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
void BackgroundImpl(Ark_NativePointer node,
                    const Opt_CustomNodeBuilder* builder,
                    const Opt_Literal_Alignment_align* options)
{
}
void BackgroundImage0Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceStr_PixelMap* src,
                          const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvertPtr<ImageSourceInfo>(src);

    auto imageRepeat = Converter::OptConvertPtr<ImageRepeat>(repeat);
}
void BackgroundImage1Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceStr_PixelMap* src,
                          const Opt_BackgroundImageOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BackgroundBlurStyle0Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* value,
                              const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (auto opt = Converter::OptConvertPtr<BlurStyleOption>(options); opt) {
        convValue = *opt;
    }
    if (auto style = Converter::OptConvertPtr<BlurStyle>(value); style) {
        convValue.blurStyle = *style;
    }
}
void BackgroundBlurStyle1Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* style,
                              const Opt_BackgroundBlurStyleOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ForegroundBlurStyle0Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* value,
                              const Opt_ForegroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (auto opt = Converter::OptConvertPtr<BlurStyleOption>(options); opt) {
        convValue = *opt;
    }
    if (auto style = Converter::OptConvertPtr<BlurStyle>(value); style) {
        convValue.blurStyle = *style;
    }
}
void ForegroundBlurStyle1Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* style,
                              const Opt_ForegroundBlurStyleOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void FocusScopeId0Impl(Ark_NativePointer node,
                       const Opt_String* id,
                       const Opt_Boolean* isGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convIdValue = Converter::OptConvertPtr<std::string>(id);
    if (!convIdValue) {
        // TODO: Reset value
        return;
    }
    auto convIsGroupValue = Converter::OptConvertPtr<bool>(isGroup);
    ViewAbstractModelStatic::SetFocusScopeId(frameNode, *convIdValue, convIsGroupValue, std::nullopt);
}
void FocusScopeId1Impl(Ark_NativePointer node,
                       const Opt_String* id,
                       const Opt_Boolean* isGroup,
                       const Opt_Boolean* arrowStepOut)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convIdValue = Converter::OptConvertPtr<std::string>(id);
    if (!convIdValue) {
        // TODO: Reset value
        return;
    }
    auto convIsGroupValue = Converter::OptConvertPtr<bool>(isGroup);
    auto convArrowStepOutValue = Converter::OptConvertPtr<bool>(arrowStepOut);
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Opt_String* scopeId,
                            const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convIdValue = Converter::OptConvertPtr<std::string>(scopeId);
    if (!convIdValue) {
        // TODO: Reset value
        return;
    }
    auto optPriority = Converter::OptConvertPtr<uint32_t>(priority);
    ViewAbstractModelStatic::SetFocusScopePriority(frameNode, *convIdValue, optPriority);
}
void GestureImplInternal(Ark_NativePointer node, const Opt_GestureType* gesture, const Opt_GestureMask* mask,
    GesturePriority priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<RefPtr<Gesture>> aceGestureOpt;
    Converter::VisitUnionPtr(gesture,
        [&aceGestureOpt](const auto& gestureType) {
            aceGestureOpt = gestureType->gesture;
        },
        []() {}
    );
    CHECK_NULL_VOID(aceGestureOpt);
    auto aceGesture = aceGestureOpt.value();
    auto gestureMask = (Converter::OptConvertPtr<GestureMask>(mask)).value_or(GestureMask::Normal);
    aceGesture->SetGestureMask(gestureMask);
    aceGesture->SetPriority(priority);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->AddGesture(aceGesture);
}
void GestureImpl(Ark_NativePointer node,
                 const Opt_GestureType* gesture,
                 const Opt_GestureMask* mask)
{
    GestureImplInternal(node, gesture, mask, GesturePriority::Low);
}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Opt_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
    GestureImplInternal(node, gesture, mask, GesturePriority::High);
}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Opt_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
    GestureImplInternal(node, gesture, mask, GesturePriority::Parallel);
}
void Blur0Impl(Ark_NativePointer node,
               const Opt_Number* value,
               const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blur = Converter::OptConvertPtr<float>(value);
    if (!blur) {
        // TODO: Reset value
        return;
    }
    BlurOption blurOptions;
    auto optionsOpt = Converter::OptConvertPtr<BlurOption>(options);
    if (optionsOpt.has_value()) {
        blurOptions = optionsOpt.value();
    }
    CalcDimension dimensionBlur(*blur, DimensionUnit::PX);
}
void Blur1Impl(Ark_NativePointer node,
               const Opt_Number* blurRadius,
               const Opt_BlurOptions* options,
               const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blur = Converter::OptConvertPtr<float>(blurRadius).value_or(0.f);
    BlurOption blurOptions;
    auto optionsOpt = Converter::OptConvertPtr<BlurOption>(options);
    if (optionsOpt.has_value()) {
        blurOptions = optionsOpt.value();
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
}
void LinearGradientBlur0Impl(Ark_NativePointer node,
                             const Opt_Number* value,
                             const Opt_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvertPtr<Dimension>(value);
    auto convValue = Converter::OptConvertPtr<NG::LinearGradientBlurPara>(options);
    Validator::ValidateNonNegative(radius);
    if (radius.has_value() && convValue.has_value()) {
        convValue->blurRadius_ = radius.value();
    }
    ViewAbstractModelStatic::SetLinearGradientBlur(frameNode, convValue);
}
void LinearGradientBlur1Impl(Ark_NativePointer node,
                             const Opt_Number* blurRadius,
                             const Opt_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("The `ViewAbstract::SetSystemBarEffect(frameNode, enable)` function must take two parameters");
}
void BackdropBlur0Impl(Ark_NativePointer node,
                       const Opt_Number* value,
                       const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvertPtr<Dimension>(value);
    auto option = Converter::OptConvertPtr<BlurOption>(options);
    ViewAbstractModelStatic::SetBackdropBlur(frameNode, radius, option);
}
void BackdropBlur1Impl(Ark_NativePointer node,
                       const Opt_Number* radius,
                       const Opt_BlurOptions* options,
                       const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Opt_String* id,
                          const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto modelId = Converter::OptConvertPtr<std::string>(id);
    if (!modelId) {
        // TODO: Reset value
        return;
    }
    auto modelOptions = std::make_shared<SharedTransitionOption>();
    if (auto transOpt = Converter::OptConvertPtr<SharedTransitionOption>(options); transOpt) {
        *modelOptions = std::move(*transOpt);
    }
}
void ChainModeImpl(Ark_NativePointer node,
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
void DragPreviewOptionsImpl(Ark_NativePointer node,
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
    }
    LOGE("CommonMethodModifier::DragPreviewOptionsImpl Ark_ImageModifier is not supported yet.");
}
void OverlayImpl(Ark_NativePointer node,
                 const Opt_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{
}
void BlendMode0Impl(Ark_NativePointer node,
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
void BlendMode1Impl(Ark_NativePointer node,
                    const Opt_BlendMode* mode,
                    const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Opt_Union_BlendMode_Blender* effect,
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
        [](const Ark_BrightnessBlender& value) {
            LOGE("CommonMethodModifier::AdvancedBlendModeImpl Ark_BrightnessBlender is not supported yet.");
        },
        []() {}
    );
    std::optional<BlendApplyType> blendApplyTypeOpt = Converter::OptConvertPtr<BlendApplyType>(type);
    blendApplyType = blendApplyTypeOpt.value_or(blendApplyType);
    ViewAbstractModelStatic::SetBlendApplyType(frameNode, blendApplyType);
}
void BindTipsImpl(Ark_NativePointer node,
                  const Opt_TipsMessageType* message,
                  const Opt_TipsOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BindPopupImpl(Ark_NativePointer node,
                   const Opt_Boolean* show,
                   const Opt_Union_PopupOptions_CustomPopupOptions* popup)
{
}
void BindMenuBase(Ark_NativePointer node,
    const Opt_Boolean *isShow,
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
    menuParam.setShow = false;
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
            CallbackHelper(value).BuildAsync([frameNode, node, menuParam](const RefPtr<UINode>& uiNode) {
                auto builder = [uiNode]() {
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
                ViewAbstractModelStatic::BindMenu(frameNode, {}, std::move(builder), menuParam);
                }, node);
        },
        []() {});
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Opt_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    auto show = ArkValue<Opt_Boolean>(false);
    BindMenuBase(node, &show, content, options);
}
void BindMenu1Impl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const Opt_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    BindMenuBase(node, isShow, content, options);
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
    if (!menuOption) {
        contentBuilder(menuParam, nullptr);
        return;
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
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::NORMAL_TYPE;
    menuParam.isShow = false;
    BindContextMenuBase(node, content, responseType, options, menuParam);
}
void BindContextMenu1Impl(Ark_NativePointer node,
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
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Opt_CustomNodeBuilder* builder,
                           const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(builder);
    auto isShowValue = Converter::OptConvertPtr<bool>(isShow);
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
            }, node);
    } else {
        ContentCoverParam contentCoverParam;
        std::function<RefPtr<UINode>()> buildFunc = nullptr;
    }
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Opt_CustomNodeBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const Opt_CustomNodeBuilder* builder,
                   const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(builder);
    auto isShowValue = Converter::OptConvertPtr<Ark_Boolean>(isShow);
    if (!isShowValue) {
        // TODO: Reset value
        return;
    }
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    sheetStyle.showInPage = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto sheetOptions = Converter::OptConvertPtr<Ark_SheetOptions>(options);
    if (sheetOptions) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, sheetOptions.value());
        BindSheetUtil::ParseFuntionalCallbacks(cbs, sheetOptions.value());
        Converter::VisitUnion(sheetOptions->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.sheetTitle = OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = OptConvert<std::string>(value.title);
            },
            [frameNode, node, &cbs](const CustomNodeBuilder& value) {
                cbs.titleBuilder = [callback = CallbackHelper(value), node]() {
                    auto uiNode = callback.BuildSync(node);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            }, []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, sheetOptions.value());
    }
    auto optBuilder = Converter::GetOptPtr(builder);
    if (!optBuilder) {
        // TODO: Reset value
        return;
    }
    CallbackHelper(*optBuilder).BuildAsync([frameNode, isShowValue, sheetStyle,
        titleBuilder = std::move(cbs.titleBuilder), onAppear = std::move(cbs.onAppear),
        onDisappear = std::move(cbs.onDisappear), shouldDismiss = std::move(cbs.shouldDismiss),
        onWillDismiss = std::move(cbs.onWillDismiss), onWillAppear = std::move(cbs.onWillAppear),
        onWillDisappear = std::move(cbs.onWillDisappear), onHeightDidChange = std::move(cbs.onHeightDidChange),
        onDetentsDidChange = std::move(cbs.onDetentsDidChange), onWidthDidChange = std::move(cbs.onWidthDidChange),
        onTypeDidChange = std::move(cbs.onTypeDidChange), sheetSpringBack = std::move(cbs.sheetSpringBack)](
        const RefPtr<UINode>& uiNode) mutable {
        auto buildFunc = [frameNode, uiNode]() {
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        ViewAbstractModelStatic::BindSheet(frameNode, *isShowValue, nullptr, std::move(buildFunc),
            std::move(titleBuilder), sheetStyle, std::move(onAppear), std::move(onDisappear),
            std::move(shouldDismiss), std::move(onWillDismiss), std::move(onWillAppear), std::move(onWillDisappear),
            std::move(onHeightDidChange), std::move(onDetentsDidChange), std::move(onWidthDidChange),
            std::move(onTypeDidChange), std::move(sheetSpringBack));
        }, node);
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Opt_Array_Number* ratios,
                             const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    auto rawRatioVec = Converter::OptConvertPtr<std::vector<double>>(ratios);
    if (!rawRatioVec) {
        // TODO: Reset value
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
        // TODO: Reset value
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onVisibleAreaChange =
        [arkCallback = CallbackHelper(*optEvent), node = weakNode](bool visible, double ratio) {
            Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
            Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
            PipelineContext::SetCallBackNode(node);
            arkCallback.Invoke(isExpanding, currentRatio);
        };
}
void OnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                        const Opt_VisibleAreaEventOptions* options,
                                        const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
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
    auto optEvent = Converter::GetOptPtr(event);
    if (!optEvent) {
        // TODO: Reset value
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onVisibleAreaChange = [arkCallback = CallbackHelper(*optEvent), node = weakNode](
                                   bool visible, double ratio) {
        Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
        Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
        PipelineContext::SetCallBackNode(node);
        arkCallback.Invoke(isExpanding, currentRatio);
    };
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Opt_Union_String_FunctionKey* value,
                          const Opt_Array_ModifierKey* keys,
                          const Opt_Callback_Void* action)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value || !keys) {
        ViewAbstractModelStatic::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
        return;
    }
    auto strValue = Converter::OptConvertPtr<std::string>(value);
    if (!strValue.has_value() || strValue.value().size() != 1) {
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
            arkCallback.Invoke();
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
        CommonMethodModifier::Width0Impl,
        CommonMethodModifier::Width1Impl,
        CommonMethodModifier::Height0Impl,
        CommonMethodModifier::Height1Impl,
        CommonMethodModifier::DrawModifierImpl,
        CommonMethodModifier::ResponseRegionImpl,
        CommonMethodModifier::MouseResponseRegionImpl,
        CommonMethodModifier::SizeImpl,
        CommonMethodModifier::ConstraintSizeImpl,
        CommonMethodModifier::TouchableImpl,
        CommonMethodModifier::HitTestBehaviorImpl,
        CommonMethodModifier::OnChildTouchTestImpl,
        CommonMethodModifier::LayoutWeightImpl,
        CommonMethodModifier::ChainWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::SafeAreaPaddingImpl,
        CommonMethodModifier::MarginImpl,
        CommonMethodModifier::BackgroundColor0Impl,
        CommonMethodModifier::BackgroundColor1Impl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundEffect0Impl,
        CommonMethodModifier::BackgroundEffect1Impl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::Opacity0Impl,
        CommonMethodModifier::Opacity1Impl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::Outline0Impl,
        CommonMethodModifier::Outline1Impl,
        CommonMethodModifier::OutlineStyle0Impl,
        CommonMethodModifier::OutlineStyle1Impl,
        CommonMethodModifier::OutlineWidth0Impl,
        CommonMethodModifier::OutlineWidth1Impl,
        CommonMethodModifier::OutlineColor0Impl,
        CommonMethodModifier::OutlineColor1Impl,
        CommonMethodModifier::OutlineRadius0Impl,
        CommonMethodModifier::OutlineRadius1Impl,
        CommonMethodModifier::ForegroundColor0Impl,
        CommonMethodModifier::ForegroundColor1Impl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnHoverMoveImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEvent0Impl,
        CommonMethodModifier::OnKeyEvent1Impl,
        CommonMethodModifier::OnDigitalCrownImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::OnKeyEventDispatchImpl,
        CommonMethodModifier::OnFocusAxisEventImpl,
        CommonMethodModifier::OnAxisEventImpl,
        CommonMethodModifier::FocusableImpl,
        CommonMethodModifier::NextFocusImpl,
        CommonMethodModifier::TabStopImpl,
        CommonMethodModifier::OnFocusImpl,
        CommonMethodModifier::OnBlurImpl,
        CommonMethodModifier::TabIndexImpl,
        CommonMethodModifier::DefaultFocusImpl,
        CommonMethodModifier::GroupDefaultFocusImpl,
        CommonMethodModifier::FocusOnTouchImpl,
        CommonMethodModifier::FocusBoxImpl,
        CommonMethodModifier::AnimationImpl,
        CommonMethodModifier::Transition0Impl,
        CommonMethodModifier::Transition1Impl,
        CommonMethodModifier::MotionBlur0Impl,
        CommonMethodModifier::MotionBlur1Impl,
        CommonMethodModifier::Brightness0Impl,
        CommonMethodModifier::Brightness1Impl,
        CommonMethodModifier::Contrast0Impl,
        CommonMethodModifier::Contrast1Impl,
        CommonMethodModifier::Grayscale0Impl,
        CommonMethodModifier::Grayscale1Impl,
        CommonMethodModifier::ColorBlend0Impl,
        CommonMethodModifier::ColorBlend1Impl,
        CommonMethodModifier::Saturate0Impl,
        CommonMethodModifier::Saturate1Impl,
        CommonMethodModifier::Sepia0Impl,
        CommonMethodModifier::Sepia1Impl,
        CommonMethodModifier::Invert0Impl,
        CommonMethodModifier::Invert1Impl,
        CommonMethodModifier::HueRotate0Impl,
        CommonMethodModifier::HueRotate1Impl,
        CommonMethodModifier::UseShadowBatching0Impl,
        CommonMethodModifier::UseShadowBatching1Impl,
        CommonMethodModifier::UseEffect0Impl,
        CommonMethodModifier::UseEffect1Impl,
        CommonMethodModifier::UseEffect2Impl,
        CommonMethodModifier::RenderGroup0Impl,
        CommonMethodModifier::RenderGroup1Impl,
        CommonMethodModifier::Freeze0Impl,
        CommonMethodModifier::Freeze1Impl,
        CommonMethodModifier::Translate0Impl,
        CommonMethodModifier::Translate1Impl,
        CommonMethodModifier::Scale0Impl,
        CommonMethodModifier::Scale1Impl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::Rotate0Impl,
        CommonMethodModifier::Rotate1Impl,
        CommonMethodModifier::Transform0Impl,
        CommonMethodModifier::Transform1Impl,
        CommonMethodModifier::OnAppearImpl,
        CommonMethodModifier::OnDisAppearImpl,
        CommonMethodModifier::OnAttachImpl,
        CommonMethodModifier::OnDetachImpl,
        CommonMethodModifier::OnAreaChangeImpl,
        CommonMethodModifier::VisibilityImpl,
        CommonMethodModifier::FlexGrowImpl,
        CommonMethodModifier::FlexShrinkImpl,
        CommonMethodModifier::FlexBasisImpl,
        CommonMethodModifier::AlignSelfImpl,
        CommonMethodModifier::DisplayPriorityImpl,
        CommonMethodModifier::ZIndexImpl,
        CommonMethodModifier::DirectionImpl,
        CommonMethodModifier::AlignImpl,
        CommonMethodModifier::PositionImpl,
        CommonMethodModifier::MarkAnchorImpl,
        CommonMethodModifier::OffsetImpl,
        CommonMethodModifier::EnabledImpl,
        CommonMethodModifier::UseSizeTypeImpl,
        CommonMethodModifier::AlignRules0Impl,
        CommonMethodModifier::AlignRules1Impl,
        CommonMethodModifier::AspectRatioImpl,
        CommonMethodModifier::ClickEffect0Impl,
        CommonMethodModifier::ClickEffect1Impl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDrop0Impl,
        CommonMethodModifier::OnDrop1Impl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreview0Impl,
        CommonMethodModifier::DragPreview1Impl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::LinearGradient0Impl,
        CommonMethodModifier::LinearGradient1Impl,
        CommonMethodModifier::SweepGradient0Impl,
        CommonMethodModifier::SweepGradient1Impl,
        CommonMethodModifier::RadialGradient0Impl,
        CommonMethodModifier::RadialGradient1Impl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::Shadow0Impl,
        CommonMethodModifier::Shadow1Impl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::Clip2Impl,
        CommonMethodModifier::ClipShape0Impl,
        CommonMethodModifier::ClipShape1Impl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::Mask2Impl,
        CommonMethodModifier::MaskShape0Impl,
        CommonMethodModifier::MaskShape1Impl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::SphericalEffect0Impl,
        CommonMethodModifier::SphericalEffect1Impl,
        CommonMethodModifier::LightUpEffect0Impl,
        CommonMethodModifier::LightUpEffect1Impl,
        CommonMethodModifier::PixelStretchEffect0Impl,
        CommonMethodModifier::PixelStretchEffect1Impl,
        CommonMethodModifier::AccessibilityGroup0Impl,
        CommonMethodModifier::AccessibilityGroup1Impl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityNextFocusIdImpl,
        CommonMethodModifier::AccessibilityDefaultFocusImpl,
        CommonMethodModifier::AccessibilityUseSamePageImpl,
        CommonMethodModifier::AccessibilityScrollTriggerableImpl,
        CommonMethodModifier::AccessibilityRoleImpl,
        CommonMethodModifier::OnAccessibilityFocusImpl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::AccessibilityCheckedImpl,
        CommonMethodModifier::AccessibilitySelectedImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::ReuseImpl,
        CommonMethodModifier::RenderFit0Impl,
        CommonMethodModifier::RenderFit1Impl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightness0Impl,
        CommonMethodModifier::BackgroundBrightness1Impl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
        CommonMethodModifier::AccessibilityFocusDrawLevelImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundImage0Impl,
        CommonMethodModifier::BackgroundImage1Impl,
        CommonMethodModifier::BackgroundBlurStyle0Impl,
        CommonMethodModifier::BackgroundBlurStyle1Impl,
        CommonMethodModifier::ForegroundBlurStyle0Impl,
        CommonMethodModifier::ForegroundBlurStyle1Impl,
        CommonMethodModifier::FocusScopeId0Impl,
        CommonMethodModifier::FocusScopeId1Impl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::Blur0Impl,
        CommonMethodModifier::Blur1Impl,
        CommonMethodModifier::LinearGradientBlur0Impl,
        CommonMethodModifier::LinearGradientBlur1Impl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::BackdropBlur0Impl,
        CommonMethodModifier::BackdropBlur1Impl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::BlendMode0Impl,
        CommonMethodModifier::BlendMode1Impl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::BindTipsImpl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::OnVisibleAreaApproximateChangeImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
