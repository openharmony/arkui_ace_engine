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

constexpr uint32_t DEFAULT_MAX_FONT_FAMILY_LENGTH = Infinity<uint32_t>();

enum class FontStyle {
    NORMAL,
    ITALIC,
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
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), placeholderAlignment);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils

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

class ACE_EXPORT TextStyle final {
public:
    TextStyle() = default;
    TextStyle(const std::vector<std::string>& fontFamilies, double fontSize, FontWeight fontWeight, FontStyle fontStyle,
        const Color& textColor);
    TextStyle(double fontSize) : fontSize_(fontSize) {}
    TextStyle(const Color& textColor) : textColor_(textColor) {}
    ~TextStyle() = default;

    bool operator==(const TextStyle& rhs) const;
    bool operator!=(const TextStyle& rhs) const;

    TextBaseline GetTextBaseline() const
    {
        return textBaseline_;
    }

    const Dimension& GetBaselineOffset() const
    {
        return baselineOffset_;
    }

    void SetBaselineOffset(const Dimension& baselineOffset)
    {
        baselineOffset_ = baselineOffset;
    }

    void SetTextBaseline(TextBaseline baseline)
    {
        textBaseline_ = baseline;
    }

    void ResetTextBaseline()
    {
        baselineOffset_.Reset();
    }

    void SetTextDecoration(TextDecoration textDecoration)
    {
        textDecoration_ = textDecoration;
    }

    void SetTextDecorationStyle(TextDecorationStyle textDecorationStyle)
    {
        textDecorationStyle_ = textDecorationStyle;
    }

    FontStyle GetFontStyle() const
    {
        return fontStyle_;
    }

    void SetFontStyle(FontStyle fontStyle)
    {
        fontStyle_ = fontStyle;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    WhiteSpace GetWhiteSpace() const
    {
        return whiteSpace_;
    }

    void SetWhiteSpace(WhiteSpace whiteSpace)
    {
        whiteSpace_ = whiteSpace;
    }

    void SetFontSize(const Dimension& fontSize)
    {
        fontSize_ = fontSize;
    }

    void SetMaxFontScale(float maxFontScale)
    {
        maxFontScale_ = maxFontScale;
    }

    void SetMinFontScale(float minFontScale)
    {
        minFontScale_ = minFontScale;
    }

    std::optional<float> GetMaxFontScale() const
    {
        return maxFontScale_;
    }

    std::optional<float> GetMinFontScale() const
    {
        return minFontScale_;
    }

    FontWeight GetFontWeight() const
    {
        return fontWeight_;
    }

    void SetFontWeight(FontWeight fontWeight)
    {
        fontWeight_ = fontWeight;
    }

    int32_t GetVariableFontWeight() const
    {
        return variableFontWeight_;
    }

    void SetVariableFontWeight(int32_t variableFontWeight)
    {
        variableFontWeight_ = variableFontWeight;
    }

    bool GetEnableVariableFontWeight() const
    {
        return enableVariableFontWeight_;
    }

    void SetEnableVariableFontWeight(bool enableVariableFontWeight)
    {
        enableVariableFontWeight_ = enableVariableFontWeight;
    }
    const Color GetTextColor() const
    {
        return textColor_;
    }

    void SetTextColor(const Color& textColor)
    {
        textColor_ = textColor;
    }

    TextDecoration GetTextDecoration() const
    {
        return textDecoration_;
    }

    TextDecorationStyle GetTextDecorationStyle() const
    {
        return textDecorationStyle_;
    }

    const Dimension& GetWordSpacing() const
    {
        return wordSpacing_;
    }

    void SetWordSpacing(const Dimension& wordSpacing)
    {
        wordSpacing_ = wordSpacing;
    }

    const Color GetTextDecorationColor() const
    {
        return textDecorationColor_;
    }

    void SetTextDecorationColor(const Color& textDecorationColor)
    {
        textDecorationColor_ = textDecorationColor;
    }

    const std::vector<std::string>& GetFontFamilies() const
    {
        return fontFamilies_;
    }

    void SetFontFamilies(const std::vector<std::string>& fontFamilies)
    {
        fontFamilies_ = fontFamilies;
    }

    Dimension GetTextIndent() const
    {
        return textIndent_;
    }

    void SetTextIndent(const Dimension& textIndent)
    {
        textIndent_ = textIndent;
    }

    const std::list<std::pair<std::string, int32_t>>& GetFontFeatures() const
    {
        return fontFeatures_;
    }

    void SetFontFeatures(const std::list<std::pair<std::string, int32_t>>& fontFeatures)
    {
        fontFeatures_ = fontFeatures;
    }

    const Dimension& GetLineHeight() const
    {
        return lineHeight_;
    }

    void SetLineHeight(const Dimension& lineHeight, bool hasHeightOverride = true)
    {
        lineHeight_ = lineHeight;
        hasHeightOverride_ = hasHeightOverride;
    }

    const Dimension& GetLineSpacing() const
    {
        return lineSpacing_;
    }

    void SetLineSpacing(const Dimension& lineSpacing)
    {
        lineSpacing_ = lineSpacing;
    }

    const Dimension& GetParagraphSpacing() const
    {
        return paragraphSpacing_;
    }

    void SetParagraphSpacing(const Dimension& paragraphSpacing)
    {
        paragraphSpacing_ = paragraphSpacing;
    }

    bool HasHeightOverride() const
    {
        return hasHeightOverride_;
    }

    const Dimension& GetLetterSpacing() const
    {
        return letterSpacing_;
    }

    void SetLetterSpacing(const Dimension& letterSpacing)
    {
        letterSpacing_ = letterSpacing;
    }

    bool GetAdaptTextSize() const
    {
        return adaptTextSize_;
    }

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

    void DisableAdaptTextSize()
    {
        adaptTextSize_ = false;
    }

    uint32_t GetMaxLines() const
    {
        return maxLines_;
    }

    void SetMaxLines(uint32_t maxLines)
    {
        maxLines_ = maxLines;
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

    // Must use with SetAdaptMinFontSize and SetAdaptMaxFontSize.
    void SetAdaptFontSizeStep(const Dimension& adaptTextSizeStep)
    {
        adaptFontSizeStep_ = adaptTextSizeStep;
    }
    // Must use with SetAdaptMaxFontSize.
    void SetAdaptMinFontSize(const Dimension& adaptMinFontSize)
    {
        adaptMinFontSize_ = adaptMinFontSize;
        adaptTextSize_ = true;
    }
    // Must use with SetAdaptMinFontSize.
    void SetAdaptMaxFontSize(const Dimension& adaptMaxFontSize)
    {
        adaptMaxFontSize_ = adaptMaxFontSize;
        adaptTextSize_ = true;
    }

    const Dimension& GetAdaptFontSizeStep() const
    {
        return adaptFontSizeStep_;
    }

    const Dimension& GetAdaptMinFontSize() const
    {
        return adaptMinFontSize_;
    }

    const Dimension& GetAdaptMaxFontSize() const
    {
        return adaptMaxFontSize_;
    }

    const std::vector<TextSizeGroup>& GetPreferTextSizeGroups() const
    {
        return preferTextSizeGroups_;
    }
    void SetPreferTextSizeGroups(const std::vector<TextSizeGroup>& preferTextSizeGroups)
    {
        preferTextSizeGroups_ = preferTextSizeGroups;
        adaptTextSize_ = true;
    }

    bool IsAllowScale() const
    {
        return allowScale_;
    }

    void SetAllowScale(bool allowScale)
    {
        allowScale_ = allowScale;
    }

    TextOverflow GetTextOverflow() const
    {
        return textOverflow_;
    }
    void SetTextOverflow(TextOverflow textOverflow)
    {
        textOverflow_ = textOverflow;
    }
    TextAlign GetTextAlign() const
    {
        return textAlign_;
    }
    void SetTextAlign(TextAlign textAlign)
    {
        textAlign_ = textAlign;
    }
    void SetTextVerticalAlign(VerticalAlign verticalAlign)
    {
        verticalAlign_ = verticalAlign;
    }

    VerticalAlign GetTextVerticalAlign() const
    {
        return verticalAlign_;
    }

    WordBreak GetWordBreak() const
    {
        return wordBreak_;
    }

    void SetWordBreak(WordBreak wordBreak)
    {
        wordBreak_ = wordBreak;
    }

    TextCase GetTextCase() const
    {
        return textCase_;
    }

    void SetTextCase(TextCase textCase)
    {
        textCase_ = textCase;
    }

    const std::vector<Shadow>& GetTextShadows() const
    {
        return textShadows_;
    }

    void SetTextShadows(const std::vector<Shadow>& textShadows)
    {
        textShadows_ = textShadows;
    }

    void SetShadow(const Shadow& shadow)
    {
        textShadows_.emplace_back(shadow);
    }

    bool GetHalfLeading() const
    {
        return halfLeading_;
    }

    void SetHalfLeading(bool halfLeading)
    {
        halfLeading_ = halfLeading;
    }

    void SetEllipsisMode(EllipsisMode modal)
    {
        ellipsisMode_ = modal;
    }

    EllipsisMode GetEllipsisMode() const
    {
        return ellipsisMode_;
    }
    
    void SetHeightScale(double heightScale)
    {
        heightScale_ = heightScale;
    }
 
    double GetHeightScale() const
    {
        return heightScale_;
    }
 
    void SetHeightOnly(bool heightOnly)
    {
        heightOnly_ = heightOnly;
    }
 
    bool GetHeightOnly() const
    {
        return heightOnly_;
    }
 
    void SetEllipsis(std::u16string ellipsis)
    {
        ellipsis_ = ellipsis;
    }
 
    std::u16string GetEllipsis() const
    {
        return ellipsis_;
    }
 
    void SetLocale(std::string locale)
    {
        locale_ = locale;
    }
 
    std::string GetLocale() const
    {
        return locale_;
    }

    void SetTextBackgroundStyle(const std::optional<TextBackgroundStyle>& style)
    {
        textBackgroundStyle_ = style;
    }

    const std::optional<TextBackgroundStyle>& GetTextBackgroundStyle() const
    {
        return textBackgroundStyle_;
    }

    bool isSymbolGlyph_ = false;

    void SetRenderColors(std::vector<Color>& renderColors)
    {
        renderColors_ = renderColors ;
    }

    void SetRenderStrategy(int32_t renderStrategy)
    {
        renderStrategy_ = renderStrategy;
    }

    void SetEffectStrategy(int32_t effectStrategy)
    {
        effectStrategy_ = effectStrategy;
    }

    void SetSymbolColorList(const std::vector<Color>& renderColors)
    {
        renderColors_ = renderColors;
    }

    void SetSymbolEffectOptions(const std::optional<NG::SymbolEffectOptions>& symbolEffectOptions)
    {
        symbolEffectOptions_ = symbolEffectOptions;
    }

    std::vector<Color> GetRenderColors()
    {
        return renderColors_;
    }

    int32_t GetRenderStrategy() const
    {
        return renderStrategy_;
    }

    const std::vector<Color>& GetSymbolColorList() const
    {
        return renderColors_;
    }

    int32_t GetEffectStrategy() const
    {
        return effectStrategy_;
    }

    LineBreakStrategy GetLineBreakStrategy() const
    {
        return lineBreakStrategy_;
    }

    void SetLineBreakStrategy(const LineBreakStrategy breakStrategy)
    {
        lineBreakStrategy_ = breakStrategy;
    }

    SymbolType GetSymbolType() const
    {
        return symbolType_;
    }

    void SetSymbolType(const SymbolType symbolType)
    {
        symbolType_ = symbolType;
    }

    const std::optional<NG::SymbolEffectOptions> GetSymbolEffectOptions() const
    {
        return symbolEffectOptions_;
    }

    std::string ToString() const;
    void UpdateColorByResourceId();

private:
    std::vector<std::string> fontFamilies_;
    std::list<std::pair<std::string, int32_t>> fontFeatures_;
    std::vector<Dimension> preferFontSizes_;
    std::vector<TextSizeGroup> preferTextSizeGroups_;
    std::vector<Shadow> textShadows_;
    // use 14px for normal font size.
    Dimension fontSize_ { 14, DimensionUnit::PX };
    Dimension adaptMinFontSize_;
    Dimension adaptMaxFontSize_;
    Dimension adaptFontSizeStep_;
    Dimension lineHeight_;
    Dimension baselineOffset_;
    Dimension wordSpacing_;
    Dimension textIndent_ { 0.0f, DimensionUnit::PX };
    Dimension letterSpacing_;
    Dimension lineSpacing_;
    Dimension paragraphSpacing_ { 0.0f, DimensionUnit::PX };
    FontWeight fontWeight_ { FontWeight::NORMAL };
    FontStyle fontStyle_ { FontStyle::NORMAL };
    TextBaseline textBaseline_ { TextBaseline::ALPHABETIC };
    TextOverflow textOverflow_ { TextOverflow::CLIP };
    VerticalAlign verticalAlign_ { VerticalAlign::NONE };
    TextAlign textAlign_ { TextAlign::START };
    TextDecorationStyle textDecorationStyle_ { TextDecorationStyle::SOLID };
    TextDecoration textDecoration_ { TextDecoration::NONE };
    WhiteSpace whiteSpace_ { WhiteSpace::PRE };
    WordBreak wordBreak_ { WordBreak::BREAK_WORD };
    TextCase textCase_ { TextCase::NORMAL };
    EllipsisMode ellipsisMode_ = EllipsisMode::TAIL;
    LineBreakStrategy lineBreakStrategy_ { LineBreakStrategy::GREEDY };
    Color textColor_ { Color::BLACK };
    Color textDecorationColor_ { Color::BLACK };
    uint32_t maxLines_ = UINT32_MAX;
    int32_t variableFontWeight_ = 0;
    bool hasHeightOverride_ = false;
    bool adaptTextSize_ = false;
    bool adaptHeight_ = false; // whether adjust text size with height.
    bool allowScale_ = true;
    bool halfLeading_ = false;
    bool enableVariableFontWeight_ = false;
    std::optional<TextBackgroundStyle> textBackgroundStyle_;
    std::optional<float> minFontScale_;
    std::optional<float> maxFontScale_;

    // for Symbol
    std::vector<Color> renderColors_;
    int32_t renderStrategy_ = 0;
    int32_t effectStrategy_ = 0;
    std::optional<NG::SymbolEffectOptions> symbolEffectOptions_;
    double heightScale_ = 1.0;
    bool heightOnly_ = false;
    std::u16string ellipsis_;
    std::string locale_;
    SymbolType symbolType_ = SymbolType::SYSTEM;
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
