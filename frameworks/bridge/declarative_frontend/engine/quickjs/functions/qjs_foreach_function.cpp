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

std::vector<std::tuple<std::string, JSViewAbstract*>> QJSForEachFunction::execute()
{
    std::vector<std::tuple<std::string, JSViewAbstract*>> result;

    JSValue jsKeys = JS_NULL;
    if (!JS_IsNull(jsIdentityMapperFunc_)) {
        jsKeys = QJSFunction::executeJS(1, &jsIdentityMapperFunc_);

        if (JS_IsException(jsKeys)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
            JS_FreeValue(ctx_, jsKeys);
            return result;
        }
    }

    JSValue jsViews = QJSFunction::executeJS(1, &jsViewMapperFunc_);

    if (JS_IsException(jsViews)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
        JS_FreeValue(ctx_, jsViews);
        return result;
    }

    int length = 0;
    JSValue jsLength = JS_GetPropertyStr(ctx_, jsViews, "length");
    JS_ToInt32(ctx_, &length, jsLength);
    JS_FreeValue(ctx_, jsLength);

    for (int i = 0; i < length; i++) {
        // this is safe because both results are from the same array
        JSValue jsView = JS_GetPropertyUint32(ctx_, jsViews, i);

        JSValue jsKey = JS_NULL;
        if (!JS_IsNull(jsKeys)) {
            jsKey = JS_GetPropertyUint32(ctx_, jsKeys, i);
            if (!JS_IsString(jsKey) && !JS_IsNumber(jsKey)) {
                LOGE("ForEach Item with invalid identifier.........");
                JS_FreeValue(ctx_, jsKey);
                continue;
            }
        }

        std::string key(JS_IsNull(jsKeys) ? std::to_string(i) : JS_ToCString(ctx_, jsKey));
        LOGD("ForEach item with identifier: %s", key.c_str());

        if (JS_IsArray(ctx_, jsView)) {
            int arrLength = 0;
            JSValue jsArrLength = JS_GetPropertyStr(ctx_, jsView, "length");
            JS_ToInt32(ctx_, &arrLength, jsArrLength);
            JS_FreeValue(ctx_, jsArrLength);
            for (int j = 0; j < arrLength; j++) {
                JSValue jsArritem = JS_GetPropertyUint32(ctx_, jsView, i);
                JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsArritem));
                JS_FreeValue(ctx_, jsArritem);
                result.emplace_back(std::make_tuple(key + "_" + std::to_string(j), view));
            }
        } else {
            JSViewAbstract* value = static_cast<JSViewAbstract*>(UnwrapAny(jsView));
            result.emplace_back(std::make_tuple(key, value));
        }
        if (!JS_IsNull(jsKey)) {
            JS_FreeValue(ctx_, jsKey);
        }
        JS_FreeValue(ctx_, jsView);
    }
    if (!JS_IsNull(jsKeys)) {
        JS_FreeValue(ctx_, jsKeys);
    }
    jsResult_ = jsViews;

    return result;
}

