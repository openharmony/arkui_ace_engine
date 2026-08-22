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

#include "core/components_ng/dump_utils/dump_util.h"

#include <unordered_set>

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
// Constants matching the keys used by OverlayManager to locate AtomicService
const char ATOMIC_SERVICE_CONTAINER_KEY[] = "AtomicServiceContainerId";
const char ATOMIC_SERVICE_MENUBAR_KEY[] = "AtomicServiceMenubarRowId";

RefPtr<FrameNode> GetContainerModalDumpRootNode(const RefPtr<FrameNode>& containerModalNode)
{
    RefPtr<FrameNode> result;
    CHECK_NULL_RETURN(containerModalNode, result);
    auto containerModalPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    if (containerModalPattern) {
        result = containerModalPattern->GetStackNode();
    }
    return result;
}

RefPtr<FrameNode> GetContainerModalTitleRow(const RefPtr<FrameNode>& containerModalNode)
{
    RefPtr<FrameNode> result;
    CHECK_NULL_RETURN(containerModalNode, result);
    auto containerModalPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    if (containerModalPattern) {
        result = containerModalPattern->GetCustomTitleRow();
    }
    return result;
}

RefPtr<UINode> GetAtomicServiceDumpNode(const RefPtr<FrameNode>& dumpBeginNode)
{
    CHECK_NULL_RETURN(dumpBeginNode, nullptr);
    auto rootChildren = dumpBeginNode->GetChildren();
    for (const auto& rootChild : rootChildren) {
        CHECK_NULL_CONTINUE(rootChild);
        if (rootChild->GetTag() == V2::ATOMIC_SERVICE_ETS_TAG) {
            return rootChild;
        }
    }
    return nullptr;
}

void CollectPageStartNodes(const RefPtr<FrameNode>& lastPageNode, std::vector<RefPtr<FrameNode>>& outNodes)
{
    CHECK_NULL_VOID(lastPageNode);
    std::list<RefPtr<FrameNode>> navNodes;
    lastPageNode->FindTopNavDestination(navNodes);
    if (navNodes.empty()) {
        outNodes.push_back(lastPageNode);
        return;
    }
    for (const auto& nav : navNodes) {
        if (nav) {
            outNodes.push_back(nav);
        }
    }
}

void CollectOverlayNodes(const RefPtr<FrameNode>& rootNode, std::vector<RefPtr<FrameNode>>& outNodes)
{
    CHECK_NULL_VOID(rootNode);
    for (const auto& child : rootNode->GetChildren()) {
        CHECK_NULL_CONTINUE(child);
        if (!DumpUtil::IsTagInOverlay(child->GetTag())) {
            continue;
        }
        auto frameChild = AceType::DynamicCast<FrameNode>(child);
        if (frameChild) {
            outNodes.push_back(frameChild);
        }
    }
}
} // namespace

bool DumpUtil::IsTagInOverlay(const std::string& tag)
{
    static const std::unordered_set<std::string> targetTags = { V2::TOAST_ETS_TAG, V2::POPUP_ETS_TAG,
        V2::DIALOG_ETS_TAG, V2::ACTION_SHEET_DIALOG_ETS_TAG, V2::ALERT_DIALOG_ETS_TAG, V2::MENU_ETS_TAG,
        V2::MENU_WRAPPER_ETS_TAG, V2::SHEET_PAGE_TAG, V2::MODAL_PAGE_TAG, V2::SHEET_WRAPPER_TAG,
        V2::OVERLAY_ETS_TAG, V2::ORDER_OVERLAY_ETS_TAG };
    return targetTags.find(tag) != targetTags.end();
}

DumpStartNodeSet DumpUtil::CollectInspectorStartNodes(const RefPtr<FrameNode>& rootNode,
    const RefPtr<FrameNode>& containerModalNode, const RefPtr<FrameNode>& lastPageNode,
    const RefPtr<OverlayManager>& overlayManager)
{
    DumpStartNodeSet result;
    result.containerModalTitleRow = GetContainerModalTitleRow(containerModalNode);
    auto containerModalDumpNode = GetContainerModalDumpRootNode(containerModalNode);
    result.dumpBeginNode = containerModalDumpNode ? containerModalDumpNode : rootNode;

    // Inspector starts its main component-overlay discovery at dumpBeginNode.
    // ContainerModal may also have overlays attached directly to rootNode, so
    // preserve both disjoint direct-child branches in that case.
    CollectOverlayNodes(result.dumpBeginNode, result.overlayNodes);
    if (result.dumpBeginNode != rootNode) {
        CollectOverlayNodes(rootNode, result.overlayNodes);
    }

    auto atomicServiceDumpNode = GetAtomicServiceDumpNode(result.dumpBeginNode);
    if (atomicServiceDumpNode && overlayManager) {
        result.atomicServiceRoot = AceType::DynamicCast<FrameNode>(
            overlayManager->FindChildNodeByKey(atomicServiceDumpNode, ATOMIC_SERVICE_CONTAINER_KEY));
        if (result.atomicServiceRoot) {
            // Inspector handles AtomicService overlays from this branch root.
            // Add the same direct overlay roots for PageScene without walking
            // the complete AtomicService subtree (which also contains page
            // and menu-bar branches).
            CollectOverlayNodes(result.atomicServiceRoot, result.overlayNodes);
            result.atomicServiceMenuBar = AceType::DynamicCast<FrameNode>(
                overlayManager->FindChildNodeByKey(result.atomicServiceRoot, ATOMIC_SERVICE_MENUBAR_KEY));
        }
    }

    CollectPageStartNodes(lastPageNode, result.pageStartNodes);
    return result;
}
} // namespace OHOS::Ace::NG
