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

#ifdef WINDOWS_PLATFORM
#include <windows.h>
inline void* LoadLibrary(const char* libPath)
{
    return LoadLibraryA(libPath);
}
inline void* FindSymbol(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
inline void* LoadLibrary(const char* libPath)
{
    void* handle = dlopen(libPath, RTLD_LOCAL | RTLD_LAZY);
    if (!handle) {
        return nullptr;
    }
    return handle;
}
inline void* FindSymbol(void* library, const char* name)
{
    return dlsym(library, name);
}
#endif

namespace {
constexpr double DEFAULT_DURATION = 1000.0;

constexpr const char* ERROR_MSG_SCROLLCONTROLLER_NOT_FOUND = "Controller not bound to component.";
constexpr const char* ERROR_MSG_PARAM_INVALID = "Input parameter check failed.";
constexpr int32_t ERROR_CODE_SCROLLCONTROLLER_NOT_FOUND = 100004;
constexpr int32_t ERROR_CODE_PARAM_INVALID = 401;
#ifdef WINDOWS_PLATFORM
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.dll";
#else
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.z.so";
#endif
using AniThrowErrorFunc = void (*)(Ark_VMContext vmContext, int32_t errCode, const std::string& errorMsg);
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

using ScrollAnimationParam = std::variant<ScrollAnimationOptions, bool>;

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
        case ARK_EDGE_BOTTOM: dst = ScrollEdgeType::SCROLL_BOTTOM; break;
        case ARK_EDGE_START: dst = ScrollEdgeType::SCROLL_TOP; break;
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
void ScrollerPeerImpl::TriggerScrollTo(Ark_VMContext vmContext, const Ark_ScrollOptions* optionsValue)
{
    CHECK_NULL_VOID(optionsValue);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollTo Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
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

void ScrollerPeerImpl::TriggerScrollEdge(Ark_VMContext vmContext, Ark_Edge value, const Opt_ScrollEdgeOptions* options)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollEdge Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
        return;
    }
    std::optional<ScrollEdgeType> edgeType = Converter::OptConvert<ScrollEdgeType>(value);
    if (!edgeType.has_value()) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto edgeOptions = Converter::OptConvertPtr<ScrollEdgeOptions>(options);
    if (edgeOptions && edgeOptions.value().velocity) {
        float velocity = edgeOptions.value().velocity.value();
        if (velocity > 0) {
            velocity = Dimension(velocity, DimensionUnit::VP).ConvertToPx();
            scrollController->ScrollToEdge(edgeType.value(), velocity);
            return;
        }
    }
    scrollController->ScrollToEdge(edgeType.value(), true);
}

void ScrollerPeerImpl::TriggerFling(Ark_VMContext vmContext, const Ark_Float64 velocity)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerFling Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
        return;
    }
    double flingVelocity = Converter::Convert<double>(velocity);
    if (NearZero(flingVelocity)) {
        return;
    }
    ContainerScope scope(instanceId_);
    flingVelocity = Dimension(flingVelocity, DimensionUnit::VP).ConvertToPx();
    scrollController->Fling(flingVelocity);
}

void ScrollerPeerImpl::TriggerScrollPage0(Ark_VMContext vmContext, const Ark_ScrollPageOptions* value)
{
    CHECK_NULL_VOID(value);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollPage0 Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
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

Opt_OffsetResult ScrollerPeerImpl::TriggerCurrentOffset(Ark_VMContext vmContext)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerCurrentOffset Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
        return Converter::ArkValue<Opt_OffsetResult>();
    }
    ContainerScope scope(instanceId_);
    auto offset = scrollController->GetCurrentOffset(); // the result of GetCurrentOffset need to be returned
    return Converter::ArkValue<Opt_OffsetResult>(offset);
}

Opt_OffsetResult ScrollerPeerImpl::TriggerOffset()
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerOffset Controller not bound to component.");
        return (Opt_OffsetResult) {
            .tag = static_cast<InteropTag>(INTEROP_TAG_UNDEFINED),
            .value = { 0, 0 }
            };
    }
    ContainerScope scope(instanceId_);
    auto offset = scrollController->GetCurrentOffset(); // the result of GetCurrentOffset need to be returned
    return Converter::ArkValue<Opt_OffsetResult>(offset);
}

