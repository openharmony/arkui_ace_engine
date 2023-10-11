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

#include "key_event.h"
#include "pointer_event.h"
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
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
class UIExtensionLifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit UIExtensionLifecycleListener(const WeakPtr<UIExtensionPattern>& uiExtensionPattern_)
        : uiExtensionPattern_(uiExtensionPattern_) {}
    virtual ~UIExtensionLifecycleListener() = default;

    void OnActivation() override {}
    void OnForeground() override {}
    void OnBackground() override {}

    void OnConnect() override
    {
        auto uiExtensionPattern = uiExtensionPattern_.Upgrade();
        CHECK_NULL_VOID(uiExtensionPattern);
        uiExtensionPattern->OnConnect();
    }

    void OnDisconnect() override
    {
        auto uiExtensionPattern = uiExtensionPattern_.Upgrade();
        CHECK_NULL_VOID(uiExtensionPattern);
        uiExtensionPattern->OnDisconnect();
    }

    void OnExtensionDied() override
    {
        auto uiExtensionPattern = uiExtensionPattern_.Upgrade();
        CHECK_NULL_VOID(uiExtensionPattern);
        uiExtensionPattern->OnExtensionDied();
    }

private:
    WeakPtr<UIExtensionPattern> uiExtensionPattern_;
};

UIExtensionPattern::UIExtensionPattern() = default;

UIExtensionPattern::~UIExtensionPattern()
{
    DestorySession();
}

void UIExtensionPattern::DestorySession()
{
    UnregisterLifecycleListener();
    UnregisterAbilityResultListener();
    RequestExtensionSessionDestruction();
    // Native modal page destroy callback
    if (onModalDestroy_) {
        onModalDestroy_();
    }
}

void UIExtensionPattern::UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    UpdateWant(want);
}

void UIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    if (session_ && (!session_->GetSessionInfo().want->IsEquals(want))) {
        DestorySession();
    }
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID(container);
    auto callerToken = container->GetToken();
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = want.GetElement().GetBundleName(),
        .abilityName_ = want.GetElement().GetAbilityName(),
        .callerToken_ = callerToken,
        .want = std::make_shared<Want>(want),
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

void UIExtensionPattern::OnConnect()
{
    LOGI("UIExtension OnConnect called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID(extensionPattern);
            extensionPattern->OnConnectInner();
        },
        TaskExecutor::TaskType::UI);
}

void UIExtensionPattern::OnConnectInner()
{
    CHECK_NULL_VOID(session_);
    ContainerScope scope(instanceId_);
    contentNode_ = FrameNode::CreateFrameNode(
        V2::UI_EXTENSION_SURFACE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    context->SetRSNode(surfaceNode);
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
    bool isFocused = IsCurrentFocus();
    RegisterVisibleAreaChange();
    TransferFocusState(isFocused);
    if (isFocused) {
        auto context = AceType::DynamicCast<PipelineContext>(pipeline);
        auto uiExtensionManager = context->GetUIExtensionManager();
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this));
    }
}

void UIExtensionPattern::OnDisconnect()
{
    LOGI("UIExtension OnDisconnect called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    state_ = AbilityState::DESTRUCTION;
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID(extensionPattern);
            if (extensionPattern->onReleaseCallback_) {
                extensionPattern->onReleaseCallback_(static_cast<int32_t>(ReleaseCode::DESTROY_NORMAL));
            }
        },
        TaskExecutor::TaskType::UI);
}

void UIExtensionPattern::OnExtensionDied()
{
    LOGI("UIExtension OnExtensionDied called");
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    state_ = AbilityState::DESTRUCTION;
    taskExecutor->PostTask(
        [weak = WeakClaim(this)]() {
            auto extensionPattern = weak.Upgrade();
            CHECK_NULL_VOID(extensionPattern);
            if (extensionPattern->onReleaseCallback_) {
                extensionPattern->onReleaseCallback_(static_cast<int32_t>(ReleaseCode::CONNECT_BROKEN));
            }
        },
        TaskExecutor::TaskType::UI);
}

