/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/log/log_wrapper.h"
#include "core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
bool GetNodeAccessibilityVisible(const RefPtr<NG::FrameNode>& frameNode, bool isAllAncestorAccessibilityVisible,
                                 bool clipVisible)
{
    if (frameNode->IsFirstVirtualNode()) {
        return frameNode->IsVisible() && isAllAncestorAccessibilityVisible && clipVisible;
    } else {
        return frameNode->IsActive() && frameNode->IsVisible() && isAllAncestorAccessibilityVisible && clipVisible;
    }
}

bool ProcessParentFrameNode(
    const RefPtr<NG::UINode>& parent, std::string& parentPath, bool& isAllAncestorAccessibilityVisible)
{
    CHECK_NULL_RETURN(parent, false);
    auto parentFrameNode = AceType::DynamicCast<NG::FrameNode>(parent);
    CHECK_NULL_RETURN(parentFrameNode, false);
    if (parentFrameNode->CheckAccessibilityLevelNo()) {
        return false;
    }

    parentPath += "Parent ID: " + std::to_string(parent->GetAccessibilityId()) +
                  " IsActive: " + std::to_string(parentFrameNode->IsActive()) +
                  " IsVisible: " + std::to_string(parentFrameNode->IsVisible()) +
                  " AccessibilityVisible: " + std::to_string(parentFrameNode->GetAccessibilityVisible()) +
                  " Parent Tag: " + parent->GetTag() + " | ";

    if (parent->GetTag() == V2::PAGE_ETS_TAG) {
        isAllAncestorAccessibilityVisible = parentFrameNode->GetAccessibilityVisible();
    } else if (parentFrameNode->IsFirstVirtualNode()) {
        isAllAncestorAccessibilityVisible = parentFrameNode->IsVisible();
    } else {
        isAllAncestorAccessibilityVisible = parentFrameNode->IsActive() && parentFrameNode->IsVisible();
    }

    return !isAllAncestorAccessibilityVisible;
}

RefPtr<NG::UINode> GetInitialParent(const RefPtr<NG::UINode>& uiNode)
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
        if (frameNode->IsFirstVirtualNode()) {
            auto weakNode = frameNode->GetVirtualNodeParent();
            return weakNode.Upgrade();
        } else {
            return uiNode->GetParent();
        }
    }
    return nullptr;
}

bool FindFrameNodeByAccessibilityId(int64_t id, const std::list<RefPtr<NG::UINode>>& children,
    std::queue<RefPtr<NG::UINode>>& nodes, RefPtr<NG::FrameNode>& result)
{
    for (const auto& child : children) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(child);
        if (frameNode != nullptr && !frameNode->CheckAccessibilityLevelNo()) {
            if (frameNode->GetAccessibilityId() == id) {
                result = AceType::DynamicCast<NG::FrameNode>(child);
                return true;
            }
        }
        nodes.push(child);
    }
    return false;
}
} // namespace

void AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(const RefPtr<NG::UINode>& uiNode)
{
    RefPtr<NG::UINode> parent = GetInitialParent(uiNode);
    bool isAllAncestorAccessibilityVisible = true;
    bool clipVisible = true;
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::RectF frameRect;
    OHOS::Ace::NG::RectF visibleInnerRect;
    OHOS::Ace::NG::RectF visibleRect;
    frameNode->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect, true);
    bool isClipCheckSkip = NearEqual(visibleRect.Width(), 0.0) && NearEqual(visibleRect.Height(), 0.0) &&
                           NearEqual(visibleInnerRect.Width(), 0.0) && NearEqual(visibleInnerRect.Height(), 0.0);
    clipVisible = (GreatNotEqual(visibleInnerRect.Width(), 0.0) && GreatNotEqual(visibleInnerRect.Height(), 0.0)) ||
                  isClipCheckSkip;
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    if (NearEqual(rect.Width(), 0.0) && NearEqual(rect.Height(), 0.0)) {
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "Component %{public}s is not visible: width and height are both zero.",
                 std::to_string(frameNode->GetAccessibilityId()).c_str());
        clipVisible = false;
    }
    std::string parentPath;
    while (parent) {
        if (AceType::InstanceOf<NG::FrameNode>(parent)) {
            if (ProcessParentFrameNode(parent, parentPath, isAllAncestorAccessibilityVisible)) {
                break;
            }
        }
        parent = parent->GetParent();
    }
    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "Complete parent path:current id %{public}" PRId64 " %{public}s",
        frameNode->GetAccessibilityId(), parentPath.c_str());

    bool nodeAccessibilityVisible =
        GetNodeAccessibilityVisible(frameNode, isAllAncestorAccessibilityVisible, clipVisible);
    if (!nodeAccessibilityVisible) {
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "Element %{public}" PRId64 " is invisible. isActive %{public}d, isVisible %{public}d"
            " isAllAncestorAccessibilityVisible:%{public}d clipVisible:%{public}d",
            frameNode->GetAccessibilityId(), frameNode->IsActive(), frameNode->IsVisible(),
            isAllAncestorAccessibilityVisible, clipVisible);
    }

    if (frameNode->GetTag() != V2::PAGE_ETS_TAG) {
        frameNode->SetAccessibilityVisible(nodeAccessibilityVisible);
    }
}

RefPtr<NG::FrameNode> AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(
    const RefPtr<NG::FrameNode>& root,
    int64_t id)
{
    CHECK_NULL_RETURN(root, nullptr);
    if (root->GetAccessibilityId() == id) {
        return root;
    }
    std::queue<RefPtr<NG::UINode>> nodes;
    nodes.push(root);
    RefPtr<NG::FrameNode> frameNodeResult = nullptr;

    while (!nodes.empty()) {
        auto current = nodes.front();
        nodes.pop();
        if (current->HasVirtualNodeAccessibilityProperty()) {
            auto fnode = AceType::DynamicCast<NG::FrameNode>(current);
            CHECK_NULL_CONTINUE(fnode);
            auto property = fnode->GetAccessibilityProperty<NG::AccessibilityProperty>();
            const auto& children = std::list<RefPtr<NG::UINode>> { property->GetAccessibilityVirtualNode() };
            if (FindFrameNodeByAccessibilityId(id, children, nodes, frameNodeResult)) {
                return frameNodeResult;
            }
        } else {
            const auto& children = current->GetChildren(true);
            if (FindFrameNodeByAccessibilityId(id, children, nodes, frameNodeResult)) {
                return frameNodeResult;
            }
        }
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(current);
        if (!frameNode) {
            continue;
        }
        auto overlayNode = frameNode->GetOverlayNode();
        if (overlayNode) {
            const auto& children = std::list<RefPtr<NG::UINode>> { overlayNode };
            if (FindFrameNodeByAccessibilityId(id, children, nodes, frameNodeResult)) {
                return frameNodeResult;
            }
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
