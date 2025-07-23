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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { ResourceColor, Edges, BorderRadiuses } from "./../component/units"
import { Color, BorderStyle } from "./../component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { drawing } from "./ohos.graphics.drawing"
import { common2D_Rect_serializer, common2D } from "./ohos.graphics.common2D"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { GlobalScope } from "./GlobalScope"
export class ColorMetricsInternal {
    public static fromPtr(ptr: KPointer): ColorMetrics {
        return new ColorMetrics(ptr)
    }
}
export class ColorMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorMetrics.getFinalizer())
    }
    constructor() {
        this(ColorMetrics.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorMetrics_getFinalizer()
    }
    private static numeric_serialize(value: number): ColorMetrics {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_numeric(value)
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static rgba_serialize(red: number, green: number, blue: number, alpha: number): ColorMetrics {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_rgba(red, green, blue, alpha)
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resourceColor_serialize(color: ResourceColor): ColorMetrics {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_resourceColor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    public static numeric(value: number): ColorMetrics {
        const value_casted = value as (number)
        return ColorMetrics.numeric_serialize(value_casted)
    }
    public static rgba(red: number, green: number, blue: number, alpha: number): ColorMetrics {
        const red_casted = red as (number)
        const green_casted = green as (number)
        const blue_casted = blue as (number)
        const alpha_casted = alpha as (number)
        return ColorMetrics.rgba_serialize(red_casted, green_casted, blue_casted, alpha_casted)
    }
    public static resourceColor(color: ResourceColor): ColorMetrics {
        const color_casted = color as (ResourceColor)
        return ColorMetrics.resourceColor_serialize(color_casted)
    }
    public blendColor(overlayColor: ColorMetrics): ColorMetrics {
        const overlayColor_casted = overlayColor as (ColorMetrics)
        return this.blendColor_serialize(overlayColor_casted)
    }
    public color(): string {
        return this.color_serialize()
    }
    public red(): number {
        return this.red_serialize()
    }
    public green(): number {
        return this.green_serialize()
    }
    public blue(): number {
        return this.blue_serialize()
    }
    public alpha(): number {
        return this.alpha_serialize()
    }
    private blendColor_serialize(overlayColor: ColorMetrics): ColorMetrics {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_blendColor(this.peer!.ptr, toPeerPtr(overlayColor))
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private color_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_color(this.peer!.ptr)
        return retval
    }
    private red_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_red(this.peer!.ptr)
        return retval
    }
    private green_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_green(this.peer!.ptr)
        return retval
    }
    private blue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_blue(this.peer!.ptr)
        return retval
    }
    private alpha_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_alpha(this.peer!.ptr)
        return retval
    }
}
export class DrawContextInternal {
    public static fromPtr(ptr: KPointer): DrawContext {
        return new DrawContext(ptr)
    }
}
export class DrawContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DrawContext.getFinalizer())
    }
    constructor() {
        this(DrawContext.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawContext_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawContext_getFinalizer()
    }
    public size(): Size {
        return this.size_serialize()
    }
    public sizeInPixel(): Size {
        return this.sizeInPixel_serialize()
    }
    public canvas(): drawing.Canvas {
        return this.canvas_serialize()
    }
    private size_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._DrawContext_size(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    private sizeInPixel_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._DrawContext_sizeInPixel(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    private canvas_serialize(): drawing.Canvas {
        const retval  = ArkUIGeneratedNativeModule._DrawContext_canvas(this.peer!.ptr)
        const obj : drawing.Canvas = drawing.CanvasInternal.fromPtr(retval)
        return obj
    }
}
export class LengthMetricsInternal {
    public static fromPtr(ptr: KPointer): LengthMetrics {
        return new LengthMetrics(false, false, ptr)
    }
}
export class LengthMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get unit(): LengthUnit {
        return this.getUnit()
    }
    set unit(unit: LengthUnit) {
        this.setUnit(unit)
    }
    get value(): number {
        return this.getValue()
    }
    set value(value: number) {
        this.setValue(value)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LengthMetrics.getFinalizer())
    }
    constructor(value: number, unit: LengthUnit) {
        this(false, false, LengthMetrics.construct(value, unit))
    }
    static construct(value: number, unit: LengthUnit): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_construct(value, TypeChecker.LengthUnit_ToNumeric(unit))
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LengthMetrics_getFinalizer()
    }
    private static px_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_px(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static vp_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_vp(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static fp_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_fp(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static percent_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_percent(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static lpx_serialize(value: number): LengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_lpx(value)
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resource_serialize(value: Resource): LengthMetrics {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Resource_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_resource(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    public static px(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.px_serialize(value_casted)
    }
    public static vp(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.vp_serialize(value_casted)
    }
    public static fp(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.fp_serialize(value_casted)
    }
    public static percent(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.percent_serialize(value_casted)
    }
    public static lpx(value: number): LengthMetrics {
        const value_casted = value as (number)
        return LengthMetrics.lpx_serialize(value_casted)
    }
    public static resource(value: Resource): LengthMetrics {
        const value_casted = value as (Resource)
        return LengthMetrics.resource_serialize(value_casted)
    }
    private getUnit(): LengthUnit {
        return this.getUnit_serialize()
    }
    private setUnit(unit: LengthUnit): void {
        const unit_casted = unit as (LengthUnit)
        this.setUnit_serialize(unit_casted)
        return
    }
    private getValue(): number {
        return this.getValue_serialize()
    }
    private setValue(value: number): void {
        const value_casted = value as (number)
        this.setValue_serialize(value_casted)
        return
    }
    private getUnit_serialize(): LengthUnit {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_getUnit(this.peer!.ptr)
        return TypeChecker.LengthUnit_FromNumeric(retval)
    }
    private setUnit_serialize(unit: LengthUnit): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setUnit(this.peer!.ptr, TypeChecker.LengthUnit_ToNumeric(unit))
    }
    private getValue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LengthMetrics_getValue(this.peer!.ptr)
        return retval
    }
    private setValue_serialize(value: number): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setValue(this.peer!.ptr, value)
    }
}
export class ShapeClipInternal {
    public static fromPtr(ptr: KPointer): ShapeClip {
        return new ShapeClip(ptr)
    }
}
export class ShapeClip implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ShapeClip.getFinalizer())
    }
    constructor() {
        this(ShapeClip.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ShapeClip_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ShapeClip_getFinalizer()
    }
    public setRectShape(rect: common2D.Rect): void {
        const rect_casted = rect as (common2D.Rect)
        this.setRectShape_serialize(rect_casted)
        return
    }
    public setRoundRectShape(roundRect: RoundRect): void {
        const roundRect_casted = roundRect as (RoundRect)
        this.setRoundRectShape_serialize(roundRect_casted)
        return
    }
    public setCircleShape(circle: Circle): void {
        const circle_casted = circle as (Circle)
        this.setCircleShape_serialize(circle_casted)
        return
    }
    public setOvalShape(oval: common2D.Rect): void {
        const oval_casted = oval as (common2D.Rect)
        this.setOvalShape_serialize(oval_casted)
        return
    }
    public setCommandPath(path: CommandPath): void {
        const path_casted = path as (CommandPath)
        this.setCommandPath_serialize(path_casted)
        return
    }
    private setRectShape_serialize(rect: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._ShapeClip_setRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setRoundRectShape_serialize(roundRect: RoundRect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._ShapeClip_setRoundRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCircleShape_serialize(circle: Circle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._ShapeClip_setCircleShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOvalShape_serialize(oval: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, oval)
        ArkUIGeneratedNativeModule._ShapeClip_setOvalShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCommandPath_serialize(path: CommandPath): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._ShapeClip_setCommandPath(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ShapeMaskInternal {
    public static fromPtr(ptr: KPointer): ShapeMask {
        return new ShapeMask(ptr)
    }
}
export class ShapeMask implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get fillColor(): number {
        return this.getFillColor()
    }
    set fillColor(fillColor: number) {
        this.setFillColor(fillColor)
    }
    get strokeColor(): number {
        return this.getStrokeColor()
    }
    set strokeColor(strokeColor: number) {
        this.setStrokeColor(strokeColor)
    }
    get strokeWidth(): number {
        return this.getStrokeWidth()
    }
    set strokeWidth(strokeWidth: number) {
        this.setStrokeWidth(strokeWidth)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ShapeMask.getFinalizer())
    }
    constructor() {
        this(ShapeMask.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ShapeMask_getFinalizer()
    }
    public setRectShape(rect: common2D.Rect): void {
        const rect_casted = rect as (common2D.Rect)
        this.setRectShape_serialize(rect_casted)
        return
    }
    public setRoundRectShape(roundRect: RoundRect): void {
        const roundRect_casted = roundRect as (RoundRect)
        this.setRoundRectShape_serialize(roundRect_casted)
        return
    }
    public setCircleShape(circle: Circle): void {
        const circle_casted = circle as (Circle)
        this.setCircleShape_serialize(circle_casted)
        return
    }
    public setOvalShape(oval: common2D.Rect): void {
        const oval_casted = oval as (common2D.Rect)
        this.setOvalShape_serialize(oval_casted)
        return
    }
    public setCommandPath(path: CommandPath): void {
        const path_casted = path as (CommandPath)
        this.setCommandPath_serialize(path_casted)
        return
    }
    private getFillColor(): number {
        return this.getFillColor_serialize()
    }
    private setFillColor(fillColor: number): void {
        const fillColor_casted = fillColor as (number)
        this.setFillColor_serialize(fillColor_casted)
        return
    }
    private getStrokeColor(): number {
        return this.getStrokeColor_serialize()
    }
    private setStrokeColor(strokeColor: number): void {
        const strokeColor_casted = strokeColor as (number)
        this.setStrokeColor_serialize(strokeColor_casted)
        return
    }
    private getStrokeWidth(): number {
        return this.getStrokeWidth_serialize()
    }
    private setStrokeWidth(strokeWidth: number): void {
        const strokeWidth_casted = strokeWidth as (number)
        this.setStrokeWidth_serialize(strokeWidth_casted)
        return
    }
    private setRectShape_serialize(rect: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._ShapeMask_setRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setRoundRectShape_serialize(roundRect: RoundRect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._ShapeMask_setRoundRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCircleShape_serialize(circle: Circle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._ShapeMask_setCircleShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOvalShape_serialize(oval: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, oval)
        ArkUIGeneratedNativeModule._ShapeMask_setOvalShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCommandPath_serialize(path: CommandPath): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._ShapeMask_setCommandPath(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFillColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getFillColor(this.peer!.ptr)
        return retval
    }
    private setFillColor_serialize(fillColor: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setFillColor(this.peer!.ptr, fillColor)
    }
    private getStrokeColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getStrokeColor(this.peer!.ptr)
        return retval
    }
    private setStrokeColor_serialize(strokeColor: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setStrokeColor(this.peer!.ptr, strokeColor)
    }
    private getStrokeWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getStrokeWidth(this.peer!.ptr)
        return retval
    }
    private setStrokeWidth_serialize(strokeWidth: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setStrokeWidth(this.peer!.ptr, strokeWidth)
    }
}
export interface Size {
    width: number;
    height: number;
}
export interface Vector2 {
    x: number;
    y: number;
}
export interface Vector2T<T = void> {
    x: number;
    y: number;
}
export interface Vector3 {
    x: number;
    y: number;
    z: number;
}
export type Offset = Vector2;
export type Position = Vector2;
export type Pivot = Vector2;
export type Scale = Vector2;
export type Translation = Vector2;
export type Rotation = Vector3;
export interface Frame {
    x: number;
    y: number;
    width: number;
    height: number;
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export enum LengthMetricsUnit {
    DEFAULT = 0,
    PX = 1
}
export interface Corners {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
export type Rect = common2D.Rect;
export interface CornerRadius {
}
export interface RoundRect {
    rect: common2D.Rect;
    corners: CornerRadius;
}
export interface Circle {
    centerX: number;
    centerY: number;
    radius: number;
}
export interface CommandPath {
    commands: string;
}
export function edgeColors(all: number): Edges {
    return GlobalScope.edgeColors(all)
}
export function edgeWidths(all: number): Edges {
    return GlobalScope.edgeWidths(all)
}
export function borderStyles(all: BorderStyle): Edges {
    return GlobalScope.borderStyles(all)
}
export function borderRadiuses(all: number): BorderRadiuses {
    return GlobalScope.borderRadiuses(all)
}
export class ColorMetrics_serializer {
    public static write(buffer: SerializerBase, value: ColorMetrics): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ColorMetrics {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ColorMetricsInternal.fromPtr(ptr)
    }
}
export class CornerRadius_serializer {
    public static write(buffer: SerializerBase, value: CornerRadius): void {
    }
    public static read(buffer: DeserializerBase): CornerRadius {
        let value : CornerRadius = ({} as CornerRadius)
        return value
    }
}
export class DrawContext_serializer {
    public static write(buffer: SerializerBase, value: DrawContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DrawContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DrawContextInternal.fromPtr(ptr)
    }
}
export class ShapeClip_serializer {
    public static write(buffer: SerializerBase, value: ShapeClip): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ShapeClip {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ShapeClipInternal.fromPtr(ptr)
    }
}
export class ShapeMask_serializer {
    public static write(buffer: SerializerBase, value: ShapeMask): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ShapeMask {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ShapeMaskInternal.fromPtr(ptr)
    }
}
export class Size_serializer {
    public static write(buffer: SerializerBase, value: Size): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
    }
    public static read(buffer: DeserializerBase): Size {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        let value : Size = ({width: width_result, height: height_result} as Size)
        return value
    }
}
export class Vector2_serializer {
    public static write(buffer: SerializerBase, value: Vector2): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
    }
    public static read(buffer: DeserializerBase): Vector2 {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        let value : Vector2 = ({x: x_result, y: y_result} as Vector2)
        return value
    }
}
export class Vector3_serializer {
    public static write(buffer: SerializerBase, value: Vector3): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
    }
    public static read(buffer: DeserializerBase): Vector3 {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        let value : Vector3 = ({x: x_result, y: y_result, z: z_result} as Vector3)
        return value
    }
}
export class Circle_serializer {
    public static write(buffer: SerializerBase, value: Circle): void {
        let valueSerializer : SerializerBase = buffer
        const value_centerX  = value.centerX
        valueSerializer.writeNumber(value_centerX)
        const value_centerY  = value.centerY
        valueSerializer.writeNumber(value_centerY)
        const value_radius  = value.radius
        valueSerializer.writeNumber(value_radius)
    }
    public static read(buffer: DeserializerBase): Circle {
        let valueDeserializer : DeserializerBase = buffer
        const centerX_result : number = (valueDeserializer.readNumber() as number)
        const centerY_result : number = (valueDeserializer.readNumber() as number)
        const radius_result : number = (valueDeserializer.readNumber() as number)
        let value : Circle = ({centerX: centerX_result, centerY: centerY_result, radius: radius_result} as Circle)
        return value
    }
}
export class CommandPath_serializer {
    public static write(buffer: SerializerBase, value: CommandPath): void {
        let valueSerializer : SerializerBase = buffer
        const value_commands  = value.commands
        valueSerializer.writeString(value_commands)
    }
    public static read(buffer: DeserializerBase): CommandPath {
        let valueDeserializer : DeserializerBase = buffer
        const commands_result : string = (valueDeserializer.readString() as string)
        let value : CommandPath = ({commands: commands_result} as CommandPath)
        return value
    }
}
export class Frame_serializer {
    public static write(buffer: SerializerBase, value: Frame): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
    }
    public static read(buffer: DeserializerBase): Frame {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        let value : Frame = ({x: x_result, y: y_result, width: width_result, height: height_result} as Frame)
        return value
    }
}
export class LengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: LengthMetrics): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LengthMetrics {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LengthMetricsInternal.fromPtr(ptr)
    }
}
export class RoundRect_serializer {
    public static write(buffer: SerializerBase, value: RoundRect): void {
        let valueSerializer : SerializerBase = buffer
        const value_rect  = value.rect
        common2D_Rect_serializer.write(valueSerializer, value_rect)
        const value_corners  = value.corners
        CornerRadius_serializer.write(valueSerializer, value_corners)
    }
    public static read(buffer: DeserializerBase): RoundRect {
        let valueDeserializer : DeserializerBase = buffer
        const rect_result : common2D.Rect = common2D_Rect_serializer.read(valueDeserializer)
        const corners_result : CornerRadius = CornerRadius_serializer.read(valueDeserializer)
        let value : RoundRect = ({rect: rect_result, corners: corners_result} as RoundRect)
        return value
    }
}
