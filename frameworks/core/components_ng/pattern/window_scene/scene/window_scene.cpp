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
const uint32_t REMOVE_STARTING_WINDOW_TIMEOUT_MS = 5000;
const int32_t ANIMATION_DURATION = 200;
const uint32_t REMOVE_SNAPSHOT_WINDOW_DELAY_TIME = 100;
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
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        ACE_SCOPED_TRACE("BufferAvailableCallback[id:%d]", session->GetPersistentId());
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "BufferAvailableCallback id:%{public}d", session->GetPersistentId());
        if (!session->GetBufferAvailable()) {
            session->SetBufferAvailable(true, false);
            Rosen::SceneSessionManager::GetInstance().NotifyCompleteFirstFrameDrawing(session->GetPersistentId());
        }
        // In a locked screen scenario, the lifetime of the session is larger than the lifetime of the object self
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        if (self->startingWindow_) {
            self->BufferAvailableCallback();
            return;
        }
        CHECK_EQUAL_VOID(self->session_->IsAnco(), true);
        if (self->snapshotWindow_) {
            self->BufferAvailableCallbackForSnapshot();
        }
        if (self->newAppWindow_ && self->appWindow_) {
            self->BufferAvailableCallback();
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
    auto rsUIContext = session_->GetRSUIContext(__func__);
    auto surfaceNode = Rosen::RSSurfaceNode::Create(
        config, Rosen::RSSurfaceNodeType::LEASH_WINDOW_NODE, true, false, rsUIContext);
    TAG_LOGD(AceLogTag::ACE_WINDOW, "Create RSSurfaceNode: %{public}s",
             WindowSceneHelper::RSNodeToStr(surfaceNode).c_str());
    CHECK_NULL_RETURN(surfaceNode, nullptr);
    surfaceNode->SetSkipCheckInMultiInstance(true);
    surfaceNode->SetLeashPersistentId(static_cast<int64_t>(session_->GetPersistentId()));
    return surfaceNode;
}

bool WindowScene::IsMainSessionRecent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto parent = host->GetParentFrameNode();
    CHECK_NULL_RETURN(parent, false);
    auto pattern = parent->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    auto windowScene = AceType::DynamicCast<WindowScene>(pattern);
    CHECK_NULL_RETURN(windowScene, false);
    CHECK_NULL_RETURN(windowScene->session_, false);
    
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "IsMainSessionRecent id:%{public}d, nodeId:%{public}d,"
        "type:%{public}d, recent:%{public}d", windowScene->session_->GetPersistentId(), host->GetId(),
        windowScene->session_->GetWindowType(), windowScene->session_->GetShowRecent());
    if (windowScene->session_->GetShowRecent()) {
        windowScene->weakSubSessions_.push_back(wptr(session_));
        return true;
    }
    return false;
}

void WindowScene::SubWindowAttachToFrameNode(sptr<Rosen::Session>& session)
{
    CHECK_NULL_VOID(session);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto surfaceNode = session->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
    surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);
    SetSubWindowBufferAvailableCallback(surfaceNode);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "SubWindowAttachToFrameNode id:%{public}d, nodeId:%{public}d, type:%{public}d, name:%{public}s",
        session->GetPersistentId(), host->GetId(), session->GetWindowType(), session->GetWindowName().c_str());
}
 
void WindowScene::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(session_);
    auto windowName = IsMainWindow() ? session_->GetSessionInfo().bundleName_ : session_->GetWindowName();
    ACE_SCOPED_TRACE("OnAttachToMainTree[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), windowName.c_str());
    if (IsMainWindow()) {
        return;
    }
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "OnAttachToMainTree id:%{public}d, nodeId:%{public}d, type:%{public}d, name:%{public}s",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), windowName.c_str());
    surfaceNode->SetVisible(IsMainSessionRecent());
}

