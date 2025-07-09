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
#include "core/interfaces/native/implementation/drag_event_peer.h"
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
#include "base/log/log_wrapper.h"

using namespace OHOS::Ace::NG::Converter;

namespace {
constexpr double PERCENT_100 = 100.0;
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int NUM_3 = 3;
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
    std::function<void()> onAppearCallback;
    std::function<void()> onDisappearCallback;
    std::function<void()> onWillAppearCallback;
    std::function<void()> onWillDisappearCallback;
    std::function<void()> shouldDismissFunc;
    std::function<void(const int32_t)> onWillDismissCallback;
    std::function<void(const float)> onHeightDidChangeCallback;
    std::function<void(const float)> onDetentsDidChangeCallback;
    std::function<void(const float)> onWidthDidChangeCallback;
    std::function<void(const float)> onTypeDidChangeCallback;
    std::function<void()> titleBuilderFunction;
    std::function<void()> sheetSpringBackFunc;
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

namespace GeneratedModifier {
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor();
}

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
                arkCallback.Invoke(parameter);
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
        [&popupParam](const Ark_Literal_ResourceColor_color& mask) {
            auto maskColorOpt = OptConvert<Color>(mask.color);
            if (maskColorOpt.has_value()) {
                popupParam->SetMaskColor(maskColorOpt.value());
            }
        },
        []() {});
    auto arkOnStateChange = OptConvert<Callback_Literal_Boolean_isVisible_Void>(src.onStateChange);
    if (arkOnStateChange.has_value()) {
        auto onStateChangeCallback = [arkCallback = CallbackHelper(arkOnStateChange.value())](
            const std::string& param) {
            auto json = JsonUtil::Create(true);
            json->Put("isVisible", param.c_str());
            Ark_Literal_Boolean_isVisible event;
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
    auto backgroundColorOpt = Converter::OptConvert<Color>(src.popupColor);
    if (backgroundColorOpt.has_value()) {
        popupParam->SetBackgroundColor(backgroundColorOpt.value());
    }
    popupParam->SetHasAction(Converter::OptConvert<bool>(src.autoCancel).value_or(popupParam->HasAction()));
};

auto g_popupCommonParamPart1 = [](const auto& src, RefPtr<PopupParam>& popupParam) {
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
    auto blurStyleOpt = Converter::OptConvert<BlurStyle>(src.backgroundBlurStyle);
    if (blurStyleOpt.has_value()) {
        popupParam->SetBlurStyle(blurStyleOpt.value());
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
    auto transitionOpt = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(src.transition);
    if (transitionOpt.has_value()) {
        popupParam->SetTransitionEffects(transitionOpt.value());
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
    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
    menuParam.borderRadius = OptConvert<BorderRadiusProperty>(menuOptions.borderRadius);
    menuParam.layoutRegionMargin = OptConvert<PaddingProperty>(menuOptions.layoutRegionMargin);
};

auto g_bindContextMenuParams = [](MenuParam& menuParam, const Opt_ContextMenuOptions* options,
    std::function<void()>& previewBuildFunc, Ark_NativePointer node, FrameNode* frameNode) {
    menuParam.placement = Placement::BOTTOM_LEFT;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    auto menuOption = options ? Converter::OptConvert<Ark_ContextMenuOptions>(*options) : std::nullopt;
    CHECK_NULL_VOID(menuOption);
    auto weakNode = AceType::WeakClaim(frameNode);
    g_bindMenuOptionsParam(menuOption.value(), menuParam, weakNode);
    Converter::VisitUnion(menuOption->preview,
        [&menuParam, menuOption](const Ark_MenuPreviewMode& value) {
            auto mode = Converter::OptConvert<MenuPreviewMode>(value);
            if (mode && mode.value() == MenuPreviewMode::IMAGE) {
                menuParam.previewMode = MenuPreviewMode::IMAGE;
            }
        },
        [&menuParam, menuOption, &previewBuildFunc, node, frameNode, weakNode](const CustomNodeBuilder& value) {
            previewBuildFunc = [callback = CallbackHelper(value), node, weakNode]() -> RefPtr<UINode> {
                PipelineContext::SetCallBackNode(weakNode);
                return callback.BuildSync(node);
            };
            menuParam.previewMode = MenuPreviewMode::CUSTOM;
        },
        []() {});
    auto optParam = options ? Converter::OptConvert<NG::MenuParam>(menuOption->previewAnimationOptions) : std::nullopt;
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

namespace Converter {

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
std::pair<std::optional<Dimension>, std::optional<Dimension>> Convert(const Ark_Position& src)
{
    auto x = OptConvert<Dimension>(src.x);
    auto y = OptConvert<Dimension>(src.y);
    return {x, y};
}

template<>
ButtonProperties Convert(const Ark_Literal_String_value_Callback_Void_action& src)
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
    popupParam->SetPlacement(OptConvert<Placement>(src.placement).value_or(
        OptConvert<bool>(src.placementOnTop).value_or(false) ? Placement::TOP : Placement::BOTTOM));
    g_popupCommonParam(src, popupParam);
    g_popupCommonParamPart1(src, popupParam);
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
    g_popupCommonParamPart1(src, popupParam);
    return popupParam;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
void AssignArkValue(Ark_PreDragStatus& dst, const PreDragStatus& src)
{}
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
    return 0;
}
void RequestFrameImpl()
{
    ViewAbstract::RequestFrame();
}
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) != CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
            return;
        }
        ViewAbstract::SetWidth(frameNode, result);
    }
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) != CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstract::SetHeight(frameNode, result);
    }
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Opt_DrawModifier* value)
{}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Ark_Union_Array_Rectangle_Rectangle* value)
{}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Ark_Union_Array_Rectangle_Rectangle* value)
{}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Ark_Length>(value->width);
    if (width) {
        WidthImpl(node, &width.value());
    }
    auto height = Converter::OptConvert<Ark_Length>(value->height);
    if (height) {
        HeightImpl(node, &height.value());
    }
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         Ark_HitTestMode value)
{}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          const Callback_Array_TouchTestInfo_TouchResult* value)
{}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String* value)
{}
void ChainWeightImpl(Ark_NativePointer node,
                     const Ark_ChainWeightOptions* value)
{}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Length_LocalizedPadding* value)
{}
void SafeAreaPaddingImpl(Ark_NativePointer node,
                         const Ark_Union_Padding_LengthMetrics_LocalizedPadding* value)
{}
void MarginImpl(Ark_NativePointer node,
                const Ark_Union_Margin_Length_LocalizedMargin* value)
{}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{}
void PixelRoundImpl(Ark_NativePointer node,
                    const Ark_PixelRoundPolicy* value)
{}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Ark_Union_SizeOptions_ImageSize* value)
{}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Ark_Union_Position_Alignment* value)
{}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* value)
{}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* value)
{}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_VisualEffect* value)
{}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
}
void OpacityImpl(Ark_NativePointer node,
                 const Ark_Union_Number_Resource* value)
{}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{}
void BorderStyleImpl(Ark_NativePointer node,
                     const Ark_Union_BorderStyle_EdgeStyles* value)
{}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{}

void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Ark_Union_OutlineStyle_EdgeOutlineStyles* value)
{}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Ark_Union_Dimension_EdgeOutlineWidths* value)
{}
void OutlineColorImpl(Ark_NativePointer node,
                      const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Ark_Union_Dimension_OutlineRadiuses* value)
{}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceColor_ColoringStrategy* value)
{}
void OnClick0Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onClick = [callback = CallbackHelper(*value)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.Invoke(event.ArkValue());
    };
    NG::ViewAbstract::SetOnClick(frameNode, std::move(onClick));
}
void OnClick1Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* event,
                  const Ark_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(distanceThreshold);
    auto onEvent = [callback = CallbackHelper(*event)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.InvokeSync(event.ArkValue());
    };
    auto convValue = Converter::Convert<float>(*distanceThreshold);

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent), convValue);
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 const Callback_Boolean_HoverEvent_Void* value)
{}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              const AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value) {
        ViewAbstract::DisableOnAccessibilityHover(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAccessibilityHover = [arkCallback = CallbackHelper(*value), node = weakNode](
        bool isHover, AccessibilityHoverInfo& hoverInfo) {
        PipelineContext::SetCallBackNode(node);
        Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
        auto event = Converter::ArkAccessibilityHoverEventSync(hoverInfo);
        arkCallback.InvokeSync(arkIsHover, event.ArkValue());
    };
    ViewAbstract::SetOnAccessibilityHover(frameNode, std::move(onAccessibilityHover));
}
void HoverEffectImpl(Ark_NativePointer node,
                     Ark_HoverEffect value)
{}
void OnMouseImpl(Ark_NativePointer node,
                 const Callback_MouseEvent_Void* value)
{}
void OnTouchImpl(Ark_NativePointer node,
                 const Callback_TouchEvent_Void* value)
{}
void OnKeyEventImpl(Ark_NativePointer node,
                    const Callback_KeyEvent_Void* value)
{}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Callback_KeyEvent_Boolean* value)
{}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{}
void OnFocusImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{}
void OnBlurImpl(Ark_NativePointer node,
                const Callback_Void* value)
{}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* value)
{}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{}
void Transition0Impl(Ark_NativePointer node,
                     const Ark_Union_TransitionOptions_TransitionEffect* value)
{}
void Transition1Impl(Ark_NativePointer node,
                     Ark_TransitionEffect effect,
                     const Opt_TransitionFinishCallback* onFinish)
{}

