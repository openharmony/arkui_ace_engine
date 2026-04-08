/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/text_style.h"

#include "ui/base/utils/utils.h"

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace {
namespace StringUtils {

std::pair<bool, FontWeight> ParseFontWeight(const std::string& weight, FontWeight defaultFontWeight)
{
    static const LinearMapNode<FontWeight> fontWeightTable[] = {
        { "100", FontWeight::W100 },
        { "200", FontWeight::W200 },
        { "300", FontWeight::W300 },
        { "400", FontWeight::W400 },
        { "500", FontWeight::W500 },
        { "600", FontWeight::W600 },
        { "700", FontWeight::W700 },
        { "800", FontWeight::W800 },
        { "900", FontWeight::W900 },
        { "bold", FontWeight::BOLD },
        { "bolder", FontWeight::BOLDER },
        { "lighter", FontWeight::LIGHTER },
        { "medium", FontWeight::MEDIUM },
        { "normal", FontWeight::NORMAL },
        { "regular", FontWeight::REGULAR },
    };
    auto weightIter = BinarySearchFindIndex(fontWeightTable, ArraySize(fontWeightTable), weight.c_str());
    return weightIter != -1 ? std::make_pair(true, fontWeightTable[weightIter].value)
                            : std::make_pair(false, defaultFontWeight);
}

FontWeight StringToFontWeight(const std::string& weight, FontWeight defaultFontWeight)
{
    return ParseFontWeight(weight, defaultFontWeight).second;
}

WordBreak StringToWordBreak(const std::string& wordBreak)
{
    static const LinearMapNode<WordBreak> wordBreakTable[] = {
        { "hyphenation", WordBreak::HYPHENATION },
        { "break-all", WordBreak::BREAK_ALL },
        { "break-word", WordBreak::BREAK_WORD },
        { "normal", WordBreak::NORMAL },
    };
    auto wordBreakIter = BinarySearchFindIndex(wordBreakTable, ArraySize(wordBreakTable), wordBreak.c_str());
    return wordBreakIter != -1 ? wordBreakTable[wordBreakIter].value : WordBreak::BREAK_WORD;
}

int32_t GetFontWeightNumericValue(FontWeight fontWeight)
{
    FontWeight converted = ConvertFontWeight(fontWeight);
    int32_t index = static_cast<int32_t>(converted);
    int32_t result = DEFAULT_FONT_WEIGHT_INT32;
    if (index >= 0 && index <= static_cast<int32_t>(FontWeight::W900)) {
        result = (index + 1) * DEFAULT_MULTIPLE;
    }
    return result;
}

std::string FontWeightToString(const FontWeight& fontWeight)
{
    static const std::unordered_map<FontWeight, std::string> fontWeightTable = {
        { FontWeight::W100, "100" },
        { FontWeight::W200, "200" },
        { FontWeight::W300, "300" },
        { FontWeight::W400, "400" },
        { FontWeight::W500, "500" },
        { FontWeight::W600, "600" },
        { FontWeight::W700, "700" },
        { FontWeight::W800, "800" },
        { FontWeight::W900, "900" },
        { FontWeight::BOLD, "bold" },
        { FontWeight::BOLDER, "bolder" },
        { FontWeight::LIGHTER, "lighter" },
        { FontWeight::MEDIUM, "medium" },
        { FontWeight::NORMAL, "normal" },
        { FontWeight::REGULAR, "regular" },
    };
    auto weightIter = fontWeightTable.find(fontWeight);
    return weightIter != fontWeightTable.end() ? weightIter->second : "";
}

std::string ToString(const FontWeight& fontWeight)
{
    return FontWeightToString(fontWeight);
}

std::string SymbolColorListToString(const std::vector<Color>& colorList)
{
    std::string symbolColorList = "";
    if (!colorList.empty()) {
        symbolColorList = colorList[0].ColorToString();
        for (uint32_t i = 1; i < colorList.size(); ++i) {
            symbolColorList += ", " + colorList[i].ColorToString();
        }
    }
    return symbolColorList;
}

std::string SymbolColorListToStringWithHolder(const std::vector<Color>& colorList)
{
    std::string symbolColorList = "";
    if (!colorList.empty()) {
        symbolColorList = colorList[0].ColorToString();
        symbolColorList += "|PH:" + std::to_string(static_cast<uint8_t>(colorList[0].GetPlaceholder()));
        for (uint32_t i = 1; i < colorList.size(); ++i) {
            symbolColorList += ", " + colorList[i].ColorToString();
            symbolColorList += "|PH:" + std::to_string(static_cast<uint8_t>(colorList[i].GetPlaceholder()));
        }
    }
    return symbolColorList;
}
} // namespace StringUtils

FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    static const FontWeight FONT_WEIGHT_CONVERT_MAP[] = {
        FontWeight::W100,
        FontWeight::W200,
        FontWeight::W300,
        FontWeight::W400,
        FontWeight::W500,
        FontWeight::W600,
        FontWeight::W700,
        FontWeight::W800,
        FontWeight::W900,
        FontWeight::W700,
        FontWeight::W400,
        FontWeight::W900,
        FontWeight::W100,
        FontWeight::W500,
        FontWeight::W400,
    };
    int index = static_cast<int>(fontWeight);
    if (index >= 0 && index < static_cast<int>(sizeof(FONT_WEIGHT_CONVERT_MAP) / sizeof(FontWeight))) {
        return FONT_WEIGHT_CONVERT_MAP[index];
    }
    return FontWeight::W400;
}

