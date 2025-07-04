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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = controller ? Converter::OptConvert<type>(*controller) : std::nullopt;
    //SwiperModelNG::SetSetSwiperOptions(frameNode, convValue);
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void SetIndexImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetIndex(frameNode, convValue);
}
void SetIntervalImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetInterval(frameNode, convValue);
}
void SetIndicatorImpl(Ark_NativePointer node,
                      const Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetIndicator(frameNode, convValue);
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetLoop(frameNode, convValue);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetDuration(frameNode, convValue);
}
void SetVerticalImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetVertical(frameNode, convValue);
}
void SetItemSpaceImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetItemSpace(frameNode, convValue);
}
void SetDisplayModeImpl(Ark_NativePointer node,
                        const Opt_SwiperDisplayMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetDisplayMode(frameNode, convValue);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetCachedCount0(frameNode, convValue);
}
void SetEffectModeImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetEffectMode(frameNode, convValue);
}
void SetDisableSwipeImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetDisableSwipe(frameNode, convValue);
}
void SetCurveImpl(Ark_NativePointer node,
                  const Opt_Union_Curve_String_ICurve* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetCurve(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnChange(frameNode, convValue);
}
void SetOnSelectedImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnSelected(frameNode, convValue);
}
void SetOnUnselectedImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnUnselected(frameNode, convValue);
}
void SetOnAnimationStartImpl(Ark_NativePointer node,
                             const Opt_OnSwiperAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnAnimationStart(frameNode, convValue);
}
void SetOnAnimationEndImpl(Ark_NativePointer node,
                           const Opt_OnSwiperAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnAnimationEnd(frameNode, convValue);
}
void SetOnGestureSwipeImpl(Ark_NativePointer node,
                           const Opt_OnSwiperGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnGestureSwipe(frameNode, convValue);
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_SwiperNestedScrollMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetNestedScroll(frameNode, convValue);
}
void SetCustomContentTransitionImpl(Ark_NativePointer node,
                                    const Opt_SwiperContentAnimatedTransition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetCustomContentTransition(frameNode, convValue);
}
void SetOnContentDidScrollImpl(Ark_NativePointer node,
                               const Opt_ContentDidScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnContentDidScroll(frameNode, convValue);
}
void SetIndicatorInteractiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetIndicatorInteractive(frameNode, convValue);
}
void SetPageFlipModeImpl(Ark_NativePointer node,
                         const Opt_PageFlipMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetPageFlipMode(frameNode, convValue);
}
void SetOnContentWillScrollImpl(Ark_NativePointer node,
                                const Opt_ContentWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnContentWillScroll(frameNode, convValue);
}
void SetAutoPlayImpl(Ark_NativePointer node,
                     const Opt_Boolean* autoPlay,
                     const Opt_AutoPlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(autoPlay);
    //auto convValue = Converter::OptConvert<type>(autoPlay); // for enums
    //SwiperModelNG::SetSetAutoPlay(frameNode, convValue);
}
void SetDisplayArrowImpl(Ark_NativePointer node,
                         const Opt_Union_ArrowStyle_Boolean* value,
                         const Opt_Boolean* isHoverShow)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetSetDisplayArrow(frameNode, convValue);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Number* count,
                         const Opt_Boolean* isShown)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //SwiperModelNG::SetSetCachedCount1(frameNode, convValue);
}
void SetDisplayCountImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_SwiperAutoFill* value,
                         const Opt_Boolean* swipeByGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetSetDisplayCount(frameNode, convValue);
}
void SetPrevMarginImpl(Ark_NativePointer node,
                       const Opt_Length* value,
                       const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetSetPrevMargin(frameNode, convValue);
}
void SetNextMarginImpl(Ark_NativePointer node,
                       const Opt_Length* value,
                       const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetSetNextMargin(frameNode, convValue);
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperModifier::ConstructImpl,
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::SetIndexImpl,
        SwiperAttributeModifier::SetIntervalImpl,
        SwiperAttributeModifier::SetIndicatorImpl,
        SwiperAttributeModifier::SetLoopImpl,
        SwiperAttributeModifier::SetDurationImpl,
        SwiperAttributeModifier::SetVerticalImpl,
        SwiperAttributeModifier::SetItemSpaceImpl,
        SwiperAttributeModifier::SetDisplayModeImpl,
        SwiperAttributeModifier::SetCachedCount0Impl,
        SwiperAttributeModifier::SetEffectModeImpl,
        SwiperAttributeModifier::SetDisableSwipeImpl,
        SwiperAttributeModifier::SetCurveImpl,
        SwiperAttributeModifier::SetOnChangeImpl,
        SwiperAttributeModifier::SetOnSelectedImpl,
        SwiperAttributeModifier::SetOnUnselectedImpl,
        SwiperAttributeModifier::SetOnAnimationStartImpl,
        SwiperAttributeModifier::SetOnAnimationEndImpl,
        SwiperAttributeModifier::SetOnGestureSwipeImpl,
        SwiperAttributeModifier::SetNestedScrollImpl,
        SwiperAttributeModifier::SetCustomContentTransitionImpl,
        SwiperAttributeModifier::SetOnContentDidScrollImpl,
        SwiperAttributeModifier::SetIndicatorInteractiveImpl,
        SwiperAttributeModifier::SetPageFlipModeImpl,
        SwiperAttributeModifier::SetOnContentWillScrollImpl,
        SwiperAttributeModifier::SetAutoPlayImpl,
        SwiperAttributeModifier::SetDisplayArrowImpl,
        SwiperAttributeModifier::SetCachedCount1Impl,
        SwiperAttributeModifier::SetDisplayCountImpl,
        SwiperAttributeModifier::SetPrevMarginImpl,
        SwiperAttributeModifier::SetNextMarginImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
