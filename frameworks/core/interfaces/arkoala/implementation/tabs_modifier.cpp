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
namespace TabsInterfaceModifier {
void SetTabsOptionsImpl(Ark_NativePointer node,
                        const Opt_Type_TabsInterface_setTabsOptions_Arg0* value)
{
}
} // TabsInterfaceModifier
namespace TabsAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void BarPositionImpl(Ark_NativePointer node,
                     enum Ark_BarPosition value)
{
}
void ScrollableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void BarMode0Impl(Ark_NativePointer node,
                  enum Ark_BarMode value)
{
}
void BarMode1Impl(Ark_NativePointer node,
                  enum Ark_BarMode value,
                  const Ark_ScrollableBarModeOptions* options)
{
}
void BarMode2Impl(Ark_NativePointer node,
                  enum Ark_BarMode value,
                  const Opt_ScrollableBarModeOptions* options)
{
}
void BarWidthImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void BarHeightImpl(Ark_NativePointer node,
                   const Ark_Length* value)
{
}
void AnimationDurationImpl(Ark_NativePointer node,
                           const Ark_Number* value)
{
}
void AnimationModeImpl(Ark_NativePointer node,
                       const Opt_AnimationMode* mode)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* edgeEffect)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnTabBarClickImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          Ark_Function handler)
{
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        Ark_Function handler)
{
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        Ark_Function handler)
{
}
void FadingEdgeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Type_TabsAttribute_divider_Arg0* value)
{
}
void BarOverlapImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void BarBackgroundColorImpl(Ark_NativePointer node,
                            const ResourceColor* value)
{
}
void BarGridAlignImpl(Ark_NativePointer node,
                      const Ark_BarGridColumnOptions* value)
{
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 Ark_Function delegate)
{
}
void BarBackgroundBlurStyleImpl(Ark_NativePointer node,
                                enum Ark_BlurStyle value)
{
}
void OnContentWillChangeImpl(Ark_NativePointer node,
                             Ark_Function handler)
{
}
} // TabsAttributeModifier
const GENERATED_ArkUITabsModifier* GetTabsModifier()
{
    static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
        TabsInterfaceModifier::SetTabsOptionsImpl,
        TabsAttributeModifier::VerticalImpl,
        TabsAttributeModifier::BarPositionImpl,
        TabsAttributeModifier::ScrollableImpl,
        TabsAttributeModifier::BarMode0Impl,
        TabsAttributeModifier::BarMode1Impl,
        TabsAttributeModifier::BarMode2Impl,
        TabsAttributeModifier::BarWidthImpl,
        TabsAttributeModifier::BarHeightImpl,
        TabsAttributeModifier::AnimationDurationImpl,
        TabsAttributeModifier::AnimationModeImpl,
        TabsAttributeModifier::EdgeEffectImpl,
        TabsAttributeModifier::OnChangeImpl,
        TabsAttributeModifier::OnTabBarClickImpl,
        TabsAttributeModifier::OnAnimationStartImpl,
        TabsAttributeModifier::OnAnimationEndImpl,
        TabsAttributeModifier::OnGestureSwipeImpl,
        TabsAttributeModifier::FadingEdgeImpl,
        TabsAttributeModifier::DividerImpl,
        TabsAttributeModifier::BarOverlapImpl,
        TabsAttributeModifier::BarBackgroundColorImpl,
        TabsAttributeModifier::BarGridAlignImpl,
        TabsAttributeModifier::CustomContentTransitionImpl,
        TabsAttributeModifier::BarBackgroundBlurStyleImpl,
        TabsAttributeModifier::OnContentWillChangeImpl,
    };
    return &ArkUITabsModifierImpl;
}

}
