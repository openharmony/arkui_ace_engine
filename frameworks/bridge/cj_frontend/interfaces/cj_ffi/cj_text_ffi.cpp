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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_ffi.h"

#include "cj_lambda.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/text/text_controller.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::FFI;

namespace {
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::vector<TextOverflow> TEXT_OVERFLOWS_NEW = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::LEFT,
    TextAlign::RIGHT, TextAlign::JUSTIFY };
const std::vector<TextDecoration> TEXT_DECORATIONS = { TextDecoration::NONE, TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE, TextDecoration::LINE_THROUGH };
const std::vector<WordBreak> WORD_BREAK = { WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD,
    WordBreak::HYPHENATION };
const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY = { LineBreakStrategy::GREEDY, LineBreakStrategy::HIGH_QUALITY,
    LineBreakStrategy::BALANCED };
const std::vector<CopyOptions> COPY_OPTIONS = { CopyOptions::None, CopyOptions::InApp, CopyOptions::Local };
const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE = { TextSelectableMode::SELECTABLE_UNFOCUSABLE,
    TextSelectableMode::SELECTABLE_FOCUSABLE, TextSelectableMode::UNSELECTABLE };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<EllipsisMode> ELLIPSIS_MODE = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL };
const std::vector<NG::TextSpanType> TEXT_SPAN_TYPE = { NG::TextSpanType::TEXT, NG::TextSpanType::IMAGE,
    NG::TextSpanType::MIXED };
const std::vector<NG::TextResponseType> TEXT_RESPONSE_TYPE = { NG::TextResponseType::RIGHT_CLICK,
    NG::TextResponseType::LONG_PRESS, NG::TextResponseType::SELECTED_BY_MOUSE };
const std::vector<TextDecorationStyle> TEXT_DECORATIONS_STYLE = { TextDecorationStyle::SOLID,
    TextDecorationStyle::DOUBLE, TextDecorationStyle::DOTTED, TextDecorationStyle::DASHED, TextDecorationStyle::WAVY };
} // namespace

namespace OHOS::Ace::Framework {

NGNativeTextController::NGNativeTextController() : FFIData()
{
    LOGI("Native TextController constructed: %{public}" PRId64, GetID());
}

void NGNativeTextController::CloseSelectionMenu()
{
    if (controller_) {
        controller_->CloseSelectionMenu();
    }
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTextCreate(const char* content)
{
    TextModel::GetInstance()->Create(content);
}

void FfiOHOSAceFrameworkTextCreateWithController(const char* content, int64_t controllerId)
{
    auto controller = FFIData::GetData<NGNativeTextController>(controllerId);
    if (controller == nullptr) {
        LOGE("FfiText invalid controllerId");
        return;
    }
    TextModel::GetInstance()->Create(content);
    auto nativeController = TextModel::GetInstance()->GetTextController();
    if (controller) {
        controller->SetController(nativeController);
    }
}

void FfiOHOSAceFrameworkTextSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetWidth(value);
    TextModel::GetInstance()->OnSetWidth();
}

void FfiOHOSAceFrameworkTextSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetHeight(value);
    TextModel::GetInstance()->OnSetHeight();
}

void FfiOHOSAceFrameworkTextSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetFontSize(value);
}

void FfiOHOSAceFrameworkTextSetFontWeight(const char* fontWeight)
{
    TextModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkTextSetFontColor(uint32_t textColor)
{
    TextModel::GetInstance()->SetTextColor(Color(textColor));
}

void FfiOHOSAceFrameworkTextSetTextOverflow(int32_t overflow)
{
    if (!Utils::CheckParamsValid(overflow, TEXT_OVERFLOWS.size())) {
        LOGE("invalid value for over flow");
        return;
    }
    TextModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[overflow]);
}

