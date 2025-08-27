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
#include "core/components_ng/pattern/image_animator/controlled_animator.h"

#include <utility>
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"
#include "base/log/ace_trace.h"
#include "base/thread/task_executor.h"
#include "core/animation/animation_pub.h"
#include "core/common/container.h"
#include "core/components_ng/image_provider/image_utils.h"

namespace OHOS::Ace {

namespace {
// Forever animation
static constexpr int32_t ANIMATION_INFINITE { -1 };
} // namespace

void ControlledAnimator::SetControlStatus(ControlStatus controlStatus)
{
    controlStatus_ = controlStatus;
}

ControlledAnimator::ControlStatus ControlledAnimator::GetControlStatus() const
{
    return controlStatus_;
}

void ControlledAnimator::SetFillMode(FillMode fillMode)
{
    fillMode_ = fillMode;
}

FillMode ControlledAnimator::GetFillMode() const
{
    return fillMode_;
}

void ControlledAnimator::SetRunningIdx(int32_t runningIdx)
{
    runningIdx_ = runningIdx;
}

void ControlledAnimator::SetDuration(int32_t duration)
{
    duration_ = duration;
}

int32_t ControlledAnimator::GetDuration() const
{
    return duration_;
}

void ControlledAnimator::ClearInterpolators()
{
    pictureInfos_.clear();
}

void ControlledAnimator::AddInterpolator(const std::vector<PictureInfo>& pictureInfos)
{
    pictureInfos_ = std::move(pictureInfos);
}

void ControlledAnimator::AddStartListener(AnimatorEvent startEvent)
{
    startEvent_ = std::move(startEvent);
}

void ControlledAnimator::AddStopListener(AnimatorEvent stopEvent)
{
    stopEvent_ = std::move(stopEvent);
}

void ControlledAnimator::AddPauseListener(AnimatorEvent pauseEvent)
{
    pauseEvent_ = std::move(pauseEvent);
}

void ControlledAnimator::AddRepeatListener(AnimatorEvent repeatEvent)
{
    repeatEvent_ = std::move(repeatEvent);
}

void ControlledAnimator::AddInnerRepeatListener(AnimatorEvent innerRepeatEvent)
{
    innerRepeatEvent_ = std::move(innerRepeatEvent);
}

void ControlledAnimator::RemoveRepeatListener()
{
    repeatEvent_ = nullptr;
}

void ControlledAnimator::RemoveInnerRepeatListener()
{
    innerRepeatEvent_ = nullptr;
}

void ControlledAnimator::AddCancelListener(AnimatorEvent cancelEvent)
{
    cancelEvent_ = std::move(cancelEvent);
}

void ControlledAnimator::ClearAllListeners()
{
    startEvent_ = nullptr;
    stopEvent_ = nullptr;
    pauseEvent_ = nullptr;
    repeatEvent_ = nullptr;
    cancelEvent_ = nullptr;
}

void ControlledAnimator::SetIteration(int32_t iteration)
{
    if (iteration_ == iteration) {
        return;
    }
    iteration_ = iteration;
    if (controlStatus_ != ControlStatus::IDLE && controlStatus_ != ControlStatus::STOPPED) {
        if (stopEvent_) {
            stopEvent_();
        }
        MovePictureToRightPosition(false);
        needFireRepeatEvent_ = false;
        controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
        currentPostTask_.Cancel();
    }
}

void ControlledAnimator::AddListener(IndexChangeListener listener)
{
    playbackListener_ = std::move(listener);
}

// This function is guaranteed to be executed on the main thread.
void ControlledAnimator::PostPlayTask(int32_t idx, int32_t iteration, int32_t idxOffset, int32_t elapsedTime)
{
    if (iteration >= iteration_ && iteration_ != ANIMATION_INFINITE) {
        Finish();
        return;
    }
    ACE_SCOPED_TRACE("ControlledAnimator postPlayTask %d-%d-%d-%d", idx, iteration, idxOffset, elapsedTime);
    runningIdx_ = idx;
    if (needFireRepeatEvent_) {
        needFireRepeatEvent_ = false;
        if (repeatEvent_) {
            repeatEvent_();
        }
        if (innerRepeatEvent_) {
            innerRepeatEvent_();
            innerRepeatEvent_ = nullptr;
        }
    }
    playbackListener_(pictureInfos_[idx].second);
    // records the task start time, and calculates the remaining playback time for the current frame.
    currentTaskStartTime_ = std::chrono::steady_clock::now();
    // If elapsedTime is less than to 0, it indicates the playback order is reversed compared to the last time,
    // so the current playback duration should be the same as the previous duration. Otherwise, the current playback
    // duration is the total duration minus the previously elapsed time.
    auto runningTime = elapsedTime < 0 ? static_cast<int32_t>(-elapsedTime)
                                       : static_cast<int32_t>(pictureInfos_[idx].first * GetDuration() - elapsedTime);
    idx += idxOffset;
    // Sets needFireRepeatEvent_ to true when the current iteration ends,
    // indicating that the repeat callback should be triggered in the next iteration.
    if (idx == static_cast<int32_t>(pictureInfos_.size()) || idx == -1) {
        ++iteration;
        needFireRepeatEvent_ = true;
        idx = (idx == -1) ? static_cast<int32_t>(pictureInfos_.size()) - 1 : 0;
    }
    currentPostTask_.Reset([weak = WeakClaim(this), idx, iteration, idxOffset] {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->PostPlayTask(idx, iteration, idxOffset);
    });
    NG::ImageUtils::PostDelayedTaskToUI(
        currentPostTask_, runningTime, "ArkUIImageAnimatorPostPlayTask", Container::CurrentId(), PriorityType::VIP);
}

int32_t ControlledAnimator::GetIteration() const
{
    return iteration_;
}

void ControlledAnimator::Forward()
{
    if (!iteration_ || (controlStatus_ == ControlledAnimator::ControlStatus::RUNNING && !isReverse_) ||
        pictureInfos_.empty()) {
        return;
    }
    if (startEvent_) {
        startEvent_();
    }
    if (!duration_) {
        Finish();
        return;
    }
    isReverse_ = false;
    isFirstRun_ = false;
    if (controlStatus_ == ControlledAnimator::ControlStatus::STOPPED) {
        MovePictureToRightPosition(false);
    }
    needFireRepeatEvent_ = false;
    controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    PostPlayTask(runningIdx_, 0, 1, elapsedTimeReversedStatus_ ? -elapsedTime_ : elapsedTime_);
    // reset elapsedTime_
    elapsedTime_ = 0;
}

void ControlledAnimator::Backward()
{
    if (!iteration_ || (controlStatus_ == ControlledAnimator::ControlStatus::RUNNING && isReverse_) ||
        pictureInfos_.empty()) {
        return;
    }
    if (startEvent_) {
        startEvent_();
    }
    if (!duration_) {
        Finish();
        return;
    }
    isReverse_ = true;
    if (isFirstRun_) {
        isFirstRun_ = false;
        runningIdx_ = static_cast<int32_t>(pictureInfos_.size()) - 1;
    }
    if (controlStatus_ == ControlledAnimator::ControlStatus::STOPPED) {
        MovePictureToRightPosition(false);
    }
    needFireRepeatEvent_ = false;
    controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    PostPlayTask(runningIdx_, 0, -1, elapsedTimeReversedStatus_ ? elapsedTime_ : -elapsedTime_);
    // reset elapsedTime_
    elapsedTime_ = 0;
}

void ControlledAnimator::Cancel()
{
    if (!iteration_ || controlStatus_ == ControlledAnimator::ControlStatus::IDLE || pictureInfos_.empty()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "Already initial.");
        return;
    }
    if (cancelEvent_) {
        cancelEvent_();
    }
    controlStatus_ = ControlledAnimator::ControlStatus::IDLE;
    needFireRepeatEvent_ = false;
    elapsedTime_ = 0;
    auto finishIdx = CalFinishIdx(false);
    if (runningIdx_ != finishIdx) {
        playbackListener_(pictureInfos_[finishIdx].second);
        runningIdx_ = finishIdx;
    }
    currentPostTask_.Cancel();
}

