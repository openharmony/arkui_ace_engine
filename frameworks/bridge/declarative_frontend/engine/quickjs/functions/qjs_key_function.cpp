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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_key_function.h"

#include "base/log/log.h"
#include "core/gestures/raw_recognizer.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

JSValue QJSKeyFunction::createKeyEvent(const OHOS::Ace::KeyEventInfo& info)
{
    JSValue keyEventObj = JS_NewObject(ctx_);
    JS_SetPropertyStr(ctx_, keyEventObj, "type", JS_NewInt32(ctx_, static_cast<int32_t>(info.GetKeyType())));
    JS_SetPropertyStr(ctx_, keyEventObj, "keyCode", JS_NewInt32(ctx_, static_cast<int32_t>(info.GetKeyCode())));
    JS_SetPropertyStr(ctx_, keyEventObj, "keyText", JS_NewString(ctx_, info.GetKeyText()));
    JS_SetPropertyStr(ctx_, keyEventObj, "keySource", JS_NewInt32(ctx_, info.GetKeySource()));
    JS_SetPropertyStr(ctx_, keyEventObj, "deviceId", JS_NewInt32(ctx_, info.GetDeviceId()));
    JS_SetPropertyStr(ctx_, keyEventObj, "metaKey", JS_NewInt32(ctx_, info.GetMetaKey()));
    JS_SetPropertyStr(ctx_, keyEventObj, "timestamp",
        JS_NewFloat64(ctx_, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
    return keyEventObj;
}

void QJSKeyFunction::execute(const OHOS::Ace::KeyEventInfo& info)
{
    LOGD("QJSKeyFunction: eventType[%s]", info.GetType().c_str());
    JSValue param = createKeyEvent(info);
    if (JS_IsException(param)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
    }
    JSValue result = QJSFunction::executeJS(1, &param);
    if (JS_IsException(result)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
    }
    JS_FreeValue(ctx_, result);
}

void QJSKeyFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSKeyFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    JS_MarkValue(rt, jsFunction_, markFunc);
    LOGD("QJSKeyFunction(MarkGC): end");
}

void QJSKeyFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSKeyFunction(release): start");
    QJSFunction::ReleaseRT(rt);
    JS_FreeValueRT(rt, jsFunction_);
    LOGD("QJSKeyFunction(release): end");
}

} // namespace OHOS::Ace::Framework
