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
namespace Component3DModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // Component3DModifier
namespace Component3DInterfaceModifier {
void SetComponent3DOptionsImpl(Ark_NativePointer node,
                               const Opt_SceneOptions* sceneOptions)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = sceneOptions ? Converter::OptConvert<type>(*sceneOptions) : std::nullopt;
    // Component3DModelNG::SetSetComponent3DOptions(frameNode, convValue);
}
} // Component3DInterfaceModifier
namespace Component3DAttributeModifier {
void SetEnvironmentImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetEnvironment(frameNode, convValue);
}
void SetShaderImpl(Ark_NativePointer node,
                   const Opt_ResourceStr* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetShader(frameNode, convValue);
}
void SetShaderImageTextureImpl(Ark_NativePointer node,
                               const Opt_ResourceStr* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetShaderImageTexture(frameNode, convValue);
}
void SetShaderInputBufferImpl(Ark_NativePointer node,
                              const Opt_Array_Number* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetShaderInputBuffer(frameNode, convValue);
}
void SetRenderWidthImpl(Ark_NativePointer node,
                        const Opt_Dimension* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetRenderWidth(frameNode, convValue);
}
void SetRenderHeightImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // Component3DModelNG::SetSetRenderHeight(frameNode, convValue);
}
void SetCustomRenderImpl(Ark_NativePointer node,
                         const Opt_ResourceStr* uri,
                         const Opt_Boolean* selfRenderUpdate)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(uri);
    //auto convValue = Converter::OptConvert<type>(uri); // for enums
    // Component3DModelNG::SetSetCustomRender(frameNode, convValue);
}
} // Component3DAttributeModifier
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
{
    static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
        Component3DModifier::ConstructImpl,
        Component3DInterfaceModifier::SetComponent3DOptionsImpl,
        Component3DAttributeModifier::SetEnvironmentImpl,
        Component3DAttributeModifier::SetShaderImpl,
        Component3DAttributeModifier::SetShaderImageTextureImpl,
        Component3DAttributeModifier::SetShaderInputBufferImpl,
        Component3DAttributeModifier::SetRenderWidthImpl,
        Component3DAttributeModifier::SetRenderHeightImpl,
        Component3DAttributeModifier::SetCustomRenderImpl,
    };
    return &ArkUIComponent3DModifierImpl;
}

}