void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{}
void ColorBlendImpl(Ark_NativePointer node,
                    const Ark_Union_Color_String_Resource* value)
{}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{}
void InvertImpl(Ark_NativePointer node,
                const Ark_Union_Number_InvertOptions* value)
{}
void HueRotateImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{}
void UseEffect0Impl(Ark_NativePointer node,
                    Ark_Boolean value)
{}
void UseEffect1Impl(Ark_NativePointer node,
                    Ark_Boolean useEffect,
                    Ark_EffectType effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{}
void OnAppearImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{}
void OnDisAppearImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{}
void OnAttachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{}
void OnDetachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{}
void OnAreaChangeImpl(Ark_NativePointer node,
                      const Callback_Area_Area_Void* value)
{}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{}
void FlexBasisImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{}
void AlignSelfImpl(Ark_NativePointer node,
                   Ark_ItemAlign value)
{}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Direction value)
{}
void AlignImpl(Ark_NativePointer node,
               Ark_Alignment value)
{}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Union_Position_Edges_LocalizedEdges* value)
{}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Union_Position_LocalizedPosition* value)
{}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
{}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* value)
{}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{}
void ClickEffectImpl(Ark_NativePointer node,
                     const Opt_ClickEffect* value)
{}
void OnDragStartImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Callback_DragEvent_String_Void* value)
{}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{}
void OnDropImpl(Ark_NativePointer node,
                const Callback_DragEvent_String_Void* value)
{}
void OnDragEndImpl(Ark_NativePointer node,
                   const Callback_DragEvent_String_Void* value)
{}
void AllowDropImpl(Ark_NativePointer node,
                   const Opt_Array_UniformDataType* value)
{}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{}
void DragPreviewImpl(Ark_NativePointer node,
                     const Ark_Union_CustomBuilder_DragItemInfo_String* value)
{}
void OnPreDragImpl(Ark_NativePointer node,
                   const Callback_PreDragStatus_Void* value)
{}
void LinearGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_linearGradient_value* value)
{}
void SweepGradientImpl(Ark_NativePointer node,
                       const Ark_Type_CommonMethod_sweepGradient_value* value)
{}
void RadialGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_radialGradient_value* value)
{}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{}
void ShadowImpl(Ark_NativePointer node,
                const Ark_Union_ShadowOptions_ShadowStyle* value)
{}
void Clip0Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetClipEdge(frameNode, Converter::OptConvert<bool>(*value).value_or(false));
}
void Clip1Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{}
void Mask0Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{}
void Mask1Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* value)
{}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("Ark_StateStyles contains a CustomObject's which is not supported");
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* value)
{}
void AccessibilityGroup0Impl(Ark_NativePointer node,
                             Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessible = Converter::Convert<bool>(value);
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, accessible);
}
void AccessibilityGroup1Impl(Ark_NativePointer node,
                             Ark_Boolean isGroup,
                             const Ark_AccessibilityOptions* accessibilityOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isGroupValue = Converter::Convert<bool>(isGroup);
    auto accessibilityPreferred = accessibilityOptions
        ? Converter::OptConvert<bool>(accessibilityOptions->accessibilityPreferred) : std::nullopt;
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, isGroupValue);
    ViewAbstractModelNG::SetAccessibilityTextPreferred(frameNode, accessibilityPreferred.value_or(false));
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    ViewAbstractModelNG::SetAccessibilityText(frameNode, convValue);
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<std::string>(*value);
    if (optValue.has_value()) {
        ViewAbstractModelNG::SetAccessibilityText(frameNode, optValue.value());
    }
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    ViewAbstractModelNG::SetAccessibilityTextHint(frameNode, convValue);
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, convValue);
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<std::string>(*value);
    if (optValue.has_value()) {
        ViewAbstractModelNG::SetAccessibilityDescription(frameNode, optValue.value());
    }
    LOGE("SetAccessibilityDescription for Ark_Resource is not implemented");
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, convValue);
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto builder = [callback = CallbackHelper(*value), node]() -> RefPtr<UINode> {
        return callback.BuildSync(node);
    };
    ViewAbstractModelStatic::SetAccessibilityVirtualNode(frameNode, std::move(builder));
}
void AccessibilityCheckedImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    auto resetValue = false;
    ViewAbstractModelNG::SetAccessibilityChecked(frameNode, convValue, resetValue);
}
void AccessibilitySelectedImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    bool resetValue = false;
    ViewAbstractModelNG::SetAccessibilitySelected(frameNode, convValue, resetValue);
}
void ObscuredImpl(Ark_NativePointer node,
                  const Array_ObscuredReasons* value)
{}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* value)
{}
void RenderFitImpl(Ark_NativePointer node,
                   Ark_RenderFit value)
{}
void GestureModifierImpl(Ark_NativePointer node,
                         Ark_GestureModifier value)
{}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* value)
{}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             const Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* callback,
                                        Ark_Boolean exposeInnerGesture);
