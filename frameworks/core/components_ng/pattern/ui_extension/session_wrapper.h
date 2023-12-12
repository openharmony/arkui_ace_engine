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

#include "base/memory/ace_type.h"

namespace OHOS {

namespace MMI {
class PointerEvent;
class KeyEvent;
class AxisEvent;
} // namespace MMI

namespace Rosen {
class RSSurfaceNode;
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
class SessionWrapper : public AceType {
    DECLARE_ACE_TYPE(SessionWrapper, AceType);

public:
    virtual ~SessionWrapper() = default;

    // About session
    virtual void CreateSession(const AAFwk::Want& want) = 0;
    virtual void DestroySession() = 0;
    virtual bool IsSessionValid() = 0;
    virtual int32_t GetSessionId() = 0;
    virtual const std::shared_ptr<AAFwk::Want> GetWant() = 0;

    // Synchronous interface for event notify
    virtual bool NotifyFocusEventSync(bool isFocus) = 0;
    virtual bool NotifyFocusStateSync(bool focusState) = 0;
    virtual bool NotifyBackPressedSync() = 0;
    virtual bool NotifyPointerEventSync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;
    virtual bool NotifyKeyEventSync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) = 0;
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
    virtual void NotifyBackground() = 0;
    virtual void NotifyDestroy() = 0;
    virtual void NotifyConfigurationUpdate() = 0;

    // The interface about the accessibility
    virtual bool TransferExecuteAction(int32_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int32_t offset) = 0;
    virtual void SearchExtensionElementInfoByAccessibilityId(int32_t elementId, int32_t mode, int32_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) = 0;
    virtual void SearchElementInfosByText(int32_t elementId, const std::string& text, int32_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) = 0;
    virtual void FindFocusedElementInfo(
        int32_t elementId, int32_t focusType, int32_t baseParent, Accessibility::AccessibilityElementInfo& output) = 0;
    virtual void FocusMoveSearch(
        int32_t elementId, int32_t direction, int32_t baseParent, Accessibility::AccessibilityElementInfo& output) = 0;

    // The interface to control the display area
    virtual std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode() const = 0;
    virtual void RefreshDisplayArea(float left, float top, float width, float height) = 0;

    // The interface to send the data for ArkTS
    virtual void SendDataAsync(const AAFwk::WantParams& params) const = 0;
    virtual int32_t SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_H
