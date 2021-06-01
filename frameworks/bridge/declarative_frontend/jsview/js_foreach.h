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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FOREACH_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FOREACH_H

#include <list>

#include "core/pipeline/base/composed_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_foreach_function.h"
#endif
#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_foreach_function.h"
#endif

namespace OHOS::Ace {
class ComposedElement;
}
namespace OHOS::Ace::Framework {

class JSCustomViewBase;

class JSForEach : public JSViewAbstract {
    DECLARE_ACE_TYPE(JSForEach, JSViewAbstract);

public:
#ifdef USE_QUICKJS_ENGINE
    JSForEach(QJSForEachFunction* jsForEachFunction);
#else
    JSForEach(V8ForEachFunction* jsForEachFunction);
#endif
    ~JSForEach();

    /**
     * marks the JSView's composed component as needing update / rerender
     */
    void MarkNeedUpdate() override;
    virtual void Destroy(JSViewAbstract* parentCustomView) override;
    virtual bool IsForEachView() override
    {
        return true;
    }

    void SetParentCustomView(JSCustomViewBase* view)
    {
        parentCustomView_ = view;
    }

    void SetTranspilerGeneratedViewId(std::string viewId)
    {
        transpilerGeneratedViewId_ = viewId;
    }

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSForEach* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
#endif

protected:
    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;

private:
#ifdef USE_QUICKJS_ENGINE
    QJSForEachFunction* jsForEachFunction_;
#elif USE_V8_ENGINE
    V8ForEachFunction* jsForEachFunction_;
#endif
    JSCustomViewBase* parentCustomView_ = nullptr;
    // element_ for the first item in foreach.
    // It is set to null, once the parentElement_ is updated.
    OHOS::Ace::Element* element_ = nullptr;
    OHOS::Ace::Element* parentElement_ = nullptr;
    // Number of items in a foreach
    // will be updated on markNeedUpdate with new count
    int32_t itemsCount_ = 0;
    // key/id of the first item in a foreach
    // will be updated on markNeedUpdate
    std::string firstItemKey_;
    std::string transpilerGeneratedViewId_;
    bool needsUpdate_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FOREACH_H
