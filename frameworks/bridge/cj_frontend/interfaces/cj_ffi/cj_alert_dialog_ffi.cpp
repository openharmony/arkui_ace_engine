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

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<DialogButtonDirection> DIALOG_BUTTONS_DIRECTION = { DialogButtonDirection::AUTO,
    DialogButtonDirection::HORIZONTAL, DialogButtonDirection::VERTICAL };
const std::vector<WordBreak> WORDBREAK = { WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD,
    WordBreak::HYPHENATION };

constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int32_t ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM = 1;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

extern "C" {
void ParseTitleAndMessage(DialogProperties& properties, NativeAlertDialogParam& alertDialog)
{
    // Parses message.
    properties.content = std::string(alertDialog.message);

    // Parse title.
    if (alertDialog.title.hasValue) {
        properties.title = std::string(alertDialog.title.value);
    }

    // Parse subtitle.
    if (alertDialog.subtitle.hasValue) {
        properties.subtitle = std::string(alertDialog.subtitle.value);
    }
}

void ParseAlignment(DialogProperties& properties, NativeAlertDialogParam& alertDialog)
{
    if (!alertDialog.alignment.hasValue) {
        return;
    }
    auto alignment = alertDialog.alignment.value;
    if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        properties.alignment = DIALOG_ALIGNMENT[alignment];
    }
}

void ParseOffset(DialogProperties& properties, NativeAlertDialogParam& alertDialog)
{
    if (!alertDialog.offset.hasValue) {
        return;
    }
    double dxVal = alertDialog.offset.value.dx.value;
    int32_t dxType = alertDialog.offset.value.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));

    double dyVal = alertDialog.offset.value.dy.value;
    int32_t dyType = alertDialog.offset.value.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    properties.offset = DimensionOffset(dx, dy);
}

void ParseMaskRect(DialogProperties& properties, NativeAlertDialogParam& alertDialog)
{
    if (!alertDialog.maskRect.hasValue) {
        return;
    }
    NativeRectangle nativeRectangle = alertDialog.maskRect.value;
    Dimension xDimen = Dimension(nativeRectangle.x, static_cast<DimensionUnit>(nativeRectangle.xUnit));
    Dimension yDimen = Dimension(nativeRectangle.y, static_cast<DimensionUnit>(nativeRectangle.yUnit));
    Dimension widthDimen = Dimension(nativeRectangle.width, static_cast<DimensionUnit>(nativeRectangle.widthUnit));
    Dimension heightDimen = Dimension(nativeRectangle.height, static_cast<DimensionUnit>(nativeRectangle.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    properties.maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);
}

void ParseBackgroundProp(DialogProperties& properties, NativeAlertDialogParam& alertDialog)
{
    if (alertDialog.backgroundColor.hasValue) {
        Color backgroundColor = Color(ColorAlphaAdapt(alertDialog.backgroundColor.value));
        properties.backgroundColor = backgroundColor;
    }

    if (alertDialog.backgroundBlurStyle.hasValue) {
        int32_t blurStyle = alertDialog.backgroundBlurStyle.value;
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            properties.backgroundBlurStyle = blurStyle;
        }
    }
}

void ParseBorderProps(DialogProperties& properties, NativeAlertDialogParam alertDialog)
{
    if (alertDialog.borderWidth.hasValue) {
        auto nativeBorderWidth = alertDialog.borderWidth.value;
        auto borderWidth = Dimension(nativeBorderWidth.value, static_cast<DimensionUnit>(nativeBorderWidth.unitType));
        auto borderWidthProp = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
        properties.borderWidth = borderWidthProp;
    }

    if (alertDialog.borderColor.hasValue) {
        NG::BorderColorProperty colorProperty;
        Color borderColor = Color(ColorAlphaAdapt(alertDialog.borderColor.value));
        colorProperty.SetColor(borderColor);
        properties.borderColor = colorProperty;
    }

    if (alertDialog.borderStyle.hasValue) {
        NG::BorderStyleProperty borderStyle;
        auto nativeBorderStyle = alertDialog.borderStyle.value;
        borderStyle.styleLeft = static_cast<BorderStyle>(nativeBorderStyle.left);
        borderStyle.styleRight = static_cast<BorderStyle>(nativeBorderStyle.right);
        borderStyle.styleTop = static_cast<BorderStyle>(nativeBorderStyle.top);
        borderStyle.styleBottom = static_cast<BorderStyle>(nativeBorderStyle.bottom);
        borderStyle.multiValued = true;
        properties.borderStyle = borderStyle;
    }

    if (alertDialog.cornerRadius.hasValue) {
        NativeBorderRadiuses nativeBorderRadiuses = alertDialog.cornerRadius.value;
        NG::BorderRadiusProperty radius;
        CalcDimension topLeft(
            nativeBorderRadiuses.topLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topLeftUnit));
        CalcDimension topRight(
            nativeBorderRadiuses.topRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topRightUnit));
        CalcDimension bottomLeft(
            nativeBorderRadiuses.bottomLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomLeftUnit));
        CalcDimension bottomRight(
            nativeBorderRadiuses.bottomRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomRightUnit));
        radius.radiusTopLeft = topLeft;
        radius.radiusTopRight = topRight;
        radius.radiusBottomLeft = bottomLeft;
        radius.radiusBottomRight = bottomRight;
        radius.multiValued = true;
        properties.borderRadius = radius;
    }
}

