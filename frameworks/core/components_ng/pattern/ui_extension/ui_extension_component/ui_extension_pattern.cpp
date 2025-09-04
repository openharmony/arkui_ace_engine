/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"

#include <optional>

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/log/dump_log.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/platform_utils.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_container_handler.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_surface_pattern.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
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
constexpr char UEC_ERROR_NAME_PROHIBIT_NESTING_FAIL_NAME[] = "Prohibit_Nesting";
constexpr char UEC_ERROR_MAG_PROHIBIT_NESTING_FAIL_MESSAGE[] =
    "Prohibit nesting uiExtensionComponent";
constexpr double SHOW_START = 0.0;
constexpr double SHOW_FULL = 1.0;
constexpr char PID_FLAG[] = "pidflag";
constexpr char NO_EXTRA_UIE_DUMP[] = "-nouie";
constexpr uint32_t REMOVE_PLACEHOLDER_DELAY_TIME = 32;
constexpr char OCCLUSION_SCENE[] = "_occlusion";

bool StartWith(const std::string &source, const std::string &prefix)
{
    if (source.empty() || prefix.empty()) {
        return false;
    }

    return source.find(prefix) == 0;
}
}
UIExtensionPattern::UIExtensionPattern(
    bool isTransferringCaller, bool isModal, bool isAsyncModalBinding, SessionType sessionType)
    : isTransferringCaller_(isTransferringCaller), isModal_(isModal),
    isAsyncModalBinding_(isAsyncModalBinding), sessionType_(sessionType)
{
    uiExtensionId_ = UIExtensionIdUtility::GetInstance().ApplyExtensionId();
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

void UIExtensionPattern::Initialize()
{
    if (hasInitialize_) {
        return;
    }

    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        sessionType_, AceType::WeakClaim(this), instanceId_, isTransferringCaller_);
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterUIExtension>(sessionWrapper_);
    hasInitialize_ = true;
}

/* only for 1.2 begin */
bool UIExtensionPattern::GetIsTransferringCaller()
{
    return isTransferringCaller_;
}

void UIExtensionPattern::SetIsTransferringCaller(bool isTransferringCaller)
{
    isTransferringCaller_ = isTransferringCaller;
}
/* only for 1.2 end */

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

void UIExtensionPattern::OnAttachToMainTree()
{
    UIEXT_LOGI("OnAttachToMainTree, isMoving: %{public}d", IsMoving());
    if (IsMoving()) {
        return;
    }
    if (needReNotifyForeground_) {
        auto hostWindowNode = WindowSceneHelper::FindWindowScene(GetHost());
        if (hostWindowNode) {
            needReNotifyForeground_ = false;
            UIEXT_LOGI("NotifyForeground OnAttachToMainTree.");
            NotifyForeground();
        } else {
            UIEXT_LOGI("No WindowScene When OnAttachToMainTree, wait.");
        }
    }
}

void UIExtensionPattern::OnDetachFromMainTree()
{
    UIEXT_LOGI("OnDetachFromMainTree, isMoving: %{public}d", IsMoving());
}

void UIExtensionPattern::OnAttachContext(PipelineContext *context)
{
    CHECK_NULL_VOID(context);
    auto newInstanceId = context->GetInstanceId();
    bool isMoving = IsMoving();
    bool detachContextHappened = hasDetachContext_;
    UIEXT_LOGI("OnAttachContext newInstanceId: %{public}d, oldInstanceId: %{public}d,"
        " isMoving: %{public}d, detachContextHappened: %{public}d.",
        newInstanceId, instanceId_, isMoving, detachContextHappened);
    if (newInstanceId != instanceId_) {
        UnRegisterEvent(instanceId_);
        RegisterEvent(newInstanceId);
        instanceId_ = newInstanceId;
        UpdateSessionInstanceId(newInstanceId);
    } else if (detachContextHappened) {
        RegisterEvent(instanceId_);
    }
    /* only for 1.2 begin */
    if (context->GetFrontendType() == FrontendType::ARK_TS) {
        auto wantWrap = GetWantWrap();
        CHECK_NULL_VOID(wantWrap);
        UIEXT_LOGI("OnAttachContext UpdateWant, newInstanceId: %{public}d", instanceId_);
        UpdateWant(wantWrap);
        SetWantWrap(nullptr);
        hasAttachContext_ = true;
    }
    /* only for 1.2 end */
}

