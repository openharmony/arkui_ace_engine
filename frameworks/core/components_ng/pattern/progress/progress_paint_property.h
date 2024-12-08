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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ProgressPaintProperty, PaintProperty);

public:
    ProgressPaintProperty() = default;

    ~ProgressPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ProgressPaintProperty>();
        paintProperty->propProgressPaintDate_ = CloneProgressPaintDate();
        paintProperty->propColor_ = CloneColor();
        paintProperty->propBackgroundColor_ = CloneBackgroundColor();
        paintProperty->propProgressType_ = CloneProgressType();
        paintProperty->propBorderColor_ = CloneBorderColor();
        paintProperty->propGradientColor_ = CloneGradientColor();
        paintProperty->propPaintShadow_ = ClonePaintShadow();
        paintProperty->propProgressStatus_ = CloneProgressStatus();
        paintProperty->propEnableSmoothEffect_ = CloneEnableSmoothEffect();
        paintProperty->propIsSensitive_ = CloneIsSensitive();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetProgressPaintDate();
        ResetColor();
        ResetBackgroundColor();
        ResetProgressType();
        ResetBorderColor();
        ResetGradientColor();
        ResetPaintShadow();
        ResetProgressStatus();
        ResetEnableSmoothEffect();
        ResetIsSensitive();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    std::string ProgressOptions() const;
    void ToJsonValueForCapsule(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    std::string ToJsonGradientColor() const;

    ACE_DEFINE_PROPERTY_GROUP(ProgressPaintDate, ProgressDate);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, MaxValue, double, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Value, double, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ScaleCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ScaleWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, BorderWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, TextSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Text, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableScanEffect, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ProgressPaintDate, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, TextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableRingScanEffect, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableLinearScanEffect, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, EnableShowText, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, StrokeRadius, Dimension, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressType, ProgressType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColor, Gradient, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PaintShadow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressStatus, ProgressStatus, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableSmoothEffect, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSensitive, bool, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PAINT_PROPERTY_H
