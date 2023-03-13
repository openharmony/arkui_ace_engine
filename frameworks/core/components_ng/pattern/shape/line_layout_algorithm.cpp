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

#include "core/components_ng/pattern/shape/line_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/line_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFAULT_STROKE_WIDTH(1, DimensionUnit::PX);
} // namespace
std::optional<SizeF> LineLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // When the width and height are not specified, the content size is determined based on the start and end points
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto paintProperty = host->GetPaintProperty<LinePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, std::nullopt);

    auto strokewidth = static_cast<float>(paintProperty->GetStrokeWidthValue(DEFAULT_STROKE_WIDTH).ConvertToPx());
    if (paintProperty->HasStrokeWidth()) {
        strokewidth = paintProperty->GetStrokeWidthValue().ConvertToPx();
    }

    PointF startPoint = PointF(paintProperty->GetStartPointValue().first.ConvertToPx(),
        paintProperty->GetStartPointValue().second.ConvertToPx());
    PointF endPoint = PointF(
        paintProperty->GetEndPointValue().first.ConvertToPx(), paintProperty->GetEndPointValue().second.ConvertToPx());

    auto width = startPoint.GetX() > endPoint.GetX() ? startPoint.GetX()
                                                     : endPoint.GetX();
    auto height = startPoint.GetY() > endPoint.GetY() ? startPoint.GetY()
                                                      : endPoint.GetY();
    if (NearZero(width)) {
        width = strokewidth;
    }
    if (NearZero(height)) {
        height = strokewidth;
    }

    return SizeF(width, height);
}
} // namespace OHOS::Ace::NG

