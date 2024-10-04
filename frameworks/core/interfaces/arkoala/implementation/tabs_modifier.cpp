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

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/interfaces/arkoala/utility/validators.h"

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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, Converter::Convert<bool>(value));
}
void BarPositionImpl(Ark_NativePointer node,
                     enum Ark_BarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, Converter::OptConvert<BarPosition>(value));
}
void ScrollableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, Converter::Convert<bool>(value));
}
void BarMode2Impl(Ark_NativePointer node, Ark_BarMode value, const Opt_ScrollableBarModeOptions* options);
void BarMode0Impl(Ark_NativePointer node,
                  enum Ark_BarMode value)
{
    BarMode2Impl(node, ARK_BAR_MODE_FIXED, nullptr);
}
void BarMode1Impl(Ark_NativePointer node,
                  enum Ark_BarMode value,
                  const Ark_ScrollableBarModeOptions* options)
{
    if (options) {
        auto optionsOpt = Converter::ArkValue<Opt_ScrollableBarModeOptions>(*options);
        BarMode2Impl(node, ARK_BAR_MODE_SCROLLABLE, &optionsOpt);
    } else {
        BarMode2Impl(node, ARK_BAR_MODE_SCROLLABLE, nullptr);
    }
}
void BarMode2Impl(Ark_NativePointer node,
                  enum Ark_BarMode value,
                  const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value == ARK_BAR_MODE_SCROLLABLE) {
        ScrollableBarModeOptions barModeOptions;
        auto defaultMargin = barModeOptions.margin;
        auto defaultStyle = barModeOptions.nonScrollableLayoutStyle;
        if (options) {
            auto optionsOpt = Converter::OptConvert<Ark_ScrollableBarModeOptions>(*options);
            if (optionsOpt) {
                auto marginOpt = Converter::OptConvert<Dimension>(optionsOpt.value().margin);
                Validator::ValidateNonPercent(marginOpt);
                auto styleOpt = Converter::OptConvert<LayoutStyle>(optionsOpt.value().nonScrollableLayoutStyle);
                barModeOptions.margin = marginOpt.value_or(defaultMargin);
                barModeOptions.nonScrollableLayoutStyle = styleOpt.value_or(defaultStyle);
            }
        }
        TabsModelNG::SetScrollableBarModeOptions(frameNode, barModeOptions);
    }
    TabsModelNG::SetTabBarMode(frameNode, Converter::OptConvert<TabBarMode>(value));
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TabsModelNG::SetAnimationDuration(frameNode, Converter::Convert<float>(*value));
}
void AnimationModeImpl(Ark_NativePointer node,
                       const Opt_AnimationMode* mode)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(mode);
    TabsModelNG::SetAnimateMode(frameNode, Converter::OptConvert<TabAnimateMode>(*mode));
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* edgeEffect)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(edgeEffect);
    auto edgeEffectOpt = Converter::OptConvert<EdgeEffect>(*edgeEffect);
    TabsModelNG::SetEdgeEffect(frameNode, OHOS::Ace::NG::EnumToInt(edgeEffectOpt));
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [frameNode](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onChange(frameNode->GetId(), index);
    };
    TabsModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTabBarClickImpl(Ark_NativePointer node,
                       Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onTabBarClick = [frameNode](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onTabBarClick(frameNode->GetId(), index);
    };
    TabsModelNG::SetOnTabBarClick(frameNode, std::move(onTabBarClick));
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          Ark_Function handler)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onAnimationStart = [frameNode](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkTargetIndex = Converter::ArkValue<Ark_Number>(targetIndex);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));

        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onAnimationStart(frameNode->GetId(),
            arkIndex, arkTargetIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnAnimationStart(frameNode, std::move(onAnimationStart));
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        Ark_Function handler)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onAnimationEnd = [frameNode](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));

        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onAnimationEnd(frameNode->GetId(),
            arkIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnAnimationEnd(frameNode, std::move(onAnimationEnd));
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        Ark_Function handler)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onGestureSwipe = [frameNode](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));

        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onGestureSwipe(frameNode->GetId(),
            arkIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnGestureSwipe(frameNode, std::move(onGestureSwipe));
}
void FadingEdgeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, Converter::Convert<bool>(value));
}
void DividerImpl(Ark_NativePointer node,
                 const Type_TabsAttribute_divider_Arg0* value)
{
}
void BarOverlapImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, Converter::Convert<bool>(value));
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCustomAnimation = [frameNode](int32_t from, int32_t to) {
        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->customContentTransition(frameNode->GetId(),
            Converter::ArkValue<Ark_Number>(from), Converter::ArkValue<Ark_Number>(to));
        TabContentAnimatedTransition result;
        LOGE("ARKOALA TabsAttributeModifier.customContentTransition -> Method work incorrect.");
        return result;  // wrong result!!!
    };
    TabsModelNG::SetIsCustomAnimation(frameNode, true); //Set 'true' to any cases. It is wrong behavior.
    TabsModelNG::SetOnCustomAnimation(frameNode, std::move(onCustomAnimation));
}
void BarBackgroundBlurStyleImpl(Ark_NativePointer node,
                                enum Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, Converter::OptConvert<BlurStyle>(value));
}
void OnContentWillChangeImpl(Ark_NativePointer node,
                             Ark_Function handler)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto callback = [frameNode](int32_t currentIndex, int32_t comingIndex) {
        GetFullAPI()->getEventsAPI()->getTabsEventsReceiver()->onContentWillChange(frameNode->GetId(),
            Converter::ArkValue<Ark_Number>(currentIndex), Converter::ArkValue<Ark_Number>(comingIndex));
        LOGE("ARKOALA TabsAttributeModifier.onContentWillChange -> Method work incorrect.");
        return true; // wrong result!!!
    };
    TabsModelNG::SetOnContentWillChange(frameNode, std::move(callback));
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
