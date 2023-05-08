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
#include "base/geometry/arc.h"
#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
struct RingProgressData {
    PointF centerPt;
    float radius = 0.0f;
    float thickness = 0.0f;
    float angle = 0.0f;
    float shadowBlurSigma = 0.0f;
};

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
    void SetContentOffset(const OffsetF& offset);
    void SetContentSize(const SizeF& contentSize);
    void SetBorderWidth(float width);
    void SetSweepEffect(bool value);
    void SetVisible(bool visible)
    {
        isVisible_ = visible;
    }
    void SetRingProgressColor(const Gradient& color);
    void SetPaintShadow(bool paintShadow);
    void SetProgressStatus(ProgressStatus status);

private:
    void ContentDrawWithFunction(DrawingContext& context);
    void PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintRingBackground(RSCanvas& canvas, const RingProgressData& ringProgressData) const;
    void PaintRingProgressOrShadow(RSCanvas& canvas, const RingProgressData& ringProgressData, bool isShadow) const;
    void PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;

    void StartLightSweepAnimation(ProgressType type, float value);
    void StartCapsuleProgressLightSweep(float value);
    void StartCapsuleProgressLightSweepImpl(float value);
    void PaintCapsuleLightSweep(RSCanvas& canvas, const SizeF& contentSize,
        const OffsetF& offset, const RSPath& path, bool isVertical) const;
    Gradient CreateGradient() const;

    // Animatable
    RefPtr<AnimatablePropertyFloat> strokeWidth_; // After adjusting to the content width and height
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<AnimatablePropertyColor> bgColor_;
    RefPtr<AnimatablePropertyColor> borderColor_;
    RefPtr<AnimatablePropertyFloat> capsuleDate_;
    RefPtr<AnimatablePropertyVectorColor> ringProgressColors_;

    // no Animatable
    RefPtr<PropertyFloat> value_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyFloat> maxValue_;
    RefPtr<PropertyFloat> scaleWidth_;
    RefPtr<PropertyInt> scaleCount_;
    RefPtr<PropertyInt> progressType_;
    RefPtr<PropertyFloat> capsuleBorderWidth_;
    RefPtr<PropertyBool> sweepEffect_;
    RefPtr<PropertyBool> paintShadow_;
    RefPtr<PropertyInt> progressStatus_;
    float sweepingDateBackup_ = 0.0f;
    bool sweepingDateUpdated_ = false;
    bool isSweeping_ = false;
    bool isVisible_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(ProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_MODIFIER_H
