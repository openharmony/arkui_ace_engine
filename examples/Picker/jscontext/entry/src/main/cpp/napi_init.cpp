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
#include "hilog/log.h"
#include "napi/native_api.h"
#include <arkui/native_node_napi.h>
#include <map>
#include <string>

extern "C" napi_status napi_create_ark_context(napi_env env, napi_env *newEnv);
extern "C" napi_status napi_switch_ark_context(napi_env env);
extern "C" napi_status napi_destroy_ark_context(napi_env env);

static std::map<std::string, napi_env> envMaps_;

const int ATTR_INDEX_0 = 0;
const int ATTR_INDEX_1 = 1;
const int ATTR_INDEX_2 = 2;
const int ATTR_INDEX_3 = 3;
const int ATTR_INDEX_4 = 4;
const int BUFFER_SIZE = 4096;

std::string GetString(const napi_env &env, const napi_value &value)
{
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(BUFFER_SIZE);
    size_t length = 0;
    napi_get_value_string_utf8(env, value, buffer.get(), BUFFER_SIZE, &length);
    return std::string(buffer.get(), length);
}


// Helper functions for NAPI_Global_callFunctionInContext1
static napi_value LoadAndGetProperty(napi_env env, const char* path, const char* propertyName)
{
    napi_value plugin = nullptr;
    napi_status status = napi_load_module_with_info(env, path, "com.example.jscontext/entry", &plugin);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] load module info of env failed");
        return nullptr;
    }

    napi_value property = nullptr;
    status = napi_get_named_property(env, plugin, propertyName, &property);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] get name property of env failed");
        return nullptr;
    }
    return property;
}

static void CallFunctionAndLogResult(napi_env env, napi_value func, napi_value arg, const char* logPrefix)
{
    napi_value result = nullptr;
    napi_value args[1] = {arg};
    napi_status status = napi_call_function(env, nullptr, func, 1, args, &result);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] call function of env failed");
        return;
    }

    int32_t ret = 0;
    status = napi_get_value_int32(env, result, &ret);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] napi_get_value_int32 of env failed");
    } else {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] %s ret is %{public}d", logPrefix, ret);
    }
}

// context1
static napi_value NAPI_Global_callFunctionInContext1(napi_env env, napi_callback_info info)
{
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] NAPI_Global_callFunctionInContext1 called");
    napi_status status = napi_ok;

    size_t argc = 1;
    napi_value args[ATTR_INDEX_1] = {nullptr};
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        return nullptr;
    }

    napi_value getLocation1 = LoadAndGetProperty(env, "entry/src/main/ets/pages/plugin1", "GetLocation");
    napi_value getLocation2 = LoadAndGetProperty(env, "entry/src/main/ets/pages/plugin2", "GetLocation");

    if (getLocation1 != nullptr) {
        CallFunctionAndLogResult(env, args[ATTR_INDEX_0], getLocation1, "plugin1");
    }
    if (getLocation2 != nullptr) {
        CallFunctionAndLogResult(env, args[ATTR_INDEX_0], getLocation2, "plugin2");
    }

    OH_LOG_INFO(LOG_APP, "[jsMultiContext] NAPI_Global_callFunctionInContext1 finished");
    return nullptr;
}

// Helper functions for NAPI_Global_callFunctionInContext2
static napi_env CreateAndSwitchContext(napi_env env)
{
    napi_env newEnv = nullptr;
    napi_status status = napi_create_ark_context(env, &newEnv);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] create ark context failed");
        return nullptr;
    }
    napi_switch_ark_context(newEnv);
    return newEnv;
}

