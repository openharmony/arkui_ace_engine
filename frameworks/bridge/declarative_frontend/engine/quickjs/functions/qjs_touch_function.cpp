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

JSValue QJSTouchFunction::createTouchInfo(const TouchLocationInfo& touchInfo)
{
    JSValue touchInfoObj = JS_NewObject(ctx_);
    const OHOS::Ace::Offset& globalLocation = touchInfo.GetGlobalLocation();
    const OHOS::Ace::Offset& localLocation = touchInfo.GetLocalLocation();
    JS_SetPropertyStr(ctx_, touchInfoObj, "globalX", JS_NewFloat64(ctx_, globalLocation.GetX()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "globalY", JS_NewFloat64(ctx_, globalLocation.GetY()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "localX", JS_NewFloat64(ctx_, localLocation.GetX()));
    JS_SetPropertyStr(ctx_, touchInfoObj, "localY", JS_NewFloat64(ctx_, localLocation.GetY()));
    return touchInfoObj;
}

JSValue QJSTouchFunction::createJSEventInfo(const TouchEventInfo& info)
{
    JSValue eventObj = JS_NewObject(ctx_);
    JSValue touchArr = JS_NewArray(ctx_);
    JSValue changeTouchArr = JS_NewArray(ctx_);

    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    uint32_t idx = 0;
    for (const TouchLocationInfo& location : touchList) {
        JSValue element = createTouchInfo(location);
        JS_SetPropertyUint32(ctx_, touchArr, idx++, element);
    }
    JS_SetPropertyStr(ctx_, eventObj, "touches", touchArr);

    idx = 0; // reset index counter
    const std::list<TouchLocationInfo>& changeTouch = info.GetChangedTouches();
    for (const TouchLocationInfo& change : changeTouch) {
        JSValue element = createTouchInfo(change);
        JS_SetPropertyUint32(ctx_, changeTouchArr, idx++, element);
    }
    JS_SetPropertyStr(ctx_, eventObj, "changedTouches", changeTouchArr);

    return eventObj;
}

void QJSTouchFunction::execute(const TouchEventInfo& info)
{
    LOGD("QJSTouchFunction: eventType[%s]", info.GetType().c_str());
    JSValue param = createJSEventInfo(info);

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
