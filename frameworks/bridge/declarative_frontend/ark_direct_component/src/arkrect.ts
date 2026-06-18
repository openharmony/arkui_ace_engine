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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

getUINativeModule().loadNativeModule('CommonShape');
let commonModule = globalThis.requireNapi('arkui.components.arkcommonshape');
commonModule.exportView();
commonModule.loadComponent();
commonModule.exportComponent();

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkRectComponent extends ArkCommonShapeComponent {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      radiusWidth(value) {
        modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity, RectRadiusWidthModifier, value);
        return this;
      }
      radiusHeight(value) {
        modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity, RectRadiusHeightModifier, value);
        return this;
      }
      radius(value) {
        modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity, RectRadiusModifier, value);
        return this;
      }
      resetRectOptions() {
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
      initializeRoundedRectOptions(value) {
        if (value === undefined || value === null) {
          return;
        }
        if ((value[0].radiusWidth === undefined || value[0].radiusWidth === null) &&
              (value[0].radiusHeight === undefined || value[0].radiusHeight === null)) {
            modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity,
              RectRadiusModifier, undefined);
            return;
        }
        if (value[0].radiusWidth !== undefined && value[0].radiusWidth !== null) {
          modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity,
            RectRadiusWidthModifier, value[0].radiusWidth);
        } else {
          modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity,
            RectRadiusWidthModifier, undefined);
        }
        if (value[0].radiusHeight !== undefined && value[0].radiusHeight !== null) {
          modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity,
            RectRadiusHeightModifier, value[0].radiusHeight);
        } else {
          modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity,
            RectRadiusHeightModifier, undefined);
        }
      }
      initialize(value) {
        if (value[0] === undefined || value[0] === null) {
          this.resetRectOptions();
          return this;
        }
        if (value[0].width !== undefined && value[0].width !== null) {
          modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
            CommonShapeWidthModifier, value[0].width);
        } else {
          modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
            CommonShapeWidthModifier, undefined);
        }
        if (value[0].height !== undefined && value[0].height !== null) {
          modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
            CommonShapeHeightModifier, value[0].height);
        } else {
          modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
            CommonShapeHeightModifier, undefined);
        }
        if (value[0].radius !== undefined && value[0].radius !== null) {
          modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity,
            RectRadiusModifier, value[0].radius);
        } else {
          this.initializeRoundedRectOptions(value);
        }
        return this;
      }
    }

    class RectRadiusWidthModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().rect.resetRectRadiusWidth(node);
        }
        else {
          getUINativeModule().rect.setRectRadiusWidth(node, this.value);
        }
      }
    }
    RectRadiusWidthModifier.identity = Symbol('rectRadiusWidth');
    class RectRadiusHeightModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().rect.resetRectRadiusHeight(node);
        }
        else {
          getUINativeModule().rect.setRectRadiusHeight(node, this.value);
        }
      }
    }
    RectRadiusHeightModifier.identity = Symbol('rectRadiusHeight');
    class RectRadiusModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().rect.resetRectRadius(node);
        }
        else {
          getUINativeModule().rect.setRectRadius(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    RectRadiusModifier.identity = Symbol('rectRadius');

    loadComponent.componentObj = {'component' : ArkRectComponent };
  }
  return loadComponent.componentObj;
}

class JSRect extends commonModule.CommonShape {
    constructor(value) {
      super();
      return new __Rect__(value)
    }
    static create(value: any): void {
        getUINativeModule().rect.create(value);
    }
    static radiusWidth(value: any): void {
        getUINativeModule().rect.setRectRadiusWidth(true, value);
    }
    static radiusHeight(value: any): void {
        getUINativeModule().rect.setRectRadiusHeight(true, value);
    }
    static radius(value: any): void {
        getUINativeModule().rect.setRectRadius(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.RectModifier(nativePtr, classType);
        });
    }

    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
    static onHover(value: any): void {
        __Common__.onHover(value);
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
    globalThis.ArkRectComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Rect = JSRect;
}

export default { loadComponent, createComponent, exportComponent, exportView };
