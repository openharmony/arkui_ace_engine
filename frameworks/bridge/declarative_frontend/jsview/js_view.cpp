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

#include "bridge/declarative_frontend/jsview/js_view.h"

#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "bridge/declarative_frontend/jsview/models/view_full_update_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/view_partial_update_model_impl.h"
#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/layout_inspector.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_full_update_model.h"
#include "core/components_ng/base/view_full_update_model_ng.h"
#include "core/components_ng/base/view_partial_update_model.h"
#include "core/components_ng/base/view_partial_update_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/recycle_view/recycle_dummy_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "interfaces/napi/kits/promptaction/prompt_controller.h"

namespace OHOS::Ace {

std::unique_ptr<ViewFullUpdateModel> ViewFullUpdateModel::instance_ = nullptr;
std::mutex ViewFullUpdateModel::mutex_;

ViewFullUpdateModel* ViewFullUpdateModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
    }
    return instance_.get();
}

ViewPartialUpdateModel* ViewPartialUpdateModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ViewPartialUpdateModelNG instance;
    return &instance;
#else
  if (Container::IsCurrentUseNewPipeline()) {
      static NG::ViewPartialUpdateModelNG instance;
      return &instance;
  } else {
      static Framework::ViewPartialUpdateModelImpl instance;
      return &instance;
  }
#endif
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
        return;
    }
    {
        ACE_SCORING_EVENT("Component.AboutToRender");
        jsViewFunction_->ExecuteAboutToRender();
    }
    if (!jsViewFunction_) {
        return;
    }
    {
        ACE_SCORING_EVENT("Component.Build");
        ViewStackModel::GetInstance()->PushKey(viewId_);
        jsViewFunction_->ExecuteRender();
        ViewStackModel::GetInstance()->PopKey();
    }
    if (!jsViewFunction_) {
        return;
    }
    {
        ACE_SCORING_EVENT("Component.OnRenderDone");
        jsViewFunction_->ExecuteOnRenderDone();
        if (notifyRenderDone_) {
            notifyRenderDone_();
        }
    }
}

void JSView::SyncInstanceId()
{
    if (primaryStackSize_ >= PRIMARY_ID_STACK_SIZE) {
        restoreInstanceIdStack_.emplace_back(Container::CurrentId());
    } else {
        primaryIdStack_[primaryStackSize_++] = Container::CurrentId();
    }
    ContainerScope::UpdateCurrent(instanceId_);
}

void JSView::RestoreInstanceId()
{
    if (primaryStackSize_ >= PRIMARY_ID_STACK_SIZE && !restoreInstanceIdStack_.empty()) {
        // Checking primaryStackSize_ is necessary, because the pointer in restoreInstanceIdStack_ may be corrupted.
        ContainerScope::UpdateCurrent(restoreInstanceIdStack_.back());
        restoreInstanceIdStack_.pop_back();
        return;
    }
    if (primaryStackSize_ == 0) {
        ContainerScope::UpdateCurrent(-1);
        return;
    }
    ContainerScope::UpdateCurrent(primaryIdStack_[--primaryStackSize_]);
}

void JSView::GetInstanceId(const JSCallbackInfo& info)
{
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(instanceId_)));
}

void JSView::JsSetCardId(int64_t cardId)
{
    cardId_ = cardId;
}

void JSView::JsGetCardId(const JSCallbackInfo& info)
{
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(cardId_)));
}


JSViewFullUpdate::JSViewFullUpdate(const std::string& viewId, JSRef<JSObject> jsObject, JSRef<JSFunc> jsRenderFunction)
{
    viewId_ = viewId;
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsObject, jsRenderFunction);
    jsViewObject_ = jsObject;
}

JSViewFullUpdate::~JSViewFullUpdate()
{
    jsViewFunction_.Reset();
};

RefPtr<AceType> JSViewFullUpdate::CreateViewNode(bool isTitleNode, bool isCustomAppBar)
{
    auto appearFunc = [weak = AceType::WeakClaim(this)] {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->viewNode_.Invalid() && jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<AceType> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        ContainerScope scope(jsView->GetInstanceId());
        return jsView->InternalRender();
    };

    auto pageTransitionFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        if (!jsView || !jsView->jsViewFunction_) {
            return;
        }
        {
            ContainerScope scope(jsView->GetInstanceId());
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

    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        auto jsView = weak.Upgrade();
        if (jsView && jsView->jsViewFunction_) {
            ContainerScope scope(jsView->GetInstanceId());
            jsView->jsViewFunction_->ExecuteDisappear();
        }
    };

    NodeInfo info = { .viewId = viewId_,
        .appearFunc = std::move(appearFunc),
        .renderFunc = std::move(renderFunction),
        .removeFunc = std::move(removeFunction),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .isStatic = IsStatic() };

    if (jsViewFunction_ && jsViewFunction_->HasPageTransition()) {
        info.pageTransitionFunc = std::move(pageTransitionFunction);
    }

    return ViewFullUpdateModel::GetInstance()->CreateNode(std::move(info));
}

RefPtr<AceType> JSViewFullUpdate::InternalRender()
{
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
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
    DestroyChild(parentCustomView);
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Disappear");
        jsViewFunction_->ExecuteDisappear();
    }
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].AboutToBeDeleted");
        jsViewFunction_->ExecuteAboutToBeDeleted();
    }
    jsViewObject_.Reset();
}

void JSViewFullUpdate::Create(const JSCallbackInfo& info)
{
    ACE_DCHECK(!Container::IsCurrentUsePartialUpdate());

    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        auto* view = object->Unwrap<JSViewFullUpdate>();
        if (view == nullptr) {
            return;
        }
        ViewStackModel::GetInstance()->Push(view->CreateViewNode(), true);
    }
}

void JSViewFullUpdate::JSBind(BindingTarget object)
{
    JSClass<JSViewFullUpdate>::Declare("NativeViewFullUpdate");
    JSClass<JSViewFullUpdate>::StaticMethod("create", &JSViewFullUpdate::Create);
    JSClass<JSViewFullUpdate>::Method("markNeedUpdate", &JSViewFullUpdate::MarkNeedUpdate);
    JSClass<JSViewFullUpdate>::Method("syncInstanceId", &JSViewFullUpdate::SyncInstanceId);
    JSClass<JSViewFullUpdate>::Method("restoreInstanceId", &JSViewFullUpdate::RestoreInstanceId);
    JSClass<JSViewFullUpdate>::CustomMethod("getInstanceId", &JSViewFullUpdate::GetInstanceId);
    JSClass<JSViewFullUpdate>::Method("needsUpdate", &JSViewFullUpdate::NeedsUpdate);
    JSClass<JSViewFullUpdate>::Method("markStatic", &JSViewFullUpdate::MarkStatic);
    JSClass<JSViewFullUpdate>::Method("setCardId", &JSViewFullUpdate::JsSetCardId);
    JSClass<JSViewFullUpdate>::CustomMethod("getCardId", &JSViewFullUpdate::JsGetCardId);
    JSClass<JSViewFullUpdate>::CustomMethod("findChildById", &JSViewFullUpdate::FindChildById);
    JSClass<JSViewFullUpdate>::CustomMethod("findChildByIdForPreview", &JSViewFullUpdate::FindChildByIdForPreview);
    JSClass<JSViewFullUpdate>::InheritAndBind<JSViewAbstract>(object, ConstructorCallback, DestructorCallback);
}

void JSViewFullUpdate::FindChildById(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber() || info[0]->IsString()) {
        std::string viewId = info[0]->ToString();
        info.SetReturnValue(GetChildById(viewId));
    } else {
        JSException::Throw("%s", "JSView FindChildById with invalid arguments.");
    }
}

void JSViewFullUpdate::FindChildByIdForPreview(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        return;
    }
    std::string viewId = std::to_string(info[0]->ToNumber<int32_t>());
    if (viewId_ == viewId) {
        info.SetReturnValue(jsViewObject_);
        return;
    }
    JSRef<JSObject> targetView = JSRef<JSObject>::New();
    for (auto&& child : customViewChildren_) {
        if (GetChildByViewId(viewId, child.second, targetView)) {
            break;
        }
    }
    auto view = targetView->Unwrap<JSViewFullUpdate>();
    if (view) {
        info.SetReturnValue(targetView);
    }
    return;
}

bool JSViewFullUpdate::GetChildByViewId(
    const std::string& viewId, JSRef<JSObject>& childView, JSRef<JSObject>& targetView)
{
    auto* view = childView->Unwrap<JSViewFullUpdate>();
    CHECK_NULL_RETURN(view, false);
    if (view->viewId_ == viewId) {
        targetView = childView;
        return true;
    }
    for (auto&& child : view->customViewChildren_) {
        if (GetChildByViewId(viewId, child.second, targetView)) {
            return true;
        }
    }
    return false;
}

