/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/sheet/side/sheet_presentation_side_layout_algorithm.h"

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SHEET_SIDE_DEFAULT_WIDTH = 400.0_vp;
constexpr float DOUBLE_SIZE = 2.0f;
} // namespace

float SheetPresentationSideLayoutAlgorithm::GetSheetDefaultWidth(
    const RefPtr<SheetPresentationPattern>& sheetPattern)
{
    double rootWidth = 0.0f;
    CHECK_NULL_RETURN(sheetPattern, rootWidth);
    if (sheetPattern->GetWindowSize().has_value()) {
        rootWidth = sheetPattern->GetWindowSize().value().Width();
    } else {
        rootWidth = PipelineContext::GetCurrentRootWidth();
    }
#ifdef PREVIEW
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, rootWidth);
    rootWidth = pipelineContext->GetDisplayWindowRectInfo().Width();
#endif
    if (GreatOrEqual(rootWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) &&
        LessNotEqual(rootWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
        return rootWidth / DOUBLE_SIZE; // [600vp, 840vp)
    } else if (GreatOrEqual(rootWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
        return SHEET_SIDE_DEFAULT_WIDTH.ConvertToPx(); // [840vp, +∞)
    } else {
        return 0.0f; // other
    }
}

void SheetPresentationSideLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    LayoutConstraintF layoutConstraint = parentConstraint.value();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    sheetMaxHeight_ = layoutConstraint.maxSize.Height();
    sheetMaxWidth_ = layoutConstraint.maxSize.Width();
    // width
    float defaultWidth = GetSheetDefaultWidth(sheetPattern);
    float width = defaultWidth;
    if (sheetStyle.width.has_value()) {
        if (sheetStyle.width->Unit() == DimensionUnit::PERCENT) {
            width = sheetStyle.width->ConvertToPxWithSize(sheetMaxWidth_);
        } else {
            width = sheetStyle.width->ConvertToPx();
        }
    }
    if (LessNotEqual(width, 0.0f) || width > sheetMaxWidth_) {
        width = defaultWidth;
    }
    // The height attribute only takes effect at the full-screen size
    sheetHeight_ = sheetMaxHeight_;
    sheetWidth_ = width;

    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    auto childConstraint = layoutProperty->CreateChildConstraint();
    auto childWidth = sheetWidth_ - padding.left.value_or(0.0f) - padding.right.value_or(0.0f);
    auto childHeight = sheetHeight_ - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f);
    childConstraint.parentIdealSize = OptionalSizeF(childWidth, childHeight);
    childConstraint.percentReference = SizeF(childWidth, childHeight);
    MeasureOperation(layoutWrapper, childConstraint);
    MeasureCloseIcon(layoutWrapper, childConstraint);
    MeasureScrollNode(layoutWrapper, childConstraint);

    SizeF idealSize(sheetWidth_, sheetHeight_);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
}

void SheetPresentationSideLayoutAlgorithm::MeasureOperation(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto operationNode = sheetPattern->GetTitleBuilderNode();
    CHECK_NULL_VOID(operationNode);
    operationNode->Measure(constraint);
}

void SheetPresentationSideLayoutAlgorithm::MeasureCloseIcon(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetCloseIcon = sheetPattern->GetSheetCloseIcon();
    CHECK_NULL_VOID(sheetCloseIcon);
    sheetCloseIcon->Measure(constraint);
}

void SheetPresentationSideLayoutAlgorithm::MeasureScrollNode(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto operatoration = sheetPattern->GetTitleBuilderNode();
    CHECK_NULL_VOID(operatoration);
    auto operatorGeometryNode = operatoration->GetGeometryNode();
    CHECK_NULL_VOID(operatorGeometryNode);
    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    float childHeight = sheetHeight_ - operatorGeometryNode->GetFrameSize().Height() - padding.top.value_or(0.0f);
    float childWidth = sheetWidth_ - padding.left.value_or(0.0f) - padding.right.value_or(0.0f);
    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(childWidth);
    childConstraint.maxSize.SetHeight(childHeight);
    childConstraint.parentIdealSize = OptionalSizeF(childWidth, childHeight);
    childConstraint.percentReference = SizeF(childWidth, childHeight);
    scrollNode->Measure(childConstraint);
}

void SheetPresentationSideLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    OffsetF positionOffset;
    positionOffset.SetX(0.0f);
    positionOffset.SetY(0.0f);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(positionOffset);

    LayoutCloseIcon(layoutWrapper);
    LayoutTitleBuilder(layoutWrapper);
    LayoutScrollNode(layoutWrapper);
}

void SheetPresentationSideLayoutAlgorithm::LayoutCloseIcon(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetCloseNode = sheetPattern->GetSheetCloseIcon();
    CHECK_NULL_VOID(sheetCloseNode);
    auto index = host->GetChildIndexById(sheetCloseNode->GetId());
    auto closeIconWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(closeIconWrapper);
    auto geometryNode = closeIconWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
 
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    auto closeIconX = sheetGeometryNode->GetFrameSize().Width() -
                      static_cast<float>(sheetTheme->GetCloseIconButtonWidth().ConvertToPx()) -
                      static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx()) - padding.right.value_or(0.0f);
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        closeIconX = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx()) + padding.left.value_or(0.0f);
    }
    auto closeIconY = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx()) + padding.top.value_or(0.0f);
    OffsetF positionOffset;
    positionOffset.SetX(closeIconX);
    positionOffset.SetY(closeIconY);
    geometryNode->SetMarginFrameOffset(positionOffset);
    closeIconWrapper->Layout();
}

void SheetPresentationSideLayoutAlgorithm::LayoutTitleBuilder(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto titleBuilderNode = sheetPattern->GetTitleBuilderNode();
    CHECK_NULL_VOID(titleBuilderNode);
    auto index = host->GetChildIndexById(titleBuilderNode->GetId());
    auto titleBuilderWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleBuilderWrapper);
    auto geometryNode = titleBuilderWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    OffsetF offset;
    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        offset.SetX(padding.left.value_or(0.0f));
    }
    offset.SetY(padding.top.value_or(0.0f));
    geometryNode->SetMarginFrameOffset(offset);
    titleBuilderWrapper->Layout();
}

void SheetPresentationSideLayoutAlgorithm::LayoutScrollNode(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto index = host->GetChildIndexById(scrollNode->GetId());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(scrollWrapper);

    OffsetF offset;
    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        offset.SetX(padding.left.value_or(0.0f));
    }
    offset.SetY(padding.top.value_or(0.0f));

    auto titleBuilder = sheetPattern->GetTitleBuilderNode();
    if (titleBuilder) {
        auto titleBuilderNode = titleBuilder->GetGeometryNode();
        CHECK_NULL_VOID(titleBuilderNode);
        offset += OffsetF(0, titleBuilderNode->GetFrameSize().Height());
    }
    auto geometryNode = scrollWrapper->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(offset);
    scrollWrapper->Layout();
}

} // namespace OHOS::Ace::NG