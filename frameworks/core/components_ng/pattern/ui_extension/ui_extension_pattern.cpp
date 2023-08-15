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

#include <cstdint>
#include <memory>

#include "session/host/include/extension_session.h"
#include "session_manager/include/extension_session_manager.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
UIExtensionPattern::UIExtensionPattern(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID_NOLOG(container);
    auto callerToken = container->GetToken();
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    if (want.GetElement().GetBundleName() == "AbilityComp") {
        return;
    }
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = want.GetElement().GetBundleName(),
        .abilityName_ = want.GetElement().GetAbilityName(),
        .callerToken_ = callerToken,
        .want = new (std::nothrow) Want(want),
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    CHECK_NULL_VOID(session_);
    RegisterLifecycleListener();
    LOGI("UIExtension request UIExtensionAbility start");
    RequestExtensionSessionActivation();
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    sptr<Rosen::ExtensionSession::ExtensionSessionEventCallback> extSessionEventCallback =
        new (std::nothrow) Rosen::ExtensionSession::ExtensionSessionEventCallback();
    extensionSession->RegisterExtensionSessionEventCallback(extSessionEventCallback);
}

UIExtensionPattern::UIExtensionPattern(const AAFwk::Want& want)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID_NOLOG(container);
    auto callerToken = container->GetToken();
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = want.GetElement().GetBundleName(),
        .abilityName_ = want.GetElement().GetAbilityName(),
        .callerToken_ = callerToken,
        .want = new (std::nothrow) Want(want),
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    CHECK_NULL_VOID(session_);
    RegisterLifecycleListener();
    LOGI("Native Modal UIExtension request UIExtensionAbility start");
    RequestExtensionSessionActivation();
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    sptr<Rosen::ExtensionSession::ExtensionSessionEventCallback> extSessionEventCallback =
        new (std::nothrow) Rosen::ExtensionSession::ExtensionSessionEventCallback();
    extensionSession->RegisterExtensionSessionEventCallback(extSessionEventCallback);
}

UIExtensionPattern::~UIExtensionPattern()
{
    UnregisterLifecycleListener();
    UnregisterAbilityResultListener();
    RequestExtensionSessionDestruction();
}

void UIExtensionPattern::OnConnect()
{
    LOGI("UIExtension OnConnect called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(extensionPattern);
            extensionPattern->OnConnectInner();
        },
        TaskExecutor::TaskType::UI);
}

void UIExtensionPattern::OnConnectInner()
{
    ContainerScope scope(instanceId_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID_NOLOG(surfaceNode);
    CHECK_NULL_VOID_NOLOG(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID_NOLOG(context);
    context->SetRSNode(surfaceNode);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    auto pipeline = PipelineBase::GetCurrentContext();
    if (onRemoteReadyCallback_) {
        onRemoteReadyCallback_(MakeRefPtr<UIExtensionProxy>(session_));
    }
    if (onModalRemoteReadyCallback_) {
        onModalRemoteReadyCallback_(std::make_shared<ModalUIExtensionProxyImpl>(session_));
    }
    RegisterVisibleAreaChange();
    TransferFocusState(IsCurrentFocus());
}

void UIExtensionPattern::OnDisconnect()
{
    LOGI("UIExtension OnDisconnect called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    isDestruction_ = true;
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(extensionPattern);
            if (extensionPattern->onReleaseCallback_) {
                extensionPattern->onReleaseCallback_(static_cast<int32_t>(ReleaseCode::DESTROY_NORMAL));
            }
        },
        TaskExecutor::TaskType::UI);
}

void UIExtensionPattern::OnExtensionDied()
{
    LOGI("UIExtensionPattern OnExtensionDied called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(extensionPattern);
            if (extensionPattern->onReleaseCallback_) {
                extensionPattern->onReleaseCallback_(static_cast<int32_t>(ReleaseCode::CONNECT_BROKEN));
            }
        },
        TaskExecutor::TaskType::UI);
}

