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

#include "core/components_v2/grid_layout/render_grid_row.h"

#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/components_v2/grid_layout/grid_row_component.h"
#include "core/components_v2/grid_layout/render_grid_col.h"

namespace OHOS::Ace::V2 {
namespace {
std::map<RefPtr<RenderGridCol>, RefPtr<RenderNode>> gridColToNodeMap;

bool OrderComparator(const RefPtr<RenderNode>& left, const RefPtr<RenderNode>& right)
{
    auto leftGrid = AceType::DynamicCast<RenderGridCol>(left);
    auto rightGrid = AceType::DynamicCast<RenderGridCol>(right);
    if (leftGrid && rightGrid) {
        return (leftGrid->GetOrder(leftGrid->GetSizeType()) < rightGrid->GetOrder(rightGrid->GetSizeType()));
    }
    return false;
}

inline std::list<RefPtr<RenderNode>> SortChildrenByOrder(const std::list<RefPtr<RenderNode>>& children)
{
    auto sortChildren = children;
    sortChildren.sort(OrderComparator);
    return sortChildren;
}

std::string ConvertSizeTypeToString(GridSizeType sizeType)
{
    switch (sizeType) {
        case GridSizeType::XS:
            return "xs";
        case GridSizeType::SM:
            return "sm";
        case GridSizeType::LG:
            return "lg";
        case GridSizeType::MD:
            return "md";
        case GridSizeType::XL:
            return "xl";
        case GridSizeType::XXL:
            return "xxl";
        case GridSizeType::UNDEFINED:
            return "undefined";
    }
}

} // namespace

RefPtr<RenderNode> RenderGridRow::Create()
{
    return AceType::MakeRefPtr<RenderGridRow>();
}

void RenderGridRow::Update(const RefPtr<Component>& component)
{
    auto gridRowComponent = AceType::DynamicCast<GridRowComponent>(component);
    if (!gridRowComponent) {
        LOGE("update grid row component fail, because type unmatch");
        return;
    }
    gridRowComponent_ = component;
}

GridRowDirection RenderGridRow::GetDirection() const
{
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        return GridRowDirection::Row;
    }
    return component->GetDirection();
}

RefPtr<BreakPoints> RenderGridRow::GetBreakPoints() const
{
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        return nullptr;
    }
    return component->GetBreakPoints();
}

int32_t RenderGridRow::GetTotalCol() const
{
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        return 0;
    }
    auto totalColumn = GridContainerUtils::ProcessColumn(currentSizeType_, component->GetTotalCol());
    return totalColumn;
}

std::pair<double, double> RenderGridRow::GetGutter() const
{
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        return std::make_pair<double, double>(0.0, 0.0);
    }
    auto gutter = GridContainerUtils::ProcessGutter(currentSizeType_, component->GetGutter());
    return std::make_pair<double, double>(NormalizeToPx(gutter.first), NormalizeToPx(gutter.second));
}

