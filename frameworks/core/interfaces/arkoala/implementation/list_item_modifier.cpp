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
namespace ListItemInterfaceModifier {
void SetListItemOptions0Impl(Ark_NativePointer node,
                             const Opt_ListItemOptions* value)
{
}
void SetListItemOptions1Impl(Ark_NativePointer node,
                             const Opt_String* value)
{
}
} // ListItemInterfaceModifier
namespace ListItemAttributeModifier {
void StickyImpl(Ark_NativePointer node,
                enum Ark_Sticky value)
{
}
void EditableImpl(Ark_NativePointer node,
                  const Type_ListItemAttribute_editable_Arg0* value)
{
}
void SelectableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void SwipeActionImpl(Ark_NativePointer node,
                     const Ark_SwipeActionOptions* value)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
} // ListItemAttributeModifier
const GENERATED_ArkUIListItemModifier* GetListItemModifier()
{
    static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
        ListItemInterfaceModifier::SetListItemOptions0Impl,
        ListItemInterfaceModifier::SetListItemOptions1Impl,
        ListItemAttributeModifier::StickyImpl,
        ListItemAttributeModifier::EditableImpl,
        ListItemAttributeModifier::SelectableImpl,
        ListItemAttributeModifier::SelectedImpl,
        ListItemAttributeModifier::SwipeActionImpl,
        ListItemAttributeModifier::OnSelectImpl,
    };
    return &ArkUIListItemModifierImpl;
}

}
