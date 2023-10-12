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

namespace OHOS::Ace::NG {

void EventHub::AttachHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
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
                stateStyleMgr_->UpdateCurrentUIState(UI_STATE_DISABLED);
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
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("FireCustomerOnDragFunc type: %u", dragFuncType);
    }
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
        case: DragFuncType::DRAG_END: {
            if (customerOnDragEnd_ != nullptr) {
                auto customerOnDragEnd = customerOnDragEnd_;
                customerOnDragEnd(info);
            }
        }
        default:
            LOGW("unsuport DragFuncType");
            break;
    }
}

bool EventHub::IsFireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info)
{
#ifdef ENABLE_DRAG_FRAMEWORK
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("DragDropManager IsFireOnDrop, drag ret: %d", info->GetResult());
    }
    return !HasCustomerOnDrop()
        || info->GetResult() == DragRet::DRAG_DEFAULT
        || info->GetResult() == DragRet::ENABLE_DROP
        || info->GetResult() == DragRet::DISABLE_DROP;
#endif
    return true;
}

void EventHub::HandleInternalOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
{
    if (IsFireOnDrop(info)) {
        FireOnDrop(info, extraParams);
    }
}

} // namespace OHOS::Ace::NG
