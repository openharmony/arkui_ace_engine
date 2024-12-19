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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_textinput_ffi.h"

#include "base/utils/utf_helper.h"


using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {

NGNativeTextInputController::NGNativeTextInputController() : FFIData()
{
    LOGI("Native TextInputController constructed: %{public}" PRId64, GetID());
}

void NGNativeTextInputController::CaretPosition(int32_t caretPosition)
{
    if (controller_) {
        controller_->CaretPosition(caretPosition);
    }
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTextInputCreate(const char* placeholder, const char* text, int64_t controllerId)
{
    auto controller = FFIData::GetData<NGNativeTextInputController>(controllerId);
    if (controller == nullptr) {
        LOGE("FfiTextInput invalid controllerId");
        return;
    }
    std::string placeHolderStr8(placeholder);
    std::string textStr8(text);
    auto nativeController = TextFieldModel::GetInstance()->CreateTextInput(UtfUtils::Str8ToStr16(placeHolderStr8),
        UtfUtils::Str8ToStr16(textStr8));
    controller->SetController(nativeController);
}

int64_t FfiOHOSAceFrameworkTextInputControllerCtor()
{
    auto controller = FFIData::Create<NGNativeTextInputController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkTextInputControllerCaretPosition(int64_t selfID, int32_t value)
{
    int32_t position = value < 0 ? 0 : value;
    auto self = FFIData::GetData<NGNativeTextInputController>(selfID);
    if (self != nullptr) {
        self->CaretPosition(position);
    } else {
        LOGE("FfiTextInput: invalid textInputControllerId");
    }
}
}
