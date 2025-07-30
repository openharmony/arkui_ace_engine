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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"

#include <cmath>
#include <memory>

#include "accessibility_event_info.h"
#include "extension/extension_business_info.h"
#include "interfaces/include/ws_common.h"
#include "refbase.h"
#include "session_manager/include/extension_session_manager.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"
#include "ui/rs_surface_node.h"
#include "want_params.h"
#include "want_params_wrapper.h"
#include "wm/wm_common.h"
#include "wm/data_handler_interface.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_container_handler.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "pointer_event.h"
#include "string_wrapper.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/ui/rs_ui_context.h"

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
constexpr char UIEXTENSION_HOST_UICONTENT_TYPE[] = "ohos.ace.uiextension.hostUicontentType";
// Defines the want parameter to control the soft-keyboard area change of the provider.
constexpr char OCCUPIED_AREA_CHANGE_KEY[] = "ability.want.params.IsNotifyOccupiedAreaChange";
// Set the UIExtension type of the EmbeddedComponent.
constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
constexpr const char* const UIEXTENSION_CONFIG_FIELD = "ohos.system.window.uiextension.params";
const std::string EMBEDDED_UI("embeddedUI");
constexpr int32_t AVOID_DELAY_TIME = 30;
constexpr int32_t INVALID_WINDOW_ID = -1;
} // namespace

static bool IsDispatchExtensionDataToHostWindow(uint32_t customId)
{
    auto businessCode = static_cast<UIContentBusinessCode>(customId);
    return (businessCode >= UIContentBusinessCode::WINDOW_CODE_BEGIN &&
        businessCode <= UIContentBusinessCode::WINDOW_CODE_END);
}

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

    void OnExtensionDetachToDisplay() override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnExtensionDetachToDisplay();
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

void SessionWrapperImpl::InitForegroundCallback()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    int32_t callSessionId = GetSessionId();
    foregroundCallback_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] (OHOS::Rosen::WSError errcode) {
            if (errcode == OHOS::Rosen::WSError::WS_OK) {
                return;
            }

            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitForegroundCallback: taskExecutor is nullptr");
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionForegroundError");
        };
}

void SessionWrapperImpl::InitBackgroundCallback()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    int32_t callSessionId = GetSessionId();
    backgroundCallback_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] (OHOS::Rosen::WSError errcode) {
            if (errcode == OHOS::Rosen::WSError::WS_OK) {
                return;
            }

            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitBackgroundCallback: taskExecutor is nullptr");
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionBackgroundError");
        };
}

void SessionWrapperImpl::InitDestructionCallback()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    int32_t callSessionId = GetSessionId();
    destructionCallback_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] (OHOS::Rosen::WSError errcode) {
            if (errcode == OHOS::Rosen::WSError::WS_OK) {
                return;
            }

            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitDestructionCallback: taskExecutor is nullptr");
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionDestructionError");
        };
}

void SessionWrapperImpl::InitTransferAbilityResultFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitTransferAbilityResultFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->transferAbilityResultFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, sessionType = sessionType_, callSessionId] (
            int32_t code, const AAFwk::Want& want) {
                auto taskExecutor = weakTaskExecutor.Upgrade();
                if (taskExecutor == nullptr) {
                    TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                        "InitTransferAbilityResultFunc: taskExecutor is nullptr");
                        return;
                }

                taskExecutor->PostTask(
                    [weak, code, want, sessionType, callSessionId] () {
                        auto pattern = weak.Upgrade();
                        CHECK_NULL_VOID(pattern);
                        if (callSessionId != pattern->GetSessionId()) {
                            TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                                "transferAbilityResultFunc_: The callSessionId(%{public}d)"
                                    " is inconsistent with the curSession(%{public}d)",
                                callSessionId, pattern->GetSessionId());
                                return;
                        }

                        if (sessionType == SessionType::UI_EXTENSION_ABILITY
                            && pattern->IsCompatibleOldVersion()) {
                            pattern->FireOnResultCallback(code, want);
                        } else {
                            pattern->FireOnTerminatedCallback(code, MakeRefPtr<WantWrapOhos>(want));
                        }
                    }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionTransferAbilityResult");
            };
}

