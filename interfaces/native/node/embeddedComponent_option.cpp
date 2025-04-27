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

ArkUI_EmbeddedComponentItem* OH_ArkUI_EmbeddedComponentItem_Create()
{
    ArkUI_EmbeddedComponentItem* item =
        new ArkUI_EmbeddedComponentItem { nullptr, nullptr };
    return item;
}

void OH_ArkUI_EmbeddedComponentItem_Dispose(ArkUI_EmbeddedComponentItem* item)
{
    delete item;
}

void OH_ArkUI_EmbeddedComponentItem_SetOnError(
    ArkUI_EmbeddedComponentItem* item, void (*callback)(int32_t code, const char* name, const char* message))
{
    CHECK_NULL_VOID(item);
    CHECK_NULL_VOID(callback);
    item->onError = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_EmbeddedComponentItem_SetOnTerminated(
    ArkUI_EmbeddedComponentItem* item, void (*callback)(int32_t code, AbilityBase_Want* want))
{
    CHECK_NULL_VOID(item);
    CHECK_NULL_VOID(callback);
    item->onTerminated = reinterpret_cast<void*>(callback);
}

#ifdef __cplusplus
};
#endif
