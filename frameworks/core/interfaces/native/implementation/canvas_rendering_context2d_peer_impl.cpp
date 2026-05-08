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

#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/promise_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "canvas_rendering_context2d_peer_impl.h"
#include "image_bitmap_peer_impl.h"
#include "rendering_context_settings_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
CanvasRenderingContext2DPeerImpl::CanvasRenderingContext2DPeerImpl()
{
#ifdef NG_BUILD
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
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
        auto canvasRenderingContext2DModel =
            AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
        CHECK_NULL_VOID(canvasRenderingContext2DModel);
        canvasRenderingContext2DModel->SetOnAttach(onAttach);
        canvasRenderingContext2DModel->SetOnDetach(onDetach);
    } else {
        renderingContext2DModel_ = nullptr;
    }
#endif
}
void CanvasRenderingContext2DPeerImpl::SetOptions(const std::optional<RenderingContextSettingsPeer*>& optSettings)
{
    if (optSettings && optSettings.value() && optSettings.value()->antialias) {
        bool anti = optSettings.value()->antialias.value();
        SetAnti(anti);
    }
}
void CanvasRenderingContext2DPeerImpl::OnAttachToCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : attachCallback_) {
        if (iter.second) {
            iter.second();
        }
    }
}
void CanvasRenderingContext2DPeerImpl::OnDetachFromCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : detachCallback_) {
        if (iter.second) {
            iter.second();
        }
    }
}
CanvasRenderingContext2DPeerImpl::CanvasCallbackIterator CanvasRenderingContext2DPeerImpl::FindCallbackInList(
    const CanvasCallbackList& callbackFuncPairList, int32_t callbackId) const
{
    return std::find_if(callbackFuncPairList.begin(), callbackFuncPairList.end(),
        [callbackId](const auto& item) -> bool { return (callbackId == item.first); });
}
void CanvasRenderingContext2DPeerImpl::DeleteCallbackFromList(
    const std::function<void()>& callback, const CanvasCallbackType& type)
{
    if (!callback) {
        if (type == CanvasCallbackType::ON_ATTACH) {
            attachCallback_.clear();
        } else if (type == CanvasCallbackType::ON_DETACH) {
            detachCallback_.clear();
        }
        return;
    }
    if (type == CanvasCallbackType::ON_ATTACH) {
        if (attachCallbackId_ == -1) {
            return;
        }
        auto iter = FindCallbackInList(attachCallback_, attachCallbackId_);
        if (iter != attachCallback_.end()) {
            attachCallback_.erase(iter);
        }
    } else if (type == CanvasCallbackType::ON_DETACH) {
        if (detachCallbackId_ == -1) {
            return;
        }
        auto iter = FindCallbackInList(detachCallback_, detachCallbackId_);
        if (iter != detachCallback_.end()) {
            detachCallback_.erase(iter);
        }
    }
}
void CanvasRenderingContext2DPeerImpl::AddCallbackToList(
    std::function<void()>&& callback, const CanvasCallbackType& type)
{
    if (type == CanvasCallbackType::ON_ATTACH) {
        auto iter = FindCallbackInList(attachCallback_, attachCallbackId_);
        if (iter  == attachCallback_.end()) {
            attachCallback_.emplace_back(attachCallbackId_, callback);
        }
    } else if (type == CanvasCallbackType::ON_DETACH) {
        auto iter = FindCallbackInList(detachCallback_, detachCallbackId_);
        if (iter == detachCallback_.end()) {
            detachCallback_.emplace_back(detachCallbackId_, callback);
        }
    }
}
void CanvasRenderingContext2DPeerImpl::On(std::function<void()> &&callback, const CanvasCallbackType& type)
{
    AddCallbackToList(std::move(callback), type);
}
void CanvasRenderingContext2DPeerImpl::Off(std::function<void()> &&callback, const CanvasCallbackType& type)
{
    DeleteCallbackFromList(callback, type);
}
void CanvasRenderingContext2DPeerImpl::StartImageAnalyzer(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
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

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), wrapConfigFunc = wrapAnalyzerConfigImpl,
        onAnalyzed = std::move(onAnalyzed)]() {
        auto model = AceType::DynamicCast<CanvasRenderingContext2DModel>(peer->renderingContext2DModel_);
        if (model) {
            OnAnalyzedCallback optOnAnalyzed = std::move(onAnalyzed);
            void* config = wrapConfigFunc == nullptr ? nullptr : wrapConfigFunc();
            model->StartImageAnalyzer(config, optOnAnalyzed);
        } else {
            onAnalyzed(ImageAnalyzerState::STOPPED);
        }
    });
    wrapAnalyzerConfigImpl = nullptr;
}
void CanvasRenderingContext2DPeerImpl::StopImageAnalyzer()
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    ContainerScope scope(instanceId_);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->StopImageAnalyzer();
}
double CanvasRenderingContext2DPeerImpl::GetHeight()
{
    double height = 0.0;
    CHECK_NULL_RETURN(renderingContext2DModel_, height);
    auto renderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_RETURN(renderingContext2DModel_, height);
    renderingContext2DModel->GetHeight(height);
    double density = GetDensity();
    if (density == 0) {
        return height;
    }
    height /= density;
    return height;
}
double CanvasRenderingContext2DPeerImpl::GetWidth()
{
    double width = 0.0;
    CHECK_NULL_RETURN(renderingContext2DModel_, width);
    auto renderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_RETURN(renderingContext2DModel_, width);
    renderingContext2DModel->GetWidth(width);
    double density = GetDensity();
    if (density == 0) {
        return width;
    }
    width /= density;
    return width;
}
int32_t CanvasRenderingContext2DPeerImpl::GetCanvasId()
{
    CHECK_NULL_RETURN(renderingContext2DModel_, -1);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_RETURN(canvasRenderingContext2DModel, -1);
    return canvasRenderingContext2DModel->GetId();
}
void CanvasRenderingContext2DPeerImpl::SetRenderingContextOptions(const RenderingContextOptions& options)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetAntiAlias(options.antialias);
}
} // namespace OHOS::Ace::NG::GeneratedModifier
