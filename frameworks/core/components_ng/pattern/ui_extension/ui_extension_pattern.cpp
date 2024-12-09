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

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
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
#include "core/components_ng/pattern/ui_extension/ui_extension_surface_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_proxy.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/pointer_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char ABILITY_KEY_ASYNC[] = "ability.want.params.KeyAsync";
constexpr char ABILITY_KEY_IS_MODAL[] = "ability.want.params.IsModal";
constexpr char ATOMIC_SERVICE_PREFIX[] = "com.atomicservice.";
constexpr char PROHIBIT_NESTING_FAIL_NAME[] = "Prohibit_Nesting_SecurityUIExtensionComponent";
constexpr char PROHIBIT_NESTING_FAIL_MESSAGE[] =
    "Prohibit nesting uIExtensionExtensionComponent in securityUIAbility";
constexpr char PID_FLAG[] = "pidflag";
constexpr char NO_EXTRA_UIE_DUMP[] = "-nouie";
constexpr double SHOW_START = 0.0;
constexpr double SHOW_FULL = 1.0;
constexpr uint32_t REMOVE_PLACEHOLDER_DELAY_TIME = 32;
constexpr uint32_t PLACEHOLDER_TIMEOUT = 6000;

bool StartWith(const std::string &source, const std::string &prefix)
{
    if (source.empty() || prefix.empty()) {
        return false;
    }

    return source.find(prefix) == 0;
}

class UIExtensionAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    UIExtensionAccessibilityChildTreeCallback(const WeakPtr<UIExtensionPattern> &weakPattern, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(weakPattern)
    {}

    ~UIExtensionAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        if (isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeRegister(windowId, treeId, GetAccessibilityId());
        isReg_ = true;
        return true;
    }

    bool OnDeregister() override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        if (!isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeDeregister();
        isReg_ = false;
        return true;
    }

    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        pattern->OnSetAccessibilityChildTree(childWindowId, childTreeId);
        return true;
    }

    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        pattern->OnAccessibilityDumpChildInfo(params, info);
        return true;
    }

    void OnClearRegisterFlag() override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return;
        }
        isReg_ = false;
    }

private:
    bool isReg_ = false;
    WeakPtr<UIExtensionPattern> weakPattern_;
};
}
UIExtensionPattern::UIExtensionPattern(
    bool isTransferringCaller, bool isModal, bool isAsyncModalBinding, SessionType sessionType)
    : isTransferringCaller_(isTransferringCaller), isModal_(isModal),
    isAsyncModalBinding_(isAsyncModalBinding), sessionType_(sessionType)
{
    uiExtensionId_ = UIExtensionIdUtility::GetInstance().ApplyExtensionId();
    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        sessionType, AceType::WeakClaim(this), instanceId_, isTransferringCaller_);
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterUIExtension>(sessionWrapper_);
    UIEXT_LOGI("The %{public}smodal UIExtension is created.", isModal_ ? "" : "non");
}

