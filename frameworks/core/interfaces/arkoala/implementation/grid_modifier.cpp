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
namespace GridInterfaceModifier {
void SetGridOptionsImpl(Ark_NativePointer node,
                        const Opt_Scroller* scroller,
                        const Opt_GridLayoutOptions* layoutOptions)
{
}
} // GridInterfaceModifier
namespace GridAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void RowsGapImpl(Ark_NativePointer node,
                 const Ark_Length* value)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Type_GridAttribute_scrollBarWidth_Arg0* value)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Type_GridAttribute_scrollBarColor_Arg0* value)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                   enum Ark_BarState value)
{
}
void OnScrollBarUpdateImpl(Ark_NativePointer node,
                           Ark_Function event)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
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
void MaxCountImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void MinCountImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void CellLengthImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         enum Ark_GridDirection value)
{
}
void SupportAnimationImpl(Ark_NativePointer node,
                          Ark_Boolean value)
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
void EdgeEffectImpl(Ark_NativePointer node,
                    enum Ark_EdgeEffect value,
                    const Opt_EdgeEffectOptions* options)
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
                  const Type_GridAttribute_friction_Arg0* value)
{
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_GridItemAlignment* alignment)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function event)
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
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            Ark_Function event)
{
}
} // GridAttributeModifier
const GENERATED_ArkUIGridModifier* GetGridModifier()
{
    static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
        GridInterfaceModifier::SetGridOptionsImpl,
        GridAttributeModifier::ColumnsTemplateImpl,
        GridAttributeModifier::RowsTemplateImpl,
        GridAttributeModifier::ColumnsGapImpl,
        GridAttributeModifier::RowsGapImpl,
        GridAttributeModifier::ScrollBarWidthImpl,
        GridAttributeModifier::ScrollBarColorImpl,
        GridAttributeModifier::ScrollBarImpl,
        GridAttributeModifier::OnScrollBarUpdateImpl,
        GridAttributeModifier::OnScrollIndexImpl,
        GridAttributeModifier::CachedCountImpl,
        GridAttributeModifier::EditModeImpl,
        GridAttributeModifier::MultiSelectableImpl,
        GridAttributeModifier::MaxCountImpl,
        GridAttributeModifier::MinCountImpl,
        GridAttributeModifier::CellLengthImpl,
        GridAttributeModifier::LayoutDirectionImpl,
        GridAttributeModifier::SupportAnimationImpl,
        GridAttributeModifier::OnItemDragStartImpl,
        GridAttributeModifier::OnItemDragEnterImpl,
        GridAttributeModifier::OnItemDragMoveImpl,
        GridAttributeModifier::OnItemDragLeaveImpl,
        GridAttributeModifier::OnItemDropImpl,
        GridAttributeModifier::EdgeEffectImpl,
        GridAttributeModifier::NestedScrollImpl,
        GridAttributeModifier::EnableScrollInteractionImpl,
        GridAttributeModifier::FrictionImpl,
        GridAttributeModifier::AlignItemsImpl,
        GridAttributeModifier::OnScrollImpl,
        GridAttributeModifier::OnReachStartImpl,
        GridAttributeModifier::OnReachEndImpl,
        GridAttributeModifier::OnScrollStartImpl,
        GridAttributeModifier::OnScrollStopImpl,
        GridAttributeModifier::OnScrollFrameBeginImpl,
    };
    return &ArkUIGridModifierImpl;
}

}
