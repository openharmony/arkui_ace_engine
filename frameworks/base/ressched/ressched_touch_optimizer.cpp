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

#include "ressched_touch_optimizer.h"

#include "base/log/ace_trace.h"
#include "base/thread/background_task_executor.h"

namespace {
    // RVS queue size for detecting reverse sliding
    constexpr int32_t RVS_QUEUE_SIZE = 7;
    // RVS queue size for checking reverse signal
    constexpr int32_t DPT_QUEUE_SIZE = 3;
    // Index of the second-to-last element in RVS queue
    constexpr int32_t RVS_QUEUE_RTWO_INDEX = 2;
    // Time gap threshold for clearing RVS data (30ms)
    constexpr int64_t RVS_CLEAR_GAP_TIME = 30 * 1000 * 1000;
    // Initial value for RVS calculations
    constexpr int32_t RVS_INITIAL_VALUE = -10000.0;
    // Compensation extent for initial sliding
    constexpr int32_t COMPENSATE_EXTENT = 4;
    // Threshold for TP use detection
    constexpr double THRESHOLD_TP_USE = 5.0;
    // Threshold for offset value
    constexpr double THRESHOLD_OFFSET_VALUE = 2.0;
    // Coefficient for TP use end calculation
    constexpr double TP_USE_END_COEFFICIENT = 0.6;
    // Direction enum for RVS detection
    enum RVS_DIRECTION : int32_t {
        RVS_NOT_APPLY = 0,      // No reverse signal
        RVS_INITIAL_SIGNAL = 1, // Initial signal
        RVS_DOWN_LEFT = 2,      // Reverse down or left
        RVS_UP_RIGHT = 3,       // Reverse up or right
    };

    // Reset info enum for RVS point reset
    enum RVS_RESET_INFO : int32_t {
        RVS_RESET_ALL = 0,     // Reset all data
        RVS_RESET_CUR_ID = 1,  // Reset current ID data only
    };
    
    // Axis enum for RVS detection
    enum RVS_AXIS : int32_t {
        RVS_AXIS_X = 0,  // X axis
        RVS_AXIS_Y = 1,  // Y axis
    };

    // Fine-tune state enum for RVS processing
    enum RVS_FINETUNE_STATE : int32_t {
        NO_CHANGE = 0,  // No change state
        TP_USE = 1,     // TP use state
        OFFSET = 2,     // Offset state
    };
}

