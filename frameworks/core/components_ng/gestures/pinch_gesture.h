/*
* Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PINCH_GESTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PINCH_GESTURE_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT PinchGesture : public Gesture {
    DECLARE_ACE_TYPE(PinchGesture, Gesture);

public:
    PinchGesture(int32_t fingers, double distance, bool limitFingerCount = false) :
        Gesture(fingers, limitFingerCount), distance_(distance)
    {
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::PINCH_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::PINCH_GESTURE);
        } else {
            gestureInfo_ =
                MakeRefPtr<GestureInfo>(GestureTypeName::PINCH_GESTURE, GestureTypeName::PINCH_GESTURE, false);
        }
    }
    ~PinchGesture() override = default;

#ifdef ARKUI_CAPI_UNITTEST
    double GetDistance()
    {
        return distance_;
    }
#endif // ARKUI_CAPI_UNITTEST
protected:
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    double distance_ = 0.0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PINCH_GESTURE_H
