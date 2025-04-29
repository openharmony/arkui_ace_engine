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
#include "base/i18n/localization.h"
#include "base/log/ace_checker.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "base/websocket/websocket_manager.h"
namespace OHOS::Ace {
namespace {
constexpr int32_t BASE_YEAR = 1900;
constexpr char DATE_FORMAT[] = "MM-dd HH:mm:ss";
constexpr int32_t CONVERT_NANOSECONDS = 1000000;
constexpr int32_t FUNCTION_TIMEOUT = 150;
constexpr char ETS_PATH[] = "/src/main/ets/";
constexpr char DEBUG_PATH[] = "entry/build/default/cache/default/default@CompileArkTS/esmodule/debug/";
constexpr char NEW_PATH[] = "entry|entry|1.0.0|src/main/ets/";
constexpr char TS_SUFFIX[] = ".ts";
constexpr char ETS_SUFFIX[] = ".ets";
constexpr char CHECK_RESULT[] = "{\"message_type\": \"SendArkPerformanceCheckResult\", \"performance_check_result\": ";
} // namespace

// ============================== survival interval of JSON files ============================================

std::unique_ptr<JsonValue> AcePerformanceCheck::performanceInfo_ = nullptr;
std::string AceScopedPerformanceCheck::currentPath_;
std::vector<std::pair<int64_t, std::string>> AceScopedPerformanceCheck::records_;
void AcePerformanceCheck::Start()
{
    if (AceChecker::IsPerformanceCheckEnabled()) {
        LOGI("performance check start");
        performanceInfo_ = JsonUtil::Create(true);
    }
}

void AcePerformanceCheck::Stop()
{
    if (performanceInfo_) {
        LOGI("performance check stop");
        auto info = performanceInfo_->ToString();
        if (AceChecker::IsWebSocketCheckEnabled()) {
            info = CHECK_RESULT + info + "}";
            WebSocketManager::SendMessage(info);
        } else {
            // output info to json file
            auto filePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/arkui_bestpractice.json";
            std::unique_ptr<std::ostream> ss = std::make_unique<std::ofstream>(filePath);
            CHECK_NULL_VOID(ss);
            DumpLog::GetInstance().SetDumpFile(std::move(ss));
            DumpLog::GetInstance().Print(info);
            DumpLog::GetInstance().Reset();
            AceChecker::NotifyCaution("AcePerformanceCheck::Stop, json data generated, store in " + filePath);
        }
        performanceInfo_.reset(nullptr);
    }
}

// ============================== specific implementation ======================================================

AceScopedPerformanceCheck::AceScopedPerformanceCheck(const std::string& name)
{
    // micro time.
    markTime_ = GetSysTimestamp();
    name_ = name;
}

AceScopedPerformanceCheck::~AceScopedPerformanceCheck()
{
    auto time = static_cast<int64_t>((GetSysTimestamp() - markTime_) / CONVERT_NANOSECONDS);
    if (time >= FUNCTION_TIMEOUT) {
        EventReport::ReportFunctionTimeout(name_, time, FUNCTION_TIMEOUT);
    }
    if (AcePerformanceCheck::performanceInfo_) {
        // convert micro time to ms with 1000.
        std::pair recordInfo { time, name_ };
        records_.push_back(recordInfo);
    }
}

bool AceScopedPerformanceCheck::CheckIsRuleContainsPage(const std::string& ruleType, const std::string& pagePath)
{
    // check for the presence of rule json
    CHECK_NULL_RETURN(AcePerformanceCheck::performanceInfo_, false);
    if (AceChecker::IsWebSocketCheckEnabled()) {
        if (!CheckIsRuleWebsocket(ruleType)) {
            return true;
        }
    }
    if (!AcePerformanceCheck::performanceInfo_->Contains(ruleType)) {
        AcePerformanceCheck::performanceInfo_->Put(ruleType.c_str(), JsonUtil::CreateArray(true));
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

std::string AceScopedPerformanceCheck::GetCurrentTime()
{
    // get system date and time
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto* local = std::localtime(&now);
    if (!local) {
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
    auto sourceMap = GetCurrentSourceMap();
    CHECK_NULL_RETURN(sourceMap, {});
    // There is no same row and column info of viewPU in sourcemap, but the row info is correct.
    auto codeInfo = sourceMap->Find(row, col, false);
    return { codeInfo.row, codeInfo.col, codeInfo.sources };
}

bool AceScopedPerformanceCheck::CheckPage(const CodeInfo& codeInfo, const std::string& rule)
{
    if (!codeInfo.sources.empty() && CheckIsRuleContainsPage(rule, codeInfo.sources)) {
        return true;
    }
    return false;
}

void AceScopedPerformanceCheck::RecordPerformanceCheckData(
    const PerformanceCheckNodeMap& nodeMap, int64_t vsyncTimeout, std::string path)
{
    currentPath_ = path;
    auto codeInfo = GetCodeInfo(1, 1);
    std::vector<PerformanceCheckNode> pageNodeList;
    std::vector<PerformanceCheckNode> flexNodeList;
    std::unordered_map<int32_t, PerformanceCheckNode> foreachNodeMap;
    int32_t itemCount = 0;
    int32_t maxDepth = 0;
    for (const auto& node : nodeMap) {
        if (node.second.childrenSize >= AceChecker::GetNodeChildren()) {
            pageNodeList.emplace_back(node.second);
        }
        if (node.second.pageDepth > maxDepth) {
            maxDepth = node.second.pageDepth;
        }
        if (node.second.flexLayouts != 0 && node.second.flexLayouts >= AceChecker::GetFlexLayouts()) {
            flexNodeList.emplace_back(node.second);
        }
        if (node.second.isForEachItem) {
            itemCount++;
            auto iter = foreachNodeMap.find(node.second.codeRow);
            if (iter != foreachNodeMap.end()) {
                iter->second.foreachItems++;
            } else {
                foreachNodeMap.insert(std::make_pair(node.second.codeRow, node.second));
            }
        }
    }
    RecordFunctionTimeout();
    RecordPageNodeCountAndDepth(nodeMap.size(), maxDepth, pageNodeList, codeInfo);
    RecordForEachItemsCount(itemCount, foreachNodeMap, codeInfo);
    RecordFlexLayoutsCount(flexNodeList, codeInfo);
    RecordVsyncTimeout(nodeMap, vsyncTimeout / CONVERT_NANOSECONDS, codeInfo);
}

void AceScopedPerformanceCheck::RecordPageNodeCountAndDepth(
    int32_t pageNodeCount, int32_t pageDepth, std::vector<PerformanceCheckNode>& pageNodeList, const CodeInfo& codeInfo)
{
    if ((pageNodeCount < AceChecker::GetPageNodes() && pageDepth < AceChecker::GetPageDepth()) ||
        CheckPage(codeInfo, "9901")) {
        return;
    }
    auto eventTime = GetCurrentTime();
    CHECK_NULL_VOID(AcePerformanceCheck::performanceInfo_);
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9901");
    auto pageJson = JsonUtil::Create(true);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    pageJson->Put("nodeCount", pageNodeCount);
    pageJson->Put("depth", pageDepth);
    // add children size > 100 of component to pageJson
    for (const auto& iter : pageNodeList) {
        auto componentJson = JsonUtil::Create(true);
        componentJson->Put("name", iter.nodeTag.c_str());
        componentJson->Put("items", iter.childrenSize);
        componentJson->Put("sourceLine", GetCodeInfo(iter.codeRow, iter.codeCol).row);
        std::unique_ptr<JsonValue> componentsJson;
        if (pageJson->Contains("components")) {
            componentsJson = pageJson->GetValue("components");
            componentsJson->Put(componentJson);
        } else {
            componentsJson = JsonUtil::CreateArray(true);
            componentsJson->Put(componentJson);
            pageJson->Put("components", componentsJson);
        }
    }
    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordFunctionTimeout()
{
    for (auto record : records_) {
        if (record.first < AceChecker::GetFunctionTimeout()) {
            continue;
        }
        auto codeInfo = GetCodeInfo(1, 1);
        if (!codeInfo.sources.empty()) {
            continue;
        }
        CheckIsRuleContainsPage("9902", codeInfo.sources);
        auto eventTime = GetCurrentTime();
        CHECK_NULL_VOID(AcePerformanceCheck::performanceInfo_);
        auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9902");
        auto pageJson = JsonUtil::Create(true);
        pageJson->Put("eventTime", eventTime.c_str());
        pageJson->Put("pagePath", codeInfo.sources.c_str());
        pageJson->Put("functionName", record.second.c_str());
        pageJson->Put("costTime", record.first);
        ruleJson->Put(pageJson);
    }
    records_.clear();
}

void AceScopedPerformanceCheck::RecordVsyncTimeout(
    const PerformanceCheckNodeMap& nodeMap, int64_t vsyncTimeout, const CodeInfo& codeInfo)
{
    if (vsyncTimeout < AceChecker::GetVsyncTimeout() || CheckPage(codeInfo, "9903")) {
        return;
    }
    auto eventTime = GetCurrentTime();
    CHECK_NULL_VOID(AcePerformanceCheck::performanceInfo_);
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9903");
    auto pageJson = JsonUtil::Create(true);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    pageJson->Put("costTime", vsyncTimeout);
    for (const auto& node : nodeMap) {
        int64_t layoutTime = node.second.layoutTime / CONVERT_NANOSECONDS;
        if (layoutTime != 0 && layoutTime >= AceChecker::GetNodeTimeout() && node.second.nodeTag != "page" &&
            node.second.nodeTag != "ContainerModal" && node.second.nodeTag != "JsView") {
            auto componentJson = JsonUtil::Create(true);
            componentJson->Put("name", node.second.nodeTag.c_str());
            componentJson->Put("costTime", layoutTime);
            componentJson->Put("sourceLine", GetCodeInfo(node.second.codeRow, node.second.codeCol).row);
            std::unique_ptr<JsonValue> componentsJson;
            if (pageJson->Contains("components")) {
                componentsJson = pageJson->GetValue("components");
                componentsJson->Put(componentJson);
            } else {
                componentsJson = JsonUtil::CreateArray(true);
                componentsJson->Put(componentJson);
                pageJson->Put("components", componentsJson);
            }
        }
    }
    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordForEachItemsCount(
    int32_t count, std::unordered_map<int32_t, PerformanceCheckNode>& foreachNodeMap, const CodeInfo& codeInfo)
{
    if (count == 0 || count < AceChecker::GetForeachItems() || CheckPage(codeInfo, "9904")) {
        return;
    }
    auto eventTime = GetCurrentTime();
    CHECK_NULL_VOID(AcePerformanceCheck::performanceInfo_);
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9904");
    auto pageJson = JsonUtil::Create(true);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    for (const auto& iter : foreachNodeMap) {
        auto componentJson = JsonUtil::Create(true);
        componentJson->Put("name", iter.second.nodeTag.c_str());
        componentJson->Put("items", iter.second.foreachItems + 1);
        componentJson->Put("sourceLine", GetCodeInfo(iter.second.codeRow, iter.second.codeCol).row);
        std::unique_ptr<JsonValue> componentsJson;
        if (pageJson->Contains("components")) {
            componentsJson = pageJson->GetValue("components");
            componentsJson->Put(componentJson);
        } else {
            componentsJson = JsonUtil::CreateArray(true);
            componentsJson->Put(componentJson);
            pageJson->Put("components", componentsJson);
        }
    }
    ruleJson->Put(pageJson);
}

void AceScopedPerformanceCheck::RecordFlexLayoutsCount(
    const std::vector<PerformanceCheckNode>& flexNodeList, const CodeInfo& codeInfo)
{
    if (flexNodeList.empty() || CheckPage(codeInfo, "9905")) {
        return;
    }
    auto eventTime = GetCurrentTime();
    CHECK_NULL_VOID(AcePerformanceCheck::performanceInfo_);
    auto ruleJson = AcePerformanceCheck::performanceInfo_->GetValue("9905");
    auto pageJson = JsonUtil::Create(true);
    pageJson->Put("eventTime", eventTime.c_str());
    pageJson->Put("pagePath", codeInfo.sources.c_str());
    for (auto& node : flexNodeList) {
        auto componentJson = JsonUtil::Create(true);
        componentJson->Put("name", node.nodeTag.c_str());
        componentJson->Put("flexTime", node.flexLayouts);
        componentJson->Put("sourceLine", GetCodeInfo(node.codeRow, node.codeCol).row);
        std::unique_ptr<JsonValue> componentsJson;
        if (pageJson->Contains("components")) {
            componentsJson = pageJson->GetValue("components");
            componentsJson->Put(componentJson);
        } else {
            componentsJson = JsonUtil::CreateArray(true);
            componentsJson->Put(componentJson);
            pageJson->Put("components", componentsJson);
        }
    }
    ruleJson->Put(pageJson);
}

RefPtr<Framework::RevSourceMap> AceScopedPerformanceCheck::GetCurrentSourceMap()
{
    std::string jsSourceMap;
    auto sourceMap = AceType::MakeRefPtr<Framework::RevSourceMap>();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pos = currentPath_.find("pages");
    if (pos != std::string::npos) {
        currentPath_ = currentPath_.substr(pos, currentPath_.size());
    }
    pos = currentPath_.find(".js");
    if (pos != std::string::npos) {
        currentPath_ = currentPath_.substr(0, pos);
    }
    if (container->IsUseStageModel()) {
        auto pagePath = currentPath_;
        auto moduleName = container->GetModuleName();
        std::string judgePath = "";
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            judgePath = DEBUG_PATH + moduleName + ETS_PATH + pagePath + TS_SUFFIX;
        } else {
            judgePath = moduleName + ETS_PATH + pagePath + ETS_SUFFIX;
        }
        if (Framework::GetAssetContentImpl(container->GetAssetManager(), "sourceMaps.map", jsSourceMap)) {
            auto jsonPages = JsonUtil::ParseJsonString(jsSourceMap);
            auto child = jsonPages->GetChild();
            if (!child->GetValue("entry-package-info")->IsNull()) {
                judgePath = NEW_PATH + pagePath + TS_SUFFIX;
            }
            auto jsonPage = jsonPages->GetValue(judgePath)->ToString();
            sourceMap = AceType::MakeRefPtr<Framework::RevSourceMap>();
            sourceMap->Init(jsonPage);
            return sourceMap;
        }
    } else {
        if (Framework::GetAssetContentImpl(container->GetAssetManager(), currentPath_ + ".map", jsSourceMap)) {
            auto faPageMap = AceType::MakeRefPtr<Framework::RevSourceMap>();
            faPageMap->Init(jsSourceMap);
            return faPageMap;
        }
    }
    return nullptr;
}

bool AceScopedPerformanceCheck::CheckIsRuleWebsocket(const std::string& ruleType)
{
    if (AceChecker::GetCheckMessge().empty()) {
        return false;
    }

    if (AceChecker::GetCheckMessge().find(ruleType, 0) != std::string::npos) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
