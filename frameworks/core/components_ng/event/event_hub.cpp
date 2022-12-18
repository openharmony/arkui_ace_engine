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

#include "core/components_ng/event/event_hub.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void EventHub::AttachHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> EventHub::GetFrameNode() const
{
    return host_.Upgrade();
}

GetEventTargetImpl EventHub::CreateGetEventTargetImpl() const
{
    auto impl = [weak = host_]() -> std::optional<EventTarget> {
        auto host = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(host, std::nullopt);
        EventTarget eventTarget;
        eventTarget.id = host->GetId();
        eventTarget.type = host->GetTag();
        auto geometryNode = host->GetGeometryNode();
        auto offset = geometryNode->GetFrameOffset();
        auto size = geometryNode->GetFrameSize();
        eventTarget.area.SetOffset(DimensionOffset(offset));
        eventTarget.area.SetHeight(Dimension(size.Height()));
        eventTarget.area.SetWidth(Dimension(size.Width()));
        eventTarget.origin = DimensionOffset(geometryNode->GetParentGlobalOffset());
        return eventTarget;
    };
    return impl;
}

void EventHub::MarkModifyDone()
{
    if (gestureEventHub_) {
        gestureEventHub_->OnModifyDone();
    }
    OnModifyDone();
}

} // namespace OHOS::Ace::NG