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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_MANAGER_H

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "base/utils/macros.h"
#include "core/components/web/resource/web_page_scene_types.h"

namespace OHOS::Ace {

class JsonValue;

/**
 * Singleton that holds PageScene rules for all Web components.
 *
 * Rules persist across page navigations (delegate instance changes).
 * WebDelegate reads rules from this singleton for matching;
 * results are reported back via OnMatchResult for merging.
 */
class ACE_FORCE_EXPORT WebPageSceneManager {
public:
    static WebPageSceneManager& GetInstance();

    // --- Rule management ---

    /**
     * Register PageScene rules for a process. One processId maps to one rule set.
     * Returns false if processId already registered (reject, not overwrite).
     * Returns true on success.
     */
    int32_t RegisterPageSceneRules(int32_t processId, const std::string& ruleJson);

    /**
     * Unregister PageScene rules for a process.
     * Clears all rules and match states for the given processId.
     */
    int32_t UnregisterPageSceneRules(int32_t processId);

    /**
     * Get the registered rule set for a process (copy-on-read).
     * Returns nullopt if no rules registered for this processId.
     */
    std::optional<WebPageSceneRuleSet> GetPageSceneRules(int32_t processId);

    /**
     * Begin a Get/PageScene query for a process.
     * If rules are already registered with matching ruleSetId, reuse them (no temp register).
     * Otherwise, parse ruleJson and store in pendingGetRules_ for temporary use.
     * Returns PAGE_SCENE_ERR_OK on success, or an error code on failure.
     * On success, ruleSetOut is set to the rules to query against.
     */
    int32_t BeginGetPageScene(int32_t processId, const std::string& ruleJsonOrRuleSetId,
        std::optional<WebPageSceneRuleSet>& ruleSetOut);

    /**
     * Complete a Get/PageScene query for a process.
     * Cleans up pendingGetRules_ and pendingGetProcesses_ for temporary queries.
     */
    void CompleteGetPageScene(int32_t processId);

    /**
     * Update RuleMatchState under lock protection.
     * Called by WebDelegate after ShouldReportEvent check.
     */
    void UpdateRuleState(int32_t processId, int32_t webId, const std::string& ruleId,
        bool matched, int32_t matchedCount, bool reported,
        const std::vector<PageSceneControlInfo>& controls);

    /**
     * Get the processId that has registered rules.
     * Returns -1 if no rules registered.
     */
    int32_t GetRegisteredProcessId();

    // --- Result reporting ---

    /**
     * Report EXIT for all rules that were triggered on the given webId
     * and clear the component's rule states. Called on page navigation
     * to ensure old page's triggered state does not leak into new page.
     */
    void FlushExitOnNavigate(int32_t processId, int32_t webId);

    /**
     * Called by each WebDelegate when a rule match result is ready.
     * Forwards the result directly to UiSessionManager::ReportPageSceneEvent.
     */
    void OnMatchResult(int32_t processId, const std::string& sceneJson, bool isGetResult);

    // --- JSON parsing (migrated from WebDelegate) ---
    std::vector<PageSceneControlInfo> ParseControlsJson(const std::string& resultJson);
    PageSceneControlInfo ParseSingleControlItem(const std::unique_ptr<JsonValue>& item);

    // --- Condition evaluation (migrated from WebDelegate) ---
    bool EvaluateCondition(const PageSceneCondition& condition, int32_t matchedCount);

    // --- Scene type derivation ---
    std::string DeriveSceneType(int32_t processId, int32_t webId,
        const std::string& ruleId, bool matched);

    // --- Reporting decision (migrated from WebDelegate) ---
    bool ShouldReportEvent(int32_t processId, int32_t webId, const std::string& ruleId,
        const std::string& eventName, int32_t matchedCount,
        const std::vector<PageSceneControlInfo>& controls);
    bool IsDuplicatedEvent(const WebRule& rule, int32_t matchedCount,
        const std::vector<PageSceneControlInfo>& controls, const RuleMatchState& ruleState);
    bool IsWithinMinInterval(const WebRule& rule, const RuleMatchState& ruleState);

    // --- JSON building (migrated from WebDelegate) ---
    std::string BuildSelectorJson(const WebRule& rule, const PageSceneGlobalConfig& globalConfig);

