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

#include "core/components_ng/gestures/swipe_gesture.h"

#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> SwipeGesture::CreateRecognizer()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);

    double speed = context->NormalizeToPx(Dimension(speed_, DimensionUnit::VP));
    RefPtr<SwipeRecognizer> swipeRecognizer;
    swipeRecognizer = AceType::MakeRefPtr<SwipeRecognizer>(fingers_, direction_, speed, isLimitFingerCount_);
    if (onActionId_) {
        swipeRecognizer->SetOnAction(*onActionId_);
    }

    swipeRecognizer->SetPriority(priority_);
    swipeRecognizer->SetPriorityMask(gestureMask_);
    swipeRecognizer->SetGestureInfo(gestureInfo_);
    if (gestureInfo_) {
        gestureInfo_->SetDisposeTag(false);
    }
    swipeRecognizer->SetUserData(userData_);
    return swipeRecognizer;
}

} // namespace OHOS::Ace::NG