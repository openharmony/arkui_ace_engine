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

#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_UP_THRESHOLD = 48.0_vp;

} // namespace

void SlidingPanelLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    if (!constraint) {
        LOGE("fail to measure slidingPanel due to layoutConstraint is nullptr");
        return;
    }
    auto idealSize =
        !invisibleFlag_
            ? ((PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9)
                      ? CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
                            layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT))
                            .ConvertToSizeT()
                      : CreateIdealSize(constraint.value(), Axis::HORIZONTAL,
                            layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true))
            : SizeF();

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);

    // Calculate child layout constraint.
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    auto childIdeaSize = idealSize;
    childIdeaSize.SetHeight(static_cast<float>(idealSize.Height() - currentOffset_));
    childLayoutConstraint.selfIdealSize = OptionalSizeF(childIdeaSize);
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    // Measure child( is a Column).
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    if (!childWrapper) {
        LOGI("There is no child.");
        return;
    }
    childWrapper->Measure(childLayoutConstraint);
}

void SlidingPanelLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto frameSize = geometryNode->GetFrameSize();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);

    fullHeight_ =
        layoutProperty->GetFullHeight().value_or(Dimension(frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()));
    halfHeight_ = layoutProperty->GetHalfHeight().value_or(Dimension(frameSize.Height() / 2));
    miniHeight_ = layoutProperty->GetMiniHeight().value_or(Dimension(DRAG_UP_THRESHOLD.ConvertToPx()));

    if (isFirstLayout_) {
        auto childOffset = OffsetF();
        if (invisibleFlag_) {
            auto rootHeight = PipelineContext::GetCurrentRootHeight();
            childOffset = OffsetF(0.0f, rootHeight);
        } else {
            childOffset = OffsetF(0.0f, frameSize.Height());
        }
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(childOffset + padding.Offset());
        isFirstLayout_ = false;
    } else {
        auto childOffset = OffsetF(0.0f, currentOffset_);
        childGeometryNode->SetMarginFrameOffset(childOffset + padding.Offset());
    }
    childWrapper->Layout();
}

} // namespace OHOS::Ace::NG