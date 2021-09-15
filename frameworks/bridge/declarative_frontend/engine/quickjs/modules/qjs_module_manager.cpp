/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_module_manager.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_curves_module.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_matrix4_module.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_router_module.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

ModuleManager* ModuleManager::GetInstance()
{
    static ModuleManager instance;
    return &instance;
}

bool ModuleManager::InitModule(JSContext* ctx, const std::string& moduleName, JSValue& jsObject)
{
    static const std::unordered_map<std::string, void (*)(JSContext* ctx, JSValue& jsObject)> MODULE_LIST = {
        { "system.router", [](JSContext* ctx, JSValue& jsObject) { InitRouterModule(ctx, jsObject); } },
        { "ohos.router", [](JSContext* ctx, JSValue& jsObject) { InitRouterModule(ctx, jsObject); } },
        { "system.curves", [](JSContext* ctx, JSValue& jsObject) { InitCurvesModule(ctx, jsObject); } },
        { "ohos.curves", [](JSContext* ctx, JSValue& jsObject) { InitCurvesModule(ctx, jsObject); } },
        { "system.matrix4", [](JSContext* ctx, JSValue& jsObject) { InitMatrix4Module(ctx, jsObject); } },
        { "ohos.matrix4", [](JSContext* ctx, JSValue& jsObject) { InitMatrix4Module(ctx, jsObject); } },
    };
    auto iter = MODULE_LIST.find(moduleName);
    if (iter != MODULE_LIST.end()) {
        iter->second(ctx, jsObject);
        LOGD("ModuleManager InitModule is %{private}s", moduleName.c_str());
        return true;
    } else {
        LOGE("register module is not found");
        return false;
    }
}

JSValue SetTimeout(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return ModuleManager::GetInstance()->SetWaitTimer(ctx, argc, argv, false);
}

JSValue SetInterval(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return ModuleManager::GetInstance()->SetWaitTimer(ctx, argc, argv, true);
}

JSValue ClearTimeout(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return ModuleManager::GetInstance()->ClearWaitTimer(ctx, argc, argv, false);
}

JSValue ClearInterval(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return ModuleManager::GetInstance()->ClearWaitTimer(ctx, argc, argv, true);
}

JSValue ModuleManager::SetWaitTimer(JSContext* ctx, int32_t argc, JSValueConst* argv, bool isInterval)
{
    if (argc < 1) {
        LOGE("JsSetTimer: invalid callback value");
        return JS_NULL;
    }

    if (!JS_IsFunction(ctx, argv[0])) {
        LOGE("arg[0] is not function");
        return JS_NULL;
    }
    JSValue jsFunc = JS_DupValue(ctx, argv[0]);


    int index = 1;
    uint32_t delay = 0;
    if (JS_IsNumber(argv[1])) {
        JS_ToUint32(ctx, &delay, argv[1]);
        index = 2;
    }

    std::vector<JSValue> callbackArray;
    while (index < argc) {
        callbackArray.emplace_back(JS_DupValue(ctx, argv[index]));
        ++index;
    }

    uint32_t callbackId = ModuleManager::GetInstance()->AddCallback(jsFunc, callbackArray, isInterval);

    auto instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return JS_NULL;
    }
    instance->GetDelegate()->WaitTimer(std::to_string(callbackId), std::to_string(delay), isInterval, true);

    return JS_NewInt32(ctx, callbackId);
}

uint32_t ModuleManager::AddCallback(JSValue callbackFunc, std::vector<JSValue> callbackArray, bool isInterval)
{
    if (isInterval) {
        return AddCallback(intervalCallbackFuncMap_, intervalCallbackArrayMap_, callbackFunc, callbackArray);
    } else {
        return AddCallback(callbackFuncMap_, callbackArrayMap_, callbackFunc, callbackArray);
    }
}

