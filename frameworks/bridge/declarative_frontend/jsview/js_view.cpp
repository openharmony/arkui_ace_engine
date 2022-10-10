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

#include <string>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components/grid_layout/grid_layout_item_element.h"
#include "core/components/ifelse/if_else_element.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_v2/common/element_proxy.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSView::JSBind(BindingTarget object)
{
    JSViewPartialUpdate::JSBind(object);
    JSViewFullUpdate::JSBind(object);
}

void JSView::MarkNeedUpdate()
{
    ACE_DCHECK((!GetElement().Invalid()));
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");

    if (GetElement().Invalid()) {
        LOGE("Invalid Element weak ref, internal error");
        return;
    }
    needsUpdate_ = true;
    auto element = GetElement().Upgrade();
    if (element) {
        LOGD("Element %{public}d MarkDirty", element->GetElementId());
        element->MarkDirty();
    }
}

RefPtr<PageTransitionComponent> JSView::BuildPageTransitionComponent()
{
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    ViewStackProcessor::GetInstance()->ClearPageTransitionComponent();
    return pageTransitionComponent;
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
        ViewStackProcessor::GetInstance()->PushKey(viewId_);
        jsViewFunction_->ExecuteRender();
        ViewStackProcessor::GetInstance()->PopKey();
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

RefPtr<Component> JSViewFullUpdate::CreateComponent()
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID

    std::string key = ViewStackProcessor::GetInstance()->ProcessViewId(viewId_);
    auto composedComponent = AceType::MakeRefPtr<ComposedComponent>(key, "view");

    // add callback for element creation to component, and get pointer reference
    // to the element on creation. When state of this view changes, mark the
    // element to dirty.
    auto renderFunction = [weak = AceType::WeakClaim(this)](const RefPtr<Component>& component) -> RefPtr<Component> {
        auto jsView = weak.Upgrade();
        return jsView ? jsView->InternalRender(component) : nullptr;
    };

    auto elementFunction = [weak = AceType::WeakClaim(this), renderFunction](const RefPtr<ComposedElement>& element) {
        auto jsView = weak.Upgrade();
        if (!jsView) {
            LOGE("the js view is nullptr in element function");
            return;
        }
        if (jsView->element_.Invalid()) {
            ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
            if (jsView->jsViewFunction_) {
                jsView->jsViewFunction_->ExecuteAppear();
            }
        }
        jsView->element_ = element;
        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        if (element) {
            element->SetRenderFunction(std::move(renderFunction));
            if (jsView->jsViewFunction_ && jsView->jsViewFunction_->HasPageTransition()) {
                auto pageTransitionFunction = [weak]() -> RefPtr<Component> {
                    auto jsView = weak.Upgrade();
                    if (!jsView || !jsView->jsViewFunction_) {
                        return nullptr;
                    }
                    {
                        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Transition");
                        jsView->jsViewFunction_->ExecuteTransition();
                    }
                    return jsView->BuildPageTransitionComponent();
                };
                element->SetPageTransitionFunction(std::move(pageTransitionFunction));
            }
        }
    };

    composedComponent->SetElementFunction(std::move(elementFunction));

    if (IsStatic()) {
        LOGD("will mark composedComponent as static");
        composedComponent->SetStatic();
    }
    return composedComponent;
}

RefPtr<NG::UINode> JSViewFullUpdate::CreateUINode()
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID
    std::string key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewId_);
    auto composedNode = NG::CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), key);
    node_ = composedNode;

    {
        ACE_SCORING_EVENT("Component[" + viewId_ + "].Appear");
        if (jsViewFunction_) {
            jsViewFunction_->ExecuteAppear();
        }
    }

    // add callback for element creation to component, and get pointer reference
    // to the element on creation. When state of this view changes, mark the
    // element to dirty.
    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<NG::UINode> {
        auto jsView = weak.Upgrade();
        return jsView ? jsView->InternalRender() : nullptr;
    };

    composedNode->SetRenderFunction(std::move(renderFunction));
    return composedNode;
}

RefPtr<Component> JSViewFullUpdate::InternalRender(const RefPtr<Component>& parent)
{
    needsUpdate_ = false;
    RenderJSExecution();
    CleanUpAbandonedChild();
    jsViewFunction_->Destroy();
    auto buildComponent = ViewStackProcessor::GetInstance()->Finish();
    return buildComponent;
}

RefPtr<NG::UINode> JSViewFullUpdate::InternalRender()
{
    needsUpdate_ = false;
    RenderJSExecution();
    CleanUpAbandonedChild();
    jsViewFunction_->Destroy();
    return NG::ViewStackProcessor::GetInstance()->Finish();
}

/**
 * marks the JSView's composed component as needing update / rerender
 */
