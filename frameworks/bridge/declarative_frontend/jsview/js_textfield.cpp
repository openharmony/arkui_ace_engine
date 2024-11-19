/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include <string>
#include <vector>
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "bridge/declarative_frontend/jsview/js_textarea.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_field_model_impl.h"
#include "core/common/container.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/image/image_source_info.h"
#include "core/text/text_emoji_processor.h"

namespace OHOS::Ace {

std::unique_ptr<TextFieldModel> TextFieldModel::instance_ = nullptr;
std::mutex TextFieldModel::mutex_;

TextFieldModel* TextFieldModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::TextFieldModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::TextFieldModelNG instance;
        return &instance;
    } else {
        static Framework::TextFieldModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY };
const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES = { LineBreakStrategy::GREEDY,
    LineBreakStrategy::HIGH_QUALITY, LineBreakStrategy::BALANCED };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
const std::vector<WordBreak> WORD_BREAK_TYPES = { WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE, TextOverflow::DEFAULT };
constexpr uint32_t MAX_LINES = 3;
constexpr uint32_t MINI_VAILD_VALUE = 1;
constexpr uint32_t MAX_VAILD_VALUE = 100;
constexpr uint32_t ILLEGAL_VALUE = 0;
constexpr uint32_t DEFAULT_MODE = -1;
constexpr uint32_t DEFAULT_OVERFLOW = 4;
const char* TOP_START_PROPERTY = "topStart";
const char* TOP_END_PROPERTY = "topEnd";
const char* BOTTOM_START_PROPERTY = "bottomStart";
const char* BOTTOM_END_PROPERTY = "bottomEnd";
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
constexpr TextDecorationStyle DEFAULT_TEXT_DECORATION_STYLE = TextDecorationStyle::SOLID;

bool ParseJsLengthMetrics(const JSRef<JSObject>& obj, CalcDimension& result)
{
    auto value = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    return true;
}

void ProcessStringUnpairedSurrogates(std::optional<std::string>& value)
{
    if (!value.has_value()) {
        return;
    }
    std::u16string temp = StringUtils::Str8ToStr16(value.value());
    std::string result(value.value().c_str());
    if (temp.length() == 0 && result.length() != 0) {
        result = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(result);
    }
    value = result;
}
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
    JSTextEditableController* jsController = nullptr;
    JSRef<JSVal> changeEventVal = JSRef<JSVal>::Make();
    auto jsValue = info[0];
    if (jsValue->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(jsValue);
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
            value = "";
            if (ParseJsString(textValue, text)) {
                value = text;
            }
        } else if (paramObject->HasProperty("text")) {
            if (ParseJsString(textValue, text)) {
                value = text;
            }
            if (textValue->IsUndefined()) {
                value = "";
            }
        }
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextEditableController>();
        }
    }

    ProcessStringUnpairedSurrogates(placeholderSrc);
    ProcessStringUnpairedSurrogates(value);
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
    JSTextEditableController* jsController = nullptr;
    JSRef<JSVal> changeEventVal = JSRef<JSVal>::Make();
    auto jsValue = info[0];
    if (jsValue->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(jsValue);
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
        } else if (paramObject->HasProperty("text")) {
            if (ParseJsString(textValue, text)) {
                value = text;
            }
            if (textValue->IsUndefined()) {
                value = "";
            }
        }
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextEditableController>();
        }
    }

    ProcessStringUnpairedSurrogates(placeholderSrc);
    ProcessStringUnpairedSurrogates(value);
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
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->SetType(TextInputType::UNSPECIFIED);
        return;
    }
    if (!jsValue->IsNumber()) {
        return;
    }
    TextInputType textInputType = CastToTextInputType(jsValue->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetType(textInputType);
}

void JSTextField::SetContentType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->SetContentType(NG::TextContentType::UNSPECIFIED);
        return;
    }
    if (!jsValue->IsNumber()) {
        return;
    }
    NG::TextContentType textContentType = static_cast<NG::TextContentType>(jsValue->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetContentType(textContentType);
}

void JSTextField::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
        return;
    }
    Font font;
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto fontSize = paramObject->GetProperty("size");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        if (fontSize->IsString()) {
            auto result = StringUtils::StringToDimensionWithThemeValue(
                fontSize->ToString(), true, Dimension(theme->GetFontSize()));
            if (result.Unit() == DimensionUnit::PERCENT) {
                result = theme->GetFontSize();
            }
            font.fontSize = result;
        } else if (ParseJsDimensionFp(fontSize, size) && size.Unit() != DimensionUnit::PERCENT) {
            font.fontSize = size;
        } else {
            font.fontSize = Dimension(theme->GetFontSize());
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
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->SetEnterKeyType(TextInputAction::UNSPECIFIED);
        return;
    }
    if (!jsValue->IsNumber()) {
        return;
    }
    TextInputAction textInputAction = CastToTextInputAction(jsValue->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetEnterKeyType(textInputAction);
}

void JSTextField::SetTextAlign(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        TextFieldModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
    }
}

