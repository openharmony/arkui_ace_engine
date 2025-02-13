/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_layout_manager.h"
#include "bridge/declarative_frontend/jsview/js_text.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/event/ace_event_handler.h"
#include "core/pipeline/pipeline_base.h"
#include "core/text/text_emoji_processor.h"

namespace OHOS::Ace {

std::unique_ptr<TextModel> TextModel::instance_ = nullptr;
std::mutex TextModel::mutex_;

TextModel* TextModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::TextModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::TextModelNG instance;
        return &instance;
    } else {
        static Framework::TextModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY,
    TextAlign::LEFT, TextAlign::RIGHT };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES = { LineBreakStrategy::GREEDY,
    LineBreakStrategy::HIGH_QUALITY, LineBreakStrategy::BALANCED };
const std::vector<EllipsisMode> ELLIPSIS_MODALS = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL };
const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE = { TextSelectableMode::SELECTABLE_UNFOCUSABLE,
    TextSelectableMode::SELECTABLE_FOCUSABLE, TextSelectableMode::UNSELECTABLE };
constexpr TextDecorationStyle DEFAULT_TEXT_DECORATION_STYLE = TextDecorationStyle::SOLID;
const int32_t DEFAULT_VARIABLE_FONT_WEIGHT = 400;
}; // namespace

void JSText::SetWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    TextModel::GetInstance()->OnSetWidth();
}

void JSText::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    TextModel::GetInstance()->OnSetHeight();
}

void JSText::SetFont(const JSCallbackInfo& info)
{
    Font font;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    font.fontSize = theme->GetTextStyle().GetFontSize();
    font.fontWeight = theme->GetTextStyle().GetFontWeight();
    font.fontFamilies = theme->GetTextStyle().GetFontFamilies();
    font.fontStyle = theme->GetTextStyle().GetFontStyle();
    GetFontInfo(info, font);
    TextModel::GetInstance()->SetFont(font);
    if (info.Length() < 2) { // 2 : two args
        return;
    }
    auto tmpInfo = info[1];
    if (!tmpInfo->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(tmpInfo);
    auto enableVariableFontWeight = paramObject->GetProperty("enableVariableFontWeight");
    if (enableVariableFontWeight->IsBoolean()) {
        TextModel::GetInstance()->SetEnableVariableFontWeight(enableVariableFontWeight->ToBoolean());
    } else {
        TextModel::GetInstance()->SetEnableVariableFontWeight(false);
    }
}

void JSText::GetFontInfo(const JSCallbackInfo& info, Font& font)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(tmpInfo);
    auto fontSize = paramObject->GetProperty(static_cast<int32_t>(ArkUIIndex::SIZE));
    CalcDimension size;
    if (ParseJsDimensionFpNG(fontSize, size, false) && size.IsNonNegative()) {
        font.fontSize = size;
    }
    std::string weight;
    auto fontWeight = paramObject->GetProperty(static_cast<int32_t>(ArkUIIndex::WEIGHT));
    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        int32_t variableFontWeight = DEFAULT_VARIABLE_FONT_WEIGHT;
        ParseJsInt32(fontWeight, variableFontWeight);
        TextModel::GetInstance()->SetVariableFontWeight(variableFontWeight);
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            JSContainerBase::ParseJsString(fontWeight, weight);
        }
        font.fontWeight = ConvertStrToFontWeight(weight);
    }
    auto fontFamily = paramObject->GetProperty(static_cast<int32_t>(ArkUIIndex::FAMILY));
    if (!fontFamily->IsNull() && !fontFamily->IsUndefined()) {
        std::vector<std::string> fontFamilies;
        if (JSContainerBase::ParseJsFontFamilies(fontFamily, fontFamilies)) {
            font.fontFamilies = fontFamilies;
        }
    }
    auto style = paramObject->GetProperty(static_cast<int32_t>(ArkUIIndex::STYLE));
    if (!style->IsNull() && style->IsNumber()) {
        font.fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
    }
}

void JSText::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension fontSize;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, fontSize, false) || fontSize.IsNegative()) {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        fontSize = theme->GetTextStyle().GetFontSize();
        TextModel::GetInstance()->SetFontSize(fontSize);
        return;
    }
    TextModel::GetInstance()->SetFontSize(fontSize);
}

