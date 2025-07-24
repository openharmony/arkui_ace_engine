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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_LONG_PRESS_GESTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_LONG_PRESS_GESTURE_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT LongPressGesture : public Gesture {
    DECLARE_ACE_TYPE(LongPressGesture, Gesture);

public:
    LongPressGesture(
        int32_t fingers, bool repeat, int32_t duration, bool isForDrag = false, bool isDisableMouseLeft = false,
        bool isLimitFingerCount = false)
        : Gesture(fingers, isLimitFingerCount), repeat_(repeat), duration_(duration), isForDrag_(isForDrag),
          isDisableMouseLeft_(isDisableMouseLeft)
    {
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::LONG_PRESS_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::LONG_PRESS_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(
                GestureTypeName::LONG_PRESS_GESTURE, GestureTypeName::LONG_PRESS_GESTURE, false);
        }
    }
    ~LongPressGesture() override = default;

#ifdef ARKUI_CAPI_UNITTEST
    bool GetRepeat()
    {
        return repeat_;
    }

    int32_t GetDuration()
    {
        return duration_;
    }
#endif // ARKUI_CAPI_UNITTEST
protected:
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    bool repeat_ = false;
    int32_t duration_ = 500;
    bool isForDrag_ = false;
    bool isDisableMouseLeft_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_LONG_PRESS_GESTURE_H
