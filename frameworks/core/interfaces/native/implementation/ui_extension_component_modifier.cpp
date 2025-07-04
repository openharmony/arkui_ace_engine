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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIExtensionComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // UIExtensionComponentModifier
namespace UIExtensionComponentInterfaceModifier {
void SetUIExtensionComponentOptionsImpl(Ark_NativePointer node,
                                        const Ark_Want* want,
                                        const Opt_UIExtensionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(want);
    //auto convValue = Converter::OptConvert<type>(want); // for enums
    //UIExtensionComponentModelNG::SetSetUIExtensionComponentOptions(frameNode, convValue);
}
} // UIExtensionComponentInterfaceModifier
namespace UIExtensionComponentAttributeModifier {
void SetOnRemoteReadyImpl(Ark_NativePointer node,
                          const Opt_Callback_UIExtensionProxy_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //UIExtensionComponentModelNG::SetSetOnRemoteReady(frameNode, convValue);
}
void SetOnReceiveImpl(Ark_NativePointer node,
                      const Opt_Callback_Map_String_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //UIExtensionComponentModelNG::SetSetOnReceive(frameNode, convValue);
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_ErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //UIExtensionComponentModelNG::SetSetOnError(frameNode, convValue);
}
void SetOnTerminatedImpl(Ark_NativePointer node,
                         const Opt_Callback_TerminationInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //UIExtensionComponentModelNG::SetSetOnTerminated(frameNode, convValue);
}
} // UIExtensionComponentAttributeModifier
const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
{
    static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
        UIExtensionComponentModifier::ConstructImpl,
        UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
        UIExtensionComponentAttributeModifier::SetOnRemoteReadyImpl,
        UIExtensionComponentAttributeModifier::SetOnReceiveImpl,
        UIExtensionComponentAttributeModifier::SetOnErrorImpl,
        UIExtensionComponentAttributeModifier::SetOnTerminatedImpl,
    };
    return &ArkUIUIExtensionComponentModifierImpl;
}

}
