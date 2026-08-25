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

#include "core/components/web/resource/web_page_scene_manager.h"

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace {

namespace {
PageSceneTypeAttrRule ParseSingleTypeAttrRule(const std::unique_ptr<JsonValue>& attrItem)
{
    PageSceneTypeAttrRule tar;
    tar.attr = attrItem->GetString("attr");
    auto values = attrItem->GetValue("value");
    if (values && values->IsArray()) {
        for (int32_t m = 0; m < values->GetArraySize(); ++m) {
            auto v = values->GetArrayItem(m);
            if (v && v->IsString()) {
                tar.value.emplace_back(v->GetString());
            }
        }
    }
    return tar;
}
} // namespace

WebPageSceneManager& WebPageSceneManager::GetInstance()
{
    static WebPageSceneManager instance;
    return instance;
}

// ===== Rule management =====

void WebPageSceneManager::ParseTypeAttrRulesFromJson(const std::unique_ptr<JsonValue>& typeAttrRules, WebRule& rule)
{
    int32_t size = typeAttrRules->GetArraySize();
    auto child = typeAttrRules->GetChild();
    for (int32_t i = 0; i < size && child && child->IsValid(); ++i) {
        std::string nodeType = child->GetKey();
        if (nodeType.empty() || !child->IsArray()) {
            child = child->GetNext();
            continue;
        }
        std::vector<PageSceneTypeAttrRule> rules;
        for (int32_t k = 0; k < child->GetArraySize(); ++k) {
            auto attrItem = child->GetArrayItem(k);
            if (!attrItem || !attrItem->IsObject()) {
                continue;
            }
            auto tar = ParseSingleTypeAttrRule(attrItem);
            rules.emplace_back(std::move(tar));
        }
        rule.selector.typeAttrRules[nodeType] = std::move(rules);
        child = child->GetNext();
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "ParseTypeAttrRules: total=%{public}zu nodeTypes, ruleId=%{public}s",
        rule.selector.typeAttrRules.size(), rule.ruleId.c_str());
}

void WebPageSceneManager::ParseSelectorFromJson(const std::unique_ptr<JsonValue>& selector, WebRule& rule)
{
    auto nodeTypes = selector->GetValue("nodeTypes");
    if (nodeTypes && nodeTypes->IsArray()) {
        for (int32_t j = 0; j < nodeTypes->GetArraySize(); ++j) {
            auto item = nodeTypes->GetArrayItem(j);
            if (item && item->IsString()) {
                rule.selector.nodeTypes.emplace_back(item->GetString());
            }
        }
    }
    auto typeAttrRules = selector->GetValue("typeAttrRules");
    if (typeAttrRules && typeAttrRules->IsObject()) {
        ParseTypeAttrRulesFromJson(typeAttrRules, rule);
    }
}

void WebPageSceneManager::ParseConditionFromJson(const std::unique_ptr<JsonValue>& condition, WebRule& rule)
{
    rule.condition.conditionOperator = condition->GetString("operator");
    rule.condition.threshold = condition->GetInt("threshold", PAGE_SCENE_DEFAULT_THRESHOLD);
}

void WebPageSceneManager::ParseReportFromJson(
    const std::unique_ptr<JsonValue>& report, WebRule& rule)
{
    rule.report.eventName = report->GetString("eventName");
    rule.report.includeNodeIds = report->GetBool("includeNodeIds", true);
    rule.report.includeNodeTypes = report->GetBool("includeNodeTypes", true);
    rule.report.includeRect = report->GetBool("includeRect", true);
    rule.report.includeFocusable = report->GetBool("includeFocusable", true);
    rule.report.includeText = report->GetBool("includeText", false);
    rule.report.includeEditable = report->GetBool("includeEditable", false);
    rule.report.includeAutocomplete = report->GetBool("includeAutocomplete", true);
    rule.report.includeXpath = report->GetBool("includeXpath", true);
}

void WebPageSceneManager::ParsePolicyFromJson(
    const std::unique_ptr<JsonValue>& policy, WebRule& rule)
{
    rule.policy.reportOnRegister = policy->GetBool("reportOnRegister", true);
    rule.policy.minReportIntervalMs = policy->GetInt("minReportIntervalMs", PAGE_SCENE_DEFAULT_MIN_REPORT_INTERVAL_MS);
    if (rule.policy.minReportIntervalMs < 0) {
        rule.policy.minReportIntervalMs = PAGE_SCENE_DEFAULT_MIN_REPORT_INTERVAL_MS;
    }
    rule.policy.deduplicate = policy->GetBool("deduplicate", true);
}

bool WebPageSceneManager::ValidateRuleCondition(const WebRule& rule) const
{
    if (rule.condition.conditionOperator != "COUNT_GTE") {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "ValidateRuleCondition: unsupported operator=%{public}s, ruleId=%{public}s",
            rule.condition.conditionOperator.c_str(), rule.ruleId.c_str());
        return false;
    }
    if (rule.condition.threshold <= 0) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "ValidateRuleCondition: threshold=%{public}d must be positive, ruleId=%{public}s",
            rule.condition.threshold, rule.ruleId.c_str());
        return false;
    }
    return true;
}

