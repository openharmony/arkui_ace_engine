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

#ifndef PICKER_HEIGHT_AND_COUNT_CAPI_COMMON_H
#define PICKER_HEIGHT_AND_COUNT_CAPI_COMMON_H

#include <hilog/log.h>
#include <napi/native_api.h>

namespace PickerHeightAndCountCapi {
constexpr unsigned int LOG_PRINT_DOMAIN = 0xFF00;
constexpr int PARAM_1 = 1;
constexpr int PARAM_64 = 64;
constexpr int DEFAULT_MARGIN = 10;
constexpr float DEFAULT_WIDTH = 320.0f;
constexpr float DEFAULT_HEIGHT = 360.0f;
} // namespace PickerHeightAndCountCapi

#endif // PICKER_HEIGHT_AND_COUNT_CAPI_COMMON_H