// context2
static napi_value NAPI_Global_callFunctionInContext2(napi_env env, napi_callback_info info)
{
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] NAPI_Global_callFunctionInContext2 called");

    size_t argc = 1;
    napi_value args[ATTR_INDEX_1] = {nullptr};
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        return nullptr;
    }

    napi_value getLocation1 = LoadAndGetProperty(env, "entry/src/main/ets/pages/plugin1", "GetLocation");
    napi_env newEnv2 = CreateAndSwitchContext(env);
    if (newEnv2 == nullptr) {
        return nullptr;
    }

    napi_value getLocation2 = LoadAndGetProperty(newEnv2, "entry/src/main/ets/pages/plugin2", "GetLocation");
    if (getLocation2 != nullptr) {
        CallFunctionAndLogResult(newEnv2, args[ATTR_INDEX_0], getLocation2, "plugin2 in new context");
    }

    napi_switch_ark_context(env);
    if (getLocation1 != nullptr) {
        CallFunctionAndLogResult(env, args[ATTR_INDEX_0], getLocation1, "plugin1 in original context");
    }

    OH_LOG_INFO(LOG_APP, "[jsMultiContext] NAPI_Global_callFunctionInContext2 finished");
    napi_destroy_ark_context(newEnv2);
    return nullptr;
}

// Helper functions for NAPI_Global_RequirePlugin
static napi_value SetupPluginEnv(napi_env env, napi_env pluginEnv, napi_value hmsValue)
{
    napi_status status = napi_switch_ark_context(pluginEnv);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] switch context status failed. %{public}d", status);
        return nullptr;
    }

    napi_value plugin_global;
    status = napi_get_global(pluginEnv, &plugin_global);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] napi_get_global failed. %{public}d", status);
        return nullptr;
    }

    status = napi_set_named_property(pluginEnv, plugin_global, "hms", hmsValue);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] napi_set_named_property failed. %{public}d", status);
    }
    return plugin_global;
}

static napi_value NAPI_Global_RequirePlugin(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[ATTR_INDEX_2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string id = GetString(env, args[ATTR_INDEX_0]);
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] native require plugin id is %{public}s", id.c_str());

    napi_env pluginEnv = nullptr;
    napi_status status = napi_create_ark_context(env, &pluginEnv);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] create ark context failed. %{public}d", status);
        return nullptr;
    }

    SetupPluginEnv(env, pluginEnv, args[ATTR_INDEX_1]);

    napi_value pluginObj = nullptr;
    status = napi_load_module_with_info(pluginEnv, id.c_str(), "com.example.jscontext/entry", &pluginObj);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] native napi_load_module_with_info failed");
    }

    napi_value car = nullptr;
    status = napi_get_named_property(pluginEnv, pluginObj, "car", &car);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] get car failed");
    }

    napi_switch_ark_context(env);
    return car;
}

// Helper functions for NAPI_Global_nativeRequirePluginComponent
static bool InitializeArkUIEnv(napi_env env)
{
    auto ret = OH_ArkUI_InitModuleForArkTSEnv(env);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] OH_ArkUI_InitModuleForArkTSEnv failed");
        return false;
    }
    return true;
}

static napi_value NAPI_Global_nativeRequirePluginComponent(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value args[ATTR_INDEX_3] = {};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] id = %{public}s", GetString(env, args[ATTR_INDEX_0]).c_str());

    ArkUI_NodeContentHandle nodeHandle = nullptr;
    int32_t code = OH_ArkUI_GetNodeContentFromNapiValue(env, args[ATTR_INDEX_1], &nodeHandle);
    if (code != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] getNodeContent failed");
    }

    napi_env newEnv2 = nullptr;
    napi_status status = napi_create_ark_context(env, &newEnv2);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] create ark context failed");
    }

    OH_LOG_INFO(LOG_APP, "[jsMultiContext] create NAPI_Global_nativeRequirePluginComponent p = %{public}p", newEnv2);
    envMaps_["envArkui"] = newEnv2;

    status = napi_switch_ark_context(newEnv2);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] switch component context failed");
    }

    InitializeArkUIEnv(newEnv2);

    std::string car = "car";
    napi_value pluginObj;
    napi_status status1 = napi_load_module_with_info(newEnv2, car.c_str(), "com.example.jscontext/entry", &pluginObj);
    if (status1 != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] napi_load_module_with_info failed");
    }

    napi_value carComponent = nullptr;
    status = napi_get_named_property(newEnv2, pluginObj, "InitBuilder", &carComponent);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] native fetch carContent failed");
    }

    napi_value result2 = nullptr;
    status = napi_call_function(newEnv2, pluginObj, carComponent, 1, &args[ATTR_INDEX_2], &result2);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] napi_call_function failed");
    }

    napi_switch_ark_context(env);
    return result2;
}

