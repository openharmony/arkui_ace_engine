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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#if !defined(PREVIEW)
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#endif
#include "core/interfaces/native/implementation/nav_path_info_peer_impl.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavExtenderAccessor {
void SetNavigationOptionsImpl(Ark_NativePointer ptr,
                              Ark_NavPathStack pathStack)
{
}
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
    CHECK_NULL_VOID(peer);
    auto navigationStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navigationStack);
    auto updater = [callback = CallbackHelper(*callback)]() {
        callback.Invoke();
        auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
        context->RequestFrame();
    };
    navigationStack->SetOnStateChangedCallback(std::move(updater));
}

void SetCreateNavDestinationCallbackImpl(Ark_NavPathStack peer,
                                         const NavExtender_CreateNavDestination* callback)
{
    CHECK_NULL_VOID(peer);
    auto navigationStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navigationStack);
    auto stack = AceType::DynamicCast<Nav::NavigationStack>(navigationStack);
    CHECK_NULL_VOID(stack);
    auto creater = [callback = CallbackHelper(*callback)](int32_t index) -> RefPtr<NG::UINode> {
        auto node = callback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(index);
        return Referenced::Claim(reinterpret_cast<UINode*>(node));
    };
    stack->SetCreateNavDestinationCallback(std::move(creater));
}

void SyncStackImpl(Ark_NavPathStack peer)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    auto navigationNode = AceType::DynamicCast<FrameNode>(stack->GetNavigationNode().Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    stack->ClearNodeList();
}
Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                Ark_Int32 index)
{
    auto invalidVal = Converter::ArkValue<Ark_Boolean>(false);
    auto navigationNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_RETURN(navigationNode, invalidVal);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, invalidVal);
    auto isCreated = pattern->CheckNeedCreate(index);
    return Converter::ArkValue<Ark_Boolean>(isCreated);
}
void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                               Ark_Int32 index,
                               Ark_NativePointer node)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    int32_t curIndex = Converter::Convert<int32_t>(index);
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto instanceId = container->GetInstanceId();
    auto proxyNode = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(instanceId);
    CHECK_NULL_VOID(proxyNode);
    proxyNode->AddChild(Referenced::Claim(reinterpret_cast<UINode*>(node)));
    stack->AddCustomNode(curIndex, proxyNode);
#else
    stack->AddCustomNode(curIndex, Referenced::Claim(reinterpret_cast<UINode*>(node)));
#endif
}
void PushPathImpl(Ark_NavPathStack pathStack,
                  Ark_NavPathInfo info,
                  const Ark_NavigationOptions* options)
{
    CHECK_NULL_VOID(pathStack);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(options);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    auto navOptions = Converter::Convert<NavigationOptions>(*options);
    pathStack->SetInstanceId(1);
    navStack->NavigationContext::PathStack::PushPath(navInfo, navOptions);
}
void ReplacePathImpl(Ark_NavPathStack pathStack,
                     Ark_NavPathInfo info,
                     const Ark_NavigationOptions* options)
{
    CHECK_NULL_VOID(pathStack);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(options);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    auto navOptions = Converter::Convert<NavigationOptions>(*options);
    navStack->NavigationContext::PathStack::ReplacePath(navInfo, navOptions);
}
Ark_String PopImpl(Ark_NavPathStack pathStack,
                   Ark_Boolean animated)
{
    auto invalidVal = Converter::ArkValue<Ark_String>("", Converter::FC);
    CHECK_NULL_RETURN(pathStack, invalidVal);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto isAnimated = Converter::Convert<bool>(animated);
    auto info = navStack->NavigationContext::PathStack::Pop(isAnimated);
    return Converter::ArkValue<Ark_String>(info.navDestinationId_.value_or(""), Converter::FC);
}
void SetOnPopCallbackImpl(Ark_NavPathStack pathStack,
                          const Callback_String_Void* popCallback)
{
    auto stack = pathStack;
    CHECK_NULL_VOID(stack);
    auto navigationStack = stack->GetNavPathStack();
    CHECK_NULL_VOID(navigationStack);
    auto callback = [callback = CallbackHelper(*popCallback)](const std::string& navDestinationId) {
        auto idVal = Converter::ArkValue<Ark_String>(navDestinationId);
        callback.Invoke(idVal);
    };
    navigationStack->SetOnPopCallback(std::move(callback));
}
Ark_String GetIdByIndexImpl(Ark_NavPathStack pathStack,
                            Ark_Int32 index)
{
    auto invalidVal = Converter::ArkValue<Ark_String>("", Converter::FC);
    CHECK_NULL_RETURN(pathStack, invalidVal);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto indexVal = Converter::Convert<int32_t>(index);
    auto pathInfo = navStack->GetPathInfo(indexVal);
    CHECK_NULL_RETURN(pathInfo, invalidVal);
    return Converter::ArkValue<Ark_String>(pathInfo->navDestinationId_.value_or(""), Converter::FC);
}
Array_String GetIdByNameImpl(Ark_NavPathStack pathStack,
                             const Ark_String* name)
{
    CHECK_NULL_RETURN(pathStack, {});
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, {});
    auto nameVal = Converter::Convert<std::string>(*name);
    auto ids = navStack->GetIdByName(nameVal);
    return Converter::ArkValue<Array_String>(ids, Converter::FC);
}
void PopToIndexImpl(Ark_NavPathStack pathStack,
                    Ark_Int32 index,
                    Ark_Boolean animated)
{
    CHECK_NULL_VOID(pathStack);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto indexVal = Converter::Convert<int32_t>(index);
    auto animatedVal = Converter::Convert<bool>(animated);
    navStack->NavigationContext::PathStack::PopToIndex(indexVal, animatedVal);
}
Ark_Int32 PopToNameImpl(Ark_NavPathStack pathStack,
                         const Ark_String* name,
                         Ark_Boolean animated)
{
    static Ark_Int32 invalidVal = Converter::ArkValue<Ark_Int32>(-1);
    CHECK_NULL_RETURN(pathStack, invalidVal);
    auto navStack = pathStack->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto nameVal = Converter::Convert<std::string>(*name);
    auto animatedVal = Converter::Convert<bool>(animated);
    auto index = navStack->NavigationContext::PathStack::PopToName(nameVal, animatedVal);
    return Converter::ArkValue<Ark_Int32>(index);
}
} // NavExtenderAccessor
const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
{
    static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
        NavExtenderAccessor::SetNavigationOptionsImpl,
        NavExtenderAccessor::SetUpdateStackCallbackImpl,
        NavExtenderAccessor::SyncStackImpl,
        NavExtenderAccessor::CheckNeedCreateImpl,
        NavExtenderAccessor::SetNavDestinationNodeImpl,
        NavExtenderAccessor::PushPathImpl,
        NavExtenderAccessor::ReplacePathImpl,
        NavExtenderAccessor::PopImpl,
        NavExtenderAccessor::SetOnPopCallbackImpl,
        NavExtenderAccessor::GetIdByIndexImpl,
        NavExtenderAccessor::GetIdByNameImpl,
        NavExtenderAccessor::PopToIndexImpl,
        NavExtenderAccessor::PopToNameImpl,
        NavExtenderAccessor::SetCreateNavDestinationCallbackImpl,
    };
    return &NavExtenderAccessorImpl;
}

}
