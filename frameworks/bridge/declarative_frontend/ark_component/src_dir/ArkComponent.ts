/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
/// <reference path="./CommonUtils.ts" />
const arkUINativeModule = globalThis.getArkUINativeModule();
function getUINativeModule(): any {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
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
      if (isNumber((this.value as ShadowOptions).shadowStyle)) {
        getUINativeModule().common.setShadow(node, (this.value as ShadowOptions).shadowStyle, undefined, undefined, undefined, undefined, undefined, undefined);
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
    if (isNumber((this.value as ShadowOptions).shadowStyle)) {
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
        this.value?.angle, this.value?.direction,
        this.value?.colors, this.value?.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue?.angle === this.value?.angle) &&
      (this.stageValue?.direction === this.value?.direction) &&
      (this.stageValue?.colors === this.value?.colors) &&
      (this.stageValue?.repeating === this.value?.repeating));
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
        this.value?.center, this.value?.radius, this.value?.colors, this.value?.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue?.center === this.value?.center) &&
      (this.stageValue?.radius === this.value?.radius) &&
      (this.stageValue?.colors === this.value?.colors) &&
      (this.stageValue?.repeating === this.value?.repeating));
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
        this.value?.center,
        this.value?.start, this.value?.end, this.value?.rotation,
        this.value?.colors, this.value?.metricsColors, this.value?.repeating);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue?.center === this.value?.center) &&
      (this.stageValue?.start === this.value?.start) &&
      (this.stageValue?.end === this.value?.end) &&
      (this.stageValue?.rotation === this.value?.rotation) &&
      (this.stageValue?.colors === this.value?.colors) &&
      (this.stageValue?.metricsColors === this.value?.metricsColors) &&
      (this.stageValue?.repeating === this.value?.repeating));
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
        this.value?.value, this.value?.align,
        this.value?.offsetX, this.value?.offsetY,
        this.value?.hasOptions, this.value?.hasOffset);
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

      if (!isUndefined(this.value?.slice)) {
        if (isLengthType(this.value?.slice) || isResource(this.value?.slice)) {
          let tmpSlice = this.value?.slice as Length;
          sliceTop = tmpSlice;
          sliceRight = tmpSlice;
          sliceBottom = tmpSlice;
          sliceLeft = tmpSlice;
        } else {
          let tmpSlice = this.value?.slice as EdgeWidths;
          sliceTop = tmpSlice.top;
          sliceRight = tmpSlice.right;
          sliceBottom = tmpSlice.bottom;
          sliceLeft = tmpSlice.left;
        }
      }
      repeat = this.value?.repeat;
      if (!isUndefined(this.value?.source)) {
        if (isString(this.value?.source) || isResource(this.value?.source)) {
          source = this.value?.source;
        } else {
          let tmpSource = this.value!.source as LinearGradient;
          sourceAngle = tmpSource.angle;
          sourceDirection = tmpSource.direction;
          sourceColors = tmpSource.colors;
          sourceRepeating = tmpSource.repeating;
        }
      }
      if (!isUndefined(this.value?.width)) {
        if (isLengthType(this.value?.width) || isResource(this.value?.width)) {
          let tmpWidth = this.value?.width as Length;
          widthTop = tmpWidth;
          widthRight = tmpWidth;
          widthBottom = tmpWidth;
          widthLeft = tmpWidth;
        } else {
          let tmpWidth = this.value?.width as EdgeWidths;
          widthTop = tmpWidth.top;
          widthRight = tmpWidth.right;
          widthBottom = tmpWidth.bottom;
          widthLeft = tmpWidth.left;
        }
      }
      if (!isUndefined(this.value?.outset)) {
        if (isLengthType(this.value?.outset) || isResource(this.value?.outset)) {
          let tmpOutset = this.value?.outset as Length;
          outsetTop = tmpOutset;
          outsetRight = tmpOutset;
          outsetBottom = tmpOutset;
          outsetLeft = tmpOutset;
        } else {
          let tmpOutset = this.value?.outset as EdgeWidths;
          outsetTop = tmpOutset.top;
          outsetRight = tmpOutset.right;
          outsetBottom = tmpOutset.bottom;
          outsetLeft = tmpOutset.left;
        }
      }
      fill = this.value?.fill;
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
          const localizedEdgeColors = this.value.color as LocalizedEdgeColors;
          if (localizedEdgeColors.start || localizedEdgeColors.end) {
            leftColor = localizedEdgeColors.start;
            rightColor = localizedEdgeColors.end;
            topColor = localizedEdgeColors.top;
            bottomColor = localizedEdgeColors.bottom;
          } else {
            const edgeColors = this.value.color as EdgeColors;
            leftColor = edgeColors.left;
            rightColor = edgeColors.right;
            topColor = edgeColors.top;
            bottomColor = edgeColors.bottom;
          }
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
    return true;
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

class ExcludeFromRenderGroupModifier extends ModifierWithKey<boolean|undefined> {
  constructor(value: boolean|undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('excludeFromRenderGroup');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetExcludeFromRenderGroup(node);
    } else {
      getUINativeModule().common.setExcludeFromRenderGroup(node, this.value);
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