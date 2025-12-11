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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_TOUCH_OPTIMIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_TOUCH_OPTIMIZER_H

#include "core/event/touch_event.h"
#include <deque>
#include <mutex>

namespace OHOS::Ace {
class ACE_EXPORT ResSchedTouchOptimizer final {
public:
    ResSchedTouchOptimizer();
    ~ResSchedTouchOptimizer();

    // basic getter and setters
    void SetSlideAccepted(bool accept);
    void SetLastTpFlush(bool lastTpFlush);
    void SetSlideDirection(int32_t direction);
    void SetLastVsyncTimeStamp(uint64_t lastVsyncTimeStamp);
    void SetVsyncPeriod(uint64_t vsyncPeriod);
    bool GetIsTpFlushFrameDisplayPeriod() const;
    bool GetIsFirstFrameAfterTpFlushFrameDisplayPeriod() const;

    // TP driven drawing
    bool NeedTpFlushVsync(const TouchEvent& touchEvent);

    // RVS Dispatch funcs
    void DispatchPointSelect(bool resampleEnable, TouchEvent& point,
        TouchEvent& resamplePoint, TouchEvent& resultPoint);
    TouchEvent SetPointReverseSignal(const TouchEvent& point);
    // Dynamic effect chasing
    void SetSlideAcceptOffset(Offset offset);
    double HandleMainDelta(double& mainDelta, const double& touchPointsSize,
        const std::map<int32_t, TouchEvent>& touchPoints);
    bool RVSEnableCheck();

    void SetHisAvgPointTimeStamp(const int32_t pointId,
        const std::unordered_map<int32_t, std::vector<TouchEvent>>& historyPointsById);
    
    uint64_t FineTuneTimeStampDuringTpFlushPeriod(uint64_t timeStamp);
    void FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod(const int32_t pointId,
        std::unordered_map<int32_t, std::vector<TouchEvent>>& historyPointsById);
    void EndTpFlushVsyncPeriod();
private:
    // RVS Dispatch funcs
    void RVSPointReset(const int32_t pointId, const int32_t info);
    void RVSQueueUpdate(std::list<TouchEvent>& touchEvents);
    void UpdateDptHistory(const TouchEvent& event);
    void UpdateState(const int32_t id, const int32_t newState, const int32_t axis);
    bool RVSSingleAxisUpdate(TouchEvent& point, TouchEvent& resamplePoint, const bool resampleEnable,
        const int32_t axis, double& result);
    bool HandleState0(const TouchEvent& point, const bool resampleEnable, const int32_t axis, double& result);
    bool HandleState1(const TouchEvent& point, const bool resampleEnable, const int32_t axis, double& result);
    bool HandleState2(const TouchEvent& point, const int32_t axis, double& result);
    bool RVSPointCheckWithoutSignal(TouchEvent& touchPoint, const int32_t axis);
    bool RVSPointCheckWithSignal(TouchEvent& touchPoint, const int32_t axis);
    bool RVSDirectionStateCheck(uint32_t rvsDirection);

    // tpFlush related funcs
    bool NeedTpFlushVsyncInner(const TouchEvent& touchEvent);

    // revord tp report point and dispatch point;
    std::unordered_map<int32_t, double> dptGapX_;
    std::unordered_map<int32_t, double> dptGapY_;
    std::unordered_map<int32_t, std::deque<double>> dptHistoryPointX_;
    std::unordered_map<int32_t, std::deque<double>> dptHistoryPointY_;
    // switch to use resamplePoint or toPoint or fine-tuning
    std::unordered_map<int32_t, int32_t> stateTagX_;
    std::unordered_map<int32_t, int32_t> stateTagY_;
    // record different coordinate  values of tp point
    std::unordered_map<int32_t, std::deque<double>> rvsDequeX_;
    std::unordered_map<int32_t, std::deque<double>> rvsDequeY_;
    // record timestamp of last move event
    int64_t lastRVSPointTimeStamp_ = 0;
    std::once_flag rvsOnceFlag_;
    std::atomic_bool rvsEnable_ = false;

    // Default value is true, set to false when pan recognizer down, set to true when accept
    std::atomic_bool slideAccepted_ = true;
    // Whether the last frame drawing was triggered by TP
    std::atomic_bool lastTpFlush_ = false;

    // Dynamic effect chasing
    Offset slideAcceptOffset_{0.0, 0.0};
    float accumulatedDistance_ = 0.0;

    int32_t slideDirection_ = 0;

    uint64_t vsyncPeriod_ = std::numeric_limits<uint64_t>::max();
    uint64_t lastVsyncTimeStamp_ = 0;
    uint64_t hisAvgPointTimeStamp_ = 0;
    bool vsyncTimeReportExemption_ = false;
    bool isTpFlushFrameDisplayPeriod_ = false;
    bool isFristFrameAfterTpFlushFrameDisplayPeriod_ = false;
    bool vsyncFlushed_ = false;
    bool rvsSignalEnable_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_TOUCH_OPTIMIZER_H