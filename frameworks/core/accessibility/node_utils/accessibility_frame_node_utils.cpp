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
#include "accessibility_frame_node_utils.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/components_ng/property/accessibility_property.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/stage/stage_manager.h"

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

bool FindFrameNodeByAccessibilityId(int64_t id, NG::FrameNode* frameNode)
{
    return frameNode != nullptr &&
        !frameNode->CheckAccessibilityLevelNo() &&
        frameNode->GetAccessibilityId() == id;
}

bool FindFrameNodeByCondition(const std::list<RefPtr<NG::UINode>>& children,
    std::queue<RefPtr<NG::UINode>>& nodes, RefPtr<NG::FrameNode>& result, FindCondition condition)
{
    for (const auto& child : children) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(child);
        if (frameNode != nullptr && !frameNode->CheckAccessibilityLevelNo()) {
            if (condition(frameNode)) {
                result = frameNode;
                return true;
            }
        }
        nodes.push(child);
    }
    return false;
}

bool IsInPageNodes(int32_t pageId, const std::vector<WeakPtr<FrameNode>>& pageNodes)
{
    for (const auto& weak : pageNodes) {
        auto page = weak.Upgrade();
        CHECK_NULL_CONTINUE(page);
        if (pageId == page->GetPageId()) {
            return true;
        }
    }
    return false;
}

void GetFrameNodeChildren(
    const RefPtr<UINode>& uiNode,
    std::vector<RefPtr<FrameNode>>& children,
    const FrameNodeHandleParam& handleParam,
    const RefPtr<AccessibilityManager>& accessibilityManager)
{
    CHECK_NULL_VOID(uiNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (AccessibilityFrameNodeUtils::IsValidEmbedTarget(frameNode, accessibilityManager)) {
        return;
    }

    if (frameNode) {
        if (uiNode->GetTag() == "page") {
            if (!handleParam.pageNodes.empty() && !IsInPageNodes(uiNode->GetPageId(), handleParam.pageNodes)) {
                return;
            }
        } else if (!frameNode->IsInternal() && uiNode->GetTag() != "stage") {
            children.emplace_back(frameNode);
            return;
        }

        auto overlayNode = frameNode->GetOverlayNode();
        if (overlayNode) {
            GetFrameNodeChildren(overlayNode, children, handleParam, accessibilityManager);
        }

        auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
        auto uiVirtualNode = accessibilityProperty->GetAccessibilityVirtualNode();
        if (uiVirtualNode != nullptr) {
            auto virtualNode = AceType::DynamicCast<FrameNode>(uiVirtualNode);
            if (virtualNode != nullptr) {
                GetFrameNodeChildren(virtualNode, children, handleParam, accessibilityManager);
                return;
            }
        }
    }

    for (const auto& frameChild : uiNode->GetChildren(true)) {
        GetFrameNodeChildren(frameChild, children, handleParam, accessibilityManager);
    }
}

RefPtr<NG::FrameNode> GetParentFrameNodeWithVirtualNode(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto parent = node->GetParentFrameNode();
    if (!parent && node->IsAccessibilityVirtualNode()) {
        auto weakNode = AceType::DynamicCast<NG::FrameNode>(node->GetVirtualNodeParent());
        parent = weakNode.Upgrade();
    }
    return parent;
}

NG::RectF ApplyFrameNodeTranformToRect(const NG::RectF& rect, const RefPtr<NG::FrameNode>& parent)
{
    NG::RectF newRect = rect;
    if (!parent) {
        return newRect;
    }

    auto parentRenderContext = parent->GetRenderContext();
    if (!parentRenderContext) {
        return newRect;
    }

    auto parentScale = parentRenderContext->GetTransformScale();
    auto offset = rect.GetOffset();
    if (parentScale) {
        newRect.SetWidth(rect.Width() * parentScale.value().x);
        newRect.SetHeight(rect.Height() * parentScale.value().y);
        offset = NG::OffsetF(offset.GetX() * parentScale.value().x, offset.GetY() * parentScale.value().y);
    }
    offset += parentRenderContext->GetPaintRectWithTransform().GetOffset();
    newRect.SetOffset(offset);
    return newRect;
}

bool GetTransformRectRelativeToParent(
    const RefPtr<NG::FrameNode>& currentNode,
    const RefPtr<NG::FrameNode>& parentNode,
    NG::RectF& rect)
{
    bool find = false;
    CHECK_NULL_RETURN(currentNode, find);
    CHECK_NULL_RETURN(parentNode, find);
    auto context = currentNode->GetRenderContext();
    CHECK_NULL_RETURN(context, find);

    rect = context->GetPaintRectWithTransform();
    auto parent = currentNode->GetAncestorNodeOfFrame(true);
    while (parent) {
        if (parent->IsWindowBoundary()) {
            break;
        }
        if (parent->GetAccessibilityId() == parentNode->GetAccessibilityId()) {
            find = true;
            break;
        }
        rect = ApplyFrameNodeTranformToRect(rect, parent);

        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return find;
}

bool ScrollByOffsetToParent(const RefPtr<NG::FrameNode>& curFrameNode, const RefPtr<NG::FrameNode>& parentFrameNode)
{
    CHECK_NULL_RETURN(curFrameNode, false);
    CHECK_NULL_RETURN(parentFrameNode, false);
    auto parentPattern = parentFrameNode->GetPattern<NG::ScrollablePattern>();
    CHECK_NULL_RETURN(parentPattern, false);

    auto scrollAbility = parentPattern->GetScrollOffsetAbility(true);
    auto scrollFunc = scrollAbility.scrollFunc;
    auto scrollAxis = scrollAbility.axis;
    if (!scrollFunc || scrollAxis == Axis::NONE) {
        return false;
    }

    NG::MoveOffsetParam param {
        .isVertical = scrollAxis == Axis::VERTICAL,
        .contentStartOffset = scrollAbility.contentStartOffset,
        .contentEndOffset = scrollAbility.contentEndOffset,
        .noNeedMargin = true,
        .isFromAccessibility = true
    };
    auto moveOffset = NG::ScrollableUtils::GetMoveOffset(parentFrameNode, curFrameNode, param);
    if (!NearZero(moveOffset)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "Scroll offset: %{public}f on %{public}s/%{public}d, axis: %{public}d",
            moveOffset, parentFrameNode->GetTag().c_str(), parentFrameNode->GetId(), scrollAxis);
        auto ret = scrollFunc(parentPattern->IsReverse() ? -moveOffset : moveOffset);
        auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
        return ret;
    }
    return false;
}

bool ScrollByOffset(const RefPtr<NG::FrameNode>& curFrameNode)
{
    CHECK_NULL_RETURN(curFrameNode, false);
    bool ret = false;
    auto parentFrameNode = curFrameNode->GetParentFrameNode();

    while (parentFrameNode) {
        auto accessibilityProperty = parentFrameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty && !accessibilityProperty->IsUserScrollTriggerable()) {
            return false;
        }
        if (ScrollByOffsetToParent(curFrameNode, parentFrameNode)) {
            ret = true;
        }
        parentFrameNode = parentFrameNode->GetParentFrameNode();
    }
    return ret;
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

    IsCoveredByBrother(frameNode, nodeAccessibilityVisible);
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
    std::vector<RefPtr<NG::UINode>> nodes;
    std::vector<RefPtr<NG::UINode>> nodesNext;
    nodes.emplace_back(root);

    while (!nodes.empty()) {
        nodesNext.reserve(nodes.size() * 2); // double size
        for (auto& current: nodes) {
            CHECK_NULL_CONTINUE(current);

            auto hasVirtualNodeAccessibilityProperty = current->HasVirtualNodeAccessibilityProperty();
            if (!hasVirtualNodeAccessibilityProperty) {
                const auto& children = current->GetChildren(true);
                for (auto& child: children) {
                    auto frameNode = AceType::DynamicCast<NG::FrameNode>(child.GetRawPtr());
                    if (FindFrameNodeByAccessibilityId(id, frameNode)) {
                        return AceType::Claim(frameNode);
                    }
                }
                for (auto& child: children) {
                    nodesNext.emplace_back(child);
                }
            }

            auto fnode = AceType::DynamicCast<NG::FrameNode>(current.GetRawPtr());
            CHECK_NULL_CONTINUE(fnode);

            if (hasVirtualNodeAccessibilityProperty) {
                auto property = fnode->GetAccessibilityProperty<NG::AccessibilityProperty>();
                const auto& child = property->GetAccessibilityVirtualNode();
                auto frameNode = AceType::DynamicCast<NG::FrameNode>(child.GetRawPtr());
                if (FindFrameNodeByAccessibilityId(id, frameNode)) {
                    frameNode->SetAccessibilityNodeVirtual();
                    frameNode->SetAccessibilityVirtualNodeParent(current);
                    return AceType::Claim(frameNode);
                }
                nodesNext.emplace_back(child);
            }

            auto overlayNode = fnode->GetOverlayNode();
            if (overlayNode) {
                if (FindFrameNodeByAccessibilityId(id, overlayNode.GetRawPtr())) {
                    return overlayNode;
                }
                nodesNext.emplace_back(overlayNode);
            }
        }
        nodes.swap(nodesNext);
        nodesNext.clear();
    }
    return nullptr;
}

