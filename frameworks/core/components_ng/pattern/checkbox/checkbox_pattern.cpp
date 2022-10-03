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

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/test/unittest/image/image_test_utils.h"
#include "core/components_ng/pattern/checkbox/checkbox_layout_algorithm.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void CheckBoxPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);

    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void CheckBoxPattern::OnModifyDone()
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

void CheckBoxPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    paintProperty->UpdateCheckBoxSelect(!isSelected);
    UpdateState();

    auto checkboxEventHub = GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkboxEventHub);
    checkboxEventHub->UpdateChangeEvent(!isSelected);
}

void CheckBoxPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto checkBoxEventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    pageEventHub->RemoveCheckBoxFromGroup(checkBoxEventHub->GetGroupName(), frameNode->GetId());
}

void CheckBoxPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = host->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto paintProperty = host->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();

    auto preGroup = pattern->GetPreGroup();
    auto group = eventHub->GetGroupName();
    if (!preGroup.has_value()) {
        pageEventHub->AddCheckBoxToGroup(group, host->GetId());
        auto callback = [weak = WeakClaim(this)]() {
            auto checkbox = weak.Upgrade();
            if (checkbox) {
                checkbox->CheckBoxGroupIsTrue();
            }
        };
        PipelineContext::GetCurrentContext()->AddBuildFinishCallBack(callback);
        pattern->SetPreGroup(group);
        return;
    }
    if (preGroup.value() != group) {
        pageEventHub->RemoveCheckBoxFromGroup(preGroup.value(), host->GetId());
        pageEventHub->AddCheckBoxToGroup(group, host->GetId());
    }

    pattern->SetPreGroup(group);

    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
    }

    UpdateCheckBoxGroupStatus(host, checkBoxGroupMap, isSelected);
}

void CheckBoxPattern::UpdateCheckBoxGroupStatus(const RefPtr<FrameNode>& checkBoxFrameNode,
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap, bool select)
{
    checkBoxFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    auto checkBoxEventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    auto group = checkBoxEventHub->GetGroupName();

    std::vector<std::string> vec;

    RefPtr<FrameNode> checkBoxGroupNode;
    bool isSameAsSelf = true;
    const auto& list = checkBoxGroupMap[group];

    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node == checkBoxFrameNode) {
            if (select) {
                auto eventHub = node->GetEventHub<CheckBoxEventHub>();
                CHECK_NULL_VOID(eventHub);
                vec.push_back(eventHub->GetName());
            }
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            checkBoxGroupNode = node;
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);

        if (!paintProperty->HasCheckBoxSelect()) {
            if (select) {
                isSameAsSelf = false;
            }
        }

        if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue() != select) {
            isSameAsSelf = false;
        }

        if (paintProperty->HasCheckBoxSelect() && paintProperty->GetCheckBoxSelectValue()) {
            auto eventHub = node->GetEventHub<CheckBoxEventHub>();
            CHECK_NULL_VOID(eventHub);
            vec.push_back(eventHub->GetName());
        }
    }

    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_VOID(groupPaintProperty);
    if (isSameAsSelf) {
        if (select) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
        } else {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
        }
        checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else {
        auto checkBoxGroupStatus = groupPaintProperty->GetSelectStatus();
        if (checkBoxGroupStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL ||
            checkBoxGroupStatus == CheckBoxGroupPaintProperty::SelectStatus::NONE) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
            checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }

    auto status = groupPaintProperty->GetSelectStatus();
    CheckboxGroupResult groupResult(vec, int(status));
    auto eventHub = checkBoxGroupNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(groupResult);
}

void CheckBoxPattern::CheckBoxGroupIsTrue()
{
    auto checkBoxFrameNode = GetHost();
    CHECK_NULL_VOID(checkBoxFrameNode);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_VOID(pageEventHub);

    auto paintProperty = checkBoxFrameNode->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();

    auto checkBoxEventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(checkBoxEventHub);
    auto group = checkBoxEventHub->GetGroupName();

    std::vector<std::string> vec;

    RefPtr<FrameNode> checkBoxGroupNode;
    bool allSelectIsNull = true;
    const auto& list = checkBoxGroupMap[group];

    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            checkBoxGroupNode = node;
            continue;
        }
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);

        if (paintProperty->HasCheckBoxSelect()) {
            allSelectIsNull = false;
        } else {
            paintProperty->UpdateCheckBoxSelect(false);
        }
    }

    CHECK_NULL_VOID(checkBoxGroupNode);
    auto groupPaintProperty = checkBoxGroupNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    if (groupPaintProperty->GetIsCheckBoxCallbackDealed()) {
        return;
    }
    if (allSelectIsNull) {
        if (groupPaintProperty->GetCheckBoxGroupSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
            groupPaintProperty->UpdateCheckBoxGroupSelect(true);
            checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            for (auto&& item : list) {
                auto node = item.Upgrade();
                if (!node) {
                    continue;
                }
                if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
                    continue;
                }
                auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
                CHECK_NULL_VOID(paintProperty);
                paintProperty->UpdateCheckBoxSelect(true);
                node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            }
        }
    }
    if (!allSelectIsNull) {
        bool allIsSame = true;
        bool selfSelect = paintProperty->GetCheckBoxSelectValue();
        for (auto&& item : list) {
            auto node = item.Upgrade();
            if (node == checkBoxFrameNode) {
                continue;
            }
            if (!node) {
                continue;
            }
            if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
                continue;
            }
            auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            if (selfSelect != paintProperty->GetCheckBoxSelectValue()) {
                allIsSame = false;
            }
            node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        if (allIsSame && paintProperty->GetCheckBoxSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
        } else if (allIsSame && !paintProperty->GetCheckBoxSelectValue()) {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
        } else {
            groupPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
        }
        checkBoxGroupNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    groupPaintProperty->SetIsCheckBoxCallbackDealed(true);
}

} // namespace OHOS::Ace::NG
