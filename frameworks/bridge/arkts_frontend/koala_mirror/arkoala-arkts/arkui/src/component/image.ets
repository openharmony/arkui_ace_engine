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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { Resource_serializer, Resource } from "./../generated/resource"
import { DrawableDescriptor_serializer, DrawableDescriptor } from "./../generated/ohos.arkui.drawableDescriptor"
import { ImageAIOptions_serializer, ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { ColorMetrics_serializer, ColorMetrics } from "./../generated/arkui.Graphics"
import { matrix4_Matrix4Transit_serializer, matrix4 } from "./../generated/ohos.matrix4"
import { ColorFilter_serializer, ResourceColor, ColorFilter, ResourceStr, EdgeWidths, EdgeWidths_serializer } from "./units"
import { drawing_ColorFilter_serializer, drawing, drawing_Lattice_serializer } from "./../generated/ohos.graphics.drawing"
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Color, ImageFit, ImageRepeat, CopyOptions } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { BusinessError, BusinessError_serializer } from "./../generated/ohos.base"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
    static readonly ORIGIN: ColorContent = ColorContent.getORIGIN()
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorContent.getFinalizer())
    }
    constructor() {
        this(ColorContent.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ColorContent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorContent_getFinalizer()
    }
    private static getORIGIN_serialize(): ColorContent {
        const retval  = ArkUIGeneratedNativeModule._ColorContent_getORIGIN()
        const obj : ColorContent = ColorContentInternal.fromPtr(retval)
        return obj
    }
    private static getORIGIN(): ColorContent {
        return ColorContent.getORIGIN_serialize()
    }
}
export class ArkImagePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer  = new ArkImagePeer(_peerPtr, peerId, 'Image', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptions0Attribute(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toChar())
            const srcForIdx0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toChar())
            const srcForIdx1  = src as ResourceStr
            if (srcForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const srcForIdx1ForIdx0  = srcForIdx1 as string
                thisSerializer.writeString(srcForIdx1ForIdx0)
            } else if (srcForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const srcForIdx1ForIdx1  = srcForIdx1 as Resource
                Resource_serializer.write(thisSerializer, srcForIdx1ForIdx1)
            }
        } else if (src instanceof DrawableDescriptor) {
            thisSerializer.writeInt8((2).toChar())
            const srcForIdx2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, srcForIdx2)
        } else if (src instanceof ImageContent) {
            thisSerializer.writeInt8((3).toChar())
            const srcForIdx3  = src as ImageContent
            thisSerializer.writeInt32(TypeChecker.ImageContent_ToNumeric(srcForIdx3))
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions1Attribute(src: image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toChar())
            const srcForIdx0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toChar())
            const srcForIdx1  = src as ResourceStr
            if (srcForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const srcForIdx1ForIdx0  = srcForIdx1 as string
                thisSerializer.writeString(srcForIdx1ForIdx0)
            } else if (srcForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const srcForIdx1ForIdx1  = srcForIdx1 as Resource
                Resource_serializer.write(thisSerializer, srcForIdx1ForIdx1)
            }
        } else if (src instanceof DrawableDescriptor) {
            thisSerializer.writeInt8((2).toChar())
            const srcForIdx2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, srcForIdx2)
        }
        ImageAIOptions_serializer.write(thisSerializer, imageAIOptions)
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAltAttribute(value: string | Resource | image.PixelMap | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAlt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMatchTextDirectionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setMatchTextDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFitOriginalSizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setFitOriginalSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillColorAttribute(value: ResourceColor | ColorContent | ColorMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceColor) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0ForIdx0))
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toChar())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof ColorContent) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as ColorContent
                ColorContent_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof ColorMetrics) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as ColorMetrics
                ColorMetrics_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setFillColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageMatrixAttribute(value: matrix4.Matrix4Transit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            matrix4_Matrix4Transit_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setImageMatrix(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectRepeatAttribute(value: ImageRepeat | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageRepeat)
            thisSerializer.writeInt32(TypeChecker.ImageRepeat_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setObjectRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoResizeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAutoResize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderModeAttribute(value: ImageRenderMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageRenderMode)
            thisSerializer.writeInt32(TypeChecker.ImageRenderMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setRenderMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDynamicRangeModeAttribute(value: DynamicRangeMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as DynamicRangeMode)
            thisSerializer.writeInt32(TypeChecker.DynamicRangeMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setDynamicRangeMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInterpolationAttribute(value: ImageInterpolation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageInterpolation)
            thisSerializer.writeInt32(TypeChecker.ImageInterpolation_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setInterpolation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSourceSizeAttribute(value: ImageSourceSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ImageSourceSize_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSyncLoadAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSyncLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorFilterAttribute(value: ColorFilter | drawing.ColorFilter | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ColorFilter) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ColorFilter
                ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof drawing.ColorFilter) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as drawing.ColorFilter
                drawing_ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setColorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDraggableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setDraggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PointLightStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeAntialiasingAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEdgeAntialiasing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: ImageOnCompleteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnalyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ImageAnalyzerConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAnalyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setResizableAttribute(value: ResizableOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ResizableOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setResizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnhancedImageQualityAttribute(value: image.ResolutionQuality | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as image.ResolutionQuality)
            thisSerializer.writeInt32(TypeChecker.image_ResolutionQuality_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEnhancedImageQuality(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOrientationAttribute(value: ImageRotateOrientation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageRotateOrientation)
            thisSerializer.writeInt32(TypeChecker.ImageRotateOrientation_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    alt(value: string | Resource | image.PixelMap | undefined): this {
        throw new Error("Unimplemented method alt")
    }
    matchTextDirection(value: boolean | undefined): this {
        throw new Error("Unimplemented method matchTextDirection")
    }
    fitOriginalSize(value: boolean | undefined): this {
        throw new Error("Unimplemented method fitOriginalSize")
    }
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        throw new Error("Unimplemented method fillColor")
    }
    objectFit(value: ImageFit | undefined): this {
        throw new Error("Unimplemented method objectFit")
    }
    imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        throw new Error("Unimplemented method imageMatrix")
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        throw new Error("Unimplemented method objectRepeat")
    }
    autoResize(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoResize")
    }
    renderMode(value: ImageRenderMode | undefined): this {
        throw new Error("Unimplemented method renderMode")
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        throw new Error("Unimplemented method dynamicRangeMode")
    }
    interpolation(value: ImageInterpolation | undefined): this {
        throw new Error("Unimplemented method interpolation")
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        throw new Error("Unimplemented method sourceSize")
    }
    syncLoad(value: boolean | undefined): this {
        throw new Error("Unimplemented method syncLoad")
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        throw new Error("Unimplemented method colorFilter")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    draggable(value: boolean | undefined): this
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    edgeAntialiasing(value: number | undefined): this {
        throw new Error("Unimplemented method edgeAntialiasing")
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        throw new Error("Unimplemented method onComplete")
    }
    onError(value: ImageErrorCallback | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    onFinish(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnalyzer")
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        throw new Error("Unimplemented method analyzerConfig")
    }
    resizable(value: ResizableOptions | undefined): this {
        throw new Error("Unimplemented method resizable")
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error("Unimplemented method privacySensitive")
    }
    enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        throw new Error("Unimplemented method enhancedImageQuality")
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        throw new Error("Unimplemented method orientation")
    }
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    public setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent): this {
        if (this.checkPriority("setImageOptions")) {
            const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
            this.getPeer()?.setImageOptions0Attribute(src_casted)
            return this
        }
        return this
    }
    public setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor)
            const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
            this.getPeer()?.setImageOptions1Attribute(src_casted, imageAIOptions_casted)
            return this
        }
        return this
    }
    public alt(value: string | Resource | image.PixelMap | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | image.PixelMap | undefined)
            this.getPeer()?.setAltAttribute(value_casted)
            return this
        }
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        if (this.checkPriority("matchTextDirection")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMatchTextDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        if (this.checkPriority("fitOriginalSize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setFitOriginalSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        if (this.checkPriority("fillColor")) {
            const value_casted = value as (ResourceColor | ColorContent | ColorMetrics | undefined)
            this.getPeer()?.setFillColorAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.setObjectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        if (this.checkPriority("imageMatrix")) {
            const value_casted = value as (matrix4.Matrix4Transit | undefined)
            this.getPeer()?.setImageMatrixAttribute(value_casted)
            return this
        }
        return this
    }
    public objectRepeat(value: ImageRepeat | undefined): this {
        if (this.checkPriority("objectRepeat")) {
            const value_casted = value as (ImageRepeat | undefined)
            this.getPeer()?.setObjectRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    public autoResize(value: boolean | undefined): this {
        if (this.checkPriority("autoResize")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoResizeAttribute(value_casted)
            return this
        }
        return this
    }
    public renderMode(value: ImageRenderMode | undefined): this {
        if (this.checkPriority("renderMode")) {
            const value_casted = value as (ImageRenderMode | undefined)
            this.getPeer()?.setRenderModeAttribute(value_casted)
            return this
        }
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (this.checkPriority("dynamicRangeMode")) {
            const value_casted = value as (DynamicRangeMode | undefined)
            this.getPeer()?.setDynamicRangeModeAttribute(value_casted)
            return this
        }
        return this
    }
    public interpolation(value: ImageInterpolation | undefined): this {
        if (this.checkPriority("interpolation")) {
            const value_casted = value as (ImageInterpolation | undefined)
            this.getPeer()?.setInterpolationAttribute(value_casted)
            return this
        }
        return this
    }
    public sourceSize(value: ImageSourceSize | undefined): this {
        if (this.checkPriority("sourceSize")) {
            const value_casted = value as (ImageSourceSize | undefined)
            this.getPeer()?.setSourceSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        if (this.checkPriority("syncLoad")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSyncLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | drawing.ColorFilter | undefined)
            this.getPeer()?.setColorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDraggableAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeAntialiasing(value: number | undefined): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setEdgeAntialiasingAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (ImageOnCompleteCallback | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig | undefined)
            this.getPeer()?.setAnalyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public resizable(value: ResizableOptions | undefined): this {
        if (this.checkPriority("resizable")) {
            const value_casted = value as (ResizableOptions | undefined)
            this.getPeer()?.setResizableAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (image.ResolutionQuality | undefined)
            this.getPeer()?.setEnhancedImageQualityAttribute(value_casted)
            return this
        }
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        if (this.checkPriority("orientation")) {
            const value_casted = value as (ImageRotateOrientation | undefined)
            this.getPeer()?.setOrientationAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Image(
    @memo
    style: ((attributes: ImageAttribute) => void) | undefined,
    src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageComponent>((): ArkImageComponent => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer): void => {
        receiver.setImageOptions(src)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}


@memo
export function Image(
    @memo
    style: ((attributes: ImageAttribute) => void) | undefined,
    src: image.PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageComponent>((): ArkImageComponent => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer): void => {
        receiver.setImageOptions(src,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ImageModifier extends CommonMethodModifier implements ImageAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alt_0_0value?: string | Resource | image.PixelMap | undefined
    _matchTextDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _matchTextDirection_0_0value?: boolean | undefined
    _fitOriginalSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fitOriginalSize_0_0value?: boolean | undefined
    _fillColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillColor_0_0value?: ResourceColor | ColorContent | ColorMetrics | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _imageMatrix_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _imageMatrix_0_0value?: matrix4.Matrix4Transit | undefined
    _objectRepeat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectRepeat_0_0value?: ImageRepeat | undefined
    _autoResize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoResize_0_0value?: boolean | undefined
    _renderMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderMode_0_0value?: ImageRenderMode | undefined
    _dynamicRangeMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dynamicRangeMode_0_0value?: DynamicRangeMode | undefined
    _interpolation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _interpolation_0_0value?: ImageInterpolation | undefined
    _sourceSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sourceSize_0_0value?: ImageSourceSize | undefined
    _syncLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _syncLoad_0_0value?: boolean | undefined
    _colorFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colorFilter_0_0value?: ColorFilter | drawing.ColorFilter | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _draggable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _draggable_0_0value?: boolean | undefined
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    _edgeAntialiasing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeAntialiasing_0_0value?: number | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: ImageOnCompleteCallback | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ImageErrorCallback | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _analyzerConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    _resizable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _resizable_0_0value?: ResizableOptions | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    _enhancedImageQuality_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enhancedImageQuality_0_0value?: image.ResolutionQuality | undefined
    _orientation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _orientation_0_0value?: ImageRotateOrientation | undefined
    applyModifierPatch(peer: ArkImagePeer): void {
        super.applyModifierPatch(peer)
        if (this._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAltAttribute((this._alt_0_0value as string | Resource | image.PixelMap | undefined));
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAltAttribute((undefined as string | Resource | image.PixelMap | undefined));
                }
            }
        }
        if (this._matchTextDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._matchTextDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMatchTextDirectionAttribute((this._matchTextDirection_0_0value as boolean | undefined));
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMatchTextDirectionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fitOriginalSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fitOriginalSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFitOriginalSizeAttribute((this._fitOriginalSize_0_0value as boolean | undefined));
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFitOriginalSizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fillColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillColorAttribute((this._fillColor_0_0value as ResourceColor | ColorContent | ColorMetrics | undefined));
                    this._fillColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillColorAttribute((undefined as ResourceColor | ColorContent | ColorMetrics | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._imageMatrix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._imageMatrix_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImageMatrixAttribute((this._imageMatrix_0_0value as matrix4.Matrix4Transit | undefined));
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImageMatrixAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (this._objectRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectRepeatAttribute((this._objectRepeat_0_0value as ImageRepeat | undefined));
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectRepeatAttribute((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (this._autoResize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoResize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoResizeAttribute((this._autoResize_0_0value as boolean | undefined));
                    this._autoResize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoResize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoResize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoResizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._renderMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderModeAttribute((this._renderMode_0_0value as ImageRenderMode | undefined));
                    this._renderMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderModeAttribute((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (this._dynamicRangeMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dynamicRangeMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDynamicRangeModeAttribute((this._dynamicRangeMode_0_0value as DynamicRangeMode | undefined));
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDynamicRangeModeAttribute((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (this._interpolation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._interpolation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInterpolationAttribute((this._interpolation_0_0value as ImageInterpolation | undefined));
                    this._interpolation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._interpolation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._interpolation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInterpolationAttribute((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (this._sourceSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sourceSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSourceSizeAttribute((this._sourceSize_0_0value as ImageSourceSize | undefined));
                    this._sourceSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sourceSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sourceSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSourceSizeAttribute((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (this._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSyncLoadAttribute((this._syncLoad_0_0value as boolean | undefined));
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSyncLoadAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | drawing.ColorFilter | undefined));
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorFilterAttribute((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (this._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._draggable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (this._edgeAntialiasing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeAntialiasing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeAntialiasingAttribute((this._edgeAntialiasing_0_0value as number | undefined));
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeAntialiasingAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageOnCompleteCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnalyzerConfigAttribute((this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnalyzerConfigAttribute((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (this._resizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._resizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setResizableAttribute((this._resizable_0_0value as ResizableOptions | undefined));
                    this._resizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._resizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._resizable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setResizableAttribute((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enhancedImageQuality_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enhancedImageQuality_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnhancedImageQualityAttribute((this._enhancedImageQuality_0_0value as image.ResolutionQuality | undefined));
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnhancedImageQualityAttribute((undefined as image.ResolutionQuality | undefined));
                }
            }
        }
        if (this._orientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._orientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOrientationAttribute((this._orientation_0_0value as ImageRotateOrientation | undefined));
                    this._orientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._orientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._orientation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOrientationAttribute((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as string | Resource | image.PixelMap | undefined));
                }
            }
        }
        if (modifier._matchTextDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._matchTextDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.matchTextDirection(modifier._matchTextDirection_0_0value);
                    break;
                }
                default: {
                    this.matchTextDirection((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fitOriginalSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fitOriginalSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fitOriginalSize(modifier._fitOriginalSize_0_0value);
                    break;
                }
                default: {
                    this.fitOriginalSize((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fillColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillColor(modifier._fillColor_0_0value);
                    break;
                }
                default: {
                    this.fillColor((undefined as ResourceColor | ColorContent | ColorMetrics | undefined));
                }
            }
        }
        if (modifier._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (modifier._imageMatrix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._imageMatrix_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.imageMatrix(modifier._imageMatrix_0_0value);
                    break;
                }
                default: {
                    this.imageMatrix((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (modifier._objectRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectRepeat(modifier._objectRepeat_0_0value);
                    break;
                }
                default: {
                    this.objectRepeat((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (modifier._autoResize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoResize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoResize(modifier._autoResize_0_0value);
                    break;
                }
                default: {
                    this.autoResize((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._renderMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderMode(modifier._renderMode_0_0value);
                    break;
                }
                default: {
                    this.renderMode((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (modifier._dynamicRangeMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dynamicRangeMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dynamicRangeMode(modifier._dynamicRangeMode_0_0value);
                    break;
                }
                default: {
                    this.dynamicRangeMode((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (modifier._interpolation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._interpolation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.interpolation(modifier._interpolation_0_0value);
                    break;
                }
                default: {
                    this.interpolation((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (modifier._sourceSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sourceSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sourceSize(modifier._sourceSize_0_0value);
                    break;
                }
                default: {
                    this.sourceSize((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (modifier._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.syncLoad(modifier._syncLoad_0_0value);
                    break;
                }
                default: {
                    this.syncLoad((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (modifier._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (modifier._edgeAntialiasing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeAntialiasing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeAntialiasing(modifier._edgeAntialiasing_0_0value);
                    break;
                }
                default: {
                    this.edgeAntialiasing((undefined as number | undefined));
                }
            }
        }
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.analyzerConfig(modifier._analyzerConfig_0_0value);
                    break;
                }
                default: {
                    this.analyzerConfig((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (modifier._resizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._resizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.resizable(modifier._resizable_0_0value);
                    break;
                }
                default: {
                    this.resizable((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enhancedImageQuality_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enhancedImageQuality_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enhancedImageQuality(modifier._enhancedImageQuality_0_0value);
                    break;
                }
                default: {
                    this.enhancedImageQuality((undefined as image.ResolutionQuality | undefined));
                }
            }
        }
        if (modifier._orientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._orientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.orientation(modifier._orientation_0_0value);
                    break;
                }
                default: {
                    this.orientation((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    alt(value: string | Resource | image.PixelMap | undefined): this {
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else
        {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    matchTextDirection(value: boolean | undefined): this {
        if (((this._matchTextDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._matchTextDirection_0_0value) !== (value)))
        {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._matchTextDirection_0_0value = value
        } else
        {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fitOriginalSize(value: boolean | undefined): this {
        if (((this._fitOriginalSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fitOriginalSize_0_0value) !== (value)))
        {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fitOriginalSize_0_0value = value
        } else
        {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        if (((this._fillColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillColor_0_0value = value
        } else
        {
            this._fillColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._imageMatrix_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.UPDATE
            this._imageMatrix_0_0value = value
        } else
        {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        if (((this._objectRepeat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectRepeat_0_0value = value
        } else
        {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoResize(value: boolean | undefined): this {
        if (((this._autoResize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoResize_0_0value) !== (value)))
        {
            this._autoResize_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoResize_0_0value = value
        } else
        {
            this._autoResize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderMode(value: ImageRenderMode | undefined): this {
        if (((this._renderMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderMode_0_0value = value
        } else
        {
            this._renderMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (((this._dynamicRangeMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._dynamicRangeMode_0_0value = value
        } else
        {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    interpolation(value: ImageInterpolation | undefined): this {
        if (((this._interpolation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._interpolation_0_flag = AttributeUpdaterFlag.UPDATE
            this._interpolation_0_0value = value
        } else
        {
            this._interpolation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        if (((this._sourceSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sourceSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._sourceSize_0_0value = value
        } else
        {
            this._sourceSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    syncLoad(value: boolean | undefined): this {
        if (((this._syncLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._syncLoad_0_0value) !== (value)))
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._syncLoad_0_0value = value
        } else
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorFilter_0_0value = value
        } else
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
        } else
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._draggable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable_0_0value) !== (value)))
        {
            this._draggable_0_flag = AttributeUpdaterFlag.UPDATE
            this._draggable_0_0value = value
        } else
        {
            this._draggable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeAntialiasing(value: number | undefined): this {
        if (((this._edgeAntialiasing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._edgeAntialiasing_0_0value) !== (value)))
        {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeAntialiasing_0_0value = value
        } else
        {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._analyzerConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._analyzerConfig_0_0value = value
        } else
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    resizable(value: ResizableOptions | undefined): this {
        if (((this._resizable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._resizable_0_flag = AttributeUpdaterFlag.UPDATE
            this._resizable_0_0value = value
        } else
        {
            this._resizable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        if (((this._enhancedImageQuality_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.UPDATE
            this._enhancedImageQuality_0_0value = value
        } else
        {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        if (((this._orientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._orientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._orientation_0_0value = value
        } else
        {
            this._orientation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeNumber(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeNumber(valueHolderForComponentHeight)
        const valueHolderForLoadingStatus  = value.loadingStatus
        valueSerializer.writeNumber(valueHolderForLoadingStatus)
        const valueHolderForContentWidth  = value.contentWidth
        valueSerializer.writeNumber(valueHolderForContentWidth)
        const valueHolderForContentHeight  = value.contentHeight
        valueSerializer.writeNumber(valueHolderForContentHeight)
        const valueHolderForContentOffsetX  = value.contentOffsetX
        valueSerializer.writeNumber(valueHolderForContentOffsetX)
        const valueHolderForContentOffsetY  = value.contentOffsetY
        valueSerializer.writeNumber(valueHolderForContentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageCompleteEvent {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        const componentWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const componentHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const loadingStatusTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentOffsetXTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentOffsetYTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ImageCompleteEvent = ({width: widthTmpResult, height: heightTmpResult, componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, loadingStatus: loadingStatusTmpResult, contentWidth: contentWidthTmpResult, contentHeight: contentHeightTmpResult, contentOffsetX: contentOffsetXTmpResult, contentOffsetY: contentOffsetYTmpResult} as ImageCompleteEvent)
        return value
    }
}
export class ImageSourceSize_serializer {
    public static write(buffer: SerializerBase, value: ImageSourceSize): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): ImageSourceSize {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ImageSourceSize = ({width: widthTmpResult, height: heightTmpResult} as ImageSourceSize)
        return value
    }
}
export class ImageError_serializer {
    public static write(buffer: SerializerBase, value: ImageError): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeNumber(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeNumber(valueHolderForComponentHeight)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForError  = value.error
        if (valueHolderForError !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForErrorTmpValue  = valueHolderForError!
            BusinessError_serializer.write(valueSerializer, valueHolderForErrorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageError {
        let valueDeserializer : DeserializerBase = buffer
        const componentWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const componentHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const errorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let errorTmpBuf : BusinessError | undefined
        if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            errorTmpBuf = BusinessError_serializer.read(valueDeserializer)
        }
        const errorTmpResult : BusinessError | undefined = errorTmpBuf
        let value : ImageError = ({componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, message: messageTmpResult, error: errorTmpResult} as ImageError)
        return value
    }
}
export class ResizableOptions_serializer {
    public static write(buffer: SerializerBase, value: ResizableOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSlice  = value.slice
        if (valueHolderForSlice !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSliceTmpValue  = valueHolderForSlice!
            EdgeWidths_serializer.write(valueSerializer, valueHolderForSliceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLattice  = value.lattice
        if (valueHolderForLattice !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLatticeTmpValue  = valueHolderForLattice!
            drawing_Lattice_serializer.write(valueSerializer, valueHolderForLatticeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ResizableOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sliceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sliceTmpBuf : EdgeWidths | undefined
        if ((sliceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sliceTmpBuf = EdgeWidths_serializer.read(valueDeserializer)
        }
        const sliceTmpResult : EdgeWidths | undefined = sliceTmpBuf
        const latticeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let latticeTmpBuf : drawing.Lattice | undefined
        if ((latticeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            latticeTmpBuf = (drawing_Lattice_serializer.read(valueDeserializer) as drawing.Lattice)
        }
        const latticeTmpResult : drawing.Lattice | undefined = latticeTmpBuf
        let value : ResizableOptions = ({slice: sliceTmpResult, lattice: latticeTmpResult} as ResizableOptions)
        return value
    }
}
