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

#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> ShapeContainerLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto curFrameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(curFrameNode, std::nullopt);
    auto paintProperty = curFrameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, std::nullopt);
    double portWidth = 0.0;
    double portHeight = 0.0;
    if (paintProperty->HasShapeViewBox() && paintProperty->GetShapeViewBoxValue().IsValid()) {
        portWidth = paintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
        portHeight = paintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
    }
    auto newSize = contentConstraint.selfIdealSize.ConvertToSizeT();

    // When the width and height are both not specified, shape size is determined by viewport's size.
    if (contentConstraint.selfIdealSize.IsNull()) {
        if (GreatNotEqual(portWidth, 0.0) && GreatNotEqual(portHeight, 0.0)) {
            newSize = contentConstraint.Constrain(SizeF(portWidth, portHeight));
            return newSize;
        }
    }

    // When the width and height are both specified, shape size will not be influenced by viewport.
    if (contentConstraint.selfIdealSize.IsValid()) {
        return newSize;
    }

    // When only the width is not specified, width = (contentSize.Height() / portHeight) * portWidth
    // When only the height is not specified, height = (contentSize.Width() / portWidth) * portHeight
    bool hasDefineWidth = contentConstraint.selfIdealSize.Width().has_value();
    bool hasDefineHeight = contentConstraint.selfIdealSize.Height().has_value();
    if (hasDefineWidth && !hasDefineHeight && GreatNotEqual(portWidth, 0.0)) {
        auto selfWidth = contentConstraint.selfIdealSize.Width().value();
        auto newHeight = (selfWidth / portWidth) * portHeight;
        newSize = contentConstraint.Constrain(SizeF(selfWidth, newHeight));
    } else if (!hasDefineWidth && hasDefineHeight && GreatNotEqual(portHeight, 0.0)) {
        auto selfHeight = contentConstraint.selfIdealSize.Height().value();
        auto newWidth = (selfHeight / portHeight) * portWidth;
        newSize = contentConstraint.Constrain(SizeF(newWidth, selfHeight));
    }
    return newSize;
}
} // namespace OHOS::Ace::NG
