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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_scene.h"

#include "render_service_client/core/ui/rs_surface_node.h"

#include "core/common/container_scope.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void HostWindowScene::InitContent()
{
    // had initialized, should not initialize again
    if (initialized_) {
        return;
    }
    initialized_ = true;

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    startingNode_ = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    startingNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(0xffffffff));
    host->AddChild(startingNode_);

    contentNode_ = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    surfaceNode->SetBufferAvailableCallback([weak = WeakClaim(this)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto hostWindowPattern = weak.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->BufferAvailableCallback();
    });
}

void HostWindowScene::BufferAvailableCallback()
{
    auto uiTask = [this]() {
        auto host = GetHost();
        CHECK_NULL_VOID(host);

        host->RemoveChild(startingNode_);
        startingNode_.Reset();

        contentNode_->SetActive(true);
        contentNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        host->AddChild(contentNode_);
        host->RebuildRenderContextTree();
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void HostWindowScene::OnForeground()
{
    auto uiTask = [this]() {
        auto host = GetHost();
        CHECK_NULL_VOID(host);

        host->RemoveChild(startingNode_);
        startingNode_.Reset();

        host->AddChild(contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostSyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void HostWindowScene::OnBackground()
{
    // CHECK_NULL_VOID(session_);
    // auto snapShot = session_->GetSnapShot();

    auto uiTask = [this]() {
        auto host = GetHost();
        CHECK_NULL_VOID(host);

        host->RemoveChild(contentNode_);

        startingNode_ = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        // auto imageLayoutProperty = startingNode_->GetLayoutProperty<ImageLayoutProperty>();
        // if (imageLayoutProperty) {
        //     imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(snapShot));
        // }
        startingNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
        startingNode_->GetRenderContext()->UpdateBackgroundColor(Color(0xffffffff));

        host->AddChild(startingNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostSyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

} // namespace OHOS::Ace::NG
