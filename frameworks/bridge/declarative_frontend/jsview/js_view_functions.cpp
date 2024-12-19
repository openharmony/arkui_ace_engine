/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_functions.h"

#include <memory>
#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view.h"
#include "bridge/declarative_frontend/jsview/js_view_measure_layout.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace::Framework {
const std::string EMPTY_STATUS_DATA = "empty_status_data";

#ifdef USE_ARK_ENGINE

void ViewFunctions::ExecuteLayout(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteLayout");
    auto jsParam = JSMeasureLayoutParam::GetInstance(layoutWrapper);
    auto constraint = jsParam->GetConstraint();
    auto childArray = jsParam->GetChildArray();
    JSRef<JSVal> params[2] = { childArray, constraint };
    jsLayoutFunc_.Lock()->Call(jsObject_.Lock(), 2, params);
}

void ViewFunctions::ExecuteMeasure(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteMeasure");
    auto jsParam = JSMeasureLayoutParam::GetInstance(layoutWrapper);
    auto constraint = jsParam->GetConstraint();
    auto childArray = jsParam->GetChildArray();
    JSRef<JSVal> params[2] = { childArray, constraint };
    jsMeasureFunc_.Lock()->Call(jsObject_.Lock(), 2, params);
}

void ViewFunctions::ExecutePlaceChildren(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecutePlaceChildren");
    auto jsParam = JSMeasureLayoutParamNG::GetInstance(layoutWrapper);

    auto selfLayoutInfo = jsParam->GetSelfLayoutInfo();
    auto childArray = jsParam->GetChildArray();
    auto constraint = jsParam->GetPlaceChildrenConstraint();

    JSRef<JSVal> params[3] = { selfLayoutInfo, childArray, constraint };
    jsPlaceChildrenFunc_.Lock()->Call(jsObject_.Lock(), 3, params); /* 3:params number */
}

void ViewFunctions::InitJsParam(NG::LayoutWrapper* layoutWrapper)
{
    JSMeasureLayoutParamNG::GetInstance(layoutWrapper);
}

void ViewFunctions::ExecuteMeasureSize(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteMeasureSize");
    auto jsParam = JSMeasureLayoutParamNG::GetInstance(layoutWrapper);
    if (!jsParam) {
        layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GetInstance return val in onMeasureSize API is null");
        return;
    }

    auto selfLayoutInfo = jsParam->GetSelfLayoutInfo();
    auto childArray = jsParam->GetChildArray();
    auto constraint = jsParam->GetConstraint();

    JSRef<JSVal> params[3] = { selfLayoutInfo, childArray, constraint };
    JSRef<JSObject> result = jsMeasureSizeFunc_.Lock()->Call(jsObject_.Lock(), 3, params); /* 3:params number */
    if (result->IsUndefined()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "app return val of onMeasureSize API is empty or undefined");
        return;
    }

    CalcDimension measureWidth;
    CalcDimension measureHeight;
    if (!JSViewAbstract::ParseJsDimensionVp(result->GetProperty("width"), measureWidth)) {
        measureWidth = { -1.0f };
    }
    if (!JSViewAbstract::ParseJsDimensionVp(result->GetProperty("height"), measureHeight)) {
        measureWidth = { -1.0f };
    }
    NG::SizeF frameSize = { measureWidth.ConvertToPx(), measureHeight.ConvertToPx() };
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void ViewFunctions::ExecuteReload(bool deep)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteReload");
    auto func = jsReloadFunc_.Lock();
    if (!func.IsEmpty()) {
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>(JSVal(JsiValueConvertor::toJsiValue(deep)));
        func->Call(jsObject_.Lock(), 1, params);
    } else {
        LOGE("the reload func is null");
    }
}

void ViewFunctions::ExecuteForceNodeRerender(int32_t elemId)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteForceNodeRerender");
    auto func = jsForceRerenderNodeFunc_.Lock();
    if (!func.IsEmpty()) {
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>(JSVal(JsiValueConvertor::toJsiValue(elemId)));
        func->Call(jsObject_.Lock(), 1, params);
    } else {
        LOGE("the force node rerender func is null");
    }
}

