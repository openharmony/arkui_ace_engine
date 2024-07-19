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
#include "core/components_ng/pattern/patternlock/patternlock_challenge.h"
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
    void SetRegularColor(const Color& regularColor);
    void SetSelectColor(const Color& selectedColor);
    void SetActiveColor(const Color& activeColor);
    void SetPathColor(const LinearColor& pathColor);
    void SetHoverColor(const Color& hoverColor);
    void SetWrongColor(const Color& wrongColor);
    void SetCorrectColor(const Color& correctColor);
    void SetPathStrokeWidth(float pathStrokeWidth);
    void SetIsMoveEventValid(bool isMoveEventValid);
    void SetIsHover(bool isHover);
    void SetHoverIndex(int32_t hoverIndex);
    void SetChallengeResult(std::optional<NG::PatternLockChallengeResult>& challengeResult);
    void SetCellCenterOffset(const OffsetF& cellCenter);
    void SetContentOffset(const OffsetF& offset);
    void SetChoosePoint(const std::vector<PatternLockCell>& choosePoint);
    size_t GetChoosePointCount()
    {
        return choosePoint_.size();
    }
    void SetActiveCircleRadiusScale(float scale);
    void SetBackgroundCircleRadiusScale(float scale);
    void SetLightRingRadiusStartScale(float scale);
    void SetLightRingRadiusEndScale(float scale);
    void SetHoverRadiusScale(float scale);
    void StartConnectedCircleAnimate(int32_t x, int32_t y);
    void StartConnectedLineAnimate(int32_t x, int32_t y);
    void StartCanceledAnimate();
    void Reset();
    void SetIsTouchDown(bool isTouchDown);
    void UpdateBoundsRect();
    void SetActiveCircleColor(const LinearColor& activeCircleColor);
    void SetActiveBackgroundRadius(float activeBackgroundRadius);
    void SetEnableWaveEffect(bool enableWaveEffect);

private:
    void DrawForApiNine(DrawingContext& context);
    void PaintLockLineForApiNine(RSCanvas& canvas, const OffsetF& offset);
    void PaintLockCircleForApiNine(RSCanvas& canvas, const OffsetF& offset, int32_t x, int32_t y);
    void PaintLockLine(RSCanvas& canvas, const OffsetF& offset);
    void PaintLockCircle(RSCanvas& canvas, const OffsetF& offset, int32_t x, int32_t y);
    void CheckIsHoverAndPaint(RSCanvas& canvas, float offsetX, float offsetY, float radius, int32_t index);
    void PaintCircle(RSCanvas& canvas, float offsetX, float offsetY, float radius, const RSColor& circleColor);
    void PaintLightRing(RSCanvas& canvas, float offsetX, float offsetY, float radius, float alphaF);
    void AddConnectedLineToPath(RSPath& path, const OffsetF& offset);
    void AddCanceledLineToPath(RSPath& path, const OffsetF& offset);
    void SetConnectedLineTailPoint(int32_t x, int32_t y);
    void SetCanceledLineTailPoint();
    OffsetF GetConnectedLineTailPoint() const;
    OffsetF GetCanceledLineTailPoint() const;
    OffsetF GetPointEndByCellCenter() const;

    bool CheckChoosePoint(int32_t x, int32_t y) const;
    bool CheckChoosePointIsLastIndex(int32_t x, int32_t y, int32_t index) const;
    void SetBackgroundCircleRadius(int32_t index);
    void SetActiveCircleRadius(int32_t index);
    void SetLightRingCircleRadius(int32_t index);
    void SetLightRingAlphaF(int32_t index);
    float GetLightRingAlphaF(int32_t index) const;
    float GetBackgroundCircleRadius(int32_t index) const;
    float GetActiveCircleRadius(int32_t index) const;
    float GetLightRingCircleRadius(int32_t index) const;

    OffsetF GetCircleCenterByXY(const OffsetF& offset, int32_t x, int32_t y);
    void CreateProperties();
    void AttachProperties();
    void StartChallengeResultAnimate();
    void SetCircleClip(RSCanvas& canvas);

    RefPtr<PropertyColor> regularColor_;
    RefPtr<PropertyColor> selectedColor_;
    RefPtr<PropertyColor> activeColor_;
    RefPtr<PropertyColor> hoverColor_;
    RefPtr<PropertyColor> wrongColor_;
    RefPtr<PropertyColor> correctColor_;
    RefPtr<AnimatablePropertyColor> pathColor_;
    RefPtr<AnimatablePropertyColor> activeCircleColor_;
    RefPtr<AnimatablePropertyOffsetF> connectedLineTailPoint_;
    RefPtr<AnimatablePropertyOffsetF> canceledLineTailPoint_;
    RefPtr<AnimatablePropertyColor> pointAnimateColor_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertyFloat> sideLength_;
    RefPtr<PropertyFloat> circleRadius_;
    RefPtr<PropertyFloat> pathStrokeWidth_;
    RefPtr<PropertyFloat> activeBackgroundRadius_;
    RefPtr<PropertyBool> isMoveEventValid_;
    RefPtr<PropertyBool> isHover_;
    RefPtr<PropertyBool> enableWaveEffect_;
    RefPtr<PropertyInt> hoverIndex_;
    std::optional<NG::PatternLockChallengeResult> challengeResult_;
    RefPtr<PropertyOffsetF> cellCenter_;
    std::vector<RefPtr<AnimatablePropertyFloat>> backgroundCircleRadius_;
    std::vector<RefPtr<AnimatablePropertyFloat>> activeCircleRadius_;
    std::vector<RefPtr<AnimatablePropertyFloat>> lightRingRadius_;
    std::vector<RefPtr<AnimatablePropertyFloat>> lightRingAlphaF_;
    std::vector<PatternLockCell> choosePoint_;

    float scaleActiveCircleRadius_ = 1.0f;
    float scaleBackgroundCircleRadius_ = 1.0f;
    float scaleLightRingRadiusStart_ = 1.0f;
    float scaleLightRingRadiusEnd_ = 1.0f;
    float hoverRadiusScale_ = 1.0f;
    bool isTouchDown_ = false;
    bool needCanceledLine_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(PatternLockModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_MODIFIER_H
