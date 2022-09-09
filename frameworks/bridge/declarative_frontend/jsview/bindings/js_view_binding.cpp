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

#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "core/components_v2/common/element_proxy.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

void JSView::RenderJSExecution()
{
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    if (!jsViewFunction_) {
        LOGE("JSView: InternalRender jsViewFunction_ error");
    }
    {
        ACE_SCORING_EVENT("Component.AboutToRender");
        jsViewFunction_->ExecuteAboutToRender();
    }
    {
        ACE_SCORING_EVENT("Component.Build");
        jsViewFunction_->ExecuteRender();
    }
    {
        ACE_SCORING_EVENT("Component.OnRenderDone");
        jsViewFunction_->ExecuteOnRenderDone();
    }
}

void JSView::SyncInstanceId()
{
    restoreInstanceId_ = Container::CurrentId();
    ContainerScope::UpdateCurrent(instanceId_);
}

void JSView::RestoreInstanceId()
{
    ContainerScope::UpdateCurrent(restoreInstanceId_);
}

JSViewFullUpdate::JSViewFullUpdate(const std::string& viewId, JSRef<JSObject> jsObject,
    JSRef<JSFunc> jsRenderFunction) : viewId_(viewId)
{
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsObject, jsRenderFunction);
    LOGD("JSView constructor");
}

JSViewFullUpdate::~JSViewFullUpdate()
{
    LOGD("Destroy");
    jsViewFunction_.Reset();
};

void JSViewFullUpdate::Destroy(JSView* parentCustomView)
{
    LOGD("JSView::Destroy start");
    DestroyChild(parentCustomView);
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Disappear");
        jsViewFunction_->ExecuteDisappear();
    }
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].AboutToBeDeleted");
        jsViewFunction_->ExecuteAboutToBeDeleted();
    }
    LOGD("JSView::Destroy end");
}

void JSViewFullUpdate::JSBind(BindingTarget object)
{
    JSClass<JSViewFullUpdate>::Declare("NativeViewFullUpdate");
    JSClass<JSViewFullUpdate>::StaticMethod("create", &JSViewFullUpdate::Create);
    JSClass<JSViewFullUpdate>::Method("markNeedUpdate", &JSViewFullUpdate::MarkNeedUpdate);
    JSClass<JSViewFullUpdate>::Method("syncInstanceId", &JSViewFullUpdate::SyncInstanceId);
    JSClass<JSViewFullUpdate>::Method("restoreInstanceId", &JSViewFullUpdate::RestoreInstanceId);
    JSClass<JSViewFullUpdate>::Method("needsUpdate", &JSViewFullUpdate::NeedsUpdate);
    JSClass<JSViewFullUpdate>::Method("markStatic", &JSViewFullUpdate::MarkStatic);
    JSClass<JSViewFullUpdate>::CustomMethod("findChildById", &JSViewFullUpdate::FindChildById);
    JSClass<JSViewFullUpdate>::Inherit<JSViewAbstract>();
    JSClass<JSViewFullUpdate>::Bind(object, ConstructorCallback, DestructorCallback);
}

void JSViewFullUpdate::FindChildById(const JSCallbackInfo& info)
{
    LOGD("JSView::FindChildById");
    if (info[0]->IsNumber() || info[0]->IsString()) {
        std::string viewId = info[0]->ToString();
        info.SetReturnValue(GetChildById(viewId));
    } else {
        LOGE("JSView FindChildById with invalid arguments.");
        JSException::Throw("%s", "JSView FindChildById with invalid arguments.");
    }
}

void JSViewFullUpdate::ConstructorCallback(const JSCallbackInfo& info)
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
        auto instance = AceType::MakeRefPtr<JSViewFullUpdate>(viewId, info.This(), JSRef<JSFunc>::Cast(renderFunc));
        auto context = info.GetExecutionContext();
        instance->SetContext(context);
        instance->IncRefCount();
        info.SetReturnValue(AceType::RawPtr(instance));
        if (!info[1]->IsUndefined() && info[1]->IsObject()) {
            JSRef<JSObject> parentObj = JSRef<JSObject>::Cast(info[1]);
            auto* parentView = parentObj->Unwrap<JSViewFullUpdate>();
            if (parentView != nullptr) {
                auto id = parentView->AddChildById(viewId, info.This());
                instance->id_ = id;
            }
        }
        LOGD("JSView ConstructorCallback: %{public}s", instance->id_.c_str());
    } else {
        LOGE("JSView creation with invalid arguments.");
        JSException::Throw("%s", "JSView creation with invalid arguments.");
    }
}

void JSViewFullUpdate::DestructorCallback(JSViewFullUpdate* view)
{
    if (view == nullptr) {
        LOGE("DestructorCallback failed: the view is nullptr");
        return;
    }
    LOGD("JSView(DestructorCallback) start: %{public}s", view->id_.c_str());
    view->DecRefCount();
    LOGD("JSView(DestructorCallback) end");
}

