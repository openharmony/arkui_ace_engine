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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PAGE_SCENE_PAGE_SCENE_RULE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PAGE_SCENE_PAGE_SCENE_RULE_MANAGER_H

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace {
class JsonValue;
}

namespace OHOS::Ace::NG {
class FrameNode;
class UINode;

struct PageSceneRectInfo {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};

struct PageSceneNodeInfo {
    int32_t nodeId = -1;
    std::string nodeType;
    std::string text;
    bool focusable = false;
    PageSceneRectInfo rect;
};

struct PageSceneRule {
    std::string ruleId;
    std::string sceneType;
    bool enabled = true;
    bool onlyVisible = true;
    bool includeWeb = false;
    bool includeUIExtension = false;
    bool includeNodeIds = true;
    bool includeNodeTypes = true;
    bool includeRect = true;
    bool includeFocusable = true;
    bool includeText = false;
    bool reportOnRegister = true;
    bool deduplicate = true;
    int32_t minReportIntervalMs = 500;
    int32_t threshold = 2;
    std::set<std::string> nodeTypes;
};

struct PageSceneRuleSet {
    int32_t version = 1;
    std::string ruleSetId;
    std::string rawJson;
    std::string webRulesRaw;
    bool includeUnfocusableTextInput = false;
    bool arkuiEnabled = true;
    bool webEnabled = false;
    bool uiExtensionEnabled = false;
    std::vector<PageSceneRule> rules;
};

struct PageSceneMatchResult {
    std::string ruleSetId;
    std::string ruleId;
    std::string sceneType;
    std::string eventName;
    std::string pageName;
    bool matched = false;
    int32_t matchedCount = 0;
    int32_t minReportIntervalMs = 500;
    bool deduplicate = true;
    std::vector<int32_t> nodeIds;
    std::string sceneJson;
};

struct PageSceneReportState {
    std::vector<int32_t> lastReportedNodeIds;
    std::chrono::steady_clock::time_point lastReportTime;
};

class PageSceneInputCountTracker {
public:
    void Initialize(const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<FrameNode>& pageRoot);
    void Reset();
    const std::vector<PageSceneNodeInfo>& GetVisibleInputNodes() const;

private:
    void CollectInputNodes(const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<UINode>& node);
    std::optional<PageSceneNodeInfo> BuildNodeInfo(
        const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<FrameNode>& node) const;

    std::vector<PageSceneNodeInfo> visibleInputNodes_;
    RectF pageViewportRect_;
};

class PageSceneRuleManager {
public:
    int32_t RegisterRuleSet(int32_t processId, const std::string& ruleJson);
    int32_t UnregisterRuleSet(int32_t processId, const std::string& ruleSetId);
    int32_t BeginGetPageScene(int32_t processId, const std::string& ruleJsonOrRuleSetId, std::string& ruleJson);
    void CompleteGetPageScene(int32_t processId);
    void ClearProcess(int32_t processId);

    std::vector<std::pair<int32_t, std::string>> GetActiveRuleJsons() const;
    std::optional<PageSceneMatchResult> MatchPageScene(
        int32_t processId, const std::string& ruleJson, const RefPtr<FrameNode>& pageRoot,
        const std::string& pageName, bool forceReportUnmatched);
    bool ShouldReport(int32_t processId, const PageSceneMatchResult& result);
    bool IsTextInputNodeType(const std::string& nodeType) const;

private:
    std::optional<PageSceneRuleSet> ParseRuleSet(const std::string& ruleJson) const;
    std::optional<PageSceneRule> ParseRule(const std::unique_ptr<JsonValue>& ruleJson) const;
    std::string BuildSceneJson(const PageSceneRuleSet& ruleSet, const PageSceneRule& rule,
        const std::string& pageName, const std::vector<PageSceneNodeInfo>& nodes, bool matched,
        const std::string& eventName) const;

    mutable std::mutex mutex_;
    std::unordered_map<int32_t, PageSceneRuleSet> registeredRuleSets_;
    std::set<int32_t> pendingGetProcesses_;
    std::unordered_map<std::string, PageSceneReportState> reportStates_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_PAGE_SCENE_PAGE_SCENE_RULE_MANAGER_H
