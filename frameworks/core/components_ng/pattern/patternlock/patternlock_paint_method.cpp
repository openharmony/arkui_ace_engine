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

#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"

namespace OHOS::Ace::NG {
void PatternLockPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(patternlockModifier_);
    GetThemeProp();
    auto paintProperty = DynamicCast<PatternLockPaintProperty>(paintWrapper->GetPaintProperty());

    CHECK_NULL_VOID(paintProperty);
    sideLength_ = paintWrapper->GetContentSize().Width();
    circleRadius_ = paintProperty->GetCircleRadius().value_or(circleRadius_);
    regularColor_ = paintProperty->GetRegularColor().value_or(regularColor_);
    selectedColor_ = paintProperty->GetSelectedColor().value_or(selectedColor_);
    activeColor_ = paintProperty->GetActiveColor().value_or(activeColor_);
    pathColor_ = paintProperty->GetPathColor().value_or(pathColor_);
    activeCircleColor_ = paintProperty->GetActiveCircleColor().value_or(pathColor_);
    if (activeCircleColor_ == Color::TRANSPARENT) {
        activeCircleColor_ = paintProperty->GetPathColor().value_or(pathColor_);
    }
    pathStrokeWidth_ = paintProperty->GetPathStrokeWidth().value_or(pathStrokeWidth_);
    backgroundCircleRadius_ = paintProperty->GetActiveCircleRadius().value_or(Dimension(0.0f, DimensionUnit::VP));
    enableWaveEffect_ = paintProperty->GetEnableWaveEffect().value_or(true);
    enableForeground_ = paintProperty->GetEnableForeground().value_or(false);

    patternlockModifier_->SetRegularColor(regularColor_);
    patternlockModifier_->SetSelectColor(selectedColor_);
    patternlockModifier_->SetActiveColor(activeColor_);
    patternlockModifier_->SetPathColor(LinearColor(pathColor_));
    patternlockModifier_->SetHoverColor(hoverColor_);
    patternlockModifier_->SetWrongColor(wrongColor_);
    patternlockModifier_->SetCorrectColor(correctColor_);
    patternlockModifier_->SetIsMoveEventValid(isMoveEventValid_);
    patternlockModifier_->SetCellCenterOffset(cellCenter_);
    patternlockModifier_->SetContentOffset(paintWrapper->GetContentOffset());
    patternlockModifier_->SetChoosePoint(choosePoint_);
    patternlockModifier_->SetActiveCircleRadiusScale(scaleActiveCircleRadius_);
    patternlockModifier_->SetBackgroundCircleRadiusScale(scaleBackgroundCircleRadius_);
    patternlockModifier_->SetLightRingRadiusStartScale(scaleWaveCircleRadiusStart_);
    patternlockModifier_->SetLightRingRadiusEndScale(scaleWaveCircleRadiusEnd_);
    patternlockModifier_->SetHoverRadiusScale(hoverRadiusScale_);
    patternlockModifier_->SetSideLength(sideLength_);
    patternlockModifier_->SetCircleRadius(circleRadius_.ConvertToPxWithSize(sideLength_));
    patternlockModifier_->SetPathStrokeWidth(pathStrokeWidth_.ConvertToPxWithSize(sideLength_));
    patternlockModifier_->SetActiveCircleColor(LinearColor(activeCircleColor_));
    patternlockModifier_->SetActiveBackgroundRadius(backgroundCircleRadius_.ConvertToPxWithSize(sideLength_));
    patternlockModifier_->SetEnableWaveEffect(enableWaveEffect_);
    patternlockModifier_->SetEnableForeground(enableForeground_);
    patternlockModifier_->UpdateBoundsRect();
}

void PatternLockPaintMethod::GetThemeProp()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto patternLockTheme = pipeline->GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    regularColor_ = patternLockTheme->GetRegularColor();
    selectedColor_ = patternLockTheme->GetSelectedColor();
    activeColor_ = patternLockTheme->GetActiveColor();
    pathColor_ = patternLockTheme->GetPathColor();
    hoverColor_ = patternLockTheme->GetHoverColor();
    wrongColor_ = patternLockTheme->GetWrongColor();
    correctColor_ = patternLockTheme->GetCorrectColor();
    circleRadius_ = patternLockTheme->GetCircleRadius();
    pathStrokeWidth_ = patternLockTheme->GetPathStrokeWidth();
    scaleActiveCircleRadius_ = patternLockTheme->GetActiveCircleRadiusScale();
    scaleBackgroundCircleRadius_ = patternLockTheme->GetBackgroundRadiusScale();
    scaleWaveCircleRadiusStart_ = patternLockTheme->GetLightRingCircleRadiusStartScale();
    scaleWaveCircleRadiusEnd_ = patternLockTheme->GetLightRingCircleRadiusEndScale();
    hoverRadiusScale_ = patternLockTheme->GetHoverRadiusScale();
}
} // namespace OHOS::Ace::NG
