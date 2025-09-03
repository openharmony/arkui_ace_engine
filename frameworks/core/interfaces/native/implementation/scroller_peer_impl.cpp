/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "scroller_peer_impl.h"

namespace {
constexpr double DEFAULT_DURATION = 1000.0;

struct ScrollEdgeOptions {
    std::optional<float> velocity;
};

struct ScrollToIndexOptions {
    std::optional<float> extraOffset;
};

struct ScrollAnimationOptions {
    std::optional<double> duration;
    std::optional<OHOS::Ace::RefPtr<OHOS::Ace::Curve>> curve;
    std::optional<bool> canOverScroll;
};

using ScrollAnimationParam = std::variant<
    ScrollAnimationOptions, bool
>;

struct ScrollOptions {
    OHOS::Ace::Dimension xOffset;
    OHOS::Ace::Dimension yOffset;
    std::optional<ScrollAnimationParam> animation;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<ScrollEdgeType>& dst, const Ark_Edge& src)
{
    switch (src) {
        case ARK_EDGE_TOP: dst = ScrollEdgeType::SCROLL_TOP; break;
        case ARK_EDGE_CENTER: dst = ScrollEdgeType::SCROLL_NONE; break;
        case ARK_EDGE_BOTTOM: dst = ScrollEdgeType::SCROLL_BOTTOM; break;
        case ARK_EDGE_BASELINE: dst = ScrollEdgeType::SCROLL_NONE; break;
        case ARK_EDGE_START: dst = ScrollEdgeType::SCROLL_TOP; break;
        case ARK_EDGE_MIDDLE: dst = ScrollEdgeType::SCROLL_NONE; break;
        case ARK_EDGE_END: dst = ScrollEdgeType::SCROLL_BOTTOM; break;
        default: LOGE("Unexpected enum value in Ark_Edge: %{public}d", src);
    }
}

template<>
inline ScrollEdgeOptions Convert(const Ark_ScrollEdgeOptions& src)
{
    ScrollEdgeOptions scrollEdgeOptions = {
        .velocity = Converter::OptConvert<float>(src.velocity),
    };
    return scrollEdgeOptions;
}

template<>
inline ScrollToIndexOptions Convert(const Ark_ScrollToIndexOptions& src)
{
    auto offset = Converter::OptConvert<Dimension>(src.extraOffset);
    ScrollToIndexOptions scrollToIndexOptions = {
        .extraOffset = offset ? std::optional<float>(offset.value().ConvertToPx()) : std::nullopt
    };
    return scrollToIndexOptions;
}

template<>
inline ScrollAnimationOptions Convert(const Ark_ScrollAnimationOptions& src)
{
    ScrollAnimationOptions scrollAnimationOptions = {
        .duration = Converter::OptConvert<float>(src.duration),
        .curve = Converter::OptConvert<RefPtr<Curve>>(src.curve),
        .canOverScroll = Converter::OptConvert<bool>(src.canOverScroll),
    };
    return scrollAnimationOptions;
}

template<>
inline ScrollAnimationParam Convert(const Ark_ScrollAnimationOptions& src)
{
    return Converter::Convert<ScrollAnimationOptions>(src);
}

template<>
inline ScrollAnimationParam Convert(const Ark_Boolean& src)
{
    return Converter::Convert<bool>(src);
}

template<>
inline ScrollOptions Convert(const Ark_ScrollOptions& src)
{
    ScrollOptions scrollOptions = {
        .xOffset = Converter::OptConvert<Dimension>(src.xOffset).value(),
        .yOffset = Converter::OptConvert<Dimension>(src.yOffset).value(),
        .animation = Converter::OptConvert<ScrollAnimationParam>(src.animation),
    };
    return scrollOptions;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
void ScrollerPeerImpl::TriggerScrollTo(const Ark_ScrollOptions* optionsValue)
{
    CHECK_NULL_VOID(optionsValue);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollTo Controller not bound to component.");
        return;
    }
    ScrollOptions options = Converter::Convert<ScrollOptions>(*optionsValue);

    double duration = 0.0;
    bool smooth = false;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;

    if (options.animation) {
        ScrollAnimationParam animationParam = options.animation.value();
        if (auto animation = std::get_if<bool>(&animationParam)) {
            smooth = *animation;
        } else if (auto animationOptions = std::get_if<ScrollAnimationOptions>(&animationParam)) {
            bool hasDuration = true;
            if (!animationOptions->duration.has_value() || Negative(animationOptions->duration.value())) {
                duration = DEFAULT_DURATION;
                hasDuration = false;
            } else {
                duration = animationOptions->duration.value();
            }
            bool hasCurve = animationOptions->curve.has_value();
            curve = animationOptions->curve.value_or(curve);
            bool hasCanOverScroll = animationOptions->canOverScroll.has_value();
            canOverScroll = animationOptions->canOverScroll.value_or(canOverScroll);
            smooth = !hasDuration && !hasCurve && !hasCanOverScroll ? true : false;
        }
    }
    ContainerScope scope(instanceId_);
    auto direction = scrollController->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? options.yOffset : options.xOffset;
    scrollController->AnimateTo(position, static_cast<float>(duration), curve, smooth, canOverScroll);
}

void ScrollerPeerImpl::TriggerScrollEdge(Ark_Edge value, const Opt_ScrollEdgeOptions* options)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollEdge Controller not bound to component.");
        return;
    }
    std::optional<ScrollEdgeType> edgeType = Converter::OptConvert<ScrollEdgeType>(value);
    if (!edgeType.has_value()) {
        return;
    }
    ContainerScope scope(instanceId_);
    if (options) {
        std::optional<ScrollEdgeOptions> edgeOptions = Converter::OptConvert<ScrollEdgeOptions>(*options);
        if (edgeOptions && edgeOptions.value().velocity) {
            float velocity = edgeOptions.value().velocity.value();
            if (velocity > 0) {
                velocity = Dimension(velocity, DimensionUnit::VP).ConvertToPx();
                scrollController->ScrollToEdge(edgeType.value(), velocity);
                return;
            }
        }
    }
    scrollController->ScrollToEdge(edgeType.value(), true);
}

