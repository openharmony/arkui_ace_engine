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

#include "core/components_ng/pattern/blank/blank_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/blank/blank_pattern.h"

namespace OHOS::Ace::NG {
void BlankModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::BLANK_ETS_TAG, nodeId);
    auto blankNode = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BlankPattern>(); });
    stack->Push(blankNode);
    auto blankProperty = blankNode->GetLayoutProperty<BlankLayoutProperty>();
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexGrow, 1.0f);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexShrink, 0.0f);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, AlignSelf, FlexAlign::STRETCH);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, Height, Dimension(0.0, DimensionUnit::VP));
    } else if (blankProperty) {
        blankProperty->ResetCalcMinSize();
    }
}

RefPtr<FrameNode> BlankModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BlankPattern>(); });
    auto blankProperty = frameNode->GetLayoutProperty<BlankLayoutProperty>();
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        frameNode->GetLayoutProperty<BlankLayoutProperty>()->UpdateFlexGrow(1.0f);
        frameNode->GetLayoutProperty<BlankLayoutProperty>()->UpdateFlexShrink(0.0f);
        frameNode->GetLayoutProperty<BlankLayoutProperty>()->UpdateAlignSelf(FlexAlign::STRETCH);
        frameNode->GetLayoutProperty<BlankLayoutProperty>()->UpdateHeight(Dimension(0.0, DimensionUnit::VP));
    } else if (blankProperty) {
        blankProperty->ResetCalcMinSize();
    }

    return frameNode;
}

void BlankModelNG::SetBlankMin(const Dimension& blankMin)
{
    auto blankNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(blankNode);
    auto layoutProperty = blankNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto result = blankMin;
    if (blankMin.IsNegative()) {
        result = Dimension(0.0, DimensionUnit::VP);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, MinSize, result);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexBasis, result);
    }
}

void BlankModelNG::SetHeight(const Dimension& height)
{
    auto blankNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(blankNode);
    auto layoutProperty = blankNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateHeight(height);
}

void BlankModelNG::SetColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(BlankPaintProperty, Color, color);
}

void BlankModelNG::SetColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(BlankPaintProperty, Color, color, frameNode);
}

void BlankModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateHeight(height);
}

void BlankModelNG::SetBlankMin(FrameNode* frameNode, const Dimension& blankMin)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto result = blankMin;
    if (blankMin.IsNegative()) {
        result = Dimension(0.0, DimensionUnit::VP);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(BlankLayoutProperty, MinSize, result, frameNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexBasis, result, frameNode);
    }
}
} // namespace OHOS::Ace::NG
