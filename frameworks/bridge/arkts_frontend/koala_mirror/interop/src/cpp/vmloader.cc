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

#include <algorithm>
#include <cstring>
#include <sstream>
#include <vector>
#include <filesystem>

#include "interop-logging.h"
#include "dynamic-loader.h"
#include "koala-types.h"
#include "interop-utils.h"

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

#ifdef KOALA_KOTLIN
#include "kotlin_koala_api.h"
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

void traverseDir(const std::string& root, std::vector<std::string>& paths, std::string suffix, const std::vector<std::string>& fallbackPaths = {});

struct VMLibInfo {
    const char* sdkPath;
    const char* platform;
    const char* lib;
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
    "jvm"
};
#endif

#if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
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
};
#endif

#ifdef KOALA_KOTLIN
const VMLibInfo kotlinLib = {
    .sdkPath = nullptr,
    .platform = nullptr,
    .lib = "kotlin_koala",
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
#define KOTLIN_KIND 5

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
    void* loadView;
    ForeignVMContext foreignVMContext;
    std::string userFilesAbcPaths;
};

VMEntry g_vmEntry = {};

typedef int (*createVM_t)(void** pVM, void** pEnv, void* vmInitArgs);

#ifdef KOALA_WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

int loadES2Panda(const char* appClassPath, const char* appLibPath) {
    fprintf(stderr, "native: es2panda %s\n", appClassPath);
    return 0;
}

#ifdef KOALA_ETS_NAPI
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

