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

#include "core/components_ng/pattern/ui_extension/session_wrapper_impl.h"

#include <cmath>
#include <memory>

#include "accessibility_event_info.h"
#include "interfaces/include/ws_common.h"
#include "refbase.h"
#include "session_manager/include/extension_session_manager.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"
#include "ui/rs_surface_node.h"
#include "want_params.h"
#include "wm/wm_common.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
// Defines all error names and messages.
constexpr char START_FAIL_NAME[] = "start_ability_fail";
constexpr char START_FAIL_MESSAGE[] = "Start ui extension ability failed, please check the want of UIextensionAbility.";
constexpr char BACKGROUND_FAIL_NAME[] = "background_fail";
constexpr char BACKGROUND_FAIL_MESSAGE[] = "background ui extension ability failed, please check AMS log.";
constexpr char TERMINATE_FAIL_NAME[] = "terminate_fail";
constexpr char TERMINATE_FAIL_MESSAGE[] = "terminate ui extension ability failed, please check AMS log.";
constexpr char PULL_FAIL_NAME[] = "extension_pulling_up_fail";
constexpr char PULL_FAIL_MESSAGE[] = "pulling another embedded component failed, not allowed to cascade.";
constexpr char EXIT_ABNORMALLY_NAME[] = "extension_exit_abnormally";
constexpr char EXIT_ABNORMALLY_MESSAGE[] = "the extension ability exited abnormally, please check AMS log.";
constexpr char EXTENSION_TRANSPARENT_NAME[] = "extension_node_transparent";
constexpr char EXTENSION_TRANSPARENT_MESSAGE[] = "the extension ability has transparent node.";
constexpr char LIFECYCLE_TIMEOUT_NAME[] = "extension_lifecycle_timeout";
constexpr char LIFECYCLE_TIMEOUT_MESSAGE[] = "the lifecycle of extension ability is timeout, please check AMS log.";
constexpr char EVENT_TIMEOUT_NAME[] = "handle_event_timeout";
constexpr char EVENT_TIMEOUT_MESSAGE[] = "the extension ability has timed out processing the key event.";
// Defines the want parameter to control the soft-keyboard area change of the provider.
constexpr char OCCUPIED_AREA_CHANGE_KEY[] = "ability.want.params.IsNotifyOccupiedAreaChange";
// Set the UIExtension type of the EmbeddedComponent.
constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
const std::string EMBEDDED_UI("embeddedUI");
constexpr int32_t AVOID_DELAY_TIME = 30;
constexpr int32_t INVALID_WINDOW_ID = -1;
constexpr uint32_t REMOVE_PLACEHOLDER_DELAY_TIME = 32;
} // namespace

class UIExtensionLifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit UIExtensionLifecycleListener(const WeakPtr<SessionWrapper>& sessionWrapper)
        : sessionWrapper_(sessionWrapper)
    {}
    virtual ~UIExtensionLifecycleListener() = default;

    void OnActivation() override {}
    void OnForeground() override {}
    void OnBackground() override {}

    void OnConnect() override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnConnect();
    }

    void OnDisconnect() override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnDisconnect(false);
    }

    void OnExtensionDied() override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnDisconnect(true);
    }

    void OnExtensionTimeout(int32_t errorCode) override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnExtensionTimeout(errorCode);
    }

    void OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t uiExtensionOffset) override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnAccessibilityEvent(info, uiExtensionOffset);
    }

private:
    WeakPtr<SessionWrapper> sessionWrapper_;
};

/************************************************ Begin: Initialization ***********************************************/
SessionWrapperImpl::SessionWrapperImpl(const WeakPtr<UIExtensionPattern>& hostPattern, int32_t instanceId,
    bool isTransferringCaller, SessionType sessionType)
    : hostPattern_(hostPattern), instanceId_(instanceId), isTransferringCaller_(isTransferringCaller),
      sessionType_(sessionType)
{
    auto pattern = hostPattern.Upgrade();
    uiExtensionId_ = pattern ? pattern->GetUiExtensionId() : 0;
    taskExecutor_ = Container::CurrentTaskExecutor();
}