void JSText::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    JSRef<JSVal> args = info[0];
    std::string fontWeight;
    if (args->IsNumber()) {
        fontWeight = args->ToString();
    } else {
        ParseJsString(args, fontWeight);
    }
    FontWeight formatFontWeight = ConvertStrToFontWeight(fontWeight);
    TextModel::GetInstance()->SetFontWeight(formatFontWeight);
    int32_t fontWeightValue = static_cast<int32_t>(Constants::GetVariableFontWeight(formatFontWeight));
    TextModel::GetInstance()->SetVariableFontWeight(fontWeightValue);

    if (info.Length() < 2) { // 2 : two args
        return;
    }
    auto tmpInfo = info[1];
    if (!tmpInfo->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(tmpInfo);
    auto enableVariableFontWeight = paramObject->GetProperty("enableVariableFontWeight");
    if (enableVariableFontWeight->IsBoolean()) {
        TextModel::GetInstance()->SetEnableVariableFontWeight(enableVariableFontWeight->ToBoolean());
    } else {
        TextModel::GetInstance()->SetEnableVariableFontWeight(false);
    }
}

void JSText::SetMinFontScale(const JSCallbackInfo& info)
{
    double minFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], minFontScale)) {
        return;
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        TextModel::GetInstance()->SetMinFontScale(0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        TextModel::GetInstance()->SetMinFontScale(1.0f);
        return;
    }
    TextModel::GetInstance()->SetMinFontScale(static_cast<float>(minFontScale));
}

void JSText::SetMaxFontScale(const JSCallbackInfo& info)
{
    double maxFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], maxFontScale)) {
        return;
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        TextModel::GetInstance()->SetMaxFontScale(1.0f);
        return;
    }
    TextModel::GetInstance()->SetMaxFontScale(static_cast<float>(maxFontScale));
}

void JSText::SetForegroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        TextModel::GetInstance()->SetTextColor(Color::FOREGROUND);
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        return;
    }
    SetTextColor(info);
}

void JSText::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color textColor;
    JSRef<JSVal> args = info[0];
    if (!ParseJsColor(args, textColor)) {
        TextModel::GetInstance()->ResetTextColor();
        return;
    }
    TextModel::GetInstance()->SetTextColor(textColor);
}

void JSText::SetTextShadow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<Shadow> shadows;
    JSRef<JSVal> args = info[0];
    ParseTextShadowFromShadowObject(args, shadows);
    TextModel::GetInstance()->SetTextShadow(shadows);
}

void JSText::SetTextOverflow(const JSCallbackInfo& info)
{
    do {
        auto tmpInfo = info[0];
        if (!tmpInfo->IsObject()) {
            break;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(tmpInfo);
        JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
        if (!overflowValue->IsNumber() && !overflowValue->IsUndefined()) {
            break;
        }
        auto overflow = overflowValue->ToNumber<int32_t>();
        if(overflowValue->IsUndefined()) {
            overflow = 0;
        } else if (overflow < 0 || overflow >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            break;
        }
        TextModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[overflow]);
    } while (false);

    info.SetReturnValue(info.This());
}

void JSText::SetWordBreak(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    if (!args->IsNumber()) {
        return;
    }
    uint32_t index = args->ToNumber<uint32_t>();
    if (index < WORD_BREAK_TYPES.size()) {
        TextModel::GetInstance()->SetWordBreak(WORD_BREAK_TYPES[index]);
    }
}

void JSText::SetEllipsisMode(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    if (!args->IsNumber()) {
        return;
    }
    uint32_t index = args->ToNumber<uint32_t>();
    if (index < ELLIPSIS_MODALS.size()) {
        TextModel::GetInstance()->SetEllipsisMode(ELLIPSIS_MODALS[index]);
    }
}

void JSText::SetLineBreakStrategy(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TextModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    if (!info[0]->IsNumber()) {
        TextModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    auto index = info[0]->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(LINE_BREAK_STRATEGY_TYPES.size())) {
        TextModel::GetInstance()->SetLineBreakStrategy(LineBreakStrategy::GREEDY);
        return;
    }
    TextModel::GetInstance()->SetLineBreakStrategy(LINE_BREAK_STRATEGY_TYPES[index]);
}

void JSText::SetTextSelection(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    JSRef<JSVal> argsStartIndex = info[0];
    JSRef<JSVal> argsEndIndex = info[1];
    if (!argsStartIndex->IsNumber() || !argsEndIndex->IsNumber()) {
        return;
    }
    auto startIndex = argsStartIndex->ToNumber<int32_t>();
    auto endIndex = argsEndIndex->ToNumber<int32_t>();
    TextModel::GetInstance()->SetTextSelection(startIndex, endIndex);
}

