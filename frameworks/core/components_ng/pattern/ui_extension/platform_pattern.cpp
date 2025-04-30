/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/platform_pattern.h"

#include <optional>

#include "core/event/key_event.h"
#include "core/event/pointer_event.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/ui_extension/platform_utils.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
PlatformPattern::PlatformPattern(AceLogTag tag, int32_t platformId)
    : tag_(tag), platformId_(platformId)
{
    PLATFORM_LOGI("The PlatformPattern is created");
}

PlatformPattern::~PlatformPattern()
{
    PLATFORM_LOGI("The PlatformPattern is destroyed");
}

RefPtr<LayoutAlgorithm> PlatformPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<UIExtensionLayoutAlgorithm>();
}

FocusPattern PlatformPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::FORCE_NONE };
}

void PlatformPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);
    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitMouseEvent(inputHub);
    InitHoverEvent(inputHub);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitKeyEvent(focusHub);
}

void PlatformPattern::InitKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetIsNodeNeedKey(true);
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });

    focusHub->SetOnBlurInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    });

    focusHub->SetOnClearFocusStateInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->DispatchFocusActiveEvent(false);
        }
    });

    focusHub->SetOnPaintFocusStateInternal([weak = WeakClaim(this)]() -> bool {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->DispatchFocusActiveEvent(true);
            return true;
        }
        return false;
    });

    focusHub->SetOnKeyEventInternal([wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->HandleKeyEvent(event);
        }
        return false;
    });
}

void PlatformPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto callback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    gestureHub->AddTouchEvent(touchEvent_);
}

void PlatformPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (mouseEvent_) {
        return;
    }
    auto callback = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    if (mouseEvent_) {
        inputHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(callback));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void PlatformPattern::InitHoverEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (hoverEvent_) {
        return;
    }
    auto callback = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };
    if (hoverEvent_) {
        inputHub->RemoveOnHoverEvent(hoverEvent_);
    }
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(callback));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

bool PlatformPattern::HandleKeyEvent(const KeyEvent& event)
{
    return false;
}

void PlatformPattern::HandleFocusEvent()
{}

void PlatformPattern::HandleBlurEvent()
{}

void PlatformPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetSourceDevice() != SourceType::TOUCH) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto newPointerEvent = PlatformUtils::CopyPointerEventWithExtraProperty(pointerEvent, tag_);
    CHECK_NULL_VOID(newPointerEvent);
    Platform::CalculatePointerEvent(newPointerEvent, host);
    AceExtraInputData::InsertInterpolatePoints(info);
    const auto& changedTouches = info.GetChangedTouches();
    if (!changedTouches.empty() && changedTouches.back().GetTouchType() == TouchType::DOWN) {
        auto focusHub = host->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->RequestFocusImmediately();
    }
    DispatchPointerEvent(newPointerEvent);
}

void PlatformPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    lastPointerEvent_ = PlatformUtils::CopyPointerEventWithExtraProperty(pointerEvent, tag_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Platform::CalculatePointerEvent(pointerEvent, host);
    if (info.GetAction() == MouseAction::PRESS) {
        auto hub = host->GetFocusHub();
        CHECK_NULL_VOID(hub);
        hub->RequestFocusImmediately();
    }
    DispatchPointerEvent(pointerEvent);
}

void PlatformPattern::HandleHoverEvent(bool isHover)
{
    if (isHover) {
        return;
    }
    CHECK_NULL_VOID(lastPointerEvent_);
    lastPointerEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    DispatchPointerEvent(lastPointerEvent_);
}

void PlatformPattern::HandleDragEvent(const DragPointerEvent& info)
{
    const auto pointerEvent = info.rawPointerEvent;
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Platform::CalculatePointerEvent(pointerEvent, host, true);
    DispatchPointerEvent(pointerEvent);
}

void PlatformPattern::SetOnErrorCallback(
    const std::function<void(int32_t code, const std::string& name, const std::string& message)>&& callback)
{
    onErrorCallback_ = std::move(callback);
    if (lastError_.code != 0) {
        ErrorMsg error;
        std::swap(lastError_, error);
        FireOnErrorCallback(error.code, error.name, error.message);
    }
}

void PlatformPattern::FireOnErrorCallback(
    int32_t code, const std::string& name, const std::string& message)
{
    PLATFORM_LOGI("FireOnError code: %{public}d, name: %{public}s, message: %{public}s",
        code, name.c_str(), message.c_str());
    if (onErrorCallback_) {
        ContainerScope scope(instanceId_);
        onErrorCallback_(code, name, message);
        return;
    }

    lastError_ = { code, name, message };
}

void PlatformPattern::OnMountToParentDone()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetNodeStatus() == NodeStatus::NORMAL_NODE) {
        PLATFORM_LOGW("Frame node status is normal.");
        return;
    }
}

int32_t PlatformPattern::GetNodeId()
{
    auto host = GetHost();
    return host ? host->GetId() : -1;
}

int32_t PlatformPattern::GetInstanceId()
{
    return instanceId_;
}
} // namespace OHOS::Ace::NG
