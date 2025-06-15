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

enum ModifierType {
  ORIGIN = 0,
  STATE = 1,
  FRAME_NODE = 2,
  EXPOSE_MODIFIER = 3,
}

type AttributeModifierWithKey = ModifierWithKey<number | string | boolean | object>;

class ObservedMap {
  private map_: Map<Symbol, AttributeModifierWithKey>;
  private changeCallback: ((key: Symbol, value: AttributeModifierWithKey) => void) | undefined;
  private isFrameNode_: boolean = false;

  constructor() {
    this.map_ = new Map();
  }

  public clear(): void {
    this.map_.clear();
  }

  public delete(key: Symbol): boolean {
    return this.map_.delete(key);
  }

  public forEach(callbackfn: (value: AttributeModifierWithKey, key: Symbol,
    map: Map<Symbol, AttributeModifierWithKey>) => void, thisArg?: any): void {
    this.map_.forEach(callbackfn, thisArg);
  }
  public get(key: Symbol): AttributeModifierWithKey | undefined {
    return this.map_.get(key);
  }
  public has(key: Symbol): boolean {
    return this.map_.has(key);
  }
  public set(key: Symbol, value: AttributeModifierWithKey): this {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a === null || _a === void 0 ? void 0 : _a(key, value);
    return this;
  }
  public get size(): number {
    return this.map_.size;
  }
  public entries(): IterableIterator<[Symbol, AttributeModifierWithKey]> {
    return this.map_.entries();
  }
  public keys(): IterableIterator<Symbol> {
    return this.map_.keys();
  }
  public values(): IterableIterator<AttributeModifierWithKey> {
    return this.map_.values();
  }
  public [Symbol.iterator](): IterableIterator<[Symbol, AttributeModifierWithKey]> {
    return this.map_.entries();
  }
  public get [Symbol.toStringTag](): string {
    return 'ObservedMapTag';
  }
  public setOnChange(callback: (key: Symbol, value: AttributeModifierWithKey) => void): void {
    if (this.changeCallback === undefined) {
      this.changeCallback = callback;
    }
  }
  public setFrameNode(isFrameNode: boolean): void {
    this.isFrameNode_ = isFrameNode;
  }
  public isFrameNode(): boolean {
    return this.isFrameNode_;
  }
}

const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;

function applyUIAttributesInit(modifier: AttributeModifier<CommonAttribute>, nativeNode: KNode): void {
  if (modifier.applyPressedAttribute == undefined && modifier.applyFocusedAttribute == undefined &&
    modifier.applyDisabledAttribute == undefined && modifier.applySelectedAttribute == undefined) {
    return;
  }
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
}

function applyUIAttributes(modifier: AttributeModifier<CommonAttribute>, nativeNode: KNode, component: ArkComponent): void {
  applyUIAttributesInit(modifier, nativeNode);
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

function isBaseOrResourceEqual(stageValue: any, value: any): boolean {
  if (!isResource(stageValue) && !isResource(value)) {
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
const SAFE_AREA_LOWER_LIMIT = 0;
const LAYOUT_SAFE_AREA_TYPE_LIMIT = 2;
const LAYOUT_SAFE_AREA_EDGE_LIMIT = 6;
const DIRECTION_RANGE = 3;

type KNode = number | null

interface Equable {
  isEqual(value: Equable): boolean;
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

class BorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses | LocalizedBorderRadius> {
  constructor(value: Length | BorderRadiuses | LocalizedBorderRadius) {
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
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
            (Object.keys(this.value).indexOf('topEnd') >= 0) ||
            (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
            (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().common.setBorderRadius(node,
            (this.value as LocalizedBorderRadius).topStart,
            (this.value as LocalizedBorderRadius).topEnd,
            (this.value as LocalizedBorderRadius).bottomStart,
            (this.value as LocalizedBorderRadius).bottomEnd);
        } else {
          getUINativeModule().common.setBorderRadius(node,
            (this.value as BorderRadiuses).topLeft,
            (this.value as BorderRadiuses).topRight,
            (this.value as BorderRadiuses).bottomLeft,
            (this.value as BorderRadiuses).bottomRight);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
        return !((this.stageValue as LocalizedBorderRadius).topStart === (this.value as LocalizedBorderRadius).topStart &&
          (this.stageValue as LocalizedBorderRadius).topEnd === (this.value as LocalizedBorderRadius).topEnd &&
          (this.stageValue as LocalizedBorderRadius).bottomStart === (this.value as LocalizedBorderRadius).bottomStart &&
          (this.stageValue as LocalizedBorderRadius).bottomEnd === (this.value as LocalizedBorderRadius).bottomEnd);
      }
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
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

class BlurModifier extends ModifierWithKey<ArkBlurOptions> {
  constructor(value: ArkBlurOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('blur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBlur(node);
    } else {
      getUINativeModule().common.setBlur(node, this.value.value, this.value.options?.grayscale);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
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
  colors: Array<any>; metricsColors?: Array<any>; repeating?: boolean;
}> {
  constructor(value: {
    center: Array<any>;
    start?: number | string; end?: number | string;
    rotation?: number | string; colors: Array<any>; metricsColors?: Array<any>; repeating?: boolean;
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
        this.value.colors, this.value.metricsColors, this.value.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.center === this.value.center) &&
      (this.stageValue.start === this.value.start) &&
      (this.stageValue.end === this.value.end) &&
      (this.stageValue.rotation === this.value.rotation) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.metricsColors === this.value.metricsColors) &&
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
      let isLocalizedBorderWidth;
      let isLocalizedBorderColor;
      let isLocalizedBorderRadius;
      if ((Object.keys(this.value.arkWidth).indexOf('start') >= 0 && isUndefined(this.value.arkWidth.start)) ||
        (Object.keys(this.value.arkWidth).indexOf('end') >= 0 && isUndefined(this.value.arkWidth.end))) {
        isLocalizedBorderWidth = true;
      } else {
        isLocalizedBorderWidth = false;
      }
      if ((Object.keys(this.value.arkColor).indexOf('startColor') >= 0 && isUndefined(this.value.arkColor.startColor)) ||
        (Object.keys(this.value.arkColor).indexOf('endColor') >= 0 && isUndefined(this.value.arkColor.endColor))) {
        isLocalizedBorderColor = true;
      } else {
        isLocalizedBorderColor = false;
      }
      if ((Object.keys(this.value.arkRadius).indexOf('topStart') >= 0 && isUndefined(this.value.arkRadius.topStart)) ||
        (Object.keys(this.value.arkRadius).indexOf('topEnd') >= 0 && isUndefined(this.value.arkRadius.topEnd)) ||
        (Object.keys(this.value.arkRadius).indexOf('bottomStart') >= 0 && isUndefined(this.value.arkRadius.bottomStart)) ||
        (Object.keys(this.value.arkRadius).indexOf('bottomEnd') >= 0 && isUndefined(this.value.arkRadius.bottomEnd))) {
        isLocalizedBorderRadius = true;
      } else {
        isLocalizedBorderRadius = false;
      }
      getUINativeModule().common.setBorderWithDashParams(node,
        this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor,
        this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
        this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left,
        this.value.arkDashGap.left, this.value.arkDashGap.right, this.value.arkDashGap.top, this.value.arkDashGap.bottom,
        this.value.arkDashWidth.left, this.value.arkDashWidth.right, this.value.arkDashWidth.top, this.value.arkDashWidth.bottom,
        this.value.arkWidth.start, this.value.arkWidth.end, this.value.arkColor.startColor, this.value.arkColor.endColor,
        this.value.arkRadius.topStart, this.value.arkRadius.topEnd, this.value.arkRadius.bottomStart, this.value.arkRadius.bottomEnd,
        isLocalizedBorderWidth, isLocalizedBorderColor, isLocalizedBorderRadius,
        this.value.arkDashGap.start, this.value.arkDashGap.end, this.value.arkDashWidth.start, this.value.arkDashWidth.end
      );
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
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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
        this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale,
          this.value.blurOptions?.grayscale);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as ArkForegroundBlurStyle).blurStyle === (this.value as ArkForegroundBlurStyle).blurStyle &&
      (this.stageValue as ArkForegroundBlurStyle).colorMode === (this.value as ArkForegroundBlurStyle).colorMode &&
      (this.stageValue as ArkForegroundBlurStyle).adaptiveColor === (this.value as ArkForegroundBlurStyle).adaptiveColor &&
      (this.stageValue as ArkForegroundBlurStyle).scale === (this.value as ArkForegroundBlurStyle).scale &&
      (this.stageValue as ArkForegroundBlurStyle).blurOptions === (this.value as ArkForegroundBlurStyle).blurOptions);
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

class BackgroundImageResizableModifier extends ModifierWithKey<ResizableOptions> {
  constructor(value: ResizableOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundImageResizable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundImageResizable(node);
    } else {
      let sliceTop: Length | undefined;
      let sliceBottom: Length | undefined;
      let sliceLeft: Length | undefined;
      let sliceRight: Length | undefined;
      if (!isUndefined(this.value.slice)) {
        let tempSlice = this.value.slice as EdgeWidths;
        sliceTop = tempSlice.top;
        sliceBottom = tempSlice.bottom;
        sliceLeft = tempSlice.left;
        sliceRight = tempSlice.right;
      }
      getUINativeModule().common.setBackgroundImageResizable(node, sliceTop, sliceBottom, sliceLeft, sliceRight);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
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
        this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale,
          this.value.blurOptions?.grayscale, this.value.policy, this.value.inactiveColor, this.value.type);
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

class RotateModifier extends ModifierWithKey<RotateOptions | RotateAngleOptions> {
  constructor(value: RotateOptions | RotateAngleOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('rotate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetRotate(node);
    } else {
      if ('angle' in this.value) {
        getUINativeModule().common.setRotate(
          node,
          this.value.x,
          this.value.y,
          this.value.z,
          this.value.angle,
          this.value.centerX,
          this.value.centerY,
          this.value.centerZ,
          this.value.perspective
        );
      } else {
        getUINativeModule().common.setRotateAngle(
          node,
          this.value.angleX,
          this.value.angleY,
          this.value.angleZ,
          this.value.centerX,
          this.value.centerY,
          this.value.centerZ,
          this.value.perspective
        );
      }
    }
  }
  checkObjectDiff(): boolean {
    if ('angle' in this.value) {
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
    } else {
      return !(
        this.value.angleX === this.stageValue.angleX &&
        this.value.angleY === this.stageValue.angleY &&
        this.value.angleZ === this.stageValue.angleZ &&
        this.value.centerX === (this.stageValue.centerX) &&
        this.value.centerY === (this.stageValue.centerY) &&
        this.value.centerZ === (this.stageValue.centerZ) &&
        this.value.perspective === this.stageValue.perspective
      );
    }
  }
}

class GeometryTransitionModifier extends ModifierWithKey<ArkGeometryTransition> {
  constructor(value: ArkGeometryTransition) {
    super(value);
  }
  static identity: Symbol = Symbol('geometryTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetGeometryTransition(node);
    } else {
      getUINativeModule().common.setGeometryTransition(node, this.value.id,
        (this.value.options as GeometryTransitionOptions)?.follow,
        (this.value.options as GeometryTransitionOptions)?.hierarchyStrategy);
    }
  }
}

class AdvancedBlendModeModifier extends ModifierWithKey<ArkBlendMode> {
  constructor(value: ArkBlendMode) {
    super(value);
  }
  static identity: Symbol = Symbol('advancedBlendMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAdvancedBlendMode(node);
    } else {
      getUINativeModule().common.setAdvancedBlendMode(node, this.value.blendMode, this.value.blendApplyType);
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

class ClipShapeModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('clipShape');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClipShape(node);
    } else {
      getUINativeModule().common.setClipShape(node, this.value);
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

class MaskShapeModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('maskShape');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMaskShape(node);
    } else {
      getUINativeModule().common.setMaskShape(node, this.value);
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

class UseEffectModifier extends ModifierWithKey<ArkUseEffect> {
  constructor(value: ArkUseEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('useEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetUseEffect(node);
    } else {
      getUINativeModule().common.setUseEffect(node, this.value.useEffect, this.value.effectType);
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

declare type ClickCallback = (event: ClickEvent) => void;
class OnClickModifier extends ModifierWithKey<ClickCallback> {
  constructor(value: ClickCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onClick');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnClick(node);
    } else {
      getUINativeModule().common.setOnClick(node, this.value);
    }
  }
}

declare type DragStartCallback = (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo;
class DragStartModifier extends ModifierWithKey<DragStartCallback> {
  constructor(value: DragStartCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragStart(node);
    } else {
      getUINativeModule().common.setOnDragStart(node, this.value);
    }
  }
}

declare type DragEnterCallback = (event?: DragEvent, extraParams?: string) => void;
class DragEnterModifier extends ModifierWithKey<DragEnterCallback> {
  constructor(value: DragEnterCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragEnter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragEnter(node);
    } else {
      getUINativeModule().common.setOnDragEnter(node, this.value);
    }
  }
}

class DragSpringLoadingModifier extends ModifierWithKey<ArkDragSpringLoading> {
  constructor(value: ArkDragSpringLoading) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragSpringLoading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragSpringLoading(node);
    } else {
      getUINativeModule().common.setOnDragSpringLoading(node, this.value.callback, this.value.configuration);
    }
  }

  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

declare type DragMoveCallback = (event?: DragEvent, extraParams?: string) => void;
class DragMoveModifier extends ModifierWithKey<DragMoveCallback> {
  constructor(value: DragMoveCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragMove');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragMove(node);
    } else {
      getUINativeModule().common.setOnDragMove(node, this.value);
    }
  }
}

declare type DragLeaveCallback = (event?: DragEvent, extraParams?: string) => void;
class DragLeaveModifier extends ModifierWithKey<DragLeaveCallback> {
  constructor(value: DragLeaveCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragLeave');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragLeave(node);
    } else {
      getUINativeModule().common.setOnDragLeave(node, this.value);
    }
  }
}

class DropModifier extends ModifierWithKey<ArkOnDrop> {
  constructor(value: ArkOnDrop) {
    super(value);
  }
  static identity: Symbol = Symbol('onDrop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDrop(node);
    } else {
      getUINativeModule().common.setOnDrop(node, this.value.event, this.value.disableDataPrefetch);
    }
  }
}

declare type DragEndCallback = (event?: DragEvent, extraParams?: string) => void;
class DragEndModifier extends ModifierWithKey<DragEndCallback> {
  constructor(value: DragEndCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDragEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDragEnd(node);
    } else {
      getUINativeModule().common.setOnDragEnd(node, this.value);
    }
  }
}

declare type TouchCallback = (event: TouchEvent) => void;
class OnTouchModifier extends ModifierWithKey<TouchCallback> {
  constructor(value: TouchCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onTouch');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnTouch(node);
    } else {
      getUINativeModule().common.setOnTouch(node, this.value);
    }
  }
}

declare type VoidCallback = () => void;
class OnAppearModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAppear');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnAppear(node);
    } else {
      getUINativeModule().common.setOnAppear(node, this.value);
    }
  }
}

class OnDisappearModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDisappear');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDisappear(node);
    } else {
      getUINativeModule().common.setOnDisappear(node, this.value);
    }
  }
}

class OnAttachModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAttach');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnAttach(node);
    } else {
      getUINativeModule().common.setOnAttach(node, this.value);
    }
  }
}

class OnDetachModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onDetach');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnDetach(node);
    } else {
      getUINativeModule().common.setOnDetach(node, this.value);
    }
  }
}

declare type KeyEventCallback = (event: KeyEvent) => void;
class OnKeyEventModifier extends ModifierWithKey<KeyEventCallback> {
  constructor(value: KeyEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onKeyEvent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnKeyEvent(node);
    } else {
      getUINativeModule().common.setOnKeyEvent(node, this.value);
    }
  }
}

class OnKeyPreImeModifier extends ModifierWithKey<Callback<KeyEvent, boolean>> {
  constructor(value: Callback<KeyEvent, boolean>) {
    super(value);
  }
  static identity: Symbol = Symbol('onKeyPreIme');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnKeyPreIme(node);
    } else {
      getUINativeModule().common.setOnKeyPreIme(node, this.value);
    }
  }
}

class OnKeyEventDispatchModifier extends ModifierWithKey<Callback<KeyEvent, boolean>> {
  private _onKeyEventDispatch: Callback<KeyEvent, boolean> = null;
  constructor(value: Callback<KeyEvent, boolean>) {
    super(value);
  }
  static identity: Symbol = Symbol('onKeyEventDispatch');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      this._onKeyEventDispatch = null;
      getUINativeModule().common.resetOnKeyEventDispatch(node);
    } else {
      this._onKeyEventDispatch = this.value;
      getUINativeModule().common.setOnKeyEventDispatch(node, this.value);
    }
  }
}

class OnFocusModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnFocus(node);
    } else {
      getUINativeModule().common.setOnFocus(node, this.value);
    }
  }
}

class OnBlurModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnBlur(node);
    } else {
      getUINativeModule().common.setOnBlur(node, this.value);
    }
  }
}

declare type HoverEventCallback = (isHover: boolean, event: HoverEvent) => void;
class OnHoverModifier extends ModifierWithKey<HoverEventCallback> {
  constructor(value: HoverEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onHover');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnHover(node);
    } else {
      getUINativeModule().common.setOnHover(node, this.value);
    }
  }
}

declare type HoverMoveEventCallback = (event: HoverEvent) => void;
class OnHoverMoveModifier extends ModifierWithKey<HoverMoveEventCallback> {
  constructor(value: HoverMoveEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onHoverMove');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnHoverMove(node);
    } else {
      getUINativeModule().common.setOnHoverMove(node, this.value);
    }
  }
}

declare type MouseEventCallback = (event: MouseEvent) => void;
class OnMouseModifier extends ModifierWithKey<MouseEventCallback> {
  constructor(value: MouseEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onMouse');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnMouse(node);
    } else {
      getUINativeModule().common.setOnMouse(node, this.value);
    }
  }
}

declare type AxisEventCallback = (event: AxisEvent) => void;
class OnAxisEventModifier extends ModifierWithKey<AxisEventCallback> {
  constructor(value: AxisEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAxisEvent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnAxisEvent(node);
    } else {
      getUINativeModule().common.setOnAxisEvent(node, this.value);
    }
  }
}

declare type SizeChangeEventCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
class OnSizeChangeModifier extends ModifierWithKey<SizeChangeEventCallback> {
  constructor(value: SizeChangeEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onSizeChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnSizeChange(node);
    } else {
      getUINativeModule().common.setOnSizeChange(node, this.value);
    }
  }
}

declare type AreaChangeEventCallback = (oldValue: Area, newValue: Area) => void;
class OnAreaChangeModifier extends ModifierWithKey<AreaChangeEventCallback> {
  constructor(value: AreaChangeEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAreaChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnAreaChange(node);
    } else {
      getUINativeModule().common.setOnAreaChange(node, this.value);
    }
  }
}

declare type GestureJudgeBeginCallback = (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult;
class OnGestureJudgeBeginModifier extends ModifierWithKey<GestureJudgeBeginCallback> {
  constructor(value: GestureJudgeBeginCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onGestureJudgeBegin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnGestureJudgeBegin(node);
    } else {
      getUINativeModule().common.setOnGestureJudgeBegin(node, this.value);
    }
  }
}

declare type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>,
  touchRecognizers?: Array<TouchRecognizer>) => GestureJudgeResult;
class OnGestureRecognizerJudgeBeginModifier extends ModifierWithKey<GestureRecognizerJudgeBeginCallback> {
  constructor(value: GestureRecognizerJudgeBeginCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onGestureRecognizerJudgeBegin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnGestureRecognizerJudgeBegin(node);
    } else {
      getUINativeModule().common.setOnGestureRecognizerJudgeBegin(node, this.value);
    }
  }
}

declare type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
class ShouldBuiltInRecognizerParallelWithModifier extends ModifierWithKey<ShouldBuiltInRecognizerParallelWithCallback> {
  constructor(value: ShouldBuiltInRecognizerParallelWithCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('shouldBuiltInRecognizerParallelWith');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetShouldBuiltInRecognizerParallelWith(node);
    } else {
      getUINativeModule().common.setShouldBuiltInRecognizerParallelWith(node, this.value);
    }
  }
}

declare type FocusAxisEventCallback = (event: FocusAxisEvent) => void;
class OnFocusAxisEventModifier extends ModifierWithKey<FocusAxisEventCallback> {
  constructor(value: FocusAxisEventCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onFocusAxisEvent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnKeyEvent(node);
    } else {
      getUINativeModule().common.setOnKeyEvent(node, this.value);
    }
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

class MotionBlurModifier extends ModifierWithKey<MotionBlurOptions> {
  constructor(value: MotionBlurOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('motionBlur');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMotionBlur(node);
    } else {
      getUINativeModule().common.setMotionBlur(node, this.value.radius, this.value.anchor.x, this.value.anchor.y);
    }
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
class OffsetModifier extends ModifierWithKey<Position | Edges | LocalizedEdges> {
  constructor(value: Position | Edges | LocalizedEdges) {
    super(value);
  }
  static identity: Symbol = Symbol('offset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOffset(node);
    } else {
      if (isUndefined(this.value)) {
        getUINativeModule().common.resetOffset(node);
      } else if (('x' in this.value) || ('y' in this.value)) {
        getUINativeModule().common.setOffset(node, false, this.value.x, this.value.y);
      } else if (('top' in this.value) || ('bottom' in this.value) || ('left' in this.value) || ('start' in this.value) || ('right' in this.value) || ('end' in this.value)) {
        if (('start' in this.value)) {
          this.value.left = this.value.start;
        }
        if (('end' in this.value)) {
          this.value.right = this.value.end;
        }
        getUINativeModule().common.setOffset(node, true, this.value.top, this.value.left, this.value.bottom, this.value.right);
      } else {
        getUINativeModule().common.resetOffset(node);
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

class MarkAnchorModifier extends ModifierWithKey<Position | LocalizedPosition> {
  constructor(value: Position | LocalizedPosition) {
    super(value);
  }
  static identity: Symbol = Symbol('markAnchor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetMarkAnchor(node);
    } else {
      if (this.value === void 0) {
        getUINativeModule().common.resetMarkAnchor(node);
      } else {
        if ('start' in this.value) {
          this.value.x = this.value.start;
        }
        if ('top' in this.value) {
          this.value.y = this.value.top;
        }
      }
      getUINativeModule().common.setMarkAnchor(node, this.value.x, this.value.y);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y) ||
      !isBaseOrResourceEqual(this.stageValue.start, this.value.start) ||
      !isBaseOrResourceEqual(this.stageValue.top, this.value.top);
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
    getUINativeModule().common.setFocusable(node, this.value);
  }
}

class TabStopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('tabStop');
  applyPeer(node: KNode, reset: boolean): void {
    getUINativeModule().common.setTabStop(node, this.value);
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

class SafeAreaPaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('safeAreaPadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetSafeAreaPadding(node);
    } else {
      getUINativeModule().common.setSafeAreaPadding(node, this.value.top,
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

class IgnoreLayoutSafeAreaCommonModifier extends ModifierWithKey<ArkSafeAreaExpandOpts | undefined> {
  constructor(value: ArkSafeAreaExpandOpts | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('ignoreLayoutSafeAreaCommon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetIgnoreLayoutSafeArea(node);
    } else {
      getUINativeModule().common.setIgnoreLayoutSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
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

class AccessibilityRoleModifier extends ModifierWithKey<AccessibilityRoleType> {
  constructor(value: AccessibilityRoleType) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityRole');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityRoleType(node);
    } else {
      getUINativeModule().common.setAccessibilityRoleType(node, this.value);
    }
  }
}

class AccessibilityFocusCallbackModifier extends ModifierWithKey<AccessibilityFocusCallback> {
  constructor(value: AccessibilityFocusCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAccessibilityFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityFocusCallback(node);
    } else {
      getUINativeModule().common.setAccessibilityFocusCallback(node, this.value);
    }
  }
}

class AccessibilityActionInterceptCallbackModifier extends ModifierWithKey<AccessibilityActionInterceptCallback> {
  constructor(value: AccessibilityActionInterceptCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAccessibilityActionIntercept');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnAccessibilityActionIntercept(node);
    } else {
      getUINativeModule().common.setOnAccessibilityActionIntercept(node, this.value);
    }
  }
}

class AccessibilityHoverTransparentModifier extends ModifierWithKey<AccessibilityTransparentCallback> {
  constructor(value: AccessibilityTransparentCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onAccessibilityHoverTransparent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityHoverTransparent(node);
    } else {
      getUINativeModule().common.setAccessibilityHoverTransparent(node, this.value);
    }
  }
}

class AccessibilityTextHintModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityTextHint');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityTextHint(node);
    } else {
      getUINativeModule().common.setAccessibilityTextHint(node, this.value);
    }
  }
}

class AccessibilityCheckedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityChecked');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityChecked(node);
    } else {
      getUINativeModule().common.setAccessibilityChecked(node, this.value);
    }
  }
}

class AccessibilitySelectedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilitySelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilitySelected(node);
    } else {
      getUINativeModule().common.setAccessibilitySelected(node, this.value);
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

class ForegroundEffectModifier extends ModifierWithKey<ForegroundEffectOptions> {
  constructor(value: ForegroundEffectOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('foregroundEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetForegroundEffect(node);
    } else {
      getUINativeModule().common.setForegroundEffect(node, this.value.radius);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.radius === this.stageValue.radius);
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
        this.value.brightness, this.value.color, this.value.adaptiveColor, this.value.blurOptions?.grayscale,
        this.value.policy, this.value.inactiveColor, this.value.type);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.radius === this.stageValue.radius && this.value.saturation === this.stageValue.saturation &&
      this.value.brightness === this.stageValue.brightness &&
      isBaseOrResourceEqual(this.stageValue.color, this.value.color) &&
      this.value.adaptiveColor === this.stageValue.adaptiveColor &&
      this.value.policy === this.stageValue.policy &&
      this.value.inactiveColor === this.stageValue.inactiveColor &&
      this.value.type === this.stageValue.type &&
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

class BackgroundBrightnessInternalModifier extends ModifierWithKey<BrightnessOptions> {
  constructor(params: BrightnessOptions) {
    super(params);
  }
  static identity: Symbol = Symbol('backgroundBrightnessInternal');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundBrightnessInternal(node);
    } else {
      getUINativeModule().common.setBackgroundBrightnessInternal(node, this.value.rate, this.value.lightUpDegree, this.value.cubicCoeff,
        this.value.quadCoeff, this.value.saturation, this.value.posRGB, this.value.negRGB, this.value.fraction);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.rate === this.stageValue.rate && this.value.lightUpDegree === this.stageValue.lightUpDegree
      && this.value.cubicCoeff === this.stageValue.cubicCoeff && this.value.quadCoeff === this.stageValue.quadCoeff
      && this.value.saturation === this.stageValue.saturation && this.value.posRGB === this.stageValue.posRGB
      && this.value.negRGB === this.stageValue.negRGB && this.value.fraction === this.stageValue.fraction);
  }
}

class ForegroundBrightnessModifier extends ModifierWithKey<BrightnessOptions> {
  constructor(params: BrightnessOptions) {
    super(params);
  }
  static identity: Symbol = Symbol('foregroundBrightness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetForegroundBrightness(node);
    } else {
      getUINativeModule().common.setForegroundBrightness(node, this.value.rate, this.value.lightUpDegree, this.value.cubicCoeff,
        this.value.quadCoeff, this.value.saturation, this.value.posRGB, this.value.negRGB, this.value.fraction);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.rate === this.stageValue.rate && this.value.lightUpDegree === this.stageValue.lightUpDegree
      && this.value.cubicCoeff === this.stageValue.cubicCoeff && this.value.quadCoeff === this.stageValue.quadCoeff
      && this.value.saturation === this.stageValue.saturation && this.value.posRGB === this.stageValue.posRGB
      && this.value.negRGB === this.stageValue.negRGB && this.value.fraction === this.stageValue.fraction);
  }
}

class DragPreviewOptionsModifier extends ModifierWithKey<ArkDragPreviewOptions> {
  constructor(value: ArkDragPreviewOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('dragPreviewOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDragPreviewOptions(node);
    } else {
      getUINativeModule().common.setDragPreviewOptions(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
  }
}

class DragPreviewModifier extends ModifierWithKey<ArkDragPreview> {
  constructor(value: ArkDragPreview) {
    super(value);
  }
  static identity: Symbol = Symbol('dragPreview');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetDragPreview(node);
    } else {
      getUINativeModule().common.setDragPreview(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !this.value.isEqual(this.stageValue);
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

class BindTipsModifier extends ModifierWithKey<ArkBindTipsOptions> {
  constructor(value: ArkBindTipsOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('bindTips');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBindTips(node);
    } else {
      if (this.value.message === undefined) {
        return;
      }
      getUINativeModule().common.setBindTips(
        node,
        this.value.message,
        this.value.options?.appearingTime,
        this.value.options?.disappearingTime,
        this.value.options?.appearingTimeWithContinuousOperation,
        this.value.options?.disappearingTimeWithContinuousOperation,
        this.value.options?.enableArrow,
        this.value.options?.arrowPointPosition,
        this.value.options?.arrowWidth,
        this.value.options?.arrowHeight,
        this.value.options?.showAtAnchor
      );
    }
  }
  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue.message, this.value.message) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.appearingTime,
        this.value.options.appearingTime
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.disappearingTime,
        this.value.options.disappearingTime
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.appearingTimeWithContinuousOperation,
        this.value.options.appearingTimeWithContinuousOperation
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.disappearingTimeWithContinuousOperation,
        this.value.options.disappearingTimeWithContinuousOperation
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.enableArrow,
        this.value.options.enableArrow
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.arrowPointPosition,
        this.value.options.arrowPointPosition
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.arrowWidth,
        this.value.options.arrowWidth
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.arrowHeight,
        this.value.options.arrowHeight
      ) ||
      !isBaseOrResourceEqual(
        this.stageValue.options.showAtAnchor,
        this.value.options.showAtAnchor
      )
    );
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

class AccessibilityNextFocusIdModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityNextFocusId');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityNextFocusId(node);
    } else {
      getUINativeModule().common.setAccessibilityNextFocusId(node, this.value);
    }
  }
}

class AccessibilityDefaultFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityDefaultFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityDefaultFocus(node);
    } else {
      getUINativeModule().common.setAccessibilityDefaultFocus(node, this.value);
    }
  }
}

class AccessibilityUseSamePageModifier extends ModifierWithKey<AccessibilitySamePageMode> {
  constructor(value: AccessibilitySamePageMode) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityUseSamePage');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityUseSamePage(node);
    } else {
      getUINativeModule().common.setAccessibilityUseSamePage(node, this.value);
    }
  }
}

class AccessibilityScrollTriggerableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityScrollTriggerable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityScrollTriggerable(node);
    } else {
      getUINativeModule().common.setAccessibilityScrollTriggerable(node, this.value);
    }
  }
}

class AccessibilityFocusDrawLevelModifier extends ModifierWithKey<FocusDrawLevel> {
  constructor(value: FocusDrawLevel) {
    super(value);
  }
  static identity: Symbol = Symbol('accessibilityFocusDrawLevel');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetAccessibilityFocusDrawLevel(node);
    } else {
      getUINativeModule().common.setAccessibilityFocusDrawLevel(node, this.value);
    }
  }
}

class HoverEffectModifier extends ModifierWithKey<HoverEffect> {
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

class CustomPropertyModifier extends ModifierWithKey<ArkCustomProperty> {
  constructor(value: ArkCustomProperty) {
    super(value);
  }
  static identity: Symbol = Symbol('customProperty');
  applyPeer(node: KNode, reset: boolean): void {
    const nodeId = getUINativeModule().frameNode.getIdByNodePtr(node);
    if (reset) {
      __removeCustomProperty__(nodeId, this.value.key);
    } else {
      __setValidCustomProperty__(nodeId, this.value.key, this.value.value);
    }
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

class SystemBarEffectModifier extends ModifierWithKey<null> {
  constructor(value: null) {
    super(value);
  }
  static identity: Symbol = Symbol('systemBarEffect');
  applyPeer(node: KNode, reset: boolean): void {
    getUINativeModule().common.setSystemBarEffect(node, true);
  }
}
class PixelRoundModifier extends ModifierWithKey<PixelRoundPolicy> {
  constructor(value: PixelRoundPolicy) {
    super(value);
  }
  static identity: Symbol = Symbol('pixelRound');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPixelRound(node);
    } else {
      let start: PixelRoundCalcPolicy;
      let top: PixelRoundCalcPolicy;
      let end: PixelRoundCalcPolicy;
      let bottom: PixelRoundCalcPolicy;
      if (isObject(this.value)) {
        start = (this.value as PixelRoundCalcPolicy)?.start;
        top = (this.value as PixelRoundCalcPolicy)?.top;
        end = (this.value as PixelRoundCalcPolicy)?.end;
        bottom = (this.value as PixelRoundCalcPolicy)?.bottom;
      }
      getUINativeModule().common.setPixelRound(node, start, top, end, bottom);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.stageValue.start === this.value.start &&
      this.stageValue.end === this.value.end &&
      this.stageValue.top === this.value.top &&
      this.stageValue.bottom === this.value.bottom);
  }
}

class FocusScopeIdModifier extends ModifierWithKey<ArkFocusScopeId> {
  constructor(value: ArkFocusScopeId) {
    super(value);
  }
  static identity: Symbol = Symbol('focusScopeId');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFocusScopeId(node);
    } else {
      getUINativeModule().common.setFocusScopeId(node, this.value.id, this.value.isGroup, this.value.arrowStepOut);
    }
  }
}

class FocusScopePriorityModifier extends ModifierWithKey<ArkFocusScopePriority> {
  constructor(value: ArkFocusScopePriority) {
    super(value);
  }
  static identity: Symbol = Symbol('focusScopePriority');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFocusScopePriority(node);
    } else {
      getUINativeModule().common.setFocusScopePriority(node, this.value.scopeId, this.value.priority);
    }
  }
}

class FocusBoxModifier extends ModifierWithKey<FocusBoxStyle> {
  constructor(value: FocusBoxStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('focusBox');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFocusBox(node);
    } else {
      getUINativeModule().common.setFocusBox(node, this.value?.margin,
        this.value?.strokeWidth, this.value?.strokeColor);
    }
  }
}

class ParticleEmitterModifier extends ModifierWithKey<object> {
  constructor(value) {
    super(value);
  }
  
  static identity: Symbol = Symbol('emitter');

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().particle.resetEmitter(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkEmitterPropertyOptions = new ArkEmitterPropertyOptions();
        let data = this.value[i];
        arkEmitterPropertyOptions.index = 0;
        if (data.index > 0) {
          arkEmitterPropertyOptions.index = data.index;
        }

        if (isNumber(data.emitRate)) {
          arkEmitterPropertyOptions.isSetEmitRate = 1;
          if (data.emitRate >= 0) {
            arkEmitterPropertyOptions.emitRate = data.emitRate;
          } else {
            arkEmitterPropertyOptions.emitRate = 5;
          }
        }

        if (isObject(data.position)) {
          if (isNumber(data.position.x) && isNumber(data.position.y)) {
            arkEmitterPropertyOptions.isSetPosition = 1;
            arkEmitterPropertyOptions.positionX = data.position.x;
            arkEmitterPropertyOptions.positionY = data.position.y;
          }
        }

        if (isObject(data.size)) {
          if (data.size.width > 0 && data.size.height > 0) {
            arkEmitterPropertyOptions.isSetSize = 1;
            arkEmitterPropertyOptions.sizeWidth = data.size.width;
            arkEmitterPropertyOptions.sizeHeight = data.size.height;
          }
        }

        if (isObject(data.annulusRegion)) {
          arkEmitterPropertyOptions.isSetAnnulusRegion = 1;
          if (isObject(data.annulusRegion.center) &&
            isObject(data.annulusRegion.center.x) && isObject(data.annulusRegion.center.y)) {
            arkEmitterPropertyOptions.isSetCenter = 1;
            arkEmitterPropertyOptions.centerXValue = data.annulusRegion.center.x.value;
            arkEmitterPropertyOptions.centerXUnit = data.annulusRegion.center.x.unit;
            arkEmitterPropertyOptions.centerYValue = data.annulusRegion.center.y.value;
            arkEmitterPropertyOptions.centerYUnit = data.annulusRegion.center.y.unit;
          }
          if (isObject(data.annulusRegion.innerRadius)) {
            arkEmitterPropertyOptions.isSetInnerRadius = 1;
            arkEmitterPropertyOptions.innerRadiusValue = data.annulusRegion.innerRadius.value;
            arkEmitterPropertyOptions.innerRadiusUnit = data.annulusRegion.innerRadius.unit;
          }
          if (isObject(data.annulusRegion.outerRadius)) {
            arkEmitterPropertyOptions.isSetOuterRadius = 1;
            arkEmitterPropertyOptions.outerRadiusValue = data.annulusRegion.outerRadius.value;
            arkEmitterPropertyOptions.outerRadiusUnit = data.annulusRegion.outerRadius.unit;
          }
          if (isNumber(data.annulusRegion.startAngle)) {
            arkEmitterPropertyOptions.isSetStartAngle = 1;
            arkEmitterPropertyOptions.startAngle = data.annulusRegion.startAngle;
          }
          if (isNumber(data.annulusRegion.endAngle)) {
            arkEmitterPropertyOptions.isSetEndAngle = 1;
            arkEmitterPropertyOptions.endAngle = data.annulusRegion.endAngle;
          }
        }
        dataArray.push(arkEmitterPropertyOptions);
      }
      getUINativeModule().particle.setEmitter(node, dataArray);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class NextFocusModifier extends ModifierWithKey<FocusMovement> {
  constructor(value: FocusMovement) {
    super(value);
  }
  static identity: Symbol = Symbol('nextFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetNextFocus(node);
    } else {
      getUINativeModule().common.setNextFocus(node, this.value.forward, this.value.backward,
        this.value.up, this.value.down, this.value.left, this.value.right);
    }
  }
}

