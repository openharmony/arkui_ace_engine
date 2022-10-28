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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;

class PatternLockCell {
public:
    PatternLockCell(int16_t column, int16_t row)
    {
        column_ = column;
        row_ = row;
        code_ = PATTERN_LOCK_COL_COUNT * (row - 1) + (column - 1);
    };
    ~PatternLockCell() = default;
    int16_t GetColumn() const
    {
        return column_;
    }
    int16_t GetRow() const
    {
        return row_;
    }
    int16_t GetCode() const
    {
        return code_;
    }

private:
    int16_t column_;
    int16_t row_;
    int16_t code_;
};

class PatternLockPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(PatternLockPaintMethod, NodePaintMethod)

public:
    PatternLockPaintMethod(std::vector<PatternLockCell>& choosePoint, OffsetF& cellCenter, bool isMoveEventValid)
        : choosePoint_(choosePoint), cellCenter_(cellCenter), isMoveEventValid_(isMoveEventValid) {};

    ~PatternLockPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintLockLine(RSCanvas& canvas, const OffsetF& offset);
    void PaintLockCircle(RSCanvas& canvas, const OffsetF& offset, int16_t x, int16_t y);

    bool CheckChoosePoint(int16_t x, int16_t y) const;
    bool CheckChoosePointIsLastIndex(int16_t x, int16_t y, int16_t index) const;
    void InitializeParam(const RefPtr<PatternLockPaintProperty>& patternLockPaintProperty);
    OffsetF GetCircleCenterByXY(const OffsetF& offset, int16_t x, int16_t y);

    Dimension sideLength_;
    Dimension circleRadius_;
    Color regularColor_;
    Color selectedColor_;
    Color activeColor_;
    Color pathColor_;
    Dimension pathStrokeWidth_;
    bool autoReset_ {};

    std::vector<PatternLockCell> choosePoint_;
    OffsetF cellCenter_;
    bool isMoveEventValid_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H