void UIExtensionPattern::UpdateSessionInstanceId(int32_t instanceId)
{
    auto sessionWrapperImpl = AceType::DynamicCast<SessionWrapperImpl>(sessionWrapper_);
    if (!sessionWrapperImpl) {
        UIEXT_LOGW("DynamicCast failed, sessionWrapperImpl is nullptr");
        return;
    }

    sessionWrapperImpl->UpdateInstanceId(instanceId);
}

void UIExtensionPattern::RegisterEvent(int32_t instanceId)
{
    RegisterUIExtensionManagerEvent(instanceId);
    RegisterPipelineEvent(instanceId);
    hasDetachContext_ = false;
}

void UIExtensionPattern::RegisterPipelineEvent(int32_t instanceId)
{
    ContainerScope scope(instanceId);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    RegisterPipelineEvent(pipeline);
}

void UIExtensionPattern::RegisterUIExtensionManagerEvent(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    // 1. Add alive uec in uiExtensionManager
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));

    // 2. Add focus uec in uiExtensionManager
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    bool isFocusd = focusHub && focusHub->IsCurrentFocus();
    if (isFocusd) {
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
    }
    UIEXT_LOGI("RegisterUIExtensionManagerEvent");
}

void UIExtensionPattern::OnDetachContext(PipelineContext *context)
{
    hasAttachContext_ = false;
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    if (instanceId != instanceId_) {
        UIEXT_LOGW("InstanceId(%{public}d) is inconsistent with the exist Id(%{public}d),",
            instanceId, instanceId_);
        return;
    }

    bool isMoving = IsMoving();
    UIEXT_LOGI("OnDetachContext instanceId: %{public}d, isMoving: %{public}d,"
        " isOnDetachContext: %{public}d.", instanceId, isMoving, hasDetachContext_);
    if (!isMoving && !hasDetachContext_) {
        UnRegisterEvent(instanceId);
    }
}

void UIExtensionPattern::UnRegisterEvent(int32_t instanceId)
{
    UnRegisterUIExtensionManagerEvent(instanceId);
    UnRegisterPipelineEvent(instanceId);
    hasDetachContext_ = true;
}

void UIExtensionPattern::UnRegisterPipelineEvent(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    ContainerScope scope(instanceId);
    UnRegisterPipelineEvent(pipeline, AceType::RawPtr(host));
}

void UIExtensionPattern::UnRegisterUIExtensionManagerEvent(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtensionManager);
    // 1. Delete alive uec in uiExtensionManager
    uiExtensionManager->RemoveDestroyedUIExtension(GetNodeId());

    // 2. Delete focus uec in uiExtensionManager
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    bool isFocusd = focusHub && focusHub->IsCurrentFocus();
    if (isFocusd) {
        uiExtensionManager->RegisterUIExtensionInFocus(nullptr, nullptr);
    }
    UIEXT_LOGI("UnRegisterUIExtensionManagerEvent");
}

bool UIExtensionPattern::IsMoving()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    return host->IsMoving();
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

bool UIExtensionPattern::CheckHostUiContentConstraint()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto containerHandler = container->GetContainerHandler();
    CHECK_NULL_RETURN(containerHandler, true);
    auto uIExtensionContainerHandler =
        AceType::DynamicCast<UIExtensionContainerHandler>(containerHandler);
    CHECK_NULL_RETURN(uIExtensionContainerHandler, true);
    UIContentType hostUIContentType = uIExtensionContainerHandler->GetHostUIContentType();
    static std::set<UIContentType> dcNotSupportHostUIContentType = {
        UIContentType::ISOLATED_COMPONENT,
        UIContentType::DYNAMIC_COMPONENT
    };

    if (dcNotSupportHostUIContentType.find(hostUIContentType) != dcNotSupportHostUIContentType.end()) {
        UIEXT_LOGE("Not support uec in hostUIContentType: %{public}d.",
            static_cast<int32_t>(hostUIContentType));
        FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE,
            UEC_ERROR_NAME_PROHIBIT_NESTING_FAIL_NAME, UEC_ERROR_MAG_PROHIBIT_NESTING_FAIL_MESSAGE);
        return false;
    }

    return true;
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

    return CheckHostUiContentConstraint();
}

void UIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    if (!CheckConstraint()) {
        UIEXT_LOGE("Check constraint failed.");
        return;
    }

    CHECK_NULL_VOID(sessionWrapper_);
    UIEXT_LOGI("The current state is '%{public}s' when UpdateWant, need Check: '%{public}d'.",
        ToString(state_), needCheckWindowSceneId_);
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
    if (needCheckWindowSceneId_ && container->IsSceneBoardWindow() &&
        uIExtensionUsage != UIExtensionUsage::MODAL && !hasMountToParent_) {
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

void UIExtensionPattern::ReDispatchWantParams()
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->ReDispatchWantParams();
}