void JSViewFullUpdate::ConstructorCallback(const JSCallbackInfo& info)
{
    JSRef<JSObject> thisObj = info.This();
    JSRef<JSVal> renderFunc = thisObj->GetProperty("render");
    if (!renderFunc->IsFunction()) {
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
    } else {
        JSException::Throw("%s", "JSView creation with invalid arguments.");
    }
}

void JSViewFullUpdate::DestructorCallback(JSViewFullUpdate* view)
{
    if (view == nullptr) {
        return;
    }
    view->DecRefCount();
}

void JSViewFullUpdate::DestroyChild(JSView* parentCustomView)
{
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
}

void JSViewFullUpdate::CleanUpAbandonedChild()
{
    auto startIter = customViewChildren_.begin();
    auto endIter = customViewChildren_.end();
    std::vector<std::string> removedViewIds;
    while (startIter != endIter) {
        auto found = lastAccessedViewIds_.find(startIter->first);
        if (found == lastAccessedViewIds_.end()) {
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
    auto iter = lazyItemGroups_.find(viewId);
    if (iter == lazyItemGroups_.end()) {
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

std::map<std::string, JSRef<JSObject>> JSViewStackProcessor::viewMap_;

JSViewPartialUpdate::JSViewPartialUpdate(JSRef<JSObject> jsViewObject)
{
    jsViewFunction_ = AceType::MakeRefPtr<ViewFunctions>(jsViewObject);
    // keep the reference to the JS View object to prevent GC
    jsViewObject_ = jsViewObject;
}

JSViewPartialUpdate::~JSViewPartialUpdate()
{
    jsViewFunction_.Reset();
};

RefPtr<AceType> JSViewPartialUpdate::CreateViewNode(bool isTitleNode, bool isCustomAppBar)
{
    auto updateViewIdFunc = [weak = AceType::WeakClaim(this)](const std::string& viewId) {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->viewId_ = viewId;
    };

    auto appearFunc = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };

    auto didBuildFunc = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteDidBuild();
        }
    };

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<AceType> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        ContainerScope scope(jsView->GetInstanceId());
        if (!jsView->isFirstRender_) {
            return nullptr;
        }
        jsView->isFirstRender_ = false;
        return jsView->InitialRender();
    };

    auto updateFunction = [weak = AceType::WeakClaim(this)]() -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        if (!jsView->needsUpdate_) {
            return;
        }
        jsView->needsUpdate_ = false;
        {
            ACE_SCOPED_TRACE("JSView: ExecuteRerender");
            jsView->jsViewFunction_->ExecuteRerender();
        }
        for (const UpdateTask& updateTask : jsView->pendingUpdateTasks_) {
            ViewPartialUpdateModel::GetInstance()->FlushUpdateTask(updateTask);
        }
        jsView->pendingUpdateTasks_.clear();
    };

    auto reloadFunction = [weak = AceType::WeakClaim(this)](bool deep) {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteReload(deep);
    };

    // @Component level complete reload, can detect added/deleted frame nodes
    auto completeReloadFunc = [weak = AceType::WeakClaim(this)]() -> RefPtr<AceType> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        ContainerScope scope(jsView->GetInstanceId());
        return jsView->InitialRender();
    };

    auto pageTransitionFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        {
            ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Transition");
            jsView->jsViewFunction_->ExecuteTransition();
        }
    };

    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->Destroy(nullptr);
        jsView->viewNode_.Reset();
    };

    auto updateViewNodeFunction = [weak = AceType::WeakClaim(this)](const RefPtr<AceType>& node) {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->viewNode_ = node;
    };

    auto nodeUpdateFunc = [weak = AceType::WeakClaim(this)](int32_t nodeId) {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteForceNodeRerender(nodeId);
    };

    auto hasNodeUpdateFunc = [weak = AceType::WeakClaim(this)](int32_t nodeId) -> bool {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, false);
        CHECK_NULL_RETURN(jsView->jsViewFunction_, false);
        ContainerScope scope(jsView->GetInstanceId());
        return jsView->jsViewFunction_->ExecuteHasNodeUpdateFunc(nodeId);
    };

    auto recycleCustomNode = [weak = AceType::WeakClaim(this)](const RefPtr<NG::CustomNodeBase>& recycleNode) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        auto name = jsView->GetRecycleCustomNodeName();
        if (name.empty()) {
            return;
        }
        auto recycleUINode = AceType::DynamicCast<NG::UINode>(recycleNode);
        recycleUINode->SetActive(false);
        jsView->SetRecycleCustomNode(recycleNode);
        jsView->jsViewFunction_->ExecuteRecycle(jsView->GetRecycleCustomNodeName());
        if (!recycleNode->HasRecycleRenderFunc() && jsView->recycleCustomNode_) {
            recycleUINode->SetJSViewActive(false, false, true);
            jsView->jsViewFunction_->ExecuteAboutToRecycle();
        }
        recycleNode->ResetRecycle();
    };

    auto setActiveFunc = [weak = AceType::WeakClaim(this)](bool active, bool isReuse = false) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        jsView->jsViewFunction_->ExecuteSetActive(active, isReuse);
    };

    auto onDumpInfoFunc = [weak = AceType::WeakClaim(this)](const std::vector<std::string>& params) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteOnDumpInfo(params);
    };

    auto onDumpInspectorFunc = [weak = AceType::WeakClaim(this)]() -> std::string {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, "");
        ContainerScope scope(jsView->GetInstanceId());
        return jsView->jsViewFunction_->ExecuteOnDumpInfo();
    };

    auto getThisFunc = [weak = AceType::WeakClaim(this)]() -> void* {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        ContainerScope scope(jsView->GetInstanceId());
        return (void*)&(jsView->jsViewObject_);
    };

    auto recycleFunc = [weak = AceType::WeakClaim(this)]() -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteAboutToRecycle();
    };

    auto reuseFunc = [weak = AceType::WeakClaim(this)](void* params) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        CHECK_NULL_VOID(jsView->jsViewFunction_);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteAboutToReuse(params);
    };

    NodeInfoPU info = { .appearFunc = std::move(appearFunc),
        .didBuildFunc = std::move(didBuildFunc),
        .renderFunc = std::move(renderFunction),
        .updateFunc = std::move(updateFunction),
        .removeFunc = std::move(removeFunction),
        .updateNodeFunc = std::move(updateViewNodeFunction),
        .pageTransitionFunc = std::move(pageTransitionFunction),
        .reloadFunc = std::move(reloadFunction),
        .completeReloadFunc = std::move(completeReloadFunc),
        .nodeUpdateFunc = std::move(nodeUpdateFunc),
        .hasNodeUpdateFunc = std::move(hasNodeUpdateFunc),
        .recycleCustomNodeFunc = recycleCustomNode,
        .setActiveFunc = std::move(setActiveFunc),
        .onDumpInfoFunc = std::move(onDumpInfoFunc),
        .onDumpInspectorFunc = std::move(onDumpInspectorFunc),
        .getThisFunc = std::move(getThisFunc),
        .recycleFunc = std::move(recycleFunc),
        .reuseFunc = std::move(reuseFunc),
        .hasMeasureOrLayout = jsViewFunction_->HasMeasure() || jsViewFunction_->HasLayout() ||
                              jsViewFunction_->HasMeasureSize() || jsViewFunction_->HasPlaceChildren(),
        .isStatic = IsStatic(),
        .jsViewName = GetJSViewName(),
        .isV2 = GetJSIsV2() };

    auto measureFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteMeasure(layoutWrapper);
    };
    if (jsViewFunction_->HasMeasure()) {
        info.measureFunc = std::move(measureFunc);
    }

    auto layoutFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ContainerScope scope(jsView->GetInstanceId());
        jsView->jsViewFunction_->ExecuteLayout(layoutWrapper);
    };
    if (jsViewFunction_->HasLayout()) {
        info.layoutFunc = std::move(layoutFunc);
    }

    if (jsViewFunction_->HasMeasureSize()) {
        auto measureSizeFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
            auto jsView = weak.Upgrade();
            CHECK_NULL_VOID(jsView);
            ContainerScope scope(jsView->GetInstanceId());
            jsView->jsViewFunction_->ExecuteMeasureSize(layoutWrapper);
        };
        info.measureSizeFunc = std::move(measureSizeFunc);
    }

    if (jsViewFunction_->HasPlaceChildren()) {
        auto placeChildren = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
            auto jsView = weak.Upgrade();
            CHECK_NULL_VOID(jsView);
            ContainerScope scope(jsView->GetInstanceId());
            jsView->jsViewFunction_->ExecutePlaceChildren(layoutWrapper);
        };
        info.placeChildrenFunc = std::move(placeChildren);
    }

    JSRef<JSObject> jsViewExtraInfo = jsViewObject_->GetProperty("extraInfo_");
    if (!jsViewExtraInfo->IsUndefined()) {
        JSRef<JSVal> jsPage = jsViewExtraInfo->GetProperty("page");
        JSRef<JSVal> jsLine = jsViewExtraInfo->GetProperty("line");
        JSRef<JSVal> jsColumn = jsViewExtraInfo->GetProperty("col");
        info.extraInfo = {.page = jsPage->ToString(), .line = jsLine->ToNumber<int32_t>(),
            .col = jsColumn->ToNumber<int32_t>()};
    }
    
    if (isTitleNode) {
        info.isCustomTitle = true;
    }

    if (isCustomAppBar) {
        info.isCustomAppBar = true;
    }
    auto node = ViewPartialUpdateModel::GetInstance()->CreateNode(std::move(info));
    auto customMeasureLayoutNode = DynamicCast<NG::CustomMeasureLayoutNode>(node);
    if (customMeasureLayoutNode) {
        auto updateParamFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
            auto jsView = weak.Upgrade();
            CHECK_NULL_VOID(jsView);
            ContainerScope scope(jsView->GetInstanceId());
            jsView->jsViewFunction_->InitJsParam(layoutWrapper);
        };
        customMeasureLayoutNode->SetUpdateParamFunc(updateParamFunc);
    }
