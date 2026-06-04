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

#include "core/components_ng/render/adapter/rosen_mixed_render_child_list.h"

#include <cinttypes>
#include <unordered_map>
#include <utility>

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/mixed_mount_registry.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace::NG {
bool RosenMixedRenderChildList::IsFrameRenderChild(const std::shared_ptr<Rosen::RSNode>& rsNode)
{
    CHECK_NULL_RETURN(rsNode, false);
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        auto childRSNode = GetChildRSNode(*iter);
        if (!childRSNode) {
            RemoveExpiredChild(iter);
            continue;
        }
        if (iter->source == MixedRenderChildSource::FRAME_NODE_CHILD && childRSNode == rsNode) {
            return true;
        }
        ++iter;
    }
    return false;
}

std::shared_ptr<Rosen::RSNode> RosenMixedRenderChildList::GetRSNodeFromFrameNode(
    const RefPtr<FrameNode>& frameNode) const
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_RETURN(rosenRenderContext, nullptr);
    return rosenRenderContext->GetRSNode();
}

std::shared_ptr<Rosen::RSNode> RosenMixedRenderChildList::ResolveFrameChildRSNode(
    const RefPtr<UINode>& uiNode) const
{
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        return GetRSNodeFromFrameNode(frameNode);
    }
    std::list<RefPtr<FrameNode>> frameNodes;
    uiNode->GenerateSelfVisibleFrameWithTransition(frameNodes);
    if (frameNodes.empty()) {
        return nullptr;
    }
    return GetRSNodeFromFrameNode(frameNodes.front());
}

std::shared_ptr<Rosen::RSNode> RosenMixedRenderChildList::GetChildRSNode(const MixedRenderChild& child) const
{
    return child.rsNode.lock();
}

void RosenMixedRenderChildList::RegisterChild(
    const RefPtr<FrameNode>& host, const std::shared_ptr<Rosen::RSNode>& childRSNode) const
{
    CHECK_NULL_VOID(host && childRSNode);
    MixedMountRegistry::RegisterChild(static_cast<uint64_t>(childRSNode->GetId()), WeakPtr<FrameNode>(host));
}

void RosenMixedRenderChildList::UnregisterChild(const std::optional<uint64_t>& childRSNodeId) const
{
    if (!childRSNodeId.has_value()) {
        return;
    }
    MixedMountRegistry::UnregisterChild(childRSNodeId.value());
}

void RosenMixedRenderChildList::RemoveExpiredChild(MixedRenderChildIterator& iter)
{
    TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN,
        "Mixed render child rsNode expired, source:%{public}d, rsNodeId:%{public}" PRIu64,
        static_cast<int32_t>(iter->source), iter->rsNodeId.value_or(static_cast<uint64_t>(0)));
    UnregisterChild(iter->rsNodeId);
    iter = mixedRenderChildren_.erase(iter);
}

int32_t RosenMixedRenderChildList::GetChildCount()
{
    int32_t count = 0;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (!GetChildRSNode(*iter)) {
            RemoveExpiredChild(iter);
            continue;
        }
        ++count;
        ++iter;
    }
    return count;
}

std::shared_ptr<Rosen::RSNode> RosenMixedRenderChildList::GetChildAt(int32_t index)
{
    if (index < 0) {
        return nullptr;
    }
    int32_t currentIndex = 0;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        auto childRSNode = GetChildRSNode(*iter);
        if (!childRSNode) {
            RemoveExpiredChild(iter);
            continue;
        }
        if (currentIndex == index) {
            return childRSNode;
        }
        ++currentIndex;
        ++iter;
    }
    return nullptr;
}

int32_t RosenMixedRenderChildList::GetChildIndexByRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode)
{
    CHECK_NULL_RETURN(rsNode, -1);
    int32_t currentIndex = 0;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        auto childRSNode = GetChildRSNode(*iter);
        if (!childRSNode) {
            RemoveExpiredChild(iter);
            continue;
        }
        if (childRSNode == rsNode) {
            return currentIndex;
        }
        ++currentIndex;
        ++iter;
    }
    return -1;
}