void JSViewFullUpdate::DestroyChild(JSView* parentCustomView)
{
    LOGD("JSView::DestroyChild start");
    for (auto&& child : customViewChildren_) {
        auto* view = child.second->Unwrap<JSView>();
        if (view != nullptr) {
            view->Destroy(this);
        }
        child.second.Reset();
    }
    customViewChildren_.clear();
    for (auto&& lazyChild : customViewChildrenWithLazy_) {
        auto* view = lazyChild.second->Unwrap<JSView>();
        if (view != nullptr) {
            view->Destroy(this);
        }
        lazyChild.second.Reset();
    }
    customViewChildrenWithLazy_.clear();
    LOGD("JSView::DestroyChild end");
}

void JSViewFullUpdate::CleanUpAbandonedChild()
{
    auto startIter = customViewChildren_.begin();
    auto endIter = customViewChildren_.end();
    std::vector<std::string> removedViewIds;
    while (startIter != endIter) {
        auto found = lastAccessedViewIds_.find(startIter->first);
        if (found == lastAccessedViewIds_.end()) {
            LOGD(" found abandoned view with id %{public}s", startIter->first.c_str());
            removedViewIds.emplace_back(startIter->first);
            auto* view = startIter->second->Unwrap<JSView>();
            if (view != nullptr) {
                view->Destroy(this);
            }
            startIter->second.Reset();
        }
        ++startIter;
    }

    for (auto& viewId : removedViewIds) {
        customViewChildren_.erase(viewId);
    }

    lastAccessedViewIds_.clear();
}

void JSViewFullUpdate::RemoveChildGroupById(const std::string& viewId)
{
    // js runtime may be released
    CHECK_JAVASCRIPT_SCOPE_AND_RETURN;
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    LOGD("RemoveChildGroupById in lazy for each case: %{public}s", viewId.c_str());
    auto iter = lazyItemGroups_.find(viewId);
    if (iter == lazyItemGroups_.end()) {
        LOGI("can not find this group to delete: %{public}s", viewId.c_str());
        return;
    }
    std::vector<std::string> removedViewIds;
    for (auto&& item : iter->second) {
        auto removeView = customViewChildrenWithLazy_.find(item);
        if (removeView != customViewChildrenWithLazy_.end()) {
            auto* view = removeView->second->Unwrap<JSView>();
            if (view != nullptr) {
                view->Destroy(this);
            }
            removeView->second.Reset();
            removedViewIds.emplace_back(item);
        }
    }

    for (auto&& removeId : removedViewIds) {
        customViewChildrenWithLazy_.erase(removeId);
    }
    lazyItemGroups_.erase(iter);
}

void JSViewFullUpdate::ChildAccessedById(const std::string& viewId)
{
    lastAccessedViewIds_.emplace(viewId);
}

JSViewPartialUpdate::JSViewPartialUpdate(JSRef<JSObject> jsObject)
{
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsObject);
    LOGD("JSViewPartialUpdate constructor");
    // keep the reference to the JS View object to prevent GC
    jsViewObject_ = jsObject;
}

JSViewPartialUpdate::~JSViewPartialUpdate()
{
    LOGD("JSViewPartialUpdate destructor");
    jsViewFunction_.Reset();
};

RefPtr<Component> JSViewPartialUpdate::CreateComponent()
{
    return nullptr;
}

RefPtr<Component> JSViewPartialUpdate::InitialRender()
{
    return nullptr;
}

// parentCustomView in not used by PartialUpdate
void JSViewPartialUpdate::Destroy(JSView* parentCustomView)
{
    if (jsViewFunction_ == nullptr) {
        // already called Destroy before
        return;
    }

    LOGD("JSViewPartialUpdate::Destroy start");
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Disappear");
        jsViewFunction_->ExecuteDisappear();
    }
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].AboutToBeDeleted");
        jsViewFunction_->ExecuteAboutToBeDeleted();
    }
    jsViewFunction_->Destroy();
    jsViewFunction_.Reset();

    // release reference to JS view object, and allow GC, calls DestructorCallback
    jsViewObject_.Reset();
    LOGD("JSViewPartialUpdate::Destroy end");
}


