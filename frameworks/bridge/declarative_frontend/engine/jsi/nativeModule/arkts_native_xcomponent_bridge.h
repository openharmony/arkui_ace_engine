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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
class ArkUI_XComponent_Params;
class XComponentBridge {
public:
    static void ParseParams(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Params& params);
    static void SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnCreated(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnChanged(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnDestroyed(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static ArkUINativeModuleValue SetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnLoad(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnLoad(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnDestroy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDestroy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableSecure(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableSecure(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHdrBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHdrBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableTransparentLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableTransparentLayer(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static XComponentType ConvertToXComponentType(const std::string& type);
    static void SetControllerCallback(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static void HandleImageAIOptions(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static void HandleDetachCallback(ArkUIRuntimeCallInfo *runtimeCallInfo);
};
}

#endif  // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H