TextStyle::TextStyle(const std::vector<std::string>& fontFamilies, double fontSize, FontWeight fontWeight,
    FontStyle fontStyle, const Color& textColor)
    : propFontFamilies_(fontFamilies), propFontStyle_(fontStyle), propTextColor_(textColor), fontWeight_(fontWeight)
{
    SetFontSize(Dimension(fontSize));
}

bool TextStyle::operator==(const TextStyle& rhs) const
{
    return propFontFamilies_ == rhs.propFontFamilies_ && fontFeatures_ == rhs.fontFeatures_ &&
           propTextDecorationStyle_ == rhs.propTextDecorationStyle_ && preferFontSizes_ == rhs.preferFontSizes_ &&
           fontSize_.value == rhs.fontSize_.value && adaptMinFontSize_.value == rhs.adaptMinFontSize_.value &&
           adaptMaxFontSize_.value == rhs.adaptMaxFontSize_.value &&
           propAdaptFontSizeStep_.value == rhs.propAdaptFontSizeStep_.value &&
           lineHeight_.value == rhs.lineHeight_.value && fontWeight_ == rhs.fontWeight_ &&
           propFontStyle_ == rhs.propFontStyle_ && propTextBaseline_ == rhs.propTextBaseline_ &&
           propTextOverflow_ == rhs.propTextOverflow_ && propTextAlign_ == rhs.propTextAlign_ &&
           propTextColor_ == rhs.propTextColor_ && propTextDecoration_ == rhs.propTextDecoration_ &&
           propTextShadows_ == rhs.propTextShadows_ && propLetterSpacing_.value == rhs.propLetterSpacing_.value &&
           propMaxLines_ == rhs.propMaxLines_ && adaptTextSize_ == rhs.adaptTextSize_ &&
           propAllowScale_ == rhs.propAllowScale_ && propWordBreak_ == rhs.propWordBreak_ &&
           propTextDecorationColor_ == rhs.propTextDecorationColor_ && propTextCase_ == rhs.propTextCase_ &&
           propBaselineOffset_.value == rhs.propBaselineOffset_.value && adaptHeight_ == rhs.adaptHeight_ &&
           propTextIndent_.value == rhs.propTextIndent_.value && propTextVerticalAlign_ == rhs.propTextVerticalAlign_ &&
           propWordSpacing_.value == rhs.propWordSpacing_.value && propEllipsisMode_ == rhs.propEllipsisMode_ &&
           propLineBreakStrategy_ == rhs.propLineBreakStrategy_ &&
           propTextBackgroundStyle_ == rhs.propTextBackgroundStyle_ &&
           propOrphanCharOptimization_ == rhs.propOrphanCharOptimization_ &&
           propCompressLeadingPunctuation_ == rhs.propCompressLeadingPunctuation_ &&
           propIncludeFontPadding_ == rhs.propIncludeFontPadding_ &&
           propFallbackLineSpacing_ == rhs.propFallbackLineSpacing_ && propStrokeWidth_ == rhs.propStrokeWidth_ &&
           propStrokeColor_ == rhs.propStrokeColor_ && NearEqual(propLineThicknessScale_, rhs.propLineThicknessScale_);
}

