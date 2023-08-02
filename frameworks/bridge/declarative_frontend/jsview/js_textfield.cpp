/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"

#include <algorithm>
#include <cstdint>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_textarea.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_field_model_impl.h"
#include "core/common/container.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/pipeline/pipeline_base.h"
#include "base/log/ace_scoring_log.h"

namespace OHOS::Ace {

std::unique_ptr<TextFieldModel> TextFieldModel::instance_ = nullptr;
std::mutex TextFieldModel::mutex_;

TextFieldModel* TextFieldModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TextFieldModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TextFieldModelNG());
            } else {
                instance_.reset(new Framework::TextFieldModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
const uint32_t MAX_LINES = 3;
} // namespace

void ParseTextFieldTextObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    JsEventCallback<void(const std::string&)> onChangeEvent(
        info.GetExecutionContext(), JSRef<JSFunc>::Cast(changeEventVal));
    TextFieldModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSTextField::CreateTextInput(const JSCallbackInfo& info)
{
    std::optional<std::string> placeholderSrc;
    std::optional<std::string> value;
    JSTextInputController* jsController = nullptr;
    JSRef<JSVal> changeEventVal = JSRef<JSVal>::Make();
    if (info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        std::string placeholder;
        if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
            placeholderSrc = placeholder;
        }
        std::string text;
        JSRef<JSVal> textValue = paramObject->GetProperty("text");
        if (textValue->IsObject()) {
            JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(textValue);
            changeEventVal = valueObj->GetProperty("changeEvent");
            if (changeEventVal->IsFunction()) {
                textValue = valueObj->GetProperty("value");
            }
            if (ParseJsString(textValue, text)) {
                value = text;
            }
        } else {
            if (ParseJsString(textValue, text)) {
                value = text;
            }
        }
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextInputController>();
        }
    }

    auto controller = TextFieldModel::GetInstance()->CreateTextInput(placeholderSrc, value);
    if (jsController) {
        jsController->SetController(controller);
    }
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseTextFieldTextObject(info, changeEventVal);
    }

    TextFieldModel::GetInstance()->SetFocusableAndFocusNode();
}

void JSTextField::CreateTextArea(const JSCallbackInfo& info)
{
    std::optional<std::string> placeholderSrc;
    std::optional<std::string> value;
    JSTextAreaController* jsController = nullptr;
    JSRef<JSVal> changeEventVal = JSRef<JSVal>::Make();
    if (info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        std::string placeholder;
        if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
            placeholderSrc = placeholder;
        }
        std::string text;
        JSRef<JSVal> textValue = paramObject->GetProperty("text");
        if (textValue->IsObject()) {
            JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(textValue);
            changeEventVal = valueObj->GetProperty("changeEvent");
            if (changeEventVal->IsFunction()) {
                textValue = valueObj->GetProperty("value");
            }
            if (ParseJsString(textValue, text)) {
                value = text;
            }
        } else {
            if (ParseJsString(textValue, text)) {
                value = text;
            }
        }
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextAreaController>();
        }
    }
    auto controller = TextFieldModel::GetInstance()->CreateTextArea(placeholderSrc, value);
    if (jsController) {
        jsController->SetController(controller);
    }
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseTextFieldTextObject(info, changeEventVal);
    }

    TextFieldModel::GetInstance()->SetFocusableAndFocusNode();
}

void JSTextField::SetType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("SetType create error, info is non-valid");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGI("The inputType is not number");
        return;
    }
    TextInputType textInputType = static_cast<TextInputType>(info[0]->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetType(textInputType);
}

void JSTextField::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg(SetPlaceholderColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    auto theme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    Color color = theme->GetPlaceholderColor();
    CheckColor(info[0], color, V2::TEXTINPUT_ETS_TAG, "PlaceholderColor");
    TextFieldModel::GetInstance()->SetPlaceholderColor(color);
}

void JSTextField::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("PlaceholderFont create error, info is non-valid");
        return;
    }
    Font font;
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto fontSize = paramObject->GetProperty("size");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (fontSize->IsString()) {
            auto result = StringUtils::StringToDimensionWithThemeValue(fontSize->ToString(), true, Dimension(-1));
            font.fontSize = result;
        } else if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            font.fontSize = Dimension(-1);
            LOGW("Parse to dimension FP failed.");
        } else {
            font.fontSize = size;
        }
    }

    std::string weight;
    auto fontWeight = paramObject->GetProperty("weight");
    if (!fontWeight->IsNull()) {
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        font.fontWeight = ConvertStrToFontWeight(weight);
    }

    auto fontFamily = paramObject->GetProperty("family");
    if (!fontFamily->IsNull()) {
        std::vector<std::string> fontFamilies;
        if (ParseJsFontFamilies(fontFamily, fontFamilies)) {
            font.fontFamilies = fontFamilies;
        }
    }

    auto style = paramObject->GetProperty("style");
    if (!style->IsNull()) {
        font.fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
    }
    TextFieldModel::GetInstance()->SetPlaceholderFont(font);
}

void JSTextField::SetEnterKeyType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGI("Info(SetEnterKeyType) is not number");
        return;
    }
    TextInputAction textInputAction = static_cast<TextInputAction>(info[0]->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetEnterKeyType(textInputAction);
}

void JSTextField::SetTextAlign(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        TextFieldModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
    } else {
        LOGI("the value is error");
    }
}

void JSTextField::SetInputStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg(SetInputStyle) is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto styleString = info[0]->ToString();
    if (styleString == "Inline") {
        TextFieldModel::GetInstance()->SetInputStyle(InputStyle::INLINE);
    } else {
        TextFieldModel::GetInstance()->SetInputStyle(InputStyle::DEFAULT);
    }
}

void JSTextField::SetCaretColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg(SetCareColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGI("info[0] is null");
        return;
    }

    TextFieldModel::GetInstance()->SetCaretColor(color);
}

void JSTextField::SetCaretStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("CaretStyle create error, info is non-valid");
        return;
    }
    CaretStyle caretStyle;
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto caretWidth = paramObject->GetProperty("width");

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    if (caretWidth->IsNull() || caretWidth->IsUndefined()) {
        caretStyle.caretWidth = theme->GetCursorWidth();
    } else {
        CalcDimension width;
        if (!ParseJsDimensionVpNG(caretWidth, width, false)) {
            width = theme->GetCursorWidth();
        }
        if (LessNotEqual(width.Value(), 0.0)) {
            width = theme->GetCursorWidth();
        }
        caretStyle.caretWidth = width;
    }
    TextFieldModel::GetInstance()->SetCaretStyle(caretStyle);
}

void JSTextField::SetCaretPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg(SetCaretPosition) is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    int32_t caretPosition = 0;
    if (!ParseJsInt32(info[0], caretPosition)) {
        return;
    }
    if (caretPosition < 0) {
        return;
    }
    TextFieldModel::GetInstance()->SetCaretPosition(caretPosition);
}

void JSTextField::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg(SetSelectedBackgroundColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID_NOLOG(theme);
        selectedColor = theme->GetSelectedColor();
    }
    TextFieldModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
}

void JSTextField::SetMaxLength(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The arg(SetMaxLength) is wrong, it is supposed to have atleast 1 argument");
        return;
    }
    int32_t maxLength = 0;
    if (info[0]->IsUndefined()) {
        TextFieldModel::GetInstance()->ResetMaxLength();
        return;
    } else if (!info[0]->IsNumber()) {
        LOGI("Max length should be number");
        TextFieldModel::GetInstance()->ResetMaxLength();
        return;
    }
    maxLength = info[0]->ToNumber<int32_t>();
    if (GreatOrEqual(maxLength, 0)) {
        TextFieldModel::GetInstance()->SetMaxLength(maxLength);
    } else {
        TextFieldModel::GetInstance()->ResetMaxLength();
    }
}

void JSTextField::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("JSTextField::SetFontSize The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionNG(info[0], fontSize, DimensionUnit::FP, false)) {
        LOGI("Parse to dimension FP failed!");
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        fontSize = theme->GetFontSize();
    }
    TextFieldModel::GetInstance()->SetFontSize(fontSize);
}

void JSTextField::SetFontWeight(const std::string& value)
{
    TextFieldModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSTextField::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        LOGI("Parse to dimension FP failed!");
        return;
    }
    TextFieldModel::GetInstance()->SetTextColor(textColor);
}

void JSTextField::SetForegroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        TextFieldModel::GetInstance()->SetForegroundColor(Color::FOREGROUND);
        return;
    }
    Color foregroundColor;
    if (!ParseJsColor(info[0], foregroundColor)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
    TextFieldModel::GetInstance()->SetForegroundColor(foregroundColor);
}

void JSTextField::SetFontStyle(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        TextFieldModel::GetInstance()->SetFontStyle(FONT_STYLES[value]);
    } else {
        LOGI("TextInput fontStyle(%{public}d) illegal value", value);
    }
}

