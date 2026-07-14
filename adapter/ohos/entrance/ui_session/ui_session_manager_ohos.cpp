/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ui_session/ui_session_manager_ohos.h"
#include "adapter/ohos/entrance/ui_session/include/ui_session_trace.h"
#include "adapter/ohos/entrance/ui_session/ui_translate_request_util.h"
#include "interfaces/inner_api/ui_session/ui_session_json_util.h"

#include <algorithm>
#include <cctype>

#include "cJSON.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t PAGE_SCENE_MAX_ID_LENGTH = 128;
constexpr char PAGE_SCENE_RULE_SET_ID[] = "ruleSetId";
constexpr char PAGE_SCENE_SOURCE_CONFIG[] = "sourceConfig";
constexpr char PAGE_SCENE_ARKUI_SOURCE[] = "arkui";
constexpr char PAGE_SCENE_RULES[] = "rules";
constexpr char PAGE_SCENE_RULE_ID[] = "ruleId";
constexpr char PAGE_SCENE_SCENE_TYPE[] = "sceneType";
constexpr char PAGE_SCENE_ENABLED[] = "enabled";
constexpr char PAGE_SCENE_SELECTOR[] = "selector";
constexpr char PAGE_SCENE_NODE_TYPES[] = "nodeTypes";
constexpr char PAGE_SCENE_CONDITION[] = "condition";
constexpr char PAGE_SCENE_OPERATOR[] = "operator";
constexpr char PAGE_SCENE_THRESHOLD[] = "threshold";
constexpr char PAGE_SCENE_POLICY[] = "policy";
constexpr char PAGE_SCENE_REPORT_ON_REGISTER[] = "reportOnRegister";
constexpr char PAGE_SCENE_REPORT_ON_TEXT_INPUT_ATTACHED[] = "reportOnTextInputAttached";
constexpr char PAGE_SCENE_TEXT_EDITOR_SCENE[] = "TEXT_EDITOR";
constexpr char PAGE_SCENE_COUNT_GTE_OPERATOR[] = "COUNT_GTE";
constexpr char PAGE_SCENE_TEXT_INPUT_TAG[] = "TextInput";
constexpr char PAGE_SCENE_TEXT_AREA_TAG[] = "TextArea";
constexpr char PAGE_SCENE_SEARCH_TAG[] = "Search";
constexpr char PAGE_SCENE_SEARCH_FIELD_TAG[] = "SearchField";
constexpr char PAGE_SCENE_RICH_EDITOR_TAG[] = "RichEditor";

bool IsValidPageSceneId(const std::string& id)
{
    if (id.empty() || id.size() > PAGE_SCENE_MAX_ID_LENGTH) {
        return false;
    }
    return std::all_of(id.begin(), id.end(), [](char ch) {
        return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_' || ch == '-';
    });
}

bool IsPageSceneTextInputNode(const std::string& nodeTag)
{
    return nodeTag == PAGE_SCENE_TEXT_INPUT_TAG || nodeTag == PAGE_SCENE_TEXT_AREA_TAG ||
           nodeTag == PAGE_SCENE_SEARCH_TAG || nodeTag == PAGE_SCENE_SEARCH_FIELD_TAG ||
           nodeTag == PAGE_SCENE_RICH_EDITOR_TAG;
}

bool IsPageSceneInputControlNode(const std::string& nodeTag)
{
    return nodeTag == PAGE_SCENE_TEXT_INPUT_TAG || nodeTag == PAGE_SCENE_TEXT_AREA_TAG ||
           nodeTag == PAGE_SCENE_SEARCH_TAG || nodeTag == PAGE_SCENE_RICH_EDITOR_TAG;
}

std::string NormalizePageSceneNodeType(const std::string& nodeTag)
{
    return nodeTag == PAGE_SCENE_SEARCH_FIELD_TAG ? PAGE_SCENE_SEARCH_TAG : nodeTag;
}

std::string GetJsonString(const JsonObject* object, const char* key)
{
    if (object == nullptr || key == nullptr) {
        return "";
    }
    auto item = cJSON_GetObjectItem(object, key);
    return (cJSON_IsString(item) && item->valuestring != nullptr) ? item->valuestring : "";
}

bool GetJsonBool(const JsonObject* object, const char* key, bool defaultValue)
{
    if (object == nullptr || key == nullptr) {
        return defaultValue;
    }
    auto item = cJSON_GetObjectItem(object, key);
    return cJSON_IsBool(item) ? cJSON_IsTrue(item) : defaultValue;
}

int32_t GetJsonInt(const JsonObject* object, const char* key, int32_t defaultValue)
{
    if (object == nullptr || key == nullptr) {
        return defaultValue;
    }
    auto item = cJSON_GetObjectItem(object, key);
    return cJSON_IsNumber(item) ? item->valueint : defaultValue;
}

bool IsSupportedArkuiPageScene(const std::string& sceneType)
{
    return sceneType == PAGE_SCENE_TEXT_EDITOR_SCENE;
}

std::set<std::string> ExtractTextInputNodeTypes(const JsonObject* ruleJsonValue)
{
    std::set<std::string> nodeTypeSet;
    auto selector = cJSON_GetObjectItem(ruleJsonValue, PAGE_SCENE_SELECTOR);
    if (!cJSON_IsObject(selector)) {
        return nodeTypeSet;
    }
    auto nodeTypes = cJSON_GetObjectItem(selector, PAGE_SCENE_NODE_TYPES);
    if (!cJSON_IsArray(nodeTypes) || cJSON_GetArraySize(nodeTypes) <= 0) {
        return nodeTypeSet;
    }
    auto nodeTypeSize = cJSON_GetArraySize(nodeTypes);
    for (int32_t index = 0; index < nodeTypeSize; ++index) {
        auto nodeType = cJSON_GetArrayItem(nodeTypes, index);
        if (!cJSON_IsString(nodeType) || nodeType->valuestring == nullptr) {
            continue;
        }
        auto normalizedType = NormalizePageSceneNodeType(nodeType->valuestring);
        if (IsPageSceneTextInputNode(normalizedType)) {
            nodeTypeSet.emplace(normalizedType);
        }
    }
    return nodeTypeSet;
}

bool HasCountGreaterThanOrEqualCondition(const JsonObject* ruleJsonValue)
{
    auto condition = cJSON_GetObjectItem(ruleJsonValue, PAGE_SCENE_CONDITION);
    if (!cJSON_IsObject(condition)) {
        return false;
    }
    return GetJsonString(condition, PAGE_SCENE_OPERATOR) == PAGE_SCENE_COUNT_GTE_OPERATOR &&
           GetJsonInt(condition, PAGE_SCENE_THRESHOLD, 0) > 0;
}

bool IsSupportedArkuiPageSceneRule(const std::string& ruleId, const std::string& sceneType,
    const std::set<std::string>& nodeTypes, const JsonObject* ruleJsonValue)
{
    return IsValidPageSceneId(ruleId) && IsSupportedArkuiPageScene(sceneType) &&
           !nodeTypes.empty() && HasCountGreaterThanOrEqualCondition(ruleJsonValue);
}

std::string PrintJsonUnformatted(const JsonObject* object)
{
    if (object == nullptr) {
        return "";
    }
    std::string result;
    auto unformatted = cJSON_PrintUnformatted(object);
    if (unformatted != nullptr) {
        result = unformatted;
        cJSON_free(unformatted);
    }
    return result;
}

std::string BuildPageSceneRuleJson(const JsonObject* root, const JsonObject* ruleJsonValue)
{
    auto scopedRuleSet = cJSON_Duplicate(root, true);
    if (scopedRuleSet == nullptr) {
        return "";
    }
    auto scopedRules = cJSON_CreateArray();
    auto scopedRule = cJSON_Duplicate(ruleJsonValue, true);
    if (scopedRules == nullptr || scopedRule == nullptr) {
        cJSON_Delete(scopedRuleSet);
        cJSON_Delete(scopedRules);
        cJSON_Delete(scopedRule);
        return "";
    }
    cJSON_AddItemToArray(scopedRules, scopedRule);
    if (!cJSON_ReplaceItemInObject(scopedRuleSet, PAGE_SCENE_RULES, scopedRules)) {
        cJSON_Delete(scopedRuleSet);
        cJSON_Delete(scopedRules);
        return "";
    }
    auto result = PrintJsonUnformatted(scopedRuleSet);
    cJSON_Delete(scopedRuleSet);
    return result;
}

