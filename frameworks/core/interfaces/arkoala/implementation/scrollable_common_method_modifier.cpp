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
namespace ScrollableCommonMethodModifier {
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_Int32 barState)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Type_ScrollableCommonMethod_scrollBarColor_Arg0* color)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Type_ScrollableCommonMethod_scrollBarWidth_Arg0* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_Int32 edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* enabled,
                    const Opt_FadingEdgeOptions* options)
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
                  const Type_ScrollableCommonMethod_friction_Arg0* value)
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
void FlingSpeedLimitImpl(Ark_NativePointer node,
                         const Ark_Number* speedLimit)
{
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ScrollBarImpl,
        ScrollableCommonMethodModifier::ScrollBarColorImpl,
        ScrollableCommonMethodModifier::ScrollBarWidthImpl,
        ScrollableCommonMethodModifier::EdgeEffectImpl,
        ScrollableCommonMethodModifier::FadingEdgeImpl,
        ScrollableCommonMethodModifier::NestedScrollImpl,
        ScrollableCommonMethodModifier::EnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::FrictionImpl,
        ScrollableCommonMethodModifier::OnScrollImpl,
        ScrollableCommonMethodModifier::OnWillScrollImpl,
        ScrollableCommonMethodModifier::OnDidScrollImpl,
        ScrollableCommonMethodModifier::OnReachStartImpl,
        ScrollableCommonMethodModifier::OnReachEndImpl,
        ScrollableCommonMethodModifier::OnScrollStartImpl,
        ScrollableCommonMethodModifier::OnScrollStopImpl,
        ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