void JSText::SetTextCaretColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color caretColor;
    if (!ParseJsColor(info[0], caretColor)) {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        caretColor = theme->GetCaretColor();
    }
    TextModel::GetInstance()->SetTextCaretColor(caretColor);
}

void JSText::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        selectedColor = theme->GetSelectedColor();
    }
    // Alpha = 255 means opaque
    if (selectedColor.GetAlpha() == JSThemeUtils::DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(JSThemeUtils::DEFAULT_OPACITY);
    }
    TextModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
}

void JSText::SetTextSelectableMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TextModel::GetInstance()->SetTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
        return;
    }
    if (!info[0]->IsNumber()) {
        TextModel::GetInstance()->SetTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
        return;
    }
    auto index = info[0]->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(TEXT_SELECTABLE_MODE.size())) {
        TextModel::GetInstance()->SetTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
        return;
    }
    TextModel::GetInstance()->SetTextSelectableMode(TEXT_SELECTABLE_MODE[index]);
}

void JSText::SetMaxLines(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    auto value = Infinity<int32_t>();
    if (args->ToString() != "Infinity") {
        ParseJsInt32(args, value);
    }
    TextModel::GetInstance()->SetMaxLines(value);
}

void JSText::SetTextIndent(const JSCallbackInfo& info)
{
    CalcDimension value;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, value)) {
        value.Reset();
        TextModel::GetInstance()->SetTextIndent(value);
        return;
    }
    TextModel::GetInstance()->SetTextIndent(value);
}

void JSText::SetFontStyle(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
        if (!(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE))) {
            return;
        }
        value = 0;
    }
    TextModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[value]);
}

void JSText::SetTextAlign(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_ALIGNS.size())) {
        if (!(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE))) {
            return;
        }
        value = 0;
    }
    TextModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
}

void JSText::SetAlign(const JSCallbackInfo& info)
{
    JSViewAbstract::JsAlign(info);
    JSRef<JSVal> args = info[0];
    if (!args->IsNumber()) {
        return;
    }
    TextModel::GetInstance()->OnSetAlign();
}

void JSText::SetLineHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, value)) {
        value.Reset();
        TextModel::GetInstance()->SetLineHeight(value);
        return;
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    TextModel::GetInstance()->SetLineHeight(value);
}

void JSText::SetLineSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    JSRef<JSVal> args = info[0];
    if (!ParseLengthMetricsToPositiveDimension(args, value)) {
        value.Reset();
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    TextModel::GetInstance()->SetLineSpacing(value);
}

void JSText::SetFontFamily(const JSCallbackInfo& info)
{
    std::vector<std::string> fontFamilies;
    JSRef<JSVal> args = info[0];
    ParseJsFontFamilies(args, fontFamilies);
    TextModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSText::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, minFontSize, false)) {
        minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
        TextModel::GetInstance()->SetAdaptMinFontSize(minFontSize);
        return;
    }
    if (minFontSize.IsNegative()) {
        minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    }
    TextModel::GetInstance()->SetAdaptMinFontSize(minFontSize);
}

void JSText::SetMaxFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, maxFontSize, false)) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
        TextModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
        return;
    }
    if (maxFontSize.IsNegative()) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    }
    TextModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
}

void JSText::SetLetterSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, value, false)) {
        value.Reset();
        TextModel::GetInstance()->SetLetterSpacing(value);
        return;
    }
    TextModel::GetInstance()->SetLetterSpacing(value);
}

void JSText::SetTextCase(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_CASES.size())) {
        if (!(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE))) {
            return;
        }
        value = 0;
    }
    TextModel::GetInstance()->SetTextCase(TEXT_CASES[value]);
}

void JSText::SetBaselineOffset(const JSCallbackInfo& info)
{
    CalcDimension value;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, value, false)) {
        value.Reset();
        TextModel::GetInstance()->SetBaselineOffset(value);
        return;
    }
    TextModel::GetInstance()->SetBaselineOffset(value);
}

