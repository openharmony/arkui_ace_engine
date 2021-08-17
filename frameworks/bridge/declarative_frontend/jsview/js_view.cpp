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

#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

#include "base/log/ace_trace.h"
#include "core/pipeline/base/composed_element.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

ViewFunctions::ViewFunctions(JSRef<JSObject> jsObject, JSRef<JSFunc> jsRenderFunction)
{
    jsObject_ = jsObject;

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

    JSRef<JSVal> jsTransitionFunc = jsObject->GetProperty("pageTransition");
    if (jsTransitionFunc->IsFunction()) {
        jsTransitionFunc_ = JSRef<JSFunc>::Cast(jsTransitionFunc);
    } else {
        LOGE("transition is not a function");
    }

    jsRenderFunc_ = jsRenderFunction;
}

void ViewFunctions::executeRender()
{
    if (jsRenderFunc_.IsEmpty()) {
        LOGE("no render function in View!");
        return;
    }

    auto func = jsRenderFunc_.Lock();
    JSRef<JSVal> jsThis = jsObject_.Lock();
    JSRef<JSVal> res = func->Call(jsThis);
    if (!res.IsEmpty()) {
        jsRenderResult_ = res;
    }

    if (jsRenderResult_.IsEmpty()) {
        LOGE("Result of render function is empty!");
    }
}

void ViewFunctions::executeAppear()
{
    executeFunction(jsAppearFunc_, "aboutToAppear");
}

void ViewFunctions::executeDisappear()
{
    executeFunction(jsDisappearFunc_, "aboutToDisappear");
}

void ViewFunctions::executeAboutToBeDeleted()
{
    executeFunction(jsAboutToBeDeletedFunc_, "aboutToDisappear");
}

void ViewFunctions::executeAboutToRender()
{
    executeFunction(jsAboutToRenderFunc_, "aboutToRender");
}

void ViewFunctions::executeOnRenderDone()
{
    executeFunction(jsRenderDoneFunc_, "onRenderDone");
}

void ViewFunctions::executeTransition()
{
    executeFunction(jsTransitionFunc_, "pageTransition");
}

void ViewFunctions::executeFunction(JSWeak<JSFunc>& func, const char* debugInfo)
{
    if (func.IsEmpty()) {
        LOGD("View doesn't have %{public}s() method!", debugInfo);
        return;
    }
    LOGD("View has %{public}s() method!", debugInfo);

    JSRef<JSVal> jsObject = jsObject_.Lock();
    JSRef<JSVal> result = func.Lock()->Call(jsObject);
    if (result.IsEmpty()) {
        LOGE("Error calling %{public}s", debugInfo);
    }
}

void ViewFunctions::Destroy(JSView* parentCustomView)
{
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
        JSView* view = obj->Unwrap<JSView>();
        view->Destroy(parentCustomView);
    }
    jsRenderResult_.Reset();
    LOGD("ViewFunctions::Destroy() end");
}

JSView::JSView(const std::string& viewId, JSRef<JSObject> jsObject, JSRef<JSFunc> jsRenderFunction)
    : viewId_(viewId)
{
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsObject, jsRenderFunction);
    LOGD("JSView constructor");
}

JSView::~JSView()
{
    jsViewFunction_.Reset();
    LOGD("DestroyJSView");
};

RefPtr<OHOS::Ace::Component> JSView::CreateComponent()
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    LOGE("Create component: View  -> create composed component");
    // create component, return new something, need to set proper ID

    std::string key = ViewStackProcessor::GetInstance()->ProcessViewId(viewId_);
    auto composedComponent = AceType::MakeRefPtr<ComposedComponent>(key, "view");

    // add callback for element creation to component, and get pointer reference
    // to the element on creation. When state of this view changes, mark the
    // element to dirty.
    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<Component> {
        auto jsView = weak.Upgrade();
        return jsView ? jsView->InternalRender() : nullptr;
    };

    auto elementFunction = [&, renderFunction](const RefPtr<ComposedElement>& element) {
        if (element_.Invalid()) {
            jsViewFunction_->executeAppear();
        }
        element_ = element;
        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        if (element) {
            element->SetRenderFunction(std::move(renderFunction));
        }
    };

    composedComponent->SetElementFunction(std::move(elementFunction));

    if (jsViewFunction_) {
        jsViewFunction_->executeTransition();
    }

    if (IsStatic()) {
        LOGD("will mark composedComponent as static");
        composedComponent->SetStatic();
    }
    return composedComponent;
}

RefPtr<OHOS::Ace::PageTransitionComponent> JSView::BuildPageTransitionComponent()
{
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    ViewStackProcessor::GetInstance()->ClearPageTransitionComponent();
    return pageTransitionComponent;
}

RefPtr<OHOS::Ace::Component> JSView::InternalRender()
{
    LOGD("JSView: InternalRender");
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    needsUpdate_ = false;
    if (!jsViewFunction_) {
        LOGE("JSView: InternalRender jsViewFunction_ error");
        return nullptr;
    }
    jsViewFunction_->executeAboutToRender();
    jsViewFunction_->executeRender();
    jsViewFunction_->executeOnRenderDone();
    CleanUpAbandonedChild();
    jsViewFunction_->Destroy(this);
    return ViewStackProcessor::GetInstance()->Finish();
}

