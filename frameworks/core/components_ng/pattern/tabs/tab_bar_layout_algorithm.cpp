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
constexpr int8_t MASK_COUNT = 2;
}
void TabBarLayoutAlgorithm::UpdateChildConstraint(LayoutConstraintF& childConstraint,
    const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& ideaSize, int32_t childCount, Axis axis)
{
    childConstraint.parentIdealSize = OptionalSizeF(ideaSize);
    const auto& barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (barMode == TabBarMode::FIXED) {
        auto childIdeaSize = ideaSize;
        if (axis == Axis::HORIZONTAL) {
            childIdeaSize.SetWidth(ideaSize.Width() / childCount);
            childConstraint.maxSize.SetHeight(childConstraint.maxSize.Height());
            if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
                childConstraint.minSize.SetWidth(tabTheme->GetSubTabBarMinWidth().ConvertToPx());
            }
        } else if (axis == Axis::VERTICAL) {
            childIdeaSize.SetHeight(tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE
                                        ? ideaSize.Height() / (childCount * 2)
                                        : ideaSize.Height() / childCount);
        }
        childConstraint.selfIdealSize = OptionalSizeF(childIdeaSize);
    } else {
        if (axis == Axis::HORIZONTAL) {
            childConstraint.maxSize.SetWidth(Infinity<float>());
            childConstraint.maxSize.SetHeight(childConstraint.maxSize.Height());
            childConstraint.selfIdealSize.SetHeight(ideaSize.Height());
            if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
                childConstraint.minSize.SetWidth(tabTheme->GetSubTabBarMinWidth().ConvertToPx());
            }
        } else if (axis == Axis::VERTICAL) {
            childConstraint.maxSize.SetHeight(Infinity<float>());
            childConstraint.selfIdealSize.SetWidth(ideaSize.Width());
        }
    }
}

void TabBarLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = GetAxis(frameNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize =
        CreateIdealSize(constraint.value(), axis, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));
    if (constraint->selfIdealSize.Width().has_value() &&
        constraint->selfIdealSize.Width().value() > constraint->parentIdealSize.Width().value_or(0.0f)) {
        idealSize.SetWidth(static_cast<float>(
            axis == Axis::HORIZONTAL                         ? constraint->parentIdealSize.Width().value_or(0.0f)
            : tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE ? tabTheme->GetTabBarDefaultWidth().ConvertToPx()
                                                             : tabTheme->GetTabBarDefaultHeight().ConvertToPx()));
    }
    if (constraint->selfIdealSize.Height().has_value() &&
        constraint->selfIdealSize.Height().value() > constraint->parentIdealSize.Height().value_or(0.0f)) {
        idealSize.SetHeight(
            static_cast<float>(axis == Axis::HORIZONTAL ? tabTheme->GetTabBarDefaultHeight().ConvertToPx()
                                                        : constraint->parentIdealSize.Height().value_or(0.0f)));
    }
    if (!constraint->selfIdealSize.Width().has_value() && axis == Axis::VERTICAL) {
        idealSize.SetWidth(static_cast<float>(tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE
                                                  ? tabTheme->GetTabBarDefaultWidth().ConvertToPx()
                                                  : tabTheme->GetTabBarDefaultHeight().ConvertToPx()));
    }
    if (!constraint->selfIdealSize.Height().has_value() && axis == Axis::HORIZONTAL) {
        idealSize.SetHeight(static_cast<float>(tabTheme->GetTabBarDefaultHeight().ConvertToPx()));
    }
    geometryNode->SetFrameSize(idealSize.ConvertToSizeT());

    // Create layout constraint of children .
    auto childCount = frameNode->TotalChildCount();
    if (childCount <= MASK_COUNT) {
        LOGI("ChildCount is illegal.");
        return;
    }
    childCount -= MASK_COUNT;
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(childLayoutConstraint, layoutProperty, idealSize.ConvertToSizeT(), childCount, axis);

    // Measure children.
    childrenMainSize_ = 0.0f;
    for (int32_t index = 0; index < childCount; ++index) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        if (!child) {
            LOGI("Child %{public}d is null.", index);
            continue;
        }
        child->Measure(childLayoutConstraint);
        childrenMainSize_ += child->GetGeometryNode()->GetMarginFrameSize().MainSize(axis);
    }
}

void TabBarLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    tabItemOffset_.clear();
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto axis = GetAxis(frameNode);
    auto frameSize = geometryNode->GetFrameSize();

    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    int32_t indicator = layoutProperty->GetIndicatorValue(0);
    if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::FIXED &&
        tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE && axis == Axis::VERTICAL) {
        indicator_ = indicator;
        auto space = frameSize.Height() / 4;
        OffsetF childOffset = OffsetF(0.0f, space);
        LayoutChildren(frameNode, frameSize, axis, childOffset);
        return;
    }
    if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        childrenMainSize_ <= frameSize.MainSize(axis)) {
        indicator_ = indicator;
        auto frontSpace = (frameSize.MainSize(axis) - childrenMainSize_) / 2;
        OffsetF childOffset = (axis == Axis::HORIZONTAL ? OffsetF(frontSpace, 0.0f) : OffsetF(0.0f, frontSpace));
        LayoutChildren(frameNode, frameSize, axis, childOffset);
        return;
    }
    if (indicator != indicator_ &&
        layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        if (childrenMainSize_ > frameSize.MainSize(axis) && tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE &&
            axis == Axis::HORIZONTAL) {
            OffsetF childOffset = OffsetF(currentOffset_, 0.0f);
            indicator_ = indicator;
            LayoutChildren(frameNode, frameSize, axis, childOffset);
            return;
        }
        indicator_ = indicator;
        auto space = GetSpace(frameNode, indicator, frameSize, axis);
        float frontChildrenMainSize = CalculateFrontChildrenMainSize(frameNode, indicator, axis);
        if (frontChildrenMainSize < space) {
            OffsetF childOffset = OffsetF(0.0f, 0.0f);
            currentOffset_ = 0.0f;
            LayoutChildren(frameNode, frameSize, axis, childOffset);
            return;
        }
        float backChildrenMainSize = CalculateBackChildrenMainSize(frameNode, indicator, axis);
        if (backChildrenMainSize < space) {
            auto scrollableDistance = std::max(childrenMainSize_ - frameSize.MainSize(axis), 0.0f);
            currentOffset_ = -scrollableDistance;
            OffsetF childOffset =
                (axis == Axis::HORIZONTAL ? OffsetF(-scrollableDistance, 0.0f) : OffsetF(0.0f, -scrollableDistance));
            LayoutChildren(frameNode, frameSize, axis, childOffset);
            return;
        }
        auto scrollableDistance = std::max(frontChildrenMainSize - space, 0.0f);
        currentOffset_ = -scrollableDistance;
        OffsetF childOffset =
            (axis == Axis::HORIZONTAL ? OffsetF(-scrollableDistance, 0.0f) : OffsetF(0.0f, -scrollableDistance));
        LayoutChildren(frameNode, frameSize, axis, childOffset);
        return;
    }
    if (tabBarStyle_ != TabBarStyle::SUBTABBATSTYLE || axis == Axis::VERTICAL) {
        auto scrollableDistance = std::max(childrenMainSize_ - frameSize.MainSize(axis), 0.0f);
        currentOffset_ = std::clamp(currentOffset_, -scrollableDistance, 0.0f);
    }
    OffsetF childOffset = (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_));
    indicator_ = indicator;
    LayoutChildren(frameNode, frameSize, axis, childOffset);
}

Axis TabBarLayoutAlgorithm::GetAxis(FrameNode* frameNode) const
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, Axis::HORIZONTAL);
    return layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
}

