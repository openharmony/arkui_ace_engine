/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/search/search_gesture_event_hub.h"
namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> SearchGestureEventHub::PackInnerRecognizer(
    const Offset& offset, std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent)
{
    auto recognizer = GestureEventHub::PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
    auto clickEventActuator = GetUserClickEventActuator();
    CHECK_NULL_RETURN(clickEventActuator, recognizer);
    auto clickRecognizer = clickEventActuator->GetClickRecognizer();
    CHECK_NULL_RETURN(clickRecognizer, recognizer);
    clickRecognizer->BeginReferee(touchId, true);
    std::list<RefPtr<NGGestureRecognizer>> innerRecognizersList;
    innerRecognizersList.push_back(recognizer);
    innerRecognizersList.push_back(clickRecognizer);
    if (!innerParallelRecognizer_) {
        innerParallelRecognizer_ = MakeRefPtr<ParallelRecognizer>(std::move(innerRecognizersList));
    } else {
        innerParallelRecognizer_->AddChildren(innerRecognizersList);
    }
    innerParallelRecognizer_->SetCoordinateOffset(offset);
    innerParallelRecognizer_->BeginReferee(touchId);
    auto host = GetFrameNode();
    innerParallelRecognizer_->AttachFrameNode(WeakPtr<FrameNode>(host));
    innerParallelRecognizer_->SetTargetComponent(targetComponent);
    return innerParallelRecognizer_;
}
}