int ArkMobileLog(int id, int level, const char *component, const char *fmt, const char *msg)
{
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

#ifdef KOALA_ANI

static void AniMobileLog([[maybe_unused]] FILE *stream, int level,
                         const char *component, const char *msg)
{
    switch (level) {
    case ANI_LOGLEVEL_INFO:
    case ANI_LOGLEVEL_DEBUG:
        LOGI("ArkRuntime [%" LOG_PUBLIC "s]: %" LOG_PUBLIC "s", component, msg);
        break;
    case ANI_LOGLEVEL_FATAL:
    case ANI_LOGLEVEL_ERROR:
    case ANI_LOGLEVEL_WARNING:
    default:
        LOGE("ArkRuntime [%" LOG_PUBLIC "s]: %" LOG_PUBLIC "s", component, msg);
        break;
    }
}

static std::string makeClasspath(const std::vector<std::string>& files)
{
    std::stringstream stream;
    for (size_t index = 0, end = files.size(); index < end; ++index) {
        if (index > 0) {
            stream << ':';
        }
        stream << files[index];
    }
    return stream.str();
}

static std::pair<std::string, std::string> GetBootAndAppPandaFiles(const VMLibInfo* thisVM, const char* bootFilesPath, const char* userFilesPath)
{
    std::vector<std::string> bootFiles;
#if USE_SYSTEM_ARKVM
    bootFiles.push_back(SYSTEM_ARK_STDLIB_PATH);
#elif defined(KOALA_OHOS)
    bootFiles.push_back(std::string(OHOS_USER_LIBS) + "/etsstdlib.abc");
#elif defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_WINDOWS)
    bootFiles.push_back(std::string(thisVM->sdkPath) + "/ets/etsstdlib.abc");
#endif

#if defined(KOALA_OHOS)
    traverseDir("/system/framework", bootFiles, ".abc", {
        "etsstdlib_bootabc"
    });
#endif

    std::vector<std::string> userFiles;
    traverseDir(userFilesPath, userFiles, ".abc");
    std::sort(userFiles.begin(), userFiles.end());

    traverseDir(bootFilesPath, bootFiles, ".abc");
    std::sort(bootFiles.begin(), bootFiles.end());

    if (bootFiles.empty() || userFiles.empty())
        return {"",""};

    return { makeClasspath(bootFiles), makeClasspath(userFiles) };
}

static std::string GetAOTFiles(const char* appClassPath)
{
    std::vector<std::string> files;
    traverseDir(std::string(appClassPath), files, ".an");
    return makeClasspath(files);
}

static bool ResetErrorIfExists(ani_env *env)
{
    ani_boolean hasError = ANI_FALSE;
    env->ExistUnhandledError(&hasError);
    if (hasError == ANI_TRUE) {
        env->DescribeError();
        env->ResetError();
        return true;
    }
    return false;
}

#endif

std::string makeLibPath(const char *sdkPath, const char *platform, const char *lib) {
    std::string result;
    result.reserve(255);
    if (sdkPath) {
        result.append(sdkPath).append("/");
    }
    if (platform) {
        result.append(platform).append("/");
    }
    result.append(libName(lib));
    return result;
}

extern "C" DLL_EXPORT KInt LoadVirtualMachine(KInt vmKind, const char* bootFilesDir, const char* userFilesDir, const char* appLibPath, const ForeignVMContext* foreignVMContext)
{
    if (vmKind == ES2PANDA_KIND) {
        return loadES2Panda(bootFilesDir, appLibPath);
    }

    const VMLibInfo* thisVM =
        #ifdef KOALA_JNI
        (vmKind == JAVA_VM_KIND) ? &javaVMLib :
        #endif
        #if defined(KOALA_ETS_NAPI) || defined(KOALA_ANI)
        (vmKind == PANDA_VM_KIND || vmKind == PANDA_ANI_VM_KIND) ? &pandaVMLib :
        #endif
        #ifdef KOALA_KOTLIN
        (vmKind == KOTLIN_KIND) ? &kotlinLib :
        #endif
        nullptr;

    if (!thisVM) {
        LOGE("Unknown VM kind: %" LOG_PUBLIC "d\n (possibly %" LOG_PUBLIC "s is compiled without expected flags)", vmKind, __FILE__);
        return -1;
    }

    LOGI("Starting VM %" LOG_PUBLIC "d with bootFilesDir=%" LOG_PUBLIC "s bootFilesDir=%" LOG_PUBLIC "s native=%" LOG_PUBLIC "s", vmKind, bootFilesDir, userFilesDir, appLibPath);

    std::string libPath =
#if USE_SYSTEM_ARKVM
        std::string(thisVM->sdkPath) + "/" + libName(thisVM->lib)
#elif defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_WINDOWS)
        makeLibPath(thisVM->sdkPath, thisVM->platform, thisVM->lib)
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

    void* vm = nullptr;
    void* env = nullptr;
    int result = 0;

#ifdef KOALA_JNI
    if (vmKind == JAVA_VM_KIND) {
        typedef int (*createVM_t)(void** pVM, void** pEnv, void* vmInitArgs);
        createVM_t createVM = (createVM_t)findSymbol(handle, "JNI_CreateJavaVM");
        if (!createVM) {
            LOGE("Cannot find %" LOG_PUBLIC "s\n", "JNI_CreateJavaVM");
            return -1;
        }
        JavaVMInitArgs javaVMArgs;
        javaVMArgs.version = JNI_VERSION_10;
        javaVMArgs.ignoreUnrecognized = false;
        std::vector<JavaVMOption> javaVMOptions;
        javaVMOptions = {
            {(char*)strdup((std::string("-Djava.class.path=") + bootFilesDir).c_str())},
            {(char*)strdup((std::string("-Djava.library.path=") + appLibPath).c_str())},
        };
        javaVMArgs.nOptions = javaVMOptions.size();
        javaVMArgs.options = javaVMOptions.data();
        g_vmEntry.vmKind = JAVA_VM_KIND;
        result = createVM(&vm, &env, &javaVMArgs);
    }
#endif

#if defined(KOALA_ANI)
    if (vmKind == PANDA_ANI_VM_KIND) {
        g_vmEntry.vmKind = vmKind;

        uint32_t version = ANI_VERSION_1;
        size_t nVMs = 0;
        typedef int (*getVMs_t)(void** pVM, size_t bufLen, size_t* nVMs);
        typedef int (*createVM_t)(const void* args, uint32_t version, void** pVM);
        createVM_t createVM = (createVM_t)findSymbol(handle, "ANI_CreateVM");
        getVMs_t getVMs = (getVMs_t)findSymbol(handle, "ANI_GetCreatedVMs");
        result = getVMs ? getVMs(&vm, 1, &nVMs) : 0;
        if (nVMs == 0 && result == 0) {
            std::vector<ani_option> pandaVMOptions;

            auto [bootFiles, userFiles] = GetBootAndAppPandaFiles(thisVM, bootFilesDir, userFilesDir);
            LOGI("ANI: user abc-files \"%" LOG_PUBLIC "s\" from %" LOG_PUBLIC "s", userFiles.c_str(), userFilesDir);
            g_vmEntry.userFilesAbcPaths = std::move(userFiles);

            bootFiles = "--ext:--boot-panda-files=" + bootFiles;
            LOGI("ANI boot-panda-files option: \"%" LOG_PUBLIC "s\"", bootFiles.c_str());
            pandaVMOptions.push_back({bootFiles.c_str(), nullptr});

            auto aotFiles = GetAOTFiles(bootFilesDir);
            if (!aotFiles.empty()) {
                LOGI("ANI AOT files: \"%" LOG_PUBLIC "s\"", aotFiles.c_str());
                aotFiles = "--ext:--aot-files=" + aotFiles;
                pandaVMOptions.push_back({aotFiles.c_str(), nullptr});
            }

            pandaVMOptions.push_back({"--ext:--gc-trigger-type=heap-trigger", nullptr});
            std::string nativeLibraryPathOption =
                std::string("--ext:--native-library-path=") + appLibPath;
            pandaVMOptions.push_back({nativeLibraryPathOption.c_str(), nullptr});
            pandaVMOptions.push_back({"--ext:--verification-mode=on-the-fly", nullptr});
            pandaVMOptions.push_back({"--ext:--compiler-enable-jit=true", nullptr});
            pandaVMOptions.push_back({"--logger", reinterpret_cast<void *>(AniMobileLog)});
            pandaVMOptions.push_back({"--ext:--enable-an", nullptr});
            ani_options optionsPtr = {pandaVMOptions.size(), pandaVMOptions.data()};

            result = createVM(&optionsPtr, version, &vm);
        }

        if (result == 0) {
            ani_vm* vmInstance = (ani_vm*)vm;
            ani_env* pEnv = nullptr;
            result = vmInstance->GetEnv(version, &pEnv);
            env = static_cast<void*>(pEnv);
        }
    }
#endif /* KOALA_ANI */

// For now we use ETS API for VM startup and entry.
#if defined(KOALA_ETS_NAPI)
    if (vmKind == PANDA_VM_KIND) {
        EtsVMInitArgs pandaVMArgs;
        pandaVMArgs.version = ETS_NAPI_VERSION_1_0;
        std::vector<EtsVMOption> etsVMOptions;
        std::vector<std::string> files;
        traverseDir(std::string(bootFilesDir), files, ".abc");
        std::sort(files.begin(), files.end());
        std::vector<std::string> files_aot;
        traverseDir(std::string(bootFilesDir), files_aot, ".an");
        std::sort(files_aot.begin(), files_aot.end());
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
        LOGI("Using ETSNAPI: classpath \"%" LOG_PUBLIC "s\" from %" LOG_PUBLIC "s", all_files.c_str(), bootFilesDir);
        std::string all_files_aot;
        for (const std::string& path : files_aot) {
            etsVMOptions.push_back({EtsOptionType::ETS_AOT_FILE, (char*)strdup(path.c_str())});
            if (all_files_aot.size() > 0) all_files_aot.append(":");
            all_files_aot.append(path);
        }
        LOGI("ETSNAPI classpath (aot) \"%" LOG_PUBLIC "s\" from %" LOG_PUBLIC "s", all_files_aot.c_str(), bootFilesDir);
        etsVMOptions.push_back({EtsOptionType::ETS_GC_TRIGGER_TYPE, "heap-trigger"});
        etsVMOptions.push_back({EtsOptionType::ETS_NATIVE_LIBRARY_PATH, (char*)strdup(std::string(appLibPath).c_str())});
        etsVMOptions.push_back({EtsOptionType::ETS_VERIFICATION_MODE, "on-the-fly"});
        etsVMOptions.push_back({EtsOptionType::ETS_JIT, nullptr});
        etsVMOptions.push_back({EtsOptionType::ETS_MOBILE_LOG, (void*)ArkMobileLog});
        etsVMOptions.push_back({EtsOptionType::ETS_AOT, nullptr});
        pandaVMArgs.nOptions = etsVMOptions.size();
        pandaVMArgs.options = etsVMOptions.data();
        g_vmEntry.vmKind = vmKind;

        int32_t nVMs = 0;
        typedef int (*createVM_t)(void** pVM, void** pEnv, void* vmInitArgs);
        typedef int (*getVMs_t)(void** pVM, int32_t bufLen, int32_t* nVMs);
        createVM_t createVM = (createVM_t)findSymbol(handle, "ETS_CreateVM");
        getVMs_t getVMs = (getVMs_t)findSymbol(handle, "ETS_GetCreatedVMs");
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

#ifdef KOALA_KOTLIN
    if (vmKind == KOTLIN_KIND) {
        g_vmEntry.vmKind = vmKind;

        typedef kotlin_koala_ExportedSymbols* (*get_symbols_t)(void);
        get_symbols_t get_symbols = (get_symbols_t)findSymbol(handle, "kotlin_koala_symbols");
        env = static_cast<void*>(get_symbols());

        result = 0;
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
    const char* loadViewMethodName;
    const char* loadViewMethodSig;
};

#ifdef KOALA_JNI
const AppInfo javaAppInfo = {
    "org/koalaui/arkoala/Application",
    "createApplication",
    "(Ljava/lang/String;Ljava/lang/String;)Lorg/koalaui/arkoala/Application;",
    "start",
    "(JI)J",
    "enter",
    "(IIJ)Z",
    "emitEvent",
    "(IIII)Ljava/lang/String;",
    "UNUSED",
    "()V"
};
#endif

#ifdef KOALA_ETS_NAPI
const AppInfo pandaAppInfo = {
    "@ohos/arkui/Application/Application",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZI:L@ohos/arkui/Application/Application;",
    "start",
    "JI:J",
    "enter",
    "IIJ:Z",
    "emitEvent",
    "IIII:Lstd/core/String;",
    "UNUSED",
    "I:I"
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
        "Lstd/core/String;:V",
    };
#endif
#ifdef KOALA_ANI
const AppInfo harnessAniAppInfo = {
    "L@koalaui/ets-harness/src/EtsHarnessApplication/EtsHarnessApplication;",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;Lstd/core/String;ZI:L@koalaui/ets-harness/src/EtsHarnessApplication/EtsHarnessApplication;",
    "start",
    "JI:J",
    "enter",
    "IIJ:Z",
    "emitEvent",
    "IIII:Lstd/core/String;",
    "restartWith",
    "Lstd/core/String;:V",
    "UNUSED",
    "I:I"
};
const AppInfo aniAppInfo = {
    "L@ohos/arkui/Application/Application;",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;Lstd/core/String;ZI:L@ohos/arkui/Application/Application;",
    "start",
    "JI:J",
    "enter",
    "IJ:Z",
    "emitEvent",
    "IIII:Lstd/core/String;",
    "UNUSED",
    "I:I",
    "loadView",
    "Lstd/core/String;Lstd/core/String;:Lstd/core/String;",
};
#endif

#ifdef KOALA_KOTLIN
const AppInfo kotlinAppInfo = { 0 };
#endif

extern "C" DLL_EXPORT KNativePointer StartApplication(const char* appUrl, const char* appParams, int32_t loopIterations)
{
    const auto isTestEnv = std::string(appUrl) == "EtsHarness";
    const AppInfo* appInfo =
        #ifdef KOALA_JNI
        (g_vmEntry.vmKind == JAVA_VM_KIND) ? &javaAppInfo :
        #endif
        #if defined(KOALA_ETS_NAPI)
        (g_vmEntry.vmKind == PANDA_VM_KIND) ? isTestEnv ? &harnessAppInfo : &pandaAppInfo :
        #endif
        #if defined(KOALA_ANI)
        (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) ? isTestEnv ? &harnessAniAppInfo : &aniAppInfo :
        #endif
        #if defined(KOALA_KOTLIN)
        (g_vmEntry.vmKind == KOTLIN_KIND) ? &kotlinAppInfo :
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
#if defined(KOALA_ETS_NAPI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND) {
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
        auto useNativeLog = false;
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
        // Improve: pass app entry point!
        return reinterpret_cast<KNativePointer>(etsEnv->CallLongMethod((ets_object)(app), start, &g_vmEntry.foreignVMContext));
    }
#endif
#if defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        auto *env = reinterpret_cast<ani_env *>(g_vmEntry.env);

        ani_class appClass {};
        auto status = env->FindClass(appInfo->className, &appClass);
        if (status != ANI_OK) {
            LOGE("Cannot load main class %" LOG_PUBLIC "s\n", appInfo->className);
            ResetErrorIfExists(env);
            return nullptr;
        }
        ani_static_method create {};
        status = env->Class_FindStaticMethod(appClass, appInfo->createMethodName, appInfo->createMethodSig, &create);
        if (status != ANI_OK) {
            LOGE("Cannot find create method %" LOG_PUBLIC "s\n", appInfo->createMethodName);
            ResetErrorIfExists(env);
            return nullptr;
        }

        ani_boolean useNativeLog = ANI_FALSE;
        ani_string appUrlString {};
        status = env->String_NewUTF8(appUrl, interop_strlen(appUrl), &appUrlString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return nullptr;
        }

        ani_string userPandaFilesPathString {};
        status = env->String_NewUTF8(g_vmEntry.userFilesAbcPaths.c_str(), g_vmEntry.userFilesAbcPaths.size(), &userPandaFilesPathString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return nullptr;
        }

        ani_string appParamsString {};
        status = env->String_NewUTF8(appParams, interop_strlen(appParams), &appParamsString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return nullptr;
        }

        ani_ref appInstance {};
        status = env->Class_CallStaticMethod_Ref(appClass, create, &appInstance, appUrlString, userPandaFilesPathString, appParamsString,
            useNativeLog, static_cast<ani_int>(g_vmEntry.vmKind));
        if (status != ANI_OK) {
            LOGE("createApplication returned null");
            ResetErrorIfExists(env);
            return nullptr;
        }
        ani_ref app {};
        status = env->GlobalReference_Create(appInstance, &app);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return nullptr;
        }
        g_vmEntry.app = (void*)app;

        ani_method start {};
        status = env->Class_FindMethod(appClass, appInfo->startMethodName, appInfo->startMethodSig, &start);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return nullptr;
        }
        ani_method enter {};
        status = env->Class_FindMethod(appClass, appInfo->enterMethodName, nullptr, &enter);
        if (status != ANI_OK) {
            LOGE("Cannot find `enter` method %" LOG_PUBLIC "s", appInfo->enterMethodName);
            ResetErrorIfExists(env);
            return nullptr;
        }
        g_vmEntry.enter = reinterpret_cast<void *>(enter);
        ani_method emitEvent {};
        status = env->Class_FindMethod(appClass, appInfo->emitEventMethodName, appInfo->emitEventMethodSig, &emitEvent);
        if (status != ANI_OK) {
            LOGE("Cannot find `emitEvent` method %" LOG_PUBLIC "s", appInfo->emitEventMethodSig);
            ResetErrorIfExists(env);
            return nullptr;
        }
        g_vmEntry.emitEvent = reinterpret_cast<void *>(emitEvent);
        ani_method loadView {};
        status = env->Class_FindMethod(appClass, appInfo->loadViewMethodName, appInfo->loadViewMethodSig, &loadView);
        if (status != ANI_OK) {
            LOGE("Cannot find `%" LOG_PUBLIC "s` method %" LOG_PUBLIC "s",
                appInfo->loadViewMethodName, appInfo->loadViewMethodSig);
            ResetErrorIfExists(env);
            return nullptr;
        }
        g_vmEntry.loadView = reinterpret_cast<void *>(loadView);

        if (isTestEnv) {
            ani_method restartWith {};
            status = env->Class_FindMethod(appClass, appInfo->restartWithMethodName, appInfo->restartWithMethodSig, &restartWith);
            if (status != ANI_OK) {
                LOGE("Cannot find `restartWith` method sig=%" LOG_PUBLIC "s", appInfo->restartWithMethodSig);
                ResetErrorIfExists(env);
                return nullptr;
            }
            g_vmEntry.restartWith = reinterpret_cast<void *>(restartWith);
        }

        ani_long ptr = 0;
        // Improve: pass app entry point!
        status = env->Object_CallMethod_Long(static_cast<ani_object>(appInstance), start, &ptr,
            reinterpret_cast<ani_long>(&g_vmEntry.foreignVMContext), loopIterations);
        if (status != ANI_OK) {
            LOGE("Cannot start application");
            ResetErrorIfExists(env);
            return nullptr;
        }
        return reinterpret_cast<KNativePointer>(ptr);
    }
