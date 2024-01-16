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

/// <reference path='./import.ts' />
const arkUINativeModule = globalThis.getArkUINativeModule();
function getUINativeModule(): any {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
}

const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;

function applyUIAttributes(modifier: AttributeModifier<CommonAttribute>, nativeNode: KNode, component: ArkComponent): void {
  let state = 0;
  if (modifier.applyPressedAttribute !== undefined) {
    state |= UI_STATE_PRESSED;
  }
  if (modifier.applyFocusedAttribute !== undefined) {
    state |= UI_STATE_FOCUSED;
  }
  if (modifier.applyDisabledAttribute !== undefined) {
    state |= UI_STATE_DISABLED;
  }
  if (modifier.applySelectedAttribute !== undefined) {
    state |= UI_STATE_SELECTED;
  }

  getUINativeModule().setSupportedUIState(nativeNode, state);
  const currentUIState = getUINativeModule().getUIState(nativeNode);

  if (modifier.applyNormalAttribute !== undefined) {
    modifier.applyNormalAttribute(component);
  }
  if ((currentUIState & UI_STATE_PRESSED) && (modifier.applyPressedAttribute !== undefined)) {
    modifier.applyPressedAttribute(component);
  }
  if ((currentUIState & UI_STATE_FOCUSED) && (modifier.applyFocusedAttribute !== undefined)) {
    modifier.applyFocusedAttribute(component);
  }
  if ((currentUIState & UI_STATE_DISABLED) && (modifier.applyDisabledAttribute !== undefined)) {
    modifier.applyDisabledAttribute(component);
  }
  if ((currentUIState & UI_STATE_SELECTED) && (modifier.applySelectedAttribute !== undefined)) {
    modifier.applySelectedAttribute(component);
  }
}

function isResource(variable: any): variable is Resource {
  return (variable as Resource)?.bundleName !== undefined;
}

function isResourceEqual(stageValue: Resource, value: Resource): boolean {
  return (stageValue.bundleName === value.bundleName) &&
    (stageValue.moduleName === value.moduleName) &&
    (stageValue.id === value.id) &&
    (stageValue.params === value.params) &&
    (stageValue.type === value.type);
}
function isBaseOrResourceEqual(stageValue: any, value: any): boolean {
  if (isResource(stageValue) && isResource(value)) {
    return isResourceEqual(stageValue, value);
  } else if (!isResource(stageValue) && !isResource(value)) {
    return (stageValue === value);
  }
  return false;
}

const SAFE_AREA_TYPE_NONE = 0;
const SAFE_AREA_TYPE_SYSTEM = 1;
const SAFE_AREA_TYPE_CUTOUT = 2;
const SAFE_AREA_TYPE_KEYBOARD = 4;
const SAFE_AREA_TYPE_ALL = 7;

const SAFE_AREA_EDGE_NONE = 0;
const SAFE_AREA_EDGE_TOP = 1;
const SAFE_AREA_EDGE_BOTTOM = 2;
const SAFE_AREA_EDGE_START = 4;
const SAFE_AREA_EDGE_END = 8;
const SAFE_AREA_EDGE_ALL = 15;

const SAFE_AREA_TYPE_LIMIT = 3;
const SAFE_AREA_EDGE_LIMIT = 4;
const DIRECTION_RANGE = 3;

type KNode = number | null

interface Equable {
  isEqual(value: Equable): boolean;
}

class Modifier<T extends number | string | boolean | Equable | Resource | object> {
  stageValue?: T;
  value?: T;
  constructor(value: T) {
    this.stageValue = value;
  }

  applyStage(node: KNode): boolean {
    if (this.stageValue === this.value) {
      if (this.value === undefined) {
        this.applyPeer(node, true);
      }
      delete this.stageValue;
      return;
    }
    if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
      if ((this.stageValue as Equable).isEqual(this.value as Equable)) {
        delete this.stageValue;
        return;
      }
    }
    this.value = this.stageValue;
    delete this.stageValue;
    this.applyPeer(node, this.value === undefined);
    return (this.value === undefined);
  }

  applyPeer(node: KNode, reset: boolean): void { }
}

class ModifierWithKey<T extends number | string | boolean | object> {
  stageValue?: T;
  value?: T;
  constructor(value: T) {
    this.stageValue = value;
  }

  applyStage(node: KNode): boolean {
    if (this.stageValue === undefined || this.stageValue === null) {
      this.value = this.stageValue;
      this.applyPeer(node, true);
      return true;
    }
    const stageTypeInfo: string = typeof this.stageValue;
    const valueTypeInfo: string = typeof this.value;
    let different: boolean = false;
    if (stageTypeInfo !== valueTypeInfo) {
      different = true;
    } else if (stageTypeInfo === 'number' || stageTypeInfo === 'string' || stageTypeInfo === 'boolean') {
      different = (this.stageValue !== this.value);
    } else {
      different = this.checkObjectDiff();
    }
    if (different) {
      this.value = this.stageValue;
      this.applyPeer(node, false);
    }
    this.stageValue = undefined;
    return false;
  }

  applyPeer(node: KNode, reset: boolean): void { }

  checkObjectDiff(): boolean {
    return true;
  }
}

class BackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundColor(node);
    } else {
      getUINativeModule().common.setBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class WidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('width');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetWidth(node);
    } else {
      getUINativeModule().common.setWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BorderWidthModifier extends ModifierWithKey<Length | EdgeWidths> {
  constructor(value: Length | EdgeWidths) {
    super(value);
  }
  static identity: Symbol = Symbol('borderWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderWidth(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().common.setBorderWidth(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setBorderWidth(node,
          (this.value as EdgeWidths).left,
          (this.value as EdgeWidths).right,
          (this.value as EdgeWidths).top,
          (this.value as EdgeWidths).bottom);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as EdgeWidths).left === (this.value as EdgeWidths).left &&
        (this.stageValue as EdgeWidths).right === (this.value as EdgeWidths).right &&
        (this.stageValue as EdgeWidths).top === (this.value as EdgeWidths).top &&
        (this.stageValue as EdgeWidths).bottom === (this.value as EdgeWidths).bottom);
    } else {
      return true;
    }
  }
}

class HeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('height');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetHeight(node);
    } else {
      getUINativeModule().common.setHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('borderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().common.setBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setBorderRadius(node,
          (this.value as BorderRadiuses).topLeft,
          (this.value as BorderRadiuses).topRight,
          (this.value as BorderRadiuses).bottomLeft,
          (this.value as BorderRadiuses).bottomRight);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}

class PositionModifier extends ModifierWithKey<Position> {
  constructor(value: Position) {
    super(value);
  }
  static identity: Symbol = Symbol('position');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPosition(node);
    } else {
      getUINativeModule().common.setPosition(node, this.value.x, this.value.y);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}

class BorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors> {
  constructor(value: ResourceColor | EdgeColors) {
    super(value);
  }
  static identity: Symbol = Symbol('borderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().common.setBorderColor(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setBorderColor(node, (this.value as EdgeColors).left,
          (this.value as EdgeColors).right, (this.value as EdgeColors).top,
          (this.value as EdgeColors).bottom);
      }

    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as EdgeColors).left === (this.value as EdgeColors).left &&
        (this.stageValue as EdgeColors).right === (this.value as EdgeColors).right &&
        (this.stageValue as EdgeColors).top === (this.value as EdgeColors).top &&
        (this.stageValue as EdgeColors).bottom === (this.value as EdgeColors).bottom);
    } else {
      return true;
    }
  }
}

interface Matrix {
  matrix4x4: []
}


class TransformModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('transform');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTransform(node);
    } else {
      getUINativeModule().common.setTransform(node, (this.value as Matrix).matrix4x4);
    }
  }
  checkObjectDiff(): boolean {
    return !deepCompareArrays((this.stageValue as Matrix).matrix4x4, (this.value as Matrix).matrix4x4);
  }
}

class BorderStyleModifier extends ModifierWithKey<BorderStyle | EdgeStyles> {
  constructor(value: BorderStyle | EdgeStyles) {
    super(value);
  }
  static identity: Symbol = Symbol('borderStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderStyle(node);
    } else {
      let type: boolean;
      let style: BorderStyle;
      let top: BorderStyle;
      let right: BorderStyle;
      let bottom: BorderStyle;
      let left: BorderStyle;
      if (isNumber(this.value)) {
        style = this.value as BorderStyle;
        type = true;
      } else if (isObject(this.value)) {
        top = (this.value as EdgeStyles)?.top;
        right = (this.value as EdgeStyles)?.right;
        bottom = (this.value as EdgeStyles)?.bottom;
        left = (this.value as EdgeStyles)?.left;
        type = true;
      }
      if (type === true) {
        getUINativeModule().common.setBorderStyle(node, type, style, top, right, bottom, left);
      } else {
        getUINativeModule().common.resetBorderStyle(node);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as EdgeStyles)?.top === (this.stageValue as EdgeStyles)?.top &&
      (this.value as EdgeStyles)?.right === (this.stageValue as EdgeStyles)?.right &&
      (this.value as EdgeStyles)?.bottom === (this.stageValue as EdgeStyles)?.bottom &&
      (this.value as EdgeStyles)?.left === (this.stageValue as EdgeStyles)?.left);
  }
}

