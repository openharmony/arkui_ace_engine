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

#include "core/components_ng/gestures/tap_gesture.h"

#include "core/components_ng/gestures/recognizers/click_recognizer.h"

namespace OHOS::Ace::NG {
TapGesture::TapGesture(int32_t count, int32_t fingers, Dimension distanceThreshold, bool isLimitFingerCount)
    : Gesture(fingers, isLimitFingerCount), count_(count), distanceThreshold_(distanceThreshold)
{
    if (gestureInfo_) {
        gestureInfo_->SetType(GestureTypeName::TAP_GESTURE);
        gestureInfo_->SetRecognizerType(GestureTypeName::TAP_GESTURE);
    } else {
        gestureInfo_ = MakeRefPtr<GestureInfo>(GestureTypeName::TAP_GESTURE, GestureTypeName::TAP_GESTURE, false);
    }
}

RefPtr<NGGestureRecognizer> TapGesture::CreateRecognizer()
{
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(
        fingers_, count_, distanceThreshold_, isLimitFingerCount_);
    if (onActionId_) {
        clickRecognizer->SetOnAction(*onActionId_);
    }
    if (gestureInfo_) {
        gestureInfo_->SetDisposeTag(false);
    }
    clickRecognizer->SetPriority(priority_);
    clickRecognizer->SetPriorityMask(gestureMask_);
    clickRecognizer->SetGestureInfo(gestureInfo_);
    if (gestureInfo_) {
        gestureInfo_->SetDisposeTag(false);
    }
    clickRecognizer->SetUserData(userData_);
    return clickRecognizer;
}

} // namespace OHOS::Ace::NG
