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
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
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

struct ArcData {
    Offset center;
    float progress = 0.0f;
    float radius = 0.0f;
    float thickness = 0.0f;
    double maxValue = 0.0;
    Color startColor;
    Color endColor;

    float wholeAngle = 360.0f;
    float startAngle = 0.0f;
};

class DataPanelModifier : public ContentModifier {
    DECLARE_ACE_TYPE(DataPanelModifier, ContentModifier);

public:
    DataPanelModifier();
    ~DataPanelModifier() override = default;
    void onDraw(DrawingContext& context) override
    {
        float date = date_->Get();
        RSCanvas canvas = context.canvas;
        if (dataPanelType_ == 0) {
            PaintCircle(context, offset_, date);
        } else {
            PaintLinearProgress(context, offset_);
        }
    }

    void PaintCircle(DrawingContext& context, OffsetF offset, float date) const;
    void PaintLinearProgress(DrawingContext& context, OffsetF offset) const;
    void PaintBackground(RSCanvas& canvas, OffsetF offset, float totalWidth, float height) const;
    void PaintColorSegment(RSCanvas& canvas, OffsetF offset, float segmentWidth, float xSpace, float height,
        const Color segmentStartColor, const Color segmentEndColor) const;
    void PaintSpace(RSCanvas& canvas, OffsetF offset, float spaceWidth, float xSpace, float height) const;
    void PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const;
    void PaintProgress(RSCanvas& canvas, ArcData arcData, bool useEffect = false, bool useAnimator = false,
        float percent = 0.0f) const;

    void UpdateDate()
    {
        if (date_) {
            // When the date update, the animation will repeat once.
            LOGI("Data panel animatableProperty is updating, the animation will start from 0.0 to 1.0.");
            date_->Set(ANIMATION_START);
            AnimationOption option = AnimationOption();
            RefPtr<Curve> curve = AceType::MakeRefPtr<SpringCurve>(
                ANIMATION_CURVE_VELOCITY, ANIMATION_CURVE_MASS, ANIMATION_CURVE_STIFFNESS, ANIMATION_CURVE_DAMPING);
            option.SetDuration(ANIMATION_DURATION);
            option.SetDelay(ANIMATION_DELAY);
            option.SetCurve(curve);
            option.SetIteration(ANIMATION_TIMES);
            AnimationUtils::Animate(option, [&]() { date_->Set(ANIMATION_END); });
        }
    }

    void SetValues(std::vector<double> values)
    {
        values_ = values;
    };

    void SetMax(double max)
    {
        max_ = max;
    };

    void SetDataPanelType(size_t dataPanelType)
    {
        dataPanelType_ = dataPanelType;
    };

    void SetEffect(bool effect)
    {
        effect_ = effect;
    };

    void SetOffset(OffsetF offset)
    {
        offset_ = offset;
    };

private:
    void PaintRainbowFilterMask(RSCanvas& canvas, double factor, ArcData arcData) const;
    RefPtr<AnimatablePropertyFloat> date_;
    std::vector<double> values_;
    double max_;
    size_t dataPanelType_;
    bool effect_ = true;
    OffsetF offset_;

    ACE_DISALLOW_COPY_AND_MOVE(DataPanelModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H