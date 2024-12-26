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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_textfield_ffi.h"

#include "cj_lambda.h"

#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextInputAction> TEXT_INPUT_ACTIONS = {
    TextInputAction::UNSPECIFIED, TextInputAction::NONE, TextInputAction::GO,  TextInputAction::SEARCH,
    TextInputAction::SEND, TextInputAction::NEXT, TextInputAction::DONE, TextInputAction::PREVIOUS,
    TextInputAction::NEW_LINE
};
const std::vector<TextInputType> TEXT_INPUT_TYPES = { TextInputType::TEXT, TextInputType::NUMBER,
    TextInputType::EMAIL_ADDRESS, TextInputType::VISIBLE_PASSWORD };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };

const std::function<void(std::u16string)> FormatCharFunction(void (*callback)(const char* value))
{
    const std::function<void(std::u16string)> result = [lambda = CJLambda::Create(callback)]
        (const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16ToStr8(value);
        lambda(valueStr.c_str());
    };
    return result;
}

} // namespace

extern "C" {
void FfiOHOSAceFrameworkTextFieldSetHeight(double height, uint32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
}

void FfiOHOSAceFrameworkTextFieldSetSize(double width, uint32_t widthUnit, double height, uint32_t heightUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetSize(width, widthUnit, height, heightUnit);
}

void FfiOHOSAceFrameworkTextFieldSetBorder(CJBorder params)
{
    if (!Utils::CheckParamsValid(params.style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }

    FfiOHOSAceFrameworkViewAbstractSetBorder(params);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderWidth(double value, uint32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidth(value, unit);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderColor(uint32_t color)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderColor(color);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderWidthWithCJEdge(CJEdge params)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidthWithCJEdge(params);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }

    FfiOHOSAceFrameworkViewAbstractSetBorderStyle(style);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderRadius(double value, uint32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderRadius(value, unit);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetAllBorderRadius(CJBorderRadius value)
{
    FfiOHOSAceFrameworkViewAbstractSetAllBorderRadius(value);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBackgroundColor(uint32_t value)
{
    TextFieldModel::GetInstance()->SetBackgroundColor(Color(value), false);
}

void FfiOHOSAceFrameworkTextFieldSetPadding(double value, int32_t unit)
{
    struct CJEdge textEdge;
    textEdge.top = value;
    textEdge.topUnit = unit;
    textEdge.right = value;
    textEdge.rightUnit = unit;
    textEdge.bottom = value;
    textEdge.bottomUnit = unit;
    textEdge.left = value;
    textEdge.leftUnit = unit;
    FfiOHOSAceFrameworkTextFieldSetPaddings(textEdge);
}

void FfiOHOSAceFrameworkTextFieldSetPaddings(CJEdge params)
{
    NG::PaddingProperty paddings;
    paddings.top = NG::CalcLength(Dimension(params.top, static_cast<DimensionUnit>(params.topUnit)));
    paddings.right = NG::CalcLength(Dimension(params.right, static_cast<DimensionUnit>(params.rightUnit)));
    paddings.bottom = NG::CalcLength(Dimension(params.bottom, static_cast<DimensionUnit>(params.bottomUnit)));
    paddings.left = NG::CalcLength(Dimension(params.left, static_cast<DimensionUnit>(params.leftUnit)));
    TextFieldModel::GetInstance()->SetPadding(paddings, Edge(), false);
}

void FfiOHOSAceFrameworkTextFieldSetMargin(double value, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetMargin(value, unit);
    TextFieldModel::GetInstance()->SetMargin();
}

void FfiOHOSAceFrameworkTextFieldSetMargins(CJEdge params)
{
    FfiOHOSAceFrameworkViewAbstractSetMargins(params);
    TextFieldModel::GetInstance()->SetMargin();
}

void FfiOHOSAceFrameworkTextFieldSetPlaceholderColor(uint32_t value)
{
    TextFieldModel::GetInstance()->SetPlaceholderColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetPlaceholderFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    if (!Utils::CheckParamsValid(style, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    Dimension sizeDime(size, static_cast<DimensionUnit>(unit));
    if (sizeDime.IsNegative()) {
        sizeDime.SetValue(0.0);
    }

    OHOS::Ace::Font font;

    font.fontWeight = ConvertStrToFontWeight(weight);
    font.fontSize = sizeDime;
    font.fontStyle = FONT_STYLES[style];
    font.fontFamilies = ConvertStrToFontFamilies(family);

    TextFieldModel::GetInstance()->SetPlaceholderFont(font);
}

void FfiOHOSAceFrameworkTextFieldSetEnterKeyType(int32_t type)
{
    if (!Utils::CheckParamsValid(type, TEXT_INPUT_ACTIONS.size())) {
        LOGE("invalid value for text input action");
        return;
    }

    TextFieldModel::GetInstance()->SetEnterKeyType(TEXT_INPUT_ACTIONS[type]);
}

void FfiOHOSAceFrameworkTextFieldSetType(int32_t value)
{
    if (!Utils::CheckParamsValid(value, TEXT_INPUT_TYPES.size())) {
        LOGE("invalid value for text input type");
        return;
    }

    TextFieldModel::GetInstance()->SetType(TEXT_INPUT_TYPES[value]);
}

void FfiOHOSAceFrameworkTextFieldSetTextAlign(int32_t value)
{
    if (!Utils::CheckParamsValid(value, TEXT_ALIGNS.size())) {
        LOGE("invalid value for textAlign");
        return;
    }

    TextFieldModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
}

void FfiOHOSAceFrameworkTextFieldSetCaretColor(uint32_t value)
{
    TextFieldModel::GetInstance()->SetCaretColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetMaxLength(uint32_t value)
{
    TextFieldModel::GetInstance()->SetMaxLength(value);
}

void FfiOHOSAceFrameworkTextFieldSetFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldSetFontColor(uint32_t value)
{
    TextFieldModel::GetInstance()->SetTextColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetFontWeight(const char* value)
{
    TextFieldModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void FfiOHOSAceFrameworkTextFieldSetFontStyle(int32_t value)
{
    if (!Utils::CheckParamsValid(value, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }

    TextFieldModel::GetInstance()->SetFontStyle(FONT_STYLES[value]);
}

void FfiOHOSAceFrameworkTextFieldSetFontFamily(const char* value)
{
    TextFieldModel::GetInstance()->SetFontFamily(ConvertStrToFontFamilies(value));
}

void FfiOHOSAceFrameworkTextFieldSetInputFilter(const char* value, void (*callback)(const char* value))
{
    TextFieldModel::GetInstance()->SetInputFilter(value, FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldOnSubmit(void (*callback)(int32_t value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto task = [func = CJLambda::Create(callback), node = targetNode](int32_t key,
                       NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        func(key);
    };
    TextFieldModel::GetInstance()->SetOnSubmit(task);
}

void FfiOHOSAceFrameworkTextFieldOnChange(void (*callback)(const char* value))
{
    auto onChange = [func = FormatCharFunction(callback)](
        const std::u16string& val, PreviewText& previewText) {
        func(val);
    };
    TextFieldModel::GetInstance()->SetOnChange(onChange);
}

void FfiOHOSAceFrameworkTextFieldOnCopy(void (*callback)(const char* value))
{
    TextFieldModel::GetInstance()->SetOnCopy(FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldOnCut(void (*callback)(const char* value))
{
    TextFieldModel::GetInstance()->SetOnCut(FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldOnPaste(void (*callback)(const char* value))
{
    auto onPaste = [func = FormatCharFunction(callback)](
        const std::u16string& val, NG::TextCommonEvent& info) {
        func(val);
    };
    TextFieldModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
}

void FfiOHOSAceFrameworkTextFieldOnEditChanged(void (*callback)(bool value))
{
    TextFieldModel::GetInstance()->SetOnEditChanged(CJLambda::Create(callback));
}
}