bool UIExtensionPattern::OnBackPressed()
{
    bool isConsumed = false;
    DispatchBackpressedEventForConsumed(isConsumed);
    return isConsumed;
}

void UIExtensionPattern::RegisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<UIExtensionLifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
}

void UIExtensionPattern::UnregisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
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
    LOGI("UIExtension request UIExtensionAbility foreground, AbilityState=%{public}d", static_cast<int>(state_));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    LOGI("UIExtension request host windowId %{public}u", hostWindowId);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto&& resultCallback =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor] (OHOS::Rosen::WSError errcode) {
        taskExecutor->PostTask([weak, instanceId, errcode] {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessUIExtensionSessionActivationResult(errcode);
        }, TaskExecutor::TaskType::UI);
    };
    state_ = AbilityState::FOREGROUND;
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        extensionSession, hostWindowId, resultCallback);
}

void UIExtensionPattern::RequestExtensionSessionBackground()
{
    LOGI("UIExtension request UIExtensionAbility background, AbilityState=%{public}d", static_cast<int>(state_));
    if (state_ != AbilityState::FOREGROUND) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto&& resultCallback =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor] (OHOS::Rosen::WSError errcode) {
        taskExecutor->PostTask([weak, instanceId, errcode] {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessUIExtensionSessionBackgroundResult(errcode);
        }, TaskExecutor::TaskType::UI);
    };
    state_ = AbilityState::BACKGROUND;
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(extensionSession, resultCallback);
}

void UIExtensionPattern::RequestExtensionSessionDestruction()
{
    LOGI("UIExtension request UIExtensionAbility destroy, AbilityState=%{public}d", static_cast<int>(state_));
    if (state_ == AbilityState::DESTRUCTION || state_ == AbilityState::NONE) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto&& resultCallback =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor] (OHOS::Rosen::WSError errcode) {
        taskExecutor->PostTask([weak, instanceId, errcode] {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessUIExtensionSessionDestructionResult(errcode);
        }, TaskExecutor::TaskType::UI);
    };
    state_ = AbilityState::DESTRUCTION;
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(extensionSession, resultCallback);
}

RefPtr<LayoutAlgorithm> UIExtensionPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<UIExtensionLayoutAlgorithm>();
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
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
        DisPatchFocusActiveEvent(true);
    }
    TransferFocusState(true);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this));
}

void UIExtensionPattern::HandleBlurEvent()
{
    DisPatchFocusActiveEvent(false);
    TransferFocusState(false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->RegisterUIExtensionInFocus(nullptr);
}

bool UIExtensionPattern::KeyEventConsumed(const KeyEvent& event)
{
    bool isConsumed = false;
    DispatchKeyEventForConsumed(event.rawKeyEvent, isConsumed);
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
    CHECK_NULL_VOID(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        auto touchOffsetToWindow = info.GetTouches().front().GetGlobalLocation();
        auto touchOffsetToFrameNode = info.GetTouches().front().GetLocalLocation();
        auto rectToWindow = host->GetTransformRectRelativeToWindow();
        UpdateTextFieldManager({ rectToWindow.GetOffset().GetX(), touchOffsetToWindow.GetY() },
            rectToWindow.Height() - touchOffsetToFrameNode.GetY());
    }
    DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
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

        auto mouseOffsetToWindow = info.GetGlobalLocation();
        auto mouseOffsetToFrameNode = info.GetLocalLocation();
        auto rectToWindow = host->GetTransformRectRelativeToWindow();
        UpdateTextFieldManager({ rectToWindow.GetOffset().GetX(), mouseOffsetToWindow.GetY() },
            rectToWindow.Height() - mouseOffsetToFrameNode.GetY());
    }
    DispatchPointerEvent(pointerEvent);
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

void UIExtensionPattern::UnregisterAbilityResultListener()
{
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
}

void UIExtensionPattern::SetOnRemoteReadyCallback(const std::function<void(const RefPtr<UIExtensionProxy>&)>&& callback)
{
    onRemoteReadyCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
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
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
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

void UIExtensionPattern::SetModalOnDestroy(const std::function<void()>&& callback)
{
    onModalDestroy_ = std::move(callback);
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
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    auto extSessionEventCallback = extensionSession->GetExtensionSessionEventCallback();
    extSessionEventCallback->transferAbilityResultFunc_ =
        [weak = WeakClaim(this), instanceId = instanceId_, taskExecutor](int32_t code, const AAFwk::Want& want) {
            taskExecutor->PostTask([weak, instanceId, code, want]() {
                ContainerScope scope(instanceId);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (pattern && (pattern->state_ != AbilityState::DESTRUCTION) && pattern->onResultCallback_) {
                    LOGI("UIExtension OnResult called");
                    pattern->state_ = AbilityState::DESTRUCTION;
                    pattern->onResultCallback_(code, want);
                }
            }, TaskExecutor::TaskType::UI);
        };
}

void UIExtensionPattern::SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback)
{
    onReceiveCallback_ = std::move(callback);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
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
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto uiExtension = weak.Upgrade();
        CHECK_NULL_VOID(uiExtension);
        uiExtension->OnVisibleChange(visible);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

int32_t UIExtensionPattern::GetSessionId()
{
    CHECK_NULL_RETURN(session_, 0);
    return session_->GetPersistentId();
}

void UIExtensionPattern::DispatchBackpressedEventForConsumed(bool& isConsumed)
{
    CHECK_NULL_VOID(session_);
    session_->TransferBackPressedEventForConsumed(isConsumed);
}

void UIExtensionPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(pointerEvent);
    session_->TransferPointerEvent(pointerEvent);
}

void UIExtensionPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(keyEvent);
    session_->TransferKeyEvent(keyEvent);
}

void UIExtensionPattern::DispatchKeyEventForConsumed(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed)
{
    CHECK_NULL_VOID(session_);
    session_->TransferKeyEventForConsumed(keyEvent, isConsumed);
}

void UIExtensionPattern::DisPatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusActiveEvent(isFocusActive);
}

void UIExtensionPattern::TransferFocusState(bool focusState)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusStateEvent(focusState);
}

void UIExtensionPattern::ProcessUIExtensionSessionActivationResult(OHOS::Rosen::WSError errcode)
{
    if (errcode != OHOS::Rosen::WSError::WS_OK) {
        int32_t code = static_cast<int32_t>(errcode);
        std::string name = "start_ability_fail";
        std::string message = "Start ui extension ability failed, please check the want of UIextensionAbility.";
        lastError_ = { code, name, message };
        state_ = AbilityState::NONE;
        if (onErrorCallback_) {
            ErrorMsg error;
            std::swap(lastError_, error);
            onErrorCallback_(error.code, error.name, error.message);
        }
    }
}

void UIExtensionPattern::ProcessUIExtensionSessionBackgroundResult(OHOS::Rosen::WSError errcode)
{
    if (errcode != OHOS::Rosen::WSError::WS_OK) {
        state_ = AbilityState::NONE;
        if (onErrorCallback_) {
            int32_t code = static_cast<int32_t>(errcode);
            std::string name = "background_fail";
            std::string message = "background ui extension ability failed, please check AMS log.";
            onErrorCallback_(code, name, message);
        }
    }
}

void UIExtensionPattern::ProcessUIExtensionSessionDestructionResult(OHOS::Rosen::WSError errcode)
{
    if (errcode != OHOS::Rosen::WSError::WS_OK) {
        state_ = AbilityState::NONE;
        if (onErrorCallback_) {
            int32_t code = static_cast<int32_t>(errcode);
            std::string name = "terminate_fail";
            std::string message = "terminate ui extension ability failed, please check AMS log.";
            onErrorCallback_(code, name, message);
        }
    }
}
} // namespace OHOS::Ace::NG
