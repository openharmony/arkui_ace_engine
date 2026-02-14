/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerExtenderAccessor {
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_XComponentController peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    peer->TriggerStartImageAnalyzer(vmContext, asyncWorker, config, outputArgumentForReturningPromise);
#endif //XCOMPONENT_SUPPORTED
}
} // XComponentControllerExtenderAccessor
const GENERATED_ArkUIXComponentControllerExtenderAccessor* GetXComponentControllerExtenderAccessor()
{
    static const GENERATED_ArkUIXComponentControllerExtenderAccessor XComponentControllerExtenderAccessorImpl {
        XComponentControllerExtenderAccessor::StartImageAnalyzerImpl,
    };
    return &XComponentControllerExtenderAccessorImpl;
}

}
