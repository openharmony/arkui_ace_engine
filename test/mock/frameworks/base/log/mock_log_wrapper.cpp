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
#include "test/mock/frameworks/base/log/mock_log_wrapper.h"

#include <atomic>

#include "base/log/log_wrapper.h"

namespace {
std::atomic<int> g_printLogCount { 0 };
std::atomic<int> g_diagnosticCount { 0 };
} // namespace

void ResetPrintLogCount()
{
    g_printLogCount.store(0, std::memory_order_relaxed);
}

int GetPrintLogCount()
{
    return g_printLogCount.load(std::memory_order_relaxed);
}

int GetDiagnosticCount()
{
    return g_diagnosticCount.load(std::memory_order_relaxed);
}

void ResetDiagnosticCount()
{
    g_diagnosticCount.store(0, std::memory_order_relaxed);
}

void IncrementDiagnosticCount()
{
    g_diagnosticCount.fetch_add(1, std::memory_order_relaxed);
}

namespace OHOS::Ace {

bool LogWrapper::JudgeLevel(LogLevel level)
{
    (void)level;
    return true;
}

void LogWrapper::SetLogLevel(LogLevel level)
{
    level_ = level;
}

LogLevel LogWrapper::GetLogLevel()
{
    return level_;
}

const char* LogWrapper::GetBriefFileName(const char* filePath)
{
    return filePath;
}

void LogWrapper::StripFormatString(const std::string& prefix, std::string& str)
{
    (void)prefix;
    (void)str;
}

void LogWrapper::ReplaceFormatString(const std::string& prefix, const std::string& replace, std::string& str)
{
    (void)prefix;
    (void)replace;
    (void)str;
}

void LogWrapper::PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, ...)
{
    (void)domain;
    (void)level;
    (void)tag;
    (void)fmt;
    g_printLogCount.fetch_add(1, std::memory_order_relaxed);
}
} // namespace OHOS::Ace
