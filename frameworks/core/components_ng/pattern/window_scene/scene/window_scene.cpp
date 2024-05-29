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
    CHECK_NULL_VOID(session_);
    initWindowMode_ = session_->GetWindowMode();
    session_->SetNeedSnapshot(true);
    RegisterLifecycleListener();
    callback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        if (self->onceFlag_) {
            auto session = weakSession.promote();
            CHECK_NULL_VOID(session);
            session->SetBufferAvailable(true);
            self->BufferAvailableCallback();
            self->onceFlag_ = false;
            Rosen::SceneSessionManager::GetInstance().NotifyCompleteFirstFrameDrawing(session->GetPersistentId());
        }
    };
}

WindowScene::~WindowScene()
{
    CHECK_NULL_VOID(IsMainWindow());
    CHECK_NULL_VOID(session_);
    session_->SetShowRecent(false);
    session_->SetNeedSnapshot(false);
    UnregisterLifecycleListener();
}

std::shared_ptr<Rosen::RSSurfaceNode> WindowScene::CreateLeashWindowNode()
{
    auto name = session_->GetSessionInfo().bundleName_;
    auto pos = name.find_last_of('.');
    name = (pos == std::string::npos) ? name : name.substr(pos + 1); // skip '.'
    Rosen::RSSurfaceNodeConfig config;
    config.SurfaceNodeName = "WindowScene_" + name + std::to_string(session_->GetPersistentId());
    return Rosen::RSSurfaceNode::Create(config, Rosen::RSSurfaceNodeType::LEASH_WINDOW_NODE);
}

void WindowScene::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(session_);
    session_->SetAttachState(true, initWindowMode_);
    session_->SetUINodeId(host->GetAccessibilityId());
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
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSSystem] id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
            session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
        return;
    }

    auto surfaceNode = CreateLeashWindowNode();
    session_->SetLeashWinSurfaceNode(surfaceNode);
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
    session_->SetAttachState(false, initWindowMode_);
    oldWindowRect_ = session_->GetSessionRect();
    session_->SetOldRect(oldWindowRect_);
    CHECK_NULL_VOID(frameNode);
    if (IsMainWindow()) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "[WMSMain] id: %{public}d, node id: %{public}d, name: %{public}s",
            session_->GetPersistentId(), frameNode->GetId(), session_->GetSessionInfo().bundleName_.c_str());
    } else {
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSSystem] id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
            session_->GetPersistentId(), frameNode->GetId(),
            session_->GetWindowType(), session_->GetWindowName().c_str());
    }
}

void WindowScene::OnMountToParentDone()
{
    if (snapshotNode_) {
        snapshotNode_->MovePosition(-1);
    }
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
        }, "ArkUIWindowSceneRequestFocus", TaskExecutor::TaskType::UI);
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
        }, "ArkUIWindowSceneLostFocus", TaskExecutor::TaskType::UI);
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
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self && self->session_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        RefPtr<FrameNode> node;
        std::string nodeName;
        if (self->startingNode_) {
            node = self->startingNode_;
            nodeName = self->startingNodeName_;
        } else if (self->blankNode_) {
            node = self->blankNode_;
            nodeName = self->blankNodeName_;
        } else {
            return;
        }

        auto contentContext = AceType::DynamicCast<RosenRenderContext>(self->contentNode_->GetRenderContext());
        CHECK_NULL_VOID(contentContext);
        auto contentRsNode = contentContext->GetRSNode();
        CHECK_NULL_VOID(contentRsNode);
        contentRsNode->MarkNodeGroup(true);
        contentRsNode->SetAlpha(self->contentOpacityEnd_);

        const auto& config =
            Rosen::SceneSessionManager::GetInstance().GetWindowSceneConfig().startingWindowAnimationConfig_;
        if (config.enabled_) {
            CHECK_NULL_VOID(node);
            auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
            CHECK_NULL_VOID(context);
            auto rsNode = context->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            rsNode->MarkNodeGroup(true);
            rsNode->SetAlpha(config.opacityStart_);
            auto effect = Rosen::RSTransitionEffect::Create()->Opacity(config.opacityEnd_);
            Rosen::RSAnimationTimingProtocol protocol;
            protocol.SetDuration(config.duration_);
            auto curve = Rosen::RSAnimationTimingCurve::DEFAULT;
            auto iter = curveMap.find(config.curve_);
            if (iter != curveMap.end()) {
                curve = iter->second;
            }
            Rosen::RSNode::Animate(protocol, curve, [rsNode, effect] {
                AceAsyncTraceBegin(0, "StartingWindowExitAnimation");
                rsNode->NotifyTransition(effect, false);
            }, []() {
                AceAsyncTraceEnd(0, "StartingWindowExitAnimation");
            });
        }
        self->RemoveChild(host, node, nodeName);
        node.Reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSMain] Remove starting window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneBufferAvailable", TaskExecutor::TaskType::UI);
}