#endif

#if defined(KOALA_KOTLIN)
    if (g_vmEntry.vmKind == KOTLIN_KIND) {
        auto env = reinterpret_cast<kotlin_koala_ExportedSymbols*>(g_vmEntry.env);
        auto ApplicationType = env->kotlin.root.koala.Application;

        auto app = ApplicationType.Application(appUrl, appParams);
        g_vmEntry.app = (void*)app.pinned;

        auto ptr = ApplicationType.start(app);
        return reinterpret_cast<KNativePointer>(ptr.pinned);
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
#if defined(KOALA_ETS_NAPI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND) {
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
#if defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        ani_env* env = reinterpret_cast<ani_env *>(g_vmEntry.env);
        if (g_vmEntry.enter == nullptr) {
            LOGE("Cannot find enter method");
            return -1;
        }
        ani_boolean result = ANI_FALSE;
        auto status = env->Object_CallMethod_Boolean(reinterpret_cast<ani_object>(g_vmEntry.app),
            reinterpret_cast<ani_method>(g_vmEntry.enter), &result,
            static_cast<ani_int>(arg0), static_cast<ani_int>(arg1),
            reinterpret_cast<ani_long>(&g_vmEntry.foreignVMContext));
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return ANI_FALSE;
        }
        return result;
    }
