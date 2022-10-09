/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

#include <functional>
#include <memory>

#include "base/utils/macros.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {

using ClickEventFunc = std::function<void(const ClickInfo* info)>;
using RemoteCallback = std::function<void(const BaseEventInfo* info)>;

class ACE_EXPORT ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    // event
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) = 0;
    virtual void SetOnTouch(TouchEventFunc&& touchEventFunc) = 0;
    virtual void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) = 0;
    virtual void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) = 0;
    virtual void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) = 0;
    virtual void SetOnDelete(std::function<void()>&& onDeleteCallback) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) = 0;
    virtual void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) = 0;
    virtual void SetTouchable(bool touchable) = 0;
    virtual void SetFocusable(bool focusable) = 0;
    virtual void SetFocusNode(bool focus) = 0;

private:
    static std::unique_ptr<ViewAbstractModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