namespace OHOS::Ace {

/*
 * Get the singleton instance of ResSchedTouchOptimizer.
 *
 * Returns:
 *     Reference to the ResSchedTouchOptimizer instance for the current thread.
 */
ResSchedTouchOptimizer& ResSchedTouchOptimizer::GetInstance()
{
    thread_local ResSchedTouchOptimizer instance;
    return instance;
}

/*
 * Set whether the slide is accepted.
 *
 * Parameters:
 *     accept [in] Whether the slide is accepted.
 */
void ResSchedTouchOptimizer::SetSlideAccepted(bool accept)
{
    slideAccepted_ = accept;
}

/*
 * Set whether the last frame was triggered by TP flush.
 *
 * Parameters:
 *     lastTpFlush [in] Whether the last frame was triggered by TP flush.
 */
void ResSchedTouchOptimizer::SetLastTpFlush(bool lastTpFlush)
{
    lastTpFlush_ = lastTpFlush;
}

/*
 * Set the VSync count of the last TP flush.
 *
 * Parameters:
 *     lastVsyncCount [in] The VSync count when the last TP flush occurred.
 */
void ResSchedTouchOptimizer::SetLastTpFlushCount(uint32_t lastVsyncCount)
{
    lastTpFlushCount_ = lastVsyncCount;
}

/*
 * Check if TP flush is needed for the current VSync.
 *
 * Parameters:
 *     touchEvent [in] The current touch event.
 *     currentVsyncCount [in] The current VSync count.
 *
 * Returns:
 *     true if TP flush is needed, false otherwise.
 */
bool ResSchedTouchOptimizer::NeedTpFlushVsync(TouchEvent touchEvent, uint32_t currentVsyncCount)
{
    // RVS is disabled
    if (!RVSEnableCheck()) {
        return false;
    }
    // Non-touch events are not processed
    if (touchEvent.sourceTool != SourceTool::FINGER) {
        return false;
    }
    // If slide is not accepted, trigger TP flush for the first frame
    if (!slideAccepted_) {
        ACE_SCOPED_TRACE("slide first frame scene");
        return true;
    }
    // If last frame was TP triggered and current VSync count differs,
    // trigger TP flush to avoid frame drop
    if (lastTpFlushCount_ != 0 && lastTpFlushCount_ != currentVsyncCount) {
        ACE_SCOPED_TRACE("reversed and need tp flush");
        return true;
    }
    // If current direction is reversed and last frame wasn't TP triggered,
    // trigger TP flush to avoid frame drop
    if (!lastTpFlush_ && (touchEvent.xReverse || touchEvent.yReverse)) {
        ACE_SCOPED_TRACE("slide reversed");
        return true;
    }
    return false;
}

/*
 * Update RVS queue and detect sliding direction reversal signals.
 *
 * Parameters:
 *     touchEvents [in/out] List of touch events to process.
 */
void ResSchedTouchOptimizer::RVSQueueUpdate(std::list<TouchEvent>& touchEvents)
{
    if (!RVSEnableCheck()) {
        return;
    }

    int64_t curTimestamp = GetSysTimestamp();
    // Clear RVS data if time gap exceeds threshold
    if (curTimestamp - lastRVSPointTimeStamp_ >= RVS_CLEAR_GAP_TIME && lastRVSPointTimeStamp_ != 0) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "RVSCheck gap timeout!");
        lastRVSPointTimeStamp_ = 0;
        RVSPointReset(0, RVS_RESET_INFO::RVS_RESET_ALL);
        return;
    }
    lastRVSPointTimeStamp_ = curTimestamp;

    for (auto& iter : touchEvents) {
        if (iter.sourceTool != SourceTool::FINGER) {
            RVSPointReset(0, RVS_RESET_INFO::RVS_RESET_ALL);
            return;
        }
        // Reset RVS data for non-MOVE events
        if (iter.type != TouchType::MOVE) {
            RVSPointReset(iter.id, RVS_RESET_INFO::RVS_RESET_CUR_ID);
            continue;
        }

        // Process X-axis data
        if (!(rvsDequeX_[iter.id].size() >= 1 && rvsDequeX_[iter.id].back() == iter.x)) {
            rvsDequeX_[iter.id].push_back(iter.x);
            if (rvsDequeX_[iter.id].size() >= RVS_QUEUE_SIZE) {
                rvsDequeX_[iter.id].pop_front();
                const int32_t axis = RVS_AXIS::RVS_AXIS_X;
                RVSPointCheckWithSignal(iter, axis) || RVSPointCheckWithoutSignal(iter, axis);
            }
        }

        // Process Y-axis data
        if (!(rvsDequeY_[iter.id].size() >= 1 && rvsDequeY_[iter.id].back() == iter.y)) {
            rvsDequeY_[iter.id].push_back(iter.y);
            if (rvsDequeY_[iter.id].size() >= RVS_QUEUE_SIZE) {
                rvsDequeY_[iter.id].pop_front();
                const int32_t axis = RVS_AXIS::RVS_AXIS_Y;
                RVSPointCheckWithSignal(iter, axis) || RVSPointCheckWithoutSignal(iter, axis);
            }
        }
    }
}

/*
 * Check for sliding direction reversal with existing signal.
 *
 * Parameters:
 *     touchEvent [in/out] Current touch event.
 *     axis [in] Axis identifier (X or Y).
 *
 * Returns:
 *     true if direction reversal is detected, false otherwise.
 */
bool ResSchedTouchOptimizer::RVSPointCheckWithSignal(TouchEvent& touchEvent, const int32_t axis)
{
    double gap = RVS_INITIAL_VALUE;
    double pointBefore = RVS_INITIAL_VALUE;
    double pointCurrent = RVS_INITIAL_VALUE;
    // Get reverse signal for the specified axis
    int32_t rvsSignal = axis == RVS_AXIS::RVS_AXIS_X ? touchEvent.xReverse : touchEvent.yReverse;
    if (rvsSignal == RVS_DIRECTION::RVS_NOT_APPLY) {
        return false;
    }
    // Get deque for the specified axis
    std::deque<double> curDeque = axis == RVS_AXIS::RVS_AXIS_X ? rvsDequeX_[touchEvent.id] : rvsDequeY_[touchEvent.id];
    // Traverse deque from back to front
    for (auto it = curDeque.rbegin(); it != curDeque.rend(); ++it) {
        pointBefore = pointCurrent;
        pointCurrent = *it;
        // Calculate gap for the last element
        if (std::next(it) == curDeque.rend()) {
            gap = pointCurrent - pointBefore;
            uint32_t direction = gap < 0 ? RVS_DIRECTION::RVS_DOWN_LEFT : RVS_DIRECTION::RVS_UP_RIGHT;
            // Update reverse signal for the specified axis
            if (axis == RVS_AXIS::RVS_AXIS_X) {
                touchEvent.xReverse = direction;
                TAG_LOGI(AceLogTag::ACE_UIEVENT, "RVSCheck xReverse with signal");
                ACE_SCOPED_TRACE("RVSCheck signal RVSHappen[%d][%d]", axis, direction);
            } else {
                touchEvent.yReverse = direction;
                TAG_LOGI(AceLogTag::ACE_UIEVENT, "RVSCheck yReverse with signal");
                ACE_SCOPED_TRACE("RVSCheck signal RVSHappen[%d][%d]", axis, direction);
            }
            return true;
        }
    }
    return false;
}

/*
 * Check for sliding direction reversal without existing signal.
 *
 * Parameters:
 *     touchEvent [in/out] Current touch event.
 *     axis [in] Axis identifier (X or Y).
 *
 * Returns:
 *     true if direction reversal is detected, false otherwise.
 */
bool ResSchedTouchOptimizer::RVSPointCheckWithoutSignal(TouchEvent& touchEvent, const int32_t axis)
{
    double gap1 = RVS_INITIAL_VALUE;
    double gap2 = RVS_INITIAL_VALUE;
    double pointBefore = RVS_INITIAL_VALUE;
    double pointCurrent = RVS_INITIAL_VALUE;
    // Get deque for the specified axis
    std::deque<double> curDeque = axis == RVS_AXIS::RVS_AXIS_X ? rvsDequeX_[touchEvent.id] : rvsDequeY_[touchEvent.id];
    // Traverse deque from back to front
    for (auto it = curDeque.rbegin(); it != curDeque.rend(); ++it) {
        if (pointCurrent == RVS_INITIAL_VALUE) {
            pointCurrent = *it;
            continue;
        }
        pointBefore = pointCurrent;
        pointCurrent = *it;
        // Calculate first gap
        if (gap1 == RVS_INITIAL_VALUE) {
            gap1 = pointCurrent - pointBefore;
        } else {
            // Calculate second gap and compare signs
            gap2 = pointCurrent - pointBefore;
            if ((gap2 >= 0) == (gap1 >= 0)) {
                return false;
            }
        }
        // Process the last element
        if (std::next(it) == curDeque.rend()) {
            uint32_t direction = gap2 < 0 ? RVS_DIRECTION::RVS_DOWN_LEFT : RVS_DIRECTION::RVS_UP_RIGHT;
            // Update reverse signal for the specified axis
            if (axis == RVS_AXIS::RVS_AXIS_X) {
                touchEvent.xReverse = direction;
                TAG_LOGI(AceLogTag::ACE_UIEVENT, "RVSCheck xReverse without signal");
                ACE_SCOPED_TRACE("RVSCheck signal RVSHappen[%d][%d]", axis, direction);
                return true;
            } else {
                touchEvent.yReverse = direction;
                TAG_LOGI(AceLogTag::ACE_UIEVENT, "RVSCheck yReverse without signal");
                ACE_SCOPED_TRACE("RVSCheck signal RVSHappen[%d][%d]", axis, direction);
                return true;
            }
        }
    }
    return false;
}