void JSTextField::SetLineBreakStrategy(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TextFieldModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    if (!info[0]->IsNumber()) {
        TextFieldModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    auto index = info[0]->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(LINE_BREAK_STRATEGY_TYPES.size())) {
        TextFieldModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    TextFieldModel::GetInstance()->SetLineBreakStrategy(LINE_BREAK_STRATEGY_TYPES[index]);
}

void JSTextField::SetInputStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }

    TextFieldModel::GetInstance()->SetCaretColor(color);
}

void JSTextField::SetCaretStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsObject()) {
        CaretStyle caretStyle;
        auto paramObject = JSRef<JSObject>::Cast(jsValue);
        auto caretWidth = paramObject->GetProperty("width");

        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
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

        // set caret color
        Color caretColor;
        if (!paramObject->HasProperty("color")) {
            return;
        } else {
            auto caretColorProp = paramObject->GetProperty("color");
            if (caretColorProp->IsUndefined() || caretColorProp->IsNull()
                || !ParseJsColor(caretColorProp, caretColor)) {
                caretColor = theme->GetCursorColor();
            }
            TextFieldModel::GetInstance()->SetCaretColor(caretColor);
        }
    }
}

void JSTextField::SetCaretPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t caretPosition = 0;
    auto tempInfo = info[0];
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (!ParseJsInt32(tempInfo, caretPosition) || caretPosition < 0) {
            caretPosition = 0;
        }
    } else {
        if (!ParseJsInt32(tempInfo, caretPosition)) {
            return;
        }
        if (caretPosition < 0) {
            return;
        }
    }
    TextFieldModel::GetInstance()->SetCaretPosition(caretPosition);
}

void JSTextField::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        selectedColor = theme->GetSelectedColor();
    }
    // Alpha = 255 means opaque
    if (selectedColor.GetAlpha() == 255) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(0.2);
    }
    TextFieldModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
}

void JSTextField::SetMaxLength(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    int32_t maxLength = 0;
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->ResetMaxLength();
        return;
    } else if (!jsValue->IsNumber()) {
        TextFieldModel::GetInstance()->ResetMaxLength();
        return;
    }
    maxLength = jsValue->ToNumber<int32_t>();
    if (std::isinf(jsValue->ToNumber<float>())) {
        maxLength = INT32_MAX; // Infinity
    }
    if (GreatOrEqual(maxLength, 0)) {
        TextFieldModel::GetInstance()->SetMaxLength(maxLength);
    } else {
        TextFieldModel::GetInstance()->ResetMaxLength();
    }
}

void JSTextField::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionNG(info[0], fontSize, DimensionUnit::FP, false)) {
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
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        textColor = theme->GetTextColor();
    }
    TextFieldModel::GetInstance()->SetTextColor(textColor);
}

void JSTextField::SetWordBreak(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (!jsValue->IsNumber()) {
        TextFieldModel::GetInstance()->SetWordBreak(WordBreak::BREAK_WORD);
        return;
    }
    auto index = jsValue->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(WORD_BREAK_TYPES.size())) {
        TextFieldModel::GetInstance()->SetWordBreak(WordBreak::BREAK_WORD);
        return;
    }
    TextFieldModel::GetInstance()->SetWordBreak(WORD_BREAK_TYPES[index]);
}

void JSTextField::SetForegroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(jsValue, strategy)) {
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        TextFieldModel::GetInstance()->SetForegroundColor(Color::FOREGROUND);
        return;
    }
    Color foregroundColor;
    if (!ParseJsColor(jsValue, foregroundColor)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
    TextFieldModel::GetInstance()->SetForegroundColor(foregroundColor);
}

void JSTextField::SetFontStyle(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        TextFieldModel::GetInstance()->SetFontStyle(FONT_STYLES[value]);
    }
}

void JSTextField::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        return;
    }
    TextFieldModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSTextField::SetInputFilter(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    std::string inputFilter;
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
        return;
    }
    if (!ParseJsString(jsValue, inputFilter)) {
        return;
    }
    if (!CheckRegexValid(inputFilter)) {
        inputFilter = "";
    }
    if (info.Length() > 1 && info[1]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(info[1]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto resultId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute(info);
        };
        TextFieldModel::GetInstance()->SetInputFilter(inputFilter, resultId);
        return;
    }
    TextFieldModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
}

void JSTextField::SetShowPasswordIcon(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->SetShowPasswordIcon(true);
        return;
    }

    bool isShowPasswordIcon = jsValue->ToBoolean();
    TextFieldModel::GetInstance()->SetShowPasswordIcon(isShowPasswordIcon);
}

void JSTextField::ShowPasswordText(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        TextFieldModel::GetInstance()->SetShowPasswordText(false);
        return;
    }

    bool showPassword = tmpInfo->ToBoolean();
    TextFieldModel::GetInstance()->SetShowPasswordText(showPassword);
}

void JSTextField::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        return;
    }
    TextFieldModel::GetInstance()->SetHeight(value);
}

