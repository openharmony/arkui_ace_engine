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
namespace SwiperContentTransitionProxyAccessor {
void DestroyPeerImpl(SwiperContentTransitionProxyPeer* peer)
{
}
SwiperContentTransitionProxyPeer* CtorImpl()
{
    return new SwiperContentTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(SwiperContentTransitionProxyPeer* peer)
{
}
Ark_Int32 GetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer,
                          const Ark_Number* selectedIndex)
{
}
Ark_Int32 GetIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetIndexImpl(SwiperContentTransitionProxyPeer* peer,
                  const Ark_Number* index)
{
}
Ark_Int32 GetPositionImpl(SwiperContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetPositionImpl(SwiperContentTransitionProxyPeer* peer,
                     const Ark_Number* position)
{
}
Ark_Int32 GetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer,
                           const Ark_Number* mainAxisLength)
{
}
} // SwiperContentTransitionProxyAccessor
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
        SwiperContentTransitionProxyAccessor::DestroyPeerImpl,
        SwiperContentTransitionProxyAccessor::CtorImpl,
        SwiperContentTransitionProxyAccessor::GetFinalizerImpl,
        SwiperContentTransitionProxyAccessor::FinishTransitionImpl,
        SwiperContentTransitionProxyAccessor::GetSelectedIndexImpl,
        SwiperContentTransitionProxyAccessor::SetSelectedIndexImpl,
        SwiperContentTransitionProxyAccessor::GetIndexImpl,
        SwiperContentTransitionProxyAccessor::SetIndexImpl,
        SwiperContentTransitionProxyAccessor::GetPositionImpl,
        SwiperContentTransitionProxyAccessor::SetPositionImpl,
        SwiperContentTransitionProxyAccessor::GetMainAxisLengthImpl,
        SwiperContentTransitionProxyAccessor::SetMainAxisLengthImpl,
    };
    return &SwiperContentTransitionProxyAccessorImpl;
}

}
