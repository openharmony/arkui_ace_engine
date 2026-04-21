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

#include <hilog/log.h>
#include <string>

#include "common/common.h"
#include "manager/plugin_manager.h"
#include "scenarios/ScenarioManager.h"


namespace {

const size_t ARGC_TWO = 2;          // Argument count for two parameters
const size_t ARGC_ONE = 1;          // Argument count for one parameter
const size_t ARGC_ZERO = 0;         // Argument count for zero parameters
const uint32_t FIRST_INDEX = 0;     // First index in array
const uint32_t SECOND_INDEX = 1;    // Second index in array

} // namespace


namespace NativeXComponentSample {

/**
 * @brief NAPI interface to switch scenarios
 * @param env NAPI environment
 * @param info Callback info containing two parameters: instanceId (string) and
 *             scenarioId (string)
 * @return undefined
 *
 * Usage example (ETS side):
 * import nativerender from 'libentry.so';
 * nativerender.switchScenario("xcomponent_instance_id", "scenario1");
 */
static napi_value SwitchScenario(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_TWO;
    napi_value args[2];
    napi_value thisVar;
    void* data;

    // Get parameters
    napi_status status = napi_get_cb_info(env, info, &argc, args, &thisVar,
        &data);
    if (status != napi_ok || argc < ARGC_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwitchScenario",
            "Invalid arguments, expected 2 parameters");
        napi_value result;
        napi_get_undefined(env, &result);
        return result;
    }

    // Get instanceId parameter
    size_t instanceIdLength = ARGC_ZERO;
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX], nullptr, ARGC_ZERO,
        &instanceIdLength);
    if (status != napi_ok || instanceIdLength == ARGC_ZERO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwitchScenario",
            "Failed to get instanceId string length");
        napi_value result;
        napi_get_undefined(env, &result);
        return result;
    }

    char* instanceId = new char[instanceIdLength + 1];
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX], instanceId,
        instanceIdLength + 1,
        &instanceIdLength);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwitchScenario",
            "Failed to get instanceId string value");
        delete[] instanceId;
        napi_value result;
        napi_get_undefined(env, &result);
        return result;
    }

    // Get scenarioId parameter
    size_t scenarioIdLength = ARGC_ZERO;
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX + 1], nullptr, ARGC_ZERO,
        &scenarioIdLength);
    if (status != napi_ok || scenarioIdLength == ARGC_ZERO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwitchScenario",
            "Failed to get scenarioId string length");
        delete[] instanceId;
        napi_value result;
        napi_get_undefined(env, &result);
        return result;
    }

    char* scenarioId = new char[scenarioIdLength + 1];
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX + 1], scenarioId,
        scenarioIdLength + 1,
        &scenarioIdLength);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwitchScenario",
            "Failed to get scenarioId string value");
        delete[] instanceId;
        delete[] scenarioId;
        napi_value result;
        napi_get_undefined(env, &result);
        return result;
    }

    // Call ScenarioManager to switch scenario
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "SwitchScenario",
        "Switching to scenario '%{public}s' for instance '%{public}s",
        scenarioId, instanceId);

    ScenarioManager::GetInstance().SetScenarioForInstance(instanceId,
        scenarioId);

    // Clean up resources
    delete[] instanceId;
    delete[] scenarioId;

    napi_value result;
    napi_get_undefined(env, &result);
    return result;
}

/**
 * @brief NAPI interface to get all available scenarios
 * @param env NAPI environment
 * @param info Callback info
 * @return Array containing scenario information
 *
 * Return format: [{id: "scenario1", name: "登录页", description: "..."}, ...]
 */
static napi_value GetAvailableScenarios(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_ZERO;
    napi_value args[1];
    napi_value thisVar;
    void* data;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &thisVar,
        &data);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN,
            "GetAvailableScenarios",
            "Failed to get callback info");
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    // Get all scenarios
    const auto& scenarios = ScenarioManager::GetInstance().GetAllScenarios();

    // Create array
    napi_value scenarioArray;
    status = napi_create_array_with_length(env, scenarios.size(),
        &scenarioArray);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN,
            "GetAvailableScenarios",
            "Failed to create array");
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    // Fill scenario information
    uint32_t index = FIRST_INDEX;
    for (const auto& scenarioPair : scenarios) {
        napi_value scenarioObj;
        napi_create_object(env, &scenarioObj);

        // scenarioPair.second is ScenarioBase* pointer
        ScenarioBase* scenario = scenarioPair.second;

        // Set id property
        napi_value idValue;
        napi_create_string_utf8(env, scenario->GetId(), NAPI_AUTO_LENGTH,
            &idValue);
        napi_set_named_property(env, scenarioObj, "id", idValue);

        // Set name property
        napi_value nameValue;
        napi_create_string_utf8(env, scenario->GetName(), NAPI_AUTO_LENGTH,
            &nameValue);
        napi_set_named_property(env, scenarioObj, "name", nameValue);

        // Set description property
        napi_value descValue;
        napi_create_string_utf8(env, scenario->GetDescription(),
            NAPI_AUTO_LENGTH, &descValue);
        napi_set_named_property(env, scenarioObj, "description", descValue);

        // Set interfaceCount property
        napi_value interfaceCountValue;
        napi_create_int32(env, scenario->GetInterfaceCount(),
            &interfaceCountValue);
        napi_set_named_property(env, scenarioObj, "interfaceCount",
            interfaceCountValue);

        // Set testCaseCount property
        napi_value testCaseCountValue;
        napi_create_int32(env, scenario->GetTestCaseCount(),
            &testCaseCountValue);
        napi_set_named_property(env, scenarioObj, "testCaseCount",
            testCaseCountValue);

        // Add to array
        napi_set_element(env, scenarioArray, index++, scenarioObj);
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GetAvailableScenarios",
        "Returning %{public}zu scenarios", scenarios.size());

    return scenarioArray;
}

