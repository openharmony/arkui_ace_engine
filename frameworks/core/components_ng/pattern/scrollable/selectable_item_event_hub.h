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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_ITEM_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_ITEM_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using SelectFunc = std::function<void(bool)>;

class SelectableItemEventHub : public EventHub {
    DECLARE_ACE_TYPE(SelectableItemEventHub, EventHub);

public:
    SelectableItemEventHub() = default;
    ~SelectableItemEventHub() override = default;

    void SetOnSelect(SelectFunc&& onSelect)
    {
        onSelect_ = std::move(onSelect);
    }

    SelectFunc GetOnSelect() const
    {
        return onSelect_;
    }

    void SetSelectChangeEvent(SelectFunc&& changeEvent)
    {
        selectChangeEvent_ = std::move(changeEvent);
    }

    SelectFunc GetSelectChangeEvent() const
    {
        return selectChangeEvent_;
    }

    void FireSelectChangeEvent(bool select) const
    {
        if (selectChangeEvent_) {
            selectChangeEvent_(select);
        }
        if (onSelect_) {
            onSelect_(select);
        }
    }

    void BindContextMenu();

    void RestoreGatherNode();

private:
    SelectFunc onSelect_;
    SelectFunc selectChangeEvent_;
    CancelableCallback<void()> gatherTask_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_ITEM_EVENT_HUB_H