bool WebPageSceneManager::ParseWebRuleItem(const std::unique_ptr<JsonValue>& ruleItem, WebRule& rule)
{
    rule.ruleId = ruleItem->GetString("ruleId");
    if (rule.ruleId.empty()) {
        return false;
    }
    rule.sceneType = ruleItem->GetString("sceneType");
    if (rule.sceneType != "TEXT_EDITOR") {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "WebPageSceneManager::ParseWebRuleItem: unsupported sceneType=%{public}s, ruleId=%{public}s",
            rule.sceneType.c_str(), rule.ruleId.c_str());
        return false;
    }
    rule.enabled = ruleItem->GetBool("enabled", true);

    auto scope = ruleItem->GetValue("scope");
    if (scope && scope->IsObject()) {
        rule.scope.onlyVisible = scope->GetBool("onlyVisible", true);
    }

    auto selector = ruleItem->GetValue("selector");
    if (selector && selector->IsObject()) {
        ParseSelectorFromJson(selector, rule);
    }
    if (rule.selector.nodeTypes.empty()) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "ParseWebRuleItem: selector.nodeTypes is missing or empty, ruleId=%{public}s",
            rule.ruleId.c_str());
        return false;
    }

    auto condition = ruleItem->GetValue("condition");
    if (!condition || !condition->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "ParseWebRuleItem: condition is missing or invalid, ruleId=%{public}s",
            rule.ruleId.c_str());
        return false;
    }
    ParseConditionFromJson(condition, rule);
    if (!ValidateRuleCondition(rule)) {
        return false;
    }

    auto report = ruleItem->GetValue("report");
    if (report && report->IsObject()) {
        ParseReportFromJson(report, rule);
    }

    auto policy = ruleItem->GetValue("policy");
    if (policy && policy->IsObject()) {
        ParsePolicyFromJson(policy, rule);
    }
    return true;
}

