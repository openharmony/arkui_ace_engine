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

#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SwiperController> SwiperModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    return pattern ? pattern->GetSwiperController() : nullptr;
}

void SwiperModelNG::SetDirection(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, Direction, axis);
}

void SwiperModelNG::SetIndex(uint32_t index)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, Index, index);
}

void SwiperModelNG::SetDisplayMode(SwiperDisplayMode displayMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode, displayMode);
}

void SwiperModelNG::SetDisplayCount(int32_t displayCount)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, displayCount);
}

void SwiperModelNG::SetShowIndicator(bool showIndicator)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ShowIndicator, showIndicator);
}

void SwiperModelNG::SetItemSpace(const Dimension& itemSpace)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ItemSpace, itemSpace);
}

void SwiperModelNG::SetCachedCount(int32_t cachedCount)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, CachedCount, cachedCount);
}

void SwiperModelNG::SetAutoPlay(bool autoPlay)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlay, autoPlay);
}

void SwiperModelNG::SetAutoPlayInterval(uint32_t interval)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlayInterval, interval);
}

void SwiperModelNG::SetDuration(uint32_t duration)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Duration, duration);
}

void SwiperModelNG::SetLoop(bool loop)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Loop, loop);
}

void SwiperModelNG::SetEnabled(bool enabled)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Enabled, enabled);
}

void SwiperModelNG::SetDisableSwipe(bool disableSwipe)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, DisableSwipe, disableSwipe);
}

void SwiperModelNG::SetEdgeEffect(EdgeEffect edgeEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, EdgeEffect, edgeEffect);
}

void SwiperModelNG::SetCurve(const RefPtr<Curve>& curve)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Curve, curve);
}

void SwiperModelNG::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG
