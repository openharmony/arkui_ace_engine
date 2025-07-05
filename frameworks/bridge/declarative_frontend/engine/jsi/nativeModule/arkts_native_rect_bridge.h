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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RECT_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RECT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class RectBridge {
public:
    static ArkUINativeModuleValue SetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRadiusWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRadiusHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static void SetRadiusWithArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
        std::vector<ArkUI_Float32>& radiusValues, std::vector<int32_t>& radiusUnits,
        std::vector<uint32_t>& radiusValidPairs, std::vector<RefPtr<ResourceObject>>& radiusXResObjArray,
        std::vector<RefPtr<ResourceObject>>& radiusYResObjArray);
    static void SetRadiusArraysInvalidValue(std::vector<ArkUI_Float32>& radiusValues,
        std::vector<int32_t>& radiusUnits,
        std::vector<uint32_t>& radiusValidPairs, int index);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RECT__BRIDGE_H
