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
const arkCanvasGlobal = globalThis as Record<string, any>;

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkCanvasComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        return 0;
      }
      initialize(value: any): this {
        if (!value.length) {
          return this;
        }
        if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, CanvasParamsModifier.identity, CanvasParamsModifier, value[0]);
        }
        return this;
      }
      onReady(event: any): this {
        modifierWithKey(this._modifiersWithKeys, CanvasOnReadyModifier.identity, CanvasOnReadyModifier, event);
        return this;
      }
      enableAnalyzer(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CanvasEnableAnalyzerModifier.identity,
          CanvasEnableAnalyzerModifier, value);
        return this;
      }
    }

    class CanvasOnReadyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().canvas.resetCanvasOnReady(node);
        } else {
          getUINativeModule().canvas.setCanvasOnReady(node, this.value);
        }
      }
    }
    (CanvasOnReadyModifier as any).identity = Symbol('canvasOnReady');

    class CanvasEnableAnalyzerModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().canvas.resetCanvasEnableAnalyzer(node);
        } else {
          getUINativeModule().canvas.setCanvasEnableAnalyzer(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (CanvasEnableAnalyzerModifier as any).identity = Symbol('canvasEnableAnalyzer');

    class CanvasParamsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        // CanvasParams are handled in CanvasBridge::CreateCanvas in C++
      }
    }
    (CanvasParamsModifier as any).identity = Symbol('canvasParams');

    loadComponent.componentObj = {'component' : ArkCanvasComponent };
  }
  return loadComponent.componentObj;
}

// @ts-ignore
function canvasAttributeModifier(modifier: any): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
    const component = (loadComponent() as any)?.component;
    return component ? new component(nativePtr) : undefined;
  }, (nativePtr: any, classType: any, modifierJS: any) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
}

// Store globally for later use — arkDynamicComponent.js sets globalThis.Canvas AFTER
// this module loads, so we can't set it directly here.
arkCanvasGlobal.__CanvasAttributeModifier__ = canvasAttributeModifier;
// @ts-ignore
if (arkCanvasGlobal.Canvas !== undefined) {
  arkCanvasGlobal.Canvas.attributeModifier = canvasAttributeModifier;
}

class JSCanvas extends JSViewAbstract {
  static create(params?: any): typeof JSCanvas {
    // All node creation and params handling is done in a single C++ call
    // (CanvasBridge::CreateCanvas) to keep view stack operations atomic.
    getUINativeModule().canvas.create(params);
    return this;
  }

  static onReady(event: any): typeof JSCanvas {
    getUINativeModule().canvas.setCanvasOnReady(true, event);
    return this;
  }

  static enableAnalyzer(value: any): typeof JSCanvas {
    getUINativeModule().canvas.setCanvasEnableAnalyzer(true, value);
    return this;
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      const component = (loadComponent() as any)?.component;
      return component ? new component(nativePtr) : undefined;
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  }

  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static onClick(value: any): void {
    __Common__.onClick(value);
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

  static onHover(value: any): void {
    __Common__.onHover(value);
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
  arkCanvasGlobal.ArkCanvasComponent = (loadComponent() as any)?.component;
}

function exportView(): void {
  arkCanvasGlobal.Canvas = JSCanvas;
  // arkComponent.js stores attributeModifier globally since it runs before
  // this module loads and globalThis.Canvas is still undefined at that point.
  if (typeof arkCanvasGlobal.__CanvasAttributeModifier__ === 'function') {
    arkCanvasGlobal.Canvas.attributeModifier = arkCanvasGlobal.__CanvasAttributeModifier__;
  }
}

export default {
  loadComponent,
  createComponent,
  exportComponent,
  exportView,
};
