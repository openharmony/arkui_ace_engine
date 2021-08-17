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

#include "core/components/shape/render_shape.h"

#include "base/log/event_report.h"

namespace OHOS::Ace {

void RenderShape::Update(const RefPtr<Component>& component)
{
    auto shapeComponent = AceType::DynamicCast<ShapeComponent>(component);
    if (!shapeComponent) {
        LOGE("RenderShape update with nullptr");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    shapeType_ = shapeComponent->GetShapeType();
    topLeftRadius_ = shapeComponent->GetTopLeftRadius();
    topRightRadius_ = shapeComponent->GetTopRightRadius();
    bottomRightRadius_ = shapeComponent->GetBottomRightRadius();
    bottomLeftRadius_ = shapeComponent->GetBottomLeftRadius();
    start_ = shapeComponent->GetStart();
    end_ = shapeComponent->GetEnd();
    fillState_ = shapeComponent->GetFillState();
    strokeState_ = shapeComponent->GetStrokeState();
    antiAlias_ = shapeComponent->GetAntiAlias();
    pathCmd_ = shapeComponent->GetPathCmd();
    points_ = shapeComponent->GetPoints();
    width_ = shapeComponent->GetWidth();
    height_ = shapeComponent->GetHeight();
    MarkNeedLayout();
}

void RenderShape::PerformLayout()
{
    auto size = CalcSize();
    if (size.IsValid()) {
        size = GetLayoutParam().Constrain(size);
    }
    SetLayoutSize(size);
}

void RenderShape::OnAnimationCallback()
{
    MarkNeedLayout();
}

}; // namespace OHOS::Ace
