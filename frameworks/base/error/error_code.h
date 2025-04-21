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
constexpr int32_t ERROR_CODE_CAPI_INIT_ERROR = 500;     // C-API impl not initialized yet.
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
// Forbid cascade uiextension
constexpr int32_t ERROR_CODE_UIEXTENSION_FORBID_CASCADE = 100013;
// The uiextension ability exited abnormally.
constexpr int32_t ERROR_CODE_UIEXTENSION_EXITED_ABNORMALLY = 100014;
// The lifecycle of uiextension ability is timeout.
constexpr int32_t ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT = 100015;
// The uiextension ability has timed out processing the key event.
constexpr int32_t ERROR_CODE_UIEXTENSION_EVENT_TIMEOUT = 100016;
// The component not supported prevent function.
constexpr int32_t ERROR_CODE_COMPONENT_NOT_SUPPORTED_PREVENT_FUNCTION = 100017;
// The uiextension ability foreground failed.
constexpr int32_t ERROR_CODE_UIEXTENSION_FOREGROUND_FAILED = 100018;
// The uiextension ability background failed.
constexpr int32_t ERROR_CODE_UIEXTENSION_BACKGROUND_FAILED = 100019;
// The uiextension ability destruction failed.
constexpr int32_t ERROR_CODE_UIEXTENSION_DESTRUCTION_FAILED = 100020;
// The uiextension transparent node detected.
constexpr int32_t ERROR_CODE_UIEXTENSION_TRANSPARENT = 100021;

// C-API errors
constexpr int32_t ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND = 106101;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED = 106102;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR = 106103;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR = 106104;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_EXIST = 106105;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_CHILD_NODE_EXIST = 106106;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID = 106108;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_EVENT_NO_RETURN = 106109;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_INDEX_INVALID  = 106200;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED  = 106201;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_BUFFER_SIZE_ERROR  = 106202;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD  = 106301;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE  = 106203;

// AI error for Canvas,XComponent
constexpr int32_t ERROR_CODE_AI_ANALYSIS_UNSUPPORTED = 110001;
constexpr int32_t ERROR_CODE_AI_ANALYSIS_IS_ONGOING = 110002;
constexpr int32_t ERROR_CODE_AI_ANALYSIS_IS_STOPPED = 110003;

// Drag event error code (190001 ~ 191000)
constexpr int32_t ERROR_CODE_DRAG_DATA_NOT_FOUND = 190001;  // GetData failed, data not found.
constexpr int32_t ERROR_CODE_DRAG_DATA_ERROR = 190002;      // GetData failed, data error.
constexpr int32_t ERROR_CODE_DRAG_DATA_NOT_ONDROP = 190003; // Operation no allowed for current pharse.
constexpr int32_t ERROR_CODE_DRAG_OPERATION_FAILED = 190004; // Operation failed.

// custom dialog error code
constexpr int32_t ERROR_CODE_DIALOG_CONTENT_ERROR = 103301;
constexpr int32_t ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST = 103302;
constexpr int32_t ERROR_CODE_DIALOG_CONTENT_NOT_FOUND = 103303;
constexpr int32_t ERROR_CODE_TARGET_INFO_NOT_EXIST = 103304;
constexpr int32_t ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE = 103305;

// toast error code
constexpr int32_t ERROR_CODE_TOAST_NOT_FOUND = 103401;

// XComponent error code
constexpr int32_t ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501;

// Video error Code
constexpr int32_t ERROR_CODE_VIDEO_CREATE_PLAYER_FAILED = 103601;
constexpr int32_t ERROR_CODE_VIDEO_SOURCE_INVALID = 103602;

// Canvas error code
constexpr int32_t ERROR_CODE_CANVAS_PARAM_INVALID = 103701;

// BindSheet error code
constexpr int32_t ERROR_CODE_BIND_SHEET_CONTENT_ERROR = 120001;
constexpr int32_t ERROR_CODE_BIND_SHEET_CONTENT_ALREADY_EXIST = 120002;
constexpr int32_t ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND = 120003;
constexpr int32_t ERROR_CODE_TARGET_ID_NOT_EXIST = 120004;
constexpr int32_t ERROR_CODE_TARGET_NOT_ON_MAIN_TREE = 120005;
constexpr int32_t ERROR_CODE_TARGET_NOT_PAGE_CHILD = 120006;

// RequestFocus error code (150001 ~ 151000)
constexpr int32_t ERROR_CODE_NON_FOCUSABLE = 150001;
constexpr int32_t ERROR_CODE_NON_FOCUSABLE_ANCESTOR = 150002;
constexpr int32_t ERROR_CODE_NON_EXIST = 150003;

// ComponentSnapshot error code (160001 ~ 161000), 1610001 ~ 163000 reserved
constexpr int32_t ERROR_CODE_COMPONENT_SNAPSHOT_IMAGE_LOAD_ERROR = 160001;
constexpr int32_t ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002;

// FromHtml error code
constexpr int32_t ERROR_CODE_FROM_HTML_CONVERT_ERROR = 170001;
constexpr int32_t ERROR_CODE_STYLED_STRING_CONVERT_ERROR = 170002;

// Gesture error code (180001 ~ 181000)
constexpr int32_t ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001;
constexpr int32_t ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002;
} // namespace OHOS::Ace
