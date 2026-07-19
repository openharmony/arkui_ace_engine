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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CANVAS_RUNTIME_BRIDGE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CANVAS_RUNTIME_BRIDGE_H

#include "base/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/canvas_runtime_bridge_api.h"

namespace OHOS::Ace::NG {

inline const ArkUICanvasRuntimeBridge* GetCanvasRuntimeBridgeFromModule()
{
    static const ArkUICanvasRuntimeBridge* bridge = nullptr;
    if (bridge == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Canvas");
        CHECK_NULL_RETURN(module, nullptr);
        bridge = reinterpret_cast<const ArkUICanvasRuntimeBridge*>(module->GetCustomModifier("canvasBridge"));
    }
    return bridge;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CANVAS_RUNTIME_BRIDGE_H