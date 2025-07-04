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
namespace NavigationTransitionProxyAccessor {
void DestroyPeerImpl(Ark_NavigationTransitionProxy peer)
{
}
Ark_NavigationTransitionProxy ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(Ark_NavigationTransitionProxy peer)
{
}
Ark_NavContentInfo GetFromImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetFromImpl(Ark_NavigationTransitionProxy peer,
                 const Ark_NavContentInfo* from)
{
}
Ark_NavContentInfo GetToImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetToImpl(Ark_NavigationTransitionProxy peer,
               const Ark_NavContentInfo* to)
{
}
Opt_Boolean GetIsInteractiveImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetIsInteractiveImpl(Ark_NavigationTransitionProxy peer,
                          const Opt_Boolean* isInteractive)
{
}
Opt_VoidCallback GetCancelTransitionImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetCancelTransitionImpl(Ark_NavigationTransitionProxy peer,
                             const Opt_VoidCallback* cancelTransition)
{
}
Opt_UpdateTransitionCallback GetUpdateTransitionImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetUpdateTransitionImpl(Ark_NavigationTransitionProxy peer,
                             const Opt_UpdateTransitionCallback* updateTransition)
{
}
} // NavigationTransitionProxyAccessor
const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor()
{
    static const GENERATED_ArkUINavigationTransitionProxyAccessor NavigationTransitionProxyAccessorImpl {
        NavigationTransitionProxyAccessor::DestroyPeerImpl,
        NavigationTransitionProxyAccessor::ConstructImpl,
        NavigationTransitionProxyAccessor::GetFinalizerImpl,
        NavigationTransitionProxyAccessor::FinishTransitionImpl,
        NavigationTransitionProxyAccessor::GetFromImpl,
        NavigationTransitionProxyAccessor::SetFromImpl,
        NavigationTransitionProxyAccessor::GetToImpl,
        NavigationTransitionProxyAccessor::SetToImpl,
        NavigationTransitionProxyAccessor::GetIsInteractiveImpl,
        NavigationTransitionProxyAccessor::SetIsInteractiveImpl,
        NavigationTransitionProxyAccessor::GetCancelTransitionImpl,
        NavigationTransitionProxyAccessor::SetCancelTransitionImpl,
        NavigationTransitionProxyAccessor::GetUpdateTransitionImpl,
        NavigationTransitionProxyAccessor::SetUpdateTransitionImpl,
    };
    return &NavigationTransitionProxyAccessorImpl;
}

}
