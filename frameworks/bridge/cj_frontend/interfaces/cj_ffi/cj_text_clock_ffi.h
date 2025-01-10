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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXT_CLOCK_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXT_CLOCK_FFI_H

#include <cinttypes>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativeTextClockController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeTextClockController, OHOS::FFI::FFIData)
public:
    NativeTextClockController();

    void Start();
    void Stop();
    void SetController(const RefPtr<TextClockController>& controller)
    {
        controller_ = controller;
    }

private:
    RefPtr<TextClockController> controller_;
};
} // namespace OHOS::Ace::Framework

using VectorDoubleHandle = void*;
using VectorStringPtr = void*;
using VectorNativeTextShadow = void*;

extern "C" {
struct NativeTextShadow {
    double radius;
    double offsetX;
    double offsetY;
    uint32_t color;
    bool isFilled;
    int32_t type;
};
CJ_EXPORT VectorNativeTextShadow FFICJCreateVectorNativeTextShadow(int64_t size);
CJ_EXPORT void FFICJVectorNativeTextShadowSetElement(
    VectorNativeTextShadow vec, int64_t index, NativeTextShadow textShadow);
CJ_EXPORT void FFICJVectorNativeTextShadowDelete(VectorNativeTextShadow vec);

CJ_EXPORT void FfiOHOSAceFrameworkTextClockCreateDefault(int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockCreate(float timeZoneOffset, int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockCreateSimple(int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFormat(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockOnChange(void (*callback)(int64_t timeStamp));
CJ_EXPORT void FfiOHOSAceFrameworkTextClockTextColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFontSize(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFontStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockTextShadow(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockFontFeature(const char* fontFeature);
CJ_EXPORT int64_t FfiOHOSAceFrameworkTextClockControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTextClockControllerStart(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockControllerStop(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkTextClockDateTimeOptions(const char* hourOptions);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXT_CLOCK_FFI_H