bool TextStyle::operator!=(const TextStyle& rhs) const
{
    return !(rhs == *this);
}

void TextStyle::SetAdaptTextSize(
    const Dimension& maxFontSize, const Dimension& minFontSize, const Dimension& fontSizeStep)
{
    adaptMaxFontSize_.value = maxFontSize;
    adaptMinFontSize_.value = minFontSize;
    propAdaptFontSizeStep_.value = fontSizeStep;
    adaptTextSize_ = true;
}

void TextBackgroundStyle::ToJsonValue(std::unique_ptr<JsonValue>& json, const std::optional<TextBackgroundStyle>& style,
    const NG::InspectorFilter& filter)
{
    NG::BorderRadiusProperty defaultRadius;
    TextBackgroundStyle exportStyle = { .backgroundColor = Color::TRANSPARENT, .backgroundRadius = defaultRadius };
    if (style.has_value()) {
        exportStyle.backgroundColor = style.value().backgroundColor.value_or(Color::TRANSPARENT);
        exportStyle.backgroundRadius = style.value().backgroundRadius.value_or(defaultRadius);
    }

    auto styleJson = JsonUtil::Create(true);
    styleJson->Put("color", exportStyle.backgroundColor->ColorToString().c_str());
    auto radiusJson = JsonUtil::Create(true);
    exportStyle.backgroundRadius->ToJsonValue(radiusJson, styleJson, filter);

    json->PutExtAttr("textBackgroundStyle", styleJson, filter);
}

void TextStyle::ToJsonValue(
    std::unique_ptr<JsonValue>& json, const std::optional<TextStyle>& style, const NG::InspectorFilter& filter)
{
    CHECK_NULL_VOID(json);
    CHECK_NULL_VOID(style);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("decoration",
        GetDeclarationString(style->GetTextDecorationColor(), style->GetTextDecoration(),
            style->GetTextDecorationStyle(), style->GetLineThicknessScale())
            .c_str(),
        filter);
}

std::string TextStyle::GetDeclarationString(const std::optional<Color>& color,
    const std::vector<TextDecoration>& textDecorations, const std::optional<TextDecorationStyle>& textDecorationStyle,
    const std::optional<float>& lineThicknessScale)
{
    auto jsonSpanDeclaration = JsonUtil::Create(true);
    jsonSpanDeclaration->Put("type", V2::ConvertWrapTextDecorationToStirng(textDecorations).c_str());
    jsonSpanDeclaration->Put("color", (color.value_or(Color::BLACK).ColorToString()).c_str());
    jsonSpanDeclaration->Put("style",
        V2::ConvertWrapTextDecorationStyleToString(textDecorationStyle.value_or(TextDecorationStyle::SOLID)).c_str());
    jsonSpanDeclaration->Put(
        "thicknessScale", StringUtils::DoubleToString(static_cast<double>(lineThicknessScale.value_or(1.0f))).c_str());
    return jsonSpanDeclaration->ToString();
}

void TextStyle::AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&, TextStyle&)>&& updateFunc)
{
    CHECK_NULL_VOID(resObj && updateFunc);
    auto& map = resMap_.map_;
    if (!map) {
        map = std::make_unique<std::unordered_map<std::string, resourceUpdater>>();
    }
    (*map)[key] = { resObj, std::move(updateFunc) };
}

