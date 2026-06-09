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

#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.h"

namespace OHOS::Ace::NG {

RefPtr<NGGestureRecognizer> RichEditorGestureEventHub::PackInnerRecognizer(const Offset& offset,
    std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId, int32_t originalId)
{
    auto recognizer =
        GestureEventHub::PackInnerRecognizer(offset, innerRecognizers, touchId, originalId);
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
    return exclusiveRecognizer;
}

void RichEditorGestureEventHub::AddScrollGestureRecognizer(std::list<RefPtr<NGGestureRecognizer>>& innerRecognizersList)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    auto scrollController = richEditorPattern->GetScrollController();
    CHECK_NULL_VOID(scrollController);
    auto recognizer = scrollController->GetScrollGestureRecognizer();
    CHECK_NULL_VOID(recognizer);
    innerRecognizersList.push_back(recognizer);
}
} // namespace OHOS::Ace::NG