#ifdef PREVIEW
    auto uiNode = AceType::DynamicCast<NG::UINode>(node);
    if (uiNode) {
        Framework::JSViewStackProcessor::SetViewMap(std::to_string(uiNode->GetId()), jsViewObject_);
    }
#endif

    if (AceChecker::IsPerformanceCheckEnabled()) {
        auto uiNode = AceType::DynamicCast<NG::UINode>(node);
        if (uiNode) {
            auto codeInfo = EngineHelper::GetPositionOnJsCode();
            uiNode->SetRow(codeInfo.first);
            uiNode->SetCol(codeInfo.second);
        }
    }
    return node;
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
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Disappear");
        jsViewFunction_->ExecuteDisappear();
    }
    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].AboutToBeDeleted");
        jsViewFunction_->ExecuteAboutToBeDeleted();
    }
    pendingUpdateTasks_.clear();
    jsViewFunction_->Destroy();
    jsViewFunction_.Reset();

    // release reference to JS view object, and allow GC, calls DestructorCallback
    jsViewObject_.Reset();
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
    ACE_DCHECK(Container::IsCurrentUsePartialUpdate());

    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        auto* view = object->Unwrap<JSView>();
        if (view == nullptr) {
            LOGE("View is null");
            return;
        }
        ViewStackModel::GetInstance()->Push(view->CreateViewNode(), true);
    }
}

