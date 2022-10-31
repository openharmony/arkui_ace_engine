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
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"

#include <optional>

#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

namespace OHOS::Ace::NG {

constexpr int32_t RADIUS_TO_DIAMETER = 2;
constexpr int16_t scale = RADIUS_TO_DIAMETER;
constexpr float SCALE_ACTIVE_CIRCLE_RADIUS = 16.00 / 14.00;
constexpr float GRADUAL_CHANGE_POINT = 0.5;

CanvasDrawFunction PatternLockPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    const auto& paintProperty = DynamicCast<PatternLockPaintProperty>(paintWrapper->GetPaintProperty());
    InitializeParam(paintProperty);
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto patternlock = weak.Upgrade();
        auto offset = paintWrapper->GetGeometryNode()->GetContentOffset();
        if (patternlock) {
            patternlock->PaintLockLine(canvas, offset);
            for (int i = 0; i < PATTERN_LOCK_COL_COUNT; i++) {
                for (int j = 0; j < PATTERN_LOCK_COL_COUNT; j++) {
                    patternlock->PaintLockCircle(canvas, offset, i + 1, j + 1);
                }
            }
        }
    };
    return paintFunc;
}

void PatternLockPaintMethod::InitializeParam(const RefPtr<PatternLockPaintProperty>& patternLockPaintProperty)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto patternLockTheme = pipeline->GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    if (patternLockPaintProperty->HasSideLength()) {
        sideLength_ = patternLockPaintProperty->GetSideLengthValue();
    } else {
        sideLength_ = 300.0_vp;
    }
    if (patternLockPaintProperty->HasCircleRadius()) {
        circleRadius_ = patternLockPaintProperty->GetCircleRadiusValue();
    } else {
        circleRadius_ = 14.0_vp;
    }
    if (patternLockPaintProperty->HasRegularColor()) {
        regularColor_ = patternLockPaintProperty->GetRegularColorValue();
    } else {
        regularColor_ = patternLockTheme->GetRegularColor();
    }
    if (patternLockPaintProperty->HasSelectedColor()) {
        selectedColor_ = patternLockPaintProperty->GetSelectedColorValue();
    } else {
        selectedColor_ = patternLockTheme->GetSelectedColor();
    }
    if (patternLockPaintProperty->HasActiveColor()) {
        activeColor_ = patternLockPaintProperty->GetActiveColorValue();
    } else {
        activeColor_ = patternLockTheme->GetActiveColor();
    }
    if (patternLockPaintProperty->HasPathColor()) {
        pathColor_ = patternLockPaintProperty->GetPathColorValue();
    } else {
        pathColor_ = patternLockTheme->GetPathColor();
    }
    if (patternLockPaintProperty->HasPathStrokeWidth()) {
        pathStrokeWidth_ = patternLockPaintProperty->GetPathStrokeWidthValue();
    } else {
        pathStrokeWidth_ = 34.0_vp;
    }
    if (patternLockPaintProperty->HasAutoReset()) {
        autoReset_ = patternLockPaintProperty->GetAutoResetValue();
    } else {
        autoReset_ = true;
    }
}

OffsetF PatternLockPaintMethod::GetCircleCenterByXY(const OffsetF& offset, int16_t x, int16_t y)
{
    OffsetF cellCenter;
    cellCenter.SetX(offset.GetX() + sideLength_.ConvertToPx() / PATTERN_LOCK_COL_COUNT / scale * (x * scale - 1));
    cellCenter.SetY(offset.GetY() + sideLength_.ConvertToPx() / PATTERN_LOCK_COL_COUNT / scale * (y * scale - 1));
    return cellCenter;
}

