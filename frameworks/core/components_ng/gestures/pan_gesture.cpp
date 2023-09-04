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

#include "core/components_ng/gestures/pan_gesture.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> PanGesture::CreateRecognizer()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);

    RefPtr<PanRecognizer> panRecognizer;
    if (panGestureOption_) {
        LOGD("AceType::MakeRefPtr<OHOS::Ace::PanRecognizer>(panGestureOption_)");
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption_);
    } else {
        LOGD("AceType::MakeRefPtr<OHOS::Ace::PanRecognizer>(fingers_, direction_, distance)");
        panRecognizer = AceType::MakeRefPtr<PanRecognizer>(fingers_, direction_, distance_);
    }
    if (onActionStartId_) {
        panRecognizer->SetOnActionStart(*onActionStartId_);
    }

    if (onActionUpdateId_) {
        panRecognizer->SetOnActionUpdate(*onActionUpdateId_);
    }

    if (onActionEndId_) {
        panRecognizer->SetOnActionEnd(*onActionEndId_);
    }

    if (onActionCancelId_) {
        panRecognizer->SetOnActionCancel(*onActionCancelId_);
    }

    panRecognizer->SetPriority(priority_);
    panRecognizer->SetPriorityMask(gestureMask_);
    return panRecognizer;
}

} // namespace OHOS::Ace::NG
