/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_model_static.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/list_item_swipe_action_manager_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace {
constexpr int32_t ERROR_CODE_PARAM_ERROR = 100023;
constexpr int32_t ERROR_CODE_PARAM_INVALID = 401;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE = 106203;
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemSwipeActionManagerAccessor {
void DestroyPeerImpl(Ark_ListItemSwipeActionManager peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ListItemSwipeActionManager ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<ListItemSwipeActionManagerPeer>();
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 ExpandImpl(Ark_FrameNode node,
                     Ark_ListItemSwipeActionDirection direction)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    if (frameNode->GetTag() != V2::LIST_ITEM_ETS_TAG) {
        return ERROR_CODE_PARAM_ERROR;
    }
    ListItemSwipeActionDirection convValue =
        Converter::OptConvert<ListItemSwipeActionDirection>(direction).value_or(ListItemSwipeActionDirection::START);
    if (static_cast<int32_t>(ListItemSwipeActionDirection::START) > static_cast<int32_t>(convValue) ||
        static_cast<int32_t>(ListItemSwipeActionDirection::END) < static_cast<int32_t>(convValue)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!frameNode->IsOnMainTree()) {
        return ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE;
    }
    ListItemModelStatic::ExpandSwipeAction(frameNode.GetRawPtr(), convValue);
    return ERROR_CODE_NO_ERROR;
}
Ark_Int32 CollapseImpl(Ark_FrameNode node)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    if (frameNode->GetTag() != V2::LIST_ITEM_ETS_TAG) {
        return ERROR_CODE_PARAM_ERROR;
    }
    if (!frameNode->IsOnMainTree()) {
        return ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE;
    }
    ListItemModelStatic::CollapseSwipeAction(frameNode.GetRawPtr());
    return ERROR_CODE_NO_ERROR;
}
} // ListItemSwipeActionManagerAccessor
const GENERATED_ArkUIListItemSwipeActionManagerAccessor* GetListItemSwipeActionManagerAccessor()
{
    static const GENERATED_ArkUIListItemSwipeActionManagerAccessor ListItemSwipeActionManagerAccessorImpl {
        ListItemSwipeActionManagerAccessor::DestroyPeerImpl,
        ListItemSwipeActionManagerAccessor::ConstructImpl,
        ListItemSwipeActionManagerAccessor::GetFinalizerImpl,
        ListItemSwipeActionManagerAccessor::ExpandImpl,
        ListItemSwipeActionManagerAccessor::CollapseImpl,
    };
    return &ListItemSwipeActionManagerAccessorImpl;
}
}
