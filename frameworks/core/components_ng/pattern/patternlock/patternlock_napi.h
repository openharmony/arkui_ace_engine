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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_NAPI_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_NAPI_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace {

// Type tag for napi_wrap_s/napi_unwrap_s type safety
constexpr napi_type_tag PATTERN_LOCK_CONTROLLER_TYPE_TAG = {
    .lower = 0x9E4F7A3C2B8D1E6F,
    .upper = 0x5A7C3D9E2B6F8A1C,
};

napi_value Create(napi_env env, napi_callback_info info);
napi_value SideLength(napi_env env, napi_callback_info info);
napi_value CircleRadius(napi_env env, napi_callback_info info);
napi_value PathStrokeWidth(napi_env env, napi_callback_info info);
napi_value ActiveColor(napi_env env, napi_callback_info info);
napi_value SelectedColor(napi_env env, napi_callback_info info);
napi_value PathColor(napi_env env, napi_callback_info info);
napi_value RegularColor(napi_env env, napi_callback_info info);
napi_value AutoReset(napi_env env, napi_callback_info info);
napi_value OnPatternComplete(napi_env env, napi_callback_info info);
napi_value Reset(napi_env env, napi_callback_info info);
napi_value PatternLockControllerConstructor(napi_env env, napi_callback_info info);
static napi_value Init(napi_env env, napi_value exports);
static napi_value InitController(napi_env env, napi_value exports);
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_NAPI_H