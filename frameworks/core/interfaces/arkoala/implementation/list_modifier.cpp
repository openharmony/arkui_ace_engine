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
namespace ListInterfaceModifier {
void SetListOptionsImpl(Ark_NativePointer node,
                        const Opt_ListOptions* options)
{
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void LanesImpl(Ark_NativePointer node,
               const Type_ListAttribute_lanes_Arg0* value,
               const Opt_Dimension* gutter)
{
}
void AlignListItemImpl(Ark_NativePointer node,
                       Ark_Int32 value)
{
}
void ListDirectionImpl(Ark_NativePointer node,
                       Ark_Int32 value)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_Int32 value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_Int32 value,
                    const Opt_EdgeEffectOptions* options)
{
}
void ContentStartOffsetImpl(Ark_NativePointer node,
                            const Ark_Number* value)
{
}
void ContentEndOffsetImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Type_ListAttribute_divider_Arg0* value)
{
}
void EditModeImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void MultiSelectableImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void ChainAnimationImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
}
void ChainAnimationOptionsImpl(Ark_NativePointer node,
                               const Ark_ChainAnimationOptions* value)
{
}
void StickyImpl(Ark_NativePointer node,
                Ark_Int32 value)
{
}
void ScrollSnapAlignImpl(Ark_NativePointer node,
                         Ark_Int32 value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Type_ListAttribute_friction_Arg0* value)
{
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                          const Ark_Materialized* value)
{
}
void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                        Ark_Boolean enabled)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                      Ark_Function handler)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
void OnScrollStopImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnItemDeleteImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnItemMoveImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnItemDragStartImpl(Ark_NativePointer node,
                         Ark_Function event)
{
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                         Ark_Function event)
{
}
void OnItemDragMoveImpl(Ark_NativePointer node,
                        Ark_Function event)
{
}
void OnItemDragLeaveImpl(Ark_NativePointer node,
                         Ark_Function event)
{
}
void OnItemDropImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            Ark_Function event)
{
}
} // ListAttributeModifier
const GENERATED_ArkUIListModifier* GetListModifier()
{
    static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
        ListInterfaceModifier::SetListOptionsImpl,
        ListAttributeModifier::LanesImpl,
        ListAttributeModifier::AlignListItemImpl,
        ListAttributeModifier::ListDirectionImpl,
        ListAttributeModifier::ScrollBarImpl,
        ListAttributeModifier::EdgeEffectImpl,
        ListAttributeModifier::ContentStartOffsetImpl,
        ListAttributeModifier::ContentEndOffsetImpl,
        ListAttributeModifier::DividerImpl,
        ListAttributeModifier::EditModeImpl,
        ListAttributeModifier::MultiSelectableImpl,
        ListAttributeModifier::CachedCountImpl,
        ListAttributeModifier::ChainAnimationImpl,
        ListAttributeModifier::ChainAnimationOptionsImpl,
        ListAttributeModifier::StickyImpl,
        ListAttributeModifier::ScrollSnapAlignImpl,
        ListAttributeModifier::NestedScrollImpl,
        ListAttributeModifier::EnableScrollInteractionImpl,
        ListAttributeModifier::FrictionImpl,
        ListAttributeModifier::ChildrenMainSizeImpl,
        ListAttributeModifier::MaintainVisibleContentPositionImpl,
        ListAttributeModifier::OnScrollImpl,
        ListAttributeModifier::OnScrollIndexImpl,
        ListAttributeModifier::OnScrollVisibleContentChangeImpl,
        ListAttributeModifier::OnReachStartImpl,
        ListAttributeModifier::OnReachEndImpl,
        ListAttributeModifier::OnScrollStartImpl,
        ListAttributeModifier::OnScrollStopImpl,
        ListAttributeModifier::OnItemDeleteImpl,
        ListAttributeModifier::OnItemMoveImpl,
        ListAttributeModifier::OnItemDragStartImpl,
        ListAttributeModifier::OnItemDragEnterImpl,
        ListAttributeModifier::OnItemDragMoveImpl,
        ListAttributeModifier::OnItemDragLeaveImpl,
        ListAttributeModifier::OnItemDropImpl,
        ListAttributeModifier::OnScrollFrameBeginImpl,
    };
    return &ArkUIListModifierImpl;
}

}
