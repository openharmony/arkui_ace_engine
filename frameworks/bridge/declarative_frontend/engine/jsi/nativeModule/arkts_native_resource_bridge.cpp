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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_resource_bridge.h"

#include <cstdint>

#include "jsnapi_expo.h"

#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/resource/resource_manager.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
namespace {
ColorMode MapJsColorModeToColorMode(int32_t jsColorMode)
{
    switch (jsColorMode) {
        case 1: // 1 is the ThemeColorMode.LIGHT
            return ColorMode::LIGHT;
        case 2: // 2 is the ThemeColorMode.DARK
            return ColorMode::DARK;
        default:
            return ColorMode::COLOR_MODE_UNDEFINED;
    }
    return ColorMode::COLOR_MODE_UNDEFINED;
}

#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
void UpdateColorModeForThemeConstants(const ColorMode& colorMode)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto resConfig = container->GetResourceConfiguration();
    resConfig.SetColorMode(colorMode);

    auto themeManager = PipelineBase::CurrentThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_VOID(themeConstants);
    themeConstants->UpdateConfig(resConfig);
}
#endif
} // namespace

ArkUINativeModuleValue ResourceBridge::UpdateColorMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ColorMode colorModeValue = ColorMode::COLOR_MODE_UNDEFINED;
    if (firstArg->IsNumber()) {
        int32_t firstArgValue = firstArg->Int32Value(vm);
        colorModeValue = MapJsColorModeToColorMode(firstArgValue);
    }
    if (colorModeValue != ColorMode::COLOR_MODE_UNDEFINED) {
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        UpdateColorModeForThemeConstants(colorModeValue);
#else
        ResourceManager::GetInstance().UpdateColorMode(colorModeValue);
#endif
        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
        pipelineContext->SetLocalColorMode(colorModeValue);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResourceBridge::Restore(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);

    auto colorModeValue = pipelineContext->GetColorMode();
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    UpdateColorModeForThemeConstants(colorModeValue);
#else
    ResourceManager::GetInstance().UpdateColorMode(colorModeValue);
#endif
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResourceBridge::GetColorValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, firstArg, color)) {
        uint32_t colorValue = color.GetValue();
        return panda::NumberRef::New(vm, colorValue);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResourceBridge::GetStringValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    std::string result;
    if (ArkTSUtils::ParseJsString(vm, firstArg, result)) {
        return panda::StringRef::NewFromUtf8(vm, result.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResourceBridge::GetNumberValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    double result;
    if (ArkTSUtils::ParseJsDouble(vm, firstArg, result)) {
        return panda::NumberRef::New(vm, result);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResourceBridge::ClearCache(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ResourceManager::GetInstance().Reset();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
