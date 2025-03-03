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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SCROLLABLE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SCROLLABLE_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "ffi_remote_data.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseFlingSpeed(double speedLimit);
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseFadingEdge(bool enabled);
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseFadingEdgeOptions(
    bool enabled, double fadingEdge, int32_t fadingEdgeUnit);
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseClipMode(int32_t clip);
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseClipShape(int64_t shapeId);
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseOnWillScroll(
    double (*callback)(double scrollOffset, int32_t state, int32_t source));
CJ_EXPORT void FfiOHOSAceFrameworkScrollableBaseOnDidScroll(void (*callback)(double scrollOffset, int32_t state));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SCROLLABLE_FFI_H
