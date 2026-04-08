/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_H

#include "advanced_text_style.h"
#include "text_enums.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;
class SymbolEffectOptions;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

struct DimensionWithActual {
    constexpr DimensionWithActual() = default;
    explicit DimensionWithActual(const Dimension& variable, float actual) : value(variable), actualValue(actual) {}
    bool operator==(const DimensionWithActual& rhs) const
    {
        return NearEqual(value, rhs.value) && NearEqual(actualValue, rhs.actualValue, 0.00001f);
    }

    std::string ToString()
    {
        std::stringstream ss;
        ss << "value: " << value.ToString();
        ss << " actualValue: " << std::to_string(actualValue);
        return ss.str();
    }

    void Reset()
    {
        value.Reset();
        actualValue = 0.0f;
    }

    Dimension value;
    float actualValue = 0.0f;
};

struct TextSizeGroup {
    Dimension fontSize = 14.0_px;
    uint32_t maxLines = INT32_MAX;
    TextOverflow textOverflow = TextOverflow::CLIP;
};

/// Placeholder properties
struct PlaceholderRun {
    /// Placeholder's width
    float width = 0.0f;

    /// Placeholder's height
    float height = 0.0f;

    /// Vertically alignment the placeholder relative to the surrounding text.
    PlaceholderAlignment alignment = PlaceholderAlignment::BOTTOM;

    /// The placeholder with the baseline styles
    TextBaseline baseline = TextBaseline::ALPHABETIC;

    /// The baseline offset
    float baseline_offset = 0.0f;

    bool operator==(const PlaceholderRun& value) const
    {
        return width == value.width && height == value.height && alignment == value.alignment &&
               baseline == value.baseline && baseline_offset == value.baseline_offset;
    }

    bool operator!=(const PlaceholderRun& value) const
    {
        return !(value == *this);
    }
};

struct TextBackgroundStyle {
    std::optional<Color> backgroundColor;
    std::optional<NG::BorderRadiusProperty> backgroundRadius;
    int32_t groupId = 0;
    bool needCompareGroupId = true;

    static void ToJsonValue(std::unique_ptr<JsonValue>& json, const std::optional<TextBackgroundStyle>& style,
        const NG::InspectorFilter& filter);

