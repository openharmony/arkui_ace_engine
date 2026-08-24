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
#include "core/common/dynamic_module_helper.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

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
    TextInputType::NEW_PASSWORD, TextInputType::NUMBER_PASSWORD, TextInputType::NUMBER_DECIMAL, TextInputType::URL,
    TextInputType::ONE_TIME_CODE };
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

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::TextFieldModelNG* GetTextFieldModel()
{
    static NG::TextFieldModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextInput");
        if (module == nullptr) {
            LOGF_ABORT("Can't find textfield dynamic module");
        }
        cachedModel = reinterpret_cast<NG::TextFieldModelNG*>(module->GetModel());
    }
    return cachedModel;
}
} // namespace OHOS::Ace

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
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderWidth(double value, uint32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidth(value, unit);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderColor(uint32_t color)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderColor(color);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderWidthWithCJEdge(CJEdge params)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidthWithCJEdge(params);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }

    FfiOHOSAceFrameworkViewAbstractSetBorderStyle(style);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBorderRadius(double value, uint32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderRadius(value, unit);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetAllBorderRadius(CJBorderRadius value)
{
    FfiOHOSAceFrameworkViewAbstractSetAllBorderRadius(value);
    GetTextFieldModel()->SetBackBorder();
}

void FfiOHOSAceFrameworkTextFieldSetBackgroundColor(uint32_t value)
{
    GetTextFieldModel()->SetBackgroundColor(Color(value), false);
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
    GetTextFieldModel()->SetPadding(paddings, Edge(), false);
}

void FfiOHOSAceFrameworkTextFieldSetMargin(double value, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetMargin(value, unit);
    GetTextFieldModel()->SetMargin();
}

void FfiOHOSAceFrameworkTextFieldSetMargins(CJEdge params)
{
    FfiOHOSAceFrameworkViewAbstractSetMargins(params);
    GetTextFieldModel()->SetMargin();
}

void FfiOHOSAceFrameworkTextFieldSetPlaceholderColor(uint32_t value)
{
    GetTextFieldModel()->SetPlaceholderColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldResetPlaceholderColor()
{
    GetTextFieldModel()->ResetPlaceholderColor();
}

void FfiOHOSAceFrameworkTextFieldSetPlaceholderFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    if (!Utils::CheckParamsValid(style, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    Dimension sizeDime(size, static_cast<DimensionUnit>(unit));

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        if (sizeDime.Unit() == DimensionUnit::PERCENT) {
            auto theme = GetTheme<TextFieldTheme>();
            sizeDime = theme->GetFontSize();
        }
    } else {
        if (sizeDime.IsNegative()) {
            sizeDime.SetValue(0.0);
        }
    }

    OHOS::Ace::Font font;

    font.fontWeight = ConvertStrToFontWeight(weight);
    font.fontSize = sizeDime;
    font.fontStyle = FONT_STYLES[style];
    font.fontFamilies = ConvertStrToFontFamilies(family);

    GetTextFieldModel()->SetPlaceholderFont(font);
}

void FfiOHOSAceFrameworkTextFieldSetEnterKeyType(int32_t type)
{
    if (!Utils::CheckParamsValid(type, TEXT_INPUT_ACTIONS.size())) {
        LOGE("invalid value for text input action");
        return;
    }

    GetTextFieldModel()->SetEnterKeyType(TEXT_INPUT_ACTIONS[type]);
}

void FfiOHOSAceFrameworkTextFieldSetType(int32_t value)
{
    if (!Utils::CheckParamsValid(value, TEXT_INPUT_TYPES.size())) {
        LOGE("invalid value for text input type");
        return;
    }

    GetTextFieldModel()->SetType(TEXT_INPUT_TYPES[value]);
}

void FfiOHOSAceFrameworkTextFieldSetTextAlign(int32_t value)
{
    if (!Utils::CheckParamsValid(value, TEXT_ALIGNS.size())) {
        LOGE("invalid value for textAlign");
        return;
    }

    GetTextFieldModel()->SetTextAlign(TEXT_ALIGNS[value]);
}

void FfiOHOSAceFrameworkTextFieldSetCaretColor(uint32_t value)
{
    GetTextFieldModel()->SetCaretColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetMaxLength(uint32_t value)
{
    GetTextFieldModel()->SetMaxLength(value);
}

void FfiOHOSAceFrameworkTextFieldResetMaxLength()
{
    GetTextFieldModel()->ResetMaxLength();
}

void FfiOHOSAceFrameworkTextFieldSetFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    // For API versions >= 23, negative font sizes are handled by the layoutmodel.
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        if (size.IsNegative()) {
            size.SetValue(0.0);
        }
    }

    GetTextFieldModel()->SetFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldResetFontSize()
{
    CalcDimension fontSize;
    auto theme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    fontSize = theme->GetFontSize();

    GetTextFieldModel()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkTextFieldSetFontColor(uint32_t value)
{
    GetTextFieldModel()->SetTextColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldResetFontColor()
{
    GetTextFieldModel()->ResetTextColor();
}

void FfiOHOSAceFrameworkTextFieldSetFontWeight(const char* value)
{
    GetTextFieldModel()->SetFontWeight(ConvertStrToFontWeight(value));
}

void FfiOHOSAceFrameworkTextFieldSetFontStyle(int32_t value)
{
    if (!Utils::CheckParamsValid(value, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }

    GetTextFieldModel()->SetFontStyle(FONT_STYLES[value]);
}

void FfiOHOSAceFrameworkTextFieldSetFontFamily(const char* value)
{
    GetTextFieldModel()->SetFontFamily(ConvertStrToFontFamilies(value));
}

void FfiOHOSAceFrameworkTextFieldSetInputFilter(const char* value, void (*callback)(const char* value))
{
    GetTextFieldModel()->SetInputFilter(value, FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldSetFontFeature(const char* value)
{
    GetTextFieldModel()->SetFontFeature(ParseFontFeatureSettings(value));
}

void FfiOHOSAceFrameworkTextFieldSetWidth(double value, uint32_t unit)
{
    GetTextFieldModel()->SetWidthAuto(false);
    Dimension width(value, static_cast<DimensionUnit>(unit));
    if (width.Unit() == DimensionUnit::AUTO) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        GetTextFieldModel()->SetWidthAuto(true);
        ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        return;
    }

    if (LessNotEqual(width.Value(), 0.0)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetWidth(width);
}

void FfiOHOSAceFrameworkTextFieldSetLineHeight(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    GetTextFieldModel()->SetLineHeight(size);
}

void FfiOHOSAceFrameworkTextFieldSetLineSpacing(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    GetTextFieldModel()->SetLineSpacing(size);
}

void FfiOHOSAceFrameworkTextFieldSetLetterSpacing(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    GetTextFieldModel()->SetLetterSpacing(size);
}

void FfiOHOSAceFrameworkTextFieldSetDecoration(int32_t value, uint32_t color, int32_t style)
{
    GetTextFieldModel()->SetTextDecoration(static_cast<TextDecoration>(value));
    GetTextFieldModel()->SetTextDecorationColor(Color(color));
    GetTextFieldModel()->SetTextDecorationStyle(static_cast<TextDecorationStyle>(style));
}

void FfiOHOSAceFrameworkTextFieldSetLineBreakStrategy(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(LineBreakStrategy::BALANCED)) {
        value = 0;
    }
    GetTextFieldModel()->SetLineBreakStrategy(static_cast<LineBreakStrategy>(value));
}

void FfiOHOSAceFrameworkTextFieldSetWordBreak(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(WordBreak::BREAK_WORD)) {
        value = static_cast<int32_t>(WordBreak::BREAK_WORD);
    }
    GetTextFieldModel()->SetWordBreak(static_cast<WordBreak>(value));
}

void FfiOHOSAceFrameworkTextFieldSetHeightAdaptivePolicy(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST)) {
        value = 0;
    }
    GetTextFieldModel()->SetHeightAdaptivePolicy(static_cast<TextHeightAdaptivePolicy>(value));
}

void FfiOHOSAceFrameworkTextFieldSetMaxFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    GetTextFieldModel()->SetAdaptMaxFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldSetMinFontSize(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size = Dimension();
    }

    GetTextFieldModel()->SetAdaptMinFontSize(size);
}

void FfiOHOSAceFrameworkTextFieldSetSelectedBackgroundColor(uint32_t value)
{
    GetTextFieldModel()->SetSelectedBackgroundColor(Color(value));
}

void FfiOHOSAceFrameworkTextFieldSetCaretStyle(double value, int32_t unit, uint32_t color)
{
    CaretStyle caretStyle;
    caretStyle.caretWidth = Dimension(value, (DimensionUnit)unit);

    GetTextFieldModel()->SetCaretStyle(caretStyle);
    GetTextFieldModel()->SetCaretColor(Color(color));
}

void FfiOHOSAceFrameworkTextFieldSetTextIndent(double value, int32_t unit)
{
    Dimension size(value, static_cast<DimensionUnit>(unit));
    if (size.IsNegative()) {
        size.SetValue(0.0);
    }

    GetTextFieldModel()->SetTextIndent(size);
}

void FfiOHOSAceFrameworkTextFieldSetTextOverflow(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        value = 0;
    }
    GetTextFieldModel()->SetTextOverflow(TEXT_OVERFLOWS[value]);
}

void FfiOHOSAceFrameworkTextFieldSetEnablePreviewText(bool value)
{
    GetTextFieldModel()->SetEnablePreviewText(value);
}

void FfiOHOSAceFrameworkTextFieldSetStyle(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(InputStyle::INLINE)) {
        value = static_cast<int32_t>(InputStyle::DEFAULT);
    }
    GetTextFieldModel()->SetInputStyle(static_cast<InputStyle>(value));
}

void FfiOHOSAceFrameworkTextFieldSetBarState(int32_t value)
{
    GetTextFieldModel()->SetBarState(static_cast<DisplayMode>(value));
}

void FfiOHOSAceFrameworkTextFieldSetSelectionMenuHidden(bool value)
{
    GetTextFieldModel()->SetSelectionMenuHidden(value);
}

void FfiOHOSAceFrameworkTextFieldSetShowCounter(bool value, int32_t threshold, bool showBorder)
{
    GetTextFieldModel()->SetShowCounterBorder(showBorder);
    if (threshold >= static_cast<int32_t>(MINI_VAILD_VALUE) && threshold <= static_cast<int32_t>(MAX_VAILD_VALUE)) {
        GetTextFieldModel()->SetShowCounter(value);
        GetTextFieldModel()->SetCounterType(threshold);
    } else {
        GetTextFieldModel()->SetShowCounter(false);
        GetTextFieldModel()->SetCounterType(ILLEGAL_VALUE);
    }
}

void FfiOHOSAceFrameworkTextFieldSetMaxLines(int32_t value)
{
    if (value <= 0) {
        value = DEFAULTMAXLINES;
    }
    GetTextFieldModel()->SetMaxViewLines(static_cast<uint32_t>(value));
}

void FfiOHOSAceFrameworkTextFieldSetEnableKeyboardOnFocus(bool value)
{
    GetTextFieldModel()->RequestKeyboardOnFocus(value);
}