/*
 * Reset RVS-related state data for specified ID or all data.
 *
 * Parameters:
 *     id [in] Touch point ID.
 *     resetInfo [in] Reset type (all data or current ID data).
 */
void ResSchedTouchOptimizer::RVSPointReset(int32_t id, const int32_t resetInfo)
{
    // Reset data for current ID
    if (resetInfo == RVS_RESET_INFO::RVS_RESET_CUR_ID) {
        dptHistoryPointX_.erase(id);
        dptHistoryPointY_.erase(id);
        rvsDequeX_.erase(id);
        rvsDequeY_.erase(id);
        stateTagX_.erase(id);
        stateTagY_.erase(id);
        dptGapX_.erase(id);
        dptGapY_.erase(id);
    }
    // Reset all data
    if (resetInfo == RVS_RESET_INFO::RVS_RESET_ALL) {
        lastRVSPointTimeStamp_ = 0;
        dptHistoryPointX_.clear();
        dptHistoryPointY_.clear();
        rvsDequeX_.clear();
        rvsDequeY_.clear();
        stateTagX_.clear();
        stateTagY_.clear();
        dptGapX_.clear();
        dptGapY_.clear();
    }
}

/*
 * Update state tag for the specified axis.
 *
 * Parameters:
 *     id [in] Touch point ID.
 *     state [in] New state value.
 *     axis [in] Axis identifier (X or Y).
 */
void ResSchedTouchOptimizer::UpdateState(const int32_t id, const int32_t state, const int32_t axis)
{
    std::unordered_map<int32_t, int32_t>& stateTag = (axis == RVS_AXIS::RVS_AXIS_X) ? stateTagX_ : stateTagY_;
    stateTag[id] = state;
    ACE_SCOPED_TRACE("RVSCheck state changed[%d][%d]", axis, stateTag[id]);
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "RVSCheck state changed[%d][%d]", axis, stateTag[id]);
}

/*
 * Select final touch point based on resampling enable status and perform RVS optimization.
 *
 * Parameters:
 *     resampleEnable [in] Whether resampling is enabled.
 *     point [in] Original touch point.
 *     resamplePoint [in] Resampled touch point.
 *     resultPoint [out] Final processed touch point.
 */
void ResSchedTouchOptimizer::DispatchPointSelect(bool resampleEnable, TouchEvent& point,
    TouchEvent& resamplePoint, TouchEvent& resultPoint)
{
    if (resampleEnable) {
        resultPoint = resamplePoint;
    } else {
        resultPoint = point;
    }

    if (!RVSEnableCheck()) {
        return;
    }

    if (point.sourceTool != SourceTool::FINGER) {
        return;
    }

    double resultValue;
    if (RVSSingleAxisUpdate(point, resamplePoint, resampleEnable, RVS_AXIS::RVS_AXIS_X, resultValue)) {
        resultPoint.x = resultValue;
    }
    if (RVSSingleAxisUpdate(point, resamplePoint, resampleEnable, RVS_AXIS::RVS_AXIS_Y, resultValue)) {
        resultPoint.y = resultValue;
    }
    UpdateDptHistory(resultPoint);
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "RVSCheck finally touchEvents.x = %{public}s touchEvents.y = %{public}s",
        std::to_string(resultPoint.x).c_str(), std::to_string(resultPoint.y).c_str());
}

/*
 * Check if RVS feature is enabled, which is determined by the config in RSS.
 *
 * Returns:
 *     true if RVS feature is enabled, false otherwise.
 */
bool ResSchedTouchOptimizer::RVSEnableCheck()
{
    std::call_once(rvsOnceFlag_, [this]() {
        auto task = [this]() {
            std::unordered_map<std::string, std::string> payload;
            std::unordered_map<std::string, std::string> reply;
            payload["bundleName"] = AceApplicationInfo::GetInstance().GetPackageName();
            rvsEnable_ = ResSchedReport::GetInstance().AppRVSEnableCheck(payload, reply);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "RVS_ENABLE_CHECK Result: %{public}d", static_cast<int32_t>(rvsEnable_));
        };
        BackgroundTaskExecutor::GetInstance().PostTask(task);
    });
    return rvsEnable_;
}

/*
 * Select single point with direction reversal from touch events list.
 *
 * Parameters:
 *     touchEvents [in/out] List of touch events to process.
 */
void ResSchedTouchOptimizer::SelectSinglePoint(std::list<TouchEvent>& touchEvents)
{
    if (!RVSEnableCheck()) {
        return;
    }

    // Group points by ID
    std::map<int, std::list<TouchEvent>> groupedPoints;
    for (const auto& point : touchEvents) {
        if (point.sourceTool != SourceTool::FINGER) {
            return;
        }
        groupedPoints[point.id].push_back(point);
    }
    
    std::list<TouchEvent> selectedPoints;
    // Process each group
    for (auto& pointGroup : groupedPoints) {
        auto& points = pointGroup.second;
        TouchEvent selectedPoint;
        bool foundReverse = false;

        // Find point with direction reversal
        for (auto& point : points) {
            if (point.xReverse != 0 || point.yReverse != 0) {
                selectedPoint = point;
                foundReverse = true;
                break;
            }
        }

        // If no reversal found, use the last point
        if (!foundReverse && !points.empty()) {
            selectedPoint = points.back();
        }
        // Add selected point to result if reversal was found
        if (foundReverse && !points.empty()) {
            selectedPoints.push_back(selectedPoint);
        }
    }
    touchEvents.clear();
    touchEvents = std::move(selectedPoints);
}

/*
 * Update Dispatch history records.
 *
 * Parameters:
 *     event [in] Current touch event.
 */
void ResSchedTouchOptimizer::UpdateDptHistory(const TouchEvent& event)
{
    if (dptHistoryPointX_[event.id].size() >= DPT_QUEUE_SIZE) {
        dptHistoryPointX_[event.id].pop_front();
    }
    dptHistoryPointX_[event.id].push_back(event.x);
    
    if (dptHistoryPointY_[event.id].size() >= DPT_QUEUE_SIZE) {
        dptHistoryPointY_[event.id].pop_front();
    }
    dptHistoryPointY_[event.id].push_back(event.y);
}

/*
 * Handle main axis delta value for compensating initial sliding offset.
 *
 * Parameters:
 *     mainDelta [in] Main axis delta value.
 *     touchPointsSize [in] Number of touch points.
 *
 * Returns:
 *     Compensated delta value.
 */
double ResSchedTouchOptimizer::HandleMainDelta(double& mainDelta, const double& touchPointsSize,
    const std::map<int32_t, TouchEvent>& touchPoints)
{
    if (touchPointsSize <= 0) {
        return mainDelta;
    }
    double main_Delta = mainDelta / touchPointsSize;
    if (!RVSEnableCheck()) {
        return main_Delta;
    }

    for (const auto& it : touchPoints) {
        if (it.second.sourceTool != SourceTool::FINGER) {
            return main_Delta;
        }
    }
    // Apply compensation if accumulated distance is less than slide accept offset
    if (accumulatedDistance_ < slideAcceptOffset_.GetDistance()) {
        main_Delta = main_Delta + main_Delta / COMPENSATE_EXTENT;
        accumulatedDistance_ += fabs(main_Delta / COMPENSATE_EXTENT);
        ACE_SCOPED_TRACE("BeforeMainDelta %f, AfterMainDelta %f", mainDelta / touchPointsSize, main_Delta);
    }
    return main_Delta;
}

