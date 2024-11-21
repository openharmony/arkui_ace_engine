/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_RENDERING_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_RENDERING_CONTEXT_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context_settings.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
enum class CanvasCallbackType {
    ON_ATTACH = 0,
    ON_DETACH,
    UNKNOWN
};

using CanvasCallbackFuncPairList = std::list<std::pair<napi_ref, std::function<void()>>>;

class JSRenderingContext : public JSCanvasRenderer {
public:
    JSRenderingContext();
    ~JSRenderingContext() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSRenderingContext* controller);

    void OnAttachToCanvas();
    void OnDetachFromCanvas();

    void JsToDataUrl(const JSCallbackInfo& info);
    void JsGetWidth(const JSCallbackInfo& info);
    void JsGetHeight(const JSCallbackInfo& info);
    void JsSetHeight(const JSCallbackInfo& info);
    void JsSetWidth(const JSCallbackInfo& info);
    void JsTransferFromImageBitmap(const JSCallbackInfo& info);
    void JsStartImageAnalyzer(const JSCallbackInfo& info);
    void JsStopImageAnalyzer(const JSCallbackInfo& info);
    void JsGetCanvas(const JSCallbackInfo& info);
    void JsSetCanvas(const JSCallbackInfo& info);
    void JsOn(const JSCallbackInfo& info);
    void JsOff(const JSCallbackInfo& info);

    ACE_DISALLOW_COPY_AND_MOVE(JSRenderingContext);

private:
    void DeleteCallbackFromList(int argc, napi_env env, napi_value cb, CanvasCallbackType type);
    void AddCallbackToList(napi_env env, napi_value cb, CanvasCallbackType type, const std::function<void()>&& onFunc);
    CanvasCallbackFuncPairList::const_iterator FindCbList(
        napi_env env, napi_value cb, CanvasCallbackFuncPairList& callbackFuncPairList);
    CanvasCallbackType GetCanvasCallbackType(const std::string& strType);

    bool isImageAnalyzing_ = false;
    CanvasCallbackFuncPairList attachCallback_;
    CanvasCallbackFuncPairList detachCallback_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_RENDERING_CONTEXT_H
