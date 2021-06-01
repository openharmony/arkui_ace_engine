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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_helpers.h"

#include "base/log/log.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

JSValue JsLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ScopedString printLog(ctx, argv[0]);
    LOGD("ace Log: %s", printLog.get());

    return JS_NULL;
}

JSValue JsDebugLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ScopedString printLog(ctx, argv[0]);
    LOGD("ace Log: %s", printLog.get());

    return JS_NULL;
}

JSValue JsInfoLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ScopedString printLog(ctx, argv[0]);
    LOGI("ace Log: %s", printLog.get());

    return JS_NULL;
}

JSValue JsWarnLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ScopedString printLog(ctx, argv[0]);
    LOGW("ace Log: %s", printLog.get());

    return JS_NULL;
}

JSValue JsErrorLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ScopedString printLog(ctx, argv[0]);
    LOGE("ace Log: %s", printLog.get());

    return JS_NULL;
}

void InitConsole(JSContext* ctx)
{
    JSValue globalObj, console;
    globalObj = JS_GetGlobalObject(ctx);
    console = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, JsLogPrint, "log", 1));
    JS_SetPropertyStr(ctx, console, "debug", JS_NewCFunction(ctx, JsDebugLogPrint, "debug", 1));
    JS_SetPropertyStr(ctx, console, "info", JS_NewCFunction(ctx, JsInfoLogPrint, "info", 1));
    JS_SetPropertyStr(ctx, console, "warn", JS_NewCFunction(ctx, JsWarnLogPrint, "warn", 1));
    JS_SetPropertyStr(ctx, console, "error", JS_NewCFunction(ctx, JsErrorLogPrint, "error", 1));
    JS_SetPropertyStr(ctx, globalObj, "console", console);
}

} // namespace OHOS::Ace::Framework
