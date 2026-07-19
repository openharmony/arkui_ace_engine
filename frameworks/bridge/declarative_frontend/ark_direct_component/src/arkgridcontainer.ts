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

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkGridContainerComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType?: any) {
        super(nativePtr, classType);
      }
      alignItems(value: any): this {
        throw new Error('Method not implemented.');
      }
      justifyContent(value: any): this {
        throw new Error('Method not implemented.');
      }
      pointLight(value: any): this {
        throw new Error('Method not implemented.');
      }
    }
    loadComponent.componentObj = { component: ArkGridContainerComponent };
  }
  return loadComponent.componentObj;
}

class JSGridContainer extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().gridContainer.create(params);
  }
  static pop(): void {
    getUINativeModule().gridContainer.pop();
    JSContainerBase.pop();
  }
  static createWithWrap(value: any): void { Column.createWithWrap(value); }
  static fillParent(value: any): void { Flex.fillParent(value); }
  static wrapContent(value: any): void { Flex.wrapContent(value); }
  static justifyContent(value: any): void { Column.justifyContent(value); }
  static alignItems(value: any): void { Column.alignItems(value); }
  static reverse(value: any): void { Column.reverse(value); }
  static alignContent(value: any): void { Flex.alignContent(value); }
  static height(value: any): void { Flex.height(value); }
  static width(value: any): void { Flex.width(value); }
  static size(value: any): void { Flex.size(value); }
  static pointLight(value: any): void { __Common__.pointLight(value); }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => createComponent(nativePtr),
      (nativePtr: any, classType: any, modifierJS: any) => new modifierJS.CommonModifier(nativePtr, classType));
  }
  static onAttach(value: any): void { __Common__.onAttach(value); }
  static onAppear(value: any): void { __Common__.onAppear(value); }
  static onDetach(value: any): void { __Common__.onDetach(value); }
  static onDisAppear(value: any): void { __Common__.onDisAppear(value); }
  static onTouch(value: any): void { __Common__.onTouch(value); }
  static onHover(value: any): void { __Common__.onHover(value); }
  static onKeyEvent(value: any): void { __Common__.onKeyEvent(value); }
  static onDeleteEvent(value: any): void { __Common__.onDeleteEvent(value); }
  static onClick(value: any): void { __Common__.onClick(value); }
  static onPan(value: any): void { __Common__.onPan(value); }
  static remoteMessage(value: any): void { __Common__.remoteMessage(value); }
}

function createComponent(nativePtr: any, classType?: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  loadComponent();
  globalThis.ArkGridContainerComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.GridContainer = JSGridContainer;
}

export default { loadComponent, createComponent, exportComponent, exportView };
