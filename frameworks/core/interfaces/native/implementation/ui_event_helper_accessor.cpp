/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "ui_scrollable_event_peer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
void ApplyPeerNode(Ark_UIScrollableCommonEvent peer, Ark_NativePointer node)
{
    CHECK_NULL_VOID(peer);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    peer->node = frameNode;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIEventHelperAccessor {
Ark_UIGridEvent ConstructGridEventImpl(Ark_NativePointer node)
{
    auto eventPeer = PeerUtils::CreatePeer<UIGridEventPeer>();
    ApplyPeerNode(eventPeer, node);
    return eventPeer;
}
Ark_UIListEvent ConstructListEventImpl(Ark_NativePointer node)
{
    auto eventPeer = PeerUtils::CreatePeer<UIListEventPeer>();
    ApplyPeerNode(eventPeer, node);
    return eventPeer;
}
Ark_UIScrollableCommonEvent ConstructScrollableCommonEventImpl(Ark_NativePointer node)
{
    auto eventPeer = PeerUtils::CreatePeer<UIScrollableCommonEventPeer>();
    ApplyPeerNode(eventPeer, node);
    return eventPeer;
}
Ark_UIScrollEvent ConstructScrollEventImpl(Ark_NativePointer node)
{
    auto eventPeer = PeerUtils::CreatePeer<UIScrollEventPeer>();
    ApplyPeerNode(eventPeer, node);
    return eventPeer;
}
Ark_UIWaterFlowEvent ConstructWaterFlowEventImpl(Ark_NativePointer node)
{
    auto eventPeer = PeerUtils::CreatePeer<UIWaterFlowEventPeer>();
    ApplyPeerNode(eventPeer, node);
    return eventPeer;
}
} // UIEventHelperAccessor
const GENERATED_ArkUIUIEventHelperAccessor* GetUIEventHelperAccessor()
{
    static const GENERATED_ArkUIUIEventHelperAccessor UIEventHelperAccessorImpl {
        UIEventHelperAccessor::ConstructGridEventImpl,
        UIEventHelperAccessor::ConstructListEventImpl,
        UIEventHelperAccessor::ConstructScrollableCommonEventImpl,
        UIEventHelperAccessor::ConstructScrollEventImpl,
        UIEventHelperAccessor::ConstructWaterFlowEventImpl,
    };
    return &UIEventHelperAccessorImpl;
}

}
