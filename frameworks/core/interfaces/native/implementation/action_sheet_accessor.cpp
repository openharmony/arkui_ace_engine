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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/overlay/level_order.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
DimensionOffset Convert(const Ark_ActionSheetOffset& src)
{
    return DimensionOffset(OptConvert<Dimension>(src.dx).value_or(Dimension()),
        OptConvert<Dimension>(src.dy).value_or(Dimension()));
}

template<>
ActionSheetInfo Convert(const Ark_SheetInfo& src)
{
    ActionSheetInfo info;
    auto title = Converter::OptConvert<std::string>(src.title);
    if (title) {
        info.title = *title;
    }
    auto icon = Converter::OptConvert<std::string>(src.icon);
    if (icon) {
        info.icon = *icon;
    }

    auto action = Converter::OptConvert<VoidCallback>(src.action);
    if (action.has_value()) {
        auto onClick = [callback = CallbackHelper(*action)](GestureEvent& gestureInfo) { callback.Invoke(); };
        info.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(onClick));
    } else {
        info.action = nullptr;
    }
    return info;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace {
const DimensionOffset DEFAULT_OFFSET = DimensionOffset(0.0_vp, -40.0_vp);
const DimensionOffset DEFAULT_OFFSET_TOP = DimensionOffset(0.0_vp, 40.0_vp);
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ActionSheetAccessor {
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

void CreateConfirmButton(DialogProperties& dialogProps, const Ark_ActionSheetOptions options)
{
    auto confirmInfoOpt = Converter::OptConvert<Ark_ActionSheetButtonOptions>(options.confirm);
    auto text = confirmInfoOpt ? Converter::OptConvert<std::string>(confirmInfoOpt->value) : nullptr;
    if (text) {
        ButtonInfo confirmInfo { .text = *text };
        auto arkCallbackOpt = Converter::OptConvert<VoidCallback>(confirmInfoOpt->action);
        if (arkCallbackOpt) {
            auto gestureEvent = [arkCallback = CallbackHelper(*arkCallbackOpt)](
                                    const GestureEvent& info) -> void { arkCallback.Invoke(); };
            confirmInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
        }
        auto enabled = Converter::OptConvert<bool>(confirmInfoOpt->enabled);
        if (enabled) {
            confirmInfo.enabled = enabled.value();
        }
        auto defaultFocus = Converter::OptConvert<bool>(confirmInfoOpt->defaultFocus);
        if (defaultFocus) {
            confirmInfo.defaultFocus = defaultFocus.value();
        }
        if (!confirmInfo.defaultFocus) {
            confirmInfo.isPrimary = true;
        }
        confirmInfo.dlgButtonStyle = Converter::OptConvert<DialogButtonStyle>(confirmInfoOpt->style);
        if (confirmInfo.IsValid()) {
            dialogProps.buttons.clear();
            dialogProps.buttons.emplace_back(confirmInfo);
        }
    }
}
void UpdateDynamicDialogProperties(DialogProperties& dialogProps, const Ark_ActionSheetOptions options)
{
    auto title = Converter::OptConvert<std::string>(options.title);
    if (title) {
        dialogProps.title = title.value();
    }
    auto subtitle = Converter::OptConvert<std::string>(options.subtitle);
    if (subtitle) {
        dialogProps.subtitle = subtitle.value();
    }
    auto content = Converter::OptConvert<std::string>(options.message);
    if (content) {
        dialogProps.content = content.value();
    }
    CreateConfirmButton(dialogProps, options);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogProps.borderWidth = Converter::OptConvert<BorderWidthProperty>(options.borderWidth);
    if (dialogProps.borderWidth) {
        BorderColorProperty borderColor;
        borderColor.SetColor(Color::BLACK);
        dialogProps.borderColor = Converter::OptConvert<BorderColorProperty>(options.borderColor).value_or(borderColor);
        BorderStyleProperty borderStyle;
        borderStyle.SetBorderStyle(BorderStyle::SOLID);
        dialogProps.borderStyle = Converter::OptConvert<BorderStyleProperty>(options.borderStyle).value_or(borderStyle);
    }
    dialogProps.borderRadius = Converter::OptConvert<BorderRadiusProperty>(options.cornerRadius);
    auto alignment = Converter::OptConvert<DialogAlignment>(options.alignment);
    if (alignment) {
        dialogProps.alignment = alignment.value();
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (isRtl) {
            UpdateDialogAlignmentForRtl(dialogProps.alignment);
        }
        if (dialogProps.alignment == DialogAlignment::TOP || dialogProps.alignment == DialogAlignment::TOP_START ||
            dialogProps.alignment == DialogAlignment::TOP_END) {
            dialogProps.offset = DEFAULT_OFFSET_TOP;
        }
    }
    auto offset = Converter::OptConvert<DimensionOffset>(options.offset);
    if (offset) {
        dialogProps.offset = offset.value();
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        Dimension offsetX = isRtl ? dialogProps.offset.GetX() * (-1) : dialogProps.offset.GetX();
        dialogProps.offset.SetX(offsetX);
    }
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    dialogProps.sheetsInfo = Converter::Convert<std::vector<ActionSheetInfo>>(options.sheets);
    auto transitionEffect = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(options.transition);
    if (transitionEffect) {
        dialogProps.transitionEffect = transitionEffect.value();
    }
    auto dialogLevelMode = Converter::OptConvert<LevelMode>(options.levelMode);
    if (!Converter::OptConvert<bool>(options.showInSubWindow).value_or(false) && dialogLevelMode) {
        dialogProps.dialogLevelMode = dialogLevelMode.value();
    }
    auto dialogLevelUniqueId = Converter::OptConvert<int32_t>(options.levelUniqueId);
    if (dialogLevelUniqueId) {
        dialogProps.dialogLevelUniqueId = dialogLevelUniqueId.value();
    }
    auto dialogImmersiveMode = Converter::OptConvert<ImmersiveMode>(options.immersiveMode);
    if (dialogImmersiveMode) {
        dialogProps.dialogImmersiveMode = dialogImmersiveMode.value();
    }
}
void ShowImpl(const Ark_ActionSheetOptions* value)
{
    DialogProperties dialogProps {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = DEFAULT_OFFSET
    };
    UpdateDynamicDialogProperties(dialogProps, *value);
    dialogProps.sheetsInfo = Converter::Convert<std::vector<ActionSheetInfo>>(value->sheets);
    auto backgroundBlurStyle = Converter::OptConvert<BlurStyle>(value->backgroundBlurStyle);
    if (backgroundBlurStyle) {
        dialogProps.backgroundBlurStyle = static_cast<int32_t>(backgroundBlurStyle.value());
    }
    dialogProps.blurStyleOption = Converter::OptConvert<BlurStyleOption>(value->backgroundBlurStyleOptions);
    dialogProps.effectOption = Converter::OptConvert<EffectOption>(value->backgroundEffect);
    dialogProps.backgroundColor = Converter::OptConvert<Color>(value->backgroundColor);
    auto enableHoverMode = Converter::OptConvert<bool>(value->enableHoverMode);
    if (enableHoverMode) {
        dialogProps.enableHoverMode = enableHoverMode.value();
    }
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(value->hoverModeArea);
    auto autoCancel = Converter::OptConvert<bool>(value->autoCancel);
    if (autoCancel) {
        dialogProps.autoCancel = autoCancel.value();
    }
    auto isModal = Converter::OptConvert<bool>(value->isModal);
    if (isModal) {
        dialogProps.isModal = isModal.value();
    }
    auto isShowInSubWindow = Converter::OptConvert<bool>(value->showInSubWindow);
    if (isShowInSubWindow) {
#if defined(PREVIEW)
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
#else
        dialogProps.isShowInSubWindow = isShowInSubWindow.value();
#endif
    }
    dialogProps.width = Converter::OptConvert<CalcDimension>(value->width);
    dialogProps.height = Converter::OptConvert<CalcDimension>(value->height);

    AddOnWillDismiss(dialogProps, value->onWillDismiss);
    auto onDidAppear = Converter::OptConvert<Callback_Void>(value->onDidAppear);
    if (onDidAppear) {
        dialogProps.onDidAppear = [arkCallback = CallbackHelper(onDidAppear.value())]() { arkCallback.InvokeSync(); };
    }
    auto onDidDisappear = Converter::OptConvert<Callback_Void>(value->onDidDisappear);
    if (onDidDisappear) {
        dialogProps.onDidDisappear = [arkCallback = CallbackHelper(onDidDisappear.value())]() { arkCallback.Invoke(); };
    }
    auto onWillAppear = Converter::OptConvert<Callback_Void>(value->onWillAppear);
    if (onWillAppear) {
        dialogProps.onWillAppear = [arkCallback = CallbackHelper(onWillAppear.value())]() { arkCallback.Invoke(); };
    }
    auto onWillDisappear = Converter::OptConvert<Callback_Void>(value->onWillDisappear);
    if (onWillDisappear) {
        dialogProps.onWillDisappear = [arkCallback = CallbackHelper(onWillDisappear.value())]() {
            arkCallback.Invoke();
        };
    }
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(value->cancel);
    if (cancelCallbackOpt) {
        auto cancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogProps.onCancel = cancelFunc;
    }
    dialogProps.onLanguageChange = [actionSheetValue = *value, updateDialogProperties = UpdateDynamicDialogProperties](
        DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, actionSheetValue);
    };
    dialogProps.levelOrder = std::make_optional(LevelOrder::ORDER_DEFAULT);
    auto levelOrder = Converter::OptConvert<double>(value->levelOrder);
    if (!dialogProps.isShowInSubWindow && levelOrder) {
        dialogProps.levelOrder = levelOrder.value();
    }
    OHOS::Ace::NG::ActionSheetModelNG sheetModel;
    sheetModel.ShowActionSheet(dialogProps);
}
} // ActionSheetAccessor
const GENERATED_ArkUIActionSheetAccessor* GetActionSheetAccessor()
{
    static const GENERATED_ArkUIActionSheetAccessor ActionSheetAccessorImpl {
        ActionSheetAccessor::ShowImpl,
    };
    return &ActionSheetAccessorImpl;
}

}
