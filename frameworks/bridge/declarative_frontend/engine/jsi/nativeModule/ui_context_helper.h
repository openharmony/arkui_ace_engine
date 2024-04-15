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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVE_MODULE_UI_CONTEXT_HELPER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVE_MODULE_UI_CONTEXT_HELPER_H

#include <shared_mutex>
#include <unordered_map>

#include "ecmascript/napi/include/jsnapi.h"

namespace OHOS::Ace::NG {
class UIContextHelper final {
public:
    static void AddUIContext(panda::EcmaVM* vm, int32_t instanceId, panda::Local<panda::JSValueRef> uiContext);
    static void RemoveUIContext(int32_t instanceId);
    static panda::Local<panda::JSValueRef> GetUIContext(panda::EcmaVM* vm, int32_t instanceId);
    static bool HasUIContext(int32_t instanceId);
    static void RegisterRemoveUIContextFunc();

private:
    static std::unordered_map<int32_t, panda::Global<panda::JSValueRef>> uiContextMap_;
    static std::shared_mutex uiContextMapMutex_;
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVE_MODULE_UI_CONTEXT_HELPER_H
