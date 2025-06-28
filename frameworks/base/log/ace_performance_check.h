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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/json/json_util.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "bridge/common/utils/source_map.h"

namespace OHOS::Ace {
struct PerformanceCheckNode {
    int32_t pageDepth = 0;      // node depth
    int32_t childrenSize = 0;   // node children size
    int32_t codeRow = 0;        // js code row
    int32_t codeCol = 0;        // js code col
    int64_t layoutTime = 0;     // node layout time
    int32_t flexLayouts = 0;    // node flex layout times
    bool isForEachItem = false; // foreach item
    int32_t foreachItems = 0;   // foreach item count
    std::string nodeTag;        // node tag
    std::string pagePath;       // page path
};

struct CodeInfo {
    int32_t row = 0;     // ets code row
    int32_t col = 0;     // ets code col
    std::string sources; // ets page
};

using PerformanceCheckNodeMap = std::unordered_map<int32_t, PerformanceCheckNode>;

class ACE_EXPORT AcePerformanceCheck final {
public:
    static void Start();
    static void Stop();

private:
    AcePerformanceCheck() = default;
    ~AcePerformanceCheck() = default;

    static std::unique_ptr<JsonValue> performanceInfo_;

    friend class AceScopedPerformanceCheck;
    ACE_DISALLOW_COPY_AND_MOVE(AcePerformanceCheck);
};

class ACE_EXPORT AceScopedPerformanceCheck final {
public:
    explicit AceScopedPerformanceCheck(const std::string& name);
    ~AceScopedPerformanceCheck();

    static CodeInfo GetCodeInfo(int32_t row, int32_t col);
    static void RecordPerformanceCheckData(const PerformanceCheckNodeMap& nodeMap, int64_t vsyncTimeout,
        std::string path, std::string fromPath = "", std::string moduleName = "", bool isNavgation = false);

private:
    static std::string GetCurrentTime();
    static bool CheckIsRuleContainsPage(const std::string& ruleType, const std::string& pagePath);
    static void RecordPageNodeCountAndDepth(int32_t pageNodeCount, int32_t pageDepth,
        std::vector<PerformanceCheckNode>& pageNodeList, const CodeInfo& info, const std::string& pageRoute);
    static void RecordForEachItemsCount(
    int32_t count, std::unordered_map<int32_t, PerformanceCheckNode>& foreachNodeMap,
    const CodeInfo& info, const std::string& pageRoute);
    static void RecordFlexLayoutsCount(
        const std::vector<PerformanceCheckNode>& nodeList, const CodeInfo& info, const std::string& pageRoute);
    static void RecordVsyncTimeout(
    const PerformanceCheckNodeMap& nodeMap, int64_t vsyncTimeout,
    const CodeInfo& info, const std::string& pageRoute);
    static bool CheckPage(const CodeInfo& codeInfo, const std::string& rule);
    static void RecordFunctionTimeout();
    static RefPtr<Framework::RevSourceMap> GetCurrentSourceMap();
    static bool CheckIsRuleWebsocket(const std::string& ruleType);
    int64_t markTime_ = 0;
    std::string name_;
    std::string pagePath_;
    static std::string currentPath_;
    static std::vector<std::pair<int64_t, std::string>> records_;
    ACE_DISALLOW_COPY_AND_MOVE(AceScopedPerformanceCheck);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H