RefPtr<RosenRenderContext> WindowScene::GetContextByDisableDelegator(bool isAbilityHook, bool isBufferAvailable)
{
    if (isAbilityHook) {
        if (isBufferAvailable) {
            return AceType::DynamicCast<RosenRenderContext>(appWindow_->GetRenderContext());
        }
        return AceType::DynamicCast<RosenRenderContext>(newAppWindow_->GetRenderContext());
    }
    if (isBufferAvailable) {
        return AceType::DynamicCast<RosenRenderContext>(startingWindow_->GetRenderContext());
    }
    return AceType::DynamicCast<RosenRenderContext>(appWindow_->GetRenderContext());
}
void WindowScene::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(session_);
    auto windowName = IsMainWindow() ? session_->GetSessionInfo().bundleName_ : session_->GetWindowName();
    ACE_SCOPED_TRACE("OnAttachToFrameNode[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), windowName.c_str());
    session_->SetAttachState(true, initWindowMode_);
    session_->SetUINodeId(host->GetAccessibilityId());
    RegisterResponseRegionCallback();

    if (!IsMainWindow()) {
        auto surfaceNode = session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
        surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);
        SetSubWindowBufferAvailableCallback(surfaceNode);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "OnAttachToFrameNode id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
            session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
        return;
    }

    auto surfaceNode = CreateLeashWindowNode();
    CHECK_NULL_VOID(surfaceNode);
    session_->SetLeashWinSurfaceNode(surfaceNode);
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
    auto windowName = IsMainWindow() ? session_->GetSessionInfo().bundleName_ : session_->GetWindowName();
    ACE_SCOPED_TRACE("OnDetachFromFrameNode[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), frameNode->GetId(), session_->GetWindowType(), windowName.c_str());
    TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE,
        "OnDetachFromFrameNode id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
        session_->GetPersistentId(), frameNode->GetId(), session_->GetWindowType(), windowName.c_str());
}

void WindowScene::OnMountToParentDone()
{
    if (snapshotWindow_) {
        snapshotWindow_->MovePosition(-1);
    }
}

void WindowScene::RegisterResponseRegionCallback()
{
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (gestureHub) {
        gestureHub->SetResponseRegionFunc(responseRegionCallback);
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
    auto transaction = session_->GetSessionRect() != windowRect ?
        WindowSceneHelper::GetRSTransaction(session_) : nullptr;
    auto ret = session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED, "OnBoundsChanged", transaction);
    auto sizeChangeReason = session_->GetSizeChangeReason();
    if ((sizeChangeReason >= Rosen::SizeChangeReason::MAXIMIZE &&
        sizeChangeReason <= Rosen::SizeChangeReason::RESIZE) ||
        sizeChangeReason == Rosen::SizeChangeReason::DRAG_MOVE) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "Update rect id:%{public}d, reason:%{public}u, rect:%{public}s",
            session_->GetPersistentId(), sizeChangeReason, windowRect.ToString().c_str());
    }
    if (ret != Rosen::WSError::WS_OK) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "Update rect failed, id: %{public}d, ret: %{public}d",
            session_->GetPersistentId(), static_cast<int32_t>(ret));
    }
}

