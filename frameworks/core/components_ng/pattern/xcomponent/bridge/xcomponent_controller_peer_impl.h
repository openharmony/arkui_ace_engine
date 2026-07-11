/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_X_COMPONENT_CONTROLLER_PEER_IMPL_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_X_COMPONENT_CONTROLLER_PEER_IMPL_H

#include <functional>
#include <memory>
#include <string>

#include "interfaces/inner_api/xcomponent_controller/xcomponent_controller.h"

#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"

#ifdef XCOMPONENT_SUPPORTED
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif // XCOMPONENT_SUPPORTED

struct drawing_CanvasPeer;
namespace OHOS::Ace::NG::GeneratedModifier {
using SurfaceCreatedEvent = std::function<void(const std::string&, const std::string&)>;
using SurfaceChangedEvent = std::function<void(const std::string&, const RectF&)>;
using SurfaceDestroyedEvent = std::function<void(const std::string&, const std::string&)>;
struct XComponentControllerNativePeerImpl : public Referenced {
    std::shared_ptr<OHOS::Ace::XComponentController> controller;
#ifdef XCOMPONENT_SUPPORTED
    void TriggerStartImageAnalyzer(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Ark_ImageAnalyzerConfig* config, const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    void SetOnSurfaceCreatedEvent(const OnSurfaceCreatedCb& callback);
    void SetOnSurfaceChangedEvent(const OnSurfaceChangedCb& callback);
    void SetOnSurfaceDestroyedEvent(const OnSurfaceDestroyedCb& callback);
    drawing_CanvasPeer* GetCanvas();
    OnSurfaceCreatedCb arkOnSurfaceCreated = {};
    OnSurfaceChangedCb arkOnSurfaceChanged = {};
    OnSurfaceDestroyedCb arkOnSurfaceDestroyed = {};
    SurfaceCreatedEvent onSurfaceCreatedEvent = nullptr;
    SurfaceChangedEvent onSurfaceChangedEvent = nullptr;
    SurfaceDestroyedEvent onSurfaceDestroyedEvent = nullptr;
    bool isImageAnalyzing = false;
    ImageAnalyzerConfig analyzerConfig;
    std::function<void*()> wrapAnalyzerConfigImpl = nullptr;
    drawing_CanvasPeer* rsCanvas_ = nullptr;
#endif // XCOMPONENT_SUPPORTED
};

} // namespace OHOS::Ace::NG::GeneratedModifier

struct XComponentControllerNativePeer : public OHOS::Ace::NG::GeneratedModifier::XComponentControllerNativePeerImpl {};

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_X_COMPONENT_CONTROLLER_PEER_IMPL_H