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
ResSchedTouchOptimizer& ResSchedTouchOptimizer::GetInstance()
{
    thread_local ResSchedTouchOptimizer instance;
    return instance;
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
} // namespace OHOS::Ace
