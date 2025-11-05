/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"

namespace OHOS::Ace::NG {

enum class Direction {
    PRE = 0,
    NEXT,
};
using ChangeIndicatorEvent = std::function<void()>;
using IndicatorIndexChangeEvent = std::function<void(int32_t index)>;
using ChangeEvent = std::function<void(int32_t index)>;
using ChangeEventPtr = std::shared_ptr<ChangeEvent>;
using ChangeEventWithPreIndex = std::function<void(int32_t preIndex, int32_t currentIndex)>;
using ChangeEventWithPreIndexPtr = std::shared_ptr<ChangeEventWithPreIndex>;
using ChangeDoneEvent = std::function<void()>;

class SwiperEventHub : public EventHub {
    DECLARE_ACE_TYPE(SwiperEventHub, EventHub);

public:
    SwiperEventHub() = default;
    ~SwiperEventHub() override = default;

    /* Using shared_ptr to enable event modification without adding again */
    void AddOnChangeEvent(const ChangeEventPtr& changeEvent)
    {
        changeEvents_.emplace_back(changeEvent);
    }

    void AddOnChangeEventWithPreIndex(const ChangeEventWithPreIndexPtr& changeEventWithPreIndex)
    {
        changeEventsWithPreIndex_.emplace_back(changeEventWithPreIndex);
    }

    void SetIndicatorOnChange(ChangeIndicatorEvent&& changeEvent)
    {
        changeIndicatorEvent_ = std::move(changeEvent);
    }

    void SetIndicatorIndexChangeEvent(IndicatorIndexChangeEvent&& indicatorIndexChangeEvent)
    {
        indicatorIndexChangeEvent_ = std::move(indicatorIndexChangeEvent);
    }

    void SetChangeDoneEvent(ChangeDoneEvent&& changeDoneEvent)
    {
        changeDoneEvent_ = std::move(changeDoneEvent);
    }

    void AddAnimationStartEvent(const AnimationStartEventPtr& animationStartEvent)
    {
        animationStartEvents_.emplace_back(animationStartEvent);
    }

    void AddAnimationEndEvent(const AnimationEndEventPtr& animationEndEvent)
    {
        animationEndEvents_.emplace_back(animationEndEvent);
    }

    void SetGestureSwipeEvent(GestureSwipeEvent&& gestureSwipeEvent)
    {
        gestureSwipeEvent_ = std::move(gestureSwipeEvent);
    }

    void AddOnSlectedEvent(const ChangeEventPtr& changeEvent)
    {
        selectedEvents_.emplace_back(changeEvent);
    }

    void AddOnUnselectedEvent(const ChangeEventPtr& changeEvent)
    {
        unselectedEvents_.emplace_back(changeEvent);
    }

    void AddOnScrollStateChangedEvent(const ChangeEventPtr& changeEvent)
    {
        scrollStateChangedEvent_ = changeEvent;
    }

    Direction GetDirection()
    {
        return direction_;
    }

    void SetSwiperId(int32_t swiperId)
    {
        swiperId_ = swiperId;
    }

    void FireIndicatorChangeEvent(int32_t index) const
    {
        if (changeIndicatorEvent_) {
            changeIndicatorEvent_();
        }
    }

    void FireIndicatorIndexChangeEvent(int32_t index) const
    {
        if (indicatorIndexChangeEvent_) {
            indicatorIndexChangeEvent_(index);
        }
    }

    void FireUnselectedEvent(int32_t index);

    void FireScrollStateChangedEvent(ScrollState scrollState);

    void FireChangeDoneEvent(bool direction);

    void FireChangeEvent(int32_t preIndex, int32_t currentIndex, bool isInLayout);

    void FireAnimationStartEvent(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info);

    void FireAnimationEndEvent(int32_t index, const AnimationCallbackInfo& info);

    void FireAnimationEndOnForceEvent(int32_t index, const AnimationCallbackInfo& info);

    void FireGestureSwipeEvent(int32_t index, const AnimationCallbackInfo& info) const;

    void FireSelectedEvent(int32_t index);

private:
    void FireJSChangeEvent(int32_t preIndex, int32_t index);
    void NotifySwiperObserver(const RefPtr<FrameNode>& hostNode, int32_t index);

    Direction direction_;
    std::list<ChangeEventPtr> unselectedEvents_;
    std::list<ChangeEventPtr> changeEvents_;
    std::list<ChangeEventPtr> selectedEvents_;
    std::list<ChangeEventWithPreIndexPtr> changeEventsWithPreIndex_;
    ChangeEventPtr scrollStateChangedEvent_;
    ChangeDoneEvent changeDoneEvent_;
    ChangeIndicatorEvent changeIndicatorEvent_;
    IndicatorIndexChangeEvent indicatorIndexChangeEvent_;
    std::list<AnimationStartEventPtr> animationStartEvents_;
    std::list<AnimationEndEventPtr> animationEndEvents_;
    GestureSwipeEvent gestureSwipeEvent_;
    int32_t aniStartCalledCount_ = 0;
    std::function<void()> delayCallback_;
    int32_t swiperId_ = -1;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_EVENT_HUB_H