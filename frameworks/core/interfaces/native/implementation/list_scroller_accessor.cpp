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
#include "list_scroller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<Callback_Void>& dst, const Ark_CloseSwipeActionOptions& src)
{
    dst = Converter::OptConvert<Callback_Void>(src.onFinish);
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListScrollerAccessor {
void DestroyPeerImpl(Ark_ListScroller peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_ListScroller CtorImpl()
{
    auto peer = Referenced::MakeRefPtr<ListScrollerPeer>();
    peer->IncRefCount();
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RectResult GetItemRectInGroupImpl(Ark_VMContext vmContext,
                                      Ark_ListScroller peer,
                                      const Ark_Number* index,
                                      const Ark_Number* indexInGroup)
{
    auto errValue = Converter::ArkValue<Ark_RectResult>(Rect{});
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(index, errValue);
    CHECK_NULL_RETURN(indexInGroup, errValue);

    auto scrollController = peer->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerAccessor::GetItemRectInGroupImpl. Controller isn't bound to a component.");
        return errValue;
    }

    int32_t convIndex = Converter::Convert<int32_t>(*index);
    int32_t convIndexInGroup = Converter::Convert<int32_t>(*indexInGroup);
    auto rect = scrollController->GetItemRectInGroup(convIndex, convIndexInGroup);
    return Converter::ArkValue<Ark_RectResult>(rect);
}
void ScrollToItemInGroupImpl(Ark_VMContext vmContext,
                             Ark_ListScroller peer,
                             const Ark_Number* index,
                             const Ark_Number* indexInGroup,
                             const Opt_Boolean* smooth,
                             const Opt_ScrollAlign* align)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(index);
    CHECK_NULL_VOID(indexInGroup);

    auto scrollController = peer->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerAccessor::ScrollToItemInGroupImpl. Controller isn't bound to a component.");
        return;
    }

    int32_t indexValue = Converter::Convert<int32_t>(*index);
    int32_t indexInGroupValue = Converter::Convert<int32_t>(*indexInGroup);
    auto smoothValue = smooth ? Converter::OptConvert<bool>(*smooth) : std::nullopt;
    auto alignValue = align ? Converter::OptConvert<ScrollAlign>(*align) : std::nullopt;
    scrollController->JumpToItemInGroup(indexValue, indexInGroupValue,
        smoothValue.value_or(false), alignValue.value_or(ScrollAlign::NONE));
}
void CloseAllSwipeActionsImpl(Ark_VMContext vmContext,
                              Ark_ListScroller peer,
                              const Opt_CloseSwipeActionOptions* options)
{
    CHECK_NULL_VOID(peer);
    auto scrollController = peer->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerAccessor::CloseAllSwipeActionsImpl. Controller isn't bound to a component.");
        return;
    }

    auto funcOpt = options ? Converter::OptConvert<Callback_Void>(*options) : std::nullopt;
    if (funcOpt.has_value()) {
        auto func =  [arkCallback = CallbackHelper(funcOpt.value())]() { arkCallback.Invoke(); };
        scrollController->CloseAllSwipeActions(std::move(func));
    }
}
Ark_VisibleListContentInfo GetVisibleListContentInfoImpl(Ark_VMContext vmContext,
                                                         Ark_ListScroller peer,
                                                         const Ark_Number* x,
                                                         const Ark_Number* y)
{
    auto errValue = Converter::ArkValue<Ark_VisibleListContentInfo>(ListItemGroupIndex{});
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(x, errValue);
    CHECK_NULL_RETURN(y, errValue);

    auto scrollController = peer->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerPeerAccessor::GetVisibleListContentInfoImpl. Controller isn't bound to a component.");
        return errValue;
    }

    auto convX = Converter::Convert<float>(*x);
    auto convY = Converter::Convert<float>(*y);
    auto retVal = scrollController->GetItemIndexInGroup(convX, convY);
    return Converter::ArkValue<Ark_VisibleListContentInfo>(retVal);
}
} // ListScrollerAccessor
const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor()
{
    static const GENERATED_ArkUIListScrollerAccessor ListScrollerAccessorImpl {
        ListScrollerAccessor::DestroyPeerImpl,
        ListScrollerAccessor::CtorImpl,
        ListScrollerAccessor::GetFinalizerImpl,
        ListScrollerAccessor::GetItemRectInGroupImpl,
        ListScrollerAccessor::ScrollToItemInGroupImpl,
        ListScrollerAccessor::CloseAllSwipeActionsImpl,
        ListScrollerAccessor::GetVisibleListContentInfoImpl,
    };
    return &ListScrollerAccessorImpl;
}

}
