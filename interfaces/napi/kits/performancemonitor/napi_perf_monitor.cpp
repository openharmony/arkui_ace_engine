/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include "base/perfmonitor/perf_monitor.h"
#include "napi_perf_monitor.h"

namespace OHOS::Ace::Napi {
static constexpr uint32_t LAST_DOWN = 0;
static constexpr uint32_t LAST_UP = 1;
static constexpr uint32_t FIRST_MOVE = 2;
static constexpr uint32_t PERF_TOUCH_EVENT = 0;
static constexpr uint32_t PERF_MOUSE_EVENT = 1;
static constexpr uint32_t PERF_TOUCHPAD_EVENT = 2;
static constexpr uint32_t PERF_JOYSTICK_EVENT = 3;
static constexpr uint32_t PERF_KEY_EVENT = 4;
constexpr int FIRST_ARG_INDEX = 0;
constexpr int SECOND_ARG_INDEX = 1;
constexpr int THIRD_ARG_INDEX = 2;
constexpr int ARGC_NUMBER_ONE = 1;
constexpr int ARGC_NUMBER_TWO = 2;
constexpr int ARGC_NUMBER_THREE = 3;

napi_value PreParseParams(napi_env& env, napi_callback_info& info, size_t& argc, napi_value* argv)
{
    napi_value thisVar;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    return nullptr;
}

bool PerfValueType(const napi_env& env, const napi_value& value, const napi_valuetype expectType)
{
    napi_valuetype valueType;
    napi_status status = napi_typeof(env, value, &valueType);
    if (status != napi_ok) {
        return false;
    }
    if (valueType != expectType) {
        return false;
    }
    return true;
}

void GetStringParam(const napi_env& env, const napi_value& value, std::string& dest)
{
    constexpr int nameMaxSize = 1024;
    char buf[nameMaxSize] = {0};
    size_t len = 0;
    napi_get_value_string_utf8(env, value, buf, nameMaxSize, &len);
    dest = std::string {buf};
}

bool ParseStringParam(const napi_env& env, const napi_value& value, std::string& dest)
{
    if (PerfValueType(env, value, napi_string)) {
        GetStringParam(env, value, dest);
        return true;
    }
    if (PerfValueType(env, value, napi_number)) {
        int64_t destI64;
        napi_get_value_int64(env, value, &destI64);
        dest = std::to_string(destI64);
        return true;
    }
    if (PerfValueType(env, value, napi_undefined)) {
        dest = "undefined";
        return true;
    }
    if (PerfValueType(env, value, napi_null)) {
        dest = "null";
        return true;
    }
    return false;
}

bool ParseInt32Param(const napi_env& env, const napi_value& value, int& dest)
{
    if (!PerfValueType(env, value, napi_number)) {
        return false;
    }
    napi_get_value_int32(env, value, &dest);
    return true;
}

bool ParseInt64Param(const napi_env& env, const napi_value& value, int64_t& dest)
{
    if (!PerfValueType(env, value, napi_number)) {
        return false;
    }
    napi_get_value_int64(env, value, &dest);
    return true;
}

static void SceneStart(std::string sceneId, int type, std::string note)
{
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor != nullptr) {
        pMonitor->Start(sceneId, static_cast<PerfActionType>(type), note);
    }
}

static void SceneEnd(std::string sceneId, bool isJsApi)
{
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor != nullptr) {
        pMonitor->End(sceneId, isJsApi);
    }
}

static void InputEvent(int type, int sourceType, int64_t time)
{
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor != nullptr) {
        pMonitor->RecordInputEvent(static_cast<PerfActionType>(type), static_cast<PerfSourceType>(sourceType), time);
    }
}

static napi_value JSSceneStart(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_NUMBER_THREE;
    napi_value argv[ARGC_NUMBER_THREE];
    PreParseParams(env, info, argc, argv);
    NAPI_ASSERT(env, argc >= ARGC_NUMBER_TWO, "Wrong number of arguments");
    if (argc < ARGC_NUMBER_TWO) {
        return nullptr;
    }

    std::string sceneId = "";
    if (!ParseStringParam(env, argv[FIRST_ARG_INDEX], sceneId)) {
        return nullptr;
    }

    int inputType = 0;
    if (!ParseInt32Param(env, argv[SECOND_ARG_INDEX], inputType)) {
        return nullptr;
    }

    std::string note;
    if (argc >= ARGC_NUMBER_THREE && !ParseStringParam(env, argv[THIRD_ARG_INDEX], note)) {
        return nullptr;
    }
    SceneStart(sceneId, inputType, note);
    return nullptr;
}

