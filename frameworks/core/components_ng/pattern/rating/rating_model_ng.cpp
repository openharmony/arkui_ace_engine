/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rating/rating_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void RatingModelNG::Create(double rating, bool indicator)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RATING_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RatingPattern>(); });
    stack->Push(frameNode);
    RatingModelNG::SetRatingScore(rating);
    RatingModelNG::SetIndicator(indicator);
}

void RatingModelNG::SetRatingScore(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(RatingRenderProperty, RatingScore, value);
}

void RatingModelNG::SetIndicator(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, Indicator, value);
}

void RatingModelNG::SetStars(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, Stars, value);
}

void RatingModelNG::SetStepSize(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(RatingRenderProperty, StepSize, value);
}

void RatingModelNG::SetForegroundSrc(const std::string& value, bool flag)
{
    if (flag) {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(RatingLayoutProperty, ForegroundImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, ForegroundImageSourceInfo, ImageSourceInfo(value));
    }
}

void RatingModelNG::SetSecondarySrc(const std::string& value, bool flag)
{
    if (flag) {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(RatingLayoutProperty, SecondaryImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, SecondaryImageSourceInfo, ImageSourceInfo(value));
    }
}

void RatingModelNG::SetBackgroundSrc(const std::string& value, bool flag)
{
    if (flag) {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(RatingLayoutProperty, BackgroundImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(RatingLayoutProperty, BackgroundImageSourceInfo, ImageSourceInfo(value));
    }
}

void RatingModelNG::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void RatingModelNG::SetOnChangeEvent(ChangeEvent&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
