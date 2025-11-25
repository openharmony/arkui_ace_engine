/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MOCK_FORM_CONSTANTS_H
#define MOCK_FORM_CONSTANTS_H

namespace OHOS::AppExecFwk::Constants {
enum class Dimension : int8_t {
    DIMENSION_MIN = 1,
    DIMENSION_1_2 = DIMENSION_MIN,
    DIMENSION_2_2,
    DIMENSION_2_4,
    DIMENSION_4_4,
    DIMENSION_2_1,
    DIMENSION_1_1,
    DIMENSION_6_4,
    DIMENSION_2_3,
    DIMENSION_3_3,
    DIMENSION_MAX = DIMENSION_3_3
};
} // namespace OHOS::AppExecFwk::Constants

#endif // MOCK_FORM_CONSTANTS_H
