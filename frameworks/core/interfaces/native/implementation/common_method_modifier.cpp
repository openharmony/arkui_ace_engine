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

// auto g_contentCoverCallbacks = [](WeakPtr<FrameNode> weakNode, const Ark_ContentCoverOptions& options,
//     std::function<void()>& onShowCallback, std::function<void()>& onDismissCallback,
//     std::function<void()>& onWillShowCallback, std::function<void()>& onWillDismissCallback,
//     std::function<void(const int32_t& info)>& onWillDismissFunc) {
//     auto onAppearValue = OptConvert<Callback_Void>(options.onAppear);
//     if (onAppearValue) {
//         onShowCallback = [arkCallback = CallbackHelper(onAppearValue.value()), weakNode]() {
//             PipelineContext::SetCallBackNode(weakNode);
//             arkCallback.Invoke();
//         };
//     }
//     auto onDisappearValue = OptConvert<Callback_Void>(options.onDisappear);
//     if (onDisappearValue) {
//         onDismissCallback = [arkCallback = CallbackHelper(onDisappearValue.value()), weakNode]() {
//             PipelineContext::SetCallBackNode(weakNode);
//             arkCallback.Invoke();
//         };
//     }
//     auto onWillAppearValue = OptConvert<Callback_Void>(options.onWillAppear);
//     if (onWillAppearValue) {
//         onWillShowCallback = [arkCallback = CallbackHelper(onWillAppearValue.value()), weakNode]() {
//             PipelineContext::SetCallBackNode(weakNode);
//             arkCallback.Invoke();
//         };
//     }
//     auto onWillDisappearValue = OptConvert<Callback_Void>(options.onWillDisappear);
//     if (onWillDisappearValue) {
//         onWillDismissCallback = [arkCallback = CallbackHelper(onWillDisappearValue.value()), weakNode]() {
//             PipelineContext::SetCallBackNode(weakNode);
//             arkCallback.Invoke();
//         };
//     }
//     auto onWillDismissValue = OptConvert<Callback_DismissContentCoverAction_Void>(options.onWillDismiss);
//     if (onWillDismissValue) {
//         onWillDismissFunc = [arkCallback = CallbackHelper(onWillDismissValue.value()), weakNode](int32_t reason) {
//             PipelineContext::SetCallBackNode(weakNode);
//             Ark_DismissContentCoverAction parameter;
//             auto reasonOpt = Converter::ArkValue<Opt_DismissReason>(
//                 static_cast<BindSheetDismissReason>(reason));
//             parameter.reason = Converter::OptConvert<Ark_DismissReason>(reasonOpt)
//                 .value_or(ARK_DISMISS_REASON_CLOSE_BUTTON);
//             const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelNG::DismissContentCoverStatic));
//             parameter.dismiss = keeper.ArkValue();
//             arkCallback.Invoke(parameter);
//         };
//     }
// };

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

// auto g_bindSheetCallbacks1 = [](SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions) {
//     auto onAppear = Converter::OptConvert<Callback_Void>(sheetOptions.onAppear);
//     if (onAppear) {
//         callbacks.onAppearCallback = [arkCallback = CallbackHelper(onAppear.value())]() {
//             arkCallback.Invoke();
//         };
//     }
//     auto onDisappear = Converter::OptConvert<Callback_Void>(sheetOptions.onDisappear);
//     if (onDisappear) {
//         callbacks.onDisappearCallback = [arkCallback = CallbackHelper(onDisappear.value())]() {
//             arkCallback.Invoke();
//         };
//     }
//     auto onWillAppear = Converter::OptConvert<Callback_Void>(sheetOptions.onWillAppear);
//     if (onWillAppear) {
//         callbacks.onWillAppearCallback = [arkCallback = CallbackHelper(onWillAppear.value())]() {
//             arkCallback.Invoke();
//         };
//     }
//     auto onWillDisappear = Converter::OptConvert<Callback_Void>(sheetOptions.onWillDisappear);
//     if (onWillDisappear) {
//         callbacks.onWillDisappearCallback = [arkCallback = CallbackHelper(onWillDisappear.value())]() {
//             arkCallback.Invoke();
//         };
//     }
//     auto shouldDismiss = Converter::OptConvert<Callback_SheetDismiss_Void>(sheetOptions.shouldDismiss);
//     if (shouldDismiss) {
//         callbacks.shouldDismissFunc = [arkCallback = CallbackHelper(shouldDismiss.value())]() {
//             Ark_SheetDismiss parameter;
//             const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelNG::DismissSheetStatic));
//             parameter.dismiss = keeper.ArkValue();
//             arkCallback.Invoke(parameter);
//         };
//     }
//     auto onTypeDidChange = Converter::OptConvert<Callback_SheetType_Void>(sheetOptions.onTypeDidChange);
//     if (onTypeDidChange) {
//         callbacks.onTypeDidChangeCallback = [arkCallback = CallbackHelper(onTypeDidChange.value())](int32_t value) {
//             arkCallback.Invoke(Converter::ArkValue<Ark_SheetType>(static_cast<SheetType>(value)));
//         };
//     }
// };

// auto g_bindSheetCallbacks2 = [](SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions) {
//     auto onWillDismiss = Converter::OptConvert<Callback_DismissSheetAction_Void>(sheetOptions.onWillDismiss);
//     if (onWillDismiss) {
//         callbacks.onWillDismissCallback = [arkCallback = CallbackHelper(onWillDismiss.value())](const int32_t reason) {
//             Ark_DismissSheetAction parameter;
//             auto reasonOpt = ArkValue<Opt_DismissReason>(static_cast<BindSheetDismissReason>(reason));
//             parameter.reason = OptConvert<Ark_DismissReason>(reasonOpt).value_or(ARK_DISMISS_REASON_CLOSE_BUTTON);
//             const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelNG::DismissSheetStatic));
//             parameter.dismiss = keeper.ArkValue();
//             arkCallback.Invoke(parameter);
//         };
//     }
//     auto onWillSpringBackWhenDismiss = Converter::OptConvert<Callback_SpringBackAction_Void>(
//         sheetOptions.onWillSpringBackWhenDismiss);
//     if (onWillSpringBackWhenDismiss) {
//         callbacks.sheetSpringBackFunc = [arkCallback = CallbackHelper(onWillSpringBackWhenDismiss.value())]() {
//             Ark_SpringBackAction parameter;
//             const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelNG::SheetSpringBackStatic));
//             parameter.springBack = keeper.ArkValue();
//             arkCallback.Invoke(parameter);
//         };
//     }
//     auto onHeightDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onHeightDidChange);
//     if (onHeightDidChange) {
//         callbacks.onHeightDidChangeCallback = [arkCallback = CallbackHelper(onHeightDidChange.value())](int32_t value) {
//             arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
//         };
//     }
//     auto onWidthDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onWidthDidChange);
//     if (onWidthDidChange) {
//         callbacks.onWidthDidChangeCallback = [arkCallback = CallbackHelper(onWidthDidChange.value())](int32_t value) {
//             arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
//         };
//     }
//     auto onDetentsDidChange = Converter::OptConvert<Callback_Number_Void>(sheetOptions.onDetentsDidChange);
//     if (onDetentsDidChange) {
//         callbacks.onDetentsDidChangeCallback = [arkCallback = CallbackHelper(onDetentsDidChange.value())](
//             int32_t value) {
//             arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
//         };
//     }
// };

// auto g_bindSheetParams = [](SheetStyle sheetStyle, const Ark_SheetOptions& sheetOptions) {
//     sheetStyle.showInPage = OptConvert<SheetLevel>(sheetOptions.mode).value_or(SheetLevel::EMBEDDED);
//     std::vector<SheetHeight> detents;
//     auto detentsOpt = OptConvert<Ark_Type_SheetOptions_detents>(sheetOptions.detents);
//     if (detentsOpt) {
//         auto value0 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value0);
//         if (value0) {
//             detents.emplace_back(value0.value());
//         }
//         auto value1 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value1);
//         if (value1) {
//             detents.emplace_back(value1.value());
//         }
//         auto value2 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value2);
//         if (value2) {
//             detents.emplace_back(value2.value());
//         }
//     }
//     sheetStyle.detents = detents;
//     sheetStyle.backgroundBlurStyle = OptConvert<BlurStyleOption>(sheetOptions.blurStyle);
//     sheetStyle.showCloseIcon = OptConvert<bool>(sheetOptions.showClose);
//     sheetStyle.interactive = OptConvert<bool>(sheetOptions.enableOutsideInteractive);
//     sheetStyle.showDragBar = OptConvert<bool>(sheetOptions.dragBar);
//     sheetStyle.sheetType = OptConvert<SheetType>(sheetOptions.preferType);
//     sheetStyle.scrollSizeMode = OptConvert<ScrollSizeMode>(sheetOptions.scrollSizeMode);
//     sheetStyle.sheetKeyboardAvoidMode = OptConvert<SheetKeyboardAvoidMode>(sheetOptions.keyboardAvoidMode);
//     sheetStyle.backgroundColor = OptConvert<Color>(sheetOptions.backgroundColor);
//     sheetStyle.maskColor = OptConvert<Color>(sheetOptions.maskColor);
//     sheetStyle.borderWidth = OptConvert<BorderWidthProperty>(sheetOptions.borderWidth);
//     sheetStyle.borderColor = OptConvert<BorderColorProperty>(sheetOptions.borderColor);
//     sheetStyle.borderStyle = OptConvert<BorderStyleProperty>(sheetOptions.borderStyle);
//     sheetStyle.shadow = OptConvert<Shadow>(sheetOptions.shadow);
//     sheetStyle.width = OptConvert<Dimension>(sheetOptions.width);
//     Validator::ValidateNonNegative(sheetStyle.width);
//     auto height = OptConvert<SheetHeight>(sheetOptions.height);
//     if (height) {
//         sheetStyle.sheetMode = height->sheetMode;
//         sheetStyle.height = height->height;
//     }
// };

// namespace Validator {
// void ValidateNonNegative(std::optional<InvertVariant>& value)
// {
//     if (!value.has_value()) {
//         return;
//     }
//     auto& invertVariant = value.value();
//     if (auto optionPtr = std::get_if<InvertOption>(&invertVariant)) {
//         const InvertOption& option = *optionPtr;
//         if (Negative(option.low_) || Negative(option.high_) ||
//             Negative(option.threshold_) || Negative(option.thresholdRange_)) {
//             value.reset();
//             return;
//         }
//     }
//     if (auto floatPtr = std::get_if<float>(&invertVariant)) {
//         if (Negative(*floatPtr)) {
//             value.reset();
//         }
//     }
// }
// void ValidateByRange(std::optional<InvertVariant>& value, const float& left, const float& right)
// {
//     if (!value.has_value()) {
//         return;
//     }
//     auto& invertVariant = value.value();
//     if (auto optionPtr = std::get_if<InvertOption>(&invertVariant)) {
//         const InvertOption& option = *optionPtr;
//         if (LessNotEqual(option.low_, left) || LessNotEqual(option.high_, left) ||
//             LessNotEqual(option.threshold_, left) || LessNotEqual(option.thresholdRange_, left) ||
//             GreatNotEqual(option.low_, right) || GreatNotEqual(option.high_, right) ||
//             GreatNotEqual(option.threshold_, right) || GreatNotEqual(option.thresholdRange_, right)) {
//             value.reset();
//             return;
//         }
//     }
//     if (auto floatPtr = std::get_if<float>(&invertVariant)) {
//         if (LessNotEqual(*floatPtr, left) || GreatNotEqual(*floatPtr, right)) {
//             value.reset();
//         }
//     }
// }
// } // namespace Validator

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

// template<>
// void AssignCast(std::optional<BackgroundImageSizeType>& dst, const Ark_ImageSize& src)
// {
//     switch (src) {
//         case ARK_IMAGE_SIZE_AUTO: dst = BackgroundImageSizeType::AUTO; break;
//         case ARK_IMAGE_SIZE_COVER: dst = BackgroundImageSizeType::COVER; break;
//         case ARK_IMAGE_SIZE_CONTAIN: dst = BackgroundImageSizeType::CONTAIN; break;
//         case ARK_IMAGE_SIZE_FILL: dst = BackgroundImageSizeType::FILL; break;
//         default: LOGE("Unexpected enum value in Ark_ImageSize: %{public}d", src);
//     }
// }

// template<>
// void AssignCast(std::optional<std::pair<double, double>>& dst, const Ark_Alignment& src)
// {
//     switch (src) {
//         case ARK_ALIGNMENT_TOP_START: dst = { 0.0, 0.0 }; break;
//         case ARK_ALIGNMENT_TOP: dst = { HALF_DIMENSION, 0.0 }; break;
//         case ARK_ALIGNMENT_TOP_END: dst = { FULL_DIMENSION, 0.0 }; break;
//         case ARK_ALIGNMENT_START: dst = { 0.0, HALF_DIMENSION }; break;
//         case ARK_ALIGNMENT_CENTER: dst = { HALF_DIMENSION, HALF_DIMENSION }; break;
//         case ARK_ALIGNMENT_END: dst = { FULL_DIMENSION, HALF_DIMENSION }; break;
//         case ARK_ALIGNMENT_BOTTOM_START: dst = { 0.0, FULL_DIMENSION }; break;
//         case ARK_ALIGNMENT_BOTTOM: dst = { HALF_DIMENSION, FULL_DIMENSION }; break;
//         case ARK_ALIGNMENT_BOTTOM_END: dst = { FULL_DIMENSION, FULL_DIMENSION }; break;
//         default: LOGE("Unexpected enum value in Ark_Alignment: %{public}d", src);
//     }
// }

// template<>
// MotionPathOption Convert(const Ark_MotionPathOptions& src)
// {
//     MotionPathOption p;
//     p.SetPath(Converter::Convert<std::string>(src.path));
//     if (auto opt = Converter::OptConvert<float>(src.from); opt) {
//         p.SetBegin(*opt);
//     }
//     if (auto opt = Converter::OptConvert<float>(src.to); opt) {
//         p.SetEnd(*opt);
//     }
//     if (auto opt = Converter::OptConvert<bool>(src.rotatable); opt) {
//         p.SetRotate(*opt);
//     }
//     return p;
// }

// template<>
// OHOS::Ace::SharedTransitionOption Convert(const Ark_sharedTransitionOptions& src)
// {
//     OHOS::Ace::SharedTransitionOption o = { .duration = INT_MIN };
//     if (auto opt = Converter::OptConvert<RefPtr<Curve>>(src.curve); opt) {
//         o.curve = *opt;
//     }
//     if (auto opt = Converter::OptConvert<int32_t>(src.duration); opt) {
//         o.duration = *opt;
//     }
//     if (auto opt = Converter::OptConvert<int32_t>(src.delay); opt) {
//         o.delay = *opt;
//     }
//     if (auto opt = Converter::OptConvert<MotionPathOption>(src.motionPath); opt) {
//         o.motionPathOption = *opt;
//     }
//     if (auto opt = Converter::OptConvert<int32_t>(src.zIndex); opt) {
//         o.zIndex = *opt;
//     }
//     if (auto opt = Converter::OptConvert<SharedTransitionEffectType>(src.type); opt) {
//         o.type = *opt;
//     }
//     return o;
// }

// template<>
// OffsetOrEdgesParam Convert(const Ark_Position& src)
// {
//     OffsetT<Dimension> offset;
//     std::optional<Dimension> x = Converter::OptConvert<Dimension>(src.x);
//     if (x) {
//         offset.SetX(x.value());
//     }
//     std::optional<Dimension> y = Converter::OptConvert<Dimension>(src.y);
//     if (y) {
//         offset.SetY(y.value());
//     }
//     return offset;
// }

// template<>
// OffsetOrEdgesParam Convert(const Ark_Edges& src)
// {
//     EdgesParamOptions edgesParamOptions;
//     edgesParamOptions.value = Converter::Convert<EdgesParam>(src);
//     edgesParamOptions.isLocalized = false;
//     return edgesParamOptions;
// }

// template<>
// OffsetOrEdgesParam Convert(const Ark_LocalizedEdges& src)
// {
//     return EdgesParamOptions {
//         .value = EdgesParam {
//             .top = OptConvert<Dimension>(src.top),
//             .left = OptConvert<Dimension>(src.start),
//             .bottom = OptConvert<Dimension>(src.bottom),
//             .right = OptConvert<Dimension>(src.end),
//             .start = OptConvert<Dimension>(src.start),
//             .end = OptConvert<Dimension>(src.end),
//         },
//         .isLocalized = true
//     };
// }

