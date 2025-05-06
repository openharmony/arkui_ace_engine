/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace_kit/include/ui/view/layout/box_layout_algorithm.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::Kit {

void BoxLayoutAlgorithm::Measure(const Kit::LayoutConstraintInfo& contentConstraint)
{
    auto frameNode = host_.Upgrade();
    if (frameNode) {
        frameNode->MeasureChildren();
        BoxLayoutAlgorithm::PerformMeasureSelf(AceType::RawPtr(frameNode));
    }
}

void BoxLayoutAlgorithm::Layout()
{
    auto frameNode = host_.Upgrade();
    if (frameNode) {
        BoxLayoutAlgorithm::PerformLayout(AceType::RawPtr(frameNode));
        frameNode->LayoutChildren();
    }
}

std::optional<NG::SizeF> BoxLayoutAlgorithm::MeasureContent(const NG::LayoutConstraintT<float>& contentConstraint)
{
    auto frameNode = DynamicCast<FrameNodeImpl>(host_.Upgrade());
    if (frameNode) {
        return NG::BoxLayoutAlgorithm::PerformMeasureContent(contentConstraint, frameNode->GetLayoutWrapper());
    }
    return std::nullopt;
}

void BoxLayoutAlgorithm::PerformMeasureSelf(FrameNode* frameNode)
{
    auto* frameNodeImpl = reinterpret_cast<FrameNodeImpl*>(frameNode);
    CHECK_NULL_VOID(frameNodeImpl);
    auto* layoutWrapper = frameNodeImpl->GetLayoutWrapper();
    NG::BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

void BoxLayoutAlgorithm::PerformLayout(FrameNode* frameNode)
{
    auto* frameNodeImpl = reinterpret_cast<FrameNodeImpl*>(frameNode);
    CHECK_NULL_VOID(frameNodeImpl);
    auto* layoutWrapper = frameNodeImpl->GetLayoutWrapper();
    NG::BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
}

void BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(FrameNode* frameNode)
{
    auto* frameNodeImpl = reinterpret_cast<FrameNodeImpl*>(frameNode);
    CHECK_NULL_VOID(frameNodeImpl);
    auto* layoutWrapper = frameNodeImpl->GetLayoutWrapper();
    CHECK_NULL_VOID(layoutWrapper);
    NG::BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(
        layoutWrapper, layoutWrapper->GetAllChildrenWithBuild());
}
} // namespace OHOS::Ace::Kit
