/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");q
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_search_ffi.h"

#include <optional>
#include <string>

#include "cj_lambda.h"

#include "base/utils/utf_helper.h"
#include "bridge/cj_frontend/cppview/search_controller.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/search/search_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FontStyle> FONT_STYLE = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<CopyOptions> COPY_OPTION = {
    CopyOptions::None,
    CopyOptions::InApp,
    CopyOptions::Local,
    CopyOptions::Distributed,
};

const std::vector<TextDecoration> TEXT_DECORATIONS = { TextDecoration::NONE, TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE, TextDecoration::LINE_THROUGH };

const std::vector<TextDecorationStyle> TEXT_DECORATION_STYLES = { TextDecorationStyle::SOLID,
    TextDecorationStyle::DOUBLE, TextDecorationStyle::DOTTED, TextDecorationStyle::DASHED, TextDecorationStyle::WAVY };

const std::vector<TextInputAction> TEXT_INPUT_ACTIONS = { TextInputAction::UNSPECIFIED, TextInputAction::NONE,
    TextInputAction::GO, TextInputAction::SEARCH, TextInputAction::SEND, TextInputAction::NEXT, TextInputAction::DONE,
    TextInputAction::PREVIOUS, TextInputAction::NEW_LINE };

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };

void handleFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily, Font& font)
{
    Dimension fontSizeDim(fontSize, static_cast<DimensionUnit>(sizeUnit));
    font.fontSize = fontSizeDim;
    font.fontWeight = ConvertStrToFontWeight(fontWeight);
    font.fontFamilies = ConvertStrToFontFamilies(fontFamily);
    font.fontStyle = FONT_STYLE[fontStyle];
}

std::optional<std::u16string> OptionalStr8ToStr16(const std::optional<std::string> optStr)
{
    if (optStr.has_value()) {
        return UtfUtils::Str8DebugToStr16(optStr.value());
    }
    return std::nullopt;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSearchCreateByIconID(SearchCreateParam value)
{
    std::string iconUrl = "";
    std::optional<std::string> key = value.value;
    std::optional<std::string> tip = value.placeholder;
    std::optional<std::string> src = iconUrl;
    if (!ParseCjMedia(value.iconID, static_cast<ResourceType>(value.iconType), value.iconParams, iconUrl)) {
        LOGI("icon url not found");
    }
    if (value.controllerID == -1) {
        SearchModel::GetInstance()->Create(OptionalStr8ToStr16(key), OptionalStr8ToStr16(tip), src);
    } else {
        auto self_ = FFIData::GetData<SearchController>(value.controllerID);
        if (self_ != nullptr) {
            auto controller =
                SearchModel::GetInstance()->Create(OptionalStr8ToStr16(key), OptionalStr8ToStr16(tip), src);
            self_->SetController(controller);
        } else {
            LOGE("invalid scrollerID");
        }
    }
    std::string bundleName;
    std::string moduleName;
    SearchModel::GetInstance()->SetSearchSrcPath(iconUrl, bundleName, moduleName);
}

void FfiOHOSAceFrameworkSearchCreateByIconRes(
    const char* value, const char* placeholder, const char* iconUrl, int64_t controllerId)
{
    std::optional<std::string> key = value;
    std::optional<std::string> tip = placeholder;
    std::optional<std::string> src = iconUrl;
    if (controllerId == -1) {
        SearchModel::GetInstance()->Create(OptionalStr8ToStr16(key), OptionalStr8ToStr16(tip), src);
    } else {
        auto nativeController = FFIData::GetData<SearchController>(controllerId);
        if (nativeController != nullptr) {
            auto controller =
                SearchModel::GetInstance()->Create(OptionalStr8ToStr16(key), OptionalStr8ToStr16(tip), src);
            nativeController->SetController(controller);
        } else {
            LOGE("Invalid controller id.");
        }
    }
}

void FfiOHOSAceFrameworkSearchSetSearchButton(const char* text)
{
    SearchModel::GetInstance()->SetSearchButton(text);
}

void FfiOHOSAceFrameworkSearchSetPlaceholderColor(uint32_t color)
{
    SearchModel::GetInstance()->SetPlaceholderColor(Color(color));
}

void FfiOHOSAceFrameworkSearchSetPlaceholderFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLE.size())) {
        LOGE("invalid value for fontStyle");
        return;
    }
    Font font;
    handleFont(fontSize, sizeUnit, fontWeight, fontStyle, fontFamily, font);
    SearchModel::GetInstance()->SetPlaceholderFont(font);
}