void ScrollerPeerImpl::TriggerScrollToIndex(Ark_VMContext vmContext, const Ark_Int32 value,
    const Opt_Boolean* smoothValue, const Opt_ScrollAlign* alignValue, const Opt_ScrollToIndexOptions* options)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollToIndex Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
        return;
    }

    int32_t index = Converter::Convert<int32_t>(value);
    if (index < 0) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollToIndex Incorrect index value.");
        return;
    }

    auto smooth = Converter::OptConvertPtr<bool>(smoothValue).value_or(false);
    auto align = Converter::OptConvertPtr<ScrollAlign>(alignValue).value_or(ScrollAlign::NONE);
    auto scrollToIndexOptions = Converter::OptConvertPtr<ScrollToIndexOptions>(options);
    auto extraOffset = scrollToIndexOptions ? scrollToIndexOptions->extraOffset : std::nullopt;

    ContainerScope scope(instanceId_);
    scrollController->ScrollToIndex(index, smooth, align, extraOffset);
}

void ScrollerPeerImpl::TriggerScrollBy(Ark_VMContext vmContext, const Dimension& xOffset, const Dimension& yOffset)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerScrollBy Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
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

Ark_Boolean ScrollerPeerImpl::TriggerIsAtEnd(Ark_VMContext vmContext)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerIsAtEnd Controller not bound to component.");
        return 0;
    }
    ContainerScope scope(instanceId_);
    return Converter::ArkValue<Ark_Boolean>(scrollController->IsAtEnd());
}

Ark_RectResult ScrollerPeerImpl::TriggerGetItemRect(Ark_VMContext vmContext, const Ark_Int32 indexValue)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerGetItemRect Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
        return Converter::ArkValue<Ark_RectResult>(Rect());
    }
    int32_t index = Converter::Convert<int32_t>(indexValue);
    ContainerScope scope(instanceId_);
    auto rect = scrollController->GetItemRect(index); // the result of GetItemRect need to be returned
    return Converter::ArkValue<Ark_RectResult>(rect);
}

Ark_Int32 ScrollerPeerImpl::TriggerGetItemIndex(Ark_VMContext vmContext, const Ark_Float64 x, const Ark_Float64 y)
{
    Dimension xOffset = Converter::Convert<Dimension>(x);
    Dimension yOffset = Converter::Convert<Dimension>(y);

    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        LOGE("ARKOALA ScrollerPeerImpl::TriggerGetItemIndex Controller not bound to component.");
        ScrollerPeerImpl::ThrowControllerError(vmContext);
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

void ScrollerPeerImpl::ThrowParamsError(Ark_VMContext vmContext)
{
    if (vmContext == nullptr) {
        TAG_LOGE(AceLogTag::ACE_SCROLLABLE, "null env");
        return;
    }
    ScrollerPeerImpl::ThrowError(vmContext, ERROR_CODE_PARAM_INVALID, ERROR_MSG_PARAM_INVALID);
}

void ScrollerPeerImpl::ThrowControllerError(Ark_VMContext vmContext)
{
    if (vmContext == nullptr) {
        TAG_LOGE(AceLogTag::ACE_SCROLLABLE, "null env");
        return;
    }
    ScrollerPeerImpl::ThrowError(
        vmContext, ERROR_CODE_SCROLLCONTROLLER_NOT_FOUND, ERROR_MSG_SCROLLCONTROLLER_NOT_FOUND);
}
void ScrollerPeerImpl::ThrowError(Ark_VMContext vmContext, int32_t errCode, const std::string& errorMsg)
{
    if (vmContext == nullptr) {
        TAG_LOGE(AceLogTag::ACE_SCROLLABLE, "null env");
        return;
    }
    auto handle = LoadLibrary(LIBARKOALA_MODULE);
    if (handle == nullptr) {
        LOGE("dlopen can't find libArkoalaNative.z.so");
        return;
    }
    auto aniErrorFunc = reinterpret_cast<AniThrowErrorFunc>(FindSymbol(handle, "AniThrowError"));
    if (aniErrorFunc == nullptr) {
        LOGE("dlsym can't find ANI_ThrowError");
        return;
    }
    aniErrorFunc(vmContext, errCode, errorMsg);
}
} // namespace OHOS::Ace::NG::GeneratedModifier
