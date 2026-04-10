/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_TEXT_ENUMS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_TEXT_ENUMS_H

#include <string>

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
enum class TextDirection;

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

enum class FontStyle { NORMAL, ITALIC, NONE };

enum class SuperscriptStyle { NORMAL, SUPERSCRIPT, SUBSCRIPT, NONE };

enum class TextBaseline {
    ALPHABETIC,
    IDEOGRAPHIC,
    TOP,
    BOTTOM,
    MIDDLE,
    HANGING,
};

enum class TextCase {
    NORMAL = 0,
    LOWERCASE,
    UPPERCASE,
};

enum class EllipsisMode {
    HEAD,
    MIDDLE,
    TAIL,
    MULTILINE_HEAD,
    MULTILINE_MIDDLE,
};

enum class TextFlipDirection {
    DOWN = 0,
    UP,
};

enum class WordBreak { NORMAL = 0, BREAK_ALL, BREAK_WORD, HYPHENATION };

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

enum class SpanItemType { NORMAL = 0, IMAGE = 1, CustomSpan = 2, SYMBOL = 3, PLACEHOLDER = 4 };

enum class BorderRadiusIndex { TOPLEFT = 0, TOPRIGHT = 1, BOTTOMLEFT = 2, BOTTOMRIGHT = 3 };

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
    GRADIENT_COLOR = 6,
    SYMBOL_SHADOW = 7,
    MAX_SYMBOL_STYLE,
};

namespace StringUtils {

ACE_FORCE_EXPORT std::string ToString(const FontStyle& fontStyle);

ACE_FORCE_EXPORT std::string ToStringNDK(const FontStyle& fontStyle);

ACE_FORCE_EXPORT std::string ToString(const TextBaseline& textBaseline);

ACE_FORCE_EXPORT std::string ToString(const TextCase& textCase);

ACE_FORCE_EXPORT std::string ToString(const TextFlipDirection& textFlipDirection);
ACE_FORCE_EXPORT std::string ToString(const TextDirection& textDirection);

ACE_FORCE_EXPORT std::string ToString(const EllipsisMode& ellipsisMode);

ACE_FORCE_EXPORT std::string ToString(const WordBreak& wordBreak);

ACE_FORCE_EXPORT std::string ToString(const PlaceholderAlignment& placeholderAlignment);

ACE_FORCE_EXPORT std::string ToString(const SpanItemType& spanItemType);

} // namespace StringUtils

constexpr int32_t DEFAULT_FONT_WEIGHT_INT32 = 400;
constexpr int32_t DEFAULT_MULTIPLE = 100;
constexpr uint32_t DEFAULT_MAX_FONT_FAMILY_LENGTH = 128;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_PROPERTIES_TEXT_ENUMS_H