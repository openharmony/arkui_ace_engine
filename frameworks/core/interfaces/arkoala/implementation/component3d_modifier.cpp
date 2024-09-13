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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Component3DInterfaceModifier {
void SetComponent3DOptionsImpl(Ark_NativePointer node,
                               const Opt_SceneOptions* sceneOptions)
{
}
} // Component3DInterfaceModifier
namespace Component3DAttributeModifier {
void EnvironmentImpl(Ark_NativePointer node,
                     const ResourceStr* uri)
{
}
void CustomRenderImpl(Ark_NativePointer node,
                      const ResourceStr* uri,
                      Ark_Boolean selfRenderUpdate)
{
}
void ShaderImpl(Ark_NativePointer node,
                const ResourceStr* uri)
{
}
void ShaderImageTextureImpl(Ark_NativePointer node,
                            const ResourceStr* uri)
{
}
void ShaderInputBufferImpl(Ark_NativePointer node,
                           const Array_Number* buffer)
{
}
void RenderWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
}
void RenderHeightImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
}
} // Component3DAttributeModifier
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
{
    static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
        Component3DInterfaceModifier::SetComponent3DOptionsImpl,
        Component3DAttributeModifier::EnvironmentImpl,
        Component3DAttributeModifier::CustomRenderImpl,
        Component3DAttributeModifier::ShaderImpl,
        Component3DAttributeModifier::ShaderImageTextureImpl,
        Component3DAttributeModifier::ShaderInputBufferImpl,
        Component3DAttributeModifier::RenderWidthImpl,
        Component3DAttributeModifier::RenderHeightImpl,
    };
    return &ArkUIComponent3DModifierImpl;
}

}
