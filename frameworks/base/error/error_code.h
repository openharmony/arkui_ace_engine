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

#pragma once

#include <cstdint>

namespace OHOS::Ace {

// Common error code
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
constexpr int32_t ERROR_CODE_PERMISSION_DENIED = 201; // The application does not have permission to call the interface.
constexpr int32_t ERROR_CODE_PARAM_INVALID = 401;     // Invalid input parameter.
constexpr int32_t ERROR_CODE_SYSTEMCAP_ERROR = 801;   // The specified SystemCapability names was not found.

// Notification error code
constexpr int32_t ERROR_CODE_INTERNAL_ERROR = 100001;    // Internal error.
constexpr int32_t ERROR_CODE_URI_ERROR = 100002;         // Uri error.
constexpr int32_t ERROR_CODE_PAGE_STACK_FULL = 100003;   // The pages are pushed too much.
constexpr int32_t ERROR_CODE_NAMED_ROUTE_ERROR = 100004; // Named route error.
constexpr int32_t ERROR_CODE_URI_ERROR_LITE = 200002;    // Uri error for lite.

// push destination error code
constexpr int32_t ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED = 100005; // builder function not registered
constexpr int32_t ERROR_CODE_DESTINATION_NOT_FOUND = 100006;           // navDestination not found

// Send synchronous message error code
// No callback has been registered to process synchronous data transferring.
constexpr int32_t ERROR_CODE_UIEXTENSION_NOT_REGISTER_SYNC_CALLBACK = 100011;
// Transferring data failed
constexpr int32_t ERROR_CODE_UIEXTENSION_TRANSFER_DATA_FAILED = 100012;

// C-API errors
constexpr int32_t ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND = 106101;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED = 106102;

// Drag event error code
constexpr int32_t ERROR_CODE_DRAG_DATA_NOT_FOUND = 190001; // GetData failed, data not found.
constexpr int32_t ERROR_CODE_DRAG_DATA_ERROR = 190002;     // GetData failed, data error.

} // namespace OHOS::Ace