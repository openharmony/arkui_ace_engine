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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_H

#include <list>

#include "core/pipeline/base/composed_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_customview_base.h"

#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_view_function.h"
#endif

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_view_function.h"
#endif

namespace OHOS::Ace {

class ComposedElement;

}
namespace OHOS::Ace::Framework {

class JSView : public JSCustomViewBase {
    DECLARE_ACE_TYPE(JSView, JSCustomViewBase);

public:
#ifdef USE_QUICKJS_ENGINE
    JSView(JSContext* ctx, JSValue jsObject, JSValue jsRenderFunction);
#endif
#ifdef USE_V8_ENGINE
    JSView(v8::Local<v8::Object> jsObject, v8::Local<v8::Function> jsRenderFunction);
#endif
    ~JSView();

    RefPtr<OHOS::Ace::Component> internalRender();
    virtual void MarkNeedUpdate() override;
    virtual bool NeedsUpdate() override
    {
        return needsUpdate_;
    }

    OHOS::Ace::ComposedElement* getElement()
    {
        return element_;
    }

    virtual void Destroy(JSViewAbstract* parentCustomView) override;

    static void JSBind(BindingTarget globalObj);
#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSView* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif
protected:
    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
#ifdef USE_QUICKJS_ENGINE
    RefPtr<QJSViewFunction> jsViewFunction_;
#endif
#ifdef USE_V8_ENGINE
    RefPtr<V8ViewFunction> jsViewFunction_;
#endif
    OHOS::Ace::ComposedElement* element_ = nullptr;
    bool needsUpdate_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_H