void FfiOHOSAceFrameworkSearchSetTextFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLE.size())) {
        LOGE("invalid value for fontStyle");
        return;
    }
    Font font;
    handleFont(fontSize, sizeUnit, fontWeight, fontStyle, fontFamily, font);
    SearchModel::GetInstance()->SetTextFont(font);
}

void FfiOHOSAceFrameworkSearchSetBorder(SearchSetBorder value)
{
    if (!Utils::CheckParamsValid(value.style, BORDER_STYLES.size())) {
        LOGE("invalid value for style");
        return;
    }
    FfiOHOSAceFrameworkViewAbstractSetBorder(
        CJBorder({ value.width, value.widthUnit, value.color, value.radius, value.radiusUnit, value.style }));
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderWidth(double width, int32_t widthUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidth(width, widthUnit);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderColor(uint32_t color)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderColor(color);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for style");
        return;
    }
    FfiOHOSAceFrameworkViewAbstractSetBorderStyle(style);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderRadius(double radius, int32_t radiusUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderRadius(radius, radiusUnit);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetHeight(double height, int32_t heightUnit)
{
    Dimension heightDim(height, static_cast<DimensionUnit>(heightUnit));
    NG::ViewAbstract::SetHeight(NG::CalcLength(heightDim));
    if (LessNotEqual(heightDim.Value(), 0.0)) {
        heightDim.SetValue(0.0);
    }
    SearchModel::GetInstance()->SetHeight(heightDim);
}

void FfiOHOSAceFrameworkSearchSetCopyOption(int32_t copyOption)
{
    if (!Utils::CheckParamsValid(copyOption, COPY_OPTION.size())) {
        LOGE("invalid value for style");
        return;
    }
    SearchModel::GetInstance()->SetCopyOption(COPY_OPTION[copyOption]);
}

void FfiOHOSAceFrameworkSearchOnSubmit(void (*callback)(const char* value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto task = [func = CJLambda::Create(callback), node = targetNode](
                    const std::u16string& value, NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        std::string utf8String = convert.to_bytes(value);
        func(utf8String.c_str());
    };
    SearchModel::GetInstance()->SetOnSubmit(std::move(task));
}

void FfiOHOSAceFrameworkSearchOnChange(void (*callback)(const char* value))
{
    auto onChange = [lambda = CJLambda::Create(callback)]
        (const ChangeValueInfo& info) -> void {
        const std::string valueStr = UtfUtils::Str16DebugToStr8(info.value);
        lambda(valueStr.c_str());
    };
    SearchModel::GetInstance()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkSearchOnCopy(void (*callback)(const char* value))
{
    auto onCopy = [lambda = CJLambda::Create(callback)](const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16DebugToStr8(value);
        lambda(valueStr.c_str());
    };
    SearchModel::GetInstance()->SetOnCopy(std::move(onCopy));
}

void FfiOHOSAceFrameworkSearchOnCut(void (*callback)(const char* value))
{
    auto onCut = [lambda = CJLambda::Create(callback)](const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16DebugToStr8(value);
        lambda(valueStr.c_str());
    };
    SearchModel::GetInstance()->SetOnCut(std::move(onCut));
}

void FfiOHOSAceFrameworkSearchOnPaste(void (*callback)(const char* value))
{
    auto onPaste = [lambda = CJLambda::Create(callback)](const std::u16string& val, NG::TextCommonEvent& info) -> void {
        LOGI("OnPaste called.");
        const std::string valStr = UtfUtils::Str16DebugToStr8(val);
        lambda(valStr.c_str());
    };
    SearchModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
}

int64_t FfiOHOSAceFrameworkSearchController()
{
    auto ret_ = FFIData::Create<SearchController>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkSearchCaretPosition(int64_t selfID, int32_t carePosition)
{
    auto self_ = FFIData::GetData<SearchController>(selfID);
    if (self_ != nullptr) {
        self_->CaretPosition(carePosition);
    } else {
        LOGE("invalid SearchControllerID");
    }
}

void FfiOHOSAceFrameworkSearchSetMaxFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetAdaptMaxFontSize(dimValue);
}

void FfiOHOSAceFrameworkSearchSetMinFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetAdaptMinFontSize(dimValue);
}

void FfiOHOSAceFrameworkSearchSetFontFeature(const char* fontFeature)
{
    std::string fontFeatureSettings = fontFeature;
    SearchModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

void FfiOHOSAceFrameworkSearchSetLineHeight(double lineHeight, int32_t unit)
{
    Dimension dimValue(lineHeight, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetLineHeight(dimValue);
}

void FfiOHOSAceFrameworkSearchSetLetterSpacing(double space, int32_t unit)
{
    Dimension value(space, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetLetterSpacing(value);
}

void FfiOHOSAceFrameworkSearchSetDecoration(int32_t type, uint32_t color, int32_t style)
{
    if (!Utils::CheckParamsValid(type, TEXT_DECORATIONS.size()) ||
        !Utils::CheckParamsValid(style, TEXT_DECORATION_STYLES.size())) {
        LOGE("invalid value for searchDirection");
        return;
    }
    SearchModel::GetInstance()->SetTextDecoration(TEXT_DECORATIONS[type]);
    SearchModel::GetInstance()->SetTextDecorationColor(Color(color));
    SearchModel::GetInstance()->SetTextDecorationStyle(TEXT_DECORATION_STYLES[style]);
}

void FfiOHOSAceFrameworkSearchSetEnterKeyType(int32_t type)
{
    if (!Utils::CheckParamsValid(type, TEXT_INPUT_ACTIONS.size())) {
        LOGE("invalid value for text input action");
        return;
    }
    SearchModel::GetInstance()->SetSearchEnterKeyType(TEXT_INPUT_ACTIONS[type]);
}

void FfiOHOSAceFrameworkSearchSetSelectedBackgroundColor(uint32_t color)
{
    SearchModel::GetInstance()->SetSelectedBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkSearchSetTextIndent(double value, int32_t unit)
{
    Dimension dimValue(value, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetTextIndent(dimValue);
}

void FfiOHOSAceFrameworkSearchStopEditing(int64_t selfID)
{
    auto self_ = FFIData::GetData<SearchController>(selfID);
    if (self_ != nullptr) {
        self_->StopEditing();
    } else {
        LOGE("invalid SearchControllerID");
    }
}

void FfiOHOSAceFrameworkSearchSetTextSelection(
    int64_t selfID, int32_t selectionStart, int32_t selectionEnd, int32_t option)
{
    auto self_ = FFIData::GetData<SearchController>(selfID);
    SelectionOptions options;
    options.menuPolicy = static_cast<MenuPolicy>(option);
    if (self_ != nullptr) {
        self_->SetTextSelection(selectionStart, selectionEnd, options);
    } else {
        LOGE("invalid SearchControllerID");
    }
}

void FfiOHOSAceFrameworkSearchSetCancelButton(
    int32_t style, double value, int32_t unit, uint32_t color, const char* src)
{
    Dimension iconSize(value, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetCancelButtonStyle(static_cast<CancelButtonStyle>(style));
    NG::IconOptions cancelIconOptions = NG::IconOptions(Color(color), iconSize, std::string(src), "", "");
    SearchModel::GetInstance()->SetCancelImageIcon(cancelIconOptions);
}

void FfiOHOSAceFrameworkSearchSetSearchIcon(double value, int32_t unit, uint32_t color, const char* src)
{
    Dimension iconSize(value, static_cast<DimensionUnit>(unit));
    NG::IconOptions searchIcon = NG::IconOptions(Color(color), iconSize, std::string(src), "", "");
    SearchModel::GetInstance()->SetSearchImageIcon(searchIcon);
}

void FfiOHOSAceFrameworkSearchSetEnablePreviewText(bool enablePreviewText)
{
    SearchModel::GetInstance()->SetEnablePreviewText(enablePreviewText);
}

void FfiOHOSAceFrameworkSearchSetType(int32_t value)
{
    TextInputType textInputType;
    if (value < static_cast<int32_t>(TextInputType::BEGIN) || value > static_cast<int32_t>(TextInputType::END)) {
        textInputType = TextInputType::TEXT;
    } else if (value == static_cast<int32_t>(TextInputType::JS_ENUM_URL)) {
        textInputType = TextInputType::URL;
    } else {
        textInputType = static_cast<TextInputType>(value);
    }
    SearchModel::GetInstance()->SetType(textInputType);
}

void FfiOHOSAceFrameworkSearchSetMaxLength(uint32_t maxLength)
{
    if (GreatOrEqual(maxLength, 0)) {
        SearchModel::GetInstance()->SetMaxLength(maxLength);
    } else {
        SearchModel::GetInstance()->ResetMaxLength();
    }
}

void FfiOHOSAceFrameworkSearchSetSelectionMenuHidden(bool value)
{
    SearchModel::GetInstance()->SetSelectionMenuHidden(value);
}

void FfiOHOSAceFrameworkSearchSetEnableKeyboardOnFocus(bool value)
{
    SearchModel::GetInstance()->RequestKeyboardOnFocus(value);
}

void FfiOHOSAceFrameworkSearchSetCaretStyle(double value, int32_t unit, uint32_t color)
{
    CalcDimension caretWidth(value, static_cast<DimensionUnit>(unit));
    SearchModel::GetInstance()->SetCaretWidth(caretWidth);
    SearchModel::GetInstance()->SetCaretColor(Color(color));
}

void FfiOHOSAceFrameworkSearchSetTextAlign(int32_t value)
{
    if (!Utils::CheckParamsValid(value, TEXT_ALIGNS.size())) {
        LOGE("invalid value for set text align");
        return;
    }
    SearchModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
}

void FfiOHOSAceFrameworkSearchSetFontColor(uint32_t color)
{
    SearchModel::GetInstance()->SetTextColor(Color(color));
}

void FfiOHOSAceFrameworkSearchOnDidInsert(void (*callback)(double insertOffset, const char* insertValue))
{
    auto onDidInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> void {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        lambda(insertOffset, insertValue);
    };
    SearchModel::GetInstance()->SetOnDidInsertValueEvent(onDidInsert);
}

void FfiOHOSAceFrameworkSearchOnDidDelete(
    void (*callback)(double deleteOffset, int32_t direction, const char* deleteValue))
{
    auto onDidDelete = [lambda = CJLambda::Create(callback)](const DeleteValueInfo& Info) -> void {
        double deleteOffset = Info.deleteOffset;
        int32_t direction = static_cast<int32_t>(Info.direction);
        const std::string deleteStr = UtfUtils::Str16ToStr8(Info.deleteValue);
        const char* deleteValue = deleteStr.c_str();
        lambda(deleteOffset, direction, deleteValue);
    };
    SearchModel::GetInstance()->SetOnDidDeleteEvent(onDidDelete);
}

void FfiOHOSAceFrameworkSearchOnWillInsert(bool (*callback)(double insertOffset, const char* insertValue))
{
    auto onWillInsert = [lambda = CJLambda::Create(callback)](const InsertValueInfo& Info) -> bool {
        double insertOffset = Info.insertOffset;
        const std::string insertStr = UtfUtils::Str16ToStr8(Info.insertValue);
        const char* insertValue = insertStr.c_str();
        return lambda(insertOffset, insertValue);
    };
    SearchModel::GetInstance()->SetOnWillInsertValueEvent(onWillInsert);
}

void FfiOHOSAceFrameworkSearchOnWillDelete(
    bool (*callback)(double deleteOffset, int32_t direction, const char* deleteValue))
{
    auto onWillDelete = [lambda = CJLambda::Create(callback)](const DeleteValueInfo& Info) -> bool {
        double deleteOffset = Info.deleteOffset;
        int32_t direction = static_cast<int32_t>(Info.direction);
        const std::string deleteStr = UtfUtils::Str16ToStr8(Info.deleteValue);
        const char* deleteValue = deleteStr.c_str();
        return lambda(deleteOffset, direction, deleteValue);
    };
    SearchModel::GetInstance()->SetOnWillDeleteEvent(onWillDelete);
}

void FfiOHOSAceFrameworkSearchOnContentScroll(void (*callback)(float totalOffsetX, float totalOffsetY))
{
    auto onScroll = [lambda = CJLambda::Create(callback)](
                        float totalOffsetX, float totalOffsetY) -> void { lambda(totalOffsetX, totalOffsetY); };
    SearchModel::GetInstance()->SetOnScroll(onScroll);
}

void FfiOHOSAceFrameworkSearchOnTextSelectionChange(void (*callback)(int32_t selectionStart, int32_t selectionEnd))
{
    auto onTextSelectionChange = [lambda = CJLambda::Create(callback)](int32_t selectionStart,
                                     int32_t selectionEnd) -> void { lambda(selectionStart, selectionEnd); };
    SearchModel::GetInstance()->SetOnTextSelectionChange(onTextSelectionChange);
}

void FfiOHOSAceFrameworkSearchOnEditChange(void (*callback)(bool value))
{
    SearchModel::GetInstance()->SetOnEditChanged(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkSearchSetInputFilter(const char* value, void (*callback)(const char* value))
{
    auto inputFilter = [lambda = CJLambda::Create(callback)](const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16ToStr8(value);
        lambda(valueStr.c_str());
    };
    SearchModel::GetInstance()->SetInputFilter(value, inputFilter);
}

void FfiOHOSAceFrameworkSearchSetCustomKeyboard(void (*callback)(), bool options)
{
    auto builderFunc = CJLambda::Create(callback);
    SearchModel::GetInstance()->SetCustomKeyboard(std::move(builderFunc), options);
}

void FfiOHOSAceFrameworkSearchEditMenuOptions(CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    ViewAbstract::ParseEditMenuOptions(cjOnCreateMenu, cjOnMenuItemClick, onCreateMenuCallback, onMenuItemClick);
    SearchModel::GetInstance()->SetSelectionMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

SearchTextMenuItemHandle FfiOHOSAceFrameworkSearchCreateTextMenuItem(int64_t size)
{
    LOGI("Create FFiSearchTextMenuItem Vector");
    return new std::vector<FFiSearchTextMenuItem>(size);
}

void FfiOHOSAceFrameworkSearchTextMenuItemDelete(SearchTextMenuItemHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<FFiSearchTextMenuItem>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkSearchTextMenuItemSetElement(
    SearchTextMenuItemHandle vec, int64_t index, FFiSearchTextMenuItem textMenuItem)
{
    LOGI("FFiSearchTextMenuItem Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<FFiSearchTextMenuItem>*>(vec);
    (*actualVec)[index] = textMenuItem;
    LOGI("FFiSearchTextMenuItem Vector Set Element Success");
}

FFiSearchTextMenuItem FfiOHOSAceFrameworkSearchTextMenuItemGetElement(SearchTextMenuItemHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<FFiSearchTextMenuItem>*>(vec);
    return (*actualVec)[index];
}

int64_t FfiOHOSAceFrameworkSearchTextMenuItemGetSize(SearchTextMenuItemHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<FFiSearchTextMenuItem>*>(vec);
    return (*actualVec).size();
}

CJRectResult FfiOHOSAceFrameworkSearchGetTextContentRect(int64_t selfID)
{
    CJRectResult result;
    auto self = FFIData::GetData<SearchController>(selfID);
    if (self != nullptr) {
        result = self->GetTextContentRect();
    } else {
        LOGE("invalid SearchControllerID");
    }
    return result;
}

int32_t FfiOHOSAceFrameworkSearchGetTextContentLineCount(int64_t selfID)
{
    int32_t result = 0;
    auto self = FFIData::GetData<SearchController>(selfID);
    if (self != nullptr) {
        result = self->GetTextContentLinesNum();
    } else {
        LOGE("invalid SearchControllerID");
    }
    return result;
}

CJCaretOffset FfiOHOSAceFrameworkSearchGetCaretOffset(int64_t selfID)
{
    CJCaretOffset result;
    auto self = FFIData::GetData<SearchController>(selfID);
    if (self != nullptr) {
        result = self->GetCaretOffset();
    } else {
        LOGE("invalid SearchControllerID");
    }
    return result;
}
}