void SessionWrapperImpl::InitTransferExtensionDataFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitTransferExtensionDataFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->transferExtensionDataFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] (const AAFwk::WantParams& params) {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitTransferExtensionDataFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostTask(
                [weak, params, callSessionId] () {
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionReceiveCallback");
        };
}

void SessionWrapperImpl::InitNotifyRemoteReadyFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifyRemoteReadyFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->notifyRemoteReadyFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] () {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitNotifyRemoteReadyFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostTask(
                [weak, callSessionId] () {
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionRemoteReadyCallback");
        };
}

void SessionWrapperImpl::InitNotifySyncOnFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifySyncOnFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->notifySyncOnFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] () {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitNotifySyncOnFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostTask(
                [weak, callSessionId] () {
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionSyncCallbacks");
        };
}

void SessionWrapperImpl::InitNotifyAsyncOnFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifyAsyncOnFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->notifyAsyncOnFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] () {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitNotifyAsyncOnFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostTask(
                [weak, callSessionId] () {
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionAsyncCallbacks");
        };
}

void SessionWrapperImpl::InitNotifyBindModalFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifyBindModalFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->notifyBindModalFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] () {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitNotifyBindModalFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostSyncTask(
                [weak, callSessionId] () {
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
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionBindModalCallback");
        };
}

void SessionWrapperImpl::InitNotifyGetAvoidAreaByTypeFunc()
{
    CHECK_NULL_VOID(session_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifyGetAvoidAreaByTypeFunc: sessionCallbacks is nullptr");
        return;
    }

    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_ =
        [instanceId = instanceId_] (Rosen::AvoidAreaType type, int32_t apiVersion) -> Rosen::AvoidArea {
            Rosen::AvoidArea avoidArea;
            auto container = Platform::AceContainer::GetContainer(instanceId);
            CHECK_NULL_RETURN(container, avoidArea);
            avoidArea = container->GetAvoidAreaByType(type, apiVersion);
            return avoidArea;
        };
}

void SessionWrapperImpl::InitNotifyExtensionEventFunc()
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(taskExecutor_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitNotifyExtensionEventFunc: sessionCallbacks is nullptr");
        return;
    }

    int32_t callSessionId = GetSessionId();
    sessionCallbacks->notifyExtensionEventFunc_ = [weakTaskExecutor = WeakClaim(RawPtr(taskExecutor_)),
        weak = hostPattern_, callSessionId] (uint32_t eventId) {
            auto taskExecutor = weakTaskExecutor.Upgrade();
            if (taskExecutor == nullptr) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "InitNotifyExtensionEventFunc: taskExecutor is nullptr");
                    return;
            }

            taskExecutor->PostTask(
                [weak, callSessionId, eventId] () {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    if (callSessionId != pattern->GetSessionId()) {
                        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                            "notifyBindModalFunc_: The callSessionId(%{public}d)"
                                " is inconsistent with the curSession(%{public}d)",
                            callSessionId, pattern->GetSessionId());
                            return;
                    }

                    pattern->OnExtensionEvent(static_cast<UIExtCallbackEventId>(eventId));
                }, TaskExecutor::TaskType::UI, "ArkUIUIExtensionEventCallback");
        };
}

void SessionWrapperImpl::InitGetStatusBarHeightFunc()
{
    CHECK_NULL_VOID(session_);
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitGetStatusBarHeightFunc: sessionCallbacks is nullptr");
        return;
    }

    sessionCallbacks->getStatusBarHeightFunc_ = [instanceId = instanceId_]() -> uint32_t {
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_RETURN(container, 0);
        return container->GetStatusBarHeight();
    };
}

