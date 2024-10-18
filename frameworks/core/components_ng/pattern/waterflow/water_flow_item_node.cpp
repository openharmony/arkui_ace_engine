/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_item_node.h"

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> WaterFlowItemNode::GetOrCreateFlowItem(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto node = GetFrameNode(tag, nodeId);
    if (node) {
        return node;
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    node = MakeRefPtr<WaterFlowItemNode>(tag, nodeId, pattern);
    node->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RefPtr<FrameNode> WaterFlowItemNode::CreateFlowItem(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    auto frameNode = MakeRefPtr<WaterFlowItemNode>(tag, nodeId, pattern);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

bool WaterFlowItemNode::RequestParentDirty()
{
    auto parent = GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(parent, false);
    parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    auto pattern = parent->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, true);
    // record index of dirty child, but only when using TOP_DOWN layout with sections
    if ((pattern->GetLayoutMode() == WaterFlowLayoutMode::TOP_DOWN && pattern->GetSections()) ||
        SystemProperties::WaterFlowUseSegmentedLayout()) {
        auto idx = parent->GetChildTrueIndex(Claim(this));
        if (idx > -1) {
            parent->ChildrenUpdatedFrom(idx);
        }
    }
    return true;
}
} // namespace OHOS::Ace::NG
