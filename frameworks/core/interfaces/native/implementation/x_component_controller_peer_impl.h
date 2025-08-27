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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_X_COMPONENT_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_X_COMPONENT_CONTROLLER_PEER_IMPL_H

#include "base/memory/referenced.h"
#ifdef XCOMPONENT_SUPPORTED
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#endif // XCOMPONENT_SUPPORTED

namespace OHOS::Ace::NG::GeneratedModifier {

struct XComponentControllerPeerImpl : public OHOS::Ace::Referenced {
#ifdef XCOMPONENT_SUPPORTED
    void TriggerStartImageAnalyzer(const Ark_ImageAnalyzerConfig* config,
        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    std::shared_ptr<XComponentControllerNG> controller;
    void SetOnSurfaceCreatedEvent(const Callback_String_Void& callback);
    void SetOnSurfaceChangedEvent(const Callback_String_SurfaceRect_Void& callback);
    void SetOnSurfaceDestroyedEvent(const Callback_String_Void& callback);
    SurfaceCreatedEvent GetOnSurfaceCreatedEvent();
    SurfaceChangedEvent GetOnSurfaceChangedEvent();
    SurfaceDestroyedEvent GetOnSurfaceDestroyedEvent();

private:
    SurfaceCreatedEvent onSurfaceCreatedEvent_ = nullptr;
    SurfaceChangedEvent onSurfaceChangedEvent_ = nullptr;
    SurfaceDestroyedEvent onSurfaceDestroyedEvent_ = nullptr;
    bool isImageAnalyzing_ = false;
    ImageAnalyzerConfig config_;
#endif // XCOMPONENT_SUPPORTED
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_X_COMPONENT_CONTROLLER_PEER_IMPL_H