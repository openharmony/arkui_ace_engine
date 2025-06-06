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

#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/linear_map.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/border_property.h"
#include "core/pipeline/base/render_component.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "frameworks/core/components/common/properties/decoration.h"

namespace OHOS::Ace {
// The normal weight is W400, the larger the number after W, the thicker the font will be.
// BOLD is equal to W700 and NORMAL is equal to W400, lighter is W100, BOLDER is W900.
enum class FontWeight {
    W100 = 0,
    W200,
    W300,
    W400,
    W500,
    W600,
    W700,
    W800,
    W900,
    BOLD,
    NORMAL,
    BOLDER,
    LIGHTER,
    MEDIUM,
    REGULAR,
};

namespace {
const FontWeight FONT_WEIGHT_CONVERT_MAP[] = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::W700,       // FontWeight::BOLD
    FontWeight::W400,       // FontWeight::NORMAL
    FontWeight::W900,       // FontWeight::BOLDER,
    FontWeight::W100,       // FontWeight::LIGHTER
    FontWeight::W500,       // FontWeight::MEDIUM
    FontWeight::W400,       // FontWeight::REGULAR
};

inline FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    int index = static_cast<int>(fontWeight);
    if (index >= 0 && index < static_cast<int>(sizeof(FONT_WEIGHT_CONVERT_MAP) / sizeof(FontWeight))) {
        return FONT_WEIGHT_CONVERT_MAP[index];
    }
    // 返回默认值，例如 FontWeight::W400
    return FontWeight::W400;
}
} // namespace

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

constexpr uint32_t DEFAULT_MAX_FONT_FAMILY_LENGTH = Infinity<uint32_t>();

enum class FontStyle {
    NORMAL,
    ITALIC,
    NONE
};

struct FontForegroudGradiantColor {
    std::vector<NG::PointF> points;
    std::vector<float> scalars;
    std::vector<Color> colors;

    bool IsValid() const
    {
        // 2 points including begin and end
        return points.size() == 2 && scalars.size() == colors.size();
    }

    bool operator==(const FontForegroudGradiantColor& fontForegroudGradiantColor) const
    {
        auto isScalarEq = true;
        if (scalars.size() != fontForegroudGradiantColor.scalars.size()) {
            isScalarEq = false;
        }
        for (size_t i = 0; i < scalars.size() && isScalarEq; i++) {
            isScalarEq = NearEqual(scalars[i], fontForegroudGradiantColor.scalars[i]);
        }
        return isScalarEq && (points == fontForegroudGradiantColor.points) &&
               (colors == fontForegroudGradiantColor.colors);
    }
};

enum class SuperscriptStyle {
    NORMAL,
    SUPERSCRIPT,
    SUBSCRIPT,
    NONE
};

