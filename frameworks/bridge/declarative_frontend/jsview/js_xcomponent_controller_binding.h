/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_CONTROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_CONTROLLER_BINDING_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::Framework {
class JSXComponentControllerBinding final : public JSXComponentController {
public:
    JSXComponentControllerBinding() = default;
    ~JSXComponentControllerBinding() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);

    void GetSurfaceId(const JSCallbackInfo& args);
    void SetSurfaceConfig(const JSCallbackInfo& args);

    void GetXComponentContext(const JSCallbackInfo& args)
    {
        args.SetReturnValue(renderContext_.Lock());
    }

    void SetXComponentContext(const JSRef<JSVal>& renderContext)
    {
        renderContext_ = renderContext;
    }

    void GetXComponentSurfaceRect(const JSCallbackInfo& args);
    void SetXComponentSurfaceRect(const JSCallbackInfo& args);

    void StartImageAnalyzer(const JSCallbackInfo& args);
    void StopImageAnalyzer(const JSCallbackInfo& args);

    void SetXComponentSurfaceRotation(const JSCallbackInfo& args);
    void GetXComponentSurfaceRotation(const JSCallbackInfo& args);

    void LockCanvas(const JSCallbackInfo& args);
    void UnlockCanvasAndPost(const JSCallbackInfo& args);

    void SetXComponentSurfaceConfig(const JSCallbackInfo& args);

private:
    JSWeak<JSVal> renderContext_;
    bool isImageAnalyzing_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(JSXComponentControllerBinding);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_CONTROLLER_BINDING_H
