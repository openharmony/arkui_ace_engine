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

#include "core/components_ng/manager/page_scene/page_scene_rule_manager.h"

#include <algorithm>
#include <cctype>
#include <sstream>

#include "base/geometry/ng/rect_t.h"
#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_MIN_REPORT_INTERVAL_MS = 500;
constexpr int32_t MAX_ID_LENGTH = 128;
constexpr int32_t PAGE_SCENE_NO_ERROR = 0;
constexpr int32_t PAGE_SCENE_PARAM_INVALID = 4;
constexpr int32_t PAGE_SCENE_LAST_UNFINISH = 5;
const char TEXT_EDITOR_SCENE[] = "TEXT_EDITOR";
const char EXIT_EVENT_SUFFIX[] = "_EXIT";
const char COUNT_GTE_OPERATOR[] = "COUNT_GTE";
const char SOURCE_ARKUI[] = "ARKUI";
const char SEARCH_FIELD_TAG[] = "SearchField";

bool IsValidId(const std::string& id)
{
    if (id.empty() || id.size() > MAX_ID_LENGTH) {
        return false;
    }
    return std::all_of(id.begin(), id.end(), [](char ch) {
        return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_' || ch == '-';
    });
}

std::unique_ptr<JsonValue> GetObjectValue(const std::unique_ptr<JsonValue>& json, const std::string& key)
{
    if (!json || !json->IsObject()) {
        return nullptr;
    }
    auto value = json->GetValue(key);
    if (!value || !value->IsObject()) {
        return nullptr;
    }
    return value;
}

std::string NormalizeNodeType(const std::string& tag)
{
    if (tag == V2::TEXTINPUT_ETS_TAG) {
        return "TextInput";
    }
    if (tag == V2::TEXTAREA_ETS_TAG) {
        return "TextArea";
    }
    if (tag == V2::SEARCH_ETS_TAG || tag == SEARCH_FIELD_TAG) {
        return "Search";
    }
    if (tag == V2::RICH_EDITOR_ETS_TAG) {
        return "RichEditor";
    }
    return tag;
}

bool IsPageSceneInputControlTag(const std::string& tag)
{
    return tag == V2::TEXTINPUT_ETS_TAG || tag == V2::TEXTAREA_ETS_TAG ||
           tag == V2::SEARCH_ETS_TAG || tag == V2::RICH_EDITOR_ETS_TAG;
}

std::unique_ptr<JsonValue> BuildRectJson(const PageSceneRectInfo& rect)
{
    auto rectJson = JsonUtil::Create(true);
    rectJson->Put("x", static_cast<double>(rect.x));
    rectJson->Put("y", static_cast<double>(rect.y));
    rectJson->Put("width", static_cast<double>(rect.width));
    rectJson->Put("height", static_cast<double>(rect.height));
    return rectJson;
}

std::string ExtractTextFieldText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    auto textFieldPattern = node->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, "");
    auto text = textFieldPattern->GetTextValue();
    if (!text.empty()) {
        return text;
    }
    return UtfUtils::Str16DebugToStr8(textFieldPattern->GetPlaceHolder());
}

std::string ExtractSearchText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    for (const auto& child : node->GetChildrenForInspector(true)) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetTag() == SEARCH_FIELD_TAG) {
            return ExtractTextFieldText(childFrameNode);
        }
    }
    return "";
}

std::string ExtractRichEditorText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    auto richEditorPattern = node->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, "");
    std::u16string text;
    richEditorPattern->GetContentBySpans(text);
    if (text.empty()) {
        return richEditorPattern->GetPlaceHolder();
    }
    return UtfUtils::Str16DebugToStr8(text);
}

std::string ExtractInputText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    auto tag = node->GetTag();
    if (tag == V2::TEXTINPUT_ETS_TAG || tag == V2::TEXTAREA_ETS_TAG || tag == SEARCH_FIELD_TAG) {
        return ExtractTextFieldText(node);
    }
    if (tag == V2::SEARCH_ETS_TAG) {
        return ExtractSearchText(node);
    }
    if (tag == V2::RICH_EDITOR_ETS_TAG) {
        return ExtractRichEditorText(node);
    }
    return "";
}

