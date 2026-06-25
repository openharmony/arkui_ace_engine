/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "base/log/log_wrapper.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace {
void CheckThread(TaskExecutor::TaskType taskType)
{
    (void)taskType;
}

bool LogWrapper::JudgeLevel(LogLevel level)
{
    (void)level;
    return true;
}

const char* LogWrapper::GetBriefFileName(const char* filePath)
{
    return filePath;
}

void LogWrapper::PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, ...)
{
    (void)domain;
    (void)level;
    (void)tag;
    (void)fmt;
}
} // namespace OHOS::Ace
