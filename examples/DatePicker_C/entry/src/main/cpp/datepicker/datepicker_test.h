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

#ifndef DATE_PICKER_CAN_LOOP_TEST_H
#define DATE_PICKER_CAN_LOOP_TEST_H
#include "../common/common.h"

namespace ArkUIDatePickerCApiDemo {

class DatePickerTest {
public:
    ~DatePickerTest();
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
};

} // namespace ArkUIDatePickerCApiDemo
#endif // DATE_PICKER_CAN_LOOP_TEST_H
 