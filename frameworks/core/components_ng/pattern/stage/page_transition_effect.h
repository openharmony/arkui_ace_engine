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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_EFFECT_H

#include <memory>
#include <optional>

#include "core/animation/page_transition_common.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::NG {
using PageTransitionEventFunc = std::function<void(RouteType, const float&)>;

class PageTransitionEffect : public AceType {
    DECLARE_ACE_TYPE(PageTransitionEffect, AceType);

public:
    PageTransitionEffect(PageTransitionType type, const PageTransitionOption& option)
        : animationOption_(option), type_(type)
    {}
    ~PageTransitionEffect() override = default;

    void SetPageTransitionOption(const PageTransitionOption& animationOption)
    {
        animationOption_ = animationOption;
    }

    void SetTranslateEffect(const TranslateOptions& translate)
    {
        translate_ = translate;
    }

    const std::optional<TranslateOptions>& GetTranslateEffect() const
    {
        return translate_;
    }

    void SetSlideEffect(const SlideEffect& slide)
    {
        slide_ = slide;
    }

    void SetUserCallback(PageTransitionEventFunc&& callback)
    {
        userCallback_ = callback;
    }

    const std::optional<SlideEffect>& GetSlideEffect() const
    {
        return slide_;
    }

    void SetScaleEffect(const ScaleOptions& scale)
    {
        scale_ = scale;
    }

    const std::optional<ScaleOptions>& GetScaleEffect() const
    {
        return scale_;
    }

    void SetOpacityEffect(float opacity)
    {
        opacity_ = opacity;
    }

    const std::optional<float>& GetOpacityEffect() const
    {
        return opacity_;
    }

    void SetPageTransitionRectF(const RectF& pageTransitionRectF)
    {
        pageTransitionRectF_ = pageTransitionRectF;
    }

    const std::optional<RectF>& GetPageTransitionRectF() const
    {
        return pageTransitionRectF_;
    }

    void SetDefaultPageTransitionRectF(const RectF& defaultPageTransitionRectF)
    {
        defaultPageTransitionRectF_ = defaultPageTransitionRectF;
    }

    const std::optional<RectF>& GetDefaultPageTransitionRectF() const
    {
        return defaultPageTransitionRectF_;
    }

    void SetInitialBackgroundColor(const Color& initialBackgroundColor)
    {
        initialBackgroundColor_ = initialBackgroundColor;
    }

    const std::optional<Color>& GetInitialBackgroundColor() const
    {
        return initialBackgroundColor_;
    }

    void SetBackgroundColor(const Color& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }

    const std::optional<Color>& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    // test whether this effect can match the pageTransitionType
    bool CanFit(PageTransitionType type) const
    {
        switch (type) {
            case PageTransitionType::ENTER_PUSH:
                return type_ == PageTransitionType::ENTER && animationOption_.routeType != RouteType::POP;
            case PageTransitionType::ENTER_POP:
                return type_ == PageTransitionType::ENTER && animationOption_.routeType != RouteType::PUSH;
            case PageTransitionType::EXIT_PUSH:
                return type_ == PageTransitionType::EXIT && animationOption_.routeType != RouteType::POP;
            case PageTransitionType::EXIT_POP:
                return type_ == PageTransitionType::EXIT && animationOption_.routeType != RouteType::PUSH;
            default:
                return false;
        }
    }

    int32_t GetDuration() const
    {
        return animationOption_.duration;
    }

    int32_t GetDelay() const
    {
        return animationOption_.delay;
    }

    const RefPtr<Curve>& GetCurve() const
    {
        return animationOption_.curve;
    }

    const PageTransitionEventFunc& GetUserCallback() const
    {
        return userCallback_;
    }

    PageTransitionType GetPageTransitionType() const
    {
        return type_;
    }

    PageTransitionOption GetPageTransitionOption() const
    {
        return animationOption_;
    }

private:
    std::optional<TranslateOptions> translate_;
    std::optional<ScaleOptions> scale_;
    std::optional<SlideEffect> slide_;
    std::optional<float> opacity_;
    std::optional<RectF> pageTransitionRectF_;
    std::optional<RectF> defaultPageTransitionRectF_;
    std::optional<Color> initialBackgroundColor_;
    std::optional<Color> backgroundColor_;
    PageTransitionOption animationOption_;
    // user defined onEnter or onExit callback;
    PageTransitionEventFunc userCallback_;
    PageTransitionType type_ = PageTransitionType::ENTER;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_TRANSITION_EFFECT_H
