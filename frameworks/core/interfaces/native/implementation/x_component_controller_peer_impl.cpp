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


void XComponentControllerPeer::TriggerStartImageAnalyzer(const Ark_ImageAnalyzerConfig* config,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(controller);
    CHECK_NULL_VOID(config);
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    auto onError = [arkCallback = OHOS::Ace::NG::CallbackHelper(*outputArgumentForReturningPromise)]
        (std::vector<std::string> error) -> void {
        if (!error.empty()) {
            OHOS::Ace::NG::Converter::ArkArrayHolder<Array_String> stringHolder(error);
            Array_String stringArrayValues = stringHolder.ArkValue();
            auto arkError = OHOS::Ace::NG::Converter::ArkValue<Opt_Array_String>(stringArrayValues);
            arkCallback.Invoke(arkError);
        } else {
            auto arkEmptyMessage = OHOS::Ace::NG::Converter::ArkValue<Opt_Array_String>(Ark_Empty());
            arkCallback.Invoke(arkEmptyMessage);
        }
    };

    if (isImageAnalyzing_) {
        auto error = PeerUtils::CreateAIError(OHOS::Ace::ImageAnalyzerState::ONGOING);
        onError(error);
        return;
    }

    auto vectorIATypes = OHOS::Ace::NG::Converter::Convert<std::vector<OHOS::Ace::ImageAnalyzerType>>(config->types);
    std::set<OHOS::Ace::ImageAnalyzerType> types(vectorIATypes.begin(), vectorIATypes.end());
    config_.types = std::move(types);
    void* aceConfig = reinterpret_cast<void*>(&config_);

    OHOS::Ace::OnAnalyzedCallback onAnalyzed =
        [weakCtx = OHOS::Ace::Referenced::WeakClaim(this), callback = std::move(onError)]
        (OHOS::Ace::ImageAnalyzerState state) -> void {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto error = PeerUtils::CreateAIError(state);
        callback(error);
        ctx->isImageAnalyzing_ = false;
    };

    isImageAnalyzing_ = true;
    controller->StartImageAnalyzer(aceConfig, onAnalyzed);
}
#endif // XCOMPONENT_SUPPORTED
