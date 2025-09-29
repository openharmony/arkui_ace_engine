/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ability_component/ability_component_pattern.h"

#include "session_manager/include/extension_session_manager.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
AbilityComponentPattern::AbilityComponentPattern(const std::string& bundleName, const std::string& abilityName)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    if (container && container->IsSceneBoardEnabled()) {
        auto wantWrap = Ace::WantWrap::CreateWantWrap(bundleName, abilityName);
        auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
        Rosen::SessionInfo extensionSessionInfo = {
            .bundleName_ = bundleName,
            .abilityName_ = abilityName,
            .callerToken_ = container->GetToken(),
            .want = std::make_shared<Want>(want),
        };
        session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    }
}

void AbilityComponentPattern::OnAttachToFrameNode()
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    if (!container || !container->IsSceneBoardEnabled()) {
        return;
    }
    WindowPattern::OnAttachToFrameNode();
}

void AbilityComponentPattern::OnModifyDone()
{
    auto container = Container::Current();
    if (container && container->IsSceneBoardEnabled()) {
        Pattern::OnModifyDone();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetOrCreateEventHub<EventHub>();
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
    if (adapter_) {
        UpdateWindowRect();
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto windowId = pipelineContext->GetWindowId();
        adapter_ = WindowExtensionConnectionProxyNG::CreateAdapter();
        CHECK_NULL_VOID(adapter_);
        if (container && container->IsSceneBoardEnabled()) {
            CHECK_NULL_VOID(session_);
            sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
            CHECK_NULL_VOID(extensionSession);
            adapter_->SetExtensionSession(extensionSession);
        }
        adapter_->ConnectExtension(GetHost(), windowId);
        pipelineContext->AddOnAreaChangeNode(host->GetId());
        pipelineContext->AddWindowStateChangedCallback(host->GetId());
        LOGI("connect to windows extension begin %{public}s", GetHost()->GetTag().c_str());
    }
}

void AbilityComponentPattern::FireConnect()
{
    hasConnectionToAbility_ = true;
    UpdateWindowRect();
    auto pipeline = PipelineBase::GetCurrentContext();
    TransferFocusState(IsCurrentFocus());

    auto abilityComponentEventHub = GetOrCreateEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(abilityComponentEventHub);
    abilityComponentEventHub->FireOnConnect();
}

void AbilityComponentPattern::FireDisConnect()
{
    hasConnectionToAbility_ = false;
    auto abilityComponentEventHub = GetOrCreateEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(abilityComponentEventHub);
    abilityComponentEventHub->FireOnDisConnect();
}

bool AbilityComponentPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /*dirty*/, const DirtySwapConfig& config)
{
    if (config.frameSizeChange || config.frameOffsetChange) {
        UpdateWindowRect();
    }
    return false;
}

FocusPattern AbilityComponentPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::NONE };
}

void AbilityComponentPattern::UpdateWindowRect()
{
    if (!hasConnectionToAbility_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto size = host->GetGeometryNode()->GetFrameSize();
    auto offset = host->GetTransformRelativeOffset();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    Rect rect = pipeline->GetDisplayWindowRectInfo();
    rect = Rect(offset.GetX() + rect.Left(), offset.GetY() + rect.Top(), size.Width(), size.Height());
    if (adapter_ && rect != lastRect_) {
        LOGI("ConnectExtension: %{public}f %{public}f %{public}f %{public}f", offset.GetX(), offset.GetY(),
            size.Width(), size.Height());
        adapter_->UpdateRect(rect);
        lastRect_ = rect;
    }
}

void AbilityComponentPattern::OnAreaChangedInner()
{
    UpdateWindowRect();
}

void AbilityComponentPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
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

void AbilityComponentPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
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

void AbilityComponentPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetSourceDevice() != SourceType::TOUCH) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Platform::CalculatePointerEvent(pointerEvent, host);
    WindowPattern::DispatchPointerEvent(pointerEvent);
    auto hub = host->GetFocusHub();
    CHECK_NULL_VOID(hub);
    hub->RequestFocusImmediately();
}

void AbilityComponentPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    if (info.GetAction() == MouseAction::PRESS) {
        auto hub = host->GetFocusHub();
        CHECK_NULL_VOID(hub);
        hub->RequestFocusImmediately();
    }
    WindowPattern::DispatchPointerEvent(pointerEvent);
}

void AbilityComponentPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)](FocusReason reason) {
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

void AbilityComponentPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        WindowPattern::DisPatchFocusActiveEvent(true);
    }
    TransferFocusState(true);
}

void AbilityComponentPattern::HandleBlurEvent()
{
    WindowPattern::DisPatchFocusActiveEvent(false);
    TransferFocusState(false);
}

bool AbilityComponentPattern::KeyEventConsumed(const KeyEvent& event)
{
    bool isConsumed = false;
    WindowPattern::DispatchKeyEventForConsumed(event.rawKeyEvent, isConsumed);
    return isConsumed;
}

bool AbilityComponentPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_TAB && event.action == KeyAction::DOWN) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, false);
        // tab trigger consume the key event
        return pipeline->IsTabJustTriggerOnKeyEvent();
    } else {
        return KeyEventConsumed(event);
    }
}

bool AbilityComponentPattern::IsCurrentFocus() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}
} // namespace OHOS::Ace::NG
