/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/common/layout_inspector.h"

#include <string>

#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/utils/SkBase64.h"
#include "wm/window.h"

#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_v2/inspector/inspector.h"
#include "foundation/ability/ability_runtime/frameworks/native/runtime/connect_server_manager.h"

namespace OHOS::Ace {

bool LayoutInspector::layoutInspectorStatus_ = false;

void LayoutInspector::SupportInspector()
{
    auto container = Container::Current();
    CHECK_NULL_VOID_NOLOG(container);
    if (!layoutInspectorStatus_) {
        return;
    }
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr, ContainerScope::CurrentId());
    if (treeJsonStr.empty()) {
        return;
    }
    auto message = JsonUtil::Create(true);
    GetSnapshotJson(ContainerScope::CurrentId(), message);
    CHECK_NULL_VOID(message);

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::SetStatus(bool layoutInspectorStatus)
{
    layoutInspectorStatus_ = layoutInspectorStatus;
}

void LayoutInspector::SetCallback(int32_t instanceId)
{
    LOGI("SetCallback start");
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID_NOLOG(container);
    if (container->IsUseStageModel()) {
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetLayoutInspectorCallback(
            [](int32_t containerId) { return CreateLayoutInfo(containerId); },
            [](bool status) { return SetStatus(status); });
    } else {
        OHOS::Ace::ConnectServerManager::Get().SetLayoutInspectorCallback(
            [](int32_t containerId) { return CreateLayoutInfo(containerId); },
            [](bool status) { return SetStatus(status); });
    }
}

void LayoutInspector::CreateLayoutInfo(int32_t containerId)
{
    LOGI("CreateLayoutInfo start");
    ContainerScope sope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr, containerId);
    auto message = JsonUtil::Create(true);
    GetSnapshotJson(containerId, message);
    CHECK_NULL_VOID(message);

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::GetInspectorTreeJsonStr(std::string& treeJsonStr, int32_t containerId)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);
    if (container->IsUseNewPipeline()) {
        treeJsonStr = NG::Inspector::GetInspector(true);
    } else {
        auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipelineContext);
        treeJsonStr = V2::Inspector::GetInspectorTree(pipelineContext, true);
    }
}

void LayoutInspector::GetSnapshotJson(int32_t containerId, std::unique_ptr<JsonValue>& message)
{
    LOGI("GetSnapshotJson start");
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);

    OHOS::sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::GetTopWindowWithId(container->GetWindowId());
    CHECK_NULL_VOID_NOLOG(window);
    auto pixelMap = window->Snapshot();
    CHECK_NULL_VOID(pixelMap);

    auto data = (*pixelMap).GetPixels();
    auto height = (*pixelMap).GetHeight();
    auto stride = (*pixelMap).GetRowBytes();
    message->Put("type", "snapShot");
    message->Put("width", (*pixelMap).GetWidth());
    message->Put("height", height);
    message->Put("posX", container->GetViewPosX());
    message->Put("posY", container->GetViewPosY());
    int32_t encodeLength = SkBase64::Encode(data, height * stride, nullptr);
    SkString info(encodeLength);
    SkBase64::Encode(data, height * stride, info.writable_str());
    message->Put("pixelMapBase64", info.c_str());
}

} // namespace OHOS::Ace