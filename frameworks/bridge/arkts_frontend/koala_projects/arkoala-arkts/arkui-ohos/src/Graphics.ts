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

// import { LengthUnit } from "./component/ArkArkuiExternalInterfaces"
import { Resource } from "global.resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, pointer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./component"
import { ResourceColor } from "./component/units"
import { Color, BorderStyle } from "./component/enums"
import { DrawingCanvas } from "./component/arkui-drawing"
import { Dimension } from "./component/units"
import { common2D } from "@ohos/graphics/common2D"
import { drawing } from "@ohos/graphics/drawing"
export interface Size {
    width: number;
    height: number;
}
export class SizeInternal implements Size {
    width: number;
    height: number;
    constructor(width: number, height: number) {
        this.width = width
        this.height = height
    }
}
export interface Frame {
    x: number;
    y: number;
    width: number;
    height: number;
}
export type Position = Vector2;
export interface Vector2 {
    x: number;
    y: number;
}
export enum LengthMetricsUnit {
    DEFAULT = 0,
    PX = 1
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export class LengthMetricsInternal {
    public static fromPtr(ptr: KPointer): LengthMetrics {
        const obj: LengthMetrics = new LengthMetrics(0)
        obj.peer = new Finalizable(ptr, LengthMetrics.getFinalizer())
        return obj
    }
}
export class LengthMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public unit: LengthUnit;
    public value: number;
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_lengthmetrics(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_ctor()
        return retval
    }
    constructor(value: number, unit?: LengthUnit) {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = LengthMetrics.ctor_lengthmetrics()
        this.peer = new Finalizable(ctorPtr, LengthMetrics.getFinalizer())
        if (unit === undefined) {
            this.setUnit(LengthUnit.VP);
            this.setValue(value);
            this.unit = LengthUnit.VP;
            this.value = value;
        } else {
            if (unit >= LengthUnit.PX && unit <= LengthUnit.LPX) {
                this.setUnit(unit);
                this.setValue(value);
                this.unit = unit;
                this.value = value;
            } else {
                this.setUnit(LengthUnit.VP);
                this.setValue(0);
                this.unit = LengthUnit.VP;
                this.value = 0;
            }
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LengthMetrics_getFinalizer()
    }
    public static px(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj: LengthMetrics = LengthMetrics.px_serialize(value_casted)
        obj.unit = LengthUnit.PX
        obj.value = value
        return obj
    }
    public static vp(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj: LengthMetrics = LengthMetrics.vp_serialize(value_casted)
        obj.unit = LengthUnit.VP
        obj.value = value
        return obj
    }
    public static fp(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj: LengthMetrics = LengthMetrics.fp_serialize(value_casted)
        obj.unit = LengthUnit.FP
        obj.value = value
        return obj
    }
    public static percent(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj: LengthMetrics = LengthMetrics.percent_serialize(value_casted)
        obj.unit = LengthUnit.PERCENT
        obj.value = value
        return obj
    }
    public static lpx(value: number): LengthMetrics {
        const value_casted = value as (number)
        const obj: LengthMetrics = LengthMetrics.lpx_serialize(value_casted)
        obj.unit = LengthUnit.LPX
        obj.value = value
        return obj
    }
    public static resource(value: Resource): LengthMetrics {
        const value_casted = value as (Resource)
        const obj: LengthMetrics = LengthMetrics.resource_serialize(value_casted)
        obj.unit = obj.getUnit()
        obj.value = obj.getValue()
        return obj
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
    private static px_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_px(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static vp_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_vp(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static fp_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_fp(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static percent_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_percent(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static lpx_serialize(value: number): LengthMetrics {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_lpx(value)
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resource_serialize(value: Resource): LengthMetrics {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_resource(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: LengthMetrics = LengthMetricsInternal.fromPtr(retval)
        return obj
    }
    private getUnit_serialize(): LengthUnit {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_getUnit(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setUnit_serialize(unit: LengthUnit): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setUnit(this.peer!.ptr, unit.valueOf())
    }
    private getValue_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._LengthMetrics_getValue(this.peer!.ptr)
        return retval
    }
    private setValue_serialize(value: number): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setValue(this.peer!.ptr, value)
    }
}

export class ColorMetricsInternal {
    public static fromPtr(ptr: KPointer): ColorMetrics {
        const obj: ColorMetrics = new ColorMetrics()
        obj.peer = new Finalizable(ptr, ColorMetrics.getFinalizer())
        return obj
    }
}
export class ColorMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get color(): string {
        return this.getColor()
    }
    get red(): number {
        return this.getRed()
    }
    get green(): number {
        return this.getGreen()
    }
    get blue(): number {
        return this.getBlue()
    }
    get alpha(): number {
        return this.getAlpha()
    }
    static ctor_colormetrics(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = ColorMetrics.ctor_colormetrics()
        this.peer = new Finalizable(ctorPtr, ColorMetrics.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorMetrics_getFinalizer()
    }
    public static numeric(value: number): ColorMetrics {
        const value_casted = value as (number)
        return ColorMetrics.numeric_serialize(value_casted)
    }
    public static rgba(red: number, green: number, blue: number, alpha?: number): ColorMetrics {
        const red_casted = red as (number)
        const green_casted = green as (number)
        const blue_casted = blue as (number)
        const alpha_casted = alpha as (number | undefined)
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
    private getColor(): string {
        return this.getColor_serialize()
    }
    private getRed(): number {
        return this.getRed_serialize()
    }
    private getGreen(): number {
        return this.getGreen_serialize()
    }
    private getBlue(): number {
        return this.getBlue_serialize()
    }
    private getAlpha(): number {
        return this.getAlpha_serialize()
    }
    private static numeric_serialize(value: number): ColorMetrics {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_numeric(value)
        const obj: ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static rgba_serialize(red: number, green: number, blue: number, alpha?: number): ColorMetrics {
        const thisSerializer: Serializer = Serializer.hold()
        let alpha_type: int32 = RuntimeType.UNDEFINED
        alpha_type = runtimeType(alpha)
        thisSerializer.writeInt8(alpha_type as int32)
        if ((RuntimeType.UNDEFINED) != (alpha_type)) {
            const alpha_value = alpha!
            thisSerializer.writeNumber(alpha_value)
        }
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_rgba(red, green, blue, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resourceColor_serialize(color: ResourceColor): ColorMetrics {
        const thisSerializer: Serializer = Serializer.hold()
        let color_type: int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0 as int32)
            const color_0 = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1 as int32)
            const color_1 = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2 as int32)
            const color_2 = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3 as int32)
            const color_3 = color as Resource
            thisSerializer.writeResource(color_3)
        }
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_resourceColor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private blendColor_serialize(overlayColor: ColorMetrics): ColorMetrics {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_blendColor(this.peer!.ptr, toPeerPtr(overlayColor))
        const obj: ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private getColor_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_getColor(this.peer!.ptr)
        return retval
    }
    private getRed_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_getRed(this.peer!.ptr)
        return retval
    }
    private getGreen_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_getGreen(this.peer!.ptr)
        return retval
    }
    private getBlue_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_getBlue(this.peer!.ptr)
        return retval
    }
    private getAlpha_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ColorMetrics_getAlpha(this.peer!.ptr)
        return retval
    }
}
export class ShapeMask {
    public rect: Rect | null = null;
    public roundRect: RoundRect | null = null;
    public circle: Circle | null = null;
    public oval: Rect | null = null;
    public path: CommandPath | null = null;
    setRectShape(rect: Rect) {
        this.rect = rect;
        this.roundRect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setRoundRectShape(roundRect: RoundRect) {
        this.roundRect = roundRect;
        this.rect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setCircleShape(circle: Circle) {
        this.circle = circle;
        this.rect = null;
        this.roundRect = null;
        this.oval = null;
        this.path = null;
    }
    setOvalShape(oval: Rect) {
        this.oval = oval;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
        this.path = null;
    }
    setCommandPath(path: CommandPath) {
        this.path = path;
        this.oval = null;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
    }
    public fillColor: number = 0XFF000000;
    public strokeColor: number = 0XFF000000;
    public strokeWidth: number = 0;
}
export class ShapeClip {
    public rect: Rect | null = null;
    public roundRect: RoundRect | null = null;
    public circle: Circle | null = null;
    public oval: Rect | null = null;
    public path: CommandPath | null = null;
    setRectShape(rect: Rect) {
        this.rect = rect;
        this.roundRect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setRoundRectShape(roundRect: RoundRect) {
        this.roundRect = roundRect;
        this.rect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setCircleShape(circle: Circle) {
        this.circle = circle;
        this.rect = null;
        this.roundRect = null;
        this.oval = null;
        this.path = null;
    }
    setOvalShape(oval: Rect) {
        this.oval = oval;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
        this.path = null;
    }
    setCommandPath(path: CommandPath) {
        this.path = path;
        this.oval = null;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
    }
}
export class DrawContext {
    size_: Size;
    sizeInPixel_: Size;
    canvas_: drawing.Canvas;
    constructor() {
        this.size_ = { width: 0, height: 0 }
        this.sizeInPixel_ = { width: 0, height: 0 }
        this.canvas_ = new drawing.Canvas();
    }
    get size(): Size {
        return this.size_;
    }
    get sizeInPixel(): Size {
        return this.sizeInPixel_;
    }
    get canvas(): drawing.Canvas {
        return this.canvas_
    }
}
export interface Vector2T {
    x: number;
    y: number;
}
export interface Vector3 {
    x: number;
    y: number;
    z: number;
}
export type Matrix4 = [
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number
]
export interface Edges<T> {
    top?: T;
    left?: T;
    bottom?: T;
    right?: T;
}
export type CornerRadius = Corners<Vector2>
export interface Corners<T> {
    topLeft: T;
    topRight: T;
    bottomLeft: T;
    bottomRight: T;
}
export type Rect = common2D.Rect;
export interface RoundRect {
    rect: Rect;
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
export type Offset_graphics = Vector2;
export type Pivot = Vector2;
export type Scale = Vector2;
export type Translation = Vector2;
export type Rotation = Vector3;

export function edgeColors(all: number): Edges<number> {
    return { left: all, top: all, right: all, bottom: all };
}

export function edgeWidths(all: number): Edges<number> {
    return { left: all, top: all, right: all, bottom: all };
}

export function borderStyles(all: BorderStyle): Edges<BorderStyle> {
    return { left: all, top: all, right: all, bottom: all };
}

export function borderRadiuses(all: number): Corners<number> {
    return { topLeft: all, topRight: all, bottomLeft: all, bottomRight: all };
}
