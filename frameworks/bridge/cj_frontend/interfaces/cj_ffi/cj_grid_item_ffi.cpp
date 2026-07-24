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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_item_ffi.h"

#include "cj_lambda.h"

#include "base/utils/utils.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/grid/grid_item_model.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkGridItemCreate()
{
    NG::GridItemStyle style {};
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->Create(style);
}

void FfiOHOSAceFrameworkGridItemCreateWithOptions(int32_t value)
{
    auto style = static_cast<NG::GridItemStyle>(value);
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->Create(style);
}

void FfiOHOSAceFrameworkGridItemSetColumnStart(int32_t columnStart)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetColumnStart(columnStart);
}

void FfiOHOSAceFrameworkGridItemSetColumnEnd(int32_t columnEnd)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetColumnEnd(columnEnd);
}

void FfiOHOSAceFrameworkGridItemSetRowStart(int32_t rowStart)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetRowStart(rowStart);
}

void FfiOHOSAceFrameworkGridItemSetRowEnd(int32_t rowEnd)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetRowEnd(rowEnd);
}

void FfiOHOSAceFrameworkGridItemForceRebuild(bool forceRebuild)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetForceRebuild(forceRebuild);
}

void FfiOHOSAceFrameworkGridItemSelectable(bool value)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetSelectable(value);
}

void FfiOHOSAceFrameworkGridItemSelected(bool value)
{
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetSelected(value);
}

void FfiOHOSAceFrameworkGridItemOnSelect(void (*callback)(bool isSelected))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelectId = [node = targetNode, lambda](bool isSelected) {
        PipelineContext::SetCallBackNode(node);
        lambda(isSelected);
    };
    if (GridItemModel::GetInstance() == nullptr) {
        LOGE("GridItem Instance is null");
        return;
    }
    GridItemModel::GetInstance()->SetOnSelect(std::move(onSelectId));
}
}
