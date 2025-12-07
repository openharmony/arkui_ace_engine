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
import { ArkThemeScopeManager } from "#arktheme"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { Resource_serializer } from "./../framework/resource"
import { DrawableDescriptor_serializer } from "./../framework/ohos.arkui.drawableDescriptor"
import { ImageAIOptions_serializer, ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { ColorMetrics_serializer } from "./../Graphics"
import { matrix4_Matrix4Transit_serializer } from "./../framework/ohos.matrix4"
import { ColorFilter_serializer, ResourceColor, ColorFilter, ResourceStr, EdgeWidths, EdgeWidths_serializer } from "./units"
import { drawing_ColorFilter_serializer, drawing_Lattice_serializer } from "./../framework/ohos.graphics.drawing"
import { PointLightStyle_serializer, ContentTransitionEffect_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ContentTransitionEffect, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Resource } from "global.resource"
import { extractors, AttributeModifier, hookImageAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { default as image } from "@ohos.multimedia.image"
import { Color, ImageFit, ImageRepeat, CopyOptions } from "./enums"
import { ColorMetrics } from "arkui.Graphics"
import { default as matrix4 } from "@ohos.matrix4"
import { default as drawing } from "@ohos.graphics.drawing"
import { DrawableDescriptor } from "@ohos.arkui.drawableDescriptor"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { BusinessError } from "@ohos.base"
import { ImageModifier } from "./../ImageModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { BusinessError_serializer } from "./../framework/ohos.base"
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
    attributeSet?: ImageModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer  = new ArkImagePeer(_peerPtr, peerId, 'Image', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptionsAttribute(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toByte())
            const srcForIdx0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toByte())
            const srcForIdx1  = src as ResourceStr
            if (srcForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const srcForIdx1ForIdx0  = srcForIdx1 as string
                thisSerializer.writeString(srcForIdx1ForIdx0)
            } else if (srcForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const srcForIdx1ForIdx1  = srcForIdx1 as Resource
                Resource_serializer.write(thisSerializer, srcForIdx1ForIdx1)
            }
        } else if (src instanceof DrawableDescriptor) {
            thisSerializer.writeInt8((2).toByte())
            const srcForIdx2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, srcForIdx2)
        } else if (src instanceof ImageContent) {
            thisSerializer.writeInt8((3).toByte())
            const srcForIdx3  = src as ImageContent
            thisSerializer.writeInt32(srcForIdx3.valueOf())
        } else if (src === undefined) {
            thisSerializer.writeInt8((3).toByte())
            const srcForIdx3  = ImageContent.EMPTY
            thisSerializer.writeInt32(srcForIdx3.valueOf())
        }
        if (imageAIOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const imageAIOptionsTmpValue  = imageAIOptions!
            ImageAIOptions_serializer.write(thisSerializer, imageAIOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAltAttribute(value: string | Resource | image.PixelMap | ImageAlt | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof ImageAlt) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as ImageAlt
                ImageAlt_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueTmpValueForIdx0 instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as int32
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof ColorContent) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as ColorContent
                ColorContent_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof ColorMetrics) {
                thisSerializer.writeInt8((2).toByte())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ColorFilter
                ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof drawing.ColorFilter) {
                thisSerializer.writeInt8((1).toByte())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setEdgeAntialiasingAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportSvg2Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSupportSvg2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentTransitionAttribute(value: ContentTransitionEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ContentTransitionEffect_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    width: int32;
    height: int32;
    componentWidth: int32;
    componentHeight: int32;
    loadingStatus: int32;
    contentWidth: int32;
    contentHeight: int32;
    contentOffsetX: int32;
    contentOffsetY: int32;
}
export interface ImageSourceSize {
    width: double;
    height: double;
}
export interface ImageAlt {
    placeholder?: ResourceStr | image.PixelMap;
    error?: ResourceStr | image.PixelMap;
}
export interface ImageAttribute extends CommonMethod {
    setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): this {
        throw new Error("Unimplemented method setImageOptions")
    }
    alt(value: string | Resource | image.PixelMap | ImageAlt | undefined): this {
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
    edgeAntialiasing(value: double | undefined): this {
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
    supportSvg2(value: boolean | undefined): this {
        throw new Error("Unimplemented method supportSvg2")
    }
    contentTransition(value: ContentTransitionEffect | undefined): this {
        throw new Error("Unimplemented method contentTransition")
    }
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkImageStyle extends ArkCommonMethodStyle implements ImageAttribute {
    alt_value?: string | Resource | image.PixelMap | ImageAlt | undefined
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
    edgeAntialiasing_value?: double | undefined
    onComplete_value?: ImageOnCompleteCallback | undefined
    onError_value?: ImageErrorCallback | undefined
    onFinish_value?: (() => void) | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    resizable_value?: ResizableOptions | undefined
    privacySensitive_value?: boolean | undefined
    enhancedImageQuality_value?: image.ResolutionQuality | undefined
    orientation_value?: ImageRotateOrientation | undefined
    supportSvg2_value?: boolean | undefined
    contentTransition_value?: ContentTransitionEffect | undefined
    attributeModifier_value?: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined
    setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): this {
        return this
    }
    alt(value: string | Resource | image.PixelMap | ImageAlt | undefined): this {
        return this
    }
    matchTextDirection(value: boolean | undefined): this {
        return this
    }
    fitOriginalSize(value: boolean | undefined): this {
        return this
    }
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        return this
    }
    imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        return this
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        return this
    }
    autoResize(value: boolean | undefined): this {
        return this
    }
    renderMode(value: ImageRenderMode | undefined): this {
        return this
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        return this
    }
    interpolation(value: ImageInterpolation | undefined): this {
        return this
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        return this
    }
    syncLoad(value: boolean | undefined): this {
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        return this
    }
    draggable(value: boolean | undefined): this {
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    edgeAntialiasing(value: double | undefined): this {
        return this
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        return this
    }
    resizable(value: ResizableOptions | undefined): this {
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        return this
    }
    enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        return this
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        return this
    }
    supportSvg2(value: boolean | undefined): this {
        return this
    }
    contentTransition(value: ContentTransitionEffect | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type ImageErrorCallback = (error: ImageError) => void;
export type ImageOnCompleteCallback = (loadEvent?: ImageCompleteEvent) => void;
export interface ImageError {
    componentWidth: int32;
    componentHeight: int32;
    message: string;
    error?: BusinessError;
}
export interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: drawing.Lattice;
}

export class ArkImageComponent extends ArkCommonMethodComponent implements ImageAttribute {
    getPeer(): ArkImagePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkImagePeer)
    }
    public setImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined)
            const imageAIOptions_casted = imageAIOptions as (ImageAIOptions | undefined)
            this.getPeer()?.setImageOptionsAttribute(src_casted, imageAIOptions_casted)
            this.applyOptionsFinish('ImageAttribute');
            return this
        }
        return this
    }
    public alt(value: string | Resource | image.PixelMap | ImageAlt | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | image.PixelMap | ImageAlt | undefined)
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
    public edgeAntialiasing(value: double | undefined): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (double | undefined)
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
    public supportSvg2(value: boolean | undefined): this {
        if (this.checkPriority("supportSvg2")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSupportSvg2Attribute(value_casted)
            return this
        }
        return this
    }
    public contentTransition(value: ContentTransitionEffect | undefined): this {
        if (this.checkPriority("contentTransition")) {
            const value_casted = value as (ContentTransitionEffect | undefined)
            this.getPeer()?.setContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookImageAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ImageImpl(
    @memo
    style: ((attributes: ImageAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageComponent>((): ArkImageComponent => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (peer: ArkImagePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
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
export class ImageSourceSize_serializer {
    public static write(buffer: SerializerBase, value: ImageSourceSize): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): ImageSourceSize {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        let value : ImageSourceSize = ({width: widthTmpResult, height: heightTmpResult} as ImageSourceSize)
        return value
    }
}
export class ImageCompleteEvent_serializer {
    public static write(buffer: SerializerBase, value: ImageCompleteEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeInt32(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeInt32(valueHolderForHeight)
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeInt32(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeInt32(valueHolderForComponentHeight)
        const valueHolderForLoadingStatus  = value.loadingStatus
        valueSerializer.writeInt32(valueHolderForLoadingStatus)
        const valueHolderForContentWidth  = value.contentWidth
        valueSerializer.writeInt32(valueHolderForContentWidth)
        const valueHolderForContentHeight  = value.contentHeight
        valueSerializer.writeInt32(valueHolderForContentHeight)
        const valueHolderForContentOffsetX  = value.contentOffsetX
        valueSerializer.writeInt32(valueHolderForContentOffsetX)
        const valueHolderForContentOffsetY  = value.contentOffsetY
        valueSerializer.writeInt32(valueHolderForContentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageCompleteEvent {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : int32 = valueDeserializer.readInt32()
        const heightTmpResult : int32 = valueDeserializer.readInt32()
        const componentWidthTmpResult : int32 = valueDeserializer.readInt32()
        const componentHeightTmpResult : int32 = valueDeserializer.readInt32()
        const loadingStatusTmpResult : int32 = valueDeserializer.readInt32()
        const contentWidthTmpResult : int32 = valueDeserializer.readInt32()
        const contentHeightTmpResult : int32 = valueDeserializer.readInt32()
        const contentOffsetXTmpResult : int32 = valueDeserializer.readInt32()
        const contentOffsetYTmpResult : int32 = valueDeserializer.readInt32()
        let value : ImageCompleteEvent = ({width: widthTmpResult, height: heightTmpResult, componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, loadingStatus: loadingStatusTmpResult, contentWidth: contentWidthTmpResult, contentHeight: contentHeightTmpResult, contentOffsetX: contentOffsetXTmpResult, contentOffsetY: contentOffsetYTmpResult} as ImageCompleteEvent)
        return value
    }
}
export class ImageAlt_serializer {
    public static write(buffer: SerializerBase, value: ImageAlt): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPlaceholder  = value.placeholder
        if (valueHolderForPlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlaceholderTmpValue  = valueHolderForPlaceholder!
            if (valueHolderForPlaceholderTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPlaceholderTmpValueForIdx0  = valueHolderForPlaceholderTmpValue as ResourceStr
                if (valueHolderForPlaceholderTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForPlaceholderTmpValueForIdx0ForIdx0  = valueHolderForPlaceholderTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForPlaceholderTmpValueForIdx0ForIdx0)
                } else if (valueHolderForPlaceholderTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForPlaceholderTmpValueForIdx0ForIdx1  = valueHolderForPlaceholderTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForPlaceholderTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPlaceholderTmpValueForIdx1  = valueHolderForPlaceholderTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForError  = value.error
        if (valueHolderForError !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForErrorTmpValue  = valueHolderForError!
            if (valueHolderForErrorTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForErrorTmpValueForIdx0  = valueHolderForErrorTmpValue as ResourceStr
                if (valueHolderForErrorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForErrorTmpValueForIdx0ForIdx0  = valueHolderForErrorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForErrorTmpValueForIdx0ForIdx0)
                } else if (valueHolderForErrorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForErrorTmpValueForIdx0ForIdx1  = valueHolderForErrorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForErrorTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForErrorTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForErrorTmpValueForIdx1  = valueHolderForErrorTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForErrorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageAlt {
        let valueDeserializer : DeserializerBase = buffer
        const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholderTmpBuf : ResourceStr | image.PixelMap | undefined = undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const placeholderTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let placeholderTmpBuf_ : ResourceStr | image.PixelMap | undefined
            if (placeholderTmpBuf_UnionSelector == (0).toChar()) {
                const placeholderTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let placeholderTmpBuf_BufU : string | Resource | undefined
                if (placeholderTmpBuf_BufUUnionSelector == (0).toChar()) {
                    placeholderTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (placeholderTmpBuf_BufUUnionSelector == (1).toChar()) {
                    placeholderTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for placeholderTmpBuf_BufU has to be chosen through deserialisation.")
                }
                placeholderTmpBuf_ = (placeholderTmpBuf_BufU as string | Resource)
            } else if (placeholderTmpBuf_UnionSelector == (1).toChar()) {
                placeholderTmpBuf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else {
                throw new Error("One of the branches for placeholderTmpBuf_ has to be chosen through deserialisation.")
            }
            placeholderTmpBuf = (placeholderTmpBuf_ as ResourceStr | image.PixelMap)
        }
        const placeholderTmpResult : ResourceStr | image.PixelMap | undefined = placeholderTmpBuf
        const errorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let errorTmpBuf : ResourceStr | image.PixelMap | undefined = undefined
        if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const errorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let errorTmpBuf_ : ResourceStr | image.PixelMap | undefined
            if (errorTmpBuf_UnionSelector == (0).toChar()) {
                const errorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let errorTmpBuf_BufU : string | Resource | undefined
                if (errorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    errorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (errorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    errorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for errorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                errorTmpBuf_ = (errorTmpBuf_BufU as string | Resource)
            } else if (errorTmpBuf_UnionSelector == (1).toChar()) {
                errorTmpBuf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else {
                throw new Error("One of the branches for errorTmpBuf_ has to be chosen through deserialisation.")
            }
            errorTmpBuf = (errorTmpBuf_ as ResourceStr | image.PixelMap)
        }
        const errorTmpResult : ResourceStr | image.PixelMap | undefined = errorTmpBuf
        let value : ImageAlt = ({placeholder: placeholderTmpResult, error: errorTmpResult} as ImageAlt)
        return value
    }
}
export class ImageError_serializer {
    public static write(buffer: SerializerBase, value: ImageError): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeInt32(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeInt32(valueHolderForComponentHeight)
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
        const componentWidthTmpResult : int32 = valueDeserializer.readInt32()
        const componentHeightTmpResult : int32 = valueDeserializer.readInt32()
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const errorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let errorTmpBuf : BusinessError | undefined = undefined
        if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            errorTmpBuf = (BusinessError_serializer.read(valueDeserializer) as BusinessError)
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
        let sliceTmpBuf : EdgeWidths | undefined = undefined
        if ((sliceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sliceTmpBuf = EdgeWidths_serializer.read(valueDeserializer)
        }
        const sliceTmpResult : EdgeWidths | undefined = sliceTmpBuf
        const latticeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let latticeTmpBuf : drawing.Lattice | undefined = undefined
        if ((latticeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            latticeTmpBuf = (drawing_Lattice_serializer.read(valueDeserializer) as drawing.Lattice)
        }
        const latticeTmpResult : drawing.Lattice | undefined = latticeTmpBuf
        let value : ResizableOptions = ({slice: sliceTmpResult, lattice: latticeTmpResult} as ResizableOptions)
        return value
    }
}
