/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"
#include "ui_scrollable_event_peer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIScrollableCommonEventAccessor {
void DestroyPeerImpl(Ark_UIScrollableCommonEvent peer)
{
    CHECK_NULL_VOID(peer);
    PeerUtils::DestroyPeer(peer);
}
Ark_UIScrollableCommonEvent ConstructImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventPeer = PeerUtils::CreatePeer<UIScrollableCommonEventPeer>();
    eventPeer->node = frameNode;
    return eventPeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnReachStartImpl(Ark_UIScrollableCommonEvent peer,
                         const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnReachStart = Converter::GetOptPtr(callback_);
    if (arkOnReachStart) {
        auto onReachStart = [arkCallback = CallbackHelper(arkOnReachStart.value())]() { arkCallback.InvokeSync(); };
        ScrollableModelStatic::SetOnReachStart(rawPtr, std::move(onReachStart));
    } else {
        ScrollableModelStatic::SetOnReachStart(rawPtr, nullptr);
    }
}
void SetOnReachEndImpl(Ark_UIScrollableCommonEvent peer,
                       const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnReachEnd = Converter::GetOptPtr(callback_);
    if (arkOnReachEnd) {
        auto onReachEnd = [arkCallback = CallbackHelper(arkOnReachEnd.value())]() { arkCallback.InvokeSync(); };
        ScrollableModelStatic::SetOnReachEnd(rawPtr, std::move(onReachEnd));
    } else {
        ScrollableModelStatic::SetOnReachEnd(rawPtr, nullptr);
    }
}
void SetOnScrollStartImpl(Ark_UIScrollableCommonEvent peer,
                          const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollStart = Converter::GetOptPtr(callback_);
    if (arkOnScrollStart) {
        auto onScrollStart = [arkCallback = CallbackHelper(arkOnScrollStart.value())]() { arkCallback.InvokeSync(); };
        ScrollableModelStatic::SetOnScrollStart(rawPtr, std::move(onScrollStart));
    } else {
        ScrollableModelStatic::SetOnScrollStart(rawPtr, nullptr);
    }
}
void SetOnScrollStopImpl(Ark_UIScrollableCommonEvent peer,
                         const Opt_Callback_Void* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollStop = Converter::GetOptPtr(callback_);
    if (arkOnScrollStop) {
        auto onScrollStop = [arkCallback = CallbackHelper(arkOnScrollStop.value())]() { arkCallback.InvokeSync(); };
        ScrollableModelStatic::SetOnScrollStop(rawPtr, std::move(onScrollStop));
    } else {
        ScrollableModelStatic::SetOnScrollStop(rawPtr, nullptr);
    }
}
void SetOnScrollFrameBeginImpl(Ark_UIScrollableCommonEvent peer,
                               const Opt_OnScrollFrameBeginCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollFrameBegin = Converter::GetOptPtr(callback_);
    if (arkOnScrollFrameBegin) {
        auto onScrollFrameBegin = [arkCallback = CallbackHelper(arkOnScrollFrameBegin.value())](
                                      Dimension offset, ScrollState state) -> ScrollFrameResult {
            ScrollFrameResult defaultResult { .offset = offset };
            Ark_Float64 arkOffset = Converter::ArkValue<Ark_Float64>(offset);
            Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
            return arkCallback
                .InvokeWithOptConvertResult<ScrollFrameResult, Ark_OnScrollFrameBeginHandlerResult,
                    Callback_OnScrollFrameBeginHandlerResult_Void>(arkOffset, arkState)
                .value_or(defaultResult);
        };
        ScrollableModelStatic::SetOnScrollFrameBegin(rawPtr, std::move(onScrollFrameBegin));
    } else {
        ScrollableModelStatic::SetOnScrollFrameBegin(rawPtr, nullptr);
    }
}
} // UIScrollableCommonEventAccessor
const GENERATED_ArkUIUIScrollableCommonEventAccessor* GetUIScrollableCommonEventAccessor()
{
    static const GENERATED_ArkUIUIScrollableCommonEventAccessor UIScrollableCommonEventAccessorImpl {
        UIScrollableCommonEventAccessor::DestroyPeerImpl,
        UIScrollableCommonEventAccessor::ConstructImpl,
        UIScrollableCommonEventAccessor::GetFinalizerImpl,
        UIScrollableCommonEventAccessor::SetOnReachStartImpl,
        UIScrollableCommonEventAccessor::SetOnReachEndImpl,
        UIScrollableCommonEventAccessor::SetOnScrollStartImpl,
        UIScrollableCommonEventAccessor::SetOnScrollStopImpl,
        UIScrollableCommonEventAccessor::SetOnScrollFrameBeginImpl,
    };
    return &UIScrollableCommonEventAccessorImpl;
}
}
