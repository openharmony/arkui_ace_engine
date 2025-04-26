/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_PATTERN_H

#include <cstdint>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <refbase.h>
#include <vector>

#include "base/memory/referenced.h"
#include "base/want/want_wrap.h"
#include "core/common/container.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

#define PLATFORM_LOGD(fmt, ...)                                                 \
    TAG_LOGD(tag_, "[@%{public}d][ID: %{public}d] " fmt, __LINE__, platformId_, \
        ##__VA_ARGS__)
#define PLATFORM_LOGI(fmt, ...)                                                 \
    TAG_LOGI(tag_, "[@%{public}d][ID: %{public}d] " fmt, __LINE__, platformId_, \
        ##__VA_ARGS__)
#define PLATFORM_LOGW(fmt, ...)                                                 \
    TAG_LOGW(tag_, "[@%{public}d][ID: %{public}d] " fmt, __LINE__, platformId_, \
        ##__VA_ARGS__)
#define PLATFORM_LOGE(fmt, ...)                                                 \
    TAG_LOGE(tag_, "[@%{public}d][ID: %{public}d] " fmt, __LINE__, platformId_, \
        ##__VA_ARGS__)
#define PLATFORM_LOGF(fmt, ...)                                                 \
    TAG_LOGF(tag_, "[@%{public}d][ID: %{public}d] " fmt, __LINE__, platformId_, \
        ##__VA_ARGS__)

namespace OHOS::MMI {
class KeyEvent;
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {
class ModalUIExtensionProxy;
} // namespace OHOS::Ace

namespace OHOS::Rosen {
class AvoidArea;
class RSTransaction;
} // namespace OHOS::Rosen

namespace OHOS::Ace::NG {
class UIExtensionProxy;
class PlatformPattern : public Pattern {
    DECLARE_ACE_TYPE(PlatformPattern, Pattern);

public:
    explicit PlatformPattern(AceLogTag tag, int32_t platformId);
    ~PlatformPattern() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    FocusPattern GetFocusPattern() const override;
    void OnMountToParentDone() override;
    void HandleDragEvent(const DragPointerEvent& info) override;

    virtual void SetOnErrorCallback(const std::function<void(int32_t code,
        const std::string& name, const std::string& message)>&& callback);
    virtual void FireOnErrorCallback(
        int32_t code, const std::string& name, const std::string& message);

    int32_t GetInstanceId();
    int32_t GetNodeId();
    bool HandleTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

protected:
    virtual void DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) {}
    virtual void DispatchFocusActiveEvent(bool isFocusActive) {}
    virtual bool HandleKeyEvent(const KeyEvent& event);
    virtual void HandleFocusEvent();
    virtual void HandleBlurEvent();

    AceLogTag tag_ = AceLogTag::ACE_DEFAULT_DOMAIN;
    int32_t platformId_ = -1;
    int32_t instanceId_ = Container::CurrentId();

protected:
    struct ErrorMsg {
        int32_t code = 0;
        std::string name;
        std::string message;
    };

    void OnModifyDone() override;

    void InitKeyEvent(const RefPtr<FocusHub>& focusHub);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void InitHoverEvent(const RefPtr<InputEventHub>& inputHub);
    virtual void HandleTouchEvent(const TouchEventInfo& info);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleHoverEvent(bool isHover);

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    std::shared_ptr<MMI::PointerEvent> lastPointerEvent_ = nullptr;
    ErrorMsg lastError_;

    std::function<void(int32_t code, const std::string& name, const std::string& message)> onErrorCallback_;
    ACE_DISALLOW_COPY_AND_MOVE(PlatformPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_PATTERN_H
