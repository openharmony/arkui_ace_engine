/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "common_text_constants.h"

namespace OHOS::Ace {
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY,
    TextAlign::LEFT, TextAlign::RIGHT };

const std::vector<TextContentAlign> TEXT_CONTENT_ALIGNS = { TextContentAlign::TOP, TextContentAlign::CENTER,
    TextContentAlign::BOTTOM };

const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE = { TextSelectableMode::SELECTABLE_UNFOCUSABLE,
    TextSelectableMode::SELECTABLE_FOCUSABLE, TextSelectableMode::UNSELECTABLE };

const std::vector<TextVerticalAlign> TEXT_VERTICAL_ALIGNS = { TextVerticalAlign::BASELINE, TextVerticalAlign::BOTTOM,
    TextVerticalAlign::CENTER, TextVerticalAlign::TOP };

const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES = { LineBreakStrategy::GREEDY,
    LineBreakStrategy::HIGH_QUALITY, LineBreakStrategy::BALANCED };

const std::vector<TextDirection> TEXT_DIRECTIONS = { TextDirection::LTR, TextDirection::RTL, TextDirection::INHERIT,
    TextDirection::AUTO };

const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };

const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };

const std::vector<WordBreak> WORD_BREAK_TYPES = { WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD,
    WordBreak::HYPHENATION };

const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };

const std::vector<EllipsisMode> ELLIPSIS_MODES = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL };

} // namespace OHOS::Ace