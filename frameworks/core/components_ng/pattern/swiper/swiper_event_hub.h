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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_EVENT_HUB_H

#include <algorithm>
#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

enum class Direction {
    PRE = 0,
    NEXT,
};
using ChangeIndicatorEvent = std::function<void(const BaseEventInfo* info)>;
using ChangeEvent = std::function<void(int32_t index)>;
using ChangeEventPtr = std::shared_ptr<ChangeEvent>;
using ChangeDoneEvent = std::function<void()>;

class SwiperEventHub : public EventHub {
    DECLARE_ACE_TYPE(SwiperEventHub, EventHub)

public:
    SwiperEventHub() = default;
    ~SwiperEventHub() override = default;

    /* Using shared_ptr to enable event modification without adding again */
    void AddOnChangeEvent(const ChangeEventPtr& changeEvent)
    {
        changeEvents_.emplace_back(changeEvent);
    }

    void SetIndicatorOnChange(ChangeIndicatorEvent&& changeEvent)
    {
        changeIndicatorEvent_ = std::move(changeEvent);
    }

    void SetChangeDoneEvent(ChangeDoneEvent&& changeDoneEvent)
    {
        changeDoneEvent_ = std::move(changeDoneEvent);
    }

    void FireChangeDoneEvent(bool direction)
    {
        if (changeDoneEvent_) {
            if (direction == true) {
                direction_ = Direction::NEXT;
            } else {
                direction_ = Direction::PRE;
            }
            changeDoneEvent_();
        }
    }

    void FireChangeEvent(int32_t index) const
    {
        if (!changeEvents_.empty()) {
            std::for_each(
                changeEvents_.begin(), changeEvents_.end(), [index](const ChangeEventPtr& event) { (*event)(index); });
        }
    }

    void FireIndicatorChangeEvent(int32_t index) const
    {
        if (changeIndicatorEvent_) {
            changeIndicatorEvent_(std::make_shared<SwiperChangeEvent>(index).get());
        }
    }

    Direction GetDirection()
    {
        return direction_;
    }

private:
    Direction direction_;
    std::list<ChangeEventPtr> changeEvents_;
    ChangeDoneEvent changeDoneEvent_;
    ChangeIndicatorEvent changeIndicatorEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_EVENT_HUB_H