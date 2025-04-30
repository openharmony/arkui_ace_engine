/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "x_component_controller_peer_impl.h"

#ifdef XCOMPONENT_SUPPORTED
#include "base/utils/utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/promise_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
void XComponentControllerPeerImpl::TriggerStartImageAnalyzer(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
    const Ark_ImageAnalyzerConfig* config, const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    CHECK_NULL_VOID(config);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    if (isImageAnalyzing_) {
        promise->Reject(PeerUtils::CreateAIError(ImageAnalyzerState::ONGOING));
        return;
    }
    isImageAnalyzing_ = true;

    auto onAnalyzed = [peer = Claim(this), promise](ImageAnalyzerState state) {
        peer->isImageAnalyzing_ = false;
        auto error = PeerUtils::CreateAIError(state);
        if (error.empty()) {
            promise->Resolve();
        } else {
            promise->Reject(error);
        }
    };
    auto vectorIATypes = Converter::Convert<std::vector<ImageAnalyzerType>>(config->types);
    std::set<ImageAnalyzerType> types(vectorIATypes.begin(), vectorIATypes.end());
    config_ = {
        .types = std::move(types)
    };

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), onAnalyzed = std::move(onAnalyzed)]() {
        if (peer->controller) {
            OnAnalyzedCallback optOnAnalyzed = std::move(onAnalyzed);
            peer->controller->StartImageAnalyzer(reinterpret_cast<void*>(&peer->config_), optOnAnalyzed);
        } else {
            onAnalyzed(ImageAnalyzerState::STOPPED);
        }
    });
}
} // namespace OHOS::Ace::NG::GeneratedModifier

#endif // XCOMPONENT_SUPPORTED
