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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_blank_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_button_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkbox_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkboxgroup_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_counter_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_divider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_col_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_row_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_router_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigator_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_area_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_toggle_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_radio_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rating_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_select_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_slider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_textpicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_timepicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rich_editor_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_video_bridge.h"


namespace OHOS::Ace::NG {
ArkUINativeModuleValue ArkUINativeModule::GetFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUIInternalNodeAPI()->GetFrameNodeById(nodeId);
    return panda::NativePointerRef::New(vm, nodePtr);
}

ArkUINativeModuleValue ArkUINativeModule::GetArkUINativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto object = panda::ObjectRef::New(vm);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetFrameNodeById));

    auto common = panda::ObjectRef::New(vm);
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTransform));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTransform));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetShadow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetShadow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHitTestBehavior"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHitTestBehavior));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHitTestBehavior"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHitTestBehavior));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setZIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetZIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetZIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetZIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOpacity));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "ResetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOpacity));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAlign));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAlign));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackdropBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackdropBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackdropBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackdropBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHueRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHueRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHueRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHueRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInvert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetInvert));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInvert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetInvert));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSepia"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSepia));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSepia"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSepia));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSaturate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSaturate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSaturate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSaturate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColorBlend"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetColorBlend));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColorBlend"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetColorBlend));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGrayscale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGrayscale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContrast"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetContrast));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContrast"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetContrast));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLinearGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLinearGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLinearGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLinearGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSweepGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSweepGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSweepGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSweepGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadialGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRadialGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadialGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRadialGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLinearGradientBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLinearGradientBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLinearGradientBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLinearGradientBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorder));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorder));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImagePosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImagePosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImagePosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImagePosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImageSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImageSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImageSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImageSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTranslate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTranslate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTranslate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTranslate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetScale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetScale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGeometryTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGeometryTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGeometryTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGeometryTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPixelStretchEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPixelStretchEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPixelStretchEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPixelStretchEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLightUpEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLightUpEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLightUpEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLightUpEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSphericalEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSphericalEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSphericalEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSphericalEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRenderGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRenderGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRenderFit));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRenderFit));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetUseEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetUseEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMotionPath"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMotionPath));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMotionPath"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMotionPath));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGroupDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGroupDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTouchable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTouchable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTouchable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTouchable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisplayPriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDisplayPriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisplayPriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDisplayPriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetPadding));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetPadding));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetMargin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetMargin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarkAnchor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetMarkAnchor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarkAnchor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetMarkAnchor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetVisibility));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetVisibility));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityText));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityText));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAllowDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAllowDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityLevel));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityLevel));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityDescription));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityDescription));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "common"), common);

    auto counter = panda::ObjectRef::New(vm);
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableDec));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableDec));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "counter"), counter);

    auto checkboxgroup = panda::ObjectRef::New(vm);
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetGroupSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetGroupSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetGroupUnSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetGroupUnSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetGroupSelectAll));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetGroupSelectAll));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupWidth));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupWidth));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupHeight));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupHeight));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetGroupMark));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetGroupMark));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkboxgroup"), checkboxgroup);

    auto panel = panda::ObjectRef::New(vm);
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShow));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShow));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "panel"), panel);

    auto text = panda::ObjectRef::New(vm);
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontStyle));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontStyle));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextAlign));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextAlign));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontWeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontWeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetLineHeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetLineHeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextOverflow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextOverflow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetDecoration));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetDecoration));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "text"), text);

    auto select = panda::ObjectRef::New(vm);
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSpace));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetValue));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelected));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setArrowPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetArrowPosition));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuAlign));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetArrowPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetArrowPosition));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuAlign));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSpace));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetValue));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelected));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFontColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "select"), select);

    auto radio = panda::ObjectRef::New(vm);
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioChecked"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioChecked));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioChecked"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioChecked));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioStyle));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "radio"), radio);

    auto checkbox = panda::ObjectRef::New(vm);
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetMark));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetMark));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetUnSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetUnSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelect));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelect));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxWidth));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxWidth));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxHeight));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxHeight));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkbox"), checkbox);

    auto textpicker = panda::ObjectRef::New(vm);
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetBackgroundColor));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textpicker"), textpicker);

    auto timepicker = panda::ObjectRef::New(vm);
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetSelectedTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetDisappearTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetSelectedTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetDisappearTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerBackgroundColor));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "timepicker"), timepicker);

    auto rating = panda::ObjectRef::New(vm);
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStars"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStars));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStars"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStars));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetRatingStepSize));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetRatingStepSize));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStarStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStarStyle));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStarStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStarStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rating"), rating);

    auto slider = panda::ObjectRef::New(vm);
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowTips));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowTips));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSliderStepSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSliderStepSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTrackBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTrackBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetStepColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetStepColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderWidth));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderWidth));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBackgroundColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBackgroundColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSelectColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSelectColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowSteps"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowSteps));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowSteps"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowSteps));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setThickness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetThickness));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetThickness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetThickness));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "slider"), slider);

    auto blank = panda::ObjectRef::New(vm);
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetColor));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "blank"), blank);

    auto gridCol = panda::ObjectRef::New(vm);
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetSpan));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetSpan));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridColOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetGridColOffset));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridColOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetGridColOffset));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOrder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetOrder));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOrder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetOrder));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridCol"), gridCol);

    auto gridRow = panda::ObjectRef::New(vm);
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetAlignItems));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetAlignItems));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridRow"), gridRow);

    auto richEditor = panda::ObjectRef::New(vm);
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCopyOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCopyOptions));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "richEditor"), richEditor);

    auto textArea = panda::ObjectRef::New(vm);
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextAreaBridge::SetMaxLines));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxLines));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textArea"), textArea);

    auto video = panda::ObjectRef::New(vm);
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetAutoPlay));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetAutoPlay));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetControls));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetControls));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetObjectFit));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetObjectFit));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetLoop));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetLoop));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetMuted));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetMuted));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "video"), video);

    RegisterButtonAttributes(object, vm);
    RegisterToggleAttributes(object, vm);
    RegisterDividerAttributes(object, vm);
    RegisterNavigationAttributes(object, vm);
    RegisterImageAttributes(object, vm);
    RegisterNavRouterAttributes(object, vm);
    RegisterNavigatorAttributes(object, vm);

    return object;
}

