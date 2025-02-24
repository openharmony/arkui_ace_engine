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
#include "securec.h"

#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components/text_field/textfield_theme.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextInputAction> TEXT_INPUT_ACTIONS = { TextInputAction::UNSPECIFIED, TextInputAction::NONE,
    TextInputAction::GO, TextInputAction::SEARCH, TextInputAction::SEND, TextInputAction::NEXT, TextInputAction::DONE,
    TextInputAction::PREVIOUS, TextInputAction::NEW_LINE };
const std::vector<TextInputType> TEXT_INPUT_TYPES = { TextInputType::TEXT, TextInputType::NUMBER,
    TextInputType::EMAIL_ADDRESS, TextInputType::VISIBLE_PASSWORD, TextInputType::PHONE, TextInputType::USER_NAME,
    TextInputType::NEW_PASSWORD, TextInputType::NUMBER_PASSWORD, TextInputType::NUMBER_DECIMAL, TextInputType::URL };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::function<void(std::u16string)> FormatCharFunction(void (*callback)(const char* value))
{
    const std::function<void(std::u16string)> result = [lambda = CJLambda::Create(callback)]
        (const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16DebugToStr8(value);
        lambda(valueStr.c_str());
    };
    return result;
}
constexpr uint32_t MINI_VAILD_VALUE = 1;
constexpr uint32_t MAX_VAILD_VALUE = 100;
constexpr uint32_t ILLEGAL_VALUE = 0;
constexpr uint32_t DEFAULTMAXLINES = 3;

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

void FfiOHOSAceFrameworkTextFieldSetFontFeature(const char* value)
{
    TextFieldModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(value));
}

void FfiOHOSAceFrameworkTextFieldSetLineHeight(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetLineHeight(size);
}

void FfiOHOSAceFrameworkTextFieldSetLineSpacing(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetLineSpacing(size);
}

void FfiOHOSAceFrameworkTextFieldSetLetterSpacing(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetLetterSpacing(size);
}

void FfiOHOSAceFrameworkTextFieldSetDecoration(int32_t value, uint32_t color, int32_t style)
{
    TextFieldModel::GetInstance()->SetTextDecoration(static_cast<TextDecoration>(value));
    TextFieldModel::GetInstance()->SetTextDecorationColor(Color(color));
    TextFieldModel::GetInstance()->SetTextDecorationStyle(static_cast<TextDecorationStyle>(style));
}

void FfiOHOSAceFrameworkTextFieldSetLineBreakStrategy(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(LineBreakStrategy::BALANCED)) {
        value = 0;
    }
    TextFieldModel::GetInstance()->SetLineBreakStrategy(static_cast<LineBreakStrategy>(value));
}

void FfiOHOSAceFrameworkTextFieldSetWordBreak(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(WordBreak::BREAK_WORD)) {
        value = static_cast<int32_t>(WordBreak::BREAK_WORD);
    }
    TextFieldModel::GetInstance()->SetWordBreak(static_cast<WordBreak>(value));
}

void FfiOHOSAceFrameworkTextFieldSetHeightAdaptivePolicy(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST)) {
        value = 0;
    }
    TextFieldModel::GetInstance()->SetHeightAdaptivePolicy(static_cast<TextHeightAdaptivePolicy>(value));
}

void FfiOHOSAceFrameworkTextFieldSetMaxFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetAdaptMaxFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldSetMinFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size = Dimension();
    }

    TextFieldModel::GetInstance()->SetAdaptMinFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldSetSelectedBackgroundColor(uint32_t value)
{
    TextFieldModel::GetInstance()->SetSelectedBackgroundColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetCaretStyle(double value, int32_t unit, uint32_t color)
{
    CaretStyle caretStyle;
    caretStyle.caretWidth = Dimension(value, (DimensionUnit)unit);

    TextFieldModel::GetInstance()->SetCaretStyle(caretStyle);
    TextFieldModel::GetInstance()->SetCaretColor(Color(color));
}

void FfiOHOSAceFrameworkTextFieldSetTextIndent(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    TextFieldModel::GetInstance()->SetTextIndent(size);
}

void FfiOHOSAceFrameworkTextFieldSetTextOverflow(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        value = 0;
    }
    TextFieldModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[value]);
}

void FfiOHOSAceFrameworkTextFieldSetEnablePreviewText(bool value)
{
    TextFieldModel::GetInstance()->SetEnablePreviewText(value);
}

