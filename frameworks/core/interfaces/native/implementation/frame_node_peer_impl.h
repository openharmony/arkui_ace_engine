/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "base/memory/referenced.h"

struct FrameNodePeer {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node;

    static FrameNodePeer *Create(const Ark_UIContext* uiContext)
    {
        return new FrameNodePeer;
    }

    static FrameNodePeer *Create(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& src)
    {
        return new FrameNodePeer{src};
    }

    static FrameNodePeer *Create(OHOS::Ace::NG::FrameNode* src)
    {
        return new FrameNodePeer{OHOS::Ace::Referenced::Claim<OHOS::Ace::NG::FrameNode>(src)};
    }

    static void Destroy(FrameNodePeer *peer)
    {
        delete peer;
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H