std::string BuildPageSceneEventName(const std::string& sceneType, bool matched, bool forceReportUnmatched)
{
    if (!matched && !forceReportUnmatched) {
        return sceneType + EXIT_EVENT_SUFFIX;
    }
    return sceneType;
}
} // namespace

void PageSceneInputCountTracker::Initialize(
    const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<FrameNode>& pageRoot)
{
    Reset();
    CollectInputNodes(ruleSet, rule, pageRoot);
    std::sort(visibleInputNodes_.begin(), visibleInputNodes_.end(), [](const auto& left, const auto& right) {
        return left.nodeId < right.nodeId;
    });
}

void PageSceneInputCountTracker::Reset()
{
    visibleInputNodes_.clear();
}

const std::vector<PageSceneNodeInfo>& PageSceneInputCountTracker::GetVisibleInputNodes() const
{
    return visibleInputNodes_;
}

void PageSceneInputCountTracker::CollectInputNodes(
    const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        auto nodeInfo = BuildNodeInfo(ruleSet, rule, frameNode);
        if (nodeInfo.has_value()) {
            visibleInputNodes_.emplace_back(nodeInfo.value());
            return;
        }
        if (IsPageSceneInputControlTag(frameNode->GetTag())) {
            return;
        }
    }
    for (const auto& child : node->GetChildrenForInspector(true)) {
        CollectInputNodes(ruleSet, rule, child);
    }
}

std::optional<PageSceneNodeInfo> PageSceneInputCountTracker::BuildNodeInfo(
    const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, std::nullopt);
    if (!IsPageSceneInputControlTag(node->GetTag())) {
        return std::nullopt;
    }
    auto nodeType = NormalizeNodeType(node->GetTag());
    if (rule.nodeTypes.find(nodeType) == rule.nodeTypes.end()) {
        return std::nullopt;
    }

    RectF rect = rule.onlyVisible ? node->GetTransformRectRelativeToWindowOnlyVisible(true)
                                  : node->GetTransformRectRelativeToWindow(true);
    bool visible = !rule.onlyVisible || (node->IsVisibleAndActive() && rect.Width() > 0.0f && rect.Height() > 0.0f);
    if (!visible) {
        return std::nullopt;
    }

    auto focusHub = node->GetFocusHub();
    bool focusable = focusHub != nullptr && focusHub->IsFocusable();
    if (!ruleSet.includeUnfocusableTextInput && !focusable) {
        return std::nullopt;
    }

    PageSceneNodeInfo info;
    info.nodeId = node->GetId();
    info.nodeType = nodeType;
    if (rule.includeText) {
        info.text = ExtractInputText(node);
    }
    info.focusable = focusable;
    info.rect.x = rect.GetX();
    info.rect.y = rect.GetY();
    info.rect.width = rect.Width();
    info.rect.height = rect.Height();
    return info;
}

