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

#include "frameworks/bridge/declarative_frontend/jsview/js_view_functions.h"
// #include "frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h"
#include <cstddef>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/base/composed_element.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

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
    }

    JSRef<JSVal> jsAppearFunc = jsObject->GetProperty("aboutToAppear");
    if (jsAppearFunc->IsFunction()) {
        LOGD("%s, receive js function aboutToAppear", OHOS::Ace::DEVTAG.c_str());
        jsAppearFunc_ = JSRef<JSFunc>::Cast(jsAppearFunc);
    }

    JSRef<JSVal> jsDisappearFunc = jsObject->GetProperty("aboutToDisappear");
    if (jsDisappearFunc->IsFunction()) {
        jsDisappearFunc_ = JSRef<JSFunc>::Cast(jsDisappearFunc);
    } else {
        LOGD("aboutToDisappear is not a function");
    }

    JSRef<JSVal> jsLayoutFunc = jsObject->GetProperty("onLayout");
    if (jsLayoutFunc->IsFunction()) {
        LOGD("%s, receive js function onLayout", OHOS::Ace::DEVTAG.c_str());
        jsLayoutFunc_ = JSRef<JSFunc>::Cast(jsLayoutFunc);
    }

    JSRef<JSVal> jsMeasureFunc = jsObject->GetProperty("onMeasure");
    if (jsMeasureFunc->IsFunction()) {
        LOGD("%s, receive js function onMeasure", OHOS::Ace::DEVTAG.c_str());
        jsMeasureFunc_ = JSRef<JSFunc>::Cast(jsMeasureFunc);
    }

    JSRef<JSVal> jsAboutToBeDeletedFunc = jsObject->GetProperty("aboutToBeDeleted");
    if (jsAboutToBeDeletedFunc->IsFunction()) {
        jsAboutToBeDeletedFunc_ = JSRef<JSFunc>::Cast(jsAboutToBeDeletedFunc);
    } else {
        LOGD("aboutToBeDeleted is not a function");
    }

    JSRef<JSVal> jsAboutToRenderFunc = jsObject->GetProperty("aboutToRender");
    if (jsAboutToRenderFunc->IsFunction()) {
        jsAboutToRenderFunc_ = JSRef<JSFunc>::Cast(jsAboutToRenderFunc);
    } else {
        LOGD("aboutToRender is not a function");
    }

    JSRef<JSVal> jsRenderDoneFunc = jsObject->GetProperty("onRenderDone");
    if (jsRenderDoneFunc->IsFunction()) {
        jsRenderDoneFunc_ = JSRef<JSFunc>::Cast(jsRenderDoneFunc);
    } else {
        LOGD("onRenderDone is not a function");
    }

    JSRef<JSVal> jsAboutToBuildFunc = jsObject->GetProperty("aboutToBuild");
    if (jsAboutToBuildFunc->IsFunction()) {
        jsAboutToBuildFunc_ = JSRef<JSFunc>::Cast(jsAboutToBuildFunc);
    } else {
        LOGD("aboutToBuild is not a function");
    }

    JSRef<JSVal> jsBuildDoneFunc = jsObject->GetProperty("onBuildDone");
    if (jsBuildDoneFunc->IsFunction()) {
        jsBuildDoneFunc_ = JSRef<JSFunc>::Cast(jsBuildDoneFunc);
    } else {
        LOGD("onBuildDone is not a function");
    }

    JSRef<JSVal> jsTransitionFunc = jsObject->GetProperty("pageTransition");
    if (jsTransitionFunc->IsFunction()) {
        jsTransitionFunc_ = JSRef<JSFunc>::Cast(jsTransitionFunc);
    } else {
        LOGD("transition is not a function");
    }

    JSRef<JSVal> jsOnHideFunc = jsObject->GetProperty("onPageHide");
    if (jsOnHideFunc->IsFunction()) {
        jsOnHideFunc_ = JSRef<JSFunc>::Cast(jsOnHideFunc);
    } else {
        LOGD("onHide is not a function");
    }

    JSRef<JSVal> jsOnShowFunc = jsObject->GetProperty("onPageShow");
    if (jsOnShowFunc->IsFunction()) {
        jsOnShowFunc_ = JSRef<JSFunc>::Cast(jsOnShowFunc);
    } else {
        LOGD("onShow is not a function");
    }

    JSRef<JSVal> jsBackPressFunc = jsObject->GetProperty("onBackPress");
    if (jsBackPressFunc->IsFunction()) {
        jsBackPressFunc_ = JSRef<JSFunc>::Cast(jsBackPressFunc);
    } else {
        LOGD("onBackPress is not a function");
    }

    if (!partialUpdate) {
        JSRef<JSVal> jsUpdateWithValueParamsFunc = jsObject->GetProperty("updateWithValueParams");
        if (jsUpdateWithValueParamsFunc->IsFunction()) {
            LOGD("updateWithValueParams is a function");
            jsUpdateWithValueParamsFunc_ = JSRef<JSFunc>::Cast(jsUpdateWithValueParamsFunc);
        } else {
            LOGD("updateWithValueParams is not a function");
        }
        jsRenderFunc_ = jsRenderFunction;
    }
}