UIExtensionPattern::~UIExtensionPattern()
{
    UIEXT_LOGI("The %{public}smodal UIExtension is destroyed.", isModal_ ? "" : "non");
    if (isModal_) {
        LogoutModalUIExtension();
    }
    NotifyDestroy();
    FireModalOnDestroy();
    UIExtensionIdUtility::GetInstance().RecycleExtensionId(uiExtensionId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    uiExtensionManager->RemoveDestroyedUIExtension(GetNodeId());

    if (accessibilityChildTreeCallback_ == nullptr) {
        return;
    }

    auto instanceId = GetInstanceIdFromHost();
    ContainerScope scope(instanceId);
    auto ngPipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(
        accessibilityChildTreeCallback_->GetAccessibilityId());
    accessibilityChildTreeCallback_ = nullptr;
}

void UIExtensionPattern::LogoutModalUIExtension()
{
    auto sessionId = GetSessionId();
    UIEXT_LOGI("LogoutModalUIExtension sessionId %{public}d.", sessionId);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlay = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    overlay->ResetRootNode(-(sessionId));
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

void UIExtensionPattern::UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    if (!wantWrap) {
        UIEXT_LOGW("wantWrap is nullptr");
        return;
    }
    auto wantWrapOhos = AceType::DynamicCast<WantWrapOhos>(wantWrap);
    if (!wantWrapOhos) {
        UIEXT_LOGW("DynamicCast failed, wantWrapOhos is nullptr");
        return;
    }
    auto want = wantWrapOhos->GetWant();
    want_ = want.GetElement().GetBundleName().append(want.GetElement().GetAbilityName().c_str());
    UpdateWant(want);
}

void UIExtensionPattern::MountPlaceholderNode(PlaceholderType type)
{
    if (!IsCanMountPlaceholder(type)) {
        return;
    }
    RefPtr<NG::FrameNode> placeholderNode = nullptr;
    auto it = placeholderMap_.find(type);
    if (it != placeholderMap_.end()) {
        placeholderNode = it->second;
    }
    CHECK_NULL_VOID(placeholderNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChildAtIndex(0);
    host->AddChild(placeholderNode, 0);
    ACE_SCOPED_TRACE("MountPlaceholderNode type[%d]", static_cast<int32_t>(type));
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    SetCurPlaceholderType(type);
    PostDelayRemovePlaceholder(PLACEHOLDER_TIMEOUT);
}

void UIExtensionPattern::RemovePlaceholderNode()
{
    if (!IsShowPlaceholder()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChildAtIndex(0);
    ACE_SCOPED_TRACE("RemovePlaceholderNode type[%d]", static_cast<int32_t>(curPlaceholderType_));
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    SetCurPlaceholderType(PlaceholderType::NONE);
}

bool UIExtensionPattern::CheckConstraint()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    if (container->GetUIContentType() == UIContentType::SECURITY_UI_EXTENSION) {
        UIEXT_LOGE("Not allowed nesting in SECURITY_UI_EXTENSION.");
        FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE,
            PROHIBIT_NESTING_FAIL_NAME, PROHIBIT_NESTING_FAIL_MESSAGE);
        return false;
    }

    return true;
}

void UIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    if (!CheckConstraint()) {
        UIEXT_LOGE("Check constraint failed.");
        return;
    }

    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("The current state is '%{public}s' when UpdateWant.", ToString(state_));
    bool isBackground = state_ == AbilityState::BACKGROUND;
    // Prohibit rebuilding the session unless the Want is updated.
    if (sessionWrapper_->IsSessionValid()) {
        auto sessionWant = sessionWrapper_->GetWant();
        if (sessionWant == nullptr) {
            UIEXT_LOGW("The sessionWrapper want is nulllptr.");
            return;
        }
        if (sessionWant->IsEquals(want)) {
            return;
        }
        UIEXT_LOGI("The old want bundle = %{public}s, ability = %{public}s",
            sessionWant->GetElement().GetBundleName().c_str(), sessionWant->GetElement().GetAbilityName().c_str());
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChildAtIndex(0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        SetCurPlaceholderType(PlaceholderType::NONE);
        NotifyDestroy();
        // reset callback, in order to register childtree call back again when onConnect to new ability
        ResetAccessibilityChildTreeCallback();
    }

    isKeyAsync_ = want.GetBoolParam(ABILITY_KEY_ASYNC, false);
    UIExtensionUsage uIExtensionUsage = GetUIExtensionUsage(want);
    usage_ = uIExtensionUsage;
    UIEXT_LOGI("The ability KeyAsync %{public}d, uIExtensionUsage: %{public}u.",
        isKeyAsync_, uIExtensionUsage);
    MountPlaceholderNode(PlaceholderType::INITIAL);
    SessionConfig config;
    config.isAsyncModalBinding = isAsyncModalBinding_;
    config.uiExtensionUsage = uIExtensionUsage;
    sessionWrapper_->CreateSession(want, config);
    if (isBackground) {
        UIEXT_LOGW("Unable to StartUiextensionAbility while in the background.");
        return;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    if (container->IsScenceBoardWindow() && !isModal_ && !hasMountToParent_) {
        needReNotifyForeground_ = true;
        UIEXT_LOGI("Should NotifyForeground after MountToParent.");
        return;
    }
    NotifyForeground();
}

bool UIExtensionPattern::IsModalUec()
{
    return usage_ == UIExtensionUsage::MODAL;
}

bool UIExtensionPattern::IsForeground()
{
    return state_ == AbilityState::FOREGROUND;
}

UIExtensionUsage UIExtensionPattern::GetUIExtensionUsage(const AAFwk::Want& want)
{
    if (sessionType_ == SessionType::EMBEDDED_UI_EXTENSION) {
        return UIExtensionUsage::EMBEDDED;
    }

    if (isModal_) {
        return UIExtensionUsage::MODAL;
    }

    bool wantParamModal = want.GetBoolParam(ABILITY_KEY_IS_MODAL, false);
    auto bundleName = want.GetElement().GetBundleName();
    bool startWithAtomicService = StartWith(bundleName, ATOMIC_SERVICE_PREFIX);
    if (wantParamModal && startWithAtomicService) {
        return UIExtensionUsage::MODAL;
    }

    return UIExtensionUsage::EMBEDDED;
}

void UIExtensionPattern::OnConnect()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("The session is connected and the current state is '%{public}s'.", ToString(state_));
    ContainerScope scope(instanceId_);
    contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<UIExtensionSurfacePattern>());
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
        UIEXT_LOGE("Get surfaceNode from session is null.");
        return;
    }
    context->SetRSNode(surfaceNode);
    RemovePlaceholderNode();
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    surfaceNode->SetForeground(usage_ == UIExtensionUsage::MODAL);
    FireOnRemoteReadyCallback();
    auto focusHub = host->GetFocusHub();
    if ((usage_ == UIExtensionUsage::MODAL) && focusHub) {
        focusHub->RequestFocusImmediately();
    }
    bool isFocused = focusHub && focusHub->IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    sessionWrapper_->UpdateSessionViewportConfig();
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));
    if (isFocused || (usage_ == UIExtensionUsage::MODAL)) {
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
    }
    InitializeAccessibility();
    ReDispatchDisplayArea();
}

void UIExtensionPattern::ReplacePlaceholderByContent()
{
    CHECK_RUN_ON(UI);
    if (!IsShowPlaceholder()) {
        return;
    }
    RemovePlaceholderNode();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void UIExtensionPattern::OnAreaUpdated()
{
    PostDelayRemovePlaceholder(REMOVE_PLACEHOLDER_DELAY_TIME);
}

void UIExtensionPattern::PostDelayRemovePlaceholder(uint32_t delay)
{
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ReplacePlaceholderByContent();
        },
        TaskExecutor::TaskType::UI, delay, "ArkUIUIExtensionRemovePlaceholder");
}

void UIExtensionPattern::OnExtensionEvent(UIExtCallbackEventId eventId)
{
    CHECK_RUN_ON(UI);
    ContainerScope scope(instanceId_);
    switch (eventId) {
        case UIExtCallbackEventId::ON_AREA_CHANGED:
            OnAreaUpdated();
            break;
        case UIExtCallbackEventId::ON_UEA_ACCESSIBILITY_READY:
            OnUeaAccessibilityEventAsync();
            break;
    }
}

void UIExtensionPattern::OnUeaAccessibilityEventAsync()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if ((accessibilityChildTreeCallback_ != nullptr) && (accessibilityProperty->GetChildTreeId() != -1)) {
        UIEXT_LOGI("uec need notify register accessibility again %{public}d, %{public}d.",
            accessibilityProperty->GetChildWindowId(), accessibilityProperty->GetChildTreeId());
        ResetAccessibilityChildTreeCallback();
        InitializeAccessibility();
    }
}

PlaceholderType UIExtensionPattern::GetSizeChangeReason()
{
    CHECK_NULL_RETURN(sessionWrapper_, PlaceholderType::NONE);
    if (IsFoldStatusChanged()) {
        SetFoldStatusChanged(false);
        return PlaceholderType::FOLD_TO_EXPAND;
    }
    if (IsRotateStatusChanged()) {
        SetRotateStatusChanged(false);
        return PlaceholderType::ROTATION;
    }
    return PlaceholderType::UNDEFINED;
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
    host->RemoveChildAtIndex(0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    SetCurPlaceholderType(PlaceholderType::NONE);
}

void UIExtensionPattern::OnSyncGeometryNode(const DirtySwapConfig& config)
{
    if (needReNotifyForeground_) {
        needReNotifyForeground_ = false;
        UIEXT_LOGI("NotifyForeground onSyncGeometryNode first.");
        NotifyForeground();
        needReDispatchDisplayArea_ = true;
    }
    DispatchDisplayArea(true);
}

void UIExtensionPattern::ReDispatchDisplayArea()
{
    if (needReDispatchDisplayArea_) {
        UIEXT_LOGI("ReDispatchDisplayArea.");
        DispatchDisplayArea(true);
        needReDispatchDisplayArea_ = false;
    }
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
    UIEXT_LOGI("The window is being hidden and the component is %{public}s, state is '%{public}s.",
        isVisible_ ? "visible" : "invisible", ToString(state_));
    if (isVisible_) {
        NotifyBackground();
    } else if (state_ == AbilityState::FOREGROUND) {
        NotifyBackground(false);
    }
}

void UIExtensionPattern::OnWindowSizeChanged(int32_t  /*width*/, int32_t  /*height*/, WindowSizeChangeReason type)
{
    if (WindowSizeChangeReason::ROTATION == type) {
        SetRotateStatusChanged(true);
    }
}

void UIExtensionPattern::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifySizeChangeReason(type, rsTransaction);
}

