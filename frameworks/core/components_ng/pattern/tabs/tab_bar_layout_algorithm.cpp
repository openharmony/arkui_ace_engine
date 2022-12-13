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

#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme
constexpr Dimension TAB_BAR_DEFAULT_SIZE = 56.0_vp;

} // namespace

void TabBarLayoutAlgorithm::UpdateChildConstraint(LayoutConstraintF& childConstraint,
    const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& ideaSize, int32_t childCount, Axis axis)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    childConstraint.parentIdealSize = OptionalSizeF(ideaSize);
    const auto& barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    if (barMode == TabBarMode::FIXED) {
        auto childIdeaSize = ideaSize;
        if (axis == Axis::HORIZONTAL) {
            childIdeaSize.SetWidth(ideaSize.Width() / childCount);
            childConstraint.maxSize.SetHeight(
                childConstraint.maxSize.Height() - tabTheme->GetSubTabIndicatorHeight().ConvertToPx());
        } else if (axis == Axis::VERTICAL) {
            childIdeaSize.SetHeight(
                ideaSize.Height() / childCount - tabTheme->GetSubTabIndicatorHeight().ConvertToPx());
        }
        childConstraint.selfIdealSize = OptionalSizeF(childIdeaSize);
    } else {
        if (axis == Axis::HORIZONTAL) {
            childConstraint.maxSize.SetWidth(Infinity<float>());
            childConstraint.maxSize.SetHeight(
                childConstraint.maxSize.Height() - tabTheme->GetSubTabIndicatorHeight().ConvertToPx());
            childConstraint.selfIdealSize.SetHeight(ideaSize.Height());
        } else if (axis == Axis::VERTICAL) {
            childConstraint.maxSize.SetHeight(Infinity<float>());
            childConstraint.selfIdealSize.SetWidth(ideaSize.Width());
        }
    }
}

void TabBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = GetAxis(layoutWrapper);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize =
        CreateIdealSize(constraint.value(), axis, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));
    auto defaultSize = static_cast<float>(TAB_BAR_DEFAULT_SIZE.ConvertToPx());
    if (!constraint->selfIdealSize.Width().has_value() && axis == Axis::VERTICAL) {
        idealSize.SetWidth(defaultSize);
    }
    if (!constraint->selfIdealSize.Height().has_value() && axis == Axis::HORIZONTAL) {
        idealSize.SetHeight(defaultSize);
    }
    geometryNode->SetFrameSize(idealSize.ConvertToSizeT());

    // Create layout constraint of children .
    auto childCount = layoutWrapper->GetTotalChildCount();
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(childLayoutConstraint, layoutProperty, idealSize.ConvertToSizeT(), childCount, axis);

    // Measure children.
    childrenMainSize_ = 0.0f;
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            LOGI("Child %{public}d is null.", index);
            continue;
        }
        childWrapper->Measure(childLayoutConstraint);
        if (axis == Axis::HORIZONTAL) {
            childrenMainSize_ += childWrapper->GetGeometryNode()->GetMarginFrameSize().MainSize(axis);
        } else {
            childrenMainSize_ = childrenMainSize_ +
                                childWrapper->GetGeometryNode()->GetMarginFrameSize().MainSize(axis) +
                                tabTheme->GetSubTabIndicatorHeight().ConvertToPx();
        }
    }
}

void TabBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    tabItemOffset_.clear();
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto axis = GetAxis(layoutWrapper);
    auto frameSize = geometryNode->GetFrameSize();

    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    int32_t indicator = layoutProperty->GetIndicatorValue(0);
    if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        childrenMainSize_ <= frameSize.MainSize(axis) && !isBuilder_) {
        indicator_ = indicator;
        auto frontSpace = (frameSize.MainSize(axis) - childrenMainSize_) / 2;
        OffsetF childOffset = (axis == Axis::HORIZONTAL ? OffsetF(frontSpace, 0.0f) : OffsetF(0.0f, frontSpace));
        LayoutChildren(layoutWrapper, frameSize, axis, childOffset);
        return;
    }
    if (indicator != indicator_ &&
        layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        indicator_ = indicator;
        auto space = GetSpace(layoutWrapper, indicator, frameSize, axis);
        float frontChildrenMainSize = CalculateFrontChildrenMainSize(layoutWrapper, indicator, axis);
        if (frontChildrenMainSize < space) {
            OffsetF childOffset = OffsetF(0.0f, 0.0f);
            currentOffset_ = 0.0f;
            LayoutChildren(layoutWrapper, frameSize, axis, childOffset);
            return;
        }
        float backChildrenMainSize = CalculateBackChildrenMainSize(layoutWrapper, indicator, axis);
        if (backChildrenMainSize < space) {
            auto scrollableDistance = std::max(childrenMainSize_ - frameSize.MainSize(axis), 0.0f);
            currentOffset_ = -scrollableDistance;
            OffsetF childOffset =
                (axis == Axis::HORIZONTAL ? OffsetF(-scrollableDistance, 0.0f) : OffsetF(0.0f, -scrollableDistance));
            LayoutChildren(layoutWrapper, frameSize, axis, childOffset);
            return;
        }
        auto scrollableDistance = std::max(frontChildrenMainSize - space, 0.0f);
        currentOffset_ = -scrollableDistance;
        OffsetF childOffset =
            (axis == Axis::HORIZONTAL ? OffsetF(-scrollableDistance, 0.0f) : OffsetF(0.0f, -scrollableDistance));
        LayoutChildren(layoutWrapper, frameSize, axis, childOffset);
        return;
    }

    auto scrollableDistance = std::max(childrenMainSize_ - frameSize.MainSize(axis), 0.0f);
    currentOffset_ = std::clamp(currentOffset_, -scrollableDistance, 0.0f);
    OffsetF childOffset = (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_));
    indicator_ = indicator;
    LayoutChildren(layoutWrapper, frameSize, axis, childOffset);
}

Axis TabBarLayoutAlgorithm::GetAxis(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, Axis::HORIZONTAL);
    return layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
}

float TabBarLayoutAlgorithm::GetSpace(
    LayoutWrapper* layoutWrapper, int32_t indicator, const SizeF& frameSize, Axis axis)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(indicator);
    if (!childWrapper) {
        return 0.0f;
    }
    auto childGeometryNode = childWrapper->GetGeometryNode();
    auto childFrameSize = childGeometryNode->GetMarginFrameSize();
    return (frameSize.MainSize(axis) - childFrameSize.MainSize(axis)) / 2;
}

float TabBarLayoutAlgorithm::CalculateFrontChildrenMainSize(LayoutWrapper* layoutWrapper, int32_t indicator, Axis axis)
{
    float frontChildrenMainSize = 0.0f;
    for (int32_t index = 0; index < indicator; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            return 0.0f;
        }
        auto childGeometryNode = childWrapper->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        frontChildrenMainSize += childFrameSize.MainSize(axis);
    }
    return frontChildrenMainSize;
}

void TabBarLayoutAlgorithm::LayoutChildren(
    LayoutWrapper* layoutWrapper, const SizeF& frameSize, Axis axis, OffsetF& childOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto childCount = layoutWrapper->GetTotalChildCount();
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            continue;
        }
        auto childGeometryNode = childWrapper->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        OffsetF centerOffset = (axis == Axis::HORIZONTAL)
                                   ? OffsetF(0, (frameSize.Height() - childFrameSize.Height()) / 2.0)
                                   : OffsetF((frameSize.Width() - childFrameSize.Width()) / 2.0, 0);
        childGeometryNode->SetMarginFrameOffset(childOffset + centerOffset);
        childWrapper->Layout();
        tabItemOffset_.emplace_back(childOffset);

        if (axis == Axis::HORIZONTAL) {
            childOffset += OffsetF(childFrameSize.Width(), 0.0f);
        } else {
            childOffset += OffsetF(0.0f, childFrameSize.Height() + tabTheme->GetSubTabIndicatorHeight().ConvertToPx());
        }
    }
    tabItemOffset_.emplace_back(childOffset);
}

float TabBarLayoutAlgorithm::CalculateBackChildrenMainSize(LayoutWrapper* layoutWrapper, int32_t indicator, Axis axis)
{
    float backChildrenMainSize = 0.0f;
    auto childCount = layoutWrapper->GetTotalChildCount();
    for (int32_t index = indicator + 1; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            return 0.0f;
        }
        auto childGeometryNode = childWrapper->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        backChildrenMainSize += childFrameSize.MainSize(axis);
    }
    return backChildrenMainSize;
}

} // namespace OHOS::Ace::NG
