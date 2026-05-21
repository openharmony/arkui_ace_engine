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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_col_ffi.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"

using namespace OHOS::Ace;

namespace OHOS::Ace {
NG::GridColModelNG* GetGridColModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("GridCol");
    if (module == nullptr) {
        LOGF_ABORT("Can't find gridcol dynamic module");
    }
    return reinterpret_cast<NG::GridColModelNG*>(module->GetModel());
}
} // namespace OHOS::Ace

namespace {
constexpr size_t MAX_NUMBER_BREAKPOINT = 6;

void InheritGridContainerSize(V2::GridContainerSize& gridContainerSize,
    std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT], int32_t defaultVal)
{
    if (!containerSizeArray[0].has_value()) {
        containerSizeArray[0] = defaultVal;
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    int32_t index = 0;
    gridContainerSize.xs = containerSizeArray[index++].value();
    gridContainerSize.sm = containerSizeArray[index++].value();
    gridContainerSize.md = containerSizeArray[index++].value();
    gridContainerSize.lg = containerSizeArray[index++].value();
    gridContainerSize.xl = containerSizeArray[index++].value();
    gridContainerSize.xxl = containerSizeArray[index].value();
}

V2::GridContainerSize ParserGridContainerSize(int32_t columnNumber, int32_t defaultVal)
{
    auto gridContainerSize = columnNumber >= 0 ? V2::GridContainerSize(columnNumber)
                                               : V2::GridContainerSize(defaultVal);
    return gridContainerSize;
}

V2::GridContainerSize ParserGridContainerSize(GridRowColumnOption columnNumber, int32_t defaultVal)
{
    auto gridContainerSize = V2::GridContainerSize(defaultVal);
    std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
    int32_t index = 0;
    containerSizeArray[index++] = columnNumber.xs;
    containerSizeArray[index++] = columnNumber.sm;
    containerSizeArray[index++] = columnNumber.md;
    containerSizeArray[index++] = columnNumber.lg;
    containerSizeArray[index++] = columnNumber.xl;
    containerSizeArray[index] = columnNumber.xxl;
    InheritGridContainerSize(gridContainerSize, containerSizeArray, defaultVal);
    return gridContainerSize;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkGridColCreate()
{
    GetGridColModel()->Create();
}

void FfiOHOSAceFrameworkGridColCreateWithInt32(int32_t span, int32_t offset, int32_t order)
{
    auto spanSize = ParserGridContainerSize(span, 1);
    auto offsetSize = ParserGridContainerSize(offset, 0);
    auto orderSize = ParserGridContainerSize(order, 0);
    GetGridColModel()->Create(spanSize, offsetSize, orderSize);
}

void FfiOHOSAceFrameworkGridColCreateWithOption(
    GridRowColumnOption span, GridRowColumnOption offset, GridRowColumnOption order)
{
    auto spanSize = ParserGridContainerSize(span, 1);
    auto offsetSize = ParserGridContainerSize(offset, 0);
    auto orderSize = ParserGridContainerSize(order, 0);
    GetGridColModel()->Create(spanSize, offsetSize, orderSize);
}

void FfiOHOSAceFrameworkGridColSetSpan(int32_t span)
{
    auto spanSize = ParserGridContainerSize(span, 1);
    GetGridColModel()->SetSpan(spanSize);
}

void FfiOHOSAceFrameworkGridColSetSpanWithOption(GridRowColumnOption span)
{
    auto spanSize = ParserGridContainerSize(span, 1);
    GetGridColModel()->SetSpan(spanSize);
}

void FfiOHOSAceFrameworkGridColSetOffset(int32_t offset)
{
    auto offsetSize = ParserGridContainerSize(offset, 0);
    GetGridColModel()->SetOffset(offsetSize);
}

void FfiOHOSAceFrameworkGridColSetOffsetWithOption(GridRowColumnOption offset)
{
    auto offsetSize = ParserGridContainerSize(offset, 0);
    GetGridColModel()->SetOffset(offsetSize);
}

void FfiOHOSAceFrameworkGridColSetOrder(int32_t order)
{
    auto orderSize = ParserGridContainerSize(order, 0);
    GetGridColModel()->SetOrder(orderSize);
}

void FfiOHOSAceFrameworkGridColSetOrderWithOption(GridRowColumnOption order)
{
    auto orderSize = ParserGridContainerSize(order, 0);
    GetGridColModel()->SetOrder(orderSize);
}
}
