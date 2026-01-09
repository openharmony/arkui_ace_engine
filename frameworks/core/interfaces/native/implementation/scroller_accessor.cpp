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
void ScrollToImpl(Ark_VMContext vmContext,
                  Ark_Scroller peer,
                  const Ark_ScrollOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollTo(vmContext, options);
}
void ScrollEdgeImpl(Ark_VMContext vmContext,
                    Ark_Scroller peer,
                    Ark_Edge value,
                    const Opt_ScrollEdgeOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollEdge(vmContext, value, options);
}
void FlingImpl(Ark_VMContext vmContext,
               Ark_Scroller peer,
               Ark_Float64 velocity)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerFling(vmContext, velocity);
}
void ScrollPageImpl(Ark_VMContext vmContext,
                    Ark_Scroller peer,
                    const Ark_ScrollPageOptions* value)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollPage0(vmContext, value);
}
Opt_OffsetResult CurrentOffsetImpl(Ark_VMContext vmContext,
                                   Ark_Scroller peer)
{
    auto invalid = Converter::ArkValue<Opt_OffsetResult>();
    CHECK_NULL_RETURN(peer, invalid);
    return peer->TriggerCurrentOffset(vmContext);
}
Opt_OffsetResult OffsetImpl(Ark_Scroller peer)
{
    auto invalid = Converter::ArkValue<Opt_OffsetResult>();
    CHECK_NULL_RETURN(peer, invalid);
    return peer->TriggerOffset();
}
void ScrollToIndexImpl(Ark_VMContext vmContext,
                       Ark_Scroller peer,
                       Ark_Int32 value,
                       const Opt_Boolean* smooth,
                       const Opt_ScrollAlign* align,
                       const Opt_ScrollToIndexOptions* options)
{
    CHECK_NULL_VOID(peer);
    peer->TriggerScrollToIndex(vmContext, value, smooth, align, options);
}
void ScrollByImpl(Ark_VMContext vmContext,
                  Ark_Scroller peer,
                  const Ark_Length* dx,
                  const Ark_Length* dy)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(dx);
    CHECK_NULL_VOID(dy);
    auto xOffset = Converter::OptConvert<Dimension>(*dx).value_or(Dimension());
    auto yOffset = Converter::OptConvert<Dimension>(*dy).value_or(Dimension());
    peer->TriggerScrollBy(vmContext, xOffset, yOffset);
}
Ark_Boolean IsAtEndImpl(Ark_VMContext vmContext,
                        Ark_Scroller peer)
{
    CHECK_NULL_RETURN(peer, false); // need to fix default value
    return peer->TriggerIsAtEnd(vmContext);
}
Ark_RectResult GetItemRectImpl(Ark_VMContext vmContext,
                               Ark_Scroller peer,
                               Ark_Int32 index)
{
    CHECK_NULL_RETURN(peer, {}); // need to fix default value
    return peer->TriggerGetItemRect(vmContext, index);
}
Ark_Int32 GetItemIndexImpl(Ark_VMContext vmContext,
                           Ark_Scroller peer,
                           Ark_Float64 x,
                           Ark_Float64 y)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(-1);
    CHECK_NULL_RETURN(peer, errValue); // need to fix default value
    auto res = peer->TriggerGetItemIndex(vmContext, x, y);
    return Converter::ArkValue<Ark_Int32>(res);
}
Ark_SizeResult ContentSizeImpl(Ark_VMContext vmContext, 
                               Ark_Scroller peer)
{
    CHECK_NULL_RETURN(peer, {}); // need to fix default value
    return peer->TriggerContentSize(vmContext);
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
        ScrollerAccessor::OffsetImpl,
        ScrollerAccessor::ScrollToIndexImpl,
        ScrollerAccessor::ScrollByImpl,
        ScrollerAccessor::IsAtEndImpl,
        ScrollerAccessor::GetItemRectImpl,
        ScrollerAccessor::GetItemIndexImpl,
        ScrollerAccessor::ContentSizeImpl,
    };
    return &ScrollerAccessorImpl;
}

}