bool ViewFunctions::ExecuteHasNodeUpdateFunc(int32_t elmtId)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_, false)
    auto func = jsHasNodeUpdateFunc_.Lock();
    if (func->IsEmpty()) {
        LOGE("the hasNodeUpdateFunc is null");
        return false;
    }
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>(JSVal(JsiValueConvertor::toJsiValue(elmtId)));
    auto result = func->Call(jsObject_.Lock(), 1, params);
    return result->IsBoolean() && result->ToBoolean();
}

// recycleSelf
void ViewFunctions::ExecuteRecycle(const std::string& viewName)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteRecycle");
    auto func = jsRecycleFunc_.Lock();
    if (!func->IsEmpty()) {
        auto recycleNodeName = JSRef<JSVal>::Make(ToJSValue(viewName));
        func->Call(jsObject_.Lock(), 1, &recycleNodeName);
    } else {
        LOGE("the recycle func is null");
    }
}

void ViewFunctions::ExecuteSetActive(bool active)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    auto func = jsSetActive_.Lock();
    if (!func->IsEmpty()) {
        JSFastNativeScope scope(func->GetEcmaVM());
        auto isActive = JSRef<JSVal>::Make(ToJSValue(active));
        func->Call(jsObject_.Lock(), 1, &isActive);
    } else {
        LOGE("the set active func is null");
    }
}

void ViewFunctions::ExecuteOnDumpInfo(const std::vector<std::string>& params)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    auto func = jsOnDumpInfo_.Lock();
    if (!func->IsEmpty()) {
        JSRef<JSArray> arr = JSRef<JSArray>::New();
        for (size_t i = 0; i < params.size(); ++i) {
            arr->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(params.at(i))));
        }
        JSRef<JSVal> argv = arr;
        func->Call(jsObject_.Lock(), 1, &argv);
    } else {
        LOGE("the on dump info func is null");
    }
}

std::string ViewFunctions::ExecuteOnDumpInfo()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_, "")
    std::string res;
    auto func = jsOnDumpInspector_.Lock();
    if (!func->IsEmpty()) {
        auto result = func->Call(jsObject_.Lock());
        if (result->IsString()) {
            res = result->ToString();
        }
    } else {
        LOGE("the onDumpInspector func is null");
    }
    return res;
}

#else

void ViewFunctions::ExecuteLayout(NG::LayoutWrapper* layoutWrapper) {}

void ViewFunctions::ExecuteMeasure(NG::LayoutWrapper* layoutWrapper) {}

void ViewFunctions::ExecutePlaceChildren(NG::LayoutWrapper* layoutWrapper) {}

void ViewFunctions::ExecuteMeasureSize(NG::LayoutWrapper* layoutWrapper) {}

void ViewFunctions::ExecuteReload(bool deep) {}

void ViewFunctions::ExecuteForceNodeRerender(int32_t elemId) {}

#endif

