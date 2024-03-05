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

#include "ui/rs_canvas_node.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
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
    session_->UpdateRect(windowRect, Rosen::SizeChangeReason::UNDEFINED);
}

void SystemWindowScene::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetWindowBoundary();
    session_->SetUINodeId(host->GetAccessibilityId());
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);

    if (!session_->IsSystemInput()) {
        context->SetRSNode(surfaceNode);
        surfaceNode->SetBoundsChangedCallback(boundsChangedCallback_);
    } else {
        auto rsNode = Rosen::RSCanvasNode::Create();
        context->SetRSNode(rsNode);
        rsNode->SetBoundsChangedCallback(boundsChangedCallback_);
    }

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
}

void SystemWindowScene::RegisterEventCallback()
{
    CHECK_NULL_VOID(session_);
    auto pointerEventCallback =
        [weakThis = WeakClaim(this), instanceId = instanceId_](std::shared_ptr<MMI::PointerEvent> PointerEvent) {
            ContainerScope Scope(instanceId);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->PostAsyncEvent([weakThis, PointerEvent]() {
                auto self = weakThis.Upgrade();
                auto host = self->GetHost();
                CHECK_NULL_VOID(host);
                WindowSceneHelper::InjectPointerEvent(host, PointerEvent);
            },
                TaskExecutor::TaskType::UI);
    };
    session_->SetNotifySystemSessionPointerEventFunc(std::move(pointerEventCallback));

    auto keyEventCallback = [instanceId = instanceId_](std::shared_ptr<MMI::KeyEvent> KeyEvent) {
        ContainerScope Scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->PostAsyncEvent([KeyEvent]() {
            WindowSceneHelper::InjectKeyEvent(KeyEvent);
        },
            TaskExecutor::TaskType::UI);
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

void SystemWindowScene::RegisterFocusCallback()
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
} // namespace OHOS::Ace::NG