int32_t PageSceneRuleManager::RegisterRuleSet(int32_t processId, const std::string& ruleJson)
{
    auto ruleSet = ParseRuleSet(ruleJson);
    if (!ruleSet.has_value()) {
        return PAGE_SCENE_PARAM_INVALID;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (registeredRuleSets_.find(processId) != registeredRuleSets_.end()) {
        return PAGE_SCENE_LAST_UNFINISH;
    }
    registeredRuleSets_[processId] = ruleSet.value();
    return PAGE_SCENE_NO_ERROR;
}

int32_t PageSceneRuleManager::UnregisterRuleSet(int32_t processId, const std::string& ruleSetId)
{
    if (ruleSetId.empty()) {
        return PAGE_SCENE_PARAM_INVALID;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = registeredRuleSets_.find(processId);
    if (iter == registeredRuleSets_.end() || iter->second.ruleSetId != ruleSetId) {
        return PAGE_SCENE_PARAM_INVALID;
    }
    registeredRuleSets_.erase(iter);
    pendingGetProcesses_.erase(processId);
    for (auto stateIter = reportStates_.begin(); stateIter != reportStates_.end();) {
        if (stateIter->first.find(std::to_string(processId) + ":") == 0) {
            stateIter = reportStates_.erase(stateIter);
        } else {
            ++stateIter;
        }
    }
    return PAGE_SCENE_NO_ERROR;
}

int32_t PageSceneRuleManager::BeginGetPageScene(
    int32_t processId, const std::string& ruleJsonOrRuleSetId, std::string& ruleJson)
{
    if (ruleJsonOrRuleSetId.empty()) {
        return PAGE_SCENE_PARAM_INVALID;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (pendingGetProcesses_.find(processId) != pendingGetProcesses_.end()) {
        return PAGE_SCENE_LAST_UNFINISH;
    }
    auto registeredIter = registeredRuleSets_.find(processId);
    if (registeredIter != registeredRuleSets_.end() && registeredIter->second.ruleSetId == ruleJsonOrRuleSetId) {
        ruleJson = registeredIter->second.rawJson;
    } else {
        auto ruleSet = ParseRuleSet(ruleJsonOrRuleSetId);
        if (!ruleSet.has_value()) {
            return PAGE_SCENE_PARAM_INVALID;
        }
        ruleJson = ruleJsonOrRuleSetId;
    }
    pendingGetProcesses_.insert(processId);
    return PAGE_SCENE_NO_ERROR;
}

void PageSceneRuleManager::CompleteGetPageScene(int32_t processId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    pendingGetProcesses_.erase(processId);
}

void PageSceneRuleManager::ClearProcess(int32_t processId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    registeredRuleSets_.erase(processId);
    pendingGetProcesses_.erase(processId);
    for (auto stateIter = reportStates_.begin(); stateIter != reportStates_.end();) {
        if (stateIter->first.find(std::to_string(processId) + ":") == 0) {
            stateIter = reportStates_.erase(stateIter);
        } else {
            ++stateIter;
        }
    }
}

std::vector<std::pair<int32_t, std::string>> PageSceneRuleManager::GetActiveRuleJsons() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::pair<int32_t, std::string>> ruleJsons;
    for (const auto& [pid, ruleSet] : registeredRuleSets_) {
        ruleJsons.emplace_back(pid, ruleSet.rawJson);
    }
    return ruleJsons;
}

std::optional<PageSceneMatchResult> PageSceneRuleManager::MatchPageScene(
    int32_t processId, const std::string& ruleJson, const RefPtr<FrameNode>& pageRoot,
    const std::string& pageName, bool forceReportUnmatched)
{
    auto ruleSet = ParseRuleSet(ruleJson);
    if (!ruleSet.has_value() || !ruleSet->arkuiEnabled || !pageRoot) {
        return std::nullopt;
    }
    std::optional<PageSceneMatchResult> unmatchedResult;
    for (const auto& rule : ruleSet->rules) {
        if (!rule.enabled || rule.sceneType != TEXT_EDITOR_SCENE) {
            continue;
        }
        PageSceneInputCountTracker tracker;
        tracker.Initialize(ruleSet.value(), rule, pageRoot);
        const auto& nodes = tracker.GetVisibleInputNodes();
        bool matched = static_cast<int32_t>(nodes.size()) >= rule.threshold;
        PageSceneMatchResult result;
        result.ruleSetId = ruleSet->ruleSetId;
        result.ruleId = rule.ruleId;
        result.sceneType = rule.sceneType;
        result.eventName = BuildPageSceneEventName(rule.sceneType, matched, forceReportUnmatched);
        result.pageName = pageName;
        result.matched = matched;
        result.matchedCount = static_cast<int32_t>(nodes.size());
        result.minReportIntervalMs = rule.minReportIntervalMs;
        result.deduplicate = rule.deduplicate;
        result.signature = BuildSignature(ruleSet.value(), rule, pageName, nodes);
        result.sceneJson = BuildSceneJson(ruleSet.value(), rule, pageName, nodes, matched, result.eventName);
        if (matched || forceReportUnmatched) {
            return result;
        }
        if (!unmatchedResult.has_value()) {
            unmatchedResult = result;
        }
    }
    if (unmatchedResult.has_value()) {
        return unmatchedResult;
    }
    return std::nullopt;
}

bool PageSceneRuleManager::ShouldReport(int32_t processId, const PageSceneMatchResult& result)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto key = std::to_string(processId) + ":" + result.ruleSetId + ":" + result.ruleId + ":" + SOURCE_ARKUI;
    auto iter = reportStates_.find(key);
    if (!result.matched) {
        if (iter == reportStates_.end()) {
            return false;
        }
        reportStates_.erase(iter);
        return true;
    }
    auto now = std::chrono::steady_clock::now();
    if (iter != reportStates_.end()) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - iter->second.second).count();
        if (result.deduplicate && iter->second.first == result.signature) {
            return false;
        }
        if (elapsed < result.minReportIntervalMs) {
            return false;
        }
    }
    reportStates_[key] = { result.signature, now };
    return true;
}

bool PageSceneRuleManager::IsTextInputNodeType(const std::string& nodeType) const
{
    auto normalizedType = NormalizeNodeType(nodeType);
    return normalizedType == "TextInput" || normalizedType == "TextArea" ||
           normalizedType == "Search" || normalizedType == "RichEditor";
}

std::optional<PageSceneRuleSet> PageSceneRuleManager::ParseRuleSet(const std::string& ruleJson) const
{
    auto root = JsonUtil::ParseJsonString(ruleJson);
    if (!root || !root->IsObject()) {
        LOGW("Parse page scene rule failed, invalid json");
        return std::nullopt;
    }
    PageSceneRuleSet ruleSet;
    ruleSet.rawJson = ruleJson;
    ruleSet.ruleSetId = root->GetString("ruleSetId");
    if (!IsValidId(ruleSet.ruleSetId)) {
        return std::nullopt;
    }

    auto globalConfig = GetObjectValue(root, "globalConfig");
    if (globalConfig) {
        ruleSet.includeUnfocusableTextInput = globalConfig->GetBool("includeUnfocusableTextInput", false);
    }

    auto sourceConfig = GetObjectValue(root, "sourceConfig");
    if (sourceConfig) {
        ruleSet.arkuiEnabled = sourceConfig->GetBool("arkui", true);
        ruleSet.webEnabled = sourceConfig->GetBool("web", false);
        ruleSet.uiExtensionEnabled = sourceConfig->GetBool("uiExtension", false);
    }

    auto webRules = root->GetValue("webRules");
    if (webRules && !webRules->IsNull()) {
        ruleSet.webRulesRaw = webRules->ToString();
    }

    auto rules = root->GetValue("rules");
    if (!rules || !rules->IsArray() || rules->GetArraySize() <= 0) {
        return std::nullopt;
    }
    for (int32_t index = 0; index < rules->GetArraySize(); ++index) {
        auto ruleJsonValue = rules->GetArrayItem(index);
        auto rule = ParseRule(ruleJsonValue);
        if (rule.has_value()) {
            ruleSet.rules.emplace_back(rule.value());
        }
    }
    if (ruleSet.rules.empty()) {
        return std::nullopt;
    }
    return ruleSet;
}