/*
 * Set slide accept offset.
 *
 * Parameters:
 *     offset [in] Slide accept offset.
 */
void ResSchedTouchOptimizer::SetSlideAcceptOffset(Offset offset)
{
    if (!RVSEnableCheck()) {
        slideAcceptOffset_.SetX(offset.GetX());
        slideAcceptOffset_.SetY(offset.GetY());
        accumulatedDistance_ = 0.0;
        ACE_SCOPED_TRACE("slideAcceptOffset_X %f, slideAcceptOffset_Y %f", offset.GetX(), offset.GetY());
    }
}

/*
 * Update single axis for RVS optimization.
 *
 * Parameters:
 *     point [in] Original touch point.
 *     resamplePoint [in] Resampled touch point.
 *     resampleEnable [in] Whether resampling is enabled.
 *     axis [in] Axis identifier (X or Y).
 *     result [out] Optimized result value.
 *
 * Returns:
 *     true if optimization was applied, false otherwise.
 */
bool ResSchedTouchOptimizer::RVSSingleAxisUpdate(TouchEvent& point, TouchEvent& resamplePoint,
    const bool resampleEnable, const int32_t axis, double& result)
{
    int32_t id = point.id;
    std::unordered_map<int32_t, int32_t>& stateTag = (axis == RVS_AXIS::RVS_AXIS_X) ? stateTagX_ : stateTagY_;
    bool changeState = false;
    
    // Handle different states
    if (stateTag[id] == RVS_FINETUNE_STATE::NO_CHANGE) {
        changeState = HandleState0(point, resampleEnable, axis, result);
    }
    if (stateTag[id] == RVS_FINETUNE_STATE::TP_USE) {
        changeState = HandleState1(point, resampleEnable, axis, result);
    }
    if (stateTag[id] == RVS_FINETUNE_STATE::OFFSET) {
        changeState = HandleState2(point, axis, result);
    }
    return changeState;
}

/*
 * Handle state 0 (NO_CHANGE) for RVS optimization logic.
 *
 * Parameters:
 *     point [in] Current touch point.
 *     resampleEnable [in] Whether resampling is enabled.
 *     axis [in] Axis identifier (X or Y).
 *     result [out] Optimized result value.
 *
 * Returns:
 *     true if optimization was applied, false otherwise.
 */
bool ResSchedTouchOptimizer::HandleState0(const TouchEvent& point, const bool resampleEnable, const int32_t axis,
    double& result)
{
    int32_t id = point.id;
    double pointNow = (axis == RVS_AXIS::RVS_AXIS_X) ? point.x : point.y;
    const std::deque<double>& dptQueue = (axis == RVS_AXIS::RVS_AXIS_X) ? dptHistoryPointX_[id] : dptHistoryPointY_[id];

    // Check if enough history points are available
    if (dptQueue.size() < DPT_QUEUE_SIZE) {
        return false;
    }

    // Transition to TP_USE state if point movement is small
    if (std::abs(dptQueue.back() - pointNow) <= THRESHOLD_TP_USE) {
        UpdateState(id, RVS_FINETUNE_STATE::TP_USE, axis);
        result = pointNow;
        return true;
    }

    return false;
}

/*
 * Handle state 1 (TP_USE) for RVS optimization logic.
 *
 * Parameters:
 *     point [in] Current touch point.
 *     resampleEnable [in] Whether resampling is enabled.
 *     axis [in] Axis identifier (X or Y).
 *     result [out] Optimized result value.
 *
 * Returns:
 *     true if optimization was applied, false otherwise.
 */
