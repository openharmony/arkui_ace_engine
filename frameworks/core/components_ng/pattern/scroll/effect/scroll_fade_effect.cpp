/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"

namespace OHOS::Ace::NG {
void ScrollFadeEffect::InitialEdgeEffect()
{
    ResetFadeEffect(fadeColor_);
}

void ScrollFadeEffect::ResetFadeEffect(const Color& color)
{
    fadeColor_ = color;
    if (!fadePainter_) {
        fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();
    }

    if (!fadeController_) {
        fadeController_ = AceType::MakeRefPtr<ScrollFadeController>();
        fadeController_->SetCallback([weakFade = AceType::WeakClaim(this)](double opacity, double scale) {
            auto fade = weakFade.Upgrade();
            if (fade) {
                fade->SetOpacityAndScale(opacity, scale);
            }
        });
    }
}

double ScrollFadeEffect::CalculateOverScroll(double oldPosition, bool isReachMax)
{
    if (!currentPositionCallback_ || !leadingCallback_ || !trailingCallback_) {
        return 0.0;
    }

    double newPosition = -currentPositionCallback_();
    double minExtent = -trailingCallback_();
    double maxExtent = -leadingCallback_();

    // under scroll
    if (newPosition < oldPosition && oldPosition <= minExtent) {
        return newPosition - oldPosition;
    }

    // over scroll
    if (newPosition > oldPosition && oldPosition >= maxExtent) {
        return newPosition - oldPosition;
    }

    // crash the top
    if (newPosition < minExtent && oldPosition > minExtent) {
        return newPosition;
    }

    // crash the bottom
    if (newPosition > maxExtent && maxExtent > oldPosition && isReachMax) {
        return newPosition - maxExtent;
    }

    return 0.0;
}

void ScrollFadeEffect::SetPaintDirection(Axis axis, float overScroll, bool isNotPositiveScrollableDistance)
{
    CHECK_NULL_VOID((!NearZero(overScroll)) && fadePainter_);
    auto const isVertical = axis == Axis::VERTICAL;
    auto scaleFactor = fadePainter_->GetScaleFactor();
    if (isNotPositiveScrollableDistance) {
        if (isVertical && Negative(overScroll)) {
            auto isOverScrollAtDown = fadePainter_->GetDirection() == OverScrollDirection::DOWN &&
                                      GreatOrEqual(scaleFactor, SCALE_THRESHOLD) &&
                                      LessOrEqual(std::abs(overScroll), OVER_SCROLL_THRESHOLD);
            CHECK_NULL_VOID(!isOverScrollAtDown);
            fadePainter_->SetDirection(OverScrollDirection::UP);
        } else if (isVertical && Positive(overScroll)) {
            auto isOverScrollAtUp = fadePainter_->GetDirection() == OverScrollDirection::UP &&
                                    GreatOrEqual(scaleFactor, SCALE_THRESHOLD) &&
                                    LessOrEqual(overScroll, OVER_SCROLL_THRESHOLD);
            CHECK_NULL_VOID(!isOverScrollAtUp);
            fadePainter_->SetDirection(OverScrollDirection::DOWN);
        } else if (Negative(overScroll)) {
            auto isOverScrollAtRight = fadePainter_->GetDirection() == OverScrollDirection::RIGHT &&
                                       GreatOrEqual(scaleFactor, SCALE_THRESHOLD) &&
                                       LessOrEqual(std::abs(overScroll), OVER_SCROLL_THRESHOLD);
            CHECK_NULL_VOID(!isOverScrollAtRight);
            fadePainter_->SetDirection(OverScrollDirection::LEFT);
        } else {
            auto isOverScrollAtLeft = fadePainter_->GetDirection() == OverScrollDirection::LEFT &&
                                      GreatOrEqual(scaleFactor, SCALE_THRESHOLD) &&
                                      LessOrEqual(overScroll, OVER_SCROLL_THRESHOLD);
            CHECK_NULL_VOID(!isOverScrollAtLeft);
            fadePainter_->SetDirection(OverScrollDirection::RIGHT);
        }
    } else {
        if (isVertical && Negative(overScroll)) {
            fadePainter_->SetDirection(OverScrollDirection::UP);
        } else if (isVertical && Positive(overScroll)) {
            fadePainter_->SetDirection(OverScrollDirection::DOWN);
        } else if (Negative(overScroll)) {
            fadePainter_->SetDirection(OverScrollDirection::LEFT);
        } else {
            fadePainter_->SetDirection(OverScrollDirection::RIGHT);
        }
    }
}

void ScrollFadeEffect::Paint(RSCanvas& canvas, const SizeF& viewPort, const OffsetF& offset)
{
    if (fadePainter_) {
        fadePainter_->SetColor(fadeColor_);
        fadePainter_->PaintSide(canvas, viewPort, offset);
    }
}

void ScrollFadeEffect::HandleOverScroll(Axis axis, float overScroll, const SizeF& viewPort,
    bool isScrollFromUpdate, bool isNotPositiveScrollableDistance)
{
    if (NearZero(overScroll)) {
        return;
    }

    SetPaintDirection(axis, overScroll, isNotPositiveScrollableDistance);

    if (!fadeController_) {
        fadeController_ = AceType::MakeRefPtr<ScrollFadeController>();
        fadeController_->SetCallback([weakFade = AceType::WeakClaim(this)](double opacity, double scale) {
            auto fade = weakFade.Upgrade();
            if (fade) {
                fade->SetOpacityAndScale(opacity, scale);
            }
        });
    }

    if (fadeController_ && scrollable_) {
        if (!isScrollFromUpdate) {
            fadeController_->ProcessAbsorb(std::abs(scrollable_->GetCurrentVelocity()));
        } else {
            axis == Axis::VERTICAL
                ? fadeController_->ProcessPull(std::abs(overScroll), viewPort.Height(), viewPort.Width())
                : fadeController_->ProcessPull(std::abs(overScroll), viewPort.Width(), viewPort.Height());
        }
    }
}

void ScrollFadeEffect::SetOpacityAndScale(float opacity, float scale)
{
    if (fadePainter_) {
        fadePainter_->SetOpacity(opacity);
        fadePainter_->SetScaleFactor(scale);

        if (handleOverScrollCallback_) {
            handleOverScrollCallback_();
        }
    }
}

void ScrollFadeEffect::SetHandleOverScrollCallback(const HandleOverScrollCallback& callback)
{
    handleOverScrollCallback_ = callback;
}
} // namespace OHOS::Ace::NG