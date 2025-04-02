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

#ifndef _INTEROP_CRASHDUMP_H
#define _INTEROP_CRASHDUMP_H

#ifdef KOALA_LINUX
#include <signal.h>
#include <execinfo.h>

sighandler_t oldCrashHandler = nullptr;

static void onCrashHandler(int signo) {
    void* stack[20];
    size_t size = backtrace(stack, 20);
    backtrace_symbols_fd(stack, size, STDERR_FILENO);
    if (oldCrashHandler) oldCrashHandler(signo);
}

static void installCrashHandlers() {
    static bool installed = false;
    if (!installed) {
        oldCrashHandler = signal(SIGSEGV, onCrashHandler);
        installed = true;
    }
}
#else
static void installCrashHandlers() {}
#endif

#endif  // _INTEROP_CRASHDUMP_H