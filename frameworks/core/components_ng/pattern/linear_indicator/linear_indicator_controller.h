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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_CONTROLLER_H

#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
class LinearIndicatorPattern;
enum class LinearIndicatorControllerDataState { STOP, ANIMATION, INTERVAL, ANIMATION_PAUSE, INTERVAL_PAUSE };

class LinearIndicatorControllerData {
public:
    LinearIndicatorControllerData();

    void InitData();

    bool IsAnimationTimeEqually(int32_t totalAnimationTime) const
    {
        return totalAnimationTime == totalAnimationTime_;
    }

    bool IsIntervalTimeEqually(int32_t totalIntervalTime) const
    {
        return totalIntervalTime == totalIntervalTime_;
    }

    bool IsTimeEqually(int32_t totalAnimationTime, int32_t totalIntervalTime) const
    {
        return IsAnimationTimeEqually(totalAnimationTime) && IsIntervalTimeEqually(totalIntervalTime);
    }

    void SetTotalAnimationTime(int32_t totalAnimationTime)
    {
        totalAnimationTime_ = totalAnimationTime;
    }

    void SetTotalIntervalTime(int32_t totalIntervalTime)
    {
        totalIntervalTime_ = totalIntervalTime;
    }

    int32_t TotalAnimationTime() const
    {
        return totalAnimationTime_;
    }

    int32_t TotalIntervalTime() const
    {
        return totalIntervalTime_;
    }

    void SetTime(int32_t totalAnimationTime, int32_t totalIntervalTime)
    {
        SetTotalAnimationTime(totalAnimationTime);
        SetTotalIntervalTime(totalIntervalTime);
    }

    bool IsStop() const
    {
        return state_ == LinearIndicatorControllerDataState::STOP;
    }

    bool IsRuning() const
    {
        return state_ == LinearIndicatorControllerDataState::ANIMATION ||
               state_ == LinearIndicatorControllerDataState::INTERVAL;
    }

    bool IsPause() const
    {
        return state_ == LinearIndicatorControllerDataState::ANIMATION_PAUSE ||
               state_ == LinearIndicatorControllerDataState::INTERVAL_PAUSE;
    }

    LinearIndicatorControllerDataState State() const
    {
        return state_;
    }

    void SetState(LinearIndicatorControllerDataState state)
    {
        state_ = state;
        if (LinearIndicatorControllerDataState::INTERVAL_PAUSE == state) {
            UpdateIntervalConsumeTime();
        }
    }

    void UpdateIntervalStart(int32_t consumeTime)
    {
        intervalStart_ = std::chrono::system_clock::now() - std::chrono::milliseconds(consumeTime);
    }

    int32_t IntervalCurrentConsumeTime() const
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - intervalStart_);
        return int(duration.count());
    }

    int32_t IntervalConsumeTime() const
    {
        return intervalConsumeTime_;
    }

    void UpdateIntervalConsumeTime()
    {
        intervalConsumeTime_ = IntervalCurrentConsumeTime();
    }

    float Value() const
    {
        return value_;
    }

    void SetValue(float value)
    {
        value_ = value;
    }

    int32_t Index() const
    {
        return index_;
    }

    int32_t UpdateIndex()
    {
        SetValue(.0f);
        return ++index_;
    }

    void SetIndex(int32_t index)
    {
        index_ = index;
    }

    void SetIndexAndValue(int32_t index, float value)
    {
        SetIndex(index);
        SetValue(value);
    }

    bool IsLoop() const
    {
        return isLoop_;
    }

    void Loop(bool value)
    {
        isLoop_ = value;
    }

    bool IsProgressAnimation() const
    {
        return progressAnimation_.operator bool();
    }

    std::shared_ptr<AnimationUtils::Animation> ProgressAnimationAndClear()
    {
        std::shared_ptr<AnimationUtils::Animation> animation = progressAnimation_;
        progressAnimation_.reset();
        return animation;
    }

    void SetProgressAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
    {
        progressAnimation_ = animation;
    }

    const CancelableCallback<void()>& ProgressInterval() const
    {
        return progressInterval_;
    }

    void ProgressIntervalCancel()
    {
        progressInterval_.Cancel();
    }

    void ProgressIntervalReset(std::function<void()>&& callback)
    {
        progressInterval_.Reset(callback);
    }

    int32_t UpdateAnimationTag()
    {
        return ++animationTag_;
    }

    int32_t AnimationTag() const
    {
        return animationTag_;
    }

private:
    std::shared_ptr<AnimationUtils::Animation> progressAnimation_;
    int32_t animationTag_ = 0;
    CancelableCallback<void()> progressInterval_;
    int32_t totalAnimationTime_ = 0;
    int32_t totalIntervalTime_ = 0;

    LinearIndicatorControllerDataState state_;

    int32_t index_ = 0;
    float value_ = .0f;
    int32_t intervalConsumeTime_ = 0;
    std::chrono::system_clock::time_point intervalStart_;
    bool isLoop_ = true;
};

class LinearIndicatorController : public Referenced {
public:
    explicit LinearIndicatorController(const WeakPtr<LinearIndicatorPattern>& pattern)
        : pattern_(pattern), animationData_(), changeCallback_(nullptr)
    {}
    ~LinearIndicatorController() override = default;

    void SetProgress(int32_t index, float value);
    void Start(int32_t animationTime, int32_t intervalTime);
    void Pause();
    void Stop();

    void OnChange(std::function<void(int32_t index, float progress)>&& callback)
    {
        changeCallback_ = std::move(callback);
    }

    void Loop(bool value)
    {
        animationData_.Loop(value);
    }

    int32_t TotalAnimationTime() const
    {
        return animationData_.TotalAnimationTime();
    }

    int32_t TotalIntervalTime() const
    {
        return animationData_.TotalIntervalTime();
    }

    bool IsRuning() const
    {
        return animationData_.IsRuning();
    }

    void UpdateProgressSize(int32_t size);

    float Value() const
    {
        return animationData_.Value();
    }

    int32_t Index() const
    {
        return animationData_.Index();
    }

private:
    void PlayingUpdateTime(int32_t animationTime, int32_t intervalTime);
    void StartProgressAnimation();
    void SetProgressValue(float value);
    void ProgreAnimationStart();
    void ProgreAnimationEnd();
    void StartProgressInterval(int32_t intervalTime);

    int32_t GetProgressSize() const;
    RefPtr<FrameNode> GetProgressNode(int32_t index) const;
    bool SetProgressComponentValue(int32_t index, float value);
    void InitProgressValue();

    RefPtr<FrameNode> GetHost() const;

    void StopAnimation(LinearIndicatorControllerDataState state);

    float RecalcProgressValue(int32_t newAnimationTime);

    void SetValueAndCallback(float value, bool isDraw);

public:
    static constexpr float END_VALUE = 100.0f;
    static constexpr char LINEAR_INDICATOR_ANIMATION_NAME[] = "linear_indicator_animation";
    static constexpr char LINEAR_INDICATOR_INTERVAL_NAME[] = "linear_indicator_interval";
    static constexpr int32_t ANIMATION_TIME_MIN = 1;

private:
    WeakPtr<LinearIndicatorPattern> pattern_;
    LinearIndicatorControllerData animationData_;
    std::function<void(int32_t index, float progress)> changeCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_CONTROLLER_H
