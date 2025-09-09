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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_info.h"

namespace OHOS::Ace::NG {
using ChangeEvent = std::function<void(const FolderEventInfo& folderEventInfo)>;
using HoverStatusChangeEvent = std::function<void(const FolderEventInfo& folderEventInfo)>;

class FolderStackEventHub : public EventHub {
    DECLARE_ACE_TYPE(FolderStackEventHub, EventHub);

public:
    void SetOnFolderStateChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void SetOnHoverStatusChange(HoverStatusChangeEvent&& hoverStatusChangeEvent)
    {
        hoverStatusChangeEvent_ = std::move(hoverStatusChangeEvent);
    }

    void OnFolderStateChange(const FolderEventInfo& folderEventInfo) const
    {
        if (changeEvent_) {
            changeEvent_(std::move(folderEventInfo));
        }
    }

    void OnHoverStatusChange(const FolderEventInfo&& folderEventInfo) const
    {
        if (hoverStatusChangeEvent_) {
            hoverStatusChangeEvent_(folderEventInfo);
        }
    }

private:
    ChangeEvent changeEvent_;
    HoverStatusChangeEvent hoverStatusChangeEvent_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_EVENT_HUB.H