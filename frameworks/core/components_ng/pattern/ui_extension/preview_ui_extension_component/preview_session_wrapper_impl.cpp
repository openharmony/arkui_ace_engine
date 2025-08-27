/*
* Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
 
#include <cmath>
#include <memory>
 
#include "accessibility_event_info.h"
#include "extension/extension_business_info.h"
#include "refbase.h"
#include "session_manager/include/extension_session_manager.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"
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
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/pipeline_ng/pipeline_context.h"
 
namespace OHOS::Ace::NG {
namespace {
constexpr char START_FAIL_NAME[] = "start_ability_fail";
constexpr char START_FAIL_MESSAGE[] = "Start ui extension ability failed, please check the want of UIextensionAbility.";
constexpr char BACKGROUND_FAIL_NAME[] = "background_fail";
constexpr char BACKGROUND_FAIL_MESSAGE[] = "background ui extension ability failed, please check AMS log.";
constexpr char TERMINATE_FAIL_NAME[] = "terminate_fail";
constexpr char TERMINATE_FAIL_MESSAGE[] = "terminate ui extension ability failed, please check AMS log.";
constexpr char EXIT_ABNORMALLY_NAME[] = "extension_exit_abnormally";
constexpr char EXIT_ABNORMALLY_MESSAGE[] = "the extension ability exited abnormally, please check AMS log.";
constexpr char EXTENSION_TRANSPARENT_NAME[] = "extension_node_transparent";
constexpr char EXTENSION_TRANSPARENT_MESSAGE[] = "the extension ability has transparent node.";
constexpr char LIFECYCLE_TIMEOUT_NAME[] = "extension_lifecycle_timeout";
constexpr char LIFECYCLE_TIMEOUT_MESSAGE[] = "the lifecycle of extension ability is timeout, please check AMS log.";
constexpr char OCCUPIED_AREA_CHANGE_KEY[] = "ability.want.params.IsNotifyOccupiedAreaChange";
constexpr const char* const UIEXTENSION_CONFIG_FIELD = "ohos.system.window.uiextension.params";
} // namespace
 
static bool IsDispatchExtensionDataToHostWindow(uint32_t customId)
{
    auto businessCode = static_cast<UIContentBusinessCode>(customId);
    return (businessCode >= UIContentBusinessCode::WINDOW_CODE_BEGIN &&
        businessCode <= UIContentBusinessCode::WINDOW_CODE_END);
}
 
class PreviewUIExtensionLifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit PreviewUIExtensionLifecycleListener(const WeakPtr<SessionWrapper>& sessionWrapper)
        : sessionWrapper_(sessionWrapper) {}
    virtual ~PreviewUIExtensionLifecycleListener() = default;
 
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
 
    void OnAccessibilityEvent(
        const Accessibility::AccessibilityEventInfo& info, int64_t uiExtensionOffset) override
    {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        CHECK_NULL_VOID(sessionWrapper);
        sessionWrapper->OnAccessibilityEvent(info, uiExtensionOffset);
    }
 
private:
    WeakPtr<SessionWrapper> sessionWrapper_;
};
 
/********************* Begin: Initialization *************************/
PreviewSessionWrapperImpl::PreviewSessionWrapperImpl(
    const WeakPtr<PreviewUIExtensionPattern>& hostPattern,
    int32_t instanceId, bool isTransferringCaller, SessionType sessionType)
    : hostPattern_(hostPattern), instanceId_(instanceId), isTransferringCaller_(isTransferringCaller),
    sessionType_(sessionType)
{
    auto pattern = hostPattern.Upgrade();
    platformId_ = pattern ? pattern->GetUiExtensionId() : 0;
    taskExecutor_ = Container::CurrentTaskExecutor();
}
 
PreviewSessionWrapperImpl::~PreviewSessionWrapperImpl() {}
 