void FfiOHOSAceFrameworkTextFieldSetStyle(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(InputStyle::INLINE)) {
        value = static_cast<int32_t>(InputStyle::DEFAULT);
    }
    TextFieldModel::GetInstance()->SetInputStyle(static_cast<InputStyle>(value));
}

void FfiOHOSAceFrameworkTextFieldSetBarState(int32_t value)
{
    TextFieldModel::GetInstance()->SetBarState(static_cast<DisplayMode>(value));
}

void FfiOHOSAceFrameworkTextFieldSetSelectionMenuHidden(bool value)
{
    TextFieldModel::GetInstance()->SetSelectionMenuHidden(value);
}

void FfiOHOSAceFrameworkTextFieldSetShowCounter(bool value, int32_t threshold, bool showBorder)
{
    TextFieldModel::GetInstance()->SetShowCounterBorder(showBorder);
    if (threshold >= static_cast<int32_t>(MINI_VAILD_VALUE) && threshold <= static_cast<int32_t>(MAX_VAILD_VALUE)) {
        TextFieldModel::GetInstance()->SetShowCounter(value);
        TextFieldModel::GetInstance()->SetCounterType(threshold);
    } else {
        TextFieldModel::GetInstance()->SetShowCounter(false);
        TextFieldModel::GetInstance()->SetCounterType(ILLEGAL_VALUE);
    }
}

void FfiOHOSAceFrameworkTextFieldSetMaxLines(int32_t value)
{
    if (value <= 0) {
        value = DEFAULTMAXLINES;
    }
    TextFieldModel::GetInstance()->SetMaxLines(value);
}

void FfiOHOSAceFrameworkTextFieldSetEnableKeyboardOnFocus(bool value)
{
    TextFieldModel::GetInstance()->RequestKeyboardOnFocus(value);
}

void FfiOHOSAceFrameworkTextFieldSetContentType(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(NG::TextContentType::END)) {
        value = static_cast<int32_t>(NG::TextContentType::UNSPECIFIED);
    }
    TextFieldModel::GetInstance()->SetContentType(static_cast<NG::TextContentType>(value));
}

void FfiOHOSAceFrameworkTextFieldSetEnableAutoFill(bool value)
{
    TextFieldModel::GetInstance()->SetEnableAutoFill(value);
}

void FfiOHOSAceFrameworkTextFieldSetTextAreaType(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(TextInputType::END)) {
        value = static_cast<int32_t>(TextInputType::UNSPECIFIED);
    }
    TextFieldModel::GetInstance()->SetType(static_cast<TextInputType>(value));
}

void FfiOHOSAceFrameworkTextFieldSetCopyOption(int32_t value)
{
    TextFieldModel::GetInstance()->SetCopyOption(static_cast<CopyOptions>(value));
}

void FfiOHOSAceFrameworkTextFieldSetCustomKeyboard(void (*callback)(), bool options)
{
    auto builderFunc = CJLambda::Create(callback);
    TextFieldModel::GetInstance()->SetCustomKeyboard(std::move(builderFunc), options);
}

void FfiOHOSAceFrameworkTextFieldOnSecurityStateChange(void (*callback)(bool value))
{
    TextFieldModel::GetInstance()->SetOnSecurityStateChange(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkTextFieldShowUnit(void (*callback)())
{
    auto unitFunc = CJLambda::Create(callback);
    TextFieldModel::GetInstance()->SetShowUnit(std::move(unitFunc));
}

void FfiOHOSAceFrameworkTextFieldSetPasswordRules(const char* rules)
{
    if (rules == nullptr) {
        return;
    }
    TextFieldModel::GetInstance()->SetPasswordRules(rules);
}

void FfiOHOSAceFrameworkTextFieldSetShowError(const char* errorText)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    bool isVisible = false;
    std::string error;

    if (errorText != nullptr) {
        error = errorText;
        isVisible = true;
    }

    TextFieldModel::GetInstance()->SetShowError(UtfUtils::Str8ToStr16(error), isVisible);
}

void FfiOHOSAceFrameworkTextFieldSetShowPasswordIcon(bool isShow)
{
    TextFieldModel::GetInstance()->SetShowPasswordIcon(isShow);
}

void FfiOHOSAceFrameworkTextFieldShowPasswordText(bool show)
{
    TextFieldModel::GetInstance()->SetShowPasswordText(show);
}

void FfiOHOSAceFrameworkTextFieldSetPasswordIcon(const char* onIconSrc, const char* offIconSrc)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    PasswordIcon passwordIcon;
    if (onIconSrc != nullptr) {
        passwordIcon.showResult = onIconSrc;
    }

    if (offIconSrc != nullptr) {
        passwordIcon.hideResult = offIconSrc;
    }

    TextFieldModel::GetInstance()->SetPasswordIcon(passwordIcon);
}