    bool operator==(const TextBackgroundStyle& value) const
    {
        // Only compare groupId if both styles require it.
        bool bothNeedCompareGroupId = needCompareGroupId && value.needCompareGroupId;
        return backgroundColor == value.backgroundColor && backgroundRadius == value.backgroundRadius &&
               (!bothNeedCompareGroupId || groupId == value.groupId);
    }

    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, TextBackgroundStyle&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        textBackgroundStyleResMap_[key] = { resObj, std::move(updateFunc) };
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : textBackgroundStyleResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, TextBackgroundStyle&)> updateFunc;
    };

    void ReloadResourcesByKey(const std::string& key)
    {
        auto res = textBackgroundStyleResMap_.find(key);
        if (res != textBackgroundStyleResMap_.end()) {
            auto resourceUpdater = res->second;
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    bool HasKey(const std::string& key) const
    {
        return textBackgroundStyleResMap_.find(key) != textBackgroundStyleResMap_.end();
    }

    std::unordered_map<std::string, ResourceUpdater> textBackgroundStyleResMap_;
};

// For textStyle
#define ACE_DEFINE_TEXT_STYLE_FUNC(name, type, changeflag)           \
public:                                                              \
    const type& Get##name() const                                    \
    {                                                                \
        return prop##name##_;                                        \
    }                                                                \
    void Set##name(const type& newValue)                             \
    {                                                                \
        if (NearEqual(prop##name##_, newValue)) {                    \
            return;                                                  \
        }                                                            \
        auto flag = static_cast<int32_t>(changeflag);                \
        if (GreatOrEqual(flag, 0)) {                                 \
            reLayoutTextStyleBitmap_.set(static_cast<size_t>(flag)); \
        } else {                                                     \
            needReCreateParagraph_ = true;                           \
        }                                                            \
        prop##name##_ = newValue;                                    \
    }                                                                \
    void Set##name(const std::optional<type>& value)                 \
    {                                                                \
        if (value.has_value()) {                                     \
            Set##name(value.value());                                \
        }                                                            \
    }

#define ACE_DEFINE_TEXT_STYLE(name, type, changeflag)  \
    ACE_DEFINE_TEXT_STYLE_FUNC(name, type, changeflag) \
private:                                               \
    type prop##name##_;

#define ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(name, type, value, changeflag) \
    ACE_DEFINE_TEXT_STYLE_FUNC(name, type, changeflag)                          \
                                                                                \
private:                                                                        \
    type prop##name##_ = value;
// For textStyle
#define ACE_DEFINE_TEXT_DIMENSION_STYLE_FUNC(name, changeflag)                                                \
public:                                                                                                       \
    const Dimension& Get##name() const                                                                        \
    {                                                                                                         \
        return prop##name##_.value;                                                                           \
    }                                                                                                         \
    void Set##name(const Dimension& value)                                                                    \
    {                                                                                                         \
        auto actualValue = value.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale()); \
        auto newValue = DimensionWithActual(value, static_cast<float>(actualValue));                          \
        if (NearEqual(prop##name##_, newValue)) {                                                             \
            return;                                                                                           \
        }                                                                                                     \
        auto flag = static_cast<int32_t>(changeflag);                                                         \
        if (GreatOrEqual(flag, 0)) {                                                                          \
            reLayoutTextStyleBitmap_.set(flag);                                                               \
        } else {                                                                                              \
            needReCreateParagraph_ = true;                                                                    \
        }                                                                                                     \
        prop##name##_ = newValue;                                                                             \
    }

// For textStyle
#define ACE_DEFINE_TEXT_DIMENSION_STYLE(name, changeflag)  \
    ACE_DEFINE_TEXT_DIMENSION_STYLE_FUNC(name, changeflag) \
                                                           \
private:                                                   \
    DimensionWithActual prop##name##_;
// For textStyle
#define ACE_DEFINE_TEXT_DIMENSION_STYLE_WITH_DEFAULT_VALUE(name, defaultValue, actualDefaultValue, changeflag) \
    ACE_DEFINE_TEXT_DIMENSION_STYLE_FUNC(name, changeflag)                                                     \
                                                                                                               \
private:                                                                                                       \
    DimensionWithActual prop##name##_ { defaultValue, actualDefaultValue };

#define ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(name, type, changeflag)   \
public:                                                               \
    const std::optional<type>& Get##name() const                      \
    {                                                                 \
        return prop##name##_;                                         \
    }                                                                 \
    void Set##name(const type& newValue)                              \
    {                                                                 \
        if (prop##name##_.has_value()) {                              \
            if (NearEqual(prop##name##_.value(), newValue)) {         \
                return;                                               \
            }                                                         \
        }                                                             \
        auto flag = static_cast<int32_t>(changeflag);                 \
        if (flag >= 0) {                                              \
            reLayoutTextStyleBitmap_.set(static_cast<size_t>(flag));  \
        } else {                                                      \
            needReCreateParagraph_ = true;                            \
        }                                                             \
        prop##name##_ = newValue;                                     \
    }                                                                 \
    void Set##name(const std::optional<type> newValue)                \
    {                                                                 \
        if (!prop##name##_.has_value() && !newValue.has_value()) {    \
            return;                                                   \
        }                                                             \
        if (prop##name##_.has_value() && newValue.has_value()) {      \
            if (NearEqual(prop##name##_.value(), newValue.value())) { \
                return;                                               \
            }                                                         \
        }                                                             \
        auto flag = static_cast<int32_t>(changeflag);                 \
        if (GreatOrEqual(flag, 0)) {                                  \
            reLayoutTextStyleBitmap_.set(flag);                       \
        } else {                                                      \
            needReCreateParagraph_ = true;                            \
        }                                                             \
        prop##name##_ = newValue;                                     \
    }                                                                 \
                                                                      \
private:                                                              \
    std::optional<type> prop##name##_;

// For paragraphStyle
#define ACE_DEFINE_PARAGRAPH_STYLE(name, type, changeflag)                \
public:                                                                   \
    const type& Get##name() const                                         \
    {                                                                     \
        return prop##name##_;                                             \
    }                                                                     \
    void Set##name(const type& newValue)                                  \
    {                                                                     \
        if (NearEqual(prop##name##_, newValue)) {                         \
            return;                                                       \
        }                                                                 \
        auto flag = static_cast<int32_t>(changeflag);                     \
        if (GreatOrEqual(flag, 0)) {                                      \
            reLayoutParagraphStyleBitmap_.set(static_cast<size_t>(flag)); \
        } else {                                                          \
            needReCreateParagraph_ = true;                                \
        }                                                                 \
        prop##name##_ = newValue;                                         \
    }                                                                     \
                                                                          \
private:                                                                  \
    type prop##name##_;

#define ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(name, type, initValue, changeflag) \
public:                                                                                  \
    const type& Get##name() const                                                        \
    {                                                                                    \
        return prop##name##_;                                                            \
    }                                                                                    \
    void Set##name(const type& newValue)                                                 \
    {                                                                                    \
        if (NearEqual(prop##name##_, newValue)) {                                        \
            return;                                                                      \
        }                                                                                \
        auto flag = static_cast<int32_t>(changeflag);                                    \
        if (GreatOrEqual(flag, 0)) {                                                     \
            reLayoutParagraphStyleBitmap_.set(static_cast<size_t>(flag));                \
        } else {                                                                         \
            needReCreateParagraph_ = true;                                               \
        }                                                                                \
        prop##name##_ = newValue;                                                        \
    }                                                                                    \
    void Set##name(const std::optional<type>& newValue)                                  \
    {                                                                                    \
        if (newValue.has_value()) {                                                      \
            Set##name(newValue.value());                                                 \
        }                                                                                \
    }                                                                                    \
                                                                                         \
private:                                                                                 \
    type prop##name##_ = initValue;

// For symbol
#define ACE_DEFINE_SYMBOL_STYLE(name, type, changeflag) \
public:                                                 \
    const type& Get##name() const                       \
    {                                                   \
        return prop##name##_;                           \
    }                                                   \
    void Set##name(const type& newValue)                \
    {                                                   \
        if (NearEqual(prop##name##_, newValue)) {       \
            return;                                     \
        }                                               \
        auto flag = static_cast<int32_t>(changeflag);   \
        if (GreatOrEqual(flag, 0)) {                    \
            reLayoutSymbolStyleBitmap_.set(flag);       \
        } else {                                        \
            needReCreateParagraph_ = true;              \
        }                                               \
        prop##name##_ = newValue;                       \
    }                                                   \
                                                        \
private:                                                \
    type prop##name##_;

#define ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(name, type, value, changeflag) \
public:                                                                           \
    const type& Get##name() const                                                 \
    {                                                                             \
        return prop##name##_;                                                     \
    }                                                                             \
    void Set##name(const type& newValue)                                          \
    {                                                                             \
        if (NearEqual(prop##name##_, newValue)) {                                 \
            return;                                                               \
        }                                                                         \
        auto flag = static_cast<int32_t>(changeflag);                             \
        if (GreatOrEqual(flag, 0)) {                                              \
            reLayoutSymbolStyleBitmap_.set(flag);                                 \
        } else {                                                                  \
            needReCreateParagraph_ = true;                                        \
        }                                                                         \
        prop##name##_ = newValue;                                                 \
    }                                                                             \
                                                                                  \
private:                                                                          \
    type prop##name##_ = value;

#define ACE_DEFINE_ADVANCED_TEXT_STYLE_OPTIONAL_TYPE(name, type)                     \
public:                                                                              \
    std::optional<type> Get##name() const                                            \
    {                                                                                \
        CHECK_NULL_RETURN(advancedTextStyle_, std::nullopt);                         \
        return advancedTextStyle_->Get##name();                                      \
    }                                                                                \
    void Set##name(const type& newValue)                                             \
    {                                                                                \
        if (!advancedTextStyle_) {                                                   \
            advancedTextStyle_ = AceType::MakeRefPtr<AdvancedTextStyle>();           \
        }                                                                            \
        CHECK_NULL_VOID(advancedTextStyle_);                                         \
        advancedTextStyle_->Set##name(newValue);                                     \
    }                                                                                \
    void Set##name(const std::optional<type> newValue)                               \
    {                                                                                \
        if (!advancedTextStyle_ && !newValue.has_value()) {                          \
            return;                                                                  \
        }                                                                            \
        if (!advancedTextStyle_) {                                                   \
            advancedTextStyle_ = AceType::MakeRefPtr<AdvancedTextStyle>();           \
        }                                                                            \
        CHECK_NULL_VOID(advancedTextStyle_);                                         \
        if (!advancedTextStyle_->Get##name().has_value() && !newValue.has_value()) { \
            return;                                                                  \
        }                                                                            \
        advancedTextStyle_->Set##name(newValue);                                     \
    }

#define ACE_DEFINE_ADVANCED_TEXT_STYLE_OPTIONAL_TYPE_WITH_FLAG(name, type, changeflag)  \
    std::optional<type> Get##name() const                                               \
    {                                                                                   \
        CHECK_NULL_RETURN(advancedTextStyle_, std::nullopt);                            \
        return advancedTextStyle_->Get##name();                                         \
    }                                                                                   \
    void Set##name(const type& newValue)                                                \
    {                                                                                   \
        if (!advancedTextStyle_) {                                                      \
            advancedTextStyle_ = AceType::MakeRefPtr<AdvancedTextStyle>();              \
        }                                                                               \
        CHECK_NULL_VOID(advancedTextStyle_);                                            \
        if (Has##name()) {                                                              \
            if (NearEqual(advancedTextStyle_->Get##name().value(), newValue)) {         \
                return;                                                                 \
            }                                                                           \
        }                                                                               \
        advancedTextStyle_->Set##name(newValue);                                        \
        auto flag = static_cast<int32_t>(changeflag);                                   \
        if (GreatOrEqual(flag, 0)) {                                                    \
            reLayoutParagraphStyleBitmap_.set(flag);                                    \
        } else {                                                                        \
            needReCreateParagraph_ = true;                                              \
        }                                                                               \
    }                                                                                   \
    void Set##name(const std::optional<type> newValue)                                  \
    {                                                                                   \
        if (!advancedTextStyle_ && !newValue.has_value()) {                             \
            return;                                                                     \
        }                                                                               \
        if (!advancedTextStyle_) {                                                      \
            advancedTextStyle_ = AceType::MakeRefPtr<AdvancedTextStyle>();              \
        }                                                                               \
        CHECK_NULL_VOID(advancedTextStyle_);                                            \
        if (!advancedTextStyle_->Get##name().has_value() && !newValue.has_value()) {    \
            return;                                                                     \
        }                                                                               \
        if (Has##name() && newValue.has_value()) {                                      \
            if (NearEqual(advancedTextStyle_->Get##name().value(), newValue.value())) { \
                return;                                                                 \
            }                                                                           \
        }                                                                               \
        advancedTextStyle_->Set##name(newValue);                                        \
        auto flag = static_cast<int32_t>(changeflag);                                   \
        if (GreatOrEqual(flag, 0)) {                                                    \
            reLayoutParagraphStyleBitmap_.set(flag);                                    \
        } else {                                                                        \
            needReCreateParagraph_ = true;                                              \
        }                                                                               \
    }                                                                                   \
    bool Has##name() const                                                              \
    {                                                                                   \
        CHECK_NULL_RETURN(advancedTextStyle_, false);                                   \
        return advancedTextStyle_->Get##name().has_value();                             \
    }                                                                                   \
    const type& Get##name##Value(const type& defaultValue) const                        \
    {                                                                                   \
        if (!Has##name()) {                                                             \
            return defaultValue;                                                        \
        }                                                                               \
        return advancedTextStyle_->Get##name().value();                                 \
    }

#define ACE_DEFINE_SYMBOL_TEXT_STYLE_OPTIONAL_TYPE(name, type)                        \
    std::optional<type> Get##name() const                                             \
    {                                                                                 \
        CHECK_NULL_RETURN(symbolTextStyle_, std::nullopt);                            \
        return symbolTextStyle_->Get##name();                                         \
    }                                                                                 \
    void Set##name(const type& newValue)                                              \
    {                                                                                 \
        if (!symbolTextStyle_) {                                                      \
            symbolTextStyle_ = AceType::MakeRefPtr<SymbolTextStyle>();                \
        }                                                                             \
        CHECK_NULL_VOID(symbolTextStyle_);                                            \
        if (Has##name()) {                                                            \
            if (NearEqual(symbolTextStyle_->Get##name().value(), newValue)) {         \
                return;                                                               \
            }                                                                         \
        }                                                                             \
        symbolTextStyle_->Set##name(newValue);                                        \
    }                                                                                 \
    void Set##name(const std::optional<type> newValue)                                \
    {                                                                                 \
        if (!symbolTextStyle_ && !newValue.has_value()) {                             \
            return;                                                                   \
        }                                                                             \
        if (!symbolTextStyle_) {                                                      \
            symbolTextStyle_ = AceType::MakeRefPtr<SymbolTextStyle>();                \
        }                                                                             \
        CHECK_NULL_VOID(symbolTextStyle_);                                            \
        if (!symbolTextStyle_->Get##name().has_value() && !newValue.has_value()) {    \
            return;                                                                   \
        }                                                                             \
        if (Has##name() && newValue.has_value()) {                                    \
            if (NearEqual(symbolTextStyle_->Get##name().value(), newValue.value())) { \
                return;                                                               \
            }                                                                         \
        }                                                                             \
        symbolTextStyle_->Set##name(newValue);                                        \
    }                                                                                 \
    bool Has##name() const                                                            \
    {                                                                                 \
        CHECK_NULL_RETURN(symbolTextStyle_, false);                                   \
        return symbolTextStyle_->Get##name().has_value();                             \
    }                                                                                 \
    const type& Get##name##Value(const type& defaultValue) const                      \
    {                                                                                 \
        if (!Has##name()) {                                                           \
            return defaultValue;                                                      \
        }                                                                             \
        return symbolTextStyle_->Get##name().value();                                 \
    }                                                                                 \
    void Set##name##WithoutMark(const std::optional<type> newValue)                   \
    {                                                                                 \
        if (!symbolTextStyle_ && !newValue.has_value()) {                             \
            return;                                                                   \
        }                                                                             \
        if (!symbolTextStyle_) {                                                      \
            symbolTextStyle_ = AceType::MakeRefPtr<SymbolTextStyle>();                \
        }                                                                             \
        CHECK_NULL_VOID(symbolTextStyle_);                                            \
        if (!symbolTextStyle_->Get##name().has_value() && !newValue.has_value()) {    \
            return;                                                                   \
        }                                                                             \
        if (Has##name() && newValue.has_value()) {                                    \
            if (NearEqual(symbolTextStyle_->Get##name().value(), newValue.value())) { \
                return;                                                               \
            }                                                                         \
        }                                                                             \
        symbolTextStyle_->Set##name(newValue);                                        \
    }

// implement lazy loading and deep copy
template<class K, class V>
class ResourceMap {
public:
    ResourceMap() = default;
    ResourceMap(const ResourceMap<K, V>& other)
    {
        CopyMap(other);
    }
    ResourceMap& operator=(const ResourceMap<K, V>& other)
    {
        CopyMap(other);
        return *this;
    }
    size_t Size()
    {
        return map_ ? map_->size() : 0;
    }
    std::unique_ptr<std::unordered_map<K, V>> map_;

private:
    void CopyMap(const ResourceMap<K, V>& other)
    {
        if (other.map_) {
            map_ = std::make_unique<std::unordered_map<K, V>>(*other.map_);
        } else {
            map_.reset();
        }
    }
};

ACE_FORCE_EXPORT FontWeight ConvertFontWeight(FontWeight fontWeight);

class ACE_EXPORT TextStyle final {
public:
    TextStyle() = default;
    TextStyle(const std::vector<std::string>& fontFamilies, double fontSize, FontWeight fontWeight, FontStyle fontStyle,
        const Color& textColor);
    TextStyle(double fontSize)
    {
        SetFontSize(Dimension(fontSize));
    }
    TextStyle(const Color& textColor) : propTextColor_(textColor) {}
    ~TextStyle() = default;

    ACE_FORCE_EXPORT bool operator==(const TextStyle& rhs) const;
    ACE_FORCE_EXPORT bool operator!=(const TextStyle& rhs) const;

    static void ToJsonValue(
        std::unique_ptr<JsonValue>& json, const std::optional<TextStyle>& style, const NG::InspectorFilter& filter);

    static std::string GetDeclarationString(const std::optional<Color>& color,
        const std::vector<TextDecoration>& textDecorations,
        const std::optional<TextDecorationStyle>& textDecorationStyle, const std::optional<float>& lineThicknessScale);

    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        TextBaseline, TextBaseline, TextBaseline::ALPHABETIC, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_DIMENSION_STYLE(BaselineOffset, TextStyleAttribute::BASELINE_SHIFT);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        TextDecoration, std::vector<TextDecoration>, { TextDecoration::NONE }, TextStyleAttribute::DECRATION);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        TextDecorationStyle, TextDecorationStyle, TextDecorationStyle::SOLID, TextStyleAttribute::DECORATION_STYLE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        TextDecorationColor, Color, Color::BLACK, TextStyleAttribute::DECORATION_COLOR);
    ACE_DEFINE_TEXT_STYLE(FontFamilies, std::vector<std::string>, TextStyleAttribute::FONT_FAMILIES);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(FontStyle, FontStyle, FontStyle::NORMAL, TextStyleAttribute::FONT_STYLE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(WhiteSpace, WhiteSpace, WhiteSpace::PRE, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(MaxFontScale, float, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(MinFontScale, float, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(VariableFontWeight, int32_t, 0, TextStyleAttribute::FONT_VARIATIONS);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        EnableVariableFontWeight, bool, false, TextStyleAttribute::FONT_VARIATIONS);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        EnableDeviceFontWeightCategory, bool, true, TextStyleAttribute::FONT_VARIATIONS);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(TextColor, Color, Color::BLACK, TextStyleAttribute::FONT_COLOR);
    ACE_DEFINE_TEXT_DIMENSION_STYLE(WordSpacing, TextStyleAttribute::WORD_SPACING);
    ACE_DEFINE_TEXT_DIMENSION_STYLE_WITH_DEFAULT_VALUE(
        TextIndent, Dimension(0.0f, DimensionUnit::PX), 0.0f, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(LineHeightMultiply, double, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(MinimumLineHeight, Dimension, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(MaximumLineHeight, Dimension, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_DIMENSION_STYLE(LetterSpacing, TextStyleAttribute::LETTER_SPACING);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(MaxLines, uint32_t, UINT32_MAX, ParagraphStyleAttribute::MAXLINES);
    // Must use with SetAdaptMinFontSize and SetAdaptMaxFontSize.
    ACE_DEFINE_TEXT_DIMENSION_STYLE(AdaptFontSizeStep, TextStyleAttribute::FONT_SIZE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(AllowScale, bool, true, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        TextOverflow, TextOverflow, TextOverflow::CLIP, ParagraphStyleAttribute::ELLIPSIS);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        TextAlign, TextAlign, TextAlign::START, ParagraphStyleAttribute::TEXT_ALIGN);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        TextVerticalAlign, VerticalAlign, VerticalAlign::NONE, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        ParagraphVerticalAlign, TextVerticalAlign, TextVerticalAlign::BASELINE, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        WordBreak, WordBreak, WordBreak::BREAK_WORD, ParagraphStyleAttribute::WORD_BREAKTYPE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(TextCase, TextCase, TextCase::NORMAL, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE(TextShadows, std::vector<Shadow>, TextStyleAttribute::SHADOWS);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(HalfLeading, bool, false, TextStyleAttribute::HALF_LEADING);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        IsOnlyBetweenLines, bool, false, ParagraphStyleAttribute::TEXT_HEIGHT_BEHAVIOR);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        EllipsisMode, EllipsisMode, EllipsisMode::TAIL, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE(Locale, std::string, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(TextBackgroundStyle, TextBackgroundStyle, TextStyleAttribute::BACKGROUND_RECT);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        LineBreakStrategy, LineBreakStrategy, LineBreakStrategy::GREEDY, ParagraphStyleAttribute::BREAKSTRAGY);
    ACE_DEFINE_PARAGRAPH_STYLE(Ellipsis, std::u16string, ParagraphStyleAttribute::ELLIPSIS);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(HeightScale, double, 1.0, TextStyleAttribute::HEIGHT_SCALE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        TextDirection, TextDirection, TextDirection::AUTO, ParagraphStyleAttribute::DIRECTION);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(HeightOnly, bool, false, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        OptimizeTrailingSpace, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        StrokeWidth, Dimension, Dimension(0.0f, DimensionUnit::PX), TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE(StrokeColor, Color, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        Superscript, SuperscriptStyle, SuperscriptStyle::NORMAL, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        LineThicknessScale, float, 1.0f, TextStyleAttribute::DECORATION_THICKNESS_SCALE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        OrphanCharOptimization, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(
        CompressLeadingPunctuation, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(EnableAutoSpacing, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_OPTIONAL_TYPE(ColorShaderStyle, Color, TextStyleAttribute::FOREGROUND_BRUSH);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(IncludeFontPadding, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(FallbackLineSpacing, bool, false, ParagraphStyleAttribute::RE_CREATE);

    // for Symbol
    ACE_DEFINE_SYMBOL_STYLE(RenderColors, std::vector<Color>, SymbolStyleAttribute::COLOR_LIST);
    ACE_DEFINE_SYMBOL_STYLE(GradientColorProp, std::vector<SymbolGradient>, SymbolStyleAttribute::GRADIENT_COLOR);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(RenderStrategy, int32_t, 0, SymbolStyleAttribute::RENDER_MODE);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(EffectStrategy, int32_t, 0, SymbolStyleAttribute::EFFECT_STRATEGY);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(
        SymbolType, SymbolType, SymbolType::SYSTEM, SymbolStyleAttribute::RE_CREATE);
    ACE_DEFINE_ADVANCED_TEXT_STYLE_OPTIONAL_TYPE(Gradient, Gradient);

public:
    ACE_DEFINE_ADVANCED_TEXT_STYLE_OPTIONAL_TYPE_WITH_FLAG(
        FontForegroudGradiantColor, FontForegroudGradiantColor, TextStyleAttribute::RE_CREATE);

    void SetFontSize(const Dimension& fontSize)
    {
        auto actualValue = fontSize.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale());
        auto newValue = DimensionWithActual(fontSize, static_cast<float>(actualValue));
        if (NearEqual(newValue, fontSize_)) {
            return;
        }
        fontSize_ = newValue;
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_SIZE));
        reLayoutParagraphStyleBitmap_.set(static_cast<int32_t>(ParagraphStyleAttribute::FONT_SIZE));
        if (lineSpacing_.value.IsValid() || hasHeightOverride_) {
            reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_SCALE));
            reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_ONLY));
        }
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_.value;
    }

    float GetFontSizeActual()
    {
        return fontSize_.actualValue;
    }

    void ResetTextBaselineOffset()
    {
        propBaselineOffset_.Reset();
        reLayoutTextStyleBitmap_.reset(static_cast<int32_t>(TextStyleAttribute::BASELINE_SHIFT));
    }

    FontWeight GetFontWeight() const
    {
        return fontWeight_;
    }

    void SetFontWeight(FontWeight fontWeight)
    {
        auto before = ConvertFontWeight(fontWeight_);
        auto after = ConvertFontWeight(fontWeight);
        fontWeight_ = fontWeight;
        if (NearEqual(before, after)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_WEIGHT));
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_VARIATIONS));
    }

    void SetFontWeight(const std::optional<FontWeight>& fontWeight) const
    {
        if (fontWeight.has_value()) {
            SetFontWeight(fontWeight.value());
        }
    }

    const std::list<std::pair<std::string, int32_t>>& GetFontFeatures() const
    {
        return fontFeatures_;
    }

    void SetFontFeatures(const std::list<std::pair<std::string, int32_t>>& fontFeatures)
    {
        if (NearEqual(fontFeatures, fontFeatures_)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_FEATURES));
        fontFeatures_ = fontFeatures;
    }

    void SetFontFeatures(const std::optional<std::list<std::pair<std::string, int32_t>>>& fontFeatures)
    {
        if (fontFeatures.has_value()) {
            SetFontFeatures(fontFeatures.value());
        }
    }

    const Dimension& GetLineHeight() const
    {
        return lineHeight_.value;
    }

    void SetLineHeight(const Dimension& lineHeight, bool hasHeightOverride = true)
    {
        auto actualValue = lineHeight.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale());
        auto newValue = DimensionWithActual(lineHeight, static_cast<float>(actualValue));
        if (NearEqual(newValue, lineHeight_)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_SCALE));
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_ONLY));
        lineHeight_ = newValue;
        hasHeightOverride_ = hasHeightOverride;
    }

    void SetTextDecoration(TextDecoration value)
    {
        std::vector<TextDecoration> array { value };
        SetTextDecoration(array);
    }

    TextDecoration GetTextDecorationFirst() const
    {
        return GetTextDecoration().size() > 0 ? GetTextDecoration()[0] : TextDecoration::NONE;
    }

    const Dimension& GetParagraphSpacing() const
    {
        return paragraphSpacing_;
    }

    void SetParagraphSpacing(const Dimension& paragraphSpacing)
    {
        if (NearEqual(paragraphSpacing_, paragraphSpacing)) {
            return;
        }
        paragraphSpacing_ = paragraphSpacing;
        needReCreateParagraph_ = true;
    }

    const Dimension& GetLineSpacing() const
    {
        return lineSpacing_.value;
    }

    void SetLineSpacing(const Dimension& lineSpacing)
    {
        auto actualValue = lineSpacing.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale());
        auto newValue = DimensionWithActual(lineSpacing, static_cast<float>(actualValue));
        if (NearEqual(newValue, lineSpacing_)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_SCALE));
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::HEIGHT_ONLY));
        lineSpacing_ = newValue;
    }

    bool HasHeightOverride() const
    {
        return hasHeightOverride_;
    }

    bool GetAdaptTextSize() const
    {
        return adaptTextSize_;
    }

    void DisableAdaptTextSize()
    {
        adaptTextSize_ = false;
    }

    void SetAdaptTextSize(bool value)
    {
        adaptTextSize_ = value;
    }

    // Only used in old frames.
    // start
    ACE_FORCE_EXPORT void SetAdaptTextSize(
        const Dimension& maxFontSize, const Dimension& minFontSize, const Dimension& fontSizeStep = 1.0_px);

    bool GetAdaptHeight() const
    {
        return adaptHeight_;
    }

    void SetAdaptHeight(bool adaptHeight)
    {
        adaptHeight_ = adaptHeight;
    }

    void SetPreferFontSizes(const std::vector<Dimension>& preferFontSizes)
    {
        preferFontSizes_ = preferFontSizes;
        adaptTextSize_ = true;
    }

    const std::vector<Dimension>& GetPreferFontSizes() const
    {
        return preferFontSizes_;
    }

    const std::vector<TextSizeGroup>& GetPreferTextSizeGroups() const
    {
        return preferTextSizeGroups_;
    }

    void SetPreferTextSizeGroups(const std::vector<TextSizeGroup>& preferTextSizeGroups)
    {
        preferTextSizeGroups_ = preferTextSizeGroups;
        adaptTextSize_ = true;
    } // end

    // Must use with SetAdaptMaxFontSize.
    void SetAdaptMinFontSize(const Dimension& adaptMinFontSize)
    {
        auto actualValue = adaptMinFontSize.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale());
        auto newValue = DimensionWithActual(adaptMinFontSize, static_cast<float>(actualValue));
        if (NearEqual(newValue, adaptMinFontSize_)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_SIZE));
        adaptMinFontSize_ = newValue;
        adaptTextSize_ = true;
    }
    // Must use with SetAdaptMinFontSize.
    void SetAdaptMaxFontSize(const Dimension& adaptMaxFontSize)
    {
        auto actualValue = adaptMaxFontSize.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale(), IsAllowScale());
        auto newValue = DimensionWithActual(adaptMaxFontSize, static_cast<float>(actualValue));
        if (NearEqual(newValue, adaptMaxFontSize_)) {
            return;
        }
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FONT_SIZE));
        adaptMaxFontSize_ = newValue;
        adaptTextSize_ = true;
    }

    const Dimension& GetAdaptMinFontSize() const
    {
        return adaptMinFontSize_.value;
    }

    const Dimension& GetAdaptMaxFontSize() const
    {
        return adaptMaxFontSize_.value;
    }

    bool IsAllowScale() const
    {
        return propAllowScale_;
    }

    void SetShadow(const Shadow& shadow)
    {
        propTextShadows_.emplace_back(shadow);
    }

    bool isSymbolGlyph_ = false;

    void SetSymbolColorList(const std::vector<Color>& renderColors)
    {
        if (NearEqual(propRenderColors_, renderColors)) {
            return;
        }
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::COLOR_LIST));
        propRenderColors_ = renderColors;
    }

    const std::vector<Color>& GetSymbolColorList() const
    {
        return propRenderColors_;
    }

    std::vector<Color>& GetSymbolColorListRef()
    {
        return propRenderColors_;
    }

    void CompareCommonSubType(const std::optional<NG::SymbolEffectOptions>& options,
        const std::optional<NG::SymbolEffectOptions>& oldOptions);
    void CompareAnimationMode(const std::optional<NG::SymbolEffectOptions>& options,
        const std::optional<NG::SymbolEffectOptions>& oldOptions);
    void SetWhenOnlyOneOptionIsValid(const std::optional<NG::SymbolEffectOptions>& options);
    void SetSymbolEffectOptions(const std::optional<NG::SymbolEffectOptions>& symbolEffectOptions);

    const std::optional<NG::SymbolEffectOptions> GetSymbolEffectOptions() const
    {
        return GetInnerSymbolEffectOptions();
    }

    ACE_FORCE_EXPORT std::string ToString() const;

    const std::bitset<static_cast<size_t>(TextStyleAttribute::MAX_TEXT_STYLE)>& GetReLayoutTextStyleBitmap() const
    {
        return reLayoutTextStyleBitmap_;
    }

    const std::bitset<static_cast<size_t>(ParagraphStyleAttribute::MAX_TEXT_STYLE)>&
    GetReLayoutParagraphStyleBitmap() const
    {
        return reLayoutParagraphStyleBitmap_;
    }

    const std::bitset<static_cast<size_t>(SymbolStyleAttribute::MAX_SYMBOL_STYLE)>& GetReLayoutSymbolStyleBitmap() const
    {
        return reLayoutSymbolStyleBitmap_;
    }

    bool NeedReLayout() const
    {
        return reLayoutTextStyleBitmap_.any() || reLayoutParagraphStyleBitmap_.any() ||
               reLayoutSymbolStyleBitmap_.any();
    }

    bool NeedReCreateParagraph() const
    {
        return needReCreateParagraph_;
    }

    void ResetReCreateAndReLayoutBitmap()
    {
        reLayoutTextStyleBitmap_.reset();
        reLayoutParagraphStyleBitmap_.reset();
        reLayoutSymbolStyleBitmap_.reset();
        needReCreateParagraph_ = false;
    }

    int32_t GetTextStyleUid() const
    {
        return textStyleUid_;
    }

    void SetTextStyleUid(int32_t textStyleUid)
    {
        textStyleUid_ = textStyleUid;
    }

    int32_t GetSymbolUid() const
    {
        return symbolUid_;
    }

    void SetSymbolUid(int32_t symbolUid)
    {
        symbolUid_ = symbolUid;
    }

    void SetSymbolShadow(const SymbolShadow& symbolShadow)
    {
        if (GetInnerSymbolShadowProp().has_value() && GetInnerSymbolShadowProp().value() == symbolShadow) {
            return;
        }
        SetInnerSymbolShadowProp(symbolShadow);
        reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::SYMBOL_SHADOW));
    }

    SymbolShadow GetSymbolShadow() const
    {
        return GetInnerSymbolShadowProp().value_or(SymbolShadow());
    }

    void SetShaderStyle(const std::vector<SymbolGradient>& shaderStyle)
    {
        if (propGradientColorProp_ != shaderStyle) {
            propGradientColorProp_ = shaderStyle;
            reLayoutSymbolStyleBitmap_.set(static_cast<int32_t>(SymbolStyleAttribute::GRADIENT_COLOR));
        }
    }

    std::vector<SymbolGradient> GetShaderStyle() const
    {
        return propGradientColorProp_;
    }

    void SetForeGroundBrushBitMap()
    {
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FOREGROUND_BRUSH));
    }

    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, TextStyle&)>&& updateFunc);
    ACE_FORCE_EXPORT const RefPtr<ResourceObject>& GetResource(const std::string& key) const;
    ACE_FORCE_EXPORT void CopyResource(const TextStyle& source);
    void AppendResource(const TextStyle& source);
    ACE_FORCE_EXPORT void ReloadResources();
    void UpdateFontSizeOrColorChanged();
    bool CheckIsFontSizeOrColorChanged()
    {
        bool changed = isFontSizeOrColorChanged_;
        isFontSizeOrColorChanged_ = true;
        return changed;
    }

