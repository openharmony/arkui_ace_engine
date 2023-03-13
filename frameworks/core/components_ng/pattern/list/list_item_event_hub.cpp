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

#include "core/components_ng/pattern/list/list_item_event_hub.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_event_hub.h"

namespace OHOS::Ace::NG {
int32_t ListItemEventHub::GetIndex(const Point& point) const
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, -1);
    auto parent = host->GetParent();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
    while (parent && !frameNode) {
        parent = parent->GetParent();
        frameNode = AceType::DynamicCast<FrameNode>(parent);
    }
    CHECK_NULL_RETURN(frameNode, -1);
    auto hub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_RETURN(hub, -1);
    return hub->GetListItemIndexByPosition(point.GetX(), point.GetY());
}

std::string ListItemEventHub::GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType drag)
{
    auto json = JsonUtil::Create(true);
    if (drag == DragEventType::START) {
        int32_t index = GetIndex(point);
        json->Put("selectedIndex", index);
    }
    if (!extraInfo.empty()) {
        json->Put("extraInfo", extraInfo.c_str());
    }
    return json->ToString();
}
} // namespace OHOS::Ace::NG