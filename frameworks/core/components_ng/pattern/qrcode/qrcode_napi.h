/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_NAPI_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_NAPI_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace {
napi_value JsCreate(napi_env env, napi_callback_info info);
napi_value JsColor(napi_env env, napi_callback_info info);
napi_value JsBackgroundColor(napi_env env, napi_callback_info info);
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_QRCODE_NAPI_H