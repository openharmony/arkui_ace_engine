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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/pattern/scroll/scroll_model_static.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
inline OffsetT<CalcDimension> Convert(const Ark_OffsetOptions& value)
{
    auto xOffset = Converter::OptConvert<CalcDimension>(value.xOffset);
    auto yOffset = Converter::OptConvert<CalcDimension>(value.yOffset);
    OffsetT<CalcDimension> dst;
    if (xOffset.has_value()) {
        dst.SetX(xOffset.value());
    }
    if (yOffset.has_value()) {
        dst.SetY(yOffset.value());
    }
    return dst;
}
template<>
inline bool Convert(const Ark_EdgeEffectOptions& value)
{
    return Converter::Convert<bool>(value.alwaysEnabled);
}
template<>
TwoDimensionScrollResult Convert(const Ark_OffsetResult& src)
{
    auto xOffset = OptConvert<Dimension>(src.xOffset);
    auto yOffset = OptConvert<Dimension>(src.yOffset);
    TwoDimensionScrollResult result;
    if (xOffset.has_value()) {
        result.xOffset = xOffset.value();
    }
    if (yOffset.has_value()) {
        result.yOffset = yOffset.value();
    }
    return result;
}
} // namespace Converter
namespace {
std::vector<Dimension> ValidateDimensionArray(std::optional<std::vector<std::optional<Dimension>>>& in)
{
    std::vector<Dimension> out;
    if (!in) {
        return out;
    }
    for (auto& v : in.value()) {
        Validator::ValidateNonNegative(v);
        if (!v) {
            out.clear();
            break;
        }
        out.emplace_back(std::move(v.value()));
    }
    return out;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ScrollModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ScrollModifier
namespace ScrollInterfaceModifier {
void SetScrollOptionsImpl(Ark_NativePointer node,
                          const Opt_Scroller* scroller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ScrollControllerBase> positionController = ScrollModelStatic::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = ScrollModelStatic::GetOrCreateScrollBarProxy(frameNode);

    auto abstPeerPtrOpt = Converter::OptConvertPtr<Ark_Scroller>(scroller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = abstPeerPtrOpt.value();
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
} // ScrollInterfaceModifier
namespace ScrollAttributeModifier {
void SetScrollableImpl(Ark_NativePointer node,
                       const Opt_ScrollDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = Converter::OptConvertPtr<Axis>(value);
    ScrollModelStatic::SetAxis(frameNode, direction);
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_ScrollOnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnWillScroll(frameNode, nullptr);
        return;
    }
    if (optValue) {
        auto call = [arkCallback = CallbackHelper(*optValue)] (
            const Dimension& xOffset,
            const Dimension& yOffset,
            const ScrollState& scrollState,
            const ScrollSource& scrollSource) {
            auto retVal = arkCallback.InvokeWithOptConvertResult<
                TwoDimensionScrollResult,
                Opt_OffsetResult,
                Callback_Opt_OffsetResult_Void>(
                Converter::ArkValue<Ark_Float64>(xOffset),
                Converter::ArkValue<Ark_Float64>(yOffset),
                Converter::ArkValue<Ark_ScrollState>(scrollState),
                Converter::ArkValue<Ark_ScrollSource>(scrollSource)
            );
            TwoDimensionScrollResult defaultResult { .xOffset = xOffset, .yOffset = yOffset };
            return retVal.value_or(defaultResult);
        };
        ScrollModelStatic::SetOnWillScroll(frameNode, call);
    }
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_ScrollOnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnDidScroll(frameNode, nullptr);
        return;
    }
    auto call = [arkCallback = CallbackHelper(*optValue)](
        Dimension xIn, Dimension yIn, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto x = Converter::ArkValue<Ark_Float64>(xIn);
            auto y = Converter::ArkValue<Ark_Float64>(yIn);
            arkCallback.Invoke(x, y, state);
    };
    ScrollModelStatic::SetOnDidScroll(frameNode, std::move(call));
}
void SetOnScrollEdgeImpl(Ark_NativePointer node,
                         const Opt_OnScrollEdgeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnScrollEdge(frameNode, nullptr);
        return;
    }
    auto call = [arkCallback = CallbackHelper(*optValue)](ScrollEdge edgeIn) {
        auto edge = Converter::ArkValue<Ark_Edge>(edgeIn);
        arkCallback.Invoke(edge);
    };
    ScrollModelStatic::SetOnScrollEdge(frameNode, call);
}
void SetOnScrollStartImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnScrollStart(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ScrollModelStatic::SetOnScrollStart(frameNode, std::move(onEvent));
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnScrollStop(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    ScrollModelStatic::SetOnScrollStop(frameNode, std::move(onEvent));
}
void SetScrollBarImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto displayMode = Converter::OptConvertPtr<DisplayMode>(value);
    ScrollModelStatic::SetScrollBar(frameNode, displayMode);
}
void SetScrollBarColorImpl(Ark_NativePointer node,
                           const Opt_Union_arkui_component_enums_Color_I32_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto colorVal = Converter::OptConvertPtr<Color>(value);
    ScrollModelStatic::SetScrollBarColor(frameNode, colorVal);
}
void SetScrollBarWidthImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonPercent(width);
    ScrollModelStatic::SetScrollBarWidth(frameNode, width);
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetOnScrollFrameBegin(frameNode, nullptr);
        return;
    }
    auto onScrollFrameEvent = [callback = CallbackHelper(*optValue)](
        Dimension dimension, ScrollState state) -> ScrollFrameResult {
        ScrollFrameResult result;
        Ark_Float64 arkValue = Converter::ArkValue<Ark_Float64>(dimension);
        Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
        return callback.InvokeWithOptConvertResult<
            ScrollFrameResult, Ark_OnScrollFrameBeginHandlerResult,
            Callback_OnScrollFrameBeginHandlerResult_Void>(arkValue, arkState)
            .value_or(result);
    };

