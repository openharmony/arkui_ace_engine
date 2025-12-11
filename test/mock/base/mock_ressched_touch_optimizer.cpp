// test/mock/base/mock_ressched_touch_optimizer.cpp
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

#include "base/ressched/ressched_touch_optimizer.h"

namespace OHOS::Ace {

namespace {
    // Reset info enum for RVS point reset
    enum RVS_RESET_INFO : int32_t {
        RVS_RESET_ALL = 0,     // Reset all data
        RVS_RESET_CUR_ID = 1,  // Reset current ID data only
    };
}

ResSchedTouchOptimizer::ResSchedTouchOptimizer()
{
}

ResSchedTouchOptimizer::~ResSchedTouchOptimizer()
{
}


void ResSchedTouchOptimizer::SetSlideAccepted(bool accept)
{
}

double ResSchedTouchOptimizer::HandleMainDelta(double& mainDelta, const double& touchPointsSize,
    const std::map<int32_t, TouchEvent>& touchPoints)
{
    if (touchPointsSize <= 0) {
        return mainDelta;
    }
    return mainDelta / touchPointsSize;
}

void ResSchedTouchOptimizer::SetSlideAcceptOffset(Offset offset)
{
}

void ResSchedTouchOptimizer::SetSlideDirection(int32_t slideDirection)
{
}

void ResSchedTouchOptimizer::SetVsyncPeriod(uint64_t vsyncPeriod)
{
}

bool ResSchedTouchOptimizer::GetIsTpFlushFrameDisplayPeriod() const
{
    return isTpFlushFrameDisplayPeriod_;
}

bool ResSchedTouchOptimizer::GetIsFirstFrameAfterTpFlushFrameDisplayPeriod() const
{
    return isFristFrameAfterTpFlushFrameDisplayPeriod_;
}

bool ResSchedTouchOptimizer::NeedTpFlushVsync(const TouchEvent& touchEvent)
{
    return isTpFlushFrameDisplayPeriod_;
}

TouchEvent ResSchedTouchOptimizer::SetPointReverseSignal(const TouchEvent& inputEvent)
{
    return inputEvent;
}

void ResSchedTouchOptimizer::SetHisAvgPointTimeStamp(int32_t pointId,
    const std::unordered_map<int32_t, std::vector<TouchEvent>>& historyPointsById)
{
}

uint64_t ResSchedTouchOptimizer::FineTuneTimeStampDuringTpFlushPeriod(uint64_t timeStamp)
{
    // only Mock Behavior
    isTpFlushFrameDisplayPeriod_ = false;
    return timeStamp;
}

void ResSchedTouchOptimizer::FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod(const int32_t pointId,
    std::unordered_map<int32_t, std::vector<TouchEvent>>& historyPointsById)
{
    // only Mock Behavior
    historyPointsById.clear();
}

void ResSchedTouchOptimizer::SetLastVsyncTimeStamp(uint64_t timeStamp)
{
}

bool ResSchedTouchOptimizer::RVSEnableCheck()
{
    return rvsEnable_;
}

void ResSchedTouchOptimizer::DispatchPointSelect(bool hasResamplePoint, TouchEvent& tpPoint,
    TouchEvent& resamplePoint, TouchEvent& resultPoint)
{
    resultPoint = hasResamplePoint ? resamplePoint : tpPoint;
}

void ResSchedTouchOptimizer::EndTpFlushVsyncPeriod()
{
    lastTpFlush_ = false;
    vsyncPeriod_ = 0;
    lastVsyncTimeStamp_ = 0;
    hisAvgPointTimeStamp_ = 0;
    vsyncTimeReportExemption_ = false;
    vsyncFlushed_ = false;
    isTpFlushFrameDisplayPeriod_ = false;
    isFristFrameAfterTpFlushFrameDisplayPeriod_ = false;
}
} // namespace OHOS::Ace