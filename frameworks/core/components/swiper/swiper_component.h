/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_COMPONENT_H

#include "base/utils/macros.h"
#include "core/components/common/properties/swiper_indicator.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components/swiper/swiper_element.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

inline constexpr uint32_t DEFAULT_SWIPER_CURRENT_INDEX = 0;
inline constexpr double DEFAULT_SWIPER_ANIMATION_DURATION = 400.0;
inline constexpr double DEFAULT_SWIPER_AUTOPLAY_INTERVAL = 3000.0;

using SwipeToImpl = std::function<void(const int32_t, bool)>;
using SwiperChangeEndListener = std::function<void(int32_t)>;
using ShowPrevImpl = std::function<void()>;
using ShowNextImpl = std::function<void()>;

class SwiperController : public virtual AceType {
    DECLARE_ACE_TYPE(SwiperController, AceType);

public:
    void SwipeTo(int32_t index, bool reverse = false)
    {
        if (swipeToImpl_) {
            swipeToImpl_(index, reverse);
        }
    }

    void SetSwipeToImpl(const SwipeToImpl& swipeToImpl)
    {
        swipeToImpl_ = swipeToImpl;
    }

    void ShowPrevious()
    {
        if (showPrevImpl_) {
            showPrevImpl_();
        }
    }

    void SetShowPrevImpl(const ShowPrevImpl& showPrevImpl)
    {
        showPrevImpl_ = showPrevImpl;
    }

    void ShowNext()
    {
        if (showNextImpl_) {
            showNextImpl_();
        }
    }

    void SetShowNextImpl(const ShowNextImpl& showNextImpl)
    {
        showNextImpl_ = showNextImpl;
    }

private:
    SwipeToImpl swipeToImpl_;
    ShowPrevImpl showPrevImpl_;
    ShowNextImpl showNextImpl_;
};

class ACE_EXPORT SwiperComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(SwiperComponent, ComponentGroup);

public:
    explicit SwiperComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children)
    {
        swiperController_ = AceType::MakeRefPtr<SwiperController>();
        rotationController_ = AceType::MakeRefPtr<RotationController>();
    };
    SwiperComponent(const std::list<RefPtr<Component>>& children, bool showIndicator) : ComponentGroup(children)
    {
        if (showIndicator) {
            indicator_ = AceType::MakeRefPtr<SwiperIndicator>();
        }
        swiperController_ = AceType::MakeRefPtr<SwiperController>();
        rotationController_ = AceType::MakeRefPtr<RotationController>();
    };
    ~SwiperComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderSwiper::Create();
    }

    RefPtr<Element> CreateElement() override
    {
        return AceType::MakeRefPtr<SwiperElement>();
    }

    uint32_t GetIndex() const
    {
        return index_;
    }
    void SetIndex(uint32_t index)
    {
        index_ = index;
    }

    Axis GetAxis() const
    {
        return axis_;
    }
    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    bool IsLoop() const
    {
        return loop_;
    }
    void SetLoop(bool loop)
    {
        loop_ = loop;
    }

    bool IsAutoPlay() const
    {
        return autoPlay_;
    }
    void SetAutoPlay(bool autoPlay)
    {
        autoPlay_ = autoPlay;
    }

    bool IsShow() const
    {
        return show_;
    }
    void SetShow(bool show)
    {
        show_ = show;
    }

    double GetAutoPlayInterval() const
    {
        return autoPlayInterval_;
    }
    void SetAutoPlayInterval(double autoPlayInterval)
    {
        autoPlayInterval_ = autoPlayInterval;
    }

    void SetChangeEventId(const EventMarker& changeEventId)
    {
        changeEventId_ = changeEventId;
    }
    const EventMarker& GetChangeEventId() const
    {
        return changeEventId_;
    }

    const EventMarker& GetRotationEventId() const
    {
        return rotationEventId_;
    }
    void SetRotationEventId(const EventMarker& rotationEventId)
    {
        rotationEventId_ = rotationEventId;
    }

    const EventMarker& GetClickEventId() const
    {
        return clickEventId_;
    }
    void SetClickEventId(const EventMarker& clickEventId)
    {
        clickEventId_ = clickEventId;
    }

    void SetDuration(double duration)
    {
        duration_ = duration;
    }
    double GetDuration() const
    {
        return duration_;
    }

    RefPtr<SwiperIndicator> GetIndicator() const
    {
        return indicator_;
    }
    void SetIndicator(const RefPtr<SwiperIndicator>& indicator)
    {
        indicator_ = indicator;
    }
    void SetIndicatorColor(const Color& color)
    {
        if (indicator_) {
            indicator_->SetColor(color);
        }
    }
    void SetIndicatorSelectedColor(const Color& selectedColor)
    {
        if (indicator_) {
            indicator_->SetSelectedColor(selectedColor);
        }
    }

    void SetIndicatorSize(const Dimension& size)
    {
        if (indicator_) {
            indicator_->SetSize(size);
        }
    }

    void SetIndicatorSelectedSize(const Dimension& selectedSize)
    {
        if (indicator_) {
            indicator_->SetSelectedSize(selectedSize);
        }
    }

    void SetIndicatorTop(const Dimension& top)
    {
        if (indicator_) {
            indicator_->SetTop(top);
        }
    }

    void SetIndicatorLeft(const Dimension& left)
    {
        if (indicator_) {
            indicator_->SetLeft(left);
        }
    }

    void SetIndicatorBottom(const Dimension& bottom)
    {
        if (indicator_) {
            indicator_->SetBottom(bottom);
        }
    }

    void SetIndicatorRight(const Dimension& right)
    {
        if (indicator_) {
            indicator_->SetRight(right);
        }
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    const RefPtr<RotationController>& GetRotationController() const
    {
        return rotationController_;
    }

    const SwiperChangeEndListener& GetChangeEndListener() const
    {
        return changeEndListener_;
    }

    void SetChangeEndListener(const SwiperChangeEndListener& changeEndListener)
    {
        changeEndListener_ = changeEndListener;
    }

    void SetDigitalIndicator(bool digitalIndicator)
    {
        digitalIndicator_ = digitalIndicator;
    }

    bool GetDigitalIndicator() const
    {
        return digitalIndicator_;
    }

    void SetMoveCallback(const MoveCallback& moveCallback)
    {
        moveCallback_ = moveCallback;
    }

    const MoveCallback& GetMoveCallback() const
    {
        return moveCallback_;
    }

    void SetSlideContinue(bool slideContinued)
    {
        slideContinued_ = slideContinued;
    }

    bool GetSlideContinue() const
    {
        return slideContinued_;
    }

    void DisableSwipe(bool disableSwipe)
    {
        disableSwipe_ = disableSwipe;
    }

    bool GetDisableSwipe() const
    {
        return disableSwipe_;
    }

    AnimationCurve GetAnimationCurve() const
    {
        return animationCurve_;
    }

    void SetAnimationCurve(AnimationCurve animationCurve)
    {
        animationCurve_ = animationCurve;
    }

    bool IsAnimationOpacity() const
    {
        return animationOpacity_;
    }

    void SetAnimationOpacity(bool animationOpacity)
    {
        animationOpacity_ = animationOpacity;
    }

private:
    uint32_t index_ { DEFAULT_SWIPER_CURRENT_INDEX };
    double duration_ { DEFAULT_SWIPER_ANIMATION_DURATION };
    EventMarker changeEventId_;
    EventMarker rotationEventId_;
    EventMarker clickEventId_;
    RefPtr<SwiperIndicator> indicator_;
    Axis axis_ { Axis::HORIZONTAL };
    bool loop_ { true };
    bool autoPlay_ { false };
    bool show_ { true };
    bool digitalIndicator_ { false };
    bool slideContinued_ { false };
    bool disableSwipe_ { false };
    bool animationOpacity_ { true };
    double autoPlayInterval_ { DEFAULT_SWIPER_AUTOPLAY_INTERVAL };
    RefPtr<SwiperController> swiperController_;
    RefPtr<RotationController> rotationController_;
    SwiperChangeEndListener changeEndListener_;
    MoveCallback moveCallback_;
    AnimationCurve animationCurve_ { AnimationCurve::FRICTION };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_COMPONENT_H
