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

#include "cj_pixel_unit_convert_ffi.h"

#include "core/pipeline/pipeline_base.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
extern "C" {
double FfiOHOSAceFrameworkVp2Px(double value)
{
    auto container = Container::Current();
    if (!container) {
        return NAN;
    }
    double density = PipelineBase::GetCurrentDensity();
    return value * density;
}

double FfiOHOSAceFrameworkPx2Vp(double value)
{
    auto container = Container::Current();
    if (!container) {
        return NAN;
    }
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return 1.0f;
    }
    return value / density;
}


double GetFp2PxParam()
{
    double density = PipelineBase::GetCurrentDensity();
    auto container = Container::Current();
    if (!container) {
        return NAN;
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;

    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    return density * fontScale;
}

double FfiOHOSAceFrameworkFp2Px(double value)
{
    return value * GetFp2PxParam();
}

double FfiOHOSAceFrameworkPx2Fp(double value)
{
    double fp2PxGap = GetFp2PxParam();
    if (fp2PxGap > 0) {
        return value / fp2PxGap;
    } else {
        return value;
    }
}

double GetdesignWidthScale()
{
    auto container = Container::Current();
    if (!container) {
        return NAN;
    }
    auto window = container->GetWindow();
    if (!window) {
        return NAN;
    }
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    if (!frontend) {
        return NAN;
    }
    auto windowConfig = frontend->GetWindowConfig();

    windowConfig.UpdateDesignWidthScale(width);
    return windowConfig.GetDesignWidthScale(width);
}

double FfiOHOSAceFrameworkLpx2Px(double value)
{
    auto designWidthScale = GetdesignWidthScale();
    return value * designWidthScale;
}

double FfiOHOSAceFrameworkPx2Lpx(double value)
{
    auto designWidthScale = GetdesignWidthScale();
    if (designWidthScale > 0) {
        return value / designWidthScale;
    } else {
        return value;
    }
}
}
}