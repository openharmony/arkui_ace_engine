/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_modifier.h"

#include "base/utils/utils.h"
#include "core/animation/spring_curve.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HOVER_ANIMATION_DURATION = 100;
constexpr int32_t SPRING_ANIMATION_DURATION = 400;
} // namespace

void SwiperIndicatorModifier::onDraw(DrawingContext& context)
{
    ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX_->Get();
    contentProperty.longPointLeftCenterX = longPointLeftCenterX_->Get();
    contentProperty.longPointRightCenterX = longPointRightCenterX_->Get();
    contentProperty.centerY = centerY_->Get();
    contentProperty.pointRadius = pointRadius_->Get();
    contentProperty.hoverPointRadius = hoverPointRadius_->Get();
    if (indicatorMask_) {
        PaintMask(context);
    }
    PaintContent(context, contentProperty);
}

void SwiperIndicatorModifier::PaintContent(DrawingContext& context, ContentProperty& contentProperty)
{
    RSCanvas canvas = context.canvas;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    for (size_t i = 0; i < contentProperty.vectorBlackPointCenterX.size(); ++i) {
        OffsetF center = { contentProperty.vectorBlackPointCenterX[i], contentProperty.centerY };
        float radius = isHoverPoint(center, center, contentProperty.pointRadius) ? contentProperty.hoverPointRadius
                                                                                 : contentProperty.pointRadius;
        PaintUnselectedIndicator(canvas, center, radius);
    }
    OffsetF leftCenter = { contentProperty.longPointLeftCenterX, contentProperty.centerY };
    OffsetF rightCenter = { contentProperty.longPointRightCenterX, contentProperty.centerY };
    float radius = isHoverPoint(leftCenter, rightCenter, contentProperty.pointRadius) ? contentProperty.hoverPointRadius
                                                                                      : contentProperty.pointRadius;
    PaintSelectedIndicator(canvas, leftCenter, rightCenter, radius);
}

void SwiperIndicatorModifier::PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center, float radius)
{
    RSBrush brush;
    brush.SetColor(ToRSColor(unselectedColor_));
    canvas.AttachBrush(brush);
    float pointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
    float pointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
    canvas.DrawCircle({ pointX, pointY }, radius);
}

void SwiperIndicatorModifier::PaintSelectedIndicator(
    RSCanvas& canvas, const OffsetF& leftCenter, const OffsetF& rightCenter, float radius)
{
    RSBrush brush;
    brush.SetColor(ToRSColor(selectedColor_));
    canvas.AttachBrush(brush);
    float rectLeft = (axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY()) - radius;
    float rectTop = (axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX()) - radius;
    float rectRight = (axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY()) + radius;
    float rectBottom = (axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX()) + radius;
    canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, radius, radius });
}

bool SwiperIndicatorModifier::isHoverPoint(const OffsetF& leftCenter, const OffsetF& rightCenter, float radius)
{
    CHECK_NULL_RETURN_NOLOG(hoverPoint_, false);
    float tempLeftCenterX = axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY();
    float tempLeftCenterY = axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX();
    float tempRightCenterX = axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY();
    float tempRightCenterY = axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX();
    return hoverPoint_->GetX() >= (tempLeftCenterX - radius) && hoverPoint_->GetX() <= (tempRightCenterX + radius) &&
           hoverPoint_->GetY() >= (tempLeftCenterY - radius) && hoverPoint_->GetY() <= (tempRightCenterY + radius);
}

void SwiperIndicatorModifier::PaintMask(DrawingContext& context)
{
    RSCanvas canvas = context.canvas;

    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.Save();

    std::vector<RSColorQuad> colors;
    colors.push_back(0x00000000);
    colors.push_back(0xff000000);
    colors.push_back(0xff000000);

    RSPoint startPt = { offset_.GetX(), offset_.GetY() };
    RSPoint endPt = { offset_.GetX(), offset_.GetY() };
    startPt -= axis_ == Axis::HORIZONTAL ? RSPoint(0, (9.0_vp).ConvertToPx()) : RSPoint((9.0_vp).ConvertToPx(), 0);
    endPt += axis_ == Axis::HORIZONTAL ? RSPoint(0, (15.0_vp).ConvertToPx()) : RSPoint((15.0_vp).ConvertToPx(), 0);

    std::vector<float> pos = { 0.0f, 0.75f, 1.0f };

    brush.SetShaderEffect(RSShaderEffect::CreateLinearGradient(startPt, endPt, colors, pos, RSTileMode::CLAMP));
    canvas.DrawRect({ startPt.GetX(), startPt.GetY(), endPt.GetX(), endPt.GetY() });
}

void SwiperIndicatorModifier::UpdateVectorBlackPointCenterX(const LinearVector<float>& vectorBlackPointCenterX)
{
    vectorBlackPointCenterX_->Set(vectorBlackPointCenterX);
}

void SwiperIndicatorModifier::UpdateLongPointLeftCenterX(float longPointLeftCenterX, bool isAnimation)
{
    longPointLeftCenterX_->Set(longPointLeftCenterX);
    if (isAnimation) {
        AnimationOption option = AnimationOption();
        option.SetDuration(SPRING_ANIMATION_DURATION);
        option.SetCurve(AceType::MakeRefPtr<CubicCurve>(100, 1, 228, 20));
        AnimationUtils::Animate(option, [&]() { longPointLeftCenterX_->Set(longPointLeftCenterX); });
    }
}

void SwiperIndicatorModifier::UpdateLongPointRightCenterX(float longPointRightCenterX, bool isAnimation)
{
    longPointRightCenterX_->Set(longPointRightCenterX);
    if (isAnimation) {
        AnimationOption option = AnimationOption();
        option.SetDuration(SPRING_ANIMATION_DURATION);
        option.SetCurve(AceType::MakeRefPtr<CubicCurve>(100, 1, 228, 20));
        AnimationUtils::Animate(option, [&]() { longPointRightCenterX_->Set(longPointRightCenterX); });
    }
}

void SwiperIndicatorModifier::UpdateCenterY(float centerY)
{
    centerY_->Set(centerY);
}

void SwiperIndicatorModifier::UpdatePointRadius(float pointRadius)
{
    pointRadius_->Set(pointRadius);
}

void SwiperIndicatorModifier::UpdateHoverPointRadius(float startHoverPointRadius, float endHoverPointRadius)
{
    hoverPointRadius_->Set(startHoverPointRadius);
    AnimationOption option = AnimationOption();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() { hoverPointRadius_->Set(endHoverPointRadius); });
}
} // namespace OHOS::Ace::NG