void JSTextField::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsString() && jsValue->ToString().empty()) {
        return;
    }
    if (jsValue->IsString() && jsValue->ToString() == "auto") {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        TextFieldModel::GetInstance()->SetWidthAuto(true);
        return;
    }

    TextFieldModel::GetInstance()->SetWidthAuto(false);
    CalcDimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
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

void JSTextField::JsMargin(const JSCallbackInfo& info)
{
    JSViewAbstract::JsMargin(info);
    TextFieldModel::GetInstance()->SetMargin();
}

void JSTextField::JsPadding(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || (jsValue->IsString() && CheckIsIllegalString(jsValue->ToString()))) {
        return;
    };
    CalcDimension length;
    ParseJsDimensionVp(jsValue, length);
    if (length.IsNegative()) {
        TextFieldModel::GetInstance()->SetPadding(NG::PaddingProperty(), Edge(), true);
        return;
    }
    bool tmp = !jsValue->IsString() && !jsValue->IsNumber() && !jsValue->IsObject();

    NG::PaddingProperty newPadding = GetNewPadding(info);
    Edge oldPadding = Edge(GetOldPadding(info));
    TextFieldModel::GetInstance()->SetPadding(newPadding, oldPadding, tmp);
}

Edge JSTextField::GetOldPadding(const JSCallbackInfo& info)
{
    Edge padding;
    auto jsValue = info[0];
    if (jsValue->IsNumber() || jsValue->IsString()) {
        CalcDimension edgeValue;
        if (ParseJsDimensionVp(jsValue, edgeValue)) {
            padding = Edge(edgeValue);
        }
    }
    if (jsValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
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
    auto jsValue = info[0];
    if (jsValue->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(jsValue);
        CommonCalcDimension commonCalcDimension;
        ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
            return padding;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(jsValue, length)) {
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
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
        ViewAbstractModel::GetInstance()->SetDashGap(Dimension(-1));
        ViewAbstractModel::GetInstance()->SetDashWidth(Dimension(-1));
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);

    auto valueWidth = object->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH));
    if (!valueWidth->IsUndefined()) {
        JSViewAbstract::ParseBorderWidth(valueWidth);
    }

    // use default value when undefined.
    JSViewAbstract::ParseBorderColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR)));

    auto valueRadius = object->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS));
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    // use default value when undefined.
    JSViewAbstract::ParseBorderStyle(object->GetProperty(static_cast<int32_t>(ArkUIIndex::STYLE)));

    auto dashGap = object->GetProperty("dashGap");
    if (!dashGap->IsUndefined()) {
        JSViewAbstract::ParseDashGap(dashGap);
    }
    auto dashWidth = object->GetProperty("dashWidth");
    if (!dashWidth->IsUndefined()) {
        JSViewAbstract::ParseDashWidth(dashWidth);
    }

    TextFieldModel::GetInstance()->SetBackBorder();
    info.ReturnSelf();
}

void JSTextField::JsBorderWidth(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsObject() && !jsValue->IsString() && !jsValue->IsNumber()) {
        return;
    }
    JSViewAbstract::JsBorderWidth(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsBorderColor(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsObject() && !jsValue->IsString() && !jsValue->IsNumber()) {
        return;
    }
    JSViewAbstract::JsBorderColor(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsBorderStyle(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsObject() && !jsValue->IsNumber()) {
        return;
    }
    JSViewAbstract::JsBorderStyle(info);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::GetBorderRadiusByLengthMetrics(const char* key, JSRef<JSObject>& object,
    std::optional<CalcDimension>& radius)
{
    if (object->HasProperty(key) && object->GetProperty(key)->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(object->GetProperty(key));
        CalcDimension value;
        ParseJsLengthMetrics(startObj, value);
        radius = value;
    }
}

bool JSTextField::ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft,
    CalcDimension& topRight, CalcDimension& bottomLeft, CalcDimension& bottomRight)
{
    if (object->HasProperty(TOP_START_PROPERTY) || object->HasProperty(TOP_END_PROPERTY) ||
        object->HasProperty(BOTTOM_START_PROPERTY) || object->HasProperty(BOTTOM_END_PROPERTY)) {
        std::optional<CalcDimension> topStart;
        std::optional<CalcDimension> topEnd;
        std::optional<CalcDimension> bottomStart;
        std::optional<CalcDimension> bottomEnd;
        GetBorderRadiusByLengthMetrics(TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(BOTTOM_END_PROPERTY, object, bottomEnd);
        topLeft = topStart.has_value() ? topStart.value() : topLeft;
        topRight = topEnd.has_value() ? topEnd.value() : topRight;
        bottomLeft = bottomStart.has_value() ? bottomStart.value() : bottomLeft;
        bottomRight = bottomEnd.has_value() ? bottomEnd.value() : bottomRight;
        return true;
    }
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topLeft"), topLeft);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topRight"), topRight);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomLeft"), bottomLeft);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomRight"), bottomRight);
    return false;
}

