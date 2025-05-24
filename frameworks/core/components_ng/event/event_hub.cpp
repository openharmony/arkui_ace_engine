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

#include "core/components_ng/event/event_hub.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void EventHub::AttachHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

void EventHub::OnAttachContext(PipelineContext *context)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    if (HasOnAreaChanged() || HasInnerOnAreaChanged()) {
        context->AddOnAreaChangeNode(host->GetId());
    }

    if (HasVisibleAreaCallback(true) || HasVisibleAreaCallback(false) || HasThrottledVisibleAreaCallback()) {
        context->AddVisibleAreaChangeNode(host->GetId());
    }
}

void EventHub::OnDetachContext(PipelineContext *context)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    if (HasOnAreaChanged() || HasInnerOnAreaChanged()) {
        context->RemoveOnAreaChangeNode(host->GetId());
    }

    if (HasVisibleAreaCallback(true) || HasVisibleAreaCallback(false) || HasThrottledVisibleAreaCallback()) {
        host->SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::DETACH_FROM_MAINTREE);
        host->TriggerVisibleAreaChangeCallback(0, true);
        context->RemoveVisibleAreaChangeNode(host->GetId());
    }
    auto eventManager = context->GetEventManager();
    if (eventManager) {
        eventManager->DelKeyboardShortcutNode(host->GetId());
    }
}

RefPtr<FrameNode> EventHub::GetFrameNode() const
{
    return host_.Upgrade();
}

void EventHub::AddSupportedState(UIState state)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->AddSupportedState(state);
}

void EventHub::SetSupportedStates(UIState state)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->SetSupportedStates(state);
}

void EventHub::AddSupportedUIStateWithCallback(
    UIState state, std::function<void(uint64_t)>& callback, bool isInner, bool excludeInner)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->AddSupportedUIStateWithCallback(state, callback, isInner, excludeInner);
    AddPressedListener();
}

void EventHub::RemoveSupportedUIState(UIState state, bool isInner)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->RemoveSupportedUIState(state, isInner);
}

bool EventHub::GetUserSetStateStyle()
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    return stateStyleMgr_->GetUserSetStateStyle();
}

void EventHub::SetScrollingFeatureForbidden(bool isSetStateStyle)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->SetScrollingFeatureForbidden(isSetStateStyle);
}

void EventHub::SetCurrentUIState(UIState state, bool flag)
{
    if (!stateStyleMgr_) {
        stateStyleMgr_ = MakeRefPtr<StateStyleManager>(host_);
    }
    stateStyleMgr_->SetCurrentUIState(state, flag);
}

bool EventHub::IsCurrentStateOn(UIState state)
{
    if (!stateStyleMgr_) {
        return false;
    }
    return stateStyleMgr_->IsCurrentStateOn(state);
}

GetEventTargetImpl EventHub::CreateGetEventTargetImpl() const
{
    auto impl = [weak = host_]() -> std::optional<EventTarget> {
        auto host = weak.Upgrade();
        CHECK_NULL_RETURN(host, std::nullopt);
        EventTarget eventTarget;
        eventTarget.id = host->GetInspectorId().value_or("").c_str();
        eventTarget.type = host->GetTag();
        auto geometryNode = host->GetGeometryNode();
        auto offset = geometryNode->GetFrameOffset();
        auto size = geometryNode->GetFrameSize();
        eventTarget.area.SetOffset(DimensionOffset(offset));
        eventTarget.area.SetHeight(Dimension(size.Height()));
        eventTarget.area.SetWidth(Dimension(size.Width()));
        eventTarget.origin = DimensionOffset(host->GetOffsetRelativeToWindow() - offset);
        return eventTarget;
    };
    return impl;
}

void EventHub::PostEnabledTask()
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(this)]() {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->UpdateCurrentUIState(UI_STATE_DISABLED);
    };
    if (!host->IsOnMainTree()) {
        enabledFunc_ = callback;
        return;
    }
    taskExecutor->PostTask(callback, TaskExecutor::TaskType::UI, "ArkUIUpdateCurrentUIState");
}

void EventHub::FireEnabledTask()
{
    if (enabledFunc_) {
        enabledFunc_();
        enabledFunc_ = nullptr;
    }
}

void EventHub::AddPressedListener()
{
    if (stateStyleMgr_ && stateStyleMgr_->HasStateStyle(UI_STATE_PRESSED)) {
        GetOrCreateGestureEventHub()->AddTouchEvent(stateStyleMgr_->GetPressedListener());
    }
}

void EventHub::MarkModifyDone()
{
    if (stateStyleMgr_) {
        // focused style is managered in focus event hub.
        AddPressedListener();
        if (stateStyleMgr_->HasStateStyle(UI_STATE_DISABLED)) {
            if (enabled_) {
                stateStyleMgr_->ResetCurrentUIState(UI_STATE_DISABLED);
            } else {
                PostEnabledTask();
            }
        }
    }

    if (gestureEventHub_) {
        gestureEventHub_->OnModifyDone();
    }
    OnModifyDone();
}

void EventHub::SetCustomerOnDragFunc(DragFuncType dragFuncType, OnDragFunc&& onDragFunc)
{
    switch (dragFuncType) {
        case DragFuncType::DRAG_ENTER:
            customerOnDragEnter_ = std::move(onDragFunc);
            break;
        case DragFuncType::DRAG_LEAVE:
            customerOnDragLeave_ = std::move(onDragFunc);
            break;
        case DragFuncType::DRAG_MOVE:
            customerOnDragMove_ = std::move(onDragFunc);
            break;
        case DragFuncType::DRAG_DROP:
            customerOnDrop_ = std::move(onDragFunc);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_DRAG, "Unsupported DragFuncType");
            break;
    }
}

void EventHub::SetCustomerOnDragFunc(DragFuncType dragFuncType, OnNewDragFunc&& onDragEnd)
{
    if (dragFuncType != DragFuncType::DRAG_END) {
        return;
    }
    customerOnDragEnd_ = std::move(onDragEnd);
}

void EventHub::FireCustomerOnDragFunc(DragFuncType dragFuncType, const RefPtr<OHOS::Ace::DragEvent>& info,
    const std::string& extraParams)
{
    switch (dragFuncType) {
        case DragFuncType::DRAG_ENTER: {
            if (customerOnDragEnter_ != nullptr) {
                auto customerDragEnter = customerOnDragEnter_;
                customerDragEnter(info, extraParams);
            }
            break;
        }
        case DragFuncType::DRAG_LEAVE: {
            if (customerOnDragLeave_ != nullptr) {
                auto customerOnDragLeave = customerOnDragLeave_;
                customerOnDragLeave(info, extraParams);
            }
            break;
        }
        case DragFuncType::DRAG_MOVE: {
            if (customerOnDragMove_ != nullptr) {
                auto customerOnDragMove = customerOnDragMove_;
                customerOnDragMove(info, extraParams);
            }
            break;
        }
        case DragFuncType::DRAG_DROP: {
            if (customerOnDrop_ != nullptr) {
                auto customerOnDrop = customerOnDrop_;
                ACE_SCOPED_TRACE("drag: execute user onDrop");
                customerOnDrop(info, extraParams);
            }
            break;
        }
        case DragFuncType::DRAG_END: {
            if (customerOnDragEnd_ != nullptr) {
                auto customerOnDragEnd = customerOnDragEnd_;
                customerOnDragEnd(info);
            }
            break;
        }
        default:
            TAG_LOGW(AceLogTag::ACE_DRAG, "Unsupported DragFuncType");
            break;
    }
}

void EventHub::FireOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragDropManager fire onDragEnter");
    }
    if (onDragEnter_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDragEnter = onDragEnter_;
        onDragEnter(info, extraParams);
    }
}

void EventHub::FireOnDragLeave(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragDropManager fire onDragLeave");
    }
    if (onDragLeave_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDragLeave = onDragLeave_;
        onDragLeave(info, extraParams);
    }
}

void EventHub::FireOnDragMove(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragDropManager fire onDragMove");
    }
    if (onDragMove_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDragMove = onDragMove_;
        onDragMove(info, extraParams);
    }
}

