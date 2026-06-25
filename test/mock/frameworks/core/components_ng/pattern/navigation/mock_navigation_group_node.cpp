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

#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
NavigationGroupNode::~NavigationGroupNode() = default;

void NavigationGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    AddChild(child, slot);
}

void NavigationGroupNode::OnInspectorIdUpdate(const std::string& id)
{
    (void)id;
}

void NavigationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    (void)json;
    (void)filter;
}

void NavigationGroupNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    (void)recursive;
    (void)context;
}

void NavigationGroupNode::OnAttachToMainTree(bool recursive)
{
    (void)recursive;
}

void NavigationGroupNode::CreateAnimationWithPop(const TransitionUnitInfo& preInfo, const TransitionUnitInfo& curInfo,
    const AnimationFinishCallback finishCallback, bool isNavBarOrHomeDestination)
{
    (void)preInfo;
    (void)curInfo;
    (void)isNavBarOrHomeDestination;
    if (finishCallback) {
        finishCallback();
    }
}

void NavigationGroupNode::CreateAnimationWithPush(const TransitionUnitInfo& preInfo, const TransitionUnitInfo& curInfo,
    const AnimationFinishCallback finishCallback, bool isNavBarOrHomeDestination)
{
    (void)preInfo;
    (void)curInfo;
    (void)isNavBarOrHomeDestination;
    if (finishCallback) {
        finishCallback();
    }
}

void NavigationGroupNode::ResetSystemAnimationProperties(const RefPtr<FrameNode>& navDestinationNode)
{
    (void)navDestinationNode;
}

RefPtr<NavigationGroupNode> NavigationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto node = ElementRegister::GetInstance()->GetUINodeById(nodeId);
    if (node) {
        auto navGroup = AceType::DynamicCast<NavigationGroupNode>(node);
        if (navGroup) {
            return navGroup;
        }
    }

    RefPtr<Pattern> pattern;
    if (patternCreator) {
        pattern = patternCreator();
    } else {
        pattern = AceType::MakeRefPtr<NavigationPattern>();
    }
    auto navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(tag, nodeId, pattern);
    navigationGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navigationGroupNode);
    return navigationGroupNode;
}

RefPtr<FrameNode> NavigationGroupNode::GetTopDestination()
{
    return nullptr;
}

bool NavigationGroupNode::CheckCanHandleBack(bool& isEntry)
{
    (void)isEntry;
    return false;
}

const RefPtr<UINode>& NavigationGroupNode::GetNavBarOrHomeDestinationNode() const
{
    static RefPtr<UINode> node = nullptr;
    return node;
}

RefPtr<UINode> NavigationGroupNode::GetNavDestinationNode(RefPtr<UINode> uiNode)
{
    if (!uiNode) {
        return nullptr;
    }
    while (uiNode) {
        if (uiNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            return uiNode;
        }
        if (AceType::DynamicCast<UINode>(uiNode)) {
            auto children = uiNode->GetChildren();
            if (children.empty()) {
                break;
            }
            uiNode = children.front();
            continue;
        }
        break;
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