float TabBarLayoutAlgorithm::GetSpace(
    FrameNode* frameNode, int32_t indicator, const SizeF& frameSize, Axis axis)
{
    auto child = frameNode->GetFrameNodeByIndex(indicator);
    if (!child) {
        return 0.0f;
    }
    auto childGeometryNode = child->GetGeometryNode();
    auto childFrameSize = childGeometryNode->GetMarginFrameSize();
    return (frameSize.MainSize(axis) - childFrameSize.MainSize(axis)) / 2;
}

float TabBarLayoutAlgorithm::CalculateFrontChildrenMainSize(FrameNode* frameNode, int32_t indicator, Axis axis)
{
    float frontChildrenMainSize = 0.0f;
    for (int32_t index = 0; index < indicator; ++index) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        if (!child) {
            return 0.0f;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        frontChildrenMainSize += childFrameSize.MainSize(axis);
    }
    return frontChildrenMainSize;
}

void TabBarLayoutAlgorithm::LayoutChildren(
    FrameNode* frameNode, const SizeF& frameSize, Axis axis, OffsetF& childOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto childCount = frameNode->TotalChildCount() - MASK_COUNT;
    if (childCount < 0) {
        return;
    }
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    for (int32_t index = 0; index < childCount; ++index) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        if (!child) {
            continue;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        OffsetF centerOffset = (axis == Axis::HORIZONTAL)
                                   ? OffsetF(0, (frameSize.Height() - childFrameSize.Height()) / 2.0)
                                   : OffsetF((frameSize.Width() - childFrameSize.Width()) / 2.0, 0);
        childGeometryNode->SetMarginFrameOffset(childOffset + centerOffset);
        child->Layout();
        tabItemOffset_.emplace_back(childOffset);

        childOffset +=
            axis == Axis::HORIZONTAL ? OffsetF(childFrameSize.Width(), 0.0f) : OffsetF(0.0f, childFrameSize.Height());
    }
    tabItemOffset_.emplace_back(childOffset);
    LayoutMask(frameNode);
}

void TabBarLayoutAlgorithm::LayoutMask(FrameNode* frameNode)
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto childCount = frameNode->TotalChildCount() - MASK_COUNT;
    if (childCount < 0) {
        return;
    }
    auto selectedMask = frameNode->GetFrameNodeByIndex(childCount);
    CHECK_NULL_VOID(selectedMask);
    auto unselectedMask = frameNode->GetFrameNodeByIndex(childCount + 1);
    CHECK_NULL_VOID(unselectedMask);
    for (int32_t i = 0; i < MASK_COUNT; i++) {
        auto current = (i == 0 ? selectedMask : unselectedMask);
        auto currentMask = (i == 0 ? layoutProperty->GetSelectedMask().value_or(-1) :
            layoutProperty->GetUnselectedMask().value_or(-1));
        if (currentMask < 0) {
            current->GetGeometryNode()->SetFrameSize(SizeF());
        } else {
            auto child = frameNode->GetFrameNodeByIndex(currentMask);
            CHECK_NULL_VOID(child);
            auto childOffset = child->GetGeometryNode()->GetMarginFrameOffset();
            auto offset = current->GetGeometryNode()->GetMarginFrameOffset();
            current->GetGeometryNode()->SetMarginFrameOffset(offset + childOffset);
        }
        current->Layout();
    }
}

float TabBarLayoutAlgorithm::CalculateBackChildrenMainSize(FrameNode* frameNode, int32_t indicator, Axis axis)
{
    float backChildrenMainSize = 0.0f;
    auto childCount = frameNode->TotalChildCount() - MASK_COUNT;
    for (int32_t index = indicator + 1; index < childCount; ++index) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        if (!child) {
            return 0.0f;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        backChildrenMainSize += childFrameSize.MainSize(axis);
    }
    return backChildrenMainSize;
}

} // namespace OHOS::Ace::NG
