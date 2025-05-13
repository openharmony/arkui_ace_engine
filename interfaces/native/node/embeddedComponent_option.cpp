/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "embeddedComponent_option.h"

#include "node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_EmbeddedComponentOption* OH_ArkUI_EmbeddedComponentOption_Create()
{
    ArkUI_EmbeddedComponentOption* option =
        new ArkUI_EmbeddedComponentOption { nullptr, nullptr };
    return option;
}

void OH_ArkUI_EmbeddedComponentOption_Dispose(ArkUI_EmbeddedComponentOption* option)
{
    delete option;
}

void OH_ArkUI_EmbeddedComponentOption_SetOnError(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, const char* name, const char* message))
{
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(callback);
    option->onError = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_EmbeddedComponentOption_SetOnTerminated(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, AbilityBase_Want* want))
{
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(callback);
    option->onTerminated = reinterpret_cast<void*>(callback);
}

#ifdef __cplusplus
};
#endif
