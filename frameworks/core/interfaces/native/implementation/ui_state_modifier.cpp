/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace UIStateModifier {

int64_t GetUIStateImpl(Ark_NativePointer node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, 0);
    return eventHub->GetCurrentUIState();
}
} // namespace UIStateModifier

const GENERATED_ArkUIStateModifier* GetUIStateModifier()
{
    static const GENERATED_ArkUIStateModifier UIStateModifierImpl {
        UIStateModifier::GetUIStateImpl,
    };
    return &UIStateModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
