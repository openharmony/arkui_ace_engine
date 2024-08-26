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

#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
bool WaterFlowAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsScrollable();
}

int32_t WaterFlowAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetBeginIndex();
}

int32_t WaterFlowAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetEndIndex();
}

int32_t WaterFlowAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetChildrenCount();
}

AceCollectionInfo WaterFlowAccessibilityProperty::GetCollectionInfo() const
{
    AceCollectionInfo aceCollectionInfo;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, aceCollectionInfo);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, aceCollectionInfo);
    aceCollectionInfo.rows = pattern->GetRows();
    aceCollectionInfo.columns = pattern->GetColumns();
    return aceCollectionInfo;
}

void WaterFlowAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsScrollable()) {
        if (!(pattern->IsAtTop())) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
        if (!(pattern->IsAtBottom())) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
