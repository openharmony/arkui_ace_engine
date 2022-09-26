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

#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"

#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void TextPickerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<TextPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto children = layoutWrapper->GetAllChildrenWithBuild();

    float childStartCoordinate = 0.0;
    for (const auto& child : children) {
        auto childGeometryNode = child->GetGeometryNode();
        auto childSize = childGeometryNode->GetFrameSize();
        auto childOffset = padding.Offset() + OffsetF(0.0f, childStartCoordinate);
        childGeometryNode->SetFrameOffset(childOffset);
        child->Layout(parentOffset);
        childStartCoordinate += childSize.Height();
    }
}

} // namespace OHOS::Ace::NG
