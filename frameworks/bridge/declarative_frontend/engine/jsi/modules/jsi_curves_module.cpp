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

#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_curves_module.h"

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/core/animation/curve.h"

namespace OHOS::Ace::Framework {

double GetJsDoubleVal(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& value)
{
    auto jsonVal = JsonUtil::ParseJsonData(value->ToString(runtime).c_str());
    if (jsonVal && jsonVal->IsNumber()) {
        return jsonVal->GetDouble();
    }
    return 0.0;
}

shared_ptr<JsValue> CurvesInterpolate(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    auto jsPageId = thisObj->GetProperty(runtime, "__pageId");
    auto pageId = jsPageId->ToInt32(runtime);
    auto jsCurveString = thisObj->GetProperty(runtime, "__curveString");
    auto curveString = jsCurveString->ToString(runtime);

    double time = GetJsDoubleVal(runtime, argv[0]);
    auto instance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (instance == nullptr) {
        LOGE("get jsi engine instance failed");
        return runtime->NewNull();
    }
    auto delegate = instance->GetDelegate();
    if (delegate == nullptr) {
        LOGE("delegate is null.");
        return runtime->NewNull();
    }
    auto page = delegate->GetPage(pageId);
    if (page == nullptr) {
        LOGE("page is null.");
        return runtime->NewNull();
    }
    auto animationCurve = page->GetCurve(curveString);
    if (!animationCurve) {
        LOGE("animationCurve is null.");
        return runtime->NewNull();
    }
    double curveValue = animationCurve->Move(time);
    return runtime->NewNumber(curveValue);
}

shared_ptr<JsValue> CurvesInit(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    thisObj->SetProperty(runtime, CURVE_INTERPOLATE, runtime->NewFunction(CurvesInterpolate));
    if (argc != 1 && argc != 0) {
        LOGE("CurvesInit args count is invalid");
        return runtime->NewNull();
    }
    RefPtr<Curve> curve;
    std::string curveString;
    if (argc == 1) {
        curveString = argv[0]->ToString(runtime);
    } else {
        curveString = "linear";
    }
    curve = CreateCurve(curveString);
    auto instance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (instance == nullptr) {
        LOGE("get jsi engine instance failed");
        return runtime->NewNull();
    }
    auto page = instance->GetStagingPage();
    if (page == nullptr) {
        LOGE("page is nullptr");
        return runtime->NewNull();
    }

    page->AddCurve(curveString, curve);
    int32_t pageId = page->GetPageId();
    thisObj->SetProperty(runtime, "__pageId", runtime->NewInt32(pageId));
    thisObj->SetProperty(runtime, "__curveString", runtime->NewString(curveString));
    return thisObj;
}

shared_ptr<JsValue> ParseCurves(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, std::string& curveString)
{
    thisObj->SetProperty(runtime, CURVE_INTERPOLATE, runtime->NewFunction(CurvesInterpolate));
    if (argc != 4) {
        LOGE("CurvesBezier or Spring curve args count is invalid");
        return runtime->NewNull();
    }
    double x0 = GetJsDoubleVal(runtime, argv[0]);
    double y0 = GetJsDoubleVal(runtime, argv[1]);
    double x1 = GetJsDoubleVal(runtime, argv[2]);
    double y1 = GetJsDoubleVal(runtime, argv[3]);
    RefPtr<Curve> curve;
    if (curveString == "spring") {
        curve = AceType::MakeRefPtr<SpringCurve>(x0, y0, x1, y1);
    } else if (curveString == "cubic-bezier") {
        curve = AceType::MakeRefPtr<CubicCurve>(x0, y0, x1, y1);
    } else {
        LOGE("curve params: %{public}s is illegal", curveString.c_str());
        return runtime->NewNull();
    }
    auto customCurve = curve->ToString();
    auto instance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (instance == nullptr) {
        LOGE("get jsi engine instance failed");
        return runtime->NewNull();
    }
    auto page = instance->GetStagingPage();
    if (page == nullptr) {
        LOGE("page is nullptr");
        return runtime->NewNull();
    }
    page->AddCurve(customCurve, curve);
    int32_t pageId = page->GetPageId();
    thisObj->SetProperty(runtime, "__pageId", runtime->NewInt32(pageId));
    thisObj->SetProperty(runtime, "__curveString", runtime->NewString(customCurve));
    return thisObj;
}

shared_ptr<JsValue> CurvesBezier(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString("cubic-bezier");
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> CurvesSpring(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString("spring");
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

void InitCurvesModule(const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& moduleObj)
{
    moduleObj->SetProperty(runtime, CURVES_INIT, runtime->NewFunction(CurvesInit));
    moduleObj->SetProperty(runtime, CURVES_CUBIC_BEZIER, runtime->NewFunction(CurvesBezier));
    moduleObj->SetProperty(runtime, CURVES_SPRING, runtime->NewFunction(CurvesSpring));
}

} // namespace OHOS::Ace::Framework