namespace StringUtils {
inline std::string ToString(const FontStyle& fontStyle)
{
    static const LinearEnumMapNode<FontStyle, std::string> table[] = {
        { FontStyle::NORMAL, "NORMAL" },
        { FontStyle::ITALIC, "ITALIC" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), fontStyle);
    return iter != -1 ? table[iter].value : "";
}

inline std::string ToStringNDK(const FontStyle& fontStyle)
{
    static const LinearEnumMapNode<FontStyle, std::string> table[] = {
        { FontStyle::NORMAL, "normal" },
        { FontStyle::ITALIC, "italic" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), fontStyle);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class TextBaseline {
    ALPHABETIC,
    IDEOGRAPHIC,
    TOP,
    BOTTOM,
    MIDDLE,
    HANGING,
};

namespace StringUtils {
inline std::string ToString(const TextBaseline& textBaseline)
{
    static const LinearEnumMapNode<TextBaseline, std::string> table[] = {
        { TextBaseline::ALPHABETIC, "ALPHABETIC" },
        { TextBaseline::IDEOGRAPHIC, "IDEOGRAPHIC" },
        { TextBaseline::TOP, "TOP" },
        { TextBaseline::BOTTOM, "BOTTOM" },
        { TextBaseline::MIDDLE, "MIDDLE" },
        { TextBaseline::HANGING, "HANGING" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textBaseline);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class TextCase {
    NORMAL = 0,
    LOWERCASE,
    UPPERCASE,
};

namespace StringUtils {
inline std::string ToString(const TextCase& textCase)
{
    static const LinearEnumMapNode<TextCase, std::string> table[] = {
        { TextCase::NORMAL, "NORMAL" },
        { TextCase::LOWERCASE, "LOWERCASE" },
        { TextCase::UPPERCASE, "UPPERCASE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textCase);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class EllipsisMode {
    HEAD,
    MIDDLE,
    TAIL,
};

namespace StringUtils {
inline std::string ToString(const EllipsisMode& ellipsisMode)
{
    static const LinearEnumMapNode<EllipsisMode, std::string> table[] = {
        { EllipsisMode::HEAD, "HEAD" },
        { EllipsisMode::MIDDLE, "MIDDLE" },
        { EllipsisMode::TAIL, "TAIL" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), ellipsisMode);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class WordBreak { NORMAL = 0, BREAK_ALL, BREAK_WORD, HYPHENATION };
extern const std::vector<WordBreak> WORD_BREAK_TYPES;
extern const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES;
namespace StringUtils {
inline std::string ToString(const WordBreak& wordBreak)
{
    static const LinearEnumMapNode<WordBreak, std::string> table[] = {
        { WordBreak::NORMAL, "NORMAL" },
        { WordBreak::BREAK_ALL, "BREAK_ALL" },
        { WordBreak::BREAK_WORD, "BREAK_WORD" },
        { WordBreak::HYPHENATION, "HYPHENATION" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), wordBreak);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

/// Where to vertically align the placeholder relative to the surrounding text.
enum class PlaceholderAlignment {
    /// Match the baseline of the placeholder with the baseline.
    BASELINE,

    /// Align the bottom edge of the placeholder with the baseline such that the
    /// placeholder sits on top of the baseline.
    ABOVEBASELINE,

    /// Align the top edge of the placeholder with the baseline specified in
    /// such that the placeholder hangs below the baseline.
    BELOWBASELINE,

    /// Align the top edge of the placeholder with the top edge of the font.
    /// When the placeholder is very tall, the extra space will hang from
    /// the top and extend through the bottom of the line.
    TOP,

    /// Align the bottom edge of the placeholder with the top edge of the font.
    /// When the placeholder is very tall, the extra space will rise from
    /// the bottom and extend through the top of the line.
    BOTTOM,

    /// Align the middle of the placeholder with the middle of the text. When the
    /// placeholder is very tall, the extra space will grow equally from
    /// the top and bottom of the line.
    MIDDLE,

    /// Same alignment as Text.
    FOLLOW_PARAGRAPH,
};

namespace StringUtils {
inline std::string ToString(const PlaceholderAlignment& placeholderAlignment)
{
    static const LinearEnumMapNode<PlaceholderAlignment, std::string> table[] = {
        { PlaceholderAlignment::BASELINE, "BASELINE" },
        { PlaceholderAlignment::ABOVEBASELINE, "ABOVEBASELINE" },
        { PlaceholderAlignment::BELOWBASELINE, "BELOWBASELINE" },
        { PlaceholderAlignment::TOP, "TOP" },
        { PlaceholderAlignment::BOTTOM, "BOTTOM" },
        { PlaceholderAlignment::MIDDLE, "MIDDLE" },
        { PlaceholderAlignment::FOLLOW_PARAGRAPH, "FOLLOW_PARAGRAPH" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), placeholderAlignment);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

enum class SpanItemType { NORMAL = 0, IMAGE = 1, CustomSpan = 2, SYMBOL = 3, PLACEHOLDER = 4 };

namespace StringUtils {
inline std::string ToString(const SpanItemType& spanItemType)
{
    static const LinearEnumMapNode<SpanItemType, std::string> table[] = {
        { SpanItemType::NORMAL, "NORMAL" },
        { SpanItemType::IMAGE, "IMAGE" },
        { SpanItemType::CustomSpan, "CustomSpan" },
        { SpanItemType::SYMBOL, "SYMBOL" },
        { SpanItemType::PLACEHOLDER, "PLACEHOLDER" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), spanItemType);
    return iter != -1 ? table[iter].value : "";
}
}

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

    void UpdateColorByResourceId()
    {
        CHECK_NULL_VOID(backgroundColor);
        backgroundColor->UpdateColorByResourceId();
    }

    static void ToJsonValue(std::unique_ptr<JsonValue>& json, const std::optional<TextBackgroundStyle>& style,
        const NG::InspectorFilter& filter);

    bool operator==(const TextBackgroundStyle& value) const
    {
        // Only compare groupId if both styles require it.
        bool bothNeedCompareGroupId = needCompareGroupId && value.needCompareGroupId;
        return backgroundColor == value.backgroundColor && backgroundRadius == value.backgroundRadius &&
               (!bothNeedCompareGroupId || groupId == value.groupId);
    }
};
enum class TextStyleAttribute {
    RE_CREATE = -1,
    FONT_SIZE = 0,
    FONT_WEIGHT = 1,
    FONT_STYLE = 3,
    FONT_FAMILIES = 4,
    LETTER_SPACING = 5,
    WORD_SPACING = 6,
    HEIGHT_ONLY = 7,
    HEIGHT_SCALE = 8,
    FONT_FEATURES = 9,
    FONT_VARIATIONS = 10,
    BASELINE_SHIFT = 11,

    DECRATION = 12,
    DECORATION_COLOR = 13,
    DECORATION_STYLE = 14,
    DECORATION_THICKNESS_SCALE = 15,
    BACKGROUND_RECT = 16,
    STYLE_ID = 17,
    FONT_COLOR = 18,
    SHADOWS = 19,
    HALF_LEADING = 20,
    FOREGROUND_BRUSH = 21,
    MAX_TEXT_STYLE
};

enum class ParagraphStyleAttribute {
    RE_CREATE = -1,
    FONT_SIZE = 0,
    DIRECTION = 1,
    MAXLINES = 2,

    HALF_LEADING = 8,
    BREAKSTRAGY = 19,

    WORD_BREAKTYPE = 20,
    ELLIPSIS = 21,
    ELLIPSE_MODAL = 22,
    TEXT_ALIGN = 23,
    SPACING = 24,
    SPACING_IS_END = 25,
    TEXT_HEIGHT_BEHAVIOR = 26,

    MAX_TEXT_STYLE
};

enum class SymbolStyleAttribute {
    RE_CREATE = -1,
    // EffectStrategy
    EFFECT_STRATEGY = 0,
    // SymbolEffectOptions
    ANIMATION_MODE = 1,
    ANIMATION_START = 2,
    COMMONSUB_TYPE = 3,
    // RenderColors(SymbolColorList)
    COLOR_LIST = 4,
    // RenderStrategy
    RENDER_MODE = 5,
    MAX_SYMBOL_STYLE,
};

// For textStyle
#define ACE_DEFINE_TEXT_STYLE_FUNC(name, type, changeflag) \
public:                                                    \
    const type& Get##name() const                          \
    {                                                      \
        return prop##name##_;                              \
    }                                                      \
    void Set##name(const type& newValue)                   \
    {                                                      \
        if (NearEqual(prop##name##_, newValue)) {          \
            return;                                        \
        }                                                  \
        auto flag = static_cast<int32_t>(changeflag);      \
        if (GreatOrEqual(flag, 0)) {                       \
            reLayoutTextStyleBitmap_.set(flag);            \
        } else {                                           \
            needReCreateParagraph_ = true;                 \
        }                                                  \
        prop##name##_ = newValue;                          \
    }                                                      \
    void Set##name(const std::optional<type>& value)       \
    {                                                      \
        if (value.has_value()) {                           \
            Set##name(value.value());                      \
        }                                                  \
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
        if (GreatOrEqual(flag, 0)) {                                  \
            reLayoutTextStyleBitmap_.set(flag);                       \
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
#define ACE_DEFINE_PARAGRAPH_STYLE(name, type, changeflag) \
public:                                                    \
    const type& Get##name() const                          \
    {                                                      \
        return prop##name##_;                              \
    }                                                      \
    void Set##name(const type& newValue)                   \
    {                                                      \
        if (NearEqual(prop##name##_, newValue)) {          \
            return;                                        \
        }                                                  \
        auto flag = static_cast<int32_t>(changeflag);      \
        if (GreatOrEqual(flag, 0)) {                       \
            reLayoutParagraphStyleBitmap_.set(flag);       \
        } else {                                           \
            needReCreateParagraph_ = true;                 \
        }                                                  \
        prop##name##_ = newValue;                          \
    }                                                      \
                                                           \
private:                                                   \
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
            reLayoutParagraphStyleBitmap_.set(flag);                                     \
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

    bool operator==(const TextStyle& rhs) const;
    bool operator!=(const TextStyle& rhs) const;

    static void ToJsonValue(std::unique_ptr<JsonValue>& json, const std::optional<TextStyle>& style,
        const NG::InspectorFilter& filter);

    static std::string GetDeclarationString(
        const std::optional<Color>& color, const std::vector<TextDecoration>& textDecorations,
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
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(TextColor, Color, Color::BLACK, TextStyleAttribute::FONT_COLOR);
    ACE_DEFINE_TEXT_DIMENSION_STYLE(WordSpacing, TextStyleAttribute::WORD_SPACING);
    ACE_DEFINE_TEXT_DIMENSION_STYLE_WITH_DEFAULT_VALUE(
        TextIndent, Dimension(0.0f, DimensionUnit::PX), 0.0f, TextStyleAttribute::RE_CREATE);
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
    ACE_DEFINE_PARAGRAPH_STYLE_WITH_DEFAULT_VALUE(EnableAutoSpacing, bool, false, ParagraphStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        LineThicknessScale, float, 1.0f, TextStyleAttribute::DECORATION_THICKNESS_SCALE);

    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        StrokeWidth, Dimension, Dimension(0.0f, DimensionUnit::PX), TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE(StrokeColor, Color, TextStyleAttribute::RE_CREATE);
    ACE_DEFINE_TEXT_STYLE_WITH_DEFAULT_VALUE(
        Superscript, SuperscriptStyle, SuperscriptStyle::NORMAL, TextStyleAttribute::RE_CREATE);    

    // used for gradiant color
    ACE_DEFINE_PARAGRAPH_STYLE(FontForegroudGradiantColor, FontForegroudGradiantColor,
        TextStyleAttribute::RE_CREATE);

    // for Symbol
    ACE_DEFINE_SYMBOL_STYLE(RenderColors, std::vector<Color>, SymbolStyleAttribute::COLOR_LIST);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(RenderStrategy, int32_t, 0, SymbolStyleAttribute::RENDER_MODE);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(EffectStrategy, int32_t, 0, SymbolStyleAttribute::EFFECT_STRATEGY);
    ACE_DEFINE_SYMBOL_STYLE_WITH_DEFAULT_VALUE(
        SymbolType, SymbolType, SymbolType::SYSTEM, SymbolStyleAttribute::RE_CREATE);

public:
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
        return GetTextDecoration().size() > 0 ?
            GetTextDecoration()[0] : TextDecoration::NONE;
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
    void SetAdaptTextSize(
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

    void CompareCommonSubType(const std::optional<NG::SymbolEffectOptions>& options,
        const std::optional<NG::SymbolEffectOptions>& oldOptions);
    void CompareAnimationMode(const std::optional<NG::SymbolEffectOptions>& options,
        const std::optional<NG::SymbolEffectOptions>& oldOptions);
    void SetWhenOnlyOneOptionIsValid(const std::optional<NG::SymbolEffectOptions>& options);
    void SetSymbolEffectOptions(const std::optional<NG::SymbolEffectOptions>& symbolEffectOptions);

    const std::optional<NG::SymbolEffectOptions> GetSymbolEffectOptions() const
    {
        return symbolEffectOptions_;
    }

    std::string ToString() const;
    void UpdateColorByResourceId();

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

    void SetGradient(const std::optional<Gradient>& gradient)
    {
        gradient_ = gradient;
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FOREGROUND_BRUSH));
    }

    void SetForeGroundBrushBitMap()
    {
        reLayoutTextStyleBitmap_.set(static_cast<int32_t>(TextStyleAttribute::FOREGROUND_BRUSH));
    }

    const std::optional<Gradient>& GetGradient() const
    {
        return gradient_;
    }

private:
    std::bitset<static_cast<size_t>(TextStyleAttribute::MAX_TEXT_STYLE)> reLayoutTextStyleBitmap_;
    std::bitset<static_cast<size_t>(ParagraphStyleAttribute::MAX_TEXT_STYLE)> reLayoutParagraphStyleBitmap_;
    std::bitset<static_cast<size_t>(SymbolStyleAttribute::MAX_SYMBOL_STYLE)> reLayoutSymbolStyleBitmap_;
    bool needReCreateParagraph_ = false;
    int32_t textStyleUid_ = 0;
    int32_t symbolUid_ = 0;
    std::list<std::pair<std::string, int32_t>> fontFeatures_;
    std::vector<Dimension> preferFontSizes_;
    std::vector<TextSizeGroup> preferTextSizeGroups_;
    std::optional<Gradient> gradient_;
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
    // for Symbol
    std::optional<NG::SymbolEffectOptions> symbolEffectOptions_;
};

namespace StringUtils {

inline std::pair<bool, FontWeight> ParseFontWeight(const std::string& weight,
    FontWeight defaultFontWeight = FontWeight::NORMAL)
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

inline FontWeight StringToFontWeight(const std::string& weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    return ParseFontWeight(weight, defaultFontWeight).second;
}

inline WordBreak StringToWordBreak(const std::string& wordBreak)
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

inline std::string FontWeightToString(const FontWeight& fontWeight)
{
    static const std::unordered_map<FontWeight, std::string> fontWeightTable = {
        { FontWeight::W100, "100" }, { FontWeight::W200, "200" }, { FontWeight::W300, "300" },
        { FontWeight::W400, "400" }, { FontWeight::W500, "500" }, { FontWeight::W600, "600" },
        { FontWeight::W700, "700" }, { FontWeight::W800, "800" }, { FontWeight::W900, "900" },
        { FontWeight::BOLD, "bold" }, { FontWeight::BOLDER, "bolder" }, { FontWeight::LIGHTER, "lighter" },
        { FontWeight::MEDIUM, "medium" }, { FontWeight::NORMAL, "normal" }, { FontWeight::REGULAR, "regular" },
    };
    auto weightIter = fontWeightTable.find(fontWeight);
    return weightIter != fontWeightTable.end() ? weightIter->second : "";
}

inline std::string ToString(const FontWeight& fontWeight)
{
    return FontWeightToString(fontWeight);
}

inline std::string SymbolColorListToString(const std::vector<Color>& colorList)
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
} // namespace StringUtils
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_H