void UIExtensionPattern::HandleOcclusionScene(const RefPtr<FrameNode>& node, bool flag)
{
    CHECK_NULL_VOID(node);
    if (node->GetInspectorId().value_or("").find(OCCLUSION_SCENE) == std::string::npos) {
        return;
    }
    ACE_SCOPED_TRACE("occlusion contentNode id: %d, name: %s setSuccess",
        node->GetId(), node->GetInspectorId().value_or("").c_str());
    node->AddToOcclusionMap(flag);
}

void UIExtensionPattern::UpdateSessionViewportConfigFromContext()
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SessionViewportConfig sessionViewportConfig;
    sessionViewportConfig.isDensityFollowHost_ = GetDensityDpi();
    sessionViewportConfig.density_ = pipeline->GetCurrentDensity();
    sessionViewportConfig.displayId_ = container->GetCurrentDisplayId();
    sessionViewportConfig.orientation_ = static_cast<int32_t>(SystemProperties::GetDeviceOrientation());
    sessionViewportConfig.transform_ = pipeline->GetTransformHint();
    auto curSessionViewportConfig = GetSessionViewportConfig();
    if (curSessionViewportConfig == sessionViewportConfig) {
        return;
    }
    UIEXT_LOGI("diff session viewport config between createSession and onConnect.");
    SetSessionViewportConfig(sessionViewportConfig);
    sessionWrapper_->UpdateSessionViewportConfig();
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
    if (SystemProperties::GetMultiInstanceEnabled()) {
        auto pipelineContext = host->GetContext();
        if (pipelineContext) {
            auto rsUIDirector = pipelineContext->GetWindow()->GetRSUIDirector();
            if (rsUIDirector) {
                auto rsUIContext = rsUIDirector->GetRSUIContext();
                surfaceNode->SetRSUIContext(rsUIContext);
            }
        }
    }
    if (curPlaceholderType_ != PlaceholderType::INITIAL) {
        host->AddChild(contentNode_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    surfaceNode->CreateNodeInRenderThread();
    surfaceNode->SetForeground(usage_ == UIExtensionUsage::MODAL);
    FireOnRemoteReadyCallback();
    auto focusHub = host->GetFocusHub();
    if ((usage_ == UIExtensionUsage::MODAL) && focusHub && isModalRequestFocus_) {
        focusHub->RequestFocusImmediately();
    }
    bool isFocused = focusHub && focusHub->IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    UpdateSessionViewportConfigFromContext();
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->AddAliveUIExtension(host->GetId(), WeakClaim(this));
    if (isFocused || (usage_ == UIExtensionUsage::MODAL)) {
        uiExtensionManager->RegisterUIExtensionInFocus(WeakClaim(this), sessionWrapper_);
    }
    ReDispatchWantParams();
    InitializeAccessibility();
    ReDispatchDisplayArea();
    InitBusinessDataHandleCallback();
    HandleOcclusionScene(host, true);
}

void UIExtensionPattern::InitBusinessDataHandleCallback()
{
    RegisterReceivePageModeRequestCallback();
    RegisterEventProxyFlagCallback();
    RegisterGetAvoidInfoCallback();
    NotifyHostWindowMode();
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

void UIExtensionPattern::RegisterWindowSceneVisibleChangeCallback(
    const RefPtr<Pattern>& windowScenePattern)
{
    auto systemWindowScene = AceType::DynamicCast<SystemWindowScene>(windowScenePattern);
    CHECK_NULL_VOID(systemWindowScene);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto callback = [weak = WeakClaim(this)](bool visible) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnWindowSceneVisibleChange(visible);
        }
    };
    systemWindowScene->RegisterVisibleChangeCallback(host->GetId(), callback);
    weakSystemWindowScene_ = systemWindowScene;
    UIEXT_LOGI("RegisterWindowSceneVisibleChangeCallback %{public}d.", host->GetId());
}

void UIExtensionPattern::UnRegisterWindowSceneVisibleChangeCallback(int32_t nodeId)
{
    auto pattern = weakSystemWindowScene_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto systemWindowScene = AceType::DynamicCast<SystemWindowScene>(pattern);
    CHECK_NULL_VOID(systemWindowScene);
    systemWindowScene->UnRegisterVisibleChangeCallback(nodeId);
    UIEXT_LOGI("UnRegisterWindowSceneVisibleChangeCallback %{public}d.", nodeId);
}

