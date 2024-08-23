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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_radio_ffi.h"


#include "cj_lambda.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

using namespace OHOS::Ace;

extern "C" {
void FfiOHOSAceFrameworkRadioCreate(const char* group, const char* value)
{
    std::optional<int32_t> indicator;
    RadioModel::GetInstance()->Create(std::optional<std::string>(value), std::optional<std::string>(group), indicator);
}
void FfiOHOSAceFrameworkRadioChecked(bool value)
{
    RadioModel::GetInstance()->SetChecked(value);
}
void FfiOHOSAceFrameworkRadioOnChange(void (*callback)(bool isChecked))
{
    RadioModel::GetInstance()->SetOnChange(CJLambda::Create(callback));
}

void FfiRadioSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    RadioModel::GetInstance()->SetResponseRegion(result);
}

void FfiRadioSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    RadioModel::GetInstance()->SetResponseRegion(result);
}
}
