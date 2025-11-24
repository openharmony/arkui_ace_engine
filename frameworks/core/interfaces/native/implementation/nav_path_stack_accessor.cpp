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
#include "core/interfaces/native/utility/promise_helper.h"
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
Ark_NavPathStack ConstructImpl()
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
    CHECK_NULL_VOID(animated);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    NavigationOptions navOptions;
    if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        navOptions.animated = Converter::Convert<bool>(animated->value);
    }
    peer->SetInstanceId(1);
    navStack->NavigationContext::PathStack::PushPath(navInfo, navOptions);
}
void PushPath1Impl(Ark_NavPathStack peer,
                   Ark_NavPathInfo info,
                   const Opt_NavigationOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(options);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    NavigationOptions navOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        navOptions = Converter::Convert<NavigationOptions>(options->value);
    }
    peer->SetInstanceId(1);
    navStack->NavigationContext::PathStack::PushPath(navInfo, navOptions);
}
void PushDestination0Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_Boolean* animated,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](int32_t errorCode, std::string errorMessage) {
        if (errorCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({ std::to_string(errorCode), errorMessage });
        }
    };

    auto execFunc = [peer, info, animated, finishFunc]() {
        CHECK_NULL_VOID(peer);
        CHECK_NULL_VOID(info);
        auto navStack = peer->GetNavPathStack();
        if (!navStack) {
            LOGE("NavPathStackAccessor::PushDestination0Impl. Navigation Stack isn't bound to a component.");
            finishFunc(ERROR_CODE_PARAM_INVALID,
                "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified; 2. Incorrect "
                "parameter types; 3. Parameter verification failed.");
            return;
        }
        auto navInfo = info->data;
        navInfo.promise_ = finishFunc;
        Ark_NavigationOptions options;
        options.animated = *animated;
        auto navOptions = Converter::Convert<NavigationOptions>(options);
        navStack->NavigationContext::PathStack::PushDestination(navInfo, navOptions);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void PushDestination1Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_NavigationOptions* options,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](int32_t errorCode, std::string errorMessage) {
        if (errorCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({ std::to_string(errorCode), errorMessage });
        }
    };

    auto execFunc = [peer, info, options, finishFunc]() {
        CHECK_NULL_VOID(peer);
        CHECK_NULL_VOID(info);
        auto navStack = peer->GetNavPathStack();
        if (!navStack) {
            LOGE("NavPathStackAccessor::PushDestination0Impl. Navigation Stack isn't bound to a component.");
            finishFunc(ERROR_CODE_PARAM_INVALID,
                "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified; 2. Incorrect "
                "parameter types; 3. Parameter verification failed.");
            return;
        }
        auto navInfo = info->data;
        navInfo.promise_ = finishFunc;
        auto navOptions = Converter::Convert<NavigationOptions>(options->value);
        navStack->NavigationContext::PathStack::PushDestination(navInfo, navOptions);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void PushPathByName0Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Opt_Object* param,
                         const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    auto navStack = peer->GetNavPathStack();
    if (!navStack) {
        LOGE("NavPathStackAccessor::PushPathByName0Impl. Navigation Stack isn't bound to a component.");
        return;
    }

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::OptConvertPtr<Nav::ExternalData>(param).value_or(Nav::ExternalData{});
    auto convAnimated = Converter::OptConvertPtr<bool>(animated);
    navStack->Nav::PathStack::PushPathByName(convName, convParam, nullptr, convAnimated);
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
    auto convOnPop = AceType::MakeRefPtr<CallbackHelper<Callback_PopInfo_Void>>(*onPop);
    auto convAnimated = Converter::OptConvertPtr<bool>(animated);
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
    CHECK_NULL_VOID(peer && name && param && animated && outputArgumentForReturningPromise);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](int32_t errorCode, std::string errorMessage) {
        if (errorCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({ std::to_string(errorCode), errorMessage });
        }
    };

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    auto info = std::make_shared<NavigationContext::PathInfo>(convName, convParam);

    auto execFunc = [peer, info, convAnimated, finishFunc]() {
        auto navStack = peer->GetNavPathStack();
        if (!navStack) {
            LOGE("NavPathStackAccessor::PushDestinationByName0Impl. Navigation Stack isn't bound to a component.");
            finishFunc(ERROR_CODE_PARAM_INVALID,
                "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified; 2. Incorrect "
                "parameter types; 3. Parameter verification failed.");
            return;
        }
        info->promise_ = finishFunc;
        navStack->NavigationContext::PathStack::PushDestinationByName(info->name_, info->param_, nullptr, convAnimated);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
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
    CHECK_NULL_VOID(peer && name && param && onPop && animated && outputArgumentForReturningPromise);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](int32_t errorCode, std::string errorMessage) {
        if (errorCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({ std::to_string(errorCode), errorMessage });
        }
    };

    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convOnPop = AceType::MakeRefPtr<CallbackHelper<Callback_PopInfo_Void>>(*onPop);
    auto convAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    auto info = std::make_shared<NavigationContext::PathInfo>(convName, convParam, convOnPop);

    auto execFunc = [peer, info, convAnimated, finishFunc]() {
        auto navStack = peer->GetNavPathStack();
        if (!navStack) {
            LOGE("NavPathStackAccessor::PushDestinationByName1Impl. Navigation Stack isn't bound to a component.");
            finishFunc(ERROR_CODE_PARAM_INVALID,
                "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified; 2. Incorrect "
                "parameter types; 3. Parameter verification failed.");
            return;
        }
        info->promise_ = finishFunc;
        navStack->NavigationContext::PathStack::PushDestinationByName(
            info->name_, info->param_, info->onPop_, convAnimated);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void ReplacePath0Impl(Ark_NavPathStack peer,
                      Ark_NavPathInfo info,
                      const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(animated);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    NavigationOptions navOptions;
    if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        navOptions.animated = Converter::Convert<bool>(animated->value);
    }
    navStack->NavigationContext::PathStack::ReplacePath(navInfo, navOptions);
}
void ReplacePath1Impl(Ark_NavPathStack peer,
                      Ark_NavPathInfo info,
                      const Opt_NavigationOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(options);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto navInfo = Converter::Convert<NavigationContext::PathInfo>(info);
    NavigationOptions navOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        navOptions = Converter::Convert<NavigationOptions>(options->value);
    }
    navStack->NavigationContext::PathStack::ReplacePath(navInfo, navOptions);
}
void ReplaceDestinationImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_NavPathStack peer,
                            Ark_NavPathInfo info,
                            const Opt_NavigationOptions* options,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    auto finishFunc = [promise](int32_t errorCode, std::string errorMessage) {
        if (errorCode == ERROR_CODE_NO_ERROR) {
            promise->Resolve();
        } else {
            promise->Reject({ std::to_string(errorCode), errorMessage });
        }
    };

    auto execFunc = [peer, info, options, finishFunc]() {
        CHECK_NULL_VOID(peer);
        CHECK_NULL_VOID(info);
        auto navStack = peer->GetNavPathStack();
        if (!navStack) {
            LOGE("NavPathStackAccessor::PushDestination0Impl. Navigation Stack isn't bound to a component.");
            finishFunc(ERROR_CODE_PARAM_INVALID,
                "Parameter error. Possible causes: 1. Mandatory parameters are left unspecified; 2. Incorrect "
                "parameter types; 3. Parameter verification failed.");
            return;
        }
        auto navInfo = info->data;
        navInfo.promise_ = finishFunc;
        auto navOptions = Converter::Convert<NavigationOptions>(options->value);
        navStack->NavigationContext::PathStack::ReplaceDestination(navInfo, navOptions);
    };
    promise->StartAsync(vmContext, *asyncWorker, execFunc);
}
void ReplacePathByNameImpl(Ark_NavPathStack peer,
                           const Ark_String* name,
                           const Ark_Object* param,
                           const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer && name && param && animated);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto convName = Converter::Convert<std::string>(*name);
    auto convParam = Converter::Convert<Nav::ExternalData>(*param);
    auto convAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    navStack->NavigationContext::PathStack::ReplacePathByName(convName, convParam, convAnimated);
}
Ark_Int32 RemoveByIndexesImpl(Ark_NavPathStack peer,
                              const Array_Int32* indexes)
{
    auto invalidVal = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(indexes, invalidVal);
    auto removeIndexes = Converter::Convert<std::vector<int>>(*indexes);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto size = navStack->PathStack::RemoveByIndexes(removeIndexes);
    return Converter::ArkValue<Ark_Int32>(size);
}
Ark_Int32 RemoveByNameImpl(Ark_NavPathStack peer,
                           const Ark_String* name)
{
    auto invalidVal = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(name, invalidVal);
    auto removeName = Converter::Convert<std::string>(*name);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto size = navStack->RemoveByName(removeName);
    return Converter::ArkValue<Ark_Int32>(size);
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
    Opt_NavPathInfo invalidVal = {
        .tag = InteropTag::INTEROP_TAG_UNDEFINED
    };
    CHECK_NULL_RETURN(peer, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    NavigationContext::PathInfo info;
    if (!navStack->NavigationContext::PathStack::Pop(isAnimated, info)) {
        return invalidVal;
    }
    auto arkInfo = Converter::ArkValue<Ark_NavPathInfo>(info);
    CHECK_NULL_RETURN(arkInfo, invalidVal);
    Opt_NavPathInfo retVal = {
        .tag = InteropTag::INTEROP_TAG_OBJECT,
        .value = arkInfo
    };
    return retVal;
}
Opt_NavPathInfo Pop1Impl(Ark_NavPathStack peer,
                         const Ark_Object* result,
                         const Opt_Boolean* animated)
{
    Opt_NavPathInfo invalidVal = {
        .tag = InteropTag::INTEROP_TAG_UNDEFINED
    };
    CHECK_NULL_RETURN(peer, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    NavigationContext::PathInfo info;
    if (!navStack->NavigationContext::PathStack::Pop(isAnimated, *result, info)) {
        return invalidVal;
    }
    auto arkInfo = Converter::ArkValue<Ark_NavPathInfo>(info);
    CHECK_NULL_RETURN(arkInfo, invalidVal);
    Opt_NavPathInfo retVal = {
        .tag = InteropTag::INTEROP_TAG_OBJECT,
        .value = arkInfo
    };
    return retVal;
}
Ark_Int32 PopToName0Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Opt_Boolean* animated)
{
    static Ark_Int32 invalidVal = Converter::ArkValue<Ark_Int32>(-1);
    CHECK_NULL_RETURN(peer, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto nameVal = Converter::Convert<std::string>(*name);
    auto animatedVal = Converter::OptConvertPtr<bool>(animated).value_or(true);
    auto index = navStack->NavigationContext::PathStack::PopToName(nameVal, animatedVal);
    return Converter::ArkValue<Ark_Int32>(index);
}
Ark_Int32 PopToName1Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_Object* result,
                         const Opt_Boolean* animated)
{
    static Ark_Int32 invalidVal = Converter::ArkValue<Ark_Int32>(-1);
    CHECK_NULL_RETURN(peer, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto nameVal = Converter::Convert<std::string>(*name);
    auto animatedVal = Converter::OptConvertPtr<bool>(animated).value_or(true);
    auto index = navStack->NavigationContext::PathStack::PopToName(nameVal, animatedVal, *result);
    return Converter::ArkValue<Ark_Int32>(index);
}
void PopToIndex0Impl(Ark_NavPathStack peer,
                     Ark_Int32 index,
                     const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto indexVal = Converter::Convert<int32_t>(index);
    auto animatedVal = Converter::OptConvertPtr<bool>(animated).value_or(true);
    navStack->NavigationContext::PathStack::PopToIndex(indexVal, animatedVal);
}
void PopToIndex1Impl(Ark_NavPathStack peer,
                     Ark_Int32 index,
                     const Ark_Object* result,
                     const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto indexVal = Converter::Convert<int32_t>(index);
    auto animatedVal = Converter::OptConvertPtr<bool>(animated).value_or(true);
    navStack->NavigationContext::PathStack::PopToIndex(indexVal, animatedVal, *result);
}
Ark_Int32 MoveToTopImpl(Ark_NavPathStack peer,
                        const Ark_String* name,
                        const Opt_Boolean* animated)
{
    auto invalidVal = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    CHECK_NULL_RETURN(name, invalidVal);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalidVal);
    auto pathName = Converter::Convert<std::string>(*name);
    bool isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    auto index = navStack->NavigationContext::PathStack::MoveToTop(pathName, isAnimated);
    return Converter::ArkValue<Ark_Int32>(index);
}
void MoveIndexToTopImpl(Ark_NavPathStack peer,
                        Ark_Int32 index,
                        const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(animated);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto indexNum = Converter::Convert<std::uint32_t>(index);
    bool isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
    navStack->NavigationContext::PathStack::MoveIndexToTop(indexNum, isAnimated);
}
void ClearImpl(Ark_NavPathStack peer,
               const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navStack);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(true);
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
                               Ark_Int32 index)
{
    Opt_Object invalid = {
        .tag = InteropTag::INTEROP_TAG_UNDEFINED
    };
    CHECK_NULL_RETURN(peer, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto paramIndex = Converter::Convert<int32_t>(index);
    auto param = navStack->GetParamByIndex(paramIndex);
    CHECK_NULL_RETURN(param, invalid);
    Opt_Object retVal = param->data_;
    return retVal;
}
Array_Opt_Object GetParamByNameImpl(Ark_NavPathStack peer,
                                    const Ark_String* name)
{
    Array_Opt_Object invalid = {
        .length = 0
    };
    CHECK_NULL_RETURN(peer && name, invalid);
    auto navStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(navStack, invalid);
    auto paramName = Converter::Convert<std::string>(*name);
    auto params = navStack->GetParamByName(paramName);
    return Converter::ArkValue<Array_Opt_Object>(params, Converter::FC);
}
Array_Int32 GetIndexByNameImpl(Ark_NavPathStack peer,
                               const Ark_String* name)
{
    CHECK_NULL_RETURN(peer, {});
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, {});
    auto pathName = Converter::Convert<std::string>(*name);
    std::vector<size_t> allIndexes = pathStack->NavigationContext::PathStack::GetIndexByName(pathName);
    std::vector<uint32_t> indexes;
    indexes.assign(allIndexes.begin(), allIndexes.end());
    Array_Int32 result = Converter::ArkValue<Array_Int32>(indexes, Converter::FC);
    return result;
}
Opt_NavPathStack GetParentImpl(Ark_NavPathStack peer)
{
    Opt_NavPathStack invalid = {
        .tag = InteropTag::INTEROP_TAG_UNDEFINED,
    };
    CHECK_NULL_RETURN(peer, invalid);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, invalid);
    auto parentStack = pathStack->GetParent();
    CHECK_NULL_RETURN(parentStack, invalid);
    Opt_NavPathStack retVal = {
        .tag = InteropTag::INTEROP_TAG_OBJECT,
        .value = new NavPathStackPeer(parentStack)
    };
    return retVal;
}
Ark_Int32 SizeImpl(Ark_NavPathStack peer)
{
    auto invalidVal = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, invalidVal);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, invalidVal);
    auto size = static_cast<int32_t>(pathStack->NavigationContext::PathStack::Size());
    return Converter::ArkValue<Ark_Int32>(size);
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
    Array_NavPathInfo invalid = {
        .length = 0
    };
    CHECK_NULL_RETURN(peer, invalid);
    auto pathStack = peer->GetNavPathStack();
    CHECK_NULL_RETURN(pathStack, invalid);
    auto pathArray = pathStack->NavigationContext::PathStack::GetAllPathInfo();
    Array_NavPathInfo result = Converter::ArkValue<Array_NavPathInfo>(pathArray, Converter::FC);
    return result;
}
void SetPathStackImpl(Ark_NavPathStack peer,
                      const Array_NavPathInfo* pathStack,
                      const Opt_Boolean* animated)
{
    CHECK_NULL_VOID(peer && pathStack);
    auto navPathStack = peer->GetNavPathStack();
    CHECK_NULL_VOID(navPathStack);
    std::vector<NavigationContext::PathInfo> pathArray;
    for (int32_t i = 0; i < pathStack->length; i++) {
        NavigationContext::PathInfo info = Converter::Convert<NavigationContext::PathInfo>(pathStack->array[i]);
        pathArray.push_back(info);
    }
    bool convertAnimate = Converter::OptConvertPtr<bool>(animated).value_or(true);
    navPathStack->SetPathInfo(pathArray, convertAnimate);
}
} // NavPathStackAccessor
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor()
{
    static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
        NavPathStackAccessor::DestroyPeerImpl,
        NavPathStackAccessor::ConstructImpl,
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

struct NavPathStackPeer {
    virtual ~NavPathStackPeer() = default;
};
}