void LogPageSceneRuleParseFailed(const std::string& ruleJson, const char* parseEnd)
{
    size_t offset = 0;
    if (parseEnd != nullptr && parseEnd >= ruleJson.c_str()) {
        offset = static_cast<size_t>(parseEnd - ruleJson.c_str());
    }
    LOGW("Parse page scene rule failed, length:%{public}zu, offset:%{public}zu", ruleJson.length(), offset);
}
} // namespace

constexpr int32_t ONCE_IPC_SEND_DATA_MAX_SIZE = 131072;
namespace {
constexpr char TRANSLATE_PROCESS_KEY[] = "translate";

struct PageTranslateRequestInfo {
    int32_t scope = PageTranslateRequestUtil::ARKUI_ARKWEB_TRANSLATE_SCOPE;
    std::string extraData;
    bool valid = true;
};

bool HasScope(int32_t scope, int32_t target)
{
    return (scope & target) != 0;
}

PageTranslateRequestInfo ParsePageTranslateRequest(const std::string& request)
{
    PageTranslateRequestInfo info;
    auto json = InspectorJsonUtil::ParseJsonString(request);
    if (json == nullptr || !json->IsObject()) {
        info.extraData = request;
        return info;
    }
    auto scopeValue = json->GetValue("scope");
    if (scopeValue != nullptr) {
        if (!scopeValue->IsNumber()) {
            info.valid = false;
            return info;
        }
        auto scope = scopeValue->GetInt();
        if (!PageTranslateRequestUtil::IsTranslateScopeValid(scope)) {
            info.valid = false;
            return info;
        }
        info.scope = scope;
    }
    info.extraData = json->GetString("extraData", "");
    return info;
}
} // namespace

UiSessionManager* UiSessionManager::GetInstance()
{
    static UiSessionManagerOhos instance;
    return &instance;
}