const RefPtr<ResourceObject>& TextStyle::GetResource(const std::string& key) const
{
    static const RefPtr<ResourceObject> invalidResObj = nullptr;
    auto& map = resMap_.map_;
    CHECK_NULL_RETURN(map, invalidResObj);
    auto iter = map->find(key);
    return iter == map->end() ? invalidResObj : iter->second.resObj;
}

void TextStyle::CopyResource(const TextStyle& source)
{
    resMap_ = source.resMap_;
}

void TextStyle::AppendResource(const TextStyle& source)
{
    auto& sourceMap = source.resMap_.map_;
    CHECK_NULL_VOID(sourceMap);
    auto& map = resMap_.map_;
    if (!map) {
        map = std::make_unique<std::unordered_map<std::string, resourceUpdater>>();
    }
    map->insert(sourceMap->begin(), sourceMap->end());
}

void TextStyle::ReloadResources()
{
    std::for_each(propTextShadows_.begin(), propTextShadows_.end(), [](Shadow& sd) { sd.ReloadResources(); });
    if (propTextBackgroundStyle_.has_value()) {
        propTextBackgroundStyle_->ReloadResources();
    }
    auto& map = resMap_.map_;
    CHECK_NULL_VOID(map);
    for (const auto& [key, resourceUpdater] : *map) {
        resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
    }
}

std::string TextStyle::ToString() const
{
    auto jsonValue = JsonUtil::Create(true);
    JSON_STRING_PUT_STRINGABLE(jsonValue, fontSize_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, propTextColor_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, lineHeight_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, propBaselineOffset_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, propWordSpacing_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, propTextIndent_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, propLetterSpacing_.value);
    JSON_STRING_PUT_STRINGABLE(jsonValue, lineSpacing_.value);

    JSON_STRING_PUT_INT(jsonValue, fontWeight_);
    JSON_STRING_PUT_INT(jsonValue, propFontStyle_);
    JSON_STRING_PUT_INT(jsonValue, propTextBaseline_);
    JSON_STRING_PUT_INT(jsonValue, propTextOverflow_);
    JSON_STRING_PUT_INT(jsonValue, propTextVerticalAlign_);
    JSON_STRING_PUT_INT(jsonValue, propTextAlign_);
    JSON_STRING_PUT_INT(jsonValue, propTextDecorationStyle_);
    JSON_STRING_PUT_INT(jsonValue, propTextDecoration_.size() > 0 ? propTextDecoration_[0] : TextDecoration::NONE);
    JSON_STRING_PUT_INT(jsonValue, propLineThicknessScale_);
    JSON_STRING_PUT_INT(jsonValue, propWhiteSpace_);
    JSON_STRING_PUT_INT(jsonValue, propWordBreak_);
    JSON_STRING_PUT_INT(jsonValue, propTextCase_);
    JSON_STRING_PUT_INT(jsonValue, propEllipsisMode_);
    JSON_STRING_PUT_INT(jsonValue, propLineBreakStrategy_);

    std::stringstream ss;
    std::for_each(
        propRenderColors_.begin(), propRenderColors_.end(), [&ss](const Color& c) { ss << c.ToString() << ","; });
    jsonValue->Put("renderColors", ss.str().c_str());
    JSON_STRING_PUT_INT(jsonValue, propRenderStrategy_);
    JSON_STRING_PUT_INT(jsonValue, propEffectStrategy_);
    JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, GetInnerSymbolEffectOptions());

    return jsonValue->ToString();
}