ViewFunctions::ViewFunctions(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsRenderFunction)
{
    ACE_DCHECK(jsObject);
    InitViewFunctions(jsObject, jsRenderFunction, false);
}

void ViewFunctions::ExecuteRender()
{
    if (jsRenderFunc_.IsEmpty()) {
        LOGE("no render function in View!");
        return;
    }

    auto func = jsRenderFunc_.Lock();
    JSRef<JSVal> jsThis = jsObject_.Lock();
    jsRenderResult_ = func->Call(jsThis);
}

void ViewFunctions::ExecuteAppear()
{
    ExecuteFunction(jsAppearFunc_, "aboutToAppear");
}

void ViewFunctions::ExecuteDisappear()
{
    ExecuteFunction(jsDisappearFunc_, "aboutToDisappear");
}

namespace {

JSRef<JSObject> genConstraint(const std::optional<NG::LayoutConstraintF>& parentConstraint)
{
    auto minSize = parentConstraint->minSize;
    auto maxSize = parentConstraint->maxSize;
    JSRef<JSObject> constraint = JSRef<JSObject>::New();
    constraint->SetProperty<double>("minWidth", minSize.Width());
    constraint->SetProperty<double>("minHeight", minSize.Height());
    constraint->SetProperty<double>("maxWidth", maxSize.Width());
    constraint->SetProperty<double>("maxHeight", maxSize.Height());
    return constraint;
}

JSRef<JSArray> genChildArray(std::list<RefPtr<NG::LayoutWrapper>> children)
{
    JSRef<JSArray> childInfo = JSRef<JSArray>::New();
    size_t index = 0;
    for (const auto& iter : children) {
        JSRef<JSObject> info = JSRef<JSObject>::New();
        info->SetProperty<std::string>("name", iter->GetGeometryNode()->GetFrameSize().ToString());
        childInfo->SetValueAt(index++, info);
    }
    return childInfo;
}

} // namespace

void ViewFunctions::ExecuteLayout(NG::LayoutWrapper* layoutWrapper)
{
    LOGD("%s, ExecuteLayout ------------------------------------------------ in", OHOS::Ace::DEVTAG.c_str());

    auto children = layoutWrapper->GetAllChildrenWithBuild();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();

    auto jsConstraint = genConstraint(parentConstraint);
    auto childArray = genChildArray(children);

    JSRef<JSVal> params[2] = { childArray, jsConstraint };

    layoutChildren_ = layoutWrapper->GetAllChildrenWithBuild();
    iterLayoutChildren_ = layoutChildren_.begin();
    parentGlobalOffset = layoutWrapper->GetGeometryNode()->GetParentGlobalOffset();

    jsLayoutFunc_.Lock()->Call(jsObject_.Lock(), 2, params);
    LOGD("%s, ExecuteLayout ------------------------------------------------ out", OHOS::Ace::DEVTAG.c_str());
}