SessionWrapperImpl::~SessionWrapperImpl() {}

void SessionWrapperImpl::InitAllCallback()
{
    CHECK_NULL_VOID(session_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    int32_t callSessionId = GetSessionId();
    foregroundCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]
        (OHOS::Rosen::WSError errcode) {
        if (errcode == OHOS::Rosen::WSError::WS_OK) {
            return;
        }
        taskExecutor->PostTask(
            [weak, errcode, callSessionId] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "foregroundCallback_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                int32_t code = pattern->IsCompatibleOldVersion()
                    ? static_cast<int32_t>(errcode) : ERROR_CODE_UIEXTENSION_FOREGROUND_FAILED;
                pattern->FireOnErrorCallback(code, START_FAIL_NAME, START_FAIL_MESSAGE);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionForegroundError");
    };
    backgroundCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]
        (OHOS::Rosen::WSError errcode) {
        if (errcode == OHOS::Rosen::WSError::WS_OK) {
            return;
        }
        taskExecutor->PostTask(
            [weak, errcode, callSessionId] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "backgroundCallback_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                int32_t code = pattern->IsCompatibleOldVersion()
                    ? static_cast<int32_t>(errcode) : ERROR_CODE_UIEXTENSION_BACKGROUND_FAILED;
                pattern->FireOnErrorCallback(
                    code, BACKGROUND_FAIL_NAME, BACKGROUND_FAIL_MESSAGE);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionBackgroundError");
    };
    destructionCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]
        (OHOS::Rosen::WSError errcode) {
        if (errcode == OHOS::Rosen::WSError::WS_OK) {
            return;
        }
        taskExecutor->PostTask(
            [weak, errcode, callSessionId] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "destructionCallback_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                int32_t code = pattern->IsCompatibleOldVersion()
                    ? static_cast<int32_t>(errcode) : ERROR_CODE_UIEXTENSION_DESTRUCTION_FAILED;
                pattern->FireOnErrorCallback(
                    code, TERMINATE_FAIL_NAME, TERMINATE_FAIL_MESSAGE);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionDestructionError");
    };
    sessionCallbacks->transferAbilityResultFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_,
        sessionType = sessionType_, callSessionId](int32_t code, const AAFwk::Want& want) {
        taskExecutor->PostTask(
            [weak, code, want, sessionType, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "transferAbilityResultFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                if (sessionType == SessionType::UI_EXTENSION_ABILITY && pattern->IsCompatibleOldVersion()) {
                    pattern->FireOnResultCallback(code, want);
                } else {
                    pattern->FireOnTerminatedCallback(code, MakeRefPtr<WantWrapOhos>(want));
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionTransferAbilityResult");
    };
    sessionCallbacks->transferExtensionDataFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId](
        const AAFwk::WantParams& params) {
        taskExecutor->PostTask(
            [weak, params, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "transferExtensionDataFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->FireOnReceiveCallback(params);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionReceiveCallback");
    };
    sessionCallbacks->notifyRemoteReadyFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]() {
        taskExecutor->PostTask(
            [weak, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "notifyRemoteReadyFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->FireOnRemoteReadyCallback();
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionRemoteReadyCallback");
    };
    sessionCallbacks->notifySyncOnFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]() {
        taskExecutor->PostTask(
            [weak, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "notifySyncOnFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->FireSyncCallbacks();
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionSyncCallbacks");
    };
    sessionCallbacks->notifyAsyncOnFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]() {
        taskExecutor->PostTask(
            [weak, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "notifyAsyncOnFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->FireAsyncCallbacks();
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionAsyncCallbacks");
    };
    sessionCallbacks->notifyBindModalFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId]() {
        taskExecutor->PostSyncTask(
            [weak, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "notifyBindModalFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->FireBindModalCallback();
            },
            TaskExecutor::TaskType::UI, "ArkUIUIExtensionBindModalCallback");
    };
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_ = [instanceId = instanceId_](
                                                          Rosen::AvoidAreaType type) -> Rosen::AvoidArea {
        Rosen::AvoidArea avoidArea;
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_RETURN(container, avoidArea);
        avoidArea = container->GetAvoidAreaByType(type);
        return avoidArea;
    };
    sessionCallbacks->notifyExtensionEventFunc_ =
        [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId](uint32_t event) {
        taskExecutor->PostDelayedTask(
            [weak, callSessionId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "notifyBindModalFunc_: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->OnAreaUpdated();
            },
            TaskExecutor::TaskType::UI, REMOVE_PLACEHOLDER_DELAY_TIME, "ArkUIUIExtensionEventCallback");
    };
}
/************************************************ End: Initialization *************************************************/

/************************************************ Begin: About session ************************************************/
Rosen::SessionViewportConfig ConvertToRosenSessionViewportConfig(const SessionViewportConfig& config)
{
    Rosen::SessionViewportConfig config_ = {
        .isDensityFollowHost_ = config.isDensityFollowHost_,
        .density_ = config.density_,
        .displayId_ = config.displayId_,
        .orientation_ = config.orientation_,
        .transform_ = config.transform_,
    };
    return config_;
}

void SessionWrapperImpl::CreateSession(const AAFwk::Want& want, const SessionConfig& config)
{
    UIEXT_LOGI("The session is created with want = %{private}s", want.ToString().c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto realHostWindowId = pipeline->GetRealHostWindowId();
    auto wantPtr = std::make_shared<Want>(want);
    if (sessionType_ == SessionType::UI_EXTENSION_ABILITY) {
        if (wantPtr->GetStringParam(UI_EXTENSION_TYPE_KEY) == EMBEDDED_UI) {
            UIEXT_LOGE("The UIExtensionComponent is not allowed to start the EmbeddedUIExtensionAbility.");
            return;
        }
        if ((container->IsUIExtensionAbilityHost() && container->IsUIExtensionSubWindow())) {
            UIEXT_LOGE("The UIExtensionComponent does not allow nested pulling of another.");
            auto pattern = hostPattern_.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE, PULL_FAIL_NAME, PULL_FAIL_MESSAGE);
            return;
        }
    }
    if (sessionType_ == SessionType::EMBEDDED_UI_EXTENSION) {
        if ((container->IsUIExtensionWindow()) ||
            (container->IsUIExtensionAbilityProcess() && container->IsUIExtensionSubWindow())) {
            UIEXT_LOGE("The EmbeddedComponent does not allow nested pulling of another.");
            auto pattern = hostPattern_.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_FORBID_CASCADE, PULL_FAIL_NAME, PULL_FAIL_MESSAGE);
            return;
        }
        WantParams wantParams;
        wantPtr->SetParam(UI_EXTENSION_TYPE_KEY, EMBEDDED_UI);
    }
    isNotifyOccupiedAreaChange_ = want.GetBoolParam(OCCUPIED_AREA_CHANGE_KEY, true);
    uint32_t parentWindowType = 0;
    if (container->IsUIExtensionWindow()) {
        parentWindowType = container->GetParentWindowType();
    } else {
        parentWindowType = container->GetWindowType();
    }
    UIEXT_LOGI("Want param isNotifyOccupiedAreaChange is %{public}d, realHostWindowId: %{public}u,"
        " parentWindowType: %{public}u",
        isNotifyOccupiedAreaChange_, realHostWindowId, parentWindowType);
    auto callerToken = container->GetToken();
    auto parentToken = container->GetParentToken();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    SessionViewportConfig sessionViewportConfig;
    sessionViewportConfig.isDensityFollowHost_ = pattern->GetDensityDpi();
    sessionViewportConfig.density_ = context->GetCurrentDensity();
    sessionViewportConfig.displayId_ = 0;
    sessionViewportConfig.orientation_ = static_cast<int32_t>(SystemProperties::GetDeviceOrientation());
    sessionViewportConfig.transform_ = context->GetTransformHint();
    pattern->SetSessionViewportConfig(sessionViewportConfig);
    Rosen::SessionInfo extensionSessionInfo;
    extensionSessionInfo.bundleName_ = want.GetElement().GetBundleName();
    extensionSessionInfo.abilityName_ = want.GetElement().GetAbilityName();
    extensionSessionInfo.callerToken_ = callerToken;
    extensionSessionInfo.rootToken_ = (isTransferringCaller_ && parentToken) ? parentToken : callerToken;
    extensionSessionInfo.want = wantPtr;
    extensionSessionInfo.parentWindowType_ = parentWindowType;
    extensionSessionInfo.realParentId_ = static_cast<int32_t>(realHostWindowId);
    extensionSessionInfo.uiExtensionUsage_ = static_cast<uint32_t>(config.uiExtensionUsage);
    extensionSessionInfo.isAsyncModalBinding_ = config.isAsyncModalBinding;
    extensionSessionInfo.config_ = ConvertToRosenSessionViewportConfig(sessionViewportConfig);
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    CHECK_NULL_VOID(session_);
    UpdateSessionConfig();
    lifecycleListener_ = std::make_shared<UIExtensionLifecycleListener>(AceType::WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
    InitAllCallback();
}

void SessionWrapperImpl::UpdateSessionConfig()
{
    auto extConfig = session_->GetSystemConfig();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hostConfig = pipeline->GetKeyboardAnimationConfig();
    extConfig.animationIn_ = {
        hostConfig.curveIn_.curveType_, hostConfig.curveIn_.curveParams_, hostConfig.curveIn_.duration_};
    extConfig.animationOut_ = {
        hostConfig.curveOut_.curveType_, hostConfig.curveOut_.curveParams_, hostConfig.curveOut_.duration_};
    session_->SetSystemConfig(extConfig);
}

void SessionWrapperImpl::DestroySession()
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("DestroySession, persistentid = %{public}d.", session_->GetPersistentId());
    session_->UnregisterLifecycleListener(lifecycleListener_);
    session_ = nullptr;
}

bool SessionWrapperImpl::IsSessionValid()
{
    return session_ != nullptr;
}

int32_t SessionWrapperImpl::GetSessionId() const
{
    return session_ ? session_->GetPersistentId() : 0;
}

const std::shared_ptr<AAFwk::Want> SessionWrapperImpl::GetWant()
{
    return session_ ? session_->GetSessionInfo().want : nullptr;
}
/************************************************ End: About session **************************************************/

/************************************************ Begin: Synchronous interface for event notify ***********************/
bool SessionWrapperImpl::NotifyFocusEventSync(bool isFocus)
{
    return false;
}
bool SessionWrapperImpl::NotifyFocusStateSync(bool focusState)
{
    return false;
}

bool SessionWrapperImpl::NotifyBackPressedSync()
{
    CHECK_NULL_RETURN(session_, false);
    bool isConsumed = false;
    session_->TransferBackPressedEventForConsumed(isConsumed);
    UIEXT_LOGI("Back event notified to uiextension, persistentid = %{public}d and %{public}s consumed.",
        GetSessionId(), isConsumed ? "is" : "is not");
    return isConsumed;
}

bool SessionWrapperImpl::NotifyPointerEventSync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return false;
}

bool SessionWrapperImpl::NotifyKeyEventSync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    CHECK_NULL_RETURN(session_, false);
    bool isConsumed = false;
    bool isTimeout = false;
    session_->TransferKeyEventForConsumed(keyEvent, isConsumed, isTimeout, isPreIme);
    auto pattern = hostPattern_.Upgrade();
    if (isTimeout && pattern) {
        pattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_EVENT_TIMEOUT, EVENT_TIMEOUT_NAME, EVENT_TIMEOUT_MESSAGE);
        return false;
    }
    UIEXT_LOGI("Key event notified to uiextension, persistentid = %{public}d and %{public}s consumed.",
        GetSessionId(), isConsumed ? "is" : "is not");
    return isConsumed;
}

bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    CHECK_NULL_RETURN(session_, false);
    session_->TransferKeyEventAsync(keyEvent, isPreIme);
    return true;
}

bool SessionWrapperImpl::NotifyAxisEventSync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}
/************************************************ End: Synchronous interface for event notify *************************/

/************************************************ Begin: Asynchronous interface for event notify **********************/
bool SessionWrapperImpl::NotifyFocusEventAsync(bool isFocus)
{
    CHECK_NULL_RETURN(session_, false);
    UIEXT_LOGI("Notify uiextension, persistentid = %{public}d to %{public}s the focus state.",
        GetSessionId(), isFocus ? "paint" : "clear");
    session_->TransferFocusActiveEvent(isFocus);
    return true;
}

bool SessionWrapperImpl::NotifyFocusStateAsync(bool focusState)
{
    CHECK_NULL_RETURN(session_, false);
    UIEXT_LOGI("%{public}s state notified to uiextension, persistentid = %{public}d.",
        focusState ? "focused" : "unfocused", GetSessionId());
    session_->TransferFocusStateEvent(focusState);
    return true;
}

bool SessionWrapperImpl::NotifyBackPressedAsync()
{
    return false;
}
bool SessionWrapperImpl::NotifyPointerEventAsync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    if (session_ && pointerEvent) {
        UIEXT_LOGI("Transfer pointer event with 'id = %{public}d' to uiextension, persistentid = %{public}d.",
            pointerEvent->GetId(), GetSessionId());
        session_->TransferPointerEvent(pointerEvent);
    }
    return false;
}
bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    if (session_ && keyEvent) {
        UIEXT_LOGI("Transfer key event with 'id = %{public}d' to uiextension, persistentid = %{public}d.",
            keyEvent->GetId(), GetSessionId());
        session_->TransferKeyEvent(keyEvent);
    }
    return false;
}
bool SessionWrapperImpl::NotifyAxisEventAsync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}
/************************************************ End: Asynchronous interface for event notify ************************/

