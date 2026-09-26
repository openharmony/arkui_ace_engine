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
#include <cstdarg>
#include <cstring>

#include "base/log/log_wrapper.h"

namespace {
std::atomic<int> g_printLogCount { 0 };
std::atomic<int> g_diagnosticLogCount { 0 };
DiagnosticLog g_lastDiagnosticLog { nullptr, nullptr, nullptr };

constexpr char DIAGNOSTIC_MARKER[] = "ArkUI runtime check hit";
} // namespace

void ResetPrintLogCount()
{
    g_printLogCount.store(0, std::memory_order_relaxed);
}

int GetPrintLogCount()
{
    return g_printLogCount.load(std::memory_order_relaxed);
}

int GetDiagnosticLogCount()
{
    return g_diagnosticLogCount.load(std::memory_order_relaxed);
}

void ResetDiagnosticLog()
{
    g_diagnosticLogCount.store(0, std::memory_order_relaxed);
    g_lastDiagnosticLog = { nullptr, nullptr, nullptr };
}

const DiagnosticLog* GetLastDiagnosticLog()
{
    return &g_lastDiagnosticLog;
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
    g_printLogCount.fetch_add(1, std::memory_order_relaxed);
    if (fmt && std::strstr(fmt, DIAGNOSTIC_MARKER) != nullptr) {
        va_list args;
        va_start(args, fmt);
        (void)va_arg(args, const char*); // skip: file name
        (void)va_arg(args, int);         // skip: line number
        g_lastDiagnosticLog.checkName = va_arg(args, const char*);
        g_lastDiagnosticLog.apiName = va_arg(args, const char*);
        g_lastDiagnosticLog.reason = va_arg(args, const char*);
        va_end(args);
        g_diagnosticLogCount.fetch_add(1, std::memory_order_relaxed);
    }
}
} // namespace OHOS::Ace