void WindowScene::BufferAvailableCallback()
{
    bool isAbilityHook = session_->GetSessionInfo().reuseDelegatorWindow;
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "isAbilityHook: %{public}d,BufferAvailableCallback id: %{public}d,"
        "enableRemoveStartingWindow: %{public}d, appBufferReady: %{public}d",
        isAbilityHook, session_->GetPersistentId(),
        session_->GetEnableRemoveStartingWindow(), session_->GetAppBufferReady());
    auto uiTask = [weakThis = WeakClaim(this), isAbilityHook]() {
        ACE_SCOPED_TRACE("WindowScene::BufferAvailableCallback");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        if (isAbilityHook) {
            CHECK_NULL_VOID(self->appWindow_);
        } else {
            CHECK_NULL_VOID(self->startingWindow_);
        }

        CHECK_NULL_VOID(self->session_);
        if (self->session_->GetHidingStartingWindow()) {
            self->session_->SetHidingStartingWindow(false);
            self->session_->SetBufferAvailable(true, true);
        }
        auto surfaceNode = self->session_->GetSurfaceNode();
        bool isWindowSizeEqual = self->IsWindowSizeEqual();
        if (!isWindowSizeEqual || surfaceNode == nullptr || !surfaceNode->IsBufferAvailable()) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
                "BufferAvailableCallback id: %{public}d, isWindowSizeEqual: %{public}d",
                self->session_->GetPersistentId(), isWindowSizeEqual);
            return;
        }
        if (self->session_->GetSystemConfig().IsPcWindow()) {
            auto leashSurfaceNode = self->session_->GetLeashWinSurfaceNode();
            if (leashSurfaceNode) {
                leashSurfaceNode->SetUIFirstSwitch(Rosen::RSUIFirstSwitch::FORCE_DISABLE);
            }
        }
        CHECK_NULL_VOID(self->startingWindow_);
        const auto& config =
            Rosen::SceneSessionManager::GetInstance().GetWindowSceneConfig().startingWindowAnimationConfig_;
        if (config.enabled_ && self->session_->NeedStartingWindowExitAnimation()) {
            auto context = self->GetContextByDisableDelegator(isAbilityHook, true);
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
            AceAsyncTraceBeginCommercial(0, "StartingWindowExitAnimation");
            context->SetTransitionUserCallback([weakSession = wptr(self->session_)](bool) {
                AceAsyncTraceEndCommercial(0, "StartingWindowExitAnimation");
                auto session = weakSession.promote();
                CHECK_NULL_VOID(session);
                CHECK_EQUAL_VOID(session->GetSystemConfig().IsPcWindow(), false);
                auto leashSurfaceNode = session->GetLeashWinSurfaceNode();
                CHECK_NULL_VOID(leashSurfaceNode);
                leashSurfaceNode->SetUIFirstSwitch(Rosen::RSUIFirstSwitch::NONE);
            });
        }

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (isAbilityHook && self->appWindow_ && self->newAppWindow_) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "reuseDelegatorWindow from true to false");
            self->RemoveChild(host, self->appWindow_, self->appWindowName_, true);
            self->appWindow_.Reset();
            self->session_->EditSessionInfo().reuseDelegatorWindow = false;
        }
        if (self->startingWindow_ != nullptr) {
            self->RemoveChild(host, self->startingWindow_, self->startingWindowName_, true);
            self->startingWindow_.Reset();
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "Remove starting window finished, id: %{public}d, node id: %{public}d, name: %{public}s",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetSessionInfo().bundleName_.c_str());
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!isAbilityHook && session_->GetEnableRemoveStartingWindow() && !session_->GetAppBufferReady()) {
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        removeStartingWindowTask_.Cancel();
        removeStartingWindowTask_.Reset(uiTask);
        taskExecutor->PostDelayedTask(removeStartingWindowTask_, TaskExecutor::TaskType::UI,
            REMOVE_STARTING_WINDOW_TIMEOUT_MS, "ArkUIWindowSceneBufferAvailableDelayedCallback");
    } else {
        pipelineContext->PostAsyncEvent(
            std::move(uiTask), "ArkUIWindowSceneBufferAvailableCallback", TaskExecutor::TaskType::UI);
    }
}

void WindowScene::BufferAvailableCallbackForBlank(bool fromMainThread)
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::BufferAvailableCallbackForBlank");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->blankWindow_);
        auto surfaceNode = self->session_->GetSurfaceNode();
        if (surfaceNode) {
            surfaceNode->SetVisible(true);
        }

        self->SetOpacityAnimation(self->blankWindow_);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->blankWindow_, self->blankWindowName_, true);
        self->blankWindow_.Reset();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    CHECK_EQUAL_RETURN(fromMainThread, true, uiTask());
    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(
        std::move(uiTask), "ArkUIBufferAvailableCallbackForBlank", TaskExecutor::TaskType::UI);
}

void WindowScene::SetSubSessionVisible()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (auto& weakSubSession : weakSubSessions_) {
        auto subSession = weakSubSession.promote();
        if (subSession) {
            auto surfaceNode = subSession->GetSurfaceNode();
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
                "SetSubSessionVisible id:%{public}d, nodeId:%{public}d, name:%{public}s",
                subSession->GetPersistentId(), host->GetId(), subSession->GetSessionInfo().bundleName_.c_str());
            if (surfaceNode) {
                surfaceNode->SetVisible(true);
            }
        }
    }
    weakSubSessions_.clear();
}

