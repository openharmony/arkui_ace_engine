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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"

#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

QJSFunction::QJSFunction(JSContext* ctx, JSValue jsObject, JSValue jsFunction)
{
    // Do not duplicate values here.
    // jsObject determines the lifecycle of this object.
    // jsFunction can be:  (1) property of jsObject
    //                     (2) argument to a different function
    // case 1: duplicating jsFunction value will prevent GC on its owner jsObject.
    // case 2: Duplicate this value, at the position where the argument was passed (onClick() for example)
    ctx_ = ctx;
    jsThis_ = jsObject;
    jsFunction_ = jsFunction;
}

QJSFunction::~QJSFunction()
{
    ctx_ = nullptr;
}

JSValue QJSFunction::executeJS(int argc, JSValueConst* argv)
{
    ACE_DCHECK(JS_IsFunction(ctx_, jsFunction_) && "jsFunction is not a JS Function");

    ACE_FUNCTION_TRACE();

    const char* jsFunctionStr = JS_ToCString(ctx_, jsFunction_);
    LOGD("JS_CALL: %s", jsFunctionStr);
    JS_FreeCString(ctx_, jsFunctionStr);

    // The function might delete itself or the object in a callback. Safe to duplicate before execution
    JSValue jsTmpFunc = JS_DupValue(ctx_, jsFunction_);
    JSValue jsTmpThis = JS_DupValue(ctx_, jsThis_);

    JSValue result = JS_Call(ctx_, jsTmpFunc, jsTmpThis, argc, argv);

    JS_FreeValue(ctx_, jsTmpFunc);
    JS_FreeValue(ctx_, jsTmpThis);

    if (JS_IsException(result)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
        JS_FreeValue(ctx_, result);
        return JS_NULL;
    }

    return result;
}

void QJSFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) {}

void QJSFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSFunction(release): start");
    ctx_ = nullptr;
    LOGD("QJSFunction(release): end");
}

} // namespace OHOS::Ace::Framework
