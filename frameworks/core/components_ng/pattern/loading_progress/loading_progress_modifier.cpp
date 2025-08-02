/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/loading_progress/loading_progress_modifier.h"

#include "base/geometry/arc.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_utill.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float TOTAL_ANGLE = 360.0f;
constexpr float ROTATEX = -116.0f;
constexpr float ROTATEY = 30.0f;
constexpr float ROTATEZ = 22.0f;
constexpr float COUNT = 50.0f;
constexpr float HALF = 0.5f;
constexpr float DOUBLE = 2.0f;
constexpr int32_t SKEWY = 3;
constexpr int32_t SCALEY = 4;
constexpr float RING_ALPHA = 200 / 255.0f;
constexpr int32_t RING_ALPHA_DARK = 255;
constexpr int32_t RING_ALPHA_DARK_BACKGROUNG = 150;
constexpr Color DEFAULT_COLOR_DARK = Color(0x99FFFFFF);
constexpr int32_t TOTAL_POINTS_COUNT = 20;
constexpr int32_t TAIL_ANIAMTION_DURATION = 400;
constexpr int32_t TRANS_DURATION = 100;
constexpr float TOTAL_TAIL_LENGTH = 60.0f;
constexpr float TAIL_ALPHA_RATIO = 0.82f;
constexpr float INITIAL_SIZE_SCALE = 0.825f;
constexpr float INITIAL_OPACITY_SCALE = 0.7f;
constexpr float COMET_TAIL_ANGLE = 3.0f;
constexpr int32_t LOADING_DURATION = 1200;
constexpr float FOLLOW_START = 72.0f;
constexpr float FOLLOW_SPAN = 10.0f;
constexpr float FULL_COUNT = 100.0f;
constexpr float STAGE1 = 0.25f;
constexpr float STAGE2 = 0.65f;
constexpr float STAGE3 = 0.75f;
constexpr float STAGE4 = 0.85f;
constexpr float STAGE5 = 1.0f;
constexpr float OPACITY1 = 0.2f;
constexpr float OPACITY2 = 0.7f;
constexpr float OPACITY3 = 1.0f;
constexpr float SIZE_SCALE1 = 0.65f;
constexpr float SIZE_SCALE2 = 0.825f;
constexpr float SIZE_SCALE3 = 0.93f;
constexpr float MOVE_STEP = 0.06f;
constexpr float TRANS_OPACITY_SPAN = 0.3f;
constexpr float FULL_OPACITY = 255.0f;
constexpr float FAKE_DELTA = 0.01f;
constexpr float BASE_SCALE = 0.707f; // std::sqrt(2)/2
constexpr float REFRESH_DARK_MODE_RING_BLUR_RADIUS = 0.4f;
constexpr int32_t ANIMATION_MIN_FFR = 15;
constexpr int32_t ANIMATION_MAX_FFR = 60;
constexpr int32_t ANIMATION_EXPECT_FFR = 30;
} // namespace
LoadingProgressModifier::LoadingProgressModifier(LoadingProgressOwner loadingProgressOwner)
    : enableLoading_(AceType::MakeRefPtr<PropertyBool>(true)),
      offset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      date_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT)),
      centerDeviation_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f)),
      cometOpacity_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_OPACITY_SCALE)),
      cometSizeScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_SIZE_SCALE)),
      cometTailLen_(AceType::MakeRefPtr<AnimatablePropertyFloat>(TOTAL_TAIL_LENGTH)),
      sizeScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0f)),
      useContentModifier_(AceType::MakeRefPtr<PropertyBool>(false)),
      loadingProgressOwner_(loadingProgressOwner)
{
    AttachProperty(enableLoading_);
    AttachProperty(offset_);
    AttachProperty(contentSize_);
    AttachProperty(date_);
    AttachProperty(color_);
    AttachProperty(centerDeviation_);
    AttachProperty(cometOpacity_);
    AttachProperty(cometSizeScale_);
    AttachProperty(cometTailLen_);
};

