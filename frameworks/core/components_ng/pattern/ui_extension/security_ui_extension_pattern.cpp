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

#include "core/components_ng/pattern/ui_extension/security_ui_extension_pattern.h"

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
#include "base/error/error_code.h"
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
namespace {
constexpr char PROHIBIT_NESTING_FAIL_NAME[] = "Prohibit_Nesting_SecurityUIExtensionComponent";
constexpr char PROHIBIT_NESTING_FAIL_MESSAGE[] =
    "Prohibit nesting securityUIExtensionComponent in securityUIExtensionAbility";
constexpr char PROHIBIT_NESTING_FAIL_IN_UEC_NAME[] = "Prohibit_Nesting_UIExtensionComponent";
constexpr char PROHIBIT_NESTING_FAIL_IN_UEC_MESSAGE[] =
    "Prohibit nesting securityUIExtensionComponent in uIExtensionAbility";
constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
}

SecurityUIExtensionPattern::SecurityUIExtensionPattern()
    : PlatformPattern::PlatformPattern(AceLogTag::ACE_SECURITYUIEXTENSION, 0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionId_ = uiExtensionManager->ApplyExtensionId();
    platformId_ = uiExtensionId_;
    PLATFORM_LOGI("The Security UIExtension is created.");
}

SecurityUIExtensionPattern::~SecurityUIExtensionPattern()
{
    PLATFORM_LOGI("The Security UIExtension is destroyed.");
    NotifyDestroy();
    UnregisterResources();
}

void SecurityUIExtensionPattern::UnregisterResources()
{
    PLATFORM_LOGI("UnregisterResources.");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RecycleExtensionId(uiExtensionId_);
    uiExtensionManager->RemoveDestroyedUIExtension(GetNodeId());
}

void SecurityUIExtensionPattern::Initialize(const NG::UIExtensionConfig& config)
{
    if (sessionWrapper_ != nullptr) {
        return;
    }

    sessionType_ = config.sessionType;
    SessionCreateParam sessionCreateParam;
    sessionCreateParam.hostPattern = WeakClaim(this);
    sessionCreateParam.instanceId = instanceId_;
    sessionCreateParam.isTransferringCaller = config.transferringCaller;
    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        config.sessionType, sessionCreateParam);
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterUIExtension>(sessionWrapper_);
}

RefPtr<LayoutAlgorithm> SecurityUIExtensionPattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<UIExtensionLayoutAlgorithm>();
}

FocusPattern SecurityUIExtensionPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::FORCE_NONE };
}

RefPtr<AccessibilitySessionAdapter> SecurityUIExtensionPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void SecurityUIExtensionPattern::OnExtensionDetachToDisplay()
{
    if (contentNode_ == nullptr) {
        PLATFORM_LOGW("ContentNode is null when OnExtensionDetachToDisplay.");
        return;
    }

    PLATFORM_LOGI("OnExtensionDetachToDisplay");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SecurityUIExtensionPattern::UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    if (!wantWrap) {
        PLATFORM_LOGW("wantWrap is nullptr");
        return;
    }
    auto wantWrapOhos = AceType::DynamicCast<WantWrapOhos>(wantWrap);
    if (!wantWrapOhos) {
        PLATFORM_LOGW("DynamicCast failed, wantWrapOhos is nullptr");
        return;
    }
    auto want = wantWrapOhos->GetWant();
    UpdateWant(want);
}

bool SecurityUIExtensionPattern::CheckConstraint()
{
#if defined(PREVIEW)
    PLATFORM_LOGE("No support preview.");
    return false;
#else
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    if (container->GetUIContentType() == UIContentType::SECURITY_UI_EXTENSION) {
        PLATFORM_LOGE("Not allowed nesting in SECURITY_UI_EXTENSION.");
        FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE,
            PROHIBIT_NESTING_FAIL_NAME, PROHIBIT_NESTING_FAIL_MESSAGE);
        return false;
    }

    if (container->IsUIExtensionWindow()) {
        PLATFORM_LOGE("Not allowed nesting in UI_EXTENSION.");
        FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE,
            PROHIBIT_NESTING_FAIL_IN_UEC_NAME, PROHIBIT_NESTING_FAIL_IN_UEC_MESSAGE);
        return false;
    }

    return true;
#endif
}

void SecurityUIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    uiExtensionType_ = want.GetStringParam(UI_EXTENSION_TYPE_KEY);
    if (!CheckConstraint()) {
        PLATFORM_LOGE("Check constraint failed.");
        return;
    }

    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("The current state is '%{public}s' when UpdateWant.", ToString(state_));
    bool isBackground = state_ == AbilityState::BACKGROUND;
    // Prohibit rebuilding the session unless the Want is updated.
    if (sessionWrapper_->IsSessionValid()) {
        auto sessionWant = sessionWrapper_->GetWant();
        if (sessionWant == nullptr) {
            PLATFORM_LOGW("The sessionWrapper want is nulllptr.");
            return;
        }
        if (sessionWant->IsEquals(want)) {
            return;
        }
        PLATFORM_LOGI("The old want bundle = %{public}s, ability = %{public}s",
            sessionWant->GetElement().GetBundleName().c_str(), sessionWant->GetElement().GetAbilityName().c_str());
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        NotifyDestroy();
        // reset callback, in order to register childtree call back again when onConnect to new ability
        ResetAccessibilityChildTreeCallback();
    }

    MountPlaceholderNode();
    SessionConfig config;
    config.uiExtensionUsage = UIExtensionUsage::CONSTRAINED_EMBEDDED;
    sessionWrapper_->CreateSession(want, config);
    if (isBackground) {
        PLATFORM_LOGW("Unable to StartUiextensionAbility while in the background.");
        return;
    }
    NotifyForeground();
}

void SecurityUIExtensionPattern::MountPlaceholderNode()
{
    if (!isShowPlaceholder_ && placeholderNode_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->AddChild(placeholderNode_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        isShowPlaceholder_ = true;
    }
}

void SecurityUIExtensionPattern::RemovePlaceholderNode()
{
    if (isShowPlaceholder_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChildAtIndex(0);
        isShowPlaceholder_ = false;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SecurityUIExtensionPattern::OnConnect()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("The session is connected and the current state is '%{public}s'.", ToString(state_));
    ContainerScope scope(instanceId_);
    contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
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
    if (!surfaceNode) {
        PLATFORM_LOGE("Get surfaceNode from session is null.");
        return;
    }
    context->SetRSNode(surfaceNode);
    RemovePlaceholderNode();
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    FireOnRemoteReadyCallback();
    auto focusHub = host->GetFocusHub();
    bool isFocused = focusHub && focusHub->IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    DispatchFollowHostDensity(GetDensityDpi());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));
    if (isFocused) {
        uiExtensionManager->RegisterSecurityUIExtensionInFocus(
            WeakClaim(this), sessionWrapper_);
    }
}

void SecurityUIExtensionPattern::OnDisconnect(bool isAbnormal)
{
    CHECK_RUN_ON(UI);
    PLATFORM_LOGI("The session is disconnected and the current state is '%{public}s'.", ToString(state_));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SecurityUIExtensionPattern::FireBindModalCallback()
{}

void SecurityUIExtensionPattern::OnSyncGeometryNode(const DirtySwapConfig& config)
{
    DispatchDisplayArea(true);
}

void SecurityUIExtensionPattern::OnWindowShow()
{
    PLATFORM_LOGI("The window is being shown and the component is %{public}s.",
        isVisible_ ? "visible" : "invisible");
    if (isVisible_) {
        NotifyForeground();
    }
}

void SecurityUIExtensionPattern::OnWindowHide()
{
    PLATFORM_LOGI("The window is being hidden and the component is %{public}s.",
        isVisible_ ? "visible" : "invisible");
    if (isVisible_) {
        NotifyBackground();
    }
}

void SecurityUIExtensionPattern::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifySizeChangeReason(type, rsTransaction);
}

void SecurityUIExtensionPattern::NotifyForeground()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ != AbilityState::FOREGROUND) {
        PLATFORM_LOGI("The state is changing from '%{public}s' to 'FOREGROUND'.", ToString(state_));
        state_ = AbilityState::FOREGROUND;
        sessionWrapper_->NotifyForeground();
    }
}

void SecurityUIExtensionPattern::NotifyBackground()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ == AbilityState::FOREGROUND) {
        PLATFORM_LOGI("The state is changing from '%{public}s' to 'BACKGROUND'.", ToString(state_));
        state_ = AbilityState::BACKGROUND;
        sessionWrapper_->NotifyBackground();
    }
}

void SecurityUIExtensionPattern::NotifyDestroy()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ != AbilityState::DESTRUCTION &&
        state_ != AbilityState::NONE) {
        PLATFORM_LOGI("The state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
        state_ = AbilityState::DESTRUCTION;
        sessionWrapper_->NotifyDestroy();
        sessionWrapper_->DestroySession();
    }
}

void SecurityUIExtensionPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onAreaChangedFunc = [weak = WeakClaim(this)](
        const RectF& oldRect,
        const OffsetF& oldOrigin,
        const RectF& rect,
        const OffsetF& origin) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->DispatchDisplayArea();
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));
    pipeline->AddOnAreaChangeNode(host->GetId());
    callbackId_ = pipeline->RegisterSurfacePositionChangedCallback(
        [weak = WeakClaim(this)](int32_t, int32_t) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->DispatchDisplayArea(true);
            }
        });
    PLATFORM_LOGI("OnAttachToFrameNode");
}

void SecurityUIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->UnregisterSurfacePositionChangedCallback(callbackId_);
}

void SecurityUIExtensionPattern::OnModifyDone()
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

bool SecurityUIExtensionPattern::HandleKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_RETURN(sessionWrapper_, false);
    if (!(event.IsDirectionalKey() || event.IsKey({ KeyCode::KEY_TAB }) || event.IsShiftWith(KeyCode::KEY_TAB) ||
        event.IsKey({ KeyCode::KEY_MOVE_HOME }) || event.IsKey({ KeyCode::KEY_MOVE_END }) || event.IsEscapeKey())) {
        return false;
    }
    return sessionWrapper_->NotifyKeyEventSync(event.rawKeyEvent, event.isPreIme);
}

void SecurityUIExtensionPattern::HandleFocusEvent()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        DispatchFocusActiveEvent(true);
    }
    DispatchFocusState(true);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RegisterSecurityUIExtensionInFocus(
        WeakClaim(this), sessionWrapper_);
}

void SecurityUIExtensionPattern::SetEventProxyFlag(int32_t flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (flag != static_cast<int32_t>(EventProxyFlag::EVENT_NONE)
        && platformEventProxy_ == nullptr) {
        platformEventProxy_ = MakeRefPtr<PlatformEventProxy>();
        platformEventProxy_->SetHostNode(host);
    }

    if (platformEventProxy_ != nullptr) {
        platformEventProxy_->SetEventProxyFlag(flag);
    }
}

void SecurityUIExtensionPattern::HandleBlurEvent()
{
    DispatchFocusActiveEvent(false);
    DispatchFocusState(false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RegisterSecurityUIExtensionInFocus(nullptr, nullptr);
}

void SecurityUIExtensionPattern::DispatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyFocusEventAsync(isFocusActive);
}

void SecurityUIExtensionPattern::DispatchFocusState(bool focusState)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyFocusStateAsync(focusState);
}

void SecurityUIExtensionPattern::DispatchDisplayArea(bool isForce)
{
    CHECK_NULL_VOID(sessionWrapper_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto [displayOffset, err] = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto displaySize = renderContext->GetPaintRectWithoutTransform().GetSize();
    auto displayArea = RectF(displayOffset, displaySize);
    if (displayArea_ != displayArea || isForce) {
        displayArea_ = displayArea;
        sessionWrapper_->NotifyDisplayArea(displayArea_);
    }
}

void SecurityUIExtensionPattern::FireOnRemoteReadyCallback()
{
    PLATFORM_LOGI("The current state is '%{public}s'.", ToString(state_));
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnRemoteReadyCallback(
        MakeRefPtr<NG::SecurityUIExtensionProxy>(sessionWrapper_, Claim(this)));
}

void SecurityUIExtensionPattern::FireOnTerminatedCallback(
    int32_t code, const RefPtr<WantWrap>& wantWrap)
{
    PLATFORM_LOGI("The state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
    if (state_ == AbilityState::DESTRUCTION) {
        PLATFORM_LOGW("The state has DESTRUCTION when OnTerminated %{public}d.", code);
        return;
    }

    state_ = AbilityState::DESTRUCTION;
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        PLATFORM_LOGI("DestroySession.");
        sessionWrapper_->DestroySession();
    }

    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnTerminatedCallback(code, wantWrap);
}

void SecurityUIExtensionPattern::FireOnErrorCallback(
    int32_t code, const std::string& name, const std::string& message)
{
    state_ = AbilityState::NONE;
    PlatformPattern::FireOnErrorCallback(code, name, message);
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        sessionWrapper_->DestroySession();
    }
}

void SecurityUIExtensionPattern::FireOnReceiveCallback(const AAFwk::WantParams& params)
{
    PLATFORM_LOGI("The current state is '%{public}s'.", ToString(state_));
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnReceiveCallback(params);
}

void SecurityUIExtensionPattern::SetSyncCallbacks(
    const std::list<std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>>&& callbackList)
{
    onSyncOnCallbackList_ = std::move(callbackList);
}

void SecurityUIExtensionPattern::FireSyncCallbacks()
{
    PLATFORM_LOGI("The size of sync callbacks = %{public}zu.", onSyncOnCallbackList_.size());
    ContainerScope scope(instanceId_);
    for (const auto& callback : onSyncOnCallbackList_) {
        if (callback) {
            callback(MakeRefPtr<SecurityUIExtensionProxy>(sessionWrapper_, Claim(this)));
        }
    }
}

void SecurityUIExtensionPattern::SetAsyncCallbacks(
    const std::list<std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>>&& callbackList)
{
    onAsyncOnCallbackList_ = std::move(callbackList);
}