void EventHub::FireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragDropManager fire onDrop");
    }
    if (onDrop_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDrop = onDrop_;
        onDrop(info, extraParams);
    }
}

bool EventHub::IsFireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info)
{
    return !HasCustomerOnDrop()
        || info->GetResult() == DragRet::DRAG_DEFAULT
        || info->GetResult() == DragRet::ENABLE_DROP
        || info->GetResult() == DragRet::DISABLE_DROP;
}

void EventHub::HandleInternalOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    CHECK_NULL_VOID(info);
    if (IsFireOnDrop(info)) {
        FireOnDrop(info, extraParams);
    } else {
        TAG_LOGI(AceLogTag::ACE_DRAG, "InternalOnDrop not exist");
    }
}

void EventHub::AddInnerOnAreaChangedCallback(int32_t id, OnAreaChangedFunc&& callback)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    pipeline->AddOnAreaChangeNode(frameNode->GetId());
    frameNode->InitLastArea();
    if (onAreaChangedInnerCallbacks_.find(id) == onAreaChangedInnerCallbacks_.end()) {
        hasInnerAreaChangeUntriggered_.emplace_back(id);
    }
    onAreaChangedInnerCallbacks_[id] = std::move(callback);
}

void EventHub::RemoveInnerOnAreaChangedCallback(int32_t id)
{
    onAreaChangedInnerCallbacks_.erase(id);
}

void EventHub::ClearCustomerOnDragFunc()
{
    onDragStart_ = nullptr;
    customerOnDragEnter_ = nullptr;
    customerOnDragSpringLoading_ = nullptr;
    customerOnDragLeave_ = nullptr;
    customerOnDragMove_ = nullptr;
    customerOnDrop_ = nullptr;
    customerOnDragEnd_ = nullptr;
}

void EventHub::ClearCustomerOnDragStart()
{
    onDragStart_ = nullptr;
}

void EventHub::ClearCustomerOnDragEnter()
{
    customerOnDragEnter_ = nullptr;
}

void EventHub::ClearCustomerOnDragSpringLoading()
{
    customerOnDragSpringLoading_ = nullptr;
}

void EventHub::ClearCustomerOnDragMove()
{
    customerOnDragMove_ = nullptr;
}

void EventHub::ClearCustomerOnDragLeave()
{
    customerOnDragLeave_ = nullptr;
}

void EventHub::ClearCustomerOnDrop()
{
    customerOnDrop_ = nullptr;
}

void EventHub::ClearCustomerOnDragEnd()
{
    customerOnDragEnd_ = nullptr;
}

void EventHub::SetOnSizeChanged(OnSizeChangedFunc&& onSizeChanged)
{
    onSizeChanged_ = std::move(onSizeChanged);
}

void EventHub::FireOnSizeChanged(const RectF& oldRect, const RectF& rect)
{
    if (onSizeChanged_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onSizeChanged = onSizeChanged_;
        onSizeChanged(oldRect, rect);
    }
}

void EventHub::SetJSFrameNodeOnSizeChangeCallback(OnSizeChangedFunc&& onSizeChanged)
{
    onJsFrameNodeSizeChanged_ = std::move(onSizeChanged);
}

void EventHub::FireJSFrameNodeOnSizeChanged(const RectF& oldRect, const RectF& rect)
{
    if (onJsFrameNodeSizeChanged_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onSizeChanged = onJsFrameNodeSizeChanged_;
        onSizeChanged(oldRect, rect);
    }
}

void EventHub::ClearJSFrameNodeOnSizeChange()
{
    if (onJsFrameNodeSizeChanged_) {
        onJsFrameNodeSizeChanged_ = nullptr;
    }
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    host->ResetLastFrameNodeRect();
}

bool EventHub::HasOnSizeChanged() const
{
    return static_cast<bool>(onSizeChanged_) || static_cast<bool>(onJsFrameNodeSizeChanged_);
}

bool EventHub::HasImmediatelyVisibleCallback()
{
    return visibleAreaUserCallback_.callback || visibleAreaInnerCallback_.callback;
}

