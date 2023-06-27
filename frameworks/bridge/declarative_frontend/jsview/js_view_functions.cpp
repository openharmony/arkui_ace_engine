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

#include <memory>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/base/composed_element.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

namespace {

JSRef<JSObject> GenConstraint(const std::optional<NG::LayoutConstraintF>& parentConstraint)
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

JSRef<JSObject> GenPadding(const std::unique_ptr<NG::PaddingProperty>& paddingNative)
{
    JSRef<JSObject> padding = JSRef<JSObject>::New();
    padding->SetProperty("top", paddingNative->top->ToString());
    padding->SetProperty("right", paddingNative->right->ToString());
    padding->SetProperty("bottom", paddingNative->bottom->ToString());
    padding->SetProperty("left", paddingNative->left->ToString());
    return padding;
}

JSRef<JSObject> GenEdgeWidths(const std::unique_ptr<NG::BorderWidthProperty>& edgeWidthsNative)
{
    JSRef<JSObject> edgeWidths = JSRef<JSObject>::New();
    edgeWidths->SetProperty("top", edgeWidthsNative->topDimen->ToString());
    edgeWidths->SetProperty("right", edgeWidthsNative->rightDimen->ToString());
    edgeWidths->SetProperty("bottom", edgeWidthsNative->bottomDimen->ToString());
    edgeWidths->SetProperty("left", edgeWidthsNative->leftDimen->ToString());
    return edgeWidths;
}

JSRef<JSObject> GenBorderInfo(const RefPtr<NG::LayoutWrapper>& layoutWrapper)
{
    JSRef<JSObject> borderInfo = JSRef<JSObject>::New();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    if (!layoutProperty) {
        return borderInfo;
    }

    const std::unique_ptr<NG::PaddingProperty> defaultPadding = std::make_unique<NG::PaddingProperty>();
    const std::unique_ptr<NG::BorderWidthProperty>& defaultEdgeWidth = std::make_unique<NG::BorderWidthProperty>();
    borderInfo->SetPropertyObject("borderWidth",
        GenEdgeWidths(
            layoutProperty->GetBorderWidthProperty() ? layoutProperty->GetBorderWidthProperty() : defaultEdgeWidth));

    borderInfo->SetPropertyObject("margin",
        GenPadding(layoutProperty->GetMarginProperty() ? layoutProperty->GetMarginProperty() : defaultPadding));
    borderInfo->SetPropertyObject("padding",
        GenPadding(layoutProperty->GetPaddingProperty() ? layoutProperty->GetPaddingProperty() : defaultPadding));

    return borderInfo;
}

JSRef<JSObject> GenPositionInfo(const RefPtr<NG::LayoutWrapper>& layoutWrapper)
{
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    JSRef<JSObject> position = JSRef<JSObject>::New();
    position->SetProperty("x", offset.GetX());
    position->SetProperty("y", offset.GetY());
    return position;
}

void FillSubComponetProperty(JSRef<JSObject>& info, const RefPtr<NG::LayoutWrapper>& layoutWrapper, const size_t& index)
{
    info->SetProperty<std::string>("name", layoutWrapper->GetHostNode()->GetTag());
    info->SetProperty<std::string>("id", std::to_string(layoutWrapper->GetHostNode()->GetId()));
    info->SetPropertyObject("constraint", GenConstraint(layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()));
    info->SetPropertyObject("borderInfo", GenBorderInfo(layoutWrapper));
    info->SetPropertyObject("position", GenPositionInfo(layoutWrapper));
}

JSRef<JSArray> GenLayoutChildArray(std::list<RefPtr<NG::LayoutWrapper>> children)
{
    JSRef<JSArray> childInfo = JSRef<JSArray>::New();
    JSRef<JSFunc> layoutFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSLayout);
    size_t index = 0;

    for (const auto& iter : children) {
        JSRef<JSObject> info = JSRef<JSObject>::New();
        FillSubComponetProperty(info, iter, index);
        info->SetPropertyObject("layout", layoutFunc);
        childInfo->SetValueAt(index++, info);
    }

    return childInfo;
}

JSRef<JSArray> GenMeasureChildArray(std::list<RefPtr<NG::LayoutWrapper>> children)
{
    JSRef<JSArray> childInfo = JSRef<JSArray>::New();
    JSRef<JSFunc> measureFunc = JSRef<JSFunc>::New<FunctionCallback>(ViewMeasureLayout::JSMeasure);
    size_t index = 0;

    for (const auto& iter : children) {
        JSRef<JSObject> info = JSRef<JSObject>::New();
        FillSubComponetProperty(info, iter, index);
        info->SetPropertyObject("measure", measureFunc);
        childInfo->SetValueAt(index++, info);
    }

    return childInfo;
}

} // namespace

void ViewFunctions::ExecuteLayout(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteLayout");
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    auto constraint = GenConstraint(parentConstraint);
    auto childArray = GenLayoutChildArray(children);
    JSRef<JSVal> params[2] = { childArray, constraint };

    ViewMeasureLayout::SetLayoutChildren(layoutWrapper->GetAllChildrenWithBuild());
    ViewMeasureLayout::SetDefaultMeasureConstraint(parentConstraint.value());
    jsLayoutFunc_.Lock()->Call(jsObject_.Lock(), 2, params);
}