// template<>
// Gradient Convert(const Ark_Type_CommonMethod_radialGradient_value& src)
// {
//     NG::Gradient gradient;
//     gradient.CreateGradientWithType(NG::GradientType::RADIAL);

//     // center
//     auto centerX = Converter::Convert<Dimension>(src.center.value0);
//     if (centerX.Unit() == DimensionUnit::PERCENT) {
//         centerX = centerX * PERCENT_100;
//     }
//     gradient.GetRadialGradient()->radialCenterX = centerX;

//     auto centerY = Converter::Convert<Dimension>(src.center.value1);
//     if (centerY.Unit() == DimensionUnit::PERCENT) {
//         centerY = centerY * PERCENT_100;
//     }
//     gradient.GetRadialGradient()->radialCenterY = centerY;

//     // radius
//     std::optional<Dimension> radiusOpt = Converter::OptConvert<Dimension>(src.radius);
//     if (radiusOpt) {
//         // radius should be positive [0, +∞)
//         Dimension radius = radiusOpt.value().IsNonPositive() ? Dimension(0, DimensionUnit::VP) : radiusOpt.value();
//         gradient.GetRadialGradient()->radialVerticalSize = radius;
//         gradient.GetRadialGradient()->radialHorizontalSize = radius;
//     }

//     // repeating
//     std::optional<bool> repeating = Converter::OptConvert<bool>(src.repeating);
//     if (repeating) {
//         gradient.SetRepeat(repeating.value());
//     }

//     // color stops
//     std::vector<GradientColor> colorStops = Converter::Convert<std::vector<GradientColor>>(src.colors);
//     for (GradientColor gradientColor : colorStops) {
//         gradient.AddColor(gradientColor);
//     }

//     return gradient;
// }

// template<>
// BackgroundImageSize Convert(const Ark_SizeOptions& src)
// {
//     BackgroundImageSize imageSize;
//     CalcDimension width;
//     CalcDimension height;
//     auto widthOpt = Converter::OptConvert<Dimension>(src.width);
//     if (widthOpt) {
//         width = widthOpt.value();
//     }
//     auto heightOpt = Converter::OptConvert<Dimension>(src.height);
//     if (heightOpt) {
//         height = heightOpt.value();
//     }
//     double valueWidth = width.ConvertToPx();
//     double valueHeight = height.ConvertToPx();
//     BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
//     BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
//     if (width.Unit() == DimensionUnit::PERCENT) {
//         typeWidth = BackgroundImageSizeType::PERCENT;
//         valueWidth = width.Value();
//     }
//     if (height.Unit() == DimensionUnit::PERCENT) {
//         typeHeight = BackgroundImageSizeType::PERCENT;
//         valueHeight = height.Value();
//     }
//     imageSize.SetSizeTypeX(typeWidth);
//     imageSize.SetSizeValueX(valueWidth);
//     imageSize.SetSizeTypeY(typeHeight);
//     imageSize.SetSizeValueY(valueHeight);
//     return imageSize;
// }

// template<>
// BackgroundImageSize Convert(const Ark_ImageSize& src)
// {
//     auto sizeType = OptConvert<BackgroundImageSizeType>(src).value_or(BackgroundImageSizeType::AUTO);
//     BackgroundImageSize imageSize;
//     imageSize.SetSizeTypeX(sizeType);
//     imageSize.SetSizeTypeY(sizeType);
//     return imageSize;
// }

template<>
std::pair<std::optional<Dimension>, std::optional<Dimension>> Convert(const Ark_Position& src)
{
    auto x = OptConvert<Dimension>(src.x);
    auto y = OptConvert<Dimension>(src.y);
    return {x, y};
}

// template<>
// TranslateOpt Convert(const Ark_TranslateOptions& src)
// {
//     TranslateOpt translateOptions;
//     translateOptions.x = OptConvert<Dimension>(src.x);
//     translateOptions.y = OptConvert<Dimension>(src.y);
//     translateOptions.z = OptConvert<Dimension>(src.z);
//     return translateOptions;
// }

// template<>
// std::vector<DimensionRect> Convert(const Ark_Rectangle &src)
// {
//     return { Convert<DimensionRect>(src) };
// }

// using PixelRoundPolicyOneRule = bool; // let rule 'Ceil' is false, rool 'FLoor' is true

// template<>
// void AssignCast(std::optional<PixelRoundPolicyOneRule>& dst, const Ark_PixelRoundCalcPolicy& src)
// {
//     if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_CEIL) {
//         dst = false;
//     }
//     if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_FLOOR) {
//         dst = true;
//     }
// }

// template<>
// uint16_t Convert(const Ark_PixelRoundPolicy& src)
// {
//     uint16_t dst = 0;
//     if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.start); rule) {
//         auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_START : PixelRoundPolicy::FORCE_CEIL_START;
//         dst |= static_cast<uint16_t>(policy);
//     }
//     if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.end); rule) {
//         auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_END : PixelRoundPolicy::FORCE_CEIL_END;
//         dst |= static_cast<uint16_t>(policy);
//     }
//     if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.top); rule) {
//         auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_TOP : PixelRoundPolicy::FORCE_CEIL_TOP;
//         dst |= static_cast<uint16_t>(policy);
//     }
//     if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.bottom); rule) {
//         auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_BOTTOM : PixelRoundPolicy::FORCE_CEIL_BOTTOM;
//         dst |= static_cast<uint16_t>(policy);
//     }
//     return dst;
// }

// template<>
// float Convert(const Ark_ForegroundEffectOptions& src)
// {
//     return Convert<float>(src.radius);
// }

// template<>
// BlurStyleOption Convert(const Ark_ForegroundBlurStyleOptions& src)
// {
//     BlurStyleOption dst;
//     dst.colorMode = OptConvert<ThemeColorMode>(src.colorMode).value_or(dst.colorMode);
//     dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
//     if (auto scaleOpt = OptConvert<float>(src.scale); scaleOpt) {
//         dst.scale = static_cast<double>(*scaleOpt);
//     }
//     dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
//     return dst;
// }

// template<>
// OverlayOptions Convert(const Ark_OverlayOptions& src)
// {
//     OverlayOptions dst { .align = Alignment::TOP_LEFT};
//     auto align = Converter::OptConvert<Alignment>(src.align);
//     if (align) {
//         dst.align = align.value();
//     }
//     auto x = Converter::OptConvert<Dimension>(src.offset.value.x);
//     if (x) {
//         dst.x = x.value();
//     }
//     auto y = Converter::OptConvert<Dimension>(src.offset.value.y);
//     if (y) {
//         dst.y = y.value();
//     }
//     return dst;
// }

// template<>
// BorderWidthProperty Convert(const Ark_EdgeOutlineWidths& src)
// {
//     BorderWidthProperty dst;
//     dst.leftDimen = OptConvert<Dimension>(src.left);
//     Validator::ValidateNonNegative(dst.leftDimen);
//     dst.topDimen = OptConvert<Dimension>(src.top);
//     Validator::ValidateNonNegative(dst.topDimen);
//     dst.rightDimen = OptConvert<Dimension>(src.right);
//     Validator::ValidateNonNegative(dst.rightDimen);
//     dst.bottomDimen = OptConvert<Dimension>(src.bottom);
//     Validator::ValidateNonNegative(dst.bottomDimen);
//     dst.multiValued = true;
//     return dst;
// }

// template<>
// BorderRadiusProperty Convert(const Ark_OutlineRadiuses& src)
// {
//     BorderRadiusProperty dst;
//     dst.radiusTopLeft = OptConvert<Dimension>(src.topLeft);
//     dst.radiusTopRight = OptConvert<Dimension>(src.topRight);
//     dst.radiusBottomLeft = OptConvert<Dimension>(src.bottomLeft);
//     dst.radiusBottomRight = OptConvert<Dimension>(src.bottomRight);
//     dst.multiValued = true;
//     return dst;
// }

// template<>
// void AssignCast(std::optional<BorderStyle>& dst, const Ark_OutlineStyle& src)
// {
//     switch (src) {
//         case ARK_OUTLINE_STYLE_DOTTED: dst = BorderStyle::DOTTED; break;
//         case ARK_OUTLINE_STYLE_DASHED: dst = BorderStyle::DASHED; break;
//         case ARK_OUTLINE_STYLE_SOLID: dst = BorderStyle::SOLID; break;
//         default: LOGE("Unexpected enum value in Ark_OutlineStyle: %{public}d", src);
//     }
// }

// template<>
// BorderStyleProperty Convert(const Ark_OutlineStyle& src)
// {
//     BorderStyleProperty dst;
//     if (auto styleOpt = OptConvert<BorderStyle>(src); styleOpt) {
//         dst.SetBorderStyle(*styleOpt);
//     }
//     return dst;
// }

// template<>
// BorderStyleProperty Convert(const Ark_EdgeOutlineStyles& src)
// {
//     BorderStyleProperty dst;
//     dst.styleLeft = OptConvert<BorderStyle>(src.left);
//     dst.styleRight = OptConvert<BorderStyle>(src.right);
//     dst.styleTop = OptConvert<BorderStyle>(src.top);
//     dst.styleBottom = OptConvert<BorderStyle>(src.bottom);
//     dst.multiValued = true;
//     return dst;
// }
// template<>
// InvertVariant Convert(const Ark_Number& value)
// {
//     float fDst = Converter::Convert<float>(value);
//     return std::variant<float, InvertOption>(fDst);
// }
// template<>
// InvertVariant Convert(const Ark_InvertOptions& value)
// {
//     InvertOption invertOption = {
//         .low_ = Converter::Convert<float>(value.low),
//         .high_ = Converter::Convert<float>(value.high),
//         .threshold_ = Converter::Convert<float>(value.threshold),
//         .thresholdRange_ = Converter::Convert<float>(value.thresholdRange)};
//     return std::variant<float, InvertOption>(invertOption);
// }
// template<>
// float Convert(const Ark_InvertOptions& value)
// {
//     auto low = Converter::Convert<float>(value.low);
//     auto high = Converter::Convert<float>(value.high);
//     auto threshold = Converter::Convert<float>(value.threshold);
//     auto thresholdRange = Converter::Convert<float>(value.thresholdRange);
//     if (NearEqual(low, high) && NearEqual(low, threshold) && NearEqual(low, thresholdRange)) {
//         return low;
//     }
//     float invalidValue = -1.0;
//     return invalidValue;
// }
// template<>
// void AssignCast(std::optional<float>& dst, const Ark_InvertOptions& src)
// {
//     auto low = Converter::Convert<float>(src.low);
//     auto high = Converter::Convert<float>(src.high);
//     auto threshold = Converter::Convert<float>(src.threshold);
//     auto thresholdRange = Converter::Convert<float>(src.thresholdRange);
//     if (NearEqual(low, high) && NearEqual(low, threshold) && NearEqual(low, thresholdRange)) {
//         dst = low;
//         return;
//     }
//     dst.reset();
// }
// template<>
// void AssignCast(std::optional<PixStretchEffectOption>& dst, const Ark_PixelStretchEffectOptions& src)
// {
//     auto invalidValue = 0.0_vp;
//     auto top = OptConvert<Dimension>(src.top);
//     auto bottom = OptConvert<Dimension>(src.bottom);
//     auto left = OptConvert<Dimension>(src.left);
//     auto right = OptConvert<Dimension>(src.right);
//     if (!top.has_value() && !bottom.has_value() && !left.has_value() && !right.has_value()) {
//         dst = std::nullopt;
//         return;
//     }
//     dst = {.left = left.value_or(invalidValue), .top = top.value_or(invalidValue),
//         .right = right.value_or(invalidValue), .bottom = bottom.value_or(invalidValue)};
// }

// template<>
// PositionWithLocalization Convert(const Ark_Position& src)
// {
//     auto x = Converter::OptConvert<Dimension>(src.x);
//     auto y = Converter::OptConvert<Dimension>(src.y);
//     if (!x && !y) {
//         return PositionWithLocalization {std::nullopt, false};
//     }
//     auto offsetOpt = std::make_optional<OffsetT<Dimension>>();
//     if (x) {
//         offsetOpt->SetX(*x);
//     }
//     if (y) {
//         offsetOpt->SetY(*y);
//     }
//     return PositionWithLocalization {offsetOpt, false};
// }

// template<>
// PositionWithLocalization Convert(const Ark_LocalizedPosition& src)
// {
//     auto start = Converter::OptConvert<Dimension>(src.start);
//     auto top = Converter::OptConvert<Dimension>(src.top);
//     auto offsetOpt = std::make_optional<OffsetT<Dimension>>();
//     if (start.has_value()) {
//         offsetOpt->SetX(start.value());
//     }
//     if (top.has_value()) {
//         offsetOpt->SetY(top.value());
//     }
//     return PositionWithLocalization {offsetOpt, true};
// }

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

// template<>
// void AssignCast(std::optional<HorizontalAlign>& dst, const Ark_HorizontalAlign& src)
// {
//     switch (src) {
//         case ARK_HORIZONTAL_ALIGN_START: dst = HorizontalAlign::START; break;
//         case ARK_HORIZONTAL_ALIGN_END: dst = HorizontalAlign::END; break;
//         case ARK_HORIZONTAL_ALIGN_CENTER: dst = HorizontalAlign::CENTER; break;
//         default: LOGE("Unexpected enum value in Ark_HorizontalAlign: %{public}d", src);
//     }
// }

// template<>
// void AssignCast(std::optional<VerticalAlign>& dst, const Ark_VerticalAlign& src)
// {
//     switch (src) {
//         case ARK_VERTICAL_ALIGN_TOP: dst = VerticalAlign::TOP; break;
//         case ARK_VERTICAL_ALIGN_BOTTOM: dst = VerticalAlign::BOTTOM; break;
//         case ARK_VERTICAL_ALIGN_CENTER: dst = VerticalAlign::CENTER; break;
//         default: LOGE("Unexpected enum value in Ark_VerticalAlign: %{public}d", src);
//     }
// }

// template<>
// AlignRule Convert(const Ark_Literal_String_anchor_HorizontalAlign_align& src)
// {
//     AlignRule rule;
//     rule.anchor = Convert<std::string>(src.anchor);
//     auto align = OptConvert<HorizontalAlign>(src.align);
//     if (align.has_value()) {
//         rule.horizontal = align.value();
//     }
//     return rule;
// }

// template<>
// AlignRule Convert(const Ark_LocalizedHorizontalAlignParam& src)
// {
//     AlignRule rule;
//     rule.anchor = Convert<std::string>(src.anchor);
//     auto align = OptConvert<HorizontalAlign>(src.align);
//     if (align.has_value()) {
//         rule.horizontal = align.value();
//     }
//     return rule;
// }

// template<>
// AlignRule Convert(const Ark_Literal_String_anchor_VerticalAlign_align& src)
// {
//     AlignRule rule;
//     rule.anchor = Convert<std::string>(src.anchor);
//     auto align = OptConvert<VerticalAlign>(src.align);
//     if (align.has_value()) {
//         rule.vertical = align.value();
//     }
//     return rule;
// }

// template<>
// AlignRule Convert(const Ark_LocalizedVerticalAlignParam& src)
// {
//     AlignRule rule;
//     rule.anchor = Convert<std::string>(src.anchor);
//     auto align = OptConvert<VerticalAlign>(src.align);
//     if (align.has_value()) {
//         rule.vertical = align.value();
//     }
//     return rule;
// }

// template<>
// std::map<AlignDirection, AlignRule> Convert(const Ark_AlignRuleOption& src)
// {
//     std::map<AlignDirection, AlignRule> rulesMap;
//     auto rule = OptConvert<AlignRule>(src.left);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::LEFT] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.right);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::RIGHT] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.middle);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::MIDDLE] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.top);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::TOP] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.bottom);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::BOTTOM] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.center);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::CENTER] = rule.value();
//     }
//     return rulesMap;
// }

