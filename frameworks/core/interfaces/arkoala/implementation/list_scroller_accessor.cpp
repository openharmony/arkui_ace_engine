/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "list_scroller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListScrollerAccessor {
static void DestroyPeer(ListScrollerPeerImpl* peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_NativePointer CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<ListScrollerPeerImpl>();
    peerImpl->IncRefCount();
    return Referenced::RawPtr(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeer);
}
Ark_NativePointer GetItemRectInGroupImpl(ListScrollerPeer* peer,
                                         const Ark_Number* index,
                                         const Ark_Number* indexInGroup)
{
    LOGE("ListScrollerAccessor::GetItemRectInGroupImpl is not implemented.");
    // wait for Ark_NativePointer change to another type which is acceptable to "Rect" data
    auto peerImpl = reinterpret_cast<ListScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, 0); // need to fix a return value
    CHECK_NULL_RETURN(index, 0); // need to fix a return value
    CHECK_NULL_RETURN(indexInGroup, 0); // need to fix a return value

    auto scrollController = peerImpl->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerAccessor::GetItemRectInGroupImpl. Controller isn't bound to a component.");
        return 0; // need to fix a return value
    }

    int32_t convIndex = Converter::Convert<int32_t>(*index);
    int32_t convIndexInGroup = Converter::Convert<int32_t>(*indexInGroup);
    // get a result of GetItemRectInGroup to return it
    scrollController->GetItemRectInGroup(convIndex, convIndexInGroup);
    return 0; // need to fix a return value
}
void ScrollToItemInGroupImpl(ListScrollerPeer* peer,
                             const Ark_Number* index,
                             const Ark_Number* indexInGroup,
                             const Opt_Boolean* smooth,
                             const Opt_ScrollAlign* align)
{
    auto peerImpl = reinterpret_cast<ListScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(index);
    CHECK_NULL_VOID(indexInGroup);

    auto scrollController = peerImpl->GetController().Upgrade();
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
void CloseAllSwipeActionsImpl(ListScrollerPeer* peer,
                              const Opt_CloseSwipeActionOptions* options)
{
    auto peerImpl = reinterpret_cast<ListScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    LOGE("ListScrollerAccessor::CloseAllSwipeActionsImpl. Callback isn't implemented yet.");
}
Ark_NativePointer GetVisibleListContentInfoImpl(ListScrollerPeer* peer,
                                                const Ark_Number* x,
                                                const Ark_Number* y)
{
    LOGE("ListScrollerAccessor::GetVisibleListContentInfoImpl is not implemented.");
    // wait for Ark_NativePointer change to another type which is acceptable to "ListItemGroupIndex" data
    auto peerImpl = reinterpret_cast<ListScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, 0); // need to fix a return value
    CHECK_NULL_RETURN(x, 0); // need to fix a return value
    CHECK_NULL_RETURN(y, 0); // need to fix a return value

    auto scrollController = peerImpl->GetController().Upgrade();
    if (!scrollController) {
        LOGE("ListScrollerPeerAccessor::GetVisibleListContentInfoImpl. Controller isn't bound to a component.");
        return 0; // need to fix a return value
    }

    auto convX = Converter::Convert<float>(*x);
    auto convY = Converter::Convert<float>(*y);
    // get a result of GetItemIndexInGroup to return it
    scrollController->GetItemIndexInGroup(convX, convY);
    return 0; // need to fix a return value
}
} // ListScrollerAccessor
const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor()
{
    static const GENERATED_ArkUIListScrollerAccessor ListScrollerAccessorImpl {
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
