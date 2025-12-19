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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ContainerPickerChangeEvent = std::function<void(const double&)>;

class ContainerPickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(ContainerPickerEventHub, EventHub);

public:
    ContainerPickerEventHub() = default;
    ~ContainerPickerEventHub() override = default;

    void SetOnChange(ContainerPickerChangeEvent&& onChangeEvent)
    {
        onChangeEvent_ = std::move(onChangeEvent);
    }

    void FireChangeEvent(const double& index) const
    {
        if (selectedIndexChangeEvent_) {
            selectedIndexChangeEvent_(index);
        }
        if (onChangeEvent_) {
            onChangeEvent_(index);
        }
    }

    void SetOnScrollStop(ContainerPickerChangeEvent&& onScrollStopEvent)
    {
        onScrollStopEvent_ = std::move(onScrollStopEvent);
    }

    void FireScrollStopEvent(const double& index) const
    {
        if (onScrollStopEvent_) {
            onScrollStopEvent_(index);
        }
    }

    void SetChangeEvent(ContainerPickerChangeEvent&& onChange)
    {
        selectedIndexChangeEvent_ = std::move(onChange);
    }

private:
    ContainerPickerChangeEvent onChangeEvent_;
    ContainerPickerChangeEvent onScrollStopEvent_;
    ContainerPickerChangeEvent selectedIndexChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(ContainerPickerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_EVENT_HUB_H
