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

#include "core/components_ng/pattern/shape/path_layout_algorithm.h"

#include "include/utils/SkParsePath.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/path_paint_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFAULT_STROKE_WIDTH(1, DimensionUnit::PX);
} // namespace
void PathLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Measure(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    OptionalSizeF frameSize =
        UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(contentSize.Width(), contentSize.Height()),
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
    if (layoutPolicy->IsWidthFix()) {
        layoutWrapper->GetGeometryNode()->SetFrameWidth(frameSize.Width().value_or(-1));
    }
    if (layoutPolicy->IsHeightFix()) {
        layoutWrapper->GetGeometryNode()->SetFrameHeight(frameSize.Height().value_or(-1));
    }
}

std::optional<SizeF> PathLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto paintProperty = host->GetPaintProperty<PathPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, std::nullopt);
    if (propertiesFromAncestor_) {
        paintProperty->UpdateShapeProperty(propertiesFromAncestor_);
    }

    auto pathCommands = paintProperty->GetCommandsValue("");
    CHECK_NULL_RETURN(!pathCommands.empty(), SizeF());
    RSPath path;
    bool ret = path.BuildFromSVGString(pathCommands.c_str());
    CHECK_NULL_RETURN(ret, SizeF());
    auto rect = path.GetBounds();
    SizeF size = SizeF(rect.GetRight(), rect.GetBottom());
    if (NearZero(size.Width()) && NearZero(size.Height())) {
        return SizeF();
    }
    auto lineWidth = static_cast<float>(paintProperty->GetStrokeWidthValue(DEFAULT_STROKE_WIDTH).ConvertToPx());
    if (NearZero(size.Width())) {
        size.SetWidth(lineWidth + size.Width());
    }
    if (NearZero(size.Height())) {
        size.SetHeight(lineWidth + size.Height());
    }
    MeasureLayoutPolicySize(contentConstraint, layoutWrapper, size);
    return size;
}

void PathLayoutAlgorithm::MeasureLayoutPolicySize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, SizeF& size)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    const std::optional<float>& parentIdealSizeWidth = contentConstraint.parentIdealSize.Width();
    const std::optional<float>& parentIdealSizeHeight = contentConstraint.parentIdealSize.Height();
    if (layoutPolicy->IsWidthMatch() && parentIdealSizeWidth.has_value()) {
        size.SetWidth(parentIdealSizeWidth.value());
    }
    if (layoutPolicy->IsHeightMatch() && parentIdealSizeHeight.has_value()) {
        size.SetHeight(parentIdealSizeHeight.value());
    }
}
} // namespace OHOS::Ace::NG