/**
 * marks the JSView's composed component as needing update / rerender
 */
void JSView::MarkNeedUpdate()
{
    ACE_DCHECK((!GetElement().Invalid()) && "JSView's ComposedElement must be created before requesting an update");
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");
    LOGD("JSView has just been marked to need update");

    auto element = GetElement().Upgrade();
    if (element) {
        element->MarkDirty();
    }
    needsUpdate_ = true;
}

void JSView::Destroy(JSView* parentCustomView)
{
    LOGD("JSView::Destroy start");
    DestroyChild(parentCustomView);
    jsViewFunction_->executeDisappear();
    jsViewFunction_->executeAboutToBeDeleted();
    jsViewFunction_.Reset();
    LOGD("JSView::Destroy end");
}

void JSView::Create(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        JSRefPtr<JSView> view = JSRef<JSObject>::Cast(info[0]);
        ViewStackProcessor::GetInstance()->Push(view->CreateComponent());
    } else {
        LOGE("JSView Object is expected.");
    }
}

void JSView::JSBind(BindingTarget object)
{
    JSClass<JSView>::Declare("NativeView");
    JSClass<JSView>::StaticMethod("create", &JSView::Create);
    JSClass<JSView>::Method("markNeedUpdate", &JSView::MarkNeedUpdate);
    JSClass<JSView>::Method("needsUpdate", &JSView::NeedsUpdate);
    JSClass<JSView>::Method("markStatic", &JSView::MarkStatic);
    JSClass<JSView>::CustomMethod("findChildById", &JSView::FindChildById);
    JSClass<JSView>::Inherit<JSViewAbstract>();
    JSClass<JSView>::Bind(object, ConstructorCallback, DestructorCallback);
}

void JSView::FindChildById(const JSCallbackInfo& info)
{
    LOGD("JSView::FindChildById");
    if (info[0]->IsNumber() || info[0]->IsString()) {
        std::string viewId = info[0]->ToString();
        JSRefPtr<JSView> jsView = GetChildById(viewId);
        info.SetReturnValue(jsView.Get());
    } else {
        LOGE("JSView FindChildById with invalid arguments.");
        JSException::Throw("%s", "JSView FindChildById with invalid arguments.");
    }
}

void JSView::ConstructorCallback(const JSCallbackInfo& info)
{
    JSRef<JSObject> thisObj = info.This();
    JSRef<JSVal> renderFunc = thisObj->GetProperty("render");
    if (!renderFunc->IsFunction()) {
        LOGE("View derived classes must provide render(){...} function");
        JSException::Throw("%s", "View derived classes must provide render(){...} function");
        return;
    }

    int argc = info.Length();
    if (argc > 1 && (info[0]->IsNumber() || info[0]->IsString())) {
        std::string viewId = info[0]->ToString();
        auto instance = AceType::MakeRefPtr<JSView>(viewId, info.This(), JSRef<JSFunc>::Cast(renderFunc));
        instance->IncRefCount();
        info.SetReturnValue(AceType::RawPtr(instance));
        if (!info[1]->IsUndefined() && info[1]->IsObject()) {
            JSRef<JSObject> parentObj = JSRef<JSObject>::Cast(info[1]);
            JSView* parentView = parentObj->Unwrap<JSView>();
            parentView->AddChildById(viewId, info.This());
        }
    } else {
        LOGE("JSView creation with invalid arguments.");
        JSException::Throw("%s", "JSView creation with invalid arguments.");
    }
}

void JSView::DestructorCallback(JSView* view)
{
    LOGD("JSView(DestructorCallback) start");
    view->DecRefCount();
    LOGD("JSView(DestructorCallback) end");
}

void JSView::DestroyChild(JSView* parentCustomView)
{
    LOGD("JSView::DestroyChild start");
    for (auto child : customViewChildren_) {
        child.second->Destroy(this);
        child.second.Reset();
    }
    LOGD("JSView::DestroyChild end");
}

void JSView::CleanUpAbandonedChild()
{
    auto startIter = customViewChildren_.begin();
    auto endIter = customViewChildren_.end();
    std::vector<std::string> removedViewIds;
    while (startIter != endIter) {
        auto found = lastAccessedViewIds_.find(startIter->first);
        if (found == lastAccessedViewIds_.end()) {
            LOGD(" found abandoned view with id %{public}s", startIter->first.c_str());
            removedViewIds.emplace_back(startIter->first);
            startIter->second->Destroy(this);
            startIter->second.Reset();
        }
        ++startIter;
    }

    for (auto& viewId : removedViewIds) {
        customViewChildren_.erase(viewId);
    }

    lastAccessedViewIds_.clear();
}

JSRefPtr<JSView> JSView::GetChildById(const std::string& viewId)
{
    auto id = ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    auto found = customViewChildren_.find(id);
    if (found != customViewChildren_.end()) {
        ChildAccessedById(id);
        return found->second;
    }
    return JSRefPtr<JSView>();
}

void JSView::AddChildById(const std::string& viewId, const JSRefPtr<JSView>& obj)
{
    auto id = ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    customViewChildren_.emplace(id, obj);
    ChildAccessedById(id);
}

void JSView::ChildAccessedById(const std::string& viewId)
{
    lastAccessedViewIds_.emplace(viewId);
}

} // namespace OHOS::Ace::Framework