bool UIExtensionPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    auto host = dirty->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto globalOffsetWithTranslate = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto frameRect = geometryNode->GetFrameRect();

    Rosen::WSRect windowRect {
        .posX_ = std::round(globalOffsetWithTranslate.GetX()),
        .posY_ = std::round(globalOffsetWithTranslate.GetY()),
        .width_ = std::round(frameRect.Width()),
        .height_ = std::round(frameRect.Height())
    };

    CHECK_NULL_RETURN(session_, false);
    session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED);
    return false;
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    LOGI("UIExtension request host windowId %{public}u", hostWindowId);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto errcode = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        extensionSession, hostWindowId);
    if (errcode != OHOS::Rosen::WSError::WS_OK) {
        int32_t code = static_cast<int32_t>(errcode);
        std::string name = "start_ability_fail";
        std::string message = "Start ui extension ability failed, please check the want of UIextensionAbility.";
        lastError_ = { code, name, message };
        if (onErrorCallback_) {
            ErrorMsg error;
            std::swap(lastError_, error);
            onErrorCallback_(error.code, error.name, error.message);
        }
    }
}

void UIExtensionPattern::RequestExtensionSessionBackground()
{
    LOGI("UIExtension request UIExtensionAbility background, isDestruction_=%{public}u, isBackground_=%{public}u",
            isDestruction_, isBackground_);
    if (!isDestruction_ && !isBackground_) {
        sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
        auto errcode =
            Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(extensionSession);
        if (errcode != OHOS::Rosen::WSError::WS_OK) {
            if (onErrorCallback_) {
                int32_t code = static_cast<int32_t>(errcode);
                std::string name = "background_fail";
                std::string message = "background ui extension ability failed, please check AMS log.";
                onErrorCallback_(code, name, message);
            }
        } else {
            isBackground_ = true;
        }
    }
}

void UIExtensionPattern::RequestExtensionSessionDestruction()
{
    LOGI("UIExtension request UIExtensionAbility destroy, isDestruction_=%{public}u", isDestruction_);
    if (!isDestruction_) {
        sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
        auto errcode =
            Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(extensionSession);
        if (errcode != OHOS::Rosen::WSError::WS_OK) {
            if (onErrorCallback_) {
                int32_t code = static_cast<int32_t>(errcode);
                std::string name = "terminate_fail";
                std::string message = "terminate ui extension ability failed, please check AMS log.";
                onErrorCallback_(code, name, message);
            }
        }
    }
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
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
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
    TransferFocusState(true);
}

void UIExtensionPattern::HandleBlurEvent()
{
    WindowPattern::DisPatchFocusActiveEvent(false);
    TransferFocusState(false);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
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
    CHECK_NULL_VOID_NOLOG(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    auto hub = host->GetFocusHub();
    CHECK_NULL_VOID(hub);
    hub->RequestFocusImmediately();

    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        auto touchOffsetToWindow = info.GetTouches().front().GetGlobalLocation();
        auto touchOffsetToFrameNode = info.GetTouches().front().GetLocalLocation();
        auto rectToWindow = host->GetTransformRectRelativeToWindow();
        UpdateTextFieldManager({ rectToWindow.GetOffset().GetX(), touchOffsetToWindow.GetY() },
            rectToWindow.Height() - touchOffsetToFrameNode.GetY());
    }

    WindowPattern::DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID_NOLOG(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    if (info.GetAction() == MouseAction::PRESS) {
        auto hub = host->GetFocusHub();
        CHECK_NULL_VOID(hub);
        hub->RequestFocusImmediately();

        auto mouseOffsetToWindow = info.GetGlobalLocation();
        auto mouseOffsetToFrameNode = info.GetLocalLocation();
        auto rectToWindow = host->GetTransformRectRelativeToWindow();
        UpdateTextFieldManager({ rectToWindow.GetOffset().GetX(), mouseOffsetToWindow.GetY() },
            rectToWindow.Height() - mouseOffsetToFrameNode.GetY());
    }
    WindowPattern::DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID_NOLOG(gestureHub);
    InitTouchEvent(gestureHub);
    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID_NOLOG(inputHub);
    InitMouseEvent(inputHub);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
}

void UIExtensionPattern::UnregisterAbilityResultListener()
{
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
}

void UIExtensionPattern::SetOnRemoteReadyCallback(const std::function<void(const RefPtr<UIExtensionProxy>&)>&& callback)
{
    onRemoteReadyCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto extSessionEventCallback = extensionSession->GetExtensionSessionEventCallback();
    extSessionEventCallback->notifyRemoteReadyFunc_ =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor]() {
            taskExecutor->PostTask([weak, instanceId]() {
                ContainerScope scope(instanceId);
                LOGI("UIExtension OnRemoteReady called");
                auto pattern = weak.Upgrade();
                if (pattern && pattern->onRemoteReadyCallback_) {
                    pattern->onRemoteReadyCallback_(MakeRefPtr<UIExtensionProxy>(pattern->session_));
                }
            }, TaskExecutor::TaskType::UI);
        };
}