void FfiOHOSAceFrameworkTextSetTextOverflowNew(int32_t overflow)
{
    if (!Utils::CheckParamsValid(overflow, TEXT_OVERFLOWS_NEW.size())) {
        LOGE("invalid value for over flow");
        return;
    }
    TextModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS_NEW[overflow]);
}

void FfiOHOSAceFrameworkTextSetMaxLines(int32_t maxLines)
{
    TextModel::GetInstance()->SetMaxLines(maxLines);
}

void FfiOHOSAceFrameworkTextSetFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    TextModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkTextSetTextAlign(int32_t textAlign)
{
    if (!Utils::CheckParamsValid(textAlign, TEXT_ALIGNS.size())) {
        LOGE("invalid value for text align");
        return;
    }
    TextModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[textAlign]);
}

void FfiOHOSAceFrameworkTextSetLineHeight(double lineHeight, int32_t unit)
{
    Dimension dimValue(lineHeight, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetLineHeight(dimValue);
}

void FfiOHOSAceFrameworkTextSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    TextModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkTextSetDecoration(int32_t typeValue, uint32_t colorValue)
{
    if (!Utils::CheckParamsValid(typeValue, TEXT_DECORATIONS.size())) {
        LOGE("invalid value for text decoration");
        return;
    }
    TextModel::GetInstance()->SetTextDecoration(TEXT_DECORATIONS[typeValue]);
    TextModel::GetInstance()->SetTextDecorationColor(Color(colorValue));
}

void FfiOHOSAceFrameworkTextSetDecorationNew(int32_t typeValue, uint32_t colorValue, int32_t styleValue)
{
    if (!Utils::CheckParamsValid(typeValue, TEXT_DECORATIONS.size())) {
        LOGE("invalid value for text decoration type");
        return;
    }
    if (!Utils::CheckParamsValid(styleValue, TEXT_DECORATIONS_STYLE.size())) {
        LOGE("invalid value for text decoration style");
        return;
    }
    TextModel::GetInstance()->SetTextDecoration(TEXT_DECORATIONS[typeValue]);
    TextModel::GetInstance()->SetTextDecorationColor(Color(colorValue));
    TextModel::GetInstance()->SetTextDecorationStyle(TEXT_DECORATIONS_STYLE[styleValue]);
}

void FfiOHOSAceFrameworkTextSetMinFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetAdaptMinFontSize(dimValue);
}

void FfiOHOSAceFrameworkTextSetMaxFontSize(double fontSize, int32_t unit)
{
    Dimension dimValue(fontSize, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetAdaptMaxFontSize(dimValue);
}

void FfiOHOSAceFrameworkTextSetTextCase(int32_t textCase)
{
    if (!Utils::CheckParamsValid(textCase, TEXT_CASES.size())) {
        LOGE("invalid value for text case");
        return;
    }
    TextModel::GetInstance()->SetTextCase(TEXT_CASES[textCase]);
}

void FfiOHOSAceFrameworkTextSetBaselineOffset(double baseLine, int32_t unit)
{
    Dimension dimValue(baseLine, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetBaselineOffset(dimValue);
}

void FfiOHOSAceFrameworkTextOnClick(void (*callback)(CJClickInfo clickInfo)) {}

void FfiTextSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
    TextModel::GetInstance()->SetResponseRegion(true);
}

void FfiTextSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
    TextModel::GetInstance()->SetResponseRegion(true);
}

void FfiOHOSAceFrameworkTextSetFont(
    double fontSize, int32_t unit, const char* fontWeight, const char* fontFamily, int32_t fontStyle)
{
    Font font;
    font.fontSize = Dimension(fontSize, static_cast<DimensionUnit>(unit));
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    font.fontStyle = FONT_STYLES[fontStyle];
    font.fontWeight = ConvertStrToFontWeight(fontWeight);
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    font.fontFamilies = fontFamilies;
    TextModel::GetInstance()->SetFont(font);
}

