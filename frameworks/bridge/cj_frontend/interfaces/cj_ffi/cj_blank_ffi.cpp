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

#include "cj_blank_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::BlankModelNG* GetBlankModel()
{
    static NG::BlankModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Blank");
        if (module == nullptr) {
            LOGF_ABORT("Can't find blank dynamic module");
        }
        model = reinterpret_cast<NG::BlankModelNG*>(module->GetModel());
    }
    return model;
}

} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkBlankCreate(double minSize, int32_t unit)
{
    Dimension blankMin(minSize, static_cast<DimensionUnit>(unit));
    GetBlankModel()->Create();
    GetBlankModel()->SetBlankMin(blankMin);
}
void FfiOHOSAceFrameworkBlankHeight(double height, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
    Dimension value(height, static_cast<DimensionUnit>(unit));
    GetBlankModel()->SetHeight(value);
}
}
