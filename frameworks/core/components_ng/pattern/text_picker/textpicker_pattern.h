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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_PATTERN_H

#include <optional>

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"

namespace OHOS::Ace::NG {
class TextPickerPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(TextPickerPattern, LinearLayoutPattern);

public:
    TextPickerPattern() : LinearLayoutPattern(true) {};

    ~TextPickerPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextPickerEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextPickerLayoutProperty>();
    }

    void OnColumnsBuilding();

    void FlushCurrentOptions();

    void InitilaScorllEvent();

    void UpdateCurrentOffset(float offset);

    void UpdateColumnChildPosition(double y);

    bool CanMove(bool isDown) const;

    bool NotLoopOptions() const;

    bool InnerHandleScroll(bool isDown);

    void SetDefaultPickerItemHeight();

    uint32_t GetShowOptionCount() const;

    void SetSelected(uint32_t value)
    {
        selectedIndex_ = value;
    }
    uint32_t GetSelected() const
    {
        return selectedIndex_;
    }

    void SetRange(const std::vector<std::string>& value)
    {
        if (value.empty()) {
            LOGE("input value of range is empty.");
            return;
        }
        range_ = value;
    }

    const std::vector<std::string>& GetRange() const
    {
        return range_;
    }

    uint32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }
    void SetCurrentIndex(uint32_t value)
    {
        currentIndex_ = value;
    }

    void ClearOption()
    {
        options_.clear();
    }

    void AppendOption(const std::string& value)
    {
        options_.emplace_back(value);
    }

    uint32_t GetOptionCount() const
    {
        return options_.size();
    }

    std::string GetOption(uint32_t index) const
    {
        if (index >= GetOptionCount()) {
            LOGE("index out of range.");
            return "";
        }
        return options_[index];
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;

    uint32_t selectedIndex_ = 0;
    std::string selectedValue_;
    std::vector<std::string> range_ { "" };
    uint32_t currentIndex_ = 0;
    std::vector<std::string> options_;
    int32_t currentChildIndex_ = 0;
    float currentOffset_ = 0.0f;
    RefPtr<ScrollableEvent> scrollableEvent_;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    Dimension jumpInterval_;
    Size optionSize_;
    Dimension fixHeight_;
    bool isIndexChanged_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_PATTERN_H
