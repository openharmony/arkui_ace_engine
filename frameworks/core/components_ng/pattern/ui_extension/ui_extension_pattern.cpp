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

#include "key_event.h"
#include "pointer_event.h"
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_proxy.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
UIExtensionPattern::UIExtensionPattern(bool isTransferringCaller, bool isModal)
    : isTransferringCaller_(isTransferringCaller), isModal_(isModal)
{
    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        SessionTye::UI_EXTENSION_ABILITY, AceType::WeakClaim(this), instanceId_, isTransferringCaller_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionId_ = uiExtensionManager->ApplyExtensionId();
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Id = %{public}d, TransferrCaller = %{public}d, isModal = %{public}d",
        uiExtensionId_, isTransferringCaller_, isModal_);
}

UIExtensionPattern::~UIExtensionPattern()
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension with id = %{public}d is destroyed.", uiExtensionId_);
    NotifyDestroy();
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->DestroySession();
    FireModalOnDestroy();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RecycleExtensionId(uiExtensionId_);
    uiExtensionManager->RemoveDestroyedUIExtension(GetNodeId());
}

RefPtr<LayoutAlgorithm> UIExtensionPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<UIExtensionLayoutAlgorithm>();
}

FocusPattern UIExtensionPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::NONE };
}

void UIExtensionPattern::InitializeDynamicComponent(
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint, void* runtime)
{
    componentType_ = ComponentType::DYNAMIC;

    if (!dynamicComponentRenderer_) {
        ContainerScope scope(instanceId_);
        dynamicComponentRenderer_ = DynamicComponentRenderer::Create(GetHost(), hapPath, abcPath, entryPoint, runtime);
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->CreateContent();
    }
}

void UIExtensionPattern::UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    UpdateWant(want);
}

void UIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    CHECK_NULL_VOID(sessionWrapper_);
    // Prohibit rebuilding the session unless the Want is updated.
    if (sessionWrapper_->IsSessionValid()) {
        if (sessionWrapper_->GetWant()->IsEquals(want)) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The old want is %{private}s",
            sessionWrapper_->GetWant()->ToString().c_str());
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        NotifyDestroy();
        sessionWrapper_->DestroySession();
    }
    sessionWrapper_->CreateSession(want);
    NotifyForeground();
}

void UIExtensionPattern::OnConnect()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(sessionWrapper_);
    ContainerScope scope(instanceId_);
    contentNode_ = FrameNode::CreateFrameNode(
        V2::UI_EXTENSION_SURFACE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    if (opts && opts->Expansive()) {
        contentNode_->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        contentNode_->MarkModifyDone();
    }
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto surfaceNode = sessionWrapper_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    context->SetRSNode(surfaceNode);
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    surfaceNode->SetForeground(isModal_);
    FireOnRemoteReadyCallback();
    if (isModal_) {
        auto focusHub = host->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->RequestFocusImmediately();
    }
    bool isFocused = IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));
    if (isFocused || isModal_) {
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
    }
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The UIExtensionComponent is connected.");
}

void UIExtensionPattern::OnAccessibilityEvent(
    const Accessibility::AccessibilityEventInfo& info, int64_t uiExtensionOffset)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The accessibility event is reported.");
    ContainerScope scope(instanceId_);
    auto ngPipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ngPipeline);
    uiExtensionOffset = uiExtensionId_ * NG::UI_EXTENSION_OFFSET_MAX + uiExtensionOffset;
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->SendExtensionAccessibilityEvent(info, uiExtensionOffset);
}

void UIExtensionPattern::OnDisconnect()
{
    CHECK_RUN_ON(UI);
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The session is disconnected and state = %{public}d.", state_);
    state_ = AbilityState::DESTRUCTION;
    if (onReleaseCallback_) {
        onReleaseCallback_(static_cast<int32_t>(ReleaseCode::DESTROY_NORMAL));
    }
}

void UIExtensionPattern::OnExtensionDied()
{
    CHECK_RUN_ON(UI);
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The session is died and state = %{public}d.", state_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    state_ = AbilityState::DESTRUCTION;
    if (onReleaseCallback_) {
        onReleaseCallback_(static_cast<int32_t>(ReleaseCode::CONNECT_BROKEN));
    }
}

