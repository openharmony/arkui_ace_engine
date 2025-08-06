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

import { Resource } from "global.resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, pointer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer, LengthMetricsCustom } from './component';
import { ResourceColor } from "./component/units"
import { Color, BorderStyle } from "./component/enums"
import { DrawingCanvas } from "./component/arkui-drawing"
import { Dimension } from "./component/units"
import { common2D } from "@ohos/graphics/common2D"
import { drawing } from "@ohos/graphics/drawing"
import { Deserializer } from './component/peers/Deserializer';
import { BusinessError } from '#external';
export interface Size {
    width: number;
    height: number;
}
export interface SizeT<T> {
    width: T,
    height: T
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
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LengthMetrics_getFinalizer()
    }
    constructor(value: number, unit?: LengthUnit) {
        const ctorPtr: KPointer = LengthMetrics.ctor_lengthmetrics()
        this.peer = new Finalizable(ctorPtr, LengthMetrics.getFinalizer())
        this.value = value;
        if (unit === undefined || unit === null || unit < LengthUnit.PX || unit > LengthUnit.LPX) {
            this.unit = LengthUnit.VP;
            this.value = !unit ? value : 0;
        } else {
            this.unit = unit!;
            this.value = value;
        }
        this.setValue(this.value);
        this.setUnit(this.unit);
    }
    static px(value: number) {
        return new LengthMetrics(value, LengthUnit.PX);
    }
    static vp(value: number) {
        return new LengthMetrics(value, LengthUnit.VP);
    }
    static fp(value: number) {
        return new LengthMetrics(value, LengthUnit.FP);
    }
    static percent(value: number) {
        return new LengthMetrics(value, LengthUnit.PERCENT);
    }
    static lpx(value: number) {
        return new LengthMetrics(value, LengthUnit.LPX);
    }
    static resource(res: Resource) {
        const thisSerializer : Serializer = Serializer.hold();
        thisSerializer.writeResource(res);
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._SystemOps_resourceToLengthMetrics(thisSerializer.asBuffer(), thisSerializer.length()) as FixedArray<byte>;
        thisSerializer.release();
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>;
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]));
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult : LengthMetricsCustom = retvalDeserializer.readLengthMetricsCustom();
        let unit = returnResult.unit as int32;
        let lengthUnit: LengthUnit = LengthUnit.PX;
        if (unit >= LengthUnit.PX || unit <= LengthUnit.LPX) {
            lengthUnit = unit as LengthUnit;
        }
        return new LengthMetrics((returnResult.value as number), lengthUnit);
    }
    private setUnit(unit: LengthUnit): void {
        const unit_casted = unit as (LengthUnit)
        this.setUnit_serialize(unit_casted)
        return
    }
    private setValue(value: number): void {
        const value_casted = value as (number)
        this.setValue_serialize(value_casted)
        return
    }
    private setUnit_serialize(unit: LengthUnit): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setUnit(this.peer!.ptr, unit.valueOf())
    }
    private setValue_serialize(value: number): void {
        ArkUIGeneratedNativeModule._LengthMetrics_setValue(this.peer!.ptr, value)
    }
  }