std::vector<std::string> QJSForEachFunction::executeIdentityMapper()
{
    std::vector<std::string> result;

    JSValue jsKeys = JS_NULL;
    if (!JS_IsNull(jsIdentityMapperFunc_)) {
        JSValue jsKeys = QJSFunction::executeJS(1, &jsIdentityMapperFunc_);

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

std::vector<JSViewAbstract*> QJSForEachFunction::executeBuilderForIndex(int32_t index)
{
    // indexed item
    JSValue jsItem = JS_GetPropertyUint32(ctx_, jsThis_, index);
    JSValue jsView = JS_Call(ctx_, jsViewMapperFunc_, jsThis_, 1, &jsItem);
    JS_FreeValue(ctx_, jsItem);
    if (JS_IsException(jsView)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
        JS_FreeValue(ctx_, jsView);
        return {};
    }

    std::vector<JSViewAbstract*> result;
    if (JS_IsArray(ctx_, jsView)) {
        int length = 0;
        JSValue jsLength = JS_GetPropertyStr(ctx_, jsView, "length");
        JS_ToInt32(ctx_, &length, jsLength);
        JS_FreeValue(ctx_, jsLength);
        for (int i = 0; i < length; i++) {
            JSValue jsArritem = JS_GetPropertyUint32(ctx_, jsView, i);
            JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsArritem));
            JS_FreeValue(ctx_, jsArritem);
            result.emplace_back(view);
        }
    } else {
        JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsView));
        result.emplace_back(view);
    }

    if (JS_IsNull(jsResult_)) {
        jsResult_ = JS_NewArray(ctx_);
    }

    if (JS_IsArray(ctx_, jsResult_)) {
        JSValue jsPushFunc_ = JS_GetPropertyStr(ctx_, jsResult_, "push");
        JSValue jsPushResult = JS_Call(ctx_, jsPushFunc_, jsResult_, 1, &jsView);
        // JS_Call internally dups the argument
        // hence JS_FreeValue is added here.
        // without this the destruction of the newly add view fail
        JS_FreeValue(ctx_, jsView);

        if (JS_IsException(jsPushResult)) {
            QjsUtils::JsStdDumpErrorAce(ctx_);
            JS_FreeValue(ctx_, jsPushResult);
            return {};
        }
    }
    return result;
}

void QJSForEachFunction::PostTask(std::function<void()>&& task)
{
    // though its named PostJsTask, in acediff ui and js thread are the same
    // FIXME: During cleanup of the ace-diff
    QJSDeclarativeEngineInstance::PostJsTask(ctx_, std::move(task));
}

void QJSForEachFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSForEachFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    if (!JS_IsNull(jsResult_)) {
        JS_MarkValue(rt, jsResult_, markFunc);
    }
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
    if (!JS_IsNull(jsResult_)) {
        JS_FreeValueRT(rt, jsResult_);
    }
    JS_FreeValueRT(rt, QJSFunction::jsThis_);
    JS_FreeValueRT(rt, QJSFunction::jsFunction_);
    JS_FreeValueRT(rt, jsIdentityMapperFunc_);
    JS_FreeValueRT(rt, jsViewMapperFunc_);
    LOGD("QJSForEachFunction(release): end");
}

void QJSForEachFunction::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("QJSForEachFunction::Destroy start");
    if (!JS_IsNull(jsResult_)) {
        int length = 0;
        JSValue jsLength = JS_GetPropertyStr(ctx_, jsResult_, "length");
        JS_ToInt32(ctx_, &length, jsLength);
        JS_FreeValue(ctx_, jsLength);

        for (int i = 0; i < length; i++) {
            // this is safe because both results are from the same array
            JSValue jsView = JS_GetPropertyUint32(ctx_, jsResult_, i);
            if (JS_IsArray(ctx_, jsView)) {
                int arrLength = 0;
                JSValue jsArrLength = JS_GetPropertyStr(ctx_, jsView, "length");
                JS_ToInt32(ctx_, &arrLength, jsArrLength);
                JS_FreeValue(ctx_, jsArrLength);
                for (int i = 0; i < arrLength; i++) {
                    JSValue jsArritem = JS_GetPropertyUint32(ctx_, jsView, i);
                    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsArritem));
                    JS_FreeValue(ctx_, jsArritem);
                    if (view && !view->IsCustomView()) {
                        view->Destroy(parentCustomView);
                    }
                }
            } else if (JS_IsObject(jsView)) {
                JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsView));
                if (view && !view->IsCustomView()) {
                    view->Destroy(parentCustomView);
                }
            }
        }
        JS_FreeValue(ctx_, jsResult_);
        jsResult_ = JS_NULL;
    }
    LOGD("QJSForEachFunction::Destroy end");
}

} // namespace OHOS::Ace::Framework
