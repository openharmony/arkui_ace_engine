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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_static.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"

namespace OHOS::Ace::NG {
const uint32_t DEFAULT_SWIPER_CURRENT_INDEX = 0;

RefPtr<FrameNode> IndicatorModelStatic::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        V2::INDICATOR_ETS_TAG, nodeId, AceType::MakeRefPtr<IndicatorPattern>());
}

void IndicatorModelStatic::SetDirection(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Direction, axis, frameNode);
}

void IndicatorModelStatic::SetShowIndicator(FrameNode* frameNode, bool showIndicator)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, ShowIndicator, showIndicator, frameNode);
}

void IndicatorModelStatic::SetLoop(FrameNode* frameNode, bool loop)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Loop, loop, frameNode);
}

void IndicatorModelStatic::SetInitialIndex(FrameNode* frameNode, const std::optional<uint32_t>& index)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, InitialIndex,
        index.value_or(DEFAULT_SWIPER_CURRENT_INDEX), frameNode);
}

void IndicatorModelStatic::SetCount(FrameNode* frameNode, const std::optional<uint32_t>& count)
{
    if (count) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Count, *count, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Count, frameNode);
    }
}

void IndicatorModelStatic::SetDigitIndicatorStyle(
    FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(swiperDigitalParameters);
}

void IndicatorModelStatic::SetIndicatorType(FrameNode* frameNode,
                                            const std::optional<SwiperIndicatorType>& indicatorType)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, IndicatorType,
        indicatorType.value_or(SwiperIndicatorType::DOT), frameNode);
}

void IndicatorModelStatic::SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
}

void IndicatorModelStatic::SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateChangeEvent(std::move(onChange));
}

void IndicatorModelStatic::SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}

bool IndicatorModelStatic::GetLoop(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(SwiperIndicatorLayoutProperty, Loop, value, frameNode, value);
    return value;
}

int32_t IndicatorModelStatic::GetCount(FrameNode* frameNode)
{
    int32_t value = 0;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(SwiperIndicatorLayoutProperty, Count, value, frameNode, value);
    return value;
}

RefPtr<IndicatorController> IndicatorModelStatic::InitIndicatorController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->InitIndicatorController();
    return pattern->GetIndicatorController();
}
} // namespace OHOS::Ace::NG