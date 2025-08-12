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

#include "core/components_ng/pattern/texttimer/text_timer_layout_algorithm.h"

#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void TextTimerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto childConstraint = layoutProperty->CreateChildConstraint();
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(textWrapper);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto& minSize = constraint->minSize;
    auto& maxSize = constraint->maxSize;
    if (layoutPolicy.has_value()) {
        if (layoutPolicy->IsWidthFix()) {
            maxSize.SetWidth(std::numeric_limits<float>::max());
            childConstraint.maxSize.SetWidth(std::numeric_limits<float>::max());
        }
        if (layoutPolicy->IsHeightFix()) {
            maxSize.SetHeight(std::numeric_limits<float>::max());
            childConstraint.maxSize.SetHeight(std::numeric_limits<float>::max());
        }
        if (layoutPolicy->IsWidthMatch()) {
            maxSize.SetWidth(constraint->parentIdealSize.Width().value());
            childConstraint.maxSize.SetWidth(constraint->parentIdealSize.Width().value());
        }
        if (layoutPolicy->IsHeightMatch()) {
            maxSize.SetHeight(constraint->parentIdealSize.Height().value());
            childConstraint.maxSize.SetHeight(constraint->parentIdealSize.Height().value());
        }
    }
    textWrapper->Measure(childConstraint);

    auto textSize = textWrapper->GetGeometryNode()->GetFrameSize();
    OptionalSizeF textTimerFrameSize = { textSize.Width(), textSize.Height() };
    auto padding = layoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, textTimerFrameSize);
    textTimerFrameSize.Constrain(minSize, maxSize);
    if (constraint->selfIdealSize.Width()) {
        textTimerFrameSize.SetWidth(constraint->selfIdealSize.Width().value());
    }
    if (constraint->selfIdealSize.Height()) {
        textTimerFrameSize.SetHeight(constraint->selfIdealSize.Height().value());
    }
    if (layoutPolicy.has_value() && layoutPolicy->IsMatch()) {
        if (layoutPolicy->IsWidthMatch()) {
            textTimerFrameSize.SetWidth(constraint->parentIdealSize.Width().value());
        }
        if (layoutPolicy->IsHeightMatch()) {
            textTimerFrameSize.SetHeight(constraint->parentIdealSize.Height().value());
        }
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(textTimerFrameSize.ConvertToSizeT());
}
} // namespace OHOS::Ace::NG
