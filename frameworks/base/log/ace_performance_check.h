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
#include "base/utils/system_properties.h"

namespace OHOS::Ace {
// define marco
#define PERFORMANCE_CHECK_FUNCTION_TIMEOUT(functionName) AceScopedPerformanceCheck scoped(functionName);
#define PERFORMANCE_CHECK_NODE_COUNT_AND_DEPTH(count, depth, nodeMap) \
    AceScopedPerformanceCheck::RecordPageNodeCountAndDepth(count, depth, nodeMap);
#define PERFORMANCE_CHECK_FOR_EACH_ITEMS_COUNT(itemMap) AceScopedPerformanceCheck::RecordForEachItemsCount(itemMap)
#define PERFORMANCE_CHECK_FLEX_CHILDREN_LAYOUTS(itemMap) AceScopedPerformanceCheck::RecordFlexLayoutsCount(itemMap);
#define CHECK_PERFORMANCE_CHECK_ENABLED()                 \
    if (!SystemProperties::IsPerformanceCheckEnabled()) { \
        return;                                           \
    }

struct CodeInfo {
    int32_t row;
    int32_t col;
    std::string sources;
};

struct NodeTimeoutInfo {
    int32_t row;
    int64_t sec;
    std::string tag;
};

struct CheckNodeInfo {
    int32_t row {};
    int32_t col {};
    std::string tag;

    bool operator==(const OHOS::Ace::CheckNodeInfo& other) const
    {
        return other.row == row && other.col == col && other.tag == tag;
    }
};

struct CheckHashFunc {
    size_t operator()(const CheckNodeInfo& info) const
    {
        size_t h1 = std::hash<int32_t> {}(info.row);
        size_t h2 = std::hash<int32_t> {}(info.col);
        size_t h3 = std::hash<std::string> {}(info.tag);
        return h1 ^ (h2 << 1) ^ (h3 << 1);
    }
};

using CheckNodeMap = std::unordered_map<CheckNodeInfo, int32_t, CheckHashFunc>;

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
    explicit AceScopedPerformanceCheck(const std::string& name = "");
    ~AceScopedPerformanceCheck();

    static void RecordPageNodeCountAndDepth(int32_t pageNodeCount, int32_t pageDepth, const CheckNodeMap& nodeMap);
    static void RecordForEachItemsCount(const CheckNodeMap& itemMap);
    static void RecordFlexLayoutsCount(const CheckNodeMap& itemMap);
    void InsertNodeTimeout(int64_t sec, int32_t row, int32_t col, const std::string& tag);

private:
    static std::string GetEventTime();
    static CodeInfo GetCodeInfo(int32_t row, int32_t col);
    static int32_t GetSourceLine(int32_t row, int32_t col);
    static bool CheckIsRuleContainsPage(const std::string& ruleType, const std::string& pagePath);
    static void RecordFunctionTimeout(int64_t sec, const std::string& functionName);
    static int32_t GetItemMapSize(const CheckNodeMap& itemMap);
    void RecordVsyncTimeout(int64_t sec);

    int64_t markTime_ = 0;
    std::string functionName_;
    std::string typeName_;
    std::vector<NodeTimeoutInfo> nodeList_;

    ACE_DISALLOW_COPY_AND_MOVE(AceScopedPerformanceCheck);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H
