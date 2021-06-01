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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H

#include <variant>

#include "core/components/button/button_component.h"
#include "core/components/touch_listener/touch_listener_component.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_click_function.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/quickjs.h"
#ifdef __cplusplus
}
#endif
#endif

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_click_function.h"
#endif

namespace OHOS::Ace::Framework {

class JSButton : public JSViewAbstract, public JSInteractableView {
    DECLARE_ACE_TYPE(JSButton, JSViewAbstract);

public:
#ifdef USE_QUICKJS_ENGINE
    using ClickFunction = QJSClickFunction;
#elif USE_V8_ENGINE
    using ClickFunction = V8ClickFunction;
#endif

    JSButton() = delete;
    JSButton(const std::string text)
        : text_(text), child_(nullptr), buttonType_(static_cast<int32_t>(ButtonType::CAPSULE))
    {}
    JSButton(JSViewAbstract* child) : child_(child), buttonType_(static_cast<int32_t>(ButtonType::CAPSULE)) {}
    ~JSButton()
    {
        LOGD("Destroy: JSButton");
    }

    void SetFontSize(double value);
    void SetFontWeight(std::string value);
    void SetTextColor(std::string value);
    void SetType(int value);

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    virtual std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    RefPtr<OHOS::Ace::Component> CreateTouchComponent(const RefPtr<OHOS::Ace::Component>& wrapped);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;
    virtual JSValue JsOnClick(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv) override;
#endif
#ifdef USE_V8_ENGINE
    void JsOnClick(const v8::FunctionCallbackInfo<v8::Value>& args) override;
#endif

public:
#ifdef USE_QUICKJS_ENGINE
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSButton* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif
#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
    static void JSBind(BindingTarget globalObj);

private:
    std::string text_;
    JSViewAbstract* child_ = nullptr;
    TextStyle textStyle_;
    int32_t buttonType_;
    RefPtr<ClickFunction> onClickFunc_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H