void UIExtensionPattern::OnWindowSceneVisibleChange(bool visible)
{
    UIEXT_LOGI("OnWindowSceneVisibleChange %{public}d.", visible);
    if (!visible) {
        OnWindowHide();
    }
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
    ACE_SCOPED_TRACE("OnExtensionEvent[%u]", eventId);
    ContainerScope scope(instanceId_);
    switch (eventId) {
        case UIExtCallbackEventId::ON_AREA_CHANGED:
            OnAreaUpdated();
            break;
        case UIExtCallbackEventId::ON_UEA_ACCESSIBILITY_READY:
            OnUeaAccessibilityEventAsync();
            break;
        case UIExtCallbackEventId::ON_DRAW_FIRST:
            FireOnDrawReadyCallback();
            break;
    }
}

void UIExtensionPattern::UpdateFrameNodeState()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto frontend = pipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->UpdateFrameNodeState(frameNode->GetId());
}

void UIExtensionPattern::OnUeaAccessibilityEventAsync()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    UpdateFrameNodeState();
    TransferAccessibilityRectInfo(true); // first connect need info UEC rect info
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

class UECAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    UECAccessibilitySAObserverCallback(
        const WeakPtr<UIExtensionPattern>& weakPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakUECPattern_(weakPattern)
    {}

    ~UECAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        auto pattern = weakUECPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (state) {
            // first time turn on Accessibility, add TransferAccessibilityRectInfo
            pattern->TransferAccessibilityRectInfo(true);
        }
        return true;
    }
private:
    WeakPtr<UIExtensionPattern> weakUECPattern_;
};

void UIExtensionPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    Initialize();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    RegisterPipelineEvent(pipeline);
    UIEXT_LOGI("OnAttachToFrameNode");
}

void UIExtensionPattern::RegisterPipelineEvent(
    const RefPtr<PipelineContext>& pipeline)
{
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
        pattern->TransferAccessibilityRectInfo();
        pattern->DispatchDisplayArea(true);
    });
    foldDisplayCallBackId_ =
        pipeline->RegisterFoldDisplayModeChangedCallback([weak = WeakClaim(this)](FoldDisplayMode foldDisplayMode) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetFoldStatusChanged(true);
    });
    auto frontend = pipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->AddFrameNodeToUecStatusVec(host);
    host->RegisterNodeChangeListener();
    accessibilitySAObserverCallback_ = std::make_shared<UECAccessibilitySAObserverCallback>(
        WeakClaim(this), host->GetAccessibilityId());
#ifndef ACE_UNITTEST
    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
#endif
    UIEXT_LOGI("RegisterPipelineEvent");
}

void UIExtensionPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    UnRegisterWindowSceneVisibleChangeCallback(id);
    ContainerScope scope(instanceId_);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    UnRegisterPipelineEvent(pipeline, frameNode);
}

void UIExtensionPattern::UnRegisterPipelineEvent(
    const RefPtr<PipelineContext>& pipeline, FrameNode* frameNode)
{
    CHECK_NULL_VOID(pipeline);
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    pipeline->RemoveOnAreaChangeNode(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionCallBackId_);
    pipeline->UnRegisterFoldDisplayModeChangedCallback(foldDisplayCallBackId_);
    frameNode->UnregisterNodeChangeListener();
#ifndef ACE_UNITTEST
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(frameNode->GetAccessibilityId());
#endif
    UIEXT_LOGI("UnRegisterPipelineEvent");
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
#ifdef SUPPORT_DIGITAL_CROWN
    InitCrownEvent(focusHub);
#endif
}

void UIExtensionPattern::InitKeyEventOnFocus(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Focus Internal.");
            pattern->HandleFocusEvent();
        }
    });
}

void UIExtensionPattern::InitKeyEventOnBlur(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnBlurInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Blur Internal.");
            pattern->HandleBlurEvent();
        }
    });
}

void UIExtensionPattern::InitKeyEventOnClearFocusState(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnClearFocusStateInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Clear FocusState Internal.");
            pattern->DispatchFocusActiveEvent(false);
        }
    });
}

void UIExtensionPattern::InitKeyEventOnPaintFocusState(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnPaintFocusStateInternal([weak = WeakClaim(this)]() -> bool {
        auto pattern = weak.Upgrade();
        if (pattern) {
            bool forceProcessKeyEvent = pattern->GetForceProcessOnKeyEventInternal();
            TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "Paint FocusState Internal will %{public}s Active UIExtension.", forceProcessKeyEvent ? "not" : "");
            if (forceProcessKeyEvent) {
                return true;
            }
            pattern->DispatchFocusActiveEvent(true);
            return true;
        }
        return false;
    });
}

