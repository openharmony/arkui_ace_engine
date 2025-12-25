/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_event_hub.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::NG {
void SwiperEventHub::FireUnselectedEvent(int32_t index)
{
    auto frameNode = GetFrameNode();
    TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper FireUnselectedEvent id:%{public}d, index:%{public}d",
        frameNode ? frameNode->GetId() : -1, index);
    ACE_SCOPED_TRACE("Swiper FireUnselectedEvent, id: %d, index: %d", frameNode ? frameNode->GetId() : -1, index);
    if (!unselectedEvents_.empty()) {
        std::for_each(unselectedEvents_.begin(), unselectedEvents_.end(),
            [index](const ChangeEventPtr& changeEvent) {
            if (!changeEvent || !(*changeEvent)) {
                return;
            }
            auto event = *changeEvent;
            event(index);
        });
    }
}

void SwiperEventHub::FireScrollStateChangedEvent(ScrollState scrollState)
{
    if (!scrollStateChangedEvent_ || !(*scrollStateChangedEvent_)) {
        return;
    }
    auto event = *scrollStateChangedEvent_;
    event(static_cast<int32_t>(scrollState));
}

void SwiperEventHub::FireChangeDoneEvent(bool direction)
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

void SwiperEventHub::FireChangeEvent(int32_t preIndex, int32_t currentIndex, bool isInLayout)
{
    if (isInLayout) {
        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([weak = WeakClaim(this), preIndex, currentIndex]() {
            auto eventHub = weak.Upgrade();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireJSChangeEvent(preIndex, currentIndex);
        });
    } else {
        FireJSChangeEvent(preIndex, currentIndex);
    }

    if (!changeEventsWithPreIndex_.empty()) {
        std::for_each(changeEventsWithPreIndex_.begin(), changeEventsWithPreIndex_.end(),
            [preIndex, currentIndex](const ChangeEventWithPreIndexPtr& changeEventWithPreIndex) {
                if (!changeEventWithPreIndex || !(*changeEventWithPreIndex)) {
                    return;
                }
                auto event = *changeEventWithPreIndex;
                event(preIndex, currentIndex);
            });
    }

    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        auto host = GetFrameNode();
        if (host) {
            auto id = host->GetInspectorIdValue("");
            builder.SetId(id)
                .SetType(host->GetHostTag())
                .SetDescription(host->GetAutoEventParamValue(""))
                .SetHost(host);
            if (!id.empty()) {
                Recorder::NodeDataCache::Get().PutInt(host, id, currentIndex);
            }
        }
        builder.SetIndex(currentIndex);
        Recorder::EventRecorder::Get().OnChange(std::move(builder));
    }
}

void SwiperEventHub::FireAnimationStartEvent(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_SWIPER,
        "FireAnimationStartEvent, index: %{public}d, targetIndex: %{public}d, id:%{public}d", index, targetIndex,
        swiperId_);
    ACE_SCOPED_TRACE(
        "Swiper FireAnimationStartEvent, index: %d, targetIndex %d, id: %d", index, targetIndex, swiperId_);
    if (!animationStartEvents_.empty()) {
        std::for_each(animationStartEvents_.begin(), animationStartEvents_.end(),
            [index, targetIndex, info](const AnimationStartEventPtr& animationStartEvent) {
                if (!animationStartEvent || !(*animationStartEvent)) {
                    return;
                }
                auto event = *animationStartEvent;
                event(index, targetIndex, info);
            });
    }
    // animationEnd callback need to be fired after animationStart callback, use flag for protection.
    ++aniStartCalledCount_;
    if (delayCallback_) {
        auto frameNode = GetFrameNode();
        TAG_LOGI(AceLogTag::ACE_SWIPER, "the timing of the animation callback has been corrected id:%{public}d",
            frameNode ? frameNode->GetId() : -1);
        delayCallback_();
        delayCallback_ = nullptr;
    }
}

void SwiperEventHub::FireAnimationEndEvent(int32_t index, const AnimationCallbackInfo& info)
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
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Swiper.onAnimationEnd");
    if (!animationEndEvents_.empty()) {
        std::for_each(animationEndEvents_.begin(), animationEndEvents_.end(),
            [index, info](const AnimationEndEventPtr& animationEndEvent) {
                if (!animationEndEvent || !(*animationEndEvent)) {
                    return;
                }
                auto event = *animationEndEvent;
                event(index, info);
            });
    }
    --aniStartCalledCount_;
}

void SwiperEventHub::FireAnimationEndOnForceEvent(int32_t index, const AnimationCallbackInfo& info)
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
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Swiper.onAnimationEnd");
    if (animationEndEvents_.empty()) {
        --aniStartCalledCount_;
        return;
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->AddBuildFinishCallBack([this, index, info]() {
        std::for_each(animationEndEvents_.begin(), animationEndEvents_.end(),
            [index, info](const AnimationEndEventPtr& animationEndEvent) {
                if (!animationEndEvent || !(*animationEndEvent)) {
                    return;
                }
                auto event = *animationEndEvent;
                event(index, info);
            });
    });
    --aniStartCalledCount_;
}

void SwiperEventHub::FireGestureSwipeEvent(int32_t index, const AnimationCallbackInfo& info) const
{
    if (gestureSwipeEvent_) {
        // gestureSwipeEvent_ may be overwrite in its invoke, so copy it first
        auto event = gestureSwipeEvent_;
        event(index, info);
    }
}

void SwiperEventHub::FireSelectedEvent(int32_t index)
{
    auto frameNode = GetFrameNode();
    ACE_SCOPED_TRACE("Swiper FireSelectedEvent, id: %d, index: %d", frameNode ? frameNode->GetId() : -1, index);
    if (!selectedEvents_.empty()) {
        std::for_each(selectedEvents_.begin(), selectedEvents_.end(), [index](const ChangeEventPtr& changeEvent) {
            if (!changeEvent || !(*changeEvent)) {
                return;
            }
            auto event = *changeEvent;
            event(index);
        });
    }
}

void SwiperEventHub::FireJSChangeEvent(int32_t preIndex, int32_t index)
{
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Swiper.onChange");
    auto frameNode = GetFrameNode();
    ACE_SCOPED_TRACE("Swiper FireChangeEvent, id: %d, preIndex: %d, index: %d", frameNode ? frameNode->GetId() : -1,
        preIndex, index);
    NotifySwiperObserver(frameNode, index);
    if (changeEvents_.empty()) {
        return;
    }
    std::for_each(changeEvents_.begin(), changeEvents_.end(), [index](const ChangeEventPtr& changeEvent) {
        if (!changeEvent || !(*changeEvent)) {
            return;
        }
        auto event = *changeEvent;
        event(index);
    });
}

void SwiperEventHub::NotifySwiperObserver(const RefPtr<FrameNode>& hostNode, int32_t index)
{
    if (UIObserverHandler::GetInstance().IsSwiperContentObserverEmpty()) {
        return;
    }
    CHECK_NULL_VOID(hostNode);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (!swiperPattern->IsPureSwiper()) {
        return;
    }
    SwiperContentInfo info;
    info.id = hostNode->GetInspectorId().value_or("");
    info.uniqueId = hostNode->GetId();
    info.swiperItemInfos = swiperPattern->GetShownItemInfoFromIndex(index);
    UIObserverHandler::GetInstance().NotifySwiperContentUpdate(info);
}
} // namespace