void RenderGridRow::PerformLayout()
{
    auto maxSize = GetLayoutParam().GetMaxSize();
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        LOGI("Grid row fail to perform build");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGI("context upgrade fail perform layout fail");
        return;
    }
    auto sizeType = GridContainerUtils::ProcessGridSizeType(component->GetBreakPoints(), maxSize, context);
    if (currentSizeType_ != sizeType) {
        auto sizeTypeString = ConvertSizeTypeToString(sizeType);
        component->FirebreakPointEvent(sizeTypeString);
        currentSizeType_ = sizeType;
    }
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, component->GetGutter());
    auto gutterInDouble = std::make_pair<double, double>(NormalizeToPx(gutter.first), NormalizeToPx(gutter.second));
    int32_t columnNum = GridContainerUtils::ProcessColumn(sizeType, component->GetTotalCol());
    double columnUnitWidth = GridContainerUtils::ProcessColumnWidth(gutterInDouble, columnNum, maxSize.Width());
    LayoutEachChild(columnUnitWidth, maxSize.Height(), gutterInDouble.first, sizeType, columnNum);
    int32_t offset = 0;
    Offset rowPosition;
    double currentRowHeight = 0.0;
    double totalHeight = 0.0;
    double lastLength = maxSize.Width();
    for (const auto& child : gridColChildren_) {
        auto gridColChild = AceType::DynamicCast<RenderGridCol>(child);
        if (!gridColChild) {
            continue;
        }
        auto currentChildSpan = GetGridColSpan(gridColChild, sizeType);
        if (currentChildSpan == 0) {
            continue;
        }
        currentChildSpan = std::min(columnNum, currentChildSpan);
        NewLineOffset newLineOffset;
        CalculateOffsetOfNewline(
            gridColChild, currentChildSpan, columnNum - offset, columnNum, sizeType, newLineOffset);
        if (!newLineOffset.isValid) {
            continue;
        }
        if (newLineOffset.newLineCount > 0) {
            totalHeight += currentRowHeight * newLineOffset.newLineCount + gutterInDouble.second;
            rowPosition.SetY(
                rowPosition.GetY() + currentRowHeight * newLineOffset.newLineCount + gutterInDouble.second);
            offset = newLineOffset.offset;
            currentRowHeight = gridColToNodeMap[gridColChild]->GetLayoutSize().Height();
            lastLength = maxSize.Width();
        } else {
            currentRowHeight = std::max(currentRowHeight, gridColToNodeMap[gridColChild]->GetLayoutSize().Height());
        }
        Offset position;
        if (component->GetDirection() == V2::GridRowDirection::RowReverse) {
            double childSpanPlusOffsetWidth = 0.0;
            if (newLineOffset.newLineCount > 0) {
                childSpanPlusOffsetWidth = ((currentChildSpan + newLineOffset.offset) * columnUnitWidth +
                                            ((currentChildSpan + newLineOffset.offset) - 1) * gutterInDouble.first);
                position.SetX(lastLength - childSpanPlusOffsetWidth);
            } else {
                childSpanPlusOffsetWidth =
                    ((currentChildSpan + GetRelativeOffset(gridColChild, sizeType)) * columnUnitWidth +
                        ((currentChildSpan + GetRelativeOffset(gridColChild, sizeType)) - 1) * gutterInDouble.first);
                offset += GetRelativeOffset(gridColChild, sizeType);
            }
            position.SetX(lastLength - childSpanPlusOffsetWidth);
            lastLength -= childSpanPlusOffsetWidth + gutterInDouble.first;
        } else if (component->GetDirection() == V2::GridRowDirection::Row) {
            if (newLineOffset.newLineCount > 0) {
                position.SetX(offset > 0 ? offset * columnUnitWidth + offset * gutterInDouble.first : 0);
            } else {
                offset += GetRelativeOffset(gridColChild, sizeType);
                position.SetX(offset * (columnUnitWidth + gutterInDouble.first));
            }
        }
        position.SetY(rowPosition.GetY());
        gridColToNodeMap[gridColChild]->SetPosition(position);
        offset += currentChildSpan;
    }
    totalHeight += currentRowHeight;
    if (component->HasContainerHeight()) {
        SetLayoutSize(Size(maxSize.Width(), maxSize.Height()));
    } else {
        SetLayoutSize(Size(maxSize.Width(), totalHeight));
    }
    gridColToNodeMap.clear();
    gridColChildren_.clear();
}

