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
namespace SwiperInterfaceModifier {
void SetSwiperOptionsImpl(Ark_NativePointer node,
                          const Opt_SwiperController* controller)
{
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void IndexImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
}
void AutoPlayImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void IntervalImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void IndicatorImpl(Ark_NativePointer node,
                   const Type_SwiperAttribute_indicator_Arg0* value)
{
}
void DisplayArrowImpl(Ark_NativePointer node,
                      const Type_SwiperAttribute_displayArrow_Arg0* value,
                      const Opt_Boolean* isHoverShow)
{
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void VerticalImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void ItemSpaceImpl(Ark_NativePointer node,
                   const Type_SwiperAttribute_itemSpace_Arg0* value)
{
}
void DisplayModeImpl(Ark_NativePointer node,
                     enum Ark_SwiperDisplayMode value)
{
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void DisplayCountImpl(Ark_NativePointer node,
                      const Type_SwiperAttribute_displayCount_Arg0* value,
                      const Opt_Boolean* swipeByGroup)
{
}
void EffectModeImpl(Ark_NativePointer node,
                    enum Ark_EdgeEffect value)
{
}
void DisableSwipeImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void CurveImpl(Ark_NativePointer node,
               const Type_SwiperAttribute_curve_Arg0* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void IndicatorStyleImpl(Ark_NativePointer node,
                        const Opt_IndicatorStyle* value)
{
}
void PrevMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
}
void NextMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          Ark_Function event)
{
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        Ark_Function event)
{
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        Ark_Function event)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      enum Ark_SwiperNestedScrollMode value)
{
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Ark_SwiperContentAnimatedTransition* transition)
{
}
void OnContentDidScrollImpl(Ark_NativePointer node,
                            Ark_Function handler)
{
}
void IndicatorInteractiveImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::IndexImpl,
        SwiperAttributeModifier::AutoPlayImpl,
        SwiperAttributeModifier::IntervalImpl,
        SwiperAttributeModifier::IndicatorImpl,
        SwiperAttributeModifier::DisplayArrowImpl,
        SwiperAttributeModifier::LoopImpl,
        SwiperAttributeModifier::DurationImpl,
        SwiperAttributeModifier::VerticalImpl,
        SwiperAttributeModifier::ItemSpaceImpl,
        SwiperAttributeModifier::DisplayModeImpl,
        SwiperAttributeModifier::CachedCountImpl,
        SwiperAttributeModifier::DisplayCountImpl,
        SwiperAttributeModifier::EffectModeImpl,
        SwiperAttributeModifier::DisableSwipeImpl,
        SwiperAttributeModifier::CurveImpl,
        SwiperAttributeModifier::OnChangeImpl,
        SwiperAttributeModifier::IndicatorStyleImpl,
        SwiperAttributeModifier::PrevMarginImpl,
        SwiperAttributeModifier::NextMarginImpl,
        SwiperAttributeModifier::OnAnimationStartImpl,
        SwiperAttributeModifier::OnAnimationEndImpl,
        SwiperAttributeModifier::OnGestureSwipeImpl,
        SwiperAttributeModifier::NestedScrollImpl,
        SwiperAttributeModifier::CustomContentTransitionImpl,
        SwiperAttributeModifier::OnContentDidScrollImpl,
        SwiperAttributeModifier::IndicatorInteractiveImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
