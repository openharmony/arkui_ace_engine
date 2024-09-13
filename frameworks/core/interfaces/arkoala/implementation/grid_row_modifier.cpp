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
namespace GridRowInterfaceModifier {
void SetGridRowOptionsImpl(Ark_NativePointer node,
                           const Opt_GridRowOptions* option)
{
}
} // GridRowInterfaceModifier
namespace GridRowAttributeModifier {
void OnBreakpointChangeImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
}
void AlignItemsImpl(Ark_NativePointer node,
                    enum Ark_ItemAlign value)
{
}
} // GridRowAttributeModifier
const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
{
    static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
        GridRowInterfaceModifier::SetGridRowOptionsImpl,
        GridRowAttributeModifier::OnBreakpointChangeImpl,
        GridRowAttributeModifier::AlignItemsImpl,
    };
    return &ArkUIGridRowModifierImpl;
}

}
