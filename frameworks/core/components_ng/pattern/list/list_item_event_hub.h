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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
class ListItemEventHub : public EventHub {
    DECLARE_ACE_TYPE(ListItemEventHub, EventHub)

public:
    ListItemEventHub() = default;
    ~ListItemEventHub() override = default;

    void SetOnSelect(OnSelectFunc&& onSelect)
    {
        onSelectEvent_ = std::move(onSelect);
    }

    const OnSelectFunc& GetOnSelect() const
    {
        return onSelectEvent_;
    }

    int32_t GetIndex(const Point& point) const;

    std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType drag) override;

private:
    OnSelectFunc onSelectEvent_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_EVENT_HUB_H