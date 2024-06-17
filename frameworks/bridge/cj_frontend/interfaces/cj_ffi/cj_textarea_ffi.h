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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXTAREA_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXTAREA_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/text_field/text_field_controller.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NGNativeTextAreaController : public OHOS::FFI::FFIData {
    DECL_TYPE(NGNativeTextAreaController, OHOS::FFI::FFIData)
public:
    NGNativeTextAreaController();

    void CaretPosition(int32_t caretPosition);
    void SetController(const RefPtr<TextFieldControllerBase>& controller)
    {
        controller_ = controller;
    }

private:
    RefPtr<TextFieldControllerBase> controller_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkTextAreaCreate(const char* placeholder, const char* text, int64_t controllerID);
CJ_EXPORT int64_t FfiOHOSAceFrameworkTextAreaControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkTextAreaControllerCaretPosition(int64_t selfID, int32_t value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXTAREA_FFI_H