    ScrollModelStatic::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ScrollModelStatic::SetNestedScroll(frameNode, std::nullopt, std::nullopt);
        return;
    }
    auto forward = Converter::OptConvert<NestedScrollMode>(optValue->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(optValue->scrollBackward);
    ScrollModelStatic::SetNestedScroll(frameNode, forward, backward);
}
void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        convValue = true;
    }
    ScrollModelStatic::SetScrollEnabled(frameNode, *convValue);
}
void SetFrictionImpl(Ark_NativePointer node,
                     const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto frictionVal = Converter::OptConvertPtr<float>(value);
    ScrollModelStatic::SetFriction(frameNode, frictionVal);
}
void SetScrollSnapImpl(Ark_NativePointer node,
                       const Opt_ScrollSnapOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        std::vector<Dimension> snapSizes;
        ScrollModelStatic::SetScrollSnap(frameNode, std::nullopt, std::nullopt, snapSizes, std::nullopt, std::nullopt);
        return;
    }
    auto snapAlign = Converter::OptConvert<ScrollSnapAlign>(optValue->snapAlign);
    auto enableSnapToStart = Converter::OptConvert<bool>(optValue->enableSnapToStart);
    auto enableSnapToEnd = Converter::OptConvert<bool>(optValue->enableSnapToEnd);

    std::optional<std::vector<std::optional<Dimension>>> paginationParamsOpt;
    std::optional<Dimension> intervalSize;
    Converter::VisitUnion(optValue->snapPagination,
        [&paginationParamsOpt](const Array_Dimension& src) {
            paginationParamsOpt = Converter::Convert<std::vector<std::optional<Dimension>>>(src);
        },
        [&intervalSize](const auto& src) {
            intervalSize = Converter::OptConvert<Dimension>(src);
        },
        []() {});
    auto paginationParams = ValidateDimensionArray(paginationParamsOpt);
    Validator::ValidateNonNegative(intervalSize);
    ScrollModelStatic::SetScrollSnap(
        frameNode,
        snapAlign,
        intervalSize,
        paginationParams,
        enableSnapToStart,
        enableSnapToEnd);
}
void SetEnablePagingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        convValue = false;
    }
    ScrollModelStatic::SetEnablePaging(frameNode, *convValue);
}
void SetInitialOffsetImpl(Ark_NativePointer node,
                          const Opt_OffsetOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OffsetT<CalcDimension>>(*value);
    if (!convValue) {
        ScrollModelStatic::SetInitialOffset(frameNode, std::nullopt);
        return;
    }
    ScrollModelStatic::SetInitialOffset(frameNode, *convValue);
}
void SetEdgeEffectImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* edgeEffect,
                       const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto effect = Converter::OptConvert<EdgeEffect>(*edgeEffect);

    bool alwaysEnabled = true;
    EffectEdge edge = EffectEdge::ALL;
    auto edgeEffectOptions = options ? Converter::GetOpt(*options) : std::nullopt;
    if (edgeEffectOptions) {
        alwaysEnabled = Converter::Convert<bool>(edgeEffectOptions.value().alwaysEnabled);
        auto value = Converter::OptConvert<int32_t>(edgeEffectOptions.value().effectEdge);
        if (value.has_value()) {
            edge = static_cast<EffectEdge>(value.value());
        }
    }
    ScrollModelStatic::SetEdgeEffect(frameNode, effect, alwaysEnabled, edge);
}
} // ScrollAttributeModifier
const GENERATED_ArkUIScrollModifier* GetScrollModifier()
{
    static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
        ScrollModifier::ConstructImpl,
        ScrollInterfaceModifier::SetScrollOptionsImpl,
        ScrollAttributeModifier::SetScrollableImpl,
        ScrollAttributeModifier::SetOnWillScrollImpl,
        ScrollAttributeModifier::SetOnDidScrollImpl,
        ScrollAttributeModifier::SetOnScrollEdgeImpl,
        ScrollAttributeModifier::SetOnScrollStartImpl,
        ScrollAttributeModifier::SetOnScrollStopImpl,
        ScrollAttributeModifier::SetScrollBarImpl,
        ScrollAttributeModifier::SetScrollBarColorImpl,
        ScrollAttributeModifier::SetScrollBarWidthImpl,
        ScrollAttributeModifier::SetOnScrollFrameBeginImpl,
        ScrollAttributeModifier::SetNestedScrollImpl,
        ScrollAttributeModifier::SetEnableScrollInteractionImpl,
        ScrollAttributeModifier::SetFrictionImpl,
        ScrollAttributeModifier::SetScrollSnapImpl,
        ScrollAttributeModifier::SetEnablePagingImpl,
        ScrollAttributeModifier::SetInitialOffsetImpl,
        ScrollAttributeModifier::SetEdgeEffectImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
