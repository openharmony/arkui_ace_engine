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
        SetlayoutInspectorStatus();
        CHECK_NULL_VOID_NOLOG(layoutInspectorStatus_);
    }
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr);
    if (treeJsonStr.empty()) {
        return;
    }
    OHOS::sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::GetTopWindowWithId(container->GetWindowId());
    CHECK_NULL_VOID(window);
    auto pixelMap = window->Snapshot();
    CHECK_NULL_VOID(pixelMap);
    auto data = (*pixelMap).GetPixels();
    auto height = (*pixelMap).GetHeight();
    auto stride = (*pixelMap).GetRowBytes();
    auto message = JsonUtil::Create(true);
    message->Put("type", "snapShot");
    message->Put("width", (*pixelMap).GetWidth());
    message->Put("height", height);
    message->Put("posX", container->GetViewPosX());
    message->Put("posY", container->GetViewPosY());
    int32_t encodeLength = SkBase64::Encode(data, height * stride, nullptr);
    SkString info(encodeLength);
    SkBase64::Encode(data, height * stride, info.writable_str());
    message->Put("pixelMapBase64", info.c_str());

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::SetlayoutInspectorStatus()
{
    auto container = Container::Current();
    CHECK_NULL_VOID_NOLOG(container);
    if (container->IsUseStageModel()) {
        layoutInspectorStatus_ = OHOS::AbilityRuntime::ConnectServerManager::Get().GetlayoutInspectorStatus();
        return;
    }
    layoutInspectorStatus_ = OHOS::Ace::ConnectServerManager::Get().GetlayoutInspectorStatus();
}

void LayoutInspector::GetInspectorTreeJsonStr(std::string& treeJsonStr)
{
    auto container = Container::Current();
    if (container->IsCurrentUseNewPipeline()) {
        treeJsonStr = NG::Inspector::GetInspectorTree(true);
    } else {
        auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipelineContext);
        treeJsonStr = V2::Inspector::GetInspectorTree(pipelineContext, true);
    }
}

} // namespace OHOS::Ace