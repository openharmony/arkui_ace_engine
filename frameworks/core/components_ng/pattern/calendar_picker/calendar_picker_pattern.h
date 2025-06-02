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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_PATTERN_H

#include <optional>

#include "core/components_ng/pattern/calendar_picker/calendar_picker_event_hub.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_algorithm.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_property.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class CalendarPickerPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(CalendarPickerPattern, LinearLayoutPattern);

public:
    CalendarPickerPattern() : LinearLayoutPattern(false) {};
    ~CalendarPickerPattern() override = default;

    void OnColorModeChange(uint32_t colorMode) override
    {
        LinearLayoutPattern::OnColorModeChange(colorMode);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkModifyDone();
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CalendarPickerEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<CalendarPickerLayoutProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION };
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CalendarPickerLayoutAlgorithm>();
    }

    void SetCalendarEdgeAlign(CalendarEdgeAlign align)
    {
        align_ = align;
    }

    CalendarEdgeAlign GetCalendarEdgeAlign() const
    {
        return align_;
    }

    void SetCalendarDialogOffset(const DimensionOffset& offset)
    {
        offset_ = offset;
    }

    DimensionOffset GetCalendarDialogOffset() const
    {
        return offset_;
    }

    void SetCalendarData(const CalendarSettingData& data)
    {
        CalendarSettingData settingData = data;
        settingData.selectedDate = PickerDate::AdjustDateToRange(data.selectedDate, data.startDate, data.endDate);
        calendarData_ = settingData;
    }

    CalendarSettingData GetCalendarData() const
    {
        return calendarData_;
    }

    void HandleClickEvent(const Offset& globalLocation);
    void HandleTextHoverEvent(bool state, int32_t index);
    void HandleAddButtonClick();
    void HandleSubButtonClick();
    bool HandleNumberKeyEvent(const KeyEvent& event);

    bool HandleKeyEvent(const KeyEvent& event);
    bool HandleFocusEvent(const KeyEvent& event);
    bool HandleBlurEvent(const KeyEvent& event);

    void OnValueChange();
    bool IsDialogShow() const
    {
        return isDialogShow_;
    }
    void SetDialogShow(bool flag)
    {
        isDialogShow_ = flag;
    }

    CalendarPickerSelectedType CheckRegion(const Offset& globalLocation);
    CalendarPickerSelectedType GetSelectedType() const
    {
        return selected_;
    }
    void SetSelectedType(CalendarPickerSelectedType type);

    bool HasSubNode() const
    {
        return subId_.has_value();
    }
    int32_t GetSubId()
    {
        if (!subId_.has_value()) {
            subId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return subId_.value();
    }

    bool HasContentNode() const
    {
        return contentId_.has_value();
    }
    int32_t GetContentId()
    {
        if (!contentId_.has_value()) {
            contentId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return contentId_.value();
    }

    bool HasAddNode() const
    {
        return addId_.has_value();
    }
    int32_t GetAddId()
    {
        if (!addId_.has_value()) {
            addId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return addId_.value();
    }

    bool HasButtonFlexNode() const
    {
        return buttonFlexId_.has_value();
    }
    int32_t GetButtonFlexId()
    {
        if (!buttonFlexId_.has_value()) {
            buttonFlexId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return buttonFlexId_.value();
    }

    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, bool /* skipMeasure */, bool /* skipLayout */) override;

    OffsetF CalculateDialogOffset();
    void HandleHoverEvent(bool state, const Offset& globalLocation);
    void HandleTouchEvent(bool isPressed, const Offset& globalLocation);

    bool IsContainerModal();

    void SetDate(const std::string& info);
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void SetMarkToday(bool isMarkToday);
    bool GetMarkToday();
    void SetDisabledDateRange(const std::vector<std::pair<PickerDate, PickerDate>>& disabledDateRange);
    std::string GetDisabledDateRange();
    void UpdateTextStyle(const PickerTextStyle& textStyle);

private:
    void OnModifyDone() override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void OnColorConfigurationUpdate() override;
    void InitDateIndex();
    void InitClickEvent();
    void InitOnKeyEvent();
    void InitOnHoverEvent();
    void ShowDialog();
    void InitDialogProperties(DialogProperties& properties);
    void PostTaskToUI(const std::function<void()>& task, const std::string& name);
    void HandleTaskCallback();
    void HandleZeroStartTaskCallback();
    void HandleTextFocusEvent(int32_t index);
    void HandleBlurEvent();
    void HandleButtonHoverEvent(bool state, int32_t index);
    void HandleButtonTouchEvent(bool isPressed, int32_t index);
    void HandleEnable();
    void ResetTextState();
    void ResetTextStateByNode(const RefPtr<FrameNode>& textFrameNode);
    void FlushTextStyle();
    bool IsInNodeRegion(const RefPtr<FrameNode>& node, const PointF& point);
    bool HandleYearKeyWaitingEvent(
        const uint32_t number, const std::function<void()>& task, const std::function<void()>& zeroStartTask);
    bool HandleYearKeyEvent(uint32_t number);
    bool HandleMonthKeyEvent(uint32_t number);
    bool HandleDayKeyEvent(uint32_t number);
    void FireChangeEvents(const std::string& info);
    void UpdateEntryButtonColor();
    void UpdateEntryButtonBorderWidth();
    void UpdateEdgeAlign();
    void UpdateAccessibilityText();
    void FlushAddAndSubButton();
    bool IsAddOrSubButtonEnable(int32_t buttonIndex);
    void PrevDateBySelectedType(PickerDate& date);
    void NextDateBySelectedType(PickerDate& date);

    std::string GetEntryDateInfo();
    bool ReportChangeEvent(const std::string& compName,
        const std::string& eventName, const std::string& eventData);

    uint32_t yearEnterCount_ = 0;
    uint32_t yearPrefixZeroCount_ = 0;
    uint32_t monthPrefixZeroCount_ = 0;
    uint32_t dayPrefixZeroCount_ = 0;
	
    int32_t yearIndex_ = 0;
    int32_t monthIndex_ = 2;
    int32_t dayIndex_ = 4;

    std::optional<int32_t> subId_;
    std::optional<int32_t> contentId_;
    std::optional<int32_t> addId_;
    std::optional<int32_t> buttonFlexId_;
    int32_t taskCount_ = 0;
    CalendarEdgeAlign align_ = CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset_;
    CalendarSettingData calendarData_;
    bool isDialogShow_ = false;
    bool isKeyWaiting_ = false;
    bool isFirtFocus_ = true;
    RefPtr<ClickEvent> clickListener_;
    RefPtr<InputEvent> hoverListener_;
    CalendarPickerSelectedType selected_ = CalendarPickerSelectedType::OTHER;
    PickerDate reportedPickerDate_;
    ACE_DISALLOW_COPY_AND_MOVE(CalendarPickerPattern);
    bool isMarkToday_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_PATTERN_H