/************************************************ Begin: The lifecycle interface **************************************/
void SessionWrapperImpl::NotifyCreate() {}

int32_t SessionWrapperImpl::GetWindowSceneId()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, INVALID_WINDOW_ID);
    auto hostWindowNode = WindowSceneHelper::FindWindowScene(pattern->GetHost());
    CHECK_NULL_RETURN(hostWindowNode, INVALID_WINDOW_ID);
    auto hostNode = AceType::DynamicCast<FrameNode>(hostWindowNode);
    CHECK_NULL_RETURN(hostNode, INVALID_WINDOW_ID);
    auto hostPattern = hostNode->GetPattern<SystemWindowScene>();
    CHECK_NULL_RETURN(hostPattern, INVALID_WINDOW_ID);
    auto hostSession = hostPattern->GetSession();
    CHECK_NULL_RETURN(hostSession, INVALID_WINDOW_ID);
    return hostSession->GetPersistentId();
}

void SessionWrapperImpl::NotifyForeground()
{
    CHECK_NULL_VOID(session_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    int32_t windowSceneId = GetWindowSceneId();
    UIEXT_LOGI("NotifyForeground, persistentid = %{public}d, hostWindowId = %{public}u,"
        " windowSceneId = %{public}d, IsScenceBoardWindow: %{public}d.",
        session_->GetPersistentId(), hostWindowId, windowSceneId, container->IsScenceBoardWindow());
    if (container->IsScenceBoardWindow() && windowSceneId != INVALID_WINDOW_ID) {
        hostWindowId = static_cast<uint32_t>(windowSceneId);
    }
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->IsViewportConfigChanged()) {
        pattern->SetViewportConfigChanged(false);
        UpdateSessionViewportConfig();
    }
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        session_, hostWindowId, std::move(foregroundCallback_));
}

