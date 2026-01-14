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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_counter_ffi.h"

#include "cj_lambda.h"
#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::CounterModelNG* GetCounterModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Counter");
    if (module == nullptr) {
        LOGF("Can't find counter dynamic module");
        abort();
    }
    return reinterpret_cast<NG::CounterModelNG*>(module->GetModel());
}

}

extern "C" {
void FfiOHOSAceFrameworkCounterCreate()
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->Create();
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetWidth(double value, int32_t unit)
{
    Dimension dValue(value, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetWidth(dValue);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetHeight(double value, int32_t unit)
{
    Dimension dValue(value, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetHeight(dValue);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    FfiOHOSAceFrameworkCounterSetWidth(width, widthUnit);
    FfiOHOSAceFrameworkCounterSetHeight(height, heightUnit);
}

void FfiOHOSAceFrameworkCounterSetControlWidth(double value, int32_t unit)
{
    Dimension dValue(value, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetControlWidth(dValue);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetStateChange(bool state)
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetStateChange(state);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetBackgroundColor(uint32_t color)
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetBackgroundColor(Color(color));
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterEnableDec(bool enable)
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetEnableDec(enable);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterEnableInc(bool enable)
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetEnableInc(enable);
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetOnInc(void (*callback)())
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetOnInc(CJLambda::Create(callback));
    } else {
        LOGE("Counter Instance is null");
    }
}

void FfiOHOSAceFrameworkCounterSetOnDec(void (*callback)())
{
    if (GetCounterModel() != nullptr) {
        GetCounterModel()->SetOnDec(CJLambda::Create(callback));
    } else {
        LOGE("Counter Instance is null");
    }
}
}
