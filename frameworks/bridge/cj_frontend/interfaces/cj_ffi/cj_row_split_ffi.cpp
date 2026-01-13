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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_row_split_ffi.h"

#include "base/log/log_wrapper.h"
#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::LinearSplitModelNG* GetRowSplitModel()
{
    static NG::LinearSplitModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("RowSplit");
        if (module == nullptr) {
            LOGF("Can't find row split dynamic module");
            abort();
        }
        return reinterpret_cast<NG::LinearSplitModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkRowSplitCreate()
{
    GetRowSplitModel()->Create(NG::SplitType::ROW_SPLIT);
}

void FfiOHOSAceFrameworkRowSplitResizeable(bool resizeable)
{
    GetRowSplitModel()->SetResizable(NG::SplitType::ROW_SPLIT, resizeable);
}

void FfiOHOSAceFrameworkRowSplitClip(bool isClip)
{
    ViewAbstractModel::GetInstance()->SetClipEdge(isClip);
}

void FfiOHOSAceFrameworkRowSplitClipByShape(int64_t shapeId)
{
    auto context = FFIData::GetData<NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        ViewAbstractModel::GetInstance()->SetClipShape(context->GetBasicShape());
    } else {
        LOGE("set clip error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}
}
