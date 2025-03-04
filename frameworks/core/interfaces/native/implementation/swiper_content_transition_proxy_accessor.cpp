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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperContentTransitionProxyAccessor {
void DestroyPeerImpl(Ark_SwiperContentTransitionProxy peer)
{
}
Ark_SwiperContentTransitionProxy CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(Ark_SwiperContentTransitionProxy peer)
{
}
Ark_Number GetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    return {};
}
void SetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer,
                          const Ark_Number* selectedIndex)
{
}
Ark_Number GetIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    return {};
}
void SetIndexImpl(Ark_SwiperContentTransitionProxy peer,
                  const Ark_Number* index)
{
}
Ark_Number GetPositionImpl(Ark_SwiperContentTransitionProxy peer)
{
    return {};
}
void SetPositionImpl(Ark_SwiperContentTransitionProxy peer,
                     const Ark_Number* position)
{
}
Ark_Number GetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer)
{
    return {};
}
void SetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer,
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
