/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/focus_animation_modifier.h"

#include <cmath>
#include <tuple>

#include "base/log/log_wrapper.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TRAJECTORY_DATA_CNT = 8;
constexpr int32_t TOP_SIDE = 0;
constexpr int32_t TOP_RIGHT = 1;
constexpr int32_t RIGHT_SIDE = 2;
constexpr int32_t BOTTOM_RIGHT = 3;
constexpr int32_t BOTTOM_SIDE = 4;
constexpr int32_t BOTTOM_LEFT = 5;
constexpr int32_t LEFT_SIDE = 6;
constexpr int32_t TOP_LEFT = 7;
constexpr float LEFTEDGE_START_PERCENT = 0.0f;
constexpr float MIDLOWEDGE_START_PERCENT = 0.1f;
constexpr float RIGHTLOWEDGE_START_PERCENT = 0.9f;
constexpr float RIGHTEDGE_END_PERCENT = 1.0f;
constexpr uint32_t ILLUMUNATEDTYPE_BORDER = 1;
constexpr uint32_t ILLUMUNATEDTYPE_CONTENT = 2;
constexpr float PERCENT_GLOW_LINE = 0.8f;
constexpr float RISING_SLOPE = (153.0f - 25.5f) / 360.0f;
constexpr float RISING_CONSTANT = 25.5f;
constexpr float DESECEND_SLOPE = (25.5f - 153.0f) / 360.0f;
constexpr float DESECEND_CONSTANT = 153.0f;
constexpr float CORNER_LEN_CONSTANT = 0.25f;
constexpr uint32_t ANIMATION_DURATION = 3000;
} // namespace

FocusAnimationModifier::FocusAnimationModifier()
    : focusProcessFloat_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f))
{
    AttachProperty(focusProcessFloat_);
    InitTrajectDataFunc();
}

void FocusAnimationModifier::InitTrajectDataFunc()
{
    CHECK_NULL_VOID(&roundRect_);
    trajectDataFunc_[TOP_SIDE] = [this](float current, float compeleted) -> std::tuple<float, float> {
        return std::make_tuple(topLeftX_ + current, 0);
    };
    trajectDataFunc_[TOP_RIGHT] = [this](float current, float compeleted) -> std::tuple<float, float> {
        float radius = (topRightX_ + topRightY_) / 2;
        float angle = CalArcAngle(radius, current - compeleted);
        return std::make_tuple(
            roundRect_.GetRect().GetWidth() - radius * (1 - std::sin(angle)), radius * (1 - std::cos(angle)));
    };
    trajectDataFunc_[RIGHT_SIDE] = [this](float current, float compeleted) -> std::tuple<float, float> {
        return std::make_tuple(roundRect_.GetRect().GetWidth(), current - compeleted + topRightY_);
    };
    trajectDataFunc_[BOTTOM_RIGHT] = [this](float current, float compeleted) -> std::tuple<float, float> {
        float radius = (bottomRightX_ + bottomRightY_) / 2;
        float angle = CalArcAngle(radius, current - compeleted);
        return std::make_tuple(roundRect_.GetRect().GetWidth() - radius * (1 - std::cos(angle)),
            roundRect_.GetRect().GetHeight() - radius * (1 - std::sin(angle)));
    };
    trajectDataFunc_[BOTTOM_SIDE] = [this](float current, float compeleted) -> std::tuple<float, float> {
        return std::make_tuple(
            roundRect_.GetRect().GetWidth() - bottomRightX_ - (current - compeleted), roundRect_.GetRect().GetHeight());
    };
    trajectDataFunc_[BOTTOM_LEFT] = [this](float current, float compeleted) -> std::tuple<float, float> {
        float radius = (bottomLeftX_ + bottomLeftY_) / 2;
        float angle = CalArcAngle(radius, current - compeleted);
        return std::make_tuple(
            radius * (1 - std::sin(angle)), roundRect_.GetRect().GetHeight() - radius * (1 - std::cos(angle)));
    };
    trajectDataFunc_[LEFT_SIDE] = [this](float current, float compeleted) -> std::tuple<float, float> {
        return std::make_tuple(0.0f, roundRect_.GetRect().GetHeight() - bottomRightY_ - (current - compeleted));
    };
    trajectDataFunc_[TOP_LEFT] = [this](float current, float compeleted) -> std::tuple<float, float> {
        float radius = (topLeftX_ + topLeftY_) / 2;
        float angle = CalArcAngle(radius, current - compeleted);
        return std::make_tuple(radius * (1 - std::cos(angle)), radius * (1 - std::sin(angle)));
    };
}

