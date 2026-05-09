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

#ifndef OHOS_ACE_FRAMEWORK_CJ_LAYOUT_INSPECTOR_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_LAYOUT_INSPECTOR_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"

extern "C" {
typedef struct FfiProfilerStateChangeRecord {
    int32_t viewId;
    const char* componentNameUtf8;
    const char* decoratorUtf8;
    const char* propertyNameUtf8;
    const char* valueUtf8;
    int64_t inRenderingElementId;
    int32_t propertyId;
    const char* dependentElmtIdsCsvUtf8;
    const char* syncPeersJsonUtf8;
} FfiProfilerStateChangeRecord;


CJ_EXPORT void FfiOHOSAceFrameworkRegisterProfilerStatusNotify(void (*notifyProfilerStatus)(bool enabled));
CJ_EXPORT void FfiOHOSAceFrameworkLayoutInspectorPushStateChangeRecord(const FfiProfilerStateChangeRecord* record);
CJ_EXPORT ExternalString FfiOHOSAceProfilerGetViewElementName(int32_t viewElementId);
}

namespace OHOS::Ace::Framework {
void CjProfilerRegisterViewElementName(int32_t viewElementId, const char* utf8);
void CjProfilerUnregisterViewElementName(int32_t viewElementId);
std::string CjProfilerGetViewElementName(int32_t viewElementId);
void CjProfilerRegisterViewToElementId(int64_t nativeViewId, int32_t elementId);
void CjProfilerUnregisterViewToElementId(int64_t nativeViewId);
void CjAppendProfilerStateRecordFromFfi(const FfiProfilerStateChangeRecord* record);
void CjSendStateInfoToProfiler(const std::string& stateInfoJson);
void CjSendMinimalStateInfoToProfiler(int32_t viewId, const std::string& componentName);
void CjNotifyProfilerStatusToCangjie(bool enabled);
void EnsureCangjieProfilerStatusHookedForHybridAndEmbedded();

}

#endif // OHOS_ACE_FRAMEWORK_CJ_LAYOUT_INSPECTOR_FFI_H