bool UIExtensionPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (componentType_ == ComponentType::DYNAMIC) {
        return OnDirtyLayoutWrapperSwapForDynamicComponent(dirty, config);
    }

    CHECK_NULL_RETURN(sessionWrapper_, false);
    CHECK_NULL_RETURN(dirty, false);
    auto host = dirty->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto [globalOffsetWithTranslate, err] = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto frameRect = geometryNode->GetFrameRect();
    sessionWrapper_->RefreshDisplayArea(
        globalOffsetWithTranslate.GetX(), globalOffsetWithTranslate.GetY(), frameRect.Width(), frameRect.Height());
    return false;
}

bool UIExtensionPattern::OnDirtyLayoutWrapperSwapForDynamicComponent(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);

    CHECK_NULL_RETURN(dirty, false);
    auto host = dirty->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto offset = host->GetPaintRectGlobalOffsetWithTranslate().first;
    auto size = dirty->GetGeometryNode()->GetFrameSize();
    Ace::ViewportConfig vpConfig;
    vpConfig.SetSize(size.Width(), size.Height());
    vpConfig.SetPosition(offset.GetX(), offset.GetY());
    float density = 1.0f;
    int32_t orientation = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        orientation = static_cast<int32_t>(defaultDisplay->GetOrientation());
    }
    vpConfig.SetDensity(density);
    vpConfig.SetOrientation(orientation);
    dynamicComponentRenderer_->UpdateViewportConfig(vpConfig, Rosen::WindowSizeChangeReason::UNDEFINED, nullptr);
    return false;
}

void UIExtensionPattern::OnWindowShow()
{
    if (isVisible_) {
        NotifyForeground();
    }
}

void UIExtensionPattern::OnWindowHide()
{
    if (isVisible_) {
        NotifyBackground();
    }
}

void UIExtensionPattern::NotifyForeground()
{
    if (state_ != AbilityState::FOREGROUND) {
        state_ = AbilityState::FOREGROUND;
        sessionWrapper_->NotifyForeground();
    }
}

void UIExtensionPattern::NotifyBackground()
{
    if (state_ == AbilityState::FOREGROUND) {
        state_ = AbilityState::BACKGROUND;
        sessionWrapper_->NotifyBackground();
    }
}

void UIExtensionPattern::NotifyDestroy()
{
    if (state_ != AbilityState::DESTRUCTION && state_ != AbilityState::NONE) {
        state_ = AbilityState::DESTRUCTION;
        sessionWrapper_->NotifyDestroy();
    }
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (componentType_ == ComponentType::DYNAMIC) {
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->DestroyContent();
        dynamicComponentRenderer_ = nullptr;
        return;
    }

    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
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
    InitHoverEvent(inputHub);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitKeyEvent(focusHub);
}

void UIExtensionPattern::InitKeyEvent(const RefPtr<FocusHub>& focusHub)
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

void UIExtensionPattern::InitHoverEvent(const RefPtr<InputEventHub>& inputHub)
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

bool UIExtensionPattern::HandleKeyEvent(const KeyEvent& event)
{
    return DispatchKeyEventSync(event.rawKeyEvent);
}

void UIExtensionPattern::HandleFocusEvent()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline->GetIsFocusActive()) {
        DispatchFocusActiveEvent(true);
    }
    DispatchFocusState(true);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
}

void UIExtensionPattern::HandleBlurEvent()
{
    DispatchFocusActiveEvent(false);
    DispatchFocusState(false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->RegisterUIExtensionInFocus(nullptr, nullptr);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto window = static_cast<RosenWindow*>(pipeline->GetWindow());
    CHECK_NULL_VOID(window);
    auto rsWindow = window->GetRSWindow();
    auto udegree = WindowPattern::CalculateTranslateDegree(host->GetId());
    if (rsWindow->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD) {
        Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale, udegree);
    } else {
        Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale, udegree);
    }
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    lastPointerEvent_ = pointerEvent;
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
    DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::HandleHoverEvent(bool isHover)
{
    if (isHover) {
        return;
    }
    CHECK_NULL_VOID(lastPointerEvent_);
    lastPointerEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    DispatchPointerEvent(lastPointerEvent_);
}

void UIExtensionPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(keyEvent);
    if (componentType_ == ComponentType::DYNAMIC) {
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->TransferKeyEvent(keyEvent);
    } else if (sessionWrapper_) {
        sessionWrapper_->NotifyKeyEventAsync(keyEvent);
    }
}

