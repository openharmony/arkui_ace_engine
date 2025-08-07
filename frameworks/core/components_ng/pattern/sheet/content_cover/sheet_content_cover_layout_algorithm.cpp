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

#include "core/components_ng/pattern/sheet/content_cover/sheet_content_cover_layout_algorithm.h"

#include "base/log/log.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void SheetContentCoverLayoutAlgorithm::MeasureOperation(
    RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint)
{
    auto operationNode = sheetPattern->GetTitleBuilderNode();
    CHECK_NULL_VOID(operationNode);
    operationNode->Measure(constraint);
}

void SheetContentCoverLayoutAlgorithm::MeasureDragBar(
    RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint)
{
    auto dragBarNode = sheetPattern->GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    dragBarNode->Measure(constraint);
}

void SheetContentCoverLayoutAlgorithm::MeasureCloseIcon(
    RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint)
{
    auto sheetCloseIcon = sheetPattern->GetSheetCloseIcon();
    CHECK_NULL_VOID(sheetCloseIcon);
    sheetCloseIcon->Measure(constraint);
}

void SheetContentCoverLayoutAlgorithm::MeasureScrollNode(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint)
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
    auto index = host->GetChildIndexById(scrollNode->GetId());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(scrollWrapper);
    auto scrollLayoutProperty = scrollWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(scrollLayoutProperty);

    // Set SafeAreaPadding
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto inset = context->GetSafeAreaWithoutProcess();
    NG::CalcLength safeAreaPaddingTop(inset.top_.Length());
    NG::CalcLength safeAreaPaddingBottom(inset.bottom_.Length());
    NG::CalcLength safeAreaPaddingLeft(inset.left_.Length());
    NG::CalcLength safeAreaPaddingRight(inset.right_.Length());
    PaddingProperty safeAreaPadding;
    safeAreaPadding.top = safeAreaPaddingTop;
    safeAreaPadding.bottom = safeAreaPaddingBottom;
    safeAreaPadding.left = safeAreaPaddingLeft;
    safeAreaPadding.right = safeAreaPaddingRight;
    scrollLayoutProperty->UpdateSafeAreaPadding(safeAreaPadding);

    scrollWrapper->Measure(constraint);
}

void SheetContentCoverLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto sheetPattern = frameNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto parentConstraint  = geometryNode->GetParentLayoutConstraint();
    LayoutConstraintF layoutConstraint = parentConstraint.value();
    sheetHeight_ = layoutConstraint.maxSize.Height();
    sheetWidth_ = layoutConstraint.maxSize.Width();
    geometryNode->SetFrameSize(SizeF(sheetWidth_, sheetHeight_));
    geometryNode->SetContentSize(SizeF(sheetWidth_, sheetHeight_));

    auto layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    auto childConstraint = layoutProp->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(sheetWidth_);
    childConstraint.maxSize.SetHeight(sheetHeight_);
    childConstraint.parentIdealSize = OptionalSizeF(sheetWidth_, sheetHeight_);
    childConstraint.percentReference = SizeF(sheetWidth_, sheetHeight_);
    childConstraint.selfIdealSize = OptionalSizeF(sheetWidth_, sheetHeight_);
    MeasureScrollNode(layoutWrapper, childConstraint);

    auto hideChildConstraint = layoutProp->CreateChildConstraint();
    hideChildConstraint.maxSize.SetWidth(0.0f);
    hideChildConstraint.maxSize.SetHeight(0.0f);
    hideChildConstraint.parentIdealSize = OptionalSizeF(0.0f, 0.0f);
    hideChildConstraint.percentReference = SizeF(0.0f, 0.0f);
    hideChildConstraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    MeasureOperation(sheetPattern, hideChildConstraint);
    MeasureCloseIcon(sheetPattern, hideChildConstraint);
    MeasureDragBar(sheetPattern, hideChildConstraint);
}

void SheetContentCoverLayoutAlgorithm::LayoutTitleBuilder(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper)
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

    geometryNode->SetMarginFrameOffset(translate);
    titleBuilderWrapper->Layout();
}

void SheetContentCoverLayoutAlgorithm::LayoutDragBar(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto dragBarNode = sheetPattern->GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto index = host->GetChildIndexById(dragBarNode->GetId());
    auto dragBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dragBarWrapper);
    auto geometryNode = dragBarWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    geometryNode->SetMarginFrameOffset(translate);
    dragBarWrapper->Layout();
}

void SheetContentCoverLayoutAlgorithm::LayoutCloseIcon(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper)
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

    geometryNode->SetMarginFrameOffset(translate);
    closeIconWrapper->Layout();
}

void SheetContentCoverLayoutAlgorithm::LayoutScrollNode(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper)
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
    auto geometryNode = scrollWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    geometryNode->SetMarginFrameOffset(translate);
    scrollWrapper->Layout();
}

void SheetContentCoverLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    OffsetF positionOffset(0.0f, 0.0f);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(positionOffset);

    LayoutTitleBuilder(positionOffset, layoutWrapper);
    LayoutDragBar(positionOffset, layoutWrapper);
    LayoutCloseIcon(positionOffset, layoutWrapper);
    LayoutScrollNode(positionOffset, layoutWrapper);
}
} // namespace OHOS::Ace::NG