void EventHub::ClearOnAreaChangedInnerCallbacks()
{
    onAreaChangedInnerCallbacks_.clear();
}

void EventHub::SetJSFrameNodeOnAppear(std::function<void()>&& onAppear)
{
    onJSFrameNodeAppear_ = std::move(onAppear);
}

void EventHub::ClearJSFrameNodeOnAppear()
{
    if (onJSFrameNodeAppear_) {
        onJSFrameNodeAppear_ = nullptr;
    }
}

void EventHub::SetJSFrameNodeOnDisappear(std::function<void()>&& onDisappear)
{
    onJSFrameNodeDisappear_ = std::move(onDisappear);
}

void EventHub::ClearJSFrameNodeOnDisappear()
{
    if (onJSFrameNodeDisappear_) {
        onJSFrameNodeDisappear_ = nullptr;
    }
}

void EventHub::FireOnAppear()
{
    if (onAppear_ || onJSFrameNodeAppear_) {
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [weak = WeakClaim(this)]() {
                auto eventHub = weak.Upgrade();
                CHECK_NULL_VOID(eventHub);
                if (eventHub->onAppear_) {
                    // callback may be overwritten in its invoke so we copy it first
                    auto onAppear = eventHub->onAppear_;
                    onAppear();
                }
                if (eventHub->onJSFrameNodeAppear_) {
                    // callback may be overwritten in its invoke so we copy it first
                    auto onJSFrameNodeAppear = eventHub->onJSFrameNodeAppear_;
                    onJSFrameNodeAppear();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIFrameNodeAppearEvent");
    }
}

void EventHub::FireOnDisappear()
{
    if (onDisappear_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onDisappear = onDisappear_;
        onDisappear();
    }
    if (onJSFrameNodeDisappear_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onJSFrameNodeDisappear = onJSFrameNodeDisappear_;
        onJSFrameNodeDisappear();
    }
}

void EventHub::AddInnerOnSizeChanged(int32_t id, OnSizeChangedFunc&& callback)
{
    onSizeChangedInnerCallbacks_[id] = std::move(callback);
}

void EventHub::FireInnerOnSizeChanged(const RectF& oldRect, const RectF& rect)
{
    for (auto& innerCallbackInfo : onSizeChangedInnerCallbacks_) {
        if (innerCallbackInfo.second) {
            auto innerOnSizeCallback = innerCallbackInfo.second;
            innerOnSizeCallback(oldRect, rect);
        }
    }
}

bool EventHub::HasInnerOnSizeChanged() const
{
    return !onSizeChangedInnerCallbacks_.empty();
}

void EventHub::ClearInnerOnSizeChanged()
{
    onSizeChangedInnerCallbacks_.clear();
}

void EventHub::SetOnAttach(std::function<void()>&& onAttach)
{
    onAttach_ = std::move(onAttach);
}

void EventHub::ClearOnAttach()
{
    onAttach_ = nullptr;
}

void EventHub::FireOnAttach()
{
    if (onAttach_) {
        auto onAttach = onAttach_;
        onAttach();
    }
}

void EventHub::SetOnDetach(std::function<void()>&& onDetach)
{
    onDetach_ = std::move(onDetach);
}

void EventHub::ClearOnDetach()
{
    onDetach_ = nullptr;
}

void EventHub::ClearOnPreDrag()
{
    onPreDragFunc_ = nullptr;
}

void EventHub::FireOnDetach()
{
    if (onDetach_) {
        auto onDetach = onDetach_;
        onDetach();
    }
}

void EventHub::SetOnWillBind(std::function<void(int32_t)>&& onWillBind)
{
    onWillBind_ = std::move(onWillBind);
}

void EventHub::ClearOnWillBind()
{
    onWillBind_ = nullptr;
}

void EventHub::FireOnWillBind(int32_t containerId)
{
    if (onWillBind_) {
        auto onWillBind = onWillBind_;
        onWillBind(containerId);
    }
}

void EventHub::SetOnWillUnbind(std::function<void(int32_t)>&& onWillUnbind)
{
    onWillUnbind_ = std::move(onWillUnbind);
}

void EventHub::ClearOnWillUnbind()
{
    onWillUnbind_ = nullptr;
}

void EventHub::FireOnWillUnbind(int32_t containerId)
{
    if (onWillUnbind_) {
        auto onWillUnbind = onWillUnbind_;
        onWillUnbind(containerId);
    }
}

void EventHub::SetOnBind(std::function<void(int32_t)>&& onBind)
{
    onBind_ = std::move(onBind);
}

void EventHub::ClearOnBind()
{
    onBind_ = nullptr;
}

void EventHub::FireOnBind(int32_t containerId)
{
    if (onBind_) {
        auto onBind = onBind_;
        onBind(containerId);
    }
}

void EventHub::SetOnUnbind(std::function<void(int32_t)>&& onUnbind)
{
    onUnbind_ = std::move(onUnbind);
}

void EventHub::ClearOnUnbind()
{
    onUnbind_ = nullptr;
}

void EventHub::FireOnUnbind(int32_t containerId)
{
    if (onUnbind_) {
        auto onUnbind = onUnbind_;
        onUnbind(containerId);
    }
}

void EventHub::ClearStateStyle()
{
    if (stateStyleMgr_) {
        stateStyleMgr_->ClearStateStyleTask();
    }
}

void EventHub::OnDetachClear()
{
    FireOnDetach();
    FireOnDisappear();
    ClearStateStyle();
}

const RefPtr<GestureEventHub>& EventHub::GetOrCreateGestureEventHub()
{
    if (!gestureEventHub_) {
        gestureEventHub_ = CreateGestureEventHub();
    }
    return gestureEventHub_;
}

const RefPtr<GestureEventHub>& EventHub::GetGestureEventHub() const
{
    return gestureEventHub_;
}

void EventHub::SetGestureEventHub(const RefPtr<GestureEventHub>& gestureEventHub)
{
    gestureEventHub_ = gestureEventHub;
}

const RefPtr<InputEventHub>& EventHub::GetOrCreateInputEventHub()
{
    if (!inputEventHub_) {
        inputEventHub_ = MakeRefPtr<InputEventHub>(WeakClaim(this));
    }
    return inputEventHub_;
}

const RefPtr<InputEventHub>& EventHub::GetInputEventHub() const
{
    return inputEventHub_;
}

RefPtr<FocusHub> EventHub::GetOrCreateFocusHub(FocusType type, bool focusable, FocusStyleType focusStyleType,
    const std::unique_ptr<FocusPaintParam>& paintParamsPtr)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetOrCreateFocusHub(type, focusable, focusStyleType, paintParamsPtr);
}

RefPtr<FocusHub> EventHub::GetOrCreateFocusHub(const FocusPattern& focusPattern)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetOrCreateFocusHub(focusPattern);
}

