/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_MULTI_FINGERS_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_MULTI_FINGERS_RECOGNIZER_H

#include <list>
#include <map>

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

class MultiFingersRecognizer : public NGGestureRecognizer {
    DECLARE_ACE_TYPE(MultiFingersRecognizer, NGGestureRecognizer);

public:
    MultiFingersRecognizer() = default;
    explicit MultiFingersRecognizer(int32_t fingers);

    ~MultiFingersRecognizer() override = default;

    void UpdateFingerListInfo(const Offset& coordinateOffset);

    bool CheckTouchId(int32_t touchId) override
    {
        return touchPoints_.find(touchId) != touchPoints_.end();
    }

    int GetFingers()
    {
        return fingers_;
    }

protected:
    void OnBeginGestureReferee(int32_t touchId, bool needUpdateChild = false) override
    {
        touchPoints_[touchId] = {};
    }

    void OnFinishGestureReferee(int32_t touchId, bool isBlocked) override
    {
        touchPoints_.erase(touchId);
        if (touchPoints_.empty()) {
            ResetStatusOnFinish(isBlocked);
        }
    }

    void OnResetStatus() override
    {
        touchPoints_.clear();
        fingerList_.clear();
    }

    std::map<int32_t, TouchEvent> touchPoints_;
    std::list<FingerInfo> fingerList_;

    int32_t fingers_ = 1;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_MULTI_FINGERS_RECOGNIZER_H