void UIExtensionPattern::InitKeyEventOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnKeyEventInternal([wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            if (event.IsPreIme()) {
                TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "KeyEvent Internal preIme.");
                return pattern->HandleKeyEvent(event);
            }
            auto host = pattern->GetHost();
            CHECK_NULL_RETURN(host, false);
            auto pipeline = host->GetContextRefPtr();
            CHECK_NULL_RETURN(pipeline, false);
            bool isBypassInner =
                event.IsKey({ KeyCode::KEY_TAB }) && pipeline && pipeline->IsTabJustTriggerOnKeyEvent();
            bool forceProcessKeyEvent = pattern->GetForceProcessOnKeyEventInternal();
            bool sendKey = !isBypassInner || forceProcessKeyEvent;
            TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "KeyEvent Internal will %{public}s send, bypass[%{public}d], isForce[%{public}d].",
                sendKey ? "" : "not", isBypassInner, forceProcessKeyEvent);
            if (sendKey) {
                pattern->SetForceProcessOnKeyEventInternal(false);
                return pattern->HandleKeyEvent(event);
            }
        }
        return false;
    });
}

#ifdef SUPPORT_DIGITAL_CROWN
void UIExtensionPattern::InitCrownEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnCrownEventInternal([wp = WeakClaim(this)](const CrownEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->HandleCrownEvent(event);
        }
        return false;
    });
}

void UIExtensionPattern::HandleCrownEvent(const CrownEvent& event)
{
    if (event.action == Ace::CrownAction::UNKNOWN) {
        UIEXT_LOGE("action is UNKNOWN");
        return;
    }
    auto pointerEvent = event.GetPointerEvent();
    CHECK_NULL_VOID(pointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Platform::CalculatePointerEvent(pointerEvent, host);
    DispatchPointerEvent(pointerEvent);
}
#endif

void UIExtensionPattern::InitKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetIsNodeNeedKey(true);
    InitKeyEventOnFocus(focusHub);
    InitKeyEventOnBlur(focusHub);
    InitKeyEventOnClearFocusState(focusHub);
    InitKeyEventOnPaintFocusState(focusHub);
    InitKeyEventOnKeyEvent(focusHub);
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
        UIEXT_LOGD("focus by tab is %{public}d.", pipeline->GetIsFocusingByTab());
        if (!pipeline->GetIsFocusingByTab()) {
            SetForceProcessOnKeyEventInternal(true);
        }
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
    SetForceProcessOnKeyEventInternal(false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    uiExtensionManager->RegisterUIExtensionInFocus(nullptr, nullptr);
}

bool UIExtensionPattern::HandleTouchEvent(
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_RETURN(pointerEvent, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (pointerEvent->GetSourceType() == OHOS::MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        return false;
    }
    auto originalAction = pointerEvent->GetPointerAction();
    if (originalAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE ||
        originalAction == OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        return false;
    }
    auto newPointerEvent =
        PlatformUtils::CopyPointerEventWithExtraProperty(pointerEvent, AceLogTag::ACE_UIEXTENSIONCOMPONENT);
    CHECK_NULL_RETURN(newPointerEvent, false);
    Platform::CalculatePointerEvent(newPointerEvent, host);
    DispatchPointerEvent(newPointerEvent);
    return true;
}

void UIExtensionPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetSourceDevice() != SourceType::TOUCH) {
        UIEXT_LOGE("The source type is not TOUCH, type %{public}d.", info.GetSourceDevice());
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
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
    const auto pointerEvent = info.GetPointerEvent();
    if (!pointerEvent) {
        UIEXT_LOGE("The pointerEvent is empty.");
        return;
    }
    if (focusState_ && pointerEvent->GetPointerAction() == MMI::PointerEvent::POINTER_ACTION_UP) {
        if (needReSendFocusToUIExtension_) {
            HandleFocusEvent();
            needReSendFocusToUIExtension_ = false;
        }
        SetForceProcessOnKeyEventInternal(true);
    }
}

void UIExtensionPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        UIEXT_LOGE("The source type is not MOUSE.");
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
        SetForceProcessOnKeyEventInternal(true);
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hub = host->GetFocusHub();
    CHECK_NULL_RETURN(hub, false);
    if (isKeyAsync_) {
        sessionWrapper_->NotifyKeyEventAsync(event.rawKeyEvent, false);
        return true;
    }

    bool isTab = event.IsKey({ KeyCode::KEY_TAB });
    if (!isTab) {
        SetForceProcessOnKeyEventInternal(true);
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
    std::shared_ptr<MMI::PointerEvent> newPointerEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);
    CHECK_NULL_VOID(newPointerEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Platform::CalculatePointerEvent(newPointerEvent, host, true);
    Platform::UpdatePointerAction(newPointerEvent, info.action);
    DispatchPointerEvent(newPointerEvent);
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
    UIEXT_LOGI("OnError the state is changing from '%{public}s' to 'NONE', errorCode = %{public}d.",
        ToString(state_), code);
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
    // Release the session if current UEC is use for UIExtensionAbility && not use for modal UIextension.
    if ((sessionType_ == SessionType::UI_EXTENSION_ABILITY) && (usage_ != UIExtensionUsage::MODAL)
        && sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        sessionWrapper_->DestroySession();
    }
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
        if (needReNotifyForeground_) {
            UIEXT_LOGI("Should NotifyForeground after MountToParent though visable");
            return;
        }
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
            UIEXT_LOGI("No WindowScene when OnMountToParentDone, wait.");
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
            UIEXT_LOGI("No WindowScene when AfterMountToParent, wait.");
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
    if (IsMoving()) {
        UIEXT_LOGI("HandleVisibleAreaChange when uec is moving.");
        return;
    }

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

int32_t UIExtensionPattern::GetInstanceIdFromHost() const
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
    if (hasAttachContext_) {
        UpdateWant(wantWrap);
    } else {
        curWant_ = wantWrap;
    }
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
    UIEXT_LOGD("Dump UIE Info In String Format");
    DumpLog::GetInstance().AddDesc(std::string("focusWindowId: ").append(std::to_string(focusWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("realHostWindowId: ").append(std::to_string(realHostWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("want: ").append(want_));
    DumpLog::GetInstance().AddDesc(std::string("displayArea: ").append(displayArea_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("reason: ").append(std::to_string(sessionWrapper_->GetReasonDump())));
    DumpLog::GetInstance().AddDesc(std::string("focusStatus: ").append(std::to_string(focusState_)));
    DumpLog::GetInstance().AddDesc(std::string("abilityState: ").append(ToString(state_)));
    std::string eventProxyStr = "[]";
    if (platformEventProxy_) {
        eventProxyStr = platformEventProxy_->GetCurEventProxyToString();
    }
    DumpLog::GetInstance().AddDesc(std::string("eventProxy: ").append(eventProxyStr));

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        UIEXT_LOGI("Not Support Dump Extra UIE Info");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dumpNodeIter = std::find(params.begin(), params.end(), std::to_string(host->GetId()));
    if (dumpNodeIter != params.end()) {
        params.erase(dumpNodeIter);
    }
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
    std::string eventProxyStr = "[]";
    if (platformEventProxy_) {
        eventProxyStr = platformEventProxy_->GetCurEventProxyToString();
    }
    json->Put("eventProxy: ", eventProxyStr.c_str());

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        UIEXT_LOGI("Not Support Dump Extra UIE Info");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dumpNodeIter = std::find(params.begin(), params.end(), std::to_string(host->GetId()));
    if (dumpNodeIter != params.end()) {
        params.erase(dumpNodeIter);
    }
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

void UIExtensionPattern::DumpOthers()
{
    CHECK_NULL_VOID(sessionWrapper_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    if (params.empty()) {
        return;
    }
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

void UIExtensionPattern::RegisterEventProxyFlagCallback()
{
    RegisterUIExtBusinessConsumeCallback(UIContentBusinessCode::EVENT_PROXY,
        [weak = WeakClaim(this)](const AAFwk::Want& data) -> int32_t {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, -1);
            std::string type = "";
            int32_t eventFlags = 0;
            if (data.HasParameter("type")) {
                type = data.GetStringParam("type");
            }
            if (type == "OccupyEvents") {
                if (data.HasParameter("eventFlags")) {
                    eventFlags = data.GetIntParam("eventFlags", 0);
                }
                pattern->SetEventProxyFlag(eventFlags);
                return 0;
            } else {
                return -1;
            }
        });
}

void UIExtensionPattern::SendPageModeToProvider()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto pageMode = accessibilityProperty->GetAccessibilitySamePage();
    AAFwk::Want data;
    data.SetParam("pageMode", pageMode);
    SendBusinessData(UIContentBusinessCode::SEND_PAGE_MODE_TO_UEA, data, BusinessDataSendType::ASYNC);
}

void UIExtensionPattern::RegisterReceivePageModeRequestCallback()
{
    auto callback = [weak = WeakClaim(this)](const AAFwk::Want& data) -> int32_t {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, -1);
        auto host = pattern->GetHost();
        CHECK_NULL_RETURN(host, -1);
        if (data.HasParameter("requestPageMode")) {
            pattern->SendPageModeToProvider();
            return 0;
        }
        return -1;
    };
    RegisterUIExtBusinessConsumeCallback(UIContentBusinessCode::SEND_PAGE_MODE_REQUEST, callback);
}

void UIExtensionPattern::RegisterGetAvoidInfoCallback()
{
    auto callback = [weak = WeakClaim(this)](const AAFwk::Want&) -> int32_t {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, -1);
        auto host = pattern->GetHost();
        CHECK_NULL_RETURN(host, -1);
        auto context = host->GetContext();
        CHECK_NULL_RETURN(context, -1);
        auto avoidInfoMgr = context->GetAvoidInfoManager();
        CHECK_NULL_RETURN(avoidInfoMgr, -1);
        AAFwk::Want avoidInfoWant;
        const auto& info = pattern->GetAvoidInfo();
        avoidInfoMgr->BuildAvoidInfo(info, avoidInfoWant);
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UECPattern send avoidInfo: %{public}s.", info.ToString().c_str());
        pattern->SendBusinessData(UIContentBusinessCode::NOTIFY_AVOID_INFO_CHANGE,
            std::move(avoidInfoWant), BusinessDataSendType::ASYNC);
        return 0;
    };
    RegisterUIExtBusinessConsumeCallback(UIContentBusinessCode::GET_AVOID_INFO, callback);
}

bool UIExtensionPattern::SendBusinessDataSyncReply(
    UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply, RSSubsystemId subSystemId)
{
    CHECK_NULL_RETURN(sessionWrapper_, false);
    UIEXT_LOGI("SendBusinessDataSyncReply businessCode=%{public}u.", code);
    return sessionWrapper_->SendBusinessDataSyncReply(code, data, reply, subSystemId);
}

bool UIExtensionPattern::SendBusinessData(
    UIContentBusinessCode code, const AAFwk::Want& data, BusinessDataSendType type, RSSubsystemId subSystemId)
{
    CHECK_NULL_RETURN(sessionWrapper_, false);
    UIEXT_LOGD("SendBusinessData businessCode=%{public}u.", code);
    return sessionWrapper_->SendBusinessData(code, data, type, subSystemId);
}

void UIExtensionPattern::OnUIExtBusinessReceiveReply(
    UIContentBusinessCode code, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply)
{
    UIEXT_LOGI("OnUIExtBusinessReceiveReply businessCode=%{public}u.", code);
    auto it = businessDataUECConsumeReplyCallbacks_.find(code);
    if (it == businessDataUECConsumeReplyCallbacks_.end()) {
        return;
    }
    auto callback = it->second;
    CHECK_NULL_VOID(callback);
    callback(data, reply);
}

void UIExtensionPattern::OnUIExtBusinessReceive(
    UIContentBusinessCode code, const AAFwk::Want& data)
{
    UIEXT_LOGI("OnUIExtBusinessReceive businessCode=%{public}u.", code);
    auto it = businessDataUECConsumeCallbacks_.find(code);
    if (it == businessDataUECConsumeCallbacks_.end()) {
        return;
    }
    auto callback = it->second;
    CHECK_NULL_VOID(callback);
    callback(data);
}

void UIExtensionPattern::RegisterUIExtBusinessConsumeReplyCallback(
    UIContentBusinessCode code, BusinessDataUECConsumeReplyCallback callback)
{
    UIEXT_LOGI("RegisterUIExtBusinessConsumeReplyCallback businessCode=%{public}u.", code);
    businessDataUECConsumeReplyCallbacks_.try_emplace(code, callback);
}

void UIExtensionPattern::RegisterUIExtBusinessConsumeCallback(
    UIContentBusinessCode code, BusinessDataUECConsumeCallback callback)
{
    UIEXT_LOGI("RegisterUIExtBusinessConsumeCallback businessCode=%{public}u.", code);
    businessDataUECConsumeCallbacks_.try_emplace(code, callback);
}

void UIExtensionPattern::NotifyHostWindowMode()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto mode = container->GetWindowMode();
    NotifyHostWindowMode(mode);
}

void UIExtensionPattern::NotifyHostWindowMode(Rosen::WindowMode mode)
{
    UIEXT_LOGI("NotifyHostWindowMode: instanceId = %{public}d, followStrategy = %{public}d, mode = %{public}d",
        instanceId_, isWindowModeFollowHost_, static_cast<int32_t>(mode));
    CHECK_NULL_VOID(sessionWrapper_);
    if (isWindowModeFollowHost_ && mode != Rosen::WindowMode::WINDOW_MODE_UNDEFINED) {
        int32_t windowMode = static_cast<int32_t>(mode);
        sessionWrapper_->NotifyHostWindowMode(windowMode);
    }
}

void UIExtensionPattern::SetOnDrawReadyCallback(const std::function<void()>&& callback)
{
    onDrawReadyCallback_ = std::move(callback);
}

void UIExtensionPattern::FireOnDrawReadyCallback()
{
    ReplacePlaceholderByContent();
    if (onDrawReadyCallback_) {
        onDrawReadyCallback_();
    }
}

bool UIExtensionPattern::IsAncestorNodeGeometryChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_GEOMETRY_CHANGE) == FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
}

bool UIExtensionPattern::IsAncestorNodeTransformChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_TRANSFORM_CHANGE) == FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
}

