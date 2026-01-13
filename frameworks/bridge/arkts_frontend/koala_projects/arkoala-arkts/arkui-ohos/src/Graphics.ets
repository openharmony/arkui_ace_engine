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
import { TypeChecker } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, pointer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { ResourceColor } from '#generated';
import { Color, BorderStyle } from '#generated';
import { default as common2D } from "@ohos.graphics.common2D"
import { default as drawing } from "@ohos.graphics.drawing"
import { BusinessError } from '@ohos.base';
import { SystemOps } from './framework';
import { ColorSpace } from './component/enums';
export interface Size {
    width: double;
    height: double;
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
    x: double;
    y: double;
    width: double;
    height: double;
}
export type NodePosition = Vector2;
export interface Vector2 {
    x: double;
    y: double;
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

export class LengthMetrics {
    public unit: LengthUnit;
    public value: double;
    constructor(){
        this.value = 0;
        this.unit = LengthUnit.VP;
    }
    constructor(value: double, unit?: LengthUnit) {
        this.value = value;
        if (unit === undefined || unit === null || unit < LengthUnit.PX || unit > LengthUnit.LPX) {
            this.unit = LengthUnit.VP;
            this.value = !unit ? value : 0;
        } else {
            this.unit = unit!;
            this.value = value;
        }
    }
    static px(value: double) {
        return new LengthMetrics(value, LengthUnit.PX);
    }
    static vp(value: double) {
        return new LengthMetrics(value, LengthUnit.VP);
    }
    static fp(value: double) {
        return new LengthMetrics(value, LengthUnit.FP);
    }
    static percent(value: double) {
        return new LengthMetrics(value, LengthUnit.PERCENT);
    }
    static lpx(value: double) {
        return new LengthMetrics(value, LengthUnit.LPX);
    }
    static resource(res: Resource) {
        let returnResult = SystemOps.resourceToLengthMetrics(res);
        let unit = returnResult.unit as int32;
        let lengthUnit: LengthUnit = LengthUnit.PX;
        if (unit >= LengthUnit.PX || unit <= LengthUnit.LPX) {
            lengthUnit = unit as LengthUnit;
        }
        return new LengthMetrics((returnResult.value as number), lengthUnit);
    }
  }

const MAX_CHANNEL_VALUE = 0xFF;
const MAX_ALPHA_VALUE = 1;
const ERROR_CODE_RESOURCE_GET_FAILED = 180003;
const ERROR_CODE_COLOR_PARAMETER_INCORRECT = 401;
export class ColorMetrics {
    private red_: int32;
    private green_: int32;
    private blue_: int32;
    private alpha_: int32;
    private colorSpace_: ColorSpace = ColorSpace.SRGB;
    private resourceId_: int32 = -1;
    static readonly WHITE: int32 = 0xffffffff.toInt();
    static readonly BLACK: int32 = 0xff000000.toInt();
    static readonly BLUE: int32 = 0xff0000ff.toInt();
    static readonly BROWN: int32 = 0xffa52a2a.toInt();
    static readonly GRAY: int32 = 0xff808080.toInt();
    static readonly GREEN: int32 = 0xff008000.toInt();
    static readonly GREY: int32 = 0xff808080.toInt();
    static readonly ORANGE: int32 = 0xffffa500.toInt();
    static readonly PINK: int32 = 0xffffc0cb.toInt();
    static readonly RED: int32 = 0xffff0000.toInt();
    static readonly YELLOW: int32 = 0xffffff00.toInt();
    static readonly TRANSPARENT: string = '#00000000';
    get color(): string {
        return `rgba(${this.red}, ${this.green}, ${this.blue}, ${(this.alpha as double) / MAX_CHANNEL_VALUE})`;
    }
    get red(): int32 {
        return this.red_!;
    }
    get green(): int32 {
        return this.green_!;
    }
    get blue(): int32 {
        return this.blue_!;
    }
    get alpha(): int32 {
        return this.alpha_!;
    }
    set red(red: int32) {
        this.red_ = red;
    }
    set green(green: int32) {
        this.green_ = green;
    }
    set blue(blue: int32) {
        this.blue_ = blue;
    }
    set alpha(alpha: int32) {
        this.alpha_ = alpha;
    }
    set resourceId(id: int32) {
        this.resourceId_ = id;
    }
    private static clamp(value: number): number {
        return Math.min(Math.max(value, 0), MAX_CHANNEL_VALUE);
    }
    constructor(){
        this.red_ = 0;
        this.green_ = 0;
        this.blue_ = 0;
        this.alpha_ = MAX_CHANNEL_VALUE;
    }
    constructor(red: number, green: number, blue: number, alpha: number = MAX_CHANNEL_VALUE) {
        this.red_ = ColorMetrics.clamp(red) as int32;
        this.green_ = ColorMetrics.clamp(green) as int32;
        this.blue_ = ColorMetrics.clamp(blue) as int32;
        this.alpha_ = ColorMetrics.clamp(alpha) as int32;
    }
    public static numeric(value: int32): ColorMetrics {
        const red = (value >> 16) & 0x000000FF;
        const green = (value >> 8) & 0x000000FF;
        const blue = value & 0x000000FF;
        const alpha = (value >> 24) & 0x000000FF;
        if (alpha === 0) {
            return new ColorMetrics(red, green, blue);
        }
        return new ColorMetrics(red, green, blue, alpha);
    }
    public static rgba(red: double, green: double, blue: double, alpha?: double): ColorMetrics {
        const red_casted = red as (number)
        const green_casted = green as (number)
        const blue_casted = blue as (number)
        let alpha_casted = alpha as (number | undefined);
        if (alpha !== undefined && alpha !== null) {
            alpha_casted = Math.min(Math.max(alpha, 0), MAX_ALPHA_VALUE) * MAX_CHANNEL_VALUE;
        } else {
            alpha_casted = MAX_CHANNEL_VALUE;
        }
        return new ColorMetrics(red, green, blue, alpha_casted);
    }
    public static colorWithSpace(colorSpace: ColorSpace, red: double, green: double, blue: double, alpha?: double): ColorMetrics {
        const red_casted = Math.round(red * MAX_CHANNEL_VALUE);
        const green_casted = Math.round(green * MAX_CHANNEL_VALUE);
        const blue_casted = Math.round(blue * MAX_CHANNEL_VALUE);
        let alpha_casted = alpha as (double | undefined);
        if (alpha !== undefined && alpha !== null) {
            alpha_casted = Math.round(alpha * MAX_CHANNEL_VALUE);
        } else {
            alpha_casted = MAX_CHANNEL_VALUE;
        }
        const colorMetrics = new ColorMetrics(red_casted, green_casted, blue_casted, alpha_casted);
        colorMetrics.setColorSpace(colorSpace);
        return colorMetrics;
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
        } else if (rgbaMatch) {
            const r = ColorMetrics.clamp(Number.parseInt(rgbaMatch[1]!, 10));
            const g = ColorMetrics.clamp(Number.parseInt(rgbaMatch[2]!, 10));
            const b = ColorMetrics.clamp(Number.parseInt(rgbaMatch[3]!, 10));
            const a = ColorMetrics.clamp(Number.parseFloat(rgbaMatch[4]!));
            return ColorMetrics.rgba(r, g, b, a);
        } else {
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
            chanels = SystemOps.colorMetricsResourceColor(color_casted);
            if (chanels[0] === 0) {
                const error = new Error('Failed to obtain the color resource.');
                throw new BusinessError(ERROR_CODE_RESOURCE_GET_FAILED, error);
            }
            const red = chanels[1];
            const green = chanels[2];
            const blue = chanels[3];
            const alpha = chanels[4];
            let colorMetrics = new ColorMetrics(red, green, blue, alpha);
            colorMetrics.alpha_ = ColorMetrics.clamp(alpha) as int32;
            if (chanels.length > 5) {
                const resourceId = chanels[5];
                colorMetrics.setResourceId(resourceId as int32);
            }
            return colorMetrics;
        } else if (color instanceof int32) {
            return ColorMetrics.numeric(color as int32);
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

        return new ColorMetrics(r, g, b, a);
    }
    private toNumeric(): number {
        return (this.alpha_! << 24) + (this.red_! << 16) + (this.green_! << 8) + this.blue_!;
    }
    public blendColor(overlayColor: ColorMetrics): ColorMetrics {
        let chanels: Array<number> = [];
        chanels = SystemOps.blendColorByColorMetrics(this.toNumeric(), overlayColor.toNumeric());
        if (chanels.length <= 1) {
            const error = new Error('Parameter error. The type of the input parameter is not ColorMetrics.');
            throw new BusinessError(ERROR_CODE_COLOR_PARAMETER_INCORRECT, error);
        }
        const red = chanels[1];
        const green = chanels[2];
        const blue = chanels[3];
        const alpha = chanels[4];

        return new ColorMetrics(red, green, blue, alpha);
    }
    setResourceId(resourceId: int32): void {
        this.resourceId_ = resourceId;
    }
    getResourceId(): int32 {
        return this.resourceId_;
    }
    setColorSpace(colorSpace: ColorSpace): void {
        if (ColorSpace.DISPLAY_P3 === colorSpace || ColorSpace.SRGB === colorSpace) {
            this.colorSpace_ = colorSpace;
        }
    }
    getColorSpace(): ColorSpace {
        return this.colorSpace_;
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
    public fillColor: int32 = 0XFF000000.toInt();
    public strokeColor: int32 = 0XFF000000.toInt();
    public strokeWidth: double = 0;
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
  canvas_: drawing.Canvas | undefined;
  constructor() {
    this.size_ = { width: 0, height: 0 };
    this.sizeInPixel_ = { width: 0, height: 0 };
    this.canvas_ = undefined;
  }
  get size(): Size {
    return this.size_;
  }
  get sizeInPixel(): Size {
    return this.sizeInPixel_;
  }
  get canvas(): drawing.Canvas {
    return this.canvas_!;
  }
}
export interface Vector2T<T> {
    x: T;
    y: T;
}
export type PositionT<T> = Vector2T<T>;
export interface Vector3 {
    x: double;
    y: double;
    z: double;
}
export type Matrix4 = [
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double
]
export interface NodeEdges<T> {
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
    centerX: double;
    centerY: double;
    radius: double;
}
export interface CommandPath {
    commands: string;
}
export type Offset_graphics = Vector2;
export type Pivot = Vector2;
export type Scale = Vector2;
export type Translation = Vector2;
export type Rotation = Vector3;

export function edgeColors(all: int32): NodeEdges<int32> {
    return { left: all, top: all, right: all, bottom: all };
}

export function edgeWidths(all: double): NodeEdges<double> {
    return { left: all, top: all, right: all, bottom: all };
}

export function borderStyles(all: BorderStyle): NodeEdges<BorderStyle> {
    return { left: all, top: all, right: all, bottom: all };
}

export function borderRadiuses(all: double): Corners<double> {
    return { topLeft: all, topRight: all, bottomLeft: all, bottomRight: all };
}

export type NodeBorderRadiuses = Corners<double>;
export type NodeOffset = Vector2;
