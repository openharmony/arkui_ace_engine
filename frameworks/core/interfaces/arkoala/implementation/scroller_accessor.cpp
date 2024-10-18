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

#include "scroller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollerModifier {

static void DestroyPeer(ScrollerPeerImpl *peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}

Ark_NativePointer CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<ScrollerPeerImpl>();
    peerImpl->IncRefCount();
    return Referenced::RawPtr(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void ScrollToImpl(ScrollerPeer* peer,
                  const Ark_ScrollOptions* options)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollTo(options);
}
void ScrollEdgeImpl(ScrollerPeer* peer,
                    enum Ark_Edge value,
                    const Opt_ScrollEdgeOptions* options)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollEdge(value, options);
}
void FlingImpl(ScrollerPeer* peer,
               const Ark_Number* velocity)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerFling(velocity);
}
void ScrollPage0Impl(ScrollerPeer* peer,
                     const Ark_Literal_Boolean_next* value)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollPage0(value);
}
void ScrollPage1Impl(ScrollerPeer* peer,
                     const Ark_Literal_Boolean_next_Axis_direction* value)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollPage1(value);
}
Ark_NativePointer CurrentOffsetImpl(ScrollerPeer* peer)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr); // need to fix default value
    return peerImpl->TriggerCurrentOffset();
}
void ScrollToIndexImpl(ScrollerPeer* peer,
                       const Ark_Number* value,
                       const Opt_Boolean* smooth,
                       const Opt_ScrollAlign* align,
                       const Opt_ScrollToIndexOptions* options)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollToIndex(value, smooth, align, options);
}
void ScrollByImpl(ScrollerPeer* peer,
                  const Ark_Length* dx,
                  const Ark_Length* dy)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerScrollBy(dx, dy);
}
Ark_Boolean IsAtEndImpl(ScrollerPeer* peer)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, false); // need to fix default value
    return peerImpl->TriggerIsAtEnd();
}
Ark_NativePointer GetItemRectImpl(ScrollerPeer* peer,
                                  const Ark_Number* index)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr); // need to fix default value
    return peerImpl->TriggerGetItemRect(index);
}
Ark_Int32 GetItemIndexImpl(ScrollerPeer* peer,
                           const Ark_Number* x,
                           const Ark_Number* y)
{
    auto peerImpl = reinterpret_cast<ScrollerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, -1); // need to fix default value
    return peerImpl->TriggerGetItemIndex(x, y);
}
} // ScrollerModifier
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
{
    static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
        ScrollerModifier::CtorImpl,
        ScrollerModifier::GetFinalizerImpl,
        ScrollerModifier::ScrollToImpl,
        ScrollerModifier::ScrollEdgeImpl,
        ScrollerModifier::FlingImpl,
        ScrollerModifier::ScrollPage0Impl,
        ScrollerModifier::ScrollPage1Impl,
        ScrollerModifier::CurrentOffsetImpl,
        ScrollerModifier::ScrollToIndexImpl,
        ScrollerModifier::ScrollByImpl,
        ScrollerModifier::IsAtEndImpl,
        ScrollerModifier::GetItemRectImpl,
        ScrollerModifier::GetItemIndexImpl,
    };
    return &ScrollerAccessorImpl;
}

}
