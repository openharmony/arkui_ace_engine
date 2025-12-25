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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERING_CONTEXT2D_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERING_CONTEXT2D_PEER_IMPL_H

#include "canvas_renderer_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
using ReadyEvent = std::function<void()>;

class CanvasRenderingContext2DPeerImpl : public CanvasRendererPeerImpl {
public:
    enum class CanvasCallbackType {
        ON_ATTACH = 0,
        ON_DETACH,
        UNKNOWN
    };
    using CanvasCallbackList = std::list<std::pair<int32_t, std::function<void()>>>;
    using CanvasCallbackIterator = CanvasCallbackList::const_iterator;
    CanvasRenderingContext2DPeerImpl();
    ~CanvasRenderingContext2DPeerImpl() override = default;

    void SetOptions(const std::optional<RenderingContextSettingsPeer*>& optSettings);
    void OnAttachToCanvas();
    void OnDetachFromCanvas();
    void StartImageAnalyzer(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Ark_ImageAnalyzerConfig* config, const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    void StopImageAnalyzer();
    double GetHeight();
    double GetWidth();
    void On(std::function<void()> &&callback, const CanvasCallbackType& type);
    void Off(std::function<void()> &&callback, const CanvasCallbackType& type);
    int32_t GetCanvasId();
    void SetRenderingContextOptions(const RenderingContextOptions& options);
    void SetAttachCallbackId(int32_t attachCallbackId)
    {
        attachCallbackId_ = attachCallbackId;
    }
    void SetDetachCallbackId(int32_t detachCallbackId)
    {
        detachCallbackId_ = detachCallbackId;
    }
    void SetBuiltIn(bool builtIn)
    {
        builtIn_ = builtIn;
    }
    bool IsBuiltIn() const
    {
        return builtIn_;
    }

private:
    CanvasCallbackList::const_iterator FindCallbackInList(
        const CanvasCallbackList& callbackFuncPairList, int32_t callbackId) const;
    void DeleteCallbackFromList(const std::function<void()>& callback, const CanvasCallbackType& type);
    void AddCallbackToList(std::function<void()> &&callback, const CanvasCallbackType& type);

    bool isImageAnalyzing_ = false;
    int32_t attachCallbackId_ = -1;
    int32_t detachCallbackId_ = -1;
    ImageAnalyzerConfig config_;
    CanvasCallbackList attachCallback_;
    CanvasCallbackList detachCallback_;
    bool builtIn_ = false;
};

} // namespace OHOS::Ace::NG::GeneratedModifier

struct CanvasRenderingContext2DPeer : public OHOS::Ace::NG::GeneratedModifier::CanvasRenderingContext2DPeerImpl {
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
