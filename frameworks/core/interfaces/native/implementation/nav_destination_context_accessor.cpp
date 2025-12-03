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
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/navigation/navigation_route.h"

namespace OHOS::Ace::NG::Converter {
using NG::GeneratedModifier::NavigationContext::NavigationStack;
void AssignArkValue(Ark_NavPathStack& dst, const RefPtr<NavigationStack>& src, ConvContext *ctx)
{
    const auto peer = PeerUtils::CreatePeer<NavPathStackPeer>();
    peer->SetNavigationStack(src);
    dst = peer;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavDestinationContextAccessor {
void DestroyPeerImpl(Ark_NavDestinationContext peer)
{
    delete peer;
}
Ark_NavDestinationContext ConstructImpl()
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
    CHECK_NULL_RETURN(peer, nullptr);
    auto navDestination = peer->handler;
    CHECK_NULL_RETURN(navDestination, nullptr);
    auto tsPathInfo = AceType::DynamicCast<NavigationContext::JSNavPathInfoStatic>(navDestination->GetNavPathInfo());
    CHECK_NULL_RETURN(tsPathInfo, nullptr);
    NavigationContext::PathInfo pathInfo(
        tsPathInfo->GetName(), tsPathInfo->GetParam(), tsPathInfo->GetOnPop(), tsPathInfo->GetIsEntry());
    return Converter::ArkValue<Ark_NavPathInfo>(pathInfo);
}

void SetPathInfoImpl(Ark_NavDestinationContext peer,
                     Ark_NavPathInfo pathInfo)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pathInfo);
    auto navDestination = peer->handler;
    CHECK_NULL_VOID(navDestination);
    auto tsPathInfo = AceType::DynamicCast<NavigationContext::JSNavPathInfoStatic>(navDestination->GetNavPathInfo());
    CHECK_NULL_VOID(tsPathInfo);
    auto info = Converter::Convert<NavigationContext::PathInfo>(pathInfo);
    tsPathInfo->SetName(info.name_);
    tsPathInfo->SetParam(info.param_);
    tsPathInfo->SetOnPop(info.onPop_);
    tsPathInfo->SetIsEntry(info.isEntry_);
}
Ark_NavPathStack GetPathStackImpl(Ark_NavDestinationContext peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto navDestination = peer->handler;
    CHECK_NULL_RETURN(navDestination, nullptr);
    auto navPathStack =
        AceType::DynamicCast<NavigationContext::NavigationStack>(navDestination->GetNavigationStack().Upgrade());
    CHECK_NULL_RETURN(navPathStack, nullptr);
    return Converter::ArkValue<Ark_NavPathStack>(navPathStack);
}
void SetPathStackImpl(Ark_NavDestinationContext peer,
                      Ark_NavPathStack pathStack)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(pathStack);
    auto navPathStack = pathStack->GetNavPathStack();
    CHECK_NULL_VOID(navPathStack);
    peer->handler->SetNavigationStack(navPathStack);
}
Opt_String GetNavDestinationIdImpl(Ark_NavDestinationContext peer)
{
    auto invalidVal = Converter::ArkValue<Opt_String>("", Converter::FC);
    CHECK_NULL_RETURN(peer && peer->handler, invalidVal);
    auto id = std::to_string(peer->handler->GetNavDestinationId());
    return Converter::ArkValue<Opt_String>(id, Converter::FC);
}
void SetNavDestinationIdImpl(Ark_NavDestinationContext peer,
                             const Opt_String* navDestinationId)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(navDestinationId);
    auto id = Converter::OptConvertPtr<std::string>(navDestinationId).value_or("");
    peer->handler->SetNavDestinationId(std::atol(id.c_str()));
}
} // NavDestinationContextAccessor
const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor()
{
    static const GENERATED_ArkUINavDestinationContextAccessor NavDestinationContextAccessorImpl {
        NavDestinationContextAccessor::DestroyPeerImpl,
        NavDestinationContextAccessor::ConstructImpl,
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
