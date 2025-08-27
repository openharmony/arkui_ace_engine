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
#include <string.h>

#include <map>
#include "convertors-ani.h"
#include "signatures.h"
#include "interop-logging.h"
#include "interop-types.h"

static const char* callCallbackFromNative = "callCallbackFromNative";
static const char* callCallbackFromNativeSig = "IJI:I";

const bool registerByOne = true;

static bool registerNatives(ani_env *env, const ani_class clazz, const std::vector<std::tuple<std::string, std::string, void*, int>> impls) {
    std::vector<ani_native_function> methods;
    methods.reserve(impls.size());
    bool result = true;
    for (const auto &[name, type, func, flag] : impls) {
        ani_native_function method;
        method.name = name.c_str();
        method.pointer = func;
        method.signature = nullptr;
        if (registerByOne) {
            result &= env->Class_BindNativeMethods(clazz, &method, 1) == ANI_OK;
            ani_boolean isError = false;
            env->ExistUnhandledError(&isError);
            if (isError) {
                env->DescribeError();
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

bool registerAllModules(ani_env *aniEnv) {
    auto moduleNames = AniExports::getInstance()->getModules();
    for (auto it = moduleNames.begin(); it != moduleNames.end(); ++it) {
        std::string classpath = AniExports::getInstance()->getClasspath(*it);
        ani_class nativeModule = nullptr;
        aniEnv->FindClass(classpath.c_str(), &nativeModule);
        if (nativeModule == nullptr) {
            LOGE("Cannot find managed class %s", classpath.c_str());
            continue;
        }
        if (!registerNatives(aniEnv, nativeModule, AniExports::getInstance()->getMethods(*it))) {
            return false;
        }
    }
    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result) {
    LOGE("Use ANI")
    ani_env* aniEnv = nullptr;
    *result = 1;
    vm->GetEnv(/* version */ 1, (ani_env**)&aniEnv);
    if (!registerAllModules(aniEnv)) {
        LOGE("Failed to register ANI modules");
        return ANI_ERROR;
    }
    ani_boolean hasError = false;
    aniEnv->ExistUnhandledError(&hasError);
    if (hasError) {
        aniEnv->DescribeError();
        aniEnv->ResetError();
    }
    auto interopClassName = AniExports::getInstance()->getClasspath("InteropNativeModule");
    ani_class interopClass = nullptr;
    aniEnv->FindClass(interopClassName.c_str(), &interopClass);
    if (interopClass == nullptr) {
        LOGE("Can not find InteropNativeModule class to set callback dispatcher");
        aniEnv->ExistUnhandledError(&hasError);
        if (hasError) {
            aniEnv->DescribeError();
            aniEnv->ResetError();
        }
        return ANI_OK;
    }
    if (!setKoalaANICallbackDispatcher(aniEnv, interopClass, callCallbackFromNative, callCallbackFromNativeSig)) {
        LOGE("Failed to set ANI callback dispatcher");
        return ANI_ERROR;
    }
    return ANI_OK;
}

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
    {"InteropNativeModule", "L@koalaui/interop/InteropNativeModule/InteropNativeModule;"},
    // todo leave just InteropNativeModule, define others via KOALA_ETS_INTEROP_MODULE_CLASSPATH
    {"TestNativeModule", "arkui/component/arkts/TestNativeModule/TestNativeModule"},
    {"ArkUINativeModule", "arkui/component/arkts/ArkUINativeModule/ArkUINativeModule"},
    {"ArkUIGeneratedNativeModule", "arkui/component/arkts/ArkUIGeneratedNativeModule/ArkUIGeneratedNativeModule"},
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

static struct {
    ani_class clazz = nullptr;
    ani_static_method method = nullptr;
} g_koalaANICallbackDispatcher;

bool setKoalaANICallbackDispatcher(
    ani_env* aniEnv,
    ani_class clazz,
    const char* dispatcherMethodName,
    const char* dispatcherMethodSig
) {
    g_koalaANICallbackDispatcher.clazz = clazz;
    aniEnv->Class_FindStaticMethod(
        clazz, dispatcherMethodName, dispatcherMethodSig,
        &g_koalaANICallbackDispatcher.method
    );
    if (g_koalaANICallbackDispatcher.method == nullptr) {
        return false;
    }
    return true;
}

void getKoalaANICallbackDispatcher(ani_class* clazz, ani_static_method* method) {
    *clazz = g_koalaANICallbackDispatcher.clazz;
    *method = g_koalaANICallbackDispatcher.method;
}