class VisualEffectModifier extends ModifierWithKey<VisualEffect> {
  constructor(value: VisualEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('visualEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetVisualEffect(node);
    } else {
      getUINativeModule().common.setVisualEffect(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value === this.stageValue);
  }
}

class BackgroundFilterModifier extends ModifierWithKey<Filter> {
  constructor(value: Filter) {
    super(value);
  }
  static identity: Symbol = Symbol('backgroundFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetBackgroundFilter(node);
    } else {
      getUINativeModule().common.setBackgroundFilter(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value === this.stageValue);
  }
}

class ForegroundFilterModifier extends ModifierWithKey<Filter> {
  constructor(value: Filter) {
    super(value);
  }
  static identity: Symbol = Symbol('foregroundFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetForegroundFilter(node);
    } else {
      getUINativeModule().common.setForegroundFilter(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value === this.stageValue);
  }
}

class CompositingFilterModifier extends ModifierWithKey<Filter> {
  constructor(value: Filter) {
    super(value);
  }
  static identity: Symbol = Symbol('compositingFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetCompositingFilter(node);
    } else {
      getUINativeModule().common.setCompositingFilter(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.value === this.stageValue);
  }
}

class FreezeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('freeze');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetFreeze(node);
    } else {
      getUINativeModule().common.setFreeze(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

declare type PreDragCallback = (preDragStatus?: PreDragStatus) => void;
class PreDragModifier extends ModifierWithKey<PreDragCallback> {
  constructor(value: PreDragCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onPreDrag');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnPreDrag(node);
    } else {
      getUINativeModule().common.setOnPreDrag(node, this.value);
    }
  }
}

class OnVisibleAreaChangeModifier extends ModifierWithKey<ArkOnVisibleAreaChange> {
  constructor(value: ArkOnVisibleAreaChange) {
      super(value);
  }
  static identity: Symbol = Symbol('onVisibleAreaChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnVisibleAreaChange(node);
    } else {
      getUINativeModule().common.setOnVisibleAreaChange(node, this.value.ratios, this.value.event);
    }
  }
}

declare type TouchInterceptCallback = Callback<TouchEvent, HitTestMode>;
class OnTouchInterceptModifier extends ModifierWithKey<TouchInterceptCallback> {
  constructor(value: TouchInterceptCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onTouchIntercept');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetOnTouchIntercept(node);
    } else {
      getUINativeModule().common.setOnTouchIntercept(node, this.value);
    }
  }
}

declare type ChildTouchTestCallback = (value: Array<TouchTestInfo>) => TouchResult;
class OnChildTouchTestModifier extends ModifierWithKey<ChildTouchTestCallback> {
  constructor(value: ChildTouchTestCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onChildTouchTest');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
        getUINativeModule().common.resetOnChildTouchTest(node);
      } else {
        getUINativeModule().common.setOnChildTouchTest(node, this.value);
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
function parseWithDefaultNumber(val, defaultValue) {
  if (isNumber(val)) {
    return val;
  }
  else { return defaultValue; }
}

function modifierWithKey<T extends number | string | boolean | object, M extends ModifierWithKey<T>>(
  modifiers: Map<Symbol, AttributeModifierWithKey>,
  identity: Symbol,
  modifierClass: new (value: T) => M,
  value: T
) {
  if (typeof (modifiers as ObservedMap).isFrameNode === 'function' && (modifiers as ObservedMap).isFrameNode()) {
    if (!(modifierClass as any).instance) {
      (modifierClass as any).instance = new modifierClass(value);
    } else {
      (modifierClass as any).instance.stageValue = value;
    }
    modifiers.set(identity, (modifierClass as any).instance);
    return;
  }
  const item = modifiers.get(identity);
  if (item) {
    item.stageValue = value;
    modifiers.set(identity, item);
  } else {
    modifiers.set(identity, new modifierClass(value));
  }
}

declare class __JSScopeUtil__ {
  static syncInstanceId(instanceId: number): void;
  static restoreInstanceId(): void;
}

class ArkComponent implements CommonMethod<CommonAttribute> {
  _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
  _changed: boolean;
  nativePtr: KNode;
  _weakPtr: JsPointerClass;
  _classType: ModifierType | undefined;
  _nativePtrChanged: boolean;
  _gestureEvent: UIGestureEvent;
  _instanceId: number;
  _needDiff: boolean;
  private _onVisibleAreaChange: ArkOnVisibleAreaChange = null;
  private _onPreDragEvent: PreDragCallback = null;
  private _onTouchInterceptEvent: TouchInterceptCallback = null;
  private _onChildTouchTestEvent: ChildTouchTestCallback = null;
  private _clickEvent: ClickCallback = null;
  private _touchEvent: TouchCallback = null;
  private _onAppearEvent: VoidCallback = null;
  private _onDisappearEvent: VoidCallback = null;
  private _onAttach: VoidCallback = null;
  private _onDetach: VoidCallback = null;
  private _onKeyEvent: KeyEventCallback = null;
  private _onKeyPreIme: Callback<KeyEvent, boolean> = null;
  private _onKeyEventDispatch: Callback<KeyEvent, boolean> = null;
  private _onFocus: VoidCallback = null;
  private _onBlur: VoidCallback = null;
  private _onHover: HoverEventCallback = null;
  private _onHoverMove: HoverMoveEventCallback = null;
  private _onMouse: MouseEventCallback = null;
  private _onAxis: AxisEventCallback = null;
  private _onSizeChange: SizeChangeEventCallback = null;
  private _onAreaChange: AreaChangeEventCallback = null;
  private _onGestureJudgeBegin: GestureJudgeBeginCallback = null;
  private _onGestureRecognizerJudgeBegin: GestureRecognizerJudgeBeginCallback = null;
  private _shouldBuiltInRecognizerParallelWith: ShouldBuiltInRecognizerParallelWithCallback = null;
  private _onFocusAxisEvent: FocusAxisEventCallback = null;

  constructor(nativePtr: KNode, classType?: ModifierType) {
    this.nativePtr = nativePtr;
    this._changed = false;
    this._classType = classType;
    this._needDiff = true;
    if (classType === ModifierType.FRAME_NODE) {
      this._instanceId = -1;
      this._modifiersWithKeys = new ObservedMap();
      (this._modifiersWithKeys as ObservedMap).setOnChange((key, value) => {
        if (this.nativePtr === undefined) {
          return;
        }
        if (this._instanceId !== -1) {
          __JSScopeUtil__.syncInstanceId(this._instanceId);
        }
        value.applyStageImmediately(this.nativePtr, this);
        getUINativeModule().frameNode.propertyUpdate(this.nativePtr);
        if (this._instanceId !== -1) {
          __JSScopeUtil__.restoreInstanceId();
        }
      });
      (this._modifiersWithKeys as ObservedMap).setFrameNode(true);
    } else if (classType === ModifierType.EXPOSE_MODIFIER || classType === ModifierType.STATE) {
      this._modifiersWithKeys = new ObservedMap();
      this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(nativePtr);
    } else {
      this._modifiersWithKeys = new Map();
      this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(nativePtr);
    }
    this._nativePtrChanged = false;
  }

  setNodePtr(nodePtr: KNode) {
    if (nodePtr === this.nativePtr) {
      return;
    }
    this.nativePtr = nodePtr;
    this._weakPtr = (nodePtr !== undefined && nodePtr !== null) ? getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr) : undefined;
  }

  setInstanceId(instanceId: number): void {
    this._instanceId = instanceId;
  }

  getOrCreateGestureEvent() {
    if (this._gestureEvent === null || this._gestureEvent === undefined) {
      this._gestureEvent = new UIGestureEvent();
      this._gestureEvent.setNodePtr(this.nativePtr);
      this._gestureEvent.setWeakNodePtr(this._weakPtr);
      if (!this._weakPtr?.invalid()) {
        this._gestureEvent.registerFrameNodeDeletedCallback(this.nativePtr);
      }
    }
    return this._gestureEvent;
  }

  cleanStageValue(): void {
    if (!this._modifiersWithKeys) {
      return;
    }
    this._modifiersWithKeys.forEach((value, key) => {
        value.stageValue = undefined;
    });
  }

  applyStateUpdatePtr(instance: ArkComponent): void {
    if (this.nativePtr !== instance.nativePtr) {
      this.nativePtr = instance.nativePtr;
      this._nativePtrChanged = true;
      if (instance._weakPtr) {
        this._weakPtr = instance._weakPtr;
      } else {
        this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(this.nativePtr);
      }
    }
  }

  applyModifierPatch(): void {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr, this)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    this._onGestureJudgeBegin = callback;
    modifierWithKey(this._modifiersWithKeys, OnGestureJudgeBeginModifier.identity, OnGestureJudgeBeginModifier, callback);
    return this;
  }
  onGestureRecognizerJudgeBegin(callback: (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>,
    touchRecognizers?: Array<TouchRecognizer>) => GestureJudgeResult): this {
    this._onGestureRecognizerJudgeBegin = callback;
    modifierWithKey(this._modifiersWithKeys, OnGestureRecognizerJudgeBeginModifier.identity, OnGestureRecognizerJudgeBeginModifier, callback);
    return this;
  }
  shouldBuiltInRecognizerParallelWith(callback: (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer): this {
    this._shouldBuiltInRecognizerParallelWith = callback;
    modifierWithKey(this._modifiersWithKeys, ShouldBuiltInRecognizerParallelWithModifier.identity, ShouldBuiltInRecognizerParallelWithModifier, callback);
    return this;
  }
  onSizeChange(callback: (oldValue: SizeOptions, newValue: SizeOptions) => void): this {
    this._onSizeChange = callback;
    modifierWithKey(this._modifiersWithKeys, OnSizeChangeModifier.identity, OnSizeChangeModifier, callback);
    return this;
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
          safeAreaType += param.toString();
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
          safeAreaEdge += param.toString();
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

  backgroundBrightnessInternal(params: BrightnessOptions): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundBrightnessInternalModifier.identity,
      BackgroundBrightnessInternalModifier, params);
    return this;
  }

  foregroundBrightness(params: BrightnessOptions): this {
    modifierWithKey(this._modifiersWithKeys, ForegroundBrightnessModifier.identity,
      ForegroundBrightnessModifier, params);
    return this;
  }

  dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, DragPreviewOptionsModifier.identity,
        DragPreviewOptionsModifier, undefined);
      return this;
    }
    let arkDragPreviewOptions = new ArkDragPreviewOptions();
    if (typeof value === 'object') {
      arkDragPreviewOptions.mode = value.mode;
      arkDragPreviewOptions.numberBadge = value.numberBadge;
      arkDragPreviewOptions.sizeChangeEffect = value.sizeChangeEffect;
    }
    if (typeof options === 'object') {
      arkDragPreviewOptions.isMultiSelectionEnabled = options.isMultiSelectionEnabled;
      arkDragPreviewOptions.defaultAnimationBeforeLifting = options.defaultAnimationBeforeLifting;
      arkDragPreviewOptions.enableEdgeAutoScroll = options.enableEdgeAutoScroll;
      arkDragPreviewOptions.enableHapticFeedback = options.enableHapticFeedback;
      arkDragPreviewOptions.isLiftingDisabled = options.isLiftingDisabled;
    }
    modifierWithKey(this._modifiersWithKeys, DragPreviewOptionsModifier.identity,
      DragPreviewOptionsModifier, arkDragPreviewOptions);
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

  padding(value: Padding | Length | LocalizedPadding): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, undefined);
    }
    return this;
  }

  safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isObject(value) && (Object.keys(value).indexOf('value') >= 0)) {
        arkValue.top = <LengthMetrics>value;
        arkValue.right = <LengthMetrics>value;
        arkValue.bottom = <LengthMetrics>value;
        arkValue.left = <LengthMetrics>value;
      } else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, SafeAreaPaddingModifier.identity, SafeAreaPaddingModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, SafeAreaPaddingModifier.identity, SafeAreaPaddingModifier, undefined);
    }
    return this;
  }

  ignoreLayoutSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length >= 0) {
      let safeAreaType: string | number = '';
      for (let param of types) {
        if (!isNumber(param) || param > LAYOUT_SAFE_AREA_TYPE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
          safeAreaType += param.toString();
        } else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length >= 0) {
      let safeAreaEdge: string | number = '';
      for (let param of edges) {
        if (!isNumber(param) || param > LAYOUT_SAFE_AREA_EDGE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
          safeAreaEdge += param.toString();
        } else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaCommonModifier.identity, IgnoreLayoutSafeAreaCommonModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaCommonModifier.identity, IgnoreLayoutSafeAreaCommonModifier, opts);
    }
    return this;
  }

  margin(value: Margin | Length | LocalizedMargin): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
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

  backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat | BackgroundImageOptions): this {
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

  backgroundImageResizable(value: ResizableOptions): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundImageResizableModifier.identity, BackgroundImageResizableModifier, value);
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
      arkBackgroundBlurStyle.blurOptions = options.blurOptions;
      arkBackgroundBlurStyle.policy = options.policy;
      arkBackgroundBlurStyle.inactiveColor = options.inactiveColor;
      arkBackgroundBlurStyle.type = options.type;
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
      arkForegroundBlurStyle.blurOptions = options.blurOptions;
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
        if ((Object.keys(value.width).indexOf('start') >= 0) ||
        (Object.keys(value.width).indexOf('end') >= 0)) {
          arkBorder.arkWidth.start = (value.width as LocalizedEdgeWidths).start;
          arkBorder.arkWidth.end = (value.width as LocalizedEdgeWidths).end;
          arkBorder.arkWidth.top = (value.width as LocalizedEdgeWidths).top;
          arkBorder.arkWidth.bottom = (value.width as LocalizedEdgeWidths).bottom;
        } else {
          arkBorder.arkWidth.left = (value.width as EdgeWidths).left;
          arkBorder.arkWidth.right = (value.width as EdgeWidths).right;
          arkBorder.arkWidth.top = (value.width as EdgeWidths).top;
          arkBorder.arkWidth.bottom = (value.width as EdgeWidths).bottom;
        }
    }
  }
    if (!isUndefined(value?.color) && value?.color !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        arkBorder.arkColor.leftColor = value.color;
        arkBorder.arkColor.rightColor = value.color;
        arkBorder.arkColor.topColor = value.color;
        arkBorder.arkColor.bottomColor = value.color;
      } else {
        if ((Object.keys(value.color).indexOf('start') >= 0) ||
          (Object.keys(value.color).indexOf('end') >= 0)) {
            arkBorder.arkColor.startColor = (value.color as LocalizedEdgeColors).start;
            arkBorder.arkColor.endColor = (value.color as LocalizedEdgeColors).end;
            arkBorder.arkColor.topColor = (value.color as LocalizedEdgeColors).top;
            arkBorder.arkColor.bottomColor = (value.color as LocalizedEdgeColors).bottom;
          } else {
            arkBorder.arkColor.leftColor = (value.color as EdgeColors).left;
            arkBorder.arkColor.rightColor = (value.color as EdgeColors).right;
            arkBorder.arkColor.topColor = (value.color as EdgeColors).top;
            arkBorder.arkColor.bottomColor = (value.color as EdgeColors).bottom;
          }
      }
    }
    if (!isUndefined(value?.radius) && value?.radius !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        arkBorder.arkRadius.topLeft = value.radius;
        arkBorder.arkRadius.topRight = value.radius;
        arkBorder.arkRadius.bottomLeft = value.radius;
        arkBorder.arkRadius.bottomRight = value.radius;
      } else {
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          arkBorder.arkRadius.topStart = (value.radius as LocalizedBorderRadius)?.topStart;
          arkBorder.arkRadius.topEnd = (value.radius as LocalizedBorderRadius)?.topEnd;
          arkBorder.arkRadius.bottomStart = (value.radius as LocalizedBorderRadius)?.bottomStart;
          arkBorder.arkRadius.bottomEnd = (value.radius as LocalizedBorderRadius)?.bottomEnd;
        } else {
          arkBorder.arkRadius.topLeft = (value.radius as BorderRadiuses)?.topLeft;
          arkBorder.arkRadius.topRight = (value.radius as BorderRadiuses)?.topRight;
          arkBorder.arkRadius.bottomLeft = (value.radius as BorderRadiuses)?.bottomLeft;
          arkBorder.arkRadius.bottomRight = (value.radius as BorderRadiuses)?.bottomRight;
        }
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
    if (!isUndefined(value?.dashGap) && value?.dashGap !== null) {
      if (isNumber(value.dashGap) || isString(value.dashGap) || isResource(value.dashGap) || isObject(value.dashGap) && isNumber(value.dashGap.value)) {
        arkBorder.arkDashGap.left = value.dashGap;
        arkBorder.arkDashGap.right = value.dashGap;
        arkBorder.arkDashGap.top = value.dashGap;
        arkBorder.arkDashGap.bottom = value.dashGap;
      } else {
        arkBorder.arkDashGap.left = (value.dashGap as EdgeWidths).left;
        arkBorder.arkDashGap.right = (value.dashGap as EdgeWidths).right;
        arkBorder.arkDashGap.top = (value.dashGap as EdgeWidths).top;
        arkBorder.arkDashGap.bottom = (value.dashGap as EdgeWidths).bottom;
        arkBorder.arkDashGap.start = (value.dashGap as LocalizedEdgeWidths).start;
        arkBorder.arkDashGap.end = (value.dashGap as LocalizedEdgeWidths).end;
      }
    }
    if (!isUndefined(value?.dashWidth) && value?.dashWidth !== null) {
      if (isNumber(value.dashWidth) || isString(value.dashWidth) || isResource(value.dashWidth) || isObject(value.dashWidth) && isNumber(value.dashWidth.value)) {
        arkBorder.arkDashWidth.left = value.dashWidth;
        arkBorder.arkDashWidth.right = value.dashWidth;
        arkBorder.arkDashWidth.top = value.dashWidth;
        arkBorder.arkDashWidth.bottom = value.dashWidth;
      } else {
        arkBorder.arkDashWidth.left = (value.dashWidth as EdgeWidths).left;
        arkBorder.arkDashWidth.right = (value.dashWidth as EdgeWidths).right;
        arkBorder.arkDashWidth.top = (value.dashWidth as EdgeWidths).top;
        arkBorder.arkDashWidth.bottom = (value.dashWidth as EdgeWidths).bottom;
        arkBorder.arkDashWidth.start = (value.dashWidth as EdgeWidths).start;
        arkBorder.arkDashWidth.end = (value.dashWidth as EdgeWidths).end;
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
    this._clickEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnClickModifier.identity, OnClickModifier, event);
    return this;
  }

  onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this {
    this._onHover = event;
    modifierWithKey(this._modifiersWithKeys, OnHoverModifier.identity, OnHoverModifier, event);
    return this;
  }

  onHoverMove(event: (event?: HoverMoveEvent) => void): this {
    this._onHoverMove = event;
    modifierWithKey(this._modifiersWithKeys, OnHoverMoveModifier.identity, OnHoverMoveModifier, event);
    return this;
  }

  hoverEffect(value: HoverEffect): this {
    modifierWithKey(this._modifiersWithKeys, HoverEffectModifier.identity, HoverEffectModifier, value);
    return this;
  }

  onMouse(event: (event?: MouseEvent) => void): this {
    this._onMouse = event;
    modifierWithKey(this._modifiersWithKeys, OnMouseModifier.identity, OnMouseModifier, event);
    return this;
  }

  onAxisEvent(event: (event?: AxisEvent) => void): this {
    this._onAxis = event;
    modifierWithKey(this._modifiersWithKeys, OnAxisEventModifier.identity, OnAxisEventModifier, event);
    return this;
  }
  
  onTouch(event: (event?: TouchEvent) => void): this {
    this._touchEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnTouchModifier.identity, OnTouchModifier, event);
    return this;
  }

  onKeyEvent(event: (event?: KeyEvent) => void): this {
    this._onKeyEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity, OnKeyEventModifier, event);
    return this;
  }

  onKeyPreIme(event: Callback<KeyEvent, boolean>): this {
    this._onKeyPreIme = event;
    modifierWithKey(this._modifiersWithKeys, OnKeyPreImeModifier.identity, OnKeyPreImeModifier, event);
    return this;
  }

  onKeyEventDispatch(event: Callback<KeyEvent, boolean>): this {
    this._onKeyEventDispatch = event;
    modifierWithKey(this._modifiersWithKeys, OnKeyEventDispatchModifier.identity, OnKeyEventDispatchModifier, event);
    return this;
  }

  onFocusAxisEvent(event: (event?: FocusAxisEvent) => void): this {
    this._onFocusAxisEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnFocusAxisEventModifier.identity, OnFocusAxisEventModifier, event);
    return this;
  }

  focusable(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, undefined);
    }
    return this;
  }

  tabStop(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, TabStopModifier.identity, TabStopModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, TabStopModifier.identity, TabStopModifier, undefined);
    }
    return this;
  }

  onFocus(event: () => void): this {
    this._onFocus = event;
    modifierWithKey(this._modifiersWithKeys, OnFocusModifier.identity, OnFocusModifier, event);
    return this;
  }

  onBlur(event: () => void): this {
    this._onBlur = event;
    modifierWithKey(this._modifiersWithKeys, OnBlurModifier.identity, OnBlurModifier, event);
    return this;
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

  blur(value: number, options?: BlurOptions): this {
    let blur: ArkBlurOptions = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, blur);
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

  invert(value: number | InvertOptions): this {
    if (!isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, undefined);
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

  useEffect(value: boolean, type: EffectType = EffectType.DEFAULT): this {
    let useEffectObj = new ArkUseEffect();
    useEffectObj.useEffect = value;
    useEffectObj.effectType = type;
    modifierWithKey(this._modifiersWithKeys, UseEffectModifier.identity, UseEffectModifier, useEffectObj);
    return this;
  }

  backdropBlur(value: number, options?: BlurOptions): this {
    let blur: ArkBlurOptions = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, blur);
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
    this._onAppearEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnAppearModifier.identity, OnAppearModifier, event);
    return this;
  }

  onDisAppear(event: () => void): this {
    this._onDisappearEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnDisappearModifier.identity, OnDisappearModifier, event);
    return this;
  }

  onAttach(event: () => void): this {
    this._onAttach = event;
    modifierWithKey(this._modifiersWithKeys, OnAttachModifier.identity, OnAttachModifier, event);
    return this;
  }

  onDetach(event: () => void): this {
    this._onDetach = event;
    modifierWithKey(this._modifiersWithKeys, OnDetachModifier.identity, OnDetachModifier, event);
    return this;
  }
  onAreaChange(event: (oldValue: Area, newValue: Area) => void): this {
    this._onAreaChange = event;
    modifierWithKey(this._modifiersWithKeys, OnAreaChangeModifier.identity, OnAreaChangeModifier, event);
    return this;
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

  align(value: Alignment | LocalizedAlignment): this {
    if (!isNumber(value) && !isString(value)) {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, value);
    }
    return this;
  }

  layoutGravity(value:string): this {
    if (!isString(value)) {
      modifierWithKey(this._modifiersWithKeys, LayoutGravityModifier.identity, LayoutGravityModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, LayoutGravityModifier.identity, LayoutGravityModifier, value);
    }
    return this;
  }

  position(value: Position | Edges): this {
    if (isObject(value)) {
      modifierWithKey(this._modifiersWithKeys, PositionModifier.identity, PositionModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, PositionModifier.identity, PositionModifier, undefined);
    }
    return this;
  }

  markAnchor(value: Position): this {
    modifierWithKey(this._modifiersWithKeys, MarkAnchorModifier.identity, MarkAnchorModifier, value);
    return this;
  }

  offset(value: Position | Edges): this {
    if (isObject(value)) {
      modifierWithKey(this._modifiersWithKeys, OffsetModifier.identity, OffsetModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, OffsetModifier.identity, OffsetModifier, undefined);
    }
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
    modifierWithKey(this._modifiersWithKeys, DragStartModifier.identity, DragStartModifier, event);
    return this;
  }

  onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this {
    modifierWithKey(this._modifiersWithKeys, DragEnterModifier.identity, DragEnterModifier, event);
    return this;
  }

  onDragSpringLoading(callback: (context: ArkSpringLoadingContext) => void, configuration? DragSpringLoadingConfiguration): this {
    let arkDragSpringLoading = new ArkDragSpringLoading();
    if (typeof callback === 'function') {
      arkDragSpringLoading.callback = callback;
    }
    arkDragSpringLoading.configuration.stillTimeLimit = configuration?.stillTimeLimit;
    arkDragSpringLoading.configuration.updateInterval = configuration?.updateInterval;
    arkDragSpringLoading.configuration.updateNotifyCount = configuration?.updateNotifyCount;
    arkDragSpringLoading.configuration.updateToFinishInterval = configuration?.updateToFinishInterval;

    modifierWithKey(this._modifiersWithKeys, DragSpringLoadingModifier.identity, DragSpringLoadingModifier, arkDragSpringLoading);
    return this;
  }

  onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this {
    modifierWithKey(this._modifiersWithKeys, DragMoveModifier.identity, DragMoveModifier, event);
    return this;
  }

  onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this {
    modifierWithKey(this._modifiersWithKeys, DragLeaveModifier.identity, DragLeaveModifier, event);
    return this;
  }

  onDrop(event: (event?: DragEvent, extraParams?: string) => void, dropOptions: DropOptions): this {
    let arkOnDrop = new ArkOnDrop();
    if (typeof event === 'function') {
      arkOnDrop.event = event;
    }
    if (typeof dropOptions === 'object') {
      arkOnDrop.disableDataPrefetch = dropOptions.disableDataPrefetch;
    }
    modifierWithKey(this._modifiersWithKeys, DropModifier.identity, DropModifier, arkOnDrop);
    return this;
  }

  onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this {
    modifierWithKey(this._modifiersWithKeys, DragEndModifier.identity, DragEndModifier, event);
    return this;
  }

  onPreDrag(event: (preDragStatus: PreDragStatus) => void): this {
    this._onPreDragEvent = event;
    modifierWithKey(this._modifiersWithKeys, PreDragModifier.identity, PreDragModifier, event);
    return this;
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

  dragPreview(preview: CustomBuilder | DragItemInfo | string, config: PreviewConfiguration): this {
    let arkDragPreview = new ArkDragPreview();
    if (typeof config === 'object') {
      arkDragPreview.onlyForLifting = config.onlyForLifting;
    }
    if (typeof preview === 'string') {
      arkDragPreview.inspetorId = preview;
      modifierWithKey(this._modifiersWithKeys, DragPreviewModifier.identity, DragPreviewModifier, arkDragPreview);
    } else if (typeof preview === 'object') {
      arkDragPreview.pixelMap = preview.pixelMap;
      arkDragPreview.extraInfo = preview.extraInfo;
      if (preview.builder) {
        throw new Error('Builder is not supported.');
      }
      modifierWithKey(this._modifiersWithKeys, DragPreviewModifier.identity, DragPreviewModifier, arkDragPreview);
    } else if (typeof preview === 'function') {
      throw new Error('Method not implemented.');
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
    metricsColors?: Array<any>; 
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

  motionBlur(value: MotionBlurOptions): this {
    modifierWithKey(this._modifiersWithKeys, MotionBlurModifier.identity, MotionBlurModifier, value);
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

  chainMode(direction: Axis, style: ChainStyle): this {
    let arkChainMode = new ArkChainMode();
    arkChainMode.direction = direction;
    arkChainMode.style = style;
    modifierWithKey(this._modifiersWithKeys, ChainModeifier.identity, ChainModeifier, arkChainMode);
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

  geometryTransition(id: string, options?: GeometryTransitionOptions): this {
    let arkGeometryTransition = new ArkGeometryTransition();
    arkGeometryTransition.id = id;
    arkGeometryTransition.options = options;
    modifierWithKey(this._modifiersWithKeys, GeometryTransitionModifier.identity, GeometryTransitionModifier, arkGeometryTransition);
    return this;
  }

  bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
    throw new Error('Method not implemented.');
  }

  bindTips(message: TipsMessageType, options?: TipsOptions): this {
    let arkBindTipsOptions = new ArkBindTipsOptions();
    arkBindTipsOptions.message = message;
    arkBindTipsOptions.options = options;
    modifierWithKey(this._modifiersWithKeys, BindTipsModifier.identity, BindTipsModifier, arkBindTipsOptions);
    return this;
  }

  bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
    let arkBindMenu = new ArkBindMenu();
    arkBindMenu.content = content;
    arkBindMenu.options = options;
    modifierWithKey(this._modifiersWithKeys, BindMenuModifier.identity, BindMenuModifier, arkBindMenu);
    return this;
  }

  searchAutoCapitalization(autoCapitalizationMode: AutoCapitalizationMode): this {
    let ArkSearchAutoCapitalization = new ArkSearchAutoCapitalization();
    ArkSearchAutoCapitalization.autoCapitalizationMode = autoCapitalizationMode;
    modifierWithKey(this._modifiersWithKeys, SearchAutoCapitalizationModifier.identity, SearchAutoCapitalizationModifier, ArkSearchAutoCapitalization);
    return this;
  }

  textAreaAutoCapitalization(autoCapitalizationMode: AutoCapitalizationMode): this {
    let ArkTextAreaAutoCapitalization = new ArkTextAreaAutoCapitalization();
    ArkTextAreaAutoCapitalization.autoCapitalizationMode = autoCapitalizationMode;
    modifierWithKey(this._modifiersWithKeys, TextAreaAutoCapitalizationModifier.identity, TextAreaAutoCapitalizationModifier, ArkTextAreaAutoCapitalization);
    return this;
  }

  textInputAutoCapitalization(autoCapitalizationMode: AutoCapitalizationMode): this {
    let ArkTextInputAutoCapitalization = new ArkTextInputAutoCapitalization();
    ArkTextInputAutoCapitalization.autoCapitalizationMode = autoCapitalizationMode;
    modifierWithKey(this._modifiersWithKeys, TextAreaAutoCapitalizationModifier.identity, TextAreaAutoCapitalizationModifier, ArkTextInputAutoCapitalization);
    return this;
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

  advancedBlendMode(blendMode: BlendMode, blendApplyType?: BlendApplyType): this {
    let arkBlendMode = new ArkBlendMode();
    arkBlendMode.blendMode = blendMode;
    arkBlendMode.blendApplyType = blendApplyType;
    modifierWithKey(this._modifiersWithKeys, AdvancedBlendModeModifier.identity,
      AdvancedBlendModeModifier, arkBlendMode);
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
    let onVisibleAreaChange = new ArkOnVisibleAreaChange();
    onVisibleAreaChange.ratios = ratios;
    onVisibleAreaChange.event = event;
    this._onVisibleAreaChange = onVisibleAreaChange;
    if (typeof ratios === 'undefined' || typeof event === 'undefined') {
      modifierWithKey(this._modifiersWithKeys, OnVisibleAreaChangeModifier.identity, OnVisibleAreaChangeModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, OnVisibleAreaChangeModifier.identity, OnVisibleAreaChangeModifier, onVisibleAreaChange);
    }
    return this;
  }

  onChildTouchTest(event: (value: Array<TouchTestInfo>) => TouchResult): this {
    this._onChildTouchTestEvent = event;
    modifierWithKey(this._modifiersWithKeys, OnChildTouchTestModifier.identity, OnChildTouchTestModifier, event);
    return this;
  }

  onTouchIntercept(callback: Callback<TouchEvent, HitTestMode>): this {
    this._onTouchInterceptEvent = callback;
    modifierWithKey(this._modifiersWithKeys, OnTouchInterceptModifier.identity, OnTouchInterceptModifier, callback);
    return this;
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
    modifierWithKey(this._modifiersWithKeys, AccessibilityTextModifier.identity, AccessibilityTextModifier, value);
    return this;
  }

  accessibilityDescription(value: string): this {
    modifierWithKey(this._modifiersWithKeys, AccessibilityDescriptionModifier.identity, AccessibilityDescriptionModifier, value);
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

  accessibilityRole(value: AccessibilityRoleType): this {
    modifierWithKey(this._modifiersWithKeys, AccessibilityRoleModifier.identity, AccessibilityRoleModifier, value);
    return this;
  }

  onAccessibilityFocus(value: AccessibilityFocusCallback): this {
    modifierWithKey(this._modifiersWithKeys, AccessibilityFocusCallbackModifier.identity, AccessibilityFocusCallbackModifier, value);
    return this;
  }

  onAccessibilityActionIntercept(value: AccessibilityActionInterceptCallback): this {
    modifierWithKey(this._modifiersWithKeys,
      AccessibilityActionInterceptCallbackModifier.identity, AccessibilityActionInterceptCallbackModifier, value);
    return this;
  }

  onAccessibilityHoverTransparent(value: AccessibilityTransparentCallback): this {
    modifierWithKey(this._modifiersWithKeys,
      AccessibilityHoverTransparentModifier.identity, AccessibilityHoverTransparentModifier, value);
    return this;
  }

  accessibilityNextFocusId(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityNextFocusIdModifier.identity, AccessibilityNextFocusIdModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityNextFocusIdModifier.identity, AccessibilityNextFocusIdModifier, undefined);
    }
    return this;
  }

  accessibilityDefaultFocus(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDefaultFocusModifier.identity, AccessibilityDefaultFocusModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDefaultFocusModifier.identity, AccessibilityDefaultFocusModifier, undefined);
    }
    return this;
  }

  accessibilityUseSamePage(value: AccessibilitySamePageMode): this {
    modifierWithKey(this._modifiersWithKeys, AccessibilityUseSamePageModifier.identity, AccessibilityUseSamePageModifier, value);
    return this;
  }

  accessibilityScrollTriggerable(value: boolean): this {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityScrollTriggerableModifier.identity, AccessibilityScrollTriggerableModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityScrollTriggerableModifier.identity, AccessibilityScrollTriggerableModifier, undefined);
    }
    return this;
  }

  accessibilityTextHint(value: string): this {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextHintModifier.identity, AccessibilityTextHintModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextHintModifier.identity, AccessibilityTextHintModifier, undefined);
    }
    return this;
  }

  accessibilityVirtualNode(builder: CustomBuilder): this {
    throw new Error('Method not implemented.');
  }

  accessibilityChecked(isCheck: boolean): this {
    if (typeof isCheck === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityCheckedModifier.identity, AccessibilityCheckedModifier, isCheck);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityCheckedModifier.identity, AccessibilityCheckedModifier, undefined);
    }
    return this;
  }
  
  accessibilitySelected(isCheck: boolean): this {
    if (typeof isCheck === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilitySelectedModifier.identity, AccessibilitySelectedModifier, isCheck);
    } else {
      modifierWithKey(this._modifiersWithKeys, AccessibilitySelectedModifier.identity, AccessibilitySelectedModifier, undefined);
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

  customProperty(key: string, value: object): this {
    let returnBool = getUINativeModule().frameNode.setCustomPropertyModiferByKey(this.nativePtr, key, value);
    if (!returnBool) {
      const property = new ArkCustomProperty();
      property.key = key;
      property.value = value;
      modifierWithKey(this._modifiersWithKeys, CustomPropertyModifier.identity, CustomPropertyModifier, property);
      getUINativeModule().frameNode.setRemoveCustomProperties(this.nativePtr);
    }
    return this;
  }

  systemBarEffect(): this {
    modifierWithKey(this._modifiersWithKeys, SystemBarEffectModifier.identity, SystemBarEffectModifier, null);
    return this;
  }

  focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this {
    let arkFocusScopeId = new ArkFocusScopeId();
    if (isString(id)) {
      arkFocusScopeId.id = id;
    }
    if (typeof isGroup === 'boolean') {
      arkFocusScopeId.isGroup = isGroup;
    }
    if (typeof arrowStepOut === 'boolean') {
      arkFocusScopeId.arrowStepOut = arrowStepOut;
    }
    modifierWithKey(
      this._modifiersWithKeys, FocusScopeIdModifier.identity, FocusScopeIdModifier, arkFocusScopeId);
    return this;
  }

  focusScopePriority(scopeId: string, priority?: number): this {
    let arkFocusScopePriority = new ArkFocusScopePriority();
    if (isString(scopeId)) {
      arkFocusScopePriority.scopeId = scopeId;
    }
    if (typeof priority === 'number') {
      arkFocusScopePriority.priority = priority;
    }
    modifierWithKey(
      this._modifiersWithKeys, FocusScopePriorityModifier.identity, FocusScopePriorityModifier, arkFocusScopePriority);
    return this;
  }
  pixelRound(value:PixelRoundPolicy):this {
    modifierWithKey(this._modifiersWithKeys, PixelRoundModifier.identity, PixelRoundModifier, value);
  }
  focusBox(value:FocusBoxStyle):this {
    modifierWithKey(this._modifiersWithKeys, FocusBoxModifier.identity, FocusBoxModifier, value);
  }
  nextFocus(value:FocusMovement):this {
    modifierWithKey(this._modifiersWithKeys, NextFocusModifier.identity, NextFocusModifier, value);
  }
  visualEffect(effect: VisualEffect): this {
    modifierWithKey(this._modifiersWithKeys, VisualEffectModifier.identity, VisualEffectModifier, effect);
    return this;
  }
  backgroundFilter(filter: Filter): this {
    modifierWithKey(this._modifiersWithKeys, BackgroundFilterModifier.identity, BackgroundFilterModifier, filter);
    return this;
  }
  foregroundFilter(filter: Filter): this {
    modifierWithKey(this._modifiersWithKeys, ForegroundFilterModifier.identity, ForegroundFilterModifier, filter);
    return this;
  }
  compositingFilter(filter: Filter): this {
    modifierWithKey(this._modifiersWithKeys, CompositingFilterModifier.identity, CompositingFilterModifier, filter);
    return this;
  }
  foregroundEffect(options: ForegroundEffectOptions): this {
    modifierWithKey(this._modifiersWithKeys, ForegroundEffectModifier.identity, ForegroundEffectModifier, options);
    return this;
  }
  freeze(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, FreezeModifier.identity, FreezeModifier, value);
    return this;
  }
  maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
    modifierWithKey(this._modifiersWithKeys, MaskShapeModifier.identity, MaskShapeModifier, value);
    return this;
  }
  clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
    modifierWithKey(this._modifiersWithKeys, ClipShapeModifier.identity, ClipShapeModifier, value);
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

class UICommonEvent {
  private _nodePtr: Object | null;
  private _instanceId: number;
  private _clickEvent?: (event: ClickEvent) => void;
  private _touchEvent?: (event: TouchEvent) => void;
  private _onAppearEvent?: () => void;
  private _onDisappearEvent?: () => void;
  private _onAttachEvent?: () => void;
  private _onDetachEvent?: () => void;
  private _onKeyEvent?: (event: KeyEvent) => void;
  private _onFocusEvent?: () => void;
  private _onBlur?: () => void;
  private _onHoverEvent?: (isHover: boolean, event: HoverEvent) => void;
  private _onHoverMoveEvent?: (event: HoverEvent) => void;
  private _onMouseEvent?: (event: MouseEvent) => void;
  private _onSizeChangeEvent?: SizeChangeCallback;
  private _onVisibleAreaApproximateChange?: VisibleAreaChangeCallback;

  setInstanceId(instanceId: number): void {
    this._instanceId = instanceId;
  }
  setNodePtr(nodePtr: Object | null): void {
    this._nodePtr = nodePtr;
  }
  // the first param is used to indicate frameNode
  // the second param is used to indicate the callback
  // the third param is used to indicate the instanceid
  // other options will be indicated after them
  setOnClick(callback: (event: ClickEvent) => void): void {
    this._clickEvent = callback;
    getUINativeModule().frameNode.setOnClick(this._nodePtr, callback, this._instanceId);
  }
  setOnTouch(callback: (event: TouchEvent) => void): void {
    this._touchEvent = callback;
    getUINativeModule().frameNode.setOnTouch(this._nodePtr, callback, this._instanceId);
  }
  setOnAppear(callback: () => void): void {
    this._onAppearEvent = callback;
    getUINativeModule().frameNode.setOnAppear(this._nodePtr, callback, this._instanceId);
  }
  setOnDisappear(callback: () => void): void {
    this._onDisappearEvent = callback;
    getUINativeModule().frameNode.setOnDisappear(this._nodePtr, callback, this._instanceId);
  }
  setOnAttach(callback: () => void): void {
    this._onAttachEvent = callback;
    getUINativeModule().frameNode.setOnAttach(this._nodePtr, callback, this._instanceId);
  }
  setOnDetach(callback: () => void): void {
    this._onDetachEvent = callback;
    getUINativeModule().frameNode.setOnDetach(this._nodePtr, callback, this._instanceId);
  }
  setOnKeyEvent(callback: (event: KeyEvent) => void): void {
    this._onKeyEvent = callback;
    getUINativeModule().frameNode.setOnKeyEvent(this._nodePtr, callback, this._instanceId);
  }
  setOnFocus(callback: () => void): void {
    this._onFocusEvent = callback;
    getUINativeModule().frameNode.setOnFocus(this._nodePtr, callback, this._instanceId);
  }
  setOnBlur(callback: () => void): void {
    this._onBlur = callback;
    getUINativeModule().frameNode.setOnBlur(this._nodePtr, callback, this._instanceId);
  }
  setOnHover(callback: (isHover: boolean, event: HoverEvent) => void): void {
    this._onHoverEvent = callback;
    getUINativeModule().frameNode.setOnHover(this._nodePtr, callback, this._instanceId);
  }
  setOnHoverMove(callback: (event: HoverMoveEvent) => void): void {
    this._onHoverMoveEvent = callback;
    getUINativeModule().frameNode.setOnHoverMove(this._nodePtr, callback, this._instanceId);
  }
  setOnMouse(callback: (event: MouseEvent) => void): void {
    this._onMouseEvent = callback;
    getUINativeModule().frameNode.setOnMouse(this._nodePtr, callback, this._instanceId);
  }
  setOnSizeChange(callback: SizeChangeCallback): void {
    this._onSizeChangeEvent = callback;
    getUINativeModule().frameNode.setOnSizeChange(this._nodePtr, callback, this._instanceId);
  }
  setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, callback: VisibleAreaChangeCallback): void {
    this._onVisibleAreaApproximateChange = callback;
    getUINativeModule().frameNode.setOnVisibleAreaApproximateChange(this._nodePtr, callback, this._instanceId, options.ratios, options.expectedUpdateInterval ? options.expectedUpdateInterval : 1000);
  }
}