void FfiOHOSAceFrameworkTextFieldSetCaretPosition(int32_t position)
{
    int32_t caretPosition = 0;

    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        caretPosition = (position < 0) ? 0 : position;
    } else {
        if (position < 0) {
            return;
        }
        caretPosition = position;
    }

    TextFieldModel::GetInstance()->SetCaretPosition(caretPosition);
}

void FfiOHOSAceFrameworkTextFieldSetSelectAllValue(bool value)
{
    TextFieldModel::GetInstance()->SetSelectAllValue(value);
}

void FfiOHOSAceFrameworkTextFieldSetShowUnderline(bool show)
{
    TextFieldModel::GetInstance()->SetShowUnderline(show);
}

void FfiOHOSAceFrameworkTextFieldNormalUnderlineColor(uint32_t color)
{
    TextFieldModel::GetInstance()->SetNormalUnderlineColor(Color(color));
}

void FfiOHOSAceFrameworkTextFieldUserUnderlineColor(uint32_t typing, uint32_t normal, uint32_t error, uint32_t disable)
{
    UserUnderlineColor userColor = UserUnderlineColor();
    userColor.typing = Color(typing);
    userColor.normal = Color(normal);
    userColor.error = Color(error);
    userColor.disable = Color(disable);
    TextFieldModel::GetInstance()->SetUserUnderlineColor(userColor);
}

void FfiOHOSAceFrameworkTextFieldCancelButton(int32_t style, double size, int32_t unit, uint32_t color, const char* src)
{
    // set style
    if (style < 0) {
        TextFieldModel::GetInstance()->SetCleanNodeStyle(CleanNodeStyle::INPUT);
    } else {
        TextFieldModel::GetInstance()->SetCleanNodeStyle(static_cast<CleanNodeStyle>(style));
    }
    TextFieldModel::GetInstance()->SetIsShowCancelButton(true);
    // set normal
    if (src == nullptr) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        if (SystemProperties::GetColorMode() == ColorMode::DARK) {
            TextFieldModel::GetInstance()->SetCancelIconColor(theme->GetCancelButtonIconColor());
        } else {
            TextFieldModel::GetInstance()->SetCancelIconColor(Color());
        }
        TextFieldModel::GetInstance()->SetCancelIconSize(theme->GetIconSize());
        TextFieldModel::GetInstance()->SetCanacelIconSrc(std::string(), std::string(), std::string());
        return;
    }
    // set size
    CalcDimension iconSize(size, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        iconSize = theme->GetIconSize();
    }
    TextFieldModel::GetInstance()->SetCancelIconSize(iconSize);
    // set color
    Color iconColor(color);
    if (SystemProperties::GetColorMode() == ColorMode::DARK) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        TextFieldModel::GetInstance()->SetCancelIconColor(theme->GetCancelButtonIconColor());
    } else {
        TextFieldModel::GetInstance()->SetCancelIconColor(iconColor);
    }
    // set src
    std::string iconSrc(src);
    TextFieldModel::GetInstance()->SetCanacelIconSrc(iconSrc, std::string(), std::string());
}

void FfiOHOSAceFrameworkTextFieldOnSubmit(void (*callback)(int32_t value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto task = [func = CJLambda::Create(callback), node = targetNode](int32_t key, NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        func(key);
    };
    TextFieldModel::GetInstance()->SetOnSubmit(task);
}

void FfiOHOSAceFrameworkTextFieldOnChange(void (*callback)(const char* value))
{
    auto onChange = [func = FormatCharFunction(callback)](
                        const ChangeValueInfo& info) { func(info.value); };
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
                       const std::u16string& val, NG::TextCommonEvent& info) { func(val); };
    TextFieldModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
}

