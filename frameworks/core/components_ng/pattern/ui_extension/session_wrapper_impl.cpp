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
constexpr char LIFECYCLE_TIMEOUT_NAME[] = "extension_lifecycle_timeout";
constexpr char LIFECYCLE_TIMEOUT_MESSAGE[] = "the lifecycle of extension ability is timeout, please check AMS log.";
constexpr char EVENT_TIMEOUT_NAME[] = "handle_event_timeout";
constexpr char EVENT_TIMEOUT_MESSAGE[] = "the extension ability has timed out processing the key event.";
// Defines the want parameter to control the soft-keyboard area change of the provider.
constexpr char OCCUPIED_AREA_CHANGE_KEY[] = "ability.want.params.IsNotifyOccupiedAreaChange";
// Set the UIExtension type of the EmbeddedComponent.
constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
const std::string EMBEDDED_UI("embeddedUI");
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

    foregroundCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_](OHOS::Rosen::WSError errcode) {
        if (errcode != OHOS::Rosen::WSError::WS_OK) {
            taskExecutor->PostTask(
                [weak, errcode] {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->FireOnErrorCallback(static_cast<int32_t>(errcode), START_FAIL_NAME, START_FAIL_MESSAGE);
                },
                TaskExecutor::TaskType::UI);
        }
    };
    backgroundCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_](OHOS::Rosen::WSError errcode) {
        if (errcode != OHOS::Rosen::WSError::WS_OK) {
            taskExecutor->PostTask(
                [weak, errcode] {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->FireOnErrorCallback(
                        static_cast<int32_t>(errcode), BACKGROUND_FAIL_NAME, BACKGROUND_FAIL_MESSAGE);
                },
                TaskExecutor::TaskType::UI);
        }
    };
    destructionCallback_ = [weak = hostPattern_, taskExecutor = taskExecutor_](OHOS::Rosen::WSError errcode) {
        if (errcode != OHOS::Rosen::WSError::WS_OK) {
            taskExecutor->PostTask(
                [weak, errcode] {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->FireOnErrorCallback(
                        static_cast<int32_t>(errcode), TERMINATE_FAIL_NAME, TERMINATE_FAIL_MESSAGE);
                },
                TaskExecutor::TaskType::UI);
        }
    };
    sessionCallbacks->transferAbilityResultFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_,
                                                       sessionType = sessionType_](
                                                       int32_t code, const AAFwk::Want& want) {
        taskExecutor->PostTask(
            [weak, code, want, sessionType]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (sessionType == SessionType::UI_EXTENSION_ABILITY) {
                    pattern->FireOnResultCallback(code, want);
                } else {
                    pattern->FireOnTerminatedCallback(code, MakeRefPtr<WantWrapOhos>(want));
                }
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->transferExtensionDataFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_](
                                                       const AAFwk::WantParams& params) {
        taskExecutor->PostTask(
            [weak, params]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireOnReceiveCallback(params);
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->notifyRemoteReadyFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_]() {
        taskExecutor->PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireOnRemoteReadyCallback();
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->notifySyncOnFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_]() {
        taskExecutor->PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireSyncCallbacks();
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->notifyAsyncOnFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_]() {
        taskExecutor->PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireAsyncCallbacks();
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->notifyBindModalFunc_ = [weak = hostPattern_, taskExecutor = taskExecutor_]() {
        taskExecutor->PostSyncTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireBindModalCallback();
            },
            TaskExecutor::TaskType::UI);
    };
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_ = [instanceId = instanceId_](
                                                          Rosen::AvoidAreaType type) -> Rosen::AvoidArea {
        Rosen::AvoidArea avoidArea;
        auto container = Platform::AceContainer::GetContainer(instanceId);
        CHECK_NULL_RETURN(container, avoidArea);
        avoidArea = container->GetAvoidAreaByType(type);
        return avoidArea;
    };
}
/************************************************ End: Initialization *************************************************/

