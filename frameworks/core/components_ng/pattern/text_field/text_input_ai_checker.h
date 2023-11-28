/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef OPENHARMONY_TEXT_INPUT_AI_CHECKER_H
#define OPENHARMONY_TEXT_INPUT_AI_CHECKER_H
#include <string>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng//pattern/text_field/text_selector.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT InputAIChecker {
public:
    constexpr static float FLOAT_DIFF_COMPARE = 1.0f;
    constexpr static uint32_t SECONDS_TO_MILLISECONDS = 1000;
    constexpr static float AIPOS_RECTIFIED_INTERVAL_MS = 1000.0f;

    static bool NeedAIAnalysis(const std::string& content, NG::CaretUpdateType targetType,
        std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout);

    static bool IsSingleClickAtBoundary(int32_t position, int32_t textLength);

    static bool IsMultiClickAtBoundary(const NG::OffsetF& handleOffset, const NG::RectF& textRect);
};
} // namespace OHOS::Ace

#endif // OPENHARMONY_TEXT_INPUT_AI_CHECKER_H
