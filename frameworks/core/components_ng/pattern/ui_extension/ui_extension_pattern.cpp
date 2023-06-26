/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

#include "session/host/include/extension_session.h"
#include "session_manager/include/extension_session_manager.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
UIExtensionPattern::UIExtensionPattern(const std::string& bundleName, const std::string& abilityName)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID(container);
    auto callerToken = container->GetToken();

    Rosen::ExtensionSessionManager::GetInstance().Init();
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = bundleName,
        .abilityName_ = abilityName,
        .callerToken_ = callerToken,
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    RegisterLifecycleListener();
    RequestExtensionSessionActivation();
}

UIExtensionPattern::~UIExtensionPattern()
{
    UnregisterLifecycleListener();
    RequestExtensionSessionDestruction();
}

void UIExtensionPattern::OnConnect()
{
    WindowPattern::OnConnect();
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    surfaceNode->CreateNodeInRenderThread();
}

void UIExtensionPattern::OnDisconnect()
{
    LOGI("UIExtensionPattern OnDisconnect called");
    auto pipeline = PipelineBase::GetCurrentContext();
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    taskExecutor->PostTask([weak = WeakClaim(this)]() {
        auto extensionPattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(extensionPattern);
        if (extensionPattern->onReleaseCallback_) {
            extensionPattern->onReleaseCallback_(static_cast<int32_t>(ReleaseCode::DESTROY_NORMAL));
        }
    }, TaskExecutor::TaskType::UI);
}

void UIExtensionPattern::OnWindowShow()
{
    RequestExtensionSessionActivation();
}

void UIExtensionPattern::OnWindowHide()
{
    RequestExtensionSessionBackground();
}

void UIExtensionPattern::RequestExtensionSessionActivation()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(extensionSession);
}

void UIExtensionPattern::RequestExtensionSessionBackground()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(extensionSession);
}

void UIExtensionPattern::RequestExtensionSessionDestruction()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(extensionSession);
}

RefPtr<LayoutAlgorithm> UIExtensionPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<UIExtensionLayoutAlgorithm>();
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID_NOLOG(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

FocusPattern UIExtensionPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::NONE };
}

void UIExtensionPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
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
            pattern->DisPatchFocusActiveEvent(false);
        }
    });
    focusHub->SetOnPaintFocusStateInternal([weak = WeakClaim(this)]() -> bool {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->DisPatchFocusActiveEvent(true);
            return true;
        }
        return false;
    });

    focusHub->SetOnKeyEventInternal([wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    });
}

void UIExtensionPattern::HandleFocusEvent()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline->GetIsFocusActive()) {
        WindowPattern::DisPatchFocusActiveEvent(true);
    }
}

void UIExtensionPattern::HandleBlurEvent()
{
    WindowPattern::DisPatchFocusActiveEvent(false);
}

bool UIExtensionPattern::KeyEventConsumed(const KeyEvent& event)
{
    bool isConsumed = false;
    WindowPattern::DispatchKeyEventForConsumed(event.rawKeyEvent, isConsumed);
    return isConsumed;
}

bool UIExtensionPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_TAB && event.action == KeyAction::DOWN) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        // tab trigger consume the key event
        return pipeline->IsTabJustTriggerOnKeyEvent();
    } else {
        return KeyEventConsumed(event);
    }
}

void UIExtensionPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
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

void UIExtensionPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
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

void UIExtensionPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetSourceDevice() != SourceType::TOUCH) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    WindowPattern::DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    WindowPattern::DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::OnModifyDone()
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
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
}

void UIExtensionPattern::SetOnReleaseCallback(std::function<void(int32_t)>&& callback)
{
    onReleaseCallback_ = std::move(callback);
}
} // namespace OHOS::Ace::NG
