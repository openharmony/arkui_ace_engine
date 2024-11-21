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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
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

    if (HasVisibleAreaCallback(true) || HasVisibleAreaCallback(false)) {
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

    if (HasVisibleAreaCallback(true) || HasVisibleAreaCallback(false)) {
        host->TriggerVisibleAreaChangeCallback(0, true);
        context->RemoveVisibleAreaChangeNode(host->GetId());
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
        eventTarget.id = std::to_string(host->GetId());
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto eventHub = weak.Upgrade();
            CHECK_NULL_VOID(eventHub);
            eventHub->UpdateCurrentUIState(UI_STATE_DISABLED);
        }, TaskExecutor::TaskType::UI, "ArkUIUpdateCurrentUIState");
}

void EventHub::MarkModifyDone()
{
    if (stateStyleMgr_) {
        // focused style is managered in focus event hub.
        if (stateStyleMgr_->HasStateStyle(UI_STATE_PRESSED)) {
            GetOrCreateGestureEventHub()->AddTouchEvent(stateStyleMgr_->GetPressedListener());
        }
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
            LOGW("unsuport dragFuncType");
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
            LOGW("unsuport DragFuncType");
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
    if (IsFireOnDrop(info)) {
        FireOnDrop(info, extraParams);
    }
}

void EventHub::AddInnerOnAreaChangedCallback(int32_t id, OnAreaChangedFunc&& callback)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    pipeline->AddOnAreaChangeNode(frameNode->GetId());
    frameNode->InitLastArea();
    onAreaChangedInnerCallbacks_[id] = std::move(callback);
}

void EventHub::RemoveInnerOnAreaChangedCallback(int32_t id)
{
    CHECK_RUN_ON(UI);
    onAreaChangedInnerCallbacks_.erase(id);
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

void EventHub::ClearCustomerOnDragFunc()
{
    onDragStart_ = nullptr;
    customerOnDragEnter_ = nullptr;
    customerOnDragLeave_ = nullptr;
    customerOnDragMove_ = nullptr;
    customerOnDrop_ = nullptr;
    customerOnDragEnd_ = nullptr;
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
        auto pipeline = PipelineBase::GetCurrentContextSafely();
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

void EventHub::FireOnDetach()
{
    if (onDetach_) {
        auto onDetach = onDetach_;
        onDetach();
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

void EventHub::SetEnabled(bool enabled)
{
    auto host = GetFrameNode();
    if (enabled_ != enabled && host) {
        host->OnAccessibilityEvent(AccessibilityEventType::ELEMENT_INFO_CHANGE);
    }
    enabled_ = enabled;
    developerEnabled_ = enabled;
}
} // namespace OHOS::Ace::NG
