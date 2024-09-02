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

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/panel/close_icon_layout_property.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_UP_THRESHOLD = 48.0_vp;
constexpr double HALF_VALUS = 2.0;
constexpr int32_t DOUBLENESS = 2;

} // namespace

void SlidingPanelLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (!layoutConstraint) {
        return;
    }
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.UpdateMaxSizeWithCheck(layoutConstraint->maxSize);
    auto maxSize = childLayoutConstraint.maxSize;
    auto idealSize =
        !invisibleFlag_
            ? ((PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9)
                ? CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::HORIZONTAL,
                    layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT()
                : CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL,
                    layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true))
            : SizeF();
    auto width = GetMaxWidthByScreenSizeType(maxSize, idealSize);
    maxWidth_ = width;
    idealSize_ = idealSize;
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);
    auto type = layoutProperty->GetPanelType();
    if (type != PanelType::CUSTOM) {
        childLayoutConstraint.minSize = SizeF(width, static_cast<float>(idealSize.Height() - currentOffset_));
    }
    childLayoutConstraint.maxSize = SizeF(width, static_cast<float>(idealSize.Height() - currentOffset_));
    childLayoutConstraint.parentIdealSize =
        OptionalSizeF(width, static_cast<float>(idealSize.Height() - currentOffset_));
    if (type == PanelType::CUSTOM) {
        auto calc = layoutProperty->GetCustomHeight().value_or(Dimension(0.0));
        if (!calc.CalcValue().empty() && calc.CalcValue().find("wrapContent") != std::string::npos) {
            childLayoutConstraint.maxSize = SizeF(width, static_cast<float>(idealSize.Height()));
            childLayoutConstraint.parentIdealSize = OptionalSizeF(width, static_cast<float>(idealSize.Height()));
        }
    }
    childLayoutConstraint.percentReference = childLayoutConstraint.maxSize;
    layoutConstraint->percentReference = childLayoutConstraint.maxSize;
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
    auto leftPadding = 0.0f;
    auto rightPadding = 0.0f;
    if (geometryNode->GetPadding()) {
        leftPadding = geometryNode->GetPadding()->left.value_or(0.0f);
        rightPadding = geometryNode->GetPadding()->right.value_or(0.0f);
    }
    auto childOffsetX = static_cast<float>((idealSize_.Width() - leftPadding - rightPadding - maxWidth_) / HALF_VALUS);
    fullHeight_ =
        layoutProperty->GetFullHeight().value_or(Dimension(frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()));
    halfHeight_ = layoutProperty->GetHalfHeight().value_or(
        Dimension((frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()) / HALF_VALUS));
    miniHeight_ = layoutProperty->GetMiniHeight().value_or(Dimension(DRAG_UP_THRESHOLD.ConvertToPx()));
    customHeight_ = layoutProperty->GetCustomHeight().value_or(Dimension(0.0));
    auto type = layoutProperty->GetPanelType();
    if (type == PanelType::CUSTOM) {
        auto calc = layoutProperty->GetCustomHeight().value_or(Dimension(0.0));
        if (!calc.CalcValue().empty() && calc.CalcValue().find("wrapContent") != std::string::npos) {
            customHeight_ = Dimension(columnGeometryNode->GetFrameSize().Height());
        }
    }

    auto childOffset = OffsetF();
    if (isFirstLayout_) {
        if (invisibleFlag_) {
            auto rootHeight = PipelineContext::GetCurrentRootHeight();
            childOffset = OffsetF(childOffsetX, rootHeight);
        } else {
            childOffset = OffsetF(childOffsetX, frameSize.Height());
        }
        columnWrapper->GetGeometryNode()->SetMarginFrameOffset(childOffset + padding.Offset());
        isFirstLayout_ = false;
    } else {
        childOffset = OffsetF(childOffsetX, currentOffset_);
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
    auto closeIconX = maxWidth_ + childOffsetX - static_cast<float>(closeIconWidth.ConvertToPx()) -
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

float SlidingPanelLayoutAlgorithm::GetMaxWidthByScreenSizeType(const SizeF& maxSize, const SizeF& idealSize) const
{
    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::PANEL);
    columnInfo->GetParent()->BuildColumnWidth(maxSize.Width());
    auto gridSizeType = ScreenSystemManager::GetInstance().GetSize(maxSize.Width());
    auto width = 0.0f;
    uint32_t columns = 0;
    switch (gridSizeType) {
        case ScreenSizeType::UNDEFINED:
        case ScreenSizeType::XS:
        case ScreenSizeType::SM:
            width = idealSize.Width();
            break;
        case ScreenSizeType::MD:
            columns = columnInfo->GetColumns(gridSizeType);
            width =
                columnInfo->GetWidth(columns) + columnInfo->GetParent()->GetGutterWidth().ConvertToPx() * DOUBLENESS;
            break;
        case ScreenSizeType::LG:
        case ScreenSizeType::XL:
            columns = columnInfo->GetColumns(ScreenSizeType::LG);
            width =
                columnInfo->GetWidth(columns) + columnInfo->GetParent()->GetGutterWidth().ConvertToPx() * DOUBLENESS;
            break;
        default:
            break;
    }
    if (width > maxSize.Width()) {
        return maxSize.Width();
    }
    return width;
}
} // namespace OHOS::Ace::NG