const MAX_CHANNEL_VALUE = 0xFF;
const MAX_ALPHA_VALUE = 1;
const ERROR_CODE_RESOURCE_GET_FAILED = 180003;
const ERROR_CODE_COLOR_PARAMETER_INCORRECT = 401;
export class ColorMetricsInternal {
    public static fromPtr(ptr: KPointer): ColorMetrics {
        const obj: ColorMetrics = new ColorMetrics()
        obj.peer = new Finalizable(ptr, ColorMetrics.getFinalizer())
        return obj
    }
}
export class ColorMetrics implements MaterializedBase {
    private red_: number | undefined = undefined;
    private green_: number | undefined = undefined;
    private blue_: number | undefined = undefined;
    private alpha_: number | undefined = undefined;
    private resourceId_: number = -1;
    static readonly WHITE: int32 = 0xffffffff;
    static readonly BLACK: int32 = 0xff000000;
    static readonly BLUE: int32 = 0xff0000ff;
    static readonly BROWN: int32 = 0xffa52a2a;
    static readonly GRAY: int32 = 0xff808080;
    static readonly GREEN: int32 = 0xff008000;
    static readonly GREY: int32 = 0xff808080;
    static readonly ORANGE: int32 = 0xffffa500;
    static readonly PINK: int32 = 0xffffc0cb;
    static readonly RED: int32 = 0xffff0000;
    static readonly YELLOW: int32 = 0xffffff00;
    static readonly TRANSPARENT: string = '#00000000';
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get color(): string {
        return `rgba(${this.red}, ${this.green}, ${this.blue}, ${this.alpha / MAX_CHANNEL_VALUE})`;
    }
    get red(): number {
        if (!this.red_) {
            this.red_ = this.getRed();
        }
        return this.red_!;
    }
    get green(): number {
        if (!this.green_) {
            this.green_ = this.getGreen();
        }
        return this.green_!;
    }
    get blue(): number {
        if (!this.blue_) {
            this.blue_ = this.getBlue();
        }
        return this.blue_!;
    }
    get alpha(): number {
        if (!this.alpha_) {
            this.alpha_ = this.getAlpha();
        }
        return this.alpha_!;
    }
    private static clamp(value: number): number {
        return Math.min(Math.max(value, 0), MAX_CHANNEL_VALUE);
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
        let alpha_casted = alpha as (number | undefined);
        if (alpha !== undefined && alpha !== null) {
            alpha_casted = Math.min(Math.max(alpha, 0), MAX_ALPHA_VALUE) * MAX_CHANNEL_VALUE;
        } else {
            alpha_casted = MAX_CHANNEL_VALUE;
        }
        let result = ColorMetrics.rgba_serialize(red_casted, green_casted, blue_casted, alpha_casted);
        if (alpha !== undefined) {
            result.alpha_ = ColorMetrics.clamp(alpha_casted);
        }
        return result;
    }
    private static rgbOrRGBA(format: string): ColorMetrics {
        const rgbPattern = new RegExp('^rgb\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)$', 'i');
        const rgbaPattern = new RegExp('^rgba\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+(\\.\\d+)?)\\s*\\)$', 'i');

        const rgbMatch = rgbPattern.exec(format);
        const rgbaMatch = rgbaPattern.exec(format);
        if (rgbMatch) {
            const r = ColorMetrics.clamp(Number.parseInt(rgbMatch[1]!, 10));
            const g = ColorMetrics.clamp(Number.parseInt(rgbMatch[2]!, 10));
            const b = ColorMetrics.clamp(Number.parseInt(rgbMatch[3]!, 10));
            return ColorMetrics.rgba(r, g, b);
        }
        else if (rgbaMatch) {
            const r = ColorMetrics.clamp(Number.parseInt(rgbaMatch[1]!, 10));
            const g = ColorMetrics.clamp(Number.parseInt(rgbaMatch[2]!, 10));
            const b = ColorMetrics.clamp(Number.parseInt(rgbaMatch[3]!, 10));
            const a = ColorMetrics.clamp(Number.parseFloat(rgbaMatch[4]!));
            return ColorMetrics.rgba(r, g, b, a);
        }
        else {
            const error = new Error('Parameter error. The format of the input color string is not RGB or RGBA.');
            throw new BusinessError(ERROR_CODE_COLOR_PARAMETER_INCORRECT, error);
        }
    }
    public static resourceColor(color: ResourceColor): ColorMetrics {
        if (color === undefined || color === null) {
            const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.');
            throw new BusinessError(ERROR_CODE_COLOR_PARAMETER_INCORRECT, error);
        }
        let chanels: Array<number> = [];
        if (typeof color === 'object') {
            const color_casted = (color as Object) as (Resource);
            chanels = ColorMetrics.colorMetricsResourceColor_serialize(color_casted);
            if (chanels[0] === 0) {
                const error = new Error('Failed to obtain the color resource.');
                throw new BusinessError(ERROR_CODE_RESOURCE_GET_FAILED, error);
            }
            const red = chanels[1];
            const green = chanels[2];
            const blue = chanels[3];
            const alpha = chanels[4];
            let colorMetrics = ColorMetrics.rgba_serialize(red, green, blue, alpha);
            colorMetrics.alpha_ = ColorMetrics.clamp(alpha);
            if (chanels.length > 5) {
                const resourceId = chanels[5];
                colorMetrics.setResourceId(resourceId);
            }
            return colorMetrics;
        } else if (typeof color === 'number') {
            return ColorMetrics.numeric(color as number);
        } else if (typeof color === 'string') {
            let colorValue = color as string;
            if (ColorMetrics.isHexFormat(colorValue)) {
                return ColorMetrics.hex(colorValue);
            } else {
                return ColorMetrics.rgbOrRGBA(colorValue);
            }
        } else {
            const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.');
            throw new BusinessError(ERROR_CODE_COLOR_PARAMETER_INCORRECT, error);
        }
    }
    private static isHexFormat(format: string): boolean {
        const rgbPattern = new RegExp('#(([0-9A-Fa-f]{3})|([0-9A-Fa-f]{6})|([0-9A-Fa-f]{4})|([0-9A-Fa-f]{8}))');
        return rgbPattern.test(format);
    }
    private static hex(hexFormat: string): ColorMetrics {
        let r: number = 0;
        let g: number = 0;
        let b: number = 0;
        let a: number = 255;
        if (hexFormat.length === 4) {
            r = parseInt(hexFormat.slice(1, 2).repeat(2), 16);
            g = parseInt(hexFormat.slice(2, 3).repeat(2), 16);
            b = parseInt(hexFormat.slice(3).repeat(2), 16);
        } else if (hexFormat.length === 7) {
            r = parseInt(hexFormat.slice(1, 3), 16);
            g = parseInt(hexFormat.slice(3, 5), 16);
            b = parseInt(hexFormat.slice(5), 16);
        } else if (hexFormat.length === 5) {
            a = parseInt(hexFormat.slice(1, 2).repeat(2), 16);
            r = parseInt(hexFormat.slice(2, 3).repeat(2), 16);
            g = parseInt(hexFormat.slice(3, 4).repeat(2), 16);
            b = parseInt(hexFormat.slice(4).repeat(2), 16);
        } else if (hexFormat.length === 9) {
            a = parseInt(hexFormat.slice(1, 3), 16);
            r = parseInt(hexFormat.slice(3, 5), 16);
            g = parseInt(hexFormat.slice(5, 7), 16);
            b = parseInt(hexFormat.slice(7), 16);
        }

        return ColorMetrics.rgba(r, g, b, a);
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
    setResourceId(resourceId: number): void {
        this.resourceId_ = resourceId;
    }
    getResourceId(): number {
        return this.resourceId_;
    }
    private static colorMetricsResourceColor_serialize(color: Resource): Array<number> {
        const thisSerializer : Serializer = Serializer.hold();
        thisSerializer.writeResource(color);
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._SystemOps_colorMetricsResourceColor(thisSerializer.asBuffer(), thisSerializer.length()) as FixedArray<byte>;
        thisSerializer.release();
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>;
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]));
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const buffer_length : int32 = retvalDeserializer.readInt32();
        let buffer : Array<number> = new Array<number>(buffer_length);
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number);
        }
        const returnResult : Array<number> = buffer;
        return returnResult;
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
export interface Vector2T<T> {
    x: T;
    y: T;
}
export type PositionT<T> = Vector2T<T>;
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