void UIExtensionPattern::OnExtensionDetachToDisplay()
{
    if (contentNode_ == nullptr) {
        UIEXT_LOGW("ContentNode is null when OnExtensionDetachToDisplay.");
        return;
    }

    UIEXT_LOGI("OnExtensionDetachToDisplay");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void UIExtensionPattern::NotifyForeground()
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ != AbilityState::FOREGROUND) {
        UIEXT_LOGI("The state is changing from '%{public}s' to 'FOREGROUND'.", ToString(state_));
        state_ = AbilityState::FOREGROUND;
        sessionWrapper_->NotifyForeground();
        if (displayAreaChanged_) {
            sessionWrapper_->NotifyDisplayArea(displayArea_);
            displayAreaChanged_ = false;
        }
    }
}

void UIExtensionPattern::NotifyBackground(bool isHandleError)
{
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid() && state_ == AbilityState::FOREGROUND) {
        UIEXT_LOGI("The state is changing from '%{public}s' to 'BACKGROUND'.", ToString(state_));
        state_ = AbilityState::BACKGROUND;
        sessionWrapper_->NotifyBackground(isHandleError);
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
    pipeline->AddWindowSizeChangeCallback(host->GetId());
    surfacePositionCallBackId_ =
        pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t, int32_t) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->DispatchDisplayArea(true);
    });
    foldDisplayCallBackId_ =
        pipeline->RegisterFoldDisplayModeChangedCallback([weak = WeakClaim(this)](FoldDisplayMode foldDisplayMode) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetFoldStatusChanged(true);
    });
    UIEXT_LOGI("OnAttachToFrameNode");
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveOnAreaChangeNode(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionCallBackId_);
    pipeline->UnRegisterFoldDisplayModeChangedCallback(foldDisplayCallBackId_);
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
    CHECK_NULL_VOID(pipeline);
    if (canFocusSendToUIExtension_) {
        if (pipeline->GetIsFocusActive()) {
            DispatchFocusActiveEvent(true);
        }

        DispatchFocusState(true);
        needReSendFocusToUIExtension_ = false;
    } else {
        needReSendFocusToUIExtension_ = true;
    }

    canFocusSendToUIExtension_ = true;
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
        UIEXT_LOGE("The source type is not TOUCH, type %{public}d.", info.GetSourceDevice());
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    if (!pointerEvent) {
        UIEXT_LOGE("The pointerEvent is empty.");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    std::shared_ptr<MMI::PointerEvent> newPointerEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);
    Platform::CalculatePointerEvent(newPointerEvent, host);
    AceExtraInputData::InsertInterpolatePoints(info);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    bool ret = true;
    focusState_ = pipeline->IsWindowFocused();
    if (focusState_ && !focusHub->IsCurrentFocus()) {
        canFocusSendToUIExtension_ = false;
        ret = focusHub->RequestFocusImmediately();
        if (!ret) {
            canFocusSendToUIExtension_ = true;
            UIEXT_LOGW("RequestFocusImmediately failed when HandleTouchEvent.");
        }
    }
    auto pointerAction = newPointerEvent->GetPointerAction();
    if (!(pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_MOVE ||
            pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW ||
            pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_UP)) {
        DispatchPointerEvent(newPointerEvent);
    }
    if (focusState_ && newPointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_UP) {
        if (needReSendFocusToUIExtension_) {
            HandleFocusEvent();
            needReSendFocusToUIExtension_ = false;
        }
        focusHub->SetForceProcessOnKeyEventInternal(true);
    }
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        return;
    }
    if (info.GetPullAction() == MouseAction::PULL_MOVE || info.GetPullAction() == MouseAction::PULL_UP) {
        return;
    }
    const auto pointerEvent = info.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    lastPointerEvent_ = pointerEvent;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Platform::CalculatePointerEvent(pointerEvent, host);
    if (info.GetAction() == MouseAction::PRESS) {
        auto hub = host->GetFocusHub();
        CHECK_NULL_VOID(hub);
        hub->RequestFocusImmediately();
        hub->SetForceProcessOnKeyEventInternal(true);
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
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->NotifyKeyEventAsync(event.rawKeyEvent);
}

