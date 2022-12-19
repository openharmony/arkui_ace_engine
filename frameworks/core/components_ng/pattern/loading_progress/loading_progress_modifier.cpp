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
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint.h"

namespace OHOS::Ace::NG {
namespace {
const float MOVE_ANGLE = 10.f;
const float TOTAL_ANGLE = 360.0f;
const float COMET_TAIL_ANGLE = 2.0f;
const float ROTATEX = 100.f;
const float ROTATEZ = 30.f;
const float DECAY_FACTOR = 2.f;
const float HALF_COUNT = 25.0f;
const Dimension RING_WIDTH = 2.8_vp;
const Dimension COMET_WIDTH = 6.0_vp;
constexpr int32_t START_POINT = 0;
constexpr int32_t MIDDLE_POINT = 1;
constexpr int32_t END_POINT = 2;
const Dimension MODE_SMALL = 16.0_vp;
const Dimension MODE_MIDDLE = 40.0_vp;
const Dimension MODE_LARGE = 76.0_vp;
const Dimension MODE_RING_WIDTH[] = { 2.8_vp, 1.9_vp, 1.2_vp };
const Dimension MODE_COMET_RADIUS[] = { 3.0_vp, 3.0_vp, 2.2_vp };
} // namespace

LoadingProgressModifier::LoadingProgressModifier()
    : date_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE))
{
    AttachProperty(date_);
    AttachProperty(color_);
}

void LoadingProgressModifier::DrawRing(DrawingContext& context, float date, float scale_) const
{
    auto& canvas = context.canvas;
    float width_ = context.width;
    float height_ = context.height;
    float ringRadius_ = scale_ * RING_RADIUS.ConvertToPx();
    canvas.Save();
    RSPen pen;
    pen.SetColor(ToRSColor(color_->Get()));
    pen.SetWidth(ringWidth_ * scale_);
    date = abs(COUNT - date);
    canvas.AttachPen(pen);
    canvas.DrawCircle(
        { width_ / 2, height_ / 2 + (date - HALF_COUNT) / HALF_COUNT * ringRadius_ * RING_MOVEMENT }, ringRadius_);
    canvas.DetachPen();
    canvas.Restore();
}

void LoadingProgressModifier::DrawOrbit(DrawingContext& context, float date, float scale_) const
{
    constexpr uint32_t pointCounts = 20;
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
    for (int i = 0; i <= pointCounts; i++) {
        RSPoint point;
        float cometAngal = i * COMET_TAIL_ANGLE + angle + TOTAL_ANGLE - pointCounts * COMET_TAIL_ANGLE - MOVE_ANGLE;
        float rad = cometAngal * PI_NUM / (TOTAL_ANGLE * HALF);
        point.SetX((std::cos(rad) * scale_ * ORBIT_RADIUS.ConvertToPx()));
        point.SetY(-std::sin(rad) * scale_ * ORBIT_RADIUS.ConvertToPx());
        points.push_back(point);
    }
    std::vector<RSPoint> distPoints(pointCounts);
    matrix.MapPoints(distPoints, points, points.size());
    for (int i = 0; i <= pointCounts; i++) {
        RSPoint pointCenter = distPoints[i];
        float setAlpha = colorAlpha * pow(static_cast<float>(i) / pointCounts, DECAY_FACTOR);
        if (NearZero(setAlpha)) {
            continue;
        }
        cometColor.SetAlphaF(setAlpha);
        brush.SetColor(cometColor);
        canvas.AttachBrush(brush);
        canvas.DrawCircle(pointCenter, cometRadius_ * scale_);
    }
    canvas.DetachBrush();
    canvas.Restore();
}

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
        ringWidth_ = pipeline->NormalizeToPx(MODE_RING_WIDTH[start]);
        cometRadius_ = pipeline->NormalizeToPx(MODE_COMET_RADIUS[start]);
    } else {
        ringWidth_ = pipeline->NormalizeToPx(MODE_RING_WIDTH[start] +
            (MODE_RING_WIDTH[end] - MODE_RING_WIDTH[start]) * percent);
        cometRadius_ = pipeline->NormalizeToPx(MODE_COMET_RADIUS[start] +
            (MODE_COMET_RADIUS[end] - MODE_COMET_RADIUS[start]) * percent);
    }
}
} // namespace OHOS::Ace::NG