void RenderGridRow::LayoutEachChild(
    double columnUnitWidth, double childHeightLimit, double xGutter, GridSizeType sizeType, int32_t columnNum)
{
    auto children = GetChildren();
    std::list<RefPtr<RenderNode>> gridColChildren;
    for (const auto& child : children) {
        RefPtr<RenderNode> childPtr = child;
        FindGridColChild(childPtr);
        auto gridCol = AceType::DynamicCast<RenderGridCol>(childPtr);
        if (!gridCol) {
            LOGE("Not a grid_col component");
            continue;
        }
        auto span = std::min(gridCol->GetSpan(sizeType), columnNum);
        gridCol->SetSizeType(sizeType);
        LayoutParam childLayout(Size(columnUnitWidth * span + (span - 1) * xGutter, childHeightLimit),
            Size(columnUnitWidth * span + (span - 1) * xGutter, 0));
        child->Layout(childLayout);
        gridColChildren.emplace_back(gridCol);
        gridColToNodeMap[gridCol] = child;
    }
    gridColChildren_ = SortChildrenByOrder(gridColChildren);
}

void RenderGridRow::ParseNewLineForLargeOffset(
    int32_t childSpan, int32_t childOffset, int32_t restColumnNum, int32_t totalColumnNum, NewLineOffset& newLineOffset)
{
    int32_t totalOffsetStartFromNewLine = childOffset - restColumnNum;
    if (totalColumnNum <= 0) {
        return;
    }
    newLineOffset.newLineCount = totalOffsetStartFromNewLine / totalColumnNum + 1;
    // ex. totalColumn 12, restColumn is 4, child offset 26, span 6. Offsets of next 2 lines are 12 and 10
    // then the child will be placed at the third new line with offset 0.
    if ((totalOffsetStartFromNewLine % totalColumnNum) + childSpan > totalColumnNum) {
        newLineOffset.offset = 0;
        ++newLineOffset.newLineCount;
    } else {
        // ex. totalColumn 12, restColumn is 4, child offset 20, span 6. Offsets of next 2 lines are 12 and 4
        // then the child will be placed at the second new line with offset 4.
        newLineOffset.offset = totalOffsetStartFromNewLine % totalColumnNum;
    }
}

void RenderGridRow::CalculateOffsetOfNewline(const RefPtr<RenderNode>& node, int32_t currentChildSpan,
    int32_t restColumnNum, int32_t totalColumnNum, GridSizeType sizeType, NewLineOffset& newLineOffset) const
{
    auto gridCol = AceType::DynamicCast<RenderGridCol>(node);
    if (!gridCol) {
        LOGE("Not a grid_col component");
        return;
    }
    newLineOffset.isValid = true;
    auto offset = gridCol->GetOffset(sizeType);
    if (restColumnNum >= offset + currentChildSpan) {
        // in this case, child can be place at current row
        newLineOffset.offset = gridCol->GetOffset(sizeType);
        newLineOffset.newLineCount = 0;
        return;
    }
    // ex. if there are 7 columns left and chile span is 4 or 8(< or > than restColumnNum), offset is 5,
    // child will be set on a new row with offset 0
    if (restColumnNum >= offset) {
        newLineOffset.offset = 0;
        newLineOffset.newLineCount = 1;
    } else {
        ParseNewLineForLargeOffset(currentChildSpan, offset, restColumnNum, totalColumnNum, newLineOffset);
    }
}

int32_t RenderGridRow::GetRelativeOffset(const RefPtr<RenderNode>& node, GridSizeType sizeType) const
{
    auto gridCol = AceType::DynamicCast<RenderGridCol>(node);
    if (!gridCol) {
        LOGE("Not a grid_col component");
        return false;
    }
    return gridCol->GetOffset(sizeType);
}

int32_t RenderGridRow::GetGridColSpan(const RefPtr<RenderNode>& node, GridSizeType sizeType) const
{
    auto gridCol = AceType::DynamicCast<RenderGridCol>(node);
    if (!gridCol) {
        LOGE("Not a grid_col component");
        return 0;
    }
    return gridCol->GetSpan(sizeType);
}

void RenderGridRow::FindGridColChild(RefPtr<RenderNode>& gridColChild) const
{
    while (gridColChild) {
        if (AceType::InstanceOf<RenderGridCol>(gridColChild)) {
            return;
        }
        gridColChild = gridColChild->GetChildren().front();
    }
}
} // namespace OHOS::Ace::V2