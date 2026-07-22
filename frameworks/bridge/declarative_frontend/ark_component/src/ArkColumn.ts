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
class ColumnAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('columnAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetAlignItems(node);
    } else {
      getUINativeModule().column.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ColumnJustifyContentModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('columnJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetJustifyContent(node);
    } else {
      getUINativeModule().column.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ColumnSpaceModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity:Symbol = Symbol('columnSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetSpace(node);
    }
    else {
      getUINativeModule().column.setSpace(node, this.value);
    }
  }
  checkObjectDiff() : boolean {
    return this.stageValue !== this.value;
  }
}
class ColumnPointLightModifier extends ModifierWithKey<PointLightStyle> {
  constructor(value: PointLightStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('columnPointLight');
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

class ColumnReverseModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('columnReverse');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetReverse(node);
    } else {
      getUINativeModule().column.setReverse(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

interface ColumnParam {
  space: string | number;
}
class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): ColumnAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ColumnSpaceModifier.identity, ColumnSpaceModifier, (value[0] as ColumnParam).space);
    }
    return this
  }
  alignItems(value: HorizontalAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnAlignItemsModifier.identity, ColumnAlignItemsModifier, value);
    return this;
  }
  justifyContent(value: FlexAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnJustifyContentModifier.identity, ColumnJustifyContentModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnPointLightModifier.identity, ColumnPointLightModifier, value);
    return this;
  }
  reverse(value: boolean | undefined): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnReverseModifier.identity, ColumnReverseModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkColumnComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ColumnModifier(nativePtr, classType);
  });
};