static napi_value JSSceneEnd(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_NUMBER_ONE;
    napi_value argv[ARGC_NUMBER_ONE];
    PreParseParams(env, info, argc, argv);
    NAPI_ASSERT(env, argc >= ARGC_NUMBER_ONE, "Wrong number of arguments");
    if (argc < ARGC_NUMBER_ONE) {
        return nullptr;
    }

    std::string sceneId = "";
    if (!ParseStringParam(env, argv[FIRST_ARG_INDEX], sceneId)) {
        return nullptr;
    }
    SceneEnd(sceneId, true);
    return nullptr;
}

static napi_value JSRecordInputEventTime(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_NUMBER_THREE;
    napi_value argv[ARGC_NUMBER_THREE];
    PreParseParams(env, info, argc, argv);
    NAPI_ASSERT(env, argc >= ARGC_NUMBER_TWO, "Wrong number of arguments");
    if (argc < ARGC_NUMBER_TWO) {
        return nullptr;
    }

    int type = 0;
    if (!ParseInt32Param(env, argv[FIRST_ARG_INDEX], type)) {
        return nullptr;
    }

    int sourceType = 0;
    if (!ParseInt32Param(env, argv[SECOND_ARG_INDEX], sourceType)) {
        return nullptr;
    }

    int64_t time = 0;
    if (!ParseInt64Param(env, argv[THIRD_ARG_INDEX], time)) {
        return nullptr;
    }
    InputEvent(type, sourceType, time);
    return nullptr;
}


/*
 * function for module exports
 */
static napi_value PerfMonitorInit(napi_env env, napi_value exports)
{
    napi_value actionType = nullptr;
    napi_create_object(env, &actionType);
    napi_value prop = nullptr;
    napi_create_uint32(env, LAST_DOWN, &prop);
    napi_set_named_property(env, actionType, "LAST_DOWN", prop);
    napi_create_uint32(env, LAST_UP, &prop);
    napi_set_named_property(env, actionType, "LAST_UP", prop);
    napi_create_uint32(env, FIRST_MOVE, &prop);
    napi_set_named_property(env, actionType, "FIRST_MOVE", prop);

    napi_value sourceType = nullptr;
    napi_create_object(env, &sourceType);
    prop = nullptr;
    napi_create_uint32(env, PERF_TOUCH_EVENT, &prop);
    napi_set_named_property(env, sourceType, "PERF_TOUCH_EVENT", prop);
    napi_create_uint32(env, PERF_MOUSE_EVENT, &prop);
    napi_set_named_property(env, sourceType, "PERF_MOUSE_EVENT", prop);
    napi_create_uint32(env, PERF_TOUCHPAD_EVENT, &prop);
    napi_set_named_property(env, sourceType, "PERF_TOUCHPAD_EVENT", prop);
    napi_create_uint32(env, PERF_JOYSTICK_EVENT, &prop);
    napi_set_named_property(env, sourceType, "PERF_JOYSTICK_EVENT", prop);
    napi_create_uint32(env, PERF_KEY_EVENT, &prop);
    napi_set_named_property(env, sourceType, "PERF_KEY_EVENT", prop);

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("begin", JSSceneStart),
        DECLARE_NAPI_FUNCTION("end", JSSceneEnd),
        DECLARE_NAPI_FUNCTION("recordInputEventTime", JSRecordInputEventTime),
        DECLARE_NAPI_PROPERTY("ActionType", actionType),
        DECLARE_NAPI_PROPERTY("SourceType", sourceType),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

/*
 * performanceMonitor module definition
 */
static napi_module perfmonitor_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PerfMonitorInit,
    .nm_modname = "arkui.performanceMonitor",
    .nm_priv = ((void *)0),
    .reserved = {0}
};

/*
 * Module registration
 */
extern "C" __attribute__((constructor)) void RegisterModule(void)
{
    napi_module_register(&perfmonitor_module);
}
}