/************************************************ Begin: About session ************************************************/
void SessionWrapperImpl::CreateSession(const AAFwk::Want& want, bool isAsyncModalBinding)
{
    UIEXT_LOGI("The session is created with want = %{private}s", want.ToString().c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
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
    isNotifyOccupiedAreaChange_ = want.GetBoolParam(OCCUPIED_AREA_CHANGE_KEY, false);
    auto callerToken = container->GetToken();
    auto parentToken = container->GetParentToken();
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = want.GetElement().GetBundleName(),
        .abilityName_ = want.GetElement().GetAbilityName(),
        .callerToken_ = callerToken,
        .rootToken_ = (isTransferringCaller_ && parentToken) ? parentToken : callerToken,
        .want = wantPtr,
        .isAsyncModalBinding_ = isAsyncModalBinding,
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<UIExtensionLifecycleListener>(AceType::WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
    InitAllCallback();
}

void SessionWrapperImpl::DestroySession()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
    session_ = nullptr;
}

bool SessionWrapperImpl::IsSessionValid()
{
    return session_ != nullptr;
}

int32_t SessionWrapperImpl::GetSessionId()
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
    UIEXT_LOGD("The back evnet is notified to the provider and %{public}s consumed.", isConsumed ? "is" : "is not");
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
    UIEXT_LOGD("The key evnet is notified to the provider and %{public}s consumed.", isConsumed ? "is" : "is not");
    return isConsumed;
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
    UIEXT_LOGD("Notify the provider to %{public}s the focus state.", isFocus ? "paint" : "clear");
    session_->TransferFocusActiveEvent(isFocus);
    return true;
}

bool SessionWrapperImpl::NotifyFocusStateAsync(bool focusState)
{
    CHECK_NULL_RETURN(session_, false);
    UIEXT_LOGD("The %{public}s state is notified to the provider.", focusState ? "focused" : "unfocused");
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
        UIEXT_LOGD("Transfer the pointer event with 'id = %{public}d' to the provider.", pointerEvent->GetId());
        session_->TransferPointerEvent(pointerEvent);
    }
    return false;
}
bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    if (session_ && keyEvent) {
        UIEXT_LOGD("Transfer the key event with 'id = %{public}d' to the provider.", keyEvent->GetId());
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

void SessionWrapperImpl::NotifyForeground()
{
    CHECK_NULL_VOID(session_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hostWindowId = pipeline->GetFocusWindowId();
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(
        session_, hostWindowId, std::move(foregroundCallback_));
}

void SessionWrapperImpl::NotifyBackground()
{
    CHECK_NULL_VOID(session_);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(
        session_, std::move(backgroundCallback_));
}
void SessionWrapperImpl::NotifyDestroy()
{
    CHECK_NULL_VOID(session_);
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(
        session_, std::move(destructionCallback_));
}

void SessionWrapperImpl::NotifyConfigurationUpdate() {}
/************************************************ End: The lifecycle interface ****************************************/

/************************************************ Begin: The interface for responsing provider ************************/
void SessionWrapperImpl::OnConnect()
{
    taskExecutor_->PostTask(
        [weak = hostPattern_, wrapperWeak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
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
        TaskExecutor::TaskType::UI);
}

void SessionWrapperImpl::OnDisconnect(bool isAbnormal)
{
    taskExecutor_->PostTask(
        [weak = hostPattern_, sessionType = sessionType_, isAbnormal]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnDisconnect(isAbnormal);
            if (sessionType == SessionType::UI_EXTENSION_ABILITY) {
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
        TaskExecutor::TaskType::UI);
}

void SessionWrapperImpl::OnExtensionTimeout(int32_t /* errorCode */)
{
    taskExecutor_->PostTask(
        [weak = hostPattern_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireOnErrorCallback(
                ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT, LIFECYCLE_TIMEOUT_NAME, LIFECYCLE_TIMEOUT_MESSAGE);
        },
        TaskExecutor::TaskType::UI);
}

void SessionWrapperImpl::OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset)
{
    taskExecutor_->PostTask(
        [weak = hostPattern_, info, offset]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAccessibilityEvent(info, offset);
        },
        TaskExecutor::TaskType::UI);
}
/************************************************** End: The interface for responsing provider ************************/

/************************************************ Begin: The interface about the accessibility ************************/
bool SessionWrapperImpl::TransferExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    CHECK_NULL_RETURN(session_, false);
    return OHOS::Rosen::WSError::WS_OK == session_->TransferExecuteAction(elementId, actionArguments, action, offset);
}

void SessionWrapperImpl::SearchExtensionElementInfoByAccessibilityId(
    int64_t elementId, int32_t mode, int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(session_);
    session_->TransferSearchElementInfo(elementId, mode, baseParent, output);
}

void SessionWrapperImpl::SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
    std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(session_);
    session_->TransferSearchElementInfosByText(elementId, text, baseParent, output);
}

