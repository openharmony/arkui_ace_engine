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

#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void SwiperLayoutAlgorithm::UpdateChildConstraint(const SizeF& selfIdealSize, LayoutConstraintF& layoutConstraint, 
    const RefPtr<SwiperLayoutProperty>& layoutProperty)
{
    layoutConstraint.parentIdealSize = selfIdealSize;
    layoutConstraint.selfIdealSize->Reset();
    layoutConstraint.UpdateSelfIdealSizeWithCheck(SizeF(100.0, -1));
}

void SwiperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    preEndIndex_ = 0;
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);

    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto idealSize = CreateIdealSize(swiperLayoutProperty->GetLayoutConstraint().value(), axis,
        swiperLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);

    // Measure children.
    auto layoutConstraint = swiperLayoutProperty->CreateChildConstraint();
    UpdateChildConstraint(idealSize, layoutConstraint.value(), swiperLayoutProperty);
    LOGE("CCCC UpdateChildConstraint max: %{public}s, min: %{public}s, selfIdeaSize: %{public}s, parentIdeaSize: %{public}s",
        layoutConstraint->maxSize.ToString().c_str(), layoutConstraint->minSize.ToString().c_str(),
        layoutConstraint->selfIdealSize->ToString().c_str(), layoutConstraint->parentIdealSize->ToString().c_str());

    auto currentIndex = preStartIndex_ - 1;
    auto totalCount = layoutWrapper->GetTotalChildCount();
    do {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(++currentIndex);
        if (!wrapper) {
            LOGE("the start %{public}d index wrapper is null", currentIndex);
            break;
        }

        {
            ACE_SCOPED_TRACE("SwiperLayoutAlgorithm::Measure child");
            wrapper->Measure(layoutConstraint);
        }
    } while (currentIndex < totalCount);

    startIndex_ = 0;
    endIndex_ = totalCount - 1;
}

void SwiperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto childrenSize = layoutWrapper->GetTotalChildCount();

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout chilren.
    for (auto index = startIndex_.value(); index <= endIndex_.value(); ++index) {
        // When enable loop, adjust offset.
        auto loopIndex = index;
        if (currentIndex_ == 0 && GreatNotEqual(currentOffset_, 0.0) && index == childrenSize - 1) {
            loopIndex = -1;
        } else if (currentIndex_ == childrenSize - 1 && LessNotEqual(currentOffset_, 0.0) && index == 0) {
            loopIndex = childrenSize;
        }

        auto offset = OffsetF(0.0, 0.0);
        auto itemWidth = (axis == Axis::HORIZONTAL ? (size.Width() / displayCount) : (size.Height() / displayCount));
        if (axis == Axis::HORIZONTAL) {
            offset += OffsetF((loopIndex - currentIndex_) * itemWidth + currentOffset_, 0.0f);
        } else if (axis == Axis::VERTICAL) {
            offset += OffsetF(0.0f, (loopIndex - currentIndex_) * itemWidth + currentOffset_);
        } else {
            LOGW("axis [%{public}d] is not supported yet", axis);
        }
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG
