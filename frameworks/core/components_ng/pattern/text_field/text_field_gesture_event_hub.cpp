/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_gesture_event_hub.h"

#include "core/components_ng/pattern/text_field/text_field_free_scroller.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> TextFieldGestureEventHub::PackInnerRecognizer(const Offset& offset,
    std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId, int32_t originalId,
    const RefPtr<TargetComponent>& targetComponent)
{
    auto recognizer =
        GestureEventHub::PackInnerRecognizer(offset, innerRecognizers, touchId, originalId, targetComponent);
    std::list<RefPtr<NGGestureRecognizer>> innerRecognizersList;
    innerRecognizersList.push_back(recognizer);
    AddScrollGestureRecognizer(innerRecognizersList);
    if (innerRecognizersList.size() == 1) {
        return recognizer;
    }
    auto exclusiveRecognizer = MakeRefPtr<ExclusiveRecognizer>(std::move(innerRecognizersList));
    exclusiveRecognizer->SetCoordinateOffset(offset);
    exclusiveRecognizer->BeginReferee(touchId, originalId, true);
    auto host = GetFrameNode();
    exclusiveRecognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
    exclusiveRecognizer->SetTargetComponent(targetComponent);
    return exclusiveRecognizer;
}

void TextFieldGestureEventHub::AddScrollGestureRecognizer(std::list<RefPtr<NGGestureRecognizer>>& innerRecognizersList)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto scrollController = textFieldPattern->GetFreeScroller();
    CHECK_NULL_VOID(scrollController);
    auto recognizer = scrollController->GetScrollGestureRecognizer();
    CHECK_NULL_VOID(recognizer);
    innerRecognizersList.push_back(recognizer);
}

RefPtr<GestureEventHub> TextFieldEventHub::CreateGestureEventHub()
{
    return MakeRefPtr<TextFieldGestureEventHub>(WeakClaim(this));
}
} // namespace OHOS::Ace::NG
