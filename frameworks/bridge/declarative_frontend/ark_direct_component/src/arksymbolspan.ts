/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class SymbolSpanFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.resetFontColor(node);
        } else {
          getUINativeModule().symbolSpan.setFontColor(node, this.value);
        }
      }
    }
    (SymbolSpanFontColorModifier as any).identity = Symbol('symbolSpanFontColor');
    class SymbolSpanFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.resetFontSize(node);
        } else {
          getUINativeModule().symbolSpan.setFontSize(node, this.value);
        }
      }
    }
    (SymbolSpanFontSizeModifier as any).identity = Symbol('symbolSpanFontSize');
    class SymbolSpanFontWeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.resetFontWeight(node);
        } else {
          getUINativeModule().symbolSpan.setFontWeight(node, this.value.value,
            this.value?.enableVariableFontWeight,
            this.value?.enableDeviceFontWeightCategory);
        }
      }
    }
    (SymbolSpanFontWeightModifier as any).identity = Symbol('symbolSpanFontWeight');
    class SymbolSpanEffectStrategyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.resetEffectStrategy(node);
        } else {
          getUINativeModule().symbolSpan.setEffectStrategy(node, this.value);
        }
      }
    }
    (SymbolSpanEffectStrategyModifier as any).identity = Symbol('symbolSpanEffectStrategy');
    class SymbolSpanRenderingStrategyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.resetRenderingStrategy(node);
        } else {
          getUINativeModule().symbolSpan.setRenderingStrategy(node, this.value);
        }
      }
    }
    (SymbolSpanRenderingStrategyModifier as any).identity = Symbol('symbolSpanRenderingStrategy');
    class SymbolSpanIdModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().symbolSpan.setId(node, "");
        }
        else {
          getUINativeModule().symbolSpan.setId(node, this.value);
        }
      }
    }
    (SymbolSpanIdModifier as any).identity = Symbol('symbolSpanId');
    class ArkSymbolSpanComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      initialize(value: Object[]): this {
        if (value[0] !== undefined) {
          modifierWithKey(this._modifiersWithKeys, SymbolSpanIdModifier.identity, SymbolSpanIdModifier, value[0]);
        }
        return this;
      }
      fontSize(value: number | string | Resource): this {
        modifierWithKey(this._modifiersWithKeys, SymbolSpanFontSizeModifier.identity,
          SymbolSpanFontSizeModifier, value);
        return this;
      }
      fontColor(value: object): this {
        modifierWithKey(this._modifiersWithKeys, SymbolSpanFontColorModifier.identity,
          SymbolSpanFontColorModifier, value);
        return this;
      }
      fontWeight(value: number | FontWeight | string, fontWeightConfigs?: FontWeightConfigs): this {
        let arkFontWeight = new ArkFontWeight();
        arkFontWeight.value = value;
        if (fontWeightConfigs !== null && fontWeightConfigs !== undefined && typeof fontWeightConfigs === 'object') {
          arkFontWeight.enableVariableFontWeight = fontWeightConfigs.enableVariableFontWeight ?? false;
          arkFontWeight.enableDeviceFontWeightCategory = fontWeightConfigs.enableDeviceFontWeightCategory ?? true;
        }
        modifierWithKey(this._modifiersWithKeys, SymbolSpanFontWeightModifier.identity,
          SymbolSpanFontWeightModifier, arkFontWeight);
        return this;
      }
      effectStrategy(value: SymbolEffectStrategy): this {
        modifierWithKey(this._modifiersWithKeys, SymbolSpanEffectStrategyModifier.identity,
          SymbolSpanEffectStrategyModifier, value);
        return this;
      }
      renderingStrategy(value: SymbolRenderingStrategy): this {
        modifierWithKey(this._modifiersWithKeys, SymbolSpanRenderingStrategyModifier.identity,
          SymbolSpanRenderingStrategyModifier, value);
        return this;
      }
    }
    loadComponent.componentObj = { 'component': ArkSymbolSpanComponent };
  }
  return loadComponent.componentObj;
}

class JSSymbolSpan extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().symbolSpan.jsCreate(params);
  }
  static fontSize(value: any): void {
    getUINativeModule().symbolSpan.setFontSize(true, value);
  }
  static fontWeight(value: any, fontWeightConfigs: any): void {
    let arkFontWeight = new ArkFontWeight();
    arkFontWeight.value = value;
    if (fontWeightConfigs !== null && fontWeightConfigs !== undefined && typeof fontWeightConfigs === 'object') {
      arkFontWeight.enableVariableFontWeight = fontWeightConfigs.enableVariableFontWeight ?? false;
      arkFontWeight.enableDeviceFontWeightCategory = fontWeightConfigs.enableDeviceFontWeightCategory ?? true;
    }
    getUINativeModule().symbolSpan.setFontWeight(true, arkFontWeight.value,
        arkFontWeight.enableVariableFontWeight, arkFontWeight.enableDeviceFontWeightCategory);
  }
  static fontColor(value: any): void {
    getUINativeModule().symbolSpan.setFontColor(true, value);
  }
  static effectStrategy(value: any): void {
    getUINativeModule().symbolSpan.setEffectStrategy(true, value);
  }
  static renderingStrategy(value: any): void {
    getUINativeModule().symbolSpan.setRenderingStrategy(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFuncWithoutStateStyles.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.SymbolSpanModifier(undefined, nativePtr, classType);
    });
  }
}
  
function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkSymbolSpanComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.SymbolSpan = JSSymbolSpan;
}
export default { createComponent, exportComponent, exportView, loadComponent };