// template<>
// std::map<AlignDirection, AlignRule> Convert(const Ark_LocalizedAlignRuleOptions& src)
// {
//     std::map<AlignDirection, AlignRule> rulesMap;
//     auto rule = OptConvert<AlignRule>(src.start);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::START] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.end);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::END] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.middle);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::MIDDLE] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.top);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::TOP] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.bottom);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::BOTTOM] = rule.value();
//     }
//     rule = OptConvert<AlignRule>(src.center);
//     if (rule.has_value()) {
//         rulesMap[AlignDirection::CENTER] = rule.value();
//     }
//     return rulesMap;
// }

// template<>
// BiasOpt Convert(const Ark_Bias& src)
// {
//     BiasOpt bias;
//     bias.first = OptConvert<float>(src.horizontal);
//     bias.second = OptConvert<float>(src.vertical);
//     return bias;
// }

// template<>
// void AssignCast(std::optional<uint32_t>& dst, const Ark_FocusPriority& src)
// {
//     switch (src) {
//         case ARK_FOCUS_PRIORITY_AUTO: dst = FOCUS_PRIORITY_AUTO; break;
//         case ARK_FOCUS_PRIORITY_PRIOR: dst = FOCUS_PRIORITY_PRIOR; break;
//         case ARK_FOCUS_PRIORITY_PREVIOUS: dst = FOCUS_PRIORITY_PREVIOUS; break;
//         default: LOGE("Unexpected enum value in Ark_FocusPriority: %{public}d", src);
//     }
// }

// template<>
// FocusBoxStyle Convert(const Ark_FocusBoxStyle& src)
// {
//     FocusBoxStyle style;
//     style.strokeWidth = Converter::OptConvert<Dimension>(src.strokeWidth);
//     style.margin = Converter::OptConvert<Dimension>(src.margin);
//     return style;
// }

// template<>
// MotionBlurOption Convert(const Ark_MotionBlurOptions& src)
// {
//     MotionBlurOption options;
//     const float minValue = 0.0;
//     const float maxValue = 1.0;
//     options.radius = Convert<float>(src.radius);
//     if (LessNotEqual(options.radius, minValue)) {
//         options.radius = minValue;
//     }
//     options.anchor.x = Convert<float>(src.anchor.x);
//     if (LessNotEqual(options.anchor.x, minValue)) {
//         options.anchor.x = minValue;
//     }
//     if (GreatNotEqual(options.anchor.x, maxValue)) {
//         options.anchor.x = maxValue;
//     }
//     options.anchor.y = Convert<float>(src.anchor.y);
//     if (LessNotEqual(options.anchor.y, minValue)) {
//         options.anchor.y = minValue;
//     }
//     if (GreatNotEqual(options.anchor.y, maxValue)) {
//         options.anchor.y = maxValue;
//     }
//     return options;
// }

// template<>
// RotateOpt Convert(const Ark_RotateOptions& src)
// {
//     RotateOpt options;
//     options.vec5f.emplace_back(OptConvert<float>(src.x));
//     options.vec5f.emplace_back(OptConvert<float>(src.y));
//     options.vec5f.emplace_back(OptConvert<float>(src.z));
//     options.vec5f.emplace_back(OptConvert<float>(src.angle));
//     options.vec5f.emplace_back(OptConvert<float>(src.perspective));

//     auto centerX =  OptConvert<Dimension>(src.centerX);
//     auto centerY =  OptConvert<Dimension>(src.centerY);
//     if (centerX.has_value() && centerY.has_value()) {
//         auto center = DimensionOffset(centerX.value(), centerY.value());
//         auto centerZ =  OptConvert<Dimension>(src.centerZ);
//         if (centerZ.has_value()) {
//             center.SetZ(centerZ.value());
//         }
//         options.center = center;
//     }
//     return options;
// }

// template<>
// void AssignCast(std::optional<TransitionType>& dst, const Ark_TransitionType& src)
// {
//     switch (src) {
//         case ARK_TRANSITION_TYPE_ALL: dst = TransitionType::ALL; break;
//         case ARK_TRANSITION_TYPE_INSERT: dst = TransitionType::APPEARING; break;
//         case ARK_TRANSITION_TYPE_DELETE: dst = TransitionType::DISAPPEARING; break;
//         default: LOGE("Unexpected enum value in Opt_TransitionType: %{public}d", src);
//     }
// }

// template<>
// ScaleOptions Convert(const Ark_ScaleOptions& src)
// {
//     ScaleOptions scaleOptions;
//     auto coord = OptConvert<float>(src.x);
//     scaleOptions.xScale = coord.value_or(0.0);
//     coord = OptConvert<float>(src.y);
//     scaleOptions.yScale = coord.value_or(0.0);
//     coord = OptConvert<float>(src.z);
//     scaleOptions.zScale = coord.value_or(0.0);

//     auto center = OptConvert<Dimension>(src.centerX);
//     if (center.has_value()) {
//         scaleOptions.centerX = center.value();
//     }
//     center = OptConvert<Dimension>(src.centerY);
//     if (center.has_value()) {
//         scaleOptions.centerY = center.value();
//     }
//     return scaleOptions;
// }

// template<>
// RotateOptions Convert(const Ark_RotateOptions& src)
// {
//     RotateOptions rotateOptions;
//     auto coord = OptConvert<float>(src.x);
//     if (coord.has_value()) {
//         rotateOptions.xDirection = coord.value();
//     }
//     coord = OptConvert<float>(src.y);
//     if (coord.has_value()) {
//         rotateOptions.yDirection = coord.value();
//     }
//     coord = OptConvert<float>(src.z);
//     if (coord.has_value()) {
//         rotateOptions.zDirection = coord.value();
//     }
//     auto angle = OptConvert<float>(src.angle);
//     if (angle.has_value()) {
//         rotateOptions.angle = angle.value();
//     }
//     auto perspective = OptConvert<float>(src.perspective);
//     if (perspective.has_value()) {
//         rotateOptions.perspective = perspective.value();
//     }
//     auto center = OptConvert<Dimension>(src.centerX);
//     if (center.has_value()) {
//         rotateOptions.centerX = center.value();
//     }
//     center = OptConvert<Dimension>(src.centerY);
//     if (center.has_value()) {
//         rotateOptions.centerY = center.value();
//     }
//     center = OptConvert<Dimension>(src.centerZ);
//     if (center.has_value()) {
//         rotateOptions.centerZ = center.value();
//     }
//     return rotateOptions;
// }

// template<>
// TransitionOptions Convert(const Ark_TransitionOptions& src)
// {
//     TransitionOptions options;
//     auto type = OptConvert<TransitionType>(src.type);
//     if (type.has_value()) {
//         options.Type = type.value();
//     }
//     auto opacity = OptConvert<float>(src.opacity);
//     if (opacity.has_value()) {
//         options.UpdateOpacity(opacity.value());
//     }
//     auto translateOpt = Converter::OptConvert<TranslateOptions>(src.translate);
//     if (translateOpt.has_value()) {
//         options.UpdateTranslate(translateOpt.value());
//     }
//     auto scaleOpt = Converter::OptConvert<ScaleOptions>(src.scale);
//     if (scaleOpt.has_value()) {
//         options.UpdateScale(scaleOpt.value());
//     }
//     auto rotateOpt = Converter::OptConvert<RotateOptions>(src.rotate);
//     if (rotateOpt.has_value()) {
//         options.UpdateRotate(rotateOpt.value());
//     }
//     return options;
// }

// template<>
// GridSizeOpt Convert(const Ark_Number& src)
// {
//     GridSizeOpt options;
//     options.span = OptConvert<int32_t>(src);
//     Validator::ValidateNonNegative(options.span);
//     options.offset = 0;
//     return options;
// }

// template<>
// GridSizeOpt Convert(const Ark_Literal_Number_offset_span& src)
// {
//     GridSizeOpt options;
//     options.span = OptConvert<int32_t>(src.span);
//     Validator::ValidateNonNegative(options.span);
//     options.offset = OptConvert<int32_t>(src.offset);
//     return options;
// }
// template<>
// GradientDirection Convert(const Ark_GradientDirection& value)
// {
//     auto optVal = OptConvert<GradientDirection>(value);
//     return optVal.has_value() ? optVal.value() : GradientDirection::NONE;
// }
// template<>
// std::pair<float, float> Convert(const Ark_FractionStop& value)
// {
//     return std::make_pair(Convert<float>(value.value0), Convert<float>(value.value1));
// }
// template<>
// NG::LinearGradientBlurPara Convert(const Ark_LinearGradientBlurOptions& value)
// {
//     auto blurRadius = Dimension(0);
//     std::pair<float, float> pair;
//     std::vector<std::pair<float, float>> fractionStops;
//     auto fractionStopsVec = Convert<std::vector<Ark_FractionStop>>(value.fractionStops);
//     for (auto arkPair : fractionStopsVec) {
//         pair = Convert<std::pair<float, float>>(arkPair);
//         fractionStops.push_back(pair);
//     }
//     auto direction = Convert<GradientDirection>(value.direction);
//     return NG::LinearGradientBlurPara(blurRadius, fractionStops, direction);
// }
// template<>
// void AssignCast(std::optional<Matrix4>& dst, const Ark_CustomObject& src)
// {
//     LOGE("This converter is created for testing purposes only. Custom objects are not supported.");
//     double* row1 = (double*)src.pointers[0];
//     double* row2 = (double*)src.pointers[1];
//     double* row3 = (double*)src.pointers[2];
//     double* row4 = (double*)src.pointers[3];
//     if (!row1 || !row2 || !row3 || !row4) {
//         dst = std::nullopt;
//         return;
//     }
//     if (strcmp(src.kind, "Matrix4") != 0) {
//         dst = std::nullopt;
//         return;
//     }
//     double m11 = row1[0], m12 = row1[1], m13 = row1[2], m14 = row1[3],
//         m21 = row2[0], m22 = row2[1], m23 = row2[2], m24 = row2[3],
//         m31 = row3[0], m32 = row3[1], m33 = row3[2], m34 = row3[3],
//         m41 = row4[0], m42 = row4[1], m43 = row4[2], m44 = row4[3];
//     dst = Matrix4(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
// }
// template<>
// ClickEffectLevel Convert(const Ark_ClickEffectLevel& src)
// {
//     switch (src) {
//         case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_LIGHT:
//             return ClickEffectLevel::LIGHT;
//         case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_MIDDLE:
//             return ClickEffectLevel::MIDDLE;
//         case Ark_ClickEffectLevel::ARK_CLICK_EFFECT_LEVEL_HEAVY:
//             return ClickEffectLevel::HEAVY;
//         default:
//             return ClickEffectLevel::UNDEFINED;
//     }
// }
// template<>
// void AssignCast(std::optional<ClickEffectLevel>& dst, const Ark_ClickEffectLevel& src)
// {
//     auto arkVal = Convert<ClickEffectLevel>(src);
//     dst = arkVal == ClickEffectLevel::UNDEFINED ? std::nullopt :
//         std::optional<ClickEffectLevel>(arkVal);
// }
// template<>
// void AssignCast(std::optional<DragDropInfo>& dst, const Ark_DragItemInfo& src)
// {
//     LOGE("ARKOALA: Convert to [DragDropInfo.PixelMap] from [Ark_DragItemInfo] is not supported\n");
// }
// template<>
// void AssignCast(std::optional<DragDropInfo>& dst, const Ark_String& src)
// {
//     auto vDst = DragDropInfo();
//     vDst.extraInfo = Convert<std::string>(src);
//     dst = vDst;
// }

// template<>
// void AssignCast(std::optional<OHOS::Ace::ObscuredReasons>& dst, const Ark_ObscuredReasons& src)
// {
//     switch (src) {
//         case ARK_OBSCURED_REASONS_PLACEHOLDER: dst = ObscuredReasons::PLACEHOLDER; break;
//         default: LOGE("Unexpected enum value in Ark_ObscuredReasons: %{public}d", src);
//     }
// }

// template<>
//     void AssignCast(std::optional<uint32_t>& dst, const Ark_SafeAreaType& src)
// {
//     switch (src) {
//         case ARK_SAFE_AREA_TYPE_SYSTEM: dst = SAFE_AREA_TYPE_SYSTEM; break;
//         case ARK_SAFE_AREA_TYPE_CUTOUT: dst = SAFE_AREA_TYPE_CUTOUT; break;
//         case ARK_SAFE_AREA_TYPE_KEYBOARD: dst = SAFE_AREA_TYPE_KEYBOARD; break;
//         default: LOGE("Unexpected enum value in Ark_SafeAreaType: %{public}d", src);
//     }
// }

// template<>
//     void AssignCast(std::optional<uint32_t>& dst, const Ark_SafeAreaEdge& src)
// {
//     switch (src) {
//         case ARK_SAFE_AREA_EDGE_TOP: dst = SAFE_AREA_EDGE_TOP; break;
//         case ARK_SAFE_AREA_EDGE_BOTTOM: dst = SAFE_AREA_EDGE_BOTTOM; break;
//         case ARK_SAFE_AREA_EDGE_START: dst = SAFE_AREA_EDGE_START; break;
//         case ARK_SAFE_AREA_EDGE_END: dst = SAFE_AREA_EDGE_END; break;
//         default: LOGE("Unexpected enum value in Ark_SafeAreaEdge: %{public}d", src);
//     }
// }

// template<>
//     void AssignCast(std::optional<RenderFit>& dst, const Ark_RenderFit& src)
// {
//     switch (src) {
//         case ARK_RENDER_FIT_CENTER: dst = RenderFit::CENTER; break;
//         case ARK_RENDER_FIT_TOP: dst = RenderFit::TOP; break;
//         case ARK_RENDER_FIT_BOTTOM: dst = RenderFit::BOTTOM; break;
//         case ARK_RENDER_FIT_LEFT: dst = RenderFit::LEFT; break;
//         case ARK_RENDER_FIT_RIGHT: dst = RenderFit::RIGHT; break;
//         case ARK_RENDER_FIT_TOP_LEFT: dst = RenderFit::TOP_LEFT; break;
//         case ARK_RENDER_FIT_TOP_RIGHT: dst = RenderFit::TOP_RIGHT; break;
//         case ARK_RENDER_FIT_BOTTOM_LEFT: dst = RenderFit::BOTTOM_LEFT; break;
//         case ARK_RENDER_FIT_BOTTOM_RIGHT: dst = RenderFit::BOTTOM_RIGHT; break;
//         case ARK_RENDER_FIT_RESIZE_FILL: dst = RenderFit::RESIZE_FILL; break;
//         case ARK_RENDER_FIT_RESIZE_CONTAIN: dst = RenderFit::RESIZE_CONTAIN; break;
//         case ARK_RENDER_FIT_RESIZE_CONTAIN_TOP_LEFT: dst = RenderFit::RESIZE_CONTAIN_TOP_LEFT; break;
//         case ARK_RENDER_FIT_RESIZE_CONTAIN_BOTTOM_RIGHT: dst = RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT; break;
//         case ARK_RENDER_FIT_RESIZE_COVER: dst = RenderFit::RESIZE_COVER; break;
//         case ARK_RENDER_FIT_RESIZE_COVER_TOP_LEFT: dst = RenderFit::RESIZE_COVER_TOP_LEFT; break;
//         case ARK_RENDER_FIT_RESIZE_COVER_BOTTOM_RIGHT: dst = RenderFit::RESIZE_COVER_BOTTOM_RIGHT; break;
//         default: LOGE("Unexpected enum value in Ark_RenderFit: %{public}d", src);
//     }
// }
// template<>
// TransitionHierarchyStrategy Convert(const Ark_TransitionHierarchyStrategy& src)
// {
//     if (src == ARK_TRANSITION_HIERARCHY_STRATEGY_ADAPTIVE) {
//         return TransitionHierarchyStrategy::ADAPTIVE;
//     }
//     return TransitionHierarchyStrategy::NONE;
// }
// template<>
// GeometryTransitionOptions Convert(const Ark_GeometryTransitionOptions& src)
// {
//     GeometryTransitionOptions dst;
//     dst.follow = OptConvert<bool>(src.follow);
//     dst.hierarchyStrategy = OptConvert<TransitionHierarchyStrategy>(src.hierarchyStrategy);
//     return dst;
// }

// template<>
// RefPtr<NG::NGGestureRecognizer> Convert(const Ark_GestureRecognizer &src)
// {
//     if (src) {
//         return src->GetRecognizer();
//     }
//     return nullptr;
// }

