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
const std::map<std::string, RefPtr<Curve>> curveMap {
    { "default",            Curves::EASE_IN_OUT },
    { "linear",             Curves::LINEAR      },
    { "ease",               Curves::EASE        },
    { "easeIn",             Curves::EASE_IN     },
    { "easeOut",            Curves::EASE_OUT    },
    { "easeInOut",          Curves::EASE_IN_OUT },
};
const uint32_t CLEAN_WINDOW_DELAY_TIME = 1000;
const int32_t ANIMATION_DURATION = 200;
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
    coldStartCallback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        session->SetBufferAvailable(true);
        self->BufferAvailableCallback();
        Rosen::SceneSessionManager::GetInstance().NotifyCompleteFirstFrameDrawing(session->GetPersistentId());
    };
    hotStartCallback_ = [weakThis = WeakClaim(this), weakSession = wptr(session_)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        CHECK_NULL_VOID(self->session_);
        if (self->session_->IsAnco()) {
            if (self->blankWindow_) {
                self->BufferAvailableCallbackForBlank();
            }
            return;
        }
        if (self->session_->GetBufferAvailableCallbackEnable()) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
                "buffer available callback enable is true, no need remove blank.");
            return;
        }
        if (self->snapshotWindow_) {
            self->BufferAvailableCallbackForSnapshot();
        } else if (self->blankWindow_) {
            self->BufferAvailableCallbackForBlank();
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
    if (snapshotWindow_) {
        snapshotWindow_->MovePosition(-1);
    }
}

void WindowScene::RegisterFocusCallback()
{
    CHECK_NULL_VOID(session_);

    auto requestFocusCallback = [weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent(
            [weakThis]() {
                auto self = weakThis.Upgrade();
                CHECK_NULL_VOID(self);
                auto host = self->GetHost();
                CHECK_NULL_VOID(host);
                auto focusHub = host->GetFocusHub();
                CHECK_NULL_VOID(focusHub);
                focusHub->SetParentFocusable(true);
            },
            "ArkUIWindowSceneRequestFocus", TaskExecutor::TaskType::UI);
    };
    session_->SetNotifyUIRequestFocusFunc(requestFocusCallback);

    auto lostFocusCallback = [weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent(
            [weakThis]() {
                auto self = weakThis.Upgrade();
                CHECK_NULL_VOID(self);
                auto host = self->GetHost();
                CHECK_NULL_VOID(host);
                auto focusHub = host->GetFocusHub();
                CHECK_NULL_VOID(focusHub);
                focusHub->SetParentFocusable(false);
            },
            "ArkUIWindowSceneLostFocus", TaskExecutor::TaskType::UI);
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
        CHECK_NULL_VOID(self->startingWindow_);
        const auto& config =
            Rosen::SceneSessionManager::GetInstance().GetWindowSceneConfig().startingWindowAnimationConfig_;
        if (config.enabled_ && self->session_->NeedStartingWindowExitAnimation()) {
            auto context = self->startingWindow_->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->SetMarkNodeGroup(true);
            context->SetOpacity(config.opacityStart_);
            RefPtr<Curve> curve = Curves::LINEAR;
            auto iter = curveMap.find(config.curve_);
            if (iter != curveMap.end()) {
                curve = iter->second;
            }
            auto effect = AceType::MakeRefPtr<ChainedOpacityEffect>(config.opacityEnd_);
            effect->SetAnimationOption(std::make_shared<AnimationOption>(curve, config.duration_));
            context->UpdateChainedTransition(effect);
            AceAsyncTraceBegin(0, "StartingWindowExitAnimation");
            context->SetTransitionUserCallback([](bool) {
                AceAsyncTraceEnd(0, "StartingWindowExitAnimation");
            });
        }

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->startingWindow_, self->startingWindowName_, true);
        self->startingWindow_.Reset();
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

void WindowScene::BufferAvailableCallbackForBlank()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::BufferAvailableCallbackForBlank");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self && self->session_);

        auto context = AceType::DynamicCast<RosenRenderContext>(self->appWindow_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetOpacity(1);

        CHECK_NULL_VOID(self->blankWindow_);
        auto blankWindowContext = AceType::DynamicCast<RosenRenderContext>(self->blankWindow_->GetRenderContext());
        CHECK_NULL_VOID(blankWindowContext);
        auto blankRsNode = blankWindowContext->GetRSNode();
        CHECK_NULL_VOID(blankRsNode);
        auto effect = Rosen::RSTransitionEffect::Create()->Opacity(0);
        Rosen::RSAnimationTimingProtocol protocol;
        protocol.SetDuration(ANIMATION_DURATION);
        auto curve = Rosen::RSAnimationTimingCurve::LINEAR;
        Rosen::RSNode::Animate(protocol, curve, [blankRsNode, effect] {
            AceAsyncTraceBegin(0, "BlankWindowExitAnimation");
            blankRsNode->NotifyTransition(effect, false);
        }, []() {
            AceAsyncTraceEnd(0, "BlankWindowExitAnimation");
        });

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->blankWindow_, self->blankWindowName_);
        self->blankWindow_.Reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSMain] Remove blank window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());
    };
    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIBufferAvailableForBlank", TaskExecutor::TaskType::UI);
}