enum {
    PARAM_VIEW_OBJ = 0,
    PARAM_IS_RECYCLE,
    PARAM_NODE_NAME,
    PARAM_RECYCLE_UPDATE_FUNC,

    PARAM_SIZE,
};

bool ParseRecycleParams(const JSCallbackInfo& info, JSRef<JSVal> (&params)[PARAM_SIZE])
{
    if (info.Length() != PARAM_SIZE) {
        return false;
    }
    if (!info[PARAM_VIEW_OBJ]->IsObject()) {
        return false;
    }
    if (!info[PARAM_IS_RECYCLE]->IsBoolean()) {
        return false;
    }
    if (!info[PARAM_RECYCLE_UPDATE_FUNC]->IsFunction()) {
        return false;
    }

    for (int32_t idx = PARAM_VIEW_OBJ; idx < PARAM_SIZE; ++idx) {
        params[idx] = info[idx];
    }
    return true;
}

/**
 * in JS ViewPU.createRecycle(...)
 * create a recyclable custom node
 */
void JSViewPartialUpdate::CreateRecycle(const JSCallbackInfo& info)
{
    ACE_DCHECK(Container::IsCurrentUsePartialUpdate());

    JSRef<JSVal> params[PARAM_SIZE];
    if (!ParseRecycleParams(info, params)) {
        return;
    }

    auto viewObj = JSRef<JSObject>::Cast(params[PARAM_VIEW_OBJ]);
    auto* view = viewObj->Unwrap<JSViewPartialUpdate>();
    if (!view) {
        return;
    }
    if (info[PARAM_NODE_NAME]->IsUndefined()) {
        view->SetRecycleCustomNodeName("");
        ViewStackModel::GetInstance()->Push(view->CreateViewNode(), true);
        return;
    }
    auto recycle = params[PARAM_IS_RECYCLE]->ToBoolean();
    auto nodeName = params[PARAM_NODE_NAME]->ToString();
    auto jsRecycleUpdateFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(params[PARAM_RECYCLE_UPDATE_FUNC]));
    auto recycleUpdateFunc = [weak = AceType::WeakClaim(view), execCtx = info.GetExecutionContext(),
                                 func = std::move(jsRecycleUpdateFunc)]() -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->SetIsRecycleRerender(true);
        func->ExecuteJS();
        jsView->SetIsRecycleRerender(false);
    };

    // update view and node property
    view->SetRecycleCustomNodeName(nodeName);

    RefPtr<AceType> node;

    // get or create recycle node
    if (recycle) {
        node = view->GetCachedRecycleNode();
        AceType::DynamicCast<NG::CustomNodeBase>(node)->SetRecycleRenderFunc(std::move(recycleUpdateFunc));
    } else {
        node = view->CreateViewNode();
    }
    auto* stack = NG::ViewStackProcessor::GetInstance();
    auto dummyNode = NG::RecycleDummyNode::WrapRecycleDummyNode(node, stack->GetRecycleNodeId());
    ViewStackModel::GetInstance()->Push(dummyNode, true);
}

