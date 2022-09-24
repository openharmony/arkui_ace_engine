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

#include "core/components_ng/pattern/loading_progress/loading_progress_modifer.h"

#include "include/core/SkColor.h"
#include "include/core/SkPoint.h"
#include "third_party/skia/include/utils/SkCamera.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/paint.h"

namespace OHOS::Ace::NG {

LoadingProgressModifier::LoadingProgressModifier() : ContentModifierFloat(0.0) {}

// void LoadingProgressModifier::DrawRing(RSDrawingContext& context, float date, float scale_) const
// {
//     auto* canvas = context.canvas;
//     float width_ = context.width;
//     float height_ = context.height;
//     float ringRadius_ = scale_ * RING_RADIUS.ConvertToPx();
//     SkPaint pen;
//     pen.setAntiAlias(true);
//     pen.setStyle(SkPaint::Style::kStroke_Style);
//     pen.setColor(color_);
//     pen.setStrokeWidth(RING_WIDTH.ConvertToPx() * scale_);
//     date = abs(COUNT - date);
//     date = ringRadius_ * RING_MOVEMENT * (date - HALF_COUNT) / COUNT;
//     canvas->drawCircle(width_ / 2, height_ / 2 + date, ringRadius_, pen);
// }

// void LoadingProgressModifier::DrawOrbit(RSDrawingContext& context, float date, float scale_) const
// {
//     auto* canvas = context.canvas;
//     float width_ = context.width;
//     float height_ = context.height;
//     double angle = TOTAL_ANGLE * date / FULL_COUNT;
//     auto center = new SkPoint();
//     center->set(width_ / 2, height_ / 2);
//     SkMatrix matrix;
//     auto camera_ = new Sk3DView();
//     canvas->save();
//     camera_->save();
//     camera_->rotateZ(ROTATEZ);
//     camera_->rotateX(ROTATEX);
//     camera_->getMatrix(&matrix);
//     camera_->restore();
//     SkPaint pen;
//     pen.setAntiAlias(true);
//     SkColor color1_;
//     pen.setStyle(SkPaint::Style::kFill_Style);
//     float color_a = SkColorGetA(color_);
//     if (date > 0 && date < COUNT) {
//         color_a = color_a * pow((date - HALF_COUNT) / HALF_COUNT, 4) * (1 - HALF * HALF * HALF) +
//                   color_a * HALF * HALF * HALF;
//     }
//     SkPoint point;
//     canvas->translate(center->x(), center->y());
//     for (int i = 0; i <= COMET_TAIL_ANGLE; i++) {
//         color1_ = SkColorSetA(color_, color_a * pow(static_cast<float>(i) / (COMET_TAIL_ANGLE), 3));
//         float cometAngal = i + angle + TOTAL_ANGLE - COMET_TAIL_ANGLE;
//         float rad = cometAngal * PI_NUM / (TOTAL_ANGLE * HALF);
//         point.set((std::cos(rad) * scale_ * ORBIT_RADIUS.ConvertToPx()),
//             -std::sin(rad) * scale_ * ORBIT_RADIUS.ConvertToPx());
//         matrix.mapPoints(&point, &point, 1);
//         pen.setColor(color1_);
//         canvas->drawCircle(point.x(), point.y(), COMET_WIDTH.ConvertToPx() * HALF * scale_, pen);
//     }
//     canvas->restore();
// }
} // namespace OHOS::Ace::NG