void JSText::SetDecoration(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (tmpInfo->IsUndefined()) {
        TextModel::GetInstance()->SetTextDecoration(TextDecoration::NONE);
        info.ReturnSelf();
        return;
    }
    if (!tmpInfo->IsObject()) {
        info.ReturnSelf();
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(tmpInfo);
    JSRef<JSVal> typeValue = obj->GetProperty("type");
    JSRef<JSVal> colorValue = obj->GetProperty("color");
    JSRef<JSVal> styleValue = obj->GetProperty("style");

    TextDecoration textDecoration;
    if (typeValue->IsNumber()) {
        textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
    } else {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        textDecoration = theme->GetTextStyle().GetTextDecoration();
    }
    Color result;
    if (!ParseJsColor(colorValue, result)) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        if (SystemProperties::GetColorMode() == ColorMode::DARK) {
            result = theme->GetTextStyle().GetTextColor();
        } else {
            result = theme->GetTextStyle().GetTextDecorationColor();
        }
    }
    std::optional<TextDecorationStyle> textDecorationStyle;
    if (styleValue->IsNumber()) {
        textDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
    } else {
        textDecorationStyle = DEFAULT_TEXT_DECORATION_STYLE;
    }
    TextModel::GetInstance()->SetTextDecoration(textDecoration);
    TextModel::GetInstance()->SetTextDecorationColor(result);
    if (textDecorationStyle) {
        TextModel::GetInstance()->SetTextDecorationStyle(textDecorationStyle.value());
    }
    info.ReturnSelf();
}

void JSText::SetHeightAdaptivePolicy(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        if (!(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE))) {
            return;
        }
        value = 0;
    }
    TextModel::GetInstance()->SetHeightAdaptivePolicy(HEIGHT_ADAPTIVE_POLICY[value]);
}

void JSText::JsOnClick(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    if (Container::IsCurrentUseNewPipeline()) {
        if (args->IsUndefined() && IsDisableEventVersion()) {
            TextModel::GetInstance()->ClearOnClick();
            return;
        }
        if (!args->IsFunction()) {
            return;
        }
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(args));
        auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = frameNode]
            (BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            ACE_SCORING_EVENT("Text.onClick");
            PipelineContext::SetCallBackNode(node);
            func->Execute(*clickInfo);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
            std::u16string label = u"";
            if (!node.Invalid()) {
                auto pattern = node.GetRawPtr()->GetPattern();
                CHECK_NULL_VOID(pattern);
                auto layoutProperty = pattern->GetLayoutProperty<NG::TextLayoutProperty>();
                CHECK_NULL_VOID(layoutProperty);
                label = layoutProperty->GetContent().value_or(u"");
            }
            JSInteractableView::ReportClickEvent(node, label);
#endif
        };
        double distanceThreshold = std::numeric_limits<double>::infinity();
        if (info.Length() > 1 && info[1]->IsNumber()) {
            distanceThreshold = info[1]->ToNumber<double>();
            distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
        }
        TextModel::GetInstance()->SetOnClick(std::move(onClick), distanceThreshold);

        auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusable(true, false);
    } else {
        JsOnClickWithoutNGBUILD(info);
    }
}

void JSText::JsOnClickWithoutNGBUILD(const JSCallbackInfo& info)
{
#ifndef NG_BUILD
    JSRef<JSVal> args = info[0];
    if (args->IsFunction()) {
        auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
        auto impl = inspector ? inspector->GetInspectorFunctionImpl() : nullptr;
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(args));
        auto onClickId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), impl,
                             node = frameNode](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }
            ACE_SCORING_EVENT("Text.onClick");
            PipelineContext::SetCallBackNode(node);
            func->Execute(newInfo);
        };
        double distanceThreshold = std::numeric_limits<double>::infinity();
        if (info.Length() > 1 && info[1]->IsNumber()) {
            distanceThreshold = info[1]->ToNumber<double>();
            distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
        }
        TextModel::GetInstance()->SetOnClick(std::move(onClickId), distanceThreshold);
    }
#endif
}

void JSText::JsRemoteMessage(const JSCallbackInfo& info)
{
    JSInteractableView::JsCommonRemoteMessage(info);
    auto callback = JSInteractableView::GetRemoteMessageEventCallback(info);
    TextModel::GetInstance()->SetRemoteMessage(std::move(callback));
}

