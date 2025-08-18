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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_v2/indexer/indexer_event_info.h"

namespace OHOS::Ace::NG {

using OnSelectedEvent = std::function<void(int32_t)>;
using OnRequestPopupDataEvent = std::function<std::vector<std::string>(int32_t)>;
using OnPopupSelectedEvent = std::function<void(int32_t)>;

class IndexerEventHub : public EventHub {
    DECLARE_ACE_TYPE(IndexerEventHub, EventHub);

public:
    IndexerEventHub() = default;
    ~IndexerEventHub() override = default;

    void SetOnSelected(OnSelectedEvent&& onSelected)
    {
        onSelectedEvent_ = std::move(onSelected);
    }

    const OnSelectedEvent& GetOnSelected() const
    {
        return onSelectedEvent_;
    }

    void SetOnRequestPopupData(OnRequestPopupDataEvent&& onRequestPopupData)
    {
        onRequestPopupDataEvent_ = std::move(onRequestPopupData);
    }

    const OnRequestPopupDataEvent& GetOnRequestPopupData() const
    {
        return onRequestPopupDataEvent_;
    }

    void SetOnPopupSelected(OnPopupSelectedEvent&& onPopupSelected)
    {
        onPopupSelectedEvent_ = std::move(onPopupSelected);
    }

    const OnPopupSelectedEvent& GetOnPopupSelected() const
    {
        return onPopupSelectedEvent_;
    }

    void SetChangeEvent(OnSelectedEvent&& changeEvent)
    {
        selectedChangeEvent_ = std::move(changeEvent);
    }

    const OnSelectedEvent& GetChangeEvent() const
    {
        return selectedChangeEvent_;
    }
    void SetCreatChangeEvent(OnSelectedEvent&& changeEvent)
    {
        creatChangeEvent_ = std::move(changeEvent);
    }

    const OnSelectedEvent& GetCreatChangeEvent() const
    {
        return creatChangeEvent_;
    }

private:
    OnSelectedEvent onSelectedEvent_;
    OnRequestPopupDataEvent onRequestPopupDataEvent_;
    OnPopupSelectedEvent onPopupSelectedEvent_;
    OnSelectedEvent selectedChangeEvent_;
    OnSelectedEvent creatChangeEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H
