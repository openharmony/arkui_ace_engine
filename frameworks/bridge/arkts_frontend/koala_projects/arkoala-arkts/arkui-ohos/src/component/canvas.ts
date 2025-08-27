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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { Matrix2D, Matrix2DInternal } from "./matrix2d"
import { Size } from "./../Graphics"
import { LengthMetricsUnit, LengthMetrics} from "../Graphics"
import { PixelMap } from "#external"
import { ArkUIAniModule } from "arkui.ani"
import { DrawingCanvas, DrawingCanvasInternal } from "./arkui-drawing"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VoidCallback } from "./units"
import { ImageAIOptions, ImageAnalyzerConfig } from "./imageCommon"
import { NodeAttach, remember } from "@koalaui/runtime"
import { FrameNode, FrameNodeInternal } from "../FrameNode"

export class CanvasGradientInternal {
    public static fromPtr(ptr: KPointer): CanvasGradient {
        const obj : CanvasGradient = new CanvasGradient()
        obj.peer = new Finalizable(ptr, CanvasGradient.getFinalizer())
        return obj
    }
}
export class CanvasGradient implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_canvasgradient(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasGradient_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CanvasGradient.ctor_canvasgradient()
        this.peer = new Finalizable(ctorPtr, CanvasGradient.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasGradient_getFinalizer()
    }
    public addColorStop(offset: number, color: string): void {
        const offset_casted = offset as (number)
        const color_casted = color as (string)
        this.addColorStop_serialize(offset_casted, color_casted)
        return
    }
    private addColorStop_serialize(offset: number, color: string): void {
        ArkUIGeneratedNativeModule._CanvasGradient_addColorStop(this.peer!.ptr, offset, color)
    }
}
export class CanvasPathInternal {
    public static fromPtr(ptr: KPointer): CanvasPath {
        const obj : CanvasPath = new CanvasPath()
        obj.peer = new Finalizable(ptr, CanvasPath.getFinalizer())
        return obj
    }
}
export class CanvasPath implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_canvaspath(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasPath_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CanvasPath.ctor_canvaspath()
        this.peer = new Finalizable(ctorPtr, CanvasPath.getFinalizer())
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
    private arc_serialize(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let counterclockwise_type : int32 = RuntimeType.UNDEFINED
        counterclockwise_type = runtimeType(counterclockwise)
        thisSerializer.writeInt8(counterclockwise_type as int32)
        if ((RuntimeType.UNDEFINED) != (counterclockwise_type)) {
            const counterclockwise_value  = counterclockwise!
            thisSerializer.writeBoolean(counterclockwise_value)
        }
        ArkUIGeneratedNativeModule._CanvasPath_arc(this.peer!.ptr, x, y, radius, startAngle, endAngle, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private arcTo_serialize(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_arcTo(this.peer!.ptr, x1, y1, x2, y2, radius)
    }
    private bezierCurveTo_serialize(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_bezierCurveTo(this.peer!.ptr, cp1x, cp1y, cp2x, cp2y, x, y)
    }
    private closePath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasPath_closePath(this.peer!.ptr)
    }
    private ellipse_serialize(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let counterclockwise_type : int32 = RuntimeType.UNDEFINED
        counterclockwise_type = runtimeType(counterclockwise)
        thisSerializer.writeInt8(counterclockwise_type as int32)
        if ((RuntimeType.UNDEFINED) != (counterclockwise_type)) {
            const counterclockwise_value  = counterclockwise!
            thisSerializer.writeBoolean(counterclockwise_value)
        }
        ArkUIGeneratedNativeModule._CanvasPath_ellipse(this.peer!.ptr, x, y, radiusX, radiusY, rotation, startAngle, endAngle, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private lineTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_lineTo(this.peer!.ptr, x, y)
    }
    private moveTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_moveTo(this.peer!.ptr, x, y)
    }
    private quadraticCurveTo_serialize(cpx: number, cpy: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_quadraticCurveTo(this.peer!.ptr, cpx, cpy, x, y)
    }
    private rect_serialize(x: number, y: number, w: number, h: number): void {
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
    static ctor_canvaspattern(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasPattern_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CanvasPatternInternal.ctor_canvaspattern()
        this.peer = new Finalizable(ctorPtr, CanvasPatternInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasPattern_getFinalizer()
    }
    public setTransform(transform?: Matrix2D): void {
        const transform_casted = transform as (Matrix2D | undefined)
        this.setTransform_serialize(transform_casted)
        return
    }
    private setTransform_serialize(transform?: Matrix2D): void {
        const thisSerializer : Serializer = Serializer.hold()
        let transform_type : int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type as int32)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value  = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._CanvasPattern_setTransform(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): CanvasPatternInternal {
        const obj : CanvasPatternInternal = new CanvasPatternInternal()
        obj.peer = new Finalizable(ptr, CanvasPatternInternal.getFinalizer())
        return obj
    }
}
export class ImageBitmapInternal {
    public static fromPtr(ptr: KPointer): ImageBitmap {
        const obj : ImageBitmap = new ImageBitmap(undefined)
        obj.peer = new Finalizable(ptr, ImageBitmap.getFinalizer())
        return obj
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
    get width(): number {
        return this.getWidth()
    }
    static ctor_imagebitmap(src: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_ctor(src)
        return retval
    }
    constructor(src?: string) {
        if ((src) !== (undefined))
        {
            const ctorPtr : KPointer = ImageBitmap.ctor_imagebitmap((src)!)
            this.peer = new Finalizable(ctorPtr, ImageBitmap.getFinalizer())
        }
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
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._ImageBitmap_close(this.peer!.ptr)
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getWidth(this.peer!.ptr)
        return retval
    }
}
export class ImageDataInternal {
    public static fromPtr(ptr: KPointer): ImageData {
        const obj : ImageData = new ImageData(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ImageData.getFinalizer())
        return obj
    }
}
export class ImageData implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get data(): NativeBuffer {
        throw new Error("Not implemented")
    }
    get height(): number {
        return this.getHeight()
    }
    get width(): number {
        return this.getWidth()
    }
    static ctor_imagedata(width: number, height: number, data?: NativeBuffer): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let data_type : int32 = RuntimeType.UNDEFINED
        data_type = runtimeType(data)
        thisSerializer.writeInt8(data_type as int32)
        if ((RuntimeType.UNDEFINED) != (data_type)) {
            const data_value  = data!
            thisSerializer.writeBuffer(data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._ImageData_ctor(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(width?: number, height?: number, data?: NativeBuffer) {
        if (((width) !== (undefined)) || ((height) !== (undefined)) || ((data) !== (undefined)))
        {
            const ctorPtr : KPointer = ImageData.ctor_imagedata((width)!, (height)!, data)
            this.peer = new Finalizable(ctorPtr, ImageData.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageData_getFinalizer()
    }
    private getData(): NativeBuffer {
        return this.getData_serialize()
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private getData_serialize(): NativeBuffer {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getData(this.peer!.ptr)
        return new Deserializer(retval, retval.length as int32).readBuffer()
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageData_getWidth(this.peer!.ptr)
        return retval
    }
}
export class RenderingContextSettingsInternal {
    public static fromPtr(ptr: KPointer): RenderingContextSettings {
        const obj : RenderingContextSettings = new RenderingContextSettings(undefined)
        obj.peer = new Finalizable(ptr, RenderingContextSettings.getFinalizer())
        return obj
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
        const antialias_NonNull  = (antialias as boolean)
        this.setAntialias(antialias_NonNull)
    }
    static ctor_renderingcontextsettings(antialias?: boolean): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let antialias_type : int32 = RuntimeType.UNDEFINED
        antialias_type = runtimeType(antialias)
        thisSerializer.writeInt8(antialias_type as int32)
        if ((RuntimeType.UNDEFINED) != (antialias_type)) {
            const antialias_value  = antialias!
            thisSerializer.writeBoolean(antialias_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(antialias?: boolean) {
        const ctorPtr : KPointer = RenderingContextSettings.ctor_renderingcontextsettings(antialias)
        this.peer = new Finalizable(ctorPtr, RenderingContextSettings.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RenderingContextSettings_getFinalizer()
    }
    private getAntialias(): boolean | undefined {
        return this.getAntialias_serialize()
    }
    private setAntialias(antialias: boolean): void {
        const antialias_casted = antialias as (boolean)
        this.setAntialias_serialize(antialias_casted)
        return
    }
    private getAntialias_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_getAntialias(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setAntialias_serialize(antialias: boolean): void {
        ArkUIGeneratedNativeModule._RenderingContextSettings_setAntialias(this.peer!.ptr, antialias ? 1 : 0)
    }
}
export class OffscreenCanvasInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvas {
        const obj : OffscreenCanvas = new OffscreenCanvas(undefined, undefined)
        obj.peer = new Finalizable(ptr, OffscreenCanvas.getFinalizer())
        return obj
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
    static ctor_offscreencanvas(width: number, height: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_ctor(width, height)
        return retval
    }
    constructor(width?: number, height?: number) {
        if (((width) !== (undefined)) || ((height) !== (undefined)))
        {
            const ctorPtr : KPointer = OffscreenCanvas.ctor_offscreencanvas((width)!, (height)!)
            this.peer = new Finalizable(ctorPtr, OffscreenCanvas.getFinalizer())
        }
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
        throw new Error("TBD")
    }
    private transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
    private getContext2d_serialize(options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRenderingContextSettings(options_value)
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
export class DrawingRenderingContextInternal {
    public static fromPtr(ptr: KPointer): DrawingRenderingContext {
        const obj : DrawingRenderingContext = new DrawingRenderingContext(undefined)
        obj.peer = new Finalizable(ptr, DrawingRenderingContext.getFinalizer())
        return obj
    }
}
export class DrawingRenderingContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get size(): Size {
        throw new Error("Not implemented")
    }
    get canvas(): DrawingCanvas {
        return this.getCanvas()
    }
    static ctor_drawingrenderingcontext(unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let unit_type : int32 = RuntimeType.UNDEFINED
        unit_type = runtimeType(unit)
        thisSerializer.writeInt8(unit_type as int32)
        if ((RuntimeType.UNDEFINED) != (unit_type)) {
            const unit_value  = (unit as LengthMetricsUnit)
            thisSerializer.writeInt32(TypeChecker.LengthMetricsUnit_ToNumeric(unit_value))
        }
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(unit?: LengthMetricsUnit) {
        const ctorPtr : KPointer = DrawingRenderingContext.ctor_drawingrenderingcontext(unit)
        this.peer = new Finalizable(ctorPtr, DrawingRenderingContext.getFinalizer())
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
    private getCanvas(): DrawingCanvas {
        return this.getCanvas_serialize()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._DrawingRenderingContext_invalidate(this.peer!.ptr)
    }
    private getSize_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getSize(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Size = retvalDeserializer.readSize()
        return returnResult
    }
    private getCanvas_serialize(): DrawingCanvas {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getCanvas(this.peer!.ptr)
        const obj : DrawingCanvas = DrawingCanvasInternal.fromPtr(retval)
        return obj
    }
}
export class ArkCanvasPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCanvasPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Canvas_construct(peerId, flags)
        const _peer  = new ArkCanvasPeer(_peerPtr, peerId, "Canvas", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCanvasOptions0Attribute(context?: CanvasRenderingContext2D | DrawingRenderingContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        let context_type : int32 = RuntimeType.UNDEFINED
        context_type = runtimeType(context)
        thisSerializer.writeInt8(context_type as int32)
        if ((RuntimeType.UNDEFINED) != (context_type)) {
            const context_value  = context!
            let context_value_type : int32 = RuntimeType.UNDEFINED
            context_value_type = runtimeType(context_value)
            if (TypeChecker.isCanvasRenderingContext2D(context_value, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const context_value_0  = context_value as CanvasRenderingContext2D
                thisSerializer.writeCanvasRenderingContext2D(context_value_0)
            }
            else if (TypeChecker.isDrawingRenderingContext(context_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const context_value_1  = context_value as DrawingRenderingContext
                thisSerializer.writeDrawingRenderingContext(context_value_1)
            }
        }
        ArkUIGeneratedNativeModule._CanvasInterface_setCanvasOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCanvasOptions1Attribute(context: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions: ImageAIOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let context_type : int32 = RuntimeType.UNDEFINED
        context_type = runtimeType(context)
        if (TypeChecker.isCanvasRenderingContext2D(context, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const context_0  = context as CanvasRenderingContext2D
            thisSerializer.writeCanvasRenderingContext2D(context_0)
        }
        else if (TypeChecker.isDrawingRenderingContext(context, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const context_1  = context as DrawingRenderingContext
            thisSerializer.writeDrawingRenderingContext(context_1)
        }
        thisSerializer.writeImageAIOptions(imageAIOptions)
        ArkUIGeneratedNativeModule._CanvasInterface_setCanvasOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CanvasAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CanvasAttribute_enableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    actualBoundingBoxAscent: number;
    actualBoundingBoxDescent: number;
    actualBoundingBoxLeft: number;
    actualBoundingBoxRight: number;
    alphabeticBaseline: number;
    emHeightAscent: number;
    emHeightDescent: number;
    fontBoundingBoxAscent: number;
    fontBoundingBoxDescent: number;
    hangingBaseline: number;
    ideographicBaseline: number;
    width: number;
    height: number;
}
export interface CanvasAttribute extends CommonMethod {
    onReady(value: VoidCallback | undefined): this
    enableAnalyzer(value: boolean | undefined): this
}
export class ArkCanvasStyle extends ArkCommonMethodStyle implements CanvasAttribute {
    onReady_value?: VoidCallback | undefined
    enableAnalyzer_value?: boolean | undefined
    public onReady(value: VoidCallback | undefined): this {
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        return this
    }
}
export class ArkCanvasComponent extends ArkCommonMethodComponent implements CanvasAttribute {
    getPeer(): ArkCanvasPeer {
        return (this.peer as ArkCanvasPeer)
    }
    public setCanvasOptions(context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setCanvasOptions")) {
            const context_type = runtimeType(context)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if ((RuntimeType.OBJECT == context_type) || (RuntimeType.OBJECT == context_type) || (RuntimeType.UNDEFINED == context_type)) {
                const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext | undefined)
                this.getPeer()?.setCanvasOptions0Attribute(context_casted)
                return this
            }
            if ((TypeChecker.isCanvasRenderingContext2D(context, false, false, false)) || (TypeChecker.isDrawingRenderingContext(context, false, false))) {
                const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setCanvasOptions1Attribute(context_casted, imageAIOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onReady(value: VoidCallback | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onReadyAttribute(value_casted)
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
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Canvas(
    /** @memo */
    style: ((attributes: CanvasAttribute) => void) | undefined,
    context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkCanvasComponent()
    })
    NodeAttach<ArkCanvasPeer>((): ArkCanvasPeer => ArkCanvasPeer.create(receiver), (_: ArkCanvasPeer) => {
        receiver.setCanvasOptions(context,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class Path2DInternal {
    public static fromPtr(ptr: KPointer): Path2D {
        const obj : Path2D = new Path2D()
        obj.peer = new Finalizable(ptr, Path2D.getFinalizer())
        return obj
    }
}
export class Path2D extends CanvasPath implements MaterializedBase {
    static ctor_path2d(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = Path2D.ctor_path2d()
        this.peer = new Finalizable(ctorPtr, Path2D.getFinalizer())
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
    private addPath_serialize(path: Path2D, transform?: Matrix2D): void {
        const thisSerializer : Serializer = Serializer.hold()
        let transform_type : int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type as int32)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value  = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._Path2D_addPath(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class CanvasRendererInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderer {
        const obj : CanvasRenderer = new CanvasRenderer()
        obj.peer = new Finalizable(ptr, CanvasRenderer.getFinalizer())
        return obj
    }
}
export class CanvasRenderer extends CanvasPath implements MaterializedBase {
    get letterSpacing(): LengthMetrics | string {
        throw new Error("Not implemented")
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
    get fillStyle(): string | number | CanvasGradient | CanvasPattern {
        throw new Error("Not implemented")
    }
    set fillStyle(fillStyle: string | number | CanvasGradient | CanvasPattern) {
        this.setFillStyle(fillStyle)
    }
    get strokeStyle(): string | number | CanvasGradient | CanvasPattern {
        throw new Error("Not implemented")
    }
    set strokeStyle(strokeStyle: string | number | CanvasGradient | CanvasPattern) {
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
    static ctor_canvasrenderer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = CanvasRenderer.ctor_canvasrenderer()
        this.peer = new Finalizable(ctorPtr, CanvasRenderer.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderer_getFinalizer()
    }
    public drawImage(image: ImageBitmap | PixelMap, sx: number, sy: number, sw?: number, sh?: number, dx?: number, dy?: number, dw?: number, dh?: number): void {
        const image_type = runtimeType(image)
        const sx_type = runtimeType(sx)
        const sy_type = runtimeType(sy)
        const sw_type = runtimeType(sw)
        const sh_type = runtimeType(sh)
        const dx_type = runtimeType(dx)
        const dy_type = runtimeType(dy)
        const dw_type = runtimeType(dw)
        const dh_type = runtimeType(dh)
        if ((TypeChecker.isImageBitmap(image, false, false)) || (TypeChecker.isPixelMap(image, false, false))) {
            const image_casted = image as (ImageBitmap | PixelMap)
            const dx_casted = sx as (number)
            const dy_casted = sy as (number)
            this.drawImage0_serialize(image_casted, dx_casted, dy_casted)
            return
        }
        if ((TypeChecker.isImageBitmap(image, false, false)) || (TypeChecker.isPixelMap(image, false, false))) {
            const image_casted = image as (ImageBitmap | PixelMap)
            const dx_casted = sx as (number)
            const dy_casted = sy as (number)
            const dw_casted = sw as (number)
            const dh_casted = sh as (number)
            this.drawImage1_serialize(image_casted, dx_casted, dy_casted, dw_casted, dh_casted)
            return
        }
        if ((TypeChecker.isImageBitmap(image, false, false)) || (TypeChecker.isPixelMap(image, false, false))) {
            const image_casted = image as (ImageBitmap | PixelMap)
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
        throw new Error("Can not select appropriate overload")
    }
    public beginPath(): void {
        this.beginPath_serialize()
        return
    }
    public clip(path?: CanvasFillRule | undefined | Path2D, fillRule?: CanvasFillRule): void {
        const path_type = runtimeType(path)
        const fillRule_type = runtimeType(fillRule)
        if (((RuntimeType.STRING == path_type) || (RuntimeType.UNDEFINED == path_type)) && (RuntimeType.UNDEFINED == fillRule_type)) {
            const fillRule_casted = path as (CanvasFillRule | undefined)
            this.clip0_serialize(fillRule_casted)
            return
        }
        if ((RuntimeType.OBJECT == path_type) && ((RuntimeType.STRING == fillRule_type) || (RuntimeType.UNDEFINED == fillRule_type))) {
            const path_casted = path as (Path2D)
            const fillRule_casted = fillRule as (CanvasFillRule | undefined)
            this.clip1_serialize(path_casted, fillRule_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public fill(path?: CanvasFillRule | undefined | Path2D, fillRule?: CanvasFillRule): void {
        const path_type = runtimeType(path)
        const fillRule_type = runtimeType(fillRule)
        if (((RuntimeType.STRING == path_type) || (RuntimeType.UNDEFINED == path_type)) && (RuntimeType.UNDEFINED == fillRule_type)) {
            const fillRule_casted = path as (CanvasFillRule | undefined)
            this.fill0_serialize(fillRule_casted)
            return
        }
        if ((RuntimeType.OBJECT == path_type) && ((RuntimeType.STRING == fillRule_type) || (RuntimeType.UNDEFINED == fillRule_type))) {
            const path_casted = path as (Path2D)
            const fillRule_casted = fillRule as (CanvasFillRule | undefined)
            this.fill1_serialize(path_casted, fillRule_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public stroke(path?: Path2D): void {
        const path_type = runtimeType(path)
        this.stroke0_serialize()
        return
    }
    public createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const x0_casted = x0 as (number)
        const y0_casted = y0 as (number)
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        return this.createLinearGradient_serialize(x0_casted, y0_casted, x1_casted, y1_casted)
    }
    public createPattern(image: ImageBitmap, repetition: string | undefined): CanvasPattern | undefined {
        const image_casted = image as (ImageBitmap)
        const repetition_casted = repetition as (string | undefined)
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
    public createImageData(sw: ImageData | number, sh?: number): ImageData {
        const sw_type = runtimeType(sw)
        const sh_type = runtimeType(sh)
        if (RuntimeType.OBJECT == sw_type) {
            const imagedata_casted = sw as (ImageData)
            return this.createImageData1_serialize(imagedata_casted)
        }
        if (RuntimeType.NUMBER == sw_type) {
            const sw_casted = sw as (number)
            const sh_casted = sh as (number)
            return this.createImageData0_serialize(sw_casted, sh_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public getImageData(sx: number, sy: number, sw: number, sh: number): ImageData {
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        return this.getImageData_serialize(sx_casted, sy_casted, sw_casted, sh_casted)
    }
    public getPixelMap(sx: number, sy: number, sw: number, sh: number): PixelMap {
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        return this.getPixelMap_serialize(sx_casted, sy_casted, sw_casted, sh_casted)
    }
    public putImageData(imagedata: ImageData, dx: number | string, dy: number | string, dirtyX?: number | string, dirtyY?: number | string, dirtyWidth?: number | string, dirtyHeight?: number | string): void {
        const imagedata_type = runtimeType(imagedata)
        const dx_type = runtimeType(dx)
        const dy_type = runtimeType(dy)
        const dirtyX_type = runtimeType(dirtyX)
        const dirtyY_type = runtimeType(dirtyY)
        const dirtyWidth_type = runtimeType(dirtyWidth)
        const dirtyHeight_type = runtimeType(dirtyHeight)
        if (((RuntimeType.NUMBER == dx_type) || (RuntimeType.STRING == dx_type)) && ((RuntimeType.NUMBER == dy_type) || (RuntimeType.STRING == dy_type)) && (RuntimeType.UNDEFINED == dirtyX_type) && (RuntimeType.UNDEFINED == dirtyY_type) && (RuntimeType.UNDEFINED == dirtyWidth_type) && (RuntimeType.UNDEFINED == dirtyHeight_type)) {
            const imagedata_casted = imagedata as (ImageData)
            const dx_casted = dx as (number | string)
            const dy_casted = dy as (number | string)
            this.putImageData0_serialize(imagedata_casted, dx_casted, dy_casted)
            return
        }
        if (((RuntimeType.NUMBER == dx_type) || (RuntimeType.STRING == dx_type)) && ((RuntimeType.NUMBER == dy_type) || (RuntimeType.STRING == dy_type)) && ((RuntimeType.NUMBER == dirtyX_type) || (RuntimeType.STRING == dirtyX_type)) && ((RuntimeType.NUMBER == dirtyY_type) || (RuntimeType.STRING == dirtyY_type)) && ((RuntimeType.NUMBER == dirtyWidth_type) || (RuntimeType.STRING == dirtyWidth_type)) && ((RuntimeType.NUMBER == dirtyHeight_type) || (RuntimeType.STRING == dirtyHeight_type))) {
            const imagedata_casted = imagedata as (ImageData)
            const dx_casted = dx as (number | string)
            const dy_casted = dy as (number | string)
            const dirtyX_casted = dirtyX as (number | string)
            const dirtyY_casted = dirtyY as (number | string)
            const dirtyWidth_casted = dirtyWidth as (number | string)
            const dirtyHeight_casted = dirtyHeight as (number | string)
            this.putImageData1_serialize(imagedata_casted, dx_casted, dy_casted, dirtyX_casted, dirtyY_casted, dirtyWidth_casted, dirtyHeight_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
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
    public setTransform(a?: Matrix2D | undefined | number, b?: number, c?: number, d?: number, e?: number, f?: number): void {
        const a_type = runtimeType(a)
        const b_type = runtimeType(b)
        const c_type = runtimeType(c)
        const d_type = runtimeType(d)
        const e_type = runtimeType(e)
        const f_type = runtimeType(f)
        if ((RuntimeType.OBJECT == a_type) || (RuntimeType.UNDEFINED == a_type)) {
            const transform_casted = a as (Matrix2D | undefined)
            this.setTransform1_serialize(transform_casted)
            return
        }
        if (RuntimeType.NUMBER == a_type) {
            const a_casted = a as (number)
            const b_casted = b as (number)
            const c_casted = c as (number)
            const d_casted = d as (number)
            const e_casted = e as (number)
            const f_casted = f as (number)
            this.setTransform0_serialize(a_casted, b_casted, c_casted, d_casted, e_casted, f_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
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
    public setPixelMap(value?: PixelMap): void {
        const value_casted = value as (PixelMap | undefined)
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
    private getFillStyle(): string | number | CanvasGradient | CanvasPattern {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: string | number | CanvasGradient | CanvasPattern): void {
        const fillStyle_casted = fillStyle as (string | number | CanvasGradient | CanvasPattern)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getStrokeStyle(): string | number | CanvasGradient | CanvasPattern {
        return this.getStrokeStyle_serialize()
    }
    private setStrokeStyle(strokeStyle: string | number | CanvasGradient | CanvasPattern): void {
        const strokeStyle_casted = strokeStyle as (string | number | CanvasGradient | CanvasPattern)
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
    private drawImage0_serialize(image: ImageBitmap | PixelMap, dx: number, dy: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let image_type : int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (TypeChecker.isImageBitmap(image, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const image_0  = image as ImageBitmap
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (TypeChecker.isPixelMap(image, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const pixelMap = image as PixelMap
            let ptr = ArkUIAniModule._ConvertUtils_ConvertFromPixelMapAni(pixelMap)
            const ptr_value: KPointer  = ptr as KPointer
            thisSerializer.writePointer(ptr_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy)
        thisSerializer.release()
    }
    private drawImage1_serialize(image: ImageBitmap | PixelMap, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let image_type : int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (TypeChecker.isImageBitmap(image, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const image_0  = image as ImageBitmap
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (TypeChecker.isPixelMap(image, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const pixelMap = image as PixelMap
            let ptr = ArkUIAniModule._ConvertUtils_ConvertFromPixelMapAni(pixelMap)
            const ptr_value: KPointer  = ptr as KPointer
            thisSerializer.writePointer(ptr_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy, dw, dh)
        thisSerializer.release()
    }
    private drawImage2_serialize(image: ImageBitmap | PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let image_type : int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (TypeChecker.isImageBitmap(image, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const image_0  = image as ImageBitmap
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (TypeChecker.isPixelMap(image, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const pixelMap = image as PixelMap
            let ptr = ArkUIAniModule._ConvertUtils_ConvertFromPixelMapAni(pixelMap)
            const ptr_value: KPointer  = ptr as KPointer
            thisSerializer.writePointer(ptr_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage2(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), sx, sy, sw, sh, dx, dy, dw, dh)
        thisSerializer.release()
    }
    private beginPath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_beginPath(this.peer!.ptr)
    }
    private clip0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer : Serializer = Serializer.hold()
        let fillRule_type : int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value  = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private clip1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer : Serializer = Serializer.hold()
        let fillRule_type : int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value  = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private fill0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer : Serializer = Serializer.hold()
        let fillRule_type : int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value  = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private fill1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer : Serializer = Serializer.hold()
        let fillRule_type : int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value  = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stroke0_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_stroke0(this.peer!.ptr)
    }
    private stroke1_serialize(path: Path2D): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_stroke1(this.peer!.ptr, toPeerPtr(path))
    }
    private createLinearGradient_serialize(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createLinearGradient(this.peer!.ptr, x0, y0, x1, y1)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createPattern_serialize(image: ImageBitmap, repetition: string | undefined): CanvasPattern | undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let repetition_type : int32 = RuntimeType.UNDEFINED
        repetition_type = runtimeType(repetition)
        thisSerializer.writeInt8(repetition_type as int32)
        if ((RuntimeType.UNDEFINED) != (repetition_type)) {
            const repetition_value  = repetition!
            thisSerializer.writeString(repetition_value)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createPattern(this.peer!.ptr, toPeerPtr(image), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    private createRadialGradient_serialize(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createRadialGradient(this.peer!.ptr, x0, y0, r0, x1, y1, r1)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createConicGradient_serialize(startAngle: number, x: number, y: number): CanvasGradient {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createConicGradient(this.peer!.ptr, startAngle, x, y)
        const obj : CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createImageData0_serialize(sw: number, sh: number): ImageData {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createImageData0(this.peer!.ptr, sw, sh)
        const obj : ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private createImageData1_serialize(imagedata: ImageData): ImageData {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_createImageData1(this.peer!.ptr, toPeerPtr(imagedata))
        const obj : ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private getImageData_serialize(sx: number, sy: number, sw: number, sh: number): ImageData {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getImageData(this.peer!.ptr, sx, sy, sw, sh)
        const obj : ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private getPixelMap_serialize(sx: number, sy: number, sw: number, sh: number): PixelMap {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getPixelMap(this.peer!.ptr, sx, sy, sw, sh)
        const ptr : KPointer = retval as KPointer
        const obj : PixelMap = ArkUIAniModule._ConvertUtils_ConvertToPixelMapAni(ptr)
        return obj
    }
    private putImageData0_serialize(imagedata: ImageData, dx: number | string, dy: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let dx_type : int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(0 as int32)
            const dx_0  = dx as number
            thisSerializer.writeNumber(dx_0)
        }
        else if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8(1 as int32)
            const dx_1  = dx as string
            thisSerializer.writeString(dx_1)
        }
        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(0 as int32)
            const dy_0  = dy as number
            thisSerializer.writeNumber(dy_0)
        }
        else if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(1 as int32)
            const dy_1  = dy as string
            thisSerializer.writeString(dy_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_putImageData0(this.peer!.ptr, toPeerPtr(imagedata), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private putImageData1_serialize(imagedata: ImageData, dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let dx_type : int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(0 as int32)
            const dx_0  = dx as number
            thisSerializer.writeNumber(dx_0)
        }
        else if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8(1 as int32)
            const dx_1  = dx as string
            thisSerializer.writeString(dx_1)
        }
        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(0 as int32)
            const dy_0  = dy as number
            thisSerializer.writeNumber(dy_0)
        }
        else if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(1 as int32)
            const dy_1  = dy as string
            thisSerializer.writeString(dy_1)
        }
        let dirtyX_type : int32 = RuntimeType.UNDEFINED
        dirtyX_type = runtimeType(dirtyX)
        if (RuntimeType.NUMBER == dirtyX_type) {
            thisSerializer.writeInt8(0 as int32)
            const dirtyX_0  = dirtyX as number
            thisSerializer.writeNumber(dirtyX_0)
        }
        else if (RuntimeType.STRING == dirtyX_type) {
            thisSerializer.writeInt8(1 as int32)
            const dirtyX_1  = dirtyX as string
            thisSerializer.writeString(dirtyX_1)
        }
        let dirtyY_type : int32 = RuntimeType.UNDEFINED
        dirtyY_type = runtimeType(dirtyY)
        if (RuntimeType.NUMBER == dirtyY_type) {
            thisSerializer.writeInt8(0 as int32)
            const dirtyY_0  = dirtyY as number
            thisSerializer.writeNumber(dirtyY_0)
        }
        else if (RuntimeType.STRING == dirtyY_type) {
            thisSerializer.writeInt8(1 as int32)
            const dirtyY_1  = dirtyY as string
            thisSerializer.writeString(dirtyY_1)
        }
        let dirtyWidth_type : int32 = RuntimeType.UNDEFINED
        dirtyWidth_type = runtimeType(dirtyWidth)
        if (RuntimeType.NUMBER == dirtyWidth_type) {
            thisSerializer.writeInt8(0 as int32)
            const dirtyWidth_0  = dirtyWidth as number
            thisSerializer.writeNumber(dirtyWidth_0)
        }
        else if (RuntimeType.STRING == dirtyWidth_type) {
            thisSerializer.writeInt8(1 as int32)
            const dirtyWidth_1  = dirtyWidth as string
            thisSerializer.writeString(dirtyWidth_1)
        }
        let dirtyHeight_type : int32 = RuntimeType.UNDEFINED
        dirtyHeight_type = runtimeType(dirtyHeight)
        if (RuntimeType.NUMBER == dirtyHeight_type) {
            thisSerializer.writeInt8(0 as int32)
            const dirtyHeight_0  = dirtyHeight as number
            thisSerializer.writeNumber(dirtyHeight_0)
        }
        else if (RuntimeType.STRING == dirtyHeight_type) {
            thisSerializer.writeInt8(1 as int32)
            const dirtyHeight_1  = dirtyHeight as string
            thisSerializer.writeString(dirtyHeight_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_putImageData1(this.peer!.ptr, toPeerPtr(imagedata), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getLineDash_serialize(): Array<number> {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLineDash(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    private setLineDash_serialize(segments: Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(segments.length as int32)
        for (let i = 0; i < segments.length; i++) {
            const segments_element : number = segments[i]
            thisSerializer.writeNumber(segments_element)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineDash(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private clearRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_clearRect(this.peer!.ptr, x, y, w, h)
    }
    private fillRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_fillRect(this.peer!.ptr, x, y, w, h)
    }
    private strokeRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeRect(this.peer!.ptr, x, y, w, h)
    }
    private restore_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restore(this.peer!.ptr)
    }
    private save_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_save(this.peer!.ptr)
    }
    private fillText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let maxWidth_type : int32 = RuntimeType.UNDEFINED
        maxWidth_type = runtimeType(maxWidth)
        thisSerializer.writeInt8(maxWidth_type as int32)
        if ((RuntimeType.UNDEFINED) != (maxWidth_type)) {
            const maxWidth_value  = maxWidth!
            thisSerializer.writeNumber(maxWidth_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fillText(this.peer!.ptr, text, x, y, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private measureText_serialize(text: string): TextMetrics {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_measureText(this.peer!.ptr, text)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : TextMetrics = retvalDeserializer.readTextMetrics()
        return returnResult
    }
    private strokeText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let maxWidth_type : int32 = RuntimeType.UNDEFINED
        maxWidth_type = runtimeType(maxWidth)
        thisSerializer.writeInt8(maxWidth_type as int32)
        if ((RuntimeType.UNDEFINED) != (maxWidth_type)) {
            const maxWidth_value  = maxWidth!
            thisSerializer.writeNumber(maxWidth_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeText(this.peer!.ptr, text, x, y, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTransform_serialize(): Matrix2D {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getTransform(this.peer!.ptr)
        const obj : Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private resetTransform_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_resetTransform(this.peer!.ptr)
    }
    private rotate_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_rotate(this.peer!.ptr, angle)
    }
    private scale_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_scale(this.peer!.ptr, x, y)
    }
    private setTransform0_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform0(this.peer!.ptr, a, b, c, d, e, f)
    }
    private setTransform1_serialize(transform?: Matrix2D): void {
        const thisSerializer : Serializer = Serializer.hold()
        let transform_type : int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type as int32)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value  = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private transform_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transform(this.peer!.ptr, a, b, c, d, e, f)
    }
    private translate_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_translate(this.peer!.ptr, x, y)
    }
    private setPixelMap_serialize(value?: PixelMap): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const pixelMap = value as PixelMap
            let ptr = ArkUIAniModule._ConvertUtils_ConvertFromPixelMapAni(pixelMap)
            const ptr_value: KPointer  = ptr as KPointer
            thisSerializer.writePointer(ptr_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setPixelMap(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private transferFromImageBitmap_serialize(bitmap: ImageBitmap): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transferFromImageBitmap(this.peer!.ptr, toPeerPtr(bitmap))
    }
    private saveLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_saveLayer(this.peer!.ptr)
    }
    private restoreLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restoreLayer(this.peer!.ptr)
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_reset(this.peer!.ptr)
    }
    private getLetterSpacing_serialize(): LengthMetrics | string {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getLetterSpacing(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setLetterSpacing_serialize(letterSpacing: LengthMetrics | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let letterSpacing_type : int32 = RuntimeType.UNDEFINED
        letterSpacing_type = runtimeType(letterSpacing)
        if (RuntimeType.OBJECT == letterSpacing_type) {
            thisSerializer.writeInt8(0 as int32)
            const letterSpacing_0  = letterSpacing as LengthMetrics
            thisSerializer.writeLengthMetrics(letterSpacing_0)
        }
        else if (RuntimeType.STRING == letterSpacing_type) {
            thisSerializer.writeInt8(1 as int32)
            const letterSpacing_1  = letterSpacing as string
            thisSerializer.writeString(letterSpacing_1)
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
    private getFillStyle_serialize(): string | number | CanvasGradient | CanvasPattern {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getFillStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setFillStyle_serialize(fillStyle: string | number | CanvasGradient | CanvasPattern): void {
        const thisSerializer : Serializer = Serializer.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        if (RuntimeType.STRING == fillStyle_type) {
            thisSerializer.writeInt8(0 as int32)
            const fillStyle_0  = fillStyle as string
            thisSerializer.writeString(fillStyle_0)
        }
        else if (RuntimeType.NUMBER == fillStyle_type) {
            thisSerializer.writeInt8(1 as int32)
            const fillStyle_1  = fillStyle as number
            thisSerializer.writeNumber(fillStyle_1)
        }
        else if (TypeChecker.isCanvasGradient(fillStyle)) {
            thisSerializer.writeInt8(2 as int32)
            const fillStyle_2  = fillStyle as CanvasGradient
            thisSerializer.writeCanvasGradient(fillStyle_2)
        }
        else if (TypeChecker.isCanvasPattern(fillStyle)) {
            thisSerializer.writeInt8(3 as int32)
            const fillStyle_3  = fillStyle as CanvasPattern
            thisSerializer.writeCanvasPattern(fillStyle_3)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setFillStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getStrokeStyle_serialize(): string | number | CanvasGradient | CanvasPattern {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderer_getStrokeStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStrokeStyle_serialize(strokeStyle: string | number | CanvasGradient | CanvasPattern): void {
        const thisSerializer : Serializer = Serializer.hold()
        let strokeStyle_type : int32 = RuntimeType.UNDEFINED
        strokeStyle_type = runtimeType(strokeStyle)
        if (RuntimeType.STRING == strokeStyle_type) {
            thisSerializer.writeInt8(0 as int32)
            const strokeStyle_0  = strokeStyle as string
            thisSerializer.writeString(strokeStyle_0)
        }
        else if (RuntimeType.NUMBER == strokeStyle_type) {
            thisSerializer.writeInt8(1 as int32)
            const strokeStyle_1  = strokeStyle as number
            thisSerializer.writeNumber(strokeStyle_1)
        }
        else if (TypeChecker.isCanvasGradient(strokeStyle)) {
            thisSerializer.writeInt8(2 as int32)
            const strokeStyle_2  = strokeStyle as CanvasGradient
            thisSerializer.writeCanvasGradient(strokeStyle_2)
        }
        else if (TypeChecker.isCanvasPattern(strokeStyle)) {
            thisSerializer.writeInt8(3 as int32)
            const strokeStyle_3  = strokeStyle as CanvasPattern
            thisSerializer.writeCanvasPattern(strokeStyle_3)
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
export class CanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderingContext2D {
        const obj : CanvasRenderingContext2D = new CanvasRenderingContext2D(undefined)
        obj.peer = new Finalizable(ptr, CanvasRenderingContext2D.getFinalizer())
        return obj
    }
}
export class CanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    get height(): number {
        return this.getHeight()
    }
    get width(): number {
        return this.getWidth()
    }
    get canvas(): FrameNode {
        return this.getCanvas()
    }
    static ctor_canvasrenderingcontext2d(settings?: RenderingContextSettings): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let settings_type : int32 = RuntimeType.UNDEFINED
        settings_type = runtimeType(settings)
        thisSerializer.writeInt8(settings_type as int32)
        if ((RuntimeType.UNDEFINED) != (settings_type)) {
            const settings_value  = settings!
            thisSerializer.writeRenderingContextSettings(settings_value)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(settings?: RenderingContextSettings) {
        super()
        const ctorPtr : KPointer = CanvasRenderingContext2D.ctor_canvasrenderingcontext2d(settings)
        this.peer = new Finalizable(ctorPtr, CanvasRenderingContext2D.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: float32): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (float32 | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this.stopImageAnalyzer_serialize()
        return
    }
    public onOnAttach(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this.onOnAttach_serialize(callback__casted)
        return
    }
    public onOnDetach(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this.onOnDetach_serialize(callback__casted)
        return
    }
    public offOnAttach(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.offOnAttach_serialize(callback__casted)
        return
    }
    public offOnDetach(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this.offOnDetach_serialize(callback__casted)
        return
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private getCanvas(): FrameNode {
        return this.getCanvas_serialize()
    }
    on(type: string, callback_: (() => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: (() => void)): void {
        throw new Error("TBD")
    }
    private toDataURL_serialize(type?: string, quality?: float32): string {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = type!
            thisSerializer.writeString(type_value)
        }
        let quality_type : int32 = RuntimeType.UNDEFINED
        quality_type = runtimeType(quality)
        thisSerializer.writeInt8(quality_type as int32)
        if ((RuntimeType.UNDEFINED) != (quality_type)) {
            const quality_value  = quality!
            thisSerializer.writeFloat32(quality_value)
        }
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(config)
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_startImageAnalyzer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_stopImageAnalyzer(this.peer!.ptr)
    }
    private onOnAttach_serialize(callback_: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onOnAttach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onOnDetach_serialize(callback_: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onOnDetach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offOnAttach_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offOnAttach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offOnDetach_serialize(callback_?: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offOnDetach(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getWidth(this.peer!.ptr)
        return retval
    }
    private getCanvas_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getCanvas(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
}
export class OffscreenCanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvasRenderingContext2D {
        const obj : OffscreenCanvasRenderingContext2D = new OffscreenCanvasRenderingContext2D(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, OffscreenCanvasRenderingContext2D.getFinalizer())
        return obj
    }
}
export class OffscreenCanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    static ctor_offscreencanvasrenderingcontext2d(width: number, height: number, settings?: RenderingContextSettings): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let settings_type : int32 = RuntimeType.UNDEFINED
        settings_type = runtimeType(settings)
        thisSerializer.writeInt8(settings_type as int32)
        if ((RuntimeType.UNDEFINED) != (settings_type)) {
            const settings_value  = settings!
            thisSerializer.writeRenderingContextSettings(settings_value)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_ctor(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(width?: number, height?: number, settings?: RenderingContextSettings) {
        super()
        if (((width) !== (undefined)) || ((height) !== (undefined)) || ((settings) !== (undefined)))
        {
            const ctorPtr : KPointer = OffscreenCanvasRenderingContext2D.ctor_offscreencanvasrenderingcontext2d((width)!, (height)!, settings)
            this.peer = new Finalizable(ctorPtr, OffscreenCanvasRenderingContext2D.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: float32): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (float32 | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public transferToImageBitmap(): ImageBitmap {
        return this.transferToImageBitmap_serialize()
    }
    private toDataURL_serialize(type?: string, quality?: float32): string {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = type!
            thisSerializer.writeString(type_value)
        }
        let quality_type : int32 = RuntimeType.UNDEFINED
        quality_type = runtimeType(quality)
        thisSerializer.writeInt8(quality_type as int32)
        if ((RuntimeType.UNDEFINED) != (quality_type)) {
            const quality_value  = quality!
            thisSerializer.writeFloat32(quality_value)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
}