void JSText::Create(const JSCallbackInfo& info)
{
    std::u16string data;
    if (info.Length() <= 0) {
        TextModel::GetInstance()->Create(data);
        return;
    }

    JSRef<JSVal> args = info[0];
    if (args->IsObject() && JSRef<JSObject>::Cast(args)->Unwrap<JSSpanString>()) {
        auto *spanString = JSRef<JSObject>::Cast(args)->Unwrap<JSSpanString>();
        if (spanString == nullptr) {
            return;
        }
        auto spanStringController = spanString->GetController();
        if (spanStringController) {
            TextModel::GetInstance()->Create(spanStringController);
        } else {
            TextModel::GetInstance()->Create(data);
        }
    } else {
        ParseJsString(args, data);
        UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(data.data()), data.length(), 0);
        TextModel::GetInstance()->Create(data);
    }

    if (info.Length() <= 1 || !info[1]->IsObject()) {
        return;
    }

    JSTextController* jsController = nullptr;
    auto paramObject = JSRef<JSObject>::Cast(info[1]);
    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject()) {
        jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextController>();
    }

    RefPtr<TextControllerBase> controller = TextModel::GetInstance()->GetTextController();
    if (jsController) {
        jsController->SetController(controller);
        auto styledString = jsController->GetStyledString();
        if (styledString) {
            controller->SetStyledString(styledString, false);
        }
    }
}

void JSText::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::None;
    auto tmpInfo = info[0];
    if (tmpInfo->IsNumber()) {
        auto emunNumber = tmpInfo->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    TextModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSText::SetOnCopy(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    CHECK_NULL_VOID(args->IsFunction());
    JsEventCallback<void(const std::u16string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(args));
    TextModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSText::JsOnDragStart(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    CHECK_NULL_VOID(args->IsFunction());
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(args));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc),
                           targetNode = frameNode](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);
        PipelineContext::SetCallBackNode(targetNode);
        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return itemInfo;
        }
        auto node = ParseDragNode(ret);
        if (node) {
            itemInfo.node = node;
            return itemInfo;
        }
        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        node = ParseDragNode(builderObj->GetProperty("builder"));
        itemInfo.node = node;
        return itemInfo;
    };

    TextModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
}

void JSText::JsFocusable(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        return;
    }
    JSInteractableView::SetFocusable(tmpInfo->ToBoolean());
    JSInteractableView::SetFocusNode(false);
}

void JSText::JsDraggable(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetDraggable(tmpInfo->ToBoolean());
}

void JSText::JsEnableDataDetector(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        TextModel::GetInstance()->SetTextDetectEnable(false);
        return;
    }
    auto enable = tmpInfo->ToBoolean();
    TextModel::GetInstance()->SetTextDetectEnable(enable);
}

void JSText::JsDataDetectorConfig(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    JSRef<JSVal> args = info[0];
    if (!args->IsObject()) {
        return;
    }

    TextDetectConfig textDetectConfig;
    if (!ParseDataDetectorConfig(info, textDetectConfig)) {
        return;
    }
    TextModel::GetInstance()->SetTextDetectConfig(textDetectConfig);
}

void JSText::BindSelectionMenu(const JSCallbackInfo& info)
{
    // TextSpanType
    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    bool isValidTextSpanType = true;
    JSRef<JSVal> argsSpanType = info[0];
    if (argsSpanType->IsNumber()) {
        auto spanTypeId = argsSpanType->ToNumber<int32_t>();
        isValidTextSpanType = NG::TextSpanTypeMapper::GetTextSpanTypeFromJsType(spanTypeId, textSpanType);
    }

    // Builder
    JSRef<JSVal> argsMenuObj = info[1];
    if (!argsMenuObj->IsObject()) {
        return;
    }
    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(argsMenuObj);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);

    // TextResponseType
    int32_t resquiredParameterCount = 3;
    JSRef<JSVal> argsResponse = info[resquiredParameterCount - 1];
    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    if (argsResponse->IsNumber()) {
        auto response = argsResponse->ToNumber<int32_t>();
        responseType = static_cast<NG::TextResponseType>(response);
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void()> buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                          node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSelectionMenu");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    // SelectionMenuOptions
    NG::SelectMenuParam menuParam;
    menuParam.isValid = isValidTextSpanType;
    if (info.Length() > static_cast<uint32_t>(resquiredParameterCount)) {
        JSRef<JSVal> argsMenuOptions = info[resquiredParameterCount];
        if (argsMenuOptions->IsObject()) {
            ParseMenuParam(info, argsMenuOptions, menuParam);
        }
    }

    TextModel::GetInstance()->BindSelectionMenu(textSpanType, responseType, buildFunc, menuParam);
}

