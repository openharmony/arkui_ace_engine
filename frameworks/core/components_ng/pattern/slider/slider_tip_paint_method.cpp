/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/slider/slider_tip_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"

namespace OHOS::Ace::NG {
void SliderTipPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(sliderPattern_);
    auto host = sliderPattern_->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto paintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    sliderTipModifier_->UpdateThemeParams(theme);
    sliderTipModifier_->SetDirection(paintProperty->GetDirectionValue(Axis::HORIZONTAL));
    sliderTipModifier_->SetTipColor(paintProperty->GetTipColorValue(theme->GetTipColor()));
    sliderTipModifier_->SetTextFontSize(paintProperty->GetFontSizeValue(theme->GetTipFontSize()));
    sliderTipModifier_->SetTextColor(paintProperty->GetTextColorValue(theme->GetTipTextColor()));
    sliderTipModifier_->SetContent(paintProperty->GetCustomContent().value_or(paintProperty->GetContentValue("")));
    sliderTipModifier_->SetSliderMode(paintProperty->GetSliderModeValue(SliderModelNG::SliderMode::OUTSET));
    auto blockSize = parameters_.blockSize;
    if (paintProperty->GetSliderModeValue(SliderModelNG::SliderMode::OUTSET) != SliderModelNG::SliderMode::OUTSET) {
        blockSize = SizeF(std::min(blockSize.Width(), parameters_.trackThickness),
            std::min(blockSize.Height(), parameters_.trackThickness));
    }

    sliderTipModifier_->SetBlockSize(blockSize);
    sliderTipModifier_->SetTipFlag(tipParameters_.isDrawTip_);
    sliderTipModifier_->SetContentOffset(paintWrapper->GetContentOffset());
    sliderTipModifier_->SetContentSize(paintWrapper->GetContentSize());
    sliderTipModifier_->SetBubbleVertex(tipParameters_.bubbleVertex_);
    sliderTipModifier_->SetSliderGlobalOffset(tipParameters_.sliderGlobalOffset_);
    sliderTipModifier_->BuildParagraph();
    sliderTipModifier_->UpdateBubbleSize();
    if (sliderTipModifier_->UpdateOverlayRect(paintWrapper->GetGeometryNode()->GetFrameSize())) {
        paintWrapper->FlushOverlayModifier();
    }
}
} // namespace OHOS::Ace::NG