void WindowScene::BufferAvailableCallbackForSnapshot()
{
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "BufferAvailableCallbackForSnapshot id:%{public}d", session_->GetPersistentId());
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::BufferAvailableCallbackForSnapshot");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->snapshotWindow_);
        if (self->isBlankForSnapshot_) {
            self->SetOpacityAnimation(self->snapshotWindow_);
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "blank animation id %{public}d, name %{public}s",
                self->session_->GetPersistentId(), self->session_->GetSessionInfo().bundleName_.c_str());
        }
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->snapshotWindow_.Reset();
        self->session_->SetNeedSnapshot(true);
        self->SetSubSessionVisible();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (Rosen::SceneSessionManager::GetInstance().GetDelayRemoveSnapshot()) {
        Rosen::SceneSessionManager::GetInstance().SetDelayRemoveSnapshot(false);
        removeSnapshotWindowTask_.Cancel();
        removeSnapshotWindowTask_.Reset(uiTask);
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(removeSnapshotWindowTask_, TaskExecutor::TaskType::UI,
            REMOVE_SNAPSHOT_WINDOW_DELAY_TIME, "ArkUIWindowSceneBufferAvailableDelayedCallback");
    } else {
        pipelineContext->PostAsyncEvent(
            std::move(uiTask), "ArkUIWindowSceneBufferAvailableCallbackForSnapshot", TaskExecutor::TaskType::UI);
    }
}

