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
#include "convertors-ani.h"
#include "signatures.h"
#include "interop-logging.h"
#include "interop-types.h"

static const char* callCallbackFromNative = "callCallbackFromNative";
static const char* callCallbackFromNativeSig = "I[BI:I";

static const char* FAST_NATIVE_PREFIX = "#F$";

const bool registerByOne = true;

static bool registerNatives(ani_env *env, const ani_class clazz, const std::vector<std::tuple<std::string, std::string, void*, int>> impls) {
    std::vector<ani_native_function> methods;
    methods.reserve(impls.size());
    bool result = true;
    for (const auto &[name, type, func, flag] : impls) {
        ani_native_function method;
        method.name = name.c_str();
        method.pointer = func;
        method.signature = (flag & ANI_SLOW_NATIVE_FLAG) == 0 ? FAST_NATIVE_PREFIX : nullptr;
        if (registerByOne) {
            result &= env->Class_BindNativeMethods(clazz, &method, 1) == ANI_OK;
            ani_boolean isError = false;
            env->ExistUnhandledError(&isError);
            if (isError) {
                //env->ErrorDescribe();
                env->ResetError();
            }
        }
        else {
            methods.push_back(method);
        }
    }
    if (!registerByOne) {
        result = env->Class_BindNativeMethods(clazz, methods.data(), static_cast<ani_size>(methods.size())) == ANI_OK;
    }
    return registerByOne ? true : result;
}

bool registerAllModules(ani_env *env) {
    auto moduleNames = AniExports::getInstance()->getModules();

    for (auto it = moduleNames.begin(); it != moduleNames.end(); ++it) {
        std::string classpath = AniExports::getInstance()->getClasspath(*it);
        ani_class nativeModule = nullptr;
        env->FindClass(classpath.c_str(), &nativeModule);
        if (nativeModule == nullptr) {
            LOGE("Cannot find managed class %s", classpath.c_str());
            continue;
        }
        if (!registerNatives(env, nativeModule, AniExports::getInstance()->getMethods(*it))) {
            return false;
        }
    }

    return true;
}

#if 0
extern "C" ETS_EXPORT ets_int ETS_CALL EtsNapiOnLoad(ets_env *env) {
    if (!registerAllModules(env)) {
        LOGE("Failed to register ets modules");
        return ETS_ERR;
    }
    auto interopClasspath = AniExports::getInstance()->getClasspath("InteropNativeModule");
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
#endif

AniExports* AniExports::getInstance() {
    static AniExports *instance = nullptr;
    if (instance == nullptr) {
        instance = new AniExports();
    }
    return instance;
}

std::vector<std::string> AniExports::getModules() {
    std::vector<std::string> result;
    for (auto it = implementations.begin(); it != implementations.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

const std::vector<std::tuple<std::string, std::string, void*, int>>& AniExports::getMethods(const std::string& module) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        LOGE("Module %s is not registered", module.c_str());
    }
    return it->second;
}

void AniExports::addMethod(const char* module, const char *name, const char *type, void *impl, int flags) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        it = implementations.insert(std::make_pair(module, std::vector<std::tuple<std::string, std::string, void*, int>>())).first;
    }
    it->second.push_back(std::make_tuple(name, convertType(name, type), impl, flags));
}

void AniExports::setClasspath(const char* module, const char *classpath) {
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
    {"TestNativeModule", "@koalaui/arkts-arkui/generated/arkts/TestNativeModule/TestNativeModule"},
    {"ArkUINativeModule", "@koalaui/arkts-arkui/generated/arkts/ArkUINativeModule/ArkUINativeModule"},
    {"ArkUIGeneratedNativeModule", "@koalaui/arkts-arkui/generated/arkts/ArkUIGeneratedNativeModule/ArkUIGeneratedNativeModule"},
};
const std::string& AniExports::getClasspath(const std::string& module) {
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