void LoadingProgressModifier::onDraw(DrawingContext& context)
{
    if (useContentModifier_->Get()) {
        return;
    }
    if (!enableLoading_->Get()) {
        return;
    }
    float date = date_->Get();
    auto diameter = std::min(contentSize_->Get().Width(), contentSize_->Get().Height());
    RingParam ringParam;
    ringParam.strokeWidth = LoadingProgressUtill::GetRingStrokeWidth(diameter) * sizeScale_->Get();
    ringParam.radius = LoadingProgressUtill::GetRingRadius(diameter) * sizeScale_->Get();
    ringParam.movement =
        (ringParam.radius * DOUBLE + ringParam.strokeWidth) * centerDeviation_->Get() * sizeScale_->Get();
    ringParam.darkRingRadius = LoadingProgressUtill::GetRingDarkRadius(diameter) * sizeScale_->Get();
    ringParam.darkBackgroundWidth = LoadingProgressUtill::GetRingDarkBackgroundWidth(diameter) * sizeScale_->Get();
    ringParam.darkBackgroundRadius = LoadingProgressUtill::GetRingDarkBackgroundRadius(diameter) * sizeScale_->Get();

    CometParam cometParam;
    cometParam.radius = LoadingProgressUtill::GetCometRadius(diameter) * sizeScale_->Get();
    cometParam.alphaScale = cometOpacity_->Get();
    cometParam.sizeScale = cometSizeScale_->Get();
    cometParam.pointCount = GetCometNumber();

    auto orbitRadius = LoadingProgressUtill::GetOrbitRadius(diameter) * sizeScale_->Get();
    if (date > COUNT) {
        DrawRing(context, ringParam);
        DrawOrbit(context, cometParam, orbitRadius, date);
    } else {
        DrawOrbit(context, cometParam, orbitRadius, date);
        DrawRing(context, ringParam);
    }
}

void LoadingProgressModifier::DrawRing(DrawingContext& context, const RingParam& ringParam)
{
    auto& canvas = context.canvas;
    canvas.Save();
    RSPen pen;
    RSFilter filter;
    auto ringColor = color_->Get();
    ringColor.BlendOpacity(RING_ALPHA);
    pen.SetColor(ToRSColor(ringColor));
    if (Container::CurrentColorMode() == ColorMode::DARK) {
        if (ringColor.GetValue() == DEFAULT_COLOR_DARK.GetValue()) {
            ringColor = LinearColor::WHITE;
        }
        // draw ring background
        DrawRingBackground(context, ringParam, ringColor);

        ringColor.BlendOpacity(RING_ALPHA_DARK / FULL_OPACITY);
        pen.SetColor(ToRSColor(ringColor));

#ifndef USE_ROSEN_DRAWING
        filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(
            ringParam.darkRingRadius, ringParam.darkRingRadius, RSTileMode::DECAL, nullptr));
#else
        filter.SetImageFilter(RSRecordingImageFilter::CreateBlurImageFilter(
            ringParam.darkRingRadius, ringParam.darkRingRadius, RSTileMode::DECAL, nullptr));
#endif
        pen.SetFilter(filter);
    }
    if (loadingProgressOwner_ == LoadingProgressOwner::REFRESH && Container::CurrentColorMode() == ColorMode::DARK) {
        filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
            RSBlurType::NORMAL, PipelineBase::GetCurrentDensity() * REFRESH_DARK_MODE_RING_BLUR_RADIUS));
        pen.SetFilter(filter);
    }
    pen.SetWidth(ringParam.strokeWidth);
    pen.SetAntiAlias(true);
    canvas.AttachPen(pen);
    canvas.DrawCircle(
        { offset_->Get().GetX() + contentSize_->Get().Width() * HALF,
            offset_->Get().GetY() + contentSize_->Get().Height() * HALF + ringParam.movement },
        ringParam.radius);
    canvas.DetachPen();
    canvas.Restore();
}

void LoadingProgressModifier::DrawRingBackground(
    DrawingContext& context, const RingParam& ringParam, LinearColor& ringColor)
{
    auto& canvas = context.canvas;
    canvas.Save();
    RSPen pen;

    ringColor.BlendOpacity(RING_ALPHA_DARK_BACKGROUNG / FULL_OPACITY);
    pen.SetColor(ToRSColor(ringColor));

    RSFilter filter;
#ifndef USE_ROSEN_DRAWING
    filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(
        ringParam.darkBackgroundRadius, ringParam.darkBackgroundRadius, RSTileMode::DECAL, nullptr));
#else
    filter.SetImageFilter(RSRecordingImageFilter::CreateBlurImageFilter(
        ringParam.darkBackgroundRadius, ringParam.darkBackgroundRadius, RSTileMode::DECAL, nullptr));
#endif
    pen.SetFilter(filter);
    pen.SetWidth(ringParam.darkBackgroundWidth);
    pen.SetAntiAlias(true);
    canvas.AttachPen(pen);
    canvas.DrawCircle({ offset_->Get().GetX() + contentSize_->Get().Width() * HALF,
                          offset_->Get().GetY() + contentSize_->Get().Height() * HALF + ringParam.movement },
        ringParam.radius);
    canvas.DetachPen();
    canvas.Restore();
}

