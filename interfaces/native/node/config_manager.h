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

namespace OHOS::Ace::NodeModel::ConfigManager {
// Saves the process-level runtime check mode of one runtime check type.
// checkType/mode are raw integers because the C ABI may pass any value; invalid input returns false.
// Must be called on the UI thread: a non-UI-thread call terminates the process before validation.
bool SetRuntimeCheckMode(int32_t checkType, int32_t mode);

// NODE_DISPOSED detection point: diagnoses a disposed handle according to the effective mode.
// errorMessage carries the call-site reason text (parameter role) for the diagnosis output.
// A crash from the debug build default also explains how to disable the check through the public API.
// It never short-circuits the caller: DISABLED returns silently, LOG prints the diagnosis and
// returns, CRASH prints the diagnosis and terminates the process.
void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage);
} // namespace OHOS::Ace::NodeModel::ConfigManager

// One-line diagnosis guard for the public C API entries. __FUNCTION__ is captured at the call
// site so the diagnosis records the entry name; the guard never short-circuits.
#define CHECK_NODE_DISPOSED(nodePtr, errorMessage)                                                    \
    OHOS::Ace::NodeModel::ConfigManager::CheckNodeDisposed((nodePtr), __FUNCTION__, (errorMessage))

#endif // ARKUI_NATIVE_NODE_CONFIG_MANAGER_H
