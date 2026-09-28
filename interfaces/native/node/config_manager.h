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

#ifndef ARKUI_NATIVE_NODE_CONFIG_MANAGER_H
#define ARKUI_NATIVE_NODE_CONFIG_MANAGER_H

#include <cstdint>

#include "native_type.h"

namespace OHOS::Ace::NodeModel {

// Check type values, kept in sync with OH_ArkUI_NativeModule_RuntimeCheckType (public C API).
enum class CheckType : uint32_t {
    UI_THREAD = 0,
    NODE_DISPOSED = 1,
    // Number of check types and the exclusive upper bound for configuration indices;
    // COUNT is not a configurable check type. Keep values contiguous from zero.
    // Append new types immediately before COUNT without changing existing values,
    // align their values with the public C API, and add their default policy,
    // detection entry points and tests. The configuration array grows with COUNT.
    COUNT,
};

// Runtime check mode values, kept in sync with OH_ArkUI_NativeModule_RuntimeCheckMode (public C API).
enum class CheckMode : int32_t {
    DISABLED = 0,
    LOG = 1,
    CRASH = 2,
};

namespace ConfigManager {
// Saves the process-level user configuration. The UI thread check runs before
// parameter validation and is independent of the configured check modes.
bool SetRuntimeCheckMode(int32_t checkType, int32_t mode);

// Diagnose misuse without short-circuiting the caller in DISABLED or LOG mode.
void CheckUIThread(const char* publicApiName);
void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage);
} // namespace ConfigManager

} // namespace OHOS::Ace::NodeModel

#define CHECK_NODE_DISPOSED(nodePtr, errorMessage)                                                    \
    OHOS::Ace::NodeModel::ConfigManager::CheckNodeDisposed((nodePtr), __FUNCTION__, (errorMessage))

#define CHECK_UI_THREAD(apiName)                                                                      \
    OHOS::Ace::NodeModel::ConfigManager::CheckUIThread((apiName))

#endif // ARKUI_NATIVE_NODE_CONFIG_MANAGER_H