void FocusAnimationModifier::InitTrajectoryData(const RSRoundRect& rrect)
{
    CHECK_NULL_VOID(&rrect);
    auto rect = rrect.GetRect();
    CHECK_NULL_VOID(&rect);
    float width = rect.GetWidth();
    float height = rect.GetHeight();
    longerSide_ = std::max(width, height);
    shorterSide_ = std::min(width, height);
    CheckBoxStyle checkBoxStyle = CheckBoxStyle::CIRCULAR_STYLE;
    checkBoxStyle = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? CheckBoxStyle::CIRCULAR_STYLE
                                                                                       : CheckBoxStyle::SQUARE_STYLE;
    auto delegatePtr = weakFrameNode_.Upgrade();
    CHECK_NULL_VOID(delegatePtr);
    auto paintProperty = delegatePtr->GetPaintProperty<CheckBoxPaintProperty>();
    if (paintProperty && paintProperty->HasCheckBoxSelectedStyle()) {
        checkBoxStyle = paintProperty->GetCheckBoxSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE);
    }
    if (!delegatePtr->GetCheckboxFlag() || CheckBoxStyle::SQUARE_STYLE == checkBoxStyle) {
        InitRoundRectTrajectory(rrect);
        return;
    }
    InitCircleTrajectory(shorterSide_ / 2.0f);
}

void FocusAnimationModifier::InitRoundRectTrajectory(const RSRoundRect& rrect)
{
    auto rect = rrect.GetRect();
    CHECK_NULL_VOID(&rect);
    float width = rect.GetWidth();
    float height = rect.GetHeight();
    float halfShorterSide = shorterSide_ / 2.0f;
    topLeftX_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::TOP_LEFT_POS).GetX());
    topLeftY_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::TOP_LEFT_POS).GetY());
    topRightX_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::TOP_RIGHT_POS).GetX());
    topRightY_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::TOP_RIGHT_POS).GetY());
    bottomLeftX_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::BOTTOM_LEFT_POS).GetX());
    bottomLeftY_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::BOTTOM_LEFT_POS).GetY());
    bottomRightX_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS).GetX());
    bottomRightY_ = std::min(halfShorterSide, rrect.GetCornerRadius(RSRoundRect::CornerPos::BOTTOM_RIGHT_POS).GetY());
    float topSide = std::max(0.0f, width - topLeftX_ - topRightX_);
    float leftSide = std::max(0.0f, height - topLeftY_ - bottomLeftY_);
    float rightSide = std::max(0.0f, height - topRightY_ - bottomRightY_);
    float bottomSide = std::max(0.0f, width - bottomLeftX_ - bottomRightX_);
    float topLeftArc = CalArcLen((topLeftX_ + topLeftY_) / 2.0f);
    float topRightArc = CalArcLen((topRightX_ + topRightY_) / 2.0f);
    float bottomLeftArc = CalArcLen((bottomLeftX_ + bottomLeftY_) / 2.0f);
    float bottomRightArc = CalArcLen((bottomRightX_ + bottomRightY_) / 2.0f);
    grith_ = topSide + bottomSide + rightSide + leftSide + topLeftArc + topRightArc + bottomRightArc + bottomLeftArc;
    trajectoryData_[TOP_SIDE] = topSide;
    trajectoryData_[TOP_RIGHT] = topRightArc;
    trajectoryData_[RIGHT_SIDE] = rightSide;
    trajectoryData_[BOTTOM_RIGHT] = bottomRightArc;
    trajectoryData_[BOTTOM_SIDE] = bottomSide;
    trajectoryData_[BOTTOM_LEFT] = bottomLeftArc;
    trajectoryData_[LEFT_SIDE] = leftSide;
    trajectoryData_[TOP_LEFT] = topLeftArc;
}