// // this creates the peer for Materialized object. DO NOT FORGET TO RELEASE IT
// void AssignArkValue(Ark_GestureRecognizer &dst, const RefPtr<NG::NGGestureRecognizer>& src)
// {
//     auto accessor = GeneratedModifier::GetGestureRecognizerAccessor();
//     CHECK_NULL_VOID(accessor);
//     dst = accessor->ctor();
//     if (dst) {
//         dst->SetRecognizer(src);
//     }
// }
// void AssignArkValue(Ark_GestureInfo &dst, const GestureInfo &src)
// {
//     auto tagOpt = src.GetTag();
//     dst.tag = ArkValue<Opt_String>(tagOpt);
//     dst.type = ArkValue<Ark_GestureControl_GestureType>(src.GetType());
//     dst.isSystemGesture = ArkValue<Ark_Boolean>(src.IsSystemGesture());
// }

// template<>
// void AssignCast(std::optional<GestureJudgeResult> &dst, const Ark_GestureJudgeResult& src)
// {
//     switch (src) {
//         case ARK_GESTURE_JUDGE_RESULT_CONTINUE: dst = GestureJudgeResult::CONTINUE; break;
//         case ARK_GESTURE_JUDGE_RESULT_REJECT: dst = GestureJudgeResult::REJECT; break;
//         default: LOGE("Unexpected enum value in Ark_GestureJudgeResult: %{public}d", src);
//     }
// }

// template<>
// void AssignCast(std::optional<TouchTestStrategy>& dst, const Ark_TouchTestStrategy& src)
// {
//     switch (src) {
//         case ARK_TOUCH_TEST_STRATEGY_DEFAULT: dst = TouchTestStrategy::DEFAULT; break;
//         case ARK_TOUCH_TEST_STRATEGY_FORWARD_COMPETITION: dst = TouchTestStrategy::FORWARD_COMPETITION; break;
//         case ARK_TOUCH_TEST_STRATEGY_FORWARD: dst = TouchTestStrategy::FORWARD; break;
//         default: LOGE("Unexpected enum value in Ark_TouchTestStrategy: %{public}d", src);
//     }
// }

// template<>
// void AssignCast(std::optional<NG::TouchResult> &dst, const Ark_TouchResult& src)
// {
//     if (auto strategy = OptConvert<TouchTestStrategy>(src.strategy); strategy) {
//         dst = { .strategy = *strategy };
//         if (auto id = OptConvert<std::string>(src.id); id) {
//             dst->id = *id;
//         }
//     } else {
//         dst.reset();
//     }
// }


// void AssignArkValue(Ark_TouchTestInfo& dst, const OHOS::Ace::NG::TouchTestInfo& src)
// {
//     dst.windowX = ArkValue<Ark_Number>(src.windowPoint.GetX());
//     dst.windowY = ArkValue<Ark_Number>(src.windowPoint.GetY());
//     dst.parentX = ArkValue<Ark_Number>(src.currentCmpPoint.GetX());
//     dst.parentY = ArkValue<Ark_Number>(src.currentCmpPoint.GetY());
//     dst.x = ArkValue<Ark_Number>(src.subCmpPoint.GetX());
//     dst.y = ArkValue<Ark_Number>(src.subCmpPoint.GetY());
//     dst.rect = ArkValue<Ark_RectResult>(src.subRect);
//     dst.id = ArkValue<Ark_String>(src.id);
// }

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
// template<>
// void AssignCast(std::optional<Alignment>& dst, const Ark_Literal_Alignment_align& src)
// {
//     auto optAlign = Converter::OptConvert<Ark_Alignment>(src.align);
//     if (!optAlign.has_value()) {
//         dst = std::nullopt;
//         return;
//     }
//     switch (optAlign.value()) {
//         case ARK_ALIGNMENT_TOP_START: dst = Alignment::TOP_LEFT; break;
//         case ARK_ALIGNMENT_TOP: dst = Alignment::TOP_CENTER; break;
//         case ARK_ALIGNMENT_TOP_END: dst = Alignment::TOP_RIGHT; break;
//         case ARK_ALIGNMENT_START: dst = Alignment::CENTER_LEFT; break;
//         case ARK_ALIGNMENT_CENTER: dst = Alignment::CENTER; break;
//         case ARK_ALIGNMENT_END: dst = Alignment::CENTER_RIGHT; break;
//         case ARK_ALIGNMENT_BOTTOM_START: dst = Alignment::BOTTOM_LEFT; break;
//         case ARK_ALIGNMENT_BOTTOM: dst = Alignment::BOTTOM_CENTER; break;
//         case ARK_ALIGNMENT_BOTTOM_END: dst = Alignment::BOTTOM_RIGHT; break;
//         default:
//             dst = std::nullopt;
//     }
// }
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
void AssignArkValue(Ark_PreDragStatus& dst, const PreDragStatus& src)
{
    // switch (src) {
    //     case PreDragStatus::ACTION_DETECTING_STATUS: dst = ARK_PRE_DRAG_STATUS_ACTION_DETECTING_STATUS; break;
    //     case PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION:
    //         dst = ARK_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG_ACTION;
    //         break;
    //     case PreDragStatus::PREVIEW_LIFT_STARTED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_STARTED; break;
    //     case PreDragStatus::PREVIEW_LIFT_FINISHED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LIFT_FINISHED; break;
    //     case PreDragStatus::PREVIEW_LANDING_STARTED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_STARTED; break;
    //     case PreDragStatus::PREVIEW_LANDING_FINISHED: dst = ARK_PRE_DRAG_STATUS_PREVIEW_LANDING_FINISHED; break;
    //     case PreDragStatus::ACTION_CANCELED_BEFORE_DRAG: dst = ARK_PRE_DRAG_STATUS_ACTION_CANCELED_BEFORE_DRAG; break;
    //     default:
    //         dst = static_cast<Ark_PreDragStatus>(-1);
    //         LOGE("Unexpected enum value in PreDragStatus: %{public}d", src);
    //         break;
    // }
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
    // CHECK_NULL_RETURN(pipelineContext, 0);
    // return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
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
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        // if (result.GetDimensionContainsNegative().IsNegative()) {
        //     return;
        // }
        // CounterModelNG::SetWidth(frameNode, result);
    } else {
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
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        // if (result.GetDimensionContainsNegative().IsNegative()) {
        //     return;
        // }
        // CounterModelNG::SetHeight(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstract::SetHeight(frameNode, result);
    }
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Opt_DrawModifier* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!frameNode->IsSupportDrawModifier()) {
    //     return;
    // }
    // auto convValue = value ? Converter::OptConvert<Ark_DrawModifier>(*value) : std::nullopt;
    // if (!convValue) {
    //     return;
    // }
    // auto peer = convValue.value();
    // CHECK_NULL_VOID(peer);
    // if (!peer->drawModifier) {
    //     peer->drawModifier = AceType::MakeRefPtr<DrawModifier>();
    // }
    // peer->frameNode = AceType::WeakClaim(frameNode);
    // ViewAbstract::SetDrawModifier(frameNode, peer->drawModifier);
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Ark_Union_Array_Rectangle_Rectangle* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // if (auto convArray = Converter::OptConvert<std::vector<DimensionRect>>(*value); convArray) {
    //     ViewAbstract::SetResponseRegion(frameNode, *convArray);
    // } else {
    //     ViewAbstract::SetResponseRegion(frameNode, { DimensionRect() });
    // }
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Ark_Union_Array_Rectangle_Rectangle* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // if (auto convArray = Converter::OptConvert<std::vector<DimensionRect>>(*value); convArray) {
    //     ViewAbstract::SetMouseResponseRegion(frameNode, *convArray);
    // } else {
    //     ViewAbstract::SetMouseResponseRegion(frameNode, { DimensionRect() });
    // }
}
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
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto minWidth = Converter::OptConvert<CalcLength>(value->minWidth);
    // if (minWidth) {
    //     ViewAbstract::SetMinWidth(frameNode, minWidth.value());
    // }
    // auto minHeight = Converter::OptConvert<CalcLength>(value->minHeight);
    // if (minHeight) {
    //     ViewAbstract::SetMinHeight(frameNode, minHeight.value());
    // }
    // auto maxWidth = Converter::OptConvert<CalcLength>(value->maxWidth);
    // if (maxWidth) {
    //     ViewAbstract::SetMaxWidth(frameNode, maxWidth.value());
    // }
    // auto maxHeight = Converter::OptConvert<CalcLength>(value->maxHeight);
    // if (maxHeight) {
    //     ViewAbstract::SetMaxHeight(frameNode, maxHeight.value());
    // }
}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // ViewAbstract::SetTouchable(frameNode, static_cast<bool>(value));
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         Ark_HitTestMode value)
{
//     auto frameNode = reinterpret_cast<FrameNode *>(node);
//     CHECK_NULL_VOID(frameNode);
//     NG::HitTestMode hitTestModeNG = static_cast<NG::HitTestMode>(value);
//     ViewAbstract::SetHitTestMode(frameNode, hitTestModeNG);
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          const Callback_Array_TouchTestInfo_TouchResult* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onTouchTestFunc = [callback = CallbackHelper(*value)](
    //     const std::vector<NG::TouchTestInfo>& touchInfo
    // ) -> NG::TouchResult {
    //     std::vector<NG::TouchTestInfo> touchInfoUpd = touchInfo;
    //     for (auto &item: touchInfoUpd) {
    //         item.windowPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.windowPoint.GetX()));
    //         item.windowPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.windowPoint.GetY()));
    //         item.currentCmpPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.currentCmpPoint.GetX()));
    //         item.currentCmpPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.currentCmpPoint.GetY()));
    //         item.subCmpPoint.SetX(PipelineBase::Px2VpWithCurrentDensity(item.subCmpPoint.GetX()));
    //         item.subCmpPoint.SetY(PipelineBase::Px2VpWithCurrentDensity(item.subCmpPoint.GetY()));
    //         item.subRect.SetLeft(PipelineBase::Px2VpWithCurrentDensity(item.subRect.GetX()));
    //         item.subRect.SetTop(PipelineBase::Px2VpWithCurrentDensity(item.subRect.GetY()));
    //         item.subRect.SetWidth(PipelineBase::Px2VpWithCurrentDensity(item.subRect.Width()));
    //         item.subRect.SetHeight(PipelineBase::Px2VpWithCurrentDensity(item.subRect.Height()));
    //     }

    //     Converter::ArkArrayHolder<Array_TouchTestInfo> holder(touchInfoUpd);
    //     auto resultOpt =
    //         callback.InvokeWithOptConvertResult<NG::TouchResult, Ark_TouchResult, Callback_TouchResult_Void>(
    //             holder.ArkValue()
    //     );
    //     static const NG::TouchResult defaultRes{ NG::TouchTestStrategy::DEFAULT, "" };
    //     return resultOpt.value_or(defaultRes);
    // };
    // ViewAbstract::SetOnTouchTestFunc(frameNode, std::move(onTouchTestFunc));
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weight = Converter::OptConvert<float>(*value);
    // if (weight) {
    //     ViewAbstract::SetLayoutWeight(frameNode, weight.value());
    // }
}
void ChainWeightImpl(Ark_NativePointer node,
                     const Ark_ChainWeightOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // LayoutWeightPair layoutWeightPair(Converter::OptConvert<float>(value->horizontal),
    //                                   Converter::OptConvert<float>(value->vertical));
    // ViewAbstractModelNG::SetLayoutWeight(frameNode, layoutWeightPair);
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Length_LocalizedPadding* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // ViewAbstract::SetPadding(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void SafeAreaPaddingImpl(Ark_NativePointer node,
                         const Ark_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Converter::VisitUnion(*value,
    //     [frameNode](const Ark_Padding& value) {
    //         auto convValue = Converter::Convert<PaddingProperty>(value);
    //         ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
    //     },
    //     [frameNode](const Ark_LocalizedPadding& value) {
    //          LOGE("ARKOALA: CommonMethod::SafeAreaPaddingImpl: Ark_LocalizedPadding is not supported.\n");
    //         auto convValue = Converter::Convert<PaddingProperty>(value);
    //          ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
    //     },
    //     [frameNode](const Ark_LengthMetrics& value) {
    //         auto convValue = Converter::Convert<CalcLength>(value);
    //          ViewAbstract::SetSafeAreaPadding(frameNode, convValue);
    //     },
    //     []() {}
    // );
}
void MarginImpl(Ark_NativePointer node,
                const Ark_Union_Margin_Length_LocalizedMargin* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // ViewAbstract::SetMargin(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
    //     CounterModelNG::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    // } else {
    //     ViewAbstract::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    // }
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Ark_PixelRoundPolicy* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<uint16_t>(*value);
    // ViewAbstract::SetPixelRound(frameNode, convValue);
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Ark_Union_SizeOptions_ImageSize* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // ViewAbstract::SetBackgroundImageSize(frameNode, Converter::OptConvert<BackgroundImageSize>(*value));
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Ark_Union_Position_Alignment* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto varValue = Converter::OptConvert<BackgroundImagePositionType>(*value);
    // BackgroundImagePosition bgImgPosition;
    // AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    // double valueX = 0.0;
    // double valueY = 0.0;
    // DimensionUnit typeX = DimensionUnit::PX;
    // DimensionUnit typeY = DimensionUnit::PX;
    // if (varValue) {
    //     if (auto arkPosition = std::get_if<Ark_Position>(&varValue.value()); arkPosition) {
    //         auto position =
    //             Converter::Convert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(*arkPosition);
    //         CalcDimension x;
    //         CalcDimension y;
    //         if (position.first) {
    //             x = position.first.value();
    //         }
    //         if (position.second) {
    //             y = position.second.value();
    //         }
    //         valueX = x.ConvertToPx();
    //         valueY = y.ConvertToPx();
    //         if (x.Unit() == DimensionUnit::PERCENT) {
    //             valueX = x.Value();
    //             typeX = DimensionUnit::PERCENT;
    //         }
    //         if (y.Unit() == DimensionUnit::PERCENT) {
    //             valueY = y.Value();
    //             typeY = DimensionUnit::PERCENT;
    //         }
    //     } else if (auto arkAlign = std::get_if<Ark_Alignment>(&varValue.value()); arkAlign) {
    //         auto alignment = Converter::OptConvert<std::pair<double, double>>(*arkAlign);
    //         if (alignment) {
    //             bgImgPosition.SetIsAlign(true);
    //             typeX = DimensionUnit::PERCENT;
    //             typeY = DimensionUnit::PERCENT;
    //             valueX = alignment.value().first;
    //             valueY = alignment.value().second;
    //         }
    //     }
    // }
    // bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    // bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
    // ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<EffectOption>(*value);
    // ViewAbstract::SetBackgroundEffect(frameNode, convValue);
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // ImageResizableSlice convValue {};
    // convValue = Converter::OptConvert<ImageResizableSlice>(value->slice).value_or(convValue);
    // // lattice .. This parameter does not take effect for the backgroundImageResizable API.
    // ViewAbstract::SetBackgroundImageResizableSlice(frameNode, convValue);
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<float>(*value);
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetForegroundEffect(frameNode, convValue);
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_VisualEffect* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // //auto convValue = Converter::OptConvert<type_name>(*value);
    // //CommonMethodModelNG::SetVisualEffect(frameNode, convValue);
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundFilter(frameNode, convValue);
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetForegroundFilter(frameNode, convValue);
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetCompositingFilter(frameNode, convValue);
}
void OpacityImpl(Ark_NativePointer node,
                 const Ark_Union_Number_Resource* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto result = Converter::OptConvert<float>(*value);
    // if (result) {
    //     ViewAbstract::SetOpacity(frameNode, result.value());
    // }
}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto style = Converter::OptConvert<BorderStyleProperty>(value->style);
    // if (style) {
    //     ViewAbstract::SetBorderStyle(frameNode, style.value());
    // }
    // auto width = Converter::OptConvert<BorderWidthProperty>(value->width);
    // if (width) {
    //     ViewAbstract::SetBorderWidth(frameNode, width.value());
    // }
    // auto color = Converter::OptConvert<BorderColorProperty>(value->color);
    // if (color) {
    //     ViewAbstract::SetBorderColor(frameNode, color.value());
    // }
    // auto radius = Converter::OptConvert<BorderRadiusProperty>(value->radius);
    // if (radius) {
    //     ViewAbstract::SetBorderRadius(frameNode, radius.value());
    // }
    // auto dashGap = Converter::OptConvert<BorderWidthProperty>(value->dashGap);
    // if (dashGap) {
    //     ViewAbstract::SetDashGap(frameNode, dashGap.value());
    // }
    // auto dashWidth = Converter::OptConvert<BorderWidthProperty>(value->dashWidth);
    // if (dashWidth) {
    //     ViewAbstract::SetDashWidth(frameNode, dashWidth.value());
    // }
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Ark_Union_BorderStyle_EdgeStyles* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto style = Converter::OptConvert<BorderStyleProperty>(*value);
    // if (style) {
    //     ViewAbstract::SetBorderStyle(frameNode, style.value());
    // }
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto width = Converter::OptConvert<BorderWidthProperty>(*value);
    // if (width) {
    //     ViewAbstract::SetBorderWidth(frameNode, width.value());
    // }
}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto color = Converter::OptConvert<BorderColorProperty>(*value);
    // if (color) {
    //     ViewAbstract::SetBorderColor(frameNode, color.value());
    // }
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto radiuses = Converter::OptConvert<BorderRadiusProperty>(*value);
    // if (radiuses) {
    //     ViewAbstract::SetBorderRadius(frameNode, radiuses.value());
    // }
}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    // if (value->source.tag != Ark_Tag::ARK_TAG_UNDEFINED && value->source.value.selector == NUM_3) {
    //     Gradient gradient = Converter::Convert<Gradient>(value->source.value.value2);
    //     ViewAbstract::SetBorderImageGradient(frameNode, gradient);
    // } else {
    //     auto info = Converter::OptConvert<ImageSourceInfo>(value->source);
    //     if (info) {
    //         borderImage->SetSrc(info.value().GetSrc());
    //     }
    // }
    // auto repeat = Converter::OptConvert<BorderImageRepeat>(value->repeat);
    // if (repeat) {
    //     borderImage->SetRepeatMode(repeat.value());
    // }
    // auto fill = Converter::OptConvert<bool>(value->fill);
    // if (fill) {
    //     borderImage->SetNeedFillCenter(fill.value());
    // }
    // if (value->outset.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
    //     switch (value->outset.value.selector) {
    //         case CASE_0: {
    //             auto outset = Converter::OptConvert<Dimension>(value->outset.value.value0);
    //             if (outset) {
    //                 borderImage->SetEdgeOutset(BorderImageDirection::LEFT, outset.value());
    //                 borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, outset.value());
    //                 borderImage->SetEdgeOutset(BorderImageDirection::TOP, outset.value());
    //                 borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, outset.value());
    //             }
    //             break;
    //         }
    //         case CASE_1: {
    //             auto left = Converter::OptConvert<Dimension>(value->outset.value.value1.left);
    //             auto top = Converter::OptConvert<Dimension>(value->outset.value.value1.top);
    //             auto right = Converter::OptConvert<Dimension>(value->outset.value.value1.right);
    //             auto bottom = Converter::OptConvert<Dimension>(value->outset.value.value1.bottom);
    //             if (left) {
    //                 borderImage->SetEdgeOutset(BorderImageDirection::LEFT, left.value());
    //             }
    //             if (top) {
    //                 borderImage->SetEdgeOutset(BorderImageDirection::TOP, top.value());
    //             }
    //             if (right) {
    //                 borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, right.value());
    //             }
    //             if (bottom) {
    //                 borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, bottom.value());
    //             }
    //             break;
    //         }
    //         case CASE_2:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
    //             break;
    //         default:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
    //                 value->outset.value.selector);
    //             return;
    //     }
    // }
    // if (value->slice.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
    //     switch (value->slice.value.selector) {
    //         case CASE_0: {
    //             auto slice = Converter::OptConvert<Dimension>(value->slice.value.value0);
    //             if (slice) {
    //                 borderImage->SetEdgeSlice(BorderImageDirection::LEFT, slice.value());
    //                 borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, slice.value());
    //                 borderImage->SetEdgeSlice(BorderImageDirection::TOP, slice.value());
    //                 borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, slice.value());
    //             }
    //             break;
    //         }
    //         case CASE_1: {
    //             auto left = Converter::OptConvert<Dimension>(value->slice.value.value1.left);
    //             auto top = Converter::OptConvert<Dimension>(value->slice.value.value1.top);
    //             auto right = Converter::OptConvert<Dimension>(value->slice.value.value1.right);
    //             auto bottom = Converter::OptConvert<Dimension>(value->slice.value.value1.bottom);
    //             if (left) {
    //                 borderImage->SetEdgeSlice(BorderImageDirection::LEFT, left.value());
    //             }
    //             if (top) {
    //                 borderImage->SetEdgeSlice(BorderImageDirection::TOP, top.value());
    //             }
    //             if (right) {
    //                 borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, right.value());
    //             }
    //             if (bottom) {
    //                 borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, bottom.value());
    //             }
    //             break;
    //         }
    //         case CASE_2:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
    //             break;
    //         default:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
    //                 value->slice.value.selector);
    //             return;
    //     }
    // }
    // if (value->width.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
    //     switch (value->width.value.selector) {
    //         case CASE_0: {
    //             auto width = Converter::OptConvert<Dimension>(value->width.value.value0);
    //             if (width) {
    //                 borderImage->SetEdgeWidth(BorderImageDirection::LEFT, width.value());
    //                 borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, width.value());
    //                 borderImage->SetEdgeWidth(BorderImageDirection::TOP, width.value());
    //                 borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, width.value());
    //             }
    //             break;
    //         }
    //         case CASE_1: {
    //             auto left = Converter::OptConvert<Dimension>(value->width.value.value1.left);
    //             auto top = Converter::OptConvert<Dimension>(value->width.value.value1.top);
    //             auto right = Converter::OptConvert<Dimension>(value->width.value.value1.right);
    //             auto bottom = Converter::OptConvert<Dimension>(value->width.value.value1.bottom);
    //             if (left) {
    //                 borderImage->SetEdgeWidth(BorderImageDirection::LEFT, left.value());
    //             }
    //             if (top) {
    //                 borderImage->SetEdgeWidth(BorderImageDirection::TOP, top.value());
    //             }
    //             if (right) {
    //                 borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, right.value());
    //             }
    //             if (bottom) {
    //                 borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, bottom.value());
    //             }
    //             break;
    //         }
    //         case CASE_2:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
    //             break;
    //         default:
    //             LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
    //                 value->slice.value.selector);
    //             return;
    //     }
    // }
    // ViewAbstract::SetBorderImage(frameNode, borderImage);
}

void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto borderWidthOpt = Converter::OptConvert<BorderWidthProperty>(value->width);
    // ViewAbstract::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));

    // auto borderRadiusOpt = Converter::OptConvert<BorderRadiusProperty>(value->radius);
    // ViewAbstract::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));

    // auto borderColorsOpt = Converter::OptConvert<BorderColorProperty>(value->color);
    // ViewAbstract::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));

    // auto borderStylesOpt = Converter::OptConvert<BorderStyleProperty>(value->style);
    // ViewAbstract::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Ark_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto borderStylesOpt = Converter::OptConvert<BorderStyleProperty>(*value);
    // ViewAbstract::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Ark_Union_Dimension_EdgeOutlineWidths* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto borderWidthOpt = Converter::OptConvert<BorderWidthProperty>(*value);
    // ViewAbstract::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));
}
void OutlineColorImpl(Ark_NativePointer node,
                      const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto borderColorsOpt = Converter::OptConvert<BorderColorProperty>(*value);
    // ViewAbstract::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));
}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Ark_Union_Dimension_OutlineRadiuses* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto borderRadiusOpt = Converter::OptConvert<BorderRadiusProperty>(*value);
    // ViewAbstract::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));
}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceColor_ColoringStrategy* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Converter::VisitUnion(*value,
    //     [frameNode](const Ark_ResourceColor& resourceColor) {
    //         auto colorOpt = Converter::OptConvert<Color>(resourceColor);
    //         ViewAbstract::SetForegroundColor(frameNode, colorOpt);
    //     },
    //     [frameNode](const Ark_ColoringStrategy& colorStrategy) {
    //         auto colorStrategyOpt = Converter::OptConvert<ForegroundColorStrategy>(colorStrategy);
    //         ViewAbstract::SetForegroundColorStrategy(frameNode, colorStrategyOpt);
    //     },
    //     []() {}
    // );
}
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
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!value) {
    //     ViewAbstract::DisableOnHover(frameNode);
    //     return;
    // }
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onHover = [arkCallback = CallbackHelper(*value), node = weakNode](bool isHover, HoverInfo& hoverInfo) {
    //     PipelineContext::SetCallBackNode(node);
    //     Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
    //     const auto event = Converter::ArkHoverEventSync(hoverInfo);
    //     arkCallback.InvokeSync(arkIsHover, event.ArkValue());
    // };
    // ViewAbstract::SetOnHover(frameNode, std::move(onHover));
}
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
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto hoverEffect = Converter::OptConvert<OHOS::Ace::HoverEffectType>(value);
    // if (hoverEffect) {
    //     ViewAbstract::SetHoverEffect(frameNode, hoverEffect.value());
    // }
}
void OnMouseImpl(Ark_NativePointer node,
                 const Callback_MouseEvent_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!value) {
    //     return ViewAbstract::DisableOnMouse(frameNode);
    // }
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onMouse = [arkCallback = CallbackHelper(*value), node = weakNode](MouseInfo& mouseInfo) {
    //     PipelineContext::SetCallBackNode(node);
    //     const auto event = Converter::ArkMouseEventSync(mouseInfo);
    //     arkCallback.InvokeSync(event.ArkValue());
    // };
    // ViewAbstract::SetOnMouse(frameNode, std::move(onMouse));
}
void OnTouchImpl(Ark_NativePointer node,
                 const Callback_TouchEvent_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onEvent = [callback = CallbackHelper(*value)](TouchEventInfo& info) {
    //     const auto event = Converter::ArkTouchEventSync(info);
    //     callback.InvokeSync(event.ArkValue());
    // };
    // ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEventImpl(Ark_NativePointer node,
                    const Callback_KeyEvent_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!value) {
    //     ViewAbstract::DisableOnKeyEvent(frameNode);
    // } else {
    //     auto weakNode = AceType::WeakClaim(frameNode);
    //     auto onKeyEvent = [arkCallback = CallbackHelper(*value), node = weakNode](KeyEventInfo& info) -> bool {
    //         PipelineContext::SetCallBackNode(node);
    //         const auto event = Converter::ArkKeyEventSync(info);
    //         arkCallback.InvokeSync(event.ArkValue());
    //         return false;
    //     };
    //     ViewAbstract::SetOnKeyEvent(frameNode, std::move(onKeyEvent));
    // }
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Callback_KeyEvent_Boolean* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!value) {
    //     ViewAbstractModelNG::DisableOnKeyPreIme(frameNode);
    // } else {
    //     auto weakNode = AceType::WeakClaim(frameNode);
    //     auto onKeyPreImeEvent = [arkCallback = CallbackHelper(*value), node = weakNode](KeyEventInfo& info)
    //         -> bool {
    //         PipelineContext::SetCallBackNode(node);
    //         const auto event = Converter::ArkKeyEventSync(info);
    //         auto arkResult = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(event.ArkValue());
    //         return Converter::Convert<bool>(arkResult);
    //     };
    //     ViewAbstractModelNG::SetOnKeyPreIme(frameNode, std::move(onKeyPreImeEvent));
    // }
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // ViewAbstract::SetFocusable(frameNode, static_cast<bool>(value));
}
void OnFocusImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onEvent = [arkCallback = CallbackHelper(*value)]() {
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onEvent = [arkCallback = CallbackHelper(*value)]() {
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnBlur(frameNode, std::move(onEvent));
}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<int32_t>(*value);
    // ViewAbstract::SetTabIndex(frameNode, convValue);
}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetDefaultFocus(frameNode, convValue);
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetGroupDefaultFocus(frameNode, convValue);
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetFocusOnTouch(frameNode, convValue);
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // LOGE("ARKOALA: CommonMethod::FocusBoxImpl: Ark_FocusBoxStyle.CustomObject is not supported.\n");
    // auto convValue = Converter::OptConvert<NG::FocusBoxStyle>(*value);
    // ViewAbstract::SetFocusBoxStyle(frameNode, convValue);
}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);

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

    // if (value) {
    //     AnimationOption option = Converter::Convert<AnimationOption>(*value);
    //     // Validator::ValidateAnimationOption(option, pipelineContextBase->IsFormRender());

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
void Transition0Impl(Ark_NativePointer node,
                     const Ark_Union_TransitionOptions_TransitionEffect* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Converter::VisitUnion(*value,
    //     [frameNode](const Ark_TransitionOptions& value) {
    //         auto convValue = Converter::Convert<TransitionOptions>(value);
    //         ViewAbstract::SetTransition(frameNode, convValue);
    //     },
    //     [frameNode](const Ark_TransitionEffect& value) {
    //         auto convValue = Converter::Convert<RefPtr<NG::ChainedTransitionEffect>>(value);
    //          ViewAbstract::SetChainedTransition(frameNode, convValue);
    //     },
    //     []() {}
    // );
}
void Transition1Impl(Ark_NativePointer node,
                     Ark_TransitionEffect effect,
                     const Opt_TransitionFinishCallback* onFinish)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(effect);
    // std::function<void(bool)> finishCallback;
    // if (onFinish) {
    //     auto arkOnFinish = Converter::OptConvert<::TransitionFinishCallback>(*onFinish);
    //     if (arkOnFinish) {
    //             finishCallback = [callback = CallbackHelper(*arkOnFinish)](bool transitionIn) {
    //                 callback.Invoke(Converter::ArkValue<Ark_Boolean>(transitionIn));
    //             };
    //     }
    // }
    // auto effectPeer = effect;
    // if (effectPeer && effectPeer->handler) {
    //     ViewAbstract::SetChainedTransition(frameNode, effectPeer->handler, std::move(finishCallback));
    // } else {
    //     ViewAbstract::CleanTransition(frameNode);
    // }
}

void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<MotionBlurOption>(*value);
    // ViewAbstract::SetMotionBlur(frameNode, convValue);
}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetBrightness(frameNode, convValue);
}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetContrast(frameNode, convValue);
}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetGrayScale(frameNode, convValue);
}
void ColorBlendImpl(Ark_NativePointer node,
                    const Ark_Union_Color_String_Resource* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<Color>(*value) : std::nullopt;
    // ViewAbstract::SetColorBlend(frameNode, convValue);
}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetSaturate(frameNode, convValue);
}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetSepia(frameNode, convValue);
}
void InvertImpl(Ark_NativePointer node,
                const Ark_Union_Number_InvertOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // const float minValue = 0.0;
    // const float maxValue = 100.0;
    // auto convValue = value ? Converter::OptConvert<InvertVariant>(*value) : std::nullopt;
    // Validator::ValidateByRange(convValue, minValue, maxValue);
    // ViewAbstract::SetInvert(frameNode, convValue);
}
void HueRotateImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    // ViewAbstract::SetHueRotate(frameNode, convValue);
}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode*>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetUseShadowBatching(frameNode, convValue);
}
void UseEffect0Impl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetUseEffect(frameNode, convValue);
}
void UseEffect1Impl(Ark_NativePointer node,
                    Ark_Boolean useEffect,
                    Ark_EffectType effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(useEffect);
    //auto convValue = Converter::OptConvert<type>(useEffect); // for enums
    //CommonMethodModelNG::SetUseEffect1(frameNode, convValue);
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetRenderGroup(frameNode, convValue);
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetFreeze(frameNode, convValue);
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);

    // TranslateOpt options = Converter::Convert<TranslateOpt>(*value);

    // CalcDimension x = options.x.value_or(CalcDimension(0.0));
    // CalcDimension y = options.y.value_or(CalcDimension(0.0));
    // CalcDimension z = options.z.value_or(CalcDimension(0.0));
    // ViewAbstract::SetTranslate(frameNode, TranslateOptions(x, y, z));
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);

    // ScaleOpt scaleOptions = Converter::Convert<ScaleOpt>(*value);

    // float scaleX = scaleOptions.x.value_or(1.0f);
    // float scaleY = scaleOptions.y.value_or(1.0f);
    // ViewAbstract::SetScale(frameNode, VectorF(scaleX, scaleY));

    // CalcDimension centerX = scaleOptions.centerX.value_or(0.5_pct);
    // CalcDimension centerY = scaleOptions.centerY.value_or(0.5_pct);
    // ViewAbstract::SetPivot(frameNode, DimensionOffset(centerX, centerY));
}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetGrid(frameNode, convValue, std::nullopt, GridSizeType::UNDEFINED);
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    // Validator::ValidateNonNegative(convValue);
    // ViewAbstract::SetGrid(frameNode, std::nullopt, convValue, GridSizeType::UNDEFINED);
}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<RotateOpt>(*value);
    // ViewAbstract::SetPivot(frameNode, convValue.center);
    // ViewAbstract::SetRotate(frameNode, convValue.vec5f);
}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<Matrix4>(*value) : std::nullopt;
    // ViewAbstract::SetTransformMatrix(frameNode, convValue);
}
void OnAppearImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onEvent = [arkCallback = CallbackHelper(*value)]() {
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onEvent = [arkCallback = CallbackHelper(*value)]() {
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onAttach = [arkCallback = CallbackHelper(*value), node = weakNode]() {
    //     PipelineContext::SetCallBackNode(node);
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnAttach(frameNode, std::move(onAttach));
}
void OnDetachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onDetach = [arkCallback = CallbackHelper(*value), node = weakNode]() {
    //     PipelineContext::SetCallBackNode(node);
    //     arkCallback.Invoke();
    // };
    // ViewAbstract::SetOnDetach(frameNode, std::move(onDetach));
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      const Callback_Area_Area_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onEvent = [arkCallback = CallbackHelper(*value), node = weakNode](
    //     const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin) {
    //     PipelineContext::SetCallBackNode(node);

    //     auto previousOffset = oldRect.GetOffset();
    //     Ark_Area previous;
    //     previous.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
    //     previous.height = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
    //     previous.position.x = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX()));
    //     previous.position.y = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY()));
    //     previous.globalPosition.x = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetX() + oldOrigin.GetX()));
    //     previous.globalPosition.y = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(previousOffset.GetY() + oldOrigin.GetY()));

    //     auto currentOffset = rect.GetOffset();
    //     Ark_Area current;
    //     current.width = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Width()));
    //     current.height = Converter::ArkValue<Ark_Length>(PipelineBase::Px2VpWithCurrentDensity(rect.Height()));
    //     current.position.x = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX()));
    //     current.position.y = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY()));
    //     current.globalPosition.x = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetX() + origin.GetX()));
    //     current.globalPosition.y = Converter::ArkValue<Opt_Length>(
    //         PipelineBase::Px2VpWithCurrentDensity(currentOffset.GetY() + origin.GetY()));

    //     arkCallback.Invoke(previous, current);
    // };
    // auto areaChangeCallback = [areaChangeFunc = std::move(onEvent)](const RectF& oldRect,
    //                               const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
    //     areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
    //         Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
    //         Offset(origin.GetX(), origin.GetY()));
    // };
    // ViewAbstract::SetOnAreaChanged(frameNode, std::move(areaChangeCallback));
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(value));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<float>(*value);
    // ViewAbstract::SetFlexGrow(frameNode, convValue);
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<float>(*value);
    // ViewAbstract::SetFlexShrink(frameNode, convValue);
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<Dimension>(*value);
    // Validator::ValidateNonNegative(convValue);
    // Validator::ValidateNonPercent(convValue);
    // ViewAbstract::SetFlexBasis(frameNode, convValue);
}
void AlignSelfImpl(Ark_NativePointer node,
                   Ark_ItemAlign value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto align = Converter::OptConvert<OHOS::Ace::FlexAlign>(value);
    // if (align) {
    //     ViewAbstract::SetAlignSelf(frameNode, align.value());
    // }
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto result = Converter::OptConvert<int>(*value);
    // if (result) {
    //     ViewAbstract::SetDisplayIndex(frameNode, result.value());
    // }
}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto result = Converter::OptConvert<int>(*value);
    // if (result) {
    //     ViewAbstract::SetZIndex(frameNode, result.value());
    // }
}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Direction value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto direction = Converter::OptConvert<TextDirection>(value);
    // if (direction) {
    //     ViewAbstract::SetLayoutDirection(frameNode, direction.value());
    // }
}
void AlignImpl(Ark_NativePointer node,
               Ark_Alignment value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto alignment = Converter::OptConvert<Alignment>(value);
    // if (alignment) {
    //     ViewAbstract::SetAlign(frameNode, alignment.value());
    // }
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // switch (value->selector) {
    //     case CASE_0: {
    //         auto x = Converter::ConvertOrDefault(value->value0.x, Dimension());
    //         auto y = Converter::ConvertOrDefault(value->value0.y, Dimension());
    //         ViewAbstract::SetPosition(frameNode, { x, y });
    //         break;
    //     }
    //     case CASE_1: {
    //         auto result = Converter::ConvertOrDefault(value->value1, EdgesParam());
    //         ViewAbstract::SetPositionEdges(frameNode, result);
    //         break;
    //     }
    //     case CASE_2:
    //         LOGE("ARKOALA: LocalizedEdges is not fully support.");
    //         ViewAbstract::SetPositionLocalizedEdges(frameNode, true);
    //         break;

    //     default:
    //         LOGE("ARKOALA:PositionImpl: Unexpected value->selector: %{public}d\n", value->selector);
    //         return;
    // }
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Union_Position_LocalizedPosition* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto anchorOpt = Converter::OptConvert<PositionWithLocalization>(*value);
    // if (anchorOpt) {
    //     if (anchorOpt->second && anchorOpt->first.has_value()) {
    //         ViewAbstract::SetMarkAnchorStart(frameNode, anchorOpt->first->GetX());
    //         ViewAbstract::MarkAnchor(frameNode, anchorOpt->first);
    //         return;
    //     }
    //     ViewAbstract::MarkAnchor(frameNode, anchorOpt->first);
    // } else {
    //     ViewAbstract::MarkAnchor(frameNode, std::nullopt);
    // }
    // ViewAbstract::ResetMarkAnchorStart(frameNode);
}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto varOpt = Converter::OptConvert<OffsetOrEdgesParam>(*value);
    // CHECK_NULL_VOID(varOpt);
    // if (auto offset = std::get_if<std::optional<OffsetT<Dimension>>>(&varOpt.value()); offset) {
    //     ViewAbstract::SetOffset(frameNode, offset->value());
    // } else if (auto edges = std::get_if<std::optional<EdgesParamOptions>>(&varOpt.value()); edges) {
    //     ViewAbstract::SetOffsetEdges(frameNode, edges->value().value);
    //     ViewAbstract::SetOffsetLocalizedEdges(frameNode, edges->value().isLocalized);
    // } else {
    //     LOGE("ARKOALA CommonMethod::OffsetImpl: incorrect value");
    // }
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // ViewAbstract::SetEnabled(frameNode, static_cast<bool>(value));
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);

    // auto gridSizeOpt = Converter::OptConvert<GridSizeOpt>(value->xs);
    // if (gridSizeOpt.has_value()) {
    //     ViewAbstract::SetGrid(frameNode, gridSizeOpt.value().span, gridSizeOpt.value().offset, GridSizeType::XS);
    // }
    // gridSizeOpt = Converter::OptConvert<GridSizeOpt>(value->sm);
    // if (gridSizeOpt.has_value()) {
    //     ViewAbstract::SetGrid(frameNode, gridSizeOpt.value().span, gridSizeOpt.value().offset, GridSizeType::SM);
    // }
    // gridSizeOpt = Converter::OptConvert<GridSizeOpt>(value->md);
    // if (gridSizeOpt.has_value()) {
    //     ViewAbstract::SetGrid(frameNode, gridSizeOpt.value().span, gridSizeOpt.value().offset, GridSizeType::MD);
    // }
    // gridSizeOpt= Converter::OptConvert<GridSizeOpt>(value->lg);
    // if (gridSizeOpt.has_value()) {
    //     ViewAbstract::SetGrid(frameNode, gridSizeOpt.value().span, gridSizeOpt.value().offset, GridSizeType::LG);
    // }
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convMapValue = Converter::OptConvert<std::map<AlignDirection, AlignRule>>(*value);
    // ViewAbstract::SetAlignRules(frameNode, convMapValue);
    // auto convBiasValue = Converter::OptConvert<BiasOpt>(value->bias);
    // if (convBiasValue.has_value()) {
    //     ViewAbstract::SetBias(frameNode, convBiasValue.value().first, convBiasValue.value().second);
    // } else {
    //     ViewAbstract::SetBias(frameNode, std::nullopt);
    // }
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convMapValue = Converter::OptConvert<std::map<AlignDirection, AlignRule>>(*value);
    // ViewAbstract::SetAlignRules(frameNode, convMapValue);
    // auto convBiasValue = Converter::OptConvert<BiasOpt>(value->bias);
    // if (convBiasValue.has_value()) {
    //     ViewAbstract::SetBias(frameNode, convBiasValue.value().first, convBiasValue.value().second);
    // } else {
    //     ViewAbstract::SetBias(frameNode, std::nullopt);
    // }
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto result = Converter::OptConvert<float>(*value);
    // if (result) {
    //     auto ratio = result.value();
    //     if (ratio <= 0.0) {
    //         if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
    //             ViewAbstract::ResetAspectRatio(frameNode);
    //             return;
    //         } else {
    //             ratio = 1.0;
    //         }
    //     }
    //     ViewAbstract::SetAspectRatio(frameNode, ratio);
    // }
}
void ClickEffectImpl(Ark_NativePointer node,
                     const Opt_ClickEffect* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<Ark_ClickEffect>(*value) : std::nullopt;
    // if (!convValue.has_value()) {
    //     ViewAbstract::SetClickEffectLevel(frameNode, std::nullopt, std::nullopt);
    //     return;
    // }
    // const std::optional<ClickEffectLevel>& level = Converter::OptConvert<ClickEffectLevel>(convValue.value().level);
    // const std::optional<float> scaleValue = Converter::OptConvert<float>(convValue.value().scale);
    // ViewAbstract::SetClickEffectLevel(frameNode, level, scaleValue);
}
void OnDragStartImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onDragStart = [callback = CallbackHelper(*value), weakNode]
    //     (const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) -> DragDropInfo {
    //     DragDropInfo result;
    //     CHECK_NULL_RETURN(info, result);
    //     auto arkDragInfo = Converter::ArkValue<Ark_DragEvent>(info);
    //     auto arkExtraParam = Converter::ArkValue<Opt_String>(extraParams);

    //     auto parseBuilder = [&result, weakNode](const CustomNodeBuilder& val) {
    //         if (auto frameNode = weakNode.Upgrade(); frameNode) {
    //             result.customNode = CallbackHelper(val).BuildSync(frameNode.GetRawPtr());
    //         }
    //     };
    //     auto parseItemInfo = [&result, weakNode](const Ark_DragItemInfo& value) {
    //         result.pixelMap = Converter::OptConvert<RefPtr<PixelMap>>(value.pixelMap).value_or(nullptr);
    //         result.extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string());
    //         auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
    //         if (builder) {
    //             auto frameNode = weakNode.Upgrade();
    //             CHECK_NULL_VOID(frameNode);
    //             result.customNode = CallbackHelper(builder.value()).BuildSync(frameNode.GetRawPtr());
    //         }
    //     };
    //     auto handler = [builder = std::move(parseBuilder), dragItemInfo = std::move(parseItemInfo)]
    //         (const void *rawResultPtr) {
    //         auto arkResultPtr = reinterpret_cast<const Ark_Union_CustomBuilder_DragItemInfo*>(rawResultPtr);
    //         CHECK_NULL_VOID(arkResultPtr);
    //         Converter::VisitUnion(*arkResultPtr, builder, dragItemInfo, []() {});
    //     };

    //     PipelineContext::SetCallBackNode(weakNode);

    //     CallbackKeeper::InvokeWithResultHandler<Ark_Union_CustomBuilder_DragItemInfo,
    //         Callback_Union_CustomBuilder_DragItemInfo_Void>(handler, callback, arkDragInfo, arkExtraParam);
    //     return result;
    // };
    // ViewAbstract::SetOnDragStart(frameNode, std::move(onDragStart));
}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onDragEnter = [callback = CallbackHelper(*value)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
    //                                                        const std::string& extraParams) {
    //     CHECK_NULL_VOID(dragEvent);
    //     Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
    //     callback.Invoke(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    // };
    // ViewAbstract::SetOnDragEnter(frameNode, std::move(onDragEnter));
}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Callback_DragEvent_String_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onDragMove = [callback = CallbackHelper(*value)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
    //                                                       const std::string& extraParams) {
    //     CHECK_NULL_VOID(dragEvent);
    //     Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
    //     callback.Invoke(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    // };
    // ViewAbstract::SetOnDragMove(frameNode, std::move(onDragMove));
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onDragLeave = [callback = CallbackHelper(*value)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
    //                                                        const std::string& extraParams) {
    //     CHECK_NULL_VOID(dragEvent);
    //     Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
    //     callback.Invoke(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    // };
    // ViewAbstract::SetOnDragLeave(frameNode, std::move(onDragLeave));
}
void OnDropImpl(Ark_NativePointer node,
                const Callback_DragEvent_String_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onDrop = [callback = CallbackHelper(*value)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent,
    //                                                   const std::string& extraParams) {
    //     CHECK_NULL_VOID(dragEvent);
    //     Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
    //     callback.Invoke(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    // };
    // ViewAbstract::SetOnDrop(frameNode, std::move(onDrop));
}
void OnDragEndImpl(Ark_NativePointer node,
                   const Callback_DragEvent_String_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onDragEnd = [callback = CallbackHelper(*value)](const RefPtr<OHOS::Ace::DragEvent>& dragEvent) {
    //     CHECK_NULL_VOID(dragEvent);
    //     Ark_DragEvent arkDragEvent = Converter::ArkValue<Ark_DragEvent>(dragEvent);
    //     std::string extraParams = "";
    //     callback.Invoke(arkDragEvent, Converter::ArkValue<Opt_String>(extraParams));
    // };
    // ViewAbstract::SetOnDragEnd(frameNode, std::move(onDragEnd));
}
void AllowDropImpl(Ark_NativePointer node,
                   const Opt_Array_UniformDataType* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // //CommonMethodModelNG::SetAllowDrop(frameNode, convValue);
    // LOGE("ARKOALA: CommonMethod::setAllowDrop: Ark_Union_Array_UniformDataType_Undefined"
    //     ".CustomObject is not supported.\n");
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetDraggable(frameNode, convValue);
}
void DragPreviewImpl(Ark_NativePointer node,
                     const Ark_Union_CustomBuilder_DragItemInfo_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // DragDropInfo dragDropInfo;
    // Converter::VisitUnion(*value,
    //     [&dragDropInfo](const Ark_String& val) {
    //         dragDropInfo.inspectorId = Converter::Convert<std::string>(val);
    //     },
    //     [node, frameNode, &dragDropInfo](const CustomNodeBuilder& val) {
    //         dragDropInfo.customNode = CallbackHelper(val).BuildSync(node);
    //     },
    //     [node, frameNode, &dragDropInfo](const Ark_DragItemInfo& value) {
    //         auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
    //         if (builder) {
    //             dragDropInfo.customNode = CallbackHelper(builder.value()).BuildSync(node);
    //         }
    //         dragDropInfo.extraInfo = Converter::OptConvert<std::string>(value.extraInfo).value_or(std::string());
    //         dragDropInfo.pixelMap = Converter::OptConvert<RefPtr<PixelMap>>(value.pixelMap).value_or(nullptr);
    //     },
    //     []() {
    //         LOGE("DragPreviewImpl(): Invalid union argument");
    //     });
    // ViewAbstract::SetDragPreview(frameNode, dragDropInfo);
}
void OnPreDragImpl(Ark_NativePointer node,
                   const Callback_PreDragStatus_Void* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onPreDrag = [callback = CallbackHelper(*value)](const PreDragStatus info) {
    //     callback.Invoke(Converter::ArkValue<Ark_PreDragStatus>(info));
    // };
    // ViewAbstract::SetOnPreDrag(frameNode, onPreDrag);
}
void LinearGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_linearGradient_value* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Gradient gradient;
    // gradient.CreateGradientWithType(GradientType::LINEAR);
    // auto repeat = Converter::OptConvert<bool>(value->repeating);
    // if (repeat) {
    //     gradient.SetRepeat(repeat.value());
    // }
    // auto linear = gradient.GetLinearGradient();
    // linear->angle = Converter::OptConvert<Dimension>(value->angle);
    // auto direction = Converter::OptConvert<GradientDirection>(value->direction);
    // if (direction) {
    //     Converter::AssignLinearGradientDirection(linear, direction.value());
    // }
    // Converter::AssignGradientColors(&gradient, &value->colors);
    // ViewAbstract::SetLinearGradient(frameNode, gradient);
}
void SweepGradientImpl(Ark_NativePointer node,
                       const Ark_Type_CommonMethod_sweepGradient_value* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Gradient gradient;
    // gradient.CreateGradientWithType(GradientType::SWEEP);
    // auto repeat = Converter::OptConvert<bool>(value->repeating);
    // if (repeat) {
    //     gradient.SetRepeat(repeat.value());
    // }
    // auto sweep = gradient.GetSweepGradient();
    // auto centerX = Converter::OptConvert<Dimension>(value->center.value0);
    // auto centerY = Converter::OptConvert<Dimension>(value->center.value1);
    // auto startAngle = Converter::OptConvert<Dimension>(value->start);
    // auto endAngle = Converter::OptConvert<Dimension>(value->end);
    // auto rotation = Converter::OptConvert<Dimension>(value->rotation);
    // if (centerX) sweep->centerX = centerX.value();
    // if (centerY) sweep->centerY = centerY.value();
    // if (startAngle) sweep->startAngle = startAngle.value();
    // if (endAngle) sweep->endAngle = endAngle.value();
    // if (rotation) sweep->rotation = rotation.value();
    // Converter::AssignGradientColors(&gradient, &value->colors);
    // ViewAbstract::SetSweepGradient(frameNode, gradient);
}
void RadialGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_radialGradient_value* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // Gradient gradient = Converter::Convert<Gradient>(*value);
    // ViewAbstract::SetRadialGradient(frameNode, gradient);
}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<MotionPathOption>(*value);
    // ViewAbstract::SetMotionPath(frameNode, convValue);
}
void ShadowImpl(Ark_NativePointer node,
                const Ark_Union_ShadowOptions_ShadowStyle* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto shadow = Converter::OptConvert<Shadow>(*value);
    // if (shadow) {
    //     ViewAbstract::SetBackShadow(frameNode, shadow.value());
    // }
}
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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetClip1(frameNode, convValue);
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<RefPtr<BasicShape>>(*value);
    // if (convValue.has_value() && convValue.value()) {
    //     ViewAbstract::SetClipShape(convValue.value());
    // }
}
void Mask0Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto mask = Converter::OptConvert<Ark_ProgressMask>(*value);
    // if (!mask) return;
    // const auto& progressMask = mask.value()->GetProperty();
    // ViewAbstract::SetProgressMask(frameNode, progressMask);
}
void Mask1Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetMask1(frameNode, convValue);
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<RefPtr<BasicShape>>(*value);
    // if (convValue.has_value() && convValue.value()) {
    //     ViewAbstract::SetMask(convValue.value());
    // }
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<std::string>(*value);
    // ViewAbstract::SetInspectorId(frameNode, convValue);
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // std::string id = Converter::Convert<std::string>(*value);
    // if (id.empty()) {
    //     return;
    // }
    // ViewAbstract::SetInspectorId(frameNode, id);
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto id = Converter::Convert<std::string>(*value);
    // bool followWithoutTransition {false};
    // bool doRegisterSharedTransition {false};
    // ViewAbstract::SetGeometryTransition(frameNode, id, followWithoutTransition, doRegisterSharedTransition);
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_EQUAL_VOID(id && options, false);
    // auto idValue = id ? Converter::Convert<std::string>(*id) : "";
    // auto optOptions = options ? Converter::OptConvert<GeometryTransitionOptions>(*options) : std::nullopt;
    // auto followWithoutTransition {false};
    // auto hierarchyStrategy = TransitionHierarchyStrategy::NONE;
    // auto doRegisterSharedTransition {false};
    // if (optOptions.has_value()) {
    //     followWithoutTransition = optOptions.value().follow.value_or(false);
    //     hierarchyStrategy = optOptions.value().hierarchyStrategy.value_or(TransitionHierarchyStrategy::NONE);
    //     doRegisterSharedTransition = hierarchyStrategy == TransitionHierarchyStrategy::ADAPTIVE;
    // }
    // ViewAbstract::SetGeometryTransition(frameNode, idValue, followWithoutTransition, doRegisterSharedTransition);
}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetStateStyles(frameNode, convValue);
    LOGE("Ark_StateStyles contains a CustomObject's which is not supported");
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<int32_t>(*value);
    // ViewAbstract::SetRestoreId(frameNode, convValue);
}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? Converter::OptConvert<float>(*value) : std::nullopt;
    // const float minValue = 0.0;
    // const float maxValue = 1.0;
    // Validator::ValidateByRange(convValue, minValue, maxValue);
    // ViewAbstract::SetSphericalEffect(frameNode, convValue);
}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? Converter::OptConvert<float>(*value) : std::nullopt;
    // const float minValue = 0.0;
    // const float maxValue = 1.0;
    // Validator::ValidateByRange(convValue, minValue, maxValue);
    // ViewAbstract::SetLightUpEffect(frameNode, convValue);
}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = value
    //     ? Converter::OptConvert<PixStretchEffectOption>(*value) : std::nullopt;
    // ViewAbstract::SetPixelStretchEffect(frameNode, convValue);
}
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
    // auto optValue = Converter::OptConvert<std::string>(*value);
    // ViewAbstractModelNG::SetAccessibilityDescription(frameNode, convValue);
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
    // ViewAbstractModelNG::SetAccessibilityLevel(frameNode, convValue);
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
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto convValue = Converter::Convert<std::vector<std::optional<ObscuredReasons>>>(*value);
    // auto vec = std::vector<ObscuredReasons>();
    // for (auto reason : convValue) {
    //     if (reason.has_value()) {
    //         vec.emplace_back(reason.value());
    //     }
    // }
    // ViewAbstract::SetObscured(frameNode, vec);
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // //auto convValue = Converter::Convert<std::string>(*value);
    // //CommonMethodModelNG::SetReuseId(frameNode, convValue);
    // LOGE("ARKOALA CommonMethod::ReuseIdImpl: Method not implemented in ViewAbstract!");
}
void RenderFitImpl(Ark_NativePointer node,
                   Ark_RenderFit value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::OptConvert<RenderFit>(value); // for enums
    // ViewAbstract::SetRenderFit(frameNode, convValue);
}
void GestureModifierImpl(Ark_NativePointer node,
                         Ark_GestureModifier value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // //auto convValue = Converter::Convert<type>(value);
    // //auto convValue = Converter::OptConvert<type>(value); // for enums
    // //CommonMethodModelNG::SetGestureModifier(frameNode, convValue);
}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto rate = Converter::Convert<float>(value->rate);
    // auto lightUpDegree = Converter::Convert<float>(value->lightUpDegree);
    // ViewAbstract::SetDynamicLightUp(frameNode, rate, lightUpDegree);
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             const Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onGestureJudgefunc = [callback = CallbackHelper(*value), node = weakNode](
    //         const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& baseGestureInfo
    //     ) -> GestureJudgeResult {
    //     GestureJudgeResult defVal = GestureJudgeResult::CONTINUE;
    //     CHECK_NULL_RETURN(gestureInfo && baseGestureInfo, defVal);
    //     PipelineContext::SetCallBackNode(node);
    //     auto arkGestInfo = Converter::ArkValue<Ark_GestureInfo>(*gestureInfo);
    //     auto arkGestEvent = Converter::ArkValue<Ark_BaseGestureEvent>(baseGestureInfo);
    //     auto resultOpt = callback.InvokeWithOptConvertResult
    //         <GestureJudgeResult, Ark_GestureJudgeResult, Callback_GestureJudgeResult_Void>(arkGestInfo, arkGestEvent);
    //     return resultOpt.value_or(defVal);
    // };
    // ViewAbstract::SetOnGestureJudgeBegin(frameNode, std::move(onGestureJudgefunc));
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* callback,
                                        Ark_Boolean exposeInnerGesture);
