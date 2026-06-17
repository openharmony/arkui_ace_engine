/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_TYPES_H

#include <cstdint>

namespace OHOS::Ace {

enum DatePickerType {
    TIME = 0,
    DATE,
};

enum class DatePickerMode : uint32_t {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2,
};

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

constexpr double PICKER_ANGULAR_VELOCITY_FACTOR = 0.001f;
constexpr float PICKER_ANGULAR_VELOCITY_SLOW = 0.07f;
constexpr float PICKER_ANGULAR_VELOCITY_MEDIUM = 0.2f;
constexpr float PICKER_ANGULAR_VELOCITY_FAST = 0.54f;
constexpr float PICKER_DISPLAY_CONTROL_RATIO_VERY_SLOW = 1.19f;
constexpr float PICKER_DISPLAY_CONTROL_RATIO_SLOW = 1.51f;
constexpr float PICKER_DISPLAY_CONTROL_RATIO_MEDIUM = 1.48f;
constexpr float PICKER_DISPLAY_CONTROL_RATIO_FAST = 1.33f;
constexpr float PICKER_CROWN_SENSITIVITY_LOW = 0.8f;
constexpr float PICKER_CROWN_SENSITIVITY_MEDIUM = 1.0f;
constexpr float PICKER_CROWN_SENSITIVITY_HIGH = 1.2f;
constexpr uint32_t PICKER_SELECT_AVERAGE = 2;
constexpr int32_t INVALID_CROWNSENSITIVITY = -1;
constexpr int32_t DEFAULT_CROWNSENSITIVITY = 1;
constexpr int32_t INVALID_SELECTED_COLUMN_INDEX = -1;
constexpr int32_t CROWN_SENSITIVITY_MIN = 0;
constexpr int32_t CROWN_SENSITIVITY_MAX = 2;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_TYPES_H
