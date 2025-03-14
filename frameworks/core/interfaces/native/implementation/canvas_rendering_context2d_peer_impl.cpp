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
#include "core/interfaces/native/utility/peer_utils.h"

namespace {
constexpr auto ERROR_VALUE = -1;
constexpr auto EMPTY_STRING = "";

} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {

void CanvasRenderingContext2DPeerImpl::SetCanvasPattern(const RefPtr<AceType>& pattern)
{
    CHECK_NULL_VOID(pattern);
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    if (pattern_ == canvasPattern) {
        return;
    }
    auto onAttach = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnAttachToCanvas();
    };
    auto onDetach = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnDetachFromCanvas();
    };
    pattern_ = canvasPattern;
    pattern_->SetOnContext2DAttach(onAttach);
    pattern_->SetOnContext2DDetach(onDetach);
    pattern_->AttachRenderContext();
}

void CanvasRenderingContext2DPeerImpl::OnAttachToCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : attachCallback_) {
        if (iter.IsValid()) {
            iter.Invoke();
        }
    }
}

void CanvasRenderingContext2DPeerImpl::OnDetachFromCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : detachCallback_) {
        if (iter.IsValid()) {
            iter.Invoke();
        }
    }
}

CanvasRenderingContext2DPeerImpl::CanvasCallbackIterator CanvasRenderingContext2DPeerImpl::FindCallbackInList(
    const CanvasCallbackList& callbackFuncPairList,
    const CallbackHelper<Callback_Void>& callback) const
{
    return std::find(callbackFuncPairList.begin(), callbackFuncPairList.end(), callback);
}

void CanvasRenderingContext2DPeerImpl::DeleteCallbackFromList(const CallbackHelper<Callback_Void>& callback,
    const CanvasCallbackType& type)
{
    if (!callback.IsValid()) {
        if (type == CanvasCallbackType::ON_ATTACH) {
            attachCallback_.clear();
        } else if (type == CanvasCallbackType::ON_DETACH) {
            detachCallback_.clear();
        }
        return;
    }
    if (type == CanvasCallbackType::ON_ATTACH) {
        auto iter = FindCallbackInList(attachCallback_, callback);
        if (iter != attachCallback_.end()) {
            attachCallback_.erase(iter);
        }
    } else if (type == CanvasCallbackType::ON_DETACH) {
        auto iter = FindCallbackInList(detachCallback_, callback);
        if (iter != detachCallback_.end()) {
            detachCallback_.erase(iter);
        }
    }
}

void CanvasRenderingContext2DPeerImpl::AddCallbackToList(CallbackHelper<Callback_Void> &&callback,
    const CanvasCallbackType& type)
{
    if (type == CanvasCallbackType::ON_ATTACH) {
        auto iter = FindCallbackInList(attachCallback_, callback);
        if (iter  == attachCallback_.end()) {
            attachCallback_.emplace_back(callback);
        }
    } else if (type == CanvasCallbackType::ON_DETACH) {
        auto iter = FindCallbackInList(detachCallback_, callback);
        if (iter == detachCallback_.end()) {
            detachCallback_.emplace_back(callback);
        }
    }
}

void CanvasRenderingContext2DPeerImpl::On(CallbackHelper<Callback_Void> &&callback, const CanvasCallbackType& type)
{
    AddCallbackToList(std::move(callback), type);
}

void CanvasRenderingContext2DPeerImpl::Off(CallbackHelper<Callback_Void> &&callback, const CanvasCallbackType& type)
{
    DeleteCallbackFromList(callback, type);
}

void CanvasRenderingContext2DPeerImpl::TriggerStartImageAnalyzer(const Ark_ImageAnalyzerConfig* config,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(pattern_);
    CHECK_NULL_VOID(config);
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    auto onError = [arkCallback = CallbackHelper(*outputArgumentForReturningPromise)]
        (std::vector<std::string> error) -> void {
        if (!error.empty()) {
            Converter::ArkArrayHolder<Array_String> stringHolder(error);
            Array_String stringArrayValues = stringHolder.ArkValue();
            auto arkError = Converter::ArkValue<Opt_Array_String>(stringArrayValues);
            arkCallback.Invoke(arkError);
        } else {
            auto arkEmptyMessage = Converter::ArkValue<Opt_Array_String>(Ark_Empty());
            arkCallback.Invoke(arkEmptyMessage);
        }
    };

    if (isImageAnalyzing_) {
        auto error = PeerUtils::CreateAIError(ImageAnalyzerState::ONGOING);
        onError(error);
        return;
    }

    auto vectorIATypes = Converter::Convert<std::vector<ImageAnalyzerType>>(config->types);
    std::set<ImageAnalyzerType> types(vectorIATypes.begin(), vectorIATypes.end());
    config_.types = std::move(types);
    void* aceConfig = reinterpret_cast<void*>(&config_);

    OnAnalyzedCallback onAnalyzed = [weakCtx = WeakClaim(this),
        callback = std::move(onError)](ImageAnalyzerState state) -> void {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto error = PeerUtils::CreateAIError(state);
        callback(error);
        ctx->isImageAnalyzing_ = false;
    };

    isImageAnalyzing_ = true;
    pattern_->StartImageAnalyzer(aceConfig, onAnalyzed);
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

double CanvasRenderingContext2DPeerImpl::TriggerGetHeight()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetHeight pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    return PipelineBase::Px2VpWithCurrentDensity(pattern_->GetHeight());
}

double CanvasRenderingContext2DPeerImpl::TriggerGetWidth()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetWidth pattern "
            "not bound to component.");
        return ::ERROR_VALUE;
    }
    return PipelineBase::Px2VpWithCurrentDensity(pattern_->GetWidth());
}

std::string CanvasRenderingContext2DPeerImpl::ToDataURL(const std::string& type, float& quality)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRenderingContext2DPeerImpl::TriggerGetWidth pattern not bound to component.");
        return EMPTY_STRING;
    }
    return pattern_->ToDataURL(type, quality);
}
} // namespace OHOS::Ace::NG::GeneratedModifier
