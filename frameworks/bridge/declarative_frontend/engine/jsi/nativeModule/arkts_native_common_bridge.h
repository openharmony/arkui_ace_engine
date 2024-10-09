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
#include "core/components_ng/pattern/gesture/gesture_model.h"

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
    static ArkUINativeModuleValue SetOutlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOutlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOutlineRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOutlineRadius(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOutlineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOutlineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOutlineStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOutlineStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOutline(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOutline(ArkUIRuntimeCallInfo* runtimeCallInfo);
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
    static ArkUINativeModuleValue SetOverlay(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOverlay(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderImage(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLocalizedBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderWithDashParams(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundImageResizable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundImageResizable(ArkUIRuntimeCallInfo* runtimeCallInfo);
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
    static ArkUINativeModuleValue SetClipShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetClipShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
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
    static ArkUINativeModuleValue SetMotionBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMotionBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
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
    static ArkUINativeModuleValue SetConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLayoutWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLayoutWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAlignSelf(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAlignSelf(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAspectRatio(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAspectRatio(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFlexGrow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFlexGrow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFlexShrink(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFlexShrink(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGridOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGridOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetGridSpan(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetGridSpan(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetExpandSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetExpandSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAlignRules(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAlignRules(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFlexBasis(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFlexBasis(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetKey(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetKey(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetRestoreId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetRestoreId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetObscured(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetObscured(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBackgroundBrightnessInternal(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBackgroundBrightnessInternal(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDragPreviewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDragPreviewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDragPreview(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDragPreview(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMouseResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMouseResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTransitionPassThrough(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTransitionPassThrough(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSharedTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSharedTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMask(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMask(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMaskShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaskShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetUseShadowBatching(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetUseShadowBatching(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAdvancedBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAdvancedBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMonopolizeEvents(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMonopolizeEvents(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAccessibilityGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAccessibilityGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetClickEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetClickEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetKeyBoardShortCut(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetKeyBoardShortCut(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPointLightStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPointLightStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetClipWithEdge(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetClipWithEdge(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static FrameNode* GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static Local<panda::ObjectRef> CreateGestureInfo(EcmaVM* vm, const RefPtr<NG::GestureInfo>& gestureInfo);
    static Local<panda::ObjectRef> CreateGestureEventInfo(
        EcmaVM* vm, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info);
    static Local<panda::ObjectRef> SetUniqueAttributes(
        EcmaVM* vm, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info);
    static Local<panda::ObjectRef> CreateRecognizerObject(EcmaVM* vm, const RefPtr<NG::NGGestureRecognizer>& target);
    static Local<panda::ObjectRef> CreateFingerInfo(EcmaVM* vm, const FingerInfo& fingerInfo);
    static Local<panda::ObjectRef> CreateEventTargetObject(EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info);
    static Local<panda::ObjectRef> CreateAreaObject(EcmaVM* vm, const RectF& rect, const OffsetF& origin);
    static void GetGestureCommonValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& priority, int32_t& mask);
    static void SetGestureTag(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber, ArkUIGesture* gesture);
    static void GetTapGestureValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers,
        int32_t& count, double& distanceThreshold, uint32_t argNumber);
    static void GetLongPressGestureValue(
        ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, bool& repeat, int32_t& duration, uint32_t argNumber);
    static void GetPanGestureValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, int32_t& direction,
        double& distance, uint32_t argNumber);
    static void GetSwipeGestureValue(
        ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, int32_t& direction, double& speed, uint32_t argNumber);
    static void GetPinchGestureValue(
        ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, double& distance, uint32_t argNumber);
    static void GetRotationGestureValue(
        ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, double& angle, uint32_t argNumber);
    static void GetGestureModeValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& mode, uint32_t argNumber);
    static void SetOnGestureEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, const GestureEventAction& action,
        uint32_t argNumber, ArkUIGesture* gesture);
    static void ParseLocalizedBorder(ArkUIRuntimeCallInfo* runtimeCallInfo, int& isLocalizedBorderWidth,
        int& isLocalizedBorderColor, int& isLocalizedBorderRadius);
    static ArkUIGesture* GetGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber);
    static Local<panda::ObjectRef> CreateCommonGestureEventInfo(EcmaVM* vm, GestureEvent& info);
    static Local<panda::ArrayRef> CreateFingerListArray(EcmaVM* vm, GestureEvent& info);
    static ArkUINativeModuleValue SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnAttach(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnAttach(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnDetach(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDetach(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnKeyPreIme(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnKeyPreIme(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnGestureJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnGestureJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnGestureRecognizerJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnGestureRecognizerJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetShouldBuiltInRecognizerParallelWith(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShouldBuiltInRecognizerParallelWith(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddTapGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddLongPressGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddPanGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddSwipeGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddPinchGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddRotationGesture(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddTapGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddLongPressGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddPanGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddSwipeGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddPinchGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddRotationGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AddGestureGroupToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AttachGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RemoveGestureByTag(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClearGestures(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetWindowName(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetWindowWidthBreakpoint(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetWindowHeightBreakpoint(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSystemBarEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue PostFrameCallback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFocusScopeId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFocusScopeId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFocusScopePriority(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFocusScopePriority(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetChainMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetChainMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPixelRound(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPixelRound(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue GreatOrEqualAPITargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LessThanAPITargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetApiTargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFocusBox(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFocusBox(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_COMMON_BRIDGE_H
