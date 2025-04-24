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
namespace PasteButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // PasteButtonModifier
namespace PasteButtonInterfaceModifier {
void SetPasteButtonOptions0Impl(Ark_NativePointer node)
{
}
void SetPasteButtonOptions1Impl(Ark_NativePointer node,
                                const Ark_PasteButtonOptions* options)
{
}
} // PasteButtonInterfaceModifier
namespace PasteButtonAttributeModifier {
void OnClickImpl(Ark_NativePointer node,
                 const Opt_PasteButtonCallback* value)
{
}
} // PasteButtonAttributeModifier
const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier()
{
    static const GENERATED_ArkUIPasteButtonModifier ArkUIPasteButtonModifierImpl {
        PasteButtonModifier::ConstructImpl,
        PasteButtonInterfaceModifier::SetPasteButtonOptions0Impl,
        PasteButtonInterfaceModifier::SetPasteButtonOptions1Impl,
        PasteButtonAttributeModifier::OnClickImpl,
    };
    return &ArkUIPasteButtonModifierImpl;
}

}
