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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
void RichEditorModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, TextAlign::START);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER_LEFT);
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    richEditorPattern->InitSurfaceChangedCallback();
}

RefPtr<RichEditorControllerBase> RichEditorModelNG::GetRichEditorController()
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, nullptr);
    RefPtr<RichEditorControllerBase> controller = richEditorPattern->GetRichEditorController();
    if (!controller) {
        LOGE("RichEditorModelNG::GetRichEditorController: RichEditorControllerBase is null");
    }
    return controller;
}

void RichEditorModelNG::SetOnReady(std::function<void()>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReady(std::move(func));
}

void RichEditorModelNG::SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(func));
}
} // namespace OHOS::Ace::NG
