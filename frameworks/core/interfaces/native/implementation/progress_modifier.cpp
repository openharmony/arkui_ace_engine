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
namespace ProgressModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ProgressModifier
namespace ProgressInterfaceModifier {
void SetProgressOptionsImpl(Ark_NativePointer node,
                            const Ark_ProgressOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //ProgressModelNG::SetSetProgressOptions(frameNode, convValue);
}
} // ProgressInterfaceModifier
namespace ProgressAttributeModifier {
void SetValueImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ProgressModelNG::SetSetValue(frameNode, convValue);
}
void SetColorImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ProgressModelNG::SetSetColor(frameNode, convValue);
}
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ProgressModelNG::SetSetStyle(frameNode, convValue);
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ProgressModelNG::SetSetPrivacySensitive(frameNode, convValue);
}
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ProgressModelNG::SetSetContentModifier(frameNode, convValue);
}
} // ProgressAttributeModifier
const GENERATED_ArkUIProgressModifier* GetProgressModifier()
{
    static const GENERATED_ArkUIProgressModifier ArkUIProgressModifierImpl {
        ProgressModifier::ConstructImpl,
        ProgressInterfaceModifier::SetProgressOptionsImpl,
        ProgressAttributeModifier::SetValueImpl,
        ProgressAttributeModifier::SetColorImpl,
        ProgressAttributeModifier::SetStyleImpl,
        ProgressAttributeModifier::SetPrivacySensitiveImpl,
        ProgressAttributeModifier::SetContentModifierImpl,
    };
    return &ArkUIProgressModifierImpl;
}

}
