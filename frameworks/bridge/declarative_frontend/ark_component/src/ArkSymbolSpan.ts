/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
class SymbolSpanFontColorModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
    getUINativeModule().symbolSpan.resetFontColor(node);
    } else {
    getUINativeModule().symbolSpan.setFontColor(node, this.value);
    }
  }
}

class SymbolSpanFontSizeModifier extends ModifierWithKey<number | string | Resource> {
  constructor(value: number | string | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().symbolSpan.resetFontSize(node);
    } else {
      getUINativeModule().symbolSpan.setFontSize(node, this.value);
    }
  }
}

class SymbolSpanFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  constructor(value: number | FontWeight | string) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().symbolSpan.resetFontWeight(node);
    } else {
      getUINativeModule().symbolSpan.setFontWeight(node, this.value);
    }
  }
}

class SymbolSpanEffectStrategyModifier extends ModifierWithKey<SymbolEffectStrategy> {
  constructor(value: SymbolEffectStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanEffectStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().symbolSpan.resetEffectStrategy(node);
    } else {
      getUINativeModule().symbolSpan.setEffectStrategy(node, this.value);
    }
  }
}

class SymbolSpanRenderingStrategyModifier extends ModifierWithKey<SymbolRenderingStrategy> {
  constructor(value: SymbolRenderingStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanRenderingStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().symbolSpan.resetRenderingStrategy(node);
    } else {
      getUINativeModule().symbolSpan.setRenderingStrategy(node, this.value);
    }
  }
}

class SymbolSpanIdModifier extends ModifierWithKey<Resource> {
  constructor(value: Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('symbolSpanId');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().symbolSpan.setId(node, '');
    }
    else {
      getUINativeModule().symbolSpan.setId(node, this.value);
    }
  }
}
  
class ArkSymbolSpanComponent extends ArkComponent implements SymbolSpanAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): SymbolSpanAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, SymbolSpanIdModifier.identity, SymbolSpanIdModifier, value[0]);
    }
    return this;
  }
  fontSize(value: number | string | Resource): SymbolSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SymbolSpanFontSizeModifier.identity,
      SymbolSpanFontSizeModifier, value);
    return this;
  }
  fontColor(value: object): SymbolSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SymbolSpanFontColorModifier.identity,
      SymbolSpanFontColorModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): SymbolSpanAttribute {
    let fontWeightStr: string = '400';
    if (isNumber(value)) {
      fontWeightStr = value.toString();
    } else if (isString(value)) {
      fontWeightStr = String(value);
    }
    modifierWithKey(this._modifiersWithKeys, SymbolSpanFontWeightModifier.identity,
      SymbolSpanFontWeightModifier, fontWeightStr);
    return this;
  }
  effectStrategy(value: SymbolEffectStrategy): SymbolSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SymbolSpanEffectStrategyModifier.identity,
      SymbolSpanEffectStrategyModifier, value);
    return this;
  }
  renderingStrategy(value: SymbolRenderingStrategy): SymbolSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, SymbolSpanRenderingStrategyModifier.identity,
      SymbolSpanRenderingStrategyModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.SymbolSpan.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFuncWithoutStateStyles.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSymbolSpanComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SymbolSpanModifier(undefined, nativePtr, classType);
  });
};