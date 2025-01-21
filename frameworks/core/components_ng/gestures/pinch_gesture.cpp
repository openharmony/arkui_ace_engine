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

#include "core/components_ng/gestures/pinch_gesture.h"

#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> PinchGesture::CreateRecognizer()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, nullptr);

    double distance = context->NormalizeToPx(Dimension(distance_, DimensionUnit::VP));
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(fingers_, distance, isLimitFingerCount_);
    if (onActionStartId_) {
        pinchRecognizer->SetOnActionStart(*onActionStartId_);
    }

    if (onActionUpdateId_) {
        pinchRecognizer->SetOnActionUpdate(*onActionUpdateId_);
    }

    if (onActionEndId_) {
        pinchRecognizer->SetOnActionEnd(*onActionEndId_);
    }

    if (onActionCancelId_) {
        pinchRecognizer->SetOnActionCancel(*onActionCancelId_);
    }

    pinchRecognizer->SetPriority(priority_);
    pinchRecognizer->SetPriorityMask(gestureMask_);
    pinchRecognizer->SetGestureInfo(gestureInfo_);
    pinchRecognizer->SetUserData(userData_);

    return pinchRecognizer;
}

} // namespace OHOS::Ace::NG
