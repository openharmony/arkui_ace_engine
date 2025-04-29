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
#include "core/interfaces/native/utility/peer_utils.h"

#ifdef XCOMPONENT_SUPPORTED
#include "base/utils/utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/promise_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
void XComponentControllerPeerImpl::TriggerStartImageAnalyzer(const Ark_ImageAnalyzerConfig* config,
    PromiseHelper<Callback_Opt_Array_String_Void>&& promise)
{
    if (!controller || !config) {
        Converter::ArkArrayHolder<Array_String> vectorHolder({"the arguments are not valid"});
        promise.Reject(vectorHolder.OptValue<Opt_Array_String>());
        return;
    }
    if (isImageAnalyzing_) {
        auto error = PeerUtils::CreateAIError(ImageAnalyzerState::ONGOING);
        Converter::ArkArrayHolder<Array_String> errorHolder(error);
        promise.Reject(errorHolder.OptValue<Opt_Array_String>());
        return;
    }

    auto vectorIATypes = Converter::Convert<std::vector<ImageAnalyzerType>>(config->types);
    std::set<ImageAnalyzerType> types(vectorIATypes.begin(), vectorIATypes.end());
    config_.types = std::move(types);
    void* aceConfig = reinterpret_cast<void*>(&config_);

    OnAnalyzedCallback onAnalyzed = [weakCtx = Referenced::WeakClaim(this), promise = std::move(promise)](
            ImageAnalyzerState state) -> void {
        auto ctx = weakCtx.Upgrade();
        if (ctx == nullptr) {
            Converter::ArkArrayHolder<Array_String> errorHolder({"the object is null"});
            promise.Reject(errorHolder.OptValue<Opt_Array_String>());
            return;
        }
        auto error = PeerUtils::CreateAIError(state);
        if (error.empty()) {
            promise.Resolve(Converter::ArkValue<Opt_Array_String>(Ark_Empty()));
        } else {
            Converter::ArkArrayHolder<Array_String> errorHolder(error);
            promise.Reject(errorHolder.OptValue<Opt_Array_String>());
        }
        ctx->isImageAnalyzing_ = false;
    };

    isImageAnalyzing_ = true;
    controller->StartImageAnalyzer(aceConfig, onAnalyzed);
}
} // namespace OHOS::Ace::NG::GeneratedModifier

#endif // XCOMPONENT_SUPPORTED