void LoadingProgressModifier::DrawOrbit(
    DrawingContext& context, const CometParam& cometParam, float orbitRadius, float date)
{
    auto pointCounts = cometParam.pointCount;
    auto& canvas = context.canvas;
    float width = contentSize_->Get().Width();
    float height = contentSize_->Get().Height();
    double angle = TOTAL_ANGLE * date / FULL_COUNT;
    RSCamera3D camera;
    RSMatrix matrix;
    AdjustMatrix(camera, matrix);
    auto center = RSPoint(offset_->Get().GetX() + width / 2, offset_->Get().GetY() + height / 2);
    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.Save();
    canvas.Translate(center.GetX(), center.GetY());
    std::vector<RSPoint> points;
    for (uint32_t i = 0; i < pointCounts; i++) {
        RSPoint point;
        float cometAngal = GetCurentCometAngle(angle, pointCounts - i, pointCounts);
        float rad = cometAngal * PI_NUM / (TOTAL_ANGLE * HALF);
        point.SetX(std::cos(rad) * orbitRadius);
        point.SetY(-std::sin(rad) * orbitRadius);
        points.push_back(point);
    }
    std::vector<RSPoint> distPoints(points.size());
    matrix.MapPoints(distPoints, points, points.size());
    auto cometColor = color_->Get();
    float colorAlpha = cometColor.GetAlpha() / FULL_OPACITY;
    if (Container::CurrentColorMode() == ColorMode::DARK && cometColor.GetValue() == DEFAULT_COLOR_DARK.GetValue()) {
        colorAlpha = OPACITY3;
    }
    auto baseAlpha = colorAlpha * cometParam.alphaScale;
    for (uint32_t i = 0; i < distPoints.size(); i++) {
        RSPoint pointCenter = distPoints[i];
        if (cometColor.GetValue() == Color::FOREGROUND.GetValue()) {
            brush.SetColor(ToRSColor(cometColor));
        } else {
            float setAlpha = GetCurentCometOpacity(baseAlpha, distPoints.size() - i, distPoints.size());
            if (NearZero(setAlpha)) {
                continue;
            }
            brush.SetColor(
                ToRSColor(Color::FromRGBO(cometColor.GetRed(), cometColor.GetGreen(), cometColor.GetBlue(), setAlpha)));
        }
        canvas.AttachBrush(brush);
        canvas.DrawCircle(pointCenter, cometParam.radius * cometParam.sizeScale);
    }
    canvas.DetachBrush();
    canvas.Restore();
}

void LoadingProgressModifier::AdjustMatrix(RSCamera3D& camera, RSMatrix& matrix)
{
    camera.Save();
    camera.RotateYDegrees(ROTATEY);
    camera.RotateXDegrees(ROTATEX);
    camera.RotateZDegrees(ROTATEZ);
    camera.ApplyToMatrix(matrix);
    camera.Restore();
    auto temp = matrix.Get(SKEWY);
    matrix.Set(RSMatrix::SKEW_Y, matrix.Get(SCALEY));
    matrix.Set(RSMatrix::SCALE_Y, temp);
}

void LoadingProgressModifier::StartRecycleRingAnimation()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto previousStageCurve = AceType::MakeRefPtr<CubicCurve>(0.0f, 0.0f, 0.67f, 1.0f);
    AnimationOption option;
    RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
    option.SetFrameRateRange(frameRateRange);
    option.SetDuration(isVisible_ ? LOADING_DURATION : 0);
    option.SetCurve(previousStageCurve);
    if (context->IsFormRender() && !IsDynamicComponent()) {
        option.SetIteration(1);
    } else {
        option.SetIteration(-1);
    }
    AnimationUtils::OpenImplicitAnimation(option, previousStageCurve, nullptr);
    auto middleStageCurve = AceType::MakeRefPtr<CubicCurve>(0.33f, 0.0f, 0.67f, 1.0f);
    AnimationUtils::AddKeyFrame(
        STAGE1, middleStageCurve, [weakCenterDeviation = AceType::WeakClaim(AceType::RawPtr(centerDeviation_))]() {
            auto centerDeviation = weakCenterDeviation.Upgrade();
            CHECK_NULL_VOID(centerDeviation);
            centerDeviation->Set(-1 * MOVE_STEP);
        });
    auto latterStageCurve = AceType::MakeRefPtr<CubicCurve>(0.33f, 0.0f, 1.0f, 1.0f);
    AnimationUtils::AddKeyFrame(
        STAGE3, latterStageCurve, [weakCenterDeviation = AceType::WeakClaim(AceType::RawPtr(centerDeviation_))]() {
            auto centerDeviation = weakCenterDeviation.Upgrade();
            CHECK_NULL_VOID(centerDeviation);
            centerDeviation->Set(MOVE_STEP);
        });
    AnimationUtils::AddKeyFrame(
        STAGE5, latterStageCurve, [weakCenterDeviation = AceType::WeakClaim(AceType::RawPtr(centerDeviation_))]() {
            auto centerDeviation = weakCenterDeviation.Upgrade();
            CHECK_NULL_VOID(centerDeviation);
            centerDeviation->Set(0.0f);
        });
    AnimationUtils::CloseImplicitAnimation();
}