void ScrollerPeerImpl::TriggerFling(const Ark_Number* velocity)
{
    CHECK_NULL_VOID(velocity);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerFling Controller not bound to component.");
        return;
    }
    double flingVelocity = Converter::Convert<float>(*velocity);
    if (NearZero(flingVelocity)) {
        return;
    }
    ContainerScope scope(instanceId_);
    flingVelocity = Dimension(flingVelocity, DimensionUnit::VP).ConvertToPx();
    scrollController->Fling(flingVelocity);
}

void ScrollerPeerImpl::TriggerScrollPage0(const Ark_ScrollPageOptions* value)
{
    CHECK_NULL_VOID(value);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollPage0 Controller not bound to component.");
        return;
    }
    ContainerScope scope(instanceId_);
    bool next = Converter::Convert<bool>(value->next);
    auto smooth = Converter::OptConvert<bool>(value->animation).value_or(false);
    scrollController->ScrollPage(!next, smooth);
}

void ScrollerPeerImpl::TriggerScrollPage1(bool next)
{
    // deprecated since 9
    LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollPage1 Deprecated method.");
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollPage1 Controller not bound to component.");
        return;
    }
    ContainerScope scope(instanceId_);
    scrollController->ScrollPage(!next, false);
}

Ark_OffsetResult ScrollerPeerImpl::TriggerCurrentOffset()
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerCurrentOffset Controller not bound to component.");
        return {};
    }
    ContainerScope scope(instanceId_);
    auto offset = scrollController->GetCurrentOffset(); // the result of GetCurrentOffset need to be returned
    return Converter::ArkValue<Ark_OffsetResult>(offset);
}

