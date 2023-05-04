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

#include "base/log/ace_performance_check.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <memory>
#include <ostream>
#include <string>

#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/container.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t BASE_YEAR = 1900;
constexpr char DATE_FORMAT[] = "MM dd HH:mm:ss";
constexpr int32_t CONVERT_MILLISECONDS = 1000;
constexpr int32_t CONVERT_NANOSECONDS = 1000000;
} // namespace

// ============================== survival interval of JSON files ============================================

std::unique_ptr<JsonValue> AcePerformanceCheck::performanceInfo_ = nullptr;

void AcePerformanceCheck::Start()
{
    if (SystemProperties::IsPerformanceCheckEnabled()) {
        performanceInfo_ = JsonUtil::Create(true);
    }
}

void AcePerformanceCheck::Stop()
{
    if (performanceInfo_) {
        auto info = performanceInfo_->ToString();
        // output info to json file
        auto filePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/arkui_bestpractice.json";
        std::unique_ptr<std::ostream> ss = std::make_unique<std::ofstream>(filePath);
        CHECK_NULL_VOID(ss);
        DumpLog::GetInstance().SetDumpFile(std::move(ss));
        DumpLog::GetInstance().Print(info);
        DumpLog::GetInstance().Reset();
        performanceInfo_.reset(nullptr);
    }
}

// ============================== specific implementation ======================================================

AceScopedPerformanceCheck::AceScopedPerformanceCheck(const std::string& name)
{
    if (AcePerformanceCheck::performanceInfo_) {
        // micro sec.
        markTime_ = GetMicroTickCount();
        functionName_ = name;
    }
}

AceScopedPerformanceCheck::~AceScopedPerformanceCheck()
{
    if (AcePerformanceCheck::performanceInfo_) {
        // convert micro sec to ms with 1000.
        auto sec = static_cast<int64_t>((GetMicroTickCount() - markTime_) / CONVERT_MILLISECONDS);
        functionName_.empty() ? RecordVsyncTimeout(sec) : RecordFunctionTimeout(sec, functionName_);
    }
}

bool AceScopedPerformanceCheck::CheckIsRuleContainsPage(const std::string& ruleType, const std::string& pagePath)
{
    // check for the presence of rule json
    if (!AcePerformanceCheck::performanceInfo_->Contains(ruleType)) {
        AcePerformanceCheck::performanceInfo_->Put(ruleType.c_str(), JsonUtil::CreateArray(false));
        return false;
    }
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue(ruleType);
    auto size = ruleJson->GetArraySize();
    for (int32_t i = 0; i < size; i++) {
        auto indexJson = ruleJson->GetArrayItem(i);
        auto value = indexJson->GetString("pagePath", {});
        if (value == pagePath) {
            return true;
        }
    }
    return false;
}

std::string AceScopedPerformanceCheck::GetEventTime()
{
    // get system date and time
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto* local = std::localtime(&now);
    if (!local) {
        LOGE("Get localtime failed");
        return {};
    }

    // this is for i18n date time
    DateTime dateTime;
    dateTime.year = static_cast<uint32_t>(local->tm_year + BASE_YEAR);
    dateTime.month = static_cast<uint32_t>(local->tm_mon);
    dateTime.day = static_cast<uint32_t>(local->tm_mday);
    dateTime.hour = static_cast<uint32_t>(local->tm_hour);
    dateTime.minute = static_cast<uint32_t>(local->tm_min);
    dateTime.second = static_cast<uint32_t>(local->tm_sec);
    auto time = Localization::GetInstance()->FormatDateTime(dateTime, DATE_FORMAT);
    return time;
}

CodeInfo AceScopedPerformanceCheck::GetCodeInfo(int32_t row, int32_t col)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, {});
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, {});
    auto sourceMap = frontend->GetCurrentPageSourceMap();
    CHECK_NULL_RETURN(sourceMap, {});
    auto codeInfo = sourceMap->Find(row, col);
    return { codeInfo.row, codeInfo.col, codeInfo.sources };
}

int32_t AceScopedPerformanceCheck::GetSourceLine(int32_t row, int32_t col)
{
    auto codeInfo = GetCodeInfo(row, col);
    return codeInfo.row;
}

int32_t AceScopedPerformanceCheck::GetItemMapSize(const CheckNodeMap& itemMap)
{
    int32_t count = 0;
    for (const auto& iter : itemMap) {
        count += iter.second;
    }
    return count;
}

