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
namespace NavPathStackAccessor {
void DestroyPeerImpl(Ark_NavPathStack peer)
{
}
Ark_NavPathStack CtorImpl()
{
    return nullptr;
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
}
void PushDestination1Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_NavigationOptions* options,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void PushPathByName0Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Opt_Boolean* animated)
{
}
void PushPathByName1Impl(Ark_NavPathStack peer,
                         const Ark_String* name,
                         const Ark_CustomObject* param,
                         const Callback_PopInfo_Void* onPop,
                         const Opt_Boolean* animated)
{
}
void PushDestinationByName0Impl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_NavPathStack peer,
                                const Ark_String* name,
                                const Ark_CustomObject* param,
                                const Opt_Boolean* animated,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
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
    return {};
}
Opt_NavPathInfo Pop1Impl(Ark_NavPathStack peer,
                         const Ark_CustomObject* result,
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
}
Array_String GetAllPathNameImpl(Ark_NavPathStack peer)
{
    return {};
}
Opt_CustomObject GetParamByIndexImpl(Ark_NavPathStack peer,
                                     const Ark_Number* index)
{
    return {};
}
Array_CustomObject GetParamByNameImpl(Ark_NavPathStack peer,
                                      const Ark_String* name)
{
    return {};
}
Array_Number GetIndexByNameImpl(Ark_NavPathStack peer,
                                const Ark_String* name)
{
    return {};
}
Opt_NavPathStack GetParentImpl(Ark_NavPathStack peer)
{
    return {};
}
Ark_Number SizeImpl(Ark_NavPathStack peer)
{
    return {};
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

}