void JSText::SetOnTextSelectionChange(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    CHECK_NULL_VOID(args->IsFunction());
    JsEventCallback<void(int32_t, int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(args));
    TextModel::GetInstance()->SetOnTextSelectionChange(std::move(callback));
}

void JSText::JsClip(const JSCallbackInfo& info)
{
    JSViewAbstract::JsClip(info);
    JSRef<JSVal> args = info[0];
    if (args->IsBoolean()) {
        TextModel::GetInstance()->SetClipEdge(args->ToBoolean());
    }
}

void JSText::SetFontFeature(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsObject()) {
        return;
    }
    std::string fontFeatureSettings = info[0]->ToString();
    TextModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

void JSText::JsResponseRegion(const JSCallbackInfo& info)
{
    JSViewAbstract::JsResponseRegion(info);
    TextModel::GetInstance()->SetResponseRegion(true);
}

void JSText::SetHalfLeading(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto halfLeading = info[0];
    if (!halfLeading->IsBoolean()) {
        TextModel::GetInstance()->SetHalfLeading(false);
        return;
    }
    auto enable = halfLeading->ToBoolean();
    TextModel::GetInstance()->SetHalfLeading(enable);
}

void JSText::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    bool state = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        state = info[0]->ToBoolean();
    }
    TextModel::GetInstance()->SetEnableHapticFeedback(state);
}

void JSText::JSBind(BindingTarget globalObj)
{
    JSClass<JSText>::Declare("Text");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSText>::StaticMethod("create", &JSText::Create, opt);
    JSClass<JSText>::StaticMethod("width", &JSText::SetWidth);
    JSClass<JSText>::StaticMethod("height", &JSText::SetHeight);
    JSClass<JSText>::StaticMethod("font", &JSText::SetFont, opt);
    JSClass<JSText>::StaticMethod("fontColor", &JSText::SetTextColor, opt);
    JSClass<JSText>::StaticMethod("textShadow", &JSText::SetTextShadow, opt);
    JSClass<JSText>::StaticMethod("fontSize", &JSText::SetFontSize, opt);
    JSClass<JSText>::StaticMethod("fontWeight", &JSText::SetFontWeight, opt);
    JSClass<JSText>::StaticMethod("minFontScale", &JSText::SetMinFontScale, opt);
    JSClass<JSText>::StaticMethod("maxFontScale", &JSText::SetMaxFontScale, opt);
    JSClass<JSText>::StaticMethod("wordBreak", &JSText::SetWordBreak, opt);
    JSClass<JSText>::StaticMethod("lineBreakStrategy", &JSText::SetLineBreakStrategy, opt);
    JSClass<JSText>::StaticMethod("ellipsisMode", &JSText::SetEllipsisMode, opt);
    JSClass<JSText>::StaticMethod("selection", &JSText::SetTextSelection, opt);
    JSClass<JSText>::StaticMethod("textSelectable", &JSText::SetTextSelectableMode, opt);
    JSClass<JSText>::StaticMethod("maxLines", &JSText::SetMaxLines, opt);
    JSClass<JSText>::StaticMethod("textIndent", &JSText::SetTextIndent);
    JSClass<JSText>::StaticMethod("textOverflow", &JSText::SetTextOverflow, opt);
    JSClass<JSText>::StaticMethod("fontStyle", &JSText::SetFontStyle, opt);
    JSClass<JSText>::StaticMethod("align", &JSText::SetAlign, opt);
    JSClass<JSText>::StaticMethod("textAlign", &JSText::SetTextAlign, opt);
    JSClass<JSText>::StaticMethod("lineHeight", &JSText::SetLineHeight, opt);
    JSClass<JSText>::StaticMethod("lineSpacing", &JSText::SetLineSpacing, opt);
    JSClass<JSText>::StaticMethod("fontFamily", &JSText::SetFontFamily, opt);
    JSClass<JSText>::StaticMethod("minFontSize", &JSText::SetMinFontSize, opt);
    JSClass<JSText>::StaticMethod("maxFontSize", &JSText::SetMaxFontSize, opt);
    JSClass<JSText>::StaticMethod("letterSpacing", &JSText::SetLetterSpacing, opt);
    JSClass<JSText>::StaticMethod("textCase", &JSText::SetTextCase, opt);
    JSClass<JSText>::StaticMethod("baselineOffset", &JSText::SetBaselineOffset, opt);
    JSClass<JSText>::StaticMethod("caretColor", &JSText::SetTextCaretColor);
    JSClass<JSText>::StaticMethod("selectedBackgroundColor", &JSText::SetSelectedBackgroundColor);
    JSClass<JSText>::StaticMethod("decoration", &JSText::SetDecoration);
    JSClass<JSText>::StaticMethod("heightAdaptivePolicy", &JSText::SetHeightAdaptivePolicy);
    JSClass<JSText>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSText>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSText>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSText>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSText>::StaticMethod("remoteMessage", &JSText::JsRemoteMessage);
    JSClass<JSText>::StaticMethod("copyOption", &JSText::SetCopyOption);
    JSClass<JSText>::StaticMethod("onClick", &JSText::JsOnClick);
    JSClass<JSText>::StaticMethod("onCopy", &JSText::SetOnCopy);
    JSClass<JSText>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSText>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSText>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSText>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FIFTEEN)) {
        JSClass<JSText>::StaticMethod("onDragStart", &JSText::JsOnDragStart);
    } else {
        JSClass<JSText>::StaticMethod("onDragStart", &JSViewAbstract::JsOnDragStart);
    }
    JSClass<JSText>::StaticMethod("focusable", &JSText::JsFocusable);
    JSClass<JSText>::StaticMethod("draggable", &JSText::JsDraggable);
    JSClass<JSText>::StaticMethod("enableDataDetector", &JSText::JsEnableDataDetector);
    JSClass<JSText>::StaticMethod("dataDetectorConfig", &JSText::JsDataDetectorConfig);
    JSClass<JSText>::StaticMethod("bindSelectionMenu", &JSText::BindSelectionMenu);
    JSClass<JSText>::StaticMethod("onTextSelectionChange", &JSText::SetOnTextSelectionChange);
    JSClass<JSText>::StaticMethod("clip", &JSText::JsClip);
    JSClass<JSText>::StaticMethod("fontFeature", &JSText::SetFontFeature);
    JSClass<JSText>::StaticMethod("foregroundColor", &JSText::SetForegroundColor);
    JSClass<JSText>::StaticMethod("marqueeOptions", &JSText::SetMarqueeOptions);
    JSClass<JSText>::StaticMethod("onMarqueeStateChange", &JSText::SetOnMarqueeStateChange);
    JSClass<JSText>::StaticMethod("editMenuOptions", &JSText::EditMenuOptions);
    JSClass<JSText>::StaticMethod("responseRegion", &JSText::JsResponseRegion);
    JSClass<JSText>::StaticMethod("halfLeading", &JSText::SetHalfLeading);
    JSClass<JSText>::StaticMethod("enableHapticFeedback", &JSText::SetEnableHapticFeedback);
    JSClass<JSText>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSTextController::CloseSelectionMenu()
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->CloseSelectionMenu();
}

