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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace Nav = OHOS::Ace::NG::GeneratedModifier::NavigationContext;


namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<Nav::LaunchMode>& dst, const Ark_LaunchMode& src)
{
    switch (src) {
        case ARK_LAUNCH_MODE_STANDARD: dst = Nav::LaunchMode::STANDARD; break;
        case ARK_LAUNCH_MODE_MOVE_TO_TOP_SINGLETON: dst = Nav::LaunchMode::MOVE_TO_TOP_SINGLETON; break;
        case ARK_LAUNCH_MODE_POP_TO_SINGLETON: dst = Nav::LaunchMode::POP_TO_SINGLETON; break;
        case ARK_LAUNCH_MODE_NEW_INSTANCE: dst = Nav::LaunchMode::NEW_INSTANCE; break;
        default: LOGE("Unexpected enum value in Ark_LaunchMode: %{public}d", src);
    }
}

template<>
Nav::Options Convert(const Ark_NavigationOptions& src)
{
    return {
        .launchMode = OptConvert<Nav::LaunchMode>(src.launchMode),
        .animated = OptConvert<bool>(src.animated)
    };
}
} // namespace OHOS::Ace::NG::Converter

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
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPath0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushPath(convNavInfo, Nav::Options{std::nullopt, convAnimated});
}
void PushPath1Impl(Ark_NavPathStack peer,
                   Ark_NavPathInfo info,
                   const Opt_NavigationOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPath1Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(info);
    auto convNavOptions = options ? Converter::OptConvert<Nav::Options>(*options) : std::nullopt;
    navStack->Nav::PathStack::PushPath(convNavInfo, convNavOptions);
}
void PushDestination0Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_Boolean* animated,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    LOGE("NavPathStackAccessor::PushDestination0Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestination0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    LOGE("NavPathStackAccessor::PushDestination0Impl does not return required type");
    navStack->Nav::PathStack::PushDestination(convNavInfo, Nav::Options{std::nullopt, convAnimated});
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
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(info);
    auto convNavOptions = options ? Converter::OptConvert<Nav::Options>(*options) : std::nullopt;
    navStack->Nav::PathStack::PushDestination(convNavInfo, convNavOptions);
}
void PushPathByName0Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
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
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushPathByName(convName, convParam, Nav::OnPopCallback(), convAnimated);
}
void PushPathByName1Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
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
                                const Ark_CustomObject* param,
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
                                const Ark_CustomObject* param,
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
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(animated);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::ReplacePath0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::ReplacePath(convNavInfo, Nav::Options{std::nullopt, convAnimated});
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
                           const Ark_CustomObject* param,
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
    return {};
}
Ark_Boolean RemoveByNavDestinationIdImpl(Ark_NavPathStack peer,
                                         const Ark_String* navDestinationId)
{
    return {};
}
Opt_NavPathInfo Pop0Impl(Ark_NavPathStack peer,
                         const Opt_Boolean* animated)
{
    auto invalid = Converter::ArkValue<Opt_NavPathInfo>();
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    auto pathInfo = navStack->Nav::PathStack::Pop(Nav::PopResultType(), convAnimated);
    return Converter::ArkValue<Opt_NavPathInfo>(pathInfo);
}
Opt_NavPathInfo Pop1Impl(Ark_NavPathStack peer,
                         const Ark_CustomObject* result,
                         const Opt_Boolean* animated)
{
    auto invalid = Converter::ArkValue<Opt_NavPathInfo>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(result, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    auto convResult = Converter::Convert<Nav::ExternalData>(*result);
    auto pathInfo = navStack->Nav::PathStack::Pop(convResult, convAnimated);
    return Converter::ArkValue<Opt_NavPathInfo>(pathInfo);
}
Ark_Number PopToName0Impl(Ark_NavPathStack peer,
                          const Ark_String* name,
                          const Opt_Boolean* animated)
{
    return {};
}
Ark_Number PopToName1Impl(Ark_NavPathStack peer,
                          const Ark_String* name,
                          const Ark_CustomObject* result,
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
                     const Ark_CustomObject* result,
                     const Opt_Boolean* animated)
{
}
Ark_Number MoveToTopImpl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    return {};
}
void MoveIndexToTopImpl(Ark_NavPathStack peer,
                        const Ark_Number* index,
                        const Opt_Boolean* animated)
{
}
void ClearImpl(Ark_NavPathStack peer,
               const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::Clear(convAnimated);
}
Array_String GetAllPathNameImpl(Ark_NavPathStack peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, {});
    auto allName = navStack->Nav::PathStack::GetAllPathName();
    return Converter::ArkValue<Array_String>(allName, Converter::FC);
}
Opt_CustomObject GetParamByIndexImpl(Ark_NavPathStack peer,
                                     const Ark_Number* index)
{
    auto invalid = Converter::ArkValue<Opt_CustomObject>();
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    return invalid;
}
Array_CustomObject GetParamByNameImpl(Ark_NavPathStack peer,
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
    auto allIndexes = pathStack->Nav::PathStack::GetIndexByName(pathName);
    return Converter::ArkValue<Array_Number>(allIndexes);
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
    auto size = static_cast<int32_t>(pathStack->Size());
    return Converter::ArkValue<Ark_Number>(size);
}
void DisableAnimationImpl(Ark_NavPathStack peer,
                          Ark_Boolean value)
{
}
void SetInterceptionImpl(Ark_NavPathStack peer,
                         const Ark_NavigationInterception* interception)
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
    };
    return &NavPathStackAccessorImpl;
}

struct NavPathStackPeer {
    virtual ~NavPathStackPeer() = default;
};
}
