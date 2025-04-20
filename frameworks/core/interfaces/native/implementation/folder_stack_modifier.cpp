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
namespace FolderStackModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // FolderStackModifier
namespace FolderStackInterfaceModifier {
void SetFolderStackOptionsImpl(Ark_NativePointer node,
                               const Opt_FolderStackOptions* options)
{
}
} // FolderStackInterfaceModifier
namespace FolderStackAttributeModifier {
void AlignContentImpl(Ark_NativePointer node,
                      const Opt_Alignment* value)
{
}
void OnFolderStateChangeImpl(Ark_NativePointer node,
                             const Opt_OnFoldStatusChangeCallback* value)
{
}
void OnHoverStatusChangeImpl(Ark_NativePointer node,
                             const Opt_OnHoverStatusChangeCallback* value)
{
}
void EnableAnimationImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
}
void AutoHalfFoldImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
} // FolderStackAttributeModifier
const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier()
{
    static const GENERATED_ArkUIFolderStackModifier ArkUIFolderStackModifierImpl {
        FolderStackModifier::ConstructImpl,
        FolderStackInterfaceModifier::SetFolderStackOptionsImpl,
        FolderStackAttributeModifier::AlignContentImpl,
        FolderStackAttributeModifier::OnFolderStateChangeImpl,
        FolderStackAttributeModifier::OnHoverStatusChangeImpl,
        FolderStackAttributeModifier::EnableAnimationImpl,
        FolderStackAttributeModifier::AutoHalfFoldImpl,
    };
    return &ArkUIFolderStackModifierImpl;
}

}