bool UIExtensionPattern::DispatchKeyEventSync(const KeyEvent& event)
{
    CHECK_NULL_RETURN(sessionWrapper_, false);
    if (isKeyAsync_) {
        sessionWrapper_->NotifyKeyEventAsync(event.rawKeyEvent, false);
        return true;
    }

    return sessionWrapper_->NotifyKeyEventSync(event.rawKeyEvent, event.isPreIme);
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
    if (!pointerEvent) {
        UIEXT_LOGE("DispatchPointerEvent pointerEvent is null.");
        return;
    }
    if (!sessionWrapper_) {
        UIEXT_LOGE("DispatchPointerEvent sessionWrapper is null.");
        return;
    }
    sessionWrapper_->NotifyPointerEventAsync(pointerEvent);
}

void UIExtensionPattern::DispatchDisplayArea(bool isForce)
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
    bool sizeChange = displayArea_ != displayArea;
    if (sizeChange || isForce) {
        displayArea_ = displayArea;
        if (state_ == AbilityState::FOREGROUND) {
            if (sizeChange) {
                MountPlaceholderNode(GetSizeChangeReason());
            }
            sessionWrapper_->NotifyDisplayArea(displayArea_);
        } else {
            displayAreaChanged_ = true;
        }
    }
}

void UIExtensionPattern::SetEventProxyFlag(int32_t flag)
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

void UIExtensionPattern::HandleDragEvent(const DragPointerEvent& info)
{
    auto pointerEvent = info.rawPointerEvent;
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Platform::CalculatePointerEvent(pointerEvent, host, true);
    Platform::UpdatePointerAction(pointerEvent, info.action);
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
    UIEXT_LOGI("OnRemoteReady the current state is '%{public}s'.", ToString(state_));
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
    UIEXT_LOGI("ModalOnDestroy the current state is '%{public}s'.", ToString(state_));
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
    UIEXT_LOGI("OnRelease the state is changing from '%{public}s' to 'DESTRUCTION' and releaseCode = %{public}d.",
        ToString(state_), releaseCode);
    state_ = AbilityState::DESTRUCTION;
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
    if (onReleaseCallback_) {
        onReleaseCallback_(releaseCode);
    }
    // Release the session.
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        sessionWrapper_->OnReleaseDone();
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
    UIEXT_LOGI("OnError the state is changing from '%{public}s' to 'NONE'.", ToString(state_));
    state_ = AbilityState::NONE;
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
    // Release the session.
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        if (!IsShowPlaceholder()) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->RemoveChildAtIndex(0);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        if (name.compare("extension_node_transparent") != 0) {
            sessionWrapper_->NotifyDestroy(false);
            sessionWrapper_->DestroySession();
        }
    }
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
    UIEXT_LOGI("OnResult the state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
    if (onResultCallback_ && (state_ != AbilityState::DESTRUCTION)) {
        ContainerScope scope(instanceId_);
        onResultCallback_(code, want);
    }
    state_ = AbilityState::DESTRUCTION;
}

bool UIExtensionPattern::IsCompatibleOldVersion()
{
    ContainerScope scope(instanceId_);
    return (sessionType_ == SessionType::UI_EXTENSION_ABILITY) && (onTerminatedCallback_ == nullptr);
}

void UIExtensionPattern::SetOnTerminatedCallback(
    const std::function<void(int32_t, const RefPtr<WantWrap>& wantWrap)>&& callback)
{
    onTerminatedCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnTerminatedCallback(int32_t code, const RefPtr<WantWrap>& wantWrap)
{
    UIEXT_LOGI("OnTerminated the state is changing from '%{public}s' to 'DESTRUCTION'.", ToString(state_));
    if (onTerminatedCallback_ && (state_ != AbilityState::DESTRUCTION)) {
        ContainerScope scope(instanceId_);
        onTerminatedCallback_(code, wantWrap);
    }
    state_ = AbilityState::DESTRUCTION;
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
}

void UIExtensionPattern::SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback)
{
    onReceiveCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnReceiveCallback(const AAFwk::WantParams& params)
{
    UIEXT_LOGI("OnReceive the current state is '%{public}s'.", ToString(state_));
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
    UIEXT_LOGI("The size of sync callbacks = %{public}zu.", onSyncOnCallbackList_.size());
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
    UIEXT_LOGI("The size of async callbacks = %{public}zu.", onSyncOnCallbackList_.size());
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

void UIExtensionPattern::SetDensityDpi(bool densityDpi)
{
    densityDpi_ = densityDpi;
}

bool UIExtensionPattern::GetDensityDpi()
{
    return densityDpi_;
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

void UIExtensionPattern::InitializeAccessibility()
{
    if (accessibilityChildTreeCallback_ != nullptr) {
        return;
    }
    auto instanceId = GetInstanceIdFromHost();
    ContainerScope scope(instanceId);
    auto ngPipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    accessibilityChildTreeCallback_ = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(
        WeakClaim(this), accessibilityId);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto realHostWindowId = ngPipeline->GetRealHostWindowId();
    realHostWindowId_ = realHostWindowId;
    focusWindowId_ = ngPipeline->GetFocusWindowId();
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            realHostWindowId, accessibilityManager->GetTreeId());
    }
    UIEXT_LOGI("UIExtension: %{public}" PRId64 " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
}

void UIExtensionPattern::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    UIEXT_LOGI("treeId: %{public}d, id: %{public}" PRId64, treeId, accessibilityId);
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void UIExtensionPattern::OnAccessibilityChildTreeDeregister()
{
    UIEXT_LOGI("deregister accessibility child tree");
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityChildTreeDeregister();
}

void UIExtensionPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
}

void UIExtensionPattern::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    UIEXT_LOGI("dump accessibility child info");
    if (sessionWrapper_ == nullptr) {
        UIEXT_LOGI("sessionWrapper_ is null");
        return;
    }
    sessionWrapper_->TransferAccessibilityDumpChildInfo(params, info);
}

void UIExtensionPattern::ResetAccessibilityChildTreeCallback()
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto instanceId = GetInstanceIdFromHost();
    ContainerScope scope(instanceId);
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

void UIExtensionPattern::OnMountToParentDone()
{
    UIEXT_LOGI("OnMountToParentDone.");
    hasMountToParent_ = true;
    if (needReNotifyForeground_) {
        auto hostWindowNode = WindowSceneHelper::FindWindowScene(GetHost());
        if (hostWindowNode) {
            needReNotifyForeground_ = false;
            UIEXT_LOGI("NotifyForeground OnMountToParentDone.");
            NotifyForeground();
        } else {
            UIEXT_LOGI("No WindowScene When OnMountToParentDone, wait.");
        }
    }
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

void UIExtensionPattern::AfterMountToParent()
{
    UIEXT_LOGI("AfterMountToParent.");
    hasMountToParent_ = true;
    if (needReNotifyForeground_) {
        auto hostWindowNode = WindowSceneHelper::FindWindowScene(GetHost());
        if (hostWindowNode) {
            needReNotifyForeground_ = false;
            UIEXT_LOGI("NotifyForeground AfterMountToParent.");
            NotifyForeground();
        } else {
            UIEXT_LOGI("No WindowScene When AfterMountToParent, wait.");
        }
    }
}

void UIExtensionPattern::RegisterVisibleAreaChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto uiExtension = weak.Upgrade();
        CHECK_NULL_VOID(uiExtension);
        uiExtension->HandleVisibleAreaChange(visible, ratio);
    };
    std::vector<double> ratioList = { SHOW_START, SHOW_FULL };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
}