void JSTextField::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGI("Parse FontFamilies failed");
        return;
    }
    TextFieldModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSTextField::SetInputFilter(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::string inputFilter;
    if (!ParseJsString(info[0], inputFilter)) {
        LOGI("Parse inputFilter failed");
        return;
    }
    if (info.Length() > 1 && info[1]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(info[1]));
        auto resultId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        TextFieldModel::GetInstance()->SetInputFilter(inputFilter, resultId);
        return;
    }
    TextFieldModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
}

void JSTextField::SetShowPasswordIcon(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGI("The info is wrong, it is supposed to be an boolean");
        return;
    }

    bool isShowPasswordIcon = info[0]->ToBoolean();
    TextFieldModel::GetInstance()->SetShowPasswordIcon(isShowPasswordIcon);
}

void JSTextField::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    bool tmp = !ParseJsColor(info[0], backgroundColor);
    TextFieldModel::GetInstance()->SetBackgroundColor(backgroundColor, tmp);
}

void JSTextField::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    if (info.Length() < 1) {
        LOGI("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGI("Parse to dimension VP failed!");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGI("dimension value: %{public}f is invalid!", value.Value());
        return;
    }
    TextFieldModel::GetInstance()->SetHeight(value);
}

void JSTextField::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsString() && info[0]->ToString() == "auto") {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        TextFieldModel::GetInstance()->SetWidthAuto(true);
        return;
    }

    TextFieldModel::GetInstance()->SetWidthAuto(false);
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGW("Parse width fail");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetWidth(value);
}

bool CheckIsIllegalString(const std::string& value)
{
    if (value.empty()) {
        return true;
    }
    errno = 0;
    char* pEnd = nullptr;
    std::strtod(value.c_str(), &pEnd);
    return (pEnd == value.c_str() || errno == ERANGE);
}

void JSTextField::JsPadding(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || (info[0]->IsString() && CheckIsIllegalString(info[0]->ToString()))) {
        return;
    };
    CalcDimension length;
    ParseJsDimensionVp(info[0], length);
    if (length.IsNegative()) {
        return;
    }
    bool tmp = !info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject();

    NG::PaddingProperty newPadding = GetNewPadding(info);
    Edge oldPadding = Edge(GetOldPadding(info));
    TextFieldModel::GetInstance()->SetPadding(newPadding, oldPadding, tmp);
}

Edge JSTextField::GetOldPadding(const JSCallbackInfo& info)
{
    Edge padding;
    if (info[0]->IsNumber() || info[0]->IsString()) {
        CalcDimension edgeValue;
        if (ParseJsDimensionVp(info[0], edgeValue)) {
            padding = Edge(edgeValue);
        }
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        CalcDimension left = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension top = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension right = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension bottom = CalcDimension(0.0, DimensionUnit::VP);
        ParseJsDimensionVp(object->GetProperty("left"), left);
        ParseJsDimensionVp(object->GetProperty("top"), top);
        ParseJsDimensionVp(object->GetProperty("right"), right);
        ParseJsDimensionVp(object->GetProperty("bottom"), bottom);
        padding = Edge(left, top, right, bottom);
    }
    return padding;
}

NG::PaddingProperty JSTextField::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding;
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            padding = SetPaddings(top, bottom, left, right);
            return padding;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        // use default value.
        length.Reset();
    }
    padding.SetEdges(NG::CalcLength(length.IsNonNegative() ? length : CalcDimension()));
    return padding;
}

NG::PaddingProperty JSTextField::SetPaddings(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}

void JSTextField::JsBorder(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGI("args is not a object. %s", info[0]->ToString().c_str());
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueWidth = object->GetProperty("width");
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth);
    }
    auto valueColor = object->GetProperty("color");
    if (!valueColor->IsUndefined()) {
        ParseBorderColor(valueColor);
    }
    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    auto valueStyle = object->GetProperty("style");
    if (!valueStyle->IsUndefined()) {
        ParseBorderStyle(valueStyle);
    }
    JSViewAbstract::JsBorder(info);
    TextFieldModel::GetInstance()->SetBackBorder();
    info.ReturnSelf();
}

