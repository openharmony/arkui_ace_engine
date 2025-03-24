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
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/base/frame_node.h"
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
    DECLARE_ACE_TYPE(SwiperEventHub, EventHub)

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

    void FireChangeDoneEvent(bool direction)
    {
        if (changeDoneEvent_) {
            if (direction) {
                direction_ = Direction::NEXT;
            } else {
                direction_ = Direction::PRE;
            }
            changeDoneEvent_();
        }
    }

    void FireChangeEvent(int32_t preIndex, int32_t currentIndex) const
    {
        ACE_SCOPED_TRACE("Swiper FireChangeEvent, preIndex: %d currentIndex: %d eventSize: %zu",
            preIndex, currentIndex, changeEvents_.size() + changeEventsWithPreIndex_.size());
        if (!changeEvents_.empty()) {
            std::for_each(
                changeEvents_.begin(), changeEvents_.end(), [currentIndex](const ChangeEventPtr& changeEvent) {
                    auto event = *changeEvent;
                    event(currentIndex);
                });
        }
        if (!changeEventsWithPreIndex_.empty()) {
            std::for_each(changeEventsWithPreIndex_.begin(), changeEventsWithPreIndex_.end(),
                [preIndex, currentIndex](const ChangeEventWithPreIndexPtr& changeEventWithPreIndex) {
                    auto event = *changeEventWithPreIndex;
                    event(preIndex, currentIndex);
                });
        }

        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            auto host = GetFrameNode();
            if (host) {
                auto id = host->GetInspectorIdValue("");
                builder.SetId(id).SetType(host->GetHostTag()).SetDescription(host->GetAutoEventParamValue(""));
                if (!id.empty()) {
                    Recorder::NodeDataCache::Get().PutInt(host, id, currentIndex);
                }
            }
            builder.SetIndex(currentIndex);
            Recorder::EventRecorder::Get().OnChange(std::move(builder));
        }
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

    Direction GetDirection()
    {
        return direction_;
    }

    void FireAnimationStartEvent(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info)
    {
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "FireAnimationStartEvent, index: %{public}d, targetIndex: %{public}d, id:%{public}d", index, targetIndex,
            swiperId_);
        ACE_SCOPED_TRACE(
            "Swiper FireAnimationStartEvent, index: %d, targetIndex %d, id: %d", index, targetIndex, swiperId_);
        if (!animationStartEvents_.empty()) {
            std::for_each(animationStartEvents_.begin(), animationStartEvents_.end(),
                [index, targetIndex, info](const AnimationStartEventPtr& animationStartEvent) {
                    auto event = *animationStartEvent;
                    event(index, targetIndex, info);
                });
        }
        // animationEnd callback need to be fired after animationStart callback, use flag for protection.
        ++aniStartCalledCount_;
        if (delayCallback_) {
            TAG_LOGI(AceLogTag::ACE_SWIPER, "the timing of the animation callback has been corrected");
            delayCallback_();
            delayCallback_ = nullptr;
        }
    }

    void FireAnimationEndEvent(int32_t index, const AnimationCallbackInfo& info)
    {
        if (aniStartCalledCount_ <= 0) {
            delayCallback_ = [weak = WeakClaim(this), index, info]() {
                auto hub = weak.Upgrade();
                CHECK_NULL_VOID(hub);
                hub->FireAnimationEndEvent(index, info);
            };
            return;
        }
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "FireAnimationEndEvent index: %{public}d, currentOffset: has_value %{public}d, value %{public}fvp, "
            "isForce: %{public}d, aniStartCalledCount %{public}d, id:%{public}d",
            index, info.currentOffset.has_value(), info.currentOffset.value_or(0.0), info.isForceStop,
            aniStartCalledCount_, swiperId_);
        ACE_SCOPED_TRACE("Swiper FireAnimationEndEvent, index: %d, id: %d", index, swiperId_);
        if (!animationEndEvents_.empty()) {
            std::for_each(animationEndEvents_.begin(), animationEndEvents_.end(),
                [index, info](const AnimationEndEventPtr& animationEndEvent) {
                    auto event = *animationEndEvent;
                    event(index, info);
                });
        }
        --aniStartCalledCount_;
    }

    void FireAnimationEndOnForceEvent(int32_t index, const AnimationCallbackInfo& info)
    {
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "FireAnimationEndOnForceEvent index: %{public}d, aniStartCalledCount %{public}d, id:%{public}d", index,
            aniStartCalledCount_, swiperId_);
        if (aniStartCalledCount_ <= 0) {
            delayCallback_ = [weak = WeakClaim(this), index, info]() {
                auto hub = weak.Upgrade();
                CHECK_NULL_VOID(hub);
                hub->FireAnimationEndOnForceEvent(index, info);
            };
            return;
        }
        if (!animationEndEvents_.empty()) {
            auto context = GetFrameNode()->GetContext();
            CHECK_NULL_VOID(context);
            context->AddBuildFinishCallBack([this, index, info]() {
                std::for_each(animationEndEvents_.begin(), animationEndEvents_.end(),
                    [index, info](const AnimationEndEventPtr& animationEndEvent) {
                        auto event = *animationEndEvent;
                        event(index, info);
                    });
            });
        }
        --aniStartCalledCount_;
    }

    void FireGestureSwipeEvent(int32_t index, const AnimationCallbackInfo& info) const
    {
        if (gestureSwipeEvent_) {
            // gestureSwipeEvent_ may be overwrite in its invoke, so copy it first
            auto event = gestureSwipeEvent_;
            event(index, info);
        }
    }

    void SetSwiperId(int32_t swiperId)
    {
        swiperId_ = swiperId;
    }

private:
    Direction direction_;
    std::list<ChangeEventPtr> changeEvents_;
    std::list<ChangeEventWithPreIndexPtr> changeEventsWithPreIndex_;
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