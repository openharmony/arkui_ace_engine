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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H

#include <utility>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/input_event_hub.h"

namespace OHOS::Ace::NG {

class FrameNode;

// The event hub is mainly used to handle common collections of events, such as gesture events, mouse events, etc.
class EventHub : public virtual AceType {
    DECLARE_ACE_TYPE(EventHub, AceType)

public:
    EventHub() = default;
    ~EventHub() override = default;

    const RefPtr<GestureEventHub>& GetOrCreateGestureEventHub()
    {
        if (!gestureEventHub_) {
            gestureEventHub_ = MakeRefPtr<GestureEventHub>(WeakClaim(this));
        }
        return gestureEventHub_;
    }

    const RefPtr<GestureEventHub>& GetGestureEventHub() const
    {
        return gestureEventHub_;
    }

    const RefPtr<InputEventHub>& GetOrCreateInputEventHub()
    {
        if (!inputEventHub_) {
            inputEventHub_ = MakeRefPtr<InputEventHub>(WeakClaim(this));
        }
        return inputEventHub_;
    }

    const RefPtr<InputEventHub>& GetInputEventHub() const
    {
        return inputEventHub_;
    }

    const RefPtr<FocusHub>& GetOrCreateFocusHub()
    {
        if (!focusHub_) {
            focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this));
        }
        return focusHub_;
    }

    const RefPtr<FocusHub>& GetFocusHub() const
    {
        return focusHub_;
    }

    void AttachHost(const WeakPtr<FrameNode>& host);

    RefPtr<FrameNode> GetFrameNode() const;

    GetEventTargetImpl CreateGetEventTargetImpl() const;

    void OnContextAttached()
    {
        if (gestureEventHub_) {
            gestureEventHub_->OnContextAttached();
        }
    }

    void SetOnAppear(std::function<void()>&& onAppear)
    {
        onAppear_ = std::move(onAppear);
    }
    void FireOnAppear()
    {
        if (onAppear_) {
            onAppear_();
        }
    }

    void SetOnDisappear(std::function<void()>&& onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
    }
    void FireOnDisappear()
    {
        if (onDisappear_) {
            onDisappear_();
        }
    }

    using OnAreaChangedFunc =
        std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>;
    void SetOnAreaChanged(OnAreaChangedFunc&& onAreaChanged)
    {
        onAreaChanged_ = std::move(onAreaChanged);
    }

    void FireOnAreaChanged(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
    {
        if (onAreaChanged_) {
            onAreaChanged_(oldRect, oldOrigin, rect, origin);
        }
    }

    bool HasOnAreaChanged() const
    {
        return static_cast<bool>(onAreaChanged_);
    }

private:
    WeakPtr<FrameNode> host_;
    RefPtr<GestureEventHub> gestureEventHub_;
    RefPtr<InputEventHub> inputEventHub_;
    RefPtr<FocusHub> focusHub_;

    std::function<void()> onAppear_;
    std::function<void()> onDisappear_;
    OnAreaChangedFunc onAreaChanged_;

    ACE_DISALLOW_COPY_AND_MOVE(EventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H