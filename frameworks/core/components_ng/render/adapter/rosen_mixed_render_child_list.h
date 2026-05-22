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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MIXED_RENDER_CHILD_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MIXED_RENDER_CHILD_LIST_H

#include <cstdint>
#include <list>
#include <memory>
#include <optional>
#include <vector>

#include "base/memory/referenced.h"

namespace OHOS::Rosen {
class RSNode;
} // namespace OHOS::Rosen

namespace OHOS::Ace::NG {
class FrameNode;
class UINode;

enum class MixedRenderChildSource {
    FRAME_NODE_CHILD, // logical child node mounted to the MIX frameNode.
    PURE_RENDER_NODE, // rsNode is created by CAPI interface or got from adopted frameNode.
};

struct MixedRenderChild {
    std::weak_ptr<Rosen::RSNode> rsNode;
    WeakPtr<UINode> uiNode;
    std::optional<uint64_t> rsNodeId;
    MixedRenderChildSource source = MixedRenderChildSource::PURE_RENDER_NODE;
};

class RosenMixedRenderChildList final {
public:
    bool IsFrameRenderChild(const std::shared_ptr<Rosen::RSNode>& rsNode);
    bool RemovePureRenderChild(const std::shared_ptr<Rosen::RSNode>& childRSNode);
    bool CanSwitchToSingleIfRenderNode();
    void Reset(const RefPtr<FrameNode>& host);
    bool ClearPureRenderChildren();
    int32_t GetChildCount();
    int32_t GetChildIndexByRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode);
    std::shared_ptr<Rosen::RSNode> GetChildAt(int32_t index);
    std::shared_ptr<Rosen::RSNode> GetSibling(const std::shared_ptr<Rosen::RSNode>& rsNode, int32_t offset);
    bool GetInsertIndexAfterRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode, int32_t& mixedIndex);
    bool InsertPureRenderChildAt(
        const RefPtr<FrameNode>& host, const std::shared_ptr<Rosen::RSNode>& childRSNode, int32_t index);
    bool InsertFrameChildBefore(
        const RefPtr<FrameNode>& host, const RefPtr<UINode>& child, const RefPtr<UINode>& nextSibling);
    bool RemoveFrameChild(const RefPtr<UINode>& child);
    bool SyncFrameChildren(const RefPtr<FrameNode>& host, const std::list<RefPtr<UINode>>& children);
    std::vector<std::shared_ptr<Rosen::RSNode>> BuildTargetRSNodes(const RefPtr<FrameNode>& host);

private:
    using MixedRenderChildIterator = std::list<MixedRenderChild>::iterator;

    std::shared_ptr<Rosen::RSNode> GetChildRSNode(const MixedRenderChild& child) const;
    std::shared_ptr<Rosen::RSNode> GetRSNodeFromFrameNode(const RefPtr<FrameNode>& frameNode) const;
    std::shared_ptr<Rosen::RSNode> ResolveFrameChildRSNode(const RefPtr<UINode>& uiNode) const;
    void RegisterChild(const RefPtr<FrameNode>& host, const std::shared_ptr<Rosen::RSNode>& childRSNode) const;
    void UnregisterChild(const std::optional<uint64_t>& childRSNodeId) const;
    void RemoveExpiredChild(MixedRenderChildIterator& iter);

    std::list<MixedRenderChild> mixedRenderChildren_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MIXED_RENDER_CHILD_LIST_H