void TextStyle::CompareCommonSubType(
    const std::optional<NG::SymbolEffectOptions>& options, const std::optional<NG::SymbolEffectOptions>& oldOptions)
{
    auto newOpts = options.value();
    auto oldOpts = oldOptions.value();
    if (newOpts.GetCommonSubType().has_value()) {
        auto commonType = static_cast<uint16_t>(newOpts.GetCommonSubType().value());
        if (oldOpts.GetCommonSubType().has_value()) {
            auto oldCommonType = static_cast<uint16_t>(oldOpts.GetCommonSubType().value());
            if (commonType != oldCommonType) {
                reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::COMMONSUB_TYPE));
            }
        }
    } else {
        if (oldOpts.GetCommonSubType().has_value()) {
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::COMMONSUB_TYPE));
        }
    }
}

void TextStyle::CompareAnimationMode(
    const std::optional<NG::SymbolEffectOptions>& options, const std::optional<NG::SymbolEffectOptions>& oldOptions)
{
    auto newOpts = options.value();
    auto oldOpts = oldOptions.value();
    auto effectType = newOpts.GetEffectType();
    if (effectType == SymbolEffectType::HIERARCHICAL && newOpts.GetFillStyle().has_value()) {
        if (oldOpts.GetFillStyle().has_value()) {
            if (newOpts.GetFillStyle().value() != oldOpts.GetFillStyle().value()) {
                reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_MODE));
            }
        } else {
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_MODE));
        }
        return;
    }
    if (newOpts.GetScopeType().has_value()) {
        if (oldOpts.GetScopeType().has_value()) {
            if (newOpts.GetScopeType().value() != oldOpts.GetScopeType().value()) {
                reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_MODE));
            }
        } else {
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_MODE));
        }
    }
}

void TextStyle::SetWhenOnlyOneOptionIsValid(const std::optional<NG::SymbolEffectOptions>& options)
{
    auto symbolOptions = options.value();
    if (symbolOptions.GetEffectType() != SymbolEffectType::NONE) {
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::EFFECT_STRATEGY));
    }
    if (symbolOptions.GetIsTxtActive()) {
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_START));
    }
    if (symbolOptions.GetCommonSubType().has_value()) {
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::COMMONSUB_TYPE));
    }
    if (symbolOptions.GetFillStyle().has_value() || symbolOptions.GetScopeType().has_value()) {
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_MODE));
    }
}

void TextStyle::SetSymbolEffectOptions(const std::optional<NG::SymbolEffectOptions>& symbolEffectOptions)
{
    auto innerSymbolEffectOptions = GetInnerSymbolEffectOptions();
    if (symbolEffectOptions.has_value() && innerSymbolEffectOptions.has_value()) {
        auto options = symbolEffectOptions.value();
        auto oldOptions = innerSymbolEffectOptions.value();
        if (oldOptions.GetEffectType() != options.GetEffectType()) {
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::EFFECT_STRATEGY));
        }
        if (oldOptions.GetIsTxtActive() != options.GetIsTxtActive() ||
            (options.GetTriggerNum().has_value() && options.GetIsTxtActive())) {
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::ANIMATION_START));
        }
        CompareCommonSubType(options, oldOptions);
        CompareAnimationMode(options, oldOptions);
    } else {
        if (innerSymbolEffectOptions.has_value()) {
            auto oldOptions = innerSymbolEffectOptions.value();
            SetWhenOnlyOneOptionIsValid(oldOptions);
        }
    }
    SetInnerSymbolEffectOptionsWithoutMark(symbolEffectOptions);
}

void TextStyle::UpdateFontSizeOrColorChanged()
{
    std::bitset<static_cast<size_t>(TextStyleAttribute::MAX_TEXT_STYLE)> allowedMask;
    allowedMask.set(static_cast<int32_t>(TextStyleAttribute::FONT_SIZE));
    allowedMask.set(static_cast<int32_t>(TextStyleAttribute::FONT_COLOR));
    // other properties have also changed.
    if ((reLayoutTextStyleBitmap_ & ~allowedMask).any()) {
        isFontSizeOrColorChanged_ = false;
        return;
    }
    isFontSizeOrColorChanged_ &= (reLayoutTextStyleBitmap_ & allowedMask).any();
}
} // namespace OHOS::Ace