VectorNativeShadowOptionsHandle FFICJCreateVectorNativeShadowOptions(int64_t size)
{
    return new std::vector<NativeShadowOptions>(size);
}

void FFICJVectorNativeShadowOptionsDelete(VectorNativeShadowOptionsHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeShadowOptions>*>(vec);
    delete actualVec;
}

void FFICJVectorNativeShadowOptionsSetElement(
    VectorNativeShadowOptionsHandle vec, int64_t index, NativeShadowOptions shadowOptions)
{
    auto actualVec = reinterpret_cast<std::vector<NativeShadowOptions>*>(vec);
    (*actualVec)[index] = shadowOptions;
}

void FfiOHOSAceFrameworkTextShadow(VectorStringPtr vecContent)
{
    auto nativeShadowOptionsVec = *reinterpret_cast<std::vector<NativeShadowOptions>*>(vecContent);
    std::vector<Shadow> params(nativeShadowOptionsVec.size());
    for (size_t i = 0; i < nativeShadowOptionsVec.size(); i++) {
        Shadow shadow;
        shadow.SetBlurRadius(nativeShadowOptionsVec[i].radius);
        if (nativeShadowOptionsVec[i].shadowType == 0) {
            shadow.SetShadowType(ShadowType::COLOR);
        } else {
            shadow.SetShadowType(ShadowType::BLUR);
        }
        shadow.SetColor(Color(nativeShadowOptionsVec[i].color));
        shadow.SetOffsetX(nativeShadowOptionsVec[i].offsetX);
        shadow.SetOffsetY(nativeShadowOptionsVec[i].offsetY);
        shadow.SetIsFilled(nativeShadowOptionsVec[i].fill);
        params.push_back(shadow);
    }
    TextModel::GetInstance()->SetTextShadow(params);
}

void FfiOHOSAceFrameworkTextSetDataDetectorConfig(VectorStringPtr vecContent, void (*callback)(const char* value),
    uint32_t entityColor, int32_t decorationType, uint32_t decorationColor, int32_t decorationStyle)
{
    auto actualVec = *reinterpret_cast<std::vector<std::string>*>(vecContent);
    std::string textTypes;
    for (size_t i = 0; i < actualVec.size(); i++) {
        if (i != 0) {
            textTypes.append(",");
        }
        textTypes.append(actualVec[i]);
    }
    auto onDetectResultUpdate = [lambda = CJLambda::Create(callback)](
                                    const std::string& value) -> void { lambda(value.c_str()); };
    if (!Utils::CheckParamsValid(decorationType, TEXT_DECORATIONS.size())) {
        LOGE("invalid value for text decoration type");
        return;
    }
    if (!Utils::CheckParamsValid(decorationStyle, TEXT_DECORATIONS_STYLE.size())) {
        LOGE("invalid value for text decoration style");
        return;
    }
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = textTypes;
    textDetectConfig.onResult = std::move(onDetectResultUpdate);
    textDetectConfig.entityColor = Color(entityColor);
    textDetectConfig.entityDecorationType = TEXT_DECORATIONS[decorationType];
    textDetectConfig.entityDecorationColor = Color(decorationColor);
    textDetectConfig.entityDecorationStyle = TEXT_DECORATIONS_STYLE[decorationStyle];
    TextModel::GetInstance()->SetTextDetectConfig(textDetectConfig);
}

void FfiOHOSAceFrameworkTextHalfLeading(bool value)
{
    TextModel::GetInstance()->SetHalfLeading(value);
}

void FfiOHOSAceFrameworkTextSetFontFeature(const char* fontFeature)
{
    std::string strValue = fontFeature;
    TextModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(strValue));
}

void FfiOHOSAceFrameworkTextSetLineBreakStrategy(int32_t lineBreakStrategy)
{
    if (!Utils::CheckParamsValid(lineBreakStrategy, LINE_BREAK_STRATEGY.size())) {
        LOGE("invalid value for line break strategy");
        return;
    }
    TextModel::GetInstance()->SetLineBreakStrategy(LINE_BREAK_STRATEGY[lineBreakStrategy]);
}

