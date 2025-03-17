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

#include "core/components_ng/pattern/text/text_styles.h"

namespace {
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_COLOR = 1;
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_OPACITY = 2;
};

namespace OHOS::Ace::NG {
#define UPDATE_TEXT_STYLE(group, name, func)             \
    do {                                                 \
        if ((group)->prop##name.has_value()) {           \
            textStyle.func((group)->prop##name.value()); \
        }                                                \
    } while (false)

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme)
{
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
#if defined(IOS_PLATFORM) || defined(ANDROID_PLATFORM)
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(defaultFontFamily);
#endif
    UseSelfStyle(fontStyle, textLineStyle, textStyle);
    return textStyle;
}

void UseSelfStyle(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, TextStyle& textStyle)
{
    if (fontStyle) {
        UPDATE_TEXT_STYLE(fontStyle, FontSize, SetFontSize);
        UPDATE_TEXT_STYLE(fontStyle, TextColor, SetTextColor);
        UPDATE_TEXT_STYLE(fontStyle, TextShadow, SetTextShadows);
        UPDATE_TEXT_STYLE(fontStyle, ItalicFontStyle, SetFontStyle);
        UPDATE_TEXT_STYLE(fontStyle, FontWeight, SetFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, FontFamily, SetFontFamilies);
        UPDATE_TEXT_STYLE(fontStyle, FontFeature, SetFontFeatures);
        UPDATE_TEXT_STYLE(fontStyle, TextDecoration, SetTextDecoration);
        UPDATE_TEXT_STYLE(fontStyle, TextDecorationColor, SetTextDecorationColor);
        UPDATE_TEXT_STYLE(fontStyle, TextDecorationStyle, SetTextDecorationStyle);
        UPDATE_TEXT_STYLE(fontStyle, TextCase, SetTextCase);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMinFontSize, SetAdaptMinFontSize);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMaxFontSize, SetAdaptMaxFontSize);
        UPDATE_TEXT_STYLE(fontStyle, LetterSpacing, SetLetterSpacing);
        UPDATE_TEXT_STYLE(fontStyle, SymbolColorList, SetSymbolColorList);
        UPDATE_TEXT_STYLE(fontStyle, SymbolRenderingStrategy, SetRenderStrategy);
        UPDATE_TEXT_STYLE(fontStyle, SymbolEffectStrategy, SetEffectStrategy);
        UPDATE_TEXT_STYLE(fontStyle, SymbolEffectOptions, SetSymbolEffectOptions);
        UPDATE_TEXT_STYLE(fontStyle, MinFontScale, SetMinFontScale);
        UPDATE_TEXT_STYLE(fontStyle, MaxFontScale, SetMaxFontScale);
        UPDATE_TEXT_STYLE(fontStyle, VariableFontWeight, SetVariableFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, EnableVariableFontWeight, SetEnableVariableFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, SymbolType, SetSymbolType);
    }
    if (textLineStyle) {
        UPDATE_TEXT_STYLE(textLineStyle, LineHeight, SetLineHeight);
        UPDATE_TEXT_STYLE(textLineStyle, HalfLeading, SetHalfLeading);
        UPDATE_TEXT_STYLE(textLineStyle, TextBaseline, SetTextBaseline);
        UPDATE_TEXT_STYLE(textLineStyle, BaselineOffset, SetBaselineOffset);
        UPDATE_TEXT_STYLE(textLineStyle, TextOverflow, SetTextOverflow);
        UPDATE_TEXT_STYLE(textLineStyle, TextAlign, SetTextAlign);
        UPDATE_TEXT_STYLE(textLineStyle, MaxLines, SetMaxLines);
        UPDATE_TEXT_STYLE(textLineStyle, TextIndent, SetTextIndent);
        UPDATE_TEXT_STYLE(textLineStyle, WordBreak, SetWordBreak);
        UPDATE_TEXT_STYLE(textLineStyle, EllipsisMode, SetEllipsisMode);
        UPDATE_TEXT_STYLE(textLineStyle, LineSpacing, SetLineSpacing);
        UPDATE_TEXT_STYLE(textLineStyle, LineBreakStrategy, SetLineBreakStrategy);
        UPDATE_TEXT_STYLE(textLineStyle, AllowScale, SetAllowScale);
        UPDATE_TEXT_STYLE(textLineStyle, ParagraphSpacing, SetParagraphSpacing);
    }
}

