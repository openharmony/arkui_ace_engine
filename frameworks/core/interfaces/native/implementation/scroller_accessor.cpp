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
namespace ScrollerAccessor {

static void DestroyPeer(ScrollerPeer *peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}

ScrollerPeer* CtorImpl()
{
    auto peer = Referenced::MakeRefPtr<ScrollerPeer>();
    peer->IncRefCount();
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void ScrollToImpl(ScrollerPeer* peer,
                  const Ark_ScrollOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollTo(options);
}
void ScrollEdgeImpl(ScrollerPeer* peer,
                    enum Ark_Edge value,
                    const Opt_ScrollEdgeOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollEdge(value, options);
}
void FlingImpl(ScrollerPeer* peer,
               const Ark_Number* velocity)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerFling(velocity);
}
void ScrollPage0Impl(ScrollerPeer* peer,
                     const Ark_Literal_Boolean_next* value)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollPage0(value);
}
void ScrollPage1Impl(ScrollerPeer* peer,
                     const Ark_Literal_Boolean_next_Axis_direction* value)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollPage1(value);
}
Ark_NativePointer CurrentOffsetImpl(ScrollerPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr); // need to fix default value
    return peer->TriggerCurrentOffset();
}
void ScrollToIndexImpl(ScrollerPeer* peer,
                       const Ark_Number* value,
                       const Opt_Boolean* smooth,
                       const Opt_ScrollAlign* align,
                       const Opt_ScrollToIndexOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollToIndex(value, smooth, align, options);
}
void ScrollByImpl(ScrollerPeer* peer,
                  const Ark_Length* dx,
                  const Ark_Length* dy)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollBy(dx, dy);
}
Ark_Boolean IsAtEndImpl(ScrollerPeer* peer)
{
    CHECK_NULL_RETURN(peer, false); // need to fix default value
    return peer->TriggerIsAtEnd();
}
Ark_NativePointer GetItemRectImpl(ScrollerPeer* peer,
                                  const Ark_Number* index)
{
    CHECK_NULL_RETURN(peer, nullptr); // need to fix default value
    return peer->TriggerGetItemRect(index);
}
Ark_Int32 GetItemIndexImpl(ScrollerPeer* peer,
                           const Ark_Number* x,
                           const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer, -1); // need to fix default value
    return peer->TriggerGetItemIndex(x, y);
}
} // ScrollerAccessor
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
{
    static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
        ScrollerAccessor::CtorImpl,
        ScrollerAccessor::GetFinalizerImpl,
        ScrollerAccessor::ScrollToImpl,
        ScrollerAccessor::ScrollEdgeImpl,
        ScrollerAccessor::FlingImpl,
        ScrollerAccessor::ScrollPage0Impl,
        ScrollerAccessor::ScrollPage1Impl,
        ScrollerAccessor::CurrentOffsetImpl,
        ScrollerAccessor::ScrollToIndexImpl,
        ScrollerAccessor::ScrollByImpl,
        ScrollerAccessor::IsAtEndImpl,
        ScrollerAccessor::GetItemRectImpl,
        ScrollerAccessor::GetItemIndexImpl,
    };
    return &ScrollerAccessorImpl;
}

}
