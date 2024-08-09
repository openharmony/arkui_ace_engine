/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H

#include <optional>
#include <string>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
struct MeasureContext {
    std::string textContent;
    std::string fontWeight;
    std::string fontFamily;
    bool isFontSizeUseDefaultUnit = false;
    bool isReturnActualWidth = false;
    std::optional<Dimension> constraintWidth = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Dimension> lineHeight = std::nullopt;
    std::optional<Dimension> baselineOffset = std::nullopt;
    std::optional<Dimension> letterSpacing = std::nullopt;
    std::optional<Dimension> lineSpacing = std::nullopt;
    std::optional<Dimension> textIndent = std::nullopt;
    int32_t maxlines = 0;
    TextAlign textAlign = TextAlign::START;
    FontStyle fontStyle = FontStyle::NORMAL;
    TextOverflow textOverlayFlow = TextOverflow::CLIP;
    TextCase textCase = TextCase::NORMAL;
    WordBreak wordBreak = WordBreak::BREAK_WORD;
    LineBreakStrategy lineBreakStrategy = LineBreakStrategy::GREEDY;
};

class ACE_FORCE_EXPORT MeasureUtil {
public:
    static double MeasureText(const MeasureContext& context);
    static Size MeasureTextSize(const MeasureContext& context);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MEASURE_UTIL_H
