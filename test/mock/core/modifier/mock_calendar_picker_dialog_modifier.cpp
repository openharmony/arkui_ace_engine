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
#include "core/interfaces/native/node/calendar_picker_dialog_modifier.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "mock_calendar_picker_dialog_modifier.h"
namespace OHOS::Ace::NG::NodeModifier {
bool MockCalendarPickerDialogModifier::isNull_ = false;
void MockCalendarPickerDialogModifier::SetModifierNull(bool null)
{
    isNull_ = null;
}

bool MockCalendarPickerDialogModifier::GetModifierNull()
{
    return isNull_;
}

ArkUI_Bool CheckOrientationChange()
{
    return CalendarDialogView::CheckOrientationChange();
}

const ArkUICalendarPickerDialogModifier* GetCalendarPickerDialogModifier()
{
    if (MockCalendarPickerDialogModifier::GetModifierNull()) {
        return nullptr;
    }

    static const ArkUICalendarPickerDialogModifier modifier = {
        .checkOrientationChange = CheckOrientationChange,
    };
    return &modifier;
}
}