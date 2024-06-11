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

#include "core/components_ng/gestures/rotation_gesture.h"

#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MAX_ANGLE = 360.0;
} // namespace

RotationGesture::RotationGesture(int32_t fingers, double angle) : Gesture(fingers)
{
    if (angle > MAX_ANGLE || angle <= 0) {
        angle_ = 1.0;
    } else {
        angle_ = angle;
    }
    if (gestureInfo_) {
        gestureInfo_->SetType(GestureTypeName::ROTATION_GESTURE);
        gestureInfo_->SetRecognizerType(GestureTypeName::ROTATION_GESTURE);
    } else {
        gestureInfo_ =
            MakeRefPtr<GestureInfo>(GestureTypeName::ROTATION_GESTURE, GestureTypeName::ROTATION_GESTURE, false);
    }
}
RefPtr<NGGestureRecognizer> RotationGesture::CreateRecognizer()
{
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(fingers_, angle_);
    if (onActionStartId_) {
        rotationRecognizer->SetOnActionStart(*onActionStartId_);
    }

    if (onActionUpdateId_) {
        rotationRecognizer->SetOnActionUpdate(*onActionUpdateId_);
    }

    if (onActionEndId_) {
        rotationRecognizer->SetOnActionEnd(*onActionEndId_);
    }

    if (onActionCancelId_) {
        rotationRecognizer->SetOnActionCancel(*onActionCancelId_);
    }

    rotationRecognizer->SetPriority(priority_);
    rotationRecognizer->SetPriorityMask(gestureMask_);
    rotationRecognizer->SetGestureInfo(gestureInfo_);
    rotationRecognizer->SetUserData(userData_);
    return rotationRecognizer;
}

} // namespace OHOS::Ace::NG