void ViewFunctions::InitViewFunctions(
    const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsRenderFunction, bool partialUpdate)
{
    jsObject_ = jsObject;

    if (partialUpdate) {
        if (jsObject->GetProperty("initialRender")->IsFunction()) {
            JSRef<JSVal> jsRenderFunc = jsObject->GetProperty("initialRenderView");
            if (jsRenderFunc->IsFunction()) {
                jsRenderFunc_ = JSRef<JSFunc>::Cast(jsRenderFunc);
            } else {
                LOGE("View lacks mandatory 'initialRenderView()' function, fatal internal error.");
            }
        } else {
            LOGE("View lacks mandatory 'initialRender()' function, fatal internal error.");
        }

        JSRef<JSVal> jsRerenderFunc = jsObject->GetProperty("rerender");
        if (jsRerenderFunc->IsFunction()) {
            jsRerenderFunc_ = JSRef<JSFunc>::Cast(jsRerenderFunc);
        } else {
            LOGE("View lacks mandatory 'rerender()' function, fatal internal error.");
        }

        JSRef<JSVal> jsReloadFunc = jsObject->GetProperty("forceCompleteRerender");
        if (jsReloadFunc->IsFunction()) {
            jsReloadFunc_ = JSRef<JSFunc>::Cast(jsReloadFunc);
        } else {
            LOGE("View lacks mandatory 'forceCompleteRerender()' function, fatal internal error.");
        }

        JSRef<JSVal> jsForceRerenderNodeFunc = jsObject->GetProperty("forceRerenderNode");
        if (jsForceRerenderNodeFunc->IsFunction()) {
            jsForceRerenderNodeFunc_ = JSRef<JSFunc>::Cast(jsForceRerenderNodeFunc);
        } else {
            LOGE("View lacks mandatory 'forceRerenderNode()' function, fatal internal error.");
        }

        JSRef<JSVal> jsHasNodeUpdateFunc = jsObject->GetProperty("hasNodeUpdateFunc");
        if (jsHasNodeUpdateFunc->IsFunction()) {
            jsHasNodeUpdateFunc_ = JSRef<JSFunc>::Cast(jsHasNodeUpdateFunc);
        }

        JSRef<JSVal> jsRecycleFunc = jsObject->GetProperty("recycleSelf");
        if (jsRecycleFunc->IsFunction()) {
            jsRecycleFunc_ = JSRef<JSFunc>::Cast(jsRecycleFunc);
        }

        JSRef<JSVal> jsAboutToRecycleFunc = jsObject->GetProperty("aboutToRecycleInternal");
        if (jsAboutToRecycleFunc->IsFunction()) {
            jsAboutToRecycleFunc_ = JSRef<JSFunc>::Cast(jsAboutToRecycleFunc);
        }

        JSRef<JSVal> jsAboutToReuseFunc = jsObject->GetProperty("aboutToReuseInternal");
        if (jsAboutToReuseFunc->IsFunction()) {
            jsAboutToReuseFunc_ = JSRef<JSFunc>::Cast(jsAboutToReuseFunc);
        }

        JSRef<JSVal> jsSetActive = jsObject->GetProperty("setActiveInternal");
        if (jsSetActive->IsFunction()) {
            jsSetActive_ = JSRef<JSFunc>::Cast(jsSetActive);
        }

        JSRef<JSVal> jsOnDumpInfo = jsObject->GetProperty("onDumpInfo");
        if (jsOnDumpInfo->IsFunction()) {
            jsOnDumpInfo_ = JSRef<JSFunc>::Cast(jsOnDumpInfo);
        }

        JSRef<JSVal> jsOnDumpInspector = jsObject->GetProperty("onDumpInspector");
        if (jsOnDumpInspector->IsFunction()) {
            jsOnDumpInspector_ = JSRef<JSFunc>::Cast(jsOnDumpInspector);
        }
    }

    JSRef<JSVal> jsAppearFunc = jsObject->GetProperty("aboutToAppear");
    if (jsAppearFunc->IsFunction()) {
        jsAppearFunc_ = JSRef<JSFunc>::Cast(jsAppearFunc);
    }

    JSRef<JSVal> jsDisappearFunc = jsObject->GetProperty("aboutToDisappear");
    if (jsDisappearFunc->IsFunction()) {
        jsDisappearFunc_ = JSRef<JSFunc>::Cast(jsDisappearFunc);
    }

    JSRef<JSVal> jsDidBuildFunc = jsObject->GetProperty("onDidBuild");
    if (jsDidBuildFunc->IsFunction()) {
        jsDidBuildFunc_ = JSRef<JSFunc>::Cast(jsDidBuildFunc);
    }

    JSRef<JSVal> jsLayoutFunc = jsObject->GetProperty("onLayout");
    if (jsLayoutFunc->IsFunction()) {
        jsLayoutFunc_ = JSRef<JSFunc>::Cast(jsLayoutFunc);
    }

    JSRef<JSVal> jsMeasureFunc = jsObject->GetProperty("onMeasure");
    if (jsMeasureFunc->IsFunction()) {
        jsMeasureFunc_ = JSRef<JSFunc>::Cast(jsMeasureFunc);
    }

    JSRef<JSVal> jsPlaceChildrenFunc = jsObject->GetProperty("onPlaceChildren");
    if (jsPlaceChildrenFunc->IsFunction()) {
        jsPlaceChildrenFunc_ = JSRef<JSFunc>::Cast(jsPlaceChildrenFunc);
    }

    JSRef<JSVal> jsMeasureSizeFunc = jsObject->GetProperty("onMeasureSize");
    if (jsMeasureSizeFunc->IsFunction()) {
        jsMeasureSizeFunc_ = JSRef<JSFunc>::Cast(jsMeasureSizeFunc);
    }

    JSRef<JSVal> jsAboutToBeDeletedFunc = jsObject->GetProperty("aboutToBeDeleted");
    if (jsAboutToBeDeletedFunc->IsFunction()) {
        jsAboutToBeDeletedFunc_ = JSRef<JSFunc>::Cast(jsAboutToBeDeletedFunc);
    } else {
        jsAboutToBeDeletedFunc = jsObject->GetProperty("aboutToBeDeletedInternal");
        if (jsAboutToBeDeletedFunc->IsFunction()) {
            jsAboutToBeDeletedFunc_ = JSRef<JSFunc>::Cast(jsAboutToBeDeletedFunc);
        }
    }

    JSRef<JSVal> jsAboutToRenderFunc = jsObject->GetProperty("aboutToRender");
    if (jsAboutToRenderFunc->IsFunction()) {
        jsAboutToRenderFunc_ = JSRef<JSFunc>::Cast(jsAboutToRenderFunc);
    }

    JSRef<JSVal> jsRenderDoneFunc = jsObject->GetProperty("onRenderDone");
    if (jsRenderDoneFunc->IsFunction()) {
        jsRenderDoneFunc_ = JSRef<JSFunc>::Cast(jsRenderDoneFunc);
    }

    JSRef<JSVal> jsAboutToBuildFunc = jsObject->GetProperty("aboutToBuild");
    if (jsAboutToBuildFunc->IsFunction()) {
        jsAboutToBuildFunc_ = JSRef<JSFunc>::Cast(jsAboutToBuildFunc);
    }

    JSRef<JSVal> jsBuildDoneFunc = jsObject->GetProperty("onBuildDone");
    if (jsBuildDoneFunc->IsFunction()) {
        jsBuildDoneFunc_ = JSRef<JSFunc>::Cast(jsBuildDoneFunc);
    }

    JSRef<JSVal> jsTransitionFunc = jsObject->GetProperty("pageTransition");
    if (jsTransitionFunc->IsFunction()) {
        jsTransitionFunc_ = JSRef<JSFunc>::Cast(jsTransitionFunc);
    }

    JSRef<JSVal> jsOnHideFunc = jsObject->GetProperty("onPageHide");
    if (jsOnHideFunc->IsFunction()) {
        jsOnHideFunc_ = JSRef<JSFunc>::Cast(jsOnHideFunc);
    }

    JSRef<JSVal> jsOnShowFunc = jsObject->GetProperty("onPageShow");
    if (jsOnShowFunc->IsFunction()) {
        jsOnShowFunc_ = JSRef<JSFunc>::Cast(jsOnShowFunc);
    }

    JSRef<JSVal> jsBackPressFunc = jsObject->GetProperty("onBackPress");
    if (jsBackPressFunc->IsFunction()) {
        jsBackPressFunc_ = JSRef<JSFunc>::Cast(jsBackPressFunc);
    }

    JSRef<JSVal> jsSetInitiallyProvidedValueFunc = jsObject->GetProperty("setInitiallyProvidedValue");
    if (jsSetInitiallyProvidedValueFunc->IsFunction()) {
        jsSetInitiallyProvidedValueFunc_ = JSRef<JSFunc>::Cast(jsSetInitiallyProvidedValueFunc);
    }

    if (!partialUpdate) {
        JSRef<JSVal> jsUpdateWithValueParamsFunc = jsObject->GetProperty("updateWithValueParams");
        if (jsUpdateWithValueParamsFunc->IsFunction()) {
            jsUpdateWithValueParamsFunc_ = JSRef<JSFunc>::Cast(jsUpdateWithValueParamsFunc);
        }
        jsRenderFunc_ = jsRenderFunction;
    }

    JSRef<JSVal> jsOnFormRecycleFunc = jsObject->GetProperty("onFormRecycle");
    if (jsOnFormRecycleFunc->IsFunction()) {
        jsOnFormRecycleFunc_ = JSRef<JSFunc>::Cast(jsOnFormRecycleFunc);
    }

    JSRef<JSVal> jsOnFormRecoverFunc = jsObject->GetProperty("onFormRecover");
    if (jsOnFormRecoverFunc->IsFunction()) {
        jsOnFormRecoverFunc_ = JSRef<JSFunc>::Cast(jsOnFormRecoverFunc);
    }
}

ViewFunctions::ViewFunctions(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsRenderFunction)
{
    ACE_DCHECK(jsObject);
    InitViewFunctions(jsObject, jsRenderFunction, false);
}

void ViewFunctions::ExecuteRender()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsRenderFunc_.IsEmpty()) {
        LOGE("no render function in View!");
        return;
    }

    auto func = jsRenderFunc_.Lock();
    JSRef<JSVal> jsThis = jsObject_.Lock();
    if (!jsThis->IsUndefined()) {
        jsRenderResult_ = func->Call(jsThis);
    } else {
        LOGE("jsView Object is undefined and will not execute render function");
    }
}

void ViewFunctions::ExecuteAppear()
{
    ExecuteFunction(jsAppearFunc_, "aboutToAppear");
}

void ViewFunctions::ExecuteDisappear()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsDisappearFunc_.IsEmpty()) {
        return;
    }
    ACE_SCOPED_TRACE("%s", "aboutToDisappear");
    JSRef<JSVal> jsObject = jsObject_.Lock();
    std::string functionName("aboutToDisappear");
    AceScopedPerformanceCheck scoped(functionName);
    if (!jsObject->IsUndefined()) {
        jsDisappearFunc_.Lock()->Call(jsObject);
    } else {
        LOGE("jsView Object is undefined and will not execute aboutToDisappear function");
    }
}

