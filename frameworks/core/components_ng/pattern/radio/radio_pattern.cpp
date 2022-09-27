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

#include "core/components_ng/pattern/radio/radio_pattern.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_layout_algorithm.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void RadioPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void RadioPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto host = Claim(frameNode);
    CHECK_NULL_VOID(host);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto radioEventHub = host->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    pageEventHub->RemoveRadioFromGroup(radioEventHub->GetGroup(), host);
}

void RadioPattern::OnModifyDone()
{
    UpdateState();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (clickListener_) {
        return;
    }
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto radioPattern = weak.Upgrade();
        CHECK_NULL_VOID(radioPattern);
        radioPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void RadioPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    bool check = paintProperty->GetRadioCheckValue();

    if (!preCheck_ && !check) {
        paintProperty->UpdateRadioCheck(true);
        UpdateState();
    }
}

void RadioPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroup();
    if (!preGroup.has_value()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto stageManager = pipelineContext->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_VOID(pageEventHub);
        pageEventHub->AddRadioToGroup(group, host);
    } else {
        if (preGroup.value() != group) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto stageManager = pipelineContext->GetStageManager();
            CHECK_NULL_VOID(stageManager);
            auto pageNode = stageManager->GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
            CHECK_NULL_VOID(pageEventHub);

            pageEventHub->RemoveRadioFromGroup(preGroup.value(), host);
            pageEventHub->AddRadioToGroup(group, host);
        }
    }
    pattern->SetPreGroup(group);

    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool check = paintProperty->GetRadioCheckValue();

    if (preCheck_ != check) {
        UpdateGroupCheckStatus(host, check);
    }
    preCheck_ = check;
}

void RadioPattern::UpdateUncheckStatus(const RefPtr<FrameNode>& frameNode)
{
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    radioPaintProperty->UpdateRadioCheck(false);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    if (preCheck_) {
        auto radioEventHub = GetEventHub<RadioEventHub>();
        CHECK_NULL_VOID(radioEventHub);
        radioEventHub->UpdateChangeEvent(false);
    }
    preCheck_ = false;
}

void RadioPattern::UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool check)
{
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto radioEventHub = GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    radioEventHub->UpdateChangeEvent(check);
    if (check) {
        pageEventHub->UpdateRadioGroupValue(radioEventHub->GetGroup(), frameNode);
    }
}

} // namespace OHOS::Ace::NG