void JSTextController::GetLayoutManager(const JSCallbackInfo& args)
{
    JSRef<JSObject> obj = JSClass<JSLayoutManager>::NewInstance();
    auto jsLayoutManager = Referenced::Claim(obj->Unwrap<JSLayoutManager>());
    CHECK_NULL_VOID(jsLayoutManager);
    jsLayoutManager->IncRefCount();
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto layoutInfoInterface = controller->GetLayoutInfoInterface();
    jsLayoutManager->SetLayoutInfoInterface(layoutInfoInterface);
    args.SetReturnValue(obj);
}

void JSTextController::SetStyledString(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto* spanString = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSpanString>();
    if (!spanString) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    styledString_ = spanStringController;
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->SetStyledString(spanStringController, true);
    auto thisObj = info.This();
    thisObj->SetPropertyObject("STYLED_STRING_IN_CONTROLLER", info[0]);
}

void JSTextController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextController>::Declare("TextController");
    JSClass<JSTextController>::Method("closeSelectionMenu", &JSTextController::CloseSelectionMenu);
    JSClass<JSTextController>::CustomMethod("setStyledString", &JSTextController::SetStyledString);
    JSClass<JSTextController>::CustomMethod("getLayoutManager", &JSTextController::GetLayoutManager);
    JSClass<JSTextController>::Bind(globalObj, JSTextController::Constructor, JSTextController::Destructor);
}

