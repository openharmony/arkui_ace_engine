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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_marquee_ffi.h"

#include "cj_lambda.h"
#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::MarqueeModelNG* GetMarqueeModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("marquee");
    if (module == nullptr) {
        LOGF("Can't find marquee dynamic module");
        abort();
    }
    return reinterpret_cast<NG::MarqueeModelNG*>(module->GetModel());
}
}
extern "C" {
void FfiOHOSAceFrameworkMarqueeCreate(bool start, const char* src, double step, int32_t loop, bool fromStart)
{
    GetMarqueeModel()->Create();
    GetMarqueeModel()->SetValue(src);
    GetMarqueeModel()->SetPlayerStatus(start);
    GetMarqueeModel()->SetScrollAmount(step);
    GetMarqueeModel()->SetLoop(loop);
    if (fromStart) {
        GetMarqueeModel()->SetDirection(MarqueeDirection::LEFT);
    } else {
        GetMarqueeModel()->SetDirection(MarqueeDirection::RIGHT);
    }
}

void FfiOHOSAceFrameworkMarqueeSetAllowScale(bool value)
{
    GetMarqueeModel()->SetAllowScale(value);
}

void FfiOHOSAceFrameworkMarqueeSetFontColor(uint32_t color)
{
    GetMarqueeModel()->SetTextColor(Color(color));
}

void FfiOHOSAceFrameworkMarqueeSetFontSize(double value, int32_t unit)
{
    Dimension fontSize(value, static_cast<DimensionUnit>(unit));
    GetMarqueeModel()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkMarqueeSetFontWeight(const char* fontWeight)
{
    GetMarqueeModel()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkMarqueeSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    GetMarqueeModel()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkMarqueeSetMarqueeUpdateStrategy(int32_t value)
{
    if (value == 0) {
        GetMarqueeModel()->SetMarqueeUpdateStrategy(MarqueeUpdateStrategy::DEFAULT);
    }
    if (value == 1) {
        GetMarqueeModel()->SetMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    }
}

void FfiOHOSAceFrameworkMarqueeOnStart(void (*callback)())
{
    auto onStart = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    GetMarqueeModel()->SetOnStart(std::move(onStart));
}

void FfiOHOSAceFrameworkMarqueeOnBounce(void (*callback)())
{
    auto onBounce = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    GetMarqueeModel()->SetOnBounce(std::move(onBounce));
}

void FfiOHOSAceFrameworkMarqueeOnFinish(void (*callback)())
{
    auto onFinish = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    GetMarqueeModel()->SetOnFinish(std::move(onFinish));
}
}
