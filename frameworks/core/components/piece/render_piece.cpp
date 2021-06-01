/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/piece/render_piece.h"

#include "base/log/event_report.h"
#include "core/components/box/render_box.h"
#include "core/components/image/render_image.h"
#include "core/components/text/render_text.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

void RenderPiece::Update(const RefPtr<Component>& component)
{
    const RefPtr<PieceComponent> piece = AceType::DynamicCast<PieceComponent>(component);
    if (!piece) {
        LOGE("piece component is null");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    margin_ = piece->GetMargin();
    border_ = piece->GetBorder();
    hoverColor_ = piece->GetHoverColor();
    MarkNeedLayout();
}

void RenderPiece::PerformLayout()
{
    const auto& child = GetChildren().front();
    if (!child) {
        return;
    }
    child->Layout(GetLayoutParam());
    SetLayoutSize(GetLayoutParam().Constrain(child->GetLayoutSize()));
}

void RenderPiece::OnStatusChanged(RenderStatus renderStatus)
{
    renderStatus_ = renderStatus;
}

void RenderPiece::OnPaintFinish()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (renderStatus_ == RenderStatus::FOCUS) {
        Offset offset = GetPosition();
        Size size = GetLayoutSize();
        Offset globalOffset = GetGlobalOffset();
        auto parent = GetParent().Upgrade();
        if (parent && AceType::DynamicCast<RenderBox>(parent)) {
            offset = parent->GetPosition();
            size = parent->GetLayoutSize() - margin_.GetLayoutSizeInPx(context->GetDipScale());
            globalOffset = parent->GetGlobalOffset() + margin_.GetOffsetInPx(context->GetDipScale());
        }
        RRect rrect = RRect::MakeRect(Rect(offset, size));
        rrect.SetCorner({ border_.TopLeftRadius(), border_.TopRightRadius(), border_.BottomRightRadius(),
            border_.BottomLeftRadius() });
        context->ShowFocusAnimation(rrect, Color::BLUE, globalOffset);
    }
}

bool RenderPiece::MouseHoverTest(const Point& parentLocalPoint)
{
    auto parent = GetParent().Upgrade();
    if (!parent || !AceType::DynamicCast<RenderBox>(parent)) {
        return RenderNode::MouseHoverTest(parentLocalPoint);
    }
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    if ((parent->GetTouchRect() - parent->GetTouchRect().GetOffset() + margin_.GetOffsetInPx(context->GetDipScale()))
            .IsInRegion(parentLocalPoint)) {
        if (mouseState_ == MouseState::NONE) {
            OnMouseHoverEnterTest();
            mouseState_ = MouseState::HOVER;
        }
        context->AddToHoverList(AceType::WeakClaim(this).Upgrade());
        return true;
    } else {
        if (mouseState_ == MouseState::HOVER) {
            OnMouseHoverExitTest();
            mouseState_ = MouseState::NONE;
        }
        return false;
    }
}

void RenderPiece::OnMouseHoverEnterTest()
{
    MarkNeedRender();
}

void RenderPiece::OnMouseHoverExitTest()
{
    MarkNeedRender();
}

} // namespace OHOS::Ace
