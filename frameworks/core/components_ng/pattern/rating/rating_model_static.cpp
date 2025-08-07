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

#include "core/components_ng/pattern/rating/rating_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"

namespace OHOS::Ace::NG {
void RatingModelStatic::SetStars(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    if (value.has_value()) {
        int32_t iValue = value.value();
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RatingLayoutProperty, Stars, iValue, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RatingLayoutProperty, Stars, frameNode);
    }
}

void RatingModelStatic::SetStepSize(FrameNode* frameNode, const std::optional<double>& value)
{
    if (value.has_value()) {
        double dValue = value.value();
        ACE_UPDATE_NODE_PAINT_PROPERTY(RatingRenderProperty, StepSize, dValue, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RatingRenderProperty, StepSize, frameNode);
    }
}

void RatingModelStatic::SetRatingOptions(
    FrameNode* frameNode, const std::optional<double>& rating, const std::optional<bool>& indicator)
{
    if (indicator.has_value()) {
        bool bIndicator = indicator.value();
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RatingLayoutProperty, Indicator, bIndicator, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RatingLayoutProperty, Indicator, frameNode);
    }
    if (rating.has_value()) {
        double dRating =  rating.value();
        ACE_UPDATE_NODE_PAINT_PROPERTY(RatingRenderProperty, RatingScore, dRating, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(RatingRenderProperty, RatingScore, frameNode);
    }
}

void RatingModelStatic::SetOnChange(FrameNode* frameNode, RatingChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void RatingModelStatic::SetOnChangeEvent(FrameNode* frameNode, RatingChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChange));
}
} // namespace OHOS::Ace::NG
