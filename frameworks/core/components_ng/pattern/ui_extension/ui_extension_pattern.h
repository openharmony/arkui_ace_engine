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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H

#include <cstdint>
#include <functional>
#include <memory>
#include <refbase.h>
#include <list>
#include <vector>

#include "base/memory/referenced.h"
#include "base/want/want_wrap.h"
#include "core/common/container.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Rosen {
class Session;
class ILifecycleListener;
enum class WSError;
} // namespace OHOS::Rosen

namespace OHOS::Accessibility {
class AccessibilityElementInfo;
class AccessibilityEventInfo;
} // namespace OHOS::Accessibility

namespace OHOS::MMI {
class KeyEvent;
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {
class ModalUIExtensionProxy;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class UIExtensionProxy;
class UIExtensionPattern : public Pattern {
    DECLARE_ACE_TYPE(UIExtensionPattern, Pattern);

public:
    UIExtensionPattern();
    ~UIExtensionPattern() override;

    void UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    void UpdateWant(const AAFwk::Want& want);

    void DestorySession();

    void OnWindowShow() override;
    void OnWindowHide() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    FocusPattern GetFocusPattern() const override;
    void OnVisibleChange(bool visible) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void SetModalOnDestroy(const std::function<void()>&& callback);
    void SetModalOnRemoteReadyCallback(
    const std::function<void(const std::shared_ptr<ModalUIExtensionProxy>&)>&& callback);
    void SetOnRemoteReadyCallback(const std::function<void(const RefPtr<UIExtensionProxy>&)>&& callback);
    void SetOnSyncOnCallbackList(
        const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList);
    void SetOnAsyncOnCallbackList(
        const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList);
    void SetOnSyncOffCallbackList(
        const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList);
    void SetOnAsyncOffCallbackList(
        const std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>>&& callbackList);
    void SetOnReleaseCallback(const std::function<void(int32_t)>&& callback);
    void SetOnResultCallback(const std::function<void(int32_t, const AAFwk::Want&)>&& callback);
    void SetOnReceiveCallback(const std::function<void(const AAFwk::WantParams&)>&& callback);
    void SetOnErrorCallback(
        const std::function<void(int32_t code, const std::string& name, const std::string& message)>&& callback);
    void SetTransferringCaller(bool value);

    void RegisterLifecycleListener();
    void UnregisterLifecycleListener();

    void OnConnect();
    void OnDisconnect();
    void OnExtensionDied();
    bool OnBackPressed();

    void RequestExtensionSessionActivation();
    void RequestExtensionSessionBackground();
    void RequestExtensionSessionDestruction();

    virtual void SearchExtensionElementInfoByAccessibilityId(int32_t elementId, int32_t mode,
        int32_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) override;
    virtual void SearchElementInfosByText(int32_t elementId, const std::string& text,
        int32_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) override;
    virtual void FindFocusedElementInfo(int32_t elementId, int32_t focusType,
        int32_t baseParent, Accessibility::AccessibilityElementInfo& output) override;
    virtual void FocusMoveSearch(int32_t elementId, int32_t direction,
        int32_t baseParent, Accessibility::AccessibilityElementInfo& output) override;
    virtual bool TransferExecuteAction(int32_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int32_t offset) override;

    int32_t GetSessionId();
    void SetModalFlag(bool isModal)
    {
        isModal_ = isModal;
    }

    int32_t GetUiExtensionId() override;
    int32_t WrapExtensionAbilityId(int32_t extensionOffset, int32_t abilityId) override;

    void OnAccessibilityEvent(
        const Accessibility::AccessibilityEventInfo& info, const std::vector<int32_t>& uiExtensionIdLevelList);

    void HandleDragEvent(const PointerEvent& info) override;

private:
    enum ReleaseCode {
        DESTROY_NORMAL = 0,
        CONNECT_BROKEN,
    };

    enum AbilityState {
        NONE = 0,
        FOREGROUND,
        BACKGROUND,
        DESTRUCTION,
    };

    struct ErrorMsg {
        int32_t code = 0;
        std::string name;
        std::string message;
    };

    void OnModifyDone() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void HandleFocusEvent();
    void HandleBlurEvent();
    bool KeyEventConsumed(const KeyEvent& event);

    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleMouseEvent(const MouseInfo& info);
    void UnregisterAbilityResultListener();

    void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent);
    void DispatchBackpressedEventForConsumed(bool& isConsumed);
    void DispatchKeyEventForConsumed(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed);
    void DisPatchFocusActiveEvent(bool isFocusActive);
    void TransferFocusState(bool focusState);

    void RegisterVisibleAreaChange();
    void UpdateTextFieldManager(const Offset& offset, float height);
    bool IsCurrentFocus() const;

    void ProcessUIExtensionSessionActivationResult(OHOS::Rosen::WSError errcode);
    void ProcessUIExtensionSessionBackgroundResult(OHOS::Rosen::WSError errcode);
    void ProcessUIExtensionSessionDestructionResult(OHOS::Rosen::WSError errcode);

    void onConfigurationUpdate();
    void OnLanguageConfigurationUpdate() override;
    void OnColorConfigurationUpdate() override;

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;

    std::function<void()> onModalDestroy_;
    std::function<void(const std::shared_ptr<ModalUIExtensionProxy>&)> onModalRemoteReadyCallback_;
    std::function<void(const RefPtr<UIExtensionProxy>&)> onRemoteReadyCallback_;
    std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>> onSyncOnCallbackList_;
    std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>> onAsyncOnCallbackList_;
    std::function<void(int32_t)> onReleaseCallback_;
    std::function<void(int32_t, const AAFwk::Want&)> onResultCallback_;
    std::function<void(const AAFwk::WantParams&)> onReceiveCallback_;
    std::function<void(int32_t code, const std::string& name, const std::string& message)> onErrorCallback_;

    std::shared_ptr<Rosen::ILifecycleListener> lifecycleListener_;
    sptr<Rosen::Session> session_;
    RefPtr<FrameNode> contentNode_;

    ErrorMsg lastError_;
    int32_t instanceId_ = Container::CurrentId();
    AbilityState state_ = AbilityState::NONE;
    ACE_DISALLOW_COPY_AND_MOVE(UIExtensionPattern);

    bool transferringCaller_ = false;
    bool isVisible_ = true;
    bool isModal_ = false;

    int32_t uiExtensionId_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H