void FfiOHOSAceFrameworkTextFieldOnEditChanged(void (*callback)(bool value))
{
    TextFieldModel::GetInstance()->SetOnEditChanged(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkTextFieldOnContentScroll(void (*callback)(float totalOffsetX, float totalOffsetY))
{
    auto onScroll = [lambda = CJLambda::Create(callback)](
                        float totalOffsetX, float totalOffsetY) -> void { lambda(totalOffsetX, totalOffsetY); };
    TextFieldModel::GetInstance()->SetOnContentScroll(onScroll);
}

void FfiOHOSAceFrameworkTextFieldOnTextSelectionChange(void (*callback)(int32_t selectionStart, int32_t selectionEnd))
{
    auto onTextSelectionChange = [lambda = CJLambda::Create(callback)](int32_t selectionStart,
                                     int32_t selectionEnd) -> void { lambda(selectionStart, selectionEnd); };
    TextFieldModel::GetInstance()->SetOnTextSelectionChange(onTextSelectionChange);
}

void FfiOHOSAceFrameworkTextFieldOnDidDelete(
    void (*callback)(double deleteOffset, int32_t direction, const char* deleteValue))
{
    auto onDidDelete = [lambda = CJLambda::Create(callback)](const DeleteValueInfo& Info) -> void {
        double deleteOffset = Info.deleteOffset;
        int32_t direction = static_cast<int32_t>(Info.direction);
        const std::string deleteStr = UtfUtils::Str16ToStr8(Info.deleteValue);
        const char* deleteValue = deleteStr.c_str();
        lambda(deleteOffset, direction, deleteValue);
    };
    TextFieldModel::GetInstance()->SetOnDidDeleteEvent(onDidDelete);
}

void FfiOHOSAceFrameworkTextFieldOnWillDelete(
    bool (*callback)(double deleteOffset, int32_t direction, const char* deleteValue))
{
    auto onWillDelete = [lambda = CJLambda::Create(callback)](const DeleteValueInfo& Info) -> bool {
        double deleteOffset = Info.deleteOffset;
        int32_t direction = static_cast<int32_t>(Info.direction);
        const std::string deleteStr = UtfUtils::Str16ToStr8(Info.deleteValue);
        const char* deleteValue = deleteStr.c_str();
        return lambda(deleteOffset, direction, deleteValue);
    };
    TextFieldModel::GetInstance()->SetOnWillDeleteEvent(onWillDelete);
}

void FfiOHOSAceFrameworkTextFieldOnDidInsert(void (*callback)(double insertOffset, const char* insertValue))
{
    auto onDidInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> void {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        lambda(insertOffset, insertValue);
    };
    TextFieldModel::GetInstance()->SetOnDidInsertValueEvent(onDidInsert);
}

void FfiOHOSAceFrameworkTextFieldOnWillInsert(bool (*callback)(double insertOffset, const char* insertValue))
{
    auto onWillInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> bool {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        return lambda(insertOffset, insertValue);
    };
    TextFieldModel::GetInstance()->SetOnWillInsertValueEvent(onWillInsert);
}

void FfiOHOSAceFrameworkTextFieldOnChangePreviewText(
    void (*callback)(const char* value, int32_t offset, const char* text))
{
    auto onChange = [func = CJLambda::Create(callback)](const ChangeValueInfo& info) {
        const std::string valStr = UtfUtils::Str16ToStr8(info.value);
        const std::string previewTextStr = UtfUtils::Str16ToStr8(info.previewText.value);
        func(valStr.c_str(), info.previewText.offset, previewTextStr.c_str());
    };
    TextFieldModel::GetInstance()->SetOnChange(onChange);
}

void FfiOHOSAceFrameworkTextFieldonSubmitWithEvent(bool (*callback)(int32_t value, CJSubmitEvent))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto task = [func = CJLambda::Create(callback), node = targetNode](int32_t key, NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        auto submitEvent = std::make_unique<CJSubmitEvent>();
        std::string text = UtfUtils::Str16ToStr8(event.GetText());
        size_t len = text.length() + 1;
        submitEvent->text = (char*)malloc(len);
        submitEvent->keepEditable = event.IsKeepEditable();
        if (submitEvent->text) {
            const char* src = text.c_str();
            errno_t ret = strncpy_s(submitEvent->text, len, src, len - 1);
            if (ret != EOK) {
                free(submitEvent->text);
                return;
            }
            event.SetKeepEditable(func(key, *submitEvent));
            free(submitEvent->text);
        } else {
            event.SetKeepEditable(func(key, *submitEvent));
        }
    };
    TextFieldModel::GetInstance()->SetOnSubmit(task);
}
}