void FfiOHOSAceFrameworkTextSetLineSpacing(double lineSpacing, int32_t unit)
{
    Dimension dimValue(lineSpacing, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetLineSpacing(dimValue);
}

void FfiOHOSAceFrameworkTextSetCopyOption(int32_t copyOption)
{
    if (!Utils::CheckParamsValid(copyOption, COPY_OPTIONS.size())) {
        LOGE("invalid value for copy option");
        return;
    }
    TextModel::GetInstance()->SetCopyOption(COPY_OPTIONS[copyOption]);
}

void FfiOHOSAceFrameworkTextSetLetterSpacing(double letterSpacing, int32_t unit)
{
    Dimension dimValue(letterSpacing, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetLetterSpacing(dimValue);
}

void FfiOHOSAceFrameworkTextMaxFontScale(float maxFontScale)
{
    if (maxFontScale < 1.0f) {
        maxFontScale = 1.0f;
    }
    TextModel::GetInstance()->SetMaxFontScale(maxFontScale);
}

void FfiOHOSAceFrameworkTextMinFontScale(float minFontScale)
{
    if (minFontScale < 0.0f) {
        minFontScale = 0.0f;
    }
    if (minFontScale > 1.0f) {
        minFontScale = 1.0f;
    }
    TextModel::GetInstance()->SetMinFontScale(minFontScale);
}

void FfiOHOSAceFrameworkTextSetTextSelectable(int32_t textSelectable)
{
    if (!Utils::CheckParamsValid(textSelectable, TEXT_SELECTABLE_MODE.size())) {
        LOGE("invalid value for text selectable");
        return;
    }
    TextModel::GetInstance()->SetTextSelectableMode(TEXT_SELECTABLE_MODE[textSelectable]);
}

void FfiOHOSAceFrameworkTextSetHeightAdaptivePolicy(int32_t heightAdaptivePolicy)
{
    if (!Utils::CheckParamsValid(heightAdaptivePolicy, HEIGHT_ADAPTIVE_POLICY.size())) {
        LOGE("invalid value for height adaptive policy");
        return;
    }
    TextModel::GetInstance()->SetHeightAdaptivePolicy(HEIGHT_ADAPTIVE_POLICY[heightAdaptivePolicy]);
}

void FfiOHOSAceFrameworkTextEditMenuOptions(CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    ViewAbstract::ParseEditMenuOptions(cjOnCreateMenu, cjOnMenuItemClick, onCreateMenuCallback, onMenuItemClick);
    TextModel::GetInstance()->SetSelectionMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

VectorTextMenuItemHandle FFICJCreateVectorFfiTextMenuItem(int64_t size)
{
    return new std::vector<FfiTextMenuItem>(size);
}

void FFICJVectorFfiTextMenuItemDelete(VectorTextMenuItemHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<FfiTextMenuItem>*>(vec);
    delete actualVec;
}

void FFICJVectorFfiTextMenuItemSetElement(VectorTextMenuItemHandle vec, int64_t index, FfiTextMenuItem textMenuItem)
{
    auto actualVec = reinterpret_cast<std::vector<FfiTextMenuItem>*>(vec);
    (*actualVec)[index] = textMenuItem;
}

FfiTextMenuItem FFICJVectorFfiTextMenuItemGetElement(VectorTextMenuItemHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<FfiTextMenuItem>*>(vec);
    return (*actualVec)[index];
}

int64_t FFICJVectorFfiTextMenuItemGetSize(VectorTextMenuItemHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<FfiTextMenuItem>*>(vec);
    return (*actualVec).size();
}

void FfiOHOSAceFrameworkTextEnableDataDetector(bool value)
{
    TextModel::GetInstance()->SetTextDetectEnable(value);
}

void FfiOHOSAceFrameworkTextSetWordBreak(int32_t wordBreak)
{
    if (!Utils::CheckParamsValid(wordBreak, WORD_BREAK.size())) {
        LOGE("invalid value for word break");
        return;
    }
    TextModel::GetInstance()->SetWordBreak(WORD_BREAK[wordBreak]);
}

void FfiOHOSAceFrameworkTextSetSelection(int32_t start, int32_t end)
{
    TextModel::GetInstance()->SetTextSelection(start, end);
}

void FfiOHOSAceFrameworkTextSetTextIndent(double textIndent, int32_t unit)
{
    Dimension dimValue(textIndent, static_cast<DimensionUnit>(unit));
    TextModel::GetInstance()->SetTextIndent(dimValue);
}

void FfiOHOSAceFrameworkTextSetEllipsisMode(int32_t ellipsisMode)
{
    if (!Utils::CheckParamsValid(ellipsisMode, ELLIPSIS_MODE.size())) {
        LOGE("invalid value for ellipsis mode");
        return;
    }
    TextModel::GetInstance()->SetEllipsisMode(ELLIPSIS_MODE[ellipsisMode]);
}

void FfiOHOSAceFrameworkTextOnCopy(void (*callback)(const char* value))
{
    auto onCopy = [lambda = CJLambda::Create(callback)](const std::u16string& value) -> void {
        const std::string valueStr = UtfUtils::Str16ToStr8(value);
        lambda(valueStr.c_str());
    };
    TextModel::GetInstance()->SetOnCopy(std::move(onCopy));
}

void FfiOHOSAceFrameworkTextOnTextSelectionChange(void (*callback)(int32_t start, int32_t end))
{
    auto onTextSelectionChange = [lambda = CJLambda::Create(callback)](
                                     int32_t start, int32_t end) -> void { lambda(start, end); };
    TextModel::GetInstance()->SetOnTextSelectionChange(std::move(onTextSelectionChange));
}

void FfiOHOSAceFrameworkTextBindSelectionMenu(int32_t spanType, void (*content)(), int32_t responseType,
    void (*onAppear)(int32_t start, int32_t end), void (*onDisappear)())
{
    if (!Utils::CheckParamsValid(spanType, TEXT_SPAN_TYPE.size())) {
        LOGE("invalid value for text span type");
        return;
    }
    NG::TextSpanType textSpanType = TEXT_SPAN_TYPE[spanType];
    if (!Utils::CheckParamsValid(responseType, TEXT_RESPONSE_TYPE.size())) {
        LOGE("invalid value for text response type");
        return;
    }
    NG::TextResponseType textResponseType = TEXT_RESPONSE_TYPE[responseType];
    auto customBuilder = CJLambda::Create(content);
    auto callbackOnAppear = [lambda = CJLambda::Create(onAppear)](
                                int32_t start, int32_t end) -> void { lambda(start, end); };
    NG::SelectMenuParam menuParam;
    menuParam.onAppear = std::move(callbackOnAppear);
    menuParam.onDisappear = CJLambda::Create(onDisappear);
    TextModel::GetInstance()->BindSelectionMenu(textSpanType, textResponseType, customBuilder, menuParam);
}

void FfiOHOSAceFrameworkTextDraggable(bool value)
{
    ViewAbstractModel::GetInstance()->SetDraggable(value);
}

void FfiOHOSAceFrameworkTextPrivacySensitive(bool value)
{
    ViewAbstractModel::GetInstance()->SetPrivacySensitive(value);
}

int64_t FfiOHOSAceFrameworkTextControllerCtor()
{
    auto controller = FFIData::Create<NGNativeTextController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkTextControllerCloseSelectionMenu(int64_t selfID)
{
    auto self = FFIData::GetData<NGNativeTextController>(selfID);
    if (self != nullptr) {
        self->CloseSelectionMenu();
    } else {
        LOGE("FfiText: invalid textControllerId");
    }
}
}