class ShadowModifier extends ModifierWithKey<ShadowOptions | ShadowStyle> {
  constructor(value: ShadowOptions | ShadowStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('shadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetShadow(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setShadow(node, this.value, undefined, undefined, undefined, undefined, undefined, undefined);
      } else {
        getUINativeModule().common.setShadow(node, undefined,
          (this.value as ShadowOptions).radius,
          (this.value as ShadowOptions).type,
          (this.value as ShadowOptions).color,
          (this.value as ShadowOptions).offsetX,
          (this.value as ShadowOptions).offsetY,
          (this.value as ShadowOptions).fill);
      }
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as ShadowOptions).radius === (this.value as ShadowOptions).radius &&
      (this.stageValue as ShadowOptions).type === (this.value as ShadowOptions).type &&
      (this.stageValue as ShadowOptions).color === (this.value as ShadowOptions).color &&
      (this.stageValue as ShadowOptions).offsetX === (this.value as ShadowOptions).offsetX &&
      (this.stageValue as ShadowOptions).offsetY === (this.value as ShadowOptions).offsetY &&
      (this.stageValue as ShadowOptions).fill === (this.value as ShadowOptions).fill);
  }
}

class HitTestBehaviorModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('hitTestBehavior');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetHitTestBehavior(node);
    } else {
      getUINativeModule().common.setHitTestBehavior(node, this.value);
    }
  }
}

class ZIndexModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('zIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetZIndex(node);
    } else {
      getUINativeModule().common.setZIndex(node, this.value);
    }
  }
}

class OpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('opacity');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOpacity(node);
    } else {
      getUINativeModule().common.setOpacity(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class AlignModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('align');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAlign(node);
    } else {
      getUINativeModule().common.setAlign(node, this.value);
    }
  }
}

class BackdropBlurModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('backdropBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackdropBlur(node);
    } else {
      getUINativeModule().common.setBackdropBlur(node, this.value);
    }
  }
}

class HueRotateModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('hueRotate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetHueRotate(node);
    } else {
      getUINativeModule().common.setHueRotate(node, this.value);
    }
  }
}

class InvertModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('invert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetInvert(node);
    } else {
      getUINativeModule().common.setInvert(node, this.value);
    }
  }
}

class SepiaModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('sepia');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSepia(node);
    } else {
      getUINativeModule().common.setSepia(node, this.value);
    }
  }
}

class SaturateModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('saturate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSaturate(node);
    } else {
      getUINativeModule().common.setSaturate(node, this.value);
    }
  }
}

class ColorBlendModifier extends ModifierWithKey<Color | string | Resource> {
  constructor(value: Color | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('colorBlend');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetColorBlend(node);
    } else {
      getUINativeModule().common.setColorBlend(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class GrayscaleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('grayscale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGrayscale(node);
    } else {
      getUINativeModule().common.setGrayscale(node, this.value);
    }
  }
}

class ContrastModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('contrast');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetContrast(node);
    } else {
      getUINativeModule().common.setContrast(node, this.value);
    }
  }
}

class BrightnessModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('brightness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBrightness(node);
    } else {
      getUINativeModule().common.setBrightness(node, this.value);
    }
  }
}

class BlurModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('blur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBlur(node);
    } else {
      getUINativeModule().common.setBlur(node, this.value);
    }
  }
}

class LinearGradientModifier extends ModifierWithKey<{
  angle?: number | string;
  direction?: GradientDirection; colors: Array<any>; repeating?: boolean;
}> {
  constructor(value: {
    angle?: number | string; direction?: GradientDirection;
    colors: Array<any>; repeating?: boolean;
  }) {
    super(value);
  }
  static identity: Symbol = Symbol('linearGradient');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetLinearGradient(node);
    } else {
      getUINativeModule().common.setLinearGradient(node,
        this.value.angle, this.value.direction,
        this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.angle === this.value.angle) &&
      (this.stageValue.direction === this.value.direction) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}

class RadialGradientModifier extends ModifierWithKey<{ center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }> {
  constructor(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }) {
    super(value);
  }
  static identity: Symbol = Symbol('radialGradient');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRadialGradient(node);
    } else {
      getUINativeModule().common.setRadialGradient(node,
        this.value.center, this.value.radius, this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.center === this.value.center) &&
      (this.stageValue.radius === this.value.radius) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}

class SweepGradientModifier extends ModifierWithKey<{
  center: Array<any>; start?: number |
  string; end?: number | string; rotation?: number | string;
  colors: Array<any>; repeating?: boolean;
}> {
  constructor(value: {
    center: Array<any>;
    start?: number | string; end?: number | string;
    rotation?: number | string; colors: Array<any>; repeating?: boolean;
  }) {
    super(value);
  }
  static identity: Symbol = Symbol('sweepGradient');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSweepGradient(node);
    } else {
      getUINativeModule().common.setSweepGradient(node,
        this.value.center,
        this.value.start, this.value.end, this.value.rotation,
        this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.center === this.value.center) &&
      (this.stageValue.start === this.value.start) &&
      (this.stageValue.end === this.value.end) &&
      (this.stageValue.rotation === this.value.rotation) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}

class OverlayModifier extends ModifierWithKey<ArkOverlay> {
  constructor(value: ArkOverlay) {
    super(value);
  }
  static identity: Symbol = Symbol('overlay');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOverlay(node);
    } else {
      getUINativeModule().common.setOverlay(node,
        this.value.value, this.value.align,
        this.value.offsetX, this.value.offsetY,
        this.value.hasOptions, this.value.hasOffset);
    }
  }
  checkObjectDiff(): boolean {
    if (isUndefined(this.value)) {
      return !isUndefined(this.stageValue);
    }
    return this.value.checkObjectDiff(this.stageValue);
  }
}

class BorderImageModifier extends ModifierWithKey<BorderImageOption> {
  constructor(value: BorderImageOption) {
    super(value);
  }
  static identity: Symbol = Symbol('borderImage');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderImage(node);
    } else {
      let sliceTop: Length | undefined;
      let sliceRight: Length | undefined;
      let sliceBottom: Length | undefined;
      let sliceLeft: Length | undefined;
      let repeat: RepeatMode | undefined;
      let source: string | Resource | LinearGradient | undefined;
      let sourceAngle: number | string | undefined;
      let sourceDirection: GradientDirection | undefined;
      let sourceColors: Array<any> | undefined;
      let sourceRepeating: boolean | undefined;
      let widthTop: Length | undefined;
      let widthRight: Length | undefined;
      let widthBottom: Length | undefined;
      let widthLeft: Length | undefined;
      let outsetTop: Length | undefined;
      let outsetRight: Length | undefined;
      let outsetBottom: Length | undefined;
      let outsetLeft: Length | undefined;
      let fill: boolean | undefined;

      if (!isUndefined(this.value.slice)) {
        if (isLengthType(this.value.slice) || isResource(this.value.slice)) {
          let tmpSlice = this.value.slice as Length;
          sliceTop = tmpSlice;
          sliceRight = tmpSlice;
          sliceBottom = tmpSlice;
          sliceLeft = tmpSlice;
        } else {
          let tmpSlice = this.value.slice as EdgeWidths;
          sliceTop = tmpSlice.top;
          sliceRight = tmpSlice.right;
          sliceBottom = tmpSlice.bottom;
          sliceLeft = tmpSlice.left;
        }
      }
      repeat = this.value.repeat;
      if (!isUndefined(this.value.source)) {
        if (isString(this.value.source) || isResource(this.value.source)) {
          source = this.value.source;
        } else {
          let tmpSource = this.value.source as LinearGradient;
          sourceAngle = tmpSource.angle;
          sourceDirection = tmpSource.direction;
          sourceColors = tmpSource.colors;
          sourceRepeating = tmpSource.repeating;
        }
      }
      if (!isUndefined(this.value.width)) {
        if (isLengthType(this.value.width) || isResource(this.value.width)) {
          let tmpWidth = this.value.width as Length;
          widthTop = tmpWidth;
          widthRight = tmpWidth;
          widthBottom = tmpWidth;
          widthLeft = tmpWidth;
        } else {
          let tmpWidth = this.value.width as EdgeWidths;
          widthTop = tmpWidth.top;
          widthRight = tmpWidth.right;
          widthBottom = tmpWidth.bottom;
          widthLeft = tmpWidth.left;
        }
      }
      if (!isUndefined(this.value.outset)) {
        if (isLengthType(this.value.outset) || isResource(this.value.outset)) {
          let tmpOutset = this.value.outset as Length;
          outsetTop = tmpOutset;
          outsetRight = tmpOutset;
          outsetBottom = tmpOutset;
          outsetLeft = tmpOutset;
        } else {
          let tmpOutset = this.value.outset as EdgeWidths;
          outsetTop = tmpOutset.top;
          outsetRight = tmpOutset.right;
          outsetBottom = tmpOutset.bottom;
          outsetLeft = tmpOutset.left;
        }
      }
      fill = this.value.fill;
      getUINativeModule().common.setBorderImage(node,
        sliceTop, sliceRight, sliceBottom, sliceLeft,
        repeat,
        source, sourceAngle, sourceDirection, sourceColors, sourceRepeating,
        widthTop, widthRight, widthBottom, widthLeft,
        outsetTop, outsetRight, outsetBottom, outsetLeft,
        fill);
    }
  }
}

