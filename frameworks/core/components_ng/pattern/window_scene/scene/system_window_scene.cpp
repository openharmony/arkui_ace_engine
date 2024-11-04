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

#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"

#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DELAY_TIME = 3000;
} // namespace

SystemWindowScene::SystemWindowScene(const sptr<Rosen::Session>& session) : session_(session)
{
    boundsChangedCallback_ = [weakThis = WeakClaim(this)](const Rosen::Vector4f& bounds) {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        self->OnBoundsChanged(bounds);
    };
}

sptr<Rosen::Session> SystemWindowScene::GetSession()
{
    return session_;
}

void SystemWindowScene::OnBoundsChanged(const Rosen::Vector4f& bounds)
{
    Rosen::WSRect windowRect {
        .posX_ = std::round(bounds.x_),
        .posY_ = std::round(bounds.y_),
        .width_ = std::round(bounds.z_),
        .height_ = std::round(bounds.w_),
    };

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
    auto ret = session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED, "OnBoundsChanged");
    if (ret != Rosen::WSError::WS_OK) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "Update rect failed, ret: %{public}d", static_cast<int32_t>(ret));
    }
}

void SystemWindowScene::OnVisibleChange(bool visible)
{
    CHECK_NULL_VOID(session_);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "Visibility of %{public}s[id:%{public}d] changed: %{public}s",
        session_->GetSessionInfo().bundleName_.c_str(), session_->GetPersistentId(), visible ? "visible" : "invisible");
    if (visible && session_->NeedCheckContextTransparent()) {
        PostCheckContextTransparentTask();
    } else if (session_->NeedCheckContextTransparent()) {
        checkContextTransparentTask_.Cancel();
    }
    if (SystemProperties::GetFaultInjectEnabled() && session_->NeedCheckContextTransparent()) {
        PostFaultInjectTask();
    }
}

void SystemWindowScene::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(session_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("OnAttachToFrameNode[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "OnAttachToFrameNode id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
        session_->GetPersistentId(), host->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());

    host->SetWindowBoundary();
    session_->SetUINodeId(host->GetAccessibilityId());
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
    surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);

    auto mouseEventHub = host->GetOrCreateInputEventHub();
    auto mouseCallback = [weakThis = WeakClaim(this), weakSession = wptr(session_)](MouseInfo& info) {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        const auto pointerEvent = info.GetPointerEvent();
        CHECK_NULL_VOID(pointerEvent);
        auto host = self->GetHost();
        if (host != nullptr) {
            DelayedSingleton<WindowEventProcess>::GetInstance()->ProcessWindowMouseEvent(
                host->GetId(), session, pointerEvent);
            DelayedSingleton<WindowEventProcess>::GetInstance()->ProcessWindowDragEvent(
                host->GetId(), session, pointerEvent);
        }
        session->TransferPointerEvent(pointerEvent);
    };
    mouseEventHub->SetMouseEvent(std::move(mouseCallback));

    RegisterFocusCallback();
    RegisterEventCallback();
    RegisterResponseRegionCallback();

    if (session_->NeedCheckContextTransparent()) {
        PostCheckContextTransparentTask();
    }
    SetWindowScenePosition();
}

void SystemWindowScene::SetWindowScenePosition()
{
    // set window scene position (x, y) and jsAccessibilityManager will use it
    CHECK_NULL_VOID(session_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetGetWindowScenePosition([weakSession = wptr(session_)] (int32_t& left, int32_t& top) {
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        auto windowRect = session->GetSessionGlobalRect();
        left = windowRect.posX_;
        top = windowRect.posY_;
    });
}

void SystemWindowScene::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(frameNode);
    ACE_SCOPED_TRACE("OnDetachFromFrameNode[id:%d][self:%d][type:%d][name:%s]",
        session_->GetPersistentId(), frameNode->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
        "OnDetachFromFrameNode id: %{public}d, node id: %{public}d, type: %{public}d, name: %{public}s",
        session_->GetPersistentId(), frameNode->GetId(), session_->GetWindowType(), session_->GetWindowName().c_str());
    if (session_->NeedCheckContextTransparent()) {
        checkContextTransparentTask_.Cancel();
    }
    session_->SetNotifySystemSessionKeyEventFunc(nullptr);
}

void SystemWindowScene::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetIsNeedRebuildRSTree(true);
}

void SystemWindowScene::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetIsNeedRebuildRSTree(false);
}

