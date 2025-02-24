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

#ifndef OHOS_ACE_FRAMEWORK_CJ_LIST_ITEM_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_LIST_ITEM_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkListItemCreate();
CJ_EXPORT void FfiOHOSAceFrameworkListItemCreateWithOptions(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetBorderRaduis(double raduis, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetSticky(int32_t sticky);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetEditable(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetSelectable(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetSelected(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetOnSelect(void (*callback)(bool flag));
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetSwipeAction(
    void (*startBuilder)(), void (*endBuilder)(), int32_t edgeEffect);
CJ_EXPORT void FfiOHOSAceFrameworkListItemSetSwipeAction2(
    void (*startBuilder)(), void (*endBuilder)(), int32_t edgeEffect, void (*onOffsetChange)(int32_t offset));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_FLEX_FFI_H
