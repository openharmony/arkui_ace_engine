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

#include "component_content_ani_modifier.h"

#include "base/log/log.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG {
void RemoveComponentFromFrameNode(ani_long node, ani_long content)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(node));
    auto contentNode = reinterpret_cast<UINode*>(content);
    CHECK_NULL_VOID(frameNode && contentNode);
    frameNode->RemoveChild(AceType::Claim<UINode>(contentNode));
    frameNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void AddComponentToFrameNode(ani_long node, ani_long content)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(node));
    auto contentNode = reinterpret_cast<UINode*>(content);
    CHECK_NULL_VOID(frameNode && contentNode);
    auto parent = contentNode->GetParent();
    auto childNode = AceType::Claim(contentNode);
    if (parent && parent != frameNode) {
        if (parent->GetTag() == "BuilderProxyNode") {
            parent->RemoveChild(childNode);
        } else {
            return;
        }
    }
    frameNode->AddChild(childNode);
    contentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

const ArkUIAniComponentConentModifier* GetArkUIAniComponentConentModifier()
{
    static const ArkUIAniComponentConentModifier impl = {
        .removeComponentFromFrameNode = OHOS::Ace::NG::RemoveComponentFromFrameNode,
        .addComponentToFrameNode = OHOS::Ace::NG::AddComponentToFrameNode,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
