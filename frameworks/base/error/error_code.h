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
// Permission verification failed, application which is not a system application uses system API.
constexpr int32_t ERROR_CODE_VERIFICATION_FAILED = 202;
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
// Parameter error.
constexpr int32_t ERROR_CODE_PARAM_ERROR = 100023;
// The inspector parameter depth must bu greater than zero.
constexpr int32_t ERROR_CODE_INSPECTOR_PARAM_DEPTH_INVALID  = 100024;

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
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE  = 106203;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD = 106204;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD  = 106301;
constexpr int32_t ERROR_CODE_NATIVE_IMPL_FORCE_DARK_CONFIG_INVALID = 106205;
constexpr int32_t ERROR_CODE_NODE_IS_ADOPTED = 106206;
constexpr int32_t ERROR_CODE_NODE_HAS_PARENT = 106207;
constexpr int32_t ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208;
constexpr int32_t ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209;
constexpr int32_t ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210;

// C-API RenderNode errors
constexpr int32_t ERROR_CODE_NOT_CUSTOM_NODE = 106401;
constexpr int32_t ERROR_CODE_CHILD_EXISTED = 106402;
constexpr int32_t ERROR_CODE_RENDER_PARENT_EXISTED = 106403;
constexpr int32_t ERROR_CODE_CHILD_RENDER_NOT_EXIST = 106404;
constexpr int32_t ERROR_CODE_PARAM_OUT_OF_RANGE = 106405;
constexpr int32_t ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406;
constexpr int32_t ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407;
constexpr int32_t ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408;

// AI error for Canvas,XComponent
constexpr int32_t ERROR_CODE_AI_ANALYSIS_UNSUPPORTED = 110001;
constexpr int32_t ERROR_CODE_AI_ANALYSIS_IS_ONGOING = 110002;
constexpr int32_t ERROR_CODE_AI_ANALYSIS_IS_STOPPED = 110003;

// Drawable error
constexpr int32_t ERROR_CODE_DRAWABLE_LOADER_ERROR = 111001;

// Drag event error code (190001 ~ 191000)
constexpr int32_t ERROR_CODE_DRAG_DATA_NOT_FOUND = 190001;  // GetData failed, data not found.
constexpr int32_t ERROR_CODE_DRAG_DATA_ERROR = 190002;      // GetData failed, data error.
constexpr int32_t ERROR_CODE_DRAG_DATA_NOT_ONDROP = 190003; // Operation not allowed for current phase.
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
constexpr int32_t ERROR_CODE_CANVAS_CONTEXT_NOT_BOUND = 103702;
constexpr int32_t ERROR_CODE_CANVAS_ERROR_CONTEXT = 103703;
constexpr int32_t ERROR_CODE_OFFSCREEN_CANVAS_HAS_DETACHED = 103704;

// ForEach and Repeat error code
constexpr int32_t ERROR_CODE_FOR_EACH_DEFAULT_ID_GENERATOR_INVALID = 103801;
constexpr int32_t ERROR_CODE_REPEAT_ITEM_BUILDER_FUNCTION_UNSPECIFIED = 103802;
constexpr int32_t ERROR_CODE_REPEAT_GET_RID4_INDEX_OUT_OF_RANGE = 103803;
constexpr int32_t ERROR_CODE_REPEAT_LAZY_LOADING_ILLEGAL_OPERATION = 103804;
constexpr int32_t ERROR_CODE_REPEAT_DEFAULT_ID_GENERATOR_INVALID = 103805;

// JS FrameNode error code
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_NODE_IS_NOT_MODIFIABLE = 100021;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_IS_NOT_SUPPORT_CROSS_LANGUAGE = 100022;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_NODE_IS_NULL_OR_TYPE_INCORRECT = 100023;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_HAS_NOT_COMMON_ANCESTOR_NODE = 100024;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_CURRENT_NODE_IS_ADOPTED = 100025;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_NODE_IS_DISPOSED = 100026;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_INPUT_NODE_IS_ADOPTED = 100027;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_CURRENT_NODE_IS_NOT_ON_MAINTREE = 100028;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_RECYCLE_NOT_SUPPORTED_FOR_VIEWV2 = 100029;
constexpr int32_t ERROR_CODE_JS_FRAME_NODE_RECYCLE_NOT_SUPPORTED_IN_BUILDER_NODE = 100030;

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
constexpr int32_t ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003;
constexpr int32_t ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004;
// observer node render state error code
constexpr int32_t NODE_RENDER_STATE_REGISTER_ERR_CODE = 161001;

// FromHtml error code
constexpr int32_t ERROR_CODE_FROM_HTML_CONVERT_ERROR = 170001;
constexpr int32_t ERROR_CODE_STYLED_STRING_CONVERT_ERROR = 170002;

// Gesture error code (180001 ~ 181000)
constexpr int32_t ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001;
constexpr int32_t ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002;
constexpr int32_t ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT = 180006;

// ResourceManager error code
constexpr int32_t ERROR_CODE_PARAMETER_LESS_THAN_ZERO = 100101;
constexpr int32_t ERROR_CODE_PARAMETER_TYPE_ERROR = 100102;
constexpr int32_t ERROR_CODE_NOT_RUN_ON_UI_THREAD = 100103;

// State management error code (130000 ~ 139999)
constexpr int32_t ERROR_CODE_JS_ADD_MONITOR_FAIL_TARGET_ILLEGAL = 130000;
constexpr int32_t ERROR_CODE_JS_ADD_MONITOR_FAIL_PATH_ILLEGAL = 130001;
constexpr int32_t ERROR_CODE_JS_ADD_MONITOR_FAIL_FUNC_ILLEGAL = 130002;

// State management error code (140000 ~ 149999)
constexpr int32_t ERROR_CODE_JS_UNSUPPORTED_KEY_IN_ENV = 140000;
constexpr int32_t ERROR_CODE_JS_FUNC_CALLED_IN_COMPUTED_ILLEGAL = 140001;
constexpr int32_t ERROR_CODE_JS_FUNC_CALLED_IN_MONITOR_ILLEGAL = 140002;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_APPSTORAGE_V2_UNSUPPORTED_TYPE = 140103;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_APPSTORAGE_V2_INVALID_DEFAULT_CREATOR = 140104;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_KEYS_DUPLICATE = 140105;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_NOT_SUPPORT_AREA_MODE_MESSAGE = 140106;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_MISMATCH_BETWEEN_KEY_AND_TYPE = 140107;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_LACK_TYPE = 140108;
constexpr int32_t ERROR_CODE_JS_INVALID_SET_IN_BUILDER = 140109;
constexpr int32_t ERROR_CODE_JS_NON_TRACK_PROPERTY_ON_UI = 140110;
constexpr int32_t ERROR_CODE_JS_MISSING_PROVIDE_DEFAULT_VALUE_FOR_CONSUME_CONSUMER = 140112;
constexpr int32_t ERROR_CODE_JS_REUSABLE_V2_OLD_TOOLCHAIN = 140113;
constexpr int32_t ERROR_CODE_JS_DUPLICATE_PROVIDE_KEY = 140114;
constexpr int32_t ERROR_CODE_JS_ILLEGAL_TYPE_FOR_V1_STATE_VALUE = 140115;
constexpr int32_t ERROR_CODE_JS_PERSISTENCE_V2_APPSTORAGE_V2_INVALID_KEY = 140116;
constexpr int32_t ERROR_CODE_JS_USE_REUSABLE_V2_IN_COMPONENT = 140117;
constexpr int32_t ERROR_CODE_JS_REQUIRE_INTERNAL_ERROR = 140121;

} // namespace OHOS::Ace
