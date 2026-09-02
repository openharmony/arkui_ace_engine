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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigator_ffi.h"

#include "base/log/log_wrapper.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::NavigatorModelNG* GetNavigatorModel()
{
    static NG::NavigatorModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Navigator");
        if (module == nullptr) {
            LOGF_ABORT("Can't find navigator dynamic module");
        }
        model = reinterpret_cast<NG::NavigatorModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkNavigatorCreate(const char* target, int32_t type)
{
    GetNavigatorModel()->Create();
    GetNavigatorModel()->SetUri(target);
    NavigatorType navigatorType = NavigatorType(type);
    if (navigatorType == NavigatorType::DEFAULT) {
        GetNavigatorModel()->SetType(NavigatorType::PUSH);
    } else {
        GetNavigatorModel()->SetType(navigatorType);
    }
}

void FfiOHOSAceFrameworkNavigatorSetParams(const char* args)
{
    GetNavigatorModel()->SetParams(args);
}

void FfiOHOSAceFrameworkNavigatorSetActive(bool active)
{
    GetNavigatorModel()->SetActive(active);
}

void FfiOHOSAceFrameworkNavigatorSetWidth(double width, int32_t unit)
{
    GetNavigatorModel()->SetIsDefWidth(true);
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);
}

void FfiOHOSAceFrameworkNavigatorSetHeight(double height, int32_t unit)
{
    GetNavigatorModel()->SetIsDefHeight(true);
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
}

void FfiOHOSAceFrameworkNavigatorSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    FfiOHOSAceFrameworkNavigatorSetWidth(width, widthUnit);
    FfiOHOSAceFrameworkNavigatorSetHeight(height, heightUnit);
}
}
