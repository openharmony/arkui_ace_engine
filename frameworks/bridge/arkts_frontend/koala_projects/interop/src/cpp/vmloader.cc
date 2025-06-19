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

#include <cstring>
#include <vector>
#include <algorithm>

#include "interop-logging.h"
#include "dynamic-loader.h"
#include "koala-types.h"

// DO NOT USE KOALA INTEROP MECHANISMS IN THIS FILE!

#ifdef KOALA_JNI
#include "jni.h"
#endif

#ifdef KOALA_ETS_NAPI
#include "etsapi.h"
#endif

#ifdef KOALA_ANI
#include "ani.h"
#endif

#if defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_OHOS)
#include "sys/stat.h"
#include "dirent.h"
#endif

#define OHOS_USER_LIBS "/data/storage/el1/bundle/libs"
#ifdef KOALA_OHOS_ARM32
#define USE_SYSTEM_ARKVM 1
#elif KOALA_OHOS_ARM64
#define USE_SYSTEM_ARKVM 1
#else
#define USE_SYSTEM_ARKVM 0
#endif

#if USE_SYSTEM_ARKVM
#define SYSTEM_ARK_STDLIB_PATH "/system/etc/etsstdlib.abc"
#endif

#ifndef KOALA_USE_PANDA_VM
#ifdef KOALA_ANI
#define KOALA_USE_PANDA_VM 1
#endif
#ifdef KOALA_ETS_NAPI
#define KOALA_USE_PANDA_VM 1
#endif
#endif

void traverseDir(std::string root, std::vector<std::string>& paths, int depth = 0);

struct VMLibInfo {
    const char* sdkPath;
    const char* platform;
    const char* lib;
    const char* createVM;
};

#ifdef KOALA_JNI
const VMLibInfo javaVMLib = {
    getenv("JAVA_HOME"),
    #if defined(KOALA_LINUX) || defined(KOALA_MACOS)
    "lib/server"
    #elif KOALA_WINDOWS
    "bin/server"
    #else
    #error "Unknown platform"
    #endif
    ,
    "jvm",
    "JNI_CreateJavaVM",
};
#endif

#ifdef KOALA_ETS_NAPI
const VMLibInfo pandaVMLib = {
    // sdkPath
    #if defined(KOALA_OHOS)
        #ifdef KOALA_OHOS_ARM32
            "/system/lib"
        #elif KOALA_OHOS_ARM64
            "/system/lib64"
        #else
            OHOS_USER_LIBS
        #endif
    #else
        getenv("PANDA_HOME")
    #endif
    ,

    // platform
    #ifdef KOALA_LINUX
        #ifdef KOALA_LINUX_ARM64
            "linux_arm64_host_tools/lib"
        #else
            "linux_host_tools/lib"
        #endif
    #elif KOALA_MACOS
        "macos_host_tools/lib"
    #elif KOALA_WINDOWS
        "_host_tools/lib"
    #elif KOALA_OHOS_ARM64
        "arm64"
    #elif KOALA_OHOS_ARM32
        "arm"
    #else
        #error "Unknown platform"
    #endif
    ,

    // lib
    "arkruntime"
    ,

    // createVM
    "ETS_CreateVM"
};
#endif

struct VMInitArgs {
    int version;
    int nOptions;
    void* options;
};

#define JAVA_VM_KIND 1
#define PANDA_VM_KIND 2
#define ES2PANDA_KIND 3
#define PANDA_ANI_VM_KIND 4

struct ForeignVMContext {
    void* currentVMContext;
    int32_t (*callSync)(void* vmContext, int32_t callback, int8_t* data, int32_t length);
};

struct VMEntry {
    int vmKind;
    void* env;
    void* app;
    void* enter;
    void* emitEvent;
    void* restartWith;
    ForeignVMContext foreignVMContext;
};

VMEntry g_vmEntry = {};

typedef int (*createVM_t)(void** pVM, void** pEnv, void* vmInitArgs);
typedef int (*getVMs_t)(void** pVM, int32_t bufLen, int32_t* nVMs);

#ifdef KOALA_WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

int loadES2Panda(const char* appClassPath, const char* appLibPath) {
    fprintf(stderr, "native: es2panda %s\n", appClassPath);
    return 0;
}