void JSViewPartialUpdate::OnDumpInfo(const std::vector<std::string>& params)
{
    CHECK_NULL_VOID(jsViewFunction_);
    jsViewFunction_->ExecuteOnDumpInfo(params);
}

void JSViewPartialUpdate::JSGetNavDestinationInfo(const JSCallbackInfo& info)
{
    std::shared_ptr<OHOS::Ace::NG::NavDestinationInfo> result;
    if (info[0]->IsBoolean()) {
        if (info[0]->ToBoolean()) {
            result = NG::UIObserverHandler::GetInstance().GetNavigationInnerState(GetViewNode());
        } else {
            result = NG::UIObserverHandler::GetInstance().GetNavigationOuterState(GetViewNode());
        }
    } else {
        result = NG::UIObserverHandler::GetInstance().GetNavigationState(GetViewNode());
    }
    if (result) {
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        obj->SetProperty<std::string>("navigationId", result->navigationId);
        obj->SetProperty<std::string>("name", result->name);
        obj->SetProperty<int32_t>("state", static_cast<int32_t>(result->state));
        obj->SetProperty<int32_t>("index", result->index);
        obj->SetPropertyObject("param", JsConverter::ConvertNapiValueToJsVal(result->param));
        obj->SetProperty<std::string>("navDestinationId", result->navDestinationId);
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            obj->SetProperty<int32_t>("mode", static_cast<int32_t>(result->mode));
            obj->SetProperty<std::string>("uniqueId", result->uniqueId);
        }
        info.SetReturnValue(obj);
    }
}

void JSViewPartialUpdate::JSGetRouterPageInfo(const JSCallbackInfo& info)
{
    auto result = NG::UIObserverHandler::GetInstance().GetRouterPageState(GetViewNode());
    if (result) {
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        auto jsContext = JsConverter::ConvertNapiValueToJsVal(result->context);
        obj->SetPropertyObject("context", jsContext);
        obj->SetProperty<int32_t>("index", result->index);
        obj->SetProperty<std::string>("name", result->name);
        obj->SetProperty<std::string>("path", result->path);
        obj->SetProperty<int32_t>("state", static_cast<int32_t>(result->state));
        obj->SetProperty<std::string>("pageId", result->pageId);
        info.SetReturnValue(obj);
    }
}

void JSViewPartialUpdate::JSGetNavigationInfo(const JSCallbackInfo& info)
{
    ContainerScope scope(GetInstanceId());
    auto node = AceType::DynamicCast<NG::UINode>(this->GetViewNode());
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_VOID(navigationMgr);
    auto result = navigationMgr->GetNavigationInfo(GetViewNode());
    CHECK_NULL_VOID(result);
    auto stack = result->pathStack.Upgrade();
    CHECK_NULL_VOID(stack);
    auto jsStack = AceType::DynamicCast<JSNavigationStack>(stack);
    CHECK_NULL_VOID(jsStack);
    auto navPathStackObj = jsStack->GetDataSourceObj();
    CHECK_NULL_VOID(!navPathStackObj->IsEmpty());
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty<std::string>("navigationId", result->navigationId);
    obj->SetPropertyObject("pathStack", navPathStackObj);
    info.SetReturnValue(obj);
}

void JSViewPartialUpdate::JSGetUIContext(const JSCallbackInfo& info)
{
    ContainerScope scope(GetInstanceId());
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto frontend = container->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto context = frontend->GetContextValue();
    auto jsVal = JsConverter::ConvertNapiValueToJsVal(context);
    info.SetReturnValue(jsVal);
}

