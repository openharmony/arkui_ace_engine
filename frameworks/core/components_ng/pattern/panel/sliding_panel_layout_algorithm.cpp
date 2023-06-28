/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/panel/close_icon_layout_property.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_UP_THRESHOLD = 48.0_vp;
constexpr double HALF_VALUS = 2.0;

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
    auto colunmNodeWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::COLUMN_ETS_TAG);
    if (colunmNodeWrapper) {
        colunmNodeWrapper->Measure(childLayoutConstraint);
    }
    auto closeIconWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::PANEL_CLOSE_ICON_ETS_TAG);
    if (closeIconWrapper) {
        MeasureCloseIcon(closeIconWrapper, layoutProperty);
    }
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
    auto columnWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::COLUMN_ETS_TAG);
    CHECK_NULL_VOID(columnWrapper);
    auto columnGeometryNode = columnWrapper->GetGeometryNode();
    CHECK_NULL_VOID(columnGeometryNode);

    fullHeight_ =
        layoutProperty->GetFullHeight().value_or(Dimension(frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()));
    halfHeight_ = layoutProperty->GetHalfHeight().value_or(
        Dimension((frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()) / HALF_VALUS));
    miniHeight_ = layoutProperty->GetMiniHeight().value_or(Dimension(DRAG_UP_THRESHOLD.ConvertToPx()));
    auto childOffset = OffsetF();
    if (isFirstLayout_) {
        if (invisibleFlag_) {
            auto rootHeight = PipelineContext::GetCurrentRootHeight();
            childOffset = OffsetF(0.0f, rootHeight);
        } else {
            childOffset = OffsetF(0.0f, frameSize.Height());
        }
        columnWrapper->GetGeometryNode()->SetMarginFrameOffset(childOffset + padding.Offset());
        isFirstLayout_ = false;
    } else {
        childOffset = OffsetF(0.0f, currentOffset_);
        columnGeometryNode->SetMarginFrameOffset(childOffset + padding.Offset());
    }
    columnWrapper->Layout();

    auto closeIconWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::PANEL_CLOSE_ICON_ETS_TAG);
    CHECK_NULL_VOID(closeIconWrapper);
    auto closeIconLayoutProperty = AceType::DynamicCast<CloseIconLayoutProperty>(closeIconWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(closeIconLayoutProperty);
    auto closeIconWidth = closeIconLayoutProperty->GetCloseIconWidthValue();
    auto closeIconMarginTop = closeIconLayoutProperty->GetCloseIconMarginTopValue();
    auto closeIconMargionRight = closeIconLayoutProperty->GetCloseIconMarginRightValue();
    auto closeIconX = static_cast<float>(Dimension(frameSize.Width()).ConvertToPx()) -
                      static_cast<float>(closeIconWidth.ConvertToPx()) -
                      static_cast<float>(closeIconMargionRight.ConvertToPx());
    auto closeIconY = childOffset.GetY() + static_cast<float>(closeIconMarginTop.ConvertToPx());
    auto closeIconOffset = OffsetF(closeIconX, closeIconY);
    closeIconWrapper->GetGeometryNode()->SetMarginFrameOffset(closeIconOffset + padding.Offset());
    closeIconWrapper->Layout();
}

RefPtr<LayoutWrapper> SlidingPanelLayoutAlgorithm::GetNodeLayoutWrapperByTag(
    LayoutWrapper* layoutWrapper, const std::string& tagName) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    auto totalChildCount = layoutWrapper->GetTotalChildCount();
    if (totalChildCount == 0) {
        return nullptr;
    }
    RefPtr<LayoutWrapper> nodeWrapper = nullptr;
    for (int32_t i = 0; i < totalChildCount; i++) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        if (nodeWrapper && (nodeWrapper->GetHostTag() == tagName)) {
            return nodeWrapper;
        }
    }
    return nullptr;
}

void SlidingPanelLayoutAlgorithm::MeasureCloseIcon(
    const RefPtr<LayoutWrapper>& closeIconWrapper, const RefPtr<LayoutProperty>& layoutProperty) const
{
    CHECK_NULL_VOID(closeIconWrapper);
    CHECK_NULL_VOID(layoutProperty);
    auto slidingPanelLayoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutProperty);
    CHECK_NULL_VOID(slidingPanelLayoutProperty);
    auto closeIconGeometryNode = closeIconWrapper->GetGeometryNode();
    CHECK_NULL_VOID(closeIconGeometryNode);
    auto closeIconLayoutProperty = AceType::DynamicCast<CloseIconLayoutProperty>(closeIconWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(closeIconLayoutProperty);
    auto closeIconWidth = closeIconLayoutProperty->GetCloseIconWidthValue();
    auto closeIconHeigth = closeIconLayoutProperty->GetCloseIconHeightValue();
    SizeF frameSize =
        SizeF(static_cast<float>(closeIconWidth.ConvertToPx()), static_cast<float>(closeIconHeigth.ConvertToPx()));
    closeIconGeometryNode->SetFrameSize(frameSize);
    auto childConstraint = slidingPanelLayoutProperty->CreateChildConstraint();
    closeIconWrapper->Measure(childConstraint);
}
} // namespace OHOS::Ace::NG