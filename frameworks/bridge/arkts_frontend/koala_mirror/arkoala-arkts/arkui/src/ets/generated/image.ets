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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { image_PixelMap_serializer, image } from "./ohos.multimedia.image"
import { Resource_serializer, Resource } from "./resource"
import { DrawableDescriptor_serializer, DrawableDescriptor } from "./ohos.arkui.drawableDescriptor"
import { ImageAIOptions_serializer, ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { ColorMetrics_serializer, ColorMetrics } from "./ark.Graphics"
import { matrix4_Matrix4Transit_serializer, matrix4 } from "./ohos.matrix4"
import { ColorFilter_serializer, ResourceColor, ColorFilter, ResourceStr, EdgeWidths, EdgeWidths_serializer } from "./units"
import { drawing_ColorFilter_serializer, drawing, drawing_Lattice_serializer } from "./ohos.graphics.drawing"
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Color, ImageFit, ImageRepeat, CopyOptions } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { BusinessError, BusinessError_serializer } from "./ohos.base"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ColorContentInternal {
    public static fromPtr(ptr: KPointer): ColorContent {
        return new ColorContent(ptr)
    }
}
export class ColorContent implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static get ORIGIN(): ColorContent {
        return ColorContent.getORIGIN()
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorContent.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ColorContent_ctor()
        return retval
    }
    constructor() {
        this(ColorContent.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorContent_getFinalizer()
    }
    private static getORIGIN(): ColorContent {
        return ColorContent.getORIGIN_serialize()
    }
    private static getORIGIN_serialize(): ColorContent {
        const retval  = ArkUIGeneratedNativeModule._ColorContent_getORIGIN()
        const obj : ColorContent = ColorContentInternal.fromPtr(retval)
        return obj
    }
}
export class ArkImagePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer  = new ArkImagePeer(_peerPtr, peerId, "Image", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptions0Attribute(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isimage_PixelMap(src, false, false)) {
            thisSerializer.writeInt8(0)
            const src_0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1)
                const src_1_1  = src_1 as Resource
                Resource_serializer.write(thisSerializer, src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2)
            const src_2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, src_2)
        }
        else if (TypeChecker.isImageContent(src)) {
            thisSerializer.writeInt8(3)
            const src_3  = src as ImageContent
            thisSerializer.writeInt32(TypeChecker.ImageContent_ToNumeric(src_3))
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions1Attribute(src: image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isimage_PixelMap(src, false, false)) {
            thisSerializer.writeInt8(0)
            const src_0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1)
                const src_1_1  = src_1 as Resource
                Resource_serializer.write(thisSerializer, src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2)
            const src_2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, src_2)
        }
        ImageAIOptions_serializer.write(thisSerializer, imageAIOptions)
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: string | Resource | image.PixelMap | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isimage_PixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_alt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    matchTextDirectionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_matchTextDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fitOriginalSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fitOriginalSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillColorAttribute(value: ResourceColor | ColorContent | ColorMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3)
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isColorContent(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as ColorContent
                ColorContent_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isColorMetrics(value_value)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as ColorMetrics
                ColorMetrics_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_objectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    imageMatrixAttribute(value: matrix4.Matrix4Transit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            matrix4_Matrix4Transit_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_imageMatrix(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectRepeatAttribute(value: ImageRepeat | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRepeat)
            thisSerializer.writeInt32(TypeChecker.ImageRepeat_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_objectRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoResizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_autoResize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderModeAttribute(value: ImageRenderMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRenderMode)
            thisSerializer.writeInt32(TypeChecker.ImageRenderMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_renderMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dynamicRangeModeAttribute(value: DynamicRangeMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as DynamicRangeMode)
            thisSerializer.writeInt32(TypeChecker.DynamicRangeMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_dynamicRangeMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    interpolationAttribute(value: ImageInterpolation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageInterpolation)
            thisSerializer.writeInt32(TypeChecker.ImageInterpolation_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_interpolation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sourceSizeAttribute(value: ImageSourceSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ImageSourceSize_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_sourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    syncLoadAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_syncLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorFilterAttribute(value: ColorFilter | drawing.ColorFilter | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColorFilter(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ColorFilter
                ColorFilter_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isdrawing_ColorFilter(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as drawing.ColorFilter
                drawing_ColorFilter_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_copyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    draggableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_draggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            PointLightStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAntialiasingAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_edgeAntialiasing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: ImageOnCompleteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_enableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ImageAnalyzerConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    resizableAttribute(value: ResizableOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ResizableOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_resizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enhancedImageQualityAttribute(value: image.ResolutionQuality | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as image.ResolutionQuality)
            thisSerializer.writeInt32(TypeChecker.image_ResolutionQuality_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_enhancedImageQuality(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    orientationAttribute(value: ImageRotateOrientation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageRotateOrientation)
            thisSerializer.writeInt32(TypeChecker.ImageRotateOrientation_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageAttribute_orientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type DrawingColorFilter = drawing.ColorFilter;
export type ResolutionQuality = image.ResolutionQuality;
export type DrawingLattice = drawing.Lattice;
export type ImageMatrix = matrix4.Matrix4Transit;
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
    LEFT = 4,
    UP_MIRRORED = 5,
    RIGHT_MIRRORED = 6,
    DOWN_MIRRORED = 7,
    LEFT_MIRRORED = 8
}
export interface ImageCompleteEvent {
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
export interface ImageSourceSize {
    width: number;
    height: number;
}
export interface ImageAttribute extends CommonMethod {
    alt(value: string | Resource | image.PixelMap | undefined): this
    matchTextDirection(value: boolean | undefined): this
    fitOriginalSize(value: boolean | undefined): this
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this
    objectFit(value: ImageFit | undefined): this
    imageMatrix(value: matrix4.Matrix4Transit | undefined): this
    objectRepeat(value: ImageRepeat | undefined): this
    autoResize(value: boolean | undefined): this
    renderMode(value: ImageRenderMode | undefined): this
    dynamicRangeMode(value: DynamicRangeMode | undefined): this
    interpolation(value: ImageInterpolation | undefined): this
    sourceSize(value: ImageSourceSize | undefined): this
    syncLoad(value: boolean | undefined): this
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this
    copyOption(value: CopyOptions | undefined): this
    draggable(value: boolean | undefined): this
    pointLight(value: PointLightStyle | undefined): this
    edgeAntialiasing(value: number | undefined): this
    onComplete(value: ImageOnCompleteCallback | undefined): this
    onError(value: ImageErrorCallback | undefined): this
    onFinish(value: (() => void) | undefined): this
    enableAnalyzer(value: boolean | undefined): this
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this
    resizable(value: ResizableOptions | undefined): this
    privacySensitive(value: boolean | undefined): this
    enhancedImageQuality(value: image.ResolutionQuality | undefined): this
    orientation(value: ImageRotateOrientation | undefined): this
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkImageStyle extends ArkCommonMethodStyle implements ImageAttribute {
    alt_value?: string | Resource | image.PixelMap | undefined
    matchTextDirection_value?: boolean | undefined
    fitOriginalSize_value?: boolean | undefined
    fillColor_value?: ResourceColor | ColorContent | ColorMetrics | undefined
    objectFit_value?: ImageFit | undefined
    imageMatrix_value?: matrix4.Matrix4Transit | undefined
    objectRepeat_value?: ImageRepeat | undefined
    autoResize_value?: boolean | undefined
    renderMode_value?: ImageRenderMode | undefined
    dynamicRangeMode_value?: DynamicRangeMode | undefined
    interpolation_value?: ImageInterpolation | undefined
    sourceSize_value?: ImageSourceSize | undefined
    syncLoad_value?: boolean | undefined
    colorFilter_value?: ColorFilter | drawing.ColorFilter | undefined
    copyOption_value?: CopyOptions | undefined
    draggable_value?: boolean | undefined
    pointLight_value?: PointLightStyle | undefined
    edgeAntialiasing_value?: number | undefined
    onComplete_value?: ImageOnCompleteCallback | undefined
    onError_value?: ImageErrorCallback | undefined
    onFinish_value?: (() => void) | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    resizable_value?: ResizableOptions | undefined
    privacySensitive_value?: boolean | undefined
    enhancedImageQuality_value?: image.ResolutionQuality | undefined
    orientation_value?: ImageRotateOrientation | undefined
    attributeModifier_value?: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined
    public alt(value: string | Resource | image.PixelMap | undefined): this {
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        return this
    }
    public fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        return this
    }
    public imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
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
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
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
    public onComplete(value: ImageOnCompleteCallback | undefined): this {
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
    public enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ImageAttribute): void {
        super.apply(target)
        if (this.alt_value !== undefined)
            target.alt(this.alt_value!)
        if (this.matchTextDirection_value !== undefined)
            target.matchTextDirection(this.matchTextDirection_value!)
        if (this.fitOriginalSize_value !== undefined)
            target.fitOriginalSize(this.fitOriginalSize_value!)
        if (this.fillColor_value !== undefined)
            target.fillColor(this.fillColor_value!)
        if (this.objectFit_value !== undefined)
            target.objectFit(this.objectFit_value!)
        if (this.imageMatrix_value !== undefined)
            target.imageMatrix(this.imageMatrix_value!)
        if (this.objectRepeat_value !== undefined)
            target.objectRepeat(this.objectRepeat_value!)
        if (this.autoResize_value !== undefined)
            target.autoResize(this.autoResize_value!)
        if (this.renderMode_value !== undefined)
            target.renderMode(this.renderMode_value!)
        if (this.dynamicRangeMode_value !== undefined)
            target.dynamicRangeMode(this.dynamicRangeMode_value!)
        if (this.interpolation_value !== undefined)
            target.interpolation(this.interpolation_value!)
        if (this.sourceSize_value !== undefined)
            target.sourceSize(this.sourceSize_value!)
        if (this.syncLoad_value !== undefined)
            target.syncLoad(this.syncLoad_value!)
        if (this.colorFilter_value !== undefined)
            target.colorFilter(this.colorFilter_value!)
        if (this.copyOption_value !== undefined)
            target.copyOption(this.copyOption_value!)
        if (this.draggable_value !== undefined)
            target.draggable(this.draggable_value!)
        if (this.pointLight_value !== undefined)
            target.pointLight(this.pointLight_value!)
        if (this.edgeAntialiasing_value !== undefined)
            target.edgeAntialiasing(this.edgeAntialiasing_value!)
        if (this.onComplete_value !== undefined)
            target.onComplete(this.onComplete_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
        if (this.onFinish_value !== undefined)
            target.onFinish(this.onFinish_value!)
        if (this.enableAnalyzer_value !== undefined)
            target.enableAnalyzer(this.enableAnalyzer_value!)
        if (this.analyzerConfig_value !== undefined)
            target.analyzerConfig(this.analyzerConfig_value!)
        if (this.resizable_value !== undefined)
            target.resizable(this.resizable_value!)
        if (this.privacySensitive_value !== undefined)
            target.privacySensitive(this.privacySensitive_value!)
        if (this.enhancedImageQuality_value !== undefined)
            target.enhancedImageQuality(this.enhancedImageQuality_value!)
        if (this.orientation_value !== undefined)
            target.orientation(this.orientation_value!)
    }
}
export type ImageErrorCallback = (error: ImageError) => void;
export type ImageOnCompleteCallback = (loadEvent?: ImageCompleteEvent) => void;
export interface ImageError {
    componentWidth: number;
    componentHeight: number;
    message: string;
    error?: BusinessError;
}
export interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: drawing.Lattice;
}

export class ArkImageComponent extends ArkCommonMethodComponent implements ImageAttribute {
    getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }
    public setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_type = runtimeType(src)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if (((TypeChecker.isimage_PixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src))) && (RuntimeType.OBJECT == imageAIOptions_type)) {
                const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setImageOptions1Attribute(src_casted, imageAIOptions_casted)
                return this
            }
            if (((TypeChecker.isimage_PixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src)) || (TypeChecker.isImageContent(src))) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
                this.getPeer()?.setImageOptions0Attribute(src_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public alt(value: string | Resource | image.PixelMap | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | image.PixelMap | undefined)
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
    public fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        if (this.checkPriority("fillColor")) {
            const value_casted = value as (ResourceColor | ColorContent | ColorMetrics | undefined)
            this.getPeer()?.fillColorAttribute(value_casted)
            return this
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
    public imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        if (this.checkPriority("imageMatrix")) {
            const value_casted = value as (matrix4.Matrix4Transit | undefined)
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
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | drawing.ColorFilter | undefined)
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
    public onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (ImageOnCompleteCallback | undefined)
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
    public enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (image.ResolutionQuality | undefined)
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
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withImageStyle(receiver: ImageAttribute, modifier: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkImageStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("ImageImpl")
export function Image(
    src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions?: ImageAIOptions | undefined,
    @memo
    content_?: () => void,
): ImageAttribute {
    throw new Error("Not implemented")
}

@memo
export function ImageImpl(
    @memo
    style: ((attributes: ImageAttribute) => void) | undefined,
    src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions?: ImageAIOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageComponent>((): ArkImageComponent => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer): void => {
        receiver.setImageOptions(src,imageAIOptions)
        style?.(receiver)
        withImageStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ColorContent_serializer {
    public static write(buffer: SerializerBase, value: ColorContent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ColorContent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ColorContentInternal.fromPtr(ptr)
    }
}
export class ImageCompleteEvent_serializer {
    public static write(buffer: SerializerBase, value: ImageCompleteEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
        const value_componentWidth  = value.componentWidth
        valueSerializer.writeNumber(value_componentWidth)
        const value_componentHeight  = value.componentHeight
        valueSerializer.writeNumber(value_componentHeight)
        const value_loadingStatus  = value.loadingStatus
        valueSerializer.writeNumber(value_loadingStatus)
        const value_contentWidth  = value.contentWidth
        valueSerializer.writeNumber(value_contentWidth)
        const value_contentHeight  = value.contentHeight
        valueSerializer.writeNumber(value_contentHeight)
        const value_contentOffsetX  = value.contentOffsetX
        valueSerializer.writeNumber(value_contentOffsetX)
        const value_contentOffsetY  = value.contentOffsetY
        valueSerializer.writeNumber(value_contentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageCompleteEvent {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        const componentWidth_result : number = (valueDeserializer.readNumber() as number)
        const componentHeight_result : number = (valueDeserializer.readNumber() as number)
        const loadingStatus_result : number = (valueDeserializer.readNumber() as number)
        const contentWidth_result : number = (valueDeserializer.readNumber() as number)
        const contentHeight_result : number = (valueDeserializer.readNumber() as number)
        const contentOffsetX_result : number = (valueDeserializer.readNumber() as number)
        const contentOffsetY_result : number = (valueDeserializer.readNumber() as number)
        let value : ImageCompleteEvent = ({width: width_result, height: height_result, componentWidth: componentWidth_result, componentHeight: componentHeight_result, loadingStatus: loadingStatus_result, contentWidth: contentWidth_result, contentHeight: contentHeight_result, contentOffsetX: contentOffsetX_result, contentOffsetY: contentOffsetY_result} as ImageCompleteEvent)
        return value
    }
}
export class ImageSourceSize_serializer {
    public static write(buffer: SerializerBase, value: ImageSourceSize): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
    }
    public static read(buffer: DeserializerBase): ImageSourceSize {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        let value : ImageSourceSize = ({width: width_result, height: height_result} as ImageSourceSize)
        return value
    }
}
export class ImageError_serializer {
    public static write(buffer: SerializerBase, value: ImageError): void {
        let valueSerializer : SerializerBase = buffer
        const value_componentWidth  = value.componentWidth
        valueSerializer.writeNumber(value_componentWidth)
        const value_componentHeight  = value.componentHeight
        valueSerializer.writeNumber(value_componentHeight)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_error  = value.error
        let value_error_type : int32 = RuntimeType.UNDEFINED
        value_error_type = runtimeType(value_error)
        valueSerializer.writeInt8(value_error_type)
        if ((RuntimeType.UNDEFINED) != (value_error_type)) {
            const value_error_value  = value_error!
            BusinessError_serializer.write(valueSerializer, value_error_value)
        }
    }
    public static read(buffer: DeserializerBase): ImageError {
        let valueDeserializer : DeserializerBase = buffer
        const componentWidth_result : number = (valueDeserializer.readNumber() as number)
        const componentHeight_result : number = (valueDeserializer.readNumber() as number)
        const message_result : string = (valueDeserializer.readString() as string)
        const error_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let error_buf : BusinessError | undefined
        if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
        {
            error_buf = BusinessError_serializer.read(valueDeserializer)
        }
        const error_result : BusinessError | undefined = error_buf
        let value : ImageError = ({componentWidth: componentWidth_result, componentHeight: componentHeight_result, message: message_result, error: error_result} as ImageError)
        return value
    }
}
export class ResizableOptions_serializer {
    public static write(buffer: SerializerBase, value: ResizableOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_slice  = value.slice
        let value_slice_type : int32 = RuntimeType.UNDEFINED
        value_slice_type = runtimeType(value_slice)
        valueSerializer.writeInt8(value_slice_type)
        if ((RuntimeType.UNDEFINED) != (value_slice_type)) {
            const value_slice_value  = value_slice!
            EdgeWidths_serializer.write(valueSerializer, value_slice_value)
        }
        const value_lattice  = value.lattice
        let value_lattice_type : int32 = RuntimeType.UNDEFINED
        value_lattice_type = runtimeType(value_lattice)
        valueSerializer.writeInt8(value_lattice_type)
        if ((RuntimeType.UNDEFINED) != (value_lattice_type)) {
            const value_lattice_value  = value_lattice!
            drawing_Lattice_serializer.write(valueSerializer, value_lattice_value)
        }
    }
    public static read(buffer: DeserializerBase): ResizableOptions {
        let valueDeserializer : DeserializerBase = buffer
        const slice_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let slice_buf : EdgeWidths | undefined
        if ((RuntimeType.UNDEFINED) != (slice_buf_runtimeType))
        {
            slice_buf = EdgeWidths_serializer.read(valueDeserializer)
        }
        const slice_result : EdgeWidths | undefined = slice_buf
        const lattice_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lattice_buf : drawing.Lattice | undefined
        if ((RuntimeType.UNDEFINED) != (lattice_buf_runtimeType))
        {
            lattice_buf = (drawing_Lattice_serializer.read(valueDeserializer) as drawing.Lattice)
        }
        const lattice_result : drawing.Lattice | undefined = lattice_buf
        let value : ResizableOptions = ({slice: slice_result, lattice: lattice_result} as ResizableOptions)
        return value
    }
}