void JSViewPartialUpdate::JSBind(BindingTarget object)
{
    LOGD("JSViewPartialUpdate::Bind");
    JSClass<JSViewPartialUpdate>::Declare("NativeViewPartialUpdate");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSViewPartialUpdate>::StaticMethod("create", &JSViewPartialUpdate::Create, opt);
    JSClass<JSViewPartialUpdate>::Method("markNeedUpdate", &JSViewPartialUpdate::MarkNeedUpdate);
    JSClass<JSViewPartialUpdate>::Method("syncInstanceId", &JSViewPartialUpdate::SyncInstanceId);
    JSClass<JSViewPartialUpdate>::Method("restoreInstanceId", &JSViewPartialUpdate::RestoreInstanceId);
    JSClass<JSViewPartialUpdate>::Method("markStatic", &JSViewPartialUpdate::MarkStatic);
    JSClass<JSViewPartialUpdate>::Method("finishUpdateFunc", &JSViewPartialUpdate::JsFinishUpdateFunc);
    JSClass<JSViewPartialUpdate>::CustomMethod("getDeletedElemtIds", &JSViewPartialUpdate::JsGetDeletedElemtIds);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "deletedElmtIdsHaveBeenPurged", &JSViewPartialUpdate::JsDeletedElmtIdsHaveBeenPurged);
    JSClass<JSViewPartialUpdate>::Method("elmtIdExists", &JSViewPartialUpdate::JsElementIdExists);
    JSClass<JSViewPartialUpdate>::CustomMethod("isLazyItemRender", &JSViewPartialUpdate::JSGetProxiedItemRenderState);
    JSClass<JSViewPartialUpdate>::Inherit<JSViewAbstract>();
    JSClass<JSViewPartialUpdate>::Bind(object, ConstructorCallback, DestructorCallback);
}

void JSViewPartialUpdate::ConstructorCallback(const JSCallbackInfo& info)
{
    LOGD("creating C++ and JS View Objects ...");
    JSRef<JSObject> thisObj = info.This();
    auto* instance = new JSViewPartialUpdate(thisObj);

    auto context = info.GetExecutionContext();
    instance->SetContext(context);

    //  The JS object owns the C++ object:
    // make sure the C++ is not destroyed when RefPtr thisObj goes out of scope
    // JSView::DestructorCallback has view->DecRefCount()
    instance->IncRefCount();

    info.SetReturnValue(instance);
}

void JSViewPartialUpdate::DestructorCallback(JSViewPartialUpdate* view)
{
    if (view == nullptr) {
        LOGE("JSViewPartialUpdate::DestructorCallback failed: the view is nullptr");
        return;
    }
    LOGD("JSViewPartialUpdate(DestructorCallback) start");
    view->DecRefCount();
    LOGD("JSViewPartialUpdate(DestructorCallback) end");
}



void JSViewPartialUpdate::JsGetDeletedElemtIds(const JSCallbackInfo& info)
{
    LOGD("JSView, getting elmtIds of all deleted Elements from ElementRegister:");

    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[0]);
    std::unordered_set<int32_t>& removedElements = ElementRegister::GetInstance()->GetRemovedItems();
    size_t index = jsArr->Length();
    for (const auto& rmElmtId : removedElements) {
        LOGD("  array removed elmtId %{public}d", rmElmtId);
        JSRef<JSVal> jsRmElmtId = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(rmElmtId)));
        jsArr->SetValueAt(index++, jsRmElmtId);
    }
}

void JSViewPartialUpdate::JsDeletedElmtIdsHaveBeenPurged(const JSCallbackInfo& info)
{
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[0]);
    for (size_t i = 0; i < jsArr->Length(); i++) {
        const JSRef<JSVal> strId = jsArr->GetValueAt(i);
        ElementRegister::GetInstance()->ClearRemovedItems(strId->ToNumber<int32_t>());
    }
}

void JSViewPartialUpdate::MakeElementUpdatesToCompleteRerender()
{
    ACE_SCOPED_TRACE("JSView::MakeElementUpdatesToCompleteRerender");

    LOGD("Component to Element %{public}d localized updates to do - start ....",
        static_cast<int32_t>(pendingElementUpdates_.size()));
    // process all pending localized element update tasks from queue
    for (const UpdateFuncResult& updateFuncResult : pendingElementUpdates_) {
        ComponentToElementLocalizedUpdate(updateFuncResult);
    }
    pendingElementUpdates_.clear();
    LOGD("Component to Element localized updates - done");
}

bool JSViewPartialUpdate::JsElementIdExists(int32_t elmtId)
{
    return ElementRegister::GetInstance()->Exists(elmtId);
}

void JSViewPartialUpdate::JSGetProxiedItemRenderState(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        LOGE("JSView::JSGetProxiedItemRenderState. elmtId parameter expected");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    const auto elmtId = info[0]->ToNumber<int32_t>();

    if (elmtId == ElementRegister::UndefinedElementId) {
        LOGE("JSView::JSGetProxiedItemRenderState. elmtId must not be undefined");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }

    // ElementRegister get Proxy
    auto result = false;
    auto proxy = ElementRegister::GetInstance()->GetElementProxyById(elmtId);
    if (proxy != nullptr) {
        // Get Proxy render status
        // only Grid/ListItemElementProxy can be in shallow==lazy render state
        // other proxies always return false
        result = false;
    }

    // set boolean return value to JS
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

} // namespace OHOS::Ace::Framework
