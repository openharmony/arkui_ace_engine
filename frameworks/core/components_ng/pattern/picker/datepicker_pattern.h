/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_PATTERN_H

#include <optional>

#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_data.h"
#include "core/components/theme/app_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/datepicker_accessibility_property.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"

namespace OHOS::Ace::NG {
class InspectorFilter;
namespace {
const Dimension FOCUS_PAINT_WIDTH = 2.0_vp;
constexpr Dimension PICKER_DIALOG_MARGIN_FORM_EDGE = 24.0_vp;
constexpr Dimension PICKER_MARGIN_FROM_TITLE_AND_BUTTON = 8.0_vp;
}

class DatePickerPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(DatePickerPattern, LinearLayoutPattern);

public:
    DatePickerPattern() : LinearLayoutPattern(false) {};

    ~DatePickerPattern() override = default;

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
        return MakeRefPtr<DatePickerEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DataPickerRowLayoutProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paintMethod = MakeRefPtr<DatePickerPaintMethod>(WeakClaim(this));
        paintMethod->SetEnabled(enabled_);
        paintMethod->SetBackgroundColor(backgroundColor_);
        return paintMethod;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DatePickerAccessibilityProperty>();
    }

    void SetConfirmNode(WeakPtr<FrameNode> buttonConfirmNode)
    {
        weakButtonConfirm_ = buttonConfirmNode;
    }

    void SetCancelNode(WeakPtr<FrameNode> buttonCancelNode)
    {
        weakButtonCancel_ = buttonCancelNode;
    }

    void SetNextPrevButtonNode(WeakPtr<FrameNode> nextPrevButtonNode)
    {
        nextPrevButtonNode_ = nextPrevButtonNode;
    }

    void SetIsNext(bool isNext)
    {
        isNext_ = isNext;
    }

    void SetLunarSwitchTextNode(WeakPtr<FrameNode> lunarSwitchTextNode)
    {
        weakLunarSwitchText_ = lunarSwitchTextNode;
    }

    void SetLunarSwitchCheckbox(WeakPtr<FrameNode> lunarSwitchCheckbox)
    {
        weakLunarSwitchCheckbox_ = lunarSwitchCheckbox;
    }

    void OnFontConfigurationUpdate() override;

    void OnFontScaleConfigurationUpdate() override;

    void OnLanguageConfigurationUpdate() override;

    void OnColorConfigurationUpdate() override;

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

    void SetChangeCallback(ColumnChangeCallback&& value);

    void HandleColumnChange(const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, bool needNotify);

    void SolarColumnsBuilding(const PickerDate& current);

    void LunarColumnsBuilding(const LunarDate& current);

    void SolarMonthDaysColumnsBuilding(const PickerDate& current);

    void LunarMonthDaysColumnBuilding(const LunarDate& current);

    void HandleYearChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags);

    void HandleMonthChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags);

    void HandleLunarMonthChange(bool isAdd, uint32_t index);

    void HandleLunarYearChange(bool isAdd, uint32_t index);

    void HandleSolarYearChange(bool isAdd, uint32_t index);

    LunarDate GetCurrentLunarDate(uint32_t lunarYear) const;

    void OrderCurrentLunarDate(
        RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay) const;

    void HandleSolarMonthChange(bool isAdd, uint32_t index);

    void HandleDayChange(bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags);

    void HandleReduceLunarDayChange(uint32_t index);

    void HandleLunarDayChange(bool isAdd, uint32_t index);

    void HandleAddLunarDayChange(uint32_t index);

    void HandleSolarDayChange(bool isAdd, uint32_t index);

    void IncreaseLinkageYearMonth(PickerDate& date);

    void ReduceLinkageYearMonth(PickerDate& date);

    void HandleSolarMonthDaysChange(bool isAdd, uint32_t index);

    void HandleLunarMonthDaysChange(bool isAdd, uint32_t index);

    void HandleAddLunarMonthDaysChange(uint32_t index);

    void HandleReduceLunarMonthDaysChange(uint32_t index);

    LunarDate GetCurrentLunarDateByMonthDaysColumn(uint32_t lunarYear) const;

    PickerDate GetCurrentDate() const;

    void SetEventCallback(EventCallback&& value);

    void FireChangeEvent(bool refresh);

    void FlushColumn();

    void FlushMonthDaysColumn();

    void AdjustLunarDate(LunarDate& date);

    int LunarDateCompare(const LunarDate& left, const LunarDate& right) const;

    std::unordered_map<std::string, RefPtr<FrameNode>> GetAllChildNode();

    void OrderAllChildNode(RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay);

    RefPtr<FrameNode> GetColumn(const int32_t& tag) const
    {
        auto iter = std::find_if(datePickerColumns_.begin(), datePickerColumns_.end(), [&tag](const auto& c) {
                auto column = c.Upgrade();
                return column && column->GetId() == tag;
            });
        return (iter == datePickerColumns_.end()) ? nullptr : (*iter).Upgrade();
    }

    void SetColumn(const RefPtr<FrameNode>& value)
    {
        datePickerColumns_.emplace_back(value);
    }

    void ClearColumn()
    {
        datePickerColumns_.clear();
    }

    void SetShowLunar(bool value)
    {
        isForceUpdate_ = value != lunar_;
        lunar_ = value;
    }

    bool IsShowLunar() const
    {
        return lunar_;
    }

    void SetCanLoop(bool value)
    {
        isLoop_ = value;
    }

    bool GetCanLoop() const
    {
        auto datePickerRowLayoutProperty = GetLayoutProperty<DataPickerRowLayoutProperty>();
        CHECK_NULL_RETURN(datePickerRowLayoutProperty, isLoop_);
        return datePickerRowLayoutProperty->GetCanLoopValue(true);
    }

    void SetShowMonthDaysFlag(bool value)
    {
        showMonthDays_ = value;
    }

    bool ShowMonthDays() const
    {
        return showMonthDays_;
    }

    void SetShowTimeFlag(bool value)
    {
        showTime_ = value;
    }

    void SetShowLunarSwitch(bool value)
    {
        showLunarSwitch_ = value;
    }

    bool GetShowLunarSwitch()
    {
        return showLunarSwitch_;
    }

    const EventMarker& GetDialogAcceptEvent() const
    {
        return OnDialogAccept_;
    }
    void SetDialogAcceptEvent(const EventMarker& value)
    {
        OnDialogAccept_ = value;
    }

    const EventMarker& GetDialogCancelEvent() const
    {
        return OnDialogCancel_;
    }
    void SetDialogCancelEvent(const EventMarker& value)
    {
        OnDialogCancel_ = value;
    }

    const EventMarker& GetDialogChangeEvent() const
    {
        return OnDialogChange_;
    }
    void SetDialogChangeEvent(const EventMarker& value)
    {
        OnDialogChange_ = value;
    }

    void SetResizePickerItemHeight(double resizePickerItemHeight)
    {
        resizePickerItemHeight_ = resizePickerItemHeight;
    }

    double GetResizePickerItemHeight() const
    {
        return resizePickerItemHeight_;
    }

    void SetResizeFlag(bool resizeFlag)
    {
        resizeFlag_ = resizeFlag;
    }

    bool GetResizeFlag() const
    {
        return resizeFlag_;
    }

    void SetIsShowInDialog(bool isShowInDialog)
    {
        isShowInDialog_ = isShowInDialog;
    }

    bool GetIsShowInDialog() const
    {
        return isShowInDialog_;
    }

    uint32_t GetOptionCount(RefPtr<FrameNode>& frameNode)
    {
        return options_[frameNode].size();
    }

    PickerDateF GetOptionValue(RefPtr<FrameNode>& frameNode, uint32_t index)
    {
        if (index >= GetOptionCount(frameNode)) {
            LOGE("index out of range.");
            return {};
        }
        return options_[frameNode][index];
    }

    const std::vector<PickerDateF>& GetAllOptions(RefPtr<FrameNode>& frameNode)
    {
        return options_[frameNode];
    }

    const std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>>& GetOptions() const
    {
        return options_;
    }

    uint32_t GetShowCount() const
    {
        return showCount_;
    }

    void SetShowCount(uint32_t showCount)
    {
        showCount_ = showCount;
    }

    void SetDateOrder(std::string dateOrder)
    {
        isDateOrderChange_ = dateOrder != dateOrder_;
        dateOrder_ = dateOrder;
    }

    static std::string GetYearFormatString(uint32_t year)
    {
        return PickerStringFormatter::GetYear(year);
    }

    static std::string GetMonthFormatString(uint32_t month, bool isLunar, bool isLeap)
    {
        if (isLunar) {
            return PickerStringFormatter::GetLunarMonth(month, isLeap);
        }
        return PickerStringFormatter::GetSolarMonth(month);
    }

    static std::string GetDayFormatString(uint32_t day, bool isLunar)
    {
        if (isLunar) {
            return PickerStringFormatter::GetLunarDay(day);
        }
        return PickerStringFormatter::GetSolarDay(day);
    }

    uint32_t GetLunarMaxDay(uint32_t year, uint32_t month, bool isLeap) const;

    bool GetLunarLeapMonth(uint32_t year, uint32_t& outLeapMonth) const;

    LunarDate SolarToLunar(const PickerDate& date) const;

    PickerDate LunarToSolar(const LunarDate& date) const;

    void UpdateCurrentOffset(float offset);

    void OnDataLinking(
        const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags);

    void HandleMonthDaysChange(
        const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index, std::vector<RefPtr<FrameNode>>& resultTags);

    std::string GetSelectedObject(bool isColumnChange, int status = -1) const;

    const LunarDate& GetSelectDate()
    {
        return selectedLunar_;
    }

    void SetSelectDate(const PickerDate& value)
    {
        selectedDate_ = value;
        isFiredDateChange_ = firedDateStr_.has_value() && firedDateStr_.value() == GetSelectedObject(false);
        firedDateStr_.reset();
        if (selectedDate_.GetYear() <= 0) {
            LOGW("selectedDate error");
            selectedDate_ = PickerDate::Current();
        }
        AdjustSolarDate(selectedDate_, startDateSolar_, endDateSolar_);
        selectedLunar_ = SolarToLunar(selectedDate_);
    }

    const PickerDate& GetSelectedDate()
    {
        return selectedDate_;
    }

    void SetStartDate(const PickerDate& value)
    {
        startDateSolar_ = value;
        AdjustSolarDate(startDateSolar_, limitStartDate_, limitEndDate_);
        startDateLunar_ = SolarToLunar(startDateSolar_);
    }

    const LunarDate& GetStartDateLunar()
    {
        return startDateLunar_;
    }

    const PickerDate& GetStartDateSolar()
    {
        return startDateSolar_;
    }

    void SetEndDate(const PickerDate& value)
    {
        endDateSolar_ = value;
        AdjustSolarDate(endDateSolar_, limitStartDate_, limitEndDate_);
        endDateLunar_ = SolarToLunar(endDateSolar_);
    }

    const LunarDate& GetEndDateLunar()
    {
        return endDateLunar_;
    }

    const PickerDate& GetEndDateSolar()
    {
        return endDateSolar_;
    }

    void SetMode(const DatePickerMode& value)
    {
        datePickerMode_ = value;
    }

    const DatePickerMode& GetMode()
    {
        return datePickerMode_;
    }

    void AdjustSolarDate(PickerDate& date, const PickerDate& start, const PickerDate& end) const
    {
        if (SolarDateCompare(date, start) < 0) {
            date = start;
            return;
        }
        if (SolarDateCompare(date, end) > 0) {
            date = end;
        }
    }

    void AdjustSolarDate(PickerDate& date) const
    {
        AdjustSolarDate(date, startDateSolar_, endDateSolar_);
    }

    static int SolarDateCompare(const PickerDate& left, const PickerDate& right)
    {
        static const int leftEqualRight = 0; // means left = right
        static const int leftGreatRight = 1; // means left > right
        static const int leftLessRight = -1; // means left < right
        if (left.GetYear() > right.GetYear()) {
            return leftGreatRight;
        }
        if (left.GetYear() < right.GetYear()) {
            return leftLessRight;
        }
        if (left.GetMonth() > right.GetMonth()) {
            return leftGreatRight;
        }
        if (left.GetMonth() < right.GetMonth()) {
            return leftLessRight;
        }
        if (left.GetDay() > right.GetDay()) {
            return leftGreatRight;
        }
        if (left.GetDay() < right.GetDay()) {
            return leftLessRight;
        }
        return leftEqualRight;
    }

    bool HasYearNode() const
    {
        return yearId_.has_value();
    }

    int32_t GetYearId()
    {
        if (!yearId_.has_value()) {
            yearId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return yearId_.value();
    }

    bool HasMonthNode() const
    {
        return monthId_.has_value();
    }

    int32_t GetMonthId()
    {
        if (!monthId_.has_value()) {
            monthId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return monthId_.value();
    }

    bool HasDayNode() const
    {
        return dayId_.has_value();
    }

    int32_t GetDayId()
    {
        if (!dayId_.has_value()) {
            dayId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return dayId_.value();
    }

    bool HasMonthDaysNode() const
    {
        return monthDaysId_.has_value();
    }

    int32_t GetMonthDaysId()
    {
        if (!monthDaysId_.has_value()) {
            monthDaysId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return monthDaysId_.value();
    }

    bool HasTitleNode() const
    {
        return titleId_.has_value();
    }

    bool SetTitleId(const int32_t id)
    {
        if (HasTitleNode()) {
            return false;
        }
        titleId_ = id;
        return true;
    }

    int32_t GetTitleId()
    {
        if (!titleId_.has_value()) {
            titleId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return titleId_.value();
    }

    bool HasButtonTitleNode() const
    {
        return ButtonTitleId_.has_value();
    }

    int32_t GetButtonTitleId()
    {
        if (!ButtonTitleId_.has_value()) {
            ButtonTitleId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return ButtonTitleId_.value();
    }

    bool HasDividerNode() const
    {
        return DividerId_.has_value();
    }

    int32_t GetDividerId()
    {
        if (!DividerId_.has_value()) {
            DividerId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return DividerId_.value();
    }

    void SetBackgroundColor(const Color& color)
    {
        backgroundColor_ = color;
    }

    static const std::string& GetYear(uint32_t year);

    static const std::string& GetSolarMonth(uint32_t month);

    static const std::string& GetSolarDay(uint32_t day);

    static const std::string& GetLunarMonth(uint32_t month, bool isLeap);

    static const std::string& GetLunarDay(uint32_t day);

    const std::string GetText();

    FocusPattern GetFocusPattern() const override
    {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, FocusPattern());
        auto pickerTheme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_RETURN(pickerTheme, FocusPattern());
        auto focusColor = pickerTheme->GetFocusColor();
        FocusPaintParam focusPaintParams;
        focusPaintParams.SetPaintColor(focusColor);
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParams };
    }

    void SetCurrentFocusKeyID(int32_t value)
    {
        focusKeyID_ = value;
    }

    int32_t GetCurrentFocusKeyID()
    {
        return focusKeyID_;
    }

    void SetCurrentPage(uint32_t value)
    {
        currentPage_ = value;
    }

    uint32_t GetCurrentPage()
    {
        return currentPage_;
    }

    bool NeedAdaptForAging();

    void ShowTitle(int32_t titleId);
    std::string GetVisibleColumnsText();
    void GetColumnText(const RefPtr<FrameNode>& columnNode, std::string& result);
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void SetContentRowNode(RefPtr<FrameNode>& contentRowNode)
    {
        contentRowNode_ = contentRowNode;
    }
    void SetbuttonTitleNode(RefPtr<FrameNode>& buttonTitleNode)
    {
        buttonTitleNode_ = buttonTitleNode;
    }

    void SetPickerTag(bool isPicker)
    {
        isPicker_ = isPicker;
    }

    void SetFocusDisable();
    void SetFocusEnable();
    static const std::string GetFormatString(PickerDateF data);

    void HasUserDefinedDisappearFontFamily(bool isUserDefined)
    {
        hasUserDefinedDisappearFontFamily_ = isUserDefined;
    }

    bool GetHasUserDefinedDisappearFontFamily()
    {
        return hasUserDefinedDisappearFontFamily_;
    }

    void HasUserDefinedNormalFontFamily(bool isUserDefined)
    {
        hasUserDefinedNormalFontFamily_ = isUserDefined;
    }

    bool GetHasUserDefinedNormalFontFamily()
    {
        return hasUserDefinedNormalFontFamily_;
    }

    void HasUserDefinedSelectedFontFamily(bool isUserDefined)
    {
        hasUserDefinedSelectedFontFamily_ = isUserDefined;
    }

    bool GetHasUserDefinedSelectedFontFamily()
    {
        return hasUserDefinedSelectedFontFamily_;
    }

    void updateFontConfigurationEvent(const std::function<void()>& closeDialogEvent)
    {
        closeDialogEvent_ = closeDialogEvent;
    }

    const PickerTextProperties& GetTextProperties() const
    {
        return textProperties_;
    }

    void SetTextProperties(const PickerTextProperties& properties)
    {
        textProperties_ = properties;
        if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
            isUserSetGradientFont_ = true;
            gradientHeight_ = properties.disappearTextStyle_.fontSize.value();
        }

        if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
            isUserSetGradientFont_ = true;
            gradientHeight_ = std::max(properties.normalTextStyle_.fontSize.value(), gradientHeight_);
        }

        if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
            isUserSetDividerSpacingFont_ = true;
            dividerSpacing_ = properties.selectedTextStyle_.fontSize.value();
        }
    }

    bool GetIsUserSetDividerSpacingFont()
    {
        return isUserSetDividerSpacingFont_;
    }

    bool GetIsUserSetGradientFont()
    {
        return isUserSetGradientFont_;
    }

    Dimension GetDividerSpacing()
    {
        return dividerSpacing_;
    }

    Dimension GetGradientHeight()
    {
        return gradientHeight_;
    }

    void SetPaintDividerSpacing(float& value)
    {
        paintDividerSpacing_ = value;
    }

    float GetPaintDividerSpacing()
    {
        return paintDividerSpacing_;
    }

    static bool ReportDateChangeEvent(int32_t nodeId, const std::string& compName,
        const std::string& eventName, const std::string& eventData);

    void SetUserDefinedOpacity(double opacity)
    {
        curOpacity_ = opacity;
    }

    void SetEnableHapticFeedback(bool value)
    {
        if (isEnableHaptic_ != value) {
            isHapticChanged_ = true;
        }
        isEnableHaptic_ = value;
    }

    bool GetEnableHapticFeedback() const
    {
        return isEnableHaptic_;
    }

    void ColumnPatternInitHapticController();
    void ColumnPatternInitHapticController(const RefPtr<FrameNode>& columnNode);
    void ColumnPatternStopHaptic();

    void SetDigitalCrownSensitivity(int32_t crownSensitivity);
    void UpdateUserSetSelectColor();
    void UpdateDisappearTextStyle(const PickerTextStyle& textStyle);
    void UpdateNormalTextStyle(const PickerTextStyle& textStyle);
    void UpdateSelectedTextStyle(const PickerTextStyle& textStyle);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    static void Init();
    void InitDisabled();
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void PaintFocusState();
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);
    void InitFocusEvent();
    void InitSelectorProps();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void GetInnerFocusButtonPaintRect(RoundRect& paintRect, float focusButtonXOffset);
    void UpdateFocusButtonState();
    void SetHaveFocus(bool haveFocus);
    void UpdateColumnButtonStyles(const RefPtr<FrameNode>& columnNode, bool haveFocus, bool needMarkDirty);
    PickerDate GetCurrentDateByMonthDaysColumn() const;
    PickerDate GetCurrentDateByYearMonthDayColumn() const;
    void OrderCurrentDateByYearMonthDayColumn(
        RefPtr<FrameNode>& stackYear, RefPtr<FrameNode>& stackMonth, RefPtr<FrameNode>& stackDay) const;
    void FillSolarYearOptions(const PickerDate& current, RefPtr<FrameNode>& yearColumn);
    void UpdateTitleTextColor(const RefPtr<FrameNode>& buttonTitleNode, const RefPtr<PickerTheme>& pickerTheme);
    void FillLunarMonthDaysOptions(const LunarDate& current, RefPtr<FrameNode>& monthDaysColumn);
    void AdjustSolarStartEndDate();
    void AdjustLunarStartEndDate();
    void UpdateButtonMargin(
        const RefPtr<FrameNode>& buttonNode, const RefPtr<DialogTheme>& dialogTheme, const bool isConfirmOrNextNode);
    void UpdateButtonNode(const RefPtr<FrameNode>& buttonNode, const bool isConfirmNode);
    void ShowColumnByDatePickMode();
    void UpdateStackPropVisibility(const RefPtr<FrameNode>& stackNode,
        const VisibleType visibleType, const int32_t weight);
    void ClearFocus();
    void SetDefaultFocus();
    bool IsCircle();
    bool CurrentIsLunar();
#ifdef SUPPORT_DIGITAL_CROWN
    void InitOnCrownEvent(const RefPtr<FocusHub>& focusHub);
    bool OnCrownEvent(const CrownEvent& event);
#endif
    void InitFocusKeyEvent();
    void FlushChildNodes();
    void UpdateLunarSwitch();
    void UpdateDateOrder();
    void UpdateDialogAgingButton(const RefPtr<FrameNode>& buttonNode, const bool isNext);
    Dimension ConvertFontScaleValue(const Dimension& fontSizeValue);

    void UpdateTextStyleCommon(
        const PickerTextStyle& textStyle,
        const TextStyle& defaultTextStyle,
        std::function<void(const Color&)> updateTextColorFunc,
        std::function<void(const Dimension&)> updateFontSizeFunc,
        std::function<void(const std::vector<std::string>&)> updateFontFamilyFunc);

    RefPtr<ClickEvent> clickEventListener_;
    bool enabled_ = true;
    int32_t focusKeyID_ = 0;
    uint32_t currentPage_ = 0;
    std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>> options_;
    uint32_t showCount_ = 0;
    std::string dateOrder_ = "";
    std::vector<WeakPtr<FrameNode>> datePickerColumns_;
    bool lunar_ = false;
    bool isLoop_ = true;
    bool showMonthDays_ = false;
    bool showTime_ = false;
    bool showLunarSwitch_ = false;
    Color backgroundColor_ = Color::WHITE;
    std::optional<int32_t> yearId_;
    std::optional<int32_t> monthId_;
    std::optional<int32_t> dayId_;
    std::optional<int32_t> monthDaysId_;
    std::optional<int32_t> dateNodeId_;
    std::optional<int32_t> titleId_;
    std::optional<int32_t> ButtonTitleId_;
    std::optional<int32_t> DividerId_;
    double resizePickerItemHeight_ = 0.0;
    bool resizeFlag_ = false;
    bool isShowInDialog_ = false;
    bool focusEventInitialized_ = false;
    bool haveFocus_ = false;
    bool useButtonFocusArea_ = false;
    Dimension selectorItemRadius_ = 8.0_vp;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    EventMarker OnDialogAccept_;
    EventMarker OnDialogCancel_;
    EventMarker OnDialogChange_;
    WeakPtr<FrameNode> weakButtonConfirm_;
    WeakPtr<FrameNode> weakButtonCancel_;
    WeakPtr<FrameNode> weakLunarSwitchText_;
    WeakPtr<FrameNode> weakLunarSwitchCheckbox_;
    WeakPtr<FrameNode> nextPrevButtonNode_;
    bool isNext_ = true;
    PickerDate startDateSolar_ = PickerDate(1970, 1, 1); // default start date is 1970-1-1 from FA document.
    LunarDate startDateLunar_;
    PickerDate endDateSolar_ = PickerDate(2100, 12, 31); // default end date is 2100-12-31 from FA document.
    LunarDate endDateLunar_;
    PickerDate selectedDate_ = PickerDate::Current();
    LunarDate selectedLunar_;
    PickerDate startDefaultDateSolar_ = PickerDate(1970, 1, 1); // default start date is 1970-1-1 from FA document.
    PickerDate endDefaultDateSolar_ = PickerDate(2100, 12, 31); // default end date is 2100-12-31 from FA document.
    const PickerDate limitStartDate_ = PickerDate(1900, 1, 31);
    const PickerDate limitEndDate_ = PickerDate(2100, 12, 31);
    static bool inited_;
    static const std::string empty_;
    static const PickerDateF emptyPickerDate_;
    static std::unordered_map<uint32_t, std::string> years_;       // year from 1900 to 2100,count is 201
    static std::unordered_map<uint32_t, std::string> solarMonths_; // solar month from 1 to 12,count is 12
    static std::unordered_map<uint32_t, std::string> solarDays_;   // solar day from 1 to 31, count is 31
    static std::unordered_map<uint32_t, std::string> lunarMonths_; // lunar month from 1 to 24, count is 24
    static std::unordered_map<uint32_t, std::string> lunarDays_;   // lunar day from 1 to 30, count is 30
    static std::vector<std::string> tagOrder_;    // year month day tag order
    static std::vector<std::string> localizedMonths_;
    WeakPtr<FrameNode> contentRowNode_;
    WeakPtr<FrameNode> buttonTitleNode_;
    bool isPicker_ = false;
    bool isFiredDateChange_ = false;
    bool isForceUpdate_ = false;
    bool isDateOrderChange_ = false;
    std::optional<std::string> firedDateStr_;
    void CalcLeftTotalColumnWidth(const RefPtr<FrameNode>& host, float &leftTotalColumnWidth, float childSize);
    bool CheckFocusID(int32_t childSize);
    bool ParseDirectionKey(RefPtr<DatePickerColumnPattern>& pattern, KeyCode& code, uint32_t totalOptionCount,
                          int32_t childSize);
    bool ReportDateChangeEvent(const std::string& compName,
        const std::string& eventName, const std::string& eventData);

    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;
    std::function<void()> closeDialogEvent_;
    bool isUserSetDividerSpacingFont_ = false;
    bool isUserSetGradientFont_ = false;
    Dimension gradientHeight_;
    Dimension dividerSpacing_;
    float paintDividerSpacing_ = 1.0f;
    PickerTextProperties textProperties_;
    double curOpacity_ = 1.0;
    DatePickerMode datePickerMode_ = DatePickerMode::DATE;
    bool isFocus_ = true;
    bool isEnableHaptic_ = true;
    bool isHapticChanged_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerPattern);
    std::string selectedColumnId_;
    bool lastTimeIsLuanar_ = true;
    bool isFirstTimeSetFocus_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_PATTERN_H