void FocusAnimationModifier::InitCircleTrajectory(float radius)
{
    grith_ = 2.0f * M_PI * radius;
    topLeftX_ = radius;
    topLeftY_ = radius;
    topRightX_ = radius;
    topRightY_ = radius;
    bottomLeftX_ = radius;
    bottomLeftY_ = radius;
    bottomRightX_ = radius;
    bottomRightY_ = radius;
    trajectoryData_[TOP_SIDE] = 0.0f;
    trajectoryData_[TOP_RIGHT] = CORNER_LEN_CONSTANT * grith_;
    trajectoryData_[RIGHT_SIDE] = 0.0f;
    trajectoryData_[BOTTOM_RIGHT] = CORNER_LEN_CONSTANT * grith_;
    trajectoryData_[BOTTOM_SIDE] = 0.0f;
    trajectoryData_[BOTTOM_LEFT] = CORNER_LEN_CONSTANT * grith_;
    trajectoryData_[LEFT_SIDE] = 0.0f;
    trajectoryData_[TOP_LEFT] = CORNER_LEN_CONSTANT * grith_;
}

void FocusAnimationModifier::StartFocusAnimation()
{
    if (animating_) {
        return;
    }
    InitTrajectoryData(roundRect_);
    if (onPointLightUpdate_) {
        onPointLightUpdate_(ILLUMUNATEDTYPE_CONTENT, lightIntensity_);
    }
    animating_ = true;
    AnimationOption option = AnimationOption();
    RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
    option.SetDuration(ANIMATION_DURATION);
    option.SetDelay(0);
    option.SetCurve(curve);
    option.SetIteration(-1);
    focusAnimation_ = AnimationUtils::StartAnimation(
        option, [&]() { focusProcessFloat_->Set(360.0f); }, [&]() {}, [&]() { isRise_ = !isRise_; });
}

void FocusAnimationModifier::StopFocusAnimation()
{
    if (!animating_) {
        return;
    }
    pointLightZ_ = 0.0f;
    if (onPointLightUpdate_) {
        onPointLightUpdate_(ILLUMUNATEDTYPE_BORDER, pointLightZ_);
    }
    if (focusAnimation_) {
        AnimationUtils::StopAnimation(focusAnimation_);
    }
    animating_ = false;
    focusProcessFloat_->Set(0.0f);
}

void FocusAnimationModifier::onDraw(DrawingContext& context)
{
    CHECK_NULL_VOID(&roundRect_);
    PaintFocusState(roundRect_, context.canvas, focusProcessFloat_->Get());
}

void FocusAnimationModifier::PaintFocusState(const RSRoundRect& rrect, RSCanvas& rsCanvas, float percent)
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(paintWidthPx_);
    pen.SetColor(ToRSColor(paintColor_));
    float curProcess = percent / 360.0f;
    if (onPointLightPosUpdate_) {
        auto [x, y] = GetPosition(curProcess * grith_);
        onPointLightPosUpdate_(x, y, pointLightZ_);
    }
    RSScalar halfDenominator = 2.0f;
    RSScalar centerX = (rrect.GetRect().GetLeft() + rrect.GetRect().GetRight()) / halfDenominator;
    RSScalar centerY = (rrect.GetRect().GetTop() + rrect.GetRect().GetBottom()) / halfDenominator;
    auto alpha = isRise_ ? RISING_SLOPE * percent + RISING_CONSTANT : DESECEND_SLOPE * percent + DESECEND_CONSTANT;
    RSColorQuad boundaryColor =
        RSColor::ColorQuadSetARGB(alpha, paintColor_.GetRed(), paintColor_.GetGreen(), paintColor_.GetBlue());
    RSColorQuad glowColor = RSColor::ColorQuadSetARGB(
        paintColor_.GetAlpha(), paintColor_.GetRed(), paintColor_.GetGreen(), paintColor_.GetBlue());
    std::vector<RSColorQuad> colors = { boundaryColor, glowColor, glowColor, boundaryColor };
    std::vector<RSScalar> pos = { LEFTEDGE_START_PERCENT, MIDLOWEDGE_START_PERCENT, RIGHTLOWEDGE_START_PERCENT,
        RIGHTEDGE_END_PERCENT };
    auto [angleStart, angleEnd, rotateAngle] = GetRenderAngle(curProcess, centerX, centerY);
    rsMatrix_.Translate(-centerX, -centerY);
    rsMatrix_.PostRotate(rotateAngle);
    rsMatrix_.PostTranslate(centerX, centerY);
    pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
        RSPoint(centerX, centerY), colors, pos, RSTileMode::CLAMP, angleStart, angleEnd, &rsMatrix_));
    rsCanvas.AttachPen(pen);
    auto delegatePtr = weakFrameNode_.Upgrade();
    CHECK_NULL_VOID(delegatePtr);
    if (!delegatePtr->GetCheckboxFlag()) {
        rsCanvas.DrawRoundRect(rrect);
    } else {
        auto paintProperty = delegatePtr->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        CheckBoxStyle checkBoxStyle =
            paintProperty->HasCheckBoxSelectedStyle()
                ? paintProperty->GetCheckBoxSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE)
                : (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? CheckBoxStyle::CIRCULAR_STYLE
                                                                                      : CheckBoxStyle::SQUARE_STYLE);
        if (CheckBoxStyle::SQUARE_STYLE == checkBoxStyle) {
            rsCanvas.DrawRoundRect(rrect);
        } else {
            rsCanvas.DrawCircle(RSPoint(centerX, centerY), shorterSide_ / halfDenominator);
        }
    }
    rsCanvas.DetachPen();
}