void UIExtensionPattern::OnFrameNodeChanged(FrameNodeChangeInfoFlag flag)
{
    if (IsAncestorNodeGeometryChange(flag) || IsAncestorNodeTransformChange(flag)) {
        DispatchDisplayArea();
    }
    if (!(IsAncestorNodeTransformChange(flag) || IsAncestorNodeGeometryChange(flag))) {
        return;
    }
    TransferAccessibilityRectInfo();
}

AccessibilityParentRectInfo UIExtensionPattern::GetAccessibilityRectInfo() const
{
    ACE_SCOPED_TRACE("GetAccessibilityRectInfo");
    AccessibilityParentRectInfo rectInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, rectInfo);
    auto pipeline = host->GetContextRefPtr();
    if (pipeline) {
        auto accessibilityManager = pipeline->GetAccessibilityManager();
        if (accessibilityManager) {
            return accessibilityManager->GetTransformRectInfoRelativeToWindow(host, pipeline);
        }
    }
    auto rect = host->GetTransformRectRelativeToWindow(true);
    VectorF finalScale = host->GetTransformScaleRelativeToWindow();
    rectInfo.left = static_cast<int32_t>(rect.Left());
    rectInfo.top = static_cast<int32_t>(rect.Top());
    rectInfo.scaleX = finalScale.x;
    rectInfo.scaleY = finalScale.y;
    return rectInfo;
}

