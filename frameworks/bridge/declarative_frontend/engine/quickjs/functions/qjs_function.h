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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FUNCTION_H

#include "base/memory/ace_type.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/quickjs.h"
#ifdef __cplusplus
}
#endif

#include "functional"

#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

class QJSFunction : public virtual AceType {
    DECLARE_ACE_TYPE(QJSFunction, AceType);

public:
    QJSFunction(JSContext* ctx, JSValue jsObject, JSValue jsFunction);
    ~QJSFunction();

    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc);
    virtual void ReleaseRT(JSRuntime* rt);

protected:
    virtual JSValue executeJS(int argc = 0, JSValueConst* argv = nullptr) final;

    JSValue jsFunction_;
    JSValue jsThis_;
    JSContext* ctx_;
};

template<class T, int32_t ARGC = 0>
class QJSEventFunction : public QJSFunction {
    DECLARE_ACE_TYPE(QJSEventFunction, QJSFunction);

public:
    using ParseFunc = std::function<JSValue(const T&, JSContext*)>;
    QJSEventFunction() = delete;
    QJSEventFunction(JSContext* ctx, JSValue jsFunction, ParseFunc parser)
        : QJSFunction(ctx, JS_UNDEFINED, jsFunction), parser_(parser) {};
    ~QJSEventFunction() = default;

    void execute()
    {
        JSValue result = QJSFunction::executeJS();
        if (JS_IsException(result)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
        }
        JS_FreeValue(ctx_, result);
    }

    void execute(const T& eventInfo)
    {
        JSValue param = 0;
        if (parser_) {
            param = parser_(eventInfo, ctx_);
        }
        if (JS_IsException(param)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
        }
        JSValue result = QJSFunction::executeJS(ARGC, &param);
        if (JS_IsException(result)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
        }
        JS_FreeValue(ctx_, result);
    }

    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override
    {
        QJSFunction::MarkGC(rt, markFunc);
        JS_MarkValue(rt, jsFunction_, markFunc);
    }
    void ReleaseRT(JSRuntime* rt) override
    {
        QJSFunction::ReleaseRT(rt);
        JS_FreeValueRT(rt, jsFunction_);
    }

private:
    ParseFunc parser_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_FUNCTION_H
