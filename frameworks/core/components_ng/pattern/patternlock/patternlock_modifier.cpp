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

#include "core/components_ng/pattern/patternlock/patternlock_modifier.h"

#include <algorithm>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;
constexpr int32_t RADIUS_TO_DIAMETER = 2;
constexpr float GRADUAL_CHANGE_POINT = 0.5;
// the scale of active circle radius and normal circle radius
constexpr float SCALE_ACTIVE_CIRCLE_RADIUS = 16.00 / 14.00;
// the scale of selected circle radius and normal circle radius
constexpr float SCALE_SELECTED_CIRCLE_RADIUS = 26.00 / 14.00;
constexpr int32_t MAX_ALPHA = 255;
} // namespace

PatternLockCell::PatternLockCell(int32_t column, int32_t row)
{
    column_ = column;
    row_ = row;
    code_ = PATTERN_LOCK_COL_COUNT * (row - 1) + (column - 1);
}

PatternLockModifier::PatternLockModifier()
{
    sideLength_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    circleRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    regularColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::BLACK));
    selectedColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::BLACK));
    activeColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::BLACK));
    pathColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::BLUE));
    pathStrokeWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    cellCenter_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    isMoveEventValid_ = AceType::MakeRefPtr<PropertyBool>(false);

    AttachProperty(sideLength_);
    AttachProperty(circleRadius_);
    AttachProperty(regularColor_);
    AttachProperty(selectedColor_);
    AttachProperty(activeColor_);
    AttachProperty(pathColor_);
    AttachProperty(pathStrokeWidth_);
    AttachProperty(cellCenter_);
    AttachProperty(offset_);
    AttachProperty(isMoveEventValid_);
}

void PatternLockModifier::onDraw(DrawingContext& context)
{
    auto& canvas = context.canvas;
    PaintLockLine(canvas, offset_->Get());
    for (int i = 0; i < PATTERN_LOCK_COL_COUNT; i++) {
        for (int j = 0; j < PATTERN_LOCK_COL_COUNT; j++) {
            PaintLockCircle(canvas, offset_->Get(), i + 1, j + 1);
        }
    }
}

void PatternLockModifier::PaintLockLine(RSCanvas& canvas, const OffsetF& offset)
{
    size_t count = choosePoint_.size();
    if (count == 0) {
        return;
    }

    float sideLength = sideLength_->Get();
    float pathStrokeWidth = pathStrokeWidth_->Get();
    if (LessOrEqual(pathStrokeWidth, 0.0)) {
        return;
    }
    float handleStrokeWidth = std::min(pathStrokeWidth, sideLength / PATTERN_LOCK_COL_COUNT);
    pathStrokeWidth = std::max(handleStrokeWidth, 0.0f);

    auto pathColor = pathColor_->Get();
    auto cellCenter = cellCenter_->Get();
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(pathColor));
    pen.SetWidth(pathStrokeWidth);
    pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);

    Color pathColorAlpha255 = pathColor.ToColor().ChangeAlpha(MAX_ALPHA);
    pen.SetColor(pathColorAlpha255.GetValue());
    canvas.AttachPen(pen);
    for (size_t i = 0; i < count - 1; i++) {
        OffsetF pointBegin = GetCircleCenterByXY(offset, choosePoint_[i].GetColumn(), choosePoint_[i].GetRow());
        OffsetF pointEnd = GetCircleCenterByXY(offset, choosePoint_[i + 1].GetColumn(), choosePoint_[i + 1].GetRow());
        canvas.DrawLine(RSPoint(pointBegin.GetX(), pointBegin.GetY()), RSPoint(pointEnd.GetX(), pointEnd.GetY()));
    }
    if (isMoveEventValid_->Get()) {
        OffsetF pointBegin =
            GetCircleCenterByXY(offset, choosePoint_[count - 1].GetColumn(), choosePoint_[count - 1].GetRow());
        float x1 = pointBegin.GetX();
        float y1 = pointBegin.GetY();
        float x2 = cellCenter.GetX();
        float y2 = cellCenter.GetY();
        x2 = x2 > offset.GetX() + sideLength ? offset.GetX() + sideLength : x2;
        x2 = x2 < offset.GetX() ? offset.GetX() : x2;
        y2 = y2 > offset.GetY() + sideLength ? offset.GetY() + sideLength : y2;
        y2 = y2 < offset.GetY() ? offset.GetY() : y2;

        std::vector<RSColorQuad> colors = { pathColorAlpha255.GetValue(), pathColorAlpha255.GetValue(),
            pathColorAlpha255.ChangeOpacity(0.0).GetValue() };
        std::vector<RSScalar> pos = { 0.0, GRADUAL_CHANGE_POINT, 1.0 };
        auto shader = pen.GetShaderEffect();
        shader->CreateLinearGradient(RSPoint(x1, y1), RSPoint(x2, y2), colors, pos, RSTileMode::CLAMP);
        pen.SetShaderEffect(shader);
        canvas.DrawLine(RSPoint(x1, y1), RSPoint(x2, y2));
    }
    canvas.DetachPen();
    canvas.Restore();
}

