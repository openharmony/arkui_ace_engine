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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_BUTTON_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_BUTTON_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class ButtonBridge {
public:
    static ArkUINativeModuleValue SetCreateWithLabel(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLabel(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLabel(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonRole(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonRole(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetButtonControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetButtonControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    
private:
    static void PushValuesVector(const std::optional<int32_t>& value, std::vector<int32_t>& valuesVector);
    static void PushDimensionVector(const std::optional<Dimension>& valueDimen, std::vector<ArkUI_Float32>& dimensions);
    static void PushButtonDimension(
        ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizesVector,
        int32_t argIndex);
    static void PutButtonDimensionParameters(
        ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizes);
    static void PutButtonStringParameters(
        ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<const char*>& stringParameters);
    static void PutButtonValuesParameters(
        ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<int32_t>& valuesVector);
    static RefPtr<ResourceObject> ParseFontSizeResObj(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
        int32_t argIndex);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_BUTTON__BRIDGE_H
