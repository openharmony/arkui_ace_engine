/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_v2/grid_layout/grid_container_utils.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::V2 {
namespace {
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
constexpr int BREAKPOINTSIZE = 5;
RefPtr<GridSizeInfo> ParseBreakpoints(const BreakPoints& breakpoints)
{
    auto sizeInfo = AceType::MakeRefPtr<GridSizeInfo>();
    sizeInfo->Reset();
    for (const auto& breakpoint : breakpoints.breakpoints) {
        sizeInfo->sizeInfo.push_back(Framework::StringToDimension(breakpoint));
    }
    return sizeInfo;
}

RefPtr<GridSizeInfo> ParseBreakpoints(const RefPtr<BreakPoints>& breakpoints)
{
    if (!breakpoints) {
        LOGI("user hasnt set breakpoint, use WindowSize and xs: 320vp, sm: 600vp, md: 840vp");
        return AceType::MakeRefPtr<GridSizeInfo>();
    }
    return ParseBreakpoints(*breakpoints);
}

} // namespace

int GridContainerUtils::CalcBreakPoint(const RefPtr<GridSizeInfo> &threshold, double windowWidth)
{
    int index = 0;
    for (const auto &cur : threshold->sizeInfo) {
        if (GreatNotEqual(cur.ConvertToPx(), windowWidth)) {
            break;
        }
        index++;
    }
    return index;
}

GridSizeType GridContainerUtils::ProcessGridSizeType(const V2::BreakPoints& breakpoints, const Size& size,
    const WindowMode& mode, const RefPtr<PipelineBase>& pipeline)
{
    auto threshold = ParseBreakpoints(breakpoints);
    double windowWidth = 0.0;
    if (breakpoints.reference == BreakPointsReference::WindowSize) {
        if (!pipeline) {
            TAG_LOGI(AceLogTag::ACE_GRIDROW, "pipeline is null");
            return GridSizeType::UNDEFINED;
        }
        windowWidth = pipeline->GetDisplayWindowRectInfo().GetSize().Width();
        if (mode == WindowMode::WINDOW_MODE_FLOATING &&
            Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            windowWidth =
                pipeline->CalcPageWidth(windowWidth - 2 * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx());
            int index = CalcBreakPoint(threshold, windowWidth);
            return static_cast<GridSizeType>(index);
        }
        windowWidth = pipeline->CalcPageWidth(windowWidth);
        std::vector<double> breakPoint(BREAKPOINTSIZE, -1.0);
        std::transform(threshold->sizeInfo.begin(), threshold->sizeInfo.end(), breakPoint.begin(), [](Dimension x) {
            return x.ConvertToVp();
        });
        auto custlayoutBreakpoints = WidthLayoutBreakPoint(breakPoint);
        auto breakpoint = GetWidthBreakpoint(custlayoutBreakpoints, pipeline, breakpoints.userDefine);
        return static_cast<GridSizeType>(breakpoint);
    } else {
        windowWidth = size.Width();
    }
    int index = CalcBreakPoint(threshold, windowWidth);
    return static_cast<GridSizeType>(index);
}

WidthBreakpoint GetCalcWidthBreakpoint(
    const OHOS::Ace::WidthLayoutBreakPoint &finalBreakpoints, double density, double width)
{
    WidthBreakpoint breakpoint;
    if (finalBreakpoints.widthVPXS_ < 0 || GreatNotEqual(finalBreakpoints.widthVPXS_ * density, width)) {
        breakpoint = WidthBreakpoint::WIDTH_XS;
    } else if (finalBreakpoints.widthVPSM_ < 0 || GreatNotEqual(finalBreakpoints.widthVPSM_ * density, width)) {
        breakpoint = WidthBreakpoint::WIDTH_SM;
    } else if (finalBreakpoints.widthVPMD_ < 0 || GreatNotEqual(finalBreakpoints.widthVPMD_ * density, width)) {
        breakpoint = WidthBreakpoint::WIDTH_MD;
    } else if (finalBreakpoints.widthVPLG_ < 0 || GreatNotEqual(finalBreakpoints.widthVPLG_ * density, width)) {
        breakpoint = WidthBreakpoint::WIDTH_LG;
    } else if (finalBreakpoints.widthVPXL_ < 0 || GreatNotEqual(finalBreakpoints.widthVPXL_ * density, width)) {
        breakpoint = WidthBreakpoint::WIDTH_XL;
    } else {
        breakpoint = WidthBreakpoint::WIDTH_XXL;
    }
    return breakpoint;
}

WidthBreakpoint GridContainerUtils::GetWidthBreakpoint(
    const WidthLayoutBreakPoint &custlayoutBreakpoints, const RefPtr<PipelineBase>& pipeline, bool userDefine)
{
    auto finalBreakpoints = WidthLayoutBreakPoint(320.0, 600.0, 840.0, -1.0, -1.0);
    auto configBreakpoints = SystemProperties::GetWidthLayoutBreakpoints();
    if (userDefine) {  // cust has value
        finalBreakpoints = custlayoutBreakpoints;
    } else if (configBreakpoints != WidthLayoutBreakPoint()) {  // ccm has value
        finalBreakpoints = configBreakpoints;
    }
    double density = pipeline->GetCurrentDensity();
    return GetCalcWidthBreakpoint(finalBreakpoints, density, pipeline->GetPageWidth());
}

GridSizeType GridContainerUtils::ProcessGridSizeType(
    const RefPtr<BreakPoints>& breakpoints, const Size& size, const RefPtr<PipelineContext>& pipeline)
{
    auto threshold = ParseBreakpoints(breakpoints);
    double windowWidth = 0.0;
    CHECK_NULL_RETURN(pipeline, GridSizeType::UNDEFINED);
    if (breakpoints->reference == BreakPointsReference::WindowSize) {
        windowWidth = GridSystemManager::GetInstance().GetScreenWidth();
        auto windowManager = pipeline->GetWindowManager();
        auto mode = windowManager->GetWindowMode();
        if (mode == WindowMode::WINDOW_MODE_FLOATING
            && Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            windowWidth -= 2 * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
        }
    } else {
        windowWidth = size.Width();
    }
    int index = 0;
    for (const auto& cur : threshold->sizeInfo) {
        if (pipeline->NormalizeToPx(cur) > windowWidth) {
            break;
        }
        index++;
    }
    return static_cast<GridSizeType>(index);
}

std::pair<Dimension, Dimension> GridContainerUtils::ProcessGutter(GridSizeType sizeType, const Gutter& gutter)
{
    switch (sizeType) {
        case GridSizeType::XS:
            return std::pair<Dimension, Dimension>(gutter.xXs, gutter.yXs);
        case GridSizeType::SM:
            return std::pair<Dimension, Dimension>(gutter.xSm, gutter.ySm);
        case GridSizeType::MD:
            return std::pair<Dimension, Dimension>(gutter.xMd, gutter.yMd);
        case GridSizeType::LG:
            return std::pair<Dimension, Dimension>(gutter.xLg, gutter.yLg);
        case GridSizeType::XL:
            return std::pair<Dimension, Dimension>(gutter.xXl, gutter.yXl);
        case GridSizeType::XXL:
            return std::pair<Dimension, Dimension>(gutter.xXXl, gutter.yXXl);
        default:
            return std::pair<Dimension, Dimension>(gutter.xXs, gutter.yXs);
    }
}

std::pair<Dimension, Dimension> GridContainerUtils::ProcessGutter(GridSizeType sizeType, const RefPtr<Gutter>& gutter)
{
    return ProcessGutter(sizeType, *gutter);
}

int32_t GridContainerUtils::ProcessColumn(GridSizeType sizeType, const GridContainerSize& columnNum)
{
    switch (sizeType) {
        case GridSizeType::XS:
            return columnNum.xs;
        case GridSizeType::SM:
            return columnNum.sm;
        case GridSizeType::MD:
            return columnNum.md;
        case GridSizeType::LG:
            return columnNum.lg;
        case GridSizeType::XL:
            return columnNum.xl;
        case GridSizeType::XXL:
            return columnNum.xxl;
        default:
            return columnNum.xs;
    }
}

int32_t GridContainerUtils::ProcessColumn(GridSizeType sizeType, const RefPtr<GridContainerSize>& columnNum)
{
    return ProcessColumn(sizeType, *columnNum);
}

double GridContainerUtils::ProcessColumnWidth(const std::pair<double, double>& gutter, int32_t columnNum, double width)
{
    auto xGutter = gutter.first;
    if (columnNum != 0) {
        return (width - (columnNum - 1) * xGutter) / columnNum;
    }
    return 0.0;
}

void GridContainerUtils::InheritGridRowColumns(const RefPtr<V2::GridContainerSize>& gridContainerSize,
    int32_t *containerSizeArray, int32_t size)
{
    for (auto i = 0; i < size; ++i) {
        if (containerSizeArray[i] > 0) {
            containerSizeArray[0] = containerSizeArray[i];
            break;
        }
    }
    if (containerSizeArray[0] <= 0) {
        return;
    }
    for (auto i = 1; i < size; ++i) {
        if (containerSizeArray[i] <= 0) {
            containerSizeArray[i] = containerSizeArray[i - 1];
        }
    }
    gridContainerSize->xs = containerSizeArray[XS];
    gridContainerSize->sm = containerSizeArray[SM];
    gridContainerSize->md = containerSizeArray[MD];
    gridContainerSize->lg = containerSizeArray[LG];
    gridContainerSize->xl = containerSizeArray[XL];
    gridContainerSize->xxl = containerSizeArray[XXL];
}
} // namespace OHOS::Ace::V2
