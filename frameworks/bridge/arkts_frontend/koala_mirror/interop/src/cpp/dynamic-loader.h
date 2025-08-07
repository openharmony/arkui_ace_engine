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

#ifndef _DYNAMIC_LOADER_H
#define _DYNAMIC_LOADER_H

#include <string>

#ifdef KOALA_WINDOWS
#include <windows.h>
// Here we need to find module where GetArkUINodeAPI()
// function is implemented.
inline void* loadLibrary(const std::string& libPath) {
    return LoadLibraryA(libPath.c_str());
}

inline const char* libraryError() {
    static char error[256];
    snprintf(error, sizeof error, "error %lu", GetLastError());
    return error;
}

inline void* findSymbol(void* library, const char* name) {
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}

inline std::string libName(const char* lib) {
    return std::string(lib) + ".dll";
}

#elif defined(KOALA_LINUX) || defined(KOALA_MACOS) || defined(KOALA_OHOS)
#include <dlfcn.h>

inline void* loadLibrary(const std::string& libPath) {
    void* handle = dlopen(libPath.c_str(), RTLD_LOCAL | RTLD_NOW);
    if (!handle) {
        return nullptr;
    }
    return handle;
}

inline const char* libraryError() {
    return dlerror();
}

inline std::string symbolName(const char* name) {
    return name;
}

inline void* findSymbol(void* library, const char* name) {
    return dlsym(library, symbolName(name).c_str());
}

inline std::string libName(const char* lib) {
    std::string result;
    std::string suffix =
#ifdef KOALA_MACOS
    ".dylib"
#else
    ".so"
#endif
    ;
    result = "lib" + std::string(lib) + suffix;
    return result;
}

#else

#include <cstdio>

inline void* loadLibrary(const std::string& libPath) {
    fprintf(stderr, "No loadLibrary() on this platform\n");
    return nullptr;
}

inline const char* libraryError() {
    fprintf(stderr, "No libraryError() on this platform\n");
    return nullptr;
}

inline std::string symbolName(const char* name) {
    fprintf(stderr, "No symbolName() on this platform\n");
    return "";
}

inline void* findSymbol(void* library, const char* name) {
    fprintf(stderr, "No findSymbol() on this platform\n");
    return nullptr;
}

inline std::string libName(const char* lib) {
    fprintf(stderr, "No libName() on this platform\n");
    return "";
}

#endif

#endif  // _DYNAMIC_LOADER_H