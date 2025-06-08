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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/dialog_common.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/base/view_abstract.h"
#include "arkoala_api_generated.h"

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
    if (title) { info.title = *title; }
    auto icon = Converter::OptConvert<std::string>(src.icon);
    if (icon) { info.icon = *icon; }
    
    auto action = Converter::OptConvert<VoidCallback>(src.action);
    auto onClick = [callback = CallbackHelper(*action)](GestureEvent& info) {
        callback.Invoke();
    };
    info.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(onClick));
    return info;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace {
const DimensionOffset DEFAULT_OFFSET = DimensionOffset(0.0_vp, -40.0_vp);
const DimensionOffset DEFAULT_OFFSET_TOP = DimensionOffset(0.0_vp, 40.0_vp);
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ActionSheetAccessor {
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
        confirmInfo.enabled = Converter::OptConvert<bool>(confirmInfoOpt->enabled).value_or(confirmInfo.enabled);
        confirmInfo.defaultFocus =
            Converter::OptConvert<bool>(confirmInfoOpt->defaultFocus).value_or(confirmInfo.defaultFocus);
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
    dialogProps.title = Converter::OptConvert<std::string>(options.title).value_or("");
    dialogProps.subtitle = Converter::OptConvert<std::string>(options.subtitle).value_or("");
    dialogProps.content = Converter::OptConvert<std::string>(options.message).value_or("");
    CreateConfirmButton(dialogProps, options);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogProps.borderWidth = Converter::OptConvert<BorderWidthProperty>(options.borderWidth);
    dialogProps.borderColor = Converter::OptConvert<BorderColorProperty>(options.borderColor);
    dialogProps.borderRadius = Converter::OptConvert<BorderRadiusProperty>(options.cornerRadius);
    dialogProps.borderStyle = Converter::OptConvert<BorderStyleProperty>(options.borderStyle);
    dialogProps.alignment = Converter::OptConvert<DialogAlignment>(
        options.alignment).value_or(DialogAlignment::BOTTOM);
    auto isTopAligned = dialogProps.alignment == DialogAlignment::TOP
        || dialogProps.alignment == DialogAlignment::TOP_START
        || dialogProps.alignment == DialogAlignment::TOP_END;
    dialogProps.offset = Converter::OptConvert<DimensionOffset>(options.offset).value_or(
        isTopAligned ? DEFAULT_OFFSET_TOP : DEFAULT_OFFSET
    );
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    dialogProps.sheetsInfo = Converter::Convert<std::vector<ActionSheetInfo>>(options.sheets);
    auto transition = Converter::OptConvert<RefPtr<NG::ChainedTransitionEffect>>(options.transition);
    if (transition) {
        dialogProps.transitionEffect = *transition;
    }
}
void ShowImpl(const Ark_ActionSheetOptions* value)
{
    DialogProperties dialogProps {
        .type = DialogType::ACTION_SHEET
    };
    UpdateDynamicDialogProperties(dialogProps, *value);
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        value->backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(value->backgroundColor);
    dialogProps.enableHoverMode =
        Converter::OptConvert<bool>(value->enableHoverMode);
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(value->hoverModeArea);
    dialogProps.autoCancel = Converter::OptConvert<bool>(value->autoCancel).value_or(dialogProps.autoCancel);
    dialogProps.isModal = Converter::OptConvert<bool>(value->isModal).value_or(dialogProps.isModal);
    dialogProps.isShowInSubWindow =
        Converter::OptConvert<bool>(value->showInSubWindow).value_or(dialogProps.isShowInSubWindow);
    dialogProps.width = Converter::OptConvert<CalcDimension>(value->width);
    dialogProps.height = Converter::OptConvert<CalcDimension>(value->height);

    AddOnWillDismiss(dialogProps, value->onWillDismiss);
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(value->cancel);
    if (cancelCallbackOpt) {
        auto cancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogProps.onCancel = cancelFunc;
    }
    dialogProps.onLanguageChange = [value, updateDialogProperties = UpdateDynamicDialogProperties](
        DialogProperties& dialogProps) {
        updateDialogProperties(dialogProps, *value);
    };
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