class BorderModifier extends ModifierWithKey<ArkBorder> {
  constructor(value: ArkBorder) {
    super(value);
  }
  static identity: Symbol = Symbol('border');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorder(node);
    } else {
      getUINativeModule().common.setBorder(node,
        this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor,
        this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
        this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
    }
  }

  checkObjectDiff(): boolean {
    return this.value.checkObjectDiff(this.stageValue);
  }
}

class OutlineColorModifier extends ModifierWithKey<ResourceColor | EdgeColors> {
  constructor(value: ResourceColor | EdgeColors) {
    super(value);
  }
  static identity: Symbol = Symbol('outlineColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOutlineColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().common.setOutlineColor(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setOutlineColor(node, (this.value as EdgeColors).left,
          (this.value as EdgeColors).right, (this.value as EdgeColors).top,
          (this.value as EdgeColors).bottom);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as EdgeColors).left === (this.value as EdgeColors).left &&
        (this.stageValue as EdgeColors).right === (this.value as EdgeColors).right &&
        (this.stageValue as EdgeColors).top === (this.value as EdgeColors).top &&
        (this.stageValue as EdgeColors).bottom === (this.value as EdgeColors).bottom);
    } else {
      return true;
    }
  }
}

class OutlineRadiusModifier extends ModifierWithKey<Dimension | OutlineRadiuses> {
  constructor(value: Dimension | OutlineRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('outlineRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOutlineRadius(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().common.setOutlineRadius(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setOutlineRadius(node, (this.value as OutlineRadiuses).topLeft,
          (this.value as OutlineRadiuses).topRight, (this.value as OutlineRadiuses).bottomLeft,
          (this.value as OutlineRadiuses).bottomRight);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}

class OutlineStyleModifier extends ModifierWithKey<OutlineStyle | EdgeOutlineStyles> {
  constructor(value: OutlineStyle | EdgeOutlineStyles) {
    super(value);
  }
  static identity: Symbol = Symbol('outlineStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOutlineStyle(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setOutlineStyle(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setOutlineStyle(node,
          (this.value as EdgeOutlineStyles).top,
          (this.value as EdgeOutlineStyles).right,
          (this.value as EdgeOutlineStyles).bottom,
          (this.value as EdgeOutlineStyles).left);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as EdgeOutlineStyles).top === (this.stageValue as EdgeOutlineStyles).top &&
      (this.value as EdgeOutlineStyles).right === (this.stageValue as EdgeOutlineStyles).right &&
      (this.value as EdgeOutlineStyles).bottom === (this.stageValue as EdgeOutlineStyles).bottom &&
      (this.value as EdgeOutlineStyles).left === (this.stageValue as EdgeOutlineStyles).left);
  }
}

class OutlineWidthModifier extends ModifierWithKey<Dimension | EdgeOutlineWidths> {
  constructor(value: Dimension | EdgeOutlineWidths) {
    super(value);
  }
  static identity: Symbol = Symbol('outlineWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOutlineWidth(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().common.setOutlineWidth(node, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().common.setOutlineWidth(node,
          (this.value as EdgeOutlineWidths).left,
          (this.value as EdgeOutlineWidths).right,
          (this.value as EdgeOutlineWidths).top,
          (this.value as EdgeOutlineWidths).bottom);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as EdgeOutlineWidths).left === (this.value as EdgeOutlineWidths).left &&
        (this.stageValue as EdgeOutlineWidths).right === (this.value as EdgeOutlineWidths).right &&
        (this.stageValue as EdgeOutlineWidths).top === (this.value as EdgeOutlineWidths).top &&
        (this.stageValue as EdgeOutlineWidths).bottom === (this.value as EdgeOutlineWidths).bottom);
    } else {
      return true;
    }
  }
}

class OutlineModifier extends ModifierWithKey<OutlineOptions> {
  constructor(value: OutlineOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('outline');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOutline(node);
    } else {
      let widthLeft;
      let widthRight;
      let widthTop;
      let widthBottom;
      if (!isUndefined(this.value.width) && this.value.width != null) {
        if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
          widthLeft = this.value.width;
          widthRight = this.value.width;
          widthTop = this.value.width;
          widthBottom = this.value.width;
        } else {
          widthLeft = (this.value.width as EdgeOutlineWidths).left;
          widthRight = (this.value.width as EdgeOutlineWidths).right;
          widthTop = (this.value.width as EdgeOutlineWidths).top;
          widthBottom = (this.value.width as EdgeOutlineWidths).bottom;
        }
      }
      let leftColor;
      let rightColor;
      let topColor;
      let bottomColor;
      if (!isUndefined(this.value.color) && this.value.color != null) {
        if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
          leftColor = this.value.color;
          rightColor = this.value.color;
          topColor = this.value.color;
          bottomColor = this.value.color;
        } else {
          leftColor = (this.value.color as EdgeColors).left;
          rightColor = (this.value.color as EdgeColors).right;
          topColor = (this.value.color as EdgeColors).top;
          bottomColor = (this.value.color as EdgeColors).bottom;
        }
      }
      let topLeft;
      let topRight;
      let bottomLeft;
      let bottomRight;
      if (!isUndefined(this.value.radius) && this.value.radius != null) {
        if (isNumber(this.value.radius) || isString(this.value.radius) || isResource(this.value.radius)) {
          topLeft = this.value.radius;
          topRight = this.value.radius;
          bottomLeft = this.value.radius;
          bottomRight = this.value.radius;
        } else {
          topLeft = (this.value.radius as OutlineRadiuses).topLeft;
          topRight = (this.value.radius as OutlineRadiuses).topRight;
          bottomLeft = (this.value.radius as OutlineRadiuses).bottomLeft;
          bottomRight = (this.value.radius as OutlineRadiuses).bottomRight;
        }
      }
      let styleTop;
      let styleRight;
      let styleBottom;
      let styleLeft;
      if (!isUndefined(this.value.style) && this.value.style != null) {
        if (isNumber(this.value.style) || isString(this.value.style) || isResource(this.value.style)) {
          styleTop = this.value.style;
          styleRight = this.value.style;
          styleBottom = this.value.style;
          styleLeft = this.value.style;
        } else {
          styleTop = (this.value.style as EdgeOutlineStyles).top;
          styleRight = (this.value.style as EdgeOutlineStyles).right;
          styleBottom = (this.value.style as EdgeOutlineStyles).bottom;
          styleLeft = (this.value.style as EdgeOutlineStyles).left;
        }
      }
      getUINativeModule().common.setOutline(node, widthLeft, widthRight, widthTop, widthBottom,
        leftColor, rightColor, topColor, bottomColor,
        topLeft, topRight, bottomLeft, bottomRight,
        styleTop, styleRight, styleBottom, styleLeft);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.radius, this.value.radius) ||
      !isBaseOrResourceEqual(this.stageValue.style, this.value.style);
  }
}

class ForegroundBlurStyleModifier extends ModifierWithKey<ArkForegroundBlurStyle> {
  constructor(value: ArkForegroundBlurStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('foregroundBlurStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetForegroundBlurStyle(node);
    } else {
      getUINativeModule().common.setForegroundBlurStyle(node,
        this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as ArkForegroundBlurStyle).blurStyle === (this.value as ArkForegroundBlurStyle).blurStyle &&
      (this.stageValue as ArkForegroundBlurStyle).colorMode === (this.value as ArkForegroundBlurStyle).colorMode &&
      (this.stageValue as ArkForegroundBlurStyle).adaptiveColor === (this.value as ArkForegroundBlurStyle).adaptiveColor &&
      (this.stageValue as ArkForegroundBlurStyle).scale === (this.value as ArkForegroundBlurStyle).scale);
  }
}

class BackgroundImagePositionModifier extends ModifierWithKey<Position | Alignment> {
  constructor(value: Position | Alignment) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundImagePosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundImagePosition(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setBackgroundImagePosition(node, this.value, undefined, undefined);
      } else {
        getUINativeModule().common.setBackgroundImagePosition(node, undefined, (this.value as Position)?.x, (this.value as Position)?.y);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as Position)?.x === (this.stageValue as Position)?.x &&
      (this.value as Position)?.y === (this.stageValue as Position)?.y);
  }
}

class LinearGradientBlurModifier extends ModifierWithKey<ArkLinearGradientBlur> {
  constructor(value: ArkLinearGradientBlur) {
    super(value);
  }
  static identity: Symbol = Symbol('linearGradientBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetLinearGradientBlur(node);
    } else {
      getUINativeModule().common.setLinearGradientBlur(node,
        this.value.blurRadius, this.value.fractionStops, this.value.direction);
    }
  }
  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class BackgroundImageModifier extends ModifierWithKey<ArkBackgroundImage> {
  constructor(value: ArkBackgroundImage) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundImage');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundImage(node);
    } else {
      getUINativeModule().common.setBackgroundImage(node, this.value.src, this.value.repeat);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue as ArkBackgroundImage).src === (this.value as ArkBackgroundImage).src &&
      (this.stageValue as ArkBackgroundImage).repeat === (this.value as ArkBackgroundImage).repeat);
  }
}

class BackgroundBlurStyleModifier extends ModifierWithKey<ArkBackgroundBlurStyle> {
  constructor(value: ArkBackgroundBlurStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundBlurStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundBlurStyle(node);
    } else {
      getUINativeModule().common.setBackgroundBlurStyle(node,
        this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
    }
  }
}