void SystemWindowScene::RegisterEventCallback()
{
    CHECK_NULL_VOID(session_);
    auto pointerEventCallback =
        [weakThis = WeakClaim(this), instanceId = instanceId_](std::shared_ptr<MMI::PointerEvent> PointerEvent) {
            ContainerScope Scope(instanceId);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            if (!pipelineContext) {
                TAG_LOGE(AceLogTag::ACE_INPUTTRACKING,
                    "PipelineContext GetCurrentContext null,id:%{public}d", PointerEvent->GetId());
                PointerEvent->MarkProcessed();
                return;
            }
            auto taskExecutor = pipelineContext->GetTaskExecutor();
            if (!taskExecutor) {
                TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "taskExecutor is null,id:%{public}d", PointerEvent->GetId());
                PointerEvent->MarkProcessed();
                return;
            }
            taskExecutor->PostTask([weakThis, PointerEvent]() {
                auto self = weakThis.Upgrade();
            if (!self) {
                TAG_LOGE(AceLogTag::ACE_INPUTTRACKING,
                    "weakThis Upgrade null,id:%{public}d", PointerEvent->GetId());
                PointerEvent->MarkProcessed();
                return;
            }
                auto host = self->GetHost();
            if (!host) {
                TAG_LOGE(AceLogTag::ACE_INPUTTRACKING,
                    "GetHost null,id:%{public}d", PointerEvent->GetId());
                PointerEvent->MarkProcessed();
                return;
            }
                WindowSceneHelper::InjectPointerEvent(host, PointerEvent);
            },
                TaskExecutor::TaskType::UI, "ArkUIWindowInjectPointerEvent", PriorityType::VIP);
    };
    session_->SetNotifySystemSessionPointerEventFunc(std::move(pointerEventCallback));
    auto keyEventCallback = [weakThis = WeakClaim(this), instanceId = instanceId_](
        std::shared_ptr<MMI::KeyEvent> keyEvent, bool isPreImeEvent) -> bool {
        CHECK_NULL_RETURN(keyEvent, false);
        auto self = weakThis.Upgrade();
        CHECK_NULL_RETURN(self, false);
        ContainerScope Scope(instanceId);
        return WindowSceneHelper::InjectKeyEvent(keyEvent, isPreImeEvent);
    };
    session_->SetNotifySystemSessionKeyEventFunc(std::move(keyEventCallback));
}

void SystemWindowScene::RegisterResponseRegionCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weakSession = wptr(session_)](TouchEventInfo& info) {
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        const auto pointerEvent = info.GetPointerEvent();
        CHECK_NULL_VOID(pointerEvent);
        session->TransferPointerEvent(pointerEvent);
    };
    gestureHub->SetTouchEvent(std::move(touchCallback));

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
    gestureHub->SetResponseRegionFunc(responseRegionCallback);
}

uint32_t SystemWindowScene::GetWindowPatternType() const
{
    return static_cast<uint32_t>(WindowPatternType::SYSTEM_WINDOW_SCENE);
}

void SystemWindowScene::RegisterFocusCallback()
{
    CHECK_NULL_VOID(session_);

    auto requestFocusCallback = [weakThis = WeakClaim(this), frameNode = frameNode_, instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->SetFocusedWindowSceneNode(frameNode);
        pipelineContext->PostAsyncEvent([weakThis]() {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->SetIsFocusActive(false);
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            self->FocusViewShow();
        }, "ArkUIWindowFocusViewShow", TaskExecutor::TaskType::UI);
    };
    session_->SetNotifyUIRequestFocusFunc(requestFocusCallback);

    auto lostFocusCallback = [weakThis = WeakClaim(this), instanceId = instanceId_]() {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent([weakThis]() {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            CHECK_NULL_VOID(self->GetSession());
            pipeline->RestoreDefault(self->GetSession()->GetPersistentId());
        }, "ArkUIWindowLostFocus", TaskExecutor::TaskType::UI);
    };
    session_->SetNotifyUILostFocusFunc(lostFocusCallback);
}

void SystemWindowScene::LostViewFocus()
{
    TAG_LOGI(
        AceLogTag::ACE_FOCUS, "Focus view: %{public}s/%{public}d lost focus", GetFrameName().c_str(), GetFrameId());
    auto focusHub = GetFocusHub();
    if (!focusHub || !focusHub->IsCurrentFocus()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto screenNode = pipeline->GetScreenNode();
    CHECK_NULL_VOID(screenNode);
    auto screenNodeFocusHub = screenNode->GetFocusHub();
    CHECK_NULL_VOID(screenNodeFocusHub);
    screenNodeFocusHub->LostFocus(BlurReason::VIEW_SWITCH);
}

void SystemWindowScene::PostCheckContextTransparentTask()
{
    checkContextTransparentTask_.Reset([weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        CHECK_NULL_VOID(self->GetHost());
        CHECK_NULL_VOID(self->session_);
        if (self->session_->NeedCheckContextTransparent() && self->GetHost()->IsContextTransparent()) {
            self->session_->NotifyContextTransparent();
        }
    });

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(std::move(checkContextTransparentTask_), TaskExecutor::TaskType::UI,
        DELAY_TIME, "ArkUIWindowCheckContextTransparent");
}

void SystemWindowScene::PostFaultInjectTask()
{
    auto task = ([weakThis = WeakClaim(this)]() {
        auto self = weakThis.Upgrade();
        CHECK_NULL_VOID(self);
        auto host = self->GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
        renderContext->SetOpacity(0.0f);
        host->MarkDirtyNode();
    });

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        std::move(task), TaskExecutor::TaskType::UI, DELAY_TIME, "ArkUIWindowFaultInject");
}
} // namespace OHOS::Ace::NG