void SessionWrapperImpl::InitAllCallback()
{
    CHECK_NULL_VOID(session_);
    int32_t callSessionId = GetSessionId();
    if (!taskExecutor_) {
        LOGE("taskExecutor_ is nullptr, the sessionid = %{public}d", callSessionId);
        return;
    }

    InitForegroundCallback();
    InitBackgroundCallback();
    InitDestructionCallback();

    // Init SessionEventCallback
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    if (sessionCallbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "InitAllCallback: sessionCallbacks is nullptr");
        return;
    }

    InitTransferAbilityResultFunc();
    InitTransferExtensionDataFunc();
    InitNotifyRemoteReadyFunc();
    InitNotifySyncOnFunc();
    InitNotifyAsyncOnFunc();
    InitNotifyBindModalFunc();
    InitNotifyGetAvoidAreaByTypeFunc();
    InitNotifyExtensionEventFunc();
    InitGetStatusBarHeightFunc();
}

void SessionWrapperImpl::UpdateInstanceId(int32_t instanceId)
{
    if (instanceId_ == instanceId) {
        UIEXT_LOGW("InstanceId(%{public}d) has not changed when UpdateInstanceId.", instanceId);
        return;
    }

    UIEXT_LOGI("Update instanceId %{public}d to %{public}d.", instanceId_, instanceId);
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    instanceId_ = instanceId;
    taskExecutor_ = taskExecutor;
    InitAllCallback();
    UIEXT_LOGI("Update instanceId success.");
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
    ContainerScope scope(instanceId_);
    UIEXT_LOGI("The session is created with bundle=%{public}s, ability=%{public}s, componentId=%{public}d.",
        want.GetElement().GetBundleName().c_str(), want.GetElement().GetAbilityName().c_str(), GetFrameNodeId());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto realHostWindowId = pipeline->GetRealHostWindowId();
    customWant_ = std::make_shared<Want>(want);
    auto wantPtr = std::make_shared<Want>(want);
    UpdateWantPtr(wantPtr);
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
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    SessionViewportConfig sessionViewportConfig;
    sessionViewportConfig.isDensityFollowHost_ = pattern->GetDensityDpi();
    sessionViewportConfig.density_ = context->GetCurrentDensity();
    sessionViewportConfig.displayId_ = container->GetCurrentDisplayId();
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
    RegisterDataConsumer();
}

void SessionWrapperImpl::UpdateSessionConfig()
{
    auto extConfig = session_->GetSystemConfig();
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
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
    UIEXT_LOGI("DestroySession, persistentid=%{public}d, componentId=%{public}d.",
        session_->GetPersistentId(), GetFrameNodeId());
    session_->UnregisterLifecycleListener(lifecycleListener_);
    auto dataHandler = session_->GetExtensionDataHandler();
    if (dataHandler) {
        dataHandler->UnregisterDataConsumer(subSystemId_);
    }
    customWant_ = nullptr;
    session_ = nullptr;
}

void SessionWrapperImpl::UpdateWantPtr(std::shared_ptr<AAFwk::Want>& wantPtr)
{
    CHECK_NULL_VOID(wantPtr);
    AAFwk::WantParams configParam;
    auto container = Platform::AceContainer::GetContainer(GetInstanceId());
    CHECK_NULL_VOID(container);
    container->GetExtensionConfig(configParam);
    auto str = UIExtensionContainerHandler::FromUIContentTypeToStr(container->GetUIContentType());
    configParam.SetParam(UIEXTENSION_HOST_UICONTENT_TYPE, AAFwk::String::Box(str));
    AAFwk::WantParams wantParam(wantPtr->GetParams());
    wantParam.SetParam(UIEXTENSION_CONFIG_FIELD, AAFwk::WantParamWrapper::Box(configParam));
    wantPtr->SetParams(wantParam);
}

void SessionWrapperImpl::ReDispatchWantParams()
{
    CHECK_NULL_VOID(session_);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_VOID(dataHandler);
    AAFwk::WantParams configParam;
    auto container = Platform::AceContainer::GetContainer(GetInstanceId());
    CHECK_NULL_VOID(container);
    container->GetExtensionConfig(configParam);
    AAFwk::WantParams wantParam(customWant_->GetParams());
    wantParam.SetParam(UIEXTENSION_CONFIG_FIELD, AAFwk::WantParamWrapper::Box(configParam));
    AAFwk::Want dataToSend;
    dataToSend.SetParams(wantParam);
    dataHandler->SendDataAsync(Rosen::SubSystemId::WM_UIEXT,
        static_cast<uint32_t>(OHOS::Rosen::Extension::Businesscode::SYNC_WANT_PARAMS), dataToSend);
}

bool SessionWrapperImpl::IsSessionValid()
{
    return session_ != nullptr;
}

int32_t SessionWrapperImpl::GetSessionId() const
{
    return session_ ? session_->GetPersistentId() : 0;
}

int32_t SessionWrapperImpl::GetInstanceId() const
{
    return instanceId_;
}

const std::shared_ptr<AAFwk::Want> SessionWrapperImpl::GetWant()
{
    return session_ ? customWant_ : nullptr;
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
    UIEXT_LOGI("Back event notified to uiextension, persistentid=%{public}d and %{public}s consumed,"
        " componentId=%{public}d.", GetSessionId(), isConsumed ? "is" : "is not", GetFrameNodeId());
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
    UIEXT_LOGI("Key event notified to uiextension, persistentid = %{public}d and %{public}s consumed,"
        " componentId=%{public}d.", GetSessionId(), isConsumed ? "is" : "is not", GetFrameNodeId());
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
    UIEXT_LOGI("Notify uiextension, persistentid = %{public}d to %{public}s the focus state,"
        " componentId=%{public}d.", GetSessionId(), isFocus ? "paint" : "clear", GetFrameNodeId());
    session_->TransferFocusActiveEvent(isFocus);
    return true;
}

bool SessionWrapperImpl::NotifyFocusStateAsync(bool focusState)
{
    CHECK_NULL_RETURN(session_, false);
    UIEXT_LOGI("%{public}s state notified to uiextension, persistentid = %{public}d,"
        " componentId=%{public}d.", focusState ? "focused" : "unfocused", GetSessionId(), GetFrameNodeId());
    session_->TransferFocusStateEvent(focusState);
    return true;
}

bool SessionWrapperImpl::NotifyBackPressedAsync()
{
    return false;
}
bool SessionWrapperImpl::NotifyPointerEventAsync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    if (!pointerEvent) {
        UIEXT_LOGE("Transfer pointer event to uiextension fail with null pointerEvent,"
            " componentId=%{public}d.", GetFrameNodeId());
        return false;
    }

    if (!session_) {
        UIEXT_LOGE("Transfer pointer event to uiextension fail with null session, 'id = %{public}d',"
            " componentId=%{public}d.", pointerEvent->GetId(), GetFrameNodeId());
        return false;
    }

    session_->TransferPointerEvent(pointerEvent);
    return false;
}
bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    if (session_ && keyEvent) {
        UIEXT_LOGI("Transfer key event with 'id = %{public}d' to uiextension, persistentid = %{public}d,"
            " componentId=%{public}d.", keyEvent->GetId(), GetSessionId(), GetFrameNodeId());
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

RefPtr<SystemWindowScene> SessionWrapperImpl::GetWindowScene()
{
    RefPtr<SystemWindowScene> hostPattern = nullptr;
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, hostPattern);
    auto hostWindowNode = WindowSceneHelper::FindWindowScene(pattern->GetHost());
    CHECK_NULL_RETURN(hostWindowNode, hostPattern);
    auto hostNode = AceType::DynamicCast<FrameNode>(hostWindowNode);
    CHECK_NULL_RETURN(hostNode, hostPattern);
    hostPattern = hostNode->GetPattern<SystemWindowScene>();
    return hostPattern;
}

int32_t SessionWrapperImpl::GetWindowSceneId()
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, INVALID_WINDOW_ID);
    auto hostPattern = GetWindowScene();
    CHECK_NULL_RETURN(hostPattern, INVALID_WINDOW_ID);
    auto hostSession = hostPattern->GetSession();
    CHECK_NULL_RETURN(hostSession, INVALID_WINDOW_ID);
    int32_t windowSceneId = hostSession->GetPersistentId();
    if (windowSceneId != INVALID_WINDOW_ID) {
        pattern->RegisterWindowSceneVisibleChangeCallback(hostPattern);
    }
    return windowSceneId;
}

Rosen::WSRect SessionWrapperImpl::GetWindowSceneRect()
{
    Rosen::WSRect rect = {0, 0, 0, 0};
    auto hostPattern = GetWindowScene();
    CHECK_NULL_RETURN(hostPattern, rect);
    auto hostSession = hostPattern->GetSession();
    CHECK_NULL_RETURN(hostSession, rect);
    return hostSession->GetSessionRect();
}

RectF SessionWrapperImpl::GetDisplayAreaWithWindowScene()
{
    RectF displayArea = displayArea_;
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, displayArea);
    auto curWindow = pipeline->GetCurrentWindowRect();
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, displayArea);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, displayArea);
    auto [displayOffset, err] = host->GetPaintRectGlobalOffsetWithTranslate(false, true);
    displayArea.SetOffset(displayOffset);
    displayArea = displayArea + OffsetF(curWindow.Left(), curWindow.Top());
    return displayArea;
}

void SessionWrapperImpl::NotifyForeground()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(session_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    int32_t windowSceneId = GetWindowSceneId();
    UIEXT_LOGI("NotifyForeground, persistentid = %{public}d, hostWindowId = %{public}u,"
        " windowSceneId = %{public}d, IsSceneBoardWindow: %{public}d, componentId=%{public}d.",
        session_->GetPersistentId(), hostWindowId, windowSceneId, container->IsSceneBoardWindow(), GetFrameNodeId());
    if (container->IsSceneBoardWindow() && windowSceneId != INVALID_WINDOW_ID) {
        hostWindowId = static_cast<uint32_t>(windowSceneId);
    }
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->IsViewportConfigChanged()) {
        pattern->SetViewportConfigChanged(false);
        UpdateSessionViewportConfig();
    }
    auto wantPtr = session_->EditSessionInfo().want;
    UpdateWantPtr(wantPtr);
    if (foregroundCallback_ == nullptr) {
        InitForegroundCallback();
    }
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        session_, hostWindowId, std::move(foregroundCallback_));
}

void SessionWrapperImpl::NotifyBackground(bool isHandleError)
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("NotifyBackground, persistentid = %{public}d, isHandleError = %{public}d, componentId=%{public}d.",
        session_->GetPersistentId(), isHandleError, GetFrameNodeId());
    if (isHandleError) {
        if (backgroundCallback_ == nullptr) {
            InitBackgroundCallback();
        }

        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(
            session_, std::move(backgroundCallback_));
    } else {
        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(
            session_, nullptr);
    }
}

void SessionWrapperImpl::OnReleaseDone()
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("OnReleaseDone, persistentid = %{public}d, componentId=%{public}d.",
        session_->GetPersistentId(), GetFrameNodeId());
    session_->UnregisterLifecycleListener(lifecycleListener_);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestructionDone(session_);
    session_ = nullptr;
}

void SessionWrapperImpl::NotifyDestroy(bool isHandleError)
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGI("NotifyDestroy, isHandleError = %{public}d, persistentid = %{public}d, componentId=%{public}d.",
        isHandleError, session_->GetPersistentId(), GetFrameNodeId());
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

void SessionWrapperImpl::OnExtensionDetachToDisplay()
{
    UIEXT_LOGI("OnExtensionDetachToDisplay");
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, callSessionId]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "OnExtensionDetachToDisplay: The callSessionId(%{public}d)"
                    " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
                return;
            }

            pattern->OnExtensionDetachToDisplay();
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionOnExtensionDetachToDisplay");
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