bool UIExtensionPattern::DispatchKeyEventSync(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    return sessionWrapper_ && sessionWrapper_->NotifyKeyEventSync(keyEvent);
}

void UIExtensionPattern::DispatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyFocusEventAsync(isFocusActive);
}

void UIExtensionPattern::DispatchFocusState(bool focusState)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyFocusStateAsync(focusState);
}

void UIExtensionPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    if (componentType_ == ComponentType::DYNAMIC) {
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->TransferPointerEvent(pointerEvent);
    } else if (sessionWrapper_) {
        sessionWrapper_->NotifyPointerEventAsync(pointerEvent);
    }
}

void UIExtensionPattern::HandleDragEvent(const PointerEvent& info)
{
    const auto pointerEvent = info.rawPointerEvent;
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selfGlobalOffset = host->GetTransformRelativeOffset();
    auto scale = host->GetTransformScale();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto window = static_cast<RosenWindow*>(pipeline->GetWindow());
    CHECK_NULL_VOID(window);
    auto rsWindow = window->GetRSWindow();
    auto udegree = WindowPattern::CalculateTranslateDegree(host->GetId());
    if (rsWindow->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD) {
        Platform::CalculateWindowCoordinate(selfGlobalOffset, pointerEvent, scale, udegree);
    } else {
        Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, scale, udegree);
    }
    DispatchPointerEvent(pointerEvent);
}

void UIExtensionPattern::SetOnRemoteReadyCallback(const std::function<void(const RefPtr<UIExtensionProxy>&)>&& callback)
{
    onRemoteReadyCallback_ = std::move(callback);
}

void UIExtensionPattern::SetModalOnRemoteReadyCallback(
    const std::function<void(const std::shared_ptr<ModalUIExtensionProxy>&)>&& callback)
{
    onModalRemoteReadyCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnRemoteReadyCallback()
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The onRemoteReady is called and state = %{public}d.", state_);
    ContainerScope scope(instanceId_);
    // These two callbacks will be unified in the future.
    if (onRemoteReadyCallback_) {
        onRemoteReadyCallback_(MakeRefPtr<UIExtensionProxy>(sessionWrapper_, Claim(this)));
    }
    if (onModalRemoteReadyCallback_) {
        onModalRemoteReadyCallback_(std::make_shared<ModalUIExtensionProxyImpl>(sessionWrapper_));
    }
}

void UIExtensionPattern::SetModalOnDestroy(const std::function<void()>&& callback)
{
    onModalDestroy_ = std::move(callback);
}

void UIExtensionPattern::FireModalOnDestroy()
{
    // Native modal page destroy callback
    if (onModalDestroy_) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The onModalDestroy is called and state = %{public}d.", state_);
        ContainerScope scope(instanceId_);
        onModalDestroy_();
    }
}

void UIExtensionPattern::SetOnReleaseCallback(const std::function<void(int32_t)>&& callback)
{
    onReleaseCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnReleaseCallback(int32_t releaseCode)
{
    state_ = AbilityState::DESTRUCTION;
    if (onReleaseCallback_) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The onRelease is called and state = %{public}d.", state_);
        onReleaseCallback_(static_cast<int32_t>(ReleaseCode::DESTROY_NORMAL));
    }
}

void UIExtensionPattern::SetOnErrorCallback(
    const std::function<void(int32_t code, const std::string& name, const std::string& message)>&& callback)
{
    onErrorCallback_ = std::move(callback);
    if (lastError_.code != 0) {
        ErrorMsg error;
        std::swap(lastError_, error);
        FireOnErrorCallback(error.code, error.name, error.message);
    }
}

void UIExtensionPattern::FireOnErrorCallback(int32_t code, const std::string& name, const std::string& message)
{
    // 1. As long as the error occurs, the host believes that UIExtensionAbility has been killed.
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Error: state = %{public}d, code=%{public}d, name=%{public}s", state_,
        code, name.c_str());
    state_ = AbilityState::NONE;
    if (onErrorCallback_) {
        ContainerScope scope(instanceId_);
        onErrorCallback_(code, name, message);
        return;
    }
    lastError_ = { code, name, message };
}

