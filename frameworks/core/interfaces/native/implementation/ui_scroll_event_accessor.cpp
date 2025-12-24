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
#include "core/components_ng/pattern/scroll/scroll_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"


namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIScrollEventAccessor {
void DestroyPeerImpl(Ark_UIScrollEvent peer)
{
    CHECK_NULL_VOID(peer);
    PeerUtils::DestroyPeer(peer);
}
Ark_UIScrollEvent ConstructImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventPeer = PeerUtils::CreatePeer<UIScrollEventPeer>();
    eventPeer->node = frameNode;
    return eventPeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnWillScrollImpl(Ark_UIScrollEvent peer,
                         const Opt_ScrollOnWillScrollCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnWillScroll = Converter::GetOptPtr(callback_);
    if (arkOnWillScroll) {
        auto onWillScroll = [arkCallback = CallbackHelper(arkOnWillScroll.value())](Dimension xOffset,
                                Dimension yOffset, ScrollState state, ScrollSource source) -> TwoDimensionScrollResult {
            TwoDimensionScrollResult defaultResult { .xOffset = xOffset, .yOffset = yOffset };
            Ark_Float64 arkOffsetX = Converter::ArkValue<Ark_Float64>(xOffset);
            Ark_Float64 arkOffsetY = Converter::ArkValue<Ark_Float64>(yOffset);
            Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
            Ark_ScrollSource arkSource = Converter::ArkValue<Ark_ScrollSource>(source);
            auto arkResult = arkCallback.InvokeWithOptConvertResult<TwoDimensionScrollResult, Opt_OffsetResult,
                Callback_Opt_OffsetResult_Void>(arkOffsetX, arkOffsetY, arkState, arkSource);
            return arkResult.value_or(defaultResult);
        };
        ScrollModelStatic::SetOnWillScroll(rawPtr, std::move(onWillScroll));
    } else {
        ScrollModelStatic::SetOnWillScroll(rawPtr, nullptr);
    }
}
void SetOnDidScrollImpl(Ark_UIScrollEvent peer,
                        const Opt_ScrollOnScrollCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnDidScroll = Converter::GetOptPtr(callback_);
    if (arkOnDidScroll) {
        auto onDidScroll = [arkCallback = CallbackHelper(arkOnDidScroll.value())](
                               Dimension xOffsetIn, Dimension yOffsetIn, ScrollState stateIn) {
            auto arkOffsetX = Converter::ArkValue<Ark_Float64>(xOffsetIn);
            auto arkOffsetY = Converter::ArkValue<Ark_Float64>(yOffsetIn);
            auto arkState = Converter::ArkValue<Ark_ScrollState>(stateIn);
            arkCallback.Invoke(arkOffsetX, arkOffsetY, arkState);
        };
        ScrollModelStatic::SetOnDidScroll(rawPtr, std::move(onDidScroll));
    } else {
        ScrollModelStatic::SetOnDidScroll(rawPtr, nullptr);
    }
}
} // UIScrollEventAccessor
const GENERATED_ArkUIUIScrollEventAccessor* GetUIScrollEventAccessor()
{
    static const GENERATED_ArkUIUIScrollEventAccessor UIScrollEventAccessorImpl {
        UIScrollEventAccessor::DestroyPeerImpl,
        UIScrollEventAccessor::ConstructImpl,
        UIScrollEventAccessor::GetFinalizerImpl,
        UIScrollEventAccessor::SetOnWillScrollImpl,
        UIScrollEventAccessor::SetOnDidScrollImpl,
    };
    return &UIScrollEventAccessorImpl;
}
}