void JSViewFullUpdate::MarkNeedUpdate()
{
    ACE_DCHECK((!GetElement().Invalid()));
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");

    if (Container::IsCurrentUseNewPipeline()) {
        LOGW("not support full update in ng structure");
        return;
    }
    JSView::MarkNeedUpdate();
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
        if (Container::IsCurrentUseNewPipeline()) {
            NG::ViewStackProcessor::GetInstance()->Push(view->CreateUINode(), true);
        } else {
            ViewStackProcessor::GetInstance()->Push(view->CreateComponent(), true);
        }
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
    std::string id;
    if (Container::IsCurrentUseNewPipeline()) {
        id = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    } else {
        id = ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    }
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
    std::string id;
    if (Container::IsCurrentUsePartialUpdate()) {
        id = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    } else {
        id = ViewStackProcessor::GetInstance()->ProcessViewId(viewId);
    }
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

RefPtr<Component> JSViewPartialUpdate::CreateComponent()
{
    ACE_SCOPED_TRACE("JSViewPartialUpdate::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID

    const auto reservedElementId = ViewStackProcessor::GetInstance()->ClaimElementId();
    LOGD("Creating ComposedComponent with claimed elmtId %{public}d.", reservedElementId);
    const std::string key = std::to_string(reservedElementId);
    auto composedComponent = AceType::MakeRefPtr<ComposedComponent>(key, "view");
    composedComponent->SetElementId(reservedElementId);

    // Render function lambda to be called from ComposedElement
    // on 1. render call Initial Render
    // on 2. render do the Component -> Element updates (all prior steps done already)
    // 'component' is the (unused) parent component
    auto renderFunction = [weak = AceType::WeakClaim(this), elmtId = reservedElementId](
                              const RefPtr<Component>& component) -> RefPtr<Component> {
        auto jsView = weak.Upgrade();
        if (!jsView) {
            LOGE("Render function lambda - invalid weak ref to JSView in ComposedElement elmtId %{public}d"
                 " renderFunction, internal error!",
                elmtId);
            return nullptr;
        }
        if (jsView->isFirstRender_) {
            LOGD("Initial render function lambda start for ComposedElement elmtId %{public}d - start...", elmtId);
            jsView->isFirstRender_ = false;
            return jsView->InitialRender();
        }
        if (jsView->needsUpdate_) {
            // always returns nullptr
            LOGD("Rerender function lambda start for ComposedElement elmtId %{public}d - start...", elmtId);
            jsView->jsViewFunction_->ExecuteRerender();
            jsView->MakeElementUpdatesToCompleteRerender();
            jsView->needsUpdate_ = false;
        }
        return nullptr;
    };

    // partial update relies on remove function
    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        LOGD("JSViewPartialUpdate remove function lambda start ...");
        auto jsView = weak.Upgrade();
        if (!jsView) {
            LOGE("invalid weak ref to JSView in renderFunction, internal error!");
            return;
        }
        jsView->Destroy(nullptr);
        LOGD("JSViewPartialUpdate remove function lambda - done ");
    };

    auto elementFunction = [weak = AceType::WeakClaim(this), renderFunction, removeFunction](
                               const RefPtr<ComposedElement>& element) {
        auto jsView = weak.Upgrade();
        if (!jsView) {
            LOGE("the js view is nullptr in element function");
            return;
        }
        if (jsView->element_.Invalid()) {
            ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
            if (jsView->jsViewFunction_) {
                jsView->jsViewFunction_->ExecuteAppear();
            }
        }
        jsView->element_ = element;
        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        if (element) {
            element->SetRenderFunction(std::move(renderFunction));
            element->SetRemoveFunction(std::move(removeFunction));
            if (jsView->jsViewFunction_ && jsView->jsViewFunction_->HasPageTransition()) {
                auto pageTransitionFunction = [weak]() -> RefPtr<Component> {
                    auto jsView = weak.Upgrade();
                    if (!jsView || !jsView->jsViewFunction_) {
                        return nullptr;
                    }
                    {
                        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Transition");
                        jsView->jsViewFunction_->ExecuteTransition();
                    }
                    return jsView->BuildPageTransitionComponent();
                };
                element->SetPageTransitionFunction(std::move(pageTransitionFunction));
            }
        }
    };

    composedComponent->SetElementFunction(std::move(elementFunction));

    if (IsStatic()) {
        LOGD("will mark composedComponent as static");
        composedComponent->SetStatic();
    }
    return composedComponent;
}

RefPtr<Component> JSViewPartialUpdate::InitialRender()
{
    RenderJSExecution();
    auto buildComponent = ViewStackProcessor::GetInstance()->Finish();
    needsUpdate_ = false;
    return buildComponent;
}

void JSViewPartialUpdate::UpdateCustomFrame(RefPtr<NG::CustomMeasureLayoutNode> customNode)
{
    auto appearFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };
    customNode->SetAppearFunction(std::move(appearFunction));

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<NG::UINode> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        if (!jsView->isFirstRender_) {
            LOGW("the js view has already called initial render");
            return nullptr;
        }
        jsView->isFirstRender_ = false;
        return jsView->InitialUIRender();
    };
    customNode->SetRenderFunction(renderFunction);

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
    };
    customNode->SetUpdateFunction(std::move(updateFunction));

    // partial update relies on remove function
    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        LOGD("call remove view function");
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->Destroy(nullptr);
        jsView->node_.Reset();
    };
    customNode->SetDestroyFunction(std::move(removeFunction));

    auto measureFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteMeasure(layoutWrapper);
    };
    if (jsViewFunction_->HasMeasure()) {
        customNode->GetGeometryNode()->SetMeasureFunction(std::move(measureFunc));
    }

    auto layoutFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteLayout(layoutWrapper);
    };
    if (jsViewFunction_->HasLayout()) {
        customNode->GetGeometryNode()->SetLayoutFunction(std::move(layoutFunc));
    }
}

