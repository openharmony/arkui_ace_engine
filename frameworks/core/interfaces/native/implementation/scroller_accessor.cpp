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

#include "scroller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollerAccessor {
void DestroyPeerImpl(Ark_Scroller peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_Scroller ConstructImpl()
{
    auto peer = Referenced::MakeRefPtr<ScrollerPeer>();
    peer->IncRefCount();
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ScrollToImpl(Ark_Scroller peer,
                  const Ark_ScrollOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollTo(options);
}
void ScrollEdgeImpl(Ark_Scroller peer,
                    Ark_Edge value,
                    const Opt_ScrollEdgeOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollEdge(value, options);
}
void FlingImpl(Ark_Scroller peer,
               Ark_Float64 velocity)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerFling(velocity);
}
void ScrollPageImpl(Ark_Scroller peer,
                    const Ark_ScrollPageOptions* value)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollPage0(value);
}
Ark_OffsetResult CurrentOffsetImpl(Ark_Scroller peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->TriggerCurrentOffset();
}
void ScrollToIndexImpl(Ark_Scroller peer,
                       Ark_Int32 value,
                       const Opt_Boolean* smooth,
                       const Opt_ScrollAlign* align,
                       const Opt_ScrollToIndexOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollToIndex(value, smooth, align, options);
}
void ScrollByImpl(Ark_Scroller peer,
                  const Ark_Length* dx,
                  const Ark_Length* dy)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    auto xOffset = Converter::OptConvert<Dimension>(*dx).value_or(Dimension());
    auto yOffset = Converter::OptConvert<Dimension>(*dy).value_or(Dimension());
    peer->TriggerScrollBy(xOffset, yOffset);
}
Ark_Boolean IsAtEndImpl(Ark_Scroller peer)
{
    CHECK_NULL_RETURN(peer, false); // need to fix default value
    return peer->TriggerIsAtEnd();
}
Ark_RectResult GetItemRectImpl(Ark_Scroller peer,
                               Ark_Int32 index)
{
    CHECK_NULL_RETURN(peer, {}); // need to fix default value
    return peer->TriggerGetItemRect(index);
}
Ark_Int32 GetItemIndexImpl(Ark_Scroller peer,
                           Ark_Float64 x,
                           Ark_Float64 y)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(-1);
    CHECK_NULL_RETURN(peer, errValue); // need to fix default value
    auto res = peer->TriggerGetItemIndex(x, y);
    return Converter::ArkValue<Ark_Int32>(res);
}
} // ScrollerAccessor
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
{
    static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
        ScrollerAccessor::DestroyPeerImpl,
        ScrollerAccessor::ConstructImpl,
        ScrollerAccessor::GetFinalizerImpl,
        ScrollerAccessor::ScrollToImpl,
        ScrollerAccessor::ScrollEdgeImpl,
        ScrollerAccessor::FlingImpl,
        ScrollerAccessor::ScrollPageImpl,
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
