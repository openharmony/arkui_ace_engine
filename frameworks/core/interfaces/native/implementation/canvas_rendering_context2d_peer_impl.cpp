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

#include "core/common/container.h"
#include "core/interfaces/native/implementation/canvas_runtime_bridge.h"
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
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    if (bridge && bridge->createCanvasRenderingContext2DModel) {
        renderingContext2DModel_ = bridge->createCanvasRenderingContext2DModel();
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
        if (bridge->setCanvasRenderingContext2DCallbacks) {
            bridge->setCanvasRenderingContext2DCallbacks(
                renderingContext2DModel_, std::move(onAttach), std::move(onDetach));
        }
    }
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
        auto* bridge = GetCanvasRuntimeBridgeFromModule();
        if (bridge && bridge->startCanvasImageAnalyzer) {
            OnAnalyzedCallback optOnAnalyzed = std::move(onAnalyzed);
            void* config = wrapConfigFunc == nullptr ? nullptr : wrapConfigFunc();
            bridge->startCanvasImageAnalyzer(peer->renderingContext2DModel_, config, optOnAnalyzed);
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
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_VOID(bridge);
    CHECK_NULL_VOID(bridge->stopCanvasImageAnalyzer);
    bridge->stopCanvasImageAnalyzer(renderingContext2DModel_);
}
double CanvasRenderingContext2DPeerImpl::GetHeight()
{
    double height = 0.0;
    CHECK_NULL_RETURN(renderingContext2DModel_, height);
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, height);
    CHECK_NULL_RETURN(bridge->getCanvasRenderingContext2DHeight, height);
    bridge->getCanvasRenderingContext2DHeight(renderingContext2DModel_, height);
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
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, width);
    CHECK_NULL_RETURN(bridge->getCanvasRenderingContext2DWidth, width);
    bridge->getCanvasRenderingContext2DWidth(renderingContext2DModel_, width);
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
    auto* bridge = GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, -1);
    CHECK_NULL_RETURN(bridge->getCanvasRenderingContext2DId, -1);
    return bridge->getCanvasRenderingContext2DId(renderingContext2DModel_);
}
void CanvasRenderingContext2DPeerImpl::SetRenderingContextOptions(const RenderingContextOptions& options)
{
    CHECK_NULL_VOID(renderingContext2DModel_);
    renderingContext2DModel_->SetAntiAlias(options.antialias);
}
} // namespace OHOS::Ace::NG::GeneratedModifier
