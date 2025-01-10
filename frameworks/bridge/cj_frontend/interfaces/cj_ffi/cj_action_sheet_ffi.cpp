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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_action_sheet_ffi.h"

#include <string>
#include <vector>

#include "cj_lambda.h"

#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/models/action_sheet_model_impl.h"
#include "core/common/container.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT = DimensionOffset(0.0_vp, -40.0_vp);
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<DialogButtonDirection> DIALOG_BUTTONS_DIRECTION = { DialogButtonDirection::AUTO,
    DialogButtonDirection::HORIZONTAL, DialogButtonDirection::VERTICAL };

constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

std::function<void(const GestureEvent& event)> FormatGuestureEventFunction(void (*callback)())
{
    std::function<void(const GestureEvent& event)> result = [lambda = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void { lambda(); };
    return result;
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

void ParseTitleAndMessage(DialogProperties& properties, NativeActionSheetOptions& options)
{
    // Parse Title.
    properties.title = std::string(options.title);

    // Parse subTitle
    if (options.subtitle.hasValue) {
        properties.subtitle = std::string(options.subtitle.value);
    }

    // Parse message
    properties.content = std::string(options.message);
}

void ParseConfirmButton(DialogProperties& properties, NativeOptionConfirm& confirm)
{
    if (!confirm.hasValue) {
        return;
    }

    ButtonInfo buttonInfo;

    // Parse value
    buttonInfo.text = std::string(confirm.value.value);
    // Parse enabled
    buttonInfo.enabled = confirm.value.enabled;
    // Parse defaultFocus
    buttonInfo.defaultFocus = confirm.value.defaultFocus;
    // Parse style
    int32_t style = confirm.value.style;
    if (style >= static_cast<int32_t>(DialogButtonStyle::DEFAULT) &&
        style <= static_cast<int32_t>(DialogButtonStyle::HIGHTLIGHT)) {
        buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(style);
    }
    // Parse action
    buttonInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(FormatGuestureEventFunction(confirm.value.action));
    if (!buttonInfo.defaultFocus) {
        buttonInfo.isPrimary = true;
    }
    if (buttonInfo.IsValid()) {
        properties.buttons.clear();
        properties.buttons.emplace_back(buttonInfo);
    }
}

void ParseBorderProps(DialogProperties& properties, NativeActionSheetOptions& options)
{
    if (options.borderWidth.hasValue) {
        auto nativeBorderWidth = options.borderWidth.value;
        auto borderWidth = Dimension(nativeBorderWidth.value, static_cast<DimensionUnit>(nativeBorderWidth.unitType));
        auto borderWidthProp = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
        properties.borderWidth = borderWidthProp;
    }
    if (options.borderColor.hasValue) {
        NG::BorderColorProperty colorProperty;
        Color borderColor = Color(ColorAlphaAdapt(options.borderColor.value));
        colorProperty.SetColor(borderColor);
        properties.borderColor = colorProperty;
    }
    if (options.borderStyle.hasValue) {
        NG::BorderStyleProperty borderStyle;
        auto nativeBorderSytle = options.borderStyle.value;
        borderStyle.styleLeft = static_cast<BorderStyle>(nativeBorderSytle.left);
        borderStyle.styleRight = static_cast<BorderStyle>(nativeBorderSytle.right);
        borderStyle.styleTop = static_cast<BorderStyle>(nativeBorderSytle.top);
        borderStyle.styleBottom = static_cast<BorderStyle>(nativeBorderSytle.bottom);
        borderStyle.multiValued = true;
        properties.borderStyle = borderStyle;
    }
    if (options.cornerRadius.hasValue) {
        NativeBorderRadiuses nativeBorderRadiuses = options.cornerRadius.value;
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

void ParseDialogAlignment(DialogProperties& properties, NativeOptionInt32& options)
{
    if (!options.hasValue) {
        return;
    }
    auto alignment = options.value;
    if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        properties.alignment = DIALOG_ALIGNMENT[alignment];
    }
    if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
        alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
        alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
        properties.offset = ACTION_SHEET_OFFSET_DEFAULT_TOP;
    }
}

void ParseOffset(DialogProperties& properties, NativeOptionOffset& options)
{
    if (!options.hasValue) {
        return;
    }
    double dxVal = options.value.dx.value;
    int32_t dxType = options.value.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));

    double dyVal = options.value.dy.value;
    int32_t dyType = options.value.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    properties.offset = DimensionOffset(dx, dy);
}

