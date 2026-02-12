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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_qrcode_ffi.h"

#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

namespace {
constexpr double OPACITY_MAX = 1.0;
constexpr double OPACITY_MIN = 0.0;
}   // namespace

extern "C" {
void FfiOHOSAceFrameworkQRCodeCreate(const char* value)
{
    QRCodeModel::GetInstance()->Create(value);
}

void FfiOHOSAceFrameworkQRCodeSetQRCodeColor(uint32_t color)
{
    QRCodeModel::GetInstance()->SetQRCodeColor(Color(color));
}

void FfiOHOSAceFrameworkQRCodeSetBackgroundColor(uint32_t color)
{
    QRCodeModel::GetInstance()->SetQRBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkQRCodeSetContentOpacity(double value)
{
    if (value < OPACITY_MIN || value > OPACITY_MAX) {
        value = OPACITY_MAX;
    }
    QRCodeModel::GetInstance()->SetContentOpacity(value);
}
}
