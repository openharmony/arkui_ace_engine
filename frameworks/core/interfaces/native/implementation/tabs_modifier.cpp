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

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/interfaces/native/implementation/tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/tab_content_transition_proxy_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "frameworks/base/utils/utils.h"

namespace OHOS::Ace::NG {
struct TabsOptions {
    std::optional<BarPosition> barPosOpt;
    std::optional<int32_t> indexOpt;
    std::optional<Ark_TabsController> controllerOpt;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
TabsItemDivider Convert(const Ark_DividerStyle& src)
{
    auto dst = TabsItemDivider{}; // this struct is initialized by default
    dst.strokeWidth = Convert<Dimension>(src.strokeWidth);
    auto colorOpt = OptConvert<Color>(src.color);
    if (colorOpt.has_value()) {
        dst.color = colorOpt.value();
    }
    auto startMarginOpt = OptConvert<Dimension>(src.startMargin);
    if (startMarginOpt.has_value()) {
        dst.startMargin = startMarginOpt.value();
    }
    auto endMarginOpt = OptConvert<Dimension>(src.endMargin);
    if (endMarginOpt.has_value()) {
        dst.endMargin = endMarginOpt.value();
    }
    return dst;
}

constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t EVEN_NUM = 2;
template<>
BarGridColumnOptions Convert(const Ark_BarGridColumnOptions& src)
{
    auto dst = BarGridColumnOptions{}; // this struct is initialized by default
    auto smOpt = OptConvert<int32_t>(src.sm);
    if (smOpt.has_value() && (smOpt.value() >= 0) && (smOpt.value() <= SM_COLUMN_NUM) &&
        (smOpt.value() % EVEN_NUM == 0)) {
        dst.sm = smOpt.value();
    }
    auto mdOpt = OptConvert<int32_t>(src.md);
    if (mdOpt.has_value() && (mdOpt.value() >= 0) && (mdOpt.value() <= MD_COLUMN_NUM) &&
        (mdOpt.value() % EVEN_NUM == 0)) {
        dst.md = mdOpt.value();
    }
    auto lgOpt = OptConvert<int32_t>(src.lg);
    if (lgOpt.has_value() && (lgOpt.value() >= 0) && (lgOpt.value() <= LG_COLUMN_NUM) &&
        (lgOpt.value() % EVEN_NUM == 0)) {
        dst.lg = lgOpt.value();
    }
    auto marginOpt = OptConvert<Dimension>(src.margin);
    Validator::ValidateNonNegative(marginOpt);
    Validator::ValidateNonPercent(marginOpt);
    if (marginOpt.has_value()) {
        dst.margin = marginOpt.value();
    }
    auto gutterOpt = OptConvert<Dimension>(src.gutter);
    Validator::ValidateNonNegative(gutterOpt);
    Validator::ValidateNonPercent(gutterOpt);
    if (gutterOpt.has_value()) {
        dst.gutter = gutterOpt.value();
    }
    return dst;
}

template<>
GeneratedModifier::TabsControllerPeerImpl* Convert(const Ark_Materialized &src)
{
    return reinterpret_cast<GeneratedModifier::TabsControllerPeerImpl *>(src.ptr);
}

template<>
TabsOptions Convert(const Ark_TabsOptions& src)
{
    return {
        .barPosOpt = OptConvert<BarPosition>(src.barPosition),
        .indexOpt = OptConvert<int32_t>(src.index),
        .controllerOpt = OptConvert<Ark_TabsController>(src.controller),
    };
}

template<>
void AssignTo(std::optional<TabContentAnimatedTransition>& dst, const Opt_TabContentAnimatedTransition& from)
{
    TabContentAnimatedTransition ret;
    ret.timeout = Converter::OptConvert<int32_t>(from.value.timeout).value_or(0);
    dst = ret;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor();
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabsModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TabsModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TabsModifier
namespace TabsInterfaceModifier {
void SetTabsOptionsImpl(Ark_NativePointer node,
                        const Opt_TabsOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto tabsOptionsOpt = Converter::OptConvert<TabsOptions>(*options);
    CHECK_NULL_VOID(tabsOptionsOpt);
    // need check
    // TabsModelNG::SetTabBarPosition(frameNode, tabsOptionsOpt->barPosOpt);

    // TabsModelNG::InitIndex(frameNode, tabsOptionsOpt->indexOpt);

    if (tabsOptionsOpt->controllerOpt) {
        // obtain the external TabController peer
        if (auto peerImplPtr = *(tabsOptionsOpt->controllerOpt); peerImplPtr) {
            // obtain the internal SwiperController
            // need check
            // auto internalSwiperController = TabsModelNG::GetSwiperController(frameNode);
            // // pass the internal controller to external management
            // peerImplPtr->SetTargetController(internalSwiperController);
        }
    }
}
} // TabsInterfaceModifier
namespace TabsAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, Converter::Convert<bool>(value));
}
void BarPositionImpl(Ark_NativePointer node,
                     Ark_BarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // need check
    // TabsModelNG::SetTabBarPosition(frameNode, Converter::OptConvert<BarPosition>(value));
}
void ScrollableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, Converter::Convert<bool>(value));
}
void BarMode1Impl(Ark_NativePointer node, Ark_BarMode value, const Opt_ScrollableBarModeOptions* options);
void BarMode0Impl(Ark_NativePointer node,
                  Ark_BarMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BarMode1Impl(node, ARK_BAR_MODE_FIXED, nullptr);
}
void BarMode1Impl(Ark_NativePointer node,
                  Ark_BarMode value,
                  const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
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
                // barModeOptions.nonScrollableLayoutStyle = styleOpt.value_or(defaultStyle);
            }
        }
        TabsModelNG::SetScrollableBarModeOptions(frameNode, barModeOptions);
    }
    // need check
    // TabsModelNG::SetTabBarMode(frameNode, Converter::OptConvert<TabBarMode>(value));
}
void BarWidthImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    // need check
    // TabsModelNG::SetTabBarWidth(frameNode, valueOpt);
}
void BarHeightImpl(Ark_NativePointer node,
                   const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    // need check
    // TabsModelNG::SetTabBarHeight(frameNode, valueOpt);
}
void AnimationDurationImpl(Ark_NativePointer node,
                           const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TabsModelNG::SetAnimationDuration(frameNode, Converter::Convert<float>(*value));
}
void AnimationModeImpl(Ark_NativePointer node,
                       const Opt_AnimationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // need check
    // TabsModelNG::SetAnimateMode(frameNode, Converter::OptConvert<TabAnimateMode>(*value));
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto edgeEffectOpt = Converter::OptConvert<EdgeEffect>(*value);
    // need check
    // TabsModelNG::SetEdgeEffect(frameNode, OHOS::Ace::NG::EnumToInt(edgeEffectOpt));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        arkCallback.Invoke(index);
    };
    TabsModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTabBarClickImpl(Ark_NativePointer node,
                       const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTabBarClick = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        arkCallback.Invoke(index);
    };
    TabsModelNG::SetOnTabBarClick(frameNode, std::move(onTabBarClick));
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const OnTabsAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onAnimationStart = [arkCallback = CallbackHelper(*value)](
        int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkTargetIndex = Converter::ArkValue<Ark_Number>(targetIndex);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, arkTargetIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnAnimationStart(frameNode, std::move(onAnimationStart));
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const OnTabsAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onAnimationEnd = [arkCallback = CallbackHelper(*value)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnAnimationEnd(frameNode, std::move(onAnimationEnd));
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const OnTabsGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onGestureSwipe = [arkCallback = CallbackHelper(*value)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, tabsAnimationEvent);
    };
    TabsModelNG::SetOnGestureSwipe(frameNode, std::move(onGestureSwipe));
}
void FadingEdgeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, Converter::Convert<bool>(value));
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<TabsItemDivider>(*value);
    // need check
    // TabsModelNG::SetDivider(frameNode, divider);
}
void BarOverlapImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, Converter::Convert<bool>(value));
}
void BarBackgroundColorImpl(Ark_NativePointer node,
                            const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // need check
    // TabsModelNG::SetBarBackgroundColor(frameNode,  Converter::OptConvert<Color>(*value));
}
void BarGridAlignImpl(Ark_NativePointer node,
                      const Ark_BarGridColumnOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TabsModelNG::SetBarGridAlign(frameNode, Converter::Convert<BarGridColumnOptions>(*value));
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const TabsCustomContentTransitionCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto accessor = GetTabContentTransitionProxyAccessor();
    CHECK_NULL_VOID(accessor && accessor->ctor);
    auto peer = (*accessor->ctor)();
    CHECK_NULL_VOID(peer);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::TabContentTransitionProxyPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImplPtr);

    RefPtr<TabContentTransitionProxy> internalController;
    internalController = new TabContentTransitionProxy();
    CHECK_NULL_VOID(internalController);
    peerImplPtr->AddTargetController(internalController);

    auto onCustomAnimation = [callback = CallbackHelper(*value), peerImplPtr](
        int32_t from, int32_t to) -> TabContentAnimatedTransition {
        peerImplPtr->SetFrom(from);
        peerImplPtr->SetTo(to);
        TabContentAnimatedTransition result;
        Ark_Number arkFrom = Converter::ArkValue<Ark_Number>(from);
        Ark_Number arkTo = Converter::ArkValue<Ark_Number>(to);
        return callback.InvokeWithOptConvertResult<
            TabContentAnimatedTransition, Opt_TabContentAnimatedTransition,
            Callback_Opt_TabContentAnimatedTransition_Void>(arkFrom, arkTo)
            .value_or(result);
        };
    TabsModelNG::SetIsCustomAnimation(frameNode, true); //Set 'true' to any cases. It is wrong behavior.
    // need check
    // TabsModelNG::SetOnCustomAnimation(frameNode, std::move(onCustomAnimation));
}
void BarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                 Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(value);
    if (blurStyle) {
        option.blurStyle = blurStyle.value();
    }
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, option);
}
void BarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                 Ark_BlurStyle style,
                                 const Ark_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto option = Converter::Convert<BlurStyleOption>(*options);
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, option);
}
void BarBackgroundEffectImpl(Ark_NativePointer node,
                             const Ark_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<EffectOption>(*value);
    TabsModelNG::SetBarBackgroundEffect(frameNode, options);
}
void OnContentWillChangeImpl(Ark_NativePointer node,
                             const OnTabsContentWillChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto callback = [callback = CallbackHelper(*value)](
        int32_t currentIndex, int32_t comingIndex) -> bool {
        Ark_Number arkCurrentIndex = Converter::ArkValue<Ark_Number>(currentIndex);
        Ark_Number arkComingIndex = Converter::ArkValue<Ark_Number>(comingIndex);
        return callback.InvokeWithOptConvertResult<
            bool, Ark_Boolean, Callback_Boolean_Void>(arkCurrentIndex, arkComingIndex)
            .value_or(false);
    };
    TabsModelNG::SetOnContentWillChange(frameNode, std::move(callback));
}
void BarModeScrollableImpl(Ark_NativePointer node,
                           const Ark_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    if (options) {
        auto optOptions = Converter::ArkValue<Opt_ScrollableBarModeOptions>(*options);
        BarMode1Impl(node, ARK_BAR_MODE_SCROLLABLE, &optOptions);
    } else {
        BarMode1Impl(node, ARK_BAR_MODE_SCROLLABLE, nullptr);
    }
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        CHECK_NULL_VOID(tabsInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(tabsInfo->GetIndex()));
    };
    // need check
    // TabsModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
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
        TabsAttributeModifier::BarBackgroundBlurStyle0Impl,
        TabsAttributeModifier::BarBackgroundBlurStyle1Impl,
        TabsAttributeModifier::BarBackgroundEffectImpl,
        TabsAttributeModifier::OnContentWillChangeImpl,
        TabsAttributeModifier::BarModeScrollableImpl,
        TabsAttributeModifier::_onChangeEvent_indexImpl,
    };
    return &ArkUITabsModifierImpl;
}

}
