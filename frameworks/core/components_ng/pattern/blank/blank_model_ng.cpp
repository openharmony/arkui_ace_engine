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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/blank/blank_layout_property.h"
#include "core/components_ng/pattern/blank/blank_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
void BlankModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto blankNode = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BlankPattern>(); });
    stack->Push(blankNode);
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() <= 9) {
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexGrow, 1.0f);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexShrink, 0.0f);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, AlignSelf, FlexAlign::STRETCH);
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, Height, Dimension(0.0, DimensionUnit::VP));
    }
}

void BlankModelNG::SetBlankMin(const Dimension& blankMin)
{
    auto blankNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(blankNode);
    auto layoutProperty = blankNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto result = blankMin;
    if (blankMin.IsNegative()) {
        result = Dimension();
    }
    if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() <= 9) {
        ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, FlexBasis, result);
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(BlankLayoutProperty, MinSize, result);
}

void BlankModelNG::SetHeight(const Dimension& height)
{
    auto blankNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(blankNode);
    auto layoutProperty = blankNode->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateHeight(height);
}
} // namespace OHOS::Ace::NG