std::shared_ptr<Rosen::RSNode> RosenMixedRenderChildList::GetSibling(
    const std::shared_ptr<Rosen::RSNode>& rsNode, int32_t offset)
{
    auto index = GetChildIndexByRSNode(rsNode);
    auto siblingIndex = index + offset;
    if (index < 0 || siblingIndex < 0) {
        return nullptr;
    }
    return GetChildAt(siblingIndex);
}

bool RosenMixedRenderChildList::GetInsertIndexAfterRSNode(
    const std::shared_ptr<Rosen::RSNode>& rsNode, int32_t& mixedIndex)
{
    CHECK_NULL_RETURN(rsNode, false);
    auto index = GetChildIndexByRSNode(rsNode);
    if (index < 0) {
        return false;
    }
    mixedIndex = index + 1;
    return true;
}

bool RosenMixedRenderChildList::InsertPureRenderChildAt(
    const RefPtr<FrameNode>& host, const std::shared_ptr<Rosen::RSNode>& childRSNode, int32_t index)
{
    CHECK_NULL_RETURN(childRSNode, false);
    MixedRenderChild mixedChild = {
        .rsNode = childRSNode,
        .rsNodeId = static_cast<uint64_t>(childRSNode->GetId()),
        .source = MixedRenderChildSource::PURE_RENDER_NODE,
    };
    if (index < 0) {
        mixedRenderChildren_.emplace_back(std::move(mixedChild));
        RegisterChild(host, childRSNode);
        return true;
    }
    int32_t currentIndex = 0;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (!GetChildRSNode(*iter)) {
            RemoveExpiredChild(iter);
            continue;
        }
        if (currentIndex == index) {
            mixedRenderChildren_.insert(iter, std::move(mixedChild));
            RegisterChild(host, childRSNode);
            return true;
        }
        ++currentIndex;
        ++iter;
    }
    mixedRenderChildren_.emplace_back(std::move(mixedChild));
    RegisterChild(host, childRSNode);
    return true;
}

bool RosenMixedRenderChildList::InsertFrameChildBefore(
    const RefPtr<FrameNode>& host, const RefPtr<UINode>& child, const RefPtr<UINode>& nextSibling)
{
    CHECK_NULL_RETURN(child, false);
    RemoveFrameChild(child);
    auto childRSNode = ResolveFrameChildRSNode(child);
    MixedRenderChild mixedChild = {
        .rsNode = childRSNode,
        .uiNode = WeakPtr<UINode>(child),
        .rsNodeId = childRSNode ? std::optional<uint64_t>(static_cast<uint64_t>(childRSNode->GetId())) : std::nullopt,
        .source = MixedRenderChildSource::FRAME_NODE_CHILD,
    };
    if (!nextSibling) {
        mixedRenderChildren_.emplace_back(std::move(mixedChild));
        RegisterChild(host, childRSNode);
        return true;
    }
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end(); ++iter) {
        if (iter->source != MixedRenderChildSource::FRAME_NODE_CHILD) {
            continue;
        }
        if (iter->uiNode.Upgrade() == nextSibling) {
            mixedRenderChildren_.insert(iter, std::move(mixedChild));
            RegisterChild(host, childRSNode);
            return true;
        }
    }
    mixedRenderChildren_.emplace_back(std::move(mixedChild));
    RegisterChild(host, childRSNode);
    return true;
}

bool RosenMixedRenderChildList::RemovePureRenderChild(const std::shared_ptr<Rosen::RSNode>& childRSNode)
{
    bool changed = false;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (iter->source != MixedRenderChildSource::PURE_RENDER_NODE) {
            ++iter;
            continue;
        }
        auto mixedRSNode = iter->rsNode.lock();
        if (!mixedRSNode) {
            RemoveExpiredChild(iter);
            changed = true;
            continue;
        }
        if (mixedRSNode == childRSNode) {
            UnregisterChild(iter->rsNodeId);
            iter = mixedRenderChildren_.erase(iter);
            changed = true;
            continue;
        }
        ++iter;
    }
    return changed;
}

