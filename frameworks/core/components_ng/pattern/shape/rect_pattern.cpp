/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/rect_pattern.h"

#include "core/components_ng/pattern/shape/rect_paint_method.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"

namespace OHOS::Ace::NG {

RefPtr<NodePaintMethod> RectPattern::CreateNodePaintMethod()
{
    if (!shapeOverlayModifier_) {
        shapeOverlayModifier_ = MakeRefPtr<ShapeOverlayModifier>();
    }
    return MakeRefPtr<RectPaintMethod>(GetAncestorPaintProperty(), shapeOverlayModifier_);
}

RefPtr<PaintProperty> RectPattern::CreatePaintProperty()
{
    return MakeRefPtr<RectPaintProperty>();
}

void RectPattern::OnPixelRoundFinish(const SizeF& pixelGridRoundSize)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pixelRoundContentOffset = geometryNode->GetPixelRoundContentOffset();
    auto pixelRoundContentSize = geometryNode->GetPixelRoundContentSize();
    auto rectPaintProperty = host->GetPaintProperty<RectPaintProperty>();
    CHECK_NULL_VOID(rectPaintProperty);
    rectPaintProperty->SetContentOffset(pixelRoundContentOffset);
    rectPaintProperty->SetContentSize(pixelRoundContentSize);
}

} // namespace OHOS::Ace::NG