void UIExtensionPattern::SetOnResultCallback(const std::function<void(int32_t, const AAFwk::Want&)>&& callback)
{
    onResultCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnResultCallback(int32_t code, const AAFwk::Want& want)
{
    if (onResultCallback_ && (state_ != AbilityState::DESTRUCTION)) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The onResult is called and state = %{public}d.", state_);
        ContainerScope scope(instanceId_);
        onResultCallback_(code, want);
    }
    state_ = AbilityState::DESTRUCTION;
}

void UIExtensionPattern::SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback)
{
    onReceiveCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnReceiveCallback(const AAFwk::WantParams& params)
{
    if (onReceiveCallback_) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The onReceive is called and state = %{public}d.", state_);
        ContainerScope scope(instanceId_);
        onReceiveCallback_(params);
    }
}

void UIExtensionPattern::SetSyncCallbacks(
    const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList)
{
    onSyncOnCallbackList_ = std::move(callbackList);
}

void UIExtensionPattern::FireSyncCallbacks()
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The size of sync callbacks = %{public}zu and state = %{public}d.",
        onSyncOnCallbackList_.size(), state_);
    ContainerScope scope(instanceId_);
    for (const auto& callback : onSyncOnCallbackList_) {
        if (callback) {
            callback(MakeRefPtr<UIExtensionProxy>(sessionWrapper_, Claim(this)));
        }
    }
}

void UIExtensionPattern::SetAsyncCallbacks(
    const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList)
{
    onAsyncOnCallbackList_ = std::move(callbackList);
}

void UIExtensionPattern::FireAsyncCallbacks()
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "The size of async callbacks = %{public}zu and state = %{public}d.",
        onSyncOnCallbackList_.size(), state_);
    ContainerScope scope(instanceId_);
    for (const auto& callback : onAsyncOnCallbackList_) {
        if (callback) {
            callback(MakeRefPtr<UIExtensionProxy>(sessionWrapper_, Claim(this)));
        }
    }
}

void UIExtensionPattern::OnVisibleChange(bool visible)
{
    isVisible_ = visible;
    if (visible) {
        NotifyForeground();
    } else {
        NotifyBackground();
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

bool UIExtensionPattern::IsCurrentFocus() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void UIExtensionPattern::OnLanguageConfigurationUpdate()
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyConfigurationUpdate();
}

void UIExtensionPattern::OnColorConfigurationUpdate()
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyConfigurationUpdate();
}

int32_t UIExtensionPattern::GetSessionId()
{
    return sessionWrapper_ ? sessionWrapper_->GetSessionId() : 0;
}

int32_t UIExtensionPattern::GetUiExtensionId()
{
    return uiExtensionId_;
}

int32_t UIExtensionPattern::GetNodeId()
{
    auto host = GetHost();
    return host ? host->GetId() : -1;
}

int32_t UIExtensionPattern::GetInstanceId()
{
    return instanceId_;
}

void UIExtensionPattern::DispatchOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyOriginAvoidArea(avoidArea, type);
}

bool UIExtensionPattern::NotifyOccupiedAreaChangeInfo(const sptr<Rosen::OccupiedAreaChangeInfo>& info)
{
    return sessionWrapper_ && sessionWrapper_->NotifyOccupiedAreaChangeInfo(info);
}

int64_t UIExtensionPattern::WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
{
    return uiExtensionId_ * extensionOffset + abilityId;
}

void UIExtensionPattern::SearchExtensionElementInfoByAccessibilityId(
    int64_t elementId, int32_t mode, int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->SearchExtensionElementInfoByAccessibilityId(elementId, mode, baseParent, output);
}

void UIExtensionPattern::SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
    std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->SearchElementInfosByText(elementId, text, baseParent, output);
}

void UIExtensionPattern::FindFocusedElementInfo(
    int64_t elementId, int32_t focusType, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->FindFocusedElementInfo(elementId, focusType, baseParent, output);
}

void UIExtensionPattern::FocusMoveSearch(
    int64_t elementId, int32_t direction, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->FocusMoveSearch(elementId, direction, baseParent, output);
}

bool UIExtensionPattern::TransferExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    return sessionWrapper_ && sessionWrapper_->TransferExecuteAction(elementId, actionArguments, action, offset);
}
} // namespace OHOS::Ace::NG