bool WebPageSceneManager::ParseWebRulesFromRuleJson(
    const std::string& ruleJson, PageSceneRuleJson& parsed)
{
    auto root = JsonUtil::ParseJsonString(ruleJson);
    if (!root || !root->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: invalid ruleJson");
        return false;
    }

    parsed.ruleSetId = root->GetString("ruleSetId");
    if (parsed.ruleSetId.empty()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: ruleSetId is empty");
        return false;
    }

    auto sourceConfig = root->GetValue("sourceConfig");
    if (sourceConfig && sourceConfig->IsObject()) {
        bool webEnabled = sourceConfig->GetBool("web", false);
        if (!webEnabled) {
            TAG_LOGW(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: sourceConfig.web=false, skip");
            return false;
        }
    }

    auto globalConfig = root->GetValue("globalConfig");
    if (globalConfig && globalConfig->IsObject()) {
        parsed.globalConfig.includeUnfocusableTextInput =
            globalConfig->GetBool("includeUnfocusableTextInput", false);
    }

    auto webRules = root->GetValue("webRules");
    if (!webRules || !webRules->IsArray() || webRules->GetArraySize() == 0) {
        TAG_LOGW(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: webRules is missing or empty");
        return false;
    }

    for (int32_t i = 0; i < webRules->GetArraySize(); ++i) {
        auto ruleItem = webRules->GetArrayItem(i);
        if (!ruleItem || !ruleItem->IsObject()) {
            TAG_LOGD(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: webRules[%{public}d] is not a valid object", i);
            continue;
        }
        WebRule rule;
        if (ParseWebRuleItem(ruleItem, rule)) {
            parsed.webRules.emplace_back(std::move(rule));
        } else {
            TAG_LOGD(AceLogTag::ACE_WEB, "ParseWebRulesFromRuleJson: webRules[%{public}d] parse failed, skipped", i);
        }
    }

    return !parsed.webRules.empty();
}

int32_t WebPageSceneManager::RegisterPageSceneRules(int32_t processId, const std::string& ruleJson)
{
    PageSceneRuleJson parsed;
    if (!ParseWebRulesFromRuleJson(ruleJson, parsed)) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "RegisterPageSceneRules: parse failed, processId=%{public}d", processId);
        return PAGE_SCENE_ERR_PARAM_INVALID;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    // One processId maps to one rule set: reject if already registered
    if (registeredRules_.find(processId) != registeredRules_.end()) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "RegisterPageSceneRules: processId %{public}d already registered, reject", processId);
        return PAGE_SCENE_ERR_LAST_UNFINISH;
    }

    WebPageSceneRuleSet ruleSet;
    ruleSet.ruleSetId = parsed.ruleSetId;
    ruleSet.globalConfig = parsed.globalConfig;
    for (const auto& rule : parsed.webRules) {
        ruleSet.rules.emplace_back(rule);
    }
    registeredRules_[processId] = std::move(ruleSet);

    TAG_LOGI(AceLogTag::ACE_WEB,
        "RegisterPageSceneRules: processId=%{public}d ruleSetId=%{public}s rules=%{public}zu",
        processId, parsed.ruleSetId.c_str(), parsed.webRules.size());
    return PAGE_SCENE_ERR_OK;
}

int32_t WebPageSceneManager::UnregisterPageSceneRules(int32_t processId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (registeredRules_.find(processId) == registeredRules_.end()) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "UnregisterPageSceneRules: not registered, processId=%{public}d", processId);
        return PAGE_SCENE_ERR_PARAM_INVALID;
    }
    registeredRules_.erase(processId);
    TAG_LOGI(AceLogTag::ACE_WEB, "UnregisterPageSceneRules: processId=%{public}d", processId);
    return PAGE_SCENE_ERR_OK;
}

std::optional<WebPageSceneRuleSet> WebPageSceneManager::GetPageSceneRules(int32_t processId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = registeredRules_.find(processId);
    if (it != registeredRules_.end()) {
        return it->second;
    }
    return std::nullopt;
}

int32_t WebPageSceneManager::BeginGetPageScene(int32_t processId,
    const std::string& ruleJsonOrRuleSetId, std::optional<WebPageSceneRuleSet>& ruleSetOut)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pendingGetProcesses_.find(processId) != pendingGetProcesses_.end()) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "BeginGetPageScene: already has in-flight get, processId=%{public}d", processId);
        return PAGE_SCENE_ERR_LAST_UNFINISH;
    }
    // Check if already registered with matching ruleSetId — reuse
    auto regIt = registeredRules_.find(processId);
    if (regIt != registeredRules_.end()) {
        ruleSetOut = regIt->second;
        pendingGetProcesses_.insert(processId);
        return PAGE_SCENE_ERR_OK;
    }
    // No registered rules — parse and store temporarily
    PageSceneRuleJson parsed;
    if (!ParseWebRulesFromRuleJson(ruleJsonOrRuleSetId, parsed)) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "BeginGetPageScene: parse failed, processId=%{public}d", processId);
        return PAGE_SCENE_ERR_PARAM_INVALID;
    }
    WebPageSceneRuleSet ruleSet;
    ruleSet.ruleSetId = parsed.ruleSetId;
    ruleSet.globalConfig = parsed.globalConfig;
    for (const auto& rule : parsed.webRules) {
        ruleSet.rules.emplace_back(rule);
    }
    pendingGetRules_[processId] = ruleSet;
    ruleSetOut = ruleSet;
    pendingGetProcesses_.insert(processId);
    return PAGE_SCENE_ERR_OK;
}

void WebPageSceneManager::CompleteGetPageScene(int32_t processId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    pendingGetRules_.erase(processId);
    pendingGetProcesses_.erase(processId);
}

namespace {
std::set<int32_t> CollectNodeIds(const std::vector<PageSceneControlInfo>& controls)
{
    std::set<int32_t> ids;
    for (const auto& c : controls) {
        ids.insert(c.nodeId);
    }
    return ids;
}
} // namespace

void WebPageSceneManager::UpdateRuleState(int32_t processId, int32_t webId,
    const std::string& ruleId, bool matched, int32_t matchedCount, bool reported,
    const std::vector<PageSceneControlInfo>& controls)
{
    std::lock_guard<std::mutex> lock(mutex_);
    UpdateRuleStateInner(processId, webId, ruleId, matched, matchedCount, reported, controls, registeredRules_);
}

void WebPageSceneManager::UpdateRuleStateInner(int32_t processId, int32_t webId,
    const std::string& ruleId, bool matched, int32_t matchedCount, bool reported,
    const std::vector<PageSceneControlInfo>& controls,
    std::map<int32_t, WebPageSceneRuleSet>& rules)
{
    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return;
    }
    auto& ruleState = procIt->second.componentRuleStates[webId][ruleId];
    auto currentIds = CollectNodeIds(controls);

    if (!matched && !ruleState.textEditorTriggered) {
        ruleState.lastMatchedNodeIds = std::move(currentIds);
        ruleState.lastMatchedCount = matchedCount;
        return;
    }

    ruleState.textEditorTriggered = matched;
    if (reported) {
        ruleState.lastReportTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    ruleState.lastMatchedNodeIds = std::move(currentIds);
    ruleState.lastMatchedCount = matchedCount;
}

int32_t WebPageSceneManager::GetRegisteredProcessId()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!registeredRules_.empty()) {
        return registeredRules_.begin()->first;
    }
    return -1;
}

// ===== Result reporting =====

void WebPageSceneManager::FlushExitOnNavigate(int32_t processId, int32_t webId)
{
    // Collect EXIT results outside the lock
    std::vector<std::string> exitResults;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto procIt = registeredRules_.find(processId);
        if (procIt == registeredRules_.end()) {
            TAG_LOGI(AceLogTag::ACE_WEB, "FlushExitOnNavigate: processId=%{public}d not found", processId);
            return;
        }
        const std::string& ruleSetId = procIt->second.ruleSetId;
        auto compIt = procIt->second.componentRuleStates.find(webId);
        if (compIt == procIt->second.componentRuleStates.end()) {
            TAG_LOGI(AceLogTag::ACE_WEB, "FlushExitOnNavigate: webId=%{public}d no rule states", webId);
            return;
        }
        for (auto& [ruleId, state] : compIt->second) {
            if (!state.textEditorTriggered) {
                continue;
            }
            auto ruleOpt = FindRuleByIdInner(processId, ruleId, registeredRules_);
            if (!ruleOpt.has_value()) {
                TAG_LOGW(AceLogTag::ACE_WEB,
                    "FlushExitOnNavigate: ruleId=%{public}s not found in rules", ruleId.c_str());
                continue;
            }
            auto sceneJson = BuildSceneJsonInner(ruleSetId, webId, ruleOpt.value(), false, 0, {}, "TEXT_EDITOR_EXIT");
            TAG_LOGI(AceLogTag::ACE_WEB,
                "FlushExitOnNavigate: processId=%{public}d webId=%{public}d ruleId=%{public}s EXIT",
                processId, webId, ruleId.c_str());
            exitResults.push_back(std::move(sceneJson));
            state.textEditorTriggered = false;
            state.lastMatchedCount = 0;
            state.lastMatchedNodeIds.clear();
        }
        procIt->second.componentRuleStates.erase(webId);
    }
    // Report outside lock — per-rule reporting
    if (exitResults.empty()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "FlushExitOnNavigate: no EXIT results to report");
    }
    for (auto& sceneJson : exitResults) {
        OnMatchResult(processId, std::move(sceneJson), false);
    }
}

