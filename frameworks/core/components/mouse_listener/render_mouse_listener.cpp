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

#include "core/components/mouse_listener/render_mouse_listener.h"

#include "core/components/mouse_listener/mouse_listener_component.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderMouseListener::Create()
{
    return AceType::MakeRefPtr<RenderMouseListener>();
}

RenderMouseListener::RenderMouseListener() : recognizer_(AceType::MakeRefPtr<MouseRawRecognizer>()) {}

void RenderMouseListener::Update(const RefPtr<Component>& component)
{
    auto mouseComponent = AceType::DynamicCast<MouseListenerComponent>(component);
    ACE_DCHECK(mouseComponent);
    SetOnMouse(AceAsyncEvent<void(const MouseEventInfo&)>::Create(mouseComponent->GetOnMouseId(), context_));
    SetOnMouseHover(AceAsyncEvent<void()>::Create(mouseComponent->GetOnMouseHoverId(), context_));
    SetOnMouseHoverExit(AceAsyncEvent<void()>::Create(mouseComponent->GetOnMouseHoverExitId(), context_));
    // Ace 2.0
    SetOnHover(mouseComponent->GetOnHoverId());
}

void RenderMouseListener::OnMouseTestHit(const Offset& coordinateOffset, MouseRawResult& result)
{
    recognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(recognizer_);
}

void RenderMouseListener::HandleMouseHoverEvent(MouseState mouseState)
{
    if (recognizer_) {
        recognizer_->HandleHoverEvent(mouseState);
    }
}

void RenderMouseListener::UpdateTouchRect()
{
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        for (auto& rect : child->GetTouchRectList()) {
            // unified coordinate system
            Rect newRect = rect;
            newRect.SetOffset(rect.GetOffset() + GetPaintRect().GetOffset());
            touchRectList_.emplace_back(newRect);
        }
    }
}

} // namespace OHOS::Ace