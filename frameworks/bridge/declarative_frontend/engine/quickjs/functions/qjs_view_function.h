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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_VIEW_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_VIEW_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class QJSViewFunction : public QJSFunction {
    DECLARE_ACE_TYPE(QJSViewFunction, QJSFunction)

public:
    QJSViewFunction(JSContext* ctx, JSValue jsObject, JSValue jsFunction);
    ~QJSViewFunction();

    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;
    virtual void Destroy(JSViewAbstract* parentCustomView);

    JSViewAbstract* executeRender();
    void executeAppear();
    void executeDisappear();
    void executeAboutToRender();
    void executeOnRenderDone();

private:
    JSValue jsAppearFunction_ = JS_NULL;
    JSValue jsDisappearFunction_ = JS_NULL;
    JSValue jsRenderFunction_ = JS_NULL;
    JSValue jsAboutToRenderFunc_ = JS_NULL;
    JSValue jsRenderDoneFunc_ = JS_NULL;
    JSValue jsRenderResult_ = JS_NULL;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_RENDER_FUNCTION_H