void JSViewPartialUpdate::UpdateNormalFrame(RefPtr<NG::CustomNode> customNode)
{
    auto appearFunction = [weak = AceType::WeakClaim(this)]() {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        ACE_SCORING_EVENT("Component[" + jsView->viewId_ + "].Appear");
        if (jsView->jsViewFunction_) {
            jsView->jsViewFunction_->ExecuteAppear();
        }
    };
    customNode->SetAppearFunction(std::move(appearFunction));

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<NG::UINode> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        if (!jsView->isFirstRender_) {
            LOGW("the js view has already called initial render");
            return nullptr;
        }
        jsView->isFirstRender_ = false;
        return jsView->InitialUIRender();
    };
    customNode->SetRenderFunction(renderFunction);

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
    };
    customNode->SetUpdateFunction(std::move(updateFunction));

    // partial update relies on remove function
    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        LOGD("call remove view function");
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->Destroy(nullptr);
        jsView->node_.Reset();
    };
    customNode->SetDestroyFunction(std::move(removeFunction));
}

RefPtr<NG::UINode> JSViewPartialUpdate::CreateUINode()
{
    ACE_SCOPED_TRACE("JSViewPartialUpdate::CreateSpecializedComponent");
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    viewId_ = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewId_);

    if (jsViewFunction_->HasMeasure() || jsViewFunction_->HasLayout()) {
        auto customNode = NG::CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(viewId, key);
        UpdateCustomFrame(customNode);
        node_ = customNode;
        return customNode;
    }

    // normal node donot contain onlayout onmeasure
    auto normalNode = NG::CustomNode::CreateCustomNode(viewId, key);
    UpdateNormalFrame(normalNode);
    node_ = normalNode;
    return normalNode;
}

RefPtr<NG::UINode> JSViewPartialUpdate::InitialUIRender()
{
    needsUpdate_ = false;
    RenderJSExecution();
    return NG::ViewStackProcessor::GetInstance()->Finish();
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
    if (Container::IsCurrentUseNewPipeline()) {
        auto node = node_.Upgrade();
        if (!node) {
            LOGE("fail to update due to custom Node is null");
            return;
        }
        if (AceType::InstanceOf<NG::CustomNode>(node)) {
            auto customNode = AceType::DynamicCast<NG::CustomNode>(node);
            needsUpdate_ = true;
            customNode->MarkNeedUpdate();
        } else if (AceType::InstanceOf<NG::CustomMeasureLayoutNode>(node)) {
            auto customNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(node);
            needsUpdate_ = true;
            customNode->MarkNeedUpdate();
        }
        return;
    }
    JSView::MarkNeedUpdate();
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
        if (Container::IsCurrentUseNewPipeline()) {
            NG::ViewStackProcessor::GetInstance()->Push(view->CreateUINode(), true);
        } else {
            ViewStackProcessor::GetInstance()->Push(view->CreateComponent(), true);
        }
    } else {
        LOGE("View Object is expected.");
    }
}

RefPtr<NG::CustomMeasureLayoutNode> JSViewPartialUpdate::CreateCustomMeasureLayoutNode()
{
    ACE_SCOPED_TRACE("JSViewPartialUpdate::CreateSpecializedComponent");
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    viewId_ = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewId_);
    auto customNode = NG::CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(viewId, key);
    measureLayoutNode_ = customNode;

    auto renderFunction = [weak = AceType::WeakClaim(this)]() -> RefPtr<NG::UINode> {
        auto jsView = weak.Upgrade();
        CHECK_NULL_RETURN(jsView, nullptr);
        if (!jsView->isFirstRender_) {
            LOGW("the js view has already called initial render");
            return nullptr;
        }
        jsView->isFirstRender_ = false;
        return jsView->InitialUIRender();
    };
    customNode->SetRenderFunction(renderFunction);

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
    };
    customNode->SetUpdateFunction(std::move(updateFunction));

    // partial update relies on remove function
    auto removeFunction = [weak = AceType::WeakClaim(this)]() -> void {
        LOGD("call remove view function");
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->Destroy(nullptr);
        jsView->measureLayoutNode_.Reset();
    };
    customNode->SetDestroyFunction(std::move(removeFunction));

    auto measureFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteMeasure(layoutWrapper);
    };
    if (jsViewFunction_->HasMeasure()) {
        customNode->GetGeometryNode()->SetMeasureFunction(std::move(measureFunc));
    }

    auto layoutFunc = [weak = AceType::WeakClaim(this)](NG::LayoutWrapper* layoutWrapper) -> void {
        auto jsView = weak.Upgrade();
        CHECK_NULL_VOID(jsView);
        jsView->jsViewFunction_->ExecuteLayout(layoutWrapper);
    };
    if (jsViewFunction_->HasLayout()) {
        customNode->GetGeometryNode()->SetLayoutFunction(std::move(layoutFunc));
    }

    return customNode;
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewStackProcessor::GetInstance()->FlushRerenderTask();
        return;
    }
    auto componentsPair = ViewStackProcessor::GetInstance()->FinishReturnMain();
    if ((componentsPair.first == nullptr) || (componentsPair.second == nullptr)) {
        LOGE("outmost wrapping component is null");
        return;
    }
    // chk main component componentsPair.second elmtId
    ACE_DCHECK(componentsPair.second->GetElementId() == elmtId);

    LOGD("Obtained %{public}s from ViewStackProcessor, to-be update Element has elmtId %{public}d. Adding to "
         "List of Component -> Element updates on next FlushBuild",
        AceType::TypeName(componentsPair.second), elmtId);

    // push the result of the update function with elmtId added on the list of pending updates, triple:
    // 0: elmtId
    // 1: outmost wrapping Component (most keep reference until localized updates done to avoid smart pointer auto
    // deletion!) 2: main Component
    pendingElementUpdates_.emplace_back(std::make_tuple(elmtId, componentsPair.first, componentsPair.second));

    // FlushBuild on UI thread side
    // will call MakeElementUpdatesToCompleteRerender
    auto element = GetElement().Upgrade();
    if (element) {
        element->MarkDirty();
    } else {
        LOGE("Internal error, element is is null");
    }
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

void JSViewPartialUpdate::ComponentToElementLocalizedUpdate(const UpdateFuncResult& updateFuncResult)
{
    /* updateFuncResult tuple:
       0: elmtId
       1: outmost wrapping Component (most keep reference until localized updates done to avoid smart pointer auto
          deletion!)
       2: main Component */
    const int32_t elmtId = std::get<0>(updateFuncResult);
    const RefPtr<Component> outmostWrappingComponent = std::get<1>(updateFuncResult); // stop at
    const RefPtr<Component> mainComponent = std::get<2>(updateFuncResult);            // has elmtId

    ACE_DCHECK(mainComponent != nullptr);
    ACE_DCHECK(elmtId != ElementRegister::UndefinedElementId);

    RefPtr<Element> element = ElementRegister::GetInstance()->GetElementById(elmtId);
    if (element != nullptr) {
        LOGD("Searching for localized update for %{public}s elmtId: %{public}d ...", AceType::TypeName(element),
            element->GetElementId());
        // special case, because new IfElement will be created
        if (AceType::DynamicCast<IfElseElement>(element) != nullptr) {
            IfElseElement::ComponentToElementLocalizedUpdate(mainComponent, element);
        } else if (AceType::DynamicCast<GridLayoutItemElement>(element) != nullptr) {
            // VSP::Finish returns swapped compared to reg
            AceType::DynamicCast<SoleChildElement>(element)->LocalizedUpdateWithItemComponent(
                mainComponent, outmostWrappingComponent);
        } else {
            element->LocalizedUpdateWithComponent(mainComponent, outmostWrappingComponent);
        }
        return;
    }

    auto elementProxy = ElementRegister::GetInstance()->GetElementProxyById(elmtId);
    if (elementProxy != nullptr) {
        elementProxy->LocalizedUpdate(mainComponent, outmostWrappingComponent);
        return;
    }

    LOGE("No suitable Element/ElementProxy with elmtId %{public}d found to update from %{public}s,"
         " elmtId exists in ElementRegister "
         "'%{public}s'.",
        elmtId, (mainComponent ? AceType::TypeName(mainComponent) : "no Component error"),
        (ElementRegister::GetInstance()->Exists(elmtId) ? "exists" : "missing"));
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
