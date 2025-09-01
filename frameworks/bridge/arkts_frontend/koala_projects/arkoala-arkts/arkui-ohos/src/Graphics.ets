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
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components";
import {
  SerializerBase,
  DeserializerBase,
  Finalizable,
  runtimeType,
  RuntimeType,
  registerCallback,
  wrapCallback,
  toPeerPtr,
  KPointer,
  MaterializedBase,
  NativeBuffer,
  KInt,
  KBoolean,
  KStringPtr,
  CallbackResource,
  InteropNativeModule,
  Tags,
  nullptr,
  KSerializerBuffer,
  KUint8ArrayPtr,
} from "@koalaui/interop";

import { unsafeCast, int32, int64, float32 } from "@koalaui/common";
import { ResourceColor } from "./component/units";
import { Color, BorderStyle } from "./component/enums";
import { Dimension } from "./component/units";
import { default as common2D } from "@ohos.graphics.common2D";
import { default as drawing } from "@ohos.graphics.drawing";
import { BusinessError } from "#external";
import { SystemOps } from "#generated";
export interface Size {
  width: number;
  height: number;
}
export interface SizeT<T> {
  width: T;
  height: T;
}
export class SizeInternal implements Size {
  width: number;
  height: number;
  constructor(width: number, height: number) {
    this.width = width;
    this.height = height;
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
  PX = 1,
}
export enum LengthUnit {
  PX = 0,
  VP = 1,
  FP = 2,
  PERCENT = 3,
  LPX = 4,
}

export class LengthMetrics {}

const MAX_CHANNEL_VALUE = 0xff;
const MAX_ALPHA_VALUE = 1;
const ERROR_CODE_RESOURCE_GET_FAILED = 180003;
const ERROR_CODE_COLOR_PARAMETER_INCORRECT = 401;
export class ColorMetrics {}
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
  public fillColor: number = 0xff000000;
  public strokeColor: number = 0xff000000;
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
];
export interface Edges<T> {
  top?: T;
  left?: T;
  bottom?: T;
  right?: T;
}
export type CornerRadius = Corners<Vector2>;
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

export type NodeBorderRadiuses = Corners<number>;
export type Offset = Vector2;
