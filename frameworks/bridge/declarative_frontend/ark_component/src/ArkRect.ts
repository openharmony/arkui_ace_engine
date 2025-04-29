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
}

// @ts-ignore
globalThis.Rect.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRectComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RectModifier(nativePtr, classType);
  });
};
