/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_DATE_PICKER_DIALOG_H
#define CAPI_STUBS_MOCK_DATE_PICKER_DIALOG_H

#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {
class MockDatePickerDialog {
public:
    static void Show(const PickerDialogInfo& dialogInfo, const DatePickerSettingData& settingData);
    static PickerDialogInfo GetDialogInfo();
    static DatePickerSettingData GetSettingData();

private:
    static PickerDialogInfo dialogInfo_;
    static DatePickerSettingData settingData_;
};
} // namespace OHOS::Ace::NG
#endif // CAPI_STUBS_MOCK_DATE_PICKER_DIALOG_H