#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
namespace {

enum PandaLog2MobileLog : int {
    UNKNOWN = 0,
    DEFAULT,
    VERBOSE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    SILENT,
};

int ArkMobileLog(int id, int level, const char *component, const char *fmt, const char *msg) {
    switch (level) {
        case PandaLog2MobileLog::DEFAULT:
        case PandaLog2MobileLog::VERBOSE:
        case PandaLog2MobileLog::DEBUG:
        case PandaLog2MobileLog::INFO:
        case PandaLog2MobileLog::SILENT:
            LOGI("ArkRuntime [%" LOG_PUBLIC "s]: %" LOG_PUBLIC "s", component, msg);
            break;
        case PandaLog2MobileLog::UNKNOWN:
        case PandaLog2MobileLog::WARN:
        case PandaLog2MobileLog::ERROR:
        case PandaLog2MobileLog::FATAL:
        default:
            LOGE("ArkRuntime [%" LOG_PUBLIC "s]: %" LOG_PUBLIC "s", component, msg);
            break;
    }
    return 0;
}

}
#endif

extern "C" DLL_EXPORT KInt LoadVirtualMachine(KInt vmKind, const char* appClassPath, const char* appLibPath, const ForeignVMContext* foreignVMContext) {
    if (vmKind == ES2PANDA_KIND) {
        return loadES2Panda(appClassPath, appLibPath);
    }

    const VMLibInfo* thisVM =
        #ifdef KOALA_JNI
        (vmKind == JAVA_VM_KIND) ? &javaVMLib :
        #endif
        #if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
        (vmKind == PANDA_VM_KIND || vmKind == PANDA_ANI_VM_KIND) ? &pandaVMLib :
        #endif
        nullptr;

    if (!thisVM) {
        LOGE("Unknown VM kind: %" LOG_PUBLIC "d\n (possibly %" LOG_PUBLIC "s is compiled without expected flags)", vmKind, __FILE__);
        return -1;
    }

    LOGI("Starting VM %" LOG_PUBLIC "d with classpath=%" LOG_PUBLIC "s native=%" LOG_PUBLIC "s", vmKind, appClassPath, appLibPath);

    std::string libPath =
#if USE_SYSTEM_ARKVM
        std::string(thisVM->sdkPath) + "/" + libName(thisVM->lib)
#elif defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_WINDOWS)
        std::string(thisVM->sdkPath) + "/" + std::string(thisVM->platform) + "/" + libName(thisVM->lib)
#elif defined(KOALA_OHOS)
        std::string(OHOS_USER_LIBS) + "/" + libName(thisVM->lib)
#else
        #error "Library path not specified for this platform"
#endif
        ;
    void *handle = loadLibrary(libPath);
    if (!handle) {
        LOGE("Cannot load library %" LOG_PUBLIC "s: %" LOG_PUBLIC "s\n", libPath.c_str(), libraryError());
        return -1;
    }

    createVM_t createVM = (createVM_t)findSymbol(handle, thisVM->createVM);
    getVMs_t getVMs = (getVMs_t)findSymbol(handle, "ETS_GetCreatedVMs");

    if (!createVM) {
        LOGE("Cannot find %" LOG_PUBLIC "s\n", thisVM->createVM);
        return -1;
    }

    void* vm = nullptr;
    void* env = nullptr;
    int32_t nVMs = 0;
    int result = 0;

#ifdef KOALA_JNI
    if (vmKind == JAVA_VM_KIND) {
        JavaVMInitArgs javaVMArgs;
        javaVMArgs.version = JNI_VERSION_10;
        javaVMArgs.ignoreUnrecognized = false;
        std::vector<JavaVMOption> javaVMOptions;
        javaVMOptions = {
            {(char*)strdup((std::string("-Djava.class.path=") + appClassPath).c_str())},
            {(char*)strdup((std::string("-Djava.library.path=") + appLibPath).c_str())},
        };
        javaVMArgs.nOptions = javaVMOptions.size();
        javaVMArgs.options = javaVMOptions.data();
        g_vmEntry.vmKind = JAVA_VM_KIND;
        result = createVM(&vm, &env, &javaVMArgs);
    }
#endif

// For now we use ETS API for VM startup and entry.
#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
    if (vmKind == PANDA_VM_KIND || vmKind == PANDA_ANI_VM_KIND) {
        EtsVMInitArgs pandaVMArgs;
        pandaVMArgs.version = ETS_NAPI_VERSION_1_0;
        std::vector<EtsVMOption> etsVMOptions;
        std::vector<std::string> files;
        traverseDir(std::string(appClassPath), files);
        std::sort(files.begin(), files.end());
        etsVMOptions = {
#if USE_SYSTEM_ARKVM
            {EtsOptionType::ETS_BOOT_FILE, SYSTEM_ARK_STDLIB_PATH},
#elif defined(KOALA_OHOS)
            {EtsOptionType::ETS_BOOT_FILE, (std::string(OHOS_USER_LIBS) + "/" + "etsstdlib.abc").c_str() },

#elif defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_WINDOWS)
            {EtsOptionType::ETS_BOOT_FILE, (char*)strdup((std::string(thisVM->sdkPath) + "/ets/etsstdlib.abc").c_str())},
#endif
        };
        std::string all_files;
        for (const std::string& path : files) {
            etsVMOptions.push_back({EtsOptionType::ETS_BOOT_FILE, (char*)strdup(path.c_str())});
            if (all_files.size() > 0) all_files.append(":");
            all_files.append(path);
        }
        LOGE("classpath \"%s\" from %s", all_files.c_str(), appClassPath);
        etsVMOptions.push_back({EtsOptionType::ETS_GC_TRIGGER_TYPE, "heap-trigger"});
        etsVMOptions.push_back({EtsOptionType::ETS_NATIVE_LIBRARY_PATH, (char*)strdup(std::string(appLibPath).c_str())});
        etsVMOptions.push_back({EtsOptionType::ETS_VERIFICATION_MODE, "on-the-fly"});
        etsVMOptions.push_back({EtsOptionType::ETS_NO_JIT, nullptr});
        etsVMOptions.push_back({EtsOptionType::ETS_MOBILE_LOG, (void*)ArkMobileLog});
        etsVMOptions.push_back({EtsOptionType::ETS_AOT, nullptr});
        // etsVMOptions.push_back({EtsOptionType::ETS_LOG_LEVEL, "info"});
        pandaVMArgs.nOptions = etsVMOptions.size();
        pandaVMArgs.options = etsVMOptions.data();
        g_vmEntry.vmKind = vmKind;

        result = getVMs ? getVMs(&vm, 1, &nVMs) : 0;
        if (nVMs != 0) {
            __EtsVM* vmInstance = (__EtsVM*)vm;
            EtsEnv* pEnv = nullptr;
            vmInstance->GetEnv(&pEnv, ETS_NAPI_VERSION_1_0);
            env = static_cast<void*>(pEnv);

        } else {
            result = createVM(&vm, &env, &pandaVMArgs);
        }
    }
#endif

    if (result != 0) {
        LOGE("Error creating a VM of kind %" LOG_PUBLIC "d: %" LOG_PUBLIC "d\n", vmKind, result);
        return result;
    }
    g_vmEntry.env = env;
    g_vmEntry.foreignVMContext = *foreignVMContext;
    return 0;
}

