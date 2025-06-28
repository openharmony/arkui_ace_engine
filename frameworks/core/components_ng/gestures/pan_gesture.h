/*
* Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT PanGesture : public Gesture {
    DECLARE_ACE_TYPE(PanGesture, Gesture);

public:
    PanGesture(int32_t fingers, const PanDirection& direction, double distance, bool isLimitFingerCount = false)
    {
        fingers_ = fingers;
        direction_ = direction;
        distance_ = distance;
        distanceMap_[SourceTool::UNKNOWN] = Dimension(
            Dimension(distance_, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
        isLimitFingerCount_ = isLimitFingerCount;
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::PAN_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::PAN_GESTURE, GestureTypeName::PAN_GESTURE, false);
        }
    };
    PanGesture(int32_t fingers, const PanDirection& direction, const PanDistanceMapDimension& distanceMap,
        bool isLimitFingerCount = false);
    explicit PanGesture(RefPtr<PanGestureOption> panGestureOption)
    {
        panGestureOption_ = panGestureOption;
        if (gestureInfo_) {
            gestureInfo_->SetType(GestureTypeName::PAN_GESTURE);
            gestureInfo_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::PAN_GESTURE, GestureTypeName::PAN_GESTURE, false);
        }
    };
    ~PanGesture() override = default;

    void SerializeTo(char* buff);
    
    virtual int32_t SizeofMe() override;

    int32_t Serialize(char* panGesture) override;

    virtual int32_t Deserialize(const char* buff) override;

    void SetDistanceMap(const PanDistanceMapDimension& distanceMap);

    PanDistanceMapDimension GetDistanceMap() const
    {
        return distanceMap_;
    }

protected:
    RefPtr<NGGestureRecognizer> CreateRecognizer() override;

private:
    PanDirection direction_;
    double distance_ = 0.0;
    PanDistanceMapDimension distanceMap_;
    RefPtr<PanGestureOption> panGestureOption_;
    Matrix4 matrix_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_PAN_GESTURE_H
