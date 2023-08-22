/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UTILS_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UTILS_H

#ifdef WINDOWS_PLATFORM
#include <winsock2.h>
#include <windows.h>
using LIBHANDLE = HMODULE;
#define LOADLIB(libPath) LoadLibrary(libPath)
#define FREELIB(libHandle) FreeLibrary(libHandle)
#define LOADSYM(libHandle, symbol) GetProcAddress(libHandle, symbol)
#else
#include <dlfcn.h>
using LIBHANDLE = void*;
#define LOADLIB(libPath) dlopen(libPath, RTLD_LAZY|RTLD_LOCAL)
#define FREELIB(libHandle) dlclose(libHandle)
#define LOADSYM(libHandle, symbol) dlsym(libHandle, symbol)
#endif

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UTILS_H