void WindowScene::BufferAvailableCallbackForSnapshot()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::BufferAvailableCallbackForSnapshot");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self && self->session_);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->snapshotWindow_.Reset();
        self->session_->SetNeedSnapshot(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSMain] Remove snapshot window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(
        std::move(uiTask), "ArkUIWindowSceneBufferAvailableForSnapshot", TaskExecutor::TaskType::UI);
}

void WindowScene::OnActivation()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnActivation");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self && self->session_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        bool showingInRecents = self->session_->GetShowRecent();
        self->session_->SetShowRecent(false);
        if (self->destroyed_) {
            self->destroyed_ = false;
            self->RemoveChild(host, self->startingWindow_, self->startingWindowName_);
            self->RemoveChild(host, self->appWindow_, self->appWindowName_);
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->startingWindow_.Reset();
            self->appWindow_.Reset();
            self->snapshotWindow_.Reset();
            self->session_->SetNeedSnapshot(true);
            self->OnAttachToFrameNode();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else if (showingInRecents &&
            self->session_->GetSessionState() == Rosen::SessionState::STATE_DISCONNECT && self->snapshotWindow_) {
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->snapshotWindow_.Reset();
            self->session_->SetNeedSnapshot(true);
            self->CreateStartingWindow();
            self->AddChild(host, self->startingWindow_, self->startingWindowName_);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else if (self->startingWindow_ &&
            self->session_->GetSessionState() != Rosen::SessionState::STATE_DISCONNECT) {
            auto surfaceNode = self->session_->GetSurfaceNode();
            CHECK_NULL_VOID(surfaceNode);
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            surfaceNode->SetBufferAvailableCallback(self->coldStartCallback_);
        } else if (self->snapshotWindow_) {
            self->DisposeSnapShotAndBlankWindow();
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneActivation", TaskExecutor::TaskType::UI);
}

void WindowScene::DisposeSnapShotAndBlankWindow()
{
    CHECK_NULL_VOID(session_);
    if (session_->GetBlankFlag()) {
        return;
    }
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    AddChild(host, appWindow_, appWindowName_, 0);
    surfaceNode->SetBufferAvailableCallback(hotStartCallback_);
    if (NearEqual(frameSize.Width(), session_->GetSessionLastRect().width_, 1.0f) &&
        NearEqual(frameSize.Height(), session_->GetSessionLastRect().height_, 1.0f)) {
        return;
    }
    if (!blankWindow_) {
        CreateBlankWindow();
        AddChild(host, blankWindow_, blankWindowName_);
        CleanBlankOrSnapshotWindow();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->SetIsNotifyUIBufferAvailable(true);
}

void WindowScene::OnConnect()
{
    lastWindowRect_ = session_->GetSessionRect();
    session_->SetSessionLastRect(lastWindowRect_);
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnConnect");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->session_);
        auto surfaceNode = self->session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);

        CHECK_NULL_VOID(self->appWindow_);
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(self->appWindow_->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
        self->appWindow_->ForceSyncGeometryNode();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "[WMSMain] Add app window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());

        surfaceNode->SetBufferAvailableCallback(self->coldStartCallback_);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneConnect", TaskExecutor::TaskType::UI);
}

void WindowScene::OnBackground()
{
    CHECK_NULL_VOID(session_);
    lastWindowRect_ = session_->GetSessionRect();
    session_->SetSessionLastRect(lastWindowRect_);
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
        if (!self->snapshotWindow_ && !self->startingWindow_) {
            if (snapshot) {
                self->CreateSnapshotWindow(snapshot);
                self->AddChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            } else {
                self->CreateStartingWindow();
                self->AddChild(host, self->startingWindow_, self->startingWindowName_);
            }
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneDisconnect", TaskExecutor::TaskType::UI);
}

void WindowScene::OnDrawingCompleted()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnDrawingCompleted");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->snapshotWindow_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->snapshotWindow_.Reset();
        self->session_->SetNeedSnapshot(true);
        self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneDrawingCompleted", TaskExecutor::TaskType::UI);
}

bool WindowScene::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(session_, false);
    if (attachToFrameNodeFlag_ || session_->GetBlankFlag()) {
        attachToFrameNodeFlag_ = false;
        CHECK_EQUAL_RETURN(IsMainWindow(), false, false);
        CHECK_EQUAL_RETURN(session_->GetShowRecent(), true, false);
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        CHECK_NULL_RETURN(dirty, false);
        auto size = dirty->GetGeometryNode()->GetFrameSize();
        if ((!(NearEqual(size.Width(), session_->GetSessionLastRect().width_, 1.0f) &&
            NearEqual(size.Height(), session_->GetSessionLastRect().height_, 1.0f)) && snapshotWindow_) ||
            session_->GetBlankFlag()) {
            ACE_SCOPED_TRACE("WindowScene::OnDirtyLayoutWrapperSwap");
            session_->SetBlankFlag(false);
            auto context = AceType::DynamicCast<RosenRenderContext>(appWindow_->GetRenderContext());
            CHECK_NULL_RETURN(context, false);
            context->SetOpacity(0);
            AddChild(host, appWindow_, appWindowName_, 0);
            CreateBlankWindow();
            AddChild(host, blankWindow_, blankWindowName_);
            CleanBlankOrSnapshotWindow();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        auto surfaceNode = session_->GetSurfaceNode();
        CHECK_NULL_RETURN(surfaceNode, false);
        surfaceNode->SetBufferAvailableCallback(hotStartCallback_);
        surfaceNode->SetIsNotifyUIBufferAvailable(true);
    }
    return false;
}

void WindowScene::CleanBlankOrSnapshotWindow()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    deleteWindowTask_.Cancel();
    deleteWindowTask_.Reset([weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::CleanBlankOrSnapshotWindow");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (self->snapshotWindow_) {
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->snapshotWindow_.Reset();
            self->session_->SetNeedSnapshot(true);
        }
        if (self->blankWindow_) {
            self->RemoveChild(host, self->blankWindow_, self->blankWindowName_);
            self->blankWindow_.Reset();
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
            auto context = AceType::DynamicCast<RosenRenderContext>(self->appWindow_->GetRenderContext());
            CHECK_NULL_VOID(context);
            context->SetOpacity(1);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    });
    taskExecutor->PostDelayedTask(
        deleteWindowTask_, TaskExecutor::TaskType::UI, CLEAN_WINDOW_DELAY_TIME, "ArkUICleanBlankOrSnapshotWindow");
}

uint32_t WindowScene::GetWindowPatternType() const
{
    return static_cast<uint32_t>(WindowPatternType::WINDOW_SCENE);
}
} // namespace OHOS::Ace::NG
