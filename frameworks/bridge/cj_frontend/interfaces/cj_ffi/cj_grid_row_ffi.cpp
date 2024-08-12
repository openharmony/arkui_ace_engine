/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_row_ffi.h"

#include "cj_lambda.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

using namespace OHOS::Ace;

namespace {
constexpr size_t MAX_NUMBER_BREAKPOINT = 6;

void InheritGridRowOption(const RefPtr<V2::GridContainerSize>& gridContainerSize,
    std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
{
    if (!containerSizeArray[0].has_value()) {
        containerSizeArray[0] = V2::DEFAULT_COLUMN_NUMBER;
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    int32_t index = 0;
    gridContainerSize->xs = containerSizeArray[index++].value();
    gridContainerSize->sm = containerSizeArray[index++].value();
    gridContainerSize->md = containerSizeArray[index++].value();
    gridContainerSize->lg = containerSizeArray[index++].value();
    gridContainerSize->xl = containerSizeArray[index++].value();
    gridContainerSize->xxl = containerSizeArray[index].value();
}

RefPtr<V2::GridContainerSize> ParserColumns(int32_t columns)
{
    return columns > 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(columns)
                       : AceType::MakeRefPtr<V2::GridContainerSize>();
}

RefPtr<V2::GridContainerSize> ParserColumns(const GridRowColumnOption& columns)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(12);
    std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
    int32_t index = 0;
    containerSizeArray[index++] = columns.xs;
    containerSizeArray[index++] = columns.sm;
    containerSizeArray[index++] = columns.md;
    containerSizeArray[index++] = columns.lg;
    containerSizeArray[index++] = columns.xl;
    containerSizeArray[index] = columns.xxl;
    InheritGridRowOption(gridContainerSize, containerSizeArray);
    return gridContainerSize;
}

void InheritGridRowGutterOption(const RefPtr<V2::Gutter>& gutter,
    std::optional<Dimension> (&gutterSizeArray)[MAX_NUMBER_BREAKPOINT], bool isHorizontal)
{
    if (!gutterSizeArray[0].has_value()) {
        gutterSizeArray[0] = Dimension(0);
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!gutterSizeArray[i].has_value()) {
            gutterSizeArray[i] = gutterSizeArray[i - 1].value();
        }
    }
    if (isHorizontal) {
        int32_t indexHorizontal = 0;
        gutter->xXs = gutterSizeArray[indexHorizontal++].value();
        gutter->xSm = gutterSizeArray[indexHorizontal++].value();
        gutter->xMd = gutterSizeArray[indexHorizontal++].value();
        gutter->xLg = gutterSizeArray[indexHorizontal++].value();
        gutter->xXl = gutterSizeArray[indexHorizontal++].value();
        gutter->xXXl = gutterSizeArray[indexHorizontal].value();
        return;
    }
    int32_t index = 0;
    gutter->yXs = gutterSizeArray[index++].value();
    gutter->ySm = gutterSizeArray[index++].value();
    gutter->yMd = gutterSizeArray[index++].value();
    gutter->yLg = gutterSizeArray[index++].value();
    gutter->yXl = gutterSizeArray[index++].value();
    gutter->yXXl = gutterSizeArray[index].value();
}

void ParseGutterObject(const AtCGridRowSizeOption& gutterObject, RefPtr<V2::Gutter>& gutter, bool isHorizontal)
{
    std::optional<Dimension> gutterOptions[MAX_NUMBER_BREAKPOINT];
    for (size_t i = 0; i < MAX_NUMBER_BREAKPOINT; ++i) {
        gutterOptions[i] = Dimension(gutterObject.data[i].value, static_cast<DimensionUnit>(gutterObject.data[i].unit));
    }
    InheritGridRowGutterOption(gutter, gutterOptions, isHorizontal);
}

RefPtr<V2::Gutter> ParserGutter(const AtCGridRowSizeOption& x, const AtCGridRowSizeOption& y)
{
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();

    ParseGutterObject(x, gutter, true);
    ParseGutterObject(y, gutter, false);
    return gutter;
}

RefPtr<V2::Gutter> ParserGutter(double x, int32_t xUnit, double y, int32_t yUnit)
{
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    gutter->SetXGutter(Dimension(x, static_cast<DimensionUnit>(xUnit)));
    gutter->SetYGutter(Dimension(y, static_cast<DimensionUnit>(yUnit)));
    return gutter;
}

RefPtr<V2::Gutter> ParserGutter(const Dimension& gutterDim)
{
    auto gutter = AceType::MakeRefPtr<V2::Gutter>(gutterDim);
    return gutter;
}

RefPtr<V2::BreakPoints> ParserBreakpoints(
    VectorFloat64Handle valuesHandle, VectorInt32Handle unitsHandle, int32_t breakpointReference)
{
    auto breakpoint = AceType::MakeRefPtr<V2::BreakPoints>();
    breakpoint->reference = static_cast<V2::BreakPointsReference>(breakpointReference);
    breakpoint->breakpoints.clear();
    const auto& valueVec = *reinterpret_cast<std::vector<double>*>(valuesHandle);
    const auto& unitVec = *reinterpret_cast<std::vector<int32_t>*>(unitsHandle);
    if (valueVec.size() > MAX_NUMBER_BREAKPOINT - 1) {
        LOGI("The maximum number of breakpoints is %{public}zu", MAX_NUMBER_BREAKPOINT);
        return breakpoint;
    }
    double width = -1.0;

    for (size_t i = 0; i < valueVec.size(); i++) {
        if (GreatNotEqual(width, valueVec[i])) {
            LOGI("Array data must be sorted in ascending order");
            return breakpoint;
        }
        Dimension valueDimension(valueVec[i], static_cast<DimensionUnit>(unitVec[i]));
        breakpoint->breakpoints.push_back(valueDimension.ToString());
    }
    return breakpoint;
}

V2::GridRowDirection ParserDirection(int32_t direction)
{
    return static_cast<V2::GridRowDirection>(direction);
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkGridRowCreate()
{
    GridRowModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkGridRowCreateWithFloat64Int32(GridRowCreateWithFloat64Int32 createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter =
        ParserGutter(Dimension(createOption.gutterValue, static_cast<DimensionUnit>(createOption.gutterUnit)));
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);
    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowCreateWithFloat64ColumnOption(GridRowCreateWithFloat64ColumnOption createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter =
        ParserGutter(Dimension(createOption.gutterValue, static_cast<DimensionUnit>(createOption.gutterUnit)));
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);

    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowCreateWithFloat64OptionColumnOption(
    GridRowCreateWithFloat64OptionColumnOption createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter = ParserGutter(createOption.x, createOption.xUnit, createOption.y, createOption.yUnit);
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);

    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowCreateWithSizeOptionColumnOption(GridRowCreateWithSizeOptionColumnOption createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter = ParserGutter(createOption.x, createOption.y);
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);

    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowCreateWithFloat64OptionInt32(GridRowCreateWithFloat64OptionInt32 createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter = ParserGutter(createOption.x, createOption.xUnit, createOption.y, createOption.yUnit);
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);

    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowCreateWithSizeOptionInt32(GridRowCreateWithSizeOptionInt32 createOption)
{
    auto parsedColumns = ParserColumns(createOption.columns);
    auto parsedGutter = ParserGutter(createOption.x, createOption.y);
    auto parsedBreakpoints =
        ParserBreakpoints(createOption.breakpointVals, createOption.breakpointUnits, createOption.breakpointReference);
    auto parsedDirection = ParserDirection(createOption.direction);

    GridRowModel::GetInstance()->Create(parsedColumns, parsedGutter, parsedBreakpoints, parsedDirection);
}

void FfiOHOSAceFrameworkGridRowSetHeight(double height, int32_t heightUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, heightUnit);
    GridRowModel::GetInstance()->SetHeight();
}

void FfiOHOSAceFrameworkGridRowBreakpointEvent(void (*callback)(const char*))
{
    auto onHover = CJLambda::Create(callback);
    auto onBreakpointChange = [func = std::move(onHover)](const std::string& value) { func(value.c_str()); };
    GridRowModel::GetInstance()->SetOnBreakPointChange(onBreakpointChange);
}

void FfiOHOSAceFrameworkGridRowAlignItem(int32_t alignItem)
{
    if (alignItem == static_cast<int32_t>(FlexAlign::FLEX_START) ||
        alignItem == static_cast<int32_t>(FlexAlign::FLEX_END) ||
        alignItem == static_cast<int32_t>(FlexAlign::CENTER) || alignItem == static_cast<int32_t>(FlexAlign::STRETCH)) {
        GridRowModel::GetInstance()->SetAlignItems(static_cast<FlexAlign>(alignItem));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        GridRowModel::GetInstance()->SetAlignItems(FlexAlign::FLEX_START);
    }
}
}
