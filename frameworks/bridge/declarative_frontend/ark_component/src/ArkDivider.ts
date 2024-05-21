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
class DividerVerticalModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetVertical(node);
    } else {
      getUINativeModule().divider.setVertical(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class DividerLineCapModifier extends ModifierWithKey<LineCapStyle> {
  constructor(value: LineCapStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerLineCap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetLineCap(node);
    } else {
      getUINativeModule().divider.setLineCap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class DividerColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetColor(node);
    } else {
      getUINativeModule().divider.setColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class DividerStrokeWidthModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerStrokeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetStrokeWidth(node);
    } else {
      getUINativeModule().divider.setStrokeWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ArkDividerComponent extends ArkComponent implements DividerAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): DividerAttribute {
    return this;
  }
  allowChildCount(): number {
    return 0;
  }
  vertical(value: boolean): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerVerticalModifier.identity, DividerVerticalModifier, value);
    return this;
  }
  color(value: ResourceColor): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerColorModifier.identity, DividerColorModifier, value);
    return this;
  }
  strokeWidth(value: number | string): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerStrokeWidthModifier.identity, DividerStrokeWidthModifier, value);
    return this;
  }
  lineCap(value: LineCapStyle): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerLineCapModifier.identity, DividerLineCapModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Divider.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkDividerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.DividerModifier(nativePtr, classType);
  });
};