void ParseMaskRect(DialogProperties& properties, NativeOptionRect& maskRect)
{
    if (!maskRect.hasValue) {
        return;
    }
    NativeRectangle nativeRectangle = maskRect.value;
    Dimension xDimen = Dimension(nativeRectangle.x, static_cast<DimensionUnit>(nativeRectangle.xUnit));
    Dimension yDimen = Dimension(nativeRectangle.y, static_cast<DimensionUnit>(nativeRectangle.yUnit));
    Dimension widthDimen = Dimension(nativeRectangle.width, static_cast<DimensionUnit>(nativeRectangle.widthUnit));
    Dimension heightDimen = Dimension(nativeRectangle.height, static_cast<DimensionUnit>(nativeRectangle.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    properties.maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);
}

void ParseSheets(DialogProperties& properties, NativeSheetInfoArray& sheets)
{
    std::vector<ActionSheetInfo> sheetsInfo;
    auto size = sheets.size;
    auto nativeSheetInfo = sheets.sheetInfo;
    for (size_t i = 0; i < static_cast<size_t>(size); i++) {
        ActionSheetInfo sheetInfo;
        sheetInfo.title = std::string(nativeSheetInfo[i].title);
        sheetInfo.icon = std::string(nativeSheetInfo[i].icon);
        sheetInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(FormatGuestureEventFunction(nativeSheetInfo[i].action));
        sheetsInfo.emplace_back(sheetInfo);
    }
    properties.sheetsInfo = std::move(sheetsInfo);
}

void ParseWidthAndHeight(DialogProperties& properties, NativeActionSheetOptions& options)
{
    // Parse width
    if (options.width.hasValue) {
        auto width = CalcDimension(options.width.value.value, static_cast<DimensionUnit>(options.width.value.unitType));
        properties.width = width;
    }
    // Parse height
    if (options.height.hasValue) {
        auto height =
            CalcDimension(options.height.value.value, static_cast<DimensionUnit>(options.height.value.unitType));
        properties.height = height;
    }
}

void ParseBackgroundProp(DialogProperties& properties, NativeActionSheetOptions& options)
{
    // Parse backgroundColor
    if (options.backgroundColor.hasValue) {
        Color bgColor = Color(ColorAlphaAdapt(options.backgroundColor.value));
        properties.backgroundColor = bgColor;
    }
    // Parse backgroundBlurStyle
    if (options.backgroundBlurStyle.hasValue) {
        auto blurStyle = options.backgroundBlurStyle.value;
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            properties.backgroundBlurStyle = blurStyle;
        }
    }
}

void ParseActionSheetOptions(DialogProperties& properties, NativeActionSheetOptions& options)
{
    ParseTitleAndMessage(properties, options);
    ParseConfirmButton(properties, options.confirm);
    ParseDialogAlignment(properties, options.alignment);
    ParseOffset(properties, options.offset);
    ParseMaskRect(properties, options.maskRect);
    ParseBorderProps(properties, options);
    ParseSheets(properties, options.sheets);
    ParseWidthAndHeight(properties, options);
    ParseBackgroundProp(properties, options);
    // Parse autlCancel
    if (options.autoCancel.hasValue) {
        properties.autoCancel = options.autoCancel.value;
    }
    // Parse cancel
    if (options.cancel.hasValue) {
        auto cancel = [lambda = CJLambda::Create(options.cancel.value)]() { lambda(); };
        ActionSheetModel::GetInstance()->SetCancel(cancel, properties);
    }
    if (options.showInSubWindow.hasValue) {
        properties.isShowInSubWindow = options.showInSubWindow.value;
    }
    // Parse isModalValue
    if (options.isModal.hasValue) {
        properties.isModal = options.isModal.value;
    }
    // Parse onWillDismiss
    if (options.onWillDismiss.hasValue) {
        std::function<void(const int32_t& info, const int32_t& infoTem)> onWillDismissFunc =
            [nativeFunc = CJLambda::Create(options.onWillDismiss.value)](
                const int32_t& info, const int32_t& infoTem) { nativeFunc(info); };
        ActionSheetModel::GetInstance()->SetOnWillDismiss(std::move(onWillDismissFunc), properties);
    }
    // Parse transition
    if (options.transition.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(options.transition.value);
        if (nativeTransitionEffect) {
            properties.transitionEffect = nativeTransitionEffect->effect;
        }
    }
    ActionSheetModel::GetInstance()->ShowActionSheet(properties);
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkActionSheetShowWithShadowOptions(
    NativeActionSheetOptions options, NativeShadowOptions shadowOptions)
{
    DialogProperties properties {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = ACTION_SHEET_OFFSET_DEFAULT
    };

    // Parse shadow
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
    // Parse ActionSheetOptions
    ParseActionSheetOptions(properties, options);
}
void FfiOHOSAceFrameworkActionSheetShowWithShadowStyle(NativeActionSheetOptions options, int32_t shadowSytle)
{
    DialogProperties properties {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = ACTION_SHEET_OFFSET_DEFAULT
    };
    // Parse shadow
    Shadow shadow;
    auto style = static_cast<ShadowStyle>(shadowSytle);
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
    // Parse ActionSheetOptions
    ParseActionSheetOptions(properties, options);
}
void FfiOHOSAceFrameworkActionSheetShow(NativeActionSheetOptions options)
{
    DialogProperties properties {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = ACTION_SHEET_OFFSET_DEFAULT
    };
    ParseActionSheetOptions(properties, options);
}
void FfiOHOSAceFrameworkActionSheetDismiss()
{
    ViewAbstractModel::GetInstance()->DismissDialog();
}
}