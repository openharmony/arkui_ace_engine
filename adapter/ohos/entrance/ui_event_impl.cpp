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

#include "adapter/ohos/entrance/ui_event_impl.h"

#include <dlfcn.h>

#include "ui_event_observer.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/inspector_tree_collector.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/base/simplified_inspector.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace {
namespace {
std::string GetWebLanguageByNodeId(int32_t nodeId)
{
    auto& weakNodeCache = Recorder::EventRecorder::Get().GetWeakNodeMap();
    auto iter = weakNodeCache.find(nodeId);
    if (iter == weakNodeCache.end()) {
        return "";
    }
    auto node = iter->second.Upgrade();
    CHECK_NULL_RETURN(node, "");
    auto pattern = node->GetPattern();
    CHECK_NULL_RETURN(pattern, "");
    return pattern->GetCurrentLanguage();
}

std::string GetCurrentPageParam()
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, "");
    auto frontend = container->GetFrontend();
    if (frontend) {
        return frontend->GetTopNavDestinationInfo(false, true);
    }
    return "";
}
} // namespace

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_RegisterUIEventObserver(
    const std::string& config, const std::shared_ptr<UIEventObserver>& observer)
{
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "RegisterUIEventObserver");
    Recorder::EventController::Get().Register(config, observer);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_UnregisterUIEventObserver(const std::shared_ptr<UIEventObserver>& observer)
{
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "UnregisterUIEventObserver.");
    Recorder::EventController::Get().Unregister(observer);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_GetNodeProperty(
    const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodeProperties)
{
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "GetNodeProperty.");
    Recorder::NodeDataCache::Get().GetNodeData(pageUrl, nodeProperties);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_GetSimplifiedInspectorTree(const TreeParams& params, std::string& tree)
{
    if (params.infoType == InspectorInfoType::PAGE_PARAM) {
        tree = GetCurrentPageParam();
        return;
    }
    auto containerId = Recorder::EventRecorder::Get().GetContainerId(params.inspectorType == InspectorPageType::FOCUS);
    auto container = Container::GetContainer(containerId);
    if (!container) {
        return;
    }
    if (params.isWindowIdOnly || params.infoType == InspectorInfoType::WINDOW_ID) {
        tree = std::to_string(container->GetWindowId());
        return;
    }
    if (params.infoType == InspectorInfoType::WEB_LANG) {
        tree = GetWebLanguageByNodeId(params.webId);
        return;
    }
    if (container->IsUseNewPipeline()) {
        auto inspector = std::make_shared<NG::SimplifiedInspector>(containerId, params);
        tree = inspector->GetInspector();
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_GetSimplifiedInspectorTreeAsync(
    const TreeParams& params, OnInspectorTreeResult&& callback)
{
    auto containerId = Recorder::EventRecorder::Get().GetContainerId(params.inspectorType == InspectorPageType::FOCUS);
    auto container = Container::GetContainer(containerId);
    if (!container) {
        return;
    }
    if (container->IsUseNewPipeline()) {
        auto inspector = std::make_shared<NG::SimplifiedInspector>(containerId, params);
        if (params.enableBackground) {
            auto collector = std::make_shared<Recorder::InspectorTreeCollector>(std::move(callback), true);
            inspector->GetInspectorBackgroundAsync(collector);
        } else {
            auto collector = std::make_shared<Recorder::InspectorTreeCollector>(std::move(callback), false);
            inspector->GetInspectorAsync(collector);
        }
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_ExecuteCommandAsync(const UICommandParams& params, UICommandResult&& callback)
{
    auto inspector = std::make_shared<NG::SimplifiedInspector>(0, params);
    auto collector = std::make_shared<Recorder::InspectorTreeCollector>(std::move(callback), false);
    inspector->ExecuteUICommand(collector);
}

namespace Recorder {
constexpr char HA_CLIENT_SO_PATH[] = "libha_ace_engine.z.so";

static bool g_loaded = false;
static void* g_handle = nullptr;
static std::once_flag g_loadFlag;

void InitHandler()
{
    if (g_handle) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_UIEVENT, "report ace loaded");
    auto handle = dlopen(HA_CLIENT_SO_PATH, RTLD_LAZY);
    if (handle == nullptr) {
        TAG_LOGI(AceLogTag::ACE_UIEVENT, "Failed to open shared library %{public}s, reason: %{public}sn",
            HA_CLIENT_SO_PATH, dlerror());
        return;
    }

    auto func = reinterpret_cast<void(*)()>(dlsym(handle, "OnAceLoaded"));
    if (func == nullptr) {
        TAG_LOGI(AceLogTag::ACE_UIEVENT, "Failed to find func, reason: %{public}sn", dlerror());
        dlclose(handle);
        return;
    }
    func();
    g_handle = handle;
}

void Init()
{
    if (g_loaded) {
        return;
    }
    std::call_once(g_loadFlag, [] { InitHandler(); });
    g_loaded = true;
}

void DeInit()
{
    if (g_handle) {
        dlclose(g_handle);
        g_handle = nullptr;
        g_loaded = false;
    }
}
} // namespace OHOS::Ace::Recorder
} // namespace OHOS::Ace
