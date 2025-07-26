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

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
struct DialogPropsForUpdate {
    Opt_DialogAlignment alignment;
    Opt_Boolean autoCancel;
    Opt_BlurStyle backgroundBlurStyle;
    Opt_ResourceColor backgroundColor;
    Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors borderColor;
    Opt_Union_BorderStyle_EdgeStyles borderStyle;
    Opt_Union_Dimension_EdgeWidths_LocalizedEdgeWidths borderWidth;
    Opt_VoidCallback cancel;
    Opt_Union_Dimension_BorderRadiuses_LocalizedBorderRadiuses cornerRadius;
    Opt_Boolean enableHoverMode;
    Opt_Number gridCount;
    Opt_Length height;
    Opt_HoverModeAreaType hoverModeArea;
    Opt_Boolean isModal;
    Opt_Rectangle maskRect;
    Ark_ResourceStr message;
    Opt_Offset offset;
    Opt_Callback_DismissDialogAction_Void onWillDismiss;
    Opt_Union_ShadowOptions_ShadowStyle shadow;
    Opt_Boolean showInSubWindow;
    Opt_ResourceStr subtitle;
    Opt_ResourceStr title;
    Opt_TextStyle_alert_dialog textStyle;
    Opt_TransitionEffect transition;
    Opt_Length width;
};
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_DismissReason& dst, const DialogDismissReason& src)
{
    switch (src) {
        case DialogDismissReason::DIALOG_PRESS_BACK:
            dst = Ark_DismissReason::ARK_DISMISS_REASON_PRESS_BACK;
            break;
        case DialogDismissReason::DIALOG_TOUCH_OUTSIDE:
            dst = Ark_DismissReason::ARK_DISMISS_REASON_TOUCH_OUTSIDE;
            break;
        case DialogDismissReason::DIALOG_CLOSE_BUTTON:
            dst = Ark_DismissReason::ARK_DISMISS_REASON_CLOSE_BUTTON;
            break;
        default:
            dst = static_cast<Ark_DismissReason>(-1);
            LOGE("Unexpected enum value in DialogDismissReason: %{public}d", src);
    }
}

template<>
ButtonInfo Convert(const Ark_AlertDialogButtonOptions& src)
{
    ButtonInfo info;
    info.text = Converter::OptConvert<std::string>(src.value).value_or("");
    info.enabled = Converter::OptConvert<bool>(src.enabled).value_or(info.enabled);
    info.defaultFocus = Converter::OptConvert<bool>(src.defaultFocus).value_or(info.defaultFocus);
    info.dlgButtonStyle = Converter::OptConvert<DialogButtonStyle>(src.style);
    info.fontColor = Converter::OptConvert<Color>(src.fontColor);
    auto backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    if (backgroundColor) {
        info.isBgColorSetted = true;
        info.backgroundColor = backgroundColor;
    }
    auto arkCallbackOpt = Converter::OptConvert<VoidCallback>(src.action);
    if (arkCallbackOpt) {
        auto gestureEvent = [arkCallback = CallbackHelper(*arkCallbackOpt)](
                                const GestureEvent& info) -> void { arkCallback.Invoke(); };
        info.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
    }
    return info;
}

