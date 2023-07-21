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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_NG_H

#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CalendarPickerModelNG : public CalendarPickerModel {
public:
    void Create(const CalendarSettingData& settingData) override;
    void SetEdgeAlign(const CalendarEdgeAlign& alignType, const DimensionOffset& offset) override;
    void SetTextStyle(const PickerTextStyle& textStyle) override;
    void SetOnChange(SelectedChangeEvent&& onChange) override;
    void SetChangeEvent(SelectedChangeEvent&& onChange) override;

private:
    void LayoutPicker(const RefPtr<CalendarPickerPattern>& pickerPattern, RefPtr<FrameNode>& pickerNode,
        const CalendarSettingData& settingData, const RefPtr<CalendarTheme>& theme);
    RefPtr<FrameNode> CreateButtonChild(int32_t id, bool isAdd, const RefPtr<CalendarTheme>& theme);
    RefPtr<FrameNode> CreateButtonImageChild(bool isAdd, const RefPtr<CalendarTheme>& theme);
    RefPtr<FrameNode> CreateCalendarNodeChild(
        int32_t contentId, const CalendarSettingData& settingData, const RefPtr<CalendarTheme>& theme);
    RefPtr<FrameNode> CreateButtonFlexChild(int32_t buttonFlexId, const RefPtr<CalendarTheme>& theme);
    RefPtr<FrameNode> CreateDateTextNode(const std::string& textContent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_NG_H
