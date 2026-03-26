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
    class ArkCounterComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      onInc(event: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterOnIncModifier.identity, CounterOnIncModifier, event);
        return this;
      }
      onDec(event: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterOnDecModifier.identity, CounterOnDecModifier, event);
        return this;
      }
      enableDec(value: any): this {
        modifierWithKey(this._modifiersWithKeys, EnableDecModifier.identity, EnableDecModifier, value);
        return this;
      }
      enableInc(value: any): this {
        modifierWithKey(this._modifiersWithKeys, EnableIncModifier.identity, EnableIncModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterBackgroundColorModifier.identity, CounterBackgroundColorModifier, value);
        return this;
      }
      width(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterWidthModifier.identity, CounterWidthModifier, value);
        return this;
      }
      height(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterHeightModifier.identity, CounterHeightModifier, value);
        return this;
      }
      size(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CounterSizeModifier.identity, CounterSizeModifier, value);
        return this;
      }
    }

    class CounterOnIncModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterOnInc(node);
        } else {
          getUINativeModule().counter.setCounterOnInc(node, this.value);
        }
      }
    }
    (CounterOnIncModifier as any).identity = Symbol('counterOnInc');

    class CounterOnDecModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterOnDec(node);
        } else {
          getUINativeModule().counter.setCounterOnDec(node, this.value);
        }
      }
    }
    (CounterOnDecModifier as any).identity = Symbol('counterOnDec');

    class CounterHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterHeight(node);
        }
        else {
          getUINativeModule().counter.setCounterHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (CounterHeightModifier as any).identity = Symbol('CounterHeight');

    class CounterWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterWidth(node);
        }
        else {
          getUINativeModule().counter.setCounterWidth(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (CounterWidthModifier as any).identity = Symbol('CounterWidth');

    class CounterBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterBackgroundColor(node);
        }
        else {
          getUINativeModule().counter.setCounterBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (CounterBackgroundColorModifier as any).identity = Symbol('CounterBackgroundColor');

    class CounterSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetCounterSize(node);
        }
        else {
          getUINativeModule().counter.setCounterSize(node, this.value.width, this.value.height);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
      }
    }
    (CounterSizeModifier as any).identity = Symbol('CounterSize');

    class EnableIncModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetEnableInc(node);
        }
        else {
          getUINativeModule().counter.setEnableInc(node, this.value);
        }
      }
    }
    (EnableIncModifier as any).identity = Symbol('enableInc');

    class EnableDecModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().counter.resetEnableDec(node);
        }
        else {
          getUINativeModule().counter.setEnableDec(node, this.value);
        }
      }
    }
    (EnableDecModifier as any).identity = Symbol('enableDec');

    loadComponent.componentObj = {'component' : ArkCounterComponent };
  }
  return loadComponent.componentObj;
}

class JSCounter extends JSContainerBase {
  static create(): void {
    getUINativeModule().counter.create();
  }
  static onInc(event: any): void {
    getUINativeModule().counter.setCounterOnInc(true, event);
  }
  static onDec(event: any): void {
    getUINativeModule().counter.setCounterOnDec(true, event);
  }
  static enableDec(value: any): void {
    getUINativeModule().counter.setEnableDec(true, value);
  }
  static enableInc(value: any): void {
    getUINativeModule().counter.setEnableInc(true, value);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().counter.setCounterBackgroundColor(true, value);
  }
  static width(value: any): void {
    getUINativeModule().counter.setCounterWidth(true, value);
  }
  static height(value: any): void {
    getUINativeModule().counter.setCounterHeight(true, value);
  }
  static size(value: any): void {
    if (value !== undefined && value !== null) {
      getUINativeModule().counter.setCounterSize(true, value.width, value.height);
    }
  }
  static controlWidth(value: any): void {
    getUINativeModule().counter.controlWidth(true, value);
  }
  static state(value: any): void {
    getUINativeModule().counter.state(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return new (loadComponent as any).componentObj?.component(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.CounterModifier(nativePtr, classType);
    });
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
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
  globalThis.ArkCounterComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Counter = JSCounter;
}

export default { loadComponent, createComponent, exportComponent, exportView };
