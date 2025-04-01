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

#include "core/components_ng/pattern/slider/slider_tip_pattern.h"
#include "core/components_ng/pattern/slider/slider_tip_paint_method.h"

namespace OHOS::Ace::NG {
RefPtr<NodePaintMethod> SliderTipPattern::CreateNodePaintMethod()
{
    CHECK_NULL_RETURN(sliderPattern_, nullptr);
    if (!sliderPattern_->IsSliderVisible()) {
        return nullptr;
    }
    auto paintParameters = sliderPattern_->UpdateContentParameters();
    auto overlayGlobalOffset = sliderPattern_->CalculateGlobalSafeOffset();
    std::pair<OffsetF, float> bubbleVertex = sliderPattern_->GetBubbleVertexPosition(sliderPattern_->GetBlockCenter(),
        sliderPattern_->GetTrackThickness(), sliderPattern_->GetBlockSize());
    SliderPaintMethod::TipParameters tipParameters { sliderPattern_->GetBubbleFlag(),
        bubbleVertex.first, overlayGlobalOffset };
    if (!sliderTipModifier_ && sliderPattern_->GetBubbleFlag()) {
        sliderTipModifier_ = AceType::MakeRefPtr<SliderTipModifier>([weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            if (!pattern) {
                return std::pair<OffsetF, float>();
            }
            if (!pattern->sliderPattern_) {
                return std::pair<OffsetF, float>();
            }
            auto blockCenter = pattern->sliderPattern_->GetBlockCenter();
            auto trackThickness = pattern->sliderPattern_->GetSliderContentModifier()->GetTrackThickness();
            auto blockSize = pattern->sliderPattern_->GetSliderContentModifier()->GetBlockSize();
            return pattern->sliderPattern_->GetBubbleVertexPosition(blockCenter, trackThickness, blockSize);
        },
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            if (!pattern) {
                return;
            }

            if (!pattern->sliderPattern_) {
                return;
            }
            pattern->sliderPattern_->OnFinishEventTipSize();
            return;
        });
    }
    return MakeRefPtr<SliderTipPaintMethod>(sliderPattern_, tipParameters, sliderTipModifier_,
        sliderPattern_->UpdateContentParameters());
}
}