void PatternLockModifier::PaintLockCircle(RSCanvas& canvas, const OffsetF& offset, int32_t x, int32_t y)
{
    auto activeColor = activeColor_->Get();
    auto regularColor = regularColor_->Get();
    auto selectedColor = selectedColor_->Get();
    auto sideLength = sideLength_->Get();
    auto circleRadius = circleRadius_->Get();

    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(regularColor));
    OffsetF cellcenter = GetCircleCenterByXY(offset, x, y);
    OffsetF firstCellcenter = GetCircleCenterByXY(offset, 1, 1);
    float offsetX = cellcenter.GetX();
    float offsetY = cellcenter.GetY();
    const int32_t radiusCount = RADIUS_TO_DIAMETER * PATTERN_LOCK_COL_COUNT;
    float handleCircleRadius = std::min(circleRadius, sideLength / SCALE_SELECTED_CIRCLE_RADIUS / radiusCount);
    circleRadius = std::max(handleCircleRadius, 0.0f);
    if (CheckChoosePoint(x, y)) {
        const int32_t lastIndexFir = 1;
        if (CheckChoosePointIsLastIndex(x, y, lastIndexFir)) {
            if (isMoveEventValid_->Get()) {
                brush.SetColor(ToRSColor(activeColor));
                canvas.AttachBrush(brush);
                auto radius = circleRadius * SCALE_SELECTED_CIRCLE_RADIUS;
                canvas.DrawCircle(
                    RSPoint(offsetX, offsetY), std::min(static_cast<float>(radius), firstCellcenter.GetX()));
            } else {
                brush.SetColor(ToRSColor(selectedColor));
                canvas.AttachBrush(brush);
                canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius * SCALE_ACTIVE_CIRCLE_RADIUS);
            }
        } else {
            brush.SetColor(ToRSColor(selectedColor));
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius * SCALE_ACTIVE_CIRCLE_RADIUS);
        }
    } else {
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius);
    }
    canvas.DetachBrush();
}

bool PatternLockModifier::CheckChoosePoint(int32_t x, int32_t y) const
{
    for (auto it : choosePoint_) {
        if (it.GetColumn() == x && it.GetRow() == y) {
            return true;
        }
    }
    return false;
}

bool PatternLockModifier::CheckChoosePointIsLastIndex(int32_t x, int32_t y, int32_t index) const
{
    if (!choosePoint_.empty() && static_cast<int32_t>(choosePoint_.size()) >= index) {
        if (choosePoint_.at(choosePoint_.size() - static_cast<uint32_t>(index)).GetColumn() == x &&
            choosePoint_.at(choosePoint_.size() - static_cast<uint32_t>(index)).GetRow() == y) {
            return true;
        }
    }
    return false;
}

OffsetF PatternLockModifier::GetCircleCenterByXY(const OffsetF& offset, int32_t x, int32_t y)
{
    float sideLength = sideLength_->Get();
    OffsetF cellCenter;
    int32_t scale = RADIUS_TO_DIAMETER;
    cellCenter.SetX(offset.GetX() + sideLength / PATTERN_LOCK_COL_COUNT / scale * (x * scale - 1));
    cellCenter.SetY(offset.GetY() + sideLength / PATTERN_LOCK_COL_COUNT / scale * (y * scale - 1));
    return cellCenter;
}

void PatternLockModifier::SetSideLength(float sideLength)
{
    CHECK_NULL_VOID(sideLength_);
    sideLength_->Set(sideLength);
}

void PatternLockModifier::SetCircleRadius(float circleRadius)
{
    CHECK_NULL_VOID(circleRadius_);
    circleRadius_->Set(circleRadius);
}

void PatternLockModifier::SetRegularColor(const LinearColor& regularColor)
{
    CHECK_NULL_VOID(regularColor_);
    regularColor_->Set(regularColor);
}

void PatternLockModifier::SetSelectColor(const LinearColor& selectedColor)
{
    CHECK_NULL_VOID(selectedColor_);
    selectedColor_->Set(selectedColor);
}

void PatternLockModifier::SetActiveColor(const LinearColor& activeColor)
{
    CHECK_NULL_VOID(activeColor_);
    activeColor_->Set(activeColor);
}

void PatternLockModifier::SetPathColor(const LinearColor& pathColor)
{
    CHECK_NULL_VOID(pathColor_);
    pathColor_->Set(pathColor);
}

void PatternLockModifier::SetPathStrokeWidth(float pathStrokeWidth)
{
    CHECK_NULL_VOID(pathStrokeWidth_);
    pathStrokeWidth_->Set(pathStrokeWidth);
}

void PatternLockModifier::SetContentOffset(const OffsetF& offset)
{
    CHECK_NULL_VOID(offset_);
    offset_->Set(offset);
}

void PatternLockModifier::SetIsMoveEventValid(bool isMoveEventValid)
{
    isMoveEventValid_->Set(isMoveEventValid);
}

void PatternLockModifier::SetCellCenterOffset(const OffsetF& cellcenter)
{
    CHECK_NULL_VOID(cellCenter_);
    cellCenter_->Set(cellcenter);
}

void PatternLockModifier::SetChoosePoint(const std::vector<PatternLockCell>& choosePoint)
{
    choosePoint_ = choosePoint;
}
} // namespace OHOS::Ace::NG
