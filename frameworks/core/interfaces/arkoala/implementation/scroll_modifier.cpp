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
namespace ScrollInterfaceModifier {
void SetScrollOptionsImpl(Ark_NativePointer node,
                          const Opt_Scroller* scroller)
{
}
} // ScrollInterfaceModifier
namespace ScrollAttributeModifier {
void ScrollableImpl(Ark_NativePointer node,
                    enum Ark_ScrollDirection value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnWillScrollImpl(Ark_NativePointer node,
                      const Ark_CustomObject* stub_for_onWillScroll)
{
}
void OnDidScrollImpl(Ark_NativePointer node,
                     Ark_Function handler)
{
}
void OnScrollEdgeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
void OnScrollEndImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnScrollStopImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                   enum Ark_BarState barState)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Type_ScrollAttribute_scrollBarColor_Arg0* color)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Type_ScrollAttribute_scrollBarWidth_Arg0* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    enum Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            Ark_Function event)
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
                  const Type_ScrollAttribute_friction_Arg0* value)
{
}
void ScrollSnapImpl(Ark_NativePointer node,
                    const Ark_ScrollSnapOptions* value)
{
}
void EnablePagingImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void InitialOffsetImpl(Ark_NativePointer node,
                       const Ark_OffsetOptions* value)
{
}
} // ScrollAttributeModifier
const GENERATED_ArkUIScrollModifier* GetScrollModifier()
{
    static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
        ScrollInterfaceModifier::SetScrollOptionsImpl,
        ScrollAttributeModifier::ScrollableImpl,
        ScrollAttributeModifier::OnScrollImpl,
        ScrollAttributeModifier::OnWillScrollImpl,
        ScrollAttributeModifier::OnDidScrollImpl,
        ScrollAttributeModifier::OnScrollEdgeImpl,
        ScrollAttributeModifier::OnScrollStartImpl,
        ScrollAttributeModifier::OnScrollEndImpl,
        ScrollAttributeModifier::OnScrollStopImpl,
        ScrollAttributeModifier::ScrollBarImpl,
        ScrollAttributeModifier::ScrollBarColorImpl,
        ScrollAttributeModifier::ScrollBarWidthImpl,
        ScrollAttributeModifier::EdgeEffectImpl,
        ScrollAttributeModifier::OnScrollFrameBeginImpl,
        ScrollAttributeModifier::NestedScrollImpl,
        ScrollAttributeModifier::EnableScrollInteractionImpl,
        ScrollAttributeModifier::FrictionImpl,
        ScrollAttributeModifier::ScrollSnapImpl,
        ScrollAttributeModifier::EnablePagingImpl,
        ScrollAttributeModifier::InitialOffsetImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