struct AppInfo {
    const char* className;
    const char* createMethodName;
    const char* createMethodSig;
    const char* startMethodName;
    const char* startMethodSig;
    const char* enterMethodName;
    const char* enterMethodSig;
    const char* emitEventMethodName;
    const char* emitEventMethodSig;
    const char* restartWithMethodName;
    const char* restartWithMethodSig;
};

#ifdef KOALA_JNI
const AppInfo javaAppInfo = {
    "org/koalaui/arkoala/Application",
    "createApplication",
    "(Ljava/lang/String;Ljava/lang/String;)Lorg/koalaui/arkoala/Application;",
    "start",
    "()J",
    "enter",
    "(IIJ)Z",
    "emitEvent",
    "(IIII)Ljava/lang/String;",
};
#endif

#ifdef KOALA_USE_PANDA_VM
const AppInfo pandaAppInfo = {
    "@koalaui/arkts-arkui/Application/Application",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZI:L@koalaui/arkts-arkui/Application/Application;",
    "start",
    "J:J",
    "enter",
    "IIJ:Z",
    "emitEvent",
    "IIII:Lstd/core/String;",
};
const AppInfo harnessAppInfo = {
    "@koalaui/ets-harness/src/EtsHarnessApplication/EtsHarnessApplication",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZI:L@koalaui/ets-harness/src/EtsHarnessApplication/EtsHarnessApplication;",
    "start",
    "J:J",
    "enter",
    "IIJ:Z",
    "emitEvent",
    "IIII:Lstd/core/String;",
    "restartWith",
    "Lstd/core/String;:V"
};
#endif

