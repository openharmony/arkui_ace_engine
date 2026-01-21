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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_CALENDAR_PICKER_DIALOG_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_CALENDAR_PICKER_DIALOG_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
namespace OHOS::Ace::NG {
class CalendarPickerDialogBridge : public CommonBridge {
public:
    static void RegisterCalendarPickerDialogAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static ArkUINativeModuleValue Show(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static void ParseCalendarPickerDialogEffectOption(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties);
    static void ParseEffectOption(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption);
    static void GetEffectOptionInactiveColor(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption);
    static void GetEffectOptionInactiveColorUpdate(
        const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption);
    static void GetEffectOptionColor(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption);
    static void ParseCalendarPickerDialogBlurStyleOption(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties);
    static void ParseBlurStyleOption(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, BlurStyleOption& styleOption);
    static void ParseInactiveColor(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, BlurStyleOption& styleOption);
    static void ParseBlurOption(EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsBlurOption, BlurOption& blurOption);
    static void CalendarPickerDialogShow(EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj);
    static bool ParseShadowProps(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue, Shadow& shadow,
        const bool configChangePerform = false, bool needResObj = false);
    static void ParseShadowOffsetXY(EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, Shadow& shadow);
    static void ParseShadowPropsUpdate(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, double& radius, Shadow& shadow);
    static bool GetShadowFromTheme(EcmaVM* vm, ShadowStyle shadowStyle, Shadow& shadow, const bool configChangePerform);
    static bool ParseJsShadowColorStrategy(
        EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue, ShadowColorStrategy& strategy);
    static std::map<std::string, NG::DialogCancelEvent> LifeCycleDialogEvent(
        panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param);
    static void DisappearDialogEvent(panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param,
        std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent);
    static void AppearDialogEvent(panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param,
        std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent);
    static std::map<std::string, NG::DialogGestureEvent> DialogCancelEvent(
        panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param);
    static std::map<std::string, NG::DialogEvent> ChangeDialogEvent(
        panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param);
    static void SetDialogHoverModeProperties(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties);
    static std::vector<ButtonInfo> ParseButtonStyles(panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param);
    static ButtonInfo ParseButtonStyle(EcmaVM* vm, const panda::Local<panda::ObjectRef>& pickerButtonParamObject);
    static void ParseFontOfButtonStyle(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& pickerButtonParamObject, ButtonInfo& buttonInfo);
    static std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(
        EcmaVM* vm, const panda::Local<panda::JSValueRef>& args);
    static std::optional<NG::BorderRadiusProperty> HandleDifferentRadius(
        EcmaVM* vm, const panda::Local<panda::JSValueRef>& args);
    static void ParseEffectBlurOption(EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption,
        EffectOption& effectOption);
    static void ParseBackgroundOfButtonStyle(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& pickerButtonParamObject, ButtonInfo& buttonInfo);
    static void ParseShadowColor(
        EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, Shadow& shadow, const bool configChangePerform,
        bool needResObj);
    static DialogProperties BuildDialogProperties(EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_CALENDAR_PICKER_DIALOG_BRIDGE_H
