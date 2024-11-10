/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/multiple_click_recognizer.h"

#include "base/utils/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
constexpr int32_t SINGLE_CLICK_TIME = 1;
constexpr int32_t DOUBLE_CLICK_TIME = 2;
constexpr int32_t TRIPLE_CLICK_TIME = 3;
}
void MultipleClickRecognizer::Start(const GestureEvent& event)
{
    if (clickCountTask_ && IsValidClick(event)) {
        clickTimes_++;
    } else {
        clickTimes_ = SINGLE_CLICK_TIME;
        beginGlobalLocation_ = event.GetGlobalLocation();
        beginLocalLocation_ = event.GetLocalLocation();
    }
    lastClickTimeStamp_ = event.GetTimeStamp();
    lastClickPosition_ = event.GetGlobalLocation();
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (!context || !context->GetTaskExecutor()) {
        Stop();
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    auto weak = WeakClaim(this);
    clickCountTask_.Reset([weak] {
        auto recognizer = weak.Upgrade();
        CHECK_NULL_VOID(recognizer);
        recognizer->Stop();
    });
    taskExecutor->PostDelayedTask(
        clickCountTask_, TaskExecutor::TaskType::UI, maxIntervalTime_, "MultipleClickRecognizerCountTask");
}

bool MultipleClickRecognizer::IsValidClick(const GestureEvent& event) const
{
    TimeStamp clickTimeStamp = event.GetTimeStamp();
    std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout = clickTimeStamp - lastClickTimeStamp_;
    Offset location = event.GetGlobalLocation();
    auto deltaOffset = location - lastClickPosition_;
    auto deltaDistance = deltaOffset.GetDistance();
    if (GreatOrEqual(timeout.count(), minIntervalTime_) && LessNotEqual(timeout.count(), maxIntervalTime_) &&
        LessNotEqual(deltaDistance, maxDeltaDistance_.ConvertToPx())) {
        return true;
    }
    return false;
}

bool MultipleClickRecognizer::IsSingleClick() const
{
    return GetClickTimes() == SINGLE_CLICK_TIME;
}

bool MultipleClickRecognizer::IsDoubleClick() const
{
    return GetClickTimes() == DOUBLE_CLICK_TIME;
}

bool MultipleClickRecognizer::IsTripleClick() const
{
    return GetClickTimes() == TRIPLE_CLICK_TIME;
}
} // namespace OHOS::Ace::NG