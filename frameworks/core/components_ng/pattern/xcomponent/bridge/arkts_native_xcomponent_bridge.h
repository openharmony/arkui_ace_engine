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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"

namespace OHOS::Ace::NG {
class ArkUI_XComponent_Params;
struct XComponentOptions {
    std::optional<std::string> id = std::nullopt;
    XComponentType type = XComponentType::SURFACE;
    std::optional<std::string> libraryName = std::nullopt;
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    std::optional<std::uint64_t> screenId = std::nullopt;
};
class XComponentBridge {
public:
    static void RegisterXComponentAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm);
    static ArkUINativeModuleValue Create(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static void ParseParams(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Params& params);
    static void SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnCreated(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnChanged(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static void SetControllerOnDestroyed(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode);
    static ArkUINativeModuleValue SetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImageSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackdropBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSaturate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContrast(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetInvert(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSepia(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHueRotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetColorBlend(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSphericalEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLightUpEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPixelStretchEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
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
    static ArkUINativeModuleValue SetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue IsCommonEventAvailable(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static XComponentType ConvertToXComponentType(const std::string& type);
    static void ExtractInfoToXComponentOptions(XComponentOptions& options, panda::Local<panda::ObjectRef> controllerObj,
        panda::Local<panda::ObjectRef>& paramObject, ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void HandleImageAIOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void HandleDetachCallback(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_ARKTS_NATIVE_XCOMPONENT_BRIDGE_H
