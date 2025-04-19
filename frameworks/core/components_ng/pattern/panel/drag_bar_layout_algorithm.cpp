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

#include "core/components_ng/pattern/panel/drag_bar_layout_algorithm.h"

#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension DRAG_ICON_WIDTH = 64.0_vp;
constexpr Dimension DRAG_ICON_HEIGHT = 24.0_vp;
constexpr Dimension HOT_REGION_WIDTH = 64.0_vp;
constexpr Dimension HOT_REGION_HEIGHT = 24.0_vp;
constexpr Dimension PADDING = 16.0_vp;

} // namespace

std::optional<SizeF> DragBarLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, std::nullopt);
    auto layoutProperty = AceType::DynamicCast<DragBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, std::nullopt);

    auto idealSize = CreateIdealSize(contentConstraint, Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    auto hotRegionHeight = layoutProperty->GetHotRegionHeight().value_or(HOT_REGION_HEIGHT.ConvertToPx());

    idealSize.SetWidth(static_cast<float>(HOT_REGION_WIDTH.ConvertToPx()));
    idealSize.SetHeight(static_cast<float>(hotRegionHeight));

    auto fullScreenMode = layoutProperty->GetFullScreenMode().value_or(false);
    if (fullScreenMode) {
        idealSize.SetWidth(layoutConstraint->maxSize.Width());
        idealSize.SetHeight(static_cast<float>(hotRegionHeight));
    }
    layoutProperty->UpdatePadding({ CalcLength(PADDING), CalcLength(PADDING), CalcLength(0.0f), CalcLength(0.0f) });
    auto realSize = SizeF(DRAG_ICON_WIDTH.ConvertToPx(), DRAG_ICON_HEIGHT.ConvertToPx());
    iconOffset_ = Alignment::GetAlignPosition(idealSize, realSize, Alignment::CENTER);
    return idealSize;
}

} // namespace OHOS::Ace::NG