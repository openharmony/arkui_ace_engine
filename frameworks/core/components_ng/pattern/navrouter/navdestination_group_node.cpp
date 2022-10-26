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

#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"

namespace OHOS::Ace::NG {

RefPtr<NavDestinationGroupNode> NavDestinationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(tag, nodeId, pattern);
    navDestinationNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navDestinationNode);
    return navDestinationNode;
}

void NavDestinationGroupNode::AddChildToGroup(const RefPtr<UINode>& child)
{
    auto pattern = AceType::DynamicCast<Pattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto contentNode = GetContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG,
            nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        SetContentNode(contentNode);
        auto layoutProperty = GetLayoutProperty<NavDestinationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        AddChild(contentNode);
    }
    contentNode->AddChild(child);
}

} // namespace OHOS::Ace::NG