/**
 * @brief NAPI interface to get current scenario info for a specific instance
 * @param env NAPI environment
 * @param info Callback info containing one parameter: instanceId (string)
 * @return Current scenario info object, or null if not set
 */
static napi_value GetCurrentScenario(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_ONE;
    napi_value args[1];
    napi_value thisVar;
    void* data;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &thisVar,
        &data);
    if (status != napi_ok || argc < ARGC_ONE) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetCurrentScenario",
            "Invalid arguments, expected 1 parameter");
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    // Get instanceId parameter
    size_t instanceIdLength = ARGC_ZERO;
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX], nullptr, ARGC_ZERO,
        &instanceIdLength);
    if (status != napi_ok || instanceIdLength == ARGC_ZERO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetCurrentScenario",
            "Failed to get instanceId string length");
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    char* instanceId = new char[instanceIdLength + 1];
    status = napi_get_value_string_utf8(env, args[FIRST_INDEX], instanceId,
        instanceIdLength + 1,
        &instanceIdLength);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetCurrentScenario",
            "Failed to get instanceId string value");
        delete[] instanceId;
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    // Get current scenario
    auto* scenario = ScenarioManager::GetInstance().GetScenario(instanceId);
    delete[] instanceId;

    if (scenario == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GetCurrentScenario",
            "No scenario set for instance");
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }

    // Create scenario info object
    napi_value scenarioObj;
    napi_create_object(env, &scenarioObj);

    napi_value idValue;
    napi_create_string_utf8(env, scenario->GetId(), NAPI_AUTO_LENGTH,
        &idValue);
    napi_set_named_property(env, scenarioObj, "id", idValue);

    napi_value nameValue;
    napi_create_string_utf8(env, scenario->GetName(), NAPI_AUTO_LENGTH,
        &nameValue);
    napi_set_named_property(env, scenarioObj, "name", nameValue);

    napi_value descValue;
    napi_create_string_utf8(env, scenario->GetDescription(),
        NAPI_AUTO_LENGTH, &descValue);
    napi_set_named_property(env, scenarioObj, "description", descValue);

    napi_value interfaceCountValue;
    napi_create_int32(env, scenario->GetInterfaceCount(),
        &interfaceCountValue);
    napi_set_named_property(env, scenarioObj, "interfaceCount",
        interfaceCountValue);

    napi_value testCaseCountValue;
    napi_create_int32(env, scenario->GetTestCaseCount(),
        &testCaseCountValue);
    napi_set_named_property(env, scenarioObj, "testCaseCount",
        testCaseCountValue);

    return scenarioObj;
}

EXTERN_C_START

/**
 * @brief Initializes scenarios when module is loaded
 */
__attribute__((constructor))
static void InitializeScenariosOnLoad()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init",
        "Module loaded, initializing PluginManager to trigger "
        "scenario registration");
    // Trigger entire initialization chain by accessing PluginManager singleton
    PluginManager::GetInstance();
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init",
        "PluginManager initialized, scenarios should be registered");
}

/**
 * @brief NAPI module initialization function
 * @param env NAPI environment
 * @param exports Exports object
 * @return Exports object
 */
static napi_value Init(napi_env env, napi_value exports)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init",
        "Init begins (NAPI)");
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init",
            "env or exports is null");
        return nullptr;
    }

    // Export PluginManager interfaces (this also triggers singleton
    // initialization, but already initialized in constructor)
    PluginManager::GetInstance()->Export(env, exports);

    // Define scenario management related NAPI interfaces
    napi_property_descriptor scenarioProps[] = {
        {"switchScenario", nullptr, SwitchScenario, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"getAvailableScenarios", nullptr, GetAvailableScenarios, nullptr,
         nullptr, nullptr, napi_default, nullptr},
        {"getCurrentScenario", nullptr, GetCurrentScenario, nullptr, nullptr,
         nullptr, napi_default, nullptr},
    };

    // Export scenario management interfaces
    napi_value scenarioExports;
    napi_create_object(env, &scenarioExports);
    napi_define_properties(env, scenarioExports,
        sizeof(scenarioProps) / sizeof(scenarioProps[FIRST_INDEX]),
        scenarioProps);

    // Add scenario management interfaces to exports
    napi_set_named_property(env, exports, "scenarioManager",
        scenarioExports);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init",
        "Init completed successfully");
    return exports;
}

EXTERN_C_END

static napi_module nativerenderModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "nativerender",
    .nm_priv = ((void*)0),
    .reserved = { 0 }
};

/**
 * @brief Registers the NAPI module
 */
extern "C" __attribute__((constructor)) void RegisterModule(void)
{
    napi_module_register(&nativerenderModule);
}

} // namespace NativeXComponentSample
