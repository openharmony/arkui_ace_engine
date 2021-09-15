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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_foreach_function.h"

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

namespace OHOS::Ace::Framework {

std::vector<std::string> QJSForEachFunction::executeIdentityMapper()
{
    std::vector<std::string> result;

    JSValue jsKeys = JS_NULL;
    if (!JS_IsNull(jsIdentityMapperFunc_)) {
        jsKeys = QJSFunction::executeJS(1, &jsIdentityMapperFunc_);

        if (JS_IsException(jsKeys)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
            JS_FreeValue(ctx_, jsKeys);
            return result;
        }
    }

    int length = 0;
    JSValue jsLength;
    if (!JS_IsNull(jsKeys)) {
        jsLength = JS_GetPropertyStr(ctx_, jsKeys, "length");
    } else {
        jsLength = JS_GetPropertyStr(ctx_, jsThis_, "length");
    }
    JS_ToInt32(ctx_, &length, jsLength);
    JS_FreeValue(ctx_, jsLength);

    for (int i = 0; i < length; i++) {
        if (!JS_IsNull(jsKeys)) {
            // this is safe because both results are from the same array
            JSValue jsKey = JS_GetPropertyUint32(ctx_, jsKeys, i);

            if (!JS_IsString(jsKey) && !JS_IsNumber(jsKey)) {
                LOGE("ForEach Item with invalid identifier.........");
                JS_FreeValue(ctx_, jsKey);
                continue;
            }

            std::string key(JS_ToCString(ctx_, jsKey));
            LOGD("ForEach item with identifier: %s", key.c_str());

            JS_FreeValue(ctx_, jsKey);
            result.emplace_back(key);
        } else {
            result.emplace_back(std::to_string(i));
        }
    }

    if (!JS_IsNull(jsKeys)) {
        JS_FreeValue(ctx_, jsKeys);
    }

    return result;
}

void QJSForEachFunction::executeBuilderForIndex(int32_t index)
{
    // indexed item
    JSValue jsItem = JS_GetPropertyUint32(ctx_, jsThis_, index);
    JSValue jsView = JS_Call(ctx_, jsViewMapperFunc_, jsThis_, 1, &jsItem);
    JS_FreeValue(ctx_, jsItem);
    if (JS_IsException(jsView)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
        JS_FreeValue(ctx_, jsView);
    }
}

void QJSForEachFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSForEachFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    JS_MarkValue(rt, QJSFunction::jsThis_, markFunc);
    JS_MarkValue(rt, QJSFunction::jsFunction_, markFunc);
    JS_MarkValue(rt, jsIdentityMapperFunc_, markFunc);
    JS_MarkValue(rt, jsViewMapperFunc_, markFunc);
    LOGD("QJSForEachFunction(MarkGC): end");
}

void QJSForEachFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSForEachFunction(release): start");
    QJSFunction::ReleaseRT(rt);
    JS_FreeValueRT(rt, QJSFunction::jsThis_);
    JS_FreeValueRT(rt, QJSFunction::jsFunction_);
    JS_FreeValueRT(rt, jsIdentityMapperFunc_);
    JS_FreeValueRT(rt, jsViewMapperFunc_);
    LOGD("QJSForEachFunction(release): end");
}

} // namespace OHOS::Ace::Framework