RefPtr<NG::FrameNode> AccessibilityFrameNodeUtils::GetFramenodeByCondition(
    const RefPtr<NG::FrameNode>& root, FindCondition condition)
{
    CHECK_NULL_RETURN(root, nullptr);

    std::queue<RefPtr<NG::UINode>> nodes;
    nodes.push(root);
    RefPtr<NG::FrameNode> frameNodeResult = nullptr;

    while (!nodes.empty()) {
        auto current = nodes.front();
        nodes.pop();
        CHECK_NULL_RETURN(current, nullptr);
        if (current->HasVirtualNodeAccessibilityProperty()) {
            auto fnode = AceType::DynamicCast<NG::FrameNode>(current);
            CHECK_NULL_CONTINUE(fnode);
            auto property = fnode->GetAccessibilityProperty<NG::AccessibilityProperty>();
            CHECK_NULL_CONTINUE(property);
            const auto& children = std::list<RefPtr<NG::UINode>> { property->GetAccessibilityVirtualNode() };
            if (FindFrameNodeByCondition(children, nodes, frameNodeResult, condition)) {
                return frameNodeResult;
            }
        } else {
            const auto& children = current->GetChildren(true);
            if (FindFrameNodeByCondition(children, nodes, frameNodeResult, condition)) {
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
            if (FindFrameNodeByCondition(children, nodes, frameNodeResult, condition)) {
                return frameNodeResult;
            }
        }
    }
    return nullptr;
}

bool AccessibilityFrameNodeUtils::IsValidEmbedTarget(
    const RefPtr<FrameNode>& node, const RefPtr<AccessibilityManager>& accessibilityManager)
{
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(accessibilityManager, false);
#if !defined(ACE_UNITTEST)
    return accessibilityManager->CheckAndGetEmbedFrameNode(node) != INVALID_ACCESSIBILITY_NODE_ID;
#else
    return false;
#endif
}

void AccessibilityFrameNodeUtils::GetChildrenFromFrameNode(
    const RefPtr<FrameNode>& node,
    std::vector<RefPtr<FrameNode>>& children,
    const FrameNodeHandleParam& handleParam,
    const RefPtr<AccessibilityManager>& accessibilityManager)
{
    CHECK_NULL_VOID(node);
    auto accessibilityProperty = node->GetAccessibilityProperty<AccessibilityProperty>();
    auto uiVirtualNode = accessibilityProperty->GetAccessibilityVirtualNode();
    if (uiVirtualNode != nullptr) {
        auto virtualNode = AceType::DynamicCast<FrameNode>(uiVirtualNode);
        if (virtualNode != nullptr) {
            GetFrameNodeChildren(virtualNode, children, handleParam, accessibilityManager);
        }
    } else {
        for (const auto& item : node->GetChildren(true)) {
            GetFrameNodeChildren(item, children, handleParam, accessibilityManager);
        }

        auto overlayNode = node->GetOverlayNode();
        if (overlayNode != nullptr) {
            GetFrameNodeChildren(overlayNode, children, handleParam, accessibilityManager);
        }
    }
}

void AccessibilityFrameNodeUtils::GetLastestPageNodes(
    const RefPtr<FrameNode>& node,
    std::vector<WeakPtr<FrameNode>>& pageNodes)
{
    CHECK_NULL_VOID(node);
    auto context = node->GetContextRefPtr();
    auto ngPipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(ngPipeline);
    auto stageManager = ngPipeline->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    if (stageManager->IsSplitMode()) {
        for (auto& pageNode : stageManager->GetTopPagesWithTransition()) {
            pageNodes.push_back(pageNode);
        }
        return;
    }
    auto page = stageManager->GetLastPageWithTransition();
    CHECK_NULL_VOID(page);
    pageNodes.push_back(page);
}

void AccessibilityFrameNodeUtils::IsCoveredByBrother(
    const RefPtr<NG::FrameNode>& frameNode, bool& nodeAccessibilityVisible)
{
    CHECK_EQUAL_VOID(AceApplicationInfo::GetInstance().IsAccessibilityScreenReadEnabled(), false);
    CHECK_EQUAL_VOID(nodeAccessibilityVisible, false);
    CHECK_NULL_VOID(frameNode);

    auto frameNodeAccProp = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(frameNodeAccProp);
    CHECK_EQUAL_VOID(frameNodeAccProp->IsHeaderOrFooter(), true);

    auto parentFrameNode = frameNode;
    do {
        parentFrameNode = GetParentFrameNodeWithVirtualNode(parentFrameNode);
        CHECK_NULL_BREAK(parentFrameNode);

        auto accessibilityProperty = parentFrameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_CONTINUE(accessibilityProperty);
        CHECK_EQUAL_VOID(accessibilityProperty->IsHeaderOrFooter(), true);

        NG::RectF parentRect;
        auto find = accessibilityProperty->GetAccessibilityInnerVisibleRect(parentRect);
        if (!find) {
            continue;
        }

        NG::RectF currentRect;
        auto transResult = GetTransformRectRelativeToParent(frameNode, parentFrameNode, currentRect);
        if (!transResult) {
            break;
        }

        if (GreatNotEqual(currentRect.Top(),  parentRect.Bottom()) ||
            LessNotEqual(currentRect.Bottom(),  parentRect.Top()) ||
            NearEqual(parentRect.Top(), parentRect.Bottom())) {
            nodeAccessibilityVisible = false;
            break;
        }
    } while (parentFrameNode);
}

bool AccessibilityFrameNodeUtils::IsNodeEnabled(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    auto enable = node->GetFocusHub() ? node->GetFocusHub()->IsEnabled() : true;
    if (accessibilityProperty->HasUserDisabled()) {
        enable = !accessibilityProperty->IsUserDisabled();
    }
    return enable;
}

void AccessibilityFrameNodeUtils::ProcessFocusScroll(const RefPtr<FrameNode>& curFrameNode,
    RefPtr<PipelineContext>& context)
{
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [node = AceType::WeakClaim(AceType::RawPtr(curFrameNode))] {
            auto focusNode = node.Upgrade();
            CHECK_NULL_VOID(focusNode);
            auto accessibilityProperty = focusNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
            CHECK_NULL_VOID(accessibilityProperty);
            if (accessibilityProperty->GetAccessibilityFocusState()) {
                ScrollByOffset(focusNode);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIAccessibilityProcessFocusScroll");
}
} // namespace OHOS::Ace::NG
