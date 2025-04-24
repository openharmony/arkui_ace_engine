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
}
} // Component3DInterfaceModifier
namespace Component3DAttributeModifier {
void EnvironmentImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value)
{
}
void ShaderImpl(Ark_NativePointer node,
                const Opt_ResourceStr* value)
{
}
void ShaderImageTextureImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value)
{
}
void ShaderInputBufferImpl(Ark_NativePointer node,
                           const Opt_Array_Number* value)
{
}
void RenderWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
}
void RenderHeightImpl(Ark_NativePointer node,
                      const Opt_Length* value)
{
}
void CustomRenderImpl(Ark_NativePointer node,
                      const Opt_ResourceStr* uri,
                      const Opt_Boolean* selfRenderUpdate)
{
}
} // Component3DAttributeModifier
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
{
    static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
        Component3DModifier::ConstructImpl,
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
