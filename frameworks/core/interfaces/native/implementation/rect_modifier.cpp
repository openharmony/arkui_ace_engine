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
namespace RectModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RectModifier
namespace RectInterfaceModifier {
void SetRectOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_RectOptions_RoundedRectOptions* options)
{
}
} // RectInterfaceModifier
namespace RectAttributeModifier {
void RadiusWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
}
void RadiusHeightImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
}
void RadiusImpl(Ark_NativePointer node,
                const Opt_Union_Number_String_Array_Union_Number_String* value)
{
}
} // RectAttributeModifier
const GENERATED_ArkUIRectModifier* GetRectModifier()
{
    static const GENERATED_ArkUIRectModifier ArkUIRectModifierImpl {
        RectModifier::ConstructImpl,
        RectInterfaceModifier::SetRectOptionsImpl,
        RectAttributeModifier::RadiusWidthImpl,
        RectAttributeModifier::RadiusHeightImpl,
        RectAttributeModifier::RadiusImpl,
    };
    return &ArkUIRectModifierImpl;
}

}
