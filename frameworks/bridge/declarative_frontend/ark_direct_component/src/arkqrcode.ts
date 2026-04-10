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
    class ArkQRCodeComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        return 0;
      }
      initialize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, QRValueModifier.identity, QRValueModifier, value[0]);
        return this;
      }
      color(value: any): this {
        modifierWithKey(this._modifiersWithKeys, QRColorModifier.identity, QRColorModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, QRBackgroundColorModifier.identity, QRBackgroundColorModifier, value);
        return this;
      }
      contentOpacity(value: any): this {
        modifierWithKey(this._modifiersWithKeys, QRContentOpacityModifier.identity, QRContentOpacityModifier, value);
        return this;
      }
    }

    class QRValueModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        getUINativeModule().qrcode.setQRValue(node, this.value);
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (QRValueModifier as any).identity = Symbol('QRCodeValue');

    class QRColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().qrcode.resetQRColor(node);
        }
        else {
          getUINativeModule().qrcode.setQRColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (QRColorModifier as any).identity = Symbol('color');

    class QRBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().qrcode.resetQRBackgroundColor(node);
        }
        else {
          getUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (QRBackgroundColorModifier as any).identity = Symbol('qrBackgroundColor');

    class QRContentOpacityModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().qrcode.resetContentOpacity(node);
        }
        else {
          getUINativeModule().qrcode.setContentOpacity(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (QRContentOpacityModifier as any).identity = Symbol('qrContentOpacity');

    loadComponent.componentObj = {'component' : ArkQRCodeComponent };
  }
  return loadComponent.componentObj;
}

class JSQRCode extends JSViewAbstract {
  static create(value: any): void {
    getUINativeModule().qrcode.create(value);
  }
  static color(value: any): void {
    getUINativeModule().qrcode.setQRColor(true, value);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().qrcode.setQRBackgroundColor(true, value);
  }
  static contentOpacity(value: any): void {
    getUINativeModule().qrcode.setContentOpacity(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return new (loadComponent as any).componentObj?.component(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.QRCodeModifier(nativePtr, classType);
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
  static onClick(value: any): void {
    __Common__.onClick(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
  static onHover(value: any): void {
    __Common__.onHover(value);
  }
  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
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
  globalThis.ArkQRCodeComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.QRCode = JSQRCode;
}

export default { loadComponent, createComponent, exportComponent, exportView };
