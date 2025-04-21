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

#include "core/components_ng/pattern/slider/slider_tip_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_tip_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SliderTipLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(sliderPattern_);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<SliderTipPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    PerformLayout(layoutWrapper);
    auto tipGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(tipGeometryNode);

    auto sliderNode = sliderPattern_->GetHost();
    CHECK_NULL_VOID(sliderNode);
    auto sliderGeometryNode = sliderNode->GetGeometryNode();
    CHECK_NULL_VOID(sliderGeometryNode);
    auto width = sliderGeometryNode->GetFrameSize().Width();
    auto height = sliderGeometryNode->GetFrameSize().Height();
    if (width > height) {
        tipGeometryNode->SetFrameSize(SizeF({ width, 1 }));
    } else {
        tipGeometryNode->SetFrameSize(SizeF({ 1, height }));
    }

    float sliderOffsetX = 0.0f;
    float sliderOffsetY = 0.0f;
    float tipOffsetX = 0.0f;
    float tipOffsetY = 0.0f;
    GetFrameOffset(sliderNode, sliderOffsetX, sliderOffsetY);
    GetFrameOffset(host, tipOffsetX, tipOffsetY);
    auto& posProperty = host->GetRenderContext()->GetOrCreatePositionProperty();
    posProperty->UpdateOffset(OffsetT<Dimension>(Dimension(sliderOffsetX - tipOffsetX),
        Dimension(sliderOffsetY - tipOffsetY)));
}

void SliderTipLayoutAlgorithm::GetFrameOffset(RefPtr<FrameNode> host, float& xOffset, float& yOffset) const
{
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto originFrameOffset = geometryNode->GetFrameOffset();
    xOffset += originFrameOffset.GetX();
    yOffset += originFrameOffset.GetY();
    auto parent = host->GetParent();
    while (parent) {
        auto parentFrame = DynamicCast<FrameNode>(parent);
        if (parentFrame) {
            auto geometryParentNode = parentFrame->GetGeometryNode();
            CHECK_NULL_VOID(geometryParentNode);
            auto parentFrameOffset = geometryParentNode->GetFrameOffset();
            xOffset += parentFrameOffset.GetX();
            yOffset += parentFrameOffset.GetY();
        }
        parent = parent->GetParent();
    }
    return;
}

} // namespace OHOS::Ace::NG