void JSTextField::ParseBorderRadius(const JSRef<JSVal>& args)
{
    CalcDimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
    } else if (args->IsObject()) {
        auto textFieldTheme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto borderRadiusTheme = textFieldTheme->GetBorderRadius();
        NG::BorderRadiusProperty defaultBorderRadius {
            borderRadiusTheme.GetX(), borderRadiusTheme.GetY(),
            borderRadiusTheme.GetY(), borderRadiusTheme.GetX(),
        };

        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft = defaultBorderRadius.radiusTopLeft.value();
        CalcDimension topRight = defaultBorderRadius.radiusTopRight.value();
        CalcDimension bottomLeft = defaultBorderRadius.radiusBottomLeft.value();
        CalcDimension bottomRight = defaultBorderRadius.radiusBottomRight.value();
        if (ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(
                JSViewAbstract::GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
                return;
        }
        ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    }
}

void JSTextField::JsBorderRadius(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING,
        JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorderRadius", jsValue, checkList)) {
        auto textFieldTheme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto borderRadiusTheme = textFieldTheme->GetBorderRadius();
        NG::BorderRadiusProperty defaultBorderRadius {
            borderRadiusTheme.GetX(), borderRadiusTheme.GetY(),
            borderRadiusTheme.GetY(), borderRadiusTheme.GetX(),
        };
        ViewAbstractModel::GetInstance()->SetBorderRadius(defaultBorderRadius);
        return;
    }
    ParseBorderRadius(jsValue);
    TextFieldModel::GetInstance()->SetBackBorder();
}

void JSTextField::JsHoverEffect(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsNumber()) {
        return;
    }
    TextFieldModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(jsValue->ToNumber<int32_t>()));
}

void JSTextField::SetOnEditChanged(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(bool)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnEditChanged(std::move(callback));
}

Local<JSValueRef> JSTextField::JsKeepEditableState(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<NG::TextFieldCommonEvent*>(
        panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetKeepEditable(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

void JSTextField::CreateJsTextFieldCommonEvent(const JSCallbackInfo &info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto jsValue = info[0];
    auto jsTextFunc = AceType::MakeRefPtr<JsCommonEventFunction<NG::TextFieldCommonEvent, 2>>(
        JSRef<JSFunc>::Cast(jsValue));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](int32_t key,
                       NG::TextFieldCommonEvent& event) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onSubmit");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(2);
        JSRef<JSObject> object = objectTemplate->NewInstance();
        object->SetProperty<std::string>("text", event.GetText());
        object->SetPropertyObject("keepEditableState", JSRef<JSFunc>::New<FunctionCallback>(JsKeepEditableState));
        object->Wrap<NG::TextFieldCommonEvent>(&event);
        JSRef<JSVal> keyEvent = JSRef<JSVal>::Make(ToJSValue(key));
        JSRef<JSVal> dataObject = JSRef<JSVal>::Cast(object);
        JSRef<JSVal> param[2] = {keyEvent, dataObject};
        func->Execute(param);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "onSubmit");
#endif
    };
    TextFieldModel::GetInstance()->SetOnSubmit(std::move(callback));
}

void JSTextField::SetOnSubmit(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
#ifdef NG_BUILD
    CreateJsTextFieldCommonEvent(info);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        CreateJsTextFieldCommonEvent(info);
    } else {
        JsEventCallback<void(int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
        TextFieldModel::GetInstance()->SetOnSubmit(std::move(callback));
    }
#endif
}

JSRef<JSVal> JSTextField::CreateJsOnChangeObj(const PreviewText& previewText)
{
    JSRef<JSObject> previewTextObj = JSRef<JSObject>::New();
    previewTextObj->SetProperty<int32_t>("offset", previewText.offset);
    previewTextObj->SetProperty<std::string>("value", previewText.value);
    return JSRef<JSVal>::Cast(previewTextObj);
}

void JSTextField::SetOnChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsChangeFunc = AceType::MakeRefPtr<JsCitedEventFunction<PreviewText, 2>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsOnChangeObj);
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsChangeFunc)](
        const std::string& val, PreviewText& previewText) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onChange");
        func->Execute(val, previewText);
    };
    TextFieldModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSTextField::SetOnTextSelectionChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(int32_t, int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnTextSelectionChange(std::move(callback));
}

void JSTextField::SetOnSecurityStateChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(bool)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnSecurityStateChange(std::move(callback));
}

void JSTextField::SetOnContentScroll(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(float, float)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnContentScroll(std::move(callback));
}

void JSTextField::SetOnCopy(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSTextField::SetOnCut(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
    TextFieldModel::GetInstance()->SetOnCut(std::move(callback));
}

JSRef<JSVal> JSTextField::CreateJSTextCommonEvent(NG::TextCommonEvent& event)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> object = objectTemplate->NewInstance();
    object->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsPreventDefault));
    object->Wrap<NG::TextCommonEvent>(&event);
    return JSRef<JSVal>::Cast(object);
}

void JSTextField::SetOnPaste(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 2>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJSTextCommonEvent);

    auto onPaste = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc)](
        const std::string& val, NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        func->Execute(val, info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "onPaste");
#endif
    };
    TextFieldModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
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
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        TextFieldModel::GetInstance()->SetCopyOption(CopyOptions::Local);
        return;
    }
    auto copyOptions = CopyOptions::Local;
    if (jsValue->IsNumber()) {
        auto emunNumber = jsValue->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    TextFieldModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSTextField::SetShowUnderline(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->SetShowUnderline(false);
        return;
    }
    TextFieldModel::GetInstance()->SetShowUnderline(jsValue->ToBoolean());
}

void JSTextField::SetUnderlineColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    Color underlineColor;
    if (ParseJsColor(jsValue, underlineColor)) {
        TextFieldModel::GetInstance()->SetNormalUnderlineColor(underlineColor);
    } else if (jsValue->IsObject()) {
        auto param = JSRef<JSObject>::Cast(jsValue);
        UserUnderlineColor userColor = UserUnderlineColor();
        auto typingColorProp = param->GetProperty("typing");
        Color typing;
        if (ParseJsColor(typingColorProp, typing)) {
            userColor.typing = typing;
        }
        auto normalColorProp = param->GetProperty("normal");
        Color normal;
        if (ParseJsColor(normalColorProp, normal)) {
            userColor.normal = normal;
        }
        auto errorColorProp = param->GetProperty("error");
        Color error;
        if (ParseJsColor(errorColorProp, error)) {
            userColor.error = error;
        }
        auto disableColorProp = param->GetProperty("disable");
        Color disable;
        if (ParseJsColor(disableColorProp, disable)) {
            userColor.disable = disable;
        }
        TextFieldModel::GetInstance()->SetUserUnderlineColor(userColor);
    } else {
        TextFieldModel::GetInstance()->SetUserUnderlineColor(UserUnderlineColor());
    }
}

void JSTextField::SetPasswordIcon(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    auto jsValue = info[0];
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
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
    auto jsValue = info[0];
    if (!jsValue->IsFunction()) {
        TextFieldModel::GetInstance()->SetShowUnit(nullptr);
        return;
    }

    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsValue));
    auto unitFunc = [builderFunc]() { builderFunc->Execute(); };
    TextFieldModel::GetInstance()->SetShowUnit(std::move(unitFunc));
}

void JSTextField::SetShowError(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (Container::IsCurrentUseNewPipeline()) {
        bool isVisible = false;
        std::string errorText;
        if (ParseJsString(jsValue, errorText)) {
            isVisible = true;
        }
        TextFieldModel::GetInstance()->SetShowError(errorText, isVisible);
    }
}

void JSTextField::SetShowCounter(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    auto secondJSValue = info[1];
    if ((!jsValue->IsBoolean() && !secondJSValue->IsObject())) {
        TextFieldModel::GetInstance()->SetShowCounter(false);
        return;
    }
    if (secondJSValue->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(secondJSValue);
        auto param = paramObject->GetProperty("highlightBorder");
        auto isBorderShow = param->ToBoolean();
        if (!param->IsBoolean() || param->IsUndefined() || param->IsNull()) {
            TextFieldModel::GetInstance()->SetShowCounterBorder(true);
        } else {
            TextFieldModel::GetInstance()->SetShowCounterBorder(isBorderShow);
        }
        auto parameter = paramObject->GetProperty("thresholdPercentage");
        auto inputNumber = parameter->ToNumber<int32_t>();
        TextFieldModel::GetInstance()->SetCounterType(inputNumber);
        if (parameter->IsNull() || parameter->IsUndefined()) {
            TextFieldModel::GetInstance()->SetShowCounter(jsValue->ToBoolean());
            TextFieldModel::GetInstance()->SetCounterType(DEFAULT_MODE);
            return;
        }
        if (static_cast<uint32_t>(inputNumber) < MINI_VAILD_VALUE ||
            static_cast<uint32_t>(inputNumber) > MAX_VAILD_VALUE) {
            LOGI("The info is wrong, it is supposed to be a right number");
            TextFieldModel::GetInstance()->SetCounterType(ILLEGAL_VALUE);
            TextFieldModel::GetInstance()->SetShowCounter(false);
            return;
        }
        TextFieldModel::GetInstance()->SetShowCounter(jsValue->ToBoolean());
        return;
    }
    TextFieldModel::GetInstance()->SetShowCounter(jsValue->ToBoolean());
    TextFieldModel::GetInstance()->SetCounterType(DEFAULT_MODE);
    TextFieldModel::GetInstance()->SetShowCounterBorder(true);
}

void JSTextField::SetBarState(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TextFieldModel::GetInstance()->SetBarState(DisplayMode::AUTO);
        return;
    }
    auto jsValue = info[0];
    if (!jsValue->IsNumber()) {
        TextFieldModel::GetInstance()->SetBarState(DisplayMode::AUTO);
        return;
    }
    DisplayMode displayMode = static_cast<DisplayMode>(jsValue->ToNumber<int32_t>());
    TextFieldModel::GetInstance()->SetBarState(displayMode);
}

void JSTextField::SetMaxLines(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TextFieldModel::GetInstance()->SetMaxViewLines(MAX_LINES);
        return;
    }
    auto jsValue = info[0];
    if (!jsValue->IsNumber() || jsValue->ToNumber<int32_t>() <= 0) {
        TextFieldModel::GetInstance()->SetMaxViewLines(MAX_LINES);
        return;
    }
    TextFieldModel::GetInstance()->SetMaxViewLines(jsValue->ToNumber<uint32_t>());
}

void JSTextField::SetEnableKeyboardOnFocus(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || !jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->RequestKeyboardOnFocus(true);
        return;
    }
    TextFieldModel::GetInstance()->RequestKeyboardOnFocus(jsValue->ToBoolean());
}

void JSTextField::SetSelectionMenuHidden(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || !jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->SetSelectionMenuHidden(false);
        return;
    }
    TextFieldModel::GetInstance()->SetSelectionMenuHidden(jsValue->ToBoolean());
}

bool JSTextField::ParseJsCustomKeyboardBuilder(
    const JSCallbackInfo& info, int32_t index, std::function<void()>& buildFunc)
{
    if (info.Length() <= index || !info[index]->IsObject()) {
        return false;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[index]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return false;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_RETURN(builderFunc, false);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CustomKeyboard");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };
    return true;
}

void JSTextField::SetCustomKeyboard(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || jsValue->IsNull() || !jsValue->IsObject()) {
        TextFieldModel::GetInstance()->SetCustomKeyboard(nullptr);
        return;
    }
    bool supportAvoidance = false;
    if (info.Length() == 2 && info[1]->IsObject()) {  //  2 here refers to the number of parameters
        auto paramObject = JSRef<JSObject>::Cast(info[1]);
        auto isSupportAvoidance = paramObject->GetProperty("supportAvoidance");
        if (!isSupportAvoidance->IsNull() && isSupportAvoidance->IsBoolean()) {
            supportAvoidance = isSupportAvoidance->ToBoolean();
        }
    }
    std::function<void()> buildFunc;
    if (ParseJsCustomKeyboardBuilder(info, 0, buildFunc)) {
        TextFieldModel::GetInstance()->SetCustomKeyboard(std::move(buildFunc), supportAvoidance);
    }
}

void JSTextField::SetPasswordRules(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsString()) {
        return;
    }
    auto passwordRules = jsValue->ToString();
    TextFieldModel::GetInstance()->SetPasswordRules(passwordRules);
}

void JSTextField::SetEnableAutoFill(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->SetEnableAutoFill(true);
        return;
    }
    TextFieldModel::GetInstance()->SetEnableAutoFill(jsValue->ToBoolean());
}

static CleanNodeStyle ConvertStrToCleanNodeStyle(const std::string& value)
{
    if (value == "CONSTANT") {
        return CleanNodeStyle::CONSTANT;
    } else if (value == "INVISIBLE") {
        return CleanNodeStyle::INVISIBLE;
    } else {
        return CleanNodeStyle::INPUT;
    }
}

void JSTextField::SetCancelButton(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        ResetCancelIcon();
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto theme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);

    // set style
    std::string styleStr;
    CleanNodeStyle cleanNodeStyle;
    auto styleProp = param->GetProperty("style");
    if (!styleProp->IsNull() && ParseJsString(styleProp, styleStr)) {
        cleanNodeStyle = ConvertStrToCleanNodeStyle(styleStr);
    } else {
        cleanNodeStyle = CleanNodeStyle::INPUT;
    }
    TextFieldModel::GetInstance()->SetCleanNodeStyle(cleanNodeStyle);
    TextFieldModel::GetInstance()->SetIsShowCancelButton(true);

    // set default icon
    auto iconJsVal = param->GetProperty("icon");
    if (iconJsVal->IsUndefined() || iconJsVal->IsNull() || !iconJsVal->IsObject()) {
        SetCancelDefaultIcon();
        return;
    }

    auto iconParam = JSRef<JSObject>::Cast(iconJsVal);
    bool isSymbolIcon = iconParam->HasProperty("fontColor"); // only SymbolGlyph has fontColor property
    if (isSymbolIcon) {
        SetCancelSymbolIcon(info);
        return;
    }

    // set icon size
    CalcDimension iconSize;
    auto iconSizeProp = iconParam->GetProperty("size");
    if (!iconSizeProp->IsUndefined() && !iconSizeProp->IsNull() && ParseJsDimensionVpNG(iconSizeProp, iconSize)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconSize();
        }
    } else {
        iconSize = theme->GetIconSize();
    }
    TextFieldModel::GetInstance()->SetCancelIconSize(iconSize);
    SetCancelIconColorAndIconSrc(iconParam);
}

void JSTextField::SetCancelDefaultIcon()
{
    auto theme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    if (SystemProperties::GetColorMode() == ColorMode::DARK) {
        TextFieldModel::GetInstance()->SetCancelIconColor(theme->GetCancelButtonIconColor());
    } else {
        TextFieldModel::GetInstance()->SetCancelIconColor(Color());
    }
    TextFieldModel::GetInstance()->SetCancelIconSize(theme->GetIconSize());
    TextFieldModel::GetInstance()->SetCanacelIconSrc(std::string(), std::string(), std::string());
    TextFieldModel::GetInstance()->SetCancelSymbolIcon(nullptr);
    TextFieldModel::GetInstance()->SetCancelButtonSymbol(true);
}

