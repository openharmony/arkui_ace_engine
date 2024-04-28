/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include <optional>

#include "core/event/key_event.h"
#include "core/event/pointer_event.h"
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
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
UIExtensionPattern::UIExtensionPattern(
    bool isTransferringCaller, bool isModal, bool isAsyncModalBinding, SessionType sessionType)
    : isTransferringCaller_(isTransferringCaller), isModal_(isModal), isAsyncModalBinding_(isAsyncModalBinding)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionId_ = uiExtensionManager->ApplyExtensionId();
    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        sessionType, WeakClaim(this), instanceId_, isTransferringCaller_);
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterUIExtension>(sessionWrapper_);
    UIEXT_LOGI("The %{public}smodal UIExtension is created.", isModal_ ? "" : "non");
}

UIExtensionPattern::~UIExtensionPattern()
{
    UIEXT_LOGI("The %{public}smodal UIExtension is destroyed.", isModal_ ? "" : "non");
    NotifyDestroy();
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
    return { FocusType::NODE, true, FocusStyleType::FORCE_NONE };
}

RefPtr<AccessibilitySessionAdapter> UIExtensionPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
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

void UIExtensionPattern::MountPlaceholderNode()
{
    if (!isShowPlaceholder_ && placeholderNode_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->AddChild(placeholderNode_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        isShowPlaceholder_ = true;
    }
}

void UIExtensionPattern::RemovePlaceholderNode()
{
    if (isShowPlaceholder_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChildAtIndex(0);
        isShowPlaceholder_ = false;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void UIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    CHECK_NULL_VOID(sessionWrapper_);
    // Prohibit rebuilding the session unless the Want is updated.
    if (sessionWrapper_->IsSessionValid()) {
        if (sessionWrapper_->GetWant()->IsEquals(want)) {
            return;
        }
        UIEXT_LOGI("The old want is %{private}s.", sessionWrapper_->GetWant()->ToString().c_str());
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        NotifyDestroy();
    }
    MountPlaceholderNode();
    sessionWrapper_->CreateSession(want, isAsyncModalBinding_);
    NotifyForeground();
}

void UIExtensionPattern::OnConnect()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("The session is connected and the current state is '%{public}s'.", ToString(state_));
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
    RemovePlaceholderNode();
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    surfaceNode->SetForeground(isModal_);
    FireOnRemoteReadyCallback();
    auto focusHub = host->GetFocusHub();
    if (isModal_ && focusHub) {
        focusHub->RequestFocusImmediately();
    }
    bool isFocused = focusHub && focusHub->IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));
    if (isFocused || isModal_) {
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
    }
}

void UIExtensionPattern::OnAccessibilityEvent(
    const Accessibility::AccessibilityEventInfo& info, int64_t uiExtensionOffset)
{
    UIEXT_LOGI("The accessibility event is reported and the current state is '%{public}s'.", ToString(state_));
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

void UIExtensionPattern::OnDisconnect(bool isAbnormal)
{
    CHECK_RUN_ON(UI);
    UIEXT_LOGI("The session is disconnected and the current state is '%{public}s'.", ToString(state_));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void UIExtensionPattern::OnAreaChangedInner()
{
    DispatchDisplayArea();
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
    auto [displayOffset, err] = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto displaySize = geometryNode->GetFrameSize();
    displayArea_ = RectF(displayOffset, displaySize);
    sessionWrapper_->NotifyDisplayArea(displayArea_);
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
    UIEXT_LOGI("The window is being shown and the component is %{public}s.", isVisible_ ? "visible" : "invisible");
    if (isVisible_) {
        NotifyForeground();
    }
}

void UIExtensionPattern::OnWindowHide()
{
    UIEXT_LOGI("The window is being hidden and the component is %{public}s.", isVisible_ ? "visible" : "invisible");
    if (isVisible_) {
        NotifyBackground();
    }
}

void UIExtensionPattern::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifySizeChangeReason(type, rsTransaction);
}

void UIExtensionPattern::NotifyForeground()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ != AbilityState::FOREGROUND) {
        UIEXT_LOGI("The state is changing from '%{public}s' to 'FOREGROUND'.", ToString(state_));
        state_ = AbilityState::FOREGROUND;
        sessionWrapper_->NotifyForeground();
    }
}

void UIExtensionPattern::NotifyBackground()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ == AbilityState::FOREGROUND) {
        UIEXT_LOGI("The state is changing from '%{public}s' to 'BACKGROUND'.", ToString(state_));
        state_ = AbilityState::BACKGROUND;
        sessionWrapper_->NotifyBackground();
    }
}

void UIExtensionPattern::NotifyDestroy()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ != AbilityState::DESTRUCTION &&
        state_ != AbilityState::NONE) {
        UIEXT_LOGI("The state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
        state_ = AbilityState::DESTRUCTION;
        sessionWrapper_->NotifyDestroy();
        sessionWrapper_->DestroySession();
    }
}

void UIExtensionPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->AddOnAreaChangeNode(host->GetId());
    callbackId_ = pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t, int32_t) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->DispatchDisplayArea(true);
        }
    });
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
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->UnregisterSurfacePositionChangedCallback(callbackId_);
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
    return DispatchKeyEventSync(event);
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
    AceExtraInputData::InsertInterpolatePoints(info);
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

