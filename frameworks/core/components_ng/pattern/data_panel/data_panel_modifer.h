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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H

#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {

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

    void SetDate(float date)
    {
        if (date_) {
            AnimationOption option = AnimationOption();
            RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
            option.SetDuration(200);
            option.SetDelay(0);
            option.SetCurve(curve);
            option.SetIteration(1);
            option.SetTempo(0.2f);
            AnimationUtils::Animate(option, [&]() {
                date_->Set(date);
            });
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
    RefPtr<AnimatablePropertyFloat> date_;
    std::vector<double> values_;
    double max_;
    size_t dataPanelType_;
    bool effect_;
    OffsetF offset_;

    ACE_DISALLOW_COPY_AND_MOVE(DataPanelModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_DATA_PANEL_MODIFIER_H