std::tuple<float, float, float> FocusAnimationModifier::GetRenderAngle(float curProcess, float centerX, float centerY)
{
    float glowLineLen = longerSide_ * PERCENT_GLOW_LINE;
    float halfLen = glowLineLen / 2.0f;
    auto [leftX, leftY] = GetPosition(
        curProcess * grith_ - halfLen < 0 ? curProcess * grith_ + grith_ - halfLen : curProcess * grith_ - halfLen);
    auto [rightX, rightY] = GetPosition(curProcess * grith_ + halfLen > grith_ ? curProcess * grith_ + halfLen - grith_
                                                                               : curProcess * grith_ + halfLen);
    float leftAngle = GetIncludeAngleOfVector(centerX, centerY, centerX + 1, centerY, leftX, leftY);
    float rightAngle = GetIncludeAngleOfVector(centerX, centerY, centerX + 1, centerY, rightX, rightY);
    float angleStart = 0.0f;
    float angleEnd = leftAngle <= rightAngle ? rightAngle - leftAngle : rightAngle - leftAngle + 360.0f;
    return std::make_tuple(angleStart, angleEnd, leftAngle);
}

float FocusAnimationModifier::CalArcAngle(float radius, float arcLen)
{
    return radius == 0 ? 0.0f : arcLen / radius;
}

float FocusAnimationModifier::CalArcLen(float radius)
{
    return 0.5f * M_PI * radius;
}

std::tuple<float, float> FocusAnimationModifier::GetPosition(float curProcess)
{
    float compeletedPro = 0.0f;
    for (int i = 0; i < TRAJECTORY_DATA_CNT; i++) {
        if (curProcess >= compeletedPro && curProcess < compeletedPro + trajectoryData_[i]) {
            if (trajectDataFunc_[i]) {
                auto [x, y] = trajectDataFunc_[i](curProcess, compeletedPro);
                return std::make_tuple(x + roundRect_.GetRect().GetLeft(), y + roundRect_.GetRect().GetTop());
            } else {
                return std::make_tuple(0.0f, 0.0f);
            }
        }
        compeletedPro += trajectoryData_[i];
    }
    return std::make_tuple(0.0f, 0.0f);
}

float FocusAnimationModifier::GetIncludeAngleOfVector(float x0, float y0, float x1, float y1, float x2, float y2)
{
    float xa = x1 - x0;
    float ya = y1 - y0;
    float xb = x2 - x0;
    float yb = y2 - y0;
    float d1 = std::sqrt(std::pow(xa, 2) + std::pow(ya, 2));
    float d2 = std::sqrt(std::pow(xb, 2) + std::pow(yb, 2));
    float res = (xa * xb + ya * yb) / (d1 * d2);
    float angle = std::acos(res);
    return y2 < y0 ? 360.0f - angle / M_PI * 180.0f : angle / M_PI * 180.0f;
}
} // namespace OHOS::Ace::NG