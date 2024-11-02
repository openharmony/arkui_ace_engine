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

#include "canvas_rendering_context2d_peer_impl.h"

namespace {
constexpr auto ERROR_VALUE = -1;

} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {

Ark_NativePointer CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer(
    const std::vector<ImageAnalyzerType> vector)
{
    if (isImageAnalyzing_) {
        return 0;
    }
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer pattern "
             "not bound to component.");
        return 0;
    }

    vector_ = vector;
    void* config = reinterpret_cast<void*>(&vector_);

    OnAnalyzedCallback onAnalyzed = [weakCtx = WeakClaim(this)](ImageAnalyzerState state) -> void {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->isImageAnalyzing_ = false;
    };

    isImageAnalyzing_ = true;
    pattern_->StartImageAnalyzer(config, onAnalyzed);
    LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer return pointer not implemented.");
    return 0;
}

void CanvasRenderingContext2DPeerImpl::TriggerStopImageAnalyzer()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerStopImageAnalyzer pattern "
            "not bound to component.");
        return;
    }
    pattern_->StopImageAnalyzer();
}

Ark_Int32 CanvasRenderingContext2DPeerImpl::TriggerGetHeight()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetHeight pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    auto height = PipelineBase::Px2VpWithCurrentDensity(pattern_-> GetHeight());
    return  Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(height));
}

Ark_Int32 CanvasRenderingContext2DPeerImpl::TriggerGetWidth()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetWidth pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    auto width = PipelineBase::Px2VpWithCurrentDensity(pattern_-> GetWidth());
    return  Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(width));
}

} // namespace OHOS::Ace::NG::GeneratedModifier
