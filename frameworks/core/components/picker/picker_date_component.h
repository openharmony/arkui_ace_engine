/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_COMPONENT_H

#include "base/i18n/localization.h"
#include "core/components/picker/picker_base_component.h"

namespace OHOS::Ace {

class ACE_EXPORT PickerDateComponent : public PickerBaseComponent {
    DECLARE_ACE_TYPE(PickerDateComponent, PickerBaseComponent);

public:
    PickerDateComponent();

    ~PickerDateComponent() override = default;

    const PickerDate& GetStartDate() const
    {
        return startDateSolar_;
    }
    void SetStartDate(const PickerDate& value)
    {
        startDateSolar_ = value;
        AdjustSolarDate(startDateSolar_, limitStartDate_, limitEndDate_);
        startDateLunar_ = SolarToLunar(startDateSolar_);
    }

    const PickerDate& GetEndDate() const
    {
        return endDateSolar_;
    }
    void SetEndDate(const PickerDate& value)
    {
        endDateSolar_ = value;
        AdjustSolarDate(endDateSolar_, limitStartDate_, limitEndDate_);
        endDateLunar_ = SolarToLunar(endDateSolar_);
    }

    const PickerDate& GetSelectedDate() const
    {
        return selectedDate_;
    }
    void SetSelectedDate(const PickerDate& value)
    {
        selectedDate_ = value;
    }

    void SetOnDateChange(const std::function<void(const PickerDate&)>& value)
    {
        onDateChange_ = value;
    }

    void SetShowLunar(bool value)
    {
        lunar_ = value;
    }

    bool NeedRtlColumnOrder() const override
    {
        return true;
    }

    bool IsShowLunar() const override
    {
        return lunar_;
    }

    void OnTitleBuilding() override;

    void OnColumnsBuilding() override;

    void OnSelectedSaving() override;

    std::string GetSelectedObject(bool isColumnChange,
        const std::string& changeColumnTag, int status = -1) const override;

    void OnDataLinking(
        const std::string& tag, bool isAdd, uint32_t index, std::vector<std::string>& resultTags) override;

    void OnLunarCallback(bool checked, std::vector<std::string>& resultTags) override;

    void OnAnimationPlaying() override;

private:
    PickerDate GetCurrentDate() const;
    LunarDate GetCurrentLunarDate(uint32_t lunarYear) const;

    void HandleYearChange(bool isAdd, uint32_t index, std::vector<std::string>& resultTags);

    void HandleLunarYearChange(bool isAdd, uint32_t index);

    void HandleSolarYearChange(bool isAdd, uint32_t index);

    void HandleMonthChange(bool isAdd, uint32_t index, std::vector<std::string>& resultTags);

    void HandleLunarMonthChange(bool isAdd, uint32_t index);

    void HandleSolarMonthChange(bool isAdd, uint32_t index);

    void HandleDayChange(bool isAdd, uint32_t index, std::vector<std::string>& resultTags);

    void HandleSolarDayChange(bool isAdd, uint32_t index);

    void HandleLunarDayChange(bool isAdd, uint32_t index);

    void HandleAddLunarDayChange(uint32_t index);

    void HandleReduceLunarDayChange(uint32_t index);

    std::string GetYearFormatString(uint32_t year) const;

    std::string GetMonthFormatString(uint32_t month, bool isLunar, bool isLeap) const;

    std::string GetDayFormatString(uint32_t day, bool isLunar) const;

    LunarDate SolarToLunar(const PickerDate& date) const;
    PickerDate LunarToSolar(const LunarDate& date) const;

    bool GetLunarLeapMonth(uint32_t year, uint32_t& outLeapMonth) const;

    uint32_t GetLunarMaxDay(uint32_t year, uint32_t month, bool isLeap) const;

    void SolarColumnsBuilding(const PickerDate& current);

    void LunarColumnsBuilding(const LunarDate& current);

    int SolarDateCompare(const PickerDate& left, const PickerDate& right) const;

    int LunarDateCompare(const LunarDate& left, const LunarDate& right) const;

    void AdjustSolarDate(PickerDate& date) const;
    void AdjustSolarDate(PickerDate& date, const PickerDate& start, const PickerDate& end) const;

    void AdjustLunarDate(LunarDate& date) const;

    bool lunar_ = false;
    PickerDate startDateSolar_ = PickerDate(1970, 1, 1); // default start date is 1970-1-1 from FA document.
    LunarDate startDateLunar_;
    PickerDate endDateSolar_ = PickerDate(2100, 12, 31); // default end date is 2100-12-31 from FA document.
    LunarDate endDateLunar_;
    PickerDate selectedDate_ = PickerDate::Current();
    std::function<void(const PickerDate&)> onDateChange_;

    static const PickerDate limitStartDate_;
    static const PickerDate limitEndDate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_COMPONENT_H
