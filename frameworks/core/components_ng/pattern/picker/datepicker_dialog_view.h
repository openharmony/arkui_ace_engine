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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DatePickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void SetStartDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetEndDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetSelectedDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetShowLunar(const RefPtr<FrameNode>& frameNode, bool lunar = false);
    static void SetDateTextProperties(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties);
    static void SetTimeTextProperties(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogDateChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogDateAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogSwitchEvent(std::function<bool()> switchEvent);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& datePickerNode,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static RefPtr<FrameNode> CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateTitleButtonRowNode();
    static void CreateTitleIconNode(const RefPtr<FrameNode>& titleNode);
    static RefPtr<FrameNode> CreateDividerNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& datePickerNode, DialogEvent& acceptEvent);
    static RefPtr<FrameNode> CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
        const RefPtr<FrameNode>& datePickerNode);
    static RefPtr<FrameNode> CreateDateNode(int32_t dateNodeId, std::map<std::string, PickerDate> datePickerProperty,
        const PickerTextProperties& properties, bool isLunar, bool hasTime);
    static RefPtr<FrameNode> CreateColumnNode(int32_t nodeId, uint32_t showCount, bool isDate = true);
    static void CreateNormalDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount);
    static void CreateSingleDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount);
    static RefPtr<FrameNode> CreateTimeNode(std::map<std::string, PickerTime> timePickerProperty,
        const PickerTextProperties& properties, bool useMilitaryTime);

    static bool switchFlag_;

private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static void CreateLunarswitchNode(
        const RefPtr<FrameNode>& contentColumn, std::function<void(const bool)>&& changeEvent, bool isLunar);
    static void SetTitleMouseHoverEvent(const RefPtr<FrameNode>& titleRow);
    static void HandleMouseEvent(const RefPtr<FrameNode>& titleRow, bool isHover);
    static void PlayHoverAnimation(const RefPtr<FrameNode>& titleRow, const Color& color);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H