void UiSessionManagerOhos::ReportClickEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportClickEvent(data);
        } else {
            LOGW("report click event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportSearchEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportSearchEvent(data);
        } else {
            LOGW("report search event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportTextChangeEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportTextChangeEvent(data);
        } else {
            LOGW("report text change event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportRouterChangeEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportRouterChangeEvent(data);
        } else {
            LOGW("report switch event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(
    const std::string& key, const std::string& value, uint32_t eventType)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered() &&
            NeedComponentChangeTypeReporting(eventType)) {
            auto data = InspectorJsonUtil::Create();
            data->Put(key.data(), value.data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component change event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(
    int32_t nodeId, const std::string& key, const std::string& value, uint32_t eventType)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered() &&
            NeedComponentChangeTypeReporting(eventType)) {
            auto data = InspectorJsonUtil::Create();
            data->Put("nodeId", nodeId);
            data->Put(key.data(), value.data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportWebInputEvent(
    int64_t accessibilityId, const std::string& data, const std::string& type)
{
    auto jsonValue = InspectorJsonUtil::Create(true);
    jsonValue->Put("id", accessibilityId);
    jsonValue->Put("$type", "web");
    jsonValue->Put("text", data.c_str());
    jsonValue->Put("eventType", type.c_str());
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportWebUnfocusEvent(accessibilityId, jsonValue->ToString());
        } else {
            LOGW("report web input event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportScrollEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetScrollEventRegistered()) {
            reportService->ReportScrollEvent(data);
        } else {
            LOGW("report scroll event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportLifeCycleEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetLifeCycleEventRegistered()) {
            reportService->ReportLifeCycleEvent(data);
        } else {
            LOGW("report life cycle event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportSelectTextEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetSelectTextEventRegistered()) {
            reportService->ReportSelectTextEvent(data);
        } else {
            LOGW("report select text event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId)
{
    // add death callback
    auto uiReportProxyRecipient = new UiReportProxyRecipient([processId, this]() {
        LOGW("agent process dead,processId:%{public}d", processId);
        bool shouldResetWebTranslate = false;
        bool shouldResetPageTranslate = false;
        {
            std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
            std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
            auto translateIter = processMap_.find(TRANSLATE_PROCESS_KEY);
            bool isTranslateProcess = translateIter != processMap_.end() &&
                                      translateIter->second.find(processId) != translateIter->second.end();
            if (isTranslateProcess) {
                shouldResetWebTranslate = translateIter->second.size() == 1;
                std::lock_guard<std::mutex> pageTranslateLock(pageTranslateSessionMutex_);
                shouldResetPageTranslate = pageTranslateStarted_ &&
                                           (pageTranslateOwnerPid_ == processId || pageTranslateOwnerPid_ < 0);
                if (shouldResetPageTranslate) {
                    pageTranslateStarted_ = false;
                    pageTranslateScope_ = 0;
                    pageTranslateOwnerPid_ = -1;
                }
            }
            // reportMap remove this processId
            this->reportObjectMap_.erase(processId);
            // processMap remove this processId
            for (auto& [_, processSet] : processMap_) {
                processSet.erase(processId);
            }
        }
        if (shouldResetWebTranslate) {
            ResetTranslate(-1);
        }
        if (shouldResetPageTranslate) {
            ResetPageTranslate(-1);
        }
        {
            std::lock_guard<std::mutex> lock(pageSceneMutex_);
            if (pageSceneRuleSets_.erase(processId) > 0) {
                ErasePendingPageSceneRulesLocked(processId);
                auto previousCount = pageSceneRuleRegisterProcesses_.fetch_sub(1);
                if (previousCount <= 1 || !HasRegisteredPageSceneRuleLocked(PAGE_SCENE_TEXT_EDITOR_SCENE)) {
                    pageSceneInputNodeCount_.store(0);
                    pendingPageSceneDetectRules_.clear();
                }
            }
            pendingPageSceneGets_.erase(processId);
        }
    });
    reportStub->AddDeathRecipient(uiReportProxyRecipient);
    std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    reportObjectMap_[processId] = reportStub;
}

int32_t UiSessionManagerOhos::RegisterPageSceneRules(int32_t processId, const std::string& ruleJson)
{
    sptr<IRemoteObject> reportObject;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        auto reportIter = reportObjectMap_.find(processId);
        if (reportIter != reportObjectMap_.end()) {
            reportObject = reportIter->second;
        }
    }
    if (reportObject == nullptr) {
        LOGW("RegisterPageSceneRules report object is null, process id:%{public}d", processId);
        return NOT_CONNECTED;
    }
    auto ruleSetInfo = ExtractPageSceneRuleSetInfo(ruleJson);
    if (ruleSetInfo.ruleSetId.empty()) {
        LOGW("RegisterPageSceneRules invalid rule json, process id:%{public}d", processId);
        return PARAM_INVALID;
    }
    {
        std::lock_guard<std::mutex> lock(pageSceneMutex_);
        bool hadTextEditorRule = HasRegisteredPageSceneRuleLocked(PAGE_SCENE_TEXT_EDITOR_SCENE);
        if (pageSceneRuleSets_.find(processId) != pageSceneRuleSets_.end()) {
            LOGW("RegisterPageSceneRules duplicated, process id:%{public}d", processId);
            return LAST_UNFINISH;
        }
        pageSceneRuleSets_[processId] = ruleSetInfo;
        auto previousCount = pageSceneRuleRegisterProcesses_.fetch_add(1);
        if (previousCount == 0 ||
            (!hadTextEditorRule && HasPageSceneRule(ruleSetInfo, PAGE_SCENE_TEXT_EDITOR_SCENE, false, false, ""))) {
            pageSceneInputNodeCount_.store(0);
        }
    }
    SaveProcessId("pageScene", processId);
    auto registerRuleJsons = GetPageSceneRuleJsons(ruleSetInfo, PAGE_SCENE_TEXT_EDITOR_SCENE, true, false, "");
    for (const auto& registerRuleJson : registerRuleJsons) {
        TriggerPageSceneDetect(processId, registerRuleJson, false);
    }
    return NO_ERROR;
}

int32_t UiSessionManagerOhos::UnregisterPageSceneRules(int32_t processId, const std::string& ruleSetId)
{
    if (ruleSetId.empty()) {
        return PARAM_INVALID;
    }
    {
        std::lock_guard<std::mutex> lock(pageSceneMutex_);
        auto iter = pageSceneRuleSets_.find(processId);
        if (iter == pageSceneRuleSets_.end() || iter->second.ruleSetId != ruleSetId) {
            return PARAM_INVALID;
        }
        pageSceneRuleSets_.erase(iter);
        ErasePendingPageSceneRulesLocked(processId);
        auto previousCount = pageSceneRuleRegisterProcesses_.fetch_sub(1);
        if (previousCount <= 1 || !HasRegisteredPageSceneRuleLocked(PAGE_SCENE_TEXT_EDITOR_SCENE)) {
            pageSceneInputNodeCount_.store(0);
            pendingPageSceneDetectRules_.clear();
        }
        pendingPageSceneGets_.erase(processId);
    }
    EraseProcessId("pageScene", processId);
    TriggerPageSceneDetect(processId, "", false);
    return NO_ERROR;
}

int32_t UiSessionManagerOhos::GetPageScene(int32_t processId, const std::string& ruleJsonOrRuleSetId)
{
    std::string ruleJson;
    if (ruleJsonOrRuleSetId.empty()) {
        return PARAM_INVALID;
    }
    {
        std::lock_guard<std::mutex> lock(pageSceneMutex_);
        if (pendingPageSceneGets_.find(processId) != pendingPageSceneGets_.end()) {
            LOGW("GetPageScene duplicated, process id:%{public}d", processId);
            return LAST_UNFINISH;
        }
        auto iter = pageSceneRuleSets_.find(processId);
        if (iter != pageSceneRuleSets_.end() && iter->second.ruleSetId == ruleJsonOrRuleSetId) {
            auto ruleJsons = GetPageSceneRuleJsons(iter->second, PAGE_SCENE_TEXT_EDITOR_SCENE, false, false, "");
            if (!ruleJsons.empty()) {
                ruleJson = ruleJsons.front();
            }
        } else {
            auto ruleSetInfo = ExtractPageSceneRuleSetInfo(ruleJsonOrRuleSetId);
            auto ruleJsons = GetPageSceneRuleJsons(ruleSetInfo, PAGE_SCENE_TEXT_EDITOR_SCENE, false, false, "");
            if (!ruleJsons.empty()) {
                ruleJson = ruleJsons.front();
            }
        }
        if (ruleJson.empty()) {
            return PARAM_INVALID;
        }
        pendingPageSceneGets_.insert(processId);
    }
    TriggerPageSceneDetect(processId, ruleJson, true);
    return NO_ERROR;
}

bool UiSessionManagerOhos::GetPageSceneRulesRegistered()
{
    return pageSceneRuleRegisterProcesses_.load() > 0 ? true : false;
}

void UiSessionManagerOhos::ReportPageSceneEvent(int32_t processId, const std::string& sceneJson, bool isGetResult)
{
    sptr<IRemoteObject> reportObject;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        auto reportIter = reportObjectMap_.find(processId);
        if (reportIter != reportObjectMap_.end()) {
            reportObject = reportIter->second;
        }
    }
    auto reportService = iface_cast<ReportService>(reportObject);
    if (reportService != nullptr) {
        reportService->ReportPageSceneEvent(sceneJson);
    } else {
        LOGW("ReportPageSceneEvent failed, process id:%{public}d", processId);
    }
    if (isGetResult) {
        CompleteGetPageScene(processId);
    }
}

void UiSessionManagerOhos::CompleteGetPageScene(int32_t processId)
{
    std::lock_guard<std::mutex> lock(pageSceneMutex_);
    pendingPageSceneGets_.erase(processId);
}

void UiSessionManagerOhos::NotifyPageSceneNodeChanged(const std::string& nodeTag, bool isAttach)
{
    if (!IsPageSceneInputControlNode(nodeTag)) {
        return;
    }
    auto ruleJsons = GetPageSceneRuleJsonsForNodeChange(nodeTag, PAGE_SCENE_TEXT_EDITOR_SCENE, isAttach);
    if (ruleJsons.empty()) {
        return;
    }
    if (isAttach) {
        pageSceneInputNodeCount_.fetch_add(1);
    } else {
        auto inputNodeCount = pageSceneInputNodeCount_.load();
        while (inputNodeCount > 0) {
            if (pageSceneInputNodeCount_.compare_exchange_weak(inputNodeCount, inputNodeCount - 1)) {
                break;
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(pageSceneMutex_);
        for (const auto& [pid, ruleJson] : ruleJsons) {
            if (pageSceneRuleSets_.find(pid) == pageSceneRuleSets_.end()) {
                continue;
            }
            pendingPageSceneDetectRules_.emplace(pid, ruleJson);
        }
    }
}

void UiSessionManagerOhos::NotifyPageSceneContentChanged()
{
    std::lock_guard<std::mutex> lock(pageSceneMutex_);
    for (const auto& [pid, ruleSetInfo] : pageSceneRuleSets_) {
        auto ruleJsons = GetPageSceneRuleJsons(ruleSetInfo, PAGE_SCENE_TEXT_EDITOR_SCENE, false, false, "");
        for (const auto& ruleJson : ruleJsons) {
            pendingPageSceneDetectRules_.emplace(pid, ruleJson);
        }
    }
}

void UiSessionManagerOhos::FlushPageSceneNodeChanged()
{
    std::vector<std::pair<int32_t, std::string>> ruleJsons;
    {
        std::lock_guard<std::mutex> lock(pageSceneMutex_);
        if (pendingPageSceneDetectRules_.empty()) {
            return;
        }
        ruleJsons.assign(pendingPageSceneDetectRules_.begin(), pendingPageSceneDetectRules_.end());
        pendingPageSceneDetectRules_.clear();
    }
    for (const auto& [pid, ruleJson] : ruleJsons) {
        TriggerPageSceneDetect(pid, ruleJson, false);
    }
}

void UiSessionManagerOhos::SavePageSceneDetectFunction(PageSceneDetectFunction&& function)
{
    std::lock_guard<std::mutex> lock(pageSceneDetectFunctionMutex_);
    pageSceneDetectFunction_ = std::move(function);
}

void UiSessionManagerOhos::ErasePendingPageSceneRulesLocked(int32_t processId)
{
    for (auto iter = pendingPageSceneDetectRules_.begin(); iter != pendingPageSceneDetectRules_.end();) {
        if (iter->first == processId) {
            iter = pendingPageSceneDetectRules_.erase(iter);
        } else {
            ++iter;
        }
    }
}

void UiSessionManagerOhos::TriggerPageSceneDetect(int32_t processId, const std::string& ruleJson, bool isGetResult)
{
    PageSceneDetectFunction pageSceneDetectFunction;
    {
        std::lock_guard<std::mutex> lock(pageSceneDetectFunctionMutex_);
        pageSceneDetectFunction = pageSceneDetectFunction_;
    }
    if (!pageSceneDetectFunction) {
        LOGW("TriggerPageSceneDetect callback is null, process id:%{public}d", processId);
        if (isGetResult) {
            CompleteGetPageScene(processId);
        }
        return;
    }
    pageSceneDetectFunction(processId, ruleJson, isGetResult);
}

UiSessionManagerOhos::PageSceneRuleSetInfo UiSessionManagerOhos::ExtractPageSceneRuleSetInfo(
    const std::string& ruleJson) const
{
    PageSceneRuleSetInfo ruleSetInfo;
    ruleSetInfo.ruleJson = ruleJson;
    const char* parseEnd = nullptr;
    auto root = cJSON_ParseWithOpts(ruleJson.c_str(), &parseEnd, true);
    if (!cJSON_IsObject(root)) {
        LogPageSceneRuleParseFailed(ruleJson, parseEnd);
        cJSON_Delete(root);
        return ruleSetInfo;
    }
    auto ruleSetId = GetJsonString(root, PAGE_SCENE_RULE_SET_ID);
    if (!IsValidPageSceneId(ruleSetId)) {
        LOGW("Parse page scene rule failed, invalid ruleSetId length:%{public}zu", ruleSetId.length());
        cJSON_Delete(root);
        return ruleSetInfo;
    }
    ruleSetInfo.ruleSetId = ruleSetId;
    auto sourceConfig = cJSON_GetObjectItem(root, PAGE_SCENE_SOURCE_CONFIG);
    if (cJSON_IsObject(sourceConfig)) {
        ruleSetInfo.arkuiEnabled = GetJsonBool(sourceConfig, PAGE_SCENE_ARKUI_SOURCE, true);
    }

    auto rules = cJSON_GetObjectItem(root, PAGE_SCENE_RULES);
    if (!cJSON_IsArray(rules)) {
        cJSON_Delete(root);
        return ruleSetInfo;
    }
    auto ruleSize = cJSON_GetArraySize(rules);
    for (int32_t index = 0; index < ruleSize; ++index) {
        auto ruleJsonValue = cJSON_GetArrayItem(rules, index);
        if (!cJSON_IsObject(ruleJsonValue)) {
            continue;
        }
        PageSceneRuleInfo ruleInfo;
        ruleInfo.ruleId = GetJsonString(ruleJsonValue, PAGE_SCENE_RULE_ID);
        ruleInfo.sceneType = GetJsonString(ruleJsonValue, PAGE_SCENE_SCENE_TYPE);
        if (ruleInfo.ruleId.empty() || ruleInfo.sceneType.empty()) {
            continue;
        }
        ruleInfo.enabled = GetJsonBool(ruleJsonValue, PAGE_SCENE_ENABLED, true);
        auto policy = cJSON_GetObjectItem(ruleJsonValue, PAGE_SCENE_POLICY);
        if (cJSON_IsObject(policy)) {
            ruleInfo.reportOnRegister = GetJsonBool(policy, PAGE_SCENE_REPORT_ON_REGISTER, true);
            ruleInfo.reportOnTextInputAttached =
                GetJsonBool(policy, PAGE_SCENE_REPORT_ON_TEXT_INPUT_ATTACHED, true);
        }
        ruleInfo.nodeTypes = ExtractTextInputNodeTypes(ruleJsonValue);
        if (IsSupportedArkuiPageSceneRule(ruleInfo.ruleId, ruleInfo.sceneType, ruleInfo.nodeTypes, ruleJsonValue)) {
            ruleInfo.ruleJson = BuildPageSceneRuleJson(root, ruleJsonValue);
            ruleInfo.supported = !ruleInfo.ruleJson.empty();
        }
        ruleSetInfo.rules.emplace_back(ruleInfo);
    }
    cJSON_Delete(root);
    return ruleSetInfo;
}

std::string UiSessionManagerOhos::ExtractPageSceneRuleSetId(const std::string& ruleJson) const
{
    return ExtractPageSceneRuleSetInfo(ruleJson).ruleSetId;
}

bool UiSessionManagerOhos::IsPageSceneRuleMatched(const PageSceneRuleInfo& rule, const std::string& sceneType,
    bool requireRegisterPolicy, bool isAttach, const std::string& nodeType) const
{
    if (!rule.enabled || !rule.supported || rule.sceneType != sceneType || rule.ruleJson.empty()) {
        return false;
    }
    if (!nodeType.empty() && rule.nodeTypes.find(nodeType) == rule.nodeTypes.end()) {
        return false;
    }
    if (requireRegisterPolicy && !rule.reportOnRegister) {
        return false;
    }
    if (isAttach && !rule.reportOnTextInputAttached) {
        return false;
    }
    return true;
}

bool UiSessionManagerOhos::HasPageSceneRule(
    const PageSceneRuleSetInfo& ruleSetInfo, const std::string& sceneType, bool requireRegisterPolicy,
    bool isAttach, const std::string& nodeType) const
{
    if (!ruleSetInfo.arkuiEnabled) {
        return false;
    }
    for (const auto& rule : ruleSetInfo.rules) {
        if (IsPageSceneRuleMatched(rule, sceneType, requireRegisterPolicy, isAttach, nodeType)) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> UiSessionManagerOhos::GetPageSceneRuleJsons(
    const PageSceneRuleSetInfo& ruleSetInfo, const std::string& sceneType, bool requireRegisterPolicy,
    bool isAttach, const std::string& nodeType) const
{
    std::vector<std::string> ruleJsons;
    if (!ruleSetInfo.arkuiEnabled) {
        return ruleJsons;
    }
    for (const auto& rule : ruleSetInfo.rules) {
        if (!IsPageSceneRuleMatched(rule, sceneType, requireRegisterPolicy, isAttach, nodeType)) {
            continue;
        }
        ruleJsons.emplace_back(rule.ruleJson);
    }
    return ruleJsons;
}

bool UiSessionManagerOhos::HasRegisteredPageSceneRuleLocked(const std::string& sceneType) const
{
    for (const auto& [_, ruleSetInfo] : pageSceneRuleSets_) {
        if (HasPageSceneRule(ruleSetInfo, sceneType, false, false, "")) {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int32_t, std::string>> UiSessionManagerOhos::GetPageSceneRuleJsonsForNodeChange(
    const std::string& nodeTag, const std::string& sceneType, bool isAttach)
{
    std::vector<std::pair<int32_t, std::string>> ruleJsons;
    auto nodeType = NormalizePageSceneNodeType(nodeTag);
    std::lock_guard<std::mutex> lock(pageSceneMutex_);
    for (const auto& [pid, ruleSetInfo] : pageSceneRuleSets_) {
        auto scopedRuleJsons = GetPageSceneRuleJsons(ruleSetInfo, sceneType, false, isAttach, nodeType);
        for (const auto& ruleJson : scopedRuleJsons) {
            ruleJsons.emplace_back(pid, ruleJson);
        }
    }
    return ruleJsons;
}

void UiSessionManagerOhos::SetClickEventRegistered(bool status)
{
    if (status) {
        clickEventRegisterProcesses_.fetch_add(1);
    } else {
        clickEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetSearchEventRegistered(bool status)
{
    if (status) {
        searchEventRegisterProcesses_.fetch_add(1);
    } else {
        searchEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetTextChangeEventRegistered(bool status)
{
    if (status) {
        textChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        textChangeEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetRouterChangeEventRegistered(bool status)
{
    if (status) {
        routerChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        routerChangeEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetComponentChangeEventRegistered(bool status)
{
    if (status) {
        componentChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        componentChangeEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetComponentChangeEventMask(uint32_t mask)
{
    componentChangeEventMask_ = mask;
}

void UiSessionManagerOhos::SetScrollEventRegistered(bool status)
{
    if (status) {
        scrollEventRegisterProcesses_.fetch_add(1);
    } else {
        scrollEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetLifeCycleEventRegistered(bool status)
{
    if (status) {
        lifeCycleEventRegisterProcesses_.fetch_add(1);
    } else {
        lifeCycleEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetSelectTextEventRegistered(bool status)
{
    if (status) {
        selectTextEventRegisterProcesses_.fetch_add(1);
    } else {
        selectTextEventRegisterProcesses_.fetch_sub(1);
    }
    LOGD("SetSelectTextEventRegistered selectTextEventRegisterProcesses_: %{public}d",
        selectTextEventRegisterProcesses_.load());
}

bool UiSessionManagerOhos::GetClickEventRegistered()
{
    return clickEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetSearchEventRegistered()
{
    return searchEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetTextChangeEventRegistered()
{
    return textChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetRouterChangeEventRegistered()
{
    return routerChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetComponentChangeEventRegistered()
{
    return componentChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::NeedComponentChangeTypeReporting(uint32_t eventType)
{
    return (componentChangeEventMask_ & eventType) != 0;
}

bool UiSessionManagerOhos::GetScrollEventRegistered()
{
    return scrollEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetLifeCycleEventRegistered()
{
    return lifeCycleEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetSelectTextEventRegistered()
{
    return selectTextEventRegisterProcesses_.load() > 0 ? true : false;
}

void UiSessionManagerOhos::GetInspectorTree(ParamConfig config)
{
    webTaskNums_.store(0);
    WebTaskNumsChange(1);
    {
        std::lock_guard<std::mutex> lock(jsonValueMutex_);
        jsonValue_ = InspectorJsonUtil::Create(true);
    }

    InspectorFunction inspectorFunction;
    {
        std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
        inspectorFunction = inspectorFunction_;
    }
    if (inspectorFunction) {
        inspectorFunction(false, config);
    }
}

void UiSessionManagerOhos::GetVisibleInspectorTree(ParamConfig config)
{
    InspectorFunction inspectorFunction;
    {
        std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
        inspectorFunction = inspectorFunction_;
    }
    if (inspectorFunction) {
        inspectorFunction(true, config);
    }
}

void UiSessionManagerOhos::SaveInspectorTreeFunction(InspectorFunction&& function)
{
    std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
    inspectorFunction_ = std::move(function);
}

void UiSessionManagerOhos::AddValueForTree(int32_t id, const std::string& value)
{
    std::lock_guard<std::mutex> lock(jsonValueMutex_);
    if (!jsonValue_) {
        LOGW("AddValueForTree jsonValue is nullptr");
        return;
    }
    std::string key = std::to_string(id);
    if (jsonValue_->Contains(key)) {
        jsonValue_->Replace(key.c_str(), value.c_str());
    } else {
        jsonValue_->Put(key.c_str(), value.c_str());
    }
}

void UiSessionManagerOhos::WebTaskNumsChange(int32_t num)
{
    webTaskNums_.fetch_add(num);
    if (webTaskNums_.load() == 0) {
        std::string data;
        {
            std::lock_guard<std::mutex> lock(jsonValueMutex_);
            if (!jsonValue_) {
                LOGW("WebTaskNumsChange jsonValue is nullptr");
                return;
            }
            data = jsonValue_->ToString();
        }
        ReportInspectorTreeValue(data);
    }
}

void UiSessionManagerOhos::ReportInspectorTreeValue(const std::string& data)
{
    UI_SESSION_SCOPED_TRACE("[UiSessionManagerOhos] ReportInspectorTreeValue");
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("getInspectorTree");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportInspectorTreeValue no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            int32_t index = 1;
            reportService->ReportInspectorTreeValue(data, index, true);
        } else {
            LOGW("report inspector tree value failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::NotifyAllWebPattern(bool isRegister)
{
    {
        std::lock_guard<std::mutex> lock(webFocusEventRegisteredMutex_);
        webFocusEventRegistered = isRegister;
    }

    NotifyAllWebFunction notifyWebFunction;
    {
        std::lock_guard<std::mutex> lock(notifyWebFunctionMutex_);
        notifyWebFunction = notifyWebFunction_;
    }
    if (notifyWebFunction) {
        notifyWebFunction(isRegister);
    }
}

void UiSessionManagerOhos::NotifySendCommandPattern(int32_t id, const std::string& command)
{
    NotifySendCommandFunction notifySendCommandFunction;
    {
        std::lock_guard<std::mutex> lock(notifySendCommandFunctionMutex_);
        notifySendCommandFunction = notifySendCommandFunction_;
    }
    if (notifySendCommandFunction) {
        notifySendCommandFunction(id, command);
    }
}

int32_t UiSessionManagerOhos::NotifySendCommandAsyncPattern(int32_t id, const std::string& command)
{
    NotifySendCommandAsyncFunction notifySendCommandAsyncFunction;
    {
        std::lock_guard<std::mutex> lock(notifySendCommandAsyncFunctionMutex_);
        notifySendCommandAsyncFunction = notifySendCommandAsyncFunction_;
    }
    if (!notifySendCommandAsyncFunction) {
        return 11; // 11 is the error code for no callback
    }
    return notifySendCommandAsyncFunction(id, command);
}

void UiSessionManagerOhos::SaveRegisterForWebFunction(NotifyAllWebFunction&& function)
{
    std::lock_guard<std::mutex> lock(notifyWebFunctionMutex_);
    notifyWebFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveGetHitTestInfoCallback(GetHitTestInfoFunction&& function)
{
    std::lock_guard<std::mutex> lock(getHitTestInfoFunctionMutex_);
    getHitTestInfoFunction_ = std::move(function);
}

void UiSessionManagerOhos::GetLatestHitTestNodeInfosForTouch(InteractionParamConfig config)
{
    GetHitTestInfoFunction getHitTestInfoFunction;
    {
        std::lock_guard<std::mutex> lock(getHitTestInfoFunctionMutex_);
        getHitTestInfoFunction = getHitTestInfoFunction_;
    }
    if (getHitTestInfoFunction) {
        getHitTestInfoFunction(config);
    }
}

void UiSessionManagerOhos::ReportHitTestNodeInfos(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService == nullptr) {
            LOGW("report hitTestNodeInfos failed, process id:%{public}d", pair.first);
            continue;
        }

        size_t partSize = data.size() / ONCE_IPC_SEND_DATA_MAX_SIZE;
        for (size_t i = 0; i <= partSize; i++) {
            if (i != partSize) {
                reportService->ReportHitTestNodeInfos(
                    data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE, ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, false);
            } else {
                reportService->ReportHitTestNodeInfos(data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, true);
            }
        }
    }
}


void UiSessionManagerOhos::SaveForSendCommandFunction(NotifySendCommandFunction&& function)
{
    std::lock_guard<std::mutex> lock(notifySendCommandFunctionMutex_);
    notifySendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function)
{
    std::lock_guard<std::mutex> lock(notifySendCommandAsyncFunctionMutex_);
    notifySendCommandAsyncFunction_ = std::move(function);
}

bool UiSessionManagerOhos::GetWebFocusRegistered()
{
    std::lock_guard<std::mutex> lock(webFocusEventRegisteredMutex_);
    return webFocusEventRegistered;
}

void UiSessionManagerOhos::OnRouterChange(const std::string& path, const std::string& event)
{
    if (GetRouterChangeEventRegistered()) {
        auto value = InspectorJsonUtil::Create(true);
        value->Put("path", path.c_str());
        value->Put("event", event.c_str());
        ReportRouterChangeEvent(value->ToString());
    }
}

void UiSessionManagerOhos::SaveBaseInfo(const std::string& info)
{
    std::lock_guard<std::mutex> lock(baseInfoMutex_);
    baseInfo_ = info;
}

void UiSessionManagerOhos::SendBaseInfo(int32_t processId)
{
    sptr<IRemoteObject> reportObject;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        auto reportIter = reportObjectMap_.find(processId);
        if (reportIter != reportObjectMap_.end()) {
            reportObject = reportIter->second;
        }
    }

    auto reportService = iface_cast<ReportService>(reportObject);
    if (reportService != nullptr) {
        std::string baseInfo;
        {
            std::lock_guard<std::mutex> lock(baseInfoMutex_);
            baseInfo = baseInfo_;
        }
        reportService->SendBaseInfo(baseInfo);
    }
}

void UiSessionManagerOhos::SaveGetPixelMapFunction(GetPixelMapFunction&& function)
{
    std::lock_guard<std::mutex> lock(getPixelMapFunctionMutex_);
    getPixelMapFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveGetImagesByIdFunction(GetImagesByIdFunction&& function)
{
    std::lock_guard<std::mutex> lock(getImagesByIdFunctionMutex_);
    getImagesByIdFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager,
    int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    translateManagerMap_[instanceId] = uiTranslateManager;
}

void UiSessionManagerOhos::SaveGetCurrentInstanceIdCallback(std::function<int32_t()>&& callback)
{
    std::unique_lock<std::shared_mutex> lock(getInstanceIdCallbackMutex_);
    getInstanceIdCallback_ = std::move(callback);
}

void UiSessionManagerOhos::RemoveSaveGetCurrentInstanceId(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(translateManagerMutex_);
    translateManagerMap_.erase(instanceId);
}

void UiSessionManagerOhos::SaveArkUIPageTranslateFunctions(PageTranslateTextFunction&& getTextFunction,
    PageTranslateTextFunction&& startFunction, PageTranslateEndFunction&& endFunction,
    PageTranslateResetFunction&& resetFunction, PageTranslateResultFunction&& resultFunction)
{
    std::lock_guard<std::mutex> lock(arkUIPageTranslateFunctionMutex_);
    getArkUIPageTranslateTextFunction_ = std::move(getTextFunction);
    startArkUIPageTranslateFunction_ = std::move(startFunction);
    endArkUIPageTranslateFunction_ = std::move(endFunction);
    resetArkUIPageTranslateFunction_ = std::move(resetFunction);
    sendArkUIPageTranslateResultFunction_ = std::move(resultFunction);
}

void UiSessionManagerOhos::GetArkUIPageTranslateFunctions(PageTranslateTextFunction& getTextFunction,
    PageTranslateTextFunction& startFunction, PageTranslateEndFunction& endFunction,
    PageTranslateResetFunction& resetFunction, PageTranslateResultFunction& resultFunction)
{
    std::lock_guard<std::mutex> lock(arkUIPageTranslateFunctionMutex_);
    getTextFunction = getArkUIPageTranslateTextFunction_;
    startFunction = startArkUIPageTranslateFunction_;
    endFunction = endArkUIPageTranslateFunction_;
    resetFunction = resetArkUIPageTranslateFunction_;
    resultFunction = sendArkUIPageTranslateResultFunction_;
}

std::shared_ptr<UiTranslateManager> UiSessionManagerOhos::GetCurrentTranslateManager()
{
    std::function<int32_t()> getInstanceIdCallback;
    {
        std::shared_lock<std::shared_mutex> lock(getInstanceIdCallbackMutex_);
        getInstanceIdCallback = getInstanceIdCallback_;
    }
    if (!getInstanceIdCallback) {
        return nullptr;
    }

    int32_t instanceId = getInstanceIdCallback();
    std::shared_lock<std::shared_mutex> lock(translateManagerMutex_);
    auto iter = translateManagerMap_.find(instanceId);
    if (iter == translateManagerMap_.end()) {
        return nullptr;
    }

    auto translateManager = iter->second;
    if (translateManager) {
        return translateManager;
    }
    return nullptr;
}

bool UiSessionManagerOhos::PostToCurrentTranslateManager(
    const char* caller, std::function<void(const std::shared_ptr<UiTranslateManager>&)>&& task)
{
    auto currentTranslateManager = GetCurrentTranslateManager();
    if (!currentTranslateManager) {
        LOGE("%{public}s translateManager is nullptr", caller);
        return false;
    }
    currentTranslateManager->PostToUI([currentTranslateManager, task = std::move(task)]() {
        task(currentTranslateManager);
    });
    return true;
}

void UiSessionManagerOhos::GetWebViewLanguage()
{
#ifndef CROSS_PLATFORM
    PostToCurrentTranslateManager(
        "GetWebViewLanguage", [](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->GetWebViewCurrentLanguage();
        });
#endif
}

void UiSessionManagerOhos::RegisterPipeLineGetCurrentPageName(std::function<std::string()>&& callback)
{
    std::lock_guard<std::mutex> lock(pipelineContextPageNameCallbackMutex_);
    pipelineContextPageNameCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetCurrentPageName()
{
    std::function<std::string()> pipelineContextPageNameCallback;
    {
        std::lock_guard<std::mutex> lock(pipelineContextPageNameCallbackMutex_);
        pipelineContextPageNameCallback = pipelineContextPageNameCallback_;
    }
    if (pipelineContextPageNameCallback) {
        auto result = pipelineContextPageNameCallback();
        SendCurrentPageName(result);
    }
}

void UiSessionManagerOhos::SendCurrentPageName(const std::string& result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendCurrentPageName(result);
        } else {
            LOGW("report send current page name failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveGetSpecifiedContentOffsetsFunction(
    std::function<std::vector<std::pair<float, float>>(int32_t id, const std::string& content)>&& callback)
{
    std::lock_guard<std::mutex> lock(getSpecifiedContentOffsetsCallbackMutex_);
    getSpecifiedContentOffsetsCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveHighlightSpecifiedContentFunction(std::function<void(int32_t id,
    const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)>&& callback)
{
    std::lock_guard<std::mutex> lock(highlightSpecifiedContentCallbackMutex_);
    highlightSpecifiedContentCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveSelectTextFunction(std::function<void()>&& callback)
{
    std::lock_guard<std::mutex> lock(selectTextCallbackMutex_);
    selectTextCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetSpecifiedContentOffsets(int32_t id, const std::string& content)
{
    std::function<std::vector<std::pair<float, float>>(int32_t id, const std::string& content)>
        getSpecifiedContentOffsetsCallback;
    {
        std::lock_guard<std::mutex> lock(getSpecifiedContentOffsetsCallbackMutex_);
        getSpecifiedContentOffsetsCallback = getSpecifiedContentOffsetsCallback_;
    }
    if (getSpecifiedContentOffsetsCallback) {
        getSpecifiedContentOffsetsCallback(id, content);
    }
}

void UiSessionManagerOhos::HighlightSpecifiedContent(
    int32_t id, const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)
{
    std::function<void(int32_t id, const std::string& content, const std::vector<std::string>& nodeIds,
        const std::string& configs)> highlightSpecifiedContentCallback;
    {
        std::lock_guard<std::mutex> lock(highlightSpecifiedContentCallbackMutex_);
        highlightSpecifiedContentCallback = highlightSpecifiedContentCallback_;
    }
    if (highlightSpecifiedContentCallback) {
        highlightSpecifiedContentCallback(id, content, nodeIds, configs);
    }
}

void UiSessionManagerOhos::ReportSelectText()
{
    std::function<void()> selectTextCallback;
    {
        std::lock_guard<std::mutex> lock(selectTextCallbackMutex_);
        selectTextCallback = selectTextCallback_;
    }
    if (selectTextCallback) {
        selectTextCallback();
    }
}

void UiSessionManagerOhos::SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendSpecifiedContentOffsets(offsets);
        } else {
            LOGW("report send specified content offsets failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveProcessId(std::string key, int32_t id)
{
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (key == TRANSLATE_PROCESS_KEY) {
        processMap_[key].clear();
    }
    processMap_[key].emplace(id);
}

void UiSessionManagerOhos::EraseProcessId(const std::string& key, int32_t targetPid)
{
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find(key);
    if (processIter == processMap_.end()) {
        return;
    }
    processIter->second.erase(targetPid);
}

void UiSessionManagerOhos::MarkPageTranslateOwner(int32_t processId)
{
    std::lock_guard<std::mutex> lock(pageTranslateSessionMutex_);
    if (pageTranslateStarted_) {
        pageTranslateOwnerPid_ = processId;
    }
}

void UiSessionManagerOhos::OnPageTranslateResultHandled(int32_t processId)
{
    bool shouldEraseProcess = true;
    {
        std::lock_guard<std::mutex> lock(pageTranslateSessionMutex_);
        shouldEraseProcess = !pageTranslateStarted_ || pageTranslateOwnerPid_ != processId;
    }
    if (shouldEraseProcess) {
        EraseProcessId(TRANSLATE_PROCESS_KEY, processId);
    }
}

void UiSessionManagerOhos::SendCurrentLanguage(std::string result)
{
    int32_t processId = -1;
    sptr<ReportService> reportService;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
        auto processIter = processMap_.find(TRANSLATE_PROCESS_KEY);
        if (processIter == processMap_.end() || processIter->second.empty()) {
            LOGW("SendCurrentLanguage no report proxy");
            return;
        }
        processId = *processIter->second.begin();
        auto reportIter = reportObjectMap_.find(processId);
        reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
    }
    if (reportService != nullptr) {
        reportService->SendCurrentLanguage(result);
    } else {
        LOGW("Send current language failed, process id:%{public}d", processId);
    }
}

void UiSessionManagerOhos::GetWebTranslateText(std::string extraData, bool isContinued)
{
#ifndef CROSS_PLATFORM
    PostToCurrentTranslateManager("GetWebTranslateText",
        [extraData, isContinued](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->GetTranslateText(extraData, isContinued);
        });
#endif
}

int32_t UiSessionManagerOhos::GetPageTranslateText(const std::string& request)
{
    auto requestInfo = ParsePageTranslateRequest(request);
    if (!requestInfo.valid) {
        LOGW("GetPageTranslateText invalid request scope");
        return PARAM_INVALID;
    }
    PageTranslateTextFunction getTextFunction;
    PageTranslateTextFunction startFunction;
    PageTranslateEndFunction endFunction;
    PageTranslateResetFunction resetFunction;
    PageTranslateResultFunction resultFunction;
    GetArkUIPageTranslateFunctions(getTextFunction, startFunction, endFunction, resetFunction, resultFunction);
    if (!PostToCurrentTranslateManager("GetPageTranslateText",
        [requestInfo, getTextFunction](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->GetPageTranslateText(requestInfo.scope, requestInfo.extraData);
            if (HasScope(requestInfo.scope, PageTranslateRequestUtil::ARKUI_TRANSLATE_SCOPE) && getTextFunction) {
                getTextFunction(false);
            }
        })) {
        return FAILED;
    }
    return NO_ERROR;
}

int32_t UiSessionManagerOhos::StartPageTranslate(const std::string& request)
{
    auto requestInfo = ParsePageTranslateRequest(request);
    if (!requestInfo.valid) {
        LOGW("StartPageTranslate invalid request scope");
        return PARAM_INVALID;
    }
    auto currentTranslateManager = GetCurrentTranslateManager();
    if (!currentTranslateManager) {
        LOGE("StartPageTranslate translateManager is nullptr");
        return FAILED;
    }
    {
        std::lock_guard<std::mutex> lock(pageTranslateSessionMutex_);
        pageTranslateScope_ = requestInfo.scope;
        pageTranslateStarted_ = true;
        pageTranslateOwnerPid_ = -1;
    }
    PageTranslateTextFunction getTextFunction;
    PageTranslateTextFunction startFunction;
    PageTranslateEndFunction endFunction;
    PageTranslateResetFunction resetFunction;
    PageTranslateResultFunction resultFunction;
    GetArkUIPageTranslateFunctions(getTextFunction, startFunction, endFunction, resetFunction, resultFunction);
    currentTranslateManager->PostToUI([currentTranslateManager, requestInfo, startFunction]() {
        currentTranslateManager->StartPageTranslate(requestInfo.scope, requestInfo.extraData);
        if (HasScope(requestInfo.scope, PageTranslateRequestUtil::ARKUI_TRANSLATE_SCOPE) && startFunction) {
            startFunction(true);
        }
    });
    return NO_ERROR;
}

void UiSessionManagerOhos::EndPageTranslate()
{
    int32_t scope = PageTranslateRequestUtil::ARKUI_ARKWEB_TRANSLATE_SCOPE;
    {
        std::lock_guard<std::mutex> lock(pageTranslateSessionMutex_);
        scope = pageTranslateScope_ == 0 ? PageTranslateRequestUtil::ARKUI_ARKWEB_TRANSLATE_SCOPE : pageTranslateScope_;
        pageTranslateStarted_ = false;
        pageTranslateScope_ = 0;
        pageTranslateOwnerPid_ = -1;
    }
    PageTranslateTextFunction getTextFunction;
    PageTranslateTextFunction startFunction;
    PageTranslateEndFunction endFunction;
    PageTranslateResetFunction resetFunction;
    PageTranslateResultFunction resultFunction;
    GetArkUIPageTranslateFunctions(getTextFunction, startFunction, endFunction, resetFunction, resultFunction);
    PostToCurrentTranslateManager(
        "EndPageTranslate", [scope, endFunction](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->EndPageTranslate(scope);
            if (HasScope(scope, PageTranslateRequestUtil::ARKUI_TRANSLATE_SCOPE) && endFunction) {
                endFunction();
            }
        });
}

void UiSessionManagerOhos::ResetPageTranslate(int32_t nodeId)
{
    PageTranslateTextFunction getTextFunction;
    PageTranslateTextFunction startFunction;
    PageTranslateEndFunction endFunction;
    PageTranslateResetFunction resetFunction;
    PageTranslateResultFunction resultFunction;
    GetArkUIPageTranslateFunctions(getTextFunction, startFunction, endFunction, resetFunction, resultFunction);
    PostToCurrentTranslateManager("ResetPageTranslate",
        [nodeId, resetFunction](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->ResetPageTranslate(nodeId);
            if (resetFunction) {
                resetFunction(nodeId);
            }
        });
}

void UiSessionManagerOhos::SendPageTranslateResult(const std::string& result)
{
    std::vector<TranslateResult> translateResults;
    if (!PageTranslateRequestUtil::ParseTranslateResults(result, translateResults)) {
        LOGW("SendPageTranslateResult parse result failed");
        return;
    }
    PageTranslateTextFunction getTextFunction;
    PageTranslateTextFunction startFunction;
    PageTranslateEndFunction endFunction;
    PageTranslateResetFunction resetFunction;
    PageTranslateResultFunction resultFunction;
    GetArkUIPageTranslateFunctions(getTextFunction, startFunction, endFunction, resetFunction, resultFunction);
    PostToCurrentTranslateManager("SendPageTranslateResult",
        [translateResults, resultFunction](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->SendPageTranslateResult(translateResults);
            if (resultFunction) {
                resultFunction(translateResults);
            }
        });
}

void UiSessionManagerOhos::SendPageTextToAI(int32_t nodeId, const std::string& text, int64_t version)
{
    int32_t processId = -1;
    sptr<ReportService> reportService;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
        auto processIter = processMap_.find(TRANSLATE_PROCESS_KEY);
        if (processIter == processMap_.end() || processIter->second.empty()) {
            LOGW("SendPageTextToAI no report proxy");
            return;
        }
        processId = *processIter->second.begin();
        auto reportIter = reportObjectMap_.find(processId);
        reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
    }
    if (reportService != nullptr) {
        reportService->SendPageText(nodeId, text, version);
    } else {
        LOGW("Send page text to ai failed, process id:%{public}d", processId);
    }
}

int32_t UiSessionManagerOhos::GetCurrentAbilityLanguageInfo(std::string& language, std::string& region)
{
    GetAbilityLanguageInfoFunction callback;
    {
        std::lock_guard<std::mutex> lock(getAbilityLanguageInfoCallbackMutex_);
        callback = getAbilityLanguageInfoCallback_;
    }
    if (!callback) {
        LOGW("GetCurrentAbilityLanguageInfo callback is not registered");
        return FAILED;
    }
    return callback(language, region);
}

void UiSessionManagerOhos::SaveGetCurrentAbilityLanguageInfoFunction(GetAbilityLanguageInfoFunction&& callback)
{
    std::lock_guard<std::mutex> lock(getAbilityLanguageInfoCallbackMutex_);
    getAbilityLanguageInfoCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SendWebTextToAI(int32_t nodeId, std::string res)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find(TRANSLATE_PROCESS_KEY);
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendWebTextToAI no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendWebText(nodeId, res);
        } else {
            LOGW("Send web text to ai failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
#ifndef CROSS_PLATFORM
    PostToCurrentTranslateManager("SendTranslateResult",
        [nodeId, results, ids](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->SendTranslateResult(nodeId, results, ids);
        });
#endif
}

void UiSessionManagerOhos::SendTranslateResult(int32_t nodeId, std::string res)
{
#ifndef CROSS_PLATFORM
    PostToCurrentTranslateManager("SendTranslateResult",
        [nodeId, res](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->SendTranslateResult(nodeId, res);
        });
#endif
}

void UiSessionManagerOhos::ResetTranslate(int32_t nodeId)
{
#ifndef CROSS_PLATFORM
    PostToCurrentTranslateManager("ResetTranslate",
        [nodeId](const std::shared_ptr<UiTranslateManager>& translateManager) {
            translateManager->ResetTranslate(nodeId);
        });
#endif
}

void UiSessionManagerOhos::GetPixelMap()
{
    GetPixelMapFunction getPixelMapFunction;
    {
        std::lock_guard<std::mutex> lock(getPixelMapFunctionMutex_);
        getPixelMapFunction = getPixelMapFunction_;
    }
    if (getPixelMapFunction) {
        getPixelMapFunction();
    } else {
        LOGW("get pixelMap func is nullptr");
    }
}

void UiSessionManagerOhos::GetMultiImagesById(const std::vector<int32_t>& arkUIIds,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs)
{
    GetImagesByIdFunction getImagesByIdFunction;
    {
        std::lock_guard<std::mutex> lock(getImagesByIdFunctionMutex_);
        getImagesByIdFunction = getImagesByIdFunction_;
    }
    if (getImagesByIdFunction) {
        getImagesByIdFunction(arkUIIds, arkWebs);
    } else {
        LOGW("get images by id function is nullptr");
    }
}

void UiSessionManagerOhos::SendArkUIImagesById(int32_t windowId,
    const std::unordered_map<int32_t, std::shared_ptr<Media::PixelMap>>& componentImages,
    MultiImageQueryErrorCode arkUIErrorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("getArkUIImages");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendArkUIImagesById no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendArkUIImagesById(windowId, componentImages, arkUIErrorCode);
        } else {
            LOGW("Send ArkUI Images By Id failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SendArkWebImagesById(int32_t windowId, const std::map<int32_t, std::map<int32_t,
    std::shared_ptr<Media::PixelMap>>>& webImages, MultiImageQueryErrorCode arkWebErrorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("getArkWebImages");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendArkWebImagesById no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendArkWebImagesById(windowId, webImages, arkWebErrorCode);
        } else {
            LOGW("Send ArkWeb Images By Id failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SendPixelMap(const std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>& maps)
{
#ifndef CROSS_PLATFORM
    auto currentTranslateManager = GetCurrentTranslateManager();
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!currentTranslateManager) {
        LOGW("send pixelMap failed, translateManager is nullptr");
    }
    auto processIter = processMap_.find("pixel");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendPixelMap no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendShowingImage(maps);
        } else {
            LOGW("send pixel maps failed, process id:%{public}d", pid);
        }
    }
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager]() {
            currentTranslateManager->ClearMap();
        });
    }
    processIter->second.clear();
#endif
}

void UiSessionManagerOhos::SendCommand(const std::string& command)
{
    auto json = InspectorJsonUtil::ParseJsonString(command);
    if (!json || json->IsNull()) {
        LOGW("SendCommand ParseJsonString failed");
        return;
    }

    auto value = json->GetValue("cmd");
    if (sendCommandFunction_ && value && value->IsNumber()) {
        int32_t cmdNumber = value->GetInt();
        sendCommandFunction_(cmdNumber);
    } else if (relaxedCommandFunction_) {
        relaxedCommandFunction_(command);
    } else {
        LOGW("SendCommand failed");
    }
}

void UiSessionManagerOhos::SaveSendCommandFunction(SendCommandFunction&& function)
{
    std::lock_guard<std::mutex> lock(sendCommandFunctionMutex_);
    sendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveRelaxedCommandFunction(RelaxedCommandFunction&& function)
{
    relaxedCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::RegisterPipeLineExeAppAIFunction(
    ExeAppAIFunctionFunction&& callback)
{
    std::lock_guard<std::mutex> lock(pipelineExeAppAIFunctionCallbackMutex_);
    pipelineExeAppAIFunctionCallback_ = std::move(callback);
}

void UiSessionManagerOhos::ExeAppAIFunction(const std::string& funcName, const std::string& params,
    const sptr<IRemoteObject>& remoteObj, int32_t nodeId)
{
    ExeAppAIFunctionFunction pipelineExeAppAIFunctionCallback;
    {
        std::lock_guard<std::mutex> lock(pipelineExeAppAIFunctionCallbackMutex_);
        pipelineExeAppAIFunctionCallback = pipelineExeAppAIFunctionCallback_;
    }
    if (pipelineExeAppAIFunctionCallback) {
        auto [result, data] = pipelineExeAppAIFunctionCallback(funcName, params, remoteObj, nodeId);
        SendExeAppAIFunctionResult(result, data);
    }
}

void UiSessionManagerOhos::SendExeAppAIFunctionResult(uint32_t result, const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("ExeAppAIFunction");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendExeAppAIFunctionResult no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendExeAppAIFunctionResult(result, data);
        } else {
            LOGW("report send execute application AI function result failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::RegisterContentChangeCallback(const ContentChangeConfig& config)
{
    std::function<void(ContentChangeConfig)> startContentChangeDetectCallback;
    {
        std::lock_guard<std::mutex> lock(startContentChangeDetectCallbackMutex_);
        startContentChangeDetectCallback = startContentChangeDetectCallback_;
    }
    if (startContentChangeDetectCallback) {
        startContentChangeDetectCallback(config);
    }
}

void UiSessionManagerOhos::UnregisterContentChangeCallback()
{
    std::function<void()> stopContentChangeDetectCallback;
    {
        std::lock_guard<std::mutex> lock(stopContentChangeDetectCallbackMutex_);
        stopContentChangeDetectCallback = stopContentChangeDetectCallback_;
    }
    if (stopContentChangeDetectCallback) {
        stopContentChangeDetectCallback();
    }
}

void UiSessionManagerOhos::ReportContentChangeEvent(ChangeType type, const std::string& simpleTree)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("contentChange");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportContentChangeEvent no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendContentChange(type, simpleTree);
        } else {
            LOGW("Report Content Change Event failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::SetStartContentChangeDetectCallback(std::function<void(ContentChangeConfig)>&& startCallback)
{
    std::lock_guard<std::mutex> lock(startContentChangeDetectCallbackMutex_);
    if (startContentChangeDetectCallback_) {
        return;
    }
    startContentChangeDetectCallback_ = std::move(startCallback);
}

void UiSessionManagerOhos::SetStopContentChangeDetectCallback(std::function<void()>&& stopCallback)
{
    std::lock_guard<std::mutex> lock(stopContentChangeDetectCallbackMutex_);
    if (stopContentChangeDetectCallback_) {
        return;
    }
    stopContentChangeDetectCallback_ = std::move(stopCallback);
}

void UiSessionManagerOhos::GetStateMgmtInfo(const std::string& componentName, const std::string& propertyName,
    const std::string& jsonPath, bool onlyVisible)
{
    GetStateMgmtInfoFunction getStateMgmtInfoFunction;
    {
        std::lock_guard<std::mutex> lock(getStateMgmtInfoFunctionMutex_);
        getStateMgmtInfoFunction = getStateMgmtInfoFunction_;
    }
    if (getStateMgmtInfoFunction) {
        getStateMgmtInfoFunction(componentName, propertyName, jsonPath, onlyVisible);
    }
}

void UiSessionManagerOhos::SaveGetStateMgmtInfoFunction(GetStateMgmtInfoFunction&& callback)
{
    std::lock_guard<std::mutex> lock(getStateMgmtInfoFunctionMutex_);
    getStateMgmtInfoFunction_ = std::move(callback);
}

void UiSessionManagerOhos::ReportGetStateMgmtInfo(std::vector<std::string> results)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("GetStateMgmtInfo");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportGetStateMgmtInfo no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->ReportGetStateMgmtInfo(results);
        } else {
            LOGW("Report GetStateMgmtInfo failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SaveGetWebInfoByRequestFunction(GetWebInfoByRequestFunction&& callback)
{
    std::lock_guard<std::mutex> lock(getWebInfoByRequestCallbackMutex_);
    getWebInfoByRequestCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetWebInfoByRequest(int32_t webId, const std::string& request)
{
    GetWebInfoByRequestFunction getWebInfoByRequestCallback;
    {
        std::lock_guard<std::mutex> lock(getWebInfoByRequestCallbackMutex_);
        getWebInfoByRequestCallback = getWebInfoByRequestCallback_;
    }
    if (getWebInfoByRequestCallback) {
        getWebInfoByRequestCallback(webId, request);
    }
}

void UiSessionManagerOhos::SendWebInfoByRequest(uint32_t windowId, int32_t webId, const std::string& request,
        const std::string& result, WebRequestErrorCode errorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("GetWebInfoByRequest");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendWebInfoByRequest no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendWebInfoRequestResult(windowId, webId, request, result, errorCode);
        } else {
            LOGW("Send WebInfo By Request failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}
} // namespace OHOS::Ace