RefPtr<FocusHub> EventHub::GetFocusHub() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetFocusHub();
}

void EventHub::OnContextAttached()
{
    if (gestureEventHub_) {
        gestureEventHub_->OnContextAttached();
    }
}

void EventHub::ClearUserOnAppear()
{
    if (onAppear_) {
        onAppear_ = nullptr;
    }
}

void EventHub::SetOnAppear(std::function<void()>&& onAppear)
{
    onAppear_ = std::move(onAppear);
}

void EventHub::ClearUserOnDisAppear()
{
    if (onDisappear_) {
        onDisappear_ = nullptr;
    }
}

void EventHub::SetOnDisappear(std::function<void()>&& onDisappear)
{
    onDisappear_ = std::move(onDisappear);
}

void EventHub::ClearUserOnAreaChanged()
{
    if (onAreaChanged_) {
        onAreaChanged_ = nullptr;
    }
}

void EventHub::SetOnAreaChanged(OnAreaChangedFunc&& onAreaChanged)
{
    onAreaChanged_ = std::move(onAreaChanged);
}

void EventHub::FireOnAreaChanged(
    const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
{
    if (onAreaChanged_) {
        // callback may be overwritten in its invoke so we copy it first
        auto onAreaChanged = onAreaChanged_;
        onAreaChanged(oldRect, oldOrigin, rect, origin);
    }
}

void EventHub::FireInnerOnAreaChanged(
    const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
{
    for (auto& innerCallbackInfo : onAreaChangedInnerCallbacks_) {
        if (innerCallbackInfo.second) {
            auto innerOnAreaCallback = innerCallbackInfo.second;
            innerOnAreaCallback(oldRect, oldOrigin, rect, origin);
        }
    }
    hasInnerAreaChangeUntriggered_.clear();
}

bool EventHub::HasOnAreaChanged() const
{
    return static_cast<bool>(onAreaChanged_);
}

bool EventHub::HasInnerOnAreaChanged() const
{
    return !onAreaChangedInnerCallbacks_.empty();
}

void EventHub::SetOnPreDrag(OnPreDragFunc&& onPreDragFunc)
{
    onPreDragFunc_ = std::move(onPreDragFunc);
}

const OnPreDragFunc& EventHub::GetOnPreDrag() const
{
    return onPreDragFunc_;
}

void EventHub::SetOnDragStart(OnDragStartFunc&& onDragStart)
{
    onDragStart_ = std::move(onDragStart);
}

bool EventHub::HasOnDragStart() const
{
    return static_cast<bool>(onDragStart_) || static_cast<bool>(defaultOnDragStart_);
}

void EventHub::SetOnDragEnter(OnDragFunc&& onDragEnter)
{
    onDragEnter_ = std::move(onDragEnter);
}

void EventHub::SetCustomerOnDragSpringLoading(OnDrapDropSpringLoadingFunc&& onDragSpringLoading)
{
    customerOnDragSpringLoading_ = std::move(onDragSpringLoading);
}

const OnDrapDropSpringLoadingFunc& EventHub::GetCustomerOnDragSpringLoading() const
{
    return customerOnDragSpringLoading_;
}

void EventHub::SetOnDragLeave(OnDragFunc&& onDragLeave)
{
    onDragLeave_ = std::move(onDragLeave);
}

void EventHub::SetOnDragMove(OnDragFunc&& onDragMove)
{
    onDragMove_ = std::move(onDragMove);
}

bool EventHub::HasOnDragMove() const
{
    return static_cast<bool>(onDragMove_);
}

void EventHub::SetOnDrop(OnDragFunc&& onDrop)
{
    onDrop_ = std::move(onDrop);
}

void EventHub::SetOnDragEnd(OnNewDragFunc&& onDragEnd)
{
    onDragEnd_ = std::move(onDragEnd);
}

bool EventHub::HasOnDragEnter() const
{
    return static_cast<bool>(onDragEnter_);
}

bool EventHub::HasOnDragLeave() const
{
    return static_cast<bool>(onDragLeave_);
}

bool EventHub::HasOnDragEnd() const
{
    return static_cast<bool>(onDragEnd_);
}

bool EventHub::HasOnDrop() const
{
    return onDrop_ != nullptr;
}

bool EventHub::HasCustomerOnDragEnter() const
{
    return customerOnDragEnter_ != nullptr;
}

bool EventHub::HasCustomerOnDragLeave() const
{
    return customerOnDragLeave_ != nullptr;
}

bool EventHub::HasCustomerOnDragMove() const
{
    return customerOnDragMove_ != nullptr;
}

bool EventHub::HasCustomerOnDragEnd() const
{
    return customerOnDragEnd_ != nullptr;
}

bool EventHub::HasCustomerOnDrop() const
{
    return customerOnDrop_ != nullptr;
}

bool EventHub::HasCustomerOnDragSpringLoading() const
{
    return customerOnDragSpringLoading_ != nullptr;
}

void EventHub::SetDisableDataPrefetch(bool disableDataPrefetch)
{
    disableDataPrefetch_ = disableDataPrefetch;
}

bool EventHub::GetDisableDataPrefetch() const
{
    return disableDataPrefetch_;
}

bool EventHub::IsEnabled() const
{
    return enabled_;
}

bool EventHub::IsDeveloperEnabled() const
{
    return developerEnabled_;
}

void EventHub::SetEnabled(bool enabled)
{
    auto host = GetFrameNode();
    if (enabled_ != enabled && host) {
        auto accessibilityProperty = host->GetAccessibilityProperty<NG::AccessibilityProperty>();
        if (accessibilityProperty) {
            accessibilityProperty->NotifyComponentChangeEvent(AccessibilityEventType::ELEMENT_INFO_CHANGE);
        }
    }
    enabled_ = enabled;
    developerEnabled_ = enabled;
}

void EventHub::SetEnabledInternal(bool enabled)
{
    enabled_ = enabled;
}

// restore enabled value to what developer sets
void EventHub::RestoreEnabled()
{
    enabled_ = developerEnabled_;
}

void EventHub::UpdateCurrentUIState(UIState state)
{
    if (stateStyleMgr_) {
        stateStyleMgr_->UpdateCurrentUIState(state);
    }
}

void EventHub::ResetCurrentUIState(UIState state)
{
    if (stateStyleMgr_) {
        stateStyleMgr_->ResetCurrentUIState(state);
    }
}

UIState EventHub::GetCurrentUIState() const
{
    return stateStyleMgr_ ? stateStyleMgr_->GetCurrentUIState() : UI_STATE_NORMAL;
}

bool EventHub::HasStateStyle(UIState state) const
{
    if (stateStyleMgr_) {
        return stateStyleMgr_->HasStateStyle(state);
    }
    return false;
}

void EventHub::SetKeyboardShortcut(
    const std::string& value, uint8_t keys, const std::function<void()>& onKeyboardShortcutAction)
{
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "SetKeyboardShortcut value = %{public}s, keys = %{public}d", value.c_str(), keys);
    KeyboardShortcut keyboardShortcut;
    for (auto&& ch : value) {
        keyboardShortcut.value.push_back(static_cast<char>(std::toupper(ch)));
    }
    keyboardShortcut.keys = keys;
    keyboardShortcut.onKeyboardShortcutAction = onKeyboardShortcutAction;

    for (auto& shortCut : keyboardShortcut_) {
        if (shortCut.IsEqualTrigger(keyboardShortcut)) {
            shortCut.onKeyboardShortcutAction = onKeyboardShortcutAction;
            return;
        }
    }
    keyboardShortcut_.emplace_back(keyboardShortcut);
}

void EventHub::ClearSingleKeyboardShortcut()
{
    if (keyboardShortcut_.size() == 1) {
        keyboardShortcut_.clear();
    }
}

std::vector<KeyboardShortcut>& EventHub::GetKeyboardShortcut()
{
    return keyboardShortcut_;
}

void EventHub::SetDefaultOnDragStart(OnDragStartFunc&& defaultOnDragStart)
{
    defaultOnDragStart_ = std::move(defaultOnDragStart);
}

bool EventHub::HasDefaultOnDragStart() const
{
    return static_cast<bool>(defaultOnDragStart_);
}

std::vector<double>& EventHub::GetThrottledVisibleAreaRatios()
{
    return throttledVisibleAreaRatios_;
}

VisibleCallbackInfo& EventHub::GetThrottledVisibleAreaCallback()
{
    return throttledVisibleAreaCallback_;
}

std::vector<double>& EventHub::GetVisibleAreaRatios(bool isUser)
{
    if (isUser) {
        return visibleAreaUserRatios_;
    } else {
        return visibleAreaInnerRatios_;
    }
}

VisibleCallbackInfo& EventHub::GetVisibleAreaCallback(bool isUser)
{
    if (isUser) {
        return visibleAreaUserCallback_;
    } else {
        return visibleAreaInnerCallback_;
    }
}

void EventHub::SetVisibleAreaRatiosAndCallback(
    const VisibleCallbackInfo& callback, const std::vector<double>& radios, bool isUser)
{
    if (isUser) {
        VisibleCallbackInfo* cbInfo =
            (callback.period == 0) ? &visibleAreaUserCallback_ : &throttledVisibleAreaCallback_;
        auto ratioInfo = (callback.period == 0) ? &visibleAreaUserRatios_ : &throttledVisibleAreaRatios_;
        *cbInfo = callback;
        *ratioInfo = radios;
    } else {
        visibleAreaInnerCallback_ = callback;
        visibleAreaInnerRatios_ = radios;
    }
}

void EventHub::CleanVisibleAreaCallback(bool isUser, bool isThrottled)
{
    if (!isUser) {
        visibleAreaInnerRatios_.clear();
        visibleAreaInnerCallback_.callback = nullptr;
    } else if (isThrottled) {
        throttledVisibleAreaRatios_.clear();
        throttledVisibleAreaCallback_.callback = nullptr;
    } else {
        visibleAreaUserRatios_.clear();
        visibleAreaUserCallback_.callback = nullptr;
    }
}

bool EventHub::HasVisibleAreaCallback(bool isUser)
{
    if (isUser) {
        return static_cast<bool>(visibleAreaUserCallback_.callback);
    } else {
        return static_cast<bool>(visibleAreaInnerCallback_.callback);
    }
}

bool EventHub::HasThrottledVisibleAreaCallback() const
{
    return static_cast<bool>(throttledVisibleAreaCallback_.callback);
}

void EventHub::HandleOnAreaChange(const std::unique_ptr<RectF>& lastFrameRect,
    const std::unique_ptr<OffsetF>& lastParentOffsetToWindow,
    const RectF& currFrameRect, const OffsetF& currParentOffsetToWindow)
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    if (currFrameRect != *lastFrameRect || currParentOffsetToWindow != *lastParentOffsetToWindow) {
        if (HasInnerOnAreaChanged()) {
            FireInnerOnAreaChanged(
                *lastFrameRect, *lastParentOffsetToWindow, currFrameRect, currParentOffsetToWindow);
        }
        if (HasOnAreaChanged()) {
            FireOnAreaChanged(*lastFrameRect, *lastParentOffsetToWindow,
                host->GetFrameRectWithSafeArea(true), host->GetParentGlobalOffsetWithSafeArea(true, true));
        }
        *lastFrameRect = currFrameRect;
        *lastParentOffsetToWindow = currParentOffsetToWindow;
    }

    if (!hasInnerAreaChangeUntriggered_.empty()) {
        FireUntriggeredInnerOnAreaChanged(
            *lastFrameRect, *lastParentOffsetToWindow, currFrameRect, currParentOffsetToWindow);
    }
}

