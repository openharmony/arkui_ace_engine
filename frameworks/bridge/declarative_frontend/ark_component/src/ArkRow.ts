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
class RowAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('rowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().row.resetAlignItems(node);
    } else {
      getUINativeModule().row.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class RowJustifyContentlModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('rowJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().row.resetJustifyContent(node);
    } else {
      getUINativeModule().row.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class RowSpaceModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity:Symbol = Symbol('rowSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().row.resetSpace(node);
    }
    else {
      getUINativeModule().row.setSpace(node, this.value);
    }
  }
  checkObjectDiff() : boolean {
    return this.stageValue !== this.value;
  }
}

class RowPointLightModifier extends ModifierWithKey<PointLightStyle> {
  constructor(value: PointLightStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('rowPointLight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX: Dimension | undefined;
      let positionY: Dimension | undefined;
      let positionZ: Dimension | undefined;
      let intensity: number | undefined;
      let color: ResourceColor | undefined;
      let illuminated: number | undefined;
      let bloom: number | undefined;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}

class RowReverseModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('rowReverse');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().row.resetReverse(node);
    } else {
      getUINativeModule().row.setReverse(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

interface RowParam {
  space: string | number;
}

class ArkRowComponent extends ArkComponent implements RowAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): RowAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, RowSpaceModifier.identity, RowSpaceModifier, (value[0] as RowParam).space);
    }
    return this
  }
  alignItems(value: VerticalAlign): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowAlignItemsModifier.identity, RowAlignItemsModifier, value);
    return this;
  }
  justifyContent(value: FlexAlign): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowJustifyContentlModifier.identity, RowJustifyContentlModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowPointLightModifier.identity, RowPointLightModifier, value);
    return this;
  }
  reverse(value: boolean | undefined): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowReverseModifier.identity, RowReverseModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.Row.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRowComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RowModifier(nativePtr, classType);
  });
};
