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

#ifndef OHOS_ACE_FRAMEWORK_CJ_WEB_H
#define OHOS_ACE_FRAMEWORK_CJ_WEB_H
#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "core/components/web/web_component.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_container_base_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"

struct FfiWebEvent;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkWebHandleCancel(void* result);
CJ_EXPORT void FfiOHOSAceFrameworkWebHandleConfirm(void* result);
CJ_EXPORT void FfiOHOSAceFrameworkWebHandlePromptConfirm(void* result, const char* message);
CJ_EXPORT void FfiOHOSAceFrameworkWebReleaseResult(void* result);

CJ_EXPORT void FfiOHOSAceFrameworkWebCreate(const char* src, int64_t controllerId, int32_t type, bool mode);
CJ_EXPORT void FfiOHOSAceFrameworkWebFileAccessEnabled(bool isFileAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebDomStorageAccessEnabled(bool isDomStorageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebImageAccessEnabled(bool isImageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebOnlineImageAccessEnabled(bool isImageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebMixedMode(int32_t mixedModeNum);
CJ_EXPORT void FfiOHOSAceFrameworkWebZoomAccessEnabled(bool isZoomAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebGeolocationAccessEnabled(bool isGeolocationAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebUserAgent(const std::string& userAgent);

CJ_EXPORT void FfiOHOSAceFrameworkWebOnAlert(bool (*callback)(FfiWebEvent event));
CJ_EXPORT void FfiOHOSAceFrameworkWebOnPageStart(void (*callback)(const char* url));
CJ_EXPORT void FfiOHOSAceFrameworkWebOnPageFinish(void (*callback)(const char* url));
CJ_EXPORT void FfiOHOSAceFrameworkWebJavaScriptProxy(
    VectorInt64Handle funcList, const char* name, VectorStringHandle methodList, int64_t controllerId);
};

#endif // OHOS_ACE_FRAMEWORK_CJ_WEB_H
