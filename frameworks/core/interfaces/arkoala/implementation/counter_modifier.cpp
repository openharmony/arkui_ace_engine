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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CounterInterfaceModifier {
void SetCounterOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because Counter don`t have any options
}
} // CounterInterfaceModifier
namespace CounterAttributeModifier {
void OnIncImpl(Ark_NativePointer node,
               const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCounterEventsReceiver()->onInc(frameNode->GetId());
    };
    CounterModelNG::SetOnInc(frameNode, onEvent);
}
void OnDecImpl(Ark_NativePointer node,
               const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCounterEventsReceiver()->onDec(frameNode->GetId());
    };
    CounterModelNG::SetOnDec(frameNode, onEvent);
}
void EnableDecImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableDec(frameNode, value);
}
void EnableIncImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableInc(frameNode, value);
}
} // CounterAttributeModifier
const GENERATED_ArkUICounterModifier* GetCounterModifier()
{
    static const GENERATED_ArkUICounterModifier ArkUICounterModifierImpl {
        CounterInterfaceModifier::SetCounterOptionsImpl,
        CounterAttributeModifier::OnIncImpl,
        CounterAttributeModifier::OnDecImpl,
        CounterAttributeModifier::EnableDecImpl,
        CounterAttributeModifier::EnableIncImpl,
    };
    return &ArkUICounterModifierImpl;
}

}
