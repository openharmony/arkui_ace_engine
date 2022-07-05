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

#include "core/components_v2/grid_layout/grid_container_utils.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::V2 {
namespace {

RefPtr<GridSizeInfo> ParseBreakpoints(const RefPtr<BreakPoints>& breakpoints)
{
    auto sizeInfo = AceType::MakeRefPtr<GridSizeInfo>();
    if (!breakpoints) {
        LOGI("user hasnt set breakpoint, use WindowSize and xs: 320vp, sm: 520vp, md: 840vp");
    } else {
        sizeInfo->Reset();
        for (const auto& breakpoint : breakpoints->breakpoints) {
            sizeInfo->sizeInfo.push_back(Framework::StringToDimension(breakpoint));
        }
    }
    return sizeInfo;
}

} // namespace

GridSizeType GridContainerUtils::ProcessGridSizeType(
    const RefPtr<BreakPoints>& breakpoints, const Size& size, const RefPtr<PipelineContext>& pipeline)
{
    auto threadhold = ParseBreakpoints(breakpoints);
    double windowWidth = 0.0;
    if (breakpoints->reference == BreakPointsReference::WindowSize) {
        windowWidth = GridSystemManager::GetInstance().GetScreenWidth();
    } else {
        windowWidth = size.Width();
    }
    int index = 0;
    for (const auto& cur : threadhold->sizeInfo) {
        if (pipeline->NormalizeToPx(cur) > windowWidth) {
            break;
        }
        index++;
    }
    return static_cast<GridSizeType>(index);
}

std::pair<Dimension, Dimension> GridContainerUtils::ProcessGetter(GridSizeType sizeType, const RefPtr<Getter>& getter)
{
    switch (sizeType) {
        case GridSizeType::XS:
            return std::pair<Dimension, Dimension>(getter->xXs, getter->yXs);
        case GridSizeType::SM:
            return std::pair<Dimension, Dimension>(getter->xSm, getter->ySm);
        case GridSizeType::MD:
            return std::pair<Dimension, Dimension>(getter->xMd, getter->yMd);
        case GridSizeType::LG:
            return std::pair<Dimension, Dimension>(getter->xLg, getter->yLg);
        case GridSizeType::XL:
            return std::pair<Dimension, Dimension>(getter->xXl, getter->yXl);
        case GridSizeType::XXL:
            return std::pair<Dimension, Dimension>(getter->xXXl, getter->yXXl);
        default:
            return std::pair<Dimension, Dimension>(getter->xXs, getter->yXs);
    }
}

int32_t GridContainerUtils::ProcessColumn(GridSizeType sizeType, const RefPtr<GridContainerSize>& columnNum)
{
    switch (sizeType) {
        case GridSizeType::XS:
            return columnNum->xs;
        case GridSizeType::SM:
            return columnNum->sm;
        case GridSizeType::MD:
            return columnNum->md;
        case GridSizeType::LG:
            return columnNum->lg;
        case GridSizeType::XL:
            return columnNum->xl;
        case GridSizeType::XXL:
            return columnNum->xxl;
        default:
            return columnNum->xs;
    }
}

double GridContainerUtils::ProcessColumnWidth(
    const std::pair<double, double>& getter, int32_t columnNum, const Size& size)
{
    auto xGetter = getter.first;
    if (columnNum != 0) {
        return (size.Width() - (columnNum - 1) * xGetter) / columnNum;
    }
    return 0.0;
}

} // namespace OHOS::Ace::V2