void JSTextField::JsBorderWidth(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGI("args need a string or number or object");
        return;
    }
    JSViewAbstract::JsBorderWidth(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsBorderColor(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGI("args need a string or number or object");
        return;
    }
    JSViewAbstract::JsBorderColor(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsBorderStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        LOGI("args need a string or number or object");
        return;
    }
    JSViewAbstract::JsBorderStyle(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsBorderRadius(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGI("args need a string or number or object");
        return;
    }
    JSViewAbstract::JsBorderRadius(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsHoverEffect(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        LOGI("info[0] is not a number");
        return;
    }
    TextFieldModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(info[0]->ToNumber<int32_t>()));
}

void JSTextField::SetOnEditChanged(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(bool)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnEditChanged(std::move(callback));
}

void JSTextField::SetOnSubmit(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnSubmit(std::move(callback));
}

void JSTextField::SetOnChange(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnChange(std::move(callback));
}

void JSTextField::SetOnTextSelectionChange(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(int32_t, int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnTextSelectionChange(std::move(callback));
}

void JSTextField::SetOnContentScroll(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(float, float)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnContentScroll(std::move(callback));
}

void JSTextField::SetOnCopy(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSTextField::SetOnCut(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnCut(std::move(callback));
}

void JSTextField::SetOnPaste(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnPaste(std::move(callback));
}

void JSTextField::SetOnClick(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSInteractableView::JsOnClick(info);
        return;
    }
    JsEventCallback<void(const ClickInfo&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    TextFieldModel::GetInstance()->SetOnClick(std::move(callback));
    info.ReturnSelf();
}

void JSTextField::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    TextFieldModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSTextField::JsMenuOptionsExtension(const JSCallbackInfo& info)
{
    if (info[0]->IsArray()) {
        std::vector<NG::MenuOptionsParam> menuOptionsItems;
        JSViewAbstract::ParseMenuOptions(info, JSRef<JSArray>::Cast(info[0]), menuOptionsItems);
        TextFieldModel::GetInstance()->SetMenuOptionItems(std::move(menuOptionsItems));
    }
}

void JSTextField::SetShowUnderline(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGI("The info is wrong, it is supposed to be an boolean");
        TextFieldModel::GetInstance()->SetShowUnderline(false);
        return;
    }
    TextFieldModel::GetInstance()->SetShowUnderline(info[0]->ToBoolean());
}

void JSTextField::SetPasswordIcon(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> showVal = jsObj->GetProperty("onIconSrc");
    JSRef<JSVal> hideVal = jsObj->GetProperty("offIconSrc");
    PasswordIcon passwordIcon;
    if (showVal->IsString()) {
        passwordIcon.showResult = showVal->ToString();
    }
    if (hideVal->IsString()) {
        passwordIcon.hideResult = hideVal->ToString();
    }
    if (showVal->IsObject()) {
        JSRef<JSVal> bundleName = JSRef<JSObject>::Cast(showVal)->GetProperty("bundleName");
        JSRef<JSVal> moduleName = JSRef<JSObject>::Cast(showVal)->GetProperty("moduleName");
        if (bundleName->IsString()) {
            passwordIcon.showBundleName = bundleName->ToString();
        }
        if (moduleName->IsString()) {
            passwordIcon.showModuleName = moduleName->ToString();
        }
        ParseJsMedia(JSRef<JSObject>::Cast(showVal), passwordIcon.showResult);
    }
    if (hideVal->IsObject()) {
        JSRef<JSVal> bundleName = JSRef<JSObject>::Cast(hideVal)->GetProperty("bundleName");
        JSRef<JSVal> moduleName = JSRef<JSObject>::Cast(hideVal)->GetProperty("moduleName");
        if (bundleName->IsString()) {
            passwordIcon.hideBundleName = bundleName->ToString();
        }
        if (moduleName->IsString()) {
            passwordIcon.hideModuleName = moduleName->ToString();
        }
        ParseJsMedia(JSRef<JSObject>::Cast(hideVal), passwordIcon.hideResult);
    }
    if (!showVal->IsString() && !showVal->IsObject()) {
        passwordIcon.showResult = "";
    }
    if (!hideVal->IsString() && !hideVal->IsObject()) {
        passwordIcon.hideResult = "";
    }
    TextFieldModel::GetInstance()->SetPasswordIcon(passwordIcon);
}

void JSTextField::UpdateDecoration(const RefPtr<BoxComponent>& boxComponent,
    const RefPtr<TextFieldComponent>& component, const Border& boxBorder,
    const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme)
{
    if (!textFieldTheme) {
        LOGI("UpdateDecoration: textFieldTheme is null.");
        return;
    }

    RefPtr<Decoration> decoration = component->GetDecoration();
    RefPtr<Decoration> boxDecoration = boxComponent->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
    }
    if (boxDecoration) {
        Border border = decoration->GetBorder();
        border.SetLeftEdge(boxBorder.Left());
        border.SetRightEdge(boxBorder.Right());
        border.SetTopEdge(boxBorder.Top());
        border.SetBottomEdge(boxBorder.Bottom());
        border.SetBorderRadius(textFieldTheme->GetBorderRadius());
        decoration->SetBorder(border);
        component->SetOriginBorder(decoration->GetBorder());

        if (boxDecoration->GetImage() || boxDecoration->GetGradient().IsValid()) {
            // clear box properties except background image and radius.
            boxDecoration->SetBackgroundColor(Color::TRANSPARENT);
            Border border;
            border.SetBorderRadius(textFieldTheme->GetBorderRadius());
            boxDecoration->SetBorder(border);
        }
    } else {
        boxDecoration = AceType::MakeRefPtr<Decoration>();
        boxDecoration->SetBorderRadius(textFieldTheme->GetBorderRadius());
        boxComponent->SetBackDecoration(boxDecoration);
    }
}

void JSTextField::SetShowUnit(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGI("fail to bind SetShowUnit event due to info is not object");
        return;
    }

    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto unitFunc = [builderFunc]() { builderFunc->Execute(); };
    TextFieldModel::GetInstance()->SetShowUnit(std::move(unitFunc));
}