void LoadingProgressModifier::StartRecycleCometAnimation()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto curve = AceType::MakeRefPtr<LinearCurve>();
    AnimationOption option;
    RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
    option.SetFrameRateRange(frameRateRange);
    option.SetDuration(isVisible_ ? LOADING_DURATION : 0);
    option.SetCurve(curve);
    if (context->IsFormRender() && !IsDynamicComponent()) {
        option.SetIteration(1);
    } else {
        option.SetIteration(-1);
    }

    cometOpacity_->Set(OPACITY2);
    cometTailLen_->Set(TOTAL_TAIL_LENGTH);
    AnimationUtils::OpenImplicitAnimation(option, curve, nullptr);
    AnimationUtils::AddKeyFrame(STAGE1, curve,
        [weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(OPACITY1);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(SIZE_SCALE1);
            }
        });
    AnimationUtils::AddKeyFrame(STAGE2, curve,
        [weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(OPACITY3);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(SIZE_SCALE3);
            }
        });
    AnimationUtils::AddKeyFrame(STAGE3, curve,
        [weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(OPACITY3);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(1.0f);
            }
        });
    AnimationUtils::AddKeyFrame(STAGE4, curve,
        [weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(OPACITY3);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(SIZE_SCALE3);
            }
        });
    AnimationUtils::AddKeyFrame(STAGE5, curve,
        [weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(OPACITY2);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(SIZE_SCALE2);
            }
        });
    AnimationUtils::CloseImplicitAnimation();
}

void LoadingProgressModifier::StartCometTailAnimation()
{
    auto curve = AceType::MakeRefPtr<LinearCurve>();
    AnimationOption option;
    RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
    option.SetFrameRateRange(frameRateRange);
    option.SetDuration(TAIL_ANIAMTION_DURATION);
    option.SetIteration(1);
    option.SetCurve(curve);
    AnimationUtils::Animate(option, [weakCometTailLen = AceType::WeakClaim(AceType::RawPtr(cometTailLen_))]() {
        auto cometTailLen = weakCometTailLen.Upgrade();
        CHECK_NULL_VOID(cometTailLen);
        cometTailLen->Set(TOTAL_TAIL_LENGTH);
    });
}

float LoadingProgressModifier::GetCurentCometOpacity(float baseOpacity, uint32_t index, uint32_t totalNumber)
{
    return baseOpacity * std::pow(TAIL_ALPHA_RATIO, std::clamp(index, 1u, totalNumber) - 1);
}

float LoadingProgressModifier::GetCurentCometAngle(float baseAngle, uint32_t index, uint32_t totalNumber)
{
    return std::fmod((baseAngle - (std::clamp(index, 1u, totalNumber) - 1) * COMET_TAIL_ANGLE), TOTAL_ANGLE);
}

uint32_t LoadingProgressModifier::GetCometNumber()
{
    CHECK_NULL_RETURN(cometTailLen_, TOTAL_POINTS_COUNT);
    return static_cast<uint32_t>(cometTailLen_->Get() / COMET_TAIL_ANGLE);
}

void LoadingProgressModifier::StartRecycle()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (isLoading_) {
        return;
    }
    sizeScale_->Set(1.0f);
    if (date_) {
        isLoading_ = true;
        date_->Set(0.0f);
        AnimationOption option = AnimationOption();
        RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
        option.SetFrameRateRange(frameRateRange);
        RefPtr<Curve> curve = AceType::MakeRefPtr<CubicCurve>(0.25f, 0.30f, 0.50f, 0.14f);
        option.SetDuration(isVisible_ ? LOADING_DURATION : 0);
        option.SetDelay(0);
        option.SetCurve(curve);
        if (context->IsFormRender() && !IsDynamicComponent()) {
            option.SetIteration(1);
        } else {
            option.SetIteration(-1);
        }
        AnimationUtils::Animate(option, [weakDate = AceType::WeakClaim(AceType::RawPtr(date_))]() {
            auto date = weakDate.Upgrade();
            CHECK_NULL_VOID(date);
            date->Set(FULL_COUNT);
        });
    }
    cometOpacity_->Set(INITIAL_OPACITY_SCALE);
    cometSizeScale_->Set(INITIAL_SIZE_SCALE);
    // ring up and down shift animation
    StartRecycleRingAnimation();
    // comet's circle Color transparency and sizeScale animation
    StartRecycleCometAnimation();
}

void LoadingProgressModifier::StartTransToRecycleAnimation()
{
    sizeScale_->Set(1.0f);
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.6f, 0.2f, 1.0f, 1.0f);
    AnimationOption option;
    RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
    option.SetFrameRateRange(frameRateRange);
    option.SetDuration(TRANS_DURATION);
    option.SetIteration(1);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option,
        [weakDate = AceType::WeakClaim(AceType::RawPtr(date_)),
            weakCometOpacity = AceType::WeakClaim(AceType::RawPtr(cometOpacity_)),
            weakCometSizeScale = AceType::WeakClaim(AceType::RawPtr(cometSizeScale_))]() {
            auto date = weakDate.Upgrade();
            if (date) {
                date->Set(FULL_COUNT);
            }
            auto cometOpacity = weakCometOpacity.Upgrade();
            if (cometOpacity) {
                cometOpacity->Set(1.0 - TRANS_OPACITY_SPAN);
            }
            auto cometSizeScale = weakCometSizeScale.Upgrade();
            if (cometSizeScale) {
                cometSizeScale->Set(INITIAL_SIZE_SCALE);
            }
        },
        [weak = AceType::WeakClaim(this)]() {
            auto modify = weak.Upgrade();
            CHECK_NULL_VOID(modify);
            modify->StartRecycle();
        });
    StartCometTailAnimation();
}

void LoadingProgressModifier::ChangeRefreshFollowData(float refreshFollowRatio)
{
    auto ratio = CorrectNormalize(refreshFollowRatio);
    sizeScale_->Set(BASE_SCALE + (1.0 - BASE_SCALE) * ratio);
    if (isLoading_) {
        CloseAnimation(FOLLOW_START, COMET_TAIL_ANGLE, 1.0f, 1.0f);
    }
    CHECK_NULL_VOID(date_);
    date_->Set(FOLLOW_START + FOLLOW_SPAN * ratio);
    cometTailLen_->Set(COMET_TAIL_ANGLE);
    cometOpacity_->Set(1.0f);
    cometSizeScale_->Set(1.0f);
}

void LoadingProgressModifier::ChangeSizeScaleData(float refreshFadeAwayRatio)
{
    auto ratio = CorrectNormalize(refreshFadeAwayRatio);
    sizeScale_->Set(BASE_SCALE + (1.0 - BASE_SCALE) * ratio);
}

void LoadingProgressModifier::CloseAnimation(float date, float cometLen, float cometOpacity, float cometScale)
{
    isLoading_ = false;
    AnimationOption option = AnimationOption();
    RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
    option.SetDuration(0);
    option.SetIteration(1);
    option.SetCurve(curve);
    RefPtr<FrameRateRange> frameRateRange =
            AceType::MakeRefPtr<FrameRateRange>(ANIMATION_MIN_FFR, ANIMATION_MAX_FFR, ANIMATION_EXPECT_FFR);
    option.SetFrameRateRange(frameRateRange);
    date_->Set(date + FAKE_DELTA);
    cometTailLen_->Set(cometLen + FAKE_DELTA);
    cometOpacity_->Set(cometOpacity + FAKE_DELTA);
    cometSizeScale_->Set(cometScale + FAKE_DELTA);
    centerDeviation_->Set(0.0f + FAKE_DELTA);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), date, cometLen, cometOpacity, cometScale]() {
        auto curObj = weak.Upgrade();
        CHECK_NULL_VOID(curObj);
        curObj->date_->Set(date);
        curObj->cometTailLen_->Set(cometLen);
        curObj->cometOpacity_->Set(cometOpacity);
        curObj->cometSizeScale_->Set(cometScale);
        curObj->centerDeviation_->Set(0.0f);
    });
}
float LoadingProgressModifier::CorrectNormalize(float originData)
{
    auto ratio = originData;
    if (ratio < 0.0f) {
        ratio = 0.0f;
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    };
    return ratio;
}
} // namespace OHOS::Ace::NG
