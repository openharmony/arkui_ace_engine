/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_full_update_model.h"
#include "core/components_ng/base/view_full_update_model_ng.h"
#include "core/components_ng/base/view_partial_update_model.h"
#include "core/components_ng/base/view_partial_update_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/view_full_update_model_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/view_partial_update_model_impl.h"

namespace OHOS::Ace {

std::unique_ptr<ViewFullUpdateModel> ViewFullUpdateModel::instance_ = nullptr;
std::unique_ptr<ViewPartialUpdateModel> ViewPartialUpdateModel::instance_ = nullptr;

ViewFullUpdateModel* ViewFullUpdateModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ViewFullUpdateModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ViewFullUpdateModelNG());
        } else {
            instance_.reset(new Framework::ViewFullUpdateModelImpl());
        }
#endif
    }
    return instance_.get();
}

ViewPartialUpdateModel* ViewPartialUpdateModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ViewPartialUpdateModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ViewPartialUpdateModelNG());
        } else {
            instance_.reset(new Framework::ViewPartialUpdateModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSView::JSBind(BindingTarget object)
{
    JSViewPartialUpdate::JSBind(object);
    JSViewFullUpdate::JSBind(object);
}

void JSView::RenderJSExecution()
{
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    if (!jsViewFunction_) {
        LOGE("JSView: InternalRender jsViewFunction_ error");
        return;
    }
    {
        ACE_SCORING_EVENT("Component.AboutToRender");
        jsViewFunction_->ExecuteAboutToRender();
    }
    {
        ACE_SCORING_EVENT("Component.Build");
        ViewStackModel::GetInstance()->PushKey(viewId_);
        jsViewFunction_->ExecuteRender();
        ViewStackModel::GetInstance()->PopKey();
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

JSViewFullUpdate::JSViewFullUpdate(const std::string& viewId, JSRef<JSObject> jsObject, JSRef<JSFunc> jsRenderFunction)
{
    viewId_ = viewId;
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsObject, jsRenderFunction);
    LOGD("JSViewFullUpdate constructor");
}

JSViewFullUpdate::~JSViewFullUpdate()
{
    LOGD("JSViewFullUpdate destructor");
    jsViewFunction_.Reset();
};

RefPtr<AceType> JSViewFullUpdate::CreateViewNode()
{
    auto appearFunc = [weak = AceType::WeakClaim(this)] {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<AceType> {
        auto jsView = weak.Upgrade();
        return jsView ? jsView->InternalRender() : nullptr;
    };

    auto pageTransitionFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        if (!jsView || !jsView->jsViewFunction_) {
            return;
        }
        {
            ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Transition");
            jsView->jsViewFunction_->ExecuteTransition();
        }
    };

    auto updateViewNodeFunction = [weak = AceType::WeakClaim(this)](const RefPtr<AceType>& node) {
        auto jsView = weak.Upgrade();
        if (jsView) {
            jsView->viewNode_ = node;
        }
    };

    NodeInfo info = { .viewId = viewId_,
        .appearFunc = std::move(appearFunc),
        .renderFunc = std::move(renderFunction),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .pageTransitionFunc = std::move(pageTransitionFunction),
        .isStatic = IsStatic() };

    return ViewFullUpdateModel::GetInstance()->CreateNode(std::move(info));
}

RefPtr<AceType> JSViewFullUpdate::InternalRender()
{
    needsUpdate_ = false;
    RenderJSExecution();
    CleanUpAbandonedChild();
    jsViewFunction_->Destroy();
    return ViewStackModel::GetInstance()->Finish();
}

/**
 * marks the JSView's composed component as needing update / rerender
 */
void JSViewFullUpdate::MarkNeedUpdate()
{
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");
    needsUpdate_ = ViewFullUpdateModel::GetInstance()->MarkNeedUpdate(viewNode_);
}

void JSViewFullUpdate::Destroy(JSView* parentCustomView)
{
    LOGD("JSViewFullUpdate::Destroy start");
    DestroyChild(parentCustomView);
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Disappear");
        jsViewFunction_->ExecuteDisappear();
    }
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].AboutToBeDeleted");
        jsViewFunction_->ExecuteAboutToBeDeleted();
    }
    LOGD("JSViewFullUpdate::Destroy end");
}

void JSViewFullUpdate::Create(const JSCallbackInfo& info)
{
    LOGD("Creating new View for full update");
    ACE_DCHECK(!Container::IsCurrentUsePartialUpdate());

    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        auto* view = object->Unwrap<JSViewFullUpdate>();
        if (view == nullptr) {
            LOGE("JSView is null");
            return;
        }
        ViewStackModel::GetInstance()->Push(view->CreateViewNode(), true);
    } else {
        LOGE("JSView Object is expected.");
    }
}

