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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_CONTROLLED_ANIMATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_CONTROLLED_ANIMATOR_H

#include <chrono>
#include "ui/base/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/animation/animation_pub.h"
namespace OHOS::Ace {

using AnimatorEvent = std::function<void()>;
using PictureInfo = std::pair<float, int32_t>;
using IndexChangeListener = std::function<void(int32_t)>;

class ControlledAnimator : public AceType {
    DECLARE_ACE_TYPE(ControlledAnimator, AceType)
public:
    ControlledAnimator() = default;

    ~ControlledAnimator() = default;

    enum class ControlStatus {
        IDLE,    // when animation not start or been cancel.
        RUNNING, // play in reverse / forward direction.
        PAUSED,  // paused by call Pause API.
        STOPPED, // stopped by call Finish/Stop API or has played to the end.
    };

    void SetControlStatus(ControlStatus controlStatus);
    ControlStatus GetControlStatus() const;
    void SetFillMode(FillMode fillMode);
    FillMode GetFillMode() const;
    void SetRunningIdx(int32_t runningIdx);
    void SetDuration(int32_t duration);
    int32_t GetDuration() const;
    void SetIteration(int32_t iteration);
    int32_t GetIteration() const;
    void ClearInterpolators();
    void AddInterpolator(const std::vector<PictureInfo>& pictureInfos);
    void AddListener(IndexChangeListener listener);
    // register callBack
    void AddStartListener(AnimatorEvent startEvent);
    void AddStopListener(AnimatorEvent stopEvent);
    void AddPauseListener(AnimatorEvent pauseEvent);
    void AddRepeatListener(AnimatorEvent repeatEvent);
    void AddInnerRepeatListener(AnimatorEvent innerRepeatEvent);
    void RemoveRepeatListener();
    void RemoveInnerRepeatListener();
    void AddCancelListener(AnimatorEvent cancelEvent);
    void ClearAllListeners();
    // behavioral control
    void Forward();
    void Backward();
    void Cancel();
    void Pause();
    void Finish();
    void MovePictureToRightPosition(bool checkWithFillMode = true);
    int32_t CalFinishIdx(bool checkWithFillMode = true);

private:
    ControlStatus controlStatus_ = ControlStatus::IDLE;
    bool isReverse_ = false;
    FillMode fillMode_ = FillMode::FORWARDS;
    int32_t iteration_ = 1;
    // the total playback duration.
    int32_t duration_ = 0;
    // the playback duration ratio for each picture.
    std::vector<PictureInfo> pictureInfos_;
    int32_t runningIdx_ = 0;
    bool needFireRepeatEvent_ = false;
    bool isFirstRun_ = true;

    AnimatorEvent startEvent_;
    AnimatorEvent stopEvent_;
    AnimatorEvent pauseEvent_;
    //  User-defined callback triggered when the animation repeats.
    AnimatorEvent repeatEvent_;
    //  Callback used within imageAnimatorPattern to update the duration for the next cycle.
    AnimatorEvent innerRepeatEvent_;
    AnimatorEvent cancelEvent_;

    void PostPlayTask(int32_t idx, int32_t iteration, int32_t idxOffset = 1, int32_t elapsedTime = 0.0);
    IndexChangeListener playbackListener_;
    CancelableCallback<void()> currentPostTask_;
    // Records the start time of the current playback task.
    std::chrono::time_point<std::chrono::steady_clock> currentTaskStartTime_;
    // Tracks whether the playback was in forward order when paused (true for Backward, false for Forward).
    bool elapsedTimeReversedStatus_ = false;
    // Stores the elapsed time of the current playback, used to calculate remaining time.
    int32_t elapsedTime_ = 0.0f;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_CONTROLLED_ANIMATOR_H
