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

#ifndef OHOS_ACE_FRAMEWORK_FFI_CJ_LAZY_FOREACH_H
#define OHOS_ACE_FRAMEWORK_FFI_CJ_LAZY_FOREACH_H

#include "cj_macro.h"

#include "base/memory/referenced.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkLazyForEachCreate(int64_t viewID, int64_t parentViewID, int64_t lazyForEachFuncsID);
CJ_EXPORT void FfiOHOSAceFrameworkLazyForEachPop();
}

#endif
