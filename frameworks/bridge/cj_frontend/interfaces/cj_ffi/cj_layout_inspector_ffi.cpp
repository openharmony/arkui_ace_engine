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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_layout_inspector_ffi.h"

#include <atomic>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <vector>

#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "base/utils/time_util.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/frontend.h"
#include "core/common/layout_inspector.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/base/memory/ace_type.h"
#include "core/components_ng/pattern/custom/custom_node.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace {
void CjCaptureAndSendMessage(const std::string& msg)
{
    if (msg.empty()) {
        return;
    }
    LayoutInspector::SendMessage(msg);
}
} // namespace

static void (*g_profilerStatusNotifyCj)(bool) = nullptr;

namespace OHOS::Ace::Framework {

namespace {
std::shared_mutex g_profilerViewElmtNameMutex;
std::unordered_map<int32_t, std::string> g_profilerViewElmtIdToName;
}

void CjProfilerRegisterViewElementName(int32_t viewElementId, const char* utf8)
{
    if (utf8 == nullptr || utf8[0] == '\0') {
        return;
    }
    std::unique_lock<std::shared_mutex> lock(g_profilerViewElmtNameMutex);
    g_profilerViewElmtIdToName[viewElementId] = utf8;
}

void CjProfilerUnregisterViewElementName(int32_t viewElementId)
{
    std::unique_lock<std::shared_mutex> lock(g_profilerViewElmtNameMutex);
    g_profilerViewElmtIdToName.erase(viewElementId);
}

std::string CjProfilerGetViewElementName(int32_t viewElementId)
{
    std::shared_lock<std::shared_mutex> lock(g_profilerViewElmtNameMutex);
    auto it = g_profilerViewElmtIdToName.find(viewElementId);
    if (it == g_profilerViewElmtIdToName.end()) {
        return "";
    }
    return it->second;
}

void CjNotifyProfilerStatusToCangjie(bool enabled)
{
    if (g_profilerStatusNotifyCj) {
        g_profilerStatusNotifyCj(enabled);
    }
}

namespace {

struct CjStateChangeRecord {
    int32_t viewId = 0;
    std::string componentName;
    std::string decorator;
    std::string propertyName;
    std::string value;
    int64_t inRenderingElementId = -1;
    int32_t propertyId = 0;
    std::vector<int64_t> dependentElmtIds;
    std::string syncPeersJson;
};

static std::string StripProfilerQuotes(std::string s)
{
    constexpr size_t quotePairLen = 2;
    while (s.size() >= quotePairLen && s.front() == '"' && s.back() == '"') {
        s = s.substr(1, s.size() - quotePairLen);
    }
    return s;
}

static std::vector<int64_t> ParseCsvInt64(const char* csv)
{
    std::vector<int64_t> out;
    if (!csv || !*csv) {
        return out;
    }
    const char* p = csv;
    while (*p) {
        char* end = nullptr;
        long long v = std::strtoll(p, &end, 10);
        if (end == p) {
            while (*p && *p != ',') {
                ++p;
            }
            if (*p == ',') {
                ++p;
            }
            continue;
        }
        out.push_back(static_cast<int64_t>(v));
        p = end;
        while (*p && *p != ',') {
            ++p;
        }
        if (*p == ',') {
            ++p;
        }
    }
    return out;
}

static bool ShouldFillChangedTrackPropertyName(const CjStateChangeRecord& rec)
{
    return rec.decorator == "@Publish" && !rec.propertyName.empty();
}

static std::unique_ptr<JsonValue> BuildPropertyDependenciesArray(const std::vector<int64_t>& elmtIds)
{
    auto propDeps = JsonUtil::CreateArray(false);
    if (!propDeps || !propDeps->IsValid()) {
        return propDeps;
    }
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
    auto* reg = ElementRegister::GetInstance();
    if (!reg) {
        return propDeps;
    }
    for (int64_t raw : elmtIds) {
        auto elmtId = static_cast<ElementIdType>(raw);
        auto uiNode = reg->GetUINodeById(elmtId);
        if (!uiNode) {
            continue;
        }
        auto depObj = JsonUtil::Create(false);
        if (!depObj || !depObj->IsValid()) {
            continue;
        }
        depObj->Put("elementId", static_cast<int32_t>(raw));
        depObj->Put("elementTag", uiNode->GetTag().c_str());
        bool isCustom = AceType::DynamicCast<NG::CustomNode>(uiNode) != nullptr;
        if (!isCustom) {
            isCustom = (uiNode->GetTag() == "JsView");
        }
        depObj->Put("isCustomNode", isCustom);
        propDeps->PutRef(std::move(depObj));
    }
#endif
    return propDeps;
}

static void EnrichProfilerSyncPeersArray(JsonValue* syncPeersArr);

static void EnrichProfilerPeerObject(JsonValue* peer)
{
    if (!peer || !peer->IsValid() || !peer->IsObject()) {
        return;
    }
    auto owningView = peer->GetObject("owningView");
    if (owningView && owningView->IsValid() && owningView->IsObject()) {
        const int32_t oid = owningView->GetInt("id", -1);
        if (oid >= 0) {
            const std::string compName = CjProfilerGetViewElementName(oid);
            if (owningView->Contains("componentName")) {
                owningView->Replace("componentName", compName.c_str());
            } else {
                owningView->Put("componentName", compName.c_str());
            }
        }
    }
    const std::string csvStr = peer->GetString("dependentElmtIdsCsv", "");
    if (!csvStr.empty()) {
        auto ids = ParseCsvInt64(csvStr.c_str());
        auto propDeps = BuildPropertyDependenciesArray(ids);
        auto dependentElementIds = peer->GetObject("dependentElementIds");
        if (dependentElementIds && dependentElementIds->IsValid() &&
            dependentElementIds->IsObject() && propDeps && propDeps->IsValid()) {
            dependentElementIds->Replace("propertyDependencies", std::move(propDeps));
        }
        peer->Delete("dependentElmtIdsCsv");
    }
    auto nested = peer->GetValue("syncPeers");
    if (nested && nested->IsValid() && nested->IsArray()) {
        EnrichProfilerSyncPeersArray(nested.get());
    }
}

static void EnrichProfilerSyncPeersArray(JsonValue* syncPeersArr)
{
    if (!syncPeersArr || !syncPeersArr->IsValid() || !syncPeersArr->IsArray()) {
        return;
    }
    const int32_t n = syncPeersArr->GetArraySize();
    for (int32_t i = 0; i < n; ++i) {
        auto peer = syncPeersArr->GetArrayItem(i);
        if (!peer || !peer->IsValid() || !peer->IsObject()) {
            continue;
        }
        EnrichProfilerPeerObject(peer.get());
    }
}

static void AttachDependentElementIds(
    std::unique_ptr<JsonValue>& prop, const std::vector<int64_t>& elmtIds)
{
    auto dependentElementIds = JsonUtil::Create(false);
    if (!dependentElementIds || !dependentElementIds->IsValid()) {
        return;
    }
    dependentElementIds->Put("mode", "Compatible Mode");
    auto trackProps = JsonUtil::CreateArray(false);
    auto propDeps = BuildPropertyDependenciesArray(elmtIds);
    if (trackProps && trackProps->IsValid() && propDeps && propDeps->IsValid()) {
        dependentElementIds->PutRef("trackPropertiesDependencies", std::move(trackProps));
        dependentElementIds->PutRef("propertyDependencies", std::move(propDeps));
    }
    prop->PutRef("dependentElementIds", std::move(dependentElementIds));
}

static void AttachOwningView(std::unique_ptr<JsonValue>& prop,
    const CjStateChangeRecord& rec, const std::string& componentName)
{
    auto owningView = JsonUtil::Create(false);
    if (!owningView || !owningView->IsValid()) {
        return;
    }
    owningView->Put("id", rec.viewId);
    std::string owningCompName = rec.componentName;
    if (owningCompName.empty()) {
        owningCompName = CjProfilerGetViewElementName(rec.viewId);
    }
    if (owningCompName.empty()) {
        owningCompName = componentName;
    }
    owningView->Put("componentName", owningCompName.c_str());
    prop->PutRef("owningView", std::move(owningView));
}

static void AttachSyncPeers(std::unique_ptr<JsonValue>& prop, const std::string& syncPeersJson)
{
    std::unique_ptr<JsonValue> syncPeersArr;
    if (!syncPeersJson.empty()) {
        syncPeersArr = JsonUtil::ParseJsonString(syncPeersJson);
    }
    if (!syncPeersArr || !syncPeersArr->IsArray()) {
        syncPeersArr = JsonUtil::CreateArray(false);
    }
    if (syncPeersArr && syncPeersArr->IsValid()) {
        EnrichProfilerSyncPeersArray(syncPeersArr.get());
        prop->PutRef("syncPeers", std::move(syncPeersArr));
    }
}

static std::unique_ptr<JsonValue> BuildSinglePropertyJson(
    const CjStateChangeRecord& rec, const std::string& componentName)
{
    auto prop = JsonUtil::Create(false);
    if (!prop || !prop->IsValid()) {
        return nullptr;
    }
    prop->Put("decorator", rec.decorator.c_str());
    prop->Put("propertyName", rec.propertyName.c_str());
    if (ShouldFillChangedTrackPropertyName(rec)) {
        prop->Put("changedTrackPropertyName", rec.propertyName.c_str());
    }
    prop->Put("id", rec.propertyId);
    prop->Put("value", rec.value.c_str());
    prop->Put("inRenderingElementId", static_cast<int32_t>(rec.inRenderingElementId));
    AttachDependentElementIds(prop, rec.dependentElmtIds);
    AttachOwningView(prop, rec, componentName);
    prop->Put("length", -1);
    AttachSyncPeers(prop, rec.syncPeersJson);
    return prop;
}

std::string BuildStateInfoJsonFromRecords(int32_t viewId, const std::string& componentName,
    const std::vector<CjStateChangeRecord>& records)
{
    if (records.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: BuildStateInfoJsonFromRecords records empty");
        return "";
    }
    auto root = JsonUtil::Create(true);
    if (!root || !root->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: BuildStateInfoJsonFromRecords root invalid");
        return "";
    }
    auto viewInfo = JsonUtil::Create(false);
    if (!viewInfo || !viewInfo->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: BuildStateInfoJsonFromRecords viewInfo invalid");
        return "";
    }
    viewInfo->Put("id", viewId);
    viewInfo->Put("componentName", componentName.c_str());
    root->PutRef("viewInfo", std::move(viewInfo));

    auto arr = JsonUtil::CreateArray(false);
    if (!arr || !arr->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: BuildStateInfoJsonFromRecords arr invalid");
        return "";
    }
    for (const auto& rec : records) {
        auto prop = BuildSinglePropertyJson(rec, componentName);
        if (prop && prop->IsValid()) {
            arr->PutRef(std::move(prop));
        }
    }
    root->PutRef("observedPropertiesInfo", std::move(arr));
    std::string out = root->ToString();
    TAG_LOGI(AceLogTag::ACE_LAYOUT_INSPECTOR,
        "CjLayoutInspector: BuildStateInfoJsonFromRecords ok viewId=%{public}d"
        " jsonLen=%{public}zu recordCount=%{public}zu",
        viewId, out.size(), records.size());
    return out;
}

std::string BuildMinimalStateInfoJson(int32_t viewId, const std::string& componentName)
{
    auto root = JsonUtil::Create(true);
    if (!root || !root->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: BuildMinimalStateInfoJson root invalid");
        return "";
    }
    auto viewInfo = JsonUtil::Create(false);
    if (!viewInfo || !viewInfo->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: BuildMinimalStateInfoJson viewInfo invalid");
        return "";
    }
    viewInfo->Put("id", viewId);
    viewInfo->Put("componentName", componentName.c_str());
    root->PutRef("viewInfo", std::move(viewInfo));
    auto arr = JsonUtil::CreateArray(false);
    if (arr && arr->IsValid()) {
        root->PutRef("observedPropertiesInfo", std::move(arr));
    }
    return root->ToString();
}

} // namespace

void CjAppendProfilerStateRecordFromFfi(const FfiProfilerStateChangeRecord* p)
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    (void)p;
    return;
#else
    if (!p) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjAppendProfilerStateRecordFromFfi null record");
        return;
    }
    if (!LayoutInspector::GetStateProfilerStatus()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: CjAppendProfilerStateRecordFromFfi skip profiler off viewId=%{public}d", p->viewId);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_LAYOUT_INSPECTOR,
        "CjLayoutInspector: CjAppendProfilerStateRecordFromFfi immediate-send viewId=%{public}d prop=%{public}s",
        p->viewId, p->propertyNameUtf8 ? p->propertyNameUtf8 : "");
    CjStateChangeRecord rec;
    rec.viewId = p->viewId;
    rec.componentName = StripProfilerQuotes(p->componentNameUtf8 ? p->componentNameUtf8 : "");
    const std::string dec = StripProfilerQuotes(p->decoratorUtf8 ? p->decoratorUtf8 : "");
    rec.decorator = dec.empty() ? "Unknown" : dec;
    rec.propertyName = StripProfilerQuotes(p->propertyNameUtf8 ? p->propertyNameUtf8 : "");
    rec.value = p->valueUtf8 ? p->valueUtf8 : "";
    rec.inRenderingElementId = p->inRenderingElementId;
    rec.propertyId = p->propertyId;
    rec.dependentElmtIds =
        p->dependentElmtIdsCsvUtf8 ? ParseCsvInt64(p->dependentElmtIdsCsvUtf8) : std::vector<int64_t>();
    rec.syncPeersJson = p->syncPeersJsonUtf8 ? p->syncPeersJsonUtf8 : "";

    std::string componentName = rec.componentName;
    if (componentName.empty()) {
        componentName = CjProfilerGetViewElementName(rec.viewId);
    }
    if (componentName.empty()) {
        componentName = "Unknown";
    }
    std::vector<CjStateChangeRecord> records;
    records.push_back(std::move(rec));
    std::string jsonStr = BuildStateInfoJsonFromRecords(p->viewId, componentName, records);
    if (jsonStr.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: CjAppendProfilerStateRecordFromFfi skip send due to empty state json");
        return;
    }
    CjSendStateInfoToProfiler(jsonStr);