void WindowScene::OnActivation()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnActivation");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        bool showingInRecents = self->session_->GetShowRecent();
        self->session_->SetShowRecent(false);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (self->destroyed_) {
            self->destroyed_ = false;
            self->RemoveChild(host, self->startingWindow_, self->startingWindowName_);
            self->RemoveChild(host, self->appWindow_, self->appWindowName_);
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->RemoveChild(host, self->blankWindow_, self->blankWindowName_);
            self->RemoveChild(host, self->newAppWindow_, self->newAppWindowName_);
            self->startingWindow_.Reset();
            self->appWindow_.Reset();
            self->snapshotWindow_.Reset();
            self->newAppWindow_.Reset();
            self->session_->SetNeedSnapshot(true);
            self->blankWindow_.Reset();
            self->SetSubSessionVisible();
            self->OnAttachToFrameNode();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else if (showingInRecents &&
            self->session_->GetSessionState() == Rosen::SessionState::STATE_DISCONNECT && self->snapshotWindow_) {
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->snapshotWindow_.Reset();
            self->session_->SetNeedSnapshot(true);
            self->SetSubSessionVisible();
            self->CreateStartingWindow();
            self->AddChild(host, self->startingWindow_, self->startingWindowName_);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else if (self->startingWindow_ &&
            self->session_->GetSessionState() != Rosen::SessionState::STATE_DISCONNECT) {
            auto surfaceNode = self->session_->GetSurfaceNode();
            CHECK_NULL_VOID(surfaceNode);
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            surfaceNode->SetBufferAvailableCallback(self->callback_);
        } else if (self->snapshotWindow_) {
            self->session_->SetEnableAddSnapshot(true);
            self->DisposeSnapshotAndBlankWindow();
            self->SetSubSessionVisible();
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneActivation", TaskExecutor::TaskType::UI);
}

void WindowScene::DisposeSnapshotAndBlankWindow()
{
    CHECK_NULL_VOID(session_);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "DisposeSnapshotAndBlankWindow id: %{public}d", session_->GetPersistentId());
    if (session_->GetBlank()) {
        return;
    }
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AddChild(host, appWindow_, appWindowName_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->SetBufferAvailableCallback(callback_);
    CHECK_EQUAL_VOID(session_->GetSystemConfig().IsPcWindow(), true);
    CHECK_EQUAL_VOID(session_->GetSystemConfig().freeMultiWindowEnable_, true);
    CHECK_EQUAL_VOID(IsWindowSizeEqual(), true);
    RemoveChild(host, snapshotWindow_, snapshotWindowName_);
    snapshotWindow_.Reset();
    session_->SetNeedSnapshot(true);
    SetSubSessionVisible();
    if (!blankWindow_) {
        CreateBlankWindow(blankWindow_);
        AddChild(host, blankWindow_, blankWindowName_);
        CleanBlankWindow();
    }
}

void WindowScene::OnConnect()
{
    bool isAbilityHook = session_->GetSessionInfo().reuseDelegatorWindow;
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "isAbilityHook: %{public}d", isAbilityHook);
    auto uiTask = [weakThis = WeakClaim(this), isAbilityHook]() {
        ACE_SCOPED_TRACE("WindowScene::OnConnect");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        CHECK_NULL_VOID(self->session_);
        auto surfaceNode = self->session_->GetSurfaceNode();
        CHECK_NULL_VOID(surfaceNode);

        if (isAbilityHook) {
            self->CreateAppWindow();
            CHECK_NULL_VOID(self->newAppWindow_);
        } else {
            CHECK_NULL_VOID(self->appWindow_);
        }
        auto context = self->GetContextByDisableDelegator(isAbilityHook, false);
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);

        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto frameSize = geometryNode->GetFrameSize();
        RectF windowRect(0, 0, frameSize.Width(), frameSize.Height());
        context->SyncGeometryProperties(windowRect);

        if (isAbilityHook) {
            self->AddChild(host, self->newAppWindow_, self->newAppWindowName_, 0);
        } else {
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "Add app window finished, id: %{public}d, node id: %{public}d, "
            "name: %{public}s, rect: %{public}s", self->session_->GetPersistentId(), host->GetId(),
            self->session_->GetSessionInfo().bundleName_.c_str(), windowRect.ToString().c_str());

        surfaceNode->SetBufferAvailableCallback(self->callback_);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneConnect", TaskExecutor::TaskType::UI);
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

void WindowScene::OnLayoutFinished()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        ACE_SCOPED_TRACE("WindowScene::OnLayoutFinished[id:%d][self:%d][enabled:%d]",
            self->session_->GetPersistentId(), host->GetId(), self->session_->GetBufferAvailableCallbackEnable());
        if (self->startingWindow_ && (!self->session_->GetShowRecent())) {
            self->BufferAvailableCallback();
            return;
        }
        CHECK_EQUAL_VOID(self->session_->IsAnco(), true);
        if (self->session_->GetBufferAvailableCallbackEnable()) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "buffer available callback enable is true, no need remove blank.");
            return;
        }
        CHECK_EQUAL_VOID(self->IsWindowSizeEqual(), false);
        if (self->blankWindow_) {
            self->BufferAvailableCallbackForBlank(true);
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneLayoutFinished", TaskExecutor::TaskType::UI);
}

void WindowScene::OnDrawingCompleted()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::OnDrawingCompleted");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);

        if (self->blankWindow_) {
            self->BufferAvailableCallbackForBlank(true);
            return;
        }
        CHECK_NULL_VOID(self->snapshotWindow_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->snapshotWindow_.Reset();
        self->session_->SetNeedSnapshot(true);
        self->SetSubSessionVisible();
        self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneDrawingCompleted", TaskExecutor::TaskType::UI);
}

void WindowScene::OnRemoveBlank()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        if (self->blankWindow_) {
            self->BufferAvailableCallbackForBlank(true);
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneRemoveBlank", TaskExecutor::TaskType::UI);
}