std::optional<PageSceneRule> PageSceneRuleManager::ParseRule(const std::unique_ptr<JsonValue>& ruleJson) const
{
    if (!ruleJson || !ruleJson->IsObject()) {
        return std::nullopt;
    }
    PageSceneRule rule;
    rule.ruleId = ruleJson->GetString("ruleId");
    rule.sceneType = ruleJson->GetString("sceneType");
    rule.enabled = ruleJson->GetBool("enabled", true);
    if (!IsValidId(rule.ruleId) || rule.sceneType != TEXT_EDITOR_SCENE) {
        return std::nullopt;
    }

    auto scope = GetObjectValue(ruleJson, "scope");
    if (scope) {
        rule.onlyVisible = scope->GetBool("onlyVisible", true);
        rule.includeWeb = scope->GetBool("includeWeb", false);
        rule.includeUIExtension = scope->GetBool("includeUIExtension", false);
    }

    auto selector = GetObjectValue(ruleJson, "selector");
    auto nodeTypes = selector ? selector->GetValue("nodeTypes") : nullptr;
    if (!nodeTypes || !nodeTypes->IsArray() || nodeTypes->GetArraySize() <= 0) {
        return std::nullopt;
    }
    for (int32_t index = 0; index < nodeTypes->GetArraySize(); ++index) {
        auto item = nodeTypes->GetArrayItem(index);
        auto nodeType = item ? NormalizeNodeType(item->GetString()) : "";
        if (IsTextInputNodeType(nodeType)) {
            rule.nodeTypes.insert(nodeType);
        }
    }
    if (rule.nodeTypes.empty()) {
        return std::nullopt;
    }

    auto condition = GetObjectValue(ruleJson, "condition");
    if (!condition || condition->GetString("operator") != COUNT_GTE_OPERATOR) {
        return std::nullopt;
    }
    rule.threshold = condition->GetInt("threshold", 0);
    if (rule.threshold <= 0) {
        return std::nullopt;
    }

    auto report = GetObjectValue(ruleJson, "report");
    if (report) {
        rule.includeNodeIds = report->GetBool("includeNodeIds", true);
        rule.includeNodeTypes = report->GetBool("includeNodeTypes", true);
        rule.includeRect = report->GetBool("includeRect", true);
        rule.includeFocusable = report->GetBool("includeFocusable", true);
        rule.includeText = report->GetBool("includeText", false);
    }

    auto policy = GetObjectValue(ruleJson, "policy");
    if (policy) {
        rule.reportOnRegister = policy->GetBool("reportOnRegister", true);
        rule.reportOnTextInputAttached = policy->GetBool("reportOnTextInputAttached", true);
        rule.deduplicate = policy->GetBool("deduplicate", true);
        rule.minReportIntervalMs = policy->GetInt("minReportIntervalMs", DEFAULT_MIN_REPORT_INTERVAL_MS);
        if (rule.minReportIntervalMs < 0) {
            rule.minReportIntervalMs = DEFAULT_MIN_REPORT_INTERVAL_MS;
        }
    }
    return rule;
}

std::string PageSceneRuleManager::BuildSceneJson(const PageSceneRuleSet& ruleSet, const PageSceneRule& rule,
    const std::string& pageName, const std::vector<PageSceneNodeInfo>& nodes, bool matched,
    const std::string& eventName) const
{
    auto root = JsonUtil::Create(true);
    root->Put("ruleSetId", ruleSet.ruleSetId.c_str());
    root->Put("ruleId", rule.ruleId.c_str());
    root->Put("sceneType", rule.sceneType.c_str());
    root->Put("eventName", eventName.c_str());
    root->Put("currentPageName", pageName.c_str());
    auto source = JsonUtil::Create(true);
    source->Put("type", SOURCE_ARKUI);
    source->Put("hostNodeId", -1);
    root->Put("source", source);
    root->Put("matched", matched);
    root->Put("matchedCount", static_cast<int32_t>(nodes.size()));
    auto nodesJson = JsonUtil::CreateArray(true);
    for (const auto& node : nodes) {
        auto nodeJson = JsonUtil::Create(true);
        if (rule.includeNodeIds) {
            nodeJson->Put("nodeId", node.nodeId);
        }
        if (rule.includeNodeTypes) {
            nodeJson->Put("nodeType", node.nodeType.c_str());
        }
        if (rule.includeFocusable) {
            nodeJson->Put("focusable", node.focusable);
        }
        if (rule.includeRect) {
            nodeJson->Put("rect", BuildRectJson(node.rect));
        }
        if (rule.includeText) {
            nodeJson->Put("text", node.text.c_str());
        }
        nodesJson->Put(nodeJson);
    }
    root->Put("nodes", nodesJson);
    return root->ToString();
}

std::string PageSceneRuleManager::BuildSignature(
    const PageSceneRuleSet& ruleSet, const PageSceneRule& rule, const std::string& pageName,
    const std::vector<PageSceneNodeInfo>& nodes) const
{
    std::ostringstream builder;
    builder << SOURCE_ARKUI << ':' << pageName << ':' << ruleSet.ruleSetId << ':' << rule.ruleId;
    for (const auto& node : nodes) {
        builder << ':' << node.nodeId << '/' << node.nodeType << '/' << node.rect.x << ',' << node.rect.y
                << ',' << node.rect.width << ',' << node.rect.height;
    }
    return builder.str();
}
} // namespace OHOS::Ace::NG