void SessionWrapperImpl::NotifyDisplayArea(const RectF& displayArea)
{
    CHECK_NULL_VOID(session_);
    auto instanceId = GetInstanceId();
    ContainerScope scope(instanceId);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    displayAreaWindow_ = pipeline->GetCurrentWindowRect();
    displayArea_ = displayArea + OffsetF(displayAreaWindow_.Left(), displayAreaWindow_.Top());
    std::shared_ptr<Rosen::RSTransaction> transaction;
    auto parentSession = session_->GetParentSession();
    auto reason = parentSession ? parentSession->GetSizeChangeReason() : session_->GetSizeChangeReason();
    reason_ = (uint32_t)reason;
    auto persistentId = parentSession ? parentSession->GetPersistentId() : session_->GetPersistentId();
    int32_t duration = 0;
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector;
    auto window = pipeline->GetWindow();
    if (window) {
        rsUIDirector = window->GetRSUIDirector();
    }
    if (!rsUIDirector) {
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
    } else {
        auto rsUIContext = rsUIDirector->GetRSUIContext();
        if (reason == Rosen::SizeChangeReason::ROTATION) {
            if (transaction_.lock()) {
                transaction = transaction_.lock();
                transaction_.reset();
            } else if (pipeline && rsUIContext) {
                auto transactionController = rsUIContext->GetSyncTransactionHandler();
                if (transactionController) {
                    transaction = transactionController->GetRSTransaction();
                }
            } else {
                auto transactionController = Rosen::RSSyncTransactionController::GetInstance();
                if (transactionController) {
                    transaction = transactionController->GetRSTransaction();
                }
            }
            if (transaction && parentSession) {
                duration = pipeline->GetSyncAnimationOption().GetDuration();
                transaction->SetDuration(duration);
            }
        }
    }
    ACE_SCOPED_TRACE("NotifyDisplayArea displayArea[%s], curWindow[%s], reason[%d], duration[%d], componentId[%d]",
        displayArea_.ToString().c_str(), displayAreaWindow_.ToString().c_str(), reason, duration, GetFrameNodeId());
    UIEXT_LOGD("NotifyDisplayArea displayArea=%{public}s, curWindow=%{public}s, "
        "reason=%{public}d, duration=%{public}d, persistentId=%{public}d, componentId=%{public}d.",
        displayArea_.ToString().c_str(), displayAreaWindow_.ToString().c_str(),
        reason, duration, persistentId, GetFrameNodeId());
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
    UIEXT_LOGD("NotifyAvoidArea, type: %{public}d, topRect=(%{public}d, %{public}d)-[%{public}d, %{public}d], "
        "bottomRect=(%{public}d,%{public}d)-[%{public}d,%{public}d],persistentId=%{public}d,componentId=%{public}d.",
        type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
        (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
        (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_, GetSessionId(),
        GetFrameNodeId());
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
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto curWindow = pipeline->GetCurrentWindowRect();
    int64_t curTime = GetCurrentTimestamp();
    if (displayAreaWindow_ != curWindow && needWaitLayout) {
        UIEXT_LOGI("OccupiedArea wait layout, displayAreaWindow: %{public}s,"
            " curWindow=%{public}s, componentId=%{public}d.",
            displayAreaWindow_.ToString().c_str(), curWindow.ToString().c_str(), GetFrameNodeId());
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
        TaskExecutor::TaskType::UI, "ArkUIUecAreaChange",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
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
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto curWindow = pipeline->GetCurrentWindowRect();
    auto container = Platform::AceContainer::GetContainer(GetInstanceId());
    CHECK_NULL_RETURN(container, false);
    auto displayArea = displayArea_;
    if (container->IsSceneBoardWindow()) {
        Rosen::WSRect rect = GetWindowSceneRect();
        curWindow.SetRect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        displayArea = GetDisplayAreaWithWindowScene();
    }
    if (keyboardHeight > 0) {
        if (curWindow.Bottom() >= displayArea.Bottom()) {
            int32_t spaceWindow = std::max(curWindow.Bottom() - displayArea.Bottom(), 0.0);
            keyboardHeight = static_cast<int32_t>(std::max(keyboardHeight - spaceWindow, 0));
        } else {
            keyboardHeight = keyboardHeight + (displayArea.Bottom() - curWindow.Bottom());
        }
    }
    sptr<Rosen::OccupiedAreaChangeInfo> newInfo = new Rosen::OccupiedAreaChangeInfo(
        info->type_, info->rect_, info->safeHeight_, info->textFieldPositionY_, info->textFieldHeight_);
    newInfo->rect_.height_ = static_cast<uint32_t>(keyboardHeight);
    UIEXT_LOGI("OccupiedArea keyboardHeight = %{public}d, displayOffset = %{public}s, displayArea = %{public}s, "
               "curWindow = %{public}s, persistentid = %{public}d, componentId=%{public}d.",
        keyboardHeight, displayArea.GetOffset().ToString().c_str(), displayArea_.ToString().c_str(),
        curWindow.ToString().c_str(), GetSessionId(), GetFrameNodeId());
    session_->NotifyOccupiedAreaChangeInfo(newInfo);
    return true;
}

void SessionWrapperImpl::UpdateSessionViewportConfig()
{
    CHECK_NULL_VOID(session_);
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto config = pattern->GetSessionViewportConfig();
    UIEXT_LOGI("SessionViewportConfig: isDensityFollowHost=%{public}d, density=%{public}f, "
        "displayId=%{public}" PRIu64", orientation=%{public}d, transform=%{public}d, componentId=%{public}d.",
        config.isDensityFollowHost_, config.density_, config.displayId_, config.orientation_, config.transform_,
        GetFrameNodeId());
    session_->UpdateSessionViewportConfig(ConvertToRosenSessionViewportConfig(config));
}

/***************************** End: The interface to control the display area and the avoid area **********************/

/************************************************ Begin: The interface to send the data for ArkTS *********************/
void SessionWrapperImpl::SendDataAsync(const AAFwk::WantParams& params) const
{
    if (!session_) {
        UIEXT_LOGE(
            "The data is synchronously send and the session is invalid, componentId=%{public}d.", GetFrameNodeId());
        return;
    }
    session_->TransferComponentData(params);
}

int32_t SessionWrapperImpl::SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const
{
    Rosen::WSErrorCode transferCode = Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED;
    UIEXT_LOGI("The data is synchronously send and the session is %{public}s, componentId=%{public}d.",
        session_ ? "valid" : "invalid", GetFrameNodeId());
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

int32_t SessionWrapperImpl::GetFrameNodeId() const
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, -1);
    auto frameNode =  pattern->GetHost();
    CHECK_NULL_RETURN(frameNode, -1);
    return frameNode->GetId();
}

bool SessionWrapperImpl::SendBusinessDataSyncReply(
    UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply, RSSubsystemId subSystemId)
{
    if (code == UIContentBusinessCode::UNDEFINED) {
        return false;
    }
    CHECK_NULL_RETURN(session_, false);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    auto result = dataHandler->SendDataSync(static_cast<OHOS::Rosen::SubSystemId>(subSystemId),
        static_cast<uint32_t>(code), data, reply);
    if (result != Rosen::DataHandlerErr::OK) {
        UIEXT_LOGW("SendBusinessDataSyncReply Fail, businesCode=%{public}u, result=%{public}u, compontId=%{public}d.",
            code, result, GetFrameNodeId());
        return false;
    }
    UIEXT_LOGI("SendBusinessDataSyncReply Success, businessCode=%{public}u, compontId=%{public}d.",
        code, GetFrameNodeId());
    return true;
}

bool SessionWrapperImpl::SendBusinessData(
    UIContentBusinessCode code, const AAFwk::Want& data, BusinessDataSendType type, RSSubsystemId subSystemId)
{
    if (code == UIContentBusinessCode::UNDEFINED) {
        return false;
    }
    CHECK_NULL_RETURN(session_, false);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    if (type == BusinessDataSendType::ASYNC) {
        dataHandler->SendDataAsync(static_cast<OHOS::Rosen::SubSystemId>(subSystemId),
            static_cast<uint32_t>(code), data);
        UIEXT_LOGD("SendBusinessData ASYNC Success, businessCode=%{public}u, compontId=%{public}d.",
            code, GetFrameNodeId());
        return true;
    }
    auto result = dataHandler->SendDataSync(static_cast<OHOS::Rosen::SubSystemId>(subSystemId),
        static_cast<uint32_t>(code), data);
    if (result != Rosen::DataHandlerErr::OK) {
        UIEXT_LOGD("SendBusinessData Sync Fail, businesCode=%{public}u, result=%{public}u, compontId=%{public}d.",
            code, result, GetFrameNodeId());
        return false;
    }
    UIEXT_LOGD("SendBusinessData SYNC Success, businessCode=%{public}u, componentId=%{public}d.",
        code, GetFrameNodeId());
    return true;
}

void SessionWrapperImpl::DispatchExtensionDataToHostWindow(uint32_t customId, const AAFwk::Want& data)
{
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostTask(
        [instanceId, weak = hostPattern_, customId, data, callSessionId]() {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "DispatchExtensionDataToHostWindow: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
                return;
            }
            auto container = Platform::AceContainer::GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            container->DispatchExtensionDataToHostWindow(customId, data, callSessionId);
        },
        TaskExecutor::TaskType::UI, "ArkUIDispatchExtensionDataToHostWindow");
}

void SessionWrapperImpl::PostBusinessDataConsumeAsync(uint32_t customId, const AAFwk::Want& data)
{
    UIEXT_LOGI("PostBusinessDataConsumeAsync, businessCode=%{public}u.", customId);
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostTask(
        [instanceId, weak = hostPattern_, customId, data, callSessionId]() {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "BusinessDataConsumeAsync: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
                return;
            }
            pattern->OnUIExtBusinessReceive(static_cast<UIContentBusinessCode>(customId), data);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionBusinessDataConsumeAsync");
}
void SessionWrapperImpl::PostBusinessDataConsumeSyncReply(
    uint32_t customId, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply)
{
    UIEXT_LOGI("PostBusinessDataConsumeSyncReply, businessCode=%{public}u.", customId);
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostSyncTask(
        [instanceId, weak = hostPattern_, customId, data, &reply, callSessionId]() {
            ContainerScope scope(instanceId);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (callSessionId != pattern->GetSessionId()) {
                TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "BusinessDataConsumeSyncReply: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, pattern->GetSessionId());
                return;
            }
            pattern->OnUIExtBusinessReceiveReply(
                static_cast<UIContentBusinessCode>(customId), data, reply);
        },
        TaskExecutor::TaskType::UI, "ArkUIUIExtensionBusinessDataConsumeSyncReply");
}

bool SessionWrapperImpl::RegisterDataConsumer()
{
    CHECK_NULL_RETURN(session_, false);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    auto subSystemId = subSystemId_;
    auto callback = [wrapperWeak = WeakClaim(this), subSystemId]
        (Rosen::SubSystemId id, uint32_t customId, AAFwk::Want&& data, std::optional<AAFwk::Want>& reply) ->int32_t {
        auto sessionWrapper = wrapperWeak.Upgrade();
        CHECK_NULL_RETURN(sessionWrapper, false);
        auto instanceId = sessionWrapper->GetInstanceId();
        ContainerScope scope(instanceId);
        if (id != subSystemId) {
            return false;
        }
        if (IsDispatchExtensionDataToHostWindow(customId)) {
            sessionWrapper->DispatchExtensionDataToHostWindow(customId, data);
            return true;
        }
        if (reply.has_value()) {
            sessionWrapper->PostBusinessDataConsumeSyncReply(customId, data, reply);
        } else {
            sessionWrapper->PostBusinessDataConsumeAsync(customId, data);
        }
        return false;
    };
    auto result = dataHandler->RegisterDataConsumer(subSystemId, std::move(callback));
    if (result != Rosen::DataHandlerErr::OK) {
        UIEXT_LOGW("RegisterDataConsumer Fail, result=%{public}u", result);
        return false;
    }
    return true;
}
/************************************************ End: The interface for UEC dump **********************************/

void SessionWrapperImpl::NotifyHostWindowMode(int32_t mode)
{
    UIEXT_LOGI("SendWindowModeToProvider: mode = %{public}d", mode);
    CHECK_NULL_VOID(session_);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_VOID(dataHandler);
    AAFwk::Want dataToSend;
    dataToSend.SetParam(OHOS::Rosen::Extension::WINDOW_MODE_FIELD, mode);
    dataHandler->SendDataAsync(Rosen::SubSystemId::WM_UIEXT,
        static_cast<uint32_t>(OHOS::Rosen::Extension::Businesscode::SYNC_HOST_WINDOW_MODE), dataToSend);
}
} // namespace OHOS::Ace::NG
