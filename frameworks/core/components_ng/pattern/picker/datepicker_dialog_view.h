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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DatePickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties,
        std::map<std::string, PickerDate> datePickerProperty, bool isLunar,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void SetStartDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value);
    static void SetEndDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value);
    static void SetSelectedDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value);
    static void SetShowLunar(bool lunar = false);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static RefPtr<FrameNode> CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H