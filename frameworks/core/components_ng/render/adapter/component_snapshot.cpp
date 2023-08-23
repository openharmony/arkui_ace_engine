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

#include "core/components_ng/render/adapter/component_snapshot.h"

#include <memory>

#include "transaction/rs_interfaces.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
class CustomizedCallback : public Rosen::SurfaceCaptureCallback {
public:
    explicit CustomizedCallback(ComponentSnapshot::JsCallback&& jsCallback) : callback_(std::move(jsCallback)) {}
    ~CustomizedCallback() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        CHECK_NULL_VOID(callback_);
        if (!pixelMap) {
            LOGW("snapshot creation failed");
            callback_(nullptr, Framework::ERROR_CODE_INTERNAL_ERROR);
        } else {
            LOGI("snapshot created successfully");
            callback_(pixelMap, Framework::ERROR_CODE_NO_ERROR);
        }
    }

private:
    ComponentSnapshot::JsCallback callback_;
};
} // namespace

std::shared_ptr<Rosen::RSNode> ComponentSnapshot::GetRsNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto rsNode = context->GetRSNode();
    return rsNode;
}

void ComponentSnapshot::Get(const std::string& componentId, JsCallback&& callback)
{
    auto node = Inspector::GetFrameNodeByKey(componentId);
    if (!node) {
        LOGW("node not found %{public}s", componentId.c_str());
        callback(nullptr, Framework::ERROR_CODE_INTERNAL_ERROR);
        return;
    }
    auto rsNode = GetRsNode(node);
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    LOGI("TakeSurfaceCaptureForUI");
    rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<CustomizedCallback>(std::move(callback)));
}

void ComponentSnapshot::Create(const RefPtr<AceType>& customNode, JsCallback&& callback, const int32_t delayTime)
{
    auto node = AceType::DynamicCast<FrameNode>(customNode);
    if (!node) {
        LOGW("builder is invalid");
        callback(nullptr, Framework::ERROR_CODE_INTERNAL_ERROR);
        return;
    }

    FrameNode::ProcessOffscreenNode(node);
    LOGD("ProcessOffscreenNode finished, root size = %{public}s",
        node->GetGeometryNode()->GetFrameSize().ToString().c_str());

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    executor->PostDelayedTask(
        [callback, node]() mutable {
            auto rsNode = GetRsNode(node);
            LOGI("TakeSurfaceCaptureForUI rootNode = %{public}s", node->GetTag().c_str());
            auto& rsInterface = Rosen::RSInterfaces::GetInstance();
            rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<CustomizedCallback>(std::move(callback)));
        },
        TaskExecutor::TaskType::UI, delayTime);
}
} // namespace OHOS::Ace::NG
