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

#include "content_slot_ani_modifier.h"

#include "core/components_ng/syntax/content_slot_node.h"
#include "core/interfaces/native/implementation/node_content_peer.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

ArkUIContentSlot ContentSlotConstruct(ArkUI_Int32 id)
{
    auto slot = ContentSlotNode::GetOrCreateContentSlot(id);
    CHECK_NULL_RETURN(slot, nullptr);
    slot->IncRefCount();
    return reinterpret_cast<ArkUIContentSlot>(AceType::RawPtr(slot));
}

void SetContentSlotOptions(ArkUIContentSlot node, ArkUINodeContent value)
{
    auto slot = reinterpret_cast<ContentSlotNode*>(node);
    CHECK_NULL_VOID(slot);
    if (value) {
        auto contentPtr = reinterpret_cast<NodeContentPeer*>(value);
        CHECK_NULL_VOID(contentPtr);
        auto content = contentPtr->content;
        CHECK_NULL_VOID(content);
        slot->AttachNodeContent(AceType::RawPtr(content));
    } else {
        slot->DetachNodeContent();
    }
}

const ArkUIAniContentSlotModifier* GetContentSlotAniModifier()
{
    static const ArkUIAniContentSlotModifier impl = { .construct = OHOS::Ace::NG::ContentSlotConstruct,
        .setContentSlotOptions = OHOS::Ace::NG::SetContentSlotOptions };
    return &impl;
}

} // namespace OHOS::Ace::NG