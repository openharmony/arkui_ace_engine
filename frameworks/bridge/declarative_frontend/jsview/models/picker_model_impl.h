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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PICKER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PICKER_MODEL_IMPL_H

#include "core/components_ng/pattern/picker/picker_model.h"

namespace OHOS::Ace::Framework {
class DatePickerModelImpl : public DatePickerModel {
public:
    DatePickerModelImpl() = default;
    ~DatePickerModelImpl() override = default;

    void CreateDatePicker(RefPtr<PickerTheme> theme) override;
    void CreateTimePicker(RefPtr<PickerTheme> theme) override;
    void SetStartDate(const PickerDate& value) override;
    void SetEndDate(const PickerDate& value) override;
    void SetSelectedDate(const PickerDate& value) override;
    void SetShowLunar(bool lunar) override;
    void SetSelectedTime(const PickerTime& selectedTime) override;
    void SetHour24(bool value) override;
    void SetOnChange(DateChangeEvent&& onChange) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PICKER_MODEL_IMPL_H
