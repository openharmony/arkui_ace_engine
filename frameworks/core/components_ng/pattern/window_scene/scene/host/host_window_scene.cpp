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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_scene.h"

#include "render_service_client/core/ui/rs_surface_node.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
HostWindowScene::HostWindowScene(const sptr<Rosen::Session>& session)
{
    session_ = session;
    RegisterLifecycleListener();
}

HostWindowScene::~HostWindowScene()
{
    UnregisterLifecycleListener();
}

void HostWindowScene::UpdateSession(const sptr<Rosen::Session>& session)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(session);
    if (session_->GetPersistentId() == session->GetPersistentId()) {
        return;
    }

    LOGI("session %{public}" PRIu64 " changes to %{public}" PRIu64,
        session_->GetPersistentId(), session->GetPersistentId());
    session_ = session;
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
}

void HostWindowScene::OnForeground()
{
    CHECK_NULL_VOID(snapshotNode_);

    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto hostWindowScene = weakThis.Upgrade();
        CHECK_NULL_VOID(hostWindowScene);

        auto host = hostWindowScene->GetHost();
        CHECK_NULL_VOID(host);

        host->RemoveChild(hostWindowScene->snapshotNode_);
        hostWindowScene->snapshotNode_.Reset();

        host->AddChild(hostWindowScene->contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void HostWindowScene::OnBackground()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto hostWindowScene = weakThis.Upgrade();
        CHECK_NULL_VOID(hostWindowScene);

        hostWindowScene->snapshotNode_ = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = hostWindowScene->snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        hostWindowScene->snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);

        auto host = hostWindowScene->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(hostWindowScene->contentNode_);
        host->AddChild(hostWindowScene->snapshotNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        CHECK_NULL_VOID(hostWindowScene->session_);
        auto snapshot = hostWindowScene->session_->GetSnapshot();
        auto pixelMap = PixelMap::CreatePixelMap(&snapshot);

        CHECK_NULL_VOID(pixelMap);
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
        imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
        hostWindowScene->snapshotNode_->MarkModifyDone();
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG
