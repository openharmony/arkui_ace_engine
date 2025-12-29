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

#include "core/components_ng/pattern/sheet/minimize/sheet_presentation_minimize_layout_algorithm.h"

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/sheet/minimize/sheet_minimize_object.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SHEET_MINIMIZE_DEFAULT_WIDTH = 125.0_vp;
constexpr Dimension SHEET_MINIMIZE_DEFAULT_HEIGHT = 125.0_vp;
constexpr Dimension SHEET_MINIMIZE_MARGIN_TOP = 56.0_vp;
constexpr Dimension SHEET_MINIMIZE_MARGIN_RIGHT = 32.0_vp;
} // namespace

void SheetPresentationMinimizeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    LayoutConstraintF layoutConstraint = parentConstraint.value();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    sheetMaxHeight_ = SHEET_MINIMIZE_DEFAULT_HEIGHT.ConvertToPx();
    sheetMaxWidth_ = layoutConstraint.maxSize.Width();
    sheetHeight_ = SHEET_MINIMIZE_DEFAULT_HEIGHT.ConvertToPx();
    sheetWidth_ = SHEET_MINIMIZE_DEFAULT_WIDTH.ConvertToPx();

    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(sheetWidth_);
    childConstraint.maxSize.SetHeight(sheetHeight_);
    childConstraint.parentIdealSize = OptionalSizeF(sheetWidth_, sheetHeight_);
    childConstraint.percentReference = SizeF(sheetWidth_, sheetHeight_);
    MeasureScrollNode(layoutWrapper, childConstraint);

    SizeF idealSize(sheetWidth_, sheetHeight_);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
}

void SheetPresentationMinimizeLayoutAlgorithm::MeasureScrollNode(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto minimizeObject = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(minimizeObject);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto index = host->GetChildIndexById(scrollNode->GetId());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(scrollWrapper);
    scrollWrapper->Measure(constraint);
}

void SheetPresentationMinimizeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    OffsetF positionOffset;
    positionOffset.SetX(sheetMaxWidth_ - sheetWidth_ - SHEET_MINIMIZE_MARGIN_RIGHT.ConvertToPx());
    positionOffset.SetY(SHEET_MINIMIZE_MARGIN_TOP.ConvertToPx());
    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(positionOffset);

    LayoutScrollNode(layoutWrapper);
}

void SheetPresentationMinimizeLayoutAlgorithm::LayoutScrollNode(LayoutWrapper* layoutWrapper)
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
    OffsetF positionOffset;
    positionOffset.SetX(0.0f);
    positionOffset.SetY(0.0f);
    geometryNode->SetMarginFrameOffset(positionOffset);
    scrollWrapper->Layout();
}

} // namespace OHOS::Ace::NG