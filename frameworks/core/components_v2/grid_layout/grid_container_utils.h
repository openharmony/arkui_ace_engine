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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_COL_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_COL_UTILS_H

#include <utility>

#include "base/memory/ace_type.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/geometry/size.h"
#include "frameworks/core/pipeline/pipeline_context.h"

namespace OHOS::Ace::V2 {

class GridContainerUtils : public AceType {
    DECLARE_ACE_TYPE(GridContainerUtils, AceType);

public:
    ~GridContainerUtils() override = default;

    static GridSizeType ProcessGridSizeType(const V2::BreakPoints& breakpoints, const Size& size,
        const WindowMode& mode, const RefPtr<PipelineBase>& pipeline = nullptr);
    static GridSizeType ProcessGridSizeType(
        const RefPtr<BreakPoints>& breakpoints, const Size& size, const RefPtr<PipelineContext>& pipeline);
    static std::pair<Dimension, Dimension> ProcessGutter(GridSizeType sizeType, const RefPtr<Gutter>& gutter);
    static std::pair<Dimension, Dimension> ProcessGutter(GridSizeType sizeType, const Gutter& gutter);

    static int32_t ProcessColumn(GridSizeType sizeType, const GridContainerSize& columnNum);
    static int32_t ProcessColumn(GridSizeType sizeType, const RefPtr<GridContainerSize>& columnNum);
    static double ProcessColumnWidth(const std::pair<double, double>& gutter, int32_t columnNum, double size);
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_COL_UTILS_H