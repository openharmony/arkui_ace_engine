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

#include "core/components_ng/pattern/indexer/arc_indexer_content_modifier.h"

#include <optional>
#include <utility>

#include "base/geometry/arc.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/path_painter.h"
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"

namespace OHOS::Ace::NG {
ArcIndexerContentModifier::ArcIndexerContentModifier()
{
    strokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    arcRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    arcCenter_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    startAngle_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    sweepAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    stepAngle_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    AttachProperty(strokeWidth_);
    AttachProperty(arcRadius_);
    AttachProperty(startAngle_);
    AttachProperty(sweepAngle_);
    AttachProperty(arcCenter_);
    AttachProperty(stepAngle_);
}

void ArcIndexerContentModifier::onDraw(DrawingContext& context)
{
    if (sweepAngle_ > 0) {
        DrawArcShadow(context);
        DrawArc(context);
    }
}

void ArcIndexerContentModifier::DrawArcShadow(DrawingContext& context)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto strokeWidth = strokeWidth_->Get();

    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(Color::BLACK.GetValue());

    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
        RSBlurType::SOLID, RSDrawing::ConvertRadiusToSigma(strokeWidth), false));
    pen.SetFilter(filter);

    auto center = arcCenter_->Get();
    auto radius = arcRadius_->Get();
    auto startAngle = startAngle_->Get();
    auto sweepAngle = sweepAngle_->Get();
    auto stepAngle = stepAngle_->Get();
    if (NearEqual(sweepAngle + stepAngle, FULL_CIRCLE_ANGLE)) {
        sweepAngle = FULL_CIRCLE_ANGLE;
    }

    canvas.AttachPen(pen);
    canvas.DrawArc(
        { center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
        startAngle, sweepAngle);
    canvas.DetachPen();
}

void ArcIndexerContentModifier::DrawArc(DrawingContext& context)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto strokeWidth = strokeWidth_->Get();

    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(ToRSColor(indexerTheme->GetIndexerBackgroundColor()));

    auto center = arcCenter_->Get();
    auto radius = arcRadius_->Get();
    auto startAngle = startAngle_->Get();
    auto sweepAngle = sweepAngle_->Get();
    auto stepAngle = stepAngle_->Get();
    if (NearEqual(sweepAngle + stepAngle, FULL_CIRCLE_ANGLE)) {
        sweepAngle = FULL_CIRCLE_ANGLE;
    }

    canvas.AttachPen(pen);
    canvas.DrawArc(
        { center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
        startAngle, sweepAngle);
    canvas.DetachPen();
}

} // namespace OHOS::Ace::NG
