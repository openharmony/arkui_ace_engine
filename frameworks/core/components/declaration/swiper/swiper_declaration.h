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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SWIPER_SWIPER_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SWIPER_SWIPER_DECLARATION_H

#include "core/components/common/properties/swiper_indicator.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components/swiper/swiper_controller.h"
#include "frameworks/core/components/common/rotation/rotation_controller.h"

namespace OHOS::Ace {

inline constexpr uint32_t DEFAULT_SWIPER_CURRENT_INDEX = 0;
inline constexpr double DEFAULT_SWIPER_ANIMATION_DURATION = 400.0;
inline constexpr double DEFAULT_SWIPER_AUTOPLAY_INTERVAL = 3000.0;

struct SwiperAttribute : Attribute {
    uint32_t index = DEFAULT_SWIPER_CURRENT_INDEX;
    double duration = DEFAULT_SWIPER_ANIMATION_DURATION;
    Axis axis = Axis::HORIZONTAL;
    bool loop = true;
    bool autoPlay = false;
    bool animationOpacity = true;
    bool digitalIndicator = false;
    double autoPlayInterval = DEFAULT_SWIPER_AUTOPLAY_INTERVAL;
};

struct SwiperStyle : Style {
    AnimationCurve animationCurve { AnimationCurve::FRICTION };
};

struct SwiperEvent : Event {
    EventMarker changeEventId;
    EventMarker rotationEventId;
    EventMarker clickEventId;
};

struct SwiperMethod : Method {};

class SwiperDeclaration : public Declaration {
    DECLARE_ACE_TYPE(SwiperDeclaration, Declaration);

public:
    SwiperDeclaration();
    ~SwiperDeclaration() override = default;

    void InitializeStyle() override;
    uint32_t GetIndex() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.index;
    }
    void SetIndex(uint32_t index)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.index = index;
    }

    double GetDuration() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.duration;
    }
    void SetDuration(double duration)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.duration = duration;
    }

    Axis GetAxis() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.axis;
    }
    void SetAxis(Axis axis)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.axis = axis;
    }

    bool IsLoop() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.loop;
    }
    void SetLoop(bool loop)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.loop = loop;
    }

    bool IsAutoPlay() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.autoPlay;
    }
    void SetAutoPlay(bool autoPlay)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.autoPlay = autoPlay;
    }

    double GetAutoPlayInterval() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.autoPlayInterval;
    }
    void SetAutoPlayInterval(double autoPlayInterval)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.autoPlayInterval = autoPlayInterval;
    }

    bool IsAnimationOpacity() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.animationOpacity;
    }
    void SetAnimationOpacity(bool animationOpacity)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.animationOpacity = animationOpacity;
    }

    bool GetDigitalIndicator() const
    {
        auto& attribute = static_cast<SwiperAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.digitalIndicator;
    }
    void SetDigitalIndicator(bool digitalIndicator)
    {
        auto& attribute = MaybeResetAttribute<SwiperAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.digitalIndicator = digitalIndicator;
    }

    AnimationCurve GetAnimationCurve() const
    {
        auto& style = static_cast<SwiperStyle&>(GetStyle(StyleTag::SPECIALIZED_STYLE));
        return style.animationCurve;
    }
    void SetAnimationCurve(AnimationCurve animationCurve)
    {
        auto& style = MaybeResetStyle<SwiperStyle>(StyleTag::SPECIALIZED_STYLE);
        style.animationCurve = animationCurve;
    }

    const EventMarker& GetChangeEventId() const
    {
        auto& event = static_cast<SwiperEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.changeEventId;
    }
    void SetChangeEventId(const EventMarker& changeEventId)
    {
        auto& event = MaybeResetEvent<SwiperEvent>(EventTag::SPECIALIZED_EVENT);
        event.changeEventId = changeEventId;
    }

    const EventMarker& GetRotationEventId() const
    {
        auto& event = static_cast<SwiperEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.rotationEventId;
    }
    void SetRotationEventId(const EventMarker& rotationEventId)
    {
        auto& event = MaybeResetEvent<SwiperEvent>(EventTag::SPECIALIZED_EVENT);
        event.rotationEventId = rotationEventId;
    }

    const EventMarker& GetClickEventId() const
    {
        auto& event = static_cast<SwiperEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.clickEventId;
    }

    void SetClickEventId(const EventMarker& clickEventId)
    {
        auto& event = MaybeResetEvent<SwiperEvent>(EventTag::SPECIALIZED_EVENT);
        event.clickEventId = clickEventId;
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    const RefPtr<RotationController>& GetRotationController() const
    {
        return rotationController_;
    }

    bool IsShowIndicator() const
    {
        return showIndicator_;
    }
    void SetShowIndicator(bool showIndicator)
    {
        showIndicator_ = showIndicator;
    }
    const RefPtr<SwiperIndicator>& GetIndicator() const
    {
        return indicator_;
    }
    void SetIndicator(const RefPtr<SwiperIndicator>& indicator)
    {
        indicator_ = indicator;
    }

protected:
    void InitSpecialized() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    bool SetSpecializedEvent(int32_t pageId, const std::string& eventId, const std::string& event) override;
    void CallSpecializedMethod(const std::string& method, const std::string& args) override;

private:
    bool showIndicator_ = true;
    RefPtr<SwiperIndicator> indicator_;
    RefPtr<SwiperController> swiperController_;
    RefPtr<RotationController> rotationController_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SWIPER_SWIPER_DECLARATION_H
