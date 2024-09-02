/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_container_modifier.h"

#include "core/components_ng/pattern/node_container/node_container_pattern.h"

namespace OHOS::Ace::NG {
void Rebuild(int32_t nodeId)
{
    auto nativeNodePt = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    auto frameNode = AceType::DynamicCast<FrameNode>(nativeNodePt);
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->RemakeNode();
}

void Clean(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->CleanChild();
}

namespace NodeModifier {
const ArkUINodeContainerModifier* GetNodeContainerModifier()
{
    static const ArkUINodeContainerModifier modifier = { Rebuild, Clean };
    return &modifier;
}

const CJUINodeContainerModifier* GetCJUINodeContainerModifier()
{
    static const CJUINodeContainerModifier modifier = { Rebuild, Clean };
    return &modifier;
}
}
}
