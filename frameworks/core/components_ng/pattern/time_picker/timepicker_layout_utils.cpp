/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/time_picker/timepicker_layout_utils.h"

#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

void TimePickerDialogTypeMargin::BothSidesMargin(bool isRtl, MarginProperty& margin,
    const RefPtr<DialogTheme>& dialogTheme, bool lessTwelve)
{
    if (lessTwelve) {
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }
    } else {
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }
    }
}

void TimePickerDialogTypeMargin::UpdateDialogMargin(bool isRtl, MarginProperty& margin,
    const RefPtr<DialogTheme>& dialogTheme, bool isLessThanTwelve)
{
    BothSidesMargin(isRtl, margin, dialogTheme, isLessThanTwelve);
    if (isLessThanTwelve) {
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    } else {
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
    }
}

} // namespace OHOS::Ace::NG
