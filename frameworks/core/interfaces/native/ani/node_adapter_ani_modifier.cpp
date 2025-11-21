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

#include "node_adapter_ani_modifier.h"

#include <array>
#include <memory>

#include "ui/base/utils/utils.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "core/interfaces/native/node/node_adapter_impl.h"

namespace OHOS::Ace::NG {
namespace {
ArkUINodeHandle ConvertToNodeHandle(OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(src));
}
} // namespace

ani_long NodeAdapterConstruct(NodeAdapterInfo&& info)
{
    auto handle = NodeAdapter::GetNodeAdapterAPI()->create();
    if (!handle) {
        return 0;
    }
    auto ref = AceType::MakeRefPtr<UINodeAdapter>(handle);
    ref->IncRefCount();
    auto attachfunc = [func = std::move(info.onAttachToNode)](ArkUINodeHandle node) {
        auto uiNode = reinterpret_cast<UINode*>(node);
        CHECK_NULL_VOID(uiNode && func);
        ani_double nodeId = uiNode->GetId();
        func(nodeId);
    };
    ref->SetOnAttachToNodeFunc(std::move(attachfunc));
    ref->SetOnDetachFromNodeFunc(std::move(info.onDetachFromNode));
    ref->SetOnGetChildIdFunc(std::move(info.onGetId));
    auto onCreateChild = [func = std::move(info.onCreateChild)](uint32_t index) -> ArkUINodeHandle {
        ani_long node = func(index);
        auto frameNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(node));
        return ConvertToNodeHandle(frameNode);
    };
    ref->SetOnCreateNewChild(std::move(onCreateChild));
    auto onDisposeChild = [func = std::move(info.onDisposeChild)](ArkUINodeHandle node, int32_t id) {
        ani_double nodeId = reinterpret_cast<NG::UINode*>(node) ? reinterpret_cast<NG::UINode*>(node)->GetId() : -2;
        ani_double index = id;
        func(nodeId, index);
    };
    ref->SetOnDisposeChild(std::move(onDisposeChild));

    // auto onUpdateChild = [func = std::move(info.onUpdateChild)](ArkUINodeHandle node, int32_t id) {
    //     ani_double nodeId = reinterpret_cast<NG::UINode*>(node) ? reinterpret_cast<NG::UINode*>(node)->GetId() : -2;
    //     ani_double index = id;
    //     func(nodeId, index);
    // };
    // ref->SetOnUpdateChild(std::move(onUpdateChild));
    return reinterpret_cast<ani_long>(AceType::RawPtr(ref));
}

void NodeAdapterDetachNodeAdapter(ani_long ptr)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(ptr));
    CHECK_NULL_VOID(frameNode);
    NodeAdapter::GetNodeAdapterAPI()->detachHostNode(ConvertToNodeHandle(frameNode));
    frameNode->MarkDirtyNode(ArkUIDirtyFlag::ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT);
}

ani_boolean NodeAdapterAttachNodeAdapter(ani_long ptr, ani_long node)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(node));
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    if (!frameNode || !adapter || frameNode->GetFirstChild()) {
        return false;
    }
    return NodeAdapter::GetNodeAdapterAPI()->attachHostNode(adapter->GetHandle(), ConvertToNodeHandle(frameNode));
}

void NodeAdapterDispose(ani_long ptr)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->DecRefCount();
}

void NodeAdapterNotifyItemReloaded(ani_long ptr)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->NotifyItemReloaded();
}

void NodeAdapterSetTotalNodeCount(ani_long ptr, ani_double count)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->SetTotalNodeCount(count);
}

void NodeAdapterNotifyItemChanged(ani_long ptr, ani_double start, ani_double count)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->NotifyItemChanged(start, count);
}

void NodeAdapterNotifyItemRemoved(ani_long ptr, ani_double start, ani_double count)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->NotifyItemRemoved(start, count);
}

void NodeAdapterNotifyItemInserted(ani_long ptr, ani_double start, ani_double count)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->NotifyItemInserted(start, count);
}

void NodeAdapterNotifyItemMoved(ani_long ptr, ani_double start, ani_double count)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_VOID(adapter);
    adapter->NotifyItemMoved(start, count);
}

AniDoubleArray NodeAdapterGetAllItems(ani_long ptr)
{
    auto adapter = reinterpret_cast<UINodeAdapter*>(ptr);
    CHECK_NULL_RETURN(adapter, {});
    auto items = adapter->GetAllItems();
    std::unique_ptr<ani_double[]> result = std::make_unique<ani_double[]>(items.size());
    for (uint32_t i = 0; i < items.size(); i++) {
        auto node = reinterpret_cast<UINode*>(items[i]);
        if (!node) {
            continue;
        }
        ani_double nodeId = reinterpret_cast<UINode*>(items[i])->GetId();
        result[i] = nodeId;
    }
    AniDoubleArray array = { .data = std::move(result), .size = items.size() };
    return array;
}

const ArkUIAniNodeAdapterModifier* GetNodeAdapterAniModifier()
{
    static const ArkUIAniNodeAdapterModifier impl = {
        .nodeAdapterConstruct = OHOS::Ace::NG::NodeAdapterConstruct,
        .nodeAdapterDetachNodeAdapter = OHOS::Ace::NG::NodeAdapterDetachNodeAdapter,
        .nodeAdapterAttachNodeAdapter = OHOS::Ace::NG::NodeAdapterAttachNodeAdapter,
        .nodeAdapterDispose = OHOS::Ace::NG::NodeAdapterDispose,
        .nodeAdapterNotifyItemReloaded = OHOS::Ace::NG::NodeAdapterNotifyItemReloaded,
        .nodeAdapterSetTotalNodeCount = OHOS::Ace::NG::NodeAdapterSetTotalNodeCount,
        .nodeAdapterNotifyItemChanged = OHOS::Ace::NG::NodeAdapterNotifyItemChanged,
        .nodeAdapterNotifyItemRemoved = OHOS::Ace::NG::NodeAdapterNotifyItemRemoved,
        .nodeAdapterNotifyItemInserted = OHOS::Ace::NG::NodeAdapterNotifyItemInserted,
        .nodeAdapterNotifyItemMoved = OHOS::Ace::NG::NodeAdapterNotifyItemMoved,
        .nodeAdapterGetAllItems = OHOS::Ace::NG::NodeAdapterGetAllItems,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
