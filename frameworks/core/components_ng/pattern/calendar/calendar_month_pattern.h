/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_MONTH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_MONTH_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/picker/picker_data.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/calendar/calendar_event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_layout_algorithm.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class CalendarMonthPattern : public Pattern {
    DECLARE_ACE_TYPE(CalendarMonthPattern, Pattern);

public:
    CalendarMonthPattern() = default;
    ~CalendarMonthPattern() override;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<CalendarPaintProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CalendarEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CalendarLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    const ObtainedMonth& GetMonthData() const
    {
        return obtainedMonth_;
    }

    void SetMonthData(const ObtainedMonth& obtainedMonth, MonthState monthState)
    {
        obtainedMonth_ = obtainedMonth;
        monthState_ = monthState;
    }

    const CalendarDay& GetCalendarDay() const
    {
        return calendarDay_;
    }

    void SetCalendarDay(const CalendarDay& calendarDay);

    void SetStartDate(const PickerDate& startDate)
    {
        startDate_ = startDate;
    }

    void SetEndDate(const PickerDate& endDate)
    {
        endDate_ = endDate;
    }

    void SetMarkToday(bool markToday)
    {
        markToday_ = markToday;
    }

    void SetDisabledDateRange(const std::vector<std::pair<PickerDate, PickerDate>>& disabledDateRange)
    {
        disabledDateRange_ = disabledDateRange;
    }

    bool IsCalendarDialog() const
    {
        return isCalendarDialog_;
    }

    void SetCalendarDialogFlag(bool isCalendarDialog)
    {
        isCalendarDialog_ = isCalendarDialog;
    }

    void SetHoverState(bool state)
    {
        hoverState_ = state;
    }

    bool GetHoverState() const
    {
        return hoverState_;
    }

    void UpdateColRowSpace()
    {
        SetColRowSpace();
    }

    void SetIsFirstEnter(bool isFirstEnter)
    {
        isFirstEnter_ = isFirstEnter;
    }

    void InitCurrentVirtualNode();

    void ClearCalendarVirtualNode();

    void ClearFocusCalendarDay();

    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;

    Dimension GetDaySize(const RefPtr<CalendarTheme>& theme);

    bool IsLargeSize(const RefPtr<CalendarTheme>& theme);

    void InitFoldState();

    void FireIsFoldStatusChanged();

private:
    void OnAttachToFrameNode() override;
    void OnColorConfigurationUpdate() override;
    void OnLanguageConfigurationUpdate() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnModifyDone() override;
    void OnClick(Offset& localLocation, const ObtainedMonth& obtainedMonth);
    void OnTouchEvent(const Offset& localLocation, bool isPressed);
    void OnHoverEvent(const Offset& localLocation, bool state);
    void InitClickEvent();
    void InitTouchEvent();
    void InitHoverEvent();
    void SetColRowSpace();
    int32_t JudgeArea(const Offset& offset);
    RefPtr<FrameNode> AddButtonNodeIntoVirtual(const CalendarDay& calendarDay);
    void UpdateAccessibilityButtonNode(RefPtr<FrameNode> frameNode, int32_t index);
    void UpdateButtonNodeWithoutTheme(RefPtr<FrameNode> frameNode, int32_t index);
    void ModifyAccessibilityVirtualNode(const ObtainedMonth& currentData);
    void ChangeVirtualNodeContent(const CalendarDay& calendarDay);
    bool InitCalendarVirtualNode();
    void InitVirtualButtonClickEvent(RefPtr<FrameNode> frameNode, int32_t index);
    void SetVirtualNodeUserSelected(int32_t index);
    void FireModifyAccessibilityVirtualNode(const ObtainedMonth& currentData);
    void InitAccessibilityHoverEvent();
    void HandleAccessibilityHoverEvent(bool state, AccessibilityHoverInfo& info);
    void SetCalendarAccessibilityLevel(const std::string& level);
    void InitializeCalendarAccessibility();
    void ChangeVirtualNodeState(const CalendarDay& calendarDay);
    void SetLineNodeSize(RefPtr<FrameNode> lineNode);
    void SetFocusNode(int32_t index, bool isDeviceOrientation = false);
    float GetWidth(const RefPtr<FrameNode>& host);
    bool IsDateInRange(const CalendarDay& day);
    std::string GetDayStr(int32_t index);
    bool isCalendarDialog_ = false;
    bool hoverState_ = false;
    bool isOnHover_ = false;
    bool isFirstEnter_ = false;
    int32_t selectedIndex_ = 0;
    double margin_ = 0;
    RefPtr<FrameNode> lineNode_;
    double dayHeight_ = 0;
    double dayWidth_ = 0;
    double colSpace_ = 0;
    DeviceOrientation deviceOrientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    std::string selectedTxt_;
    std::string disabledDesc_;
    FoldStatus currentFoldStatus_ = FoldStatus::UNKNOWN;
    std::vector<RefPtr<AccessibilityProperty>> accessibilityPropertyVec_;
    std::vector<RefPtr<FrameNode>> buttonAccessibilityNodeVec_;
    std::shared_ptr<AccessibilitySAObserverCallback> accessibilitySAObserverCallback_;
    bool isInitVirtualNode_ = false;
    CalendarDay calendarDay_;
    PickerDate startDate_;
    PickerDate endDate_;
    bool markToday_ = false;
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange_;
    CalendarDay focusedCalendarDay_;
    ObtainedMonth obtainedMonth_;
    MonthState monthState_ = MonthState::CUR_MONTH;
    RefPtr<ClickEvent> clickListener_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> hoverListener_;

    ACE_DISALLOW_COPY_AND_MOVE(CalendarMonthPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_MONTH_PATTERN_H