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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //TabsModelNG::SetSetTabsOptions(frameNode, convValue);
}
} // TabsInterfaceModifier
namespace TabsAttributeModifier {
void SetVerticalImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetVertical(frameNode, convValue);
}
void SetBarPositionImpl(Ark_NativePointer node,
                        const Opt_BarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarPosition(frameNode, convValue);
}
void SetScrollableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetScrollable(frameNode, convValue);
}
void SetBarWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarWidth(frameNode, convValue);
}
void SetBarHeightImpl(Ark_NativePointer node,
                      const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarHeight(frameNode, convValue);
}
void SetAnimationDurationImpl(Ark_NativePointer node,
                              const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetAnimationDuration(frameNode, convValue);
}
void SetAnimationModeImpl(Ark_NativePointer node,
                          const Opt_AnimationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetAnimationMode(frameNode, convValue);
}
void SetEdgeEffectImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetEdgeEffect(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnChange(frameNode, convValue);
}
void SetOnSelectedImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnSelected(frameNode, convValue);
}
void SetOnTabBarClickImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnTabBarClick(frameNode, convValue);
}
void SetOnUnselectedImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnUnselected(frameNode, convValue);
}
void SetOnAnimationStartImpl(Ark_NativePointer node,
                             const Opt_OnTabsAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnAnimationStart(frameNode, convValue);
}
void SetOnAnimationEndImpl(Ark_NativePointer node,
                           const Opt_OnTabsAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnAnimationEnd(frameNode, convValue);
}
void SetOnGestureSwipeImpl(Ark_NativePointer node,
                           const Opt_OnTabsGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnGestureSwipe(frameNode, convValue);
}
void SetFadingEdgeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetFadingEdge(frameNode, convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetDivider(frameNode, convValue);
}
void SetBarOverlapImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarOverlap(frameNode, convValue);
}
void SetBarBackgroundColorImpl(Ark_NativePointer node,
                               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarBackgroundColor(frameNode, convValue);
}
void SetBarGridAlignImpl(Ark_NativePointer node,
                         const Opt_BarGridColumnOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarGridAlign(frameNode, convValue);
}
void SetCustomContentTransitionImpl(Ark_NativePointer node,
                                    const Opt_TabsCustomContentTransitionCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetCustomContentTransition(frameNode, convValue);
}
void SetBarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                    const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarBackgroundBlurStyle0(frameNode, convValue);
}
void SetBarBackgroundEffectImpl(Ark_NativePointer node,
                                const Opt_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetBarBackgroundEffect(frameNode, convValue);
}
void SetPageFlipModeImpl(Ark_NativePointer node,
                         const Opt_PageFlipMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetPageFlipMode(frameNode, convValue);
}
void SetOnContentWillChangeImpl(Ark_NativePointer node,
                                const Opt_OnTabsContentWillChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TabsModelNG::SetSetOnContentWillChange(frameNode, convValue);
}
void SetBarModeImpl(Ark_NativePointer node,
                    const Opt_BarMode* value,
                    const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TabsModelNG::SetSetBarMode(frameNode, convValue);
}
void SetBarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                    const Opt_BlurStyle* style,
                                    const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(style);
    //auto convValue = Converter::OptConvert<type>(style); // for enums
    //TabsModelNG::SetSetBarBackgroundBlurStyle1(frameNode, convValue);
}
void SetCachedMaxCountImpl(Ark_NativePointer node,
                           const Opt_Number* count,
                           const Opt_TabsCacheMode* mode)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //TabsModelNG::SetSetCachedMaxCount(frameNode, convValue);
}
} // TabsAttributeModifier
const GENERATED_ArkUITabsModifier* GetTabsModifier()
{
    static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
        TabsModifier::ConstructImpl,
        TabsInterfaceModifier::SetTabsOptionsImpl,
        TabsAttributeModifier::SetVerticalImpl,
        TabsAttributeModifier::SetBarPositionImpl,
        TabsAttributeModifier::SetScrollableImpl,
        TabsAttributeModifier::SetBarWidthImpl,
        TabsAttributeModifier::SetBarHeightImpl,
        TabsAttributeModifier::SetAnimationDurationImpl,
        TabsAttributeModifier::SetAnimationModeImpl,
        TabsAttributeModifier::SetEdgeEffectImpl,
        TabsAttributeModifier::SetOnChangeImpl,
        TabsAttributeModifier::SetOnSelectedImpl,
        TabsAttributeModifier::SetOnTabBarClickImpl,
        TabsAttributeModifier::SetOnUnselectedImpl,
        TabsAttributeModifier::SetOnAnimationStartImpl,
        TabsAttributeModifier::SetOnAnimationEndImpl,
        TabsAttributeModifier::SetOnGestureSwipeImpl,
        TabsAttributeModifier::SetFadingEdgeImpl,
        TabsAttributeModifier::SetDividerImpl,
        TabsAttributeModifier::SetBarOverlapImpl,
        TabsAttributeModifier::SetBarBackgroundColorImpl,
        TabsAttributeModifier::SetBarGridAlignImpl,
        TabsAttributeModifier::SetCustomContentTransitionImpl,
        TabsAttributeModifier::SetBarBackgroundBlurStyle0Impl,
        TabsAttributeModifier::SetBarBackgroundEffectImpl,
        TabsAttributeModifier::SetPageFlipModeImpl,
        TabsAttributeModifier::SetOnContentWillChangeImpl,
        TabsAttributeModifier::SetBarModeImpl,
        TabsAttributeModifier::SetBarBackgroundBlurStyle1Impl,
        TabsAttributeModifier::SetCachedMaxCountImpl,
    };
    return &ArkUITabsModifierImpl;
}

}
