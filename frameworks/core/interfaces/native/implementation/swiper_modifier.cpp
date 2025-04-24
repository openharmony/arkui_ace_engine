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
namespace SwiperModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // SwiperModifier
namespace SwiperInterfaceModifier {
void SetSwiperOptionsImpl(Ark_NativePointer node,
                          const Opt_SwiperController* controller)
{
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void IndexImpl(Ark_NativePointer node,
               const Opt_Number* value)
{
}
void AutoPlay0Impl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void AutoPlay1Impl(Ark_NativePointer node,
                   const Opt_Boolean* autoPlay,
                   const Opt_AutoPlayOptions* options)
{
}
void IntervalImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void Indicator0Impl(Ark_NativePointer node,
                    const Opt_Union_DotIndicator_DigitIndicator_Boolean* value)
{
}
void Indicator1Impl(Ark_NativePointer node,
                    const Opt_Type_SwiperAttribute_indicator_indicator* value)
{
}
void LoopImpl(Ark_NativePointer node,
              const Opt_Boolean* value)
{
}
void DurationImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void ItemSpaceImpl(Ark_NativePointer node,
                   const Opt_Union_Number_String* value)
{
}
void DisplayModeImpl(Ark_NativePointer node,
                     const Opt_SwiperDisplayMode* value)
{
}
void CachedCount0Impl(Ark_NativePointer node,
                      const Opt_Number* value)
{
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* isShown)
{
}
void EffectModeImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value)
{
}
void DisableSwipeImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void CurveImpl(Ark_NativePointer node,
               const Opt_Union_Curve_String_ICurve* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Void* value)
{
}
void OnSelectedImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Void* value)
{
}
void IndicatorStyleImpl(Ark_NativePointer node,
                        const Opt_IndicatorStyle* value)
{
}
void OnUnselectedImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const Opt_OnSwiperAnimationStartCallback* value)
{
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const Opt_OnSwiperAnimationEndCallback* value)
{
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const Opt_OnSwiperGestureSwipeCallback* value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_SwiperNestedScrollMode* value)
{
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Opt_SwiperContentAnimatedTransition* value)
{
}
void OnContentDidScrollImpl(Ark_NativePointer node,
                            const Opt_ContentDidScrollCallback* value)
{
}
void IndicatorInteractiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void PageFlipModeImpl(Ark_NativePointer node,
                      const Opt_PageFlipMode* value)
{
}
void OnContentWillScrollImpl(Ark_NativePointer node,
                             const Opt_ContentWillScrollCallback* value)
{
}
void DisplayArrowImpl(Ark_NativePointer node,
                      const Opt_Union_ArrowStyle_Boolean* value,
                      const Opt_Boolean* isHoverShow)
{
}
void DisplayCountImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String_SwiperAutoFill* value,
                      const Opt_Boolean* swipeByGroup)
{
}
void PrevMarginImpl(Ark_NativePointer node,
                    const Opt_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
}
void NextMarginImpl(Ark_NativePointer node,
                    const Opt_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Opt_Number_Void* callback)
{
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperModifier::ConstructImpl,
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::IndexImpl,
        SwiperAttributeModifier::AutoPlay0Impl,
        SwiperAttributeModifier::AutoPlay1Impl,
        SwiperAttributeModifier::IntervalImpl,
        SwiperAttributeModifier::Indicator0Impl,
        SwiperAttributeModifier::Indicator1Impl,
        SwiperAttributeModifier::LoopImpl,
        SwiperAttributeModifier::DurationImpl,
        SwiperAttributeModifier::VerticalImpl,
        SwiperAttributeModifier::ItemSpaceImpl,
        SwiperAttributeModifier::DisplayModeImpl,
        SwiperAttributeModifier::CachedCount0Impl,
        SwiperAttributeModifier::CachedCount1Impl,
        SwiperAttributeModifier::EffectModeImpl,
        SwiperAttributeModifier::DisableSwipeImpl,
        SwiperAttributeModifier::CurveImpl,
        SwiperAttributeModifier::OnChangeImpl,
        SwiperAttributeModifier::OnSelectedImpl,
        SwiperAttributeModifier::IndicatorStyleImpl,
        SwiperAttributeModifier::OnUnselectedImpl,
        SwiperAttributeModifier::OnAnimationStartImpl,
        SwiperAttributeModifier::OnAnimationEndImpl,
        SwiperAttributeModifier::OnGestureSwipeImpl,
        SwiperAttributeModifier::NestedScrollImpl,
        SwiperAttributeModifier::CustomContentTransitionImpl,
        SwiperAttributeModifier::OnContentDidScrollImpl,
        SwiperAttributeModifier::IndicatorInteractiveImpl,
        SwiperAttributeModifier::PageFlipModeImpl,
        SwiperAttributeModifier::OnContentWillScrollImpl,
        SwiperAttributeModifier::DisplayArrowImpl,
        SwiperAttributeModifier::DisplayCountImpl,
        SwiperAttributeModifier::PrevMarginImpl,
        SwiperAttributeModifier::NextMarginImpl,
        SwiperAttributeModifier::_onChangeEvent_indexImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
