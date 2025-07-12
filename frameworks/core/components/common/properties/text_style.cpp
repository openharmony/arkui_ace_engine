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
#include "core/components_ng/pattern/text/text_styles.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {
const std::vector<WordBreak> WORD_BREAK_TYPES = {
    WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD, WordBreak::HYPHENATION};
const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES = {
    LineBreakStrategy::GREEDY, LineBreakStrategy::HIGH_QUALITY, LineBreakStrategy::BALANCED};
TextStyle::TextStyle(const std::vector<std::string> &fontFamilies, double fontSize, FontWeight fontWeight,
    FontStyle fontStyle, const Color &textColor)
    : propFontFamilies_(fontFamilies), propFontStyle_(fontStyle), propTextColor_(textColor),
      fontWeight_(fontWeight)
{
    SetFontSize(Dimension(fontSize));
}

bool TextStyle::operator==(const TextStyle &rhs) const
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
           NearEqual(propLineThicknessScale_, rhs.propLineThicknessScale_);
}

bool TextStyle::operator!=(const TextStyle &rhs) const
{
    return !(rhs == *this);
}

void TextStyle::SetAdaptTextSize(
    const Dimension &maxFontSize, const Dimension &minFontSize, const Dimension &fontSizeStep)
{
    adaptMaxFontSize_.value = maxFontSize;
    adaptMinFontSize_.value = minFontSize;
    propAdaptFontSizeStep_.value = fontSizeStep;
    adaptTextSize_ = true;
}

void TextBackgroundStyle::ToJsonValue(std::unique_ptr<JsonValue> &json, const std::optional<TextBackgroundStyle> &style,
    const NG::InspectorFilter &filter)
{
    NG::BorderRadiusProperty defaultRadius;
    TextBackgroundStyle exportStyle = {.backgroundColor = Color::TRANSPARENT, .backgroundRadius = defaultRadius};
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

void TextStyle::ToJsonValue(std::unique_ptr<JsonValue>& json, const std::optional<TextStyle>& style,
                            const NG::InspectorFilter& filter)
{
    CHECK_NULL_VOID(json);
    CHECK_NULL_VOID(style);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("decoration", GetDeclarationString(style->GetTextDecorationColor(), style->GetTextDecoration(),
        style->GetTextDecorationStyle(), style->GetLineThicknessScale()).c_str(), filter);
}

std::string TextStyle::GetDeclarationString(
    const std::optional<Color>& color, const std::vector<TextDecoration>& textDecorations,
    const std::optional<TextDecorationStyle>& textDecorationStyle, const std::optional<float>& lineThicknessScale)
{
    auto jsonSpanDeclaration = JsonUtil::Create(true);
    jsonSpanDeclaration->Put(
        "type", V2::ConvertWrapTextDecorationToStirng(textDecorations).c_str());
    jsonSpanDeclaration->Put("color", (color.value_or(Color::BLACK).ColorToString()).c_str());
    jsonSpanDeclaration->Put("style", V2::ConvertWrapTextDecorationStyleToString(
        textDecorationStyle.value_or(TextDecorationStyle::SOLID)).c_str());
    jsonSpanDeclaration->Put("thicknessScale",
        StringUtils::DoubleToString(static_cast<double>(lineThicknessScale.value_or(1.0f))).c_str());
    return jsonSpanDeclaration->ToString();
}

void TextStyle::UpdateColorByResourceId()
{
    propTextColor_.UpdateColorByResourceId();
    propTextDecorationColor_.UpdateColorByResourceId();
    if (propTextBackgroundStyle_.has_value()) {
        propTextBackgroundStyle_->UpdateColorByResourceId();
    }
    std::for_each(propRenderColors_.begin(), propRenderColors_.end(), [](Color &cl) { cl.UpdateColorByResourceId(); });
    std::for_each(propTextShadows_.begin(), propTextShadows_.end(), [](Shadow &sd) { sd.UpdateColorByResourceId(); });
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
        propRenderColors_.begin(), propRenderColors_.end(), [&ss](const Color &c) { ss << c.ToString() << ","; });
    jsonValue->Put("renderColors", ss.str().c_str());
    JSON_STRING_PUT_INT(jsonValue, propRenderStrategy_);
    JSON_STRING_PUT_INT(jsonValue, propEffectStrategy_);
    JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, GetInnerSymbolEffectOptions());

    return jsonValue->ToString();
}

void TextStyle::CompareCommonSubType(const std::optional<NG::SymbolEffectOptions>& options,
    const std::optional<NG::SymbolEffectOptions>& oldOptions)
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
 
void TextStyle::CompareAnimationMode(const std::optional<NG::SymbolEffectOptions>& options,
    const std::optional<NG::SymbolEffectOptions>& oldOptions)
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
        if (oldOptions.GetIsTxtActive() != options.GetIsTxtActive()) {
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
}  // namespace OHOS::Ace