#endif

#ifdef KOALA_KOTLIN
    if (g_vmEntry.vmKind == KOTLIN_KIND) {
        auto env = reinterpret_cast<kotlin_koala_ExportedSymbols*>(g_vmEntry.env);
        auto ApplicationType = env->kotlin.root.koala.Application;

        kotlin_koala_kref_koala_Application app = { .pinned = g_vmEntry.app };
        return ApplicationType.enter(app, arg0, arg1) ? 1 : 0;
    }
#endif

    return 1;
}

extern "C" DLL_EXPORT const char* EmitEvent(const KInt type, const KInt target, const KInt arg0, const KInt arg1)
{
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

#if defined(KOALA_ETS_NAPI)
    if (g_vmEntry.vmKind == PANDA_VM_KIND) {
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
#if defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        ani_env *env = reinterpret_cast<ani_env *>(g_vmEntry.env);
        if (g_vmEntry.emitEvent == nullptr) {
            LOGE("Cannot find emitEvent method");
            return "-1";
        }
        ani_ref result {};
        auto status = env->Object_CallMethod_Ref(reinterpret_cast<ani_object>(g_vmEntry.app),
            reinterpret_cast<ani_method>(g_vmEntry.emitEvent),
            &result,
            static_cast<ani_int>(type),
            static_cast<ani_int>(target),
            static_cast<ani_int>(arg0),
            static_cast<ani_int>(arg1));
        if (status != ANI_OK) {
            LOGE("Calling emitEvent() method gave an error");
            ResetErrorIfExists(env);
            return "-1";
        }

        auto str = static_cast<ani_string>(result);
        ani_size sz = 0;
        status = env->String_GetUTF8Size(str, &sz);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return "-1";
        }
        auto buffer = new char[sz + 1];
        ani_size writtenChars = 0;
        status = env->String_GetUTF8(str, buffer, sz + 1, &writtenChars);
        if (status != ANI_OK || writtenChars != sz) {
            delete [] buffer;
            ResetErrorIfExists(env);
            return "-1";
        }
        return buffer;
    }
#endif
    return "-1";
}

extern "C" DLL_EXPORT void RestartWith(const char* page)
{
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
#if defined(KOALA_ETS_NAPI)
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
#if defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        ani_env *env = reinterpret_cast<ani_env *>(g_vmEntry.env);
        if (!g_vmEntry.restartWith) {
            LOGE("Cannot find restartWith method");
            return;
        }
        ani_string pageString {};
        auto status = env->String_NewUTF8(page, interop_strlen(page), &pageString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return;
        }
        status = env->Object_CallMethod_Void(reinterpret_cast<ani_object>(g_vmEntry.app),
            reinterpret_cast<ani_method>(g_vmEntry.restartWith), pageString);
        if (status != ANI_OK) {
            LOGE("Calling restartWith() method gave an error");
            ResetErrorIfExists(env);
        }
    }
#endif
}

extern "C" DLL_EXPORT const char* LoadView(const char* className, const char* params)
{
#if defined(KOALA_ANI)
    if (g_vmEntry.vmKind == PANDA_ANI_VM_KIND) {
        ani_env *env = reinterpret_cast<ani_env *>(g_vmEntry.env);
        if (!g_vmEntry.loadView) {
            return strdup("Cannot find loadView() method");
        }
        ani_string classNameString {};
        auto status = env->String_NewUTF8(className, interop_strlen(className), &classNameString);
        if (status != ANI_OK) {
            return strdup("Cannot make ANI string");
        }
        ani_string paramsString {};
        status = env->String_NewUTF8(params, interop_strlen(params), &paramsString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return strdup("Cannot make ANI string");
        }
        ani_string resultString = nullptr;
        status = env->Object_CallMethod_Ref(reinterpret_cast<ani_object>(g_vmEntry.app),
            reinterpret_cast<ani_method>(g_vmEntry.loadView),
            (ani_ref*)&resultString,
            classNameString, paramsString);
        if (status != ANI_OK) {
            ResetErrorIfExists(env);
            return strdup("Calling laodView() method gave an error");
        }
        ani_size resultStringLength = 0;
        status = env->String_GetUTF8Size(resultString, &resultStringLength);
        char* resultChars = (char*)malloc(resultStringLength);
        status = env->String_GetUTF8(resultString, resultChars, resultStringLength, &resultStringLength);
        return resultChars;
    }
#endif
    return strdup("Unsupported");
}

namespace fs = std::filesystem;

bool ends_with(std::string str, std::string suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

void traverseDir(const std::string& root, std::vector<std::string>& paths, std::string suffix, const std::vector<std::string>& fallbackPaths)
{
    #ifdef KOALA_OHOS_ARM32
    // selinux prohibits any access to "/system/framework"
    if (root == "/system/framework") {
        for (auto path: fallbackPaths) {
            paths.push_back(root + "/" + path + suffix);
        }
        return;
    }
    #endif

    if (!fs::exists(root)) {
        LOGE("Cannot open dir %" LOG_PUBLIC "s\n", root.c_str());
        return;
    }

    #if defined(KOALA_OHOS)
    suffix += ".so";
    #endif

    LOGI("Searching in %" LOG_PUBLIC "s\n", root.c_str());
    for (auto &file : fs::recursive_directory_iterator(root)) {
        if (ends_with(file.path().string(), suffix) && fs::is_regular_file(file)) {
            paths.push_back(file.path().string());
        }
    }
}
