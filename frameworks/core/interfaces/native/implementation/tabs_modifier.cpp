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
namespace TabsModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TabsModifier
namespace TabsInterfaceModifier {
void SetTabsOptionsImpl(Ark_NativePointer node,
                        const Opt_TabsOptions* options)
{
}
} // TabsInterfaceModifier
namespace TabsAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void BarPositionImpl(Ark_NativePointer node,
                     const Opt_BarPosition* value)
{
}
void ScrollableImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void BarMode0Impl(Ark_NativePointer node,
                  const Opt_BarMode* value)
{
}
void BarMode1Impl(Ark_NativePointer node,
                  const Opt_BarMode* value,
                  const Opt_ScrollableBarModeOptions* options)
{
}
void BarWidthImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void BarHeightImpl(Ark_NativePointer node,
                   const Opt_Length* value)
{
}
void AnimationDurationImpl(Ark_NativePointer node,
                           const Opt_Number* value)
{
}
void AnimationModeImpl(Ark_NativePointer node,
                       const Opt_AnimationMode* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value)
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
void OnTabBarClickImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Void* value)
{
}
void OnUnselectedImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const Opt_OnTabsAnimationStartCallback* value)
{
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const Opt_OnTabsAnimationEndCallback* value)
{
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const Opt_OnTabsGestureSwipeCallback* value)
{
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerStyle* value)
{
}
void BarOverlapImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void BarBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
}
void BarGridAlignImpl(Ark_NativePointer node,
                      const Opt_BarGridColumnOptions* value)
{
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Opt_TabsCustomContentTransitionCallback* value)
{
}
void BarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                 const Opt_BlurStyle* value)
{
}
void BarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                 const Opt_BlurStyle* style,
                                 const Opt_BackgroundBlurStyleOptions* options)
{
}
void BarBackgroundEffectImpl(Ark_NativePointer node,
                             const Opt_BackgroundEffectOptions* value)
{
}
void PageFlipModeImpl(Ark_NativePointer node,
                      const Opt_PageFlipMode* value)
{
}
void OnContentWillChangeImpl(Ark_NativePointer node,
                             const Opt_OnTabsContentWillChangeCallback* value)
{
}
void BarModeScrollableImpl(Ark_NativePointer node,
                           const Opt_ScrollableBarModeOptions* options)
{
}
void CachedMaxCountImpl(Ark_NativePointer node,
                        const Opt_Number* count,
                        const Opt_TabsCacheMode* mode)
{
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
}
} // TabsAttributeModifier
const GENERATED_ArkUITabsModifier* GetTabsModifier()
{
    static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
        TabsModifier::ConstructImpl,
        TabsInterfaceModifier::SetTabsOptionsImpl,
        TabsAttributeModifier::VerticalImpl,
        TabsAttributeModifier::BarPositionImpl,
        TabsAttributeModifier::ScrollableImpl,
        TabsAttributeModifier::BarMode0Impl,
        TabsAttributeModifier::BarMode1Impl,
        TabsAttributeModifier::BarWidthImpl,
        TabsAttributeModifier::BarHeightImpl,
        TabsAttributeModifier::AnimationDurationImpl,
        TabsAttributeModifier::AnimationModeImpl,
        TabsAttributeModifier::EdgeEffectImpl,
        TabsAttributeModifier::OnChangeImpl,
        TabsAttributeModifier::OnSelectedImpl,
        TabsAttributeModifier::OnTabBarClickImpl,
        TabsAttributeModifier::OnUnselectedImpl,
        TabsAttributeModifier::OnAnimationStartImpl,
        TabsAttributeModifier::OnAnimationEndImpl,
        TabsAttributeModifier::OnGestureSwipeImpl,
        TabsAttributeModifier::FadingEdgeImpl,
        TabsAttributeModifier::DividerImpl,
        TabsAttributeModifier::BarOverlapImpl,
        TabsAttributeModifier::BarBackgroundColorImpl,
        TabsAttributeModifier::BarGridAlignImpl,
        TabsAttributeModifier::CustomContentTransitionImpl,
        TabsAttributeModifier::BarBackgroundBlurStyle0Impl,
        TabsAttributeModifier::BarBackgroundBlurStyle1Impl,
        TabsAttributeModifier::BarBackgroundEffectImpl,
        TabsAttributeModifier::PageFlipModeImpl,
        TabsAttributeModifier::OnContentWillChangeImpl,
        TabsAttributeModifier::BarModeScrollableImpl,
        TabsAttributeModifier::CachedMaxCountImpl,
        TabsAttributeModifier::_onChangeEvent_indexImpl,
    };
    return &ArkUITabsModifierImpl;
}

}
