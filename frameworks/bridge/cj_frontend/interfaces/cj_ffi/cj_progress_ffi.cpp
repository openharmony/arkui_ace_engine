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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_progress_ffi.h"

#include "core/components_ng/pattern/progress/progress_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<ProgressType> PROGRESS_TYPES = { ProgressType::LINEAR, ProgressType::RING, ProgressType::MOON,
    ProgressType::SCALE, ProgressType::CAPSULE };

const std::vector<NG::ProgressType> PROGRESS_TYPES_NG = { NG::ProgressType::LINEAR, NG::ProgressType::RING,
    NG::ProgressType::MOON, NG::ProgressType::SCALE, NG::ProgressType::CAPSULE };

} // namespace

extern "C" {
void FfiOHOSAceFrameworkProgressCreate(double value, double total, int32_t type)
{
    if (!Utils::CheckParamsValid(type, PROGRESS_TYPES.size())) {
        LOGE("invalid value for progress type");
        return;
    }

    double realValue = value;
    if (value > total) {
        realValue = total;
    } else if (value < 0) {
        realValue = 0;
    }

    ProgressModel::GetInstance()->Create(0.0, realValue, 0.0, total, PROGRESS_TYPES_NG[type]);
}

void FfiOHOSAceFrameworkProgressSetValue(double value)
{
    double realValue = value;
    if (value < 0) {
        realValue = 0;
    }

    ProgressModel::GetInstance()->SetValue(realValue);
}

void FfiOHOSAceFrameworkProgressSetColor(uint32_t color)
{
    ProgressModel::GetInstance()->SetColor(Color(color));
}

void FfiOHOSAceFrameworkProgressSetBackgroundColor(uint32_t color)
{
    ProgressModel::GetInstance()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkProgressSetStyle(
    double strokeWidth, int32_t strokeWidthUnit, int32_t scaleCount, double scaleWidth, int32_t scaleWidthUnit)
{
    Dimension strokeWidthValue(strokeWidth, static_cast<DimensionUnit>(strokeWidthUnit));
    Dimension scaleWidthValue(scaleWidth, static_cast<DimensionUnit>(scaleWidthUnit));

    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthValue);
    ProgressModel::GetInstance()->SetScaleCount(scaleCount);
    ProgressModel::GetInstance()->SetScaleWidth(scaleWidthValue);
}
}
