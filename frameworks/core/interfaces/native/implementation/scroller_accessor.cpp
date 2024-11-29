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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollerAccessor {
void DestroyPeerImpl(ScrollerPeer* peer)
{
}
ScrollerPeer* CtorImpl()
{
    return new ScrollerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ScrollToImpl(ScrollerPeer* peer,
                  const Ark_ScrollOptions* options)
{
}
void ScrollEdgeImpl(ScrollerPeer* peer,
                    Ark_Edge value,
                    const Opt_ScrollEdgeOptions* options)
{
}
void FlingImpl(ScrollerPeer* peer,
               const Ark_Number* velocity)
{
}
void ScrollPage0Impl(ScrollerPeer* peer,
                     const Ark_ScrollPageOptions* value)
{
}
void ScrollPage1Impl(ScrollerPeer* peer,
                     const Ark_Literal_Boolean_next_Axis_direction* value)
{
}
Ark_NativePointer CurrentOffsetImpl(ScrollerPeer* peer)
{
    return 0;
}
void ScrollToIndexImpl(ScrollerPeer* peer,
                       const Ark_Number* value,
                       const Opt_Boolean* smooth,
                       const Opt_ScrollAlign* align,
                       const Opt_ScrollToIndexOptions* options)
{
}
void ScrollByImpl(ScrollerPeer* peer,
                  const Ark_Length* dx,
                  const Ark_Length* dy)
{
}
Ark_Boolean IsAtEndImpl(ScrollerPeer* peer)
{
    return 0;
}
Ark_NativePointer GetItemRectImpl(ScrollerPeer* peer,
                                  const Ark_Number* index)
{
    return 0;
}
Ark_Int32 GetItemIndexImpl(ScrollerPeer* peer,
                           const Ark_Number* x,
                           const Ark_Number* y)
{
    return 0;
}
} // ScrollerAccessor
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
{
    static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
        ScrollerAccessor::DestroyPeerImpl,
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