extern "C" DLL_EXPORT KNativePointer StartApplication(const char* appUrl, const char* appParams) {
    const auto isTestEnv = std::string(appUrl) == "EtsHarness";
    const AppInfo* appInfo =
        #ifdef KOALA_JNI
        (g_vmEntry.vmKind == JAVA_VM_KIND) ? &javaAppInfo :
        #endif
        #if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
        (g_vmEntry.vmKind == PANDA_VM_KIND || g_vmEntry.vmKind == PANDA_ANI_VM_KIND) ? isTestEnv ? &harnessAppInfo : &pandaAppInfo :
        #endif
        nullptr;

    if (!appInfo) {
        LOGE("No appInfo provided for VM kind %" LOG_PUBLIC "d (recompile vmloader.cc with the missing flags)\n", g_vmEntry.vmKind);
        return nullptr;
    }

    LOGI("Starting application %" LOG_PUBLIC "s with params %" LOG_PUBLIC "s", appUrl, appParams);
#ifdef KOALA_JNI
    if (g_vmEntry.vmKind == JAVA_VM_KIND) {
        JNIEnv* jEnv = (JNIEnv*)(g_vmEntry.env);
        jclass appClass = jEnv->FindClass(appInfo->className);
        if (!appClass) {
            LOGE("Cannot load main class %s\n", appInfo->className);
            return nullptr;
        }
        jmethodID create = jEnv->GetStaticMethodID(appClass, appInfo->createMethodName, appInfo->createMethodSig);
        if (!create) {
            LOGE("Cannot find create method %s\n", appInfo->createMethodName);
            return nullptr;
        }
        auto app = jEnv->NewGlobalRef(jEnv->CallStaticObjectMethod(appClass, create, jEnv->NewStringUTF(appUrl), jEnv->NewStringUTF(appParams)));
        g_vmEntry.app = app;
        auto start = jEnv->GetMethodID(appClass, appInfo->startMethodName, appInfo->startMethodSig);
        if (!start) {
            LOGE("Cannot find start method \"%s %s\"\n", appInfo->startMethodName, appInfo->startMethodSig);
            return nullptr;
        }
        g_vmEntry.enter = (void*)(jEnv->GetMethodID(appClass, appInfo->enterMethodName, appInfo->enterMethodSig));
        if (!g_vmEntry.enter) {
            LOGE("Cannot find enter method %s\n", appInfo->enterMethodName);
            return nullptr;
        }
        g_vmEntry.emitEvent = (void*)(jEnv->GetMethodID(appClass, appInfo->emitEventMethodName, appInfo->emitEventMethodSig));
        if (!g_vmEntry.emitEvent) {
            LOGE("Cannot find emitEvent method %s\n", appInfo->emitEventMethodName);
            return nullptr;
        }
        return reinterpret_cast<KNativePointer>(jEnv->CallLongMethod(
            app, start));
    }
#endif
#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND || g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        EtsEnv* etsEnv = (EtsEnv*)g_vmEntry.env;
        ets_class appClass = etsEnv->FindClass(appInfo->className);
        if (!appClass) {
            LOGE("Cannot load main class %" LOG_PUBLIC "s\n", appInfo->className);
            if (etsEnv->ErrorCheck()) {
                etsEnv->ErrorDescribe();
                etsEnv->ErrorClear();
            }
            return nullptr;
        }
        ets_method create = etsEnv->GetStaticp_method(appClass, appInfo->createMethodName, appInfo->createMethodSig);
        if (!create) {
            LOGE("Cannot find create method %" LOG_PUBLIC "s\n", appInfo->createMethodName);
            if (etsEnv->ErrorCheck()) {
                etsEnv->ErrorDescribe();
                etsEnv->ErrorClear();
            }
            return nullptr;
        }
#if defined (KOALA_OHOS_ARM64)
        auto useNativeLog = true;
#else
        auto useNativeLog = false;
#endif
        auto app = etsEnv->NewGlobalRef(etsEnv->CallStaticObjectMethod(
            appClass, create,
            etsEnv->NewStringUTF(appUrl), etsEnv->NewStringUTF(appParams),
            useNativeLog,
            g_vmEntry.vmKind
            ));
        if (!app) {
            LOGE("createApplication returned null");
            if (etsEnv->ErrorCheck()) {
                etsEnv->ErrorDescribe();
                etsEnv->ErrorClear();
                return nullptr;
            }
            return nullptr;
        }
        g_vmEntry.app = (void*)app;
        auto start = etsEnv->Getp_method(appClass, appInfo->startMethodName, appInfo->startMethodSig);
        g_vmEntry.enter = (void*)(etsEnv->Getp_method(appClass, appInfo->enterMethodName, nullptr /*appInfo->enterMethodSig */));
        if (!g_vmEntry.enter) {
            LOGE("Cannot find enter method %" LOG_PUBLIC "s", appInfo->enterMethodName);
            if (etsEnv->ErrorCheck()) {
                etsEnv->ErrorDescribe();
                etsEnv->ErrorClear();
            }
            return nullptr;
        }
        if (etsEnv->ErrorCheck()) {
            etsEnv->ErrorDescribe();
            etsEnv->ErrorClear();
            return nullptr;
        }
        g_vmEntry.emitEvent = (void*)(etsEnv->Getp_method(appClass, appInfo->emitEventMethodName, appInfo->emitEventMethodSig));
        if (!g_vmEntry.emitEvent) {
            LOGE("Cannot find enter emitEvent %" LOG_PUBLIC "s", appInfo->emitEventMethodSig);
            if (etsEnv->ErrorCheck()) {
                etsEnv->ErrorDescribe();
                etsEnv->ErrorClear();
            }
            return nullptr;
        }
        if (isTestEnv) {
            g_vmEntry.restartWith = (void*)(etsEnv->Getp_method(appClass, appInfo->restartWithMethodName, appInfo->restartWithMethodSig));
            if (!g_vmEntry.restartWith) {
                LOGE("Cannot find enter restartWith %" LOG_PUBLIC "s", appInfo->restartWithMethodSig);
                if (etsEnv->ErrorCheck()) {
                    etsEnv->ErrorDescribe();
                    etsEnv->ErrorClear();
                }
                return nullptr;
            }
        }
        // TODO: pass app entry point!
        return reinterpret_cast<KNativePointer>(etsEnv->CallLongMethod((ets_object)(app), start, &g_vmEntry.foreignVMContext));
    }
