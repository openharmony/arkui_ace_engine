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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H

#include <utility>

#include "base/i18n/localization.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;
using ColumnFinishCallback = std::function<void(bool)>;
using EventCallback = std::function<void(bool)>;

class DatePickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(DatePickerColumnPattern, LinearLayoutPattern);

public:
    DatePickerColumnPattern() : LinearLayoutPattern(true) {};

    ~DatePickerColumnPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<DatePickerColumnLayoutAlgorithm>(currentOffset_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DataPickerLayoutProperty>();
    }

    void FlushCurrentOptions();

    bool NotLoopOptions() const;

    void UpdateColumnChildPosition(double y);

    bool CanMove(bool isDown) const;

    bool InnerHandleScroll(bool isDown);

    void ScrollColumn();

    void UpdateCurrentOffset(float offset);

    uint32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetCurrentIndex(uint32_t value)
    {
        currentIndex_ = value;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    const std::map<RefPtr<FrameNode>, std::vector<std::string>>& GetOptions() const
    {
        return options_;
    }

    void SetOptions(const std::map<RefPtr<FrameNode>, std::vector<std::string>>& value)
    {
        options_ = value;
    }

    uint32_t GetShowCount() const
    {
        return showCount_;
    }

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
    }

    void HandleChangeCallback(bool isAdd, bool needNotify)
    {
        if (changeCallback_) {
            changeCallback_(GetHost(), isAdd, GetCurrentIndex(), needNotify);
        } else {
            LOGE("change callback is null.");
        }
    }

    const ColumnChangeCallback& GetChangeCallback() const
    {
        return changeCallback_;
    }

    void SetChangeCallback(ColumnChangeCallback&& value)
    {
        changeCallback_ = value;
    }

    void HandleEventCallback(bool refresh)
    {
        if (EventCallback_) {
            EventCallback_(refresh);
        } else {
            LOGE("event callback is null.");
        }
    }

    const EventCallback& GetEventCallback() const
    {
        return EventCallback_;
    }

    void SetEventCallback(EventCallback&& value)
    {
        EventCallback_ = value;
    }

private:
    void OnAttachToFrameNode() override;

    std::map<RefPtr<FrameNode>, std::vector<std::string>> options_;
    ColumnChangeCallback changeCallback_;
    EventCallback EventCallback_;
    uint32_t currentIndex_ = 0;
    RefPtr<ScrollableEvent> scrollableEvent_;
    float currentOffset_ = 0.0f;
    int32_t currentChildIndex_ = 0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    Dimension jumpInterval_;
    uint32_t showCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerColumnPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H