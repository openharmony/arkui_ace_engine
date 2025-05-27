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
import { ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Resource } from "./resource"
import { PixelMap } from "./arkui-pixelmap"
import { ResourceColor, ColorFilter, ResourceStr, EdgeWidths } from "./units"
import { ImageFit, ImageRepeat, CopyOptions, Color } from "./enums"
import { DrawingColorFilter, DrawingLattice } from "./arkui-drawing"
import { Callback_Void } from "./ability_component"
import { ImageAnalyzerConfig, ImageAIOptions } from "./image_common"
import { ResolutionQuality } from "./arkui-external"
import { DrawableDescriptor } from "./arkui-drawabledescriptor"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    altAttribute(value: string | Resource | PixelMap): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isResource(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as PixelMap
            thisSerializer.writePixelMap(value_2)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_alt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    matchTextDirectionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_matchTextDirection(this.peer.ptr, value ? 1 : 0)
    }
    fitOriginalSizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_fitOriginalSize(this.peer.ptr, value ? 1 : 0)
    }
    fillColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectFit(this.peer.ptr, TypeChecker.ImageFit_ToNumeric(value))
    }
    objectRepeatAttribute(value: ImageRepeat): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectRepeat(this.peer.ptr, TypeChecker.ImageRepeat_ToNumeric(value))
    }
    autoResizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_autoResize(this.peer.ptr, value ? 1 : 0)
    }
    renderModeAttribute(value: ImageRenderMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_renderMode(this.peer.ptr, TypeChecker.ImageRenderMode_ToNumeric(value))
    }
    dynamicRangeModeAttribute(value: DynamicRangeMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_dynamicRangeMode(this.peer.ptr, TypeChecker.DynamicRangeMode_ToNumeric(value))
    }
    interpolationAttribute(value: ImageInterpolation): void {
        ArkUIGeneratedNativeModule._ImageAttribute_interpolation(this.peer.ptr, TypeChecker.ImageInterpolation_ToNumeric(value))
    }
    sourceSizeAttribute(value: ImageSourceSize): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageSourceSize(value)
        ArkUIGeneratedNativeModule._ImageAttribute_sourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    syncLoadAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_syncLoad(this.peer.ptr, value ? 1 : 0)
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColorFilter(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ColorFilter
            thisSerializer.writeColorFilter(value_0)
        }
        else if (TypeChecker.isDrawingColorFilter(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as DrawingColorFilter
            thisSerializer.writeDrawingColorFilter(value_1)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._ImageAttribute_copyOption(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_draggable(this.peer.ptr, value ? 1 : 0)
    }
    pointLightAttribute(value: PointLightStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePointLightStyle(value)
        ArkUIGeneratedNativeModule._ImageAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAntialiasingAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAttribute_edgeAntialiasing(this.peer.ptr, value)
    }
    onCompleteAttribute(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_enableAnalyzer(this.peer.ptr, value ? 1 : 0)
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(value)
        ArkUIGeneratedNativeModule._ImageAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    resizableAttribute(value: ResizableOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResizableOptions(value)
        ArkUIGeneratedNativeModule._ImageAttribute_resizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_privacySensitive(this.peer.ptr, value ? 1 : 0)
    }
    enhancedImageQualityAttribute(value: ResolutionQuality): void {
        ArkUIGeneratedNativeModule._ImageAttribute_enhancedImageQuality(this.peer.ptr, TypeChecker.ResolutionQuality_ToNumeric(value))
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

export interface ImageSourceSize {
    width: number;
    height: number;
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
    alt(value: string | Resource | PixelMap): this
    matchTextDirection(value: boolean): this
    fitOriginalSize(value: boolean): this
    fillColor(value: ResourceColor): this
    objectFit(value: ImageFit): this
    objectRepeat(value: ImageRepeat): this
    autoResize(value: boolean): this
    renderMode(value: ImageRenderMode): this
    dynamicRangeMode(value: DynamicRangeMode): this
    interpolation(value: ImageInterpolation): this
    sourceSize(value: ImageSourceSize): this
    syncLoad(value: boolean): this
    colorFilter(value: ColorFilter | DrawingColorFilter): this
    copyOption(value: CopyOptions): this
    draggable(value: boolean): this
    pointLight(value: PointLightStyle): this
    edgeAntialiasing(value: number): this
    onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this
    onError(value: ImageErrorCallback): this
    onFinish(value: (() => void)): this
    enableAnalyzer(value: boolean): this
    analyzerConfig(value: ImageAnalyzerConfig): this
    resizable(value: ResizableOptions): this
    privacySensitive(value: boolean): this
    enhancedImageQuality(value: ResolutionQuality): this
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIImageAttribute extends UICommonMethod {
    /** @memo */
    alt(value: string | Resource | PixelMap): this
    /** @memo */
    matchTextDirection(value: boolean): this
    /** @memo */
    fitOriginalSize(value: boolean): this
    /** @memo */
    fillColor(value: ResourceColor): this
    /** @memo */
    objectFit(value: ImageFit): this
    /** @memo */
    objectRepeat(value: ImageRepeat): this
    /** @memo */
    autoResize(value: boolean): this
    /** @memo */
    renderMode(value: ImageRenderMode): this
    /** @memo */
    dynamicRangeMode(value: DynamicRangeMode): this
    /** @memo */
    interpolation(value: ImageInterpolation): this
    /** @memo */
    sourceSize(value: ImageSourceSize): this
    /** @memo */
    syncLoad(value: boolean): this
    /** @memo */
    colorFilter(value: ColorFilter | DrawingColorFilter): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    draggable(value: boolean): this
    /** @memo */
    pointLight(value: PointLightStyle): this
    /** @memo */
    edgeAntialiasing(value: number): this
    /** @memo */
    onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this
    /** @memo */
    onError(value: ImageErrorCallback): this
    /** @memo */
    onFinish(value: (() => void)): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    analyzerConfig(value: ImageAnalyzerConfig): this
    /** @memo */
    resizable(value: ResizableOptions): this
    /** @memo */
    privacySensitive(value: boolean): this
    /** @memo */
    enhancedImageQuality(value: ResolutionQuality): this
    /** @memo */
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkImageStyle extends ArkCommonMethodStyle implements ImageAttribute {
    alt_value?: string | Resource | PixelMap
    matchTextDirection_value?: boolean
    fitOriginalSize_value?: boolean
    fillColor_value?: ResourceColor
    objectFit_value?: ImageFit
    objectRepeat_value?: ImageRepeat
    autoResize_value?: boolean
    renderMode_value?: ImageRenderMode
    dynamicRangeMode_value?: DynamicRangeMode
    interpolation_value?: ImageInterpolation
    sourceSize_value?: ImageSourceSize
    syncLoad_value?: boolean
    colorFilter_value?: ColorFilter | DrawingColorFilter
    copyOption_value?: CopyOptions
    draggable_value?: boolean
    pointLight_value?: PointLightStyle
    edgeAntialiasing_value?: number
    onComplete_value?: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)
    onError_value?: ImageErrorCallback
    onFinish_value?: (() => void)
    enableAnalyzer_value?: boolean
    analyzerConfig_value?: ImageAnalyzerConfig
    resizable_value?: ResizableOptions
    privacySensitive_value?: boolean
    enhancedImageQuality_value?: ResolutionQuality
    public alt(value: string | Resource | PixelMap): this {
        return this
    }
    public matchTextDirection(value: boolean): this {
        return this
    }
    public fitOriginalSize(value: boolean): this {
        return this
    }
    public fillColor(value: ResourceColor): this {
        return this
    }
    public objectFit(value: ImageFit): this {
        return this
    }
    public objectRepeat(value: ImageRepeat): this {
        return this
    }
    public autoResize(value: boolean): this {
        return this
    }
    public renderMode(value: ImageRenderMode): this {
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode): this {
        return this
    }
    public interpolation(value: ImageInterpolation): this {
        return this
    }
    public sourceSize(value: ImageSourceSize): this {
        return this
    }
    public syncLoad(value: boolean): this {
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        return this
    }
    public copyOption(value: CopyOptions): this {
        return this
    }
    public draggable(value: boolean): this {
        return this
    }
    public pointLight(value: PointLightStyle): this {
        return this
    }
    public edgeAntialiasing(value: number): this {
        return this
    }
    public onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this {
        return this
    }
    public onError(value: ImageErrorCallback): this {
        return this
    }
    public onFinish(value: (() => void)): this {
        return this
    }
    public enableAnalyzer(value: boolean): this {
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        return this
    }
    public resizable(value: ResizableOptions): this {
        return this
    }
    public privacySensitive(value: boolean): this {
        return this
    }
    public enhancedImageQuality(value: ResolutionQuality): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
/** @memo:stable */
export class ArkImageComponent extends ArkCommonMethodComponent implements UIImageAttribute {
    getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }
    /** @memo */
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
    /** @memo */
    public alt(value: string | Resource | PixelMap): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | PixelMap)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public matchTextDirection(value: boolean): this {
        if (this.checkPriority("matchTextDirection")) {
            const value_casted = value as (boolean)
            this.getPeer()?.matchTextDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fitOriginalSize(value: boolean): this {
        if (this.checkPriority("fitOriginalSize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fitOriginalSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillColor(value: ResourceColor): this {
        if (this.checkPriority("fillColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectRepeat(value: ImageRepeat): this {
        if (this.checkPriority("objectRepeat")) {
            const value_casted = value as (ImageRepeat)
            this.getPeer()?.objectRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoResize(value: boolean): this {
        if (this.checkPriority("autoResize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoResizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderMode(value: ImageRenderMode): this {
        if (this.checkPriority("renderMode")) {
            const value_casted = value as (ImageRenderMode)
            this.getPeer()?.renderModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dynamicRangeMode(value: DynamicRangeMode): this {
        if (this.checkPriority("dynamicRangeMode")) {
            const value_casted = value as (DynamicRangeMode)
            this.getPeer()?.dynamicRangeModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public interpolation(value: ImageInterpolation): this {
        if (this.checkPriority("interpolation")) {
            const value_casted = value as (ImageInterpolation)
            this.getPeer()?.interpolationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sourceSize(value: ImageSourceSize): this {
        if (this.checkPriority("sourceSize")) {
            const value_casted = value as (ImageSourceSize)
            this.getPeer()?.sourceSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public syncLoad(value: boolean): this {
        if (this.checkPriority("syncLoad")) {
            const value_casted = value as (boolean)
            this.getPeer()?.syncLoadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter)
            this.getPeer()?.colorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pointLight(value: PointLightStyle): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeAntialiasing(value: number): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (number)
            this.getPeer()?.edgeAntialiasingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (((event?: Type_ImageAttribute_onComplete_callback_event) => void))
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ImageErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public resizable(value: ResizableOptions): this {
        if (this.checkPriority("resizable")) {
            const value_casted = value as (ResizableOptions)
            this.getPeer()?.resizableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public privacySensitive(value: boolean): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enhancedImageQuality(value: ResolutionQuality): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (ResolutionQuality)
            this.getPeer()?.enhancedImageQualityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkImage(
    /** @memo */
    style: ((attributes: UIImageAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions,
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
