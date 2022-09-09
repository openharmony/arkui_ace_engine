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

#include "core/components_ng/pattern/list/list_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ListView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LIST_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ListPattern>(); });
    stack->Push(frameNode);
}

void ListView::SetSpace(const Dimension& space)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Space, space);
}

void ListView::SetInitialIndex(const int32_t& initialIndex)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, initialIndex);
}

void ListView::SetListDirection(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, axis);
}

void ListView::SetEdgeEffect(EdgeEffect edgeEffect)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, EdgeEffect, edgeEffect);
}

void ListView::SetDivider(const V2::ItemDivider& divider)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider);
}

void ListView::SetLanes(int32_t lanes)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes);
}

void ListView::SetLaneMinLength(const Dimension& laneMinLength)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMinLength, laneMinLength);
}

void ListView::SetLaneMaxLength(const Dimension& laneMaxLength)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength);
}

void ListView::SetListItemAlign(V2::ListItemAlign listItemAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign);
}

void ListView::SetCachedCount(const int32_t& cachedCount)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, cachedCount);
}
} // namespace OHOS::Ace::NG
