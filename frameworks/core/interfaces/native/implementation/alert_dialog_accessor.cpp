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

namespace {
constexpr int32_t PRIMARY_BUTTON_COUNT_MAX = 1;
};

namespace OHOS::Ace::NG {
struct DialogPropsForUpdate {
    Opt_DialogAlignment alignment;
    Opt_Boolean autoCancel;
    Opt_BlurStyle backgroundBlurStyle;
    Opt_BackgroundBlurStyleOptions backgroundBlurStyleOptions;
    Opt_BackgroundEffectOptions backgroundEffect;
    Opt_ResourceColor backgroundColor;
    Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors borderColor;
    Opt_Union_BorderStyle_EdgeStyles borderStyle;
    Opt_Union_Dimension_EdgeWidths_LocalizedEdgeWidths borderWidth;
    Opt_VoidCallback cancel;
    Opt_Union_Dimension_BorderRadiuses_LocalizedBorderRadiuses cornerRadius;
    Opt_Boolean enableHoverMode;
    Opt_Int32 gridCount;
    Opt_Dimension height;
    Opt_HoverModeAreaType hoverModeArea;
    Opt_Boolean isModal;
    Opt_Rectangle maskRect;
    Ark_ResourceStr message;
    Opt_Offset offset;
    Opt_Callback_DismissDialogAction_Void onWillDismiss;
    Opt_Callback_Void onDidAppear;
    Opt_Callback_Void onDidDisappear;
    Opt_Callback_Void onWillAppear;
    Opt_Callback_Void onWillDisappear;
    Opt_Union_ShadowOptions_ShadowStyle shadow;
    Opt_Boolean showInSubWindow;
    Opt_ResourceStr subtitle;
    Opt_ResourceStr title;
    Opt_AlertDialogTextStyleOptions textStyle;
    Opt_TransitionEffect transition;
    Opt_Dimension width;
    Opt_LevelMode levelMode;
    Opt_Int32 levelUniqueId;
    Opt_ImmersiveMode immersiveMode;
    Opt_LevelOrder levelOrder;
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
    auto text = Converter::OptConvert<std::string>(src.value);
    if (text) {
        info.text = text.value();
    }
    auto enabled = Converter::OptConvert<bool>(src.enabled);
    if (enabled) {
        info.enabled = enabled.value();
    }
    auto defaultFocus = Converter::OptConvert<bool>(src.defaultFocus);
    if (defaultFocus) {
        info.defaultFocus = defaultFocus.value();
    }
    info.dlgButtonStyle = Converter::OptConvert<DialogButtonStyle>(src.style);
    auto textColor = Converter::OptConvert<Color>(src.fontColor);
    if (textColor) {
        info.textColor = textColor.value().ColorToString();
    }
    auto backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    if (backgroundColor) {
        info.isBgColorSetted = true;
        info.bgColor = backgroundColor.value();
    }
    auto arkCallbackOpt = Converter::OptConvert<VoidCallback>(src.action);
    if (arkCallbackOpt) {
        auto gestureEvent = [arkCallback = CallbackHelper(*arkCallbackOpt)](
                                const GestureEvent& info) -> void { arkCallback.Invoke(); };
        info.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
    }
    auto primary = Converter::OptConvert<bool>(src.primary);
    if (primary) {
        info.isPrimary = primary.value();
    }
    return info;
}

template<>
ButtonInfo Convert(const Ark_AlertDialogButtonBaseOptions& src)
{
    ButtonInfo info;
    auto text = Converter::OptConvert<std::string>(src.value);
    if (text) {
        info.text = text.value();
    }
    auto  enabled = Converter::OptConvert<bool>(src.enabled);
    if (enabled) {
        info.enabled = enabled.value();
    }
    auto defaultFocus = Converter::OptConvert<bool>(src.defaultFocus);
    if (defaultFocus) {
        info.defaultFocus = defaultFocus.value();
    }
    info.dlgButtonStyle = Converter::OptConvert<DialogButtonStyle>(src.style);
    auto textColor = Converter::OptConvert<Color>(src.fontColor);
    if (textColor) {
        info.textColor = textColor.value().ColorToString();
    }
    auto backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    if (backgroundColor) {
        info.isBgColorSetted = true;
        info.bgColor = backgroundColor.value();
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
void UpdateDialogAlignmentForRtl(DialogAlignment& alignment)
{
    switch (alignment) {
        case DialogAlignment::TOP_START:
            alignment = DialogAlignment::TOP_END;
            break;
        case DialogAlignment::TOP_END:
            alignment = DialogAlignment::TOP_START;
            break;
        case DialogAlignment::CENTER_START:
            alignment = DialogAlignment::CENTER_END;
            break;
        case DialogAlignment::CENTER_END:
            alignment = DialogAlignment::CENTER_START;
            break;
        case DialogAlignment::BOTTOM_START:
            alignment = DialogAlignment::BOTTOM_END;
            break;
        case DialogAlignment::BOTTOM_END:
            alignment = DialogAlignment::BOTTOM_START;
            break;
        default:
            break;
    }
}
void UpdateDynamicDialogProperties(DialogProperties& dialogProps, const DialogPropsForUpdate props)
{
    auto title = Converter::OptConvert<std::string>(props.title);
    if (title) {
        dialogProps.title = title.value();
    }
    auto subtitle = Converter::OptConvert<std::string>(props.subtitle);
    if (subtitle) {
        dialogProps.subtitle = subtitle.value();
    }
    auto message = Converter::OptConvert<std::string>(props.message);
    if (message) {
        dialogProps.content = message.value();
    }
    dialogProps.shadow = Converter::OptConvert<Shadow>(props.shadow);
    dialogProps.borderWidth = Converter::OptConvert<BorderWidthProperty>(props.borderWidth);
    if (dialogProps.borderWidth) {
        BorderColorProperty borderColor;
        borderColor.SetColor(Color::BLACK);
        dialogProps.borderColor = Converter::OptConvert<BorderColorProperty>(props.borderColor).value_or(borderColor);
        BorderStyleProperty borderStyle;
        borderStyle.SetBorderStyle(BorderStyle::SOLID);
        dialogProps.borderStyle = Converter::OptConvert<BorderStyleProperty>(props.borderStyle).value_or(borderStyle);
    }
    dialogProps.borderRadius = Converter::OptConvert<BorderRadiusProperty>(props.cornerRadius);
    auto alignment = Converter::OptConvert<DialogAlignment>(props.alignment);
    if (alignment) {
        dialogProps.alignment = alignment.value();
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (isRtl) {
            UpdateDialogAlignmentForRtl(dialogProps.alignment);
        }
    }
    auto offset = Converter::OptConvert<DimensionOffset>(props.offset);
    if (offset) {
        dialogProps.offset = offset.value();
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        Dimension offsetX = isRtl ? dialogProps.offset.GetX() * (-1) : dialogProps.offset.GetX();
        dialogProps.offset.SetX(offsetX);
    }
    auto maskRect = Converter::OptConvert<DimensionRect>(props.maskRect);
    if (maskRect) {
        dialogProps.maskRect = maskRect.value();
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        auto offset = maskRect.value().GetOffset();
        Dimension offsetX = isRtl ? offset.GetX() * (-1) : offset.GetX();
        offset.SetX(offsetX);
        dialogProps.maskRect->SetOffset(offset);
    }
    auto textStyle = Converter::OptConvert<Ark_AlertDialogTextStyleOptions>(props.textStyle);
    if (textStyle) {
        auto wordBreak = Converter::OptConvert<WordBreak>(textStyle.value().wordBreak);
        if (wordBreak) {
            dialogProps.wordBreak = wordBreak.value();
        }
    }
    auto transitionEffect = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(props.transition);
    if (transitionEffect) {
        dialogProps.transitionEffect = transitionEffect.value();
    }
    auto dialogLevelMode = Converter::OptConvert<LevelMode>(props.levelMode);
    if (!Converter::OptConvert<bool>(props.showInSubWindow).value_or(false) && dialogLevelMode) {
        dialogProps.dialogLevelMode = dialogLevelMode.value();
    }
    auto dialogLevelUniqueId = Converter::OptConvert<int32_t>(props.levelUniqueId);
    if (dialogLevelUniqueId) {
        dialogProps.dialogLevelUniqueId = dialogLevelUniqueId.value();
    }
    auto dialogImmersiveMode = Converter::OptConvert<ImmersiveMode>(props.immersiveMode);
    if (dialogImmersiveMode) {
        dialogProps.dialogImmersiveMode = dialogImmersiveMode.value();
    }
}
DialogProperties CreateDialogProperties(const DialogPropsForUpdate props)
{
    DialogProperties dialogProps { .type = DialogType::ALERT_DIALOG, .isAlertDialog = true };
    UpdateDynamicDialogProperties(dialogProps, props);
    auto gridCount = Converter::OptConvert<int32_t>(props.gridCount);
    if (gridCount) {
        dialogProps.gridCount = gridCount.value();
    }
    auto backgroundBlurStyle = Converter::OptConvert<BlurStyle>(props.backgroundBlurStyle);
    if (backgroundBlurStyle) {
        dialogProps.backgroundBlurStyle = static_cast<int32_t>(backgroundBlurStyle.value());
    }
    dialogProps.blurStyleOption = Converter::OptConvert<BlurStyleOption>(props.backgroundBlurStyleOptions);
    dialogProps.effectOption = Converter::OptConvert<EffectOption>(props.backgroundEffect);
    dialogProps.backgroundColor = Converter::OptConvert<Color>(props.backgroundColor);
    auto enableHoverMode = Converter::OptConvert<bool>(props.enableHoverMode);
    if (enableHoverMode) {
        dialogProps.enableHoverMode = enableHoverMode.value();
    }
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(props.hoverModeArea);
    auto autoCancel = Converter::OptConvert<bool>(props.autoCancel);
    if (autoCancel) {
        dialogProps.autoCancel = autoCancel.value();
    }
    auto isModal = Converter::OptConvert<bool>(props.isModal);
    if (isModal) {
        dialogProps.isModal = isModal.value();
    }
    auto isShowInSubWindow = Converter::OptConvert<bool>(props.showInSubWindow);
    if (isShowInSubWindow) {
#if defined(PREVIEW)
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
#else
        dialogProps.isShowInSubWindow = isShowInSubWindow.value();
#endif
    }
    dialogProps.width = Converter::OptConvert<CalcDimension>(props.width);
    dialogProps.height = Converter::OptConvert<CalcDimension>(props.height);

    AddOnWillDismiss(dialogProps, props.onWillDismiss);
    auto onDidAppear = Converter::OptConvert<Callback_Void>(props.onDidAppear);
    if (onDidAppear) {
        dialogProps.onDidAppear = [arkCallback = CallbackHelper(onDidAppear.value())]() { arkCallback.InvokeSync(); };
    }
    auto onDidDisappear = Converter::OptConvert<Callback_Void>(props.onDidDisappear);
    if (onDidDisappear) {
        dialogProps.onDidDisappear = [arkCallback = CallbackHelper(onDidDisappear.value())]() { arkCallback.Invoke(); };
    }
    auto onWillAppear = Converter::OptConvert<Callback_Void>(props.onWillAppear);
    if (onWillAppear) {
        dialogProps.onWillAppear = [arkCallback = CallbackHelper(onWillAppear.value())]() { arkCallback.Invoke(); };
    }
    auto onWillDisappear = Converter::OptConvert<Callback_Void>(props.onWillDisappear);
    if (onWillDisappear) {
        dialogProps.onWillDisappear = [arkCallback = CallbackHelper(onWillDisappear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(props.cancel);
    if (cancelCallbackOpt) {
        auto cancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogProps.onCancel = cancelFunc;
    }
    dialogProps.onLanguageChange = [props, updateDialogProperties = UpdateDynamicDialogProperties](
        DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, props);
    };
    dialogProps.levelOrder = std::make_optional(LevelOrder::ORDER_DEFAULT);
    auto levelOrder = Converter::OptConvert<double>(props.levelOrder);
    if (!dialogProps.isShowInSubWindow && levelOrder) {
        dialogProps.levelOrder = levelOrder.value();
    }
    return dialogProps;
}
DialogPropsForUpdate GetPropsWithConfirm(const Ark_AlertDialogParamWithConfirm params)
{
    return {
        .alignment = params.alignment,
        .autoCancel = params.autoCancel,
        .backgroundBlurStyle = params.backgroundBlurStyle,
        .backgroundBlurStyleOptions = params.backgroundBlurStyleOptions,
        .backgroundEffect = params.backgroundEffect,
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
        .onDidAppear = params.onDidAppear,
        .onDidDisappear = params.onDidDisappear,
        .onWillAppear = params.onWillAppear,
        .onWillDisappear = params.onWillDisappear,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width,
        .levelMode = params.levelMode,
        .levelUniqueId = params.levelUniqueId,
        .immersiveMode = params.immersiveMode,
        .levelOrder = params.levelOrder
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
        .backgroundBlurStyleOptions = params.backgroundBlurStyleOptions,
        .backgroundEffect = params.backgroundEffect,
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
        .onDidAppear = params.onDidAppear,
        .onDidDisappear = params.onDidDisappear,
        .onWillAppear = params.onWillAppear,
        .onWillDisappear = params.onWillDisappear,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width,
        .levelMode = params.levelMode,
        .levelUniqueId = params.levelUniqueId,
        .immersiveMode = params.immersiveMode,
        .levelOrder = params.levelOrder
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
    std::vector<ButtonInfo> buttonArray;
    auto buttons = Converter::Convert<std::vector<ButtonInfo>>(params.buttons);
    for (const auto& button : buttons) {
        if (button.IsValid()) {
            buttonArray.emplace_back(button);
        }
    }
    std::function<bool(ButtonInfo)> isPrimary = [](ButtonInfo button) {
        return button.isPrimary;
    };
    int32_t primaryButtonCount = std::count_if(buttonArray.begin(), buttonArray.end(), isPrimary);
    if (primaryButtonCount > PRIMARY_BUTTON_COUNT_MAX) {
        for (auto& button : buttonArray) {
            button.isPrimary = false;
        }
    }
    dialogProps.buttons = buttonArray;

    auto buttonDirection = Converter::OptConvert<DialogButtonDirection>(params.buttonDirection);
    if (buttonDirection) {
        dialogProps.buttonDirection = buttonDirection.value();
    }
}
DialogPropsForUpdate GetPropsWithOptions(const Ark_AlertDialogParamWithOptions params)
{
    return {
        .alignment = params.alignment,
        .autoCancel = params.autoCancel,
        .backgroundBlurStyle = params.backgroundBlurStyle,
        .backgroundBlurStyleOptions = params.backgroundBlurStyleOptions,
        .backgroundEffect = params.backgroundEffect,
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
        .onDidAppear = params.onDidAppear,
        .onDidDisappear = params.onDidDisappear,
        .onWillAppear = params.onWillAppear,
        .onWillDisappear = params.onWillDisappear,
        .shadow = params.shadow,
        .showInSubWindow = params.showInSubWindow,
        .subtitle = params.subtitle,
        .title = params.title,
        .textStyle = params.textStyle,
        .transition = params.transition,
        .width = params.width,
        .levelMode = params.levelMode,
        .levelUniqueId = params.levelUniqueId,
        .immersiveMode = params.immersiveMode,
        .levelOrder = params.levelOrder
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
void ShowImpl(const Ark_Union_AlertDialogParamWithConfirm_AlertDialogParamWithButtons_AlertDialogParamWithOptions* value)
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