void UIExtensionPattern::SetModalOnRemoteReadyCallback(
    const std::function<void(const std::shared_ptr<ModalUIExtensionProxy>&)>&& callback)
{
    onModalRemoteReadyCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto extSessionEventCallback = extensionSession->GetExtensionSessionEventCallback();
    extSessionEventCallback->notifyRemoteReadyFunc_ =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor]() {
            taskExecutor->PostTask([weak, instanceId]() {
                ContainerScope scope(instanceId);
                LOGI("UIExtension native OnModalRemoteReady called");
                auto pattern = weak.Upgrade();
                if (pattern && pattern->onModalRemoteReadyCallback_) {
                    pattern->onModalRemoteReadyCallback_(
                        std::make_shared<ModalUIExtensionProxyImpl>(pattern->session_));
                }
            }, TaskExecutor::TaskType::UI);
        };
}

void UIExtensionPattern::SetOnReleaseCallback(const std::function<void(int32_t)>&& callback)
{
    onReleaseCallback_ = std::move(callback);
}

void UIExtensionPattern::SetOnErrorCallback(
    const std::function<void(int32_t code, const std::string& name, const std::string& message)>&& callback)
{
    onErrorCallback_ = std::move(callback);
    if (lastError_.code != 0) {
        ErrorMsg error;
        std::swap(lastError_, error);
        onErrorCallback_(error.code, error.name, error.message);
    }
}

void UIExtensionPattern::SetOnResultCallback(const std::function<void(int32_t, const AAFwk::Want&)>&& callback)
{
    onResultCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto extSessionEventCallback = extensionSession->GetExtensionSessionEventCallback();
    extSessionEventCallback->transferAbilityResultFunc_ =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor](int32_t code, const AAFwk::Want& want) {
            taskExecutor->PostTask([weak, instanceId, code, want]() {
                ContainerScope scope(instanceId);
                LOGI("UIExtension OnResult called");
                auto pattern = weak.Upgrade();
                if (pattern && pattern->onResultCallback_) {
                    pattern->onResultCallback_(code, want);
                }
            }, TaskExecutor::TaskType::UI);
        };
}

void UIExtensionPattern::SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback)
{
    onReceiveCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID_NOLOG(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto extSessionEventCallback = extensionSession->GetExtensionSessionEventCallback();
    extSessionEventCallback->transferExtensionDataFunc_ =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor](const AAFwk::WantParams& params) {
            taskExecutor->PostTask([weak, instanceId, params]() {
                ContainerScope scope(instanceId);
                LOGI("UIExtension OnReceive called");
                auto pattern = weak.Upgrade();
                if (pattern && pattern->onReceiveCallback_) {
                    pattern->onReceiveCallback_(params);
                }
            }, TaskExecutor::TaskType::UI);
        };
}

void UIExtensionPattern::OnVisibleChange(bool visible)
{
    if (visible) {
        RequestExtensionSessionActivation();
    } else {
        RequestExtensionSessionBackground();
    }
}

void UIExtensionPattern::RegisterVisibleAreaChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto uiExtension = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(uiExtension);
        uiExtension->OnVisibleChange(visible);
    };
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback, false);
}

void UIExtensionPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    if (!IsCurrentFocus()) {
        return;
    }
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(offset);
    textFieldManager->SetHeight(height);
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
}

bool UIExtensionPattern::IsCurrentFocus() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN_NOLOG(focusHub, false);
    return focusHub->IsCurrentFocus();
}

int32_t UIExtensionPattern::GetSessionId()
{
    CHECK_NULL_RETURN(session_, 0);
    return session_->GetPersistentId();
}
} // namespace OHOS::Ace::NG