void SessionWrapperImpl::NotifyBackground()
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("NotifyBackground, persistentid = %{public}d.", session_->GetPersistentId());
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(
        session_, std::move(backgroundCallback_));
}

void SessionWrapperImpl::OnReleaseDone()
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("OnReleaseDone, persistentid = %{public}d.", session_->GetPersistentId());
    session_->UnregisterLifecycleListener(lifecycleListener_);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestructionDone(session_);
    session_ = nullptr;
}

void SessionWrapperImpl::NotifyDestroy(bool isHandleError)
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("NotifyDestroy, isHandleError = %{public}d, persistentid = %{public}d.",
        isHandleError, session_->GetPersistentId());
    if (isHandleError) {
        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(
            session_, std::move(destructionCallback_));
    } else {
        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(
            session_, nullptr);
    }
}

void SessionWrapperImpl::NotifyConfigurationUpdate() {}
/************************************************ End: The lifecycle interface ****************************************/

/************************************************ Begin: The interface for responsing provider ************************/
void SessionWrapperImpl::OnConnect()
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, wrapperWeak = WeakClaim(this), callSessionId]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "OnConnect: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
            }
            pattern->OnConnect();
            auto wrapper = wrapperWeak.Upgrade();
            CHECK_NULL_VOID(wrapper && wrapper->session_);
            ContainerScope scope(wrapper->instanceId_);
            if (auto hostWindowNode = WindowSceneHelper::FindWindowScene(pattern->GetHost())) {
                auto hostNode = AceType::DynamicCast<FrameNode>(hostWindowNode);
                CHECK_NULL_VOID(hostNode);
                auto hostPattern = hostNode->GetPattern<SystemWindowScene>();
                CHECK_NULL_VOID(hostPattern);
                wrapper->session_->SetParentSession(hostPattern->GetSession());
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionSessionConnect");
}

