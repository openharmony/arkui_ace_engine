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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContentModifierHelperAccessor {
void ContentModifierRadioImpl(Ark_NativePointer node,
                              const Ark_Object* contentModifier,
                              const RadioModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](RadioConfiguration config) -> RefPtr<FrameNode> {
        Ark_RadioConfiguration radioConfig;
        radioConfig.value = Converter::ArkValue<Ark_String>(config.value_);
        radioConfig.checked = Converter::ArkValue<Ark_Boolean>(config.checked_);
        radioConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        radioConfig.triggerChange = CallbackKeeper::DefineBooleanCallback<Callback_Boolean_Void>([weakNode](bool change) {
            auto radioNode = weakNode.Upgrade();
            CHECK_NULL_VOID(radioNode);
            RadioModelNG::SetChangeValue(AceType::RawPtr(radioNode), change);
        });
        auto returnNode = arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, radioConfig);
        if (returnNode) {
            auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
            return contentNode;
        }
        return nullptr;
    });
}
void ResetContentModifierRadioImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, nullptr);
}
} // ContentModifierHelperAccessor
const GENERATED_ArkUIContentModifierHelperAccessor* GetContentModifierHelperAccessor()
{
    static const GENERATED_ArkUIContentModifierHelperAccessor ContentModifierHelperAccessorImpl {
        ContentModifierHelperAccessor::ContentModifierRadioImpl,
        ContentModifierHelperAccessor::ResetContentModifierRadioImpl,
    };
    return &ContentModifierHelperAccessorImpl;
}

}