bool RosenMixedRenderChildList::RemoveFrameChild(const RefPtr<UINode>& child)
{
    CHECK_NULL_RETURN(child, false);
    bool changed = false;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (iter->source != MixedRenderChildSource::FRAME_NODE_CHILD) {
            ++iter;
            continue;
        }
        auto uiNode = iter->uiNode.Upgrade();
        if (!uiNode || uiNode == child) {
            UnregisterChild(iter->rsNodeId);
            iter = mixedRenderChildren_.erase(iter);
            changed = true;
            continue;
        }
        ++iter;
    }
    return changed;
}

bool RosenMixedRenderChildList::CanSwitchToSingleIfRenderNode()
{
    int32_t frameRenderNodeCount = 0;
    int32_t pureRenderNodeCount = 0;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (!GetChildRSNode(*iter)) {
            RemoveExpiredChild(iter);
            continue;
        }
        if (iter->source == MixedRenderChildSource::FRAME_NODE_CHILD) {
            ++frameRenderNodeCount;
        } else {
            ++pureRenderNodeCount;
        }
        ++iter;
    }
    if (frameRenderNodeCount > 0) {
        return pureRenderNodeCount == 0;
    }
    constexpr int32_t maxPureRenderNodeCount = 1;
    return pureRenderNodeCount <= maxPureRenderNodeCount;
}

void RosenMixedRenderChildList::Reset(const RefPtr<FrameNode>& host)
{
    MixedMountRegistry::ClearByHost(host);
    mixedRenderChildren_.clear();
}

bool RosenMixedRenderChildList::ClearPureRenderChildren()
{
    bool changed = false;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        if (iter->source == MixedRenderChildSource::PURE_RENDER_NODE) {
            UnregisterChild(iter->rsNodeId);
            iter = mixedRenderChildren_.erase(iter);
            changed = true;
            continue;
        }
        ++iter;
    }
    return changed;
}

bool RosenMixedRenderChildList::SyncFrameChildren(
    const RefPtr<FrameNode>& host, const std::list<RefPtr<UINode>>& children)
{
    bool changed = false;
    RefPtr<UINode> nextSibling;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        changed |= InsertFrameChildBefore(host, *iter, nextSibling);
        nextSibling = *iter;
    }
    return changed;
}

std::vector<std::shared_ptr<Rosen::RSNode>> RosenMixedRenderChildList::BuildTargetRSNodes(
    const RefPtr<FrameNode>& host)
{
    auto addRSNodeIfAbsent = [](std::vector<std::shared_ptr<Rosen::RSNode>>& targetRSNodes,
                                 std::unordered_map<Rosen::RSNode::SharedPtr, bool>& targetNodeMap,
                                 const std::shared_ptr<Rosen::RSNode>& rsNode) {
        if (!rsNode) {
            return;
        }
        auto result = targetNodeMap.try_emplace(rsNode, false);
        if (result.second) {
            targetRSNodes.emplace_back(rsNode);
        }
    };

    std::unordered_map<Rosen::RSNode::SharedPtr, bool> targetNodeMap;
    std::vector<std::shared_ptr<Rosen::RSNode>> targetRSNodes;
    for (auto iter = mixedRenderChildren_.begin(); iter != mixedRenderChildren_.end();) {
        auto childRSNode = GetChildRSNode(*iter);
        if (!childRSNode) {
            RemoveExpiredChild(iter);
            continue;
        }
        RegisterChild(host, childRSNode);
        addRSNodeIfAbsent(targetRSNodes, targetNodeMap, childRSNode);
        ++iter;
    }
    return targetRSNodes;
}
} // namespace OHOS::Ace::NG
