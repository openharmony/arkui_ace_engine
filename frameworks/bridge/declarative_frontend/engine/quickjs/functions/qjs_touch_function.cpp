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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_touch_function.h"

#include "base/log/log.h"
#include "core/gestures/raw_recognizer.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

JSValue QJSTouchFunction::createTouchInfo(const TouchCallBackInfo& touchInfo)
{
    JSValue touchInfoObj = JS_NewObject(ctx_);
    JS_SetPropertyStr(ctx_, touchInfoObj, "type", JS_NewFloat64(ctx_, static_cast<int32_t>(touchInfo.GetTouchType())));
    JS_SetPropertyStr(ctx_, touchInfoObj, "screenX", JS_NewFloat64(ctx_, touchInfo.GetScreenX()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "screenY", JS_NewFloat64(ctx_, touchInfo.GetScreenY()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "x", JS_NewFloat64(ctx_, touchInfo.GetLocalX()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "y", JS_NewFloat64(ctx_, touchInfo.GetLocalY()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "timestamp",
        JS_NewFloat64(ctx_, static_cast<double>(touchInfo.GetTimeStamp().time_since_epoch().count())));
    return touchInfoObj;
}

void QJSTouchFunction::execute(const TouchCallBackInfo& info)
{
    LOGD("QJSTouchFunction: eventType[%s]", info.GetType().c_str());
    JSValue param = createTouchInfo(info);

    if (JS_IsException(param)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
    }

    JSValue result = QJSFunction::executeJS(1, &param);

    if (JS_IsException(result)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
    }

    JS_FreeValue(ctx_, result);
}

void QJSTouchFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSTouchFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    JS_MarkValue(rt, jsFunction_, markFunc);
    LOGD("QJSTouchFunction(MarkGC): end");
}

void QJSTouchFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSTouchFunction(release): start");
    QJSFunction::ReleaseRT(rt);
    JS_FreeValueRT(rt, jsFunction_);
    LOGD("QJSTouchFunction(release): end");
}

} // namespace OHOS::Ace::Framework
