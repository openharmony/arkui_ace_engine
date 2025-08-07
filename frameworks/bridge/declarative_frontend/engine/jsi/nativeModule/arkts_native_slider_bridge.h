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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_SLIDER_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_SLIDER_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
using StepOptions = std::unordered_map<uint32_t, std::string>;
class SliderBridge {
public:
    static ArkUINativeModuleValue SetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetValidSlideRange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetValidSlideRange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSelectedBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelectedBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetInteractionMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetInteractionMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMinResponsiveDistance(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMinResponsiveDistance(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSliderOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPrefix(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPrefix(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSuffix(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSuffix(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static napi_value GetIteratorNext(const napi_env env, napi_value iterator, napi_value func, bool *done);
    static napi_value ParseStepOptionsMap(
        EcmaVM* vm, Framework::JSRef<Framework::JSVal> jsStepOptionsMap, StepOptions& stepOptionsMap);
    static int32_t ParseStepOptionItemKey(const napi_env env, napi_value item);
    static bool ParseStepOptionItemValue(EcmaVM* vm, const napi_env env, napi_value item, std::string& stepText);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_SLIDER_BRIDGE_H
