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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/union_effect_container/union_effect_container_model_static.h"
#include "core/components_ng/property/union_effect_container_options.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UnionEffectContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = UnionEffectContainerModelStatic::Create(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // UnionEffectContainerModifier
namespace UnionEffectContainerInterfaceModifier {
void SetUnionEffectContainerOptionsImpl(Ark_NativePointer node,
                                        const Opt_UnionEffectContainerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = options ? Converter::OptConvert<UnionEffectContainerOptions>(*options) : std::nullopt;
    UnionEffectContainerModelStatic::SetUnionEffectContainerOptions(frameNode, convValue);
}
} // UnionEffectContainerInterfaceModifier
namespace UnionEffectContainerAttributeModifier {
void SetPointLightImpl(Ark_NativePointer node, const Ark_PointLightStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef POINT_LIGHT_ENABLE
    auto pointLightStyle = Converter::OptConvertPtr<Converter::PointLightStyle>(value);
    auto uiNode = reinterpret_cast<Ark_NodeHandle>(node);
    auto themeConstants = Converter::GetThemeConstants(uiNode, "", "");
    CHECK_NULL_VOID(themeConstants);
    if (pointLightStyle) {
        if (pointLightStyle->lightSource) {
            ViewAbstractModelStatic::SetLightPosition(frameNode, pointLightStyle->lightSource->x,
                pointLightStyle->lightSource->y,
                pointLightStyle->lightSource->z);
            ViewAbstractModelStatic::SetLightIntensity(frameNode,
                pointLightStyle->lightSource->intensity);
            ViewAbstractModelStatic::SetLightColor(frameNode, pointLightStyle->lightSource->lightColor);
        } else {
            ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
            ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
            ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        }
        // illuminated
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, pointLightStyle->illuminationType, themeConstants);
        // bloom
        ViewAbstractModelStatic::SetBloom(frameNode, pointLightStyle->bloom, themeConstants);
    } else {
        ViewAbstractModelStatic::SetLightPosition(frameNode, std::nullopt, std::nullopt, std::nullopt);
        ViewAbstractModelStatic::SetLightIntensity(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightColor(frameNode, std::nullopt);
        ViewAbstractModelStatic::SetLightIlluminated(frameNode, std::nullopt, themeConstants);
        ViewAbstractModelStatic::SetBloom(frameNode, std::nullopt, themeConstants);
    }
#endif
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
