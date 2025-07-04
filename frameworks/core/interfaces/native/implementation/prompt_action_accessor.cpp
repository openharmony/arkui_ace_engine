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
namespace PromptActionAccessor {
void DestroyPeerImpl(Ark_PromptAction peer)
{
}
Ark_PromptAction ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OpenPopupImpl(Ark_VMContext vmContext,
                   Ark_AsyncWorkerPtr asyncWorker,
                   Ark_PromptAction peer,
                   Ark_ComponentContent content,
                   const Ark_TargetInfo* target,
                   const Opt_PopupCommonOptions* options,
                   const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void UpatePopupImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_PromptAction peer,
                    Ark_ComponentContent content,
                    const Ark_PopupCommonOptions* options,
                    const Opt_Boolean* partialUpdate,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void ClosePopupImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_PromptAction peer,
                    Ark_ComponentContent content,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void OpenMenuImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  Ark_PromptAction peer,
                  Ark_ComponentContent content,
                  const Ark_TargetInfo* target,
                  const Opt_MenuOptions* options,
                  const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void UpdateMenuImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_PromptAction peer,
                    Ark_ComponentContent content,
                    const Ark_MenuOptions* options,
                    const Opt_Boolean* partialUpdate,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void CloseMenuImpl(Ark_VMContext vmContext,
                   Ark_AsyncWorkerPtr asyncWorker,
                   Ark_PromptAction peer,
                   Ark_ComponentContent content,
                   const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
} // PromptActionAccessor
const GENERATED_ArkUIPromptActionAccessor* GetPromptActionAccessor()
{
    static const GENERATED_ArkUIPromptActionAccessor PromptActionAccessorImpl {
        PromptActionAccessor::DestroyPeerImpl,
        PromptActionAccessor::ConstructImpl,
        PromptActionAccessor::GetFinalizerImpl,
        PromptActionAccessor::OpenPopupImpl,
        PromptActionAccessor::UpatePopupImpl,
        PromptActionAccessor::ClosePopupImpl,
        PromptActionAccessor::OpenMenuImpl,
        PromptActionAccessor::UpdateMenuImpl,
        PromptActionAccessor::CloseMenuImpl,
    };
    return &PromptActionAccessorImpl;
}

}