uint32_t ModuleManager::AddCallback(std::unordered_map<uint32_t, JSValue>& callbackFuncMap,
        std::unordered_map<uint32_t, std::vector<JSValue>>& callbackArrayMap, JSValue callbackFunc,
        std::vector<JSValue> callbackArray)
{
    ++callbackId_;
    callbackFuncMap[callbackId_] = callbackFunc;
    if (!callbackArray.empty()) {
        callbackArrayMap[callbackId_] = callbackArray;
    }
    return callbackId_;
}

JSValue ModuleManager::GetCallbackFunc(uint32_t callbackId, bool isInterval)
{
    if (isInterval) {
        return intervalCallbackFuncMap_[callbackId];
    } else {
        return callbackFuncMap_[callbackId];
    }
}

std::vector<JSValue> ModuleManager::GetCallbackArray(uint32_t callbackId, bool isInterval)
{
    if (isInterval) {
        return GetCallbackArray(intervalCallbackArrayMap_, callbackId);
    } else {
        return GetCallbackArray(callbackArrayMap_, callbackId);
    }
}

std::vector<JSValue> ModuleManager::GetCallbackArray(
    std::unordered_map<uint32_t, std::vector<JSValue>>& callbackArrayMap, uint32_t callbackId)
{
    if (callbackArrayMap.find(callbackId) != callbackArrayMap.end()) {
        return callbackArrayMap[callbackId];
    }
    std::vector<JSValue> emptyRet;
    return emptyRet;
}

JSValue ModuleManager::ClearWaitTimer(JSContext* ctx, int32_t argc, JSValueConst* argv, bool isInterval)
{
    if (argc < 0 || !JS_IsNumber(argv[0])) {
        LOGE("argv[0] is not number");
        return JS_NULL;
    }

    uint32_t callbackId;
    JS_ToUint32(ctx, &callbackId, argv[0]);
    ModuleManager::GetInstance()->RemoveCallbackFunc(ctx, callbackId, isInterval);
    auto instance = static_cast<QJSDeclarativeEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("Can not cast Context to QJSDeclarativeEngineInstance object.");
        return JS_NULL;
    }
    instance->GetDelegate()->ClearTimer(std::to_string(callbackId));
    return JS_NULL;
}

void ModuleManager::RemoveCallbackFunc(JSContext* ctx, uint32_t callbackId, bool isInterval)
{
    if (isInterval) {
        RemoveCallbackFunc(ctx, intervalCallbackFuncMap_, intervalCallbackArrayMap_, callbackId);
    } else {
        RemoveCallbackFunc(ctx, callbackFuncMap_, callbackArrayMap_, callbackId);
    }
}

void ModuleManager::RemoveCallbackFunc(JSContext* ctx, std::unordered_map<uint32_t, JSValue>& callbackFuncMap,
        std::unordered_map<uint32_t, std::vector<JSValue>>& callbackArrayMap, uint32_t callbackId)
{
    JS_FreeValue(ctx, callbackFuncMap[callbackId]);
    callbackFuncMap.erase(callbackId);

    if (callbackArrayMap.find(callbackId) != callbackArrayMap.end()) {
        uint32_t index = 0;
        while (index < callbackArrayMap[callbackId].size()) {
            JS_FreeValue(ctx, callbackArrayMap[callbackId][index]);
            ++index;
        }
        callbackArrayMap.erase(callbackId);
    }
}

void ModuleManager::InitTimerModule(JSContext* ctx)
{
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JS_SetPropertyStr(ctx, globalObj, SET_TIMEOUT, JS_NewCFunction(ctx, SetTimeout, SET_TIMEOUT, 2));
    JS_SetPropertyStr(ctx, globalObj, SET_INTERVAL, JS_NewCFunction(ctx, SetInterval, SET_TIMEOUT, 2));
    JS_SetPropertyStr(ctx, globalObj, CLEAR_TIMEOUT, JS_NewCFunction(ctx, ClearTimeout, SET_TIMEOUT, 1));
    JS_SetPropertyStr(ctx, globalObj, CLEAR_INTERVAL, JS_NewCFunction(ctx, ClearInterval, SET_TIMEOUT, 1));
}

} // namespace OHOS::Ace::Framework