void ViewFunctions::ExecuteDidBuild()
{
    ExecuteFunction(jsDidBuildFunc_, "onDidBuild");
}

void ViewFunctions::ExecuteAboutToRecycle()
{
    ExecuteFunction(jsAboutToRecycleFunc_, "aboutToRecycleInternal");
}

void ViewFunctions::ExecuteAboutToReuse(void* params)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsAboutToReuseFunc_.IsEmpty()) {
        return;
    }
    ACE_SCOPED_TRACE("ExecuteAboutToReuse");
    JSRef<JSVal> jsObject = jsObject_.Lock();
    if (!jsObject->IsUndefined()) {
        std::string functionName("ExecuteAboutToReuse");
        AceScopedPerformanceCheck scoped(functionName);
        auto reuseParams = JsiCallbackInfo(reinterpret_cast<panda::JsiRuntimeCallInfo*>(params));
        JsiRef<JsiValue> params[1] = { reuseParams[0] };
        if (reuseParams.Length() > 0) {
            jsAboutToReuseFunc_.Lock()->Call(jsObject, 1, params);
        } else {
            jsAboutToReuseFunc_.Lock()->Call(jsObject);
        }
    } else {
        LOGE("jsObject is undefined. Internal error while trying to exec ExecuteAboutToReuse");
    }
}

