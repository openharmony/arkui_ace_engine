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
namespace NavigationTransitionProxyAccessor {
void DestroyPeerImpl(NavigationTransitionProxyPeer* peer)
{
}
NavigationTransitionProxyPeer* CtorImpl()
{
    return new NavigationTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(NavigationTransitionProxyPeer* peer)
{
}
void CancelTransitionImpl(NavigationTransitionProxyPeer* peer)
{
}
void UpdateTransitionImpl(NavigationTransitionProxyPeer* peer,
                          const Ark_Number* progress)
{
}
void SetFromImpl(NavigationTransitionProxyPeer* peer,
                 const Ark_NavContentInfo* from)
{
}
void SetToImpl(NavigationTransitionProxyPeer* peer,
               const Ark_NavContentInfo* to)
{
}
Ark_Boolean GetIsInteractiveImpl(NavigationTransitionProxyPeer* peer)
{
    return 0;
}
void SetIsInteractiveImpl(NavigationTransitionProxyPeer* peer,
                          Ark_Boolean isInteractive)
{
}
} // NavigationTransitionProxyAccessor
const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor()
{
    static const GENERATED_ArkUINavigationTransitionProxyAccessor NavigationTransitionProxyAccessorImpl {
        NavigationTransitionProxyAccessor::DestroyPeerImpl,
        NavigationTransitionProxyAccessor::CtorImpl,
        NavigationTransitionProxyAccessor::GetFinalizerImpl,
        NavigationTransitionProxyAccessor::FinishTransitionImpl,
        NavigationTransitionProxyAccessor::CancelTransitionImpl,
        NavigationTransitionProxyAccessor::UpdateTransitionImpl,
        NavigationTransitionProxyAccessor::SetFromImpl,
        NavigationTransitionProxyAccessor::SetToImpl,
        NavigationTransitionProxyAccessor::GetIsInteractiveImpl,
        NavigationTransitionProxyAccessor::SetIsInteractiveImpl,
    };
    return &NavigationTransitionProxyAccessorImpl;
}

}
