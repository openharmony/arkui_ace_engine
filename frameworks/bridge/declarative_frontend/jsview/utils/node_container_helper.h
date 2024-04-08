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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_UTILS_NODE_CONTAINER_HELPER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_UTILS_NODE_CONTAINER_HELPER_H

#include <shared_mutex>
#include <unordered_map>

#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {
class NodeContainerHelper final {
public:
    static void AddUIContext(int32_t instanceId, JSRef<JSVal> uiContext);
    static void RemoveUIContext(int32_t instanceId);
    static JSRef<JSVal> GetUIContext(int32_t instanceId);
    static bool HasUIContext(int32_t instanceId);

private:
    static std::unordered_map<int32_t, JSRef<JSVal>> uiContextMap_;
    static std::shared_mutex uiContextMapMutex_;
};
} // namespace OHOS::Ace::Framework

#endif