template<>
ButtonInfo Convert(const Ark_AlertDialogButtonBaseOptions& src)
{
    ButtonInfo info;
    info.text = Converter::OptConvert<std::string>(src.value).value_or("");
    info.enabled = Converter::OptConvert<bool>(src.enabled).value_or(info.enabled);
    info.defaultFocus = Converter::OptConvert<bool>(src.defaultFocus).value_or(info.defaultFocus);
    info.dlgButtonStyle = Converter::OptConvert<DialogButtonStyle>(src.style);
    info.fontColor = Converter::OptConvert<Color>(src.fontColor);
    auto backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    if (backgroundColor) {
        info.isBgColorSetted = true;
        info.backgroundColor = backgroundColor;
    }
    auto arkCallbackOpt = Converter::OptConvert<VoidCallback>(src.action);
    if (arkCallbackOpt) {
        auto gestureEvent = [arkCallback = CallbackHelper(*arkCallbackOpt)](
                                const GestureEvent& info) -> void { arkCallback.Invoke(); };
        info.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
    }
    return info;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AlertDialogAccessor {
void UpdateDynamicDialogProperties(DialogProperties& dialogProps, const DialogPropsForUpdate props)
{
    dialogProps.title = Converter::OptConvert<std::string>(props.title).value_or("");
    dialogProps.subtitle = Converter::OptConvert<std::string>(props.subtitle).value_or("");
    dialogProps.content = Converter::OptConvert<std::string>(props.message).value_or("");
    dialogProps.shadow = Converter::OptConvert<Shadow>(props.shadow);
    dialogProps.borderWidth = Converter::OptConvert<BorderWidthProperty>(props.borderWidth);
    dialogProps.borderColor = Converter::OptConvert<BorderColorProperty>(props.borderColor);
    dialogProps.borderRadius = Converter::OptConvert<BorderRadiusProperty>(props.cornerRadius);
    dialogProps.borderStyle = Converter::OptConvert<BorderStyleProperty>(props.borderStyle);
    dialogProps.alignment = Converter::OptConvert<DialogAlignment>(
        props.alignment).value_or(DialogAlignment::BOTTOM);
    dialogProps.offset = Converter::OptConvert<DimensionOffset>(props.offset).value_or(dialogProps.offset);
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(props.maskRect);
    if (auto textStyle = Converter::OptConvert<Ark_TextStyle_alert_dialog>(props.textStyle); textStyle) {
        dialogProps.wordBreak = Converter::OptConvert<WordBreak>(textStyle->wordBreak).value_or(dialogProps.wordBreak);
    }
    auto transition = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(props.transition);
    if (transition) {
        dialogProps.transitionEffect = *transition;
    }
}
DialogProperties CreateDialogProperties(const DialogPropsForUpdate props)
{
    DialogProperties dialogProps { .type = DialogType::ALERT_DIALOG };
    UpdateDynamicDialogProperties(dialogProps, props);
    dialogProps.gridCount = Converter::OptConvert<int32_t>(props.gridCount).value_or(dialogProps.gridCount);
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(
        Converter::OptConvert<BlurStyle>(props.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(props.backgroundColor);
    dialogProps.enableHoverMode =
        Converter::OptConvert<bool>(props.enableHoverMode);
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(props.hoverModeArea);
    dialogProps.autoCancel = Converter::OptConvert<bool>(props.autoCancel).value_or(dialogProps.autoCancel);
    dialogProps.isModal = Converter::OptConvert<bool>(props.isModal).value_or(dialogProps.isModal);
    dialogProps.isShowInSubWindow =
        Converter::OptConvert<bool>(props.showInSubWindow).value_or(dialogProps.isShowInSubWindow);
    dialogProps.width = Converter::OptConvert<CalcDimension>(props.width);
    dialogProps.height = Converter::OptConvert<CalcDimension>(props.height);

    AddOnWillDismiss(dialogProps, props.onWillDismiss);
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(props.cancel);
    if (cancelCallbackOpt) {
        auto cancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogProps.onCancel = cancelFunc;
    }
    dialogProps.onLanguageChange = [props, updateDialogProperties = UpdateDynamicDialogProperties](
        DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, props);
    };
    return dialogProps;
}
DialogPropsForUpdate GetPropsWithConfirm(const Ark_AlertDialogParamWithConfirm params)
{
    return {
        .alignment = params.alignment,
        .autoCancel = params.autoCancel,
        .backgroundBlurStyle = params.backgroundBlurStyle,
        .backgroundColor = params.backgroundColor,
        .borderColor = params.borderColor,
        .borderStyle = params.borderStyle,
        .borderWidth = params.borderWidth,
        .cancel = params.cancel,
        .cornerRadius = params.cornerRadius,
        .enableHoverMode = params.enableHoverMode,
        .gridCount = params.gridCount,
        .height = params.height,
        .hoverModeArea = params.hoverModeArea,
        .isModal = params.isModal,
        .maskRect = params.maskRect,
        .message = params.message,
        .offset = params.offset,
        .onWillDismiss = params.onWillDismiss,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width
    };
}
void UpdateConfirmButton(DialogProperties& dialogProps, const Ark_AlertDialogParamWithConfirm params)
{
    dialogProps.buttons.clear();
    auto confirmButton = Converter::OptConvert<ButtonInfo>(params.confirm);
    if (confirmButton && confirmButton->IsValid()) {
        confirmButton->isPrimary = true;
        dialogProps.buttons.emplace_back(*confirmButton);
    }
}
void ShowWithConfirm(const Ark_AlertDialogParamWithConfirm params)
{
    auto dialogProps = CreateDialogProperties(GetPropsWithConfirm(params));
    UpdateConfirmButton(dialogProps, params);
    dialogProps.onLanguageChange = [params, getProps = GetPropsWithConfirm,
        updateDialogProperties = UpdateDynamicDialogProperties,
        updateButtons = UpdateConfirmButton](DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, getProps(params));
        updateButtons(dialogProps, params);
    };

    OHOS::Ace::NG::AlertDialogModelNG model;
    model.SetShowDialog(dialogProps);
}
void UpdateButtons(DialogProperties& dialogProps, const Ark_AlertDialogParamWithButtons params)
{
    dialogProps.buttons.clear();
    auto primaryButton = Converter::Convert<ButtonInfo>(params.primaryButton);
    primaryButton.isPrimary = !primaryButton.defaultFocus;
    auto secondaryButton = Converter::Convert<ButtonInfo>(params.secondaryButton);
    if (primaryButton.IsValid()) {
        dialogProps.buttons.emplace_back(primaryButton);
    }
    if (secondaryButton.IsValid()) {
        dialogProps.buttons.emplace_back(secondaryButton);
    }
}
DialogPropsForUpdate GetPropsWithButtons(const Ark_AlertDialogParamWithButtons params)
{
    return {
        .alignment = params.alignment,
        .autoCancel = params.autoCancel,
        .backgroundBlurStyle = params.backgroundBlurStyle,
        .backgroundColor = params.backgroundColor,
        .borderColor = params.borderColor,
        .borderStyle = params.borderStyle,
        .borderWidth = params.borderWidth,
        .cancel = params.cancel,
        .cornerRadius = params.cornerRadius,
        .enableHoverMode = params.enableHoverMode,
        .gridCount = params.gridCount,
        .height = params.height,
        .hoverModeArea = params.hoverModeArea,
        .isModal = params.isModal,
        .maskRect = params.maskRect,
        .message = params.message,
        .offset = params.offset,
        .onWillDismiss = params.onWillDismiss,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width
    };
}
void ShowWithButtons(const Ark_AlertDialogParamWithButtons params)
{
    auto dialogProps = CreateDialogProperties(GetPropsWithButtons(params));
    UpdateButtons(dialogProps, params);
    dialogProps.onLanguageChange = [params, getProps = GetPropsWithButtons,
        updateDialogProperties = UpdateDynamicDialogProperties,
        updateButtons = UpdateButtons](DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, getProps(params));
        updateButtons(dialogProps, params);
    };

    OHOS::Ace::NG::AlertDialogModelNG model;
    model.SetShowDialog(dialogProps);
}
void UpdateOptionsButtons(DialogProperties& dialogProps, const Ark_AlertDialogParamWithOptions params)
{
    dialogProps.buttons.clear();
    auto buttons = Converter::Convert<std::vector<ButtonInfo>>(params.buttons);
    for (const auto& button : buttons) {
        if (button.IsValid()) {
            dialogProps.buttons.emplace_back(button);
        }
    }
    dialogProps.buttonDirection =
        Converter::OptConvert<DialogButtonDirection>(params.buttonDirection).value_or(dialogProps.buttonDirection);
}
DialogPropsForUpdate GetPropsWithOptions(const Ark_AlertDialogParamWithOptions params)
{
    return {
        .alignment = params.alignment,
        .autoCancel = params.autoCancel,
        .backgroundBlurStyle = params.backgroundBlurStyle,
        .backgroundColor = params.backgroundColor,
        .borderColor = params.borderColor,
        .borderStyle = params.borderStyle,
        .borderWidth = params.borderWidth,
        .cancel = params.cancel,
        .cornerRadius = params.cornerRadius,
        .enableHoverMode = params.enableHoverMode,
        .gridCount = params.gridCount,
        .height = params.height,
        .hoverModeArea = params.hoverModeArea,
        .isModal = params.isModal,
        .maskRect = params.maskRect,
        .message = params.message,
        .offset = params.offset,
        .onWillDismiss = params.onWillDismiss,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width
    };
}
void ShowWithOptions(const Ark_AlertDialogParamWithOptions params)
{
    auto dialogProps = CreateDialogProperties(GetPropsWithOptions(params));
    UpdateOptionsButtons(dialogProps, params);
    dialogProps.onLanguageChange = [params, getProps = GetPropsWithOptions,
        updateDialogProperties = UpdateDynamicDialogProperties,
        updateButtons = UpdateOptionsButtons](DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, getProps(params));
        updateButtons(dialogProps, params);
    };

    OHOS::Ace::NG::AlertDialogModelNG model;
    model.SetShowDialog(dialogProps);
}
void ShowImpl(const Ark_Type_AlertDialog_show_value* value)
{
    using DialogParamsVariant = std::variant<
        Ark_AlertDialogParamWithConfirm,
        Ark_AlertDialogParamWithButtons,
        Ark_AlertDialogParamWithOptions
    >;
    auto params = Converter::OptConvert<DialogParamsVariant>(*value);
    if (!params) { return; }
    if (auto paramsWithConfirm = std::get_if<Ark_AlertDialogParamWithConfirm>(&(*params)); paramsWithConfirm) {
        ShowWithConfirm(*paramsWithConfirm);
    } else if (auto paramsWithButtons = std::get_if<Ark_AlertDialogParamWithButtons>(&(*params)); paramsWithButtons) {
        ShowWithButtons(*paramsWithButtons);
    } else if (auto paramsWithOptions = std::get_if<Ark_AlertDialogParamWithOptions>(&(*params)); paramsWithOptions) {
        ShowWithOptions(*paramsWithOptions);
    }
}
} // AlertDialogAccessor
const GENERATED_ArkUIAlertDialogAccessor* GetAlertDialogAccessor()
{
    static const GENERATED_ArkUIAlertDialogAccessor AlertDialogAccessorImpl {
        AlertDialogAccessor::ShowImpl,
    };
    return &AlertDialogAccessorImpl;
}

}
