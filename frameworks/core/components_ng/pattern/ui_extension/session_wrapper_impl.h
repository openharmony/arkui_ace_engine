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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_IMPL_H

#include <refbase.h>

#include "session/host/include/extension_session.h"
#include "want.h"

#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
class SessionWrapperImpl : public SessionWrapper {
    DECLARE_ACE_TYPE(SessionWrapperImpl, SessionWrapper);

public:
    SessionWrapperImpl(const WeakPtr<UIExtensionPattern>& hostPattern, int32_t instanceId, bool isTransferringCaller,
        SessionType sessionType);
    ~SessionWrapperImpl() override;

    // About session
    void CreateSession(const AAFwk::Want& want, bool isAsyncModalBinding = false) override;
    void DestroySession() override;
    bool IsSessionValid() override;
    int32_t GetSessionId() override;
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
    void NotifyBackground() override;
    void NotifyDestroy() override;
    void NotifyConfigurationUpdate() override;

    // The interface for responsing provider
    void OnConnect() override;
    void OnDisconnect(bool isAbnormal) override;
    void OnExtensionTimeout(int32_t errorCode) override;
    void OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset) override;

    // The interface about the accessibility
    bool TransferExecuteAction(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset) override;
    void SearchExtensionElementInfoByAccessibilityId(int64_t elementId, int32_t mode, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void SearchElementInfosByText(int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;
    void FindFocusedElementInfo(int64_t elementId, int32_t focusType, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    void FocusMoveSearch(int64_t elementId, int32_t direction, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output) override;
    void TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType, int32_t eventType,
        int64_t timeMs) override;

    // The interface to control the display area and the avoid area
    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode() const override;
    void NotifyDisplayArea(const RectF& displayArea) override;
    void NotifySizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) override;
    void NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const override;
    bool NotifyOccupiedAreaChangeInfo(sptr<Rosen::OccupiedAreaChangeInfo> info) const override;

    // The interface to send the data for ArkTS
    void SendDataAsync(const AAFwk::WantParams& params) const override;
    int32_t SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const override;

private:
    void InitAllCallback();
    WeakPtr<UIExtensionPattern> hostPattern_;
    RefPtr<TaskExecutor> taskExecutor_;
    int32_t instanceId_;
    bool isTransferringCaller_;
    SessionType sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    int32_t uiExtensionId_ = 0;
    sptr<Rosen::ExtensionSession> session_;
    bool isNotifyOccupiedAreaChange_ = false;
    RectF displayArea_;
    std::shared_ptr<Rosen::ILifecycleListener> lifecycleListener_;
    std::function<void((OHOS::Rosen::WSError))> foregroundCallback_;
    std::function<void((OHOS::Rosen::WSError))> backgroundCallback_;
    std::function<void((OHOS::Rosen::WSError))> destructionCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_IMPL_H