void ControlledAnimator::Pause()
{
    if (!iteration_ || controlStatus_ == ControlledAnimator::ControlStatus::PAUSED || pictureInfos_.empty()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "Already paused.");
        return;
    }
    if (pauseEvent_) {
        pauseEvent_();
    }
    currentPostTask_.Cancel();
    if (controlStatus_ == ControlledAnimator::ControlStatus::RUNNING) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTaskStartTime_ - currentTime).count();
        elapsedTime_ = static_cast<int32_t>(elapsedTime);
    }
    controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;
    elapsedTimeReversedStatus_ = isReverse_;
}

// Calculates the index of the image to display when stop, based on the fillMode and reverse flag.
int32_t ControlledAnimator::CalFinishIdx(bool checkWithFillMode)
{
    if (checkWithFillMode && (fillMode_ == FillMode::FORWARDS || fillMode_ == FillMode::BOTH)) {
        return isReverse_ ? 0 : static_cast<int32_t>(pictureInfos_.size()) - 1;
    }
    return isReverse_ ? static_cast<int32_t>(pictureInfos_.size()) - 1 : 0;
}


void ControlledAnimator::MovePictureToRightPosition(bool checkWithFillMode)
{
    auto finishIdx = CalFinishIdx(checkWithFillMode);
    // Ensure the first picture is displayed when only one image exists;
    // without this, the image may not show if runningIdx_ == finishIdx
    if (runningIdx_ != finishIdx || pictureInfos_.size() == 1) {
        playbackListener_(pictureInfos_[finishIdx].second);
        runningIdx_ = finishIdx;
    }
}

void ControlledAnimator::Finish()
{
    if (!iteration_ || controlStatus_ == ControlStatus::STOPPED || pictureInfos_.empty()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "Already stopped.");
        return;
    }
    if (stopEvent_) {
        stopEvent_();
    }
    controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    MovePictureToRightPosition();
    needFireRepeatEvent_ = false;
    elapsedTime_ = 0;
    currentPostTask_.Cancel();
}
} // namespace OHOS::Ace