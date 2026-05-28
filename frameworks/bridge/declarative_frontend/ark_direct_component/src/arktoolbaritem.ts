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
    class ArkToolBarItemComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
    }
    loadComponent.componentObj = { component: ArkToolBarItemComponent };
  }
  return loadComponent.componentObj;
}

class JSToolBarItem extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().toolBarItem.create(params);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.ToolBarItemModifier(nativePtr, classType);
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
  globalThis.ArkToolBarItemComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.ToolBarItem = JSToolBarItem;
}

export default { loadComponent, createComponent, exportComponent, exportView };
