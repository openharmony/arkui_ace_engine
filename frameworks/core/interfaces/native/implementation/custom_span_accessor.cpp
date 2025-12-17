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

#include "custom_span_peer.h"
#include "draw_context_peer.h"

#include "core/components_ng/pattern/text/text_styles.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_CustomSpanDrawInfo& dst, const CustomSpanOptions& src, ConvContext *ctx)
{
    dst.x = ArkValue<Ark_Float64>(src.x);
    dst.lineTop = ArkValue<Ark_Float64>(src.lineTop);
    dst.lineBottom = ArkValue<Ark_Float64>(src.lineBottom);
    dst.baseline = ArkValue<Ark_Float64>(src.baseline);
}

void AssignArkValue(Ark_CustomSpanMeasureInfo& dst, const CustomSpanMeasureInfo& src, ConvContext *ctx)
{
    dst.fontSize = ArkValue<Ark_Float64>(src.fontSize);
}

void AssignArkValue(Ark_CustomSpanMetrics& dst, const CustomSpanMetrics& src, ConvContext *ctx)
{
    dst.width = ArkValue<Ark_Float64>(src.width);
    dst.height = ArkValue<Opt_Float64>(src.height);
}

template<>
CustomSpanMetrics Convert(const Ark_CustomSpanMetrics& src)
{
    return CustomSpanMetrics {
        .width = Converter::Convert<float>(src.width),
        .height = Converter::OptConvert<float>(src.height)
    };
}

template<>
CustomSpanOptions Convert(const Ark_CustomSpanDrawInfo& src)
{
    return CustomSpanOptions {
        .x = Convert<float>(src.x),
        .lineTop = Convert<float>(src.lineTop),
        .lineBottom = Convert<float>(src.lineBottom),
        .baseline = Convert<float>(src.baseline),
    };
}

template<>
CustomSpanMeasureInfo Convert(const Ark_CustomSpanMeasureInfo& src)
{
    return CustomSpanMeasureInfo {
        .fontSize = Convert<float>(src.fontSize)
    };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CustomSpanAccessor {
void DestroyPeerImpl(Ark_CustomSpan peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_CustomSpan ConstructImpl()
{
    return PeerUtils::CreatePeer<CustomSpanPeer>(AceType::MakeRefPtr<OHOS::Ace::NG::CustomSpanImpl>());
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvalidateImpl(Ark_CustomSpan peer)
{
    CHECK_NULL_VOID(peer && peer->span);
    peer->span->Invalidate();
}
Callback_CustomSpanMeasureInfo_CustomSpanMetrics GetOnMeasure_callbackImpl(Ark_CustomSpan peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto handler = [span = peer->span](const Ark_CustomSpanMeasureInfo arkInfo,
        const Callback_CustomSpanMetrics_Void continuation) {
        CHECK_NULL_VOID(span);
        auto onMeasureFunc = span->GetOnMeasure();
        CHECK_NULL_VOID(onMeasureFunc);
        auto info = Converter::Convert<CustomSpanMeasureInfo>(arkInfo);
        auto res = (*onMeasureFunc)(info);
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_CustomSpanMetrics>(res));
    };
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_CustomSpanMeasureInfo_CustomSpanMetrics,
        std::function<void(Ark_CustomSpanMeasureInfo, Callback_CustomSpanMetrics_Void)>>(handler);
    return callback;
}
void SetOnMeasure_callbackImpl(Ark_CustomSpan peer,
                               const Callback_CustomSpanMeasureInfo_CustomSpanMetrics* onMeasure_callback)
{
    CHECK_NULL_VOID(peer && peer->span);
    if (onMeasure_callback) {
        auto callback = [arkCallback = CallbackHelper(*onMeasure_callback)](const CustomSpanMeasureInfo& measureInfo) {
            auto arkMeasureInfo = Converter::ArkValue<Ark_CustomSpanMeasureInfo>(measureInfo);
            std::optional<CustomSpanMetrics> result = arkCallback.InvokeWithOptConvertResult<CustomSpanMetrics,
                Ark_CustomSpanMetrics, Callback_CustomSpanMetrics_Void>(arkMeasureInfo);
            return result.value_or(CustomSpanMetrics());
        };
        peer->span->SetOnMeasure(callback);
    } else {
        peer->span->SetOnMeasure(nullptr);
    }
}
Callback_DrawContext_CustomSpanDrawInfo_Void GetOnDraw_callbackImpl(Ark_CustomSpan peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto handler = [span = peer->span](Ark_DrawContext arkCtxPtr, Ark_CustomSpanDrawInfo arkInfo) {
        CHECK_NULL_VOID(span);
        auto onDrawFunc = span->GetOnDraw();
        CHECK_NULL_VOID(onDrawFunc);
        CHECK_NULL_VOID(arkCtxPtr);
        (*onDrawFunc)(*arkCtxPtr, Converter::Convert<CustomSpanOptions>(arkInfo));
    };
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_DrawContext_CustomSpanDrawInfo_Void,
        std::function<void(Ark_DrawContext, Ark_CustomSpanDrawInfo)>>(handler);
    return callback;
}
void SetOnDraw_callbackImpl(Ark_CustomSpan peer,
                            const Callback_DrawContext_CustomSpanDrawInfo_Void* onDraw_callback)
{
    CHECK_NULL_VOID(peer && peer->span);
    if (onDraw_callback) {
        auto callback = [arkCallback = CallbackHelper(*onDraw_callback)](NG::DrawingContext& drawingContext,
            const CustomSpanOptions& customSpanOptions) {
            auto arkCtxPtr = reinterpret_cast<Ark_DrawContext>(std::addressof(drawingContext));
            auto arkInfo = Converter::ArkValue<Ark_CustomSpanDrawInfo>(customSpanOptions);
            arkCallback.InvokeSync(arkCtxPtr, arkInfo);
        };
        peer->span->SetOnDraw(callback);
    } else {
        peer->span->SetOnDraw(nullptr);
    }
}
} // CustomSpanAccessor
const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
{
    static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
        CustomSpanAccessor::DestroyPeerImpl,
        CustomSpanAccessor::ConstructImpl,
        CustomSpanAccessor::GetFinalizerImpl,
        CustomSpanAccessor::InvalidateImpl,
        CustomSpanAccessor::GetOnMeasure_callbackImpl,
        CustomSpanAccessor::SetOnMeasure_callbackImpl,
        CustomSpanAccessor::GetOnDraw_callbackImpl,
        CustomSpanAccessor::SetOnDraw_callbackImpl,
    };
    return &CustomSpanAccessorImpl;
}

}
