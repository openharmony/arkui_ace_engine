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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT__COMMON_TEXT_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT__COMMON_TEXT_CONSTANTS_H

#include <string>
#include <vector>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {

extern const std::vector<TextCase> TEXT_CASES;

extern const std::vector<TextAlign> TEXT_ALIGNS;

extern const std::vector<TextContentAlign> TEXT_CONTENT_ALIGNS;

extern const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY;

extern const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE;

extern const std::vector<TextVerticalAlign> TEXT_VERTICAL_ALIGNS;

extern const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES;

extern const std::vector<TextDirection> TEXT_DIRECTIONS;

extern const std::vector<FontStyle> FONT_STYLES;

extern const std::vector<std::string> INPUT_FONT_FAMILY_VALUE;

extern const std::vector<WordBreak> WORD_BREAK_TYPES;

extern const std::vector<TextOverflow> TEXT_OVERFLOWS;

extern const std::vector<EllipsisMode> ELLIPSIS_MODES;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT__COMMON_TEXT_CONSTANTS_H