class BackgroundImageSizeModifier extends ModifierWithKey<SizeOptions | ImageSize> {
  constructor(value: SizeOptions | ImageSize) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundImageSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundImageSize(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setBackgroundImageSize(node, this.value, undefined, undefined);
      } else {
        getUINativeModule().common.setBackgroundImageSize(node, undefined, (this.value as SizeOptions)?.width, (this.value as SizeOptions)?.height);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value as SizeOptions).width === (this.stageValue as SizeOptions).width &&
      (this.value as SizeOptions).height === (this.stageValue as SizeOptions).height);
  }
}

class TranslateModifier extends ModifierWithKey<TranslateOptions> {
  constructor(value: TranslateOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('translate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTranslate(node);
    } else {
      getUINativeModule().common.setTranslate(node, this.value.x, this.value.y, this.value.z);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z);
  }
}

class ScaleModifier extends ModifierWithKey<ScaleOptions> {
  constructor(value: ScaleOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('scale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetScale(node);
    } else {
      getUINativeModule().common.setScale(node, this.value.x, this.value.y, this.value.z, this.value.centerX, this.value.centerY);
    }
  }
  checkObjectDiff(): boolean {
    return !(
      this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z &&
      this.value.centerX === this.stageValue.centerX &&
      this.value.centerY === this.stageValue.centerY
    );
  }
}

class RotateModifier extends ModifierWithKey<RotateOptions> {
  constructor(value: RotateOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('rotate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRotate(node);
    } else {
      getUINativeModule().common.setRotate(node, this.value.x, this.value.y, this.value.z, this.value.angle,
        this.value.centerX, this.value.centerY, this.value.centerY, this.value.perspective);
    }
  }
  checkObjectDiff(): boolean {
    return !(
      this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z &&
      this.value.angle === this.stageValue.angle &&
      this.value.centerX === this.stageValue.centerX &&
      this.value.centerY === this.stageValue.centerY &&
      this.value.centerZ === this.stageValue.centerZ &&
      this.value.perspective === this.stageValue.perspective
    );
  }
}

class GeometryTransitionModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('geometryTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGeometryTransition(node);
    } else {
      getUINativeModule().common.setGeometryTransition(node, this.value);
    }
  }
}

class BlendModeModifier extends ModifierWithKey<ArkBlendMode> {
  constructor(value: ArkBlendMode) {
    super(value);
  }
  static identity: Symbol = Symbol('blendMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBlendMode(node);
    } else {
      getUINativeModule().common.setBlendMode(node, this.value.blendMode, this.value.blendApplyType);
    }
  }
}

class ClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('clip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClip(node);
    } else {
      getUINativeModule().common.setClip(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return true;
  }
}

class MaskModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('mask');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMask(node);
    } else {
      getUINativeModule().common.setMask(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return true;
  }
}

class PixelStretchEffectModifier extends ModifierWithKey<PixelStretchEffectOptions> {
  constructor(value: PixelStretchEffectOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('pixelStretchEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPixelStretchEffect(node);
    } else {
      getUINativeModule().common.setPixelStretchEffect(node,
        this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as PixelStretchEffectOptions).left === (this.value as PixelStretchEffectOptions).left &&
      (this.stageValue as PixelStretchEffectOptions).right === (this.value as PixelStretchEffectOptions).right &&
      (this.stageValue as PixelStretchEffectOptions).top === (this.value as PixelStretchEffectOptions).top &&
      (this.stageValue as PixelStretchEffectOptions).bottom === (this.value as PixelStretchEffectOptions).bottom);
  }
}

class LightUpEffectModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('lightUpEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetLightUpEffect(node);
    } else {
      getUINativeModule().common.setLightUpEffect(node, this.value);
    }
  }
}

class SphericalEffectModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('sphericalEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSphericalEffect(node);
    } else {
      getUINativeModule().common.setSphericalEffect(node, this.value);
    }
  }
}

class RenderGroupModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('renderGroup');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRenderGroup(node);
    } else {
      getUINativeModule().common.setRenderGroup(node, this.value);
    }
  }
}

class RenderFitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('renderFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRenderFit(node);
    } else {
      getUINativeModule().common.setRenderFit(node, this.value);
    }
  }
}

class UseEffectModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('useEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetUseEffect(node);
    } else {
      getUINativeModule().common.setUseEffect(node, this.value);
    }
  }
}

class ForegroundColorModifier extends ModifierWithKey<ResourceColor | ColoringStrategy> {
  constructor(value: ResourceColor | ColoringStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('foregroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetForegroundColor(node);
    } else {
      getUINativeModule().common.setForegroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MotionPathModifier extends ModifierWithKey<MotionPathOptions> {
  constructor(value: MotionPathOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('motionPath');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMotionPath(node);
    } else {
      let path: string;
      let rotatable: boolean;
      let from: number;
      let to: number;
      if (isString(this.value.path)) {
        path = this.value.path;
      }
      if (isBoolean(this.value.rotatable)) {
        rotatable = this.value.rotatable;
      }
      if (isNumber(this.value.from) && isNumber(this.value.to)) {
        from = this.value.from;
        to = this.value.to;
      }
      getUINativeModule().common.setMotionPath(node, path, from, to, rotatable);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value.path === this.stageValue.path &&
      this.value.from === this.stageValue.from &&
      this.value.to === this.stageValue.to &&
      this.value.rotatable === this.stageValue.rotatable);
  }
}

class GroupDefaultFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('groupDefaultFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGroupDefaultFocus(node);
    } else {
      getUINativeModule().common.setGroupDefaultFocus(node, this.value);
    }
  }
}

class FocusOnTouchModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('focusOnTouch');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFocusOnTouch(node);
    } else {
      getUINativeModule().common.setFocusOnTouch(node, this.value);
    }
  }
}
class OffsetModifier extends ModifierWithKey<Position> {
  constructor(value: Position) {
    super(value);
  }
  static identity: Symbol = Symbol('offset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOffset(node);
    } else {
      getUINativeModule().common.setOffset(node, this.value?.x, this.value?.y);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}

class MarkAnchorModifier extends ModifierWithKey<Position> {
  constructor(value: Position) {
    super(value);
  }
  static identity: Symbol = Symbol('markAnchor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMarkAnchor(node);
    } else {
      getUINativeModule().common.setMarkAnchor(node, this.value?.x, this.value?.y);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}
class DefaultFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('defaultFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDefaultFocus(node);
    } else {
      getUINativeModule().common.setDefaultFocus(node, this.value);
    }
  }
}

class FocusableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('focusable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFocusable(node);
    } else {
      getUINativeModule().common.setFocusable(node, this.value);
    }
  }
}

class TouchableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('touchable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTouchable(node);
    } else {
      getUINativeModule().common.setTouchable(node, this.value);
    }
  }
}

class MarginModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('margin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMargin(node);
    } else {
      getUINativeModule().common.setMargin(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class PaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('padding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPadding(node);
    } else {
      getUINativeModule().common.setPadding(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class VisibilityModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('visibility');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetVisibility(node);
    } else {
      getUINativeModule().common.setVisibility(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class AccessibilityTextModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityText(node);
    } else {
      getUINativeModule().common.setAccessibilityText(node, this.value);
    }
  }
}

class AllowDropModifier extends ModifierWithKey<Array<UniformDataType>> {
  constructor(value: Array<UniformDataType>) {
    super(value);
  }
  static identity: Symbol = Symbol('allowDrop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAllowDrop(node);
    } else {
      getUINativeModule().common.setAllowDrop(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(Array.isArray(this.value) && Array.isArray(this.stageValue) &&
      this.value.length === this.stageValue.length &&
      this.value.every((value, index) => value === this.stageValue[index]));
  }
}

class AccessibilityLevelModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityLevel');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityLevel(node);
    } else {
      getUINativeModule().common.setAccessibilityLevel(node, this.value);
    }
  }
}

class AccessibilityDescriptionModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityDescription');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityDescription(node);
    } else {
      getUINativeModule().common.setAccessibilityDescription(node, this.value);
    }
  }
}

class DirectionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('direction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDirection(node);
    } else {
      getUINativeModule().common.setDirection(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class AlignRulesModifier extends ModifierWithKey<ArkAlignRules> {
  constructor(value: ArkAlignRules) {
    super(value);
  }
  static identity: Symbol = Symbol('alignRules');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAlignRules(node);
    } else {
      getUINativeModule().common.setAlignRules(node, this.value.left,
        this.value.middle, this.value.right, this.value.top, this.value.center, this.value.bottom);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.left, this.value.left) ||
      !isBaseOrResourceEqual(this.stageValue.middle, this.value.middle) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.center, this.value.center) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom);
  }
}

class ExpandSafeAreaModifier extends ModifierWithKey<ArkSafeAreaExpandOpts | undefined> {
  constructor(value: ArkSafeAreaExpandOpts | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('expandSafeArea');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetExpandSafeArea(node);
    } else {
      getUINativeModule().common.setExpandSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}

class GridSpanModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridSpan');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGridSpan(node);
    } else {
      getUINativeModule().common.setGridSpan(node, this.value!);
    }
  }
}

class GridOffsetModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGridOffset(node);
    } else {
      getUINativeModule().common.setGridOffset(node, this.value!);
    }
  }
}

class AlignSelfModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('alignSelf');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAlignSelf(node);
    } else {
      getUINativeModule().common.setAlignSelf(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('size');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSize(node);
    } else {
      getUINativeModule().common.setSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

class DisplayPriorityModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('displayPriority');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDisplayPriority(node);
    } else {
      getUINativeModule().common.setDisplayPriority(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class IdModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('id');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetId(node);
    } else {
      getUINativeModule().common.setId(node, this.value);
    }
  }
}

class KeyModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('key');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetKey(node);
    } else {
      getUINativeModule().common.setKey(node, this.value);
    }
  }
}

class RestoreIdModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('restoreId');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRestoreId(node);
    } else {
      getUINativeModule().common.setRestoreId(node, this.value);
    }
  }
}

class TabIndexModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('tabIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTabIndex(node);
    } else {
      getUINativeModule().common.setTabIndex(node, this.value);
    }
  }
}

class ObscuredModifier extends ModifierWithKey<Array<ObscuredReasons>> {
  constructor(value: Array<ObscuredReasons>) {
    super(value);
  }
  static identity: Symbol = Symbol('obscured');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || (!Array.isArray(this.value))) {
      getUINativeModule().common.resetObscured(node);
    } else {
      getUINativeModule().common.setObscured(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(Array.isArray(this.value) && Array.isArray(this.stageValue) &&
      this.value.length === this.stageValue.length &&
      this.value.every((value, index) => value === this.stageValue[index]));
  }
}

class BackgroundEffectModifier extends ModifierWithKey<BackgroundEffectOptions> {
  constructor(options: BackgroundEffectOptions) {
    super(options);
  }
  static identity: Symbol = Symbol('backgroundEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundEffect(node);
    } else {
      getUINativeModule().common.setBackgroundEffect(node, this.value.radius, this.value.saturation,
        this.value.brightness, this.value.color, this.value.adaptiveColor, this.value.blurOptions?.grayscale);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.radius === this.stageValue.radius && this.value.saturation === this.stageValue.saturation &&
      this.value.brightness === this.stageValue.brightness &&
      isBaseOrResourceEqual(this.stageValue.color, this.value.color) &&
      this.value.adaptiveColor === this.stageValue.adaptiveColor &&
      this.value.blurOptions?.grayscale === this.stageValue.blurOptions?.grayscale);
  }
}

class BackgroundBrightnessModifier extends ModifierWithKey<BackgroundBrightnessOptions> {
  constructor(params: BackgroundBrightnessOptions) {
    super(params);
  }
  static identity: Symbol = Symbol('backgroundBrightness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundBrightness(node);
    } else {
      getUINativeModule().common.setBackgroundBrightness(node, this.value.rate, this.value.lightUpDegree);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.rate === this.stageValue.rate && this.value.lightUpDegree === this.stageValue.lightUpDegree);
  }
}

class DragPreviewOptionsModifier extends ModifierWithKey<DragPreviewOptions> {
  constructor(value: DragPreviewOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('dragPreviewOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDragPreviewOptions(node);
    } else {
      getUINativeModule().common.setDragPreviewOptions(node, this.value.mode);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.mode === this.stageValue.mode);
  }
}

class MouseResponseRegionModifier extends ModifierWithKey<Array<Rectangle> | Rectangle> {
  constructor(value: Array<Rectangle> | Rectangle) {
    super(value);
  }
  static identity = Symbol('mouseResponseRegion');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMouseResponseRegion(node);
    } else {
      let responseRegion: (number | string | Resource)[] = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push(this.value[i].x ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].y ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].width ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].height ?? 'PLACEHOLDER');
        }
      } else {
        responseRegion.push(this.value.x ?? 'PLACEHOLDER');
        responseRegion.push(this.value.y ?? 'PLACEHOLDER');
        responseRegion.push(this.value.width ?? 'PLACEHOLDER');
        responseRegion.push(this.value.height ?? 'PLACEHOLDER');
      }
      getUINativeModule().common.setMouseResponseRegion(node, responseRegion, responseRegion.length);
    }
  }

  checkObjectDiff(): boolean {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      } else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height)
          )) {
            return true;
          }
        }
        return false;
      }
    } else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)
      ));
    } else {
      return false;
    }
  }
}

class ResponseRegionModifier extends ModifierWithKey<Array<Rectangle> | Rectangle> {
  constructor(value: Array<Rectangle> | Rectangle) {
    super(value);
  }
  static identity = Symbol('responseRegion');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetResponseRegion(node);
    } else {
      let responseRegion: (number | string | Resource)[] = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push(this.value[i].x ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].y ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].width ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].height ?? 'PLACEHOLDER');
        }
      } else {
        responseRegion.push(this.value.x ?? 'PLACEHOLDER');
        responseRegion.push(this.value.y ?? 'PLACEHOLDER');
        responseRegion.push(this.value.width ?? 'PLACEHOLDER');
        responseRegion.push(this.value.height ?? 'PLACEHOLDER');
      }
      getUINativeModule().common.setResponseRegion(node, responseRegion, responseRegion.length);
    }
  }

  checkObjectDiff(): boolean {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      } else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height)
          )) {
            return true;
          }
        }
        return false;
      }
    } else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)
      ));
    } else {
      return false;
    }
  }
}
class FlexGrowModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('flexGrow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFlexGrow(node);
    } else {
      getUINativeModule().common.setFlexGrow(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class FlexShrinkModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('flexShrink');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFlexShrink(node);
    } else {
      getUINativeModule().common.setFlexShrink(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class AspectRatioModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('aspectRatio');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAspectRatio(node);
    } else {
      getUINativeModule().common.setAspectRatio(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ConstraintSizeModifier extends ModifierWithKey<ConstraintSizeOptions> {
  constructor(value: ConstraintSizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('constraintSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetConstraintSize(node);
    } else {
      getUINativeModule().common.setConstraintSize(node, this.value.minWidth,
        this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.minWidth, this.value.minWidth) ||
      !isBaseOrResourceEqual(this.stageValue.maxWidth, this.value.maxWidth) ||
      !isBaseOrResourceEqual(this.stageValue.minHeight, this.value.minHeight) ||
      !isBaseOrResourceEqual(this.stageValue.maxHeight, this.value.maxHeight);
  }
}

class FlexBasisModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('flexBasis');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFlexBasis(node);
    } else {
      getUINativeModule().common.setFlexBasis(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class LayoutWeightModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('layoutWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetLayoutWeight(node);
    } else {
      getUINativeModule().common.setLayoutWeight(node, this.value!);
    }
  }
}

class EnabledModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('enabled');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetEnabled(node);

    } else {
      getUINativeModule().common.setEnabled(node, this.value);
    }
  }
}

class UseShadowBatchingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('useShadowBatching');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetUseShadowBatching(node);

    } else {
      getUINativeModule().common.setUseShadowBatching(node, this.value);
    }
  }
}

class MonopolizeEventsModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('monopolizeEvents');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMonopolizeEvents(node);

    } else {
      getUINativeModule().common.setMonopolizeEvents(node, this.value);
    }
  }
}

class DraggableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('draggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDraggable(node);
    } else {
      getUINativeModule().common.setDraggable(node, this.value);
    }
  }
}

class AccessibilityGroupModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityGroup');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityGroup(node);
    } else {
      getUINativeModule().common.setAccessibilityGroup(node, this.value);
    }
  }
}

class HoverEffectModifier extends Modifier<HoverEffect> {
  constructor(value: HoverEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('hoverEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetHoverEffect(node);
    } else {
      getUINativeModule().common.setHoverEffect(node, this.value);
    }
  }
}

class ClickEffectModifier extends ModifierWithKey<ClickEffect | null> {
  constructor(value: ClickEffect | null) {
    super(value);
  }
  static identity: Symbol = Symbol('clickEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().common.resetClickEffect(node);
    } else {
      getUINativeModule().common.setClickEffect(node, this.value.level, this.value.scale);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.value.level === this.stageValue.level) && (this.value.scale === this.stageValue.scale));
  }
}

class KeyBoardShortCutModifier extends ModifierWithKey<ArkKeyBoardShortCut> {
  constructor(value: ArkKeyBoardShortCut) {
    super(value);
  }
  static identity: Symbol = Symbol('keyboardShortcut');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetKeyBoardShortCut(node);
    } else {
      getUINativeModule().common.setKeyBoardShortCut(node, this.value.value, this.value.keys);
    }
  }
  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class TransitionModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('transition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTransition(node);
    } else {
      getUINativeModule().common.setTransition(node, this.value);
    }
  }
}

class SharedTransitionModifier extends ModifierWithKey<ArkSharedTransition> {
  constructor(value: ArkSharedTransition) {
    super(value);
  }
  static identity: Symbol = Symbol('sharedTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSharedTransition(node);
    } else {
      getUINativeModule().common.setSharedTransition(node, this.value.id, this.value.options);
    }
  }
}

const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
type basicType = string | number | bigint | boolean | symbol | undefined | object | null;
const isString = (val: basicType): boolean => typeof val === 'string';
const isNumber = (val: basicType): boolean => typeof val === 'number';
const isBigint = (val: basicType): boolean => typeof val === 'bigint';
const isBoolean = (val: basicType): boolean => typeof val === 'boolean';
const isSymbol = (val: basicType): boolean => typeof val === 'symbol';
const isUndefined = (val: basicType): boolean => typeof val === 'undefined';
const isObject = (val: basicType): boolean => typeof val === 'object';
const isFunction = (val: basicType): boolean => typeof val === 'function';
const isLengthType = (val: any): boolean => typeof val === 'string' || typeof val === 'number';

function modifier<T extends number | string | boolean | Equable, M extends Modifier<T>>(
  modifiers: Map<Symbol, Modifier<number | string | boolean | Equable>>,
  modifierClass: new (value: T) => M,
  value: T
) {
  const identity: Symbol = (modifierClass as any)['identity'];
  const item = modifiers.get(identity);
  if (item) {
    item.stageValue = value;
  } else {
    modifiers.set(identity, new modifierClass(value));
  }
}

function modifierWithKey<T extends number | string | boolean | object, M extends ModifierWithKey<T>>(
  modifiers: Map<Symbol, ModifierWithKey<number | string | boolean | object>>,
  identity: Symbol,
  modifierClass: new (value: T) => M,
  value: T
) {
  const item = modifiers.get(identity);
  if (item) {
    item.stageValue = value;
  } else {
    modifiers.set(identity, new modifierClass(value));
  }
}

class ArkComponent implements CommonMethod<CommonAttribute> {
  _modifiers: Map<Symbol, Modifier<number | string | boolean | Equable>>;
  _modifiersWithKeys: Map<Symbol, ModifierWithKey<number | string | boolean | object>>;
  nativePtr: KNode;

  constructor(nativePtr: KNode) {
    this._modifiers = new Map();
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
  }

