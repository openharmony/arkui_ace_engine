/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef ARKUI_NATIVE_UI_JSON_WRAPPER_H
#define ARKUI_NATIVE_UI_JSON_WRAPPER_H

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OH_ArkUI_NativeModule_UIJsonWrapper OH_ArkUI_NativeModule_UIJsonWrapper;

/** Copies size UTF-8 bytes. The result is immutable and independently owned. */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapper_Create(const char* data, uint32_t size,
    uint32_t schemaVersion, OH_ArkUI_NativeModule_UIJsonWrapper** outOwned);
/** Borrowed, NUL-terminated bytes; NULL wrapper returns NULL. */
const char* OH_ArkUI_NativeModule_UIJsonWrapper_GetData(const OH_ArkUI_NativeModule_UIJsonWrapper* wrapper);
/** Byte count excluding the terminator. wrapper must be non-NULL. */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapper_GetSize(const OH_ArkUI_NativeModule_UIJsonWrapper* wrapper);
/** NULL wrapper returns zero. */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapper_GetSchemaVersion(const OH_ArkUI_NativeModule_UIJsonWrapper* wrapper);
/** NULL is a no-op. Must not race with readers or another destroy. */
void OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(OH_ArkUI_NativeModule_UIJsonWrapper* wrapper);

#ifdef __cplusplus
}
#endif
#endif