#endif
    return nullptr;
}

extern "C" DLL_EXPORT KBoolean RunApplication(const KInt arg0, const KInt arg1) {
#ifdef KOALA_JNI
    if (g_vmEntry.vmKind == JAVA_VM_KIND) {
        JNIEnv* jEnv = (JNIEnv*)(g_vmEntry.env);
        auto result = jEnv->CallBooleanMethod(
            (jobject)(g_vmEntry.app),
            (jmethodID)(g_vmEntry.enter),
            (jint)arg0,
            (jint)arg1,
            (int64_t)(intptr_t)(&g_vmEntry.foreignVMContext)
        );
        if (jEnv->ExceptionCheck()) {
            jEnv->ExceptionDescribe();
            jEnv->ExceptionClear();
        }
        return result;
    }
#endif
#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND || g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        EtsEnv* etsEnv = (EtsEnv*)(g_vmEntry.env);
        if (!g_vmEntry.enter) {
            LOGE("Cannot find enter method");
            return -1;
        }
        auto result = etsEnv->CallBooleanMethod(
            (ets_object)(g_vmEntry.app),
            (ets_method)(g_vmEntry.enter),
            (ets_int)arg0,
            (ets_int)arg1,
            (int64_t)(intptr_t)(&g_vmEntry.foreignVMContext)
        );
        if (etsEnv->ErrorCheck()) {
            LOGE("Calling enter() method gave an error");
            etsEnv->ErrorDescribe();
            etsEnv->ErrorClear();
        }
        return result;
    }
#endif

    return 1;
}

