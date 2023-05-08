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

#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_property.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> XComponentLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, FrameNode* frameNode)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(frameNode->GetLayoutProperty());
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        return LayoutAlgorithm::MeasureContent(contentConstraint, frameNode);
    }
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    return contentConstraint.maxSize;
}

void XComponentLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(frameNode->GetLayoutProperty());
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        LinearLayoutUtils::Measure(frameNode, true);
    } else {
        BoxLayoutAlgorithm::Measure(frameNode);
    }
}

void XComponentLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(frameNode->GetLayoutProperty());
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        LinearLayoutUtils::Layout(frameNode, true, FlexAlign::CENTER, FlexAlign::FLEX_START);
        auto children = frameNode->GetAllFrameNodeChildren();
        for (auto&& child : children) {
            child->Layout();
        }
    } else {
        BoxLayoutAlgorithm::Layout(frameNode);
    }
}

} // namespace OHOS::Ace::NG
