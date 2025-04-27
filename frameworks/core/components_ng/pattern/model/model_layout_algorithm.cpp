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

#include "core/components_ng/pattern/model/model_layout_algorithm.h"

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {

ModelLayoutAlgorithm::ModelLayoutAlgorithm(const WeakPtr<ModelAdapterWrapper>& adapter) : modelAdapter_(adapter) {}

std::optional<SizeF> ModelLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto modelLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(modelLayoutProperty, std::nullopt);

    // 1. Width and height are set properly - return content constraint as component size
    if (contentConstraint.selfIdealSize.IsValid()) {
        auto size = contentConstraint.selfIdealSize.ConvertToSizeT();
        return size;
    }

    SizeF componentSize(0.0f, 0.0f);
    do {
        // 2.1 Width and height are not set. Determine size from parent.
        const auto& modelLayoutProperty = layoutWrapper->GetLayoutProperty();
        SizeF layoutConstraintMaxSize = modelLayoutProperty->GetLayoutConstraint()->maxSize;
        if (contentConstraint.selfIdealSize.IsNull()) {
            componentSize.SetSizeT(layoutConstraintMaxSize);
            break; // exit to return statement
        }

        // 2.2 Either width or height are set. Set size based on aspect ratio.
        auto sizeSet = contentConstraint.selfIdealSize.ConvertToSizeT();
        componentSize.SetSizeT(sizeSet);
        uint8_t sizeSetStatus = (Negative(sizeSet.Width()) << 1) | Negative(sizeSet.Height());
        double aspectRatio = Size::CalcRatio(Size(4, 3)); // default aspect ratio os 4:3
        switch (sizeSetStatus) {
            case 0b01: // width is positive and height is negative
                componentSize.SetHeight(static_cast<float>(sizeSet.Width() / aspectRatio));
                break;
            case 0b10: // width is negative and height is positive
                componentSize.SetWidth(static_cast<float>(sizeSet.Height() * aspectRatio));
                break;
            case 0b11: // both width and height are negative
            default:
                break;
        }
    } while (false);

    auto size = contentConstraint.Constrain(componentSize);
    return size;
}
} // namespace OHOS::Ace::NG
