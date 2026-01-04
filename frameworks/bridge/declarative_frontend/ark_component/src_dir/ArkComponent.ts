/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/// <reference path="../types/index.d.ts" />
/// <reference path="../types/ArkUINativeModule.d.ts" />
const arkUINativeModule = globalThis.getArkUINativeModule();
function getUINativeModule(): any {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
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
const isNull = (val: any) => typeof val === 'object' && val === null;
const isArray = (val: any) => Array.isArray(val);
const isDate = (val: any) => val instanceof Date;
const isRegExp = (val: any) => val instanceof RegExp;
const isError = (val: any) => val instanceof Error;
const isFloat = (val: any) => Number.isFinite(val) && !Number.isInteger(val);
const isInteger = (val: any) => Number.isInteger(val);
const isNonEmptyMap = (val: any) => val instanceof Map && val.size > 0;
const isTruthyString = (val: any) => typeof val === 'string' && val.trim() !== '';

function isResource(variable: any): variable is Resource {
  return (variable as Resource)?.bundleName !== undefined;
}

function isBaseOrResourceEqual(stageValue: any, value: any): boolean {
  if (!isResource(stageValue) && !isResource(value)) {
    return (stageValue === value);
  }
  return false;
}

function deepCompareArrays(arr1: Array<any>, arr2: Array<any>): boolean {
  return (
    Array.isArray(arr1) &&
    Array.isArray(arr2) &&
    arr1.length === arr2.length &&
    arr1.every((value, index) => {
      if (Array.isArray(value) && Array.isArray(arr2[index])) {
        return deepCompareArrays(value, arr2[index]);
      } else {
        return value === arr2[index];
      }
    })
  );
}

class ModifierWithKey<T extends number | string | boolean | object | Function> {
  stageValue?: T;
  value?: T;
  constructor(value: T) {
    this.stageValue = value;
  }

  applyStage(node: KNode, component?: ArkComponent): boolean {
    if (this.stageValue === undefined || this.stageValue === null) {
      this.value = this.stageValue;
      this.applyPeer(node, true, component);
      return true;
    }
    if (component && component._needDiff) {
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
        this.applyPeer(node, false, component);
      }
    } else {
      this.value = this.stageValue;
      this.applyPeer(node, false, component);
    }
    return false;
  }

  applyStageImmediately(node: KNode, component?: ArkComponent): void {
    this.value = this.stageValue;
    if (this.stageValue === undefined || this.stageValue === null) {
      this.applyPeer(node, true, component);
      return;
    }
    this.applyPeer(node, false, component);
  }

  applyPeer(node: KNode, reset: boolean, component?: ArkComponent): void { }

  checkObjectDiff(): boolean {
    return true;
  }
}

class BackgroundModifier extends ModifierWithKey<ArkBackground> {
  constructor(value: ArkBackground) {
    super(value);
  }
  static identity: Symbol = Symbol('background');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackground(node);
    } else {
      getUINativeModule().common.setBackground(
        node, this.value.content, this.value.align, this.value.ignoresLayoutSafeAreaEdges);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.content, this.value.content) ||
      !isBaseOrResourceEqual(this.stageValue.align, this.value.align) ||
      !deepCompareArrays(this.stageValue.ignoresLayoutSafeAreaEdges, this.value.ignoresLayoutSafeAreaEdges);
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

class AllowForceDarkModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('allowForceDark');
  applyPeer(node: KNode, reset: boolean): void {
    getUINativeModule().common.allowForceDark(node, this.value);
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BindMenuModifier extends ModifierWithKey<ArkBindMenu> {
  constructor(value: ArkBindMenu) {
    super(value);
  }
  static identity: Symbol = Symbol('bindMenu');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBindMenu(node);
    } else {
      getUINativeModule().common.setBindMenu(node, this.value.content, this.value.options);
    }
  }
}

class SearchAutoCapitalizationModifier extends ModifierWithKey<ArkSearchAutoCapitalization> {
  constructor(value: ArkSearchAutoCapitalization) {
    super(value);
  }
  static identity: Symbol = Symbol('searchAutoCapitalization');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().search.resetAutoCapitalizationMode(node);
    } else {
      getUINativeModule().search.setAutoCapitalizationMode(node, this.value);
    }
  }
}

class TextAreaAutoCapitalizationModifier extends ModifierWithKey<ArkTextAreaAutoCapitalization> {
  constructor(value: ArkTextAreaAutoCapitalization) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaAutoCapitalization');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetAutoCapitalizationMode(node);
    } else {
      getUINativeModule().textArea.setAutoCapitalizationMode(node, this.value);
    }
  }
}