void ViewFunctions::ExecuteMeasure(NG::LayoutWrapper* layoutWrapper)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    ACE_SCOPED_TRACE("ViewFunctions::ExecuteMeasure");
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    auto constraint = GenConstraint(parentConstraint);
    auto childArray = GenMeasureChildArray(children);
    JSRef<JSVal> params[2];

    params[0] = childArray;
    params[1] = constraint;

    ViewMeasureLayout::SetMeasureChildren(children);
    ViewMeasureLayout::SetDefaultMeasureConstraint(parentConstraint.value());
    jsMeasureFunc_.Lock()->Call(jsObject_.Lock(), 2, params);
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

#else

void ViewFunctions::ExecuteLayout(NG::LayoutWrapper* layoutWrapper) {}

void ViewFunctions::ExecuteMeasure(NG::LayoutWrapper* layoutWrapper) {}

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
        if (jsReloadFunc->IsFunction()) {
            jsForceRerenderNodeFunc_ = JSRef<JSFunc>::Cast(jsForceRerenderNodeFunc);
        } else {
            LOGE("View lacks mandatory 'forceRerenderNode()' function, fatal internal error.");
        }
    }

    JSRef<JSVal> jsAppearFunc = jsObject->GetProperty("aboutToAppear");
    if (jsAppearFunc->IsFunction()) {
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
        jsLayoutFunc_ = JSRef<JSFunc>::Cast(jsLayoutFunc);
    }

    JSRef<JSVal> jsMeasureFunc = jsObject->GetProperty("onMeasure");
    if (jsMeasureFunc->IsFunction()) {
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

    JSRef<JSVal> jsSetInitiallyProvidedValueFunc = jsObject->GetProperty("setInitiallyProvidedValue");
    if (jsSetInitiallyProvidedValueFunc->IsFunction()) {
        jsSetInitiallyProvidedValueFunc_ = JSRef<JSFunc>::Cast(jsSetInitiallyProvidedValueFunc);
    }

    if (!partialUpdate) {
        JSRef<JSVal> jsUpdateWithValueParamsFunc = jsObject->GetProperty("updateWithValueParams");
        if (jsUpdateWithValueParamsFunc->IsFunction()) {
            LOGD("updateWithValueParams is a function");
            jsUpdateWithValueParamsFunc_ = JSRef<JSFunc>::Cast(jsUpdateWithValueParamsFunc);
        } else {
            LOGD("updateWithValueParams is not a function");
        }

#ifdef UICAST_COMPONENT_SUPPORTED
        JSRef<JSVal> jsCreateChildViewFunc = jsObject->GetProperty("createChildView");
        if (jsCreateChildViewFunc->IsFunction()) {
            LOGI("UICast createChildView is a function");
            jsCreateChildViewFunc_ = JSRef<JSFunc>::Cast(jsCreateChildViewFunc);
        } else {
            LOGI("UICast createChildView is not a function");
        }

        JSRef<JSVal> jsRouterHandleFunc = jsObject->GetProperty("routerHandle");
        if (jsRouterHandleFunc->IsFunction()) {
            LOGI("UICast routerHandle is a function");
            jsRouterHandleFunc_ = JSRef<JSFunc>::Cast(jsRouterHandleFunc);
        } else {
            LOGI("UICast routerHandle is not a function");
        }

        JSRef<JSVal> jsReplayOnEventFunc = jsObject->GetProperty("replayOnEvent");
        if (jsReplayOnEventFunc->IsFunction()) {
            LOGI("UICast replayOnEvent is a function");
            jsReplayOnEventFunc_ = JSRef<JSFunc>::Cast(jsReplayOnEventFunc);
        } else {
            LOGI("UICast replayOnEvent is not a function");
        }
#endif

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
        LOGD("View doesn't have %{public}s() method!", "aboutToDisappear");
        return;
    }
    ACE_SCOPED_TRACE("%s", "aboutToDisappear");
    JSRef<JSVal> jsObject = jsObject_.Lock();
    std::string functionName("aboutToDisappear");
    if (!jsObject->IsUndefined()) {
        jsDisappearFunc_.Lock()->Call(jsObject);
    } else {
        LOGE("jsView Object is undefined and will not execute aboutToDisappear function");
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

void ViewFunctions::ExecuteAboutToBeDeleted()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context_)
    if (jsAboutToBeDeletedFunc_.IsEmpty()) {
        LOGD("View doesn't have %{public}s() method!", "aboutToBeDeleted");
        return;
    }
    ACE_SCOPED_TRACE("%s", "aboutToBeDeleted");
    JSRef<JSVal> jsObject = jsObject_.Lock();
    std::string functionName("aboutToBeDeleted");
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

#ifdef UICAST_COMPONENT_SUPPORTED
void ViewFunctions::ExecuteCreateChildView(const std::string& jsonData)
{
    ExecuteFunctionWithParams(jsCreateChildViewFunc_, "createChildView", jsonData);
}

void ViewFunctions::ExecuteRouterHandle(const std::string& jsonData)
{
    ExecuteFunctionWithParams(jsRouterHandleFunc_, "routerHandle", jsonData);
}

void ViewFunctions::ExecuteReplayOnEvent(const std::string& jsonData)
{
    ExecuteFunctionWithParams(jsReplayOnEventFunc_, "replayOnEvent", jsonData);
}
#endif

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

} // namespace OHOS::Ace::Framework
