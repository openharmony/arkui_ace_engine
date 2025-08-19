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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H

#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
constexpr int32_t ANIMATION_DURATION = 1200;        // The circle animation duration is 1200ms
constexpr int32_t ANIMATION_DELAY = 0;              // The circle animation delay is 0ms
constexpr int32_t ANIMATION_TIMES = 1;              // The circle animation repeat times is 1
constexpr float ANIMATION_START = 0.0f;             // The circle animation start from 0.0
constexpr float ANIMATION_END = 1.0f;               // The circle animation end with 1.0
constexpr float ANIMATION_CURVE_VELOCITY = 0.0f;    // The circle animation spring curve velocity is 0.0
constexpr float ANIMATION_CURVE_MASS = 1.0f;        // The circle animation spring curve mass is 1.0
constexpr float ANIMATION_CURVE_STIFFNESS = 110.0f; // The circle animation spring curve stiffness is 110.0
constexpr float ANIMATION_CURVE_DAMPING = 17.0f;    // The circle animation spring curve damping is 17.0
constexpr size_t MAX_COUNT = 9;
constexpr float DEFAULT_MAX_VALUE = 100.0f;
constexpr float START_ANGLE = 0.0f;
struct ArcData {
    Offset center;
    float progressValue = 0.0f;
    float radius = 0.0f;
    float thickness = 0.0f;
    double maxValue = 0.0;
    double totalValue = 0.0f;
    Gradient progressColors;
    Gradient shadowColor;
    float drawAngle = 0.0f;
    float gradientPointBase = 0.0f;
    float lastAngle = 0.0f;
    float totalAllValue = 0.0f;
    float totalDrawAngle = 0.0f;
    float circleAngle = 0.0f;
};
struct LinearData {
    OffsetF offset;

    Gradient segmentColor;
    Gradient segmentShadowColor;

    float segmentWidth = 0.0f;
    float xSegment = 0.0f;
    float height = 0.0f;
    float totalWidth = 0.0f;

    bool isFirstData = false;
    bool isEndData = false;
};
class DataPanelModifier : public ContentModifier {
    DECLARE_ACE_TYPE(DataPanelModifier, ContentModifier);

public:
    DataPanelModifier(const WeakPtr<Pattern>& pattern);
    ~DataPanelModifier() override = default;
    void onDraw(DrawingContext& context) override;
    void UpdateDate();

    void SetValues(std::vector<double> values)
    {
        for (size_t i = 0; i < values.size(); ++i) {
            if (i >= MAX_COUNT) {
                return;
            }
            values_[i]->Set(values[i]);
        }
        valuesLastLength_ = values.size();
    };

    void SetMax(double max)
    {
        max_->Set(max);
    };

    void SetDataPanelType(size_t dataPanelType)
    {
        if (isFirstCreate_) {
            dataPanelType_ = dataPanelType;
            isFirstCreate_ = false;
        }
    };

    void SetEffect(bool effect)
    {
        isEffect_->Set(effect);
    };

    void SetOffset(OffsetF offset)
    {
        offset_ = offset;
    };

    void SetValueColors(const std::vector<Gradient>& valueColors)
    {
        for (size_t i = 0; i < valueColors.size(); ++i) {
            if (i >= MAX_COUNT) {
                return;
            }
            valueColors_[i]->Set(GradientArithmetic(valueColors[i]));
        }
    };

    void SetTrackBackground(const Color& trackBackgroundColor)
    {
        trackBackgroundColor_->Set(LinearColor(trackBackgroundColor));
    };

    void SetStrokeWidth(float strokeWidth)
    {
        strokeWidth_->Set(strokeWidth);
    };

    void SetShadowVisible(bool isShadowVisible)
    {
        isShadowVisible_ = isShadowVisible;
    };

    void SetIsHasShadowValue(bool isHasShadowValue)
    {
        isHasShadowValue_ = isHasShadowValue;
    };

    void SetShadowRadius(float shadowRadius)
    {
        shadowRadiusFloat_->Set(shadowRadius);
    };

    void SetShadowOffsetX(float shadowOffsetX)
    {
        shadowOffsetXFloat_->Set(shadowOffsetX);
    };

    void SetShadowOffsetY(float shadowOffsetY)
    {
        shadowOffsetYFloat_->Set(shadowOffsetY);
    };

    void SetShadowColors(const std::vector<Gradient>& valueColors, const size_t shadowColorsLastLength)
    {
        for (size_t i = 0; i < valueColors.size(); ++i) {
            if (i >= MAX_COUNT) {
                return;
            }
            shadowColors_[i]->Set(GradientArithmetic(valueColors[i]));
        }
        shadowColorsLastLength_ = std::min(shadowColorsLastLength, valuesLastLength_);
    };

    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

    void SetIsRtl(bool isRtl)
    {
        isRtl_ = isRtl;
    };

private:
    void PaintCircle(DrawingContext& context, OffsetF offset) const;
    void PaintLinearProgress(DrawingContext& context, OffsetF offset) const;
    void PaintBackground(RSCanvas& canvas, OffsetF offset, float totalWidth, float height, float segmentWidth) const;
    void SetCornerRadius(RSRoundRect& paintRect, const LinearData& segmentLinearData, const float height) const;
    void PaintColorSegment(RSCanvas& canvas, const LinearData& segmentLinearData) const;
    void PaintSpace(RSCanvas& canvas, const LinearData& segmentLinearData, float spaceWidth) const;
    void PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const;
    void PaintProgress(RSCanvas& canvas, ArcData arcData, RSPath& path, RSPath& endPath, bool isShadow) const;
    void GetPaintPath(ArcData& arcData, RSPath& path, RSPath& endPath) const;
    void Path2DArc(
        RSPath& path, double x, double y, double r, double startAngle, double endAngle, bool counterclockwise) const;
    void PaintColorSegmentFilterMask(RSCanvas& canvas, const LinearData& segmentLinearData) const;
    Gradient SortGradientColorsOffset(const Gradient& srcGradient) const;
    RefPtr<AnimatablePropertyFloat> date_;
    RefPtr<PropertyBool> isEffect_;
    size_t dataPanelType_ = 0;
    OffsetF offset_;
    bool isFirstCreate_ = true;
    bool isHasShadowValue_ = false;
    bool isRtl_ = false;
    RefPtr<PropertyBool> useContentModifier_;
    
    RefPtr<AnimatablePropertyFloat> max_;
    std::vector<RefPtr<AnimatablePropertyFloat>> values_;
    std::vector<RefPtr<AnimatablePropertyVectorColor>> valueColors_;
    RefPtr<AnimatablePropertyColor> trackBackgroundColor_;
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    WeakPtr<Pattern> pattern_;

    // shadow param
    bool isShadowVisible_ = false;
    RefPtr<AnimatablePropertyFloat> shadowRadiusFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetXFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetYFloat_;
    std::vector<RefPtr<AnimatablePropertyVectorColor>> shadowColors_;
    size_t shadowColorsLastLength_ = MAX_COUNT;
    size_t valuesLastLength_ = MAX_COUNT;

    ACE_DISALLOW_COPY_AND_MOVE(DataPanelModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H
