/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/interfaces/native/implementation/ui_scrollable_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIWaterFlowEventAccessor {
void DestroyPeerImpl(Ark_UIWaterFlowEvent peer)
{
    CHECK_NULL_VOID(peer);
    PeerUtils::DestroyPeer(peer);
}
Ark_UIWaterFlowEvent ConstructImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventPeer = PeerUtils::CreatePeer<UIWaterFlowEventPeer>();
    eventPeer->node = frameNode;
    return eventPeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnWillScrollImpl(Ark_UIWaterFlowEvent peer,
                         const Opt_OnWillScrollCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnWillScroll = Converter::GetOptPtr(callback_);
    if (arkOnWillScroll) {
        auto onWillScroll = [arkCallback = CallbackHelper(arkOnWillScroll.value())](
                                Dimension offset, ScrollState state, ScrollSource source) -> ScrollFrameResult {
            ScrollFrameResult defaultResult { .offset = offset };
            Ark_Float64 arkOffset = Converter::ArkValue<Ark_Float64>(offset);
            Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
            Ark_ScrollSource arkSource = Converter::ArkValue<Ark_ScrollSource>(source);
            auto arkResult = arkCallback.InvokeWithOptConvertResult<ScrollFrameResult, Opt_ScrollResult,
                Callback_Opt_ScrollResult_Void>(arkOffset, arkState, arkSource);
            return arkResult.value_or(defaultResult);
        };
        ScrollableModelStatic::SetOnWillScroll(rawPtr, std::move(onWillScroll));
    } else {
        ScrollableModelStatic::SetOnWillScroll(rawPtr, nullptr);
    }
}
void SetOnDidScrollImpl(Ark_UIWaterFlowEvent peer,
                        const Opt_OnScrollCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnDidScroll = Converter::GetOptPtr(callback_);
    if (arkOnDidScroll) {
        auto onDidScroll = [arkCallback = CallbackHelper(arkOnDidScroll.value())](
                               Dimension offsetIn, ScrollState stateIn) {
            auto arkOffset = Converter::ArkValue<Ark_Float64>(offsetIn);
            auto arkState = Converter::ArkValue<Ark_ScrollState>(stateIn);
            arkCallback.Invoke(arkOffset, arkState);
        };
        ScrollableModelStatic::SetOnDidScroll(rawPtr, std::move(onDidScroll));
    } else {
        ScrollableModelStatic::SetOnDidScroll(rawPtr, nullptr);
    }
}
void SetOnScrollIndexImpl(Ark_UIWaterFlowEvent peer,
                          const Opt_OnWaterFlowScrollIndexCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollIndex = Converter::GetOptPtr(callback_);
    if (arkOnScrollIndex) {
        auto onScrollIndex = [arkCallback = CallbackHelper(arkOnScrollIndex.value())](
                                 const int32_t first, const int32_t last) {
            auto arkFirst = Converter::ArkValue<Ark_Int32>(first);
            auto arkLast = Converter::ArkValue<Ark_Int32>(last);
            arkCallback.Invoke(arkFirst, arkLast);
        };
        WaterFlowModelStatic::SetOnScrollIndex(rawPtr, std::move(onScrollIndex));
    } else {
        WaterFlowModelStatic::SetOnScrollIndex(rawPtr, nullptr);
    }
}
} // UIWaterFlowEventAccessor
const GENERATED_ArkUIUIWaterFlowEventAccessor* GetUIWaterFlowEventStaticAccessor()
{
    static const GENERATED_ArkUIUIWaterFlowEventAccessor UIWaterFlowEventAccessorImpl {
        UIWaterFlowEventAccessor::DestroyPeerImpl,
        UIWaterFlowEventAccessor::ConstructImpl,
        UIWaterFlowEventAccessor::GetFinalizerImpl,
        UIWaterFlowEventAccessor::SetOnWillScrollImpl,
        UIWaterFlowEventAccessor::SetOnDidScrollImpl,
        UIWaterFlowEventAccessor::SetOnScrollIndexImpl,
    };
    return &UIWaterFlowEventAccessorImpl;
}
}
