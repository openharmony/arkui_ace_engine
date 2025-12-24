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
#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIListEventAccessor {
void DestroyPeerImpl(Ark_UIListEvent peer)
{
    CHECK_NULL_VOID(peer);
    PeerUtils::DestroyPeer(peer);
}
Ark_UIListEvent ConstructImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventPeer = PeerUtils::CreatePeer<UIListEventPeer>();
    eventPeer->node = frameNode;
    return eventPeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetOnWillScrollImpl(Ark_UIListEvent peer,
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
void SetOnDidScrollImpl(Ark_UIListEvent peer,
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
void SetOnScrollIndexImpl(Ark_UIListEvent peer,
                          const Opt_OnListScrollIndexCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollIndex = Converter::GetOptPtr(callback_);
    if (arkOnScrollIndex) {
        auto onScrollIndex = [arkCallback = CallbackHelper(arkOnScrollIndex.value())](
                                 const int32_t start, const int32_t end, const int32_t center) {
            auto arkStart = Converter::ArkValue<Ark_Int32>(start);
            auto arkEnd = Converter::ArkValue<Ark_Int32>(end);
            auto arkCenter = Converter::ArkValue<Ark_Int32>(center);
            arkCallback.Invoke(arkStart, arkEnd, arkCenter);
        };
        ListModelStatic::SetOnScrollIndex(rawPtr, std::move(onScrollIndex));
    } else {
        ListModelStatic::SetOnScrollIndex(rawPtr, nullptr);
    }
}
void SetOnScrollVisibleContentChangeImpl(Ark_UIListEvent peer,
                                         const Opt_OnScrollVisibleContentChangeCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto refPtr = peer->node.Upgrade();
    CHECK_NULL_VOID(refPtr);
    auto rawPtr = Referenced::RawPtr(refPtr);
    auto arkOnScrollVisibleContentChange = Converter::GetOptPtr(callback_);
    if (arkOnScrollVisibleContentChange) {
        auto onScrollVisibleContentChange = [arkCallback = CallbackHelper(arkOnScrollVisibleContentChange.value())](
                                                const ListItemIndex& start, const ListItemIndex& end) {
            auto arkStartItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(start);
            auto arkEndItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(end);
            arkCallback.Invoke(arkStartItemInfo, arkEndItemInfo);
        };
        ListModelStatic::SetOnScrollVisibleContentChange(rawPtr, std::move(onScrollVisibleContentChange));
    } else {
        ListModelStatic::SetOnScrollVisibleContentChange(rawPtr, nullptr);
    }
}
} // UIListEventAccessor
const GENERATED_ArkUIUIListEventAccessor* GetUIListEventAccessor()
{
    static const GENERATED_ArkUIUIListEventAccessor UIListEventAccessorImpl {
        UIListEventAccessor::DestroyPeerImpl,
        UIListEventAccessor::ConstructImpl,
        UIListEventAccessor::GetFinalizerImpl,
        UIListEventAccessor::SetOnWillScrollImpl,
        UIListEventAccessor::SetOnDidScrollImpl,
        UIListEventAccessor::SetOnScrollIndexImpl,
        UIListEventAccessor::SetOnScrollVisibleContentChangeImpl,
    };
    return &UIListEventAccessorImpl;
}
}
