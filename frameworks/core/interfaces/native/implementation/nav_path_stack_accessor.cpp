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

#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/interfaces/native/implementation/nav_path_info_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavPathStackAccessor {
void DestroyPeerImpl(Ark_NavPathStack peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NavPathStack CtorImpl()
{
    return new NavPathStackPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void PushPath0Impl(Ark_NavPathStack peer,
                   Ark_NavPathInfo info,
                   const Opt_Boolean* animated)
{
}
void PushPath1Impl(Ark_NavPathStack peer,
                   Ark_NavPathInfo info,
                   const Opt_NavigationOptions* options)
{
}
void PushDestination0Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_Boolean* animated,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestination0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto navInfo = info->data;
    Ark_NavigationOptions options;
    options.animated = *animated;
    auto navOptions = Converter::Convert<NavigationOptions>(options);
    navStack->NavigationContext::PathStack::PushDestination(navInfo, navOptions);
}
void PushDestination1Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_NavigationOptions* options,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestination1Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto navInfo = info->data;
    auto navOptions = Converter::Convert<NavigationOptions>(options->value);
    navStack->NavigationContext::PathStack::PushDestination(navInfo, navOptions);
}
void PushPathByName0Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Opt_Object* param,
                         const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    CHECK_NULL_VOID(param);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPathByName0Impl. Navigation Stack isn't bound to a component.");
        return;
    }

    auto convName = Converter::Convert<std::string>(*name);
#ifndef WRONG_GEN
    auto convParam = Converter::OptConvert<Nav::ExternalData>(*param).value_or(Nav::ExternalData{});
#else
    static_assert(std::is_same_v<decltype(param), const Opt_CustomObject*>);
    auto convParam = Converter::Convert<Nav::ExternalData>(Ark_Object{});
