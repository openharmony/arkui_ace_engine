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
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace {
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_COLOR = 1;
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_OPACITY = 2;
};  // namespace

namespace OHOS::Ace::NG {
#define UPDATE_TEXT_STYLE(group, name, func)             \
    do {                                                 \
        if ((group)->prop##name.has_value()) {           \
            textStyle.func((group)->prop##name.value()); \
        }                                                \
    } while (false)

#define UPDATE_TEXT_STYLE_WITH_THEME(group, name, styleName)                      \
    do {                                                                          \
        if (group && (group)->prop##name.has_value()) {                           \
            textStyle.Set##styleName((group)->prop##name.value());                \
        } else if (textTheme) {                                                   \
            textStyle.Set##styleName(textTheme->GetTextStyle().Get##styleName()); \
        }                                                                         \
    } while (false)

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme, bool isSymbol)
{
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
#ifndef OHOS_STANDARD_SYSTEM
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(defaultFontFamily);
#endif
    UseSelfStyle(fontStyle, textLineStyle, textStyle, isSymbol);
    return textStyle;
}

void CreateTextStyleUsingTheme(const RefPtr<TextLayoutProperty>& property, const RefPtr<TextTheme>& textTheme,
    TextStyle& textStyle, bool isSymbol)
{
    UseSelfStyleWithTheme(property, textStyle, textTheme, isSymbol);
}

void UseSelfStyleWithTheme(const RefPtr<TextLayoutProperty>& property, TextStyle& textStyle,
    const RefPtr<TextTheme>& textTheme, bool isSymbol)
{
    CHECK_NULL_VOID(textTheme);
    auto& fontStyle = property->GetFontStyle();
    auto& textLineStyle = property->GetTextLineStyle();
    // The setting of AllowScale, MinFontScale, MaxFontScale must be done before any Dimension-type properties that
    // depend on its value.
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, AllowScale, AllowScale);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, MinFontScale, MinFontScale);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, MaxFontScale, MaxFontScale);

    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, FontSize, FontSize);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, AdaptMinFontSize, AdaptMinFontSize);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, AdaptMaxFontSize, AdaptMaxFontSize);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, LetterSpacing, LetterSpacing);

    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, TextShadow, TextShadows);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, ItalicFontStyle, FontStyle);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, FontWeight, FontWeight);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, FontFeature, FontFeatures);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, TextDecoration, TextDecoration);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, TextDecorationColor, TextDecorationColor);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, TextDecorationStyle, TextDecorationStyle);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, TextCase, TextCase);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, VariableFontWeight, VariableFontWeight);
    UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, EnableVariableFontWeight, EnableVariableFontWeight);

    if (isSymbol) {
        UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, SymbolColorList, SymbolColorList);
        UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, SymbolRenderingStrategy, RenderStrategy);
        UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, SymbolEffectStrategy, EffectStrategy);
        UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, SymbolEffectOptions, SymbolEffectOptions);
        UPDATE_TEXT_STYLE_WITH_THEME(fontStyle, SymbolType, SymbolType);
        textStyle.SetSymbolShadow(property->GetSymbolShadowValue(textTheme->GetTextStyle().GetSymbolShadow()));
        textStyle.SetShaderStyle(property->GetShaderStyleValue(textTheme->GetTextStyle().GetShaderStyle()));
    }

    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, LineHeight, LineHeight);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, BaselineOffset, BaselineOffset);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, TextIndent, TextIndent);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, LineSpacing, LineSpacing);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, TextBaseline, TextBaseline);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, TextOverflow, TextOverflow);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, TextAlign, TextAlign);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, TextVerticalAlign, ParagraphVerticalAlign);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, MaxLines, MaxLines);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, WordBreak, WordBreak);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, EllipsisMode, EllipsisMode);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, LineBreakStrategy, LineBreakStrategy);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, IsOnlyBetweenLines, IsOnlyBetweenLines);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, ParagraphSpacing, ParagraphSpacing);
    UPDATE_TEXT_STYLE_WITH_THEME(textLineStyle, OptimizeTrailingSpace, OptimizeTrailingSpace);
}

void UseSelfStyle(const std::unique_ptr<FontStyle>& fontStyle, const std::unique_ptr<TextLineStyle>& textLineStyle,
    TextStyle& textStyle, bool isSymbol)
{
    if (textLineStyle) {
        UPDATE_TEXT_STYLE(textLineStyle, AllowScale, SetAllowScale);
    }
    if (fontStyle) {
        UPDATE_TEXT_STYLE(fontStyle, MinFontScale, SetMinFontScale);
        UPDATE_TEXT_STYLE(fontStyle, MaxFontScale, SetMaxFontScale);

        UPDATE_TEXT_STYLE(fontStyle, FontSize, SetFontSize);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMinFontSize, SetAdaptMinFontSize);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMaxFontSize, SetAdaptMaxFontSize);
        UPDATE_TEXT_STYLE(fontStyle, LetterSpacing, SetLetterSpacing);

        UPDATE_TEXT_STYLE(fontStyle, TextColor, SetTextColor);
        UPDATE_TEXT_STYLE(fontStyle, TextShadow, SetTextShadows);
        UPDATE_TEXT_STYLE(fontStyle, ItalicFontStyle, SetFontStyle);
        UPDATE_TEXT_STYLE(fontStyle, FontWeight, SetFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, FontFamily, SetFontFamilies);
        UPDATE_TEXT_STYLE(fontStyle, FontFeature, SetFontFeatures);
        UPDATE_TEXT_STYLE(fontStyle, StrokeWidth, SetStrokeWidth);
        UPDATE_TEXT_STYLE(fontStyle, StrokeColor, SetStrokeColor);
        UPDATE_TEXT_STYLE(fontStyle, Superscript, SetSuperscript);
        UPDATE_TEXT_STYLE(fontStyle, TextDecoration, SetTextDecoration);
        UPDATE_TEXT_STYLE(fontStyle, TextDecorationColor, SetTextDecorationColor);
        UPDATE_TEXT_STYLE(fontStyle, TextDecorationStyle, SetTextDecorationStyle);
        UPDATE_TEXT_STYLE(fontStyle, LineThicknessScale, SetLineThicknessScale);
        UPDATE_TEXT_STYLE(fontStyle, TextCase, SetTextCase);

        UPDATE_TEXT_STYLE(fontStyle, VariableFontWeight, SetVariableFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, EnableVariableFontWeight, SetEnableVariableFontWeight);

        if (isSymbol) {
            UPDATE_TEXT_STYLE(fontStyle, SymbolColorList, SetSymbolColorList);
            UPDATE_TEXT_STYLE(fontStyle, SymbolRenderingStrategy, SetRenderStrategy);
            UPDATE_TEXT_STYLE(fontStyle, SymbolEffectStrategy, SetEffectStrategy);
            UPDATE_TEXT_STYLE(fontStyle, SymbolEffectOptions, SetSymbolEffectOptions);
            UPDATE_TEXT_STYLE(fontStyle, SymbolType, SetSymbolType);
        }
    }
    if (textLineStyle) {
        UPDATE_TEXT_STYLE(textLineStyle, LineHeight, SetLineHeight);
        UPDATE_TEXT_STYLE(textLineStyle, BaselineOffset, SetBaselineOffset);
        UPDATE_TEXT_STYLE(textLineStyle, TextIndent, SetTextIndent);
        UPDATE_TEXT_STYLE(textLineStyle, LineSpacing, SetLineSpacing);
        
        UPDATE_TEXT_STYLE(textLineStyle, HalfLeading, SetHalfLeading);
        UPDATE_TEXT_STYLE(textLineStyle, TextBaseline, SetTextBaseline);
        UPDATE_TEXT_STYLE(textLineStyle, TextOverflow, SetTextOverflow);
        UPDATE_TEXT_STYLE(textLineStyle, TextAlign, SetTextAlign);
        UPDATE_TEXT_STYLE(textLineStyle, TextVerticalAlign, SetParagraphVerticalAlign);
        UPDATE_TEXT_STYLE(textLineStyle, MaxLines, SetMaxLines);
        UPDATE_TEXT_STYLE(textLineStyle, WordBreak, SetWordBreak);
        UPDATE_TEXT_STYLE(textLineStyle, EllipsisMode, SetEllipsisMode);
        UPDATE_TEXT_STYLE(textLineStyle, LineBreakStrategy, SetLineBreakStrategy);
        UPDATE_TEXT_STYLE(textLineStyle, IsOnlyBetweenLines, SetIsOnlyBetweenLines);
        UPDATE_TEXT_STYLE(textLineStyle, ParagraphSpacing, SetParagraphSpacing);
        UPDATE_TEXT_STYLE(textLineStyle, OptimizeTrailingSpace, SetOptimizeTrailingSpace);
    }
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

std::unique_ptr<JsonValue> GetSymbolShadowInJson(const std::optional<SymbolShadow>& value)
{
    auto res = JsonUtil::Create(true);
    if (!value.has_value()) {
        return res;
    }
    const auto& shadow = value.value();
    res->Put("color", (shadow.color).ColorToString().c_str());
    std::string offsetStr = "[" + std::to_string(shadow.offset.first) + ", "
                           + std::to_string(shadow.offset.second) + "]";
    res->Put("offset", offsetStr.c_str());
    res->Put("radius", std::to_string(shadow.radius).c_str());
    return res;
}

std::string GradientTypeToString(SymbolGradientType type)
{
    switch (type) {
        case SymbolGradientType::COLOR_SHADER:
            return "COLOR_SHADER";
        case SymbolGradientType::RADIAL_GRADIENT:
            return "RADIAL_GRADIENT";
        case SymbolGradientType::LINEAR_GRADIENT:
            return "LINEAR_GRADIENT";
        default:
            return "UNKNOWN";
    }
}

std::unique_ptr<JsonValue> GetShaderStyleInJson(const std::optional<std::vector<SymbolGradient>>& value)
{
    auto array = JsonUtil::CreateArray(true);
    if (!value.has_value() || value->empty()) {
        return array;
    }
    for (const auto& gradient : *value) {
        auto obj = JsonUtil::Create(true);
        obj->Put("type", GradientTypeToString(gradient.type).c_str());
        auto colorsArray = JsonUtil::CreateArray(true);
        for (const auto& color : gradient.symbolColor) {
            colorsArray->Put("", color.ColorToString().c_str());
        }
        obj->Put("symbolColor", colorsArray);
        auto opacitiesArray = JsonUtil::CreateArray(true);
        for (float opacity : gradient.symbolOpacities) {
            opacitiesArray->Put("", std::to_string(opacity).c_str());
        }
        obj->Put("symbolOpacities", opacitiesArray);
        obj->Put("repeating", gradient.repeating ? "true" : "false");
        if (gradient.angle.has_value()) {
            obj->Put("angle", std::to_string(*gradient.angle).c_str());
        }
        if (gradient.radius.has_value()) {
            obj->Put("radius", gradient.radius->ToString().c_str());
        }
        if (gradient.radialCenterX.has_value()) {
            obj->Put("radialCenterX", gradient.radialCenterX->ToString().c_str());
        }
        if (gradient.radialCenterY.has_value()) {
            obj->Put("radialCenterY", gradient.radialCenterY->ToString().c_str());
        }
        array->Put(obj);
    }
    return array;
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

PlaceholderAlignment GetPlaceHolderAlignmentFromVerticalAlign(VerticalAlign verticalAlign)
{
    PlaceholderAlignment alignment;
    switch (verticalAlign) {
        case VerticalAlign::TOP:
            alignment = PlaceholderAlignment::TOP;
            break;
        case VerticalAlign::CENTER:
            alignment = PlaceholderAlignment::MIDDLE;
            break;
        case VerticalAlign::BOTTOM:
        case VerticalAlign::NONE:
            alignment = PlaceholderAlignment::BOTTOM;
            break;
        case VerticalAlign::BASELINE:
            alignment = PlaceholderAlignment::ABOVEBASELINE;
            break;
        case VerticalAlign::FOLLOW_PARAGRAPH:
            alignment = PlaceholderAlignment::FOLLOW_PARAGRAPH;
            break;
        default:
            alignment = PlaceholderAlignment::BOTTOM;
    }
    return alignment;
}
} // namespace OHOS::Ace::NG
