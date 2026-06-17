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
    class ArkLazyGridLayout extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      columnsGap(value: LengthMetrics): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridColumnsGapModifier.identity, LazyGridColumnsGapModifier, value);
        return this;
      }
      rowsGap(value: LengthMetrics): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridRowsGapModifier.identity, LazyGridRowsGapModifier, value);
        return this;
      }
      sticky(value: StickyStyle): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridStickyModifier.identity, LazyGridStickyModifier, value);
        return this;
      }
      header(value: CustomBuilder | ComponentContent | undefined): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridHeaderModifier.identity, LazyGridHeaderModifier, value);
        return this;
      }
      footer(value: CustomBuilder | ComponentContent | undefined): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridFooterModifier.identity, LazyGridFooterModifier, value);
        return this;
      }
      onVisibleIndexesChange(callback: ((start: number, end: number) => void) | undefined): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridOnVisibleIndexesChangeModifier.identity,
          LazyGridOnVisibleIndexesChangeModifier, callback);
        return this;
      }
    }

    class ArkLazyVGridLayoutComponent extends ArkLazyGridLayout implements LazyVGridLayoutAttribute {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      columnsTemplate(value: string): this {
        modifierWithKey(this._modifiersWithKeys, LazyGridColumnsTemplateModifier.identity, LazyGridColumnsTemplateModifier, value);
        return this;
      }
    }

    class LazyGridColumnsGapModifier extends ModifierWithKey<LengthMetrics> {
      constructor(value: LengthMetrics) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || !isObject(this.value)) {
          getUINativeModule().lazyGridLayout.resetColumnsGap(node);
        } else {
          getUINativeModule().lazyGridLayout.setColumnsGap(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (LazyGridColumnsGapModifier as any).identity = Symbol('lazyGridColumnsGap');

    class LazyGridRowsGapModifier extends ModifierWithKey<LengthMetrics> {
      constructor(value: LengthMetrics) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || !isObject(this.value)) {
          getUINativeModule().lazyGridLayout.resetRowsGap(node);
        } else {
          getUINativeModule().lazyGridLayout.setRowsGap(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (LazyGridRowsGapModifier as any).identity = Symbol('lazyGridRowsGap');
    
    class LazyGridStickyModifier extends ModifierWithKey<StickyStyle> {
      constructor(value: StickyStyle) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || !isNumber(this.value)) {
          getUINativeModule().lazyGridLayout.resetSticky(node);
        } else {
          getUINativeModule().lazyGridLayout.setSticky(node, this.value);
        }
      }
    }
    (LazyGridStickyModifier as any).identity = Symbol('lazyGridSticky');

    class LazyGridHeaderModifier extends ModifierWithKey<CustomBuilder | ComponentContent | undefined> {
      constructor(value: CustomBuilder | ComponentContent | undefined) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || (!isObject(this.value) && !isFunction(this.value))) {
          getUINativeModule().lazyGridLayout.resetHeader(node);
        } else {
          getUINativeModule().lazyGridLayout.setHeader(node, this.value);
        }
      }
    }
    (LazyGridHeaderModifier as any).identity = Symbol('lazyGridHeader');

    class LazyGridFooterModifier extends ModifierWithKey<CustomBuilder | ComponentContent | undefined> {
      constructor(value: CustomBuilder | ComponentContent | undefined) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || (!isObject(this.value) && !isFunction(this.value))) {
          getUINativeModule().lazyGridLayout.resetFooter(node);
        } else {
          getUINativeModule().lazyGridLayout.setFooter(node, this.value);
        }
      }
    }
    (LazyGridFooterModifier as any).identity = Symbol('lazyGridFooter');

    class LazyGridOnVisibleIndexesChangeModifier extends ModifierWithKey<((start: number, end: number) => void) | undefined> {
      constructor(value: ((start: number, end: number) => void) | undefined) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset || !isFunction(this.value)) {
          getUINativeModule().lazyGridLayout.resetOnVisibleIndexesChange(node);
        } else {
          getUINativeModule().lazyGridLayout.setOnVisibleIndexesChange(node, this.value);
        }
      }
    }
    (LazyGridOnVisibleIndexesChangeModifier as any).identity = Symbol('lazyGridOnVisibleIndexesChange');

    class LazyGridColumnsTemplateModifier extends ModifierWithKey<string> {
      constructor(value: string) {
        super(value);
      }
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().lazyVGridLayout.resetColumnsTemplate(node);
        } else {
          getUINativeModule().lazyVGridLayout.setColumnsTemplate(node, this.value);
        }
      }
    }
    (LazyGridColumnsTemplateModifier as any).identity = Symbol('lazyVGridColumnsTemplate');
    loadComponent.componentObj = {'component' : ArkLazyVGridLayoutComponent };
  }
  return loadComponent.componentObj;
}

class JSLazyVGridLayout extends JSContainerBase {
  static create(): void {
    getUINativeModule().lazyVGridLayout.create();
  }
  static rowsGap(value: any): void {
    getUINativeModule().lazyGridLayout.setRowsGap(true, value);
  }
  static columnsGap(value: any): void {
    getUINativeModule().lazyGridLayout.setColumnsGap(true, value);
  }
  static columnsTemplate(value: any): void {
    getUINativeModule().lazyVGridLayout.setColumnsTemplate(true, value);
  }
  static sticky(value: any): void {
    getUINativeModule().lazyGridLayout.setSticky(true, value);
  }
  static header(value: any): void {
    getUINativeModule().lazyGridLayout.setHeader(true, value);
  }
  static footer(value: any): void {
    getUINativeModule().lazyGridLayout.setFooter(true, value);
  }
  static onVisibleIndexesChange(value: any): void {
    getUINativeModule().lazyGridLayout.setOnVisibleIndexesChange(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.LazyVGridLayoutModifier(nativePtr, classType);
    });
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
  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
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

function createComponent(nativePtr: any, classType: any) {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkLazyVGridLayoutComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.LazyVGridLayout = JSLazyVGridLayout;
}

export default { loadComponent, createComponent, exportComponent, exportView };