void JSTextField::ResetCancelIcon()
{
    TextFieldModel::GetInstance()->SetCleanNodeStyle(CleanNodeStyle::INPUT);
    TextFieldModel::GetInstance()->SetIsShowCancelButton(false);
    TextFieldModel::GetInstance()->SetCancelSymbolIcon(nullptr);
    TextFieldModel::GetInstance()->SetCancelButtonSymbol(true);
}

void JSTextField::SetCancelSymbolIcon(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
        auto param = JSRef<JSObject>::Cast(info[0]);
        auto iconProp = param->GetProperty("icon");
        SetSymbolOptionApply(info, iconSymbol, iconProp);
        TextFieldModel::GetInstance()->SetCancelSymbolIcon(iconSymbol);
        TextFieldModel::GetInstance()->SetCancelButtonSymbol(true);
    }
}

void JSTextField::SetCancelIconColorAndIconSrc(const JSRef<JSObject>& iconParam)
{
    auto theme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    // set icon src
    std::string iconSrc;
    std::string bundleName;
    std::string moduleName;
    auto iconSrcProp = iconParam->GetProperty("src");
    if (iconSrcProp->IsUndefined() || iconSrcProp->IsNull() || !ParseJsMedia(iconSrcProp, iconSrc)) {
        iconSrc = "";
    }
    GetJsMediaBundleInfo(iconSrcProp, bundleName, moduleName);
    TextFieldModel::GetInstance()->SetCanacelIconSrc(iconSrc, bundleName, moduleName);
    TextFieldModel::GetInstance()->SetCancelButtonSymbol(false);
    // set icon color
    Color iconColor;
    auto iconColorProp = iconParam->GetProperty("color");
    if (!iconColorProp->IsUndefined() && !iconColorProp->IsNull() && ParseJsColor(iconColorProp, iconColor)) {
        TextFieldModel::GetInstance()->SetCancelIconColor(iconColor);
        return;
    }
    auto info = ImageSourceInfo(iconSrc, bundleName, moduleName);
    if (info.IsSvg() && iconSrc != "") {
        // svg need not default color, otherwise multi color svg will render fault
        return;
    }
    if (SystemProperties::GetColorMode() == ColorMode::DARK) {
        TextFieldModel::GetInstance()->SetCancelIconColor(theme->GetCancelButtonIconColor());
    } else {
        TextFieldModel::GetInstance()->SetCancelIconColor(iconColor);
    }
}

void JSTextField::SetSelectAllValue(const JSCallbackInfo& info)
{
    auto infoValue = info[0];
    if (!infoValue->IsBoolean() || infoValue->IsUndefined() || infoValue->IsNull()) {
        TextFieldModel::GetInstance()->SetSelectAllValue(false);
        return;
    }

    bool isSetSelectAllValue = infoValue->ToBoolean();
    TextFieldModel::GetInstance()->SetSelectAllValue(isSetSelectAllValue);
}

void JSTextField::SetDecoration(const JSCallbackInfo& info)
{
    do {
        auto tmpInfo = info[0];
        if (!tmpInfo->IsObject()) {
            TextFieldModel::GetInstance()->SetTextDecoration(TextDecoration::NONE);
            TextFieldModel::GetInstance()->SetTextDecorationColor(Color::BLACK);
            TextFieldModel::GetInstance()->SetTextDecorationStyle(TextDecorationStyle::SOLID);
            break;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(tmpInfo);
        JSRef<JSVal> typeValue = obj->GetProperty("type");
        JSRef<JSVal> colorValue = obj->GetProperty("color");
        JSRef<JSVal> styleValue = obj->GetProperty("style");

        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        TextDecoration textDecoration = theme->GetTextStyle().GetTextDecoration();
        if (typeValue->IsNumber()) {
            textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
        }
        Color result = theme->GetTextStyle().GetTextDecorationColor();
        ParseJsColor(colorValue, result, Color::BLACK);
        std::optional<TextDecorationStyle> textDecorationStyle;
        if (styleValue->IsNumber()) {
            textDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
        } else {
            textDecorationStyle = DEFAULT_TEXT_DECORATION_STYLE;
        }
        TextFieldModel::GetInstance()->SetTextDecoration(textDecoration);
        TextFieldModel::GetInstance()->SetTextDecorationColor(result);
        if (textDecorationStyle) {
            TextFieldModel::GetInstance()->SetTextDecorationStyle(textDecorationStyle.value());
        }
    } while (false);
}

void JSTextField::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension minFontSize;
    if (!ParseJsDimensionFpNG(info[0], minFontSize, false)) {
        TextFieldModel::GetInstance()->SetAdaptMinFontSize(CalcDimension());
        return;
    }
    if (minFontSize.IsNegative()) {
        minFontSize = CalcDimension();
    }
    TextFieldModel::GetInstance()->SetAdaptMinFontSize(minFontSize);
}

