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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_TAP_GESTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_TAP_GESTURE_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT TapGesture : public Gesture {
    DECLARE_ACE_TYPE(TapGesture, Gesture);

public:
    TapGesture()
    {
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::TAP_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::TAP_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::TAP_GESTURE, GestureTypeName::TAP_GESTURE, false);
        }
    }
    TapGesture(int32_t count, int32_t fingers, double distanceThreshold = std::numeric_limits<double>::infinity(),
        bool isLimitFingerCount = false) : Gesture(fingers, isLimitFingerCount), count_(count)
    {
        distanceThreshold_ = Dimension(
            Dimension(distanceThreshold, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::TAP_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::TAP_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::TAP_GESTURE, GestureTypeName::TAP_GESTURE, false);
        }
    }
    TapGesture(int32_t count, int32_t fingers, Dimension distanceThreshold, bool isLimitFingerCount = false);
    ~TapGesture() override = default;

    int32_t GetTapCount() const
    {
        return count_;
    }

protected:
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    int32_t count_ = 1;
    Dimension distanceThreshold_ = Dimension(std::numeric_limits<double>::infinity(), DimensionUnit::PX);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_TAP_GESTURE_H
