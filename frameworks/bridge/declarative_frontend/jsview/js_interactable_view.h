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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H

#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/pipeline/base/component.h"

#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#elif USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_click_function.h"
#endif

namespace OHOS::Ace::Framework {
class JSInteractableView {
public:
#ifdef USE_QUICKJS_ENGINE
    using ClickFunction = QJSClickFunction;
    using TouchFunction = QJSTouchFunction;
#elif USE_V8_ENGINE
    using ClickFunction = V8ClickFunction;
    using TouchFunction = V8TouchFunction;
#endif

    JSInteractableView() = default;
    ~JSInteractableView();

    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateComponents();

#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc);
    void ReleaseRT(JSRuntime* rt);

    void AttachJSTouchHandler(JSValueConst jsHandler);
#endif
    void SetTouchHandler(JSTouchHandler* handler);
    void SetPanHandler(JSPanHandler* handler);
    void SetClickHandler(RefPtr<ClickFunction>& clickHandler);

#ifdef USE_QUICKJS_ENGINE
    virtual JSValue JsOnTouch(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    virtual JSValue JsOnClick(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
#elif USE_V8_ENGINE
    virtual void JsOnTouch(const v8::FunctionCallbackInfo<v8::Value>& args);
    virtual void JsOnPan(const v8::FunctionCallbackInfo<v8::Value>& args);
    virtual void JsOnClick(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    JSTouchHandler* touchHandler_ = nullptr;
    JSPanHandler* panHandler_ = nullptr;
    RefPtr<ClickFunction> onClickFunc_;
    RefPtr<TouchFunction> jsOnTouchFunc_;

#ifdef USE_QUICKJS_ENGINE
    JSValue jsHandler_ = JS_NULL;
#endif
}; // class JSInteractableView
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H