void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* value)
{
    // OnGestureRecognizerJudgeBegin1Impl(node, value, false);
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* callback_,
                                        Ark_Boolean exposeInnerGesture)
{
//     auto frameNode = reinterpret_cast<FrameNode *>(node);
//     CHECK_NULL_VOID(frameNode);
//     CHECK_NULL_VOID(callback_);
//     auto weakNode = AceType::WeakClaim(frameNode);
//     auto onGestureRecognizerJudgefunc = [callback = CallbackHelper(*callback_), node = weakNode](
//             const std::shared_ptr<BaseGestureEvent>& info,
//             const RefPtr<NG::NGGestureRecognizer>& current,
//             const std::list<RefPtr<NG::NGGestureRecognizer>>& others
//         ) -> GestureJudgeResult {
//         GestureJudgeResult defVal = GestureJudgeResult::CONTINUE;
//         CHECK_NULL_RETURN(info && current, defVal);
//         PipelineContext::SetCallBackNode(node);

//         auto arkGestEvent = Converter::ArkValue<Ark_BaseGestureEvent>(info);
//         auto arkValCurrent = Converter::ArkValue<Ark_GestureRecognizer>(current);
//         Converter::ArkArrayHolder<Array_GestureRecognizer> holderOthers(others);
//         auto arkValOthers = holderOthers.ArkValue();
//         auto resultOpt = callback.InvokeWithOptConvertResult<GestureJudgeResult, Ark_GestureJudgeResult,
//             Callback_GestureJudgeResult_Void>(arkGestEvent, arkValCurrent, arkValOthers);
//         if (auto accessor = GetGestureRecognizerAccessor(); accessor) {
//             accessor->destroyPeer(arkValCurrent);
//             holderOthers.Release([accessor](Ark_GestureRecognizer& item) {
//                 accessor->destroyPeer(item);
//             });
//         }
//         return resultOpt.value_or(defVal);
//     };
//     ViewAbstract::SetOnGestureRecognizerJudgeBegin(frameNode,
//         std::move(onGestureRecognizerJudgefunc), Converter::Convert<bool>(exposeInnerGesture));
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             const ShouldBuiltInRecognizerParallelWithCallback* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto shouldBuiltInRecognizerParallelWithFunc = [callback = CallbackHelper(*value), node = weakNode](
    //     const RefPtr<NG::NGGestureRecognizer>& current, const std::vector<RefPtr<NG::NGGestureRecognizer>>& others
    // ) -> RefPtr<NG::NGGestureRecognizer> {
    //     PipelineContext::SetCallBackNode(node);

    //     auto arkValCurrent = Converter::ArkValue<Ark_GestureRecognizer>(current);
    //     Converter::ArkArrayHolder<Array_GestureRecognizer> holderOthers(others);
    //     auto arkValOthers = holderOthers.ArkValue();
    //     auto resultOpt = callback.InvokeWithOptConvertResult<RefPtr<NG::NGGestureRecognizer>, Ark_GestureRecognizer,
    //         Callback_GestureRecognizer_Void>(arkValCurrent, arkValOthers);
    //     if (auto accessor = GetGestureRecognizerAccessor(); accessor) {
    //         accessor->destroyPeer(arkValCurrent);
    //         holderOthers.Release([accessor](Ark_GestureRecognizer& item) {
    //             accessor->destroyPeer(item);
    //         });
    //     }
    //     return resultOpt.value_or(nullptr);
    // };
    // ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, std::move(shouldBuiltInRecognizerParallelWithFunc));
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetMonopolizeEvents(frameNode, convValue);
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          const Callback_TouchEvent_HitTestMode* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onTouchIntercept = [arkCallback = CallbackHelper(*value), node = weakNode](
    //     TouchEventInfo& info) -> HitTestMode {
    //     PipelineContext::SetCallBackNode(node);
    //     const auto event = Converter::ArkTouchEventSync(info);
    //     auto resultOpt = arkCallback.InvokeWithOptConvertResult<
    //         HitTestMode, Ark_HitTestMode, Callback_HitTestMode_Void>(event.ArkValue());
    //     return resultOpt.value_or(HitTestMode::HTMDEFAULT);
    // };
    // ViewAbstract::SetOnTouchIntercept(frameNode, std::move(onTouchIntercept));
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      const SizeChangeCallback* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto onSizeChange = [callback = CallbackHelper(*value)](const RectF &oldRect, const RectF &newRect) {
    //     Ark_SizeOptions oldSize;
    //     oldSize.width = Converter::ArkValue<Opt_Length>(oldRect.Width());
    //     oldSize.height = Converter::ArkValue<Opt_Length>(oldRect.Height());
    //     Ark_SizeOptions newSize;
    //     newSize.width = Converter::ArkValue<Opt_Length>(newRect.Width());
    //     newSize.height = Converter::ArkValue<Opt_Length>(newRect.Height());
    //     callback.Invoke(oldSize, newSize);
    // };
    // ViewAbstract::SetOnSizeChanged(frameNode, std::move(onSizeChange));
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Opt_CustomObject* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // LOGE("CommonMethodModifier::CustomPropertyImpl is not implemented");
    // //auto convValue = Converter::Convert<type>(name);
    // //auto convValue = Converter::OptConvert<type>(name); // for enums
    // //CommonMethodModelNG::SetCustomProperty(frameNode, convValue);
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convTypes = Converter::OptConvert<std::vector<std::optional<uint32_t>>>(*types);
    // auto convEdges = Converter::OptConvert<std::vector<std::optional<uint32_t>>>(*edges);
    // SafeAreaExpandOpts opts;
    // uint32_t safeAreaType = SAFE_AREA_TYPE_NONE;
    // if (convTypes.has_value()) {
    //     std::vector<std::optional<uint32_t>> vec = convTypes.value();
    //     for (size_t i = 0; i < vec.size(); ++i) {
    //         safeAreaType |= vec[i].value_or(0);
    //     }
    //     opts.type = safeAreaType;
    // }
    // uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    // if (convEdges.has_value()) {
    //     std::vector<std::optional<uint32_t>> vec = convEdges.value();
    //     for (size_t i = 0; i < vec.size(); ++i) {
    //         safeAreaEdge |= vec[i].value_or(0);
    //     }
    //     opts.edges = safeAreaEdge;
    // }
    // ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}
void BackgroundImpl(Ark_NativePointer node,
                    const CustomNodeBuilder* builder,
                    const Opt_Literal_Alignment_align* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto customNode = CallbackHelper(*builder).BuildSync(node);
    // CHECK_NULL_VOID(customNode);
    // auto customFrameNode = AceType::DynamicCast<FrameNode>(customNode).GetRawPtr();
    // auto optAlign = options ? Converter::OptConvert<Alignment>(*options) : std::nullopt;
    // ViewAbstract::SetBackgroundAlign(customFrameNode, optAlign);
}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceStr_PixelMap* src,
                         const Opt_ImageRepeat* repeat)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(src);
    // LOGE("CommonMethodModifier::BackgroundImageImpl, the PixelMap support not implemented");
    // std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvert<ImageSourceInfo>(*src);
    // ViewAbstract::SetBackgroundImage(frameNode, sourceInfo);

    // auto imageRepeat = repeat ? Converter::OptConvert<ImageRepeat>(*repeat) : std::nullopt;
    // ViewAbstract::SetBackgroundImageRepeat(frameNode, imageRepeat);
}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // BlurStyleOption convValue;
    // if (options) {
    //     if (auto opt = Converter::OptConvert<BlurStyleOption>(*options); opt) {
    //         convValue = *opt;
    //     }
    // }
    // if (auto style = Converter::OptConvert<BlurStyle>(value); style) {
    //     convValue.blurStyle = *style;
    // }
    // ViewAbstract::SetBackgroundBlurStyle(frameNode, convValue);
}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // BlurStyleOption convValue;
    // if (options) {
    //     if (auto opt = Converter::OptConvert<BlurStyleOption>(*options); opt) {
    //         convValue = *opt;
    //     }
    // }
    // if (auto style = Converter::OptConvert<BlurStyle>(value); style) {
    //     convValue.blurStyle = *style;
    // }
    // ViewAbstract::SetForegroundBlurStyle(frameNode, convValue);
}
void FocusScopeId0Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(id);
    // auto convIdValue = Converter::Convert<std::string>(*id);
    // auto convIsGroupValue = isGroup ? Converter::OptConvert<bool>(*isGroup) : std::nullopt;
    // ViewAbstract::SetFocusScopeId(frameNode, convIdValue, convIsGroupValue, std::nullopt);
}
void FocusScopeId1Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup,
                       const Opt_Boolean* arrowStepOut)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(id);
    // auto convIdValue = Converter::Convert<std::string>(*id);
    // auto convIsGroupValue = isGroup ? Converter::OptConvert<bool>(*isGroup) : std::nullopt;
    // auto convArrowStepOutValue = arrowStepOut ? Converter::OptConvert<bool>(*arrowStepOut) : std::nullopt;
    // if (convArrowStepOutValue.has_value()) {
    //     ViewAbstract::SetFocusScopeId(frameNode, convIdValue, convIsGroupValue, convArrowStepOutValue.value());
    // } else {
    //     ViewAbstract::SetFocusScopeId(frameNode, convIdValue, convIsGroupValue, std::nullopt);
    // }
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(scopeId);
    // auto convIdValue = Converter::Convert<std::string>(*scopeId);
    // auto optPriority = priority ? Converter::OptConvert<uint32_t>(*priority) : std::nullopt;
    // ViewAbstract::SetFocusScopePriority(frameNode, convIdValue, optPriority);
}
void GestureImplInternal(Ark_NativePointer node, const Ark_GestureType* gesture, const Opt_GestureMask* mask,
    GesturePriority priority)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(gesture);

    // std::optional<RefPtr<Gesture>> aceGestureOpt;
    // Converter::VisitUnion(*gesture,
    //     [&aceGestureOpt](const auto& gestureType) {
    //         aceGestureOpt = gestureType->gesture;
    //     },
    //     []() {}
    // );
    // CHECK_NULL_VOID(aceGestureOpt);
    // auto aceGesture = aceGestureOpt.value();
    // auto gestureMask = (mask ?
    //     Converter::OptConvert<GestureMask>(*mask) : std::nullopt).value_or(GestureMask::Normal);
    // aceGesture->SetGestureMask(gestureMask);
    // aceGesture->SetPriority(priority);
    // auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    // CHECK_NULL_VOID(gestureEventHub);
    // gestureEventHub->AddGesture(aceGesture);
}
void GestureImpl(Ark_NativePointer node,
                 const Ark_GestureType* gesture,
                 const Opt_GestureMask* mask)
{
    // GestureImplInternal(node, gesture, mask, GesturePriority::Low);
}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
    // GestureImplInternal(node, gesture, mask, GesturePriority::High);
}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
    // GestureImplInternal(node, gesture, mask, GesturePriority::Parallel);
}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto blur = Converter::Convert<float>(*value);
    // BlurOption blurOptions;
    // auto optionsOpt = Converter::OptConvert<BlurOption>(*options);
    // if (optionsOpt.has_value()) {
    //     blurOptions = optionsOpt.value();
    // }
    // CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    // ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, blurOptions);
}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto radius = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    // auto convValue = options ? Converter::OptConvert<NG::LinearGradientBlurPara>(*options) : std::nullopt;
    // Validator::ValidateNonNegative(radius);
    // if (radius.has_value()) {
    //     convValue->blurRadius_ = radius.value();
    // }
    // ViewAbstract::SetLinearGradientBlur(frameNode, convValue);
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // //auto convValue = Converter::Convert<type>(undefined);
    // //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    // //CommonMethodModelNG::SetSystemBarEffect(frameNode, convValue);
    // LOGE("The `ViewAbstract::SetSystemBarEffect(frameNode, enable)` function must take two parameters");
}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto radius = Converter::OptConvert<Dimension>(*value);
    // auto option = nullptr == options ? std::nullopt : Converter::OptConvert<BlurOption>(*options);
    // ViewAbstract::SetBackdropBlur(frameNode, radius, option);
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Ark_String* id,
                          const Opt_sharedTransitionOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(id);
    // auto modelId = Converter::Convert<std::string>(*id);
    // auto modelOptions = std::make_shared<SharedTransitionOption>();
    // if (options) {
    //     if (auto transOpt = Converter::OptConvert<SharedTransitionOption>(*options); transOpt) {
    //         *modelOptions = std::move(*transOpt);
    //     }
    // }
    // ViewAbstract::SetSharedTransition(frameNode, modelId, modelOptions);
}
void ChainModeImpl(Ark_NativePointer node,
                   Ark_Axis direction,
                   Ark_ChainStyle style)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // ChainInfo chainInfo = {
    //     .direction = Converter::OptConvert<LineDirection>(direction),
    //     .style = Converter::OptConvert<ChainStyle>(style)
    // };
    // ViewAbstractModelNG::SetChainStyle(frameNode, chainInfo);
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto previewOption = Converter::Convert<DragPreviewOption>(*value);
    // auto optionsOpt = options ? Converter::OptConvert<Ark_DragInteractionOptions>(*options) : std::nullopt;
    // if (optionsOpt) {
    //     auto defaultAnimationBeforeLifting = Converter::OptConvert<Ark_Boolean>(
    //         optionsOpt.value().defaultAnimationBeforeLifting);
    //     if (defaultAnimationBeforeLifting) {
    //         previewOption.defaultAnimationBeforeLifting = defaultAnimationBeforeLifting.value();
    //     }
    //     auto isMultiSelectionEnabled = Converter::OptConvert<Ark_Boolean>(
    //         optionsOpt.value().isMultiSelectionEnabled);
    //     if (isMultiSelectionEnabled) {
    //         previewOption.isMultiSelectionEnabled = isMultiSelectionEnabled.value();
    //     }
    // }
    // LOGE("CommonMethodModifier::DragPreviewOptionsImpl Ark_ImageModifier is not supported yet.");
    // ViewAbstract::SetDragPreviewOptions(frameNode, previewOption);
}
void OverlayImpl(Ark_NativePointer node,
                 const Ark_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // OverlayOptions overlay { .align = Alignment::TOP_LEFT};
    // if (options) {
    //     overlay = Converter::OptConvert<OverlayOptions>(*options).value_or(overlay);
    // }
    // Converter::VisitUnion(*value,
    //     [frameNode, &overlay](const Ark_String& src) {
    //         overlay.content = Converter::Convert<std::string>(src);
    //         ViewAbstract::SetOverlay(frameNode, overlay);
    //     },
    //     [node, frameNode, &overlay](const CustomNodeBuilder& builder) {
    //          auto builderFunc = [callback = CallbackHelper(builder), node, weakNode = AceType::WeakClaim(frameNode)]() {
    //             PipelineContext::SetCallBackNode(weakNode);
    //             auto uiNode = callback.BuildSync(node);
    //             ViewStackProcessor::GetInstance()->Push(uiNode);
    //         };
    //         ViewAbstract::SetOverlayBuilder(frameNode, std::move(builderFunc), overlay.align, overlay.x, overlay.y);
    //     },
    //     [](const Ark_ComponentContent& src) {
    //         LOGE("OverlayImpl() Ark_ComponentContent.ComponentContentStub not implemented");
    //     },
    //     []() {
    //         LOGE("OverlayImpl(): Invalid union argument");
    //     });
}
void BlendModeImpl(Ark_NativePointer node,
                   Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto blendMode = Converter::OptConvert<BlendMode>(value);
    // auto blendApplyType = type ? Converter::OptConvert<BlendApplyType>(*type) : std::nullopt;
    // ViewAbstract::SetBlendMode(frameNode, blendMode);
    // ViewAbstract::SetBlendApplyType(frameNode, blendApplyType);
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Ark_Union_BlendMode_Blender* effect,
                           const Opt_BlendApplyType* type)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(effect);
    // BlendMode blendMode = BlendMode::NONE;
    // BlendApplyType blendApplyType = BlendApplyType::FAST;
    // Converter::VisitUnion(*effect,
    //     [&blendMode, &blendApplyType, frameNode](const Ark_BlendMode& value) {
    //         blendMode = Converter::OptConvert<BlendMode>(value).value_or(blendMode);
    //         blendApplyType = BlendApplyType::OFFSCREEN;
    //         ViewAbstract::SetBlendMode(frameNode, blendMode);
    //     },
    //     [](const Ark_Blender& value) {
    //         LOGE("CommonMethodModifier::AdvancedBlendModeImpl Ark_Blender is not supported yet.");
    //     },
    //     []() {}
    // );
    // std::optional<BlendApplyType> blendApplyTypeOpt = type ?
    //     Converter::OptConvert<BlendApplyType>(*type) : std::nullopt;
    // blendApplyType = blendApplyTypeOpt.value_or(blendApplyType);
    // ViewAbstract::SetBlendApplyType(frameNode, blendApplyType);
}
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
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // bool isShowValue = isShow && Converter::OptConvert<bool>(*isShow).value_or(false);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto buildFunc = [arkCallback = CallbackHelper(*builder), weakNode, node]() -> RefPtr<UINode> {
    //     PipelineContext::SetCallBackNode(weakNode);
    //     return arkCallback.BuildSync(node);
    // };
    // ModalStyle modalStyle;
    // modalStyle.modalTransition = (type ? Converter::OptConvert<ModalTransition>(*type) : std::nullopt)
    //     .value_or(ModalTransition::DEFAULT);
    // ContentCoverParam contentCoverParam;
    // ViewAbstractModelNG::BindContentCover(frameNode, isShowValue, nullptr, std::move(buildFunc), modalStyle,
    //     nullptr, nullptr, nullptr, nullptr, contentCoverParam);
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomNodeBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // bool isShowValue = isShow && Converter::OptConvert<bool>(*isShow).value_or(false);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto buildFunc = [arkCallback = CallbackHelper(*builder), weakNode, node]() -> RefPtr<UINode> {
    //     PipelineContext::SetCallBackNode(weakNode);
    //     return arkCallback.BuildSync(node);
    // };
    // ModalStyle modalStyle;
    // modalStyle.modalTransition = ModalTransition::DEFAULT;
    // std::function<void()> onShowCallback;
    // std::function<void()> onDismissCallback;
    // std::function<void()> onWillShowCallback;
    // std::function<void()> onWillDismissCallback;
    // std::function<void(const int32_t&)> onWillDismissFunc;
    // ContentCoverParam contentCoverParam;
    // auto coverOption = options ? Converter::OptConvert<Ark_ContentCoverOptions>(*options) : std::nullopt;
    // if (coverOption) {
    //     g_contentCoverCallbacks(weakNode, coverOption.value(), onShowCallback, onDismissCallback, onWillShowCallback,
    //         onWillDismissCallback, onWillDismissFunc);
    //     modalStyle.modalTransition = Converter::OptConvert<ModalTransition>(coverOption->modalTransition)
    //         .value_or(ModalTransition::DEFAULT);
    //     modalStyle.backgroundColor = Converter::OptConvert<Color>(coverOption->backgroundColor);
    //     contentCoverParam.transitionEffect = OptConvert<RefPtr<NG::ChainedTransitionEffect>>(coverOption->transition)
    //         .value_or(contentCoverParam.transitionEffect);
    // }
    // contentCoverParam.onWillDismiss = std::move(onWillDismissFunc);
    // ViewAbstractModelNG::BindContentCover(frameNode, isShowValue, nullptr, std::move(buildFunc), modalStyle,
    //     std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
    //     std::move(onWillDismissCallback), contentCoverParam);
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const CustomNodeBuilder* builder,
                   const Opt_SheetOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(builder);
    // bool isShowValue = isShow && Converter::OptConvert<Ark_Boolean>(*isShow).value_or(false);
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto buildFunc = [callback = CallbackHelper(*builder), node, weakNode]() {
    //     PipelineContext::SetCallBackNode(weakNode);
    //     auto uiNode = callback.BuildSync(node);
    //     ViewStackProcessor::GetInstance()->Push(uiNode);
    // };
    // SheetStyle sheetStyle;
    // sheetStyle.sheetMode = NG::SheetMode::LARGE;
    // sheetStyle.showDragBar = true;
    // sheetStyle.showCloseIcon = true;
    // sheetStyle.showInPage = false;
    // SheetCallbacks callbacks;
    // auto sheetOptions = options ? Converter::OptConvert<Ark_SheetOptions>(*options) : std::nullopt;
    // if (sheetOptions) {
    //     g_bindSheetCallbacks1(callbacks, sheetOptions.value());
    //     g_bindSheetCallbacks2(callbacks, sheetOptions.value());
    //     Converter::VisitUnion(sheetOptions->title,
    //         [&sheetStyle](const Ark_SheetTitleOptions& value) {
    //             sheetStyle.sheetTitle = OptConvert<std::string>(value.title);
    //             sheetStyle.sheetSubtitle = OptConvert<std::string>(value.title);
    //         },
    //         [frameNode, node, &callbacks](const CustomNodeBuilder& value) {
    //             callbacks.titleBuilderFunction = [callback = CallbackHelper(value), node]() {
    //                 auto uiNode = callback.BuildSync(node);
    //                 ViewStackProcessor::GetInstance()->Push(uiNode);
    //             };
    //         }, []() {});
    //     g_bindSheetParams(sheetStyle, sheetOptions.value());
    // }
    // ViewAbstractModelNG::BindSheet(frameNode, isShow, nullptr, std::move(buildFunc),
    //     std::move(callbacks.titleBuilderFunction), sheetStyle, std::move(callbacks.onAppearCallback),
    //     std::move(callbacks.onDisappearCallback), std::move(callbacks.shouldDismissFunc),
    //     std::move(callbacks.onWillDismissCallback),  std::move(callbacks.onWillAppearCallback),
    //     std::move(callbacks.onWillDisappearCallback), std::move(callbacks.onHeightDidChangeCallback),
    //     std::move(callbacks.onDetentsDidChangeCallback), std::move(callbacks.onWidthDidChangeCallback),
    //     std::move(callbacks.onTypeDidChangeCallback), std::move(callbacks.sheetSpringBackFunc));
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             const VisibleAreaChangeCallback* event)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(ratios);
    // CHECK_NULL_VOID(event);
    // std::vector<float> rawRatioVec = Converter::Convert<std::vector<float>>(*ratios);
    // size_t size = rawRatioVec.size();
    // std::vector<double> ratioVec;
    // for (size_t i = 0; i < size; i++) {
    //     double ratio = static_cast<double>(rawRatioVec[i]);
    //     if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
    //         ratio = VISIBLE_RATIO_MIN;
    //     }

    //     if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
    //         ratio = VISIBLE_RATIO_MAX;
    //     }
    //     ratioVec.push_back(ratio);
    // }
    // auto weakNode = AceType::WeakClaim(frameNode);
    // auto onVisibleAreaChange =
    //     [arkCallback = CallbackHelper(*event), node = weakNode](bool visible, double ratio) {
    //         Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
    //         Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
    //         PipelineContext::SetCallBackNode(node);
    //         arkCallback.Invoke(isExpanding, currentRatio);
    //     };
    // ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioVec);
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Ark_Union_String_FunctionKey* value,
                          const Array_ModifierKey* keys,
                          const Opt_Callback_Void* action)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // if (!value || !keys) {
    //     ViewAbstract::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
    //     return;
    // }
    // auto strValue = Converter::OptConvert<std::string>(*value);
    // if (!strValue.has_value() || strValue.value().size() != 1) {
    //     ViewAbstract::SetKeyboardShortcut(frameNode, {}, {}, nullptr);
    //     return;
    // }
    // auto keysOptVect = Converter::Convert<std::vector<std::optional<ModifierKey>>>(*keys);
    // std::vector<ModifierKey> keysVect;
    // for (auto item : keysOptVect) {
    //     if (item.has_value()) {
    //         keysVect.emplace_back(item.value());
    //     }
    // }
    // auto actionOpt = action ? Converter::OptConvert<Callback_Void>(*action) : std::nullopt;
    // if (actionOpt) {
    //     auto weakNode = AceType::WeakClaim(frameNode);
    //     auto onKeyboardShortcutAction = [arkCallback = CallbackHelper(actionOpt.value()), node = weakNode]() {
    //         PipelineContext::SetCallBackNode(node);
    //         arkCallback.Invoke();
    //     };
    //     ViewAbstract::SetKeyboardShortcut(frameNode, strValue.value(), keysVect, std::move(onKeyboardShortcutAction));
    //     return;
    // }
    // ViewAbstract::SetKeyboardShortcut(frameNode, strValue.value(), keysVect, nullptr);
}
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