void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* value)
{}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* callback_,
                                        Ark_Boolean exposeInnerGesture)
{}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             const ShouldBuiltInRecognizerParallelWithCallback* value)
{}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          const Callback_TouchEvent_HitTestMode* value)
{}
void OnSizeChangeImpl(Ark_NativePointer node,
                      const SizeChangeCallback* value)
{}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Opt_CustomObject* value)
{}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{}
void BackgroundImpl(Ark_NativePointer node,
                    const CustomNodeBuilder* builder,
                    const Opt_Literal_Alignment_align* options)
{}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceStr_PixelMap* src,
                         const Opt_ImageRepeat* repeat)
{}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{}
void FocusScopeId0Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup)
{}
void FocusScopeId1Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup,
                       const Opt_Boolean* arrowStepOut)
{}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{}
void GestureImplInternal(Ark_NativePointer node, const Ark_GestureType* gesture, const Opt_GestureMask* mask,
    GesturePriority priority)
{}
void GestureImpl(Ark_NativePointer node,
                 const Ark_GestureType* gesture,
                 const Opt_GestureMask* mask)
{}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{}
void SystemBarEffectImpl(Ark_NativePointer node)
{}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Ark_String* id,
                          const Opt_sharedTransitionOptions* options)
{}
void ChainModeImpl(Ark_NativePointer node,
                   Ark_Axis direction,
                   Ark_ChainStyle style)
{}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{}
void OverlayImpl(Ark_NativePointer node,
                 const Ark_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{}
void BlendModeImpl(Ark_NativePointer node,
                   Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Ark_Union_BlendMode_Blender* effect,
                           const Opt_BlendApplyType* type)
{}
void BindPopupImpl(Ark_NativePointer node,
                   Ark_Boolean show,
                   const Ark_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(popup);
    RefPtr<UINode> customNode = nullptr;
    RefPtr<PopupParam> popupParam = nullptr;
    Converter::VisitUnion(*popup,
        [&popupParam](const Ark_PopupOptions& value) {
            popupParam = Converter::Convert<RefPtr<PopupParam>>(value);
            CHECK_NULL_VOID(popupParam);
            g_onWillDismissPopup(value.onWillDismiss, popupParam);
        },
        [&popupParam, &customNode, frameNode, node](const Ark_CustomPopupOptions& value) {
            popupParam = Converter::Convert<RefPtr<PopupParam>>(value);
            CHECK_NULL_VOID(popupParam);
            if (popupParam->IsShow() && !g_isPopupCreated(frameNode)) {
                customNode = CallbackHelper(value.builder).BuildSync(node);
            }
            g_onWillDismissPopup(value.onWillDismiss, popupParam);
        },
        [&popupParam]() {
            popupParam = AceType::MakeRefPtr<PopupParam>();
        });
    CHECK_NULL_VOID(popupParam);
    popupParam->SetIsShow(Converter::Convert<bool>(show));
    ViewAbstractModelStatic::BindPopup(frameNode, popupParam, customNode);
}
void BindMenuBase(Ark_NativePointer node,
    Ark_Boolean isShow,
    const Ark_Union_Array_MenuElement_CustomBuilder* content,
    const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(content);
    MenuParam menuParam;
    menuParam.placement = Placement::BOTTOM_LEFT;
    menuParam.isShowInSubWindow = false;
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuParam.isShowInSubWindow = theme->GetExpandDisplay();
    menuParam.setShow = false;
    menuParam.isShow = Converter::Convert<bool>(isShow);
    auto menuOptions = options ? OptConvert<Ark_MenuOptions>(*options) : std::nullopt;
    if (menuOptions) {
        menuParam.title = OptConvert<std::string>(menuOptions->title).value_or(menuParam.title);
        auto weakNode = AceType::WeakClaim(frameNode);
        g_bindMenuOptionsParam(menuOptions.value(), menuParam, weakNode);
        if (menuParam.isShowInSubWindow) {
            menuParam.isShowInSubWindow = OptConvert<bool>(menuOptions->showInSubWindow).value_or(true);
        }
    }
    Converter::VisitUnion(*content,
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
void BindMenu0Impl(Ark_NativePointer node,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    BindMenuBase(node, ArkValue<Ark_Boolean>(false), content, options);
}
void BindMenu1Impl(Ark_NativePointer node,
                   Ark_Boolean isShow,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    BindMenuBase(node, isShow, content, options);
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const CustomNodeBuilder* content,
                          Ark_ResponseType responseType,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(content);
    MenuParam menuParam;
    auto type = Converter::OptConvert<ResponseType>(responseType).value_or(ResponseType::LONG_PRESS);
    auto builder = [callback = CallbackHelper(*content), node, weakNode = AceType::WeakClaim(frameNode)]() {
        PipelineContext::SetCallBackNode(weakNode);
        auto uiNode = callback.BuildSync(node);
        ViewStackProcessor::GetInstance()->Push(uiNode);
    };
    menuParam.previewMode = MenuPreviewMode::NONE;
    std::function<void()> previewBuildFunc = nullptr;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::NORMAL_TYPE;
    g_bindContextMenuParams(menuParam, options, previewBuildFunc, node, frameNode);
    if (type != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.isShowHoverImage = false;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    ViewAbstractModelStatic::BindContextMenuStatic(
        AceType::Claim(frameNode), type, std::move(builder), menuParam, std::move(previewBuildFunc));
    ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(frameNode, menuParam);
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          Ark_Boolean isShown,
                          const CustomNodeBuilder* content,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(content);
    MenuParam menuParam;
    menuParam.isShow = Converter::Convert<bool>(isShown);
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    ResponseType type = ResponseType::LONG_PRESS;
    auto builder = [callback = CallbackHelper(*content), node]() {
        auto uiNode = callback.BuildSync(node);
        ViewStackProcessor::GetInstance()->Push(uiNode);
    };
    menuParam.previewMode = MenuPreviewMode::NONE;
    std::function<void()> previewBuildFunc = nullptr;
    g_bindContextMenuParams(menuParam, options, previewBuildFunc, node, frameNode);
    ViewAbstractModelStatic::BindContextMenuStatic(
        AceType::Claim(frameNode), type, std::move(builder), menuParam, std::move(previewBuildFunc));
    ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(frameNode, menuParam);
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomNodeBuilder* builder,
                           const Opt_ModalTransition* type)
{}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomNodeBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const CustomNodeBuilder* builder,
                   const Opt_SheetOptions* options)
{}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             const VisibleAreaChangeCallback* event)
{}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Ark_Union_String_FunctionKey* value,
                          const Array_ModifierKey* keys,
                          const Opt_Callback_Void* action)
{}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::RequestFrameImpl,
        CommonMethodModifier::ConstructImpl,
        CommonMethodModifier::WidthImpl,
        CommonMethodModifier::HeightImpl,
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
        CommonMethodModifier::BackgroundColorImpl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundEffectImpl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::OpacityImpl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::OutlineImpl,
        CommonMethodModifier::OutlineStyleImpl,
        CommonMethodModifier::OutlineWidthImpl,
        CommonMethodModifier::OutlineColorImpl,
        CommonMethodModifier::OutlineRadiusImpl,
        CommonMethodModifier::ForegroundColorImpl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEventImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::FocusableImpl,
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
        CommonMethodModifier::MotionBlurImpl,
        CommonMethodModifier::BrightnessImpl,
        CommonMethodModifier::ContrastImpl,
        CommonMethodModifier::GrayscaleImpl,
        CommonMethodModifier::ColorBlendImpl,
        CommonMethodModifier::SaturateImpl,
        CommonMethodModifier::SepiaImpl,
        CommonMethodModifier::InvertImpl,
        CommonMethodModifier::HueRotateImpl,
        CommonMethodModifier::UseShadowBatchingImpl,
        CommonMethodModifier::UseEffect0Impl,
        CommonMethodModifier::UseEffect1Impl,
        CommonMethodModifier::RenderGroupImpl,
        CommonMethodModifier::FreezeImpl,
        CommonMethodModifier::TranslateImpl,
        CommonMethodModifier::ScaleImpl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::RotateImpl,
        CommonMethodModifier::TransformImpl,
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
        CommonMethodModifier::ClickEffectImpl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDropImpl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreviewImpl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::LinearGradientImpl,
        CommonMethodModifier::SweepGradientImpl,
        CommonMethodModifier::RadialGradientImpl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::ShadowImpl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::ClipShapeImpl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::MaskShapeImpl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::SphericalEffectImpl,
        CommonMethodModifier::LightUpEffectImpl,
        CommonMethodModifier::PixelStretchEffectImpl,
        CommonMethodModifier::AccessibilityGroup0Impl,
        CommonMethodModifier::AccessibilityGroup1Impl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::AccessibilityCheckedImpl,
        CommonMethodModifier::AccessibilitySelectedImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::RenderFitImpl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightnessImpl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundImageImpl,
        CommonMethodModifier::BackgroundBlurStyleImpl,
        CommonMethodModifier::ForegroundBlurStyleImpl,
        CommonMethodModifier::FocusScopeId0Impl,
        CommonMethodModifier::FocusScopeId1Impl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::BlurImpl,
        CommonMethodModifier::LinearGradientBlurImpl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::BackdropBlurImpl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::BlendModeImpl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