void SessionWrapperImpl::OnDisconnect(bool isAbnormal)
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, sessionType = sessionType_, isAbnormal, callSessionId]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "OnDisconnect: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
                return;
            }
            pattern->OnDisconnect(isAbnormal);
            if (sessionType == SessionType::UI_EXTENSION_ABILITY && pattern->IsCompatibleOldVersion()) {
                pattern->FireOnReleaseCallback(static_cast<int32_t>(isAbnormal));
                return;
            }
            if (isAbnormal) {
                pattern->FireOnErrorCallback(
                    ERROR_CODE_UIEXTENSION_EXITED_ABNORMALLY, EXIT_ABNORMALLY_NAME, EXIT_ABNORMALLY_MESSAGE);
            } else {
                pattern->FireOnTerminatedCallback(0, nullptr);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionSessionDisconnect");
}

void SessionWrapperImpl::OnExtensionTimeout(int32_t errorCode)
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, callSessionId, errorCode]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "OnExtensionTimeout: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
            }
            bool isTransparent = errorCode == ERROR_CODE_UIEXTENSION_TRANSPARENT;
            pattern->FireOnErrorCallback(
                isTransparent ? errorCode : ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT,
                isTransparent ? EXTENSION_TRANSPARENT_NAME : LIFECYCLE_TIMEOUT_NAME,
                isTransparent ? EXTENSION_TRANSPARENT_MESSAGE : LIFECYCLE_TIMEOUT_MESSAGE);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionTimeout");
}

void SessionWrapperImpl::OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset)
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, info, offset, callSessionId]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "OnAccessibilityEvent: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
            }
            pattern->OnAccessibilityEvent(info, offset);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionAccessibilityEvent");
}
/************************************************** End: The interface for responsing provider ************************/

/************************************************ Begin: The interface about the accessibility ************************/
void SessionWrapperImpl::TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
}

void SessionWrapperImpl::TransferAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void SessionWrapperImpl::TransferAccessibilityChildTreeDeregister()
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityChildTreeUnregister();
}

void SessionWrapperImpl::TransferAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityDumpChildInfo(params, info);
}
/************************************************ End: The interface about the accessibility **************************/

/***************************** Begin: The interface to control the display area and the avoid area ********************/
std::shared_ptr<Rosen::RSSurfaceNode> SessionWrapperImpl::GetSurfaceNode() const
{
    return session_ ? session_->GetSurfaceNode() : nullptr;
}

WindowSizeChangeReason SessionWrapperImpl::GetSizeChangeReason() const
{
    auto parentSession = session_->GetParentSession();
    auto reason = parentSession ? parentSession->GetSizeChangeReason() : session_->GetSizeChangeReason();
    return static_cast<WindowSizeChangeReason>(reason);
}

