/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

class ContainerReaderEventHub : public EventHub {
    DECLARE_ACE_TYPE(ContainerReaderEventHub, EventHub);

public:
    ContainerReaderEventHub() = default;
    ~ContainerReaderEventHub() override = default;

    void SetOnSizeChange(std::function<void(const SizeF&)>&& event)
    {
        onSizeChange_ = std::move(event);
    }

    void SetOnWidthBreakpointChange(std::function<void(WidthBreakpoint)>&& event)
    {
        onWidthBreakpointChange_ = std::move(event);
    }

    void SetOnHeightBreakpointChange(std::function<void(HeightBreakpoint)>&& event)
    {
        onHeightBreakpointChange_ = std::move(event);
    }

    void FireSizeChange(const SizeF& size)
    {
        if (onSizeChange_) {
            onSizeChange_(size);
        }
    }

    void FireWidthBreakpointChange(WidthBreakpoint breakpoint)
    {
        if (onWidthBreakpointChange_) {
            onWidthBreakpointChange_(breakpoint);
        }
    }

    void FireHeightBreakpointChange(HeightBreakpoint breakpoint)
    {
        if (onHeightBreakpointChange_) {
            onHeightBreakpointChange_(breakpoint);
        }
    }

private:
    std::function<void(const SizeF&)> onSizeChange_;
    std::function<void(WidthBreakpoint)> onWidthBreakpointChange_;
    std::function<void(HeightBreakpoint)> onHeightBreakpointChange_;

    ACE_DISALLOW_COPY_AND_MOVE(ContainerReaderEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_READER_CONTAINER_READER_EVENT_HUB_H
