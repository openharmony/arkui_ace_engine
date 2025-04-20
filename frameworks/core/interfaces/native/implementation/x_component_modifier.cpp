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
namespace XComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // XComponentModifier
namespace XComponentInterfaceModifier {
void SetXComponentOptions0Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_callable0_value* value)
{
}
void SetXComponentOptions1Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_callable1_value* value)
{
}
void SetXComponentOptions2Impl(Ark_NativePointer node,
                               const Ark_XComponentOptions* options)
{
}
void SetXComponentOptions3Impl(Ark_NativePointer node,
                               const Ark_NativeXComponentParameters* params)
{
}
} // XComponentInterfaceModifier
namespace XComponentAttributeModifier {
void OnLoadImpl(Ark_NativePointer node,
                const Opt_OnNativeLoadCallback* value)
{
}
void OnDestroyImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void EnableSecureImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void HdrBrightnessImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
}
void EnableTransparentLayerImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
}
} // XComponentAttributeModifier
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
{
    static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
        XComponentModifier::ConstructImpl,
        XComponentInterfaceModifier::SetXComponentOptions0Impl,
        XComponentInterfaceModifier::SetXComponentOptions1Impl,
        XComponentInterfaceModifier::SetXComponentOptions2Impl,
        XComponentInterfaceModifier::SetXComponentOptions3Impl,
        XComponentAttributeModifier::OnLoadImpl,
        XComponentAttributeModifier::OnDestroyImpl,
        XComponentAttributeModifier::EnableAnalyzerImpl,
        XComponentAttributeModifier::EnableSecureImpl,
        XComponentAttributeModifier::HdrBrightnessImpl,
        XComponentAttributeModifier::EnableTransparentLayerImpl,
    };
    return &ArkUIXComponentModifierImpl;
}

}
