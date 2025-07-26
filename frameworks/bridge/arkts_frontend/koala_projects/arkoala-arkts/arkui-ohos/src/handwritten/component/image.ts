/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ArkUIAniModule } from "arkui.ani"

export class ColorContent {
    constructor() { }
    public static readonly ORIGIN: ColorContent = new ColorContent();
}
function fillColor0Attribute(peer: KPointer, value: ResourceColor | undefined): void {
    const thisSerializer: Serializer = Serializer.hold()
    let value_type: int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    thisSerializer.writeInt8(value_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        const value_value = value!
        let value_value_type: int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (TypeChecker.isColor(value_value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_value_0 = value_value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
        }
        else if (RuntimeType.NUMBER == value_value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_value_1 = value_value as number
            thisSerializer.writeNumber(value_value_1)
        }
        else if (RuntimeType.STRING == value_value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_value_2 = value_value as string
            thisSerializer.writeString(value_value_2)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_value_3 = value_value as Resource
            thisSerializer.writeResource(value_value_3)
        }
    }
    ArkUIGeneratedNativeModule._ImageAttribute_fillColor0(peer, thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()
}
function fillColor1Attribute(peer: KPointer, value: ColorContent | undefined): void {
    const thisSerializer: Serializer = Serializer.hold()
    let value_type: int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    thisSerializer.writeInt8(value_type as int32)
    const value_value = value!
    thisSerializer.writeInt8(1 as int32)
    const value_value_1 = value_value as ColorContent
    thisSerializer.writeColorContent(value_value_1)
    ArkUIGeneratedNativeModule._ImageAttribute_fillColor1(peer, thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()
}

function hookSetImageFillColor(peer: KPointer, value: ResourceColor | ColorContent | ColorMetrics | undefined): void {
    if (value instanceof ColorMetrics) {
        throw new Error("ColorMetrics parameters not implemented")
    }
    if (value instanceof ColorContent) {
        const value_casted = value as ColorContent
        fillColor1Attribute(peer, value_casted)
    } else {
        const value_casted = value as (ResourceColor | undefined)
        fillColor0Attribute(peer, value_casted)
    }
}

function hookSetResizableOptions(peer: ArkImagePeer, value: ResizableOptions | undefined) {
    if (value != undefined && value.lattice != undefined) {
        ArkUIAniModule._Image_ResizableOptions(peer.getPeerPtr(), value.lattice as drawing.Lattice)
        return
    }
    const thisSerializer: Serializer = Serializer.hold()
    let value_type: int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    thisSerializer.writeInt8(value_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        const value_value = value!
        thisSerializer.writeResizableOptions(value_value)
    }
    ArkUIGeneratedNativeModule._ImageAttribute_resizable(peer.getPeerPtr(), thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()
}

enum DrawableType {
    BASE = 0,
    LAYERDED = 1,
    ANIMATED = 2,
    PIXELMAP = 3
}

function checkDrawableType(value: DrawableDescriptor): DrawableType {
    if (value instanceof PixelMapDrawableDescriptor) {
        return DrawableType.PIXELMAP
    }
    if (value instanceof AnimatedDrawableDescriptor) {
        return DrawableType.ANIMATED
    }
    if (value instanceof LayeredDrawableDescriptor) {
        return DrawableType.LAYERDED
    }
    return DrawableType.BASE
}

function SetImageAIOptions(component: ArkImageComponent, imageAIOptions?: ImageAIOptions) {
    if (imageAIOptions == undefined) {
        return
    }
    throw new Error("ImageAIOptions parameters not implemented")
}

function hookSetImageOptions(component: ArkImageComponent, src: PixelMap | Resource | string | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): void {
    if (src instanceof DrawableDescriptor) {
        let drawableType = checkDrawableType(src) as int
        let value = src as DrawableDescriptor
        ArkUIAniModule._Image_Consturct_DrawableDescriptor(component.getPeer().getPeerPtr(), value, drawableType)
        SetImageAIOptions(component, imageAIOptions)
        return
    }
    if (src instanceof PixelMap) {
        let value = src as PixelMap
        ArkUIAniModule._Image_Consturct_PixelMap(component.getPeer().getPeerPtr(), value)
        SetImageAIOptions(component, imageAIOptions)
        return
    }
    const thisSerializer: Serializer = Serializer.hold()
    if (src instanceof string || src instanceof Resource) {
        thisSerializer.writeInt8(1 as int32)
        if (src instanceof string) {
            thisSerializer.writeInt8(0 as int32)
            thisSerializer.writeString(src as string)
        }
        else if (src instanceof Resource) {
            thisSerializer.writeInt8(1 as int32)
            thisSerializer.writeResource(src as Resource)
        }
    }
    else if (src instanceof ImageContent) {
        thisSerializer.writeInt8(3 as int32)
        thisSerializer.writeInt32(src as int32)
    }
    ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(component.getPeer().getPeerPtr(), thisSerializer.asBuffer(), thisSerializer.length())
    SetImageAIOptions(component, imageAIOptions)
    thisSerializer.release()
}

function hookSetColorFilter(component: ArkImageComponent, value: ColorFilter | drawing.ColorFilter | undefined) {
    if (value !== undefined && value instanceof drawing.ColorFilter) {
        ArkUIAniModule._Image_DrawingColorFilter(component.getPeer().getPeerPtr(), value as drawing.ColorFilter)
        return
    }
    const thisSerializer : Serializer = Serializer.hold()
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    thisSerializer.writeInt8(value_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        const value_value  = value!
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (TypeChecker.isColorFilter(value_value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_value_0  = value_value as ColorFilter
            thisSerializer.writeColorFilter(value_value_0)
        }
    }
    ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(component.getPeer().getPeerPtr(), thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()
}