void PreviewSessionWrapperImpl::InitAllCallback()
{
    CHECK_NULL_VOID(session_);
    int32_t callSessionId = GetSessionId();
    if (!taskExecutor_) {
        PLATFORM_LOGE("[AcePreviewUIExtension] taskExecutor_ is nullptr, the sessionid = %{public}d", callSessionId);
        return;
    }
    auto sessionCallbacks = session_->GetExtensionSessionEventCallback();
    foregroundCallback_ =
        [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId](OHOS::Rosen::WSError errcode) {
            if (errcode != OHOS::Rosen::WSError::WS_OK) {
                taskExecutor->PostTask(
                    [weak, callSessionId] {
                        auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                        CHECK_NULL_VOID(pattern);
                        if (callSessionId != pattern->GetSessionId()) {
                            LOGW("[AcePreviewUIExtension]foregroundCallback:"
                                "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                callSessionId, pattern->GetSessionId());
                            return;
                        }
                        pattern->FireOnErrorCallback(
                            ERROR_CODE_UIEXTENSION_FOREGROUND_FAILED, START_FAIL_NAME, START_FAIL_MESSAGE);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionForegroundError");
            }
        };
        backgroundCallback_ = [weak = hostPattern_,
            taskExecutor = taskExecutor_, callSessionId](OHOS::Rosen::WSError errcode) {
                if (errcode != OHOS::Rosen::WSError::WS_OK) {
                    taskExecutor->PostTask(
                        [weak, callSessionId] {
                            auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                            CHECK_NULL_VOID(pattern);
                            if (callSessionId != pattern->GetSessionId()) {
                                LOGW("[AcePreviewUIExtension]backgroundCallback:"
                                    "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                    callSessionId, pattern->GetSessionId());
                                return;
                            }
                            pattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_BACKGROUND_FAILED,
                                BACKGROUND_FAIL_NAME, BACKGROUND_FAIL_MESSAGE);
                        },
                        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionBackgroundError");
                }
            };
        destructionCallback_ = [weak = hostPattern_,
            taskExecutor = taskExecutor_, callSessionId](OHOS::Rosen::WSError errcode) {
                if (errcode != OHOS::Rosen::WSError::WS_OK) {
                    taskExecutor->PostTask(
                        [weak, callSessionId] {
                            auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                            CHECK_NULL_VOID(pattern);
                            if (callSessionId != pattern->GetSessionId()) {
                                LOGW("[AcePreviewUIExtension]destructCallback:"
                                    "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                    callSessionId, pattern->GetSessionId());
                                return;
                            }
                            pattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_DESTRUCTION_FAILED,
                                TERMINATE_FAIL_NAME, TERMINATE_FAIL_MESSAGE);
                        },
                        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionDestructionError");
                }
            };
        sessionCallbacks->transferAbilityResultFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_,
            callSessionId](int32_t code, const AAFwk::Want& want) {
                taskExecutor->PostTask(
                    [weak, code, want, callSessionId]() {
                        auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                        CHECK_NULL_VOID(pattern);
                        if (callSessionId != pattern->GetSessionId()) {
                            LOGW("[AcePreviewUIExtension]transferAbilityResult:"
                                "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                callSessionId, pattern->GetSessionId());
                            return;
                        }
                        pattern->FireOnTerminatedCallback(code, MakeRefPtr<WantWrapOhos>(want));
                    },
                    TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionTransferAbilityResult");
            };
        sessionCallbacks->transferExtensionDataFunc_ = [weak = hostPattern_,
            taskExecutor = taskExecutor_, callSessionId](const AAFwk::WantParams& params) {
                taskExecutor->PostTask(
                    [weak, params, callSessionId]() {
                        auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                        CHECK_NULL_VOID(pattern);
                        if (callSessionId != pattern->GetSessionId()) {
                            LOGW("[AcePreviewUIExtension]transferExtensionData:"
                                "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                callSessionId, pattern->GetSessionId());
                            return;
                        }
                        pattern->FireOnReceiveCallback(params);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionReceiveCallback");
            };
        sessionCallbacks->notifyRemoteReadyFunc_ = [weak = hostPattern_,
            taskExecutor = taskExecutor_, callSessionId]() {
                taskExecutor->PostTask(
                    [weak, callSessionId]() {
                        auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                        CHECK_NULL_VOID(pattern);
                        if (callSessionId != pattern->GetSessionId()) {
                            LOGW("[AcePreviewUIExtension]notifyRemoteReadyFunc:"
                                "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                                callSessionId, pattern->GetSessionId());
                            return;
                        }
                        pattern->FireOnRemoteReadyCallback();
                    },
                    TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionRemoteReadyCallback");
        };
    sessionCallbacks->notifySyncOnFunc_ = [weak = hostPattern_,
        taskExecutor = taskExecutor_, callSessionId]() {
            taskExecutor->PostTask(
                [weak, callSessionId]() {
                    auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                    CHECK_NULL_VOID(pattern);
                    if (callSessionId != pattern->GetSessionId()) {
                        LOGW("[AcePreviewUIExtension]notifySyncOnFunc:"
                            "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                            callSessionId, pattern->GetSessionId());
                        return;
                    }
                    pattern->FireSyncCallbacks();
                },
                TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionSyncCallbacks");
        };
    sessionCallbacks->notifyAsyncOnFunc_ = [weak = hostPattern_,
        taskExecutor = taskExecutor_, callSessionId]() {
            taskExecutor->PostTask(
                [weak, callSessionId]() {
                    auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                    CHECK_NULL_VOID(pattern);
                    if (callSessionId != pattern->GetSessionId()) {
                        LOGW("[AcePreviewUIExtension]notifyAsyncOnFunc:"
                            "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                            callSessionId, pattern->GetSessionId());
                        return;
                    }
                    pattern->FireAsyncCallbacks();
                },
                TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionAsyncCallbacks");
        };
    sessionCallbacks->notifyBindModalFunc_ = [weak = hostPattern_,
        taskExecutor = taskExecutor_, callSessionId]() {
            taskExecutor->PostSyncTask(
                [weak, callSessionId]() {
                    auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                    CHECK_NULL_VOID(pattern);
                    if (callSessionId != pattern->GetSessionId()) {
                        LOGW("[AcePreviewUIExtension]notifyBindModalFunc:"
                            "The callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                            callSessionId, pattern->GetSessionId());
                        return;
                    }
                    pattern->FireBindModalCallback();
                },
                TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionBindModalCallback");
        };
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_ =
        [instanceId = instanceId_](Rosen::AvoidAreaType type, int32_t apiVersion) -> Rosen::AvoidArea {
            Rosen::AvoidArea avoidArea;
            auto container = Platform::AceContainer::GetContainer(instanceId);
            CHECK_NULL_RETURN(container, avoidArea);
            avoidArea = container->GetAvoidAreaByType(type, apiVersion);
            return avoidArea;
        };
    sessionCallbacks->notifyExtensionEventFunc_ =
        [weak = hostPattern_, taskExecutor = taskExecutor_, callSessionId](uint32_t eventId) {
        taskExecutor->PostTask(
            [weak, callSessionId, eventId]() {
                auto pattern = AceType::DynamicCast<PreviewUIExtensionPattern>(weak.Upgrade());
                CHECK_NULL_VOID(pattern);
                if (callSessionId != pattern->GetSessionId()) {
                    LOGW("[AcePreviewUIExtension]notifyExtensionEventFunc: The callSessionId(%{public}d)"
                            " is inconsistent with the curSession(%{public}d)",
                        callSessionId, pattern->GetSessionId());
                        return;
                }
                pattern->OnExtensionEvent(static_cast<UIExtCallbackEventId>(eventId));
            },
            TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionEventCallback");
    };
}
/*********************** End: Initialization *************************************/
 
/*********************** Begin: About session ************************************/
void PreviewSessionWrapperImpl::CreateSession(const AAFwk::Want& want, const SessionConfig& config)
{
    PLATFORM_LOGI("PreviewUIExtension The session is created with bundle = %{public}s, ability = %{public}s",
        want.GetElement().GetBundleName().c_str(), want.GetElement().GetAbilityName().c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    customWant_ = std::make_shared<Want>(want);
    auto wantPtr = std::make_shared<Want>(want);
    UpdateWantPtr(wantPtr);
    isNotifyOccupiedAreaChange_ = want.GetBoolParam(OCCUPIED_AREA_CHANGE_KEY, true);
    uint32_t parentWindowType = 0;
    if (container->IsUIExtensionWindow()) {
        parentWindowType = container->GetParentWindowType();
    } else {
        parentWindowType = container->GetWindowType();
    }
    PLATFORM_LOGI("PreviewUIExtension isNotifyOccupiedAreaChange is %{public}d, parentWindowType: %{public}u",
        isNotifyOccupiedAreaChange_, parentWindowType);
    auto callerToken = container->GetToken();
    auto parentToken = container->GetParentToken();
    Rosen::SessionInfo extensionSessionInfo;
    extensionSessionInfo.bundleName_ = want.GetElement().GetBundleName();
    extensionSessionInfo.abilityName_ = want.GetElement().GetAbilityName();
    extensionSessionInfo.callerToken_ = callerToken;
    extensionSessionInfo.rootToken_ = (isTransferringCaller_ && parentToken) ? parentToken : callerToken;
    extensionSessionInfo.want = wantPtr;
    extensionSessionInfo.parentWindowType_ = parentWindowType;
    extensionSessionInfo.uiExtensionUsage_ = static_cast<uint32_t>(config.uiExtensionUsage);
    extensionSessionInfo.isAsyncModalBinding_ = config.isAsyncModalBinding;
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<PreviewUIExtensionLifecycleListener>(
        AceType::WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
    InitAllCallback();
    RegisterDataConsumer();
}
 
void PreviewSessionWrapperImpl::DestroySession()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
    auto dataHandler = session_->GetExtensionDataHandler();
    if (dataHandler) {
        dataHandler->UnregisterDataConsumer(subSystemId_);
    }
    customWant_ = nullptr;
    session_ = nullptr;
}
 
void PreviewSessionWrapperImpl::UpdateWantPtr(std::shared_ptr<AAFwk::Want>& wantPtr)
{
    CHECK_NULL_VOID(wantPtr);
    AAFwk::WantParams configParam;
    auto container = Platform::AceContainer::GetContainer(GetInstanceId());
    CHECK_NULL_VOID(container);
    container->GetExtensionConfig(configParam);
    AAFwk::WantParams wantParam(wantPtr->GetParams());
    wantParam.SetParam(UIEXTENSION_CONFIG_FIELD, AAFwk::WantParamWrapper::Box(configParam));
    wantPtr->SetParams(wantParam);
}
 
void PreviewSessionWrapperImpl::ReDispatchWantParams()
{
    CHECK_NULL_VOID(session_);
    AAFwk::WantParams configParam;
    auto container = Platform::AceContainer::GetContainer(GetInstanceId());
    CHECK_NULL_VOID(container);
    container->GetExtensionConfig(configParam);
    AAFwk::WantParams wantParam(customWant_->GetParams());
    wantParam.SetParam(UIEXTENSION_CONFIG_FIELD, AAFwk::WantParamWrapper::Box(configParam));
    AAFwk::Want dataToSend;
    dataToSend.SetParams(wantParam);
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_VOID(dataHandler);
    dataHandler->SendDataAsync(Rosen::SubSystemId::WM_UIEXT,
        static_cast<uint32_t>(OHOS::Rosen::Extension::Businesscode::SYNC_WANT_PARAMS), dataToSend);
}
 
bool PreviewSessionWrapperImpl::IsSessionValid()
{
    return session_ != nullptr;
}
 
int32_t PreviewSessionWrapperImpl::GetSessionId() const
{
    if (session_) {
        PLATFORM_LOGI("PreviewSessionWrapperImpl::GetSessionId");
        return session_->GetPersistentId();
    }
    PLATFORM_LOGI("PreviewSessionWrapperImpl::GetSessionId session_ is NULL return 0.");
    return 0;
}
 
const std::shared_ptr<AAFwk::Want> PreviewSessionWrapperImpl::GetWant()
{
    return session_ ? customWant_ : nullptr;
}
/******************************* End: About session ***************************************/
 
/******************************* Begin: Synchronous interface for event notify ************/
bool PreviewSessionWrapperImpl::NotifyFocusEventSync(bool isFocus)
{
    return false;
}
bool PreviewSessionWrapperImpl::NotifyFocusStateSync(bool focusState)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyBackPressedSync()
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyPointerEventSync(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return false;
}

bool PreviewSessionWrapperImpl::NotifyKeyEventSync(
    const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyKeyEventAsync(
    const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyAxisEventSync(
    const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}
/*************************** End: Synchronous interface for event notify *************************/
 
/*************************** Begin: Asynchronous interface for event notify **********************/
bool PreviewSessionWrapperImpl::NotifyFocusEventAsync(bool isFocus)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyFocusStateAsync(bool focusState)
{
    return false;
}

bool PreviewSessionWrapperImpl::NotifyBackPressedAsync()
{
    return false;
}
bool PreviewSessionWrapperImpl::NotifyPointerEventAsync(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyKeyEventAsync(
    const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    return false;
}
 
bool PreviewSessionWrapperImpl::NotifyAxisEventAsync(
    const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}
 
void PreviewSessionWrapperImpl::NotifyCreate() {}
 
void PreviewSessionWrapperImpl::NotifyForeground()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(session_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    PLATFORM_LOGI("PreviewSessionWrapperImpl NotifyForeground hostWindowId is %{public}u.", hostWindowId);
    auto wantPtr = session_->EditSessionInfo().want;
    UpdateWantPtr(wantPtr);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        session_, hostWindowId, std::move(foregroundCallback_));
}
 
void PreviewSessionWrapperImpl::NotifyBackground(bool isHandleError)
{
    CHECK_NULL_VOID(session_);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(
        session_, std::move(backgroundCallback_));
}

void PreviewSessionWrapperImpl::NotifyDestroy(bool isHandleError)
{
    CHECK_NULL_VOID(session_);
    PLATFORM_LOGI("PreviewSessionWrapperImpl NotifyDestroy, isHandleError = %{public}d, persistentid = %{public}d.",
        isHandleError, session_->GetPersistentId());
    if (isHandleError) {
        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(
            session_, std::move(destructionCallback_));
    } else {
        Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(
            session_, nullptr);
    }
}

void PreviewSessionWrapperImpl::NotifyConfigurationUpdate() {}
 
void PreviewSessionWrapperImpl::OnConnect()
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, wrapperWeak = WeakClaim(this), callSessionId]() {
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("[AcePreviewUIExtension]Connect: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            preViewPattern->OnConnect();
            auto wrapper = wrapperWeak.Upgrade();
            CHECK_NULL_VOID(wrapper && wrapper->session_);
            ContainerScope scope(wrapper->instanceId_);
            if (auto hostWindowNode = WindowSceneHelper::FindWindowScene(preViewPattern->GetHost())) {
                auto hostNode = AceType::DynamicCast<FrameNode>(hostWindowNode);
                CHECK_NULL_VOID(hostNode);
                auto hostPattern = hostNode->GetPattern<SystemWindowScene>();
                CHECK_NULL_VOID(hostPattern);
                wrapper->session_->SetParentSession(hostPattern->GetSession());
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionSessionConnect");
}
 
void PreviewSessionWrapperImpl::OnDisconnect(bool isAbnormal)
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, isAbnormal, callSessionId]() {
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("[AcePreviewUIExtension]OnDisconnect: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            preViewPattern->OnDisconnect(isAbnormal);
            if (isAbnormal) {
                LOGW("[AcePreviewUIExtension]OnDisconnect Abnormal.");
                preViewPattern->FireOnErrorCallback(ERROR_CODE_UIEXTENSION_EXITED_ABNORMALLY,
                    EXIT_ABNORMALLY_NAME, EXIT_ABNORMALLY_MESSAGE);
            } else {
                preViewPattern->FireOnTerminatedCallback(0, nullptr);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionSessionDisconnect");
}
 
void PreviewSessionWrapperImpl::OnExtensionDetachToDisplay()
{
    PLATFORM_LOGI("OnExtensionDetachToDisplay");
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, callSessionId]() {
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("[AcePreviewUIExtension]OnExtensionDetachToDisplay:: The "
                    "callSessionId(%{public}d) is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
 
            preViewPattern->OnExtensionDetachToDisplay();
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionOnExtensionDetachToDisplay");
}
 
void PreviewSessionWrapperImpl::OnExtensionTimeout(int32_t errorCode)
{
    int32_t callSessionId = GetSessionId();
    taskExecutor_->PostTask(
        [weak = hostPattern_, callSessionId, errorCode]() {
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("[AcePreviewUIExtension]OnExtensionTimeout: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            bool isTransparent = errorCode == ERROR_CODE_UIEXTENSION_TRANSPARENT;
            preViewPattern->FireOnErrorCallback(
                isTransparent ? errorCode : ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT,
                isTransparent ? EXTENSION_TRANSPARENT_NAME : LIFECYCLE_TIMEOUT_NAME,
                isTransparent ? EXTENSION_TRANSPARENT_MESSAGE : LIFECYCLE_TIMEOUT_MESSAGE);
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionTimeout");
}
 
void PreviewSessionWrapperImpl::OnAccessibilityEvent(
    const Accessibility::AccessibilityEventInfo& info, int64_t offset)
{}
 
void PreviewSessionWrapperImpl::TransferAccessibilityHoverEvent(float pointX,
    float pointY, int32_t sourceType, int32_t eventType, int64_t timeMs)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
}
 
void PreviewSessionWrapperImpl::TransferAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}
 
void PreviewSessionWrapperImpl::TransferAccessibilityChildTreeDeregister()
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityChildTreeUnregister();
}
 
void PreviewSessionWrapperImpl::TransferAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityDumpChildInfo(params, info);
}
/************************ End: The interface about the accessibility **************************/
 
/********** Begin: The interface to control the display area and the avoid area ***************/
std::shared_ptr<Rosen::RSSurfaceNode> PreviewSessionWrapperImpl::GetSurfaceNode() const
{
    return session_ ? session_->GetSurfaceNode() : nullptr;
}
 
void PreviewSessionWrapperImpl::NotifyDisplayArea(const RectF& displayArea)
{
    CHECK_NULL_VOID(session_);
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto curWindow = pipeline->GetCurrentWindowRect();
    displayArea_ = displayArea + OffsetF(curWindow.Left(), curWindow.Top());
    std::shared_ptr<Rosen::RSTransaction> transaction;
    auto parentSession = session_->GetParentSession();
    auto reason = parentSession ? parentSession->GetSizeChangeReason() : session_->GetSizeChangeReason();
    reason_ = (uint32_t)reason;
    auto persistentId = parentSession ? parentSession->GetPersistentId() : session_->GetPersistentId();
    ACE_SCOPED_TRACE("NotifyDisplayArea id: %d, reason [%d]", persistentId, reason);
    PLATFORM_LOGI("PreviewUIExtension DisplayArea: %{public}s, persistentId: %{public}d, reason: %{public}d",
        displayArea_.ToString().c_str(), persistentId, reason);
        if (reason == Rosen::SizeChangeReason::ROTATION || reason == Rosen::SizeChangeReason::SNAPSHOT_ROTATION) {
            if (auto temp = transaction_.lock()) {
                transaction = temp;
                transaction_.reset();
            } else if (auto transactionController = Rosen::RSSyncTransactionController::GetInstance()) {
                transaction = transactionController->GetRSTransaction();
            }
            if (transaction && parentSession) {
                transaction->SetDuration(pipeline->GetSyncAnimationOption().GetDuration());
            }
        }
        session_->UpdateRect({ std::round(displayArea_.Left()), std::round(displayArea_.Top()),
            std::round(displayArea_.Width()), std::round(displayArea_.Height()) },
            reason, "NotifyDisplayArea", transaction);
}
    
void PreviewSessionWrapperImpl::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(session_);
    auto reason = static_cast<Rosen::SizeChangeReason>(type);
    session_->UpdateSizeChangeReason(reason);
    if (rsTransaction && (type == WindowSizeChangeReason::ROTATION ||
        type == WindowSizeChangeReason::SNAPSHOT_ROTATION)) {
        transaction_ = rsTransaction;
    }
}
    
void PreviewSessionWrapperImpl::NotifyOriginAvoidArea(
    const Rosen::AvoidArea& avoidArea, uint32_t type) const
{
    CHECK_NULL_VOID(session_);
    PLATFORM_LOGI("PreviewUIExtension The avoid area is notified to the provider.");
    session_->UpdateAvoidArea(
        sptr<Rosen::AvoidArea>::MakeSptr(avoidArea), static_cast<Rosen::AvoidAreaType>(type));
}
    
bool PreviewSessionWrapperImpl::NotifyOccupiedAreaChangeInfo(
    sptr<Rosen::OccupiedAreaChangeInfo> info, bool needWaitLayout)
{
    CHECK_NULL_RETURN(session_, false);
    CHECK_NULL_RETURN(info, false);
    CHECK_NULL_RETURN(isNotifyOccupiedAreaChange_, false);
    int32_t keyboardHeight = static_cast<int32_t>(info->rect_.height_);
    if (keyboardHeight > 0) {
        ContainerScope scope(instanceId_);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto curWindow = pipeline->GetCurrentWindowRect();
        int32_t spaceWindow = std::max(curWindow.Bottom() - displayArea_.Bottom(), .0);
        keyboardHeight = static_cast<int32_t>(std::max(keyboardHeight - spaceWindow, 0));
    }
    sptr<Rosen::OccupiedAreaChangeInfo> newInfo = new Rosen::OccupiedAreaChangeInfo(
        info->type_, info->rect_, info->safeHeight_, info->textFieldPositionY_, info->textFieldHeight_);
    newInfo->rect_.height_ = static_cast<uint32_t>(keyboardHeight);
    PLATFORM_LOGI("PreviewUIExtension The occcupied area with 'keyboardHeight = %{public}d'"
        "is notified to the provider.", keyboardHeight);
    session_->NotifyOccupiedAreaChangeInfo(newInfo);
    return true;
}
    
void PreviewSessionWrapperImpl::SetDensityDpiImpl(bool isDensityDpi)
{
    CHECK_NULL_VOID(session_);
    if (isDensityDpi) {
        float density = PipelineBase::GetCurrentDensity();
        session_->NotifyDensityFollowHost(isDensityDpi, density);
    }
}
    
void PreviewSessionWrapperImpl::SendDataAsync(const AAFwk::WantParams& params) const
{
    PLATFORM_LOGD("The data is asynchronously send and the session is %{public}s",
        session_ ? "valid" : "invalid");
    CHECK_NULL_VOID(session_);
    session_->TransferComponentData(params);
}
    
int32_t PreviewSessionWrapperImpl::SendDataSync(
    const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const
{
    PLATFORM_LOGD("The data is synchronously send and the session is %{public}s",
        session_ ? "valid" : "invalid");
    Rosen::WSErrorCode transferCode = Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED;
    if (session_) {
        transferCode = session_->TransferComponentDataSync(wantParams, reWantParams);
    }
    return static_cast<int32_t>(transferCode);
}
    
uint32_t PreviewSessionWrapperImpl::GetReasonDump() const
{
    return reason_;
}
    
void PreviewSessionWrapperImpl::NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    CHECK_NULL_VOID(session_);
    session_->NotifyDumpInfo(params, info);
}

bool PreviewSessionWrapperImpl::SendBusinessDataSyncReply(
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
        PLATFORM_LOGW("PreviewUIExtension SendBusinessDataSyncReply Fail, businessCode=%{public}u, "
            "result=%{public}u, subSystemId=%{public}hhu.", code, result, subSystemId);
        return false;
    }
    PLATFORM_LOGI("PreviewUIExtension SendBusinessDataSyncReply Success,"
        "businessCode=%{public}u, subSystemId=%{public}hhu.", code, subSystemId);
    return true;
}
    
int32_t PreviewSessionWrapperImpl::GetInstanceId() const
{
    return instanceId_;
}

void PreviewSessionWrapperImpl::UpdateInstanceId(int32_t instanceId)
{
    if (instanceId_ == instanceId) {
        PLATFORM_LOGW("InstanceId(%{public}d) has not changed when UpdateInstanceId.", instanceId);
        return;
    }
    PLATFORM_LOGI("Update instanceId %{public}d to %{public}d.", instanceId_, instanceId);
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    instanceId_ = instanceId;
    taskExecutor_ = taskExecutor;
    InitAllCallback();
    PLATFORM_LOGI("Update instanceId success.");
}

bool PreviewSessionWrapperImpl::SendBusinessData(
    UIContentBusinessCode code, const  AAFwk::Want& data, BusinessDataSendType type, RSSubsystemId subSystemId)
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
        PLATFORM_LOGD("SendBusinessData ASYNC Success, businessCode=%{public}u, subSystemId=%{public}hhu.",
            code, subSystemId);
            return true;
        }
        auto result = dataHandler->SendDataSync(static_cast<OHOS::Rosen::SubSystemId>(subSystemId),
            static_cast<uint32_t>(code), data);
        if (result != Rosen::DataHandlerErr::OK) {
            PLATFORM_LOGD("SendBusinessData SYNC Fail, businessCode=%{public}u, "
                "result=%{public}u, subSystemId=%{public}hhu.", code, result, subSystemId);
            return false;
        }
        PLATFORM_LOGD("SendBusinessData SYNC Success, businessCode=%{public}u, subSystemId=%{public}hhu.",
            code, subSystemId);
        return true;
}
    
void PreviewSessionWrapperImpl::DispatchExtensionDataToHostWindow(uint32_t customId, const AAFwk::Want& data)
{
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostTask(
        [instanceId, weak = hostPattern_, customId, data, callSessionId]() {
            ContainerScope scope(instanceId);
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("Preview DispatchExtensionDataToHostWindow: The callSessionId(%{public}d)"
                        " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            auto container = Platform::AceContainer::GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            container->DispatchExtensionDataToHostWindow(customId, data, callSessionId);
        },
        TaskExecutor::TaskType::UI, "ArkUIDispatchExtensionSecDataToHostWindow");
}
    
void PreviewSessionWrapperImpl::PostBusinessDataConsumeAsync(uint32_t customId, const AAFwk::Want& data)
{
    PLATFORM_LOGI("PreviewUIExtension PostBusinessDataConsumeAsync, businessCode=%{public}u.", customId);
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostTask(
        [instanceId, weak = hostPattern_, customId, data, callSessionId]() {
            ContainerScope scope(instanceId);
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("PreviewUIExtension BusinessDataConsumeAsync: The callSessionId(%{public}d)"
                    " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            preViewPattern->OnUIExtBusinessReceive(static_cast<UIContentBusinessCode>(customId), data);
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionBusinessDataConsumeAsync");
}
void PreviewSessionWrapperImpl::PostBusinessDataConsumeSyncReply(
    uint32_t customId, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply)
{
    PLATFORM_LOGI("PreviewUIExtension PostBusinessDataConsumeSyncReply, businessCode=%{public}u.", customId);
    int32_t callSessionId = GetSessionId();
    CHECK_NULL_VOID(taskExecutor_);
    auto instanceId = GetInstanceId();
    taskExecutor_->PostSyncTask(
        [instanceId, weak = hostPattern_, customId, data, &reply, callSessionId]() {
            ContainerScope scope(instanceId);
            auto preViewPattern = weak.Upgrade();
            CHECK_NULL_VOID(preViewPattern);
            if (callSessionId != preViewPattern->GetSessionId()) {
                LOGW("PreviewUIExtension BusinessDataConsumeSyncReply: The callSessionId(%{public}d)"
                    " is inconsistent with the curSession(%{public}d)",
                    callSessionId, preViewPattern->GetSessionId());
                return;
            }
            preViewPattern->OnUIExtBusinessReceiveReply(
                static_cast<UIContentBusinessCode>(customId), data, reply);
        },
        TaskExecutor::TaskType::UI, "ArkUIPreviewUIExtensionBusinessDataConsumeSyncReply");
}
    
bool PreviewSessionWrapperImpl::RegisterDataConsumer()
{
    CHECK_NULL_RETURN(session_, false);
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
    auto dataHandler = session_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    auto result = dataHandler->RegisterDataConsumer(subSystemId, std::move(callback));
    if (result != Rosen::DataHandlerErr::OK) {
        PLATFORM_LOGW("PreviewUIExtension RegisterDataConsumer Fail, result=%{public}u", result);
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG