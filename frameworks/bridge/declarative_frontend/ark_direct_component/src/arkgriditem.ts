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
/// <reference path='./../../ark_component/src/ArkComponent.ts' />
type ComponentObj = {
  component: any
}

/// <reference path='./import.ts' />
class GridItemSelectableModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('gridItemSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelectable(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemSelectable(node, this.value);
    }
  }
}
class GridItemSelectedModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('gridItemSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelected(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemSelected(node, this.value);
    }
  }
}
class GridItemRowStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowStart(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemRowStart(node, this.value);
    }
  }
}
class GridItemRowEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowEnd(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemRowEnd(node, this.value);
    }
  }
}
class GridItemColumnStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnStart(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemColumnStart(node, this.value);
    }
  }
}
class GridItemColumnEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnEnd(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemColumnEnd(node, this.value);
    }
  }
}
class GridItemOptionsModifier extends ModifierWithKey<GridItemOptions> {
  static identity: Symbol = Symbol('gridItemOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.setGridItemOptions(node, undefined);
    } else {
      if (this.value?.style === undefined) {
        getUINativeModule().gridItem.setGridItemOptions(node, undefined);
      } else {
        getUINativeModule().gridItem.setGridItemOptions(node, this.value.style);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.style, this.value?.style);
  }
}
class GridItemOnSelectedModifier extends ModifierWithKey<(isSelected: boolean) => void> {
  constructor(value: (isSelected: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridItemOnSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemOnSelected(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemOnSelected(node, this.value);
    }
  }
}

function loadComponent(): ComponentObj|undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkGridItemComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }

      allowChildCount() {
        return 1;
      }
      initialize(value: Object[]): this {
        if (value.length === 1 && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, GridItemOptionsModifier.identity, GridItemOptionsModifier, value[0]);
        }
        return this;
      }
      rowStart(value: number): this {
        modifierWithKey(this._modifiersWithKeys, GridItemRowStartModifier.identity, GridItemRowStartModifier, value);
        return this;
      }
      rowEnd(value: number): this {
        modifierWithKey(this._modifiersWithKeys, GridItemRowEndModifier.identity, GridItemRowEndModifier, value);
        return this;
      }
      columnStart(value: number): this {
        modifierWithKey(
            this._modifiersWithKeys, GridItemColumnStartModifier.identity, GridItemColumnStartModifier, value);
        return this;
      }
      columnEnd(value: number): this {
        modifierWithKey(this._modifiersWithKeys, GridItemColumnEndModifier.identity, GridItemColumnEndModifier, value);
        return this;
      }
      forceRebuild(value: boolean): this {
        throw new BusinessError(100201, 'forceRebuild not supported in attributeModifier scenario.');
      }
      selectable(value: boolean): this {
        modifierWithKey(
            this._modifiersWithKeys, GridItemSelectableModifier.identity, GridItemSelectableModifier, value);
        return this;
      }
      selected(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, GridItemSelectedModifier.identity, GridItemSelectedModifier, value);
        return this;
      }
      onSelect(event: (isSelected: boolean) => void): this {
        modifierWithKey(
            this._modifiersWithKeys, GridItemOnSelectedModifier.identity, GridItemOnSelectedModifier, event);
        return this;
      }
    }

    loadComponent.componentObj = {'component': ArkGridItemComponent};
  }
  return loadComponent.componentObj;
}

class JSGridItem extends JSContainerBase {
  static name: string = 'GridItem'
  static create(func: any, isLazy: any, style?: any): void {
    getUINativeModule().gridItem.create(func, isLazy, style);
  }
  static pop(): void {
    JSContainerBase.pop();
  }
  static columnStart(value: any): void {
    getUINativeModule().gridItem.setGridItemColumnStart(true, value);
  }
  static columnEnd(value: any): void {
    getUINativeModule().gridItem.setGridItemColumnEnd(true, value);
  }
  static rowStart(value: any): void {
    getUINativeModule().gridItem.setGridItemRowStart(true, value);
  }
  static rowEnd(value: any): void {
    getUINativeModule().gridItem.setGridItemRowEnd(true, value);
  }
  static forceRebuild(value: boolean): void {
    getUINativeModule().gridItem.setForceRebuild(true, value);
  }
  static selectable(value: any): void {
    getUINativeModule().gridItem.setJSSelectable(true, value);
  }
  static onSelect(event: any): void {
    getUINativeModule().gridItem.setJSOnSelect(true, event);
  }
  static width(value: any): void {
    getUINativeModule().gridItem.setJSWidth(true, value);
  }
  static height(value: any): void {
    getUINativeModule().gridItem.setJSHeight(true, value);
  }
  static selected(value: any, callback?: any): void {
    getUINativeModule().gridItem.setJSSelected(true, value, callback);
  }
  static bindContextMenu(content: any, responseType: any, options: any): void {
    getUINativeModule().gridItem.setBindContextMenu(content, responseType, options);
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
  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }
  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(
        this, modifier,
        (nativePtr: any) => {
          return createComponent(nativePtr);
        },
        (nativePtr: any, classType: any, modifierJS: any) => {
          return new modifierJS.GridItemModifier(nativePtr, classType);
        });
  }
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
  globalThis.ArkGridItemComponent = loadComponent.componentObj?.component;
}

function exportView(): void {
  globalThis.GridItem = JSGridItem;
}

export default {loadComponent, createComponent, exportComponent, exportView};