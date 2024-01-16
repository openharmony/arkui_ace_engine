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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"

#include <cstdint>

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/node/api.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RenderNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* childNativeNode = secondArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().AppendChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* child = secondArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    if (thirdArg.IsNull()) {
        GetArkUIInternalNodeAPI()->GetRenderNodeModifier().InsertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    void* sibling = thirdArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().InsertChildAfter(nativeNode, child, sibling);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* childNativeNode = secondArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().RemoveChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().ClearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetClipToFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    bool useClip = false;
    if (secondArg->IsBoolean()) {
        useClip = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetClipToFrame(nativeNode, useClip);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRotation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);
    double rotationX = 0.0;
    double rotationY = 0.0;
    double rotationZ = 0.0;
    if (secondArg->IsNumber()) {
        rotationX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        rotationY = thirdArg->ToNumber(vm)->Value();
    }
    if (fourthArg->IsNumber()) {
        rotationZ = fourthArg->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRotation(nativeNode, rotationX, rotationY, rotationZ);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> color = runtimeCallInfo->GetCallArgRef(1);
    uint32_t colorValue = 0;
    if (color->IsNumber()) {
        colorValue = color->Uint32Value(vm);
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowColor(nativeNode, colorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    double offsetX = 0.0;
    double offsetY = 0.0;
    if (secondArg->IsNumber()) {
        offsetX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        offsetY = thirdArg->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowOffset(nativeNode, offsetX, offsetY);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> alpha = runtimeCallInfo->GetCallArgRef(1);
    float alphaValue = 1.0;
    if (alpha->IsNumber()) {
        alphaValue = alpha->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowAlpha(nativeNode, alphaValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowElevation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> elevation = runtimeCallInfo->GetCallArgRef(1);
    float elevationValue = 0;
    if (elevation->IsNumber()) {
        elevationValue = elevation->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowElevation(nativeNode, elevationValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> radius = runtimeCallInfo->GetCallArgRef(1);
    float radiusValue = 0;
    if (radius->IsNumber()) {
        radiusValue = radius->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetShadowRadius(nativeNode, radiusValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    Local<JSValueRef> scaleX = runtimeCallInfo->GetCallArgRef(1);
    float scaleXValue = 0;
    if (scaleX->IsNumber()) {
        scaleXValue = scaleX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> scaleY = runtimeCallInfo->GetCallArgRef(2);
    float scaleYValue = 0;
    if (scaleY->IsNumber()) {
        scaleYValue = scaleY->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetScale(nativeNode, scaleXValue, scaleYValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> color = runtimeCallInfo->GetCallArgRef(1);
    float colorValue = 0;
    if (color->IsNumber()) {
        colorValue = color->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRenderNodeBackgroundColor(nativeNode, colorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetPivot(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    Local<JSValueRef> pivotX = runtimeCallInfo->GetCallArgRef(1);
    float pivotXValue = 0;
    if (pivotX->IsNumber()) {
        pivotXValue = pivotX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> pivotY = runtimeCallInfo->GetCallArgRef(2);
    float pivotYValue = 0;
    if (pivotY->IsNumber()) {
        pivotYValue = pivotY->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetPivot(nativeNode, pivotXValue, pivotYValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    Local<JSValueRef> positionX = runtimeCallInfo->GetCallArgRef(1);
    float positionXValue = 0;
    if (positionX->IsNumber()) {
        positionXValue = positionX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> positionY = runtimeCallInfo->GetCallArgRef(2);
    float positionYValue = 0;
    if (positionY->IsNumber()) {
        positionYValue = positionY->ToNumber(vm)->Value();
    }

    Local<JSValueRef> width = runtimeCallInfo->GetCallArgRef(3);
    float widthValue = 0;
    if (width->IsNumber()) {
        widthValue = width->ToNumber(vm)->Value();
    }

    Local<JSValueRef> height = runtimeCallInfo->GetCallArgRef(4);
    float heightValue = 0;
    if (height->IsNumber()) {
        heightValue = height->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetFrame(
        nativeNode, positionXValue, positionYValue, widthValue, heightValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> width = runtimeCallInfo->GetCallArgRef(1);
    float widthValue = 0;
    if (width->IsNumber()) {
        widthValue = width->ToNumber(vm)->Value();
    }

    Local<JSValueRef> height = runtimeCallInfo->GetCallArgRef(2);
    float heightValue = 0;
    if (height->IsNumber()) {
        heightValue = height->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetSize(nativeNode, widthValue, heightValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> opacity = runtimeCallInfo->GetCallArgRef(1);
    float opacityValue = 0;
    if (opacity->IsNumber()) {
        opacityValue = opacity->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetOpacity(nativeNode, opacityValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetTranslate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    Local<JSValueRef> translateX = runtimeCallInfo->GetCallArgRef(1);
    float translateXValue = 0;
    if (translateX->IsNumber()) {
        translateXValue = translateX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> translateY = runtimeCallInfo->GetCallArgRef(2);
    float translateYValue = 0;
    if (translateY->IsNumber()) {
        translateYValue = translateY->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetTranslate(
        nativeNode, translateXValue, translateYValue, 0);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> leftStyle = runtimeCallInfo->GetCallArgRef(1);
    BorderStyle leftStyleValue = BorderStyle::NONE;
    if (leftStyle->IsNumber()) {
        leftStyleValue = static_cast<BorderStyle>(leftStyle->Uint32Value(vm));
    }

    Local<JSValueRef> topStyle = runtimeCallInfo->GetCallArgRef(2);
    BorderStyle topStyleValue = BorderStyle::NONE;
    if (topStyle->IsNumber()) {
        topStyleValue = static_cast<BorderStyle>(topStyle->Uint32Value(vm));
    }

    Local<JSValueRef> rightStyle = runtimeCallInfo->GetCallArgRef(3);
    BorderStyle rightStyleValue = BorderStyle::NONE;
    if (rightStyle->IsNumber()) {
        rightStyleValue = static_cast<BorderStyle>(rightStyle->Uint32Value(vm));
    }

    Local<JSValueRef> bottomStyle = runtimeCallInfo->GetCallArgRef(4);
    BorderStyle bottomStyleValue = BorderStyle::NONE;
    if (bottomStyle->IsNumber()) {
        bottomStyleValue = static_cast<BorderStyle>(bottomStyle->Uint32Value(vm));
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetBorderStyle(
        nativeNode, leftStyleValue, topStyleValue, rightStyleValue, bottomStyleValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> leftWidth = runtimeCallInfo->GetCallArgRef(1);
    float leftWidthValue = 0;
    if (leftWidth->IsNumber()) {
        leftWidthValue = leftWidth->ToNumber(vm)->Value();
    }

    Local<JSValueRef> topWidth = runtimeCallInfo->GetCallArgRef(2);
    float topWidthValue = 0;
    if (topWidth->IsNumber()) {
        topWidthValue = topWidth->ToNumber(vm)->Value();
    }

    Local<JSValueRef> rightWidth = runtimeCallInfo->GetCallArgRef(3);
    float rightWidthValue = 0;
    if (rightWidth->IsNumber()) {
        rightWidthValue = rightWidth->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottomWidth = runtimeCallInfo->GetCallArgRef(4);
    float bottomWidthValue = 0;
    if (bottomWidth->IsNumber()) {
        bottomWidthValue = bottomWidth->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetBorderWidth(
        nativeNode, leftWidthValue, topWidthValue, rightWidthValue, bottomWidthValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> leftColor = runtimeCallInfo->GetCallArgRef(1);
    uint32_t leftColorValue = 0;
    if (leftColor->IsNumber()) {
        leftColorValue = leftColor->Uint32Value(vm);
    }

    Local<JSValueRef> topColor = runtimeCallInfo->GetCallArgRef(2);
    uint32_t topColorValue = 0;
    if (topColor->IsNumber()) {
        topColorValue = topColor->Uint32Value(vm);
    }

    Local<JSValueRef> rightColor = runtimeCallInfo->GetCallArgRef(3);
    uint32_t rightColorValue = 0;
    if (rightColor->IsNumber()) {
        rightColorValue = rightColor->Uint32Value(vm);
    }

    Local<JSValueRef> bottomColor = runtimeCallInfo->GetCallArgRef(4);
    uint32_t bottomColorValue = 0;
    if (bottomColor->IsNumber()) {
        bottomColorValue = bottomColor->Uint32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetBorderColor(
        nativeNode, leftColorValue, topColorValue, rightColorValue, bottomColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> topLeftRadius = runtimeCallInfo->GetCallArgRef(1);
    double topLeftRadiusValue = 0;
    if (topLeftRadius->IsNumber()) {
        topLeftRadiusValue = topLeftRadius->ToNumber(vm)->Value();
    }

    Local<JSValueRef> topRightRadius = runtimeCallInfo->GetCallArgRef(2);
    double topRightRadiusValue = 0;
    if (topRightRadius->IsNumber()) {
        topRightRadiusValue = topRightRadius->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottomLeftRadius = runtimeCallInfo->GetCallArgRef(3);
    double bottomLeftRadiusValue = 0;
    if (bottomLeftRadius->IsNumber()) {
        bottomLeftRadiusValue = bottomLeftRadius->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottomRightRadius = runtimeCallInfo->GetCallArgRef(4);
    double bottomRightRadiusValue = 0;
    if (bottomRightRadius->IsNumber()) {
        bottomRightRadiusValue = bottomRightRadius->ToNumber(vm)->Value();
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetBorderRadius(
        nativeNode, topLeftRadiusValue, topRightRadiusValue, bottomLeftRadiusValue, bottomRightRadiusValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRectMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> left = runtimeCallInfo->GetCallArgRef(1);
    float leftValue = 0;
    if (left->IsNumber()) {
        leftValue = left->ToNumber(vm)->Value();
    }

    Local<JSValueRef> top = runtimeCallInfo->GetCallArgRef(2);
    float topValue = 0;
    if (top->IsNumber()) {
        topValue = top->ToNumber(vm)->Value();
    }

    Local<JSValueRef> right = runtimeCallInfo->GetCallArgRef(3);
    float rightValue = 0;
    if (right->IsNumber()) {
        rightValue = right->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottom = runtimeCallInfo->GetCallArgRef(4);
    float bottomValue = 0;
    if (bottom->IsNumber()) {
        bottomValue = bottom->ToNumber(vm)->Value();
    }

    Local<JSValueRef> fillColor = runtimeCallInfo->GetCallArgRef(5);
    uint32_t fillColorValue = 0;
    if (fillColor->IsNumber()) {
        fillColorValue = fillColor->Uint32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRectMask(
        nativeNode, leftValue, topValue, rightValue, bottomValue, fillColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetCircleMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> centerX = runtimeCallInfo->GetCallArgRef(1);
    float centerXValue = 0;
    if (centerX->IsNumber()) {
        centerXValue = centerX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> centerY = runtimeCallInfo->GetCallArgRef(2);
    float centerYValue = 0;
    if (centerY->IsNumber()) {
        centerYValue = centerY->ToNumber(vm)->Value();
    }

    Local<JSValueRef> radius = runtimeCallInfo->GetCallArgRef(3);
    float radiusValue = 0;
    if (radius->IsNumber()) {
        radiusValue = radius->ToNumber(vm)->Value();
    }

    Local<JSValueRef> fillColor = runtimeCallInfo->GetCallArgRef(4);
    uint32_t fillColorValue = 0;
    if (fillColor->IsNumber()) {
        fillColorValue = fillColor->Uint32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetCircleMask(
        nativeNode, centerXValue, centerYValue, radiusValue, fillColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRoundRectMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    RoundRect roundRect;
    Local<JSValueRef> topLeftX = runtimeCallInfo->GetCallArgRef(1);
    float topLeftXValue = 0;
    if (topLeftX->IsNumber()) {
        topLeftXValue = topLeftX->ToNumber(vm)->Value();
    }
    Local<JSValueRef> topLeftY = runtimeCallInfo->GetCallArgRef(2);
    float topLeftYValue = 0;
    if (topLeftY->IsNumber()) {
        topLeftYValue = topLeftY->ToNumber(vm)->Value();
    }
    roundRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, topLeftXValue, topLeftYValue);

    Local<JSValueRef> topRightX = runtimeCallInfo->GetCallArgRef(3);
    float topRightXValue = 0;
    if (topRightX->IsNumber()) {
        topRightXValue = topRightX->ToNumber(vm)->Value();
    }
    Local<JSValueRef> topRightY = runtimeCallInfo->GetCallArgRef(4);
    float topRightYValue = 0;
    if (topRightY->IsNumber()) {
        topRightYValue = topRightY->ToNumber(vm)->Value();
    }
    roundRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, topRightXValue, topRightYValue);

    Local<JSValueRef> bottomLeftX = runtimeCallInfo->GetCallArgRef(5);
    float bottomLeftXValue = 0;
    if (bottomLeftX->IsNumber()) {
        bottomLeftXValue = bottomLeftX->ToNumber(vm)->Value();
    }
    Local<JSValueRef> bottomLeftY = runtimeCallInfo->GetCallArgRef(6);
    float bottomLeftYValue = 0;
    if (bottomLeftY->IsNumber()) {
        bottomLeftYValue = bottomLeftY->ToNumber(vm)->Value();
    }
    roundRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, bottomLeftXValue, bottomLeftYValue);

    Local<JSValueRef> bottomRightX = runtimeCallInfo->GetCallArgRef(7);
    float bottomRightXValue = 0;
    if (bottomRightX->IsNumber()) {
        bottomRightXValue = bottomRightX->ToNumber(vm)->Value();
    }
    Local<JSValueRef> bottomRightY = runtimeCallInfo->GetCallArgRef(8);
    float bottomRightYValue = 0;
    if (bottomRightY->IsNumber()) {
        bottomRightYValue = bottomRightY->ToNumber(vm)->Value();
    }
    roundRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, bottomRightXValue, bottomRightYValue);

    Local<JSValueRef> left = runtimeCallInfo->GetCallArgRef(9);
    float leftValue = 0;
    if (left->IsNumber()) {
        leftValue = left->ToNumber(vm)->Value();
    }

    Local<JSValueRef> top = runtimeCallInfo->GetCallArgRef(10);
    float topValue = 0;
    if (top->IsNumber()) {
        topValue = top->ToNumber(vm)->Value();
    }

    Local<JSValueRef> right = runtimeCallInfo->GetCallArgRef(11);
    float rightValue = 0;
    if (right->IsNumber()) {
        rightValue = right->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottom = runtimeCallInfo->GetCallArgRef(12);
    float bottomValue = 0;
    if (bottom->IsNumber()) {
        bottomValue = bottom->ToNumber(vm)->Value();
    }

    Local<JSValueRef> fillColor = runtimeCallInfo->GetCallArgRef(13);
    uint32_t fillColorValue = 0;
    if (fillColor->IsNumber()) {
        fillColorValue = fillColor->Uint32Value(vm);
    }
    RectF rect(leftValue, topValue, rightValue - leftValue, bottomValue - topValue);
    roundRect.SetRect(rect);

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRoundRectMask(nativeNode, roundRect, fillColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetOvalMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> left = runtimeCallInfo->GetCallArgRef(1);
    float leftValue = 0;
    if (left->IsNumber()) {
        leftValue = left->ToNumber(vm)->Value();
    }

    Local<JSValueRef> top = runtimeCallInfo->GetCallArgRef(2);
    float topValue = 0;
    if (top->IsNumber()) {
        topValue = top->ToNumber(vm)->Value();
    }

    Local<JSValueRef> right = runtimeCallInfo->GetCallArgRef(3);
    float rightValue = 0;
    if (right->IsNumber()) {
        rightValue = right->ToNumber(vm)->Value();
    }

    Local<JSValueRef> bottom = runtimeCallInfo->GetCallArgRef(4);
    float bottomValue = 0;
    if (bottom->IsNumber()) {
        bottomValue = bottom->ToNumber(vm)->Value();
    }

    Local<JSValueRef> fillColor = runtimeCallInfo->GetCallArgRef(5);
    uint32_t fillColorValue = 0;
    if (fillColor->IsNumber()) {
        fillColorValue = fillColor->Uint32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetOvalMask(
        nativeNode, leftValue, topValue, rightValue, bottomValue, fillColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetCommandPathMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> path = runtimeCallInfo->GetCallArgRef(1);
    std::string pathValue;
    if (path->IsString()) {
        pathValue = path->ToString(vm)->ToString();
    }

    Local<JSValueRef> fillColor = runtimeCallInfo->GetCallArgRef(2);
    uint32_t fillColorValue = 0;
    if (fillColor->IsNumber()) {
        fillColorValue = fillColor->Uint32Value(vm);
    }

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetCommandPathMask(nativeNode, pathValue, fillColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::Invalidate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().Invalidate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