void FfiOHOSAceFrameworkTextFieldSetContentType(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(NG::TextContentType::END)) {
        value = static_cast<int32_t>(NG::TextContentType::UNSPECIFIED);
    }
    GetTextFieldModel()->SetContentType(static_cast<NG::TextContentType>(value));
}

void FfiOHOSAceFrameworkTextFieldSetEnableAutoFill(bool value)
{
    GetTextFieldModel()->SetEnableAutoFill(value);
}

void FfiOHOSAceFrameworkTextFieldSetTextAreaType(int32_t value)
{
    if (value < 0 || value > static_cast<int32_t>(TextInputType::END)) {
        value = static_cast<int32_t>(TextInputType::UNSPECIFIED);
    }
    GetTextFieldModel()->SetType(static_cast<TextInputType>(value));
}

void FfiOHOSAceFrameworkTextFieldSetCopyOption(int32_t value)
{
    GetTextFieldModel()->SetCopyOption(static_cast<CopyOptions>(value));
}

void FfiOHOSAceFrameworkTextFieldSetCustomKeyboard(void (*callback)(), bool options)
{
    auto builderFunc = CJLambda::Create(callback);
    GetTextFieldModel()->SetCustomKeyboard(std::move(builderFunc), options);
}

void FfiOHOSAceFrameworkTextFieldOnSecurityStateChange(void (*callback)(bool value))
{
    GetTextFieldModel()->SetOnSecurityStateChange(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkTextFieldShowUnit(void (*callback)())
{
    auto unitFunc = CJLambda::Create(callback);
    GetTextFieldModel()->SetShowUnit(std::move(unitFunc));
}

void FfiOHOSAceFrameworkTextFieldSetPasswordRules(const char* rules)
{
    if (rules == nullptr) {
        return;
    }
    GetTextFieldModel()->SetPasswordRules(rules);
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

    GetTextFieldModel()->SetShowError(UtfUtils::Str8DebugToStr16(error), isVisible);
}

void FfiOHOSAceFrameworkTextFieldSetShowPasswordIcon(bool isShow)
{
    GetTextFieldModel()->SetShowPasswordIcon(isShow);
}

void FfiOHOSAceFrameworkTextFieldShowPasswordText(bool show)
{
    GetTextFieldModel()->SetShowPasswordText(show);
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

    GetTextFieldModel()->SetPasswordIcon(passwordIcon);
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

    GetTextFieldModel()->SetCaretPosition(caretPosition);
}

void FfiOHOSAceFrameworkTextFieldSetSelectAllValue(bool value)
{
    GetTextFieldModel()->SetSelectAllValue(value);
}

void FfiOHOSAceFrameworkTextFieldSetShowUnderline(bool show)
{
    GetTextFieldModel()->SetShowUnderline(show);
}

void FfiOHOSAceFrameworkTextFieldNormalUnderlineColor(uint32_t color)
{
    GetTextFieldModel()->SetNormalUnderlineColor(Color(color));
}

void FfiOHOSAceFrameworkTextFieldUserUnderlineColor(uint32_t typing, uint32_t normal, uint32_t error, uint32_t disable)
{
    UserUnderlineColor userColor = UserUnderlineColor();
    userColor.typing = Color(typing);
    userColor.normal = Color(normal);
    userColor.error = Color(error);
    userColor.disable = Color(disable);
    GetTextFieldModel()->SetUserUnderlineColor(userColor);
}

void FfiOHOSAceFrameworkTextFieldCancelButton(int32_t style, double size, int32_t unit, uint32_t color, const char* src)
{
    // set style
    if (style < 0) {
        GetTextFieldModel()->SetCleanNodeStyle(CleanNodeStyle::INPUT);
    } else {
        GetTextFieldModel()->SetCleanNodeStyle(static_cast<CleanNodeStyle>(style));
    }
    GetTextFieldModel()->SetIsShowCancelButton(true);
    // set normal
    if (src == nullptr) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        if (Container::CurrentColorMode() == ColorMode::DARK) {
            GetTextFieldModel()->SetCancelIconColor(theme->GetCancelButtonIconColor());
        } else {
            GetTextFieldModel()->SetCancelIconColor(Color());
        }
        GetTextFieldModel()->SetCancelIconSize(theme->GetCancelIconSize());
        GetTextFieldModel()->SetCanacelIconSrc(std::string(), std::string(), std::string());
        return;
    }
    // set size
    CalcDimension iconSize(size, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        iconSize = theme->GetCancelIconSize();
    }
    GetTextFieldModel()->SetCancelIconSize(iconSize);
    // set color
    Color iconColor(color);
    if (Container::CurrentColorMode() == ColorMode::DARK) {
        auto theme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        GetTextFieldModel()->SetCancelIconColor(theme->GetCancelButtonIconColor());
    } else {
        GetTextFieldModel()->SetCancelIconColor(iconColor);
    }
    // set src
    std::string iconSrc(src);
    GetTextFieldModel()->SetCanacelIconSrc(iconSrc, std::string(), std::string());
}

void FfiOHOSAceFrameworkTextFieldOnSubmit(void (*callback)(int32_t value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto task = [func = CJLambda::Create(callback), node = targetNode](int32_t key, NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        func(key);
    };
    GetTextFieldModel()->SetOnSubmit(task);
}

void FfiOHOSAceFrameworkTextFieldOnChange(void (*callback)(const char* value))
{
    auto onChange = [func = FormatCharFunction(callback)](
        const ChangeValueInfo& info) { func(info.value); };
    GetTextFieldModel()->SetOnChange(onChange);
}

void FfiOHOSAceFrameworkTextFieldOnCopy(void (*callback)(const char* value))
{
    GetTextFieldModel()->SetOnCopy(FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldOnCut(void (*callback)(const char* value))
{
    GetTextFieldModel()->SetOnCut(FormatCharFunction(callback));
}

void FfiOHOSAceFrameworkTextFieldOnPaste(void (*callback)(const char* value))
{
    auto onPaste = [func = FormatCharFunction(callback)](
        const std::u16string& val, NG::TextCommonEvent& info) { func(val); };
    GetTextFieldModel()->SetOnPasteWithEvent(std::move(onPaste));
}

void FfiOHOSAceFrameworkTextFieldOnEditChanged(void (*callback)(bool value))
{
    GetTextFieldModel()->SetOnEditChanged(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkTextFieldOnContentScroll(void (*callback)(float totalOffsetX, float totalOffsetY))
{
    auto onScroll = [lambda = CJLambda::Create(callback)](
                        float totalOffsetX, float totalOffsetY) -> void { lambda(totalOffsetX, totalOffsetY); };
    GetTextFieldModel()->SetOnContentScroll(onScroll);
}

void FfiOHOSAceFrameworkTextFieldOnTextSelectionChange(void (*callback)(int32_t selectionStart, int32_t selectionEnd))
{
    auto onTextSelectionChange = [lambda = CJLambda::Create(callback)](int32_t selectionStart,
                                     int32_t selectionEnd) -> void { lambda(selectionStart, selectionEnd); };
    GetTextFieldModel()->SetOnTextSelectionChange(onTextSelectionChange);
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
    GetTextFieldModel()->SetOnDidDeleteEvent(onDidDelete);
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
    GetTextFieldModel()->SetOnWillDeleteEvent(onWillDelete);
}

void FfiOHOSAceFrameworkTextFieldOnDidInsert(void (*callback)(double insertOffset, const char* insertValue))
{
    auto onDidInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> void {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        lambda(insertOffset, insertValue);
    };
    GetTextFieldModel()->SetOnDidInsertValueEvent(onDidInsert);
}

void FfiOHOSAceFrameworkTextFieldOnWillInsert(bool (*callback)(double insertOffset, const char* insertValue))
{
    auto onWillInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> bool {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        return lambda(insertOffset, insertValue);
    };
    GetTextFieldModel()->SetOnWillInsertValueEvent(onWillInsert);
}

void FfiOHOSAceFrameworkTextFieldOnChangePreviewText(
    void (*callback)(const char* value, int32_t offset, const char* text))
{
    auto onChange = [func = CJLambda::Create(callback)](const ChangeValueInfo& info) {
        const std::string valStr = UtfUtils::Str16ToStr8(info.value);
        const std::string previewTextStr = UtfUtils::Str16ToStr8(info.previewText.value);
        func(valStr.c_str(), info.previewText.offset, previewTextStr.c_str());
    };
    GetTextFieldModel()->SetOnChange(onChange);
}

void FfiOHOSAceFrameworkTextFieldOnSubmitWithEvent(bool (*callback)(int32_t value, CJSubmitEvent))
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
    GetTextFieldModel()->SetOnSubmit(task);
}

void FfiOHOSAceFrameworkTextFieldEditMenuOptions(CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    ViewAbstract::ParseEditMenuOptions(cjOnCreateMenu, cjOnMenuItemClick, onCreateMenuCallback, onMenuItemClick);
    GetTextFieldModel()->SetSelectionMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), nullptr);
}
}
