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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_textarea_ffi.h"

#include "base/utils/utf_helper.h"


using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {

NGNativeTextAreaController::NGNativeTextAreaController() : FFIData()
{
    LOGI("Native TextAreaController constructed: %{public}" PRId64, GetID());
}

void NGNativeTextAreaController::CaretPosition(int32_t caretPosition)
{
    if (controller_) {
        controller_->CaretPosition(caretPosition);
    }
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTextAreaCreate(const char* placeholder, const char* text, int64_t controllerId)
{
    auto controller = FFIData::GetData<NGNativeTextAreaController>(controllerId);
    if (controller == nullptr) {
        LOGE("FfiTextArea invalid controllerId");
        return;
    }
    std::string placeholderStr8(placeholder);
    std::string textStr8(text);
    auto nativeController = TextFieldModel::GetInstance()->CreateTextArea(UtfUtils::Str8ToStr16(placeholderStr8),
        UtfUtils::Str8ToStr16(textStr8));
    controller->SetController(nativeController);
}

int64_t FfiOHOSAceFrameworkTextAreaControllerCtor()
{
    auto controller = FFIData::Create<NGNativeTextAreaController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkTextAreaControllerCaretPosition(int64_t selfID, int32_t value)
{
    int32_t position = value < 0 ? 0 : value;
    auto self = FFIData::GetData<NGNativeTextAreaController>(selfID);
    if (self != nullptr) {
        self->CaretPosition(position);
    } else {
        LOGE("FfiTextArea: invalid textAreaControllerId");
    }
}
}
