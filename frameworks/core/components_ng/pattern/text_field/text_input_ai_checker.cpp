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
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"

using namespace OHOS::Ace::NG;
namespace OHOS::Ace {
bool InputAIChecker::NeedAIAnalysis(const std::string& content, const NG::CaretUpdateType targetType,
    std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout)
{
    if (targetType != CaretUpdateType::DOUBLE_CLICK) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis type is %{public}d,return!", static_cast<int>(targetType));
        return false;
    }

    // empty string check
    if (content.empty()) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis content empty,return!");
        return false;
    }

    // if user determined want the clicked position
    TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "NeedAIAnalysis rectfied time:%{public}f", timeout.count());
    if (targetType == CaretUpdateType::PRESSED && timeout.count() < AIPOS_RECTIFIED_INTERVAL_MS) {
        return false;
    }

    return true;
}
bool InputAIChecker::IsSingleClickAtBoundary(int32_t position, int32_t textLength)
{
    bool endBoundary = position == textLength;
    bool startBoundary = position == 0;
    if (startBoundary || endBoundary) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "boundary start is %{public}d,end %{public}d ", startBoundary, endBoundary);
        return true;
    }

    return false;
}
bool InputAIChecker::IsMultiClickAtBoundary(const NG::OffsetF& handleOffset, const NG::RectF& textRect)
{
    if (textRect.GetX() - FLOAT_DIFF_COMPARE <= handleOffset.GetX() &&
        handleOffset.GetX() <= textRect.GetX() + FLOAT_DIFF_COMPARE) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "multi font boundary offset is handle: %{public}f,textRect: %{public}f ",
            handleOffset.GetX(), textRect.GetX());
        return true;
    }

    auto edge = textRect.GetX() + textRect.Width();
    if (handleOffset.GetX() >= edge - FLOAT_DIFF_COMPARE) {
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "multi tail boundary offset is handle: %{public}f,textRect: %{public}f ",
            handleOffset.GetX(), edge);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
