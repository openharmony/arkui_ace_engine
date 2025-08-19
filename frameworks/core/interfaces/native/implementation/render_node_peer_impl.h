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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_RENDER_NODE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_RENDER_NODE_PEER_IMPL_H

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "base/memory/referenced.h"

struct RenderNodePeer final {
public:
    OHOS::Ace::NG::LengthMetricsUnit lengthMetricsUnit{ OHOS::Ace::NG::LengthMetricsUnit::DEFAULT };
    std::optional<uint8_t> shadowAlpha{ std::nullopt };
    std::string label = "";
    friend OHOS::Ace::NG::PeerUtils;
    const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& GetFrameNode() const
    {
        return node;
    }

protected:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node;

    RenderNodePeer(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& src)
        : node(src)
    {
        if (node) {
            node->SetIsArkTsRenderNode(true);
        }
    }

    RenderNodePeer(OHOS::Ace::NG::FrameNode* src)
        : node(OHOS::Ace::Referenced::Claim<OHOS::Ace::NG::FrameNode>(src))
    {
        if (node) {
            node->SetIsArkTsRenderNode(true);
        }
    }

private:
    ~RenderNodePeer() = default;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_RENDER_NODE_PEER_IMPL_H