// Once enter this function, must calculate and transfer data to provider
void UIExtensionPattern::TransferAccessibilityRectInfo(bool isForce)
{
    if (!(isForce || AceApplicationInfo::GetInstance().IsAccessibilityEnabled())) {
        return;
    }
    auto parentRectInfo = GetAccessibilityRectInfo();
    AAFwk::Want data;
    data.SetParam("left", parentRectInfo.left);
    data.SetParam("top", parentRectInfo.top);
    data.SetParam("scaleX", parentRectInfo.scaleX);
    data.SetParam("scaleY", parentRectInfo.scaleY);
    data.SetParam("centerX", parentRectInfo.rotateTransform.centerX);
    data.SetParam("centerY", parentRectInfo.rotateTransform.centerY);
    data.SetParam("innerCenterX", parentRectInfo.rotateTransform.innerCenterX);
    data.SetParam("innerCenterY", parentRectInfo.rotateTransform.innerCenterY);
    data.SetParam("rotateDegree", parentRectInfo.rotateTransform.rotateDegree);
    TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "UEC Transform rect param[scaleX:%{public}f, scaleY:%{public}f], rotateDegree: %{public}d.",
        parentRectInfo.scaleX, parentRectInfo.scaleY, parentRectInfo.rotateTransform.rotateDegree);
    SendBusinessData(UIContentBusinessCode::TRANSFORM_PARAM, data, BusinessDataSendType::ASYNC);
}

void UIExtensionPattern::UpdateWMSUIExtProperty(
    UIContentBusinessCode code, const AAFwk::Want& data, RSSubsystemId subSystemId)
{
    if (state_ != AbilityState::FOREGROUND) {
        UIEXT_LOGI("UEC UpdatWMSUIExtProperty state=%{public}s.", ToString(state_));
        return;
    }
    SendBusinessData(code, data, BusinessDataSendType::ASYNC, subSystemId);
}
} // namespace OHOS::Ace::NG
