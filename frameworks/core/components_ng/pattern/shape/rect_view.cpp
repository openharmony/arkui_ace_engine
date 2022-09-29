/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/rect_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/rect_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void RectView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RectPattern>(); });
    stack->Push(frameNode);
}

void RectView::SetRadiusWidth(const Dimension& value)
{
    Radius radius;
    radius.SetX(value);
    UpdateRadius(radius);
}

void RectView::SetRadiusHeight(const Dimension& value)
{
    Radius radius;
    radius.SetY(value);
    UpdateRadius(radius);
}

void RectView::UpdateRadius(const Radius& radius)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto castRectPaintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    if (castRectPaintProperty) {
        castRectPaintProperty->UpdateTopLeftRadius(radius);
        castRectPaintProperty->UpdateTopRightRadius(radius);
        castRectPaintProperty->UpdateBottomLeftRadius(radius);
        castRectPaintProperty->UpdateBottomRightRadius(radius);
    }
}

void RectView::SetTopLeftRadius(const Radius& topLeftRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(RectPaintProperty, TopLeftRadius, topLeftRadius);
}

void RectView::SetTopRightRadius(const Radius& topRightRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(RectPaintProperty, TopRightRadius, topRightRadius);
}

void RectView::SetBottomLeftRadius(const Radius& bottomLeftRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(RectPaintProperty, BottomLeftRadius, bottomLeftRadius);
}

void RectView::SetBottomRightRadius(const Radius& bottomRightRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(RectPaintProperty, BottomRightRadius, bottomRightRadius);
}

} // namespace OHOS::Ace::NG