void WindowScene::OnActivation()
{
    ACE_SCOPED_TRACE("WindowScene::OnActivation");
    auto self = weakThis.Upgrade();
    CHECK_NULL_VOID(session_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool showingInRecents = session_->GetShowRecent();
    session_->SetShowRecent(false);
    if (destroyed_) {
        destroyed_ = false;
        RemoveChild(host, startingNode_, startingNodeName_);
        RemoveChild(host, contentNode_, contentNodeName_);
        RemoveChild(host, snapshotNode_, snapshotNodeName_);
        startingNode_.Reset();
        contentNode_.Reset();
        snapshotNode_.Reset();
        session_->SetNeedSnapshot(true);
        OnAttachToFrameNode();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else if (showingInRecents &&
        session_->GetSessionState() == Rosen::SessionState::STATE_DISCONNECT && snapshotNode_) {
        RemoveChild(host, snapshotNode_, snapshotNodeName_);
        snapshotNode_.Reset();
        session_->SetNeedSnapshot(true);
        CreateStartingNode();
        AddChild(host, startingNode_, startingNodeName_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else if (session_->GetSessionState() != Rosen::SessionState::STATE_DISCONNECT && startingNode_) {
        auto surfaceNode = session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);
        AddChild(host, contentNode_, contentNodeName_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        surfaceNode->SetBufferAvailableCallback(callback_);
    } else if (snapshotNode_) {
        auto surfaceNode = session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto frameSize = geometryNode->GetFrameSize();
        AddChild(host, contentNode_, contentNodeName_);
        surfaceNode->SetBufferAvailableCallback(callback_);
        surfaceNode->SetIsNotifyUIBufferAvailable(true);
        if (NearEqual(frameSize.Width(), session_->GetOldRect().width_) &&
            NearEqual(frameSize.Height(), session_->GetOldRect().height_)) {
            return;
        }
        RemoveChild(host, snapshotNode_, snapshotNodeName_);
        snapshotNode_.Reset();
        CreateBlankNode();
        AddChild(host, blankNode_, blankNodeName_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void WindowScene::OnConnect()
{
    oldWindowRect_ = session_->GetSessionRect();
    session_->SetOldRect(oldWindowRect_);
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnConnect");
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
        self->AddChild(host, self->contentNode_, self->contentNodeName_, 0);
        self->contentNode_->ForceSyncGeometryNode();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSMain] Add app window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());

        surfaceNode->SetBufferAvailableCallback(self->callback_);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneConnect", TaskExecutor::TaskType::UI);
}

void WindowScene::OnForeground()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnForeground");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->snapshotNode_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotNode_, self->snapshotNodeName_);
        self->snapshotNode_.Reset();
        self->session_->SetNeedSnapshot(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneForeground", TaskExecutor::TaskType::UI);
}

void WindowScene::OnDisconnect()
{
    CHECK_NULL_VOID(session_);
    auto snapshot = session_->GetSnapshot();

    auto uiTask = [weakThis = WeakClaim(this), snapshot]() {
        ACE_SCOPED_TRACE("WindowScene::OnDisconnect");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->destroyed_ = true;

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (!self->snapshotNode_ && !self->startingNode_) {
            if (snapshot) {
                self->CreateSnapshotNode(snapshot);
                self->AddChild(host, self->snapshotNode_, self->snapshotNodeName_);
            } else {
                self->CreateStartingNode();
                self->AddChild(host, self->startingNode_, self->startingNodeName_);
            }
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneDisconnect", TaskExecutor::TaskType::UI);
}

void WindowScene::onBackground()
{
    oldWindowRect_ = session_->GetSessionRect();
    session_->SetOldRect(oldWindowRect_);
    WindowPattern::OnBackground();
}

bool WindowScene::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto size = dirty->GetGeometryNode()->GetFrameSize();
    auto host = GetHost();
    if (attachToFrameNodeFlag_) {
        attachToFrameNodeFlag_ = false;
        CHECK_EQUAL_RETURN(IsMainWindow(), false, false);
        CHECK_EQUAL_RETURN(session_->GetShowRecent(), true, false);
        if (!(NearEqual(size.Width(), session_->GetOldRect().width_) &&
            NearEqual(size.Height(), session_->GetOldRect().height_)) && snapshotNode_) {
                RemoveChild(host, snapshotNode_, snapshotNodeName_);
                snapshotNode_.Reset();
                CreateBlankNode();
                oldWindowRect_ = {
                    .width_ = size.Width(),
                    .height_ = size.Height()
                };
                session_->SetOldRect(oldWindowRect_);
                auto contentContext = AceType::DynamicCast<RosenRenderContext>(contentNode_->GetRenderContext());
                auto contentRsNode = contentContext->GetRSNode();
                contentRsNode->MarkNodeGroup(true);
                contentRsNode->SetAlpha(contentOpacityEnd_);
                AddChild(host, contentNode_, contentNodeName_);
                AddChild(host, blankNode_, blankNodeName_);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        auto surfaceNode = session_->GetSurfaceNode();
        surfaceNode->SetBufferAvailableCallback(callback_);
        surfaceNode->SetIsNotifyUIBufferAvailable(true);
    }
    return fasle;
}
} // namespace OHOS::Ace::NG
