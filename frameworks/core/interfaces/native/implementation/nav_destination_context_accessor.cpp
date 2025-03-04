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
namespace NavDestinationContextAccessor {
void DestroyPeerImpl(Ark_NavDestinationContext peer)
{
}
Ark_NavDestinationContext CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_RouteMapConfig GetConfigInRouteMapImpl(Ark_NavDestinationContext peer)
{
    return {};
}
Ark_NavPathInfo GetPathInfoImpl(Ark_NavDestinationContext peer)
{
    return {};
}
void SetPathInfoImpl(Ark_NavDestinationContext peer,
                     Ark_NavPathInfo pathInfo)
{
}
Ark_NavPathStack GetPathStackImpl(Ark_NavDestinationContext peer)
{
    return {};
}
void SetPathStackImpl(Ark_NavDestinationContext peer,
                      Ark_NavPathStack pathStack)
{
}
Ark_String GetNavDestinationIdImpl(Ark_NavDestinationContext peer)
{
    return {};
}
void SetNavDestinationIdImpl(Ark_NavDestinationContext peer,
                             const Ark_String* navDestinationId)
{
}
} // NavDestinationContextAccessor
const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor()
{
    static const GENERATED_ArkUINavDestinationContextAccessor NavDestinationContextAccessorImpl {
        NavDestinationContextAccessor::DestroyPeerImpl,
        NavDestinationContextAccessor::CtorImpl,
        NavDestinationContextAccessor::GetFinalizerImpl,
        NavDestinationContextAccessor::GetConfigInRouteMapImpl,
        NavDestinationContextAccessor::GetPathInfoImpl,
        NavDestinationContextAccessor::SetPathInfoImpl,
        NavDestinationContextAccessor::GetPathStackImpl,
        NavDestinationContextAccessor::SetPathStackImpl,
        NavDestinationContextAccessor::GetNavDestinationIdImpl,
        NavDestinationContextAccessor::SetNavDestinationIdImpl,
    };
    return &NavDestinationContextAccessorImpl;
}

}
