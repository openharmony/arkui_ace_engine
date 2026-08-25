/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
namespace OHOS::Ace::Framework {
NG::KeyboardAppearanceConfig JSTextField::ParseKeyboardAppearanceConfig(const JSRef<JSObject>& obj)
{
    NG::KeyboardAppearanceConfig config;
    auto gradientModeJsVal = obj->GetProperty("gradientMode");
    if (gradientModeJsVal->IsNull() || gradientModeJsVal->IsUndefined() || !gradientModeJsVal->IsNumber()) {
        config.gradientMode = NG::KeyboardGradientMode::NONE;
    } else {
        int32_t value = gradientModeJsVal->ToNumber<int32_t>();
        if (value <= static_cast<int32_t>(NG::KeyboardGradientMode::BEGIN) ||
            value > static_cast<int32_t>(NG::KeyboardGradientMode::END)) {
            config.gradientMode = NG::KeyboardGradientMode::NONE;
        } else {
            config.gradientMode = static_cast<NG::KeyboardGradientMode>(value);
        }
    }
    auto fluidLightModeJsVal = obj->GetProperty("fluidLightMode");
    if (fluidLightModeJsVal->IsNull() || fluidLightModeJsVal->IsUndefined() || !fluidLightModeJsVal->IsNumber()) {
        config.fluidLightMode = NG::KeyboardFluidLightMode::NONE;
    } else {
        int32_t value = fluidLightModeJsVal->ToNumber<int32_t>();
        if (value <= static_cast<int32_t>(NG::KeyboardFluidLightMode::BEGIN) ||
            value > static_cast<int32_t>(NG::KeyboardFluidLightMode::END)) {
            config.fluidLightMode = NG::KeyboardFluidLightMode::NONE;
        } else {
            config.fluidLightMode = static_cast<NG::KeyboardFluidLightMode>(value);
        }
    }
    return config;
}

void JSTextField::SetKeyboardAppearanceConfig(const JSCallbackInfo& info)
{
    EcmaVM* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsTargetNode = info[0];
    auto localHandle = jsTargetNode->GetLocalHandle();
    if (!localHandle->IsNativePointer(vm)) {
        return;
    }
    auto* targetNodePtr = localHandle->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(targetNodePtr);
    CHECK_NULL_VOID(frameNode);
    if (!info[1]->IsObject()) {
        return;
    }
    NG::KeyboardAppearanceConfig config = ParseKeyboardAppearanceConfig(JSRef<JSObject>::Cast(info[1]));
    auto* customModifier = NG::NodeModifier::GetTextInputCustomModifier();
    CHECK_NULL_VOID(customModifier);
    customModifier->setKeyboardAppearanceConfig(frameNode, config);
}

void JSTextField::SetSearchKeyboardAppearanceConfig(const JSCallbackInfo& info)
{
    EcmaVM* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsTargetNode = info[0];
    auto localHandle = jsTargetNode->GetLocalHandle();
    if (!localHandle->IsNativePointer(vm)) {
        return;
    }
    auto* targetNodePtr = localHandle->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(targetNodePtr);
    CHECK_NULL_VOID(frameNode);
    if (!info[1]->IsObject()) {
        return;
    }
    NG::KeyboardAppearanceConfig config = JSTextField::ParseKeyboardAppearanceConfig(JSRef<JSObject>::Cast(info[1]));
    auto customModifier = NG::NodeModifier::GetSearchCustomModifier();
    customModifier->setKeyboardAppearanceConfig(frameNode, config);
}
} // namespace OHOS::Ace::Framework