#endif
}

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkRegisterProfilerStatusNotify(void (*notifyProfilerStatus)(bool enabled))
{
    if (notifyProfilerStatus == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: RegisterProfilerStatusNotify null callback");
        return;
    }
    g_profilerStatusNotifyCj = notifyProfilerStatus;
}

void FfiOHOSAceFrameworkLayoutInspectorPushStateChangeRecord(const FfiProfilerStateChangeRecord* record)
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    (void)record;
    return;
#else
    if (!record) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR,
            "CjLayoutInspector: FfiOHOSAceFrameworkLayoutInspectorPushStateChangeRecord null record");
        return;
    }
    OHOS::Ace::Framework::CjAppendProfilerStateRecordFromFfi(record);
#endif
}

ExternalString FfiOHOSAceProfilerGetViewElementName(int32_t viewElementId)
{
    auto name = CjProfilerGetViewElementName(viewElementId);
    return Utils::MallocCString(name);
}

} // extern "C"

namespace OHOS::Ace::Framework {

void CjSendStateInfoToProfiler(const std::string& stateInfoJson)
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    return;
#else
    if (!LayoutInspector::GetStateProfilerStatus()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjSendStateInfoToProfiler skip profiler off");
        return;
    }
    auto container = Container::Current();
    if (!container) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjSendStateInfoToProfiler skip container null");
        return;
    }
    auto pipeline = container->GetPipelineContext();
    if (!pipeline) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjSendStateInfoToProfiler skip pipeline null");
        return;
    }
    if (stateInfoJson.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjSendStateInfoToProfiler skip json empty");
        return;
    }
    auto info = JsonUtil::ParseJsonString(stateInfoJson);
    if (!info || !info->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "CjLayoutInspector: CjSendStateInfoToProfiler skip parse invalid");
        return;
    }
    info->Put("timeStamp", GetCurrentTimestampMicroSecond());
    info->Put("vsyncID", static_cast<int32_t>(pipeline->GetFrameCount()));
    info->Put("processID", getpid());
    info->Put("windowID", static_cast<int32_t>(pipeline->GetWindowId()));
    std::string outStr = info->ToString();
    CjCaptureAndSendMessage(outStr);
#endif
}

void CjSendMinimalStateInfoToProfiler(int32_t viewId, const std::string& componentName)
{
    std::string jsonStr = BuildMinimalStateInfoJson(viewId, componentName);
    if (!jsonStr.empty()) {
        CjSendStateInfoToProfiler(jsonStr);
    }
}

void EnsureCangjieProfilerStatusHookedForHybridAndEmbedded()
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    return;
#else
    auto container = Container::CurrentSafely();
    if (!container) {
        return;
    }
    const auto ft = container->GetFrontendType();
    if (ft == FrontendType::DECLARATIVE_CJ) {
        return;
    }

    if (!LayoutInspector::HasJsStateProfilerStatusCallback()) {
        return;
    }
    static std::once_flag flag;
    std::call_once(flag, []() {
        LayoutInspector::AppendJsStateProfilerStatusCallback([](bool enable) {
            CjNotifyProfilerStatusToCangjie(enable);
        });
    });
#endif
}
} // namespace OHOS::Ace::Framework