void SessionWrapperImpl::NotifyDisplayArea(const RectF& displayArea)
{
    CHECK_NULL_VOID(session_);
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    displayAreaWindow_ = pipeline->GetCurrentWindowRect();
    displayArea_ = displayArea + OffsetF(displayAreaWindow_.Left(), displayAreaWindow_.Top());
    std::shared_ptr<Rosen::RSTransaction> transaction;
    auto parentSession = session_->GetParentSession();
    auto reason = parentSession ? parentSession->GetSizeChangeReason() : session_->GetSizeChangeReason();
    reason_ = (uint32_t)reason;
    auto persistentId = parentSession ? parentSession->GetPersistentId() : session_->GetPersistentId();
    int32_t duration = 0;
    if (reason == Rosen::SizeChangeReason::ROTATION) {
        if (transaction_.lock()) {
            transaction = transaction_.lock();
            transaction_.reset();
        } else if (auto transactionController = Rosen::RSSyncTransactionController::GetInstance()) {
            transaction = transactionController->GetRSTransaction();
        }
        if (transaction && parentSession) {
            duration = pipeline->GetSyncAnimationOption().GetDuration();
            transaction->SetDuration(duration);
        }
    }
    ACE_SCOPED_TRACE("NotifyDisplayArea displayArea[%s], curWindow[%s], reason[%d], duration[%d]",
        displayArea_.ToString().c_str(), displayAreaWindow_.ToString().c_str(), reason, duration);
    UIEXT_LOGI("NotifyDisplayArea displayArea = %{public}s, curWindow = %{public}s, "
        "reason = %{public}d, duration = %{public}d, persistentId = %{public}d.",
        displayArea_.ToString().c_str(), displayAreaWindow_.ToString().c_str(),
        reason, duration, persistentId);
    session_->UpdateRect({ std::round(displayArea_.Left()), std::round(displayArea_.Top()),
        std::round(displayArea_.Width()), std::round(displayArea_.Height()) }, reason, "NotifyDisplayArea",
        transaction);
}

void SessionWrapperImpl::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(session_);
    auto reason = static_cast<Rosen::SizeChangeReason>(type);
    session_->UpdateSizeChangeReason(reason);
    if (rsTransaction && (type == WindowSizeChangeReason::ROTATION)) {
        transaction_ = rsTransaction;
    }
}