void EventHub::FireUntriggeredInnerOnAreaChanged(
    const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
{
    for (auto& id : hasInnerAreaChangeUntriggered_) {
        auto it = onAreaChangedInnerCallbacks_.find(id);
        if (it != onAreaChangedInnerCallbacks_.end()) {
            auto innerOnAreaCallback = it->second;
            if (innerOnAreaCallback) {
                innerOnAreaCallback(oldRect, oldOrigin, rect, origin);
            }
        }
    }
    hasInnerAreaChangeUntriggered_.clear();
}

void EventHub::FireDrawCompletedNDKCallback(PipelineContext* pipeline)
{
    if (ndkDrawCompletedCallback_) {
        if (!pipeline) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "can not fire draw callback, pipeline is null");
            return;
        }
        auto executor = pipeline->GetTaskExecutor();
        if (!executor) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "can not fire draw callback, executor is null");
            return;
        }
        auto cb = ndkDrawCompletedCallback_;
        executor->PostTask(std::move(cb), TaskExecutor::TaskType::UI, "FireDrawCompletedNDKCallback");
    }
}

void EventHub::FireLayoutNDKCallback(PipelineContext* pipeline)
{
    if (ndkLayoutCallback_) {
        if (!pipeline) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "can not fire layout callback, pipeline is null");
            return;
        }
        auto executor = pipeline->GetTaskExecutor();
        if (!executor) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "can not fire layout callback, executor is null");
            return;
        }
        auto cb = ndkLayoutCallback_;
        executor->PostTask(std::move(cb), TaskExecutor::TaskType::UI, "FireLayoutNDKCallback");
    }
}
} // namespace OHOS::Ace::NG