bool ResSchedTouchOptimizer::HandleState1(const TouchEvent& point, const bool resampleEnable, const int32_t axis,
    double& result)
{
    int32_t id = point.id;
    double pointNow = (axis == RVS_AXIS::RVS_AXIS_X) ? point.x : point.y;
    const std::deque<double>& dptQueue = (axis == RVS_AXIS::RVS_AXIS_X) ? dptHistoryPointX_[id] : dptHistoryPointY_[id];
    std::unordered_map<int32_t, double>& dptGap = (axis == RVS_AXIS::RVS_AXIS_X) ? dptGapX_ : dptGapY_;
    int32_t rvsSignal = (axis == RVS_AXIS::RVS_AXIS_X) ? point.xReverse : point.yReverse;

    // Handle reverse signal
    if (rvsSignal) {
        // Transition to OFFSET state if rvsPoint is not sent to display
        if (rvsSignal == RVS_DIRECTION::RVS_DOWN_LEFT) {
            // Process down/left direction
            if (dptQueue[dptQueue.size() - RVS_QUEUE_RTWO_INDEX] <= pointNow) {
                dptGap[id] = dptQueue.back() - dptQueue[dptQueue.size() - RVS_QUEUE_RTWO_INDEX];
                UpdateState(id, RVS_FINETUNE_STATE::OFFSET, axis);
                return false;
            }
            if (pointNow - dptQueue.back() >= 0) {
                dptGap[id] = THRESHOLD_OFFSET_VALUE;
                UpdateState(id, RVS_FINETUNE_STATE::OFFSET, axis);
                return false;
            }
        } else if (rvsSignal == RVS_DIRECTION::RVS_UP_RIGHT) {
            // Process up/right direction
            if (dptQueue[dptQueue.size() - RVS_QUEUE_RTWO_INDEX] >= pointNow) {
                dptGap[id] = dptQueue.back() - dptQueue[dptQueue.size() - RVS_QUEUE_RTWO_INDEX];
                UpdateState(id, RVS_FINETUNE_STATE::OFFSET, axis);
                return false;
            }
            if (pointNow - dptQueue.back() <= 0) {
                dptGap[id] = -THRESHOLD_OFFSET_VALUE;
                UpdateState(id, RVS_FINETUNE_STATE::OFFSET, axis);
                return false;
            }
        }
    }

    // Transition back to NO_CHANGE state if movement is large
    if (resampleEnable && std::abs(pointNow - dptQueue.back()) > THRESHOLD_TP_USE) {
        UpdateState(id, RVS_FINETUNE_STATE::NO_CHANGE, axis);
        result = dptQueue.back() * (1 - TP_USE_END_COEFFICIENT) + pointNow * TP_USE_END_COEFFICIENT;
        return true;
    }
    result = pointNow;
    return true;
}

/*
 * Handle state 2 (OFFSET) for RVS optimization logic.
 *
 * Parameters:
 *     point [in] Current touch point.
 *     axis [in] Axis identifier (X or Y).
 *     result [out] Optimized result value.
 *
 * Returns:
 *     true if optimization was applied, false otherwise.
 */
bool ResSchedTouchOptimizer::HandleState2(const TouchEvent& point, const int32_t axis, double& result)
{
    int32_t id = point.id;
    double pointNow = (axis == RVS_AXIS::RVS_AXIS_X) ? point.x : point.y;
    const double& dptGap = (axis == RVS_AXIS::RVS_AXIS_X) ? dptGapX_[id] : dptGapY_[id];
    const std::deque<double>& dptQueue = (axis == RVS_AXIS::RVS_AXIS_X) ? dptHistoryPointX_[id] : dptHistoryPointY_[id];

    // Transition back to NO_CHANGE state if condition is met
    if ((dptGap > 0 && (dptQueue.back() - pointNow) < 0) || (dptGap < 0 && (pointNow - dptQueue.back()) < 0)) {
        UpdateState(id, RVS_FINETUNE_STATE::NO_CHANGE, axis);
        result = pointNow;
        return true;
    }

    // Apply offset compensation
    result = pointNow - dptGap;
    return true;
}

}