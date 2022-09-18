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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/test/unittest/image/image_test_utils.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void CheckBoxGroupPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);

    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxGroupPattern::OnDetachFromFrameNode(FrameNode* frameNode)
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

    auto checkBoxGroupEventHub = host->GetEventHub<NG::CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    pageEventHub->RemoveCheckBoxFromGroup(checkBoxGroupEventHub->GetGroupName(), host);
}

void CheckBoxGroupPattern::OnModifyDone()
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
        auto checkboxPattern = weak.Upgrade();
        CHECK_NULL_VOID(checkboxPattern);
        checkboxPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void CheckBoxGroupPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxGroupSelect()) {
        isSelected = paintProperty->GetCheckBoxGroupSelectValue();
    }

    auto status = paintProperty->GetSelectStatus();
    if (status == CheckBoxGroupPaintProperty::SelectStatus::ALL) {
        isSelected = false;
    } else {
        isSelected = true;
    }
    paintProperty->UpdateCheckBoxGroupSelect(isSelected);
    UpdateState();
}

void CheckBoxGroupPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroupName();

    if (!preGroup.has_value()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto stageManager = pipelineContext->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_VOID(pageEventHub);

        pageEventHub->AddCheckBoxGroupToGroup(group, host);
        if (pattern->GetIsAddToMap()) {
            auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();
            UpdateCheckBoxGroupStatusByOtherCheckBox(host, checkBoxGroupMap);
        } else {
        }
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

            pageEventHub->RemoveCheckBoxFromGroup(preGroup.value(), host);
            pageEventHub->AddCheckBoxGroupToGroup(group, host);
        } else {
            auto paintProperty = host->GetPaintProperty<CheckBoxGroupPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            bool isSelected = paintProperty->GetCheckBoxGroupSelectValue();

            if (pattern->GetIsAddToMap()) {
                UpdateGroupCheckStatus(host, isSelected);
            } else {
                UpdateRepeatedGroupStatus(host, isSelected);
            }
        }
    }
    pattern->SetPreGroup(group);
}

void CheckBoxGroupPattern::UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool select)
{
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (select) {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    } else {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto checkBoxGroupEventHub = GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);

    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();

    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    UpdateCheckBoxStatus(frameNode, checkBoxGroupMap, select);
}

void CheckBoxGroupPattern::UpdateRepeatedGroupStatus(const RefPtr<FrameNode>& frameNode, bool select)
{
    std::vector<std::string> vec;
    auto status =
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE;

    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (select) {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    } else {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto checkBoxGroupEventHub = GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);

    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    eventHub->UpdateChangeEvent(groupResult);
}

void CheckBoxGroupPattern::UpdateCheckBoxStatus(const RefPtr<FrameNode>& checkBoxGroupFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap, bool select)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto checkBoxGroupEventHub = checkBoxGroupFrameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    auto group = checkBoxGroupEventHub->GetGroupName();

    std::vector<std::string> vec;
    auto status =
        select ? CheckBoxGroupPaintProperty::SelectStatus::ALL : CheckBoxGroupPaintProperty::SelectStatus::NONE;

    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == checkBoxGroupFrameNode) {
            continue;
        }
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            continue;
        } else {
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);
            if (select) {
                vec.push_back(eventHub->GetName());
            }
        }
    }
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = checkBoxGroupFrameNode->GetEventHub<CheckBoxGroupEventHub>();
    eventHub->UpdateChangeEvent(groupResult);

    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == checkBoxGroupFrameNode) {
            continue;
        }
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            continue;
        } else {
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);

            if (!paintProperty->HasCheckBoxSelect()) {
                if (select) {
                    paintProperty->UpdateCheckBoxSelect(select);
                    node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                    eventHub->UpdateChangeEvent(select);
                }
            }

            if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue() != select) {
                paintProperty->UpdateCheckBoxSelect(select);
                node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                eventHub->UpdateChangeEvent(select);
            }
        }
    }
}

void CheckBoxGroupPattern::UpdateCheckBoxGroupStatusByOtherCheckBox(const RefPtr<FrameNode>& checkBoxGroupFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap)
{
    auto checkBoxGroupEventHub = checkBoxGroupFrameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(checkBoxGroupEventHub);
    auto group = checkBoxGroupEventHub->GetGroupName();

    bool allTrue = true;
    bool hasTrue = false;
    const auto& list = checkBoxGroupMap[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == checkBoxGroupFrameNode) {
            continue;
        }
        if (!node) {
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        bool select = paintProperty->GetCheckBoxSelectValue();
        allTrue &= select;
        if (select) {
            hasTrue = true;
        }
    }

    auto paintProperty = checkBoxGroupFrameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (allTrue) {
        paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    } else {
        if (hasTrue) {
            paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
        } else {
            paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
        }
    }
}

} // namespace OHOS::Ace::NG
