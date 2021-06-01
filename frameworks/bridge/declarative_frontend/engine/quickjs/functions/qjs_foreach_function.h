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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FOREACH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FOREACH_FUNCTION_H

#include <map>

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class QJSForEachFunction : public QJSFunction {
    DECLARE_ACE_TYPE(QJSForEachFunction, QJSFunction)

private:
    JSValue jsIdentityMapperFunc_ = JS_NULL;
    JSValue jsViewMapperFunc_ = JS_NULL;
    JSValue jsResult_ = JS_NULL;

public:
    QJSForEachFunction(JSContext* ctx, JSValue jsArray, JSValue jsIdentityMapperFunc, JSValue jsViewMapperFunc)
        : QJSFunction(ctx, JS_UNDEFINED, JS_UNDEFINED)
    {
        QJSFunction::jsThis_ = JS_DupValue(ctx, jsArray);
        QJSFunction::jsFunction_ = JS_GetPropertyStr(ctx, jsArray, "map"); // intrinsic property of array
        if (!JS_IsNull(jsIdentityMapperFunc)) {
            jsIdentityMapperFunc_ = JS_DupValue(ctx, jsIdentityMapperFunc);
        }
        jsViewMapperFunc_ = JS_DupValue(ctx, jsViewMapperFunc);
    }

    ~QJSForEachFunction()
    {
        LOGD("Destroy: QJSForEachFunction");
    }

    // ForEach Syntax
    //  ForEach(
    //    [item],             // proxied array of data items
    //    (item => String),   // IdentifierFunction: provide unique id for given data item
    //    (item => View)      // BuilderFunction: provide View for given data item
    //  )
    //  This exexutes the IdentifierFunction
    std::vector<std::tuple<std::string, JSViewAbstract*>> execute();

    // This exexutes the IdentifierFunction on all items  in a array
    // returns the vector of keys/ids in the same order.
    std::vector<std::string> executeIdentityMapper();

    // This exexutes the BuilderFunction on a specific index
    // returns the native JsView for the item in index.
    std::vector<JSViewAbstract*> executeBuilderForIndex(int32_t index);

    // Post task to the UI thread.
    // In ace_diff UI and js runs on the same thread
    void PostTask(std::function<void()>&& task);

    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    virtual void Destroy(JSViewAbstract* parentCustomView);

}; // QJSForEachFunction

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FOREACH_FUNCTION_H
