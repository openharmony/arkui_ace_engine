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

#include "core/components_ng/pattern/window_scene/scene/window_scene.h"

#include "ui/rs_surface_node.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_BLACK = 0xff000000;
constexpr uint32_t COLOR_WHITE = 0xffffffff;
} // namespace

WindowScene::WindowScene(const sptr<Rosen::Session>& session)
{
    session_ = session;
    RegisterLifecycleListener();
}

WindowScene::~WindowScene()
{
    UnregisterLifecycleListener();
}

void WindowScene::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(session_);
    auto sessionInfo = session_->GetSessionInfo();
    auto name = sessionInfo.bundleName_;
    auto pos = name.find_last_of('.');
    name = (pos == std::string::npos) ? name : name.substr(pos + 1); // skip '.'

    Rosen::RSSurfaceNodeConfig config;
    config.SurfaceNodeName = "WindowScene_" + name + std::to_string(session_->GetPersistentId());
    auto surfaceNode = Rosen::RSSurfaceNode::Create(config, Rosen::RSSurfaceNodeType::LEASH_WINDOW_NODE);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    WindowPattern::OnAttachToFrameNode();
}

void WindowScene::UpdateSession(const sptr<Rosen::Session>& session)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(session);
    if (session_->GetPersistentId() == session->GetPersistentId()) {
        return;
    }

    LOGI("session %{public}d changes to %{public}d", session_->GetPersistentId(), session->GetPersistentId());
    session_ = session;
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
}

void WindowScene::OnForeground()
{
    CHECK_NULL_VOID(snapshotNode_);

    ContainerScope scope(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->RemoveChild(snapshotNode_);
    snapshotNode_.Reset();
    host->AddChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void WindowScene::OnBackground()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        self->snapshotNode_ = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = self->snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
        self->snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(self->contentNode_);
        host->AddChild(self->snapshotNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        CHECK_NULL_VOID(self->session_);
        CHECK_NULL_VOID(self->session_->GetScenePersistence());
        imageLayoutProperty->UpdateImageSourceInfo(
            ImageSourceInfo("file:/" + self->session_->GetScenePersistence()->GetSnapshotFilePath()));
        imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
        self->snapshotNode_->MarkModifyDone();
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnSetDepth(const int32_t depth)
{
    CHECK_NULL_VOID(session_);
    session_->SetZOrder(static_cast<uint32_t>(depth));
}
} // namespace OHOS::Ace::NG
