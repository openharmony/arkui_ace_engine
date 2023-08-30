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

#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
void SystemWindowScene::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    session_->SetUINodeId(host->GetAccessibilityId());
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);

    auto gestureHub = host->GetOrCreateGestureEventHub();
    auto touchCallback = [weakSession = wptr(session_)](TouchEventInfo& info) {
        auto session = weakSession.promote();
        CHECK_NULL_VOID(session);
        const auto pointerEvent = info.GetPointerEvent();
        CHECK_NULL_VOID(pointerEvent);
        session->TransferPointerEvent(pointerEvent);
    };
    gestureHub->SetTouchEvent(std::move(touchCallback));

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
        }
        session->TransferPointerEvent(pointerEvent);
    };
    mouseEventHub->SetMouseEvent(std::move(mouseCallback));
}

bool SystemWindowScene::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
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
} // namespace OHOS::Ace::NG
