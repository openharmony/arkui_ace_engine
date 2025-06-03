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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_H

#include <cstdint>
#include <list>
#include <map>
#include <memory>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "core/common/window_animation_config.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"

namespace OHOS {
template<typename T>
class sptr;

namespace MMI {
class PointerEvent;
class KeyEvent;
class AxisEvent;
} // namespace MMI

namespace Rosen {
class OccupiedAreaChangeInfo;
class RSSurfaceNode;
class RSTransaction;
class AvoidArea;
} // namespace Rosen

namespace AAFwk {
class Want;
class WantParams;
} // namespace AAFwk

namespace Accessibility {
class AccessibilityElementInfo;
class AccessibilityEventInfo;
} // namespace Accessibility

} // namespace OHOS

namespace OHOS::Ace::NG {
enum class SessionType : int32_t {
    EMBEDDED_UI_EXTENSION = 0,
    UI_EXTENSION_ABILITY = 1,
    CLOUD_CARD = 2,
    SECURITY_UI_EXTENSION_ABILITY = 3,
    DYNAMIC_COMPONENT = 4,
    ISOLATED_COMPONENT = 5,
    PREVIEW_UI_EXTENSION_ABILITY = 6,
    INVALID_TYPE = 100,
};

enum class UIExtensionUsage : uint32_t {
    MODAL = 0,
    EMBEDDED = 1,
    CONSTRAINED_EMBEDDED = 2,
    PREVIEW_EMBEDDED = 3,
};

struct SessionConfig {
    bool isAsyncModalBinding = false;
    UIExtensionUsage uiExtensionUsage = UIExtensionUsage::MODAL;
};

class SessionWrapper : public AceType {
    DECLARE_ACE_TYPE(SessionWrapper, AceType);

public:
    virtual ~SessionWrapper() = default;

    // About session
    virtual void CreateSession(
        const AAFwk::Want& want, const SessionConfig& config) = 0;
    virtual void DestroySession() = 0;
    virtual bool IsSessionValid() = 0;
    virtual int32_t GetSessionId() const = 0;
    virtual const std::shared_ptr<AAFwk::Want> GetWant() = 0;

    // Synchronous interface for event notify
    virtual bool NotifyFocusEventSync(bool isFocus) = 0;
    virtual bool NotifyFocusStateSync(bool focusState) = 0;
    virtual bool NotifyBackPressedSync() = 0;
    virtual bool NotifyPointerEventSync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;
    virtual bool NotifyKeyEventSync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) = 0;
    virtual bool NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) = 0;
    virtual bool NotifyAxisEventSync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) = 0;

    // Asynchronous interface for event notify
    virtual bool NotifyFocusEventAsync(bool isFocus) = 0;
    virtual bool NotifyFocusStateAsync(bool focusState) = 0;
    virtual bool NotifyBackPressedAsync() = 0;
    virtual bool NotifyPointerEventAsync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;
    virtual bool NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) = 0;
    virtual bool NotifyAxisEventAsync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) = 0;

    // The lifecycle interface
    virtual void NotifyCreate() = 0;
    virtual void NotifyForeground() = 0;
    virtual void NotifyBackground(bool isHandleError = true) = 0;
    virtual void NotifyDestroy(bool isHandleError = true) = 0;
    virtual void NotifyConfigurationUpdate() = 0;

    // The interface for responsing provider
    virtual void OnConnect() = 0;
    virtual void OnDisconnect(bool isAbnormal) = 0;
    virtual void OnReleaseDone() {}
    virtual void OnExtensionTimeout(int32_t errorCode) = 0;
    virtual void OnExtensionDetachToDisplay() {};
    virtual void OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset) = 0;

    // The interface about the accessibility
    virtual void TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType, int32_t eventType,
        int64_t timeMs) = 0;
    virtual void TransferAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) = 0;
    virtual void TransferAccessibilityChildTreeDeregister() = 0;
    virtual void TransferAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) = 0;

    // The interface to control the display area and the avoid area
    virtual std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode() const = 0;
    virtual void NotifyDisplayArea(const RectF& displayArea) = 0;
    virtual void NotifySizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) = 0;
    virtual void NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const = 0;
    virtual bool NotifyOccupiedAreaChangeInfo(
        sptr<Rosen::OccupiedAreaChangeInfo> info, bool needWaitLayout = false) = 0;
    virtual void SetDensityDpiImpl(bool densityDpi) {}

    // The interface to send the data for ArkTS
    virtual void SendDataAsync(const AAFwk::WantParams& params) const = 0;
    virtual int32_t SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const = 0;

    // The interface to update viewport config
    virtual void UpdateSessionViewportConfig() {}

    // The interface for UEC dump
    virtual uint32_t GetReasonDump() const = 0;
    virtual void NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info) = 0;
    virtual bool SendBusinessDataSyncReply(UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply,
        RSSubsystemId subSystemId = RSSubsystemId::ARKUI_UIEXT) = 0;
    virtual bool SendBusinessData(UIContentBusinessCode code, const AAFwk::Want& data, BusinessDataSendType type,
        RSSubsystemId subSystemId = RSSubsystemId::ARKUI_UIEXT) = 0;

    virtual void NotifyHostWindowMode(int32_t mode) {}
    virtual void ReDispatchWantParams() {}
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_H
