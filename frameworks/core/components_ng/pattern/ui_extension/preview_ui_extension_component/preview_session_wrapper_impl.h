/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_PREVIEW_SESSION_WRAPPER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_PREVIEW_SESSION_WRAPPER_IMPL_H
 
#include <refbase.h>
 
#include "session/host/include/extension_session.h"
#include "want.h"
 
#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
 
namespace OHOS::Ace::NG {
class PreviewSessionWrapperImpl : public SessionWrapper {
    DECLARE_ACE_TYPE(PreviewSessionWrapperImpl, SessionWrapper);
 
public:
    PreviewSessionWrapperImpl(
        const WeakPtr<PreviewUIExtensionPattern>& hostPattern,
        int32_t instanceId,
        bool isTransferringCaller,
        SessionType sessionType);
    ~PreviewSessionWrapperImpl() override;
 
    // About session
    void CreateSession(const AAFwk::Want& want, const SessionConfig& config) override;
    void DestroySession() override;
    bool IsSessionValid() override;
    int32_t GetSessionId() const override;
    const std::shared_ptr<AAFwk::Want> GetWant() override;
 
    // Synchronous interface for event notify
    bool NotifyFocusEventSync(bool isFocus) override;
    bool NotifyFocusStateSync(bool focusState) override;
    bool NotifyBackPressedSync() override;
    bool NotifyPointerEventSync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override;
    bool NotifyKeyEventSync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) override;
    bool NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) override;
    bool NotifyAxisEventSync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override;
 
    // Asynchronous interface for event notify
    bool NotifyFocusEventAsync(bool isFocus) override;
    bool NotifyFocusStateAsync(bool focusState) override;
    bool NotifyBackPressedAsync() override;
    bool NotifyPointerEventAsync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override;
    bool NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) override;
    bool NotifyAxisEventAsync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override;
 
    // The lifecycle interface
    void NotifyCreate() override;
    void NotifyForeground() override;
    void NotifyBackground(bool isHandleError) override;
    void NotifyDestroy(bool isHandleError = true) override;
    void NotifyConfigurationUpdate() override;
 
    // The interface for responsing provider
    void OnConnect() override;
    void OnDisconnect(bool isAbnormal) override;
    void OnExtensionTimeout(int32_t errorCode) override;
    void OnExtensionDetachToDisplay() override;
    void OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset) override;
 
    void TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType, int32_t eventType,
        int64_t timeMs) override;
    void TransferAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) override;
    void TransferAccessibilityChildTreeDeregister() override;
    void TransferAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) override;
 
    // The interface to control the display area and the avoid area
    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode() const override;
    void NotifyDisplayArea(const RectF& displayArea) override;
    void NotifySizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) override;
    void NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const override;
    bool NotifyOccupiedAreaChangeInfo(
        sptr<Rosen::OccupiedAreaChangeInfo> info, bool needWaitLayout) override;
    void SetDensityDpiImpl(bool isDensityDpi) override;
 
    // The interface to send the data for ArkTS
    void SendDataAsync(const AAFwk::WantParams& params) const override;
    int32_t SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const override;
    
    // The interface for UEC dump
    uint32_t GetReasonDump() const override;
    void NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info) override;
    int32_t GetInstanceId() const;
    void UpdateInstanceId(int32_t instanceId);
    bool SendBusinessDataSyncReply(UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply,
        RSSubsystemId subSystemId = RSSubsystemId::ARKUI_UIEXT) override;
    bool SendBusinessData(UIContentBusinessCode code, const AAFwk::Want& data, BusinessDataSendType type,
        RSSubsystemId subSystemId = RSSubsystemId::ARKUI_UIEXT) override;
    void ReDispatchWantParams() override;
 
private:
    void InitAllCallback();
    bool RegisterDataConsumer();
    void PostBusinessDataConsumeAsync(uint32_t customId, const AAFwk::Want& data);
    void PostBusinessDataConsumeSyncReply(
        uint32_t customId, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply);
    void DispatchExtensionDataToHostWindow(uint32_t customId, const AAFwk::Want& data);
    void UpdateWantPtr(std::shared_ptr<AAFwk::Want>& wantPtr);
    AceLogTag tag_ = AceLogTag::ACE_SECURITYUIEXTENSION;
    WeakPtr<PreviewUIExtensionPattern> hostPattern_;
    RefPtr<TaskExecutor> taskExecutor_;
    int32_t instanceId_;
    bool isTransferringCaller_ = false;
    SessionType sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    int32_t platformId_ = 0;
    sptr<Rosen::ExtensionSession> session_;
    bool isNotifyOccupiedAreaChange_ = true;
    RectF displayArea_;
    uint32_t reason_ = (uint32_t)Rosen::SizeChangeReason::UNDEFINED;
    std::shared_ptr<Rosen::ILifecycleListener> lifecycleListener_;
    std::function<void((OHOS::Rosen::WSError))> foregroundCallback_;
    std::function<void((OHOS::Rosen::WSError))> backgroundCallback_;
    std::function<void((OHOS::Rosen::WSError))> destructionCallback_;
    std::weak_ptr<Rosen::RSTransaction> transaction_;
    std::shared_ptr<AAFwk::Want> customWant_;
    OHOS::Rosen::SubSystemId subSystemId_ = OHOS::Rosen::SubSystemId::ARKUI_UIEXT;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_SECURITY_SESSION_WRAPPER_IMPL_H