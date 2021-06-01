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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/grid_layout/grid_layout_component.h"

namespace OHOS::Ace::Framework {

class JSGrid : public JSContainerBase {
    DECLARE_ACE_TYPE(JSGrid, JSContainerBase);

public:
    JSGrid() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSGrid(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSGrid(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSGrid();

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSGrid* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);

    static JSValue JsColumnsTemplate(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
    static JSValue JsColumnsGap(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
    static JSValue JsRowsTemplate(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
    static JSValue JsRowsGap(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
#endif

#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    void SetColumnsTemplate(std::string value);
    void SetRowsTemplate(std::string value);
    void SetColumnsGap(double value);
    void SetRowsGap(double value);

private:
    std::string columnsTemplate_;
    std::string rowsTemplate_;
    double columnsGap_ = 0.0;
    double rowsGap_ = 0.0;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H