void JSViewFullUpdate::JSBind(BindingTarget object)
{
    LOGD("JSViewFullUpdate::Bind");
    JSClass<JSViewFullUpdate>::Declare("NativeViewFullUpdate");
    JSClass<JSViewFullUpdate>::StaticMethod("create", &JSViewFullUpdate::Create);
    JSClass<JSViewFullUpdate>::Method("markNeedUpdate", &JSViewFullUpdate::MarkNeedUpdate);
    JSClass<JSViewFullUpdate>::Method("syncInstanceId", &JSViewFullUpdate::SyncInstanceId);
    JSClass<JSViewFullUpdate>::Method("restoreInstanceId", &JSViewFullUpdate::RestoreInstanceId);
    JSClass<JSViewFullUpdate>::Method("needsUpdate", &JSViewFullUpdate::NeedsUpdate);
    JSClass<JSViewFullUpdate>::Method("markStatic", &JSViewFullUpdate::MarkStatic);
    JSClass<JSViewFullUpdate>::CustomMethod("findChildById", &JSViewFullUpdate::FindChildById);
    JSClass<JSViewFullUpdate>::CustomMethod("findChildByIdForPreview", &JSViewFullUpdate::FindChildByIdForPreview);
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

void JSViewFullUpdate::FindChildByIdForPreview(const JSCallbackInfo& info)
{
    std::string viewId = info[0]->ToString();
    if (id_ == viewId) {
        info.SetReturnValue(this);
        return;
    }
    for (auto i : customViewChildren_) {
        std::string childId = i.first;
        auto pos = i.first.find_last_of('_');
        if (pos != std::string::npos) {
            childId = i.first.substr(pos + 1);
        }
        if (childId == viewId) {
            info.SetReturnValue(i.second);
            return;
        }
    }
    LOGE("find child failed %{public}s", viewId.c_str());
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
        LOGE("JSViewFullUpdate::DestructorCallback failed: the view is nullptr");
        return;
    }
    LOGD("JSViewFullUpdate(DestructorCallback) start: %{public}s", view->id_.c_str());
    view->DecRefCount();
    LOGD("JSViewFullUpdate(DestructorCallback) end");
}

void JSViewFullUpdate::DestroyChild(JSView* parentCustomView)
{
    LOGD("JSViewFullUpdate::DestroyChild start");
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
    LOGD("JSViewFullUpdate::DestroyChild end");
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

JSRef<JSObject> JSViewFullUpdate::GetChildById(const std::string& viewId)
{
    std::string id = ViewStackModel::GetInstance()->ProcessViewId(viewId);
    auto found = customViewChildren_.find(id);
    if (found != customViewChildren_.end()) {
        ChildAccessedById(id);
        return found->second;
    }
    auto lazyItem = customViewChildrenWithLazy_.find(id);
    if (lazyItem != customViewChildrenWithLazy_.end()) {
        return lazyItem->second;
    }
    return {};
}

std::string JSViewFullUpdate::AddChildById(const std::string& viewId, const JSRef<JSObject>& obj)
{
    std::string id = ViewStackModel::GetInstance()->ProcessViewId(viewId);
    JSView* jsView = nullptr;
    if (isLazyForEachProcessed_) {
        auto result = customViewChildrenWithLazy_.try_emplace(id, obj);
        if (!result.second) {
            jsView = result.first->second->Unwrap<JSView>();
            result.first->second = obj;
        } else {
            lazyItemGroups_[lazyItemGroupId_].emplace_back(id);
        }
    } else {
        auto result = customViewChildren_.try_emplace(id, obj);
        if (!result.second) {
            jsView = result.first->second->Unwrap<JSView>();
            result.first->second = obj;
        }
        ChildAccessedById(id);
    }
    if (jsView != nullptr) {
        jsView->Destroy(this);
    }
    return id;
}

void JSViewFullUpdate::RemoveChildGroupById(const std::string& viewId)
{
    // js runtime may be released
    CHECK_JAVASCRIPT_SCOPE_AND_RETURN;
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    LOGD("JSViewFullUpdate::RemoveChildGroupById in lazy for each case: %{public}s", viewId.c_str());
    auto iter = lazyItemGroups_.find(viewId);
    if (iter == lazyItemGroups_.end()) {
        LOGI("can not find this group to delete: %{public}s", viewId.c_str());
        return;
    }
    std::vector<std::string> removedViewIds;
    for (auto&& item : iter->second) {
        auto removeView = customViewChildrenWithLazy_.find(item);
        if (removeView != customViewChildrenWithLazy_.end()) {
            if (!removeView->second.IsEmpty()) {
                auto* view = removeView->second->Unwrap<JSView>();
                if (view != nullptr) {
                    view->Destroy(this);
                }
                removeView->second.Reset();
            }
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

// =================================================================

JSViewPartialUpdate::JSViewPartialUpdate(JSRef<JSObject> jsViewObject)
{
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsViewObject);
    LOGD("JSViewPartialUpdate constructor");
    // keep the reference to the JS View object to prevent GC
    jsViewObject_ = jsViewObject;
}

JSViewPartialUpdate::~JSViewPartialUpdate()
{
    LOGD("JSViewPartialUpdate destructor");
    jsViewFunction_.Reset();
};

RefPtr<AceType> JSViewPartialUpdate::CreateViewNode()
{
    auto updateViewIdFunc = [weak = AceType::WeakClaim(this)](const std::string viewId) {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->viewId_ = viewId;
    };

    auto appearFunc = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<AceType> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        if (!jsView->isFirstRender_) {
            LOGW("the js view has already called initial render");
            return nullptr;
        }
        jsView->isFirstRender_ = false;
        return jsView->InitialRender();
    };

    auto updateFunction = [weak = AceType::WeakClaim(this)]() -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        if (!jsView->needsUpdate_) {
            LOGW("the js view does not need to update");
            return;
        }
        jsView->needsUpdate_ = false;
        LOGD("Rerender function start for ComposedElement elmtId %{public}s - start...", jsView->viewId_.c_str());
        {
            ACE_SCOPED_TRACE("JSView: ExecuteRerender");
            jsView->jsViewFunction_->ExecuteRerender();
        }
        for (const UpdateTask& updateTask : jsView->pendingUpdateTasks_) {
            ViewPartialUpdateModel::GetInstance()->FlushUpdateTask(updateTask);
        }
        jsView->pendingUpdateTasks_.clear();
    };

    auto pageTransitionFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        if (!jsView || !jsView->jsViewFunction_) {
            return;
        }
        {
            ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Transition");
            jsView->jsViewFunction_->ExecuteTransition();
        }
    };

    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        LOGD("call remove view function");
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->Destroy(nullptr);
        jsView->viewNode_.Reset();
    };

    auto updateViewNodeFunction = [weak = AceType::WeakClaim(this)](const RefPtr<AceType>& node) {
        auto jsView = weak.Upgrade();
        if (jsView) {
            jsView->viewNode_ = node;
        }
    };

    NodeInfoPU info = { .appearFunc = std::move(appearFunc),
        .renderFunc = std::move(renderFunction),
        .updateFunc = std::move(updateFunction),
        .removeFunc = std::move(removeFunction),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .pageTransitionFunc = std::move(pageTransitionFunction),
        .hasMeasureOrLayout = jsViewFunction_->HasMeasure() || jsViewFunction_->HasLayout(),
        .isStatic = IsStatic() };

    auto measureFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteMeasure(layoutWrapper);
    };
    if (jsViewFunction_->HasMeasure()) {
        info.measureFunc = std::move(measureFunc);
    }

    auto layoutFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteLayout(layoutWrapper);
    };
    if (jsViewFunction_->HasLayout()) {
        info.layoutFunc = std::move(layoutFunc);
    }

    return ViewPartialUpdateModel::GetInstance()->CreateNode(std::move(info));
}

RefPtr<AceType> JSViewPartialUpdate::InitialRender()
{
    needsUpdate_ = false;
    RenderJSExecution();
    return ViewStackModel::GetInstance()->Finish();
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

void JSViewPartialUpdate::MarkNeedUpdate()
{
    needsUpdate_ = ViewPartialUpdateModel::GetInstance()->MarkNeedUpdate(viewNode_);
}

/**
 * in JS View.create(new View(...));
 * used for FullRender case, not for re-render case
 */
void JSViewPartialUpdate::Create(const JSCallbackInfo& info)
{
    LOGD("Creating new JSViewPartialUpdate for partial update");
    ACE_DCHECK(Container::IsCurrentUsePartialUpdate());

    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        auto* view = object->Unwrap<JSView>();
        if (view == nullptr) {
            LOGE("View is null");
            return;
        }
        ViewStackModel::GetInstance()->Push(view->CreateViewNode(), true);
    } else {
        LOGE("View Object is expected.");
    }
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

// ===========================================================
// partial update own functions start below
// ===========================================================

void JSViewPartialUpdate::JsFinishUpdateFunc(int32_t elmtId)
{
    ViewPartialUpdateModel::GetInstance()->FinishUpdate(
        viewNode_, elmtId, [weak = AceType::WeakClaim(this)](const UpdateTask& task) {
            auto jsView = weak.Upgrade();
            if (jsView) {
                jsView->pendingUpdateTasks_.push_back(task);
            }
        });
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

    // TODO: Check this return value
    auto result = false;

    // set boolean return value to JS
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

} // namespace OHOS::Ace::Framework
