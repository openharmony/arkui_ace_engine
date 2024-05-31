/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PARTICLE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PARTICLE_H

#include "core/components_ng/pattern/particle/particle_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
class JSParticle : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void JsDisturbanceFields(const JSCallbackInfo& args);
    static void AddDisturbance(std::vector<ParticleDisturbance>& dataArray, const JSRef<JSObject>& paramObj);
    static void GetSizeAndPositionValues(const JSRef<JSObject>& paramObj, int& sizeXValue, int& sizeYValue,
        int& positionXValue, int& positionYValue);
    static void JsEmitter(const JSCallbackInfo& args);
    static void ParseEmitterProperty(
        std::vector<EmitterProperty>& dataArray, const JSRef<JSObject>& paramObj);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PARTICLE_H
