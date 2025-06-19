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
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFAULT_STROKE_WIDTH(1, DimensionUnit::PX);
} // namespace

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
    auto right = rect.GetRight();
    auto bottom = rect.GetBottom();
    if (NearZero(right) && NearZero(bottom)) {
        return SizeF();
    }
    auto lineWidth = static_cast<float>(paintProperty->GetStrokeWidthValue(DEFAULT_STROKE_WIDTH).ConvertToPx());
    if (NearZero(right)) {
        right += lineWidth;
    }
    if (NearZero(bottom)) {
        bottom += lineWidth;
    }

    // if width or height is matchParent
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    if (layoutProperty) {
        auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value()) {
            if (layoutPolicy->IsWidthMatch() && contentConstraint.parentIdealSize.Width().has_value()) {
                right = contentConstraint.parentIdealSize.Width().value();
            }
            if (layoutPolicy->IsHeightMatch() && contentConstraint.parentIdealSize.Height().has_value()) {
                bottom = contentConstraint.parentIdealSize.Height().value();
            }
        }
    }

    return SizeF(right, bottom);
}
} // namespace OHOS::Ace::NG
