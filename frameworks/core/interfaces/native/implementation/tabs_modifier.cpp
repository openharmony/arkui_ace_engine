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

#include "core/components_ng/pattern/tabs/tabs_model_static.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/implementation/tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/tab_content_transition_proxy_peer_impl.h"
#include "core/interfaces/native/implementation/tab_content_transition_proxy_peer.h"
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

template<>
void AssignCast(std::optional<TabsCacheMode>& dst, const Ark_TabsCacheMode& src)
{
    switch (src) {
        case ARK_TABS_CACHE_MODE_CACHE_BOTH_SIDE: dst = TabsCacheMode::CACHE_BOTH_SIDE; break;
        case ARK_TABS_CACHE_MODE_CACHE_LATEST_SWITCHED: dst = TabsCacheMode::CACHE_LATEST_SWITCHED; break;
        default: LOGE("Unexpected enum value in Ark_TabsCacheMode: %{public}d", src);
    }
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
    auto frameNode = TabsModelStatic::CreateFrameNode(id);
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
    TabsModelStatic::SetTabBarPosition(frameNode, tabsOptionsOpt->barPosOpt);
    TabsModelStatic::InitIndex(frameNode, tabsOptionsOpt->indexOpt);

    if (tabsOptionsOpt->controllerOpt) {
        // obtain the external TabController peer
        if (auto peerImplPtr = *(tabsOptionsOpt->controllerOpt); peerImplPtr) {
            // obtain the internal SwiperController
            auto internalSwiperController = TabsModelStatic::GetSwiperController(frameNode);
            // pass the internal controller to external management
            peerImplPtr->SetTargetController(internalSwiperController);
        }
    }
}
} // TabsInterfaceModifier
namespace TabsAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        TabsModelStatic::SetIsVertical(frameNode, false);
        return;
    }
    TabsModelStatic::SetIsVertical(frameNode, *convValue);
}
void BarPositionImpl(Ark_NativePointer node,
                     const Opt_BarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelStatic::SetTabBarPosition(frameNode, Converter::OptConvert<BarPosition>(*value));
}
void ScrollableImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        TabsModelStatic::SetScrollable(frameNode, true);
        return;
    }
    TabsModelStatic::SetScrollable(frameNode, *convValue);
}
void BarMode1Impl(Ark_NativePointer node, const Opt_BarMode *value, const Opt_ScrollableBarModeOptions* options);
void BarMode0Impl(Ark_NativePointer node,
                  const Opt_BarMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BarMode1Impl(node, value, nullptr);
}
void BarMode1Impl(Ark_NativePointer node,
                  const Opt_BarMode* value,
                  const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::OptConvert<TabBarMode>(*value);
    if (mode && *mode == TabBarMode::SCROLLABLE) {
        ScrollableBarModeOptions barModeOptions;
        auto defaultMargin = barModeOptions.margin;
        if (options) {
            auto optionsOpt = Converter::OptConvert<Ark_ScrollableBarModeOptions>(*options);
            if (optionsOpt) {
                auto marginOpt = Converter::OptConvert<Dimension>(optionsOpt.value().margin);
                Validator::ValidateNonPercent(marginOpt);
                auto styleOpt = Converter::OptConvert<LayoutStyle>(optionsOpt.value().nonScrollableLayoutStyle);
                barModeOptions.margin = marginOpt.value_or(defaultMargin);
                barModeOptions.nonScrollableLayoutStyle = styleOpt;
            }
        }
        TabsModelStatic::SetScrollableBarModeOptions(frameNode, barModeOptions);
    }
    TabsModelStatic::SetTabBarMode(frameNode, mode);
}
void BarWidthImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    TabsModelStatic::SetTabBarWidth(frameNode, valueOpt);
}
void BarHeightImpl(Ark_NativePointer node,
                   const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    TabsModelStatic::SetTabBarHeight(frameNode, valueOpt);
}
void AnimationDurationImpl(Ark_NativePointer node,
                           const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    if (!convValue) {
        TabsModelStatic::SetAnimationDuration(frameNode, -1);
        return;
    }
    TabsModelStatic::SetAnimationDuration(frameNode, *convValue);
}
void AnimationModeImpl(Ark_NativePointer node,
                       const Opt_AnimationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TabsModelStatic::SetAnimateMode(frameNode, Converter::OptConvert<TabAnimateMode>(*value));
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto edgeEffectOpt = Converter::OptConvert<EdgeEffect>(*value);
    TabsModelStatic::SetEdgeEffect(frameNode, OHOS::Ace::NG::EnumToInt(edgeEffectOpt));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        arkCallback.Invoke(index);
    };
    TabsModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void OnSelectedImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnSelected(frameNode, nullptr);
        return;
    }
    auto onSelected = [arkCallback = CallbackHelper(*optValue), node = AceType::WeakClaim(frameNode)](
        const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("Tabs onSelected callback execute failed.");
            return;
        }
        PipelineContext::SetCallBackNode(node);
        auto index = Converter::ArkValue<Ark_Number>(tabsInfo->GetIndex());
        arkCallback.Invoke(index);
    };
    TabsModelStatic::SetOnSelected(frameNode, std::move(onSelected));
}
void OnTabBarClickImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnTabBarClick(frameNode, nullptr);
        return;
    }
    auto onTabBarClick = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        int32_t indexInt = -1;
        if (tabsInfo) {
            indexInt = tabsInfo->GetIndex();
        }
        auto index = Converter::ArkValue<Ark_Number>(indexInt);
        arkCallback.Invoke(index);
    };
    TabsModelStatic::SetOnTabBarClick(frameNode, std::move(onTabBarClick));
}
void OnUnselectedImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnUnselected(frameNode, nullptr);
        return;
    }
    auto onUnselected = [arkCallback = CallbackHelper(*optValue), node = AceType::WeakClaim(frameNode)](
        const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("Tabs onUnselected callback execute failed.");
            return;
        }
        PipelineContext::SetCallBackNode(node);
        auto index = Converter::ArkValue<Ark_Number>(tabsInfo->GetIndex());
        arkCallback.Invoke(index);
    };
    TabsModelStatic::SetOnUnselected(frameNode, std::move(onUnselected));
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const Opt_OnTabsAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnAnimationStart(frameNode, nullptr);
        return;
    }
    auto onAnimationStart = [arkCallback = CallbackHelper(*optValue)](
        int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkTargetIndex = Converter::ArkValue<Ark_Number>(targetIndex);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, arkTargetIndex, tabsAnimationEvent);
    };
    TabsModelStatic::SetOnAnimationStart(frameNode, std::move(onAnimationStart));
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const Opt_OnTabsAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnAnimationEnd(frameNode, nullptr);
        return;
    }
    auto onAnimationEnd = [arkCallback = CallbackHelper(*optValue)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, tabsAnimationEvent);
    };
    TabsModelStatic::SetOnAnimationEnd(frameNode, std::move(onAnimationEnd));
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const Opt_OnTabsGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnGestureSwipe(frameNode, nullptr);
        return;
    }
    auto onGestureSwipe = [arkCallback = CallbackHelper(*optValue)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_TabsAnimationEvent tabsAnimationEvent;
        tabsAnimationEvent.currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.00f));
        tabsAnimationEvent.targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.00f));
        tabsAnimationEvent.velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.00f));
        arkCallback.Invoke(arkIndex, tabsAnimationEvent);
    };
    TabsModelStatic::SetOnGestureSwipe(frameNode, std::move(onGestureSwipe));
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        TabsModelStatic::SetFadingEdge(frameNode, true);
        return;
    }
    TabsModelStatic::SetFadingEdge(frameNode, *convValue);
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<TabsItemDivider>(*value);
    TabsModelStatic::SetDivider(frameNode, divider);
    TabsModelStatic::InitDivider(frameNode);
}
void BarOverlapImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        TabsModelStatic::SetBarOverlap(frameNode, false);
        return;
    }
    TabsModelStatic::SetBarOverlap(frameNode, *convValue);
}
void BarBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelStatic::SetBarBackgroundColor(frameNode,  Converter::OptConvert<Color>(*value));
}
void BarGridAlignImpl(Ark_NativePointer node,
                      const Opt_BarGridColumnOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BarGridColumnOptions columnOption;
    auto convValue = Converter::OptConvert<BarGridColumnOptions>(*value);
    if (convValue) {
        columnOption = convValue.value();
    }
    TabsModelStatic::SetBarGridAlign(frameNode, columnOption);
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Opt_TabsCustomContentTransitionCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetIsCustomAnimation(frameNode, false);
        TabsModelStatic::SetOnCustomAnimation(frameNode, nullptr);
        return;
    }
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

    auto onCustomAnimation = [callback = CallbackHelper(*optValue), peerImplPtr](
        int32_t from, int32_t to) -> TabContentAnimatedTransition {
        peerImplPtr->SetFrom(from);
        peerImplPtr->SetTo(to);
        Ark_Number arkFrom = Converter::ArkValue<Ark_Number>(from);
        Ark_Number arkTo = Converter::ArkValue<Ark_Number>(to);
        TabContentAnimatedTransition transitionInfo;
        transitionInfo =
            callback.InvokeWithOptConvertResult<TabContentAnimatedTransition, Opt_TabContentAnimatedTransition,
            Callback_Opt_TabContentAnimatedTransition_Void>(arkFrom, arkTo).value_or(transitionInfo);
        std::optional<Ark_TabContentAnimatedTransition> arkTransitionInfo;
        arkTransitionInfo = callback.InvokeWithOptConvertResult<Ark_TabContentAnimatedTransition,
            Opt_TabContentAnimatedTransition,
            Callback_Opt_TabContentAnimatedTransition_Void>(arkFrom, arkTo);
        auto optTimeout = Converter::OptConvert<int32_t>(arkTransitionInfo->timeout);
        auto onTransition = [arkCallback = CallbackHelper(arkTransitionInfo->transition)]
            (const RefPtr<TabContentTransitionProxy>& proxy) {
            auto peer = new TabContentTransitionProxyPeer();
            CHECK_NULL_VOID(peer);
            peer->SetHandler(proxy);
            arkCallback.Invoke(peer);
        };
        transitionInfo.transition = std::move(onTransition);
        return transitionInfo;
    };
    TabsModelStatic::SetIsCustomAnimation(frameNode, true); //Set 'true' to any cases. It is wrong behavior.
    TabsModelStatic::SetOnCustomAnimation(frameNode, std::move(onCustomAnimation));
}
void BarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                 const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(*value);
    if (blurStyle) {
        option.blurStyle = blurStyle.value();
    }
    TabsModelStatic::SetBarBackgroundBlurStyle(frameNode, option);
}
void BarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                 const Opt_BlurStyle* style,
                                 const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(*style);
    auto bluroption = Converter::OptConvert<BlurStyleOption>(*options);
    if (bluroption) {
        option = bluroption.value();
    }
    if (blurStyle) {
        option.blurStyle = blurStyle.value();
    }
    TabsModelStatic::SetBarBackgroundBlurStyle(frameNode, option);
}
void BarBackgroundEffectImpl(Ark_NativePointer node,
                             const Opt_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    EffectOption option;
    auto convValue = Converter::OptConvert<EffectOption>(*value);
    if (convValue) {
        option = convValue.value();
    }
    TabsModelStatic::SetBarBackgroundEffect(frameNode, option);
}
void PageFlipModeImpl(Ark_NativePointer node,
                      const Opt_PageFlipMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    int32_t defaultValue = static_cast<int32_t>(PageFlipMode::CONTINUOUS);
    TabsModelStatic::SetPageFlipMode(frameNode, convValue.value_or(defaultValue));
}
void OnContentWillChangeImpl(Ark_NativePointer node,
                             const Opt_OnTabsContentWillChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabsModelStatic::SetOnContentWillChange(frameNode, nullptr);
        return;
    }
    auto callback = [callback = CallbackHelper(*optValue)](
        int32_t currentIndex, int32_t comingIndex) -> bool {
        Ark_Number arkCurrentIndex = Converter::ArkValue<Ark_Number>(currentIndex);
        Ark_Number arkComingIndex = Converter::ArkValue<Ark_Number>(comingIndex);
        return callback.InvokeWithOptConvertResult<
            bool, Ark_Boolean, Callback_Boolean_Void>(arkCurrentIndex, arkComingIndex)
            .value_or(false);
    };
    TabsModelStatic::SetOnContentWillChange(frameNode, std::move(callback));
}
void BarModeScrollableImpl(Ark_NativePointer node,
                           const Opt_ScrollableBarModeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::ArkValue<Opt_BarMode>(ARK_BAR_MODE_SCROLLABLE);
    BarMode1Impl(node, &mode, options);
}
void CachedMaxCountImpl(Ark_NativePointer node,
                        const Opt_Number* count,
                        const Opt_TabsCacheMode* mode)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto countValue = count ? Converter::OptConvert<int32_t>(*count) : std::nullopt;
    auto modeValue = Converter::OptConvert<TabsCacheMode>(*mode);
    TabsModelStatic::SetCachedMaxCount(frameNode, countValue, modeValue);
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
    TabsModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
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
