/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_alert_dialog_ffi.h"

#include "cj_lambda.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "bridge/common/utils/engine_helper.h"

using namespace OHOS::Ace;

namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<DialogButtonDirection> DIALOG_BUTTONS_DIRECTION = { DialogButtonDirection::AUTO,
    DialogButtonDirection::HORIZONTAL, DialogButtonDirection::VERTICAL };

constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

extern "C" {
    static void ParseAlertDialogConfirm(NativeAlertDialogParam alertDialog, DialogProperties& properties)
    {
        // Parse title.
        properties.title = std::string(alertDialog.title);

        // Parse subtitle.
        properties.subtitle = std::string(alertDialog.subtitle);

        // Parses message.
        properties.content = std::string(alertDialog.message);

        // Parse autoCancel.
        properties.autoCancel = alertDialog.autoCancel;

        // Parse cancel.
        auto cancel = [lambda = CJLambda::Create(alertDialog.cancel)]() {
            lambda();
        };
        AlertDialogModel::GetInstance()->SetOnCancel(cancel, properties);

        // Parse alignment
        auto alignment = alertDialog.alignment;
        if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            properties.alignment = DIALOG_ALIGNMENT[alignment];
        }

        // Parse offset
        double dxVal = alertDialog.offset.dx.value;
        int32_t dxType = alertDialog.offset.dx.unitType;
        CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));

        double dyVal = alertDialog.offset.dy.value;
        int32_t dyType = alertDialog.offset.dy.unitType;
        CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
        properties.offset = DimensionOffset(dx, dy);

        // Parses gridCount.
        properties.gridCount = alertDialog.gridCount;

        // Parse maskRect.
        Dimension xDimen = Dimension(alertDialog.maskRect.x, static_cast<DimensionUnit>(alertDialog.maskRect.xUnit));
        Dimension yDimen = Dimension(alertDialog.maskRect.y, static_cast<DimensionUnit>(alertDialog.maskRect.yUnit));
        Dimension widthDimen =
            Dimension(alertDialog.maskRect.width, static_cast<DimensionUnit>(alertDialog.maskRect.widthUnit));
        Dimension heightDimen =
            Dimension(alertDialog.maskRect.height, static_cast<DimensionUnit>(alertDialog.maskRect.heightUnit));
        DimensionOffset offsetDimen(xDimen, yDimen);
        properties.maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);

        // Parse showInSubWindowValue.
        properties.isShowInSubWindow = alertDialog.showInSubWindow;

        // Parse isModal.
        properties.isModal = alertDialog.isModal;

        // Parse backgroundColor.
        Color backgroundColor = Color(ColorAlphaAdapt(alertDialog.backgroundColor));
        properties.backgroundColor = backgroundColor;

        // Parse backgroundColor.
        int32_t blurStyle = alertDialog.backgroundBlurStyle;
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            properties.backgroundBlurStyle = blurStyle;
        }
    }

    static void ParseButtonObj(
        DialogProperties& properties,
        NativeAlertDialogButtonOptions objInner,
        const std::string& property)
    {
        ButtonInfo buttonInfo;
        // Parse enabled
        buttonInfo.enabled = objInner.enabled;

        // Parse defaultFocus
        buttonInfo.defaultFocus = objInner.defaultFocus;

        // Parse style
        if (objInner.style != nullptr) {
            int32_t styleValue = *objInner.style;
            if (styleValue >= static_cast<int32_t>(DialogButtonStyle::DEFAULT) &&
                styleValue <= static_cast<int32_t>(DialogButtonStyle::HIGHTLIGHT)) {
                buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(styleValue);
            }
        }

        // Parse value
        buttonInfo.text = std::string(objInner.value);

        // Parse fontColor
        if (objInner.fontColor != nullptr) {
            Color fontColor = Color(ColorAlphaAdapt(*objInner.fontColor));
            buttonInfo.textColor = fontColor.ColorToString();
        }

        // Parse backgroundColor
        if (objInner.backgroundColor != nullptr) {
            Color backgroundColor = Color(ColorAlphaAdapt(*objInner.backgroundColor));
            buttonInfo.isBgColorSetted = true;
            buttonInfo.bgColor = backgroundColor;
        }

        // Parse action
        auto action = [lambda = CJLambda::Create(objInner.action)]() {
            lambda();
        };
        AlertDialogModel::GetInstance()->SetParseButtonObj(action, buttonInfo, properties, property);

        if (buttonInfo.IsValid()) {
            properties.buttons.emplace_back(buttonInfo);
        }
    }

    void FfiOHOSShowAlertDialogParamWithConfirm(
        NativeAlertDialogParam alertDialog,
        NativeAlertDialogButtonOptions confirm)
    {
        DialogProperties properties { .type = DialogType::ALERT_DIALOG };

        // Parse common Param.
        ParseAlertDialogConfirm(alertDialog, properties);

        ParseButtonObj(properties, confirm, "confirm");

        AlertDialogModel::GetInstance()->SetShowDialog(properties);
    }

    void FfiOHOSShowAlertDialogParamWithButtons(
        NativeAlertDialogParam alertDialog,
        NativeAlertDialogButtonOptions primaryButton,
        NativeAlertDialogButtonOptions secondaryButton)
    {
        DialogProperties properties { .type = DialogType::ALERT_DIALOG };

        // Parse common Param.
        ParseAlertDialogConfirm(alertDialog, properties);

        // Parse primaryButton and secondaryButton.
        ParseButtonObj(properties, primaryButton, "primaryButton");

        ParseButtonObj(properties, secondaryButton, "secondaryButton");

        AlertDialogModel::GetInstance()->SetShowDialog(properties);
    }

    void ParseButtonArray(
        DialogProperties& properties,
        CArrNativeAlertDialogButtonOptions buttons,
        const std::string& property)
    {
        if (buttons.size <= 0) {
            return;
        }
        for (int32_t i = 0; i < buttons.size; i++) {
            NativeAlertDialogButtonOptions buttonItem = buttons.head[i];
            ParseButtonObj(properties, buttonItem, property + std::to_string(i));
        }
    }

    void FfiOHOSShowAlertDialogParamWithOptions(
        NativeAlertDialogParam alertDialog,
        CArrNativeAlertDialogButtonOptions buttons,
        int32_t buttonDirection)
    {
        DialogProperties properties { .type = DialogType::ALERT_DIALOG };

        // Parse common Param.
        ParseAlertDialogConfirm(alertDialog, properties);

        // Parse buttons array.
        ParseButtonArray(properties, buttons, "buttons");

        // Parse buttons direction.
        if (buttonDirection >= 0 && buttonDirection <= static_cast<int32_t>(DIALOG_BUTTONS_DIRECTION.size())) {
            properties.buttonDirection = DIALOG_BUTTONS_DIRECTION[buttonDirection];
        }

        AlertDialogModel::GetInstance()->SetShowDialog(properties);
    }
}
}
