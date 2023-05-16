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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_MODIFIER_H

#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class PatternLockCell {
public:
    PatternLockCell(int32_t column, int32_t row);
    ~PatternLockCell() = default;
    int32_t GetColumn() const
    {
        return column_;
    }
    int32_t GetRow() const
    {
        return row_;
    }
    int32_t GetCode() const
    {
        return code_;
    }

private:
    int32_t column_;
    int32_t row_;
    int32_t code_;
};

class PatternLockModifier : public ContentModifier {
    DECLARE_ACE_TYPE(PatternLockModifier, ContentModifier);

public:
    PatternLockModifier();

    ~PatternLockModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetSideLength(float sideLength);
    void SetCircleRadius(float circleRadius);
    void SetRegularColor(const LinearColor& regularColor);
    void SetSelectColor(const LinearColor& selectedColor);
    void SetActiveColor(const LinearColor& activeColor);
    void SetPathColor(const LinearColor& pathColor);
    void SetPathStrokeWidth(float pathStrokeWidth);
    void SetIsMoveEventValid(bool isMoveEventValid);
    void SetCellCenterOffset(const OffsetF& cellCenter);
    void SetContentOffset(const OffsetF& offset);
    void SetChoosePoint(const std::vector<PatternLockCell>& choosePoint);

private:
    void PaintLockLine(RSCanvas& canvas, const OffsetF& offset);
    void PaintLockCircle(RSCanvas& canvas, const OffsetF& offset, int32_t x, int32_t y);

    bool CheckChoosePoint(int32_t x, int32_t y) const;
    bool CheckChoosePointIsLastIndex(int32_t x, int32_t y, int32_t index) const;
    OffsetF GetCircleCenterByXY(const OffsetF& offset, int32_t x, int32_t y);

    RefPtr<AnimatablePropertyColor> regularColor_;
    RefPtr<AnimatablePropertyColor> selectedColor_;
    RefPtr<AnimatablePropertyColor> activeColor_;
    RefPtr<AnimatablePropertyColor> pathColor_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertyFloat> sideLength_;
    RefPtr<PropertyFloat> circleRadius_;
    RefPtr<PropertyFloat> pathStrokeWidth_;
    RefPtr<PropertyBool> isMoveEventValid_;
    RefPtr<PropertyOffsetF> cellCenter_;

    std::vector<PatternLockCell> choosePoint_;

    ACE_DISALLOW_COPY_AND_MOVE(PatternLockModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_MODIFIER_H