void WebPageSceneManager::OnMatchResult(int32_t processId, const std::string& sceneJson, bool isGetResult)
{
    if (sceneJson.empty()) {
        TAG_LOGI(AceLogTag::ACE_WEB,
            "PageSceneReport: OnMatchResult EMPTY processId=%{public}d isGetResult=%{public}d",
            processId, isGetResult);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB,
        "PageSceneReport: OnMatchResult SUCCESS processId=%{public}d isGetResult=%{public}d "
        "sceneJson len=%{public}zu sceneJson=%{public}s",
        processId, isGetResult, sceneJson.size(), sceneJson.c_str());
    UiSessionManager::GetInstance()->ReportPageSceneEvent(processId, sceneJson, isGetResult);
}

// ===== JSON parsing (migrated from WebDelegate) =====

PageSceneControlInfo WebPageSceneManager::ParseSingleControlItem(const std::unique_ptr<JsonValue>& item)
{
    PageSceneControlInfo info;
    info.nodeId = item->GetInt("nodeId", 0);
    info.nodeType = item->GetString("nodeType");
    info.focusable = item->GetBool("focusable", false);
    info.editable = item->GetBool("editable", false);
    info.text = item->GetString("text");
    info.autocomplete = item->GetString("autocomplete");
    info.xpath = item->GetString("xpath");

    auto rect = item->GetValue("rect");
    if (rect && rect->IsObject()) {
        info.rectX = static_cast<float>(rect->GetDouble("x", 0.0));
        info.rectY = static_cast<float>(rect->GetDouble("y", 0.0));
        info.rectWidth = static_cast<float>(rect->GetDouble("width", 0.0));
        info.rectHeight = static_cast<float>(rect->GetDouble("height", 0.0));
    }
    return info;
}

std::vector<PageSceneControlInfo> WebPageSceneManager::ParseControlsJson(const std::string& resultJson)
{
    std::vector<PageSceneControlInfo> controls;
    auto root = JsonUtil::ParseJsonString(resultJson);
    if (root && !root->IsObject() && root->IsString()) {
        root = JsonUtil::ParseJsonString(root->GetString());
    }
    if (!root || !root->IsObject()) {
        return controls;
    }

    int32_t errorCode = root->GetInt("errorCode", -1);
    if (errorCode != 0) {
        return controls;
    }

    auto controlsArr = root->GetValue("controls");
    if (!controlsArr || !controlsArr->IsArray()) {
        return controls;
    }

    for (int32_t i = 0; i < controlsArr->GetArraySize(); ++i) {
        auto item = controlsArr->GetArrayItem(i);
        if (!item || !item->IsObject()) {
            continue;
        }
        controls.emplace_back(ParseSingleControlItem(item));
    }
    return controls;
}

// ===== Condition evaluation =====

bool WebPageSceneManager::EvaluateCondition(const PageSceneCondition& condition, int32_t matchedCount)
{
    if (condition.conditionOperator == "COUNT_GTE") {
        return matchedCount >= condition.threshold;
    }
    return false;
}

// ===== Scene type derivation =====

std::string WebPageSceneManager::DeriveSceneType(
    int32_t processId, int32_t webId, const std::string& ruleId, bool matched)
{
    std::lock_guard<std::mutex> lock(mutex_);
    return DeriveSceneTypeInner(processId, webId, ruleId, matched, registeredRules_);
}

std::string WebPageSceneManager::DeriveSceneTypeInner(int32_t processId, int32_t webId,
    const std::string& ruleId, bool matched, const std::map<int32_t, WebPageSceneRuleSet>& rules)
{
    if (matched) {
        return "TEXT_EDITOR";
    }
    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return "";
    }
    auto compIt = procIt->second.componentRuleStates.find(webId);
    if (compIt == procIt->second.componentRuleStates.end()) {
        return "";
    }
    auto stateIt = compIt->second.find(ruleId);
    if (stateIt != compIt->second.end() && stateIt->second.textEditorTriggered) {
        return "TEXT_EDITOR_EXIT";
    }
    return "";
}

// ===== Reporting decision =====

std::optional<WebRule> WebPageSceneManager::FindRuleById(int32_t processId, const std::string& ruleId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    return FindRuleByIdInner(processId, ruleId, registeredRules_);
}

