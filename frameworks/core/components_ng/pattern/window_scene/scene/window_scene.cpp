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

#include "session_manager/include/scene_session_manager.h"
#include "ui/rs_surface_node.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::map<std::string, Rosen::RSAnimationTimingCurve> curveMap {
    { "default",            Rosen::RSAnimationTimingCurve::DEFAULT            },
    { "linear",             Rosen::RSAnimationTimingCurve::LINEAR             },
    { "ease",               Rosen::RSAnimationTimingCurve::EASE               },
    { "easeIn",             Rosen::RSAnimationTimingCurve::EASE_IN            },
    { "easeOut",            Rosen::RSAnimationTimingCurve::EASE_OUT           },
    { "easeInOut",          Rosen::RSAnimationTimingCurve::EASE_IN_OUT        },
    { "spring",             Rosen::RSAnimationTimingCurve::SPRING             },
    { "interactiveSpring",  Rosen::RSAnimationTimingCurve::INTERACTIVE_SPRING },
};
} // namespace

WindowScene::WindowScene(const sptr<Rosen::Session>& session)
{
    session_ = session;
    RegisterLifecycleListener();
    CHECK_NULL_VOID_NOLOG(IsMainWindow());
    callback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        session->SetBufferAvailable(true);
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->BufferAvailableCallback();
    };
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

bool WindowScene::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(dirty, false);
    auto host = dirty->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto globalOffsetWithTranslate = host->GetPaintRectGlobalOffsetWithTranslate();
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto frameRect = geometryNode->GetFrameRect();
    Rosen::WSRect windowRect {
        .posX_ = std::round(globalOffsetWithTranslate.GetX()),
        .posY_ = std::round(globalOffsetWithTranslate.GetY()),
        .width_ = std::round(frameRect.Width()),
        .height_ = std::round(frameRect.Height())
    };

    CHECK_NULL_RETURN(session_, false);
    session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED);
    return false;
}

void WindowScene::BufferAvailableCallback()
{
    ContainerScope scope(instanceId_);

    const auto& config =
        Rosen::SceneSessionManager::GetInstance().GetWindowSceneConfig().startingWindowAnimationConfig_;
    if (config.enabled_) {
        CHECK_NULL_VOID(startingNode_);
        auto context = AceType::DynamicCast<RosenRenderContext>(startingNode_->GetRenderContext());
        CHECK_NULL_VOID(context);
        auto rsNode = context->GetRSNode();
        CHECK_NULL_VOID(rsNode);
        auto effect = Rosen::RSTransitionEffect::Create()->Opacity(config.opacityEnd_);
        rsNode->SetTransitionEffect(effect);
        Rosen::RSAnimationTimingProtocol protocol;
        protocol.SetDuration(config.duration_);
        auto curve = curveMap.count(config.curve_) ? curveMap.at(config.curve_) :
            Rosen::RSAnimationTimingCurve::DEFAULT;
        Rosen::RSNode::Animate(protocol, curve, [rsNode, effect] {
            rsNode->NotifyTransition(effect, false);
        });
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(startingNode_);
    startingNode_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void WindowScene::OnConnect()
{
    CHECK_NULL_VOID_NOLOG(IsMainWindow());
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->session_);
        auto surfaceNode = self->session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);

        CHECK_NULL_VOID(self->contentNode_);
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(self->contentNode_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->AddChild(self->contentNode_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        surfaceNode->SetBufferAvailableCallback(self->callback_);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnForeground()
{
    CHECK_NULL_VOID_NOLOG(IsMainWindow());
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->snapshotNode_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(self->snapshotNode_);
        self->snapshotNode_.Reset();
        host->AddChild(self->contentNode_);
        if (!self->session_->GetBufferAvailable()) {
            self->CreateStartingNode();
            host->AddChild(self->startingNode_);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnBackground()
{
    CHECK_NULL_VOID_NOLOG(IsMainWindow());
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->CreateSnapshotNode();
        host->RemoveChild(self->contentNode_);
        host->AddChild(self->snapshotNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnDisconnect()
{
    CHECK_NULL_VOID_NOLOG(IsMainWindow());
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->CreateSnapshotNode();
        host->RemoveChild(self->contentNode_);
        self->contentNode_.Reset();
        host->RemoveChild(self->startingNode_);
        self->startingNode_.Reset();
        host->AddChild(self->snapshotNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG
