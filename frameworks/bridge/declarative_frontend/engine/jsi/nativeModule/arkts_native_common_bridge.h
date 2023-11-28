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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_COMMON_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_COMMON_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class CommonBridge {
public:
    static ArkUINativeModuleValue SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetShadow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShadow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHitTestBehavior(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHitTestBehavior(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetZIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetZIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackdropBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackdropBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHueRotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHueRotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetInvert(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetInvert(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSepia(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSepia(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSaturate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSaturate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetColorBlend(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetColorBlend(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContrast(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetContrast(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLinearGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLinearGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSweepGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSweepGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRadialGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRadialGradient(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImageSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundImageSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTranslate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTranslate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRotate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGeometryTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGeometryTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetClip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetClip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPixelStretchEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPixelStretchEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLightUpEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLightUpEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSphericalEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSphericalEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRenderGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRenderGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetUseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetUseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMotionPath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMotionPath(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGroupDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGroupDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFocusOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFocusOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFocusable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFocusable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTouchable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTouchable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDisplayPriority(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDisplayPriority(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMarkAnchor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMarkAnchor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetVisibility(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetVisibility(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAccessibilityText(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAccessibilityText(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAllowDrop(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAllowDrop(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAccessibilityLevel(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAccessibilityLevel(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_COMMON_BRIDGE_H
