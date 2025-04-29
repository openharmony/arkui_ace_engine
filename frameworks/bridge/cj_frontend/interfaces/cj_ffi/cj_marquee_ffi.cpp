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
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkMarqueeCreate(bool start, const char* src, double step, int32_t loop, bool fromStart)
{
    MarqueeModel::GetInstance()->Create();
    MarqueeModel::GetInstance()->SetValue(src);
    MarqueeModel::GetInstance()->SetPlayerStatus(start);
    MarqueeModel::GetInstance()->SetScrollAmount(step);
    MarqueeModel::GetInstance()->SetLoop(loop);
    if (fromStart) {
        MarqueeModel::GetInstance()->SetDirection(MarqueeDirection::LEFT);
    } else {
        MarqueeModel::GetInstance()->SetDirection(MarqueeDirection::RIGHT);
    }
}

void FfiOHOSAceFrameworkMarqueeSetAllowScale(bool value)
{
    MarqueeModel::GetInstance()->SetAllowScale(value);
}

void FfiOHOSAceFrameworkMarqueeSetFontColor(uint32_t color)
{
    MarqueeModel::GetInstance()->SetTextColor(Color(color));
}

void FfiOHOSAceFrameworkMarqueeSetFontSize(double value, int32_t unit)
{
    Dimension fontSize(value, static_cast<DimensionUnit>(unit));
    MarqueeModel::GetInstance()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkMarqueeSetFontWeight(const char* fontWeight)
{
    MarqueeModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkMarqueeSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    MarqueeModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkMarqueeSetMarqueeUpdateStrategy(int32_t value)
{
    if (value == 0) {
        MarqueeModel::GetInstance()->SetMarqueeUpdateStrategy(MarqueeUpdateStrategy::DEFAULT);
    }
    if (value == 1) {
        MarqueeModel::GetInstance()->SetMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    }
}

void FfiOHOSAceFrameworkMarqueeOnStart(void (*callback)())
{
    auto onStart = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    MarqueeModel::GetInstance()->SetOnStart(std::move(onStart));
}

void FfiOHOSAceFrameworkMarqueeOnBounce(void (*callback)())
{
    auto onBounce = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    MarqueeModel::GetInstance()->SetOnBounce(std::move(onBounce));
}

void FfiOHOSAceFrameworkMarqueeOnFinish(void (*callback)())
{
    auto onFinish = [lambda = CJLambda::Create(callback)]() {
        lambda();
    };
    MarqueeModel::GetInstance()->SetOnFinish(std::move(onFinish));
}
}
