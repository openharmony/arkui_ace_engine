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
namespace BlankInterfaceModifier {
void SetBlankOptionsImpl(Ark_NativePointer node,
                         const Opt_Type_BlankInterface_setBlankOptions_Arg0* min)
{
}
} // BlankInterfaceModifier
namespace BlankAttributeModifier {
void ColorImpl(Ark_NativePointer node,
               const ResourceColor* value)
{
}
} // BlankAttributeModifier
const GENERATED_ArkUIBlankModifier* GetBlankModifier()
{
    static const GENERATED_ArkUIBlankModifier ArkUIBlankModifierImpl {
        BlankInterfaceModifier::SetBlankOptionsImpl,
        BlankAttributeModifier::ColorImpl,
    };
    return &ArkUIBlankModifierImpl;
}

}
