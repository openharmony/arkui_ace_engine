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

#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
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
    CHECK_NULL_VOID(session_);
    session_->SetNeedSnapshot(true);
    RegisterLifecycleListener();
    callback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        LOGI("[WMSMain]RSSurfaceNode buffer available callback");
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
    session_->AttachToFrameNode(true);
    auto responseRegionCallback = [weakThis = WeakClaim(this), weakSession = wptr(session_)](
        const std::vector<DimensionRect>& responseRegion) {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        std::vector<Rosen::Rect> hotAreas;
        for (auto& rect : responseRegion) {
            Rosen::Rect windowRect {
                .posX_ = std::round(rect.GetOffset().GetX().Value()),
                .posY_ = std::round(rect.GetOffset().GetY().Value()),
                .width_ = std::round(rect.GetWidth().Value()),
                .height_ = std::round(rect.GetHeight().Value()),
            };
            hotAreas.push_back(windowRect);
        }
        session->SetTouchHotAreas(hotAreas);
    };
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (gestureHub) {
        gestureHub->SetResponseRegionFunc(responseRegionCallback);
    }

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

    RegisterFocusCallback();
    WindowPattern::OnAttachToFrameNode();
}

void WindowScene::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(session_);
    session_->SetUINodeId(0);
    session_->AttachToFrameNode(false);
}

void WindowScene::RegisterFocusCallback()
{
    CHECK_NULL_VOID(session_);

    auto requestFocusCallback = [weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent([weakThis]() {
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            auto focusHub = host->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            focusHub->SetParentFocusable(true);
            focusHub->RequestFocusWithDefaultFocusFirstly();
        },
            TaskExecutor::TaskType::UI);
    };
    session_->SetNotifyUIRequestFocusFunc(requestFocusCallback);

    auto lostFocusCallback = [weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent([weakThis]() {
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            auto focusHub = host->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            focusHub->SetParentFocusable(false);
        },
            TaskExecutor::TaskType::UI);
    };
    session_->SetNotifyUILostFocusFunc(lostFocusCallback);
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
    Rosen::WSRectF originBounds = {
        .posX_ = bounds.x_,
        .posY_ = bounds.y_,
        .width_ = bounds.z_,
        .height_ = bounds.w_,
    };
    session_->SetBounds(originBounds);
    windowRect.posX_ = std::round(bounds.x_ + session_->GetOffsetX());
    windowRect.posY_ = std::round(bounds.y_ + session_->GetOffsetY());
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
    auto uiTask = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
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
            rsNode->MarkNodeGroup(true);
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
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        LOGI("[WMSMain]Remove starting Window node finished id:%{public}d name:%{public}s",
            session->GetPersistentId(), session->GetSessionInfo().bundleName_.c_str());
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
        CHECK_NULL_VOID(self && self->session_);

        if (self->session_->GetShowRecent() &&
            self->session_->GetSessionState() == Rosen::SessionState::STATE_DISCONNECT && self->snapshotNode_) {
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            host->RemoveChild(self->snapshotNode_);
            self->snapshotNode_.Reset();
            self->session_->SetNeedSnapshot(true);
            self->CreateStartingNode();
            host->AddChild(self->startingNode_);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else if (self->session_->GetShowRecent() &&
            self->session_->GetSessionState() != Rosen::SessionState::STATE_DISCONNECT && self->startingNode_) {
            auto surfaceNode = self->session_->GetSurfaceNode();
            CHECK_NULL_VOID(surfaceNode);
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            host->AddChild(self->contentNode_, 0);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            surfaceNode->SetBufferAvailableCallback(self->callback_);
        }
        self->session_->SetShowRecent(false);
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
        self->session_->SetNeedSnapshot(true);
        host->AddChild(self->contentNode_);
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