  applyModifierPatch(): void {
    let expiringItems = [];
    let expiringItemsWithKeys = [];
    this._modifiers.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItems.push(key);
      }
    });
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItems.forEach(key => {
      this._modifiers.delete(key);
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  outline(value: OutlineOptions): this {
    modifierWithKey(this._modifiersWithKeys, OutlineModifier.identity, OutlineModifier, value);
    return this;
  }
  outlineColor(value: ResourceColor | EdgeColors): this {
    modifierWithKey(this._modifiersWithKeys, OutlineColorModifier.identity, OutlineColorModifier, value);
    return this;
  }
  outlineRadius(value: Dimension | OutlineRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, OutlineRadiusModifier.identity, OutlineRadiusModifier, value);
    return this;
  }
  outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
    modifierWithKey(this._modifiersWithKeys, OutlineStyleModifier.identity, OutlineStyleModifier, value);
    return this;
  }
  outlineWidth(value: Dimension | EdgeOutlineWidths): this {
    modifierWithKey(this._modifiersWithKeys, OutlineWidthModifier.identity, OutlineWidthModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier, value);
    return this;
  }

  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier, value);
    return this;
  }

  expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length > 0) {
      let safeAreaType: string | number = '';
      for (let param of types) {
        if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
        } else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length > 0) {
      let safeAreaEdge: string | number = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
        } else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, ExpandSafeAreaModifier.identity, ExpandSafeAreaModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, ExpandSafeAreaModifier.identity, ExpandSafeAreaModifier, opts);
    }
    return this;
  }

  backgroundEffect(options: BackgroundEffectOptions): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundEffectModifier.identity,
      BackgroundEffectModifier, options);
    return this;
  }

  backgroundBrightness(params: BackgroundBrightnessOptions): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundBrightnessModifier.identity,
      BackgroundBrightnessModifier, params);
    return this;
  }

  dragPreviewOptions(value: DragPreviewOptions): this {
    modifierWithKey(this._modifiersWithKeys, DragPreviewOptionsModifier.identity,
      DragPreviewOptionsModifier, value);
    return this;
  }

  responseRegion(value: Array<Rectangle> | Rectangle): this {
    modifierWithKey(this._modifiersWithKeys, ResponseRegionModifier.identity,
      ResponseRegionModifier, value);
    return this;
  }

  mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
    modifierWithKey(this._modifiersWithKeys, MouseResponseRegionModifier.identity,
      MouseResponseRegionModifier, value);
    return this;
  }

  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, SizeModifier.identity, SizeModifier, value);
    return this;
  }

  constraintSize(value: ConstraintSizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, ConstraintSizeModifier.identity,
      ConstraintSizeModifier, value);
    return this;
  }

  touchable(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, TouchableModifier.identity, TouchableModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, TouchableModifier.identity, TouchableModifier, undefined);
    }
    return this;
  }

  hitTestBehavior(value: HitTestMode): this {
    if (value) {
      modifierWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity, HitTestBehaviorModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity, HitTestBehaviorModifier, undefined);
    }
    return this;
  }

  layoutWeight(value: number | string): this {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, value);
    } else if (isString(value) && !isNaN(Number(value))) {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, parseInt(value.toString()));
    } else {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, undefined);
    }
    return this;
  }

  padding(value: Padding | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = (<Margin>value).top;
        arkValue.right = (<Margin>value).right;
        arkValue.bottom = (<Margin>value).bottom;
        arkValue.left = (<Margin>value).left;
      }
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, undefined);
    }
    return this;
  }

  margin(value: Margin | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = (<Margin>value).top;
        arkValue.right = (<Margin>value).right;
        arkValue.bottom = (<Margin>value).bottom;
        arkValue.left = (<Margin>value).left;
      }
      modifierWithKey(this._modifiersWithKeys, MarginModifier.identity, MarginModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, MarginModifier.identity, MarginModifier, undefined);
    }
    return this;
  }

  background(builder: CustomBuilder, options?: { align?: Alignment }): this {
    throw new Error('Method not implemented.');
  }

  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier, value);
    return this;
  }

  backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
    let arkBackgroundImage = new ArkBackgroundImage();
    arkBackgroundImage.src = src;
    arkBackgroundImage.repeat = repeat;
    modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier, arkBackgroundImage);
    return this;
  }

  backgroundImageSize(value: SizeOptions | ImageSize): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier, value);
    return this;
  }

  backgroundImagePosition(value: Position | Alignment): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier, value);
    return this;
  }

  backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, BackgroundBlurStyleModifier.identity,
        BackgroundBlurStyleModifier, undefined);
      return this;
    }
    let arkBackgroundBlurStyle = new ArkBackgroundBlurStyle();
    arkBackgroundBlurStyle.blurStyle = value;
    if (typeof options === 'object') {
      arkBackgroundBlurStyle.colorMode = options.colorMode;
      arkBackgroundBlurStyle.adaptiveColor = options.adaptiveColor;
      arkBackgroundBlurStyle.scale = options.scale;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundBlurStyleModifier.identity,
      BackgroundBlurStyleModifier, arkBackgroundBlurStyle);
    return this;
  }

  foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, ForegroundBlurStyleModifier.identity,
        ForegroundBlurStyleModifier, undefined);
      return this;
    }
    let arkForegroundBlurStyle = new ArkForegroundBlurStyle();
    arkForegroundBlurStyle.blurStyle = value;
    if (typeof options === 'object') {
      arkForegroundBlurStyle.colorMode = options.colorMode;
      arkForegroundBlurStyle.adaptiveColor = options.adaptiveColor;
      arkForegroundBlurStyle.scale = options.scale;
    }
    modifierWithKey(this._modifiersWithKeys, ForegroundBlurStyleModifier.identity,
      ForegroundBlurStyleModifier, arkForegroundBlurStyle);
    return this;
  }

  opacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, OpacityModifier.identity, OpacityModifier, value);
    return this;
  }

  border(value: BorderOptions): this {
    let arkBorder = new ArkBorder();
    if (isUndefined(value)) {
      arkBorder = undefined;
    }

    if (!isUndefined(value?.width) && value?.width !== null) {
      if (isNumber(value.width) || isString(value.width) || isResource(value.width)) {
        arkBorder.arkWidth.left = value.width;
        arkBorder.arkWidth.right = value.width;
        arkBorder.arkWidth.top = value.width;
        arkBorder.arkWidth.bottom = value.width;
      } else {
        arkBorder.arkWidth.left = (value.width as EdgeWidths).left;
        arkBorder.arkWidth.right = (value.width as EdgeWidths).right;
        arkBorder.arkWidth.top = (value.width as EdgeWidths).top;
        arkBorder.arkWidth.bottom = (value.width as EdgeWidths).bottom;
      }
    }
    if (!isUndefined(value?.color) && value?.color !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        arkBorder.arkColor.leftColor = value.color;
        arkBorder.arkColor.rightColor = value.color;
        arkBorder.arkColor.topColor = value.color;
        arkBorder.arkColor.bottomColor = value.color;
      } else {
        arkBorder.arkColor.leftColor = (value.color as EdgeColors).left;
        arkBorder.arkColor.rightColor = (value.color as EdgeColors).right;
        arkBorder.arkColor.topColor = (value.color as EdgeColors).top;
        arkBorder.arkColor.bottomColor = (value.color as EdgeColors).bottom;
      }
    }
    if (!isUndefined(value?.radius) && value?.radius !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        arkBorder.arkRadius.topLeft = value.radius;
        arkBorder.arkRadius.topRight = value.radius;
        arkBorder.arkRadius.bottomLeft = value.radius;
        arkBorder.arkRadius.bottomRight = value.radius;
      } else {
        arkBorder.arkRadius.topLeft = (value.radius as BorderRadiuses)?.topLeft;
        arkBorder.arkRadius.topRight = (value.radius as BorderRadiuses)?.topRight;
        arkBorder.arkRadius.bottomLeft = (value.radius as BorderRadiuses)?.bottomLeft;
        arkBorder.arkRadius.bottomRight = (value.radius as BorderRadiuses)?.bottomRight;
      }
    }
    if (!isUndefined(value?.style) && value?.style !== null) {
      let arkBorderStyle = new ArkBorderStyle();
      if (arkBorderStyle.parseBorderStyle(value.style)) {
        if (!isUndefined(arkBorderStyle.style)) {
          arkBorder.arkStyle.top = arkBorderStyle.style;
          arkBorder.arkStyle.left = arkBorderStyle.style;
          arkBorder.arkStyle.bottom = arkBorderStyle.style;
          arkBorder.arkStyle.right = arkBorderStyle.style;
        } else {
          arkBorder.arkStyle.top = arkBorderStyle.top;
          arkBorder.arkStyle.left = arkBorderStyle.left;
          arkBorder.arkStyle.bottom = arkBorderStyle.bottom;
          arkBorder.arkStyle.right = arkBorderStyle.right;
        }
      }
    }
    modifierWithKey(this._modifiersWithKeys, BorderModifier.identity, BorderModifier, arkBorder);
    return this;
  }

  borderStyle(value: BorderStyle | EdgeStyles): this {
    modifierWithKey(this._modifiersWithKeys, BorderStyleModifier.identity, BorderStyleModifier, value);
    return this;
  }

  borderWidth(value: Length | EdgeWidths): this {
    modifierWithKey(this._modifiersWithKeys, BorderWidthModifier.identity, BorderWidthModifier, value);
    return this;
  }

  borderColor(value: ResourceColor | EdgeColors): this {
    modifierWithKey(this._modifiersWithKeys, BorderColorModifier.identity, BorderColorModifier, value);
    return this;
  }

  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, BorderRadiusModifier.identity, BorderRadiusModifier, value);
    return this;
  }


  borderImage(value: BorderImageOption): this {
    modifierWithKey(this._modifiersWithKeys, BorderImageModifier.identity, BorderImageModifier, value);
    return this;
  }

  foregroundColor(value: ResourceColor | ColoringStrategy): this {
    modifierWithKey(this._modifiersWithKeys, ForegroundColorModifier.identity, ForegroundColorModifier, value);
    return this;
  }

  onClick(event: (event?: ClickEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  hoverEffect(value: HoverEffect): this {
    modifier(this._modifiers, HoverEffectModifier, value);
    return this;
  }

  onMouse(event: (event?: MouseEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onTouch(event: (event?: TouchEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  onKeyEvent(event: (event?: KeyEvent) => void): this {
    throw new Error('Method not implemented.');
  }

  focusable(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, undefined);
    }
    return this;
  }

  onFocus(event: () => void): this {
    throw new Error('Method not implemented.');
  }

  onBlur(event: () => void): this {
    throw new Error('Method not implemented.');
  }

  tabIndex(index: number): this {
    if (typeof index !== 'number') {
      modifierWithKey(this._modifiersWithKeys, TabIndexModifier.identity, TabIndexModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, TabIndexModifier.identity, TabIndexModifier, index);
    }
    return this;
  }

  defaultFocus(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity, DefaultFocusModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity, DefaultFocusModifier, undefined);
    }
    return this;
  }

  groupDefaultFocus(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity, GroupDefaultFocusModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity, GroupDefaultFocusModifier, undefined);
    }
    return this;
  }

  focusOnTouch(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity, FocusOnTouchModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity, FocusOnTouchModifier, undefined);
    }
    return this;
  }

  animation(value: AnimateParam): this {
    throw new Error('Method not implemented.');
  }

  transition(value: TransitionOptions | TransitionEffect): this {
    modifierWithKey(this._modifiersWithKeys, TransitionModifier.identity, TransitionModifier, value);
    return this;
  }

  gesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }

  priorityGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }

  parallelGesture(gesture: GestureType, mask?: GestureMask): this {
    throw new Error('Method not implemented.');
  }

  blur(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, value);
    }
    return this;
  }

  linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
    if (isUndefined(value) || isNull(value) || isUndefined(options) || isNull(options)) {
      modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier,
        undefined);
      return this;
    }
    let arkLinearGradientBlur = new ArkLinearGradientBlur();
    arkLinearGradientBlur.blurRadius = value;
    arkLinearGradientBlur.fractionStops = options.fractionStops;
    arkLinearGradientBlur.direction = options.direction;
    modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier,
      arkLinearGradientBlur);
    return this;
  }

  brightness(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, value);
    }
    return this;
  }

  contrast(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, value);
    }
    return this;
  }

  grayscale(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GrayscaleModifier.identity, GrayscaleModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, GrayscaleModifier.identity, GrayscaleModifier, value);
    }
    return this;
  }

  colorBlend(value: Color | string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
    return this;
  }

  saturate(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, value);
    }
    return this;
  }

  sepia(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, value);
    }
    return this;
  }

  invert(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, value);
    }
    return this;
  }

  hueRotate(value: number | string): this {
    if (!isNumber(value) && !isString(value)) {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, value);
    }
    return this;
  }

  useEffect(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, UseEffectModifier.identity, UseEffectModifier, value);
    return this;
  }

  backdropBlur(value: number): this {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, value);
    }
    return this;
  }

  renderGroup(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, RenderGroupModifier.identity, RenderGroupModifier, value);
    return this;
  }

  translate(value: TranslateOptions): this {
    modifierWithKey(this._modifiersWithKeys, TranslateModifier.identity, TranslateModifier, value);
    return this;
  }

  scale(value: ScaleOptions): this {
    modifierWithKey(this._modifiersWithKeys, ScaleModifier.identity, ScaleModifier, value);
    return this;
  }
  gridSpan(value: number): this {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GridSpanModifier.identity, GridSpanModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, GridSpanModifier.identity, GridSpanModifier, undefined);
    }
    return this;
  }

  gridOffset(value: number): this {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GridOffsetModifier.identity, GridOffsetModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, GridOffsetModifier.identity, GridOffsetModifier, undefined);
    }
    return this;
  }

  rotate(value: RotateOptions): this {
    modifierWithKey(this._modifiersWithKeys, RotateModifier.identity, RotateModifier, value);
    return this;
  }

  transform(value: object): this {
    modifierWithKey(this._modifiersWithKeys, TransformModifier.identity, TransformModifier, value);
    return this;
  }

  onAppear(event: () => void): this {
    throw new Error('Method not implemented.');
  }

  onDisAppear(event: () => void): this {
    throw new Error('Method not implemented.');
  }

  onAreaChange(event: (oldValue: Area, newValue: Area) => void): this {
    throw new Error('Method not implemented.');
  }

  visibility(value: Visibility): this {
    modifierWithKey(this._modifiersWithKeys, VisibilityModifier.identity, VisibilityModifier, value);
    return this;
  }

  flexGrow(value: number): this {
    modifierWithKey(this._modifiersWithKeys, FlexGrowModifier.identity, FlexGrowModifier, value);
    return this;
  }

  flexShrink(value: number): this {
    modifierWithKey(this._modifiersWithKeys, FlexShrinkModifier.identity, FlexShrinkModifier, value);
    return this;
  }

  flexBasis(value: number | string): this {
    modifierWithKey(this._modifiersWithKeys, FlexBasisModifier.identity, FlexBasisModifier, value);
    return this;
  }

  alignSelf(value: ItemAlign): this {
    modifierWithKey(this._modifiersWithKeys, AlignSelfModifier.identity, AlignSelfModifier, value);
    return this;
  }

  displayPriority(value: number): this {
    modifierWithKey(this._modifiersWithKeys, DisplayPriorityModifier.identity, DisplayPriorityModifier, value);
    return this;
  }

  zIndex(value: number): this {
    if (value !== null) {
      let zIndex = 0;
      if (typeof (value) === 'number') {
        zIndex = value;
      }
      modifierWithKey(this._modifiersWithKeys, ZIndexModifier.identity, ZIndexModifier, zIndex);
    }
    return this;
  }

  sharedTransition(id: string, options?: sharedTransitionOptions): this {
    let arkSharedTransition = new ArkSharedTransition();
    if (isString(id)) {
      arkSharedTransition.id = id;
    }
    if (typeof options === 'object') {
      arkSharedTransition.options = options;
    }
    modifierWithKey(
      this._modifiersWithKeys, SharedTransitionModifier.identity, SharedTransitionModifier, arkSharedTransition);
    return this;
  }

  direction(value: Direction): this {
    modifierWithKey(this._modifiersWithKeys, DirectionModifier.identity, DirectionModifier, value);
    return this;
  }

  align(value: Alignment): this {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, undefined);
    }
    return this;
  }

  position(value: Position): this {
    modifierWithKey(this._modifiersWithKeys, PositionModifier.identity, PositionModifier, value);
    return this;
  }

  markAnchor(value: Position): this {
    modifierWithKey(this._modifiersWithKeys, MarkAnchorModifier.identity, MarkAnchorModifier, value);
    return this;
  }

  offset(value: Position): this {
    modifierWithKey(this._modifiersWithKeys, OffsetModifier.identity, OffsetModifier, value);
    return this;
  }

  enabled(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, EnabledModifier.identity, EnabledModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, EnabledModifier.identity, EnabledModifier, undefined);
    }
    return this;
  }

  useShadowBatching(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, UseShadowBatchingModifier.identity, UseShadowBatchingModifier, value);
    return this;
  }

  monopolizeEvents(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, MonopolizeEventsModifier.identity, MonopolizeEventsModifier, value);
    return this;
  }

  useSizeType(value: {
    xs?: number | { span: number; offset: number };
    sm?: number | { span: number; offset: number };
    md?: number | { span: number; offset: number };
    lg?: number | { span: number; offset: number };
  }): this {
    throw new Error('Method not implemented.');
  }

  alignRules(value: AlignRuleOption): this {
    if (!isObject(value) || JSON.stringify(value) === '{}') {
      modifierWithKey(this._modifiersWithKeys, AlignRulesModifier.identity, AlignRulesModifier, undefined);
      return this;
    }
    let keys: string[] = ['left', 'middle', 'right', 'top', 'center', 'bottom'];
    let arkValue = new ArkAlignRules();
    for (let i = 0; i < keys.length; i++) {
      let rule = value[keys[i]];
      let alignRule: string = '';
      if (isObject(rule)) {
        let alignSign = false;
        let anchorSign = false;
        let align = rule.align;
        let anchor = rule.anchor;
        if (isString(anchor)) {
          anchorSign = true;
        }
        if (i < DIRECTION_RANGE) {
          if (align in HorizontalAlign) {
            alignSign = true;
          }
        } else {
          if (align in VerticalAlign) {
            alignSign = true;
          }
        }
        if (!alignSign && !anchorSign) {
          alignRule += '';
        } else if (!anchorSign) {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += '__container__';
        } else if (!alignSign) {
          alignRule += '2';
          alignRule += '|';
          alignRule += anchor;
        } else {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += anchor;
        }
      } else {
        alignRule += '';
      }
      switch (keys[i]) {
        case 'left':
          arkValue.left = alignRule;
          break;
        case 'middle':
          arkValue.middle = alignRule;
          break;
        case 'right':
          arkValue.right = alignRule;
          break;
        case 'top':
          arkValue.top = alignRule;
          break;
        case 'center':
          arkValue.center = alignRule;
          break;
        case 'bottom':
          arkValue.bottom = alignRule;
          break;
      }
    }
    modifierWithKey(this._modifiersWithKeys, AlignRulesModifier.identity, AlignRulesModifier, arkValue);
    return this;
  }

  aspectRatio(value: number): this {
    modifierWithKey(this._modifiersWithKeys, AspectRatioModifier.identity, AspectRatioModifier, value);
    return this;
  }

  clickEffect(value: ClickEffect | null): this {
    modifierWithKey(this._modifiersWithKeys, ClickEffectModifier.identity, ClickEffectModifier, value);
    return this;
  }

  onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this {
    throw new Error('Method not implemented.');
  }

  onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDrop(event: (event?: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this {
    throw new Error('Method not implemented.');
  }

  allowDrop(value: Array<UniformDataType>): this {
    modifierWithKey(this._modifiersWithKeys, AllowDropModifier.identity, AllowDropModifier, value);
    return this;
  }

  draggable(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, DraggableModifier.identity, DraggableModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, DraggableModifier.identity, DraggableModifier, undefined);

    }
    return this;
  }

  overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number } }): this {
    if (typeof value === 'undefined') {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, undefined);
      return this;
    }
    let arkOverlay = new ArkOverlay();
    if (arkOverlay.splitOverlayValue(value, options)) {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, arkOverlay);
    } else {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, undefined);
    }
    return this;
  }

  linearGradient(value: {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    modifierWithKey(this._modifiersWithKeys, LinearGradientModifier.identity, LinearGradientModifier, value);
    return this;
  }

  sweepGradient(value: {
    center: Array<any>;
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<any>;
    repeating?: boolean;
  }): this {
    modifierWithKey(this._modifiersWithKeys, SweepGradientModifier.identity, SweepGradientModifier, value);
    return this;
  }

  radialGradient(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }): this {
    modifierWithKey(this._modifiersWithKeys, RadialGradientModifier.identity, RadialGradientModifier, value);
    return this;
  }

  motionPath(value: MotionPathOptions): this {
    modifierWithKey(this._modifiersWithKeys, MotionPathModifier.identity, MotionPathModifier, value);
    return this;
  }

  shadow(value: ShadowOptions | ShadowStyle): this {
    modifierWithKey(this._modifiersWithKeys, ShadowModifier.identity, ShadowModifier, value);
    return this;
  }

  mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this {
    modifierWithKey(this._modifiersWithKeys, MaskModifier.identity, MaskModifier, value);
    return this;
  }

  key(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, KeyModifier.identity, KeyModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, KeyModifier.identity, KeyModifier, undefined);
    }
    return this;
  }

  id(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, IdModifier.identity, IdModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, IdModifier.identity, IdModifier, undefined);
    }
    return this;
  }

  geometryTransition(id: string): this {
    if (isString(id)) {
      modifierWithKey(this._modifiersWithKeys, GeometryTransitionModifier.identity, GeometryTransitionModifier, id);
    }
    return this;
  }

  bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
    throw new Error('Method not implemented.');
  }

  bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
    throw new Error('Method not implemented.');
  }

  bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
    throw new Error('Method not implemented.');
  }

  bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
    throw new Error('Method not implemented.');
  }

  blendMode(blendMode: BlendMode, blendApplyType?: BlendApplyType): this {
    let arkBlendMode = new ArkBlendMode();
    arkBlendMode.blendMode = blendMode;
    arkBlendMode.blendApplyType = blendApplyType;
    modifierWithKey(this._modifiersWithKeys, BlendModeModifier.identity, BlendModeModifier, arkBlendMode);
    return this;
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, ClipModifier.identity, ClipModifier, value);
    return this;
  }

  bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this {
    throw new Error('Method not implemented.');
  }

  stateStyles(value: StateStyles): this {
    throw new Error('Method not implemented.');
  }

  restoreId(value: number): this {
    if (typeof value !== 'number') {
      modifierWithKey(this._modifiersWithKeys, RestoreIdModifier.identity, RestoreIdModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, RestoreIdModifier.identity, RestoreIdModifier, value);
    }
    return this;
  }

  onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this {
    throw new Error('Method not implemented.');
  }

  sphericalEffect(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SphericalEffectModifier.identity, SphericalEffectModifier, value);
    return this;
  }

  lightUpEffect(value: number): this {
    modifierWithKey(this._modifiersWithKeys, LightUpEffectModifier.identity, LightUpEffectModifier, value);
    return this;
  }

  pixelStretchEffect(options: PixelStretchEffectOptions): this {
    modifierWithKey(this._modifiersWithKeys, PixelStretchEffectModifier.identity, PixelStretchEffectModifier, options);
    return this;
  }

  keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this {
    let keyboardShortCut = new ArkKeyBoardShortCut();
    keyboardShortCut.value = value;
    keyboardShortCut.keys = keys;
    modifierWithKey(this._modifiersWithKeys, KeyBoardShortCutModifier.identity, KeyBoardShortCutModifier, keyboardShortCut);
    return this;
  }

  accessibilityGroup(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityGroupModifier.identity, AccessibilityGroupModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityGroupModifier.identity, AccessibilityGroupModifier, undefined);

    }
    return this;
  }

  accessibilityText(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextModifier.identity, AccessibilityTextModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextModifier.identity, AccessibilityTextModifier, undefined);
    }
    return this;
  }

  accessibilityDescription(value: string): this {
    if (typeof value !== 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDescriptionModifier.identity, AccessibilityDescriptionModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDescriptionModifier.identity, AccessibilityDescriptionModifier, value);
    }
    return this;
  }

  accessibilityLevel(value: string): this {
    if (typeof value !== 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityLevelModifier.identity, AccessibilityLevelModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityLevelModifier.identity, AccessibilityLevelModifier, value);
    }
    return this;
  }

  obscured(reasons: Array<ObscuredReasons>): this {
    modifierWithKey(this._modifiersWithKeys, ObscuredModifier.identity, ObscuredModifier, reasons);
    return this;
  }

  reuseId(id: string): this {
    throw new Error('Method not implemented.');
  }

  renderFit(fitMode: RenderFit): this {
    modifierWithKey(this._modifiersWithKeys, RenderFitModifier.identity, RenderFitModifier, fitMode);
    return this;
  }

  attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
    return this;
  }
}

const isNull = (val: any) => typeof val === 'object' && val === null;
const isArray = (val: any) => Array.isArray(val);
const isDate = (val: any) => val instanceof Date;
const isRegExp = (val: any) => val instanceof RegExp;
const isError = (val: any) => val instanceof Error;
const isFloat = (val: any) => Number.isFinite(val) && !Number.isInteger(val);
const isInteger = (val: any) => Number.isInteger(val);
const isNonEmptyMap = (val: any) => val instanceof Map && val.size > 0;
const isTruthyString = (val: any) => typeof val === 'string' && val.trim() !== '';
