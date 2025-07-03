/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

interface Frame {
  x: number;
  y: number;
  width: number;
  height: number;
}

interface Vector2 {
  x: number
  y: number
}

interface Vector3 {
  x: number;
  y: number;
  z: number;
}

type Transform = [
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

enum BorderStyle {
  SOLID = 0,
  DASHED,
  DOTTED,
  NONE
}

type EdgeStyles = {
  top?: BorderStyle;
  right?: BorderStyle;
  bottom?: BorderStyle;
  left?: BorderStyle;
};

interface EdgesT<T> {
  left: T,
  right: T,
  top: T,
  bottom: T,
}
interface SizeT<T> {
  width: T;
  height: T;
}

enum LengthUnit {
  PX = 0,
  VP = 1,
  FP = 2,
  PERCENT = 3,
  LPX = 4,
}

enum LengthMetricsUnit {
  DEFAULT = 0,
  PX = 1,
}

type EdgeWidths = EdgesT<Number>;

type EdgeColors = EdgesT<Number>;

interface Corners {
  topLeft: number,
  topRight: number,
  bottomLeft: number,
  bottomRight: number
}

type BorderRadiuses = Corners;

interface Rect {
  left: number,
  right: number,
  top: number,
  bottom: number
}

interface CornerRadius {
  topLeft: Vector2,
  topRight: Vector2,
  bottomLeft: Vector2,
  bottomRight: Vector2
}

interface RoundRect {
  rect: Rect,
  corners: CornerRadius
}

interface Circle {
  centerX: number,
  centerY: number,
  radius: number
}

interface CommandPath {
  commands: string
}

class LengthMetrics {
  public unit: LengthUnit;
  public value: number;
  public res: Resource;
  constructor(value: number, unit?: LengthUnit, res?: Resource) {
      if (unit in LengthUnit) {
          this.unit = unit;
          this.value = value;
      } else {
          this.unit = LengthUnit.VP;
          this.value = unit === undefined? value : 0;
      }
      this.res = res === undefined ? undefined : res;
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
    let length:Array<number> = getUINativeModule().nativeUtils.resoureToLengthMetrics(res);
    return new LengthMetrics(length[0], length[1], res);
  }
}

declare interface Resource {}
declare type BusinessError = any

declare enum Color {
  White,
  Black,
  Blue,
  Brown,
  Gray,
  Green,
  Grey,
  Orange,
  Pink,
  Red,
  Yellow,
  Transparent,
}

declare enum ColorSpace {
  SRGB = 0,
  DISPLAY_P3 = 1,
}

declare type ResourceColor = Color | number | string | Resource;

const MAX_CHANNEL_VALUE = 0xFF;
const MAX_ALPHA_VALUE = 1;
const ERROR_CODE_RESOURCE_GET_FAILED = 180003;
const ERROR_CODE_COLOR_PARAMETER_INCORRECT = 401;

class ColorMetrics {
  private red_: number;
  private green_: number;
  private blue_: number;
  private alpha_: number;
  private resourceId_: number;
  private colorSpace_: ColorSpace;
  private res_: Resource | undefined;
  private static clamp(value: number): number {
    return Math.min(Math.max(value, 0), MAX_CHANNEL_VALUE);
  }
  private constructor(red: number, green: number, blue: number, alpha: number = MAX_CHANNEL_VALUE, res?: Resource) {
    this.red_ = ColorMetrics.clamp(red);
    this.green_ = ColorMetrics.clamp(green);
    this.blue_ = ColorMetrics.clamp(blue);
    this.alpha_ = ColorMetrics.clamp(alpha);
    this.res_ = res === undefined ? undefined : res;
  }
  private toNumeric(): number {
    return (this.alpha_ << 24) + (this.red_ << 16) + (this.green_ << 8) + this.blue_;
  }
  static numeric(value: number): ColorMetrics {
    const red = (value >> 16) & 0x000000FF;
    const green = (value >> 8) & 0x000000FF;
    const blue = value & 0x000000FF;
    const alpha = (value >> 24) & 0x000000FF;
    if (alpha === 0) {
      return new ColorMetrics(red, green, blue);
    }
    return new ColorMetrics(red, green, blue, alpha);
  }
  static rgba(red: number, green: number, blue: number, alpha: number = MAX_ALPHA_VALUE): ColorMetrics {
    return new ColorMetrics(red, green, blue, alpha * MAX_CHANNEL_VALUE);
  }
  static colorWithSpace(colorSpace: ColorSpace, red: number, green: number, blue: number, alpha: number = MAX_ALPHA_VALUE): ColorMetrics {
    let redInt = Math.round(red * MAX_CHANNEL_VALUE);
    let greenInt = Math.round(green * MAX_CHANNEL_VALUE);
    let blueInt = Math.round(blue * MAX_CHANNEL_VALUE);
    let alphaInt = Math.round(alpha * MAX_CHANNEL_VALUE);
    const colorMetrics = new ColorMetrics(redInt, greenInt, blueInt, alphaInt);
    colorMetrics.setColorSpace(colorSpace);
    return colorMetrics;
  }

  private static rgbOrRGBA(format: string): ColorMetrics {
    const rgbPattern = /^rgb\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i;
    const rgbaPattern = /^rgba\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+(\.\d+)?)\s*\)$/i;

    const rgbMatch = rgbPattern.exec(format);
    const rgbaMatch = rgbaPattern.exec(format);

    if (rgbMatch) {
      const [, red, green, blue] = rgbMatch;
      return new ColorMetrics(Number.parseInt(red, 10), Number.parseInt(green, 10), Number.parseInt(blue, 10));
    } else if (rgbaMatch) {
      const [, red, green, blue, alpha] = rgbaMatch;
      return new ColorMetrics(Number.parseInt(red, 10), Number.parseInt(green, 10), Number.parseInt(blue, 10), Number.parseFloat(alpha) * MAX_CHANNEL_VALUE);
    } else {
      const error = new Error('Parameter error. The format of the input color string is not RGB or RGBA.') as BusinessError;
      error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
      throw error;
    }
  }

  static resourceColor(color: ResourceColor): ColorMetrics {
    if (color === undefined || color === null) {
      const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.') as BusinessError;
      error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
      throw error;
    }
    let chanels: Array<number> = [];
    if (typeof color === 'object') {
      chanels = getUINativeModule().nativeUtils.parseResourceColor(color);
      if (chanels === undefined) {
        const error = new Error('Failed to obtain the color resource.') as BusinessError;
        error.code = ERROR_CODE_RESOURCE_GET_FAILED;
        throw error;
      }
      const red = chanels[0];
      const green = chanels[1];
      const blue = chanels[2];
      const alpha = chanels[3];
      const resourceId = chanels[4];
      const colorMetrics = new ColorMetrics(red, green, blue, alpha, color);
      colorMetrics.setResourceId(resourceId);
      return colorMetrics;
    } else if (typeof color === 'number') {
      return ColorMetrics.numeric(color);
    } else if (typeof color === 'string') {
      if (ColorMetrics.isHexFormat(color)) {
        return ColorMetrics.hex(color);
      } else {
        return ColorMetrics.rgbOrRGBA(color);
      }
    } else {
      const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.') as BusinessError;
      error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
      throw error;
    }
  }
  private static isHexFormat(format: string): boolean {
    return /#(([0-9A-Fa-f]{3})|([0-9A-Fa-f]{6})|([0-9A-Fa-f]{4})|([0-9A-Fa-f]{8}))/.test(format);
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
  blendColor(overlayColor: ColorMetrics): ColorMetrics {
    if (overlayColor === undefined || overlayColor === null) {
      const error = new Error('Parameter error. The type of the input parameter is not ColorMetrics.') as BusinessError;
      error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
      throw error;
    }
    const chanels = getUINativeModule().nativeUtils.blendColor(this.toNumeric(), overlayColor.toNumeric());
    if (chanels === undefined) {
      const error = new Error('Parameter error. The type of the input parameter is not ColorMetrics.') as BusinessError;
      error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
      throw error;
    }
    const red = chanels[0];
    const green = chanels[1];
    const blue = chanels[2];
    const alpha = chanels[3];
    return new ColorMetrics(red, green, blue, alpha);
  }
  get color(): string {
    return `rgba(${this.red_}, ${this.green_}, ${this.blue_}, ${this.alpha_ / MAX_CHANNEL_VALUE})`;
  }
  get red(): number {
    return this.red_;
  }
  get green(): number {
    return this.green_;
  }
  get blue(): number {
    return this.blue_;
  }
  get alpha(): number {
    return this.alpha_;
  }
  setResourceId(resourceId: number): void {
    this.resourceId_ = resourceId;
  }
  getResourceId(): number {
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

class BaseShape {
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

class ShapeClip extends BaseShape { }

class ShapeMask extends BaseShape {
  public fillColor: number = 0XFF000000;
  public strokeColor: number = 0XFF000000;
  public strokeWidth: number = 0;
}

class RenderNode extends Disposable {
  private childrenList: Array<RenderNode>;
  private nodePtr: NodePtr;
  private parentRenderNode: WeakRef<RenderNode> | null;
  private backgroundColorValue: number;
  private clipToFrameValue: boolean;
  private frameValue: Frame;
  private opacityValue: number;
  private pivotValue: Vector2;
  private rotationValue: Vector3;
  private scaleValue: Vector2;
  private shadowColorValue: number;
  private shadowOffsetValue: Vector2;
  private labelValue: string;
  private shadowAlphaValue: number;
  private shadowElevationValue: number;
  private shadowRadiusValue: number;
  private transformValue: Transform;
  private translationValue: Vector2;
  private baseNode_: BaseNode;
  private borderStyleValue: EdgeStyles;
  private borderWidthValue: EdgeWidths;
  private borderColorValue: EdgeColors;
  private borderRadiusValue: BorderRadiuses;
  private shapeMaskValue: ShapeMask;
  private shapeClipValue: ShapeClip;
  private _nativeRef: NativeStrongRef;
  private _frameNode: WeakRef<FrameNode>;
  private lengthMetricsUnitValue: LengthMetricsUnit;
  private markNodeGroupValue: boolean;
  private apiTargetVersion: number;

  constructor(type: string) {
    super();
    this.nodePtr = null;
    this.childrenList = [];
    this.parentRenderNode = null;
    this.backgroundColorValue = 0;
    this.apiTargetVersion = getUINativeModule().common.getApiTargetVersion();
    this.clipToFrameValue = true;
    if (this.apiTargetVersion && this.apiTargetVersion < 12) {
        this.clipToFrameValue = false;
    }
    this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
    this.opacityValue = 1.0;
    this.pivotValue = { x: 0.5, y: 0.5 };
    this.rotationValue = { x: 0, y: 0, z: 0 };
    this.scaleValue = { x: 1.0, y: 1.0 };
    this.shadowColorValue = 0;
    this.shadowOffsetValue = { x: 0, y: 0 };
    this.labelValue = '';
    this.shadowAlphaValue = 0;
    this.shadowElevationValue = 0;
    this.shadowRadiusValue = 0;
    this.transformValue = [1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1];
    this.translationValue = { x: 0, y: 0 };
    this.lengthMetricsUnitValue = LengthMetricsUnit.DEFAULT;
    this.markNodeGroupValue = false;
    if (type === 'BuilderRootFrameNode' || type === 'CustomFrameNode') {
      return;
    }
    this._nativeRef = getUINativeModule().renderNode.createRenderNode(this);
    this.nodePtr = this._nativeRef?.getNativeHandle();
    if (this.apiTargetVersion && this.apiTargetVersion < 12) {
      this.clipToFrame = false;
  } else {
      this.clipToFrame = true;
  }
  }

  set backgroundColor(color: number) {
    this.backgroundColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(color, 0);
    getUINativeModule().renderNode.setBackgroundColor(this.nodePtr, this.backgroundColorValue);
  }
  set clipToFrame(useClip: boolean) {
    this.clipToFrameValue = this.checkUndefinedOrNullWithDefaultValue<boolean>(useClip, true);
    getUINativeModule().renderNode.setClipToFrame(this.nodePtr, this.clipToFrameValue);
  }
  set frame(frame: Frame) {
    if (frame === undefined || frame === null) {
      this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
    } else {
      this.size = { width: frame.width, height: frame.height };
      this.position = { x: frame.x, y: frame.y };
    }
  }
  set opacity(value: number) {
    this.opacityValue = this.checkUndefinedOrNullWithDefaultValue<number>(value, 1.0);
    getUINativeModule().common.setOpacity(this.nodePtr, this.opacityValue);
  }
  set pivot(pivot: Vector2) {
    if (pivot === undefined || pivot === null) {
      this.pivotValue = { x: 0.5, y: 0.5 };
    } else {
      this.pivotValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.x, 0.5);
      this.pivotValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.y, 0.5);
    }
    getUINativeModule().renderNode.setPivot(this.nodePtr, this.pivotValue.x, this.pivotValue.y);
  }
  set position(position: Vector2) {
    if (position === undefined || position === null) {
      this.frameValue.x = 0;
      this.frameValue.y = 0;
    } else {
      this.frameValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(position.x, 0);
      this.frameValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(position.y, 0);
    }
    getUINativeModule().renderNode.setPosition(this.nodePtr, this.frameValue.x, this.frameValue.y, this.lengthMetricsUnitValue);
  }
  set rotation(rotation: Vector3) {
    if (rotation === undefined || rotation === null) {
      this.rotationValue = { x: 0, y: 0, z: 0 };
    } else {
      this.rotationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.x, 0);
      this.rotationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.y, 0);
      this.rotationValue.z = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.z, 0);
    }
    getUINativeModule().renderNode.setRotation(this.nodePtr, this.rotationValue.x, this.rotationValue.y, this.rotationValue.z, this.lengthMetricsUnitValue);
  }
  set scale(scale: Vector2) {
    if (scale === undefined || scale === null) {
      this.scaleValue = { x: 1.0, y: 1.0 };
    } else {
      this.scaleValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(scale.x, 1.0);
      this.scaleValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(scale.y, 1.0);
    }
    getUINativeModule().renderNode.setScale(this.nodePtr, this.scaleValue.x, this.scaleValue.y);
  }
  set shadowColor(color: number) {
    this.shadowColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(color, 0);
    getUINativeModule().renderNode.setShadowColor(this.nodePtr, this.shadowColorValue);
  }
  set shadowOffset(offset: Vector2) {
    if (offset === undefined || offset === null) {
      this.shadowOffsetValue = { x: 0, y: 0 };
    } else {
      this.shadowOffsetValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(offset.x, 0);
      this.shadowOffsetValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(offset.y, 0);
    }
    getUINativeModule().renderNode.setShadowOffset(this.nodePtr, this.shadowOffsetValue.x, this.shadowOffsetValue.y, this.lengthMetricsUnitValue);
  }
  set label(label: string) {
    this.labelValue = this.checkUndefinedOrNullWithDefaultValue<string>(label, '');
    getUINativeModule().renderNode.setLabel(this.nodePtr, this.labelValue);
  }
  set shadowAlpha(alpha: number) {
    this.shadowAlphaValue = this.checkUndefinedOrNullWithDefaultValue<number>(alpha, 0);
    getUINativeModule().renderNode.setShadowAlpha(this.nodePtr, this.shadowAlphaValue);
  }
  set shadowElevation(elevation: number) {
    this.shadowElevationValue = this.checkUndefinedOrNullWithDefaultValue<number>(elevation, 0);
    getUINativeModule().renderNode.setShadowElevation(this.nodePtr, this.shadowElevationValue);
  }
  set shadowRadius(radius: number) {
    this.shadowRadiusValue = this.checkUndefinedOrNullWithDefaultValue<number>(radius, 0);
    getUINativeModule().renderNode.setShadowRadius(this.nodePtr, this.shadowRadiusValue);
  }
  set size(size: Size) {
    if (size === undefined || size === null) {
      this.frameValue.width = 0;
      this.frameValue.height = 0;
    } else {
      this.frameValue.width = this.checkUndefinedOrNullWithDefaultValue<number>(size.width, 0);
      this.frameValue.height = this.checkUndefinedOrNullWithDefaultValue<number>(size.height, 0);
    }
      getUINativeModule().renderNode.setSize(this.nodePtr, this.frameValue.width, this.frameValue.height, this.lengthMetricsUnitValue);
  }
  set transform(transform: Transform) {
    if (transform === undefined || transform === null) {
      this.transformValue = [1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1];
    } else {
      let i: number = 0;
      while (i < transform.length && i < 16) {
        if (i % 5 === 0) {
          this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue<number>(transform[i], 1);
        } else {
          this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue<number>(transform[i], 0);
        }
        i = i + 1;
      }
    }
    getUINativeModule().common.setTransform(this.nodePtr, this.transformValue);
  }
  set translation(translation: Vector2) {
    if (translation === undefined || translation === null) {
      this.translationValue = { x: 0, y: 0 };
    } else {
      this.translationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(translation.x, 0);
      this.translationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(translation.y, 0);
    }
    getUINativeModule().renderNode.setTranslate(this.nodePtr, this.translationValue.x, this.translationValue.y, 0);
  }
  set lengthMetricsUnit(unit: LengthMetricsUnit) {
    if (unit === undefined || unit == null) {
      this.lengthMetricsUnitValue = LengthMetricsUnit.DEFAULT;
    } else {
      this.lengthMetricsUnitValue = unit;
    }
  }
  set markNodeGroup(isNodeGroup) {
    if (isNodeGroup === undefined || isNodeGroup === null) {
        this.markNodeGroupValue = false;
    } else {
        this.markNodeGroupValue = isNodeGroup;
    }
    getUINativeModule().renderNode.setMarkNodeGroup(this.nodePtr, this.markNodeGroupValue);
  }
  get backgroundColor(): number {
    return this.backgroundColorValue;
  }
  get clipToFrame(): boolean {
    return this.clipToFrameValue;
  }
  get opacity(): number {
    return this.opacityValue;
  }
  get frame(): Frame {
    return this.frameValue;
  }
  get pivot(): Vector2 {
    return this.pivotValue;
  }
  get position(): Vector2 {
    return { x: this.frameValue.x, y: this.frameValue.y };
  }
  get rotation(): Vector3 {
    return this.rotationValue;
  }
  get scale(): Vector2 {
    return this.scaleValue;
  }
  get shadowColor(): number {
    return this.shadowColorValue;
  }
  get shadowOffset(): Vector2 {
    return this.shadowOffsetValue;
  }
  get label(): string {
    return this.labelValue;
  }
  get shadowAlpha(): number {
    return this.shadowAlphaValue;
  }
  get shadowElevation(): number {
    return this.shadowElevationValue;
  }
  get shadowRadius(): number {
    return this.shadowRadiusValue;
  }
  get size(): Size {
    return { width: this.frameValue.width, height: this.frameValue.height };
  }
  get transform(): Transform {
    return this.transformValue;
  }
  get translation(): Vector2 {
    return this.translationValue;
  }
  get lengthMetricsUnit() {
    return this.lengthMetricsUnitValue;
  }
  get markNodeGroup() {
    return this.markNodeGroupValue;
  }
  checkUndefinedOrNullWithDefaultValue<T>(arg: T, defaultValue: T): T {
    if (arg === undefined || arg === null) {
      return defaultValue;
    } else {
      return arg;
    }
  }
  appendChild(node: RenderNode) {
    if (node === undefined || node === null) {
      return;
    }
    if (this.childrenList.findIndex(element => element === node) !== -1) {
      return;
    }
    this.childrenList.push(node);
    node.parentRenderNode = new WeakRef(this);
    getUINativeModule().renderNode.appendChild(this.nodePtr, node.nodePtr);
    getUINativeModule().renderNode.addBuilderNode(this.nodePtr, node.nodePtr);
  }
  insertChildAfter(child: RenderNode, sibling: RenderNode | null) {
    if (child === undefined || child === null) {
      return;
    }
    let indexOfNode: number = this.childrenList.findIndex(element => element === child);
    if (indexOfNode !== -1) {
      return;
    }
    child.parentRenderNode = new WeakRef(this);
    let indexOfSibling = this.childrenList.findIndex(element => element === sibling);
    if (indexOfSibling === -1) {
      sibling === null;
    }
    if (sibling === undefined || sibling === null) {
      this.childrenList.splice(0, 0, child);
      getUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, null);
    } else {
      this.childrenList.splice(indexOfSibling + 1, 0, child);
      getUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, sibling.nodePtr);
    }
    getUINativeModule().renderNode.addBuilderNode(this.nodePtr, child.nodePtr);
  }
  removeChild(node: RenderNode) {
    if (node === undefined || node === null) {
      return;
    }
    const index = this.childrenList.findIndex(element => element === node);
    if (index === -1) {
      return;
    }
    const child = this.childrenList[index];
    child.parentRenderNode = null;
    this.childrenList.splice(index, 1);
    getUINativeModule().renderNode.removeBuilderNode(this.nodePtr, node.nodePtr);
    getUINativeModule().renderNode.removeChild(this.nodePtr, node.nodePtr);
  }
  clearChildren() {
    getUINativeModule().renderNode.clearBuilderNode(this.nodePtr);
    this.childrenList = new Array<RenderNode>();
    getUINativeModule().renderNode.clearChildren(this.nodePtr);
  }
  getChild(index: number): RenderNode | null {
    if (this.childrenList.length > index && index >= 0) {
      return this.childrenList[index];
    }
    return null;
  }
  getFirstChild(): RenderNode | null {
    if (this.childrenList.length > 0) {
      return this.childrenList[0];
    }
    return null;
  }
  getNextSibling(): RenderNode | null {
    if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
      return null;
    }
    let parent = this.parentRenderNode.deref();
    if (parent === undefined || parent === null) {
      return null;
    }
    let siblingList = parent.childrenList;
    const index = siblingList.findIndex(element => element === this);
    if (index === -1) {
      return null;
    }
    return parent.getChild(index + 1);
  }
  getPreviousSibling(): RenderNode | null {
    if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
      return null;
    }
    let parent = this.parentRenderNode.deref();
    if (parent === undefined || parent === null) {
      return null;
    }
    let siblingList = parent.childrenList;
    const index = siblingList.findIndex(element => element === this);
    if (index === -1) {
      return null;
    }
    return parent.getChild(index - 1);
  }
  setFrameNode(frameNode: WeakRef<FrameNode>) {
    this._frameNode = frameNode;
  }

  setNodePtr(nativeRef: NativeStrongRef) {
    this._nativeRef = nativeRef;
    this.nodePtr = this._nativeRef?.getNativeHandle();
  }

  setBaseNode(baseNode: BaseNode | null) {
    this.baseNode_ = baseNode;
  }
  resetNodePtr(): void {
    this.nodePtr = null;
    this._nativeRef = null;
  }
  getNodeType(): string {
    return getUINativeModule().renderNode.getNodeType(this.nodePtr);
  }
  dispose() {
    super.dispose();
    if (this.nodePtr) {
      getUINativeModule().renderNode.fireArkUIObjectLifecycleCallback(new WeakRef(this), 'RenderNode', this.getNodeType() || 'RenderNode', this.nodePtr);
    }
    this._nativeRef?.dispose();
    this.baseNode_?.disposeNode();
    this._frameNode?.deref()?.resetNodePtr();
    this._nativeRef = null;
    this.nodePtr = null;
  }
  isDisposed(): boolean {
    return super.isDisposed() && (this._nativeRef === undefined || this._nativeRef === null);
  }
  getNodePtr(): NodePtr {
    return this.nodePtr;
  }

  invalidate() {
    getUINativeModule().renderNode.invalidate(this.nodePtr);
  }
  set borderStyle(style: EdgeStyles) {
    if (style === undefined || style === null) {
      this.borderStyleValue = { left: BorderStyle.NONE, top: BorderStyle.NONE, right: BorderStyle.NONE, bottom: BorderStyle.NONE };
    } else {
      this.borderStyleValue = style;
    }
    getUINativeModule().renderNode.setBorderStyle(
      this.nodePtr, this.borderStyleValue.left, this.borderStyleValue.top, this.borderStyleValue.right, this.borderStyleValue.bottom);
  }
  get borderStyle(): EdgeStyles {
    return this.borderStyleValue;
  }
  set borderWidth(width: EdgeWidths) {
    if (width === undefined || width === null) {
      this.borderWidthValue = { left: 0, top: 0, right: 0, bottom: 0 };
    } else {
      this.borderWidthValue = width;
    }
    getUINativeModule().renderNode.setBorderWidth(
      this.nodePtr, this.borderWidthValue.left, this.borderWidthValue.top,
      this.borderWidthValue.right, this.borderWidthValue.bottom, this.lengthMetricsUnitValue);
  }
  get borderWidth(): EdgeWidths {
    return this.borderWidthValue;
  }
  set borderColor(color: EdgeColors) {
    if (color === undefined || color === null) {
      this.borderColorValue = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 };
    } else {
      this.borderColorValue = color;
    }
    getUINativeModule().renderNode.setBorderColor(
      this.nodePtr, this.borderColorValue.left, this.borderColorValue.top, this.borderColorValue.right, this.borderColorValue.bottom);
  }
  get borderColor(): EdgeColors {
    return this.borderColorValue;
  }
  set borderRadius(radius: BorderRadiuses) {
    if (radius === undefined || radius === null) {
      this.borderRadiusValue = { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
    } else {
      this.borderRadiusValue = radius;
    }
    getUINativeModule().renderNode.setBorderRadius(
      this.nodePtr, this.borderRadiusValue.topLeft, this.borderRadiusValue.topRight,
      this.borderRadiusValue.bottomLeft, this.borderRadiusValue.bottomRight, this.lengthMetricsUnitValue);
  }
  get borderRadius(): BorderRadiuses {
    return this.borderRadiusValue;
  }
  set shapeMask(shapeMask: ShapeMask) {
    if (shapeMask === undefined || shapeMask === null) {
      this.shapeMaskValue = new ShapeMask();
    } else {
      this.shapeMaskValue = shapeMask;
    }
    if (this.shapeMaskValue.rect !== null) {
      const rectMask = this.shapeMaskValue.rect;
      getUINativeModule().renderNode.setRectMask(
        this.nodePtr, rectMask.left, rectMask.top, rectMask.right, rectMask.bottom,
        this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.circle !== null) {
      const circle = this.shapeMaskValue.circle;
      getUINativeModule().renderNode.setCircleMask(
        this.nodePtr, circle.centerX, circle.centerY, circle.radius,
        this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.roundRect !== null) {
      const roundRect = this.shapeMask.roundRect;
      const corners = roundRect.corners;
      const rect = roundRect.rect;
      getUINativeModule().renderNode.setRoundRectMask(
        this.nodePtr,
        corners.topLeft.x,
        corners.topLeft.y,
        corners.topRight.x,
        corners.topRight.y,
        corners.bottomLeft.x,
        corners.bottomLeft.y,
        corners.bottomRight.x,
        corners.bottomRight.y,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom,
        this.shapeMaskValue.fillColor,
        this.shapeMaskValue.strokeColor,
        this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.oval !== null) {
      const oval = this.shapeMaskValue.oval;
      getUINativeModule().renderNode.setOvalMask(
        this.nodePtr, oval.left, oval.top, oval.right, oval.bottom,
        this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.path !== null) {
      const path = this.shapeMaskValue.path;
      getUINativeModule().renderNode.setPath(
        this.nodePtr, path.commands, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    }
  }
  get shapeMask(): ShapeMask {
    return this.shapeMaskValue;
  }
  set shapeClip(shapeClip: ShapeClip) {
    if (shapeClip === undefined || shapeClip === null) {
      this.shapeClipValue = new ShapeClip();
    } else {
      this.shapeClipValue = shapeClip;
    }
    if (this.shapeClipValue.rect !== null) {
      const rectClip = this.shapeClipValue.rect;
      getUINativeModule().renderNode.setRectClip(
        this.nodePtr, rectClip.left, rectClip.top, rectClip.right, rectClip.bottom);
    } else if (this.shapeClipValue.circle !== null) {
      const circle = this.shapeClipValue.circle;
      getUINativeModule().renderNode.setCircleClip(
        this.nodePtr, circle.centerX, circle.centerY, circle.radius);
    } else if (this.shapeClipValue.roundRect !== null) {
      const roundRect = this.shapeClipValue.roundRect;
      const corners = roundRect.corners;
      const rect = roundRect.rect;
      getUINativeModule().renderNode.setRoundRectClip(
        this.nodePtr,
        corners.topLeft.x,
        corners.topLeft.y,
        corners.topRight.x,
        corners.topRight.y,
        corners.bottomLeft.x,
        corners.bottomLeft.y,
        corners.bottomRight.x,
        corners.bottomRight.y,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom);
    } else if (this.shapeClipValue.oval !== null) {
      const oval = this.shapeClipValue.oval;
      getUINativeModule().renderNode.setOvalClip(
        this.nodePtr, oval.left, oval.top, oval.right, oval.bottom,
      );
    } else if (this.shapeClipValue.path !== null) {
      const path = this.shapeClipValue.path;
      getUINativeModule().renderNode.setPathClip(
        this.nodePtr, path.commands);
    }
  }
  get shapeClip(): ShapeClip {
    this.shapeClipValue = this.shapeClipValue ? this.shapeClipValue : new ShapeClip();
    return this.shapeClipValue;
  }
}

function edgeColors(all: number): EdgeColors {
  return { left: all, top: all, right: all, bottom: all };
}

function edgeWidths(all: number): EdgeWidths {
  return { left: all, top: all, right: all, bottom: all };
}

function borderStyles(all: BorderStyle): EdgeStyles {
  return { left: all, top: all, right: all, bottom: all };
}

function borderRadiuses(all: number): BorderRadiuses {
  return { topLeft: all, topRight: all, bottomLeft: all, bottomRight: all };
}
