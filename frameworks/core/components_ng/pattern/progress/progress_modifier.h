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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {
constexpr int32_t INT32_TWO = 2;
constexpr int32_t ANGLE_90 = 90;
constexpr int32_t ANGLE_180 = 180;
constexpr int32_t ANGLE_270 = 270;
constexpr float DEFAULT_MAX_VALUE = 100.0f;
constexpr float DEFAULT_SCALE_WIDTH = 10.0f;
constexpr int32_t DEFAULT_SCALE_COUNT = 100;
constexpr double DEFAULT_CAPSULE_BORDER_WIDTH = 1.0;
constexpr float FLOAT_ZERO_FIVE = 0.5f;
constexpr float FLOAT_TWO_ZERO = 2.0f;
class ProgressModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ProgressModifier, ContentModifier);

public:
    ProgressModifier();
    ~ProgressModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetStrokeWidth(float width);
    void SetColor(LinearColor color);
    void SetBackgroundColor(LinearColor color);
    void SetBorderColor(LinearColor color);
    void SetProgressType(ProgressType type);
    void SetMaxValue(float value);
    void SetValue(float value);
    void SetScaleWidth(float value);
    void SetScaleCount(int32_t value);
    void SetOffset(const OffsetF& offset);
    void SetBorderWidth(const Dimension& width);

private:
    void ContentDrawWithFunction(DrawingContext& context);
    void PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;

    // Animatable
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<AnimatablePropertyColor> bgColor_;
    RefPtr<AnimatablePropertyColor> borderColor_;

    // no Animatable
    RefPtr<PropertyFloat> maxValue_;
    RefPtr<PropertyFloat> value_;
    RefPtr<PropertyFloat> scaleWidth_;
    RefPtr<PropertyInt> scaleCount_;
    ProgressType progressType_ = ProgressType::LINEAR;

    Dimension capsuleBorderWidth_ = Dimension(DEFAULT_CAPSULE_BORDER_WIDTH,  DimensionUnit::VP);
    OffsetF offset_ = OffsetF(0.0, 0.0);

    ACE_DISALLOW_COPY_AND_MOVE(ProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_MODIFIER_H
