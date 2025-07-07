/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/interfaces/native/implementation/bind_sheet_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t EFFECT_EDGE_ZERO = 0;
constexpr int32_t EFFECT_EDGE_ONE = 1;
constexpr int32_t EFFECT_EDGE_TWO = 2;
constexpr double DETENT_SELECTION_EDGE = 0.0f;
using namespace OHOS::Ace::NG::Converter;

std::pair<std::optional<OHOS::Ace::Dimension>, std::optional<OHOS::Ace::Dimension>> OffsetConvert(
    const Ark_Position& src)
{
    auto x = OptConvert<OHOS::Ace::Dimension>(src.x);
    auto y = OptConvert<OHOS::Ace::Dimension>(src.y);
    return { x, y };
}

void BindSheetUtil::ParseLifecycleCallbacks(SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions)
{
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
            Ark_SheetDismiss parameter;
            const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelStatic::DismissSheetStatic));
            parameter.dismiss = keeper.ArkValue();
            arkCallback.Invoke(parameter);
        };
    }
    auto onTypeDidChange = Converter::OptConvert<Callback_SheetType_Void>(sheetOptions.onTypeDidChange);
    if (onTypeDidChange) {
        callbacks.onTypeDidChange = [arkCallback = CallbackHelper(onTypeDidChange.value())](int32_t value) {
            arkCallback.Invoke(Converter::ArkValue<Ark_SheetType>(static_cast<SheetType>(value)));
        };
    }
}
void BindSheetUtil::ParseFuntionalCallbacks(SheetCallbacks& callbacks, const Ark_SheetOptions& sheetOptions)
{
    auto onWillDismiss = Converter::OptConvert<Callback_DismissSheetAction_Void>(sheetOptions.onWillDismiss);
    if (onWillDismiss) {
        callbacks.onWillDismiss = [arkCallback = CallbackHelper(onWillDismiss.value())](const int32_t reason) {
            Ark_DismissSheetAction parameter;
            auto reasonOpt = ArkValue<Opt_DismissReason>(static_cast<BindSheetDismissReason>(reason));
            parameter.reason = OptConvert<Ark_DismissReason>(reasonOpt).value_or(ARK_DISMISS_REASON_CLOSE_BUTTON);
            const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelStatic::DismissSheetStatic));
            parameter.dismiss = keeper.ArkValue();
            arkCallback.Invoke(parameter);
        };
    }
    auto onWillSpringBackWhenDismiss = Converter::OptConvert<Callback_SpringBackAction_Void>(
        sheetOptions.onWillSpringBackWhenDismiss);
    if (onWillSpringBackWhenDismiss) {
        callbacks.sheetSpringBack = [arkCallback = CallbackHelper(onWillSpringBackWhenDismiss.value())]() {
            Ark_SpringBackAction parameter;
            const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelStatic::SheetSpringBackStatic));
            parameter.springBack = keeper.ArkValue();
            arkCallback.Invoke(parameter);
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
}

void BindSheetUtil::ParseSheetParams(SheetStyle& sheetStyle, const Ark_SheetOptions& sheetOptions)
{
    sheetStyle.showInPage = OptConvert<SheetLevel>(sheetOptions.mode).value_or(SheetLevel::OVERLAY);
    std::vector<SheetHeight> detents;
    auto detentsOpt = OptConvert<Ark_Type_SheetOptions_detents>(sheetOptions.detents);
    if (detentsOpt) {
        auto value0 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value0);
        if (value0) {
            detents.emplace_back(value0.value());
        }
        auto value1 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value1);
        if (value1) {
            detents.emplace_back(value1.value());
        }
        auto value2 = Converter::OptConvert<SheetHeight>(detentsOpt.value().value2);
        if (value2) {
            detents.emplace_back(value2.value());
        }
    }
    sheetStyle.detents = detents;
    sheetStyle.backgroundBlurStyle = OptConvert<BlurStyleOption>(sheetOptions.blurStyle);
    sheetStyle.showCloseIcon = OptConvert<bool>(sheetOptions.showClose);
    sheetStyle.interactive = OptConvert<bool>(sheetOptions.enableOutsideInteractive);
    sheetStyle.showDragBar = OptConvert<bool>(sheetOptions.dragBar);
    sheetStyle.sheetType = OptConvert<SheetType>(sheetOptions.preferType);
    sheetStyle.scrollSizeMode = OptConvert<ScrollSizeMode>(sheetOptions.scrollSizeMode);
    sheetStyle.sheetKeyboardAvoidMode = OptConvert<SheetKeyboardAvoidMode>(sheetOptions.keyboardAvoidMode);
    sheetStyle.backgroundColor = OptConvert<Color>(sheetOptions.backgroundColor);
    sheetStyle.maskColor = OptConvert<Color>(sheetOptions.maskColor);
    sheetStyle.borderWidth = OptConvert<BorderWidthProperty>(sheetOptions.borderWidth);
    sheetStyle.borderColor = OptConvert<BorderColorProperty>(sheetOptions.borderColor);
    sheetStyle.borderStyle = OptConvert<BorderStyleProperty>(sheetOptions.borderStyle);
    sheetStyle.shadow = OptConvert<Shadow>(sheetOptions.shadow);
    sheetStyle.enableHoverMode = OptConvert<bool>(sheetOptions.enableHoverMode);
    sheetStyle.hoverModeArea = OptConvert<HoverModeAreaType>(sheetOptions.hoverModeArea);
    sheetStyle.width = OptConvert<Dimension>(sheetOptions.width);
    auto effectEdge = OptConvert<int>(sheetOptions.effectEdge.value).value_or(3);
    switch (effectEdge) {
        case EFFECT_EDGE_ZERO:
            sheetStyle.sheetEffectEdge = SheetEffectEdge::NONE;
            break;
        case EFFECT_EDGE_ONE:
            sheetStyle.sheetEffectEdge = SheetEffectEdge::START;
            break;
        case EFFECT_EDGE_TWO:
            sheetStyle.sheetEffectEdge = SheetEffectEdge::END;
            break;
        default:
            sheetStyle.sheetEffectEdge = SheetEffectEdge::ALL;
            break;
    }
    sheetStyle.radius = OptConvert<NG::BorderRadiusProperty>(sheetOptions.radius);
    if (LessNotEqual(sheetOptions.detentSelection.value.value1.value, DETENT_SELECTION_EDGE)) {
        sheetStyle.detentSelection.reset();
    } else {
        sheetStyle.detentSelection = OptConvert<SheetHeight>(sheetOptions.detentSelection);
    }
    sheetStyle.showInSubWindow = OptConvert<bool>(sheetOptions.showInSubWindow).value_or(false);
    sheetStyle.placement = OptConvert<Placement>(sheetOptions.placement);
    sheetStyle.placementOnTarget = OptConvert<bool>(sheetOptions.placementOnTarget).value_or(true);
    Validator::ValidateNonNegative(sheetStyle.width);
    auto height = OptConvert<SheetHeight>(sheetOptions.height);
    if (height) {
        sheetStyle.sheetHeight = height.value();
    }
    auto offsetVal = OffsetConvert(sheetOptions.offset.value);
    OffsetF sheetOffset;
    sheetOffset.SetX(offsetVal.first.value().ConvertToPx());
    sheetOffset.SetY(offsetVal.second.value().ConvertToPx());
    sheetStyle.bottomOffset = sheetOffset;
}
void BindSheetUtil::ParseContentCoverCallbacks(WeakPtr<FrameNode> weakNode, const Ark_ContentCoverOptions& options,
    std::function<void()>& onShowCallback, std::function<void()>& onDismissCallback,
    std::function<void()>& onWillShowCallback, std::function<void()>& onWillDismissCallback,
    std::function<void(const int32_t& info)>& onWillDismissFunc)
{
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
            PipelineContext::SetCallBackNode(weakNode);
            Ark_DismissContentCoverAction parameter;
            auto reasonOpt = Converter::ArkValue<Opt_DismissReason>(
                static_cast<BindSheetDismissReason>(reason));
            parameter.reason = Converter::OptConvert<Ark_DismissReason>(reasonOpt)
                .value_or(ARK_DISMISS_REASON_CLOSE_BUTTON);
            const auto keeper = CallbackKeeper::Claim(std::move(ViewAbstractModelStatic::DismissContentCoverStatic));
            parameter.dismiss = keeper.ArkValue();
            arkCallback.Invoke(parameter);
        };
    }
}
}