std::optional<WebRule> WebPageSceneManager::FindRuleByIdInner(int32_t processId,
    const std::string& ruleId, const std::map<int32_t, WebPageSceneRuleSet>& rules)
{
    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return std::nullopt;
    }
    for (const auto& r : procIt->second.rules) {
        if (r.ruleId == ruleId) {
            return r;
        }
    }
    return std::nullopt;
}

bool WebPageSceneManager::IsDuplicatedEvent(const WebRule& rule, int32_t matchedCount,
    const std::vector<PageSceneControlInfo>& controls, const RuleMatchState& ruleState)
{
    if (!rule.policy.deduplicate) {
        return false;
    }
    std::set<int32_t> currentMatchedIds;
    for (const auto& c : controls) {
        currentMatchedIds.insert(c.nodeId);
    }
    if (currentMatchedIds == ruleState.lastMatchedNodeIds &&
        matchedCount == ruleState.lastMatchedCount) {
        return true;
    }
    return false;
}

bool WebPageSceneManager::IsWithinMinInterval(const WebRule& rule, const RuleMatchState& ruleState)
{
    if (rule.policy.minReportIntervalMs <= 0 || ruleState.lastReportTimeMs <= 0) {
        return false;
    }
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    if (now - ruleState.lastReportTimeMs < rule.policy.minReportIntervalMs) {
        return true;
    }
    return false;
}

bool WebPageSceneManager::ShouldReportEvent(int32_t processId, int32_t webId,
    const std::string& ruleId, const std::string& eventName,
    int32_t matchedCount, const std::vector<PageSceneControlInfo>& controls)
{
    std::lock_guard<std::mutex> lock(mutex_);
    return ShouldReportEventInner(processId, webId, ruleId, eventName, matchedCount, controls, registeredRules_);
}

bool WebPageSceneManager::ShouldReportEventInner(int32_t processId, int32_t webId,
    const std::string& ruleId, const std::string& eventName,
    int32_t matchedCount, const std::vector<PageSceneControlInfo>& controls,
    const std::map<int32_t, WebPageSceneRuleSet>& rules)
{
    auto ruleOpt = FindRuleByIdInner(processId, ruleId, rules);
    if (!ruleOpt) {
        return false;
    }

    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return false;
    }
    auto compIt = procIt->second.componentRuleStates.find(webId);
    if (compIt == procIt->second.componentRuleStates.end()) {
        return true;
    }
    auto stateIt = compIt->second.find(ruleId);
    if (stateIt == compIt->second.end()) {
        return true;
    }
    const auto& ruleState = stateIt->second;

    if (eventName == "TEXT_EDITOR_EXIT" && !ruleState.textEditorTriggered) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPageSceneManager::ShouldReportEvent: filtered by EXIT without prior trigger, "
            "processId=%{public}d webId=%{public}d", processId, webId);
        return false;
    }
    if (IsDuplicatedEvent(*ruleOpt, matchedCount, controls, ruleState)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPageSceneManager::ShouldReportEvent: filtered by deduplicate, "
            "processId=%{public}d webId=%{public}d ruleId=%{public}s eventName=%{public}s "
            "matchedCount=%{public}d lastMatchedCount=%{public}d", processId, webId, ruleId.c_str(), eventName.c_str(),
            matchedCount, ruleState.lastMatchedCount);
        return false;
    }
    if (IsWithinMinInterval(*ruleOpt, ruleState)) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebPageSceneManager::ShouldReportEvent: filtered by minReportInterval, "
            "processId=%{public}d webId=%{public}d ruleId=%{public}s eventName=%{public}s minInterval=%{public}dms",
            processId, webId, ruleId.c_str(), eventName.c_str(), ruleOpt->policy.minReportIntervalMs);
        return false;
    }
    return true;
}

// ===== JSON building =====

std::unique_ptr<JsonValue> WebPageSceneManager::BuildTypeAttrRulesJson(const PageSceneSelector& selector)
{
    auto typeAttrRulesObj = JsonUtil::Create(true);
    for (const auto& [nodeType, rules] : selector.typeAttrRules) {
        auto rulesArr = JsonUtil::CreateArray(true);
        for (const auto& tar : rules) {
            auto ruleObj = JsonUtil::Create(true);
            ruleObj->Put("attr", tar.attr.c_str());
            auto valuesArr = JsonUtil::CreateArray(true);
            for (const auto& v : tar.value) {
                valuesArr->Put("", v.c_str());
            }
            ruleObj->Put("value", valuesArr);
            rulesArr->Put(ruleObj);
        }
        typeAttrRulesObj->Put(nodeType.c_str(), rulesArr);
    }
    return typeAttrRulesObj;
}