void ViewFunctions::ExecuteMeasure(NG::LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    LOGD("%s, ExecuteMeasure ------------------------------------------------ in", OHOS::Ace::DEVTAG.c_str());
    LOGD("%s, do Measure, info, child size %d", OHOS::Ace::DEVTAG.c_str(), children.size());

    for (const auto& child : children) {
        auto childGeometryNode = child->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetFrameSize();
        auto childFrameOffset = childGeometryNode->GetFrameOffset();
        LOGD("%s, do Measure child info, %s, %s", OHOS::Ace::DEVTAG.c_str(), childFrameSize.ToString().c_str(),
            childFrameOffset.ToString().c_str());
    }
    JSRef<JSVal> params[2];

    auto minSize = parentConstraint->minSize;
    auto maxSize = parentConstraint->maxSize;
    JSRef<JSObject> constraint = JSRef<JSObject>::New();
    constraint->SetProperty<double>("minWidth", minSize.Width());
    constraint->SetProperty<double>("minHeight", minSize.Height());
    constraint->SetProperty<double>("maxWidth", maxSize.Width());
    constraint->SetProperty<double>("maxHeight", maxSize.Height());

    JSRef<JSArray> childInfo = JSRef<JSArray>::New();
    size_t index = 0;
    for (const auto& iter : children) {
        JSRef<JSObject> info = JSRef<JSObject>::New();
        info->SetProperty<std::string>("name", iter->GetGeometryNode()->GetFrameSize().ToString());
        childInfo->SetValueAt(index++, info);
    }

    params[0] = childInfo;
    params[1] = constraint;

    measureChildren_ = children;
    iterMeasureChildren_ = measureChildren_.begin();
    measureDefaultConstraint_ = parentConstraint.value();

    jsMeasureFunc_.Lock()->Call(jsObject_.Lock(), 2, params);

    LOGD("%s, do Measure, info: %s, %s", OHOS::Ace::DEVTAG.c_str(), minSize.ToString().c_str(),
        maxSize.ToString().c_str());
    LOGD("%s, ExecuteMeasure ------------------------------------------------ out", OHOS::Ace::DEVTAG.c_str());
}

bool ViewFunctions::HasLayout() const
{
    return !jsLayoutFunc_.IsEmpty();
}

bool ViewFunctions::HasMeasure() const
{
    return !jsMeasureFunc_.IsEmpty();
}

void ViewFunctions::ExecuteAboutToBeDeleted()
{
    ExecuteFunction(jsAboutToBeDeletedFunc_, "aboutToDisappear");
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
        LOGD("View doesn't have %{public}s() method!", debugInfo);
        return;
    }
    ACE_SCOPED_TRACE("%s", debugInfo);
    JSRef<JSVal> jsObject = jsObject_.Lock();
    func.Lock()->Call(jsObject);
}

JSRef<JSVal> ViewFunctions::ExecuteFunctionWithReturn(JSWeak<JSFunc>& func, const char* debugInfo)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_, JSRef<JSVal>::Make())
    if (func.IsEmpty()) {
        LOGD("View doesn't have %{public}s() method!", debugInfo);
        return JSRef<JSVal>::Make();
    }
    ACE_SCOPED_TRACE("%s", debugInfo);
    JSRef<JSVal> jsObject = jsObject_.Lock();
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
        LOGD("View doesn't have %{public}s() method!", debugInfo);
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
    LOGD("Destroy");
    // Might be called from parent view, before any result has been produced??
    if (jsRenderResult_.IsEmpty()) {
        LOGD("ViewFunctions::Destroy() -> no previous render result to delete");
        return;
    }

    auto renderRes = jsRenderResult_.Lock();
    if (renderRes.IsEmpty() || !renderRes->IsObject()) {
        LOGD("ViewFunctions::Destroy() -> result not an object");
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
    LOGD("ViewFunctions::Destroy() end");
}

// PartialUpdate version of Destroy
void ViewFunctions::Destroy()
{
    LOGD("Destroy");

    // Might be called from parent view, before any result has been produced??
    if (jsRenderResult_.IsEmpty()) {
        LOGD("ViewFunctions::Destroy() -> no previous render result to delete");
        return;
    }

    auto renderRes = jsRenderResult_.Lock();
    if (renderRes.IsEmpty() || !renderRes->IsObject()) {
        LOGD("ViewFunctions::Destroy() -> result not an object");
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

    LOGD("ViewFunctions::Destroy() end");
}

// Partial update method
void ViewFunctions::ExecuteRerender()
{
    if (jsRerenderFunc_.IsEmpty()) {
        LOGE("no rerender function in View!");
        return;
    }

    auto func = jsRerenderFunc_.Lock();
    JSRef<JSVal> jsThis = jsObject_.Lock();
    jsRenderResult_ = func->Call(jsThis);
}

// Partial update method
ViewFunctions::ViewFunctions(const JSRef<JSObject>& jsObject)
{
    InitViewFunctions(jsObject, JSRef<JSFunc>(), true);
}

} // namespace OHOS::Ace::Framework
