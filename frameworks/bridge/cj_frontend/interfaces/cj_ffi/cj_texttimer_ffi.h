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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXT_TIMER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXT_TIMER_FFI_H

#include <cinttypes>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/texttimer/text_timer_model.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeTextTimerController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeTextTimerController, OHOS::FFI::FFIData)
public:
    NativeTextTimerController();

    void Start();
    void Pause();
    void Reset();
    void SetController(const RefPtr<TextTimerController>& controller)
    {
        controller_ = controller;
    }

private:
    RefPtr<TextTimerController> controller_;
};
} // namespace OHOS::Ace::Framework

using VectorNativeTextTimerShadow = void*;
using VectorStringPtr = void*;

extern "C" {
struct NativeTextTimerShadow {
    double radius;
    double offsetX;
    double offsetY;
    uint32_t color;
    bool isFilled;
    int32_t type;
};
CJ_EXPORT VectorNativeTextTimerShadow FfiTextTimerCreateVectorNativeTextShadow(int64_t size);
CJ_EXPORT void FfiTextTimerVectorNativeTextShadowSetElement(
    VectorNativeTextTimerShadow vec, int64_t index, NativeTextTimerShadow textShadow);
CJ_EXPORT void FfiTextTimerVectorNativeTextShadowDelete(VectorNativeTextTimerShadow vec);

CJ_EXPORT void FfiOHOSAceFrameworkTextTimerCreate(bool isCountDown, int64_t count, int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFormat(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFontColor(uint32_t textColor);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFontStyle(int32_t fontStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetTextShadow(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerSetOnTimer(void (*callback)(int64_t, int64_t elapsedTime));
CJ_EXPORT int64_t FfiOHOSAceFrameworkTextTimerControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerControllerStart(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerControllerPause(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkTextTimerControllerReset(int64_t selfID);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXT_TIMER_FFI_H