TextStyle CreateTextStyleUsingThemeWithText(const RefPtr<FrameNode> frameNode,
    const std::unique_ptr<FontStyle>& fontStyle, const std::unique_ptr<TextLineStyle>& textLineStyle,
    const RefPtr<TextTheme>& textTheme)
{
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, textTheme);
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext->HasForegroundColor() || renderContext->HasForegroundColorStrategy()) {
        textStyle.SetTextColor(Color::FOREGROUND);
    }
    return textStyle;
}
std::string GetFontSizeInJson(const std::optional<Dimension>& value)
{
    return value.value_or(TEXT_DEFAULT_FONT_SIZE).ToString();
}
std::string GetFontStyleInJson(const std::optional<Ace::FontStyle>& value)
{
    return value.value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic";
}
std::string GetFontWeightInJson(const std::optional<FontWeight>& value)
{
    return V2::ConvertWrapFontWeightToStirng(value.value_or(FontWeight::NORMAL));
}
std::string GetFontFamilyInJson(const std::optional<std::vector<std::string>>& value)
{
    std::vector<std::string> fontFamilyVector = value.value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
    if (fontFamilyVector.empty()) {
        fontFamilyVector = std::vector<std::string>({ "HarmonyOS Sans" });
    }
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    return fontFamily;
}
std::string GetFontFamilyInJson(const std::vector<std::string>& fontFamilyVector)
{
    std::string fontFamily;
    if (fontFamilyVector.empty()) {
        return fontFamily;
    }
    fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    return fontFamily;
}
std::string GetSymbolRenderingStrategyInJson(const std::optional<uint32_t>& value)
{
    std::string text;
    if (value == RENDERINGSTRATEGY_MULTIPLE_COLOR) {
        text = "SymbolRenderingStrategy.MULTIPLE_COLOR";
    } else if (value == RENDERINGSTRATEGY_MULTIPLE_OPACITY) {
        text = "SymbolRenderingStrategy.MULTIPLE_OPACITY";
    } else {
        text = "SymbolRenderingStrategy.SINGLE";
    }
    return text;
}
std::string GetSymbolEffectStrategyInJson(const std::optional<uint32_t>& value)
{
    std::string text;
    SymbolEffectType type = static_cast<SymbolEffectType>(value.value_or(0));
    if (type == SymbolEffectType::SCALE) {
        text = "SymbolEffectStrategy.SCALE";
    } else if (type == SymbolEffectType::HIERARCHICAL) {
        text = "SymbolEffectStrategy.HIERARCHICAL";
    } else {
        text = "SymbolEffectStrategy.NONE";
    }
    return text;
}

std::string GetLineBreakStrategyInJson(const std::optional<Ace::LineBreakStrategy>& value)
{
    std::string text;
    if (value == LineBreakStrategy::HIGH_QUALITY) {
        text = "HIGH_QUALITY";
    } else if (value == LineBreakStrategy::BALANCED) {
        text = "BALANCED";
    } else {
        text = "GREEDY";
    }
    return text;
}

std::string GetSymbolEffectOptionsInJson(const std::optional<SymbolEffectOptions>& value)
{
    std::string text = "";
    if (value.has_value()) {
        text = value.value().ToString();
    }
    return text;
}

void FontStyle::UpdateColorByResourceId()
{
    if (propTextColor) {
        propTextColor->UpdateColorByResourceId();
    }
    if (propTextDecorationColor) {
        propTextDecorationColor->UpdateColorByResourceId();
    }
    if (propTextShadow) {
        auto& shadows = propTextShadow.value();
        std::for_each(shadows.begin(), shadows.end(), [](Shadow& sd) { sd.UpdateColorByResourceId(); });
    }
    if (propSymbolColorList) {
        auto& colors = propSymbolColorList.value();
        std::for_each(colors.begin(), colors.end(), [](Color& cl) { cl.UpdateColorByResourceId(); });
    }
}
} // namespace OHOS::Ace::NG
