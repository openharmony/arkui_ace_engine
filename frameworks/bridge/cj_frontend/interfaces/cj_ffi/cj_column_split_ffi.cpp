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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_column_split_ffi.h"

#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkColumnSplitCreate()
{
    LinearSplitModel::GetInstance()->Create(NG::SplitType::COLUMN_SPLIT);
}

void FfiOHOSAceFrameworkColumnSplitResizeable(bool resizeable)
{
    LinearSplitModel::GetInstance()->SetResizable(NG::SplitType::COLUMN_SPLIT, resizeable);
}

void FfiOHOSAceFrameworkColumnSplitDivider(DividerParam params)
{
    Dimension startMarginDime(params.startMargin, static_cast<DimensionUnit>(params.startMarginUnit));
    Dimension endMarginDime(params.endMargin, static_cast<DimensionUnit>(params.endMarginUnit));

    NG::ItemDivider divider;
    divider.startMargin = startMarginDime;
    divider.endMargin = endMarginDime;

    LinearSplitModel::GetInstance()->SetDivider(NG::SplitType::COLUMN_SPLIT, divider);
}

void FfiOHOSAceFrameworkColumnSplitClip(bool isClip)
{
    ViewAbstractModel::GetInstance()->SetClipEdge(isClip);
}

void FfiOHOSAceFrameworkColumnSplitClipByShape(int64_t shapeId)
{
    auto context = FFIData::GetData<NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        ViewAbstractModel::GetInstance()->SetClipShape(context->GetBasicShape());
    } else {
        LOGE("set clip error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}
}