void JSTextField::SetShowError(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (!info[0]->IsUndefined() && !info[0]->IsString()) {
            LOGI("args need a string or undefined");
            TextFieldModel::GetInstance()->SetShowError("", false);
            return;
        }
        TextFieldModel::GetInstance()->SetShowError(
            info[0]->IsString() ? info[0]->ToString() : "", info[0]->IsUndefined() ? false : true);
    }
}

void JSTextField::SetShowCounter(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGI("The info is wrong, it is supposed to be an boolean");
        TextFieldModel::GetInstance()->SetShowCounter(false);
        return;
    }

    TextFieldModel::GetInstance()->SetShowCounter(info[0]->ToBoolean());
}

void JSTextField::SetBarState(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        LOGI("SetBarState create error, info is not number or non-valid");
        TextFieldModel::GetInstance()->SetBarState(DisplayMode::AUTO);
        return;
    }
    DisplayMode displayMode = static_cast<DisplayMode>(info[0]->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetBarState(displayMode);
}

void JSTextField::SetMaxLines(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        LOGI("SetMaxLines create error, info is not number or non-valid");
        TextFieldModel::GetInstance()->SetMaxViewLines(MAX_LINES);
        return;
    }
    if (info[0]->ToNumber<int32_t>() <= 0) {
        TextFieldModel::GetInstance()->SetMaxViewLines(MAX_LINES);
        return;
    }
    TextFieldModel::GetInstance()->SetMaxViewLines(info[0]->ToNumber<uint32_t>());
}

void JSTextField::SetEnableKeyboardOnFocus(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("EnableKeyboardOnFocus should have at least 1 param");
        return;
    }
    if (info[0]->IsUndefined() || !info[0]->IsBoolean()) {
        LOGI("The info of SetEnableKeyboardOnFocus is not correct, using default");
        TextFieldModel::GetInstance()->RequestKeyboardOnFocus(true);
        return;
    }
    TextFieldModel::GetInstance()->RequestKeyboardOnFocus(info[0]->ToBoolean());
}

void JSTextField::SetSelectionMenuHidden(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("SelectionMenuHidden should have at least 1 param");
        return;
    }
    if (info[0]->IsUndefined() || !info[0]->IsBoolean()) {
        LOGI("The info of SetSelectionMenuHidden is not correct, using default");
        TextFieldModel::GetInstance()->SetSelectionMenuHidden(false);
        return;
    }
    TextFieldModel::GetInstance()->SetSelectionMenuHidden(info[0]->ToBoolean());
}

bool JSTextField::ParseJsCustomKeyboardBuilder(const JSCallbackInfo& info,
    int32_t index, std::function<void()>& buildFunc)
{
    if (info.Length() <= index) {
        return false;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[index]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return false;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_RETURN(builderFunc, false);
    buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CustomKeyboard");
        func->Execute();
    };
    return true;
}

void JSTextField::SetCustomKeyboard(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && (info[0]->IsUndefined() || info[0]->IsNull())) {
        TextFieldModel::GetInstance()->SetCustomKeyboard(nullptr);
        return;
    }
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    std::function<void()>buildFunc;
    if (ParseJsCustomKeyboardBuilder(info, 0, buildFunc)) {
        TextFieldModel::GetInstance()->SetCustomKeyboard(std::move(buildFunc));
    }
}
} // namespace OHOS::Ace::Framework