void WindowScene::OnAddSnapshot()
{
    int32_t imageFit = 0;
    auto isPersistentImageFit = Rosen::SceneSessionManager::GetInstance().GetPersistentImageFit(
        session_->GetPersistentId(), imageFit);
    auto uiTask = [weakThis = WeakClaim(this), isPersistentImageFit]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        CHECK_NULL_VOID(self->session_);
        CHECK_EQUAL_VOID(self->session_->GetEnableAddSnapshot(), false);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (self->snapshotWindow_ || self->startingWindow_ || self->blankWindow_) {
            TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "In snap/start/blank window id %{public}d host id %{public}d",
                self->session_->GetPersistentId(), host->GetId());
            return;
        }
        if (isPersistentImageFit && self->session_->GetSnapshot() == nullptr) {
            self->CreateSnapshotWindow();
        } else {
            self->CreateSnapshotWindow(self->session_->GetSnapshot());
        }
        self->AddChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->RemoveChild(host, self->appWindow_, self->appWindowName_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "OnAddSnapshot id %{public}d host id %{public}d", self->session_->GetPersistentId(), host->GetId());
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneAddSnapshot", TaskExecutor::TaskType::UI);
}

void WindowScene::OnRemoveSnapshot()
{
    int32_t imageFit = 0;
    auto isPersistentImageFit = Rosen::SceneSessionManager::GetInstance().GetPersistentImageFit(
        session_->GetPersistentId(), imageFit);
    auto uiTask = [weakThis = WeakClaim(this), isPersistentImageFit]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        CHECK_NULL_VOID(self->session_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (self->snapshotWindow_) {
            if (isPersistentImageFit) {
                self->SetSubSessionVisible();
            }
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
            auto surfaceNode = self->session_->GetSurfaceNode();
            CHECK_NULL_VOID(surfaceNode);
            if (!surfaceNode->IsBufferAvailable()) {
                TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "OnRemoveSnapshot not IsBufferAvailable");
                surfaceNode->SetBufferAvailableCallback(self->callback_);
                return;
            }
            self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
            self->snapshotWindow_.Reset();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
                "OnRemoveSnapshot id %{public}d host id %{public}d", self->session_->GetPersistentId(), host->GetId());
        }
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(std::move(uiTask), "ArkUIWindowSceneRemoveSnapshot", TaskExecutor::TaskType::UI);
}

void WindowScene::OnAppRemoveStartingWindow()
{
    CHECK_EQUAL_VOID(session_->GetEnableRemoveStartingWindow(), false);
    session_->SetAppBufferReady(true);
    BufferAvailableCallback();
}

void WindowScene::OnUpdateSnapshotWindow()
{
    auto uiTask = [weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        CHECK_NULL_VOID(self->snapshotWindow_);
        CHECK_NULL_VOID(self->session_);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        self->RemoveChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        self->snapshotWindow_.Reset();
        self->CreateSnapshotWindow();
        self->AddChild(host, self->snapshotWindow_, self->snapshotWindowName_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "OnUpdateSnapshotWindow id %{public}d host id %{public}d",
            self->session_->GetPersistentId(), host->GetId());
    };

    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(
        std::move(uiTask), "ArkUIWindowSceneUpdateSnapshotWindow", TaskExecutor::TaskType::UI);
}

bool WindowScene::IsWindowSizeEqual()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto frameSize = geometryNode->GetFrameSize();
    ACE_SCOPED_TRACE("WindowScene::IsWindowSizeEqual[id:%d][self:%d][%s][%s]",
        session_->GetPersistentId(), host->GetId(),
        frameSize.ToString().c_str(), session_->GetLayoutRect().ToString().c_str());
    if (NearEqual(frameSize.Width(), session_->GetLayoutRect().width_, 1.0f) &&
        NearEqual(frameSize.Height(), session_->GetLayoutRect().height_, 1.0f)) {
        return true;
    }
    return false;
}

