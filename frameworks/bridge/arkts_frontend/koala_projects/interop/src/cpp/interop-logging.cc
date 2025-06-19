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
#include <string>
#include <vector>

#include "interop-logging.h"

namespace {

struct Log {
    std::string log;
    bool isActive = true;
};

std::vector<Log*> groupedLogs;

void startGroupedLog(int index) {
    if (index >= (int)groupedLogs.size()) {
        groupedLogs.resize(index + 1);
        for (int i = 0; i <= index; i++) {
            if (!groupedLogs[i]) groupedLogs[i] = new Log();
        }
    }
    groupedLogs[index]->isActive = true;
    groupedLogs[index]->log.clear();
}

void stopGroupedLog(int index) {
    if (index < (int)groupedLogs.size()) {
        groupedLogs[index]->isActive = false;
    }
}

void appendGroupedLog(int index, const char* str) {
    if (index < (int)groupedLogs.size()) {
        groupedLogs[index]->log.append(str);
    }
}

const char* getGroupedLog(int index) {
    if (index < (int)groupedLogs.size()) {
        auto result = groupedLogs[index]->log.c_str();
        return result;
    }
    return "";
}

int needGroupedLog(int index) {
    if (index < (int)groupedLogs.size()) {
        return groupedLogs[index]->isActive;
    }
    return 0;
}

const GroupLogger defaultInstance = {
    startGroupedLog,
    stopGroupedLog,
    appendGroupedLog,
    getGroupedLog,
    needGroupedLog,
};

} // namespace

const GroupLogger* GetDefaultLogger() {
    return &defaultInstance;
}