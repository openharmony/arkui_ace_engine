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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::Converter {
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
void AssignTo(std::optional<std::vector<std::optional<Dimension>>>& dst, const Ark_Length& from)
{
    dst.reset();
}
template<>
void AssignTo(std::optional<Dimension>& dst, const Array_Length& from)
{
    dst.reset();
}

template<>
void AssignTo(std::optional<ScrollFrameResult>& dst, const Ark_OnScrollFrameBeginHandlerResult& from)
{
    ScrollFrameResult ret;
    ret.offset = Converter::Convert<Dimension>(from.offsetRemain);
    dst = ret;
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
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ScrollModelNG::CreateFrameNode(id);
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
    CHECK_NULL_VOID(scroller);
    RefPtr<ScrollControllerBase> positionController = ScrollModelNG::GetOrCreateController(frameNode);
    // need check
    // RefPtr<ScrollProxy> scrollBarProxy = ScrollModelNG::GetOrCreateScrollBarProxy(frameNode);

    // auto abstPeerPtrOpt = Converter::OptConvert<Ark_Scroller>(*scroller);
    // CHECK_NULL_VOID(abstPeerPtrOpt);
    // auto peerImplPtr = abstPeerPtrOpt.value();
    // CHECK_NULL_VOID(peerImplPtr);
    // peerImplPtr->SetController(positionController);
    // peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
} // ScrollInterfaceModifier
namespace ScrollAttributeModifier {
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
}

void ScrollableImpl(Ark_NativePointer node,
                    Ark_ScrollDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = Converter::OptConvert<Axis>(value);
    // need check
    // ScrollModelNG::SetAxis(frameNode, direction);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](Dimension xOffset, Dimension yOffset) {
        auto arkxOffset = Converter::ArkValue<Ark_Number>(xOffset);
        auto arkyOffset = Converter::ArkValue<Ark_Number>(yOffset);
        arkCallback.Invoke(arkxOffset, arkyOffset);
    };
    ScrollModelNG::SetOnScroll(frameNode, std::move(onEvent));
}
void OnWillScrollImpl(Ark_NativePointer node,
                      const Opt_ScrollOnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto callValue = Converter::OptConvert<ScrollOnWillScrollCallback>(*value);
    if (callValue.has_value()) {
        auto call = [arkCallback = CallbackHelper(callValue.value())] (
            const Dimension& xOffset,
            const Dimension& yOffset,
            const ScrollState& scrollState,
            const ScrollSource& scrollSource) {
            auto retVal = arkCallback.InvokeWithOptConvertResult<
                TwoDimensionScrollResult,
                Ark_OffsetResult,
                Callback_OffsetResult_Void>(
                Converter::ArkValue<Ark_Number>(xOffset),
                Converter::ArkValue<Ark_Number>(yOffset),
                Converter::ArkValue<Ark_ScrollState>(scrollState),
                Converter::ArkValue<Ark_ScrollSource>(scrollSource)
            );
            TwoDimensionScrollResult retDefault = {xOffset, yOffset};
            return retVal.value_or(retDefault);
        };
        ScrollModelNG::SetOnWillScroll(frameNode, call);
    }
}
void OnDidScrollImpl(Ark_NativePointer node,
                     const ScrollOnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto call = [arkCallback = CallbackHelper(*value)](
        Dimension xIn, Dimension yIn, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto x = Converter::ArkValue<Ark_Number>(xIn);
            auto y = Converter::ArkValue<Ark_Number>(yIn);
            arkCallback.Invoke(x, y, state);
    };
    ScrollModelNG::SetOnDidScroll(frameNode, std::move(call));
}
void OnScrollEdgeImpl(Ark_NativePointer node,
                      const OnScrollEdgeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto call = [arkCallback = CallbackHelper(*value)](ScrollEdge edgeIn) {
        auto edge = Converter::ArkValue<Ark_Edge>(edgeIn);
        arkCallback.Invoke(edge);
    };
    ScrollModelNG::SetOnScrollEdge(frameNode, call);
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    ScrollModelNG::SetOnScrollStart(frameNode, std::move(onEvent));
}
void OnScrollEndImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    // need check
    // ScrollModelNG::SetOnScrollEnd(frameNode, std::move(onEvent));
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    ScrollModelNG::SetOnScrollStop(frameNode, std::move(onEvent));
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto displayMode = Converter::OptConvert<DisplayMode>(value);
    // need check
    // ScrollModelNG::SetScrollBar(frameNode, displayMode);
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Ark_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto colorVal = Converter::OptConvert<Color>(*value);
    // need check
    // ScrollModelNG::SetScrollBarColor(frameNode, colorVal);
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonPercent(width);
    // need check
    // ScrollModelNG::SetScrollBarWidth(frameNode, width);
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onScrollFrameEvent = [callback = CallbackHelper(*value)](
        Dimension dimension, ScrollState state) -> ScrollFrameResult {
        ScrollFrameResult result;
        Ark_Number arkValue = Converter::ArkValue<Ark_Number>(dimension);
        Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
        return callback.InvokeWithOptConvertResult<
            ScrollFrameResult, Ark_OnScrollFrameBeginHandlerResult,
            Callback_OnScrollFrameBeginHandlerResult_Void>(arkValue, arkState)
            .value_or(result);
    };

    ScrollModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto forward = Converter::OptConvert<NestedScrollMode>(value->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(value->scrollBackward);
    // need check
    // ScrollModelNG::SetNestedScroll(frameNode, forward, backward);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollEnabled(frameNode, Converter::Convert<bool>(value));
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto frictionVal = Converter::OptConvert<float>(*value);
    // need check
    // ScrollModelNG::SetFriction(frameNode, frictionVal);
}
void ScrollSnapImpl(Ark_NativePointer node,
                    const Ark_ScrollSnapOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto snapAlign = Converter::OptConvert<ScrollSnapAlign>(value->snapAlign);
    auto enableSnapToStart = Converter::OptConvert<bool>(value->enableSnapToStart);
    auto enableSnapToEnd = Converter::OptConvert<bool>(value->enableSnapToEnd);

    auto paginationParamsOpt = Converter::OptConvert<std::vector<std::optional<Dimension>>>(value->snapPagination);
    auto paginationParams = ValidateDimensionArray(paginationParamsOpt);
    auto intervalSize = Converter::OptConvert<Dimension>(value->snapPagination);
    Validator::ValidateNonNegative(intervalSize);
    ScrollModelNG::SetScrollSnap(
        frameNode,
        snapAlign,
        intervalSize,
        paginationParams,
        enableSnapToStart,
        enableSnapToEnd);
}
void EnablePagingImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetEnablePaging(frameNode, Converter::Convert<bool>(value));
}
void InitialOffsetImpl(Ark_NativePointer node,
                       const Ark_OffsetOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    OffsetT<CalcDimension> offset = Converter::Convert<OffsetT<CalcDimension>>(*value);
    ScrollModelNG::SetInitialOffset(frameNode, offset);
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    auto effect = Converter::OptConvert<EdgeEffect>(edgeEffect);
    auto always = Converter::OptConvert<bool>(*options);
    // need check
    // ScrollModelNG::SetEdgeEffect(frameNode, effect, always);
}
} // ScrollAttributeModifier
const GENERATED_ArkUIScrollModifier* GetScrollModifier()
{
    static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
        ScrollModifier::ConstructImpl,
        ScrollInterfaceModifier::SetScrollOptionsImpl,
        ScrollAttributeModifier::ScrollableImpl,
        ScrollAttributeModifier::OnScrollImpl,
        ScrollAttributeModifier::OnWillScrollImpl,
        ScrollAttributeModifier::OnDidScrollImpl,
        ScrollAttributeModifier::OnScrollEdgeImpl,
        ScrollAttributeModifier::OnScrollStartImpl,
        ScrollAttributeModifier::OnScrollEndImpl,
        ScrollAttributeModifier::OnScrollStopImpl,
        ScrollAttributeModifier::ScrollBarImpl,
        ScrollAttributeModifier::ScrollBarColorImpl,
        ScrollAttributeModifier::ScrollBarWidthImpl,
        ScrollAttributeModifier::OnScrollFrameBeginImpl,
        ScrollAttributeModifier::NestedScrollImpl,
        ScrollAttributeModifier::EnableScrollInteractionImpl,
        ScrollAttributeModifier::FrictionImpl,
        ScrollAttributeModifier::ScrollSnapImpl,
        ScrollAttributeModifier::EnablePagingImpl,
        ScrollAttributeModifier::InitialOffsetImpl,
        ScrollAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
