/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef ACE_MOCK_FRAMEWORKS_COMMON_SECURITY_COMPONENT_ERR_H
#define ACE_MOCK_FRAMEWORKS_COMMON_SECURITY_COMPONENT_ERR_H

#include <inttypes.h>

namespace OHOS {
namespace Security {
namespace SecurityComponent {
enum SCErrCode : int32_t {
    SC_OK = 0,

    SC_SERVICE_ERROR_SERVICE_NOT_EXIST = -55,
    SC_SERVICE_ERROR_COMPONENT_INFO_INVALID = -56,
    SC_SERVICE_ERROR_COMPONENT_NOT_EXIST = -58,
    SC_SERVICE_ERROR_CLICK_EVENT_INVALID = -60
};
} // namespace SecurityComponent
} // namespace Security
} // namespace OHOS
#endif // ACE_MOCK_FRAMEWORKS_COMMON_SECURITY_COMPONENT_ERR_H
