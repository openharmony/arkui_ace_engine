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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/shape.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/render_node/render_node_properties.h"
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

    auto leftStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 1);
    auto leftStyleValue = static_cast<BorderStyle>(leftStyle);

    auto topStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2);
    auto topStyleValue = static_cast<BorderStyle>(topStyle);

    auto rightStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3);
    auto rightStyleValue = static_cast<BorderStyle>(rightStyle);

    auto bottomStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4);
    auto bottomStyleValue = static_cast<BorderStyle>(bottomStyle);

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

    auto leftWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1);
    auto topWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2);
    auto rightWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3);
    auto bottomWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4);

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

    auto leftColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 1);
    auto topColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2);
    auto rightColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3);
    auto bottomColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4);

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

    auto topLeftRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 1);
    auto topRightRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 2);
    auto bottomLeftRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 3);
    auto bottomRightRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 4);

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

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4);
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 6);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7);

    RectF rect(leftValue, topValue, rightValue - leftValue, bottomValue - topValue);
    ShapeMaskProperty property { fillColorValue, strokeColorValue, strokeWidthValue };

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRectMask(
        nativeNode, rect, property);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetCircleMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    auto centerXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1);
    auto centerYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2);
    auto radiusValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3);
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 6);

    Circle circle;
    Dimension centerX(centerXValue, DimensionUnit::VP);
    circle.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::VP);
    circle.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::VP);
    circle.SetRadius(radius);

    ShapeMaskProperty property { fillColorValue, strokeColorValue, strokeWidthValue };

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetCircleMask(
        nativeNode, circle, property);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRoundRectMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    RoundRect roundRect;
    auto topLeftXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1);
    auto topLeftYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2);
    roundRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, topLeftXValue, topLeftYValue);

    auto topRightXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3);
    auto topRightYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4);
    roundRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, topRightXValue, topRightYValue);

    auto bottomLeftXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 5);
    auto bottomLeftYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 6);
    roundRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, bottomLeftXValue, bottomLeftYValue);

    auto bottomRightXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7);
    auto bottomRightYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 8);
    roundRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, bottomRightXValue, bottomRightYValue);

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 9);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 10);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 11);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 12);

    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 13);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 14);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 15);

    RectF rect(leftValue, topValue, rightValue - leftValue, bottomValue - topValue);
    roundRect.SetRect(rect);

    ShapeMaskProperty property { fillColorValue, strokeColorValue, strokeWidthValue };

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetRoundRectMask(
        nativeNode, roundRect, property);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetOvalMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4);
    RectF rect(leftValue, topValue, rightValue - leftValue, bottomValue - topValue);

    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 6);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7);

    ShapeMaskProperty property { fillColorValue, strokeColorValue, strokeWidthValue };

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetOvalMask(
        nativeNode, rect, property);
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

    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4);

    ShapeMaskProperty property { fillColorValue, strokeColorValue, strokeWidthValue };

    GetArkUIInternalNodeAPI()->GetRenderNodeModifier().SetCommandPathMask(
        nativeNode, pathValue, property);
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