std::string WebPageSceneManager::BuildSelectorJson(
    const WebRule& rule, const PageSceneGlobalConfig& globalConfig)
{
    auto root = JsonUtil::Create(true);
    auto nodeTypesArr = JsonUtil::CreateArray(true);
    for (const auto& nt : rule.selector.nodeTypes) {
        nodeTypesArr->Put("", nt.c_str());
    }
    root->Put("nodeTypes", nodeTypesArr);

    if (!rule.selector.typeAttrRules.empty()) {
        root->Put("typeAttrRules", BuildTypeAttrRulesJson(rule.selector));
    }

    if (rule.scope.onlyVisible) {
        root->Put("onlyVisible", true);
    }
    root->Put("includeUnfocusableTextInput", globalConfig.includeUnfocusableTextInput);

    if (rule.report.includeAutocomplete) {
        root->Put("includeAutocomplete", true);
    }
    if (rule.report.includeXpath) {
        root->Put("includeXpath", true);
    }

    return root->ToString();
}

std::string WebPageSceneManager::BuildSceneJsonInner(const std::string& ruleSetId,
    int32_t webId, const WebRule& rule, bool matched, int32_t matchedCount,
    const std::vector<PageSceneControlInfo>& controls, const std::string& eventName)
{
    auto root = JsonUtil::Create(true);
    root->Put("ruleSetId", ruleSetId.c_str());
    root->Put("ruleId", rule.ruleId.c_str());
    root->Put("sceneType", rule.sceneType.c_str());
    root->Put("eventName", eventName.c_str());

    auto source = JsonUtil::Create(true);
    source->Put("type", "ARKWEB");
    source->Put("hostNodeId", webId);
    root->Put("source", source);

    root->Put("matched", matched);
    root->Put("matchedCount", matchedCount);

    auto nodesArr = JsonUtil::CreateArray(true);
    for (const auto& c : controls) {
        auto node = JsonUtil::Create(true);
        if (rule.report.includeNodeIds) {
            node->Put("nodeId", c.nodeId);
        }
        if (rule.report.includeNodeTypes) {
            node->Put("nodeType", c.nodeType.c_str());
        }
        if (rule.report.includeFocusable) {
            node->Put("focusable", c.focusable);
        }
        if (rule.report.includeEditable) {
            node->Put("editable", c.editable);
        }
        if (rule.report.includeRect) {
            auto rectObj = JsonUtil::Create(true);
            rectObj->Put("x", static_cast<double>(c.rectX));
            rectObj->Put("y", static_cast<double>(c.rectY));
            rectObj->Put("width", static_cast<double>(c.rectWidth));
            rectObj->Put("height", static_cast<double>(c.rectHeight));
            node->Put("rect", rectObj);
        }
        if (rule.report.includeText) {
            node->Put("text", c.text.c_str());
        }
        if (rule.report.includeAutocomplete) {
            node->Put("autocomplete", c.autocomplete.c_str());
        }
        if (rule.report.includeXpath) {
            node->Put("xpath", c.xpath.c_str());
        }
        nodesArr->Put(node);
    }
    root->Put("nodes", nodesArr);

    return root->ToString();
}

// ===== Query result processing (unified entry) =====

void WebPageSceneManager::ProcessEmptyControlsInner(const std::string& ruleSetId, int32_t processId,
    int32_t webId, const std::string& selectorJson,
    std::map<int32_t, WebPageSceneRuleSet>& rules, std::vector<std::string>& results)
{
    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return;
    }
    for (const auto& rule : procIt->second.rules) {
        if (!rule.enabled) continue;
        std::string expectedSelector = BuildSelectorJson(rule, procIt->second.globalConfig);
        if (expectedSelector != selectorJson) continue;

        std::string eventName = DeriveSceneTypeInner(processId, webId, rule.ruleId, false, rules);
        if (eventName.empty()) continue;

        bool shouldReport = ShouldReportEventInner(processId, webId, rule.ruleId, eventName, 0,
            {}, rules);
        UpdateRuleStateInner(processId, webId, rule.ruleId, false, 0, shouldReport, {}, rules);
        if (shouldReport) {
            results.push_back(BuildSceneJsonInner(ruleSetId, webId, rule, false, 0, {}, eventName));
        }
    }
}

