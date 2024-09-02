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

#include "core/components_ng/gestures/long_press_gesture.h"

#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> LongPressGesture::CreateRecognizer()
{
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(
        duration_, fingers_, repeat_, isForDrag_, isDisableMouseLeft_);
    longPressRecognizer->SetPriority(priority_);
    longPressRecognizer->SetPriorityMask(gestureMask_);
    longPressRecognizer->SetGestureInfo(gestureInfo_);
    if (onActionId_) {
        longPressRecognizer->SetOnAction(*onActionId_);
    }

    if (onActionEndId_) {
        longPressRecognizer->SetOnActionEnd(*onActionEndId_);
    }

    if (onActionCancelId_) {
        longPressRecognizer->SetOnActionCancel(*onActionCancelId_);
    }
    if (gestureInfo_) {
        gestureInfo_->SetDisposeTag(false);
    }
    longPressRecognizer->SetUserData(userData_);

    return longPressRecognizer;
}

} // namespace OHOS::Ace::NG