void UIExtensionPattern::HandleVisibleAreaChange(bool visible, double ratio)
{
    UIEXT_LOGI("HandleVisibleAreaChange visible: %{public}d, curVisible: %{public}d, "
        "ratio: %{public}f, displayArea: %{public}s.", visible, curVisible_,
        ratio, displayArea_.ToString().c_str());
    bool needCheckDisplayArea = NearEqual(ratio, SHOW_FULL) && curVisible_ && visible;
    bool curVisible = !NearEqual(ratio, SHOW_START);
    if (curVisible_ != curVisible) {
        curVisible_ = curVisible;
        OnVisibleChange(curVisible_);
    }

    if (needCheckDisplayArea) {
        DispatchDisplayArea(false);
    }
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

int32_t UIExtensionPattern::GetSessionId() const
{
    return sessionWrapper_ ? sessionWrapper_->GetSessionId() : 0;
}

int32_t UIExtensionPattern::GetUiExtensionId()
{
    return uiExtensionId_;
}

int32_t UIExtensionPattern::GetNodeId() const
{
    auto host = GetHost();
    return host ? host->GetId() : -1;
}

int32_t UIExtensionPattern::GetInstanceId() const
{
    return instanceId_;
}

int32_t UIExtensionPattern::GetInstanceIdFromHost()
{
    auto instanceId = GetHostInstanceId();
    if (instanceId != instanceId_) {
        UIEXT_LOGW("UIExtension pattern instanceId %{public}d not equal frame node instanceId %{public}d",
            instanceId_, instanceId);
    }
    return instanceId;
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

void UIExtensionPattern::DumpInfo()
{
    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("Dump UIE Info In String Format");
    DumpLog::GetInstance().AddDesc(std::string("focusWindowId: ").append(std::to_string(focusWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("realHostWindowId: ").append(std::to_string(realHostWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("want: ").append(want_));
    DumpLog::GetInstance().AddDesc(std::string("displayArea: ").append(displayArea_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("reason: ").append(std::to_string(sessionWrapper_->GetReasonDump())));
    DumpLog::GetInstance().AddDesc(std::string("focusStatus: ").append(std::to_string(focusState_)));
    DumpLog::GetInstance().AddDesc(std::string("abilityState: ").append(ToString(state_)));

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        UIEXT_LOGI("Not Support Dump Extra UIE Info");
    } else {
        if (!container->IsUIExtensionWindow()) {
            params.push_back(PID_FLAG);
        }
        params.push_back(std::to_string(getpid()));
        std::vector<std::string> dumpInfo;
        sessionWrapper_->NotifyUieDump(params, dumpInfo);
        for (std::string info : dumpInfo) {
            DumpLog::GetInstance().AddDesc(std::string("UI Extension info: ").append(info));
        }
    }
}

void UIExtensionPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("Dump UIE Info In Json Format");
    json->Put("focusWindowId: ", std::to_string(focusWindowId_).c_str());
    json->Put("realHostWindowId: ", std::to_string(realHostWindowId_).c_str());
    json->Put("want: ", want_.c_str());
    json->Put("displayArea: ", displayArea_.ToString().c_str());
    json->Put("reason: ", std::to_string(sessionWrapper_->GetReasonDump()).c_str());
    json->Put("focusStatus: ", std::to_string(focusState_).c_str());
    json->Put("abilityState: ", ToString(state_));

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        UIEXT_LOGI("Not Support Dump Extra UIE Info");
    } else {
        if (!container->IsUIExtensionWindow()) {
            params.push_back(PID_FLAG);
        }
        params.push_back(std::to_string(getpid()));
        std::vector<std::string> dumpInfo;
        sessionWrapper_->NotifyUieDump(params, dumpInfo);
        for (std::string info : dumpInfo) {
            json->Put("UI Extension info: ", info.c_str());
        }
    }
}

void UIExtensionPattern::DumpOthers()
{
    CHECK_NULL_VOID(sessionWrapper_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        UIEXT_LOGI("Not Support Dump Extra UIE Info");
    } else {
        if (params.back() == "-json") {
            params.insert(params.end() - 1, std::to_string(getpid()));
            if (!container->IsUIExtensionWindow()) {
                params.insert(params.end() - 1, PID_FLAG);
            }
        } else {
            if (!container->IsUIExtensionWindow()) {
                params.push_back(PID_FLAG);
            }
            params.push_back(std::to_string(getpid()));
        }
        std::vector<std::string> dumpInfo;
        sessionWrapper_->NotifyUieDump(params, dumpInfo);
        for (std::string info : dumpInfo) {
            std::stringstream ss(info);
            std::string line;
            DumpLog::GetInstance().Print("\n------ UIExtension Dump ------");
            while (getline(ss, line, ';')) {
                DumpLog::GetInstance().Print(line);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