void WebPageSceneManager::ProcessMatchedControlsInner(const std::string& ruleSetId, int32_t processId,
    int32_t webId, const std::string& selectorJson, int32_t matchedCount, bool isGetResult,
    const std::vector<PageSceneControlInfo>& controls,
    std::map<int32_t, WebPageSceneRuleSet>& rules, std::vector<std::string>& results)
{
    auto procIt = rules.find(processId);
    if (procIt == rules.end()) {
        return;
    }
    for (const auto& rule : procIt->second.rules) {
        if (!rule.enabled) continue;
        std::string expectedSelector = BuildSelectorJson(rule, procIt->second.globalConfig);
        if (expectedSelector != selectorJson) continue;

        bool matched = EvaluateCondition(rule.condition, matchedCount);

        std::string eventName;
        if (matched) {
            eventName = "TEXT_EDITOR";
        } else if (isGetResult) {
            eventName = rule.sceneType;
        } else if (rule.sceneType == "TEXT_EDITOR" || rule.sceneType == "TEXT_EDITOR_EXIT") {
            eventName = DeriveSceneTypeInner(processId, webId, rule.ruleId, matched, rules);
        } else {
            eventName = rule.sceneType;
        }

        if (eventName.empty()) {
            continue;
        }

        bool shouldReport = ShouldReportEventInner(processId, webId, rule.ruleId,
            eventName, matchedCount, controls, rules);
        if (!shouldReport && !isGetResult) {
            UpdateRuleStateInner(processId, webId, rule.ruleId, matched, matchedCount, false, controls, rules);
            continue;
        }

        if (!isGetResult) {
            UpdateRuleStateInner(processId, webId, rule.ruleId, matched, matchedCount, shouldReport, controls, rules);
        }
        results.push_back(BuildSceneJsonInner(ruleSetId, webId, rule, matched, matchedCount, controls, eventName));
    }
}

std::vector<std::string> WebPageSceneManager::ProcessQueryResultCore(int32_t processId, int32_t webId,
    const std::string& selectorJson, const std::string& rawResult, bool isGetResult)
{
    auto controls = ParseControlsJson(rawResult);
    std::vector<std::string> results;

    {
        std::lock_guard<std::mutex> lock(mutex_);
        std::map<int32_t, WebPageSceneRuleSet>* rulesMap = nullptr;
        std::map<int32_t, WebPageSceneRuleSet>::iterator ruleIt;
        auto regIt = registeredRules_.find(processId);
        if (regIt != registeredRules_.end()) {
            rulesMap = &registeredRules_;
            ruleIt = regIt;
        } else {
            auto pendIt = pendingGetRules_.find(processId);
            if (pendIt != pendingGetRules_.end()) {
                rulesMap = &pendingGetRules_;
                ruleIt = pendIt;
            }
        }
        if (!rulesMap) {
            return results;
        }
        const std::string& ruleSetId = ruleIt->second.ruleSetId;

        if (controls.empty() && !isGetResult) {
            ProcessEmptyControlsInner(ruleSetId, processId, webId, selectorJson, *rulesMap, results);
        } else {
            int32_t matchedCount = static_cast<int32_t>(controls.size());
            ProcessMatchedControlsInner(ruleSetId, processId, webId, selectorJson,
                matchedCount, isGetResult, controls, *rulesMap, results);
        }
    } // lock released

    return results;
}

void WebPageSceneManager::ProcessQueryResult(int32_t processId, int32_t webId,
    const std::string& selectorJson, const std::string& rawResult, bool isGetResult)
{
    auto results = ProcessQueryResultCore(processId, webId, selectorJson, rawResult, isGetResult);
    for (const auto& sceneJson : results) {
        OnMatchResult(processId, sceneJson, isGetResult);
    }
}

} // namespace OHOS::Ace