void ArkUINativeModule::RegisterButtonAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto button = panda::ObjectRef::New(vm);
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetType));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetType));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStateEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetStateEffect));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStateEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetStateEffect));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontWeight));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontWeight));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontFamily));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontFamily));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabelStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetLabelStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLabelStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetLabelStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "button"), button);
}

void ArkUINativeModule::RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto toggle = panda::ObjectRef::New(vm);
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSwitchPointColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSwitchPointColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "toggle"), toggle);
}

void ArkUINativeModule::RegisterDividerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto divider = panda::ObjectRef::New(vm);
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetStrokeWidth));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetStrokeWidth));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetLineCap));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetLineCap));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetColor));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetColor));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetVertical));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetVertical));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "divider"), divider);
}

void ArkUINativeModule::RegisterNavigationAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navigation = panda::ObjectRef::New(vm);
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideToolBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideToolBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTitleMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetTitleMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTitleMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetTitleMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideBackButton));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideBackButton));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSubTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetSubtitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSubTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetSubtitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideNavBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideNavBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideNavBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideNavBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetUsrNavigationMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetUsrNavigationMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNavBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetNavBarPosition));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNavBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetNavBarPosition));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetMinNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetMinNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetMaxNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetMaxNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideTitleBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideTitleBar));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigation"), navigation);
}

void ArkUINativeModule::RegisterImageAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto image = panda::ObjectRef::New(vm);
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::SetObjectFit));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::ResetObjectFit));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "image"), image);
}

void ArkUINativeModule::RegisterNavRouterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navRouter = panda::ObjectRef::New(vm);
    navRouter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavRouterBridge::SetMode));
    navRouter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavRouterBridge::ResetMode));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navRouter"), navRouter);
}

void ArkUINativeModule::RegisterNavigatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navigator = panda::ObjectRef::New(vm);
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTarget"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetTarget));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTarget"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetTarget));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetType));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetType));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setActive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetActive));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetActive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetActive));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setParams"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetParams));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetParams"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetParams));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigator"), navigator);
}
} // namespace OHOS::Ace::NG