bool WindowScene::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_EQUAL_RETURN(IsMainWindow(), false, false);
    CHECK_EQUAL_RETURN(attachToFrameNodeFlag_ || session_->GetBlank(), false, false);
    attachToFrameNodeFlag_ = false;
    CHECK_EQUAL_RETURN(session_->GetShowRecent() && !session_->GetBlank(), true, false);
    auto surfaceNode = session_->GetSurfaceNode();
    if (surfaceNode) {
        surfaceNode->SetBufferAvailableCallback(callback_);
    }
    CHECK_EQUAL_RETURN(session_->GetSystemConfig().IsPcWindow(), true, false);
    CHECK_EQUAL_RETURN(session_->GetSystemConfig().freeMultiWindowEnable_, true, false);
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto size = geometryNode->GetFrameSize();
    ACE_SCOPED_TRACE("WindowSCENE::OnDirtyLayoutWrapperSwap[id:%d][%f %f][%d %d][blank:%d]",
        session_->GetPersistentId(), size.Width(), size.Height(),
        session_->GetLayoutRect().width_, session_->GetLayoutRect().height_, session_->GetBlank());
    if (NearEqual(size.Width(), session_->GetLayoutRect().width_, 1.0f) &&
        NearEqual(size.Height(), session_->GetLayoutRect().height_, 1.0f) && !session_->GetBlank()) {
        return false;
    }
    session_->SetBlank(false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    RemoveChild(host, snapshotWindow_, snapshotWindowName_);
    snapshotWindow_.Reset();
    session_->SetNeedSnapshot(true);
    SetSubSessionVisible();
    RemoveChild(host, startingWindow_, startingWindowName_);
    startingWindow_.Reset();
    AddChild(host, appWindow_, appWindowName_, 0);
    if (surfaceNode) {
        surfaceNode->SetVisible(false);
    }
    if (!blankWindow_) {
        CreateBlankWindow(blankWindow_);
        AddChild(host, blankWindow_, blankWindowName_);
        auto blankWindowContext = blankWindow_->GetRenderContext();
        CHECK_NULL_RETURN(blankWindowContext, false);
        blankWindowContext->SyncGeometryProperties(RectF(0, 0, size.Width(), size.Height()));
        blankWindow_->SetActive(true);
        CleanBlankWindow();
    }
    host->RebuildRenderContextTree();
    return false;
}

void WindowScene::CleanBlankWindow()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    deleteWindowTask_.Cancel();
    deleteWindowTask_.Reset([weakThis = WeakClaim(this)]() {
        ACE_SCOPED_TRACE("WindowScene::CleanBlankWindow");
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        if (self->blankWindow_) {
            self->RemoveChild(host, self->blankWindow_, self->blankWindowName_);
            self->blankWindow_.Reset();
            self->AddChild(host, self->appWindow_, self->appWindowName_, 0);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto surfaceNode = self->session_->GetSurfaceNode();
            CHECK_NULL_VOID(surfaceNode);
            surfaceNode->SetVisible(true);
        }
    });
    taskExecutor->PostDelayedTask(
        deleteWindowTask_, TaskExecutor::TaskType::UI, CLEAN_WINDOW_DELAY_TIME, "ArkUICleanBlankWindow");
}

uint32_t WindowScene::GetWindowPatternType() const
{
    return static_cast<uint32_t>(WindowPatternType::WINDOW_SCENE);
}

void WindowScene::SetSubWindowBufferAvailableCallback(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    CHECK_NULL_VOID(surfaceNode);
    auto subWindowCallback = [weakSession = wptr(session_), weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent([weakThis, weakSession]() {
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            auto host = self->GetHost();
            CHECK_NULL_VOID(host);
            auto session = weakSession.promote();
            CHECK_NULL_VOID(session);
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
                "subWindowBufferAvailable id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
                session->GetPersistentId(), host->GetId(), session->GetWindowType(), session->GetWindowName().c_str());
            session->SetBufferAvailable(true);
        },
            "ArkUIWindowSceneSubWindowBufferAvailable", TaskExecutor::TaskType::UI);
    };
    surfaceNode->SetBufferAvailableCallback(subWindowCallback);
}

void WindowScene::SetOpacityAnimation(RefPtr<FrameNode>& window)
{
    RefPtr<Curve> curve = Curves::LINEAR;
    auto effect = AceType::MakeRefPtr<ChainedOpacityEffect>(0);
    effect->SetAnimationOption(std::make_shared<AnimationOption>(curve, ANIMATION_DURATION));
    auto context = window->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateChainedTransition(effect);
}
} // namespace OHOS::Ace::NG
