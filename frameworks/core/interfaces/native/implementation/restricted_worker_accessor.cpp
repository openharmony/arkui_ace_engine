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
namespace RestrictedWorkerAccessor {
void DestroyPeerImpl(Ark_RestrictedWorker peer)
{
}
Ark_RestrictedWorker CtorImpl(const Ark_String* scriptURL,
                              const Opt_WorkerOptions* options)
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void PostMessage0Impl(Ark_VMContext vmContext,
                      Ark_RestrictedWorker peer,
                      const Ark_Object* message,
                      const Array_Buffer* transfer)
{
}
void PostMessage1Impl(Ark_VMContext vmContext,
                      Ark_RestrictedWorker peer,
                      const Ark_Object* message,
                      const Opt_PostMessageOptions* options)
{
}
void PostMessageWithSharedSendableImpl(Ark_VMContext vmContext,
                                       Ark_RestrictedWorker peer,
                                       const Ark_Object* message,
                                       const Opt_Array_Buffer* transfer)
{
}
void OnImpl(Ark_VMContext vmContext,
            Ark_RestrictedWorker peer,
            const Ark_String* Type,
            Ark_WorkerEventListener listener)
{
}
void OnceImpl(Ark_VMContext vmContext,
              Ark_RestrictedWorker peer,
              const Ark_String* Type,
              Ark_WorkerEventListener listener)
{
}
void OffImpl(Ark_VMContext vmContext,
             Ark_RestrictedWorker peer,
             const Ark_String* Type,
             const Opt_WorkerEventListener* listener)
{
}
void TerminateImpl(Ark_VMContext vmContext,
                   Ark_RestrictedWorker peer)
{
}
void AddEventListenerImpl(Ark_VMContext vmContext,
                          Ark_RestrictedWorker peer,
                          const Ark_String* Type,
                          Ark_WorkerEventListener listener)
{
}
Ark_Boolean DispatchEventImpl(Ark_VMContext vmContext,
                              Ark_RestrictedWorker peer,
                              const Ark_Event* event)
{
    return {};
}
void RemoveEventListenerImpl(Ark_VMContext vmContext,
                             Ark_RestrictedWorker peer,
                             const Ark_String* Type,
                             const Opt_WorkerEventListener* callback_)
{
}
void RemoveAllListenerImpl(Ark_VMContext vmContext,
                           Ark_RestrictedWorker peer)
{
}
void RegisterGlobalCallObjectImpl(Ark_VMContext vmContext,
                                  Ark_RestrictedWorker peer,
                                  const Ark_String* instanceName,
                                  const Ark_Object* globalCallObject)
{
}
void UnregisterGlobalCallObjectImpl(Ark_VMContext vmContext,
                                    Ark_RestrictedWorker peer,
                                    const Opt_String* instanceName)
{
}
Opt_RestrictedWorker_onexit_Callback GetOnexitImpl(Ark_RestrictedWorker peer)
{
    return {};
}
void SetOnexitImpl(Ark_RestrictedWorker peer,
                   const RestrictedWorker_onexit_Callback* onexit)
{
}
Opt_RestrictedWorker_onerror_Callback GetOnerrorImpl(Ark_RestrictedWorker peer)
{
    return {};
}
void SetOnerrorImpl(Ark_RestrictedWorker peer,
                    const RestrictedWorker_onerror_Callback* onerror)
{
}
Opt_RestrictedWorker_onmessage_Callback GetOnmessageImpl(Ark_RestrictedWorker peer)
{
    return {};
}
void SetOnmessageImpl(Ark_RestrictedWorker peer,
                      const RestrictedWorker_onmessage_Callback* onmessage)
{
}
Opt_RestrictedWorker_onmessage_Callback GetOnmessageerrorImpl(Ark_RestrictedWorker peer)
{
    return {};
}
void SetOnmessageerrorImpl(Ark_RestrictedWorker peer,
                           const RestrictedWorker_onmessage_Callback* onmessageerror)
{
}
} // RestrictedWorkerAccessor
const GENERATED_ArkUIRestrictedWorkerAccessor* GetRestrictedWorkerAccessor()
{
    static const GENERATED_ArkUIRestrictedWorkerAccessor RestrictedWorkerAccessorImpl {
        RestrictedWorkerAccessor::DestroyPeerImpl,
        RestrictedWorkerAccessor::CtorImpl,
        RestrictedWorkerAccessor::GetFinalizerImpl,
        RestrictedWorkerAccessor::PostMessage0Impl,
        RestrictedWorkerAccessor::PostMessage1Impl,
        RestrictedWorkerAccessor::PostMessageWithSharedSendableImpl,
        RestrictedWorkerAccessor::OnImpl,
        RestrictedWorkerAccessor::OnceImpl,
        RestrictedWorkerAccessor::OffImpl,
        RestrictedWorkerAccessor::TerminateImpl,
        RestrictedWorkerAccessor::AddEventListenerImpl,
        RestrictedWorkerAccessor::DispatchEventImpl,
        RestrictedWorkerAccessor::RemoveEventListenerImpl,
        RestrictedWorkerAccessor::RemoveAllListenerImpl,
        RestrictedWorkerAccessor::RegisterGlobalCallObjectImpl,
        RestrictedWorkerAccessor::UnregisterGlobalCallObjectImpl,
        RestrictedWorkerAccessor::GetOnexitImpl,
        RestrictedWorkerAccessor::SetOnexitImpl,
        RestrictedWorkerAccessor::GetOnerrorImpl,
        RestrictedWorkerAccessor::SetOnerrorImpl,
        RestrictedWorkerAccessor::GetOnmessageImpl,
        RestrictedWorkerAccessor::SetOnmessageImpl,
        RestrictedWorkerAccessor::GetOnmessageerrorImpl,
        RestrictedWorkerAccessor::SetOnmessageerrorImpl,
    };
    return &RestrictedWorkerAccessorImpl;
}

}
