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
namespace ListModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ListModifier
namespace ListInterfaceModifier {
void SetListOptionsImpl(Ark_NativePointer node,
                        const Opt_ListOptions* options)
{
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void AlignListItemImpl(Ark_NativePointer node,
                    const Opt_ListItemAlign* value)
{
}
void ListDirectionImpl(Ark_NativePointer node,
                    const Opt_Axis* value)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                const Opt_BarState* value)
{
}
void ContentStartOffsetImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
}
void ContentEndOffsetImpl(Ark_NativePointer node,
                        const Opt_Number* value)
{
}
void DividerImpl(Ark_NativePointer node,
                const Opt_ListDividerOptions* value)
{
}
void EditModeImpl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
}
void MultiSelectableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void CachedCount0Impl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void CachedCount1Impl(Ark_NativePointer node,
                    const Opt_Number* count,
                    const Opt_Boolean* show)
{
}
void ChainAnimationImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void ChainAnimationOptionsImpl(Ark_NativePointer node,
                            const Opt_ChainAnimationOptions* value)
{
}
void StickyImpl(Ark_NativePointer node,
                const Opt_StickyStyle* value)
{
}
void ScrollSnapAlignImpl(Ark_NativePointer node,
                        const Opt_ScrollSnapAlign* value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                    const Opt_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
}
void FrictionImpl(Ark_NativePointer node,
                const Opt_Union_Number_Resource* value)
{
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                        const Opt_ChildrenMainSize* value)
{
}
void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
{
}
void StackFromEndImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                const Opt_Callback_Number_Number_Void* value)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Number_Void* value)
{
}
void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                    const Opt_OnScrollVisibleContentChangeCallback* value)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnScrollStopImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnItemDeleteImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Boolean* value)
{
}
void OnItemMoveImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Boolean* value)
{
}
void OnItemDragStartImpl(Ark_NativePointer node,
                        const Opt_ListAttribute_onItemDragStart_event_type* value)
{
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Void* value)
{
}
void OnItemDragMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
}
void OnItemDragLeaveImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Void* value)
{
}
void OnItemDropImpl(Ark_NativePointer node,
                    const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
}
void LanesImpl(Ark_NativePointer node,
            const Opt_Union_Number_LengthConstrain* value,
            const Opt_Length* gutter)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value,
                    const Opt_EdgeEffectOptions* options)
{
}
} // ListAttributeModifier
const GENERATED_ArkUIListModifier* GetListModifier()
{
    static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
        ListModifier::ConstructImpl,
        ListInterfaceModifier::SetListOptionsImpl,
        ListAttributeModifier::AlignListItemImpl,
        ListAttributeModifier::ListDirectionImpl,
        ListAttributeModifier::ScrollBarImpl,
        ListAttributeModifier::ContentStartOffsetImpl,
        ListAttributeModifier::ContentEndOffsetImpl,
        ListAttributeModifier::DividerImpl,
        ListAttributeModifier::EditModeImpl,
        ListAttributeModifier::MultiSelectableImpl,
        ListAttributeModifier::CachedCount0Impl,
        ListAttributeModifier::CachedCount1Impl,
        ListAttributeModifier::ChainAnimationImpl,
        ListAttributeModifier::ChainAnimationOptionsImpl,
        ListAttributeModifier::StickyImpl,
        ListAttributeModifier::ScrollSnapAlignImpl,
        ListAttributeModifier::NestedScrollImpl,
        ListAttributeModifier::EnableScrollInteractionImpl,
        ListAttributeModifier::FrictionImpl,
        ListAttributeModifier::ChildrenMainSizeImpl,
        ListAttributeModifier::MaintainVisibleContentPositionImpl,
        ListAttributeModifier::StackFromEndImpl,
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
        ListAttributeModifier::LanesImpl,
        ListAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIListModifierImpl;
}

}
