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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H

#include <list>

#include "base/memory/referenced.h"
#include "core/components_ng/event/scrollable_event.h"

namespace OHOS::Ace::NG {

// The gesture event hub is mainly used to handle common gesture events.
class GestureEventHub : public Referenced {
public:
    explicit GestureEventHub(const WeakPtr<FrameNode>& host);
    ~GestureEventHub() override = default;

    void AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        if (!scrollableActuator_) {
            scrollableActuator_ = MakeRefPtr<ScrollableActuator>(host_);
        }
        scrollableActuator_->AddScrollableEvent(scrollableEvent);
    }

    void RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        if (!scrollableActuator_) {
            return;
        }
        scrollableActuator_->RemoveScrollableEvent(scrollableEvent);
    }

    // the return value means prevents event bubbling.
    bool OnTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
    {
        if (scrollableActuator_) {
            scrollableActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, result);
        }
        return false;
    }

private:
    WeakPtr<FrameNode> host_;
    RefPtr<ScrollableActuator> scrollableActuator_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H