static napi_value NAPI_Global_nativeDestroyPluginComponent(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[ATTR_INDEX_1] = {};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    auto pluginName = GetString(env, args[ATTR_INDEX_0]);
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] DestroyPlugin %{public}s", pluginName.c_str());

    if (envMaps_.find(pluginName) != envMaps_.end()) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] DestroyPlugin success! p = %{public}p", envMaps_[pluginName]);

        OH_ArkUI_NotifyArkTSEnvDestroy(envMaps_[pluginName]);
        auto ret = napi_destroy_ark_context(envMaps_[pluginName]);
        if (ret != napi_ok) {
            OH_LOG_INFO(LOG_APP, "[jsMultiContext] DestroyPlugin failed!");
            return nullptr;
        }
        envMaps_.erase(pluginName);
    }
    return nullptr;
}

// Helper functions for NAPI_Global_nativeRequirePlugins
static bool SetupPluginEnvironment(napi_env env, const std::string& pluginName)
{
    if (envMaps_.find(pluginName) != envMaps_.end()) {
        return true;
    }

    napi_env newEnv = nullptr;
    napi_status status = napi_create_ark_context(env, &newEnv);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] create ark context of %{public}s failed", pluginName.c_str());
        return false;
    }

    envMaps_[pluginName] = newEnv;
    OH_LOG_INFO(LOG_APP, "[jsMultiContext] create envMaps_[%{public}s] p = %{public}p", pluginName.c_str(), newEnv);

    status = napi_switch_ark_context(newEnv);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] switch %{public}s failed", pluginName.c_str());
        return false;
    }

    if (!InitializeArkUIEnv(newEnv)) {
        return false;
    }

    return true;
}

static napi_value NAPI_Global_nativeRequirePlugins(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value args[ATTR_INDEX_4] = {};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    auto moduleName = GetString(env, args[ATTR_INDEX_0]);
    auto builderFunc = GetString(env, args[ATTR_INDEX_1]);
    auto pluginName = GetString(env, args[ATTR_INDEX_3]);
    if (!SetupPluginEnvironment(env, pluginName)) {
        return nullptr;
    }

    napi_value pluginObj;
    napi_status status = napi_load_module_with_info(
        envMaps_[pluginName], moduleName.c_str(), "com.example.jscontext/entry", &pluginObj);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] load module %{public}s failed", moduleName.c_str());
    }

    napi_value component = nullptr;
    status = napi_get_named_property(envMaps_[pluginName], pluginObj, builderFunc.c_str(), &component);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] fetch %{public}s failed", builderFunc.c_str());
    }

    napi_value result = nullptr;
    napi_value para[1] = {args[ATTR_INDEX_2]};
    status = napi_call_function(envMaps_[pluginName], pluginObj, component, 1, para, &result);
    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "[jsMultiContext] call %{public}s failed", builderFunc.c_str());
    }

    napi_switch_ark_context(env);
    return result;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        {"callFunctionInContext1", nullptr, NAPI_Global_callFunctionInContext1, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"callFunctionInContext2", nullptr, NAPI_Global_callFunctionInContext2, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"nativeRequirePlugin", nullptr, NAPI_Global_RequirePlugin, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"nativeRequirePluginComponent", nullptr, NAPI_Global_nativeRequirePluginComponent, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"nativeDestroyPluginComponent", nullptr, NAPI_Global_nativeDestroyPluginComponent, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"nativeRequirePlugins", nullptr, NAPI_Global_nativeRequirePlugins, nullptr, nullptr, nullptr, napi_default,
         nullptr}};
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[ATTR_INDEX_0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }