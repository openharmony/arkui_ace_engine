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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PROGRESSMASK_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PROGRESSMASK_FFI_H

#include <cstdint>
#include <string>

#include "ffi_remote_data.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeProgressMask : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeProgressMask, OHOS::FFI::FFIData)
public:
    explicit NativeProgressMask(float value, float total, uint32_t color);

    void UpdateProgress(float number);

    void UpdateColor(uint32_t color);

    void EnableBreathingAnimation(bool value);

    const RefPtr<NG::ProgressMaskProperty> GetProgressMask() const
    {
        return progress_mask_;
    }

    void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>& progressMask)
    {
        progress_mask_ = progressMask;
    }

    void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>&& progressMask)
    {
        progress_mask_ = std::move(progressMask);
    }

private:
    RefPtr<NG::ProgressMaskProperty> progress_mask_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
CJ_EXPORT int64_t FfiOHOSAceFrameworkProgressMaskCreate(float value, float total, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkProgressMaskUpdateProgress(int64_t selfId, float value);
CJ_EXPORT void FfiOHOSAceFrameworkProgressMaskUpdateColor(int64_t selfId, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkProgressMaskEnableBreathingAnimation(int64_t selfId, bool value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PROGRESSMASK_FFI_H