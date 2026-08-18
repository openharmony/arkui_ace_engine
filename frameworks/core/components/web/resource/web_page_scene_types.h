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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_TYPES_H

#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace OHOS::Ace {

// ===== PageScene Rule-Based Perception Data Structures =====

struct PageSceneGlobalConfig {
    bool includeUnfocusableTextInput = false;
};

struct PageSceneTypeAttrRule {
    std::string attr;
    std::vector<std::string> value;
};

struct PageSceneSelector {
    std::vector<std::string> nodeTypes;
    std::map<std::string, std::vector<PageSceneTypeAttrRule>> typeAttrRules;
};

struct PageSceneScope {
    bool onlyVisible = true;
};

// QueryControls JS script error codes
constexpr int32_t PAGE_SCENE_QUERY_SUCCESS = 0;          // Query completed normally
constexpr int32_t PAGE_SCENE_QUERY_EMPTY_SCRIPT = 1;     // Empty/invalid selector script
constexpr int32_t PAGE_SCENE_QUERY_EXCEPTION = 2;        // JS execution exception
constexpr int32_t PAGE_SCENE_QUERY_DOM_PENDING = 3;      // DOM not ready (readyState=loading)

// MutationObserver timing constants (milliseconds)
constexpr int32_t PAGE_SCENE_DOM_READY_DELAY_MS = 100;   // Delay after DOMContentLoaded before notifying
constexpr int32_t PAGE_SCENE_OBSERVER_DEBOUNCE_MS = 500; // Debounce interval for MutationObserver
constexpr int32_t PAGE_SCENE_OBSERVER_TIMEOUT_MS = 5000; // Auto-disconnect timeout for MutationObserver

// Policy defaults (aligned with ArkUI PageSceneRuleManager)
constexpr int32_t PAGE_SCENE_DEFAULT_MIN_REPORT_INTERVAL_MS = 500;
constexpr int32_t PAGE_SCENE_DEFAULT_THRESHOLD = 0;

// Error codes (aligned with ui_content_errors.h ErrorCode)
constexpr int32_t PAGE_SCENE_ERR_OK = 0;
constexpr int32_t PAGE_SCENE_ERR_NOT_CONNECTED = 1;
constexpr int32_t PAGE_SCENE_ERR_FAILED = 2;
constexpr int32_t PAGE_SCENE_ERR_PARAM_INVALID = 4;
constexpr int32_t PAGE_SCENE_ERR_LAST_UNFINISH = 5;

struct PageSceneCondition {
    std::string conditionOperator;  // "COUNT_GTE"
    int32_t threshold = 0;
};

struct PageSceneReport {
    std::string eventName;
    bool includeNodeIds = true;
    bool includeNodeTypes = true;
    bool includeRect = true;
    bool includeFocusable = true;
    bool includeText = false;
    bool includeEditable = false;
    bool includeAutocomplete = true;
    bool includeXpath = true;
};

struct PageScenePolicy {
    bool reportOnRegister = true;
    int32_t minReportIntervalMs = PAGE_SCENE_DEFAULT_MIN_REPORT_INTERVAL_MS;
    bool deduplicate = true;
};

struct WebRule {
    std::string ruleId;
    std::string sceneType;
    bool enabled = true;
    PageSceneScope scope;
    PageSceneSelector selector;
    PageSceneCondition condition;
    PageSceneReport report;
    PageScenePolicy policy;
};

struct PageSceneRuleJson {
    std::string ruleSetId;
    PageSceneGlobalConfig globalConfig;
    std::vector<WebRule> webRules;
};

struct RuleMatchState {
    bool textEditorTriggered = false;
    int64_t lastReportTimeMs = 0;
    std::set<int32_t> lastMatchedNodeIds;
    int32_t lastMatchedCount = 0;
};

// ArkWeb-side rule set (distinct from baseline PageSceneRuleSet used by ArkUI host)
struct WebPageSceneRuleSet {
    std::string ruleSetId;
    PageSceneGlobalConfig globalConfig;
    std::vector<WebRule> rules;
    // Per-component rule states: webId -> (ruleId -> match state)
    // Each Web component maintains its own triggered state independently,
    // so one component's EXIT doesn't overwrite another's active state.
    std::map<int32_t, std::map<std::string, RuleMatchState>> componentRuleStates;
};

struct PageSceneControlInfo {
    int32_t nodeId = 0;
    std::string nodeType;
    bool focusable = false;
    bool editable = false;
    float rectX = 0.0f;
    float rectY = 0.0f;
    float rectWidth = 0.0f;
    float rectHeight = 0.0f;
    std::string text;
    std::string autocomplete;
    std::string xpath;
};

// Callback type for page scene query results.
// WebDelegate calls this when JS query returns raw results.
// Parameters: webId, selectorJson, rawResult
using PageSceneQueryCallback = std::function<void(int32_t, const std::string&, const std::string&)>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_TYPES_H