void JSViewPartialUpdate::JSGetUniqueId(const JSCallbackInfo& info)
{
    auto node = AceType::DynamicCast<NG::UINode>(this->GetViewNode());
    auto nodeId = -1;
    if (node) {
        nodeId = node->GetId();
    }
    
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(nodeId)));
}

void JSViewPartialUpdate::JSSendStateInfo(const std::string& stateInfo)
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    return;
#else
    if (!LayoutInspector::GetStateProfilerStatus()) {
        return;
    }
    ContainerScope scope(GetInstanceId());
    auto node = AceType::DynamicCast<NG::UINode>(this->GetViewNode());
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);

    auto info = JsonUtil::ParseJsonString(stateInfo);
    info->Put("timeStamp", GetCurrentTimestampMicroSecond());
    info->Put("vsyncID", (int32_t)pipeline->GetFrameCount());
    info->Put("processID", getpid());
    info->Put("windowID", (int32_t)pipeline->GetWindowId());
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI SendStateInfo %{public}s", info->ToString().c_str());
    LayoutInspector::SendStateProfilerMessage(info->ToString());
#endif
}

void JSViewPartialUpdate::JSSetIsV2(const bool isV2)
{
    isV2_ = isV2;
}

napi_value GetDialogController(napi_env env)
{
    napi_value globalValue = nullptr;
    napi_get_global(env, &globalValue);
    CHECK_NULL_RETURN(globalValue, nullptr);
    napi_value func = nullptr;
    napi_get_named_property(env, globalValue, "requireNapi", &func);
    CHECK_NULL_RETURN(func, nullptr);
    napi_value module = nullptr;
    napi_create_string_utf8(env, "promptAction", NAPI_AUTO_LENGTH, &module);
    CHECK_NULL_RETURN(module, nullptr);
    napi_value returnValue = nullptr;
    napi_call_function(env, globalValue, func, 1, &module, &returnValue);
    CHECK_NULL_RETURN(returnValue, nullptr);
    napi_value constructor = nullptr;
    napi_get_named_property(env, returnValue, "DialogController", &constructor);
    CHECK_NULL_RETURN(constructor, nullptr);
    napi_value result = nullptr;
    napi_new_instance(env, constructor, 0, nullptr, &result);
    CHECK_NULL_RETURN(result, nullptr);
    return result;
}

void JSViewPartialUpdate::JSGetDialogController(const JSCallbackInfo& info)
{
    ContainerScope scope(GetInstanceId());
    auto node = AceType::DynamicCast<NG::UINode>(this->GetViewNode());
    CHECK_NULL_VOID(node);
    RefPtr<NG::FrameNode> dialogNode = node->GetParentFrameNode();
    while (dialogNode) {
        if (dialogNode->GetTag() == V2::DIALOG_ETS_TAG) {
            break;
        }
        dialogNode = dialogNode->GetParentFrameNode();
    }
    CHECK_NULL_VOID(dialogNode);

    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value result = GetDialogController(env);
    CHECK_NULL_VOID(result);
    Napi::PromptDialogController* controller = nullptr;
    napi_unwrap(env, result, (void**)&controller);
    CHECK_NULL_VOID(controller);
    controller->SetNode(dialogNode);
    auto jsVal = JsConverter::ConvertNapiValueToJsVal(result);
    info.SetReturnValue(jsVal);
}

void JSViewPartialUpdate::JSBind(BindingTarget object)
{
    JSClass<JSViewPartialUpdate>::Declare("NativeViewPartialUpdate");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSViewPartialUpdate>::StaticMethod("create", &JSViewPartialUpdate::Create, opt);
    JSClass<JSViewPartialUpdate>::StaticMethod("createRecycle", &JSViewPartialUpdate::CreateRecycle, opt);
    JSClass<JSViewPartialUpdate>::Method("markNeedUpdate", &JSViewPartialUpdate::MarkNeedUpdate);
    JSClass<JSViewPartialUpdate>::Method("syncInstanceId", &JSViewPartialUpdate::SyncInstanceId);
    JSClass<JSViewPartialUpdate>::Method("restoreInstanceId", &JSViewPartialUpdate::RestoreInstanceId);
    JSClass<JSViewPartialUpdate>::CustomMethod("getInstanceId", &JSViewPartialUpdate::GetInstanceId);
    JSClass<JSViewPartialUpdate>::Method("markStatic", &JSViewPartialUpdate::MarkStatic);
    JSClass<JSViewPartialUpdate>::Method("finishUpdateFunc", &JSViewPartialUpdate::JsFinishUpdateFunc);
    JSClass<JSViewPartialUpdate>::Method("setCardId", &JSViewPartialUpdate::JsSetCardId);
    JSClass<JSViewPartialUpdate>::CustomMethod("getCardId", &JSViewPartialUpdate::JsGetCardId);
    JSClass<JSViewPartialUpdate>::Method("elmtIdExists", &JSViewPartialUpdate::JsElementIdExists);
    JSClass<JSViewPartialUpdate>::CustomMethod("isLazyItemRender", &JSViewPartialUpdate::JSGetProxiedItemRenderState);
    JSClass<JSViewPartialUpdate>::CustomMethod("isFirstRender", &JSViewPartialUpdate::IsFirstRender);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "findChildByIdForPreview", &JSViewPartialUpdate::FindChildByIdForPreview);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "resetRecycleCustomNode", &JSViewPartialUpdate::JSResetRecycleCustomNode);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "queryNavDestinationInfo", &JSViewPartialUpdate::JSGetNavDestinationInfo);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "queryNavigationInfo", &JSViewPartialUpdate::JSGetNavigationInfo);
    JSClass<JSViewPartialUpdate>::CustomMethod(
        "queryRouterPageInfo", &JSViewPartialUpdate::JSGetRouterPageInfo);
    JSClass<JSViewPartialUpdate>::CustomMethod("getUIContext", &JSViewPartialUpdate::JSGetUIContext);
    JSClass<JSViewPartialUpdate>::Method("sendStateInfo", &JSViewPartialUpdate::JSSendStateInfo);
    JSClass<JSViewPartialUpdate>::CustomMethod("getUniqueId", &JSViewPartialUpdate::JSGetUniqueId);
    JSClass<JSViewPartialUpdate>::Method("setIsV2", &JSViewPartialUpdate::JSSetIsV2);
    JSClass<JSViewPartialUpdate>::CustomMethod("getDialogController", &JSViewPartialUpdate::JSGetDialogController);
    JSClass<JSViewPartialUpdate>::Method(
        "allowReusableV2Descendant", &JSViewPartialUpdate::JSAllowReusableV2Descendant);
    JSClass<JSViewPartialUpdate>::InheritAndBind<JSViewAbstract>(object, ConstructorCallback, DestructorCallback);
}

bool JSViewPartialUpdate::JSAllowReusableV2Descendant()
{
    return ViewPartialUpdateModel::GetInstance()->AllowReusableV2Descendant(viewNode_);
}

void JSViewPartialUpdate::ConstructorCallback(const JSCallbackInfo& info)
{
    JSRef<JSObject> thisObj = info.This();

    // Get js view name by this.constructor.name
    JSRef<JSObject> constructor = thisObj->GetProperty("constructor");
    JSRef<JSVal> jsViewName = constructor->GetProperty("name");
    auto viewName = jsViewName->ToString();
    auto* instance = new JSViewPartialUpdate(thisObj);

    auto context = info.GetExecutionContext();
    instance->SetContext(context);
    instance->SetJSViewName(viewName);

    //  The JS object owns the C++ object:
    // make sure the C++ is not destroyed when RefPtr thisObj goes out of scope
    // JSView::DestructorCallback has view->DecRefCount()
    instance->IncRefCount();

    info.SetReturnValue(instance);
}

void JSViewPartialUpdate::DestructorCallback(JSViewPartialUpdate* view)
{
    if (view == nullptr) {
        return;
    }
    view->DecRefCount();
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

bool JSViewPartialUpdate::JsElementIdExists(int32_t elmtId)
{
    return ElementRegister::GetInstance()->Exists(elmtId);
}

void JSViewPartialUpdate::JSGetProxiedItemRenderState(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    const auto elmtId = info[0]->ToNumber<int32_t>();

    if (elmtId == ElementRegister::UndefinedElementId) {
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto result = false;

    // set boolean return value to JS
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSViewPartialUpdate::IsFirstRender(const JSCallbackInfo& info)
{
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isFirstRender_)));
}

void JSViewPartialUpdate::FindChildByIdForPreview(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        return;
    }
    std::string viewId = std::to_string(info[0]->ToNumber<int32_t>());
    JSRef<JSObject> targetView = Framework::JSViewStackProcessor::GetViewById(viewId);
    info.SetReturnValue(targetView);
    return;
}

} // namespace OHOS::Ace::Framework