bool ViewFunctions::HasLayout() const
{
    return !jsLayoutFunc_.IsEmpty();
}

bool ViewFunctions::HasMeasure() const
{
    return !jsMeasureFunc_.IsEmpty();
}

bool ViewFunctions::HasPlaceChildren() const
{
    return !jsPlaceChildrenFunc_.IsEmpty();
}

bool ViewFunctions::HasMeasureSize() const
{
    return !jsMeasureSizeFunc_.IsEmpty();
}

void ViewFunctions::ExecuteAboutToBeDeleted()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsAboutToBeDeletedFunc_.IsEmpty()) {
        return;
    }
    ACE_SCOPED_TRACE("%s", "aboutToBeDeleted");
    JSRef<JSVal> jsObject = jsObject_.Lock();
    std::string functionName("aboutToBeDeleted");
    AceScopedPerformanceCheck scoped(functionName);
    if (!jsObject->IsUndefined()) {
        jsAboutToBeDeletedFunc_.Lock()->Call(jsObject);
    } else {
        LOGE("jsView Object is undefined and will not execute aboutToBeDeleted function");
    }
}

void ViewFunctions::ExecuteAboutToRender()
{
    // for developer callback.
    ExecuteFunction(jsAboutToBuildFunc_, "aboutToBuild");
    // for state manager mark rendering progress.
    ExecuteFunction(jsAboutToRenderFunc_, "aboutToRender");
}

void ViewFunctions::ExecuteOnRenderDone()
{
    // for state manager reset rendering progress.
    ExecuteFunction(jsRenderDoneFunc_, "onRenderDone");
    // for developer callback.
    ExecuteFunction(jsBuildDoneFunc_, "onBuildDone");
}

void ViewFunctions::ExecuteTransition()
{
    ExecuteFunction(jsTransitionFunc_, "pageTransition");
}

bool ViewFunctions::HasPageTransition() const
{
    return !jsTransitionFunc_.IsEmpty();
}

void ViewFunctions::ExecuteShow()
{
    ExecuteFunction(jsOnShowFunc_, "onPageShow");
}

void ViewFunctions::ExecuteHide()
{
    ExecuteFunction(jsOnHideFunc_, "onPageHide");
}

void ViewFunctions::ExecuteInitiallyProvidedValue(const std::string& jsonData)
{
    ExecuteFunctionWithParams(jsSetInitiallyProvidedValueFunc_, "setInitiallyProvidedValue", jsonData);
}

// Method not needed for Partial Update code path
void ViewFunctions::ExecuteUpdateWithValueParams(const std::string& jsonData)
{
    ExecuteFunctionWithParams(jsUpdateWithValueParamsFunc_, "updateWithValueParams", jsonData);
}

bool ViewFunctions::ExecuteOnBackPress()
{
    auto ret = ExecuteFunctionWithReturn(jsBackPressFunc_, "onBackPress");
    if (!ret->IsEmpty() && ret->IsBoolean()) {
        return ret->ToBoolean();
    }
    return false;
}

void ViewFunctions::ExecuteFunction(JSWeak<JSFunc>& func, const char* debugInfo)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (func.IsEmpty()) {
        return;
    }
    ACE_SCOPED_TRACE("%s", debugInfo);
    JSRef<JSVal> jsObject = jsObject_.Lock();
    if (!jsObject->IsUndefined()) {
        std::string functionName(debugInfo);
        AceScopedPerformanceCheck scoped(functionName);
        func.Lock()->Call(jsObject);
    } else {
        LOGE("jsObject is undefined. Internal error while trying to exec %{public}s", debugInfo);
    }
}

JSRef<JSVal> ViewFunctions::ExecuteFunctionWithReturn(JSWeak<JSFunc>& func, const char* debugInfo)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_, JSRef<JSVal>::Make())
    if (func.IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    ACE_SCOPED_TRACE("%s", debugInfo);
    JSRef<JSVal> jsObject = jsObject_.Lock();
    std::string functionName(debugInfo);
    AceScopedPerformanceCheck scoped(functionName);
    JSRef<JSVal> result = func.Lock()->Call(jsObject);
    if (result.IsEmpty()) {
        LOGE("Error calling %{public}s", debugInfo);
    }
    return result;
}

