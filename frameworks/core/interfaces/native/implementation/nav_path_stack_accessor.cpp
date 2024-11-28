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

#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"

namespace Nav = OHOS::Ace::NG::GeneratedModifier::NavigationContext;

namespace OHOS::Ace::NG::Converter {
template<>
Nav::ExternalData Convert(const Ark_CustomObject& src)
{
    return Referenced::MakeRefPtr<Nav::ExternalDataKeeper>(src);
}

template<>
Nav::PathInfo Convert(const Ark_NavPathInfo& src)
{
    auto name = Convert<std::string>(src.name);
    auto isEntryOpt = OptConvert<bool>(src.isEntry);
    auto paramOpt = OptConvert<Nav::ExternalData>(src.param);
    Nav::OnPopCallback onPop;
    if (auto onPopOpt = OptConvert<Callback_PopInfo_Void>(src.onPop); onPopOpt) {
        onPop = *onPopOpt;
    }
    return Nav::PathInfo(name, paramOpt.value_or(nullptr), onPop, isEntryOpt.value_or(false));
}

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
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavPathStackAccessor {
void DestroyPeerImpl(NavPathStackPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
NavPathStackPeer* CtorImpl()
{
    return new NavPathStackPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void PushPath0Impl(NavPathStackPeer* peer,
                   const Ark_NavPathInfo* info,
                   const Opt_Boolean* animated)
{
    LOGE("NavPathStackAccessor::PushPath0Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPath0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(*info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::PushPath(convNavInfo, Nav::Options{std::nullopt, convAnimated});
}
void PushPath1Impl(NavPathStackPeer* peer,
                   const Ark_NavPathInfo* info,
                   const Opt_NavigationOptions* options)
{
    LOGE("NavPathStackAccessor::PushPath1Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPath1Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(*info);
    auto convNavOptions = options ? Converter::OptConvert<Nav::Options>(*options) : std::nullopt;
    navStack->Nav::PathStack::PushPath(convNavInfo, convNavOptions);
}
void PushDestination0Impl(NavPathStackPeer* peer,
                          const Ark_NavPathInfo* info,
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
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(*info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    auto errorCode = navStack->Nav::PathStack::PushDestination(convNavInfo, Nav::Options{std::nullopt, convAnimated});
/*     auto errorCode = std::make_shared<std::promise<void>>();
    if (errorCode != ERROR_CODE_NO_ERROR) {
        promise->set_value();
    } else {
        promise->set_exception(std::make_exception_ptr(std::runtime_error("Internal error.")));
    }
    return reinterpret_cast<Ark_NativePointer>(promise.get());
 */
}
void PushDestination1Impl(NavPathStackPeer* peer,
                          const Ark_NavPathInfo* info,
                          const Opt_NavigationOptions* options,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    LOGE("NavPathStackAccessor::PushDestination1Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushDestination1Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(*info);
    auto convNavOptions = options ? Converter::OptConvert<Nav::Options>(*options) : std::nullopt;
    navStack->Nav::PathStack::PushDestination(convNavInfo, convNavOptions);
}
void PushPathByName0Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Opt_Boolean* animated)
{
    LOGE("NavPathStackAccessor::PushPathByName0Impl is not implemented yet.");
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
void PushPathByName1Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Callback_PopInfo_Void* onPop,
                         const Opt_Boolean* animated)
{
    LOGE("NavPathStackAccessor::PushPathByName1Impl is not implemented yet.");
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
void PushDestinationByName0Impl(NavPathStackPeer* peer,
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
void PushDestinationByName1Impl(NavPathStackPeer* peer,
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
void ReplacePath0Impl(NavPathStackPeer* peer,
                      const Ark_NavPathInfo* info,
                      const Opt_Boolean* animated)
{
    LOGE("NavPathStackAccessor::ReplacePath0Impl is not implemented yet.");
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(animated);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::ReplacePath0Impl. Navigation Stack isn't bound to a component.");
        return;
    }
    auto convNavInfo = Converter::Convert<Nav::PathInfo>(*info);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::ReplacePath(convNavInfo, Nav::Options{std::nullopt, convAnimated});
}
void ReplacePath1Impl(NavPathStackPeer* peer,
                      const Ark_NavPathInfo* info,
                      const Opt_NavigationOptions* options)
{
}
void ReplaceDestinationImpl(NavPathStackPeer* peer,
                            const Ark_NavPathInfo* info,
                            const Opt_NavigationOptions* options,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void ReplacePathByNameImpl(NavPathStackPeer* peer,
                           const Ark_String* name,
                           const Ark_CustomObject* param,
                           const Opt_Boolean* animated)
{
}
Ark_Int32 RemoveByIndexesImpl(NavPathStackPeer* peer,
                              const Array_Number* indexes)
{
    return 0;
}
Ark_Int32 RemoveByNameImpl(NavPathStackPeer* peer,
                           const Ark_String* name)
{
    return 0;
}
Ark_Boolean RemoveByNavDestinationIdImpl(NavPathStackPeer* peer,
                                         const Ark_String* navDestinationId)
{
    return 0;
}
Ark_NativePointer Pop0Impl(NavPathStackPeer* peer,
                           const Opt_Boolean* animated)
{
    Ark_NativePointer invalid = nullptr;
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    navStack->Nav::PathStack::Pop(Nav::PopResultType(), convAnimated);
    // convert the result of above to Ark_NavPathInfo here
    LOGE("NavPathStackAccessor::Pop0Impl - the result type does not match to documentation");
    return invalid;
}
Ark_NativePointer Pop1Impl(NavPathStackPeer* peer,
                           const Ark_CustomObject* result,
                           const Opt_Boolean* animated)
{
    Ark_NativePointer invalid = nullptr;
    LOGE("NavPathStackAccessor::Pop1Impl is not implemented yet.");
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(result, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto convAnimated = animated ? Converter::OptConvert<bool>(*animated) : std::nullopt;
    Nav::PopResultType convResult; // temp stub // Converter::Convert<Nav::ExternalData>(*result);
    navStack->Nav::PathStack::Pop(convResult, convAnimated);
    // convert the result of above to Ark_NavPathInfo here
    LOGE("NavPathStackAccessor::Pop1Impl - the result type does not match to documentation");
    return invalid;
}
Ark_Int32 PopToName0Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    return 0;
}
Ark_Int32 PopToName1Impl(NavPathStackPeer* peer,
                         const Ark_String* name,
                         const Ark_CustomObject* result,
                         const Opt_Boolean* animated)
{
    return 0;
}
void PopToIndex0Impl(NavPathStackPeer* peer,
                     const Ark_Number* index,
                     const Opt_Boolean* animated)
{
}
void PopToIndex1Impl(NavPathStackPeer* peer,
                     const Ark_Number* index,
                     const Ark_CustomObject* result,
                     const Opt_Boolean* animated)
{
}
Ark_Int32 MoveToTopImpl(NavPathStackPeer* peer,
                        const Ark_String* name,
                        const Opt_Boolean* animated)
{
    return 0;
}
void MoveIndexToTopImpl(NavPathStackPeer* peer,
                        const Ark_Number* index,
                        const Opt_Boolean* animated)
{
}
void ClearImpl(NavPathStackPeer* peer,
               const Opt_Boolean* animated)
{
}
void GetAllPathNameImpl(NavPathStackPeer* peer)
{
}
void GetParamByIndexImpl(NavPathStackPeer* peer,
                         const Ark_Number* index)
{
}
void GetParamByNameImpl(NavPathStackPeer* peer,
                        const Ark_String* name)
{
}
void GetIndexByNameImpl(NavPathStackPeer* peer,
                        const Ark_String* name)
{
}
Ark_NativePointer GetParentImpl(NavPathStackPeer* peer)
{
    return 0;
}
Ark_Int32 SizeImpl(NavPathStackPeer* peer)
{
    Ark_Int32 invalid = -111;
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(navStack->Nav::PathStack::Size()));
}
void DisableAnimationImpl(NavPathStackPeer* peer,
                          Ark_Boolean value)
{
}
void SetInterceptionImpl(NavPathStackPeer* peer,
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

}