void SessionWrapperImpl::FindFocusedElementInfo(
    int64_t elementId, int32_t focusType, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFindFocusedElementInfo(elementId, focusType, baseParent, output);
}

void SessionWrapperImpl::FocusMoveSearch(
    int64_t elementId, int32_t direction, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusMoveSearch(elementId, direction, baseParent, output);
}

void SessionWrapperImpl::TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    CHECK_NULL_VOID(session_);
    session_->TransferAccessibilityHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
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
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto curWindow = pipeline->GetCurrentWindowRect();
    displayArea_ = displayArea + OffsetF(curWindow.Left(), curWindow.Top());
    UIEXT_LOGD("The display area with '%{public}s' is notified to the provider.", displayArea_.ToString().c_str());
    std::shared_ptr<Rosen::RSTransaction> transaction;
    auto parentSession = session_->GetParentSession();
    auto reason = parentSession ? parentSession->GetSizeChangeReason() : session_->GetSizeChangeReason();
    if (reason == Rosen::SizeChangeReason::ROTATION) {
        if (auto transactionController = Rosen::RSSyncTransactionController::GetInstance()) {
            transaction = transactionController->GetRSTransaction();
            auto pipelineContext = PipelineContext::GetCurrentContext();
            if (transaction && parentSession && pipelineContext) {
                transaction->SetDuration(pipelineContext->GetSyncAnimationOption().GetDuration());
            }
        }
    }
    session_->UpdateRect({ std::round(displayArea_.Left()), std::round(displayArea_.Top()),
        std::round(displayArea_.Width()), std::round(displayArea_.Height()) }, reason, transaction);
}

void SessionWrapperImpl::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(session_);
    auto reason = static_cast<Rosen::SizeChangeReason>(type);
    session_->UpdateSizeChangeReason(reason);
    if (rsTransaction && (type == WindowSizeChangeReason::ROTATION)) {
        session_->UpdateRect(session_->GetSessionRect(), reason, rsTransaction);
    }
}

void SessionWrapperImpl::NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const
{
    CHECK_NULL_VOID(session_);
    UIEXT_LOGD("The avoid area is notified to the provider.");
    session_->UpdateAvoidArea(sptr<Rosen::AvoidArea>::MakeSptr(avoidArea), static_cast<Rosen::AvoidAreaType>(type));
}

bool SessionWrapperImpl::NotifyOccupiedAreaChangeInfo(sptr<Rosen::OccupiedAreaChangeInfo> info) const
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
    info->rect_.height_ = static_cast<uint32_t>(keyboardHeight);
    UIEXT_LOGD("The occcupied area with 'keyboardHeight = %{public}d' is notified to the provider.", keyboardHeight);
    session_->NotifyOccupiedAreaChangeInfo(info);
    return true;
}
/***************************** End: The interface to control the display area and the avoid area **********************/

/************************************************ Begin: The interface to send the data for ArkTS *********************/
void SessionWrapperImpl::SendDataAsync(const AAFwk::WantParams& params) const
{
    UIEXT_LOGD("The data is asynchronously send and the session is %{public}s", session_ ? "valid" : "invalid");
    CHECK_NULL_VOID(session_);
    session_->TransferComponentData(params);
}

int32_t SessionWrapperImpl::SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const
{
    UIEXT_LOGD("The data is synchronously send and the session is %{public}s", session_ ? "valid" : "invalid");
    Rosen::WSErrorCode transferCode = Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED;
    if (session_) {
        transferCode = session_->TransferComponentDataSync(wantParams, reWantParams);
    }
    return static_cast<int32_t>(transferCode);
}
/************************************************ End: The interface to send the data for ArkTS ***********************/
} // namespace OHOS::Ace::NG