class TextInputAutoCapitalizationModifier extends ModifierWithKey<ArkTextInputAutoCapitalization> {
  constructor(value: ArkTextInputAutoCapitalization) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputAutoCapitalization');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textInput.resetAutoCapitalizationMode(node);
    } else {
      getUINativeModule().textInput.setAutoCapitalizationMode(node, this.value);
    }
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
  constructor(value: Length | EdgeWidths | LocalizedEdgeWidths) {
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
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().common.setBorderWidth(node,
            (this.value as LocalizedEdgeWidths).top,
            (this.value as LocalizedEdgeWidths).end,
            (this.value as LocalizedEdgeWidths).bottom,
            (this.value as LocalizedEdgeWidths).start);
        } else {
          getUINativeModule().common.setBorderWidth(node,
            (this.value as EdgeWidths).top,
            (this.value as EdgeWidths).right,
            (this.value as EdgeWidths).bottom,
            (this.value as EdgeWidths).left);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
        return !((this.stageValue as LocalizedEdgeWidths).start === (this.value as LocalizedEdgeWidths).start &&
          (this.stageValue as LocalizedEdgeWidths).end === (this.value as LocalizedEdgeWidths).end &&
          (this.stageValue as LocalizedEdgeWidths).top === (this.value as LocalizedEdgeWidths).top &&
          (this.stageValue as LocalizedEdgeWidths).bottom === (this.value as LocalizedEdgeWidths).bottom);
      }
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

class ChainModeifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('chainMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetChainMode(node);
    } else {
      getUINativeModule().common.setChainMode(node, this.value.direction, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BorderRadiusModifier extends ModifierWithKey<ArkBorderRadiusOpts | undefined> {
  constructor(value: ArkBorderRadiusOpts | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('borderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBorderRadius(node);
    } else {
      if (isNumber(this.value.value) || isString(this.value.value) || isResource(this.value.value)) {
        getUINativeModule().common.setBorderRadius(node, this.value.value, this.value.value, this.value.value, this.value.value, this.value.type);
      } else {
        if (isUndefined(this.value.value) || isNull(this.value.value)) {
          getUINativeModule().common.setBorderRadius(node, undefined, undefined, undefined, undefined, this.value.type);
          return;
        }
        if ((Object.keys(this.value.value).indexOf('topStart') >= 0) ||
            (Object.keys(this.value.value).indexOf('topEnd') >= 0) ||
            (Object.keys(this.value.value).indexOf('bottomStart') >= 0) ||
            (Object.keys(this.value.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().common.setBorderRadius(node,
            (this.value.value as LocalizedBorderRadius).topStart,
            (this.value.value as LocalizedBorderRadius).topEnd,
            (this.value.value as LocalizedBorderRadius).bottomStart,
            (this.value.value as LocalizedBorderRadius).bottomEnd,
            (this.value.type as RenderStrategy));
        } else {
          getUINativeModule().common.setBorderRadius(node,
            (this.value.value as BorderRadiuses).topLeft,
            (this.value.value as BorderRadiuses).topRight,
            (this.value.value as BorderRadiuses).bottomLeft,
            (this.value.value as BorderRadiuses).bottomRight,
            (this.value.type as RenderStrategy));
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isNull(this.value.value)) {
      return !isNull(this.stageValue.value);
    }
    if (isNull(this.stageValue.value)) {
      return !isNull(this.value.value);
    }
    if (isUndefined(this.value.value)) {
      return !isUndefined(this.stageValue.value);
    }
    if (isUndefined(this.stageValue.value)) {
      return !isUndefined(this.value.value);
    }
    if (!isResource(this.stageValue.value) && !isResource(this.value.value)) {
      if ((Object.keys(this.value.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value.value).indexOf('bottomEnd') >= 0)) {
        return !((this.stageValue.value as LocalizedBorderRadius).topStart === (this.value.value as LocalizedBorderRadius).topStart &&
          (this.stageValue.value as LocalizedBorderRadius).topEnd === (this.value.value as LocalizedBorderRadius).topEnd &&
          (this.stageValue.value as LocalizedBorderRadius).bottomStart === (this.value.value as LocalizedBorderRadius).bottomStart &&
          (this.stageValue.value as LocalizedBorderRadius).bottomEnd === (this.value.value as LocalizedBorderRadius).bottomEnd &&
          (this.stageValue.type as RenderStrategy) === (this.value.type as RenderStrategy));
      }
      return !((this.stageValue.value as BorderRadiuses).topLeft === (this.value.value as BorderRadiuses).topLeft &&
        (this.stageValue.value as BorderRadiuses).topRight === (this.value.value as BorderRadiuses).topRight &&
        (this.stageValue.value as BorderRadiuses).bottomLeft === (this.value.value as BorderRadiuses).bottomLeft &&
        (this.stageValue.value as BorderRadiuses).bottomRight === (this.value.value as BorderRadiuses).bottomRight &&
        (this.stageValue.type as RenderStrategy) === (this.value.type as RenderStrategy));
    } else {
      return true;
    }
  }
}

class PositionModifier extends ModifierWithKey<Position | Edges | LocalizedEdges> {
  constructor(value: Position | Edges | LocalizedEdges) {
    super(value);
  }
  static identity: Symbol = Symbol('position');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPosition(node);
    } else {
      if (isUndefined(this.value)) {
        getUINativeModule().common.resetPosition(node);
      } else if (('x' in this.value) || ('y' in this.value)) {
        getUINativeModule().common.setPosition(node, false, this.value.x, this.value.y);
      } else if (('top' in this.value) || ('bottom' in this.value) || ('left' in this.value) || ('start' in this.value) || ('right' in this.value) || ('end' in this.value)) {
        if (('start' in this.value)) {
          this.value.left = this.value.start;
        }
        if (('end' in this.value)) {
          this.value.right = this.value.end;
        }
        getUINativeModule().common.setPosition(node, true, this.value.top, this.value.left, this.value.bottom, this.value.right);
      } else {
        getUINativeModule().common.resetPosition(node);
      }
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y) ||
      !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.start, this.value.start) ||
      !isBaseOrResourceEqual(this.stageValue.end, this.value.end);
  }
}

class BorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors | LocalizedEdgeColors> {
  constructor(value: ResourceColor | EdgeColors | LocalizedEdgeColors) {
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
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().common.setBorderColor(node,
            (this.value as LocalizedEdgeColors).top,
            (this.value as LocalizedEdgeColors).end,
            (this.value as LocalizedEdgeColors).bottom,
            (this.value as LocalizedEdgeColors).start,
            true);
        } else {
          getUINativeModule().common.setBorderColor(node,
            (this.value as EdgeColors).top,
            (this.value as EdgeColors).right,
            (this.value as EdgeColors).bottom,
            (this.value as EdgeColors).left,
            false);
        }
      }

    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
        return !((this.stageValue as LocalizedEdgeColors).start === (this.value as LocalizedEdgeColors).start &&
          (this.stageValue as LocalizedEdgeColors).end === (this.value as LocalizedEdgeColors).end &&
          (this.stageValue as LocalizedEdgeColors).top === (this.value as LocalizedEdgeColors).top &&
          (this.stageValue as LocalizedEdgeColors).bottom === (this.value as LocalizedEdgeColors).bottom);
      }
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

class Transform3DModifier extends ModifierWithKey<object> {
  constructor(value: Matrix4Transit | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('transform3D');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetTransform3D(node);
    } else {
      getUINativeModule().common.setTransform3D(node, (this.value as Matrix).matrix4x4);
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

class ShadowModifier extends ModifierWithKey<ShadowOptions | ArkShadowStyle> {
  constructor(value: ShadowOptions | ArkShadowStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('shadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetShadow(node);
    } else {
      if (isNumber(this.value.shadowStyle)) {
        getUINativeModule().common.setShadow(node, this.value.shadowStyle, undefined, undefined, undefined, undefined, undefined, undefined);
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
    if (isNumber(this.value.shadowStyle)) {
      return true;
    }
    const stageValue = this.stageValue as ShadowOptions;
    const value = this.value as ShadowOptions;
    return !(isBaseOrResourceEqual(stageValue.radius, value.radius) &&
      stageValue.type === value.type &&
      isBaseOrResourceEqual(stageValue.color, value.color) &&
      isBaseOrResourceEqual(stageValue.offsetX, value.offsetX) &&
      isBaseOrResourceEqual(stageValue.offsetY, value.offsetY) &&
      stageValue.fill === value.fill);
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

class AlignModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
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

class LayoutGravityModifier extends ModifierWithKey<string> {
    constructor(value: string) {
      super(value);
    }
    static identity: Symbol = Symbol('layoutGravity');
    applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        getUINativeModule().common.resetLayoutGravity(node);
      } else {
        getUINativeModule().common.setLayoutGravity(node, this.value);
      }
    }
  }

class BackdropBlurModifier extends ModifierWithKey<ArkBlurOptions> {
  constructor(value: ArkBlurOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('backdropBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackdropBlur(node);
    } else {
      getUINativeModule().common.setBackdropBlur(node, this.value.value, this.value.options?.grayscale);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
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

class InvertModifier extends ModifierWithKey<number | InvertOptions> {
  constructor(value: number | InvertOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('invert');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetInvert(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setInvert(node, this.value, undefined, undefined, undefined, undefined);
      } else {
        getUINativeModule().common.setInvert(node, undefined,
          (this.value as InvertOptions).low,
          (this.value as InvertOptions).high,
          (this.value as InvertOptions).threshold,
          (this.value as InvertOptions).thresholdRange);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue as InvertOptions).high === (this.value as InvertOptions).high &&
      (this.stageValue as InvertOptions).low === (this.value as InvertOptions).low &&
      (this.stageValue as InvertOptions).threshold === (this.value as InvertOptions).threshold &&
      (this.stageValue as InvertOptions).thresholdRange === (this.value as InvertOptions).thresholdRange);
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