void AceScopedPerformanceCheck::RecordPageNodeCountAndDepth(
    int32_t pageNodeCount, int32_t pageDepth, const CheckNodeMap& nodeMap)
{
    if (pageNodeCount < SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::PAGE_NODES) &&
        pageDepth < SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::PAGE_DEPTH)) {
        return;
    }
    // // get page path
    auto codeInfo = GetCodeInfo(1, 1);
    // check if the rule contains the current page
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage("9901", codeInfo.sources)) {
        return;
    }
    // get event time
    auto eventTime = GetEventTime();
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9901");
    auto pageJson = JsonUtil::Create(false);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    pageJson->Put("nodeCount", pageNodeCount);
    pageJson->Put("depth", pageDepth);
    // add children size > 100 of component to pageJson
    for (const auto& iter : nodeMap) {
        if (iter.second > SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::NODE_CHILDREN)) {
            auto componentJson = JsonUtil::Create(false);
            componentJson->Put("name", iter.first.tag.c_str());
            componentJson->Put("items", iter.second);
            componentJson->Put("sourceLine", GetSourceLine(iter.first.row, iter.first.col));
            std::unique_ptr<JsonValue> componentsJson = nullptr;
            if (pageJson->Contains("components")) {
                componentsJson = pageJson->GetValue("components");
                componentsJson->Put(componentJson);
            } else {
                componentsJson = JsonUtil::CreateArray(false);
                componentsJson->Put(componentJson);
                pageJson->Put("components", componentsJson);
            }
        }
    }

    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordFunctionTimeout(int64_t sec, const std::string& functionName)
{
    if (sec < SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::FUNCTION_TIMEOUT)) {
        return;
    }
    auto codeInfo = GetCodeInfo(1, 1);
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage("9902", codeInfo.sources)) {
        return;
    }
    auto eventTime = GetEventTime();
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9902");
    auto pageJson = JsonUtil::Create(false);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    pageJson->Put("functionName", functionName.c_str());
    auto sources = EngineHelper::GetPositionOnJsCode();
    pageJson->Put("sourceLine", GetSourceLine(sources.first, sources.second));
    pageJson->Put("costTime", sec);
    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordVsyncTimeout(int64_t sec)
{
    if (sec < SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::VSYNC_TIMEOUT)) {
        return;
    }
    auto codeInfo = GetCodeInfo(1, 1);
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage("9903", codeInfo.sources)) {
        return;
    }
    auto eventTime = GetEventTime();
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9903");
    auto pageJson = JsonUtil::Create(false);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    pageJson->Put("costTime", sec);
    for (auto& info : nodeList_) {
        if (info.sec > SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::NODE_TIMEOUT)) {
            auto componentJson = JsonUtil::Create(false);
            componentJson->Put("name", info.tag.c_str());
            componentJson->Put("costTime", info.sec);
            componentJson->Put("sourceLine", info.row);
            std::unique_ptr<JsonValue> componentsJson = nullptr;
            if (pageJson->Contains("components")) {
                componentsJson = pageJson->GetValue("components");
                componentsJson->Put(componentJson);
            } else {
                componentsJson = JsonUtil::CreateArray(false);
                componentsJson->Put(componentJson);
                pageJson->Put("components", componentsJson);
            }
        }
    }

    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::InsertNodeTimeout(int64_t sec, int32_t row, int32_t col, const std::string& tag)
{
    if (!SystemProperties::IsPerformanceCheckEnabled() || tag == "stage" || tag == "page" || tag == "root") {
        return;
    }
    NodeTimeoutInfo info;
    info.row = GetSourceLine(row, col);
    info.sec = sec / CONVERT_NANOSECONDS;
    info.tag = tag;
    nodeList_.emplace_back(info);
}

void AceScopedPerformanceCheck::RecordForEachItemsCount(const CheckNodeMap& itemMap)
{
    if (GetItemMapSize(itemMap) <
        SystemProperties::GetPerformanceParameterWithType(PerformanceParameterType::FOREACH_ITEMS)) {
        return;
    }
    auto codeInfo = GetCodeInfo(1, 1);
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage("9904", codeInfo.sources)) {
        return;
    }
    auto eventTime = GetEventTime();
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9904");
    auto pageJson = JsonUtil::Create(false);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    for (const auto& iter : itemMap) {
        auto componentJson = JsonUtil::Create(false);
        componentJson->Put("name", iter.first.tag.c_str());
        componentJson->Put("items", iter.second);
        componentJson->Put("sourceLine", GetSourceLine(iter.first.row, iter.first.col));
        std::unique_ptr<JsonValue> componentsJson = nullptr;
        if (pageJson->Contains("components")) {
            componentsJson = pageJson->GetValue("components");
            componentsJson->Put(componentJson);
        } else {
            componentsJson = JsonUtil::CreateArray(false);
            componentsJson->Put(componentJson);
            pageJson->Put("components", componentsJson);
        }
    }
    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordFlexLayoutsCount(const CheckNodeMap& itemMap)
{
    if (itemMap.empty()) {
        return;
    }
    auto codeInfo = GetCodeInfo(1, 1);
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage("9905", codeInfo.sources)) {
        return;
    }
    auto eventTime = GetEventTime();
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9905");
    auto pageJson = JsonUtil::Create(false);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    for (const auto& iter : itemMap) {
        auto componentJson = JsonUtil::Create(false);
        componentJson->Put("name", iter.first.tag.c_str());
        componentJson->Put("flexTime", iter.second);
        componentJson->Put("sourceLine", GetSourceLine(iter.first.row, iter.first.col));
        std::unique_ptr<JsonValue> componentsJson = nullptr;
        if (pageJson->Contains("components")) {
            componentsJson = pageJson->GetValue("components");
            componentsJson->Put(componentJson);
        } else {
            componentsJson = JsonUtil::CreateArray(false);
            componentsJson->Put(componentJson);
            pageJson->Put("components", componentsJson);
        }
    }
    ruleJson->Put(pageJson);
}
} // namespace OHOS::Ace
