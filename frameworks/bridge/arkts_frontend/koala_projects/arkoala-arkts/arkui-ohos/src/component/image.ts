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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, AttributeModifier } from "./common"
import { Resource } from "global.resource"
import { PixelMap } from "./arkui-pixelmap"
import { ResourceColor, ColorFilter, ResourceStr, EdgeWidths } from "./units"
import { ImageFit, ImageRepeat, CopyOptions, Color } from "./enums"
import { Matrix4Transit } from "./arkui-matrix4"
import { DrawingColorFilter, DrawingLattice } from "./arkui-drawing"
import { ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { ResolutionQuality } from "./arkui-external"
import { DrawableDescriptor } from "./arkui-drawabledescriptor"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkBaseNode } from "../handwritten/modifiers/ArkBaseNode"
import { ArkImageNode } from "../handwritten/modifiers/ArkImageNode"
import { ImageModifier } from "../handwritten/modifiers/ArkImageModifier"
import { ArkCommonAttributeSet, applyUIAttributes } from "../handwritten/modifiers/ArkCommonModifier"
import { AttributeUpdater } from "../AttributeUpdater"

export class ArkImagePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer  = new ArkImagePeer(_peerPtr, peerId, "Image", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptions0Attribute(src: PixelMap | ResourceStr | DrawableDescriptor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions1Attribute(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        else if (TypeChecker.isImageContent(src)) {
            thisSerializer.writeInt8(3 as int32)
            const src_3  = src as ImageContent
            thisSerializer.writeInt32(TypeChecker.ImageContent_ToNumeric(src_3))
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions2Attribute(src: PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        thisSerializer.writeImageAIOptions(imageAIOptions)
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: string | Resource | PixelMap | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
            else if (TypeChecker.isPixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as PixelMap
                thisSerializer.writePixelMap(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_alt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    matchTextDirectionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_matchTextDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fitOriginalSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fitOriginalSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillColor0Attribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillColor1Attribute(value: ResourceColor | ColorContent | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isColorContent(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ColorContent
                thisSerializer.writeColorContent(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_objectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    imageMatrixAttribute(value: Matrix4Transit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMatrix4Transit(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_imageMatrix(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectRepeatAttribute(value: ImageRepeat | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRepeat)
            thisSerializer.writeInt32(TypeChecker.ImageRepeat_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_objectRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoResizeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_autoResize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderModeAttribute(value: ImageRenderMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRenderMode)
            thisSerializer.writeInt32(TypeChecker.ImageRenderMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_renderMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dynamicRangeModeAttribute(value: DynamicRangeMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as DynamicRangeMode)
            thisSerializer.writeInt32(TypeChecker.DynamicRangeMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_dynamicRangeMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    interpolationAttribute(value: ImageInterpolation | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageInterpolation)
            thisSerializer.writeInt32(TypeChecker.ImageInterpolation_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_interpolation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sourceSizeAttribute(value: ImageSourceSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeImageSourceSize(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_sourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    syncLoadAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_syncLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter | undefined): void {
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
            else if (TypeChecker.isDrawingColorFilter(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as DrawingColorFilter
                thisSerializer.writeDrawingColorFilter(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_copyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    draggableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_draggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePointLightStyle(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAntialiasingAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_edgeAntialiasing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_enableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeImageAnalyzerConfig(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    resizableAttribute(value: ResizableOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeResizableOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_resizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enhancedImageQualityAttribute(value: ResolutionQuality | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ResolutionQuality)
            thisSerializer.writeInt32(TypeChecker.ResolutionQuality_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_enhancedImageQuality(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    orientationAttribute(value: ImageRotateOrientation | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRotateOrientation)
            thisSerializer.writeInt32(TypeChecker.ImageRotateOrientation_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_orientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ImageRenderMode {
    ORIGINAL = 0,
    Original = 0,
    TEMPLATE = 1,
    Template = 1
}
export enum ImageContent {
    EMPTY = 0
}
export enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2
}
export enum ImageInterpolation {
    NONE = 0,
    None = 0,
    LOW = 1,
    Low = 1,
    MEDIUM = 2,
    Medium = 2,
    HIGH = 3,
    High = 3
}
export enum ImageRotateOrientation {
    AUTO = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4
}
export interface ImageSourceSize {
    width: number;
    height: number;
}
export interface ColorContent {
}
export interface Type_ImageAttribute_onComplete_callback_event {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
}
export type Callback_Type_ImageAttribute_onComplete_callback_event_Void = (event?: Type_ImageAttribute_onComplete_callback_event) => void;
export interface ImageAttribute extends CommonMethod {
    alt(value: string | Resource | PixelMap | undefined): this
    matchTextDirection(value: boolean | undefined): this
    fitOriginalSize(value: boolean | undefined): this
    fillColor(value: ResourceColor | undefined | ResourceColor | ColorContent | undefined): this
    objectFit(value: ImageFit | undefined): this
    imageMatrix(value: Matrix4Transit | undefined): this
    objectRepeat(value: ImageRepeat | undefined): this
    autoResize(value: boolean | undefined): this
    renderMode(value: ImageRenderMode | undefined): this
    dynamicRangeMode(value: DynamicRangeMode | undefined): this
    interpolation(value: ImageInterpolation | undefined): this
    sourceSize(value: ImageSourceSize | undefined): this
    syncLoad(value: boolean | undefined): this
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this
    copyOption(value: CopyOptions | undefined): this
    draggable(value: boolean | undefined): this
    pointLight(value: PointLightStyle | undefined): this
    edgeAntialiasing(value: number | undefined): this
    onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined): this
    onError(value: ImageErrorCallback | undefined): this
    onFinish(value: (() => void) | undefined): this
    enableAnalyzer(value: boolean | undefined): this
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this
    resizable(value: ResizableOptions | undefined): this
    privacySensitive(value: boolean | undefined): this
    enhancedImageQuality(value: ResolutionQuality | undefined): this
    orientation(value: ImageRotateOrientation | undefined): this
}
export class ArkImageStyle extends ArkCommonMethodStyle implements ImageAttribute {
    alt_value?: string | Resource | PixelMap | undefined
    matchTextDirection_value?: boolean | undefined
    fitOriginalSize_value?: boolean | undefined
    fillColor_value?: ResourceColor | undefined
    objectFit_value?: ImageFit | undefined
    imageMatrix_value?: Matrix4Transit | undefined
    objectRepeat_value?: ImageRepeat | undefined
    autoResize_value?: boolean | undefined
    renderMode_value?: ImageRenderMode | undefined
    dynamicRangeMode_value?: DynamicRangeMode | undefined
    interpolation_value?: ImageInterpolation | undefined
    sourceSize_value?: ImageSourceSize | undefined
    syncLoad_value?: boolean | undefined
    colorFilter_value?: ColorFilter | DrawingColorFilter | undefined
    copyOption_value?: CopyOptions | undefined
    draggable_value?: boolean | undefined
    pointLight_value?: PointLightStyle | undefined
    edgeAntialiasing_value?: number | undefined
    onComplete_value?: ((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined
    onError_value?: ImageErrorCallback | undefined
    onFinish_value?: (() => void) | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    resizable_value?: ResizableOptions | undefined
    privacySensitive_value?: boolean | undefined
    enhancedImageQuality_value?: ResolutionQuality | undefined
    orientation_value?: ImageRotateOrientation | undefined
    public alt(value: string | Resource | PixelMap | undefined): this {
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        return this
    }
    public fillColor(value: ResourceColor | undefined | ResourceColor | ColorContent | undefined): this {
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        return this
    }
    public imageMatrix(value: Matrix4Transit | undefined): this {
        return this
    }
    public objectRepeat(value: ImageRepeat | undefined): this {
        return this
    }
    public autoResize(value: boolean | undefined): this {
        return this
    }
    public renderMode(value: ImageRenderMode | undefined): this {
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        return this
    }
    public interpolation(value: ImageInterpolation | undefined): this {
        return this
    }
    public sourceSize(value: ImageSourceSize | undefined): this {
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public draggable(value: boolean | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public edgeAntialiasing(value: number | undefined): this {
        return this
    }
    public onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined): this {
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        return this
    }
    public resizable(value: ResizableOptions | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public enhancedImageQuality(value: ResolutionQuality | undefined): this {
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        return this
        }
}
export type ImageErrorCallback = (error: ImageError) => void;
export interface ImageError {
    componentWidth: number;
    componentHeight: number;
    message: string;
}
export interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: DrawingLattice;
}
export class ArkImageComponent extends ArkCommonMethodComponent implements ImageAttribute {
    getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }

    getModifierHost(): ArkBaseNode {
        if (this._modifierHost == undefined || this._modifierHost == null) {
            this._modifierHost = new ArkImageNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost!
    }

    public setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_type = runtimeType(src)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if ((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src))) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                this.getPeer()?.setImageOptions0Attribute(src_casted)
                return this
            }
            if ((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src))) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setImageOptions2Attribute(src_casted, imageAIOptions_casted)
                return this
            }
            if ((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src)) || (TypeChecker.isImageContent(src))) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
                this.getPeer()?.setImageOptions1Attribute(src_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public alt(value: string | Resource | PixelMap | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | PixelMap | undefined)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        if (this.checkPriority("matchTextDirection")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.matchTextDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        if (this.checkPriority("fitOriginalSize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.fitOriginalSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fillColor(value: ResourceColor | undefined | ResourceColor | ColorContent | undefined): this {
        if (this.checkPriority("fillColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.fillColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | ColorContent | undefined)
                this.getPeer()?.fillColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public imageMatrix(value: Matrix4Transit | undefined): this {
        if (this.checkPriority("imageMatrix")) {
            const value_casted = value as (Matrix4Transit | undefined)
            this.getPeer()?.imageMatrixAttribute(value_casted)
            return this
        }
        return this
    }
    public objectRepeat(value: ImageRepeat | undefined): this {
        if (this.checkPriority("objectRepeat")) {
            const value_casted = value as (ImageRepeat | undefined)
            this.getPeer()?.objectRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    public autoResize(value: boolean | undefined): this {
        if (this.checkPriority("autoResize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoResizeAttribute(value_casted)
            return this
        }
        return this
    }
    public renderMode(value: ImageRenderMode | undefined): this {
        if (this.checkPriority("renderMode")) {
            const value_casted = value as (ImageRenderMode | undefined)
            this.getPeer()?.renderModeAttribute(value_casted)
            return this
        }
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (this.checkPriority("dynamicRangeMode")) {
            const value_casted = value as (DynamicRangeMode | undefined)
            this.getPeer()?.dynamicRangeModeAttribute(value_casted)
            return this
        }
        return this
    }
    public interpolation(value: ImageInterpolation | undefined): this {
        if (this.checkPriority("interpolation")) {
            const value_casted = value as (ImageInterpolation | undefined)
            this.getPeer()?.interpolationAttribute(value_casted)
            return this
        }
        return this
    }
    public sourceSize(value: ImageSourceSize | undefined): this {
        if (this.checkPriority("sourceSize")) {
            const value_casted = value as (ImageSourceSize | undefined)
            this.getPeer()?.sourceSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        if (this.checkPriority("syncLoad")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.syncLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter | undefined)
            this.getPeer()?.colorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeAntialiasing(value: number | undefined): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.edgeAntialiasingAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (((event?: Type_ImageAttribute_onComplete_callback_event) => void) | undefined)
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig | undefined)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public resizable(value: ResizableOptions | undefined): this {
        if (this.checkPriority("resizable")) {
            const value_casted = value as (ResizableOptions | undefined)
            this.getPeer()?.resizableAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public enhancedImageQuality(value: ResolutionQuality | undefined): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (ResolutionQuality | undefined)
            this.getPeer()?.enhancedImageQualityAttribute(value_casted)
            return this
        }
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        if (this.checkPriority("orientation")) {
            const value_casted = value as (ImageRotateOrientation | undefined)
            this.getPeer()?.orientationAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier<T>(value: AttributeModifier<T>): this {
        let peerNode = this.getPeer()
        if (!peerNode._attributeSet) {
            let isImageModifier: boolean = (value instanceof ImageModifier)
            if (isImageModifier) {
                let imageModifier = value as object as ImageModifier
                peerNode._attributeSet = imageModifier.attribute
            } else {
                peerNode._attributeSet = new ArkCommonAttributeSet()
            }
        }
        applyUIAttributes(value, peerNode)
        let isAttributeUpdater: boolean = (value instanceof AttributeUpdater)
        if (isAttributeUpdater) {
            let attributeUpdater = value as object as AttributeUpdater<ImageAttribute, ImageInterface>
            attributeUpdater.updateConstructorParams = (...params: Object[]) => {
                const node = this.getModifierHost()! as ArkImageNode
                this.getModifierHost()!.constructParam(params)
                return node
            }
        }
        peerNode._attributeSet!.applyModifierPatch(peerNode)
        return this
    }

    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

export type ImageInterface = (...param: Object[]) => ArkImageNode

/** @memo */
export function Image(
    /** @memo */
    style: ((attributes: ImageAttribute) => void) | undefined,
    src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer) => {
        receiver.setImageOptions(src,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