void SecurityUIExtensionPattern::FireAsyncCallbacks()
{
    PLATFORM_LOGI("The size of async callbacks = %{public}zu.", onSyncOnCallbackList_.size());
    ContainerScope scope(instanceId_);
    for (const auto& callback : onAsyncOnCallbackList_) {
        if (callback) {
            callback(MakeRefPtr<SecurityUIExtensionProxy>(sessionWrapper_, Claim(this)));
        }
    }
}

void SecurityUIExtensionPattern::SetDensityDpi(bool densityDpi)
{
    densityDpi_ = densityDpi;
}

void SecurityUIExtensionPattern::DispatchFollowHostDensity(bool densityDpi)
{
    densityDpi_ = densityDpi;
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->SetDensityDpiImpl(densityDpi_);
}

void SecurityUIExtensionPattern::OnDpiConfigurationUpdate()
{
    if (GetDensityDpi()) {
        DispatchFollowHostDensity(true);
    }
}

bool SecurityUIExtensionPattern::GetDensityDpi()
{
    return densityDpi_;
}

void SecurityUIExtensionPattern::OnVisibleChange(bool visible)
{
    PLATFORM_LOGI("The component is changing from '%{public}s' to '%{public}s'.",
        isVisible_ ? "visible" : "invisible", visible ? "visible" : "invisible");
    isVisible_ = visible;
    if (visible) {
        NotifyForeground();
    } else {
        NotifyBackground();
    }
}

void SecurityUIExtensionPattern::OnMountToParentDone()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetNodeStatus() == NodeStatus::NORMAL_NODE) {
        PLATFORM_LOGI("Frame node status is normal.");
        return;
    }

    PLATFORM_LOGI("OnMountToParentDone.");
    auto wantWrap = GetWantWrap();
    CHECK_NULL_VOID(wantWrap);
    UpdateWant(wantWrap);
    SetWantWrap(nullptr);
}

void SecurityUIExtensionPattern::RegisterVisibleAreaChange()
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

void SecurityUIExtensionPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
}

void SecurityUIExtensionPattern::OnLanguageConfigurationUpdate()
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyConfigurationUpdate();
}

void SecurityUIExtensionPattern::OnColorConfigurationUpdate()
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyConfigurationUpdate();
}

int32_t SecurityUIExtensionPattern::GetSessionId()
{
    return sessionWrapper_ ? sessionWrapper_->GetSessionId() : 0;
}

int32_t SecurityUIExtensionPattern::GetUiExtensionId()
{
    return uiExtensionId_;
}

int32_t SecurityUIExtensionPattern::GetNodeId()
{
    auto host = GetHost();
    return host ? host->GetId() : -1;
}

int32_t SecurityUIExtensionPattern::GetInstanceId()
{
    return instanceId_;
}

void SecurityUIExtensionPattern::DispatchOriginAvoidArea(
    const Rosen::AvoidArea& avoidArea, uint32_t type)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyOriginAvoidArea(avoidArea, type);
}

void SecurityUIExtensionPattern::SetWantWrap(
    const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    curWant_ = wantWrap;
}

RefPtr<OHOS::Ace::WantWrap> SecurityUIExtensionPattern::GetWantWrap()
{
    return curWant_;
}

int64_t SecurityUIExtensionPattern::WrapExtensionAbilityId(
    int64_t extensionOffset, int64_t abilityId)
{
    return uiExtensionId_ * extensionOffset + abilityId;
}

const char* SecurityUIExtensionPattern::ToString(AbilityState state)
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

void SecurityUIExtensionPattern::InitializeAccessibility()
{
    if (accessibilityChildTreeCallback_ != nullptr) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ngPipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(
        WeakClaim(this), accessibilityId);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto realHostWindowId = ngPipeline->GetRealHostWindowId();
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            realHostWindowId, accessibilityManager->GetTreeId());
    }
    UIEXT_LOGI("SecurityUIExtension: %{public}" PRId64 " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
}

void SecurityUIExtensionPattern::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId) const
{
    UIEXT_LOGI("treeId: %{public}d, id: %{public}" PRId64, treeId, accessibilityId);
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void SecurityUIExtensionPattern::OnAccessibilityChildTreeDeregister() const
{
    UIEXT_LOGI("deregister accessibility child tree");
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityChildTreeDeregister();
}

void SecurityUIExtensionPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId) const
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
}

void SecurityUIExtensionPattern::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info) const
{
    UIEXT_LOGI("dump accessibility child info");
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityDumpChildInfo(params, info);
}

void SecurityUIExtensionPattern::ResetAccessibilityChildTreeCallback()
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    ContainerScope scope(instanceId_);
    auto ngPipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(
        accessibilityChildTreeCallback_->GetAccessibilityId());
    accessibilityChildTreeCallback_.reset();
    accessibilityChildTreeCallback_ = nullptr;
}
} // namespace OHOS::Ace::NG
