/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
namespace UnionEffectContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // UnionEffectContainerModifier
namespace UnionEffectContainerInterfaceModifier {
void SetUnionEffectContainerOptionsImpl(Ark_NativePointer node,
                                        const Opt_UnionEffectContainerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // UnionEffectContainerInterfaceModifier
namespace UnionEffectContainerAttributeModifier {
void SetPointLightImpl(Ark_NativePointer node,
                       const Ark_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
}
} // UnionEffectContainerAttributeModifier
const GENERATED_ArkUIUnionEffectContainerModifier* GetUnionEffectContainerModifier()
{
    static const GENERATED_ArkUIUnionEffectContainerModifier ArkUIUnionEffectContainerModifierImpl {
        UnionEffectContainerModifier::ConstructImpl,
        UnionEffectContainerInterfaceModifier::SetUnionEffectContainerOptionsImpl,
        UnionEffectContainerAttributeModifier::SetPointLightImpl,
    };
    return &ArkUIUnionEffectContainerModifierImpl;
}

}
