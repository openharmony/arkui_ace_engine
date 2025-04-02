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

#include "base/memory/referenced.h"
#include "core/interfaces/native/implementation/nav_destination_context_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/navigation/navigation_route.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavDestinationContextAccessor {
void DestroyPeerImpl(Ark_NavDestinationContext peer)
{
    delete peer;
}
Ark_NavDestinationContext CtorImpl()
{
    return new NavDestinationContextPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_RouteMapConfig GetConfigInRouteMapImpl(Ark_NavDestinationContext peer)
{
    auto invalid = Converter::ArkValue<Opt_RouteMapConfig>();
    CHECK_NULL_RETURN(peer && peer->handler, invalid);
    auto container = Container::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute) {
        return invalid;
    }
    auto navPathInfo = peer->handler->GetNavPathInfo();
    CHECK_NULL_RETURN(navPathInfo, invalid);
    NG::RouteItem routeInfo;
    if (!navigationRoute->GetRouteItem(navPathInfo->GetName(), routeInfo)) {
        return invalid;
    }

    // a temp struct
    struct RouteMapConfig : public Referenced {
        std::string name = "";
        std::string pageSourceFile = "";
        std::map<std::string, std::string> data;
    };

    auto config = Referenced::MakeRefPtr<RouteMapConfig>();
    config->IncRefCount();
    config->name = navPathInfo->GetName();
    config->pageSourceFile = routeInfo.pageSourceFile->c_str();
    for (auto iter = routeInfo.data.begin(); iter != routeInfo.data.end(); iter++) {
        config->data.insert(std::pair(iter->first, iter->second));
    }

    return invalid; // fix a return value
}
Ark_NavPathInfo GetPathInfoImpl(Ark_NavDestinationContext peer)
{
    return {};
}
void SetPathInfoImpl(Ark_NavDestinationContext peer,
                     Ark_NavPathInfo pathInfo)
{
    LOGE("NavDestinationContext doesn't support set path info");
}
Ark_NavPathStack GetPathStackImpl(Ark_NavDestinationContext peer)
{
    return {};
}
void SetPathStackImpl(Ark_NavDestinationContext peer,
                      Ark_NavPathStack pathStack)
{
    LOGE("NavDestinationContext doesn't support set nav path stack");
}
Ark_String GetNavDestinationIdImpl(Ark_NavDestinationContext peer)
{
    LOGE("NavDestinationContext doesn't support a return value"); // temp
    CHECK_NULL_RETURN(peer && peer->handler, {});
    auto id = std::to_string(peer->handler->GetNavDestinationId());
    // fix a return value
    Converter::ArkValue<Ark_String>(id);
    return {};
}
void SetNavDestinationIdImpl(Ark_NavDestinationContext peer,
                             const Ark_String* navDestinationId)
{
    LOGE("NavDestinationContext doesn't support set nav destination id");
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

struct NavDestinationContextPeer {
    virtual ~NavDestinationContextPeer() = default;
};
}