    // --- Selector JSON helpers ---
    std::unique_ptr<JsonValue> BuildTypeAttrRulesJson(const PageSceneSelector& selector);

    // --- Query result processing (new unified entry) ---

    /**
     * Core processing: parse, evaluate, update state, return sceneJson strings.
     * Does NOT call OnMatchResult — caller decides when/how to report.
     */
    std::vector<std::string> ProcessQueryResultCore(int32_t processId, int32_t webId,
        const std::string& selectorJson, const std::string& rawResult, bool isGetResult);

    /**
     * Convenience wrapper: ProcessQueryResultCore + immediate OnMatchResult per result.
     * Used for observer callbacks where each result is reported individually.
     */
    void ProcessQueryResult(int32_t processId, int32_t webId,
        const std::string& selectorJson, const std::string& rawResult, bool isGetResult);

private:
    WebPageSceneManager() = default;
    ~WebPageSceneManager() = default;
    WebPageSceneManager(const WebPageSceneManager&) = delete;
    WebPageSceneManager& operator=(const WebPageSceneManager&) = delete;

    bool ParseWebRulesFromRuleJson(const std::string& ruleJson, PageSceneRuleJson& parsed);
    bool ParseWebRuleItem(const std::unique_ptr<JsonValue>& ruleItem, WebRule& rule);
    bool ValidateRuleCondition(const WebRule& rule) const;
    void ParseSelectorFromJson(const std::unique_ptr<JsonValue>& selector, WebRule& rule);
    void ParseTypeAttrRulesFromJson(const std::unique_ptr<JsonValue>& typeAttrRules, WebRule& rule);
    void ParseConditionFromJson(const std::unique_ptr<JsonValue>& condition, WebRule& rule);
    void ParseReportFromJson(const std::unique_ptr<JsonValue>& report, WebRule& rule);
    void ParsePolicyFromJson(const std::unique_ptr<JsonValue>& policy, WebRule& rule);

    std::optional<WebRule> FindRuleById(int32_t processId, const std::string& ruleId);

    // Internal helpers (caller must hold mutex_)
    void ProcessEmptyControlsInner(const std::string& ruleSetId, int32_t processId, int32_t webId,
        const std::string& selectorJson, std::map<int32_t, WebPageSceneRuleSet>& rules,
        std::vector<std::string>& results);
    void ProcessMatchedControlsInner(const std::string& ruleSetId, int32_t processId, int32_t webId,
        const std::string& selectorJson, int32_t matchedCount, bool isGetResult,
        const std::vector<PageSceneControlInfo>& controls,
        std::map<int32_t, WebPageSceneRuleSet>& rules,
        std::vector<std::string>& results);
    std::string DeriveSceneTypeInner(int32_t processId, int32_t webId,
        const std::string& ruleId, bool matched,
        const std::map<int32_t, WebPageSceneRuleSet>& rules);
    bool ShouldReportEventInner(int32_t processId, int32_t webId, const std::string& ruleId,
        const std::string& eventName, int32_t matchedCount,
        const std::vector<PageSceneControlInfo>& controls,
        const std::map<int32_t, WebPageSceneRuleSet>& rules);
    void UpdateRuleStateInner(int32_t processId, int32_t webId, const std::string& ruleId,
        bool matched, int32_t matchedCount, bool reported,
        const std::vector<PageSceneControlInfo>& controls,
        std::map<int32_t, WebPageSceneRuleSet>& rules);
    std::optional<WebRule> FindRuleByIdInner(int32_t processId, const std::string& ruleId,
        const std::map<int32_t, WebPageSceneRuleSet>& rules);
    std::string BuildSceneJsonInner(const std::string& ruleSetId,
        int32_t webId, const WebRule& rule, bool matched, int32_t matchedCount,
        const std::vector<PageSceneControlInfo>& controls, const std::string& eventName);

    std::mutex mutex_;

    // Rule definitions: processId -> ruleSet (one-to-one)
    std::map<int32_t, WebPageSceneRuleSet> registeredRules_;

    // Temporary Get query storage (separate from registered rules)
    std::map<int32_t, WebPageSceneRuleSet> pendingGetRules_;
    std::set<int32_t> pendingGetProcesses_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_PAGE_SCENE_MANAGER_H
