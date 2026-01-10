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
#include "core/interfaces/native/implementation/leading_margin_span_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "arkoala_api_generated.h"
#include "draw_context_peer.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG::Converter {

void AssignArkValue(Ark_LeadingMarginSpan& dst, const DrawableLeadingMargin& src)
{
    dst = PeerUtils::CreatePeer<LeadingMarginSpanPeer>();
    if (dst->span.has_value()) {
        dst->span.value().onDraw_ = src.onDraw_;
        dst->span.value().getLeadingMarginFunc_ = src.getLeadingMarginFunc_;
    }
}

void AssignArkValue(Ark_LeadingMarginSpanDrawInfo& dst, const LeadingMarginSpanOptions& src)
{
    dst.x = Converter::ArkValue<Ark_Float64>(src.x);
    dst.direction = Converter::ArkValue<Ark_TextDirection>(src.direction);
    dst.top = Converter::ArkValue<Ark_Float64>(src.top);
    dst.baseline = Converter::ArkValue<Ark_Float64>(src.baseline);
    dst.bottom = Converter::ArkValue<Ark_Float64>(src.bottom);
    dst.start = Converter::ArkValue<Ark_Float64>(src.start);
    dst.end = Converter::ArkValue<Ark_Float64>(src.end);
    dst.first = Converter::ArkValue<Ark_Boolean>(src.first);
}
template<>
NG::DrawableLeadingMargin Convert(const Ark_LeadingMarginSpan& src)
{
    NG::DrawableLeadingMargin options;
    options.getLeadingMarginFunc_ = src->span->getLeadingMarginFunc_;
    options.onDraw_ = src->span->onDraw_;
    return options;
}

template<>
NG::LeadingMarginSpanOptions Convert(const Ark_LeadingMarginSpanDrawInfo& src)
{
    NG::LeadingMarginSpanOptions options;
    options.x = Converter::Convert<double>(src.x);
    options.direction = Converter::Convert<TextDirection>(src.direction);
    options.top = Converter::Convert<double>(src.top);
    options.baseline = Converter::Convert<double>(src.baseline);
    options.bottom = Converter::Convert<double>(src.bottom);
    options.start = Converter::Convert<size_t>(src.start);
    options.end = Converter::Convert<size_t>(src.end);
    options.first = Converter::Convert<bool>(src.first);
    return options;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LeadingMarginSpanAccessor {
void DestroyPeerImpl(Ark_LeadingMarginSpan peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LeadingMarginSpan ConstructImpl()
{
    return PeerUtils::CreatePeer<LeadingMarginSpanPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
Callback_DrawContext_LeadingMarginSpanDrawInfo_Void GetOnDraw_callbackImpl(Ark_LeadingMarginSpan peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto handler = [span = peer->span](Ark_DrawContext arkCtxPtr, Ark_LeadingMarginSpanDrawInfo arkInfo) {
        CHECK_NULL_VOID(span);
        auto onDrawFunc = span->onDraw_;
        CHECK_NULL_VOID(onDrawFunc);
        CHECK_NULL_VOID(arkCtxPtr);
        LeadingMarginSpanOptions options = Converter::Convert<LeadingMarginSpanOptions>(arkInfo);
        onDrawFunc(*arkCtxPtr, options);
    };
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_DrawContext_LeadingMarginSpanDrawInfo_Void,
        std::function<void(Ark_DrawContext, Ark_LeadingMarginSpanDrawInfo)>>(handler);
    return callback;
}

void SetOnDraw_callbackImpl(
    Ark_LeadingMarginSpan peer, const Callback_DrawContext_LeadingMarginSpanDrawInfo_Void* onDraw_callback)
{
    CHECK_NULL_VOID(peer && peer->span);
    peer->span->onDraw_ = nullptr;
    if (onDraw_callback) {
        auto callback = [arkCallback = CallbackHelper(*onDraw_callback)](NG::DrawingContext& drawingContext,
                            const LeadingMarginSpanOptions& leadingMarginSpanOptions) {
            auto arkCtxPtr = reinterpret_cast<Ark_DrawContext>(std::addressof(drawingContext));
            auto arkInfo = Converter::ArkValue<Ark_LeadingMarginSpanDrawInfo>(leadingMarginSpanOptions);
            arkCallback.InvokeSync(arkCtxPtr, arkInfo);
        };
        peer->span->onDraw_ = callback;
    }
}

Callback_LengthMetrics GetGetLeadingMargin_callbackImpl(Ark_LeadingMarginSpan peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto handler = [peer](Callback_LengthMetrics_Void continuation) {
        CHECK_NULL_VOID(peer && peer->span);
        auto getLeadingMarginFunc = peer->span->getLeadingMarginFunc_;
        CHECK_NULL_VOID(getLeadingMarginFunc);
        auto res = getLeadingMarginFunc();
        auto result = Converter::ArkValue<Ark_LengthMetrics>(res);
        if (continuation.callSync) {
            (*continuation.callSync)(
                CallbackHelper<VoidCallback>::GetVMContext(), continuation.resource.resourceId, result);
        }
    };
    auto callback =
        CallbackKeeper::ReturnReverseCallback<Callback_LengthMetrics, std::function<void(Callback_LengthMetrics_Void)>>(
            handler);
    return callback;
}

void SetGetLeadingMargin_callbackImpl(
    Ark_LeadingMarginSpan peer, const Callback_LengthMetrics* getLeadingMargin_callback)
{
    CHECK_NULL_VOID(peer && peer->span);
    peer->span->getLeadingMarginFunc_ = nullptr;
    if (getLeadingMargin_callback) {
        auto callback = [arkCallback = CallbackHelper(*getLeadingMargin_callback)]() -> CalcDimension {
            Ark_LengthMetrics result {};
            auto handler = [&result](Ark_LengthMetrics value) { result = value; };
            auto continuation = CallbackKeeper::Claim<Callback_LengthMetrics_Void>(std::move(handler));
            arkCallback.InvokeSync(continuation.ArkValue());
            return Converter::Convert<CalcDimension>(result);
        };
        peer->span->getLeadingMarginFunc_ = callback;
    }
}
} // namespace LeadingMarginSpanAccessor
const GENERATED_ArkUILeadingMarginSpanAccessor* GetLeadingMarginSpanAccessor()
{
    static const GENERATED_ArkUILeadingMarginSpanAccessor LeadingMarginSpanAccessorImpl {
        LeadingMarginSpanAccessor::DestroyPeerImpl,
        LeadingMarginSpanAccessor::ConstructImpl,
        LeadingMarginSpanAccessor::GetFinalizerImpl,
        LeadingMarginSpanAccessor::GetOnDraw_callbackImpl,
        LeadingMarginSpanAccessor::SetOnDraw_callbackImpl,
        LeadingMarginSpanAccessor::GetGetLeadingMargin_callbackImpl,
        LeadingMarginSpanAccessor::SetGetLeadingMargin_callbackImpl,
    };
    return &LeadingMarginSpanAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
