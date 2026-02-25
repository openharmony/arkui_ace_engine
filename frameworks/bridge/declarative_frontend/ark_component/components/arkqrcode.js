/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
function loadComponent() {
  if (globalThis.__ArkComponent__ !== undefined && loadComponent.componentObj === undefined) {
    class ArkQRCodeComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      allowChildCount() {
        return 0;
      }
      initialize(value) {
        modifierWithKey(this._modifiersWithKeys, QRValueModifier.identity, QRValueModifier, value[0]);
        return this;
      }
      color(value) {
        modifierWithKey(this._modifiersWithKeys, QRColorModifier.identity, QRColorModifier, value);
        return this;
      }
      backgroundColor(value) {
        modifierWithKey(this._modifiersWithKeys, QRBackgroundColorModifier.identity, QRBackgroundColorModifier, value);
        return this;
      }
      contentOpacity(value) {
        modifierWithKey(this._modifiersWithKeys, QRContentOpacityModifier.identity, QRContentOpacityModifier, value);
        return this;
      }
    }
    class QRValueModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        getUINativeModule().qrcode.setQRValue(node, this.value);
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    QRValueModifier.identity = Symbol('QRCodeValue');
    class QRColorModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().qrcode.resetQRColor(node);
        }
        else {
          getUINativeModule().qrcode.setQRColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    QRColorModifier.identity = Symbol('color');
    class QRBackgroundColorModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().qrcode.resetQRBackgroundColor(node);
        }
        else {
          getUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    QRBackgroundColorModifier.identity = Symbol('qrBackgroundColor');
    class QRContentOpacityModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().qrcode.resetContentOpacity(node);
        }
        else {
          getUINativeModule().qrcode.setContentOpacity(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    QRContentOpacityModifier.identity = Symbol('qrContentOpacity');
    loadComponent.componentObj = {'component' : ArkQRCodeComponent };
  }
 return loadComponent.componentObj;
}
class JSQRCode extends JSViewAbstract {
    static create(value) {
        getUINativeModule().qrcode.create(value);
    }
    static color(value) {
        getUINativeModule().qrcode.setQRColor(true, value);
    }
    static backgroundColor(value) {
        getUINativeModule().qrcode.setQRBackgroundColor(true, value);
    }
    static contentOpacity(value) {
        getUINativeModule().qrcode.setContentOpacity(true, value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return createComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.QRCodeModifier(nativePtr, classType);
        });
    };
    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
     static onDetach(value) {
        __Common__.onDetach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }
    static onClick(value) {
        __Common__.onClick(value);
    }
    static onTouch(value) {
        __Common__.onTouch(value);
    }  
    static onHover(value) {
        __Common__.onHover(value);
    }
    static remoteMessage(value) {
        __Common__.remoteMessage(value);
    }
}

function createComponent(nativePtr, classType) {
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent() {
    globalThis.ArkQRCodeComponent = ArkQRCodeComponent;
}

function exportView() {
    globalThis.QRCode = JSQRCode;
}

export default { loadComponent, createComponent, exportComponent, exportView };
