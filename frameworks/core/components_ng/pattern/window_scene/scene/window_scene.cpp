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
#include "transaction/rs_sync_transaction_controller.h"
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
    boundsChangedCallback_ = [weakThis = WeakClaim(this)](const Rosen::Vector4f& bounds) {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->OnBoundsChanged(bounds);
    };
    CHECK_NULL_VOID(IsMainWindow());
    RegisterLifecycleListener();
    callback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        LOGI("RSSurfaceNode buffer available callback");
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        session->SetBufferAvailable(true);
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->BufferAvailableCallback();
        Rosen::SceneSessionManager::GetInstance().NotifyCompleteFirstFrameDrawing(session->GetPersistentId());
    };
}

WindowScene::~WindowScene()
{
    CHECK_NULL_VOID(IsMainWindow());
    CHECK_NULL_VOID(session_);
    session_->SetShowRecent(false);
    UnregisterLifecycleListener();
}

void WindowScene::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(session_);
    session_->SetUINodeId(host->GetAccessibilityId());

    if (!IsMainWindow()) {
        auto surfaceNode = session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
        surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);
        return;
    }

    auto surfaceNode = session_->GetLeashWinSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
    surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);

    WindowPattern::OnAttachToFrameNode();
}

void WindowScene::UpdateSession(const sptr<Rosen::Session>& session)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(session_ != session);

    LOGI("session %{public}d changes to %{public}d", session_->GetPersistentId(), session->GetPersistentId());
    session_ = session;
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
}

void WindowScene::OnBoundsChanged(const Rosen::Vector4f& bounds)
{
    Rosen::WSRect windowRect {
        .posX_ = std::round(bounds.x_),
        .posY_ = std::round(bounds.y_),
        .width_ = std::round(bounds.z_),
        .height_ = std::round(bounds.w_),
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetGeometryNode()->SetFrameSize(SizeF(windowRect.width_, windowRect.height_));

    CHECK_NULL_VOID(session_);
    auto transactionController = Rosen::RSSyncTransactionController::GetInstance();
    if (transactionController && (session_->GetSessionRect() != windowRect)) {
        session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED,
            transactionController->GetRSTransaction());
    } else {
        session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED);
    }
}

void WindowScene::BufferAvailableCallback()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        const auto& config =
            Rosen::SceneSessionManager::GetInstance().GetWindowSceneConfig().startingWindowAnimationConfig_;
        if (config.enabled_) {
            CHECK_NULL_VOID(self->startingNode_);
            auto context = AceType::DynamicCast<RosenRenderContext>(self->startingNode_->GetRenderContext());
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

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(self->startingNode_);
        self->startingNode_.Reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnActivation()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        if (self->destroyed_) {
            self->destroyed_ = false;
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            host->RemoveChild(self->startingNode_);
            host->RemoveChild(self->contentNode_);
            host->RemoveChild(self->snapshotNode_);
            self->startingNode_.Reset();
            self->contentNode_.Reset();
            self->snapshotNode_.Reset();
            self->OnAttachToFrameNode();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            return;
        }

        if (self->session_ && self->session_->GetShowRecent() &&
            self->session_->GetSessionState() == Rosen::SessionState::STATE_DISCONNECT && self->snapshotNode_) {
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            host->RemoveChild(self->snapshotNode_);
            self->snapshotNode_.Reset();
            self->CreateStartingNode();
            host->AddChild(self->startingNode_);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}

void WindowScene::OnConnect()
{
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
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->snapshotNode_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(self->snapshotNode_);
        self->snapshotNode_.Reset();
        host->AddChild(self->contentNode_);
        if (!self->session_->GetBufferAvailable() && !self->startingNode_) {
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

void WindowScene::OnDisconnect()
{
    CHECK_NULL_VOID(session_);
    auto snapshot = session_->GetSnapshot();

    auto uiTask = [weakThis = WeakClaim(this), snapshot]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->destroyed_ = true;

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(self->contentNode_);
        self->contentNode_.Reset();
        if (!self->snapshotNode_) {
            self->CreateSnapshotNode(snapshot);
            host->AddChild(self->snapshotNode_, 0);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG
