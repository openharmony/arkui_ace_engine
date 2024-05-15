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
class FlexInitializeModifier extends ModifierWithKey<FlexParam> {
  constructor(value: FlexParam) {
    super(value);
  }
  static identity: Symbol = Symbol('flexInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().flex.resetFlexInitialize(node);
    } else {
      getUINativeModule().flex.setFlexInitialize(node, this.value.direction, this.value.wrap,
        this.value.justifyContent, this.value.alignItems, this.value.alignContent);
    }
  }
}
interface FlexParam {
  direction?: FlexDirection;
  wrap?: FlexWrap;
  justifyContent?: FlexAlign;
  alignItems?: ItemAlign;
  alignContent?: FlexAlign;
}
class ArkFlexComponent extends ArkComponent implements FlexAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  pointLight(value: PointLightStyle): this {
    throw new Error('Method not implemented.');
  }
  initialize(value: Object[]): FlexAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, FlexInitializeModifier.identity,
        FlexInitializeModifier, (value[0] as FlexParam));
    }
    return this;
  }
}

// @ts-ignore
globalThis.Flex.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkFlexComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.FlexModifier(nativePtr, classType);
  });
};
