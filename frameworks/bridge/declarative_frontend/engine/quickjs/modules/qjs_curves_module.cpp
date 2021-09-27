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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_curves_module.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

int32_t GetJsInt32Val(JSContext* ctx, JSValueConst value)
{
    int32_t val = 0;
    if (JS_IsNumber(value) && (JS_ToInt32(ctx, &val, value)) < 0) {
        val = 0;
    }
    return val;
}

double GetJsDoubleVal(JSContext* ctx, JSValueConst value)
{
    // use ScopedString to parse double
    ScopedString scopedVal(ctx, value);
    auto jsonVal = JsonUtil::ParseJsonData(scopedVal.get());
    if (jsonVal && jsonVal->IsNumber()) {
        return jsonVal->GetDouble();
    }
    return 0.0;
}

std::string GetJsStringVal(JSContext* ctx, JSValueConst value)
{
    std::string val;
    if (JS_IsString(value)) {
        ScopedString curveJsonStr(ctx, value);
        val = curveJsonStr.get();
    }
    return val;
}

JSValue CurvesInterpolate(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    QJSHandleScope handleScope(ctx);
    int32_t pageId = GetJsInt32Val(ctx, QJSUtils::GetPropertyStr(ctx, value, "__pageId"));
    std::string curveString = GetJsStringVal(ctx, QJSUtils::GetPropertyStr(ctx, value, "__curveString"));
    double time = GetJsDoubleVal(ctx, argv[0]);
    auto instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return JS_NULL;
    }
    auto delegate = instance->GetDelegate();
    if (delegate == nullptr) {
        LOGE("delegate is null.");
        return JS_NULL;
    }
    auto page = delegate->GetPage(pageId);
    if (page == nullptr) {
        LOGE("page is null.");
        return JS_NULL;
    }
    auto animationCurve = page->GetCurve(curveString);
    if (!animationCurve) {
        LOGE("animationCurve is null.");
        return JS_NULL;
    }
    double curveValue = animationCurve->Move(time);
    JSValue curveNum = JS_NewFloat64(ctx, curveValue);
    return curveNum;
}

JSValue CurvesInit(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    JS_SetPropertyStr(ctx, value, CURVE_INTERPOLATE, JS_NewCFunction(ctx, CurvesInterpolate, CURVE_INTERPOLATE, 1));
    if ((!argv) || ((argc != 1) && (argc != 0))) {
        LOGE("CurvesInit args count is invalid");
        return JS_NULL;
    }
    RefPtr<Curve> curve;
    std::string curveString;
    if (argc == 1) {
        ScopedString curveJsonStr(ctx, argv[0]);
        curveString = curveJsonStr.get();
    } else {
        curveString = "linear";
    }
    curve = CreateCurve(curveString);
    auto* instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return JS_NULL;
    }
    auto page = instance->GetRunningPage(ctx);
    if (page == nullptr) {
        LOGE("page is nullptr");
        return JS_NULL;
    }
    page->AddCurve(curveString, curve);
    int32_t pageId = page->GetPageId();
    JS_SetPropertyStr(ctx, value, "__pageId", JS_NewInt32(ctx, pageId));
    JS_SetPropertyStr(ctx, value, "__curveString", JS_NewString(ctx, curveString.c_str()));
    return value;
}

JSValue ParseCurves(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv, std::string& curveString)
{
    JS_SetPropertyStr(ctx, value, CURVE_INTERPOLATE, JS_NewCFunction(ctx, CurvesInterpolate, CURVE_INTERPOLATE, 1));
    if ((!argv) || (argc != 4)) {
        LOGE("CurvesBezier or Spring curve args count is invalid");
        return JS_NULL;
    }
    double x0 = GetJsDoubleVal(ctx, argv[0]);
    double y0 = GetJsDoubleVal(ctx, argv[1]);
    double x1 = GetJsDoubleVal(ctx, argv[2]);
    double y1 = GetJsDoubleVal(ctx, argv[3]);
    RefPtr<Curve> curve;
    if (curveString == "spring") {
        curve = AceType::MakeRefPtr<SpringCurve>(x0, y0, x1, y1);
    } else if (curveString == "cubic-bezier") {
        curve = AceType::MakeRefPtr<CubicCurve>(x0, y0, x1, y1);
    } else {
        LOGE("curve params: %{public}s is illegal", curveString.c_str());
        return JS_NULL;
    }
    auto customCurve = curve->ToString();
    auto* instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return JS_NULL;
    }
    auto page = instance->GetRunningPage(ctx);
    if (page == nullptr) {
        LOGE("page is nullptr");
        return JS_NULL;
    }
    page->AddCurve(customCurve, curve);
    int32_t pageId = page->GetPageId();
    JS_SetPropertyStr(ctx, value, "__pageId", JS_NewInt32(ctx, pageId));
    JS_SetPropertyStr(ctx, value, "__curveString", JS_NewString(ctx, customCurve.c_str()));
    return value;
}

JSValue CurvesBezier(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    std::string curveString("cubic-bezier");
    return ParseCurves(ctx, value, argc, argv, curveString);
}

JSValue CurvesSpring(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    std::string curveString("spring");
    return ParseCurves(ctx, value, argc, argv, curveString);
}

void InitCurvesModule(JSContext* ctx, JSValue& moduleObj)
{
    JS_SetPropertyStr(ctx, moduleObj, CURVES_INIT, JS_NewCFunction(ctx, CurvesInit, CURVES_INIT, 1));
    JS_SetPropertyStr(ctx, moduleObj, CURVES_CUBIC_BEZIER, JS_NewCFunction(ctx, CurvesBezier, CURVES_CUBIC_BEZIER, 4));
    JS_SetPropertyStr(ctx, moduleObj, CURVES_SPRING, JS_NewCFunction(ctx, CurvesSpring, CURVES_SPRING, 4));
}
} // namespace OHOS::Ace::Framework