void PatternLockPaintMethod::PaintLockLine(RSCanvas& canvas, const OffsetF& offset)
{
    constexpr int32_t MAX_ALPHA = 255;
    size_t count = choosePoint_.size();
    if (count == 0) {
        return;
    }

    if (LessOrEqual(pathStrokeWidth_.Value(), 0.0)) {
        return;
    }

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(pathColor_));
    pen.SetWidth(pathStrokeWidth_.ConvertToPx());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    Color pathColorAlpha255 = pathColor_.ChangeAlpha(MAX_ALPHA);
    pen.SetColor(pathColorAlpha255.GetValue());
    canvas.AttachPen(pen);
    for (size_t i = 0; i < count - 1; i++) {
        OffsetF pointBegin = GetCircleCenterByXY(offset, choosePoint_[i].GetColumn(), choosePoint_[i].GetRow());
        OffsetF pointEnd = GetCircleCenterByXY(offset, choosePoint_[i + 1].GetColumn(), choosePoint_[i + 1].GetRow());
        canvas.DrawLine(RSPoint(pointBegin.GetX(), pointBegin.GetY()), RSPoint(pointEnd.GetX(), pointEnd.GetY()));
    }
    if (count > 0 && isMoveEventValid_) {
        OffsetF pointBegin =
            GetCircleCenterByXY(offset, choosePoint_[count - 1].GetColumn(), choosePoint_[count - 1].GetRow());
        float x1 = pointBegin.GetX();
        float y1 = pointBegin.GetY();
        float x2 = offset.GetX() + cellCenter_.GetX();
        float y2 = offset.GetY() + cellCenter_.GetY();
        x2 = x2 > offset.GetX() + sideLength_.ConvertToPx() ? offset.GetX() + sideLength_.ConvertToPx() : x2;
        x2 = x2 < offset.GetX() ? offset.GetX() : x2;
        y2 = y2 > offset.GetY() + sideLength_.ConvertToPx() ? offset.GetY() + sideLength_.ConvertToPx() : y2;
        y2 = y2 < offset.GetY() ? offset.GetY() : y2;

        std::vector<rosen::ColorQuad> colors = { pathColorAlpha255.GetValue(), pathColorAlpha255.GetValue(),
            pathColorAlpha255.ChangeOpacity(0.0).GetValue() };
        std::vector<rosen::scalar> pos = { 0.0, GRADUAL_CHANGE_POINT, 1.0 };
        auto shader = pen.GetShaderEffect();
        shader->CreateLinearGradient(RSPoint(x1, y1), RSPoint(x2, y2), colors, pos, rosen::TileMode::CLAMP);
        pen.SetShaderEffect(shader);
        canvas.DrawLine(RSPoint(x1, y1), RSPoint(x2, y2));
    }
    canvas.DetachPen();
    canvas.Restore();
}

void PatternLockPaintMethod::PaintLockCircle(RSCanvas& canvas, const OffsetF& offset, int16_t x, int16_t y)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(regularColor_));

    OffsetF cellcenter = GetCircleCenterByXY(offset, x, y);
    float offsetX = cellcenter.GetX();
    float offsetY = cellcenter.GetY();
    if (CheckChoosePoint(x, y)) {
        const int16_t lastIndexFir = 1;
        if (CheckChoosePointIsLastIndex(x, y, lastIndexFir)) {
            if (isMoveEventValid_) {
                brush.SetColor(ToRSColor(activeColor_));
                canvas.AttachBrush(brush);
                canvas.DrawCircle(
                    RSPoint(offsetX, offsetY), circleRadius_.ConvertToPx() * 2 * SCALE_ACTIVE_CIRCLE_RADIUS);
            } else {
                brush.SetColor(ToRSColor(selectedColor_));
                canvas.AttachBrush(brush);
                canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius_.ConvertToPx() * SCALE_ACTIVE_CIRCLE_RADIUS);
            }
        } else {
            brush.SetColor(ToRSColor(selectedColor_));
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius_.ConvertToPx() * SCALE_ACTIVE_CIRCLE_RADIUS);
        }
    } else {
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(offsetX, offsetY), circleRadius_.ConvertToPx());
    }
}

bool PatternLockPaintMethod::CheckChoosePoint(int16_t x, int16_t y) const
{
    for (auto it : choosePoint_) {
        if (it.GetColumn() == x && it.GetRow() == y) {
            return true;
        }
    }
    return false;
}

bool PatternLockPaintMethod::CheckChoosePointIsLastIndex(int16_t x, int16_t y, int16_t index) const
{
    if (!choosePoint_.empty() && static_cast<int16_t>(choosePoint_.size()) >= index) {
        if (choosePoint_.at(choosePoint_.size() - static_cast<uint32_t>(index)).GetColumn() == x &&
            choosePoint_.at(choosePoint_.size() - static_cast<uint32_t>(index)).GetRow() == y) {
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace::NG
