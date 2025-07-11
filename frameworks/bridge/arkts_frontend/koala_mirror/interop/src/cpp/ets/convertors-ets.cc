/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <map>
#include "convertors-ets.h"
#include "signatures.h"
#include "interop-logging.h"
#include "interop-types.h"

static const char* callCallbackFromNative = "callCallbackFromNative";
static const char* callCallbackFromNativeSig = "IJI:I";

static const char* FAST_NATIVE_PREFIX = "#F$";

const bool registerByOne = true;

static bool registerNatives(ets_env *env, const ets_class clazz, const std::vector<std::tuple<std::string, std::string, void*, int>> impls) {
    std::vector<EtsNativeMethod> methods;
    methods.reserve(impls.size());
    bool result = true;
    for (const auto &[name, type, func, flag] : impls) {
        EtsNativeMethod method;
        method.name = name.c_str();
        method.func = func;
        method.signature = (flag & ETS_SLOW_NATIVE_FLAG) == 0 ? FAST_NATIVE_PREFIX : nullptr;
        if (registerByOne) {
            result &= env->RegisterNatives(clazz, &method, 1) >= 0;
            if (env->ErrorCheck()) {
                //env->ErrorDescribe();
                env->ErrorClear();
            }
        }
        else {
            methods.push_back(method);
        }
    }
    if (!registerByOne) {
        result = env->RegisterNatives(clazz, methods.data(), static_cast<ets_int>(methods.size())) >= 0;
    }
    return registerByOne ? true : result;
}

bool registerAllModules(ets_env *env) {
    auto moduleNames = EtsExports::getInstance()->getModules();

    for (auto it = moduleNames.begin(); it != moduleNames.end(); ++it) {
        std::string className = EtsExports::getInstance()->getClasspath(*it);
        ets_class nativeModule = env->FindClass(className.c_str());
        if (nativeModule == nullptr) {
            LOGE("Cannot find managed class %s", className.c_str());
            continue;
        }
        if (!registerNatives(env, nativeModule, EtsExports::getInstance()->getMethods(*it))) {
            return false;
        }
    }

    return true;
}

extern "C" ETS_EXPORT ets_int ETS_CALL EtsNapiOnLoad(ets_env *env) {
    LOGE("Use ETSNAPI")
    if (!registerAllModules(env)) {
        LOGE("Failed to register ets modules");
        return ETS_ERR;
    }
    auto interopClasspath = EtsExports::getInstance()->getClasspath("InteropNativeModule");
    auto interopClass = env->FindClass(interopClasspath.c_str());
    if (interopClass == nullptr) {
        LOGE("Can not find InteropNativeModule classpath to set callback dispatcher");
        return ETS_ERR;
    }
    if (!setKoalaEtsNapiCallbackDispatcher(env, interopClass, callCallbackFromNative, callCallbackFromNativeSig)) {
        LOGE("Failed to set koala ets callback dispatcher");
        return ETS_ERR;
    }
    return ETS_NAPI_VERSION_1_0;
}

EtsExports* EtsExports::getInstance() {
    static EtsExports *instance = nullptr;
    if (instance == nullptr) {
        instance = new EtsExports();
    }
    return instance;
}

std::vector<std::string> EtsExports::getModules() {
    std::vector<std::string> result;
    for (auto it = implementations.begin(); it != implementations.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

const std::vector<std::tuple<std::string, std::string, void*, int>>& EtsExports::getMethods(const std::string& module) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        LOGE("Module %s is not registered", module.c_str());
    }
    return it->second;
}

void EtsExports::addMethod(const char* module, const char *name, const char *type, void *impl, int flags) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        it = implementations.insert(std::make_pair(module, std::vector<std::tuple<std::string, std::string, void*, int>>())).first;
    }
    it->second.push_back(std::make_tuple(name, convertType(name, type), impl, flags));
}

void EtsExports::setClasspath(const char* module, const char *classpath) {
    auto it = classpaths.find(module);
    if (it == classpaths.end()) {
        classpaths.insert(std::make_pair(module, classpath));
    } else {
        LOGE("Classpath for module %s was redefined", module);
    }
}

static std::map<std::string, std::string> g_defaultClasspaths = {    
    {"InteropNativeModule", "@koalaui/interop/InteropNativeModule/InteropNativeModule"},
    // todo leave just InteropNativeModule, define others via KOALA_ETS_INTEROP_MODULE_CLASSPATH
    {"TestNativeModule", "@ohos/arkui/generated/arkts/TestNativeModule/TestNativeModule"},
    {"ArkUINativeModule", "@ohos/arkui/generated/arkts/ArkUINativeModule/ArkUINativeModule"},
    {"ArkUIGeneratedNativeModule", "@ohos/arkui/generated/arkts/ArkUIGeneratedNativeModule/ArkUIGeneratedNativeModule"},
};
const std::string& EtsExports::getClasspath(const std::string& module) {
    auto it = classpaths.find(module);
    if (it != classpaths.end()) {
        return it->second;
    }
    auto defaultClasspath = g_defaultClasspaths.find(module);
    if (defaultClasspath != g_defaultClasspaths.end()) {
        return defaultClasspath->second;
    }
    INTEROP_FATAL("Classpath for module %s was not registered", module.c_str());
}
