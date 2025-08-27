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

#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdarg>
#include <memory>
#include "oh_sk_log.h"

static const char* KOALAUI_OHOS_LOG_ROOT = "/data/storage/el2/base/files/logs";

#define APPLY_LOG_FILE_PATTERN(buf, t, ms, pid) \
    sprintf(buf, "%s/%d_%d_%d_%lld.pid%d.log", \
    KOALAUI_OHOS_LOG_ROOT, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, ms.tv_sec, pid)

const char* oh_sk_log_type_str(oh_sk_log_type type) {
    switch (type) {
        case Log_Debug: return "D";
        case Log_Info: return "I";
        case Log_Warn: return "W";
        case Log_Error: return "E";
        case Log_Fatal: return "F";
    }
}

void oh_sk_file_log(oh_sk_log_type type, const char* msg, ...) {
    time_t t = time(nullptr);
    struct tm lt = *localtime(&t);
    struct timeval ms{};
    gettimeofday(&ms, nullptr);

    static char* path = nullptr;
    if (!path) {
        path = new char[strlen(KOALAUI_OHOS_LOG_ROOT) + 100];
        APPLY_LOG_FILE_PATTERN(path, lt, ms, getpid());
        mkdir(KOALAUI_OHOS_LOG_ROOT, 0777);
    }

    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(path, "a"), fclose);
    if (!file) return;

    fprintf(file.get(), "%02d-%02d %02d:%02d:%02d.%03lld %s koala: ",
            lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min, lt.tm_sec, ms.tv_usec / 1000,
            oh_sk_log_type_str(type));

    va_list args;
    va_start(args, msg);
    vfprintf(file.get(), msg, args);
    va_end(args);

    fprintf(file.get(), "\n");
}