void ScrollerPeerImpl::TriggerScrollToIndex(const Ark_Number* value, const Opt_Boolean* smoothValue,
    const Opt_ScrollAlign* alignValue, const Opt_ScrollToIndexOptions* options)
{
    CHECK_NULL_VOID(value);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollToIndex Controller not bound to component.");
        return;
    }

    int32_t index = Converter::Convert<int32_t>(*value);
    if (index < 0) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollToIndex Incorrect index value.");
        return;
    }

    bool smooth = false;
    if (smoothValue) {
        smooth = Converter::OptConvert<bool>(*smoothValue).value_or(smooth);
    }

    ScrollAlign align = ScrollAlign::NONE;
    if (alignValue) {
        align = Converter::OptConvert<ScrollAlign>(*alignValue).value_or(align);
    }

    std::optional<float> extraOffset = std::nullopt;
    if (options) {
        std::optional<ScrollToIndexOptions> scrollToIndexOptions =
            Converter::OptConvert<ScrollToIndexOptions>(*options);
        if (scrollToIndexOptions) {
            extraOffset = scrollToIndexOptions.value().extraOffset;
        }
    }

    ContainerScope scope(instanceId_);
    scrollController->ScrollToIndex(index, smooth, align, extraOffset);
}

void ScrollerPeerImpl::TriggerScrollBy(const Opt_Length* dx, const Opt_Length* dy)
{
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    Dimension xOffset = Converter::OptConvert<Dimension>(*dx).value_or(Dimension());
    Dimension yOffset = Converter::OptConvert<Dimension>(*dy).value_or(Dimension());

    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollBy Controller not bound to component.");
        return;
    }

    ContainerScope scope(instanceId_);
    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            if (xOffset.Unit() == DimensionUnit::PERCENT) {
                deltaX = 0.0;
            } else {
                deltaX = context->NormalizeToPx(xOffset);
            }
            if (yOffset.Unit() == DimensionUnit::PERCENT) {
                deltaY = 0.0;
            } else {
                deltaY = context->NormalizeToPx(yOffset);
            }
        }
    }
    scrollController->ScrollBy(deltaX, deltaY, false);
}

Ark_Boolean ScrollerPeerImpl::TriggerIsAtEnd()
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerIsAtEnd Controller not bound to component.");
        return 0;
    }
    ContainerScope scope(instanceId_);
    return Converter::ArkValue<Ark_Boolean>(scrollController->IsAtEnd());
}

Ark_RectResult ScrollerPeerImpl::TriggerGetItemRect(const Ark_Number* indexValue)
{
    CHECK_NULL_RETURN(indexValue, {});
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerGetItemRect Controller not bound to component.");
        return {};
    }
    int32_t index = Converter::Convert<int32_t>(*indexValue);
    ContainerScope scope(instanceId_);
    auto rect = scrollController->GetItemRect(index); // the result of GetItemRect need to be returned
    return Converter::ArkValue<Ark_RectResult>(rect);
}

Ark_Int32 ScrollerPeerImpl::TriggerGetItemIndex(const Ark_Number* x, const Ark_Number* y)
{
    CHECK_NULL_RETURN(x, Converter::ArkValue<Ark_Int32>(-1));
    CHECK_NULL_RETURN(y, Converter::ArkValue<Ark_Int32>(-1));

    Dimension xOffset = Converter::Convert<Dimension>(*x);
    Dimension yOffset = Converter::Convert<Dimension>(*y);

    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerGetItemIndex Controller not bound to component.");
        return Converter::ArkValue<Ark_Int32>(-1);
    }

    ContainerScope scope(instanceId_);
    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            deltaX = context->NormalizeToPx(xOffset);
            deltaY = context->NormalizeToPx(yOffset);
        }
    }

    return Converter::ArkValue<Ark_Int32>(scrollController->GetItemIndex(deltaX, deltaY));
}
} // namespace OHOS::Ace::NG::GeneratedModifier