static void ParseWidthAndHeight(DialogProperties& properties, NativeAlertDialogParam alertDialog)
{
    if (alertDialog.width.hasValue) {
        auto width =
            CalcDimension(alertDialog.width.value.value, static_cast<DimensionUnit>(alertDialog.width.value.unitType));
        properties.width = width;
    }
    if (alertDialog.height.hasValue) {
        auto height = CalcDimension(
            alertDialog.height.value.value, static_cast<DimensionUnit>(alertDialog.height.value.unitType));
        properties.height = height;
    }
}

static void ParseAlertDialogConfirm(NativeAlertDialogParam& alertDialog, DialogProperties& properties)
{
    ParseTitleAndMessage(properties, alertDialog);

    // Parse autoCancel.
    if (alertDialog.autoCancel.hasValue) {
        properties.autoCancel = alertDialog.autoCancel.value;
    }

    // Parse cancel.
    if (alertDialog.cancel.hasValue) {
        auto cancel = [lambda = CJLambda::Create(alertDialog.cancel.value)]() { lambda(); };
        AlertDialogModel::GetInstance()->SetOnCancel(cancel, properties);
    }

    // Parse alignment
    ParseAlignment(properties, alertDialog);

    // Parse offset
    ParseOffset(properties, alertDialog);

    // Parses gridCount.
    if (alertDialog.gridCount.hasValue) {
        properties.gridCount = alertDialog.gridCount.value;
    }

    // Parse maskRect.
    ParseMaskRect(properties, alertDialog);

    // Parse showInSubWindowValue.
    if (alertDialog.showInSubWindow.hasValue) {
        properties.isShowInSubWindow = alertDialog.showInSubWindow.value;
    }

    // Parse isModal.
    if (alertDialog.isModal.hasValue) {
        properties.isModal = alertDialog.isModal.value;
    }

    // Parse backgroundColor and backgroundBlurStyle.
    ParseBackgroundProp(properties, alertDialog);

    // Parse onWillDismiss
    if (alertDialog.onWillDismiss.hasValue) {
        std::function<void(const int32_t& info, const int32_t& id)> onWillDismissFunc =
            [nativeFunc = CJLambda::Create(alertDialog.onWillDismiss.value)](
                const int32_t& info, const int32_t& instanceID) { nativeFunc(info); };
        AlertDialogModel::GetInstance()->SetOnWillDismiss(std::move(onWillDismissFunc), properties);
    }

    // Prase transition
    if (alertDialog.transition.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(alertDialog.transition.value);
        if (nativeTransitionEffect) {
            properties.transitionEffect = nativeTransitionEffect->effect;
        }
    }

    // Paese width and height
    ParseWidthAndHeight(properties, alertDialog);

    // Parse borderProps
    ParseBorderProps(properties, alertDialog);

    // Prase textstyle
    if (alertDialog.textstyle.hasValue) {
        properties.wordBreak = WORDBREAK[alertDialog.textstyle.value];
    }
}

static void ParseButtonObj(DialogProperties& properties, NativeAlertDialogButtonOptions objInner,
    const std::string& property, bool isPrimaryButtonValid)
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
    auto action = [lambda = CJLambda::Create(objInner.action)]() { lambda(); };
    AlertDialogModel::GetInstance()->SetParseButtonObj(action, buttonInfo, properties, property);

    if (!buttonInfo.defaultFocus && isPrimaryButtonValid) {
        if (strcmp(property.c_str(), "confirm") == 0 || strcmp(property.c_str(), "primaryButton") == 0) {
            buttonInfo.isPrimary = true;
        } else {
            buttonInfo.isPrimary = objInner.primary;
        }
    }

    if (buttonInfo.IsValid()) {
        properties.buttons.emplace_back(buttonInfo);
    }
}

void FfiOHOSShowAlertDialogParamWithConfirm(NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    ParseButtonObj(properties, confirm, "confirm", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithConfirmShadowStyle(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm, int32_t shadowStyle)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow
    Shadow shadow;
    auto style = static_cast<ShadowStyle>(shadowStyle);
    auto colorMode = SystemProperties::GetColorMode();
    if (style != ShadowStyle::None) {
        auto container = Container::Current();
        auto pipelineContext = container->GetPipelineContext();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (!shadowTheme) {
            shadow = shadowTheme->GetShadow(style, colorMode);
        }
    }
    properties.shadow = shadow;

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    ParseButtonObj(properties, confirm, "confirm", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithConfirmShadowOptions(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm, NativeShadowOptions shadowOptions)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow.
    Shadow shadow;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(ColorAlphaAdapt(shadowOptions.color));
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    properties.shadow = shadow;

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    ParseButtonObj(properties, confirm, "confirm", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithButtons(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    // Parse primaryButton and secondaryButton.
    ParseButtonObj(properties, primaryButton, "primaryButton", true);

    ParseButtonObj(properties, secondaryButton, "secondaryButton", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithButtonsShadowStyle(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton, int32_t shadowStyle)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow
    Shadow shadow;
    auto style = static_cast<ShadowStyle>(shadowStyle);
    auto colorMode = SystemProperties::GetColorMode();
    if (style != ShadowStyle::None) {
        auto container = Container::Current();
        auto pipelineContext = container->GetPipelineContext();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (!shadowTheme) {
            shadow = shadowTheme->GetShadow(style, colorMode);
        }
    }
    properties.shadow = shadow;

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    // Parse primaryButton and secondaryButton.
    ParseButtonObj(properties, primaryButton, "primaryButton", true);

    ParseButtonObj(properties, secondaryButton, "secondaryButton", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithButtonsShadowOptions(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton,
    NativeShadowOptions shadowOptions)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow.
    Shadow shadow;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(ColorAlphaAdapt(shadowOptions.color));
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    properties.shadow = shadow;

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    // Parse primaryButton and secondaryButton.
    ParseButtonObj(properties, primaryButton, "primaryButton", true);

    ParseButtonObj(properties, secondaryButton, "secondaryButton", true);

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void ParseButtonArray(
    DialogProperties& properties, CArrNativeAlertDialogButtonOptions buttons, const std::string& property)
{
    if (buttons.size <= 0) {
        return;
    }
    int32_t primaryButtonNum = 0;
    bool isPrimaryButtonValid = true;
    for (int32_t i = 0; i < buttons.size; i++) {
        auto primaryButton = buttons.head[i].primary;
        if (primaryButton) {
            primaryButtonNum += (primaryButton ? ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM : 0);
        }
        if (primaryButtonNum > ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM) {
            isPrimaryButtonValid = false;
            break;
        }
    }

    for (int32_t i = 0; i < buttons.size; i++) {
        NativeAlertDialogButtonOptions buttonItem = buttons.head[i];
        ParseButtonObj(properties, buttonItem, property + std::to_string(i), isPrimaryButtonValid);
    }
}

void FfiOHOSShowAlertDialogParamWithOptions(
    NativeAlertDialogParam alertDialog, CArrNativeAlertDialogButtonOptions buttons, int32_t buttonDirection)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse common Param.
    ParseAlertDialogConfirm(alertDialog, properties);

    // Parse buttons array.
    ParseButtonArray(properties, buttons, "buttons");

    // Parse buttons direction.
    if (buttonDirection >= 0 && buttonDirection < static_cast<int32_t>(DIALOG_BUTTONS_DIRECTION.size())) {
        properties.buttonDirection = DIALOG_BUTTONS_DIRECTION[buttonDirection];
    }

    AlertDialogModel::GetInstance()->SetShowDialog(properties);
}

void FfiOHOSShowAlertDialogParamWithOptionsShadowStyle(NativeAlertDialogParam alertDialog,
    CArrNativeAlertDialogButtonOptions buttons, int32_t shadowStyle, int32_t buttonDirection)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow
    Shadow shadow;
    auto style = static_cast<ShadowStyle>(shadowStyle);
    auto colorMode = SystemProperties::GetColorMode();
    if (style != ShadowStyle::None) {
        auto container = Container::Current();
        auto pipelineContext = container->GetPipelineContext();
        auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
        if (!shadowTheme) {
            shadow = shadowTheme->GetShadow(style, colorMode);
        }
    }
    properties.shadow = shadow;

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

void FfiOHOSShowAlertDialogParamWithOptionsShadowOptions(NativeAlertDialogParam alertDialog,
    CArrNativeAlertDialogButtonOptions buttons, NativeShadowOptions shadowOptions, int32_t buttonDirection)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };

    // Parse shadow.
    Shadow shadow;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(ColorAlphaAdapt(shadowOptions.color));
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    properties.shadow = shadow;

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
} // namespace