#endif
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushPathByName(convName, convParam, Nav::OnPopCallback(), convAnimated);
}
void PushPathByName1Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_Object* param,
                         const Callback_PopInfo_Void* onPop,
                         const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    CHECK_NULL_VOID(param);
    CHECK_NULL_VOID(onPop);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPathByName1Impl. Navigation Stack isn't bound to a component.");
        return;
    }

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convOnPop = Converter::Convert<Callback_PopInfo_Void>(*onPop);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushPathByName(convName, convParam, convOnPop, convAnimated);
}
void PushDestinationByName0Impl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_NavPathStack peer,
                                const Ark_String* name,
                                const Ark_Object* param,
                                const Opt_Boolean* animated,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Ark_NativePointer invalid = nullptr;
    LOGE("NavPathStackAccessor::PushDestinationByName0Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    CHECK_NULL_VOID(param);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestinationByName0Impl. Navigation Stack isn't bound to a component.");
        return;
    }

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushDestinationByName(convName, convParam, Nav::OnPopCallback(), convAnimated);
}
void PushDestinationByName1Impl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_NavPathStack peer,
                                const Ark_String* name,
                                const Ark_Object* param,
                                const Callback_PopInfo_Void* onPop,
                                const Opt_Boolean* animated,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    LOGE("NavPathStackAccessor::PushDestinationByName1Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    CHECK_NULL_VOID(param);
    CHECK_NULL_VOID(onPop);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestinationByName1Impl. Navigation Stack isn't bound to a component.");
        return;
    }

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convOnPop = Converter::Convert<Callback_PopInfo_Void>(*onPop);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushDestinationByName(convName, convParam, convOnPop, convAnimated);
}
void ReplacePath0Impl(Ark_NavPathStack peer,
                      Ark_NavPathInfo info,
                      const Opt_Boolean* animated)
{
}
void ReplacePath1Impl(Ark_NavPathStack peer,
                      Ark_NavPathInfo info,
                      const Opt_NavigationOptions* options)
{
}
void ReplaceDestinationImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_NavPathStack peer,
                            Ark_NavPathInfo info,
                            const Opt_NavigationOptions* options,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void ReplacePathByNameImpl(Ark_NavPathStack peer,
                           const Ark_String* name,
                           const Ark_Object* param,
                           const Opt_Boolean* animated)
{
}
Ark_Number RemoveByIndexesImpl(Ark_NavPathStack peer,
                               const Array_Number* indexes)
{
    return {};
}
Ark_Number RemoveByNameImpl(Ark_NavPathStack peer,
                            const Ark_String* name)
{
    auto invalidVal = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(name, invalidVal);
    auto removeName = Converter::Convert<std::string>(*name);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto size = navStack->RemoveByName(removeName);
    return Converter::ArkValue<Ark_Number>(size);
}
Ark_Boolean RemoveByNavDestinationIdImpl(Ark_NavPathStack peer,
                                         const Ark_String* navDestinationId)
{
    auto invalidVal = Converter::ArkValue<Ark_Boolean>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(navDestinationId, invalidVal);
    auto removeId = Converter::Convert<std::string>(*navDestinationId);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto size = navStack->RemoveByNavDestinationId(removeId);
    return Converter::ArkValue<Ark_Boolean>(size);
}
Opt_NavPathInfo Pop0Impl(Ark_NavPathStack peer,
                         const Opt_Boolean* animated)
{
    return {};
}
Opt_NavPathInfo Pop1Impl(Ark_NavPathStack peer,
                         const Ark_Object* result,
                         const Opt_Boolean* animated)
{
    return {};
}
Ark_Number PopToName0Impl(Ark_NavPathStack peer,
                          const Ark_String* name,
                          const Opt_Boolean* animated)
{
    return {};
}
Ark_Number PopToName1Impl(Ark_NavPathStack peer,
                          const Ark_String* name,
                          const Ark_Object* result,
                          const Opt_Boolean* animated)
{
    return {};
}
void PopToIndex0Impl(Ark_NavPathStack peer,
                     const Ark_Number* index,
                     const Opt_Boolean* animated)
{
}
void PopToIndex1Impl(Ark_NavPathStack peer,
                     const Ark_Number* index,
                     const Ark_Object* result,
                     const Opt_Boolean* animated)
{
}
Ark_Number MoveToTopImpl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    auto invalidVal = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(name, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto pathName = Converter::Convert<std::string>(*name);
    bool isAnimated = Converter::OptConvert<bool>(*animated).value_or(true);
    auto index = navStack->NavigationContext::PathStack::MoveToTop(pathName, isAnimated);
    return Converter::ArkValue<Ark_Number>(index);
}
void MoveIndexToTopImpl(Ark_NavPathStack peer,
                        const Ark_Number* index,
                        const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(index);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto indexNum = Converter::Convert<std::uint32_t>(*index);
    bool isAnimated = Converter::OptConvert<bool>(*animated).value_or(true);
    navStack->NavigationContext::PathStack::MoveIndexToTop(indexNum, isAnimated);
}
void ClearImpl(Ark_NavPathStack peer,
               const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto isAnimated = Converter::OptConvert<bool>(*animated).value_or(true);
    navStack->NavigationContext::PathStack::Clear(isAnimated);
}
Array_String GetAllPathNameImpl(Ark_NavPathStack peer)
{
    std::vector<std::string> result;
    auto invalidVal = Converter::ArkValue<Array_String>(result, Converter::FC);
    CHECK_NULL_RETURN(peer, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    std::vector<std::string> allName = navStack->NavigationContext::PathStack::GetAllPathName();
    Array_String values = Converter::ArkValue<Array_String>(allName, Converter::FC);
    Ark_Int32 len = values.length;
    return values;
}
Opt_Object GetParamByIndexImpl(Ark_NavPathStack peer,
                               const Ark_Number* index)
{
    auto invalid = Converter::ArkValue<Opt_Object>();
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    return invalid;
}
Array_Opt_Object GetParamByNameImpl(Ark_NavPathStack peer,
                                    const Ark_String* name)
{
    return {};
}
Array_Number GetIndexByNameImpl(Ark_NavPathStack peer,
                                const Ark_String* name)
{
    CHECK_NULL_RETURN(peer, {});
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, {});
    auto pathName = Converter::Convert<std::string>(*name);
    std::vector<size_t> allIndexes = pathStack->NavigationContext::PathStack::GetIndexByName(pathName);
    std::vector<uint32_t> indexes;
    indexes.assign(allIndexes.begin(), allIndexes.end());
    Array_Number result = Converter::ArkValue<Array_Number>(indexes, Converter::FC);
    return result;
}
Opt_NavPathStack GetParentImpl(Ark_NavPathStack peer)
{
    return {};
}
Ark_Number SizeImpl(Ark_NavPathStack peer)
{
    auto invalidVal = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, invalidVal);
    auto size = static_cast<int32_t>(pathStack->NavigationContext::PathStack::Size());
    return Converter::ArkValue<Ark_Number>(size);
}
void DisableAnimationImpl(Ark_NavPathStack peer,
                          Ark_Boolean value)
{
    CHECK_NULL_VOID(peer);
    auto animated = Converter::Convert<bool>(value);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(pathStack);
    pathStack->DisableAnimation(animated);
}
void SetInterceptionImpl(Ark_NavPathStack peer,
                         const Ark_NavigationInterception* interception)
{
    CHECK_NULL_VOID(peer);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(pathStack);
    NavigationContext::InterceptionType result = new NavigationContext::Interception();
    if (interception->modeChange.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        result->modeChange = [callback = CallbackHelper(interception->modeChange.value)](NG::NavigationMode mode) {
            callback.Invoke(Converter::ArkValue<Ark_NavigationMode>(mode));
        };
    }
    if (interception->willShow.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        result->willShow = [callback = CallbackHelper(interception->willShow.value)](
                               const RefPtr<NG::NavDestinationContext>& from,
                               const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation,
                               bool isAnimated) {
            Ark_Union_NavDestinationContext_NavBar tempfrom;
            Ark_Union_NavDestinationContext_NavBar tempto;
            auto preDestination = AceType::DynamicCast<NG::NavDestinationContext>(from);
            if (!preDestination) {
                tempfrom = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_String>("navbar");
            } else {
                tempfrom = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_NavDestinationContext>(from);
            }
            auto topDestination = AceType::DynamicCast<NG::NavDestinationContext>(to);
            if (!topDestination) {
                tempto = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_String>("navbar");
            } else {
                tempto = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_NavDestinationContext>(to);
            }
            callback.Invoke(tempfrom, tempto, Converter::ArkValue<Ark_NavigationOperation>(operation),
                Converter::ArkValue<Ark_Boolean>(isAnimated));
        };
    }
    if (interception->didShow.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        result->didShow = [callback = CallbackHelper(interception->didShow.value)](
                              const RefPtr<NG::NavDestinationContext>& from,
                              const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation,
                              bool isAnimated) {
            Ark_Union_NavDestinationContext_NavBar tempfrom;
            Ark_Union_NavDestinationContext_NavBar tempto;
            auto preDestination = AceType::DynamicCast<NG::NavDestinationContext>(from);
            if (!preDestination) {
                tempfrom = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_String>("navbar");
            } else {
                tempfrom = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_NavDestinationContext>(from);
            }
            auto topDestination = AceType::DynamicCast<NG::NavDestinationContext>(to);
            if (!topDestination) {
                tempto = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_String>("navbar");
            } else {
                tempto = Converter::ArkUnion<Ark_Union_NavDestinationContext_NavBar, Ark_NavDestinationContext>(to);
            }
            callback.Invoke(tempfrom, tempto, Converter::ArkValue<Ark_NavigationOperation>(operation),
                Converter::ArkValue<Ark_Boolean>(isAnimated));
        };
    }
    pathStack->NavigationContext::PathStack::SetInterception(result);
}
Array_NavPathInfo GetPathStackImpl(Ark_NavPathStack peer)
{
    return {};
}
void SetPathStackImpl(Ark_NavPathStack peer,
                      const Array_NavPathInfo* pathStack,
                      const Opt_Boolean* animated)
{
}
} // NavPathStackAccessor
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor()
{
    static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
        NavPathStackAccessor::DestroyPeerImpl,
        NavPathStackAccessor::CtorImpl,
        NavPathStackAccessor::GetFinalizerImpl,
        NavPathStackAccessor::PushPath0Impl,
        NavPathStackAccessor::PushPath1Impl,
        NavPathStackAccessor::PushDestination0Impl,
        NavPathStackAccessor::PushDestination1Impl,
        NavPathStackAccessor::PushPathByName0Impl,
        NavPathStackAccessor::PushPathByName1Impl,
        NavPathStackAccessor::PushDestinationByName0Impl,
        NavPathStackAccessor::PushDestinationByName1Impl,
        NavPathStackAccessor::ReplacePath0Impl,
        NavPathStackAccessor::ReplacePath1Impl,
        NavPathStackAccessor::ReplaceDestinationImpl,
        NavPathStackAccessor::ReplacePathByNameImpl,
        NavPathStackAccessor::RemoveByIndexesImpl,
        NavPathStackAccessor::RemoveByNameImpl,
        NavPathStackAccessor::RemoveByNavDestinationIdImpl,
        NavPathStackAccessor::Pop0Impl,
        NavPathStackAccessor::Pop1Impl,
        NavPathStackAccessor::PopToName0Impl,
        NavPathStackAccessor::PopToName1Impl,
        NavPathStackAccessor::PopToIndex0Impl,
        NavPathStackAccessor::PopToIndex1Impl,
        NavPathStackAccessor::MoveToTopImpl,
        NavPathStackAccessor::MoveIndexToTopImpl,
        NavPathStackAccessor::ClearImpl,
        NavPathStackAccessor::GetAllPathNameImpl,
        NavPathStackAccessor::GetParamByIndexImpl,
        NavPathStackAccessor::GetParamByNameImpl,
        NavPathStackAccessor::GetIndexByNameImpl,
        NavPathStackAccessor::GetParentImpl,
        NavPathStackAccessor::SizeImpl,
        NavPathStackAccessor::DisableAnimationImpl,
        NavPathStackAccessor::SetInterceptionImpl,
        NavPathStackAccessor::GetPathStackImpl,
        NavPathStackAccessor::SetPathStackImpl,
    };
    return &NavPathStackAccessorImpl;
}

}
