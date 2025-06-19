/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


#define KOALA_INTEROP_MODULE
#include "convertors-jni.h"
#include "signatures.h"
#include "interop-logging.h"
#include "interop-types.h"

static const char* nativeModule = "org/koalaui/arkoala/InteropNativeModule";
static const char* nativeModulePrefix = "org/koalaui/arkoala/";
static const char* callCallbackFromNative = "callCallbackFromNative";
static const char* callCallbackFromNativeSig = "(I[BI)I";

const bool registerByOne = true;

static bool registerNatives(JNIEnv *env, jclass clazz, const std::vector<std::tuple<std::string, std::string, void* >> impls) {
    size_t numMethods = impls.size();
    JNINativeMethod *methods = new JNINativeMethod[numMethods];
    bool result = true;
    for (size_t i = 0; i < numMethods; i++)
    {
        methods[i].name = (char *)std::get<0>(impls[i]).c_str();
        methods[i].signature = (char *)std::get<1>(impls[i]).c_str();
        methods[i].fnPtr = std::get<2>(impls[i]);
        if (registerByOne) {
            result &= (env->RegisterNatives(clazz, methods + i, 1) >= 0);
            if (env->ExceptionCheck()) {
                env->ExceptionDescribe();
                env->ExceptionClear();
                result = false;
            }
        }
    }
    return registerByOne ? true : env->RegisterNatives(clazz, methods, numMethods) >= 0;
}

constexpr bool splitPerModule = true;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_8) != JNI_OK) {
        return JNI_ERR;
    }
    auto modules = JniExports::getInstance()->getModules();
    jclass defaultNativeModule = env->FindClass(nativeModule);
    for (auto it = modules.begin(); it != modules.end(); ++it) {
        std::string className = std::string(nativeModulePrefix) + *it;
        jclass nativeModule =
            (!splitPerModule) ? defaultNativeModule : env->FindClass(className.c_str());
        if (nativeModule == nullptr) {
            LOGE("Cannot find managed class %s", className.c_str());
            continue;
        }
        registerNatives(env, nativeModule, JniExports::getInstance()->getMethods(*it));
    }
    if (!setKoalaJniCallbackDispatcher(env, defaultNativeModule, callCallbackFromNative, callCallbackFromNativeSig)) return JNI_ERR;
    return JNI_VERSION_1_8;
}

JniExports *JniExports::getInstance()
{
    static JniExports *instance = nullptr;
    if (instance == nullptr)
    {
        instance = new JniExports();
    }
    return instance;
}

std::vector<std::string> JniExports::getModules() {
    std::vector<std::string> result;
    for (auto it = implementations.begin(); it != implementations.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

const std::vector<std::tuple<std::string, std::string, void*>>& JniExports::getMethods(const std::string& module) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        LOGE("Module %s is not registered", module.c_str());
        INTEROP_FATAL("Fatal error: not registered module %s", module.c_str());
    }
    return it->second;
}

void JniExports::addMethod(const char* module, const char *name, const char *type, void *impl) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        it = implementations.insert(std::make_pair(module, std::vector<std::tuple<std::string, std::string, void*>>())).first;
    }
    it->second.push_back(std::make_tuple(name, convertType(name, type), impl));
}
