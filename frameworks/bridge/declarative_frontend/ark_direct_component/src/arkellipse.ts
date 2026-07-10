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
    class ArkEllipseComponent extends ArkCommonShapeComponent {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
    }
    loadComponent.componentObj = {'component' : ArkEllipseComponent };
  }
  return loadComponent.componentObj;
}

class JSEllipse extends commonModule.CommonShape {
    constructor(value) {
      super();
      return new __Ellipse__(value)
    }
    static create(value: any): void {
        getUINativeModule().ellipse.create(value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.CommonModifier(nativePtr, classType);
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
    globalThis.ArkEllipseComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Ellipse = JSEllipse;
}

export default { loadComponent, createComponent, exportComponent, exportView };
