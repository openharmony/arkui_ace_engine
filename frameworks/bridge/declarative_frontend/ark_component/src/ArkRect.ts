/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/// <reference path="./ArkCommonShape.ts" />
interface RectOptionsParam {
  width?: Length;
  height?: Length;
  radius?: Length | Array<Length>;
  radiusWidth?: Length;
  radiusHeight?: Length;
}
class RectRadiusWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('rectRadiusWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rect.resetRectRadiusWidth(node);
    } else {
      getUINativeModule().rect.setRectRadiusWidth(node, this.value);
    }
  }
}
class RectRadiusHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('rectRadiusHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rect.resetRectRadiusHeight(node);
    } else {
      getUINativeModule().rect.setRectRadiusHeight(node, this.value);
    }
  }
}
class RectRadiusModifier extends ModifierWithKey<Length | Array<any>> {
  constructor(value: Length | Array<any>) {
    super(value);
  }
  static identity: Symbol = Symbol('rectRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rect.resetRectRadius(node);
    } else {
      getUINativeModule().rect.setRectRadius(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ArkRectComponent extends ArkCommonShapeComponent implements RectAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  radiusWidth(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity, RectRadiusWidthModifier, value);
    return this;
  }
  radiusHeight(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity, RectRadiusHeightModifier, value);
    return this;
  }
  radius(value: Length | Array<any>): this {
    modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity, RectRadiusModifier, value);
    return this;
  }
  resetRectOptions(): void {
    modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
      CommonShapeWidthModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
      CommonShapeHeightModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity,
      RectRadiusModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity,
      RectRadiusWidthModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity,
      RectRadiusHeightModifier, undefined);
  }
  initializeRoundedRectOptions(value: RectOptionsParam): void {
    if (isUndefined(value) || isNull(value)) {
      return;
    }
    if ((isUndefined(value.radiusWidth) || isNull(value.radiusWidth)) &&
          (isUndefined(value.radiusHeight) || isNull(value.radiusHeight))) {
        modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity,
          RectRadiusModifier, undefined);
          return;
    }
    if (!isUndefined(value.radiusWidth) && !isNull(value.radiusWidth)) {
      modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity,
        RectRadiusWidthModifier, value.radiusWidth);
    } else {
      modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity,
        RectRadiusWidthModifier, undefined);
    }
    if (!isUndefined(value.radiusHeight) && !isNull(value.radiusHeight)) {
      modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity,
        RectRadiusHeightModifier, value.radiusHeight);
    } else {
      modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity,
        RectRadiusHeightModifier, undefined);
    }
  }
  initialize(value: Object[]): this {
    if (isUndefined(value[0]) || isNull(value[0])) {
      this.resetRectOptions();
      return this;
    }
    const value_casted = value[0] as RectOptionsParam;
    if (!isUndefined(value_casted.width) && !isNull(value_casted.width)) {
      modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
        CommonShapeWidthModifier, value_casted.width);
    } else {
      modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
        CommonShapeWidthModifier, undefined);
    }
    if (!isUndefined(value_casted.height) && !isNull(value_casted.height)) {
      modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
        CommonShapeHeightModifier, value_casted.height);
    } else {
      modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
        CommonShapeHeightModifier, undefined);
    }
    if (!isUndefined(value_casted.radius) && !isNull(value_casted.radius)) {
      modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity,
        RectRadiusModifier, value_casted.radius);
    } else {
      this.initializeRoundedRectOptions(value_casted);
    }
    return this;
  }
}

// @ts-ignore
globalThis.Rect.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRectComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RectModifier(nativePtr, classType);
  });
};
