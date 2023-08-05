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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H

#include "key_event.h"
#include "pointer_event.h"
#include "session/host/include/session.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class WindowPattern : public Pattern {
    DECLARE_ACE_TYPE(WindowPattern, Pattern);

public:
    WindowPattern() = default;
    ~WindowPattern() override = default;

    std::vector<Rosen::Rect> GetHotAreas();

protected:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;

    void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent);
    void DispatchKeyEventForConsumed(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed);
    void DisPatchFocusActiveEvent(bool isFocusActive);
    void TransferFocusState(bool focusState);

    virtual bool HasStartingPage() = 0;
    bool IsMainWindow() const;

    void RegisterLifecycleListener();
    void UnregisterLifecycleListener();

    void InitContent();
    void CreateStartingNode();
    void CreateSnapshotNode();

    virtual void OnConnect() {}
    virtual void OnForeground() {}
    virtual void OnBackground() {}
    virtual void OnDisconnect() {}
    virtual void OnExtensionDied() {}

    RefPtr<FrameNode> startingNode_;
    RefPtr<FrameNode> contentNode_;
    RefPtr<FrameNode> snapshotNode_;

    sptr<Rosen::Session> session_;
    int32_t instanceId_ = Container::CurrentId();
    std::function<void()> callback_;

private:
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    bool IsFilterTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    bool IsFilterMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    std::shared_ptr<Rosen::ILifecycleListener> lifecycleListener_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;

    friend class LifecycleListener;
    friend class WindowEventProcess;

    ACE_DISALLOW_COPY_AND_MOVE(WindowPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
