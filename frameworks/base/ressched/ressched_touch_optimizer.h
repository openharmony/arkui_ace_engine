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
#include "ressched_report.h"
#include <deque>

namespace OHOS::Ace {
class ACE_EXPORT ResSchedTouchOptimizer final {
public:
    static ResSchedTouchOptimizer& GetInstance();

    // basic getter adns setters
    void SetSlideAccepted(bool accept);
    void SetLastTpFlush(bool lastTpFlush);
    void SetLastTpFlushCount(uint32_t lastVsyncCount);

    // TP driven drawing
    bool NeedTpFlushVsync(TouchEvent touchEvent, uint32_t currentVsyncCount);

    // RVS Dispatch funcs
    void DispatchPointSelect(bool resampleEnable, TouchEvent& point,
        TouchEvent& resamplePoint, TouchEvent& resultPoint);
    void SelectSinglePoint(std::list<TouchEvent>& touchEvents);
    void RVSQueueUpdate(std::list<TouchEvent>& touchEvents);

    // Dynamic effect chasing
    void SetSlideAcceptOffset(Offset offset);
    double HandleMainDelta(double& mainDelta, const double& touchPointsSize,
        const std::map<int32_t, TouchEvent>& touchPoints);
    bool RVSEnableCheck();

private:
    // RVS Dispatch funcs
    void RVSPointReset(const int32_t pointId, const int32_t info);
    void UpdateDptHistory(const TouchEvent& event);
    void UpdateState(const int32_t id, const int32_t newState, const int32_t axis);
    bool RVSSingleAxisUpdate(TouchEvent& point, TouchEvent& resamplePoint, const bool resampleEnable,
        const int32_t axis, double& result);
    bool HandleState0(const TouchEvent& point, const bool resampleEnable, const int32_t axis, double& result);
    bool HandleState1(const TouchEvent& point, const bool resampleEnable, const int32_t axis, double& result);
    bool HandleState2(const TouchEvent& point, const int32_t axis, double& result);
    bool RVSPointCheckWithoutSignal(TouchEvent& touchPoint, const int32_t axis);
    bool RVSPointCheckWithSignal(TouchEvent& touchPoint, const int32_t axis);


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
    // Record the last VSync count to determine if current TP falls between
    // the last TP triggered early drawing and the next VSync
    uint32_t lastTpFlushCount_ = 0;

    // Dynamic effect chasing
    Offset slideAcceptOffset_{0.0, 0.0};
    float accumulatedDistance_ = 0.0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_TOUCH_OPTIMIZER_H