void ViewFunctions::ExecuteFunctionWithParams(JSWeak<JSFunc>& func, const char* debugInfo, const std::string& jsonData)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (func.IsEmpty()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSVal> param = obj->ToJsonObject(jsonData.c_str());

    JSRef<JSVal> jsObject = jsObject_.Lock();
    JSRef<JSVal> result = func.Lock()->Call(jsObject, 1, &param);
    if (result.IsEmpty()) {
        LOGE("Error calling %{public}s", debugInfo);
    }
}

// Baseline version of Destroy
void ViewFunctions::Destroy(JSView* parentCustomView)
{
    // Might be called from parent view, before any result has been produced??
    if (jsRenderResult_.IsEmpty()) {
        return;
    }

    auto renderRes = jsRenderResult_.Lock();
    if (renderRes.IsEmpty() || !renderRes->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(renderRes);
    if (!obj.IsEmpty()) {
        // jsRenderResult_ maybe an js exception, not a JSView
        JSView* view = obj->Unwrap<JSView>();
        if (view != nullptr) {
            view->Destroy(parentCustomView);
        }
    }
    jsRenderResult_.Reset();
}

// PartialUpdate version of Destroy
void ViewFunctions::Destroy()
{
    // Might be called from parent view, before any result has been produced??
    if (jsRenderResult_.IsEmpty()) {
        return;
    }

    auto renderRes = jsRenderResult_.Lock();
    if (renderRes.IsEmpty() || !renderRes->IsObject()) {
        return;
    }

    // merging: when would a render function return a JSView ?
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(renderRes);
    if (!obj.IsEmpty()) {
        // jsRenderResult_ maybe an js exception, not a JSView
        JSView* view = obj->Unwrap<JSView>();
        if (view != nullptr) {
            LOGE("NOTE NOTE NOTE render returned a JSView object that's dangling!");
        }
    }
    jsObject_.Reset();
    jsRenderResult_.Reset();
}

// Partial update method
void ViewFunctions::ExecuteRerender()
{
    COMPONENT_UPDATE_DURATION();
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsRerenderFunc_.IsEmpty()) {
        LOGE("no rerender function in View!");
        return;
    }

    auto func = jsRerenderFunc_.Lock();
    JSRef<JSVal> jsThis = jsObject_.Lock();
    if (!jsThis->IsUndefined()) {
        jsRenderResult_ = func->Call(jsThis);
    } else {
        LOGE("jsView Object is undefined and will not execute rerender function");
    }
}

// Partial update method
ViewFunctions::ViewFunctions(const JSRef<JSObject>& jsObject)
{
    InitViewFunctions(jsObject, JSRef<JSFunc>(), true);
}

std::string ViewFunctions::ExecuteOnFormRecycle()
{
    auto ret = ExecuteFunctionWithReturn(jsOnFormRecycleFunc_, "OnFormRecycle");
    if (!ret->IsEmpty() && ret->IsString()) {
        std::string statusData = ret->ToString();
        return statusData.empty() ? EMPTY_STATUS_DATA : statusData;
    }
    LOGE("ExecuteOnFormRecycle failed");
    return "";
}

void ViewFunctions::ExecuteOnFormRecover(const std::string& statusData)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsOnFormRecoverFunc_.IsEmpty()) {
        LOGE("jsOnFormRecoverFunc_ is null");
        return;
    }

    std::string data;
    if (statusData != EMPTY_STATUS_DATA) {
        data = statusData;
    }
    auto jsData = JSRef<JSVal>::Make(ToJSValue(data));
    auto func = jsOnFormRecoverFunc_.Lock();
    func->Call(jsObject_.Lock(), 1, &jsData);
}
} // namespace OHOS::Ace::Framework
