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
import { Matrix2D_serializer, Matrix2D, Matrix2DInternal } from "./matrix2d"
import { ColorMetrics_serializer, Size_serializer, LengthMetrics_serializer } from "./../Graphics"
import { drawing_Canvas_serializer } from "./../framework/ohos.graphics.drawing"
import { ColorMetrics, Size, LengthMetricsUnit, LengthMetrics } from "arkui.Graphics"
import { extractors, AttributeModifier, hookCanvasAttributeModifier, AttributeUpdater, hookSetCanvasOptions, hookCanvasStartImageAnalyzer, hookCreateImageData, hookGetImageData, hookPutImageData, hookGetContext, registerAttach, unregisterAttach, registerDetach, unregisterDetach } from "#handwritten"
import { default as drawing } from "@ohos.graphics.drawing"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { default as image } from "@ohos.multimedia.image"
import { ImageAIOptions_serializer, ImageAIOptions, ImageAnalyzerConfig_serializer, ImageAnalyzerConfig } from "./imageCommon"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VoidCallback } from "./units"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CanvasModifier } from "./../CanvasModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Color } from "./enums"
import { FrameNode } from "arkui.FrameNode"
export class CanvasGradientInternal {
    public static fromPtr(ptr: KPointer): CanvasGradient {
        return new CanvasGradient(ptr)
    }
}
export class CanvasGradient implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CanvasGradient.getFinalizer())
    }
    constructor() {
        this(CanvasGradient.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasGradient_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasGradient_getFinalizer()
    }
    public addColorStop(offset: double, color: string | ColorMetrics): void {
        const offset_casted = offset as (double)
        const color_casted = color as (string | ColorMetrics)
        this.addColorStop_serialize(offset_casted, color_casted)
        return
    }
    addColorStop_serialize(offset: double, color: string | ColorMetrics): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (color instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const colorForIdx0  = color as string
            thisSerializer.writeString(colorForIdx0)
        } else if (color instanceof ColorMetrics) {
            thisSerializer.writeInt8((1).toByte())
            const colorForIdx1  = color as ColorMetrics
            ColorMetrics_serializer.write(thisSerializer, colorForIdx1)
        }
        ArkUIGeneratedNativeModule._CanvasGradient_addColorStop(this.peer!.ptr, offset, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class CanvasPathInternal {
    public static fromPtr(ptr: KPointer): CanvasPath {
        return new CanvasPath(ptr)
    }
}
export class CanvasPath implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CanvasPath.getFinalizer())
    }
    constructor() {
        this(CanvasPath.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasPath_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasPath_getFinalizer()
    }
    public arc(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const radius_casted = radius as (number)
        const startAngle_casted = startAngle as (number)
        const endAngle_casted = endAngle as (number)
        const counterclockwise_casted = counterclockwise as (boolean | undefined)
        this.arc_serialize(x_casted, y_casted, radius_casted, startAngle_casted, endAngle_casted, counterclockwise_casted)
        return
    }
    public arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        const x2_casted = x2 as (number)
        const y2_casted = y2 as (number)
        const radius_casted = radius as (number)
        this.arcTo_serialize(x1_casted, y1_casted, x2_casted, y2_casted, radius_casted)
        return
    }
    public bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        const cp1x_casted = cp1x as (number)
        const cp1y_casted = cp1y as (number)
        const cp2x_casted = cp2x as (number)
        const cp2y_casted = cp2y as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.bezierCurveTo_serialize(cp1x_casted, cp1y_casted, cp2x_casted, cp2y_casted, x_casted, y_casted)
        return
    }
    public closePath(): void {
        this.closePath_serialize()
        return
    }
    public ellipse(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const radiusX_casted = radiusX as (number)
        const radiusY_casted = radiusY as (number)
        const rotation_casted = rotation as (number)
        const startAngle_casted = startAngle as (number)
        const endAngle_casted = endAngle as (number)
        const counterclockwise_casted = counterclockwise as (boolean | undefined)
        this.ellipse_serialize(x_casted, y_casted, radiusX_casted, radiusY_casted, rotation_casted, startAngle_casted, endAngle_casted, counterclockwise_casted)
        return
    }
    public lineTo(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.lineTo_serialize(x_casted, y_casted)
        return
    }
    public moveTo(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.moveTo_serialize(x_casted, y_casted)
        return
    }
    public quadraticCurveTo(cpx: number, cpy: number, x: number, y: number): void {
        const cpx_casted = cpx as (number)
        const cpy_casted = cpy as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.quadraticCurveTo_serialize(cpx_casted, cpy_casted, x_casted, y_casted)
        return
    }
    public rect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this.rect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    arc_serialize(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (counterclockwise !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const counterclockwiseTmpValue  = counterclockwise!
            thisSerializer.writeBoolean(counterclockwiseTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasPath_arc(this.peer!.ptr, x, y, radius, startAngle, endAngle, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arcTo_serialize(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_arcTo(this.peer!.ptr, x1, y1, x2, y2, radius)
    }
    bezierCurveTo_serialize(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_bezierCurveTo(this.peer!.ptr, cp1x, cp1y, cp2x, cp2y, x, y)
    }
    closePath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasPath_closePath(this.peer!.ptr)
    }
    ellipse_serialize(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (counterclockwise !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const counterclockwiseTmpValue  = counterclockwise!
            thisSerializer.writeBoolean(counterclockwiseTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasPath_ellipse(this.peer!.ptr, x, y, radiusX, radiusY, rotation, startAngle, endAngle, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_lineTo(this.peer!.ptr, x, y)
    }
    moveTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_moveTo(this.peer!.ptr, x, y)
    }
    quadraticCurveTo_serialize(cpx: number, cpy: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_quadraticCurveTo(this.peer!.ptr, cpx, cpy, x, y)
    }
    rect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_rect(this.peer!.ptr, x, y, w, h)
    }
}
export interface CanvasPattern {
    setTransform(transform: Matrix2D | undefined): void
}
export class CanvasPatternInternal implements MaterializedBase,CanvasPattern {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CanvasPatternInternal.getFinalizer())
    }
    constructor() {
        this(CanvasPatternInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasPattern_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasPattern_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): CanvasPatternInternal {
        return new CanvasPatternInternal(ptr)
    }
    public setTransform(transform?: Matrix2D): void {
        const transform_casted = transform as (Matrix2D | undefined)
        this.setTransform_serialize(transform_casted)
        return
    }
    setTransform_serialize(transform?: Matrix2D): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (transform !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transformTmpValue  = transform!
            Matrix2D_serializer.write(thisSerializer, transformTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasPattern_setTransform(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DrawingRenderingContextInternal {
    public static fromPtr(ptr: KPointer): DrawingRenderingContext {
        return new DrawingRenderingContext(false, ptr)
    }
}
export class DrawingRenderingContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get size(): Size {
        return this.getSize()
    }
    set size(size: Size) {
        this.setSize(size)
    }
    get canvas(): drawing.Canvas | undefined {
        return this.getCanvas()
    }
    set canvas(canvas: drawing.Canvas | undefined) {
        this.setCanvas(canvas)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DrawingRenderingContext.getFinalizer())
    }
    constructor(unit?: LengthMetricsUnit) {
        this(false, DrawingRenderingContext.construct(unit))
    }
    static construct(unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingRenderingContext_getFinalizer()
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private getSize(): Size {
        return this.getSize_serialize()
    }
    private setSize(size: Size): void {
        const size_casted = size as (Size)
        this.setSize_serialize(size_casted)
        return
    }
    private getCanvas(): drawing.Canvas | undefined {
        return this.getCanvas_serialize()
    }
    private setCanvas(canvas: drawing.Canvas | undefined): void {
        const canvas_casted = canvas as (drawing.Canvas | undefined)
        this.setCanvas_serialize(canvas_casted)
        return
    }
    invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._DrawingRenderingContext_invalidate(this.peer!.ptr)
    }
    private getSize_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setSize_serialize(size: Size): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._DrawingRenderingContext_setSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getCanvas_serialize(): drawing.Canvas | undefined {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getCanvas(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : drawing.Canvas | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (drawing_Canvas_serializer.read(retvalDeserializer) as drawing.Canvas)
        }
        const returnResult : drawing.Canvas | undefined = buffer
        return returnResult
    }
    private setCanvas_serialize(canvas: drawing.Canvas | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (canvas !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const canvasTmpValue  = canvas!
            drawing_Canvas_serializer.write(thisSerializer, canvasTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DrawingRenderingContext_setCanvas(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ImageBitmapInternal {
    public static fromPtr(ptr: KPointer): ImageBitmap {
        return new ImageBitmap(false, false, ptr)
    }
}
export class ImageBitmap implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get height(): number {
        return this.getHeight()
    }
    set height(height: number) {
        this.setHeight(height)
    }
    get width(): number {
        return this.getWidth()
    }
    set width(width: number) {
        this.setWidth(width)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ImageBitmap.getFinalizer())
    }
    constructor(src: image.PixelMap | string, unit?: LengthMetricsUnit) {
        this(false, false, ImageBitmap.construct(src, unit))
    }
    static construct(src: image.PixelMap | string, unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toByte())
            const srcForIdx0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof string) {
            thisSerializer.writeInt8((1).toByte())
            const srcForIdx1  = src as string
            thisSerializer.writeString(srcForIdx1)
        }
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageBitmap_getFinalizer()
    }
    public close(): void {
        this.close_serialize()
        return
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private setHeight(height: number): void {
        const height_casted = height as (number)
        this.setHeight_serialize(height_casted)
        return
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private setWidth(width: number): void {
        const width_casted = width as (number)
        this.setWidth_serialize(width_casted)
        return
    }
    close_serialize(): void {
        ArkUIGeneratedNativeModule._ImageBitmap_close(this.peer!.ptr)
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getHeight(this.peer!.ptr)
        return retval
    }
    private setHeight_serialize(height: number): void {
        ArkUIGeneratedNativeModule._ImageBitmap_setHeight(this.peer!.ptr, height)
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getWidth(this.peer!.ptr)
        return retval
    }
    private setWidth_serialize(width: number): void {
        ArkUIGeneratedNativeModule._ImageBitmap_setWidth(this.peer!.ptr, width)
    }
}
export class OffscreenCanvasInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvas {
        return new OffscreenCanvas(false, false, false, ptr)
    }
}
export class OffscreenCanvas implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get height(): number {
        return this.getHeight()
    }
    set height(height: number) {
        this.setHeight(height)
    }
    get width(): number {
        return this.getWidth()
    }
    set width(width: number) {
        this.setWidth(width)
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, OffscreenCanvas.getFinalizer())
    }
    constructor(width: number, height: number, unit?: LengthMetricsUnit) {
        this(false, false, false, OffscreenCanvas.construct(width, height, unit))
    }
    static construct(width: number, height: number, unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_construct(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._OffscreenCanvas_getFinalizer()
    }
    public transferToImageBitmap(): ImageBitmap {
        return this.transferToImageBitmap_serialize()
    }
    public getContext2d(options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        const options_casted = options as (RenderingContextSettings | undefined)
        return this.getContext2d_serialize(options_casted)
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private setHeight(height: number): void {
        const height_casted = height as (number)
        this.setHeight_serialize(height_casted)
        return
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private setWidth(width: number): void {
        const width_casted = width as (number)
        this.setWidth_serialize(width_casted)
        return
    }
    getContext(contextType: string, options: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        return hookGetContext(this, contextType, options)
    }
    transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
    getContext2d_serialize(options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RenderingContextSettings_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getContext2d(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : OffscreenCanvasRenderingContext2D = OffscreenCanvasRenderingContext2DInternal.fromPtr(retval)
        return obj
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getHeight(this.peer!.ptr)
        return retval
    }
    private setHeight_serialize(height: number): void {
        ArkUIGeneratedNativeModule._OffscreenCanvas_setHeight(this.peer!.ptr, height)
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getWidth(this.peer!.ptr)
        return retval
    }
    private setWidth_serialize(width: number): void {
        ArkUIGeneratedNativeModule._OffscreenCanvas_setWidth(this.peer!.ptr, width)
    }
}
export class RenderingContextSettingsInternal {
    public static fromPtr(ptr: KPointer): RenderingContextSettings {
        return new RenderingContextSettings(false, ptr)
    }
}
export class RenderingContextSettings implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get antialias(): boolean | undefined {
        return this.getAntialias()
    }
    set antialias(antialias: boolean | undefined) {
        this.setAntialias(antialias)
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RenderingContextSettings.getFinalizer())
    }
    constructor(antialias?: boolean) {
        this(false, RenderingContextSettings.construct(antialias))
    }
    static construct(antialias?: boolean): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (antialias !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const antialiasTmpValue  = antialias!
            thisSerializer.writeBoolean(antialiasTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RenderingContextSettings_getFinalizer()
    }
    private getAntialias(): boolean | undefined {
        return this.getAntialias_serialize()
    }
    private setAntialias(antialias: boolean | undefined): void {
        const antialias_casted = antialias as (boolean | undefined)
        this.setAntialias_serialize(antialias_casted)
        return
    }
    private getAntialias_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_getAntialias(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setAntialias_serialize(antialias: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (antialias !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const antialiasTmpValue  = antialias!
            thisSerializer.writeBoolean(antialiasTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RenderingContextSettings_setAntialias(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkCanvasPeer extends ArkCommonMethodPeer {
    attributeSet?: CanvasModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCanvasPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Canvas_construct(peerId, flags)
        const _peer  = new ArkCanvasPeer(_peerPtr, peerId, 'Canvas', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCanvasOptionsAttribute(context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (context !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contextTmpValue  = context!
            if (contextTmpValue instanceof CanvasRenderingContext2D) {
                thisSerializer.writeInt8((0).toByte())
                const contextTmpValueForIdx0  = contextTmpValue as CanvasRenderingContext2D
                CanvasRenderingContext2D_serializer.write(thisSerializer, contextTmpValueForIdx0)
            } else if (contextTmpValue instanceof DrawingRenderingContext) {
                thisSerializer.writeInt8((1).toByte())
                const contextTmpValueForIdx1  = contextTmpValue as DrawingRenderingContext
                DrawingRenderingContext_serializer.write(thisSerializer, contextTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (imageAIOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const imageAIOptionsTmpValue  = imageAIOptions!
            ImageAIOptions_serializer.write(thisSerializer, imageAIOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasInterface_setCanvasOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReadyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasAttribute_setOnReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CanvasAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type CanvasFillRule = string;
export type CanvasLineCap = string;
export type CanvasLineJoin = string;
export type CanvasDirection = string;
export type CanvasTextAlign = string;
export type CanvasTextBaseline = string;
export type ImageSmoothingQuality = string;
export interface TextMetrics {
    readonly actualBoundingBoxAscent: number;
    readonly actualBoundingBoxDescent: number;
    readonly actualBoundingBoxLeft: number;
    readonly actualBoundingBoxRight: number;
    readonly alphabeticBaseline: number;
    readonly emHeightAscent: number;
    readonly emHeightDescent: number;
    readonly fontBoundingBoxAscent: number;
    readonly fontBoundingBoxDescent: number;
    readonly hangingBaseline: number;
    readonly ideographicBaseline: number;
    readonly width: number;
    readonly height: number;
}
export interface CanvasAttribute extends CommonMethod {
    setCanvasOptions(context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): this {
        throw new Error("Unimplemented method setCanvasOptions")
    }
    onReady(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onReady")
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnalyzer")
    }
    attributeModifier(value: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCanvasStyle extends ArkCommonMethodStyle implements CanvasAttribute {
    onReady_value?: VoidCallback | undefined
    enableAnalyzer_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined
    setCanvasOptions(context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): this {
        return this
    }
    onReady(value: VoidCallback | undefined): this {
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkCanvasComponent extends ArkCommonMethodComponent implements CanvasAttribute {
    getPeer(): ArkCanvasPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkCanvasPeer)
    }
    public setCanvasOptions(context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setCanvasOptions")) {
            hookSetCanvasOptions(this, context, imageAIOptions)
            const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext | undefined)
            const imageAIOptions_casted = imageAIOptions as (ImageAIOptions | undefined)
            this.getPeer()?.setCanvasOptionsAttribute(context_casted, imageAIOptions_casted)
            return this
        }
        return this
    }
    public onReady(value: VoidCallback | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnReadyAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookCanvasAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function CanvasImpl(
    @memo
    style: ((attributes: CanvasAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCanvasComponent>((): ArkCanvasComponent => {
        return new ArkCanvasComponent()
    })
    NodeAttach<ArkCanvasPeer>((): ArkCanvasPeer => ArkCanvasPeer.create(receiver), (peer: ArkCanvasPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class CanvasGradient_serializer {
    public static write(buffer: SerializerBase, value: CanvasGradient): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CanvasGradient {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CanvasGradientInternal.fromPtr(ptr)
    }
}
export class CanvasPath_serializer {
    public static write(buffer: SerializerBase, value: CanvasPath): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CanvasPath {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CanvasPathInternal.fromPtr(ptr)
    }
}
export class CanvasPattern_serializer {
    public static write(buffer: SerializerBase, value: CanvasPattern): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CanvasPattern {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CanvasPatternInternal.fromPtr(ptr)
    }
}
export class OffscreenCanvas_serializer {
    public static write(buffer: SerializerBase, value: OffscreenCanvas): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): OffscreenCanvas {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return OffscreenCanvasInternal.fromPtr(ptr)
    }
}
export class Path2D_serializer {
    public static write(buffer: SerializerBase, value: Path2D): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Path2D {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return Path2DInternal.fromPtr(ptr)
    }
}
export class TextMetrics_serializer {
    public static write(buffer: SerializerBase, value: TextMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForActualBoundingBoxAscent  = value.actualBoundingBoxAscent
        valueSerializer.writeNumber(valueHolderForActualBoundingBoxAscent)
        const valueHolderForActualBoundingBoxDescent  = value.actualBoundingBoxDescent
        valueSerializer.writeNumber(valueHolderForActualBoundingBoxDescent)
        const valueHolderForActualBoundingBoxLeft  = value.actualBoundingBoxLeft
        valueSerializer.writeNumber(valueHolderForActualBoundingBoxLeft)
        const valueHolderForActualBoundingBoxRight  = value.actualBoundingBoxRight
        valueSerializer.writeNumber(valueHolderForActualBoundingBoxRight)
        const valueHolderForAlphabeticBaseline  = value.alphabeticBaseline
        valueSerializer.writeNumber(valueHolderForAlphabeticBaseline)
        const valueHolderForEmHeightAscent  = value.emHeightAscent
        valueSerializer.writeNumber(valueHolderForEmHeightAscent)
        const valueHolderForEmHeightDescent  = value.emHeightDescent
        valueSerializer.writeNumber(valueHolderForEmHeightDescent)
        const valueHolderForFontBoundingBoxAscent  = value.fontBoundingBoxAscent
        valueSerializer.writeNumber(valueHolderForFontBoundingBoxAscent)
        const valueHolderForFontBoundingBoxDescent  = value.fontBoundingBoxDescent
        valueSerializer.writeNumber(valueHolderForFontBoundingBoxDescent)
        const valueHolderForHangingBaseline  = value.hangingBaseline
        valueSerializer.writeNumber(valueHolderForHangingBaseline)
        const valueHolderForIdeographicBaseline  = value.ideographicBaseline
        valueSerializer.writeNumber(valueHolderForIdeographicBaseline)
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): TextMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const actualBoundingBoxAscentTmpResult : number = (valueDeserializer.readNumber() as number)
        const actualBoundingBoxDescentTmpResult : number = (valueDeserializer.readNumber() as number)
        const actualBoundingBoxLeftTmpResult : number = (valueDeserializer.readNumber() as number)
        const actualBoundingBoxRightTmpResult : number = (valueDeserializer.readNumber() as number)
        const alphabeticBaselineTmpResult : number = (valueDeserializer.readNumber() as number)
        const emHeightAscentTmpResult : number = (valueDeserializer.readNumber() as number)
        const emHeightDescentTmpResult : number = (valueDeserializer.readNumber() as number)
        const fontBoundingBoxAscentTmpResult : number = (valueDeserializer.readNumber() as number)
        const fontBoundingBoxDescentTmpResult : number = (valueDeserializer.readNumber() as number)
        const hangingBaselineTmpResult : number = (valueDeserializer.readNumber() as number)
        const ideographicBaselineTmpResult : number = (valueDeserializer.readNumber() as number)
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : TextMetrics = ({actualBoundingBoxAscent: actualBoundingBoxAscentTmpResult, actualBoundingBoxDescent: actualBoundingBoxDescentTmpResult, actualBoundingBoxLeft: actualBoundingBoxLeftTmpResult, actualBoundingBoxRight: actualBoundingBoxRightTmpResult, alphabeticBaseline: alphabeticBaselineTmpResult, emHeightAscent: emHeightAscentTmpResult, emHeightDescent: emHeightDescentTmpResult, fontBoundingBoxAscent: fontBoundingBoxAscentTmpResult, fontBoundingBoxDescent: fontBoundingBoxDescentTmpResult, hangingBaseline: hangingBaselineTmpResult, ideographicBaseline: ideographicBaselineTmpResult, width: widthTmpResult, height: heightTmpResult} as TextMetrics)
        return value
    }
}
export class DrawingRenderingContext_serializer {
    public static write(buffer: SerializerBase, value: DrawingRenderingContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DrawingRenderingContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DrawingRenderingContextInternal.fromPtr(ptr)
    }
}
export class ImageBitmap_serializer {
    public static write(buffer: SerializerBase, value: ImageBitmap): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ImageBitmap {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ImageBitmapInternal.fromPtr(ptr)
    }
}
export class RenderingContextSettings_serializer {
    public static write(buffer: SerializerBase, value: RenderingContextSettings): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RenderingContextSettings {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RenderingContextSettingsInternal.fromPtr(ptr)
    }
}
export class CanvasRenderer_serializer {
    public static write(buffer: SerializerBase, value: CanvasRenderer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CanvasRenderer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CanvasRendererInternal.fromPtr(ptr)
    }
}
export class CanvasRenderingContext2D_serializer {
    public static write(buffer: SerializerBase, value: CanvasRenderingContext2D): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CanvasRenderingContext2D {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CanvasRenderingContext2DInternal.fromPtr(ptr)
    }
}
export class OffscreenCanvasRenderingContext2D_serializer {
    public static write(buffer: SerializerBase, value: OffscreenCanvasRenderingContext2D): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): OffscreenCanvasRenderingContext2D {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return OffscreenCanvasRenderingContext2DInternal.fromPtr(ptr)
    }
}
export class CanvasRendererInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderer {
        return new CanvasRenderer(ptr)
    }
}
export class CanvasRenderer extends CanvasPath implements MaterializedBase {
    get letterSpacing(): LengthMetrics | string {
        return this.getLetterSpacing()
    }
    set letterSpacing(letterSpacing: LengthMetrics | string) {
        this.setLetterSpacing(letterSpacing)
    }
    get globalAlpha(): number {
        return this.getGlobalAlpha()
    }
    set globalAlpha(globalAlpha: number) {
        this.setGlobalAlpha(globalAlpha)
    }
    get globalCompositeOperation(): string {
        return this.getGlobalCompositeOperation()
    }
    set globalCompositeOperation(globalCompositeOperation: string) {
        this.setGlobalCompositeOperation(globalCompositeOperation)
    }
    get fillStyle(): string | Color | int32 | CanvasGradient | CanvasPattern {
        return this.getFillStyle()
    }
    set fillStyle(fillStyle: string | Color | int32 | CanvasGradient | CanvasPattern) {
        this.setFillStyle(fillStyle)
    }
    get strokeStyle(): string | Color | int32 | CanvasGradient | CanvasPattern {
        return this.getStrokeStyle()
    }
    set strokeStyle(strokeStyle: string | Color | int32 | CanvasGradient | CanvasPattern) {
        this.setStrokeStyle(strokeStyle)
    }
    get filter(): string {
        return this.getFilter()
    }
    set filter(filter: string) {
        this.setFilter(filter)
    }
    get imageSmoothingEnabled(): boolean {
        return this.getImageSmoothingEnabled()
    }
    set imageSmoothingEnabled(imageSmoothingEnabled: boolean) {
        this.setImageSmoothingEnabled(imageSmoothingEnabled)
    }
    get imageSmoothingQuality(): ImageSmoothingQuality {
        return this.getImageSmoothingQuality()
    }
    set imageSmoothingQuality(imageSmoothingQuality: ImageSmoothingQuality) {
        this.setImageSmoothingQuality(imageSmoothingQuality)
    }
    get lineCap(): CanvasLineCap {
        return this.getLineCap()
    }
    set lineCap(lineCap: CanvasLineCap) {
        this.setLineCap(lineCap)
    }
    get lineDashOffset(): number {
        return this.getLineDashOffset()
    }
    set lineDashOffset(lineDashOffset: number) {
        this.setLineDashOffset(lineDashOffset)
    }
    get lineJoin(): CanvasLineJoin {
        return this.getLineJoin()
    }
    set lineJoin(lineJoin: CanvasLineJoin) {
        this.setLineJoin(lineJoin)
    }
    get lineWidth(): number {
        return this.getLineWidth()
    }
    set lineWidth(lineWidth: number) {
        this.setLineWidth(lineWidth)
    }
    get miterLimit(): number {
        return this.getMiterLimit()
    }
    set miterLimit(miterLimit: number) {
        this.setMiterLimit(miterLimit)
    }
    get shadowBlur(): number {
        return this.getShadowBlur()
    }
    set shadowBlur(shadowBlur: number) {
        this.setShadowBlur(shadowBlur)
    }
    get shadowColor(): string {
        return this.getShadowColor()
    }
    set shadowColor(shadowColor: string) {
        this.setShadowColor(shadowColor)
    }
    get shadowOffsetX(): number {
        return this.getShadowOffsetX()
    }
    set shadowOffsetX(shadowOffsetX: number) {
        this.setShadowOffsetX(shadowOffsetX)
    }
    get shadowOffsetY(): number {
        return this.getShadowOffsetY()
    }
    set shadowOffsetY(shadowOffsetY: number) {
        this.setShadowOffsetY(shadowOffsetY)
    }
    get direction(): CanvasDirection {
        return this.getDirection()
    }
    set direction(direction: CanvasDirection) {
        this.setDirection(direction)
    }
    get font(): string {
        return this.getFont()
    }
    set font(font: string) {
        this.setFont(font)
    }
    get textAlign(): CanvasTextAlign {
        return this.getTextAlign()
    }
    set textAlign(textAlign: CanvasTextAlign) {
        this.setTextAlign(textAlign)
    }
    get textBaseline(): CanvasTextBaseline {
        return this.getTextBaseline()
    }
    set textBaseline(textBaseline: CanvasTextBaseline) {
        this.setTextBaseline(textBaseline)
    }
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(CanvasRenderer.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderer_getFinalizer()
    }
    public drawImage(image: ImageBitmap | image.PixelMap, dx: number, dy: number): void {
        const image_casted = image as (ImageBitmap | image.PixelMap)
        const dx_casted = dx as (number)
        const dy_casted = dy as (number)
        this.drawImage0_serialize(image_casted, dx_casted, dy_casted)
        return
    }
    public drawImage(image: ImageBitmap | image.PixelMap, dx: number, dy: number, dw: number, dh: number): void {
        const image_casted = image as (ImageBitmap | image.PixelMap)
        const dx_casted = dx as (number)
        const dy_casted = dy as (number)
        const dw_casted = dw as (number)
        const dh_casted = dh as (number)
        this.drawImage1_serialize(image_casted, dx_casted, dy_casted, dw_casted, dh_casted)
        return
    }
    public drawImage(image: ImageBitmap | image.PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        const image_casted = image as (ImageBitmap | image.PixelMap)
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        const dx_casted = dx as (number)
        const dy_casted = dy as (number)
        const dw_casted = dw as (number)
        const dh_casted = dh as (number)
        this.drawImage2_serialize(image_casted, sx_casted, sy_casted, sw_casted, sh_casted, dx_casted, dy_casted, dw_casted, dh_casted)
        return
    }
    public beginPath(): void {
        this.beginPath_serialize()
        return
    }
    public clip(fillRule?: CanvasFillRule): void {
        const fillRule_casted = fillRule as (CanvasFillRule | undefined)
        this.clip0_serialize(fillRule_casted)
        return
    }
    public clip(path: Path2D, fillRule?: CanvasFillRule): void {
        const path_casted = path as (Path2D)
        const fillRule_casted = fillRule as (CanvasFillRule | undefined)
        this.clip1_serialize(path_casted, fillRule_casted)
        return
    }
    public fill(fillRule?: CanvasFillRule): void {
        const fillRule_casted = fillRule as (CanvasFillRule | undefined)
        this.fill0_serialize(fillRule_casted)
        return
    }
    public fill(path: Path2D, fillRule?: CanvasFillRule): void {
        const path_casted = path as (Path2D)
        const fillRule_casted = fillRule as (CanvasFillRule | undefined)
        this.fill1_serialize(path_casted, fillRule_casted)
        return
    }
    public stroke(path?: Path2D): void {
        const path_casted = path as (Path2D | undefined)
        this.stroke_serialize(path_casted)
        return
    }
    public createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const x0_casted = x0 as (number)
        const y0_casted = y0 as (number)
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        return this.createLinearGradient_serialize(x0_casted, y0_casted, x1_casted, y1_casted)
    }
    public createPattern(image: ImageBitmap, repetition: string | null): CanvasPattern | null {
        const image_casted = image as (ImageBitmap)
        const repetition_casted = repetition as (string | null)
        return this.createPattern_serialize(image_casted, repetition_casted)
    }
    public createRadialGradient(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient {
        const x0_casted = x0 as (number)
        const y0_casted = y0 as (number)
        const r0_casted = r0 as (number)
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        const r1_casted = r1 as (number)
        return this.createRadialGradient_serialize(x0_casted, y0_casted, r0_casted, x1_casted, y1_casted, r1_casted)
    }
    public createConicGradient(startAngle: number, x: number, y: number): CanvasGradient {
        const startAngle_casted = startAngle as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.createConicGradient_serialize(startAngle_casted, x_casted, y_casted)
    }
    public createImageData(sw: number, sh: number): ImageData {
        return hookCreateImageData(this, sw, sh)
    }
    public createImageData(imagedata: ImageData): ImageData {
        return hookCreateImageData(this, imagedata)
    }
    public getImageData(sx: number, sy: number, sw: number, sh: number): ImageData {
        return hookGetImageData(this, sx, sy, sw, sh)
    }
    public getPixelMap(sx: number, sy: number, sw: number, sh: number): image.PixelMap {
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        return this.getPixelMap_serialize(sx_casted, sy_casted, sw_casted, sh_casted)
    }
    public putImageData(imagedata: ImageData, dx: number | string, dy: number | string): void {
        hookPutImageData(this, imagedata, dx, dy)
    }
    public putImageData(imagedata: ImageData, dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void {
        hookPutImageData(this, imagedata, dx, dy, dirtyX, dirtyY, dirtyWidth, dirtyHeight)
    }
    public getLineDash(): Array<number> {
        return this.getLineDash_serialize()
    }
    public setLineDash(segments: Array<number>): void {
        const segments_casted = segments as (Array<number>)
        this.setLineDash_serialize(segments_casted)
        return
    }
    public clearRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this.clearRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public fillRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this.fillRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public strokeRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this.strokeRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public restore(): void {
        this.restore_serialize()
        return
    }
    public save(): void {
        this.save_serialize()
        return
    }
    public fillText(text: string, x: number, y: number, maxWidth?: number): void {
        const text_casted = text as (string)
        const x_casted = x as (number)
        const y_casted = y as (number)
        const maxWidth_casted = maxWidth as (number | undefined)
        this.fillText_serialize(text_casted, x_casted, y_casted, maxWidth_casted)
        return
    }
    public measureText(text: string): TextMetrics {
        const text_casted = text as (string)
        return this.measureText_serialize(text_casted)
    }
    public strokeText(text: string, x: number, y: number, maxWidth?: number): void {
        const text_casted = text as (string)
        const x_casted = x as (number)
        const y_casted = y as (number)
        const maxWidth_casted = maxWidth as (number | undefined)
        this.strokeText_serialize(text_casted, x_casted, y_casted, maxWidth_casted)
        return
    }
    public getTransform(): Matrix2D {
        return this.getTransform_serialize()
    }
    public resetTransform(): void {
        this.resetTransform_serialize()
        return
    }
    public rotate(angle: number): void {
        const angle_casted = angle as (number)
        this.rotate_serialize(angle_casted)
        return
    }
    public scale(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.scale_serialize(x_casted, y_casted)
        return
    }
    public setTransform(a: number, b: number, c: number, d: number, e: number, f: number): void {
        const a_casted = a as (number)
        const b_casted = b as (number)
        const c_casted = c as (number)
        const d_casted = d as (number)
        const e_casted = e as (number)
        const f_casted = f as (number)
        this.setTransform0_serialize(a_casted, b_casted, c_casted, d_casted, e_casted, f_casted)
        return
    }
    public setTransform(transform?: Matrix2D): void {
        const transform_casted = transform as (Matrix2D | undefined)
        this.setTransform1_serialize(transform_casted)
        return
    }
    public transform(a: number, b: number, c: number, d: number, e: number, f: number): void {
        const a_casted = a as (number)
        const b_casted = b as (number)
        const c_casted = c as (number)
        const d_casted = d as (number)
        const e_casted = e as (number)
        const f_casted = f as (number)
        this.transform_serialize(a_casted, b_casted, c_casted, d_casted, e_casted, f_casted)
        return
    }
    public translate(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this.translate_serialize(x_casted, y_casted)
        return
    }
    public setPixelMap(value?: image.PixelMap): void {
        const value_casted = value as (image.PixelMap | undefined)
        this.setPixelMap_serialize(value_casted)
        return
    }
    public transferFromImageBitmap(bitmap: ImageBitmap): void {
        const bitmap_casted = bitmap as (ImageBitmap)
        this.transferFromImageBitmap_serialize(bitmap_casted)
        return
    }
    public saveLayer(): void {
        this.saveLayer_serialize()
        return
    }
    public restoreLayer(): void {
        this.restoreLayer_serialize()
        return
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private getLetterSpacing(): LengthMetrics | string {
        return this.getLetterSpacing_serialize()
    }
    private setLetterSpacing(letterSpacing: LengthMetrics | string): void {
        const letterSpacing_casted = letterSpacing as (LengthMetrics | string)
        this.setLetterSpacing_serialize(letterSpacing_casted)
        return
    }
    private getGlobalAlpha(): number {
        return this.getGlobalAlpha_serialize()
    }
    private setGlobalAlpha(globalAlpha: number): void {
        const globalAlpha_casted = globalAlpha as (number)
        this.setGlobalAlpha_serialize(globalAlpha_casted)
        return
    }
    private getGlobalCompositeOperation(): string {
        return this.getGlobalCompositeOperation_serialize()
    }
    private setGlobalCompositeOperation(globalCompositeOperation: string): void {
        const globalCompositeOperation_casted = globalCompositeOperation as (string)
        this.setGlobalCompositeOperation_serialize(globalCompositeOperation_casted)
        return
    }
    private getFillStyle(): string | Color | int32 | CanvasGradient | CanvasPattern {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: string | Color | int32 | CanvasGradient | CanvasPattern): void {
        const fillStyle_casted = fillStyle as (string | Color | int32 | CanvasGradient | CanvasPattern)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getStrokeStyle(): string | Color | int32 | CanvasGradient | CanvasPattern {
        return this.getStrokeStyle_serialize()
    }
    private setStrokeStyle(strokeStyle: string | Color | int32 | CanvasGradient | CanvasPattern): void {
        const strokeStyle_casted = strokeStyle as (string | Color | int32 | CanvasGradient | CanvasPattern)
        this.setStrokeStyle_serialize(strokeStyle_casted)
        return
    }
    private getFilter(): string {
        return this.getFilter_serialize()
    }
    private setFilter(filter: string): void {
        const filter_casted = filter as (string)
        this.setFilter_serialize(filter_casted)
        return
    }
    private getImageSmoothingEnabled(): boolean {
        return this.getImageSmoothingEnabled_serialize()
    }
    private setImageSmoothingEnabled(imageSmoothingEnabled: boolean): void {
        const imageSmoothingEnabled_casted = imageSmoothingEnabled as (boolean)
        this.setImageSmoothingEnabled_serialize(imageSmoothingEnabled_casted)
        return
    }
    private getImageSmoothingQuality(): ImageSmoothingQuality {
        return this.getImageSmoothingQuality_serialize()
    }
    private setImageSmoothingQuality(imageSmoothingQuality: ImageSmoothingQuality): void {
        const imageSmoothingQuality_casted = imageSmoothingQuality as (ImageSmoothingQuality)
        this.setImageSmoothingQuality_serialize(imageSmoothingQuality_casted)
        return
    }
    private getLineCap(): CanvasLineCap {
        return this.getLineCap_serialize()
    }
    private setLineCap(lineCap: CanvasLineCap): void {
        const lineCap_casted = lineCap as (CanvasLineCap)
        this.setLineCap_serialize(lineCap_casted)
        return
    }
    private getLineDashOffset(): number {
        return this.getLineDashOffset_serialize()
    }
    private setLineDashOffset(lineDashOffset: number): void {
        const lineDashOffset_casted = lineDashOffset as (number)
        this.setLineDashOffset_serialize(lineDashOffset_casted)
        return
    }
    private getLineJoin(): CanvasLineJoin {
        return this.getLineJoin_serialize()
    }
    private setLineJoin(lineJoin: CanvasLineJoin): void {
        const lineJoin_casted = lineJoin as (CanvasLineJoin)
        this.setLineJoin_serialize(lineJoin_casted)
        return
    }
    private getLineWidth(): number {
        return this.getLineWidth_serialize()
    }
    private setLineWidth(lineWidth: number): void {
        const lineWidth_casted = lineWidth as (number)
        this.setLineWidth_serialize(lineWidth_casted)
        return
    }
    private getMiterLimit(): number {
        return this.getMiterLimit_serialize()
    }
    private setMiterLimit(miterLimit: number): void {
        const miterLimit_casted = miterLimit as (number)
        this.setMiterLimit_serialize(miterLimit_casted)
        return
    }
    private getShadowBlur(): number {
        return this.getShadowBlur_serialize()
    }
    private setShadowBlur(shadowBlur: number): void {
        const shadowBlur_casted = shadowBlur as (number)
        this.setShadowBlur_serialize(shadowBlur_casted)
        return
    }
    private getShadowColor(): string {
        return this.getShadowColor_serialize()
    }
    private setShadowColor(shadowColor: string): void {
        const shadowColor_casted = shadowColor as (string)
        this.setShadowColor_serialize(shadowColor_casted)
        return
    }
    private getShadowOffsetX(): number {
        return this.getShadowOffsetX_serialize()
    }
    private setShadowOffsetX(shadowOffsetX: number): void {
        const shadowOffsetX_casted = shadowOffsetX as (number)
        this.setShadowOffsetX_serialize(shadowOffsetX_casted)
        return
    }
    private getShadowOffsetY(): number {
        return this.getShadowOffsetY_serialize()
    }
    private setShadowOffsetY(shadowOffsetY: number): void {
        const shadowOffsetY_casted = shadowOffsetY as (number)
        this.setShadowOffsetY_serialize(shadowOffsetY_casted)
        return
    }
    private getDirection(): CanvasDirection {
        return this.getDirection_serialize()
    }
    private setDirection(direction: CanvasDirection): void {
        const direction_casted = direction as (CanvasDirection)
        this.setDirection_serialize(direction_casted)
        return
    }
    private getFont(): string {
        return this.getFont_serialize()
    }
    private setFont(font: string): void {
        const font_casted = font as (string)
        this.setFont_serialize(font_casted)
        return
    }
    private getTextAlign(): CanvasTextAlign {
        return this.getTextAlign_serialize()
    }
    private setTextAlign(textAlign: CanvasTextAlign): void {
        const textAlign_casted = textAlign as (CanvasTextAlign)
        this.setTextAlign_serialize(textAlign_casted)
        return
    }
    private getTextBaseline(): CanvasTextBaseline {
        return this.getTextBaseline_serialize()
    }
    private setTextBaseline(textBaseline: CanvasTextBaseline): void {
        const textBaseline_casted = textBaseline as (CanvasTextBaseline)
        this.setTextBaseline_serialize(textBaseline_casted)
        return
    }
    drawImage0_serialize(image: ImageBitmap | image.PixelMap, dx: number, dy: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (image instanceof ImageBitmap) {
            thisSerializer.writeInt8((0).toByte())
            const imageForIdx0  = image as ImageBitmap
            ImageBitmap_serializer.write(thisSerializer, imageForIdx0)
        } else if (image instanceof image.PixelMap) {
            thisSerializer.writeInt8((1).toByte())
            const imageForIdx1  = image as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, imageForIdx1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy)
        thisSerializer.release()
    }
    drawImage1_serialize(image: ImageBitmap | image.PixelMap, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (image instanceof ImageBitmap) {
            thisSerializer.writeInt8((0).toByte())
            const imageForIdx0  = image as ImageBitmap
            ImageBitmap_serializer.write(thisSerializer, imageForIdx0)
        } else if (image instanceof image.PixelMap) {
            thisSerializer.writeInt8((1).toByte())
            const imageForIdx1  = image as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, imageForIdx1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy, dw, dh)
        thisSerializer.release()
    }
    drawImage2_serialize(image: ImageBitmap | image.PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (image instanceof ImageBitmap) {
            thisSerializer.writeInt8((0).toByte())
            const imageForIdx0  = image as ImageBitmap
            ImageBitmap_serializer.write(thisSerializer, imageForIdx0)
        } else if (image instanceof image.PixelMap) {
            thisSerializer.writeInt8((1).toByte())
            const imageForIdx1  = image as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, imageForIdx1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage2(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), sx, sy, sw, sh, dx, dy, dw, dh)
        thisSerializer.release()
    }
    beginPath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_beginPath(this.peer!.ptr)
    }
    clip0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillRule !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillRuleTmpValue  = fillRule!
            thisSerializer.writeString(fillRuleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clip1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillRule !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillRuleTmpValue  = fillRule!
            thisSerializer.writeString(fillRuleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fill0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillRule !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillRuleTmpValue  = fillRule!
            thisSerializer.writeString(fillRuleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fill1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillRule !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fillRuleTmpValue  = fillRule!
            thisSerializer.writeString(fillRuleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stroke_serialize(path?: Path2D): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (path !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const pathTmpValue  = path!
            Path2D_serializer.write(thisSerializer, pathTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_stroke(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    createLinearGradient_serialize(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createLinearGradient(this.peer!.ptr, x0, y0, x1, y1)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    createPattern_serialize(image: ImageBitmap, repetition: string | null): CanvasPattern | null {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (repetition !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const repetitionTmpValue  = repetition!
            thisSerializer.writeString(repetitionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createPattern(this.peer!.ptr, toPeerPtr(image), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : CanvasPattern | null = null
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (CanvasPattern_serializer.read(retvalDeserializer) as CanvasPattern)
        }
        const returnResult : CanvasPattern | null = buffer
        return returnResult
    }
    createRadialGradient_serialize(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createRadialGradient(this.peer!.ptr, x0, y0, r0, x1, y1, r1)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    createConicGradient_serialize(startAngle: number, x: number, y: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createConicGradient(this.peer!.ptr, startAngle, x, y)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    getPixelMap_serialize(sx: number, sy: number, sw: number, sh: number): image.PixelMap {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getPixelMap(this.peer!.ptr, sx, sy, sw, sh)
        const obj : image.PixelMap = extractors.fromImagePixelMapPtr(retval)
        return obj
    }
    getLineDash_serialize(): Array<number> {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineDash(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    setLineDash_serialize(segments: Array<number>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((segments.length).toInt())
        for (let segmentsCounterI = 0; segmentsCounterI < segments.length; segmentsCounterI++) {
            const segmentsTmpElement : number = segments[segmentsCounterI]
            thisSerializer.writeNumber(segmentsTmpElement)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineDash(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clearRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_clearRect(this.peer!.ptr, x, y, w, h)
    }
    fillRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_fillRect(this.peer!.ptr, x, y, w, h)
    }
    strokeRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeRect(this.peer!.ptr, x, y, w, h)
    }
    restore_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restore(this.peer!.ptr)
    }
    save_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_save(this.peer!.ptr)
    }
    fillText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (maxWidth !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const maxWidthTmpValue  = maxWidth!
            thisSerializer.writeNumber(maxWidthTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fillText(this.peer!.ptr, text, x, y, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    measureText_serialize(text: string): TextMetrics {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_measureText(this.peer!.ptr, text)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : TextMetrics = TextMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    strokeText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (maxWidth !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const maxWidthTmpValue  = maxWidth!
            thisSerializer.writeNumber(maxWidthTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeText(this.peer!.ptr, text, x, y, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    getTransform_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getTransform(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    resetTransform_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_resetTransform(this.peer!.ptr)
    }
    rotate_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_rotate(this.peer!.ptr, angle)
    }
    scale_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_scale(this.peer!.ptr, x, y)
    }
    setTransform0_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform0(this.peer!.ptr, a, b, c, d, e, f)
    }
    setTransform1_serialize(transform?: Matrix2D): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (transform !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transformTmpValue  = transform!
            Matrix2D_serializer.write(thisSerializer, transformTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transform_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transform(this.peer!.ptr, a, b, c, d, e, f)
    }
    translate_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_translate(this.peer!.ptr, x, y)
    }
    setPixelMap_serialize(value?: image.PixelMap): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            image_PixelMap_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setPixelMap(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    transferFromImageBitmap_serialize(bitmap: ImageBitmap): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transferFromImageBitmap(this.peer!.ptr, toPeerPtr(bitmap))
    }
    saveLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_saveLayer(this.peer!.ptr)
    }
    restoreLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restoreLayer(this.peer!.ptr)
    }
    reset_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_reset(this.peer!.ptr)
    }
    private getLetterSpacing_serialize(): LengthMetrics | string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLetterSpacing(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferUnionSelector : int32 = retvalDeserializer.readInt8()
        let buffer : LengthMetrics | string | undefined
        if (bufferUnionSelector == (0).toChar()) {
            buffer = LengthMetrics_serializer.read(retvalDeserializer)
        } else if (bufferUnionSelector == (1).toChar()) {
            buffer = (retvalDeserializer.readString() as string)
        } else {
            throw new Error("One of the branches for buffer has to be chosen through deserialisation.")
        }
        const returnResult : LengthMetrics | string = (buffer as LengthMetrics | string)
        return returnResult
    }
    private setLetterSpacing_serialize(letterSpacing: LengthMetrics | string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (letterSpacing instanceof LengthMetrics) {
            thisSerializer.writeInt8((0).toByte())
            const letterSpacingForIdx0  = letterSpacing as LengthMetrics
            LengthMetrics_serializer.write(thisSerializer, letterSpacingForIdx0)
        } else if (letterSpacing instanceof string) {
            thisSerializer.writeInt8((1).toByte())
            const letterSpacingForIdx1  = letterSpacing as string
            thisSerializer.writeString(letterSpacingForIdx1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setLetterSpacing(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getGlobalAlpha_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getGlobalAlpha(this.peer!.ptr)
        return retval
    }
    private setGlobalAlpha_serialize(globalAlpha: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setGlobalAlpha(this.peer!.ptr, globalAlpha)
    }
    private getGlobalCompositeOperation_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getGlobalCompositeOperation(this.peer!.ptr)
        return retval
    }
    private setGlobalCompositeOperation_serialize(globalCompositeOperation: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setGlobalCompositeOperation(this.peer!.ptr, globalCompositeOperation)
    }
    private getFillStyle_serialize(): string | Color | int32 | CanvasGradient | CanvasPattern {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getFillStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferUnionSelector : int32 = retvalDeserializer.readInt8()
        let buffer : string | Color | int32 | CanvasGradient | CanvasPattern | undefined
        if (bufferUnionSelector == (0).toByte()) {
            buffer = (retvalDeserializer.readString() as string)
        } else if (bufferUnionSelector == (1).toByte()) {
            buffer = Color.values()[retvalDeserializer.readInt32()]
        } else if (bufferUnionSelector == (2).toByte()) {
            buffer = retvalDeserializer.readInt32()
        } else if (bufferUnionSelector == (3).toByte()) {
            buffer = (CanvasGradient_serializer.read(retvalDeserializer) as CanvasGradient)
        } else if (bufferUnionSelector == (4).toByte()) {
            buffer = (CanvasPattern_serializer.read(retvalDeserializer) as CanvasPattern)
        } else {
            throw new Error("One of the branches for buffer has to be chosen through deserialisation.")
        }
        const returnResult : string | Color | int32 | CanvasGradient | CanvasPattern = (buffer as string | Color | int32 | CanvasGradient | CanvasPattern)
        return returnResult
    }
    private setFillStyle_serialize(fillStyle: string | Color | int32 | CanvasGradient | CanvasPattern): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fillStyle instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const fillStyleForIdx0  = fillStyle as string
            thisSerializer.writeString(fillStyleForIdx0)
        } else if (fillStyle instanceof Color) {
            thisSerializer.writeInt8((1).toByte())
            const fillStyleForIdx1  = fillStyle as Color
            thisSerializer.writeInt32(fillStyleForIdx1.getOrdinal())
        } else if (fillStyle instanceof int32) {
            thisSerializer.writeInt8((2).toByte())
            const fillStyleForIdx2  = fillStyle as int32
            thisSerializer.writeInt32(fillStyleForIdx2)
        } else if (fillStyle instanceof CanvasGradient) {
            thisSerializer.writeInt8((3).toByte())
            const fillStyleForIdx3  = fillStyle as CanvasGradient
            CanvasGradient_serializer.write(thisSerializer, fillStyleForIdx3)
        } else if (fillStyle instanceof CanvasPattern) {
            thisSerializer.writeInt8((4).toByte())
            const fillStyleForIdx4  = fillStyle as CanvasPattern
            CanvasPattern_serializer.write(thisSerializer, fillStyleForIdx4)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setFillStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getStrokeStyle_serialize(): string | Color | int32 | CanvasGradient | CanvasPattern {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getStrokeStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferUnionSelector : int32 = retvalDeserializer.readInt8()
        let buffer : string | Color | int32 | CanvasGradient | CanvasPattern | undefined
        if (bufferUnionSelector == (0).toByte()) {
            buffer = (retvalDeserializer.readString() as string)
        } else if (bufferUnionSelector == (1).toByte()) {
            buffer = Color.values()[retvalDeserializer.readInt32()]
        } else if (bufferUnionSelector == (2).toByte()) {
            buffer = retvalDeserializer.readInt32()
        } else if (bufferUnionSelector == (3).toByte()) {
            buffer = (CanvasGradient_serializer.read(retvalDeserializer) as CanvasGradient)
        } else if (bufferUnionSelector == (4).toByte()) {
            buffer = (CanvasPattern_serializer.read(retvalDeserializer) as CanvasPattern)
        } else {
            throw new Error("One of the branches for buffer has to be chosen through deserialisation.")
        }
        const returnResult : string | Color | int32 | CanvasGradient | CanvasPattern = (buffer as string | Color | int32 | CanvasGradient | CanvasPattern)
        return returnResult
    }
    private setStrokeStyle_serialize(strokeStyle: string | Color | int32 | CanvasGradient | CanvasPattern): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (strokeStyle instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const strokeStyleForIdx0  = strokeStyle as string
            thisSerializer.writeString(strokeStyleForIdx0)
        } else if (strokeStyle instanceof Color) {
            thisSerializer.writeInt8((1).toByte())
            const strokeStyleForIdx1  = strokeStyle as Color
            thisSerializer.writeInt32(strokeStyleForIdx1.getOrdinal())
        } else if (strokeStyle instanceof int32) {
            thisSerializer.writeInt8((2).toByte())
            const strokeStyleForIdx2  = strokeStyle as int32
            thisSerializer.writeInt32(strokeStyleForIdx2)
        } else if (strokeStyle instanceof CanvasGradient) {
            thisSerializer.writeInt8((3).toByte())
            const strokeStyleForIdx3  = strokeStyle as CanvasGradient
            CanvasGradient_serializer.write(thisSerializer, strokeStyleForIdx3)
        } else if (strokeStyle instanceof CanvasPattern) {
            thisSerializer.writeInt8((4).toByte())
            const strokeStyleForIdx4  = strokeStyle as CanvasPattern
            CanvasPattern_serializer.write(thisSerializer, strokeStyleForIdx4)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setStrokeStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFilter_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getFilter(this.peer!.ptr)
        return retval
    }
    private setFilter_serialize(filter: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setFilter(this.peer!.ptr, filter)
    }
    private getImageSmoothingEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getImageSmoothingEnabled(this.peer!.ptr)
        return retval
    }
    private setImageSmoothingEnabled_serialize(imageSmoothingEnabled: boolean): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setImageSmoothingEnabled(this.peer!.ptr, imageSmoothingEnabled ? 1 : 0)
    }
    private getImageSmoothingQuality_serialize(): ImageSmoothingQuality {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getImageSmoothingQuality(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setImageSmoothingQuality_serialize(imageSmoothingQuality: ImageSmoothingQuality): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setImageSmoothingQuality(this.peer!.ptr, imageSmoothingQuality)
    }
    private getLineCap_serialize(): CanvasLineCap {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineCap(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setLineCap_serialize(lineCap: CanvasLineCap): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineCap(this.peer!.ptr, lineCap)
    }
    private getLineDashOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineDashOffset(this.peer!.ptr)
        return retval
    }
    private setLineDashOffset_serialize(lineDashOffset: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineDashOffset(this.peer!.ptr, lineDashOffset)
    }
    private getLineJoin_serialize(): CanvasLineJoin {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineJoin(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setLineJoin_serialize(lineJoin: CanvasLineJoin): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineJoin(this.peer!.ptr, lineJoin)
    }
    private getLineWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineWidth(this.peer!.ptr)
        return retval
    }
    private setLineWidth_serialize(lineWidth: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineWidth(this.peer!.ptr, lineWidth)
    }
    private getMiterLimit_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getMiterLimit(this.peer!.ptr)
        return retval
    }
    private setMiterLimit_serialize(miterLimit: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setMiterLimit(this.peer!.ptr, miterLimit)
    }
    private getShadowBlur_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowBlur(this.peer!.ptr)
        return retval
    }
    private setShadowBlur_serialize(shadowBlur: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowBlur(this.peer!.ptr, shadowBlur)
    }
    private getShadowColor_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowColor(this.peer!.ptr)
        return retval
    }
    private setShadowColor_serialize(shadowColor: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowColor(this.peer!.ptr, shadowColor)
    }
    private getShadowOffsetX_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowOffsetX(this.peer!.ptr)
        return retval
    }
    private setShadowOffsetX_serialize(shadowOffsetX: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowOffsetX(this.peer!.ptr, shadowOffsetX)
    }
    private getShadowOffsetY_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowOffsetY(this.peer!.ptr)
        return retval
    }
    private setShadowOffsetY_serialize(shadowOffsetY: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowOffsetY(this.peer!.ptr, shadowOffsetY)
    }
    private getDirection_serialize(): CanvasDirection {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: CanvasDirection): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setDirection(this.peer!.ptr, direction)
    }
    private getFont_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getFont(this.peer!.ptr)
        return retval
    }
    private setFont_serialize(font: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setFont(this.peer!.ptr, font)
    }
    private getTextAlign_serialize(): CanvasTextAlign {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getTextAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setTextAlign_serialize(textAlign: CanvasTextAlign): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTextAlign(this.peer!.ptr, textAlign)
    }
    private getTextBaseline_serialize(): CanvasTextBaseline {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getTextBaseline(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setTextBaseline_serialize(textBaseline: CanvasTextBaseline): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTextBaseline(this.peer!.ptr, textBaseline)
    }
}
export class Path2DInternal {
    public static fromPtr(ptr: KPointer): Path2D {
        return new Path2D(false, false, ptr)
    }
}
export class Path2D extends CanvasPath implements MaterializedBase {
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(false, false, Path2D.construct0())
    }
    constructor(unit: LengthMetricsUnit) {
        this(false, false, Path2D.construct1(unit))
    }
    constructor(path: Path2D) {
        this(false, false, Path2D.construct2(path))
    }
    constructor(path: Path2D, unit: LengthMetricsUnit) {
        this(false, false, Path2D.construct3(path, unit))
    }
    constructor(d: string) {
        this(false, false, Path2D.construct4(d))
    }
    constructor(description: string, unit: LengthMetricsUnit) {
        this(false, false, Path2D.construct5(description, unit))
    }
    static construct0(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct0()
        return retval
    }
    static construct1(unit: LengthMetricsUnit): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct1(unit.valueOf())
        return retval
    }
    static construct2(path: Path2D): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct2(toPeerPtr(path))
        return retval
    }
    static construct3(path: Path2D, unit: LengthMetricsUnit): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct3(toPeerPtr(path), unit.valueOf())
        return retval
    }
    static construct4(d: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct4(d)
        return retval
    }
    static construct5(description: string, unit: LengthMetricsUnit): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_construct5(description, unit.valueOf())
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Path2D_getFinalizer()
    }
    public addPath(path: Path2D, transform?: Matrix2D): void {
        const path_casted = path as (Path2D)
        const transform_casted = transform as (Matrix2D | undefined)
        this.addPath_serialize(path_casted, transform_casted)
        return
    }
    addPath_serialize(path: Path2D, transform?: Matrix2D): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (transform !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transformTmpValue  = transform!
            Matrix2D_serializer.write(thisSerializer, transformTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Path2D_addPath(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class CanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderingContext2D {
        return new CanvasRenderingContext2D(false, false, ptr)
    }
}
export class CanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    get height(): number {
        return this.getHeight()
    }
    set height(height: number) {
        this.setHeight(height)
    }
    get width(): number {
        return this.getWidth()
    }
    set width(width: number) {
        this.setWidth(width)
    }
    get canvas(): FrameNode {
        return this.getCanvas()
    }
    set canvas(canvas: FrameNode) {
        this.setCanvas(canvas)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(settings?: RenderingContextSettings, unit?: LengthMetricsUnit) {
        this(false, false, CanvasRenderingContext2D.construct(settings, unit))
    }
    static construct(settings?: RenderingContextSettings, unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (settings !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const settingsTmpValue  = settings!
            RenderingContextSettings_serializer.write(thisSerializer, settingsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: number): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (number | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        return hookCanvasStartImageAnalyzer(this, config)
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this.stopImageAnalyzer_serialize()
        return
    }
    public onAttach(callback_: VoidCallback): void {
        registerAttach(this, callback_)
        const callback__casted = callback_ as (VoidCallback)
        this.onAttach_serialize(callback__casted)
        return
    }
    public offAttach(callback_?: VoidCallback): void {
        unregisterAttach(this, callback_)
        const callback__casted = callback_ as (VoidCallback | undefined)
        this.offAttach_serialize(callback__casted)
        return
    }
    public onDetach(callback_: VoidCallback): void {
        registerDetach(this, callback_)
        const callback__casted = callback_ as (VoidCallback)
        this.onDetach_serialize(callback__casted)
        return
    }
    public offDetach(callback_?: VoidCallback): void {
        unregisterDetach(this, callback_)
        const callback__casted = callback_ as (VoidCallback | undefined)
        this.offDetach_serialize(callback__casted)
        return
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private setHeight(height: number): void {
        const height_casted = height as (number)
        this.setHeight_serialize(height_casted)
        return
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private setWidth(width: number): void {
        const width_casted = width as (number)
        this.setWidth_serialize(width_casted)
        return
    }
    private getCanvas(): FrameNode {
        return this.getCanvas_serialize()
    }
    private setCanvas(canvas: FrameNode): void {
        const canvas_casted = canvas as (FrameNode)
        this.setCanvas_serialize(canvas_casted)
        return
    }
    toDataURL_serialize(type?: string, quality?: number): string {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = type!
            thisSerializer.writeString(typeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (quality !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const qualityTmpValue  = quality!
            thisSerializer.writeNumber(qualityTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ImageAnalyzerConfig_serializer.write(thisSerializer, config)
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_startImageAnalyzer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_stopImageAnalyzer(this.peer!.ptr)
    }
    onAttach_serialize(callback_: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onAttach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offAttach_serialize(callback_?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offAttach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDetach_serialize(callback_: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onDetach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offDetach_serialize(callback_?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offDetach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getHeight(this.peer!.ptr)
        return retval
    }
    private setHeight_serialize(height: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_setHeight(this.peer!.ptr, height)
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getWidth(this.peer!.ptr)
        return retval
    }
    private setWidth_serialize(width: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_setWidth(this.peer!.ptr, width)
    }
    private getCanvas_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getCanvas(this.peer!.ptr)
        const obj : FrameNode = extractors.fromFrameNodePtr(retval)
        return obj
    }
    private setCanvas_serialize(canvas: FrameNode): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_setCanvas(this.peer!.ptr, extractors.toFrameNodePtr(canvas))
    }
}
export class OffscreenCanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvasRenderingContext2D {
        return new OffscreenCanvasRenderingContext2D(false, false, false, false, ptr)
    }
}
export class OffscreenCanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    constructor(_0: boolean, _1: boolean, _2: boolean, _3: boolean, peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor(width: number, height: number, settings?: RenderingContextSettings, unit?: LengthMetricsUnit) {
        this(false, false, false, false, OffscreenCanvasRenderingContext2D.construct(width, height, settings, unit))
    }
    static construct(width: number, height: number, settings?: RenderingContextSettings, unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (settings !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const settingsTmpValue  = settings!
            RenderingContextSettings_serializer.write(thisSerializer, settingsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (unit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const unitTmpValue  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(unitTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_construct(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: number): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (number | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public transferToImageBitmap(): ImageBitmap {
        return this.transferToImageBitmap_serialize()
    }
    toDataURL_serialize(type?: string, quality?: number): string {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = type!
            thisSerializer.writeString(typeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (quality !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const qualityTmpValue  = quality!
            thisSerializer.writeNumber(qualityTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
}
