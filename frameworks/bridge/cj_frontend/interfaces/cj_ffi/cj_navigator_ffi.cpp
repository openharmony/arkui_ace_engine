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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkNavigatorCreate(const char* target, int32_t type)
{
    NavigatorModel::GetInstance()->Create();
    NavigatorModel::GetInstance()->SetUri(target);
    NavigatorType navigatorType = NavigatorType(type);
    if (navigatorType == NavigatorType::DEFAULT) {
        NavigatorModel::GetInstance()->SetType(NavigatorType::PUSH);
    } else {
        NavigatorModel::GetInstance()->SetType(navigatorType);
    }
}

void FfiOHOSAceFrameworkNavigatorSetParams(const char* args)
{
    NavigatorModel::GetInstance()->SetParams(args);
}

void FfiOHOSAceFrameworkNavigatorSetActive(bool active)
{
    NavigatorModel::GetInstance()->SetActive(active);
}

void FfiOHOSAceFrameworkNavigatorSetWidth(double width, int32_t unit)
{
    NavigatorModel::GetInstance()->SetIsDefWidth(true);
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);
}

void FfiOHOSAceFrameworkNavigatorSetHeight(double height, int32_t unit)
{
    NavigatorModel::GetInstance()->SetIsDefHeight(true);
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
}

void FfiOHOSAceFrameworkNavigatorSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    FfiOHOSAceFrameworkNavigatorSetWidth(width, widthUnit);
    FfiOHOSAceFrameworkNavigatorSetHeight(height, heightUnit);
}
}