void UIExtensionPattern::DispatchKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_VOID(event.rawKeyEvent);
    if (componentType_ == ComponentType::DYNAMIC) {
        CHECK_NULL_VOID(dynamicComponentRenderer_);
        dynamicComponentRenderer_->TransferKeyEvent(event.rawKeyEvent);
    } else if (sessionWrapper_) {
        sessionWrapper_->NotifyKeyEventAsync(event.rawKeyEvent);
    }
}

bool UIExtensionPattern::DispatchKeyEventSync(const KeyEvent& event)
{
    return sessionWrapper_ && sessionWrapper_->NotifyKeyEventSync(event.rawKeyEvent, event.isPreIme);
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

void UIExtensionPattern::DispatchDisplayArea(bool isForce)
{
    CHECK_NULL_VOID(sessionWrapper_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto [displayOffset, err] = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto displaySize = geometryNode->GetFrameSize();
    auto displayArea = RectF(displayOffset, displaySize);
    if (displayArea_ != displayArea || isForce) {
        displayArea_ = displayArea;
        sessionWrapper_->NotifyDisplayArea(displayArea_);
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
    UIEXT_LOGD("The current state is '%{public}s'.", ToString(state_));
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
    UIEXT_LOGD("The current state is '%{public}s'.", ToString(state_));
    // Native modal page destroy callback
    if (onModalDestroy_) {
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
    UIEXT_LOGD("The state is changing from '%{public}s' to 'DESTRUCTION' and releaseCode = %{public}d.",
        ToString(state_), releaseCode);
    state_ = AbilityState::DESTRUCTION;
    if (onReleaseCallback_) {
        onReleaseCallback_(releaseCode);
    }
    // Release the session.
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        sessionWrapper_->DestroySession();
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
    UIEXT_LOGD("The state is changing from '%{public}s' to 'NONE'.", ToString(state_));
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
    UIEXT_LOGD("The state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
    if (onResultCallback_ && (state_ != AbilityState::DESTRUCTION)) {
        ContainerScope scope(instanceId_);
        onResultCallback_(code, want);
    }
    state_ = AbilityState::DESTRUCTION;
}

void UIExtensionPattern::SetOnTerminatedCallback(
    const std::function<void(int32_t, const RefPtr<WantWrap>& wantWrap)>&& callback)
{
    onTerminatedCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnTerminatedCallback(int32_t code, const RefPtr<WantWrap>& wantWrap)
{
    UIEXT_LOGD("The state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
    if (onTerminatedCallback_ && (state_ != AbilityState::DESTRUCTION)) {
        ContainerScope scope(instanceId_);
        onTerminatedCallback_(code, wantWrap);
    }
    state_ = AbilityState::DESTRUCTION;
}

void UIExtensionPattern::SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback)
{
    onReceiveCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnReceiveCallback(const AAFwk::WantParams& params)
{
    UIEXT_LOGD("The current state is '%{public}s'.", ToString(state_));
    if (onReceiveCallback_) {
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
    UIEXT_LOGD("The size of sync callbacks = %{public}zu.", onSyncOnCallbackList_.size());
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
    UIEXT_LOGD("The size of async callbacks = %{public}zu.", onSyncOnCallbackList_.size());
    ContainerScope scope(instanceId_);
    for (const auto& callback : onAsyncOnCallbackList_) {
        if (callback) {
            callback(MakeRefPtr<UIExtensionProxy>(sessionWrapper_, Claim(this)));
        }
    }
}

void UIExtensionPattern::SetBindModalCallback(const std::function<void()>&& callback)
{
    bindModalCallback_ = std::move(callback);
}

void UIExtensionPattern::FireBindModalCallback()
{
    if (bindModalCallback_) {
        bindModalCallback_();
    }
}

void UIExtensionPattern::OnVisibleChange(bool visible)
{
    UIEXT_LOGI("The component is changing from '%{public}s' to '%{public}s'.", isVisible_ ? "visible" : "invisible",
        visible ? "visible" : "invisible");
    isVisible_ = visible;
    if (visible) {
        NotifyForeground();
    } else {
        NotifyBackground();
    }
}

void UIExtensionPattern::OnMountToParentDone()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetNodeStatus() == NodeStatus::NORMAL_NODE) {
        UIEXT_LOGD("Frame node status is normal.");
        return;
    }
    auto wantWrap = GetWantWrap();
    CHECK_NULL_VOID(wantWrap);
    UpdateWant(wantWrap);
    SetWantWrap(nullptr);
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
    std::vector<double> ratioList = { 0.0 };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
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

void UIExtensionPattern::SetWantWrap(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    curWant_ = wantWrap;
}

RefPtr<OHOS::Ace::WantWrap> UIExtensionPattern::GetWantWrap()
{
    return curWant_;
}

int64_t UIExtensionPattern::WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
{
    return uiExtensionId_ * extensionOffset + abilityId;
}

const char* UIExtensionPattern::ToString(AbilityState state)
{
    switch (state) {
        case AbilityState::FOREGROUND:
            return "FOREGROUND";
        case AbilityState::BACKGROUND:
            return "BACKGROUND";
        case AbilityState::DESTRUCTION:
            return "DESTRUCTION";
        case AbilityState::NONE:
        default:
            return "NONE";
    }
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