void SessionWrapperImpl::NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("NotifyAvoidArea, type: %{public}d, topRect = (%{public}d, %{public}d) - [%{public}d, %{public}d], "
        "bottomRect = (%{public}d, %{public}d) - [%{public}d, %{public}d], persistentId = %{public}d.",
        type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
        (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
        (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_, GetSessionId());
    ACE_SCOPED_TRACE("NotifyAvoidArea, type: %d, topRect: (%d, %d) - [%d, %d], bottomRect: (%d, %d) - [%d, %d]",
        type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
        (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
        (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_);
    session_->UpdateAvoidArea(sptr<Rosen::AvoidArea>::MakeSptr(avoidArea), static_cast<Rosen::AvoidAreaType>(type));
}

bool SessionWrapperImpl::NotifyOccupiedAreaChangeInfo(
    sptr<Rosen::OccupiedAreaChangeInfo> info, bool needWaitLayout)
{
    CHECK_NULL_RETURN(session_, false);
    CHECK_NULL_RETURN(info, false);
    CHECK_NULL_RETURN(isNotifyOccupiedAreaChange_, false);
    CHECK_NULL_RETURN(taskExecutor_, false);
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto curWindow = pipeline->GetCurrentWindowRect();
    int64_t curTime = GetCurrentTimestamp();
    if (displayAreaWindow_ != curWindow && needWaitLayout) {
        UIEXT_LOGI("OccupiedArea wait layout, displayAreaWindow: %{public}s, curWindow = %{public}s",
            displayAreaWindow_.ToString().c_str(), curWindow.ToString().c_str());
        taskExecutor_->PostDelayedTask(
            [info, weak = AceType::WeakClaim(this), curTime] {
                auto session = weak.Upgrade();
                if (session) {
                    session->InnerNotifyOccupiedAreaChangeInfo(info, true, curTime);
                }
            },
            TaskExecutor::TaskType::UI, AVOID_DELAY_TIME, "ArkUIVirtualKeyboardAreaChangeDelay");
    }

    taskExecutor_->PostTask(
        [info, weak = AceType::WeakClaim(this), curTime] {
            auto session = weak.Upgrade();
            if (session) {
                session->InnerNotifyOccupiedAreaChangeInfo(info, false, curTime);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIUecAreaChange");
    return true;
}

bool SessionWrapperImpl::InnerNotifyOccupiedAreaChangeInfo(
    sptr<Rosen::OccupiedAreaChangeInfo> info, bool isWaitTask, int64_t occupiedAreaTime)
{
    if (isWaitTask && occupiedAreaTime < lastOccupiedAreaTime_) {
        UIEXT_LOGW("OccupiedArea has been executed last time, persistentid = %{public}d.",
            GetSessionId());
        return false;
    }

    lastOccupiedAreaTime_ = occupiedAreaTime;
    CHECK_NULL_RETURN(session_, false);
    CHECK_NULL_RETURN(info, false);
    CHECK_NULL_RETURN(isNotifyOccupiedAreaChange_, false);
    int32_t keyboardHeight = static_cast<int32_t>(info->rect_.height_);
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto curWindow = pipeline->GetCurrentWindowRect();
    if (keyboardHeight > 0) {
        if (curWindow.Bottom() >= displayArea_.Bottom()) {
            int32_t spaceWindow = std::max(curWindow.Bottom() - displayArea_.Bottom(), 0.0);
            keyboardHeight = static_cast<int32_t>(std::max(keyboardHeight - spaceWindow, 0));
        } else {
            keyboardHeight = keyboardHeight + (displayArea_.Bottom() - curWindow.Bottom());
        }
    }
    sptr<Rosen::OccupiedAreaChangeInfo> newInfo = new Rosen::OccupiedAreaChangeInfo(
        info->type_, info->rect_, info->safeHeight_, info->textFieldPositionY_, info->textFieldHeight_);
    newInfo->rect_.height_ = static_cast<uint32_t>(keyboardHeight);
    UIEXT_LOGI("OccupiedArea keyboardHeight = %{public}d, displayArea = %{public}s, "
        "curWindow = %{public}s, persistentid = %{public}d.",
        keyboardHeight, displayArea_.ToString().c_str(), curWindow.ToString().c_str(), GetSessionId());
    session_->NotifyOccupiedAreaChangeInfo(newInfo);
    return true;
}

void SessionWrapperImpl::UpdateSessionViewportConfig()
{
    CHECK_NULL_VOID(session_);
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto config = pattern->GetSessionViewportConfig();
    UIEXT_LOGI("SessionViewportConfig: isDensityFollowHost_ = %{public}d, density_ = %{public}f, "
               "displayId_ = %{public}" PRIu64", orientation_ = %{public}d, transform_ = %{public}d",
        config.isDensityFollowHost_, config.density_, config.displayId_, config.orientation_, config.transform_);
    session_->UpdateSessionViewportConfig(ConvertToRosenSessionViewportConfig(config));
}

/***************************** End: The interface to control the display area and the avoid area **********************/

/************************************************ Begin: The interface to send the data for ArkTS *********************/
void SessionWrapperImpl::SendDataAsync(const AAFwk::WantParams& params) const
{
    UIEXT_LOGI("The data is asynchronously send and the session is %{public}s", session_ ? "valid" : "invalid");
    CHECK_NULL_VOID(session_);
    session_->TransferComponentData(params);
}

int32_t SessionWrapperImpl::SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const
{
    Rosen::WSErrorCode transferCode = Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED;
    UIEXT_LOGI("The data is synchronously send and the session is %{public}s", session_ ? "valid" : "invalid");
    if (session_) {
        transferCode = session_->TransferComponentDataSync(wantParams, reWantParams);
    }
    return static_cast<int32_t>(transferCode);
}
/************************************************ End: The interface to send the data for ArkTS ***********************/

/************************************************ Begin: The interface for UEC dump **********************************/
uint32_t SessionWrapperImpl::GetReasonDump() const
{
    return reason_;
}

void SessionWrapperImpl::NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    CHECK_NULL_VOID(session_);
    session_->NotifyDumpInfo(params, info);
}
/************************************************ End: The interface for UEC dump **********************************/
} // namespace OHOS::Ace::NG
