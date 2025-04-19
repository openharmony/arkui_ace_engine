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
#include "core/interfaces/native/node/lazy_grid_layout_modifier.h"

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"

namespace OHOS::Ace::NG {
namespace {
    const std::string DEFAULT_ROWS_TEMPLATE = "1fr";
    const std::string DEFAULT_COLUMNS_TEMPLATE = "1fr";
    constexpr Dimension DEFAULT_COLUMNS_GAP = 0.0_fp;
    constexpr Dimension DEFAULT_ROWS_GAP = 0.0_fp;
}

void SetLazyGridLayoutColumnsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(columnsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(columnsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(columnsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyGridLayoutModel::SetColumnGap(frameNode, gap);
}

void ResetLazyGridLayoutColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModel::SetColumnGap(frameNode, DEFAULT_COLUMNS_GAP);
}

void SetLazyGridLayoutRowsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(rowsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(rowsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(rowsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyGridLayoutModel::SetRowGap(frameNode, gap);
}

void ResetLazyGridLayoutRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModel::SetRowGap(frameNode, DEFAULT_ROWS_GAP);
}

void SetLazyGridLayoutColumnsTemplate(ArkUINodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyVGridLayoutModel::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetLazyGridLayoutColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyVGridLayoutModel::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}

namespace NodeModifier {
const ArkUILazyGridLayoutModifier* GetLazyGridLayoutModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILazyGridLayoutModifier modifier = {
        .setColumnsGap = SetLazyGridLayoutColumnsGap,
        .resetColumnsGap = ResetLazyGridLayoutColumnsGap,
        .setRowsGap = SetLazyGridLayoutRowsGap,
        .resetRowsGap = ResetLazyGridLayoutRowsGap,
        .setColumnsTemplate = SetLazyGridLayoutColumnsTemplate,
        .resetColumnsTemplate = ResetLazyGridLayoutColumnsTemplate,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