private:
    ACE_DEFINE_SYMBOL_TEXT_STYLE_OPTIONAL_TYPE(InnerSymbolEffectOptions, NG::SymbolEffectOptions);
    ACE_DEFINE_SYMBOL_TEXT_STYLE_OPTIONAL_TYPE(InnerSymbolShadowProp, SymbolShadow);
    std::bitset<static_cast<size_t>(TextStyleAttribute::MAX_TEXT_STYLE)> reLayoutTextStyleBitmap_;
    std::bitset<static_cast<size_t>(ParagraphStyleAttribute::MAX_TEXT_STYLE)> reLayoutParagraphStyleBitmap_;
    std::bitset<static_cast<size_t>(SymbolStyleAttribute::MAX_SYMBOL_STYLE)> reLayoutSymbolStyleBitmap_;
    bool needReCreateParagraph_ = false;
    int32_t textStyleUid_ = 0;
    int32_t symbolUid_ = 0;
    std::list<std::pair<std::string, int32_t>> fontFeatures_;
    std::vector<Dimension> preferFontSizes_;
    std::vector<TextSizeGroup> preferTextSizeGroups_;
    // use 14px for normal font size.
    DimensionWithActual fontSize_ { Dimension(14, DimensionUnit::PX), 14.0f };
    FontWeight fontWeight_ { FontWeight::NORMAL };

    DimensionWithActual adaptMinFontSize_;
    DimensionWithActual adaptMaxFontSize_;
    DimensionWithActual lineHeight_;
    DimensionWithActual lineSpacing_;
    Dimension paragraphSpacing_ { 0.0f, DimensionUnit::PX };
    bool hasHeightOverride_ = false;
    bool adaptTextSize_ = false;
    bool adaptHeight_ = false; // whether adjust text size with height.
    bool isFontSizeOrColorChanged_ = true;

    RefPtr<AdvancedTextStyle> advancedTextStyle_;
    RefPtr<SymbolTextStyle> symbolTextStyle_;

    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, TextStyle&)> updateFunc;
    };
    ResourceMap<std::string, resourceUpdater> resMap_;
};

namespace StringUtils {

ACE_FORCE_EXPORT std::pair<bool, FontWeight> ParseFontWeight(
    const std::string& weight, FontWeight defaultFontWeight = FontWeight::NORMAL);

ACE_FORCE_EXPORT FontWeight StringToFontWeight(
    const std::string& weight, FontWeight defaultFontWeight = FontWeight::NORMAL);

ACE_FORCE_EXPORT WordBreak StringToWordBreak(const std::string& wordBreak);

ACE_FORCE_EXPORT int32_t GetFontWeightNumericValue(FontWeight fontWeight);

ACE_FORCE_EXPORT std::string FontWeightToString(const FontWeight& fontWeight);

ACE_FORCE_EXPORT std::string ToString(const FontWeight& fontWeight);

ACE_FORCE_EXPORT std::string SymbolColorListToString(const std::vector<Color>& colorList);

ACE_FORCE_EXPORT std::string SymbolColorListToStringWithHolder(const std::vector<Color>& colorList);
} // namespace StringUtils
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_H
