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

#include "cj_progressmask_ffi.h"

using namespace OHOS::FFI;

namespace OHOS::Ace::Framework {

NativeProgressMask::NativeProgressMask(float value, float total, uint32_t color) : FFIData()
{
    LOGI("Native NativeProgressMask constructed");
}

void NativeProgressMask::UpdateProgress(float number)
{
    if (progress_mask_) {
        progress_mask_->SetValue(number);
    }
}

void NativeProgressMask::UpdateColor(uint32_t color)
{
    if (progress_mask_) {
        progress_mask_->SetColor(Color(color));
    }
}

void NativeProgressMask::EnableBreathingAnimation(bool value)
{
    if (progress_mask_) {
        progress_mask_->SetEnableBreathe(value);
    }
}
extern "C" {
int64_t FfiOHOSAceFrameworkProgressMaskCreate(float value, float total, uint32_t color)
{
    auto context = FFIData::Create<NativeProgressMask>(value, total, color);
    if (context == nullptr) {
        return FFI_ERROR_CODE;
    }

    if (value < 0.0f) {
        value = 0.0f;
    }
    if (total < 0.0f) {
        total = 0.0f;
    }

    auto progressMask = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMask->SetValue(value);
    progressMask->SetMaxValue(total);
    progressMask->SetColor(Color(color));

    context->SetProgressMask(std::move(progressMask));
    return context->GetID();
}

void FfiOHOSAceFrameworkProgressMaskUpdateProgress(int64_t selfId, float value)
{
    auto context = FFIData::GetData<NativeProgressMask>(selfId);
    if (context == nullptr) {
        LOGE("progressmask update progress error, Cannot get NativeProgressMask by id: %{public}" PRId64, selfId);
        return;
    }
    context->UpdateProgress(value);
}
void FfiOHOSAceFrameworkProgressMaskUpdateColor(int64_t selfId, uint32_t color)
{
    auto context = FFIData::GetData<NativeProgressMask>(selfId);
    if (context == nullptr) {
        LOGE("progressmask update color error, Cannot get NativeProgressMask by id: %{public}" PRId64, selfId);
        return;
    }
    context->UpdateColor(color);
}
void FfiOHOSAceFrameworkProgressMaskEnableBreathingAnimation(int64_t selfId, bool value)
{
    auto context = FFIData::GetData<NativeProgressMask>(selfId);
    if (context == nullptr) {
        LOGE("progressmask enable breathing error, Cannot get NativeProgressMask by id: %{public}" PRId64, selfId);
        return;
    }
    context->EnableBreathingAnimation(value);
}
};
} // namespace OHOS::Ace::Framework