extern "C" DLL_EXPORT const char* EmitEvent(const KInt type, const KInt target, const KInt arg0, const KInt arg1) {
#ifdef KOALA_JNI
    if (g_vmEntry.vmKind == JAVA_VM_KIND) {
        JNIEnv* jEnv = (JNIEnv*)(g_vmEntry.env);
        if (!g_vmEntry.emitEvent) {
            LOGE("Cannot find emitEvent method");
            return "-1";
        }
        auto rv = (jstring)jEnv->CallObjectMethod(
            (jobject)(g_vmEntry.app),
            (jmethodID)(g_vmEntry.emitEvent),
            (jint)type,
            (jint)target,
            (jint)arg0,
            (jint)arg1
        );
        if (jEnv->ExceptionCheck()) {
            jEnv->ExceptionDescribe();
            jEnv->ExceptionClear();
        }
        const char *result = jEnv->GetStringUTFChars(rv, 0);
        return result;
    }
#endif

#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND || g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        EtsEnv* etsEnv = (EtsEnv*)(g_vmEntry.env);
        if (!g_vmEntry.emitEvent) {
            LOGE("Cannot find emitEvent method");
            return "-1";
        }
        auto rv = (ets_string)etsEnv->CallObjectMethod(
            (ets_object)(g_vmEntry.app),
            (ets_method)(g_vmEntry.emitEvent),
            (ets_int)type,
            (ets_int)target,
            (ets_int)arg0,
            (ets_int)arg1
        );
        if (etsEnv->ErrorCheck()) {
            LOGE("Calling emitEvent() method gave an error");
            etsEnv->ErrorDescribe();
            etsEnv->ErrorClear();
        }
        const char *result = etsEnv->GetStringUTFChars(rv, 0);
        return result;
    }
#endif
    return "-1";
}

extern "C" DLL_EXPORT void RestartWith(const char* page) {
#ifdef KOALA_JNI
    if (g_vmEntry.vmKind == JAVA_VM_KIND) {
        JNIEnv* jEnv = (JNIEnv*)(g_vmEntry.env);
        if (!g_vmEntry.restartWith) {
            LOGE("Cannot find restartWith method");
            return;
        }
        jEnv->CallVoidMethod(
            (jobject)(g_vmEntry.app),
            (jmethodID)(g_vmEntry.restartWith),
            jEnv->NewStringUTF(page)
        );
        if (jEnv->ExceptionCheck()) {
            jEnv->ExceptionDescribe();
            jEnv->ExceptionClear();
        }
    }
#endif
#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND) {
        EtsEnv* etsEnv = (EtsEnv*)(g_vmEntry.env);
        if (!g_vmEntry.restartWith) {
            LOGE("Cannot find restartWith method");
            return;
        }
        etsEnv->CallVoidMethod(
            (ets_object)(g_vmEntry.app),
            (ets_method)(g_vmEntry.restartWith),
            etsEnv->NewStringUTF(page)
        );
        if (etsEnv->ErrorCheck()) {
            LOGE("Calling restartWith() method gave an error");
            etsEnv->ErrorDescribe();
            etsEnv->ErrorClear();
        }
    }
#endif
}

void traverseDir(std::string root, std::vector<std::string>& paths, int depth) {
    if (depth >= 50) {
        return;
    }
#if defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_OHOS)
    std::string suffix = ".abc";
    #if defined(KOALA_OHOS)
    suffix += ".so";
    #endif
    DIR* directory = opendir(root.c_str());
    if (!directory) {
        LOGE("Cannot open dir %" LOG_PUBLIC "s\n", root.c_str());
        return;
    }
    struct dirent* ent = NULL;
    struct stat statbuf;

    LOGI("Searching for *%" LOG_PUBLIC "s in %" LOG_PUBLIC "s\n", suffix.c_str(), root.c_str());
    while ((ent = readdir(directory)) != nullptr) {
        std::string filename = std::string(ent->d_name);
        if (filename == "." || filename == "..") {
            continue;
        }
        std::string filepath = root + "/" + filename;
        int rv = stat(filepath.c_str(), &statbuf);
        if (rv < 0) continue;
        if (filepath.size() >= suffix.size() && filepath.substr(filepath.size() - suffix.size()) == suffix && (statbuf.st_mode & S_IFMT) == S_IFREG) {
            paths.push_back(filepath);
        }
        if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
            traverseDir(filepath, paths, depth + 1);
        }
    }
    closedir(directory);
#endif
}
