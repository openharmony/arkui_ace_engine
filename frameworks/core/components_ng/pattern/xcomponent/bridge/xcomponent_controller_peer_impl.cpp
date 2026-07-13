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

#ifdef XCOMPONENT_SUPPORTED
#include "xcomponent_controller_peer_impl.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/promise_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
std::shared_ptr<InnerXComponentController> GetInnerController(const std::shared_ptr<XComponentController>& controller)
{
    return std::static_pointer_cast<InnerXComponentController>(controller);
}
} // namespace

void XComponentControllerNativePeerImpl::TriggerStartImageAnalyzer(Ark_VMContext vmContext,
    Ark_AsyncWorkerPtr asyncWorker, const Ark_ImageAnalyzerConfig* config,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    CHECK_NULL_VOID(config);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(outputArgumentForReturningPromise);
    if (isImageAnalyzing) {
        promise->Reject(PeerUtils::CreateAIError(ImageAnalyzerState::ONGOING));
        return;
    }
    isImageAnalyzing = true;

    auto onAnalyzed = [peer = Claim(this), promise](ImageAnalyzerState state) {
        peer->isImageAnalyzing = false;
        auto error = PeerUtils::CreateAIError(state);
        if (error.empty()) {
            promise->Resolve();
        } else {
            promise->Reject(error);
        }
    };

    promise->StartAsync(vmContext, *asyncWorker,
        [peer = Claim(this), wrapConfigFunc = wrapAnalyzerConfigImpl, onAnalyzed = std::move(onAnalyzed)]() {
            auto controller = GetInnerController(peer->controller);
            if (controller) {
                OnAnalyzedCallback optOnAnalyzed = std::move(onAnalyzed);
                void* config = wrapConfigFunc == nullptr ? nullptr : wrapConfigFunc();
                controller->StartImageAnalyzer(config, optOnAnalyzed);
            } else {
                onAnalyzed(ImageAnalyzerState::STOPPED);
            }
        });
    wrapAnalyzerConfigImpl = nullptr;
}
void XComponentControllerNativePeerImpl::SetOnSurfaceCreatedEvent(const OnSurfaceCreatedCb& callback)
{
    arkOnSurfaceCreated = callback;
    onSurfaceCreatedEvent = [arkCallback = CallbackHelper(callback)](
                                const std::string& surfaceId, const std::string& xcomponentId) {
        auto arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId);
        arkCallback.InvokeSync(arkSurfaceId);
    };
}
void XComponentControllerNativePeerImpl::SetOnSurfaceChangedEvent(const OnSurfaceChangedCb& callback)
{
    arkOnSurfaceChanged = callback;
    onSurfaceChangedEvent = [arkCallback = CallbackHelper(callback)](const std::string& surfaceId, const RectF& rect) {
        auto arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId);
        Ark_SurfaceRect arkSurfaceRect;
        arkSurfaceRect.offsetX = Converter::ArkValue<Opt_Float64>(rect.Left());
        arkSurfaceRect.offsetY = Converter::ArkValue<Opt_Float64>(rect.Top());
        arkSurfaceRect.surfaceWidth = Converter::ArkValue<Ark_Float64>(rect.Width());
        arkSurfaceRect.surfaceHeight = Converter::ArkValue<Ark_Float64>(rect.Height());
        arkCallback.InvokeSync(arkSurfaceId, arkSurfaceRect);
    };
}
void XComponentControllerNativePeerImpl::SetOnSurfaceDestroyedEvent(const OnSurfaceDestroyedCb& callback)
{
    arkOnSurfaceDestroyed = callback;
    onSurfaceDestroyedEvent = [arkCallback = CallbackHelper(callback)](
                                  const std::string& surfaceId, const std::string& xcomponentId) {
        auto arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId);
        arkCallback.InvokeSync(arkSurfaceId);
    };
}
drawing_CanvasPeer* XComponentControllerNativePeerImpl::GetCanvas()
{
    auto innerController = GetInnerController(controller);
    CHECK_NULL_RETURN(innerController, nullptr);
    CHECK_NULL_RETURN(innerController->LockCanvas(), nullptr);
    auto canvas = innerController->LockCanvas();
    if (!rsCanvas_ || rsCanvas_ != reinterpret_cast<drawing_CanvasPeer*>(canvas)) {
        rsCanvas_ = reinterpret_cast<drawing_CanvasPeer*>(canvas);
    }
    return rsCanvas_;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // XCOMPONENT_SUPPORTED
