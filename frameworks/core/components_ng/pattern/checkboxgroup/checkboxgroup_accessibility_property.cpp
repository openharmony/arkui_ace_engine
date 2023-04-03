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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"

namespace OHOS::Ace::NG {
bool CheckBoxGroupAccessibilityProperty::IsCheckable() const
{
    return true;
}

bool CheckBoxGroupAccessibilityProperty::IsChecked() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto selectStatus = paintProperty->GetSelectStatus();
    if (selectStatus == CheckBoxGroupPaintProperty::SelectStatus::ALL) {
        return true;
    }
    return false;
}

std::string CheckBoxGroupAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto checkBoxEventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    auto groupName = checkBoxEventHub ? checkBoxEventHub->GetGroupName() : "";
    return groupName;
}

int32_t CheckBoxGroupAccessibilityProperty::GetCollectionItemCounts() const
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, 0);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_RETURN(pageNode, 0);
    auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
    CHECK_NULL_RETURN(pageEventHub, 0);
    auto checkBoxGroupMap = pageEventHub->GetCheckBoxGroupMap();
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_RETURN(checkBoxGroupPattern, 0);
    auto checkBoxGroupEventHub = checkBoxGroupPattern->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_RETURN(checkBoxGroupEventHub, 0);
    auto group = checkBoxGroupEventHub->GetGroupName();
    auto list = checkBoxGroupMap[group];
    return list.size();
}
} // namespace OHOS::Ace::NG