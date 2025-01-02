/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_modifier.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
constexpr float DEFAULT_BORDER_WIDTH = 1.0f;

class ACE_EXPORT ProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ProgressPaintMethod, NodePaintMethod)
public:
    explicit ProgressPaintMethod(
        ProgressType progressType, float strokeWidth, const RefPtr<ProgressModifier>& progressModifier)
        : strokeWidth_(strokeWidth), progressType_(progressType), progressModifier_(progressModifier)
    {
        progressModifier_->SetProgressType(progressType_);
    }
    ~ProgressPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(progressModifier_, nullptr);
        return progressModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(progressModifier_);
        GetThemeData();
        auto paintProperty = DynamicCast<ProgressPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        auto isSensitive = paintProperty->GetIsSensitive().value_or(false);
        color_ = paintProperty->GetColor().value_or(color_);
        bgColor_ = paintProperty->GetBackgroundColor().value_or(bgColor_);
        borderColor_ = paintProperty->GetBorderColor().value_or(borderColor_);
        maxValue_ = paintProperty->GetMaxValue().value_or(maxValue_);
        value_ = paintProperty->GetValue().value_or(value_);
        scaleCount_ = paintProperty->GetScaleCount().value_or(scaleCount_);
        scaleWidth_ = paintProperty->GetScaleWidth().value_or(Dimension(scaleWidth_)).ConvertToPx();
        capsuleBorderWidth_ = paintProperty->GetBorderWidth().value_or(capsuleBorderWidth_);
        sweepEffect_ = paintProperty->GetEnableScanEffect().value_or(false);
        ringSweepEffect_ = paintProperty->GetEnableRingScanEffect().value_or(false);
        linearSweepEffect_ = paintProperty->GetEnableLinearScanEffect().value_or(false);
        bool paintShadow = paintProperty->GetPaintShadow().value_or(false);
        ProgressStatus progressStatus = paintProperty->GetProgressStatus().value_or(ProgressStatus::PROGRESSING);
        progressModifier_->SetSmoothEffect(paintProperty->GetEnableSmoothEffect().value_or(true));
        progressModifier_->SetContentOffset(paintWrapper->GetContentOffset());
        progressModifier_->SetContentSize(paintWrapper->GetContentSize());
        CalculateStrokeWidth(paintWrapper->GetContentSize());
        progressModifier_->SetSweepEffect(sweepEffect_);
        progressModifier_->SetRingSweepEffect(ringSweepEffect_);
        progressModifier_->SetLinearSweepEffect(linearSweepEffect_);
        progressModifier_->SetStrokeWidth(strokeWidth_);
        progressModifier_->SetBorderWidth(capsuleBorderWidth_.ConvertToPx());
        progressModifier_->SetColor(LinearColor(color_));
        progressModifier_->SetBackgroundColor(LinearColor(bgColor_));
        progressModifier_->SetBorderColor(LinearColor(borderColor_));
        progressModifier_->SetProgressType(progressType_);
        progressModifier_->SetProgressStatus(progressStatus);
        progressModifier_->SetScaleWidth(scaleWidth_);
        progressModifier_->SetScaleCount(scaleCount_);
        auto ringProgressColor = GenerateRingProgressColor(paintWrapper);
        progressModifier_->SetRingProgressColor(ringProgressColor);
        progressModifier_->SetPaintShadow(paintShadow);
        isItalic_ = paintProperty->GetItalicFontStyle() != Ace::FontStyle::NORMAL;
        progressModifier_->SetIsItalic(isItalic_);
        progressModifier_->SetMaxValue(maxValue_);
        progressModifier_->SetValue(isSensitive ? 0.0 : value_);
        auto strokeRadius = static_cast<float>(
            paintProperty->GetStrokeRadiusValue(Dimension(strokeWidth_ / 2.0f, DimensionUnit::VP)).ConvertToPx());
        strokeRadius = std::min(strokeWidth_ / 2, strokeRadius);
        progressModifier_->SetStrokeRadius(strokeRadius);
        SetCapsuleBorderRadius(paintWrapper);
        UpdateCapsuleProgress(paintWrapper);
    }

    void GetThemeData();
    void CalculateStrokeWidth(const SizeF& contentSize);

private:
    Gradient GenerateRingProgressColor(PaintWrapper* paintWrapper);
    void SetCapsuleBorderRadius(PaintWrapper* paintWrapper);
    void UpdateCapsuleProgress(PaintWrapper* paintWrapper);

    Color color_ = Color::BLUE;
    Color bgColor_ = Color::GRAY;
    Color borderColor_ = Color::GRAY;
    float strokeWidth_ = 0.0f;
    float scaleWidth_ = 0.0f;
    int32_t scaleCount_ = 0;
    float maxValue_ = 100.0f;
    float value_ = 0.0f;
    Dimension capsuleBorderWidth_ = Dimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP);
    Color ringProgressEndSideColor_ = Color::BLUE;
    Color ringProgressBeginSideColor_ = Color::BLUE;

    Color capsuleBgFocusedColor_;
    Color capsuleSelectFocusedColor_;
    Color capsuleInprogressBgColor_;
    Color capsuleInprogressBorderColor_;
    Dimension capsuleInprogressBorderWidth_;
    Color defaultBorderColor_;
    Dimension defaultBorderWidth_;

    ProgressType progressType_ = ProgressType::LINEAR;
    RefPtr<ProgressModifier> progressModifier_;
    bool sweepEffect_ = false;
    bool ringSweepEffect_ = false;
    bool linearSweepEffect_ = false;
    bool isItalic_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