void JSText::ParseMenuParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::SelectMenuParam& menuParam)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAppearValue = menuOptions->GetProperty("onAppear");
    if (onAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAppearValue));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc), node = frameNode](
                            int32_t start, int32_t end) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");

            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(start));
            params[1] = JSRef<JSVal>::Make(ToJSValue(end));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(2, params);
        };
        menuParam.onAppear = std::move(onAppear);
    }

    auto onDisappearValue = menuOptions->GetProperty("onDisappear");
    if (onDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDisappearValue));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    menuParam.onMenuShow = ParseMenuCallback(frameNode, menuOptions, info, "onMenuShow");
    menuParam.onMenuHide = ParseMenuCallback(frameNode, menuOptions, info, "onMenuHide");
}

std::function<void(int32_t, int32_t)> JSText::ParseMenuCallback(const WeakPtr<NG::FrameNode>& frameNode,
    const JSRef<JSObject>& menuOptions, const JSCallbackInfo& info, const std::string& name)
{
    auto onMenuCallbackValue = menuOptions->GetProperty(name.c_str());
    if (onMenuCallbackValue->IsFunction()) {
        RefPtr<JsFunction> jsOnMenuCallbackFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onMenuCallbackValue));
        auto onMenuCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnMenuCallbackFunc),
                                  node = frameNode, eventName = name](int32_t start, int32_t end) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT(eventName);

            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(start));
            params[1] = JSRef<JSVal>::Make(ToJSValue(end));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(2, params);
        };
        return onMenuCallback;
    }
    return nullptr;
}

void JSText::SetMarqueeOptions(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    auto args = info[0];
    NG::TextMarqueeOptions options;

    if (!args->IsObject()) {
        TextModel::GetInstance()->SetMarqueeOptions(options);
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(args);
    ParseMarqueeParam(paramObject, options);
    TextModel::GetInstance()->SetMarqueeOptions(options);
}

void JSText::ParseMarqueeParam(const JSRef<JSObject>& paramObject, NG::TextMarqueeOptions& options)
{
    auto getStart = paramObject->GetProperty("start");
    if (getStart->IsBoolean()) {
        options.UpdateTextMarqueeStart(getStart->ToBoolean());
    }

    auto getLoop = paramObject->GetProperty("loop");
    if (getLoop->IsNumber()) {
        int32_t loop = static_cast<int32_t>(getLoop->ToNumber<double>());
        if (loop == std::numeric_limits<int32_t>::max() || loop <= 0) {
            loop = -1;
        }
        options.UpdateTextMarqueeLoop(loop);
    }

    auto getStep = paramObject->GetProperty("step");
    if (getStep->IsNumber()) {
        auto step = getStep->ToNumber<double>();
        if (GreatNotEqual(step, 0.0)) {
            options.UpdateTextMarqueeStep(Dimension(step, DimensionUnit::VP).ConvertToPx());
        }
    }

    auto delay = paramObject->GetProperty("delay");
    if (delay->IsNumber()) {
        auto delayDouble = delay->ToNumber<double>();
        auto delayValue = static_cast<int32_t>(delayDouble);
        if (delayValue < 0) {
            delayValue = 0;
        }
        options.UpdateTextMarqueeDelay(delayValue);
    }

    auto getFromStart = paramObject->GetProperty("fromStart");
    if (getFromStart->IsBoolean()) {
        options.UpdateTextMarqueeDirection(
            getFromStart->ToBoolean() ? MarqueeDirection::DEFAULT : MarqueeDirection::DEFAULT_REVERSE);
    }

    auto getFadeout = paramObject->GetProperty("fadeout");
    if (getFadeout->IsBoolean()) {
        options.UpdateTextMarqueeFadeout(getFadeout->ToBoolean());
    }

    auto getStartPolicy = paramObject->GetProperty("marqueeStartPolicy");
    if (getStartPolicy->IsNumber()) {
        auto startPolicy = static_cast<MarqueeStartPolicy>(getStartPolicy->ToNumber<int32_t>());
        options.UpdateTextMarqueeStartPolicy(startPolicy);
    }
}

void JSText::SetOnMarqueeStateChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onMarqueeStateChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                    int32_t value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Text.onMarqueeStateChange");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(1, &newJSVal);
    };

    TextModel::GetInstance()->SetOnMarqueeStateChange(std::move(onMarqueeStateChange));
}

void JSText::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick);
    TextModel::GetInstance()->SetSelectionMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
} // namespace OHOS::Ace::Framework
