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

#include "core/components_ng/pattern/loading_progress/loading_progress_modifier.h"

#include "base/utils/utils.h"
#include "bridge/common/dom/dom_type.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension RING_WIDTH = 2.8_vp;
const Dimension COMET_WIDTH = 6.0_vp;
constexpr int32_t START_POINT = 0;
constexpr int32_t MIDDLE_POINT = 1;
constexpr int32_t END_POINT = 2;
constexpr float TOTAL_ANGLE = 360.0f;
constexpr float HALF_COUNT = 25.0f;
constexpr float ROTATEX = 100.f;
constexpr float ROTATEZ = 30.f;
constexpr float DECAY_FACTOR = 2.0f;
constexpr float COMET_TAIL_ANGLE = 2.0f;
constexpr float MOVE_ANGLE = 10.f;
const Dimension MODE_SMALL = 16.0_vp;
const Dimension MODE_MIDDLE = 40.0_vp;
const Dimension MODE_LARGE = 76.0_vp;
const Dimension MODE_RING_WIDTH[] = { 2.8_vp, 1.9_vp, 1.2_vp };
const Dimension MODE_COMET_RADIUS[] = { 3.0_vp, 3.0_vp, 2.2_vp };
constexpr Dimension RING_RADIUS = 10.5_vp;
constexpr Dimension ORBIT_RADIUS = 17.0_vp;
constexpr float RING_MOVEMENT = 0.06f;
constexpr float COUNT = 50.0f;
constexpr float HALF = 0.5f;
constexpr int32_t TOTAL_POINTS_COUNT = 20;
} // namespace
LoadingProgressModifier::LoadingProgressModifier(LoadingProgressOwner loadingProgressOwner)
    : date_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE)),
      loadingProgressOwner_(loadingProgressOwner)
{
    AttachProperty(date_);
    AttachProperty(color_);
};

void LoadingProgressModifier::UpdateLoadingSize(float diameter)
{
    ringWidth_ = RING_WIDTH.ConvertToPx();
    cometRadius_ = COMET_WIDTH.ConvertToPx() * HALF;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (LessOrEqual(diameter, pipeline->NormalizeToPx(MODE_SMALL))) {
        CalculateValue(START_POINT, START_POINT);
    } else if (LessOrEqual(diameter, pipeline->NormalizeToPx(MODE_MIDDLE))) {
        CalculateValue(START_POINT, MIDDLE_POINT,
            (diameter - pipeline->NormalizeToPx(MODE_SMALL)) /
                (pipeline->NormalizeToPx(MODE_MIDDLE) - pipeline->NormalizeToPx(MODE_SMALL)));
    } else if (LessOrEqual(diameter, pipeline->NormalizeToPx(MODE_LARGE))) {
        CalculateValue(MIDDLE_POINT, END_POINT,
            (diameter - pipeline->NormalizeToPx(MODE_MIDDLE)) /
                (pipeline->NormalizeToPx(MODE_LARGE) - pipeline->NormalizeToPx(MODE_MIDDLE)));
    } else {
        CalculateValue(END_POINT, END_POINT);
    }
}

void LoadingProgressModifier::CalculateValue(int32_t start, int32_t end, double percent)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (start == end) {
        ringWidth_ = MODE_RING_WIDTH[start].ConvertToPx();
        cometRadius_ = MODE_COMET_RADIUS[start].ConvertToPx();
    } else {
        ringWidth_ = MODE_RING_WIDTH[start].ConvertToPx() +
                     (MODE_RING_WIDTH[end].ConvertToPx() - MODE_RING_WIDTH[start].ConvertToPx()) * percent;
        cometRadius_ = MODE_COMET_RADIUS[start].ConvertToPx() +
                       (MODE_COMET_RADIUS[end].ConvertToPx() - MODE_COMET_RADIUS[start].ConvertToPx()) * percent;
    }
}

void LoadingProgressModifier::onDraw(DrawingContext& context)
{
    float scale_ = 1.0;
    float date = date_->Get();
    UpdateLoadingSize(std::min(context.width, context.height));
    scale_ = std::min((context.width / (ORBIT_RADIUS.ConvertToPx() + cometRadius_ / HALF)),
        (context.height / (RING_RADIUS.ConvertToPx() * (1 + RING_MOVEMENT) + ringWidth_ * HALF))) * HALF;
    if (date > COUNT) {
        DrawRing(context, date, scale_);
        DrawOrbit(context, date, scale_);
    } else {
        DrawOrbit(context, date, scale_);
        DrawRing(context, date, scale_);
    }
}

void LoadingProgressModifier::DrawRing(DrawingContext& context, float date, float scale_)
{
    auto ringWidth_ = RING_WIDTH.ConvertToPx();
    auto& canvas = context.canvas;
    float width_ = context.width;
    float height_ = context.height;
    float ringRadius_ = scale_ * RING_RADIUS.ConvertToPx();
    canvas.Save();
    RSPen pen;
    pen.SetColor(ToRSColor(color_->Get()));
    pen.SetWidth(ringWidth_ * scale_);
    pen.SetAntiAlias(true);
    date = abs(COUNT - date);
    canvas.AttachPen(pen);
    canvas.DrawCircle(
        { width_ / 2, height_ / 2 + (date - HALF_COUNT) / HALF_COUNT * ringRadius_ * RING_MOVEMENT }, ringRadius_);
    canvas.DetachPen();
    canvas.Restore();
}

void LoadingProgressModifier::DrawOrbit(DrawingContext& context, float date, float scale_)
{
    auto cometRadius_ = COMET_WIDTH.ConvertToPx() * HALF;
    const uint32_t pointCounts = TOTAL_POINTS_COUNT;
    auto& canvas = context.canvas;
    float width_ = context.width;
    float height_ = context.height;
    double angle = TOTAL_ANGLE * date / FULL_COUNT;
    auto* camera_ = new RSCamera3D();
    camera_->Save();
    camera_->RotateYDegrees(ROTATEZ);
    camera_->RotateXDegrees(ROTATEX);
    RSMatrix matrix;
    camera_->ApplyToMatrix(matrix);
    camera_->Restore();
    auto center = RSPoint(width_ / 2, height_ / 2);
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSColor cometColor = ToRSColor(color_->Get());
    float colorAlpha = cometColor.GetAlphaF();
    if (date > 0 && date < COUNT) {
        colorAlpha = colorAlpha * pow((date - HALF_COUNT) / HALF_COUNT, DECAY_FACTOR) * (1 - HALF * HALF * HALF) +
                     colorAlpha * HALF * HALF * HALF;
    }
    canvas.Save();
    canvas.Translate(center.GetX(), center.GetY());
    std::vector<RSPoint> points;
    for (uint32_t i = 0; i < pointCounts; i++) {
        if (!isLoading_ && i < (pointCounts - 1)) {
            continue;
        }
        RSPoint point;
        float cometAngal = i * COMET_TAIL_ANGLE + angle + TOTAL_ANGLE - pointCounts * COMET_TAIL_ANGLE - MOVE_ANGLE;
        float rad = cometAngal * PI_NUM / (TOTAL_ANGLE * HALF);
        point.SetX((std::cos(rad) * scale_ * ORBIT_RADIUS.ConvertToPx()));
        point.SetY(-std::sin(rad) * scale_ * ORBIT_RADIUS.ConvertToPx());
        points.push_back(point);
    }
    std::vector<RSPoint> distPoints(points.size());
    matrix.MapPoints(distPoints, points, points.size());

    for (uint32_t i = 0; i < distPoints.size(); i++) {
        RSPoint pointCenter = distPoints[i];
        if (isLoading_) {
            float setAlpha = colorAlpha * pow(static_cast<float>(i) / pointCounts, DECAY_FACTOR);
            if (NearZero(setAlpha)) {
                continue;
            }
            cometColor.SetAlphaF(setAlpha);
        }
        brush.SetColor(cometColor);
        canvas.AttachBrush(brush);
        canvas.DrawCircle(pointCenter, cometRadius_ * scale_);
    }
    canvas.DetachBrush();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