void JSTextField::SetMaxFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    if (!ParseJsDimensionFpNG(info[0], maxFontSize, false)) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
        TextFieldModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
        return;
    }
    if (maxFontSize.IsNegative()) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    }
    TextFieldModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
}

void JSTextField::SetHeightAdaptivePolicy(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        value = 0;
    }
    TextFieldModel::GetInstance()->SetHeightAdaptivePolicy(HEIGHT_ADAPTIVE_POLICY[value]);
}

void JSTextField::SetLetterSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value, false)) {
        value.Reset();
        TextFieldModel::GetInstance()->SetLetterSpacing(value);
        return;
    }
    TextFieldModel::GetInstance()->SetLetterSpacing(value);
}

void JSTextField::SetLineHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value)) {
        value.Reset();
        TextFieldModel::GetInstance()->SetLineHeight(value);
        return;
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    TextFieldModel::GetInstance()->SetLineHeight(value);
}

void JSTextField::SetLineSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseLengthMetricsToPositiveDimension(info[0], value)) {
        value.Reset();
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    TextFieldModel::GetInstance()->SetLineSpacing(value);
}

void JSTextField::SetFontFeature(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    std::string fontFeatureSettings = "";
    if (jsValue->IsString()) {
        fontFeatureSettings = jsValue->ToString();
    }
    TextFieldModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

void JSTextField::SetTextOverflow(const JSCallbackInfo& info)
{
    do {
        auto tmpInfo = info[0];
        int32_t overflow = 0;
        if (info.Length() < 1) {
            break;
        }
        if (tmpInfo->IsUndefined() || tmpInfo->IsNull() || !tmpInfo->IsNumber()) {
            overflow = DEFAULT_OVERFLOW;
        } else if (tmpInfo->IsNumber()) {
            overflow = tmpInfo->ToNumber<int32_t>();
            if (overflow < 0 || overflow >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
                overflow = DEFAULT_OVERFLOW;
            }
        }
        TextFieldModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[overflow]);
    } while (false);

    info.SetReturnValue(info.This());
}

void JSTextField::SetTextIndent(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVpNG(info[0], value, true)) {
        value.Reset();
    }
    TextFieldModel::GetInstance()->SetTextIndent(value);
}

JSRef<JSVal> JSTextField::CreateJsAboutToIMEInputObj(const InsertValueInfo& insertValue)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("insertOffset", insertValue.insertOffset);
    aboutToIMEInputObj->SetProperty<std::string>("insertValue", insertValue.insertValue);
    return JSRef<JSVal>::Cast(aboutToIMEInputObj);
}

void JSTextField::OnWillInsertValue(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc = AceType::MakeRefPtr<JsEventFunction<InsertValueInfo, 1>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsAboutToIMEInputObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const InsertValueInfo& insertValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(insertValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    TextFieldModel::GetInstance()->SetOnWillInsertValueEvent(std::move(callback));
}

JSRef<JSVal> JSTextField::CreateJsDeleteToIMEObj(const DeleteValueInfo& deleteValueInfo)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("deleteOffset", deleteValueInfo.deleteOffset);
    aboutToIMEInputObj->SetProperty<int32_t>("direction", static_cast<int32_t>(deleteValueInfo.direction));
    aboutToIMEInputObj->SetProperty<std::string>("deleteValue", deleteValueInfo.deleteValue);
    return JSRef<JSVal>::Cast(aboutToIMEInputObj);
}

void JSTextField::OnDidInsertValue(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc = AceType::MakeRefPtr<JsEventFunction<InsertValueInfo, 1>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsAboutToIMEInputObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const InsertValueInfo& insertValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->ExecuteWithValue(insertValue);
    };
    TextFieldModel::GetInstance()->SetOnDidInsertValueEvent(std::move(callback));
}

void JSTextField::OnWillDelete(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc =
        AceType::MakeRefPtr<JsEventFunction<DeleteValueInfo, 1>>(JSRef<JSFunc>::Cast(jsValue), CreateJsDeleteToIMEObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const DeleteValueInfo& deleteValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(deleteValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    TextFieldModel::GetInstance()->SetOnWillDeleteEvent(std::move(callback));
}

void JSTextField::OnDidDelete(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc =
        AceType::MakeRefPtr<JsEventFunction<DeleteValueInfo, 1>>(JSRef<JSFunc>::Cast(jsValue), CreateJsDeleteToIMEObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const DeleteValueInfo& deleteValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->ExecuteWithValue(deleteValue);
    };
    TextFieldModel::GetInstance()->SetOnDidDeleteEvent(std::move(callback));
}

void JSTextField::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick);
    TextFieldModel::GetInstance()->SetSelectionMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void JSTextField::SetEnablePreviewText(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsBoolean()) {
        TextFieldModel::GetInstance()->SetEnablePreviewText(true);
        return;
    }
    TextFieldModel::GetInstance()->SetEnablePreviewText(jsValue->ToBoolean());
}

void JSTextField::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    bool state = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        state = info[0]->ToBoolean();
    }
    TextFieldModel::GetInstance()->SetEnableHapticFeedback(state);
}

} // namespace OHOS::Ace::Framework
