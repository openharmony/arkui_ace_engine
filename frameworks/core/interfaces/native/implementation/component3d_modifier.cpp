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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Component3DInterfaceModifier {
void SetComponent3DOptionsImpl(Ark_NativePointer node,
                               const Opt_SceneOptions* sceneOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = sceneOptions ? Converter::OptConvert<type>(*sceneOptions) : std::nullopt;
    //Component3DModelNG::SetSetComponent3DOptions(frameNode, convValue);
}
} // Component3DInterfaceModifier
namespace Component3DAttributeModifier {
void EnvironmentImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetEnvironment(frameNode, convValue);
}
void ShaderImpl(Ark_NativePointer node,
                const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetShader(frameNode, convValue);
}
void ShaderImageTextureImpl(Ark_NativePointer node,
                            const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetShaderImageTexture(frameNode, convValue);
}
void ShaderInputBufferImpl(Ark_NativePointer node,
                           const Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetShaderInputBuffer(frameNode, convValue);
}
void RenderWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetRenderWidth(frameNode, convValue);
}
void RenderHeightImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //Component3DModelNG::SetRenderHeight(frameNode, convValue);
}
void CustomRenderImpl(Ark_NativePointer node,
                      const Ark_ResourceStr* uri,
                      Ark_Boolean selfRenderUpdate)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(uri);
    //auto convValue = Converter::OptConvert<type>(uri); // for enums
    //Component3DModelNG::SetCustomRender(frameNode, convValue);
}
} // Component3DAttributeModifier
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
{
    static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
        Component3DInterfaceModifier::SetComponent3DOptionsImpl,
        Component3DAttributeModifier::EnvironmentImpl,
        Component3DAttributeModifier::ShaderImpl,
        Component3DAttributeModifier::ShaderImageTextureImpl,
        Component3DAttributeModifier::ShaderInputBufferImpl,
        Component3DAttributeModifier::RenderWidthImpl,
        Component3DAttributeModifier::RenderHeightImpl,
        Component3DAttributeModifier::CustomRenderImpl,
    };
    return &ArkUIComponent3DModifierImpl;
}

}