class UIScrollableCommonEvent extends UICommonEvent {
  private _onReachStartEvent?: () => void;
  private _onReachEndEvent?: () => void;
  private _onScrollStartEvent?: () => void;
  private _onScrollStopEvent?: () => void;
  private _onScrollFrameBeginEvent?: (offset: number, state: ScrollState) => { offsetRemain: number; };
  private _onWillScrollEvent?: (scrollOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult;
  private _onDidScrollEvent?: (offset: number, scrollState: ScrollState) => void;

  setOnReachStart(callback: () => void): void {
    this._onReachStartEvent = callback;
    getUINativeModule().frameNode.setOnReachStart(this._nodePtr, callback, this._instanceId);
  }
  setOnReachEnd(callback: () => void): void {
    this._onReachEndEvent = callback;
    getUINativeModule().frameNode.setOnReachEnd(this._nodePtr, callback, this._instanceId);
  }
  setOnScrollStart(callback: () => void): void {
    this._onScrollStartEvent = callback;
    getUINativeModule().frameNode.setOnScrollStart(this._nodePtr, callback, this._instanceId);
  }
  setOnScrollStop(callback): void {
    this._onScrollStopEvent = callback;
    getUINativeModule().frameNode.setOnScrollStop(this._nodePtr, callback, this._instanceId);
  }
  setOnScrollFrameBegin(callback: (offset: number, state: ScrollState) => { offsetRemain: number; }): void {
    this._onScrollFrameBeginEvent = callback;
    getUINativeModule().frameNode.setOnScrollFrameBegin(this._nodePtr, callback, this._instanceId);
  }
  setOnWillScroll(callback: (scrollOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): void {
    this._onWillScrollEvent = callback;
    getUINativeModule().frameNode.setOnWillScroll(this._nodePtr, callback, this._instanceId);
  }
  setOnDidScroll(callback: (scrollOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): void {
    this._onDidScrollEvent = callback;
    getUINativeModule().frameNode.setOnDidScroll(this._nodePtr, callback, this._instanceId);
  }
}

class UIListEvent extends UIScrollableCommonEvent {
  private _onScrollIndexEvent?: (start: number, end: number, center: number) => void;
  private _onScrollVisibleContentEvent?: OnScrollVisibleContentChangeCallback;
  setOnScrollIndex(callback: (start: number, end: number, center: number) => void): void {
    this._onScrollIndexEvent = callback;
    getUINativeModule().frameNode.setOnListScrollIndex(this._nodePtr, callback, this._instanceId);
  }
  setOnScrollVisibleContentChange(callback: OnScrollVisibleContentChangeCallback): void {
    this._onScrollVisibleContentEvent = callback;
    getUINativeModule().frameNode.setOnScrollVisibleContentChange(this._nodePtr, callback, this._instanceId);
  }
}

class UIScrollEvent extends UIScrollableCommonEvent {
  private _onWillScrollEvent?: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult;
  private _onDidScrollEvent?: (xOffset: number, yOffset: number, scrollState: ScrollState) => void;
  setOnWillScroll(callback: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): void {
    this._onWillScrollEvent = callback;
    getUINativeModule().frameNode.setOnScrollWillScroll(this._nodePtr, callback, this._instanceId);
  }
  setOnDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): void {
    this._onDidScrollEvent = callback;
    getUINativeModule().frameNode.setOnScrollDidScroll(this._nodePtr, callback, this._instanceId);
  }
}

class UIGridEvent extends UIScrollableCommonEvent {
  private _onGridScrollIndexEvent?: (first: number, last: number) => void;
  setOnScrollIndex(callback: (first: number, last: number) => void): void {
    this._onGridScrollIndexEvent = callback;
    getUINativeModule().frameNode.setOnGridScrollIndex(this._nodePtr, callback, this._instanceId);
  }
}

class UIWaterFlowEvent extends UIScrollableCommonEvent {
  private _onScrollIndexEvent?: (first: number, last: number) => void;
  setOnScrollIndex(callback: (first: number, last: number) => void): void {
    this._onScrollIndexEvent = callback;
    getUINativeModule().frameNode.setOnWaterFlowScrollIndex(this._nodePtr, callback, this._instanceId);
  }
}

function attributeModifierFunc<T>(modifier: AttributeModifier<T>,
  componentBuilder: (nativePtr: KNode) => ArkComponent,
  modifierBuilder: (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => ArkComponent)
{
  if (modifier === undefined || modifier === null) {
    ArkLogConsole.info("custom modifier is undefined");
    return;
  }
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return componentBuilder(nativeNode);
  });
  if (modifier.isAttributeUpdater === true) {
    let modifierJS = globalThis.requireNapi('arkui.modifier');
    if (modifier.modifierState === modifierJS.AttributeUpdater.StateEnum.INIT) {
      modifier.modifierState = modifierJS.AttributeUpdater.StateEnum.UPDATE;
      modifier.attribute = modifierBuilder(nativeNode, ModifierType.STATE, modifierJS);
      modifierJS.ModifierUtils.applySetOnChange(modifier.attribute);
      modifier.initializeModifier(modifier.attribute);
      applyUIAttributesInit(modifier, nativeNode, component);
      component.applyModifierPatch();
    } else {
      modifier.attribute.applyStateUpdatePtr(component);
      if (modifier.attribute._nativePtrChanged) {
        modifier.onComponentChanged(modifier.attribute);
      }
      modifier.attribute.applyNormalAttribute(component);
      applyUIAttributes(modifier, nativeNode, component);
      component.applyModifierPatch();
    }
  } else {
    applyUIAttributes(modifier, nativeNode, component);
    component.applyModifierPatch();
  }
}

function attributeModifierFuncWithoutStateStyles<T>(modifier: AttributeModifier<T>,
  componentBuilder: (nativePtr: KNode) => ArkComponent,
  modifierBuilder: (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => ArkComponent)
{
  if (modifier === undefined || modifier === null) {
    ArkLogConsole.info("custom modifier is undefined");
    return;
  }
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return componentBuilder(nativeNode);
  });
  if (modifier.isAttributeUpdater === true) {
    let modifierJS = globalThis.requireNapi('arkui.modifier');
    if (modifier.modifierState === modifierJS.AttributeUpdater.StateEnum.INIT) {
      modifier.modifierState = modifierJS.AttributeUpdater.StateEnum.UPDATE;
      modifier.attribute = modifierBuilder(nativeNode, ModifierType.STATE, modifierJS);
      modifierJS.ModifierUtils.applySetOnChange(modifier.attribute);
      modifier.initializeModifier(modifier.attribute);
      component.applyModifierPatch();
    } else {
      modifier.attribute.applyStateUpdatePtr(component);
      modifier.attribute.applyNormalAttribute(component);
      if (modifier.applyNormalAttribute) {
        modifier.applyNormalAttribute(component);
      }
      component.applyModifierPatch();
    }
  } else {
    if (modifier.applyNormalAttribute) {
      modifier.applyNormalAttribute(component);
    }
    component.applyModifierPatch();
  }
}

class UIGestureEvent {
  private _nodePtr: Object | null;
  private _weakNodePtr: JsPointerClass;
  private _gestures: GestureHandler[] | undefined;
  private _destructorCallback: Callback<number>;
  setNodePtr(nodePtr: Object | null): void {
    this._nodePtr = nodePtr;
  }
  setWeakNodePtr(weakNodePtr: JsPointerClass): void {
    this._weakNodePtr = weakNodePtr;
  }
  registerFrameNodeDeletedCallback(nodePtr): void {
    this._destructorCallback = (elementId: number): void => {
      globalThis.__mapOfModifier__.delete(elementId);
    };
    getUINativeModule().common.registerFrameNodeDestructorCallback(nodePtr, this._destructorCallback);
  }
  addGesture(gesture: GestureHandler, priority?: GesturePriority, mask?: GestureMask): void {
    if (this._weakNodePtr?.invalid()) {
      return;
    }
    if (this._gestures === undefined) {
      this._gestures = [gesture];
    } else {
      this._gestures.push(gesture);
    }
    switch (gesture.gestureType) {
      case CommonGestureType.TAP_GESTURE: {
        let tapGesture: TapGestureHandler = gesture as TapGestureHandler;
        getUINativeModule().common.addTapGesture(this._nodePtr, priority, mask, tapGesture.gestureTag,
          tapGesture.allowedTypes, tapGesture.fingers, tapGesture.count, tapGesture.limitFingerCount, tapGesture.onActionCallback);
        break;
      }
      case CommonGestureType.LONG_PRESS_GESTURE: {
        let longPressGesture: LongPressGestureHandler = gesture as LongPressGestureHandler;
        getUINativeModule().common.addLongPressGesture(this._nodePtr, priority, mask, longPressGesture.gestureTag,
          longPressGesture.allowedTypes, longPressGesture.fingers, longPressGesture.repeat,
          longPressGesture.duration, longPressGesture.limitFingerCount,
          longPressGesture.onActionCallback, longPressGesture.onActionEndCallback, longPressGesture.onActionCancelCallback);
        break;
      }
      case CommonGestureType.PAN_GESTURE: {
        let panGesture: PanGestureHandler = gesture as PanGestureHandler;
        getUINativeModule().common.addPanGesture(this._nodePtr, priority, mask, panGesture.gestureTag,
          panGesture.allowedTypes, panGesture.fingers, panGesture.direction, panGesture.distance,
          panGesture.limitFingerCount, panGesture.distanceMap, panGesture.onActionStartCallback,
          panGesture.onActionUpdateCallback, panGesture.onActionEndCallback, panGesture.onActionCancelCallback);
        break;
      }
      case CommonGestureType.SWIPE_GESTURE: {
        let swipeGesture: SwipeGestureHandler = gesture as SwipeGestureHandler;
        getUINativeModule().common.addSwipeGesture(this._nodePtr, priority, mask, swipeGesture.gestureTag,
          swipeGesture.allowedTypes, swipeGesture.fingers, swipeGesture.direction, swipeGesture.speed,
          swipeGesture.limitFingerCount, swipeGesture.onActionCallback);
        break;
      }
      case CommonGestureType.PINCH_GESTURE: {
        let pinchGesture: PinchGestureHandler = gesture as PinchGestureHandler;
        getUINativeModule().common.addPinchGesture(this._nodePtr, priority, mask, pinchGesture.gestureTag,
          pinchGesture.allowedTypes, pinchGesture.fingers, pinchGesture.distance,
          pinchGesture.limitFingerCount, pinchGesture.onActionStartCallback,
          pinchGesture.onActionUpdateCallback, pinchGesture.onActionEndCallback, pinchGesture.onActionCancelCallback);
        break;
      }
      case CommonGestureType.ROTATION_GESTURE: {
        let rotationGesture: RotationGestureHandler = gesture as RotationGestureHandler;
        getUINativeModule().common.addRotationGesture(this._nodePtr, priority, mask, rotationGesture.gestureTag,
          rotationGesture.allowedTypes, rotationGesture.fingers, rotationGesture.angle,
          rotationGesture.limitFingerCount, rotationGesture.onActionStartCallback,
          rotationGesture.onActionUpdateCallback, rotationGesture.onActionEndCallback,
          rotationGesture.onActionCancelCallback);
        break;
      }
      case CommonGestureType.GESTURE_GROUP: {
        let gestureGroup: GestureGroupHandler = gesture as GestureGroupHandler;
        let groupPtr = getUINativeModule().common.addGestureGroup(this._nodePtr,
          gestureGroup.gestureTag, gestureGroup.onCancelCallback, gestureGroup.mode);
        gestureGroup.gestures.forEach((item) => {
          addGestureToGroup(this._nodePtr, item, groupPtr);
        });
        getUINativeModule().common.attachGestureGroup(this._nodePtr, priority, mask, groupPtr);
        break;
      }
      default:
        break;
    }
  }
  addParallelGesture(gesture: GestureHandler, mask?: GestureMask): void {
    this.addGesture(gesture, GesturePriority.PARALLEL, mask);
  }
  removeGestureByTag(tag: string): void {
    if (this._weakNodePtr?.invalid()) {
      return;
    }
    getUINativeModule().common.removeGestureByTag(this._nodePtr, tag);
    for (let index = this._gestures.length - 1; index >= 0; index--) {
      if (this._gestures[index].gestureTag === tag) {
        this._gestures.splice(index, 1);
        continue;
      }
      if (this._gestures[index].gestureType === CommonGestureType.GESTURE_GROUP) {
        let gestureGroup: GestureGroupHandler = this._gestures[index] as GestureGroupHandler;
        removeGestureByTagInGroup(gestureGroup, tag);
      }
    }
  }
  clearGestures(): void {
    if (this._weakNodePtr?.invalid()) {
      return;
    }
    getUINativeModule().common.clearGestures(this._nodePtr);
    this._gestures = [];
  }
}

function removeGestureByTagInGroup(gestureGroup: GestureGroupHandler, tag: string) {
  for (let index = gestureGroup.gestures.length - 1; index >= 0; index--) {
    if (gestureGroup.gestures[index].gestureTag === tag) {
      gestureGroup.gestures.splice(index, 1);
      continue;
    }
    if (gestureGroup.gestures[index].gestureType === CommonGestureType.GESTURE_GROUP) {
      removeGestureByTagInGroup(gestureGroup.gestures[index], tag);
    }
  }
}

function addGestureToGroup(nodePtr: Object | null, gesture: any, gestureGroupPtr: any) {
  switch (gesture.gestureType) {
    case CommonGestureType.TAP_GESTURE: {
      let tapGesture: TapGestureHandler = gesture as TapGestureHandler;
      getUINativeModule().common.addTapGestureToGroup(nodePtr, tapGesture.gestureTag, tapGesture.allowedTypes,
        tapGesture.fingers, tapGesture.count, tapGesture.limitFingerCount, tapGesture.onActionCallback,
        gestureGroupPtr);
      break;
    }
    case CommonGestureType.LONG_PRESS_GESTURE: {
      let longPressGesture: LongPressGestureHandler = gesture as LongPressGestureHandler;
      getUINativeModule().common.addLongPressGestureToGroup(nodePtr, longPressGesture.gestureTag, longPressGesture.allowedTypes,
        longPressGesture.fingers, longPressGesture.repeat, longPressGesture.duration, longPressGesture.limitFingerCount,
        longPressGesture.onActionCallback, longPressGesture.onActionEndCallback, longPressGesture.onActionCancelCallback, gestureGroupPtr);
      break;
    }
    case CommonGestureType.PAN_GESTURE: {
      let panGesture: PanGestureHandler = gesture as PanGestureHandler;
      getUINativeModule().common.addPanGestureToGroup(nodePtr, panGesture.gestureTag, panGesture.allowedTypes,
        panGesture.fingers, panGesture.direction, panGesture.distance, panGesture.limitFingerCount,
        panGesture.distanceMap, panGesture.onActionStartCallback, panGesture.onActionUpdateCallback,
        panGesture.onActionEndCallback, panGesture.onActionCancelCallback, gestureGroupPtr);
      break;
    }
    case CommonGestureType.SWIPE_GESTURE: {
      let swipeGesture: SwipeGestureHandler = gesture as SwipeGestureHandler;
      getUINativeModule().common.addSwipeGestureToGroup(nodePtr, swipeGesture.gestureTag, swipeGesture.allowedTypes,
        swipeGesture.fingers, swipeGesture.direction, swipeGesture.speed, swipeGesture.limitFingerCount,
        swipeGesture.onActionCallback, gestureGroupPtr);
      break;
    }
    case CommonGestureType.PINCH_GESTURE: {
      let pinchGesture: PinchGestureHandler = gesture as PinchGestureHandler;
      getUINativeModule().common.addPinchGestureToGroup(nodePtr, pinchGesture.gestureTag, pinchGesture.allowedTypes,
        pinchGesture.fingers, pinchGesture.distance, pinchGesture.limitFingerCount, pinchGesture.onActionStartCallback,
        pinchGesture.onActionUpdateCallback, pinchGesture.onActionEndCallback, pinchGesture.onActionCancelCallback, gestureGroupPtr);
      break;
    }
    case CommonGestureType.ROTATION_GESTURE: {
      let rotationGesture: RotationGestureHandler = gesture as RotationGestureHandler;
      getUINativeModule().common.addRotationGestureToGroup(nodePtr, rotationGesture.gestureTag, rotationGesture.allowedTypes,
        rotationGesture.fingers, rotationGesture.angle, rotationGesture.limitFingerCount,
        rotationGesture.onActionStartCallback, rotationGesture.onActionUpdateCallback,
        rotationGesture.onActionEndCallback, rotationGesture.onActionCancelCallback, gestureGroupPtr);
      break;
    }
    case CommonGestureType.GESTURE_GROUP: {
      let gestureGroup: GestureGroupHandler = gesture as GestureGroupHandler;
      let groupPtr = getUINativeModule().common.addGestureGroupToGroup(nodePtr, gestureGroup.gestureTag,
        gestureGroup.onCancelCallback, gestureGroup.mode, gestureGroupPtr);
      gestureGroup.gestures.forEach((item) => {
        addGestureToGroup(nodePtr, item, groupPtr);
      });
      break;
    }
    default:
      break;
  }
}

function applyGesture(modifier: GestureModifier, component: ArkComponent): void {

  if (modifier.applyGesture !== undefined) {
    let gestureEvent: UIGestureEvent = component.getOrCreateGestureEvent();
    gestureEvent.clearGestures();
    modifier.applyGesture(gestureEvent);
  }
}

globalThis.__mapOfModifier__ = new Map();
function __gestureModifier__(modifier) {
  if (modifier === undefined || modifier === null) {
    return;
  }
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  if (globalThis.__mapOfModifier__.get(elmtId)) {
    let component = globalThis.__mapOfModifier__.get(elmtId);
    applyGesture(modifier, component);
  } else {
    let component = new ArkComponent(nativeNode);
    globalThis.__mapOfModifier__.set(elmtId, component);
    applyGesture(modifier, component);
  }
}

const __elementIdToCustomProperties__ = new Map();

function __setValidCustomProperty__(nodeId: number, key: string, value: Object): void {
  if (!__elementIdToCustomProperties__.has(nodeId)) {
    __elementIdToCustomProperties__.set(nodeId, new Map());
  }

  const customProperties = __elementIdToCustomProperties__.get(nodeId);

  if (customProperties) {
    customProperties.set(key, value);
  }
}

function __removeCustomProperty__(nodeId: number, key: string): boolean {
  if (__elementIdToCustomProperties__.has(nodeId)) {
    const customProperties = __elementIdToCustomProperties__.get(nodeId);

    if (customProperties) {
      customProperties.delete(key);
      return customProperties.size > 0;
    }
  }

  return false;
}

function __removeCustomProperties__(nodeId: number): void {
  __elementIdToCustomProperties__.delete(nodeId);
}

function __getCustomProperty__(nodeId: number, key: string): Object | undefined {
  if (__elementIdToCustomProperties__.has(nodeId)) {
    const customProperties = __elementIdToCustomProperties__.get(nodeId);

    if (customProperties) {
      return customProperties.get(key);
    }
  }

  return undefined;
}

function __getCustomPropertyString__(nodeId: number, key: string): string | undefined {
  if (__elementIdToCustomProperties__.has(nodeId)) {
    const customProperties = __elementIdToCustomProperties__.get(nodeId);

    if (customProperties) {
      return JSON.stringify(customProperties.get(key));
    }
  }

  return undefined;
}

function __getCustomPropertyMapString__(nodeId: number): string | undefined {
  const customProperties = __elementIdToCustomProperties__.get(nodeId);
  if (customProperties === undefined) {
    return undefined;
  }
  const resultObj = Object.create(null);
  const obj = Object.fromEntries(customProperties);
  Object.keys(obj).forEach(key => {
    const value = obj[key];
    let str = "{}";
    try {
      str = JSON.stringify(value);
    } catch (err) {
      resultObj[key] = "Unsupported Type";
      return;
    }
    if ((value !== "{}" && str === "{}") || str == null) {
      resultObj[key] = "Unsupported Type";
    } else {
      resultObj[key] = value;
    }
  });
  return JSON.stringify(resultObj);
}

function __setCustomProperty__(nodeId: number, key: string, value: Object): boolean {
  if (value !== undefined) {
    __setValidCustomProperty__(nodeId, key, value);
    return true;
  } else {
    return __removeCustomProperty__(nodeId, key);
  }
}
