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

#include "core/components_ng/pattern/rating/rating_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void RatingView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::RATING_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RATING_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RatingPattern>(); });
    stack->Push(frameNode);
}

void RatingView::SetRatingScore(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(RatingRenderProperty, RatingScore, value);
}

void RatingView::SetIndicator(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, Indicator, value);
}

void RatingView::SetStars(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, Stars, value);
}

void RatingView::SetStepSize(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(RatingRenderProperty, StepSize, value);
}

void RatingView::SetForegroundSrc(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, ForegroundImageSourceInfo, ImageSourceInfo(value));
}

void RatingView::SetSecondarySrc(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, SecondaryImageSourceInfo, ImageSourceInfo(value));
}

void RatingView::SetBackgroundSrc(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, BackgroundImageSourceInfo, ImageSourceInfo(value));
}

void RatingView::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG